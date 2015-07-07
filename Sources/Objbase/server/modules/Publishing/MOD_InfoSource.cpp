/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoSource.h															[]
[] Date:          21.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������������� �����������								[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoSource.inc.h"				 






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ ��������������� ���������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_New (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_New);
/*............................................................................[]
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� {Concept.Feod.Aux.Sources}[C].
		<Password				������ ������������, �������������� ��������.
		<Name						�������� ��������� ����������.
		<Description			�������� ��������� ����������.
		<URL						Web-�����, �� �������� ��������� �������� ����������.
		<RefreshType			[int] ���������������� ����������� �������, ������������ ����� �������� ��������� ����������.
		<divIDs					� ����� �������������� �������� ����� ���������� ��������. ����� ��������� ������ �� �������, � ������� ���� ����� [R] � ([C] ��� [W]).

		>objID					������������� ���������� �������.
		>ExitCode				��� �������� (OK BadLogin BadPassword BadName BadID AccessDeny ERR_InsufficientAccessLevel).
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
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "C");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� �������� �������������� ����������");
	}
// ������������ ����� ��������� ������ �� �������, � ������� ���� ����� [R] � ([C] ��� [W]).
	for (int d=0; d<arg.divIDs.Size(); d++)
	{
		if (USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "RC")!=ERR_OK && USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "RW")!=ERR_OK)
		{
			if (!CHECK_INFODIV_ID(arg.divIDs[d]))
			{
				ERR_RETURN_COMMENT_1 (ERR_BadID, "������������ ������������� ������� %d", arg.divIDs[d]);
			}
			else
			{
				string divName;
				GetInfoDivFullName (arg.divIDs[d], divName);
				ERR_RETURN_COMMENT_1 (ERR_InsufficientAccessLevel, "������������ �� ����� ����� ��������� �������� ������� %s, ��� ��� �� ����� ������[R] � (���������[C] ��� �������������[W]) ������� � ���� �������.", divName.c_str());
			}
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
// ��� ������� ������ ���� ����������
	OC_InfoSource oc_src;
	oc_src.SetIndex_Name ();
	if (oc_src.Find (arg.Name))
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "��� ������������ ��������� ������ ���� ����������. �������� '%s' ��� ����������.", arg.Name.c_str());
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������
	oc_src.New();
	identifier srcID	= oc_src.GetObjectID ();

// ����������� �������� � ���� �������
	oc_src.m_Name				=	arg.Name;
	oc_src.m_Description		=	arg.Description;
	oc_src.m_RefreshType		=	arg.RefreshType;
	oc_src.m_URL				=	arg.URL;
	oc_src.m_InfoDivID		=	arg.divIDs;

// ������� �������� � �������
	FOR_EACH_ITEM_EVAL (arg.divIDs,
	{
		OC_InfoDiv (arg.divIDs[i]).m_InfoSourceSortedID.InsertSorted (srcID);
	});

// ���������� ������������� ���������� ���������
	arg.objID = srcID;

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ ��������� �������������� ����������									[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_Enumerate (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_Enumerate);
/*............................................................................[]
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� {Concept.Feod.Aux.Sources}[L].
		<Password				������ ������������, �������������� ��������.
		<objFirstNo				����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
		<objLastNo				����� �������, �� �������� ������������ ��������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
		<ShowAll					���� true, �� ������� ������ ���� �������������� ����������, ����� ������ ���, ������� ������������ ����� ��������� �������������� ��������.
		<divID					������������� ��������� ������ ���������� � ���������� ������� ��� ��� ��������. ���� NA, �� �������� �� ���� �������� {Concept.Feod.Data}.
		<divName					����� ���� �����������, ���� �� ������ divID.

		>objIDs					������ ��������������� �������������� ����������. ���� ShowAll=false, �� �������� ������ ����������� � ��������, � ������� � ������������ ���� ����������� ��������� ��� ������� ������� (������ [C] ��� [W]).
		>objNames				������ �������� �������������� ����������.
		>objURLs					web-������.
		>objRefreshTypes		[int_arr] ���������������� ����������� �������, ������������ ����� �������� ��������� ����������.
		>objDescriptions		��������. �������� ������ � ������ ������� ����� {Concept.Feod.Aux.Sources}[R].

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
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ��������� ������ �������������� ����������");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_INFOSOURCE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_INFOSOURCE_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "��������� %d �������� ������ InfoSource, � ����������� ����� ��������� %d", (arg.objLastNo - arg.objFirstNo), MAX_INFOSOURCE_ENUMERATE_NUM);
	}
// ���� �� ������ ID �������, �� ������� ��� -- �������� ���������� ��� �� �����
	if (arg.divID==NA && !arg.divName.IsEmpty())
	{
		arg.divID = GetInfoDivIDByType (arg.divName);
	}
//	����� -- ���� �������� ������
	else 
	{
		arg.divID = GetInfoDivIDByFeodID (GetFeodIDByType("Concept.Feod.Data"));
	}

// ���� ������ ������, �� �������� ��� �� ����������
	if (!CHECK_INFODIV_ID(arg.divID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "��������� ������ ID=%d �� ���������", arg.divID);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������ �������������� ����������, ������� � ��� ��������,
// � ������� ������������ ����� ��������� ��� ������������� �������������� �������.

//	�������� ������ ��� ��������� ������-��������
	identifier_arr allFeodIDs;	
	identifier rootFeodID = GetFeodIDByInfoDivID (arg.divID);
	if (!GetFeodDescendantIDs (rootFeodID, allFeodIDs))
	{
		ERR_RETURN_COMMENT (ERR_SYSTEM_ERROR, "���������� �������� ������ ��� ������� ��� �������");
	}
	allFeodIDs.Insert (0, rootFeodID);

//	��� �����, ��� ������ �� �� ��� (���� ShowAll==false), � ������� ���� ����� ������� [R] � ([C] ��� [W]), 
// ����������� � ������� � ��������� ��������� ����������.
	identifier_arr allSrcSortedIDs;
	for (int f=0; f<allFeodIDs.Size(); f++)
	{
		if (arg.ShowAll || (USER_CHECK_ACCESS (loginID, allFeodIDs[f], "RC")==ERR_OK) || (USER_CHECK_ACCESS (loginID, allFeodIDs[f], "RW")==ERR_OK))
		{
		// ���� ����-������ ������� ��� ���������� ������ ����������
			identifier divID = GetInfoDivIDByFeodID (allFeodIDs[f]);
			if (divID==NA || !CHECK_INFODIV_ID (divID))
			{
				string feodName;
				GetFeodFullName (allFeodIDs[f], feodName);
				SERVER_DEBUG_ERROR_2 ("���� '%s'[%d] �� �������� ��������.", feodName.c_str(), allFeodIDs[f]);
				continue;
			}
			identifier_arr oc_div_m_InfoSourceSortedID = OC_InfoDiv(divID).m_InfoSourceSortedID;
			for (int i=0; i<oc_div_m_InfoSourceSortedID.Size(); i++)
			{
				if (allSrcSortedIDs.Find(oc_div_m_InfoSourceSortedID[i], true)==-1)
				{
					allSrcSortedIDs.InsertSorted (oc_div_m_InfoSourceSortedID[i]);
				}
			}
		}
	}

// ���������� �� ���� ������������ ���������� � ��������� �������� ���������
	bool	bCanReadData	= (USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "R")==ERR_OK);
	static int i;
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<allSrcSortedIDs.Size(); i++)
	{
		if (!OC_Exist (OBJ_CLASS_ID_InfoSource, allSrcSortedIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("������ �������� ��������������� ��������� [%d]", allSrcSortedIDs[i]);
			continue;
		}
		OC_InfoSource oc_src (allSrcSortedIDs[i]);

		arg.objIDs				+= allSrcSortedIDs[i];
		arg.objNames			+=	oc_src.m_Name;
		arg.objURLs				+=	string(oc_src.m_URL);
		arg.objRefreshTypes	+=	oc_src.m_RefreshType;
		arg.objDescriptions	+=	bCanReadData? string(oc_src.m_Description): string ("{{Access deny}}");
	}

// ������� ����� ���������� ����� ���� �������� ������������
	arg.TotalStoredNum = allSrcSortedIDs.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ��������������� ���������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_GetData (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_GetData);
/*............................................................................[]
		<objID					������������� �������������� �������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� {Concept.Feod.Aux.Sources}[R].
		<Password				������ ������������, �������������� ��������.

		>Name						�������� ���������.
		>Description			�������� ��������� ����������.
		>URL						Web-�����, �� �������� ��������� �������� ����������.
		>RefreshType			[int] ���������������� ����������� �������, ������������ ����� �������� ��������� ����������.
		>divIDs					� ����� �������������� �������� ��������� ��������. ������������ ������ �� �������, � ������� ������������ ����� ������ ����������, �.�. ����� ������ [R].
		>divNames				�������� ��������, � ������� ��������� ��������.
		>ShowCount				������� ��� ���� �������� ������� ����� ���������.
		>ClickCount				������� ��� ���� ����������� ������� ����� ���������.
		>CTR						ClickCount*100/ShowCount
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ InfoSource[%d] �� ����������", arg.objID);
	}
	OC_InfoSource oc_src (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� �������� ���������� ������ �������������� ����������");
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ��������� ������ �������
	arg.Name				=	oc_src.m_Name;
	arg.Description	=	oc_src.m_Description;
	arg.URL				=	oc_src.m_URL;
	arg.RefreshType	=	oc_src.m_RefreshType;
	arg.ShowCount		=	oc_src.m_ShowCount;
	arg.ClickCount		=	oc_src.m_ClickCount;
	arg.CTR				=	oc_src.m_CTR;
	arg.divIDs			=	oc_src.m_InfoDivID;

// ���������� �� �������, � ������� ������������ �� ����� ������ ����������
	for (int d=0; d<arg.divIDs.Size(); d++)
	{
		if (USER_CHECK_ACCESS_TO_INFODIV (loginID, arg.divIDs[d], "R")!=ERR_OK)
		{
		// ������������ �� ���� �����, ��� ���������� ����� ������
			arg.divIDs.Del (d);
			d--;
		}
		else
		{
			string divName; 
			GetInfoDivFullName (arg.divIDs[d], divName);
			arg.divNames += divName;
		}
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ��������������� ���������											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_PutData (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_PutData);
/*............................................................................[]
		<objID					������������� ����������� ��������� ����������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� {Concept.Feod.Aux.Sources}[R].
		<Password				������ ������������, �������������� ��������.

		<Name						�������� ���������.
		<Description			�������� ��������� ����������.
		<URL						Web-�����, �� �������� ��������� �������� ����������.
		<RefreshType			[int] ���������������� ����������� �������, ������������ ����� �������� ��������� ����������.
		<divIDs					� ����� �������������� �������� ��������� ��������. ����� ��������� ������ �� �������, � ������� ���� ����� [R] � ([C] ��� [W]).

		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ���������� ���� ����� ��� �����������, ��� ��� ����� ������ VC++6.0 
//	����� INTERNAL COMPILER ERROR
	static int d=0;
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ InfoSource[%d] �� ����������", arg.objID);
	}
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������� �� ����� ����� ������������� �������������� ���������");
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
		ERR_RETURN_COMMENT (ERR_BadName, "��� ����������������� ��������� �� ������ ���� ������");
	}
// ��� ������� ������ ���� ����������
	OC_InfoSource oc_src;
	oc_src.SetIndex_Name ();
	if (oc_src.Find (arg.Name) && oc_src.GetObjectID()!=arg.objID)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "��� ����������������� ��������� ������ ���� ����������. ��� ���� ������ �������� � ������ '%s'.", arg.Name.c_str());
	}
	oc_src.Open (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ���� �������
	oc_src.m_Name				=	arg.Name;
	oc_src.m_Description		=	arg.Description;
	oc_src.m_URL				=	arg.URL;
	oc_src.m_RefreshType		=	arg.RefreshType;


// ���������� �������� �� ��������:
// arg.divIDs -- � ����� ��������, �� ������ ������, ������ ������������ ������. 
// ����� �� ����� ��������/�������� �������� � ������ �� ���� � ���� ������ [R] � ([C] ��� [W]).
	identifier_arr new_div_arr = oc_src.m_InfoDivID;

// ���������� �� �������� ��������� � �������, ����� �� ��� �� ������� �������������, �.�. �� ����� �� ��������
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
		if (arg.divIDs.Find(divID)==-1)
		{
		// ������������ �����, ��� �������� �� ������ ���������� � ������� divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RC")==ERR_OK || USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RW")==ERR_OK)
			{
			// ������������ ����� ����� �������� �������� �� �������
				new_div_arr.Del (d);
				d--;
			// ���������� �������� �� �������
				OC_InfoDiv oc_div (divID);
				int nIndex = oc_div.m_InfoSourceSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_div.m_InfoSourceSortedID.Del (nIndex);
				}
			}
		}
	}

// ���������� �� ��������, ��������� �������������� � �������, ����� �� ��� ��� � ���������, �.�. �� ����� �� ��������
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		identifier divID = arg.divIDs[d];
		if (new_div_arr.Find(divID)==-1)
		{
		// ������������ �����, ��� �������� ������ ���������� � ������� divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RC")==ERR_OK || USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "RW")==ERR_OK)
			{
			// ������������ ����� ����� �������� �������� � ������
				new_div_arr.Add (divID);
				OC_InfoDiv (divID).m_InfoSourceSortedID.InsertSorted (arg.objID);
			}
		}
	}

// �������� �������������� ��������� ��������
	oc_src.m_InfoDivID = new_div_arr;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ��������������� ���������														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoSource_Delete (MOD_InfoSource_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoSource_Delete);
/*............................................................................[]
		<objID					������������� ���������� ���������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� {Concept.Feod.Aux.Sources}[D].
		<Password				������ ������������, �������������� ��������.

		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoSource, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ InfoSource[%d] �� ����������", arg.objID);
	}
	OC_InfoSource oc_src (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Aux.Sources"), "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ �� ����� ����� ������� �������������� ���������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
//	�������� �������� �� ��������.
	for (int d=0; d<oc_src.m_InfoDivID.Size(); d++)
	{
		if (CHECK_INFODIV_ID(oc_src.m_InfoDivID[d]))
		{
			OC_InfoDiv oc_div (oc_src.m_InfoDivID[d]);
			int nIndex = oc_div.m_InfoSourceSortedID.Find (arg.objID, true);
			if (nIndex!=-1)
			{
				oc_div.m_InfoSourceSortedID.Del (nIndex);
			}
			else
			{
				string divName; 
				GetInfoDivFullName (oc_src.m_InfoDivID[d], divName);
				SERVER_DEBUG_ERROR_3 ("��������� �������� %s �� ������ � ������� %s[%d]", string(oc_src.m_Name).c_str(), divName.c_str(), identifier(oc_src.m_InfoDivID[d]));
			}
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("� ���������� ��������� %s ������� ������������ ������ %d", string(oc_src.m_Name).c_str(), identifier (oc_src.m_InfoDivID[d]));
		}
	}

//	�������� �������� �� �������������� ��������.
	OC_InfoObject oc_info;
	identifier_arr	infoIDs;
	oc_info.SetIndex_InfoSourceID__InfoTime();
	key_arr ka(arg.objID);
	oc_info.GetClassIdList (infoIDs, &ka);

	for (int i=0; i<infoIDs.Size(); i++)
	{
		oc_info.Open (infoIDs[i]);
		if (oc_info.m_InfoSourceID==arg.objID)
		{
			oc_info.m_InfoSourceID = NA;
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("��������� �������� %s �� ������ � ��������������� ������� [%s]", string(oc_src.m_Name).c_str(), string(oc_info.m_Name).c_str());
		}
	}

//	������� �������������� ��������
	oc_src.Delete ();
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