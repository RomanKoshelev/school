/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFolder.cpp															[]
[] Date:          31.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с web-файловыми директориями									[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFolder.inc.h"				 






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ОБЪЕКТА КЛАССА WebFolder												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_New (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_New);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права создание [C] и [m].
		<Password					Пароль пользователя, запрашивающего операцию.
		<Name							Имя папки.
		<Description            Описание создаваемой папки
		<ParentID					Родительская папка.
		<ParentName					Имя родительской папки, используется, если ParentID == NA;
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Директория должна иметь более слабый порог, чем уровень её создателя, чтобы тот мог её править/удалять.

		>objID						Идентификатор созданного объекта.
		>ExitCode					Код возврата (OK BadLogin BadPassword BadName AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если не указан идентификатор родительской папки -- ищем по имени
	if (arg.ParentID==NA)
	{
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("Не найдена родительская папка '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "Не найдена родительская папка '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetWebFolderIDByFeodID (feod_parent_ID);
	}
// Родительская папка должна существовать
	if (!CHECK_WEBFOLDER_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный родительский объект ID=%d", arg.ParentID);
	}
	OC_WebFolder oc_parent_folder (arg.ParentID);
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя создаваемого объекта не должно быть пустым");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Неверный пароль или логин");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[] 
// Папка должна иметь более слабый порог, чем уровень её создателя, 
// чтобы тот мог её править/удалять.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём феод
	MOD_Feod_Args feod_arg;

	feod_arg.Login							= arg.Login;
	feod_arg.Password						= arg.Password;
	feod_arg.Name							= arg.Name;
	feod_arg.Description					= arg.Description;
	feod_arg.ParentID						= guid(oc_parent_folder.m_MOD_Base_GUID).id;
	feod_arg.AccessLevelThreshold		= arg.AccessLevelThreshold;

	MOD_Feod_New (feod_arg);
	if (feod_arg.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

// Создаём папку, используя её в качестве модульного расширения феода
	SET_MOD_EXTENSION (Concept, feod_arg.objID, WebFolder, arg.objID);
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ДОСТУПНЫХ ОБЪЕКТОВ КЛАССА WebFolder									[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_Enumerate (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права получения списка [L].
		<Password					Пароль пользователя, запрашивающего операцию.
		<objFirstNo					Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
		<objLastNo					Номер объекта, до которого включительно выводятся объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
		<ParentID					Родительская папка.
		<ParentName					Имя родительской папки, используется, если ParentID == NA;
		<IncludeParent          Если true, то возвращается и сам ParentID, иначе только его потомки. Если родитель включается, то он идёт в массиве objIDs первым.
		<AllDescendants			Если false, то возвращаются только дочернии папки, иначе -- все папки-потомки.
		<FeodAttributes			Атрибуты доступа к папкам. Будут перечислены только те папкам, доступ пользователя к которым снабжён указанными атрибутами.
		<FullNameLevel				Уровень в иерархии концептов, начиная с которого выводится названия папок.

		>objIDs						Массив идентификаторов папок.
		>objNames					Массив названий папок.
		>objTypes					Массив типов соответствующих концептов-феодов ("Concept.Feod.Files.Site.Public")
		>objLevels					Массив уровней вложенности папок. У родительской папки уровень вложенности считается = 0.

		>TotalStoredNum			Сколько всего объектов может быть перечислено в данных условиях.
		>MaxNumInQuery				Максимально допустимое число запрашиваемых за один раз объектов.
		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_WEBFOLDER_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_WEBFOLDER_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "Запрошено %d объектов класса WebFolder, а максимально можно запросить %d", (arg.objLastNo - arg.objFirstNo), MAX_WEBFOLDER_ENUMERATE_NUM);
	}
// Если не указан идентификатор родительской папки -- ищем по имени
	if (arg.ParentID==NA)
	{
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("Не найдена родительская папка '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "Не найдена родительская папка '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetWebFolderIDByFeodID (feod_parent_ID);
	}
// Родительская папка должна существовать
	if (!CHECK_WEBFOLDER_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный родительский объект ID=%d", arg.ParentID);
	}
	OC_WebFolder oc_parent_folder (arg.ParentID);
	identifier   feod_parent_ID = guid(oc_parent_folder.m_MOD_Base_GUID).id;
//----------------------------------------------------------------------------[] 


	



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Неверный пароль или логин");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[] 


	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Получаем список всех объектов
	int				f;
	identifier_arr FeodArr;
	if (arg.AllDescendants)
	{
		GetFeodDescendantIDs (feod_parent_ID, FeodArr);
	}
	else
	{
		OC_Concept (feod_parent_ID).m_Child.CopyTo (FeodArr);
	}
	if (arg.IncludeParent) 
	{
		FeodArr.Insert (0, feod_parent_ID);
	}
	
// Выкидываем те папки, к которым нет указанного доступа и которые не могут быть просмотрены
	if (arg.FeodAttributes.Find ('L')==-1)
	{
		string tmp = arg.FeodAttributes;
		arg.FeodAttributes  = "L";
		arg.FeodAttributes += tmp;
	}
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], arg.FeodAttributes)!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// Проходимся по всем запрошенным объектам и заполняем выходные аргументы
	int parent_level = GetFeodLevel (feod_parent_ID);
	for (f=arg.objFirstNo; f<=arg.objLastNo && f<FeodArr.Size(); f++)
	{
		identifier folderID = GetWebFolderIDByFeodID (FeodArr[f]);

		string folderName;
		GetWebFolderFullName (folderID, folderName, max (arg.FullNameLevel,3));

		string folderType;
		GetWebFolderType		(folderID, folderType);

		int folderLevel =	GetFeodLevel (FeodArr[f]) - parent_level;

		arg.objIDs		+= folderID;
		arg.objNames	+= folderName;
		arg.objTypes	+= folderType;
		arg.objLevels	+= folderLevel;
	}

// Общее число объектов, которых можно перечислить
	arg.TotalStoredNum	=	FeodArr.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ОБЪЕКТА КЛАССА WebFolder											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_GetData (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_GetData);
/*............................................................................[]
		<objID					Идентификатор запрашиваемого объекта.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право чтения [R].
		<Password				Пароль пользователя, запрашивающего операцию.

		>Name						Название папки.
		>FullName				Полное название папки.
		>Description         Описание папки.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект WebFolder[%d] не существует", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
	identifier feodID = GetFeodIDByWebFolderID (arg.objID);
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, feodID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем аргументы полями объекта
	OC_Concept oc_feod (feodID);
	string folderFullName;
	GetWebFolderFullName (arg.objID, folderFullName, 3);

	arg.Name					=	oc_feod.m_Name;
	arg.Description		=	oc_feod.m_Description;
	arg.FullName			=	folderFullName;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ОБЪЕКТА КЛАССА WebFolder											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_PutData (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_PutData);

ERR_RETURN (ERR_FunctionNotImplemented);
#if 0  //{ Разблокировать функцию, когда она понадобится
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект WebFolder[%d] не существует", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.???"), "???");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Изменяем поля объекта
	arg.Name	=	oc_folder.m_Name;

// Проводим коррекцию базы данных в связи с изменениеями в объекте
//	...

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
#endif //}
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ ОБЪЕКТА КЛАССА WebFolder														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_Delete (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_Delete);
ERR_RETURN (ERR_FunctionNotImplemented);
#if 0  //{ Разблокировать функцию, когда она понадобится
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект WebFolder[%d] не существует", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.???"), "???");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проводим коррекцию базы данных в связи с уничтожением объекта
//	...

/*
	1. удалить все дочернии папки
	2. удалить ссылки на феоды из групп (UserGroup)
*/

// Уничтожаем объект
	oc_folder.Delete ();

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
#endif //}
}
//____________________________________________________________________________[]











/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/