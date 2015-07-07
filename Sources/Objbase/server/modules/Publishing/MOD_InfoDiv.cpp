/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoDiv.cpp															[]
[] Date:          13.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с разделами информации.										[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoDiv.inc.h"









//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО РАЗДЕЛА																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_New (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_New);
/*............................................................................[]
		<Login                  Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами создания разделов в указанной зоне доступа.
		<Password               Пароль пользователя, запрашивающего операцию.
		<Name                   Имя создаваемого раздела. При этом создастся феод с аналогичным именем. Если передано пустое или неуникальное имя, то система сама придумывает/изменяет имя раздела.
		<Description            Описание создаваемого раздела.
		<ParentID               Родительский раздел.
		<AccessLevelThreshold   Пороговое значение уровня доступа пользователей. Раздел должен иметь более слабый порог, чем уровень её создателя, чтобы тот мог его править/удалять.

		>objID                  Идентификатор созданного раздела.
		>ExitCode               Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment        Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Родительский раздел должен существовать
	if (!CHECK_INFODIV_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный родительский раздел ID=%d", arg.ParentID);
	}
	OC_InfoDiv oc_parent_div (arg.ParentID);
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
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Раздел должен иметь более слабый порог, чем уровень его создателя, 
// чтобы тот мог его править/удалять.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
	}
// Имя раздела не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя раздела не должно быть пустым");
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
	feod_arg.ParentID						= guid(oc_parent_div.m_MOD_Base_GUID).id;
	feod_arg.AccessLevelThreshold		= arg.AccessLevelThreshold;

	MOD_Feod_New (feod_arg);
	if (feod_arg.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

// Создаём раздел, используя его в качестве модульного расширения феода
	SET_MOD_EXTENSION (Concept, feod_arg.objID, InfoDiv, arg.objID);
//----------------------------------------------------------------------------[] 

	CACHE_NUM_InfoDivGetAllSubDivIDs ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ РАЗДЕЛОВ 																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_Enumerate (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь права получения списка.
		<Password					Пароль пользователя, запрашивающего операцию.
		<ParentID               Раздел, чьи подразделы следует перечислить. Если NA -- используется ParentName.
		<ParentName             Раздел, чьи подразделы следует перечислить. Необходимо польностью указать имя: "Concept.Feod.Data.Type.News.Промышленность.Нефть"
		<IncludeParent          Если true, то возвращается и сам ParentID, иначе только его потомки.
		<FeodAttributes			Атрибуты доступа к разделу. Будут перечислены только те разделы, доступ пользователя к которым снабжён указанными атрибутами.
		<FullNameLevel				Уровень в иерархии концептов, начиная с которого выводится название раздела.

		>objIDs						Массив идентификаторов объектов. Выдаются только те разделы, к которым есть доступ с указанными атрибутами.
		>objNames					Массив полных названий разделов.
		>objTypes					Массив типов разделов ("Concept.Feod.Data.Type.News")
		>objLevels					Массив уровней вложенности разделов. У родительского раздела уровень вложенности считается = 0.
		>objFeodIDs					Массив идентификаторов соответствующих зон доступа.
		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




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
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если не указан идентификатор родительского раздела -- ищем по типу
	if (arg.ParentID==NA)
	{
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			ERR_RETURN_COMMENT_1 (ERR_BadName, "Не найден родительский раздел '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetInfoDivIDByFeodID (feod_parent_ID);
	}
// Объект должен существовать
	if (!CHECK_INFODIV_ID (arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный раздел %d", arg.ParentID);
	}
	identifier feod_parent_ID = GetFeodIDByInfoDivID (arg.ParentID);
//----------------------------------------------------------------------------[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем массив всех перечисляемых разделов -- сам раздел и его потомки
	int f;
	identifier_arr FeodArr;
	GetFeodDescendantIDs (feod_parent_ID, FeodArr);
	if (arg.IncludeParent) 
	{
		FeodArr.Insert (0, feod_parent_ID);
	}
// Выкидываем те подразделы, к которым нет доступа
	if (!arg.FeodAttributes.IsEmpty()) for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], arg.FeodAttributes)!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// Заполняем выходные аргументы
	int parent_level = GetFeodLevel (feod_parent_ID);
	for (f=0; f<FeodArr.Size(); f++) if (CHECK_FEOD_ID (FeodArr[f]))
	{
		identifier divID = GetInfoDivIDByFeodID (FeodArr[f]);

		string divName;
		GetInfoDivFullName (divID, divName, arg.FullNameLevel);

		string divType;
		GetInfoDivType (divID, divType);

		int divLevel =	GetFeodLevel (FeodArr[f]) - parent_level;

		arg.objIDs		+= divID;
		arg.objNames	+= divName;
		arg.objTypes	+= divType;
		arg.objFeodIDs	+=	FeodArr[f];
		arg.objLevels	+= divLevel;
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ РАЗДЕЛА																				[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_Delete (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_Delete);
/*............................................................................[]
		<objID					Идентификатор удаляемого объекта.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право удаления [D].
		<Password				Пароль пользователя, запрашивающего операцию.

		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	identifier	div_id = arg.objID;
	if (!CHECK_INFODIV_ID (div_id))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект InfoDiv[%d] не существует", div_id);
	}
	OC_InfoDiv	oc_div	(div_id);
	identifier feod_id = GetFeodIDByInfoDivID (div_id);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять разделы (нет права Concept.Feod.Admin.Feod[D])");
	}
	res = USER_CHECK_ACCESS (loginID, feod_id, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять данный раздел (нет доступа [m] или [M])");
	}
	res = USER_CHECK_ACCESS (loginID, GetFeodParentID (feod_id), "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять данный раздел (нет доступа к изменению структуры родительского раздела -- [M] или [m])");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запоминаем все удаляемые разделы (сам + дочерние)
	identifier_arr	DivArr;
	InfoDivGetAllSubDivIDs (arg.objID, DivArr);
	DivArr.Insert (0, arg.objID);

// Уничтожаем соответствующий феод (и дочерние феоды)
	MOD_Feod_Args			feod_arg;
	feod_arg.Login			= arg.Login;
	feod_arg.Password		= arg.Password;
	feod_arg.objID			= feod_id;
	MOD_Feod_Delete (feod_arg);
	if (feod_arg.ExitCode != ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

//	Ссылки на разделы должны быть удалены из источников и из информационных объектов
	int i, d, iDiv;
	for (iDiv=0; iDiv<DivArr.Size(); iDiv++)
	{
		div_id = DivArr[iDiv];
		oc_div.Open (div_id);
	// Удаляем ссылки на разделы из источников
		for (i=0; i<oc_div.m_InfoSourceSortedID.Size(); i++)
		{
			OC_InfoSource oc_src;
			if (OC_Exist (OBJ_CLASS_ID_InfoSource, oc_div.m_InfoSourceSortedID[i]))
			{
				oc_src.Open (oc_div.m_InfoSourceSortedID[i]);
				for (d=0; d<oc_src.m_InfoDivID.Size(); d++) if (oc_src.m_InfoDivID[d] == div_id)
				{
					oc_src.m_InfoDivID.Del (d);
					d--;
				}
			}
		}
	// Удаляем ссылки на разделы из информационных объектов
		for (i=0; i<oc_div.m_InfoObjectSortedID.Size(); i++)
		{
			OC_InfoObject oc_info;
			if (OC_Exist (OBJ_CLASS_ID_InfoObject, oc_div.m_InfoObjectSortedID[i]))
			{
				oc_info.Open (oc_div.m_InfoObjectSortedID[i]);
				for (d=0; d<oc_info.m_InfoDivID.Size(); d++) if (oc_info.m_InfoDivID[d] == div_id)
				{
					oc_info.m_InfoDivID.Del (d);
					d--;
				}
			}
		}

	// Уничтожаем сам раздел и все его дочерние разделы
		oc_div.Delete	();
	}
//----------------------------------------------------------------------------[] 


	CACHE_NUM_InfoDivGetAllSubDivIDs ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/