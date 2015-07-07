/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoDiv.cpp															[]
[] Date:          13.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������� ����������.										[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoDiv.inc.h"









//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ �������																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_New (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_New);
/*............................................................................[]
		<Login                  ����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� �������� � ��������� ���� �������.
		<Password               ������ ������������, �������������� ��������.
		<Name                   ��� ������������ �������. ��� ���� ��������� ���� � ����������� ������. ���� �������� ������ ��� ������������ ���, �� ������� ���� �����������/�������� ��� �������.
		<Description            �������� ������������ �������.
		<ParentID               ������������ ������.
		<AccessLevelThreshold   ��������� �������� ������ ������� �������������. ������ ������ ����� ����� ������ �����, ��� ������� � ���������, ����� ��� ��� ��� �������/�������.

		>objID                  ������������� ���������� �������.
		>ExitCode               ��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment        ��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������ ������ ������ ������������
	if (!CHECK_INFODIV_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ ������������ ������ ID=%d", arg.ParentID);
	}
	OC_InfoDiv oc_parent_div (arg.ParentID);
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
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ����� ����� ������ �����, ��� ������� ��� ���������, 
// ����� ��� ��� ��� �������/�������.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
	}
// ��� ������� �� ������ ���� ������
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������� �� ������ ���� ������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ����
	MOD_Feod_Args feod_arg;

	feod_arg.Login							= arg.Login;
	feod_arg.Password						= arg.Password;
	feod_arg.Name							= arg.Name;
	feod_arg.Description					= arg.Description;
	feod_arg.ParentID						= guid(oc_parent_div.m_MOD_Base_GUID).id;
	feod_arg.AccessLevelThreshold		= arg.AccessLevelThreshold;

	MOD_Feod_New (feod_arg);
	if (feod_arg.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

// ������ ������, ��������� ��� � �������� ���������� ���������� �����
	SET_MOD_EXTENSION (Concept, feod_arg.objID, InfoDiv, arg.objID);
//----------------------------------------------------------------------------[] 

	CACHE_NUM_InfoDivGetAllSubDivIDs ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ �������� 																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_Enumerate (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ��������� ������.
		<Password					������ ������������, �������������� ��������.
		<ParentID               ������, ��� ���������� ������� �����������. ���� NA -- ������������ ParentName.
		<ParentName             ������, ��� ���������� ������� �����������. ���������� ���������� ������� ���: "Concept.Feod.Data.Type.News.��������������.�����"
		<IncludeParent          ���� true, �� ������������ � ��� ParentID, ����� ������ ��� �������.
		<FeodAttributes			�������� ������� � �������. ����� ����������� ������ �� �������, ������ ������������ � ������� ������ ���������� ����������.
		<FullNameLevel				������� � �������� ���������, ������� � �������� ��������� �������� �������.

		>objIDs						������ ��������������� ��������. �������� ������ �� �������, � ������� ���� ������ � ���������� ����������.
		>objNames					������ ������ �������� ��������.
		>objTypes					������ ����� �������� ("Concept.Feod.Data.Type.News")
		>objLevels					������ ������� ����������� ��������. � ������������� ������� ������� ����������� ��������� = 0.
		>objFeodIDs					������ ��������������� ��������������� ��� �������.
		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
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
		ERR_RETURN_COMMENT (res, "�������� ������ ��� �����");
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� �� ������ ������������� ������������� ������� -- ���� �� ����
	if (arg.ParentID==NA)
	{
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			ERR_RETURN_COMMENT_1 (ERR_BadName, "�� ������ ������������ ������ '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetInfoDivIDByFeodID (feod_parent_ID);
	}
// ������ ������ ������������
	if (!CHECK_INFODIV_ID (arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ ������ %d", arg.ParentID);
	}
	identifier feod_parent_ID = GetFeodIDByInfoDivID (arg.ParentID);
//----------------------------------------------------------------------------[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ������ ���� ������������� �������� -- ��� ������ � ��� �������
	int f;
	identifier_arr FeodArr;
	GetFeodDescendantIDs (feod_parent_ID, FeodArr);
	if (arg.IncludeParent) 
	{
		FeodArr.Insert (0, feod_parent_ID);
	}
// ���������� �� ����������, � ������� ��� �������
	if (!arg.FeodAttributes.IsEmpty()) for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], arg.FeodAttributes)!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// ��������� �������� ���������
	int parent_level = GetFeodLevel (feod_parent_ID);
	for (f=0; f<FeodArr.Size(); f++) if (CHECK_FEOD_ID (FeodArr[f]))
	{
		identifier divID = GetInfoDivIDByFeodID (FeodArr[f]);

		string divName;
		GetInfoDivFullName (divID, divName, arg.FullNameLevel);

		string divType;
		GetInfoDivType (divID, divType);

		int divLevel =	GetFeodLevel (FeodArr[f]) - parent_level;

		arg.objIDs		+= divID;
		arg.objNames	+= divName;
		arg.objTypes	+= divType;
		arg.objFeodIDs	+=	FeodArr[f];
		arg.objLevels	+= divLevel;
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� �������																				[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoDiv_Delete (MOD_InfoDiv_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoDiv_Delete);
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
	identifier	div_id = arg.objID;
	if (!CHECK_INFODIV_ID (div_id))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ InfoDiv[%d] �� ����������", div_id);
	}
	OC_InfoDiv	oc_div	(div_id);
	identifier feod_id = GetFeodIDByInfoDivID (div_id);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.Feod"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ������� (��� ����� Concept.Feod.Admin.Feod[D])");
	}
	res = USER_CHECK_ACCESS (loginID, feod_id, "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ������ ������ (��� ������� [m] ��� [M])");
	}
	res = USER_CHECK_ACCESS (loginID, GetFeodParentID (feod_id), "m");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� ������ ������ (��� ������� � ��������� ��������� ������������� ������� -- [M] ��� [m])");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���������� ��� ��������� ������� (��� + ��������)
	identifier_arr	DivArr;
	InfoDivGetAllSubDivIDs (arg.objID, DivArr);
	DivArr.Insert (0, arg.objID);

// ���������� ��������������� ���� (� �������� �����)
	MOD_Feod_Args			feod_arg;
	feod_arg.Login			= arg.Login;
	feod_arg.Password		= arg.Password;
	feod_arg.objID			= feod_id;
	MOD_Feod_Delete (feod_arg);
	if (feod_arg.ExitCode != ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

//	������ �� ������� ������ ���� ������� �� ���������� � �� �������������� ��������
	int i, d, iDiv;
	for (iDiv=0; iDiv<DivArr.Size(); iDiv++)
	{
		div_id = DivArr[iDiv];
		oc_div.Open (div_id);
	// ������� ������ �� ������� �� ����������
		for (i=0; i<oc_div.m_InfoSourceSortedID.Size(); i++)
		{
			OC_InfoSource oc_src;
			if (OC_Exist (OBJ_CLASS_ID_InfoSource, oc_div.m_InfoSourceSortedID[i]))
			{
				oc_src.Open (oc_div.m_InfoSourceSortedID[i]);
				for (d=0; d<oc_src.m_InfoDivID.Size(); d++) if (oc_src.m_InfoDivID[d] == div_id)
				{
					oc_src.m_InfoDivID.Del (d);
					d--;
				}
			}
		}
	// ������� ������ �� ������� �� �������������� ��������
		for (i=0; i<oc_div.m_InfoObjectSortedID.Size(); i++)
		{
			OC_InfoObject oc_info;
			if (OC_Exist (OBJ_CLASS_ID_InfoObject, oc_div.m_InfoObjectSortedID[i]))
			{
				oc_info.Open (oc_div.m_InfoObjectSortedID[i]);
				for (d=0; d<oc_info.m_InfoDivID.Size(); d++) if (oc_info.m_InfoDivID[d] == div_id)
				{
					oc_info.m_InfoDivID.Del (d);
					d--;
				}
			}
		}

	// ���������� ��� ������ � ��� ��� �������� �������
		oc_div.Delete	();
	}
//----------------------------------------------------------------------------[] 


	CACHE_NUM_InfoDivGetAllSubDivIDs ++;
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