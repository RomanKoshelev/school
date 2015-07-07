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
// ���������� �������� ���� ������ ������ "Viewer"
// 
class OC_Viewer: public OC_Object <OC_Viewer>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Viewer  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Viewer  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Viewer  (const OC_Viewer& from);
// ���������� ����������� �������
   public: ~OC_Viewer ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Viewer& operator= (const OC_Viewer& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Viewer& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Viewer& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Viewer& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Viewer& operator << (OC_Viewer& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Viewer& operator >> (OC_Viewer& from);

// ����:   identifier Viewer::Reference
   public: CSmartField      <OD_Viewer, identifier >    m_Reference;
// ����:   string Viewer::Name
   public: CSmartField      <OD_Viewer, string     >    m_Name;
// ����:   string Viewer::Email
   public: CSmartField      <OD_Viewer, string     >    m_Email;
// ����:   string Viewer::UserAgent
   public: CSmartField      <OD_Viewer, string     >    m_UserAgent;
// ����:   bool Viewer::Anonymous
   public: CSmartField      <OD_Viewer, bool       >    m_Anonymous;
// ����:   int Viewer::TotalShows
   public: CSmartField      <OD_Viewer, int        >    m_TotalShows;
// ����:   int Viewer::TotalClicks
   public: CSmartField      <OD_Viewer, int        >    m_TotalClicks;
// ����:   string Viewer::IPAddress
   public: CSmartField      <OD_Viewer, string     >    m_IPAddress;
// ����:   string Viewer::Referrer
   public: CSmartField      <OD_Viewer, string     >    m_Referrer;
// ����:   identifier Viewer::IPAddressHash
   public: CSmartField      <OD_Viewer, identifier >    m_IPAddressHash;
// ����:   int Viewer::CRN_Site_Update
   public: CSmartField      <OD_Viewer, int        >    m_CRN_Site_Update;
// ����:   identifier Viewer::Group
   public: CSmartField      <OD_Viewer, identifier >    m_Group;
// ����:   int Viewer::TZOffset
   public: CSmartField      <OD_Viewer, int        >    m_TZOffset;
// ����:   int Viewer::CreationTime
   public: CSmartField      <OD_Viewer, int        >    m_CreationTime;
// ����:   int Viewer::LastVisitTime
   public: CSmartField      <OD_Viewer, int        >    m_LastVisitTime;
// ����:   int Viewer::TotalHosts
   public: CSmartField      <OD_Viewer, int        >    m_TotalHosts;
// ����:   identifier Viewer::Site_SessionLastSiteID
   public: CSmartField      <OD_Viewer, identifier >    m_Site_SessionLastSiteID;
// ����:   int Viewer::BannerClickTime
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickTime;
// ����:   identifier Viewer::BannerClickID
   public: CSmartField      <OD_Viewer, identifier >    m_BannerClickID;
// ����:   identifier Viewer::BannerClickSiteID
   public: CSmartField      <OD_Viewer, identifier >    m_BannerClickSiteID;
// ����:   int Viewer::BannerClickHitCount
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickHitCount;
// ����:   int Viewer::BannerClickSessionTime
   public: CSmartField      <OD_Viewer, int        >    m_BannerClickSessionTime;
// ����:   float Viewer::ReloadNum
   public: CSmartField      <OD_Viewer, float      >    m_ReloadNum;
// ����:   float Viewer::AveReloadTime
   public: CSmartField      <OD_Viewer, float      >    m_AveReloadTime;
// ����:   identifier Viewer::TagID
   public: CSmartField      <OD_Viewer, identifier >    m_TagID;
// ����:   int Viewer::TagInt
   public: CSmartField      <OD_Viewer, int        >    m_TagInt;
// ����:   bool Viewer::TagBool
   public: CSmartField      <OD_Viewer, bool       >    m_TagBool;
// ����:   int Viewer::CacheTime
   public: CSmartField      <OD_Viewer, int        >    m_CacheTime;
// ����:   int Viewer::CRA_Site []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Site;
// ����:   int Viewer::CRN_Site []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Site;
// ����:   int Viewer::CRA_Click []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Click;
// ����:   int Viewer::CRN_Click []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Click;
// ����:   identifier Viewer::Site []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_Site;
// ����:   int Viewer::Site_LastHit []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_LastHit;
// ����:   int Viewer::Site_Hits []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_Hits;
// ����:   int Viewer::Site_LastHost []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_LastHost;
// ����:   int Viewer::Site_Hosts []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Site_Hosts;
// ����:   byte Viewer::Site_Votings []
   public: CSmartFieldArray <OD_Viewer, byte       >    m_Site_Votings;
// ����:   byte Viewer::Site_VoteDayNo []
   public: CSmartFieldArray <OD_Viewer, byte       >    m_Site_VoteDayNo;
// ����:   int Viewer::CRA_Inquiry []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRA_Inquiry;
// ����:   int Viewer::CRN_Inquiry []
   public: CSmartFieldArray <OD_Viewer, int        >    m_CRN_Inquiry;
// ����:   identifier Viewer::Banner []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_Banner;
// ����:   int Viewer::Banner_LastViewed []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Banner_LastViewed;
// ����:   int Viewer::Banner_ShowClick []
   public: CSmartFieldArray <OD_Viewer, int        >    m_Banner_ShowClick;
// ����:   identifier Viewer::ReservedID []
   public: CSmartFieldArray <OD_Viewer, identifier >    m_ReservedID;
// ����:   int Viewer::ReservedInt []
   public: CSmartFieldArray <OD_Viewer, int        >    m_ReservedInt;
// ����:   string Viewer::ReservedString []
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
// ���������� �������� ���� ������ ������ "ViewerGroup"
// 
class OC_ViewerGroup: public OC_Object <OC_ViewerGroup>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_ViewerGroup  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_ViewerGroup  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_ViewerGroup  (const OC_ViewerGroup& from);
// ���������� ����������� �������
   public: ~OC_ViewerGroup ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ViewerGroup& operator= (const OC_ViewerGroup& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ViewerGroup& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_ViewerGroup& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_ViewerGroup& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_ViewerGroup& operator << (OC_ViewerGroup& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_ViewerGroup& operator >> (OC_ViewerGroup& from);

// ����:   identifier ViewerGroup::TagID
   public: CSmartField      <OD_ViewerGroup, identifier >    m_TagID;
// ����:   int ViewerGroup::TagInt
   public: CSmartField      <OD_ViewerGroup, int        >    m_TagInt;
// ����:   bool ViewerGroup::TagBool
   public: CSmartField      <OD_ViewerGroup, bool       >    m_TagBool;
// ����:   int ViewerGroup::CacheTime
   public: CSmartField      <OD_ViewerGroup, int        >    m_CacheTime;
// ����:   int ViewerGroup::ConceptStats []
   public: CSmartFieldArray <OD_ViewerGroup, int        >    m_ConceptStats;
// ����:   identifier ViewerGroup::Viewer []
   public: CSmartFieldArray <OD_ViewerGroup, identifier >    m_Viewer;
// ����:   identifier ViewerGroup::ReservedID []
   public: CSmartFieldArray <OD_ViewerGroup, identifier >    m_ReservedID;
// ����:   int ViewerGroup::ReservedInt []
   public: CSmartFieldArray <OD_ViewerGroup, int        >    m_ReservedInt;
// ����:   string ViewerGroup::ReservedString []
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
// ���������� �������� ���� ������ ������ "User"
// 
class OC_User: public OC_Object <OC_User>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_User  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_User  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_User  (const OC_User& from);
// ���������� ����������� �������
   public: ~OC_User ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_User& operator= (const OC_User& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_User& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_User& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_User& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_User& operator << (OC_User& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_User& operator >> (OC_User& from);

// ����:   string User::Login
   public: CSmartField      <OD_User, string     >    m_Login;
// ����:   string User::Password
   public: CSmartField      <OD_User, string     >    m_Password;
// ����:   bool User::ForgetPassword
   public: CSmartField      <OD_User, bool       >    m_ForgetPassword;
// ����:   string User::FullName
   public: CSmartField      <OD_User, string     >    m_FullName;
// ����:   identifier User::InterfaceLanguage
   public: CSmartField      <OD_User, identifier >    m_InterfaceLanguage;
// ����:   bool User::InterfaceType
   public: CSmartField      <OD_User, bool       >    m_InterfaceType;
// ����:   int User::CreationTime
   public: CSmartField      <OD_User, int        >    m_CreationTime;
// ����:   byte User::VBN
   public: CSmartField      <OD_User, byte       >    m_VBN;
// ����:   string User::Email
   public: CSmartField      <OD_User, string     >    m_Email;
// ����:   string User::Phone
   public: CSmartField      <OD_User, string     >    m_Phone;
// ����:   string User::Fax
   public: CSmartField      <OD_User, string     >    m_Fax;
// ����:   string User::Address
   public: CSmartField      <OD_User, string     >    m_Address;
// ����:   string User::URL
   public: CSmartField      <OD_User, string     >    m_URL;
// ����:   string User::Comment
   public: CSmartField      <OD_User, string     >    m_Comment;
// ����:   int User::TZOffset
   public: CSmartField      <OD_User, int        >    m_TZOffset;
// ����:   int User::NotifyFreq
   public: CSmartField      <OD_User, int        >    m_NotifyFreq;
// ����:   bool User::NotifyHTML
   public: CSmartField      <OD_User, bool       >    m_NotifyHTML;
// ����:   int User::NotifyDepth
   public: CSmartField      <OD_User, int        >    m_NotifyDepth;
// ����:   float User::ShowsLeft
   public: CSmartField      <OD_User, float      >    m_ShowsLeft;
// ����:   float User::ClicksLeft
   public: CSmartField      <OD_User, float      >    m_ClicksLeft;
// ����:   identifier User::TradeStats
   public: CSmartField      <OD_User, identifier >    m_TradeStats;
// ����:   bool User::Allowed
   public: CSmartField      <OD_User, bool       >    m_Allowed;
// ����:   byte User::ObjectState
   public: CSmartField      <OD_User, byte       >    m_ObjectState;
// ����:   identifier User::TagID
   public: CSmartField      <OD_User, identifier >    m_TagID;
// ����:   int User::TagInt
   public: CSmartField      <OD_User, int        >    m_TagInt;
// ����:   bool User::TagBool
   public: CSmartField      <OD_User, bool       >    m_TagBool;
// ����:   int User::CacheTime
   public: CSmartField      <OD_User, int        >    m_CacheTime;
// ����:   byte User::ba_Concept []
   public: CSmartFieldArray <OD_User, byte       >    m_ba_Concept;
// ����:   byte User::eba_Concept []
   public: CSmartFieldArray <OD_User, byte       >    m_eba_Concept;
// ����:   identifier User::Site []
   public: CSmartFieldArray <OD_User, identifier >    m_Site;
// ����:   identifier User::SiteProfile []
   public: CSmartFieldArray <OD_User, identifier >    m_SiteProfile;
// ����:   identifier User::Banner []
   public: CSmartFieldArray <OD_User, identifier >    m_Banner;
// ����:   identifier User::BannerProfile []
   public: CSmartFieldArray <OD_User, identifier >    m_BannerProfile;
// ����:   byte User::ba_ModeratorComment []
   public: CSmartFieldArray <OD_User, byte       >    m_ba_ModeratorComment;
// ����:   identifier User::ReservedID []
   public: CSmartFieldArray <OD_User, identifier >    m_ReservedID;
// ����:   int User::ReservedInt []
   public: CSmartFieldArray <OD_User, int        >    m_ReservedInt;
// ����:   string User::ReservedString []
   public: CSmartFieldArray <OD_User, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// ���������� ������� ������ �� ������ ����� [VBN, Login]
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
// ���������� �������� ���� ������ ������ "TradeStats"
// 
class OC_TradeStats: public OC_Object <OC_TradeStats>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_TradeStats  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_TradeStats  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_TradeStats  (const OC_TradeStats& from);
// ���������� ����������� �������
   public: ~OC_TradeStats ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_TradeStats& operator= (const OC_TradeStats& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_TradeStats& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_TradeStats& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_TradeStats& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_TradeStats& operator << (OC_TradeStats& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_TradeStats& operator >> (OC_TradeStats& from);

// ����:   identifier TradeStats::TagID
   public: CSmartField      <OD_TradeStats, identifier >    m_TagID;
// ����:   int TradeStats::TagInt
   public: CSmartField      <OD_TradeStats, int        >    m_TagInt;
// ����:   bool TradeStats::TagBool
   public: CSmartField      <OD_TradeStats, bool       >    m_TagBool;
// ����:   int TradeStats::CacheTime
   public: CSmartField      <OD_TradeStats, int        >    m_CacheTime;
// ����:   int TradeStats::SoldShowDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldShowDates;
// ����:   int TradeStats::SoldShowAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldShowAmounts;
// ����:   string TradeStats::SoldShowBuyer []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_SoldShowBuyer;
// ����:   int TradeStats::BoughtShowDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtShowDates;
// ����:   int TradeStats::BoughtShowAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtShowAmounts;
// ����:   string TradeStats::BoughtShowSeller []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_BoughtShowSeller;
// ����:   int TradeStats::SoldClickDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldClickDates;
// ����:   int TradeStats::SoldClickAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_SoldClickAmounts;
// ����:   string TradeStats::SoldClickBuyer []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_SoldClickBuyer;
// ����:   int TradeStats::BoughtClickDates []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtClickDates;
// ����:   int TradeStats::BoughtClickAmounts []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_BoughtClickAmounts;
// ����:   string TradeStats::BoughtClickSeller []
   public: CSmartFieldArray <OD_TradeStats, string     >    m_BoughtClickSeller;
// ����:   identifier TradeStats::ReservedID []
   public: CSmartFieldArray <OD_TradeStats, identifier >    m_ReservedID;
// ����:   int TradeStats::ReservedInt []
   public: CSmartFieldArray <OD_TradeStats, int        >    m_ReservedInt;
// ����:   string TradeStats::ReservedString []
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
// ���������� �������� ���� ������ ������ "Banner"
// 
class OC_Banner: public OC_Object <OC_Banner>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Banner  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Banner  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Banner  (const OC_Banner& from);
// ���������� ����������� �������
   public: ~OC_Banner ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Banner& operator= (const OC_Banner& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Banner& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Banner& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Banner& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Banner& operator << (OC_Banner& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Banner& operator >> (OC_Banner& from);

// ����:   identifier Banner::OwnerID
   public: CSmartField      <OD_Banner, identifier >    m_OwnerID;
// ����:   string Banner::FileName
   public: CSmartField      <OD_Banner, string     >    m_FileName;
// ����:   int Banner::FileSize
   public: CSmartField      <OD_Banner, int        >    m_FileSize;
// ����:   int Banner::UploadNo
   public: CSmartField      <OD_Banner, int        >    m_UploadNo;
// ����:   int Banner::CreationTime
   public: CSmartField      <OD_Banner, int        >    m_CreationTime;
// ����:   byte Banner::VBN
   public: CSmartField      <OD_Banner, byte       >    m_VBN;
// ����:   string Banner::Description
   public: CSmartField      <OD_Banner, string     >    m_Description;
// ����:   bool Banner::State
   public: CSmartField      <OD_Banner, bool       >    m_State;
// ����:   identifier Banner::Profile
   public: CSmartField      <OD_Banner, identifier >    m_Profile;
// ����:   int Banner::TotalShows
   public: CSmartField      <OD_Banner, int        >    m_TotalShows;
// ����:   int Banner::TotalClicks
   public: CSmartField      <OD_Banner, int        >    m_TotalClicks;
// ����:   bool Banner::Allowed
   public: CSmartField      <OD_Banner, bool       >    m_Allowed;
// ����:   byte Banner::ObjectState
   public: CSmartField      <OD_Banner, byte       >    m_ObjectState;
// ����:   identifier Banner::TagID
   public: CSmartField      <OD_Banner, identifier >    m_TagID;
// ����:   int Banner::TagInt
   public: CSmartField      <OD_Banner, int        >    m_TagInt;
// ����:   bool Banner::TagBool
   public: CSmartField      <OD_Banner, bool       >    m_TagBool;
// ����:   int Banner::CacheTime
   public: CSmartField      <OD_Banner, int        >    m_CacheTime;
// ����:   identifier Banner::SiteAnnounce []
   public: CSmartFieldArray <OD_Banner, identifier >    m_SiteAnnounce;
// ����:   byte Banner::ba_Concept []
   public: CSmartFieldArray <OD_Banner, byte       >    m_ba_Concept;
// ����:   byte Banner::eba_Concept []
   public: CSmartFieldArray <OD_Banner, byte       >    m_eba_Concept;
// ����:   byte Banner::ba_ModeratorComment []
   public: CSmartFieldArray <OD_Banner, byte       >    m_ba_ModeratorComment;
// ����:   identifier Banner::ReservedID []
   public: CSmartFieldArray <OD_Banner, identifier >    m_ReservedID;
// ����:   int Banner::ReservedInt []
   public: CSmartFieldArray <OD_Banner, int        >    m_ReservedInt;
// ����:   string Banner::ReservedString []
   public: CSmartFieldArray <OD_Banner, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [VBN, Allowed, ObjectState]
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
// ���������� �������� ���� ������ ������ "BannerProfile"
// 
class OC_BannerProfile: public OC_Object <OC_BannerProfile>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_BannerProfile  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_BannerProfile  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_BannerProfile  (const OC_BannerProfile& from);
// ���������� ����������� �������
   public: ~OC_BannerProfile ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_BannerProfile& operator= (const OC_BannerProfile& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_BannerProfile& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_BannerProfile& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_BannerProfile& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_BannerProfile& operator << (OC_BannerProfile& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_BannerProfile& operator >> (OC_BannerProfile& from);

// ����:   string BannerProfile::Name
   public: CSmartField      <OD_BannerProfile, string     >    m_Name;
// ����:   byte BannerProfile::VBN
   public: CSmartField      <OD_BannerProfile, byte       >    m_VBN;
// ����:   int BannerProfile::LastModified
   public: CSmartField      <OD_BannerProfile, int        >    m_LastModified;
// ����:   identifier BannerProfile::OwnerID
   public: CSmartField      <OD_BannerProfile, identifier >    m_OwnerID;
// ����:   identifier BannerProfile::HREF
   public: CSmartField      <OD_BannerProfile, identifier >    m_HREF;
// ����:   bool BannerProfile::Commercial
   public: CSmartField      <OD_BannerProfile, bool       >    m_Commercial;
// ����:   int BannerProfile::BannerType
   public: CSmartField      <OD_BannerProfile, int        >    m_BannerType;
// ����:   bool BannerProfile::State
   public: CSmartField      <OD_BannerProfile, bool       >    m_State;
// ����:   string BannerProfile::AltText
   public: CSmartField      <OD_BannerProfile, string     >    m_AltText;
// ����:   bool BannerProfile::UseLocalTime
   public: CSmartField      <OD_BannerProfile, bool       >    m_UseLocalTime;
// ����:   int BannerProfile::ScheduleTZOffset
   public: CSmartField      <OD_BannerProfile, int        >    m_ScheduleTZOffset;
// ����:   bool BannerProfile::ShowIfLocalUnknown
   public: CSmartField      <OD_BannerProfile, bool       >    m_ShowIfLocalUnknown;
// ����:   int BannerProfile::AutoOn
   public: CSmartField      <OD_BannerProfile, int        >    m_AutoOn;
// ����:   int BannerProfile::AutoOff
   public: CSmartField      <OD_BannerProfile, int        >    m_AutoOff;
// ����:   int BannerProfile::RepeatCount
   public: CSmartField      <OD_BannerProfile, int        >    m_RepeatCount;
// ����:   int BannerProfile::RepeatTime
   public: CSmartField      <OD_BannerProfile, int        >    m_RepeatTime;
// ����:   bool BannerProfile::CountTypeByShows
   public: CSmartField      <OD_BannerProfile, bool       >    m_CountTypeByShows;
// ����:   int BannerProfile::MaxDailyClicks
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyClicks;
// ����:   int BannerProfile::MaxDailyShows
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyShows;
// ����:   int BannerProfile::MaxDailyShowsChangeTime
   public: CSmartField      <OD_BannerProfile, int        >    m_MaxDailyShowsChangeTime;
// ����:   int BannerProfile::TotalShows
   public: CSmartField      <OD_BannerProfile, int        >    m_TotalShows;
// ����:   int BannerProfile::TotalClicks
   public: CSmartField      <OD_BannerProfile, int        >    m_TotalClicks;
// ����:   int BannerProfile::SessionEvents
   public: CSmartField      <OD_BannerProfile, int        >    m_SessionEvents;
// ����:   float BannerProfile::Priority
   public: CSmartField      <OD_BannerProfile, float      >    m_Priority;
// ����:   bool BannerProfile::Allowed
   public: CSmartField      <OD_BannerProfile, bool       >    m_Allowed;
// ����:   byte BannerProfile::ObjectState
   public: CSmartField      <OD_BannerProfile, byte       >    m_ObjectState;
// ����:   identifier BannerProfile::TagID
   public: CSmartField      <OD_BannerProfile, identifier >    m_TagID;
// ����:   int BannerProfile::TagInt
   public: CSmartField      <OD_BannerProfile, int        >    m_TagInt;
// ����:   bool BannerProfile::TagBool
   public: CSmartField      <OD_BannerProfile, bool       >    m_TagBool;
// ����:   int BannerProfile::CacheTime
   public: CSmartField      <OD_BannerProfile, int        >    m_CacheTime;
// ����:   identifier BannerProfile::SiteAnnounce []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteAnnounce;
// ����:   identifier BannerProfile::Banner []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_Banner;
// ����:   byte BannerProfile::ba_Concept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_Concept;
// ����:   byte BannerProfile::eba_Concept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_Concept;
// ����:   byte BannerProfile::ba_SiteConceptInclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_SiteConceptInclude;
// ����:   byte BannerProfile::ba_SiteConceptExclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_SiteConceptExclude;
// ����:   byte BannerProfile::eba_SiteConcept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_SiteConcept;
// ����:   identifier BannerProfile::SiteInclude []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteInclude;
// ����:   identifier BannerProfile::SiteExclude []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteExclude;
// ����:   string BannerProfile::ViewerIPEnable []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ViewerIPEnable;
// ����:   string BannerProfile::ViewerIPDisable []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ViewerIPDisable;
// ����:   byte BannerProfile::ba_ViewerConceptInclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ViewerConceptInclude;
// ����:   byte BannerProfile::ba_ViewerConceptExclude []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ViewerConceptExclude;
// ����:   byte BannerProfile::eba_ViewerConcept []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_eba_ViewerConcept;
// ����:   byte BannerProfile::ba_Schedule []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_Schedule;
// ����:   identifier BannerProfile::SiteTarget_SiteID []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_SiteTarget_SiteID;
// ����:   int BannerProfile::SiteTarget_ShowRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ShowRate;
// ����:   int BannerProfile::SiteTarget_ClickRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ClickRate;
// ����:   int BannerProfile::SiteTarget_ViewRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SiteTarget_ViewRate;
// ����:   int BannerProfile::ViewerConceptRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ViewerConceptRate;
// ����:   int BannerProfile::ShowNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ShowNumRate;
// ����:   int BannerProfile::ClickNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ClickNumRate;
// ����:   int BannerProfile::HitNumRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_HitNumRate;
// ����:   int BannerProfile::SessionTimeRate []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_SessionTimeRate;
// ����:   byte BannerProfile::ba_ModeratorComment []
   public: CSmartFieldArray <OD_BannerProfile, byte       >    m_ba_ModeratorComment;
// ����:   identifier BannerProfile::ReservedID []
   public: CSmartFieldArray <OD_BannerProfile, identifier >    m_ReservedID;
// ����:   int BannerProfile::ReservedInt []
   public: CSmartFieldArray <OD_BannerProfile, int        >    m_ReservedInt;
// ����:   string BannerProfile::ReservedString []
   public: CSmartFieldArray <OD_BannerProfile, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// ���������� ������� ������ �� ������ ����� [VBN, State, Allowed, BannerType, Priority]
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
// ���������� �������� ���� ������ ������ "Page"
// 
class OC_Page: public OC_Object <OC_Page>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Page  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Page  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Page  (const OC_Page& from);
// ���������� ����������� �������
   public: ~OC_Page ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Page& operator= (const OC_Page& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Page& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Page& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Page& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Page& operator << (OC_Page& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Page& operator >> (OC_Page& from);

// ����:   identifier Page::Site
   public: CSmartField      <OD_Page, identifier >    m_Site;
// ����:   int Page::No
   public: CSmartField      <OD_Page, int        >    m_No;
// ����:   string Page::URL
   public: CSmartField      <OD_Page, string     >    m_URL;
// ����:   int Page::CounterType
   public: CSmartField      <OD_Page, int        >    m_CounterType;
// ����:   bool Page::ConceptSet
   public: CSmartField      <OD_Page, bool       >    m_ConceptSet;
// ����:   int Page::CRN_Visitor_Update
   public: CSmartField      <OD_Page, int        >    m_CRN_Visitor_Update;
// ����:   int Page::CRN_VisitorIncr_Update
   public: CSmartField      <OD_Page, int        >    m_CRN_VisitorIncr_Update;
// ����:   identifier Page::TagID
   public: CSmartField      <OD_Page, identifier >    m_TagID;
// ����:   int Page::TagInt
   public: CSmartField      <OD_Page, int        >    m_TagInt;
// ����:   bool Page::TagBool
   public: CSmartField      <OD_Page, bool       >    m_TagBool;
// ����:   int Page::CacheTime
   public: CSmartField      <OD_Page, int        >    m_CacheTime;
// ����:   byte Page::ba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_ba_Concept;
// ����:   byte Page::eba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_eba_Concept;
// ����:   byte Page::pba_Concept []
   public: CSmartFieldArray <OD_Page, byte       >    m_pba_Concept;
// ����:   identifier Page::TimeStats []
   public: CSmartFieldArray <OD_Page, identifier >    m_TimeStats;
// ����:   byte Page::TimeStatsType []
   public: CSmartFieldArray <OD_Page, byte       >    m_TimeStatsType;
// ����:   int Page::CRA_Visitor []
   public: CSmartFieldArray <OD_Page, int        >    m_CRA_Visitor;
// ����:   int Page::CRN_Visitor []
   public: CSmartFieldArray <OD_Page, int        >    m_CRN_Visitor;
// ����:   int Page::CRN_VisitorIncr []
   public: CSmartFieldArray <OD_Page, int        >    m_CRN_VisitorIncr;
// ����:   identifier Page::Referrer []
   public: CSmartFieldArray <OD_Page, identifier >    m_Referrer;
// ����:   int Page::ReferrerCount []
   public: CSmartFieldArray <OD_Page, int        >    m_ReferrerCount;
// ����:   identifier Page::ReservedID []
   public: CSmartFieldArray <OD_Page, identifier >    m_ReservedID;
// ����:   int Page::ReservedInt []
   public: CSmartFieldArray <OD_Page, int        >    m_ReservedInt;
// ����:   string Page::ReservedString []
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
// ���������� �������� ���� ������ ������ "Site"
// 
class OC_Site: public OC_Object <OC_Site>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Site  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Site  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Site  (const OC_Site& from);
// ���������� ����������� �������
   public: ~OC_Site ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Site& operator= (const OC_Site& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Site& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Site& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Site& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Site& operator << (OC_Site& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Site& operator >> (OC_Site& from);

// ����:   identifier Site::OwnerID
   public: CSmartField      <OD_Site, identifier >    m_OwnerID;
// ����:   byte Site::VBN
   public: CSmartField      <OD_Site, byte       >    m_VBN;
// ����:   int Site::CreationTime
   public: CSmartField      <OD_Site, int        >    m_CreationTime;
// ����:   string Site::Alias
   public: CSmartField      <OD_Site, string     >    m_Alias;
// ����:   string Site::Name
   public: CSmartField      <OD_Site, string     >    m_Name;
// ����:   string Site::Description
   public: CSmartField      <OD_Site, string     >    m_Description;
// ����:   string Site::URL
   public: CSmartField      <OD_Site, string     >    m_URL;
// ����:   int Site::CounterType
   public: CSmartField      <OD_Site, int        >    m_CounterType;
// ����:   bool Site::RateMySite
   public: CSmartField      <OD_Site, bool       >    m_RateMySite;
// ����:   string Site::RateStatsViewPassword
   public: CSmartField      <OD_Site, string     >    m_RateStatsViewPassword;
// ����:   bool Site::ShowAudience
   public: CSmartField      <OD_Site, bool       >    m_ShowAudience;
// ����:   int Site::ShowAudienceOffTime
   public: CSmartField      <OD_Site, int        >    m_ShowAudienceOffTime;
// ����:   identifier Site::Profile
   public: CSmartField      <OD_Site, identifier >    m_Profile;
// ����:   identifier Site::SuspiciousInfo
   public: CSmartField      <OD_Site, identifier >    m_SuspiciousInfo;
// ����:   int Site::CRN_Visitor_Update
   public: CSmartField      <OD_Site, int        >    m_CRN_Visitor_Update;
// ����:   int Site::CRN_VisitorIncr_Update
   public: CSmartField      <OD_Site, int        >    m_CRN_VisitorIncr_Update;
// ����:   int Site::RecentPointer
   public: CSmartField      <OD_Site, int        >    m_RecentPointer;
// ����:   int Site::Referrer_LastReset
   public: CSmartField      <OD_Site, int        >    m_Referrer_LastReset;
// ����:   identifier Site::SearchWordsInfo
   public: CSmartField      <OD_Site, identifier >    m_SearchWordsInfo;
// ����:   int Site::InquiredVisitorNum
   public: CSmartField      <OD_Site, int        >    m_InquiredVisitorNum;
// ����:   int Site::SessionResetTime
   public: CSmartField      <OD_Site, int        >    m_SessionResetTime;
// ����:   int Site::LastVisitTime
   public: CSmartField      <OD_Site, int        >    m_LastVisitTime;
// ����:   int Site::LastUpdateTime
   public: CSmartField      <OD_Site, int        >    m_LastUpdateTime;
// ����:   identifier Site::Loads
   public: CSmartField      <OD_Site, identifier >    m_Loads;
// ����:   identifier Site::Visitors
   public: CSmartField      <OD_Site, identifier >    m_Visitors;
// ����:   identifier Site::Hosts
   public: CSmartField      <OD_Site, identifier >    m_Hosts;
// ����:   identifier Site::Shows
   public: CSmartField      <OD_Site, identifier >    m_Shows;
// ����:   identifier Site::Clicks
   public: CSmartField      <OD_Site, identifier >    m_Clicks;
// ����:   identifier Site::Clicks_Local
   public: CSmartField      <OD_Site, identifier >    m_Clicks_Local;
// ����:   identifier Site::Hits
   public: CSmartField      <OD_Site, identifier >    m_Hits;
// ����:   identifier Site::Hits_Local
   public: CSmartField      <OD_Site, identifier >    m_Hits_Local;
// ����:   identifier Site::AnonymousHits
   public: CSmartField      <OD_Site, identifier >    m_AnonymousHits;
// ����:   identifier Site::SuspiciousHits
   public: CSmartField      <OD_Site, identifier >    m_SuspiciousHits;
// ����:   identifier Site::SessionTime
   public: CSmartField      <OD_Site, identifier >    m_SessionTime;
// ����:   identifier Site::SessionTime_Local
   public: CSmartField      <OD_Site, identifier >    m_SessionTime_Local;
// ����:   identifier Site::SessionNum
   public: CSmartField      <OD_Site, identifier >    m_SessionNum;
// ����:   int Site::Total_Loads
   public: CSmartField      <OD_Site, int        >    m_Total_Loads;
// ����:   int Site::Total_Hosts
   public: CSmartField      <OD_Site, int        >    m_Total_Hosts;
// ����:   int Site::Total_Hits
   public: CSmartField      <OD_Site, int        >    m_Total_Hits;
// ����:   int Site::Total_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousHits;
// ����:   int Site::Total_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousHits_Prc;
// ����:   int Site::Total_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_SuspiciousHits_Prc;
// ����:   int Site::Total_Visitors
   public: CSmartField      <OD_Site, int        >    m_Total_Visitors;
// ����:   int Site::Total_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorReturns;
// ����:   int Site::Total_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorReturns_Prc;
// ����:   int Site::Total_SessionNum
   public: CSmartField      <OD_Site, int        >    m_Total_SessionNum;
// ����:   int Site::Total_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_Total_AveSessionTime;
// ����:   int Site::Total_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_Total_AveReloadTime;
// ����:   int Site::Total_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_Total_AveReloadNum;
// ����:   int Site::Total_Shows
   public: CSmartField      <OD_Site, int        >    m_Total_Shows;
// ����:   int Site::Total_Clicks
   public: CSmartField      <OD_Site, int        >    m_Total_Clicks;
// ����:   int Site::Total_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_CTR_Prc;
// ����:   int Site::Total_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_CPH_Prc;
// ����:   int Site::Total_AnonymousVisitors
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousVisitors;
// ����:   int Site::Total_AnonymousVisitors_Prc
   public: CSmartField      <OD_Site, int        >    m_Total_AnonymousVisitors_Prc;
// ����:   int Site::Total_VisitorExperience
   public: CSmartField      <OD_Site, int        >    m_Total_VisitorExperience;
// ����:   int Site::Ave_VisitorExperience
   public: CSmartField      <OD_Site, int        >    m_Ave_VisitorExperience;
// ����:   int Site::OnlineVisitors
   public: CSmartField      <OD_Site, int        >    m_OnlineVisitors;
// ����:   int Site::Total_MouseOver
   public: CSmartField      <OD_Site, int        >    m_Total_MouseOver;
// ����:   int Site::Total_Votes
   public: CSmartField      <OD_Site, int        >    m_Total_Votes;
// ����:   int Site::Total_Votes_Sum
   public: CSmartField      <OD_Site, int        >    m_Total_Votes_Sum;
// ����:   int Site::Total_Votes_Ave
   public: CSmartField      <OD_Site, int        >    m_Total_Votes_Ave;
// ����:   int Site::LM_Loads
   public: CSmartField      <OD_Site, int        >    m_LM_Loads;
// ����:   int Site::LM_Hosts
   public: CSmartField      <OD_Site, int        >    m_LM_Hosts;
// ����:   int Site::LM_Hits
   public: CSmartField      <OD_Site, int        >    m_LM_Hits;
// ����:   int Site::LM_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LM_AnonymousHits;
// ����:   int Site::LM_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_AnonymousHits_Prc;
// ����:   int Site::LM_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_SuspiciousHits_Prc;
// ����:   int Site::LM_Visitors
   public: CSmartField      <OD_Site, int        >    m_LM_Visitors;
// ����:   int Site::LM_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LM_VisitorReturns;
// ����:   int Site::LM_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_VisitorReturns_Prc;
// ����:   int Site::LM_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LM_SessionNum;
// ����:   int Site::LM_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LM_AveSessionTime;
// ����:   int Site::LM_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LM_AveReloadTime;
// ����:   int Site::LM_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LM_AveReloadNum;
// ����:   int Site::LM_Shows
   public: CSmartField      <OD_Site, int        >    m_LM_Shows;
// ����:   int Site::LM_Clicks
   public: CSmartField      <OD_Site, int        >    m_LM_Clicks;
// ����:   int Site::LM_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_CTR_Prc;
// ����:   int Site::LM_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LM_CPH_Prc;
// ����:   int Site::LW_Loads
   public: CSmartField      <OD_Site, int        >    m_LW_Loads;
// ����:   int Site::LW_Hosts
   public: CSmartField      <OD_Site, int        >    m_LW_Hosts;
// ����:   int Site::LW_Hits
   public: CSmartField      <OD_Site, int        >    m_LW_Hits;
// ����:   int Site::LW_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LW_AnonymousHits;
// ����:   int Site::LW_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_AnonymousHits_Prc;
// ����:   int Site::LW_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_SuspiciousHits_Prc;
// ����:   int Site::LW_Visitors
   public: CSmartField      <OD_Site, int        >    m_LW_Visitors;
// ����:   int Site::LW_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LW_VisitorReturns;
// ����:   int Site::LW_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_VisitorReturns_Prc;
// ����:   int Site::LW_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LW_SessionNum;
// ����:   int Site::LW_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LW_AveSessionTime;
// ����:   int Site::LW_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LW_AveReloadTime;
// ����:   int Site::LW_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LW_AveReloadNum;
// ����:   int Site::LW_Shows
   public: CSmartField      <OD_Site, int        >    m_LW_Shows;
// ����:   int Site::LW_Clicks
   public: CSmartField      <OD_Site, int        >    m_LW_Clicks;
// ����:   int Site::LW_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_CTR_Prc;
// ����:   int Site::LW_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LW_CPH_Prc;
// ����:   int Site::LD_Loads
   public: CSmartField      <OD_Site, int        >    m_LD_Loads;
// ����:   int Site::LD_Hosts
   public: CSmartField      <OD_Site, int        >    m_LD_Hosts;
// ����:   int Site::LD_Hits
   public: CSmartField      <OD_Site, int        >    m_LD_Hits;
// ����:   int Site::LD_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LD_AnonymousHits;
// ����:   int Site::LD_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_AnonymousHits_Prc;
// ����:   int Site::LD_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_SuspiciousHits_Prc;
// ����:   int Site::LD_Visitors
   public: CSmartField      <OD_Site, int        >    m_LD_Visitors;
// ����:   int Site::LD_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LD_VisitorReturns;
// ����:   int Site::LD_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_VisitorReturns_Prc;
// ����:   int Site::LD_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LD_SessionNum;
// ����:   int Site::LD_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LD_AveSessionTime;
// ����:   int Site::LD_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LD_AveReloadTime;
// ����:   int Site::LD_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LD_AveReloadNum;
// ����:   int Site::LD_Shows
   public: CSmartField      <OD_Site, int        >    m_LD_Shows;
// ����:   int Site::LD_Clicks
   public: CSmartField      <OD_Site, int        >    m_LD_Clicks;
// ����:   int Site::LD_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_CTR_Prc;
// ����:   int Site::LD_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LD_CPH_Prc;
// ����:   int Site::LH_Loads
   public: CSmartField      <OD_Site, int        >    m_LH_Loads;
// ����:   int Site::LH_Hosts
   public: CSmartField      <OD_Site, int        >    m_LH_Hosts;
// ����:   int Site::LH_Hits
   public: CSmartField      <OD_Site, int        >    m_LH_Hits;
// ����:   int Site::LH_AnonymousHits
   public: CSmartField      <OD_Site, int        >    m_LH_AnonymousHits;
// ����:   int Site::LH_AnonymousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_AnonymousHits_Prc;
// ����:   int Site::LH_SuspiciousHits_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_SuspiciousHits_Prc;
// ����:   int Site::LH_Visitors
   public: CSmartField      <OD_Site, int        >    m_LH_Visitors;
// ����:   int Site::LH_VisitorReturns
   public: CSmartField      <OD_Site, int        >    m_LH_VisitorReturns;
// ����:   int Site::LH_VisitorReturns_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_VisitorReturns_Prc;
// ����:   int Site::LH_SessionNum
   public: CSmartField      <OD_Site, int        >    m_LH_SessionNum;
// ����:   int Site::LH_AveSessionTime
   public: CSmartField      <OD_Site, int        >    m_LH_AveSessionTime;
// ����:   int Site::LH_AveReloadTime
   public: CSmartField      <OD_Site, int        >    m_LH_AveReloadTime;
// ����:   int Site::LH_AveReloadNum
   public: CSmartField      <OD_Site, int        >    m_LH_AveReloadNum;
// ����:   int Site::LH_Shows
   public: CSmartField      <OD_Site, int        >    m_LH_Shows;
// ����:   int Site::LH_Clicks
   public: CSmartField      <OD_Site, int        >    m_LH_Clicks;
// ����:   int Site::LH_CTR_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_CTR_Prc;
// ����:   int Site::LH_CPH_Prc
   public: CSmartField      <OD_Site, int        >    m_LH_CPH_Prc;
// ����:   int Site::CustomIndex1
   public: CSmartField      <OD_Site, int        >    m_CustomIndex1;
// ����:   int Site::CustomIndex2
   public: CSmartField      <OD_Site, int        >    m_CustomIndex2;
// ����:   int Site::CustomIndex3
   public: CSmartField      <OD_Site, int        >    m_CustomIndex3;
// ����:   int Site::CustomIndex4
   public: CSmartField      <OD_Site, int        >    m_CustomIndex4;
// ����:   int Site::CustomIndex5
   public: CSmartField      <OD_Site, int        >    m_CustomIndex5;
// ����:   bool Site::Allowed
   public: CSmartField      <OD_Site, bool       >    m_Allowed;
// ����:   byte Site::ObjectState
   public: CSmartField      <OD_Site, byte       >    m_ObjectState;
// ����:   identifier Site::TagID
   public: CSmartField      <OD_Site, identifier >    m_TagID;
// ����:   bool Site::TagBool
   public: CSmartField      <OD_Site, bool       >    m_TagBool;
// ����:   int Site::TagInt
   public: CSmartField      <OD_Site, int        >    m_TagInt;
// ����:   identifier Site::RatingPlaceInfo
   public: CSmartField      <OD_Site, identifier >    m_RatingPlaceInfo;
// ����:   int Site::CacheTime
   public: CSmartField      <OD_Site, int        >    m_CacheTime;
// ����:   string Site::Announce []
   public: CSmartFieldArray <OD_Site, string     >    m_Announce;
// ����:   identifier Site::Keyword []
   public: CSmartFieldArray <OD_Site, identifier >    m_Keyword;
// ����:   string Site::MirrorInclude []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorInclude;
// ����:   string Site::MirrorExclude []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorExclude;
// ����:   string Site::MirrorSubstr []
   public: CSmartFieldArray <OD_Site, string     >    m_MirrorSubstr;
// ����:   string Site::IgnoredIP []
   public: CSmartFieldArray <OD_Site, string     >    m_IgnoredIP;
// ����:   identifier Site::IgnoredViewerID []
   public: CSmartFieldArray <OD_Site, identifier >    m_IgnoredViewerID;
// ����:   byte Site::ba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_ba_Concept;
// ����:   byte Site::pba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_pba_Concept;
// ����:   byte Site::eba_Concept []
   public: CSmartFieldArray <OD_Site, byte       >    m_eba_Concept;
// ����:   int Site::CRN_Self []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Self;
// ����:   identifier Site::Page []
   public: CSmartFieldArray <OD_Site, identifier >    m_Page;
// ����:   string Site::PageName []
   public: CSmartFieldArray <OD_Site, string     >    m_PageName;
// ����:   int Site::PageNo []
   public: CSmartFieldArray <OD_Site, int        >    m_PageNo;
// ����:   identifier Site::AdBannerProfile []
   public: CSmartFieldArray <OD_Site, identifier >    m_AdBannerProfile;
// ����:   int Site::CRA_Visitor []
   public: CSmartFieldArray <OD_Site, int        >    m_CRA_Visitor;
// ����:   int Site::CRN_Visitor []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Visitor;
// ����:   int Site::CRA_Inquiry []
   public: CSmartFieldArray <OD_Site, int        >    m_CRA_Inquiry;
// ����:   int Site::CRN_Inquiry []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_Inquiry;
// ����:   int Site::CRN_VisitorIncr []
   public: CSmartFieldArray <OD_Site, int        >    m_CRN_VisitorIncr;
// ����:   identifier Site::Audience_SiteID []
   public: CSmartFieldArray <OD_Site, identifier >    m_Audience_SiteID;
// ����:   int Site::Audience_Viewers []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_Viewers;
// ����:   int Site::Audience_Hosts []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_Hosts;
// ����:   int Site::Audience_SiteIDInclude []
   public: CSmartFieldArray <OD_Site, int        >    m_Audience_SiteIDInclude;
// ����:   identifier Site::ActiveViewersID []
   public: CSmartFieldArray <OD_Site, identifier >    m_ActiveViewersID;
// ����:   int Site::ActiveViewersHits []
   public: CSmartFieldArray <OD_Site, int        >    m_ActiveViewersHits;
// ����:   identifier Site::RecentVisitor []
   public: CSmartFieldArray <OD_Site, identifier >    m_RecentVisitor;
// ����:   identifier Site::RecentReferrer []
   public: CSmartFieldArray <OD_Site, identifier >    m_RecentReferrer;
// ����:   int Site::RecentTimeStamp []
   public: CSmartFieldArray <OD_Site, int        >    m_RecentTimeStamp;
// ����:   identifier Site::Referrer []
   public: CSmartFieldArray <OD_Site, identifier >    m_Referrer;
// ����:   int Site::ReferrerCount []
   public: CSmartFieldArray <OD_Site, int        >    m_ReferrerCount;
// ����:   identifier Site::DailyReferrerStats []
   public: CSmartFieldArray <OD_Site, identifier >    m_DailyReferrerStats;
// ����:   int Site::DailyReferrerTimeStamp []
   public: CSmartFieldArray <OD_Site, int        >    m_DailyReferrerTimeStamp;
// ����:   int Site::Inquire []
   public: CSmartFieldArray <OD_Site, int        >    m_Inquire;
// ����:   int Site::ReturnNumRate []
   public: CSmartFieldArray <OD_Site, int        >    m_ReturnNumRate;
// ����:   int Site::ShowNumRate []
   public: CSmartFieldArray <OD_Site, int        >    m_ShowNumRate;
// ����:   byte Site::ba_ModeratorComment []
   public: CSmartFieldArray <OD_Site, byte       >    m_ba_ModeratorComment;
// ����:   identifier Site::ReservedID []
   public: CSmartFieldArray <OD_Site, identifier >    m_ReservedID;
// ����:   int Site::ReservedInt []
   public: CSmartFieldArray <OD_Site, int        >    m_ReservedInt;
// ����:   string Site::ReservedString []
   public: CSmartFieldArray <OD_Site, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [VBN, Name]
   public: void SetIndex_VBN_Name ();
// ���������� ������� ������ �� ���� [Alias]
   public: void SetIndex_Alias ();
// ���������� ������� ������ �� ������ ����� [VBN, CreationTime]
   public: void SetIndex_VBN_CreationTime ();
// ���������� ������� ������ �� ���� [LastVisitTime]
   public: void SetIndex_LastVisitTime ();
// ���������� ������� ������ �� ���� [LastUpdateTime]
   public: void SetIndex_LastUpdateTime ();
// ���������� ������� ������ �� ������ ����� [VBN, Allowed, ObjectState]
   public: void SetIndex_VBN_Allowed_ObjectState ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Loads]
   public: void SetIndex_VBN__Total_Loads ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Hosts]
   public: void SetIndex_VBN__Total_Hosts ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Hits]
   public: void SetIndex_VBN__Total_Hits ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AnonymousHits]
   public: void SetIndex_VBN__Total_AnonymousHits ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AnonymousHits_Prc]
   public: void SetIndex_VBN__Total_AnonymousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_SuspiciousHits_Prc]
   public: void SetIndex_VBN__Total_SuspiciousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Visitors]
   public: void SetIndex_VBN__Total_Visitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_VisitorReturns]
   public: void SetIndex_VBN__Total_VisitorReturns ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_VisitorReturns_Prc]
   public: void SetIndex_VBN__Total_VisitorReturns_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_SessionNum]
   public: void SetIndex_VBN__Total_SessionNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AveSessionTime]
   public: void SetIndex_VBN__Total_AveSessionTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AveReloadTime]
   public: void SetIndex_VBN__Total_AveReloadTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AveReloadNum]
   public: void SetIndex_VBN__Total_AveReloadNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Shows]
   public: void SetIndex_VBN__Total_Shows ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Clicks]
   public: void SetIndex_VBN__Total_Clicks ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_CTR_Prc]
   public: void SetIndex_VBN__Total_CTR_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_CPH_Prc]
   public: void SetIndex_VBN__Total_CPH_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AnonymousVisitors]
   public: void SetIndex_VBN__Total_AnonymousVisitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_AnonymousVisitors_Prc]
   public: void SetIndex_VBN__Total_AnonymousVisitors_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_VisitorExperience]
   public: void SetIndex_VBN__Total_VisitorExperience ();
// ���������� ������� ������ �� ������ ����� [VBN, -Ave_VisitorExperience]
   public: void SetIndex_VBN__Ave_VisitorExperience ();
// ���������� ������� ������ �� ������ ����� [VBN, -OnlineVisitors]
   public: void SetIndex_VBN__OnlineVisitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_MouseOver]
   public: void SetIndex_VBN__Total_MouseOver ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Votes]
   public: void SetIndex_VBN__Total_Votes ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Votes_Sum]
   public: void SetIndex_VBN__Total_Votes_Sum ();
// ���������� ������� ������ �� ������ ����� [VBN, -Total_Votes_Ave]
   public: void SetIndex_VBN__Total_Votes_Ave ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Loads]
   public: void SetIndex_VBN__LM_Loads ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Hosts]
   public: void SetIndex_VBN__LM_Hosts ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Hits]
   public: void SetIndex_VBN__LM_Hits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_AnonymousHits]
   public: void SetIndex_VBN__LM_AnonymousHits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_AnonymousHits_Prc]
   public: void SetIndex_VBN__LM_AnonymousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LM_SuspiciousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Visitors]
   public: void SetIndex_VBN__LM_Visitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_VisitorReturns]
   public: void SetIndex_VBN__LM_VisitorReturns ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_VisitorReturns_Prc]
   public: void SetIndex_VBN__LM_VisitorReturns_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_SessionNum]
   public: void SetIndex_VBN__LM_SessionNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_AveSessionTime]
   public: void SetIndex_VBN__LM_AveSessionTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_AveReloadTime]
   public: void SetIndex_VBN__LM_AveReloadTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_AveReloadNum]
   public: void SetIndex_VBN__LM_AveReloadNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Shows]
   public: void SetIndex_VBN__LM_Shows ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_Clicks]
   public: void SetIndex_VBN__LM_Clicks ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_CTR_Prc]
   public: void SetIndex_VBN__LM_CTR_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LM_CPH_Prc]
   public: void SetIndex_VBN__LM_CPH_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Loads]
   public: void SetIndex_VBN__LW_Loads ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Hosts]
   public: void SetIndex_VBN__LW_Hosts ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Hits]
   public: void SetIndex_VBN__LW_Hits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_AnonymousHits]
   public: void SetIndex_VBN__LW_AnonymousHits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_AnonymousHits_Prc]
   public: void SetIndex_VBN__LW_AnonymousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LW_SuspiciousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Visitors]
   public: void SetIndex_VBN__LW_Visitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_VisitorReturns]
   public: void SetIndex_VBN__LW_VisitorReturns ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_VisitorReturns_Prc]
   public: void SetIndex_VBN__LW_VisitorReturns_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_SessionNum]
   public: void SetIndex_VBN__LW_SessionNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_AveSessionTime]
   public: void SetIndex_VBN__LW_AveSessionTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_AveReloadTime]
   public: void SetIndex_VBN__LW_AveReloadTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_AveReloadNum]
   public: void SetIndex_VBN__LW_AveReloadNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Shows]
   public: void SetIndex_VBN__LW_Shows ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_Clicks]
   public: void SetIndex_VBN__LW_Clicks ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_CTR_Prc]
   public: void SetIndex_VBN__LW_CTR_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LW_CPH_Prc]
   public: void SetIndex_VBN__LW_CPH_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Loads]
   public: void SetIndex_VBN__LD_Loads ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Hosts]
   public: void SetIndex_VBN__LD_Hosts ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Hits]
   public: void SetIndex_VBN__LD_Hits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_AnonymousHits]
   public: void SetIndex_VBN__LD_AnonymousHits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_AnonymousHits_Prc]
   public: void SetIndex_VBN__LD_AnonymousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LD_SuspiciousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Visitors]
   public: void SetIndex_VBN__LD_Visitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_VisitorReturns]
   public: void SetIndex_VBN__LD_VisitorReturns ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_VisitorReturns_Prc]
   public: void SetIndex_VBN__LD_VisitorReturns_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_SessionNum]
   public: void SetIndex_VBN__LD_SessionNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_AveSessionTime]
   public: void SetIndex_VBN__LD_AveSessionTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_AveReloadTime]
   public: void SetIndex_VBN__LD_AveReloadTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_AveReloadNum]
   public: void SetIndex_VBN__LD_AveReloadNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Shows]
   public: void SetIndex_VBN__LD_Shows ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_Clicks]
   public: void SetIndex_VBN__LD_Clicks ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_CTR_Prc]
   public: void SetIndex_VBN__LD_CTR_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LD_CPH_Prc]
   public: void SetIndex_VBN__LD_CPH_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Loads]
   public: void SetIndex_VBN__LH_Loads ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Hosts]
   public: void SetIndex_VBN__LH_Hosts ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Hits]
   public: void SetIndex_VBN__LH_Hits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_AnonymousHits]
   public: void SetIndex_VBN__LH_AnonymousHits ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_AnonymousHits_Prc]
   public: void SetIndex_VBN__LH_AnonymousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_SuspiciousHits_Prc]
   public: void SetIndex_VBN__LH_SuspiciousHits_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Visitors]
   public: void SetIndex_VBN__LH_Visitors ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_VisitorReturns]
   public: void SetIndex_VBN__LH_VisitorReturns ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_VisitorReturns_Prc]
   public: void SetIndex_VBN__LH_VisitorReturns_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_SessionNum]
   public: void SetIndex_VBN__LH_SessionNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_AveSessionTime]
   public: void SetIndex_VBN__LH_AveSessionTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_AveReloadTime]
   public: void SetIndex_VBN__LH_AveReloadTime ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_AveReloadNum]
   public: void SetIndex_VBN__LH_AveReloadNum ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Shows]
   public: void SetIndex_VBN__LH_Shows ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_Clicks]
   public: void SetIndex_VBN__LH_Clicks ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_CTR_Prc]
   public: void SetIndex_VBN__LH_CTR_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -LH_CPH_Prc]
   public: void SetIndex_VBN__LH_CPH_Prc ();
// ���������� ������� ������ �� ������ ����� [VBN, -CustomIndex1]
   public: void SetIndex_VBN__CustomIndex1 ();
// ���������� ������� ������ �� ������ ����� [VBN, -CustomIndex2]
   public: void SetIndex_VBN__CustomIndex2 ();
// ���������� ������� ������ �� ������ ����� [VBN, -CustomIndex3]
   public: void SetIndex_VBN__CustomIndex3 ();
// ���������� ������� ������ �� ������ ����� [VBN, -CustomIndex4]
   public: void SetIndex_VBN__CustomIndex4 ();
// ���������� ������� ������ �� ������ ����� [VBN, -CustomIndex5]
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
// ���������� �������� ���� ������ ������ "SiteProfile"
// 
class OC_SiteProfile: public OC_Object <OC_SiteProfile>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_SiteProfile  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_SiteProfile  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_SiteProfile  (const OC_SiteProfile& from);
// ���������� ����������� �������
   public: ~OC_SiteProfile ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SiteProfile& operator= (const OC_SiteProfile& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SiteProfile& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_SiteProfile& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_SiteProfile& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_SiteProfile& operator << (OC_SiteProfile& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_SiteProfile& operator >> (OC_SiteProfile& from);

// ����:   string SiteProfile::Name
   public: CSmartField      <OD_SiteProfile, string     >    m_Name;
// ����:   byte SiteProfile::VBN
   public: CSmartField      <OD_SiteProfile, byte       >    m_VBN;
// ����:   int SiteProfile::LastModified
   public: CSmartField      <OD_SiteProfile, int        >    m_LastModified;
// ����:   identifier SiteProfile::OwnerID
   public: CSmartField      <OD_SiteProfile, identifier >    m_OwnerID;
// ����:   int SiteProfile::MaxFileSize
   public: CSmartField      <OD_SiteProfile, int        >    m_MaxFileSize;
// ����:   bool SiteProfile::UseKeywords
   public: CSmartField      <OD_SiteProfile, bool       >    m_UseKeywords;
// ����:   bool SiteProfile::StaticSupport
   public: CSmartField      <OD_SiteProfile, bool       >    m_StaticSupport;
// ����:   bool SiteProfile::Allowed
   public: CSmartField      <OD_SiteProfile, bool       >    m_Allowed;
// ����:   byte SiteProfile::ObjectState
   public: CSmartField      <OD_SiteProfile, byte       >    m_ObjectState;
// ����:   identifier SiteProfile::TagID
   public: CSmartField      <OD_SiteProfile, identifier >    m_TagID;
// ����:   bool SiteProfile::TagBool
   public: CSmartField      <OD_SiteProfile, bool       >    m_TagBool;
// ����:   int SiteProfile::TagInt
   public: CSmartField      <OD_SiteProfile, int        >    m_TagInt;
// ����:   int SiteProfile::CacheTime
   public: CSmartField      <OD_SiteProfile, int        >    m_CacheTime;
// ����:   identifier SiteProfile::Site []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_Site;
// ����:   identifier SiteProfile::DefaultKeyword []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_DefaultKeyword;
// ����:   identifier SiteProfile::BannerInclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_BannerInclude;
// ����:   identifier SiteProfile::BannerExclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_BannerExclude;
// ����:   identifier SiteProfile::SiteInclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_SiteInclude;
// ����:   identifier SiteProfile::SiteExclude []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_SiteExclude;
// ����:   byte SiteProfile::ba_BannerConceptInclude []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_BannerConceptInclude;
// ����:   byte SiteProfile::ba_BannerConceptExclude []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_BannerConceptExclude;
// ����:   byte SiteProfile::eba_BannerConcept []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_eba_BannerConcept;
// ����:   int SiteProfile::Price []
   public: CSmartFieldArray <OD_SiteProfile, int        >    m_Price;
// ����:   byte SiteProfile::ba_ModeratorComment []
   public: CSmartFieldArray <OD_SiteProfile, byte       >    m_ba_ModeratorComment;
// ����:   identifier SiteProfile::ReservedID []
   public: CSmartFieldArray <OD_SiteProfile, identifier >    m_ReservedID;
// ����:   int SiteProfile::ReservedInt []
   public: CSmartFieldArray <OD_SiteProfile, int        >    m_ReservedInt;
// ����:   string SiteProfile::ReservedString []
   public: CSmartFieldArray <OD_SiteProfile, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [VBN, Allowed, ObjectState]
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
// ���������� �������� ���� ������ ������ "ShowEvent"
// 
class OC_ShowEvent: public OC_Object <OC_ShowEvent>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_ShowEvent  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_ShowEvent  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_ShowEvent  (const OC_ShowEvent& from);
// ���������� ����������� �������
   public: ~OC_ShowEvent ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ShowEvent& operator= (const OC_ShowEvent& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ShowEvent& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_ShowEvent& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_ShowEvent& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_ShowEvent& operator << (OC_ShowEvent& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_ShowEvent& operator >> (OC_ShowEvent& from);

// ����:   identifier ShowEvent::SiteID
   public: CSmartField      <OD_ShowEvent, identifier >    m_SiteID;
// ����:   identifier ShowEvent::ViewerID
   public: CSmartField      <OD_ShowEvent, identifier >    m_ViewerID;
// ����:   int ShowEvent::Time
   public: CSmartField      <OD_ShowEvent, int        >    m_Time;
// ����:   int ShowEvent::ExitCode
   public: CSmartField      <OD_ShowEvent, int        >    m_ExitCode;
// ����:   identifier ShowEvent::TagID
   public: CSmartField      <OD_ShowEvent, identifier >    m_TagID;
// ����:   int ShowEvent::TagInt
   public: CSmartField      <OD_ShowEvent, int        >    m_TagInt;
// ����:   bool ShowEvent::TagBool
   public: CSmartField      <OD_ShowEvent, bool       >    m_TagBool;
// ����:   string ShowEvent::ReservedString
   public: CSmartField      <OD_ShowEvent, string     >    m_ReservedString;
// ����:   int ShowEvent::CacheTime
   public: CSmartField      <OD_ShowEvent, int        >    m_CacheTime;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Time]
   public: void SetIndex_Time ();
// ���������� ������� ������ �� ������ ����� [SiteID, ViewerID, -Time]
   public: void SetIndex_SiteID_ViewerID__Time ();
// ���������� ������� ������ �� ������ ����� [SiteID, ViewerID]
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
// ���������� �������� ���� ������ ������ "Registry"
// 
class OC_Registry: public OC_Object <OC_Registry>
{
// ��� ����� ����������� ������-�������.
// ��� �������� ����������� �� ������������� ���������������
// �� ������������ ������-������ ����� ������.
// ��� ���� ������������ ������ �������� � ������������� (New,
// Open, ...), �������� (Delete) � ������ � ���������.
   void About_class_OC_Master ();

// ����������� ������-������.
// ���������� ������������� ���������� �� ������!
// * ������������ ������ �������� � ������������� (New, Open, ...)
//   �������� (Delete) � ������ � ���������.
   public: OC_Registry  ();// ���������� ����������� �������
   public: ~OC_Registry ();


// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();

// ����:   string Registry::AdminPassword
   public: CSmartField      <OD_Registry, string     >    m_AdminPassword;
// ����:   int Registry::CRN_InetAudience_Update
   public: CSmartField      <OD_Registry, int        >    m_CRN_InetAudience_Update;
// ����:   int Registry::VisitorHistoryLength
   public: CSmartField      <OD_Registry, int        >    m_VisitorHistoryLength;
// ����:   int Registry::MinimumHitsTime
   public: CSmartField      <OD_Registry, int        >    m_MinimumHitsTime;
// ����:   int Registry::SuspiciousInfoSize
   public: CSmartField      <OD_Registry, int        >    m_SuspiciousInfoSize;
// ����:   int Registry::ActiveViewersSize
   public: CSmartField      <OD_Registry, int        >    m_ActiveViewersSize;
// ����:   int Registry::ReturnNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ReturnNumRateSize;
// ����:   int Registry::DailyReferrerSize
   public: CSmartField      <OD_Registry, int        >    m_DailyReferrerSize;
// ����:   int Registry::ClickNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ClickNumRateSize;
// ����:   int Registry::ShowNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_ShowNumRateSize;
// ����:   int Registry::HitNumRateSize
   public: CSmartField      <OD_Registry, int        >    m_HitNumRateSize;
// ����:   int Registry::SessionTimeRateSize
   public: CSmartField      <OD_Registry, int        >    m_SessionTimeRateSize;
// ����:   int Registry::CachePurgeTime_IPRecord
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_IPRecord;
// ����:   int Registry::CachePurgeTime_RatingPlaceInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_RatingPlaceInfo;
// ����:   int Registry::CachePurgeTime_SuspiciousInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SuspiciousInfo;
// ����:   int Registry::CachePurgeTime_SearchWordsInfo
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SearchWordsInfo;
// ����:   int Registry::CachePurgeTime_DailyReferrerStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_DailyReferrerStats;
// ����:   int Registry::CachePurgeTime_DayStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_DayStats;
// ����:   int Registry::CachePurgeTime_YearStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_YearStats;
// ����:   int Registry::CachePurgeTime_TimeStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_TimeStats;
// ����:   int Registry::CachePurgeTime_ModeratorComment
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_ModeratorComment;
// ����:   int Registry::CachePurgeTime_Keyword
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Keyword;
// ����:   int Registry::CachePurgeTime_SiteList
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_SiteList;
// ����:   int Registry::CachePurgeTime_Concept
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Concept;
// ����:   int Registry::CachePurgeTime_Language
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Language;
// ����:   int Registry::CachePurgeTime_VBN
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_VBN;
// ����:   int Registry::CachePurgeTime_Site
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Site;
// ����:   int Registry::CachePurgeTime_Page
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Page;
// ����:   int Registry::CachePurgeTime_BannerProfile
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_BannerProfile;
// ����:   int Registry::CachePurgeTime_Banner
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Banner;
// ����:   int Registry::CachePurgeTime_TradeStats
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_TradeStats;
// ����:   int Registry::CachePurgeTime_User
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_User;
// ����:   int Registry::CachePurgeTime_ViewerGroup
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_ViewerGroup;
// ����:   int Registry::CachePurgeTime_Viewer
   public: CSmartField      <OD_Registry, int        >    m_CachePurgeTime_Viewer;
// ����:   int Registry::ReloadTimeThreshold
   public: CSmartField      <OD_Registry, int        >    m_ReloadTimeThreshold;
// ����:   float Registry::ViewerCacheReloadThreshold
   public: CSmartField      <OD_Registry, float      >    m_ViewerCacheReloadThreshold;
// ����:   float Registry::DefaultPriority
   public: CSmartField      <OD_Registry, float      >    m_DefaultPriority;
// ����:   int Registry::BannerStore_Expire
   public: CSmartField      <OD_Registry, int        >    m_BannerStore_Expire;
// ����:   int Registry::BannerStore_MaxLength
   public: CSmartField      <OD_Registry, int        >    m_BannerStore_MaxLength;
// ����:   int Registry::SiteStore_Expire
   public: CSmartField      <OD_Registry, int        >    m_SiteStore_Expire;
// ����:   int Registry::SiteStore_MaxLength
   public: CSmartField      <OD_Registry, int        >    m_SiteStore_MaxLength;
// ����:   int Registry::MaxDailyEventsDefault
   public: CSmartField      <OD_Registry, int        >    m_MaxDailyEventsDefault;
// ����:   identifier Registry::TagID1
   public: CSmartField      <OD_Registry, identifier >    m_TagID1;
// ����:   identifier Registry::TagID2
   public: CSmartField      <OD_Registry, identifier >    m_TagID2;
// ����:   identifier Registry::TagID3
   public: CSmartField      <OD_Registry, identifier >    m_TagID3;
// ����:   bool Registry::TagBool1
   public: CSmartField      <OD_Registry, bool       >    m_TagBool1;
// ����:   bool Registry::TagBool2
   public: CSmartField      <OD_Registry, bool       >    m_TagBool2;
// ����:   bool Registry::TagBool3
   public: CSmartField      <OD_Registry, bool       >    m_TagBool3;
// ����:   int Registry::TagInt1
   public: CSmartField      <OD_Registry, int        >    m_TagInt1;
// ����:   int Registry::TagInt2
   public: CSmartField      <OD_Registry, int        >    m_TagInt2;
// ����:   int Registry::TagInt3
   public: CSmartField      <OD_Registry, int        >    m_TagInt3;
// ����:   identifier Registry::ConceptID_Sorted []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ConceptID_Sorted;
// ����:   int Registry::ConceptNo_SortID []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptNo_SortID;
// ����:   identifier Registry::ConceptID_SortNo []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ConceptID_SortNo;
// ����:   int Registry::ConceptParent_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptParent_SortNo;
// ����:   int Registry::ConceptType_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptType_SortNo;
// ����:   int Registry::ConceptLevel_SortNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ConceptLevel_SortNo;
// ����:   identifier Registry::Language []
   public: CSmartFieldArray <OD_Registry, identifier >    m_Language;
// ����:   int Registry::LanguageNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_LanguageNo;
// ����:   identifier Registry::VBN []
   public: CSmartFieldArray <OD_Registry, identifier >    m_VBN;
// ����:   int Registry::VBNNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_VBNNo;
// ����:   identifier Registry::ModeratorComment []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ModeratorComment;
// ����:   int Registry::ModeratorCommentNo []
   public: CSmartFieldArray <OD_Registry, int        >    m_ModeratorCommentNo;
// ����:   int Registry::CRA_InetAudience []
   public: CSmartFieldArray <OD_Registry, int        >    m_CRA_InetAudience;
// ����:   int Registry::CRN_InetAudience []
   public: CSmartFieldArray <OD_Registry, int        >    m_CRN_InetAudience;
// ����:   string Registry::IgnoredIP []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredIP;
// ����:   string Registry::IgnoredUserAgent []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredUserAgent;
// ����:   string Registry::IgnoredBrowser []
   public: CSmartFieldArray <OD_Registry, string     >    m_IgnoredBrowser;
// ����:   string Registry::SearchEngines []
   public: CSmartFieldArray <OD_Registry, string     >    m_SearchEngines;
// ����:   string Registry::Classifiers []
   public: CSmartFieldArray <OD_Registry, string     >    m_Classifiers;
// ����:   int Registry::ReloadDistribution []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReloadDistribution;
// ����:   identifier Registry::Viewers []
   public: CSmartFieldArray <OD_Registry, identifier >    m_Viewers;
// ����:   identifier Registry::ReservedID1 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID1;
// ����:   identifier Registry::ReservedID2 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID2;
// ����:   identifier Registry::ReservedID3 []
   public: CSmartFieldArray <OD_Registry, identifier >    m_ReservedID3;
// ����:   int Registry::ReservedInt1 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt1;
// ����:   int Registry::ReservedInt2 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt2;
// ����:   int Registry::ReservedInt3 []
   public: CSmartFieldArray <OD_Registry, int        >    m_ReservedInt3;
// ����:   string Registry::ReservedString1 []
   public: CSmartFieldArray <OD_Registry, string     >    m_ReservedString1;
// ����:   string Registry::ReservedString2 []
   public: CSmartFieldArray <OD_Registry, string     >    m_ReservedString2;
// ����:   string Registry::ReservedString3 []
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
// ���������� �������� ���� ������ ������ "VBN"
// 
class OC_VBN: public OC_Object <OC_VBN>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_VBN  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_VBN  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_VBN  (const OC_VBN& from);
// ���������� ����������� �������
   public: ~OC_VBN ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_VBN& operator= (const OC_VBN& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_VBN& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_VBN& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_VBN& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_VBN& operator << (OC_VBN& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_VBN& operator >> (OC_VBN& from);

// ����:   string VBN::Password
   public: CSmartField      <OD_VBN, string     >    m_Password;
// ����:   string VBN::Name
   public: CSmartField      <OD_VBN, string     >    m_Name;
// ����:   string VBN::Description
   public: CSmartField      <OD_VBN, string     >    m_Description;
// ����:   bool VBN::IsModerated
   public: CSmartField      <OD_VBN, bool       >    m_IsModerated;
// ����:   identifier VBN::DefaultLanguage
   public: CSmartField      <OD_VBN, identifier >    m_DefaultLanguage;
// ����:   int VBN::DefaultTZOffset
   public: CSmartField      <OD_VBN, int        >    m_DefaultTZOffset;
// ����:   identifier VBN::Owner
   public: CSmartField      <OD_VBN, identifier >    m_Owner;
// ����:   identifier VBN::AdminEventList
   public: CSmartField      <OD_VBN, identifier >    m_AdminEventList;
// ����:   byte VBN::No
   public: CSmartField      <OD_VBN, byte       >    m_No;
// ����:   int VBN::OnlineVisitors
   public: CSmartField      <OD_VBN, int        >    m_OnlineVisitors;
// ����:   identifier VBN::Hits
   public: CSmartField      <OD_VBN, identifier >    m_Hits;
// ����:   identifier VBN::Hosts
   public: CSmartField      <OD_VBN, identifier >    m_Hosts;
// ����:   identifier VBN::Visitors
   public: CSmartField      <OD_VBN, identifier >    m_Visitors;
// ����:   identifier VBN::Shows
   public: CSmartField      <OD_VBN, identifier >    m_Shows;
// ����:   identifier VBN::Clicks
   public: CSmartField      <OD_VBN, identifier >    m_Clicks;
// ����:   identifier VBN::SessionTime
   public: CSmartField      <OD_VBN, identifier >    m_SessionTime;
// ����:   identifier VBN::SessionNum
   public: CSmartField      <OD_VBN, identifier >    m_SessionNum;
// ����:   int VBN::Total_Hosts
   public: CSmartField      <OD_VBN, int        >    m_Total_Hosts;
// ����:   int VBN::Total_Shows
   public: CSmartField      <OD_VBN, int        >    m_Total_Shows;
// ����:   int VBN::Total_Clicks
   public: CSmartField      <OD_VBN, int        >    m_Total_Clicks;
// ����:   int VBN::Total_Hits
   public: CSmartField      <OD_VBN, int        >    m_Total_Hits;
// ����:   int VBN::Total_Visitors
   public: CSmartField      <OD_VBN, int        >    m_Total_Visitors;
// ����:   int VBN::Total_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_Total_VisitorReturns;
// ����:   int VBN::Total_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_Total_AveSessionTime;
// ����:   int VBN::Total_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_Total_AveReloadTime;
// ����:   int VBN::Total_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_Total_AveReloadNum;
// ����:   int VBN::LM_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LM_Visitors;
// ����:   int VBN::LM_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LM_VisitorReturns;
// ����:   int VBN::LM_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LM_VisitorReturns_Prc;
// ����:   int VBN::LM_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LM_Hosts;
// ����:   int VBN::LM_Shows
   public: CSmartField      <OD_VBN, int        >    m_LM_Shows;
// ����:   int VBN::LM_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LM_Clicks;
// ����:   int VBN::LM_Hits
   public: CSmartField      <OD_VBN, int        >    m_LM_Hits;
// ����:   int VBN::LM_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LM_AveSessionTime;
// ����:   int VBN::LM_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LM_AveReloadTime;
// ����:   int VBN::LM_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LM_AveReloadNum;
// ����:   int VBN::LW_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LW_Visitors;
// ����:   int VBN::LW_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LW_VisitorReturns;
// ����:   int VBN::LW_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LW_VisitorReturns_Prc;
// ����:   int VBN::LW_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LW_Hosts;
// ����:   int VBN::LW_Shows
   public: CSmartField      <OD_VBN, int        >    m_LW_Shows;
// ����:   int VBN::LW_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LW_Clicks;
// ����:   int VBN::LW_Hits
   public: CSmartField      <OD_VBN, int        >    m_LW_Hits;
// ����:   int VBN::LW_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LW_AveSessionTime;
// ����:   int VBN::LW_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LW_AveReloadTime;
// ����:   int VBN::LW_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LW_AveReloadNum;
// ����:   int VBN::LD_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LD_Visitors;
// ����:   int VBN::LD_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LD_VisitorReturns;
// ����:   int VBN::LD_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LD_VisitorReturns_Prc;
// ����:   int VBN::LD_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LD_Hosts;
// ����:   int VBN::LD_Shows
   public: CSmartField      <OD_VBN, int        >    m_LD_Shows;
// ����:   int VBN::LD_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LD_Clicks;
// ����:   int VBN::LD_Hits
   public: CSmartField      <OD_VBN, int        >    m_LD_Hits;
// ����:   int VBN::LD_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LD_AveSessionTime;
// ����:   int VBN::LD_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LD_AveReloadTime;
// ����:   int VBN::LD_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LD_AveReloadNum;
// ����:   int VBN::LH_Visitors
   public: CSmartField      <OD_VBN, int        >    m_LH_Visitors;
// ����:   int VBN::LH_VisitorReturns
   public: CSmartField      <OD_VBN, int        >    m_LH_VisitorReturns;
// ����:   int VBN::LH_VisitorReturns_Prc
   public: CSmartField      <OD_VBN, int        >    m_LH_VisitorReturns_Prc;
// ����:   int VBN::LH_Hosts
   public: CSmartField      <OD_VBN, int        >    m_LH_Hosts;
// ����:   int VBN::LH_Shows
   public: CSmartField      <OD_VBN, int        >    m_LH_Shows;
// ����:   int VBN::LH_Clicks
   public: CSmartField      <OD_VBN, int        >    m_LH_Clicks;
// ����:   int VBN::LH_Hits
   public: CSmartField      <OD_VBN, int        >    m_LH_Hits;
// ����:   int VBN::LH_AveSessionTime
   public: CSmartField      <OD_VBN, int        >    m_LH_AveSessionTime;
// ����:   int VBN::LH_AveReloadTime
   public: CSmartField      <OD_VBN, int        >    m_LH_AveReloadTime;
// ����:   int VBN::LH_AveReloadNum
   public: CSmartField      <OD_VBN, int        >    m_LH_AveReloadNum;
// ����:   bool VBN::TagBool1
   public: CSmartField      <OD_VBN, bool       >    m_TagBool1;
// ����:   bool VBN::TagBool2
   public: CSmartField      <OD_VBN, bool       >    m_TagBool2;
// ����:   identifier VBN::TagID1
   public: CSmartField      <OD_VBN, identifier >    m_TagID1;
// ����:   identifier VBN::TagID2
   public: CSmartField      <OD_VBN, identifier >    m_TagID2;
// ����:   int VBN::TagInt1
   public: CSmartField      <OD_VBN, int        >    m_TagInt1;
// ����:   int VBN::TagInt2
   public: CSmartField      <OD_VBN, int        >    m_TagInt2;
// ����:   float VBN::TagFloat1
   public: CSmartField      <OD_VBN, float      >    m_TagFloat1;
// ����:   float VBN::TagFloat2
   public: CSmartField      <OD_VBN, float      >    m_TagFloat2;
// ����:   string VBN::TagString1
   public: CSmartField      <OD_VBN, string     >    m_TagString1;
// ����:   string VBN::TagString2
   public: CSmartField      <OD_VBN, string     >    m_TagString2;
// ����:   int VBN::CacheTime
   public: CSmartField      <OD_VBN, int        >    m_CacheTime;
// ����:   byte VBN::ConceptMask []
   public: CSmartFieldArray <OD_VBN, byte       >    m_ConceptMask;
// ����:   identifier VBN::ActiveViewersID []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ActiveViewersID;
// ����:   int VBN::ActiveViewersHosts []
   public: CSmartFieldArray <OD_VBN, int        >    m_ActiveViewersHosts;
// ����:   identifier VBN::ReservedID1 []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ReservedID1;
// ����:   identifier VBN::ReservedID2 []
   public: CSmartFieldArray <OD_VBN, identifier >    m_ReservedID2;
// ����:   int VBN::ReservedInt1 []
   public: CSmartFieldArray <OD_VBN, int        >    m_ReservedInt1;
// ����:   int VBN::ReservedInt2 []
   public: CSmartFieldArray <OD_VBN, int        >    m_ReservedInt2;
// ����:   string VBN::ReservedString1 []
   public: CSmartFieldArray <OD_VBN, string     >    m_ReservedString1;
// ����:   string VBN::ReservedString2 []
   public: CSmartFieldArray <OD_VBN, string     >    m_ReservedString2;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [No]
   public: void SetIndex_No ();
// ���������� ������� ������ �� ���� [Name]
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
// ���������� �������� ���� ������ ������ "Language"
// 
class OC_Language: public OC_Object <OC_Language>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Language  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Language  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Language  (const OC_Language& from);
// ���������� ����������� �������
   public: ~OC_Language ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Language& operator= (const OC_Language& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Language& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Language& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Language& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Language& operator << (OC_Language& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Language& operator >> (OC_Language& from);

// ����:   string Language::ShortName
   public: CSmartField      <OD_Language, string     >    m_ShortName;
// ����:   int Language::No
   public: CSmartField      <OD_Language, int        >    m_No;
// ����:   int Language::CacheTime
   public: CSmartField      <OD_Language, int        >    m_CacheTime;
// ����:   string Language::Name []
   public: CSmartFieldArray <OD_Language, string     >    m_Name;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [No]
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
// ���������� �������� ���� ������ ������ "Concept"
// 
class OC_Concept: public OC_Object <OC_Concept>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Concept  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Concept  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Concept  (const OC_Concept& from);
// ���������� ����������� �������
   public: ~OC_Concept ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Concept& operator= (const OC_Concept& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Concept& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Concept& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Concept& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Concept& operator << (OC_Concept& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Concept& operator >> (OC_Concept& from);

// ����:   identifier Concept::Parent
   public: CSmartField      <OD_Concept, identifier >    m_Parent;
// ����:   int Concept::Level
   public: CSmartField      <OD_Concept, int        >    m_Level;
// ����:   string Concept::ShortName
   public: CSmartField      <OD_Concept, string     >    m_ShortName;
// ����:   string Concept::Type
   public: CSmartField      <OD_Concept, string     >    m_Type;
// ����:   int Concept::TypeNo
   public: CSmartField      <OD_Concept, int        >    m_TypeNo;
// ����:   int Concept::No
   public: CSmartField      <OD_Concept, int        >    m_No;
// ����:   identifier Concept::TagID
   public: CSmartField      <OD_Concept, identifier >    m_TagID;
// ����:   int Concept::TagInt
   public: CSmartField      <OD_Concept, int        >    m_TagInt;
// ����:   bool Concept::TagBool
   public: CSmartField      <OD_Concept, bool       >    m_TagBool;
// ����:   int Concept::CacheTime
   public: CSmartField      <OD_Concept, int        >    m_CacheTime;
// ����:   string Concept::Name []
   public: CSmartFieldArray <OD_Concept, string     >    m_Name;
// ����:   string Concept::Description []
   public: CSmartFieldArray <OD_Concept, string     >    m_Description;
// ����:   identifier Concept::Ancestor []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Ancestor;
// ����:   int Concept::AncestorNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_AncestorNo;
// ����:   int Concept::AncestorWeight []
   public: CSmartFieldArray <OD_Concept, int        >    m_AncestorWeight;
// ����:   identifier Concept::AllAncestor []
   public: CSmartFieldArray <OD_Concept, identifier >    m_AllAncestor;
// ����:   identifier Concept::AllAncestorNo []
   public: CSmartFieldArray <OD_Concept, identifier >    m_AllAncestorNo;
// ����:   identifier Concept::Child []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Child;
// ����:   int Concept::ChildNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_ChildNo;
// ����:   identifier Concept::Descendant []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Descendant;
// ����:   int Concept::DescendantNo []
   public: CSmartFieldArray <OD_Concept, int        >    m_DescendantNo;
// ����:   identifier Concept::VBN_ID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_VBN_ID;
// ����:   identifier Concept::VBN_SiteList []
   public: CSmartFieldArray <OD_Concept, identifier >    m_VBN_SiteList;
// ����:   int Concept::VBN_SiteListSize []
   public: CSmartFieldArray <OD_Concept, int        >    m_VBN_SiteListSize;
// ����:   int Concept::ClickerConcept_Work []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Work;
// ����:   int Concept::ClickerConcept_Home []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Home;
// ����:   int Concept::ClickerConcept_Night []
   public: CSmartFieldArray <OD_Concept, int        >    m_ClickerConcept_Night;
// ����:   identifier Concept::Ads_SiteID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_Ads_SiteID;
// ����:   int Concept::Ads_ShowRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ShowRate;
// ����:   int Concept::Ads_ClickRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ClickRate;
// ����:   int Concept::Ads_ViewRate []
   public: CSmartFieldArray <OD_Concept, int        >    m_Ads_ViewRate;
// ����:   identifier Concept::ReservedID []
   public: CSmartFieldArray <OD_Concept, identifier >    m_ReservedID;
// ����:   int Concept::ReservedInt []
   public: CSmartFieldArray <OD_Concept, int        >    m_ReservedInt;
// ����:   string Concept::ReservedString []
   public: CSmartFieldArray <OD_Concept, string     >    m_ReservedString;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Level]
   public: void SetIndex_Level ();
// ���������� ������� ������ �� ���� [No]
   public: void SetIndex_No ();
// ���������� ������� ������ �� ������ ����� [Type, Level, ShortName]
   public: void SetIndex_Type_Level_ShortName ();
// ���������� ������� ������ �� ���� [TypeNo]
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
// ���������� �������� ���� ������ ������ "SiteList"
// 
class OC_SiteList: public OC_Object <OC_SiteList>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_SiteList  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_SiteList  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_SiteList  (const OC_SiteList& from);
// ���������� ����������� �������
   public: ~OC_SiteList ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SiteList& operator= (const OC_SiteList& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SiteList& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_SiteList& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_SiteList& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_SiteList& operator << (OC_SiteList& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_SiteList& operator >> (OC_SiteList& from);

// ����:   int SiteList::CacheTime
   public: CSmartField      <OD_SiteList, int        >    m_CacheTime;
// ����:   identifier SiteList::Site []
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
// ���������� �������� ���� ������ ������ "Keyword"
// 
class OC_Keyword: public OC_Object <OC_Keyword>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Keyword  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Keyword  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Keyword  (const OC_Keyword& from);
// ���������� ����������� �������
   public: ~OC_Keyword ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Keyword& operator= (const OC_Keyword& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Keyword& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Keyword& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Keyword& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Keyword& operator << (OC_Keyword& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Keyword& operator >> (OC_Keyword& from);

// ����:   string Keyword::Word
   public: CSmartField      <OD_Keyword, string     >    m_Word;
// ����:   int Keyword::CacheTime
   public: CSmartField      <OD_Keyword, int        >    m_CacheTime;
// ����:   identifier Keyword::VBN_ID []
   public: CSmartFieldArray <OD_Keyword, identifier >    m_VBN_ID;
// ����:   identifier Keyword::VBN_SiteList []
   public: CSmartFieldArray <OD_Keyword, identifier >    m_VBN_SiteList;
// ����:   int Keyword::VBN_SiteListSize []
   public: CSmartFieldArray <OD_Keyword, int        >    m_VBN_SiteListSize;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Word]
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
// ���������� �������� ���� ������ ������ "ModeratorComment"
// 
class OC_ModeratorComment: public OC_Object <OC_ModeratorComment>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_ModeratorComment  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_ModeratorComment  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_ModeratorComment  (const OC_ModeratorComment& from);
// ���������� ����������� �������
   public: ~OC_ModeratorComment ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ModeratorComment& operator= (const OC_ModeratorComment& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ModeratorComment& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_ModeratorComment& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_ModeratorComment& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_ModeratorComment& operator << (OC_ModeratorComment& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_ModeratorComment& operator >> (OC_ModeratorComment& from);

// ����:   int ModeratorComment::No
   public: CSmartField      <OD_ModeratorComment, int        >    m_No;
// ����:   int ModeratorComment::CacheTime
   public: CSmartField      <OD_ModeratorComment, int        >    m_CacheTime;
// ����:   string ModeratorComment::Name []
   public: CSmartFieldArray <OD_ModeratorComment, string     >    m_Name;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [No]
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
// ���������� �������� ���� ������ ������ "TimeStats"
// 
class OC_TimeStats: public OC_Object <OC_TimeStats>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_TimeStats  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_TimeStats  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_TimeStats  (const OC_TimeStats& from);
// ���������� ����������� �������
   public: ~OC_TimeStats ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_TimeStats& operator= (const OC_TimeStats& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_TimeStats& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_TimeStats& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_TimeStats& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_TimeStats& operator << (OC_TimeStats& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_TimeStats& operator >> (OC_TimeStats& from);

// ����:   int TimeStats::Total
   public: CSmartField      <OD_TimeStats, int        >    m_Total;
// ����:   int TimeStats::TwoLastDaysMinute_year
   public: CSmartField      <OD_TimeStats, int        >    m_TwoLastDaysMinute_year;
// ����:   int TimeStats::TwoLastDaysMinute_day_of_year
   public: CSmartField      <OD_TimeStats, int        >    m_TwoLastDaysMinute_day_of_year;
// ����:   int TimeStats::LastAccessTime
   public: CSmartField      <OD_TimeStats, int        >    m_LastAccessTime;
// ����:   int TimeStats::CacheTime
   public: CSmartField      <OD_TimeStats, int        >    m_CacheTime;
// ����:   int TimeStats::Year []
   public: CSmartFieldArray <OD_TimeStats, int        >    m_Year;
// ����:   identifier TimeStats::YearStats []
   public: CSmartFieldArray <OD_TimeStats, identifier >    m_YearStats;
// ����:   int TimeStats::TwoLastDaysMinute []
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
// ���������� �������� ���� ������ ������ "YearStats"
// 
class OC_YearStats: public OC_Object <OC_YearStats>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_YearStats  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_YearStats  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_YearStats  (const OC_YearStats& from);
// ���������� ����������� �������
   public: ~OC_YearStats ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_YearStats& operator= (const OC_YearStats& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_YearStats& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_YearStats& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_YearStats& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_YearStats& operator << (OC_YearStats& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_YearStats& operator >> (OC_YearStats& from);

// ����:   int YearStats::LastAccessTime
   public: CSmartField      <OD_YearStats, int        >    m_LastAccessTime;
// ����:   int YearStats::CacheTime
   public: CSmartField      <OD_YearStats, int        >    m_CacheTime;
// ����:   int YearStats::DayTotal []
   public: CSmartFieldArray <OD_YearStats, int        >    m_DayTotal;
// ����:   identifier YearStats::DayStats []
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
// ���������� �������� ���� ������ ������ "DayStats"
// 
class OC_DayStats: public OC_Object <OC_DayStats>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_DayStats  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_DayStats  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_DayStats  (const OC_DayStats& from);
// ���������� ����������� �������
   public: ~OC_DayStats ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_DayStats& operator= (const OC_DayStats& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_DayStats& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_DayStats& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_DayStats& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_DayStats& operator << (OC_DayStats& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_DayStats& operator >> (OC_DayStats& from);

// ����:   int DayStats::LastAccessTime
   public: CSmartField      <OD_DayStats, int        >    m_LastAccessTime;
// ����:   int DayStats::CacheTime
   public: CSmartField      <OD_DayStats, int        >    m_CacheTime;
// ����:   int DayStats::HourTotal []
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
// ���������� �������� ���� ������ ������ "Referrer"
// 
class OC_Referrer: public OC_Object <OC_Referrer>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Referrer  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Referrer  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Referrer  (const OC_Referrer& from);
// ���������� ����������� �������
   public: ~OC_Referrer ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Referrer& operator= (const OC_Referrer& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Referrer& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Referrer& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Referrer& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Referrer& operator << (OC_Referrer& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Referrer& operator >> (OC_Referrer& from);

// ����:   identifier Referrer::CRC
   public: CSmartField      <OD_Referrer, identifier >    m_CRC;
// ����:   string Referrer::Referrer
   public: CSmartField      <OD_Referrer, string     >    m_Referrer;
// ����:   int Referrer::Count
   public: CSmartField      <OD_Referrer, int        >    m_Count;
// ����:   int Referrer::LastAccessTime
   public: CSmartField      <OD_Referrer, int        >    m_LastAccessTime;
// ����:   int Referrer::CacheTime
   public: CSmartField      <OD_Referrer, int        >    m_CacheTime;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [CRC]
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
// ���������� �������� ���� ������ ������ "DailyReferrerStats"
// 
class OC_DailyReferrerStats: public OC_Object <OC_DailyReferrerStats>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_DailyReferrerStats  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_DailyReferrerStats  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_DailyReferrerStats  (const OC_DailyReferrerStats& from);
// ���������� ����������� �������
   public: ~OC_DailyReferrerStats ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_DailyReferrerStats& operator= (const OC_DailyReferrerStats& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_DailyReferrerStats& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_DailyReferrerStats& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_DailyReferrerStats& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_DailyReferrerStats& operator << (OC_DailyReferrerStats& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_DailyReferrerStats& operator >> (OC_DailyReferrerStats& from);

// ����:   identifier DailyReferrerStats::SiteID
   public: CSmartField      <OD_DailyReferrerStats, identifier >    m_SiteID;
// ����:   int DailyReferrerStats::TimeStamp
   public: CSmartField      <OD_DailyReferrerStats, int        >    m_TimeStamp;
// ����:   int DailyReferrerStats::CacheTime
   public: CSmartField      <OD_DailyReferrerStats, int        >    m_CacheTime;
// ����:   identifier DailyReferrerStats::Referrer []
   public: CSmartFieldArray <OD_DailyReferrerStats, identifier >    m_Referrer;
// ����:   int DailyReferrerStats::Count []
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
// ���������� �������� ���� ������ ������ "SearchWordsInfo"
// 
class OC_SearchWordsInfo: public OC_Object <OC_SearchWordsInfo>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_SearchWordsInfo  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_SearchWordsInfo  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_SearchWordsInfo  (const OC_SearchWordsInfo& from);
// ���������� ����������� �������
   public: ~OC_SearchWordsInfo ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SearchWordsInfo& operator= (const OC_SearchWordsInfo& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SearchWordsInfo& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_SearchWordsInfo& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_SearchWordsInfo& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_SearchWordsInfo& operator << (OC_SearchWordsInfo& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_SearchWordsInfo& operator >> (OC_SearchWordsInfo& from);

// ����:   identifier SearchWordsInfo::SiteID
   public: CSmartField      <OD_SearchWordsInfo, identifier >    m_SiteID;
// ����:   int SearchWordsInfo::CacheTime
   public: CSmartField      <OD_SearchWordsInfo, int        >    m_CacheTime;
// ����:   string SearchWordsInfo::Words []
   public: CSmartFieldArray <OD_SearchWordsInfo, string     >    m_Words;
// ����:   int SearchWordsInfo::Count []
   public: CSmartFieldArray <OD_SearchWordsInfo, int        >    m_Count;
// ����:   int SearchWordsInfo::LastAccessTime []
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
// ���������� �������� ���� ������ ������ "SuspiciousInfo"
// 
class OC_SuspiciousInfo: public OC_Object <OC_SuspiciousInfo>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_SuspiciousInfo  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_SuspiciousInfo  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_SuspiciousInfo  (const OC_SuspiciousInfo& from);
// ���������� ����������� �������
   public: ~OC_SuspiciousInfo ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SuspiciousInfo& operator= (const OC_SuspiciousInfo& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SuspiciousInfo& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_SuspiciousInfo& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_SuspiciousInfo& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_SuspiciousInfo& operator << (OC_SuspiciousInfo& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_SuspiciousInfo& operator >> (OC_SuspiciousInfo& from);

// ����:   identifier SuspiciousInfo::Site
   public: CSmartField      <OD_SuspiciousInfo, identifier >    m_Site;
// ����:   int SuspiciousInfo::Pointer
   public: CSmartField      <OD_SuspiciousInfo, int        >    m_Pointer;
// ����:   int SuspiciousInfo::CacheTime
   public: CSmartField      <OD_SuspiciousInfo, int        >    m_CacheTime;
// ����:   identifier SuspiciousInfo::Viewer []
   public: CSmartFieldArray <OD_SuspiciousInfo, identifier >    m_Viewer;
// ����:   string SuspiciousInfo::Referrer []
   public: CSmartFieldArray <OD_SuspiciousInfo, string     >    m_Referrer;
// ����:   int SuspiciousInfo::Time []
   public: CSmartFieldArray <OD_SuspiciousInfo, int        >    m_Time;
// ����:   int SuspiciousInfo::EventType []
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
// ���������� �������� ���� ������ ������ "RatingPlaceInfo"
// 
class OC_RatingPlaceInfo: public OC_Object <OC_RatingPlaceInfo>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_RatingPlaceInfo  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_RatingPlaceInfo  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_RatingPlaceInfo  (const OC_RatingPlaceInfo& from);
// ���������� ����������� �������
   public: ~OC_RatingPlaceInfo ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_RatingPlaceInfo& operator= (const OC_RatingPlaceInfo& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_RatingPlaceInfo& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_RatingPlaceInfo& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_RatingPlaceInfo& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_RatingPlaceInfo& operator << (OC_RatingPlaceInfo& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_RatingPlaceInfo& operator >> (OC_RatingPlaceInfo& from);

// ����:   identifier RatingPlaceInfo::Site
   public: CSmartField      <OD_RatingPlaceInfo, identifier >    m_Site;
// ����:   int RatingPlaceInfo::LHP_Pointer
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LHP_Pointer;
// ����:   int RatingPlaceInfo::LDP_Pointer
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LDP_Pointer;
// ����:   int RatingPlaceInfo::LDP_UpdateTime
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_LDP_UpdateTime;
// ����:   float RatingPlaceInfo::DailyPositionDiff
   public: CSmartField      <OD_RatingPlaceInfo, float      >    m_DailyPositionDiff;
// ����:   int RatingPlaceInfo::CacheTime
   public: CSmartField      <OD_RatingPlaceInfo, int        >    m_CacheTime;
// ����:   int RatingPlaceInfo::LastHourPosition []
   public: CSmartFieldArray <OD_RatingPlaceInfo, int        >    m_LastHourPosition;
// ����:   float RatingPlaceInfo::LastDailyPosition []
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
// ���������� �������� ���� ������ ������ "IPRecord"
// 
class OC_IPRecord: public OC_Object <OC_IPRecord>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_IPRecord  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_IPRecord  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_IPRecord  (const OC_IPRecord& from);
// ���������� ����������� �������
   public: ~OC_IPRecord ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_IPRecord& operator= (const OC_IPRecord& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_IPRecord& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_IPRecord& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_IPRecord& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_IPRecord& operator << (OC_IPRecord& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_IPRecord& operator >> (OC_IPRecord& from);

// ����:   int IPRecord::Count
   public: CSmartField      <OD_IPRecord, int        >    m_Count;
// ����:   string IPRecord::Mask
   public: CSmartField      <OD_IPRecord, string     >    m_Mask;
// ����:   string IPRecord::First
   public: CSmartField      <OD_IPRecord, string     >    m_First;
// ����:   string IPRecord::Last
   public: CSmartField      <OD_IPRecord, string     >    m_Last;
// ����:   bool IPRecord::Checked
   public: CSmartField      <OD_IPRecord, bool       >    m_Checked;
// ����:   int IPRecord::CacheTime
   public: CSmartField      <OD_IPRecord, int        >    m_CacheTime;
// ����:   identifier IPRecord::Hits
   public: CSmartField      <OD_IPRecord, identifier >    m_Hits;
// ����:   identifier IPRecord::Hosts
   public: CSmartField      <OD_IPRecord, identifier >    m_Hosts;
// ����:   identifier IPRecord::Visitors
   public: CSmartField      <OD_IPRecord, identifier >    m_Visitors;
// ����:   identifier IPRecord::Anonymous
   public: CSmartField      <OD_IPRecord, identifier >    m_Anonymous;
// ����:   identifier IPRecord::Suspicious
   public: CSmartField      <OD_IPRecord, identifier >    m_Suspicious;
// ����:   int IPRecord::Total_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Hits;
// ����:   int IPRecord::Total_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Hosts;
// ����:   int IPRecord::Total_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Visitors;
// ����:   int IPRecord::Total_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Anonymous;
// ����:   int IPRecord::Total_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_Total_Suspicious;
// ����:   int IPRecord::LM_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Hits;
// ����:   int IPRecord::LM_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Hosts;
// ����:   int IPRecord::LM_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Visitors;
// ����:   int IPRecord::LM_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Anonymous;
// ����:   int IPRecord::LM_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LM_Suspicious;
// ����:   int IPRecord::LW_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Hits;
// ����:   int IPRecord::LW_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Hosts;
// ����:   int IPRecord::LW_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Visitors;
// ����:   int IPRecord::LW_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Anonymous;
// ����:   int IPRecord::LW_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LW_Suspicious;
// ����:   int IPRecord::LD_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Hits;
// ����:   int IPRecord::LD_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Hosts;
// ����:   int IPRecord::LD_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Visitors;
// ����:   int IPRecord::LD_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Anonymous;
// ����:   int IPRecord::LD_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LD_Suspicious;
// ����:   int IPRecord::LH_Hits
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Hits;
// ����:   int IPRecord::LH_Hosts
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Hosts;
// ����:   int IPRecord::LH_Visitors
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Visitors;
// ����:   int IPRecord::LH_Anonymous
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Anonymous;
// ����:   int IPRecord::LH_Suspicious
   public: CSmartField      <OD_IPRecord, int        >    m_LH_Suspicious;
// ����:   identifier IPRecord::ConceptID []
   public: CSmartFieldArray <OD_IPRecord, identifier >    m_ConceptID;
// ����:   int IPRecord::ConceptNo []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_ConceptNo;
// ����:   int IPRecord::CRA_Audience []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_CRA_Audience;
// ����:   int IPRecord::CRA_Inquiry []
   public: CSmartFieldArray <OD_IPRecord, int        >    m_CRA_Inquiry;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [Checked, Mask]
   public: void SetIndex_Checked_Mask ();
// ���������� ������� ������ �� ������ ����� [Checked, -Count]
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
// ���������� �������� ���� ������ ������ "ViewerReference"
// 
class OC_ViewerReference: public OC_Object <OC_ViewerReference>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_ViewerReference  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_ViewerReference  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_ViewerReference  (const OC_ViewerReference& from);
// ���������� ����������� �������
   public: ~OC_ViewerReference ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ViewerReference& operator= (const OC_ViewerReference& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_ViewerReference& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_ViewerReference& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_ViewerReference& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_ViewerReference& operator << (OC_ViewerReference& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_ViewerReference& operator >> (OC_ViewerReference& from);

// ����:   identifier ViewerReference::ViewerID
   public: CSmartField      <OD_ViewerReference, identifier >    m_ViewerID;
// ����:   string ViewerReference::IPAddress
   public: CSmartField      <OD_ViewerReference, string     >    m_IPAddress;
// ����:   identifier ViewerReference::IPAddressHash
   public: CSmartField      <OD_ViewerReference, identifier >    m_IPAddressHash;
// ����:   int ViewerReference::CacheTime
   public: CSmartField      <OD_ViewerReference, int        >    m_CacheTime;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [IPAddressHash]
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
// ���������� �������� ���� ������ ������ "AbstractObject"
// 
class OC_AbstractObject: public OC_Object <OC_AbstractObject>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_AbstractObject  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_AbstractObject  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_AbstractObject  (const OC_AbstractObject& from);
// ���������� ����������� �������
   public: ~OC_AbstractObject ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_AbstractObject& operator= (const OC_AbstractObject& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_AbstractObject& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_AbstractObject& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_AbstractObject& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_AbstractObject& operator << (OC_AbstractObject& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_AbstractObject& operator >> (OC_AbstractObject& from);

// ����:   string AbstractObject::Type
   public: CSmartField      <OD_AbstractObject, string     >    m_Type;
// ����:   string AbstractObject::Name
   public: CSmartField      <OD_AbstractObject, string     >    m_Name;
// ����:   string AbstractObject::Header1
   public: CSmartField      <OD_AbstractObject, string     >    m_Header1;
// ����:   string AbstractObject::Header2
   public: CSmartField      <OD_AbstractObject, string     >    m_Header2;
// ����:   string AbstractObject::Header3
   public: CSmartField      <OD_AbstractObject, string     >    m_Header3;
// ����:   string AbstractObject::Body
   public: CSmartField      <OD_AbstractObject, string     >    m_Body;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [Type, Name, Header1, Header2, Header3]
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
