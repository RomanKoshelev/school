/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjController.h                                       []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Controlers for database objects                           []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/

#ifndef Lay_ObjController_h
#define Lay_ObjController_h


#include "./../bcc/main.h"
#include "./../bcc/OBD.h"
#include "./../bcc/Object.h"
#include "Lay_ObjData.h"








#ifdef  USES_OC_ALL
#define USES_OC_Viewer
#endif
#ifdef USES_OC_Viewer
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Viewer"
// 
class OC_Viewer: public OC_Object <OC_Viewer>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Viewer  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Viewer  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Viewer  (const OC_Viewer& from);
// Деструктор контроллера объекта
   public: ~OC_Viewer ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Viewer& operator= (const OC_Viewer& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Viewer& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Viewer& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Viewer& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Viewer& operator << (OC_Viewer& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Viewer& operator >> (OC_Viewer& from);

// Поле:   identifier Viewer::Reference
   public: CSmartField      <OD_Viewer, identifier >    m_Reference;
// Поле:   string Viewer::Name
   public: CSmartField      <OD_Viewer, string     >    m_Name;
// Поле:   string Viewer::Email
   public: CSmartField      <OD_Viewer, string     >    m_Email;
// Поле:   string Viewer::UserAgent
   public: CSmartField      <OD_Viewer, string     >    m_UserAgent;
// Поле:   bool Viewer::Anonymous
   public: CSmartField      <OD_Viewer, bool       >    m_Anonymous;
// Поле:   int Viewer::TotalShows
   public: CSmartField      <OD_Viewer, int        >    m_TotalShows;
// Поле:   int Viewer::TotalClicks
   public: CSmartField      <OD_Viewer, int        >    m_TotalClicks;
// Поле:   string Viewer::IPAddress
   public: CSmartField      <OD_Viewer, string     >    m_IPAddress;
// Поле:   string Viewer::Referrer
   public: CSmartField      <OD_Viewer, string     >    m_Referrer;
// Поле:   identifier Viewer::IPAddressHash
   public: CSmartField      <OD_Viewer, identifier >    m_IPAddressHash;
// Поле:   int Viewer::CRN_Site_Update
   public: CSmartField      <OD_Viewer, int        >    m_CRN_Site_Update;
// Поле:   identifier Viewer::Group
   public: CSmartField      <OD_Viewer, identifier >    m_Group;
// Поле:   int Viewer::TZOffset
   public: CSmartField      <OD_Viewer, int        >    m_TZOffset;
// Поле:   int Viewer::CreationTime
   public: CSmartField      <OD_Viewer, int        >    m_CreationTime;
// Поле:   int Viewer::LastVisitTime
   public: CSmartField      <OD_Viewer, int        >    m_LastVisitTime;
// Поле:   int Viewer::TotalHosts
   public: CSmartField      <OD_Viewer, int        >    m_TotalHosts;
// Поле:   identifier Viewer::Site_SessionLastSiteID
   public: CSmartField      <OD_Viewer, identifier >    m_Site_SessionLastSiteID;
// Поле:   int Viewer::BannerClickTime
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickTime;
// Поле:   identifier Viewer::BannerClickID
   public: CSmartField      <OD_Viewer, identifier >    m_BannerClickID;
// Поле:   identifier Viewer::BannerClickSiteID
   public: CSmartField      <OD_Viewer, identifier >    m_BannerClickSiteID;
// Поле:   int Viewer::BannerClickHitCount
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickHitCount;
// Поле:   int Viewer::BannerClickSessionTime
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickSessionTime;
// Поле:   float Viewer::ReloadNum
   public: CSmartField      <OD_Viewer, float      >    m_ReloadNum;
// Поле:   float Viewer::AveReloadTime
   public: CSmartField      <OD_Viewer, float      >    m_AveReloadTime;
// Поле:   identifier Viewer::TagID
   public: CSmartField      <OD_Viewer, identifier >    m_TagID;
// Поле:   int Viewer::TagInt
   public: CSmartField      <OD_Viewer, int        >    m_TagInt;
// Поле:   bool Viewer::TagBool
   public: CSmartField      <OD_Viewer, bool       >    m_TagBool;
// Поле:   int Viewer::CacheTime
   public: CSmartField      <OD_Viewer, int        >    m_CacheTime;
// Поле:   int Viewer::CRA_Site []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Site;
// Поле:   int Viewer::CRN_Site []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Site;
// Поле:   int Viewer::CRA_Click []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Click;
// Поле:   int Viewer::CRN_Click []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Click;
// Поле:   identifier Viewer::Site []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_Site;
// Поле:   int Viewer::Site_LastHit []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_LastHit;
// Поле:   int Viewer::Site_Hits []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_Hits;
// Поле:   int Viewer::Site_LastHost []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_LastHost;
// Поле:   int Viewer::Site_Hosts []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_Hosts;
// Поле:   byte Viewer::Site_Votings []
   public: CSmartFieldArray <OD_Viewer, byte       >    m_Site_Votings;
// Поле:   byte Viewer::Site_VoteDayNo []
   public: CSmartFieldArray <OD_Viewer, byte       >    m_Site_VoteDayNo;
// Поле:   int Viewer::CRA_Inquiry []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Inquiry;
// Поле:   int Viewer::CRN_Inquiry []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Inquiry;
// Поле:   identifier Viewer::Banner []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_Banner;
// Поле:   int Viewer::Banner_LastViewed []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Banner_LastViewed;
// Поле:   int Viewer::Banner_ShowClick []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Banner_ShowClick;
// Поле:   identifier Viewer::ReservedID []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_ReservedID;
// Поле:   int Viewer::ReservedInt []
   public: CSmartFieldArray <OD_Viewer, int        >    m_ReservedInt;
// Поле:   string Viewer::ReservedString []
   public: CSmartFieldArray <OD_Viewer, string     >    m_ReservedString;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_ViewerGroup
#endif
#ifdef USES_OC_ViewerGroup
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "ViewerGroup"
// 
class OC_ViewerGroup: public OC_Object <OC_ViewerGroup>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_ViewerGroup  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_ViewerGroup  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_ViewerGroup  (const OC_ViewerGroup& from);
// Деструктор контроллера объекта
   public: ~OC_ViewerGroup ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ViewerGroup& operator= (const OC_ViewerGroup& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ViewerGroup& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_ViewerGroup& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_ViewerGroup& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_ViewerGroup& operator << (OC_ViewerGroup& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_ViewerGroup& operator >> (OC_ViewerGroup& from);

// Поле:   identifier ViewerGroup::TagID
   public: CSmartField      <OD_ViewerGroup, identifier >    m_TagID;
// Поле:   int ViewerGroup::TagInt
   public: CSmartField      <OD_ViewerGroup, int        >    m_TagInt;
// Поле:   bool ViewerGroup::TagBool
   public: CSmartField      <OD_ViewerGroup, bool       >    m_TagBool;
// Поле:   int ViewerGroup::CacheTime
   public: CSmartField      <OD_ViewerGroup, int        >    m_CacheTime;
// Поле:   int ViewerGroup::ConceptStats []
   public: CSmartFieldArray <OD_ViewerGroup, int        >    m_ConceptStats;
// Поле:   identifier ViewerGroup::Viewer []
   public: CSmartFieldArray <OD_ViewerGroup, identifier >    m_Viewer;
// Поле:   identifier ViewerGroup::ReservedID []
   public: CSmartFieldArray <OD_ViewerGroup, identifier >    m_ReservedID;
// Поле:   int ViewerGroup::ReservedInt []
   public: CSmartFieldArray <OD_ViewerGroup, int        >    m_ReservedInt;
// Поле:   string ViewerGroup::ReservedString []
   public: CSmartFieldArray <OD_ViewerGroup, string     >    m_ReservedString;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_User
#endif
#ifdef USES_OC_User
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "User"
// 
class OC_User: public OC_Object <OC_User>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_User  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_User  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_User  (const OC_User& from);
// Деструктор контроллера объекта
   public: ~OC_User ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_User& operator= (const OC_User& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_User& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_User& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_User& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_User& operator << (OC_User& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_User& operator >> (OC_User& from);

// Поле:   string User::Login
   public: CSmartField      <OD_User, string     >    m_Login;
// Поле:   string User::Password
   public: CSmartField      <OD_User, string     >    m_Password;
// Поле:   bool User::ForgetPassword
   public: CSmartField      <OD_User, bool       >    m_ForgetPassword;
// Поле:   string User::FullName
   public: CSmartField      <OD_User, string     >    m_FullName;
// Поле:   identifier User::InterfaceLanguage
   public: CSmartField      <OD_User, identifier >    m_InterfaceLanguage;
// Поле:   bool User::InterfaceType
   public: CSmartField      <OD_User, bool       >    m_InterfaceType;
// Поле:   int User::CreationTime
   public: CSmartField      <OD_User, int        >    m_CreationTime;
// Поле:   byte User::VBN
   public: CSmartField      <OD_User, byte       >    m_VBN;
// Поле:   string User::Email
   public: CSmartField      <OD_User, string     >    m_Email;
// Поле:   string User::Phone
   public: CSmartField      <OD_User, string     >    m_Phone;
// Поле:   string User::Fax
   public: CSmartField      <OD_User, string     >    m_Fax;
// Поле:   string User::Address
   public: CSmartField      <OD_User, string     >    m_Address;
// Поле:   string User::URL
   public: CSmartField      <OD_User, string     >    m_URL;
// Поле:   string User::Comment
   public: CSmartField      <OD_User, string     >    m_Comment;
// Поле:   int User::TZOffset
   public: CSmartField      <OD_User, int        >    m_TZOffset;
// Поле:   int User::NotifyFreq
   public: CSmartField      <OD_User, int        >    m_NotifyFreq;
// Поле:   bool User::NotifyHTML
   public: CSmartField      <OD_User, bool       >    m_NotifyHTML;
// Поле:   int User::NotifyDepth
   public: CSmartField      <OD_User, int        >    m_NotifyDepth;
// Поле:   float User::ShowsLeft
   public: CSmartField      <OD_User, float      >    m_ShowsLeft;
// Поле:   float User::ClicksLeft
   public: CSmartField      <OD_User, float      >    m_ClicksLeft;
// Поле:   identifier User::TradeStats
   public: CSmartField      <OD_User, identifier >    m_TradeStats;
// Поле:   bool User::Allowed
   public: CSmartField      <OD_User, bool       >    m_Allowed;
// Поле:   byte User::ObjectState
   public: CSmartField      <OD_User, byte       >    m_ObjectState;
// Поле:   identifier User::TagID
   public: CSmartField      <OD_User, identifier >    m_TagID;
// Поле:   int User::TagInt
   public: CSmartField      <OD_User, int        >    m_TagInt;
// Поле:   bool User::TagBool
   public: CSmartField      <OD_User, bool       >    m_TagBool;
// Поле:   int User::CacheTime
   public: CSmartField      <OD_User, int        >    m_CacheTime;
// Поле:   byte User::ba_Concept []
   public: CSmartFieldArray <OD_User, byte       >    m_ba_Concept;
// Поле:   byte User::eba_Concept []
   public: CSmartFieldArray <OD_User, byte       >    m_eba_Concept;
// Поле:   identifier User::Site []
   public: CSmartFieldArray <OD_User, identifier >    m_Site;
// Поле:   identifier User::SiteProfile []
   public: CSmartFieldArray <OD_User, identifier >    m_SiteProfile;
// Поле:   identifier User::Banner []
   public: CSmartFieldArray <OD_User, identifier >    m_Banner;
// Поле:   identifier User::BannerProfile []
   public: CSmartFieldArray <OD_User, identifier >    m_BannerProfile;
// Поле:   byte User::ba_ModeratorComment []
   public: CSmartFieldArray <OD_User, byte       >    m_ba_ModeratorComment;
// Поле:   identifier User::ReservedID []
   public: CSmartFieldArray <OD_User, identifier >    m_ReservedID;
// Поле:   int User::ReservedInt []
   public: CSmartFieldArray <OD_User, int        >    m_ReservedInt;
// Поле:   string User::ReservedString []
   public: CSmartFieldArray <OD_User, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// Установить текущий индекс по набору полей [VBN, Login]
   public: void SetIndex_VBN_Login ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_TradeStats
#endif
#ifdef USES_OC_TradeStats
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "TradeStats"
// 
class OC_TradeStats: public OC_Object <OC_TradeStats>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_TradeStats  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_TradeStats  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_TradeStats  (const OC_TradeStats& from);
// Деструктор контроллера объекта
   public: ~OC_TradeStats ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_TradeStats& operator= (const OC_TradeStats& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_TradeStats& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_TradeStats& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_TradeStats& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_TradeStats& operator << (OC_TradeStats& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_TradeStats& operator >> (OC_TradeStats& from);

// Поле:   identifier TradeStats::TagID
   public: CSmartField      <OD_TradeStats, identifier >    m_TagID;
// Поле:   int TradeStats::TagInt
   public: CSmartField      <OD_TradeStats, int        >    m_TagInt;
// Поле:   bool TradeStats::TagBool
   public: CSmartField      <OD_TradeStats, bool       >    m_TagBool;
// Поле:   int TradeStats::CacheTime
   public: CSmartField      <OD_TradeStats, int        >    m_CacheTime;
// Поле:   int TradeStats::SoldShowDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldShowDates;
// Поле:   int TradeStats::SoldShowAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldShowAmounts;
// Поле:   string TradeStats::SoldShowBuyer []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_SoldShowBuyer;
// Поле:   int TradeStats::BoughtShowDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtShowDates;
// Поле:   int TradeStats::BoughtShowAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtShowAmounts;
// Поле:   string TradeStats::BoughtShowSeller []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_BoughtShowSeller;
// Поле:   int TradeStats::SoldClickDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldClickDates;
// Поле:   int TradeStats::SoldClickAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldClickAmounts;
// Поле:   string TradeStats::SoldClickBuyer []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_SoldClickBuyer;
// Поле:   int TradeStats::BoughtClickDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtClickDates;
// Поле:   int TradeStats::BoughtClickAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtClickAmounts;
// Поле:   string TradeStats::BoughtClickSeller []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_BoughtClickSeller;
// Поле:   identifier TradeStats::ReservedID []
   public: CSmartFieldArray <OD_TradeStats, identifier >    m_ReservedID;
// Поле:   int TradeStats::ReservedInt []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_ReservedInt;
// Поле:   string TradeStats::ReservedString []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_ReservedString;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Banner
#endif
#ifdef USES_OC_Banner
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Banner"
// 
class OC_Banner: public OC_Object <OC_Banner>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Banner  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Banner  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Banner  (const OC_Banner& from);
// Деструктор контроллера объекта
   public: ~OC_Banner ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Banner& operator= (const OC_Banner& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Banner& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Banner& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Banner& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Banner& operator << (OC_Banner& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Banner& operator >> (OC_Banner& from);

// Поле:   identifier Banner::OwnerID
   public: CSmartField      <OD_Banner, identifier >    m_OwnerID;
// Поле:   string Banner::FileName
   public: CSmartField      <OD_Banner, string     >    m_FileName;
// Поле:   int Banner::FileSize
   public: CSmartField      <OD_Banner, int        >    m_FileSize;
// Поле:   int Banner::UploadNo
   public: CSmartField      <OD_Banner, int        >    m_UploadNo;
// Поле:   int Banner::CreationTime
   public: CSmartField      <OD_Banner, int        >    m_CreationTime;
// Поле:   byte Banner::VBN
   public: CSmartField      <OD_Banner, byte       >    m_VBN;
// Поле:   string Banner::Description
   public: CSmartField      <OD_Banner, string     >    m_Description;
// Поле:   bool Banner::State
   public: CSmartField      <OD_Banner, bool       >    m_State;
// Поле:   identifier Banner::Profile
   public: CSmartField      <OD_Banner, identifier >    m_Profile;
// Поле:   int Banner::TotalShows
   public: CSmartField      <OD_Banner, int        >    m_TotalShows;
// Поле:   int Banner::TotalClicks
   public: CSmartField      <OD_Banner, int        >    m_TotalClicks;
// Поле:   bool Banner::Allowed
   public: CSmartField      <OD_Banner, bool       >    m_Allowed;
// Поле:   byte Banner::ObjectState
   public: CSmartField      <OD_Banner, byte       >    m_ObjectState;
// Поле:   identifier Banner::TagID
   public: CSmartField      <OD_Banner, identifier >    m_TagID;
// Поле:   int Banner::TagInt
   public: CSmartField      <OD_Banner, int        >    m_TagInt;
// Поле:   bool Banner::TagBool
   public: CSmartField      <OD_Banner, bool       >    m_TagBool;
// Поле:   int Banner::CacheTime
   public: CSmartField      <OD_Banner, int        >    m_CacheTime;
// Поле:   identifier Banner::SiteAnnounce []
   public: CSmartFieldArray <OD_Banner, identifier >    m_SiteAnnounce;
// Поле:   byte Banner::ba_Concept []
   public: CSmartFieldArray <OD_Banner, byte       >    m_ba_Concept;
// Поле:   byte Banner::eba_Concept []
   public: CSmartFieldArray <OD_Banner, byte       >    m_eba_Concept;
// Поле:   byte Banner::ba_ModeratorComment []
   public: CSmartFieldArray <OD_Banner, byte       >    m_ba_ModeratorComment;
// Поле:   identifier Banner::ReservedID []
   public: CSmartFieldArray <OD_Banner, identifier >    m_ReservedID;
// Поле:   int Banner::ReservedInt []
   public: CSmartFieldArray <OD_Banner, int        >    m_ReservedInt;
// Поле:   string Banner::ReservedString []
   public: CSmartFieldArray <OD_Banner, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_BannerProfile
#endif
#ifdef USES_OC_BannerProfile
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "BannerProfile"
// 
class OC_BannerProfile: public OC_Object <OC_BannerProfile>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_BannerProfile  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_BannerProfile  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_BannerProfile  (const OC_BannerProfile& from);
// Деструктор контроллера объекта
   public: ~OC_BannerProfile ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_BannerProfile& operator= (const OC_BannerProfile& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_BannerProfile& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_BannerProfile& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_BannerProfile& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_BannerProfile& operator << (OC_BannerProfile& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_BannerProfile& operator >> (OC_BannerProfile& from);

// Поле:   string BannerProfile::Name
   public: CSmartField      <OD_BannerProfile, string     >    m_Name;
// Поле:   byte BannerProfile::VBN
   public: CSmartField      <OD_BannerProfile, byte       >    m_VBN;
// Поле:   int BannerProfile::LastModified
   public: CSmartField      <OD_BannerProfile, int        >    m_LastModified;
// Поле:   identifier BannerProfile::OwnerID
   public: CSmartField      <OD_BannerProfile, identifier >    m_OwnerID;
// Поле:   identifier BannerProfile::HREF
   public: CSmartField      <OD_BannerProfile, identifier >    m_HREF;
// Поле:   bool BannerProfile::Commercial
   public: CSmartField      <OD_BannerProfile, bool       >    m_Commercial;
// Поле:   int BannerProfile::BannerType
   public: CSmartField      <OD_BannerProfile, int        >    m_BannerType;
// Поле:   bool BannerProfile::State
   public: CSmartField      <OD_BannerProfile, bool       >    m_State;
// Поле:   string BannerProfile::AltText
   public: CSmartField      <OD_BannerProfile, string     >    m_AltText;
// Поле:   bool BannerProfile::UseLocalTime
   public: CSmartField      <OD_BannerProfile, bool       >    m_UseLocalTime;
// Поле:   int BannerProfile::ScheduleTZOffset
   public: CSmartField      <OD_BannerProfile, int        >    m_ScheduleTZOffset;
// Поле:   bool BannerProfile::ShowIfLocalUnknown
   public: CSmartField      <OD_BannerProfile, bool       >    m_ShowIfLocalUnknown;
// Поле:   int BannerProfile::AutoOn
   public: CSmartField      <OD_BannerProfile, int        >    m_AutoOn;
// Поле:   int BannerProfile::AutoOff
   public: CSmartField      <OD_BannerProfile, int        >    m_AutoOff;
// Поле:   int BannerProfile::RepeatCount
   public: CSmartField      <OD_BannerProfile, int        >    m_RepeatCount;
// Поле:   int BannerProfile::RepeatTime
   public: CSmartField      <OD_BannerProfile, int        >    m_RepeatTime;
// Поле:   bool BannerProfile::CountTypeByShows
   public: CSmartField      <OD_BannerProfile, bool       >    m_CountTypeByShows;
// Поле:   int BannerProfile::MaxDailyClicks
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyClicks;
// Поле:   int BannerProfile::MaxDailyShows
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyShows;
// Поле:   int BannerProfile::MaxDailyShowsChangeTime
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyShowsChangeTime;
// Поле:   int BannerProfile::TotalShows
   public: CSmartField      <OD_BannerProfile, int        >    m_TotalShows;
// Поле:   int BannerProfile::TotalClicks
   public: CSmartField      <OD_BannerProfile, int        >    m_TotalClicks;
// Поле:   int BannerProfile::SessionEvents
   public: CSmartField      <OD_BannerProfile, int        >    m_SessionEvents;
// Поле:   float BannerProfile::Priority
   public: CSmartField      <OD_BannerProfile, float      >    m_Priority;
// Поле:   bool BannerProfile::Allowed
   public: CSmartField      <OD_BannerProfile, bool       >    m_Allowed;
// Поле:   byte BannerProfile::ObjectState
   public: CSmartField      <OD_BannerProfile, byte       >    m_ObjectState;
// Поле:   identifier BannerProfile::TagID
   public: CSmartField      <OD_BannerProfile, identifier >    m_TagID;
// Поле:   int BannerProfile::TagInt
   public: CSmartField      <OD_BannerProfile, int        >    m_TagInt;
// Поле:   bool BannerProfile::TagBool
   public: CSmartField      <OD_BannerProfile, bool       >    m_TagBool;
// Поле:   int BannerProfile::CacheTime
   public: CSmartField      <OD_BannerProfile, int        >    m_CacheTime;
// Поле:   identifier BannerProfile::SiteAnnounce []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteAnnounce;
// Поле:   identifier BannerProfile::Banner []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_Banner;
// Поле:   byte BannerProfile::ba_Concept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_Concept;
// Поле:   byte BannerProfile::eba_Concept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_Concept;
// Поле:   byte BannerProfile::ba_SiteConceptInclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_SiteConceptInclude;
// Поле:   byte BannerProfile::ba_SiteConceptExclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_SiteConceptExclude;
// Поле:   byte BannerProfile::eba_SiteConcept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_SiteConcept;
// Поле:   identifier BannerProfile::SiteInclude []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteInclude;
// Поле:   identifier BannerProfile::SiteExclude []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteExclude;
// Поле:   string BannerProfile::ViewerIPEnable []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ViewerIPEnable;
// Поле:   string BannerProfile::ViewerIPDisable []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ViewerIPDisable;
// Поле:   byte BannerProfile::ba_ViewerConceptInclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ViewerConceptInclude;
// Поле:   byte BannerProfile::ba_ViewerConceptExclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ViewerConceptExclude;
// Поле:   byte BannerProfile::eba_ViewerConcept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_ViewerConcept;
// Поле:   byte BannerProfile::ba_Schedule []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_Schedule;
// Поле:   identifier BannerProfile::SiteTarget_SiteID []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteTarget_SiteID;
// Поле:   int BannerProfile::SiteTarget_ShowRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ShowRate;
// Поле:   int BannerProfile::SiteTarget_ClickRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ClickRate;
// Поле:   int BannerProfile::SiteTarget_ViewRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ViewRate;
// Поле:   int BannerProfile::ViewerConceptRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ViewerConceptRate;
// Поле:   int BannerProfile::ShowNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ShowNumRate;
// Поле:   int BannerProfile::ClickNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ClickNumRate;
// Поле:   int BannerProfile::HitNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_HitNumRate;
// Поле:   int BannerProfile::SessionTimeRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SessionTimeRate;
// Поле:   byte BannerProfile::ba_ModeratorComment []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ModeratorComment;
// Поле:   identifier BannerProfile::ReservedID []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_ReservedID;
// Поле:   int BannerProfile::ReservedInt []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ReservedInt;
// Поле:   string BannerProfile::ReservedString []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// Установить текущий индекс по набору полей [VBN, State, Allowed, BannerType, Priority]
   public: void SetIndex_VBN_State_Allowed_BannerType_Priority ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Page
#endif
#ifdef USES_OC_Page
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Page"
// 
class OC_Page: public OC_Object <OC_Page>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Page  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Page  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Page  (const OC_Page& from);
// Деструктор контроллера объекта
   public: ~OC_Page ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Page& operator= (const OC_Page& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Page& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Page& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Page& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Page& operator << (OC_Page& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Page& operator >> (OC_Page& from);

// Поле:   identifier Page::Site
   public: CSmartField      <OD_Page, identifier >    m_Site;
// Поле:   int Page::No
   public: CSmartField      <OD_Page, int        >    m_No;
// Поле:   string Page::URL
   public: CSmartField      <OD_Page, string     >    m_URL;
// Поле:   int Page::CounterType
   public: CSmartField      <OD_Page, int        >    m_CounterType;
// Поле:   bool Page::ConceptSet
   public: CSmartField      <OD_Page, bool       >    m_ConceptSet;
// Поле:   int Page::CRN_Visitor_Update
   public: CSmartField      <OD_Page, int        >    m_CRN_Visitor_Update;
// Поле:   int Page::CRN_VisitorIncr_Update
   public: CSmartField      <OD_Page, int        >    m_CRN_VisitorIncr_Update;
// Поле:   identifier Page::TagID
   public: CSmartField      <OD_Page, identifier >    m_TagID;
// Поле:   int Page::TagInt
   public: CSmartField      <OD_Page, int        >    m_TagInt;
// Поле:   bool Page::TagBool
   public: CSmartField      <OD_Page, bool       >    m_TagBool;
// Поле:   int Page::CacheTime
   public: CSmartField      <OD_Page, int        >    m_CacheTime;
// Поле:   byte Page::ba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_ba_Concept;
// Поле:   byte Page::eba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_eba_Concept;
// Поле:   byte Page::pba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_pba_Concept;
// Поле:   identifier Page::TimeStats []
   public: CSmartFieldArray <OD_Page, identifier >    m_TimeStats;
// Поле:   byte Page::TimeStatsType []
   public: CSmartFieldArray <OD_Page, byte       >    m_TimeStatsType;
// Поле:   int Page::CRA_Visitor []
   public: CSmartFieldArray <OD_Page, int        >    m_CRA_Visitor;
// Поле:   int Page::CRN_Visitor []
   public: CSmartFieldArray <OD_Page, int        >    m_CRN_Visitor;
// Поле:   int Page::CRN_VisitorIncr []
   public: CSmartFieldArray <OD_Page, int        >    m_CRN_VisitorIncr;
// Поле:   identifier Page::Referrer []
   public: CSmartFieldArray <OD_Page, identifier >    m_Referrer;
// Поле:   int Page::ReferrerCount []
   public: CSmartFieldArray <OD_Page, int        >    m_ReferrerCount;
// Поле:   identifier Page::ReservedID []
   public: CSmartFieldArray <OD_Page, identifier >    m_ReservedID;
// Поле:   int Page::ReservedInt []
   public: CSmartFieldArray <OD_Page, int        >    m_ReservedInt;
// Поле:   string Page::ReservedString []
   public: CSmartFieldArray <OD_Page, string     >    m_ReservedString;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Site
#endif
#ifdef USES_OC_Site
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Site"
// 
class OC_Site: public OC_Object <OC_Site>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Site  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Site  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Site  (const OC_Site& from);
// Деструктор контроллера объекта
   public: ~OC_Site ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Site& operator= (const OC_Site& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Site& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Site& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Site& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Site& operator << (OC_Site& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Site& operator >> (OC_Site& from);

// Поле:   identifier Site::OwnerID
   public: CSmartField      <OD_Site, identifier >    m_OwnerID;
// Поле:   byte Site::VBN
   public: CSmartField      <OD_Site, byte       >    m_VBN;
// Поле:   int Site::CreationTime
   public: CSmartField      <OD_Site, int        >    m_CreationTime;
// Поле:   string Site::Alias
   public: CSmartField      <OD_Site, string     >    m_Alias;
// Поле:   string Site::Name
   public: CSmartField      <OD_Site, string     >    m_Name;
// Поле:   string Site::Description
   public: CSmartField      <OD_Site, string     >    m_Description;
// Поле:   string Site::URL
   public: CSmartField      <OD_Site, string     >    m_URL;
// Поле:   int Site::CounterType
   public: CSmartField      <OD_Site, int        >    m_CounterType;
// Поле:   bool Site::RateMySite
   public: CSmartField      <OD_Site, bool       >    m_RateMySite;
// Поле:   string Site::RateStatsViewPassword
   public: CSmartField      <OD_Site, string     >    m_RateStatsViewPassword;
// Поле:   bool Site::ShowAudience
   public: CSmartField      <OD_Site, bool       >    m_ShowAudience;
// Поле:   int Site::ShowAudienceOffTime
   public: CSmartField      <OD_Site, int        >    m_ShowAudienceOffTime;
// Поле:   identifier Site::Profile
   public: CSmartField      <OD_Site, identifier >    m_Profile;
// Поле:   identifier Site::SuspiciousInfo
   public: CSmartField      <OD_Site, identifier >    m_SuspiciousInfo;
// Поле:   int Site::CRN_Visitor_Update
   public: CSmartField      <OD_Site, int        >    m_CRN_Visitor_Update;
// Поле:   int Site::CRN_VisitorIncr_Update
   public: CSmartField      <OD_Site, int        >    m_CRN_VisitorIncr_Update;
// Поле:   int Site::RecentPointer
   public: CSmartField      <OD_Site, int        >    m_RecentPointer;
// Поле:   int Site::Referrer_LastReset
   public: CSmartField      <OD_Site, int        >    m_Referrer_LastReset;
// Поле:   identifier Site::SearchWordsInfo
   public: CSmartField      <OD_Site, identifier >    m_SearchWordsInfo;
// Поле:   int Site::InquiredVisitorNum
   public: CSmartField      <OD_Site, int        >    m_InquiredVisitorNum;
// Поле:   int Site::SessionResetTime
   public: CSmartField      <OD_Site, int        >    m_SessionResetTime;
// Поле:   int Site::LastVisitTime
   public: CSmartField      <OD_Site, int        >    m_LastVisitTime;
// Поле:   int Site::LastUpdateTime
   public: CSmartField      <OD_Site, int        >    m_LastUpdateTime;
// Поле:   identifier Site::Loads
   public: CSmartField      <OD_Site, identifier >    m_Loads;
// Поле:   identifier Site::Visitors
   public: CSmartField      <OD_Site, identifier >    m_Visitors;
// Поле:   identifier Site::Hosts
   public: CSmartField      <OD_Site, identifier >    m_Hosts;
// Поле:   identifier Site::Shows
   public: CSmartField      <OD_Site, identifier >    m_Shows;
// Поле:   identifier Site::Clicks
   public: CSmartField      <OD_Site, identifier >    m_Clicks;
// Поле:   identifier Site::Clicks_Local
   public: CSmartField      <OD_Site, identifier >    m_Clicks_Local;
// Поле:   identifier Site::Hits
   public: CSmartField      <OD_Site, identifier >    m_Hits;
// Поле:   identifier Site::Hits_Local
   public: CSmartField      <OD_Site, identifier >    m_Hits_Local;
// Поле:   identifier Site::AnonymousHits
   public: CSmartField      <OD_Site, identifier >    m_AnonymousHits;
// Поле:   identifier Site::SuspiciousHits
   public: CSmartField      <OD_Site, identifier >    m_SuspiciousHits;
// Поле:   identifier Site::SessionTime
   public: CSmartField      <OD_Site, identifier >    m_SessionTime;
// Поле:   identifier Site::SessionTime_Local
   public: CSmartField      <OD_Site, identifier >    m_SessionTime_Local;
// Поле:   identifier Site::SessionNum
   public: CSmartField      <OD_Site, identifier >    m_SessionNum;
// Поле:   int Site::Total_Loads
   public: CSmartField      <OD_Site, int        >    m_Total_Loads;
// Поле:   int Site::Total_Hosts
   public: CSmartField      <OD_Site, int        >    m_Total_Hosts;
// Поле:   int Site::Total_Hits
   public: CSmartField      <OD_Site, int        >    m_Total_Hits;
// Поле:   int Site::Total_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousHits;
// Поле:   int Site::Total_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousHits_Prc;
// Поле:   int Site::Total_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_SuspiciousHits_Prc;
// Поле:   int Site::Total_Visitors
   public: CSmartField      <OD_Site, int        >    m_Total_Visitors;
// Поле:   int Site::Total_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorReturns;
// Поле:   int Site::Total_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorReturns_Prc;
// Поле:   int Site::Total_SessionNum
   public: CSmartField      <OD_Site, int        >    m_Total_SessionNum;
// Поле:   int Site::Total_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_Total_AveSessionTime;
// Поле:   int Site::Total_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_Total_AveReloadTime;
// Поле:   int Site::Total_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_Total_AveReloadNum;
// Поле:   int Site::Total_Shows
   public: CSmartField      <OD_Site, int        >    m_Total_Shows;
// Поле:   int Site::Total_Clicks
   public: CSmartField      <OD_Site, int        >    m_Total_Clicks;
// Поле:   int Site::Total_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_CTR_Prc;
// Поле:   int Site::Total_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_CPH_Prc;
// Поле:   int Site::Total_AnonymousVisitors
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousVisitors;
// Поле:   int Site::Total_AnonymousVisitors_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousVisitors_Prc;
// Поле:   int Site::Total_VisitorExperience
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorExperience;
// Поле:   int Site::Ave_VisitorExperience
   public: CSmartField      <OD_Site, int        >    m_Ave_VisitorExperience;
// Поле:   int Site::OnlineVisitors
   public: CSmartField      <OD_Site, int        >    m_OnlineVisitors;
// Поле:   int Site::Total_MouseOver
   public: CSmartField      <OD_Site, int        >    m_Total_MouseOver;
// Поле:   int Site::Total_Votes
   public: CSmartField      <OD_Site, int        >    m_Total_Votes;
// Поле:   int Site::Total_Votes_Sum
   public: CSmartField      <OD_Site, int        >    m_Total_Votes_Sum;
// Поле:   int Site::Total_Votes_Ave
   public: CSmartField      <OD_Site, int        >    m_Total_Votes_Ave;
// Поле:   int Site::LM_Loads
   public: CSmartField      <OD_Site, int        >    m_LM_Loads;
// Поле:   int Site::LM_Hosts
   public: CSmartField      <OD_Site, int        >    m_LM_Hosts;
// Поле:   int Site::LM_Hits
   public: CSmartField      <OD_Site, int        >    m_LM_Hits;
// Поле:   int Site::LM_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LM_AnonymousHits;
// Поле:   int Site::LM_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_AnonymousHits_Prc;
// Поле:   int Site::LM_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_SuspiciousHits_Prc;
// Поле:   int Site::LM_Visitors
   public: CSmartField      <OD_Site, int        >    m_LM_Visitors;
// Поле:   int Site::LM_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LM_VisitorReturns;
// Поле:   int Site::LM_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_VisitorReturns_Prc;
// Поле:   int Site::LM_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LM_SessionNum;
// Поле:   int Site::LM_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LM_AveSessionTime;
// Поле:   int Site::LM_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LM_AveReloadTime;
// Поле:   int Site::LM_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LM_AveReloadNum;
// Поле:   int Site::LM_Shows
   public: CSmartField      <OD_Site, int        >    m_LM_Shows;
// Поле:   int Site::LM_Clicks
   public: CSmartField      <OD_Site, int        >    m_LM_Clicks;
// Поле:   int Site::LM_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_CTR_Prc;
// Поле:   int Site::LM_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_CPH_Prc;
// Поле:   int Site::LW_Loads
   public: CSmartField      <OD_Site, int        >    m_LW_Loads;
// Поле:   int Site::LW_Hosts
   public: CSmartField      <OD_Site, int        >    m_LW_Hosts;
// Поле:   int Site::LW_Hits
   public: CSmartField      <OD_Site, int        >    m_LW_Hits;
// Поле:   int Site::LW_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LW_AnonymousHits;
// Поле:   int Site::LW_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_AnonymousHits_Prc;
// Поле:   int Site::LW_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_SuspiciousHits_Prc;
// Поле:   int Site::LW_Visitors
   public: CSmartField      <OD_Site, int        >    m_LW_Visitors;
// Поле:   int Site::LW_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LW_VisitorReturns;
// Поле:   int Site::LW_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_VisitorReturns_Prc;
// Поле:   int Site::LW_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LW_SessionNum;
// Поле:   int Site::LW_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LW_AveSessionTime;
// Поле:   int Site::LW_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LW_AveReloadTime;
// Поле:   int Site::LW_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LW_AveReloadNum;
// Поле:   int Site::LW_Shows
   public: CSmartField      <OD_Site, int        >    m_LW_Shows;
// Поле:   int Site::LW_Clicks
   public: CSmartField      <OD_Site, int        >    m_LW_Clicks;
// Поле:   int Site::LW_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_CTR_Prc;
// Поле:   int Site::LW_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_CPH_Prc;
// Поле:   int Site::LD_Loads
   public: CSmartField      <OD_Site, int        >    m_LD_Loads;
// Поле:   int Site::LD_Hosts
   public: CSmartField      <OD_Site, int        >    m_LD_Hosts;
// Поле:   int Site::LD_Hits
   public: CSmartField      <OD_Site, int        >    m_LD_Hits;
// Поле:   int Site::LD_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LD_AnonymousHits;
// Поле:   int Site::LD_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_AnonymousHits_Prc;
// Поле:   int Site::LD_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_SuspiciousHits_Prc;
// Поле:   int Site::LD_Visitors
   public: CSmartField      <OD_Site, int        >    m_LD_Visitors;
// Поле:   int Site::LD_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LD_VisitorReturns;
// Поле:   int Site::LD_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_VisitorReturns_Prc;
// Поле:   int Site::LD_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LD_SessionNum;
// Поле:   int Site::LD_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LD_AveSessionTime;
// Поле:   int Site::LD_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LD_AveReloadTime;
// Поле:   int Site::LD_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LD_AveReloadNum;
// Поле:   int Site::LD_Shows
   public: CSmartField      <OD_Site, int        >    m_LD_Shows;
// Поле:   int Site::LD_Clicks
   public: CSmartField      <OD_Site, int        >    m_LD_Clicks;
// Поле:   int Site::LD_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_CTR_Prc;
// Поле:   int Site::LD_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_CPH_Prc;
// Поле:   int Site::LH_Loads
   public: CSmartField      <OD_Site, int        >    m_LH_Loads;
// Поле:   int Site::LH_Hosts
   public: CSmartField      <OD_Site, int        >    m_LH_Hosts;
// Поле:   int Site::LH_Hits
   public: CSmartField      <OD_Site, int        >    m_LH_Hits;
// Поле:   int Site::LH_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LH_AnonymousHits;
// Поле:   int Site::LH_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_AnonymousHits_Prc;
// Поле:   int Site::LH_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_SuspiciousHits_Prc;
// Поле:   int Site::LH_Visitors
   public: CSmartField      <OD_Site, int        >    m_LH_Visitors;
// Поле:   int Site::LH_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LH_VisitorReturns;
// Поле:   int Site::LH_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_VisitorReturns_Prc;
// Поле:   int Site::LH_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LH_SessionNum;
// Поле:   int Site::LH_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LH_AveSessionTime;
// Поле:   int Site::LH_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LH_AveReloadTime;
// Поле:   int Site::LH_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LH_AveReloadNum;
// Поле:   int Site::LH_Shows
   public: CSmartField      <OD_Site, int        >    m_LH_Shows;
// Поле:   int Site::LH_Clicks
   public: CSmartField      <OD_Site, int        >    m_LH_Clicks;
// Поле:   int Site::LH_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_CTR_Prc;
// Поле:   int Site::LH_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_CPH_Prc;
// Поле:   int Site::CustomIndex1
   public: CSmartField      <OD_Site, int        >    m_CustomIndex1;
// Поле:   int Site::CustomIndex2
   public: CSmartField      <OD_Site, int        >    m_CustomIndex2;
// Поле:   int Site::CustomIndex3
   public: CSmartField      <OD_Site, int        >    m_CustomIndex3;
// Поле:   int Site::CustomIndex4
   public: CSmartField      <OD_Site, int        >    m_CustomIndex4;
// Поле:   int Site::CustomIndex5
   public: CSmartField      <OD_Site, int        >    m_CustomIndex5;
// Поле:   bool Site::Allowed
   public: CSmartField      <OD_Site, bool       >    m_Allowed;
// Поле:   byte Site::ObjectState
   public: CSmartField      <OD_Site, byte       >    m_ObjectState;
// Поле:   identifier Site::TagID
   public: CSmartField      <OD_Site, identifier >    m_TagID;
// Поле:   bool Site::TagBool
   public: CSmartField      <OD_Site, bool       >    m_TagBool;
// Поле:   int Site::TagInt
   public: CSmartField      <OD_Site, int        >    m_TagInt;
// Поле:   identifier Site::RatingPlaceInfo
   public: CSmartField      <OD_Site, identifier >    m_RatingPlaceInfo;
// Поле:   int Site::CacheTime
   public: CSmartField      <OD_Site, int        >    m_CacheTime;
// Поле:   string Site::Announce []
   public: CSmartFieldArray <OD_Site, string     >    m_Announce;
// Поле:   identifier Site::Keyword []
   public: CSmartFieldArray <OD_Site, identifier >    m_Keyword;
// Поле:   string Site::MirrorInclude []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorInclude;
// Поле:   string Site::MirrorExclude []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorExclude;
// Поле:   string Site::MirrorSubstr []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorSubstr;
// Поле:   string Site::IgnoredIP []
   public: CSmartFieldArray <OD_Site, string     >    m_IgnoredIP;
// Поле:   identifier Site::IgnoredViewerID []
   public: CSmartFieldArray <OD_Site, identifier >    m_IgnoredViewerID;
// Поле:   byte Site::ba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_ba_Concept;
// Поле:   byte Site::pba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_pba_Concept;
// Поле:   byte Site::eba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_eba_Concept;
// Поле:   int Site::CRN_Self []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Self;
// Поле:   identifier Site::Page []
   public: CSmartFieldArray <OD_Site, identifier >    m_Page;
// Поле:   string Site::PageName []
   public: CSmartFieldArray <OD_Site, string     >    m_PageName;
// Поле:   int Site::PageNo []
   public: CSmartFieldArray <OD_Site, int        >    m_PageNo;
// Поле:   identifier Site::AdBannerProfile []
   public: CSmartFieldArray <OD_Site, identifier >    m_AdBannerProfile;
// Поле:   int Site::CRA_Visitor []
   public: CSmartFieldArray <OD_Site, int        >    m_CRA_Visitor;
// Поле:   int Site::CRN_Visitor []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Visitor;
// Поле:   int Site::CRA_Inquiry []
   public: CSmartFieldArray <OD_Site, int        >    m_CRA_Inquiry;
// Поле:   int Site::CRN_Inquiry []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Inquiry;
// Поле:   int Site::CRN_VisitorIncr []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_VisitorIncr;
// Поле:   identifier Site::Audience_SiteID []
   public: CSmartFieldArray <OD_Site, identifier >    m_Audience_SiteID;
// Поле:   int Site::Audience_Viewers []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_Viewers;
// Поле:   int Site::Audience_Hosts []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_Hosts;
// Поле:   int Site::Audience_SiteIDInclude []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_SiteIDInclude;
// Поле:   identifier Site::ActiveViewersID []
   public: CSmartFieldArray <OD_Site, identifier >    m_ActiveViewersID;
// Поле:   int Site::ActiveViewersHits []
   public: CSmartFieldArray <OD_Site, int        >    m_ActiveViewersHits;
// Поле:   identifier Site::RecentVisitor []
   public: CSmartFieldArray <OD_Site, identifier >    m_RecentVisitor;
// Поле:   identifier Site::RecentReferrer []
   public: CSmartFieldArray <OD_Site, identifier >    m_RecentReferrer;
// Поле:   int Site::RecentTimeStamp []
   public: CSmartFieldArray <OD_Site, int        >    m_RecentTimeStamp;
// Поле:   identifier Site::Referrer []
   public: CSmartFieldArray <OD_Site, identifier >    m_Referrer;
// Поле:   int Site::ReferrerCount []
   public: CSmartFieldArray <OD_Site, int        >    m_ReferrerCount;
// Поле:   identifier Site::DailyReferrerStats []
   public: CSmartFieldArray <OD_Site, identifier >    m_DailyReferrerStats;
// Поле:   int Site::DailyReferrerTimeStamp []
   public: CSmartFieldArray <OD_Site, int        >    m_DailyReferrerTimeStamp;
// Поле:   int Site::Inquire []
   public: CSmartFieldArray <OD_Site, int        >    m_Inquire;
// Поле:   int Site::ReturnNumRate []
   public: CSmartFieldArray <OD_Site, int        >    m_ReturnNumRate;
// Поле:   int Site::ShowNumRate []
   public: CSmartFieldArray <OD_Site, int        >    m_ShowNumRate;
// Поле:   byte Site::ba_ModeratorComment []
   public: CSmartFieldArray <OD_Site, byte       >    m_ba_ModeratorComment;
// Поле:   identifier Site::ReservedID []
   public: CSmartFieldArray <OD_Site, identifier >    m_ReservedID;
// Поле:   int Site::ReservedInt []
   public: CSmartFieldArray <OD_Site, int        >    m_ReservedInt;
// Поле:   string Site::ReservedString []
   public: CSmartFieldArray <OD_Site, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [VBN, Name]
   public: void SetIndex_VBN_Name ();
// Установить текущий индекс по полю [Alias]
   public: void SetIndex_Alias ();
// Установить текущий индекс по набору полей [VBN, CreationTime]
   public: void SetIndex_VBN_CreationTime ();
// Установить текущий индекс по полю [LastVisitTime]
   public: void SetIndex_LastVisitTime ();
// Установить текущий индекс по полю [LastUpdateTime]
   public: void SetIndex_LastUpdateTime ();
// Установить текущий индекс по набору полей [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// Установить текущий индекс по набору полей [VBN, -Total_Loads]
   public: void SetIndex_VBN__Total_Loads ();
// Установить текущий индекс по набору полей [VBN, -Total_Hosts]
   public: void SetIndex_VBN__Total_Hosts ();
// Установить текущий индекс по набору полей [VBN, -Total_Hits]
   public: void SetIndex_VBN__Total_Hits ();
// Установить текущий индекс по набору полей [VBN, -Total_AnonymousHits]
   public: void SetIndex_VBN__Total_AnonymousHits ();
// Установить текущий индекс по набору полей [VBN, -Total_AnonymousHits_Prc]
   public: void SetIndex_VBN__Total_AnonymousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_SuspiciousHits_Prc]
   public: void SetIndex_VBN__Total_SuspiciousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_Visitors]
   public: void SetIndex_VBN__Total_Visitors ();
// Установить текущий индекс по набору полей [VBN, -Total_VisitorReturns]
   public: void SetIndex_VBN__Total_VisitorReturns ();
// Установить текущий индекс по набору полей [VBN, -Total_VisitorReturns_Prc]
   public: void SetIndex_VBN__Total_VisitorReturns_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_SessionNum]
   public: void SetIndex_VBN__Total_SessionNum ();
// Установить текущий индекс по набору полей [VBN, -Total_AveSessionTime]
   public: void SetIndex_VBN__Total_AveSessionTime ();
// Установить текущий индекс по набору полей [VBN, -Total_AveReloadTime]
   public: void SetIndex_VBN__Total_AveReloadTime ();
// Установить текущий индекс по набору полей [VBN, -Total_AveReloadNum]
   public: void SetIndex_VBN__Total_AveReloadNum ();
// Установить текущий индекс по набору полей [VBN, -Total_Shows]
   public: void SetIndex_VBN__Total_Shows ();
// Установить текущий индекс по набору полей [VBN, -Total_Clicks]
   public: void SetIndex_VBN__Total_Clicks ();
// Установить текущий индекс по набору полей [VBN, -Total_CTR_Prc]
   public: void SetIndex_VBN__Total_CTR_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_CPH_Prc]
   public: void SetIndex_VBN__Total_CPH_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_AnonymousVisitors]
   public: void SetIndex_VBN__Total_AnonymousVisitors ();
// Установить текущий индекс по набору полей [VBN, -Total_AnonymousVisitors_Prc]
   public: void SetIndex_VBN__Total_AnonymousVisitors_Prc ();
// Установить текущий индекс по набору полей [VBN, -Total_VisitorExperience]
   public: void SetIndex_VBN__Total_VisitorExperience ();
// Установить текущий индекс по набору полей [VBN, -Ave_VisitorExperience]
   public: void SetIndex_VBN__Ave_VisitorExperience ();
// Установить текущий индекс по набору полей [VBN, -OnlineVisitors]
   public: void SetIndex_VBN__OnlineVisitors ();
// Установить текущий индекс по набору полей [VBN, -Total_MouseOver]
   public: void SetIndex_VBN__Total_MouseOver ();
// Установить текущий индекс по набору полей [VBN, -Total_Votes]
   public: void SetIndex_VBN__Total_Votes ();
// Установить текущий индекс по набору полей [VBN, -Total_Votes_Sum]
   public: void SetIndex_VBN__Total_Votes_Sum ();
// Установить текущий индекс по набору полей [VBN, -Total_Votes_Ave]
   public: void SetIndex_VBN__Total_Votes_Ave ();
// Установить текущий индекс по набору полей [VBN, -LM_Loads]
   public: void SetIndex_VBN__LM_Loads ();
// Установить текущий индекс по набору полей [VBN, -LM_Hosts]
   public: void SetIndex_VBN__LM_Hosts ();
// Установить текущий индекс по набору полей [VBN, -LM_Hits]
   public: void SetIndex_VBN__LM_Hits ();
// Установить текущий индекс по набору полей [VBN, -LM_AnonymousHits]
   public: void SetIndex_VBN__LM_AnonymousHits ();
// Установить текущий индекс по набору полей [VBN, -LM_AnonymousHits_Prc]
   public: void SetIndex_VBN__LM_AnonymousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LM_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LM_SuspiciousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LM_Visitors]
   public: void SetIndex_VBN__LM_Visitors ();
// Установить текущий индекс по набору полей [VBN, -LM_VisitorReturns]
   public: void SetIndex_VBN__LM_VisitorReturns ();
// Установить текущий индекс по набору полей [VBN, -LM_VisitorReturns_Prc]
   public: void SetIndex_VBN__LM_VisitorReturns_Prc ();
// Установить текущий индекс по набору полей [VBN, -LM_SessionNum]
   public: void SetIndex_VBN__LM_SessionNum ();
// Установить текущий индекс по набору полей [VBN, -LM_AveSessionTime]
   public: void SetIndex_VBN__LM_AveSessionTime ();
// Установить текущий индекс по набору полей [VBN, -LM_AveReloadTime]
   public: void SetIndex_VBN__LM_AveReloadTime ();
// Установить текущий индекс по набору полей [VBN, -LM_AveReloadNum]
   public: void SetIndex_VBN__LM_AveReloadNum ();
// Установить текущий индекс по набору полей [VBN, -LM_Shows]
   public: void SetIndex_VBN__LM_Shows ();
// Установить текущий индекс по набору полей [VBN, -LM_Clicks]
   public: void SetIndex_VBN__LM_Clicks ();
// Установить текущий индекс по набору полей [VBN, -LM_CTR_Prc]
   public: void SetIndex_VBN__LM_CTR_Prc ();
// Установить текущий индекс по набору полей [VBN, -LM_CPH_Prc]
   public: void SetIndex_VBN__LM_CPH_Prc ();
// Установить текущий индекс по набору полей [VBN, -LW_Loads]
   public: void SetIndex_VBN__LW_Loads ();
// Установить текущий индекс по набору полей [VBN, -LW_Hosts]
   public: void SetIndex_VBN__LW_Hosts ();
// Установить текущий индекс по набору полей [VBN, -LW_Hits]
   public: void SetIndex_VBN__LW_Hits ();
// Установить текущий индекс по набору полей [VBN, -LW_AnonymousHits]
   public: void SetIndex_VBN__LW_AnonymousHits ();
// Установить текущий индекс по набору полей [VBN, -LW_AnonymousHits_Prc]
   public: void SetIndex_VBN__LW_AnonymousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LW_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LW_SuspiciousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LW_Visitors]
   public: void SetIndex_VBN__LW_Visitors ();
// Установить текущий индекс по набору полей [VBN, -LW_VisitorReturns]
   public: void SetIndex_VBN__LW_VisitorReturns ();
// Установить текущий индекс по набору полей [VBN, -LW_VisitorReturns_Prc]
   public: void SetIndex_VBN__LW_VisitorReturns_Prc ();
// Установить текущий индекс по набору полей [VBN, -LW_SessionNum]
   public: void SetIndex_VBN__LW_SessionNum ();
// Установить текущий индекс по набору полей [VBN, -LW_AveSessionTime]
   public: void SetIndex_VBN__LW_AveSessionTime ();
// Установить текущий индекс по набору полей [VBN, -LW_AveReloadTime]
   public: void SetIndex_VBN__LW_AveReloadTime ();
// Установить текущий индекс по набору полей [VBN, -LW_AveReloadNum]
   public: void SetIndex_VBN__LW_AveReloadNum ();
// Установить текущий индекс по набору полей [VBN, -LW_Shows]
   public: void SetIndex_VBN__LW_Shows ();
// Установить текущий индекс по набору полей [VBN, -LW_Clicks]
   public: void SetIndex_VBN__LW_Clicks ();
// Установить текущий индекс по набору полей [VBN, -LW_CTR_Prc]
   public: void SetIndex_VBN__LW_CTR_Prc ();
// Установить текущий индекс по набору полей [VBN, -LW_CPH_Prc]
   public: void SetIndex_VBN__LW_CPH_Prc ();
// Установить текущий индекс по набору полей [VBN, -LD_Loads]
   public: void SetIndex_VBN__LD_Loads ();
// Установить текущий индекс по набору полей [VBN, -LD_Hosts]
   public: void SetIndex_VBN__LD_Hosts ();
// Установить текущий индекс по набору полей [VBN, -LD_Hits]
   public: void SetIndex_VBN__LD_Hits ();
// Установить текущий индекс по набору полей [VBN, -LD_AnonymousHits]
   public: void SetIndex_VBN__LD_AnonymousHits ();
// Установить текущий индекс по набору полей [VBN, -LD_AnonymousHits_Prc]
   public: void SetIndex_VBN__LD_AnonymousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LD_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LD_SuspiciousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LD_Visitors]
   public: void SetIndex_VBN__LD_Visitors ();
// Установить текущий индекс по набору полей [VBN, -LD_VisitorReturns]
   public: void SetIndex_VBN__LD_VisitorReturns ();
// Установить текущий индекс по набору полей [VBN, -LD_VisitorReturns_Prc]
   public: void SetIndex_VBN__LD_VisitorReturns_Prc ();
// Установить текущий индекс по набору полей [VBN, -LD_SessionNum]
   public: void SetIndex_VBN__LD_SessionNum ();
// Установить текущий индекс по набору полей [VBN, -LD_AveSessionTime]
   public: void SetIndex_VBN__LD_AveSessionTime ();
// Установить текущий индекс по набору полей [VBN, -LD_AveReloadTime]
   public: void SetIndex_VBN__LD_AveReloadTime ();
// Установить текущий индекс по набору полей [VBN, -LD_AveReloadNum]
   public: void SetIndex_VBN__LD_AveReloadNum ();
// Установить текущий индекс по набору полей [VBN, -LD_Shows]
   public: void SetIndex_VBN__LD_Shows ();
// Установить текущий индекс по набору полей [VBN, -LD_Clicks]
   public: void SetIndex_VBN__LD_Clicks ();
// Установить текущий индекс по набору полей [VBN, -LD_CTR_Prc]
   public: void SetIndex_VBN__LD_CTR_Prc ();
// Установить текущий индекс по набору полей [VBN, -LD_CPH_Prc]
   public: void SetIndex_VBN__LD_CPH_Prc ();
// Установить текущий индекс по набору полей [VBN, -LH_Loads]
   public: void SetIndex_VBN__LH_Loads ();
// Установить текущий индекс по набору полей [VBN, -LH_Hosts]
   public: void SetIndex_VBN__LH_Hosts ();
// Установить текущий индекс по набору полей [VBN, -LH_Hits]
   public: void SetIndex_VBN__LH_Hits ();
// Установить текущий индекс по набору полей [VBN, -LH_AnonymousHits]
   public: void SetIndex_VBN__LH_AnonymousHits ();
// Установить текущий индекс по набору полей [VBN, -LH_AnonymousHits_Prc]
   public: void SetIndex_VBN__LH_AnonymousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LH_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LH_SuspiciousHits_Prc ();
// Установить текущий индекс по набору полей [VBN, -LH_Visitors]
   public: void SetIndex_VBN__LH_Visitors ();
// Установить текущий индекс по набору полей [VBN, -LH_VisitorReturns]
   public: void SetIndex_VBN__LH_VisitorReturns ();
// Установить текущий индекс по набору полей [VBN, -LH_VisitorReturns_Prc]
   public: void SetIndex_VBN__LH_VisitorReturns_Prc ();
// Установить текущий индекс по набору полей [VBN, -LH_SessionNum]
   public: void SetIndex_VBN__LH_SessionNum ();
// Установить текущий индекс по набору полей [VBN, -LH_AveSessionTime]
   public: void SetIndex_VBN__LH_AveSessionTime ();
// Установить текущий индекс по набору полей [VBN, -LH_AveReloadTime]
   public: void SetIndex_VBN__LH_AveReloadTime ();
// Установить текущий индекс по набору полей [VBN, -LH_AveReloadNum]
   public: void SetIndex_VBN__LH_AveReloadNum ();
// Установить текущий индекс по набору полей [VBN, -LH_Shows]
   public: void SetIndex_VBN__LH_Shows ();
// Установить текущий индекс по набору полей [VBN, -LH_Clicks]
   public: void SetIndex_VBN__LH_Clicks ();
// Установить текущий индекс по набору полей [VBN, -LH_CTR_Prc]
   public: void SetIndex_VBN__LH_CTR_Prc ();
// Установить текущий индекс по набору полей [VBN, -LH_CPH_Prc]
   public: void SetIndex_VBN__LH_CPH_Prc ();
// Установить текущий индекс по набору полей [VBN, -CustomIndex1]
   public: void SetIndex_VBN__CustomIndex1 ();
// Установить текущий индекс по набору полей [VBN, -CustomIndex2]
   public: void SetIndex_VBN__CustomIndex2 ();
// Установить текущий индекс по набору полей [VBN, -CustomIndex3]
   public: void SetIndex_VBN__CustomIndex3 ();
// Установить текущий индекс по набору полей [VBN, -CustomIndex4]
   public: void SetIndex_VBN__CustomIndex4 ();
// Установить текущий индекс по набору полей [VBN, -CustomIndex5]
   public: void SetIndex_VBN__CustomIndex5 ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_SiteProfile
#endif
#ifdef USES_OC_SiteProfile
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "SiteProfile"
// 
class OC_SiteProfile: public OC_Object <OC_SiteProfile>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_SiteProfile  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_SiteProfile  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_SiteProfile  (const OC_SiteProfile& from);
// Деструктор контроллера объекта
   public: ~OC_SiteProfile ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SiteProfile& operator= (const OC_SiteProfile& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SiteProfile& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_SiteProfile& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_SiteProfile& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_SiteProfile& operator << (OC_SiteProfile& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_SiteProfile& operator >> (OC_SiteProfile& from);

// Поле:   string SiteProfile::Name
   public: CSmartField      <OD_SiteProfile, string     >    m_Name;
// Поле:   byte SiteProfile::VBN
   public: CSmartField      <OD_SiteProfile, byte       >    m_VBN;
// Поле:   int SiteProfile::LastModified
   public: CSmartField      <OD_SiteProfile, int        >    m_LastModified;
// Поле:   identifier SiteProfile::OwnerID
   public: CSmartField      <OD_SiteProfile, identifier >    m_OwnerID;
// Поле:   int SiteProfile::MaxFileSize
   public: CSmartField      <OD_SiteProfile, int        >    m_MaxFileSize;
// Поле:   bool SiteProfile::UseKeywords
   public: CSmartField      <OD_SiteProfile, bool       >    m_UseKeywords;
// Поле:   bool SiteProfile::StaticSupport
   public: CSmartField      <OD_SiteProfile, bool       >    m_StaticSupport;
// Поле:   bool SiteProfile::Allowed
   public: CSmartField      <OD_SiteProfile, bool       >    m_Allowed;
// Поле:   byte SiteProfile::ObjectState
   public: CSmartField      <OD_SiteProfile, byte       >    m_ObjectState;
// Поле:   identifier SiteProfile::TagID
   public: CSmartField      <OD_SiteProfile, identifier >    m_TagID;
// Поле:   bool SiteProfile::TagBool
   public: CSmartField      <OD_SiteProfile, bool       >    m_TagBool;
// Поле:   int SiteProfile::TagInt
   public: CSmartField      <OD_SiteProfile, int        >    m_TagInt;
// Поле:   int SiteProfile::CacheTime
   public: CSmartField      <OD_SiteProfile, int        >    m_CacheTime;
// Поле:   identifier SiteProfile::Site []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_Site;
// Поле:   identifier SiteProfile::DefaultKeyword []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_DefaultKeyword;
// Поле:   identifier SiteProfile::BannerInclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_BannerInclude;
// Поле:   identifier SiteProfile::BannerExclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_BannerExclude;
// Поле:   identifier SiteProfile::SiteInclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_SiteInclude;
// Поле:   identifier SiteProfile::SiteExclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_SiteExclude;
// Поле:   byte SiteProfile::ba_BannerConceptInclude []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_BannerConceptInclude;
// Поле:   byte SiteProfile::ba_BannerConceptExclude []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_BannerConceptExclude;
// Поле:   byte SiteProfile::eba_BannerConcept []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_eba_BannerConcept;
// Поле:   int SiteProfile::Price []
   public: CSmartFieldArray <OD_SiteProfile, int        >    m_Price;
// Поле:   byte SiteProfile::ba_ModeratorComment []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_ModeratorComment;
// Поле:   identifier SiteProfile::ReservedID []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_ReservedID;
// Поле:   int SiteProfile::ReservedInt []
   public: CSmartFieldArray <OD_SiteProfile, int        >    m_ReservedInt;
// Поле:   string SiteProfile::ReservedString []
   public: CSmartFieldArray <OD_SiteProfile, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_ShowEvent
#endif
#ifdef USES_OC_ShowEvent
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "ShowEvent"
// 
class OC_ShowEvent: public OC_Object <OC_ShowEvent>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_ShowEvent  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_ShowEvent  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_ShowEvent  (const OC_ShowEvent& from);
// Деструктор контроллера объекта
   public: ~OC_ShowEvent ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ShowEvent& operator= (const OC_ShowEvent& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ShowEvent& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_ShowEvent& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_ShowEvent& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_ShowEvent& operator << (OC_ShowEvent& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_ShowEvent& operator >> (OC_ShowEvent& from);

// Поле:   identifier ShowEvent::SiteID
   public: CSmartField      <OD_ShowEvent, identifier >    m_SiteID;
// Поле:   identifier ShowEvent::ViewerID
   public: CSmartField      <OD_ShowEvent, identifier >    m_ViewerID;
// Поле:   int ShowEvent::Time
   public: CSmartField      <OD_ShowEvent, int        >    m_Time;
// Поле:   int ShowEvent::ExitCode
   public: CSmartField      <OD_ShowEvent, int        >    m_ExitCode;
// Поле:   identifier ShowEvent::TagID
   public: CSmartField      <OD_ShowEvent, identifier >    m_TagID;
// Поле:   int ShowEvent::TagInt
   public: CSmartField      <OD_ShowEvent, int        >    m_TagInt;
// Поле:   bool ShowEvent::TagBool
   public: CSmartField      <OD_ShowEvent, bool       >    m_TagBool;
// Поле:   string ShowEvent::ReservedString
   public: CSmartField      <OD_ShowEvent, string     >    m_ReservedString;
// Поле:   int ShowEvent::CacheTime
   public: CSmartField      <OD_ShowEvent, int        >    m_CacheTime;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Time]
   public: void SetIndex_Time ();
// Установить текущий индекс по набору полей [SiteID, ViewerID, -Time]
   public: void SetIndex_SiteID_ViewerID__Time ();
// Установить текущий индекс по набору полей [SiteID, ViewerID]
   public: void SetIndex_SiteID_ViewerID ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Registry
#endif
#ifdef USES_OC_Registry
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Registry"
// 
class OC_Registry: public OC_Object <OC_Registry>
{
// Это класс контроллера мастер-объекта.
// При создании контроллера он автоматически устанавливается
// на единственный объект-данные этого класса.
// Для него недопустимым методы создания и инициализации (New,
// Open, ...), удаления (Delete) и работы с индексами.
   void About_class_OC_Master ();

// Конструктор мастер-класса.
// Контроллер автоматически установлен на объект!
// * Недопустимым методы создания и инициализации (New, Open, ...)
//   удаления (Delete) и работы с индексами.
   public: OC_Registry  ();// Деструктор контроллера объекта
   public: ~OC_Registry ();


// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();

// Поле:   string Registry::AdminPassword
   public: CSmartField      <OD_Registry, string     >    m_AdminPassword;
// Поле:   int Registry::CRN_InetAudience_Update
   public: CSmartField      <OD_Registry, int        >    m_CRN_InetAudience_Update;
// Поле:   int Registry::VisitorHistoryLength
   public: CSmartField      <OD_Registry, int        >    m_VisitorHistoryLength;
// Поле:   int Registry::MinimumHitsTime
   public: CSmartField      <OD_Registry, int        >    m_MinimumHitsTime;
// Поле:   int Registry::SuspiciousInfoSize
   public: CSmartField      <OD_Registry, int        >    m_SuspiciousInfoSize;
// Поле:   int Registry::ActiveViewersSize
   public: CSmartField      <OD_Registry, int        >    m_ActiveViewersSize;
// Поле:   int Registry::ReturnNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ReturnNumRateSize;
// Поле:   int Registry::DailyReferrerSize
   public: CSmartField      <OD_Registry, int        >    m_DailyReferrerSize;
// Поле:   int Registry::ClickNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ClickNumRateSize;
// Поле:   int Registry::ShowNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ShowNumRateSize;
// Поле:   int Registry::HitNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_HitNumRateSize;
// Поле:   int Registry::SessionTimeRateSize
   public: CSmartField      <OD_Registry, int        >    m_SessionTimeRateSize;
// Поле:   int Registry::CachePurgeTime_IPRecord
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_IPRecord;
// Поле:   int Registry::CachePurgeTime_RatingPlaceInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_RatingPlaceInfo;
// Поле:   int Registry::CachePurgeTime_SuspiciousInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SuspiciousInfo;
// Поле:   int Registry::CachePurgeTime_SearchWordsInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SearchWordsInfo;
// Поле:   int Registry::CachePurgeTime_DailyReferrerStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_DailyReferrerStats;
// Поле:   int Registry::CachePurgeTime_DayStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_DayStats;
// Поле:   int Registry::CachePurgeTime_YearStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_YearStats;
// Поле:   int Registry::CachePurgeTime_TimeStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_TimeStats;
// Поле:   int Registry::CachePurgeTime_ModeratorComment
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_ModeratorComment;
// Поле:   int Registry::CachePurgeTime_Keyword
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Keyword;
// Поле:   int Registry::CachePurgeTime_SiteList
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SiteList;
// Поле:   int Registry::CachePurgeTime_Concept
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Concept;
// Поле:   int Registry::CachePurgeTime_Language
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Language;
// Поле:   int Registry::CachePurgeTime_VBN
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_VBN;
// Поле:   int Registry::CachePurgeTime_Site
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Site;
// Поле:   int Registry::CachePurgeTime_Page
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Page;
// Поле:   int Registry::CachePurgeTime_BannerProfile
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_BannerProfile;
// Поле:   int Registry::CachePurgeTime_Banner
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Banner;
// Поле:   int Registry::CachePurgeTime_TradeStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_TradeStats;
// Поле:   int Registry::CachePurgeTime_User
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_User;
// Поле:   int Registry::CachePurgeTime_ViewerGroup
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_ViewerGroup;
// Поле:   int Registry::CachePurgeTime_Viewer
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Viewer;
// Поле:   int Registry::ReloadTimeThreshold
   public: CSmartField      <OD_Registry, int        >    m_ReloadTimeThreshold;
// Поле:   float Registry::ViewerCacheReloadThreshold
   public: CSmartField      <OD_Registry, float      >    m_ViewerCacheReloadThreshold;
// Поле:   float Registry::DefaultPriority
   public: CSmartField      <OD_Registry, float      >    m_DefaultPriority;
// Поле:   int Registry::BannerStore_Expire
   public: CSmartField      <OD_Registry, int        >    m_BannerStore_Expire;
// Поле:   int Registry::BannerStore_MaxLength
   public: CSmartField      <OD_Registry, int        >    m_BannerStore_MaxLength;
// Поле:   int Registry::SiteStore_Expire
   public: CSmartField      <OD_Registry, int        >    m_SiteStore_Expire;
// Поле:   int Registry::SiteStore_MaxLength
   public: CSmartField      <OD_Registry, int        >    m_SiteStore_MaxLength;
// Поле:   int Registry::MaxDailyEventsDefault
   public: CSmartField      <OD_Registry, int        >    m_MaxDailyEventsDefault;
// Поле:   identifier Registry::TagID1
   public: CSmartField      <OD_Registry, identifier >    m_TagID1;
// Поле:   identifier Registry::TagID2
   public: CSmartField      <OD_Registry, identifier >    m_TagID2;
// Поле:   identifier Registry::TagID3
   public: CSmartField      <OD_Registry, identifier >    m_TagID3;
// Поле:   bool Registry::TagBool1
   public: CSmartField      <OD_Registry, bool       >    m_TagBool1;
// Поле:   bool Registry::TagBool2
   public: CSmartField      <OD_Registry, bool       >    m_TagBool2;
// Поле:   bool Registry::TagBool3
   public: CSmartField      <OD_Registry, bool       >    m_TagBool3;
// Поле:   int Registry::TagInt1
   public: CSmartField      <OD_Registry, int        >    m_TagInt1;
// Поле:   int Registry::TagInt2
   public: CSmartField      <OD_Registry, int        >    m_TagInt2;
// Поле:   int Registry::TagInt3
   public: CSmartField      <OD_Registry, int        >    m_TagInt3;
// Поле:   identifier Registry::ConceptID_Sorted []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ConceptID_Sorted;
// Поле:   int Registry::ConceptNo_SortID []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptNo_SortID;
// Поле:   identifier Registry::ConceptID_SortNo []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ConceptID_SortNo;
// Поле:   int Registry::ConceptParent_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptParent_SortNo;
// Поле:   int Registry::ConceptType_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptType_SortNo;
// Поле:   int Registry::ConceptLevel_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptLevel_SortNo;
// Поле:   identifier Registry::Language []
   public: CSmartFieldArray <OD_Registry, identifier >    m_Language;
// Поле:   int Registry::LanguageNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_LanguageNo;
// Поле:   identifier Registry::VBN []
   public: CSmartFieldArray <OD_Registry, identifier >    m_VBN;
// Поле:   int Registry::VBNNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_VBNNo;
// Поле:   identifier Registry::ModeratorComment []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ModeratorComment;
// Поле:   int Registry::ModeratorCommentNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ModeratorCommentNo;
// Поле:   int Registry::CRA_InetAudience []
   public: CSmartFieldArray <OD_Registry, int        >    m_CRA_InetAudience;
// Поле:   int Registry::CRN_InetAudience []
   public: CSmartFieldArray <OD_Registry, int        >    m_CRN_InetAudience;
// Поле:   string Registry::IgnoredIP []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredIP;
// Поле:   string Registry::IgnoredUserAgent []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredUserAgent;
// Поле:   string Registry::IgnoredBrowser []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredBrowser;
// Поле:   string Registry::SearchEngines []
   public: CSmartFieldArray <OD_Registry, string     >    m_SearchEngines;
// Поле:   string Registry::Classifiers []
   public: CSmartFieldArray <OD_Registry, string     >    m_Classifiers;
// Поле:   int Registry::ReloadDistribution []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReloadDistribution;
// Поле:   identifier Registry::Viewers []
   public: CSmartFieldArray <OD_Registry, identifier >    m_Viewers;
// Поле:   identifier Registry::ReservedID1 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID1;
// Поле:   identifier Registry::ReservedID2 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID2;
// Поле:   identifier Registry::ReservedID3 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID3;
// Поле:   int Registry::ReservedInt1 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt1;
// Поле:   int Registry::ReservedInt2 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt2;
// Поле:   int Registry::ReservedInt3 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt3;
// Поле:   string Registry::ReservedString1 []
   public: CSmartFieldArray <OD_Registry, string     >    m_ReservedString1;
// Поле:   string Registry::ReservedString2 []
   public: CSmartFieldArray <OD_Registry, string     >    m_ReservedString2;
// Поле:   string Registry::ReservedString3 []
   public: CSmartFieldArray <OD_Registry, string     >    m_ReservedString3;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_VBN
#endif
#ifdef USES_OC_VBN
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "VBN"
// 
class OC_VBN: public OC_Object <OC_VBN>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_VBN  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_VBN  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_VBN  (const OC_VBN& from);
// Деструктор контроллера объекта
   public: ~OC_VBN ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_VBN& operator= (const OC_VBN& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_VBN& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_VBN& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_VBN& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_VBN& operator << (OC_VBN& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_VBN& operator >> (OC_VBN& from);

// Поле:   string VBN::Password
   public: CSmartField      <OD_VBN, string     >    m_Password;
// Поле:   string VBN::Name
   public: CSmartField      <OD_VBN, string     >    m_Name;
// Поле:   string VBN::Description
   public: CSmartField      <OD_VBN, string     >    m_Description;
// Поле:   bool VBN::IsModerated
   public: CSmartField      <OD_VBN, bool       >    m_IsModerated;
// Поле:   identifier VBN::DefaultLanguage
   public: CSmartField      <OD_VBN, identifier >    m_DefaultLanguage;
// Поле:   int VBN::DefaultTZOffset
   public: CSmartField      <OD_VBN, int        >    m_DefaultTZOffset;
// Поле:   identifier VBN::Owner
   public: CSmartField      <OD_VBN, identifier >    m_Owner;
// Поле:   identifier VBN::AdminEventList
   public: CSmartField      <OD_VBN, identifier >    m_AdminEventList;
// Поле:   byte VBN::No
   public: CSmartField      <OD_VBN, byte       >    m_No;
// Поле:   int VBN::OnlineVisitors
   public: CSmartField      <OD_VBN, int        >    m_OnlineVisitors;
// Поле:   identifier VBN::Hits
   public: CSmartField      <OD_VBN, identifier >    m_Hits;
// Поле:   identifier VBN::Hosts
   public: CSmartField      <OD_VBN, identifier >    m_Hosts;
// Поле:   identifier VBN::Visitors
   public: CSmartField      <OD_VBN, identifier >    m_Visitors;
// Поле:   identifier VBN::Shows
   public: CSmartField      <OD_VBN, identifier >    m_Shows;
// Поле:   identifier VBN::Clicks
   public: CSmartField      <OD_VBN, identifier >    m_Clicks;
// Поле:   identifier VBN::SessionTime
   public: CSmartField      <OD_VBN, identifier >    m_SessionTime;
// Поле:   identifier VBN::SessionNum
   public: CSmartField      <OD_VBN, identifier >    m_SessionNum;
// Поле:   int VBN::Total_Hosts
   public: CSmartField      <OD_VBN, int        >    m_Total_Hosts;
// Поле:   int VBN::Total_Shows
   public: CSmartField      <OD_VBN, int        >    m_Total_Shows;
// Поле:   int VBN::Total_Clicks
   public: CSmartField      <OD_VBN, int        >    m_Total_Clicks;
// Поле:   int VBN::Total_Hits
   public: CSmartField      <OD_VBN, int        >    m_Total_Hits;
// Поле:   int VBN::Total_Visitors
   public: CSmartField      <OD_VBN, int        >    m_Total_Visitors;
// Поле:   int VBN::Total_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_Total_VisitorReturns;
// Поле:   int VBN::Total_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_Total_AveSessionTime;
// Поле:   int VBN::Total_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_Total_AveReloadTime;
// Поле:   int VBN::Total_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_Total_AveReloadNum;
// Поле:   int VBN::LM_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LM_Visitors;
// Поле:   int VBN::LM_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LM_VisitorReturns;
// Поле:   int VBN::LM_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LM_VisitorReturns_Prc;
// Поле:   int VBN::LM_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LM_Hosts;
// Поле:   int VBN::LM_Shows
   public: CSmartField      <OD_VBN, int        >    m_LM_Shows;
// Поле:   int VBN::LM_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LM_Clicks;
// Поле:   int VBN::LM_Hits
   public: CSmartField      <OD_VBN, int        >    m_LM_Hits;
// Поле:   int VBN::LM_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LM_AveSessionTime;
// Поле:   int VBN::LM_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LM_AveReloadTime;
// Поле:   int VBN::LM_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LM_AveReloadNum;
// Поле:   int VBN::LW_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LW_Visitors;
// Поле:   int VBN::LW_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LW_VisitorReturns;
// Поле:   int VBN::LW_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LW_VisitorReturns_Prc;
// Поле:   int VBN::LW_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LW_Hosts;
// Поле:   int VBN::LW_Shows
   public: CSmartField      <OD_VBN, int        >    m_LW_Shows;
// Поле:   int VBN::LW_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LW_Clicks;
// Поле:   int VBN::LW_Hits
   public: CSmartField      <OD_VBN, int        >    m_LW_Hits;
// Поле:   int VBN::LW_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LW_AveSessionTime;
// Поле:   int VBN::LW_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LW_AveReloadTime;
// Поле:   int VBN::LW_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LW_AveReloadNum;
// Поле:   int VBN::LD_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LD_Visitors;
// Поле:   int VBN::LD_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LD_VisitorReturns;
// Поле:   int VBN::LD_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LD_VisitorReturns_Prc;
// Поле:   int VBN::LD_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LD_Hosts;
// Поле:   int VBN::LD_Shows
   public: CSmartField      <OD_VBN, int        >    m_LD_Shows;
// Поле:   int VBN::LD_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LD_Clicks;
// Поле:   int VBN::LD_Hits
   public: CSmartField      <OD_VBN, int        >    m_LD_Hits;
// Поле:   int VBN::LD_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LD_AveSessionTime;
// Поле:   int VBN::LD_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LD_AveReloadTime;
// Поле:   int VBN::LD_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LD_AveReloadNum;
// Поле:   int VBN::LH_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LH_Visitors;
// Поле:   int VBN::LH_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LH_VisitorReturns;
// Поле:   int VBN::LH_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LH_VisitorReturns_Prc;
// Поле:   int VBN::LH_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LH_Hosts;
// Поле:   int VBN::LH_Shows
   public: CSmartField      <OD_VBN, int        >    m_LH_Shows;
// Поле:   int VBN::LH_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LH_Clicks;
// Поле:   int VBN::LH_Hits
   public: CSmartField      <OD_VBN, int        >    m_LH_Hits;
// Поле:   int VBN::LH_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LH_AveSessionTime;
// Поле:   int VBN::LH_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LH_AveReloadTime;
// Поле:   int VBN::LH_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LH_AveReloadNum;
// Поле:   bool VBN::TagBool1
   public: CSmartField      <OD_VBN, bool       >    m_TagBool1;
// Поле:   bool VBN::TagBool2
   public: CSmartField      <OD_VBN, bool       >    m_TagBool2;
// Поле:   identifier VBN::TagID1
   public: CSmartField      <OD_VBN, identifier >    m_TagID1;
// Поле:   identifier VBN::TagID2
   public: CSmartField      <OD_VBN, identifier >    m_TagID2;
// Поле:   int VBN::TagInt1
   public: CSmartField      <OD_VBN, int        >    m_TagInt1;
// Поле:   int VBN::TagInt2
   public: CSmartField      <OD_VBN, int        >    m_TagInt2;
// Поле:   float VBN::TagFloat1
   public: CSmartField      <OD_VBN, float      >    m_TagFloat1;
// Поле:   float VBN::TagFloat2
   public: CSmartField      <OD_VBN, float      >    m_TagFloat2;
// Поле:   string VBN::TagString1
   public: CSmartField      <OD_VBN, string     >    m_TagString1;
// Поле:   string VBN::TagString2
   public: CSmartField      <OD_VBN, string     >    m_TagString2;
// Поле:   int VBN::CacheTime
   public: CSmartField      <OD_VBN, int        >    m_CacheTime;
// Поле:   byte VBN::ConceptMask []
   public: CSmartFieldArray <OD_VBN, byte       >    m_ConceptMask;
// Поле:   identifier VBN::ActiveViewersID []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ActiveViewersID;
// Поле:   int VBN::ActiveViewersHosts []
   public: CSmartFieldArray <OD_VBN, int        >    m_ActiveViewersHosts;
// Поле:   identifier VBN::ReservedID1 []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ReservedID1;
// Поле:   identifier VBN::ReservedID2 []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ReservedID2;
// Поле:   int VBN::ReservedInt1 []
   public: CSmartFieldArray <OD_VBN, int        >    m_ReservedInt1;
// Поле:   int VBN::ReservedInt2 []
   public: CSmartFieldArray <OD_VBN, int        >    m_ReservedInt2;
// Поле:   string VBN::ReservedString1 []
   public: CSmartFieldArray <OD_VBN, string     >    m_ReservedString1;
// Поле:   string VBN::ReservedString2 []
   public: CSmartFieldArray <OD_VBN, string     >    m_ReservedString2;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [No]
   public: void SetIndex_No ();
// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Language
#endif
#ifdef USES_OC_Language
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Language"
// 
class OC_Language: public OC_Object <OC_Language>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Language  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Language  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Language  (const OC_Language& from);
// Деструктор контроллера объекта
   public: ~OC_Language ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Language& operator= (const OC_Language& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Language& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Language& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Language& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Language& operator << (OC_Language& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Language& operator >> (OC_Language& from);

// Поле:   string Language::ShortName
   public: CSmartField      <OD_Language, string     >    m_ShortName;
// Поле:   int Language::No
   public: CSmartField      <OD_Language, int        >    m_No;
// Поле:   int Language::CacheTime
   public: CSmartField      <OD_Language, int        >    m_CacheTime;
// Поле:   string Language::Name []
   public: CSmartFieldArray <OD_Language, string     >    m_Name;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [No]
   public: void SetIndex_No ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Concept
#endif
#ifdef USES_OC_Concept
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Concept"
// 
class OC_Concept: public OC_Object <OC_Concept>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Concept  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Concept  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Concept  (const OC_Concept& from);
// Деструктор контроллера объекта
   public: ~OC_Concept ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Concept& operator= (const OC_Concept& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Concept& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Concept& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Concept& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Concept& operator << (OC_Concept& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Concept& operator >> (OC_Concept& from);

// Поле:   identifier Concept::Parent
   public: CSmartField      <OD_Concept, identifier >    m_Parent;
// Поле:   int Concept::Level
   public: CSmartField      <OD_Concept, int        >    m_Level;
// Поле:   string Concept::ShortName
   public: CSmartField      <OD_Concept, string     >    m_ShortName;
// Поле:   string Concept::Type
   public: CSmartField      <OD_Concept, string     >    m_Type;
// Поле:   int Concept::TypeNo
   public: CSmartField      <OD_Concept, int        >    m_TypeNo;
// Поле:   int Concept::No
   public: CSmartField      <OD_Concept, int        >    m_No;
// Поле:   identifier Concept::TagID
   public: CSmartField      <OD_Concept, identifier >    m_TagID;
// Поле:   int Concept::TagInt
   public: CSmartField      <OD_Concept, int        >    m_TagInt;
// Поле:   bool Concept::TagBool
   public: CSmartField      <OD_Concept, bool       >    m_TagBool;
// Поле:   int Concept::CacheTime
   public: CSmartField      <OD_Concept, int        >    m_CacheTime;
// Поле:   string Concept::Name []
   public: CSmartFieldArray <OD_Concept, string     >    m_Name;
// Поле:   string Concept::Description []
   public: CSmartFieldArray <OD_Concept, string     >    m_Description;
// Поле:   identifier Concept::Ancestor []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Ancestor;
// Поле:   int Concept::AncestorNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_AncestorNo;
// Поле:   int Concept::AncestorWeight []
   public: CSmartFieldArray <OD_Concept, int        >    m_AncestorWeight;
// Поле:   identifier Concept::AllAncestor []
   public: CSmartFieldArray <OD_Concept, identifier >    m_AllAncestor;
// Поле:   identifier Concept::AllAncestorNo []
   public: CSmartFieldArray <OD_Concept, identifier >    m_AllAncestorNo;
// Поле:   identifier Concept::Child []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Child;
// Поле:   int Concept::ChildNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_ChildNo;
// Поле:   identifier Concept::Descendant []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Descendant;
// Поле:   int Concept::DescendantNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_DescendantNo;
// Поле:   identifier Concept::VBN_ID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_VBN_ID;
// Поле:   identifier Concept::VBN_SiteList []
   public: CSmartFieldArray <OD_Concept, identifier >    m_VBN_SiteList;
// Поле:   int Concept::VBN_SiteListSize []
   public: CSmartFieldArray <OD_Concept, int        >    m_VBN_SiteListSize;
// Поле:   int Concept::ClickerConcept_Work []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Work;
// Поле:   int Concept::ClickerConcept_Home []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Home;
// Поле:   int Concept::ClickerConcept_Night []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Night;
// Поле:   identifier Concept::Ads_SiteID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Ads_SiteID;
// Поле:   int Concept::Ads_ShowRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ShowRate;
// Поле:   int Concept::Ads_ClickRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ClickRate;
// Поле:   int Concept::Ads_ViewRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ViewRate;
// Поле:   identifier Concept::ReservedID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_ReservedID;
// Поле:   int Concept::ReservedInt []
   public: CSmartFieldArray <OD_Concept, int        >    m_ReservedInt;
// Поле:   string Concept::ReservedString []
   public: CSmartFieldArray <OD_Concept, string     >    m_ReservedString;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Level]
   public: void SetIndex_Level ();
// Установить текущий индекс по полю [No]
   public: void SetIndex_No ();
// Установить текущий индекс по набору полей [Type, Level, ShortName]
   public: void SetIndex_Type_Level_ShortName ();
// Установить текущий индекс по полю [TypeNo]
   public: void SetIndex_TypeNo ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_SiteList
#endif
#ifdef USES_OC_SiteList
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "SiteList"
// 
class OC_SiteList: public OC_Object <OC_SiteList>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_SiteList  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_SiteList  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_SiteList  (const OC_SiteList& from);
// Деструктор контроллера объекта
   public: ~OC_SiteList ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SiteList& operator= (const OC_SiteList& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SiteList& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_SiteList& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_SiteList& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_SiteList& operator << (OC_SiteList& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_SiteList& operator >> (OC_SiteList& from);

// Поле:   int SiteList::CacheTime
   public: CSmartField      <OD_SiteList, int        >    m_CacheTime;
// Поле:   identifier SiteList::Site []
   public: CSmartFieldArray <OD_SiteList, identifier >    m_Site;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Keyword
#endif
#ifdef USES_OC_Keyword
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Keyword"
// 
class OC_Keyword: public OC_Object <OC_Keyword>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Keyword  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Keyword  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Keyword  (const OC_Keyword& from);
// Деструктор контроллера объекта
   public: ~OC_Keyword ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Keyword& operator= (const OC_Keyword& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Keyword& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Keyword& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Keyword& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Keyword& operator << (OC_Keyword& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Keyword& operator >> (OC_Keyword& from);

// Поле:   string Keyword::Word
   public: CSmartField      <OD_Keyword, string     >    m_Word;
// Поле:   int Keyword::CacheTime
   public: CSmartField      <OD_Keyword, int        >    m_CacheTime;
// Поле:   identifier Keyword::VBN_ID []
   public: CSmartFieldArray <OD_Keyword, identifier >    m_VBN_ID;
// Поле:   identifier Keyword::VBN_SiteList []
   public: CSmartFieldArray <OD_Keyword, identifier >    m_VBN_SiteList;
// Поле:   int Keyword::VBN_SiteListSize []
   public: CSmartFieldArray <OD_Keyword, int        >    m_VBN_SiteListSize;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Word]
   public: void SetIndex_Word ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_ModeratorComment
#endif
#ifdef USES_OC_ModeratorComment
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "ModeratorComment"
// 
class OC_ModeratorComment: public OC_Object <OC_ModeratorComment>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_ModeratorComment  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_ModeratorComment  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_ModeratorComment  (const OC_ModeratorComment& from);
// Деструктор контроллера объекта
   public: ~OC_ModeratorComment ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ModeratorComment& operator= (const OC_ModeratorComment& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ModeratorComment& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_ModeratorComment& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_ModeratorComment& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_ModeratorComment& operator << (OC_ModeratorComment& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_ModeratorComment& operator >> (OC_ModeratorComment& from);

// Поле:   int ModeratorComment::No
   public: CSmartField      <OD_ModeratorComment, int        >    m_No;
// Поле:   int ModeratorComment::CacheTime
   public: CSmartField      <OD_ModeratorComment, int        >    m_CacheTime;
// Поле:   string ModeratorComment::Name []
   public: CSmartFieldArray <OD_ModeratorComment, string     >    m_Name;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [No]
   public: void SetIndex_No ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_TimeStats
#endif
#ifdef USES_OC_TimeStats
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "TimeStats"
// 
class OC_TimeStats: public OC_Object <OC_TimeStats>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_TimeStats  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_TimeStats  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_TimeStats  (const OC_TimeStats& from);
// Деструктор контроллера объекта
   public: ~OC_TimeStats ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_TimeStats& operator= (const OC_TimeStats& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_TimeStats& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_TimeStats& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_TimeStats& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_TimeStats& operator << (OC_TimeStats& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_TimeStats& operator >> (OC_TimeStats& from);

// Поле:   int TimeStats::Total
   public: CSmartField      <OD_TimeStats, int        >    m_Total;
// Поле:   int TimeStats::TwoLastDaysMinute_year
   public: CSmartField      <OD_TimeStats, int        >    m_TwoLastDaysMinute_year;
// Поле:   int TimeStats::TwoLastDaysMinute_day_of_year
   public: CSmartField      <OD_TimeStats, int        >    m_TwoLastDaysMinute_day_of_year;
// Поле:   int TimeStats::LastAccessTime
   public: CSmartField      <OD_TimeStats, int        >    m_LastAccessTime;
// Поле:   int TimeStats::CacheTime
   public: CSmartField      <OD_TimeStats, int        >    m_CacheTime;
// Поле:   int TimeStats::Year []
   public: CSmartFieldArray <OD_TimeStats, int        >    m_Year;
// Поле:   identifier TimeStats::YearStats []
   public: CSmartFieldArray <OD_TimeStats, identifier >    m_YearStats;
// Поле:   int TimeStats::TwoLastDaysMinute []
   public: CSmartFieldArray <OD_TimeStats, int        >    m_TwoLastDaysMinute;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_YearStats
#endif
#ifdef USES_OC_YearStats
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "YearStats"
// 
class OC_YearStats: public OC_Object <OC_YearStats>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_YearStats  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_YearStats  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_YearStats  (const OC_YearStats& from);
// Деструктор контроллера объекта
   public: ~OC_YearStats ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_YearStats& operator= (const OC_YearStats& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_YearStats& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_YearStats& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_YearStats& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_YearStats& operator << (OC_YearStats& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_YearStats& operator >> (OC_YearStats& from);

// Поле:   int YearStats::LastAccessTime
   public: CSmartField      <OD_YearStats, int        >    m_LastAccessTime;
// Поле:   int YearStats::CacheTime
   public: CSmartField      <OD_YearStats, int        >    m_CacheTime;
// Поле:   int YearStats::DayTotal []
   public: CSmartFieldArray <OD_YearStats, int        >    m_DayTotal;
// Поле:   identifier YearStats::DayStats []
   public: CSmartFieldArray <OD_YearStats, identifier >    m_DayStats;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_DayStats
#endif
#ifdef USES_OC_DayStats
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "DayStats"
// 
class OC_DayStats: public OC_Object <OC_DayStats>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_DayStats  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_DayStats  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_DayStats  (const OC_DayStats& from);
// Деструктор контроллера объекта
   public: ~OC_DayStats ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_DayStats& operator= (const OC_DayStats& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_DayStats& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_DayStats& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_DayStats& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_DayStats& operator << (OC_DayStats& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_DayStats& operator >> (OC_DayStats& from);

// Поле:   int DayStats::LastAccessTime
   public: CSmartField      <OD_DayStats, int        >    m_LastAccessTime;
// Поле:   int DayStats::CacheTime
   public: CSmartField      <OD_DayStats, int        >    m_CacheTime;
// Поле:   int DayStats::HourTotal []
   public: CSmartFieldArray <OD_DayStats, int        >    m_HourTotal;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Referrer
#endif
#ifdef USES_OC_Referrer
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Referrer"
// 
class OC_Referrer: public OC_Object <OC_Referrer>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Referrer  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Referrer  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Referrer  (const OC_Referrer& from);
// Деструктор контроллера объекта
   public: ~OC_Referrer ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Referrer& operator= (const OC_Referrer& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Referrer& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Referrer& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Referrer& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Referrer& operator << (OC_Referrer& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Referrer& operator >> (OC_Referrer& from);

// Поле:   identifier Referrer::CRC
   public: CSmartField      <OD_Referrer, identifier >    m_CRC;
// Поле:   string Referrer::Referrer
   public: CSmartField      <OD_Referrer, string     >    m_Referrer;
// Поле:   int Referrer::Count
   public: CSmartField      <OD_Referrer, int        >    m_Count;
// Поле:   int Referrer::LastAccessTime
   public: CSmartField      <OD_Referrer, int        >    m_LastAccessTime;
// Поле:   int Referrer::CacheTime
   public: CSmartField      <OD_Referrer, int        >    m_CacheTime;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [CRC]
   public: void SetIndex_CRC ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_DailyReferrerStats
#endif
#ifdef USES_OC_DailyReferrerStats
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "DailyReferrerStats"
// 
class OC_DailyReferrerStats: public OC_Object <OC_DailyReferrerStats>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_DailyReferrerStats  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_DailyReferrerStats  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_DailyReferrerStats  (const OC_DailyReferrerStats& from);
// Деструктор контроллера объекта
   public: ~OC_DailyReferrerStats ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_DailyReferrerStats& operator= (const OC_DailyReferrerStats& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_DailyReferrerStats& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_DailyReferrerStats& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_DailyReferrerStats& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_DailyReferrerStats& operator << (OC_DailyReferrerStats& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_DailyReferrerStats& operator >> (OC_DailyReferrerStats& from);

// Поле:   identifier DailyReferrerStats::SiteID
   public: CSmartField      <OD_DailyReferrerStats, identifier >    m_SiteID;
// Поле:   int DailyReferrerStats::TimeStamp
   public: CSmartField      <OD_DailyReferrerStats, int        >    m_TimeStamp;
// Поле:   int DailyReferrerStats::CacheTime
   public: CSmartField      <OD_DailyReferrerStats, int        >    m_CacheTime;
// Поле:   identifier DailyReferrerStats::Referrer []
   public: CSmartFieldArray <OD_DailyReferrerStats, identifier >    m_Referrer;
// Поле:   int DailyReferrerStats::Count []
   public: CSmartFieldArray <OD_DailyReferrerStats, int        >    m_Count;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_SearchWordsInfo
#endif
#ifdef USES_OC_SearchWordsInfo
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "SearchWordsInfo"
// 
class OC_SearchWordsInfo: public OC_Object <OC_SearchWordsInfo>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_SearchWordsInfo  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_SearchWordsInfo  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_SearchWordsInfo  (const OC_SearchWordsInfo& from);
// Деструктор контроллера объекта
   public: ~OC_SearchWordsInfo ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SearchWordsInfo& operator= (const OC_SearchWordsInfo& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SearchWordsInfo& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_SearchWordsInfo& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_SearchWordsInfo& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_SearchWordsInfo& operator << (OC_SearchWordsInfo& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_SearchWordsInfo& operator >> (OC_SearchWordsInfo& from);

// Поле:   identifier SearchWordsInfo::SiteID
   public: CSmartField      <OD_SearchWordsInfo, identifier >    m_SiteID;
// Поле:   int SearchWordsInfo::CacheTime
   public: CSmartField      <OD_SearchWordsInfo, int        >    m_CacheTime;
// Поле:   string SearchWordsInfo::Words []
   public: CSmartFieldArray <OD_SearchWordsInfo, string     >    m_Words;
// Поле:   int SearchWordsInfo::Count []
   public: CSmartFieldArray <OD_SearchWordsInfo, int        >    m_Count;
// Поле:   int SearchWordsInfo::LastAccessTime []
   public: CSmartFieldArray <OD_SearchWordsInfo, int        >    m_LastAccessTime;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_SuspiciousInfo
#endif
#ifdef USES_OC_SuspiciousInfo
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "SuspiciousInfo"
// 
class OC_SuspiciousInfo: public OC_Object <OC_SuspiciousInfo>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_SuspiciousInfo  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_SuspiciousInfo  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_SuspiciousInfo  (const OC_SuspiciousInfo& from);
// Деструктор контроллера объекта
   public: ~OC_SuspiciousInfo ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SuspiciousInfo& operator= (const OC_SuspiciousInfo& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SuspiciousInfo& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_SuspiciousInfo& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_SuspiciousInfo& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_SuspiciousInfo& operator << (OC_SuspiciousInfo& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_SuspiciousInfo& operator >> (OC_SuspiciousInfo& from);

// Поле:   identifier SuspiciousInfo::Site
   public: CSmartField      <OD_SuspiciousInfo, identifier >    m_Site;
// Поле:   int SuspiciousInfo::Pointer
   public: CSmartField      <OD_SuspiciousInfo, int        >    m_Pointer;
// Поле:   int SuspiciousInfo::CacheTime
   public: CSmartField      <OD_SuspiciousInfo, int        >    m_CacheTime;
// Поле:   identifier SuspiciousInfo::Viewer []
   public: CSmartFieldArray <OD_SuspiciousInfo, identifier >    m_Viewer;
// Поле:   string SuspiciousInfo::Referrer []
   public: CSmartFieldArray <OD_SuspiciousInfo, string     >    m_Referrer;
// Поле:   int SuspiciousInfo::Time []
   public: CSmartFieldArray <OD_SuspiciousInfo, int        >    m_Time;
// Поле:   int SuspiciousInfo::EventType []
   public: CSmartFieldArray <OD_SuspiciousInfo, int        >    m_EventType;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_RatingPlaceInfo
#endif
#ifdef USES_OC_RatingPlaceInfo
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "RatingPlaceInfo"
// 
class OC_RatingPlaceInfo: public OC_Object <OC_RatingPlaceInfo>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_RatingPlaceInfo  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_RatingPlaceInfo  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_RatingPlaceInfo  (const OC_RatingPlaceInfo& from);
// Деструктор контроллера объекта
   public: ~OC_RatingPlaceInfo ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_RatingPlaceInfo& operator= (const OC_RatingPlaceInfo& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_RatingPlaceInfo& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_RatingPlaceInfo& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_RatingPlaceInfo& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_RatingPlaceInfo& operator << (OC_RatingPlaceInfo& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_RatingPlaceInfo& operator >> (OC_RatingPlaceInfo& from);

// Поле:   identifier RatingPlaceInfo::Site
   public: CSmartField      <OD_RatingPlaceInfo, identifier >    m_Site;
// Поле:   int RatingPlaceInfo::LHP_Pointer
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LHP_Pointer;
// Поле:   int RatingPlaceInfo::LDP_Pointer
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LDP_Pointer;
// Поле:   int RatingPlaceInfo::LDP_UpdateTime
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LDP_UpdateTime;
// Поле:   float RatingPlaceInfo::DailyPositionDiff
   public: CSmartField      <OD_RatingPlaceInfo, float      >    m_DailyPositionDiff;
// Поле:   int RatingPlaceInfo::CacheTime
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_CacheTime;
// Поле:   int RatingPlaceInfo::LastHourPosition []
   public: CSmartFieldArray <OD_RatingPlaceInfo, int        >    m_LastHourPosition;
// Поле:   float RatingPlaceInfo::LastDailyPosition []
   public: CSmartFieldArray <OD_RatingPlaceInfo, float      >    m_LastDailyPosition;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_IPRecord
#endif
#ifdef USES_OC_IPRecord
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "IPRecord"
// 
class OC_IPRecord: public OC_Object <OC_IPRecord>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_IPRecord  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_IPRecord  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_IPRecord  (const OC_IPRecord& from);
// Деструктор контроллера объекта
   public: ~OC_IPRecord ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_IPRecord& operator= (const OC_IPRecord& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_IPRecord& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_IPRecord& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_IPRecord& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_IPRecord& operator << (OC_IPRecord& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_IPRecord& operator >> (OC_IPRecord& from);

// Поле:   int IPRecord::Count
   public: CSmartField      <OD_IPRecord, int        >    m_Count;
// Поле:   string IPRecord::Mask
   public: CSmartField      <OD_IPRecord, string     >    m_Mask;
// Поле:   string IPRecord::First
   public: CSmartField      <OD_IPRecord, string     >    m_First;
// Поле:   string IPRecord::Last
   public: CSmartField      <OD_IPRecord, string     >    m_Last;
// Поле:   bool IPRecord::Checked
   public: CSmartField      <OD_IPRecord, bool       >    m_Checked;
// Поле:   int IPRecord::CacheTime
   public: CSmartField      <OD_IPRecord, int        >    m_CacheTime;
// Поле:   identifier IPRecord::Hits
   public: CSmartField      <OD_IPRecord, identifier >    m_Hits;
// Поле:   identifier IPRecord::Hosts
   public: CSmartField      <OD_IPRecord, identifier >    m_Hosts;
// Поле:   identifier IPRecord::Visitors
   public: CSmartField      <OD_IPRecord, identifier >    m_Visitors;
// Поле:   identifier IPRecord::Anonymous
   public: CSmartField      <OD_IPRecord, identifier >    m_Anonymous;
// Поле:   identifier IPRecord::Suspicious
   public: CSmartField      <OD_IPRecord, identifier >    m_Suspicious;
// Поле:   int IPRecord::Total_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Hits;
// Поле:   int IPRecord::Total_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Hosts;
// Поле:   int IPRecord::Total_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Visitors;
// Поле:   int IPRecord::Total_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Anonymous;
// Поле:   int IPRecord::Total_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Suspicious;
// Поле:   int IPRecord::LM_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Hits;
// Поле:   int IPRecord::LM_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Hosts;
// Поле:   int IPRecord::LM_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Visitors;
// Поле:   int IPRecord::LM_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Anonymous;
// Поле:   int IPRecord::LM_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Suspicious;
// Поле:   int IPRecord::LW_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Hits;
// Поле:   int IPRecord::LW_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Hosts;
// Поле:   int IPRecord::LW_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Visitors;
// Поле:   int IPRecord::LW_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Anonymous;
// Поле:   int IPRecord::LW_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Suspicious;
// Поле:   int IPRecord::LD_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Hits;
// Поле:   int IPRecord::LD_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Hosts;
// Поле:   int IPRecord::LD_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Visitors;
// Поле:   int IPRecord::LD_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Anonymous;
// Поле:   int IPRecord::LD_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Suspicious;
// Поле:   int IPRecord::LH_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Hits;
// Поле:   int IPRecord::LH_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Hosts;
// Поле:   int IPRecord::LH_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Visitors;
// Поле:   int IPRecord::LH_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Anonymous;
// Поле:   int IPRecord::LH_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Suspicious;
// Поле:   identifier IPRecord::ConceptID []
   public: CSmartFieldArray <OD_IPRecord, identifier >    m_ConceptID;
// Поле:   int IPRecord::ConceptNo []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_ConceptNo;
// Поле:   int IPRecord::CRA_Audience []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_CRA_Audience;
// Поле:   int IPRecord::CRA_Inquiry []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_CRA_Inquiry;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [Checked, Mask]
   public: void SetIndex_Checked_Mask ();
// Установить текущий индекс по набору полей [Checked, -Count]
   public: void SetIndex_Checked__Count ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_ViewerReference
#endif
#ifdef USES_OC_ViewerReference
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "ViewerReference"
// 
class OC_ViewerReference: public OC_Object <OC_ViewerReference>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_ViewerReference  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_ViewerReference  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_ViewerReference  (const OC_ViewerReference& from);
// Деструктор контроллера объекта
   public: ~OC_ViewerReference ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ViewerReference& operator= (const OC_ViewerReference& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_ViewerReference& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_ViewerReference& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_ViewerReference& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_ViewerReference& operator << (OC_ViewerReference& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_ViewerReference& operator >> (OC_ViewerReference& from);

// Поле:   identifier ViewerReference::ViewerID
   public: CSmartField      <OD_ViewerReference, identifier >    m_ViewerID;
// Поле:   string ViewerReference::IPAddress
   public: CSmartField      <OD_ViewerReference, string     >    m_IPAddress;
// Поле:   identifier ViewerReference::IPAddressHash
   public: CSmartField      <OD_ViewerReference, identifier >    m_IPAddressHash;
// Поле:   int ViewerReference::CacheTime
   public: CSmartField      <OD_ViewerReference, int        >    m_CacheTime;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [IPAddressHash]
   public: void SetIndex_IPAddressHash ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_AbstractObject
#endif
#ifdef USES_OC_AbstractObject
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "AbstractObject"
// 
class OC_AbstractObject: public OC_Object <OC_AbstractObject>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_AbstractObject  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_AbstractObject  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_AbstractObject  (const OC_AbstractObject& from);
// Деструктор контроллера объекта
   public: ~OC_AbstractObject ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_AbstractObject& operator= (const OC_AbstractObject& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_AbstractObject& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_AbstractObject& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_AbstractObject& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_AbstractObject& operator << (OC_AbstractObject& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_AbstractObject& operator >> (OC_AbstractObject& from);

// Поле:   string AbstractObject::Type
   public: CSmartField      <OD_AbstractObject, string     >    m_Type;
// Поле:   string AbstractObject::Name
   public: CSmartField      <OD_AbstractObject, string     >    m_Name;
// Поле:   string AbstractObject::Header1
   public: CSmartField      <OD_AbstractObject, string     >    m_Header1;
// Поле:   string AbstractObject::Header2
   public: CSmartField      <OD_AbstractObject, string     >    m_Header2;
// Поле:   string AbstractObject::Header3
   public: CSmartField      <OD_AbstractObject, string     >    m_Header3;
// Поле:   string AbstractObject::Body
   public: CSmartField      <OD_AbstractObject, string     >    m_Body;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [Type, Name, Header1, Header2, Header3]
   public: void SetIndex_Type_Name_Header1_Header2_Header3 ();
};
#endif
//------------------------------------------------------------------------------[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
