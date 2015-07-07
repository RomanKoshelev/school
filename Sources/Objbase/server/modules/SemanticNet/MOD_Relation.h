/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Relation.h																[]
[] Date:          08.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с семантическими отношениями									[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_Relation_h
#define MOD_Relation_h


#define MAX_RELATION_ENUMERATE_NUM	100


#define ChangeField_Insert	0
#define ChangeField_Delete 1
#define ChangeField_Move	2
#define ChangeField_Rename	3


//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса xxx								[]
//                                                                            []
struct MOD_Relation_Args
{ 
	MOD_Relation_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_RELATION_ENUMERATE_NUM;
		ReadOnly					=	false;

		AccessLevelThreshold	=	0;
		ChangeType				=	-1;
		FieldID					=	-1;
		FieldPos					=	-1;

		Version					=	-1;

		ExitCode					=	-1;
	}

	string			Login;
	string			Password;
	string			Attributes;
	identifier		objID;
	string			Name;
	string			SysName;
   string			Description;
	bool				ReadOnly;

	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objSysNames;
	string_arr		objDescriptions;

   string_arr		FieldNames;
   string_arr		FieldSysNames;
   string_arr		FieldTypes;
   string_arr		FieldDescriptions;
	string_arr		FieldInterfaceTypes;

   identifier_arr	FeodIDs;
   string_arr		FeodNames;
   int				AccessLevelThreshold;

	int				objFirstNo;
	int				objLastNo;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	int				ChangeType;
	int				FieldID;
	int				FieldPos;
	string			FieldName;
	string			FieldSysName;
	string			FieldDescription;
	string			FieldInterfaceType;

	int				Version;
	int_arr			objVersions;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_Relation_New				(MOD_Relation_Args& arg);
ERR_RESULT		MOD_Relation_Enumerate		(MOD_Relation_Args& arg);
ERR_RESULT		MOD_Relation_GetData			(MOD_Relation_Args& arg);
ERR_RESULT		MOD_Relation_PutData			(MOD_Relation_Args& arg);
ERR_RESULT		MOD_Relation_ChangeField	(MOD_Relation_Args& arg);
ERR_RESULT		MOD_Relation_Delete			(MOD_Relation_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool			CHECK_RELATION_ID					(identifier relID);
bool			CHECK_RELATION_GUID				(guid			relGUID);
ERR_RESULT	USER_CHECK_ACCESS_TO_RELATION	(identifier userID, identifier relID, const string& Attributes);
bool			RelationCheckFieldSystemName	(const char * SysName);
bool			RelationCheckFieldSystemName	(identifier relID, const char * SysName, int nID);
bool			RelationCheckFieldSystemNames	(string_arr& SysNames);
bool			RelationCheckFieldType			(const char * Type);
bool			RelationCheckFieldTypes			(const string_arr& Types);
identifier	GetRelationIDBySysName			(const char * SysName);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/