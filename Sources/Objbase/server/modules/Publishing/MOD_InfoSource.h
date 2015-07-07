/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoSource.h															[]
[] Date:          21.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса InfoSource								[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoSource_h
#define MOD_InfoSource_h


#define MAX_INFOSOURCE_ENUMERATE_NUM	500

//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса InfoSource						[]
//                                                                            []
struct MOD_InfoSource_Args
{ 
	MOD_InfoSource_Args()
	{
		objID				=	NA;

		objFirstNo		=	0;
		objLastNo		=	INT_MAX;
		TotalStoredNum	=	0;
		MaxNumInQuery	=	MAX_INFOSOURCE_ENUMERATE_NUM;

		RefreshType		=	0;
		divID				=	NA;
		ShowAll			=	false;

		ShowCount		=	0;
		ClickCount		=	0;
		CTR				=	0.0;

		ExitCode			=	-1;
	}

	string			Login;
	string			Password;

	identifier		objID;
	string			Name;
	string			Description;
	string			URL;
	int				RefreshType;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objDescriptions;
	string_arr		objURLs;
	int_arr			objRefreshTypes;

	
	identifier		divID;
	string			divName;
	identifier_arr	divIDs;
	string_arr		divNames;
	bool				ShowAll;

	int				ShowCount;
	int				ClickCount;
	float				CTR;

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
ERR_RESULT		MOD_InfoSource_New				(MOD_InfoSource_Args& arg);
ERR_RESULT		MOD_InfoSource_Enumerate		(MOD_InfoSource_Args& arg);
ERR_RESULT		MOD_InfoSource_GetData			(MOD_InfoSource_Args& arg);
ERR_RESULT		MOD_InfoSource_PutData			(MOD_InfoSource_Args& arg);
ERR_RESULT		MOD_InfoSource_Delete			(MOD_InfoSource_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
struct INFOSOURCE_INI			{char* Name; char* Description; char* URL; int RefreshType; char* DivName;};
bool	GetInfoSourceNameURL		(identifier srcID, string& Name, string& URL);
bool	InitializeInfoSources	(const char * sRootPassword, INFOSOURCE_INI* ini_arr, int ini_num);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/