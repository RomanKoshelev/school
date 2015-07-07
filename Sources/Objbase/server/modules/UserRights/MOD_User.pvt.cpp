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
[] Description:	������ � ��������������													[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_User.inc.h"

bool IGNORE_AUTHORIZATION = false;                                                               
//______________________________________________________________________________
//                                                                            []
//` ������� ����������� ������                                                []                          
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
//` ����� ������������ �� ������                                              []                            
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
//` �������� ������ ������������                                              []                            
//                                                                            []
ERR_RESULT USER_CHECK_LOGIN_PASSWORD (const char * Login, const char * Password, identifier& userID, bool * pPasswordInBrowser)
{
	DEBUG_STACK_NAME (USER_CHECK_LOGIN_PASSWORD);

// ������� ������������ �� ������
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

// ���� ������ ����� ����, ��� � ������������, ��� ����� ���� ����������������� ��� ����� ���� �������, �� ��� ��.
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
//`	�������� ���� ������� � ��������																				   []                                
//																																	[]
//-------------------------------------------------------------------------------------------------[]
ERR_RESULT	USER_CHECK_ACCESS (				//	== ExitCode															[]
				const	char *	Login, 			//	>> �����																[]
				const	char *	Password,		//	>> ������															[]
				const	char *	Feod, 			//	>> ���� �������, ��������� ��� ��������.					[]
				const	char *	Attrib, 			//	>> �������� �������� ������� [C][L][R][W][D]				[]
				identifier *	pLoginID) 		//	<< ID ������														[]
//-------------------------------------------------------------------------------------------------[]
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS);

	identifier feodID = GetFeodIDByType (Feod);
	if (!IGNORE_AUTHORIZATION && feodID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("��� ����� ���� ����: %s", Feod);
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
			SERVER_DEBUG_ERROR_2 ("������ �������������� ������� [%c] � ������ ��������� %s", Attrib[i], Attrib);
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
//`	�������� ���� ������� � ��������																				   []                                
//																																	[]
//-------------------------------------------------------------------------------------------------[]
void	USER_CHECK_ACCESS(						//	== ExitCode															[]
				identifier		userID, 			//	<< ������������													[]
				identifier		feodID, 			//	<< ���� �������													[]
				const	char *	Attrib, 			//	<< �������� �������� ������� [C][L][R][W][D][M]			[]
				int&			Res) 					//	>> ���������														[]
//-------------------------------------------------------------------------------------------------[]
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS);
	IF_CACHED_ARGS_4_RETURN_VOID (10*1000, userID, feodID, Attrib, CACHE_NUM_USER_CHECK_ACCESS);
	// !!! ������� ��� ������������ ������� �������������� ����� � config

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

// ��������� � ������ ����� �������
	if (oc_user.m_OwnFeodID.Find (feodID)!=-1)
	{
		Res = ERR_OK;
	}

// ���������� �� ���� �������
	for (int g=0; Res!=ERR_OK && g<oc_user.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_user.m_GroupID[g];

	// ������ ����������
		if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("������������ ������ ���� %d � ������������ %s [%d]. ����������.", (identifier)oc_user.m_GroupID[g], ((string)oc_user.m_Login).c_str(), userID);
			oc_user.m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

	// ������������ �� ��������� � ������
		if (oc_group.m_UserID.Find(userID)==-1)
		{
			SERVER_DEBUG_ERROR_4 ("������������ %s [%d] �� ��������� � ������ %s [%d]. ����������.", ((string)oc_user.m_Login).c_str(), userID, ((string)oc_group.m_Name).c_str(), groupID);
			oc_user.m_GroupID.Del (g);
			g--;
			continue;
		}

	// ���������� �� ������ ������ (=����������=������)
		for (int f=0; Res!=ERR_OK && f<oc_group.m_Rights_Feod.Size(); f++)
		{
			identifier group_feodID = oc_group.m_Rights_Feod[f];

		// ���� ����������
			if (!CHECK_FEOD_ID(group_feodID))
			{
				SERVER_DEBUG_ERROR_3 ("������������ ���� %d � ������ %s [%d]. ����������.", int (oc_group.m_Rights_Feod[f]), ((string)oc_group.m_Name).c_str(), int (oc_user.m_GroupID[g]));
				oc_group.m_Rights_Feod.Del	(f);
				oc_group.m_Rights_Attr.Del	(f);
				f--;
				continue;
			}

		// ���������, ����� �� ����� ������� ���� ��� ��� ������ (�.�. �������� ���� ����� ������� ����� ������)
			if (group_feodID==feodID || FeodHasChild (group_feodID, feodID))
			{
				int	nAttrib	= strlen(Attrib);
				int	a;

			// ��������� ��� ����������� �������� �����
				for (a=0; a<nAttrib; a++)
				{
				// ������� ��� ������
					if (ATTR.Find(Attrib[a])!=-1)
					{
						continue;
					}

				// ������� ������� ��� �������������� ����� ������, ���������� ���
					if ((Attrib[a]<'a' || group_feodID==feodID) && string(oc_group.m_Rights_Attr[f]).Find(Attrib[a])!=-1)
					{
						ATTR += Attrib[a];
					}
					else if (string(oc_group.m_Rights_Attr[f]).Find(char(Attrib[a]-32))!=-1)
					{
					// ������ ����� ������� ������� (������ [m], � ���� [M])
						ATTR += Attrib[a];
					}
				}

			// ���������, ��� ��� �������� �������
				bool bContinue = false;
				for (a=0; a<nAttrib && !bContinue; a++) 
				{
					if (((CPtr<char>)ATTR).Find(Attrib[a])==-1)
					{
					// ��� �� ��� �������� �������
						bContinue = true;
					}
				}
			// ��� �������� �������
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
//` ���������� ������������ � ������                                          []                                
//                                                                            []
ERR_RESULT AddUserToGroup (identifier userID, identifier groupID)
{
	DEBUG_STACK_NAME (AddUserToGroup);

// ������� ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("���������� ������������� ������ %d", groupID);
		return ERR_BadID;
	}
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		SERVER_DEBUG_ERROR_1 ("���������� ������������� ������������ %d", userID);
		return ERR_BadID;
	}

	OC_User			oc_user	(userID);
	OC_UserGroup	oc_group	(groupID);

	if (oc_user.m_GroupID.Find (groupID)!=-1)
	{
		SERVER_DEBUG_ERROR_2 ("������������ %s ��� �������� � ������� ������ %s", ((string)oc_user.m_Login).c_str(), ((string)oc_group.m_Name).c_str());
	}
	else if (oc_group.m_UserID.Find (userID)!=-1)
	{
		SERVER_DEBUG_ERROR_2 ("������ ���� %s ��� ��������� � ����� ���������� ������������ %s", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
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
//` �������� ������������ �� ������	                                          []                                
//                                                                            []
ERR_RESULT RemoveUserFromGroup (identifier userID, identifier groupID)
{
	DEBUG_STACK_NAME (RemoveUserFromGroup);

// ������� ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("���������� ������������� ������ %d", groupID);
		return ERR_BadID;
	}
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		SERVER_DEBUG_ERROR_1 ("���������� ������������� ������������ %d", userID);
		return ERR_BadID;
	}

	OC_User			oc_user	(userID);
	OC_UserGroup	oc_group	(groupID);
	int i;


// ������� ������ �� ������� ���� ������������
	i = oc_user.m_GroupID.Find (groupID);
	if (i!=-1)
	{
		oc_user.m_GroupID.Del (i);
	}
	else 
	{
		SERVER_DEBUG_ERROR_2 ("��������� ������ ���� %s �� ������� � ������������ %s", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
	}

// ������� ������������ �� ������� ������ ������
	i = oc_group.m_UserID.Find (userID);
	if (i!=-1)
	{
		oc_group.m_UserID.Del (i);
	}
	else 
	{
		SERVER_DEBUG_ERROR_2 ("��������� �� ������ ���� %s ������������ %s �� ������ � ���� ������.", ((string)oc_group.m_Name).c_str(), ((string)oc_user.m_Login).c_str());
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
	if (arg.ExitCode!=ERR_OK) 	{SERVER_DEBUG_ERROR_2 ("�� ������� ���������������� ������������ '%s'. %s", Login, arg.ExitCodeComment.c_str()); return false;}

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
[]` ������������� ������� ������������� ����                                  []                                        
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
//	��������� ������
//----------------------------------------------------------------------------[] 
	GROUP_INI group_ini_arr[] = 
	{
		{
			"Root",
			"root",
			"������ �������� ��� ���� ��������.",
			"Concept.Feod			[LRCWDMm]"
		},

		{
			"�������",
			"auditor",
			"�������� ����� ��� ���� � �������, ��� ����� ���-���� ������.",
			"Concept.Feod			[LR]"
		},

		{
			"�������������",
			"administrator",
			"���������� � ��������� ���� �������������, �������� � �������������� �����.",
			"Concept.Feod.Admin					[LRCWD]"
			"Concept.Feod.Data					[LRCWDMm]"
			"Concept.Feod.Aux						[LRCWD]"
			"Concept.Feod.Files					[LRCWDMm]"
			"Concept.Feod.Semantic.Admin		[LRCWDMm]"
			"Concept.Feod.Semantic.User		[LRCWDMm]"
		},

      {
         "����������� web-�������",
         "websmith",
         "��������� � �������������� ������ �������� � ������, �������������� ��� ������������ ��������� �����.",
         "Concept.Feod.Files.Site.Service.Scripts			[LRCWDMm]"
         "Concept.Feod.Files.Site.Public.Design				[LRCWDMm]"
         "Concept.Feod.Files.Site.Service.HTML-templates	[LRCWDMm]"
      },

      {
         "�������",
         "script",
         "�����, �������� �������� ������� �����.",
			"Concept.Feod.Data.Service.Drafts					[C]"
			"Concept.Feod.Data.Type.�������						[C]"
      },

      {
         "�������� �����",
         "designer",
         "��������� � �������������� ������ ������, �������������� ��� ������������ ��������� �����.",
         "Concept.Feod.Files.Site.Public.Design				[LRCWDMm]"
         "Concept.Feod.Files.Site.Service.HTML-templates	[LRCWDMm]"
      },

		{ 
			"������������������ ������������",
			"user",
			"������ ������������� ����������, �������� � �������������� ����� ��������.",
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
			"��������� ����������",
			"anonymous",
			"����� ������������������� ��� �� ��������� ����������� ������������.",
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
// ��������� ������������
//----------------------------------------------------------------------------[] 
	USER_INI user_ini_arr[]=
	{
		{
			"root",
			ROOT_PASSWORD,
			"Roman V. Koshelev",
			"root@roman.msk.ru",
			"Root|�������|�������������|����������� web-�������|�������|�������� �����|��������� ����������"
		},
		{
			"auditor",
			"auditorpw",
			"������� ��������",
			"av@4me.ru",
			"�������"
		},
		{
			"anonymous",
			"anonymous",
			"�������������������� ��� ������������������ ������������",
			"",
			""
		},
		{
			"script",	
			SCRIPT_PASSWORD,
			"��� ������� �����, ������������ � ���� ������",
			"",
			"�������"
		}
	};
	int user_ini_num = sizeof (user_ini_arr)/sizeof (user_ini_arr[0]);
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
// �������� ��������� �����
	for (g=0; g<group_ini_num; g++)
	{
		ERR_RESULT gRes = CreateUserGroup (group_ini_arr[g].Name, group_ini_arr[g].Type, group_ini_arr[g].Description, SYSTEM_ACCESS_LEVEL, group_ini_arr[g].FeodAttr);
		if (gRes != ERR_OK){SERVER_DEBUG_ERROR_1 ("������ �������� ������: ��� ������ %d", gRes); return false;}
	}
//----------------------------------------------------------------------------[] 
// �������� ��������� �������������
	for (u=0; u<user_ini_num; u++)
	{
		if (!CreateUser (user_ini_arr[u].Login, user_ini_arr[u].Password, user_ini_arr[u].FullName, user_ini_arr[u].Email, user_ini_arr[u].Groups))
		{
			return false;
		}
	}
//----------------------------------------------------------------------------[] 
//	�������� ���������� �����
	for (g=0; g<a_group_ini_num; g++)
	{
		ERR_RESULT gRes = CreateUserGroup (a_group_ini_arr[g].Name, a_group_ini_arr[g].Type, a_group_ini_arr[g].Description, ROOT_ACCESS_LEVEL, a_group_ini_arr[g].FeodAttr);

		if (gRes != ERR_OK)
		{
			SERVER_DEBUG_ERROR_1 ("������ �������� ������: ��� ������ %d", gRes);
			return false;
		}
	}
//----------------------------------------------------------------------------[] 
// �������� ���������� �������������
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
//` �������� ������������� �� �������������� � ������                         []                                                 
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
