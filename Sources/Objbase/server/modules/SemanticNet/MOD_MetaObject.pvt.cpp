/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_MetaObject.pvt.cpp													[]
[] Date:          03.10.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса MetaObject								[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_MetaObject.inc.h"


//______________________________________________________________________________
//                                                                            []
//` Проверка на валидность																		[]
//                                                                            []
bool CHECK_METAOBJECT_GUID (guid metaGUID)
{
	DEBUG_STACK_NAME (CHECK_METAOBJECT_GUID);

// Объект должен существовать
	if (!OC_Exist (metaGUID))
	{
		return false;
	}
	
	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка на валидность																		[]
//                                                                            []
bool CHECK_METAOBJECT_ID (identifier metaID)
{
	DEBUG_STACK_NAME (CHECK_METAOBJECT_ID);

// Объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_MetaObject, metaID))
	{
		return false;
	}
	OC_MetaObject oc_meta (metaID);

	guid gi = oc_meta.GetObjectGUID ();
	
	return CHECK_METAOBJECT_GUID(gi);

	return true;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS_TO_METAOBJECT															[]
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_METAOBJECT (identifier userID, identifier metaID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_METAOBJECT);

// Проверка аргументов
	if (!CHECK_METAOBJECT_ID (metaID))
	{
		return ERR_BadID;
	}
	OC_MetaObject oc_meta (metaID);

// Проходимся по всем феодам метаобъекта и проверяем доступ
	for (int f=0; f<oc_meta.m_FeodGUID.Size(); f++)
	{
		identifier feodID = guid(oc_meta.m_FeodGUID[f]).id;
		ERR_RESULT res		= USER_CHECK_ACCESS (userID, feodID, Attributes);
		if (res!=ERR_OK)
		{
			return res;
		}
	}	
	return ERR_OK;
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` ФУНКЦИИ МЕЖМОДУЛЬНЫХ ВЫЗОВОВ                                              []                            
//                                                                            []
void MOD_GET_OBJECT_NAME_MetaObject (guid& gi, string& sNAME)
{
	DEBUG_STACK_NAME (MOD_GET_OBJECT_NAME_MetaObject);
	if (OC_Exist (gi))	
	{
		OC_MetaObject oc_meta;
		oc_meta.Open (gi.id);
		sNAME = oc_meta.m_Name;
	}
	else
	{
		sNAME = "{{ERROR}}";
	}
}
//----------------------------------------------------------------------------[] 
void MOD_CHECK_ACCESS_MetaObject (identifier userID, guid& gi, const string& Attributes)
{
	DEBUG_STACK_NAME (MOD_CHECK_ACCESS_NetaObject);
	if (gi.cl!=NA && gi.id!=NA && USER_CHECK_ACCESS_TO_METAOBJECT (userID, gi.id, Attributes) != ERR_OK)
	{
		gi.cl = NA;
		gi.id = NA;
		gi.rn	= 0;
	}
}
//____________________________________________________________________________[]









/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/