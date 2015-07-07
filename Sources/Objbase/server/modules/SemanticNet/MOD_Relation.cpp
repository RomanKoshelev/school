/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Relation.cpp															[]
[] Date:          08.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с семантическими отношениями									[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Relation.inc.h"






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО СЕМАНТИЧЕСКОГО ОТНОШЕНИЯ												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_New (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_New);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права создания отношений [C].
		<Password					Пароль пользователя, запрашивающего операцию.
		<Name							Имя
		<SysName						Системное название отношения, строится как переменная С++
		<Description				Описание отношения
		<FieldNames					Названия полей
		<FieldSysNames				Системные имена полей, строятся как переменные С++
		<FieldTypes					Типы полей ("object" "byte" "int" "bool" "time" "string" "float")
		<FieldDescriptions		Описания полей
		<FieldInterfaceTypes		Типы полей, интерпретируемые интерфейсом
		<FeodIDs						Зоны доступа, к которым принадлежит отношение		
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей к объекту.

		>objID						Идентификатор созданного объекта.
		>ExitCode					Код возврата (OK BadLogin BadPassword BadName AccessDeny).
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
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_login (loginID);
// Проверяем право доступа -- пользователь должен иметь право создавать отношения в этих феодах
	int f;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, arg.FeodIDs[f], "C");
		if (res!=ERR_OK)
		{
			ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
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
		ERR_RETURN_COMMENT (ERR_BadName, "Имя создаваемого отношения не должно быть пустым");
	}
// Имя отношения должно быть уникальным
	OC_Relation oc_rel;
	oc_rel.SetIndex_Name ();
	if (oc_rel.Find (arg.Name))
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "Имя создаваемого отношения должно быть уникальным");
	}
// Системное имя должно быть корректным
	if (!arg.SysName.CheckSysName())
	{
		SERVER_DEBUG_ERROR_1 ("Некорректное системное имя %s", arg.SysName.c_str());
	}
// Системное имя отношения должно быть уникальным
	oc_rel.SetIndex_SysName ();
	if (oc_rel.Find (arg.SysName))
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "Системное имя создаваемого отношения должно быть уникальным");
	}
// Отношение должно иметь зону доступа
	if (arg.FeodIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Не указана зона доступа создаваемого отношения");
	}
// Преобразовываем зоны доступа в guid'ы
	guid_arr FeodGUIDs;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		OC_Concept oc_feod;
		oc_feod.Open (arg.FeodIDs[f]);
		FeodGUIDs += oc_feod.GetObjectGUID ();
	}	
// Системные имена полей должны быть уникальными и корректными
	if (!RelationCheckFieldSystemNames (arg.FieldSysNames))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Все системные имена полей должны быть уникальными и строитьcя как переменные в С++!");
	}
// Типы полей должны быть корректными
	if (!RelationCheckFieldTypes (arg.FieldTypes))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Указан неизвестный тип поля");
	}
// В отношении должно быть не менее 1-го поля
	if (arg.FieldSysNames.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "В отношении должно быть не менее 1-го поля");
	}
// В отношении должно быть не менее 1-го поля-объекта
	int nObjFld=0;	for (f=0; f<arg.FieldTypes.Size(); f++)
	{
		if (arg.FieldTypes[f]=="object") nObjFld++;
	}
	if (nObjFld==0) ERR_RETURN_COMMENT (ERR_BadArgument, "В отношении должно быть не менее 1-го поля-объекта");

// Число имён полей, описаний и системных имён должно совпадать
	if (arg.FieldSysNames.Size()!=arg.FieldNames.Size() || arg.FieldSysNames.Size()!=arg.FieldDescriptions.Size() || arg.FieldSysNames.Size()!=arg.FieldInterfaceTypes.Size())
	{
		ERR_RETURN_COMMENT_4 (ERR_BadArgument, "Разное число имён [%d], системных имён [%d], описаний полей [%d] и интерфейсных типов [%d]", arg.FieldNames.Size(), arg.FieldSysNames.Size(), arg.FieldDescriptions.Size(), arg.FieldInterfaceTypes.Size());
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём объект
	oc_rel.New ();
	identifier relID = oc_rel.GetObjectID ();

// Прописываем значения в поля объекта
	oc_rel.m_Name						=	arg.Name;
	oc_rel.m_Description				=	arg.Description;
	oc_rel.m_FieldName				=	arg.FieldNames;
	oc_rel.m_FieldSysName			=	arg.FieldSysNames;
	oc_rel.m_FieldType				=	arg.FieldTypes;
	oc_rel.m_FieldDescription		=	arg.FieldDescriptions;
	oc_rel.m_FieldInterfaceType	=	arg.FieldInterfaceTypes;
	oc_rel.m_OwnerGUID				=	oc_login.GetObjectGUID ();
	oc_rel.m_FeodGUID					=	FeodGUIDs;
	oc_rel.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// Запоминаем идентификатор
	arg.objID							=	relID;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ДОСТУПНЫХ СЕМАНТИЧЕСКИХ ОТНОШЕНИЙ										[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_Enumerate (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_Enumerate);
/*............................................................................[]
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь права получения списка [L].
		<Password				Пароль пользователя, запрашивающего операцию.
		<objFirstNo				Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
		<objLastNo				Номер объекта, до которого включительно выводятся объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
		<FeodIDs					К каким зонам обязательно должны принадлежать отношения.
		<FeodNames				Используется, если массив FeodIDs пуст. Имена вида "{Concept.Feod.Semantic...}"
		<Attributes				Атрибуты доступа. Будут перечислены только те отношения, доступ пользователя к которым снабжён указанными атрибутами. Атрибут [L] включается в запрос автоматически.

		>objIDs					Массив идентификаторов перечисленных объектов.
		>objVersions			Массив версий отношений
		>objNames				Массив названий перечисленных объектов.
		>objSysNames			Системные названия отношений
		>objDescriptions		Массив описаний перечисленных объектов.
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
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_RELATION_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_RELATION_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "Запрошено %d отношений, а максимально можно запросить %d", (arg.objLastNo - arg.objFirstNo), MAX_RELATION_ENUMERATE_NUM);
	}
// Если не указаны ID феодов, берём их по имени, которое совпадает с типом
	if (arg.FeodIDs.Size()==0)
	{
		FOR_EACH_ITEM_EVAL(arg.FeodNames, 
		{
			arg.FeodIDs += GetFeodIDByType (arg.FeodNames[i]);
		});
	}
// Феоды должны существовать
	FOR_EACH_ITEM_EVAL (arg.FeodIDs, {if (!CHECK_FEOD_ID (arg.FeodIDs[i])) ERR_RETURN_COMMENT_1 (ERR_BadID, "Указана несуществующая зона доступа ID=%u", arg.FeodIDs[i]);});
//	Должен быть доступ L
	if (arg.Attributes.Find ("L")==-1)
	{
		arg.Attributes += "L";
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Получаем список всех объектов
	int							i,j,N;
	OC_Relation					oc_rel;
	identifier_arr				ALL_RELATION_IDs;
	oc_rel.GetClassIdList	(ALL_RELATION_IDs);

// Вычеркиваем те объекты, к которым нет доступа
	for (i=0; i<ALL_RELATION_IDs.Size(); i++)
	{
		if (USER_CHECK_ACCESS_TO_RELATION (loginID, ALL_RELATION_IDs[i], arg.Attributes)!=ERR_OK)
		{
			ALL_RELATION_IDs [i] = NA;
		}
	}

// Проходимся по всем удовлетворяющим объектам и заполняем выходные аргументы
	for (N=0, j=0, i=0; i<ALL_RELATION_IDs.Size(); i++) if (ALL_RELATION_IDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) {j++; continue;} else j++; N++;

		oc_rel.Open (ALL_RELATION_IDs[i]);

		arg.objIDs				+= ALL_RELATION_IDs[i];
		arg.objVersions		+= oc_rel.m_Version;
		arg.objNames			+=	oc_rel.m_Name;
		arg.objSysNames		+=	oc_rel.m_SysName;
		arg.objDescriptions	+= oc_rel.m_Description;
	}

// Общее число объектов, которых можно перечислить
	arg.TotalStoredNum	=	N;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ СЕМАНТИЧЕСКОГО ОТНОШЕНИЯ											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_GetData (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_GetData);
/*............................................................................[]
		<objID						Идентификатор запрашиваемого объекта.
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь право чтения отношений [R].
		<Password					Пароль пользователя, запрашивающего операцию.

		>Name							Название отношения.
		>Version						Версия отношения.
		>SysName						Системное название отношения
		>Description				Описание отношения
		>FieldNames					Названия полей
		>FieldSysNames				Системные имена полей, строятся как переменные С++
		>FieldTypes					Типы полей ("object" "byte" "int" "bool" "time" "string" "float")
		>FieldDescriptions		Описания полей
		>FieldInterfaceTypes		Типы полей, интерпретируемые интерфейсом

		>FeodIDs						Зоны доступа, к которым принадлежит отношение		
		>AccessLevelThreshold	Пороговое значение уровня доступа пользователей к объекту.
		>ReadOnly					Имеет ли пользователь право редактировать объект

		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Relation[%u] не существует", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
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
	OC_User oc_login (loginID);
// Проверяем право доступа -- логин должен иметь право чтения во всех зонах доступа отношения
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа [R] на чтение отношения");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем аргументы полями объекта
	int	i;
	arg.Name						=	oc_rel.m_Name;
	arg.Version					=	oc_rel.m_Version;
	arg.Description			=	oc_rel.m_Description;
	arg.FieldNames				=	oc_rel.m_FieldName;
	arg.FieldSysNames			=	oc_rel.m_FieldSysName;
	arg.FieldTypes				=	oc_rel.m_FieldType;
	arg.FieldDescriptions	=	oc_rel.m_FieldDescription;
	arg.FieldInterfaceTypes	=	oc_rel.m_FieldInterfaceType;
	arg.ReadOnly				=	(USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W")!=ERR_OK);
	for (i=0; i<oc_rel.m_FeodGUID.Size(); i++) arg.FeodIDs += guid(oc_rel.m_FeodGUID[i]).id;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ СЕМАНТИЧЕСКОГО ОТНОШЕНИЯ											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_PutData (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_PutData);
/*............................................................................[]
		<objID						Идентификатор изменяемого объекта.
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь право записи [W].
		<Password					Пароль пользователя, запрашивающего операцию.

		<Name							Название отношения
		<SysName						Системное название отношения, строится как переменная С++
		<Description				Описание отношения
		<FieldNames					Названия полей
		<FieldSysNames				Системные имена полей, строятся как переменные С++
		<FieldDescriptions		Описания полей
		<FieldInterfaceTypes		Типы полей, интерпретируемые интерфейсом

		<FeodIDs						Зоны доступа, к которым принадлежит отношение
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей к объекту.

		>Version						Версия отношения.

		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Relation[%u] не существует", arg.objID);
	}
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_login (loginID);
// Проверяем право доступа -- логин должен иметь право записи во всех зонах доступа отношения
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа [W] на изменение отношения");
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
		ERR_RETURN_COMMENT (ERR_BadName, "Имя отношения не должно быть пустым");
	}
// Отношение должно иметь зону доступа
	if (arg.FeodIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Не указана зона доступа отношения");
	}
// Имя отношения должно быть уникальным
	OC_Relation oc_rel;
	oc_rel.SetIndex_Name ();
	if (oc_rel.Find (arg.Name) && oc_rel.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "Имя отношения должно быть уникальным");
	}
// Системное имя должно быть корректным
	if (!arg.SysName.CheckSysName())
	{
		SERVER_DEBUG_ERROR_1 ("Некорректное системное имя '%s'", arg.SysName.c_str());
	}
// Системное имя отношения должно быть уникальным
	oc_rel.SetIndex_SysName ();
	if (oc_rel.Find (arg.SysName) && oc_rel.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "Системное имя отношения должно быть уникальным");
	}
	oc_rel.Open (arg.objID);
//	Проверяем уровень доступа
	if (oc_rel.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа для изменения отношения");
	}
// Системные имена полей должны быть уникальными и корректными
	if (!RelationCheckFieldSystemNames (arg.FieldSysNames))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Все системные имена полей должны быть уникальными и строитьcя как переменные в С++!");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Пользователь не может убрать зоны доступа, к которым не имеет атрибута доступа [D]
	int i,j;
	for (i=0; i<oc_rel.m_FeodGUID.Size(); i++)
	{
		guid gi = oc_rel.m_FeodGUID[i];
		if (arg.FeodIDs.Find (gi.id)==-1)
		{
			if (USER_CHECK_ACCESS (loginID, gi.id, "D")!=ERR_OK)
			{
				string feodName;
				GetFeodName(gi.id, feodName);
				ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "Пользователь не имеет права удалять отношение из зоны доступа %s", feodName.c_str());
			}
		}
	}
// Пользователь не может назначить зоны доступа, к которым не имеет атрибута доступа [C]
	for (i=0; i<arg.FeodIDs.Size(); i++)
	{
		bool bFoundInRel = false;
	//	Ищем указанную зону в отношении
		for (j=0; j<oc_rel.m_FeodGUID.Size(); j++)
		{
			if (guid(oc_rel.m_FeodGUID[j]).id == arg.FeodIDs[i])
			{
				bFoundInRel = true;
				break;
			}
		}
	//	Если зона не найдена в отношении -- значии её добавили, проверяем право
		if (!bFoundInRel && USER_CHECK_ACCESS (loginID, arg.FeodIDs[i], "C")!=ERR_OK)
		{
			string feodName;
			GetFeodName (arg.FeodIDs[i], feodName);
			ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "Пользователь не имеет права вносить отношение в зону доступа %s", feodName.c_str());
		}
	}
// Преобразовываем зоны доступа в guid'ы
	int f;
	guid_arr FeodGUIDs;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		OC_Concept oc_feod;
		oc_feod.Open (arg.FeodIDs[f]);
		FeodGUIDs += oc_feod.GetObjectGUID ();
	}	
// Нельзя изменять размерность полей, для этого надо использовать функцию MOD_Relation_ChangeField
	if (oc_rel.m_FieldName.Size()!=arg.FieldNames.Size() || oc_rel.m_FieldSysName.Size()!=arg.FieldSysNames.Size() || oc_rel.m_FieldDescription.Size()!=arg.FieldDescriptions.Size() || oc_rel.m_FieldDescription.Size()!=arg.FieldInterfaceTypes.Size())
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Нельзя изменять размерность полей, для этого надо использовать функцию MOD_Relation_ChangeField");
	}
//----------------------------------------------------------------------------[] 



	
	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Изменяем поля объекта
	oc_rel.m_Name						=	arg.Name;
	oc_rel.m_Description				=	arg.Description;
	oc_rel.m_FieldName				=	arg.FieldNames;
	oc_rel.m_FieldSysName			=	arg.FieldSysNames;
	oc_rel.m_FieldDescription		=	arg.FieldDescriptions;
	oc_rel.m_FieldInterfaceType	=	arg.FieldInterfaceTypes;
	oc_rel.m_FeodGUID					=	FeodGUIDs;
	oc_rel.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// Изменяем версию отношения
	oc_rel.m_Version					+=	1;
	arg.Version							=	oc_rel.m_Version;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ПОЛЕЙ СЕМАНТИЧЕСКОГО ОТНОШЕНИЯ												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_ChangeField (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_ChangeField);
/*............................................................................[]
		<objID						Идентификатор изменяемого объекта.
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь право записи [W].
		<Password					Пароль пользователя, запрашивающего операцию.

		<ChangeType					0 - вставить новое поле, 1 - удалить поле, 2 - переместить поле, 3 - переименовать.
		<FieldID						Идентифиукатор (позиция) поля. Чтобы вставить в конец надо просто передать большое значение.
		<FieldPos					Куда поле перемещать. Используется для указания, куда перемещать поле.
		<FieldName					Новое имя поля или имя нового поля. Используется при вставки нового и переименовании старого поля.
		<FieldSysName				Новое системное имя поля или системное имя нового поля, строится как переменная С++. Используется при вставки нового и переименовании старого поля.
		<FieldDescription			Новое описание поля или описание нового поля. Используется при вставки нового и переименовании старого поля.
		<FieldInterfaceType		Тип поля, интерпретируемое интерфейсом

		>Version						Версия отношения.

		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Relation[%u] не существует", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_login (loginID);
// Проверяем право доступа -- логин должен иметь право записи во всех зонах доступа отношения
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа [W] на изменение отношения");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
//	Проверяем уровень доступа
	if (oc_rel.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа для изменения набора полей отношения");
	}
//----------------------------------------------------------------------------[] 


	
	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Изменяем поля объекта
	int oc_rel_m_FieldName_Size = oc_rel.m_FieldName.Size ();
	OC_Linkage oc_link;
	oc_link.SetIndex_RelationID();
	key_arr ka; ka+=arg.objID;
	switch (arg.ChangeType)
	{
	// Вставка нового поля
		case ChangeField_Insert:
		{
			if (arg.FieldID<0) ERR_RETURN_COMMENT_1 (ERR_BadArgument, "Некорректное значение аргумента FieldID = %d", arg.FieldID);
			if (!RelationCheckFieldSystemName	(arg.objID, arg.FieldSysName.c_str(), -1))	ERR_RETURN_COMMENT (ERR_BadArgument, "Все системные имена полей должны быть уникальными и строитьcя как переменные в С++!");
			oc_rel.m_FieldName.Insert				(arg.FieldID, arg.FieldName);
			oc_rel.m_FieldSysName.Insert			(arg.FieldID, arg.FieldSysName);
			oc_rel.m_FieldDescription.Insert		(arg.FieldID, arg.FieldDescription);
			oc_rel.m_FieldInterfaceType.Insert	(arg.FieldID, arg.FieldInterfaceType);

		// Проводим коррекцию связей
			for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
			{
			// У всех участвующих в связи объектов-прокси корректируем номер поля (позицию)
				for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
				{
					identifier link_id	= oc_link.GetObjectID ();
					identifier proxy_id	= identifier(oc_link.m_ProxyID[i]);

				// Если в связи используется не объект, а значение, или не указан объект, то ничего не делаем
					if (proxy_id==NA) continue;

					OC_LinkProxy oc_proxy (proxy_id);

				//	Находим редактируемую связь среди связей, в которых участвует объект-прокси
					for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
					{
					//	Если позиция больше чем номер вставляемого поля, увеличиваем её
						if (oc_proxy.m_RelationField[j] >= arg.FieldID)
						{
							oc_proxy.m_RelationField[j] += 1;
						}
					}
				}

			// Добавляем во все связи пустые объекты на место добавленного поля
				oc_link.m_ProxyID.Insert (arg.FieldID, NA);

			// Проверка -- число связанных объектов должно быть равно числу полей в отношении
				if (oc_link.m_ProxyID.Size () != oc_rel_m_FieldName_Size) SERVER_DEBUG_ERROR_2 ("oc_link.m_ProxyID.Size () != oc_rel.m_FieldName.Size ()   ---  %d!=%d", oc_link.m_ProxyID.Size (), oc_rel.m_FieldName.Size ());
			}
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// Удаление поля
		case ChangeField_Delete:
		{
		// Проверка номера поля
			if (arg.FieldID<0 || arg.FieldID>= oc_rel.m_FieldName.Size())	ERR_RETURN_COMMENT_1 (ERR_BadArgument, "Некорректное значение аргумента FieldID = %d", arg.FieldID);
		// В отношении должно быть не менее 1-го поля
			if (oc_rel.m_FieldName.Size()<=1)										ERR_RETURN_COMMENT   (ERR_BadArgument, "В отношении должно быть не менее 1-го поля");
		// В отношении должен участвовать хотя бы один объект
			int nObjField=0; for (int f=0; f<oc_rel.m_FieldType.Size(); f++) if (f!=arg.FieldID) if (oc_rel.m_FieldType[f]=="object") nObjField++;
			if (nObjField<=0)																ERR_RETURN_COMMENT   (ERR_BadArgument, "В отношении должен участвовать хотя бы один объект");

			oc_rel.m_FieldName.Del				(arg.FieldID);
			oc_rel.m_FieldSysName.Del			(arg.FieldID);
			oc_rel.m_FieldDescription.Del		(arg.FieldID);
			oc_rel.m_FieldInterfaceType.Del	(arg.FieldID);
		// Проводим коррекцию связей
			for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
			{
			// У всех участвующих в связи объектов-прокси корректируем номер поля (позицию)
				for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
				{
					identifier link_id	= oc_link.GetObjectID ();
					identifier proxy_id	= identifier(oc_link.m_ProxyID[i]);

				// Если в связи используется не объект, а значение, или не указан объект, то ничего не делаем
					if (proxy_id==NA) continue;

					OC_LinkProxy oc_proxy (proxy_id);
				//	Находим редактируемую связь среди связей, в которых участвует объект-прокси
					for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
					{
					//	Если позиция совпадает с выкидываемым полем, удаляем факт связи
						if (oc_proxy.m_RelationField[j] == arg.FieldID)
						{
							oc_proxy.m_LinkageID.Del		(j);
							oc_proxy.m_RelationID.Del		(j);
							oc_proxy.m_RelationField.Del	(j);
							j --;
						}
					//	Если позиция больше чем номер удаляемого поля, уменьшаем её
						if (oc_proxy.m_RelationField[j] > arg.FieldID)
						{
							oc_proxy.m_RelationField[j] -= 1;
						}
					}
				}

			//	Выкидываем связанный объект, находящийся на позиции удаляемого из отношении поля
				oc_link.m_ProxyID.Del (arg.FieldID);

			// Проверка -- число связанных объектов должно быть равно числу полей в отношении
				if (oc_link.m_ProxyID.Size () != oc_rel_m_FieldName_Size) SERVER_DEBUG_ERROR_2 ("oc_link.m_ProxyID.Size () != oc_rel.m_FieldName.Size ()   ---  %d!=%d", oc_link.m_ProxyID.Size (), oc_rel.m_FieldName.Size ());
			}
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// Переименование поля
		case ChangeField_Rename:
		{
			if (arg.FieldID<0 || arg.FieldID>= oc_rel.m_FieldName.Size())									ERR_RETURN_COMMENT_1 (ERR_BadArgument, "Некорректное значение аргумента FieldID = %d", arg.FieldID);
			if (!RelationCheckFieldSystemName (arg.objID, arg.FieldSysName.c_str(), arg.FieldID))	ERR_RETURN_COMMENT   (ERR_BadArgument, "Все системные имена полей должны быть уникальными и строитьcя как переменные в С++!");
			oc_rel.m_FieldName			[arg.FieldID]	=	arg.FieldName;
			oc_rel.m_FieldSysName		[arg.FieldID]	=	arg.FieldSysName;
			oc_rel.m_FieldDescription	[arg.FieldID]	=	arg.FieldDescription;
			oc_rel.m_FieldInterfaceType[arg.FieldID]	=	arg.FieldInterfaceType;
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// Перемещение поля
		case ChangeField_Move:
			ERR_RETURN_COMMENT (ERR_FunctionNotImplemented, "Перемещение полей пока не реализовано");
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	//	Ошибка
		default:
			ERR_RETURN_COMMENT_1 (ERR_BadArgument, "Указан неверный тип операции над полями [%d], допустимые типы: 0 - вставить новое поле, 1 - удалить поле, 2 - переместить поле, 3 - переименовать поле.", arg.ChangeType);
		break;
	}

// Изменяем версию отношения
	oc_rel.m_Version	+=	1;
	arg.Version			=	oc_rel.m_Version;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ СЕМАНТИЧЕСКОГО ОТНОШЕНИЯ														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_Delete (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_Delete);
/*............................................................................[]
		<objID					Идентификатор удаляемого отношения.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен иметь право удаления [D] отношения во всех зонах доступа.
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
	if (!OC_Exist (OBJ_CLASS_ID_Relation, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Relation[%u] не существует", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа -- пользователь должен иметь право удалять отношения во всех его зонах доступа
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, oc_rel.GetObjectID(), "D");
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
// Корректируем базу данных
	OC_Linkage oc_link;
	oc_link.SetIndex_RelationID();
	key_arr ka; ka+=arg.objID;

// Удаляем все связи указанного отношения и все записи о нём в прокси-объектах
	for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
	{
	// Проходимся по всем участвующим в связи объектам-прокси
		for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
		{
			identifier link_id = oc_link.GetObjectID ();
			OC_LinkProxy oc_proxy (identifier(oc_link.m_ProxyID[i]));
		//	Находим удаляемую связь среди связей, в которых участвует объект-прокси
			for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
			{
				if (oc_proxy.m_LinkageID[j] == link_id)
				{
					oc_proxy.m_LinkageID.Del		(j);
					oc_proxy.m_RelationID.Del		(j);
					oc_proxy.m_RelationField.Del	(j);
					j --;
				}
			}
		}
	//	Удаляем связь
		oc_link.Delete ();
	}

// Уничтожаем отношение
	oc_rel.Delete ();
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