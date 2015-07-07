/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjData.h                                             []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Data contents for database objects                        []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/


#ifndef Lay_ObjData_h
#define Lay_ObjData_h


//----------------------------------------------------------------------------[]
#define OD_SAVE_SIMPLE_ARRAY(type,field)													\
		memcpy (file.GetPtr()+nOffset, 														\
			d_##field.GetPtr(), 																	\
			d_##field.GetSize()*sizeof(type));												\
		nOffset  += d_##field.GetSize()*sizeof(type);
//----------------------------------------------------------------------------[]
#define OD_LOAD_SIMPLE_ARRAY(type,field)													\
		memcpy (d_##field.GetPtr(), 															\
			file.GetPtr()+nOffset, 																\
			arr_size_##field*sizeof(type));													\
		nOffset  += arr_size_##field*sizeof(type);
//----------------------------------------------------------------------------[]





//------------------------------------------------------------------------------[]
//
// Идентификаторы классов
//
enum OBJ_CLASS_ID
{
   OBJ_CLASS_ID_Viewer = 0,
   OBJ_CLASS_ID_ViewerGroup = 1,
   OBJ_CLASS_ID_User = 2,
   OBJ_CLASS_ID_TradeStats = 3,
   OBJ_CLASS_ID_Banner = 4,
   OBJ_CLASS_ID_BannerProfile = 5,
   OBJ_CLASS_ID_Page = 6,
   OBJ_CLASS_ID_Site = 7,
   OBJ_CLASS_ID_SiteProfile = 8,
   OBJ_CLASS_ID_ShowEvent = 9,
   OBJ_CLASS_ID_Registry = 10,
   OBJ_CLASS_ID_VBN = 11,
   OBJ_CLASS_ID_Language = 12,
   OBJ_CLASS_ID_Concept = 13,
   OBJ_CLASS_ID_SiteList = 14,
   OBJ_CLASS_ID_Keyword = 15,
   OBJ_CLASS_ID_ModeratorComment = 16,
   OBJ_CLASS_ID_TimeStats = 17,
   OBJ_CLASS_ID_YearStats = 18,
   OBJ_CLASS_ID_DayStats = 19,
   OBJ_CLASS_ID_Referrer = 20,
   OBJ_CLASS_ID_DailyReferrerStats = 21,
   OBJ_CLASS_ID_SearchWordsInfo = 22,
   OBJ_CLASS_ID_SuspiciousInfo = 23,
   OBJ_CLASS_ID_RatingPlaceInfo = 24,
   OBJ_CLASS_ID_IPRecord = 25,
   OBJ_CLASS_ID_ViewerReference = 26,
   OBJ_CLASS_ID_AbstractObject = 27,
   OBJ_CLASS_ID_END
};






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Viewer"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Viewer
#endif
#ifdef USES_OC_Viewer
class OD_Viewer: public OD_BASE
{
public:
// Конструктор
   OD_Viewer (bool bFieldsInit);
// Деструктор
  ~OD_Viewer ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_Reference;
   string     d_Name;
   string     d_Email;
   string     d_UserAgent;
   bool       d_Anonymous;
   int        d_TotalShows;
   int        d_TotalClicks;
   string     d_IPAddress;
   string     d_Referrer;
   identifier d_IPAddressHash;
   int_arr        d_CRA_Site;
   int_arr        d_CRN_Site;
   int        d_CRN_Site_Update;
   int_arr        d_CRA_Click;
   int_arr        d_CRN_Click;
   identifier d_Group;
   int        d_TZOffset;
   int        d_CreationTime;
   int        d_LastVisitTime;
   identifier_arr d_Site;
   int_arr        d_Site_LastHit;
   int_arr        d_Site_Hits;
   int_arr        d_Site_LastHost;
   int_arr        d_Site_Hosts;
   int        d_TotalHosts;
   byte_arr       d_Site_Votings;
   byte_arr       d_Site_VoteDayNo;
   int_arr        d_CRA_Inquiry;
   int_arr        d_CRN_Inquiry;
   identifier d_Site_SessionLastSiteID;
   identifier_arr d_Banner;
   int_arr        d_Banner_LastViewed;
   int_arr        d_Banner_ShowClick;
   int        d_BannerClickTime;
   identifier d_BannerClickID;
   identifier d_BannerClickSiteID;
   int        d_BannerClickHitCount;
   int        d_BannerClickSessionTime;
   float      d_ReloadNum;
   float      d_AveReloadTime;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "ViewerGroup"
// 
#ifdef  USES_OC_ALL
#define USES_OC_ViewerGroup
#endif
#ifdef USES_OC_ViewerGroup
class OD_ViewerGroup: public OD_BASE
{
public:
// Конструктор
   OD_ViewerGroup (bool bFieldsInit);
// Деструктор
  ~OD_ViewerGroup ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int_arr        d_ConceptStats;
   identifier_arr d_Viewer;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "User"
// 
#ifdef  USES_OC_ALL
#define USES_OC_User
#endif
#ifdef USES_OC_User
class OD_User: public OD_BASE
{
public:
// Конструктор
   OD_User (bool bFieldsInit);
// Деструктор
  ~OD_User ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Login;
   string     d_Password;
   bool       d_ForgetPassword;
   string     d_FullName;
   identifier d_InterfaceLanguage;
   bool       d_InterfaceType;
   int        d_CreationTime;
   byte       d_VBN;
   byte_arr       d_ba_Concept;
   byte_arr       d_eba_Concept;
   string     d_Email;
   string     d_Phone;
   string     d_Fax;
   string     d_Address;
   string     d_URL;
   string     d_Comment;
   int        d_TZOffset;
   int        d_NotifyFreq;
   bool       d_NotifyHTML;
   int        d_NotifyDepth;
   identifier_arr d_Site;
   identifier_arr d_SiteProfile;
   identifier_arr d_Banner;
   identifier_arr d_BannerProfile;
   float      d_ShowsLeft;
   float      d_ClicksLeft;
   identifier d_TradeStats;
   bool       d_Allowed;
   byte       d_ObjectState;
   byte_arr       d_ba_ModeratorComment;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "TradeStats"
// 
#ifdef  USES_OC_ALL
#define USES_OC_TradeStats
#endif
#ifdef USES_OC_TradeStats
class OD_TradeStats: public OD_BASE
{
public:
// Конструктор
   OD_TradeStats (bool bFieldsInit);
// Деструктор
  ~OD_TradeStats ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int_arr        d_SoldShowDates;
   int_arr        d_SoldShowAmounts;
   string_arr     d_SoldShowBuyer;
   int_arr        d_BoughtShowDates;
   int_arr        d_BoughtShowAmounts;
   string_arr     d_BoughtShowSeller;
   int_arr        d_SoldClickDates;
   int_arr        d_SoldClickAmounts;
   string_arr     d_SoldClickBuyer;
   int_arr        d_BoughtClickDates;
   int_arr        d_BoughtClickAmounts;
   string_arr     d_BoughtClickSeller;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Banner"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Banner
#endif
#ifdef USES_OC_Banner
class OD_Banner: public OD_BASE
{
public:
// Конструктор
   OD_Banner (bool bFieldsInit);
// Деструктор
  ~OD_Banner ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_OwnerID;
   string     d_FileName;
   int        d_FileSize;
   int        d_UploadNo;
   int        d_CreationTime;
   byte       d_VBN;
   string     d_Description;
   bool       d_State;
   identifier d_Profile;
   identifier_arr d_SiteAnnounce;
   byte_arr       d_ba_Concept;
   byte_arr       d_eba_Concept;
   int        d_TotalShows;
   int        d_TotalClicks;
   bool       d_Allowed;
   byte       d_ObjectState;
   byte_arr       d_ba_ModeratorComment;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "BannerProfile"
// 
#ifdef  USES_OC_ALL
#define USES_OC_BannerProfile
#endif
#ifdef USES_OC_BannerProfile
class OD_BannerProfile: public OD_BASE
{
public:
// Конструктор
   OD_BannerProfile (bool bFieldsInit);
// Деструктор
  ~OD_BannerProfile ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Name;
   byte       d_VBN;
   int        d_LastModified;
   identifier d_OwnerID;
   identifier d_HREF;
   bool       d_Commercial;
   int        d_BannerType;
   identifier_arr d_SiteAnnounce;
   identifier_arr d_Banner;
   byte_arr       d_ba_Concept;
   byte_arr       d_eba_Concept;
   bool       d_State;
   string     d_AltText;
   byte_arr       d_ba_SiteConceptInclude;
   byte_arr       d_ba_SiteConceptExclude;
   byte_arr       d_eba_SiteConcept;
   identifier_arr d_SiteInclude;
   identifier_arr d_SiteExclude;
   string_arr     d_ViewerIPEnable;
   string_arr     d_ViewerIPDisable;
   byte_arr       d_ba_ViewerConceptInclude;
   byte_arr       d_ba_ViewerConceptExclude;
   byte_arr       d_eba_ViewerConcept;
   bool       d_UseLocalTime;
   int        d_ScheduleTZOffset;
   bool       d_ShowIfLocalUnknown;
   byte_arr       d_ba_Schedule;
   int        d_AutoOn;
   int        d_AutoOff;
   int        d_RepeatCount;
   int        d_RepeatTime;
   identifier_arr d_SiteTarget_SiteID;
   int_arr        d_SiteTarget_ShowRate;
   int_arr        d_SiteTarget_ClickRate;
   int_arr        d_SiteTarget_ViewRate;
   int_arr        d_ViewerConceptRate;
   int_arr        d_ShowNumRate;
   int_arr        d_ClickNumRate;
   int_arr        d_HitNumRate;
   int_arr        d_SessionTimeRate;
   bool       d_CountTypeByShows;
   int        d_MaxDailyClicks;
   int        d_MaxDailyShows;
   int        d_MaxDailyShowsChangeTime;
   int        d_TotalShows;
   int        d_TotalClicks;
   int        d_SessionEvents;
   float      d_Priority;
   bool       d_Allowed;
   byte       d_ObjectState;
   byte_arr       d_ba_ModeratorComment;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Page"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Page
#endif
#ifdef USES_OC_Page
class OD_Page: public OD_BASE
{
public:
// Конструктор
   OD_Page (bool bFieldsInit);
// Деструктор
  ~OD_Page ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_Site;
   int        d_No;
   string     d_URL;
   byte_arr       d_ba_Concept;
   byte_arr       d_eba_Concept;
   byte_arr       d_pba_Concept;
   int        d_CounterType;
   bool       d_ConceptSet;
   identifier_arr d_TimeStats;
   byte_arr       d_TimeStatsType;
   int_arr        d_CRA_Visitor;
   int_arr        d_CRN_Visitor;
   int        d_CRN_Visitor_Update;
   int_arr        d_CRN_VisitorIncr;
   int        d_CRN_VisitorIncr_Update;
   identifier_arr d_Referrer;
   int_arr        d_ReferrerCount;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Site"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Site
#endif
#ifdef USES_OC_Site
class OD_Site: public OD_BASE
{
public:
// Конструктор
   OD_Site (bool bFieldsInit);
// Деструктор
  ~OD_Site ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_OwnerID;
   byte       d_VBN;
   int        d_CreationTime;
   string     d_Alias;
   string     d_Name;
   string     d_Description;
   string_arr     d_Announce;
   string     d_URL;
   int        d_CounterType;
   bool       d_RateMySite;
   string     d_RateStatsViewPassword;
   bool       d_ShowAudience;
   int        d_ShowAudienceOffTime;
   identifier d_Profile;
   identifier_arr d_Keyword;
   string_arr     d_MirrorInclude;
   string_arr     d_MirrorExclude;
   string_arr     d_MirrorSubstr;
   string_arr     d_IgnoredIP;
   identifier_arr d_IgnoredViewerID;
   byte_arr       d_ba_Concept;
   byte_arr       d_pba_Concept;
   byte_arr       d_eba_Concept;
   int_arr        d_CRN_Self;
   identifier_arr d_Page;
   string_arr     d_PageName;
   int_arr        d_PageNo;
   identifier_arr d_AdBannerProfile;
   identifier d_SuspiciousInfo;
   int_arr        d_CRA_Visitor;
   int_arr        d_CRN_Visitor;
   int        d_CRN_Visitor_Update;
   int_arr        d_CRA_Inquiry;
   int_arr        d_CRN_Inquiry;
   int_arr        d_CRN_VisitorIncr;
   int        d_CRN_VisitorIncr_Update;
   identifier_arr d_Audience_SiteID;
   int_arr        d_Audience_Viewers;
   int_arr        d_Audience_Hosts;
   int_arr        d_Audience_SiteIDInclude;
   identifier_arr d_ActiveViewersID;
   int_arr        d_ActiveViewersHits;
   int        d_RecentPointer;
   identifier_arr d_RecentVisitor;
   identifier_arr d_RecentReferrer;
   int_arr        d_RecentTimeStamp;
   identifier_arr d_Referrer;
   int_arr        d_ReferrerCount;
   int        d_Referrer_LastReset;
   identifier_arr d_DailyReferrerStats;
   int_arr        d_DailyReferrerTimeStamp;
   identifier d_SearchWordsInfo;
   int_arr        d_Inquire;
   int        d_InquiredVisitorNum;
   int        d_SessionResetTime;
   int_arr        d_ReturnNumRate;
   int_arr        d_ShowNumRate;
   int        d_LastVisitTime;
   int        d_LastUpdateTime;
   identifier d_Loads;
   identifier d_Visitors;
   identifier d_Hosts;
   identifier d_Shows;
   identifier d_Clicks;
   identifier d_Clicks_Local;
   identifier d_Hits;
   identifier d_Hits_Local;
   identifier d_AnonymousHits;
   identifier d_SuspiciousHits;
   identifier d_SessionTime;
   identifier d_SessionTime_Local;
   identifier d_SessionNum;
   int        d_Total_Loads;
   int        d_Total_Hosts;
   int        d_Total_Hits;
   int        d_Total_AnonymousHits;
   int        d_Total_AnonymousHits_Prc;
   int        d_Total_SuspiciousHits_Prc;
   int        d_Total_Visitors;
   int        d_Total_VisitorReturns;
   int        d_Total_VisitorReturns_Prc;
   int        d_Total_SessionNum;
   int        d_Total_AveSessionTime;
   int        d_Total_AveReloadTime;
   int        d_Total_AveReloadNum;
   int        d_Total_Shows;
   int        d_Total_Clicks;
   int        d_Total_CTR_Prc;
   int        d_Total_CPH_Prc;
   int        d_Total_AnonymousVisitors;
   int        d_Total_AnonymousVisitors_Prc;
   int        d_Total_VisitorExperience;
   int        d_Ave_VisitorExperience;
   int        d_OnlineVisitors;
   int        d_Total_MouseOver;
   int        d_Total_Votes;
   int        d_Total_Votes_Sum;
   int        d_Total_Votes_Ave;
   int        d_LM_Loads;
   int        d_LM_Hosts;
   int        d_LM_Hits;
   int        d_LM_AnonymousHits;
   int        d_LM_AnonymousHits_Prc;
   int        d_LM_SuspiciousHits_Prc;
   int        d_LM_Visitors;
   int        d_LM_VisitorReturns;
   int        d_LM_VisitorReturns_Prc;
   int        d_LM_SessionNum;
   int        d_LM_AveSessionTime;
   int        d_LM_AveReloadTime;
   int        d_LM_AveReloadNum;
   int        d_LM_Shows;
   int        d_LM_Clicks;
   int        d_LM_CTR_Prc;
   int        d_LM_CPH_Prc;
   int        d_LW_Loads;
   int        d_LW_Hosts;
   int        d_LW_Hits;
   int        d_LW_AnonymousHits;
   int        d_LW_AnonymousHits_Prc;
   int        d_LW_SuspiciousHits_Prc;
   int        d_LW_Visitors;
   int        d_LW_VisitorReturns;
   int        d_LW_VisitorReturns_Prc;
   int        d_LW_SessionNum;
   int        d_LW_AveSessionTime;
   int        d_LW_AveReloadTime;
   int        d_LW_AveReloadNum;
   int        d_LW_Shows;
   int        d_LW_Clicks;
   int        d_LW_CTR_Prc;
   int        d_LW_CPH_Prc;
   int        d_LD_Loads;
   int        d_LD_Hosts;
   int        d_LD_Hits;
   int        d_LD_AnonymousHits;
   int        d_LD_AnonymousHits_Prc;
   int        d_LD_SuspiciousHits_Prc;
   int        d_LD_Visitors;
   int        d_LD_VisitorReturns;
   int        d_LD_VisitorReturns_Prc;
   int        d_LD_SessionNum;
   int        d_LD_AveSessionTime;
   int        d_LD_AveReloadTime;
   int        d_LD_AveReloadNum;
   int        d_LD_Shows;
   int        d_LD_Clicks;
   int        d_LD_CTR_Prc;
   int        d_LD_CPH_Prc;
   int        d_LH_Loads;
   int        d_LH_Hosts;
   int        d_LH_Hits;
   int        d_LH_AnonymousHits;
   int        d_LH_AnonymousHits_Prc;
   int        d_LH_SuspiciousHits_Prc;
   int        d_LH_Visitors;
   int        d_LH_VisitorReturns;
   int        d_LH_VisitorReturns_Prc;
   int        d_LH_SessionNum;
   int        d_LH_AveSessionTime;
   int        d_LH_AveReloadTime;
   int        d_LH_AveReloadNum;
   int        d_LH_Shows;
   int        d_LH_Clicks;
   int        d_LH_CTR_Prc;
   int        d_LH_CPH_Prc;
   int        d_CustomIndex1;
   int        d_CustomIndex2;
   int        d_CustomIndex3;
   int        d_CustomIndex4;
   int        d_CustomIndex5;
   bool       d_Allowed;
   byte       d_ObjectState;
   byte_arr       d_ba_ModeratorComment;
   identifier d_TagID;
   bool       d_TagBool;
   int        d_TagInt;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   identifier d_RatingPlaceInfo;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "SiteProfile"
// 
#ifdef  USES_OC_ALL
#define USES_OC_SiteProfile
#endif
#ifdef USES_OC_SiteProfile
class OD_SiteProfile: public OD_BASE
{
public:
// Конструктор
   OD_SiteProfile (bool bFieldsInit);
// Деструктор
  ~OD_SiteProfile ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Name;
   identifier_arr d_Site;
   byte       d_VBN;
   int        d_LastModified;
   identifier d_OwnerID;
   identifier_arr d_DefaultKeyword;
   identifier_arr d_BannerInclude;
   identifier_arr d_BannerExclude;
   identifier_arr d_SiteInclude;
   identifier_arr d_SiteExclude;
   int        d_MaxFileSize;
   bool       d_UseKeywords;
   byte_arr       d_ba_BannerConceptInclude;
   byte_arr       d_ba_BannerConceptExclude;
   byte_arr       d_eba_BannerConcept;
   int_arr        d_Price;
   bool       d_StaticSupport;
   bool       d_Allowed;
   byte       d_ObjectState;
   byte_arr       d_ba_ModeratorComment;
   identifier d_TagID;
   bool       d_TagBool;
   int        d_TagInt;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "ShowEvent"
// 
#ifdef  USES_OC_ALL
#define USES_OC_ShowEvent
#endif
#ifdef USES_OC_ShowEvent
class OD_ShowEvent: public OD_BASE
{
public:
// Конструктор
   OD_ShowEvent (bool bFieldsInit);
// Деструктор
  ~OD_ShowEvent ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_SiteID;
   identifier d_ViewerID;
   int        d_Time;
   int        d_ExitCode;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   string     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Registry"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Registry
#endif
#ifdef USES_OC_Registry
class OD_Registry: public OD_BASE
{
public:
// Конструктор
   OD_Registry (bool bFieldsInit);
// Деструктор
  ~OD_Registry ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_AdminPassword;
   identifier_arr d_ConceptID_Sorted;
   int_arr        d_ConceptNo_SortID;
   identifier_arr d_ConceptID_SortNo;
   int_arr        d_ConceptParent_SortNo;
   int_arr        d_ConceptType_SortNo;
   int_arr        d_ConceptLevel_SortNo;
   identifier_arr d_Language;
   int_arr        d_LanguageNo;
   identifier_arr d_VBN;
   int_arr        d_VBNNo;
   identifier_arr d_ModeratorComment;
   int_arr        d_ModeratorCommentNo;
   int_arr        d_CRA_InetAudience;
   int_arr        d_CRN_InetAudience;
   int        d_CRN_InetAudience_Update;
   int        d_VisitorHistoryLength;
   int        d_MinimumHitsTime;
   int        d_SuspiciousInfoSize;
   int        d_ActiveViewersSize;
   int        d_ReturnNumRateSize;
   int        d_DailyReferrerSize;
   int        d_ClickNumRateSize;
   int        d_ShowNumRateSize;
   int        d_HitNumRateSize;
   int        d_SessionTimeRateSize;
   string_arr     d_IgnoredIP;
   string_arr     d_IgnoredUserAgent;
   string_arr     d_IgnoredBrowser;
   string_arr     d_SearchEngines;
   string_arr     d_Classifiers;
   int        d_CachePurgeTime_IPRecord;
   int        d_CachePurgeTime_RatingPlaceInfo;
   int        d_CachePurgeTime_SuspiciousInfo;
   int        d_CachePurgeTime_SearchWordsInfo;
   int        d_CachePurgeTime_DailyReferrerStats;
   int        d_CachePurgeTime_DayStats;
   int        d_CachePurgeTime_YearStats;
   int        d_CachePurgeTime_TimeStats;
   int        d_CachePurgeTime_ModeratorComment;
   int        d_CachePurgeTime_Keyword;
   int        d_CachePurgeTime_SiteList;
   int        d_CachePurgeTime_Concept;
   int        d_CachePurgeTime_Language;
   int        d_CachePurgeTime_VBN;
   int        d_CachePurgeTime_Site;
   int        d_CachePurgeTime_Page;
   int        d_CachePurgeTime_BannerProfile;
   int        d_CachePurgeTime_Banner;
   int        d_CachePurgeTime_TradeStats;
   int        d_CachePurgeTime_User;
   int        d_CachePurgeTime_ViewerGroup;
   int        d_CachePurgeTime_Viewer;
   int        d_ReloadTimeThreshold;
   float      d_ViewerCacheReloadThreshold;
   int_arr        d_ReloadDistribution;
   identifier_arr d_Viewers;
   float      d_DefaultPriority;
   int        d_BannerStore_Expire;
   int        d_BannerStore_MaxLength;
   int        d_SiteStore_Expire;
   int        d_SiteStore_MaxLength;
   int        d_MaxDailyEventsDefault;
   identifier d_TagID1;
   identifier d_TagID2;
   identifier d_TagID3;
   bool       d_TagBool1;
   bool       d_TagBool2;
   bool       d_TagBool3;
   int        d_TagInt1;
   int        d_TagInt2;
   int        d_TagInt3;
   identifier_arr d_ReservedID1;
   identifier_arr d_ReservedID2;
   identifier_arr d_ReservedID3;
   int_arr        d_ReservedInt1;
   int_arr        d_ReservedInt2;
   int_arr        d_ReservedInt3;
   string_arr     d_ReservedString1;
   string_arr     d_ReservedString2;
   string_arr     d_ReservedString3;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "VBN"
// 
#ifdef  USES_OC_ALL
#define USES_OC_VBN
#endif
#ifdef USES_OC_VBN
class OD_VBN: public OD_BASE
{
public:
// Конструктор
   OD_VBN (bool bFieldsInit);
// Деструктор
  ~OD_VBN ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Password;
   string     d_Name;
   string     d_Description;
   bool       d_IsModerated;
   identifier d_DefaultLanguage;
   int        d_DefaultTZOffset;
   identifier d_Owner;
   byte_arr       d_ConceptMask;
   identifier d_AdminEventList;
   byte       d_No;
   int        d_OnlineVisitors;
   identifier_arr d_ActiveViewersID;
   int_arr        d_ActiveViewersHosts;
   identifier d_Hits;
   identifier d_Hosts;
   identifier d_Visitors;
   identifier d_Shows;
   identifier d_Clicks;
   identifier d_SessionTime;
   identifier d_SessionNum;
   int        d_Total_Hosts;
   int        d_Total_Shows;
   int        d_Total_Clicks;
   int        d_Total_Hits;
   int        d_Total_Visitors;
   int        d_Total_VisitorReturns;
   int        d_Total_AveSessionTime;
   int        d_Total_AveReloadTime;
   int        d_Total_AveReloadNum;
   int        d_LM_Visitors;
   int        d_LM_VisitorReturns;
   int        d_LM_VisitorReturns_Prc;
   int        d_LM_Hosts;
   int        d_LM_Shows;
   int        d_LM_Clicks;
   int        d_LM_Hits;
   int        d_LM_AveSessionTime;
   int        d_LM_AveReloadTime;
   int        d_LM_AveReloadNum;
   int        d_LW_Visitors;
   int        d_LW_VisitorReturns;
   int        d_LW_VisitorReturns_Prc;
   int        d_LW_Hosts;
   int        d_LW_Shows;
   int        d_LW_Clicks;
   int        d_LW_Hits;
   int        d_LW_AveSessionTime;
   int        d_LW_AveReloadTime;
   int        d_LW_AveReloadNum;
   int        d_LD_Visitors;
   int        d_LD_VisitorReturns;
   int        d_LD_VisitorReturns_Prc;
   int        d_LD_Hosts;
   int        d_LD_Shows;
   int        d_LD_Clicks;
   int        d_LD_Hits;
   int        d_LD_AveSessionTime;
   int        d_LD_AveReloadTime;
   int        d_LD_AveReloadNum;
   int        d_LH_Visitors;
   int        d_LH_VisitorReturns;
   int        d_LH_VisitorReturns_Prc;
   int        d_LH_Hosts;
   int        d_LH_Shows;
   int        d_LH_Clicks;
   int        d_LH_Hits;
   int        d_LH_AveSessionTime;
   int        d_LH_AveReloadTime;
   int        d_LH_AveReloadNum;
   bool       d_TagBool1;
   bool       d_TagBool2;
   identifier d_TagID1;
   identifier d_TagID2;
   int        d_TagInt1;
   int        d_TagInt2;
   float      d_TagFloat1;
   float      d_TagFloat2;
   string     d_TagString1;
   string     d_TagString2;
   identifier_arr d_ReservedID1;
   identifier_arr d_ReservedID2;
   int_arr        d_ReservedInt1;
   int_arr        d_ReservedInt2;
   string_arr     d_ReservedString1;
   string_arr     d_ReservedString2;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Language"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Language
#endif
#ifdef USES_OC_Language
class OD_Language: public OD_BASE
{
public:
// Конструктор
   OD_Language (bool bFieldsInit);
// Деструктор
  ~OD_Language ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string_arr     d_Name;
   string     d_ShortName;
   int        d_No;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Concept"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Concept
#endif
#ifdef USES_OC_Concept
class OD_Concept: public OD_BASE
{
public:
// Конструктор
   OD_Concept (bool bFieldsInit);
// Деструктор
  ~OD_Concept ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string_arr     d_Name;
   string_arr     d_Description;
   identifier d_Parent;
   identifier_arr d_Ancestor;
   int_arr        d_AncestorNo;
   int_arr        d_AncestorWeight;
   identifier_arr d_AllAncestor;
   identifier_arr d_AllAncestorNo;
   identifier_arr d_Child;
   int_arr        d_ChildNo;
   identifier_arr d_Descendant;
   int_arr        d_DescendantNo;
   int        d_Level;
   string     d_ShortName;
   string     d_Type;
   int        d_TypeNo;
   identifier_arr d_VBN_ID;
   identifier_arr d_VBN_SiteList;
   int_arr        d_VBN_SiteListSize;
   int_arr        d_ClickerConcept_Work;
   int_arr        d_ClickerConcept_Home;
   int_arr        d_ClickerConcept_Night;
   identifier_arr d_Ads_SiteID;
   int_arr        d_Ads_ShowRate;
   int_arr        d_Ads_ClickRate;
   int_arr        d_Ads_ViewRate;
   int        d_No;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "SiteList"
// 
#ifdef  USES_OC_ALL
#define USES_OC_SiteList
#endif
#ifdef USES_OC_SiteList
class OD_SiteList: public OD_BASE
{
public:
// Конструктор
   OD_SiteList (bool bFieldsInit);
// Деструктор
  ~OD_SiteList ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier_arr d_Site;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Keyword"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Keyword
#endif
#ifdef USES_OC_Keyword
class OD_Keyword: public OD_BASE
{
public:
// Конструктор
   OD_Keyword (bool bFieldsInit);
// Деструктор
  ~OD_Keyword ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Word;
   identifier_arr d_VBN_ID;
   identifier_arr d_VBN_SiteList;
   int_arr        d_VBN_SiteListSize;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "ModeratorComment"
// 
#ifdef  USES_OC_ALL
#define USES_OC_ModeratorComment
#endif
#ifdef USES_OC_ModeratorComment
class OD_ModeratorComment: public OD_BASE
{
public:
// Конструктор
   OD_ModeratorComment (bool bFieldsInit);
// Деструктор
  ~OD_ModeratorComment ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string_arr     d_Name;
   int        d_No;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "TimeStats"
// 
#ifdef  USES_OC_ALL
#define USES_OC_TimeStats
#endif
#ifdef USES_OC_TimeStats
class OD_TimeStats: public OD_BASE
{
public:
// Конструктор
   OD_TimeStats (bool bFieldsInit);
// Деструктор
  ~OD_TimeStats ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int        d_Total;
   int_arr        d_Year;
   identifier_arr d_YearStats;
   int_arr        d_TwoLastDaysMinute;
   int        d_TwoLastDaysMinute_year;
   int        d_TwoLastDaysMinute_day_of_year;
   int        d_LastAccessTime;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "YearStats"
// 
#ifdef  USES_OC_ALL
#define USES_OC_YearStats
#endif
#ifdef USES_OC_YearStats
class OD_YearStats: public OD_BASE
{
public:
// Конструктор
   OD_YearStats (bool bFieldsInit);
// Деструктор
  ~OD_YearStats ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int_arr        d_DayTotal;
   identifier_arr d_DayStats;
   int        d_LastAccessTime;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "DayStats"
// 
#ifdef  USES_OC_ALL
#define USES_OC_DayStats
#endif
#ifdef USES_OC_DayStats
class OD_DayStats: public OD_BASE
{
public:
// Конструктор
   OD_DayStats (bool bFieldsInit);
// Деструктор
  ~OD_DayStats ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int_arr        d_HourTotal;
   int        d_LastAccessTime;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "Referrer"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Referrer
#endif
#ifdef USES_OC_Referrer
class OD_Referrer: public OD_BASE
{
public:
// Конструктор
   OD_Referrer (bool bFieldsInit);
// Деструктор
  ~OD_Referrer ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_CRC;
   string     d_Referrer;
   int        d_Count;
   int        d_LastAccessTime;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "DailyReferrerStats"
// 
#ifdef  USES_OC_ALL
#define USES_OC_DailyReferrerStats
#endif
#ifdef USES_OC_DailyReferrerStats
class OD_DailyReferrerStats: public OD_BASE
{
public:
// Конструктор
   OD_DailyReferrerStats (bool bFieldsInit);
// Деструктор
  ~OD_DailyReferrerStats ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_SiteID;
   identifier_arr d_Referrer;
   int_arr        d_Count;
   int        d_TimeStamp;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "SearchWordsInfo"
// 
#ifdef  USES_OC_ALL
#define USES_OC_SearchWordsInfo
#endif
#ifdef USES_OC_SearchWordsInfo
class OD_SearchWordsInfo: public OD_BASE
{
public:
// Конструктор
   OD_SearchWordsInfo (bool bFieldsInit);
// Деструктор
  ~OD_SearchWordsInfo ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_SiteID;
   string_arr     d_Words;
   int_arr        d_Count;
   int_arr        d_LastAccessTime;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "SuspiciousInfo"
// 
#ifdef  USES_OC_ALL
#define USES_OC_SuspiciousInfo
#endif
#ifdef USES_OC_SuspiciousInfo
class OD_SuspiciousInfo: public OD_BASE
{
public:
// Конструктор
   OD_SuspiciousInfo (bool bFieldsInit);
// Деструктор
  ~OD_SuspiciousInfo ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_Site;
   int        d_Pointer;
   identifier_arr d_Viewer;
   string_arr     d_Referrer;
   int_arr        d_Time;
   int_arr        d_EventType;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "RatingPlaceInfo"
// 
#ifdef  USES_OC_ALL
#define USES_OC_RatingPlaceInfo
#endif
#ifdef USES_OC_RatingPlaceInfo
class OD_RatingPlaceInfo: public OD_BASE
{
public:
// Конструктор
   OD_RatingPlaceInfo (bool bFieldsInit);
// Деструктор
  ~OD_RatingPlaceInfo ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_Site;
   int_arr        d_LastHourPosition;
   int        d_LHP_Pointer;
   float_arr      d_LastDailyPosition;
   int        d_LDP_Pointer;
   int        d_LDP_UpdateTime;
   float      d_DailyPositionDiff;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "IPRecord"
// 
#ifdef  USES_OC_ALL
#define USES_OC_IPRecord
#endif
#ifdef USES_OC_IPRecord
class OD_IPRecord: public OD_BASE
{
public:
// Конструктор
   OD_IPRecord (bool bFieldsInit);
// Деструктор
  ~OD_IPRecord ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   int        d_Count;
   string     d_Mask;
   string     d_First;
   string     d_Last;
   bool       d_Checked;
   identifier_arr d_ConceptID;
   int_arr        d_ConceptNo;
   int_arr        d_CRA_Audience;
   int_arr        d_CRA_Inquiry;
   int        d_CacheTime;
   identifier d_Hits;
   identifier d_Hosts;
   identifier d_Visitors;
   identifier d_Anonymous;
   identifier d_Suspicious;
   int        d_Total_Hits;
   int        d_Total_Hosts;
   int        d_Total_Visitors;
   int        d_Total_Anonymous;
   int        d_Total_Suspicious;
   int        d_LM_Hits;
   int        d_LM_Hosts;
   int        d_LM_Visitors;
   int        d_LM_Anonymous;
   int        d_LM_Suspicious;
   int        d_LW_Hits;
   int        d_LW_Hosts;
   int        d_LW_Visitors;
   int        d_LW_Anonymous;
   int        d_LW_Suspicious;
   int        d_LD_Hits;
   int        d_LD_Hosts;
   int        d_LD_Visitors;
   int        d_LD_Anonymous;
   int        d_LD_Suspicious;
   int        d_LH_Hits;
   int        d_LH_Hosts;
   int        d_LH_Visitors;
   int        d_LH_Anonymous;
   int        d_LH_Suspicious;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "ViewerReference"
// 
#ifdef  USES_OC_ALL
#define USES_OC_ViewerReference
#endif
#ifdef USES_OC_ViewerReference
class OD_ViewerReference: public OD_BASE
{
public:
// Конструктор
   OD_ViewerReference (bool bFieldsInit);
// Деструктор
  ~OD_ViewerReference ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   identifier d_ViewerID;
   string     d_IPAddress;
   identifier d_IPAddressHash;
   int        d_CacheTime;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
};
#endif
//------------------------------------------------------------------------------[]






//------------------------------------------------------------------------------[]
// 
// Объект-данные для класса "AbstractObject"
// 
#ifdef  USES_OC_ALL
#define USES_OC_AbstractObject
#endif
#ifdef USES_OC_AbstractObject
class OD_AbstractObject: public OD_BASE
{
public:
// Конструктор
   OD_AbstractObject (bool bFieldsInit);
// Деструктор
  ~OD_AbstractObject ();
// Создание внешнего набора ключей
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// Поля-данные
   string     d_Type;
   string     d_Name;
   string     d_Header1;
   string     d_Header2;
   string     d_Header3;
   string     d_Body;

// Загрузка объекта с диска
   size_t LoadFromFile (identifier objID);


// Подсчёт размера объекта для сохраения на диск
   size_t CalculateSize ();

// Запись данных на диск
   bool WriteToFile (identifier objID);

// Отладочная печать
   bool DebugPrint (string& dbg, identifier objID);
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
