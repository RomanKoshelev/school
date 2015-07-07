/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserGroup.cpp															[]
[] Date:          01.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������� ���� �������������                        []
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserGroup.inc.h"



//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ����� ������																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_New (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_New);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� �����. ������������ ��������� � ����������� ������.
		<Password					������ ������������, �������������� ��������.
		<Name							��� ����������� ������. ���� �������� ������ ��� ������������ ���, �� ������� ���� �����������/�������� �������� ������.
		<Type							��������������� ��� ������: root, admin, user, ������. �������� ������� ��������� � ���������������� ����.
		<Description				�������� ������. ���� �����, ������ �� FromID.
		<AccessLevelThreshold	��������� �������� ������ ������� �������������. ������ ������ ����� ����� ������ ����� (+1), ��� ������� � ���������, ����� ��� ��� � �������/�������.

		>objID						������������� ���������� ������.
		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "C", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ��������� ������� � ����� "root"
	if (!IGNORE_AUTHORIZATION && arg.Type=="root") 
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "����� �� ������! ������ ��������� ������� � ����� \"root\".");
	}
// ������ ��������� ������� � ����� "auditor"
	if (!IGNORE_AUTHORIZATION && arg.Type=="auditor") 
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "����� �� ������! ������ ��������� ������� � ����� \"auditor\".");
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
		arg.Name.Format ("New group created by %s", arg.Login.c_str());
	}

// ��� ������ ������ ���� ����������.
	if (GetGroupID(arg.Name, true)!=NA)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "������ � ������ '%s' ��� ����������.", arg.Name.c_str());
	}

	OC_UserGroup oc_group;
	identifier groupID = oc_group.New ();
	arg.objID = groupID;
	
// ����������� ������ ������ ����� ����� ������ ������� �������, ����� ��������� ��� � �������/�������
	oc_group.m_Name						= arg.Name;
	oc_group.m_Type						= arg.Type;
	oc_group.m_Description				= arg.Description;
	oc_group.m_AccessLevelThreshold	= max (arg.AccessLevelThreshold, oc_login.m_AccessLevel+1);
	oc_group.m_CreationTime				= time(0);

// ������� ��������� � ����� � ����� ������
	AddUserToGroup		(loginID, groupID);
	AddRootsToGroup	(groupID, loginID);

//	�������� ����� ���� ������
	UserGroupSimplifyRightsSet	(groupID);
//----------------------------------------------------------------------------[] 


	
	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ �����																			[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_Enumerate (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_Enumerate);
/*............................................................................[]
		<Login							����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ��������� ������.
		<Password						������ ������������, �������������� ��������.
		<objFirstNo						����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
		<objLastNo						����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

		>objIDs							������ ��������������� ��������. �������� ������ �� ������, � ������� ������� ������������.
		>objNames						������ �������� ��������.
		>objTypes						������ ����� �����: root, admin, user, ������. �������� ������� ��������� � ���������������� ����.
		>objAccessLevelThresholds	��������� �������� ��� ������ ������� �������������. 
		>TotalStoredNum				������� ����� �������� �������� � ����.
		>MaxNumInQuery					����������� ���������� ����� ������������� �� ���� ��� ��������.
		>ExitCode						��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment				��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "L", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.objFirstNo = max(arg.objFirstNo, 0);
	if ((arg.objLastNo - arg.objFirstNo) > MAX_GROUP_ENUMERATE_NUM)
	{
		arg.MaxNumInQuery	= MAX_GROUP_ENUMERATE_NUM;
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� ���� �������� ������ �� ������, � ������� ������ �����
	int				oc_login_m_GroupID_Size = oc_login.m_GroupID.Size();
	identifier_arr oc_login_m_GroupID		= oc_login.m_GroupID;

// ���� ����� ������� ��� ���, �� �������� ��� ������
	if (IS_ROOT(loginID) || IS_AUDITOR(loginID))
	{
		OC_UserGroup oc_group;
		oc_group.GetClassIdList (oc_login_m_GroupID);
		oc_login_m_GroupID_Size = oc_login_m_GroupID.Size();
	}
	static int g;
	for (g=arg.objFirstNo; (g<=arg.objLastNo) && (g<oc_login_m_GroupID_Size); g++)
	{
		identifier groupID = oc_login_m_GroupID[g];

	// ������ ����������
		if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("������������ ������ ���� %d � ������������ %s [%d]. ����������.", int (oc_login_m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login_m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

		arg.objIDs							+= groupID;
		arg.objNames						+= oc_group.m_Name;
		arg.objTypes						+= oc_group.m_Type;
		arg.objAccessLevelThresholds	+= oc_group.m_AccessLevelThreshold;
	}
	
	arg.TotalStoredNum	=	oc_login_m_GroupID.Size();
	arg.MaxNumInQuery		=	MAX_GROUP_ENUMERATE_NUM;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_GetData (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_GetData);
/*............................................................................[]
		<objID						������������� ������, ��� ���������� �������������.
		<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� ������������� ������ � ������������ � ������������� ������.
		<Password					������ ������������, �������������� ��������.
		<UserFirstNo				����� ������������ ������ �����, ������� � �������� ����������� �������������.
		<UserLastNo					����� ���������� �������������� ������������ �����.

		>Name							��� ������
		>Type							��������������� ��� ������: root, admin, user, ������. �������� ������� ��������� � ���������������� ����.
		>Description				�������� ������
		>AccessLevelThreshold	��������� �������� ������ ������� �������������. ������ ������ ����� ����� ������ �����, ��� ������� � ���������, ����� ��� ��� � �������/�������.
		>CreationTime				����� �������� �������
		>FeodIDs						����� ��������������� ��� �������.
		>FeodNames					����� ��� ��� �������.
		>FeodAttributes			�������������� ����� ������� �������� �������. ������ ���� "CLRWD"

		>UserIDs						�������������� �������������-������ ������.
		>UserLogins					������ �������������-������ ������.
		>UserFullNames				����� �������������-������ ������.
		>UserAccessLevels			������ ������� �������������-������ ������.
		>UserCreationTimes		������� �������� �������������-������ ������.
		>UserTotalStoredNum		������� ����� ������������� � ������.
		>UserMaxNumInQuery		����������� ���������� ����� ������������� �� ���� ��� ������������� ������.

		>ReadOnly					������ ����� ���� ������ ��������� � �� ����� ���� ��������.

		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel TooManyEnumerate).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[]
//
// �������� �������
//
//----------------------------------------------------------------------------[]
// ������ ������ ������������
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "R", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// ���� ������������ �� � ������ -- ���� ���.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "������������ �� ����������� � ������");
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.UserFirstNo = max(arg.UserFirstNo, 0);
	if ((arg.UserLastNo - arg.UserFirstNo) > MAX_USER_ENUMERATE_NUM)
	{
		arg.UserMaxNumInQuery = MAX_USER_ENUMERATE_NUM;
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	arg.Name							= oc_group.m_Name;
	arg.Type							= oc_group.m_Type;
	arg.Description				= oc_group.m_Description;
	arg.AccessLevelThreshold	= oc_group.m_AccessLevelThreshold;
	arg.CreationTime				= oc_group.m_CreationTime;

// ��������������, ����� � �������� ��� �������
	for (int f=0; f<oc_group.m_Rights_Feod.Size(); f++)
	{
		identifier feodID = oc_group.m_Rights_Feod[f];
		if (!CHECK_FEOD_ID (feodID))
		{
			SERVER_DEBUG_ERROR_2 ("���������� ID ���� ������� (%d) � ������ %s. ����������.", feodID, ((string)oc_group.m_Name).c_str());
			oc_group.m_Rights_Feod.Del (f);
			oc_group.m_Rights_Attr.Del (f);			
			f--;
		}
		else
		{
		// ���������� ��� �����, � ��� ����� � ����� ������ �������
			identifier_arr allFeods;
			//GetAllFeodChilds (feodID, allFeods);
			allFeods.Insert  (0, feodID);
			for (int i=0; i<allFeods.Size(); i++)
			{
				string FeodName;
				if (GetFeodFullName (allFeods[i], FeodName, 1, "::"))
				{
					arg.FeodIDs				+= allFeods[i];
					arg.FeodNames			+= FeodName;
					arg.FeodAttributes	+= oc_group.m_Rights_Attr[f];
				}
			}
		}
	}

// ��� ����� ������.
	for (int m=arg.UserFirstNo; m<=arg.UserLastNo && m<oc_group.m_UserID.Size(); m++)
	{
		identifier userID = oc_group.m_UserID[m];
		if (!OC_Exist (OBJ_CLASS_ID_User, userID))
		{
			SERVER_DEBUG_ERROR_2 ("���������� ������������ � ��������������� [%d], ���� ������ %s. ����������.", userID, ((string)oc_group.m_Name).c_str());
			oc_group.m_UserID.Del (m);
			m--;
			continue;
		}
		OC_User oc_user (userID);

		arg.UserIDs					+= userID;
		arg.UserLogins				+= oc_user.m_Login;
		arg.UserFullNames			+= oc_user.m_FullName;
		arg.UserCreationTimes	+=	oc_user.m_CreationTime;
		arg.UserAccessLevels		+= oc_user.m_AccessLevel;
	}

	bool bCanChange = (USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "W")==ERR_OK) && 
							(oc_login.m_AccessLevel < oc_group.m_AccessLevelThreshold);

	arg.UserTotalStoredNum	= oc_group.m_UserID.Size();
	arg.UserMaxNumInQuery	= MAX_USER_ENUMERATE_NUM;
	arg.ReadOnly				= !bCanChange;	
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//----------------------------------------------------------------------------[] 
// ��� ����� ������
struct GR_RIGHTS
{
	identifier	feodID;
	char			Attribute;
	bool			bFound;
	GR_RIGHTS () {feodID=NA; Attribute=0; bFound=false;}
	bool operator ==	(const GR_RIGHTS& to) const {return feodID==to.feodID && Attribute==to.Attribute;}
	bool operator <	(const GR_RIGHTS& to) const {return feodID<to.feodID || (feodID==to.feodID && Attribute<to.Attribute);}
	bool operator <=	(const GR_RIGHTS& to) const {return ((*this)<to) || ((*this)==to);}
};
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������																	[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_PutData (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_PutData);
/*............................................................................[]
	<objID						������������� ������, ��� ���������� ����������.
	<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� ������, ������������ � ���������� ������ � ����� ����� ������� ������� �������, ��� ��������� �������� ������.
	<Password					������ ������������, �������������� ��������.
	<Name							��� ������
	<Type							��������������� ��� ������: root, admin, user, ������. �������� ������� ��������� � ���������������� ����.
	<Description				�������� ������
	<AccessLevelThreshold	��������� �������� ������ ������� �������������. �� ����� ���� ������� ��� ������� ������.
	<FeodIDs						����� ��������������� ���� ��� ������� ������. ����� ������ ����� ������ � ���� ����� � ���������������� ����������.	����� ����, ����� �� ����� ������ ������ ��������� ����, ���� ��� ���� ��� �������� ���� ����. ��� ��� ������� ��������, ��� ������������ �� ����� �� ���������, �� ��������� ����� ����������� ����.
	<FeodAttributes			�������������� ����� ������� �������� �������. ������ ���� "CLRWD"

	>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
	>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "W", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// ���� ������������ �� � ������ -- ���� ���.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "������������ �� ����������� � ������");
	}
//----------------------------------------------------------------------------[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� �������� ������ ��� -- ������.
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������ �� ����� ���� ������.");
	}

// ��� ������ ������ ���� ����������.
	identifier grID = GetGroupID (arg.Name, true);
	if (grID!=NA && grID!=groupID)
	{
		ERR_RETURN_COMMENT_1 (ERR_NameAlreadyExists, "��� ������ ������ ���� ����������. ��� ���������� ������ ������ � ������ %s", arg.Name.c_str());
	}

// ��������� ���������� ������ �������
	int f;
	if (arg.AccessLevelThreshold < oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "��������� �������� ������ ������� ������������� � ������ AccessLevelThreshold �� ����� ���� ������� ��� ������� ������� ������������, ����������� ���.");
	}

// �������� ������������ ����������� ����
// (�������� ������������ ����������� ���� �� ������������, ��� ��� 
// ��������� ���� �������� ����������� ������������.)
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, arg.FeodIDs[f], arg.FeodAttributes[f])!=ERR_OK)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������ �� ����� ��������� ������ �����, �������� ��� �� ��������.");
		}
	}

// ���� ������� ������� ������, ����� �� ����� ����� ������ ������ ������
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		if (	oc_group.m_Name						!= arg.Name						||
				oc_group.m_Description				!= arg.Description			||
				oc_group.m_Type						!= arg.Type						||
				oc_group.m_AccessLevelThreshold	!= arg.AccessLevelThreshold)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ���� ��������� �������� ����� ������.");
		}
	}


// ��������� ������������ ���������
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (!CHECK_ATTRIBUTES (arg.FeodAttributes[f]))
		{
			ERR_RETURN_COMMENT_2 (ERR_BadArgument, "���� �� ��������� � ������� arg.FeodAttributes[%d]='%s' �����������.", f, arg.FeodAttributes[f].c_str());
		}
	}

//	�������� ���������� ������
	for (f=0; f<arg.FeodIDs.Size(); f++)
	{
		if (!CHECK_FEOD_ID (arg.FeodIDs[f]))
		{
			ERR_RETURN_COMMENT (ERR_BadID, "������� �������������� ���� ������� (����)");
		}
	}

// ������ �������� ��� ������ �� "root"
	if (!IGNORE_AUTHORIZATION && arg.Type=="root" && oc_group.m_Type!="root")
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "����� �� ������! ������ �������� ��� ������� �� \"root\".");
	}
// ������ �������� ��� ������ �� "auditor"
	if (!IGNORE_AUTHORIZATION && arg.Type=="auditor" && oc_group.m_Type!="auditor")
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "����� �� ������! ������ �������� ��� ������� �� \"auditor\".");
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������������� �������� ����������	                                       []
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� ������� ������� ������, ����� �� ����� �������� ����� � ������
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		CPtr <GR_RIGHTS> allRigths;
		int i,j;

	// ��������� ��� ����� ������
		for (i=0; i<oc_group.m_Rights_Feod.Size(); i++) for (j=0; j<(int)string(oc_group.m_Rights_Attr[i]).Len(); j++)
		{
			GR_RIGHTS gr_right;
			gr_right.feodID		= oc_group.m_Rights_Feod[i];
			gr_right.Attribute	= string(oc_group.m_Rights_Attr[i])[j];
			gr_right.bFound		= false;

			if (allRigths.Find(gr_right, true)==-1)
			{
				allRigths.InsertSorted (gr_right);
			}
		}

	//	��������� ������� ��������������� ���� � ����������
		for (i=0; i<arg.FeodIDs.Size(); i++) for (j=0; j<(int)arg.FeodAttributes[i].Len(); j++)
		{
			GR_RIGHTS gr_right;
			gr_right.feodID		= arg.FeodIDs[i];
			gr_right.Attribute	= arg.FeodAttributes[i][j];
			gr_right.bFound		= false;

			int index = allRigths.Find(gr_right, true);
			if (index != -1)
			{
				allRigths[index].bFound = true;
			}
		}

	// ���������, ��� ��� �����, �������������� � ������, ������������ � ����������
		for (i=0; i<allRigths.Size(); i++) if (allRigths[i].bFound==false)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ��� ���������� ���� ������.");
		}
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
//	�������� ����
	oc_group.m_Name						= arg.Name;
	oc_group.m_Description				= arg.Description;
	oc_group.m_Type						= arg.Type;

//	��������� ������ ����� (�������������, ���� ������� ������� �������������) ����� ����.
	oc_group.m_AccessLevelThreshold	= arg.AccessLevelThreshold;
	oc_group.m_Rights_Feod				= arg.FeodIDs;
	oc_group.m_Rights_Attr				= arg.FeodAttributes;

//	�������� ����� ���� ������
	UserGroupSimplifyRightsSet	(groupID);
//----------------------------------------------------------------------------[] 



	CACHE_NUM_USER_CHECK_ACCESS++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������																				[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserGroup_Delete (MOD_UserGroup_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserGroup_Delete);
/*............................................................................[]
		<objID						������������� ��������� ������.
		<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� ������, ������������ � ��������� ������ � ����� ����� ������� ������� �������, ��� ��������� �������� ������.
		<Password					������ ������������, �������������� ��������.
		>ExitCode					��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	identifier groupID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_UserGroup oc_group (groupID);

// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.Group", "D", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
	OC_User oc_login (loginID);

// ���� ������������ �� � ������ -- ���� ���.
	if (oc_login.m_GroupID.Find (groupID)==-1)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "������������ �� ����������� � ������");
	}

// �������� ���������� ������ �������
	if (oc_login.m_AccessLevel >= oc_group.m_AccessLevelThreshold)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������� ������� ������� ���� �������� ������.");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// � ���� ������ ������ ���������� � �� ������
	for (int u=0; u<oc_group.m_UserID.Size(); u++)
	{
		if (OC_Exist (OBJ_CLASS_ID_User, oc_group.m_UserID[u]))
		{
			OC_User oc_user (oc_group.m_UserID[u]);
			int g=oc_user.m_GroupID.Find (groupID);
			if (g!=-1)
			{
				oc_user.m_GroupID.Del (g);
			}
			else
			{
				SERVER_DEBUG_ERROR_4 ("� ������������ %s[%d] ������ %s[%d] �� ����������.", string (oc_user.m_Login).c_str(), int (oc_group.m_UserID[u]), string (oc_group.m_Name).c_str(), groupID);
			}
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("���������� ID=%d ����� ������ %s.", int (oc_group.m_UserID[u]), string (oc_group.m_Name).c_str());
		}
	}

// ������� ������
	oc_group.Delete ();
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