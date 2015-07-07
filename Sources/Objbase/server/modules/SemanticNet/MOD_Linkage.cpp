/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Linkage.cpp															[]
[] Date:          18.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с семантическими связями										[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Linkage.inc.h"






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОЙ СЕМАНТИЧЕСКОЙ СВЯЗИ														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_New (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_New);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права чтения [R] во всех феодах соответствующего отношения.
		<Password					Пароль пользователя, запрашивающего операцию.

		<RelationID					Идентификатор отношения, на основе которого строится связь.
		<RelationVersion			Версия отношения (если -1, то игнорируется).
		<ProxyIDs					Поля-объекты: идентификаторы связываемых прокси-объектов. К ним должен быть доступ [W].
		<Values						Поля-значения (строки)
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Объект должен иметь более слабый порог, чем уровень её создателя, чтобы тот мог её править/удалять.
		>objID						Идентификатор созданной связи.
		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Отношение должно существовать
	if (!CHECK_RELATION_ID (arg.RelationID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указанный объект Relation[%u] не существует", arg.RelationID);
	}
	OC_Relation oc_rel (arg.RelationID);
// Проверка версии отношения
	if (arg.RelationVersion!=-1 && arg.RelationVersion!=oc_rel.m_Version)
	{
		ERR_RETURN_COMMENT_3 (ERR_RelationVersionMismatch, "Несовпадение версий отношения %s -- %d!=%d", string(oc_rel.m_Name).c_str(), arg.RelationVersion, int (oc_rel.m_Version));
	}
// Прокси-объекты должны существовать
	int iProxy=0;
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.ProxyIDs[iProxy]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadID, "Указан несуществующий объект LinkProxy[%u] в аругменте %d", arg.ProxyIDs[iProxy], iProxy);
		}
	}
// Проверяем число переданных аргументов
	int nRelFields = oc_rel.m_FieldType.Size();
	if (arg.ProxyIDs.Size()!=nRelFields) 	ERR_RETURN_COMMENT_3 (ERR_BadArgument, "При создании связи '%s' должно быть передано %d аргументов-объектов (ProxyIDs), а не %d",	string(oc_rel.m_Name).c_str(), nRelFields, arg.ProxyIDs.Size());
	if (arg.Values	 .Size()!=nRelFields) 	ERR_RETURN_COMMENT_3 (ERR_BadArgument, "При создании связи '%s' должно быть передано %d аргументов-значений (Values), а не %d",		string(oc_rel.m_Name).c_str(), nRelFields, arg.Values.Size  ());
// Проверяем правильность заполнения поля (поля-значения не могут содержать объектов)
	int f=0;
	for (f=0; f<oc_rel.m_FieldType.Size(); f++) 
	{
		if (arg.ProxyIDs[f]!=NA && oc_rel.m_FieldType[f]!="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "Значением поля %s[%s] не может быть объект [%u]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.ProxyIDs[f]);
		if (!arg.Values[f].IsEmpty() && oc_rel.m_FieldType[f]=="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "Значением поля %s[%s] не может быть строка [%s]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.Values[f].c_str());
	}
// В связи должен участвовать хотя-бы один объект
	int nObj=0;
	for (f=0; f<oc_rel.m_FieldType.Size(); f++) nObj += oc_rel.m_FieldType[f]=="object" && arg.ProxyIDs[f]!=NA;
	if (nObj==0) ERR_RETURN_COMMENT_1 (ERR_BadArgument, "В связи %s должен участвовать хотя-бы один объект", string(oc_rel.m_Name).c_str());
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
// Проверяем право доступа -- пользователь должен иметь право чтения отношений
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.RelationID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
	}
// Пользователь должен иметь право изменять объекты-аргументы
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "Пользователь не имеет права редактировать (включать в связь) объект '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём объект
	OC_Linkage oc_link;
	oc_link.New ();
	identifier linkID = oc_link.GetObjectID ();

	oc_link.m_RelationID					=	arg.RelationID;
	oc_link.m_ProxyID						=	arg.ProxyIDs;
	oc_link.m_Value						=	arg.Values;
	oc_link.m_OwnerGUID					=	oc_login.GetObjectGUID ();
	oc_link.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// Запоминаем идентификатор
	arg.objID								=	linkID;

//	Заносим связь во все прокси-объекты
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		oc_proxy.m_RelationID		+=	arg.RelationID;
		oc_proxy.m_LinkageID			+=	linkID;
		oc_proxy.m_RelationField	+=	iProxy;
	}

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ДОСТУПНЫХ СЕМАНТИЧЕСКИХ СВЯЗЕЙ											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_Enumerate (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права получения списка [L] во всех феодах соответствующего отношения или [LR], если bNeedFields.
		<Password					Пароль пользователя, запрашивающего операцию.

		<objID						Идентификатор объекта-прокси, чьи связи запрашиваются. Если NA -- все связи. К парному реальному объекту должен быть доступ [R].
		<UseRelationID				Если false (по умолчаанию), то выводятся все связи, иначе только те, которые имеют тип RelatonID.
		<RelationID					Учитывается только если UseRelationID==true. Идентификатор отношения (типа связи). Выводятся только связи, реализующие указанное отношение. К отношениию должен быть доступ [L].
		<bNeedFields				Возвращать ли массив со значениями указанных полей. (По-умолчанию false). Если указано, то требуется право [R].
		<FieldIndices				Значения каких полей связей возвращать (используется при bNeedFields).
		<RelationSysName			Учитывается только если UseRelationID==true и если не указан RelationID.
		<objFirstNo					Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.
		<objLastNo					Номер объекта, до которого включительно выводятся объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

		>objIDs						Массив идентификаторов связей, в которых участвует объект. Исключаются те связи, которые содержат объекты, к котороым нет доступа [R].
		>objFieldsValues			Значения указанных полей в виде строк. Упаковано последовательно -- сначала все поля i-й, потом i+1-й связи. Пустой массив если bNeedFields==false. Если пользователь не имеет право чтения связи, возвращается строка "{{ACCESS DENY}}".
		>objRelationIDs			Массив идентификаторов соответствующих отношений.

		>TotalStoredNum			Сколько всего связей может быть перечислено в данных условиях.
		>MaxNumInQuery				Максимально допустимое число запрашиваемых за один раз объектов.

		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект-прокси должен существовать
	if (arg.objID!=NA && !OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указанный объект LinkProxy[%u] не существует", arg.objID);	
	}
	OC_LinkProxy oc_proxy;
	if (arg.objID!=NA) oc_proxy.Open (arg.objID);

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_login (loginID);
// Проверка доступа на чтение данных у реального объекта
	if (arg.objID!=NA && !MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "R"))
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "Нет доступа к связанным объектам");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_LINKAGE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_LINKAGE_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "Запрошено %d связей, а максимально можно запросить %d", (arg.objLastNo - arg.objFirstNo), MAX_LINKAGE_ENUMERATE_NUM);
	}
// Если использовать фильтр по отношению, то проверить существование.
	if (arg.UseRelationID)
	{
		if (arg.RelationID==NA)
		{
			arg.RelationID = GetRelationIDBySysName (arg.RelationSysName);
			if (arg.RelationID==NA)
			{
				ERR_RETURN_COMMENT_1 (ERR_BadName, "Указанный объект Relation[%s] не существует", arg.RelationSysName.c_str());
			}
		}
		if (!OC_Exist (OBJ_CLASS_ID_Relation, arg.RelationID))
		{
			ERR_RETURN_COMMENT_1 (ERR_BadID, "Указанный объект Relation[%u] не существует", arg.RelationID);
		}
	}
	OC_Relation oc_rel; if (arg.UseRelationID) oc_rel.Open (arg.RelationID);

// Если указаны поля, то надо указать отношение
	if (arg.bNeedFields && arg.RelationID==NA)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Если указываются поля (arg.bNeedFields), то надо указать отношение (arg.RelationID)");
	}
// Если указаны поля, то надо проверить их валидность
	int f;
	int oc_rel_m_FieldType_Size = arg.UseRelationID? oc_rel.m_FieldType.Size() : 0;
	if (arg.bNeedFields) for (f=0; f<arg.FieldIndices.Size(); f++) if (arg.FieldIndices[f]<0 || arg.FieldIndices[f]>=oc_rel_m_FieldType_Size)
	{
		ERR_RETURN_COMMENT_3 (ERR_BadArgument, "Некорректный индекс поля %d в отношении '%s' -- максимально допустимый индекс поля -- %d", arg.FieldIndices[f], string(oc_rel.m_Name).c_str(), oc_rel_m_FieldType_Size);
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Получаем список всех связей объекта
	int						i,j,l,N;
	identifier_arr			ALL_LINKAGE_IDs;
	OC_Linkage				oc_link;

// Если указан объект -- все его связи	
	if (arg.objID!=NA) 
	{
		ALL_LINKAGE_IDs = oc_proxy.m_LinkageID;
	}
// Если объект не указан -- все связи указанго отношения
	else if (arg.UseRelationID)
	{
		oc_link.SetIndex_RelationID();
		key_arr ka;
		ka += arg.RelationID;
		oc_link.GetClassIdList (ALL_LINKAGE_IDs, &ka);
	}
// Если не указан ни объект, ни отношение -- ошибка
	else
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Надо указать либо объект, либо тип связей (отношения), а лучше и то и другое");
	}

// Оставляем только связи, реализующие указанное отношение
	if (arg.UseRelationID)
	{
		for (l=0; l<ALL_LINKAGE_IDs.Size(); l++)
		{
			oc_link.Open (ALL_LINKAGE_IDs[l]);
			if (oc_link.m_RelationID != arg.RelationID)
			{
				ALL_LINKAGE_IDs[l] = NA;
			}
		}
	}

// Выкидываем те связи, к которым нет доступа на чтение (например, связывающие недоступные объекты)
	for (l=0; l<ALL_LINKAGE_IDs.Size(); l++) if (ALL_LINKAGE_IDs[l]!=NA)
	{
		ERR_RESULT res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, ALL_LINKAGE_IDs[l], (arg.bNeedFields? "LR": "L"));
		if (res!=ERR_OK)
		{
			ALL_LINKAGE_IDs[l] = NA;
		}
	}

// Проходимся по всем удовлетворяющим объектам и заполняем выходные аргументы
	for (N=0, j=0, i=0; i<ALL_LINKAGE_IDs.Size(); i++) if (ALL_LINKAGE_IDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) {j++; continue;} else j++; N++;

		oc_link.Open (ALL_LINKAGE_IDs[i]);

		arg.objIDs				+= ALL_LINKAGE_IDs[i];
		arg.objRelationIDs	+=	oc_link.m_RelationID;
		if (arg.bNeedFields) for (f=0; f<arg.FieldIndices.Size(); f++)
		{
			if (oc_rel.m_FieldType[arg.FieldIndices[f]]=="object")
			{
				static string strFieldValue;
				strFieldValue.Format ("%u", identifier (oc_link.m_ProxyID[arg.FieldIndices[f]]));
				arg.objFieldsValues	+=	strFieldValue;
			}
			else
			{
				arg.objFieldsValues	+=	oc_link.m_Value[arg.FieldIndices[f]];
			}
		}
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
//` ПОЛУЧЕНИЕ ДАННЫХ СЕМАНТИЧЕСКОЙ СВЯЗИ													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_GetData (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_GetData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь право чтения [R].
		<Password					Пароль пользователя, запрашивающего операцию.

		<objID						Идентификатор запрашиваемой связи.

		>FieldTypes					Типы полей ("object" "byte" "int" "bool" "time" "string" "float")
		>FieldValues				Строковые значения полей, если тип не "object"
		>FieldObjectProxyIDs		Идентификаторы прокси-объектов, если тип="object". NA если поле пусто.
		>FieldObjectClasses		Классы реальных объектов-полей, если тип поля="object". Пустая строка если поле пусто.
		>FieldObjectIDs			Идентификаторы реальных объектов-полей, если тип поля="object". NA если поле пусто.
		>FieldObjectNames			Имена реальных объектов-полей, если тип поля="object". Если база не может узнать имя объекта, возвращается "{{UNKNOWN NAME}}". "{{NA}}" если поле пусто.

		>AccessLevelThreshold	Пороговое значение уровня доступа пользователей.
		>ReadOnly					Имеет ли пользователь право редактировать объект

		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!CHECK_LINKAGE_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Linkage[%u] не существует", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
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
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа [R] на чтение связи (отношения или одного из объектов)");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем аргументы полями объекта
	OC_Relation oc_rel (identifier (oc_link.m_RelationID));

	arg.FieldTypes				=	oc_rel.m_FieldType;
	for (int f=0; f<arg.FieldTypes.Size(); f++)
	{
		if (arg.FieldTypes[f] == "object")
		{
			arg.FieldValues += "";
			if (OC_Exist (OBJ_CLASS_ID_LinkProxy, identifier(oc_link.m_ProxyID [f])))
			{
				arg.FieldObjectProxyIDs += oc_link.m_ProxyID [f];
				OC_LinkProxy oc_proxy (identifier(oc_link.m_ProxyID [f]));

				identifier classID = guid(oc_proxy.m_RealObject).cl;
				string StrClassName = classID<1024? className[classID] : "";

				guid gi = oc_proxy.m_RealObject;
				arg.FieldObjectClasses	+= StrClassName;
				arg.FieldObjectIDs		+= gi.id;
				arg.FieldObjectNames		+= MOD_GET_OBJECT_NAME (gi);
			}
			else
			{
				arg.FieldObjectProxyIDs += NA;
				arg.FieldObjectClasses	+= "";
				arg.FieldObjectIDs		+= NA;
				arg.FieldObjectNames		+= "{{NA}}";
			}
		}
		else
		{
			arg.FieldValues			+= oc_link.m_Value[f];
			arg.FieldObjectProxyIDs += NA;
			arg.FieldObjectClasses	+= "";
			arg.FieldObjectIDs		+= NA;
			arg.FieldObjectNames		+= "-";
		}
	}

	arg.ReadOnly					=	(USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "W")!=ERR_OK);
	arg.AccessLevelThreshold	=	oc_link.m_AccessLevelThreshold;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ СЕМАНТИЧЕСКОЙ СВЯЗИ													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_PutData (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_PutData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь право записи [W].
		<Password					Пароль пользователя, запрашивающего операцию.

		<objID						Идентификатор связи.
		<RelationVersion			Версия отношения (если -1, то игнорируется).
		<ProxyIDs					Идентификаторы связываемых прокси-объектов. К ним должен быть доступ [W].
		<Values						Поля-значения (строки)

		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!CHECK_LINKAGE_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Linkage[%u] не существует", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_login (loginID);
// Проверяем право доступа -- логин должен иметь право записи во всех зонах доступа отношения
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа [W] на изменение отношения");
	}
// Пользователь должен иметь право изменять объекты-аргументы
	int iProxy=0;
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "Пользователь не имеет права редактировать (включать в связь) объект '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//	Проверяем уровень доступа
	if (oc_link.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа для изменения отношения");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Отношение должно существовать
	if (!CHECK_RELATION_ID (oc_link.m_RelationID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указанный объект Relation[%u] не существует", arg.RelationID);
	}
	OC_Relation oc_rel (oc_link.m_RelationID);
// Проверка версии отношения
	if (arg.RelationVersion!=-1 && arg.RelationVersion!=oc_rel.m_Version)
	{
		ERR_RETURN_COMMENT_3 (ERR_RelationVersionMismatch, "Несовпадение версий отношения %s -- %d!=%d", string(oc_rel.m_Name).c_str(), arg.RelationVersion, int (oc_rel.m_Version));
	}
// Прокси-объекты должны существовать
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.ProxyIDs[iProxy]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadID, "Указан несуществующий объект LinkProxy[%u] в аргугменте %d", arg.ProxyIDs[iProxy], iProxy);
		}
	}
// Проверяем число переданных аргументов
	int nRelFields = oc_rel.m_FieldType.Size();
	if (arg.ProxyIDs.Size()!=nRelFields) 	ERR_RETURN_COMMENT_4 (ERR_BadArgument, "При редактировании связи %s[ID=%u] должно быть передано %d аргументов-объектов (ProxyIDs), а не %d", string(oc_rel.m_Name).c_str(), arg.objID, nRelFields, arg.ProxyIDs.Size());
	if (arg.Values	 .Size()!=nRelFields) 	ERR_RETURN_COMMENT_4 (ERR_BadArgument, "При редактировании связи %s[ID=%u] должно быть передано %d аргументов-значений (Values), а не %d",	string(oc_rel.m_Name).c_str(), arg.objID, nRelFields, arg.Values.Size  ());

// Проверяем правильность заполнения поля (поля-значения не могут содержать объектов)
	int f=0;
	for (f=0; f<nRelFields; f++) 
	{
		if (arg.ProxyIDs[f]!=NA && oc_rel.m_FieldType[f]!="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "Значением поля %s[%s] не может быть объект [%u]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.ProxyIDs[f]);
		if (!arg.Values[f].IsEmpty() && oc_rel.m_FieldType[f]=="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "Значением поля %s[%s] не может быть строка [%s]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.Values[f].c_str());
	}
// В связи должен участвовать хотя-бы один объект
	int nObj=0;
	for (f=0; f<nRelFields; f++) nObj += oc_rel.m_FieldType[f]=="object" && arg.ProxyIDs[f]!=NA;
	if (nObj==0) ERR_RETURN_COMMENT_2 (ERR_BadArgument, "В связи %s[ID=%u] должен участвовать хотя-бы один объект", string(oc_rel.m_Name).c_str(), arg.objID);
//----------------------------------------------------------------------------[] 





	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Изменяем у связи поля-значения
	oc_link.m_Value = arg.Values;

// Изменяем у связи поля-объекты
	for (f=0; f<nRelFields; f++) if (oc_rel.m_FieldType[f]=="object")
	{
		identifier oldProxyID = oc_link.m_ProxyID[f];
		identifier newProxyID = arg.ProxyIDs[f];
		if (oldProxyID != newProxyID)
		{
		// Если изменяется аргумент-объект -- надо у старого корректно оборвать связи
			if (oldProxyID!=NA)
			{
				OC_LinkProxy oc_proxy (oldProxyID);
				int index = oc_proxy.m_LinkageID.Find (arg.objID);
				if (index!=-1)
				{
					oc_proxy.m_LinkageID		.Del (index);
					oc_proxy.m_RelationField.Del (index);
					oc_proxy.m_RelationID	.Del (index);
				}
				else SERVER_DEBUG_ERROR_4 ("Связь %u (%s[%s]) не найдена у прокси-объекта %u", arg.objID, string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), oldProxyID);
			}
		// Прописывем у нового объекта связи
			if (newProxyID!=NA)
			{
				OC_LinkProxy oc_proxy (newProxyID);
				oc_proxy.m_LinkageID			+=	arg.objID;
				oc_proxy.m_RelationID		+=	oc_link.m_RelationID;
				oc_proxy.m_RelationField	+=	f;
			}		
		// Изменяем саму связь
			oc_link.m_ProxyID[f] = newProxyID;
		}
	}
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]




















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ СЕМАНТИЧЕСКОЙ СВЯЗИ																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_Delete (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_Delete);
/*............................................................................[]
Удаление семантической связи. Должен быть доступ [D] к отношению и [W] ко всем объекта-участникам.
		<Login						Логин пользователя, запрашивающего операцию.
		<Password					Пароль пользователя, запрашивающего операцию.

		<objID						Идентификатор связи.
		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_Linkage, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Linkage[%u] не существует", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
// Проверяем право доступа -- пользователь должен иметь право удалять отношения во всех его зонах доступа
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, oc_link.GetObjectID(), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Нет доступа для выполнения операции");
	}
// Пользователь должен иметь право изменять объекты-аргументы
	int iProxy=0;
	for (iProxy=0; iProxy<oc_link.m_ProxyID.Size(); iProxy++) if (oc_link.m_ProxyID[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (oc_link.m_ProxyID[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "Пользователь не имеет права редактировать (исключать из связи) объект '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Удаляем упоминание о связи у всех объектов-участников
	for (int i=0; i<oc_link.m_ProxyID.Size(); i++) if (oc_link.m_ProxyID[i]!=NA)
	{
		OC_Relation oc_rel (oc_link.m_RelationID);
		if (OC_Exist (OBJ_CLASS_ID_LinkProxy, oc_link.m_ProxyID[i]))
		{
			OC_LinkProxy oc_proxy (oc_link.m_ProxyID[i]);
			int index = oc_proxy.m_LinkageID.Find (arg.objID);
			int Pos = oc_proxy.m_RelationField[index];

			if (index!=-1)
			{
				oc_proxy.m_LinkageID		.Del (index);
				oc_proxy.m_RelationField.Del (index);
				oc_proxy.m_RelationID	.Del (index);
			}
			else SERVER_DEBUG_ERROR_3 ("Удаляеммая связь %u (%s) не найдена у прокси-объекта %u", arg.objID, string(oc_rel.m_Name).c_str(), identifier (oc_link.m_ProxyID[i]));

			if (Pos!=i)
			{
				SERVER_DEBUG_ERROR_5 ("Удаляеммая связь %u (%s) найдена у прокси-объекта %u в другой позиции поля (%d вместо %d)", arg.objID, string(oc_rel.m_Name).c_str(), identifier (oc_link.m_ProxyID[i]), index, Pos);
			}
		}
		else SERVER_DEBUG_ERROR_4 ("В удаляемой связи %u (%s) в аргументе %d обнаружена ссылка %u на несуществующий объект.", arg.objID, string(oc_rel.m_Name).c_str(), i, identifier (oc_link.m_ProxyID[i]));
	}
	

// Уничтожаем связь
	oc_link.Delete ();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ РЕАЛЬНОГО ОБЪЕКТА ПО ЕГО ПРОКСИ											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_GetRealObjectByProxyID (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_GetRealObjectByProxyID);
/*............................................................................[]
		<objID						Прокси объект.

		>RealObjectClassName		Класс реального объекта
		>RealObjectID				Идентификатор реального объекта
		>RealObjectName			Имя реального объекта

		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Прокси-объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан несуществующий объект LinkProxy[%u]", arg.objID);
	}
	OC_LinkProxy oc_proxy (arg.objID);
//----------------------------------------------------------------------------[] 
// Реальный объект должен существовать
	if (!OC_Exist (oc_proxy.m_RealObject))
	{
		guid gi = oc_proxy.m_RealObject;
		ERR_RETURN_COMMENT_4 (ERR_BadID, "Прокси объект LinkProxy[%u] ссылается на несуществующий объект [%u:%u:%u]", arg.objID, gi.cl, gi.id, gi.rn);
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	identifier classID = guid(oc_proxy.m_RealObject).cl;
	guid gi = oc_proxy.m_RealObject;
	arg.RealObjectClassName	= className[classID];
	arg.RealObjectID			= gi.id;
	arg.RealObjectName		= MOD_GET_OBJECT_NAME (gi);
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