/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Feod.cpp																[]
[] Date:          07.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с зонами доступа, концептами ветви {Concept.Feod})	[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Feod.inc.h"





//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ФЕОДА																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_New (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_New);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами создания зон доступа.
		<Password					Пароль пользователя, запрашивающего операцию.
		<Name							Имя создаваемой зоны. Если передано пустое или неуникальное имя, то система сама придумывает/изменяет название зоны доступа.
		<Type							Тип создаваемой зоны. Если не указан, равен имени.
		<Description				Описание создаваемой зоны.
		<ParentID					Зона верхнего уровня. Пользователь должен иметь право создавать дочернии зоны доступа в указанной зоне (обладать правом на эту зону с атрибутом [M]).
		<ParentName					Имя зоны верхнего уровня. Используется, когда не указан ParentID.
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Зона должна иметь более слабый порог, чем уровень её создателя, чтобы тот мог её править/удалять.

		>objID						Идентификатор созданной зоны.
		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если не указан ParentID, берём его по ParentName
	if (arg.ParentID==NA) 
	{
		arg.ParentID = GetFeodIDByType (arg.ParentName);
	}

// Объект должен существовать
	if (!CHECK_FEOD_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_2 (ERR_BadID, "Передан некорректный идентификатор [%u] или имя '%s' родительской зоны доступа.", arg.ParentID, arg.ParentName.c_str());
	}
	OC_Feod oc_parent_feod (arg.ParentID);

// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Feod", "C", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не обладает правами создания зон доступа");
	}
// Проверяем возможность манипулирования с зоной доступа ParentID
	res = USER_CHECK_ACCESS (loginID, arg.ParentID, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права манипулировать (атрибут [M] или [m]) внутри указанной зоны доступа.");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Зона должна иметь более слабый порог, чем уровень её создателя, 
// чтобы тот мог её править/удалять.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
	}
// Если тип не указан, использеум имя.
	if (arg.Type.IsEmpty())
	{
		arg.Type = arg.Name;
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если передано пустое имя -- придумываем своё.
	if (arg.Name.IsEmpty())
	{
		arg.Name.Format ("%s feod", arg.Login.c_str());
	}

// Имя зоны должно быть уникальным.
	string OriginalName	= arg.Name;
	string OriginalType	= arg.Type;
	string parentFeodType;
	string newFeodType;
	GetFeodType (arg.ParentID, parentFeodType);
	newFeodType.Format ("%s.%s", parentFeodType.c_str(), OriginalType.c_str());
	if (GetFeodIDByType(newFeodType)!=NA)
	{
		for (int r=4; r<80; r++)
		{
			string rnd;
			rnd.Randomize (r, "ABCDEF0123456789");
			string newName;
			newFeodType.Format ("%s.%s [%s]", parentFeodType.c_str(), OriginalType.c_str(), rnd.c_str());
			if (GetFeodIDByType (newFeodType)==NA)
			{
				break;
			}
		}
		if (GetFeodIDByType(newFeodType)!=NA)
		{
			ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "Не удалось сгенерировать уникальное имя для зоны доступа");
		}
	}

// Создаём феод как концепт
	MOD_Concept_Args concept_arg;
	concept_arg.ParentID				= arg.ParentID;
	concept_arg.Name					= OriginalName;
	concept_arg.Description			= arg.Description;
	concept_arg.Type					= newFeodType;
	concept_arg.TypeNo				= ConceptGetUnicTypeNo ();
	GetPicklockPassword (concept_arg.PicklockPassword);
	res = MOD_Concept_New (concept_arg);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_2 (res, "Не удалось создать феод '%s {%s}' как концепт", OriginalName.c_str(), newFeodType.c_str());
	}
	identifier feodID = concept_arg.objID;
	OC_Feod oc_feod (feodID);

// Устанавливаем порог доступа к зоне, пользователи с таким же или более 
// слабым доступом не смогут удалять/редактировать зону.
	SET_EXT_FIELD (oc_feod, AccessLevelThreshold, arg.AccessLevelThreshold);

// Запоминаем идентификатор владельца зоны.
	SET_EXT_FIELD (oc_feod, OwnerID, loginID);

// Запоминаем созданную зону в списке собственных зон пользователя, чтобы он мог ею распоряжаться.
	oc_login.m_OwnFeodID += feodID;

// Добаляем созданную зону в рутовую группу доступа, при импорте не надо.
	identifier rootGroupID = arg.Login=="{{IMPORT}}" ? NA : GetGroupIDByType ("root");
	if (rootGroupID != NA)
	{
		OC_UserGroup oc_root_group (rootGroupID);
		oc_root_group.m_Rights_Feod	+= feodID;
		oc_root_group.m_Rights_Attr	+= ALL_ATTRIBUTES;
	//	Упрощаем набор прав рутовой группы
		UserGroupSimplifyRightsSet	(rootGroupID);
	}
	arg.objID = feodID;
//----------------------------------------------------------------------------[] 



	
	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ДОСТУПНЫХ ЗОН ДОСТУПА														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_Enumerate (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен иметь права получения списка [L].
		<Password					Пароль пользователя, запрашивающего операцию.
		<ParentID					Идентификатор феода, потомков которого перечислить.
		<ParentName					Используется, если ParentID == NA.

		>objIDs						Идентификаторы феодов, включая родительский (objID)
		>objNames					Названия феодов
		>objTypes					Типы феодов, полный путь от корня ("Feod.Concept.Data")
		>objDescriptions			Описания феодов
		>objParentIDs				Идентификаторы родительских феодов или NA для корня
		>objThresholds 			Уровни доступа
		>objExtClassNames			Названия классов-расширений над соответствующими феодами
		>objExtIDs					Идентификаторы объектов-расширений над соответствующими феодами

		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny).
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

		arg.ParentID = GetFeodIDByType (arg.ParentName);
		if (arg.ParentID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("Не найден родительский феод '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "Не найден родительский феод '%s'", arg.ParentName.c_str());
		}
	}
// Родительский феод должен существовать
	if (!CHECK_FEOD_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный родительский феод ID=%u", arg.ParentID);
	}
	identifier feodID  = arg.ParentID;
	OC_Feod oc_feod (feodID);
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
// проверяем доступ
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет прав перечисления зон доступа Concept.Feod.Admin.Feod[L]");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[] 


	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Получаем список всех зон доступа
	int				f;
	int MAX_CLASS_NUM = 1024; // !!! Запрашивать в ядре.
	identifier_arr FeodArr;
	GetFeodDescendantIDs (feodID, FeodArr);
	FeodArr.Insert (0, feodID);
	
// Выкидываем те зоны доступа, которые не могут быть просмотрены
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], "L")!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// Проходимся по всем запрошенным объектам и заполняем выходные аргументы
	for (f=0; f<FeodArr.Size(); f++)
	{
		OC_Concept oc_feod (FeodArr[f]);

		int AccessLevel = SYSTEM_ACCESS_LEVEL;
		GET_EXT_FIELD (oc_feod, AccessLevelThreshold, AccessLevel);
		guid gi = guid(oc_feod.m_MOD_Extension_GUID);
		const char * ExtClassName = (gi.cl>=0 && gi.cl<(identifier)MAX_CLASS_NUM)? className [gi.cl]: "";

		arg.objIDs				+=	FeodArr[f];
		arg.objNames			+=	oc_feod.m_Name;
		arg.objTypes			+=	oc_feod.m_Type;
		arg.objDescriptions	+=	oc_feod.m_Description;
		arg.objParentIDs		+=	oc_feod.m_Parent;
		arg.objThresholds 	+=	AccessLevel;
		arg.objExtClassNames	+=	ExtClassName;
		arg.objExtIDs			+=	gi.id;
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ ЗОНЫ ДОСТУПА																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_Delete (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_Delete);
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
	identifier	feod_id = arg.objID;
	if (!CHECK_FEOD_ID (feod_id))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект Feod[%u] не существует", feod_id);
	}
	OC_Feod	   oc_feod (feod_id);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	OC_User oc_user;
	oc_user.Open (loginID);

// Проверяем право доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять зоны доступа (нет права Concept.Feod.Admin.Feod[D])");
	}
// Проверка возможности модификации родительской зоны доступа
	res = USER_CHECK_ACCESS (loginID, feod_id, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять данный раздел (нет доступа [m] или [M])");
	}
// Проверка возможности модификации удаляемой зоны доступа
	res = USER_CHECK_ACCESS (loginID, GetFeodParentID (feod_id), "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Пользователь не имеет права удалять данный раздел (нет доступа к изменению структуры родительской зоны доступа -- [M] или [m])");
	}
// Проверка уровня доступа
	int AccessLevel = SYSTEM_ACCESS_LEVEL;
	GET_EXT_FIELD (oc_feod, AccessLevelThreshold, AccessLevel);

	if (oc_user.m_AccessLevel >= AccessLevel)
	{
		ERR_RETURN_COMMENT_2 (ERR_InsufficientAccessLevel, "У пользователя недостаточный уровень (%d) для удаления зоны доступа с порогом доступа (%d)", int(oc_user.m_AccessLevel), AccessLevel);
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Удаляем ссылки на указанны феод и его дочерние феоды из базы данных 
	identifier_arr			FeodArr;
	GetFeodDescendantIDs (arg.objID, FeodArr);
	FeodArr.Insert			(0, arg.objID);

	identifier_arr			GroupArr;
	OC_UserGroup			oc_group;
	oc_group.GetClassIdList (GroupArr);

// Удаляем ссылки на феоды из групп
	for (int g=0; g<GroupArr.Size(); g++)
	{
		oc_group.Open (GroupArr[g]);

		if (oc_group.IsValid()) for (int f=0; f<FeodArr.Size(); f++)
		{
			for (;;)
			{
				int index = oc_group.m_Rights_Feod.Find (FeodArr[f]);
				if (index==-1) break;
				oc_group.m_Rights_Feod.Del (index);
				oc_group.m_Rights_Attr.Del (index);
			}
		}
	}

// У всех пользователей удаляем феод и дочерние феоды из "собственных зон доступа"
	identifier_arr				UserArr;
	oc_user.GetClassIdList (UserArr);
	for (int u=0; u<UserArr.Size(); u++)
	{
		oc_user.Open (UserArr[u]);
		if (oc_user.IsValid()) for (int f=0; f<FeodArr.Size(); f++)
		{
			for (;;)
			{
				int index = oc_user.m_OwnFeodID.Find (FeodArr[f]);
				if (index==-1) break;
				oc_user.m_OwnFeodID.Del (index);
			}
		}
	}


// Уничтожаем феод как концепт
	MOD_Concept_Args concept_arg;
	concept_arg.objID = arg.objID;
	GetPicklockPassword (concept_arg.PicklockPassword);
	res = MOD_Concept_Delete (concept_arg);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_1 (res, "Не удалось уничтожить феод %u как концепт", arg.objID);
	}
//----------------------------------------------------------------------------[] 



	
	CACHE_NUM_USER_CHECK_ACCESS ++;
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