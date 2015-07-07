/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Feod.h																	[]
[] Date:          07.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с зонами доступа, концептами ветви {Concept.Feod})	[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_Feod_h
#define MOD_Feod_h


#define MAX_FEOD_ENUMERATE_NUM	100
#define	ALL_ATTRIBUTES				"CLRWDmM"

//______________________________________________________________________________
//                                                                            []
//` Зоны доступа																					[]
//                                                                            []
struct MOD_Feod_Args
{ 
	MOD_Feod_Args()
	{
		objID						=	NA;
		ExitCode					=	-1;
		ParentID					=	NA;
		AccessLevelThreshold	=	0;
	}

	string			Login;
	string			Password;
	identifier		objID;
	string			Name;
	string			Type;
	string			Description;
	identifier		ParentID;
	string			ParentName;
	int				AccessLevelThreshold;
						
	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objTypes;
	string_arr		objDescriptions;
	identifier_arr	objParentIDs;
	int_arr			objThresholds;
	string_arr		objExtClassNames;
	identifier_arr	objExtIDs;		

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_Feod_New			(MOD_Feod_Args& arg);
ERR_RESULT		MOD_Feod_Enumerate	(MOD_Feod_Args& arg);
ERR_RESULT		MOD_Feod_GetData		(MOD_Feod_Args& arg);
ERR_RESULT		MOD_Feod_PutData		(MOD_Feod_Args& arg);
ERR_RESULT		MOD_Feod_Delete		(MOD_Feod_Args& arg);
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
bool				CHECK_FEOD_ID					(identifier feodID);
bool				GetFeodName						(identifier feodID, string& objName);
bool				GetFeodFullName				(identifier feodID, string& objName, int nLevel=1, const char* sDelimiter="::");
int				GetFeodLevel					(identifier feodID);
identifier		GetFeodIDByName				(const char * Name);
identifier		GetFeodIDByType				(const char * Type);
bool				FeodHasChild					(identifier feodID, identifier childID);
bool				GetAllFeodChilds				(identifier feodID, identifier_arr& childIDs);
bool				GetFeodDescendantIDs			(identifier feodID, identifier_arr& DescendantIDs);
identifier		GetFeodParentID				(identifier feodID);
void				GetFeodType						(identifier feodID, string& Type);
void				MOD_CHECK_ACCESS				(identifier userID, guid_arr& objGUIDs, const char * Attributes);
bool				MOD_CHECK_ACCESS				(identifier userID, guid objGUID, const char * Attributes);
void				MOD_CHECK_PLACEMENT			(identifier_arr& feodIDs, guid_arr& objGUIDs);
void				MOD_CHECK_ACCESS_PLACEMENT	(identifier userID, guid_arr& objGUIDs, const char * Attributes, identifier_arr& feodIDs, int nMaxFound);
const char *	MOD_GET_OBJECT_NAME			(guid& gi);
const char *	MOD_GET_OBJECT_DESCRIPTION (guid& gi);
void				FIX_FEODS						(void);
void				GetFeodGUIDs					(identifier_arr& FeodIDs, guid_arr& FeodGUIDs);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/