/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Linkage.h																[]
[] Date:          18.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с семантическими связями										[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_Linkage_h
#define MOD_Linkage_h


#define MAX_LINKAGE_ENUMERATE_NUM	100



//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса xxx								[]
//                                                                            []
struct MOD_Linkage_Args
{ 
	MOD_Linkage_Args()
	{
		objID						=	NA;

		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		MaxNumInQuery			=	MAX_LINKAGE_ENUMERATE_NUM;
		ReadOnly					=	false;
		UseRelationID			=	false;
		RelationID				=	NA;

		RelationVersion		=	-1;
		bNeedFields				=	false;

		RealObjectID			=	NA;

		AccessLevelThreshold	=	0;

		ExitCode					=	-1;
	}

	string			Login;
	string			Password;
	string			Attributes;
	identifier		objID;
	bool				UseRelationID;
	string			RelationSysName;
	bool				ReadOnly;

	identifier		RelationID;
	identifier_arr	objRelationIDs;
	identifier_arr	objIDs;
	identifier_arr	ProxyIDs;
	string_arr		Values;

	string_arr		FieldTypes;
	string_arr		FieldValues;
	identifier_arr	FieldObjectProxyIDs;
	string_arr		FieldObjectClasses;
	identifier_arr	FieldObjectIDs;
	string_arr		FieldObjectNames;

	int				RelationVersion;

	string			RealObjectClassName;
	identifier		RealObjectID;
	string			RealObjectName;

	bool				bNeedFields;
	int_arr			FieldIndices;
	string_arr		objFieldsValues;

   int				AccessLevelThreshold;

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
//` Проверить -- есть ли у объекта прокси для участия в связях,					[]
//  если нет -- создать                                                       []
#define CHECK_PROXY_OBJECT_OF(oc)															\
{																										\
	DEBUG_STACK_NAME (CHECK_PROXY_OBJECT);													\
	if (!OC_Exist(guid(oc.m_ProxyObject)))													\
	{																									\
		OC_LinkProxy oc_proxy;																	\
		oc_proxy.New ();																			\
		oc.m_ProxyObject			= oc_proxy.GetObjectGUID();							\
		oc_proxy.m_RealObject	= oc.GetObjectGUID();									\
	}																									\
}
//____________________________________________________________________________[]
//																										[]
//` При удалении указанного объекта корректно удалить прокси-объект				[]
//																										[]
#define DELETE_PROXY_OBJECT_OF(oc)															\
{																										\
	DEBUG_STACK_NAME	(DELETE_PROXY_OBJECT);												\
	guid oc_m_ProxyObject	= oc.m_ProxyObject;											\
	oc.m_ProxyObject			= guid (0);														\
	DeleteProxyObject (oc_m_ProxyObject);													\
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_Linkage_New							(MOD_Linkage_Args& arg);
ERR_RESULT		MOD_Linkage_Enumerate					(MOD_Linkage_Args& arg);
ERR_RESULT		MOD_Linkage_GetData						(MOD_Linkage_Args& arg);
ERR_RESULT		MOD_Linkage_PutData						(MOD_Linkage_Args& arg);
ERR_RESULT		MOD_Linkage_Delete						(MOD_Linkage_Args& arg);
ERR_RESULT		MOD_Linkage_GetRealObjectByProxyID	(MOD_Linkage_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
//____________________________________________________________________________[]
bool			CHECK_LINKAGE_ID					(identifier linkID);
bool			CHECK_LINKAGE_GUID				(guid			linkGUID);
ERR_RESULT	USER_CHECK_ACCESS_TO_LINKAGE	(identifier userID, identifier linkID, const string& Attributes);
void			DeleteProxyObject					(guid			proxyGUID);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/