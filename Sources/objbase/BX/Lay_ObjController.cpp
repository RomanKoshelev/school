/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjController.cpp                                     []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Controlers for database objects                           []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/

#define USES_OC_ALL
#define USES_string_h
#define USES_key_arr_h
#define USES_EventMonitor_h
#define USES_FileDriver_h
#define USES_File_h
#define USES_ObjDriver_h

#include "Lay_ObjController.h"


// ===============================================================================
// Viewer

// Конструктор по умолчанию
OC_Viewer::OC_Viewer ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Viewer::OC_Viewer  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Viewer::OC_Viewer  (const OC_Viewer& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Viewer::~OC_Viewer ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Viewer& OC_Viewer::operator= (const OC_Viewer& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Viewer& OC_Viewer::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Viewer::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Viewer;
   m_Reference._init              (classID, 1, &coPtr, &OD_Viewer::d_Reference              );
   m_Name._init                   (classID, 2, &coPtr, &OD_Viewer::d_Name                   );
   m_Email._init                  (classID, 3, &coPtr, &OD_Viewer::d_Email                  );
   m_UserAgent._init              (classID, 4, &coPtr, &OD_Viewer::d_UserAgent              );
   m_Anonymous._init              (classID, 5, &coPtr, &OD_Viewer::d_Anonymous              );
   m_TotalShows._init             (classID, 6, &coPtr, &OD_Viewer::d_TotalShows             );
   m_TotalClicks._init            (classID, 7, &coPtr, &OD_Viewer::d_TotalClicks            );
   m_IPAddress._init              (classID, 8, &coPtr, &OD_Viewer::d_IPAddress              );
   m_Referrer._init               (classID, 9, &coPtr, &OD_Viewer::d_Referrer               );
   m_IPAddressHash._init          (classID, 10, &coPtr, &OD_Viewer::d_IPAddressHash          );
   m_CRA_Site._init               (classID, 11, &coPtr, &OD_Viewer::d_CRA_Site               );
   m_CRN_Site._init               (classID, 12, &coPtr, &OD_Viewer::d_CRN_Site               );
   m_CRN_Site_Update._init        (classID, 13, &coPtr, &OD_Viewer::d_CRN_Site_Update        );
   m_CRA_Click._init              (classID, 14, &coPtr, &OD_Viewer::d_CRA_Click              );
   m_CRN_Click._init              (classID, 15, &coPtr, &OD_Viewer::d_CRN_Click              );
   m_Group._init                  (classID, 16, &coPtr, &OD_Viewer::d_Group                  );
   m_TZOffset._init               (classID, 17, &coPtr, &OD_Viewer::d_TZOffset               );
   m_CreationTime._init           (classID, 18, &coPtr, &OD_Viewer::d_CreationTime           );
   m_LastVisitTime._init          (classID, 19, &coPtr, &OD_Viewer::d_LastVisitTime          );
   m_Site._init                   (classID, 20, &coPtr, &OD_Viewer::d_Site                   );
   m_Site_LastHit._init           (classID, 21, &coPtr, &OD_Viewer::d_Site_LastHit           );
   m_Site_Hits._init              (classID, 22, &coPtr, &OD_Viewer::d_Site_Hits              );
   m_Site_LastHost._init          (classID, 23, &coPtr, &OD_Viewer::d_Site_LastHost          );
   m_Site_Hosts._init             (classID, 24, &coPtr, &OD_Viewer::d_Site_Hosts             );
   m_TotalHosts._init             (classID, 25, &coPtr, &OD_Viewer::d_TotalHosts             );
   m_Site_Votings._init           (classID, 26, &coPtr, &OD_Viewer::d_Site_Votings           );
   m_Site_VoteDayNo._init         (classID, 27, &coPtr, &OD_Viewer::d_Site_VoteDayNo         );
   m_CRA_Inquiry._init            (classID, 28, &coPtr, &OD_Viewer::d_CRA_Inquiry            );
   m_CRN_Inquiry._init            (classID, 29, &coPtr, &OD_Viewer::d_CRN_Inquiry            );
   m_Site_SessionLastSiteID._init (classID, 30, &coPtr, &OD_Viewer::d_Site_SessionLastSiteID );
   m_Banner._init                 (classID, 31, &coPtr, &OD_Viewer::d_Banner                 );
   m_Banner_LastViewed._init      (classID, 32, &coPtr, &OD_Viewer::d_Banner_LastViewed      );
   m_Banner_ShowClick._init       (classID, 33, &coPtr, &OD_Viewer::d_Banner_ShowClick       );
   m_BannerClickTime._init        (classID, 34, &coPtr, &OD_Viewer::d_BannerClickTime        );
   m_BannerClickID._init          (classID, 35, &coPtr, &OD_Viewer::d_BannerClickID          );
   m_BannerClickSiteID._init      (classID, 36, &coPtr, &OD_Viewer::d_BannerClickSiteID      );
   m_BannerClickHitCount._init    (classID, 37, &coPtr, &OD_Viewer::d_BannerClickHitCount    );
   m_BannerClickSessionTime._init (classID, 38, &coPtr, &OD_Viewer::d_BannerClickSessionTime );
   m_ReloadNum._init              (classID, 39, &coPtr, &OD_Viewer::d_ReloadNum              );
   m_AveReloadTime._init          (classID, 40, &coPtr, &OD_Viewer::d_AveReloadTime          );
   m_TagID._init                  (classID, 41, &coPtr, &OD_Viewer::d_TagID                  );
   m_TagInt._init                 (classID, 42, &coPtr, &OD_Viewer::d_TagInt                 );
   m_TagBool._init                (classID, 43, &coPtr, &OD_Viewer::d_TagBool                );
   m_ReservedID._init             (classID, 44, &coPtr, &OD_Viewer::d_ReservedID             );
   m_ReservedInt._init            (classID, 45, &coPtr, &OD_Viewer::d_ReservedInt            );
   m_ReservedString._init         (classID, 46, &coPtr, &OD_Viewer::d_ReservedString         );
   m_CacheTime._init              (classID, 47, &coPtr, &OD_Viewer::d_CacheTime              );
}


// Копирование данных из другого контроллера
void OC_Viewer::CopyDataFrom (OC_Viewer& from)
{
   m_Reference              = from.m_Reference;
   m_Name                   = from.m_Name;
   m_Email                  = from.m_Email;
   m_UserAgent              = from.m_UserAgent;
   m_Anonymous              = from.m_Anonymous;
   m_TotalShows             = from.m_TotalShows;
   m_TotalClicks            = from.m_TotalClicks;
   m_IPAddress              = from.m_IPAddress;
   m_Referrer               = from.m_Referrer;
   m_IPAddressHash          = from.m_IPAddressHash;
   m_CRA_Site               = from.m_CRA_Site;
   m_CRN_Site               = from.m_CRN_Site;
   m_CRN_Site_Update        = from.m_CRN_Site_Update;
   m_CRA_Click              = from.m_CRA_Click;
   m_CRN_Click              = from.m_CRN_Click;
   m_Group                  = from.m_Group;
   m_TZOffset               = from.m_TZOffset;
   m_CreationTime           = from.m_CreationTime;
   m_LastVisitTime          = from.m_LastVisitTime;
   m_Site                   = from.m_Site;
   m_Site_LastHit           = from.m_Site_LastHit;
   m_Site_Hits              = from.m_Site_Hits;
   m_Site_LastHost          = from.m_Site_LastHost;
   m_Site_Hosts             = from.m_Site_Hosts;
   m_TotalHosts             = from.m_TotalHosts;
   m_Site_Votings           = from.m_Site_Votings;
   m_Site_VoteDayNo         = from.m_Site_VoteDayNo;
   m_CRA_Inquiry            = from.m_CRA_Inquiry;
   m_CRN_Inquiry            = from.m_CRN_Inquiry;
   m_Site_SessionLastSiteID = from.m_Site_SessionLastSiteID;
   m_Banner                 = from.m_Banner;
   m_Banner_LastViewed      = from.m_Banner_LastViewed;
   m_Banner_ShowClick       = from.m_Banner_ShowClick;
   m_BannerClickTime        = from.m_BannerClickTime;
   m_BannerClickID          = from.m_BannerClickID;
   m_BannerClickSiteID      = from.m_BannerClickSiteID;
   m_BannerClickHitCount    = from.m_BannerClickHitCount;
   m_BannerClickSessionTime = from.m_BannerClickSessionTime;
   m_ReloadNum              = from.m_ReloadNum;
   m_AveReloadTime          = from.m_AveReloadTime;
   m_TagID                  = from.m_TagID;
   m_TagInt                 = from.m_TagInt;
   m_TagBool                = from.m_TagBool;
   m_ReservedID             = from.m_ReservedID;
   m_ReservedInt            = from.m_ReservedInt;
   m_ReservedString         = from.m_ReservedString;
   m_CacheTime              = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Viewer::CopyDataTo (OC_Viewer& to)
{
   to.m_Reference              = m_Reference;
   to.m_Name                   = m_Name;
   to.m_Email                  = m_Email;
   to.m_UserAgent              = m_UserAgent;
   to.m_Anonymous              = m_Anonymous;
   to.m_TotalShows             = m_TotalShows;
   to.m_TotalClicks            = m_TotalClicks;
   to.m_IPAddress              = m_IPAddress;
   to.m_Referrer               = m_Referrer;
   to.m_IPAddressHash          = m_IPAddressHash;
   to.m_CRA_Site               = m_CRA_Site;
   to.m_CRN_Site               = m_CRN_Site;
   to.m_CRN_Site_Update        = m_CRN_Site_Update;
   to.m_CRA_Click              = m_CRA_Click;
   to.m_CRN_Click              = m_CRN_Click;
   to.m_Group                  = m_Group;
   to.m_TZOffset               = m_TZOffset;
   to.m_CreationTime           = m_CreationTime;
   to.m_LastVisitTime          = m_LastVisitTime;
   to.m_Site                   = m_Site;
   to.m_Site_LastHit           = m_Site_LastHit;
   to.m_Site_Hits              = m_Site_Hits;
   to.m_Site_LastHost          = m_Site_LastHost;
   to.m_Site_Hosts             = m_Site_Hosts;
   to.m_TotalHosts             = m_TotalHosts;
   to.m_Site_Votings           = m_Site_Votings;
   to.m_Site_VoteDayNo         = m_Site_VoteDayNo;
   to.m_CRA_Inquiry            = m_CRA_Inquiry;
   to.m_CRN_Inquiry            = m_CRN_Inquiry;
   to.m_Site_SessionLastSiteID = m_Site_SessionLastSiteID;
   to.m_Banner                 = m_Banner;
   to.m_Banner_LastViewed      = m_Banner_LastViewed;
   to.m_Banner_ShowClick       = m_Banner_ShowClick;
   to.m_BannerClickTime        = m_BannerClickTime;
   to.m_BannerClickID          = m_BannerClickID;
   to.m_BannerClickSiteID      = m_BannerClickSiteID;
   to.m_BannerClickHitCount    = m_BannerClickHitCount;
   to.m_BannerClickSessionTime = m_BannerClickSessionTime;
   to.m_ReloadNum              = m_ReloadNum;
   to.m_AveReloadTime          = m_AveReloadTime;
   to.m_TagID                  = m_TagID;
   to.m_TagInt                 = m_TagInt;
   to.m_TagBool                = m_TagBool;
   to.m_ReservedID             = m_ReservedID;
   to.m_ReservedInt            = m_ReservedInt;
   to.m_ReservedString         = m_ReservedString;
   to.m_CacheTime              = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Viewer&  OC_Viewer::operator << (OC_Viewer& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Viewer&  OC_Viewer::operator >> (OC_Viewer& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// ViewerGroup

// Конструктор по умолчанию
OC_ViewerGroup::OC_ViewerGroup ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_ViewerGroup::OC_ViewerGroup  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_ViewerGroup::OC_ViewerGroup  (const OC_ViewerGroup& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_ViewerGroup::~OC_ViewerGroup ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_ViewerGroup& OC_ViewerGroup::operator= (const OC_ViewerGroup& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_ViewerGroup& OC_ViewerGroup::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_ViewerGroup::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_ViewerGroup;
   m_ConceptStats._init   (classID, 1, &coPtr, &OD_ViewerGroup::d_ConceptStats   );
   m_Viewer._init         (classID, 2, &coPtr, &OD_ViewerGroup::d_Viewer         );
   m_TagID._init          (classID, 3, &coPtr, &OD_ViewerGroup::d_TagID          );
   m_TagInt._init         (classID, 4, &coPtr, &OD_ViewerGroup::d_TagInt         );
   m_TagBool._init        (classID, 5, &coPtr, &OD_ViewerGroup::d_TagBool        );
   m_ReservedID._init     (classID, 6, &coPtr, &OD_ViewerGroup::d_ReservedID     );
   m_ReservedInt._init    (classID, 7, &coPtr, &OD_ViewerGroup::d_ReservedInt    );
   m_ReservedString._init (classID, 8, &coPtr, &OD_ViewerGroup::d_ReservedString );
   m_CacheTime._init      (classID, 9, &coPtr, &OD_ViewerGroup::d_CacheTime      );
}


// Копирование данных из другого контроллера
void OC_ViewerGroup::CopyDataFrom (OC_ViewerGroup& from)
{
   m_ConceptStats   = from.m_ConceptStats;
   m_Viewer         = from.m_Viewer;
   m_TagID          = from.m_TagID;
   m_TagInt         = from.m_TagInt;
   m_TagBool        = from.m_TagBool;
   m_ReservedID     = from.m_ReservedID;
   m_ReservedInt    = from.m_ReservedInt;
   m_ReservedString = from.m_ReservedString;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_ViewerGroup::CopyDataTo (OC_ViewerGroup& to)
{
   to.m_ConceptStats   = m_ConceptStats;
   to.m_Viewer         = m_Viewer;
   to.m_TagID          = m_TagID;
   to.m_TagInt         = m_TagInt;
   to.m_TagBool        = m_TagBool;
   to.m_ReservedID     = m_ReservedID;
   to.m_ReservedInt    = m_ReservedInt;
   to.m_ReservedString = m_ReservedString;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_ViewerGroup&  OC_ViewerGroup::operator << (OC_ViewerGroup& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_ViewerGroup&  OC_ViewerGroup::operator >> (OC_ViewerGroup& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// User

// Конструктор по умолчанию
OC_User::OC_User ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_User::OC_User  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_User::OC_User  (const OC_User& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_User::~OC_User ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_User& OC_User::operator= (const OC_User& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_User& OC_User::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_User::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_User;
   m_Login._init               (classID, 1, &coPtr, &OD_User::d_Login               );
   m_Password._init            (classID, 2, &coPtr, &OD_User::d_Password            );
   m_ForgetPassword._init      (classID, 3, &coPtr, &OD_User::d_ForgetPassword      );
   m_FullName._init            (classID, 4, &coPtr, &OD_User::d_FullName            );
   m_InterfaceLanguage._init   (classID, 5, &coPtr, &OD_User::d_InterfaceLanguage   );
   m_InterfaceType._init       (classID, 6, &coPtr, &OD_User::d_InterfaceType       );
   m_CreationTime._init        (classID, 7, &coPtr, &OD_User::d_CreationTime        );
   m_VBN._init                 (classID, 8, &coPtr, &OD_User::d_VBN                 );
   m_ba_Concept._init          (classID, 9, &coPtr, &OD_User::d_ba_Concept          );
   m_eba_Concept._init         (classID, 10, &coPtr, &OD_User::d_eba_Concept         );
   m_Email._init               (classID, 11, &coPtr, &OD_User::d_Email               );
   m_Phone._init               (classID, 12, &coPtr, &OD_User::d_Phone               );
   m_Fax._init                 (classID, 13, &coPtr, &OD_User::d_Fax                 );
   m_Address._init             (classID, 14, &coPtr, &OD_User::d_Address             );
   m_URL._init                 (classID, 15, &coPtr, &OD_User::d_URL                 );
   m_Comment._init             (classID, 16, &coPtr, &OD_User::d_Comment             );
   m_TZOffset._init            (classID, 17, &coPtr, &OD_User::d_TZOffset            );
   m_NotifyFreq._init          (classID, 18, &coPtr, &OD_User::d_NotifyFreq          );
   m_NotifyHTML._init          (classID, 19, &coPtr, &OD_User::d_NotifyHTML          );
   m_NotifyDepth._init         (classID, 20, &coPtr, &OD_User::d_NotifyDepth         );
   m_Site._init                (classID, 21, &coPtr, &OD_User::d_Site                );
   m_SiteProfile._init         (classID, 22, &coPtr, &OD_User::d_SiteProfile         );
   m_Banner._init              (classID, 23, &coPtr, &OD_User::d_Banner              );
   m_BannerProfile._init       (classID, 24, &coPtr, &OD_User::d_BannerProfile       );
   m_ShowsLeft._init           (classID, 25, &coPtr, &OD_User::d_ShowsLeft           );
   m_ClicksLeft._init          (classID, 26, &coPtr, &OD_User::d_ClicksLeft          );
   m_TradeStats._init          (classID, 27, &coPtr, &OD_User::d_TradeStats          );
   m_Allowed._init             (classID, 28, &coPtr, &OD_User::d_Allowed             );
   m_ObjectState._init         (classID, 29, &coPtr, &OD_User::d_ObjectState         );
   m_ba_ModeratorComment._init (classID, 30, &coPtr, &OD_User::d_ba_ModeratorComment );
   m_TagID._init               (classID, 31, &coPtr, &OD_User::d_TagID               );
   m_TagInt._init              (classID, 32, &coPtr, &OD_User::d_TagInt              );
   m_TagBool._init             (classID, 33, &coPtr, &OD_User::d_TagBool             );
   m_ReservedID._init          (classID, 34, &coPtr, &OD_User::d_ReservedID          );
   m_ReservedInt._init         (classID, 35, &coPtr, &OD_User::d_ReservedInt         );
   m_ReservedString._init      (classID, 36, &coPtr, &OD_User::d_ReservedString      );
   m_CacheTime._init           (classID, 37, &coPtr, &OD_User::d_CacheTime           );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_User::CopyDataFrom (OC_User& from)
{
   m_Login               = from.m_Login;
   m_Password            = from.m_Password;
   m_ForgetPassword      = from.m_ForgetPassword;
   m_FullName            = from.m_FullName;
   m_InterfaceLanguage   = from.m_InterfaceLanguage;
   m_InterfaceType       = from.m_InterfaceType;
   m_CreationTime        = from.m_CreationTime;
   m_VBN                 = from.m_VBN;
   m_ba_Concept          = from.m_ba_Concept;
   m_eba_Concept         = from.m_eba_Concept;
   m_Email               = from.m_Email;
   m_Phone               = from.m_Phone;
   m_Fax                 = from.m_Fax;
   m_Address             = from.m_Address;
   m_URL                 = from.m_URL;
   m_Comment             = from.m_Comment;
   m_TZOffset            = from.m_TZOffset;
   m_NotifyFreq          = from.m_NotifyFreq;
   m_NotifyHTML          = from.m_NotifyHTML;
   m_NotifyDepth         = from.m_NotifyDepth;
   m_Site                = from.m_Site;
   m_SiteProfile         = from.m_SiteProfile;
   m_Banner              = from.m_Banner;
   m_BannerProfile       = from.m_BannerProfile;
   m_ShowsLeft           = from.m_ShowsLeft;
   m_ClicksLeft          = from.m_ClicksLeft;
   m_TradeStats          = from.m_TradeStats;
   m_Allowed             = from.m_Allowed;
   m_ObjectState         = from.m_ObjectState;
   m_ba_ModeratorComment = from.m_ba_ModeratorComment;
   m_TagID               = from.m_TagID;
   m_TagInt              = from.m_TagInt;
   m_TagBool             = from.m_TagBool;
   m_ReservedID          = from.m_ReservedID;
   m_ReservedInt         = from.m_ReservedInt;
   m_ReservedString      = from.m_ReservedString;
   m_CacheTime           = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_User::CopyDataTo (OC_User& to)
{
   to.m_Login               = m_Login;
   to.m_Password            = m_Password;
   to.m_ForgetPassword      = m_ForgetPassword;
   to.m_FullName            = m_FullName;
   to.m_InterfaceLanguage   = m_InterfaceLanguage;
   to.m_InterfaceType       = m_InterfaceType;
   to.m_CreationTime        = m_CreationTime;
   to.m_VBN                 = m_VBN;
   to.m_ba_Concept          = m_ba_Concept;
   to.m_eba_Concept         = m_eba_Concept;
   to.m_Email               = m_Email;
   to.m_Phone               = m_Phone;
   to.m_Fax                 = m_Fax;
   to.m_Address             = m_Address;
   to.m_URL                 = m_URL;
   to.m_Comment             = m_Comment;
   to.m_TZOffset            = m_TZOffset;
   to.m_NotifyFreq          = m_NotifyFreq;
   to.m_NotifyHTML          = m_NotifyHTML;
   to.m_NotifyDepth         = m_NotifyDepth;
   to.m_Site                = m_Site;
   to.m_SiteProfile         = m_SiteProfile;
   to.m_Banner              = m_Banner;
   to.m_BannerProfile       = m_BannerProfile;
   to.m_ShowsLeft           = m_ShowsLeft;
   to.m_ClicksLeft          = m_ClicksLeft;
   to.m_TradeStats          = m_TradeStats;
   to.m_Allowed             = m_Allowed;
   to.m_ObjectState         = m_ObjectState;
   to.m_ba_ModeratorComment = m_ba_ModeratorComment;
   to.m_TagID               = m_TagID;
   to.m_TagInt              = m_TagInt;
   to.m_TagBool             = m_TagBool;
   to.m_ReservedID          = m_ReservedID;
   to.m_ReservedInt         = m_ReservedInt;
   to.m_ReservedString      = m_ReservedString;
   to.m_CacheTime           = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_User&  OC_User::operator << (OC_User& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_User&  OC_User::operator >> (OC_User& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_User::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_VBN_Allowed_ObjectState ();
              return oldIndex;
      case 1: SetIndex_VBN_Login ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_User::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_User::SetIndex_VBN_Allowed_ObjectState ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_byte; 
};

// Установить текущий индекс по набору полей
void OC_User::SetIndex_VBN_Login ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// TradeStats

// Конструктор по умолчанию
OC_TradeStats::OC_TradeStats ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_TradeStats::OC_TradeStats  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_TradeStats::OC_TradeStats  (const OC_TradeStats& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_TradeStats::~OC_TradeStats ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_TradeStats& OC_TradeStats::operator= (const OC_TradeStats& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_TradeStats& OC_TradeStats::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_TradeStats::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_TradeStats;
   m_SoldShowDates._init      (classID, 1, &coPtr, &OD_TradeStats::d_SoldShowDates      );
   m_SoldShowAmounts._init    (classID, 2, &coPtr, &OD_TradeStats::d_SoldShowAmounts    );
   m_SoldShowBuyer._init      (classID, 3, &coPtr, &OD_TradeStats::d_SoldShowBuyer      );
   m_BoughtShowDates._init    (classID, 4, &coPtr, &OD_TradeStats::d_BoughtShowDates    );
   m_BoughtShowAmounts._init  (classID, 5, &coPtr, &OD_TradeStats::d_BoughtShowAmounts  );
   m_BoughtShowSeller._init   (classID, 6, &coPtr, &OD_TradeStats::d_BoughtShowSeller   );
   m_SoldClickDates._init     (classID, 7, &coPtr, &OD_TradeStats::d_SoldClickDates     );
   m_SoldClickAmounts._init   (classID, 8, &coPtr, &OD_TradeStats::d_SoldClickAmounts   );
   m_SoldClickBuyer._init     (classID, 9, &coPtr, &OD_TradeStats::d_SoldClickBuyer     );
   m_BoughtClickDates._init   (classID, 10, &coPtr, &OD_TradeStats::d_BoughtClickDates   );
   m_BoughtClickAmounts._init (classID, 11, &coPtr, &OD_TradeStats::d_BoughtClickAmounts );
   m_BoughtClickSeller._init  (classID, 12, &coPtr, &OD_TradeStats::d_BoughtClickSeller  );
   m_TagID._init              (classID, 13, &coPtr, &OD_TradeStats::d_TagID              );
   m_TagInt._init             (classID, 14, &coPtr, &OD_TradeStats::d_TagInt             );
   m_TagBool._init            (classID, 15, &coPtr, &OD_TradeStats::d_TagBool            );
   m_ReservedID._init         (classID, 16, &coPtr, &OD_TradeStats::d_ReservedID         );
   m_ReservedInt._init        (classID, 17, &coPtr, &OD_TradeStats::d_ReservedInt        );
   m_ReservedString._init     (classID, 18, &coPtr, &OD_TradeStats::d_ReservedString     );
   m_CacheTime._init          (classID, 19, &coPtr, &OD_TradeStats::d_CacheTime          );
}


// Копирование данных из другого контроллера
void OC_TradeStats::CopyDataFrom (OC_TradeStats& from)
{
   m_SoldShowDates      = from.m_SoldShowDates;
   m_SoldShowAmounts    = from.m_SoldShowAmounts;
   m_SoldShowBuyer      = from.m_SoldShowBuyer;
   m_BoughtShowDates    = from.m_BoughtShowDates;
   m_BoughtShowAmounts  = from.m_BoughtShowAmounts;
   m_BoughtShowSeller   = from.m_BoughtShowSeller;
   m_SoldClickDates     = from.m_SoldClickDates;
   m_SoldClickAmounts   = from.m_SoldClickAmounts;
   m_SoldClickBuyer     = from.m_SoldClickBuyer;
   m_BoughtClickDates   = from.m_BoughtClickDates;
   m_BoughtClickAmounts = from.m_BoughtClickAmounts;
   m_BoughtClickSeller  = from.m_BoughtClickSeller;
   m_TagID              = from.m_TagID;
   m_TagInt             = from.m_TagInt;
   m_TagBool            = from.m_TagBool;
   m_ReservedID         = from.m_ReservedID;
   m_ReservedInt        = from.m_ReservedInt;
   m_ReservedString     = from.m_ReservedString;
   m_CacheTime          = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_TradeStats::CopyDataTo (OC_TradeStats& to)
{
   to.m_SoldShowDates      = m_SoldShowDates;
   to.m_SoldShowAmounts    = m_SoldShowAmounts;
   to.m_SoldShowBuyer      = m_SoldShowBuyer;
   to.m_BoughtShowDates    = m_BoughtShowDates;
   to.m_BoughtShowAmounts  = m_BoughtShowAmounts;
   to.m_BoughtShowSeller   = m_BoughtShowSeller;
   to.m_SoldClickDates     = m_SoldClickDates;
   to.m_SoldClickAmounts   = m_SoldClickAmounts;
   to.m_SoldClickBuyer     = m_SoldClickBuyer;
   to.m_BoughtClickDates   = m_BoughtClickDates;
   to.m_BoughtClickAmounts = m_BoughtClickAmounts;
   to.m_BoughtClickSeller  = m_BoughtClickSeller;
   to.m_TagID              = m_TagID;
   to.m_TagInt             = m_TagInt;
   to.m_TagBool            = m_TagBool;
   to.m_ReservedID         = m_ReservedID;
   to.m_ReservedInt        = m_ReservedInt;
   to.m_ReservedString     = m_ReservedString;
   to.m_CacheTime          = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_TradeStats&  OC_TradeStats::operator << (OC_TradeStats& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_TradeStats&  OC_TradeStats::operator >> (OC_TradeStats& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// Banner

// Конструктор по умолчанию
OC_Banner::OC_Banner ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Banner::OC_Banner  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Banner::OC_Banner  (const OC_Banner& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Banner::~OC_Banner ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Banner& OC_Banner::operator= (const OC_Banner& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Banner& OC_Banner::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Banner::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Banner;
   m_OwnerID._init             (classID, 1, &coPtr, &OD_Banner::d_OwnerID             );
   m_FileName._init            (classID, 2, &coPtr, &OD_Banner::d_FileName            );
   m_FileSize._init            (classID, 3, &coPtr, &OD_Banner::d_FileSize            );
   m_UploadNo._init            (classID, 4, &coPtr, &OD_Banner::d_UploadNo            );
   m_CreationTime._init        (classID, 5, &coPtr, &OD_Banner::d_CreationTime        );
   m_VBN._init                 (classID, 6, &coPtr, &OD_Banner::d_VBN                 );
   m_Description._init         (classID, 7, &coPtr, &OD_Banner::d_Description         );
   m_State._init               (classID, 8, &coPtr, &OD_Banner::d_State               );
   m_Profile._init             (classID, 9, &coPtr, &OD_Banner::d_Profile             );
   m_SiteAnnounce._init        (classID, 10, &coPtr, &OD_Banner::d_SiteAnnounce        );
   m_ba_Concept._init          (classID, 11, &coPtr, &OD_Banner::d_ba_Concept          );
   m_eba_Concept._init         (classID, 12, &coPtr, &OD_Banner::d_eba_Concept         );
   m_TotalShows._init          (classID, 13, &coPtr, &OD_Banner::d_TotalShows          );
   m_TotalClicks._init         (classID, 14, &coPtr, &OD_Banner::d_TotalClicks         );
   m_Allowed._init             (classID, 15, &coPtr, &OD_Banner::d_Allowed             );
   m_ObjectState._init         (classID, 16, &coPtr, &OD_Banner::d_ObjectState         );
   m_ba_ModeratorComment._init (classID, 17, &coPtr, &OD_Banner::d_ba_ModeratorComment );
   m_TagID._init               (classID, 18, &coPtr, &OD_Banner::d_TagID               );
   m_TagInt._init              (classID, 19, &coPtr, &OD_Banner::d_TagInt              );
   m_TagBool._init             (classID, 20, &coPtr, &OD_Banner::d_TagBool             );
   m_ReservedID._init          (classID, 21, &coPtr, &OD_Banner::d_ReservedID          );
   m_ReservedInt._init         (classID, 22, &coPtr, &OD_Banner::d_ReservedInt         );
   m_ReservedString._init      (classID, 23, &coPtr, &OD_Banner::d_ReservedString      );
   m_CacheTime._init           (classID, 24, &coPtr, &OD_Banner::d_CacheTime           );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Banner::CopyDataFrom (OC_Banner& from)
{
   m_OwnerID             = from.m_OwnerID;
   m_FileName            = from.m_FileName;
   m_FileSize            = from.m_FileSize;
   m_UploadNo            = from.m_UploadNo;
   m_CreationTime        = from.m_CreationTime;
   m_VBN                 = from.m_VBN;
   m_Description         = from.m_Description;
   m_State               = from.m_State;
   m_Profile             = from.m_Profile;
   m_SiteAnnounce        = from.m_SiteAnnounce;
   m_ba_Concept          = from.m_ba_Concept;
   m_eba_Concept         = from.m_eba_Concept;
   m_TotalShows          = from.m_TotalShows;
   m_TotalClicks         = from.m_TotalClicks;
   m_Allowed             = from.m_Allowed;
   m_ObjectState         = from.m_ObjectState;
   m_ba_ModeratorComment = from.m_ba_ModeratorComment;
   m_TagID               = from.m_TagID;
   m_TagInt              = from.m_TagInt;
   m_TagBool             = from.m_TagBool;
   m_ReservedID          = from.m_ReservedID;
   m_ReservedInt         = from.m_ReservedInt;
   m_ReservedString      = from.m_ReservedString;
   m_CacheTime           = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Banner::CopyDataTo (OC_Banner& to)
{
   to.m_OwnerID             = m_OwnerID;
   to.m_FileName            = m_FileName;
   to.m_FileSize            = m_FileSize;
   to.m_UploadNo            = m_UploadNo;
   to.m_CreationTime        = m_CreationTime;
   to.m_VBN                 = m_VBN;
   to.m_Description         = m_Description;
   to.m_State               = m_State;
   to.m_Profile             = m_Profile;
   to.m_SiteAnnounce        = m_SiteAnnounce;
   to.m_ba_Concept          = m_ba_Concept;
   to.m_eba_Concept         = m_eba_Concept;
   to.m_TotalShows          = m_TotalShows;
   to.m_TotalClicks         = m_TotalClicks;
   to.m_Allowed             = m_Allowed;
   to.m_ObjectState         = m_ObjectState;
   to.m_ba_ModeratorComment = m_ba_ModeratorComment;
   to.m_TagID               = m_TagID;
   to.m_TagInt              = m_TagInt;
   to.m_TagBool             = m_TagBool;
   to.m_ReservedID          = m_ReservedID;
   to.m_ReservedInt         = m_ReservedInt;
   to.m_ReservedString      = m_ReservedString;
   to.m_CacheTime           = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Banner&  OC_Banner::operator << (OC_Banner& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Banner&  OC_Banner::operator >> (OC_Banner& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Banner::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_VBN_Allowed_ObjectState ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Banner::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_Banner::SetIndex_VBN_Allowed_ObjectState ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_byte; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// BannerProfile

// Конструктор по умолчанию
OC_BannerProfile::OC_BannerProfile ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_BannerProfile::OC_BannerProfile  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_BannerProfile::OC_BannerProfile  (const OC_BannerProfile& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_BannerProfile::~OC_BannerProfile ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_BannerProfile& OC_BannerProfile::operator= (const OC_BannerProfile& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_BannerProfile& OC_BannerProfile::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_BannerProfile::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_BannerProfile;
   m_Name._init                    (classID, 1, &coPtr, &OD_BannerProfile::d_Name                    );
   m_VBN._init                     (classID, 2, &coPtr, &OD_BannerProfile::d_VBN                     );
   m_LastModified._init            (classID, 3, &coPtr, &OD_BannerProfile::d_LastModified            );
   m_OwnerID._init                 (classID, 4, &coPtr, &OD_BannerProfile::d_OwnerID                 );
   m_HREF._init                    (classID, 5, &coPtr, &OD_BannerProfile::d_HREF                    );
   m_Commercial._init              (classID, 6, &coPtr, &OD_BannerProfile::d_Commercial              );
   m_BannerType._init              (classID, 7, &coPtr, &OD_BannerProfile::d_BannerType              );
   m_SiteAnnounce._init            (classID, 8, &coPtr, &OD_BannerProfile::d_SiteAnnounce            );
   m_Banner._init                  (classID, 9, &coPtr, &OD_BannerProfile::d_Banner                  );
   m_ba_Concept._init              (classID, 10, &coPtr, &OD_BannerProfile::d_ba_Concept              );
   m_eba_Concept._init             (classID, 11, &coPtr, &OD_BannerProfile::d_eba_Concept             );
   m_State._init                   (classID, 12, &coPtr, &OD_BannerProfile::d_State                   );
   m_AltText._init                 (classID, 13, &coPtr, &OD_BannerProfile::d_AltText                 );
   m_ba_SiteConceptInclude._init   (classID, 14, &coPtr, &OD_BannerProfile::d_ba_SiteConceptInclude   );
   m_ba_SiteConceptExclude._init   (classID, 15, &coPtr, &OD_BannerProfile::d_ba_SiteConceptExclude   );
   m_eba_SiteConcept._init         (classID, 16, &coPtr, &OD_BannerProfile::d_eba_SiteConcept         );
   m_SiteInclude._init             (classID, 17, &coPtr, &OD_BannerProfile::d_SiteInclude             );
   m_SiteExclude._init             (classID, 18, &coPtr, &OD_BannerProfile::d_SiteExclude             );
   m_ViewerIPEnable._init          (classID, 19, &coPtr, &OD_BannerProfile::d_ViewerIPEnable          );
   m_ViewerIPDisable._init         (classID, 20, &coPtr, &OD_BannerProfile::d_ViewerIPDisable         );
   m_ba_ViewerConceptInclude._init (classID, 21, &coPtr, &OD_BannerProfile::d_ba_ViewerConceptInclude );
   m_ba_ViewerConceptExclude._init (classID, 22, &coPtr, &OD_BannerProfile::d_ba_ViewerConceptExclude );
   m_eba_ViewerConcept._init       (classID, 23, &coPtr, &OD_BannerProfile::d_eba_ViewerConcept       );
   m_UseLocalTime._init            (classID, 24, &coPtr, &OD_BannerProfile::d_UseLocalTime            );
   m_ScheduleTZOffset._init        (classID, 25, &coPtr, &OD_BannerProfile::d_ScheduleTZOffset        );
   m_ShowIfLocalUnknown._init      (classID, 26, &coPtr, &OD_BannerProfile::d_ShowIfLocalUnknown      );
   m_ba_Schedule._init             (classID, 27, &coPtr, &OD_BannerProfile::d_ba_Schedule             );
   m_AutoOn._init                  (classID, 28, &coPtr, &OD_BannerProfile::d_AutoOn                  );
   m_AutoOff._init                 (classID, 29, &coPtr, &OD_BannerProfile::d_AutoOff                 );
   m_RepeatCount._init             (classID, 30, &coPtr, &OD_BannerProfile::d_RepeatCount             );
   m_RepeatTime._init              (classID, 31, &coPtr, &OD_BannerProfile::d_RepeatTime              );
   m_SiteTarget_SiteID._init       (classID, 32, &coPtr, &OD_BannerProfile::d_SiteTarget_SiteID       );
   m_SiteTarget_ShowRate._init     (classID, 33, &coPtr, &OD_BannerProfile::d_SiteTarget_ShowRate     );
   m_SiteTarget_ClickRate._init    (classID, 34, &coPtr, &OD_BannerProfile::d_SiteTarget_ClickRate    );
   m_SiteTarget_ViewRate._init     (classID, 35, &coPtr, &OD_BannerProfile::d_SiteTarget_ViewRate     );
   m_ViewerConceptRate._init       (classID, 36, &coPtr, &OD_BannerProfile::d_ViewerConceptRate       );
   m_ShowNumRate._init             (classID, 37, &coPtr, &OD_BannerProfile::d_ShowNumRate             );
   m_ClickNumRate._init            (classID, 38, &coPtr, &OD_BannerProfile::d_ClickNumRate            );
   m_HitNumRate._init              (classID, 39, &coPtr, &OD_BannerProfile::d_HitNumRate              );
   m_SessionTimeRate._init         (classID, 40, &coPtr, &OD_BannerProfile::d_SessionTimeRate         );
   m_CountTypeByShows._init        (classID, 41, &coPtr, &OD_BannerProfile::d_CountTypeByShows        );
   m_MaxDailyClicks._init          (classID, 42, &coPtr, &OD_BannerProfile::d_MaxDailyClicks          );
   m_MaxDailyShows._init           (classID, 43, &coPtr, &OD_BannerProfile::d_MaxDailyShows           );
   m_MaxDailyShowsChangeTime._init (classID, 44, &coPtr, &OD_BannerProfile::d_MaxDailyShowsChangeTime );
   m_TotalShows._init              (classID, 45, &coPtr, &OD_BannerProfile::d_TotalShows              );
   m_TotalClicks._init             (classID, 46, &coPtr, &OD_BannerProfile::d_TotalClicks             );
   m_SessionEvents._init           (classID, 47, &coPtr, &OD_BannerProfile::d_SessionEvents           );
   m_Priority._init                (classID, 48, &coPtr, &OD_BannerProfile::d_Priority                );
   m_Allowed._init                 (classID, 49, &coPtr, &OD_BannerProfile::d_Allowed                 );
   m_ObjectState._init             (classID, 50, &coPtr, &OD_BannerProfile::d_ObjectState             );
   m_ba_ModeratorComment._init     (classID, 51, &coPtr, &OD_BannerProfile::d_ba_ModeratorComment     );
   m_TagID._init                   (classID, 52, &coPtr, &OD_BannerProfile::d_TagID                   );
   m_TagInt._init                  (classID, 53, &coPtr, &OD_BannerProfile::d_TagInt                  );
   m_TagBool._init                 (classID, 54, &coPtr, &OD_BannerProfile::d_TagBool                 );
   m_ReservedID._init              (classID, 55, &coPtr, &OD_BannerProfile::d_ReservedID              );
   m_ReservedInt._init             (classID, 56, &coPtr, &OD_BannerProfile::d_ReservedInt             );
   m_ReservedString._init          (classID, 57, &coPtr, &OD_BannerProfile::d_ReservedString          );
   m_CacheTime._init               (classID, 58, &coPtr, &OD_BannerProfile::d_CacheTime               );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_BannerProfile::CopyDataFrom (OC_BannerProfile& from)
{
   m_Name                    = from.m_Name;
   m_VBN                     = from.m_VBN;
   m_LastModified            = from.m_LastModified;
   m_OwnerID                 = from.m_OwnerID;
   m_HREF                    = from.m_HREF;
   m_Commercial              = from.m_Commercial;
   m_BannerType              = from.m_BannerType;
   m_SiteAnnounce            = from.m_SiteAnnounce;
   m_Banner                  = from.m_Banner;
   m_ba_Concept              = from.m_ba_Concept;
   m_eba_Concept             = from.m_eba_Concept;
   m_State                   = from.m_State;
   m_AltText                 = from.m_AltText;
   m_ba_SiteConceptInclude   = from.m_ba_SiteConceptInclude;
   m_ba_SiteConceptExclude   = from.m_ba_SiteConceptExclude;
   m_eba_SiteConcept         = from.m_eba_SiteConcept;
   m_SiteInclude             = from.m_SiteInclude;
   m_SiteExclude             = from.m_SiteExclude;
   m_ViewerIPEnable          = from.m_ViewerIPEnable;
   m_ViewerIPDisable         = from.m_ViewerIPDisable;
   m_ba_ViewerConceptInclude = from.m_ba_ViewerConceptInclude;
   m_ba_ViewerConceptExclude = from.m_ba_ViewerConceptExclude;
   m_eba_ViewerConcept       = from.m_eba_ViewerConcept;
   m_UseLocalTime            = from.m_UseLocalTime;
   m_ScheduleTZOffset        = from.m_ScheduleTZOffset;
   m_ShowIfLocalUnknown      = from.m_ShowIfLocalUnknown;
   m_ba_Schedule             = from.m_ba_Schedule;
   m_AutoOn                  = from.m_AutoOn;
   m_AutoOff                 = from.m_AutoOff;
   m_RepeatCount             = from.m_RepeatCount;
   m_RepeatTime              = from.m_RepeatTime;
   m_SiteTarget_SiteID       = from.m_SiteTarget_SiteID;
   m_SiteTarget_ShowRate     = from.m_SiteTarget_ShowRate;
   m_SiteTarget_ClickRate    = from.m_SiteTarget_ClickRate;
   m_SiteTarget_ViewRate     = from.m_SiteTarget_ViewRate;
   m_ViewerConceptRate       = from.m_ViewerConceptRate;
   m_ShowNumRate             = from.m_ShowNumRate;
   m_ClickNumRate            = from.m_ClickNumRate;
   m_HitNumRate              = from.m_HitNumRate;
   m_SessionTimeRate         = from.m_SessionTimeRate;
   m_CountTypeByShows        = from.m_CountTypeByShows;
   m_MaxDailyClicks          = from.m_MaxDailyClicks;
   m_MaxDailyShows           = from.m_MaxDailyShows;
   m_MaxDailyShowsChangeTime = from.m_MaxDailyShowsChangeTime;
   m_TotalShows              = from.m_TotalShows;
   m_TotalClicks             = from.m_TotalClicks;
   m_SessionEvents           = from.m_SessionEvents;
   m_Priority                = from.m_Priority;
   m_Allowed                 = from.m_Allowed;
   m_ObjectState             = from.m_ObjectState;
   m_ba_ModeratorComment     = from.m_ba_ModeratorComment;
   m_TagID                   = from.m_TagID;
   m_TagInt                  = from.m_TagInt;
   m_TagBool                 = from.m_TagBool;
   m_ReservedID              = from.m_ReservedID;
   m_ReservedInt             = from.m_ReservedInt;
   m_ReservedString          = from.m_ReservedString;
   m_CacheTime               = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_BannerProfile::CopyDataTo (OC_BannerProfile& to)
{
   to.m_Name                    = m_Name;
   to.m_VBN                     = m_VBN;
   to.m_LastModified            = m_LastModified;
   to.m_OwnerID                 = m_OwnerID;
   to.m_HREF                    = m_HREF;
   to.m_Commercial              = m_Commercial;
   to.m_BannerType              = m_BannerType;
   to.m_SiteAnnounce            = m_SiteAnnounce;
   to.m_Banner                  = m_Banner;
   to.m_ba_Concept              = m_ba_Concept;
   to.m_eba_Concept             = m_eba_Concept;
   to.m_State                   = m_State;
   to.m_AltText                 = m_AltText;
   to.m_ba_SiteConceptInclude   = m_ba_SiteConceptInclude;
   to.m_ba_SiteConceptExclude   = m_ba_SiteConceptExclude;
   to.m_eba_SiteConcept         = m_eba_SiteConcept;
   to.m_SiteInclude             = m_SiteInclude;
   to.m_SiteExclude             = m_SiteExclude;
   to.m_ViewerIPEnable          = m_ViewerIPEnable;
   to.m_ViewerIPDisable         = m_ViewerIPDisable;
   to.m_ba_ViewerConceptInclude = m_ba_ViewerConceptInclude;
   to.m_ba_ViewerConceptExclude = m_ba_ViewerConceptExclude;
   to.m_eba_ViewerConcept       = m_eba_ViewerConcept;
   to.m_UseLocalTime            = m_UseLocalTime;
   to.m_ScheduleTZOffset        = m_ScheduleTZOffset;
   to.m_ShowIfLocalUnknown      = m_ShowIfLocalUnknown;
   to.m_ba_Schedule             = m_ba_Schedule;
   to.m_AutoOn                  = m_AutoOn;
   to.m_AutoOff                 = m_AutoOff;
   to.m_RepeatCount             = m_RepeatCount;
   to.m_RepeatTime              = m_RepeatTime;
   to.m_SiteTarget_SiteID       = m_SiteTarget_SiteID;
   to.m_SiteTarget_ShowRate     = m_SiteTarget_ShowRate;
   to.m_SiteTarget_ClickRate    = m_SiteTarget_ClickRate;
   to.m_SiteTarget_ViewRate     = m_SiteTarget_ViewRate;
   to.m_ViewerConceptRate       = m_ViewerConceptRate;
   to.m_ShowNumRate             = m_ShowNumRate;
   to.m_ClickNumRate            = m_ClickNumRate;
   to.m_HitNumRate              = m_HitNumRate;
   to.m_SessionTimeRate         = m_SessionTimeRate;
   to.m_CountTypeByShows        = m_CountTypeByShows;
   to.m_MaxDailyClicks          = m_MaxDailyClicks;
   to.m_MaxDailyShows           = m_MaxDailyShows;
   to.m_MaxDailyShowsChangeTime = m_MaxDailyShowsChangeTime;
   to.m_TotalShows              = m_TotalShows;
   to.m_TotalClicks             = m_TotalClicks;
   to.m_SessionEvents           = m_SessionEvents;
   to.m_Priority                = m_Priority;
   to.m_Allowed                 = m_Allowed;
   to.m_ObjectState             = m_ObjectState;
   to.m_ba_ModeratorComment     = m_ba_ModeratorComment;
   to.m_TagID                   = m_TagID;
   to.m_TagInt                  = m_TagInt;
   to.m_TagBool                 = m_TagBool;
   to.m_ReservedID              = m_ReservedID;
   to.m_ReservedInt             = m_ReservedInt;
   to.m_ReservedString          = m_ReservedString;
   to.m_CacheTime               = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_BannerProfile&  OC_BannerProfile::operator << (OC_BannerProfile& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_BannerProfile&  OC_BannerProfile::operator >> (OC_BannerProfile& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_BannerProfile::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_VBN_Allowed_ObjectState ();
              return oldIndex;
      case 1: SetIndex_VBN_State_Allowed_BannerType_Priority ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_BannerProfile::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_BannerProfile::SetIndex_VBN_Allowed_ObjectState ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_byte; 
};

// Установить текущий индекс по набору полей
void OC_BannerProfile::SetIndex_VBN_State_Allowed_BannerType_Priority ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 5; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_bool; 
   curIndexInfo.m_keyType[3] = (byte)FT_int; 
   curIndexInfo.m_keyType[4] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Page

// Конструктор по умолчанию
OC_Page::OC_Page ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Page::OC_Page  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Page::OC_Page  (const OC_Page& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Page::~OC_Page ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Page& OC_Page::operator= (const OC_Page& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Page& OC_Page::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Page::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Page;
   m_Site._init                   (classID, 1, &coPtr, &OD_Page::d_Site                   );
   m_No._init                     (classID, 2, &coPtr, &OD_Page::d_No                     );
   m_URL._init                    (classID, 3, &coPtr, &OD_Page::d_URL                    );
   m_ba_Concept._init             (classID, 4, &coPtr, &OD_Page::d_ba_Concept             );
   m_eba_Concept._init            (classID, 5, &coPtr, &OD_Page::d_eba_Concept            );
   m_pba_Concept._init            (classID, 6, &coPtr, &OD_Page::d_pba_Concept            );
   m_CounterType._init            (classID, 7, &coPtr, &OD_Page::d_CounterType            );
   m_ConceptSet._init             (classID, 8, &coPtr, &OD_Page::d_ConceptSet             );
   m_TimeStats._init              (classID, 9, &coPtr, &OD_Page::d_TimeStats              );
   m_TimeStatsType._init          (classID, 10, &coPtr, &OD_Page::d_TimeStatsType          );
   m_CRA_Visitor._init            (classID, 11, &coPtr, &OD_Page::d_CRA_Visitor            );
   m_CRN_Visitor._init            (classID, 12, &coPtr, &OD_Page::d_CRN_Visitor            );
   m_CRN_Visitor_Update._init     (classID, 13, &coPtr, &OD_Page::d_CRN_Visitor_Update     );
   m_CRN_VisitorIncr._init        (classID, 14, &coPtr, &OD_Page::d_CRN_VisitorIncr        );
   m_CRN_VisitorIncr_Update._init (classID, 15, &coPtr, &OD_Page::d_CRN_VisitorIncr_Update );
   m_Referrer._init               (classID, 16, &coPtr, &OD_Page::d_Referrer               );
   m_ReferrerCount._init          (classID, 17, &coPtr, &OD_Page::d_ReferrerCount          );
   m_TagID._init                  (classID, 18, &coPtr, &OD_Page::d_TagID                  );
   m_TagInt._init                 (classID, 19, &coPtr, &OD_Page::d_TagInt                 );
   m_TagBool._init                (classID, 20, &coPtr, &OD_Page::d_TagBool                );
   m_ReservedID._init             (classID, 21, &coPtr, &OD_Page::d_ReservedID             );
   m_ReservedInt._init            (classID, 22, &coPtr, &OD_Page::d_ReservedInt            );
   m_ReservedString._init         (classID, 23, &coPtr, &OD_Page::d_ReservedString         );
   m_CacheTime._init              (classID, 24, &coPtr, &OD_Page::d_CacheTime              );
}


// Копирование данных из другого контроллера
void OC_Page::CopyDataFrom (OC_Page& from)
{
   m_Site                   = from.m_Site;
   m_No                     = from.m_No;
   m_URL                    = from.m_URL;
   m_ba_Concept             = from.m_ba_Concept;
   m_eba_Concept            = from.m_eba_Concept;
   m_pba_Concept            = from.m_pba_Concept;
   m_CounterType            = from.m_CounterType;
   m_ConceptSet             = from.m_ConceptSet;
   m_TimeStats              = from.m_TimeStats;
   m_TimeStatsType          = from.m_TimeStatsType;
   m_CRA_Visitor            = from.m_CRA_Visitor;
   m_CRN_Visitor            = from.m_CRN_Visitor;
   m_CRN_Visitor_Update     = from.m_CRN_Visitor_Update;
   m_CRN_VisitorIncr        = from.m_CRN_VisitorIncr;
   m_CRN_VisitorIncr_Update = from.m_CRN_VisitorIncr_Update;
   m_Referrer               = from.m_Referrer;
   m_ReferrerCount          = from.m_ReferrerCount;
   m_TagID                  = from.m_TagID;
   m_TagInt                 = from.m_TagInt;
   m_TagBool                = from.m_TagBool;
   m_ReservedID             = from.m_ReservedID;
   m_ReservedInt            = from.m_ReservedInt;
   m_ReservedString         = from.m_ReservedString;
   m_CacheTime              = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Page::CopyDataTo (OC_Page& to)
{
   to.m_Site                   = m_Site;
   to.m_No                     = m_No;
   to.m_URL                    = m_URL;
   to.m_ba_Concept             = m_ba_Concept;
   to.m_eba_Concept            = m_eba_Concept;
   to.m_pba_Concept            = m_pba_Concept;
   to.m_CounterType            = m_CounterType;
   to.m_ConceptSet             = m_ConceptSet;
   to.m_TimeStats              = m_TimeStats;
   to.m_TimeStatsType          = m_TimeStatsType;
   to.m_CRA_Visitor            = m_CRA_Visitor;
   to.m_CRN_Visitor            = m_CRN_Visitor;
   to.m_CRN_Visitor_Update     = m_CRN_Visitor_Update;
   to.m_CRN_VisitorIncr        = m_CRN_VisitorIncr;
   to.m_CRN_VisitorIncr_Update = m_CRN_VisitorIncr_Update;
   to.m_Referrer               = m_Referrer;
   to.m_ReferrerCount          = m_ReferrerCount;
   to.m_TagID                  = m_TagID;
   to.m_TagInt                 = m_TagInt;
   to.m_TagBool                = m_TagBool;
   to.m_ReservedID             = m_ReservedID;
   to.m_ReservedInt            = m_ReservedInt;
   to.m_ReservedString         = m_ReservedString;
   to.m_CacheTime              = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Page&  OC_Page::operator << (OC_Page& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Page&  OC_Page::operator >> (OC_Page& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// Site

// Конструктор по умолчанию
OC_Site::OC_Site ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Site::OC_Site  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Site::OC_Site  (const OC_Site& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Site::~OC_Site ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Site& OC_Site::operator= (const OC_Site& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Site& OC_Site::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Site::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Site;
   m_OwnerID._init                     (classID, 1, &coPtr, &OD_Site::d_OwnerID                     );
   m_VBN._init                         (classID, 2, &coPtr, &OD_Site::d_VBN                         );
   m_CreationTime._init                (classID, 3, &coPtr, &OD_Site::d_CreationTime                );
   m_Alias._init                       (classID, 4, &coPtr, &OD_Site::d_Alias                       );
   m_Name._init                        (classID, 5, &coPtr, &OD_Site::d_Name                        );
   m_Description._init                 (classID, 6, &coPtr, &OD_Site::d_Description                 );
   m_Announce._init                    (classID, 7, &coPtr, &OD_Site::d_Announce                    );
   m_URL._init                         (classID, 8, &coPtr, &OD_Site::d_URL                         );
   m_CounterType._init                 (classID, 9, &coPtr, &OD_Site::d_CounterType                 );
   m_RateMySite._init                  (classID, 10, &coPtr, &OD_Site::d_RateMySite                  );
   m_RateStatsViewPassword._init       (classID, 11, &coPtr, &OD_Site::d_RateStatsViewPassword       );
   m_ShowAudience._init                (classID, 12, &coPtr, &OD_Site::d_ShowAudience                );
   m_ShowAudienceOffTime._init         (classID, 13, &coPtr, &OD_Site::d_ShowAudienceOffTime         );
   m_Profile._init                     (classID, 14, &coPtr, &OD_Site::d_Profile                     );
   m_Keyword._init                     (classID, 15, &coPtr, &OD_Site::d_Keyword                     );
   m_MirrorInclude._init               (classID, 16, &coPtr, &OD_Site::d_MirrorInclude               );
   m_MirrorExclude._init               (classID, 17, &coPtr, &OD_Site::d_MirrorExclude               );
   m_MirrorSubstr._init                (classID, 18, &coPtr, &OD_Site::d_MirrorSubstr                );
   m_IgnoredIP._init                   (classID, 19, &coPtr, &OD_Site::d_IgnoredIP                   );
   m_IgnoredViewerID._init             (classID, 20, &coPtr, &OD_Site::d_IgnoredViewerID             );
   m_ba_Concept._init                  (classID, 21, &coPtr, &OD_Site::d_ba_Concept                  );
   m_pba_Concept._init                 (classID, 22, &coPtr, &OD_Site::d_pba_Concept                 );
   m_eba_Concept._init                 (classID, 23, &coPtr, &OD_Site::d_eba_Concept                 );
   m_CRN_Self._init                    (classID, 24, &coPtr, &OD_Site::d_CRN_Self                    );
   m_Page._init                        (classID, 25, &coPtr, &OD_Site::d_Page                        );
   m_PageName._init                    (classID, 26, &coPtr, &OD_Site::d_PageName                    );
   m_PageNo._init                      (classID, 27, &coPtr, &OD_Site::d_PageNo                      );
   m_AdBannerProfile._init             (classID, 28, &coPtr, &OD_Site::d_AdBannerProfile             );
   m_SuspiciousInfo._init              (classID, 29, &coPtr, &OD_Site::d_SuspiciousInfo              );
   m_CRA_Visitor._init                 (classID, 30, &coPtr, &OD_Site::d_CRA_Visitor                 );
   m_CRN_Visitor._init                 (classID, 31, &coPtr, &OD_Site::d_CRN_Visitor                 );
   m_CRN_Visitor_Update._init          (classID, 32, &coPtr, &OD_Site::d_CRN_Visitor_Update          );
   m_CRA_Inquiry._init                 (classID, 33, &coPtr, &OD_Site::d_CRA_Inquiry                 );
   m_CRN_Inquiry._init                 (classID, 34, &coPtr, &OD_Site::d_CRN_Inquiry                 );
   m_CRN_VisitorIncr._init             (classID, 35, &coPtr, &OD_Site::d_CRN_VisitorIncr             );
   m_CRN_VisitorIncr_Update._init      (classID, 36, &coPtr, &OD_Site::d_CRN_VisitorIncr_Update      );
   m_Audience_SiteID._init             (classID, 37, &coPtr, &OD_Site::d_Audience_SiteID             );
   m_Audience_Viewers._init            (classID, 38, &coPtr, &OD_Site::d_Audience_Viewers            );
   m_Audience_Hosts._init              (classID, 39, &coPtr, &OD_Site::d_Audience_Hosts              );
   m_Audience_SiteIDInclude._init      (classID, 40, &coPtr, &OD_Site::d_Audience_SiteIDInclude      );
   m_ActiveViewersID._init             (classID, 41, &coPtr, &OD_Site::d_ActiveViewersID             );
   m_ActiveViewersHits._init           (classID, 42, &coPtr, &OD_Site::d_ActiveViewersHits           );
   m_RecentPointer._init               (classID, 43, &coPtr, &OD_Site::d_RecentPointer               );
   m_RecentVisitor._init               (classID, 44, &coPtr, &OD_Site::d_RecentVisitor               );
   m_RecentReferrer._init              (classID, 45, &coPtr, &OD_Site::d_RecentReferrer              );
   m_RecentTimeStamp._init             (classID, 46, &coPtr, &OD_Site::d_RecentTimeStamp             );
   m_Referrer._init                    (classID, 47, &coPtr, &OD_Site::d_Referrer                    );
   m_ReferrerCount._init               (classID, 48, &coPtr, &OD_Site::d_ReferrerCount               );
   m_Referrer_LastReset._init          (classID, 49, &coPtr, &OD_Site::d_Referrer_LastReset          );
   m_DailyReferrerStats._init          (classID, 50, &coPtr, &OD_Site::d_DailyReferrerStats          );
   m_DailyReferrerTimeStamp._init      (classID, 51, &coPtr, &OD_Site::d_DailyReferrerTimeStamp      );
   m_SearchWordsInfo._init             (classID, 52, &coPtr, &OD_Site::d_SearchWordsInfo             );
   m_Inquire._init                     (classID, 53, &coPtr, &OD_Site::d_Inquire                     );
   m_InquiredVisitorNum._init          (classID, 54, &coPtr, &OD_Site::d_InquiredVisitorNum          );
   m_SessionResetTime._init            (classID, 55, &coPtr, &OD_Site::d_SessionResetTime            );
   m_ReturnNumRate._init               (classID, 56, &coPtr, &OD_Site::d_ReturnNumRate               );
   m_ShowNumRate._init                 (classID, 57, &coPtr, &OD_Site::d_ShowNumRate                 );
   m_LastVisitTime._init               (classID, 58, &coPtr, &OD_Site::d_LastVisitTime               );
   m_LastUpdateTime._init              (classID, 59, &coPtr, &OD_Site::d_LastUpdateTime              );
   m_Loads._init                       (classID, 60, &coPtr, &OD_Site::d_Loads                       );
   m_Visitors._init                    (classID, 61, &coPtr, &OD_Site::d_Visitors                    );
   m_Hosts._init                       (classID, 62, &coPtr, &OD_Site::d_Hosts                       );
   m_Shows._init                       (classID, 63, &coPtr, &OD_Site::d_Shows                       );
   m_Clicks._init                      (classID, 64, &coPtr, &OD_Site::d_Clicks                      );
   m_Clicks_Local._init                (classID, 65, &coPtr, &OD_Site::d_Clicks_Local                );
   m_Hits._init                        (classID, 66, &coPtr, &OD_Site::d_Hits                        );
   m_Hits_Local._init                  (classID, 67, &coPtr, &OD_Site::d_Hits_Local                  );
   m_AnonymousHits._init               (classID, 68, &coPtr, &OD_Site::d_AnonymousHits               );
   m_SuspiciousHits._init              (classID, 69, &coPtr, &OD_Site::d_SuspiciousHits              );
   m_SessionTime._init                 (classID, 70, &coPtr, &OD_Site::d_SessionTime                 );
   m_SessionTime_Local._init           (classID, 71, &coPtr, &OD_Site::d_SessionTime_Local           );
   m_SessionNum._init                  (classID, 72, &coPtr, &OD_Site::d_SessionNum                  );
   m_Total_Loads._init                 (classID, 73, &coPtr, &OD_Site::d_Total_Loads                 );
   m_Total_Hosts._init                 (classID, 74, &coPtr, &OD_Site::d_Total_Hosts                 );
   m_Total_Hits._init                  (classID, 75, &coPtr, &OD_Site::d_Total_Hits                  );
   m_Total_AnonymousHits._init         (classID, 76, &coPtr, &OD_Site::d_Total_AnonymousHits         );
   m_Total_AnonymousHits_Prc._init     (classID, 77, &coPtr, &OD_Site::d_Total_AnonymousHits_Prc     );
   m_Total_SuspiciousHits_Prc._init    (classID, 78, &coPtr, &OD_Site::d_Total_SuspiciousHits_Prc    );
   m_Total_Visitors._init              (classID, 79, &coPtr, &OD_Site::d_Total_Visitors              );
   m_Total_VisitorReturns._init        (classID, 80, &coPtr, &OD_Site::d_Total_VisitorReturns        );
   m_Total_VisitorReturns_Prc._init    (classID, 81, &coPtr, &OD_Site::d_Total_VisitorReturns_Prc    );
   m_Total_SessionNum._init            (classID, 82, &coPtr, &OD_Site::d_Total_SessionNum            );
   m_Total_AveSessionTime._init        (classID, 83, &coPtr, &OD_Site::d_Total_AveSessionTime        );
   m_Total_AveReloadTime._init         (classID, 84, &coPtr, &OD_Site::d_Total_AveReloadTime         );
   m_Total_AveReloadNum._init          (classID, 85, &coPtr, &OD_Site::d_Total_AveReloadNum          );
   m_Total_Shows._init                 (classID, 86, &coPtr, &OD_Site::d_Total_Shows                 );
   m_Total_Clicks._init                (classID, 87, &coPtr, &OD_Site::d_Total_Clicks                );
   m_Total_CTR_Prc._init               (classID, 88, &coPtr, &OD_Site::d_Total_CTR_Prc               );
   m_Total_CPH_Prc._init               (classID, 89, &coPtr, &OD_Site::d_Total_CPH_Prc               );
   m_Total_AnonymousVisitors._init     (classID, 90, &coPtr, &OD_Site::d_Total_AnonymousVisitors     );
   m_Total_AnonymousVisitors_Prc._init (classID, 91, &coPtr, &OD_Site::d_Total_AnonymousVisitors_Prc );
   m_Total_VisitorExperience._init     (classID, 92, &coPtr, &OD_Site::d_Total_VisitorExperience     );
   m_Ave_VisitorExperience._init       (classID, 93, &coPtr, &OD_Site::d_Ave_VisitorExperience       );
   m_OnlineVisitors._init              (classID, 94, &coPtr, &OD_Site::d_OnlineVisitors              );
   m_Total_MouseOver._init             (classID, 95, &coPtr, &OD_Site::d_Total_MouseOver             );
   m_Total_Votes._init                 (classID, 96, &coPtr, &OD_Site::d_Total_Votes                 );
   m_Total_Votes_Sum._init             (classID, 97, &coPtr, &OD_Site::d_Total_Votes_Sum             );
   m_Total_Votes_Ave._init             (classID, 98, &coPtr, &OD_Site::d_Total_Votes_Ave             );
   m_LM_Loads._init                    (classID, 99, &coPtr, &OD_Site::d_LM_Loads                    );
   m_LM_Hosts._init                    (classID, 100, &coPtr, &OD_Site::d_LM_Hosts                    );
   m_LM_Hits._init                     (classID, 101, &coPtr, &OD_Site::d_LM_Hits                     );
   m_LM_AnonymousHits._init            (classID, 102, &coPtr, &OD_Site::d_LM_AnonymousHits            );
   m_LM_AnonymousHits_Prc._init        (classID, 103, &coPtr, &OD_Site::d_LM_AnonymousHits_Prc        );
   m_LM_SuspiciousHits_Prc._init       (classID, 104, &coPtr, &OD_Site::d_LM_SuspiciousHits_Prc       );
   m_LM_Visitors._init                 (classID, 105, &coPtr, &OD_Site::d_LM_Visitors                 );
   m_LM_VisitorReturns._init           (classID, 106, &coPtr, &OD_Site::d_LM_VisitorReturns           );
   m_LM_VisitorReturns_Prc._init       (classID, 107, &coPtr, &OD_Site::d_LM_VisitorReturns_Prc       );
   m_LM_SessionNum._init               (classID, 108, &coPtr, &OD_Site::d_LM_SessionNum               );
   m_LM_AveSessionTime._init           (classID, 109, &coPtr, &OD_Site::d_LM_AveSessionTime           );
   m_LM_AveReloadTime._init            (classID, 110, &coPtr, &OD_Site::d_LM_AveReloadTime            );
   m_LM_AveReloadNum._init             (classID, 111, &coPtr, &OD_Site::d_LM_AveReloadNum             );
   m_LM_Shows._init                    (classID, 112, &coPtr, &OD_Site::d_LM_Shows                    );
   m_LM_Clicks._init                   (classID, 113, &coPtr, &OD_Site::d_LM_Clicks                   );
   m_LM_CTR_Prc._init                  (classID, 114, &coPtr, &OD_Site::d_LM_CTR_Prc                  );
   m_LM_CPH_Prc._init                  (classID, 115, &coPtr, &OD_Site::d_LM_CPH_Prc                  );
   m_LW_Loads._init                    (classID, 116, &coPtr, &OD_Site::d_LW_Loads                    );
   m_LW_Hosts._init                    (classID, 117, &coPtr, &OD_Site::d_LW_Hosts                    );
   m_LW_Hits._init                     (classID, 118, &coPtr, &OD_Site::d_LW_Hits                     );
   m_LW_AnonymousHits._init            (classID, 119, &coPtr, &OD_Site::d_LW_AnonymousHits            );
   m_LW_AnonymousHits_Prc._init        (classID, 120, &coPtr, &OD_Site::d_LW_AnonymousHits_Prc        );
   m_LW_SuspiciousHits_Prc._init       (classID, 121, &coPtr, &OD_Site::d_LW_SuspiciousHits_Prc       );
   m_LW_Visitors._init                 (classID, 122, &coPtr, &OD_Site::d_LW_Visitors                 );
   m_LW_VisitorReturns._init           (classID, 123, &coPtr, &OD_Site::d_LW_VisitorReturns           );
   m_LW_VisitorReturns_Prc._init       (classID, 124, &coPtr, &OD_Site::d_LW_VisitorReturns_Prc       );
   m_LW_SessionNum._init               (classID, 125, &coPtr, &OD_Site::d_LW_SessionNum               );
   m_LW_AveSessionTime._init           (classID, 126, &coPtr, &OD_Site::d_LW_AveSessionTime           );
   m_LW_AveReloadTime._init            (classID, 127, &coPtr, &OD_Site::d_LW_AveReloadTime            );
   m_LW_AveReloadNum._init             (classID, 128, &coPtr, &OD_Site::d_LW_AveReloadNum             );
   m_LW_Shows._init                    (classID, 129, &coPtr, &OD_Site::d_LW_Shows                    );
   m_LW_Clicks._init                   (classID, 130, &coPtr, &OD_Site::d_LW_Clicks                   );
   m_LW_CTR_Prc._init                  (classID, 131, &coPtr, &OD_Site::d_LW_CTR_Prc                  );
   m_LW_CPH_Prc._init                  (classID, 132, &coPtr, &OD_Site::d_LW_CPH_Prc                  );
   m_LD_Loads._init                    (classID, 133, &coPtr, &OD_Site::d_LD_Loads                    );
   m_LD_Hosts._init                    (classID, 134, &coPtr, &OD_Site::d_LD_Hosts                    );
   m_LD_Hits._init                     (classID, 135, &coPtr, &OD_Site::d_LD_Hits                     );
   m_LD_AnonymousHits._init            (classID, 136, &coPtr, &OD_Site::d_LD_AnonymousHits            );
   m_LD_AnonymousHits_Prc._init        (classID, 137, &coPtr, &OD_Site::d_LD_AnonymousHits_Prc        );
   m_LD_SuspiciousHits_Prc._init       (classID, 138, &coPtr, &OD_Site::d_LD_SuspiciousHits_Prc       );
   m_LD_Visitors._init                 (classID, 139, &coPtr, &OD_Site::d_LD_Visitors                 );
   m_LD_VisitorReturns._init           (classID, 140, &coPtr, &OD_Site::d_LD_VisitorReturns           );
   m_LD_VisitorReturns_Prc._init       (classID, 141, &coPtr, &OD_Site::d_LD_VisitorReturns_Prc       );
   m_LD_SessionNum._init               (classID, 142, &coPtr, &OD_Site::d_LD_SessionNum               );
   m_LD_AveSessionTime._init           (classID, 143, &coPtr, &OD_Site::d_LD_AveSessionTime           );
   m_LD_AveReloadTime._init            (classID, 144, &coPtr, &OD_Site::d_LD_AveReloadTime            );
   m_LD_AveReloadNum._init             (classID, 145, &coPtr, &OD_Site::d_LD_AveReloadNum             );
   m_LD_Shows._init                    (classID, 146, &coPtr, &OD_Site::d_LD_Shows                    );
   m_LD_Clicks._init                   (classID, 147, &coPtr, &OD_Site::d_LD_Clicks                   );
   m_LD_CTR_Prc._init                  (classID, 148, &coPtr, &OD_Site::d_LD_CTR_Prc                  );
   m_LD_CPH_Prc._init                  (classID, 149, &coPtr, &OD_Site::d_LD_CPH_Prc                  );
   m_LH_Loads._init                    (classID, 150, &coPtr, &OD_Site::d_LH_Loads                    );
   m_LH_Hosts._init                    (classID, 151, &coPtr, &OD_Site::d_LH_Hosts                    );
   m_LH_Hits._init                     (classID, 152, &coPtr, &OD_Site::d_LH_Hits                     );
   m_LH_AnonymousHits._init            (classID, 153, &coPtr, &OD_Site::d_LH_AnonymousHits            );
   m_LH_AnonymousHits_Prc._init        (classID, 154, &coPtr, &OD_Site::d_LH_AnonymousHits_Prc        );
   m_LH_SuspiciousHits_Prc._init       (classID, 155, &coPtr, &OD_Site::d_LH_SuspiciousHits_Prc       );
   m_LH_Visitors._init                 (classID, 156, &coPtr, &OD_Site::d_LH_Visitors                 );
   m_LH_VisitorReturns._init           (classID, 157, &coPtr, &OD_Site::d_LH_VisitorReturns           );
   m_LH_VisitorReturns_Prc._init       (classID, 158, &coPtr, &OD_Site::d_LH_VisitorReturns_Prc       );
   m_LH_SessionNum._init               (classID, 159, &coPtr, &OD_Site::d_LH_SessionNum               );
   m_LH_AveSessionTime._init           (classID, 160, &coPtr, &OD_Site::d_LH_AveSessionTime           );
   m_LH_AveReloadTime._init            (classID, 161, &coPtr, &OD_Site::d_LH_AveReloadTime            );
   m_LH_AveReloadNum._init             (classID, 162, &coPtr, &OD_Site::d_LH_AveReloadNum             );
   m_LH_Shows._init                    (classID, 163, &coPtr, &OD_Site::d_LH_Shows                    );
   m_LH_Clicks._init                   (classID, 164, &coPtr, &OD_Site::d_LH_Clicks                   );
   m_LH_CTR_Prc._init                  (classID, 165, &coPtr, &OD_Site::d_LH_CTR_Prc                  );
   m_LH_CPH_Prc._init                  (classID, 166, &coPtr, &OD_Site::d_LH_CPH_Prc                  );
   m_CustomIndex1._init                (classID, 167, &coPtr, &OD_Site::d_CustomIndex1                );
   m_CustomIndex2._init                (classID, 168, &coPtr, &OD_Site::d_CustomIndex2                );
   m_CustomIndex3._init                (classID, 169, &coPtr, &OD_Site::d_CustomIndex3                );
   m_CustomIndex4._init                (classID, 170, &coPtr, &OD_Site::d_CustomIndex4                );
   m_CustomIndex5._init                (classID, 171, &coPtr, &OD_Site::d_CustomIndex5                );
   m_Allowed._init                     (classID, 172, &coPtr, &OD_Site::d_Allowed                     );
   m_ObjectState._init                 (classID, 173, &coPtr, &OD_Site::d_ObjectState                 );
   m_ba_ModeratorComment._init         (classID, 174, &coPtr, &OD_Site::d_ba_ModeratorComment         );
   m_TagID._init                       (classID, 175, &coPtr, &OD_Site::d_TagID                       );
   m_TagBool._init                     (classID, 176, &coPtr, &OD_Site::d_TagBool                     );
   m_TagInt._init                      (classID, 177, &coPtr, &OD_Site::d_TagInt                      );
   m_ReservedID._init                  (classID, 178, &coPtr, &OD_Site::d_ReservedID                  );
   m_ReservedInt._init                 (classID, 179, &coPtr, &OD_Site::d_ReservedInt                 );
   m_ReservedString._init              (classID, 180, &coPtr, &OD_Site::d_ReservedString              );
   m_RatingPlaceInfo._init             (classID, 181, &coPtr, &OD_Site::d_RatingPlaceInfo             );
   m_CacheTime._init                   (classID, 182, &coPtr, &OD_Site::d_CacheTime                   );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Site::CopyDataFrom (OC_Site& from)
{
   m_OwnerID                     = from.m_OwnerID;
   m_VBN                         = from.m_VBN;
   m_CreationTime                = from.m_CreationTime;
   m_Alias                       = from.m_Alias;
   m_Name                        = from.m_Name;
   m_Description                 = from.m_Description;
   m_Announce                    = from.m_Announce;
   m_URL                         = from.m_URL;
   m_CounterType                 = from.m_CounterType;
   m_RateMySite                  = from.m_RateMySite;
   m_RateStatsViewPassword       = from.m_RateStatsViewPassword;
   m_ShowAudience                = from.m_ShowAudience;
   m_ShowAudienceOffTime         = from.m_ShowAudienceOffTime;
   m_Profile                     = from.m_Profile;
   m_Keyword                     = from.m_Keyword;
   m_MirrorInclude               = from.m_MirrorInclude;
   m_MirrorExclude               = from.m_MirrorExclude;
   m_MirrorSubstr                = from.m_MirrorSubstr;
   m_IgnoredIP                   = from.m_IgnoredIP;
   m_IgnoredViewerID             = from.m_IgnoredViewerID;
   m_ba_Concept                  = from.m_ba_Concept;
   m_pba_Concept                 = from.m_pba_Concept;
   m_eba_Concept                 = from.m_eba_Concept;
   m_CRN_Self                    = from.m_CRN_Self;
   m_Page                        = from.m_Page;
   m_PageName                    = from.m_PageName;
   m_PageNo                      = from.m_PageNo;
   m_AdBannerProfile             = from.m_AdBannerProfile;
   m_SuspiciousInfo              = from.m_SuspiciousInfo;
   m_CRA_Visitor                 = from.m_CRA_Visitor;
   m_CRN_Visitor                 = from.m_CRN_Visitor;
   m_CRN_Visitor_Update          = from.m_CRN_Visitor_Update;
   m_CRA_Inquiry                 = from.m_CRA_Inquiry;
   m_CRN_Inquiry                 = from.m_CRN_Inquiry;
   m_CRN_VisitorIncr             = from.m_CRN_VisitorIncr;
   m_CRN_VisitorIncr_Update      = from.m_CRN_VisitorIncr_Update;
   m_Audience_SiteID             = from.m_Audience_SiteID;
   m_Audience_Viewers            = from.m_Audience_Viewers;
   m_Audience_Hosts              = from.m_Audience_Hosts;
   m_Audience_SiteIDInclude      = from.m_Audience_SiteIDInclude;
   m_ActiveViewersID             = from.m_ActiveViewersID;
   m_ActiveViewersHits           = from.m_ActiveViewersHits;
   m_RecentPointer               = from.m_RecentPointer;
   m_RecentVisitor               = from.m_RecentVisitor;
   m_RecentReferrer              = from.m_RecentReferrer;
   m_RecentTimeStamp             = from.m_RecentTimeStamp;
   m_Referrer                    = from.m_Referrer;
   m_ReferrerCount               = from.m_ReferrerCount;
   m_Referrer_LastReset          = from.m_Referrer_LastReset;
   m_DailyReferrerStats          = from.m_DailyReferrerStats;
   m_DailyReferrerTimeStamp      = from.m_DailyReferrerTimeStamp;
   m_SearchWordsInfo             = from.m_SearchWordsInfo;
   m_Inquire                     = from.m_Inquire;
   m_InquiredVisitorNum          = from.m_InquiredVisitorNum;
   m_SessionResetTime            = from.m_SessionResetTime;
   m_ReturnNumRate               = from.m_ReturnNumRate;
   m_ShowNumRate                 = from.m_ShowNumRate;
   m_LastVisitTime               = from.m_LastVisitTime;
   m_LastUpdateTime              = from.m_LastUpdateTime;
   m_Loads                       = from.m_Loads;
   m_Visitors                    = from.m_Visitors;
   m_Hosts                       = from.m_Hosts;
   m_Shows                       = from.m_Shows;
   m_Clicks                      = from.m_Clicks;
   m_Clicks_Local                = from.m_Clicks_Local;
   m_Hits                        = from.m_Hits;
   m_Hits_Local                  = from.m_Hits_Local;
   m_AnonymousHits               = from.m_AnonymousHits;
   m_SuspiciousHits              = from.m_SuspiciousHits;
   m_SessionTime                 = from.m_SessionTime;
   m_SessionTime_Local           = from.m_SessionTime_Local;
   m_SessionNum                  = from.m_SessionNum;
   m_Total_Loads                 = from.m_Total_Loads;
   m_Total_Hosts                 = from.m_Total_Hosts;
   m_Total_Hits                  = from.m_Total_Hits;
   m_Total_AnonymousHits         = from.m_Total_AnonymousHits;
   m_Total_AnonymousHits_Prc     = from.m_Total_AnonymousHits_Prc;
   m_Total_SuspiciousHits_Prc    = from.m_Total_SuspiciousHits_Prc;
   m_Total_Visitors              = from.m_Total_Visitors;
   m_Total_VisitorReturns        = from.m_Total_VisitorReturns;
   m_Total_VisitorReturns_Prc    = from.m_Total_VisitorReturns_Prc;
   m_Total_SessionNum            = from.m_Total_SessionNum;
   m_Total_AveSessionTime        = from.m_Total_AveSessionTime;
   m_Total_AveReloadTime         = from.m_Total_AveReloadTime;
   m_Total_AveReloadNum          = from.m_Total_AveReloadNum;
   m_Total_Shows                 = from.m_Total_Shows;
   m_Total_Clicks                = from.m_Total_Clicks;
   m_Total_CTR_Prc               = from.m_Total_CTR_Prc;
   m_Total_CPH_Prc               = from.m_Total_CPH_Prc;
   m_Total_AnonymousVisitors     = from.m_Total_AnonymousVisitors;
   m_Total_AnonymousVisitors_Prc = from.m_Total_AnonymousVisitors_Prc;
   m_Total_VisitorExperience     = from.m_Total_VisitorExperience;
   m_Ave_VisitorExperience       = from.m_Ave_VisitorExperience;
   m_OnlineVisitors              = from.m_OnlineVisitors;
   m_Total_MouseOver             = from.m_Total_MouseOver;
   m_Total_Votes                 = from.m_Total_Votes;
   m_Total_Votes_Sum             = from.m_Total_Votes_Sum;
   m_Total_Votes_Ave             = from.m_Total_Votes_Ave;
   m_LM_Loads                    = from.m_LM_Loads;
   m_LM_Hosts                    = from.m_LM_Hosts;
   m_LM_Hits                     = from.m_LM_Hits;
   m_LM_AnonymousHits            = from.m_LM_AnonymousHits;
   m_LM_AnonymousHits_Prc        = from.m_LM_AnonymousHits_Prc;
   m_LM_SuspiciousHits_Prc       = from.m_LM_SuspiciousHits_Prc;
   m_LM_Visitors                 = from.m_LM_Visitors;
   m_LM_VisitorReturns           = from.m_LM_VisitorReturns;
   m_LM_VisitorReturns_Prc       = from.m_LM_VisitorReturns_Prc;
   m_LM_SessionNum               = from.m_LM_SessionNum;
   m_LM_AveSessionTime           = from.m_LM_AveSessionTime;
   m_LM_AveReloadTime            = from.m_LM_AveReloadTime;
   m_LM_AveReloadNum             = from.m_LM_AveReloadNum;
   m_LM_Shows                    = from.m_LM_Shows;
   m_LM_Clicks                   = from.m_LM_Clicks;
   m_LM_CTR_Prc                  = from.m_LM_CTR_Prc;
   m_LM_CPH_Prc                  = from.m_LM_CPH_Prc;
   m_LW_Loads                    = from.m_LW_Loads;
   m_LW_Hosts                    = from.m_LW_Hosts;
   m_LW_Hits                     = from.m_LW_Hits;
   m_LW_AnonymousHits            = from.m_LW_AnonymousHits;
   m_LW_AnonymousHits_Prc        = from.m_LW_AnonymousHits_Prc;
   m_LW_SuspiciousHits_Prc       = from.m_LW_SuspiciousHits_Prc;
   m_LW_Visitors                 = from.m_LW_Visitors;
   m_LW_VisitorReturns           = from.m_LW_VisitorReturns;
   m_LW_VisitorReturns_Prc       = from.m_LW_VisitorReturns_Prc;
   m_LW_SessionNum               = from.m_LW_SessionNum;
   m_LW_AveSessionTime           = from.m_LW_AveSessionTime;
   m_LW_AveReloadTime            = from.m_LW_AveReloadTime;
   m_LW_AveReloadNum             = from.m_LW_AveReloadNum;
   m_LW_Shows                    = from.m_LW_Shows;
   m_LW_Clicks                   = from.m_LW_Clicks;
   m_LW_CTR_Prc                  = from.m_LW_CTR_Prc;
   m_LW_CPH_Prc                  = from.m_LW_CPH_Prc;
   m_LD_Loads                    = from.m_LD_Loads;
   m_LD_Hosts                    = from.m_LD_Hosts;
   m_LD_Hits                     = from.m_LD_Hits;
   m_LD_AnonymousHits            = from.m_LD_AnonymousHits;
   m_LD_AnonymousHits_Prc        = from.m_LD_AnonymousHits_Prc;
   m_LD_SuspiciousHits_Prc       = from.m_LD_SuspiciousHits_Prc;
   m_LD_Visitors                 = from.m_LD_Visitors;
   m_LD_VisitorReturns           = from.m_LD_VisitorReturns;
   m_LD_VisitorReturns_Prc       = from.m_LD_VisitorReturns_Prc;
   m_LD_SessionNum               = from.m_LD_SessionNum;
   m_LD_AveSessionTime           = from.m_LD_AveSessionTime;
   m_LD_AveReloadTime            = from.m_LD_AveReloadTime;
   m_LD_AveReloadNum             = from.m_LD_AveReloadNum;
   m_LD_Shows                    = from.m_LD_Shows;
   m_LD_Clicks                   = from.m_LD_Clicks;
   m_LD_CTR_Prc                  = from.m_LD_CTR_Prc;
   m_LD_CPH_Prc                  = from.m_LD_CPH_Prc;
   m_LH_Loads                    = from.m_LH_Loads;
   m_LH_Hosts                    = from.m_LH_Hosts;
   m_LH_Hits                     = from.m_LH_Hits;
   m_LH_AnonymousHits            = from.m_LH_AnonymousHits;
   m_LH_AnonymousHits_Prc        = from.m_LH_AnonymousHits_Prc;
   m_LH_SuspiciousHits_Prc       = from.m_LH_SuspiciousHits_Prc;
   m_LH_Visitors                 = from.m_LH_Visitors;
   m_LH_VisitorReturns           = from.m_LH_VisitorReturns;
   m_LH_VisitorReturns_Prc       = from.m_LH_VisitorReturns_Prc;
   m_LH_SessionNum               = from.m_LH_SessionNum;
   m_LH_AveSessionTime           = from.m_LH_AveSessionTime;
   m_LH_AveReloadTime            = from.m_LH_AveReloadTime;
   m_LH_AveReloadNum             = from.m_LH_AveReloadNum;
   m_LH_Shows                    = from.m_LH_Shows;
   m_LH_Clicks                   = from.m_LH_Clicks;
   m_LH_CTR_Prc                  = from.m_LH_CTR_Prc;
   m_LH_CPH_Prc                  = from.m_LH_CPH_Prc;
   m_CustomIndex1                = from.m_CustomIndex1;
   m_CustomIndex2                = from.m_CustomIndex2;
   m_CustomIndex3                = from.m_CustomIndex3;
   m_CustomIndex4                = from.m_CustomIndex4;
   m_CustomIndex5                = from.m_CustomIndex5;
   m_Allowed                     = from.m_Allowed;
   m_ObjectState                 = from.m_ObjectState;
   m_ba_ModeratorComment         = from.m_ba_ModeratorComment;
   m_TagID                       = from.m_TagID;
   m_TagBool                     = from.m_TagBool;
   m_TagInt                      = from.m_TagInt;
   m_ReservedID                  = from.m_ReservedID;
   m_ReservedInt                 = from.m_ReservedInt;
   m_ReservedString              = from.m_ReservedString;
   m_RatingPlaceInfo             = from.m_RatingPlaceInfo;
   m_CacheTime                   = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Site::CopyDataTo (OC_Site& to)
{
   to.m_OwnerID                     = m_OwnerID;
   to.m_VBN                         = m_VBN;
   to.m_CreationTime                = m_CreationTime;
   to.m_Alias                       = m_Alias;
   to.m_Name                        = m_Name;
   to.m_Description                 = m_Description;
   to.m_Announce                    = m_Announce;
   to.m_URL                         = m_URL;
   to.m_CounterType                 = m_CounterType;
   to.m_RateMySite                  = m_RateMySite;
   to.m_RateStatsViewPassword       = m_RateStatsViewPassword;
   to.m_ShowAudience                = m_ShowAudience;
   to.m_ShowAudienceOffTime         = m_ShowAudienceOffTime;
   to.m_Profile                     = m_Profile;
   to.m_Keyword                     = m_Keyword;
   to.m_MirrorInclude               = m_MirrorInclude;
   to.m_MirrorExclude               = m_MirrorExclude;
   to.m_MirrorSubstr                = m_MirrorSubstr;
   to.m_IgnoredIP                   = m_IgnoredIP;
   to.m_IgnoredViewerID             = m_IgnoredViewerID;
   to.m_ba_Concept                  = m_ba_Concept;
   to.m_pba_Concept                 = m_pba_Concept;
   to.m_eba_Concept                 = m_eba_Concept;
   to.m_CRN_Self                    = m_CRN_Self;
   to.m_Page                        = m_Page;
   to.m_PageName                    = m_PageName;
   to.m_PageNo                      = m_PageNo;
   to.m_AdBannerProfile             = m_AdBannerProfile;
   to.m_SuspiciousInfo              = m_SuspiciousInfo;
   to.m_CRA_Visitor                 = m_CRA_Visitor;
   to.m_CRN_Visitor                 = m_CRN_Visitor;
   to.m_CRN_Visitor_Update          = m_CRN_Visitor_Update;
   to.m_CRA_Inquiry                 = m_CRA_Inquiry;
   to.m_CRN_Inquiry                 = m_CRN_Inquiry;
   to.m_CRN_VisitorIncr             = m_CRN_VisitorIncr;
   to.m_CRN_VisitorIncr_Update      = m_CRN_VisitorIncr_Update;
   to.m_Audience_SiteID             = m_Audience_SiteID;
   to.m_Audience_Viewers            = m_Audience_Viewers;
   to.m_Audience_Hosts              = m_Audience_Hosts;
   to.m_Audience_SiteIDInclude      = m_Audience_SiteIDInclude;
   to.m_ActiveViewersID             = m_ActiveViewersID;
   to.m_ActiveViewersHits           = m_ActiveViewersHits;
   to.m_RecentPointer               = m_RecentPointer;
   to.m_RecentVisitor               = m_RecentVisitor;
   to.m_RecentReferrer              = m_RecentReferrer;
   to.m_RecentTimeStamp             = m_RecentTimeStamp;
   to.m_Referrer                    = m_Referrer;
   to.m_ReferrerCount               = m_ReferrerCount;
   to.m_Referrer_LastReset          = m_Referrer_LastReset;
   to.m_DailyReferrerStats          = m_DailyReferrerStats;
   to.m_DailyReferrerTimeStamp      = m_DailyReferrerTimeStamp;
   to.m_SearchWordsInfo             = m_SearchWordsInfo;
   to.m_Inquire                     = m_Inquire;
   to.m_InquiredVisitorNum          = m_InquiredVisitorNum;
   to.m_SessionResetTime            = m_SessionResetTime;
   to.m_ReturnNumRate               = m_ReturnNumRate;
   to.m_ShowNumRate                 = m_ShowNumRate;
   to.m_LastVisitTime               = m_LastVisitTime;
   to.m_LastUpdateTime              = m_LastUpdateTime;
   to.m_Loads                       = m_Loads;
   to.m_Visitors                    = m_Visitors;
   to.m_Hosts                       = m_Hosts;
   to.m_Shows                       = m_Shows;
   to.m_Clicks                      = m_Clicks;
   to.m_Clicks_Local                = m_Clicks_Local;
   to.m_Hits                        = m_Hits;
   to.m_Hits_Local                  = m_Hits_Local;
   to.m_AnonymousHits               = m_AnonymousHits;
   to.m_SuspiciousHits              = m_SuspiciousHits;
   to.m_SessionTime                 = m_SessionTime;
   to.m_SessionTime_Local           = m_SessionTime_Local;
   to.m_SessionNum                  = m_SessionNum;
   to.m_Total_Loads                 = m_Total_Loads;
   to.m_Total_Hosts                 = m_Total_Hosts;
   to.m_Total_Hits                  = m_Total_Hits;
   to.m_Total_AnonymousHits         = m_Total_AnonymousHits;
   to.m_Total_AnonymousHits_Prc     = m_Total_AnonymousHits_Prc;
   to.m_Total_SuspiciousHits_Prc    = m_Total_SuspiciousHits_Prc;
   to.m_Total_Visitors              = m_Total_Visitors;
   to.m_Total_VisitorReturns        = m_Total_VisitorReturns;
   to.m_Total_VisitorReturns_Prc    = m_Total_VisitorReturns_Prc;
   to.m_Total_SessionNum            = m_Total_SessionNum;
   to.m_Total_AveSessionTime        = m_Total_AveSessionTime;
   to.m_Total_AveReloadTime         = m_Total_AveReloadTime;
   to.m_Total_AveReloadNum          = m_Total_AveReloadNum;
   to.m_Total_Shows                 = m_Total_Shows;
   to.m_Total_Clicks                = m_Total_Clicks;
   to.m_Total_CTR_Prc               = m_Total_CTR_Prc;
   to.m_Total_CPH_Prc               = m_Total_CPH_Prc;
   to.m_Total_AnonymousVisitors     = m_Total_AnonymousVisitors;
   to.m_Total_AnonymousVisitors_Prc = m_Total_AnonymousVisitors_Prc;
   to.m_Total_VisitorExperience     = m_Total_VisitorExperience;
   to.m_Ave_VisitorExperience       = m_Ave_VisitorExperience;
   to.m_OnlineVisitors              = m_OnlineVisitors;
   to.m_Total_MouseOver             = m_Total_MouseOver;
   to.m_Total_Votes                 = m_Total_Votes;
   to.m_Total_Votes_Sum             = m_Total_Votes_Sum;
   to.m_Total_Votes_Ave             = m_Total_Votes_Ave;
   to.m_LM_Loads                    = m_LM_Loads;
   to.m_LM_Hosts                    = m_LM_Hosts;
   to.m_LM_Hits                     = m_LM_Hits;
   to.m_LM_AnonymousHits            = m_LM_AnonymousHits;
   to.m_LM_AnonymousHits_Prc        = m_LM_AnonymousHits_Prc;
   to.m_LM_SuspiciousHits_Prc       = m_LM_SuspiciousHits_Prc;
   to.m_LM_Visitors                 = m_LM_Visitors;
   to.m_LM_VisitorReturns           = m_LM_VisitorReturns;
   to.m_LM_VisitorReturns_Prc       = m_LM_VisitorReturns_Prc;
   to.m_LM_SessionNum               = m_LM_SessionNum;
   to.m_LM_AveSessionTime           = m_LM_AveSessionTime;
   to.m_LM_AveReloadTime            = m_LM_AveReloadTime;
   to.m_LM_AveReloadNum             = m_LM_AveReloadNum;
   to.m_LM_Shows                    = m_LM_Shows;
   to.m_LM_Clicks                   = m_LM_Clicks;
   to.m_LM_CTR_Prc                  = m_LM_CTR_Prc;
   to.m_LM_CPH_Prc                  = m_LM_CPH_Prc;
   to.m_LW_Loads                    = m_LW_Loads;
   to.m_LW_Hosts                    = m_LW_Hosts;
   to.m_LW_Hits                     = m_LW_Hits;
   to.m_LW_AnonymousHits            = m_LW_AnonymousHits;
   to.m_LW_AnonymousHits_Prc        = m_LW_AnonymousHits_Prc;
   to.m_LW_SuspiciousHits_Prc       = m_LW_SuspiciousHits_Prc;
   to.m_LW_Visitors                 = m_LW_Visitors;
   to.m_LW_VisitorReturns           = m_LW_VisitorReturns;
   to.m_LW_VisitorReturns_Prc       = m_LW_VisitorReturns_Prc;
   to.m_LW_SessionNum               = m_LW_SessionNum;
   to.m_LW_AveSessionTime           = m_LW_AveSessionTime;
   to.m_LW_AveReloadTime            = m_LW_AveReloadTime;
   to.m_LW_AveReloadNum             = m_LW_AveReloadNum;
   to.m_LW_Shows                    = m_LW_Shows;
   to.m_LW_Clicks                   = m_LW_Clicks;
   to.m_LW_CTR_Prc                  = m_LW_CTR_Prc;
   to.m_LW_CPH_Prc                  = m_LW_CPH_Prc;
   to.m_LD_Loads                    = m_LD_Loads;
   to.m_LD_Hosts                    = m_LD_Hosts;
   to.m_LD_Hits                     = m_LD_Hits;
   to.m_LD_AnonymousHits            = m_LD_AnonymousHits;
   to.m_LD_AnonymousHits_Prc        = m_LD_AnonymousHits_Prc;
   to.m_LD_SuspiciousHits_Prc       = m_LD_SuspiciousHits_Prc;
   to.m_LD_Visitors                 = m_LD_Visitors;
   to.m_LD_VisitorReturns           = m_LD_VisitorReturns;
   to.m_LD_VisitorReturns_Prc       = m_LD_VisitorReturns_Prc;
   to.m_LD_SessionNum               = m_LD_SessionNum;
   to.m_LD_AveSessionTime           = m_LD_AveSessionTime;
   to.m_LD_AveReloadTime            = m_LD_AveReloadTime;
   to.m_LD_AveReloadNum             = m_LD_AveReloadNum;
   to.m_LD_Shows                    = m_LD_Shows;
   to.m_LD_Clicks                   = m_LD_Clicks;
   to.m_LD_CTR_Prc                  = m_LD_CTR_Prc;
   to.m_LD_CPH_Prc                  = m_LD_CPH_Prc;
   to.m_LH_Loads                    = m_LH_Loads;
   to.m_LH_Hosts                    = m_LH_Hosts;
   to.m_LH_Hits                     = m_LH_Hits;
   to.m_LH_AnonymousHits            = m_LH_AnonymousHits;
   to.m_LH_AnonymousHits_Prc        = m_LH_AnonymousHits_Prc;
   to.m_LH_SuspiciousHits_Prc       = m_LH_SuspiciousHits_Prc;
   to.m_LH_Visitors                 = m_LH_Visitors;
   to.m_LH_VisitorReturns           = m_LH_VisitorReturns;
   to.m_LH_VisitorReturns_Prc       = m_LH_VisitorReturns_Prc;
   to.m_LH_SessionNum               = m_LH_SessionNum;
   to.m_LH_AveSessionTime           = m_LH_AveSessionTime;
   to.m_LH_AveReloadTime            = m_LH_AveReloadTime;
   to.m_LH_AveReloadNum             = m_LH_AveReloadNum;
   to.m_LH_Shows                    = m_LH_Shows;
   to.m_LH_Clicks                   = m_LH_Clicks;
   to.m_LH_CTR_Prc                  = m_LH_CTR_Prc;
   to.m_LH_CPH_Prc                  = m_LH_CPH_Prc;
   to.m_CustomIndex1                = m_CustomIndex1;
   to.m_CustomIndex2                = m_CustomIndex2;
   to.m_CustomIndex3                = m_CustomIndex3;
   to.m_CustomIndex4                = m_CustomIndex4;
   to.m_CustomIndex5                = m_CustomIndex5;
   to.m_Allowed                     = m_Allowed;
   to.m_ObjectState                 = m_ObjectState;
   to.m_ba_ModeratorComment         = m_ba_ModeratorComment;
   to.m_TagID                       = m_TagID;
   to.m_TagBool                     = m_TagBool;
   to.m_TagInt                      = m_TagInt;
   to.m_ReservedID                  = m_ReservedID;
   to.m_ReservedInt                 = m_ReservedInt;
   to.m_ReservedString              = m_ReservedString;
   to.m_RatingPlaceInfo             = m_RatingPlaceInfo;
   to.m_CacheTime                   = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Site&  OC_Site::operator << (OC_Site& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Site&  OC_Site::operator >> (OC_Site& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Site::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_VBN_Name ();
              return oldIndex;
      case 1: SetIndex_Alias ();
              return oldIndex;
      case 2: SetIndex_VBN_CreationTime ();
              return oldIndex;
      case 3: SetIndex_LastVisitTime ();
              return oldIndex;
      case 4: SetIndex_LastUpdateTime ();
              return oldIndex;
      case 5: SetIndex_VBN_Allowed_ObjectState ();
              return oldIndex;
      case 6: SetIndex_VBN__Total_Loads ();
              return oldIndex;
      case 7: SetIndex_VBN__Total_Hosts ();
              return oldIndex;
      case 8: SetIndex_VBN__Total_Hits ();
              return oldIndex;
      case 9: SetIndex_VBN__Total_AnonymousHits ();
              return oldIndex;
      case 10: SetIndex_VBN__Total_AnonymousHits_Prc ();
              return oldIndex;
      case 11: SetIndex_VBN__Total_SuspiciousHits_Prc ();
              return oldIndex;
      case 12: SetIndex_VBN__Total_Visitors ();
              return oldIndex;
      case 13: SetIndex_VBN__Total_VisitorReturns ();
              return oldIndex;
      case 14: SetIndex_VBN__Total_VisitorReturns_Prc ();
              return oldIndex;
      case 15: SetIndex_VBN__Total_SessionNum ();
              return oldIndex;
      case 16: SetIndex_VBN__Total_AveSessionTime ();
              return oldIndex;
      case 17: SetIndex_VBN__Total_AveReloadTime ();
              return oldIndex;
      case 18: SetIndex_VBN__Total_AveReloadNum ();
              return oldIndex;
      case 19: SetIndex_VBN__Total_Shows ();
              return oldIndex;
      case 20: SetIndex_VBN__Total_Clicks ();
              return oldIndex;
      case 21: SetIndex_VBN__Total_CTR_Prc ();
              return oldIndex;
      case 22: SetIndex_VBN__Total_CPH_Prc ();
              return oldIndex;
      case 23: SetIndex_VBN__Total_AnonymousVisitors ();
              return oldIndex;
      case 24: SetIndex_VBN__Total_AnonymousVisitors_Prc ();
              return oldIndex;
      case 25: SetIndex_VBN__Total_VisitorExperience ();
              return oldIndex;
      case 26: SetIndex_VBN__Ave_VisitorExperience ();
              return oldIndex;
      case 27: SetIndex_VBN__OnlineVisitors ();
              return oldIndex;
      case 28: SetIndex_VBN__Total_MouseOver ();
              return oldIndex;
      case 29: SetIndex_VBN__Total_Votes ();
              return oldIndex;
      case 30: SetIndex_VBN__Total_Votes_Sum ();
              return oldIndex;
      case 31: SetIndex_VBN__Total_Votes_Ave ();
              return oldIndex;
      case 32: SetIndex_VBN__LM_Loads ();
              return oldIndex;
      case 33: SetIndex_VBN__LM_Hosts ();
              return oldIndex;
      case 34: SetIndex_VBN__LM_Hits ();
              return oldIndex;
      case 35: SetIndex_VBN__LM_AnonymousHits ();
              return oldIndex;
      case 36: SetIndex_VBN__LM_AnonymousHits_Prc ();
              return oldIndex;
      case 37: SetIndex_VBN__LM_SuspiciousHits_Prc ();
              return oldIndex;
      case 38: SetIndex_VBN__LM_Visitors ();
              return oldIndex;
      case 39: SetIndex_VBN__LM_VisitorReturns ();
              return oldIndex;
      case 40: SetIndex_VBN__LM_VisitorReturns_Prc ();
              return oldIndex;
      case 41: SetIndex_VBN__LM_SessionNum ();
              return oldIndex;
      case 42: SetIndex_VBN__LM_AveSessionTime ();
              return oldIndex;
      case 43: SetIndex_VBN__LM_AveReloadTime ();
              return oldIndex;
      case 44: SetIndex_VBN__LM_AveReloadNum ();
              return oldIndex;
      case 45: SetIndex_VBN__LM_Shows ();
              return oldIndex;
      case 46: SetIndex_VBN__LM_Clicks ();
              return oldIndex;
      case 47: SetIndex_VBN__LM_CTR_Prc ();
              return oldIndex;
      case 48: SetIndex_VBN__LM_CPH_Prc ();
              return oldIndex;
      case 49: SetIndex_VBN__LW_Loads ();
              return oldIndex;
      case 50: SetIndex_VBN__LW_Hosts ();
              return oldIndex;
      case 51: SetIndex_VBN__LW_Hits ();
              return oldIndex;
      case 52: SetIndex_VBN__LW_AnonymousHits ();
              return oldIndex;
      case 53: SetIndex_VBN__LW_AnonymousHits_Prc ();
              return oldIndex;
      case 54: SetIndex_VBN__LW_SuspiciousHits_Prc ();
              return oldIndex;
      case 55: SetIndex_VBN__LW_Visitors ();
              return oldIndex;
      case 56: SetIndex_VBN__LW_VisitorReturns ();
              return oldIndex;
      case 57: SetIndex_VBN__LW_VisitorReturns_Prc ();
              return oldIndex;
      case 58: SetIndex_VBN__LW_SessionNum ();
              return oldIndex;
      case 59: SetIndex_VBN__LW_AveSessionTime ();
              return oldIndex;
      case 60: SetIndex_VBN__LW_AveReloadTime ();
              return oldIndex;
      case 61: SetIndex_VBN__LW_AveReloadNum ();
              return oldIndex;
      case 62: SetIndex_VBN__LW_Shows ();
              return oldIndex;
      case 63: SetIndex_VBN__LW_Clicks ();
              return oldIndex;
      case 64: SetIndex_VBN__LW_CTR_Prc ();
              return oldIndex;
      case 65: SetIndex_VBN__LW_CPH_Prc ();
              return oldIndex;
      case 66: SetIndex_VBN__LD_Loads ();
              return oldIndex;
      case 67: SetIndex_VBN__LD_Hosts ();
              return oldIndex;
      case 68: SetIndex_VBN__LD_Hits ();
              return oldIndex;
      case 69: SetIndex_VBN__LD_AnonymousHits ();
              return oldIndex;
      case 70: SetIndex_VBN__LD_AnonymousHits_Prc ();
              return oldIndex;
      case 71: SetIndex_VBN__LD_SuspiciousHits_Prc ();
              return oldIndex;
      case 72: SetIndex_VBN__LD_Visitors ();
              return oldIndex;
      case 73: SetIndex_VBN__LD_VisitorReturns ();
              return oldIndex;
      case 74: SetIndex_VBN__LD_VisitorReturns_Prc ();
              return oldIndex;
      case 75: SetIndex_VBN__LD_SessionNum ();
              return oldIndex;
      case 76: SetIndex_VBN__LD_AveSessionTime ();
              return oldIndex;
      case 77: SetIndex_VBN__LD_AveReloadTime ();
              return oldIndex;
      case 78: SetIndex_VBN__LD_AveReloadNum ();
              return oldIndex;
      case 79: SetIndex_VBN__LD_Shows ();
              return oldIndex;
      case 80: SetIndex_VBN__LD_Clicks ();
              return oldIndex;
      case 81: SetIndex_VBN__LD_CTR_Prc ();
              return oldIndex;
      case 82: SetIndex_VBN__LD_CPH_Prc ();
              return oldIndex;
      case 83: SetIndex_VBN__LH_Loads ();
              return oldIndex;
      case 84: SetIndex_VBN__LH_Hosts ();
              return oldIndex;
      case 85: SetIndex_VBN__LH_Hits ();
              return oldIndex;
      case 86: SetIndex_VBN__LH_AnonymousHits ();
              return oldIndex;
      case 87: SetIndex_VBN__LH_AnonymousHits_Prc ();
              return oldIndex;
      case 88: SetIndex_VBN__LH_SuspiciousHits_Prc ();
              return oldIndex;
      case 89: SetIndex_VBN__LH_Visitors ();
              return oldIndex;
      case 90: SetIndex_VBN__LH_VisitorReturns ();
              return oldIndex;
      case 91: SetIndex_VBN__LH_VisitorReturns_Prc ();
              return oldIndex;
      case 92: SetIndex_VBN__LH_SessionNum ();
              return oldIndex;
      case 93: SetIndex_VBN__LH_AveSessionTime ();
              return oldIndex;
      case 94: SetIndex_VBN__LH_AveReloadTime ();
              return oldIndex;
      case 95: SetIndex_VBN__LH_AveReloadNum ();
              return oldIndex;
      case 96: SetIndex_VBN__LH_Shows ();
              return oldIndex;
      case 97: SetIndex_VBN__LH_Clicks ();
              return oldIndex;
      case 98: SetIndex_VBN__LH_CTR_Prc ();
              return oldIndex;
      case 99: SetIndex_VBN__LH_CPH_Prc ();
              return oldIndex;
      case 100: SetIndex_VBN__CustomIndex1 ();
              return oldIndex;
      case 101: SetIndex_VBN__CustomIndex2 ();
              return oldIndex;
      case 102: SetIndex_VBN__CustomIndex3 ();
              return oldIndex;
      case 103: SetIndex_VBN__CustomIndex4 ();
              return oldIndex;
      case 104: SetIndex_VBN__CustomIndex5 ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Site::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN_Name ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_Site::SetIndex_Alias ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN_CreationTime ()
{
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Site::SetIndex_LastVisitTime ()
{
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Site::SetIndex_LastUpdateTime ()
{
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN_Allowed_ObjectState ()
{
   curIndexInfo.m_id         = 5; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_byte; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Loads ()
{
   curIndexInfo.m_id         = 6; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Hosts ()
{
   curIndexInfo.m_id         = 7; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Hits ()
{
   curIndexInfo.m_id         = 8; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AnonymousHits ()
{
   curIndexInfo.m_id         = 9; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AnonymousHits_Prc ()
{
   curIndexInfo.m_id         = 10; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_SuspiciousHits_Prc ()
{
   curIndexInfo.m_id         = 11; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Visitors ()
{
   curIndexInfo.m_id         = 12; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_VisitorReturns ()
{
   curIndexInfo.m_id         = 13; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_VisitorReturns_Prc ()
{
   curIndexInfo.m_id         = 14; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_SessionNum ()
{
   curIndexInfo.m_id         = 15; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AveSessionTime ()
{
   curIndexInfo.m_id         = 16; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AveReloadTime ()
{
   curIndexInfo.m_id         = 17; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AveReloadNum ()
{
   curIndexInfo.m_id         = 18; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Shows ()
{
   curIndexInfo.m_id         = 19; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Clicks ()
{
   curIndexInfo.m_id         = 20; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_CTR_Prc ()
{
   curIndexInfo.m_id         = 21; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_CPH_Prc ()
{
   curIndexInfo.m_id         = 22; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AnonymousVisitors ()
{
   curIndexInfo.m_id         = 23; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_AnonymousVisitors_Prc ()
{
   curIndexInfo.m_id         = 24; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_VisitorExperience ()
{
   curIndexInfo.m_id         = 25; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Ave_VisitorExperience ()
{
   curIndexInfo.m_id         = 26; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__OnlineVisitors ()
{
   curIndexInfo.m_id         = 27; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_MouseOver ()
{
   curIndexInfo.m_id         = 28; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Votes ()
{
   curIndexInfo.m_id         = 29; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Votes_Sum ()
{
   curIndexInfo.m_id         = 30; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__Total_Votes_Ave ()
{
   curIndexInfo.m_id         = 31; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Loads ()
{
   curIndexInfo.m_id         = 32; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Hosts ()
{
   curIndexInfo.m_id         = 33; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Hits ()
{
   curIndexInfo.m_id         = 34; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_AnonymousHits ()
{
   curIndexInfo.m_id         = 35; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_AnonymousHits_Prc ()
{
   curIndexInfo.m_id         = 36; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_SuspiciousHits_Prc ()
{
   curIndexInfo.m_id         = 37; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Visitors ()
{
   curIndexInfo.m_id         = 38; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_VisitorReturns ()
{
   curIndexInfo.m_id         = 39; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_VisitorReturns_Prc ()
{
   curIndexInfo.m_id         = 40; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_SessionNum ()
{
   curIndexInfo.m_id         = 41; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_AveSessionTime ()
{
   curIndexInfo.m_id         = 42; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_AveReloadTime ()
{
   curIndexInfo.m_id         = 43; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_AveReloadNum ()
{
   curIndexInfo.m_id         = 44; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Shows ()
{
   curIndexInfo.m_id         = 45; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_Clicks ()
{
   curIndexInfo.m_id         = 46; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_CTR_Prc ()
{
   curIndexInfo.m_id         = 47; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LM_CPH_Prc ()
{
   curIndexInfo.m_id         = 48; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Loads ()
{
   curIndexInfo.m_id         = 49; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Hosts ()
{
   curIndexInfo.m_id         = 50; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Hits ()
{
   curIndexInfo.m_id         = 51; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_AnonymousHits ()
{
   curIndexInfo.m_id         = 52; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_AnonymousHits_Prc ()
{
   curIndexInfo.m_id         = 53; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_SuspiciousHits_Prc ()
{
   curIndexInfo.m_id         = 54; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Visitors ()
{
   curIndexInfo.m_id         = 55; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_VisitorReturns ()
{
   curIndexInfo.m_id         = 56; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_VisitorReturns_Prc ()
{
   curIndexInfo.m_id         = 57; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_SessionNum ()
{
   curIndexInfo.m_id         = 58; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_AveSessionTime ()
{
   curIndexInfo.m_id         = 59; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_AveReloadTime ()
{
   curIndexInfo.m_id         = 60; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_AveReloadNum ()
{
   curIndexInfo.m_id         = 61; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Shows ()
{
   curIndexInfo.m_id         = 62; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_Clicks ()
{
   curIndexInfo.m_id         = 63; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_CTR_Prc ()
{
   curIndexInfo.m_id         = 64; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LW_CPH_Prc ()
{
   curIndexInfo.m_id         = 65; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Loads ()
{
   curIndexInfo.m_id         = 66; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Hosts ()
{
   curIndexInfo.m_id         = 67; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Hits ()
{
   curIndexInfo.m_id         = 68; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_AnonymousHits ()
{
   curIndexInfo.m_id         = 69; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_AnonymousHits_Prc ()
{
   curIndexInfo.m_id         = 70; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_SuspiciousHits_Prc ()
{
   curIndexInfo.m_id         = 71; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Visitors ()
{
   curIndexInfo.m_id         = 72; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_VisitorReturns ()
{
   curIndexInfo.m_id         = 73; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_VisitorReturns_Prc ()
{
   curIndexInfo.m_id         = 74; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_SessionNum ()
{
   curIndexInfo.m_id         = 75; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_AveSessionTime ()
{
   curIndexInfo.m_id         = 76; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_AveReloadTime ()
{
   curIndexInfo.m_id         = 77; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_AveReloadNum ()
{
   curIndexInfo.m_id         = 78; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Shows ()
{
   curIndexInfo.m_id         = 79; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_Clicks ()
{
   curIndexInfo.m_id         = 80; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_CTR_Prc ()
{
   curIndexInfo.m_id         = 81; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LD_CPH_Prc ()
{
   curIndexInfo.m_id         = 82; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Loads ()
{
   curIndexInfo.m_id         = 83; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Hosts ()
{
   curIndexInfo.m_id         = 84; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Hits ()
{
   curIndexInfo.m_id         = 85; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_AnonymousHits ()
{
   curIndexInfo.m_id         = 86; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_AnonymousHits_Prc ()
{
   curIndexInfo.m_id         = 87; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_SuspiciousHits_Prc ()
{
   curIndexInfo.m_id         = 88; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Visitors ()
{
   curIndexInfo.m_id         = 89; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_VisitorReturns ()
{
   curIndexInfo.m_id         = 90; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_VisitorReturns_Prc ()
{
   curIndexInfo.m_id         = 91; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_SessionNum ()
{
   curIndexInfo.m_id         = 92; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_AveSessionTime ()
{
   curIndexInfo.m_id         = 93; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_AveReloadTime ()
{
   curIndexInfo.m_id         = 94; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_AveReloadNum ()
{
   curIndexInfo.m_id         = 95; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Shows ()
{
   curIndexInfo.m_id         = 96; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_Clicks ()
{
   curIndexInfo.m_id         = 97; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_CTR_Prc ()
{
   curIndexInfo.m_id         = 98; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__LH_CPH_Prc ()
{
   curIndexInfo.m_id         = 99; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__CustomIndex1 ()
{
   curIndexInfo.m_id         = 100; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__CustomIndex2 ()
{
   curIndexInfo.m_id         = 101; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__CustomIndex3 ()
{
   curIndexInfo.m_id         = 102; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__CustomIndex4 ()
{
   curIndexInfo.m_id         = 103; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Site::SetIndex_VBN__CustomIndex5 ()
{
   curIndexInfo.m_id         = 104; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// SiteProfile

// Конструктор по умолчанию
OC_SiteProfile::OC_SiteProfile ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_SiteProfile::OC_SiteProfile  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_SiteProfile::OC_SiteProfile  (const OC_SiteProfile& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_SiteProfile::~OC_SiteProfile ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_SiteProfile& OC_SiteProfile::operator= (const OC_SiteProfile& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_SiteProfile& OC_SiteProfile::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_SiteProfile::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_SiteProfile;
   m_Name._init                    (classID, 1, &coPtr, &OD_SiteProfile::d_Name                    );
   m_Site._init                    (classID, 2, &coPtr, &OD_SiteProfile::d_Site                    );
   m_VBN._init                     (classID, 3, &coPtr, &OD_SiteProfile::d_VBN                     );
   m_LastModified._init            (classID, 4, &coPtr, &OD_SiteProfile::d_LastModified            );
   m_OwnerID._init                 (classID, 5, &coPtr, &OD_SiteProfile::d_OwnerID                 );
   m_DefaultKeyword._init          (classID, 6, &coPtr, &OD_SiteProfile::d_DefaultKeyword          );
   m_BannerInclude._init           (classID, 7, &coPtr, &OD_SiteProfile::d_BannerInclude           );
   m_BannerExclude._init           (classID, 8, &coPtr, &OD_SiteProfile::d_BannerExclude           );
   m_SiteInclude._init             (classID, 9, &coPtr, &OD_SiteProfile::d_SiteInclude             );
   m_SiteExclude._init             (classID, 10, &coPtr, &OD_SiteProfile::d_SiteExclude             );
   m_MaxFileSize._init             (classID, 11, &coPtr, &OD_SiteProfile::d_MaxFileSize             );
   m_UseKeywords._init             (classID, 12, &coPtr, &OD_SiteProfile::d_UseKeywords             );
   m_ba_BannerConceptInclude._init (classID, 13, &coPtr, &OD_SiteProfile::d_ba_BannerConceptInclude );
   m_ba_BannerConceptExclude._init (classID, 14, &coPtr, &OD_SiteProfile::d_ba_BannerConceptExclude );
   m_eba_BannerConcept._init       (classID, 15, &coPtr, &OD_SiteProfile::d_eba_BannerConcept       );
   m_Price._init                   (classID, 16, &coPtr, &OD_SiteProfile::d_Price                   );
   m_StaticSupport._init           (classID, 17, &coPtr, &OD_SiteProfile::d_StaticSupport           );
   m_Allowed._init                 (classID, 18, &coPtr, &OD_SiteProfile::d_Allowed                 );
   m_ObjectState._init             (classID, 19, &coPtr, &OD_SiteProfile::d_ObjectState             );
   m_ba_ModeratorComment._init     (classID, 20, &coPtr, &OD_SiteProfile::d_ba_ModeratorComment     );
   m_TagID._init                   (classID, 21, &coPtr, &OD_SiteProfile::d_TagID                   );
   m_TagBool._init                 (classID, 22, &coPtr, &OD_SiteProfile::d_TagBool                 );
   m_TagInt._init                  (classID, 23, &coPtr, &OD_SiteProfile::d_TagInt                  );
   m_ReservedID._init              (classID, 24, &coPtr, &OD_SiteProfile::d_ReservedID              );
   m_ReservedInt._init             (classID, 25, &coPtr, &OD_SiteProfile::d_ReservedInt             );
   m_ReservedString._init          (classID, 26, &coPtr, &OD_SiteProfile::d_ReservedString          );
   m_CacheTime._init               (classID, 27, &coPtr, &OD_SiteProfile::d_CacheTime               );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_SiteProfile::CopyDataFrom (OC_SiteProfile& from)
{
   m_Name                    = from.m_Name;
   m_Site                    = from.m_Site;
   m_VBN                     = from.m_VBN;
   m_LastModified            = from.m_LastModified;
   m_OwnerID                 = from.m_OwnerID;
   m_DefaultKeyword          = from.m_DefaultKeyword;
   m_BannerInclude           = from.m_BannerInclude;
   m_BannerExclude           = from.m_BannerExclude;
   m_SiteInclude             = from.m_SiteInclude;
   m_SiteExclude             = from.m_SiteExclude;
   m_MaxFileSize             = from.m_MaxFileSize;
   m_UseKeywords             = from.m_UseKeywords;
   m_ba_BannerConceptInclude = from.m_ba_BannerConceptInclude;
   m_ba_BannerConceptExclude = from.m_ba_BannerConceptExclude;
   m_eba_BannerConcept       = from.m_eba_BannerConcept;
   m_Price                   = from.m_Price;
   m_StaticSupport           = from.m_StaticSupport;
   m_Allowed                 = from.m_Allowed;
   m_ObjectState             = from.m_ObjectState;
   m_ba_ModeratorComment     = from.m_ba_ModeratorComment;
   m_TagID                   = from.m_TagID;
   m_TagBool                 = from.m_TagBool;
   m_TagInt                  = from.m_TagInt;
   m_ReservedID              = from.m_ReservedID;
   m_ReservedInt             = from.m_ReservedInt;
   m_ReservedString          = from.m_ReservedString;
   m_CacheTime               = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_SiteProfile::CopyDataTo (OC_SiteProfile& to)
{
   to.m_Name                    = m_Name;
   to.m_Site                    = m_Site;
   to.m_VBN                     = m_VBN;
   to.m_LastModified            = m_LastModified;
   to.m_OwnerID                 = m_OwnerID;
   to.m_DefaultKeyword          = m_DefaultKeyword;
   to.m_BannerInclude           = m_BannerInclude;
   to.m_BannerExclude           = m_BannerExclude;
   to.m_SiteInclude             = m_SiteInclude;
   to.m_SiteExclude             = m_SiteExclude;
   to.m_MaxFileSize             = m_MaxFileSize;
   to.m_UseKeywords             = m_UseKeywords;
   to.m_ba_BannerConceptInclude = m_ba_BannerConceptInclude;
   to.m_ba_BannerConceptExclude = m_ba_BannerConceptExclude;
   to.m_eba_BannerConcept       = m_eba_BannerConcept;
   to.m_Price                   = m_Price;
   to.m_StaticSupport           = m_StaticSupport;
   to.m_Allowed                 = m_Allowed;
   to.m_ObjectState             = m_ObjectState;
   to.m_ba_ModeratorComment     = m_ba_ModeratorComment;
   to.m_TagID                   = m_TagID;
   to.m_TagBool                 = m_TagBool;
   to.m_TagInt                  = m_TagInt;
   to.m_ReservedID              = m_ReservedID;
   to.m_ReservedInt             = m_ReservedInt;
   to.m_ReservedString          = m_ReservedString;
   to.m_CacheTime               = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_SiteProfile&  OC_SiteProfile::operator << (OC_SiteProfile& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_SiteProfile&  OC_SiteProfile::operator >> (OC_SiteProfile& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_SiteProfile::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_VBN_Allowed_ObjectState ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_SiteProfile::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_SiteProfile::SetIndex_VBN_Allowed_ObjectState ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
   curIndexInfo.m_keyType[2] = (byte)FT_byte; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// ShowEvent

// Конструктор по умолчанию
OC_ShowEvent::OC_ShowEvent ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_ShowEvent::OC_ShowEvent  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_ShowEvent::OC_ShowEvent  (const OC_ShowEvent& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_ShowEvent::~OC_ShowEvent ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_ShowEvent& OC_ShowEvent::operator= (const OC_ShowEvent& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_ShowEvent& OC_ShowEvent::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_ShowEvent::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_ShowEvent;
   m_SiteID._init         (classID, 1, &coPtr, &OD_ShowEvent::d_SiteID         );
   m_ViewerID._init       (classID, 2, &coPtr, &OD_ShowEvent::d_ViewerID       );
   m_Time._init           (classID, 3, &coPtr, &OD_ShowEvent::d_Time           );
   m_ExitCode._init       (classID, 4, &coPtr, &OD_ShowEvent::d_ExitCode       );
   m_TagID._init          (classID, 5, &coPtr, &OD_ShowEvent::d_TagID          );
   m_TagInt._init         (classID, 6, &coPtr, &OD_ShowEvent::d_TagInt         );
   m_TagBool._init        (classID, 7, &coPtr, &OD_ShowEvent::d_TagBool        );
   m_ReservedString._init (classID, 8, &coPtr, &OD_ShowEvent::d_ReservedString );
   m_CacheTime._init      (classID, 9, &coPtr, &OD_ShowEvent::d_CacheTime      );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_ShowEvent::CopyDataFrom (OC_ShowEvent& from)
{
   m_SiteID         = from.m_SiteID;
   m_ViewerID       = from.m_ViewerID;
   m_Time           = from.m_Time;
   m_ExitCode       = from.m_ExitCode;
   m_TagID          = from.m_TagID;
   m_TagInt         = from.m_TagInt;
   m_TagBool        = from.m_TagBool;
   m_ReservedString = from.m_ReservedString;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_ShowEvent::CopyDataTo (OC_ShowEvent& to)
{
   to.m_SiteID         = m_SiteID;
   to.m_ViewerID       = m_ViewerID;
   to.m_Time           = m_Time;
   to.m_ExitCode       = m_ExitCode;
   to.m_TagID          = m_TagID;
   to.m_TagInt         = m_TagInt;
   to.m_TagBool        = m_TagBool;
   to.m_ReservedString = m_ReservedString;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_ShowEvent&  OC_ShowEvent::operator << (OC_ShowEvent& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_ShowEvent&  OC_ShowEvent::operator >> (OC_ShowEvent& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_ShowEvent::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Time ();
              return oldIndex;
      case 1: SetIndex_SiteID_ViewerID__Time ();
              return oldIndex;
      case 2: SetIndex_SiteID_ViewerID ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_ShowEvent::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_ShowEvent::SetIndex_Time ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_ShowEvent::SetIndex_SiteID_ViewerID__Time ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
   curIndexInfo.m_keyType[1] = (byte)FT_identifier; 
   curIndexInfo.m_keyType[2] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_ShowEvent::SetIndex_SiteID_ViewerID ()
{
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
   curIndexInfo.m_keyType[1] = (byte)FT_identifier; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Registry

void OC_Registry::About_class_OC_Master (){return;}

// Конструктор по умолчанию
OC_Registry::OC_Registry ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=OBD_OpenMasterObject(classID);
}



// Деструктор контроллера объекта
OC_Registry::~OC_Registry ()
{
   Release();
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Registry::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Registry;
   m_AdminPassword._init                     (classID, 1, &coPtr, &OD_Registry::d_AdminPassword                     );
   m_ConceptID_Sorted._init                  (classID, 2, &coPtr, &OD_Registry::d_ConceptID_Sorted                  );
   m_ConceptNo_SortID._init                  (classID, 3, &coPtr, &OD_Registry::d_ConceptNo_SortID                  );
   m_ConceptID_SortNo._init                  (classID, 4, &coPtr, &OD_Registry::d_ConceptID_SortNo                  );
   m_ConceptParent_SortNo._init              (classID, 5, &coPtr, &OD_Registry::d_ConceptParent_SortNo              );
   m_ConceptType_SortNo._init                (classID, 6, &coPtr, &OD_Registry::d_ConceptType_SortNo                );
   m_ConceptLevel_SortNo._init               (classID, 7, &coPtr, &OD_Registry::d_ConceptLevel_SortNo               );
   m_Language._init                          (classID, 8, &coPtr, &OD_Registry::d_Language                          );
   m_LanguageNo._init                        (classID, 9, &coPtr, &OD_Registry::d_LanguageNo                        );
   m_VBN._init                               (classID, 10, &coPtr, &OD_Registry::d_VBN                               );
   m_VBNNo._init                             (classID, 11, &coPtr, &OD_Registry::d_VBNNo                             );
   m_ModeratorComment._init                  (classID, 12, &coPtr, &OD_Registry::d_ModeratorComment                  );
   m_ModeratorCommentNo._init                (classID, 13, &coPtr, &OD_Registry::d_ModeratorCommentNo                );
   m_CRA_InetAudience._init                  (classID, 14, &coPtr, &OD_Registry::d_CRA_InetAudience                  );
   m_CRN_InetAudience._init                  (classID, 15, &coPtr, &OD_Registry::d_CRN_InetAudience                  );
   m_CRN_InetAudience_Update._init           (classID, 16, &coPtr, &OD_Registry::d_CRN_InetAudience_Update           );
   m_VisitorHistoryLength._init              (classID, 17, &coPtr, &OD_Registry::d_VisitorHistoryLength              );
   m_MinimumHitsTime._init                   (classID, 18, &coPtr, &OD_Registry::d_MinimumHitsTime                   );
   m_SuspiciousInfoSize._init                (classID, 19, &coPtr, &OD_Registry::d_SuspiciousInfoSize                );
   m_ActiveViewersSize._init                 (classID, 20, &coPtr, &OD_Registry::d_ActiveViewersSize                 );
   m_ReturnNumRateSize._init                 (classID, 21, &coPtr, &OD_Registry::d_ReturnNumRateSize                 );
   m_DailyReferrerSize._init                 (classID, 22, &coPtr, &OD_Registry::d_DailyReferrerSize                 );
   m_ClickNumRateSize._init                  (classID, 23, &coPtr, &OD_Registry::d_ClickNumRateSize                  );
   m_ShowNumRateSize._init                   (classID, 24, &coPtr, &OD_Registry::d_ShowNumRateSize                   );
   m_HitNumRateSize._init                    (classID, 25, &coPtr, &OD_Registry::d_HitNumRateSize                    );
   m_SessionTimeRateSize._init               (classID, 26, &coPtr, &OD_Registry::d_SessionTimeRateSize               );
   m_IgnoredIP._init                         (classID, 27, &coPtr, &OD_Registry::d_IgnoredIP                         );
   m_IgnoredUserAgent._init                  (classID, 28, &coPtr, &OD_Registry::d_IgnoredUserAgent                  );
   m_IgnoredBrowser._init                    (classID, 29, &coPtr, &OD_Registry::d_IgnoredBrowser                    );
   m_SearchEngines._init                     (classID, 30, &coPtr, &OD_Registry::d_SearchEngines                     );
   m_Classifiers._init                       (classID, 31, &coPtr, &OD_Registry::d_Classifiers                       );
   m_CachePurgeTime_IPRecord._init           (classID, 32, &coPtr, &OD_Registry::d_CachePurgeTime_IPRecord           );
   m_CachePurgeTime_RatingPlaceInfo._init    (classID, 33, &coPtr, &OD_Registry::d_CachePurgeTime_RatingPlaceInfo    );
   m_CachePurgeTime_SuspiciousInfo._init     (classID, 34, &coPtr, &OD_Registry::d_CachePurgeTime_SuspiciousInfo     );
   m_CachePurgeTime_SearchWordsInfo._init    (classID, 35, &coPtr, &OD_Registry::d_CachePurgeTime_SearchWordsInfo    );
   m_CachePurgeTime_DailyReferrerStats._init (classID, 36, &coPtr, &OD_Registry::d_CachePurgeTime_DailyReferrerStats );
   m_CachePurgeTime_DayStats._init           (classID, 37, &coPtr, &OD_Registry::d_CachePurgeTime_DayStats           );
   m_CachePurgeTime_YearStats._init          (classID, 38, &coPtr, &OD_Registry::d_CachePurgeTime_YearStats          );
   m_CachePurgeTime_TimeStats._init          (classID, 39, &coPtr, &OD_Registry::d_CachePurgeTime_TimeStats          );
   m_CachePurgeTime_ModeratorComment._init   (classID, 40, &coPtr, &OD_Registry::d_CachePurgeTime_ModeratorComment   );
   m_CachePurgeTime_Keyword._init            (classID, 41, &coPtr, &OD_Registry::d_CachePurgeTime_Keyword            );
   m_CachePurgeTime_SiteList._init           (classID, 42, &coPtr, &OD_Registry::d_CachePurgeTime_SiteList           );
   m_CachePurgeTime_Concept._init            (classID, 43, &coPtr, &OD_Registry::d_CachePurgeTime_Concept            );
   m_CachePurgeTime_Language._init           (classID, 44, &coPtr, &OD_Registry::d_CachePurgeTime_Language           );
   m_CachePurgeTime_VBN._init                (classID, 45, &coPtr, &OD_Registry::d_CachePurgeTime_VBN                );
   m_CachePurgeTime_Site._init               (classID, 46, &coPtr, &OD_Registry::d_CachePurgeTime_Site               );
   m_CachePurgeTime_Page._init               (classID, 47, &coPtr, &OD_Registry::d_CachePurgeTime_Page               );
   m_CachePurgeTime_BannerProfile._init      (classID, 48, &coPtr, &OD_Registry::d_CachePurgeTime_BannerProfile      );
   m_CachePurgeTime_Banner._init             (classID, 49, &coPtr, &OD_Registry::d_CachePurgeTime_Banner             );
   m_CachePurgeTime_TradeStats._init         (classID, 50, &coPtr, &OD_Registry::d_CachePurgeTime_TradeStats         );
   m_CachePurgeTime_User._init               (classID, 51, &coPtr, &OD_Registry::d_CachePurgeTime_User               );
   m_CachePurgeTime_ViewerGroup._init        (classID, 52, &coPtr, &OD_Registry::d_CachePurgeTime_ViewerGroup        );
   m_CachePurgeTime_Viewer._init             (classID, 53, &coPtr, &OD_Registry::d_CachePurgeTime_Viewer             );
   m_ReloadTimeThreshold._init               (classID, 54, &coPtr, &OD_Registry::d_ReloadTimeThreshold               );
   m_ViewerCacheReloadThreshold._init        (classID, 55, &coPtr, &OD_Registry::d_ViewerCacheReloadThreshold        );
   m_ReloadDistribution._init                (classID, 56, &coPtr, &OD_Registry::d_ReloadDistribution                );
   m_Viewers._init                           (classID, 57, &coPtr, &OD_Registry::d_Viewers                           );
   m_DefaultPriority._init                   (classID, 58, &coPtr, &OD_Registry::d_DefaultPriority                   );
   m_BannerStore_Expire._init                (classID, 59, &coPtr, &OD_Registry::d_BannerStore_Expire                );
   m_BannerStore_MaxLength._init             (classID, 60, &coPtr, &OD_Registry::d_BannerStore_MaxLength             );
   m_SiteStore_Expire._init                  (classID, 61, &coPtr, &OD_Registry::d_SiteStore_Expire                  );
   m_SiteStore_MaxLength._init               (classID, 62, &coPtr, &OD_Registry::d_SiteStore_MaxLength               );
   m_MaxDailyEventsDefault._init             (classID, 63, &coPtr, &OD_Registry::d_MaxDailyEventsDefault             );
   m_TagID1._init                            (classID, 64, &coPtr, &OD_Registry::d_TagID1                            );
   m_TagID2._init                            (classID, 65, &coPtr, &OD_Registry::d_TagID2                            );
   m_TagID3._init                            (classID, 66, &coPtr, &OD_Registry::d_TagID3                            );
   m_TagBool1._init                          (classID, 67, &coPtr, &OD_Registry::d_TagBool1                          );
   m_TagBool2._init                          (classID, 68, &coPtr, &OD_Registry::d_TagBool2                          );
   m_TagBool3._init                          (classID, 69, &coPtr, &OD_Registry::d_TagBool3                          );
   m_TagInt1._init                           (classID, 70, &coPtr, &OD_Registry::d_TagInt1                           );
   m_TagInt2._init                           (classID, 71, &coPtr, &OD_Registry::d_TagInt2                           );
   m_TagInt3._init                           (classID, 72, &coPtr, &OD_Registry::d_TagInt3                           );
   m_ReservedID1._init                       (classID, 73, &coPtr, &OD_Registry::d_ReservedID1                       );
   m_ReservedID2._init                       (classID, 74, &coPtr, &OD_Registry::d_ReservedID2                       );
   m_ReservedID3._init                       (classID, 75, &coPtr, &OD_Registry::d_ReservedID3                       );
   m_ReservedInt1._init                      (classID, 76, &coPtr, &OD_Registry::d_ReservedInt1                      );
   m_ReservedInt2._init                      (classID, 77, &coPtr, &OD_Registry::d_ReservedInt2                      );
   m_ReservedInt3._init                      (classID, 78, &coPtr, &OD_Registry::d_ReservedInt3                      );
   m_ReservedString1._init                   (classID, 79, &coPtr, &OD_Registry::d_ReservedString1                   );
   m_ReservedString2._init                   (classID, 80, &coPtr, &OD_Registry::d_ReservedString2                   );
   m_ReservedString3._init                   (classID, 81, &coPtr, &OD_Registry::d_ReservedString3                   );
}


// ===============================================================================
// VBN

// Конструктор по умолчанию
OC_VBN::OC_VBN ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_VBN::OC_VBN  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_VBN::OC_VBN  (const OC_VBN& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_VBN::~OC_VBN ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_VBN& OC_VBN::operator= (const OC_VBN& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_VBN& OC_VBN::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_VBN::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_VBN;
   m_Password._init              (classID, 1, &coPtr, &OD_VBN::d_Password              );
   m_Name._init                  (classID, 2, &coPtr, &OD_VBN::d_Name                  );
   m_Description._init           (classID, 3, &coPtr, &OD_VBN::d_Description           );
   m_IsModerated._init           (classID, 4, &coPtr, &OD_VBN::d_IsModerated           );
   m_DefaultLanguage._init       (classID, 5, &coPtr, &OD_VBN::d_DefaultLanguage       );
   m_DefaultTZOffset._init       (classID, 6, &coPtr, &OD_VBN::d_DefaultTZOffset       );
   m_Owner._init                 (classID, 7, &coPtr, &OD_VBN::d_Owner                 );
   m_ConceptMask._init           (classID, 8, &coPtr, &OD_VBN::d_ConceptMask           );
   m_AdminEventList._init        (classID, 9, &coPtr, &OD_VBN::d_AdminEventList        );
   m_No._init                    (classID, 10, &coPtr, &OD_VBN::d_No                    );
   m_OnlineVisitors._init        (classID, 11, &coPtr, &OD_VBN::d_OnlineVisitors        );
   m_ActiveViewersID._init       (classID, 12, &coPtr, &OD_VBN::d_ActiveViewersID       );
   m_ActiveViewersHosts._init    (classID, 13, &coPtr, &OD_VBN::d_ActiveViewersHosts    );
   m_Hits._init                  (classID, 14, &coPtr, &OD_VBN::d_Hits                  );
   m_Hosts._init                 (classID, 15, &coPtr, &OD_VBN::d_Hosts                 );
   m_Visitors._init              (classID, 16, &coPtr, &OD_VBN::d_Visitors              );
   m_Shows._init                 (classID, 17, &coPtr, &OD_VBN::d_Shows                 );
   m_Clicks._init                (classID, 18, &coPtr, &OD_VBN::d_Clicks                );
   m_SessionTime._init           (classID, 19, &coPtr, &OD_VBN::d_SessionTime           );
   m_SessionNum._init            (classID, 20, &coPtr, &OD_VBN::d_SessionNum            );
   m_Total_Hosts._init           (classID, 21, &coPtr, &OD_VBN::d_Total_Hosts           );
   m_Total_Shows._init           (classID, 22, &coPtr, &OD_VBN::d_Total_Shows           );
   m_Total_Clicks._init          (classID, 23, &coPtr, &OD_VBN::d_Total_Clicks          );
   m_Total_Hits._init            (classID, 24, &coPtr, &OD_VBN::d_Total_Hits            );
   m_Total_Visitors._init        (classID, 25, &coPtr, &OD_VBN::d_Total_Visitors        );
   m_Total_VisitorReturns._init  (classID, 26, &coPtr, &OD_VBN::d_Total_VisitorReturns  );
   m_Total_AveSessionTime._init  (classID, 27, &coPtr, &OD_VBN::d_Total_AveSessionTime  );
   m_Total_AveReloadTime._init   (classID, 28, &coPtr, &OD_VBN::d_Total_AveReloadTime   );
   m_Total_AveReloadNum._init    (classID, 29, &coPtr, &OD_VBN::d_Total_AveReloadNum    );
   m_LM_Visitors._init           (classID, 30, &coPtr, &OD_VBN::d_LM_Visitors           );
   m_LM_VisitorReturns._init     (classID, 31, &coPtr, &OD_VBN::d_LM_VisitorReturns     );
   m_LM_VisitorReturns_Prc._init (classID, 32, &coPtr, &OD_VBN::d_LM_VisitorReturns_Prc );
   m_LM_Hosts._init              (classID, 33, &coPtr, &OD_VBN::d_LM_Hosts              );
   m_LM_Shows._init              (classID, 34, &coPtr, &OD_VBN::d_LM_Shows              );
   m_LM_Clicks._init             (classID, 35, &coPtr, &OD_VBN::d_LM_Clicks             );
   m_LM_Hits._init               (classID, 36, &coPtr, &OD_VBN::d_LM_Hits               );
   m_LM_AveSessionTime._init     (classID, 37, &coPtr, &OD_VBN::d_LM_AveSessionTime     );
   m_LM_AveReloadTime._init      (classID, 38, &coPtr, &OD_VBN::d_LM_AveReloadTime      );
   m_LM_AveReloadNum._init       (classID, 39, &coPtr, &OD_VBN::d_LM_AveReloadNum       );
   m_LW_Visitors._init           (classID, 40, &coPtr, &OD_VBN::d_LW_Visitors           );
   m_LW_VisitorReturns._init     (classID, 41, &coPtr, &OD_VBN::d_LW_VisitorReturns     );
   m_LW_VisitorReturns_Prc._init (classID, 42, &coPtr, &OD_VBN::d_LW_VisitorReturns_Prc );
   m_LW_Hosts._init              (classID, 43, &coPtr, &OD_VBN::d_LW_Hosts              );
   m_LW_Shows._init              (classID, 44, &coPtr, &OD_VBN::d_LW_Shows              );
   m_LW_Clicks._init             (classID, 45, &coPtr, &OD_VBN::d_LW_Clicks             );
   m_LW_Hits._init               (classID, 46, &coPtr, &OD_VBN::d_LW_Hits               );
   m_LW_AveSessionTime._init     (classID, 47, &coPtr, &OD_VBN::d_LW_AveSessionTime     );
   m_LW_AveReloadTime._init      (classID, 48, &coPtr, &OD_VBN::d_LW_AveReloadTime      );
   m_LW_AveReloadNum._init       (classID, 49, &coPtr, &OD_VBN::d_LW_AveReloadNum       );
   m_LD_Visitors._init           (classID, 50, &coPtr, &OD_VBN::d_LD_Visitors           );
   m_LD_VisitorReturns._init     (classID, 51, &coPtr, &OD_VBN::d_LD_VisitorReturns     );
   m_LD_VisitorReturns_Prc._init (classID, 52, &coPtr, &OD_VBN::d_LD_VisitorReturns_Prc );
   m_LD_Hosts._init              (classID, 53, &coPtr, &OD_VBN::d_LD_Hosts              );
   m_LD_Shows._init              (classID, 54, &coPtr, &OD_VBN::d_LD_Shows              );
   m_LD_Clicks._init             (classID, 55, &coPtr, &OD_VBN::d_LD_Clicks             );
   m_LD_Hits._init               (classID, 56, &coPtr, &OD_VBN::d_LD_Hits               );
   m_LD_AveSessionTime._init     (classID, 57, &coPtr, &OD_VBN::d_LD_AveSessionTime     );
   m_LD_AveReloadTime._init      (classID, 58, &coPtr, &OD_VBN::d_LD_AveReloadTime      );
   m_LD_AveReloadNum._init       (classID, 59, &coPtr, &OD_VBN::d_LD_AveReloadNum       );
   m_LH_Visitors._init           (classID, 60, &coPtr, &OD_VBN::d_LH_Visitors           );
   m_LH_VisitorReturns._init     (classID, 61, &coPtr, &OD_VBN::d_LH_VisitorReturns     );
   m_LH_VisitorReturns_Prc._init (classID, 62, &coPtr, &OD_VBN::d_LH_VisitorReturns_Prc );
   m_LH_Hosts._init              (classID, 63, &coPtr, &OD_VBN::d_LH_Hosts              );
   m_LH_Shows._init              (classID, 64, &coPtr, &OD_VBN::d_LH_Shows              );
   m_LH_Clicks._init             (classID, 65, &coPtr, &OD_VBN::d_LH_Clicks             );
   m_LH_Hits._init               (classID, 66, &coPtr, &OD_VBN::d_LH_Hits               );
   m_LH_AveSessionTime._init     (classID, 67, &coPtr, &OD_VBN::d_LH_AveSessionTime     );
   m_LH_AveReloadTime._init      (classID, 68, &coPtr, &OD_VBN::d_LH_AveReloadTime      );
   m_LH_AveReloadNum._init       (classID, 69, &coPtr, &OD_VBN::d_LH_AveReloadNum       );
   m_TagBool1._init              (classID, 70, &coPtr, &OD_VBN::d_TagBool1              );
   m_TagBool2._init              (classID, 71, &coPtr, &OD_VBN::d_TagBool2              );
   m_TagID1._init                (classID, 72, &coPtr, &OD_VBN::d_TagID1                );
   m_TagID2._init                (classID, 73, &coPtr, &OD_VBN::d_TagID2                );
   m_TagInt1._init               (classID, 74, &coPtr, &OD_VBN::d_TagInt1               );
   m_TagInt2._init               (classID, 75, &coPtr, &OD_VBN::d_TagInt2               );
   m_TagFloat1._init             (classID, 76, &coPtr, &OD_VBN::d_TagFloat1             );
   m_TagFloat2._init             (classID, 77, &coPtr, &OD_VBN::d_TagFloat2             );
   m_TagString1._init            (classID, 78, &coPtr, &OD_VBN::d_TagString1            );
   m_TagString2._init            (classID, 79, &coPtr, &OD_VBN::d_TagString2            );
   m_ReservedID1._init           (classID, 80, &coPtr, &OD_VBN::d_ReservedID1           );
   m_ReservedID2._init           (classID, 81, &coPtr, &OD_VBN::d_ReservedID2           );
   m_ReservedInt1._init          (classID, 82, &coPtr, &OD_VBN::d_ReservedInt1          );
   m_ReservedInt2._init          (classID, 83, &coPtr, &OD_VBN::d_ReservedInt2          );
   m_ReservedString1._init       (classID, 84, &coPtr, &OD_VBN::d_ReservedString1       );
   m_ReservedString2._init       (classID, 85, &coPtr, &OD_VBN::d_ReservedString2       );
   m_CacheTime._init             (classID, 86, &coPtr, &OD_VBN::d_CacheTime             );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_VBN::CopyDataFrom (OC_VBN& from)
{
   m_Password              = from.m_Password;
   m_Name                  = from.m_Name;
   m_Description           = from.m_Description;
   m_IsModerated           = from.m_IsModerated;
   m_DefaultLanguage       = from.m_DefaultLanguage;
   m_DefaultTZOffset       = from.m_DefaultTZOffset;
   m_Owner                 = from.m_Owner;
   m_ConceptMask           = from.m_ConceptMask;
   m_AdminEventList        = from.m_AdminEventList;
   m_No                    = from.m_No;
   m_OnlineVisitors        = from.m_OnlineVisitors;
   m_ActiveViewersID       = from.m_ActiveViewersID;
   m_ActiveViewersHosts    = from.m_ActiveViewersHosts;
   m_Hits                  = from.m_Hits;
   m_Hosts                 = from.m_Hosts;
   m_Visitors              = from.m_Visitors;
   m_Shows                 = from.m_Shows;
   m_Clicks                = from.m_Clicks;
   m_SessionTime           = from.m_SessionTime;
   m_SessionNum            = from.m_SessionNum;
   m_Total_Hosts           = from.m_Total_Hosts;
   m_Total_Shows           = from.m_Total_Shows;
   m_Total_Clicks          = from.m_Total_Clicks;
   m_Total_Hits            = from.m_Total_Hits;
   m_Total_Visitors        = from.m_Total_Visitors;
   m_Total_VisitorReturns  = from.m_Total_VisitorReturns;
   m_Total_AveSessionTime  = from.m_Total_AveSessionTime;
   m_Total_AveReloadTime   = from.m_Total_AveReloadTime;
   m_Total_AveReloadNum    = from.m_Total_AveReloadNum;
   m_LM_Visitors           = from.m_LM_Visitors;
   m_LM_VisitorReturns     = from.m_LM_VisitorReturns;
   m_LM_VisitorReturns_Prc = from.m_LM_VisitorReturns_Prc;
   m_LM_Hosts              = from.m_LM_Hosts;
   m_LM_Shows              = from.m_LM_Shows;
   m_LM_Clicks             = from.m_LM_Clicks;
   m_LM_Hits               = from.m_LM_Hits;
   m_LM_AveSessionTime     = from.m_LM_AveSessionTime;
   m_LM_AveReloadTime      = from.m_LM_AveReloadTime;
   m_LM_AveReloadNum       = from.m_LM_AveReloadNum;
   m_LW_Visitors           = from.m_LW_Visitors;
   m_LW_VisitorReturns     = from.m_LW_VisitorReturns;
   m_LW_VisitorReturns_Prc = from.m_LW_VisitorReturns_Prc;
   m_LW_Hosts              = from.m_LW_Hosts;
   m_LW_Shows              = from.m_LW_Shows;
   m_LW_Clicks             = from.m_LW_Clicks;
   m_LW_Hits               = from.m_LW_Hits;
   m_LW_AveSessionTime     = from.m_LW_AveSessionTime;
   m_LW_AveReloadTime      = from.m_LW_AveReloadTime;
   m_LW_AveReloadNum       = from.m_LW_AveReloadNum;
   m_LD_Visitors           = from.m_LD_Visitors;
   m_LD_VisitorReturns     = from.m_LD_VisitorReturns;
   m_LD_VisitorReturns_Prc = from.m_LD_VisitorReturns_Prc;
   m_LD_Hosts              = from.m_LD_Hosts;
   m_LD_Shows              = from.m_LD_Shows;
   m_LD_Clicks             = from.m_LD_Clicks;
   m_LD_Hits               = from.m_LD_Hits;
   m_LD_AveSessionTime     = from.m_LD_AveSessionTime;
   m_LD_AveReloadTime      = from.m_LD_AveReloadTime;
   m_LD_AveReloadNum       = from.m_LD_AveReloadNum;
   m_LH_Visitors           = from.m_LH_Visitors;
   m_LH_VisitorReturns     = from.m_LH_VisitorReturns;
   m_LH_VisitorReturns_Prc = from.m_LH_VisitorReturns_Prc;
   m_LH_Hosts              = from.m_LH_Hosts;
   m_LH_Shows              = from.m_LH_Shows;
   m_LH_Clicks             = from.m_LH_Clicks;
   m_LH_Hits               = from.m_LH_Hits;
   m_LH_AveSessionTime     = from.m_LH_AveSessionTime;
   m_LH_AveReloadTime      = from.m_LH_AveReloadTime;
   m_LH_AveReloadNum       = from.m_LH_AveReloadNum;
   m_TagBool1              = from.m_TagBool1;
   m_TagBool2              = from.m_TagBool2;
   m_TagID1                = from.m_TagID1;
   m_TagID2                = from.m_TagID2;
   m_TagInt1               = from.m_TagInt1;
   m_TagInt2               = from.m_TagInt2;
   m_TagFloat1             = from.m_TagFloat1;
   m_TagFloat2             = from.m_TagFloat2;
   m_TagString1            = from.m_TagString1;
   m_TagString2            = from.m_TagString2;
   m_ReservedID1           = from.m_ReservedID1;
   m_ReservedID2           = from.m_ReservedID2;
   m_ReservedInt1          = from.m_ReservedInt1;
   m_ReservedInt2          = from.m_ReservedInt2;
   m_ReservedString1       = from.m_ReservedString1;
   m_ReservedString2       = from.m_ReservedString2;
   m_CacheTime             = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_VBN::CopyDataTo (OC_VBN& to)
{
   to.m_Password              = m_Password;
   to.m_Name                  = m_Name;
   to.m_Description           = m_Description;
   to.m_IsModerated           = m_IsModerated;
   to.m_DefaultLanguage       = m_DefaultLanguage;
   to.m_DefaultTZOffset       = m_DefaultTZOffset;
   to.m_Owner                 = m_Owner;
   to.m_ConceptMask           = m_ConceptMask;
   to.m_AdminEventList        = m_AdminEventList;
   to.m_No                    = m_No;
   to.m_OnlineVisitors        = m_OnlineVisitors;
   to.m_ActiveViewersID       = m_ActiveViewersID;
   to.m_ActiveViewersHosts    = m_ActiveViewersHosts;
   to.m_Hits                  = m_Hits;
   to.m_Hosts                 = m_Hosts;
   to.m_Visitors              = m_Visitors;
   to.m_Shows                 = m_Shows;
   to.m_Clicks                = m_Clicks;
   to.m_SessionTime           = m_SessionTime;
   to.m_SessionNum            = m_SessionNum;
   to.m_Total_Hosts           = m_Total_Hosts;
   to.m_Total_Shows           = m_Total_Shows;
   to.m_Total_Clicks          = m_Total_Clicks;
   to.m_Total_Hits            = m_Total_Hits;
   to.m_Total_Visitors        = m_Total_Visitors;
   to.m_Total_VisitorReturns  = m_Total_VisitorReturns;
   to.m_Total_AveSessionTime  = m_Total_AveSessionTime;
   to.m_Total_AveReloadTime   = m_Total_AveReloadTime;
   to.m_Total_AveReloadNum    = m_Total_AveReloadNum;
   to.m_LM_Visitors           = m_LM_Visitors;
   to.m_LM_VisitorReturns     = m_LM_VisitorReturns;
   to.m_LM_VisitorReturns_Prc = m_LM_VisitorReturns_Prc;
   to.m_LM_Hosts              = m_LM_Hosts;
   to.m_LM_Shows              = m_LM_Shows;
   to.m_LM_Clicks             = m_LM_Clicks;
   to.m_LM_Hits               = m_LM_Hits;
   to.m_LM_AveSessionTime     = m_LM_AveSessionTime;
   to.m_LM_AveReloadTime      = m_LM_AveReloadTime;
   to.m_LM_AveReloadNum       = m_LM_AveReloadNum;
   to.m_LW_Visitors           = m_LW_Visitors;
   to.m_LW_VisitorReturns     = m_LW_VisitorReturns;
   to.m_LW_VisitorReturns_Prc = m_LW_VisitorReturns_Prc;
   to.m_LW_Hosts              = m_LW_Hosts;
   to.m_LW_Shows              = m_LW_Shows;
   to.m_LW_Clicks             = m_LW_Clicks;
   to.m_LW_Hits               = m_LW_Hits;
   to.m_LW_AveSessionTime     = m_LW_AveSessionTime;
   to.m_LW_AveReloadTime      = m_LW_AveReloadTime;
   to.m_LW_AveReloadNum       = m_LW_AveReloadNum;
   to.m_LD_Visitors           = m_LD_Visitors;
   to.m_LD_VisitorReturns     = m_LD_VisitorReturns;
   to.m_LD_VisitorReturns_Prc = m_LD_VisitorReturns_Prc;
   to.m_LD_Hosts              = m_LD_Hosts;
   to.m_LD_Shows              = m_LD_Shows;
   to.m_LD_Clicks             = m_LD_Clicks;
   to.m_LD_Hits               = m_LD_Hits;
   to.m_LD_AveSessionTime     = m_LD_AveSessionTime;
   to.m_LD_AveReloadTime      = m_LD_AveReloadTime;
   to.m_LD_AveReloadNum       = m_LD_AveReloadNum;
   to.m_LH_Visitors           = m_LH_Visitors;
   to.m_LH_VisitorReturns     = m_LH_VisitorReturns;
   to.m_LH_VisitorReturns_Prc = m_LH_VisitorReturns_Prc;
   to.m_LH_Hosts              = m_LH_Hosts;
   to.m_LH_Shows              = m_LH_Shows;
   to.m_LH_Clicks             = m_LH_Clicks;
   to.m_LH_Hits               = m_LH_Hits;
   to.m_LH_AveSessionTime     = m_LH_AveSessionTime;
   to.m_LH_AveReloadTime      = m_LH_AveReloadTime;
   to.m_LH_AveReloadNum       = m_LH_AveReloadNum;
   to.m_TagBool1              = m_TagBool1;
   to.m_TagBool2              = m_TagBool2;
   to.m_TagID1                = m_TagID1;
   to.m_TagID2                = m_TagID2;
   to.m_TagInt1               = m_TagInt1;
   to.m_TagInt2               = m_TagInt2;
   to.m_TagFloat1             = m_TagFloat1;
   to.m_TagFloat2             = m_TagFloat2;
   to.m_TagString1            = m_TagString1;
   to.m_TagString2            = m_TagString2;
   to.m_ReservedID1           = m_ReservedID1;
   to.m_ReservedID2           = m_ReservedID2;
   to.m_ReservedInt1          = m_ReservedInt1;
   to.m_ReservedInt2          = m_ReservedInt2;
   to.m_ReservedString1       = m_ReservedString1;
   to.m_ReservedString2       = m_ReservedString2;
   to.m_CacheTime             = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_VBN&  OC_VBN::operator << (OC_VBN& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_VBN&  OC_VBN::operator >> (OC_VBN& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_VBN::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_No ();
              return oldIndex;
      case 1: SetIndex_Name ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_VBN::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_VBN::SetIndex_No ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
};

// Установить текущий индекс по полю
void OC_VBN::SetIndex_Name ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Language

// Конструктор по умолчанию
OC_Language::OC_Language ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Language::OC_Language  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Language::OC_Language  (const OC_Language& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Language::~OC_Language ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Language& OC_Language::operator= (const OC_Language& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Language& OC_Language::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Language::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Language;
   m_Name._init      (classID, 1, &coPtr, &OD_Language::d_Name      );
   m_ShortName._init (classID, 2, &coPtr, &OD_Language::d_ShortName );
   m_No._init        (classID, 3, &coPtr, &OD_Language::d_No        );
   m_CacheTime._init (classID, 4, &coPtr, &OD_Language::d_CacheTime );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Language::CopyDataFrom (OC_Language& from)
{
   m_Name      = from.m_Name;
   m_ShortName = from.m_ShortName;
   m_No        = from.m_No;
   m_CacheTime = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Language::CopyDataTo (OC_Language& to)
{
   to.m_Name      = m_Name;
   to.m_ShortName = m_ShortName;
   to.m_No        = m_No;
   to.m_CacheTime = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Language&  OC_Language::operator << (OC_Language& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Language&  OC_Language::operator >> (OC_Language& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Language::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_No ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Language::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Language::SetIndex_No ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Concept

// Конструктор по умолчанию
OC_Concept::OC_Concept ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Concept::OC_Concept  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Concept::OC_Concept  (const OC_Concept& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Concept::~OC_Concept ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Concept& OC_Concept::operator= (const OC_Concept& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Concept& OC_Concept::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Concept::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Concept;
   m_Name._init                 (classID, 1, &coPtr, &OD_Concept::d_Name                 );
   m_Description._init          (classID, 2, &coPtr, &OD_Concept::d_Description          );
   m_Parent._init               (classID, 3, &coPtr, &OD_Concept::d_Parent               );
   m_Ancestor._init             (classID, 4, &coPtr, &OD_Concept::d_Ancestor             );
   m_AncestorNo._init           (classID, 5, &coPtr, &OD_Concept::d_AncestorNo           );
   m_AncestorWeight._init       (classID, 6, &coPtr, &OD_Concept::d_AncestorWeight       );
   m_AllAncestor._init          (classID, 7, &coPtr, &OD_Concept::d_AllAncestor          );
   m_AllAncestorNo._init        (classID, 8, &coPtr, &OD_Concept::d_AllAncestorNo        );
   m_Child._init                (classID, 9, &coPtr, &OD_Concept::d_Child                );
   m_ChildNo._init              (classID, 10, &coPtr, &OD_Concept::d_ChildNo              );
   m_Descendant._init           (classID, 11, &coPtr, &OD_Concept::d_Descendant           );
   m_DescendantNo._init         (classID, 12, &coPtr, &OD_Concept::d_DescendantNo         );
   m_Level._init                (classID, 13, &coPtr, &OD_Concept::d_Level                );
   m_ShortName._init            (classID, 14, &coPtr, &OD_Concept::d_ShortName            );
   m_Type._init                 (classID, 15, &coPtr, &OD_Concept::d_Type                 );
   m_TypeNo._init               (classID, 16, &coPtr, &OD_Concept::d_TypeNo               );
   m_VBN_ID._init               (classID, 17, &coPtr, &OD_Concept::d_VBN_ID               );
   m_VBN_SiteList._init         (classID, 18, &coPtr, &OD_Concept::d_VBN_SiteList         );
   m_VBN_SiteListSize._init     (classID, 19, &coPtr, &OD_Concept::d_VBN_SiteListSize     );
   m_ClickerConcept_Work._init  (classID, 20, &coPtr, &OD_Concept::d_ClickerConcept_Work  );
   m_ClickerConcept_Home._init  (classID, 21, &coPtr, &OD_Concept::d_ClickerConcept_Home  );
   m_ClickerConcept_Night._init (classID, 22, &coPtr, &OD_Concept::d_ClickerConcept_Night );
   m_Ads_SiteID._init           (classID, 23, &coPtr, &OD_Concept::d_Ads_SiteID           );
   m_Ads_ShowRate._init         (classID, 24, &coPtr, &OD_Concept::d_Ads_ShowRate         );
   m_Ads_ClickRate._init        (classID, 25, &coPtr, &OD_Concept::d_Ads_ClickRate        );
   m_Ads_ViewRate._init         (classID, 26, &coPtr, &OD_Concept::d_Ads_ViewRate         );
   m_No._init                   (classID, 27, &coPtr, &OD_Concept::d_No                   );
   m_TagID._init                (classID, 28, &coPtr, &OD_Concept::d_TagID                );
   m_TagInt._init               (classID, 29, &coPtr, &OD_Concept::d_TagInt               );
   m_TagBool._init              (classID, 30, &coPtr, &OD_Concept::d_TagBool              );
   m_ReservedID._init           (classID, 31, &coPtr, &OD_Concept::d_ReservedID           );
   m_ReservedInt._init          (classID, 32, &coPtr, &OD_Concept::d_ReservedInt          );
   m_ReservedString._init       (classID, 33, &coPtr, &OD_Concept::d_ReservedString       );
   m_CacheTime._init            (classID, 34, &coPtr, &OD_Concept::d_CacheTime            );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Concept::CopyDataFrom (OC_Concept& from)
{
   m_Name                 = from.m_Name;
   m_Description          = from.m_Description;
   m_Parent               = from.m_Parent;
   m_Ancestor             = from.m_Ancestor;
   m_AncestorNo           = from.m_AncestorNo;
   m_AncestorWeight       = from.m_AncestorWeight;
   m_AllAncestor          = from.m_AllAncestor;
   m_AllAncestorNo        = from.m_AllAncestorNo;
   m_Child                = from.m_Child;
   m_ChildNo              = from.m_ChildNo;
   m_Descendant           = from.m_Descendant;
   m_DescendantNo         = from.m_DescendantNo;
   m_Level                = from.m_Level;
   m_ShortName            = from.m_ShortName;
   m_Type                 = from.m_Type;
   m_TypeNo               = from.m_TypeNo;
   m_VBN_ID               = from.m_VBN_ID;
   m_VBN_SiteList         = from.m_VBN_SiteList;
   m_VBN_SiteListSize     = from.m_VBN_SiteListSize;
   m_ClickerConcept_Work  = from.m_ClickerConcept_Work;
   m_ClickerConcept_Home  = from.m_ClickerConcept_Home;
   m_ClickerConcept_Night = from.m_ClickerConcept_Night;
   m_Ads_SiteID           = from.m_Ads_SiteID;
   m_Ads_ShowRate         = from.m_Ads_ShowRate;
   m_Ads_ClickRate        = from.m_Ads_ClickRate;
   m_Ads_ViewRate         = from.m_Ads_ViewRate;
   m_No                   = from.m_No;
   m_TagID                = from.m_TagID;
   m_TagInt               = from.m_TagInt;
   m_TagBool              = from.m_TagBool;
   m_ReservedID           = from.m_ReservedID;
   m_ReservedInt          = from.m_ReservedInt;
   m_ReservedString       = from.m_ReservedString;
   m_CacheTime            = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Concept::CopyDataTo (OC_Concept& to)
{
   to.m_Name                 = m_Name;
   to.m_Description          = m_Description;
   to.m_Parent               = m_Parent;
   to.m_Ancestor             = m_Ancestor;
   to.m_AncestorNo           = m_AncestorNo;
   to.m_AncestorWeight       = m_AncestorWeight;
   to.m_AllAncestor          = m_AllAncestor;
   to.m_AllAncestorNo        = m_AllAncestorNo;
   to.m_Child                = m_Child;
   to.m_ChildNo              = m_ChildNo;
   to.m_Descendant           = m_Descendant;
   to.m_DescendantNo         = m_DescendantNo;
   to.m_Level                = m_Level;
   to.m_ShortName            = m_ShortName;
   to.m_Type                 = m_Type;
   to.m_TypeNo               = m_TypeNo;
   to.m_VBN_ID               = m_VBN_ID;
   to.m_VBN_SiteList         = m_VBN_SiteList;
   to.m_VBN_SiteListSize     = m_VBN_SiteListSize;
   to.m_ClickerConcept_Work  = m_ClickerConcept_Work;
   to.m_ClickerConcept_Home  = m_ClickerConcept_Home;
   to.m_ClickerConcept_Night = m_ClickerConcept_Night;
   to.m_Ads_SiteID           = m_Ads_SiteID;
   to.m_Ads_ShowRate         = m_Ads_ShowRate;
   to.m_Ads_ClickRate        = m_Ads_ClickRate;
   to.m_Ads_ViewRate         = m_Ads_ViewRate;
   to.m_No                   = m_No;
   to.m_TagID                = m_TagID;
   to.m_TagInt               = m_TagInt;
   to.m_TagBool              = m_TagBool;
   to.m_ReservedID           = m_ReservedID;
   to.m_ReservedInt          = m_ReservedInt;
   to.m_ReservedString       = m_ReservedString;
   to.m_CacheTime            = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Concept&  OC_Concept::operator << (OC_Concept& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Concept&  OC_Concept::operator >> (OC_Concept& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Concept::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Level ();
              return oldIndex;
      case 1: SetIndex_No ();
              return oldIndex;
      case 2: SetIndex_Type_Level_ShortName ();
              return oldIndex;
      case 3: SetIndex_TypeNo ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Concept::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Concept::SetIndex_Level ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Concept::SetIndex_No ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Concept::SetIndex_Type_Level_ShortName ()
{
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
   curIndexInfo.m_keyType[2] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_Concept::SetIndex_TypeNo ()
{
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// SiteList

// Конструктор по умолчанию
OC_SiteList::OC_SiteList ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_SiteList::OC_SiteList  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_SiteList::OC_SiteList  (const OC_SiteList& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_SiteList::~OC_SiteList ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_SiteList& OC_SiteList::operator= (const OC_SiteList& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_SiteList& OC_SiteList::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_SiteList::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_SiteList;
   m_Site._init      (classID, 1, &coPtr, &OD_SiteList::d_Site      );
   m_CacheTime._init (classID, 2, &coPtr, &OD_SiteList::d_CacheTime );
}


// Копирование данных из другого контроллера
void OC_SiteList::CopyDataFrom (OC_SiteList& from)
{
   m_Site      = from.m_Site;
   m_CacheTime = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_SiteList::CopyDataTo (OC_SiteList& to)
{
   to.m_Site      = m_Site;
   to.m_CacheTime = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_SiteList&  OC_SiteList::operator << (OC_SiteList& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_SiteList&  OC_SiteList::operator >> (OC_SiteList& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// Keyword

// Конструктор по умолчанию
OC_Keyword::OC_Keyword ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Keyword::OC_Keyword  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Keyword::OC_Keyword  (const OC_Keyword& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Keyword::~OC_Keyword ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Keyword& OC_Keyword::operator= (const OC_Keyword& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Keyword& OC_Keyword::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Keyword::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Keyword;
   m_Word._init             (classID, 1, &coPtr, &OD_Keyword::d_Word             );
   m_VBN_ID._init           (classID, 2, &coPtr, &OD_Keyword::d_VBN_ID           );
   m_VBN_SiteList._init     (classID, 3, &coPtr, &OD_Keyword::d_VBN_SiteList     );
   m_VBN_SiteListSize._init (classID, 4, &coPtr, &OD_Keyword::d_VBN_SiteListSize );
   m_CacheTime._init        (classID, 5, &coPtr, &OD_Keyword::d_CacheTime        );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Keyword::CopyDataFrom (OC_Keyword& from)
{
   m_Word             = from.m_Word;
   m_VBN_ID           = from.m_VBN_ID;
   m_VBN_SiteList     = from.m_VBN_SiteList;
   m_VBN_SiteListSize = from.m_VBN_SiteListSize;
   m_CacheTime        = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Keyword::CopyDataTo (OC_Keyword& to)
{
   to.m_Word             = m_Word;
   to.m_VBN_ID           = m_VBN_ID;
   to.m_VBN_SiteList     = m_VBN_SiteList;
   to.m_VBN_SiteListSize = m_VBN_SiteListSize;
   to.m_CacheTime        = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Keyword&  OC_Keyword::operator << (OC_Keyword& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Keyword&  OC_Keyword::operator >> (OC_Keyword& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Keyword::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Word ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Keyword::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Keyword::SetIndex_Word ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// ModeratorComment

// Конструктор по умолчанию
OC_ModeratorComment::OC_ModeratorComment ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_ModeratorComment::OC_ModeratorComment  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_ModeratorComment::OC_ModeratorComment  (const OC_ModeratorComment& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_ModeratorComment::~OC_ModeratorComment ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_ModeratorComment& OC_ModeratorComment::operator= (const OC_ModeratorComment& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_ModeratorComment& OC_ModeratorComment::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_ModeratorComment::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_ModeratorComment;
   m_Name._init      (classID, 1, &coPtr, &OD_ModeratorComment::d_Name      );
   m_No._init        (classID, 2, &coPtr, &OD_ModeratorComment::d_No        );
   m_CacheTime._init (classID, 3, &coPtr, &OD_ModeratorComment::d_CacheTime );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_ModeratorComment::CopyDataFrom (OC_ModeratorComment& from)
{
   m_Name      = from.m_Name;
   m_No        = from.m_No;
   m_CacheTime = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_ModeratorComment::CopyDataTo (OC_ModeratorComment& to)
{
   to.m_Name      = m_Name;
   to.m_No        = m_No;
   to.m_CacheTime = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_ModeratorComment&  OC_ModeratorComment::operator << (OC_ModeratorComment& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_ModeratorComment&  OC_ModeratorComment::operator >> (OC_ModeratorComment& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_ModeratorComment::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_No ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_ModeratorComment::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_ModeratorComment::SetIndex_No ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// TimeStats

// Конструктор по умолчанию
OC_TimeStats::OC_TimeStats ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_TimeStats::OC_TimeStats  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_TimeStats::OC_TimeStats  (const OC_TimeStats& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_TimeStats::~OC_TimeStats ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_TimeStats& OC_TimeStats::operator= (const OC_TimeStats& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_TimeStats& OC_TimeStats::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_TimeStats::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_TimeStats;
   m_Total._init                         (classID, 1, &coPtr, &OD_TimeStats::d_Total                         );
   m_Year._init                          (classID, 2, &coPtr, &OD_TimeStats::d_Year                          );
   m_YearStats._init                     (classID, 3, &coPtr, &OD_TimeStats::d_YearStats                     );
   m_TwoLastDaysMinute._init             (classID, 4, &coPtr, &OD_TimeStats::d_TwoLastDaysMinute             );
   m_TwoLastDaysMinute_year._init        (classID, 5, &coPtr, &OD_TimeStats::d_TwoLastDaysMinute_year        );
   m_TwoLastDaysMinute_day_of_year._init (classID, 6, &coPtr, &OD_TimeStats::d_TwoLastDaysMinute_day_of_year );
   m_LastAccessTime._init                (classID, 7, &coPtr, &OD_TimeStats::d_LastAccessTime                );
   m_CacheTime._init                     (classID, 8, &coPtr, &OD_TimeStats::d_CacheTime                     );
}


// Копирование данных из другого контроллера
void OC_TimeStats::CopyDataFrom (OC_TimeStats& from)
{
   m_Total                         = from.m_Total;
   m_Year                          = from.m_Year;
   m_YearStats                     = from.m_YearStats;
   m_TwoLastDaysMinute             = from.m_TwoLastDaysMinute;
   m_TwoLastDaysMinute_year        = from.m_TwoLastDaysMinute_year;
   m_TwoLastDaysMinute_day_of_year = from.m_TwoLastDaysMinute_day_of_year;
   m_LastAccessTime                = from.m_LastAccessTime;
   m_CacheTime                     = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_TimeStats::CopyDataTo (OC_TimeStats& to)
{
   to.m_Total                         = m_Total;
   to.m_Year                          = m_Year;
   to.m_YearStats                     = m_YearStats;
   to.m_TwoLastDaysMinute             = m_TwoLastDaysMinute;
   to.m_TwoLastDaysMinute_year        = m_TwoLastDaysMinute_year;
   to.m_TwoLastDaysMinute_day_of_year = m_TwoLastDaysMinute_day_of_year;
   to.m_LastAccessTime                = m_LastAccessTime;
   to.m_CacheTime                     = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_TimeStats&  OC_TimeStats::operator << (OC_TimeStats& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_TimeStats&  OC_TimeStats::operator >> (OC_TimeStats& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// YearStats

// Конструктор по умолчанию
OC_YearStats::OC_YearStats ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_YearStats::OC_YearStats  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_YearStats::OC_YearStats  (const OC_YearStats& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_YearStats::~OC_YearStats ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_YearStats& OC_YearStats::operator= (const OC_YearStats& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_YearStats& OC_YearStats::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_YearStats::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_YearStats;
   m_DayTotal._init       (classID, 1, &coPtr, &OD_YearStats::d_DayTotal       );
   m_DayStats._init       (classID, 2, &coPtr, &OD_YearStats::d_DayStats       );
   m_LastAccessTime._init (classID, 3, &coPtr, &OD_YearStats::d_LastAccessTime );
   m_CacheTime._init      (classID, 4, &coPtr, &OD_YearStats::d_CacheTime      );
}


// Копирование данных из другого контроллера
void OC_YearStats::CopyDataFrom (OC_YearStats& from)
{
   m_DayTotal       = from.m_DayTotal;
   m_DayStats       = from.m_DayStats;
   m_LastAccessTime = from.m_LastAccessTime;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_YearStats::CopyDataTo (OC_YearStats& to)
{
   to.m_DayTotal       = m_DayTotal;
   to.m_DayStats       = m_DayStats;
   to.m_LastAccessTime = m_LastAccessTime;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_YearStats&  OC_YearStats::operator << (OC_YearStats& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_YearStats&  OC_YearStats::operator >> (OC_YearStats& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// DayStats

// Конструктор по умолчанию
OC_DayStats::OC_DayStats ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_DayStats::OC_DayStats  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_DayStats::OC_DayStats  (const OC_DayStats& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_DayStats::~OC_DayStats ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_DayStats& OC_DayStats::operator= (const OC_DayStats& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_DayStats& OC_DayStats::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_DayStats::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_DayStats;
   m_HourTotal._init      (classID, 1, &coPtr, &OD_DayStats::d_HourTotal      );
   m_LastAccessTime._init (classID, 2, &coPtr, &OD_DayStats::d_LastAccessTime );
   m_CacheTime._init      (classID, 3, &coPtr, &OD_DayStats::d_CacheTime      );
}


// Копирование данных из другого контроллера
void OC_DayStats::CopyDataFrom (OC_DayStats& from)
{
   m_HourTotal      = from.m_HourTotal;
   m_LastAccessTime = from.m_LastAccessTime;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_DayStats::CopyDataTo (OC_DayStats& to)
{
   to.m_HourTotal      = m_HourTotal;
   to.m_LastAccessTime = m_LastAccessTime;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_DayStats&  OC_DayStats::operator << (OC_DayStats& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_DayStats&  OC_DayStats::operator >> (OC_DayStats& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// Referrer

// Конструктор по умолчанию
OC_Referrer::OC_Referrer ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Referrer::OC_Referrer  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Referrer::OC_Referrer  (const OC_Referrer& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Referrer::~OC_Referrer ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Referrer& OC_Referrer::operator= (const OC_Referrer& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Referrer& OC_Referrer::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Referrer::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Referrer;
   m_CRC._init            (classID, 1, &coPtr, &OD_Referrer::d_CRC            );
   m_Referrer._init       (classID, 2, &coPtr, &OD_Referrer::d_Referrer       );
   m_Count._init          (classID, 3, &coPtr, &OD_Referrer::d_Count          );
   m_LastAccessTime._init (classID, 4, &coPtr, &OD_Referrer::d_LastAccessTime );
   m_CacheTime._init      (classID, 5, &coPtr, &OD_Referrer::d_CacheTime      );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Referrer::CopyDataFrom (OC_Referrer& from)
{
   m_CRC            = from.m_CRC;
   m_Referrer       = from.m_Referrer;
   m_Count          = from.m_Count;
   m_LastAccessTime = from.m_LastAccessTime;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_Referrer::CopyDataTo (OC_Referrer& to)
{
   to.m_CRC            = m_CRC;
   to.m_Referrer       = m_Referrer;
   to.m_Count          = m_Count;
   to.m_LastAccessTime = m_LastAccessTime;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Referrer&  OC_Referrer::operator << (OC_Referrer& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Referrer&  OC_Referrer::operator >> (OC_Referrer& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Referrer::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_CRC ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Referrer::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Referrer::SetIndex_CRC ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// DailyReferrerStats

// Конструктор по умолчанию
OC_DailyReferrerStats::OC_DailyReferrerStats ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_DailyReferrerStats::OC_DailyReferrerStats  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_DailyReferrerStats::OC_DailyReferrerStats  (const OC_DailyReferrerStats& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_DailyReferrerStats::~OC_DailyReferrerStats ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_DailyReferrerStats& OC_DailyReferrerStats::operator= (const OC_DailyReferrerStats& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_DailyReferrerStats& OC_DailyReferrerStats::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_DailyReferrerStats::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_DailyReferrerStats;
   m_SiteID._init    (classID, 1, &coPtr, &OD_DailyReferrerStats::d_SiteID    );
   m_Referrer._init  (classID, 2, &coPtr, &OD_DailyReferrerStats::d_Referrer  );
   m_Count._init     (classID, 3, &coPtr, &OD_DailyReferrerStats::d_Count     );
   m_TimeStamp._init (classID, 4, &coPtr, &OD_DailyReferrerStats::d_TimeStamp );
   m_CacheTime._init (classID, 5, &coPtr, &OD_DailyReferrerStats::d_CacheTime );
}


// Копирование данных из другого контроллера
void OC_DailyReferrerStats::CopyDataFrom (OC_DailyReferrerStats& from)
{
   m_SiteID    = from.m_SiteID;
   m_Referrer  = from.m_Referrer;
   m_Count     = from.m_Count;
   m_TimeStamp = from.m_TimeStamp;
   m_CacheTime = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_DailyReferrerStats::CopyDataTo (OC_DailyReferrerStats& to)
{
   to.m_SiteID    = m_SiteID;
   to.m_Referrer  = m_Referrer;
   to.m_Count     = m_Count;
   to.m_TimeStamp = m_TimeStamp;
   to.m_CacheTime = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_DailyReferrerStats&  OC_DailyReferrerStats::operator << (OC_DailyReferrerStats& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_DailyReferrerStats&  OC_DailyReferrerStats::operator >> (OC_DailyReferrerStats& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// SearchWordsInfo

// Конструктор по умолчанию
OC_SearchWordsInfo::OC_SearchWordsInfo ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_SearchWordsInfo::OC_SearchWordsInfo  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_SearchWordsInfo::OC_SearchWordsInfo  (const OC_SearchWordsInfo& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_SearchWordsInfo::~OC_SearchWordsInfo ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_SearchWordsInfo& OC_SearchWordsInfo::operator= (const OC_SearchWordsInfo& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_SearchWordsInfo& OC_SearchWordsInfo::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_SearchWordsInfo::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_SearchWordsInfo;
   m_SiteID._init         (classID, 1, &coPtr, &OD_SearchWordsInfo::d_SiteID         );
   m_Words._init          (classID, 2, &coPtr, &OD_SearchWordsInfo::d_Words          );
   m_Count._init          (classID, 3, &coPtr, &OD_SearchWordsInfo::d_Count          );
   m_LastAccessTime._init (classID, 4, &coPtr, &OD_SearchWordsInfo::d_LastAccessTime );
   m_CacheTime._init      (classID, 5, &coPtr, &OD_SearchWordsInfo::d_CacheTime      );
}


// Копирование данных из другого контроллера
void OC_SearchWordsInfo::CopyDataFrom (OC_SearchWordsInfo& from)
{
   m_SiteID         = from.m_SiteID;
   m_Words          = from.m_Words;
   m_Count          = from.m_Count;
   m_LastAccessTime = from.m_LastAccessTime;
   m_CacheTime      = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_SearchWordsInfo::CopyDataTo (OC_SearchWordsInfo& to)
{
   to.m_SiteID         = m_SiteID;
   to.m_Words          = m_Words;
   to.m_Count          = m_Count;
   to.m_LastAccessTime = m_LastAccessTime;
   to.m_CacheTime      = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_SearchWordsInfo&  OC_SearchWordsInfo::operator << (OC_SearchWordsInfo& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_SearchWordsInfo&  OC_SearchWordsInfo::operator >> (OC_SearchWordsInfo& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// SuspiciousInfo

// Конструктор по умолчанию
OC_SuspiciousInfo::OC_SuspiciousInfo ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_SuspiciousInfo::OC_SuspiciousInfo  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_SuspiciousInfo::OC_SuspiciousInfo  (const OC_SuspiciousInfo& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_SuspiciousInfo::~OC_SuspiciousInfo ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_SuspiciousInfo& OC_SuspiciousInfo::operator= (const OC_SuspiciousInfo& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_SuspiciousInfo& OC_SuspiciousInfo::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_SuspiciousInfo::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_SuspiciousInfo;
   m_Site._init      (classID, 1, &coPtr, &OD_SuspiciousInfo::d_Site      );
   m_Pointer._init   (classID, 2, &coPtr, &OD_SuspiciousInfo::d_Pointer   );
   m_Viewer._init    (classID, 3, &coPtr, &OD_SuspiciousInfo::d_Viewer    );
   m_Referrer._init  (classID, 4, &coPtr, &OD_SuspiciousInfo::d_Referrer  );
   m_Time._init      (classID, 5, &coPtr, &OD_SuspiciousInfo::d_Time      );
   m_EventType._init (classID, 6, &coPtr, &OD_SuspiciousInfo::d_EventType );
   m_CacheTime._init (classID, 7, &coPtr, &OD_SuspiciousInfo::d_CacheTime );
}


// Копирование данных из другого контроллера
void OC_SuspiciousInfo::CopyDataFrom (OC_SuspiciousInfo& from)
{
   m_Site      = from.m_Site;
   m_Pointer   = from.m_Pointer;
   m_Viewer    = from.m_Viewer;
   m_Referrer  = from.m_Referrer;
   m_Time      = from.m_Time;
   m_EventType = from.m_EventType;
   m_CacheTime = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_SuspiciousInfo::CopyDataTo (OC_SuspiciousInfo& to)
{
   to.m_Site      = m_Site;
   to.m_Pointer   = m_Pointer;
   to.m_Viewer    = m_Viewer;
   to.m_Referrer  = m_Referrer;
   to.m_Time      = m_Time;
   to.m_EventType = m_EventType;
   to.m_CacheTime = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_SuspiciousInfo&  OC_SuspiciousInfo::operator << (OC_SuspiciousInfo& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_SuspiciousInfo&  OC_SuspiciousInfo::operator >> (OC_SuspiciousInfo& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// RatingPlaceInfo

// Конструктор по умолчанию
OC_RatingPlaceInfo::OC_RatingPlaceInfo ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_RatingPlaceInfo::OC_RatingPlaceInfo  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_RatingPlaceInfo::OC_RatingPlaceInfo  (const OC_RatingPlaceInfo& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_RatingPlaceInfo::~OC_RatingPlaceInfo ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_RatingPlaceInfo& OC_RatingPlaceInfo::operator= (const OC_RatingPlaceInfo& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_RatingPlaceInfo& OC_RatingPlaceInfo::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_RatingPlaceInfo::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_RatingPlaceInfo;
   m_Site._init              (classID, 1, &coPtr, &OD_RatingPlaceInfo::d_Site              );
   m_LastHourPosition._init  (classID, 2, &coPtr, &OD_RatingPlaceInfo::d_LastHourPosition  );
   m_LHP_Pointer._init       (classID, 3, &coPtr, &OD_RatingPlaceInfo::d_LHP_Pointer       );
   m_LastDailyPosition._init (classID, 4, &coPtr, &OD_RatingPlaceInfo::d_LastDailyPosition );
   m_LDP_Pointer._init       (classID, 5, &coPtr, &OD_RatingPlaceInfo::d_LDP_Pointer       );
   m_LDP_UpdateTime._init    (classID, 6, &coPtr, &OD_RatingPlaceInfo::d_LDP_UpdateTime    );
   m_DailyPositionDiff._init (classID, 7, &coPtr, &OD_RatingPlaceInfo::d_DailyPositionDiff );
   m_CacheTime._init         (classID, 8, &coPtr, &OD_RatingPlaceInfo::d_CacheTime         );
}


// Копирование данных из другого контроллера
void OC_RatingPlaceInfo::CopyDataFrom (OC_RatingPlaceInfo& from)
{
   m_Site              = from.m_Site;
   m_LastHourPosition  = from.m_LastHourPosition;
   m_LHP_Pointer       = from.m_LHP_Pointer;
   m_LastDailyPosition = from.m_LastDailyPosition;
   m_LDP_Pointer       = from.m_LDP_Pointer;
   m_LDP_UpdateTime    = from.m_LDP_UpdateTime;
   m_DailyPositionDiff = from.m_DailyPositionDiff;
   m_CacheTime         = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_RatingPlaceInfo::CopyDataTo (OC_RatingPlaceInfo& to)
{
   to.m_Site              = m_Site;
   to.m_LastHourPosition  = m_LastHourPosition;
   to.m_LHP_Pointer       = m_LHP_Pointer;
   to.m_LastDailyPosition = m_LastDailyPosition;
   to.m_LDP_Pointer       = m_LDP_Pointer;
   to.m_LDP_UpdateTime    = m_LDP_UpdateTime;
   to.m_DailyPositionDiff = m_DailyPositionDiff;
   to.m_CacheTime         = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_RatingPlaceInfo&  OC_RatingPlaceInfo::operator << (OC_RatingPlaceInfo& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_RatingPlaceInfo&  OC_RatingPlaceInfo::operator >> (OC_RatingPlaceInfo& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// IPRecord

// Конструктор по умолчанию
OC_IPRecord::OC_IPRecord ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_IPRecord::OC_IPRecord  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_IPRecord::OC_IPRecord  (const OC_IPRecord& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_IPRecord::~OC_IPRecord ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_IPRecord& OC_IPRecord::operator= (const OC_IPRecord& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_IPRecord& OC_IPRecord::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_IPRecord::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_IPRecord;
   m_Count._init            (classID, 1, &coPtr, &OD_IPRecord::d_Count            );
   m_Mask._init             (classID, 2, &coPtr, &OD_IPRecord::d_Mask             );
   m_First._init            (classID, 3, &coPtr, &OD_IPRecord::d_First            );
   m_Last._init             (classID, 4, &coPtr, &OD_IPRecord::d_Last             );
   m_Checked._init          (classID, 5, &coPtr, &OD_IPRecord::d_Checked          );
   m_ConceptID._init        (classID, 6, &coPtr, &OD_IPRecord::d_ConceptID        );
   m_ConceptNo._init        (classID, 7, &coPtr, &OD_IPRecord::d_ConceptNo        );
   m_CRA_Audience._init     (classID, 8, &coPtr, &OD_IPRecord::d_CRA_Audience     );
   m_CRA_Inquiry._init      (classID, 9, &coPtr, &OD_IPRecord::d_CRA_Inquiry      );
   m_CacheTime._init        (classID, 10, &coPtr, &OD_IPRecord::d_CacheTime        );
   m_Hits._init             (classID, 11, &coPtr, &OD_IPRecord::d_Hits             );
   m_Hosts._init            (classID, 12, &coPtr, &OD_IPRecord::d_Hosts            );
   m_Visitors._init         (classID, 13, &coPtr, &OD_IPRecord::d_Visitors         );
   m_Anonymous._init        (classID, 14, &coPtr, &OD_IPRecord::d_Anonymous        );
   m_Suspicious._init       (classID, 15, &coPtr, &OD_IPRecord::d_Suspicious       );
   m_Total_Hits._init       (classID, 16, &coPtr, &OD_IPRecord::d_Total_Hits       );
   m_Total_Hosts._init      (classID, 17, &coPtr, &OD_IPRecord::d_Total_Hosts      );
   m_Total_Visitors._init   (classID, 18, &coPtr, &OD_IPRecord::d_Total_Visitors   );
   m_Total_Anonymous._init  (classID, 19, &coPtr, &OD_IPRecord::d_Total_Anonymous  );
   m_Total_Suspicious._init (classID, 20, &coPtr, &OD_IPRecord::d_Total_Suspicious );
   m_LM_Hits._init          (classID, 21, &coPtr, &OD_IPRecord::d_LM_Hits          );
   m_LM_Hosts._init         (classID, 22, &coPtr, &OD_IPRecord::d_LM_Hosts         );
   m_LM_Visitors._init      (classID, 23, &coPtr, &OD_IPRecord::d_LM_Visitors      );
   m_LM_Anonymous._init     (classID, 24, &coPtr, &OD_IPRecord::d_LM_Anonymous     );
   m_LM_Suspicious._init    (classID, 25, &coPtr, &OD_IPRecord::d_LM_Suspicious    );
   m_LW_Hits._init          (classID, 26, &coPtr, &OD_IPRecord::d_LW_Hits          );
   m_LW_Hosts._init         (classID, 27, &coPtr, &OD_IPRecord::d_LW_Hosts         );
   m_LW_Visitors._init      (classID, 28, &coPtr, &OD_IPRecord::d_LW_Visitors      );
   m_LW_Anonymous._init     (classID, 29, &coPtr, &OD_IPRecord::d_LW_Anonymous     );
   m_LW_Suspicious._init    (classID, 30, &coPtr, &OD_IPRecord::d_LW_Suspicious    );
   m_LD_Hits._init          (classID, 31, &coPtr, &OD_IPRecord::d_LD_Hits          );
   m_LD_Hosts._init         (classID, 32, &coPtr, &OD_IPRecord::d_LD_Hosts         );
   m_LD_Visitors._init      (classID, 33, &coPtr, &OD_IPRecord::d_LD_Visitors      );
   m_LD_Anonymous._init     (classID, 34, &coPtr, &OD_IPRecord::d_LD_Anonymous     );
   m_LD_Suspicious._init    (classID, 35, &coPtr, &OD_IPRecord::d_LD_Suspicious    );
   m_LH_Hits._init          (classID, 36, &coPtr, &OD_IPRecord::d_LH_Hits          );
   m_LH_Hosts._init         (classID, 37, &coPtr, &OD_IPRecord::d_LH_Hosts         );
   m_LH_Visitors._init      (classID, 38, &coPtr, &OD_IPRecord::d_LH_Visitors      );
   m_LH_Anonymous._init     (classID, 39, &coPtr, &OD_IPRecord::d_LH_Anonymous     );
   m_LH_Suspicious._init    (classID, 40, &coPtr, &OD_IPRecord::d_LH_Suspicious    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_IPRecord::CopyDataFrom (OC_IPRecord& from)
{
   m_Count            = from.m_Count;
   m_Mask             = from.m_Mask;
   m_First            = from.m_First;
   m_Last             = from.m_Last;
   m_Checked          = from.m_Checked;
   m_ConceptID        = from.m_ConceptID;
   m_ConceptNo        = from.m_ConceptNo;
   m_CRA_Audience     = from.m_CRA_Audience;
   m_CRA_Inquiry      = from.m_CRA_Inquiry;
   m_CacheTime        = from.m_CacheTime;
   m_Hits             = from.m_Hits;
   m_Hosts            = from.m_Hosts;
   m_Visitors         = from.m_Visitors;
   m_Anonymous        = from.m_Anonymous;
   m_Suspicious       = from.m_Suspicious;
   m_Total_Hits       = from.m_Total_Hits;
   m_Total_Hosts      = from.m_Total_Hosts;
   m_Total_Visitors   = from.m_Total_Visitors;
   m_Total_Anonymous  = from.m_Total_Anonymous;
   m_Total_Suspicious = from.m_Total_Suspicious;
   m_LM_Hits          = from.m_LM_Hits;
   m_LM_Hosts         = from.m_LM_Hosts;
   m_LM_Visitors      = from.m_LM_Visitors;
   m_LM_Anonymous     = from.m_LM_Anonymous;
   m_LM_Suspicious    = from.m_LM_Suspicious;
   m_LW_Hits          = from.m_LW_Hits;
   m_LW_Hosts         = from.m_LW_Hosts;
   m_LW_Visitors      = from.m_LW_Visitors;
   m_LW_Anonymous     = from.m_LW_Anonymous;
   m_LW_Suspicious    = from.m_LW_Suspicious;
   m_LD_Hits          = from.m_LD_Hits;
   m_LD_Hosts         = from.m_LD_Hosts;
   m_LD_Visitors      = from.m_LD_Visitors;
   m_LD_Anonymous     = from.m_LD_Anonymous;
   m_LD_Suspicious    = from.m_LD_Suspicious;
   m_LH_Hits          = from.m_LH_Hits;
   m_LH_Hosts         = from.m_LH_Hosts;
   m_LH_Visitors      = from.m_LH_Visitors;
   m_LH_Anonymous     = from.m_LH_Anonymous;
   m_LH_Suspicious    = from.m_LH_Suspicious;
}


// Копирование данных в другой контроллер
void OC_IPRecord::CopyDataTo (OC_IPRecord& to)
{
   to.m_Count            = m_Count;
   to.m_Mask             = m_Mask;
   to.m_First            = m_First;
   to.m_Last             = m_Last;
   to.m_Checked          = m_Checked;
   to.m_ConceptID        = m_ConceptID;
   to.m_ConceptNo        = m_ConceptNo;
   to.m_CRA_Audience     = m_CRA_Audience;
   to.m_CRA_Inquiry      = m_CRA_Inquiry;
   to.m_CacheTime        = m_CacheTime;
   to.m_Hits             = m_Hits;
   to.m_Hosts            = m_Hosts;
   to.m_Visitors         = m_Visitors;
   to.m_Anonymous        = m_Anonymous;
   to.m_Suspicious       = m_Suspicious;
   to.m_Total_Hits       = m_Total_Hits;
   to.m_Total_Hosts      = m_Total_Hosts;
   to.m_Total_Visitors   = m_Total_Visitors;
   to.m_Total_Anonymous  = m_Total_Anonymous;
   to.m_Total_Suspicious = m_Total_Suspicious;
   to.m_LM_Hits          = m_LM_Hits;
   to.m_LM_Hosts         = m_LM_Hosts;
   to.m_LM_Visitors      = m_LM_Visitors;
   to.m_LM_Anonymous     = m_LM_Anonymous;
   to.m_LM_Suspicious    = m_LM_Suspicious;
   to.m_LW_Hits          = m_LW_Hits;
   to.m_LW_Hosts         = m_LW_Hosts;
   to.m_LW_Visitors      = m_LW_Visitors;
   to.m_LW_Anonymous     = m_LW_Anonymous;
   to.m_LW_Suspicious    = m_LW_Suspicious;
   to.m_LD_Hits          = m_LD_Hits;
   to.m_LD_Hosts         = m_LD_Hosts;
   to.m_LD_Visitors      = m_LD_Visitors;
   to.m_LD_Anonymous     = m_LD_Anonymous;
   to.m_LD_Suspicious    = m_LD_Suspicious;
   to.m_LH_Hits          = m_LH_Hits;
   to.m_LH_Hosts         = m_LH_Hosts;
   to.m_LH_Visitors      = m_LH_Visitors;
   to.m_LH_Anonymous     = m_LH_Anonymous;
   to.m_LH_Suspicious    = m_LH_Suspicious;
}

// Копирование данных из другого контроллера: to << from;
OC_IPRecord&  OC_IPRecord::operator << (OC_IPRecord& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_IPRecord&  OC_IPRecord::operator >> (OC_IPRecord& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_IPRecord::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Checked_Mask ();
              return oldIndex;
      case 1: SetIndex_Checked__Count ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_IPRecord::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_IPRecord::SetIndex_Checked_Mask ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_bool; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_IPRecord::SetIndex_Checked__Count ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_bool; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// ViewerReference

// Конструктор по умолчанию
OC_ViewerReference::OC_ViewerReference ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_ViewerReference::OC_ViewerReference  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_ViewerReference::OC_ViewerReference  (const OC_ViewerReference& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_ViewerReference::~OC_ViewerReference ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_ViewerReference& OC_ViewerReference::operator= (const OC_ViewerReference& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_ViewerReference& OC_ViewerReference::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_ViewerReference::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_ViewerReference;
   m_ViewerID._init      (classID, 1, &coPtr, &OD_ViewerReference::d_ViewerID      );
   m_IPAddress._init     (classID, 2, &coPtr, &OD_ViewerReference::d_IPAddress     );
   m_IPAddressHash._init (classID, 3, &coPtr, &OD_ViewerReference::d_IPAddressHash );
   m_CacheTime._init     (classID, 4, &coPtr, &OD_ViewerReference::d_CacheTime     );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_ViewerReference::CopyDataFrom (OC_ViewerReference& from)
{
   m_ViewerID      = from.m_ViewerID;
   m_IPAddress     = from.m_IPAddress;
   m_IPAddressHash = from.m_IPAddressHash;
   m_CacheTime     = from.m_CacheTime;
}


// Копирование данных в другой контроллер
void OC_ViewerReference::CopyDataTo (OC_ViewerReference& to)
{
   to.m_ViewerID      = m_ViewerID;
   to.m_IPAddress     = m_IPAddress;
   to.m_IPAddressHash = m_IPAddressHash;
   to.m_CacheTime     = m_CacheTime;
}

// Копирование данных из другого контроллера: to << from;
OC_ViewerReference&  OC_ViewerReference::operator << (OC_ViewerReference& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_ViewerReference&  OC_ViewerReference::operator >> (OC_ViewerReference& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_ViewerReference::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_IPAddressHash ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_ViewerReference::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_ViewerReference::SetIndex_IPAddressHash ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// AbstractObject

// Конструктор по умолчанию
OC_AbstractObject::OC_AbstractObject ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_AbstractObject::OC_AbstractObject  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_AbstractObject::OC_AbstractObject  (const OC_AbstractObject& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_AbstractObject::~OC_AbstractObject ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_AbstractObject& OC_AbstractObject::operator= (const OC_AbstractObject& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_AbstractObject& OC_AbstractObject::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_AbstractObject::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_AbstractObject;
   m_Type._init    (classID, 1, &coPtr, &OD_AbstractObject::d_Type    );
   m_Name._init    (classID, 2, &coPtr, &OD_AbstractObject::d_Name    );
   m_Header1._init (classID, 3, &coPtr, &OD_AbstractObject::d_Header1 );
   m_Header2._init (classID, 4, &coPtr, &OD_AbstractObject::d_Header2 );
   m_Header3._init (classID, 5, &coPtr, &OD_AbstractObject::d_Header3 );
   m_Body._init    (classID, 6, &coPtr, &OD_AbstractObject::d_Body    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_AbstractObject::CopyDataFrom (OC_AbstractObject& from)
{
   m_Type    = from.m_Type;
   m_Name    = from.m_Name;
   m_Header1 = from.m_Header1;
   m_Header2 = from.m_Header2;
   m_Header3 = from.m_Header3;
   m_Body    = from.m_Body;
}


// Копирование данных в другой контроллер
void OC_AbstractObject::CopyDataTo (OC_AbstractObject& to)
{
   to.m_Type    = m_Type;
   to.m_Name    = m_Name;
   to.m_Header1 = m_Header1;
   to.m_Header2 = m_Header2;
   to.m_Header3 = m_Header3;
   to.m_Body    = m_Body;
}

// Копирование данных из другого контроллера: to << from;
OC_AbstractObject&  OC_AbstractObject::operator << (OC_AbstractObject& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_AbstractObject&  OC_AbstractObject::operator >> (OC_AbstractObject& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_AbstractObject::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Type_Name_Header1_Header2_Header3 ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_AbstractObject::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_AbstractObject::SetIndex_Type_Name_Header1_Header2_Header3 ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 5; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
   curIndexInfo.m_keyType[2] = (byte)FT_string; 
   curIndexInfo.m_keyType[3] = (byte)FT_string; 
   curIndexInfo.m_keyType[4] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
