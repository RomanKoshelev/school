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
// ����:   identifier Viewer::TagID
   public: CSmartField      <OD_Viewer, identifier >    m_TagID;
// ����:   int Viewer::TagInt
   public: CSmartField      <OD_Viewer, int        >    m_TagInt;
// ����:   bool Viewer::TagBool
   public: CSmartField      <OD_Viewer, bool       >    m_TagBool;
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

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [IPAddressHash, Anonymous]
   public: void SetIndex_IPAddressHash_Anonymous ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Test_Load
#endif
#ifdef USES_OC_Test_Load
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_Load"
// 
class OC_Test_Load: public OC_Object <OC_Test_Load>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_Load  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_Load  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_Load  (const OC_Test_Load& from);
// ���������� ����������� �������
   public: ~OC_Test_Load ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_Load& operator= (const OC_Test_Load& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_Load& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_Load& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_Load& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_Load& operator << (OC_Test_Load& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_Load& operator >> (OC_Test_Load& from);

// ����:   int Test_Load::Field
   public: CSmartField      <OD_Test_Load, int        >    m_Field;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Field]
   public: void SetIndex_Field ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_jerom_table
#endif
#ifdef USES_OC_jerom_table
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "jerom_table"
// 
class OC_jerom_table: public OC_Object <OC_jerom_table>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_jerom_table  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_jerom_table  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_jerom_table  (const OC_jerom_table& from);
// ���������� ����������� �������
   public: ~OC_jerom_table ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_jerom_table& operator= (const OC_jerom_table& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_jerom_table& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_jerom_table& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_jerom_table& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_jerom_table& operator << (OC_jerom_table& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_jerom_table& operator >> (OC_jerom_table& from);

// ����:   int jerom_table::OperatorID
   public: CSmartField      <OD_jerom_table, int        >    m_OperatorID;
// ����:   int jerom_table::MessageDate
   public: CSmartField      <OD_jerom_table, int        >    m_MessageDate;
// ����:   string jerom_table::Message
   public: CSmartField      <OD_jerom_table, string     >    m_Message;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_tsmc_table
#endif
#ifdef USES_OC_tsmc_table
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "tsmc_table"
// 
class OC_tsmc_table: public OC_Object <OC_tsmc_table>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_tsmc_table  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_tsmc_table  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_tsmc_table  (const OC_tsmc_table& from);
// ���������� ����������� �������
   public: ~OC_tsmc_table ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_tsmc_table& operator= (const OC_tsmc_table& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_tsmc_table& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_tsmc_table& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_tsmc_table& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_tsmc_table& operator << (OC_tsmc_table& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_tsmc_table& operator >> (OC_tsmc_table& from);

// ����:   int tsmc_table::Int_Field
   public: CSmartField      <OD_tsmc_table, int        >    m_Int_Field;
// ����:   float tsmc_table::Float_Field
   public: CSmartField      <OD_tsmc_table, float      >    m_Float_Field;
// ����:   string tsmc_table::Text_Field
   public: CSmartField      <OD_tsmc_table, string     >    m_Text_Field;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Float_Field]
   public: void SetIndex_Float_Field ();
// ���������� ������� ������ �� ���� [Text_Field]
   public: void SetIndex_Text_Field ();
// ���������� ������� ������ �� ������ ����� [Int_Field, Float_Field, Text_Field]
   public: void SetIndex_Int_Field_Float_Field_Text_Field ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Test_MM
#endif
#ifdef USES_OC_Test_MM
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_MM"
// 
class OC_Test_MM: public OC_Object <OC_Test_MM>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_MM  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_MM  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_MM  (const OC_Test_MM& from);
// ���������� ����������� �������
   public: ~OC_Test_MM ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_MM& operator= (const OC_Test_MM& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_MM& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_MM& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_MM& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_MM& operator << (OC_Test_MM& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_MM& operator >> (OC_Test_MM& from);

// ����:   int Test_MM::n
   public: CSmartField      <OD_Test_MM, int        >    m_n;
// ����:   string Test_MM::s
   public: CSmartField      <OD_Test_MM, string     >    m_s;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [n, s]
   public: void SetIndex_n_s ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Test_CRC
#endif
#ifdef USES_OC_Test_CRC
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_CRC"
// 
class OC_Test_CRC: public OC_Object <OC_Test_CRC>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_CRC  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_CRC  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_CRC  (const OC_Test_CRC& from);
// ���������� ����������� �������
   public: ~OC_Test_CRC ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_CRC& operator= (const OC_Test_CRC& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_CRC& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_CRC& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_CRC& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_CRC& operator << (OC_Test_CRC& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_CRC& operator >> (OC_Test_CRC& from);

// ����:   identifier Test_CRC::CRC
   public: CSmartField      <OD_Test_CRC, identifier >    m_CRC;
// ����:   string Test_CRC::STR
   public: CSmartField      <OD_Test_CRC, string     >    m_STR;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [CRC]
   public: void SetIndex_CRC ();
// ���������� ������� ������ �� ���� [STR]
   public: void SetIndex_STR ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Test_4G
#endif
#ifdef USES_OC_Test_4G
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_4G"
// 
class OC_Test_4G: public OC_Object <OC_Test_4G>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_4G  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_4G  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_4G  (const OC_Test_4G& from);
// ���������� ����������� �������
   public: ~OC_Test_4G ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_4G& operator= (const OC_Test_4G& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_4G& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_4G& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_4G& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_4G& operator << (OC_Test_4G& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_4G& operator >> (OC_Test_4G& from);

// ����:   int Test_4G::i
   public: CSmartField      <OD_Test_4G, int        >    m_i;
// ����:   string Test_4G::s
   public: CSmartField      <OD_Test_4G, string     >    m_s;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [i]
   public: void SetIndex_i ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Test_sort
#endif
#ifdef USES_OC_Test_sort
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_sort"
// 
class OC_Test_sort: public OC_Object <OC_Test_sort>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_sort  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_sort  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_sort  (const OC_Test_sort& from);
// ���������� ����������� �������
   public: ~OC_Test_sort ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_sort& operator= (const OC_Test_sort& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_sort& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_sort& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_sort& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_sort& operator << (OC_Test_sort& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_sort& operator >> (OC_Test_sort& from);

// ����:   int Test_sort::n1
   public: CSmartField      <OD_Test_sort, int        >    m_n1;
// ����:   int Test_sort::n2
   public: CSmartField      <OD_Test_sort, int        >    m_n2;
// ����:   string Test_sort::s1
   public: CSmartField      <OD_Test_sort, string     >    m_s1;
// ����:   string Test_sort::s2
   public: CSmartField      <OD_Test_sort, string     >    m_s2;
// ����:   float Test_sort::f1
   public: CSmartField      <OD_Test_sort, float      >    m_f1;
// ����:   float Test_sort::f2
   public: CSmartField      <OD_Test_sort, float      >    m_f2;
// ����:   bool Test_sort::b1
   public: CSmartField      <OD_Test_sort, bool       >    m_b1;
// ����:   bool Test_sort::b2
   public: CSmartField      <OD_Test_sort, bool       >    m_b2;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [n1]
   public: void SetIndex_n1 ();
// ���������� ������� ������ �� ���� [-n1]
   public: void SetIndex__n1 ();
// ���������� ������� ������ �� ���� [s1]
   public: void SetIndex_s1 ();
// ���������� ������� ������ �� ���� [-s1]
   public: void SetIndex__s1 ();
// ���������� ������� ������ �� ������ ����� [n1, -f1]
   public: void SetIndex_n1__f1 ();
// ���������� ������� ������ �� ������ ����� [-f1, f2]
   public: void SetIndex__f1_f2 ();
// ���������� ������� ������ �� ������ ����� [s1, s2]
   public: void SetIndex_s1_s2 ();
// ���������� ������� ������ �� ������ ����� [-s1, s2]
   public: void SetIndex__s1_s2 ();
// ���������� ������� ������ �� ������ ����� [s1, -s2]
   public: void SetIndex_s1__s2 ();
// ���������� ������� ������ �� ������ ����� [-s1, -s2]
   public: void SetIndex__s1__s2 ();
// ���������� ������� ������ �� ������ ����� [f1, s1, n2]
   public: void SetIndex_f1_s1_n2 ();
// ���������� ������� ������ �� ������ ����� [b1, -s1, n2]
   public: void SetIndex_b1__s1_n2 ();
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
