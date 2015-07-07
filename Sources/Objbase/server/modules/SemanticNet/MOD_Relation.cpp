/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Relation.cpp															[]
[] Date:          08.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������������� �����������									[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Relation.inc.h"






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ �������������� ���������												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_New (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_New);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� �������� ��������� [C].
		<Password					������ ������������, �������������� ��������.
		<Name							���
		<SysName						��������� �������� ���������, �������� ��� ���������� �++
		<Description				�������� ���������
		<FieldNames					�������� �����
		<FieldSysNames				��������� ����� �����, �������� ��� ���������� �++
		<FieldTypes					���� ����� ("object" "byte" "int" "bool" "time" "string" "float")
		<FieldDescriptions		�������� �����
		<FieldInterfaceTypes		���� �����, ���������������� �����������
		<FeodIDs						���� �������, � ������� ����������� ���������		
		<AccessLevelThreshold	��������� �������� ������ ������� ������������� � �������.

		>objID						������������� ���������� �������.
		>ExitCode					��� �������� (OK BadLogin BadPassword BadName AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




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
// ��������� ����� ������� -- ������������ ������ ����� ����� ��������� ��������� � ���� ������
	int f;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, arg.FeodIDs[f], "C");
		if (res!=ERR_OK)
		{
			ERR_RETURN_COMMENT (res, "��� ������� ��� ���������� ��������");
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ������� �� ������ ���� ������
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������������ ��������� �� ������ ���� ������");
	}
// ��� ��������� ������ ���� ����������
	OC_Relation oc_rel;
	oc_rel.SetIndex_Name ();
	if (oc_rel.Find (arg.Name))
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "��� ������������ ��������� ������ ���� ����������");
	}
// ��������� ��� ������ ���� ����������
	if (!arg.SysName.CheckSysName())
	{
		SERVER_DEBUG_ERROR_1 ("������������ ��������� ��� %s", arg.SysName.c_str());
	}
// ��������� ��� ��������� ������ ���� ����������
	oc_rel.SetIndex_SysName ();
	if (oc_rel.Find (arg.SysName))
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "��������� ��� ������������ ��������� ������ ���� ����������");
	}
// ��������� ������ ����� ���� �������
	if (arg.FeodIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "�� ������� ���� ������� ������������ ���������");
	}
// ��������������� ���� ������� � guid'�
	guid_arr FeodGUIDs;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		OC_Concept oc_feod;
		oc_feod.Open (arg.FeodIDs[f]);
		FeodGUIDs += oc_feod.GetObjectGUID ();
	}	
// ��������� ����� ����� ������ ���� ����������� � �����������
	if (!RelationCheckFieldSystemNames (arg.FieldSysNames))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "��� ��������� ����� ����� ������ ���� ����������� � �������c� ��� ���������� � �++!");
	}
// ���� ����� ������ ���� �����������
	if (!RelationCheckFieldTypes (arg.FieldTypes))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "������ ����������� ��� ����");
	}
// � ��������� ������ ���� �� ����� 1-�� ����
	if (arg.FieldSysNames.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "� ��������� ������ ���� �� ����� 1-�� ����");
	}
// � ��������� ������ ���� �� ����� 1-�� ����-�������
	int nObjFld=0;	for (f=0; f<arg.FieldTypes.Size(); f++)
	{
		if (arg.FieldTypes[f]=="object") nObjFld++;
	}
	if (nObjFld==0) ERR_RETURN_COMMENT (ERR_BadArgument, "� ��������� ������ ���� �� ����� 1-�� ����-�������");

// ����� ��� �����, �������� � ��������� ��� ������ ���������
	if (arg.FieldSysNames.Size()!=arg.FieldNames.Size() || arg.FieldSysNames.Size()!=arg.FieldDescriptions.Size() || arg.FieldSysNames.Size()!=arg.FieldInterfaceTypes.Size())
	{
		ERR_RETURN_COMMENT_4 (ERR_BadArgument, "������ ����� ��� [%d], ��������� ��� [%d], �������� ����� [%d] � ������������ ����� [%d]", arg.FieldNames.Size(), arg.FieldSysNames.Size(), arg.FieldDescriptions.Size(), arg.FieldInterfaceTypes.Size());
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������
	oc_rel.New ();
	identifier relID = oc_rel.GetObjectID ();

// ����������� �������� � ���� �������
	oc_rel.m_Name						=	arg.Name;
	oc_rel.m_Description				=	arg.Description;
	oc_rel.m_FieldName				=	arg.FieldNames;
	oc_rel.m_FieldSysName			=	arg.FieldSysNames;
	oc_rel.m_FieldType				=	arg.FieldTypes;
	oc_rel.m_FieldDescription		=	arg.FieldDescriptions;
	oc_rel.m_FieldInterfaceType	=	arg.FieldInterfaceTypes;
	oc_rel.m_OwnerGUID				=	oc_login.GetObjectGUID ();
	oc_rel.m_FeodGUID					=	FeodGUIDs;
	oc_rel.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// ���������� �������������
	arg.objID							=	relID;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ ��������� ������������� ���������										[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_Enumerate (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_Enumerate);
/*............................................................................[]
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� ��������� ������ [L].
		<Password				������ ������������, �������������� ��������.
		<objFirstNo				����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
		<objLastNo				����� �������, �� �������� ������������ ��������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
		<FeodIDs					� ����� ����� ����������� ������ ������������ ���������.
		<FeodNames				������������, ���� ������ FeodIDs ����. ����� ���� "{Concept.Feod.Semantic...}"
		<Attributes				�������� �������. ����� ����������� ������ �� ���������, ������ ������������ � ������� ������ ���������� ����������. ������� [L] ���������� � ������ �������������.

		>objIDs					������ ��������������� ������������� ��������.
		>objVersions			������ ������ ���������
		>objNames				������ �������� ������������� ��������.
		>objSysNames			��������� �������� ���������
		>objDescriptions		������ �������� ������������� ��������.
		>TotalStoredNum		������� ����� �������� ����� ���� ����������� � ������ ��������.
		>MaxNumInQuery			����������� ���������� ����� ������������� �� ���� ��� ��������.

		>ExitCode				��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]





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
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_RELATION_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_RELATION_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "��������� %d ���������, � ����������� ����� ��������� %d", (arg.objLastNo - arg.objFirstNo), MAX_RELATION_ENUMERATE_NUM);
	}
// ���� �� ������� ID ������, ���� �� �� �����, ������� ��������� � �����
	if (arg.FeodIDs.Size()==0)
	{
		FOR_EACH_ITEM_EVAL(arg.FeodNames, 
		{
			arg.FeodIDs += GetFeodIDByType (arg.FeodNames[i]);
		});
	}
// ����� ������ ������������
	FOR_EACH_ITEM_EVAL (arg.FeodIDs, {if (!CHECK_FEOD_ID (arg.FeodIDs[i])) ERR_RETURN_COMMENT_1 (ERR_BadID, "������� �������������� ���� ������� ID=%u", arg.FeodIDs[i]);});
//	������ ���� ������ L
	if (arg.Attributes.Find ("L")==-1)
	{
		arg.Attributes += "L";
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������ ���� ��������
	int							i,j,N;
	OC_Relation					oc_rel;
	identifier_arr				ALL_RELATION_IDs;
	oc_rel.GetClassIdList	(ALL_RELATION_IDs);

// ����������� �� �������, � ������� ��� �������
	for (i=0; i<ALL_RELATION_IDs.Size(); i++)
	{
		if (USER_CHECK_ACCESS_TO_RELATION (loginID, ALL_RELATION_IDs[i], arg.Attributes)!=ERR_OK)
		{
			ALL_RELATION_IDs [i] = NA;
		}
	}

// ���������� �� ���� ��������������� �������� � ��������� �������� ���������
	for (N=0, j=0, i=0; i<ALL_RELATION_IDs.Size(); i++) if (ALL_RELATION_IDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) {j++; continue;} else j++; N++;

		oc_rel.Open (ALL_RELATION_IDs[i]);

		arg.objIDs				+= ALL_RELATION_IDs[i];
		arg.objVersions		+= oc_rel.m_Version;
		arg.objNames			+=	oc_rel.m_Name;
		arg.objSysNames		+=	oc_rel.m_SysName;
		arg.objDescriptions	+= oc_rel.m_Description;
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
//` ��������� ������ �������������� ���������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_GetData (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_GetData);
/*............................................................................[]
		<objID						������������� �������������� �������.
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ ��������� [R].
		<Password					������ ������������, �������������� ��������.

		>Name							�������� ���������.
		>Version						������ ���������.
		>SysName						��������� �������� ���������
		>Description				�������� ���������
		>FieldNames					�������� �����
		>FieldSysNames				��������� ����� �����, �������� ��� ���������� �++
		>FieldTypes					���� ����� ("object" "byte" "int" "bool" "time" "string" "float")
		>FieldDescriptions		�������� �����
		>FieldInterfaceTypes		���� �����, ���������������� �����������

		>FeodIDs						���� �������, � ������� ����������� ���������		
		>AccessLevelThreshold	��������� �������� ������ ������� ������������� � �������.
		>ReadOnly					����� �� ������������ ����� ������������� ������

		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Relation[%u] �� ����������", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
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
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [R] �� ������ ���������");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ��������� ������ �������
	int	i;
	arg.Name						=	oc_rel.m_Name;
	arg.Version					=	oc_rel.m_Version;
	arg.Description			=	oc_rel.m_Description;
	arg.FieldNames				=	oc_rel.m_FieldName;
	arg.FieldSysNames			=	oc_rel.m_FieldSysName;
	arg.FieldTypes				=	oc_rel.m_FieldType;
	arg.FieldDescriptions	=	oc_rel.m_FieldDescription;
	arg.FieldInterfaceTypes	=	oc_rel.m_FieldInterfaceType;
	arg.ReadOnly				=	(USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W")!=ERR_OK);
	for (i=0; i<oc_rel.m_FeodGUID.Size(); i++) arg.FeodIDs += guid(oc_rel.m_FeodGUID[i]).id;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ �������������� ���������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_PutData (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_PutData);
/*............................................................................[]
		<objID						������������� ����������� �������.
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [W].
		<Password					������ ������������, �������������� ��������.

		<Name							�������� ���������
		<SysName						��������� �������� ���������, �������� ��� ���������� �++
		<Description				�������� ���������
		<FieldNames					�������� �����
		<FieldSysNames				��������� ����� �����, �������� ��� ���������� �++
		<FieldDescriptions		�������� �����
		<FieldInterfaceTypes		���� �����, ���������������� �����������

		<FeodIDs						���� �������, � ������� ����������� ���������
		<AccessLevelThreshold	��������� �������� ������ ������� ������������� � �������.

		>Version						������ ���������.

		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Relation[%u] �� ����������", arg.objID);
	}
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// ��������� ����� ������� -- ����� ������ ����� ����� ������ �� ���� ����� ������� ���������
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [W] �� ��������� ���������");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ������� �� ������ ���� ������
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ��������� �� ������ ���� ������");
	}
// ��������� ������ ����� ���� �������
	if (arg.FeodIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "�� ������� ���� ������� ���������");
	}
// ��� ��������� ������ ���� ����������
	OC_Relation oc_rel;
	oc_rel.SetIndex_Name ();
	if (oc_rel.Find (arg.Name) && oc_rel.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "��� ��������� ������ ���� ����������");
	}
// ��������� ��� ������ ���� ����������
	if (!arg.SysName.CheckSysName())
	{
		SERVER_DEBUG_ERROR_1 ("������������ ��������� ��� '%s'", arg.SysName.c_str());
	}
// ��������� ��� ��������� ������ ���� ����������
	oc_rel.SetIndex_SysName ();
	if (oc_rel.Find (arg.SysName) && oc_rel.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "��������� ��� ��������� ������ ���� ����������");
	}
	oc_rel.Open (arg.objID);
//	��������� ������� �������
	if (oc_rel.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ��� ��������� ���������");
	}
// ��������� ����� ����� ������ ���� ����������� � �����������
	if (!RelationCheckFieldSystemNames (arg.FieldSysNames))
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "��� ��������� ����� ����� ������ ���� ����������� � �������c� ��� ���������� � �++!");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������ �� ����� ������ ���� �������, � ������� �� ����� �������� ������� [D]
	int i,j;
	for (i=0; i<oc_rel.m_FeodGUID.Size(); i++)
	{
		guid gi = oc_rel.m_FeodGUID[i];
		if (arg.FeodIDs.Find (gi.id)==-1)
		{
			if (USER_CHECK_ACCESS (loginID, gi.id, "D")!=ERR_OK)
			{
				string feodName;
				GetFeodName(gi.id, feodName);
				ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "������������ �� ����� ����� ������� ��������� �� ���� ������� %s", feodName.c_str());
			}
		}
	}
// ������������ �� ����� ��������� ���� �������, � ������� �� ����� �������� ������� [C]
	for (i=0; i<arg.FeodIDs.Size(); i++)
	{
		bool bFoundInRel = false;
	//	���� ��������� ���� � ���������
		for (j=0; j<oc_rel.m_FeodGUID.Size(); j++)
		{
			if (guid(oc_rel.m_FeodGUID[j]).id == arg.FeodIDs[i])
			{
				bFoundInRel = true;
				break;
			}
		}
	//	���� ���� �� ������� � ��������� -- ������ � ��������, ��������� �����
		if (!bFoundInRel && USER_CHECK_ACCESS (loginID, arg.FeodIDs[i], "C")!=ERR_OK)
		{
			string feodName;
			GetFeodName (arg.FeodIDs[i], feodName);
			ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "������������ �� ����� ����� ������� ��������� � ���� ������� %s", feodName.c_str());
		}
	}
// ��������������� ���� ������� � guid'�
	int f;
	guid_arr FeodGUIDs;
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		OC_Concept oc_feod;
		oc_feod.Open (arg.FeodIDs[f]);
		FeodGUIDs += oc_feod.GetObjectGUID ();
	}	
// ������ �������� ����������� �����, ��� ����� ���� ������������ ������� MOD_Relation_ChangeField
	if (oc_rel.m_FieldName.Size()!=arg.FieldNames.Size() || oc_rel.m_FieldSysName.Size()!=arg.FieldSysNames.Size() || oc_rel.m_FieldDescription.Size()!=arg.FieldDescriptions.Size() || oc_rel.m_FieldDescription.Size()!=arg.FieldInterfaceTypes.Size())
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "������ �������� ����������� �����, ��� ����� ���� ������������ ������� MOD_Relation_ChangeField");
	}
//----------------------------------------------------------------------------[] 



	
	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ���� �������
	oc_rel.m_Name						=	arg.Name;
	oc_rel.m_Description				=	arg.Description;
	oc_rel.m_FieldName				=	arg.FieldNames;
	oc_rel.m_FieldSysName			=	arg.FieldSysNames;
	oc_rel.m_FieldDescription		=	arg.FieldDescriptions;
	oc_rel.m_FieldInterfaceType	=	arg.FieldInterfaceTypes;
	oc_rel.m_FeodGUID					=	FeodGUIDs;
	oc_rel.m_AccessLevelThreshold	=	max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);

// �������� ������ ���������
	oc_rel.m_Version					+=	1;
	arg.Version							=	oc_rel.m_Version;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ����� �������������� ���������												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_ChangeField (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_ChangeField);
/*............................................................................[]
		<objID						������������� ����������� �������.
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [W].
		<Password					������ ������������, �������������� ��������.

		<ChangeType					0 - �������� ����� ����, 1 - ������� ����, 2 - ����������� ����, 3 - �������������.
		<FieldID						�������������� (�������) ����. ����� �������� � ����� ���� ������ �������� ������� ��������.
		<FieldPos					���� ���� ����������. ������������ ��� ��������, ���� ���������� ����.
		<FieldName					����� ��� ���� ��� ��� ������ ����. ������������ ��� ������� ������ � �������������� ������� ����.
		<FieldSysName				����� ��������� ��� ���� ��� ��������� ��� ������ ����, �������� ��� ���������� �++. ������������ ��� ������� ������ � �������������� ������� ����.
		<FieldDescription			����� �������� ���� ��� �������� ������ ����. ������������ ��� ������� ������ � �������������� ������� ����.
		<FieldInterfaceType		��� ����, ���������������� �����������

		>Version						������ ���������.

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!CHECK_RELATION_ID (arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Relation[%u] �� ����������", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_login (loginID);
// ��������� ����� ������� -- ����� ������ ����� ����� ������ �� ���� ����� ������� ���������
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [W] �� ��������� ���������");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
//	��������� ������� �������
	if (oc_rel.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ��� ��������� ������ ����� ���������");
	}
//----------------------------------------------------------------------------[] 


	
	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ���� �������
	int oc_rel_m_FieldName_Size = oc_rel.m_FieldName.Size ();
	OC_Linkage oc_link;
	oc_link.SetIndex_RelationID();
	key_arr ka; ka+=arg.objID;
	switch (arg.ChangeType)
	{
	// ������� ������ ����
		case ChangeField_Insert:
		{
			if (arg.FieldID<0) ERR_RETURN_COMMENT_1 (ERR_BadArgument, "������������ �������� ��������� FieldID = %d", arg.FieldID);
			if (!RelationCheckFieldSystemName	(arg.objID, arg.FieldSysName.c_str(), -1))	ERR_RETURN_COMMENT (ERR_BadArgument, "��� ��������� ����� ����� ������ ���� ����������� � �������c� ��� ���������� � �++!");
			oc_rel.m_FieldName.Insert				(arg.FieldID, arg.FieldName);
			oc_rel.m_FieldSysName.Insert			(arg.FieldID, arg.FieldSysName);
			oc_rel.m_FieldDescription.Insert		(arg.FieldID, arg.FieldDescription);
			oc_rel.m_FieldInterfaceType.Insert	(arg.FieldID, arg.FieldInterfaceType);

		// �������� ��������� ������
			for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
			{
			// � ���� ����������� � ����� ��������-������ ������������ ����� ���� (�������)
				for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
				{
					identifier link_id	= oc_link.GetObjectID ();
					identifier proxy_id	= identifier(oc_link.m_ProxyID[i]);

				// ���� � ����� ������������ �� ������, � ��������, ��� �� ������ ������, �� ������ �� ������
					if (proxy_id==NA) continue;

					OC_LinkProxy oc_proxy (proxy_id);

				//	������� ������������� ����� ����� ������, � ������� ��������� ������-������
					for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
					{
					//	���� ������� ������ ��� ����� ������������ ����, ����������� �
						if (oc_proxy.m_RelationField[j] >= arg.FieldID)
						{
							oc_proxy.m_RelationField[j] += 1;
						}
					}
				}

			// ��������� �� ��� ����� ������ ������� �� ����� ������������ ����
				oc_link.m_ProxyID.Insert (arg.FieldID, NA);

			// �������� -- ����� ��������� �������� ������ ���� ����� ����� ����� � ���������
				if (oc_link.m_ProxyID.Size () != oc_rel_m_FieldName_Size) SERVER_DEBUG_ERROR_2 ("oc_link.m_ProxyID.Size () != oc_rel.m_FieldName.Size ()   ---  %d!=%d", oc_link.m_ProxyID.Size (), oc_rel.m_FieldName.Size ());
			}
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// �������� ����
		case ChangeField_Delete:
		{
		// �������� ������ ����
			if (arg.FieldID<0 || arg.FieldID>= oc_rel.m_FieldName.Size())	ERR_RETURN_COMMENT_1 (ERR_BadArgument, "������������ �������� ��������� FieldID = %d", arg.FieldID);
		// � ��������� ������ ���� �� ����� 1-�� ����
			if (oc_rel.m_FieldName.Size()<=1)										ERR_RETURN_COMMENT   (ERR_BadArgument, "� ��������� ������ ���� �� ����� 1-�� ����");
		// � ��������� ������ ����������� ���� �� ���� ������
			int nObjField=0; for (int f=0; f<oc_rel.m_FieldType.Size(); f++) if (f!=arg.FieldID) if (oc_rel.m_FieldType[f]=="object") nObjField++;
			if (nObjField<=0)																ERR_RETURN_COMMENT   (ERR_BadArgument, "� ��������� ������ ����������� ���� �� ���� ������");

			oc_rel.m_FieldName.Del				(arg.FieldID);
			oc_rel.m_FieldSysName.Del			(arg.FieldID);
			oc_rel.m_FieldDescription.Del		(arg.FieldID);
			oc_rel.m_FieldInterfaceType.Del	(arg.FieldID);
		// �������� ��������� ������
			for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
			{
			// � ���� ����������� � ����� ��������-������ ������������ ����� ���� (�������)
				for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
				{
					identifier link_id	= oc_link.GetObjectID ();
					identifier proxy_id	= identifier(oc_link.m_ProxyID[i]);

				// ���� � ����� ������������ �� ������, � ��������, ��� �� ������ ������, �� ������ �� ������
					if (proxy_id==NA) continue;

					OC_LinkProxy oc_proxy (proxy_id);
				//	������� ������������� ����� ����� ������, � ������� ��������� ������-������
					for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
					{
					//	���� ������� ��������� � ������������ �����, ������� ���� �����
						if (oc_proxy.m_RelationField[j] == arg.FieldID)
						{
							oc_proxy.m_LinkageID.Del		(j);
							oc_proxy.m_RelationID.Del		(j);
							oc_proxy.m_RelationField.Del	(j);
							j --;
						}
					//	���� ������� ������ ��� ����� ���������� ����, ��������� �
						if (oc_proxy.m_RelationField[j] > arg.FieldID)
						{
							oc_proxy.m_RelationField[j] -= 1;
						}
					}
				}

			//	���������� ��������� ������, ����������� �� ������� ���������� �� ��������� ����
				oc_link.m_ProxyID.Del (arg.FieldID);

			// �������� -- ����� ��������� �������� ������ ���� ����� ����� ����� � ���������
				if (oc_link.m_ProxyID.Size () != oc_rel_m_FieldName_Size) SERVER_DEBUG_ERROR_2 ("oc_link.m_ProxyID.Size () != oc_rel.m_FieldName.Size ()   ---  %d!=%d", oc_link.m_ProxyID.Size (), oc_rel.m_FieldName.Size ());
			}
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// �������������� ����
		case ChangeField_Rename:
		{
			if (arg.FieldID<0 || arg.FieldID>= oc_rel.m_FieldName.Size())									ERR_RETURN_COMMENT_1 (ERR_BadArgument, "������������ �������� ��������� FieldID = %d", arg.FieldID);
			if (!RelationCheckFieldSystemName (arg.objID, arg.FieldSysName.c_str(), arg.FieldID))	ERR_RETURN_COMMENT   (ERR_BadArgument, "��� ��������� ����� ����� ������ ���� ����������� � �������c� ��� ���������� � �++!");
			oc_rel.m_FieldName			[arg.FieldID]	=	arg.FieldName;
			oc_rel.m_FieldSysName		[arg.FieldID]	=	arg.FieldSysName;
			oc_rel.m_FieldDescription	[arg.FieldID]	=	arg.FieldDescription;
			oc_rel.m_FieldInterfaceType[arg.FieldID]	=	arg.FieldInterfaceType;
		}
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	// ����������� ����
		case ChangeField_Move:
			ERR_RETURN_COMMENT (ERR_FunctionNotImplemented, "����������� ����� ���� �� �����������");
		break;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]



	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
	//	������
		default:
			ERR_RETURN_COMMENT_1 (ERR_BadArgument, "������ �������� ��� �������� ��� ������ [%d], ���������� ����: 0 - �������� ����� ����, 1 - ������� ����, 2 - ����������� ����, 3 - ������������� ����.", arg.ChangeType);
		break;
	}

// �������� ������ ���������
	oc_rel.m_Version	+=	1;
	arg.Version			=	oc_rel.m_Version;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� �������������� ���������														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Relation_Delete (MOD_Relation_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Relation_Delete);
/*............................................................................[]
		<objID					������������� ���������� ���������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� �������� [D] ��������� �� ���� ����� �������.
		<Password				������ ������������, �������������� ��������.

		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_Relation, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Relation[%u] �� ����������", arg.objID);
	}
	OC_Relation oc_rel (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� ������� -- ������������ ������ ����� ����� ������� ��������� �� ���� ��� ����� �������
	res = USER_CHECK_ACCESS_TO_RELATION (loginID, oc_rel.GetObjectID(), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� ��� ���������� ��������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������ ���� ������
	OC_Linkage oc_link;
	oc_link.SetIndex_RelationID();
	key_arr ka; ka+=arg.objID;

// ������� ��� ����� ���������� ��������� � ��� ������ � �� � ������-��������
	for (oc_link.Find (ka); oc_link.IsValid (); oc_link++)
	{
	// ���������� �� ���� ����������� � ����� ��������-������
		for (int i=0; i<oc_link.m_ProxyID.Size(); i++)
		{
			identifier link_id = oc_link.GetObjectID ();
			OC_LinkProxy oc_proxy (identifier(oc_link.m_ProxyID[i]));
		//	������� ��������� ����� ����� ������, � ������� ��������� ������-������
			for (int j=0; j<oc_proxy.m_LinkageID.Size(); j++) if (oc_proxy.m_LinkageID[j] == link_id)
			{
				if (oc_proxy.m_LinkageID[j] == link_id)
				{
					oc_proxy.m_LinkageID.Del		(j);
					oc_proxy.m_RelationID.Del		(j);
					oc_proxy.m_RelationField.Del	(j);
					j --;
				}
			}
		}
	//	������� �����
		oc_link.Delete ();
	}

// ���������� ���������
	oc_rel.Delete ();
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