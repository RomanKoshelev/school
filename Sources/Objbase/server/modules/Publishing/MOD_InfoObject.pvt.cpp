/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoObject.pvt.cpp													[]
[] Date:          16.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с информационными объектами.									[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoObject.inc.h"



//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS_TO_INFOOBJECT                                           []                               
//                                                                            []
void USER_CHECK_ACCESS_TO_INFOOBJECT (identifier userID, identifier infoID, const string& Attributes, int& Res)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_INFOOBJECT);
	IF_CACHED_ARGS_4_RETURN_VOID (10*1000, userID, infoID, Attributes, CACHE_NUM_InfoDivGetAllSubDivIDs+CACHE_NUM_USER_CHECK_ACCESS);

	Res = ERR_OK;

// Проверка аргументов
	if (!OC_Exist (OBJ_CLASS_ID_InfoObject, infoID))
	{
		SERVER_DEBUG_ERROR_1 ("Указанный информационный объект ID=%d не существует", infoID);
		Res = ERR_BadID;
	}
	OC_InfoObject oc_info (infoID);

// Проходимся по всем разделам объекта и проверяем доступ
	for (int d=0; Res==ERR_OK && d<oc_info.m_InfoDivID.Size(); d++)
	{
		ERR_RESULT res = USER_CHECK_ACCESS_TO_INFODIV (userID, oc_info.m_InfoDivID[d], Attributes);
		if (res == ERR_BadID)
		{
			SERVER_DEBUG_ERROR_1 ("Указанный раздел %d не существует или некорректен. Исправлено.", identifier (oc_info.m_InfoDivID[d]));
			oc_info.m_InfoDivID.Del(d);
			d --;
		}
		if (res!=ERR_OK)
		{
			Res = res;
			break;
		}
	}

	CACHE_STORE_RESULT_1	(Res);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Проверка доступа к информационному объекту с указанными атрибутами        []
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_INFOOBJECT (identifier userID, identifier infoID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_INFOOBJECT);

	int Res;
	USER_CHECK_ACCESS_TO_INFOOBJECT (userID, infoID, Attributes, Res);

	return (ERR_RESULT)Res;
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` ФУНКЦИИ МЕЖМОДУЛЬНЫХ ВЫЗОВОВ                                              []                            
//                                                                            []
void MOD_GET_OBJECT_NAME_InfoObject (guid& gi, string& sNAME)
{
	DEBUG_STACK_NAME (MOD_GET_OBJECT_NAME_InfoObject);
	if (OC_Exist (gi))	
	{
		OC_InfoObject oc_info;
		oc_info.Open (gi.id);
		sNAME = oc_info.m_Name;
	}
	else
	{
		sNAME = "{{ERROR}}";
	}
}
//----------------------------------------------------------------------------[] 
void MOD_GET_OBJECT_DESCRIPTION_InfoObject (guid& gi, string& sNAME)
{
	DEBUG_STACK_NAME (MOD_GET_OBJECT_DESCRIPTION_InfoObject);
	if (OC_Exist (gi))	
	{
		OC_InfoObject oc_info;
		oc_info.Open (gi.id);
		sNAME = oc_info.m_Description;
	}
	else
	{
		sNAME = "{{ERROR}}";
	}
}
//----------------------------------------------------------------------------[] 
void MOD_CHECK_ACCESS_InfoObject (identifier userID, guid& gi, const string& Attributes)
{
	DEBUG_STACK_NAME (MOD_CHECK_ACCESS_InfoObject);
	if (gi.cl!=NA && gi.id!=NA && USER_CHECK_ACCESS_TO_INFOOBJECT (userID, gi.id, Attributes) != ERR_OK)
	{
		gi.cl = NA;
		gi.id = NA;
		gi.rn	= 0;
	}
}
//----------------------------------------------------------------------------[] 
void MOD_CHECK_PLACEMENT_InfoObject (identifier_arr& feodIDs, guid& gi)
{
	DEBUG_STACK_NAME (MOD_CHECK_PLACEMENT_InfoObject);

// Если не задан набор ограничений -- проверять не надо
	if (feodIDs.Size()==0 || gi.cl==NA || gi.id==NA)	return;

//	Пытаемся найти объект хотя бы в одном из разделов и в их потомках
	bool bFound = false;
	int f,d;
	for (f=0; !bFound && f<feodIDs.Size(); f++)
	{
		identifier_arr subDivIDs;
		InfoDivGetAllSubDivIDs (GetInfoDivIDByFeodID (feodIDs[f]), subDivIDs);
		subDivIDs.Insert (0, GetInfoDivIDByFeodID (feodIDs[f]));

		for (d=0; !bFound && d<subDivIDs.Size(); d++)
		{
			OC_InfoDiv oc_div (subDivIDs[d]);
			if (oc_div.m_InfoObjectSortedID.Find (gi.id, true)!=-1)
			{
				bFound = true;
			}
		}
	}

//	Если объект не найден ни в одном из запрашиваемых разделов -- вычёркиваем его
	if (!bFound)
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