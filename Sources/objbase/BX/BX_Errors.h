/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'														[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Errors.h																[]
[] Date:            26.07.99                                                  []
[] Author:          Alex Vershinin															[]
[] Description:     Ошибки BX-функций.														[]
[] Last Modified:																					[]
[]____________________________________________________________________________[]
*/
#ifndef BX_Errors_H
#define BX_Errors_H

enum BX_RESULT
{
	BX_OK = 0,

	BXE_BadAdminPassword,

	BXE_NoLanguages,
	BXE_Language_InvalidObjectID,
	BXE_Language_New_InvalidLanguageNameList,
	BXE_Language_New_InvalidLanguageTransList,
	BXE_Concept_InvalidObjectID,
	BXE_Concept_New_InvalidParentID,
	BXE_Concept_New_InvalidNameList,
	BXE_Concept_New_InvalidDescriptionList,
	BXE_Concept_New_RootAlreadyExists,
	BXE_Concept_New_InvalidTypeInfo,
	BXE_VBN_New_PasswordVoid,
	BXE_VBN_New_AccessDenied,
	BXE_VBN_New_InvalidObjectID,
	BXE_VBN_GetData_InvalidObjectID,
	BXE_VBN_GetOwnerID_InvalidObjectID,
	BXE_VBN_GetOwnerID_AccessDenied,
	BXE_VBN_Delete_AccessDenied,
	BXE_VBN_Delete_InvalidObjectID,
	BXE_VBN_InvalidObjectID,
	BXE_VBN_AccessDenied,
	BXE_VBN_RangeTooLarge,

	BXE_IPRecord_InvalidID,
	BXE_IPRecord_InvalidIP,

// FILE: BX_Objects.cpp
	BXE_Viewer_GetData_InvalidViewerID,
	BXE_User_New_LoginAlreadyExists,
	BXE_User_New_BadPasswordConfirm,
	BXE_User_New_InvalidEmail,
	BXE_User_New_InvalidVBN,
	BXE_User_New_PasswordTooShort,
	BXE_User_New_LoginTooShort,
	BXE_User_GetData_InvalidVBN,
	BXE_User_GetData_LoginNotFound,
	BXE_User_GetData_PasswordIncorrect,
	BXE_User_GetData_InvalidUserID,
	BXE_User_PutData_InvalidUserID,
	BXE_User_Delete_InvalidUserID,
	BXE_User_Delete_SystemUser,
	BXE_User_SiteEnumerate_InvalidObjectID,
	BXE_User_BannerEnumerate_InvalidObjectID,
	BXE_User_SiteProfileEnumerate_InvalidObjectID,
	BXE_User_BannerProfileEnumerate_InvalidObjectID,
 	BXE_User_RegisterAsSystem_InvalidObjectID,
	BXE_User_AccessDenied,

	BXE_SiteProfile_New_InvalidUserID,
	BXE_SiteProfile_New_InvalidProfileID,
	BXE_SiteProfile_CopyData_InvalidProfileID,
	BXE_SiteProfile_CopyData_AccessDenied,
	BXE_SiteProfile_GetData_InvalidProfileID,
	BXE_SiteProfile_PutData_InvalidProfileID,
	BXE_SiteProfile_Delete_InvalidProfileID,
	BXE_SiteProfile_Delete_AccessDenied,
	BXE_Site_New_InvalidOwnerID,
	BXE_Site_New_InvalidSourceID,
	BXE_Site_GetData_InvalidSiteID,
	BXE_Site_PutData_InvalidSiteID,
	BXE_Site_PutData_ProfileAccessDenied,
	BXE_Site_Delete_InvalidSiteID,
	BXE_Site_GetCounterType_InvalidSiteID,
	BXE_SiteSuspiciousInfo_GetData_InvalidSiteID,
	BXE_Site_GetAudienceIntersect_InvalidSiteID,
	BXE_BannerProfile_New_InvalidUserID,
	BXE_BannerProfile_CopyData_InvalidProfileID,
	BXE_BannerProfile_CopyData_AccessDenied,
	BXE_BannerProfile_GetData_InvalidProfileID,
	BXE_BannerProfile_PutData_InvalidProfileID,
	BXE_BannerProfile_Delete_InvalidProfileID,
	BXE_BannerProfile_Delete_AccessDenied,
	BXE_Banner_New_InvalidOwnerID,
	BXE_Banner_New_InvalidFileSize,
	BXE_Banner_GetData_InvalidBannerID,
	BXE_Banner_PutData_InvalidBannerID,
	BXE_Banner_PutData_ProfileAccessDenied,
	BXE_Banner_Delete_InvalidBannerID,

// FILE: BX_Common.cpp

// FILE: BX_Events.cpp
	BXE_ClickEvent_New_InvalidSiteID,
	BXE_ClickEvent_New_InvalidBannerID,
	BXE_ShowEvent_New_InvalidSiteID,

// FILE: BX_Stats.cpp
	BXE_RateStats_InvalidVBN,
	BXE_RateStats_InvalidKeyIndex,
	BXE_SiteStats_InvalidSiteID,
	BXE_SiteStats_InvalidSitePassword,

// FILE: BX_TimeStats.cpp
	BXE_TimeStats_GetData_InvalidRange,
	BXE_TimeStats_GetData_InvalidOutputFormat,
	BXE_TimeStats_GetData_InvalidTZOffset,
	BXE_TimeStats_GetData_InvalidObjectID,
	BXE_TimeStats_GetData_AccessDenied,
	BXE_TimeStats_GetData_InvalidCounterName,
	BXE_TimeStats_GetData_InvalidCounterID,

	
	BX_SYSTEM_ERROR = -1									// Сработал ASSERT
};


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/