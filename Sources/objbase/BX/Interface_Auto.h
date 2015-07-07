/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Auto.h                                          []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Прототипы интерфейсных функций для работы с базой данных. []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________[]
*/
#ifndef Interface_Auto_H
#define Interface_Auto_H




   void OBServer_BX_Counter_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_TimeStats_GetStatInfo (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Admin_GetObjectNum (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_SetFilter (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_GetFilter (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteStats_Referrer (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetAliasByID (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetIDByAlias (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Admin_SaveBXObjects (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetBriefInfo (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_TimeStats_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteStats_WhatsNew (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetStatsPassword (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_CheckStatsPassword (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetVBN (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteStats_AudienceIntersect (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_IPRecord_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_IPRecord_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_IPRecord_Check (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_IPRecord_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_TypeEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_GetLanguage (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetAudienceIntersect (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_ConceptRate_Reg_InetAudience (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_ConceptRate_Site_Visitor (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_ConceptRate_Viewer_Site (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_ConceptRate_Viewer_Inquiry (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Admin_MemoryManagerReport (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Viewer_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Viewer_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_RateStats_Site (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Security_Authorize (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Banner_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Language_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Language_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Language_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Language_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Language_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_ExtendedEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Concept_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ConceptEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_GetOwnerID (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UserEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_SiteEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_SiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_BannerEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_BannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UnallowedUserEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UnallowedSiteEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UnallowedSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UnallowedBannerEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_UnallowedBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_NewUserEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_NewSiteEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_NewSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_NewBannerEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_NewBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ChangedUserEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ChangedSiteEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ChangedSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ChangedBannerEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_VBN_ChangedBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_GetForgetPassword (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_SetForgetPassword (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_GetEmail (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_SiteEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_BannerEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_SiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_BannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_User_RegisterAsSystem (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_CopyData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteProfile_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Site_GetCounterType (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_SiteSuspiciousInfo_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_CopyData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_BannerProfile_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Banner_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Banner_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Banner_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_BX_Banner_Delete (const char * inStr, const char * outStr, void ** ppData);



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
