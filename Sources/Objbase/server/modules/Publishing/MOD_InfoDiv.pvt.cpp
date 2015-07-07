/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoDiv.pvt.cpp														[]
[] Date:          13.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������� ����������.										[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoDiv.inc.h"

//______________________________________________________________________________
//                                                                            []
//` �������� �� ���������� �������������� �������                             []                                             
//                                                                            []
bool CHECK_INFODIV_ID (identifier divID)
{
	DEBUG_STACK_NAME (CHECK_INFODIV_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoDiv, divID))
	{
		return false;
	}
	OC_InfoDiv oc_div (divID);

// �������� �� ����������� ��������� ������
	IF_NOT_CHECK_MOD_BASE (InfoDiv, Concept, oc_div.GetObjectGUID ())
	{
		return false;
	}
	identifier feodID = guid(oc_div.m_MOD_Base_GUID).id;

// ���� ������ �������� ����������
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR ("������������ ������� ������");
		return false;
	}

// ������ ������ �������� ������ ����� {Concept.Feod.Data}
	identifier_arr dataFeods = OC_Concept (GetFeodIDByType ("Concept.Feod.Data")).m_Descendant;
	dataFeods.Insert (0, GetFeodIDByType ("Concept.Feod.Data"));
	if (dataFeods.Find (feodID)==-1)
	{
		SERVER_DEBUG_ERROR_2 ("������ %s [%d] ������ �������� ������ ����� {Concept.Feod.Data}", string(OC_Concept (feodID).m_Name).c_str(), divID);
		return false;
	}

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ������ �� ���������� �����                                       []                                   
//                                                                            []
identifier GetInfoDivIDByType (const char * Type)
{
	DEBUG_STACK_NAME (GetInfoDivIDByType);

	identifier feodID = GetFeodIDByType (Type);
	if (feodID!=NA)
	{
		GET_MOD_EXTENSION (Concept, feodID, InfoDiv, div);
		if (divID!=NA && CHECK_INFODIV_ID(divID))
		{
			return divID;
		}
		return NA;
	}
	return NA;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ������ �� �����                                                  []                        
//  ���� �� ����������, �������� �����													[]
//                                                                            []
identifier GetInfoDivIDByFeodID (identifier feodID)
{
	DEBUG_STACK_NAME (GetInfoDivIDByFeodID);

	GET_MOD_EXTENSION (Concept, feodID, InfoDiv, div);
	if (divID!=NA && CHECK_INFODIV_ID(divID))
	{
		return divID;
	}
	return NA;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ���� �� �������                                                  []                        
//                                                                            []
identifier GetFeodIDByInfoDivID (identifier divID)
{
	DEBUG_STACK_NAME (GetFeodIDByInfoDivID);
	if (!CHECK_INFODIV_ID(divID))
	{
		return NA;
	}
	return guid(OC_InfoDiv(divID).m_MOD_Base_GUID).id;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ������ ���� �������� �������, �� ������� ��� ������                       []
//																										[]
int CACHE_NUM_InfoDivGetAllSubDivIDs=0;
void InfoDivGetAllSubDivIDs (identifier divID, identifier_arr& subDivIDs)
{
	DEBUG_STACK_NAME (IfoDivGetAllSubDivIDs);

	IF_CACHED_ARGS_2_RETURN_VOID (10*1000, divID, CACHE_NUM_InfoDivGetAllSubDivIDs);

	subDivIDs.Erase ();
	identifier feodID = GetFeodIDByInfoDivID (divID);
	if (CHECK_FEOD_ID (feodID))
	{
		identifier_arr subFeodIDs;
		GetFeodDescendantIDs (feodID, subFeodIDs);

		for (int f=0; f<subFeodIDs.Size(); f++)
		{
			identifier subDivID = GetInfoDivIDByFeodID (subFeodIDs[f]);
			if (subDivID!=NA)
			{
				subDivIDs += subDivID;
			}
		}	
	}	
	CACHE_STORE_RESULT_1	(subDivIDs);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ������ ���� �������� ������� � ��� ��������                               []
//																										[]
void InfoDivGetAllInfoObjectSortedIDs (identifier divID, identifier_arr_arr& infoObjIDs)
{
	DEBUG_STACK_NAME (InfoDivGetAllInfoObjectSortedIDs);

	infoObjIDs.Erase ();
	identifier_arr subDivIDs;
	InfoDivGetAllSubDivIDs (divID, subDivIDs);
	subDivIDs += divID;

	infoObjIDs.Alloc (subDivIDs.Size());

	for (int d=0; d<subDivIDs.Size(); d++)
	{
		OC_InfoDiv oc_div (subDivIDs[d]);
		oc_div.m_InfoObjectSortedID.CopyTo (infoObjIDs[d]);
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ������� � ��������������� ������� � ���������� ����������        []
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_INFODIV (identifier userID, identifier divID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_INFODIV);

  	identifier feodID = GetFeodIDByInfoDivID (divID);
	if (!CHECK_FEOD_ID (feodID))
	{
		return ERR_BadID;
	}

	return USER_CHECK_ACCESS (userID, feodID, Attributes);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ��������� ������� ����� �������															[]
//                                                                            []
bool GetInfoDivFullName (identifier divID, string& divName, int FullNameLevel)
{
	DEBUG_STACK_NAME (GetInfoDivFullName);

	return GetFeodFullName (GetFeodIDByInfoDivID (divID), divName, FullNameLevel, "::");
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ������� ��� ���������������� ��������-�����                               []                                           
//                                                                            []
bool GetInfoDivType (identifier divID, string& divType)
{
	DEBUG_STACK_NAME (GetInfoDivType);
	
	divType ="";

  	identifier feodID = GetFeodIDByInfoDivID (divID);
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("������������ ������������� ������� %d", divID);
		return false;
	}

	divType = OC_Concept (feodID).m_Type;
	return true;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/