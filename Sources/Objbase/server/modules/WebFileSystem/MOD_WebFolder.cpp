/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFolder.cpp															[]
[] Date:          31.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � web-��������� ������������									[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFolder.inc.h"				 






//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ ������� ������ WebFolder												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_New (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_New);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� �������� [C] � [m].
		<Password					������ ������������, �������������� ��������.
		<Name							��� �����.
		<Description            �������� ����������� �����
		<ParentID					������������ �����.
		<ParentName					��� ������������ �����, ������������, ���� ParentID == NA;
		<AccessLevelThreshold	��������� �������� ������ ������� �������������. ���������� ������ ����� ����� ������ �����, ��� ������� � ���������, ����� ��� ��� � �������/�������.

		>objID						������������� ���������� �������.
		>ExitCode					��� �������� (OK BadLogin BadPassword BadName AccessDeny).
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
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("�� ������� ������������ ����� '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "�� ������� ������������ ����� '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetWebFolderIDByFeodID (feod_parent_ID);
	}
// ������������ ����� ������ ������������
	if (!CHECK_WEBFOLDER_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ ������������ ������ ID=%d", arg.ParentID);
	}
	OC_WebFolder oc_parent_folder (arg.ParentID);
// ��� ������� �� ������ ���� ������
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������������ ������� �� ������ ���� ������");
	}
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
// ����� ������ ����� ����� ������ �����, ��� ������� � ���������, 
// ����� ��� ��� � �������/�������.
	if (arg.AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		arg.AccessLevelThreshold = oc_login.m_AccessLevel+1;
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
	feod_arg.ParentID						= guid(oc_parent_folder.m_MOD_Base_GUID).id;
	feod_arg.AccessLevelThreshold		= arg.AccessLevelThreshold;

	MOD_Feod_New (feod_arg);
	if (feod_arg.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (feod_arg.ExitCode, feod_arg.ExitCodeComment);
	}

// ������ �����, ��������� � � �������� ���������� ���������� �����
	SET_MOD_EXTENSION (Concept, feod_arg.objID, WebFolder, arg.objID);
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ ��������� �������� ������ WebFolder									[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_Enumerate (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ ����� ����� ��������� ������ [L].
		<Password					������ ������������, �������������� ��������.
		<objFirstNo					����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
		<objLastNo					����� �������, �� �������� ������������ ��������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
		<ParentID					������������ �����.
		<ParentName					��� ������������ �����, ������������, ���� ParentID == NA;
		<IncludeParent          ���� true, �� ������������ � ��� ParentID, ����� ������ ��� �������. ���� �������� ����������, �� �� ��� � ������� objIDs ������.
		<AllDescendants			���� false, �� ������������ ������ �������� �����, ����� -- ��� �����-�������.
		<FeodAttributes			�������� ������� � ������. ����� ����������� ������ �� ������, ������ ������������ � ������� ������ ���������� ����������.
		<FullNameLevel				������� � �������� ���������, ������� � �������� ��������� �������� �����.

		>objIDs						������ ��������������� �����.
		>objNames					������ �������� �����.
		>objTypes					������ ����� ��������������� ���������-������ ("Concept.Feod.Files.Site.Public")
		>objLevels					������ ������� ����������� �����. � ������������ ����� ������� ����������� ��������� = 0.

		>TotalStoredNum			������� ����� �������� ����� ���� ����������� � ������ ��������.
		>MaxNumInQuery				����������� ���������� ����� ������������� �� ���� ��� ��������.
		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_WEBFOLDER_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_WEBFOLDER_ENUMERATE_NUM)
	{
		ERR_RETURN_COMMENT_2 (ERR_TooManyEnumerate, "��������� %d �������� ������ WebFolder, � ����������� ����� ��������� %d", (arg.objLastNo - arg.objFirstNo), MAX_WEBFOLDER_ENUMERATE_NUM);
	}
// ���� �� ������ ������������� ������������ ����� -- ���� �� �����
	if (arg.ParentID==NA)
	{
		identifier feod_parent_ID = GetFeodIDByType (arg.ParentName);
		if (feod_parent_ID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("�� ������� ������������ ����� '%s'", arg.ParentName.c_str());
			ERR_RETURN_COMMENT_1 (ERR_BadName, "�� ������� ������������ ����� '%s'", arg.ParentName.c_str());
		}
		arg.ParentID = GetWebFolderIDByFeodID (feod_parent_ID);
	}
// ������������ ����� ������ ������������
	if (!CHECK_WEBFOLDER_ID(arg.ParentID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ ������������ ������ ID=%d", arg.ParentID);
	}
	OC_WebFolder oc_parent_folder (arg.ParentID);
	identifier   feod_parent_ID = guid(oc_parent_folder.m_MOD_Base_GUID).id;
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
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������ ���� ��������
	int				f;
	identifier_arr FeodArr;
	if (arg.AllDescendants)
	{
		GetFeodDescendantIDs (feod_parent_ID, FeodArr);
	}
	else
	{
		OC_Concept (feod_parent_ID).m_Child.CopyTo (FeodArr);
	}
	if (arg.IncludeParent) 
	{
		FeodArr.Insert (0, feod_parent_ID);
	}
	
// ���������� �� �����, � ������� ��� ���������� ������� � ������� �� ����� ���� �����������
	if (arg.FeodAttributes.Find ('L')==-1)
	{
		string tmp = arg.FeodAttributes;
		arg.FeodAttributes  = "L";
		arg.FeodAttributes += tmp;
	}
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (USER_CHECK_ACCESS (loginID, FeodArr[f], arg.FeodAttributes)!=ERR_OK)
		{
			FeodArr.Remove(f);
			f--;
		}
	}

// ���������� �� ���� ����������� �������� � ��������� �������� ���������
	int parent_level = GetFeodLevel (feod_parent_ID);
	for (f=arg.objFirstNo; f<=arg.objLastNo && f<FeodArr.Size(); f++)
	{
		identifier folderID = GetWebFolderIDByFeodID (FeodArr[f]);

		string folderName;
		GetWebFolderFullName (folderID, folderName, max (arg.FullNameLevel,3));

		string folderType;
		GetWebFolderType		(folderID, folderType);

		int folderLevel =	GetFeodLevel (FeodArr[f]) - parent_level;

		arg.objIDs		+= folderID;
		arg.objNames	+= folderName;
		arg.objTypes	+= folderType;
		arg.objLevels	+= folderLevel;
	}

// ����� ����� ��������, ������� ����� �����������
	arg.TotalStoredNum	=	FeodArr.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������� ������ WebFolder											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_GetData (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_GetData);
/*............................................................................[]
		<objID					������������� �������������� �������.
		<Login					����� ������������, �������������� ��������. ������������ ������ ����� ����� ������ [R].
		<Password				������ ������������, �������������� ��������.

		>Name						�������� �����.
		>FullName				������ �������� �����.
		>Description         �������� �����.
		>ExitCode				��� �������� (OK BadID BadLogin BadPassword AccessDeny).
		>ExitCodeComment		��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ WebFolder[%d] �� ����������", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
	identifier feodID = GetFeodIDByWebFolderID (arg.objID);
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
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, feodID, "R");
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
// ��������� ��������� ������ �������
	OC_Concept oc_feod (feodID);
	string folderFullName;
	GetWebFolderFullName (arg.objID, folderFullName, 3);

	arg.Name					=	oc_feod.m_Name;
	arg.Description		=	oc_feod.m_Description;
	arg.FullName			=	folderFullName;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������� ������ WebFolder											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_PutData (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_PutData);

ERR_RETURN (ERR_FunctionNotImplemented);
#if 0  //{ �������������� �������, ����� ��� �����������
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ WebFolder[%d] �� ����������", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.???"), "???");
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
// �������� ���� �������
	arg.Name	=	oc_folder.m_Name;

// �������� ��������� ���� ������ � ����� � ������������ � �������
//	...

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
#endif //}
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������� ������ WebFolder														[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFolder_Delete (MOD_WebFolder_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFolder_Delete);
ERR_RETURN (ERR_FunctionNotImplemented);
#if 0  //{ �������������� �������, ����� ��� �����������
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ WebFolder[%d] �� ����������", arg.objID);
	}
	OC_WebFolder oc_folder (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.???"), "???");
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
// �������� ��������� ���� ������ � ����� � ������������ �������
//	...

/*
	1. ������� ��� �������� �����
	2. ������� ������ �� ����� �� ����� (UserGroup)
*/

// ���������� ������
	oc_folder.Delete ();

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
#endif //}
}
//____________________________________________________________________________[]











/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/