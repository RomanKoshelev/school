/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_User.pvt.cpp															[]
[] Date:          06.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:	Работа с пользователями													[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_User.inc.h"

bool IGNORE_AUTHORIZATION = false;                                                               
//______________________________________________________________________________
//                                                                            []
//` Функция хеширования пароля                                                []                          
//                                                                            []
const char * PASSWORD_HASH (const char * Password)
{
	DEBUG_STACK_NAME (PASSWORD_HASH);

	static char RetVal [1024];

	strncpy (RetVal, Password, 512);
	return RetVal;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Найти пользователя по логину                                              []                            
//                                                                            []
identifier FindUserByLogin (const char * Login)
{
	DEBUG_STACK_NAME (FindUserByLogin);

	OC_User oc_user;
	oc_user.SetIndex_Login ();
	key_arr ka;
	ka += Login;
	if (oc_user.Find (ka))
	{
		return oc_user.IsValid()? oc_user.GetObjectID (): NA;
	}
	return NA;
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Проверка пароля пользователя                                              []                            
//                                                                            []
ERR_RESULT USER_CHECK_LOGIN_PASSWORD (const char * Login, const char * Password, identifier& userID, bool * pPasswordInBrowser)
{
	DEBUG_STACK_NAME (USER_CHECK_LOGIN_PASSWORD);

// Находим пользователя по логину
	userID = FindUserByLogin (Login);
	if (userID==NA)
	{
		return ERR_BadLogin;
	}
	OC_User oc_user = userID;

	if (pPasswordInBrowser)
	{
		(*pPasswordInBrowser) = (bool)(oc_user.m_PasswordInBrowser);
	}

// Если пароль равен тому, что у пользователя, или равен хешу пользовательского или равен хешу отмычки, то все ок.
	string PicklockPassword;
	GetPicklockPassword (PicklockPassword);
	if (IGNORE_AUTHORIZATION || (oc_user.m_Password == Password) || (Password == PASSWORD_HASH (((string)(oc_user.m_Password)))) || (Password == PASSWORD_HASH (PicklockPassword)))
	{
		return ERR_OK;
	}

	return ERR_BadPassword;
}
//____________________________________________________________________________[]









//___________________________________________________________________________________________________
//																																	[]
//																																	[]
//		01.07.2000	(C) Roman V. Koshelev																				[]
//`	Проверка прав доступа к операции																				   []                                
//																																	[]
//-------------------------------------------------------------------------------------------------[]
ERR_RESULT	USER_CHECK_ACCESS (				//	== ExitCode															[]
				const	char *	Login, 			//	>> Логин																[]
				const	char *	Password,		//	>> Пароль															[]
				const	char *	Feod, 			//	>> Зона доступа, системный тип концепта.					[]
				const	char *	Attrib, 			//	>> Атрибуты владения правами [C][L][R][W][D]				[]
				identifier *	pLoginID) 		//	<< ID логина														[]
//-------------------------------------------------------------------------------------------------[]
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS);

	identifier feodID = GetFeodIDByType (Feod);
	if (!IGNORE_AUTHORIZATION && feodID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("Нет такой зоны прав: %s", Feod);
		return ERR_SYSTEM_ERROR;
	}

	identifier userID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (Login, Password, userID);
	if (res!=ERR_OK)
	{
		return res;
	}

	if (pLoginID) *pLoginID=userID;

	return USER_CHECK_ACCESS (userID, feodID, Attrib);
}
//_________________________________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` CHECK_ATTRIBUTES                                                          []                
//                                                                            []
bool CHECK_ATTRIBUTES (const char *Attrib)
{
	DEBUG_STACK_NAME (CHECK_ATTRIBUTES);

	static string all_attributes (ALL_ATTRIBUTES);
	for (int i=0; Attrib[i]; i++)
	{
		if (all_attributes.Find (Attrib[i])==-1)
		{
			SERVER_DEBUG_ERROR_2 ("Указан несуществующий атрибут [%c] в списке атрибутов %s", Attrib[i], Attrib);
			return false;
		}
	}
	return true;
}
//____________________________________________________________________________[]




int CACHE_NUM_USER_CHECK_ACCESS = 0;
//___________________________________________________________________________________________________
//																																	[]
//																																	[]
//		07.07.2000	(C) Roman V. Koshelev																				[]
//`	Проверка прав доступа к операции																				   []                                
//																																	[]
//-------------------------------------------------------------------------------------------------[]
void	USER_CHECK_ACCESS(						//	== ExitCode															[]
				identifier		userID, 			//	<< Пользователь													[]
				identifier		feodID, 			//	<< Зона доступа													[]
				const	char *	Attrib, 			//	<< Атрибуты владения правами [C][L][R][W][D][M]			[]
				int&			Res) 					//	>> Результат														[]
//-------------------------------------------------------------------------------------------------[]
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS);
	IF_CACHED_ARGS_4_RETURN_VOID (10*1000, userID, feodID, Attrib, CACHE_NUM_USER_CHECK_ACCESS);
	// !!! Вынести все максимальные размеры функциональных кешей в config

//----------------------------------------------------------------------------[] 
	Res = ERR_AccessDeny;

	if (IGNORE_AUTHORIZATION) {Res = ERR_OK; return;}

	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		Res = ERR_BadID;
		return;
	}
	if (!CHECK_FEOD_ID(feodID))
	{
		Res = ERR_BadID;
		return;
	}
	if (!CHECK_ATTRIBUTES (Attrib))
	{
		Res = ERR_BadArgument;
		return;
	}

	OC_User oc_user;
	oc_user.Open (userID);

	string ATTR="";

// Проверяем в личных зонах доступа
	if (oc_user.m_OwnFeodID.Find (feodID)!=-1)
	{
		Res = ERR_OK;
	}

// Проходимся по всем группам
	for (int g=0; Res!=ERR_OK && g<oc_user.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_user.m_GroupID[g];

	// Группа невалидная
		if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("Некорректная группа прав %d у пользователя %s [%d]. Исправлено.", (identifier)oc_user.m_GroupID[g], ((string)oc_user.m_Login).c_str(), userID);
			oc_user.m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

	// Пользователь не обнаружен в группе
		if (oc_group.m_UserID.Find(userID)==-1)
		{
			SERVER_DEBUG_ERROR_4 ("Пользователь %s [%d] не обнаружен в группе %s [%d]. Исправлено.", ((string)oc_user.m_Login).c_str(), userID, ((string)oc_group.m_Name).c_str(), groupID);
			oc_user.m_GroupID.Del (g);
			g--;
			continue;
		}

	// Проходимся по правам группы (=хозяйствам=феодам)
		for (int f=0; Res!=ERR_OK && f<oc_group.m_Rights_Feod.Size(); f++)
		{
			identifier group_feodID = oc_group.m_Rights_Feod[f];

		// Феод невалидный
			if (!CHECK_FEOD_ID(group_feodID))
			{
				SERVER_DEBUG_ERROR_3 ("Некорректный феод %d у группы %s [%d]. Исправлено.", int (oc_group.m_Rights_Feod[f]), ((string)oc_group.m_Name).c_str(), int (oc_user.m_GroupID[g]));
				oc_group.m_Rights_Feod.Del	(f);
				oc_group.m_Rights_Attr.Del	(f);
				f--;
				continue;
			}

		// Проверяем, имеет ли група искомый феод или его предка (т.е. обладает даже более широкой зоной досупа)
			if (group_feodID==feodID || FeodHasChild (group_feodID, feodID))
			{
				int	nAttrib	= strlen(Attrib);
				int	a;

			// Проверяем все недостающие атрибуты права
				for (a=0; a<nAttrib; a++)
				{
				// Атрибут уже найден
					if (ATTR.Find(Attrib[a])!=-1)
					{
						continue;
					}

				// Искомый атрибут дла запрашиваемого феода найден, запоминаем его
					if ((Attrib[a]<'a' || group_feodID==feodID) && string(oc_group.m_Rights_Attr[f]).Find(Attrib[a])!=-1)
					{
						ATTR += Attrib[a];
					}
					else if (string(oc_group.m_Rights_Attr[f]).Find(char(Attrib[a]-32))!=-1)
					{
					// Найден более сильный атрибут (искали [m], а есть [M])
						ATTR += Attrib[a];
					}
				}

			// Проверяем, все или атрибуты найдены
				bool bContinue = false;
				for (a=0; a<nAttrib && !bContinue; a++) 
				{
					if (((CPtr<char>)ATTR).Find(Attrib[a])==-1)
					{
					// Ещё не все атрибуты нашлись
						bContinue = true;
					}
				}
			// Все атрибуты найдены
				if (!bContinue) 
				{
					Res = ERR_OK;
					break;
				}
			}
		}
	}
//----------------------------------------------------------------------------[] 


	CACHE_STORE_RESULT_1	(Res);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS                                                         []                 
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS (identifier userID, identifier feodID, const char * Attrib)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS);

	if (IGNORE_AUTHORIZATION) {return ERR_OK;}
	
	int Res;
	USER_CHECK_ACCESS (userID, feodID, Attrib, Res);
	return (ERR_RESULT)Res;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Добавление пользователя в группу                                          []                                
//                                                                            []
ERR_RESULT AddUserToGroup (identifier userID, identifier groupID)
{
	DEBUG_STACK_NAME (AddUserToGroup);

// Объекты должны существовать
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("Невалидный идентификатор группы %d", groupID);
		return ERR_BadID;
	}
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		SERVER_DEBUG_ERROR_1 ("Невалидный идентификатор пользователя %d", userID);
		return ERR_BadID;
	}

	OC_User			oc_user	(userID);
	OC_UserGroup	oc_group	(groupID);

	if (oc_user.m_GroupID.Find (groupID)!=-1)
	{
		SERVER_DEBUG_ERROR_2 ("Пользователь %s уже числится в составе группы %s", ((string)oc_user.m_Login).c_str(), ((string)oc_group.m_Name).c_str());
	}
	else if (oc_group.m_UserID.Find (userID)!=-1)
	{
		SERVER_DEBUG_ERROR_2 ("Группа прав %s уже находится в числе полномочий пользователя %s", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
	}
	else
	{
		oc_user.m_GroupID	+= groupID;
		oc_group.m_UserID	+= userID;
	}

	return ERR_OK;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Удаление пользователя из группы	                                          []                                
//                                                                            []
ERR_RESULT RemoveUserFromGroup (identifier userID, identifier groupID)
{
	DEBUG_STACK_NAME (RemoveUserFromGroup);

// Объекты должны существовать
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("Невалидный идентификатор группы %d", groupID);
		return ERR_BadID;
	}
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		SERVER_DEBUG_ERROR_1 ("Невалидный идентификатор пользователя %d", userID);
		return ERR_BadID;
	}

	OC_User			oc_user	(userID);
	OC_UserGroup	oc_group	(groupID);
	int i;


// Удаляем группу из массива прав пользователя
	i = oc_user.m_GroupID.Find (groupID);
	if (i!=-1)
	{
		oc_user.m_GroupID.Del (i);
	}
	else 
	{
		SERVER_DEBUG_ERROR_2 ("Удаляемая группа прав %s не найдена у пользователя %s", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
	}

// Удаляем пользователя из массива членов группы
	i = oc_group.m_UserID.Find (userID);
	if (i!=-1)
	{
		oc_group.m_UserID.Del (i);
	}
	else 
	{
		SERVER_DEBUG_ERROR_2 ("Удаляемый из группы прав %s пользоваетль %s не найден в этой группе.", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
	}


	return ERR_OK;
}
//____________________________________________________________________________[]

















//______________________________________________________________________________
//                                                                            []
//` CreateUser                                                                []          
//                                                                            []
bool CreateUser (char* Login, char* Password, char* FullName, char* Email, char* Groups)
{
	MOD_User_Args arg;
	
	arg.Login					= Login;
	arg.Password				= Password;
	arg.PasswordConfirm		= Password;
	arg.FullName				= FullName;
	arg.Email					= Email;

	int AccessLevel = WEAKEST_ACCESS_LEVEL;
	if			(strcmp (Login, "root")==0)			AccessLevel = ROOT_ACCESS_LEVEL;
	else if	(strcmp (Login, "auditor")==0)		AccessLevel = ROOT_ACCESS_LEVEL+1;
	else if	(strcmp (Login, "anonymous")==0)		AccessLevel = ROOT_ACCESS_LEVEL+1;
	else														AccessLevel = USER_ACCESS_LEVEL;
	MOD_User_New (arg, AccessLevel);
	if (arg.ExitCode!=ERR_OK) 	{SERVER_DEBUG_ERROR_2 ("Не удалось зарегистрировать пользователя '%s'. %s", Login, arg.ExitCodeComment.c_str()); return false;}

	string		UserGroupsStr = Groups;
	string_arr	UserGroupsArr; UserGroupsStr.explode (UserGroupsArr, "|"); 
	FOR_EACH_ITEM_EVAL (UserGroupsArr,
	{
		UserGroupsArr[i].trim();
		if (!UserGroupsArr[i].IsEmpty())
		{
			if (AddUserToGroup (arg.objID, GetGroupID (UserGroupsArr[i]))!=ERR_OK)
			{
				return false;
			}
		}
	});
	return true;
}
//____________________________________________________________________________[]













/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Инициализация системы разграничения прав                                  []                                        
[]                                                                            []
[]____________________________________________________________________________[]
*/
bool InitializeSystemRights (const char * sRootPassword,  const char * sScriptPassword,  GROUP_INI * a_group_ini_arr, int a_group_ini_num,  USER_INI * a_user_ini_arr, int a_user_ini_num)
{
	DEBUG_STACK_NAME (InitializeSystemRights);

	int g, u;
	char ROOT_PASSWORD[1024];
	strcpy (ROOT_PASSWORD, sRootPassword);
	char SCRIPT_PASSWORD[1024];
	strcpy (SCRIPT_PASSWORD, sScriptPassword);

//----------------------------------------------------------------------------[] 
//	Системные группы
//----------------------------------------------------------------------------[] 
	GROUP_INI group_ini_arr[] = 
	{
		{
			"Root",
			"root",
			"Полный контроль над всей системой.",
			"Concept.Feod			[LRCWDMm]"
		},

		{
			"Аудитор",
			"auditor",
			"Просмотр всего что есть в системе, без права что-либо менять.",
			"Concept.Feod			[LR]"
		},

		{
			"Администратор",
			"administrator",
			"Назначение и изменение прав пользователям, создание и редактирование групп.",
			"Concept.Feod.Admin					[LRCWD]"
			"Concept.Feod.Data					[LRCWDMm]"
			"Concept.Feod.Aux						[LRCWD]"
			"Concept.Feod.Files					[LRCWDMm]"
			"Concept.Feod.Semantic.Admin		[LRCWDMm]"
			"Concept.Feod.Semantic.User		[LRCWDMm]"
		},

      {
         "Программист web-страниц",
         "websmith",
         "Изменение и редактирование набора скриптов и файлов, использующихся для формирования страничек сайта.",
         "Concept.Feod.Files.Site.Service.Scripts			[LRCWDMm]"
         "Concept.Feod.Files.Site.Public.Design				[LRCWDMm]"
         "Concept.Feod.Files.Site.Service.HTML-templates	[LRCWDMm]"
      },

      {
         "Скрипты",
         "script",
         "Права, которыми обладают скрипты сайта.",
			"Concept.Feod.Data.Service.Drafts					[C]"
			"Concept.Feod.Data.Type.Каталог						[C]"
      },

      {
         "Дизайнер сайта",
         "designer",
         "Изменение и редактирование набора файлов, использующихся для формирования страничек сайта.",
         "Concept.Feod.Files.Site.Public.Design				[LRCWDMm]"
         "Concept.Feod.Files.Site.Service.HTML-templates	[LRCWDMm]"
      },

		{ 
			"Зарегистрированный пользователь",
			"user",
			"Чтение общедоступной информации, создание и редактирование своих настроек.",
			"Concept.Feod.Data.Topic								[LR]"
			"Concept.Feod.Data.Type									[LR]"
			"Concept.Feod.Data.Type.Inbox							[LRC]"
			"Concept.Feod.Data.Service.Public					[LR]"
			"Concept.Feod.Data.Mark.Regular						[LR]"
			"Concept.Feod.Data.Mark.Hot							[LR]"
			"Concept.Feod.Admin.Feod								[C]"
			"Concept.Feod.Private									[m]"
			"Concept.Feod.Files.User								[m]"
			"Concept.Feod.Files.Site.Public						[LR]"
			"Concept.Feod.Files.Site.Public.Archive.Upload	[LRC]"
			"Concept.Feod.Aux.Sources								[L]"
			"Concept.Feod.Semantic									[LR]"
			"Concept.Feod.Semantic.User							[LRCWD]"
		},

		{
			"Анонимный посетитель",
			"anonymous",
			"Любой незарегистрированый или не прошедший авторизацию пользователь.",
			"Concept.Feod.Data.Topic								[LR]"
			"Concept.Feod.Data.Type									[LR]"
			"Concept.Feod.Data.Type.Inbox							[LRC]"
			"Concept.Feod.Data.Service.Public					[LR]"
			"Concept.Feod.Data.Mark.Regular						[LR]"
			"Concept.Feod.Data.Mark.Hot							[LR]"
			"Concept.Feod.Files.Site.Public						[LR]"
			"Concept.Feod.Files.Site.Public.Archive.Upload	[LRC]"
			"Concept.Feod.Aux.Sources								[L]"
			"Concept.Feod.Semantic									[LR]"
			"Concept.Feod.Semantic.User.Anonymous				[LRCWD]"
		},

	};
	int group_ini_num = sizeof (group_ini_arr)/sizeof (group_ini_arr[0]);
//----------------------------------------------------------------------------[] 
// Системные пользователи
//----------------------------------------------------------------------------[] 
	USER_INI user_ini_arr[]=
	{
		{
			"root",
			ROOT_PASSWORD,
			"Roman V. Koshelev",
			"root@roman.msk.ru",
			"Root|Аудитор|Администратор|Программист web-страниц|Скрипты|Дизайнер сайта|Анонимный посетитель"
		},
		{
			"auditor",
			"auditorpw",
			"Алексей Вершинин",
			"av@4me.ru",
			"Аудитор"
		},
		{
			"anonymous",
			"anonymous",
			"Незарегистрированный или неавторезированный пользователь",
			"",
			""
		},
		{
			"script",	
			SCRIPT_PASSWORD,
			"Все скрипты сайта, обращающиеся к базе данных",
			"",
			"Скрипты"
		}
	};
	int user_ini_num = sizeof (user_ini_arr)/sizeof (user_ini_arr[0]);
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
// Создание системных групп
	for (g=0; g<group_ini_num; g++)
	{
		ERR_RESULT gRes = CreateUserGroup (group_ini_arr[g].Name, group_ini_arr[g].Type, group_ini_arr[g].Description, SYSTEM_ACCESS_LEVEL, group_ini_arr[g].FeodAttr);
		if (gRes != ERR_OK){SERVER_DEBUG_ERROR_1 ("Ошибка создания группы: код ошибки %d", gRes); return false;}
	}
//----------------------------------------------------------------------------[] 
// Создание системных пользователей
	for (u=0; u<user_ini_num; u++)
	{
		if (!CreateUser (user_ini_arr[u].Login, user_ini_arr[u].Password, user_ini_arr[u].FullName, user_ini_arr[u].Email, user_ini_arr[u].Groups))
		{
			return false;
		}
	}
//----------------------------------------------------------------------------[] 
//	Создание проблемных групп
	for (g=0; g<a_group_ini_num; g++)
	{
		ERR_RESULT gRes = CreateUserGroup (a_group_ini_arr[g].Name, a_group_ini_arr[g].Type, a_group_ini_arr[g].Description, ROOT_ACCESS_LEVEL, a_group_ini_arr[g].FeodAttr);

		if (gRes != ERR_OK)
		{
			SERVER_DEBUG_ERROR_1 ("Ошибка создания группы: код ошибки %d", gRes);
			return false;
		}
	}
//----------------------------------------------------------------------------[] 
// Создание проблемных пользователей
	for (u=0; u<a_user_ini_num; u++)
	{
		if (!CreateUser (a_user_ini_arr[u].Login, a_user_ini_arr[u].Password, a_user_ini_arr[u].FullName, a_user_ini_arr[u].Email, a_user_ini_arr[u].Groups))
		{
			return false;
		}
	}
//----------------------------------------------------------------------------[] 


//	DEBUG_PRINT_CLASS (UserGroup);
//	DEBUG_PRINT_CLASS (User);

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка пользователей на принадлежность к группе                         []                                                 
//                                                                            []
bool IS_ROOT (identifier loginID)
{
	DEBUG_STACK_NAME (IS_ROOT);

	OC_User			oc_user(loginID);
	OC_UserGroup	oc_group;

	oc_group.SetIndex_Type ();
	identifier groupID = oc_group.Find ("root");

	return groupID!=NA && oc_user.m_GroupID.Find (groupID)!=-1;
}
//----------------------------------------------------------------------------[] 
bool IS_AUDITOR (identifier loginID)
{
	DEBUG_STACK_NAME (IS_AUDITOR);

	OC_User			oc_user(loginID);
	OC_UserGroup	oc_group;

	oc_group.SetIndex_Type ();
	identifier groupID = oc_group.Find ("auditor");

	return groupID!=NA && oc_user.m_GroupID.Find (groupID)!=-1;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` GetUserGUID                                                               []           
//                                                                            []
guid GetUserGUID (identifier userID)
{
	DEBUG_STACK_NAME (GetUserGUID);

	return OC_User(userID).GetObjectGUID();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` UserGetLoginFullName                                                      []                    
//                                                                            []
identifier UserGetLoginFullName (guid userGUID, string& login, string& name)
{
	DEBUG_STACK_NAME (UserGetLoginFullName);

	OC_User oc_user;
	oc_user.Open (userGUID);

	login = "";
	name	= "";

	if (OC_Exist (userGUID))
	{
		login	= oc_user.m_Login;
		name	= oc_user.m_FullName;			
		return oc_user.GetObjectID ();
	}
	
	return NA;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
