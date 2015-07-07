/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFile.h																[]
[] Date:          4.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с файлами.															[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_WebFile_h
#define MOD_WebFile_h


#define MAX_WEBFILE_ENUMERATE_NUM	1000

//______________________________________________________________________________
//                                                                            []
//` Разделы информации																			[]
//                                                                            []
struct MOD_WebFile_Args
{ 
	MOD_WebFile_Args()
	{
		objID						=	NA;
		ExitCode					=	-1;
		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		UpdateStatistics		=	false;

		CreationTime			=	0;
		folderID					=	NA;
		
		OwnerID					=	NA;

		NeedBinaryData			=	true;
		NeedPlainTextData		=	true;

		StatShow					=	0;
		StatClick				=	0;
		StatCTR					=	0.0;

		ContentChanged			=	false;


		MaxNumInQuery			=	MAX_USER_ENUMERATE_NUM;
	}

	string			Login;
	string			Password;
	identifier		objID;
	identifier_arr	folderIDs;
	string_arr		folderNames;
	string			Name;
	string			Name_Upload;
	string			Name_OS;
	int				Version;
	string			OS_Path;
	string			OS_Ext;
	string			MIMEType;
	string			IconType;
	string			PlainTextData;
	byte_arr			BinaryData;

	identifier		folderID;
	string			folderName;

	string			Description;

	bool				NeedBinaryData;
	bool				NeedPlainTextData;
	bool				ContentChanged;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objOSNames;
	string_arr		objIconTypes;
	string_arr		objDescriptions;
	int_arr			objCreationTimes;

	int_arr			objStatShows;
	int_arr			objStatClicks;
	float_arr		objStatCTRs;


	int				StatShow;
	int				StatClick;
	float				StatCTR;



	bool				UpdateStatistics;

	time_t			CreationTime;

	identifier		OwnerID;

	int				TotalStoredNum;
	int				MaxNumInQuery;
	int				objFirstNo;
	int				objLastNo;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_WebFile_New					(MOD_WebFile_Args& arg);
ERR_RESULT		MOD_WebFile_Enumerate			(MOD_WebFile_Args& arg);
ERR_RESULT		MOD_WebFile_GetData				(MOD_WebFile_Args& arg);
ERR_RESULT		MOD_WebFile_PutData				(MOD_WebFile_Args& arg);
ERR_RESULT		MOD_WebFile_Delete				(MOD_WebFile_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
ERR_RESULT		USER_CHECK_ACCESS_TO_WEBFILE	(identifier userID, identifier fileID, const string& Attributes);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/