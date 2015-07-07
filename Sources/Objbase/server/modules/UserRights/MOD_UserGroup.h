/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserGroup.h	                                          []
[] Date:          01.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:	Работа с группами прав пользователей								[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_UserGroup_h
#define MOD_UserGroup_h


#define MAX_GROUP_ENUMERATE_NUM	100


//______________________________________________________________________________
//                                                                            []
//` Группа прав пользователей                                                 []
//                                                                            []
struct MOD_UserGroup_Args
{ 
	MOD_UserGroup_Args()
	{
		objID						=	NA;
		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		ExitCode					=	-1;
		ReadOnly					=	true;
		CreationTime			=  0;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	0;
		AccessLevelThreshold	=	0;
		UserTotalStoredNum	=	0;
		UserMaxNumInQuery		=	0;
		UserFirstNo				=	0;
		UserLastNo				=	INT_MAX;
	}

	identifier		objID;
	bool				ReadOnly;
	string			Login;
	string			Password;
	string			Name;
	string			Description;
	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objTypes;
	int_arr			objAccessLevelThresholds;
						
	int				objFirstNo;
	int				objLastNo;

	int				AccessLevelThreshold;
	
	identifier_arr	FeodIDs;
	string_arr		FeodNames;
	string_arr		FeodAttributes;
	string			Type;


	identifier_arr	UserIDs;
	string_arr		UserLogins;
	string_arr		UserFullNames;
	int_arr			UserAccessLevels;
	int_arr			UserCreationTime;
	int_arr			UserCreationTimes;

	time_t			CreationTime;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	int				UserTotalStoredNum;
	int				UserMaxNumInQuery;
	int				UserFirstNo;
	int				UserLastNo;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_UserGroup_New			(MOD_UserGroup_Args& arg);
ERR_RESULT		MOD_UserGroup_Enumerate	(MOD_UserGroup_Args& arg);
ERR_RESULT		MOD_UserGroup_GetData	(MOD_UserGroup_Args& arg);
ERR_RESULT		MOD_UserGroup_PutData	(MOD_UserGroup_Args& arg);
ERR_RESULT		MOD_UserGroup_Delete		(MOD_UserGroup_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//----------------------------------------------------------------------------[] 
ERR_RESULT		CreateUserGroup				(const char* Name, const char* Type, const char* Description, int AccessLevelThreshold, const char* sFeodAttr);
identifier		GetGroupID						(const char* Name, bool JustCheck=false);
identifier		GetGroupIDByType				(const char* Type);
const char *	GetGroupRights					(identifier groupID, bool bExpand);
void				AddRootsToGroup				(identifier groupID, identifier loginID);
void				UserGroupSimplifyRightsSet	(identifier groupID);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/