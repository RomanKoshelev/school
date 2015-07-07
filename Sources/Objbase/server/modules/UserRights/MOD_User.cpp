/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_User.cpp																[]
[] Date:          28.06.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������������													[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_User.inc.h"
                                                               


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ ������������                                              []                            
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_New	(MOD_User_Args& arg, int AccessLevel)
{
	DEBUG_STACK_NAME (MOD_User_New);
/*............................................................................[]
		<Login					����� ������������ ������������.
		<Password				������ ������������ ������������.
		<PasswordConfirm		������������� ������.
		<PasswordInBrowser	������������ ����������� ��������������� ����� ������
		<FullName				������ ��� ������������.
		<Email					E-mail.

		>objID					������������� ������������.
		>ExitCode				��� �������� (OK BadLogin BadPassword BadPasswordConfirm LoginAlreadyExists).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� ������������ ��� ����	
	if (FindUserByLogin (arg.Login)!=NA)
	{
		ERR_RETURN (ERR_LoginAlreadyExists);
	}
//	������ ����� 
	if (arg.Login.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadLogin, "������ �����");
	}
//	������ ������
	if (arg.Password.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadPassword, "������ ������");
	}
// ������������ ������ � ��� �������������
	if (arg.Password != arg.PasswordConfirm)
	{
		ERR_RETURN (ERR_BadPasswordConfirm);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������������
	OC_User		oc_user;
	identifier	userID = oc_user.New ();
	arg.objID = userID;

	oc_user.m_Login					= arg.Login;
	oc_user.m_CreationTime			= time(0);
	oc_user.m_Password				= arg.Password;
	oc_user.m_PasswordInBrowser	= arg.PasswordInBrowser;
	oc_user.m_FullName				= arg.FullName;
	oc_user.m_Email					= arg.Email;

// ������������ ������������
	ERR_RESULT res;

	if (arg.Login == "anonymous")
	{
		if (arg.Password!="anonymous")
		{
			ERR_RETURN_COMMENT (ERR_BadPassword, "������ ���������� ������������ 'anonymous' ������ ���� 'anonymous'.");
		}
		res = AddUserToGroup (userID, GetGroupIDByType ("anonymous"));
	}
	else if (arg.Login=="{{IMPORT}}")
	{
		AccessLevel = -10;
		res = ERR_OK;
	}
	else
	{
		res = AddUserToGroup (userID, GetGroupIDByType ("user"));
	}
	oc_user.m_AccessLevel = AccessLevel;
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 



	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ ������������                                              []                            
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Authorize	(MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Authorize);
/*............................................................................[]
		<Login					�����.
		<Password				������.
		<PasswordInBrowser	������ ��� ����� ������������� (����� ����). ���������, ���� � ������������ ����� ���� "PasswordInBrowser".

		>PasswordInBrowser	������������ ����������� ��������������� ����� ������. ���� ��, ��������������� ����.
		>objID					������������� ������������ ��� NA ���� ����������� �����������.
		>ExitCode				��� �������� (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	bool bPasswordInBrowser = arg.PasswordInBrowser;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, arg.objID, &arg.PasswordInBrowser);

// ������ �� �������� ������
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// ����� �� ������������� ����������� ������ � �����
	if (bPasswordInBrowser && !arg.PasswordInBrowser)
	{
		ERR_RETURN_COMMENT (ERR_AccessDeny, "������������ ������ ������ ����� � ������, �� ������ ������������� ���������� �� ����.");
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]

















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ �������������                                                []                          
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Enumerate	(MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Enumerate);
/*............................................................................[]
		<Login					����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ��������� ������.
		<Password				������ ������������, �������������� ��������.
		<objFirstNo				����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
		<objLastNo				����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

		>objIDs					������ ��������������� ��������.
		>objNames				������ �������� ��������.
		>objFullNames			������ ��� �������������.
		>TotalStoredNum		������� ����� �������� �������� � ����.
		>MaxNumInQuery			����������� ���������� ����� ������������� �� ���� ��� ��������.
		>ExitCode				��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User", "L", &arg.objID);
	if (res != ERR_OK)	
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 

	
	
//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� �� ��������� ������� ����� ������������� 
	arg.objFirstNo = max (arg.objFirstNo, 0);
	arg.objLastNo	= max (arg.objFirstNo, arg.objLastNo);
	if ((arg.objLastNo - arg.objFirstNo) > MAX_USER_ENUMERATE_NUM)	
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ������ �������������
	OC_User oc_user;
	oc_user.SetIndex_Login ();
	identifier_arr arrID;
	int i;
	oc_user.GetClassIdList (arrID);
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<arrID.Size(); i++)
	{
		oc_user.Open (arrID[i]);

		arg.objIDs.Add			(arrID[i]);
		arg.objNames.Add		(oc_user.m_Login);
		arg.objFullNames.Add	(oc_user.m_FullName);
	}
	arg.TotalStoredNum	= arrID.Size();
	arg.MaxNumInQuery		= MAX_USER_ENUMERATE_NUM;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������������                                             []                             
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_GetData (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_GetData);
/*............................................................................[]
		<objID					������������� ������������, ��� ���������� �������������.
		<Login					����� ������������, �������������� ��������. ������������ ������ �������� ������� ������������� ������ ������������� � �������� ����� ������� ������� �������, ��� ���� ����� �������������.
		<Password				������ ������������, �������������� ��������.

		>Login					����� �������������� ������������
		>FullName				������ ��� ������������.
		>Email					����������� ����� ������������.
		>URL						URL ������������.
		>Data						������ �����������, ����������� ��������� �� ���������� �� ������� � ��������� ������.
		>PasswordInBrowser	������������ ����������� ��������������� ����� ������.
		>CreationTime			����� �������� �������
		>ReadOnly				������ ����� ���� ������ ��������� � �� ����� ���� ��������.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// ��������� ����� �������
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "R");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}

	// ����� �� ����� ���������� ���� ��� ���������� �������� ��� ��������
		if (OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������������ �� ����� ������������ ������ ������� ����� �������� ����� ������");
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	bool bCanChange = IS_ROOT (loginID) || arg.objID==loginID || 
		(USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "W")==ERR_OK) && 
		(OC_User(loginID).m_AccessLevel < oc_user.m_AccessLevel);

	arg.FullName				= oc_user.m_FullName;
	arg.Email					= oc_user.m_Email;
	arg.PasswordInBrowser	= (bool) oc_user.m_PasswordInBrowser;
	arg.ReadOnly				= !bCanChange;
	arg.URL						= oc_user.m_URL;
	arg.Data						= oc_user.m_Data;

	arg.Login					= oc_user.m_Login;
	arg.CreationTime			= oc_user.m_CreationTime;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]
















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������������                                             []                             
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_PutData (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_PutData);
/*............................................................................[]
		<objID					������������� ������������, ��� ���������� �������������.
		<Login					����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� ������ ������������� � ����� ������� ������� �������, ��� objID, ��� ���� ����� �������������.
		<Password				������ ������������, �������������� ��������.
		<NewPassword			���� ���� �� �����, ������� ������.
		<NewPasswordConfirm	������������� ������ ������.
		<PasswordInBrowser	������������ ����������� ��������������� ����� ������
		<FullName				������ ���
		<Email					����������� �����
		<Data						������ �����������, ����������� ��������� �� ���������� �� ������� � ��������� ������.

		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// ��������� ����� �������
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Data", "W");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}

	// ����� �� ����� ���������� ���� ��� ���������� �������� ��� ��������
		if (OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
		{
			ERR_RETURN (ERR_InsufficientAccessLevel);
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	if (!arg.NewPassword.IsEmpty() && arg.NewPassword != arg.NewPasswordConfirm)
	{
		ERR_RETURN (ERR_BadPasswordConfirm);
	}
	if (!arg.NewPassword.IsEmpty())
	{
		oc_user.m_Password		= arg.NewPassword;
	}
	oc_user.m_FullName			= arg.FullName;
	oc_user.m_Email				= arg.Email;
	oc_user.m_URL					= arg.URL;
	oc_user.m_PasswordInBrowser= arg.PasswordInBrowser;
	oc_user.m_Data					= arg.Data;
//----------------------------------------------------------------------------[] 


	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]


















//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ���� ������������																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_GetRights (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_GetRights);
/*............................................................................[]
		<objID					������������� ������������, ��� ���������� �������������.
		<Login					����� ������������, �������������� ��������. ������������ ������ �������� ������� ������ ���� ������ ������������� � ����� ������� ������� �������, ��� ���� ����� �������������.
		<Password				������ ������������, �������������� ��������.
		<ExpandGroups			��������� �� �������� ����� ���� ��� ������ ������ -- LoginGroupRights.
		<ExpandRights			��������� �� ��������� ����� ���� �� ���� ���� �������� (���������) ����.

		>Login					����� �������������� ������������
		>LoginAccessLevel		������� ������� ������
		>LoginGroupIDs			��� ������ ���� ������.
		>LoginGroupNames		����� ����� ����� ������.
		>LoginGroupTypes		���� �����: root, admin, user, ������. �������� ������� ��������� � ���������������� ����.
		>LoginGroupRights		����������� � ������ ������ �� ������ ������ ������. ������: "feodID|��������|feodName|feodType\nfeodID|��������|feodName\n...feodID|��������|feodName|feodType"
		>LoginOwnRights		����������� � ������ ������ �� ������ ������ ������. ��� �� ���� �������, ������� ������ ��� �����. ������ ����, ��� � � LoginGroupRights.

		>ObjAccessLevel		������� ������� ������������.
		>ObjGroupIDs			���� ����� ����������� � ������ ������������ � ��� ������� �������, �� �� ����� ����� � ���, ��� ������������ �������� ���� �������. ������ ����� �����.
		>CreationTime			����� �������� �������
		>ReadOnly				����� ����� ���� ������ ��������� � �� ����� ���� ��������.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]


	
//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
// ��������� ����� �������
	if (loginID!=arg.objID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "R");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� ��������� ���������� �����, �� ���������� ���������� ������
	if (arg.ExpandRights && !arg.ExpandGroups)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument,"���� ��������� ���������� �����, �� ���������� ���������� � ���� ������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	OC_User oc_login (loginID);

// ����� �������	
	arg.LoginAccessLevel	= oc_login.m_AccessLevel;
	arg.ObjAccessLevel	= oc_user.m_AccessLevel;

// �������� ������ �����
	for (int g=0; g<oc_login.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_login.m_GroupID[g];

	// ������ ������ ������������
		if (!OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("������������ ������ ���� %d � ������������ %s [%d]. ����������.", int (oc_login.m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login.m_GroupID.Del (g);
			g--;
			continue;
		}
		OC_UserGroup oc_group (groupID);

	// ��������� ������ ���� ����� ���� ������
		arg.LoginGroupIDs		+=	groupID;
		arg.LoginGroupNames	+= oc_group.m_Name;
		arg.LoginGroupTypes	+= oc_group.m_Type;
		arg.LoginGroupRights	+= arg.ExpandGroups? string (GetGroupRights (groupID, arg.ExpandRights)) : string("");

	// ���� ����� ����������� � ������ ������������ � ��� ������� �������, �� �� ����� ����� � ���, ��� ������������ �������� ���� �������.
		if ((IS_ROOT (loginID) || IS_AUDITOR (loginID) || oc_login.m_AccessLevel<oc_user.m_AccessLevel) && oc_user.m_GroupID.Find (oc_login.m_GroupID[g])!=-1)
		{
			arg.ObjGroupIDs	+= groupID;
		}
	}

//	����� �� ������������� �����
	bool bCanChange = arg.objID!=loginID && (USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "W")==ERR_OK);

	arg.ReadOnly		= !bCanChange;
	arg.Login			= oc_user.m_Login;
	arg.CreationTime	= oc_user.m_CreationTime;

// ������ ����� ������
	arg.LoginOwnRights = "";
	for (int f=0; f<oc_login.m_OwnFeodID.Size(); f++)
	{
		string strFeodID;
		string strFeodName;

		identifier feodID = oc_login.m_OwnFeodID[f];
		if (!CHECK_FEOD_ID(feodID))
		{
			SERVER_DEBUG_ERROR_2 ("���������� ID ������ ���� ������� (%d) ������������ %s. ����������.", feodID, ((string)oc_login.m_Login).c_str());
			oc_login.m_OwnFeodID.Del (f);
			f--;
			continue;
		}

	// ���������� ��� �����, � ��� ����� � ����� ������ �������
		identifier_arr allFeods;
		if (arg.ExpandRights)
		{
			GetAllFeodChilds (feodID, allFeods);
			allFeods.Insert  (0, feodID);
		}
		else
		{
			allFeods	+=	feodID;
		}
			
		for (int i=0; i<allFeods.Size(); i++)
		{
			if (GetFeodFullName (allFeods[i], strFeodName, 1, "::"))
			{
				string strFeodType;
				GetFeodType (allFeods[i], strFeodType);

				strFeodID.Format ("%d", allFeods[i]);
				arg.LoginOwnRights += "\n";
				arg.LoginOwnRights += strFeodID;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += ALL_ATTRIBUTES;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += strFeodName;
				arg.LoginOwnRights += "|";
				arg.LoginOwnRights += strFeodType;
			}
		}
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ���� ������������																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_PutRights (MOD_User_Args& arg)
{
	DEBUG_STACK_NAME (MOD_User_PutRights);
/*............................................................................[]
		<objID					������������� ������������, ��� ���������� �������������.
		<Login					����� ������������, �������������� ��������. ������������ ������ �������� ������� ��������� ���� ������ �������������. ����� �������� ����� ���� ����� ����� ������� ������� �������.
		<Password				������ ������������, �������������� ��������.
		<AccessLevel			����� ������� ������� �������������. ������� ������� �� ����� ���� ������ ��� ������� ��� ������� ������� ������ ������.
		<objIDs					�����, �������, �� ������ ������, ������ ���� � ������������. ���� ����� �������, �� �� ����� �������� � ������������ ����� ������, �������� �������� ���. ���������� �� ������ ������� �� ����� ������������ �� ������ ����, �������� �������� ���.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	identifier userID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (userID);

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}

// ��������� ����� �������
	if (loginID!=userID)
	{
		ERR_RESULT res = USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User.Group", "W");
		if (res!=ERR_OK)
		{
			ERR_RETURN (res);
		}
	}
	else
	{
	// ������������ �� ����� ��� ���� �������� �����
		ERR_RETURN (ERR_OK);
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	OC_User oc_login  (loginID);
// ���� ����� ������ �������, �� ����������� ��������� ���� ����������
	if (oc_login.m_AccessLevel >= oc_user.m_AccessLevel)
	{
	// ����� �������� ������� ������� ������ ���, ��� ������
		if (arg.AccessLevel != oc_user.m_AccessLevel)
		{
			ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "����� �������� ������� ������� ������ ���, ��� ������.");
		}
	}
// ������ ��������� ������� ������� ����� �� ��� �������, ��� ������ ���
	if (arg.AccessLevel <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������ ��������� ������� ������� ����� �� ��� �������, ��� ������ ���.");
	}
// ������ ������ ���� ������ �����
	if (loginID == userID)
	{
		ERR_RETURN_COMMENT (ERR_InsufficientAccessLevel, "������ ������ ���� ������ �����.");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������� �������
	oc_user.m_AccessLevel = arg.AccessLevel;

// ������ ����
	for (int g=0; g<oc_login.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_login.m_GroupID[g];

	// ������ ������ ������������
		if (!OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			SERVER_DEBUG_ERROR_3 ("������������ ������ ���� %d � ������������ %s [%d]. ����������.", int (oc_login.m_GroupID[g]), ((string)oc_login.m_Login).c_str(), loginID);
			oc_login.m_GroupID.Del (g);
			g--;
			continue;
		}


		if (oc_user.m_GroupID.Find (oc_login.m_GroupID[g])==-1)
		{
		// � ������������ objID ����� ������ ���� ��� -- � ����� ��������
			if (arg.objIDs.Find (groupID)!=-1)
			{
			// ����� �����, ��� ������ ���� ������������.
			// ������ ������������ � ����� ������ ������� �������, ��� ���� � ������
				AddUserToGroup (userID, groupID);
			}
		}
		else if (oc_login.m_AccessLevel < oc_user.m_AccessLevel)
		{
		// � ������������ objID ����� ����� ����, ��� ������� ������� ������ -- ����� ����� ��������
			if (arg.objIDs.Find (groupID)==-1)
			{
			// ����� �����, ��� ������������ �� ������ ���� � ���� ������, ��������� ���.
				RemoveUserFromGroup (userID, groupID);
			}			
		}
	}
//----------------------------------------------------------------------------[] 




	CACHE_NUM_USER_CHECK_ACCESS ++;
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������������� ������� � ���� ��������� ����.                     []                                                     
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_CheckOwnRights (MOD_User_Args& arg)
{
	DEBUG_STACK_NAME (MOD_User_CheckOwnRights);
/*............................................................................[]
		<Login					����� ������������, �������������� ��������. ��� ���� � ����������� �����.
		<Password				������ ������������, �������������� ��������.
		<FeodNames				����� ��� ��� �������
		<FeodAttributes		�������������� ����� ������� �������� �������. ������ ���� "CLRWD"

		>Accesses				��������� ������, ���������� ������ �� ������� � ����������� ������� � ��������������� ���� � ���������� ����������.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
	identifier userID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, userID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	for (int i=0; i<arg.FeodNames.Size(); i++)
	{
		arg.Accesses += (USER_CHECK_ACCESS (arg.Login, arg.Password, arg.FeodNames[i], arg.FeodAttributes[i])==ERR_OK);
	}
//----------------------------------------------------------------------------[] 

	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������������                                                     []                     
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_User_Delete (MOD_User_Args& arg) 
{
	DEBUG_STACK_NAME (MOD_User_Delete);
/*............................................................................[]
		<objID					������������� ���������� ������������.
		<Login					����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� �������������, � ����� ������� ��������, ��� ��������� ������������.
		<Password				������ ������������, �������������� ��������.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]


//----------------------------------------------------------------------------[] 
//
// �������� �������
//
//----------------------------------------------------------------------------[] 
// ������ ������ ������������
	identifier userID = arg.objID;
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		ERR_RETURN (ERR_BadID);
	}
	OC_User oc_user (userID);
// ��������� �����/������ � ����� �������
	identifier	loginID	=	NA;
	ERR_RESULT  res		=	USER_CHECK_ACCESS (arg.Login, arg.Password, "Concept.Feod.Admin.User", "D", &loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN (res);
	}
// ����� �� ����� ���������� ���� ��� ���������� �������� ��� ��������
	if (!IGNORE_AUTHORIZATION && OC_User(loginID).m_AccessLevel >= oc_user.m_AccessLevel)
	{
		ERR_RETURN (ERR_InsufficientAccessLevel);
	}
//----------------------------------------------------------------------------[] 


	
//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������ ��������� �� �����.
	for (int g=0; g<oc_user.m_GroupID.Size(); g++)
	{
		identifier groupID = oc_user.m_GroupID[g];
		if (OC_Exist(OBJ_CLASS_ID_UserGroup, groupID))
		{
			OC_UserGroup oc_group (groupID);
			for (int i=0; i<100; i++)
			{
				int m = oc_group.m_UserID.Find (userID);
				if (m==-1) break;
				oc_group.m_UserID.Del (m);
				m--;
			}
		}
	}

// ������� ������������. ������, ������� �������.
	oc_user.Delete ();
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
