/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoDiv.h																[]
[] Date:          13.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с разделами информации.										[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoDiv_h
#define MOD_InfoDiv_h


#define MAX_INFODIV_ENUMERATE_NUM	100


extern int CACHE_NUM_InfoDivGetAllSubDivIDs;


//______________________________________________________________________________
//                                                                            []
//` Разделы информации																			[]
//                                                                            []
struct MOD_InfoDiv_Args
{
	MOD_InfoDiv_Args()
	{
		objID						=	NA;
		ExitCode					=	-1;
		ParentID					=	NA;
		AccessLevelThreshold	=	0;
		TotalStoredNum			=	0;
		objFirstNo				=	0;
		IncludeParent			=	true;
		objLastNo				=	INT_MAX;
		MaxNumInQuery			=  MAX_INFODIV_ENUMERATE_NUM;
		FullNameLevel			=	3;
	}

	string			Login;
	string			Password;
	identifier		objID;
	string			Name;
	string			Description;
	identifier		ParentID;
	string			ParentName;
	int				AccessLevelThreshold;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objTypes;
	string_arr		objDescriptions;
	int_arr			objLevels;
	int_arr			objAccessLevelThresholds;
	identifier_arr objFeodIDs;
	string			FeodAttributes;

	int				FullNameLevel;

	int				objFirstNo;
	int				objLastNo;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	bool				IncludeParent;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_InfoDiv_New			(MOD_InfoDiv_Args& arg);
ERR_RESULT		MOD_InfoDiv_Enumerate	(MOD_InfoDiv_Args& arg);
ERR_RESULT		MOD_InfoDiv_GetData		(MOD_InfoDiv_Args& arg);
ERR_RESULT		MOD_InfoDiv_PutData		(MOD_InfoDiv_Args& arg);
ERR_RESULT		MOD_InfoDiv_Delete		(MOD_InfoDiv_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool				CHECK_INFODIV_ID						(identifier divID);
identifier		GetInfoDivIDByType					(const char * Type);
identifier		GetInfoDivIDByFeodID					(identifier feodID);
identifier		GetFeodIDByInfoDivID					(identifier divID);
bool				GetInfoDivFullName					(identifier divID, string& divName, int FullNameLevel=3);
void				InfoDivGetAllSubDivIDs				(identifier divID, identifier_arr& subDivIDs);
void				InfoDivGetAllInfoObjectSortedIDs	(identifier divID, identifier_arr_arr& infoObjIDs);
ERR_RESULT		USER_CHECK_ACCESS_TO_INFODIV		(identifier userID, identifier divID, const string& Attributes);
bool				GetInfoDivType							(identifier divID, string& divType);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/