/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Relation.pvt.cpp														[]
[] Date:          08.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������������� �����������									[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_Relation.inc.h"


//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_RELATION_GUID (guid relGUID)
{
	DEBUG_STACK_NAME (CHECK_RELATION_GUID);

// ������ ������ ������������
	if (!OC_Exist (relGUID))
	{
		return false;
	}

// ��������� ���� �������
	OC_Relation oc_rel;
	oc_rel.Open (relGUID);
	for (int f=0; f<oc_rel.m_FeodGUID.Size(); f++)
	{
		guid gi = oc_rel.m_FeodGUID[f];
		if (!OC_Exist (gi))
		{
			SERVER_DEBUG_ERROR_3 ("� ��������� '%s' �������� �������������� ���� %u.%u, ����������.", string(oc_rel.m_Name).c_str(), gi.id, gi.rn);
			oc_rel.m_FeodGUID.Del (f);
			f --;
			continue;
		}
	}

// ��������� ������������ �������
	int nFields = oc_rel.m_FieldName.Size();
	SERVER_DEBUG_ASSERT_RETURN (oc_rel.m_FieldType.Size() == nFields,				"������������ ������� ������ �����", false);
	SERVER_DEBUG_ASSERT_RETURN (oc_rel.m_FieldSysName.Size() == nFields,			"������������ ������� ������ �����", false);
	SERVER_DEBUG_ASSERT_RETURN (oc_rel.m_FieldDescription.Size() == nFields,	"������������ ������� ������ �����", false);
	SERVER_DEBUG_ASSERT_RETURN (oc_rel.m_FieldInterfaceType.Size() == nFields,	"������������ ������� ������ �����", false);

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_RELATION_ID (identifier relID)
{
	DEBUG_STACK_NAME (CHECK_RELATION_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_Relation, relID))
	{
		return false;
	}
	OC_Relation oc_rel (relID);

	return CHECK_RELATION_GUID (oc_rel.GetObjectGUID ());
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS_TO_RELATION															[]
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_RELATION (identifier userID, identifier relID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_RELATION);

// �������� ����������
	if (!CHECK_RELATION_ID (relID))
	{
		return ERR_BadID;
	}
	OC_Relation oc_rel (relID);

// ���������� �� ���� ������ ��������� � ��������� ������
	for (int f=0; f<oc_rel.m_FeodGUID.Size(); f++)
	{
		identifier feodID = guid(oc_rel.m_FeodGUID[f]).id;
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
//` �������� ������������ � ������������ ���������� ����� ���� ���������		[]
//                                                                            []
bool RelationCheckFieldSystemName (const char * SysName)
{
	return string (SysName).CheckSysName ();
}
//----------------------------------------------------------------------------[] 
bool RelationCheckFieldSystemName (identifier relID, const char * SysName, int nID)
{
	DEBUG_STACK_NAME (RelationCheckFieldSystemName);

	OC_Relation  oc_rel (relID);
	if (!oc_rel.IsValid ()) return false;

// ����� ����
	if (nID == -1) 
	{
		return oc_rel.m_FieldSysName.Find (SysName)==-1;
	}

// ������������ ����
	for (int i=0; i<oc_rel.m_FieldSysName.Size(); i++)
	{
		if (oc_rel.m_FieldSysName[i] == SysName && i!=nID)
		{
			return false;
		}
	}
	return true;
}
//----------------------------------------------------------------------------[] 
bool RelationCheckFieldSystemNames (string_arr& SysNames)
{
	DEBUG_STACK_NAME (RelationCheckFieldSystemNames);
	for (int i=0; i<SysNames.Size(); i++)	for (int j=0; j<SysNames.Size(); j++)
	{
		if (SysNames[i]==SysNames[j] && i!=j) return false;
	}
	return true;
}
//----------------------------------------------------------------------------[] 
identifier GetRelationIDBySysName (const char * SysName)
{
	DEBUG_STACK_NAME (GetRelationIDBySysName);

	OC_Relation  oc_rel;
	oc_rel.SetIndex_SysName ();
	oc_rel.Find (SysName);
	return oc_rel.GetObjectID ();
}
//----------------------------------------------------------------------------[] 	
bool RelationCheckFieldType (const char * Type)
{
	DEBUG_STACK_NAME (RelationCheckFieldType);
	string sType = Type;
	return	sType == "object"	|| 
				sType == "int"		|| 
				sType == "string" || 
				sType == "time"	|| 
				sType == "byte"	|| 
				sType == "bool"	|| 
				sType == "float"	;
}
//----------------------------------------------------------------------------[] 	
bool RelationCheckFieldTypes (const string_arr& Types)
{
	DEBUG_STACK_NAME (RelationCheckFieldTypes);
	for (int i=0; i<Types.Size(); i++) 
	{
		if (!RelationCheckFieldType (Types[i]))
			return false;
	}
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