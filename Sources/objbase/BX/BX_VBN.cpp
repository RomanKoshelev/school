/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_VBN.cpp                                                []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "Виртуальная баннерная сеть"[]
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                               
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_VBN
#define USES_BX_Macros
#define USES_BX_Concept
#define USES_BX_Admin

#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_Concept
#define USES_OC_Language

#include "BX.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_New                                                                []          
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_New(BX_VBN_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;

// Пустые пароли назначать нельзя:
	if (arg.Password.Size() < 1)
		return BXE_VBN_New_PasswordVoid;

	if (oc_reg.m_Language.Size() == 0)
		return BXE_NoLanguages;

//----------------------------------------------------------------------------[] 
	OC_VBN 		oc_vbn;

// Найти последний порядковый объекта:
	int LastNo = -1;
	oc_vbn.SetIndex_No();
	if (oc_vbn.GoLast())
		LastNo = oc_vbn.m_No;

// Создать объект
	oc_vbn.New();
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.IsValid(),
		"BX_VBN_New(): Error creating object.",
		BX_SYSTEM_ERROR);

// Присвоить порядковый номер
	oc_vbn.m_No			= byte(LastNo + 1);

// Установить пароль:
	oc_vbn.m_Password = arg.Password;

// Зарегистрировать в реестре:
	oc_reg.m_VBN.Add(oc_vbn.GetObjectID());

	arg.objID = oc_vbn.GetObjectID();

//----------------------------------------------------------------------------[] 
// Установить параметры сети:

// Name
	if (arg.Name.Size() > 0)
		oc_vbn.m_Name	= arg.Name;
	else if ( (string(oc_vbn.m_Name)).Size() == 0)
	{
		arg.Name.Format("VBN #%d", (int)oc_vbn.m_No);
		oc_vbn.m_Name	= arg.Name;
	}

// Description
	oc_vbn.m_Description			= arg.Description;

// IsModerated
	oc_vbn.m_IsModerated			= arg.IsModerated;

// DefaultLanguage
	if (OC_Exist(OBJ_CLASS_ID_Language, arg.DefaultLanguage))
		oc_vbn.m_DefaultLanguage	= arg.DefaultLanguage;
	else
		oc_vbn.m_DefaultLanguage	= oc_reg.m_Language[0];

// DefaultTZOffset
	if (labs(arg.DefaultTZOffset) <= SECS_IN_DAY/2) {
		oc_vbn.m_DefaultTZOffset	= arg.DefaultTZOffset;
	}

// ConceptMask
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.ConceptMask);
	ExpandWithParentConcepts(arg.ConceptMask);
	_IDsToBits_Set(	arg.ConceptMask, oc_vbn.m_ConceptMask);

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_PutData                                                            []              
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_PutData(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))
		return BXE_VBN_New_InvalidObjectID;

	OC_VBN 		oc_vbn;
	oc_vbn.Open(arg.objID);

	if ((string(oc_vbn.m_Password) != arg.Password) && (!CheckAdminPassword(arg.Password)))
		return BXE_VBN_New_AccessDenied;
//----------------------------------------------------------------------------[] 
// Установить параметры:

// Name
	if (arg.Name.Size() > 0)
		oc_vbn.m_Name	= arg.Name;
	else if ( (string(oc_vbn.m_Name)).Size() == 0 )
	{
		arg.Name.Format("VBN #%d", (int)oc_vbn.m_No);
		oc_vbn.m_Name	= arg.Name;
	}

// Description
	oc_vbn.m_Description			= arg.Description;

// IsModerated
	oc_vbn.m_IsModerated			= arg.IsModerated;

// DefaultLanguage
	if (OC_Exist(OBJ_CLASS_ID_Language, arg.DefaultLanguage))
		oc_vbn.m_DefaultLanguage	= arg.DefaultLanguage;

// DefaultTZOffset
	if (labs(arg.DefaultTZOffset) <= SECS_IN_DAY/2) {
		oc_vbn.m_DefaultTZOffset	= arg.DefaultTZOffset;
	}

// ConceptMask
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.ConceptMask);
	ExpandWithParentConcepts(arg.ConceptMask);
	_IDsToBits_Set(	arg.ConceptMask,		oc_vbn.m_ConceptMask);

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_Enumerate																            []                     
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_Enumerate(BX_VBN_Args& arg)
{
	if (arg.objFirstNo < 0)					arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)	arg.objLastNo		= INT_MAX;

	arg.objNames.Delete();
	arg.objIDs.Delete();

	OC_VBN		oc_vbn;

	for (int i=arg.objFirstNo; (i<oc_reg.m_VBN.Size()) && (i<=arg.objLastNo); i++)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_VBN, oc_reg.m_VBN[i]),
			"BX_VBN_Enumerate(): Invalid Registry::VBN[i].",
			BX_SYSTEM_ERROR);

		oc_vbn.Open(oc_reg.m_VBN[i]);

		arg.objNames.Add(oc_vbn.m_Name);
		arg.objIDs.Add(oc_reg.m_VBN[i]);
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_GetData                                                            []              
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_GetData(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))
		return BXE_VBN_GetData_InvalidObjectID;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);
/*
	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_GetData_AccessDenied;
*/
	arg.Name						= oc_vbn.m_Name;
	arg.Description			= oc_vbn.m_Description;
									
	arg.IsModerated			= (bool)oc_vbn.m_IsModerated;

	arg.DefaultLanguage		= oc_vbn.m_DefaultLanguage;
	arg.DefaultTZOffset		= oc_vbn.m_DefaultTZOffset;

//	arg.Owner					= oc_vbn.m_Owner;
	arg.No						= (byte)oc_vbn.m_No;

	_BitsToIDs(			arg.ConceptMask,			oc_vbn.m_ConceptMask);

	return BX_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ConceptEnumerate                                                     []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_ConceptEnumerate(BX_VBN_Args& arg)
{
	if (oc_reg.m_Language.Size() == 0)						return BXE_NoLanguages;
	if (arg.objLanguageNo > oc_reg.m_Language.Size())	arg.objLanguageNo = -1;

	arg.objNames.Delete();
	arg.objIDs.Delete();

	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))
		return BXE_VBN_GetData_InvalidObjectID;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	identifier_arr	ConceptIDs;
	_BitsToIDs(		ConceptIDs, 	oc_vbn.m_ConceptMask);


	if (arg.objLanguageNo < 0)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Language,  oc_vbn.m_DefaultLanguage),
			"BX_VBN_ConceptEnumerate(): Invalid VBN::DefaultLanguage.",
			BX_SYSTEM_ERROR);
		OC_Language	oc_language;
		oc_language.Open(oc_vbn.m_DefaultLanguage);

		arg.objLanguageNo = oc_language.m_No;
	}
	
	OC_Concept			oc_concept;
	for (int i = 0; i < ConceptIDs.Size(); i++) 
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Concept, ConceptIDs[i]),
			"BX_VBN_ConceptEnumerate(): Invalid VBN::ConceptMask.",
			BX_SYSTEM_ERROR);

		arg.objIDs.Add(ConceptIDs[i]);

		oc_concept.Open(ConceptIDs[i]);
		SERVER_DEBUG_ASSERT_RETURN(
			oc_concept.m_Name.Size() > arg.objLanguageNo,
			"BX_VBN_ConceptEnumerate(): Invalid Concept::Name || Language::No.",
			BX_SYSTEM_ERROR);

		arg.objNames.Add(oc_concept.m_Name[arg.objLanguageNo]);

	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_GetOwnerID                                                         []                 
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_GetOwnerID(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))
		return BXE_VBN_GetOwnerID_InvalidObjectID;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_GetOwnerID_AccessDenied;

	arg.Owner					= oc_vbn.m_Owner;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_Delete                                                             []             
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_Delete(BX_VBN_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
	
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))
		return BXE_VBN_Delete_InvalidObjectID;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	BX_TRACE("BX_VBN_Delete(): NOT SUPPORTED.");
	SERVER_DEBUG_ERROR("BX_VBN_Delete(): NOT SUPPORTED.");
	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UserEnumerate                                                      []                    
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UserEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_User			oc_user;
	key_arr			ka;
	identifier_arr	AllowedUsers;

	oc_user.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;

	oc_user.GetClassIdList(AllowedUsers, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<AllowedUsers.Size()); i++)
	{
		oc_user.Open(AllowedUsers[i]);
		arg.objIDs.Add(AllowedUsers[i]);
		arg.objNames.Add(oc_user.m_Login);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_BannerEnumerate				                                          []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_BannerEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	OC_Banner		oc_banner;
	key_arr			ka;
	identifier_arr	AllowedBanners;

	oc_banner.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;

	oc_banner.GetClassIdList(AllowedBanners, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<AllowedBanners.Size()); i++)
	{
		oc_banner.Open(AllowedBanners[i]);
		arg.objIDs.Add(AllowedBanners[i]);
		arg.objNames.Add(oc_banner.m_FileName);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_SiteEnumerate			                                             []                         
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_SiteEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	OC_Site			oc_site;
	key_arr			ka;
	identifier_arr	AllowedSites;

	oc_site.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;

	oc_site.GetClassIdList(AllowedSites, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<AllowedSites.Size()); i++)
	{
		oc_site.Open(AllowedSites[i]);
		arg.objIDs.Add(AllowedSites[i]);
		arg.objNames.Add(oc_site.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_BannerProfileEnumerate                                             []                             
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_BannerProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	OC_BannerProfile		oc_banner_profile;
	key_arr			ka;
	identifier_arr	AllowedBannerProfiles;

	oc_banner_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;

	oc_banner_profile.GetClassIdList(AllowedBannerProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<AllowedBannerProfiles.Size()); i++)
	{
		oc_banner_profile.Open(AllowedBannerProfiles[i]);
		arg.objIDs.Add(AllowedBannerProfiles[i]);
		arg.objNames.Add(oc_banner_profile.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_SiteProfileEnumerate                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_VBN_SiteProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	OC_SiteProfile	oc_site_profile;
	key_arr			ka;
	identifier_arr	AllowedSiteProfiles;

	oc_site_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;

	oc_site_profile.GetClassIdList(AllowedSiteProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<AllowedSiteProfiles.Size()); i++)
	{
		oc_site_profile.Open(AllowedSiteProfiles[i]);
		arg.objIDs.Add(AllowedSiteProfiles[i]);
		arg.objNames.Add(oc_site_profile.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UnallowedUserEnumerate                                             []                    
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UnallowedUserEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_User			oc_user;
	key_arr			ka;
	identifier_arr	UnallowedUsers;

	oc_user.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += false;

	oc_user.GetClassIdList(UnallowedUsers, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<UnallowedUsers.Size()); i++)
	{
		oc_user.Open(UnallowedUsers[i]);
		arg.objIDs.Add(UnallowedUsers[i]);
		arg.objNames.Add(oc_user.m_Login);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UnallowedSiteEnumerate															[]                                   
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UnallowedSiteEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Site			oc_site;
	key_arr			ka;
	identifier_arr	UnallowedSites;

	oc_site.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += false;

	oc_site.GetClassIdList(UnallowedSites, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<UnallowedSites.Size()); i++)
	{
		oc_site.Open(UnallowedSites[i]);
		arg.objIDs.Add(UnallowedSites[i]);
		arg.objNames.Add(oc_site.m_URL);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UnallowedSiteProfileEnumerate													[]                                          
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UnallowedSiteProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_SiteProfile	oc_site_profile;
	key_arr			ka;
	identifier_arr	UnallowedSiteProfiles;

	oc_site_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += false;

	oc_site_profile.GetClassIdList(UnallowedSiteProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<UnallowedSiteProfiles.Size()); i++)
	{
		oc_site_profile.Open(UnallowedSiteProfiles[i]);
		arg.objIDs.Add(UnallowedSiteProfiles[i]);
		arg.objNames.Add(oc_site_profile.m_Name);
	}

	return BX_OK;	
}
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UnallowedBannerEnumerate															[]                                   
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UnallowedBannerEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Banner			oc_banner;
	key_arr			ka;
	identifier_arr	UnallowedBanners;

	oc_banner.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += false;

	oc_banner.GetClassIdList(UnallowedBanners, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<UnallowedBanners.Size()); i++)
	{
		oc_banner.Open(UnallowedBanners[i]);
		arg.objIDs.Add(UnallowedBanners[i]);
		arg.objNames.Add(oc_banner.m_FileName);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_UnallowedBannerProfileEnumerate												[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_UnallowedBannerProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN				oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_BannerProfile	oc_banner_profile;
	key_arr				ka;
	identifier_arr		UnallowedBannerProfiles;

	oc_banner_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += false;

	oc_banner_profile.GetClassIdList(UnallowedBannerProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<UnallowedBannerProfiles.Size()); i++)
	{
		oc_banner_profile.Open(UnallowedBannerProfiles[i]);
		arg.objIDs.Add(UnallowedBannerProfiles[i]);
		arg.objNames.Add(oc_banner_profile.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_NewUserEnumerate                                                   []                       
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_VBN_NewUserEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_User			oc_user;
	key_arr			ka;
	identifier_arr	NewUsers;

	oc_user.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_NEW;

	oc_user.GetClassIdList(NewUsers, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<NewUsers.Size()); i++)
	{
		oc_user.Open(NewUsers[i]);
		arg.objIDs.Add(NewUsers[i]);
		arg.objNames.Add(oc_user.m_Login);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_NewSiteEnumerate																	[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_NewSiteEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Site			oc_site;
	key_arr			ka;
	identifier_arr	NewSites;

	oc_site.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_NEW;

	oc_site.GetClassIdList(NewSites, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<NewSites.Size()); i++)
	{
		oc_site.Open(NewSites[i]);
		arg.objIDs.Add(NewSites[i]);
		arg.objNames.Add(oc_site.m_URL);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_NewSiteProfileEnumerate															[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_NewSiteProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_SiteProfile	oc_site_profile;
	key_arr			ka;
	identifier_arr	NewSiteProfiles;

	oc_site_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_NEW;

	oc_site_profile.GetClassIdList(NewSiteProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<NewSiteProfiles.Size()); i++)
	{
		oc_site_profile.Open(NewSiteProfiles[i]);
		arg.objIDs.Add(NewSiteProfiles[i]);
		arg.objNames.Add(oc_site_profile.m_Name);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_NewBannerEnumerate																	[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_NewBannerEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Banner			oc_banner;
	key_arr			ka;
	identifier_arr	NewBanners;

	oc_banner.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_NEW;

	oc_banner.GetClassIdList(NewBanners, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<NewBanners.Size()); i++)
	{
		oc_banner.Open(NewBanners[i]);
		arg.objIDs.Add(NewBanners[i]);
		arg.objNames.Add(oc_banner.m_FileName);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_NewBannerProfileEnumerate														[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_NewBannerProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN				oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_BannerProfile	oc_banner_profile;
	key_arr				ka;
	identifier_arr		NewBannerProfiles;

	oc_banner_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_NEW;

	oc_banner_profile.GetClassIdList(NewBannerProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<NewBannerProfiles.Size()); i++)
	{
		oc_banner_profile.Open(NewBannerProfiles[i]);
		arg.objIDs.Add(NewBannerProfiles[i]);
		arg.objNames.Add(oc_banner_profile.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ChangedUserEnumerate                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_ChangedUserEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_User			oc_user;
	key_arr			ka;
	identifier_arr	ChangedUsers;

	oc_user.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_CHANGED;

	oc_user.GetClassIdList(ChangedUsers, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<ChangedUsers.Size()); i++)
	{
		oc_user.Open(ChangedUsers[i]);
		arg.objIDs.Add(ChangedUsers[i]);
		arg.objNames.Add(oc_user.m_Login);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ChangedSiteEnumerate																[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_ChangedSiteEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Site			oc_site;
	key_arr			ka;
	identifier_arr	ChangedSites;

	oc_site.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_CHANGED;

	oc_site.GetClassIdList(ChangedSites, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<ChangedSites.Size()); i++)
	{
		oc_site.Open(ChangedSites[i]);
		arg.objIDs.Add(ChangedSites[i]);
		arg.objNames.Add(oc_site.m_URL);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ChangedSiteProfileEnumerate														[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_ChangedSiteProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_SiteProfile	oc_site_profile;
	key_arr			ka;
	identifier_arr	ChangedSiteProfiles;

	oc_site_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_CHANGED;

	oc_site_profile.GetClassIdList(ChangedSiteProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<ChangedSiteProfiles.Size()); i++)
	{
		oc_site_profile.Open(ChangedSiteProfiles[i]);
		arg.objIDs.Add(ChangedSiteProfiles[i]);
		arg.objNames.Add(oc_site_profile.m_Name);
	}

	return BX_OK;	
}
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ChangedBannerEnumerate															[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_ChangedBannerEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN			oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_Banner		oc_banner;
	key_arr			ka;
	identifier_arr	ChangedBanners;

	oc_banner.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_CHANGED;

	oc_banner.GetClassIdList(ChangedBanners, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<ChangedBanners.Size()); i++)
	{
		oc_banner.Open(ChangedBanners[i]);
		arg.objIDs.Add(ChangedBanners[i]);
		arg.objNames.Add(oc_banner.m_FileName);
	}

	return BX_OK;	
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_ChangedBannerProfileEnumerate													[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_ChangedBannerProfileEnumerate(BX_VBN_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.objID))	return BXE_VBN_InvalidObjectID;
	if (arg.objFirstNo < 0)								arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)				arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
																arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_VBN				oc_vbn;
	oc_vbn.Open(arg.objID);

	if (string(oc_vbn.m_Password) != arg.Password)
		return BXE_VBN_AccessDenied;

	OC_BannerProfile	oc_banner_profile;
	key_arr				ka;
	identifier_arr		ChangedBannerProfiles;

	oc_banner_profile.SetIndex_VBN_Allowed_ObjectState();
	ka += (byte)oc_vbn.m_No;
	ka += true;
	ka += (byte)OBJ_STATE_CHANGED;

	oc_banner_profile.GetClassIdList(ChangedBannerProfiles, &ka);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<ChangedBannerProfiles.Size()); i++)
	{
		oc_banner_profile.Open(ChangedBannerProfiles[i]);
		arg.objIDs.Add(ChangedBannerProfiles[i]);
		arg.objNames.Add(oc_banner_profile.m_Name);
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
