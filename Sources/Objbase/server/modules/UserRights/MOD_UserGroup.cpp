/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserGroup.cpp															[]
[] Date:          01.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с группами прав пользователей                        []
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserGroup.inc.h"



//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОЙ ГРУППЫ																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_New (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_New);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами создания групп. Пользователь заносится в создаваемую группу.
		<Password					Пароль пользователя, запрашивающего операцию.
		<Name							Имя создаваемой группы. Если передано пустое или неуникальное имя, то система сама придумывает/изменяет название группы.
		<Type							Предопределённый тип группы: root, admin, user, прочее. Помогает строить интерфейс в административной зоне.
		<Description				Описание группы. Если пусто, берётся из FromID.
		<AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Группа должна иметь более слабый порог (+1), чем уровень её создателя, чтобы тот мог её править/удалять.

		>objID						Идентификатор создданной группы.
		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "C", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Нельзя создавать групппу с типом "root"
	if (!IGNORE_AUTHORIZATION && arg.Type=="root") 
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Какой ты хитрый! Нельзя создавать групппу с типом \"root\".");
	}
// Нельзя создавать групппу с типом "auditor"
	if (!IGNORE_AUTHORIZATION && arg.Type=="auditor") 
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Какой ты хитрый! Нельзя создавать групппу с типом \"auditor\".");
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
		arg.Name.Format ("New group created by %s", arg.Login.c_str());
	}

// Имя группы должно быть уникальным.
	if (GetGroupID(arg.Name, true)!=NA)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "Группа с именем '%s' уже существует.", arg.Name.c_str());
	}

	OC_UserGroup oc_group;
	identifier groupID = oc_group.New ();
	arg.objID = groupID;
	
// Создаваемая группа должна иметь более слабый уровень доступа, чтобы создатель мог её править/удалять
	oc_group.m_Name						= arg.Name;
	oc_group.m_Type						= arg.Type;
	oc_group.m_Description				= arg.Description;
	oc_group.m_AccessLevelThreshold	= max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);
	oc_group.m_CreationTime				= time(0);

// Заносим создателя и рутов в члены группы
	AddUserToGroup		(loginID, groupID);
	AddRootsToGroup	(groupID, loginID);

//	Упрощаем набор прав группы
	UserGroupSimplifyRightsSet	(groupID);
//----------------------------------------------------------------------------[] 


	
	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ГРУПП																			[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_Enumerate (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_Enumerate);
/*............................................................................[]
		<Login							Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь права получения списка.
		<Password						Пароль пользователя, запрашивающего операцию.
		<objFirstNo						Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
		<objLastNo						Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

		>objIDs							Массив идентификаторов объектов. Выдаются только те группы, в которых состоит пользователь.
		>objNames						Массив названий объектов.
		>objTypes						Массив типов групп: root, admin, user, прочее. Помогает строить интерфейс в административной зоне.
		>objAccessLevelThresholds	Пороговые значение для уровня доступа пользователей. 
		>TotalStoredNum				Сколько всего объектов хранится в базе.
		>MaxNumInQuery					Максимально допустимое число запращиваемых за один раз объектов.
		>ExitCode						Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment				Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "L", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.objFirstNo = max(arg.objFirstNo, 0);
	if ((arg.objLastNo - arg.objFirstNo) > MAX_GROUP_ENUMERATE_NUM)
	{
		arg.MaxNumInQuery	= MAX_GROUP_ENUMERATE_NUM;
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Могут быть показаны только те группы, в которых состит логин
	int				oc_login_m_GroupID_Size = oc_login.m_GroupID.Size();
	identifier_arr oc_login_m_GroupID		= oc_login.m_GroupID;

// Если логин аудитор или рут, то доступны все группы
	if (IS_ROOT(loginID) || IS_AUDITOR(loginID))
	{
		OC_UserGroup oc_group;
		oc_group.GetClassIdList (oc_login_m_GroupID);
		oc_login_m_GroupID_Size = oc_login_m_GroupID.Size();
	}
	static int g;
	for (g=arg.objFirstNo; (g<=arg.objLastNo) && (g<oc_login_m_GroupID_Size); g++)
	{
		identifier groupID = oc_login_m_GroupID[g];

	// Группа невалидная
		if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("Некорректная группа прав %d у пользователя %s [%d]. Исправлено.", int (oc_login_m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login_m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

		arg.objIDs							+= groupID;
		arg.objNames						+= oc_group.m_Name;
		arg.objTypes						+= oc_group.m_Type;
		arg.objAccessLevelThresholds	+= oc_group.m_AccessLevelThreshold;
	}
	
	arg.TotalStoredNum	=	oc_login_m_GroupID.Size();
	arg.MaxNumInQuery		=	MAX_GROUP_ENUMERATE_NUM;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ГРУППЫ																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_GetData (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_GetData);
/*............................................................................[]
		<objID						Идентификатор группы, чья информация запрашивается.
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами просматривать группы и принадлежать к запрашиваемой группе.
		<Password					Пароль пользователя, запрашивающего операцию.
		<UserFirstNo				Номер пользователя внутри групы, начиная с которого перечислять пользователей.
		<UserLastNo					Номер последнего запрашиваемого пользователя групы.

		>Name							Имя группы
		>Type							Предопределённый тип группы: root, admin, user, прочее. Помогает строить интерфейс в административной зоне.
		>Description				Описание группы
		>AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Группа должна иметь более слабый порог, чем уровень её создателя, чтобы тот мог её править/удалять.
		>CreationTime				Время создания объекта
		>FeodIDs						Набор идентификаторов зон доступа.
		>FeodNames					Набор имён зон доступа.
		>FeodAttributes			Соответсвующие зонам доступа атрибуты доступа. Строки вида "CLRWD"

		>UserIDs						Идентификаторы пользователей-членов группы.
		>UserLogins					Логины пользователей-членов группы.
		>UserFullNames				Имена пользователей-членов группы.
		>UserAccessLevels			Уровни доступа пользователей-членов группы.
		>UserCreationTimes		Времена создания пользователей-членов группы.
		>UserTotalStoredNum		Сколько всего пользователей в группе.
		>UserMaxNumInQuery		Максимально допустимое число запращиваемых за один раз пользователей группы.

		>ReadOnly					Данные могут быть только прочитаны и не могут быть изменены.

		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel TooManyEnumerate).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[]
//
// Проверка доступа
//
//----------------------------------------------------------------------------[]
// Объект должен существовать
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "R", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// Если пользователь не в группе -- пшёл вон.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "Пользователь не принадлежит к группе");
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.UserFirstNo = max(arg.UserFirstNo, 0);
	if ((arg.UserLastNo - arg.UserFirstNo) > MAX_USER_ENUMERATE_NUM)
	{
		arg.UserMaxNumInQuery = MAX_USER_ENUMERATE_NUM;
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.Name							= oc_group.m_Name;
	arg.Type							= oc_group.m_Type;
	arg.Description				= oc_group.m_Description;
	arg.AccessLevelThreshold	= oc_group.m_AccessLevelThreshold;
	arg.CreationTime				= oc_group.m_CreationTime;

// Идентификаторы, имена и атрибуты зон доступа
	for (int f=0; f<oc_group.m_Rights_Feod.Size(); f++)
	{
		identifier feodID = oc_group.m_Rights_Feod[f];
		if (!CHECK_FEOD_ID (feodID))
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный ID зоны доступа (%d) в группе %s. Исправлено.", feodID, ((string)oc_group.m_Name).c_str());
			oc_group.m_Rights_Feod.Del (f);
			oc_group.m_Rights_Attr.Del (f);			
			f--;
		}
		else
		{
		// Запоминаем все права, в том числе и феоды нижних уровней
			identifier_arr allFeods;
			//GetAllFeodChilds (feodID, allFeods);
			allFeods.Insert  (0, feodID);
			for (int i=0; i<allFeods.Size(); i++)
			{
				string FeodName;
				if (GetFeodFullName (allFeods[i], FeodName, 1, "::"))
				{
					arg.FeodIDs				+= allFeods[i];
					arg.FeodNames			+= FeodName;
					arg.FeodAttributes	+= oc_group.m_Rights_Attr[f];
				}
			}
		}
	}

// Все члены группы.
	for (int m=arg.UserFirstNo; m<=arg.UserLastNo && m<oc_group.m_UserID.Size(); m++)
	{
		identifier userID = oc_group.m_UserID[m];
		if (!OC_Exist (OBJ_CLASS_ID_User, userID))
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный пользователь с идентификатором [%d], член группы %s. Исправлено.", userID, ((string)oc_group.m_Name).c_str());
			oc_group.m_UserID.Del (m);
			m--;
			continue;
		}
		OC_User oc_user (userID);

		arg.UserIDs					+= userID;
		arg.UserLogins				+= oc_user.m_Login;
		arg.UserFullNames			+= oc_user.m_FullName;
		arg.UserCreationTimes	+=	oc_user.m_CreationTime;
		arg.UserAccessLevels		+= oc_user.m_AccessLevel;
	}

	bool bCanChange = (USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "W")==ERR_OK) && 
							(oc_login.m_AccessLevel < oc_group.m_AccessLevelThreshold);

	arg.UserTotalStoredNum	= oc_group.m_UserID.Size();
	arg.UserMaxNumInQuery	= MAX_USER_ENUMERATE_NUM;
	arg.ReadOnly				= !bCanChange;	
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//----------------------------------------------------------------------------[] 
// Все права группы
struct GR_RIGHTS
{
	identifier	feodID;
	char			Attribute;
	bool			bFound;
	GR_RIGHTS () {feodID=NA; Attribute=0; bFound=false;}
	bool operator ==	(const GR_RIGHTS& to) const {return feodID==to.feodID && Attribute==to.Attribute;}
	bool operator <	(const GR_RIGHTS& to) const {return feodID<to.feodID || (feodID==to.feodID && Attribute<to.Attribute);}
	bool operator <=	(const GR_RIGHTS& to) const {return ((*this)<to) || ((*this)==to);}
};
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ГРУППЫ																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_PutData (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_PutData);
/*............................................................................[]
	<objID						Идентификатор группы, чья информация изменяется.
	<Login						Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами изменять группы, принадлежать к изменяемой группе и иметь более сильный уровень доступа, чем пороговое значение группы.
	<Password					Пароль пользователя, запрашивающего операцию.
	<Name							Имя группы
	<Type							Предопределённый тип группы: root, admin, user, прочее. Помогает строить интерфейс в административной зоне.
	<Description				Описание группы
	<AccessLevelThreshold	Пороговое значение уровня доступа пользователей. Не может быть сильнее чем уровень логина.
	<FeodIDs						Набор идентификаторов всех зон доступа группы. Логин должен иметь доступ к этим зонам с соответствующими атрибутами.	Кроме того, логин не может лишить группу некоторых прав, если при этом сам лишается этих прав. Эти два правила означают, что пользователь не может ни увеличить, ин уменьшить набор собственных прав.
	<FeodAttributes			Соответсвующие зонам доступа атрибуты доступа. Строки вида "CLRWD"

	>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
	>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "W", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// Если пользователь не в группе -- пшёл вон.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "Пользователь не принадлежит к группе");
	}
//----------------------------------------------------------------------------[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если передано пустое имя -- ошибка.
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя группы не может быть пустым.");
	}

// Имя группы должно быть уникальным.
	identifier grID = GetGroupID (arg.Name, true);
	if (grID!=NA && grID!=groupID)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "Имя группы должно быть уникальным. Уже существует другая группа с именем %s", arg.Name.c_str());
	}

// Изменение порогового уровня доступа
	int f;
	if (arg.AccessLevelThreshold < oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Пороговое значение уровня доступа пользователей к группе AccessLevelThreshold не может быть сильнее чем уровень доступа пользователя, изменяющего его.");
	}

// Проверка неувеличения собственных прав
// (Проверка неуменьшения собственных прав не производится, так как 
// обходится путём создания подставного пользователя.)
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, arg.FeodIDs[f], arg.FeodAttributes[f])!=ERR_OK)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Пользователь не может назначить группе права, которыми сам не обладает.");
		}
	}

// Если уровень доступа меньше, логин не имеет права менять данные группы
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		if (	oc_group.m_Name						!= arg.Name						||
				oc_group.m_Description				!= arg.Description			||
				oc_group.m_Type						!= arg.Type						||
				oc_group.m_AccessLevelThreshold	!= arg.AccessLevelThreshold)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа доля изменения значений полей группы.");
		}
	}


// Проверяем корректность атрибутов
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (!CHECK_ATTRIBUTES (arg.FeodAttributes[f]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadArgument, "Один из атрибутов в массиве arg.FeodAttributes[%d]='%s' некорректен.", f, arg.FeodAttributes[f].c_str());
		}
	}

//	Проверка валидности феодов
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (!CHECK_FEOD_ID (arg.FeodIDs[f]))
		{
			ERR_RETURN_COMMENT (ERR_BadID, "Указана несуществующая зона доступа (феод)");
		}
	}

// Нельзя изменять тип группы на "root"
	if (!IGNORE_AUTHORIZATION && arg.Type=="root" && oc_group.m_Type!="root")
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Какой ты хитрый! Нельзя изменять тип групппы на \"root\".");
	}
// Нельзя изменять тип группы на "auditor"
	if (!IGNORE_AUTHORIZATION && arg.Type=="auditor" && oc_group.m_Type!="auditor")
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Какой ты хитрый! Нельзя изменять тип групппы на \"auditor\".");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Дополнительная проверка аргументов	                                       []
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если уровень доступа меньше, логин не может отбирать права у группы
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		CPtr <GR_RIGHTS> allRigths;
		int i,j;

	// Фиксируем все права группы
		for (i=0; i<oc_group.m_Rights_Feod.Size(); i++) for (j=0; j<(int)string(oc_group.m_Rights_Attr[i]).Len(); j++)
		{
			GR_RIGHTS gr_right;
			gr_right.feodID		= oc_group.m_Rights_Feod[i];
			gr_right.Attribute	= string(oc_group.m_Rights_Attr[i])[j];
			gr_right.bFound		= false;

			if (allRigths.Find(gr_right, true)==-1)
			{
				allRigths.InsertSorted (gr_right);
			}
		}

	//	Проверяем наличие зафиксированных прав в аргументах
		for (i=0; i<arg.FeodIDs.Size(); i++) for (j=0; j<(int)arg.FeodAttributes[i].Len(); j++)
		{
			GR_RIGHTS gr_right;
			gr_right.feodID		= arg.FeodIDs[i];
			gr_right.Attribute	= arg.FeodAttributes[i][j];
			gr_right.bFound		= false;

			int index = allRigths.Find(gr_right, true);
			if (index != -1)
			{
				allRigths[index].bFound = true;
			}
		}

	// Проверяем, что все права, существовавшие у группы, присутствуют в аргументах
		for (i=0; i<allRigths.Size(); i++) if (allRigths[i].bFound==false)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа для уменьшения прав группы.");
		}
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
//	Изменяем поля
	oc_group.m_Name						= arg.Name;
	oc_group.m_Description				= arg.Description;
	oc_group.m_Type						= arg.Type;

//	Назначаем группе новый (неуменьшенный, если уровень доступа недостаточный) набор прав.
	oc_group.m_AccessLevelThreshold	= arg.AccessLevelThreshold;
	oc_group.m_Rights_Feod				= arg.FeodIDs;
	oc_group.m_Rights_Attr				= arg.FeodAttributes;

//	Упрощаем набор прав группы
	UserGroupSimplifyRightsSet	(groupID);
//----------------------------------------------------------------------------[] 



	CACHE_NUM_USER_CHECK_ACCESS++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ ГРУППЫ																				[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_Delete (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_Delete);
/*............................................................................[]
		<objID						Идентификатор удаляемой группы.
		<Login						Логин пользователя, запрашивающего операцию. Пользователь должен обладать удалять группы, принадлежать к удаляемой группе и иметь более сильный уровень доступа, чем пороговое значение группы.
		<Password					Пароль пользователя, запрашивающего операцию.
		>ExitCode					Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "D", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// Если пользователь не в группе -- пшёл вон.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "Пользователь не принадлежит к группе");
	}

// Проверка порогового уровня доступа
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Недостаточный уровень доступа доля удаления группы.");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// У всех членов группы выкидываем её из списка
	for (int u=0; u<oc_group.m_UserID.Size(); u++)
	{
		if (OC_Exist (OBJ_CLASS_ID_User, oc_group.m_UserID[u]))
		{
			OC_User oc_user (oc_group.m_UserID[u]);
			int g=oc_user.m_GroupID.Find (groupID);
			if (g!=-1)
			{
				oc_user.m_GroupID.Del (g);
			}
			else
			{
				SERVER_DEBUG_ERROR_4 ("У пользователя %s[%d] группа %s[%d] не обнаружена.", string (oc_user.m_Login).c_str(), int (oc_group.m_UserID[u]), string (oc_group.m_Name).c_str(), groupID);
			}
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный ID=%d члена группы %s.", int (oc_group.m_UserID[u]), string (oc_group.m_Name).c_str());
		}
	}

// Удаляем группу
	oc_group.Delete ();
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