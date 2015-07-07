/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserProfile.cpp														[]
[] Date:          11.�������.2000															[]
[] Author:        Roman V. Koshelev, Ekaterina B. Loupacheva 						[]
[] Description:   ������ � ����������� � �������������� ������� �������������	[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserProfile.inc.h"				 




//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������� ������ UserProfile											[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_UserProfile_GetData (MOD_UserProfile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_UserProfile_GetData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ������������ ������ �������� ������� ������������� ������ ������������� � �������� ����� ������� ������� �������, ��� ���� ����� �������������.
		<Password					������ ������������, �������������� ��������.

		<objID						������������� ������������, ��� ������� �������������.

		>Log_ObjectClassIDs		������ ��������������� ������� ��������, ������� ������� (������, �������� ...) ������������
		>Log_ObjectClassNames	������ ���� ������� ��������, ������� ������� (������, �������� ...) ������������
		>Log_ObjectIDs				������ ��������������� ��������, ������� ������� (������, �������� ...) ������������
		>Log_ObjectNames		   ������ ���� ��������, ������� ������� (������, �������� ...) ������������
		>Log_ActionCodes			������ ����� ��������, ������� �������� ������������ 
		>Log_ActionDescriptions	����������� ����� ��������
		>Log_Times					������� ���������� ��������, ������� �������� ������������

		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ������������� ������������
	if (!OC_Exist (OBJ_CLASS_ID_User, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_SYSTEM_ERROR,"������������ � �������� ��������������� %u �� ����������",arg.objID);

	}
	
	identifier profileID = GetUserProfileIDByUserID (arg.objID);

// ���� �� �������� ������� -- ��������� ������
	if (profileID==NA) 
	{
		string login, name;
		UserGetLoginFullName (GetUserGUID (arg.objID), login, name);
		ERR_RETURN_COMMENT_3 (ERR_SYSTEM_ERROR, "�� ������� ������� ������� � ������������ '%s' (%s) ID=%u", login.c_str(), name.c_str(), arg.objID);
	}
	OC_UserProfile oc_profile (profileID);
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
// ��������� ����� ������� -- ������������ ������ �������� ������� ������������� ������ 
//	������������� � �������� ����� ������� ������� �������, ��� ���� ����� �������������.
	res = USER_CHECK_ACCESS_TO_USERPROFILE (loginID, arg.objID, "R");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [R] �� ��������� ������");
	}
//----------------------------------------------------------------------------[] 








//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���������� ������ ����
	for (int l=0; l<oc_profile.m_Log_Action.Size(); l++)
	{
		int oc_profile_m_Log_Action =oc_profile.m_Log_Action[l];
		

		if (oc_profile_m_Log_Action>=USER_LOG_last_bad || oc_profile_m_Log_Action<=USER_LOG_first_bad)
		{
			SERVER_DEBUG_ERROR_1 ("��������� ��� ������ (%d) � ���, ����������", oc_profile_m_Log_Action);
			oc_profile.m_Log_ObjectGUID.Del (l);
			oc_profile.m_Log_Action		.Del (l);
			oc_profile.m_Log_Time		.Del (l);
			l --;
			continue;
		}

		arg.Log_ActionCodes			+=	oc_profile_m_Log_Action;
		arg.Log_ActionDescriptions	+=	USER_LOG_DESCRIPTION [oc_profile_m_Log_Action];

		guid gi							 = oc_profile.m_Log_ObjectGUID[l];
		arg.Log_ObjectClassIDs		+=	gi.cl;
		arg.Log_ObjectClassNames	+=	className [gi.cl];

		arg.Log_ObjectIDs				+=	gi.id;
		arg.Log_ObjectNames		   +=	MOD_GET_OBJECT_NAME (gi);
		arg.Log_Times					+=	oc_profile.m_Log_Time[l];
	}
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]













#if 0  //{ �������������� �������, ����� ��� �����������
//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ������� ������ xxx													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_xxx_PutData (MOD_xxx_Args& arg)
{
	DEBUG_STACK_NAME (MOD_xxx_PutData);
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_xxx, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ xxx[%u] �� ����������", arg.objID);
	}
	OC_xxx oc_xxx (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS_TO_XXX (loginID, arg.objID, "W");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� ��� ���������� ��������");
	}
//	��������� ������� �������
	if (oc_meta.m_AccessLevelThreshold <= oc_login.m_AccessLevel)
	{
		ERR_RETURN_COMMENT_2 (ERR_InsufficientAccessLevel, "������������� ������� ������� (%d) ��� ��������� ������� (%d)", int(oc_login.m_AccessLevel), int(oc_meta.m_AccessLevelThreshold));
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������ �� ����� ������ ���� �������, � ������� �� ����� �������� ������� [D]
	int i,j;
	for (i=0; i<oc_meta.m_FeodGUID.Size(); i++)
	{
		guid gi = oc_meta.m_FeodGUID[i];
	//	���� ���� �� ������� � ���������� -- ������ � ��������, ��������� ������������� ��������
		if (arg.FeodIDs.Find (gi.id)==-1)
		{
			if (USER_CHECK_ACCESS (loginID, gi.id, "D")!=ERR_OK)
			{
				string feodName;
				GetFeodName(gi.id, feodName);
				ERR_RETURN_COMMENT_2 (ERR_AccessDeny, "������������ �� ����� ����� ������� ������ �� ���� ������� '%s'[%u]", feodName.c_str(), arg.FeodIDs[i]);
			}
		}
	}
// ������������ �� ����� ��������� ���� �������, � ������� �� ����� �������� ������� [C]
	for (i=0; i<arg.FeodIDs.Size(); i++)
	{
		bool bFoundInRel = false;
	//	���� ��������� ���� � ���������
		for (j=0; j<oc_meta.m_FeodGUID.Size(); j++)
		{
			if (guid(oc_meta.m_FeodGUID[j]).id == arg.FeodIDs[i])
			{
				bFoundInRel = true;
				break;
			}
		}
	//	���� ���� �� ������� � ��������� -- ������ � ��������, ��������� ������������� ��������
		if (!bFoundInRel && USER_CHECK_ACCESS (loginID, arg.FeodIDs[i], "C")!=ERR_OK)
		{
			string feodName;
			GetFeodName (arg.FeodIDs[i], feodName);
			ERR_RETURN_COMMENT_2 (ERR_AccessDeny, "������������ �� ����� ����� ������� ������ � ���� ������� '%s'[%u]", feodName.c_str(), arg.FeodIDs[i]);
		}
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ���� �������
	arg.Name	=	oc_xxx.m_Name;

// �������� ��������� ���� ������ � ����� � ������������ � �������
//	...

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]
#endif //}













#if 0  //{ �������������� �������, ����� ��� �����������
//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������� ������ xxx																[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_xxx_Delete (MOD_xxx_Args& arg)
{
	DEBUG_STACK_NAME (MOD_xxx_Delete);
/*............................................................................[]
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_xxx, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ xxx[%u] �� ����������", arg.objID);
	}
	OC_xxx oc_xxx (arg.objID);
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
// ��������� ����� �������
	res = USER_CHECK_ACCESS_TO_XXX (loginID, arg.objID, "D");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "��� ������� [D] ��� �������� �������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ��������� ���� ������ � ����� � ������������ �������
//	...

// ���������� ������
	oc_xxx.Delete ();

//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]
#endif //}











/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/