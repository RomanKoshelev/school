/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Banner.cpp                                             []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������".                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                         
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Banner
#define USES_BX_Concept
#define USES_BX_Macros
#define USES_BX_Utils
#define USES_BX_VBN

#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_Banner
#define USES_OC_BannerProfile

#include "BX.h"
                                         
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Banner_New                                                             []             
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Banner_New(BX_Banner_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_User, arg.OwnerID))
		return BXE_Banner_New_InvalidOwnerID;
	if (arg.FileSize < 0)
		return BXE_Banner_New_InvalidFileSize;

// ������� ������ ������������-���������:
	OC_User		oc_user;
	oc_user.Open(arg.OwnerID);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
// �������� ������:
	OC_Banner	oc_banner;
	BX_CREATE_AND_CHECK(oc_banner);

// �������� ���� �������:

//	OwnerID
	oc_banner.m_OwnerID			= arg.OwnerID;
// VBN
	oc_banner.m_VBN				= oc_user.m_VBN;
// CreationTime
	oc_banner.m_CreationTime	= time_0;
// FileName
	oc_banner.m_FileName			= arg.FileName;
// FileSize
	oc_banner.m_FileSize			= arg.FileSize;
// Concept
	_IDsToBits_Set( arg.Concept, oc_banner.m_ba_Concept);
	ExpandConcept(arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_banner.m_eba_Concept);

// ���� ������ �������� �������, �� ��������� �� ����:
	if (OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.Profile))
	{
		SERVER_DEBUG_ASSERT_RETURN(
			oc_user.m_BannerProfile.Find(arg.Profile) != -1,
			"BX_Banner_New(): Submitted bannerprofile doesn't belong to user.",
			BX_SYSTEM_ERROR);
	// ��������� ������� � �������:
		oc_banner.m_Profile		= arg.Profile;
	// ��������� ������ � �������:
		OC_BannerProfile	oc_banner_profile;
		oc_banner_profile.Open(arg.Profile);
		oc_banner_profile.m_Banner.Add(oc_banner.GetObjectID());
	}
// ���� ������� �� ��������, �� �������� NA:
	else {
		oc_banner.m_Profile		= NA;
	}

// ������� � ������������ ������ �� ��������� ������:
	oc_user.m_Banner.Add(oc_banner.GetObjectID());

// ��������� ���������� ��� ����������:
	OC_VBN		oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr		ka;
	ka += (byte)oc_user.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Banner_New(): Invalid User::VBN.",
		BX_SYSTEM_ERROR);

	oc_banner.m_Allowed		= !bool(oc_vbn.m_IsModerated);
	oc_banner.m_ObjectState	= OBJ_STATE_NEW; // �����

// ��������� ������������� ���������� �������:	
	arg.objID = oc_banner.GetObjectID();

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Banner_GetData                                                         []                 
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Banner_GetData(BX_Banner_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Banner,arg.objID))
		return BXE_Banner_GetData_InvalidBannerID;

// ������� ������ �������:
	OC_Banner	oc_banner;
	oc_banner.Open(arg.objID);

// ������� ������ ������������-��������� �������:
	OC_User		oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner.m_OwnerID, OBJ_CLASS_ID_User);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
// OwnerID
	arg.OwnerID				= oc_banner.m_OwnerID;

// FileName
	arg.FileName			= oc_banner.m_FileName;

// FileSize
	arg.FileSize			= oc_banner.m_FileSize;

// UploadNo
	arg.UploadNo			= oc_banner.m_UploadNo;

// CreationTime, sCreationTime
	time_t	createTime =
		(time_t)(oc_banner.m_CreationTime + oc_user.m_TZOffset);
	
	arg.CreationTime	= createTime;
	arg.sCreationTime.Format("%s", asctime(gmtime(&createTime)));

// VBN
	arg.VBN					= (byte)oc_banner.m_VBN;

// State
	arg.State				= (bool)oc_banner.m_State;

// Profile
	arg.Profile				= oc_banner.m_Profile;

// Concept
	_BitsToIDs(	arg.Concept,	oc_banner.m_ba_Concept);

// TotalShows
	arg.TotalShows			= (int)oc_banner.m_TotalShows;

// TotalClicks
	arg.TotalClicks		= (int)oc_banner.m_TotalClicks;

// Allowed
	arg.Allowed				= (bool)oc_banner.m_Allowed;

// ObjectState
	arg.ObjectState		= (int)oc_banner.m_ObjectState;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Banner_PutData                                                         []
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Banner_PutData(BX_Banner_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Banner,arg.objID))
		return BXE_Banner_PutData_InvalidBannerID;

	bool	bCriticalChange = false;

// ������� ������ �������:
	OC_Banner		oc_banner;
	oc_banner.Open(arg.objID);

// ������� ������ ������������-��������� �������:
	OC_User			oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner.m_OwnerID, OBJ_CLASS_ID_User);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// �������� ���� ������� (����� ��������� ������ ���� �������):
	if (arg.Profile != NA)
	{
		 if (oc_user.m_BannerProfile.Find(arg.Profile) < 0)
			 return BXE_Banner_PutData_ProfileAccessDenied;
	}

//----------------------------------------------------------------------------[] 
// �������� ���������� ���������� ���������������:
	VALIDATE_ID		  (OBJ_CLASS_ID_BannerProfile,arg.Profile);
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept,		arg.Concept);

//----------------------------------------------------------------------------[] 
// ����������� �����:

// FileName
	oc_banner.m_FileName	= arg.FileName;

// FileSize
	oc_banner.m_FileSize	= arg.FileSize;

// UploadNo
	if (arg.UploadNo == (oc_banner.m_UploadNo+1)) {
		bCriticalChange = true;
		oc_banner.m_UploadNo = arg.UploadNo;
	}
// State
	oc_banner.m_State		= arg.State;

// Profile (��������� ����� ��������� �������):
	if (oc_banner.m_Profile != arg.Profile)
	{
		OC_BannerProfile		oc_banner_profile;

	// ������ ������ �� ������� �������:
		if (oc_banner.m_Profile != NA)
		{
			BX_CHECK_AND_OPEN(oc_banner_profile, oc_banner.m_Profile, OBJ_CLASS_ID_BannerProfile);
			DELETE_FROM_ARRAY(oc_banner_profile.m_Banner, arg.objID);
		}
	// ������� ������ � ����� �������:
		if (arg.Profile != NA)
		{
			BX_CHECK_AND_OPEN(oc_banner_profile, arg.Profile, OBJ_CLASS_ID_BannerProfile);
			oc_banner_profile.m_Banner.Add(arg.objID);
		}
	// �������� ������� � �������:
		oc_banner.m_Profile = arg.Profile;
	}

/*// RepeatCount
	if (arg.RepeatCount < 0) {
		arg.RepeatCount = -1;
	}
	oc_banner.m_RepeatCount = arg.RepeatCount;

// RepeatTime
	if (Time_IsValid(arg.RepeatTime))
	{
		oc_banner.m_RepeatTime = arg.RepeatTime;
	}
*/
// Concept
	_IDsToBits_Set(	arg.Concept, oc_banner.m_ba_Concept);
	ExpandConcept(arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_banner.m_eba_Concept);

// ��������� ������� ��������� �������:	
	if (bCriticalChange) {
		oc_banner.m_ObjectState		= OBJ_STATE_CHANGED_CRITICAL;
	}
	else {
		oc_banner.m_ObjectState		= OBJ_STATE_CHANGED;
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Banner_Delete                                                          []                
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Banner_Delete(BX_Banner_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Banner, arg.objID))
		return BXE_Banner_Delete_InvalidBannerID;
	
// ������� ��������� ������:
	OC_Banner	oc_banner;
	oc_banner.Open(arg.objID);
	
// ������� ������ ������������-��������� �������:
	OC_User		oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner.m_OwnerID, OBJ_CLASS_ID_User);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
// ������ ������ �� ������ � ������������:
	DELETE_FROM_ARRAY(oc_user.m_Banner, arg.objID);

// ������ ������ �� ������ � �������:
	if (oc_banner.m_Profile != NA)
	{
		OC_BannerProfile	oc_banner_profile;
		BX_CHECK_AND_OPEN(oc_banner_profile, oc_banner.m_Profile, OBJ_CLASS_ID_BannerProfile);
		DELETE_FROM_ARRAY(oc_banner_profile.m_Banner, arg.objID);
	}

// ������� ������:
	oc_banner.Delete();

	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_Banner_Enumerate                                                       []                   
//                                                                            []
BX_RESULT BX_Banner_Enumerate(BX_Banner_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_Banner			oc_object;
	identifier_arr		IDs;

	oc_object.GetClassIdList(IDs);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<IDs.Size()); i++)
	{
		oc_object.Open(IDs[i]);
		arg.objIDs.Add(IDs[i]);
		arg.objNames.Add(oc_object.m_FileName);
	}

	return BX_OK;	
}

//____________________________________________________________________________[]


/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/
