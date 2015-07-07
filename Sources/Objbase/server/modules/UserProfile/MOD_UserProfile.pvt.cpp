/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserProfile.pvt.cpp													[]
[] Date:          11.�������.2000															[]
[] Author:        Roman V. Koshelev, Ekaterina B. Loupacheva 						[]
[] Description:   ������ � ����������� � �������������� ������� �������������	[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserProfile.inc.h"


//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_USERPROFILE_GUID (guid profileGUID)
{
	DEBUG_STACK_NAME (CHECK_USERPROFILE_GUID);

// ������ ������ ������������
	if (!OC_Exist (profileGUID))
	{
		return false;
	}
	
// �������� �� ����������� ��������� ������
	IF_NOT_CHECK_MOD_BASE (UserProfile, User, profileGUID)
	{
		return false;
	}

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_USERPROFILE_ID (identifier profileID)
{
	DEBUG_STACK_NAME (CHECK_USERPROFILE_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_UserProfile, profileID))
	{
		return false;
	}
	OC_UserProfile oc_profile (profileID);

	guid gi = oc_profile.GetObjectGUID ();
	
	return CHECK_USERPROFILE_GUID(gi);

	return true;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` �������� ������� �� ������������														[]
//  ���� �� ����������, �������� �����													[]
//                                                                            []
identifier GetUserProfileIDByUserID (identifier userID)
{
	DEBUG_STACK_NAME (GetUserProfileIDByUserID);

	GET_MOD_EXTENSION (User, userID, UserProfile, profile);

	if (profileID!=NA && CHECK_USERPROFILE_ID (profileID))
	{
		return profileID;
	}
	return NA;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` �������� ������� � ������� ������� ������������                           []                                       
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_USERPROFILE (identifier loginID, identifier userID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_USERPROFILE);

// ��� ������������ ����� ��� ����� �� ���� �������.
	if (loginID==userID)
	{
		return ERR_OK;
	}

// ������������ ������ �������� ������� ������������� ������ �������������
	ERR_RESULT res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), Attributes);
	if (res != ERR_OK)
	{
		return res;
	}
	
// ������������ ������ �������� ����� ������� ������� �������, ��� �������� �������.
	OC_User oc_login	(loginID);
	OC_User oc_user	(userID);
	if (oc_login.m_AccessLevel >= oc_user.m_AccessLevel)
	{
		return ERR_InsufficientAccessLevel;
	}

	return ERR_OK;
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` ���������� ���� ���������, ���������� ������������� � ����						[]
//                                                                            []
bool UserProfileLogUpdate (identifier userID, int Action, guid objGUID, int Time)
{
	DEBUG_STACK_NAME (UserProfileLogUpdate);


//----------------------------------------------------------------------------[] 
// �������� ���� ��������
	if (Action>=USER_LOG_last_bad || Action<=USER_LOG_first_bad)
	{
		SERVER_DEBUG_ERROR_1 ("��������� ��� ������ (%d) � ���", Action);
		return false;
	}
// ��������� ������������� ������������
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		return false;
	}
// ���� �� �������� ������� -- ��������� ������
	identifier profileID = GetUserProfileIDByUserID (userID);
	if (profileID==NA) 
	{
		return false;
	}
	OC_UserProfile oc_profile (profileID);
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
// ���������� ����
  	oc_profile.m_Log_Action		+= Action;
	oc_profile.m_Log_Time		+=	Time; 	
	oc_profile.m_Log_ObjectGUID+= objGUID;
//----------------------------------------------------------------------------[] 


	return true;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/