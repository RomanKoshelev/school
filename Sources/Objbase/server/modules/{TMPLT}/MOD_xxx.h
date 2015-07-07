/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_xxx.h																	[]
[] Date:          ddd.2000																		[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса xxx											[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_xxx_h
#define MOD_xxx_h


#define MAX_XXX_ENUMERATE_NUM	100

//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса xxx								[]
//                                                                            []
struct MOD_xxx_Args
{ 
	MOD_xxx_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_XXX_ENUMERATE_NUM;
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

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_xxx_New				(MOD_xxx_Args& arg);
ERR_RESULT		MOD_xxx_Enumerate		(MOD_xxx_Args& arg);
ERR_RESULT		MOD_xxx_GetData		(MOD_xxx_Args& arg);
ERR_RESULT		MOD_xxx_PutData		(MOD_xxx_Args& arg);
ERR_RESULT		MOD_xxx_Delete			(MOD_xxx_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool				CHECK_XXX_ID						(identifier xxxID);
bool				CHECK_XXX_GUID						(guid			xxxGUID);
ERR_RESULT		USER_CHECK_ACCESS_TO_XXX		(identifier userID, identifier xxxID, const string& Attributes);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/