/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_MetaObject.h															[]
[] Date:          03.10.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса MetaObject								[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_MetaObject_h
#define MOD_MetaObject_h


#define MAX_METAOBJECT_ENUMERATE_NUM	100

//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса MetaObject						[]
//                                                                            []
struct MOD_MetaObject_Args
{ 
	MOD_MetaObject_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_METAOBJECT_ENUMERATE_NUM;
		ReadOnly					=	false;
		ProxyID					=	NA;

		ExitCode					=	-1;
	}

	string			Login;
	string			Password;

	identifier		objID;
	string			Type;
	string			Name;
	string			SysName;
	bool				ReadOnly;
	identifier		ProxyID;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objTypes;

	identifier_arr	FeodIDs;
	string			TypePrefix;

	string_arr		objSysNames;
	identifier_arr	objProxyIDs;
	
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
ERR_RESULT		MOD_MetaObject_New			(MOD_MetaObject_Args& arg);
ERR_RESULT		MOD_MetaObject_Enumerate	(MOD_MetaObject_Args& arg);
ERR_RESULT		MOD_MetaObject_GetData		(MOD_MetaObject_Args& arg);
ERR_RESULT		MOD_MetaObject_PutData		(MOD_MetaObject_Args& arg);
ERR_RESULT		MOD_MetaObject_Delete		(MOD_MetaObject_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//____________________________________________________________________________[]
bool			CHECK_METAOBJECT_ID					(identifier metaID);
bool			CHECK_METAOBJECT_GUID				(guid			metaGUID);
ERR_RESULT	USER_CHECK_ACCESS_TO_METAOBJECT	(identifier userID, identifier metaID, const string& Attributes);
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 
void MOD_GET_OBJECT_NAME_MetaObject				(guid& gi, string& sNAME);
void MOD_CHECK_ACCESS_MetaObject					(identifier userID, guid& gi, const string& Attributes);
//----------------------------------------------------------------------------[] 



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/