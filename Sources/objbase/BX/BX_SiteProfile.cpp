/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_SiteProfile.cpp                                        []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������� �����".            []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                       

#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_SiteProfile
#define USES_BX_Macros
#define USES_BX_ContentLevel
#define USES_BX_Utils
#define USES_BX_Concept
#define USES_BX_VBN

#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_Site
#define USES_OC_SiteProfile
#define USES_OC_Banner

#include "BX.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteProfile_New                                                        []                  
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_SiteProfile_New(BX_SiteProfile_Args& arg)
{
	arg.objID = NA;

	if (!OC_Exist(OBJ_CLASS_ID_User, arg.OwnerID))
		return BXE_SiteProfile_New_InvalidUserID;
	if ((arg.objFromID != NA) && !OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objFromID))
		return BXE_SiteProfile_New_InvalidProfileID;

// ������� ������ ������������-���������:
	OC_User				oc_user;
	oc_user.Open(arg.OwnerID);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// ������� �������:
	OC_SiteProfile		oc_site_profile;
	BX_CREATE_AND_CHECK(oc_site_profile);

// ���������, � �� ����� �� ����� ����������� ����� �������:
	if ((arg.objFromID != NA) && (oc_user.m_SiteProfile.Find(arg.objFromID) < 0))
	{
		SERVER_DEBUG_ERROR_1 ("BX_SiteProfile_New(): INTRUDER ALERT !!! Attempt to copy from an alien SiteProfile (#%lu). Creation mode selected.",
			arg.objFromID);
		arg.objFromID = NA;
	}
//----------------------------------------------------------------------------[] 
// �������� ������ �� ������� � ������������:
	oc_user.m_SiteProfile.Add(oc_site_profile.GetObjectID());

	if (arg.objFromID != NA)
	// ����� �����������
	{
		OC_SiteProfile		oc_site_profile_from;
		oc_site_profile_from.Open(arg.objFromID);

		oc_site_profile.CopyDataFrom(oc_site_profile_from);

      if (arg.Name.Length() == 0)
      {
         arg.Name = string("Copy of ") + string(oc_site_profile_from.m_Name);
      }
	}
	else
	// ����� ��������:
	{
		if (arg.Name.Length() == 0)
		{
			time_t	curtime = time_0 + (time_t)oc_user.m_TZOffset;
			arg.Name.Format("New profile (%s)", 
				asctime( gmtime(&curtime) ) );
		}

	// ������� � BannerExclude ������� ������������:
		identifier_arr UserBanners;
		UserBanners = oc_user.m_Banner.GetCPtr();
		UserBanners.Sort();
		oc_site_profile.m_BannerExclude = UserBanners;

	// MaxFileSize
		oc_site_profile.m_MaxFileSize = 50000;

/*	// Region
		oc_site_profile.m_ba_Region.CopyFrom(
			oc_user.m_ba_Region.GetPtr(),
			oc_user.m_ba_Region.Size());

		oc_site_profile.m_eba_Region.CopyFrom(
			oc_site_profile.m_ba_Region.GetPtr(),
			oc_site_profile.m_ba_Region.Size());

*/	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]

// ��������� �������� �������:
	oc_site_profile.m_Name		= arg.Name;

// ��������� ������� ������ ������:
	oc_site_profile.m_OwnerID	= arg.OwnerID;

// ����� ����� ������ ������:
	oc_site_profile.m_VBN		= oc_user.m_VBN;

// ����� ������� ��������� ������� (������ ������):
	oc_site_profile.m_Site.Delete();

// ��������� ����� �����������:
	oc_site_profile.m_LastModified = time_0;

// ��������� ���������� ��� ����������:
	OC_VBN		oc_vbn;
	key_arr		ka;
	oc_vbn.SetIndex_No();

	ka += (byte)oc_site_profile.m_VBN;
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_SiteProfile_New(): Incorrect SiteProfile::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

	oc_site_profile.m_Allowed		= !bool(oc_vbn.m_IsModerated);
	oc_site_profile.m_ObjectState	= OBJ_STATE_NEW; // �����

// ��������� ������������� ���������� �������:	
	arg.objID = oc_site_profile.GetObjectID();

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteProfile_CopyData                                                   []                       
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_SiteProfile_CopyData(BX_SiteProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objID))
		return BXE_SiteProfile_CopyData_InvalidProfileID;
	if (!OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objFromID))
		return BXE_SiteProfile_CopyData_InvalidProfileID;

// ������� �������, � ������� ����� ����������:
	OC_SiteProfile		oc_site_profile;
	oc_site_profile.Open(arg.objID);

// ������� ������ ������������-���������:
	OC_User				oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site_profile.m_OwnerID, OBJ_CLASS_ID_User);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// ���������, ���� �� ���� ������� � ������������
// (����� ������� ����� ����������, �� ������ � ����):
	if (oc_user.m_SiteProfile.Find(arg.objID) < 0)
	{
		SERVER_DEBUG_ERROR_1 ("BX_SiteProfile_CopyData(): INTRUDER ALERT !!! Attempt to copy to an alien SiteProfile (#%lu).",
			arg.objID);
		return BXE_SiteProfile_CopyData_AccessDenied;
	}

	if (oc_user.m_SiteProfile.Find(arg.objFromID) < 0)
	{
		SERVER_DEBUG_ERROR_1 ("BX_SiteProfile_CopyData(): INTRUDER ALERT !!! Attempt to copy from an alien SiteProfile (#%lu).",
			arg.objFromID);
		return BXE_SiteProfile_CopyData_AccessDenied;
	}

//----------------------------------------------------------------------------[] 

// ������� �������, �� �������� ����� ����������:
	OC_SiteProfile		oc_site_profile_from;
	oc_site_profile_from.Open(arg.objFromID);

// �����������:
	oc_site_profile.CopyDataFrom(oc_site_profile_from);

// �������� ���������:
	oc_site_profile.m_OwnerID = arg.OwnerID;

// ����� ����� ������ ������:
	oc_site_profile.m_VBN = oc_user.m_VBN;

// �������� �������� �������:
	oc_site_profile.m_Name = string("Copy of ") + oc_site_profile_from.m_Name;

// ����� ������� ��������� ������� (������ ������):
	oc_site_profile.m_Site.Delete();

// ��������� ������� ��������� �������:	
	oc_site_profile.m_ObjectState	= OBJ_STATE_CHANGED;

// ��������� ����� �����������:
	oc_site_profile.m_LastModified = time_0;

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteProfile_GetData                                                    []                      
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_SiteProfile_GetData(BX_SiteProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objID))
		return BXE_SiteProfile_GetData_InvalidProfileID;
	
// ������� ������ ������� �����:
	OC_SiteProfile	oc_site_profile;
	oc_site_profile.Open(arg.objID);

// ������� ������ ������������-���������:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site_profile.m_OwnerID, OBJ_CLASS_ID_User);
	
// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

	int	i;

//----------------------------------------------------------------------------[] 
// ��������:

// Name
	arg.Name = oc_site_profile.m_Name;

// Site, sSite
	arg.Site.Delete();
	arg.sSite.Delete();
	
	for (i = 0; i < oc_site_profile.m_Site.Size(); i++)
	{
	// ������� ��������� ���� �������:
		OC_Site	oc_site;
		BX_CHECK_AND_OPEN(oc_site, oc_site_profile.m_Site[i], OBJ_CLASS_ID_Site);
	// �������� ������������� ����� � �������:
		SERVER_DEBUG_ASSERT_RETURN(
			oc_site.m_VBN == oc_site_profile.m_VBN,
			"BX_SiteProfile_GetData(): Site & Profile VBNs do not match.",
			BX_SYSTEM_ERROR);
		SERVER_DEBUG_ASSERT_RETURN(
			oc_site.m_Profile == arg.objID,
			"BX_SiteProfile_GetData(): Site & Profile are not completely connected.",
			BX_SYSTEM_ERROR);
	// ������� id � ����� � �������� ��������:	
		arg.Site.Add(oc_site.GetObjectID());
		arg.sSite.Add(oc_site.m_Name);
	}

// VBN
	OC_VBN		oc_vbn;
	key_arr		ka;
	oc_vbn.SetIndex_No();
	ka += (byte)oc_site_profile.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_SiteProfile_GetData(): Incorrect SiteProfile::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

	arg.VBN	= oc_vbn.GetObjectID();

// LastModified	
	
	time_t	modifyTime =
		(time_t)(oc_site_profile.m_LastModified + oc_user.m_TZOffset);
	
	arg.LastModified	= modifyTime;
	arg.sLastModified.Format("%s", asctime(gmtime(&modifyTime)));

//	OwnerID
	arg.OwnerID			= oc_site_profile.m_OwnerID;

// BannerInclude
	arg.BannerInclude = oc_site_profile.m_BannerInclude.GetCPtr();

// BannerExclude
	arg.BannerExclude = oc_site_profile.m_BannerExclude.GetCPtr();

// SiteInclude
	arg.SiteInclude	= oc_site_profile.m_SiteInclude.GetCPtr();

// SiteExclude
	arg.SiteExclude	= oc_site_profile.m_SiteExclude.GetCPtr();
	
// MaxFileSize
	arg.MaxFileSize = oc_site_profile.m_MaxFileSize;

// UseKeywords
	arg.UseKeywords = (bool)oc_site_profile.m_UseKeywords;
	
// BannerConceptInclude
	_BitsToIDs( arg.BannerConceptInclude, oc_site_profile.m_ba_BannerConceptInclude);

// BannerConceptExclude
	_BitsToIDs( arg.BannerConceptExclude, oc_site_profile.m_ba_BannerConceptExclude);

// Allowed
	arg.Allowed			= (bool)oc_site_profile.m_Allowed;

// ObjectState
	arg.ObjectState	= oc_site_profile.m_ObjectState;

// ModeratorComment
	//arg.ModeratorComment

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteProfile_PutData                                                    []                      
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_SiteProfile_PutData(BX_SiteProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objID))
		return BXE_SiteProfile_PutData_InvalidProfileID;
	
// ������� ������ ������� �����:
	OC_SiteProfile	oc_site_profile;
	oc_site_profile.Open(arg.objID);

// ������� ������ ������������-���������:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site_profile.m_OwnerID, OBJ_CLASS_ID_User);
	
// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// ������� VBN �������:
	OC_VBN		oc_vbn;
	key_arr		ka;
	oc_vbn.SetIndex_No();

	ka += (byte)oc_site_profile.m_VBN;
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_SiteProfile_PutData(): Incorrect SiteProfile::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

//----------------------------------------------------------------------------[] 
// �����������:
	
// Name
	oc_site_profile.m_Name  = arg.Name;

// BannerInclude
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Banner,			arg.BannerInclude);
	arg.BannerInclude.Sort();
	oc_site_profile.m_BannerInclude = arg.BannerInclude;

// BannerExclude
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Banner,			arg.BannerExclude);
	arg.BannerExclude.Sort();
	oc_site_profile.m_BannerExclude = arg.BannerExclude;

// SiteInclude
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Site,			arg.SiteInclude);
	arg.SiteInclude.Sort();
	oc_site_profile.m_SiteInclude = arg.SiteInclude;

// SiteExclude
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Site,			arg.SiteExclude);
	arg.SiteExclude.Sort();
	oc_site_profile.m_SiteExclude = arg.SiteExclude;

// MaxFileSize
	if (arg.MaxFileSize >= 0) {
		oc_site_profile.m_MaxFileSize = arg.MaxFileSize;
	}

// UseKeywords
	oc_site_profile.m_UseKeywords = arg.UseKeywords;

// BannerConceptInclude,BannerConceptExclude
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept,		arg.BannerConceptInclude);
	_IDsToBits_Set( arg.BannerConceptInclude, oc_site_profile.m_ba_BannerConceptInclude);
	ExpandConcept(arg.BannerConceptInclude);
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept,		arg.BannerConceptExclude);
	_IDsToBits_Set( arg.BannerConceptExclude, oc_site_profile.m_ba_BannerConceptExclude);
	ExpandConcept(arg.BannerConceptExclude);
	// eba_Concept
	_IDsToBits_Set  (arg.BannerConceptInclude, oc_site_profile.m_eba_BannerConcept);
	_IDsToBits_OrNot(arg.BannerConceptExclude, oc_site_profile.m_eba_BannerConcept);

// ��������� ������� ��������� �������:	
	oc_site_profile.m_ObjectState	= OBJ_STATE_CHANGED;

// ��������� ����� �����������:
	oc_site_profile.m_LastModified = time_0;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteProfile_Delete                                                     []                     
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_SiteProfile_Delete(BX_SiteProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.objID))
		return BXE_SiteProfile_Delete_InvalidProfileID;

// ������� �������, ������� ����� ����������:
	OC_SiteProfile		oc_site_profile;
	oc_site_profile.Open(arg.objID);

// ������� ������������-��������� �������:
	OC_User				oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site_profile.m_OwnerID, OBJ_CLASS_ID_User);

// ��������� ������:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// ��������� ������� ����� ������� � ������������:
	SERVER_DEBUG_ASSERT_RETURN(
		oc_user.m_SiteProfile.Find(oc_site_profile.m_OwnerID) != -1,
		"BX_SiteProfile_Delete(): Can't found site profile ID in User::SiteProfile[].",
		BX_SYSTEM_ERROR);

// ������� VBN �������:
	OC_VBN	oc_vbn;
	key_arr	ka;
	ka += (byte)oc_site_profile.m_VBN;
	oc_vbn.SetIndex_No();
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_SiteProfile_Delete(): Wrong SiteProfile::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);
	
	int i = 0;

//----------------------------------------------------------------------------[] 

	OC_Site	oc_site;

// ���� � ������� �������� ����� ...
	while (oc_site_profile.m_Site.Size() > 0)
	{
	// �������� ����:	
		BX_CHECK_AND_OPEN(oc_site, oc_site_profile.m_Site[i], OBJ_CLASS_ID_Site);
	// ����� � ����� ������ �� �������:
		oc_site.m_Profile = NA;
	// ������ ������ �� ���� � �������:
		oc_site_profile.m_Site.Del(0);
	}

// ������� ������ �� ������� � ������������:
	DELETE_FROM_ARRAY(oc_user.m_SiteProfile, arg.objID);

// ������� �������:
	oc_site_profile.Delete();

	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_SiteProfile_Enumerate                                                  []                        
//                                                                            []
BX_RESULT BX_SiteProfile_Enumerate(BX_SiteProfile_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_SiteProfile			oc_object;
	identifier_arr			IDs;

	oc_object.GetClassIdList(IDs);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<IDs.Size()); i++)
	{
		oc_object.Open(IDs[i]);
		arg.objIDs.Add(IDs[i]);
		arg.objNames.Add(oc_object.m_Name);
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
