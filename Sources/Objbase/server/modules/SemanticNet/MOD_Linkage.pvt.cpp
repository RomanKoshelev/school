/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Linkage.pvt.cpp														[]
[] Date:          18.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������������� �������										[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_Linkage.inc.h"


//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_LINKAGE_GUID (guid linkGUID)
{
	DEBUG_STACK_NAME (CHECK_LINKAGE_GUID);

// ������ ������ ������������
	if (!OC_Exist (linkGUID))
	{
		return false;
	}
	OC_Linkage		oc_link; 
	oc_link.Open	(linkGUID);

	if (!CHECK_RELATION_ID (oc_link.m_RelationID))
	{
		SERVER_DEBUG_ERROR_2 ("� ����� %u ������������ ��������� %u", linkGUID.id, identifier (oc_link.m_RelationID));
		return false;
	}
	

// ��������� ������������ �������
	int nFields = OC_Relation(oc_link.m_RelationID).m_FieldName.Size();
	SERVER_DEBUG_ASSERT_RETURN (oc_link.m_ProxyID.Size() == nFields,		"������������ ������� ������ �����", false);
	SERVER_DEBUG_ASSERT_RETURN (oc_link.m_Value.Size() == nFields,			"������������ ������� ������ �����", false);

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_LINKAGE_ID (identifier linkID)
{
	DEBUG_STACK_NAME (CHECK_LINKAGE_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_Linkage, linkID))
	{
		return false;
	}
	OC_Linkage oc_link (linkID);

	return CHECK_LINKAGE_GUID(oc_link.GetObjectGUID ());
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS_TO_LINKAGE															[]
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_LINKAGE (identifier userID, identifier linkID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_LINKAGE);

// �������� �� ������������
	static int StackDepth=0; StackDepth++;
	if (StackDepth>100)
	{
		SERVER_DEBUG_ERROR ("������������ ��� �������� ������� � �����");
		return ERR_SYSTEM_ERROR;
	}

// �������� ����������
	if (!CHECK_LINKAGE_ID (linkID))
	{
		StackDepth--;
		return ERR_BadID;
	}
	OC_Linkage oc_link (linkID);

// ������ ���� ������ � ���������
	ERR_RESULT res = USER_CHECK_ACCESS_TO_RELATION (userID, oc_link.m_RelationID, "R");
	if (res!=ERR_OK)
	{
		StackDepth--;
		return res;
	}

// ������ ���� ������ � ��������� ��������
	for (int i=0; i<oc_link.m_ProxyID.Size(); i++) if (oc_link.m_ProxyID[i] != NA)
	{
		if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, oc_link.m_ProxyID[i]))
		{
			SERVER_DEBUG_ERROR_2 ("� ����� %u ������������ �������������� ������-������ %u", linkID, (identifier)oc_link.m_ProxyID[i]);
			continue;
		}
		OC_LinkProxy oc_proxy;
		oc_proxy.Open (oc_link.m_ProxyID[i]);

		if (OC_Exist (oc_proxy.m_RealObject))
		{
			MOD_CHECK_ACCESS (userID, guid (oc_proxy.m_RealObject), Attributes);
		}
		else
		{
			SERVER_DEBUG_ERROR_4 ("������-������[%u] ��������� �� �������������� ������ %s[%u].%u. ����������.", oc_proxy.GetObjectID(), className[guid (oc_proxy.m_RealObject).cl], guid (oc_proxy.m_RealObject).id, guid (oc_proxy.m_RealObject).rn);
			DeleteProxyObject		(oc_proxy.GetObjectGUID ());
		}
	}

	StackDepth--;
	return res;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` DeleteProxyObject                                                         []                 
//                                                                            []
void DeleteProxyObject (guid proxyGUID)
{
	DEBUG_STACK_NAME (DeleteProxyObject);
	if (!OC_Exist (proxyGUID)) return;

	OC_LinkProxy	oc_proxy;
	OC_Linkage		oc_link;
	oc_proxy.Open (proxyGUID);

// ���������� �� ���� ������ �������
	for (int l=0; l<oc_proxy.m_LinkageID.Size(); l++)
	{
		oc_link.Open (oc_proxy.m_LinkageID[l]);
		if (!oc_link.IsValid()) continue;
		oc_link.m_ProxyID[oc_proxy.m_RelationField[l]] = NA;

	// ���� � ����� �� �������� �������� �����-��������, ������� �.
		bool bDelete = true;
		for (int f=0; f<oc_link.m_ProxyID.Size(); f++)
		{
			if (oc_link.m_ProxyID[f]!=NA) 
			{
				bDelete=false;
				break;
			}
		}
		if (bDelete)
		{
			oc_link.Delete ();
		}
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