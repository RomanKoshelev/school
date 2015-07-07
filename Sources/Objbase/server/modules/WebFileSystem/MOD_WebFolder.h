/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFolder.h															[]
[] Date:          31.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с web-файловыми директориями									[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_WebFolder_h
#define MOD_WebFolder_h


#define MAX_WEBFOLDER_ENUMERATE_NUM	500

//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса WebFolder						[]
//                                                                            []
struct MOD_WebFolder_Args
{ 
	MOD_WebFolder_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_WEBFOLDER_ENUMERATE_NUM;
		ReadOnly					=	false;

		ParentID					=	NA;
		AccessLevelThreshold	=	0;

		FullNameLevel			=	INT_MAX;
		IncludeParent			=	true;
		AllDescendants			=	false;

		ExitCode					=	-1;
	}

	string			Login;
	string			Password;

	identifier		objID;
	string			Name;
	string			FullName;
	string			Description;
	identifier		ParentID;
	string			ParentName;
	bool				ReadOnly;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objTypes;
	int_arr			objLevels;
	int				AccessLevelThreshold;


	bool				IncludeParent;
	bool				AllDescendants;
	string			FeodAttributes;
	int				FullNameLevel;

	identifier_arr	GroupIDs;
	string_arr		GroupAttributes;

	int				objFirstNo;
	int				objLastNo;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_WebFolder_New				(MOD_WebFolder_Args& arg);
ERR_RESULT		MOD_WebFolder_Enumerate		(MOD_WebFolder_Args& arg);
ERR_RESULT		MOD_WebFolder_GetData		(MOD_WebFolder_Args& arg);
ERR_RESULT		MOD_WebFolder_PutData		(MOD_WebFolder_Args& arg);
ERR_RESULT		MOD_WebFolder_Delete			(MOD_WebFolder_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool			CHECK_WEBFOLDER_ID					(identifier folderID);
bool			CHECK_WEBFOLDER_GUID					(identifier folderGUID);
identifier	GetWebFolderIDByFeodID				(identifier feodID);
identifier	GetFeodIDByWebFolderID				(identifier folderID);
bool			GetWebFolderFullName					(identifier folderID, string& folderName, int FullNameLevel=3);
bool			GetWebFolderType						(identifier folderID, string& folderType);
identifier	GetWebFolderIDByType					(const char * folderType);
void			WebFolderGetWebFileSortedIDs		(identifier folderID, identifier_arr& fileIDs);
ERR_RESULT	USER_CHECK_ACCESS_TO_WEBFOLDER	(identifier userID, identifier folderID, const char * Attributes);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/