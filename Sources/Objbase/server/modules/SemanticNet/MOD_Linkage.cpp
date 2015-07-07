/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Linkage.cpp															[]
[] Date:          18.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������������� �������										[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Linkage.inc.h"






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ����� ������������� �����														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_New (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_New);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [R] �� ���� ������ ���������������� ���������.
		<Password					������ ������������, �������������� ��������.

		<RelationID					������������� ���������, �� ������ �������� �������� �����.
		<RelationVersion			������ ��������� (���� -1, �� ������������).
		<ProxyIDs					����-�������: �������������� ����������� ������-��������. � ��� ������ ���� ������ [W].
		<Values						����-�������� (������)
		<AccessLevelThreshold	��������� �������� ������ ������� �������������. ������ ������ ����� ����� ������ �����, ��� ������� � ���������, ����� ��� ��� � �������/�������.
		>objID						������������� ��������� �����.
		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ������ ������������
	if (!CHECK_RELATION_ID (arg.RelationID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "��������� ������ Relation[%u] �� ����������", arg.RelationID);
	}
	OC_Relation oc_rel (arg.RelationID);
// �������� ������ ���������
	if (arg.RelationVersion!=-1 && arg.RelationVersion!=oc_rel.m_Version)
	{
		ERR_RETURN_COMMENT_3 (ERR_RelationVersionMismatch, "������������ ������ ��������� %s -- %d!=%d", string(oc_rel.m_Name).c_str(), arg.RelationVersion, int (oc_rel.m_Version));
	}
// ������-������� ������ ������������
	int iProxy=0;
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.ProxyIDs[iProxy]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadID, "������ �������������� ������ LinkProxy[%u] � ��������� %d", arg.ProxyIDs[iProxy], iProxy);
		}
	}
// ��������� ����� ���������� ����������
	int nRelFields = oc_rel.m_FieldType.Size();
	if (arg.ProxyIDs.Size()!=nRelFields) 	ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��� �������� ����� '%s' ������ ���� �������� %d ����������-�������� (ProxyIDs), � �� %d",	string(oc_rel.m_Name).c_str(), nRelFields, arg.ProxyIDs.Size());
	if (arg.Values	 .Size()!=nRelFields) 	ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��� �������� ����� '%s' ������ ���� �������� %d ����������-�������� (Values), � �� %d",		string(oc_rel.m_Name).c_str(), nRelFields, arg.Values.Size  ());
// ��������� ������������ ���������� ���� (����-�������� �� ����� ��������� ��������)
	int f=0;
	for (f=0; f<oc_rel.m_FieldType.Size(); f++) 
	{
		if (arg.ProxyIDs[f]!=NA && oc_rel.m_FieldType[f]!="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��������� ���� %s[%s] �� ����� ���� ������ [%u]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.ProxyIDs[f]);
		if (!arg.Values[f].IsEmpty() && oc_rel.m_FieldType[f]=="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��������� ���� %s[%s] �� ����� ���� ������ [%s]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.Values[f].c_str());
	}
// � ����� ������ ����������� ����-�� ���� ������
	int nObj=0;
	for (f=0; f<oc_rel.m_FieldType.Size(); f++) nObj += oc_rel.m_FieldType[f]=="object" && arg.ProxyIDs[f]!=NA;
	if (nObj==0) ERR_RETURN_COMMENT_1 (ERR_BadArgument, "� ����� %s ������ ����������� ����-�� ���� ������", string(oc_rel.m_Name).c_str());
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// ��������� ����� ������� -- ������������ ������ ����� ����� ������ ���������
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.RelationID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� ��� ���������� ��������");
	}
// ������������ ������ ����� ����� �������� �������-���������
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "������������ �� ����� ����� ������������� (�������� � �����) ������ '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������
	OC_Linkage oc_link;
	oc_link.New ();
	identifier linkID = oc_link.GetObjectID ();

	oc_link.m_RelationID					=	arg.RelationID;
	oc_link.m_ProxyID						=	arg.ProxyIDs;
	oc_link.m_Value						=	arg.Values;
	oc_link.m_OwnerGUID					=	oc_login.GetObjectGUID ();
	oc_link.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// ���������� �������������
	arg.objID								=	linkID;

//	������� ����� �� ��� ������-�������
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		oc_proxy.m_RelationID		+=	arg.RelationID;
		oc_proxy.m_LinkageID			+=	linkID;
		oc_proxy.m_RelationField	+=	iProxy;
	}

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ ��������� ������������� ������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_Enumerate (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ��������� ������ [L] �� ���� ������ ���������������� ��������� ��� [LR], ���� bNeedFields.
		<Password					������ ������������, �������������� ��������.

		<objID						������������� �������-������, ��� ����� �������������. ���� NA -- ��� �����. � ������� ��������� ������� ������ ���� ������ [R].
		<UseRelationID				���� false (�� ����������), �� ��������� ��� �����, ����� ������ ��, ������� ����� ��� RelatonID.
		<RelationID					����������� ������ ���� UseRelationID==true. ������������� ��������� (���� �����). ��������� ������ �����, ����������� ��������� ���������. � ���������� ������ ���� ������ [L].
		<bNeedFields				���������� �� ������ �� ���������� ��������� �����. (��-��������� false). ���� �������, �� ��������� ����� [R].
		<FieldIndices				�������� ����� ����� ������ ���������� (������������ ��� bNeedFields).
		<RelationSysName			����������� ������ ���� UseRelationID==true � ���� �� ������ RelationID.
		<objFirstNo					����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.
		<objLastNo					����� �������, �� �������� ������������ ��������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

		>objIDs						������ ��������������� ������, � ������� ��������� ������. ����������� �� �����, ������� �������� �������, � �������� ��� ������� [R].
		>objFieldsValues			�������� ��������� ����� � ���� �����. ��������� ��������������� -- ������� ��� ���� i-�, ����� i+1-� �����. ������ ������ ���� bNeedFields==false. ���� ������������ �� ����� ����� ������ �����, ������������ ������ "{{ACCESS DENY}}".
		>objRelationIDs			������ ��������������� ��������������� ���������.

		>TotalStoredNum			������� ����� ������ ����� ���� ����������� � ������ ��������.
		>MaxNumInQuery				����������� ���������� ����� ������������� �� ���� ��� ��������.

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������-������ ������ ������������
	if (arg.objID!=NA && !OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "��������� ������ LinkProxy[%u] �� ����������", arg.objID);	
	}
	OC_LinkProxy oc_proxy;
	if (arg.objID!=NA) oc_proxy.Open (arg.objID);

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// �������� ������� �� ������ ������ � ��������� �������
	if (arg.objID!=NA && !MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "R"))
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "��� ������� � ��������� ��������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_LINKAGE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_LINKAGE_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "��������� %d ������, � ����������� ����� ��������� %d", (arg.objLastNo - arg.objFirstNo), MAX_LINKAGE_ENUMERATE_NUM);
	}
// ���� ������������ ������ �� ���������, �� ��������� �������������.
	if (arg.UseRelationID)
	{
		if (arg.RelationID==NA)
		{
			arg.RelationID = GetRelationIDBySysName (arg.RelationSysName);
			if (arg.RelationID==NA)
			{
				ERR_RETURN_COMMENT_1 (ERR_BadName, "��������� ������ Relation[%s] �� ����������", arg.RelationSysName.c_str());
			}
		}
		if (!OC_Exist (OBJ_CLASS_ID_Relation, arg.RelationID))
		{
			ERR_RETURN_COMMENT_1 (ERR_BadID, "��������� ������ Relation[%u] �� ����������", arg.RelationID);
		}
	}
	OC_Relation oc_rel; if (arg.UseRelationID) oc_rel.Open (arg.RelationID);

// ���� ������� ����, �� ���� ������� ���������
	if (arg.bNeedFields && arg.RelationID==NA)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "���� ����������� ���� (arg.bNeedFields), �� ���� ������� ��������� (arg.RelationID)");
	}
// ���� ������� ����, �� ���� ��������� �� ����������
	int f;
	int oc_rel_m_FieldType_Size = arg.UseRelationID? oc_rel.m_FieldType.Size() : 0;
	if (arg.bNeedFields) for (f=0; f<arg.FieldIndices.Size(); f++) if (arg.FieldIndices[f]<0 || arg.FieldIndices[f]>=oc_rel_m_FieldType_Size)
	{
		ERR_RETURN_COMMENT_3 (ERR_BadArgument, "������������ ������ ���� %d � ��������� '%s' -- ����������� ���������� ������ ���� -- %d", arg.FieldIndices[f], string(oc_rel.m_Name).c_str(), oc_rel_m_FieldType_Size);
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������ ���� ������ �������
	int						i,j,l,N;
	identifier_arr			ALL_LINKAGE_IDs;
	OC_Linkage				oc_link;

// ���� ������ ������ -- ��� ��� �����	
	if (arg.objID!=NA) 
	{
		ALL_LINKAGE_IDs = oc_proxy.m_LinkageID;
	}
// ���� ������ �� ������ -- ��� ����� �������� ���������
	else if (arg.UseRelationID)
	{
		oc_link.SetIndex_RelationID();
		key_arr ka;
		ka += arg.RelationID;
		oc_link.GetClassIdList (ALL_LINKAGE_IDs, &ka);
	}
// ���� �� ������ �� ������, �� ��������� -- ������
	else
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "���� ������� ���� ������, ���� ��� ������ (���������), � ����� � �� � ������");
	}

// ��������� ������ �����, ����������� ��������� ���������
	if (arg.UseRelationID)
	{
		for (l=0; l<ALL_LINKAGE_IDs.Size(); l++)
		{
			oc_link.Open (ALL_LINKAGE_IDs[l]);
			if (oc_link.m_RelationID != arg.RelationID)
			{
				ALL_LINKAGE_IDs[l] = NA;
			}
		}
	}

// ���������� �� �����, � ������� ��� ������� �� ������ (��������, ����������� ����������� �������)
	for (l=0; l<ALL_LINKAGE_IDs.Size(); l++) if (ALL_LINKAGE_IDs[l]!=NA)
	{
		ERR_RESULT res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, ALL_LINKAGE_IDs[l], (arg.bNeedFields? "LR": "L"));
		if (res!=ERR_OK)
		{
			ALL_LINKAGE_IDs[l] = NA;
		}
	}

// ���������� �� ���� ��������������� �������� � ��������� �������� ���������
	for (N=0, j=0, i=0; i<ALL_LINKAGE_IDs.Size(); i++) if (ALL_LINKAGE_IDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) {j++; continue;} else j++; N++;

		oc_link.Open (ALL_LINKAGE_IDs[i]);

		arg.objIDs				+= ALL_LINKAGE_IDs[i];
		arg.objRelationIDs	+=	oc_link.m_RelationID;
		if (arg.bNeedFields) for (f=0; f<arg.FieldIndices.Size(); f++)
		{
			if (oc_rel.m_FieldType[arg.FieldIndices[f]]=="object")
			{
				static string strFieldValue;
				strFieldValue.Format ("%u", identifier (oc_link.m_ProxyID[arg.FieldIndices[f]]));
				arg.objFieldsValues	+=	strFieldValue;
			}
			else
			{
				arg.objFieldsValues	+=	oc_link.m_Value[arg.FieldIndices[f]];
			}
		}
	}

// ����� ����� ��������, ������� ����� �����������
	arg.TotalStoredNum	=	N;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������������� �����													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_GetData (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_GetData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [R].
		<Password					������ ������������, �������������� ��������.

		<objID						������������� ������������� �����.

		>FieldTypes					���� ����� ("object" "byte" "int" "bool" "time" "string" "float")
		>FieldValues				��������� �������� �����, ���� ��� �� "object"
		>FieldObjectProxyIDs		�������������� ������-��������, ���� ���="object". NA ���� ���� �����.
		>FieldObjectClasses		������ �������� ��������-�����, ���� ��� ����="object". ������ ������ ���� ���� �����.
		>FieldObjectIDs			�������������� �������� ��������-�����, ���� ��� ����="object". NA ���� ���� �����.
		>FieldObjectNames			����� �������� ��������-�����, ���� ��� ����="object". ���� ���� �� ����� ������ ��� �������, ������������ "{{UNKNOWN NAME}}". "{{NA}}" ���� ���� �����.

		>AccessLevelThreshold	��������� �������� ������ ������� �������������.
		>ReadOnly					����� �� ������������ ����� ������������� ������

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!CHECK_LINKAGE_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Linkage[%u] �� ����������", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// ��������� ����� ������� -- ����� ������ ����� ����� ������ �� ���� ����� ������� ���������
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [R] �� ������ ����� (��������� ��� ������ �� ��������)");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ��������� ������ �������
	OC_Relation oc_rel (identifier (oc_link.m_RelationID));

	arg.FieldTypes				=	oc_rel.m_FieldType;
	for (int f=0; f<arg.FieldTypes.Size(); f++)
	{
		if (arg.FieldTypes[f] == "object")
		{
			arg.FieldValues += "";
			if (OC_Exist (OBJ_CLASS_ID_LinkProxy, identifier(oc_link.m_ProxyID [f])))
			{
				arg.FieldObjectProxyIDs += oc_link.m_ProxyID [f];
				OC_LinkProxy oc_proxy (identifier(oc_link.m_ProxyID [f]));

				identifier classID = guid(oc_proxy.m_RealObject).cl;
				string StrClassName = classID<1024? className[classID] : "";

				guid gi = oc_proxy.m_RealObject;
				arg.FieldObjectClasses	+= StrClassName;
				arg.FieldObjectIDs		+= gi.id;
				arg.FieldObjectNames		+= MOD_GET_OBJECT_NAME (gi);
			}
			else
			{
				arg.FieldObjectProxyIDs += NA;
				arg.FieldObjectClasses	+= "";
				arg.FieldObjectIDs		+= NA;
				arg.FieldObjectNames		+= "{{NA}}";
			}
		}
		else
		{
			arg.FieldValues			+= oc_link.m_Value[f];
			arg.FieldObjectProxyIDs += NA;
			arg.FieldObjectClasses	+= "";
			arg.FieldObjectIDs		+= NA;
			arg.FieldObjectNames		+= "-";
		}
	}

	arg.ReadOnly					=	(USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "W")!=ERR_OK);
	arg.AccessLevelThreshold	=	oc_link.m_AccessLevelThreshold;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������������� �����													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_PutData (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_PutData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [W].
		<Password					������ ������������, �������������� ��������.

		<objID						������������� �����.
		<RelationVersion			������ ��������� (���� -1, �� ������������).
		<ProxyIDs					�������������� ����������� ������-��������. � ��� ������ ���� ������ [W].
		<Values						����-�������� (������)

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!CHECK_LINKAGE_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Linkage[%u] �� ����������", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// ��������� ����� ������� -- ����� ������ ����� ����� ������ �� ���� ����� ������� ���������
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [W] �� ��������� ���������");
	}
// ������������ ������ ����� ����� �������� �������-���������
	int iProxy=0;
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (arg.ProxyIDs[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "������������ �� ����� ����� ������������� (�������� � �����) ������ '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//	��������� ������� �������
	if (oc_link.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ��� ��������� ���������");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ������ ������������
	if (!CHECK_RELATION_ID (oc_link.m_RelationID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "��������� ������ Relation[%u] �� ����������", arg.RelationID);
	}
	OC_Relation oc_rel (oc_link.m_RelationID);
// �������� ������ ���������
	if (arg.RelationVersion!=-1 && arg.RelationVersion!=oc_rel.m_Version)
	{
		ERR_RETURN_COMMENT_3 (ERR_RelationVersionMismatch, "������������ ������ ��������� %s -- %d!=%d", string(oc_rel.m_Name).c_str(), arg.RelationVersion, int (oc_rel.m_Version));
	}
// ������-������� ������ ������������
	for (iProxy=0; iProxy<arg.ProxyIDs.Size(); iProxy++) if (arg.ProxyIDs[iProxy]!=NA)
	{
		if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.ProxyIDs[iProxy]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadID, "������ �������������� ������ LinkProxy[%u] � ���������� %d", arg.ProxyIDs[iProxy], iProxy);
		}
	}
// ��������� ����� ���������� ����������
	int nRelFields = oc_rel.m_FieldType.Size();
	if (arg.ProxyIDs.Size()!=nRelFields) 	ERR_RETURN_COMMENT_4 (ERR_BadArgument, "��� �������������� ����� %s[ID=%u] ������ ���� �������� %d ����������-�������� (ProxyIDs), � �� %d", string(oc_rel.m_Name).c_str(), arg.objID, nRelFields, arg.ProxyIDs.Size());
	if (arg.Values	 .Size()!=nRelFields) 	ERR_RETURN_COMMENT_4 (ERR_BadArgument, "��� �������������� ����� %s[ID=%u] ������ ���� �������� %d ����������-�������� (Values), � �� %d",	string(oc_rel.m_Name).c_str(), arg.objID, nRelFields, arg.Values.Size  ());

// ��������� ������������ ���������� ���� (����-�������� �� ����� ��������� ��������)
	int f=0;
	for (f=0; f<nRelFields; f++) 
	{
		if (arg.ProxyIDs[f]!=NA && oc_rel.m_FieldType[f]!="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��������� ���� %s[%s] �� ����� ���� ������ [%u]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.ProxyIDs[f]);
		if (!arg.Values[f].IsEmpty() && oc_rel.m_FieldType[f]=="object")
			ERR_RETURN_COMMENT_3 (ERR_BadArgument, "��������� ���� %s[%s] �� ����� ���� ������ [%s]", string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), arg.Values[f].c_str());
	}
// � ����� ������ ����������� ����-�� ���� ������
	int nObj=0;
	for (f=0; f<nRelFields; f++) nObj += oc_rel.m_FieldType[f]=="object" && arg.ProxyIDs[f]!=NA;
	if (nObj==0) ERR_RETURN_COMMENT_2 (ERR_BadArgument, "� ����� %s[ID=%u] ������ ����������� ����-�� ���� ������", string(oc_rel.m_Name).c_str(), arg.objID);
//----------------------------------------------------------------------------[] 





	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� � ����� ����-��������
	oc_link.m_Value = arg.Values;

// �������� � ����� ����-�������
	for (f=0; f<nRelFields; f++) if (oc_rel.m_FieldType[f]=="object")
	{
		identifier oldProxyID = oc_link.m_ProxyID[f];
		identifier newProxyID = arg.ProxyIDs[f];
		if (oldProxyID != newProxyID)
		{
		// ���� ���������� ��������-������ -- ���� � ������� ��������� �������� �����
			if (oldProxyID!=NA)
			{
				OC_LinkProxy oc_proxy (oldProxyID);
				int index = oc_proxy.m_LinkageID.Find (arg.objID);
				if (index!=-1)
				{
					oc_proxy.m_LinkageID		.Del (index);
					oc_proxy.m_RelationField.Del (index);
					oc_proxy.m_RelationID	.Del (index);
				}
				else SERVER_DEBUG_ERROR_4 ("����� %u (%s[%s]) �� ������� � ������-������� %u", arg.objID, string(oc_rel.m_Name).c_str(), string(oc_rel.m_FieldName[f]).c_str(), oldProxyID);
			}
		// ���������� � ������ ������� �����
			if (newProxyID!=NA)
			{
				OC_LinkProxy oc_proxy (newProxyID);
				oc_proxy.m_LinkageID			+=	arg.objID;
				oc_proxy.m_RelationID		+=	oc_link.m_RelationID;
				oc_proxy.m_RelationField	+=	f;
			}		
		// �������� ���� �����
			oc_link.m_ProxyID[f] = newProxyID;
		}
	}
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]




















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������������� �����																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_Delete (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_Delete);
/*............................................................................[]
�������� ������������� �����. ������ ���� ������ [D] � ��������� � [W] �� ���� �������-����������.
		<Login						����� ������������, �������������� ��������.
		<Password					������ ������������, �������������� ��������.

		<objID						������������� �����.
		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_Linkage, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Linkage[%u] �� ����������", arg.objID);
	}
	OC_Linkage oc_link (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� ������� -- ������������ ������ ����� ����� ������� ��������� �� ���� ��� ����� �������
	res = USER_CHECK_ACCESS_TO_LINKAGE (loginID, oc_link.GetObjectID(), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� ��� ���������� ��������");
	}
// ������������ ������ ����� ����� �������� �������-���������
	int iProxy=0;
	for (iProxy=0; iProxy<oc_link.m_ProxyID.Size(); iProxy++) if (oc_link.m_ProxyID[iProxy]!=NA)
	{
		OC_LinkProxy oc_proxy (oc_link.m_ProxyID[iProxy]);
		if (!MOD_CHECK_ACCESS (loginID, oc_proxy.m_RealObject, "W"))
		{
			guid gi = oc_proxy.m_RealObject;
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "������������ �� ����� ����� ������������� (��������� �� �����) ������ '%s', %s[%u]", MOD_GET_OBJECT_NAME(gi), className[gi.cl], gi.id);
		}
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������� ���������� � ����� � ���� ��������-����������
	for (int i=0; i<oc_link.m_ProxyID.Size(); i++) if (oc_link.m_ProxyID[i]!=NA)
	{
		OC_Relation oc_rel (oc_link.m_RelationID);
		if (OC_Exist (OBJ_CLASS_ID_LinkProxy, oc_link.m_ProxyID[i]))
		{
			OC_LinkProxy oc_proxy (oc_link.m_ProxyID[i]);
			int index = oc_proxy.m_LinkageID.Find (arg.objID);
			int Pos = oc_proxy.m_RelationField[index];

			if (index!=-1)
			{
				oc_proxy.m_LinkageID		.Del (index);
				oc_proxy.m_RelationField.Del (index);
				oc_proxy.m_RelationID	.Del (index);
			}
			else SERVER_DEBUG_ERROR_3 ("���������� ����� %u (%s) �� ������� � ������-������� %u", arg.objID, string(oc_rel.m_Name).c_str(), identifier (oc_link.m_ProxyID[i]));

			if (Pos!=i)
			{
				SERVER_DEBUG_ERROR_5 ("���������� ����� %u (%s) ������� � ������-������� %u � ������ ������� ���� (%d ������ %d)", arg.objID, string(oc_rel.m_Name).c_str(), identifier (oc_link.m_ProxyID[i]), index, Pos);
			}
		}
		else SERVER_DEBUG_ERROR_4 ("� ��������� ����� %u (%s) � ��������� %d ���������� ������ %u �� �������������� ������.", arg.objID, string(oc_rel.m_Name).c_str(), i, identifier (oc_link.m_ProxyID[i]));
	}
	

// ���������� �����
	oc_link.Delete ();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ��������� ������� �� ��� ������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Linkage_GetRealObjectByProxyID (MOD_Linkage_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Linkage_GetRealObjectByProxyID);
/*............................................................................[]
		<objID						������ ������.

		>RealObjectClassName		����� ��������� �������
		>RealObjectID				������������� ��������� �������
		>RealObjectName			��� ��������� �������

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������-������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_LinkProxy, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ �������������� ������ LinkProxy[%u]", arg.objID);
	}
	OC_LinkProxy oc_proxy (arg.objID);
//----------------------------------------------------------------------------[] 
// �������� ������ ������ ������������
	if (!OC_Exist (oc_proxy.m_RealObject))
	{
		guid gi = oc_proxy.m_RealObject;
		ERR_RETURN_COMMENT_4 (ERR_BadID, "������ ������ LinkProxy[%u] ��������� �� �������������� ������ [%u:%u:%u]", arg.objID, gi.cl, gi.id, gi.rn);
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	identifier classID = guid(oc_proxy.m_RealObject).cl;
	guid gi = oc_proxy.m_RealObject;
	arg.RealObjectClassName	= className[classID];
	arg.RealObjectID			= gi.id;
	arg.RealObjectName		= MOD_GET_OBJECT_NAME (gi);
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/