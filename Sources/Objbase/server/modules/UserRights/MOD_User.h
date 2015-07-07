/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            MOD_User.h                                                []
[] Date:            28.06.2000                                                []
[] Author:          Roman V. Koshelev														[]
[] Description:     ������ � ��������������                                   []
[]____________________________________________________________________________[]
*/
#ifndef MOD_User_h
#define MOD_User_h


#define	SYSTEM_ACCESS_LEVEL			0				// ��������� ������� ������� 
#define	ROOT_ACCESS_LEVEL				1				// ������� ������� ������ �������� ������
#define	ADMIN_ACCESS_LEVEL			10				// ������� �� ��������� �������������� 
#define	USER_ACCESS_LEVEL				100000		// ������� ������� �� ��������� �������� �����
#define	WEAKEST_ACCESS_LEVEL			1000000		// ����� ������ ������� �������
#define	FORBIDDEN_ACCESS_LEVEL		10000000		// ����������� ������� �������

#define  MAX_USER_ENUMERATE_NUM		500			// ����. ����� ������, ������������� �� ���� ���

extern int	CACHE_NUM_USER_CHECK_ACCESS;
extern bool	IGNORE_AUTHORIZATION;
//______________________________________________________________________________
//                                                                            []
//` User                                                                      []    
//                                                                            []
struct MOD_User_Args
{ 
	MOD_User_Args()
	{
		objID					=	NA;
		objFirstNo			=	0;
		objLastNo			=	INT_MAX;
		PasswordInBrowser	=	false;
		ReadOnly				=	true;
		LoginAccessLevel	=	FORBIDDEN_ACCESS_LEVEL;
		ObjAccessLevel		=	FORBIDDEN_ACCESS_LEVEL;
		AccessLevel			=	FORBIDDEN_ACCESS_LEVEL;
		CreationTime		=  0;

		ExpandRights		=	false;
		ExpandGroups		=	true;

		TotalStoredNum		=	0;
		MaxNumInQuery		=	0;
		ExitCode				=	-1;
	}

	identifier		objID;
	string			Login;
	string			Password;
	string			PasswordConfirm;
	bool				PasswordInBrowser;
	string			FullName;
	string			Email;
	string			Data;
	int				AccessLevel;
	string			URL;
	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objFullNames;
						
	int				objFirstNo;
	int				objLastNo;
	bool				ReadOnly;

	bool				ExpandRights;
	bool				ExpandGroups;
	

	string			NewPassword;
	string			NewPasswordConfirm;

	int				LoginAccessLevel;
	int				ObjAccessLevel;
	identifier_arr	LoginGroupIDs;
	string_arr		LoginGroupNames;
	string_arr		LoginGroupTypes;
	string_arr		LoginGroupRights;
	string			LoginOwnRights;
	identifier_arr	ObjGroupIDs;

	string_arr		FeodNames;
	string_arr		FeodAttributes;
	bool_arr			Accesses;
	int				TotalStoredNum;
	int				MaxNumInQuery;
	time_t			CreationTime;

	int				ExitCode;
	string			ExitCodeComment;
};
//----------------------------------------------------------------------------[]


//______________________________________________________________________________
//                                                                            []
//` ������������ �������                                                      []                    
//                                                                            []
ERR_RESULT MOD_User_New					(MOD_User_Args& arg, int AccessLevel=USER_ACCESS_LEVEL);
ERR_RESULT MOD_User_Authorize			(MOD_User_Args& arg);
ERR_RESULT MOD_User_Enumerate			(MOD_User_Args& arg);
ERR_RESULT MOD_User_GetData			(MOD_User_Args& arg);
ERR_RESULT MOD_User_PutData			(MOD_User_Args& arg);
ERR_RESULT MOD_User_Delete				(MOD_User_Args& arg);
ERR_RESULT MOD_User_GetRights			(MOD_User_Args& arg);
ERR_RESULT MOD_User_PutRights			(MOD_User_Args& arg);
ERR_RESULT MOD_User_CheckOwnRights	(MOD_User_Args& arg);
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ��������������� �������                                                   []                       
//                                                                            []
struct GROUP_INI	{char* Name; char* Type; char* Description; char* FeodAttr;};
struct USER_INI	{char* Login; char* Password; char* FullName; char* Email; char* Groups;};
//----------------------------------------------------------------------------[] 
bool			InitializeSystemRights		(const char * sRootPassword, const char * sScriptPassword, GROUP_INI * a_group_ini_arr, int a_group_ini_num,  USER_INI * a_user_ini_arr, int a_user_ini_num);
identifier	FindUserByLogin				(const char * Login);
ERR_RESULT	USER_CHECK_ACCESS				(const char * Login, const char * Password, const char * Feod, const char * Attrib, identifier* pLoginID=NULL);
ERR_RESULT	USER_CHECK_ACCESS				(identifier loginID, identifier feodID, const char * Attrib);
ERR_RESULT	USER_CHECK_LOGIN_PASSWORD	(const char * Login, const char * Password, identifier& userID, bool * pPasswordInBrowser=NULL);
ERR_RESULT	AddUserToGroup					(identifier userID,  identifier groupID);
ERR_RESULT	RemoveUserFromGroup			(identifier userID,  identifier groupID);
bool			CHECK_ATTRIBUTES				(const char *Attrib);
guid			GetUserGUID						(identifier userID);
bool			IS_ROOT							(identifier loginID);
bool			IS_AUDITOR						(identifier loginID);
identifier	UserGetLoginFullName			(guid userGUID, string& login, string& name);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/