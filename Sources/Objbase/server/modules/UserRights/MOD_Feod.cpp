/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Feod.cpp																[]
[] Date:          07.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ������ �������, ���������� ����� {Concept.Feod})	[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_Feod.inc.h"





//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ �����																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_New (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_New);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� ��� �������.
		<Password					������ ������������, �������������� ��������.
		<Name							��� ����������� ����. ���� �������� ������ ��� ������������ ���, �� ������� ���� �����������/�������� �������� ���� �������.
		<Type							��� ����������� ����. ���� �� ������, ����� �����.
		<Description				�������� ����������� ����.
		<ParentID					���� �������� ������. ������������ ������ ����� ����� ��������� �������� ���� ������� � ��������� ���� (�������� ������ �� ��� ���� � ��������� [M]).
		<ParentName					��� ���� �������� ������. ������������, ����� �� ������ ParentID.
		<AccessLevelThreshold	��������� �������� ������ ������� �������������. ���� ������ ����� ����� ������ �����, ��� ������� � ���������, ����� ��� ��� � �������/�������.

		>objID						������������� ��������� ����.
		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� �� ������ ParentID, ���� ��� �� ParentName
	if (arg.ParentID==NA) 
	{
		arg.ParentID = GetFeodIDByType (arg.ParentName);
	}

// ������ ������ ������������
	if (!CHECK_FEOD_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_2 (ERR_BadID, "������� ������������ ������������� [%u] ��� ��� '%s' ������������ ���� �������.", arg.ParentID, arg.ParentName.c_str());
	}
	OC_Feod oc_parent_feod (arg.ParentID);

// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Feod", "C", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� �������� ������� �������� ��� �������");
	}
// ��������� ����������� ��������������� � ����� ������� ParentID
	res = USER_CHECK_ACCESS (loginID, arg.ParentID, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� �������������� (������� [M] ��� [m]) ������ ��������� ���� �������.");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� ������ ����� ����� ������ �����, ��� ������� � ���������, 
// ����� ��� ��� � �������/�������.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
	}
// ���� ��� �� ������, ���������� ���.
	if (arg.Type.IsEmpty())
	{
		arg.Type = arg.Name;
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� �������� ������ ��� -- ����������� ���.
	if (arg.Name.IsEmpty())
	{
		arg.Name.Format ("%s feod", arg.Login.c_str());
	}

// ��� ���� ������ ���� ����������.
	string OriginalName	= arg.Name;
	string OriginalType	= arg.Type;
	string parentFeodType;
	string newFeodType;
	GetFeodType (arg.ParentID, parentFeodType);
	newFeodType.Format ("%s.%s", parentFeodType.c_str(), OriginalType.c_str());
	if (GetFeodIDByType(newFeodType)!=NA)
	{
		for (int r=4; r<80; r++)
		{
			string rnd;
			rnd.Randomize (r, "ABCDEF0123456789");
			string newName;
			newFeodType.Format ("%s.%s [%s]", parentFeodType.c_str(), OriginalType.c_str(), rnd.c_str());
			if (GetFeodIDByType (newFeodType)==NA)
			{
				break;
			}
		}
		if (GetFeodIDByType(newFeodType)!=NA)
		{
			ERR_RETURN_COMMENT (ERR_NameAlreadyExists, "�� ������� ������������� ���������� ��� ��� ���� �������");
		}
	}

// ������ ���� ��� �������
	MOD_Concept_Args concept_arg;
	concept_arg.ParentID				= arg.ParentID;
	concept_arg.Name					= OriginalName;
	concept_arg.Description			= arg.Description;
	concept_arg.Type					= newFeodType;
	concept_arg.TypeNo				= ConceptGetUnicTypeNo ();
	GetPicklockPassword (concept_arg.PicklockPassword);
	res = MOD_Concept_New (concept_arg);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_2 (res, "�� ������� ������� ���� '%s {%s}' ��� �������", OriginalName.c_str(), newFeodType.c_str());
	}
	identifier feodID = concept_arg.objID;
	OC_Feod oc_feod (feodID);

// ������������� ����� ������� � ����, ������������ � ����� �� ��� ����� 
// ������ �������� �� ������ �������/������������� ����.
	SET_EXT_FIELD (oc_feod, AccessLevelThreshold, arg.AccessLevelThreshold);

// ���������� ������������� ��������� ����.
	SET_EXT_FIELD (oc_feod, OwnerID, loginID);

// ���������� ��������� ���� � ������ ����������� ��� ������������, ����� �� ��� �� �������������.
	oc_login.m_OwnFeodID += feodID;

// �������� ��������� ���� � ������� ������ �������, ��� ������� �� ����.
	identifier rootGroupID = arg.Login=="{{IMPORT}}" ? NA : GetGroupIDByType ("root");
	if (rootGroupID != NA)
	{
		OC_UserGroup oc_root_group (rootGroupID);
		oc_root_group.m_Rights_Feod	+= feodID;
		oc_root_group.m_Rights_Attr	+= ALL_ATTRIBUTES;
	//	�������� ����� ���� ������� ������
		UserGroupSimplifyRightsSet	(rootGroupID);
	}
	arg.objID = feodID;
//----------------------------------------------------------------------------[] 



	
	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ ��������� ��� �������														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_Enumerate (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ��������� ������ [L].
		<Password					������ ������������, �������������� ��������.
		<ParentID					������������� �����, �������� �������� �����������.
		<ParentName					������������, ���� ParentID == NA.

		>objIDs						�������������� ������, ������� ������������ (objID)
		>objNames					�������� ������
		>objTypes					���� ������, ������ ���� �� ����� ("Feod.Concept.Data")
		>objDescriptions			�������� ������
		>objParentIDs				�������������� ������������ ������ ��� NA ��� �����
		>objThresholds 			������ �������
		>objExtClassNames			�������� �������-���������� ��� ���������������� �������
		>objExtIDs					�������������� ��������-���������� ��� ���������������� �������

		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� �� ������ ������������� ������������ ����� -- ���� �� �����
	if (arg.ParentID==NA)
	{

		arg.ParentID = GetFeodIDByType (arg.ParentName);
		if (arg.ParentID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("�� ������ ������������ ���� '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "�� ������ ������������ ���� '%s'", arg.ParentName.c_str());
		}
	}
// ������������ ���� ������ ������������
	if (!CHECK_FEOD_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ ������������ ���� ID=%u", arg.ParentID);
	}
	identifier feodID  = arg.ParentID;
	OC_Feod oc_feod (feodID);
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
		ERR_RETURN_COMMENT (res, "�������� ������ ��� �����");
	}
// ��������� ������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ���� ������������ ��� ������� Concept.Feod.Admin.Feod[L]");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[] 


	
	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������ ���� ��� �������
	int				f;
	int MAX_CLASS_NUM = 1024; // !!! ����������� � ����.
	identifier_arr FeodArr;
	GetFeodDescendantIDs (feodID, FeodArr);
	FeodArr.Insert (0, feodID);
	
// ���������� �� ���� �������, ������� �� ����� ���� �����������
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], "L")!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// ���������� �� ���� ����������� �������� � ��������� �������� ���������
	for (f=0; f<FeodArr.Size(); f++)
	{
		OC_Concept oc_feod (FeodArr[f]);

		int AccessLevel = SYSTEM_ACCESS_LEVEL;
		GET_EXT_FIELD (oc_feod, AccessLevelThreshold, AccessLevel);
		guid gi = guid(oc_feod.m_MOD_Extension_GUID);
		const char * ExtClassName = (gi.cl>=0 && gi.cl<(identifier)MAX_CLASS_NUM)? className [gi.cl]: "";

		arg.objIDs				+=	FeodArr[f];
		arg.objNames			+=	oc_feod.m_Name;
		arg.objTypes			+=	oc_feod.m_Type;
		arg.objDescriptions	+=	oc_feod.m_Description;
		arg.objParentIDs		+=	oc_feod.m_Parent;
		arg.objThresholds 	+=	AccessLevel;
		arg.objExtClassNames	+=	ExtClassName;
		arg.objExtIDs			+=	gi.id;
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ���� �������																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_Feod_Delete (MOD_Feod_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Feod_Delete);
/*............................................................................[]
		<objID					������������� ���������� �������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� �������� [D].
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
	identifier	feod_id = arg.objID;
	if (!CHECK_FEOD_ID (feod_id))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ Feod[%u] �� ����������", feod_id);
	}
	OC_Feod	   oc_feod (feod_id);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	OC_User oc_user;
	oc_user.Open (loginID);

// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ���� ������� (��� ����� Concept.Feod.Admin.Feod[D])");
	}
// �������� ����������� ����������� ������������ ���� �������
	res = USER_CHECK_ACCESS (loginID, feod_id, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ������ ������ (��� ������� [m] ��� [M])");
	}
// �������� ����������� ����������� ��������� ���� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodParentID (feod_id), "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ������ ������ (��� ������� � ��������� ��������� ������������ ���� ������� -- [M] ��� [m])");
	}
// �������� ������ �������
	int AccessLevel = SYSTEM_ACCESS_LEVEL;
	GET_EXT_FIELD (oc_feod, AccessLevelThreshold, AccessLevel);

	if (oc_user.m_AccessLevel >= AccessLevel)
	{
		ERR_RETURN_COMMENT_2 (ERR_InsufficientAccessLevel, "� ������������ ������������� ������� (%d) ��� �������� ���� ������� � ������� ������� (%d)", int(oc_user.m_AccessLevel), AccessLevel);
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������� ������ �� �������� ���� � ��� �������� ����� �� ���� ������ 
	identifier_arr			FeodArr;
	GetFeodDescendantIDs (arg.objID, FeodArr);
	FeodArr.Insert			(0, arg.objID);

	identifier_arr			GroupArr;
	OC_UserGroup			oc_group;
	oc_group.GetClassIdList (GroupArr);

// ������� ������ �� ����� �� �����
	for (int g=0; g<GroupArr.Size(); g++)
	{
		oc_group.Open (GroupArr[g]);

		if (oc_group.IsValid()) for (int f=0; f<FeodArr.Size(); f++)
		{
			for (;;)
			{
				int index = oc_group.m_Rights_Feod.Find (FeodArr[f]);
				if (index==-1) break;
				oc_group.m_Rights_Feod.Del (index);
				oc_group.m_Rights_Attr.Del (index);
			}
		}
	}

// � ���� ������������� ������� ���� � �������� ����� �� "����������� ��� �������"
	identifier_arr				UserArr;
	oc_user.GetClassIdList (UserArr);
	for (int u=0; u<UserArr.Size(); u++)
	{
		oc_user.Open (UserArr[u]);
		if (oc_user.IsValid()) for (int f=0; f<FeodArr.Size(); f++)
		{
			for (;;)
			{
				int index = oc_user.m_OwnFeodID.Find (FeodArr[f]);
				if (index==-1) break;
				oc_user.m_OwnFeodID.Del (index);
			}
		}
	}


// ���������� ���� ��� �������
	MOD_Concept_Args concept_arg;
	concept_arg.objID = arg.objID;
	GetPicklockPassword (concept_arg.PicklockPassword);
	res = MOD_Concept_Delete (concept_arg);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_1 (res, "�� ������� ���������� ���� %u ��� �������", arg.objID);
	}
//----------------------------------------------------------------------------[] 



	
	CACHE_NUM_USER_CHECK_ACCESS ++;
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