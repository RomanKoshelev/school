/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_User.cpp																[]
[] Date:          28.06.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с пользователями													[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_User.inc.h"
                                                               


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ПОЛЬЗОВАТЕЛЯ                                              []                            
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_New	(MOD_User_Args& arg, int AccessLevel)
{
	DEBUG_STACK_NAME (MOD_User_New);
/*............................................................................[]
		<Login					Логин создаваемого пользователя.
		<Password				Пароль создаваемого пользователя.
		<PasswordConfirm		Подтверждение пароля.
		<PasswordInBrowser	Использовать возможность автоматического ввода пароля
		<FullName				Полное имя пользователя.
		<Email					E-mail.

		>objID					Идентификатор пользователя.
		>ExitCode				Код возврата (OK BadLogin BadPassword BadPasswordConfirm LoginAlreadyExists).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Такой пользователь уже есть	
	if (FindUserByLogin (arg.Login)!=NA)
	{
		ERR_RETURN (ERR_LoginAlreadyExists);
	}
//	Пустой логин 
	if (arg.Login.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadLogin, "Пустой логин");
	}
//	Пустой пароль
	if (arg.Password.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadPassword, "Пустой пароль");
	}
// Несовпаление пароля и его подтверждения
	if (arg.Password != arg.PasswordConfirm)
	{
		ERR_RETURN (ERR_BadPasswordConfirm);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём пользователя
	OC_User		oc_user;
	identifier	userID = oc_user.New ();
	arg.objID = userID;

	oc_user.m_Login					= arg.Login;
	oc_user.m_CreationTime			= time(0);
	oc_user.m_Password				= arg.Password;
	oc_user.m_PasswordInBrowser	= arg.PasswordInBrowser;
	oc_user.m_FullName				= arg.FullName;
	oc_user.m_Email					= arg.Email;

// Регистрируем пользователя
	ERR_RESULT res;

	if (arg.Login == "anonymous")
	{
		if (arg.Password!="anonymous")
		{
			ERR_RETURN_COMMENT (ERR_BadPassword, "Пароль анонимного пользователя 'anonymous' должен быть 'anonymous'.");
		}
		res = AddUserToGroup (userID, GetGroupIDByType ("anonymous"));
	}
	else if (arg.Login=="{{IMPORT}}")
	{
		AccessLevel = -10;
		res = ERR_OK;
	}
	else
	{
		res = AddUserToGroup (userID, GetGroupIDByType ("user"));
	}
	oc_user.m_AccessLevel = AccessLevel;
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 



	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПРОВЕРКА ПАРОЛЯ ПОЛЬЗОВАТЕЛЯ                                              []                            
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Authorize	(MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Authorize);
/*............................................................................[]
		<Login					Логин.
		<Password				Пароль.
		<PasswordInBrowser	Пароль был введён автоматически (через куки). Допустимо, если у пользователя стоит флаг "PasswordInBrowser".

		>PasswordInBrowser	Использовать возможность автоматического ввода пароля. Если да, устанавливаются куки.
		>objID					Идентификатор пользователя или NA если авторизация провалилась.
		>ExitCode				Код возврата (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	bool bPasswordInBrowser = arg.PasswordInBrowser;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, arg.objID, &arg.PasswordInBrowser);

// Прошла ли проверка пароля
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// Можно ли автоматически подставлять пароль и логин
	if (bPasswordInBrowser && !arg.PasswordInBrowser)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "Пользователь обязан ввести логин и пароль, их нельзя автоматически передавать из куки.");
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]

















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ПОЛЬЗОВАТЕЛЕЙ                                                []                          
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Enumerate	(MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Enumerate);
/*............................................................................[]
		<Login					Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь права получения списка.
		<Password				Пароль пользователя, запрашивающего операцию.
		<objFirstNo				Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
		<objLastNo				Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

		>objIDs					Массив идентификаторов объектов.
		>objNames				Массив названий объектов.
		>objFullNames			Массив имён пользователей.
		>TotalStoredNum		Сколько всего объектов хранится в базе.
		>MaxNumInQuery			Максимально допустимое число запращиваемых за один раз объектов.
		>ExitCode				Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User", "L", &arg.objID);
	if (res != ERR_OK)	
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 

	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Чтобы не запросили слишком много пользователей 
	arg.objFirstNo = max (arg.objFirstNo, 0);
	arg.objLastNo	= max (arg.objFirstNo, arg.objLastNo);
	if ((arg.objLastNo - arg.objFirstNo) > MAX_USER_ENUMERATE_NUM)	
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Заполняем список пользователей
	OC_User oc_user;
	oc_user.SetIndex_Login ();
	identifier_arr arrID;
	int i;
	oc_user.GetClassIdList (arrID);
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<arrID.Size(); i++)
	{
		oc_user.Open (arrID[i]);

		arg.objIDs.Add			(arrID[i]);
		arg.objNames.Add		(oc_user.m_Login);
		arg.objFullNames.Add	(oc_user.m_FullName);
	}
	arg.TotalStoredNum	= arrID.Size();
	arg.MaxNumInQuery		= MAX_USER_ENUMERATE_NUM;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ПОЛЬЗОВАТЕЛЯ                                             []                             
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_GetData (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_GetData);
/*............................................................................[]
		<objID					Идентификатор пользователя, чья информация запрашивается.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами просматривать данные пользователей и обладать более высоким уровнем доступа, или быть самим пользователем.
		<Password				Пароль пользователя, запрашивающего операцию.

		>Login					Логин запрашиваемого пользователя
		>FullName				Полное имя пользователя.
		>Email					Электронный адрес пользователя.
		>URL						URL пользователя.
		>Data						Прочая информацияя, упакованная скриптами по известному им формату в текстовую строку.
		>PasswordInBrowser	Использовать возможность автоматического ввода пароля.
		>CreationTime			Время создания объекта
		>ReadOnly				Данные могут быть только прочитаны и не могут быть изменены.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// Проверяем права доступа
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "R");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}

	// Логин не имеет достаточно прав для проведения операции над объектом
		if (OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Пользователь не имеет достаточного уровня доступа чтобы смотреть чужие данные");
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	bool bCanChange = IS_ROOT (loginID) || arg.objID==loginID || 
		(USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "W")==ERR_OK) && 
		(OC_User(loginID).m_AccessLevel < oc_user.m_AccessLevel);

	arg.FullName				= oc_user.m_FullName;
	arg.Email					= oc_user.m_Email;
	arg.PasswordInBrowser	= (bool) oc_user.m_PasswordInBrowser;
	arg.ReadOnly				= !bCanChange;
	arg.URL						= oc_user.m_URL;
	arg.Data						= oc_user.m_Data;

	arg.Login					= oc_user.m_Login;
	arg.CreationTime			= oc_user.m_CreationTime;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]
















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ПОЛЬЗОВАТЕЛЯ                                             []                             
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_PutData (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_PutData);
/*............................................................................[]
		<objID					Идентификатор пользователя, чья информация запрашивается.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами изменять данные пользователей и более сильным уровнем доступа, чем objID, или быть самим пользователем.
		<Password				Пароль пользователя, запрашивающего операцию.
		<NewPassword			Если поле не пусто, сменить пароль.
		<NewPasswordConfirm	Подтверждение нового пароля.
		<PasswordInBrowser	Использовать возможность автоматического ввода пароля
		<FullName				Полное имя
		<Email					Электронный адрес
		<Data						Прочая информацияя, упакованная скриптами по известному им формату в текстовую строку.

		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// Проверяем права доступа
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "W");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}

	// Логин не имеет достаточно прав для проведения операции над объектом
		if (OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
		{
			ERR_RETURN (ERR_InsufficientAccessLevel);
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	if (!arg.NewPassword.IsEmpty() && arg.NewPassword != arg.NewPasswordConfirm)
	{
		ERR_RETURN (ERR_BadPasswordConfirm);
	}
	if (!arg.NewPassword.IsEmpty())
	{
		oc_user.m_Password		= arg.NewPassword;
	}
	oc_user.m_FullName			= arg.FullName;
	oc_user.m_Email				= arg.Email;
	oc_user.m_URL					= arg.URL;
	oc_user.m_PasswordInBrowser= arg.PasswordInBrowser;
	oc_user.m_Data					= arg.Data;
//----------------------------------------------------------------------------[] 


	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]


















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ПРАВ ПОЛЬЗОВАТЕЛЯ																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_GetRights (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_GetRights);
/*............................................................................[]
		<objID					Идентификатор пользователя, чья информация запрашивается.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами чтения прав других пользователей и более сильным уровнем доступа, или быть самим пользователем.
		<Password				Пароль пользователя, запрашивающего операцию.
		<ExpandGroups			Требуется ли отдавать набор прав для каждой группы -- LoginGroupRights.
		<ExpandRights			Требуется ли расширять набор прав за счёт всех дочерних (выводимых) прав.

		>Login					Логин запрашиваемого пользователя
		>LoginAccessLevel		Уровень доступа логина
		>LoginGroupIDs			Все группы прав логина.
		>LoginGroupNames		Имена групп права логина.
		>LoginGroupTypes		Типы групп: root, admin, user, прочее. Помогает строить интерфейс в административной зоне.
		>LoginGroupRights		Упакованные в строки данные по правам каждой группы. Формат: "feodID|атрибуты|feodName|feodType\nfeodID|атрибуты|feodName\n...feodID|атрибуты|feodName|feodType"
		>LoginOwnRights		Упакованные в строку данные по личным правам логина. Это те зоны доступа, которые создал сам логин. Формат тоже, что и у LoginGroupRights.

		>ObjAccessLevel		Уровень доступа пользователя.
		>ObjGroupIDs			Если логин принадлежит к группе пользователя и его уровень сильнее, то он может знать о том, что пользователь обладает этой группой. Список таких групп.
		>CreationTime			Время создания объекта
		>ReadOnly				Права могут быть только прочитаны и не могут быть изменены.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]


	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
// Проверяем права доступа
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "R");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если требуется раскрывать права, то необходимо раскрывать группы
	if (arg.ExpandRights && !arg.ExpandGroups)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument,"Если требуется раскрывать права, то необходимо раскрывать и сами группы");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	OC_User oc_login (loginID);

// Права доступа	
	arg.LoginAccessLevel	= oc_login.m_AccessLevel;
	arg.ObjAccessLevel	= oc_user.m_AccessLevel;

// Получаем списки групп
	for (int g=0; g<oc_login.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_login.m_GroupID[g];

	// Группа должна существовать
		if (!OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("Некорректная группа прав %d у пользователя %s [%d]. Исправлено.", int (oc_login.m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login.m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

	// Пополняем список всех групп прав логина
		arg.LoginGroupIDs		+=	groupID;
		arg.LoginGroupNames	+= oc_group.m_Name;
		arg.LoginGroupTypes	+= oc_group.m_Type;
		arg.LoginGroupRights	+= arg.ExpandGroups? string (GetGroupRights (groupID, arg.ExpandRights)) : string("");

	// Если логин принадлежит к группе пользователя и его уровень сильнее, то он может знать о том, что пользователь обладает этой группой.
		if ((IS_ROOT (loginID) || IS_AUDITOR (loginID) || oc_login.m_AccessLevel<oc_user.m_AccessLevel) && oc_user.m_GroupID.Find (oc_login.m_GroupID[g])!=-1)
		{
			arg.ObjGroupIDs	+= groupID;
		}
	}

//	Можно ли редактировать права
	bool bCanChange = arg.objID!=loginID && (USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "W")==ERR_OK);

	arg.ReadOnly		= !bCanChange;
	arg.Login			= oc_user.m_Login;
	arg.CreationTime	= oc_user.m_CreationTime;

// Личные права логина
	arg.LoginOwnRights = "";
	for (int f=0; f<oc_login.m_OwnFeodID.Size(); f++)
	{
		string strFeodID;
		string strFeodName;

		identifier feodID = oc_login.m_OwnFeodID[f];
		if (!CHECK_FEOD_ID(feodID))
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный ID личной зоны доступа (%d) пользователя %s. Исправлено.", feodID, ((string)oc_login.m_Login).c_str());
			oc_login.m_OwnFeodID.Del (f);
			f--;
			continue;
		}

	// Запоминаем все права, в том числе и феоды нижних уровней
		identifier_arr allFeods;
		if (arg.ExpandRights)
		{
			GetAllFeodChilds (feodID, allFeods);
			allFeods.Insert  (0, feodID);
		}
		else
		{
			allFeods	+=	feodID;
		}
			
		for (int i=0; i<allFeods.Size(); i++)
		{
			if (GetFeodFullName (allFeods[i], strFeodName, 1, "::"))
			{
				string strFeodType;
				GetFeodType (allFeods[i], strFeodType);

				strFeodID.Format ("%d", allFeods[i]);
				arg.LoginOwnRights += "\n";
				arg.LoginOwnRights += strFeodID;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += ALL_ATTRIBUTES;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += strFeodName;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += strFeodType;
			}
		}
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ПРАВ ПОЛЬЗОВАТЕЛЯ																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_PutRights (MOD_User_Args& arg)
{
	DEBUG_STACK_NAME (MOD_User_PutRights);
/*............................................................................[]
		<objID					Идентификатор пользователя, чья информация запрашивается.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами изменения прав других пользователей. Чтобы отобрать права надо иметь более сильный уровень доступа.
		<Password				Пароль пользователя, запрашивающего операцию.
		<AccessLevel			Новый уровень доступа пользоваетеля. Уровень доступа не может быть равным или сильнее чем уровень доступа самого логина.
		<objIDs					Права, которые, по мнению логина, должны быть у пользователя. Если логин сильнее, то он может отобрать у пользователя любые группы, которыми обладает сам. Независимо от уровня доступа он может делегировать те группы прав, которыми обладает сам.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	identifier userID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (userID);

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// Проверяем права доступа
	if (loginID!=userID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "W");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}
	}
	else
	{
	// Пользователь не может сам себе изменить права
		ERR_RETURN (ERR_OK);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	OC_User oc_login  (loginID);
// Если более слабый уровень, то возможности изменения прав ограничены
	if (oc_login.m_AccessLevel >= oc_user.m_AccessLevel)
	{
	// Можно изменять уровень доступа только тем, кто слабее
		if (arg.AccessLevel != oc_user.m_AccessLevel)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Можно изменять уровень доступа только тем, кто слабее.");
		}
	}
// Нельзя назначать уровень доступа такой же или сильнее, чем имеешь сам
	if (arg.AccessLevel <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Нельзя назначать уровень доступа такой же или сильнее, чем имеешь сам.");
	}
// Нельзя самому себе менять права
	if (loginID == userID)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "Нельзя самому себе менять права.");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Уровень доступа
	oc_user.m_AccessLevel = arg.AccessLevel;

// Группы прав
	for (int g=0; g<oc_login.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_login.m_GroupID[g];

	// Группа должна существовать
		if (!OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("Некорректная группа прав %d у пользователя %s [%d]. Исправлено.", int (oc_login.m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login.m_GroupID.Del (g);
			g--;
			continue;
		}


		if (oc_user.m_GroupID.Find (oc_login.m_GroupID[g])==-1)
		{
		// У пользователя objID такой группы прав нет -- её можно добавить
			if (arg.objIDs.Find (groupID)!=-1)
			{
			// Логин решил, что группу надо делегировать.
			// группа делегируется с более слабым уровнем доступа, чем была у логина
				AddUserToGroup (userID, groupID);
			}
		}
		else if (oc_login.m_AccessLevel < oc_user.m_AccessLevel)
		{
		// У пользователя objID такие права есть, его уровень доступа слабее -- права можно отобрать
			if (arg.objIDs.Find (groupID)==-1)
			{
			// Логин решил, что пользователь не должен быть в этой группе, исключаем его.
				RemoveUserFromGroup (userID, groupID);
			}			
		}
	}
//----------------------------------------------------------------------------[] 




	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПРОВЕРКА ПОЛЬЗОВАТЕЛЕМ НАЛИЧИЯ У СЕБЯ УКАЗАННЫХ ПРАВ.                     []                                                     
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_CheckOwnRights (MOD_User_Args& arg)
{
	DEBUG_STACK_NAME (MOD_User_CheckOwnRights);
/*............................................................................[]
		<Login					Логин пользователя, запрашивающего операцию. Для него и проверяются права.
		<Password				Пароль пользователя, запрашивающего операцию.
		<FeodNames				Набор имён зон доступа
		<FeodAttributes		Соответсвующие зонам доступа атрибуты доступа. Строки вида "CLRWD"

		>Accesses				Булевский массив, содержащий ответы на вопросы о возможности доступа к соответствующей зоне с указанными атрибутами.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	identifier userID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, userID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	for (int i=0; i<arg.FeodNames.Size(); i++)
	{
		arg.Accesses += (USER_CHECK_ACCESS (arg.Login, arg.Password, arg.FeodNames[i], arg.FeodAttributes[i])==ERR_OK);
	}
//----------------------------------------------------------------------------[] 

	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` УДАЛЕНИЕ ПОЛЬЗОВАТЕЛЯ                                                     []                     
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Delete (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Delete);
/*............................................................................[]
		<objID					Идентификатор удаляемого пользователя.
		<Login					Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами удаления пользователей, и более сильным доступом, чем удаляемый пользователь.
		<Password				Пароль пользователя, запрашивающего операцию.
		>ExitCode				Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		Текстовый комментарий к коду возврата.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//
// Проверка доступа
//
//----------------------------------------------------------------------------[] 
// Объект должен существовать
	identifier userID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (userID);
// Проверяем логин/пароль и права доступа
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User", "D", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
// Логин не имеет достаточно прав для проведения операции над объектом
	if (!IGNORE_AUTHORIZATION && OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
	{
		ERR_RETURN (ERR_InsufficientAccessLevel);
	}
//----------------------------------------------------------------------------[] 


	
//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Пользователь удаляется из групп.
	for (int g=0; g<oc_user.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_user.m_GroupID[g];
		if (OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			OC_UserGroup oc_group (groupID);
			for (int i=0; i<100; i++)
			{
				int m = oc_group.m_UserID.Find (userID);
				if (m==-1) break;
				oc_group.m_UserID.Del (m);
				m--;
			}
		}
	}

// Удаляем пользователя. Прощай, дорогой товарищ.
	oc_user.Delete ();
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
