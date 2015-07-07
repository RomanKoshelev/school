/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoSource.h															[]
[] Date:          21.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с информационными источниками								[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoSource.inc.h"				 






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ИНФОРМАЦИОННОГО ИСТОЧНИКА											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_New (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_New);
/*............................................................................[]
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь права {Concept.Feod.Aux.Sources}[C].
		<Password				Пароль пользователя, запрашивающего операцию.
		<Name						Название источника информации.
		<Description			Описание источника информации.
		<URL						Web-адрес, по которому находится источник информации.
		<RefreshType			[int] Интерпретируемый интерфейсом признак, показывающий когда источник обновляет содержание.
		<divIDs					К каким информационным разделам будет относиться источник. Можно назначать только те разделы, в которых есть право [R] и ([C] или [W]).

		>objID					Идентификатор созданного объекта.
		>ExitCode				Код возврата (OK BadLogin BadPassword BadName BadID AccessDeny ERR_InsufficientAccessLevel).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
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
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "C");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права создания информационных источников");
	}
// Пользователь может назначать только те разделы, в которых есть право [R] и ([C] или [W]).
	for (int d=0; d<arg.divIDs.Size(); d++)
	{
		if (USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "RC")!=ERR_OK && USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "RW")!=ERR_OK)
		{
			if (!CHECK_INFODIV_ID(arg.divIDs[d]))
			{
				ERR_RETURN_COMMENT_1 (ERR_BadID, "Некорректный идентификатор раздела %d", arg.divIDs[d]);
			}
			else
			{
				string divName;
				GetInfoDivFullName (arg.divIDs[d], divName);
				ERR_RETURN_COMMENT_1 (ERR_InsufficientAccessLevel, "Пользователь не имеет права назначить источник разделу %s, так как не может читать[R] и (создавать[C] или редактировать[W]) объекты в этом разделе.", divName.c_str());
			}
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя создаваемого источника не должно быть пустым");
	}
// Имя объекта должно быть уникальным
	OC_InfoSource oc_src;
	oc_src.SetIndex_Name ();
	if (oc_src.Find (arg.Name))
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "Имя создаваемого источника должно быть уникальным. Источник '%s' уже существует.", arg.Name.c_str());
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём объект
	oc_src.New();
	identifier srcID	= oc_src.GetObjectID ();

// Прописываем значения в поля объекта
	oc_src.m_Name				=	arg.Name;
	oc_src.m_Description		=	arg.Description;
	oc_src.m_RefreshType		=	arg.RefreshType;
	oc_src.m_URL				=	arg.URL;
	oc_src.m_InfoDivID		=	arg.divIDs;

// Заносим источник в разделы
	FOR_EACH_ITEM_EVAL (arg.divIDs,
	{
		OC_InfoDiv (arg.divIDs[i]).m_InfoSourceSortedID.InsertSorted (srcID);
	});

// Запоминаем идентификатор созданного источника
	arg.objID = srcID;

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ДОСТУПНЫХ ИНФОРМАЦИОННЫХ ИСТОЧНИКОВ									[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_Enumerate (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_Enumerate);
/*............................................................................[]
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право {Concept.Feod.Aux.Sources}[L].
		<Password				Пароль пользователя, запрашивающего операцию.
		<objFirstNo				Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
		<objLastNo				Номер объекта, до которого включительно выводятся объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
		<ShowAll					Если true, то выдаётся список всех информационных источников, иначе только тех, которые пользователь может назначать информационным объектам.
		<divID					Запрашиваемые источники должны относиться к указанному разделу или его потомкам. Если NA, то смотреть во всех разделах {Concept.Feod.Data}.
		<divName					Может быть использован, если не указан divID.

		>objIDs					Массив идентификаторов информационных источников. Если ShowAll=false, то выдаются только относящиеся к разделам, в которым у пользователя есть возможность создавать или править объекты (доступ [C] или [W]).
		>objNames				Массив названий информационных источников.
		>objURLs					web-адреса.
		>objRefreshTypes		[int_arr] Интерпретируемый интерфейсом признак, показывающий когда источник обновляет содержание.
		>objDescriptions		Описания. Выдаются только в случае наличия права {Concept.Feod.Aux.Sources}[R].

		>TotalStoredNum		Сколько всего объектов может быть перечислено в данных условиях.
		>MaxNumInQuery			Максимально допустимое число запрашиваемых за один раз объектов.
		>ExitCode				Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
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
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права получения списка информационных источников");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_INFOSOURCE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_INFOSOURCE_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "Запрошено %d объектов класса InfoSource, а максимально можно запросить %d", (arg.objLastNo - arg.objFirstNo), MAX_INFOSOURCE_ENUMERATE_NUM);
	}
// Если не указан ID раздела, но указано имя -- пытаемся установить его по имени
	if (arg.divID==NA && !arg.divName.IsEmpty())
	{
		arg.divID = GetInfoDivIDByType (arg.divName);
	}
//	Иначе -- берём корневой раздел
	else 
	{
		arg.divID = GetInfoDivIDByFeodID (GetFeodIDByType("Concept.Feod.Data"));
	}

// Если указан раздел, то проверим его на валидность
	if (!CHECK_INFODIV_ID(arg.divID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указанный раздел ID=%d не корректен", arg.divID);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Получаем список информационных источников, лежащих в тех разделах,
// в которых пользователь может создавать или редактировать информационные объекты.

//	Получаем список все доступных феодов-разделов
	identifier_arr allFeodIDs;	
	identifier rootFeodID = GetFeodIDByInfoDivID (arg.divID);
	if (!GetFeodDescendantIDs (rootFeodID, allFeodIDs))
	{
		ERR_RETURN_COMMENT (ERR_SYSTEM_ERROR, "Невозможно получить список зон доступа для раздела");
	}
	allFeodIDs.Insert (0, rootFeodID);

//	Все феоды, или только те из них (если ShowAll==false), в которых есть права доступа [R] и ([C] или [W]), 
// преобразуем в разделы и пополняем коллекцию источников.
	identifier_arr allSrcSortedIDs;
	for (int f=0; f<allFeodIDs.Size(); f++)
	{
		if (arg.ShowAll || (USER_CHECK_ACCESS (loginID, allFeodIDs[f], "RC")==ERR_OK) || (USER_CHECK_ACCESS (loginID, allFeodIDs[f], "RW")==ERR_OK))
		{
		// Этот феод-раздел годится для пополнения списка источников
			identifier divID = GetInfoDivIDByFeodID (allFeodIDs[f]);
			if (divID==NA || !CHECK_INFODIV_ID (divID))
			{
				string feodName;
				GetFeodFullName (allFeodIDs[f], feodName);
				SERVER_DEBUG_ERROR_2 ("Феод '%s'[%d] не является разделом.", feodName.c_str(), allFeodIDs[f]);
				continue;
			}
			identifier_arr oc_div_m_InfoSourceSortedID = OC_InfoDiv(divID).m_InfoSourceSortedID;
			for (int i=0; i<oc_div_m_InfoSourceSortedID.Size(); i++)
			{
				if (allSrcSortedIDs.Find(oc_div_m_InfoSourceSortedID[i], true)==-1)
				{
					allSrcSortedIDs.InsertSorted (oc_div_m_InfoSourceSortedID[i]);
				}
			}
		}
	}

// Проходимся по всем получившимся источникам и заполняем выходные аргументы
	bool	bCanReadData	= (USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "R")==ERR_OK);
	static int i;
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<allSrcSortedIDs.Size(); i++)
	{
		if (!OC_Exist (OBJ_CLASS_ID_InfoSource, allSrcSortedIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("Ошибка открытия информационного источника [%d]", allSrcSortedIDs[i]);
			continue;
		}
		OC_InfoSource oc_src (allSrcSortedIDs[i]);

		arg.objIDs				+= allSrcSortedIDs[i];
		arg.objNames			+=	oc_src.m_Name;
		arg.objURLs				+=	string(oc_src.m_URL);
		arg.objRefreshTypes	+=	oc_src.m_RefreshType;
		arg.objDescriptions	+=	bCanReadData? string(oc_src.m_Description): string ("{{Access deny}}");
	}

// Сколько всего источников может быть показано пользователю
	arg.TotalStoredNum = allSrcSortedIDs.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ИНФОРМАЦИОННОГО ИСТОЧНИКА											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_GetData (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_GetData);
/*............................................................................[]
		<objID					Идентификатор запрашиваемого объекта.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право {Concept.Feod.Aux.Sources}[R].
		<Password				Пароль пользователя, запрашивающего операцию.

		>Name						Название источника.
		>Description			Описание источника информации.
		>URL						Web-адрес, по которому находится источник информации.
		>RefreshType			[int] Интерпретируемый интерфейсом признак, показывающий когда источник обновляет содержание.
		>divIDs					К каким информационным разделам относится источник. Показываются только те разделы, в которых пользователь может читать информацию, т.е. имеет доступ [R].
		>divNames				Названия разделов, к которым относится источник.
		>ShowCount				Сколько раз были показаны объекты этого источника.
		>ClickCount				Сколько раз были просмотрены объекты этого источника.
		>CTR						ClickCount*100/ShowCount
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект InfoSource[%d] не существует", arg.objID);
	}
	OC_InfoSource oc_src (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права получать внутренние данные информационных источников");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем аргументы полями объекта
	arg.Name				=	oc_src.m_Name;
	arg.Description	=	oc_src.m_Description;
	arg.URL				=	oc_src.m_URL;
	arg.RefreshType	=	oc_src.m_RefreshType;
	arg.ShowCount		=	oc_src.m_ShowCount;
	arg.ClickCount		=	oc_src.m_ClickCount;
	arg.CTR				=	oc_src.m_CTR;
	arg.divIDs			=	oc_src.m_InfoDivID;

// Выкидываем те разделы, в которых пользователь не может читать информацию
	for (int d=0; d<arg.divIDs.Size(); d++)
	{
		if (USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "R")!=ERR_OK)
		{
		// Пользователю не надо знать, что существует такой раздел
			arg.divIDs.Del (d);
			d--;
		}
		else
		{
			string divName; 
			GetInfoDivFullName (arg.divIDs[d], divName);
			arg.divNames += divName;
		}
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ИНФОРМАЦИОННОГО ИСТОЧНИКА											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_PutData (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_PutData);
/*............................................................................[]
		<objID					Идентификатор изменяемого источника информации.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право {Concept.Feod.Aux.Sources}[R].
		<Password				Пароль пользователя, запрашивающего операцию.

		<Name						Название источника.
		<Description			Описание источника информации.
		<URL						Web-адрес, по которому находится источник информации.
		<RefreshType			[int] Интерпретируемый интерфейсом признак, показывающий когда источник обновляет содержание.
		<divIDs					К каким информационным разделам относится источник. Можно назначать только те разделы, в которых есть право [R] и ([C] или [W]).

		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Эту переменную пишу здесь как статическую, так как иначе глупый VC++6.0 
//	выдаёт INTERNAL COMPILER ERROR
	static int d=0;
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект InfoSource[%d] не существует", arg.objID);
	}
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользоваетель не имеет права редактировать информационные источники");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя информаниционного источника не должно быть пустым");
	}
// Имя объекта должно быть уникальным
	OC_InfoSource oc_src;
	oc_src.SetIndex_Name ();
	if (oc_src.Find (arg.Name) && oc_src.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "Имя информаниционного источника должно быть уникальным. Уже есть другой источник с именем '%s'.", arg.Name.c_str());
	}
	oc_src.Open (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Изменяем поля объекта
	oc_src.m_Name				=	arg.Name;
	oc_src.m_Description		=	arg.Description;
	oc_src.m_URL				=	arg.URL;
	oc_src.m_RefreshType		=	arg.RefreshType;


// Перемещаем источник по разделам:
// arg.divIDs -- к каким разделам, по меннию логина, должен принадлежать объект. 
// Логин не может выкинуть/добавить источник в раздел не имея к нему доступ [R] и ([C] или [W]).
	identifier_arr new_div_arr = oc_src.m_InfoDivID;

// Проходимся по разделам источника и смотрим, какие из них не указаны пользователем, т.е. он решил их выкинуть
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
		if (arg.divIDs.Find(divID)==-1)
		{
		// Пользователь решил, что источник не должен находиться в разделе divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RC")==ERR_OK || USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RW")==ERR_OK)
			{
			// Пользователь имеет право выкинуть источник из раздела
				new_div_arr.Del (d);
				d--;
			// Выкидываем источник из раздела
				OC_InfoDiv oc_div (divID);
				int nIndex = oc_div.m_InfoSourceSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_div.m_InfoSourceSortedID.Del (nIndex);
				}
			}
		}
	}

// Проходимся по разделам, указанным пользоваетелем и смотрим, каких из них нет у источника, т.е. он решил их добавить
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		identifier divID = arg.divIDs[d];
		if (new_div_arr.Find(divID)==-1)
		{
		// Пользователь решил, что источник должен находиться в разделе divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RC")==ERR_OK || USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RW")==ERR_OK)
			{
			// Пользователь имеет право добавить источник в раздел
				new_div_arr.Add (divID);
				OC_InfoDiv (divID).m_InfoSourceSortedID.InsertSorted (arg.objID);
			}
		}
	}

// Изменяем принадлежность источника разделам
	oc_src.m_InfoDivID = new_div_arr;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ ИНФОРМАЦИОННОГО ИСТОЧНИКА														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_Delete (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_Delete);
/*............................................................................[]
		<objID					Идентификатор удаляемого источника.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право {Concept.Feod.Aux.Sources}[D].
		<Password				Пароль пользователя, запрашивающего операцию.

		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект InfoSource[%d] не существует", arg.objID);
	}
	OC_InfoSource oc_src (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять информационные источники");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
//	Источник удалется из разделов.
	for (int d=0; d<oc_src.m_InfoDivID.Size(); d++)
	{
		if (CHECK_INFODIV_ID(oc_src.m_InfoDivID[d]))
		{
			OC_InfoDiv oc_div (oc_src.m_InfoDivID[d]);
			int nIndex = oc_div.m_InfoSourceSortedID.Find (arg.objID, true);
			if (nIndex!=-1)
			{
				oc_div.m_InfoSourceSortedID.Del (nIndex);
			}
			else
			{
				string divName; 
				GetInfoDivFullName (oc_src.m_InfoDivID[d], divName);
				SERVER_DEBUG_ERROR_3 ("Удаляемый источник %s не найден в разделе %s[%d]", string(oc_src.m_Name).c_str(), divName.c_str(), identifier(oc_src.m_InfoDivID[d]));
			}
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("У удаляемого источника %s записан некорректный раздел %d", string(oc_src.m_Name).c_str(), identifier (oc_src.m_InfoDivID[d]));
		}
	}

//	Источник удалется из информационных объектов.
	OC_InfoObject oc_info;
	identifier_arr	infoIDs;
	oc_info.SetIndex_InfoSourceID__InfoTime();
	key_arr ka(arg.objID);
	oc_info.GetClassIdList (infoIDs, &ka);

	for (int i=0; i<infoIDs.Size(); i++)
	{
		oc_info.Open (infoIDs[i]);
		if (oc_info.m_InfoSourceID==arg.objID)
		{
			oc_info.m_InfoSourceID = NA;
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("Удаляемый источник %s не найден у информационного объекта [%s]", string(oc_src.m_Name).c_str(), string(oc_info.m_Name).c_str());
		}
	}

//	Удаляем информационный источник
	oc_src.Delete ();
//----------------------------------------------------------------------------[] 


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