/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserProfile.h															[]
[] Date:          11.�������.2000															[]
[] Author:        Roman V. Koshelev, Ekaterina B. Loupacheva 						[]
[] Description:   ������ � ����������� � �������������� ������� �������������	[]
[]						�������� ������������ � ������ ��������.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_UserProfile_h
#define MOD_UserProfile_h


#define MAX_USERPROFILE_ENUMERATE_NUM	100

//[]Sonora
//----------------------------------------------------------------------------[] 
// ���� ���������, ���������� �������������-���������� ������� � ����.
#define USER_LOG_first_bad		0
#define USER_LOG_CREATE			1
#define USER_LOG_PUBLIC			2
#define USER_LOG_FORBID			3
#define USER_LOG_CHANGENAME	4
#define USER_LOG_CHANGETEXT	5
#define USER_LOG_ADDTOPIC		6
#define USER_LOG_DELTOPIC		7
#define USER_LOG_CHANGEDESC	8
#define USER_LOG_REGULAR		9
#define USER_LOG_HOT				10
#define USER_LOG_last_bad		11
//----------------------------------------------------------------------------[] 
// ����������� ����� ���������, ���������� ������������� � ����.
static char * USER_LOG_DESCRIPTION [] = 
{
	"{{ERROR}}",
	"��������",
	"����������",
	"����������",
	"��������� ���������",
	"��������� ����������",
	"���������� ��������",
	"�������� ��������",
	"��������� ���������",
	"������� ��������",
	"������� ��������",
	"{{ERROR}}"
};
//----------------------------------------------------------------------------[] 





//______________________________________________________________________________
//                                                                            []
//` ��������� ��� ��������������� ��������� ������ UserProfile						[]
//                                                                            []
struct MOD_UserProfile_Args
{ 
	MOD_UserProfile_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_USERPROFILE_ENUMERATE_NUM;
		ReadOnly					=	false;

		ExitCode					=	-1;
	}

	string			Login;
	string			Password;

	identifier		objID;
	string			Name;
	bool				ReadOnly;

	identifier_arr	objIDs;
	string_arr		objNames;
	
	int				objFirstNo;
	int				objLastNo;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	identifier_arr Log_ObjectClassIDs;
   string_arr     Log_ObjectClassNames;	
   identifier_arr Log_ObjectIDs;		
   string_arr     Log_ObjectNames;		  
   int_arr        Log_ActionCodes;			
   string_arr     Log_ActionDescriptions;
   int_arr        Log_Times;	

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` ������������ �������                                                      []                    
//                                                                            []
ERR_RESULT		MOD_UserProfile_GetData			(MOD_UserProfile_Args& arg);
ERR_RESULT		MOD_UserProfile_PutData			(MOD_UserProfile_Args& arg);
ERR_RESULT		MOD_UserProfile_Delete			(MOD_UserProfile_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ��������������� �������                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool				CHECK_USERPROFILE_ID							(identifier profileID);
bool				CHECK_USERPROFILE_GUID						(guid			profileGUID);
ERR_RESULT		USER_CHECK_ACCESS_TO_USERPROFILE			(identifier loginID, identifier userID, const string& Attributes);
identifier		GetUserProfileIDByUserID					(identifier userID);
bool				UserProfileLogUpdate							(identifier userID, int Action, guid objGUID, int Time);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/