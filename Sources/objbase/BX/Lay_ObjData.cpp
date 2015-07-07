/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjData.cpp                                           []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Data contents for database objects                        []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/

#define USES_OC_ALL

#define USES_key_arr_h
#define USES_ObjDriver_h

#include "../bcc/main.h"
#include "../bcc/OBD.h"
#include "Lay_ObjData.h"




char * className[]=
{
   "Viewer",
   "ViewerGroup",
   "User",
   "TradeStats",
   "Banner",
   "BannerProfile",
   "Page",
   "Site",
   "SiteProfile",
   "ShowEvent",
   "Registry",
   "VBN",
   "Language",
   "Concept",
   "SiteList",
   "Keyword",
   "ModeratorComment",
   "TimeStats",
   "YearStats",
   "DayStats",
   "Referrer",
   "DailyReferrerStats",
   "SearchWordsInfo",
   "SuspiciousInfo",
   "RatingPlaceInfo",
   "IPRecord",
   "ViewerReference",
   "AbstractObject"
};


// Конструктор
   OD_Viewer::OD_Viewer (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Viewer;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Reference = NA;
      d_Anonymous = true;
      d_TotalShows = 0;
      d_TotalClicks = 0;
      d_CRA_Site.Alloc (0);
      d_CRN_Site.Alloc (0);
      d_CRN_Site_Update = 0;
      d_CRA_Click.Alloc (0);
      d_CRN_Click.Alloc (0);
      d_Group = NA;
      d_TZOffset = 0;
      d_CreationTime = 0;
      d_LastVisitTime = 0;
      d_Site.Alloc (0);
      d_Site_LastHit.Alloc (0);
      d_Site_Hits.Alloc (0);
      d_Site_LastHost.Alloc (0);
      d_Site_Hosts.Alloc (0);
      d_TotalHosts = 0;
      d_Site_Votings.Alloc (0);
      d_Site_VoteDayNo.Alloc (0);
      d_CRA_Inquiry.Alloc (0);
      d_CRN_Inquiry.Alloc (0);
      d_Site_SessionLastSiteID = NA;
      d_Banner.Alloc (0);
      d_Banner_LastViewed.Alloc (0);
      d_Banner_ShowClick.Alloc (0);
      d_BannerClickTime = 0;
      d_BannerClickID = NA;
      d_BannerClickSiteID = NA;
      d_BannerClickHitCount = 0;
      d_BannerClickSessionTime = 0;
      d_ReloadNum = (float) 0.0;
      d_AveReloadTime = (float) 0.0;
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_Viewer::~OD_Viewer () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Viewer::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Reference;                   break;
         case 2: ka += d_Name;                        break;
         case 3: ka += d_Email;                       break;
         case 4: ka += d_UserAgent;                   break;
         case 5: ka += d_Anonymous;                   break;
         case 6: ka += d_TotalShows;                  break;
         case 7: ka += d_TotalClicks;                 break;
         case 8: ka += d_IPAddress;                   break;
         case 9: ka += d_Referrer;                    break;
         case 10: ka += d_IPAddressHash;               break;
         case 13: ka += d_CRN_Site_Update;             break;
         case 16: ka += d_Group;                       break;
         case 17: ka += d_TZOffset;                    break;
         case 18: ka += d_CreationTime;                break;
         case 19: ka += d_LastVisitTime;               break;
         case 25: ka += d_TotalHosts;                  break;
         case 30: ka += d_Site_SessionLastSiteID;      break;
         case 34: ka += d_BannerClickTime;             break;
         case 35: ka += d_BannerClickID;               break;
         case 36: ka += d_BannerClickSiteID;           break;
         case 37: ka += d_BannerClickHitCount;         break;
         case 38: ka += d_BannerClickSessionTime;      break;
         case 39: ka += d_ReloadNum;                   break;
         case 40: ka += d_AveReloadTime;               break;
         case 41: ka += d_TagID;                       break;
         case 42: ka += d_TagInt;                      break;
         case 43: ka += d_TagBool;                     break;
         case 47: ka += d_CacheTime;                   break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Viewer::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier Reference
      d_Reference = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Email
      size_t n_Email = (*(size_t*)(file+nOffset));  // n_Email = strlen (s_Email)+1;
      nOffset += sizeof(size_t);
      char * s_Email = new char [n_Email];
      memcpy (s_Email, (file+nOffset), n_Email);
      nOffset += n_Email;
      DECODE_STRING (n_Email, s_Email);
      d_Email = s_Email;
      delete [] s_Email;

   // string UserAgent
      size_t n_UserAgent = (*(size_t*)(file+nOffset));  // n_UserAgent = strlen (s_UserAgent)+1;
      nOffset += sizeof(size_t);
      char * s_UserAgent = new char [n_UserAgent];
      memcpy (s_UserAgent, (file+nOffset), n_UserAgent);
      nOffset += n_UserAgent;
      DECODE_STRING (n_UserAgent, s_UserAgent);
      d_UserAgent = s_UserAgent;
      delete [] s_UserAgent;

   // bool Anonymous
      d_Anonymous = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int TotalShows
      d_TotalShows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TotalClicks
      d_TotalClicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string IPAddress
      size_t n_IPAddress = (*(size_t*)(file+nOffset));  // n_IPAddress = strlen (s_IPAddress)+1;
      nOffset += sizeof(size_t);
      char * s_IPAddress = new char [n_IPAddress];
      memcpy (s_IPAddress, (file+nOffset), n_IPAddress);
      nOffset += n_IPAddress;
      DECODE_STRING (n_IPAddress, s_IPAddress);
      d_IPAddress = s_IPAddress;
      delete [] s_IPAddress;

   // string Referrer
      size_t n_Referrer = (*(size_t*)(file+nOffset));  // n_Referrer = strlen (s_Referrer)+1;
      nOffset += sizeof(size_t);
      char * s_Referrer = new char [n_Referrer];
      memcpy (s_Referrer, (file+nOffset), n_Referrer);
      nOffset += n_Referrer;
      DECODE_STRING (n_Referrer, s_Referrer);
      d_Referrer = s_Referrer;
      delete [] s_Referrer;

   // identifier IPAddressHash
      d_IPAddressHash = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CRA_Site []
      int arr_size_CRA_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Site.Alloc (arr_size_CRA_Site);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Site);

   // int CRN_Site []
      int arr_size_CRN_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Site.Alloc (arr_size_CRN_Site);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Site);

   // int CRN_Site_Update
      d_CRN_Site_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CRA_Click []
      int arr_size_CRA_Click = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Click.Alloc (arr_size_CRA_Click);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Click);

   // int CRN_Click []
      int arr_size_CRN_Click = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Click.Alloc (arr_size_CRN_Click);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Click);

   // identifier Group
      d_Group = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TZOffset
      d_TZOffset = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LastVisitTime
      d_LastVisitTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Site []
      int arr_size_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site.Alloc (arr_size_Site);
      OD_LOAD_SIMPLE_ARRAY (identifier,Site);

   // int Site_LastHit []
      int arr_size_Site_LastHit = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_LastHit.Alloc (arr_size_Site_LastHit);
      OD_LOAD_SIMPLE_ARRAY (int,Site_LastHit);

   // int Site_Hits []
      int arr_size_Site_Hits = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_Hits.Alloc (arr_size_Site_Hits);
      OD_LOAD_SIMPLE_ARRAY (int,Site_Hits);

   // int Site_LastHost []
      int arr_size_Site_LastHost = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_LastHost.Alloc (arr_size_Site_LastHost);
      OD_LOAD_SIMPLE_ARRAY (int,Site_LastHost);

   // int Site_Hosts []
      int arr_size_Site_Hosts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_Hosts.Alloc (arr_size_Site_Hosts);
      OD_LOAD_SIMPLE_ARRAY (int,Site_Hosts);

   // int TotalHosts
      d_TotalHosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // byte Site_Votings []
      int arr_size_Site_Votings = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_Votings.Alloc (arr_size_Site_Votings);
      OD_LOAD_SIMPLE_ARRAY (byte,Site_Votings);

   // byte Site_VoteDayNo []
      int arr_size_Site_VoteDayNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site_VoteDayNo.Alloc (arr_size_Site_VoteDayNo);
      OD_LOAD_SIMPLE_ARRAY (byte,Site_VoteDayNo);

   // int CRA_Inquiry []
      int arr_size_CRA_Inquiry = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Inquiry.Alloc (arr_size_CRA_Inquiry);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CRN_Inquiry []
      int arr_size_CRN_Inquiry = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Inquiry.Alloc (arr_size_CRN_Inquiry);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Inquiry);

   // identifier Site_SessionLastSiteID
      d_Site_SessionLastSiteID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Banner []
      int arr_size_Banner = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Banner.Alloc (arr_size_Banner);
      OD_LOAD_SIMPLE_ARRAY (identifier,Banner);

   // int Banner_LastViewed []
      int arr_size_Banner_LastViewed = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Banner_LastViewed.Alloc (arr_size_Banner_LastViewed);
      OD_LOAD_SIMPLE_ARRAY (int,Banner_LastViewed);

   // int Banner_ShowClick []
      int arr_size_Banner_ShowClick = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Banner_ShowClick.Alloc (arr_size_Banner_ShowClick);
      OD_LOAD_SIMPLE_ARRAY (int,Banner_ShowClick);

   // int BannerClickTime
      d_BannerClickTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier BannerClickID
      d_BannerClickID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier BannerClickSiteID
      d_BannerClickSiteID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int BannerClickHitCount
      d_BannerClickHitCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int BannerClickSessionTime
      d_BannerClickSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float ReloadNum
      d_ReloadNum = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // float AveReloadTime
      d_AveReloadTime = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Viewer::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier Reference
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Email
      n_size += sizeof (size_t);
      n_size += d_Email.length()+1;

   // string UserAgent
      n_size += sizeof (size_t);
      n_size += d_UserAgent.length()+1;

   // bool Anonymous
      n_size += sizeof (bool);

   // int TotalShows
      n_size += sizeof (int);

   // int TotalClicks
      n_size += sizeof (int);

   // string IPAddress
      n_size += sizeof (size_t);
      n_size += d_IPAddress.length()+1;

   // string Referrer
      n_size += sizeof (size_t);
      n_size += d_Referrer.length()+1;

   // identifier IPAddressHash
      n_size += sizeof (identifier);

   // int CRA_Site []
      n_size += sizeof (size_t);
      n_size += d_CRA_Site.GetSize() * sizeof(int);

   // int CRN_Site []
      n_size += sizeof (size_t);
      n_size += d_CRN_Site.GetSize() * sizeof(int);

   // int CRN_Site_Update
      n_size += sizeof (int);

   // int CRA_Click []
      n_size += sizeof (size_t);
      n_size += d_CRA_Click.GetSize() * sizeof(int);

   // int CRN_Click []
      n_size += sizeof (size_t);
      n_size += d_CRN_Click.GetSize() * sizeof(int);

   // identifier Group
      n_size += sizeof (identifier);

   // int TZOffset
      n_size += sizeof (int);

   // int CreationTime
      n_size += sizeof (int);

   // int LastVisitTime
      n_size += sizeof (int);

   // identifier Site []
      n_size += sizeof (size_t);
      n_size += d_Site.GetSize() * sizeof(identifier);

   // int Site_LastHit []
      n_size += sizeof (size_t);
      n_size += d_Site_LastHit.GetSize() * sizeof(int);

   // int Site_Hits []
      n_size += sizeof (size_t);
      n_size += d_Site_Hits.GetSize() * sizeof(int);

   // int Site_LastHost []
      n_size += sizeof (size_t);
      n_size += d_Site_LastHost.GetSize() * sizeof(int);

   // int Site_Hosts []
      n_size += sizeof (size_t);
      n_size += d_Site_Hosts.GetSize() * sizeof(int);

   // int TotalHosts
      n_size += sizeof (int);

   // byte Site_Votings []
      n_size += sizeof (size_t);
      n_size += d_Site_Votings.GetSize() * sizeof(byte);

   // byte Site_VoteDayNo []
      n_size += sizeof (size_t);
      n_size += d_Site_VoteDayNo.GetSize() * sizeof(byte);

   // int CRA_Inquiry []
      n_size += sizeof (size_t);
      n_size += d_CRA_Inquiry.GetSize() * sizeof(int);

   // int CRN_Inquiry []
      n_size += sizeof (size_t);
      n_size += d_CRN_Inquiry.GetSize() * sizeof(int);

   // identifier Site_SessionLastSiteID
      n_size += sizeof (identifier);

   // identifier Banner []
      n_size += sizeof (size_t);
      n_size += d_Banner.GetSize() * sizeof(identifier);

   // int Banner_LastViewed []
      n_size += sizeof (size_t);
      n_size += d_Banner_LastViewed.GetSize() * sizeof(int);

   // int Banner_ShowClick []
      n_size += sizeof (size_t);
      n_size += d_Banner_ShowClick.GetSize() * sizeof(int);

   // int BannerClickTime
      n_size += sizeof (int);

   // identifier BannerClickID
      n_size += sizeof (identifier);

   // identifier BannerClickSiteID
      n_size += sizeof (identifier);

   // int BannerClickHitCount
      n_size += sizeof (int);

   // int BannerClickSessionTime
      n_size += sizeof (int);

   // float ReloadNum
      n_size += sizeof (float);

   // float AveReloadTime
      n_size += sizeof (float);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Viewer::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier Reference
      (*(identifier*)(file+nOffset)) = d_Reference;
      nOffset += sizeof (identifier);

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Email
      size_t n_Email = d_Email.length()+1;
      (*(size_t*)(file+nOffset)) = n_Email;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Email.c_str(), n_Email);
      ENCODE_STRING (n_Email, (char*)(file+nOffset));
      nOffset += n_Email;

   // string UserAgent
      size_t n_UserAgent = d_UserAgent.length()+1;
      (*(size_t*)(file+nOffset)) = n_UserAgent;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_UserAgent.c_str(), n_UserAgent);
      ENCODE_STRING (n_UserAgent, (char*)(file+nOffset));
      nOffset += n_UserAgent;

   // bool Anonymous
      (*(bool*)(file+nOffset)) = d_Anonymous;
      nOffset += sizeof (bool);

   // int TotalShows
      (*(int*)(file+nOffset)) = d_TotalShows;
      nOffset += sizeof (int);

   // int TotalClicks
      (*(int*)(file+nOffset)) = d_TotalClicks;
      nOffset += sizeof (int);

   // string IPAddress
      size_t n_IPAddress = d_IPAddress.length()+1;
      (*(size_t*)(file+nOffset)) = n_IPAddress;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_IPAddress.c_str(), n_IPAddress);
      ENCODE_STRING (n_IPAddress, (char*)(file+nOffset));
      nOffset += n_IPAddress;

   // string Referrer
      size_t n_Referrer = d_Referrer.length()+1;
      (*(size_t*)(file+nOffset)) = n_Referrer;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Referrer.c_str(), n_Referrer);
      ENCODE_STRING (n_Referrer, (char*)(file+nOffset));
      nOffset += n_Referrer;

   // identifier IPAddressHash
      (*(identifier*)(file+nOffset)) = d_IPAddressHash;
      nOffset += sizeof (identifier);

   // int CRA_Site []
      (*(size_t*)(file+nOffset)) = d_CRA_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Site);

   // int CRN_Site []
      (*(size_t*)(file+nOffset)) = d_CRN_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Site);

   // int CRN_Site_Update
      (*(int*)(file+nOffset)) = d_CRN_Site_Update;
      nOffset += sizeof (int);

   // int CRA_Click []
      (*(size_t*)(file+nOffset)) = d_CRA_Click.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Click);

   // int CRN_Click []
      (*(size_t*)(file+nOffset)) = d_CRN_Click.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Click);

   // identifier Group
      (*(identifier*)(file+nOffset)) = d_Group;
      nOffset += sizeof (identifier);

   // int TZOffset
      (*(int*)(file+nOffset)) = d_TZOffset;
      nOffset += sizeof (int);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // int LastVisitTime
      (*(int*)(file+nOffset)) = d_LastVisitTime;
      nOffset += sizeof (int);

   // identifier Site []
      (*(size_t*)(file+nOffset)) = d_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Site);

   // int Site_LastHit []
      (*(size_t*)(file+nOffset)) = d_Site_LastHit.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Site_LastHit);

   // int Site_Hits []
      (*(size_t*)(file+nOffset)) = d_Site_Hits.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Site_Hits);

   // int Site_LastHost []
      (*(size_t*)(file+nOffset)) = d_Site_LastHost.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Site_LastHost);

   // int Site_Hosts []
      (*(size_t*)(file+nOffset)) = d_Site_Hosts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Site_Hosts);

   // int TotalHosts
      (*(int*)(file+nOffset)) = d_TotalHosts;
      nOffset += sizeof (int);

   // byte Site_Votings []
      (*(size_t*)(file+nOffset)) = d_Site_Votings.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,Site_Votings);

   // byte Site_VoteDayNo []
      (*(size_t*)(file+nOffset)) = d_Site_VoteDayNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,Site_VoteDayNo);

   // int CRA_Inquiry []
      (*(size_t*)(file+nOffset)) = d_CRA_Inquiry.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CRN_Inquiry []
      (*(size_t*)(file+nOffset)) = d_CRN_Inquiry.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Inquiry);

   // identifier Site_SessionLastSiteID
      (*(identifier*)(file+nOffset)) = d_Site_SessionLastSiteID;
      nOffset += sizeof (identifier);

   // identifier Banner []
      (*(size_t*)(file+nOffset)) = d_Banner.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Banner);

   // int Banner_LastViewed []
      (*(size_t*)(file+nOffset)) = d_Banner_LastViewed.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Banner_LastViewed);

   // int Banner_ShowClick []
      (*(size_t*)(file+nOffset)) = d_Banner_ShowClick.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Banner_ShowClick);

   // int BannerClickTime
      (*(int*)(file+nOffset)) = d_BannerClickTime;
      nOffset += sizeof (int);

   // identifier BannerClickID
      (*(identifier*)(file+nOffset)) = d_BannerClickID;
      nOffset += sizeof (identifier);

   // identifier BannerClickSiteID
      (*(identifier*)(file+nOffset)) = d_BannerClickSiteID;
      nOffset += sizeof (identifier);

   // int BannerClickHitCount
      (*(int*)(file+nOffset)) = d_BannerClickHitCount;
      nOffset += sizeof (int);

   // int BannerClickSessionTime
      (*(int*)(file+nOffset)) = d_BannerClickSessionTime;
      nOffset += sizeof (int);

   // float ReloadNum
      (*(float*)(file+nOffset)) = d_ReloadNum;
      nOffset += sizeof (float);

   // float AveReloadTime
      (*(float*)(file+nOffset)) = d_AveReloadTime;
      nOffset += sizeof (float);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Viewer::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Viewer], objID);
      dbg += SSS;

   // identifier Reference
      SSS.Format ("Reference = %d\n", d_Reference);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Email
      SSS.Format ("Email = '%s'\n", d_Email.c_str());
      dbg += SSS;

   // string UserAgent
      SSS.Format ("UserAgent = '%s'\n", d_UserAgent.c_str());
      dbg += SSS;

   // bool Anonymous
      SSS.Format ("Anonymous = %s\n", d_Anonymous?"true":"false");
      dbg += SSS;

   // int TotalShows
      SSS.Format ("TotalShows = %d\n", d_TotalShows);
      dbg += SSS;

   // int TotalClicks
      SSS.Format ("TotalClicks = %d\n", d_TotalClicks);
      dbg += SSS;

   // string IPAddress
      SSS.Format ("IPAddress = '%s'\n", d_IPAddress.c_str());
      dbg += SSS;

   // string Referrer
      SSS.Format ("Referrer = '%s'\n", d_Referrer.c_str());
      dbg += SSS;

   // identifier IPAddressHash
      SSS.Format ("IPAddressHash = %d\n", d_IPAddressHash);
      dbg += SSS;

   // int CRA_Site []
      SSS.Format ("CRA_Site[].size = %d:\n", d_CRA_Site.GetSize());
      dbg += SSS;
      for (int iCRA_Site=0; iCRA_Site<d_CRA_Site.GetSize(); iCRA_Site++)
      {
         SSS.Format ("   CRA_Site[%d] = %d\n", iCRA_Site, d_CRA_Site[iCRA_Site]);
         dbg += SSS;
      }

   // int CRN_Site []
      SSS.Format ("CRN_Site[].size = %d:\n", d_CRN_Site.GetSize());
      dbg += SSS;
      for (int iCRN_Site=0; iCRN_Site<d_CRN_Site.GetSize(); iCRN_Site++)
      {
         SSS.Format ("   CRN_Site[%d] = %d\n", iCRN_Site, d_CRN_Site[iCRN_Site]);
         dbg += SSS;
      }

   // int CRN_Site_Update
      SSS.Format ("CRN_Site_Update = %d\n", d_CRN_Site_Update);
      dbg += SSS;

   // int CRA_Click []
      SSS.Format ("CRA_Click[].size = %d:\n", d_CRA_Click.GetSize());
      dbg += SSS;
      for (int iCRA_Click=0; iCRA_Click<d_CRA_Click.GetSize(); iCRA_Click++)
      {
         SSS.Format ("   CRA_Click[%d] = %d\n", iCRA_Click, d_CRA_Click[iCRA_Click]);
         dbg += SSS;
      }

   // int CRN_Click []
      SSS.Format ("CRN_Click[].size = %d:\n", d_CRN_Click.GetSize());
      dbg += SSS;
      for (int iCRN_Click=0; iCRN_Click<d_CRN_Click.GetSize(); iCRN_Click++)
      {
         SSS.Format ("   CRN_Click[%d] = %d\n", iCRN_Click, d_CRN_Click[iCRN_Click]);
         dbg += SSS;
      }

   // identifier Group
      SSS.Format ("Group = %d\n", d_Group);
      dbg += SSS;

   // int TZOffset
      SSS.Format ("TZOffset = %d\n", d_TZOffset);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // int LastVisitTime
      SSS.Format ("LastVisitTime = %d\n", d_LastVisitTime);
      dbg += SSS;

   // identifier Site []
      SSS.Format ("Site[].size = %d:\n", d_Site.GetSize());
      dbg += SSS;
      for (int iSite=0; iSite<d_Site.GetSize(); iSite++)
      {
         SSS.Format ("   Site[%d] = %d\n", iSite, d_Site[iSite]);
         dbg += SSS;
      }

   // int Site_LastHit []
      SSS.Format ("Site_LastHit[].size = %d:\n", d_Site_LastHit.GetSize());
      dbg += SSS;
      for (int iSite_LastHit=0; iSite_LastHit<d_Site_LastHit.GetSize(); iSite_LastHit++)
      {
         SSS.Format ("   Site_LastHit[%d] = %d\n", iSite_LastHit, d_Site_LastHit[iSite_LastHit]);
         dbg += SSS;
      }

   // int Site_Hits []
      SSS.Format ("Site_Hits[].size = %d:\n", d_Site_Hits.GetSize());
      dbg += SSS;
      for (int iSite_Hits=0; iSite_Hits<d_Site_Hits.GetSize(); iSite_Hits++)
      {
         SSS.Format ("   Site_Hits[%d] = %d\n", iSite_Hits, d_Site_Hits[iSite_Hits]);
         dbg += SSS;
      }

   // int Site_LastHost []
      SSS.Format ("Site_LastHost[].size = %d:\n", d_Site_LastHost.GetSize());
      dbg += SSS;
      for (int iSite_LastHost=0; iSite_LastHost<d_Site_LastHost.GetSize(); iSite_LastHost++)
      {
         SSS.Format ("   Site_LastHost[%d] = %d\n", iSite_LastHost, d_Site_LastHost[iSite_LastHost]);
         dbg += SSS;
      }

   // int Site_Hosts []
      SSS.Format ("Site_Hosts[].size = %d:\n", d_Site_Hosts.GetSize());
      dbg += SSS;
      for (int iSite_Hosts=0; iSite_Hosts<d_Site_Hosts.GetSize(); iSite_Hosts++)
      {
         SSS.Format ("   Site_Hosts[%d] = %d\n", iSite_Hosts, d_Site_Hosts[iSite_Hosts]);
         dbg += SSS;
      }

   // int TotalHosts
      SSS.Format ("TotalHosts = %d\n", d_TotalHosts);
      dbg += SSS;

   // byte Site_Votings []
      SSS.Format ("Site_Votings[].size = %d:\n", d_Site_Votings.GetSize());
      dbg += SSS;
      for (int iSite_Votings=0; iSite_Votings<d_Site_Votings.GetSize(); iSite_Votings++)
      {
         SSS.Format ("   Site_Votings[%d] = %d\n", iSite_Votings, d_Site_Votings[iSite_Votings]);
         dbg += SSS;
      }

   // byte Site_VoteDayNo []
      SSS.Format ("Site_VoteDayNo[].size = %d:\n", d_Site_VoteDayNo.GetSize());
      dbg += SSS;
      for (int iSite_VoteDayNo=0; iSite_VoteDayNo<d_Site_VoteDayNo.GetSize(); iSite_VoteDayNo++)
      {
         SSS.Format ("   Site_VoteDayNo[%d] = %d\n", iSite_VoteDayNo, d_Site_VoteDayNo[iSite_VoteDayNo]);
         dbg += SSS;
      }

   // int CRA_Inquiry []
      SSS.Format ("CRA_Inquiry[].size = %d:\n", d_CRA_Inquiry.GetSize());
      dbg += SSS;
      for (int iCRA_Inquiry=0; iCRA_Inquiry<d_CRA_Inquiry.GetSize(); iCRA_Inquiry++)
      {
         SSS.Format ("   CRA_Inquiry[%d] = %d\n", iCRA_Inquiry, d_CRA_Inquiry[iCRA_Inquiry]);
         dbg += SSS;
      }

   // int CRN_Inquiry []
      SSS.Format ("CRN_Inquiry[].size = %d:\n", d_CRN_Inquiry.GetSize());
      dbg += SSS;
      for (int iCRN_Inquiry=0; iCRN_Inquiry<d_CRN_Inquiry.GetSize(); iCRN_Inquiry++)
      {
         SSS.Format ("   CRN_Inquiry[%d] = %d\n", iCRN_Inquiry, d_CRN_Inquiry[iCRN_Inquiry]);
         dbg += SSS;
      }

   // identifier Site_SessionLastSiteID
      SSS.Format ("Site_SessionLastSiteID = %d\n", d_Site_SessionLastSiteID);
      dbg += SSS;

   // identifier Banner []
      SSS.Format ("Banner[].size = %d:\n", d_Banner.GetSize());
      dbg += SSS;
      for (int iBanner=0; iBanner<d_Banner.GetSize(); iBanner++)
      {
         SSS.Format ("   Banner[%d] = %d\n", iBanner, d_Banner[iBanner]);
         dbg += SSS;
      }

   // int Banner_LastViewed []
      SSS.Format ("Banner_LastViewed[].size = %d:\n", d_Banner_LastViewed.GetSize());
      dbg += SSS;
      for (int iBanner_LastViewed=0; iBanner_LastViewed<d_Banner_LastViewed.GetSize(); iBanner_LastViewed++)
      {
         SSS.Format ("   Banner_LastViewed[%d] = %d\n", iBanner_LastViewed, d_Banner_LastViewed[iBanner_LastViewed]);
         dbg += SSS;
      }

   // int Banner_ShowClick []
      SSS.Format ("Banner_ShowClick[].size = %d:\n", d_Banner_ShowClick.GetSize());
      dbg += SSS;
      for (int iBanner_ShowClick=0; iBanner_ShowClick<d_Banner_ShowClick.GetSize(); iBanner_ShowClick++)
      {
         SSS.Format ("   Banner_ShowClick[%d] = %d\n", iBanner_ShowClick, d_Banner_ShowClick[iBanner_ShowClick]);
         dbg += SSS;
      }

   // int BannerClickTime
      SSS.Format ("BannerClickTime = %d\n", d_BannerClickTime);
      dbg += SSS;

   // identifier BannerClickID
      SSS.Format ("BannerClickID = %d\n", d_BannerClickID);
      dbg += SSS;

   // identifier BannerClickSiteID
      SSS.Format ("BannerClickSiteID = %d\n", d_BannerClickSiteID);
      dbg += SSS;

   // int BannerClickHitCount
      SSS.Format ("BannerClickHitCount = %d\n", d_BannerClickHitCount);
      dbg += SSS;

   // int BannerClickSessionTime
      SSS.Format ("BannerClickSessionTime = %d\n", d_BannerClickSessionTime);
      dbg += SSS;

   // float ReloadNum
      SSS.Format ("ReloadNum = %f\n", d_ReloadNum);
      dbg += SSS;

   // float AveReloadTime
      SSS.Format ("AveReloadTime = %f\n", d_AveReloadTime);
      dbg += SSS;

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_ViewerGroup::OD_ViewerGroup (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_ViewerGroup;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_ConceptStats.Alloc (0);
      d_Viewer.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_ViewerGroup::~OD_ViewerGroup () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_ViewerGroup::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 3: ka += d_TagID;          break;
         case 4: ka += d_TagInt;         break;
         case 5: ka += d_TagBool;        break;
         case 9: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_ViewerGroup::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int ConceptStats []
      int arr_size_ConceptStats = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptStats.Alloc (arr_size_ConceptStats);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptStats);

   // identifier Viewer []
      int arr_size_Viewer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Viewer.Alloc (arr_size_Viewer);
      OD_LOAD_SIMPLE_ARRAY (identifier,Viewer);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_ViewerGroup::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int ConceptStats []
      n_size += sizeof (size_t);
      n_size += d_ConceptStats.GetSize() * sizeof(int);

   // identifier Viewer []
      n_size += sizeof (size_t);
      n_size += d_Viewer.GetSize() * sizeof(identifier);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_ViewerGroup::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int ConceptStats []
      (*(size_t*)(file+nOffset)) = d_ConceptStats.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptStats);

   // identifier Viewer []
      (*(size_t*)(file+nOffset)) = d_Viewer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Viewer);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_ViewerGroup::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_ViewerGroup], objID);
      dbg += SSS;

   // int ConceptStats []
      SSS.Format ("ConceptStats[].size = %d:\n", d_ConceptStats.GetSize());
      dbg += SSS;
      for (int iConceptStats=0; iConceptStats<d_ConceptStats.GetSize(); iConceptStats++)
      {
         SSS.Format ("   ConceptStats[%d] = %d\n", iConceptStats, d_ConceptStats[iConceptStats]);
         dbg += SSS;
      }

   // identifier Viewer []
      SSS.Format ("Viewer[].size = %d:\n", d_Viewer.GetSize());
      dbg += SSS;
      for (int iViewer=0; iViewer<d_Viewer.GetSize(); iViewer++)
      {
         SSS.Format ("   Viewer[%d] = %d\n", iViewer, d_Viewer[iViewer]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_User::OD_User (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_User;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_ForgetPassword = false;
      d_InterfaceLanguage = NA;
      d_InterfaceType = false;
      d_CreationTime = 0;
      d_VBN = 255;
      d_ba_Concept.Alloc (0);
      d_eba_Concept.Alloc (0);
      d_TZOffset = 0;
      d_NotifyFreq = 0;
      d_NotifyHTML = false;
      d_NotifyDepth = 0;
      d_Site.Alloc (0);
      d_SiteProfile.Alloc (0);
      d_Banner.Alloc (0);
      d_BannerProfile.Alloc (0);
      d_ShowsLeft = (float) 10;
      d_ClicksLeft = (float) 10;
      d_TradeStats = NA;
      d_Allowed = false;
      d_ObjectState = 1;
      d_ba_ModeratorComment.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_User::~OD_User () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_User::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Login;                  break;
         case 2: ka += d_Password;               break;
         case 3: ka += d_ForgetPassword;         break;
         case 4: ka += d_FullName;               break;
         case 5: ka += d_InterfaceLanguage;      break;
         case 6: ka += d_InterfaceType;          break;
         case 7: ka += d_CreationTime;           break;
         case 8: ka += d_VBN;                    break;
         case 11: ka += d_Email;                  break;
         case 12: ka += d_Phone;                  break;
         case 13: ka += d_Fax;                    break;
         case 14: ka += d_Address;                break;
         case 15: ka += d_URL;                    break;
         case 16: ka += d_Comment;                break;
         case 17: ka += d_TZOffset;               break;
         case 18: ka += d_NotifyFreq;             break;
         case 19: ka += d_NotifyHTML;             break;
         case 20: ka += d_NotifyDepth;            break;
         case 25: ka += d_ShowsLeft;              break;
         case 26: ka += d_ClicksLeft;             break;
         case 27: ka += d_TradeStats;             break;
         case 28: ka += d_Allowed;                break;
         case 29: ka += d_ObjectState;            break;
         case 31: ka += d_TagID;                  break;
         case 32: ka += d_TagInt;                 break;
         case 33: ka += d_TagBool;                break;
         case 37: ka += d_CacheTime;              break;
      }
   }


// Загрузка объекта с диска
   size_t OD_User::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Login
      size_t n_Login = (*(size_t*)(file+nOffset));  // n_Login = strlen (s_Login)+1;
      nOffset += sizeof(size_t);
      char * s_Login = new char [n_Login];
      memcpy (s_Login, (file+nOffset), n_Login);
      nOffset += n_Login;
      DECODE_STRING (n_Login, s_Login);
      d_Login = s_Login;
      delete [] s_Login;

   // string Password
      size_t n_Password = (*(size_t*)(file+nOffset));  // n_Password = strlen (s_Password)+1;
      nOffset += sizeof(size_t);
      char * s_Password = new char [n_Password];
      memcpy (s_Password, (file+nOffset), n_Password);
      nOffset += n_Password;
      DECODE_STRING (n_Password, s_Password);
      d_Password = s_Password;
      delete [] s_Password;

   // bool ForgetPassword
      d_ForgetPassword = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // string FullName
      size_t n_FullName = (*(size_t*)(file+nOffset));  // n_FullName = strlen (s_FullName)+1;
      nOffset += sizeof(size_t);
      char * s_FullName = new char [n_FullName];
      memcpy (s_FullName, (file+nOffset), n_FullName);
      nOffset += n_FullName;
      DECODE_STRING (n_FullName, s_FullName);
      d_FullName = s_FullName;
      delete [] s_FullName;

   // identifier InterfaceLanguage
      d_InterfaceLanguage = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool InterfaceType
      d_InterfaceType = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // byte VBN
      d_VBN = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_Concept []
      int arr_size_ba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Concept.Alloc (arr_size_ba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      int arr_size_eba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_Concept.Alloc (arr_size_eba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_Concept);

   // string Email
      size_t n_Email = (*(size_t*)(file+nOffset));  // n_Email = strlen (s_Email)+1;
      nOffset += sizeof(size_t);
      char * s_Email = new char [n_Email];
      memcpy (s_Email, (file+nOffset), n_Email);
      nOffset += n_Email;
      DECODE_STRING (n_Email, s_Email);
      d_Email = s_Email;
      delete [] s_Email;

   // string Phone
      size_t n_Phone = (*(size_t*)(file+nOffset));  // n_Phone = strlen (s_Phone)+1;
      nOffset += sizeof(size_t);
      char * s_Phone = new char [n_Phone];
      memcpy (s_Phone, (file+nOffset), n_Phone);
      nOffset += n_Phone;
      DECODE_STRING (n_Phone, s_Phone);
      d_Phone = s_Phone;
      delete [] s_Phone;

   // string Fax
      size_t n_Fax = (*(size_t*)(file+nOffset));  // n_Fax = strlen (s_Fax)+1;
      nOffset += sizeof(size_t);
      char * s_Fax = new char [n_Fax];
      memcpy (s_Fax, (file+nOffset), n_Fax);
      nOffset += n_Fax;
      DECODE_STRING (n_Fax, s_Fax);
      d_Fax = s_Fax;
      delete [] s_Fax;

   // string Address
      size_t n_Address = (*(size_t*)(file+nOffset));  // n_Address = strlen (s_Address)+1;
      nOffset += sizeof(size_t);
      char * s_Address = new char [n_Address];
      memcpy (s_Address, (file+nOffset), n_Address);
      nOffset += n_Address;
      DECODE_STRING (n_Address, s_Address);
      d_Address = s_Address;
      delete [] s_Address;

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL];
      memcpy (s_URL, (file+nOffset), n_URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // string Comment
      size_t n_Comment = (*(size_t*)(file+nOffset));  // n_Comment = strlen (s_Comment)+1;
      nOffset += sizeof(size_t);
      char * s_Comment = new char [n_Comment];
      memcpy (s_Comment, (file+nOffset), n_Comment);
      nOffset += n_Comment;
      DECODE_STRING (n_Comment, s_Comment);
      d_Comment = s_Comment;
      delete [] s_Comment;

   // int TZOffset
      d_TZOffset = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int NotifyFreq
      d_NotifyFreq = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool NotifyHTML
      d_NotifyHTML = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int NotifyDepth
      d_NotifyDepth = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Site []
      int arr_size_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site.Alloc (arr_size_Site);
      OD_LOAD_SIMPLE_ARRAY (identifier,Site);

   // identifier SiteProfile []
      int arr_size_SiteProfile = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteProfile.Alloc (arr_size_SiteProfile);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteProfile);

   // identifier Banner []
      int arr_size_Banner = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Banner.Alloc (arr_size_Banner);
      OD_LOAD_SIMPLE_ARRAY (identifier,Banner);

   // identifier BannerProfile []
      int arr_size_BannerProfile = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BannerProfile.Alloc (arr_size_BannerProfile);
      OD_LOAD_SIMPLE_ARRAY (identifier,BannerProfile);

   // float ShowsLeft
      d_ShowsLeft = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // float ClicksLeft
      d_ClicksLeft = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // identifier TradeStats
      d_TradeStats = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool Allowed
      d_Allowed = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ObjectState
      d_ObjectState = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_ModeratorComment []
      int arr_size_ba_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ModeratorComment.Alloc (arr_size_ba_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_User::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Login
      n_size += sizeof (size_t);
      n_size += d_Login.length()+1;

   // string Password
      n_size += sizeof (size_t);
      n_size += d_Password.length()+1;

   // bool ForgetPassword
      n_size += sizeof (bool);

   // string FullName
      n_size += sizeof (size_t);
      n_size += d_FullName.length()+1;

   // identifier InterfaceLanguage
      n_size += sizeof (identifier);

   // bool InterfaceType
      n_size += sizeof (bool);

   // int CreationTime
      n_size += sizeof (int);

   // byte VBN
      n_size += sizeof (byte);

   // byte ba_Concept []
      n_size += sizeof (size_t);
      n_size += d_ba_Concept.GetSize() * sizeof(byte);

   // byte eba_Concept []
      n_size += sizeof (size_t);
      n_size += d_eba_Concept.GetSize() * sizeof(byte);

   // string Email
      n_size += sizeof (size_t);
      n_size += d_Email.length()+1;

   // string Phone
      n_size += sizeof (size_t);
      n_size += d_Phone.length()+1;

   // string Fax
      n_size += sizeof (size_t);
      n_size += d_Fax.length()+1;

   // string Address
      n_size += sizeof (size_t);
      n_size += d_Address.length()+1;

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // string Comment
      n_size += sizeof (size_t);
      n_size += d_Comment.length()+1;

   // int TZOffset
      n_size += sizeof (int);

   // int NotifyFreq
      n_size += sizeof (int);

   // bool NotifyHTML
      n_size += sizeof (bool);

   // int NotifyDepth
      n_size += sizeof (int);

   // identifier Site []
      n_size += sizeof (size_t);
      n_size += d_Site.GetSize() * sizeof(identifier);

   // identifier SiteProfile []
      n_size += sizeof (size_t);
      n_size += d_SiteProfile.GetSize() * sizeof(identifier);

   // identifier Banner []
      n_size += sizeof (size_t);
      n_size += d_Banner.GetSize() * sizeof(identifier);

   // identifier BannerProfile []
      n_size += sizeof (size_t);
      n_size += d_BannerProfile.GetSize() * sizeof(identifier);

   // float ShowsLeft
      n_size += sizeof (float);

   // float ClicksLeft
      n_size += sizeof (float);

   // identifier TradeStats
      n_size += sizeof (identifier);

   // bool Allowed
      n_size += sizeof (bool);

   // byte ObjectState
      n_size += sizeof (byte);

   // byte ba_ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ba_ModeratorComment.GetSize() * sizeof(byte);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_User::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Login
      size_t n_Login = d_Login.length()+1;
      (*(size_t*)(file+nOffset)) = n_Login;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Login.c_str(), n_Login);
      ENCODE_STRING (n_Login, (char*)(file+nOffset));
      nOffset += n_Login;

   // string Password
      size_t n_Password = d_Password.length()+1;
      (*(size_t*)(file+nOffset)) = n_Password;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Password.c_str(), n_Password);
      ENCODE_STRING (n_Password, (char*)(file+nOffset));
      nOffset += n_Password;

   // bool ForgetPassword
      (*(bool*)(file+nOffset)) = d_ForgetPassword;
      nOffset += sizeof (bool);

   // string FullName
      size_t n_FullName = d_FullName.length()+1;
      (*(size_t*)(file+nOffset)) = n_FullName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_FullName.c_str(), n_FullName);
      ENCODE_STRING (n_FullName, (char*)(file+nOffset));
      nOffset += n_FullName;

   // identifier InterfaceLanguage
      (*(identifier*)(file+nOffset)) = d_InterfaceLanguage;
      nOffset += sizeof (identifier);

   // bool InterfaceType
      (*(bool*)(file+nOffset)) = d_InterfaceType;
      nOffset += sizeof (bool);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // byte VBN
      (*(byte*)(file+nOffset)) = d_VBN;
      nOffset += sizeof (byte);

   // byte ba_Concept []
      (*(size_t*)(file+nOffset)) = d_ba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      (*(size_t*)(file+nOffset)) = d_eba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_Concept);

   // string Email
      size_t n_Email = d_Email.length()+1;
      (*(size_t*)(file+nOffset)) = n_Email;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Email.c_str(), n_Email);
      ENCODE_STRING (n_Email, (char*)(file+nOffset));
      nOffset += n_Email;

   // string Phone
      size_t n_Phone = d_Phone.length()+1;
      (*(size_t*)(file+nOffset)) = n_Phone;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Phone.c_str(), n_Phone);
      ENCODE_STRING (n_Phone, (char*)(file+nOffset));
      nOffset += n_Phone;

   // string Fax
      size_t n_Fax = d_Fax.length()+1;
      (*(size_t*)(file+nOffset)) = n_Fax;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Fax.c_str(), n_Fax);
      ENCODE_STRING (n_Fax, (char*)(file+nOffset));
      nOffset += n_Fax;

   // string Address
      size_t n_Address = d_Address.length()+1;
      (*(size_t*)(file+nOffset)) = n_Address;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Address.c_str(), n_Address);
      ENCODE_STRING (n_Address, (char*)(file+nOffset));
      nOffset += n_Address;

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // string Comment
      size_t n_Comment = d_Comment.length()+1;
      (*(size_t*)(file+nOffset)) = n_Comment;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Comment.c_str(), n_Comment);
      ENCODE_STRING (n_Comment, (char*)(file+nOffset));
      nOffset += n_Comment;

   // int TZOffset
      (*(int*)(file+nOffset)) = d_TZOffset;
      nOffset += sizeof (int);

   // int NotifyFreq
      (*(int*)(file+nOffset)) = d_NotifyFreq;
      nOffset += sizeof (int);

   // bool NotifyHTML
      (*(bool*)(file+nOffset)) = d_NotifyHTML;
      nOffset += sizeof (bool);

   // int NotifyDepth
      (*(int*)(file+nOffset)) = d_NotifyDepth;
      nOffset += sizeof (int);

   // identifier Site []
      (*(size_t*)(file+nOffset)) = d_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Site);

   // identifier SiteProfile []
      (*(size_t*)(file+nOffset)) = d_SiteProfile.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteProfile);

   // identifier Banner []
      (*(size_t*)(file+nOffset)) = d_Banner.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Banner);

   // identifier BannerProfile []
      (*(size_t*)(file+nOffset)) = d_BannerProfile.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,BannerProfile);

   // float ShowsLeft
      (*(float*)(file+nOffset)) = d_ShowsLeft;
      nOffset += sizeof (float);

   // float ClicksLeft
      (*(float*)(file+nOffset)) = d_ClicksLeft;
      nOffset += sizeof (float);

   // identifier TradeStats
      (*(identifier*)(file+nOffset)) = d_TradeStats;
      nOffset += sizeof (identifier);

   // bool Allowed
      (*(bool*)(file+nOffset)) = d_Allowed;
      nOffset += sizeof (bool);

   // byte ObjectState
      (*(byte*)(file+nOffset)) = d_ObjectState;
      nOffset += sizeof (byte);

   // byte ba_ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ba_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_User::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_User], objID);
      dbg += SSS;

   // string Login
      SSS.Format ("Login = '%s'\n", d_Login.c_str());
      dbg += SSS;

   // string Password
      SSS.Format ("Password = '%s'\n", d_Password.c_str());
      dbg += SSS;

   // bool ForgetPassword
      SSS.Format ("ForgetPassword = %s\n", d_ForgetPassword?"true":"false");
      dbg += SSS;

   // string FullName
      SSS.Format ("FullName = '%s'\n", d_FullName.c_str());
      dbg += SSS;

   // identifier InterfaceLanguage
      SSS.Format ("InterfaceLanguage = %d\n", d_InterfaceLanguage);
      dbg += SSS;

   // bool InterfaceType
      SSS.Format ("InterfaceType = %s\n", d_InterfaceType?"true":"false");
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // byte VBN
      SSS.Format ("VBN = %d\n", d_VBN);
      dbg += SSS;

   // byte ba_Concept []
      SSS.Format ("ba_Concept[].size = %d:\n", d_ba_Concept.GetSize());
      dbg += SSS;
      for (int iba_Concept=0; iba_Concept<d_ba_Concept.GetSize(); iba_Concept++)
      {
         SSS.Format ("   ba_Concept[%d] = %d\n", iba_Concept, d_ba_Concept[iba_Concept]);
         dbg += SSS;
      }

   // byte eba_Concept []
      SSS.Format ("eba_Concept[].size = %d:\n", d_eba_Concept.GetSize());
      dbg += SSS;
      for (int ieba_Concept=0; ieba_Concept<d_eba_Concept.GetSize(); ieba_Concept++)
      {
         SSS.Format ("   eba_Concept[%d] = %d\n", ieba_Concept, d_eba_Concept[ieba_Concept]);
         dbg += SSS;
      }

   // string Email
      SSS.Format ("Email = '%s'\n", d_Email.c_str());
      dbg += SSS;

   // string Phone
      SSS.Format ("Phone = '%s'\n", d_Phone.c_str());
      dbg += SSS;

   // string Fax
      SSS.Format ("Fax = '%s'\n", d_Fax.c_str());
      dbg += SSS;

   // string Address
      SSS.Format ("Address = '%s'\n", d_Address.c_str());
      dbg += SSS;

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // string Comment
      SSS.Format ("Comment = '%s'\n", d_Comment.c_str());
      dbg += SSS;

   // int TZOffset
      SSS.Format ("TZOffset = %d\n", d_TZOffset);
      dbg += SSS;

   // int NotifyFreq
      SSS.Format ("NotifyFreq = %d\n", d_NotifyFreq);
      dbg += SSS;

   // bool NotifyHTML
      SSS.Format ("NotifyHTML = %s\n", d_NotifyHTML?"true":"false");
      dbg += SSS;

   // int NotifyDepth
      SSS.Format ("NotifyDepth = %d\n", d_NotifyDepth);
      dbg += SSS;

   // identifier Site []
      SSS.Format ("Site[].size = %d:\n", d_Site.GetSize());
      dbg += SSS;
      for (int iSite=0; iSite<d_Site.GetSize(); iSite++)
      {
         SSS.Format ("   Site[%d] = %d\n", iSite, d_Site[iSite]);
         dbg += SSS;
      }

   // identifier SiteProfile []
      SSS.Format ("SiteProfile[].size = %d:\n", d_SiteProfile.GetSize());
      dbg += SSS;
      for (int iSiteProfile=0; iSiteProfile<d_SiteProfile.GetSize(); iSiteProfile++)
      {
         SSS.Format ("   SiteProfile[%d] = %d\n", iSiteProfile, d_SiteProfile[iSiteProfile]);
         dbg += SSS;
      }

   // identifier Banner []
      SSS.Format ("Banner[].size = %d:\n", d_Banner.GetSize());
      dbg += SSS;
      for (int iBanner=0; iBanner<d_Banner.GetSize(); iBanner++)
      {
         SSS.Format ("   Banner[%d] = %d\n", iBanner, d_Banner[iBanner]);
         dbg += SSS;
      }

   // identifier BannerProfile []
      SSS.Format ("BannerProfile[].size = %d:\n", d_BannerProfile.GetSize());
      dbg += SSS;
      for (int iBannerProfile=0; iBannerProfile<d_BannerProfile.GetSize(); iBannerProfile++)
      {
         SSS.Format ("   BannerProfile[%d] = %d\n", iBannerProfile, d_BannerProfile[iBannerProfile]);
         dbg += SSS;
      }

   // float ShowsLeft
      SSS.Format ("ShowsLeft = %f\n", d_ShowsLeft);
      dbg += SSS;

   // float ClicksLeft
      SSS.Format ("ClicksLeft = %f\n", d_ClicksLeft);
      dbg += SSS;

   // identifier TradeStats
      SSS.Format ("TradeStats = %d\n", d_TradeStats);
      dbg += SSS;

   // bool Allowed
      SSS.Format ("Allowed = %s\n", d_Allowed?"true":"false");
      dbg += SSS;

   // byte ObjectState
      SSS.Format ("ObjectState = %d\n", d_ObjectState);
      dbg += SSS;

   // byte ba_ModeratorComment []
      SSS.Format ("ba_ModeratorComment[].size = %d:\n", d_ba_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iba_ModeratorComment=0; iba_ModeratorComment<d_ba_ModeratorComment.GetSize(); iba_ModeratorComment++)
      {
         SSS.Format ("   ba_ModeratorComment[%d] = %d\n", iba_ModeratorComment, d_ba_ModeratorComment[iba_ModeratorComment]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_TradeStats::OD_TradeStats (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_TradeStats;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_SoldShowDates.Alloc (0);
      d_SoldShowAmounts.Alloc (0);
      d_SoldShowBuyer.Alloc (0);
      d_BoughtShowDates.Alloc (0);
      d_BoughtShowAmounts.Alloc (0);
      d_BoughtShowSeller.Alloc (0);
      d_SoldClickDates.Alloc (0);
      d_SoldClickAmounts.Alloc (0);
      d_SoldClickBuyer.Alloc (0);
      d_BoughtClickDates.Alloc (0);
      d_BoughtClickAmounts.Alloc (0);
      d_BoughtClickSeller.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_TradeStats::~OD_TradeStats () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_TradeStats::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 13: ka += d_TagID;          break;
         case 14: ka += d_TagInt;         break;
         case 15: ka += d_TagBool;        break;
         case 19: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_TradeStats::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int SoldShowDates []
      int arr_size_SoldShowDates = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldShowDates.Alloc (arr_size_SoldShowDates);
      OD_LOAD_SIMPLE_ARRAY (int,SoldShowDates);

   // int SoldShowAmounts []
      int arr_size_SoldShowAmounts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldShowAmounts.Alloc (arr_size_SoldShowAmounts);
      OD_LOAD_SIMPLE_ARRAY (int,SoldShowAmounts);

   // string SoldShowBuyer []
      int arr_size_SoldShowBuyer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldShowBuyer.Alloc (arr_size_SoldShowBuyer);
      for (int iSoldShowBuyer=0; iSoldShowBuyer<(int)arr_size_SoldShowBuyer; iSoldShowBuyer++)
      {
         string tmp_SoldShowBuyer;
         size_t n_SoldShowBuyer = (*(size_t*)(file+nOffset));  // n_SoldShowBuyer = strlen (s_SoldShowBuyer)+1;
         nOffset += sizeof(size_t);
         char * s_SoldShowBuyer = new char [n_SoldShowBuyer];
         memcpy (s_SoldShowBuyer, (file+nOffset), n_SoldShowBuyer);
         nOffset += n_SoldShowBuyer;
         DECODE_STRING (n_SoldShowBuyer, s_SoldShowBuyer);
         tmp_SoldShowBuyer = s_SoldShowBuyer;
         delete [] s_SoldShowBuyer;

         d_SoldShowBuyer[iSoldShowBuyer] = tmp_SoldShowBuyer;
      }

   // int BoughtShowDates []
      int arr_size_BoughtShowDates = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtShowDates.Alloc (arr_size_BoughtShowDates);
      OD_LOAD_SIMPLE_ARRAY (int,BoughtShowDates);

   // int BoughtShowAmounts []
      int arr_size_BoughtShowAmounts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtShowAmounts.Alloc (arr_size_BoughtShowAmounts);
      OD_LOAD_SIMPLE_ARRAY (int,BoughtShowAmounts);

   // string BoughtShowSeller []
      int arr_size_BoughtShowSeller = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtShowSeller.Alloc (arr_size_BoughtShowSeller);
      for (int iBoughtShowSeller=0; iBoughtShowSeller<(int)arr_size_BoughtShowSeller; iBoughtShowSeller++)
      {
         string tmp_BoughtShowSeller;
         size_t n_BoughtShowSeller = (*(size_t*)(file+nOffset));  // n_BoughtShowSeller = strlen (s_BoughtShowSeller)+1;
         nOffset += sizeof(size_t);
         char * s_BoughtShowSeller = new char [n_BoughtShowSeller];
         memcpy (s_BoughtShowSeller, (file+nOffset), n_BoughtShowSeller);
         nOffset += n_BoughtShowSeller;
         DECODE_STRING (n_BoughtShowSeller, s_BoughtShowSeller);
         tmp_BoughtShowSeller = s_BoughtShowSeller;
         delete [] s_BoughtShowSeller;

         d_BoughtShowSeller[iBoughtShowSeller] = tmp_BoughtShowSeller;
      }

   // int SoldClickDates []
      int arr_size_SoldClickDates = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldClickDates.Alloc (arr_size_SoldClickDates);
      OD_LOAD_SIMPLE_ARRAY (int,SoldClickDates);

   // int SoldClickAmounts []
      int arr_size_SoldClickAmounts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldClickAmounts.Alloc (arr_size_SoldClickAmounts);
      OD_LOAD_SIMPLE_ARRAY (int,SoldClickAmounts);

   // string SoldClickBuyer []
      int arr_size_SoldClickBuyer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SoldClickBuyer.Alloc (arr_size_SoldClickBuyer);
      for (int iSoldClickBuyer=0; iSoldClickBuyer<(int)arr_size_SoldClickBuyer; iSoldClickBuyer++)
      {
         string tmp_SoldClickBuyer;
         size_t n_SoldClickBuyer = (*(size_t*)(file+nOffset));  // n_SoldClickBuyer = strlen (s_SoldClickBuyer)+1;
         nOffset += sizeof(size_t);
         char * s_SoldClickBuyer = new char [n_SoldClickBuyer];
         memcpy (s_SoldClickBuyer, (file+nOffset), n_SoldClickBuyer);
         nOffset += n_SoldClickBuyer;
         DECODE_STRING (n_SoldClickBuyer, s_SoldClickBuyer);
         tmp_SoldClickBuyer = s_SoldClickBuyer;
         delete [] s_SoldClickBuyer;

         d_SoldClickBuyer[iSoldClickBuyer] = tmp_SoldClickBuyer;
      }

   // int BoughtClickDates []
      int arr_size_BoughtClickDates = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtClickDates.Alloc (arr_size_BoughtClickDates);
      OD_LOAD_SIMPLE_ARRAY (int,BoughtClickDates);

   // int BoughtClickAmounts []
      int arr_size_BoughtClickAmounts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtClickAmounts.Alloc (arr_size_BoughtClickAmounts);
      OD_LOAD_SIMPLE_ARRAY (int,BoughtClickAmounts);

   // string BoughtClickSeller []
      int arr_size_BoughtClickSeller = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BoughtClickSeller.Alloc (arr_size_BoughtClickSeller);
      for (int iBoughtClickSeller=0; iBoughtClickSeller<(int)arr_size_BoughtClickSeller; iBoughtClickSeller++)
      {
         string tmp_BoughtClickSeller;
         size_t n_BoughtClickSeller = (*(size_t*)(file+nOffset));  // n_BoughtClickSeller = strlen (s_BoughtClickSeller)+1;
         nOffset += sizeof(size_t);
         char * s_BoughtClickSeller = new char [n_BoughtClickSeller];
         memcpy (s_BoughtClickSeller, (file+nOffset), n_BoughtClickSeller);
         nOffset += n_BoughtClickSeller;
         DECODE_STRING (n_BoughtClickSeller, s_BoughtClickSeller);
         tmp_BoughtClickSeller = s_BoughtClickSeller;
         delete [] s_BoughtClickSeller;

         d_BoughtClickSeller[iBoughtClickSeller] = tmp_BoughtClickSeller;
      }

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_TradeStats::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int SoldShowDates []
      n_size += sizeof (size_t);
      n_size += d_SoldShowDates.GetSize() * sizeof(int);

   // int SoldShowAmounts []
      n_size += sizeof (size_t);
      n_size += d_SoldShowAmounts.GetSize() * sizeof(int);

   // string SoldShowBuyer []
      n_size += sizeof (size_t);
      for (int iSoldShowBuyer=0; iSoldShowBuyer<d_SoldShowBuyer.GetSize(); iSoldShowBuyer++)
      {
         n_size += sizeof (size_t);
         n_size += d_SoldShowBuyer[iSoldShowBuyer].length()+1;
      }

   // int BoughtShowDates []
      n_size += sizeof (size_t);
      n_size += d_BoughtShowDates.GetSize() * sizeof(int);

   // int BoughtShowAmounts []
      n_size += sizeof (size_t);
      n_size += d_BoughtShowAmounts.GetSize() * sizeof(int);

   // string BoughtShowSeller []
      n_size += sizeof (size_t);
      for (int iBoughtShowSeller=0; iBoughtShowSeller<d_BoughtShowSeller.GetSize(); iBoughtShowSeller++)
      {
         n_size += sizeof (size_t);
         n_size += d_BoughtShowSeller[iBoughtShowSeller].length()+1;
      }

   // int SoldClickDates []
      n_size += sizeof (size_t);
      n_size += d_SoldClickDates.GetSize() * sizeof(int);

   // int SoldClickAmounts []
      n_size += sizeof (size_t);
      n_size += d_SoldClickAmounts.GetSize() * sizeof(int);

   // string SoldClickBuyer []
      n_size += sizeof (size_t);
      for (int iSoldClickBuyer=0; iSoldClickBuyer<d_SoldClickBuyer.GetSize(); iSoldClickBuyer++)
      {
         n_size += sizeof (size_t);
         n_size += d_SoldClickBuyer[iSoldClickBuyer].length()+1;
      }

   // int BoughtClickDates []
      n_size += sizeof (size_t);
      n_size += d_BoughtClickDates.GetSize() * sizeof(int);

   // int BoughtClickAmounts []
      n_size += sizeof (size_t);
      n_size += d_BoughtClickAmounts.GetSize() * sizeof(int);

   // string BoughtClickSeller []
      n_size += sizeof (size_t);
      for (int iBoughtClickSeller=0; iBoughtClickSeller<d_BoughtClickSeller.GetSize(); iBoughtClickSeller++)
      {
         n_size += sizeof (size_t);
         n_size += d_BoughtClickSeller[iBoughtClickSeller].length()+1;
      }

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_TradeStats::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int SoldShowDates []
      (*(size_t*)(file+nOffset)) = d_SoldShowDates.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SoldShowDates);

   // int SoldShowAmounts []
      (*(size_t*)(file+nOffset)) = d_SoldShowAmounts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SoldShowAmounts);

   // string SoldShowBuyer []
      (*(size_t*)(file+nOffset)) = d_SoldShowBuyer.GetSize();
      nOffset += sizeof(size_t);
      for (int iSoldShowBuyer=0; iSoldShowBuyer<d_SoldShowBuyer.GetSize(); iSoldShowBuyer++)
      {
         size_t n_SoldShowBuyer = d_SoldShowBuyer[iSoldShowBuyer].length()+1;
         (*(size_t*)(file+nOffset)) = n_SoldShowBuyer;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_SoldShowBuyer[iSoldShowBuyer].c_str(), n_SoldShowBuyer);
         ENCODE_STRING (n_SoldShowBuyer, (char*)(file+nOffset));
         nOffset += n_SoldShowBuyer;
      }

   // int BoughtShowDates []
      (*(size_t*)(file+nOffset)) = d_BoughtShowDates.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,BoughtShowDates);

   // int BoughtShowAmounts []
      (*(size_t*)(file+nOffset)) = d_BoughtShowAmounts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,BoughtShowAmounts);

   // string BoughtShowSeller []
      (*(size_t*)(file+nOffset)) = d_BoughtShowSeller.GetSize();
      nOffset += sizeof(size_t);
      for (int iBoughtShowSeller=0; iBoughtShowSeller<d_BoughtShowSeller.GetSize(); iBoughtShowSeller++)
      {
         size_t n_BoughtShowSeller = d_BoughtShowSeller[iBoughtShowSeller].length()+1;
         (*(size_t*)(file+nOffset)) = n_BoughtShowSeller;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_BoughtShowSeller[iBoughtShowSeller].c_str(), n_BoughtShowSeller);
         ENCODE_STRING (n_BoughtShowSeller, (char*)(file+nOffset));
         nOffset += n_BoughtShowSeller;
      }

   // int SoldClickDates []
      (*(size_t*)(file+nOffset)) = d_SoldClickDates.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SoldClickDates);

   // int SoldClickAmounts []
      (*(size_t*)(file+nOffset)) = d_SoldClickAmounts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SoldClickAmounts);

   // string SoldClickBuyer []
      (*(size_t*)(file+nOffset)) = d_SoldClickBuyer.GetSize();
      nOffset += sizeof(size_t);
      for (int iSoldClickBuyer=0; iSoldClickBuyer<d_SoldClickBuyer.GetSize(); iSoldClickBuyer++)
      {
         size_t n_SoldClickBuyer = d_SoldClickBuyer[iSoldClickBuyer].length()+1;
         (*(size_t*)(file+nOffset)) = n_SoldClickBuyer;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_SoldClickBuyer[iSoldClickBuyer].c_str(), n_SoldClickBuyer);
         ENCODE_STRING (n_SoldClickBuyer, (char*)(file+nOffset));
         nOffset += n_SoldClickBuyer;
      }

   // int BoughtClickDates []
      (*(size_t*)(file+nOffset)) = d_BoughtClickDates.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,BoughtClickDates);

   // int BoughtClickAmounts []
      (*(size_t*)(file+nOffset)) = d_BoughtClickAmounts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,BoughtClickAmounts);

   // string BoughtClickSeller []
      (*(size_t*)(file+nOffset)) = d_BoughtClickSeller.GetSize();
      nOffset += sizeof(size_t);
      for (int iBoughtClickSeller=0; iBoughtClickSeller<d_BoughtClickSeller.GetSize(); iBoughtClickSeller++)
      {
         size_t n_BoughtClickSeller = d_BoughtClickSeller[iBoughtClickSeller].length()+1;
         (*(size_t*)(file+nOffset)) = n_BoughtClickSeller;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_BoughtClickSeller[iBoughtClickSeller].c_str(), n_BoughtClickSeller);
         ENCODE_STRING (n_BoughtClickSeller, (char*)(file+nOffset));
         nOffset += n_BoughtClickSeller;
      }

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_TradeStats::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_TradeStats], objID);
      dbg += SSS;

   // int SoldShowDates []
      SSS.Format ("SoldShowDates[].size = %d:\n", d_SoldShowDates.GetSize());
      dbg += SSS;
      for (int iSoldShowDates=0; iSoldShowDates<d_SoldShowDates.GetSize(); iSoldShowDates++)
      {
         SSS.Format ("   SoldShowDates[%d] = %d\n", iSoldShowDates, d_SoldShowDates[iSoldShowDates]);
         dbg += SSS;
      }

   // int SoldShowAmounts []
      SSS.Format ("SoldShowAmounts[].size = %d:\n", d_SoldShowAmounts.GetSize());
      dbg += SSS;
      for (int iSoldShowAmounts=0; iSoldShowAmounts<d_SoldShowAmounts.GetSize(); iSoldShowAmounts++)
      {
         SSS.Format ("   SoldShowAmounts[%d] = %d\n", iSoldShowAmounts, d_SoldShowAmounts[iSoldShowAmounts]);
         dbg += SSS;
      }

   // string SoldShowBuyer []
      SSS.Format ("SoldShowBuyer[].size = %d:\n", d_SoldShowBuyer.GetSize());
      dbg += SSS;
      for (int iSoldShowBuyer=0; iSoldShowBuyer<d_SoldShowBuyer.GetSize(); iSoldShowBuyer++)
      {
         SSS.Format ("   SoldShowBuyer[%d] = '%s'\n", iSoldShowBuyer, d_SoldShowBuyer[iSoldShowBuyer].c_str());
         dbg += SSS;
      }

   // int BoughtShowDates []
      SSS.Format ("BoughtShowDates[].size = %d:\n", d_BoughtShowDates.GetSize());
      dbg += SSS;
      for (int iBoughtShowDates=0; iBoughtShowDates<d_BoughtShowDates.GetSize(); iBoughtShowDates++)
      {
         SSS.Format ("   BoughtShowDates[%d] = %d\n", iBoughtShowDates, d_BoughtShowDates[iBoughtShowDates]);
         dbg += SSS;
      }

   // int BoughtShowAmounts []
      SSS.Format ("BoughtShowAmounts[].size = %d:\n", d_BoughtShowAmounts.GetSize());
      dbg += SSS;
      for (int iBoughtShowAmounts=0; iBoughtShowAmounts<d_BoughtShowAmounts.GetSize(); iBoughtShowAmounts++)
      {
         SSS.Format ("   BoughtShowAmounts[%d] = %d\n", iBoughtShowAmounts, d_BoughtShowAmounts[iBoughtShowAmounts]);
         dbg += SSS;
      }

   // string BoughtShowSeller []
      SSS.Format ("BoughtShowSeller[].size = %d:\n", d_BoughtShowSeller.GetSize());
      dbg += SSS;
      for (int iBoughtShowSeller=0; iBoughtShowSeller<d_BoughtShowSeller.GetSize(); iBoughtShowSeller++)
      {
         SSS.Format ("   BoughtShowSeller[%d] = '%s'\n", iBoughtShowSeller, d_BoughtShowSeller[iBoughtShowSeller].c_str());
         dbg += SSS;
      }

   // int SoldClickDates []
      SSS.Format ("SoldClickDates[].size = %d:\n", d_SoldClickDates.GetSize());
      dbg += SSS;
      for (int iSoldClickDates=0; iSoldClickDates<d_SoldClickDates.GetSize(); iSoldClickDates++)
      {
         SSS.Format ("   SoldClickDates[%d] = %d\n", iSoldClickDates, d_SoldClickDates[iSoldClickDates]);
         dbg += SSS;
      }

   // int SoldClickAmounts []
      SSS.Format ("SoldClickAmounts[].size = %d:\n", d_SoldClickAmounts.GetSize());
      dbg += SSS;
      for (int iSoldClickAmounts=0; iSoldClickAmounts<d_SoldClickAmounts.GetSize(); iSoldClickAmounts++)
      {
         SSS.Format ("   SoldClickAmounts[%d] = %d\n", iSoldClickAmounts, d_SoldClickAmounts[iSoldClickAmounts]);
         dbg += SSS;
      }

   // string SoldClickBuyer []
      SSS.Format ("SoldClickBuyer[].size = %d:\n", d_SoldClickBuyer.GetSize());
      dbg += SSS;
      for (int iSoldClickBuyer=0; iSoldClickBuyer<d_SoldClickBuyer.GetSize(); iSoldClickBuyer++)
      {
         SSS.Format ("   SoldClickBuyer[%d] = '%s'\n", iSoldClickBuyer, d_SoldClickBuyer[iSoldClickBuyer].c_str());
         dbg += SSS;
      }

   // int BoughtClickDates []
      SSS.Format ("BoughtClickDates[].size = %d:\n", d_BoughtClickDates.GetSize());
      dbg += SSS;
      for (int iBoughtClickDates=0; iBoughtClickDates<d_BoughtClickDates.GetSize(); iBoughtClickDates++)
      {
         SSS.Format ("   BoughtClickDates[%d] = %d\n", iBoughtClickDates, d_BoughtClickDates[iBoughtClickDates]);
         dbg += SSS;
      }

   // int BoughtClickAmounts []
      SSS.Format ("BoughtClickAmounts[].size = %d:\n", d_BoughtClickAmounts.GetSize());
      dbg += SSS;
      for (int iBoughtClickAmounts=0; iBoughtClickAmounts<d_BoughtClickAmounts.GetSize(); iBoughtClickAmounts++)
      {
         SSS.Format ("   BoughtClickAmounts[%d] = %d\n", iBoughtClickAmounts, d_BoughtClickAmounts[iBoughtClickAmounts]);
         dbg += SSS;
      }

   // string BoughtClickSeller []
      SSS.Format ("BoughtClickSeller[].size = %d:\n", d_BoughtClickSeller.GetSize());
      dbg += SSS;
      for (int iBoughtClickSeller=0; iBoughtClickSeller<d_BoughtClickSeller.GetSize(); iBoughtClickSeller++)
      {
         SSS.Format ("   BoughtClickSeller[%d] = '%s'\n", iBoughtClickSeller, d_BoughtClickSeller[iBoughtClickSeller].c_str());
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Banner::OD_Banner (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Banner;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_OwnerID = NA;
      d_FileSize = 0;
      d_UploadNo = 0;
      d_CreationTime = 0;
      d_VBN = 255;
      d_State = true;
      d_Profile = NA;
      d_SiteAnnounce.Alloc (0);
      d_ba_Concept.Alloc (0);
      d_eba_Concept.Alloc (0);
      d_TotalShows = 0;
      d_TotalClicks = 0;
      d_Allowed = false;
      d_ObjectState = 1;
      d_ba_ModeratorComment.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_Banner::~OD_Banner () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Banner::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_OwnerID;           break;
         case 2: ka += d_FileName;          break;
         case 3: ka += d_FileSize;          break;
         case 4: ka += d_UploadNo;          break;
         case 5: ka += d_CreationTime;      break;
         case 6: ka += d_VBN;               break;
         case 7: ka += d_Description;       break;
         case 8: ka += d_State;             break;
         case 9: ka += d_Profile;           break;
         case 13: ka += d_TotalShows;        break;
         case 14: ka += d_TotalClicks;       break;
         case 15: ka += d_Allowed;           break;
         case 16: ka += d_ObjectState;       break;
         case 18: ka += d_TagID;             break;
         case 19: ka += d_TagInt;            break;
         case 20: ka += d_TagBool;           break;
         case 24: ka += d_CacheTime;         break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Banner::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier OwnerID
      d_OwnerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string FileName
      size_t n_FileName = (*(size_t*)(file+nOffset));  // n_FileName = strlen (s_FileName)+1;
      nOffset += sizeof(size_t);
      char * s_FileName = new char [n_FileName];
      memcpy (s_FileName, (file+nOffset), n_FileName);
      nOffset += n_FileName;
      DECODE_STRING (n_FileName, s_FileName);
      d_FileName = s_FileName;
      delete [] s_FileName;

   // int FileSize
      d_FileSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int UploadNo
      d_UploadNo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // byte VBN
      d_VBN = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description];
      memcpy (s_Description, (file+nOffset), n_Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // bool State
      d_State = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier Profile
      d_Profile = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SiteAnnounce []
      int arr_size_SiteAnnounce = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteAnnounce.Alloc (arr_size_SiteAnnounce);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteAnnounce);

   // byte ba_Concept []
      int arr_size_ba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Concept.Alloc (arr_size_ba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      int arr_size_eba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_Concept.Alloc (arr_size_eba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_Concept);

   // int TotalShows
      d_TotalShows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TotalClicks
      d_TotalClicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool Allowed
      d_Allowed = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ObjectState
      d_ObjectState = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_ModeratorComment []
      int arr_size_ba_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ModeratorComment.Alloc (arr_size_ba_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Banner::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier OwnerID
      n_size += sizeof (identifier);

   // string FileName
      n_size += sizeof (size_t);
      n_size += d_FileName.length()+1;

   // int FileSize
      n_size += sizeof (int);

   // int UploadNo
      n_size += sizeof (int);

   // int CreationTime
      n_size += sizeof (int);

   // byte VBN
      n_size += sizeof (byte);

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // bool State
      n_size += sizeof (bool);

   // identifier Profile
      n_size += sizeof (identifier);

   // identifier SiteAnnounce []
      n_size += sizeof (size_t);
      n_size += d_SiteAnnounce.GetSize() * sizeof(identifier);

   // byte ba_Concept []
      n_size += sizeof (size_t);
      n_size += d_ba_Concept.GetSize() * sizeof(byte);

   // byte eba_Concept []
      n_size += sizeof (size_t);
      n_size += d_eba_Concept.GetSize() * sizeof(byte);

   // int TotalShows
      n_size += sizeof (int);

   // int TotalClicks
      n_size += sizeof (int);

   // bool Allowed
      n_size += sizeof (bool);

   // byte ObjectState
      n_size += sizeof (byte);

   // byte ba_ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ba_ModeratorComment.GetSize() * sizeof(byte);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Banner::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier OwnerID
      (*(identifier*)(file+nOffset)) = d_OwnerID;
      nOffset += sizeof (identifier);

   // string FileName
      size_t n_FileName = d_FileName.length()+1;
      (*(size_t*)(file+nOffset)) = n_FileName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_FileName.c_str(), n_FileName);
      ENCODE_STRING (n_FileName, (char*)(file+nOffset));
      nOffset += n_FileName;

   // int FileSize
      (*(int*)(file+nOffset)) = d_FileSize;
      nOffset += sizeof (int);

   // int UploadNo
      (*(int*)(file+nOffset)) = d_UploadNo;
      nOffset += sizeof (int);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // byte VBN
      (*(byte*)(file+nOffset)) = d_VBN;
      nOffset += sizeof (byte);

   // string Description
      size_t n_Description = d_Description.length()+1;
      (*(size_t*)(file+nOffset)) = n_Description;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Description.c_str(), n_Description);
      ENCODE_STRING (n_Description, (char*)(file+nOffset));
      nOffset += n_Description;

   // bool State
      (*(bool*)(file+nOffset)) = d_State;
      nOffset += sizeof (bool);

   // identifier Profile
      (*(identifier*)(file+nOffset)) = d_Profile;
      nOffset += sizeof (identifier);

   // identifier SiteAnnounce []
      (*(size_t*)(file+nOffset)) = d_SiteAnnounce.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteAnnounce);

   // byte ba_Concept []
      (*(size_t*)(file+nOffset)) = d_ba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      (*(size_t*)(file+nOffset)) = d_eba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_Concept);

   // int TotalShows
      (*(int*)(file+nOffset)) = d_TotalShows;
      nOffset += sizeof (int);

   // int TotalClicks
      (*(int*)(file+nOffset)) = d_TotalClicks;
      nOffset += sizeof (int);

   // bool Allowed
      (*(bool*)(file+nOffset)) = d_Allowed;
      nOffset += sizeof (bool);

   // byte ObjectState
      (*(byte*)(file+nOffset)) = d_ObjectState;
      nOffset += sizeof (byte);

   // byte ba_ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ba_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Banner::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Banner], objID);
      dbg += SSS;

   // identifier OwnerID
      SSS.Format ("OwnerID = %d\n", d_OwnerID);
      dbg += SSS;

   // string FileName
      SSS.Format ("FileName = '%s'\n", d_FileName.c_str());
      dbg += SSS;

   // int FileSize
      SSS.Format ("FileSize = %d\n", d_FileSize);
      dbg += SSS;

   // int UploadNo
      SSS.Format ("UploadNo = %d\n", d_UploadNo);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // byte VBN
      SSS.Format ("VBN = %d\n", d_VBN);
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // bool State
      SSS.Format ("State = %s\n", d_State?"true":"false");
      dbg += SSS;

   // identifier Profile
      SSS.Format ("Profile = %d\n", d_Profile);
      dbg += SSS;

   // identifier SiteAnnounce []
      SSS.Format ("SiteAnnounce[].size = %d:\n", d_SiteAnnounce.GetSize());
      dbg += SSS;
      for (int iSiteAnnounce=0; iSiteAnnounce<d_SiteAnnounce.GetSize(); iSiteAnnounce++)
      {
         SSS.Format ("   SiteAnnounce[%d] = %d\n", iSiteAnnounce, d_SiteAnnounce[iSiteAnnounce]);
         dbg += SSS;
      }

   // byte ba_Concept []
      SSS.Format ("ba_Concept[].size = %d:\n", d_ba_Concept.GetSize());
      dbg += SSS;
      for (int iba_Concept=0; iba_Concept<d_ba_Concept.GetSize(); iba_Concept++)
      {
         SSS.Format ("   ba_Concept[%d] = %d\n", iba_Concept, d_ba_Concept[iba_Concept]);
         dbg += SSS;
      }

   // byte eba_Concept []
      SSS.Format ("eba_Concept[].size = %d:\n", d_eba_Concept.GetSize());
      dbg += SSS;
      for (int ieba_Concept=0; ieba_Concept<d_eba_Concept.GetSize(); ieba_Concept++)
      {
         SSS.Format ("   eba_Concept[%d] = %d\n", ieba_Concept, d_eba_Concept[ieba_Concept]);
         dbg += SSS;
      }

   // int TotalShows
      SSS.Format ("TotalShows = %d\n", d_TotalShows);
      dbg += SSS;

   // int TotalClicks
      SSS.Format ("TotalClicks = %d\n", d_TotalClicks);
      dbg += SSS;

   // bool Allowed
      SSS.Format ("Allowed = %s\n", d_Allowed?"true":"false");
      dbg += SSS;

   // byte ObjectState
      SSS.Format ("ObjectState = %d\n", d_ObjectState);
      dbg += SSS;

   // byte ba_ModeratorComment []
      SSS.Format ("ba_ModeratorComment[].size = %d:\n", d_ba_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iba_ModeratorComment=0; iba_ModeratorComment<d_ba_ModeratorComment.GetSize(); iba_ModeratorComment++)
      {
         SSS.Format ("   ba_ModeratorComment[%d] = %d\n", iba_ModeratorComment, d_ba_ModeratorComment[iba_ModeratorComment]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_BannerProfile::OD_BannerProfile (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_BannerProfile;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_VBN = 255;
      d_LastModified = 0;
      d_OwnerID = NA;
      d_HREF = NA;
      d_Commercial = false;
      d_BannerType = 0;
      d_SiteAnnounce.Alloc (0);
      d_Banner.Alloc (0);
      d_ba_Concept.Alloc (0);
      d_eba_Concept.Alloc (0);
      d_State = false;
      d_ba_SiteConceptInclude.Alloc (0);
      d_ba_SiteConceptExclude.Alloc (0);
      d_eba_SiteConcept.Alloc (0);
      d_SiteInclude.Alloc (0);
      d_SiteExclude.Alloc (0);
      d_ViewerIPEnable.Alloc (0);
      d_ViewerIPDisable.Alloc (0);
      d_ba_ViewerConceptInclude.Alloc (0);
      d_ba_ViewerConceptExclude.Alloc (0);
      d_eba_ViewerConcept.Alloc (0);
      d_UseLocalTime = true;
      d_ScheduleTZOffset = 0;
      d_ShowIfLocalUnknown = true;
      d_ba_Schedule.Alloc (0);
      d_AutoOn = 0;
      d_AutoOff = 2147483647;
      d_RepeatCount = -1;
      d_RepeatTime = 0;
      d_SiteTarget_SiteID.Alloc (0);
      d_SiteTarget_ShowRate.Alloc (0);
      d_SiteTarget_ClickRate.Alloc (0);
      d_SiteTarget_ViewRate.Alloc (0);
      d_ViewerConceptRate.Alloc (0);
      d_ShowNumRate.Alloc (0);
      d_ClickNumRate.Alloc (0);
      d_HitNumRate.Alloc (0);
      d_SessionTimeRate.Alloc (0);
      d_CountTypeByShows = true;
      d_MaxDailyClicks = 0;
      d_MaxDailyShows = 0;
      d_MaxDailyShowsChangeTime = 0;
      d_TotalShows = 0;
      d_TotalClicks = 0;
      d_SessionEvents = 0;
      d_Priority = (float) 1;
      d_Allowed = true;
      d_ObjectState = 1;
      d_ba_ModeratorComment.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_BannerProfile::~OD_BannerProfile () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_BannerProfile::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Name;                         break;
         case 2: ka += d_VBN;                          break;
         case 3: ka += d_LastModified;                 break;
         case 4: ka += d_OwnerID;                      break;
         case 5: ka += d_HREF;                         break;
         case 6: ka += d_Commercial;                   break;
         case 7: ka += d_BannerType;                   break;
         case 12: ka += d_State;                        break;
         case 13: ka += d_AltText;                      break;
         case 24: ka += d_UseLocalTime;                 break;
         case 25: ka += d_ScheduleTZOffset;             break;
         case 26: ka += d_ShowIfLocalUnknown;           break;
         case 28: ka += d_AutoOn;                       break;
         case 29: ka += d_AutoOff;                      break;
         case 30: ka += d_RepeatCount;                  break;
         case 31: ka += d_RepeatTime;                   break;
         case 41: ka += d_CountTypeByShows;             break;
         case 42: ka += d_MaxDailyClicks;               break;
         case 43: ka += d_MaxDailyShows;                break;
         case 44: ka += d_MaxDailyShowsChangeTime;      break;
         case 45: ka += d_TotalShows;                   break;
         case 46: ka += d_TotalClicks;                  break;
         case 47: ka += d_SessionEvents;                break;
         case 48: ka += d_Priority;                     break;
         case 49: ka += d_Allowed;                      break;
         case 50: ka += d_ObjectState;                  break;
         case 52: ka += d_TagID;                        break;
         case 53: ka += d_TagInt;                       break;
         case 54: ka += d_TagBool;                      break;
         case 58: ka += d_CacheTime;                    break;
      }
   }


// Загрузка объекта с диска
   size_t OD_BannerProfile::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // byte VBN
      d_VBN = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // int LastModified
      d_LastModified = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier OwnerID
      d_OwnerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier HREF
      d_HREF = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool Commercial
      d_Commercial = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int BannerType
      d_BannerType = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier SiteAnnounce []
      int arr_size_SiteAnnounce = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteAnnounce.Alloc (arr_size_SiteAnnounce);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteAnnounce);

   // identifier Banner []
      int arr_size_Banner = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Banner.Alloc (arr_size_Banner);
      OD_LOAD_SIMPLE_ARRAY (identifier,Banner);

   // byte ba_Concept []
      int arr_size_ba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Concept.Alloc (arr_size_ba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      int arr_size_eba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_Concept.Alloc (arr_size_eba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_Concept);

   // bool State
      d_State = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // string AltText
      size_t n_AltText = (*(size_t*)(file+nOffset));  // n_AltText = strlen (s_AltText)+1;
      nOffset += sizeof(size_t);
      char * s_AltText = new char [n_AltText];
      memcpy (s_AltText, (file+nOffset), n_AltText);
      nOffset += n_AltText;
      DECODE_STRING (n_AltText, s_AltText);
      d_AltText = s_AltText;
      delete [] s_AltText;

   // byte ba_SiteConceptInclude []
      int arr_size_ba_SiteConceptInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_SiteConceptInclude.Alloc (arr_size_ba_SiteConceptInclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_SiteConceptInclude);

   // byte ba_SiteConceptExclude []
      int arr_size_ba_SiteConceptExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_SiteConceptExclude.Alloc (arr_size_ba_SiteConceptExclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_SiteConceptExclude);

   // byte eba_SiteConcept []
      int arr_size_eba_SiteConcept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_SiteConcept.Alloc (arr_size_eba_SiteConcept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_SiteConcept);

   // identifier SiteInclude []
      int arr_size_SiteInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteInclude.Alloc (arr_size_SiteInclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteInclude);

   // identifier SiteExclude []
      int arr_size_SiteExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteExclude.Alloc (arr_size_SiteExclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteExclude);

   // string ViewerIPEnable []
      int arr_size_ViewerIPEnable = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ViewerIPEnable.Alloc (arr_size_ViewerIPEnable);
      for (int iViewerIPEnable=0; iViewerIPEnable<(int)arr_size_ViewerIPEnable; iViewerIPEnable++)
      {
         string tmp_ViewerIPEnable;
         size_t n_ViewerIPEnable = (*(size_t*)(file+nOffset));  // n_ViewerIPEnable = strlen (s_ViewerIPEnable)+1;
         nOffset += sizeof(size_t);
         char * s_ViewerIPEnable = new char [n_ViewerIPEnable];
         memcpy (s_ViewerIPEnable, (file+nOffset), n_ViewerIPEnable);
         nOffset += n_ViewerIPEnable;
         DECODE_STRING (n_ViewerIPEnable, s_ViewerIPEnable);
         tmp_ViewerIPEnable = s_ViewerIPEnable;
         delete [] s_ViewerIPEnable;

         d_ViewerIPEnable[iViewerIPEnable] = tmp_ViewerIPEnable;
      }

   // string ViewerIPDisable []
      int arr_size_ViewerIPDisable = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ViewerIPDisable.Alloc (arr_size_ViewerIPDisable);
      for (int iViewerIPDisable=0; iViewerIPDisable<(int)arr_size_ViewerIPDisable; iViewerIPDisable++)
      {
         string tmp_ViewerIPDisable;
         size_t n_ViewerIPDisable = (*(size_t*)(file+nOffset));  // n_ViewerIPDisable = strlen (s_ViewerIPDisable)+1;
         nOffset += sizeof(size_t);
         char * s_ViewerIPDisable = new char [n_ViewerIPDisable];
         memcpy (s_ViewerIPDisable, (file+nOffset), n_ViewerIPDisable);
         nOffset += n_ViewerIPDisable;
         DECODE_STRING (n_ViewerIPDisable, s_ViewerIPDisable);
         tmp_ViewerIPDisable = s_ViewerIPDisable;
         delete [] s_ViewerIPDisable;

         d_ViewerIPDisable[iViewerIPDisable] = tmp_ViewerIPDisable;
      }

   // byte ba_ViewerConceptInclude []
      int arr_size_ba_ViewerConceptInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ViewerConceptInclude.Alloc (arr_size_ba_ViewerConceptInclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ViewerConceptInclude);

   // byte ba_ViewerConceptExclude []
      int arr_size_ba_ViewerConceptExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ViewerConceptExclude.Alloc (arr_size_ba_ViewerConceptExclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ViewerConceptExclude);

   // byte eba_ViewerConcept []
      int arr_size_eba_ViewerConcept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_ViewerConcept.Alloc (arr_size_eba_ViewerConcept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_ViewerConcept);

   // bool UseLocalTime
      d_UseLocalTime = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int ScheduleTZOffset
      d_ScheduleTZOffset = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool ShowIfLocalUnknown
      d_ShowIfLocalUnknown = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ba_Schedule []
      int arr_size_ba_Schedule = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Schedule.Alloc (arr_size_ba_Schedule);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Schedule);

   // int AutoOn
      d_AutoOn = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int AutoOff
      d_AutoOff = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int RepeatCount
      d_RepeatCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int RepeatTime
      d_RepeatTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier SiteTarget_SiteID []
      int arr_size_SiteTarget_SiteID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteTarget_SiteID.Alloc (arr_size_SiteTarget_SiteID);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteTarget_SiteID);

   // int SiteTarget_ShowRate []
      int arr_size_SiteTarget_ShowRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteTarget_ShowRate.Alloc (arr_size_SiteTarget_ShowRate);
      OD_LOAD_SIMPLE_ARRAY (int,SiteTarget_ShowRate);

   // int SiteTarget_ClickRate []
      int arr_size_SiteTarget_ClickRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteTarget_ClickRate.Alloc (arr_size_SiteTarget_ClickRate);
      OD_LOAD_SIMPLE_ARRAY (int,SiteTarget_ClickRate);

   // int SiteTarget_ViewRate []
      int arr_size_SiteTarget_ViewRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteTarget_ViewRate.Alloc (arr_size_SiteTarget_ViewRate);
      OD_LOAD_SIMPLE_ARRAY (int,SiteTarget_ViewRate);

   // int ViewerConceptRate []
      int arr_size_ViewerConceptRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ViewerConceptRate.Alloc (arr_size_ViewerConceptRate);
      OD_LOAD_SIMPLE_ARRAY (int,ViewerConceptRate);

   // int ShowNumRate []
      int arr_size_ShowNumRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ShowNumRate.Alloc (arr_size_ShowNumRate);
      OD_LOAD_SIMPLE_ARRAY (int,ShowNumRate);

   // int ClickNumRate []
      int arr_size_ClickNumRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ClickNumRate.Alloc (arr_size_ClickNumRate);
      OD_LOAD_SIMPLE_ARRAY (int,ClickNumRate);

   // int HitNumRate []
      int arr_size_HitNumRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_HitNumRate.Alloc (arr_size_HitNumRate);
      OD_LOAD_SIMPLE_ARRAY (int,HitNumRate);

   // int SessionTimeRate []
      int arr_size_SessionTimeRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SessionTimeRate.Alloc (arr_size_SessionTimeRate);
      OD_LOAD_SIMPLE_ARRAY (int,SessionTimeRate);

   // bool CountTypeByShows
      d_CountTypeByShows = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int MaxDailyClicks
      d_MaxDailyClicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MaxDailyShows
      d_MaxDailyShows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MaxDailyShowsChangeTime
      d_MaxDailyShowsChangeTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TotalShows
      d_TotalShows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TotalClicks
      d_TotalClicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SessionEvents
      d_SessionEvents = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Priority
      d_Priority = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // bool Allowed
      d_Allowed = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ObjectState
      d_ObjectState = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_ModeratorComment []
      int arr_size_ba_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ModeratorComment.Alloc (arr_size_ba_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_BannerProfile::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // byte VBN
      n_size += sizeof (byte);

   // int LastModified
      n_size += sizeof (int);

   // identifier OwnerID
      n_size += sizeof (identifier);

   // identifier HREF
      n_size += sizeof (identifier);

   // bool Commercial
      n_size += sizeof (bool);

   // int BannerType
      n_size += sizeof (int);

   // identifier SiteAnnounce []
      n_size += sizeof (size_t);
      n_size += d_SiteAnnounce.GetSize() * sizeof(identifier);

   // identifier Banner []
      n_size += sizeof (size_t);
      n_size += d_Banner.GetSize() * sizeof(identifier);

   // byte ba_Concept []
      n_size += sizeof (size_t);
      n_size += d_ba_Concept.GetSize() * sizeof(byte);

   // byte eba_Concept []
      n_size += sizeof (size_t);
      n_size += d_eba_Concept.GetSize() * sizeof(byte);

   // bool State
      n_size += sizeof (bool);

   // string AltText
      n_size += sizeof (size_t);
      n_size += d_AltText.length()+1;

   // byte ba_SiteConceptInclude []
      n_size += sizeof (size_t);
      n_size += d_ba_SiteConceptInclude.GetSize() * sizeof(byte);

   // byte ba_SiteConceptExclude []
      n_size += sizeof (size_t);
      n_size += d_ba_SiteConceptExclude.GetSize() * sizeof(byte);

   // byte eba_SiteConcept []
      n_size += sizeof (size_t);
      n_size += d_eba_SiteConcept.GetSize() * sizeof(byte);

   // identifier SiteInclude []
      n_size += sizeof (size_t);
      n_size += d_SiteInclude.GetSize() * sizeof(identifier);

   // identifier SiteExclude []
      n_size += sizeof (size_t);
      n_size += d_SiteExclude.GetSize() * sizeof(identifier);

   // string ViewerIPEnable []
      n_size += sizeof (size_t);
      for (int iViewerIPEnable=0; iViewerIPEnable<d_ViewerIPEnable.GetSize(); iViewerIPEnable++)
      {
         n_size += sizeof (size_t);
         n_size += d_ViewerIPEnable[iViewerIPEnable].length()+1;
      }

   // string ViewerIPDisable []
      n_size += sizeof (size_t);
      for (int iViewerIPDisable=0; iViewerIPDisable<d_ViewerIPDisable.GetSize(); iViewerIPDisable++)
      {
         n_size += sizeof (size_t);
         n_size += d_ViewerIPDisable[iViewerIPDisable].length()+1;
      }

   // byte ba_ViewerConceptInclude []
      n_size += sizeof (size_t);
      n_size += d_ba_ViewerConceptInclude.GetSize() * sizeof(byte);

   // byte ba_ViewerConceptExclude []
      n_size += sizeof (size_t);
      n_size += d_ba_ViewerConceptExclude.GetSize() * sizeof(byte);

   // byte eba_ViewerConcept []
      n_size += sizeof (size_t);
      n_size += d_eba_ViewerConcept.GetSize() * sizeof(byte);

   // bool UseLocalTime
      n_size += sizeof (bool);

   // int ScheduleTZOffset
      n_size += sizeof (int);

   // bool ShowIfLocalUnknown
      n_size += sizeof (bool);

   // byte ba_Schedule []
      n_size += sizeof (size_t);
      n_size += d_ba_Schedule.GetSize() * sizeof(byte);

   // int AutoOn
      n_size += sizeof (int);

   // int AutoOff
      n_size += sizeof (int);

   // int RepeatCount
      n_size += sizeof (int);

   // int RepeatTime
      n_size += sizeof (int);

   // identifier SiteTarget_SiteID []
      n_size += sizeof (size_t);
      n_size += d_SiteTarget_SiteID.GetSize() * sizeof(identifier);

   // int SiteTarget_ShowRate []
      n_size += sizeof (size_t);
      n_size += d_SiteTarget_ShowRate.GetSize() * sizeof(int);

   // int SiteTarget_ClickRate []
      n_size += sizeof (size_t);
      n_size += d_SiteTarget_ClickRate.GetSize() * sizeof(int);

   // int SiteTarget_ViewRate []
      n_size += sizeof (size_t);
      n_size += d_SiteTarget_ViewRate.GetSize() * sizeof(int);

   // int ViewerConceptRate []
      n_size += sizeof (size_t);
      n_size += d_ViewerConceptRate.GetSize() * sizeof(int);

   // int ShowNumRate []
      n_size += sizeof (size_t);
      n_size += d_ShowNumRate.GetSize() * sizeof(int);

   // int ClickNumRate []
      n_size += sizeof (size_t);
      n_size += d_ClickNumRate.GetSize() * sizeof(int);

   // int HitNumRate []
      n_size += sizeof (size_t);
      n_size += d_HitNumRate.GetSize() * sizeof(int);

   // int SessionTimeRate []
      n_size += sizeof (size_t);
      n_size += d_SessionTimeRate.GetSize() * sizeof(int);

   // bool CountTypeByShows
      n_size += sizeof (bool);

   // int MaxDailyClicks
      n_size += sizeof (int);

   // int MaxDailyShows
      n_size += sizeof (int);

   // int MaxDailyShowsChangeTime
      n_size += sizeof (int);

   // int TotalShows
      n_size += sizeof (int);

   // int TotalClicks
      n_size += sizeof (int);

   // int SessionEvents
      n_size += sizeof (int);

   // float Priority
      n_size += sizeof (float);

   // bool Allowed
      n_size += sizeof (bool);

   // byte ObjectState
      n_size += sizeof (byte);

   // byte ba_ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ba_ModeratorComment.GetSize() * sizeof(byte);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_BannerProfile::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // byte VBN
      (*(byte*)(file+nOffset)) = d_VBN;
      nOffset += sizeof (byte);

   // int LastModified
      (*(int*)(file+nOffset)) = d_LastModified;
      nOffset += sizeof (int);

   // identifier OwnerID
      (*(identifier*)(file+nOffset)) = d_OwnerID;
      nOffset += sizeof (identifier);

   // identifier HREF
      (*(identifier*)(file+nOffset)) = d_HREF;
      nOffset += sizeof (identifier);

   // bool Commercial
      (*(bool*)(file+nOffset)) = d_Commercial;
      nOffset += sizeof (bool);

   // int BannerType
      (*(int*)(file+nOffset)) = d_BannerType;
      nOffset += sizeof (int);

   // identifier SiteAnnounce []
      (*(size_t*)(file+nOffset)) = d_SiteAnnounce.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteAnnounce);

   // identifier Banner []
      (*(size_t*)(file+nOffset)) = d_Banner.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Banner);

   // byte ba_Concept []
      (*(size_t*)(file+nOffset)) = d_ba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      (*(size_t*)(file+nOffset)) = d_eba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_Concept);

   // bool State
      (*(bool*)(file+nOffset)) = d_State;
      nOffset += sizeof (bool);

   // string AltText
      size_t n_AltText = d_AltText.length()+1;
      (*(size_t*)(file+nOffset)) = n_AltText;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_AltText.c_str(), n_AltText);
      ENCODE_STRING (n_AltText, (char*)(file+nOffset));
      nOffset += n_AltText;

   // byte ba_SiteConceptInclude []
      (*(size_t*)(file+nOffset)) = d_ba_SiteConceptInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_SiteConceptInclude);

   // byte ba_SiteConceptExclude []
      (*(size_t*)(file+nOffset)) = d_ba_SiteConceptExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_SiteConceptExclude);

   // byte eba_SiteConcept []
      (*(size_t*)(file+nOffset)) = d_eba_SiteConcept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_SiteConcept);

   // identifier SiteInclude []
      (*(size_t*)(file+nOffset)) = d_SiteInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteInclude);

   // identifier SiteExclude []
      (*(size_t*)(file+nOffset)) = d_SiteExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteExclude);

   // string ViewerIPEnable []
      (*(size_t*)(file+nOffset)) = d_ViewerIPEnable.GetSize();
      nOffset += sizeof(size_t);
      for (int iViewerIPEnable=0; iViewerIPEnable<d_ViewerIPEnable.GetSize(); iViewerIPEnable++)
      {
         size_t n_ViewerIPEnable = d_ViewerIPEnable[iViewerIPEnable].length()+1;
         (*(size_t*)(file+nOffset)) = n_ViewerIPEnable;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ViewerIPEnable[iViewerIPEnable].c_str(), n_ViewerIPEnable);
         ENCODE_STRING (n_ViewerIPEnable, (char*)(file+nOffset));
         nOffset += n_ViewerIPEnable;
      }

   // string ViewerIPDisable []
      (*(size_t*)(file+nOffset)) = d_ViewerIPDisable.GetSize();
      nOffset += sizeof(size_t);
      for (int iViewerIPDisable=0; iViewerIPDisable<d_ViewerIPDisable.GetSize(); iViewerIPDisable++)
      {
         size_t n_ViewerIPDisable = d_ViewerIPDisable[iViewerIPDisable].length()+1;
         (*(size_t*)(file+nOffset)) = n_ViewerIPDisable;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ViewerIPDisable[iViewerIPDisable].c_str(), n_ViewerIPDisable);
         ENCODE_STRING (n_ViewerIPDisable, (char*)(file+nOffset));
         nOffset += n_ViewerIPDisable;
      }

   // byte ba_ViewerConceptInclude []
      (*(size_t*)(file+nOffset)) = d_ba_ViewerConceptInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ViewerConceptInclude);

   // byte ba_ViewerConceptExclude []
      (*(size_t*)(file+nOffset)) = d_ba_ViewerConceptExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ViewerConceptExclude);

   // byte eba_ViewerConcept []
      (*(size_t*)(file+nOffset)) = d_eba_ViewerConcept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_ViewerConcept);

   // bool UseLocalTime
      (*(bool*)(file+nOffset)) = d_UseLocalTime;
      nOffset += sizeof (bool);

   // int ScheduleTZOffset
      (*(int*)(file+nOffset)) = d_ScheduleTZOffset;
      nOffset += sizeof (int);

   // bool ShowIfLocalUnknown
      (*(bool*)(file+nOffset)) = d_ShowIfLocalUnknown;
      nOffset += sizeof (bool);

   // byte ba_Schedule []
      (*(size_t*)(file+nOffset)) = d_ba_Schedule.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Schedule);

   // int AutoOn
      (*(int*)(file+nOffset)) = d_AutoOn;
      nOffset += sizeof (int);

   // int AutoOff
      (*(int*)(file+nOffset)) = d_AutoOff;
      nOffset += sizeof (int);

   // int RepeatCount
      (*(int*)(file+nOffset)) = d_RepeatCount;
      nOffset += sizeof (int);

   // int RepeatTime
      (*(int*)(file+nOffset)) = d_RepeatTime;
      nOffset += sizeof (int);

   // identifier SiteTarget_SiteID []
      (*(size_t*)(file+nOffset)) = d_SiteTarget_SiteID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteTarget_SiteID);

   // int SiteTarget_ShowRate []
      (*(size_t*)(file+nOffset)) = d_SiteTarget_ShowRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SiteTarget_ShowRate);

   // int SiteTarget_ClickRate []
      (*(size_t*)(file+nOffset)) = d_SiteTarget_ClickRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SiteTarget_ClickRate);

   // int SiteTarget_ViewRate []
      (*(size_t*)(file+nOffset)) = d_SiteTarget_ViewRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SiteTarget_ViewRate);

   // int ViewerConceptRate []
      (*(size_t*)(file+nOffset)) = d_ViewerConceptRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ViewerConceptRate);

   // int ShowNumRate []
      (*(size_t*)(file+nOffset)) = d_ShowNumRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ShowNumRate);

   // int ClickNumRate []
      (*(size_t*)(file+nOffset)) = d_ClickNumRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ClickNumRate);

   // int HitNumRate []
      (*(size_t*)(file+nOffset)) = d_HitNumRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,HitNumRate);

   // int SessionTimeRate []
      (*(size_t*)(file+nOffset)) = d_SessionTimeRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SessionTimeRate);

   // bool CountTypeByShows
      (*(bool*)(file+nOffset)) = d_CountTypeByShows;
      nOffset += sizeof (bool);

   // int MaxDailyClicks
      (*(int*)(file+nOffset)) = d_MaxDailyClicks;
      nOffset += sizeof (int);

   // int MaxDailyShows
      (*(int*)(file+nOffset)) = d_MaxDailyShows;
      nOffset += sizeof (int);

   // int MaxDailyShowsChangeTime
      (*(int*)(file+nOffset)) = d_MaxDailyShowsChangeTime;
      nOffset += sizeof (int);

   // int TotalShows
      (*(int*)(file+nOffset)) = d_TotalShows;
      nOffset += sizeof (int);

   // int TotalClicks
      (*(int*)(file+nOffset)) = d_TotalClicks;
      nOffset += sizeof (int);

   // int SessionEvents
      (*(int*)(file+nOffset)) = d_SessionEvents;
      nOffset += sizeof (int);

   // float Priority
      (*(float*)(file+nOffset)) = d_Priority;
      nOffset += sizeof (float);

   // bool Allowed
      (*(bool*)(file+nOffset)) = d_Allowed;
      nOffset += sizeof (bool);

   // byte ObjectState
      (*(byte*)(file+nOffset)) = d_ObjectState;
      nOffset += sizeof (byte);

   // byte ba_ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ba_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_BannerProfile::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_BannerProfile], objID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // byte VBN
      SSS.Format ("VBN = %d\n", d_VBN);
      dbg += SSS;

   // int LastModified
      SSS.Format ("LastModified = %d\n", d_LastModified);
      dbg += SSS;

   // identifier OwnerID
      SSS.Format ("OwnerID = %d\n", d_OwnerID);
      dbg += SSS;

   // identifier HREF
      SSS.Format ("HREF = %d\n", d_HREF);
      dbg += SSS;

   // bool Commercial
      SSS.Format ("Commercial = %s\n", d_Commercial?"true":"false");
      dbg += SSS;

   // int BannerType
      SSS.Format ("BannerType = %d\n", d_BannerType);
      dbg += SSS;

   // identifier SiteAnnounce []
      SSS.Format ("SiteAnnounce[].size = %d:\n", d_SiteAnnounce.GetSize());
      dbg += SSS;
      for (int iSiteAnnounce=0; iSiteAnnounce<d_SiteAnnounce.GetSize(); iSiteAnnounce++)
      {
         SSS.Format ("   SiteAnnounce[%d] = %d\n", iSiteAnnounce, d_SiteAnnounce[iSiteAnnounce]);
         dbg += SSS;
      }

   // identifier Banner []
      SSS.Format ("Banner[].size = %d:\n", d_Banner.GetSize());
      dbg += SSS;
      for (int iBanner=0; iBanner<d_Banner.GetSize(); iBanner++)
      {
         SSS.Format ("   Banner[%d] = %d\n", iBanner, d_Banner[iBanner]);
         dbg += SSS;
      }

   // byte ba_Concept []
      SSS.Format ("ba_Concept[].size = %d:\n", d_ba_Concept.GetSize());
      dbg += SSS;
      for (int iba_Concept=0; iba_Concept<d_ba_Concept.GetSize(); iba_Concept++)
      {
         SSS.Format ("   ba_Concept[%d] = %d\n", iba_Concept, d_ba_Concept[iba_Concept]);
         dbg += SSS;
      }

   // byte eba_Concept []
      SSS.Format ("eba_Concept[].size = %d:\n", d_eba_Concept.GetSize());
      dbg += SSS;
      for (int ieba_Concept=0; ieba_Concept<d_eba_Concept.GetSize(); ieba_Concept++)
      {
         SSS.Format ("   eba_Concept[%d] = %d\n", ieba_Concept, d_eba_Concept[ieba_Concept]);
         dbg += SSS;
      }

   // bool State
      SSS.Format ("State = %s\n", d_State?"true":"false");
      dbg += SSS;

   // string AltText
      SSS.Format ("AltText = '%s'\n", d_AltText.c_str());
      dbg += SSS;

   // byte ba_SiteConceptInclude []
      SSS.Format ("ba_SiteConceptInclude[].size = %d:\n", d_ba_SiteConceptInclude.GetSize());
      dbg += SSS;
      for (int iba_SiteConceptInclude=0; iba_SiteConceptInclude<d_ba_SiteConceptInclude.GetSize(); iba_SiteConceptInclude++)
      {
         SSS.Format ("   ba_SiteConceptInclude[%d] = %d\n", iba_SiteConceptInclude, d_ba_SiteConceptInclude[iba_SiteConceptInclude]);
         dbg += SSS;
      }

   // byte ba_SiteConceptExclude []
      SSS.Format ("ba_SiteConceptExclude[].size = %d:\n", d_ba_SiteConceptExclude.GetSize());
      dbg += SSS;
      for (int iba_SiteConceptExclude=0; iba_SiteConceptExclude<d_ba_SiteConceptExclude.GetSize(); iba_SiteConceptExclude++)
      {
         SSS.Format ("   ba_SiteConceptExclude[%d] = %d\n", iba_SiteConceptExclude, d_ba_SiteConceptExclude[iba_SiteConceptExclude]);
         dbg += SSS;
      }

   // byte eba_SiteConcept []
      SSS.Format ("eba_SiteConcept[].size = %d:\n", d_eba_SiteConcept.GetSize());
      dbg += SSS;
      for (int ieba_SiteConcept=0; ieba_SiteConcept<d_eba_SiteConcept.GetSize(); ieba_SiteConcept++)
      {
         SSS.Format ("   eba_SiteConcept[%d] = %d\n", ieba_SiteConcept, d_eba_SiteConcept[ieba_SiteConcept]);
         dbg += SSS;
      }

   // identifier SiteInclude []
      SSS.Format ("SiteInclude[].size = %d:\n", d_SiteInclude.GetSize());
      dbg += SSS;
      for (int iSiteInclude=0; iSiteInclude<d_SiteInclude.GetSize(); iSiteInclude++)
      {
         SSS.Format ("   SiteInclude[%d] = %d\n", iSiteInclude, d_SiteInclude[iSiteInclude]);
         dbg += SSS;
      }

   // identifier SiteExclude []
      SSS.Format ("SiteExclude[].size = %d:\n", d_SiteExclude.GetSize());
      dbg += SSS;
      for (int iSiteExclude=0; iSiteExclude<d_SiteExclude.GetSize(); iSiteExclude++)
      {
         SSS.Format ("   SiteExclude[%d] = %d\n", iSiteExclude, d_SiteExclude[iSiteExclude]);
         dbg += SSS;
      }

   // string ViewerIPEnable []
      SSS.Format ("ViewerIPEnable[].size = %d:\n", d_ViewerIPEnable.GetSize());
      dbg += SSS;
      for (int iViewerIPEnable=0; iViewerIPEnable<d_ViewerIPEnable.GetSize(); iViewerIPEnable++)
      {
         SSS.Format ("   ViewerIPEnable[%d] = '%s'\n", iViewerIPEnable, d_ViewerIPEnable[iViewerIPEnable].c_str());
         dbg += SSS;
      }

   // string ViewerIPDisable []
      SSS.Format ("ViewerIPDisable[].size = %d:\n", d_ViewerIPDisable.GetSize());
      dbg += SSS;
      for (int iViewerIPDisable=0; iViewerIPDisable<d_ViewerIPDisable.GetSize(); iViewerIPDisable++)
      {
         SSS.Format ("   ViewerIPDisable[%d] = '%s'\n", iViewerIPDisable, d_ViewerIPDisable[iViewerIPDisable].c_str());
         dbg += SSS;
      }

   // byte ba_ViewerConceptInclude []
      SSS.Format ("ba_ViewerConceptInclude[].size = %d:\n", d_ba_ViewerConceptInclude.GetSize());
      dbg += SSS;
      for (int iba_ViewerConceptInclude=0; iba_ViewerConceptInclude<d_ba_ViewerConceptInclude.GetSize(); iba_ViewerConceptInclude++)
      {
         SSS.Format ("   ba_ViewerConceptInclude[%d] = %d\n", iba_ViewerConceptInclude, d_ba_ViewerConceptInclude[iba_ViewerConceptInclude]);
         dbg += SSS;
      }

   // byte ba_ViewerConceptExclude []
      SSS.Format ("ba_ViewerConceptExclude[].size = %d:\n", d_ba_ViewerConceptExclude.GetSize());
      dbg += SSS;
      for (int iba_ViewerConceptExclude=0; iba_ViewerConceptExclude<d_ba_ViewerConceptExclude.GetSize(); iba_ViewerConceptExclude++)
      {
         SSS.Format ("   ba_ViewerConceptExclude[%d] = %d\n", iba_ViewerConceptExclude, d_ba_ViewerConceptExclude[iba_ViewerConceptExclude]);
         dbg += SSS;
      }

   // byte eba_ViewerConcept []
      SSS.Format ("eba_ViewerConcept[].size = %d:\n", d_eba_ViewerConcept.GetSize());
      dbg += SSS;
      for (int ieba_ViewerConcept=0; ieba_ViewerConcept<d_eba_ViewerConcept.GetSize(); ieba_ViewerConcept++)
      {
         SSS.Format ("   eba_ViewerConcept[%d] = %d\n", ieba_ViewerConcept, d_eba_ViewerConcept[ieba_ViewerConcept]);
         dbg += SSS;
      }

   // bool UseLocalTime
      SSS.Format ("UseLocalTime = %s\n", d_UseLocalTime?"true":"false");
      dbg += SSS;

   // int ScheduleTZOffset
      SSS.Format ("ScheduleTZOffset = %d\n", d_ScheduleTZOffset);
      dbg += SSS;

   // bool ShowIfLocalUnknown
      SSS.Format ("ShowIfLocalUnknown = %s\n", d_ShowIfLocalUnknown?"true":"false");
      dbg += SSS;

   // byte ba_Schedule []
      SSS.Format ("ba_Schedule[].size = %d:\n", d_ba_Schedule.GetSize());
      dbg += SSS;
      for (int iba_Schedule=0; iba_Schedule<d_ba_Schedule.GetSize(); iba_Schedule++)
      {
         SSS.Format ("   ba_Schedule[%d] = %d\n", iba_Schedule, d_ba_Schedule[iba_Schedule]);
         dbg += SSS;
      }

   // int AutoOn
      SSS.Format ("AutoOn = %d\n", d_AutoOn);
      dbg += SSS;

   // int AutoOff
      SSS.Format ("AutoOff = %d\n", d_AutoOff);
      dbg += SSS;

   // int RepeatCount
      SSS.Format ("RepeatCount = %d\n", d_RepeatCount);
      dbg += SSS;

   // int RepeatTime
      SSS.Format ("RepeatTime = %d\n", d_RepeatTime);
      dbg += SSS;

   // identifier SiteTarget_SiteID []
      SSS.Format ("SiteTarget_SiteID[].size = %d:\n", d_SiteTarget_SiteID.GetSize());
      dbg += SSS;
      for (int iSiteTarget_SiteID=0; iSiteTarget_SiteID<d_SiteTarget_SiteID.GetSize(); iSiteTarget_SiteID++)
      {
         SSS.Format ("   SiteTarget_SiteID[%d] = %d\n", iSiteTarget_SiteID, d_SiteTarget_SiteID[iSiteTarget_SiteID]);
         dbg += SSS;
      }

   // int SiteTarget_ShowRate []
      SSS.Format ("SiteTarget_ShowRate[].size = %d:\n", d_SiteTarget_ShowRate.GetSize());
      dbg += SSS;
      for (int iSiteTarget_ShowRate=0; iSiteTarget_ShowRate<d_SiteTarget_ShowRate.GetSize(); iSiteTarget_ShowRate++)
      {
         SSS.Format ("   SiteTarget_ShowRate[%d] = %d\n", iSiteTarget_ShowRate, d_SiteTarget_ShowRate[iSiteTarget_ShowRate]);
         dbg += SSS;
      }

   // int SiteTarget_ClickRate []
      SSS.Format ("SiteTarget_ClickRate[].size = %d:\n", d_SiteTarget_ClickRate.GetSize());
      dbg += SSS;
      for (int iSiteTarget_ClickRate=0; iSiteTarget_ClickRate<d_SiteTarget_ClickRate.GetSize(); iSiteTarget_ClickRate++)
      {
         SSS.Format ("   SiteTarget_ClickRate[%d] = %d\n", iSiteTarget_ClickRate, d_SiteTarget_ClickRate[iSiteTarget_ClickRate]);
         dbg += SSS;
      }

   // int SiteTarget_ViewRate []
      SSS.Format ("SiteTarget_ViewRate[].size = %d:\n", d_SiteTarget_ViewRate.GetSize());
      dbg += SSS;
      for (int iSiteTarget_ViewRate=0; iSiteTarget_ViewRate<d_SiteTarget_ViewRate.GetSize(); iSiteTarget_ViewRate++)
      {
         SSS.Format ("   SiteTarget_ViewRate[%d] = %d\n", iSiteTarget_ViewRate, d_SiteTarget_ViewRate[iSiteTarget_ViewRate]);
         dbg += SSS;
      }

   // int ViewerConceptRate []
      SSS.Format ("ViewerConceptRate[].size = %d:\n", d_ViewerConceptRate.GetSize());
      dbg += SSS;
      for (int iViewerConceptRate=0; iViewerConceptRate<d_ViewerConceptRate.GetSize(); iViewerConceptRate++)
      {
         SSS.Format ("   ViewerConceptRate[%d] = %d\n", iViewerConceptRate, d_ViewerConceptRate[iViewerConceptRate]);
         dbg += SSS;
      }

   // int ShowNumRate []
      SSS.Format ("ShowNumRate[].size = %d:\n", d_ShowNumRate.GetSize());
      dbg += SSS;
      for (int iShowNumRate=0; iShowNumRate<d_ShowNumRate.GetSize(); iShowNumRate++)
      {
         SSS.Format ("   ShowNumRate[%d] = %d\n", iShowNumRate, d_ShowNumRate[iShowNumRate]);
         dbg += SSS;
      }

   // int ClickNumRate []
      SSS.Format ("ClickNumRate[].size = %d:\n", d_ClickNumRate.GetSize());
      dbg += SSS;
      for (int iClickNumRate=0; iClickNumRate<d_ClickNumRate.GetSize(); iClickNumRate++)
      {
         SSS.Format ("   ClickNumRate[%d] = %d\n", iClickNumRate, d_ClickNumRate[iClickNumRate]);
         dbg += SSS;
      }

   // int HitNumRate []
      SSS.Format ("HitNumRate[].size = %d:\n", d_HitNumRate.GetSize());
      dbg += SSS;
      for (int iHitNumRate=0; iHitNumRate<d_HitNumRate.GetSize(); iHitNumRate++)
      {
         SSS.Format ("   HitNumRate[%d] = %d\n", iHitNumRate, d_HitNumRate[iHitNumRate]);
         dbg += SSS;
      }

   // int SessionTimeRate []
      SSS.Format ("SessionTimeRate[].size = %d:\n", d_SessionTimeRate.GetSize());
      dbg += SSS;
      for (int iSessionTimeRate=0; iSessionTimeRate<d_SessionTimeRate.GetSize(); iSessionTimeRate++)
      {
         SSS.Format ("   SessionTimeRate[%d] = %d\n", iSessionTimeRate, d_SessionTimeRate[iSessionTimeRate]);
         dbg += SSS;
      }

   // bool CountTypeByShows
      SSS.Format ("CountTypeByShows = %s\n", d_CountTypeByShows?"true":"false");
      dbg += SSS;

   // int MaxDailyClicks
      SSS.Format ("MaxDailyClicks = %d\n", d_MaxDailyClicks);
      dbg += SSS;

   // int MaxDailyShows
      SSS.Format ("MaxDailyShows = %d\n", d_MaxDailyShows);
      dbg += SSS;

   // int MaxDailyShowsChangeTime
      SSS.Format ("MaxDailyShowsChangeTime = %d\n", d_MaxDailyShowsChangeTime);
      dbg += SSS;

   // int TotalShows
      SSS.Format ("TotalShows = %d\n", d_TotalShows);
      dbg += SSS;

   // int TotalClicks
      SSS.Format ("TotalClicks = %d\n", d_TotalClicks);
      dbg += SSS;

   // int SessionEvents
      SSS.Format ("SessionEvents = %d\n", d_SessionEvents);
      dbg += SSS;

   // float Priority
      SSS.Format ("Priority = %f\n", d_Priority);
      dbg += SSS;

   // bool Allowed
      SSS.Format ("Allowed = %s\n", d_Allowed?"true":"false");
      dbg += SSS;

   // byte ObjectState
      SSS.Format ("ObjectState = %d\n", d_ObjectState);
      dbg += SSS;

   // byte ba_ModeratorComment []
      SSS.Format ("ba_ModeratorComment[].size = %d:\n", d_ba_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iba_ModeratorComment=0; iba_ModeratorComment<d_ba_ModeratorComment.GetSize(); iba_ModeratorComment++)
      {
         SSS.Format ("   ba_ModeratorComment[%d] = %d\n", iba_ModeratorComment, d_ba_ModeratorComment[iba_ModeratorComment]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Page::OD_Page (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Page;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Site = NA;
      d_No = -1;
      d_ba_Concept.Alloc (0);
      d_eba_Concept.Alloc (0);
      d_pba_Concept.Alloc (0);
      d_CounterType = 0;
      d_ConceptSet = false;
      d_TimeStats.Alloc (0);
      d_TimeStatsType.Alloc (0);
      d_CRA_Visitor.Alloc (0);
      d_CRN_Visitor.Alloc (0);
      d_CRN_Visitor_Update = 0;
      d_CRN_VisitorIncr.Alloc (0);
      d_CRN_VisitorIncr_Update = 0;
      d_Referrer.Alloc (0);
      d_ReferrerCount.Alloc (0);
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_Page::~OD_Page () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Page::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Site;                        break;
         case 2: ka += d_No;                          break;
         case 3: ka += d_URL;                         break;
         case 7: ka += d_CounterType;                 break;
         case 8: ka += d_ConceptSet;                  break;
         case 13: ka += d_CRN_Visitor_Update;          break;
         case 15: ka += d_CRN_VisitorIncr_Update;      break;
         case 18: ka += d_TagID;                       break;
         case 19: ka += d_TagInt;                      break;
         case 20: ka += d_TagBool;                     break;
         case 24: ka += d_CacheTime;                   break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Page::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier Site
      d_Site = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int No
      d_No = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL];
      memcpy (s_URL, (file+nOffset), n_URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // byte ba_Concept []
      int arr_size_ba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Concept.Alloc (arr_size_ba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      int arr_size_eba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_Concept.Alloc (arr_size_eba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_Concept);

   // byte pba_Concept []
      int arr_size_pba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_pba_Concept.Alloc (arr_size_pba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,pba_Concept);

   // int CounterType
      d_CounterType = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool ConceptSet
      d_ConceptSet = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier TimeStats []
      int arr_size_TimeStats = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_TimeStats.Alloc (arr_size_TimeStats);
      OD_LOAD_SIMPLE_ARRAY (identifier,TimeStats);

   // byte TimeStatsType []
      int arr_size_TimeStatsType = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_TimeStatsType.Alloc (arr_size_TimeStatsType);
      OD_LOAD_SIMPLE_ARRAY (byte,TimeStatsType);

   // int CRA_Visitor []
      int arr_size_CRA_Visitor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Visitor.Alloc (arr_size_CRA_Visitor);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Visitor);

   // int CRN_Visitor []
      int arr_size_CRN_Visitor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Visitor.Alloc (arr_size_CRN_Visitor);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Visitor);

   // int CRN_Visitor_Update
      d_CRN_Visitor_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CRN_VisitorIncr []
      int arr_size_CRN_VisitorIncr = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_VisitorIncr.Alloc (arr_size_CRN_VisitorIncr);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_VisitorIncr);

   // int CRN_VisitorIncr_Update
      d_CRN_VisitorIncr_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Referrer []
      int arr_size_Referrer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Referrer.Alloc (arr_size_Referrer);
      OD_LOAD_SIMPLE_ARRAY (identifier,Referrer);

   // int ReferrerCount []
      int arr_size_ReferrerCount = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReferrerCount.Alloc (arr_size_ReferrerCount);
      OD_LOAD_SIMPLE_ARRAY (int,ReferrerCount);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Page::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier Site
      n_size += sizeof (identifier);

   // int No
      n_size += sizeof (int);

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // byte ba_Concept []
      n_size += sizeof (size_t);
      n_size += d_ba_Concept.GetSize() * sizeof(byte);

   // byte eba_Concept []
      n_size += sizeof (size_t);
      n_size += d_eba_Concept.GetSize() * sizeof(byte);

   // byte pba_Concept []
      n_size += sizeof (size_t);
      n_size += d_pba_Concept.GetSize() * sizeof(byte);

   // int CounterType
      n_size += sizeof (int);

   // bool ConceptSet
      n_size += sizeof (bool);

   // identifier TimeStats []
      n_size += sizeof (size_t);
      n_size += d_TimeStats.GetSize() * sizeof(identifier);

   // byte TimeStatsType []
      n_size += sizeof (size_t);
      n_size += d_TimeStatsType.GetSize() * sizeof(byte);

   // int CRA_Visitor []
      n_size += sizeof (size_t);
      n_size += d_CRA_Visitor.GetSize() * sizeof(int);

   // int CRN_Visitor []
      n_size += sizeof (size_t);
      n_size += d_CRN_Visitor.GetSize() * sizeof(int);

   // int CRN_Visitor_Update
      n_size += sizeof (int);

   // int CRN_VisitorIncr []
      n_size += sizeof (size_t);
      n_size += d_CRN_VisitorIncr.GetSize() * sizeof(int);

   // int CRN_VisitorIncr_Update
      n_size += sizeof (int);

   // identifier Referrer []
      n_size += sizeof (size_t);
      n_size += d_Referrer.GetSize() * sizeof(identifier);

   // int ReferrerCount []
      n_size += sizeof (size_t);
      n_size += d_ReferrerCount.GetSize() * sizeof(int);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Page::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier Site
      (*(identifier*)(file+nOffset)) = d_Site;
      nOffset += sizeof (identifier);

   // int No
      (*(int*)(file+nOffset)) = d_No;
      nOffset += sizeof (int);

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // byte ba_Concept []
      (*(size_t*)(file+nOffset)) = d_ba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Concept);

   // byte eba_Concept []
      (*(size_t*)(file+nOffset)) = d_eba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_Concept);

   // byte pba_Concept []
      (*(size_t*)(file+nOffset)) = d_pba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,pba_Concept);

   // int CounterType
      (*(int*)(file+nOffset)) = d_CounterType;
      nOffset += sizeof (int);

   // bool ConceptSet
      (*(bool*)(file+nOffset)) = d_ConceptSet;
      nOffset += sizeof (bool);

   // identifier TimeStats []
      (*(size_t*)(file+nOffset)) = d_TimeStats.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,TimeStats);

   // byte TimeStatsType []
      (*(size_t*)(file+nOffset)) = d_TimeStatsType.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,TimeStatsType);

   // int CRA_Visitor []
      (*(size_t*)(file+nOffset)) = d_CRA_Visitor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Visitor);

   // int CRN_Visitor []
      (*(size_t*)(file+nOffset)) = d_CRN_Visitor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Visitor);

   // int CRN_Visitor_Update
      (*(int*)(file+nOffset)) = d_CRN_Visitor_Update;
      nOffset += sizeof (int);

   // int CRN_VisitorIncr []
      (*(size_t*)(file+nOffset)) = d_CRN_VisitorIncr.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_VisitorIncr);

   // int CRN_VisitorIncr_Update
      (*(int*)(file+nOffset)) = d_CRN_VisitorIncr_Update;
      nOffset += sizeof (int);

   // identifier Referrer []
      (*(size_t*)(file+nOffset)) = d_Referrer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Referrer);

   // int ReferrerCount []
      (*(size_t*)(file+nOffset)) = d_ReferrerCount.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReferrerCount);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Page::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Page], objID);
      dbg += SSS;

   // identifier Site
      SSS.Format ("Site = %d\n", d_Site);
      dbg += SSS;

   // int No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // byte ba_Concept []
      SSS.Format ("ba_Concept[].size = %d:\n", d_ba_Concept.GetSize());
      dbg += SSS;
      for (int iba_Concept=0; iba_Concept<d_ba_Concept.GetSize(); iba_Concept++)
      {
         SSS.Format ("   ba_Concept[%d] = %d\n", iba_Concept, d_ba_Concept[iba_Concept]);
         dbg += SSS;
      }

   // byte eba_Concept []
      SSS.Format ("eba_Concept[].size = %d:\n", d_eba_Concept.GetSize());
      dbg += SSS;
      for (int ieba_Concept=0; ieba_Concept<d_eba_Concept.GetSize(); ieba_Concept++)
      {
         SSS.Format ("   eba_Concept[%d] = %d\n", ieba_Concept, d_eba_Concept[ieba_Concept]);
         dbg += SSS;
      }

   // byte pba_Concept []
      SSS.Format ("pba_Concept[].size = %d:\n", d_pba_Concept.GetSize());
      dbg += SSS;
      for (int ipba_Concept=0; ipba_Concept<d_pba_Concept.GetSize(); ipba_Concept++)
      {
         SSS.Format ("   pba_Concept[%d] = %d\n", ipba_Concept, d_pba_Concept[ipba_Concept]);
         dbg += SSS;
      }

   // int CounterType
      SSS.Format ("CounterType = %d\n", d_CounterType);
      dbg += SSS;

   // bool ConceptSet
      SSS.Format ("ConceptSet = %s\n", d_ConceptSet?"true":"false");
      dbg += SSS;

   // identifier TimeStats []
      SSS.Format ("TimeStats[].size = %d:\n", d_TimeStats.GetSize());
      dbg += SSS;
      for (int iTimeStats=0; iTimeStats<d_TimeStats.GetSize(); iTimeStats++)
      {
         SSS.Format ("   TimeStats[%d] = %d\n", iTimeStats, d_TimeStats[iTimeStats]);
         dbg += SSS;
      }

   // byte TimeStatsType []
      SSS.Format ("TimeStatsType[].size = %d:\n", d_TimeStatsType.GetSize());
      dbg += SSS;
      for (int iTimeStatsType=0; iTimeStatsType<d_TimeStatsType.GetSize(); iTimeStatsType++)
      {
         SSS.Format ("   TimeStatsType[%d] = %d\n", iTimeStatsType, d_TimeStatsType[iTimeStatsType]);
         dbg += SSS;
      }

   // int CRA_Visitor []
      SSS.Format ("CRA_Visitor[].size = %d:\n", d_CRA_Visitor.GetSize());
      dbg += SSS;
      for (int iCRA_Visitor=0; iCRA_Visitor<d_CRA_Visitor.GetSize(); iCRA_Visitor++)
      {
         SSS.Format ("   CRA_Visitor[%d] = %d\n", iCRA_Visitor, d_CRA_Visitor[iCRA_Visitor]);
         dbg += SSS;
      }

   // int CRN_Visitor []
      SSS.Format ("CRN_Visitor[].size = %d:\n", d_CRN_Visitor.GetSize());
      dbg += SSS;
      for (int iCRN_Visitor=0; iCRN_Visitor<d_CRN_Visitor.GetSize(); iCRN_Visitor++)
      {
         SSS.Format ("   CRN_Visitor[%d] = %d\n", iCRN_Visitor, d_CRN_Visitor[iCRN_Visitor]);
         dbg += SSS;
      }

   // int CRN_Visitor_Update
      SSS.Format ("CRN_Visitor_Update = %d\n", d_CRN_Visitor_Update);
      dbg += SSS;

   // int CRN_VisitorIncr []
      SSS.Format ("CRN_VisitorIncr[].size = %d:\n", d_CRN_VisitorIncr.GetSize());
      dbg += SSS;
      for (int iCRN_VisitorIncr=0; iCRN_VisitorIncr<d_CRN_VisitorIncr.GetSize(); iCRN_VisitorIncr++)
      {
         SSS.Format ("   CRN_VisitorIncr[%d] = %d\n", iCRN_VisitorIncr, d_CRN_VisitorIncr[iCRN_VisitorIncr]);
         dbg += SSS;
      }

   // int CRN_VisitorIncr_Update
      SSS.Format ("CRN_VisitorIncr_Update = %d\n", d_CRN_VisitorIncr_Update);
      dbg += SSS;

   // identifier Referrer []
      SSS.Format ("Referrer[].size = %d:\n", d_Referrer.GetSize());
      dbg += SSS;
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         SSS.Format ("   Referrer[%d] = %d\n", iReferrer, d_Referrer[iReferrer]);
         dbg += SSS;
      }

   // int ReferrerCount []
      SSS.Format ("ReferrerCount[].size = %d:\n", d_ReferrerCount.GetSize());
      dbg += SSS;
      for (int iReferrerCount=0; iReferrerCount<d_ReferrerCount.GetSize(); iReferrerCount++)
      {
         SSS.Format ("   ReferrerCount[%d] = %d\n", iReferrerCount, d_ReferrerCount[iReferrerCount]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Site::OD_Site (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Site;


      m_CoIndexPtr = new OBD_pointer [105];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      m_CoIndexPtr[5] = NULL;
      m_CoIndexPtr[6] = NULL;
      m_CoIndexPtr[7] = NULL;
      m_CoIndexPtr[8] = NULL;
      m_CoIndexPtr[9] = NULL;
      m_CoIndexPtr[10] = NULL;
      m_CoIndexPtr[11] = NULL;
      m_CoIndexPtr[12] = NULL;
      m_CoIndexPtr[13] = NULL;
      m_CoIndexPtr[14] = NULL;
      m_CoIndexPtr[15] = NULL;
      m_CoIndexPtr[16] = NULL;
      m_CoIndexPtr[17] = NULL;
      m_CoIndexPtr[18] = NULL;
      m_CoIndexPtr[19] = NULL;
      m_CoIndexPtr[20] = NULL;
      m_CoIndexPtr[21] = NULL;
      m_CoIndexPtr[22] = NULL;
      m_CoIndexPtr[23] = NULL;
      m_CoIndexPtr[24] = NULL;
      m_CoIndexPtr[25] = NULL;
      m_CoIndexPtr[26] = NULL;
      m_CoIndexPtr[27] = NULL;
      m_CoIndexPtr[28] = NULL;
      m_CoIndexPtr[29] = NULL;
      m_CoIndexPtr[30] = NULL;
      m_CoIndexPtr[31] = NULL;
      m_CoIndexPtr[32] = NULL;
      m_CoIndexPtr[33] = NULL;
      m_CoIndexPtr[34] = NULL;
      m_CoIndexPtr[35] = NULL;
      m_CoIndexPtr[36] = NULL;
      m_CoIndexPtr[37] = NULL;
      m_CoIndexPtr[38] = NULL;
      m_CoIndexPtr[39] = NULL;
      m_CoIndexPtr[40] = NULL;
      m_CoIndexPtr[41] = NULL;
      m_CoIndexPtr[42] = NULL;
      m_CoIndexPtr[43] = NULL;
      m_CoIndexPtr[44] = NULL;
      m_CoIndexPtr[45] = NULL;
      m_CoIndexPtr[46] = NULL;
      m_CoIndexPtr[47] = NULL;
      m_CoIndexPtr[48] = NULL;
      m_CoIndexPtr[49] = NULL;
      m_CoIndexPtr[50] = NULL;
      m_CoIndexPtr[51] = NULL;
      m_CoIndexPtr[52] = NULL;
      m_CoIndexPtr[53] = NULL;
      m_CoIndexPtr[54] = NULL;
      m_CoIndexPtr[55] = NULL;
      m_CoIndexPtr[56] = NULL;
      m_CoIndexPtr[57] = NULL;
      m_CoIndexPtr[58] = NULL;
      m_CoIndexPtr[59] = NULL;
      m_CoIndexPtr[60] = NULL;
      m_CoIndexPtr[61] = NULL;
      m_CoIndexPtr[62] = NULL;
      m_CoIndexPtr[63] = NULL;
      m_CoIndexPtr[64] = NULL;
      m_CoIndexPtr[65] = NULL;
      m_CoIndexPtr[66] = NULL;
      m_CoIndexPtr[67] = NULL;
      m_CoIndexPtr[68] = NULL;
      m_CoIndexPtr[69] = NULL;
      m_CoIndexPtr[70] = NULL;
      m_CoIndexPtr[71] = NULL;
      m_CoIndexPtr[72] = NULL;
      m_CoIndexPtr[73] = NULL;
      m_CoIndexPtr[74] = NULL;
      m_CoIndexPtr[75] = NULL;
      m_CoIndexPtr[76] = NULL;
      m_CoIndexPtr[77] = NULL;
      m_CoIndexPtr[78] = NULL;
      m_CoIndexPtr[79] = NULL;
      m_CoIndexPtr[80] = NULL;
      m_CoIndexPtr[81] = NULL;
      m_CoIndexPtr[82] = NULL;
      m_CoIndexPtr[83] = NULL;
      m_CoIndexPtr[84] = NULL;
      m_CoIndexPtr[85] = NULL;
      m_CoIndexPtr[86] = NULL;
      m_CoIndexPtr[87] = NULL;
      m_CoIndexPtr[88] = NULL;
      m_CoIndexPtr[89] = NULL;
      m_CoIndexPtr[90] = NULL;
      m_CoIndexPtr[91] = NULL;
      m_CoIndexPtr[92] = NULL;
      m_CoIndexPtr[93] = NULL;
      m_CoIndexPtr[94] = NULL;
      m_CoIndexPtr[95] = NULL;
      m_CoIndexPtr[96] = NULL;
      m_CoIndexPtr[97] = NULL;
      m_CoIndexPtr[98] = NULL;
      m_CoIndexPtr[99] = NULL;
      m_CoIndexPtr[100] = NULL;
      m_CoIndexPtr[101] = NULL;
      m_CoIndexPtr[102] = NULL;
      m_CoIndexPtr[103] = NULL;
      m_CoIndexPtr[104] = NULL;
      if (!bFieldsInit) return;

      d_OwnerID = NA;
      d_VBN = 255;
      d_CreationTime = 0;
      d_Announce.Alloc (0);
      d_CounterType = 0;
      d_RateMySite = true;
      d_ShowAudience = true;
      d_ShowAudienceOffTime = 0;
      d_Profile = NA;
      d_Keyword.Alloc (0);
      d_MirrorInclude.Alloc (0);
      d_MirrorExclude.Alloc (0);
      d_MirrorSubstr.Alloc (0);
      d_IgnoredIP.Alloc (0);
      d_IgnoredViewerID.Alloc (0);
      d_ba_Concept.Alloc (0);
      d_pba_Concept.Alloc (0);
      d_eba_Concept.Alloc (0);
      d_CRN_Self.Alloc (0);
      d_Page.Alloc (0);
      d_PageName.Alloc (0);
      d_PageNo.Alloc (0);
      d_AdBannerProfile.Alloc (0);
      d_SuspiciousInfo = NA;
      d_CRA_Visitor.Alloc (0);
      d_CRN_Visitor.Alloc (0);
      d_CRN_Visitor_Update = 0;
      d_CRA_Inquiry.Alloc (0);
      d_CRN_Inquiry.Alloc (0);
      d_CRN_VisitorIncr.Alloc (0);
      d_CRN_VisitorIncr_Update = 0;
      d_Audience_SiteID.Alloc (0);
      d_Audience_Viewers.Alloc (0);
      d_Audience_Hosts.Alloc (0);
      d_Audience_SiteIDInclude.Alloc (0);
      d_ActiveViewersID.Alloc (0);
      d_ActiveViewersHits.Alloc (0);
      d_RecentPointer = 0;
      d_RecentVisitor.Alloc (0);
      d_RecentReferrer.Alloc (0);
      d_RecentTimeStamp.Alloc (0);
      d_Referrer.Alloc (0);
      d_ReferrerCount.Alloc (0);
      d_Referrer_LastReset = 0;
      d_DailyReferrerStats.Alloc (0);
      d_DailyReferrerTimeStamp.Alloc (0);
      d_SearchWordsInfo = NA;
      d_Inquire.Alloc (0);
      d_InquiredVisitorNum = 0;
      d_SessionResetTime = 0;
      d_ReturnNumRate.Alloc (0);
      d_ShowNumRate.Alloc (0);
      d_LastVisitTime = 0;
      d_LastUpdateTime = 0;
      d_Loads = NA;
      d_Visitors = NA;
      d_Hosts = NA;
      d_Shows = NA;
      d_Clicks = NA;
      d_Clicks_Local = NA;
      d_Hits = NA;
      d_Hits_Local = NA;
      d_AnonymousHits = NA;
      d_SuspiciousHits = NA;
      d_SessionTime = NA;
      d_SessionTime_Local = NA;
      d_SessionNum = NA;
      d_Total_Loads = 0;
      d_Total_Hosts = 0;
      d_Total_Hits = 0;
      d_Total_AnonymousHits = 0;
      d_Total_AnonymousHits_Prc = 0;
      d_Total_SuspiciousHits_Prc = 0;
      d_Total_Visitors = 0;
      d_Total_VisitorReturns = 0;
      d_Total_VisitorReturns_Prc = 0;
      d_Total_SessionNum = 0;
      d_Total_AveSessionTime = 0;
      d_Total_AveReloadTime = 0;
      d_Total_AveReloadNum = 0;
      d_Total_Shows = 0;
      d_Total_Clicks = 0;
      d_Total_CTR_Prc = 0;
      d_Total_CPH_Prc = 0;
      d_Total_AnonymousVisitors = 0;
      d_Total_AnonymousVisitors_Prc = 0;
      d_Total_VisitorExperience = 0;
      d_Ave_VisitorExperience = 0;
      d_OnlineVisitors = 0;
      d_Total_MouseOver = 0;
      d_Total_Votes = 0;
      d_Total_Votes_Sum = 0;
      d_Total_Votes_Ave = 0;
      d_LM_Loads = 0;
      d_LM_Hosts = 0;
      d_LM_Hits = 0;
      d_LM_AnonymousHits = 0;
      d_LM_AnonymousHits_Prc = 0;
      d_LM_SuspiciousHits_Prc = 0;
      d_LM_Visitors = 0;
      d_LM_VisitorReturns = 0;
      d_LM_VisitorReturns_Prc = 0;
      d_LM_SessionNum = 0;
      d_LM_AveSessionTime = 0;
      d_LM_AveReloadTime = 0;
      d_LM_AveReloadNum = 0;
      d_LM_Shows = 0;
      d_LM_Clicks = 0;
      d_LM_CTR_Prc = 0;
      d_LM_CPH_Prc = 0;
      d_LW_Loads = 0;
      d_LW_Hosts = 0;
      d_LW_Hits = 0;
      d_LW_AnonymousHits = 0;
      d_LW_AnonymousHits_Prc = 0;
      d_LW_SuspiciousHits_Prc = 0;
      d_LW_Visitors = 0;
      d_LW_VisitorReturns = 0;
      d_LW_VisitorReturns_Prc = 0;
      d_LW_SessionNum = 0;
      d_LW_AveSessionTime = 0;
      d_LW_AveReloadTime = 0;
      d_LW_AveReloadNum = 0;
      d_LW_Shows = 0;
      d_LW_Clicks = 0;
      d_LW_CTR_Prc = 0;
      d_LW_CPH_Prc = 0;
      d_LD_Loads = 0;
      d_LD_Hosts = 0;
      d_LD_Hits = 0;
      d_LD_AnonymousHits = 0;
      d_LD_AnonymousHits_Prc = 0;
      d_LD_SuspiciousHits_Prc = 0;
      d_LD_Visitors = 0;
      d_LD_VisitorReturns = 0;
      d_LD_VisitorReturns_Prc = 0;
      d_LD_SessionNum = 0;
      d_LD_AveSessionTime = 0;
      d_LD_AveReloadTime = 0;
      d_LD_AveReloadNum = 0;
      d_LD_Shows = 0;
      d_LD_Clicks = 0;
      d_LD_CTR_Prc = 0;
      d_LD_CPH_Prc = 0;
      d_LH_Loads = 0;
      d_LH_Hosts = 0;
      d_LH_Hits = 0;
      d_LH_AnonymousHits = 0;
      d_LH_AnonymousHits_Prc = 0;
      d_LH_SuspiciousHits_Prc = 0;
      d_LH_Visitors = 0;
      d_LH_VisitorReturns = 0;
      d_LH_VisitorReturns_Prc = 0;
      d_LH_SessionNum = 0;
      d_LH_AveSessionTime = 0;
      d_LH_AveReloadTime = 0;
      d_LH_AveReloadNum = 0;
      d_LH_Shows = 0;
      d_LH_Clicks = 0;
      d_LH_CTR_Prc = 0;
      d_LH_CPH_Prc = 0;
      d_CustomIndex1 = 0;
      d_CustomIndex2 = 0;
      d_CustomIndex3 = 0;
      d_CustomIndex4 = 0;
      d_CustomIndex5 = 0;
      d_Allowed = false;
      d_ObjectState = 1;
      d_ba_ModeratorComment.Alloc (0);
      d_TagID = NA;
      d_TagBool = false;
      d_TagInt = 0;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_RatingPlaceInfo = NA;
      d_CacheTime = 0;
   }

// Деструктор
  OD_Site::~OD_Site () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Site::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_OwnerID;                          break;
         case 2: ka += d_VBN;                              break;
         case 3: ka += d_CreationTime;                     break;
         case 4: ka += d_Alias;                            break;
         case 5: ka += d_Name;                             break;
         case 6: ka += d_Description;                      break;
         case 8: ka += d_URL;                              break;
         case 9: ka += d_CounterType;                      break;
         case 10: ka += d_RateMySite;                       break;
         case 11: ka += d_RateStatsViewPassword;            break;
         case 12: ka += d_ShowAudience;                     break;
         case 13: ka += d_ShowAudienceOffTime;              break;
         case 14: ka += d_Profile;                          break;
         case 29: ka += d_SuspiciousInfo;                   break;
         case 32: ka += d_CRN_Visitor_Update;               break;
         case 36: ka += d_CRN_VisitorIncr_Update;           break;
         case 43: ka += d_RecentPointer;                    break;
         case 49: ka += d_Referrer_LastReset;               break;
         case 52: ka += d_SearchWordsInfo;                  break;
         case 54: ka += d_InquiredVisitorNum;               break;
         case 55: ka += d_SessionResetTime;                 break;
         case 58: ka += d_LastVisitTime;                    break;
         case 59: ka += d_LastUpdateTime;                   break;
         case 60: ka += d_Loads;                            break;
         case 61: ka += d_Visitors;                         break;
         case 62: ka += d_Hosts;                            break;
         case 63: ka += d_Shows;                            break;
         case 64: ka += d_Clicks;                           break;
         case 65: ka += d_Clicks_Local;                     break;
         case 66: ka += d_Hits;                             break;
         case 67: ka += d_Hits_Local;                       break;
         case 68: ka += d_AnonymousHits;                    break;
         case 69: ka += d_SuspiciousHits;                   break;
         case 70: ka += d_SessionTime;                      break;
         case 71: ka += d_SessionTime_Local;                break;
         case 72: ka += d_SessionNum;                       break;
         case 73: ka += d_Total_Loads;                      break;
         case 74: ka += d_Total_Hosts;                      break;
         case 75: ka += d_Total_Hits;                       break;
         case 76: ka += d_Total_AnonymousHits;              break;
         case 77: ka += d_Total_AnonymousHits_Prc;          break;
         case 78: ka += d_Total_SuspiciousHits_Prc;         break;
         case 79: ka += d_Total_Visitors;                   break;
         case 80: ka += d_Total_VisitorReturns;             break;
         case 81: ka += d_Total_VisitorReturns_Prc;         break;
         case 82: ka += d_Total_SessionNum;                 break;
         case 83: ka += d_Total_AveSessionTime;             break;
         case 84: ka += d_Total_AveReloadTime;              break;
         case 85: ka += d_Total_AveReloadNum;               break;
         case 86: ka += d_Total_Shows;                      break;
         case 87: ka += d_Total_Clicks;                     break;
         case 88: ka += d_Total_CTR_Prc;                    break;
         case 89: ka += d_Total_CPH_Prc;                    break;
         case 90: ka += d_Total_AnonymousVisitors;          break;
         case 91: ka += d_Total_AnonymousVisitors_Prc;      break;
         case 92: ka += d_Total_VisitorExperience;          break;
         case 93: ka += d_Ave_VisitorExperience;            break;
         case 94: ka += d_OnlineVisitors;                   break;
         case 95: ka += d_Total_MouseOver;                  break;
         case 96: ka += d_Total_Votes;                      break;
         case 97: ka += d_Total_Votes_Sum;                  break;
         case 98: ka += d_Total_Votes_Ave;                  break;
         case 99: ka += d_LM_Loads;                         break;
         case 100: ka += d_LM_Hosts;                         break;
         case 101: ka += d_LM_Hits;                          break;
         case 102: ka += d_LM_AnonymousHits;                 break;
         case 103: ka += d_LM_AnonymousHits_Prc;             break;
         case 104: ka += d_LM_SuspiciousHits_Prc;            break;
         case 105: ka += d_LM_Visitors;                      break;
         case 106: ka += d_LM_VisitorReturns;                break;
         case 107: ka += d_LM_VisitorReturns_Prc;            break;
         case 108: ka += d_LM_SessionNum;                    break;
         case 109: ka += d_LM_AveSessionTime;                break;
         case 110: ka += d_LM_AveReloadTime;                 break;
         case 111: ka += d_LM_AveReloadNum;                  break;
         case 112: ka += d_LM_Shows;                         break;
         case 113: ka += d_LM_Clicks;                        break;
         case 114: ka += d_LM_CTR_Prc;                       break;
         case 115: ka += d_LM_CPH_Prc;                       break;
         case 116: ka += d_LW_Loads;                         break;
         case 117: ka += d_LW_Hosts;                         break;
         case 118: ka += d_LW_Hits;                          break;
         case 119: ka += d_LW_AnonymousHits;                 break;
         case 120: ka += d_LW_AnonymousHits_Prc;             break;
         case 121: ka += d_LW_SuspiciousHits_Prc;            break;
         case 122: ka += d_LW_Visitors;                      break;
         case 123: ka += d_LW_VisitorReturns;                break;
         case 124: ka += d_LW_VisitorReturns_Prc;            break;
         case 125: ka += d_LW_SessionNum;                    break;
         case 126: ka += d_LW_AveSessionTime;                break;
         case 127: ka += d_LW_AveReloadTime;                 break;
         case 128: ka += d_LW_AveReloadNum;                  break;
         case 129: ka += d_LW_Shows;                         break;
         case 130: ka += d_LW_Clicks;                        break;
         case 131: ka += d_LW_CTR_Prc;                       break;
         case 132: ka += d_LW_CPH_Prc;                       break;
         case 133: ka += d_LD_Loads;                         break;
         case 134: ka += d_LD_Hosts;                         break;
         case 135: ka += d_LD_Hits;                          break;
         case 136: ka += d_LD_AnonymousHits;                 break;
         case 137: ka += d_LD_AnonymousHits_Prc;             break;
         case 138: ka += d_LD_SuspiciousHits_Prc;            break;
         case 139: ka += d_LD_Visitors;                      break;
         case 140: ka += d_LD_VisitorReturns;                break;
         case 141: ka += d_LD_VisitorReturns_Prc;            break;
         case 142: ka += d_LD_SessionNum;                    break;
         case 143: ka += d_LD_AveSessionTime;                break;
         case 144: ka += d_LD_AveReloadTime;                 break;
         case 145: ka += d_LD_AveReloadNum;                  break;
         case 146: ka += d_LD_Shows;                         break;
         case 147: ka += d_LD_Clicks;                        break;
         case 148: ka += d_LD_CTR_Prc;                       break;
         case 149: ka += d_LD_CPH_Prc;                       break;
         case 150: ka += d_LH_Loads;                         break;
         case 151: ka += d_LH_Hosts;                         break;
         case 152: ka += d_LH_Hits;                          break;
         case 153: ka += d_LH_AnonymousHits;                 break;
         case 154: ka += d_LH_AnonymousHits_Prc;             break;
         case 155: ka += d_LH_SuspiciousHits_Prc;            break;
         case 156: ka += d_LH_Visitors;                      break;
         case 157: ka += d_LH_VisitorReturns;                break;
         case 158: ka += d_LH_VisitorReturns_Prc;            break;
         case 159: ka += d_LH_SessionNum;                    break;
         case 160: ka += d_LH_AveSessionTime;                break;
         case 161: ka += d_LH_AveReloadTime;                 break;
         case 162: ka += d_LH_AveReloadNum;                  break;
         case 163: ka += d_LH_Shows;                         break;
         case 164: ka += d_LH_Clicks;                        break;
         case 165: ka += d_LH_CTR_Prc;                       break;
         case 166: ka += d_LH_CPH_Prc;                       break;
         case 167: ka += d_CustomIndex1;                     break;
         case 168: ka += d_CustomIndex2;                     break;
         case 169: ka += d_CustomIndex3;                     break;
         case 170: ka += d_CustomIndex4;                     break;
         case 171: ka += d_CustomIndex5;                     break;
         case 172: ka += d_Allowed;                          break;
         case 173: ka += d_ObjectState;                      break;
         case 175: ka += d_TagID;                            break;
         case 176: ka += d_TagBool;                          break;
         case 177: ka += d_TagInt;                           break;
         case 181: ka += d_RatingPlaceInfo;                  break;
         case 182: ka += d_CacheTime;                        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Site::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier OwnerID
      d_OwnerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // byte VBN
      d_VBN = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string Alias
      size_t n_Alias = (*(size_t*)(file+nOffset));  // n_Alias = strlen (s_Alias)+1;
      nOffset += sizeof(size_t);
      char * s_Alias = new char [n_Alias];
      memcpy (s_Alias, (file+nOffset), n_Alias);
      nOffset += n_Alias;
      DECODE_STRING (n_Alias, s_Alias);
      d_Alias = s_Alias;
      delete [] s_Alias;

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description];
      memcpy (s_Description, (file+nOffset), n_Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // string Announce []
      int arr_size_Announce = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Announce.Alloc (arr_size_Announce);
      for (int iAnnounce=0; iAnnounce<(int)arr_size_Announce; iAnnounce++)
      {
         string tmp_Announce;
         size_t n_Announce = (*(size_t*)(file+nOffset));  // n_Announce = strlen (s_Announce)+1;
         nOffset += sizeof(size_t);
         char * s_Announce = new char [n_Announce];
         memcpy (s_Announce, (file+nOffset), n_Announce);
         nOffset += n_Announce;
         DECODE_STRING (n_Announce, s_Announce);
         tmp_Announce = s_Announce;
         delete [] s_Announce;

         d_Announce[iAnnounce] = tmp_Announce;
      }

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL];
      memcpy (s_URL, (file+nOffset), n_URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // int CounterType
      d_CounterType = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool RateMySite
      d_RateMySite = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // string RateStatsViewPassword
      size_t n_RateStatsViewPassword = (*(size_t*)(file+nOffset));  // n_RateStatsViewPassword = strlen (s_RateStatsViewPassword)+1;
      nOffset += sizeof(size_t);
      char * s_RateStatsViewPassword = new char [n_RateStatsViewPassword];
      memcpy (s_RateStatsViewPassword, (file+nOffset), n_RateStatsViewPassword);
      nOffset += n_RateStatsViewPassword;
      DECODE_STRING (n_RateStatsViewPassword, s_RateStatsViewPassword);
      d_RateStatsViewPassword = s_RateStatsViewPassword;
      delete [] s_RateStatsViewPassword;

   // bool ShowAudience
      d_ShowAudience = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int ShowAudienceOffTime
      d_ShowAudienceOffTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Profile
      d_Profile = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Keyword []
      int arr_size_Keyword = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Keyword.Alloc (arr_size_Keyword);
      OD_LOAD_SIMPLE_ARRAY (identifier,Keyword);

   // string MirrorInclude []
      int arr_size_MirrorInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_MirrorInclude.Alloc (arr_size_MirrorInclude);
      for (int iMirrorInclude=0; iMirrorInclude<(int)arr_size_MirrorInclude; iMirrorInclude++)
      {
         string tmp_MirrorInclude;
         size_t n_MirrorInclude = (*(size_t*)(file+nOffset));  // n_MirrorInclude = strlen (s_MirrorInclude)+1;
         nOffset += sizeof(size_t);
         char * s_MirrorInclude = new char [n_MirrorInclude];
         memcpy (s_MirrorInclude, (file+nOffset), n_MirrorInclude);
         nOffset += n_MirrorInclude;
         DECODE_STRING (n_MirrorInclude, s_MirrorInclude);
         tmp_MirrorInclude = s_MirrorInclude;
         delete [] s_MirrorInclude;

         d_MirrorInclude[iMirrorInclude] = tmp_MirrorInclude;
      }

   // string MirrorExclude []
      int arr_size_MirrorExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_MirrorExclude.Alloc (arr_size_MirrorExclude);
      for (int iMirrorExclude=0; iMirrorExclude<(int)arr_size_MirrorExclude; iMirrorExclude++)
      {
         string tmp_MirrorExclude;
         size_t n_MirrorExclude = (*(size_t*)(file+nOffset));  // n_MirrorExclude = strlen (s_MirrorExclude)+1;
         nOffset += sizeof(size_t);
         char * s_MirrorExclude = new char [n_MirrorExclude];
         memcpy (s_MirrorExclude, (file+nOffset), n_MirrorExclude);
         nOffset += n_MirrorExclude;
         DECODE_STRING (n_MirrorExclude, s_MirrorExclude);
         tmp_MirrorExclude = s_MirrorExclude;
         delete [] s_MirrorExclude;

         d_MirrorExclude[iMirrorExclude] = tmp_MirrorExclude;
      }

   // string MirrorSubstr []
      int arr_size_MirrorSubstr = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_MirrorSubstr.Alloc (arr_size_MirrorSubstr);
      for (int iMirrorSubstr=0; iMirrorSubstr<(int)arr_size_MirrorSubstr; iMirrorSubstr++)
      {
         string tmp_MirrorSubstr;
         size_t n_MirrorSubstr = (*(size_t*)(file+nOffset));  // n_MirrorSubstr = strlen (s_MirrorSubstr)+1;
         nOffset += sizeof(size_t);
         char * s_MirrorSubstr = new char [n_MirrorSubstr];
         memcpy (s_MirrorSubstr, (file+nOffset), n_MirrorSubstr);
         nOffset += n_MirrorSubstr;
         DECODE_STRING (n_MirrorSubstr, s_MirrorSubstr);
         tmp_MirrorSubstr = s_MirrorSubstr;
         delete [] s_MirrorSubstr;

         d_MirrorSubstr[iMirrorSubstr] = tmp_MirrorSubstr;
      }

   // string IgnoredIP []
      int arr_size_IgnoredIP = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_IgnoredIP.Alloc (arr_size_IgnoredIP);
      for (int iIgnoredIP=0; iIgnoredIP<(int)arr_size_IgnoredIP; iIgnoredIP++)
      {
         string tmp_IgnoredIP;
         size_t n_IgnoredIP = (*(size_t*)(file+nOffset));  // n_IgnoredIP = strlen (s_IgnoredIP)+1;
         nOffset += sizeof(size_t);
         char * s_IgnoredIP = new char [n_IgnoredIP];
         memcpy (s_IgnoredIP, (file+nOffset), n_IgnoredIP);
         nOffset += n_IgnoredIP;
         DECODE_STRING (n_IgnoredIP, s_IgnoredIP);
         tmp_IgnoredIP = s_IgnoredIP;
         delete [] s_IgnoredIP;

         d_IgnoredIP[iIgnoredIP] = tmp_IgnoredIP;
      }

   // identifier IgnoredViewerID []
      int arr_size_IgnoredViewerID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_IgnoredViewerID.Alloc (arr_size_IgnoredViewerID);
      OD_LOAD_SIMPLE_ARRAY (identifier,IgnoredViewerID);

   // byte ba_Concept []
      int arr_size_ba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_Concept.Alloc (arr_size_ba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_Concept);

   // byte pba_Concept []
      int arr_size_pba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_pba_Concept.Alloc (arr_size_pba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,pba_Concept);

   // byte eba_Concept []
      int arr_size_eba_Concept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_Concept.Alloc (arr_size_eba_Concept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_Concept);

   // int CRN_Self []
      int arr_size_CRN_Self = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Self.Alloc (arr_size_CRN_Self);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Self);

   // identifier Page []
      int arr_size_Page = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Page.Alloc (arr_size_Page);
      OD_LOAD_SIMPLE_ARRAY (identifier,Page);

   // string PageName []
      int arr_size_PageName = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_PageName.Alloc (arr_size_PageName);
      for (int iPageName=0; iPageName<(int)arr_size_PageName; iPageName++)
      {
         string tmp_PageName;
         size_t n_PageName = (*(size_t*)(file+nOffset));  // n_PageName = strlen (s_PageName)+1;
         nOffset += sizeof(size_t);
         char * s_PageName = new char [n_PageName];
         memcpy (s_PageName, (file+nOffset), n_PageName);
         nOffset += n_PageName;
         DECODE_STRING (n_PageName, s_PageName);
         tmp_PageName = s_PageName;
         delete [] s_PageName;

         d_PageName[iPageName] = tmp_PageName;
      }

   // int PageNo []
      int arr_size_PageNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_PageNo.Alloc (arr_size_PageNo);
      OD_LOAD_SIMPLE_ARRAY (int,PageNo);

   // identifier AdBannerProfile []
      int arr_size_AdBannerProfile = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_AdBannerProfile.Alloc (arr_size_AdBannerProfile);
      OD_LOAD_SIMPLE_ARRAY (identifier,AdBannerProfile);

   // identifier SuspiciousInfo
      d_SuspiciousInfo = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CRA_Visitor []
      int arr_size_CRA_Visitor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Visitor.Alloc (arr_size_CRA_Visitor);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Visitor);

   // int CRN_Visitor []
      int arr_size_CRN_Visitor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Visitor.Alloc (arr_size_CRN_Visitor);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Visitor);

   // int CRN_Visitor_Update
      d_CRN_Visitor_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CRA_Inquiry []
      int arr_size_CRA_Inquiry = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Inquiry.Alloc (arr_size_CRA_Inquiry);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CRN_Inquiry []
      int arr_size_CRN_Inquiry = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_Inquiry.Alloc (arr_size_CRN_Inquiry);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_Inquiry);

   // int CRN_VisitorIncr []
      int arr_size_CRN_VisitorIncr = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_VisitorIncr.Alloc (arr_size_CRN_VisitorIncr);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_VisitorIncr);

   // int CRN_VisitorIncr_Update
      d_CRN_VisitorIncr_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Audience_SiteID []
      int arr_size_Audience_SiteID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Audience_SiteID.Alloc (arr_size_Audience_SiteID);
      OD_LOAD_SIMPLE_ARRAY (identifier,Audience_SiteID);

   // int Audience_Viewers []
      int arr_size_Audience_Viewers = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Audience_Viewers.Alloc (arr_size_Audience_Viewers);
      OD_LOAD_SIMPLE_ARRAY (int,Audience_Viewers);

   // int Audience_Hosts []
      int arr_size_Audience_Hosts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Audience_Hosts.Alloc (arr_size_Audience_Hosts);
      OD_LOAD_SIMPLE_ARRAY (int,Audience_Hosts);

   // int Audience_SiteIDInclude []
      int arr_size_Audience_SiteIDInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Audience_SiteIDInclude.Alloc (arr_size_Audience_SiteIDInclude);
      OD_LOAD_SIMPLE_ARRAY (int,Audience_SiteIDInclude);

   // identifier ActiveViewersID []
      int arr_size_ActiveViewersID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ActiveViewersID.Alloc (arr_size_ActiveViewersID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ActiveViewersID);

   // int ActiveViewersHits []
      int arr_size_ActiveViewersHits = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ActiveViewersHits.Alloc (arr_size_ActiveViewersHits);
      OD_LOAD_SIMPLE_ARRAY (int,ActiveViewersHits);

   // int RecentPointer
      d_RecentPointer = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier RecentVisitor []
      int arr_size_RecentVisitor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RecentVisitor.Alloc (arr_size_RecentVisitor);
      OD_LOAD_SIMPLE_ARRAY (identifier,RecentVisitor);

   // identifier RecentReferrer []
      int arr_size_RecentReferrer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RecentReferrer.Alloc (arr_size_RecentReferrer);
      OD_LOAD_SIMPLE_ARRAY (identifier,RecentReferrer);

   // int RecentTimeStamp []
      int arr_size_RecentTimeStamp = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RecentTimeStamp.Alloc (arr_size_RecentTimeStamp);
      OD_LOAD_SIMPLE_ARRAY (int,RecentTimeStamp);

   // identifier Referrer []
      int arr_size_Referrer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Referrer.Alloc (arr_size_Referrer);
      OD_LOAD_SIMPLE_ARRAY (identifier,Referrer);

   // int ReferrerCount []
      int arr_size_ReferrerCount = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReferrerCount.Alloc (arr_size_ReferrerCount);
      OD_LOAD_SIMPLE_ARRAY (int,ReferrerCount);

   // int Referrer_LastReset
      d_Referrer_LastReset = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier DailyReferrerStats []
      int arr_size_DailyReferrerStats = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DailyReferrerStats.Alloc (arr_size_DailyReferrerStats);
      OD_LOAD_SIMPLE_ARRAY (identifier,DailyReferrerStats);

   // int DailyReferrerTimeStamp []
      int arr_size_DailyReferrerTimeStamp = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DailyReferrerTimeStamp.Alloc (arr_size_DailyReferrerTimeStamp);
      OD_LOAD_SIMPLE_ARRAY (int,DailyReferrerTimeStamp);

   // identifier SearchWordsInfo
      d_SearchWordsInfo = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Inquire []
      int arr_size_Inquire = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Inquire.Alloc (arr_size_Inquire);
      OD_LOAD_SIMPLE_ARRAY (int,Inquire);

   // int InquiredVisitorNum
      d_InquiredVisitorNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SessionResetTime
      d_SessionResetTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ReturnNumRate []
      int arr_size_ReturnNumRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReturnNumRate.Alloc (arr_size_ReturnNumRate);
      OD_LOAD_SIMPLE_ARRAY (int,ReturnNumRate);

   // int ShowNumRate []
      int arr_size_ShowNumRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ShowNumRate.Alloc (arr_size_ShowNumRate);
      OD_LOAD_SIMPLE_ARRAY (int,ShowNumRate);

   // int LastVisitTime
      d_LastVisitTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LastUpdateTime
      d_LastUpdateTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Loads
      d_Loads = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Visitors
      d_Visitors = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Hosts
      d_Hosts = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Shows
      d_Shows = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Clicks
      d_Clicks = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Clicks_Local
      d_Clicks_Local = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Hits
      d_Hits = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Hits_Local
      d_Hits_Local = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier AnonymousHits
      d_AnonymousHits = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SuspiciousHits
      d_SuspiciousHits = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SessionTime
      d_SessionTime = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SessionTime_Local
      d_SessionTime_Local = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SessionNum
      d_SessionNum = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Total_Loads
      d_Total_Loads = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Hosts
      d_Total_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Hits
      d_Total_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AnonymousHits
      d_Total_AnonymousHits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AnonymousHits_Prc
      d_Total_AnonymousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_SuspiciousHits_Prc
      d_Total_SuspiciousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Visitors
      d_Total_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_VisitorReturns
      d_Total_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_VisitorReturns_Prc
      d_Total_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_SessionNum
      d_Total_SessionNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveSessionTime
      d_Total_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveReloadTime
      d_Total_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveReloadNum
      d_Total_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Shows
      d_Total_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Clicks
      d_Total_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_CTR_Prc
      d_Total_CTR_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_CPH_Prc
      d_Total_CPH_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AnonymousVisitors
      d_Total_AnonymousVisitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AnonymousVisitors_Prc
      d_Total_AnonymousVisitors_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_VisitorExperience
      d_Total_VisitorExperience = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Ave_VisitorExperience
      d_Ave_VisitorExperience = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int OnlineVisitors
      d_OnlineVisitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_MouseOver
      d_Total_MouseOver = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Votes
      d_Total_Votes = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Votes_Sum
      d_Total_Votes_Sum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Votes_Ave
      d_Total_Votes_Ave = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Loads
      d_LM_Loads = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hosts
      d_LM_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hits
      d_LM_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AnonymousHits
      d_LM_AnonymousHits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AnonymousHits_Prc
      d_LM_AnonymousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_SuspiciousHits_Prc
      d_LM_SuspiciousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Visitors
      d_LM_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_VisitorReturns
      d_LM_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_VisitorReturns_Prc
      d_LM_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_SessionNum
      d_LM_SessionNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveSessionTime
      d_LM_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveReloadTime
      d_LM_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveReloadNum
      d_LM_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Shows
      d_LM_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Clicks
      d_LM_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_CTR_Prc
      d_LM_CTR_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_CPH_Prc
      d_LM_CPH_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Loads
      d_LW_Loads = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hosts
      d_LW_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hits
      d_LW_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AnonymousHits
      d_LW_AnonymousHits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AnonymousHits_Prc
      d_LW_AnonymousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_SuspiciousHits_Prc
      d_LW_SuspiciousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Visitors
      d_LW_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_VisitorReturns
      d_LW_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_VisitorReturns_Prc
      d_LW_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_SessionNum
      d_LW_SessionNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveSessionTime
      d_LW_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveReloadTime
      d_LW_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveReloadNum
      d_LW_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Shows
      d_LW_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Clicks
      d_LW_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_CTR_Prc
      d_LW_CTR_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_CPH_Prc
      d_LW_CPH_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Loads
      d_LD_Loads = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hosts
      d_LD_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hits
      d_LD_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AnonymousHits
      d_LD_AnonymousHits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AnonymousHits_Prc
      d_LD_AnonymousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_SuspiciousHits_Prc
      d_LD_SuspiciousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Visitors
      d_LD_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_VisitorReturns
      d_LD_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_VisitorReturns_Prc
      d_LD_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_SessionNum
      d_LD_SessionNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveSessionTime
      d_LD_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveReloadTime
      d_LD_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveReloadNum
      d_LD_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Shows
      d_LD_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Clicks
      d_LD_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_CTR_Prc
      d_LD_CTR_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_CPH_Prc
      d_LD_CPH_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Loads
      d_LH_Loads = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hosts
      d_LH_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hits
      d_LH_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AnonymousHits
      d_LH_AnonymousHits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AnonymousHits_Prc
      d_LH_AnonymousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_SuspiciousHits_Prc
      d_LH_SuspiciousHits_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Visitors
      d_LH_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_VisitorReturns
      d_LH_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_VisitorReturns_Prc
      d_LH_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_SessionNum
      d_LH_SessionNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveSessionTime
      d_LH_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveReloadTime
      d_LH_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveReloadNum
      d_LH_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Shows
      d_LH_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Clicks
      d_LH_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_CTR_Prc
      d_LH_CTR_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_CPH_Prc
      d_LH_CPH_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CustomIndex1
      d_CustomIndex1 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CustomIndex2
      d_CustomIndex2 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CustomIndex3
      d_CustomIndex3 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CustomIndex4
      d_CustomIndex4 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CustomIndex5
      d_CustomIndex5 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool Allowed
      d_Allowed = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ObjectState
      d_ObjectState = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_ModeratorComment []
      int arr_size_ba_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ModeratorComment.Alloc (arr_size_ba_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // identifier RatingPlaceInfo
      d_RatingPlaceInfo = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Site::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier OwnerID
      n_size += sizeof (identifier);

   // byte VBN
      n_size += sizeof (byte);

   // int CreationTime
      n_size += sizeof (int);

   // string Alias
      n_size += sizeof (size_t);
      n_size += d_Alias.length()+1;

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // string Announce []
      n_size += sizeof (size_t);
      for (int iAnnounce=0; iAnnounce<d_Announce.GetSize(); iAnnounce++)
      {
         n_size += sizeof (size_t);
         n_size += d_Announce[iAnnounce].length()+1;
      }

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // int CounterType
      n_size += sizeof (int);

   // bool RateMySite
      n_size += sizeof (bool);

   // string RateStatsViewPassword
      n_size += sizeof (size_t);
      n_size += d_RateStatsViewPassword.length()+1;

   // bool ShowAudience
      n_size += sizeof (bool);

   // int ShowAudienceOffTime
      n_size += sizeof (int);

   // identifier Profile
      n_size += sizeof (identifier);

   // identifier Keyword []
      n_size += sizeof (size_t);
      n_size += d_Keyword.GetSize() * sizeof(identifier);

   // string MirrorInclude []
      n_size += sizeof (size_t);
      for (int iMirrorInclude=0; iMirrorInclude<d_MirrorInclude.GetSize(); iMirrorInclude++)
      {
         n_size += sizeof (size_t);
         n_size += d_MirrorInclude[iMirrorInclude].length()+1;
      }

   // string MirrorExclude []
      n_size += sizeof (size_t);
      for (int iMirrorExclude=0; iMirrorExclude<d_MirrorExclude.GetSize(); iMirrorExclude++)
      {
         n_size += sizeof (size_t);
         n_size += d_MirrorExclude[iMirrorExclude].length()+1;
      }

   // string MirrorSubstr []
      n_size += sizeof (size_t);
      for (int iMirrorSubstr=0; iMirrorSubstr<d_MirrorSubstr.GetSize(); iMirrorSubstr++)
      {
         n_size += sizeof (size_t);
         n_size += d_MirrorSubstr[iMirrorSubstr].length()+1;
      }

   // string IgnoredIP []
      n_size += sizeof (size_t);
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         n_size += sizeof (size_t);
         n_size += d_IgnoredIP[iIgnoredIP].length()+1;
      }

   // identifier IgnoredViewerID []
      n_size += sizeof (size_t);
      n_size += d_IgnoredViewerID.GetSize() * sizeof(identifier);

   // byte ba_Concept []
      n_size += sizeof (size_t);
      n_size += d_ba_Concept.GetSize() * sizeof(byte);

   // byte pba_Concept []
      n_size += sizeof (size_t);
      n_size += d_pba_Concept.GetSize() * sizeof(byte);

   // byte eba_Concept []
      n_size += sizeof (size_t);
      n_size += d_eba_Concept.GetSize() * sizeof(byte);

   // int CRN_Self []
      n_size += sizeof (size_t);
      n_size += d_CRN_Self.GetSize() * sizeof(int);

   // identifier Page []
      n_size += sizeof (size_t);
      n_size += d_Page.GetSize() * sizeof(identifier);

   // string PageName []
      n_size += sizeof (size_t);
      for (int iPageName=0; iPageName<d_PageName.GetSize(); iPageName++)
      {
         n_size += sizeof (size_t);
         n_size += d_PageName[iPageName].length()+1;
      }

   // int PageNo []
      n_size += sizeof (size_t);
      n_size += d_PageNo.GetSize() * sizeof(int);

   // identifier AdBannerProfile []
      n_size += sizeof (size_t);
      n_size += d_AdBannerProfile.GetSize() * sizeof(identifier);

   // identifier SuspiciousInfo
      n_size += sizeof (identifier);

   // int CRA_Visitor []
      n_size += sizeof (size_t);
      n_size += d_CRA_Visitor.GetSize() * sizeof(int);

   // int CRN_Visitor []
      n_size += sizeof (size_t);
      n_size += d_CRN_Visitor.GetSize() * sizeof(int);

   // int CRN_Visitor_Update
      n_size += sizeof (int);

   // int CRA_Inquiry []
      n_size += sizeof (size_t);
      n_size += d_CRA_Inquiry.GetSize() * sizeof(int);

   // int CRN_Inquiry []
      n_size += sizeof (size_t);
      n_size += d_CRN_Inquiry.GetSize() * sizeof(int);

   // int CRN_VisitorIncr []
      n_size += sizeof (size_t);
      n_size += d_CRN_VisitorIncr.GetSize() * sizeof(int);

   // int CRN_VisitorIncr_Update
      n_size += sizeof (int);

   // identifier Audience_SiteID []
      n_size += sizeof (size_t);
      n_size += d_Audience_SiteID.GetSize() * sizeof(identifier);

   // int Audience_Viewers []
      n_size += sizeof (size_t);
      n_size += d_Audience_Viewers.GetSize() * sizeof(int);

   // int Audience_Hosts []
      n_size += sizeof (size_t);
      n_size += d_Audience_Hosts.GetSize() * sizeof(int);

   // int Audience_SiteIDInclude []
      n_size += sizeof (size_t);
      n_size += d_Audience_SiteIDInclude.GetSize() * sizeof(int);

   // identifier ActiveViewersID []
      n_size += sizeof (size_t);
      n_size += d_ActiveViewersID.GetSize() * sizeof(identifier);

   // int ActiveViewersHits []
      n_size += sizeof (size_t);
      n_size += d_ActiveViewersHits.GetSize() * sizeof(int);

   // int RecentPointer
      n_size += sizeof (int);

   // identifier RecentVisitor []
      n_size += sizeof (size_t);
      n_size += d_RecentVisitor.GetSize() * sizeof(identifier);

   // identifier RecentReferrer []
      n_size += sizeof (size_t);
      n_size += d_RecentReferrer.GetSize() * sizeof(identifier);

   // int RecentTimeStamp []
      n_size += sizeof (size_t);
      n_size += d_RecentTimeStamp.GetSize() * sizeof(int);

   // identifier Referrer []
      n_size += sizeof (size_t);
      n_size += d_Referrer.GetSize() * sizeof(identifier);

   // int ReferrerCount []
      n_size += sizeof (size_t);
      n_size += d_ReferrerCount.GetSize() * sizeof(int);

   // int Referrer_LastReset
      n_size += sizeof (int);

   // identifier DailyReferrerStats []
      n_size += sizeof (size_t);
      n_size += d_DailyReferrerStats.GetSize() * sizeof(identifier);

   // int DailyReferrerTimeStamp []
      n_size += sizeof (size_t);
      n_size += d_DailyReferrerTimeStamp.GetSize() * sizeof(int);

   // identifier SearchWordsInfo
      n_size += sizeof (identifier);

   // int Inquire []
      n_size += sizeof (size_t);
      n_size += d_Inquire.GetSize() * sizeof(int);

   // int InquiredVisitorNum
      n_size += sizeof (int);

   // int SessionResetTime
      n_size += sizeof (int);

   // int ReturnNumRate []
      n_size += sizeof (size_t);
      n_size += d_ReturnNumRate.GetSize() * sizeof(int);

   // int ShowNumRate []
      n_size += sizeof (size_t);
      n_size += d_ShowNumRate.GetSize() * sizeof(int);

   // int LastVisitTime
      n_size += sizeof (int);

   // int LastUpdateTime
      n_size += sizeof (int);

   // identifier Loads
      n_size += sizeof (identifier);

   // identifier Visitors
      n_size += sizeof (identifier);

   // identifier Hosts
      n_size += sizeof (identifier);

   // identifier Shows
      n_size += sizeof (identifier);

   // identifier Clicks
      n_size += sizeof (identifier);

   // identifier Clicks_Local
      n_size += sizeof (identifier);

   // identifier Hits
      n_size += sizeof (identifier);

   // identifier Hits_Local
      n_size += sizeof (identifier);

   // identifier AnonymousHits
      n_size += sizeof (identifier);

   // identifier SuspiciousHits
      n_size += sizeof (identifier);

   // identifier SessionTime
      n_size += sizeof (identifier);

   // identifier SessionTime_Local
      n_size += sizeof (identifier);

   // identifier SessionNum
      n_size += sizeof (identifier);

   // int Total_Loads
      n_size += sizeof (int);

   // int Total_Hosts
      n_size += sizeof (int);

   // int Total_Hits
      n_size += sizeof (int);

   // int Total_AnonymousHits
      n_size += sizeof (int);

   // int Total_AnonymousHits_Prc
      n_size += sizeof (int);

   // int Total_SuspiciousHits_Prc
      n_size += sizeof (int);

   // int Total_Visitors
      n_size += sizeof (int);

   // int Total_VisitorReturns
      n_size += sizeof (int);

   // int Total_VisitorReturns_Prc
      n_size += sizeof (int);

   // int Total_SessionNum
      n_size += sizeof (int);

   // int Total_AveSessionTime
      n_size += sizeof (int);

   // int Total_AveReloadTime
      n_size += sizeof (int);

   // int Total_AveReloadNum
      n_size += sizeof (int);

   // int Total_Shows
      n_size += sizeof (int);

   // int Total_Clicks
      n_size += sizeof (int);

   // int Total_CTR_Prc
      n_size += sizeof (int);

   // int Total_CPH_Prc
      n_size += sizeof (int);

   // int Total_AnonymousVisitors
      n_size += sizeof (int);

   // int Total_AnonymousVisitors_Prc
      n_size += sizeof (int);

   // int Total_VisitorExperience
      n_size += sizeof (int);

   // int Ave_VisitorExperience
      n_size += sizeof (int);

   // int OnlineVisitors
      n_size += sizeof (int);

   // int Total_MouseOver
      n_size += sizeof (int);

   // int Total_Votes
      n_size += sizeof (int);

   // int Total_Votes_Sum
      n_size += sizeof (int);

   // int Total_Votes_Ave
      n_size += sizeof (int);

   // int LM_Loads
      n_size += sizeof (int);

   // int LM_Hosts
      n_size += sizeof (int);

   // int LM_Hits
      n_size += sizeof (int);

   // int LM_AnonymousHits
      n_size += sizeof (int);

   // int LM_AnonymousHits_Prc
      n_size += sizeof (int);

   // int LM_SuspiciousHits_Prc
      n_size += sizeof (int);

   // int LM_Visitors
      n_size += sizeof (int);

   // int LM_VisitorReturns
      n_size += sizeof (int);

   // int LM_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LM_SessionNum
      n_size += sizeof (int);

   // int LM_AveSessionTime
      n_size += sizeof (int);

   // int LM_AveReloadTime
      n_size += sizeof (int);

   // int LM_AveReloadNum
      n_size += sizeof (int);

   // int LM_Shows
      n_size += sizeof (int);

   // int LM_Clicks
      n_size += sizeof (int);

   // int LM_CTR_Prc
      n_size += sizeof (int);

   // int LM_CPH_Prc
      n_size += sizeof (int);

   // int LW_Loads
      n_size += sizeof (int);

   // int LW_Hosts
      n_size += sizeof (int);

   // int LW_Hits
      n_size += sizeof (int);

   // int LW_AnonymousHits
      n_size += sizeof (int);

   // int LW_AnonymousHits_Prc
      n_size += sizeof (int);

   // int LW_SuspiciousHits_Prc
      n_size += sizeof (int);

   // int LW_Visitors
      n_size += sizeof (int);

   // int LW_VisitorReturns
      n_size += sizeof (int);

   // int LW_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LW_SessionNum
      n_size += sizeof (int);

   // int LW_AveSessionTime
      n_size += sizeof (int);

   // int LW_AveReloadTime
      n_size += sizeof (int);

   // int LW_AveReloadNum
      n_size += sizeof (int);

   // int LW_Shows
      n_size += sizeof (int);

   // int LW_Clicks
      n_size += sizeof (int);

   // int LW_CTR_Prc
      n_size += sizeof (int);

   // int LW_CPH_Prc
      n_size += sizeof (int);

   // int LD_Loads
      n_size += sizeof (int);

   // int LD_Hosts
      n_size += sizeof (int);

   // int LD_Hits
      n_size += sizeof (int);

   // int LD_AnonymousHits
      n_size += sizeof (int);

   // int LD_AnonymousHits_Prc
      n_size += sizeof (int);

   // int LD_SuspiciousHits_Prc
      n_size += sizeof (int);

   // int LD_Visitors
      n_size += sizeof (int);

   // int LD_VisitorReturns
      n_size += sizeof (int);

   // int LD_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LD_SessionNum
      n_size += sizeof (int);

   // int LD_AveSessionTime
      n_size += sizeof (int);

   // int LD_AveReloadTime
      n_size += sizeof (int);

   // int LD_AveReloadNum
      n_size += sizeof (int);

   // int LD_Shows
      n_size += sizeof (int);

   // int LD_Clicks
      n_size += sizeof (int);

   // int LD_CTR_Prc
      n_size += sizeof (int);

   // int LD_CPH_Prc
      n_size += sizeof (int);

   // int LH_Loads
      n_size += sizeof (int);

   // int LH_Hosts
      n_size += sizeof (int);

   // int LH_Hits
      n_size += sizeof (int);

   // int LH_AnonymousHits
      n_size += sizeof (int);

   // int LH_AnonymousHits_Prc
      n_size += sizeof (int);

   // int LH_SuspiciousHits_Prc
      n_size += sizeof (int);

   // int LH_Visitors
      n_size += sizeof (int);

   // int LH_VisitorReturns
      n_size += sizeof (int);

   // int LH_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LH_SessionNum
      n_size += sizeof (int);

   // int LH_AveSessionTime
      n_size += sizeof (int);

   // int LH_AveReloadTime
      n_size += sizeof (int);

   // int LH_AveReloadNum
      n_size += sizeof (int);

   // int LH_Shows
      n_size += sizeof (int);

   // int LH_Clicks
      n_size += sizeof (int);

   // int LH_CTR_Prc
      n_size += sizeof (int);

   // int LH_CPH_Prc
      n_size += sizeof (int);

   // int CustomIndex1
      n_size += sizeof (int);

   // int CustomIndex2
      n_size += sizeof (int);

   // int CustomIndex3
      n_size += sizeof (int);

   // int CustomIndex4
      n_size += sizeof (int);

   // int CustomIndex5
      n_size += sizeof (int);

   // bool Allowed
      n_size += sizeof (bool);

   // byte ObjectState
      n_size += sizeof (byte);

   // byte ba_ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ba_ModeratorComment.GetSize() * sizeof(byte);

   // identifier TagID
      n_size += sizeof (identifier);

   // bool TagBool
      n_size += sizeof (bool);

   // int TagInt
      n_size += sizeof (int);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // identifier RatingPlaceInfo
      n_size += sizeof (identifier);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Site::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier OwnerID
      (*(identifier*)(file+nOffset)) = d_OwnerID;
      nOffset += sizeof (identifier);

   // byte VBN
      (*(byte*)(file+nOffset)) = d_VBN;
      nOffset += sizeof (byte);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // string Alias
      size_t n_Alias = d_Alias.length()+1;
      (*(size_t*)(file+nOffset)) = n_Alias;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Alias.c_str(), n_Alias);
      ENCODE_STRING (n_Alias, (char*)(file+nOffset));
      nOffset += n_Alias;

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Description
      size_t n_Description = d_Description.length()+1;
      (*(size_t*)(file+nOffset)) = n_Description;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Description.c_str(), n_Description);
      ENCODE_STRING (n_Description, (char*)(file+nOffset));
      nOffset += n_Description;

   // string Announce []
      (*(size_t*)(file+nOffset)) = d_Announce.GetSize();
      nOffset += sizeof(size_t);
      for (int iAnnounce=0; iAnnounce<d_Announce.GetSize(); iAnnounce++)
      {
         size_t n_Announce = d_Announce[iAnnounce].length()+1;
         (*(size_t*)(file+nOffset)) = n_Announce;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Announce[iAnnounce].c_str(), n_Announce);
         ENCODE_STRING (n_Announce, (char*)(file+nOffset));
         nOffset += n_Announce;
      }

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // int CounterType
      (*(int*)(file+nOffset)) = d_CounterType;
      nOffset += sizeof (int);

   // bool RateMySite
      (*(bool*)(file+nOffset)) = d_RateMySite;
      nOffset += sizeof (bool);

   // string RateStatsViewPassword
      size_t n_RateStatsViewPassword = d_RateStatsViewPassword.length()+1;
      (*(size_t*)(file+nOffset)) = n_RateStatsViewPassword;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_RateStatsViewPassword.c_str(), n_RateStatsViewPassword);
      ENCODE_STRING (n_RateStatsViewPassword, (char*)(file+nOffset));
      nOffset += n_RateStatsViewPassword;

   // bool ShowAudience
      (*(bool*)(file+nOffset)) = d_ShowAudience;
      nOffset += sizeof (bool);

   // int ShowAudienceOffTime
      (*(int*)(file+nOffset)) = d_ShowAudienceOffTime;
      nOffset += sizeof (int);

   // identifier Profile
      (*(identifier*)(file+nOffset)) = d_Profile;
      nOffset += sizeof (identifier);

   // identifier Keyword []
      (*(size_t*)(file+nOffset)) = d_Keyword.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Keyword);

   // string MirrorInclude []
      (*(size_t*)(file+nOffset)) = d_MirrorInclude.GetSize();
      nOffset += sizeof(size_t);
      for (int iMirrorInclude=0; iMirrorInclude<d_MirrorInclude.GetSize(); iMirrorInclude++)
      {
         size_t n_MirrorInclude = d_MirrorInclude[iMirrorInclude].length()+1;
         (*(size_t*)(file+nOffset)) = n_MirrorInclude;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_MirrorInclude[iMirrorInclude].c_str(), n_MirrorInclude);
         ENCODE_STRING (n_MirrorInclude, (char*)(file+nOffset));
         nOffset += n_MirrorInclude;
      }

   // string MirrorExclude []
      (*(size_t*)(file+nOffset)) = d_MirrorExclude.GetSize();
      nOffset += sizeof(size_t);
      for (int iMirrorExclude=0; iMirrorExclude<d_MirrorExclude.GetSize(); iMirrorExclude++)
      {
         size_t n_MirrorExclude = d_MirrorExclude[iMirrorExclude].length()+1;
         (*(size_t*)(file+nOffset)) = n_MirrorExclude;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_MirrorExclude[iMirrorExclude].c_str(), n_MirrorExclude);
         ENCODE_STRING (n_MirrorExclude, (char*)(file+nOffset));
         nOffset += n_MirrorExclude;
      }

   // string MirrorSubstr []
      (*(size_t*)(file+nOffset)) = d_MirrorSubstr.GetSize();
      nOffset += sizeof(size_t);
      for (int iMirrorSubstr=0; iMirrorSubstr<d_MirrorSubstr.GetSize(); iMirrorSubstr++)
      {
         size_t n_MirrorSubstr = d_MirrorSubstr[iMirrorSubstr].length()+1;
         (*(size_t*)(file+nOffset)) = n_MirrorSubstr;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_MirrorSubstr[iMirrorSubstr].c_str(), n_MirrorSubstr);
         ENCODE_STRING (n_MirrorSubstr, (char*)(file+nOffset));
         nOffset += n_MirrorSubstr;
      }

   // string IgnoredIP []
      (*(size_t*)(file+nOffset)) = d_IgnoredIP.GetSize();
      nOffset += sizeof(size_t);
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         size_t n_IgnoredIP = d_IgnoredIP[iIgnoredIP].length()+1;
         (*(size_t*)(file+nOffset)) = n_IgnoredIP;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_IgnoredIP[iIgnoredIP].c_str(), n_IgnoredIP);
         ENCODE_STRING (n_IgnoredIP, (char*)(file+nOffset));
         nOffset += n_IgnoredIP;
      }

   // identifier IgnoredViewerID []
      (*(size_t*)(file+nOffset)) = d_IgnoredViewerID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,IgnoredViewerID);

   // byte ba_Concept []
      (*(size_t*)(file+nOffset)) = d_ba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_Concept);

   // byte pba_Concept []
      (*(size_t*)(file+nOffset)) = d_pba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,pba_Concept);

   // byte eba_Concept []
      (*(size_t*)(file+nOffset)) = d_eba_Concept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_Concept);

   // int CRN_Self []
      (*(size_t*)(file+nOffset)) = d_CRN_Self.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Self);

   // identifier Page []
      (*(size_t*)(file+nOffset)) = d_Page.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Page);

   // string PageName []
      (*(size_t*)(file+nOffset)) = d_PageName.GetSize();
      nOffset += sizeof(size_t);
      for (int iPageName=0; iPageName<d_PageName.GetSize(); iPageName++)
      {
         size_t n_PageName = d_PageName[iPageName].length()+1;
         (*(size_t*)(file+nOffset)) = n_PageName;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_PageName[iPageName].c_str(), n_PageName);
         ENCODE_STRING (n_PageName, (char*)(file+nOffset));
         nOffset += n_PageName;
      }

   // int PageNo []
      (*(size_t*)(file+nOffset)) = d_PageNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,PageNo);

   // identifier AdBannerProfile []
      (*(size_t*)(file+nOffset)) = d_AdBannerProfile.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,AdBannerProfile);

   // identifier SuspiciousInfo
      (*(identifier*)(file+nOffset)) = d_SuspiciousInfo;
      nOffset += sizeof (identifier);

   // int CRA_Visitor []
      (*(size_t*)(file+nOffset)) = d_CRA_Visitor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Visitor);

   // int CRN_Visitor []
      (*(size_t*)(file+nOffset)) = d_CRN_Visitor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Visitor);

   // int CRN_Visitor_Update
      (*(int*)(file+nOffset)) = d_CRN_Visitor_Update;
      nOffset += sizeof (int);

   // int CRA_Inquiry []
      (*(size_t*)(file+nOffset)) = d_CRA_Inquiry.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CRN_Inquiry []
      (*(size_t*)(file+nOffset)) = d_CRN_Inquiry.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_Inquiry);

   // int CRN_VisitorIncr []
      (*(size_t*)(file+nOffset)) = d_CRN_VisitorIncr.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_VisitorIncr);

   // int CRN_VisitorIncr_Update
      (*(int*)(file+nOffset)) = d_CRN_VisitorIncr_Update;
      nOffset += sizeof (int);

   // identifier Audience_SiteID []
      (*(size_t*)(file+nOffset)) = d_Audience_SiteID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Audience_SiteID);

   // int Audience_Viewers []
      (*(size_t*)(file+nOffset)) = d_Audience_Viewers.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Audience_Viewers);

   // int Audience_Hosts []
      (*(size_t*)(file+nOffset)) = d_Audience_Hosts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Audience_Hosts);

   // int Audience_SiteIDInclude []
      (*(size_t*)(file+nOffset)) = d_Audience_SiteIDInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Audience_SiteIDInclude);

   // identifier ActiveViewersID []
      (*(size_t*)(file+nOffset)) = d_ActiveViewersID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ActiveViewersID);

   // int ActiveViewersHits []
      (*(size_t*)(file+nOffset)) = d_ActiveViewersHits.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ActiveViewersHits);

   // int RecentPointer
      (*(int*)(file+nOffset)) = d_RecentPointer;
      nOffset += sizeof (int);

   // identifier RecentVisitor []
      (*(size_t*)(file+nOffset)) = d_RecentVisitor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,RecentVisitor);

   // identifier RecentReferrer []
      (*(size_t*)(file+nOffset)) = d_RecentReferrer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,RecentReferrer);

   // int RecentTimeStamp []
      (*(size_t*)(file+nOffset)) = d_RecentTimeStamp.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,RecentTimeStamp);

   // identifier Referrer []
      (*(size_t*)(file+nOffset)) = d_Referrer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Referrer);

   // int ReferrerCount []
      (*(size_t*)(file+nOffset)) = d_ReferrerCount.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReferrerCount);

   // int Referrer_LastReset
      (*(int*)(file+nOffset)) = d_Referrer_LastReset;
      nOffset += sizeof (int);

   // identifier DailyReferrerStats []
      (*(size_t*)(file+nOffset)) = d_DailyReferrerStats.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,DailyReferrerStats);

   // int DailyReferrerTimeStamp []
      (*(size_t*)(file+nOffset)) = d_DailyReferrerTimeStamp.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,DailyReferrerTimeStamp);

   // identifier SearchWordsInfo
      (*(identifier*)(file+nOffset)) = d_SearchWordsInfo;
      nOffset += sizeof (identifier);

   // int Inquire []
      (*(size_t*)(file+nOffset)) = d_Inquire.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Inquire);

   // int InquiredVisitorNum
      (*(int*)(file+nOffset)) = d_InquiredVisitorNum;
      nOffset += sizeof (int);

   // int SessionResetTime
      (*(int*)(file+nOffset)) = d_SessionResetTime;
      nOffset += sizeof (int);

   // int ReturnNumRate []
      (*(size_t*)(file+nOffset)) = d_ReturnNumRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReturnNumRate);

   // int ShowNumRate []
      (*(size_t*)(file+nOffset)) = d_ShowNumRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ShowNumRate);

   // int LastVisitTime
      (*(int*)(file+nOffset)) = d_LastVisitTime;
      nOffset += sizeof (int);

   // int LastUpdateTime
      (*(int*)(file+nOffset)) = d_LastUpdateTime;
      nOffset += sizeof (int);

   // identifier Loads
      (*(identifier*)(file+nOffset)) = d_Loads;
      nOffset += sizeof (identifier);

   // identifier Visitors
      (*(identifier*)(file+nOffset)) = d_Visitors;
      nOffset += sizeof (identifier);

   // identifier Hosts
      (*(identifier*)(file+nOffset)) = d_Hosts;
      nOffset += sizeof (identifier);

   // identifier Shows
      (*(identifier*)(file+nOffset)) = d_Shows;
      nOffset += sizeof (identifier);

   // identifier Clicks
      (*(identifier*)(file+nOffset)) = d_Clicks;
      nOffset += sizeof (identifier);

   // identifier Clicks_Local
      (*(identifier*)(file+nOffset)) = d_Clicks_Local;
      nOffset += sizeof (identifier);

   // identifier Hits
      (*(identifier*)(file+nOffset)) = d_Hits;
      nOffset += sizeof (identifier);

   // identifier Hits_Local
      (*(identifier*)(file+nOffset)) = d_Hits_Local;
      nOffset += sizeof (identifier);

   // identifier AnonymousHits
      (*(identifier*)(file+nOffset)) = d_AnonymousHits;
      nOffset += sizeof (identifier);

   // identifier SuspiciousHits
      (*(identifier*)(file+nOffset)) = d_SuspiciousHits;
      nOffset += sizeof (identifier);

   // identifier SessionTime
      (*(identifier*)(file+nOffset)) = d_SessionTime;
      nOffset += sizeof (identifier);

   // identifier SessionTime_Local
      (*(identifier*)(file+nOffset)) = d_SessionTime_Local;
      nOffset += sizeof (identifier);

   // identifier SessionNum
      (*(identifier*)(file+nOffset)) = d_SessionNum;
      nOffset += sizeof (identifier);

   // int Total_Loads
      (*(int*)(file+nOffset)) = d_Total_Loads;
      nOffset += sizeof (int);

   // int Total_Hosts
      (*(int*)(file+nOffset)) = d_Total_Hosts;
      nOffset += sizeof (int);

   // int Total_Hits
      (*(int*)(file+nOffset)) = d_Total_Hits;
      nOffset += sizeof (int);

   // int Total_AnonymousHits
      (*(int*)(file+nOffset)) = d_Total_AnonymousHits;
      nOffset += sizeof (int);

   // int Total_AnonymousHits_Prc
      (*(int*)(file+nOffset)) = d_Total_AnonymousHits_Prc;
      nOffset += sizeof (int);

   // int Total_SuspiciousHits_Prc
      (*(int*)(file+nOffset)) = d_Total_SuspiciousHits_Prc;
      nOffset += sizeof (int);

   // int Total_Visitors
      (*(int*)(file+nOffset)) = d_Total_Visitors;
      nOffset += sizeof (int);

   // int Total_VisitorReturns
      (*(int*)(file+nOffset)) = d_Total_VisitorReturns;
      nOffset += sizeof (int);

   // int Total_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_Total_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int Total_SessionNum
      (*(int*)(file+nOffset)) = d_Total_SessionNum;
      nOffset += sizeof (int);

   // int Total_AveSessionTime
      (*(int*)(file+nOffset)) = d_Total_AveSessionTime;
      nOffset += sizeof (int);

   // int Total_AveReloadTime
      (*(int*)(file+nOffset)) = d_Total_AveReloadTime;
      nOffset += sizeof (int);

   // int Total_AveReloadNum
      (*(int*)(file+nOffset)) = d_Total_AveReloadNum;
      nOffset += sizeof (int);

   // int Total_Shows
      (*(int*)(file+nOffset)) = d_Total_Shows;
      nOffset += sizeof (int);

   // int Total_Clicks
      (*(int*)(file+nOffset)) = d_Total_Clicks;
      nOffset += sizeof (int);

   // int Total_CTR_Prc
      (*(int*)(file+nOffset)) = d_Total_CTR_Prc;
      nOffset += sizeof (int);

   // int Total_CPH_Prc
      (*(int*)(file+nOffset)) = d_Total_CPH_Prc;
      nOffset += sizeof (int);

   // int Total_AnonymousVisitors
      (*(int*)(file+nOffset)) = d_Total_AnonymousVisitors;
      nOffset += sizeof (int);

   // int Total_AnonymousVisitors_Prc
      (*(int*)(file+nOffset)) = d_Total_AnonymousVisitors_Prc;
      nOffset += sizeof (int);

   // int Total_VisitorExperience
      (*(int*)(file+nOffset)) = d_Total_VisitorExperience;
      nOffset += sizeof (int);

   // int Ave_VisitorExperience
      (*(int*)(file+nOffset)) = d_Ave_VisitorExperience;
      nOffset += sizeof (int);

   // int OnlineVisitors
      (*(int*)(file+nOffset)) = d_OnlineVisitors;
      nOffset += sizeof (int);

   // int Total_MouseOver
      (*(int*)(file+nOffset)) = d_Total_MouseOver;
      nOffset += sizeof (int);

   // int Total_Votes
      (*(int*)(file+nOffset)) = d_Total_Votes;
      nOffset += sizeof (int);

   // int Total_Votes_Sum
      (*(int*)(file+nOffset)) = d_Total_Votes_Sum;
      nOffset += sizeof (int);

   // int Total_Votes_Ave
      (*(int*)(file+nOffset)) = d_Total_Votes_Ave;
      nOffset += sizeof (int);

   // int LM_Loads
      (*(int*)(file+nOffset)) = d_LM_Loads;
      nOffset += sizeof (int);

   // int LM_Hosts
      (*(int*)(file+nOffset)) = d_LM_Hosts;
      nOffset += sizeof (int);

   // int LM_Hits
      (*(int*)(file+nOffset)) = d_LM_Hits;
      nOffset += sizeof (int);

   // int LM_AnonymousHits
      (*(int*)(file+nOffset)) = d_LM_AnonymousHits;
      nOffset += sizeof (int);

   // int LM_AnonymousHits_Prc
      (*(int*)(file+nOffset)) = d_LM_AnonymousHits_Prc;
      nOffset += sizeof (int);

   // int LM_SuspiciousHits_Prc
      (*(int*)(file+nOffset)) = d_LM_SuspiciousHits_Prc;
      nOffset += sizeof (int);

   // int LM_Visitors
      (*(int*)(file+nOffset)) = d_LM_Visitors;
      nOffset += sizeof (int);

   // int LM_VisitorReturns
      (*(int*)(file+nOffset)) = d_LM_VisitorReturns;
      nOffset += sizeof (int);

   // int LM_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LM_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LM_SessionNum
      (*(int*)(file+nOffset)) = d_LM_SessionNum;
      nOffset += sizeof (int);

   // int LM_AveSessionTime
      (*(int*)(file+nOffset)) = d_LM_AveSessionTime;
      nOffset += sizeof (int);

   // int LM_AveReloadTime
      (*(int*)(file+nOffset)) = d_LM_AveReloadTime;
      nOffset += sizeof (int);

   // int LM_AveReloadNum
      (*(int*)(file+nOffset)) = d_LM_AveReloadNum;
      nOffset += sizeof (int);

   // int LM_Shows
      (*(int*)(file+nOffset)) = d_LM_Shows;
      nOffset += sizeof (int);

   // int LM_Clicks
      (*(int*)(file+nOffset)) = d_LM_Clicks;
      nOffset += sizeof (int);

   // int LM_CTR_Prc
      (*(int*)(file+nOffset)) = d_LM_CTR_Prc;
      nOffset += sizeof (int);

   // int LM_CPH_Prc
      (*(int*)(file+nOffset)) = d_LM_CPH_Prc;
      nOffset += sizeof (int);

   // int LW_Loads
      (*(int*)(file+nOffset)) = d_LW_Loads;
      nOffset += sizeof (int);

   // int LW_Hosts
      (*(int*)(file+nOffset)) = d_LW_Hosts;
      nOffset += sizeof (int);

   // int LW_Hits
      (*(int*)(file+nOffset)) = d_LW_Hits;
      nOffset += sizeof (int);

   // int LW_AnonymousHits
      (*(int*)(file+nOffset)) = d_LW_AnonymousHits;
      nOffset += sizeof (int);

   // int LW_AnonymousHits_Prc
      (*(int*)(file+nOffset)) = d_LW_AnonymousHits_Prc;
      nOffset += sizeof (int);

   // int LW_SuspiciousHits_Prc
      (*(int*)(file+nOffset)) = d_LW_SuspiciousHits_Prc;
      nOffset += sizeof (int);

   // int LW_Visitors
      (*(int*)(file+nOffset)) = d_LW_Visitors;
      nOffset += sizeof (int);

   // int LW_VisitorReturns
      (*(int*)(file+nOffset)) = d_LW_VisitorReturns;
      nOffset += sizeof (int);

   // int LW_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LW_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LW_SessionNum
      (*(int*)(file+nOffset)) = d_LW_SessionNum;
      nOffset += sizeof (int);

   // int LW_AveSessionTime
      (*(int*)(file+nOffset)) = d_LW_AveSessionTime;
      nOffset += sizeof (int);

   // int LW_AveReloadTime
      (*(int*)(file+nOffset)) = d_LW_AveReloadTime;
      nOffset += sizeof (int);

   // int LW_AveReloadNum
      (*(int*)(file+nOffset)) = d_LW_AveReloadNum;
      nOffset += sizeof (int);

   // int LW_Shows
      (*(int*)(file+nOffset)) = d_LW_Shows;
      nOffset += sizeof (int);

   // int LW_Clicks
      (*(int*)(file+nOffset)) = d_LW_Clicks;
      nOffset += sizeof (int);

   // int LW_CTR_Prc
      (*(int*)(file+nOffset)) = d_LW_CTR_Prc;
      nOffset += sizeof (int);

   // int LW_CPH_Prc
      (*(int*)(file+nOffset)) = d_LW_CPH_Prc;
      nOffset += sizeof (int);

   // int LD_Loads
      (*(int*)(file+nOffset)) = d_LD_Loads;
      nOffset += sizeof (int);

   // int LD_Hosts
      (*(int*)(file+nOffset)) = d_LD_Hosts;
      nOffset += sizeof (int);

   // int LD_Hits
      (*(int*)(file+nOffset)) = d_LD_Hits;
      nOffset += sizeof (int);

   // int LD_AnonymousHits
      (*(int*)(file+nOffset)) = d_LD_AnonymousHits;
      nOffset += sizeof (int);

   // int LD_AnonymousHits_Prc
      (*(int*)(file+nOffset)) = d_LD_AnonymousHits_Prc;
      nOffset += sizeof (int);

   // int LD_SuspiciousHits_Prc
      (*(int*)(file+nOffset)) = d_LD_SuspiciousHits_Prc;
      nOffset += sizeof (int);

   // int LD_Visitors
      (*(int*)(file+nOffset)) = d_LD_Visitors;
      nOffset += sizeof (int);

   // int LD_VisitorReturns
      (*(int*)(file+nOffset)) = d_LD_VisitorReturns;
      nOffset += sizeof (int);

   // int LD_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LD_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LD_SessionNum
      (*(int*)(file+nOffset)) = d_LD_SessionNum;
      nOffset += sizeof (int);

   // int LD_AveSessionTime
      (*(int*)(file+nOffset)) = d_LD_AveSessionTime;
      nOffset += sizeof (int);

   // int LD_AveReloadTime
      (*(int*)(file+nOffset)) = d_LD_AveReloadTime;
      nOffset += sizeof (int);

   // int LD_AveReloadNum
      (*(int*)(file+nOffset)) = d_LD_AveReloadNum;
      nOffset += sizeof (int);

   // int LD_Shows
      (*(int*)(file+nOffset)) = d_LD_Shows;
      nOffset += sizeof (int);

   // int LD_Clicks
      (*(int*)(file+nOffset)) = d_LD_Clicks;
      nOffset += sizeof (int);

   // int LD_CTR_Prc
      (*(int*)(file+nOffset)) = d_LD_CTR_Prc;
      nOffset += sizeof (int);

   // int LD_CPH_Prc
      (*(int*)(file+nOffset)) = d_LD_CPH_Prc;
      nOffset += sizeof (int);

   // int LH_Loads
      (*(int*)(file+nOffset)) = d_LH_Loads;
      nOffset += sizeof (int);

   // int LH_Hosts
      (*(int*)(file+nOffset)) = d_LH_Hosts;
      nOffset += sizeof (int);

   // int LH_Hits
      (*(int*)(file+nOffset)) = d_LH_Hits;
      nOffset += sizeof (int);

   // int LH_AnonymousHits
      (*(int*)(file+nOffset)) = d_LH_AnonymousHits;
      nOffset += sizeof (int);

   // int LH_AnonymousHits_Prc
      (*(int*)(file+nOffset)) = d_LH_AnonymousHits_Prc;
      nOffset += sizeof (int);

   // int LH_SuspiciousHits_Prc
      (*(int*)(file+nOffset)) = d_LH_SuspiciousHits_Prc;
      nOffset += sizeof (int);

   // int LH_Visitors
      (*(int*)(file+nOffset)) = d_LH_Visitors;
      nOffset += sizeof (int);

   // int LH_VisitorReturns
      (*(int*)(file+nOffset)) = d_LH_VisitorReturns;
      nOffset += sizeof (int);

   // int LH_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LH_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LH_SessionNum
      (*(int*)(file+nOffset)) = d_LH_SessionNum;
      nOffset += sizeof (int);

   // int LH_AveSessionTime
      (*(int*)(file+nOffset)) = d_LH_AveSessionTime;
      nOffset += sizeof (int);

   // int LH_AveReloadTime
      (*(int*)(file+nOffset)) = d_LH_AveReloadTime;
      nOffset += sizeof (int);

   // int LH_AveReloadNum
      (*(int*)(file+nOffset)) = d_LH_AveReloadNum;
      nOffset += sizeof (int);

   // int LH_Shows
      (*(int*)(file+nOffset)) = d_LH_Shows;
      nOffset += sizeof (int);

   // int LH_Clicks
      (*(int*)(file+nOffset)) = d_LH_Clicks;
      nOffset += sizeof (int);

   // int LH_CTR_Prc
      (*(int*)(file+nOffset)) = d_LH_CTR_Prc;
      nOffset += sizeof (int);

   // int LH_CPH_Prc
      (*(int*)(file+nOffset)) = d_LH_CPH_Prc;
      nOffset += sizeof (int);

   // int CustomIndex1
      (*(int*)(file+nOffset)) = d_CustomIndex1;
      nOffset += sizeof (int);

   // int CustomIndex2
      (*(int*)(file+nOffset)) = d_CustomIndex2;
      nOffset += sizeof (int);

   // int CustomIndex3
      (*(int*)(file+nOffset)) = d_CustomIndex3;
      nOffset += sizeof (int);

   // int CustomIndex4
      (*(int*)(file+nOffset)) = d_CustomIndex4;
      nOffset += sizeof (int);

   // int CustomIndex5
      (*(int*)(file+nOffset)) = d_CustomIndex5;
      nOffset += sizeof (int);

   // bool Allowed
      (*(bool*)(file+nOffset)) = d_Allowed;
      nOffset += sizeof (bool);

   // byte ObjectState
      (*(byte*)(file+nOffset)) = d_ObjectState;
      nOffset += sizeof (byte);

   // byte ba_ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ba_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // identifier RatingPlaceInfo
      (*(identifier*)(file+nOffset)) = d_RatingPlaceInfo;
      nOffset += sizeof (identifier);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Site::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Site], objID);
      dbg += SSS;

   // identifier OwnerID
      SSS.Format ("OwnerID = %d\n", d_OwnerID);
      dbg += SSS;

   // byte VBN
      SSS.Format ("VBN = %d\n", d_VBN);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // string Alias
      SSS.Format ("Alias = '%s'\n", d_Alias.c_str());
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // string Announce []
      SSS.Format ("Announce[].size = %d:\n", d_Announce.GetSize());
      dbg += SSS;
      for (int iAnnounce=0; iAnnounce<d_Announce.GetSize(); iAnnounce++)
      {
         SSS.Format ("   Announce[%d] = '%s'\n", iAnnounce, d_Announce[iAnnounce].c_str());
         dbg += SSS;
      }

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // int CounterType
      SSS.Format ("CounterType = %d\n", d_CounterType);
      dbg += SSS;

   // bool RateMySite
      SSS.Format ("RateMySite = %s\n", d_RateMySite?"true":"false");
      dbg += SSS;

   // string RateStatsViewPassword
      SSS.Format ("RateStatsViewPassword = '%s'\n", d_RateStatsViewPassword.c_str());
      dbg += SSS;

   // bool ShowAudience
      SSS.Format ("ShowAudience = %s\n", d_ShowAudience?"true":"false");
      dbg += SSS;

   // int ShowAudienceOffTime
      SSS.Format ("ShowAudienceOffTime = %d\n", d_ShowAudienceOffTime);
      dbg += SSS;

   // identifier Profile
      SSS.Format ("Profile = %d\n", d_Profile);
      dbg += SSS;

   // identifier Keyword []
      SSS.Format ("Keyword[].size = %d:\n", d_Keyword.GetSize());
      dbg += SSS;
      for (int iKeyword=0; iKeyword<d_Keyword.GetSize(); iKeyword++)
      {
         SSS.Format ("   Keyword[%d] = %d\n", iKeyword, d_Keyword[iKeyword]);
         dbg += SSS;
      }

   // string MirrorInclude []
      SSS.Format ("MirrorInclude[].size = %d:\n", d_MirrorInclude.GetSize());
      dbg += SSS;
      for (int iMirrorInclude=0; iMirrorInclude<d_MirrorInclude.GetSize(); iMirrorInclude++)
      {
         SSS.Format ("   MirrorInclude[%d] = '%s'\n", iMirrorInclude, d_MirrorInclude[iMirrorInclude].c_str());
         dbg += SSS;
      }

   // string MirrorExclude []
      SSS.Format ("MirrorExclude[].size = %d:\n", d_MirrorExclude.GetSize());
      dbg += SSS;
      for (int iMirrorExclude=0; iMirrorExclude<d_MirrorExclude.GetSize(); iMirrorExclude++)
      {
         SSS.Format ("   MirrorExclude[%d] = '%s'\n", iMirrorExclude, d_MirrorExclude[iMirrorExclude].c_str());
         dbg += SSS;
      }

   // string MirrorSubstr []
      SSS.Format ("MirrorSubstr[].size = %d:\n", d_MirrorSubstr.GetSize());
      dbg += SSS;
      for (int iMirrorSubstr=0; iMirrorSubstr<d_MirrorSubstr.GetSize(); iMirrorSubstr++)
      {
         SSS.Format ("   MirrorSubstr[%d] = '%s'\n", iMirrorSubstr, d_MirrorSubstr[iMirrorSubstr].c_str());
         dbg += SSS;
      }

   // string IgnoredIP []
      SSS.Format ("IgnoredIP[].size = %d:\n", d_IgnoredIP.GetSize());
      dbg += SSS;
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         SSS.Format ("   IgnoredIP[%d] = '%s'\n", iIgnoredIP, d_IgnoredIP[iIgnoredIP].c_str());
         dbg += SSS;
      }

   // identifier IgnoredViewerID []
      SSS.Format ("IgnoredViewerID[].size = %d:\n", d_IgnoredViewerID.GetSize());
      dbg += SSS;
      for (int iIgnoredViewerID=0; iIgnoredViewerID<d_IgnoredViewerID.GetSize(); iIgnoredViewerID++)
      {
         SSS.Format ("   IgnoredViewerID[%d] = %d\n", iIgnoredViewerID, d_IgnoredViewerID[iIgnoredViewerID]);
         dbg += SSS;
      }

   // byte ba_Concept []
      SSS.Format ("ba_Concept[].size = %d:\n", d_ba_Concept.GetSize());
      dbg += SSS;
      for (int iba_Concept=0; iba_Concept<d_ba_Concept.GetSize(); iba_Concept++)
      {
         SSS.Format ("   ba_Concept[%d] = %d\n", iba_Concept, d_ba_Concept[iba_Concept]);
         dbg += SSS;
      }

   // byte pba_Concept []
      SSS.Format ("pba_Concept[].size = %d:\n", d_pba_Concept.GetSize());
      dbg += SSS;
      for (int ipba_Concept=0; ipba_Concept<d_pba_Concept.GetSize(); ipba_Concept++)
      {
         SSS.Format ("   pba_Concept[%d] = %d\n", ipba_Concept, d_pba_Concept[ipba_Concept]);
         dbg += SSS;
      }

   // byte eba_Concept []
      SSS.Format ("eba_Concept[].size = %d:\n", d_eba_Concept.GetSize());
      dbg += SSS;
      for (int ieba_Concept=0; ieba_Concept<d_eba_Concept.GetSize(); ieba_Concept++)
      {
         SSS.Format ("   eba_Concept[%d] = %d\n", ieba_Concept, d_eba_Concept[ieba_Concept]);
         dbg += SSS;
      }

   // int CRN_Self []
      SSS.Format ("CRN_Self[].size = %d:\n", d_CRN_Self.GetSize());
      dbg += SSS;
      for (int iCRN_Self=0; iCRN_Self<d_CRN_Self.GetSize(); iCRN_Self++)
      {
         SSS.Format ("   CRN_Self[%d] = %d\n", iCRN_Self, d_CRN_Self[iCRN_Self]);
         dbg += SSS;
      }

   // identifier Page []
      SSS.Format ("Page[].size = %d:\n", d_Page.GetSize());
      dbg += SSS;
      for (int iPage=0; iPage<d_Page.GetSize(); iPage++)
      {
         SSS.Format ("   Page[%d] = %d\n", iPage, d_Page[iPage]);
         dbg += SSS;
      }

   // string PageName []
      SSS.Format ("PageName[].size = %d:\n", d_PageName.GetSize());
      dbg += SSS;
      for (int iPageName=0; iPageName<d_PageName.GetSize(); iPageName++)
      {
         SSS.Format ("   PageName[%d] = '%s'\n", iPageName, d_PageName[iPageName].c_str());
         dbg += SSS;
      }

   // int PageNo []
      SSS.Format ("PageNo[].size = %d:\n", d_PageNo.GetSize());
      dbg += SSS;
      for (int iPageNo=0; iPageNo<d_PageNo.GetSize(); iPageNo++)
      {
         SSS.Format ("   PageNo[%d] = %d\n", iPageNo, d_PageNo[iPageNo]);
         dbg += SSS;
      }

   // identifier AdBannerProfile []
      SSS.Format ("AdBannerProfile[].size = %d:\n", d_AdBannerProfile.GetSize());
      dbg += SSS;
      for (int iAdBannerProfile=0; iAdBannerProfile<d_AdBannerProfile.GetSize(); iAdBannerProfile++)
      {
         SSS.Format ("   AdBannerProfile[%d] = %d\n", iAdBannerProfile, d_AdBannerProfile[iAdBannerProfile]);
         dbg += SSS;
      }

   // identifier SuspiciousInfo
      SSS.Format ("SuspiciousInfo = %d\n", d_SuspiciousInfo);
      dbg += SSS;

   // int CRA_Visitor []
      SSS.Format ("CRA_Visitor[].size = %d:\n", d_CRA_Visitor.GetSize());
      dbg += SSS;
      for (int iCRA_Visitor=0; iCRA_Visitor<d_CRA_Visitor.GetSize(); iCRA_Visitor++)
      {
         SSS.Format ("   CRA_Visitor[%d] = %d\n", iCRA_Visitor, d_CRA_Visitor[iCRA_Visitor]);
         dbg += SSS;
      }

   // int CRN_Visitor []
      SSS.Format ("CRN_Visitor[].size = %d:\n", d_CRN_Visitor.GetSize());
      dbg += SSS;
      for (int iCRN_Visitor=0; iCRN_Visitor<d_CRN_Visitor.GetSize(); iCRN_Visitor++)
      {
         SSS.Format ("   CRN_Visitor[%d] = %d\n", iCRN_Visitor, d_CRN_Visitor[iCRN_Visitor]);
         dbg += SSS;
      }

   // int CRN_Visitor_Update
      SSS.Format ("CRN_Visitor_Update = %d\n", d_CRN_Visitor_Update);
      dbg += SSS;

   // int CRA_Inquiry []
      SSS.Format ("CRA_Inquiry[].size = %d:\n", d_CRA_Inquiry.GetSize());
      dbg += SSS;
      for (int iCRA_Inquiry=0; iCRA_Inquiry<d_CRA_Inquiry.GetSize(); iCRA_Inquiry++)
      {
         SSS.Format ("   CRA_Inquiry[%d] = %d\n", iCRA_Inquiry, d_CRA_Inquiry[iCRA_Inquiry]);
         dbg += SSS;
      }

   // int CRN_Inquiry []
      SSS.Format ("CRN_Inquiry[].size = %d:\n", d_CRN_Inquiry.GetSize());
      dbg += SSS;
      for (int iCRN_Inquiry=0; iCRN_Inquiry<d_CRN_Inquiry.GetSize(); iCRN_Inquiry++)
      {
         SSS.Format ("   CRN_Inquiry[%d] = %d\n", iCRN_Inquiry, d_CRN_Inquiry[iCRN_Inquiry]);
         dbg += SSS;
      }

   // int CRN_VisitorIncr []
      SSS.Format ("CRN_VisitorIncr[].size = %d:\n", d_CRN_VisitorIncr.GetSize());
      dbg += SSS;
      for (int iCRN_VisitorIncr=0; iCRN_VisitorIncr<d_CRN_VisitorIncr.GetSize(); iCRN_VisitorIncr++)
      {
         SSS.Format ("   CRN_VisitorIncr[%d] = %d\n", iCRN_VisitorIncr, d_CRN_VisitorIncr[iCRN_VisitorIncr]);
         dbg += SSS;
      }

   // int CRN_VisitorIncr_Update
      SSS.Format ("CRN_VisitorIncr_Update = %d\n", d_CRN_VisitorIncr_Update);
      dbg += SSS;

   // identifier Audience_SiteID []
      SSS.Format ("Audience_SiteID[].size = %d:\n", d_Audience_SiteID.GetSize());
      dbg += SSS;
      for (int iAudience_SiteID=0; iAudience_SiteID<d_Audience_SiteID.GetSize(); iAudience_SiteID++)
      {
         SSS.Format ("   Audience_SiteID[%d] = %d\n", iAudience_SiteID, d_Audience_SiteID[iAudience_SiteID]);
         dbg += SSS;
      }

   // int Audience_Viewers []
      SSS.Format ("Audience_Viewers[].size = %d:\n", d_Audience_Viewers.GetSize());
      dbg += SSS;
      for (int iAudience_Viewers=0; iAudience_Viewers<d_Audience_Viewers.GetSize(); iAudience_Viewers++)
      {
         SSS.Format ("   Audience_Viewers[%d] = %d\n", iAudience_Viewers, d_Audience_Viewers[iAudience_Viewers]);
         dbg += SSS;
      }

   // int Audience_Hosts []
      SSS.Format ("Audience_Hosts[].size = %d:\n", d_Audience_Hosts.GetSize());
      dbg += SSS;
      for (int iAudience_Hosts=0; iAudience_Hosts<d_Audience_Hosts.GetSize(); iAudience_Hosts++)
      {
         SSS.Format ("   Audience_Hosts[%d] = %d\n", iAudience_Hosts, d_Audience_Hosts[iAudience_Hosts]);
         dbg += SSS;
      }

   // int Audience_SiteIDInclude []
      SSS.Format ("Audience_SiteIDInclude[].size = %d:\n", d_Audience_SiteIDInclude.GetSize());
      dbg += SSS;
      for (int iAudience_SiteIDInclude=0; iAudience_SiteIDInclude<d_Audience_SiteIDInclude.GetSize(); iAudience_SiteIDInclude++)
      {
         SSS.Format ("   Audience_SiteIDInclude[%d] = %d\n", iAudience_SiteIDInclude, d_Audience_SiteIDInclude[iAudience_SiteIDInclude]);
         dbg += SSS;
      }

   // identifier ActiveViewersID []
      SSS.Format ("ActiveViewersID[].size = %d:\n", d_ActiveViewersID.GetSize());
      dbg += SSS;
      for (int iActiveViewersID=0; iActiveViewersID<d_ActiveViewersID.GetSize(); iActiveViewersID++)
      {
         SSS.Format ("   ActiveViewersID[%d] = %d\n", iActiveViewersID, d_ActiveViewersID[iActiveViewersID]);
         dbg += SSS;
      }

   // int ActiveViewersHits []
      SSS.Format ("ActiveViewersHits[].size = %d:\n", d_ActiveViewersHits.GetSize());
      dbg += SSS;
      for (int iActiveViewersHits=0; iActiveViewersHits<d_ActiveViewersHits.GetSize(); iActiveViewersHits++)
      {
         SSS.Format ("   ActiveViewersHits[%d] = %d\n", iActiveViewersHits, d_ActiveViewersHits[iActiveViewersHits]);
         dbg += SSS;
      }

   // int RecentPointer
      SSS.Format ("RecentPointer = %d\n", d_RecentPointer);
      dbg += SSS;

   // identifier RecentVisitor []
      SSS.Format ("RecentVisitor[].size = %d:\n", d_RecentVisitor.GetSize());
      dbg += SSS;
      for (int iRecentVisitor=0; iRecentVisitor<d_RecentVisitor.GetSize(); iRecentVisitor++)
      {
         SSS.Format ("   RecentVisitor[%d] = %d\n", iRecentVisitor, d_RecentVisitor[iRecentVisitor]);
         dbg += SSS;
      }

   // identifier RecentReferrer []
      SSS.Format ("RecentReferrer[].size = %d:\n", d_RecentReferrer.GetSize());
      dbg += SSS;
      for (int iRecentReferrer=0; iRecentReferrer<d_RecentReferrer.GetSize(); iRecentReferrer++)
      {
         SSS.Format ("   RecentReferrer[%d] = %d\n", iRecentReferrer, d_RecentReferrer[iRecentReferrer]);
         dbg += SSS;
      }

   // int RecentTimeStamp []
      SSS.Format ("RecentTimeStamp[].size = %d:\n", d_RecentTimeStamp.GetSize());
      dbg += SSS;
      for (int iRecentTimeStamp=0; iRecentTimeStamp<d_RecentTimeStamp.GetSize(); iRecentTimeStamp++)
      {
         SSS.Format ("   RecentTimeStamp[%d] = %d\n", iRecentTimeStamp, d_RecentTimeStamp[iRecentTimeStamp]);
         dbg += SSS;
      }

   // identifier Referrer []
      SSS.Format ("Referrer[].size = %d:\n", d_Referrer.GetSize());
      dbg += SSS;
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         SSS.Format ("   Referrer[%d] = %d\n", iReferrer, d_Referrer[iReferrer]);
         dbg += SSS;
      }

   // int ReferrerCount []
      SSS.Format ("ReferrerCount[].size = %d:\n", d_ReferrerCount.GetSize());
      dbg += SSS;
      for (int iReferrerCount=0; iReferrerCount<d_ReferrerCount.GetSize(); iReferrerCount++)
      {
         SSS.Format ("   ReferrerCount[%d] = %d\n", iReferrerCount, d_ReferrerCount[iReferrerCount]);
         dbg += SSS;
      }

   // int Referrer_LastReset
      SSS.Format ("Referrer_LastReset = %d\n", d_Referrer_LastReset);
      dbg += SSS;

   // identifier DailyReferrerStats []
      SSS.Format ("DailyReferrerStats[].size = %d:\n", d_DailyReferrerStats.GetSize());
      dbg += SSS;
      for (int iDailyReferrerStats=0; iDailyReferrerStats<d_DailyReferrerStats.GetSize(); iDailyReferrerStats++)
      {
         SSS.Format ("   DailyReferrerStats[%d] = %d\n", iDailyReferrerStats, d_DailyReferrerStats[iDailyReferrerStats]);
         dbg += SSS;
      }

   // int DailyReferrerTimeStamp []
      SSS.Format ("DailyReferrerTimeStamp[].size = %d:\n", d_DailyReferrerTimeStamp.GetSize());
      dbg += SSS;
      for (int iDailyReferrerTimeStamp=0; iDailyReferrerTimeStamp<d_DailyReferrerTimeStamp.GetSize(); iDailyReferrerTimeStamp++)
      {
         SSS.Format ("   DailyReferrerTimeStamp[%d] = %d\n", iDailyReferrerTimeStamp, d_DailyReferrerTimeStamp[iDailyReferrerTimeStamp]);
         dbg += SSS;
      }

   // identifier SearchWordsInfo
      SSS.Format ("SearchWordsInfo = %d\n", d_SearchWordsInfo);
      dbg += SSS;

   // int Inquire []
      SSS.Format ("Inquire[].size = %d:\n", d_Inquire.GetSize());
      dbg += SSS;
      for (int iInquire=0; iInquire<d_Inquire.GetSize(); iInquire++)
      {
         SSS.Format ("   Inquire[%d] = %d\n", iInquire, d_Inquire[iInquire]);
         dbg += SSS;
      }

   // int InquiredVisitorNum
      SSS.Format ("InquiredVisitorNum = %d\n", d_InquiredVisitorNum);
      dbg += SSS;

   // int SessionResetTime
      SSS.Format ("SessionResetTime = %d\n", d_SessionResetTime);
      dbg += SSS;

   // int ReturnNumRate []
      SSS.Format ("ReturnNumRate[].size = %d:\n", d_ReturnNumRate.GetSize());
      dbg += SSS;
      for (int iReturnNumRate=0; iReturnNumRate<d_ReturnNumRate.GetSize(); iReturnNumRate++)
      {
         SSS.Format ("   ReturnNumRate[%d] = %d\n", iReturnNumRate, d_ReturnNumRate[iReturnNumRate]);
         dbg += SSS;
      }

   // int ShowNumRate []
      SSS.Format ("ShowNumRate[].size = %d:\n", d_ShowNumRate.GetSize());
      dbg += SSS;
      for (int iShowNumRate=0; iShowNumRate<d_ShowNumRate.GetSize(); iShowNumRate++)
      {
         SSS.Format ("   ShowNumRate[%d] = %d\n", iShowNumRate, d_ShowNumRate[iShowNumRate]);
         dbg += SSS;
      }

   // int LastVisitTime
      SSS.Format ("LastVisitTime = %d\n", d_LastVisitTime);
      dbg += SSS;

   // int LastUpdateTime
      SSS.Format ("LastUpdateTime = %d\n", d_LastUpdateTime);
      dbg += SSS;

   // identifier Loads
      SSS.Format ("Loads = %d\n", d_Loads);
      dbg += SSS;

   // identifier Visitors
      SSS.Format ("Visitors = %d\n", d_Visitors);
      dbg += SSS;

   // identifier Hosts
      SSS.Format ("Hosts = %d\n", d_Hosts);
      dbg += SSS;

   // identifier Shows
      SSS.Format ("Shows = %d\n", d_Shows);
      dbg += SSS;

   // identifier Clicks
      SSS.Format ("Clicks = %d\n", d_Clicks);
      dbg += SSS;

   // identifier Clicks_Local
      SSS.Format ("Clicks_Local = %d\n", d_Clicks_Local);
      dbg += SSS;

   // identifier Hits
      SSS.Format ("Hits = %d\n", d_Hits);
      dbg += SSS;

   // identifier Hits_Local
      SSS.Format ("Hits_Local = %d\n", d_Hits_Local);
      dbg += SSS;

   // identifier AnonymousHits
      SSS.Format ("AnonymousHits = %d\n", d_AnonymousHits);
      dbg += SSS;

   // identifier SuspiciousHits
      SSS.Format ("SuspiciousHits = %d\n", d_SuspiciousHits);
      dbg += SSS;

   // identifier SessionTime
      SSS.Format ("SessionTime = %d\n", d_SessionTime);
      dbg += SSS;

   // identifier SessionTime_Local
      SSS.Format ("SessionTime_Local = %d\n", d_SessionTime_Local);
      dbg += SSS;

   // identifier SessionNum
      SSS.Format ("SessionNum = %d\n", d_SessionNum);
      dbg += SSS;

   // int Total_Loads
      SSS.Format ("Total_Loads = %d\n", d_Total_Loads);
      dbg += SSS;

   // int Total_Hosts
      SSS.Format ("Total_Hosts = %d\n", d_Total_Hosts);
      dbg += SSS;

   // int Total_Hits
      SSS.Format ("Total_Hits = %d\n", d_Total_Hits);
      dbg += SSS;

   // int Total_AnonymousHits
      SSS.Format ("Total_AnonymousHits = %d\n", d_Total_AnonymousHits);
      dbg += SSS;

   // int Total_AnonymousHits_Prc
      SSS.Format ("Total_AnonymousHits_Prc = %d\n", d_Total_AnonymousHits_Prc);
      dbg += SSS;

   // int Total_SuspiciousHits_Prc
      SSS.Format ("Total_SuspiciousHits_Prc = %d\n", d_Total_SuspiciousHits_Prc);
      dbg += SSS;

   // int Total_Visitors
      SSS.Format ("Total_Visitors = %d\n", d_Total_Visitors);
      dbg += SSS;

   // int Total_VisitorReturns
      SSS.Format ("Total_VisitorReturns = %d\n", d_Total_VisitorReturns);
      dbg += SSS;

   // int Total_VisitorReturns_Prc
      SSS.Format ("Total_VisitorReturns_Prc = %d\n", d_Total_VisitorReturns_Prc);
      dbg += SSS;

   // int Total_SessionNum
      SSS.Format ("Total_SessionNum = %d\n", d_Total_SessionNum);
      dbg += SSS;

   // int Total_AveSessionTime
      SSS.Format ("Total_AveSessionTime = %d\n", d_Total_AveSessionTime);
      dbg += SSS;

   // int Total_AveReloadTime
      SSS.Format ("Total_AveReloadTime = %d\n", d_Total_AveReloadTime);
      dbg += SSS;

   // int Total_AveReloadNum
      SSS.Format ("Total_AveReloadNum = %d\n", d_Total_AveReloadNum);
      dbg += SSS;

   // int Total_Shows
      SSS.Format ("Total_Shows = %d\n", d_Total_Shows);
      dbg += SSS;

   // int Total_Clicks
      SSS.Format ("Total_Clicks = %d\n", d_Total_Clicks);
      dbg += SSS;

   // int Total_CTR_Prc
      SSS.Format ("Total_CTR_Prc = %d\n", d_Total_CTR_Prc);
      dbg += SSS;

   // int Total_CPH_Prc
      SSS.Format ("Total_CPH_Prc = %d\n", d_Total_CPH_Prc);
      dbg += SSS;

   // int Total_AnonymousVisitors
      SSS.Format ("Total_AnonymousVisitors = %d\n", d_Total_AnonymousVisitors);
      dbg += SSS;

   // int Total_AnonymousVisitors_Prc
      SSS.Format ("Total_AnonymousVisitors_Prc = %d\n", d_Total_AnonymousVisitors_Prc);
      dbg += SSS;

   // int Total_VisitorExperience
      SSS.Format ("Total_VisitorExperience = %d\n", d_Total_VisitorExperience);
      dbg += SSS;

   // int Ave_VisitorExperience
      SSS.Format ("Ave_VisitorExperience = %d\n", d_Ave_VisitorExperience);
      dbg += SSS;

   // int OnlineVisitors
      SSS.Format ("OnlineVisitors = %d\n", d_OnlineVisitors);
      dbg += SSS;

   // int Total_MouseOver
      SSS.Format ("Total_MouseOver = %d\n", d_Total_MouseOver);
      dbg += SSS;

   // int Total_Votes
      SSS.Format ("Total_Votes = %d\n", d_Total_Votes);
      dbg += SSS;

   // int Total_Votes_Sum
      SSS.Format ("Total_Votes_Sum = %d\n", d_Total_Votes_Sum);
      dbg += SSS;

   // int Total_Votes_Ave
      SSS.Format ("Total_Votes_Ave = %d\n", d_Total_Votes_Ave);
      dbg += SSS;

   // int LM_Loads
      SSS.Format ("LM_Loads = %d\n", d_LM_Loads);
      dbg += SSS;

   // int LM_Hosts
      SSS.Format ("LM_Hosts = %d\n", d_LM_Hosts);
      dbg += SSS;

   // int LM_Hits
      SSS.Format ("LM_Hits = %d\n", d_LM_Hits);
      dbg += SSS;

   // int LM_AnonymousHits
      SSS.Format ("LM_AnonymousHits = %d\n", d_LM_AnonymousHits);
      dbg += SSS;

   // int LM_AnonymousHits_Prc
      SSS.Format ("LM_AnonymousHits_Prc = %d\n", d_LM_AnonymousHits_Prc);
      dbg += SSS;

   // int LM_SuspiciousHits_Prc
      SSS.Format ("LM_SuspiciousHits_Prc = %d\n", d_LM_SuspiciousHits_Prc);
      dbg += SSS;

   // int LM_Visitors
      SSS.Format ("LM_Visitors = %d\n", d_LM_Visitors);
      dbg += SSS;

   // int LM_VisitorReturns
      SSS.Format ("LM_VisitorReturns = %d\n", d_LM_VisitorReturns);
      dbg += SSS;

   // int LM_VisitorReturns_Prc
      SSS.Format ("LM_VisitorReturns_Prc = %d\n", d_LM_VisitorReturns_Prc);
      dbg += SSS;

   // int LM_SessionNum
      SSS.Format ("LM_SessionNum = %d\n", d_LM_SessionNum);
      dbg += SSS;

   // int LM_AveSessionTime
      SSS.Format ("LM_AveSessionTime = %d\n", d_LM_AveSessionTime);
      dbg += SSS;

   // int LM_AveReloadTime
      SSS.Format ("LM_AveReloadTime = %d\n", d_LM_AveReloadTime);
      dbg += SSS;

   // int LM_AveReloadNum
      SSS.Format ("LM_AveReloadNum = %d\n", d_LM_AveReloadNum);
      dbg += SSS;

   // int LM_Shows
      SSS.Format ("LM_Shows = %d\n", d_LM_Shows);
      dbg += SSS;

   // int LM_Clicks
      SSS.Format ("LM_Clicks = %d\n", d_LM_Clicks);
      dbg += SSS;

   // int LM_CTR_Prc
      SSS.Format ("LM_CTR_Prc = %d\n", d_LM_CTR_Prc);
      dbg += SSS;

   // int LM_CPH_Prc
      SSS.Format ("LM_CPH_Prc = %d\n", d_LM_CPH_Prc);
      dbg += SSS;

   // int LW_Loads
      SSS.Format ("LW_Loads = %d\n", d_LW_Loads);
      dbg += SSS;

   // int LW_Hosts
      SSS.Format ("LW_Hosts = %d\n", d_LW_Hosts);
      dbg += SSS;

   // int LW_Hits
      SSS.Format ("LW_Hits = %d\n", d_LW_Hits);
      dbg += SSS;

   // int LW_AnonymousHits
      SSS.Format ("LW_AnonymousHits = %d\n", d_LW_AnonymousHits);
      dbg += SSS;

   // int LW_AnonymousHits_Prc
      SSS.Format ("LW_AnonymousHits_Prc = %d\n", d_LW_AnonymousHits_Prc);
      dbg += SSS;

   // int LW_SuspiciousHits_Prc
      SSS.Format ("LW_SuspiciousHits_Prc = %d\n", d_LW_SuspiciousHits_Prc);
      dbg += SSS;

   // int LW_Visitors
      SSS.Format ("LW_Visitors = %d\n", d_LW_Visitors);
      dbg += SSS;

   // int LW_VisitorReturns
      SSS.Format ("LW_VisitorReturns = %d\n", d_LW_VisitorReturns);
      dbg += SSS;

   // int LW_VisitorReturns_Prc
      SSS.Format ("LW_VisitorReturns_Prc = %d\n", d_LW_VisitorReturns_Prc);
      dbg += SSS;

   // int LW_SessionNum
      SSS.Format ("LW_SessionNum = %d\n", d_LW_SessionNum);
      dbg += SSS;

   // int LW_AveSessionTime
      SSS.Format ("LW_AveSessionTime = %d\n", d_LW_AveSessionTime);
      dbg += SSS;

   // int LW_AveReloadTime
      SSS.Format ("LW_AveReloadTime = %d\n", d_LW_AveReloadTime);
      dbg += SSS;

   // int LW_AveReloadNum
      SSS.Format ("LW_AveReloadNum = %d\n", d_LW_AveReloadNum);
      dbg += SSS;

   // int LW_Shows
      SSS.Format ("LW_Shows = %d\n", d_LW_Shows);
      dbg += SSS;

   // int LW_Clicks
      SSS.Format ("LW_Clicks = %d\n", d_LW_Clicks);
      dbg += SSS;

   // int LW_CTR_Prc
      SSS.Format ("LW_CTR_Prc = %d\n", d_LW_CTR_Prc);
      dbg += SSS;

   // int LW_CPH_Prc
      SSS.Format ("LW_CPH_Prc = %d\n", d_LW_CPH_Prc);
      dbg += SSS;

   // int LD_Loads
      SSS.Format ("LD_Loads = %d\n", d_LD_Loads);
      dbg += SSS;

   // int LD_Hosts
      SSS.Format ("LD_Hosts = %d\n", d_LD_Hosts);
      dbg += SSS;

   // int LD_Hits
      SSS.Format ("LD_Hits = %d\n", d_LD_Hits);
      dbg += SSS;

   // int LD_AnonymousHits
      SSS.Format ("LD_AnonymousHits = %d\n", d_LD_AnonymousHits);
      dbg += SSS;

   // int LD_AnonymousHits_Prc
      SSS.Format ("LD_AnonymousHits_Prc = %d\n", d_LD_AnonymousHits_Prc);
      dbg += SSS;

   // int LD_SuspiciousHits_Prc
      SSS.Format ("LD_SuspiciousHits_Prc = %d\n", d_LD_SuspiciousHits_Prc);
      dbg += SSS;

   // int LD_Visitors
      SSS.Format ("LD_Visitors = %d\n", d_LD_Visitors);
      dbg += SSS;

   // int LD_VisitorReturns
      SSS.Format ("LD_VisitorReturns = %d\n", d_LD_VisitorReturns);
      dbg += SSS;

   // int LD_VisitorReturns_Prc
      SSS.Format ("LD_VisitorReturns_Prc = %d\n", d_LD_VisitorReturns_Prc);
      dbg += SSS;

   // int LD_SessionNum
      SSS.Format ("LD_SessionNum = %d\n", d_LD_SessionNum);
      dbg += SSS;

   // int LD_AveSessionTime
      SSS.Format ("LD_AveSessionTime = %d\n", d_LD_AveSessionTime);
      dbg += SSS;

   // int LD_AveReloadTime
      SSS.Format ("LD_AveReloadTime = %d\n", d_LD_AveReloadTime);
      dbg += SSS;

   // int LD_AveReloadNum
      SSS.Format ("LD_AveReloadNum = %d\n", d_LD_AveReloadNum);
      dbg += SSS;

   // int LD_Shows
      SSS.Format ("LD_Shows = %d\n", d_LD_Shows);
      dbg += SSS;

   // int LD_Clicks
      SSS.Format ("LD_Clicks = %d\n", d_LD_Clicks);
      dbg += SSS;

   // int LD_CTR_Prc
      SSS.Format ("LD_CTR_Prc = %d\n", d_LD_CTR_Prc);
      dbg += SSS;

   // int LD_CPH_Prc
      SSS.Format ("LD_CPH_Prc = %d\n", d_LD_CPH_Prc);
      dbg += SSS;

   // int LH_Loads
      SSS.Format ("LH_Loads = %d\n", d_LH_Loads);
      dbg += SSS;

   // int LH_Hosts
      SSS.Format ("LH_Hosts = %d\n", d_LH_Hosts);
      dbg += SSS;

   // int LH_Hits
      SSS.Format ("LH_Hits = %d\n", d_LH_Hits);
      dbg += SSS;

   // int LH_AnonymousHits
      SSS.Format ("LH_AnonymousHits = %d\n", d_LH_AnonymousHits);
      dbg += SSS;

   // int LH_AnonymousHits_Prc
      SSS.Format ("LH_AnonymousHits_Prc = %d\n", d_LH_AnonymousHits_Prc);
      dbg += SSS;

   // int LH_SuspiciousHits_Prc
      SSS.Format ("LH_SuspiciousHits_Prc = %d\n", d_LH_SuspiciousHits_Prc);
      dbg += SSS;

   // int LH_Visitors
      SSS.Format ("LH_Visitors = %d\n", d_LH_Visitors);
      dbg += SSS;

   // int LH_VisitorReturns
      SSS.Format ("LH_VisitorReturns = %d\n", d_LH_VisitorReturns);
      dbg += SSS;

   // int LH_VisitorReturns_Prc
      SSS.Format ("LH_VisitorReturns_Prc = %d\n", d_LH_VisitorReturns_Prc);
      dbg += SSS;

   // int LH_SessionNum
      SSS.Format ("LH_SessionNum = %d\n", d_LH_SessionNum);
      dbg += SSS;

   // int LH_AveSessionTime
      SSS.Format ("LH_AveSessionTime = %d\n", d_LH_AveSessionTime);
      dbg += SSS;

   // int LH_AveReloadTime
      SSS.Format ("LH_AveReloadTime = %d\n", d_LH_AveReloadTime);
      dbg += SSS;

   // int LH_AveReloadNum
      SSS.Format ("LH_AveReloadNum = %d\n", d_LH_AveReloadNum);
      dbg += SSS;

   // int LH_Shows
      SSS.Format ("LH_Shows = %d\n", d_LH_Shows);
      dbg += SSS;

   // int LH_Clicks
      SSS.Format ("LH_Clicks = %d\n", d_LH_Clicks);
      dbg += SSS;

   // int LH_CTR_Prc
      SSS.Format ("LH_CTR_Prc = %d\n", d_LH_CTR_Prc);
      dbg += SSS;

   // int LH_CPH_Prc
      SSS.Format ("LH_CPH_Prc = %d\n", d_LH_CPH_Prc);
      dbg += SSS;

   // int CustomIndex1
      SSS.Format ("CustomIndex1 = %d\n", d_CustomIndex1);
      dbg += SSS;

   // int CustomIndex2
      SSS.Format ("CustomIndex2 = %d\n", d_CustomIndex2);
      dbg += SSS;

   // int CustomIndex3
      SSS.Format ("CustomIndex3 = %d\n", d_CustomIndex3);
      dbg += SSS;

   // int CustomIndex4
      SSS.Format ("CustomIndex4 = %d\n", d_CustomIndex4);
      dbg += SSS;

   // int CustomIndex5
      SSS.Format ("CustomIndex5 = %d\n", d_CustomIndex5);
      dbg += SSS;

   // bool Allowed
      SSS.Format ("Allowed = %s\n", d_Allowed?"true":"false");
      dbg += SSS;

   // byte ObjectState
      SSS.Format ("ObjectState = %d\n", d_ObjectState);
      dbg += SSS;

   // byte ba_ModeratorComment []
      SSS.Format ("ba_ModeratorComment[].size = %d:\n", d_ba_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iba_ModeratorComment=0; iba_ModeratorComment<d_ba_ModeratorComment.GetSize(); iba_ModeratorComment++)
      {
         SSS.Format ("   ba_ModeratorComment[%d] = %d\n", iba_ModeratorComment, d_ba_ModeratorComment[iba_ModeratorComment]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // identifier RatingPlaceInfo
      SSS.Format ("RatingPlaceInfo = %d\n", d_RatingPlaceInfo);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_SiteProfile::OD_SiteProfile (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_SiteProfile;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_Site.Alloc (0);
      d_VBN = 255;
      d_LastModified = 0;
      d_OwnerID = NA;
      d_DefaultKeyword.Alloc (0);
      d_BannerInclude.Alloc (0);
      d_BannerExclude.Alloc (0);
      d_SiteInclude.Alloc (0);
      d_SiteExclude.Alloc (0);
      d_MaxFileSize = 0;
      d_UseKeywords = false;
      d_ba_BannerConceptInclude.Alloc (0);
      d_ba_BannerConceptExclude.Alloc (0);
      d_eba_BannerConcept.Alloc (0);
      d_Price.Alloc (0);
      d_StaticSupport = false;
      d_Allowed = false;
      d_ObjectState = 1;
      d_ba_ModeratorComment.Alloc (0);
      d_TagID = NA;
      d_TagBool = false;
      d_TagInt = 0;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_SiteProfile::~OD_SiteProfile () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_SiteProfile::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Name;               break;
         case 3: ka += d_VBN;                break;
         case 4: ka += d_LastModified;       break;
         case 5: ka += d_OwnerID;            break;
         case 11: ka += d_MaxFileSize;        break;
         case 12: ka += d_UseKeywords;        break;
         case 17: ka += d_StaticSupport;      break;
         case 18: ka += d_Allowed;            break;
         case 19: ka += d_ObjectState;        break;
         case 21: ka += d_TagID;              break;
         case 22: ka += d_TagBool;            break;
         case 23: ka += d_TagInt;             break;
         case 27: ka += d_CacheTime;          break;
      }
   }


// Загрузка объекта с диска
   size_t OD_SiteProfile::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // identifier Site []
      int arr_size_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site.Alloc (arr_size_Site);
      OD_LOAD_SIMPLE_ARRAY (identifier,Site);

   // byte VBN
      d_VBN = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // int LastModified
      d_LastModified = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier OwnerID
      d_OwnerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier DefaultKeyword []
      int arr_size_DefaultKeyword = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DefaultKeyword.Alloc (arr_size_DefaultKeyword);
      OD_LOAD_SIMPLE_ARRAY (identifier,DefaultKeyword);

   // identifier BannerInclude []
      int arr_size_BannerInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BannerInclude.Alloc (arr_size_BannerInclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,BannerInclude);

   // identifier BannerExclude []
      int arr_size_BannerExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BannerExclude.Alloc (arr_size_BannerExclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,BannerExclude);

   // identifier SiteInclude []
      int arr_size_SiteInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteInclude.Alloc (arr_size_SiteInclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteInclude);

   // identifier SiteExclude []
      int arr_size_SiteExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SiteExclude.Alloc (arr_size_SiteExclude);
      OD_LOAD_SIMPLE_ARRAY (identifier,SiteExclude);

   // int MaxFileSize
      d_MaxFileSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool UseKeywords
      d_UseKeywords = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ba_BannerConceptInclude []
      int arr_size_ba_BannerConceptInclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_BannerConceptInclude.Alloc (arr_size_ba_BannerConceptInclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_BannerConceptInclude);

   // byte ba_BannerConceptExclude []
      int arr_size_ba_BannerConceptExclude = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_BannerConceptExclude.Alloc (arr_size_ba_BannerConceptExclude);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_BannerConceptExclude);

   // byte eba_BannerConcept []
      int arr_size_eba_BannerConcept = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_eba_BannerConcept.Alloc (arr_size_eba_BannerConcept);
      OD_LOAD_SIMPLE_ARRAY (byte,eba_BannerConcept);

   // int Price []
      int arr_size_Price = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Price.Alloc (arr_size_Price);
      OD_LOAD_SIMPLE_ARRAY (int,Price);

   // bool StaticSupport
      d_StaticSupport = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // bool Allowed
      d_Allowed = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // byte ObjectState
      d_ObjectState = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte ba_ModeratorComment []
      int arr_size_ba_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ba_ModeratorComment.Alloc (arr_size_ba_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_SiteProfile::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // identifier Site []
      n_size += sizeof (size_t);
      n_size += d_Site.GetSize() * sizeof(identifier);

   // byte VBN
      n_size += sizeof (byte);

   // int LastModified
      n_size += sizeof (int);

   // identifier OwnerID
      n_size += sizeof (identifier);

   // identifier DefaultKeyword []
      n_size += sizeof (size_t);
      n_size += d_DefaultKeyword.GetSize() * sizeof(identifier);

   // identifier BannerInclude []
      n_size += sizeof (size_t);
      n_size += d_BannerInclude.GetSize() * sizeof(identifier);

   // identifier BannerExclude []
      n_size += sizeof (size_t);
      n_size += d_BannerExclude.GetSize() * sizeof(identifier);

   // identifier SiteInclude []
      n_size += sizeof (size_t);
      n_size += d_SiteInclude.GetSize() * sizeof(identifier);

   // identifier SiteExclude []
      n_size += sizeof (size_t);
      n_size += d_SiteExclude.GetSize() * sizeof(identifier);

   // int MaxFileSize
      n_size += sizeof (int);

   // bool UseKeywords
      n_size += sizeof (bool);

   // byte ba_BannerConceptInclude []
      n_size += sizeof (size_t);
      n_size += d_ba_BannerConceptInclude.GetSize() * sizeof(byte);

   // byte ba_BannerConceptExclude []
      n_size += sizeof (size_t);
      n_size += d_ba_BannerConceptExclude.GetSize() * sizeof(byte);

   // byte eba_BannerConcept []
      n_size += sizeof (size_t);
      n_size += d_eba_BannerConcept.GetSize() * sizeof(byte);

   // int Price []
      n_size += sizeof (size_t);
      n_size += d_Price.GetSize() * sizeof(int);

   // bool StaticSupport
      n_size += sizeof (bool);

   // bool Allowed
      n_size += sizeof (bool);

   // byte ObjectState
      n_size += sizeof (byte);

   // byte ba_ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ba_ModeratorComment.GetSize() * sizeof(byte);

   // identifier TagID
      n_size += sizeof (identifier);

   // bool TagBool
      n_size += sizeof (bool);

   // int TagInt
      n_size += sizeof (int);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_SiteProfile::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // identifier Site []
      (*(size_t*)(file+nOffset)) = d_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Site);

   // byte VBN
      (*(byte*)(file+nOffset)) = d_VBN;
      nOffset += sizeof (byte);

   // int LastModified
      (*(int*)(file+nOffset)) = d_LastModified;
      nOffset += sizeof (int);

   // identifier OwnerID
      (*(identifier*)(file+nOffset)) = d_OwnerID;
      nOffset += sizeof (identifier);

   // identifier DefaultKeyword []
      (*(size_t*)(file+nOffset)) = d_DefaultKeyword.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,DefaultKeyword);

   // identifier BannerInclude []
      (*(size_t*)(file+nOffset)) = d_BannerInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,BannerInclude);

   // identifier BannerExclude []
      (*(size_t*)(file+nOffset)) = d_BannerExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,BannerExclude);

   // identifier SiteInclude []
      (*(size_t*)(file+nOffset)) = d_SiteInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteInclude);

   // identifier SiteExclude []
      (*(size_t*)(file+nOffset)) = d_SiteExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SiteExclude);

   // int MaxFileSize
      (*(int*)(file+nOffset)) = d_MaxFileSize;
      nOffset += sizeof (int);

   // bool UseKeywords
      (*(bool*)(file+nOffset)) = d_UseKeywords;
      nOffset += sizeof (bool);

   // byte ba_BannerConceptInclude []
      (*(size_t*)(file+nOffset)) = d_ba_BannerConceptInclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_BannerConceptInclude);

   // byte ba_BannerConceptExclude []
      (*(size_t*)(file+nOffset)) = d_ba_BannerConceptExclude.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_BannerConceptExclude);

   // byte eba_BannerConcept []
      (*(size_t*)(file+nOffset)) = d_eba_BannerConcept.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,eba_BannerConcept);

   // int Price []
      (*(size_t*)(file+nOffset)) = d_Price.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Price);

   // bool StaticSupport
      (*(bool*)(file+nOffset)) = d_StaticSupport;
      nOffset += sizeof (bool);

   // bool Allowed
      (*(bool*)(file+nOffset)) = d_Allowed;
      nOffset += sizeof (bool);

   // byte ObjectState
      (*(byte*)(file+nOffset)) = d_ObjectState;
      nOffset += sizeof (byte);

   // byte ba_ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ba_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ba_ModeratorComment);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_SiteProfile::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_SiteProfile], objID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // identifier Site []
      SSS.Format ("Site[].size = %d:\n", d_Site.GetSize());
      dbg += SSS;
      for (int iSite=0; iSite<d_Site.GetSize(); iSite++)
      {
         SSS.Format ("   Site[%d] = %d\n", iSite, d_Site[iSite]);
         dbg += SSS;
      }

   // byte VBN
      SSS.Format ("VBN = %d\n", d_VBN);
      dbg += SSS;

   // int LastModified
      SSS.Format ("LastModified = %d\n", d_LastModified);
      dbg += SSS;

   // identifier OwnerID
      SSS.Format ("OwnerID = %d\n", d_OwnerID);
      dbg += SSS;

   // identifier DefaultKeyword []
      SSS.Format ("DefaultKeyword[].size = %d:\n", d_DefaultKeyword.GetSize());
      dbg += SSS;
      for (int iDefaultKeyword=0; iDefaultKeyword<d_DefaultKeyword.GetSize(); iDefaultKeyword++)
      {
         SSS.Format ("   DefaultKeyword[%d] = %d\n", iDefaultKeyword, d_DefaultKeyword[iDefaultKeyword]);
         dbg += SSS;
      }

   // identifier BannerInclude []
      SSS.Format ("BannerInclude[].size = %d:\n", d_BannerInclude.GetSize());
      dbg += SSS;
      for (int iBannerInclude=0; iBannerInclude<d_BannerInclude.GetSize(); iBannerInclude++)
      {
         SSS.Format ("   BannerInclude[%d] = %d\n", iBannerInclude, d_BannerInclude[iBannerInclude]);
         dbg += SSS;
      }

   // identifier BannerExclude []
      SSS.Format ("BannerExclude[].size = %d:\n", d_BannerExclude.GetSize());
      dbg += SSS;
      for (int iBannerExclude=0; iBannerExclude<d_BannerExclude.GetSize(); iBannerExclude++)
      {
         SSS.Format ("   BannerExclude[%d] = %d\n", iBannerExclude, d_BannerExclude[iBannerExclude]);
         dbg += SSS;
      }

   // identifier SiteInclude []
      SSS.Format ("SiteInclude[].size = %d:\n", d_SiteInclude.GetSize());
      dbg += SSS;
      for (int iSiteInclude=0; iSiteInclude<d_SiteInclude.GetSize(); iSiteInclude++)
      {
         SSS.Format ("   SiteInclude[%d] = %d\n", iSiteInclude, d_SiteInclude[iSiteInclude]);
         dbg += SSS;
      }

   // identifier SiteExclude []
      SSS.Format ("SiteExclude[].size = %d:\n", d_SiteExclude.GetSize());
      dbg += SSS;
      for (int iSiteExclude=0; iSiteExclude<d_SiteExclude.GetSize(); iSiteExclude++)
      {
         SSS.Format ("   SiteExclude[%d] = %d\n", iSiteExclude, d_SiteExclude[iSiteExclude]);
         dbg += SSS;
      }

   // int MaxFileSize
      SSS.Format ("MaxFileSize = %d\n", d_MaxFileSize);
      dbg += SSS;

   // bool UseKeywords
      SSS.Format ("UseKeywords = %s\n", d_UseKeywords?"true":"false");
      dbg += SSS;

   // byte ba_BannerConceptInclude []
      SSS.Format ("ba_BannerConceptInclude[].size = %d:\n", d_ba_BannerConceptInclude.GetSize());
      dbg += SSS;
      for (int iba_BannerConceptInclude=0; iba_BannerConceptInclude<d_ba_BannerConceptInclude.GetSize(); iba_BannerConceptInclude++)
      {
         SSS.Format ("   ba_BannerConceptInclude[%d] = %d\n", iba_BannerConceptInclude, d_ba_BannerConceptInclude[iba_BannerConceptInclude]);
         dbg += SSS;
      }

   // byte ba_BannerConceptExclude []
      SSS.Format ("ba_BannerConceptExclude[].size = %d:\n", d_ba_BannerConceptExclude.GetSize());
      dbg += SSS;
      for (int iba_BannerConceptExclude=0; iba_BannerConceptExclude<d_ba_BannerConceptExclude.GetSize(); iba_BannerConceptExclude++)
      {
         SSS.Format ("   ba_BannerConceptExclude[%d] = %d\n", iba_BannerConceptExclude, d_ba_BannerConceptExclude[iba_BannerConceptExclude]);
         dbg += SSS;
      }

   // byte eba_BannerConcept []
      SSS.Format ("eba_BannerConcept[].size = %d:\n", d_eba_BannerConcept.GetSize());
      dbg += SSS;
      for (int ieba_BannerConcept=0; ieba_BannerConcept<d_eba_BannerConcept.GetSize(); ieba_BannerConcept++)
      {
         SSS.Format ("   eba_BannerConcept[%d] = %d\n", ieba_BannerConcept, d_eba_BannerConcept[ieba_BannerConcept]);
         dbg += SSS;
      }

   // int Price []
      SSS.Format ("Price[].size = %d:\n", d_Price.GetSize());
      dbg += SSS;
      for (int iPrice=0; iPrice<d_Price.GetSize(); iPrice++)
      {
         SSS.Format ("   Price[%d] = %d\n", iPrice, d_Price[iPrice]);
         dbg += SSS;
      }

   // bool StaticSupport
      SSS.Format ("StaticSupport = %s\n", d_StaticSupport?"true":"false");
      dbg += SSS;

   // bool Allowed
      SSS.Format ("Allowed = %s\n", d_Allowed?"true":"false");
      dbg += SSS;

   // byte ObjectState
      SSS.Format ("ObjectState = %d\n", d_ObjectState);
      dbg += SSS;

   // byte ba_ModeratorComment []
      SSS.Format ("ba_ModeratorComment[].size = %d:\n", d_ba_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iba_ModeratorComment=0; iba_ModeratorComment<d_ba_ModeratorComment.GetSize(); iba_ModeratorComment++)
      {
         SSS.Format ("   ba_ModeratorComment[%d] = %d\n", iba_ModeratorComment, d_ba_ModeratorComment[iba_ModeratorComment]);
         dbg += SSS;
      }

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_ShowEvent::OD_ShowEvent (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_ShowEvent;


      m_CoIndexPtr = new OBD_pointer [3];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      if (!bFieldsInit) return;

      d_SiteID = NA;
      d_ViewerID = NA;
      d_Time = 0;
      d_ExitCode = 0;
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_CacheTime = 0;
   }

// Деструктор
  OD_ShowEvent::~OD_ShowEvent () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_ShowEvent::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_SiteID;              break;
         case 2: ka += d_ViewerID;            break;
         case 3: ka += d_Time;                break;
         case 4: ka += d_ExitCode;            break;
         case 5: ka += d_TagID;               break;
         case 6: ka += d_TagInt;              break;
         case 7: ka += d_TagBool;             break;
         case 8: ka += d_ReservedString;      break;
         case 9: ka += d_CacheTime;           break;
      }
   }


// Загрузка объекта с диска
   size_t OD_ShowEvent::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier SiteID
      d_SiteID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier ViewerID
      d_ViewerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Time
      d_Time = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ExitCode
      d_ExitCode = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // string ReservedString
      size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
      nOffset += sizeof(size_t);
      char * s_ReservedString = new char [n_ReservedString];
      memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
      nOffset += n_ReservedString;
      DECODE_STRING (n_ReservedString, s_ReservedString);
      d_ReservedString = s_ReservedString;
      delete [] s_ReservedString;

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_ShowEvent::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier SiteID
      n_size += sizeof (identifier);

   // identifier ViewerID
      n_size += sizeof (identifier);

   // int Time
      n_size += sizeof (int);

   // int ExitCode
      n_size += sizeof (int);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // string ReservedString
      n_size += sizeof (size_t);
      n_size += d_ReservedString.length()+1;

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_ShowEvent::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier SiteID
      (*(identifier*)(file+nOffset)) = d_SiteID;
      nOffset += sizeof (identifier);

   // identifier ViewerID
      (*(identifier*)(file+nOffset)) = d_ViewerID;
      nOffset += sizeof (identifier);

   // int Time
      (*(int*)(file+nOffset)) = d_Time;
      nOffset += sizeof (int);

   // int ExitCode
      (*(int*)(file+nOffset)) = d_ExitCode;
      nOffset += sizeof (int);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // string ReservedString
      size_t n_ReservedString = d_ReservedString.length()+1;
      (*(size_t*)(file+nOffset)) = n_ReservedString;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_ReservedString.c_str(), n_ReservedString);
      ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
      nOffset += n_ReservedString;

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_ShowEvent::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_ShowEvent], objID);
      dbg += SSS;

   // identifier SiteID
      SSS.Format ("SiteID = %d\n", d_SiteID);
      dbg += SSS;

   // identifier ViewerID
      SSS.Format ("ViewerID = %d\n", d_ViewerID);
      dbg += SSS;

   // int Time
      SSS.Format ("Time = %d\n", d_Time);
      dbg += SSS;

   // int ExitCode
      SSS.Format ("ExitCode = %d\n", d_ExitCode);
      dbg += SSS;

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // string ReservedString
      SSS.Format ("ReservedString = '%s'\n", d_ReservedString.c_str());
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Registry::OD_Registry (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Registry;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_ConceptID_Sorted.Alloc (0);
      d_ConceptNo_SortID.Alloc (0);
      d_ConceptID_SortNo.Alloc (0);
      d_ConceptParent_SortNo.Alloc (0);
      d_ConceptType_SortNo.Alloc (0);
      d_ConceptLevel_SortNo.Alloc (0);
      d_Language.Alloc (0);
      d_LanguageNo.Alloc (0);
      d_VBN.Alloc (0);
      d_VBNNo.Alloc (0);
      d_ModeratorComment.Alloc (0);
      d_ModeratorCommentNo.Alloc (0);
      d_CRA_InetAudience.Alloc (0);
      d_CRN_InetAudience.Alloc (0);
      d_CRN_InetAudience_Update = 0;
      d_VisitorHistoryLength = 20;
      d_MinimumHitsTime = 5;
      d_SuspiciousInfoSize = 100;
      d_ActiveViewersSize = 20;
      d_ReturnNumRateSize = 10;
      d_DailyReferrerSize = 100;
      d_ClickNumRateSize = 10;
      d_ShowNumRateSize = 10;
      d_HitNumRateSize = 10;
      d_SessionTimeRateSize = 10;
      d_IgnoredIP.Alloc (0);
      d_IgnoredUserAgent.Alloc (0);
      d_IgnoredBrowser.Alloc (0);
      d_SearchEngines.Alloc (0);
      d_Classifiers.Alloc (0);
      d_CachePurgeTime_IPRecord = 0;
      d_CachePurgeTime_RatingPlaceInfo = 0;
      d_CachePurgeTime_SuspiciousInfo = 0;
      d_CachePurgeTime_SearchWordsInfo = 0;
      d_CachePurgeTime_DailyReferrerStats = 0;
      d_CachePurgeTime_DayStats = 0;
      d_CachePurgeTime_YearStats = 0;
      d_CachePurgeTime_TimeStats = 0;
      d_CachePurgeTime_ModeratorComment = 0;
      d_CachePurgeTime_Keyword = 0;
      d_CachePurgeTime_SiteList = 0;
      d_CachePurgeTime_Concept = 0;
      d_CachePurgeTime_Language = 0;
      d_CachePurgeTime_VBN = 0;
      d_CachePurgeTime_Site = 0;
      d_CachePurgeTime_Page = 0;
      d_CachePurgeTime_BannerProfile = 0;
      d_CachePurgeTime_Banner = 0;
      d_CachePurgeTime_TradeStats = 0;
      d_CachePurgeTime_User = 0;
      d_CachePurgeTime_ViewerGroup = 0;
      d_CachePurgeTime_Viewer = 0;
      d_ReloadTimeThreshold = 300;
      d_ViewerCacheReloadThreshold = (float) 0.0;
      d_ReloadDistribution.Alloc (0);
      d_Viewers.Alloc (0);
      d_DefaultPriority = (float) 0.0;
      d_BannerStore_Expire = 7776000;
      d_BannerStore_MaxLength = 1000;
      d_SiteStore_Expire = 7776000;
      d_SiteStore_MaxLength = 1000;
      d_MaxDailyEventsDefault = 1000;
      d_TagID1 = NA;
      d_TagID2 = NA;
      d_TagID3 = NA;
      d_TagBool1 = false;
      d_TagBool2 = false;
      d_TagBool3 = false;
      d_TagInt1 = 0;
      d_TagInt2 = 0;
      d_TagInt3 = 0;
      d_ReservedID1.Alloc (0);
      d_ReservedID2.Alloc (0);
      d_ReservedID3.Alloc (0);
      d_ReservedInt1.Alloc (0);
      d_ReservedInt2.Alloc (0);
      d_ReservedInt3.Alloc (0);
      d_ReservedString1.Alloc (0);
      d_ReservedString2.Alloc (0);
      d_ReservedString3.Alloc (0);
   }

// Деструктор
  OD_Registry::~OD_Registry () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Registry::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_AdminPassword;                          break;
         case 16: ka += d_CRN_InetAudience_Update;                break;
         case 17: ka += d_VisitorHistoryLength;                   break;
         case 18: ka += d_MinimumHitsTime;                        break;
         case 19: ka += d_SuspiciousInfoSize;                     break;
         case 20: ka += d_ActiveViewersSize;                      break;
         case 21: ka += d_ReturnNumRateSize;                      break;
         case 22: ka += d_DailyReferrerSize;                      break;
         case 23: ka += d_ClickNumRateSize;                       break;
         case 24: ka += d_ShowNumRateSize;                        break;
         case 25: ka += d_HitNumRateSize;                         break;
         case 26: ka += d_SessionTimeRateSize;                    break;
         case 32: ka += d_CachePurgeTime_IPRecord;                break;
         case 33: ka += d_CachePurgeTime_RatingPlaceInfo;         break;
         case 34: ka += d_CachePurgeTime_SuspiciousInfo;          break;
         case 35: ka += d_CachePurgeTime_SearchWordsInfo;         break;
         case 36: ka += d_CachePurgeTime_DailyReferrerStats;      break;
         case 37: ka += d_CachePurgeTime_DayStats;                break;
         case 38: ka += d_CachePurgeTime_YearStats;               break;
         case 39: ka += d_CachePurgeTime_TimeStats;               break;
         case 40: ka += d_CachePurgeTime_ModeratorComment;        break;
         case 41: ka += d_CachePurgeTime_Keyword;                 break;
         case 42: ka += d_CachePurgeTime_SiteList;                break;
         case 43: ka += d_CachePurgeTime_Concept;                 break;
         case 44: ka += d_CachePurgeTime_Language;                break;
         case 45: ka += d_CachePurgeTime_VBN;                     break;
         case 46: ka += d_CachePurgeTime_Site;                    break;
         case 47: ka += d_CachePurgeTime_Page;                    break;
         case 48: ka += d_CachePurgeTime_BannerProfile;           break;
         case 49: ka += d_CachePurgeTime_Banner;                  break;
         case 50: ka += d_CachePurgeTime_TradeStats;              break;
         case 51: ka += d_CachePurgeTime_User;                    break;
         case 52: ka += d_CachePurgeTime_ViewerGroup;             break;
         case 53: ka += d_CachePurgeTime_Viewer;                  break;
         case 54: ka += d_ReloadTimeThreshold;                    break;
         case 55: ka += d_ViewerCacheReloadThreshold;             break;
         case 58: ka += d_DefaultPriority;                        break;
         case 59: ka += d_BannerStore_Expire;                     break;
         case 60: ka += d_BannerStore_MaxLength;                  break;
         case 61: ka += d_SiteStore_Expire;                       break;
         case 62: ka += d_SiteStore_MaxLength;                    break;
         case 63: ka += d_MaxDailyEventsDefault;                  break;
         case 64: ka += d_TagID1;                                 break;
         case 65: ka += d_TagID2;                                 break;
         case 66: ka += d_TagID3;                                 break;
         case 67: ka += d_TagBool1;                               break;
         case 68: ka += d_TagBool2;                               break;
         case 69: ka += d_TagBool3;                               break;
         case 70: ka += d_TagInt1;                                break;
         case 71: ka += d_TagInt2;                                break;
         case 72: ka += d_TagInt3;                                break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Registry::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string AdminPassword
      size_t n_AdminPassword = (*(size_t*)(file+nOffset));  // n_AdminPassword = strlen (s_AdminPassword)+1;
      nOffset += sizeof(size_t);
      char * s_AdminPassword = new char [n_AdminPassword];
      memcpy (s_AdminPassword, (file+nOffset), n_AdminPassword);
      nOffset += n_AdminPassword;
      DECODE_STRING (n_AdminPassword, s_AdminPassword);
      d_AdminPassword = s_AdminPassword;
      delete [] s_AdminPassword;

   // identifier ConceptID_Sorted []
      int arr_size_ConceptID_Sorted = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptID_Sorted.Alloc (arr_size_ConceptID_Sorted);
      OD_LOAD_SIMPLE_ARRAY (identifier,ConceptID_Sorted);

   // int ConceptNo_SortID []
      int arr_size_ConceptNo_SortID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptNo_SortID.Alloc (arr_size_ConceptNo_SortID);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptNo_SortID);

   // identifier ConceptID_SortNo []
      int arr_size_ConceptID_SortNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptID_SortNo.Alloc (arr_size_ConceptID_SortNo);
      OD_LOAD_SIMPLE_ARRAY (identifier,ConceptID_SortNo);

   // int ConceptParent_SortNo []
      int arr_size_ConceptParent_SortNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptParent_SortNo.Alloc (arr_size_ConceptParent_SortNo);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptParent_SortNo);

   // int ConceptType_SortNo []
      int arr_size_ConceptType_SortNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptType_SortNo.Alloc (arr_size_ConceptType_SortNo);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptType_SortNo);

   // int ConceptLevel_SortNo []
      int arr_size_ConceptLevel_SortNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptLevel_SortNo.Alloc (arr_size_ConceptLevel_SortNo);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptLevel_SortNo);

   // identifier Language []
      int arr_size_Language = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Language.Alloc (arr_size_Language);
      OD_LOAD_SIMPLE_ARRAY (identifier,Language);

   // int LanguageNo []
      int arr_size_LanguageNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_LanguageNo.Alloc (arr_size_LanguageNo);
      OD_LOAD_SIMPLE_ARRAY (int,LanguageNo);

   // identifier VBN []
      int arr_size_VBN = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN.Alloc (arr_size_VBN);
      OD_LOAD_SIMPLE_ARRAY (identifier,VBN);

   // int VBNNo []
      int arr_size_VBNNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBNNo.Alloc (arr_size_VBNNo);
      OD_LOAD_SIMPLE_ARRAY (int,VBNNo);

   // identifier ModeratorComment []
      int arr_size_ModeratorComment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ModeratorComment.Alloc (arr_size_ModeratorComment);
      OD_LOAD_SIMPLE_ARRAY (identifier,ModeratorComment);

   // int ModeratorCommentNo []
      int arr_size_ModeratorCommentNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ModeratorCommentNo.Alloc (arr_size_ModeratorCommentNo);
      OD_LOAD_SIMPLE_ARRAY (int,ModeratorCommentNo);

   // int CRA_InetAudience []
      int arr_size_CRA_InetAudience = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_InetAudience.Alloc (arr_size_CRA_InetAudience);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_InetAudience);

   // int CRN_InetAudience []
      int arr_size_CRN_InetAudience = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRN_InetAudience.Alloc (arr_size_CRN_InetAudience);
      OD_LOAD_SIMPLE_ARRAY (int,CRN_InetAudience);

   // int CRN_InetAudience_Update
      d_CRN_InetAudience_Update = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int VisitorHistoryLength
      d_VisitorHistoryLength = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MinimumHitsTime
      d_MinimumHitsTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SuspiciousInfoSize
      d_SuspiciousInfoSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ActiveViewersSize
      d_ActiveViewersSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ReturnNumRateSize
      d_ReturnNumRateSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int DailyReferrerSize
      d_DailyReferrerSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickNumRateSize
      d_ClickNumRateSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ShowNumRateSize
      d_ShowNumRateSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int HitNumRateSize
      d_HitNumRateSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SessionTimeRateSize
      d_SessionTimeRateSize = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string IgnoredIP []
      int arr_size_IgnoredIP = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_IgnoredIP.Alloc (arr_size_IgnoredIP);
      for (int iIgnoredIP=0; iIgnoredIP<(int)arr_size_IgnoredIP; iIgnoredIP++)
      {
         string tmp_IgnoredIP;
         size_t n_IgnoredIP = (*(size_t*)(file+nOffset));  // n_IgnoredIP = strlen (s_IgnoredIP)+1;
         nOffset += sizeof(size_t);
         char * s_IgnoredIP = new char [n_IgnoredIP];
         memcpy (s_IgnoredIP, (file+nOffset), n_IgnoredIP);
         nOffset += n_IgnoredIP;
         DECODE_STRING (n_IgnoredIP, s_IgnoredIP);
         tmp_IgnoredIP = s_IgnoredIP;
         delete [] s_IgnoredIP;

         d_IgnoredIP[iIgnoredIP] = tmp_IgnoredIP;
      }

   // string IgnoredUserAgent []
      int arr_size_IgnoredUserAgent = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_IgnoredUserAgent.Alloc (arr_size_IgnoredUserAgent);
      for (int iIgnoredUserAgent=0; iIgnoredUserAgent<(int)arr_size_IgnoredUserAgent; iIgnoredUserAgent++)
      {
         string tmp_IgnoredUserAgent;
         size_t n_IgnoredUserAgent = (*(size_t*)(file+nOffset));  // n_IgnoredUserAgent = strlen (s_IgnoredUserAgent)+1;
         nOffset += sizeof(size_t);
         char * s_IgnoredUserAgent = new char [n_IgnoredUserAgent];
         memcpy (s_IgnoredUserAgent, (file+nOffset), n_IgnoredUserAgent);
         nOffset += n_IgnoredUserAgent;
         DECODE_STRING (n_IgnoredUserAgent, s_IgnoredUserAgent);
         tmp_IgnoredUserAgent = s_IgnoredUserAgent;
         delete [] s_IgnoredUserAgent;

         d_IgnoredUserAgent[iIgnoredUserAgent] = tmp_IgnoredUserAgent;
      }

   // string IgnoredBrowser []
      int arr_size_IgnoredBrowser = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_IgnoredBrowser.Alloc (arr_size_IgnoredBrowser);
      for (int iIgnoredBrowser=0; iIgnoredBrowser<(int)arr_size_IgnoredBrowser; iIgnoredBrowser++)
      {
         string tmp_IgnoredBrowser;
         size_t n_IgnoredBrowser = (*(size_t*)(file+nOffset));  // n_IgnoredBrowser = strlen (s_IgnoredBrowser)+1;
         nOffset += sizeof(size_t);
         char * s_IgnoredBrowser = new char [n_IgnoredBrowser];
         memcpy (s_IgnoredBrowser, (file+nOffset), n_IgnoredBrowser);
         nOffset += n_IgnoredBrowser;
         DECODE_STRING (n_IgnoredBrowser, s_IgnoredBrowser);
         tmp_IgnoredBrowser = s_IgnoredBrowser;
         delete [] s_IgnoredBrowser;

         d_IgnoredBrowser[iIgnoredBrowser] = tmp_IgnoredBrowser;
      }

   // string SearchEngines []
      int arr_size_SearchEngines = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SearchEngines.Alloc (arr_size_SearchEngines);
      for (int iSearchEngines=0; iSearchEngines<(int)arr_size_SearchEngines; iSearchEngines++)
      {
         string tmp_SearchEngines;
         size_t n_SearchEngines = (*(size_t*)(file+nOffset));  // n_SearchEngines = strlen (s_SearchEngines)+1;
         nOffset += sizeof(size_t);
         char * s_SearchEngines = new char [n_SearchEngines];
         memcpy (s_SearchEngines, (file+nOffset), n_SearchEngines);
         nOffset += n_SearchEngines;
         DECODE_STRING (n_SearchEngines, s_SearchEngines);
         tmp_SearchEngines = s_SearchEngines;
         delete [] s_SearchEngines;

         d_SearchEngines[iSearchEngines] = tmp_SearchEngines;
      }

   // string Classifiers []
      int arr_size_Classifiers = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Classifiers.Alloc (arr_size_Classifiers);
      for (int iClassifiers=0; iClassifiers<(int)arr_size_Classifiers; iClassifiers++)
      {
         string tmp_Classifiers;
         size_t n_Classifiers = (*(size_t*)(file+nOffset));  // n_Classifiers = strlen (s_Classifiers)+1;
         nOffset += sizeof(size_t);
         char * s_Classifiers = new char [n_Classifiers];
         memcpy (s_Classifiers, (file+nOffset), n_Classifiers);
         nOffset += n_Classifiers;
         DECODE_STRING (n_Classifiers, s_Classifiers);
         tmp_Classifiers = s_Classifiers;
         delete [] s_Classifiers;

         d_Classifiers[iClassifiers] = tmp_Classifiers;
      }

   // int CachePurgeTime_IPRecord
      d_CachePurgeTime_IPRecord = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_RatingPlaceInfo
      d_CachePurgeTime_RatingPlaceInfo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_SuspiciousInfo
      d_CachePurgeTime_SuspiciousInfo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_SearchWordsInfo
      d_CachePurgeTime_SearchWordsInfo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_DailyReferrerStats
      d_CachePurgeTime_DailyReferrerStats = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_DayStats
      d_CachePurgeTime_DayStats = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_YearStats
      d_CachePurgeTime_YearStats = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_TimeStats
      d_CachePurgeTime_TimeStats = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_ModeratorComment
      d_CachePurgeTime_ModeratorComment = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Keyword
      d_CachePurgeTime_Keyword = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_SiteList
      d_CachePurgeTime_SiteList = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Concept
      d_CachePurgeTime_Concept = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Language
      d_CachePurgeTime_Language = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_VBN
      d_CachePurgeTime_VBN = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Site
      d_CachePurgeTime_Site = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Page
      d_CachePurgeTime_Page = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_BannerProfile
      d_CachePurgeTime_BannerProfile = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Banner
      d_CachePurgeTime_Banner = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_TradeStats
      d_CachePurgeTime_TradeStats = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_User
      d_CachePurgeTime_User = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_ViewerGroup
      d_CachePurgeTime_ViewerGroup = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CachePurgeTime_Viewer
      d_CachePurgeTime_Viewer = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ReloadTimeThreshold
      d_ReloadTimeThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float ViewerCacheReloadThreshold
      d_ViewerCacheReloadThreshold = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int ReloadDistribution []
      int arr_size_ReloadDistribution = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReloadDistribution.Alloc (arr_size_ReloadDistribution);
      OD_LOAD_SIMPLE_ARRAY (int,ReloadDistribution);

   // identifier Viewers []
      int arr_size_Viewers = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Viewers.Alloc (arr_size_Viewers);
      OD_LOAD_SIMPLE_ARRAY (identifier,Viewers);

   // float DefaultPriority
      d_DefaultPriority = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int BannerStore_Expire
      d_BannerStore_Expire = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int BannerStore_MaxLength
      d_BannerStore_MaxLength = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SiteStore_Expire
      d_SiteStore_Expire = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SiteStore_MaxLength
      d_SiteStore_MaxLength = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MaxDailyEventsDefault
      d_MaxDailyEventsDefault = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier TagID1
      d_TagID1 = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier TagID2
      d_TagID2 = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier TagID3
      d_TagID3 = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool TagBool1
      d_TagBool1 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // bool TagBool2
      d_TagBool2 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // bool TagBool3
      d_TagBool3 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int TagInt1
      d_TagInt1 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TagInt2
      d_TagInt2 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TagInt3
      d_TagInt3 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier ReservedID1 []
      int arr_size_ReservedID1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID1.Alloc (arr_size_ReservedID1);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID1);

   // identifier ReservedID2 []
      int arr_size_ReservedID2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID2.Alloc (arr_size_ReservedID2);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID2);

   // identifier ReservedID3 []
      int arr_size_ReservedID3 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID3.Alloc (arr_size_ReservedID3);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID3);

   // int ReservedInt1 []
      int arr_size_ReservedInt1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt1.Alloc (arr_size_ReservedInt1);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt1);

   // int ReservedInt2 []
      int arr_size_ReservedInt2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt2.Alloc (arr_size_ReservedInt2);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt2);

   // int ReservedInt3 []
      int arr_size_ReservedInt3 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt3.Alloc (arr_size_ReservedInt3);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt3);

   // string ReservedString1 []
      int arr_size_ReservedString1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString1.Alloc (arr_size_ReservedString1);
      for (int iReservedString1=0; iReservedString1<(int)arr_size_ReservedString1; iReservedString1++)
      {
         string tmp_ReservedString1;
         size_t n_ReservedString1 = (*(size_t*)(file+nOffset));  // n_ReservedString1 = strlen (s_ReservedString1)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString1 = new char [n_ReservedString1];
         memcpy (s_ReservedString1, (file+nOffset), n_ReservedString1);
         nOffset += n_ReservedString1;
         DECODE_STRING (n_ReservedString1, s_ReservedString1);
         tmp_ReservedString1 = s_ReservedString1;
         delete [] s_ReservedString1;

         d_ReservedString1[iReservedString1] = tmp_ReservedString1;
      }

   // string ReservedString2 []
      int arr_size_ReservedString2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString2.Alloc (arr_size_ReservedString2);
      for (int iReservedString2=0; iReservedString2<(int)arr_size_ReservedString2; iReservedString2++)
      {
         string tmp_ReservedString2;
         size_t n_ReservedString2 = (*(size_t*)(file+nOffset));  // n_ReservedString2 = strlen (s_ReservedString2)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString2 = new char [n_ReservedString2];
         memcpy (s_ReservedString2, (file+nOffset), n_ReservedString2);
         nOffset += n_ReservedString2;
         DECODE_STRING (n_ReservedString2, s_ReservedString2);
         tmp_ReservedString2 = s_ReservedString2;
         delete [] s_ReservedString2;

         d_ReservedString2[iReservedString2] = tmp_ReservedString2;
      }

   // string ReservedString3 []
      int arr_size_ReservedString3 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString3.Alloc (arr_size_ReservedString3);
      for (int iReservedString3=0; iReservedString3<(int)arr_size_ReservedString3; iReservedString3++)
      {
         string tmp_ReservedString3;
         size_t n_ReservedString3 = (*(size_t*)(file+nOffset));  // n_ReservedString3 = strlen (s_ReservedString3)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString3 = new char [n_ReservedString3];
         memcpy (s_ReservedString3, (file+nOffset), n_ReservedString3);
         nOffset += n_ReservedString3;
         DECODE_STRING (n_ReservedString3, s_ReservedString3);
         tmp_ReservedString3 = s_ReservedString3;
         delete [] s_ReservedString3;

         d_ReservedString3[iReservedString3] = tmp_ReservedString3;
      }
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Registry::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string AdminPassword
      n_size += sizeof (size_t);
      n_size += d_AdminPassword.length()+1;

   // identifier ConceptID_Sorted []
      n_size += sizeof (size_t);
      n_size += d_ConceptID_Sorted.GetSize() * sizeof(identifier);

   // int ConceptNo_SortID []
      n_size += sizeof (size_t);
      n_size += d_ConceptNo_SortID.GetSize() * sizeof(int);

   // identifier ConceptID_SortNo []
      n_size += sizeof (size_t);
      n_size += d_ConceptID_SortNo.GetSize() * sizeof(identifier);

   // int ConceptParent_SortNo []
      n_size += sizeof (size_t);
      n_size += d_ConceptParent_SortNo.GetSize() * sizeof(int);

   // int ConceptType_SortNo []
      n_size += sizeof (size_t);
      n_size += d_ConceptType_SortNo.GetSize() * sizeof(int);

   // int ConceptLevel_SortNo []
      n_size += sizeof (size_t);
      n_size += d_ConceptLevel_SortNo.GetSize() * sizeof(int);

   // identifier Language []
      n_size += sizeof (size_t);
      n_size += d_Language.GetSize() * sizeof(identifier);

   // int LanguageNo []
      n_size += sizeof (size_t);
      n_size += d_LanguageNo.GetSize() * sizeof(int);

   // identifier VBN []
      n_size += sizeof (size_t);
      n_size += d_VBN.GetSize() * sizeof(identifier);

   // int VBNNo []
      n_size += sizeof (size_t);
      n_size += d_VBNNo.GetSize() * sizeof(int);

   // identifier ModeratorComment []
      n_size += sizeof (size_t);
      n_size += d_ModeratorComment.GetSize() * sizeof(identifier);

   // int ModeratorCommentNo []
      n_size += sizeof (size_t);
      n_size += d_ModeratorCommentNo.GetSize() * sizeof(int);

   // int CRA_InetAudience []
      n_size += sizeof (size_t);
      n_size += d_CRA_InetAudience.GetSize() * sizeof(int);

   // int CRN_InetAudience []
      n_size += sizeof (size_t);
      n_size += d_CRN_InetAudience.GetSize() * sizeof(int);

   // int CRN_InetAudience_Update
      n_size += sizeof (int);

   // int VisitorHistoryLength
      n_size += sizeof (int);

   // int MinimumHitsTime
      n_size += sizeof (int);

   // int SuspiciousInfoSize
      n_size += sizeof (int);

   // int ActiveViewersSize
      n_size += sizeof (int);

   // int ReturnNumRateSize
      n_size += sizeof (int);

   // int DailyReferrerSize
      n_size += sizeof (int);

   // int ClickNumRateSize
      n_size += sizeof (int);

   // int ShowNumRateSize
      n_size += sizeof (int);

   // int HitNumRateSize
      n_size += sizeof (int);

   // int SessionTimeRateSize
      n_size += sizeof (int);

   // string IgnoredIP []
      n_size += sizeof (size_t);
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         n_size += sizeof (size_t);
         n_size += d_IgnoredIP[iIgnoredIP].length()+1;
      }

   // string IgnoredUserAgent []
      n_size += sizeof (size_t);
      for (int iIgnoredUserAgent=0; iIgnoredUserAgent<d_IgnoredUserAgent.GetSize(); iIgnoredUserAgent++)
      {
         n_size += sizeof (size_t);
         n_size += d_IgnoredUserAgent[iIgnoredUserAgent].length()+1;
      }

   // string IgnoredBrowser []
      n_size += sizeof (size_t);
      for (int iIgnoredBrowser=0; iIgnoredBrowser<d_IgnoredBrowser.GetSize(); iIgnoredBrowser++)
      {
         n_size += sizeof (size_t);
         n_size += d_IgnoredBrowser[iIgnoredBrowser].length()+1;
      }

   // string SearchEngines []
      n_size += sizeof (size_t);
      for (int iSearchEngines=0; iSearchEngines<d_SearchEngines.GetSize(); iSearchEngines++)
      {
         n_size += sizeof (size_t);
         n_size += d_SearchEngines[iSearchEngines].length()+1;
      }

   // string Classifiers []
      n_size += sizeof (size_t);
      for (int iClassifiers=0; iClassifiers<d_Classifiers.GetSize(); iClassifiers++)
      {
         n_size += sizeof (size_t);
         n_size += d_Classifiers[iClassifiers].length()+1;
      }

   // int CachePurgeTime_IPRecord
      n_size += sizeof (int);

   // int CachePurgeTime_RatingPlaceInfo
      n_size += sizeof (int);

   // int CachePurgeTime_SuspiciousInfo
      n_size += sizeof (int);

   // int CachePurgeTime_SearchWordsInfo
      n_size += sizeof (int);

   // int CachePurgeTime_DailyReferrerStats
      n_size += sizeof (int);

   // int CachePurgeTime_DayStats
      n_size += sizeof (int);

   // int CachePurgeTime_YearStats
      n_size += sizeof (int);

   // int CachePurgeTime_TimeStats
      n_size += sizeof (int);

   // int CachePurgeTime_ModeratorComment
      n_size += sizeof (int);

   // int CachePurgeTime_Keyword
      n_size += sizeof (int);

   // int CachePurgeTime_SiteList
      n_size += sizeof (int);

   // int CachePurgeTime_Concept
      n_size += sizeof (int);

   // int CachePurgeTime_Language
      n_size += sizeof (int);

   // int CachePurgeTime_VBN
      n_size += sizeof (int);

   // int CachePurgeTime_Site
      n_size += sizeof (int);

   // int CachePurgeTime_Page
      n_size += sizeof (int);

   // int CachePurgeTime_BannerProfile
      n_size += sizeof (int);

   // int CachePurgeTime_Banner
      n_size += sizeof (int);

   // int CachePurgeTime_TradeStats
      n_size += sizeof (int);

   // int CachePurgeTime_User
      n_size += sizeof (int);

   // int CachePurgeTime_ViewerGroup
      n_size += sizeof (int);

   // int CachePurgeTime_Viewer
      n_size += sizeof (int);

   // int ReloadTimeThreshold
      n_size += sizeof (int);

   // float ViewerCacheReloadThreshold
      n_size += sizeof (float);

   // int ReloadDistribution []
      n_size += sizeof (size_t);
      n_size += d_ReloadDistribution.GetSize() * sizeof(int);

   // identifier Viewers []
      n_size += sizeof (size_t);
      n_size += d_Viewers.GetSize() * sizeof(identifier);

   // float DefaultPriority
      n_size += sizeof (float);

   // int BannerStore_Expire
      n_size += sizeof (int);

   // int BannerStore_MaxLength
      n_size += sizeof (int);

   // int SiteStore_Expire
      n_size += sizeof (int);

   // int SiteStore_MaxLength
      n_size += sizeof (int);

   // int MaxDailyEventsDefault
      n_size += sizeof (int);

   // identifier TagID1
      n_size += sizeof (identifier);

   // identifier TagID2
      n_size += sizeof (identifier);

   // identifier TagID3
      n_size += sizeof (identifier);

   // bool TagBool1
      n_size += sizeof (bool);

   // bool TagBool2
      n_size += sizeof (bool);

   // bool TagBool3
      n_size += sizeof (bool);

   // int TagInt1
      n_size += sizeof (int);

   // int TagInt2
      n_size += sizeof (int);

   // int TagInt3
      n_size += sizeof (int);

   // identifier ReservedID1 []
      n_size += sizeof (size_t);
      n_size += d_ReservedID1.GetSize() * sizeof(identifier);

   // identifier ReservedID2 []
      n_size += sizeof (size_t);
      n_size += d_ReservedID2.GetSize() * sizeof(identifier);

   // identifier ReservedID3 []
      n_size += sizeof (size_t);
      n_size += d_ReservedID3.GetSize() * sizeof(identifier);

   // int ReservedInt1 []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt1.GetSize() * sizeof(int);

   // int ReservedInt2 []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt2.GetSize() * sizeof(int);

   // int ReservedInt3 []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt3.GetSize() * sizeof(int);

   // string ReservedString1 []
      n_size += sizeof (size_t);
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString1[iReservedString1].length()+1;
      }

   // string ReservedString2 []
      n_size += sizeof (size_t);
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString2[iReservedString2].length()+1;
      }

   // string ReservedString3 []
      n_size += sizeof (size_t);
      for (int iReservedString3=0; iReservedString3<d_ReservedString3.GetSize(); iReservedString3++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString3[iReservedString3].length()+1;
      }

      return n_size;
   }

// Запись данных на диск
   bool OD_Registry::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string AdminPassword
      size_t n_AdminPassword = d_AdminPassword.length()+1;
      (*(size_t*)(file+nOffset)) = n_AdminPassword;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_AdminPassword.c_str(), n_AdminPassword);
      ENCODE_STRING (n_AdminPassword, (char*)(file+nOffset));
      nOffset += n_AdminPassword;

   // identifier ConceptID_Sorted []
      (*(size_t*)(file+nOffset)) = d_ConceptID_Sorted.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ConceptID_Sorted);

   // int ConceptNo_SortID []
      (*(size_t*)(file+nOffset)) = d_ConceptNo_SortID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptNo_SortID);

   // identifier ConceptID_SortNo []
      (*(size_t*)(file+nOffset)) = d_ConceptID_SortNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ConceptID_SortNo);

   // int ConceptParent_SortNo []
      (*(size_t*)(file+nOffset)) = d_ConceptParent_SortNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptParent_SortNo);

   // int ConceptType_SortNo []
      (*(size_t*)(file+nOffset)) = d_ConceptType_SortNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptType_SortNo);

   // int ConceptLevel_SortNo []
      (*(size_t*)(file+nOffset)) = d_ConceptLevel_SortNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptLevel_SortNo);

   // identifier Language []
      (*(size_t*)(file+nOffset)) = d_Language.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Language);

   // int LanguageNo []
      (*(size_t*)(file+nOffset)) = d_LanguageNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,LanguageNo);

   // identifier VBN []
      (*(size_t*)(file+nOffset)) = d_VBN.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,VBN);

   // int VBNNo []
      (*(size_t*)(file+nOffset)) = d_VBNNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,VBNNo);

   // identifier ModeratorComment []
      (*(size_t*)(file+nOffset)) = d_ModeratorComment.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ModeratorComment);

   // int ModeratorCommentNo []
      (*(size_t*)(file+nOffset)) = d_ModeratorCommentNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ModeratorCommentNo);

   // int CRA_InetAudience []
      (*(size_t*)(file+nOffset)) = d_CRA_InetAudience.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_InetAudience);

   // int CRN_InetAudience []
      (*(size_t*)(file+nOffset)) = d_CRN_InetAudience.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRN_InetAudience);

   // int CRN_InetAudience_Update
      (*(int*)(file+nOffset)) = d_CRN_InetAudience_Update;
      nOffset += sizeof (int);

   // int VisitorHistoryLength
      (*(int*)(file+nOffset)) = d_VisitorHistoryLength;
      nOffset += sizeof (int);

   // int MinimumHitsTime
      (*(int*)(file+nOffset)) = d_MinimumHitsTime;
      nOffset += sizeof (int);

   // int SuspiciousInfoSize
      (*(int*)(file+nOffset)) = d_SuspiciousInfoSize;
      nOffset += sizeof (int);

   // int ActiveViewersSize
      (*(int*)(file+nOffset)) = d_ActiveViewersSize;
      nOffset += sizeof (int);

   // int ReturnNumRateSize
      (*(int*)(file+nOffset)) = d_ReturnNumRateSize;
      nOffset += sizeof (int);

   // int DailyReferrerSize
      (*(int*)(file+nOffset)) = d_DailyReferrerSize;
      nOffset += sizeof (int);

   // int ClickNumRateSize
      (*(int*)(file+nOffset)) = d_ClickNumRateSize;
      nOffset += sizeof (int);

   // int ShowNumRateSize
      (*(int*)(file+nOffset)) = d_ShowNumRateSize;
      nOffset += sizeof (int);

   // int HitNumRateSize
      (*(int*)(file+nOffset)) = d_HitNumRateSize;
      nOffset += sizeof (int);

   // int SessionTimeRateSize
      (*(int*)(file+nOffset)) = d_SessionTimeRateSize;
      nOffset += sizeof (int);

   // string IgnoredIP []
      (*(size_t*)(file+nOffset)) = d_IgnoredIP.GetSize();
      nOffset += sizeof(size_t);
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         size_t n_IgnoredIP = d_IgnoredIP[iIgnoredIP].length()+1;
         (*(size_t*)(file+nOffset)) = n_IgnoredIP;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_IgnoredIP[iIgnoredIP].c_str(), n_IgnoredIP);
         ENCODE_STRING (n_IgnoredIP, (char*)(file+nOffset));
         nOffset += n_IgnoredIP;
      }

   // string IgnoredUserAgent []
      (*(size_t*)(file+nOffset)) = d_IgnoredUserAgent.GetSize();
      nOffset += sizeof(size_t);
      for (int iIgnoredUserAgent=0; iIgnoredUserAgent<d_IgnoredUserAgent.GetSize(); iIgnoredUserAgent++)
      {
         size_t n_IgnoredUserAgent = d_IgnoredUserAgent[iIgnoredUserAgent].length()+1;
         (*(size_t*)(file+nOffset)) = n_IgnoredUserAgent;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_IgnoredUserAgent[iIgnoredUserAgent].c_str(), n_IgnoredUserAgent);
         ENCODE_STRING (n_IgnoredUserAgent, (char*)(file+nOffset));
         nOffset += n_IgnoredUserAgent;
      }

   // string IgnoredBrowser []
      (*(size_t*)(file+nOffset)) = d_IgnoredBrowser.GetSize();
      nOffset += sizeof(size_t);
      for (int iIgnoredBrowser=0; iIgnoredBrowser<d_IgnoredBrowser.GetSize(); iIgnoredBrowser++)
      {
         size_t n_IgnoredBrowser = d_IgnoredBrowser[iIgnoredBrowser].length()+1;
         (*(size_t*)(file+nOffset)) = n_IgnoredBrowser;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_IgnoredBrowser[iIgnoredBrowser].c_str(), n_IgnoredBrowser);
         ENCODE_STRING (n_IgnoredBrowser, (char*)(file+nOffset));
         nOffset += n_IgnoredBrowser;
      }

   // string SearchEngines []
      (*(size_t*)(file+nOffset)) = d_SearchEngines.GetSize();
      nOffset += sizeof(size_t);
      for (int iSearchEngines=0; iSearchEngines<d_SearchEngines.GetSize(); iSearchEngines++)
      {
         size_t n_SearchEngines = d_SearchEngines[iSearchEngines].length()+1;
         (*(size_t*)(file+nOffset)) = n_SearchEngines;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_SearchEngines[iSearchEngines].c_str(), n_SearchEngines);
         ENCODE_STRING (n_SearchEngines, (char*)(file+nOffset));
         nOffset += n_SearchEngines;
      }

   // string Classifiers []
      (*(size_t*)(file+nOffset)) = d_Classifiers.GetSize();
      nOffset += sizeof(size_t);
      for (int iClassifiers=0; iClassifiers<d_Classifiers.GetSize(); iClassifiers++)
      {
         size_t n_Classifiers = d_Classifiers[iClassifiers].length()+1;
         (*(size_t*)(file+nOffset)) = n_Classifiers;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Classifiers[iClassifiers].c_str(), n_Classifiers);
         ENCODE_STRING (n_Classifiers, (char*)(file+nOffset));
         nOffset += n_Classifiers;
      }

   // int CachePurgeTime_IPRecord
      (*(int*)(file+nOffset)) = d_CachePurgeTime_IPRecord;
      nOffset += sizeof (int);

   // int CachePurgeTime_RatingPlaceInfo
      (*(int*)(file+nOffset)) = d_CachePurgeTime_RatingPlaceInfo;
      nOffset += sizeof (int);

   // int CachePurgeTime_SuspiciousInfo
      (*(int*)(file+nOffset)) = d_CachePurgeTime_SuspiciousInfo;
      nOffset += sizeof (int);

   // int CachePurgeTime_SearchWordsInfo
      (*(int*)(file+nOffset)) = d_CachePurgeTime_SearchWordsInfo;
      nOffset += sizeof (int);

   // int CachePurgeTime_DailyReferrerStats
      (*(int*)(file+nOffset)) = d_CachePurgeTime_DailyReferrerStats;
      nOffset += sizeof (int);

   // int CachePurgeTime_DayStats
      (*(int*)(file+nOffset)) = d_CachePurgeTime_DayStats;
      nOffset += sizeof (int);

   // int CachePurgeTime_YearStats
      (*(int*)(file+nOffset)) = d_CachePurgeTime_YearStats;
      nOffset += sizeof (int);

   // int CachePurgeTime_TimeStats
      (*(int*)(file+nOffset)) = d_CachePurgeTime_TimeStats;
      nOffset += sizeof (int);

   // int CachePurgeTime_ModeratorComment
      (*(int*)(file+nOffset)) = d_CachePurgeTime_ModeratorComment;
      nOffset += sizeof (int);

   // int CachePurgeTime_Keyword
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Keyword;
      nOffset += sizeof (int);

   // int CachePurgeTime_SiteList
      (*(int*)(file+nOffset)) = d_CachePurgeTime_SiteList;
      nOffset += sizeof (int);

   // int CachePurgeTime_Concept
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Concept;
      nOffset += sizeof (int);

   // int CachePurgeTime_Language
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Language;
      nOffset += sizeof (int);

   // int CachePurgeTime_VBN
      (*(int*)(file+nOffset)) = d_CachePurgeTime_VBN;
      nOffset += sizeof (int);

   // int CachePurgeTime_Site
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Site;
      nOffset += sizeof (int);

   // int CachePurgeTime_Page
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Page;
      nOffset += sizeof (int);

   // int CachePurgeTime_BannerProfile
      (*(int*)(file+nOffset)) = d_CachePurgeTime_BannerProfile;
      nOffset += sizeof (int);

   // int CachePurgeTime_Banner
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Banner;
      nOffset += sizeof (int);

   // int CachePurgeTime_TradeStats
      (*(int*)(file+nOffset)) = d_CachePurgeTime_TradeStats;
      nOffset += sizeof (int);

   // int CachePurgeTime_User
      (*(int*)(file+nOffset)) = d_CachePurgeTime_User;
      nOffset += sizeof (int);

   // int CachePurgeTime_ViewerGroup
      (*(int*)(file+nOffset)) = d_CachePurgeTime_ViewerGroup;
      nOffset += sizeof (int);

   // int CachePurgeTime_Viewer
      (*(int*)(file+nOffset)) = d_CachePurgeTime_Viewer;
      nOffset += sizeof (int);

   // int ReloadTimeThreshold
      (*(int*)(file+nOffset)) = d_ReloadTimeThreshold;
      nOffset += sizeof (int);

   // float ViewerCacheReloadThreshold
      (*(float*)(file+nOffset)) = d_ViewerCacheReloadThreshold;
      nOffset += sizeof (float);

   // int ReloadDistribution []
      (*(size_t*)(file+nOffset)) = d_ReloadDistribution.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReloadDistribution);

   // identifier Viewers []
      (*(size_t*)(file+nOffset)) = d_Viewers.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Viewers);

   // float DefaultPriority
      (*(float*)(file+nOffset)) = d_DefaultPriority;
      nOffset += sizeof (float);

   // int BannerStore_Expire
      (*(int*)(file+nOffset)) = d_BannerStore_Expire;
      nOffset += sizeof (int);

   // int BannerStore_MaxLength
      (*(int*)(file+nOffset)) = d_BannerStore_MaxLength;
      nOffset += sizeof (int);

   // int SiteStore_Expire
      (*(int*)(file+nOffset)) = d_SiteStore_Expire;
      nOffset += sizeof (int);

   // int SiteStore_MaxLength
      (*(int*)(file+nOffset)) = d_SiteStore_MaxLength;
      nOffset += sizeof (int);

   // int MaxDailyEventsDefault
      (*(int*)(file+nOffset)) = d_MaxDailyEventsDefault;
      nOffset += sizeof (int);

   // identifier TagID1
      (*(identifier*)(file+nOffset)) = d_TagID1;
      nOffset += sizeof (identifier);

   // identifier TagID2
      (*(identifier*)(file+nOffset)) = d_TagID2;
      nOffset += sizeof (identifier);

   // identifier TagID3
      (*(identifier*)(file+nOffset)) = d_TagID3;
      nOffset += sizeof (identifier);

   // bool TagBool1
      (*(bool*)(file+nOffset)) = d_TagBool1;
      nOffset += sizeof (bool);

   // bool TagBool2
      (*(bool*)(file+nOffset)) = d_TagBool2;
      nOffset += sizeof (bool);

   // bool TagBool3
      (*(bool*)(file+nOffset)) = d_TagBool3;
      nOffset += sizeof (bool);

   // int TagInt1
      (*(int*)(file+nOffset)) = d_TagInt1;
      nOffset += sizeof (int);

   // int TagInt2
      (*(int*)(file+nOffset)) = d_TagInt2;
      nOffset += sizeof (int);

   // int TagInt3
      (*(int*)(file+nOffset)) = d_TagInt3;
      nOffset += sizeof (int);

   // identifier ReservedID1 []
      (*(size_t*)(file+nOffset)) = d_ReservedID1.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID1);

   // identifier ReservedID2 []
      (*(size_t*)(file+nOffset)) = d_ReservedID2.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID2);

   // identifier ReservedID3 []
      (*(size_t*)(file+nOffset)) = d_ReservedID3.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID3);

   // int ReservedInt1 []
      (*(size_t*)(file+nOffset)) = d_ReservedInt1.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt1);

   // int ReservedInt2 []
      (*(size_t*)(file+nOffset)) = d_ReservedInt2.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt2);

   // int ReservedInt3 []
      (*(size_t*)(file+nOffset)) = d_ReservedInt3.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt3);

   // string ReservedString1 []
      (*(size_t*)(file+nOffset)) = d_ReservedString1.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         size_t n_ReservedString1 = d_ReservedString1[iReservedString1].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString1;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString1[iReservedString1].c_str(), n_ReservedString1);
         ENCODE_STRING (n_ReservedString1, (char*)(file+nOffset));
         nOffset += n_ReservedString1;
      }

   // string ReservedString2 []
      (*(size_t*)(file+nOffset)) = d_ReservedString2.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         size_t n_ReservedString2 = d_ReservedString2[iReservedString2].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString2;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString2[iReservedString2].c_str(), n_ReservedString2);
         ENCODE_STRING (n_ReservedString2, (char*)(file+nOffset));
         nOffset += n_ReservedString2;
      }

   // string ReservedString3 []
      (*(size_t*)(file+nOffset)) = d_ReservedString3.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString3=0; iReservedString3<d_ReservedString3.GetSize(); iReservedString3++)
      {
         size_t n_ReservedString3 = d_ReservedString3[iReservedString3].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString3;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString3[iReservedString3].c_str(), n_ReservedString3);
         ENCODE_STRING (n_ReservedString3, (char*)(file+nOffset));
         nOffset += n_ReservedString3;
      }
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Registry::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Registry], objID);
      dbg += SSS;

   // string AdminPassword
      SSS.Format ("AdminPassword = '%s'\n", d_AdminPassword.c_str());
      dbg += SSS;

   // identifier ConceptID_Sorted []
      SSS.Format ("ConceptID_Sorted[].size = %d:\n", d_ConceptID_Sorted.GetSize());
      dbg += SSS;
      for (int iConceptID_Sorted=0; iConceptID_Sorted<d_ConceptID_Sorted.GetSize(); iConceptID_Sorted++)
      {
         SSS.Format ("   ConceptID_Sorted[%d] = %d\n", iConceptID_Sorted, d_ConceptID_Sorted[iConceptID_Sorted]);
         dbg += SSS;
      }

   // int ConceptNo_SortID []
      SSS.Format ("ConceptNo_SortID[].size = %d:\n", d_ConceptNo_SortID.GetSize());
      dbg += SSS;
      for (int iConceptNo_SortID=0; iConceptNo_SortID<d_ConceptNo_SortID.GetSize(); iConceptNo_SortID++)
      {
         SSS.Format ("   ConceptNo_SortID[%d] = %d\n", iConceptNo_SortID, d_ConceptNo_SortID[iConceptNo_SortID]);
         dbg += SSS;
      }

   // identifier ConceptID_SortNo []
      SSS.Format ("ConceptID_SortNo[].size = %d:\n", d_ConceptID_SortNo.GetSize());
      dbg += SSS;
      for (int iConceptID_SortNo=0; iConceptID_SortNo<d_ConceptID_SortNo.GetSize(); iConceptID_SortNo++)
      {
         SSS.Format ("   ConceptID_SortNo[%d] = %d\n", iConceptID_SortNo, d_ConceptID_SortNo[iConceptID_SortNo]);
         dbg += SSS;
      }

   // int ConceptParent_SortNo []
      SSS.Format ("ConceptParent_SortNo[].size = %d:\n", d_ConceptParent_SortNo.GetSize());
      dbg += SSS;
      for (int iConceptParent_SortNo=0; iConceptParent_SortNo<d_ConceptParent_SortNo.GetSize(); iConceptParent_SortNo++)
      {
         SSS.Format ("   ConceptParent_SortNo[%d] = %d\n", iConceptParent_SortNo, d_ConceptParent_SortNo[iConceptParent_SortNo]);
         dbg += SSS;
      }

   // int ConceptType_SortNo []
      SSS.Format ("ConceptType_SortNo[].size = %d:\n", d_ConceptType_SortNo.GetSize());
      dbg += SSS;
      for (int iConceptType_SortNo=0; iConceptType_SortNo<d_ConceptType_SortNo.GetSize(); iConceptType_SortNo++)
      {
         SSS.Format ("   ConceptType_SortNo[%d] = %d\n", iConceptType_SortNo, d_ConceptType_SortNo[iConceptType_SortNo]);
         dbg += SSS;
      }

   // int ConceptLevel_SortNo []
      SSS.Format ("ConceptLevel_SortNo[].size = %d:\n", d_ConceptLevel_SortNo.GetSize());
      dbg += SSS;
      for (int iConceptLevel_SortNo=0; iConceptLevel_SortNo<d_ConceptLevel_SortNo.GetSize(); iConceptLevel_SortNo++)
      {
         SSS.Format ("   ConceptLevel_SortNo[%d] = %d\n", iConceptLevel_SortNo, d_ConceptLevel_SortNo[iConceptLevel_SortNo]);
         dbg += SSS;
      }

   // identifier Language []
      SSS.Format ("Language[].size = %d:\n", d_Language.GetSize());
      dbg += SSS;
      for (int iLanguage=0; iLanguage<d_Language.GetSize(); iLanguage++)
      {
         SSS.Format ("   Language[%d] = %d\n", iLanguage, d_Language[iLanguage]);
         dbg += SSS;
      }

   // int LanguageNo []
      SSS.Format ("LanguageNo[].size = %d:\n", d_LanguageNo.GetSize());
      dbg += SSS;
      for (int iLanguageNo=0; iLanguageNo<d_LanguageNo.GetSize(); iLanguageNo++)
      {
         SSS.Format ("   LanguageNo[%d] = %d\n", iLanguageNo, d_LanguageNo[iLanguageNo]);
         dbg += SSS;
      }

   // identifier VBN []
      SSS.Format ("VBN[].size = %d:\n", d_VBN.GetSize());
      dbg += SSS;
      for (int iVBN=0; iVBN<d_VBN.GetSize(); iVBN++)
      {
         SSS.Format ("   VBN[%d] = %d\n", iVBN, d_VBN[iVBN]);
         dbg += SSS;
      }

   // int VBNNo []
      SSS.Format ("VBNNo[].size = %d:\n", d_VBNNo.GetSize());
      dbg += SSS;
      for (int iVBNNo=0; iVBNNo<d_VBNNo.GetSize(); iVBNNo++)
      {
         SSS.Format ("   VBNNo[%d] = %d\n", iVBNNo, d_VBNNo[iVBNNo]);
         dbg += SSS;
      }

   // identifier ModeratorComment []
      SSS.Format ("ModeratorComment[].size = %d:\n", d_ModeratorComment.GetSize());
      dbg += SSS;
      for (int iModeratorComment=0; iModeratorComment<d_ModeratorComment.GetSize(); iModeratorComment++)
      {
         SSS.Format ("   ModeratorComment[%d] = %d\n", iModeratorComment, d_ModeratorComment[iModeratorComment]);
         dbg += SSS;
      }

   // int ModeratorCommentNo []
      SSS.Format ("ModeratorCommentNo[].size = %d:\n", d_ModeratorCommentNo.GetSize());
      dbg += SSS;
      for (int iModeratorCommentNo=0; iModeratorCommentNo<d_ModeratorCommentNo.GetSize(); iModeratorCommentNo++)
      {
         SSS.Format ("   ModeratorCommentNo[%d] = %d\n", iModeratorCommentNo, d_ModeratorCommentNo[iModeratorCommentNo]);
         dbg += SSS;
      }

   // int CRA_InetAudience []
      SSS.Format ("CRA_InetAudience[].size = %d:\n", d_CRA_InetAudience.GetSize());
      dbg += SSS;
      for (int iCRA_InetAudience=0; iCRA_InetAudience<d_CRA_InetAudience.GetSize(); iCRA_InetAudience++)
      {
         SSS.Format ("   CRA_InetAudience[%d] = %d\n", iCRA_InetAudience, d_CRA_InetAudience[iCRA_InetAudience]);
         dbg += SSS;
      }

   // int CRN_InetAudience []
      SSS.Format ("CRN_InetAudience[].size = %d:\n", d_CRN_InetAudience.GetSize());
      dbg += SSS;
      for (int iCRN_InetAudience=0; iCRN_InetAudience<d_CRN_InetAudience.GetSize(); iCRN_InetAudience++)
      {
         SSS.Format ("   CRN_InetAudience[%d] = %d\n", iCRN_InetAudience, d_CRN_InetAudience[iCRN_InetAudience]);
         dbg += SSS;
      }

   // int CRN_InetAudience_Update
      SSS.Format ("CRN_InetAudience_Update = %d\n", d_CRN_InetAudience_Update);
      dbg += SSS;

   // int VisitorHistoryLength
      SSS.Format ("VisitorHistoryLength = %d\n", d_VisitorHistoryLength);
      dbg += SSS;

   // int MinimumHitsTime
      SSS.Format ("MinimumHitsTime = %d\n", d_MinimumHitsTime);
      dbg += SSS;

   // int SuspiciousInfoSize
      SSS.Format ("SuspiciousInfoSize = %d\n", d_SuspiciousInfoSize);
      dbg += SSS;

   // int ActiveViewersSize
      SSS.Format ("ActiveViewersSize = %d\n", d_ActiveViewersSize);
      dbg += SSS;

   // int ReturnNumRateSize
      SSS.Format ("ReturnNumRateSize = %d\n", d_ReturnNumRateSize);
      dbg += SSS;

   // int DailyReferrerSize
      SSS.Format ("DailyReferrerSize = %d\n", d_DailyReferrerSize);
      dbg += SSS;

   // int ClickNumRateSize
      SSS.Format ("ClickNumRateSize = %d\n", d_ClickNumRateSize);
      dbg += SSS;

   // int ShowNumRateSize
      SSS.Format ("ShowNumRateSize = %d\n", d_ShowNumRateSize);
      dbg += SSS;

   // int HitNumRateSize
      SSS.Format ("HitNumRateSize = %d\n", d_HitNumRateSize);
      dbg += SSS;

   // int SessionTimeRateSize
      SSS.Format ("SessionTimeRateSize = %d\n", d_SessionTimeRateSize);
      dbg += SSS;

   // string IgnoredIP []
      SSS.Format ("IgnoredIP[].size = %d:\n", d_IgnoredIP.GetSize());
      dbg += SSS;
      for (int iIgnoredIP=0; iIgnoredIP<d_IgnoredIP.GetSize(); iIgnoredIP++)
      {
         SSS.Format ("   IgnoredIP[%d] = '%s'\n", iIgnoredIP, d_IgnoredIP[iIgnoredIP].c_str());
         dbg += SSS;
      }

   // string IgnoredUserAgent []
      SSS.Format ("IgnoredUserAgent[].size = %d:\n", d_IgnoredUserAgent.GetSize());
      dbg += SSS;
      for (int iIgnoredUserAgent=0; iIgnoredUserAgent<d_IgnoredUserAgent.GetSize(); iIgnoredUserAgent++)
      {
         SSS.Format ("   IgnoredUserAgent[%d] = '%s'\n", iIgnoredUserAgent, d_IgnoredUserAgent[iIgnoredUserAgent].c_str());
         dbg += SSS;
      }

   // string IgnoredBrowser []
      SSS.Format ("IgnoredBrowser[].size = %d:\n", d_IgnoredBrowser.GetSize());
      dbg += SSS;
      for (int iIgnoredBrowser=0; iIgnoredBrowser<d_IgnoredBrowser.GetSize(); iIgnoredBrowser++)
      {
         SSS.Format ("   IgnoredBrowser[%d] = '%s'\n", iIgnoredBrowser, d_IgnoredBrowser[iIgnoredBrowser].c_str());
         dbg += SSS;
      }

   // string SearchEngines []
      SSS.Format ("SearchEngines[].size = %d:\n", d_SearchEngines.GetSize());
      dbg += SSS;
      for (int iSearchEngines=0; iSearchEngines<d_SearchEngines.GetSize(); iSearchEngines++)
      {
         SSS.Format ("   SearchEngines[%d] = '%s'\n", iSearchEngines, d_SearchEngines[iSearchEngines].c_str());
         dbg += SSS;
      }

   // string Classifiers []
      SSS.Format ("Classifiers[].size = %d:\n", d_Classifiers.GetSize());
      dbg += SSS;
      for (int iClassifiers=0; iClassifiers<d_Classifiers.GetSize(); iClassifiers++)
      {
         SSS.Format ("   Classifiers[%d] = '%s'\n", iClassifiers, d_Classifiers[iClassifiers].c_str());
         dbg += SSS;
      }

   // int CachePurgeTime_IPRecord
      SSS.Format ("CachePurgeTime_IPRecord = %d\n", d_CachePurgeTime_IPRecord);
      dbg += SSS;

   // int CachePurgeTime_RatingPlaceInfo
      SSS.Format ("CachePurgeTime_RatingPlaceInfo = %d\n", d_CachePurgeTime_RatingPlaceInfo);
      dbg += SSS;

   // int CachePurgeTime_SuspiciousInfo
      SSS.Format ("CachePurgeTime_SuspiciousInfo = %d\n", d_CachePurgeTime_SuspiciousInfo);
      dbg += SSS;

   // int CachePurgeTime_SearchWordsInfo
      SSS.Format ("CachePurgeTime_SearchWordsInfo = %d\n", d_CachePurgeTime_SearchWordsInfo);
      dbg += SSS;

   // int CachePurgeTime_DailyReferrerStats
      SSS.Format ("CachePurgeTime_DailyReferrerStats = %d\n", d_CachePurgeTime_DailyReferrerStats);
      dbg += SSS;

   // int CachePurgeTime_DayStats
      SSS.Format ("CachePurgeTime_DayStats = %d\n", d_CachePurgeTime_DayStats);
      dbg += SSS;

   // int CachePurgeTime_YearStats
      SSS.Format ("CachePurgeTime_YearStats = %d\n", d_CachePurgeTime_YearStats);
      dbg += SSS;

   // int CachePurgeTime_TimeStats
      SSS.Format ("CachePurgeTime_TimeStats = %d\n", d_CachePurgeTime_TimeStats);
      dbg += SSS;

   // int CachePurgeTime_ModeratorComment
      SSS.Format ("CachePurgeTime_ModeratorComment = %d\n", d_CachePurgeTime_ModeratorComment);
      dbg += SSS;

   // int CachePurgeTime_Keyword
      SSS.Format ("CachePurgeTime_Keyword = %d\n", d_CachePurgeTime_Keyword);
      dbg += SSS;

   // int CachePurgeTime_SiteList
      SSS.Format ("CachePurgeTime_SiteList = %d\n", d_CachePurgeTime_SiteList);
      dbg += SSS;

   // int CachePurgeTime_Concept
      SSS.Format ("CachePurgeTime_Concept = %d\n", d_CachePurgeTime_Concept);
      dbg += SSS;

   // int CachePurgeTime_Language
      SSS.Format ("CachePurgeTime_Language = %d\n", d_CachePurgeTime_Language);
      dbg += SSS;

   // int CachePurgeTime_VBN
      SSS.Format ("CachePurgeTime_VBN = %d\n", d_CachePurgeTime_VBN);
      dbg += SSS;

   // int CachePurgeTime_Site
      SSS.Format ("CachePurgeTime_Site = %d\n", d_CachePurgeTime_Site);
      dbg += SSS;

   // int CachePurgeTime_Page
      SSS.Format ("CachePurgeTime_Page = %d\n", d_CachePurgeTime_Page);
      dbg += SSS;

   // int CachePurgeTime_BannerProfile
      SSS.Format ("CachePurgeTime_BannerProfile = %d\n", d_CachePurgeTime_BannerProfile);
      dbg += SSS;

   // int CachePurgeTime_Banner
      SSS.Format ("CachePurgeTime_Banner = %d\n", d_CachePurgeTime_Banner);
      dbg += SSS;

   // int CachePurgeTime_TradeStats
      SSS.Format ("CachePurgeTime_TradeStats = %d\n", d_CachePurgeTime_TradeStats);
      dbg += SSS;

   // int CachePurgeTime_User
      SSS.Format ("CachePurgeTime_User = %d\n", d_CachePurgeTime_User);
      dbg += SSS;

   // int CachePurgeTime_ViewerGroup
      SSS.Format ("CachePurgeTime_ViewerGroup = %d\n", d_CachePurgeTime_ViewerGroup);
      dbg += SSS;

   // int CachePurgeTime_Viewer
      SSS.Format ("CachePurgeTime_Viewer = %d\n", d_CachePurgeTime_Viewer);
      dbg += SSS;

   // int ReloadTimeThreshold
      SSS.Format ("ReloadTimeThreshold = %d\n", d_ReloadTimeThreshold);
      dbg += SSS;

   // float ViewerCacheReloadThreshold
      SSS.Format ("ViewerCacheReloadThreshold = %f\n", d_ViewerCacheReloadThreshold);
      dbg += SSS;

   // int ReloadDistribution []
      SSS.Format ("ReloadDistribution[].size = %d:\n", d_ReloadDistribution.GetSize());
      dbg += SSS;
      for (int iReloadDistribution=0; iReloadDistribution<d_ReloadDistribution.GetSize(); iReloadDistribution++)
      {
         SSS.Format ("   ReloadDistribution[%d] = %d\n", iReloadDistribution, d_ReloadDistribution[iReloadDistribution]);
         dbg += SSS;
      }

   // identifier Viewers []
      SSS.Format ("Viewers[].size = %d:\n", d_Viewers.GetSize());
      dbg += SSS;
      for (int iViewers=0; iViewers<d_Viewers.GetSize(); iViewers++)
      {
         SSS.Format ("   Viewers[%d] = %d\n", iViewers, d_Viewers[iViewers]);
         dbg += SSS;
      }

   // float DefaultPriority
      SSS.Format ("DefaultPriority = %f\n", d_DefaultPriority);
      dbg += SSS;

   // int BannerStore_Expire
      SSS.Format ("BannerStore_Expire = %d\n", d_BannerStore_Expire);
      dbg += SSS;

   // int BannerStore_MaxLength
      SSS.Format ("BannerStore_MaxLength = %d\n", d_BannerStore_MaxLength);
      dbg += SSS;

   // int SiteStore_Expire
      SSS.Format ("SiteStore_Expire = %d\n", d_SiteStore_Expire);
      dbg += SSS;

   // int SiteStore_MaxLength
      SSS.Format ("SiteStore_MaxLength = %d\n", d_SiteStore_MaxLength);
      dbg += SSS;

   // int MaxDailyEventsDefault
      SSS.Format ("MaxDailyEventsDefault = %d\n", d_MaxDailyEventsDefault);
      dbg += SSS;

   // identifier TagID1
      SSS.Format ("TagID1 = %d\n", d_TagID1);
      dbg += SSS;

   // identifier TagID2
      SSS.Format ("TagID2 = %d\n", d_TagID2);
      dbg += SSS;

   // identifier TagID3
      SSS.Format ("TagID3 = %d\n", d_TagID3);
      dbg += SSS;

   // bool TagBool1
      SSS.Format ("TagBool1 = %s\n", d_TagBool1?"true":"false");
      dbg += SSS;

   // bool TagBool2
      SSS.Format ("TagBool2 = %s\n", d_TagBool2?"true":"false");
      dbg += SSS;

   // bool TagBool3
      SSS.Format ("TagBool3 = %s\n", d_TagBool3?"true":"false");
      dbg += SSS;

   // int TagInt1
      SSS.Format ("TagInt1 = %d\n", d_TagInt1);
      dbg += SSS;

   // int TagInt2
      SSS.Format ("TagInt2 = %d\n", d_TagInt2);
      dbg += SSS;

   // int TagInt3
      SSS.Format ("TagInt3 = %d\n", d_TagInt3);
      dbg += SSS;

   // identifier ReservedID1 []
      SSS.Format ("ReservedID1[].size = %d:\n", d_ReservedID1.GetSize());
      dbg += SSS;
      for (int iReservedID1=0; iReservedID1<d_ReservedID1.GetSize(); iReservedID1++)
      {
         SSS.Format ("   ReservedID1[%d] = %d\n", iReservedID1, d_ReservedID1[iReservedID1]);
         dbg += SSS;
      }

   // identifier ReservedID2 []
      SSS.Format ("ReservedID2[].size = %d:\n", d_ReservedID2.GetSize());
      dbg += SSS;
      for (int iReservedID2=0; iReservedID2<d_ReservedID2.GetSize(); iReservedID2++)
      {
         SSS.Format ("   ReservedID2[%d] = %d\n", iReservedID2, d_ReservedID2[iReservedID2]);
         dbg += SSS;
      }

   // identifier ReservedID3 []
      SSS.Format ("ReservedID3[].size = %d:\n", d_ReservedID3.GetSize());
      dbg += SSS;
      for (int iReservedID3=0; iReservedID3<d_ReservedID3.GetSize(); iReservedID3++)
      {
         SSS.Format ("   ReservedID3[%d] = %d\n", iReservedID3, d_ReservedID3[iReservedID3]);
         dbg += SSS;
      }

   // int ReservedInt1 []
      SSS.Format ("ReservedInt1[].size = %d:\n", d_ReservedInt1.GetSize());
      dbg += SSS;
      for (int iReservedInt1=0; iReservedInt1<d_ReservedInt1.GetSize(); iReservedInt1++)
      {
         SSS.Format ("   ReservedInt1[%d] = %d\n", iReservedInt1, d_ReservedInt1[iReservedInt1]);
         dbg += SSS;
      }

   // int ReservedInt2 []
      SSS.Format ("ReservedInt2[].size = %d:\n", d_ReservedInt2.GetSize());
      dbg += SSS;
      for (int iReservedInt2=0; iReservedInt2<d_ReservedInt2.GetSize(); iReservedInt2++)
      {
         SSS.Format ("   ReservedInt2[%d] = %d\n", iReservedInt2, d_ReservedInt2[iReservedInt2]);
         dbg += SSS;
      }

   // int ReservedInt3 []
      SSS.Format ("ReservedInt3[].size = %d:\n", d_ReservedInt3.GetSize());
      dbg += SSS;
      for (int iReservedInt3=0; iReservedInt3<d_ReservedInt3.GetSize(); iReservedInt3++)
      {
         SSS.Format ("   ReservedInt3[%d] = %d\n", iReservedInt3, d_ReservedInt3[iReservedInt3]);
         dbg += SSS;
      }

   // string ReservedString1 []
      SSS.Format ("ReservedString1[].size = %d:\n", d_ReservedString1.GetSize());
      dbg += SSS;
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         SSS.Format ("   ReservedString1[%d] = '%s'\n", iReservedString1, d_ReservedString1[iReservedString1].c_str());
         dbg += SSS;
      }

   // string ReservedString2 []
      SSS.Format ("ReservedString2[].size = %d:\n", d_ReservedString2.GetSize());
      dbg += SSS;
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         SSS.Format ("   ReservedString2[%d] = '%s'\n", iReservedString2, d_ReservedString2[iReservedString2].c_str());
         dbg += SSS;
      }

   // string ReservedString3 []
      SSS.Format ("ReservedString3[].size = %d:\n", d_ReservedString3.GetSize());
      dbg += SSS;
      for (int iReservedString3=0; iReservedString3<d_ReservedString3.GetSize(); iReservedString3++)
      {
         SSS.Format ("   ReservedString3[%d] = '%s'\n", iReservedString3, d_ReservedString3[iReservedString3].c_str());
         dbg += SSS;
      }
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_VBN::OD_VBN (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_VBN;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_IsModerated = false;
      d_DefaultLanguage = NA;
      d_DefaultTZOffset = 0;
      d_Owner = NA;
      d_ConceptMask.Alloc (0);
      d_AdminEventList = NA;
      d_No = 255;
      d_OnlineVisitors = 0;
      d_ActiveViewersID.Alloc (0);
      d_ActiveViewersHosts.Alloc (0);
      d_Hits = NA;
      d_Hosts = NA;
      d_Visitors = NA;
      d_Shows = NA;
      d_Clicks = NA;
      d_SessionTime = NA;
      d_SessionNum = NA;
      d_Total_Hosts = 0;
      d_Total_Shows = 0;
      d_Total_Clicks = 0;
      d_Total_Hits = 0;
      d_Total_Visitors = 0;
      d_Total_VisitorReturns = 0;
      d_Total_AveSessionTime = 0;
      d_Total_AveReloadTime = 0;
      d_Total_AveReloadNum = 0;
      d_LM_Visitors = 0;
      d_LM_VisitorReturns = 0;
      d_LM_VisitorReturns_Prc = 0;
      d_LM_Hosts = 0;
      d_LM_Shows = 0;
      d_LM_Clicks = 0;
      d_LM_Hits = 0;
      d_LM_AveSessionTime = 0;
      d_LM_AveReloadTime = 0;
      d_LM_AveReloadNum = 0;
      d_LW_Visitors = 0;
      d_LW_VisitorReturns = 0;
      d_LW_VisitorReturns_Prc = 0;
      d_LW_Hosts = 0;
      d_LW_Shows = 0;
      d_LW_Clicks = 0;
      d_LW_Hits = 0;
      d_LW_AveSessionTime = 0;
      d_LW_AveReloadTime = 0;
      d_LW_AveReloadNum = 0;
      d_LD_Visitors = 0;
      d_LD_VisitorReturns = 0;
      d_LD_VisitorReturns_Prc = 0;
      d_LD_Hosts = 0;
      d_LD_Shows = 0;
      d_LD_Clicks = 0;
      d_LD_Hits = 0;
      d_LD_AveSessionTime = 0;
      d_LD_AveReloadTime = 0;
      d_LD_AveReloadNum = 0;
      d_LH_Visitors = 0;
      d_LH_VisitorReturns = 0;
      d_LH_VisitorReturns_Prc = 0;
      d_LH_Hosts = 0;
      d_LH_Shows = 0;
      d_LH_Clicks = 0;
      d_LH_Hits = 0;
      d_LH_AveSessionTime = 0;
      d_LH_AveReloadTime = 0;
      d_LH_AveReloadNum = 0;
      d_TagBool1 = false;
      d_TagBool2 = false;
      d_TagID1 = NA;
      d_TagID2 = NA;
      d_TagInt1 = 0;
      d_TagInt2 = 0;
      d_TagFloat1 = (float) 0.0;
      d_TagFloat2 = (float) 0.0;
      d_ReservedID1.Alloc (0);
      d_ReservedID2.Alloc (0);
      d_ReservedInt1.Alloc (0);
      d_ReservedInt2.Alloc (0);
      d_ReservedString1.Alloc (0);
      d_ReservedString2.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_VBN::~OD_VBN () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_VBN::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Password;                   break;
         case 2: ka += d_Name;                       break;
         case 3: ka += d_Description;                break;
         case 4: ka += d_IsModerated;                break;
         case 5: ka += d_DefaultLanguage;            break;
         case 6: ka += d_DefaultTZOffset;            break;
         case 7: ka += d_Owner;                      break;
         case 9: ka += d_AdminEventList;             break;
         case 10: ka += d_No;                         break;
         case 11: ka += d_OnlineVisitors;             break;
         case 14: ka += d_Hits;                       break;
         case 15: ka += d_Hosts;                      break;
         case 16: ka += d_Visitors;                   break;
         case 17: ka += d_Shows;                      break;
         case 18: ka += d_Clicks;                     break;
         case 19: ka += d_SessionTime;                break;
         case 20: ka += d_SessionNum;                 break;
         case 21: ka += d_Total_Hosts;                break;
         case 22: ka += d_Total_Shows;                break;
         case 23: ka += d_Total_Clicks;               break;
         case 24: ka += d_Total_Hits;                 break;
         case 25: ka += d_Total_Visitors;             break;
         case 26: ka += d_Total_VisitorReturns;       break;
         case 27: ka += d_Total_AveSessionTime;       break;
         case 28: ka += d_Total_AveReloadTime;        break;
         case 29: ka += d_Total_AveReloadNum;         break;
         case 30: ka += d_LM_Visitors;                break;
         case 31: ka += d_LM_VisitorReturns;          break;
         case 32: ka += d_LM_VisitorReturns_Prc;      break;
         case 33: ka += d_LM_Hosts;                   break;
         case 34: ka += d_LM_Shows;                   break;
         case 35: ka += d_LM_Clicks;                  break;
         case 36: ka += d_LM_Hits;                    break;
         case 37: ka += d_LM_AveSessionTime;          break;
         case 38: ka += d_LM_AveReloadTime;           break;
         case 39: ka += d_LM_AveReloadNum;            break;
         case 40: ka += d_LW_Visitors;                break;
         case 41: ka += d_LW_VisitorReturns;          break;
         case 42: ka += d_LW_VisitorReturns_Prc;      break;
         case 43: ka += d_LW_Hosts;                   break;
         case 44: ka += d_LW_Shows;                   break;
         case 45: ka += d_LW_Clicks;                  break;
         case 46: ka += d_LW_Hits;                    break;
         case 47: ka += d_LW_AveSessionTime;          break;
         case 48: ka += d_LW_AveReloadTime;           break;
         case 49: ka += d_LW_AveReloadNum;            break;
         case 50: ka += d_LD_Visitors;                break;
         case 51: ka += d_LD_VisitorReturns;          break;
         case 52: ka += d_LD_VisitorReturns_Prc;      break;
         case 53: ka += d_LD_Hosts;                   break;
         case 54: ka += d_LD_Shows;                   break;
         case 55: ka += d_LD_Clicks;                  break;
         case 56: ka += d_LD_Hits;                    break;
         case 57: ka += d_LD_AveSessionTime;          break;
         case 58: ka += d_LD_AveReloadTime;           break;
         case 59: ka += d_LD_AveReloadNum;            break;
         case 60: ka += d_LH_Visitors;                break;
         case 61: ka += d_LH_VisitorReturns;          break;
         case 62: ka += d_LH_VisitorReturns_Prc;      break;
         case 63: ka += d_LH_Hosts;                   break;
         case 64: ka += d_LH_Shows;                   break;
         case 65: ka += d_LH_Clicks;                  break;
         case 66: ka += d_LH_Hits;                    break;
         case 67: ka += d_LH_AveSessionTime;          break;
         case 68: ka += d_LH_AveReloadTime;           break;
         case 69: ka += d_LH_AveReloadNum;            break;
         case 70: ka += d_TagBool1;                   break;
         case 71: ka += d_TagBool2;                   break;
         case 72: ka += d_TagID1;                     break;
         case 73: ka += d_TagID2;                     break;
         case 74: ka += d_TagInt1;                    break;
         case 75: ka += d_TagInt2;                    break;
         case 76: ka += d_TagFloat1;                  break;
         case 77: ka += d_TagFloat2;                  break;
         case 78: ka += d_TagString1;                 break;
         case 79: ka += d_TagString2;                 break;
         case 86: ka += d_CacheTime;                  break;
      }
   }


// Загрузка объекта с диска
   size_t OD_VBN::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Password
      size_t n_Password = (*(size_t*)(file+nOffset));  // n_Password = strlen (s_Password)+1;
      nOffset += sizeof(size_t);
      char * s_Password = new char [n_Password];
      memcpy (s_Password, (file+nOffset), n_Password);
      nOffset += n_Password;
      DECODE_STRING (n_Password, s_Password);
      d_Password = s_Password;
      delete [] s_Password;

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description];
      memcpy (s_Description, (file+nOffset), n_Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // bool IsModerated
      d_IsModerated = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier DefaultLanguage
      d_DefaultLanguage = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int DefaultTZOffset
      d_DefaultTZOffset = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Owner
      d_Owner = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // byte ConceptMask []
      int arr_size_ConceptMask = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptMask.Alloc (arr_size_ConceptMask);
      OD_LOAD_SIMPLE_ARRAY (byte,ConceptMask);

   // identifier AdminEventList
      d_AdminEventList = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // byte No
      d_No = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // int OnlineVisitors
      d_OnlineVisitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier ActiveViewersID []
      int arr_size_ActiveViewersID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ActiveViewersID.Alloc (arr_size_ActiveViewersID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ActiveViewersID);

   // int ActiveViewersHosts []
      int arr_size_ActiveViewersHosts = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ActiveViewersHosts.Alloc (arr_size_ActiveViewersHosts);
      OD_LOAD_SIMPLE_ARRAY (int,ActiveViewersHosts);

   // identifier Hits
      d_Hits = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Hosts
      d_Hosts = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Visitors
      d_Visitors = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Shows
      d_Shows = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Clicks
      d_Clicks = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SessionTime
      d_SessionTime = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier SessionNum
      d_SessionNum = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Total_Hosts
      d_Total_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Shows
      d_Total_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Clicks
      d_Total_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Hits
      d_Total_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Visitors
      d_Total_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_VisitorReturns
      d_Total_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveSessionTime
      d_Total_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveReloadTime
      d_Total_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_AveReloadNum
      d_Total_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Visitors
      d_LM_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_VisitorReturns
      d_LM_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_VisitorReturns_Prc
      d_LM_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hosts
      d_LM_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Shows
      d_LM_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Clicks
      d_LM_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hits
      d_LM_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveSessionTime
      d_LM_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveReloadTime
      d_LM_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_AveReloadNum
      d_LM_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Visitors
      d_LW_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_VisitorReturns
      d_LW_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_VisitorReturns_Prc
      d_LW_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hosts
      d_LW_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Shows
      d_LW_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Clicks
      d_LW_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hits
      d_LW_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveSessionTime
      d_LW_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveReloadTime
      d_LW_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_AveReloadNum
      d_LW_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Visitors
      d_LD_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_VisitorReturns
      d_LD_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_VisitorReturns_Prc
      d_LD_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hosts
      d_LD_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Shows
      d_LD_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Clicks
      d_LD_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hits
      d_LD_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveSessionTime
      d_LD_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveReloadTime
      d_LD_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_AveReloadNum
      d_LD_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Visitors
      d_LH_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_VisitorReturns
      d_LH_VisitorReturns = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_VisitorReturns_Prc
      d_LH_VisitorReturns_Prc = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hosts
      d_LH_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Shows
      d_LH_Shows = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Clicks
      d_LH_Clicks = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hits
      d_LH_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveSessionTime
      d_LH_AveSessionTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveReloadTime
      d_LH_AveReloadTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_AveReloadNum
      d_LH_AveReloadNum = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool1
      d_TagBool1 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // bool TagBool2
      d_TagBool2 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier TagID1
      d_TagID1 = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier TagID2
      d_TagID2 = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt1
      d_TagInt1 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TagInt2
      d_TagInt2 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float TagFloat1
      d_TagFloat1 = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // float TagFloat2
      d_TagFloat2 = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // string TagString1
      size_t n_TagString1 = (*(size_t*)(file+nOffset));  // n_TagString1 = strlen (s_TagString1)+1;
      nOffset += sizeof(size_t);
      char * s_TagString1 = new char [n_TagString1];
      memcpy (s_TagString1, (file+nOffset), n_TagString1);
      nOffset += n_TagString1;
      DECODE_STRING (n_TagString1, s_TagString1);
      d_TagString1 = s_TagString1;
      delete [] s_TagString1;

   // string TagString2
      size_t n_TagString2 = (*(size_t*)(file+nOffset));  // n_TagString2 = strlen (s_TagString2)+1;
      nOffset += sizeof(size_t);
      char * s_TagString2 = new char [n_TagString2];
      memcpy (s_TagString2, (file+nOffset), n_TagString2);
      nOffset += n_TagString2;
      DECODE_STRING (n_TagString2, s_TagString2);
      d_TagString2 = s_TagString2;
      delete [] s_TagString2;

   // identifier ReservedID1 []
      int arr_size_ReservedID1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID1.Alloc (arr_size_ReservedID1);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID1);

   // identifier ReservedID2 []
      int arr_size_ReservedID2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID2.Alloc (arr_size_ReservedID2);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID2);

   // int ReservedInt1 []
      int arr_size_ReservedInt1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt1.Alloc (arr_size_ReservedInt1);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt1);

   // int ReservedInt2 []
      int arr_size_ReservedInt2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt2.Alloc (arr_size_ReservedInt2);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt2);

   // string ReservedString1 []
      int arr_size_ReservedString1 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString1.Alloc (arr_size_ReservedString1);
      for (int iReservedString1=0; iReservedString1<(int)arr_size_ReservedString1; iReservedString1++)
      {
         string tmp_ReservedString1;
         size_t n_ReservedString1 = (*(size_t*)(file+nOffset));  // n_ReservedString1 = strlen (s_ReservedString1)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString1 = new char [n_ReservedString1];
         memcpy (s_ReservedString1, (file+nOffset), n_ReservedString1);
         nOffset += n_ReservedString1;
         DECODE_STRING (n_ReservedString1, s_ReservedString1);
         tmp_ReservedString1 = s_ReservedString1;
         delete [] s_ReservedString1;

         d_ReservedString1[iReservedString1] = tmp_ReservedString1;
      }

   // string ReservedString2 []
      int arr_size_ReservedString2 = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString2.Alloc (arr_size_ReservedString2);
      for (int iReservedString2=0; iReservedString2<(int)arr_size_ReservedString2; iReservedString2++)
      {
         string tmp_ReservedString2;
         size_t n_ReservedString2 = (*(size_t*)(file+nOffset));  // n_ReservedString2 = strlen (s_ReservedString2)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString2 = new char [n_ReservedString2];
         memcpy (s_ReservedString2, (file+nOffset), n_ReservedString2);
         nOffset += n_ReservedString2;
         DECODE_STRING (n_ReservedString2, s_ReservedString2);
         tmp_ReservedString2 = s_ReservedString2;
         delete [] s_ReservedString2;

         d_ReservedString2[iReservedString2] = tmp_ReservedString2;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_VBN::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Password
      n_size += sizeof (size_t);
      n_size += d_Password.length()+1;

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // bool IsModerated
      n_size += sizeof (bool);

   // identifier DefaultLanguage
      n_size += sizeof (identifier);

   // int DefaultTZOffset
      n_size += sizeof (int);

   // identifier Owner
      n_size += sizeof (identifier);

   // byte ConceptMask []
      n_size += sizeof (size_t);
      n_size += d_ConceptMask.GetSize() * sizeof(byte);

   // identifier AdminEventList
      n_size += sizeof (identifier);

   // byte No
      n_size += sizeof (byte);

   // int OnlineVisitors
      n_size += sizeof (int);

   // identifier ActiveViewersID []
      n_size += sizeof (size_t);
      n_size += d_ActiveViewersID.GetSize() * sizeof(identifier);

   // int ActiveViewersHosts []
      n_size += sizeof (size_t);
      n_size += d_ActiveViewersHosts.GetSize() * sizeof(int);

   // identifier Hits
      n_size += sizeof (identifier);

   // identifier Hosts
      n_size += sizeof (identifier);

   // identifier Visitors
      n_size += sizeof (identifier);

   // identifier Shows
      n_size += sizeof (identifier);

   // identifier Clicks
      n_size += sizeof (identifier);

   // identifier SessionTime
      n_size += sizeof (identifier);

   // identifier SessionNum
      n_size += sizeof (identifier);

   // int Total_Hosts
      n_size += sizeof (int);

   // int Total_Shows
      n_size += sizeof (int);

   // int Total_Clicks
      n_size += sizeof (int);

   // int Total_Hits
      n_size += sizeof (int);

   // int Total_Visitors
      n_size += sizeof (int);

   // int Total_VisitorReturns
      n_size += sizeof (int);

   // int Total_AveSessionTime
      n_size += sizeof (int);

   // int Total_AveReloadTime
      n_size += sizeof (int);

   // int Total_AveReloadNum
      n_size += sizeof (int);

   // int LM_Visitors
      n_size += sizeof (int);

   // int LM_VisitorReturns
      n_size += sizeof (int);

   // int LM_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LM_Hosts
      n_size += sizeof (int);

   // int LM_Shows
      n_size += sizeof (int);

   // int LM_Clicks
      n_size += sizeof (int);

   // int LM_Hits
      n_size += sizeof (int);

   // int LM_AveSessionTime
      n_size += sizeof (int);

   // int LM_AveReloadTime
      n_size += sizeof (int);

   // int LM_AveReloadNum
      n_size += sizeof (int);

   // int LW_Visitors
      n_size += sizeof (int);

   // int LW_VisitorReturns
      n_size += sizeof (int);

   // int LW_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LW_Hosts
      n_size += sizeof (int);

   // int LW_Shows
      n_size += sizeof (int);

   // int LW_Clicks
      n_size += sizeof (int);

   // int LW_Hits
      n_size += sizeof (int);

   // int LW_AveSessionTime
      n_size += sizeof (int);

   // int LW_AveReloadTime
      n_size += sizeof (int);

   // int LW_AveReloadNum
      n_size += sizeof (int);

   // int LD_Visitors
      n_size += sizeof (int);

   // int LD_VisitorReturns
      n_size += sizeof (int);

   // int LD_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LD_Hosts
      n_size += sizeof (int);

   // int LD_Shows
      n_size += sizeof (int);

   // int LD_Clicks
      n_size += sizeof (int);

   // int LD_Hits
      n_size += sizeof (int);

   // int LD_AveSessionTime
      n_size += sizeof (int);

   // int LD_AveReloadTime
      n_size += sizeof (int);

   // int LD_AveReloadNum
      n_size += sizeof (int);

   // int LH_Visitors
      n_size += sizeof (int);

   // int LH_VisitorReturns
      n_size += sizeof (int);

   // int LH_VisitorReturns_Prc
      n_size += sizeof (int);

   // int LH_Hosts
      n_size += sizeof (int);

   // int LH_Shows
      n_size += sizeof (int);

   // int LH_Clicks
      n_size += sizeof (int);

   // int LH_Hits
      n_size += sizeof (int);

   // int LH_AveSessionTime
      n_size += sizeof (int);

   // int LH_AveReloadTime
      n_size += sizeof (int);

   // int LH_AveReloadNum
      n_size += sizeof (int);

   // bool TagBool1
      n_size += sizeof (bool);

   // bool TagBool2
      n_size += sizeof (bool);

   // identifier TagID1
      n_size += sizeof (identifier);

   // identifier TagID2
      n_size += sizeof (identifier);

   // int TagInt1
      n_size += sizeof (int);

   // int TagInt2
      n_size += sizeof (int);

   // float TagFloat1
      n_size += sizeof (float);

   // float TagFloat2
      n_size += sizeof (float);

   // string TagString1
      n_size += sizeof (size_t);
      n_size += d_TagString1.length()+1;

   // string TagString2
      n_size += sizeof (size_t);
      n_size += d_TagString2.length()+1;

   // identifier ReservedID1 []
      n_size += sizeof (size_t);
      n_size += d_ReservedID1.GetSize() * sizeof(identifier);

   // identifier ReservedID2 []
      n_size += sizeof (size_t);
      n_size += d_ReservedID2.GetSize() * sizeof(identifier);

   // int ReservedInt1 []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt1.GetSize() * sizeof(int);

   // int ReservedInt2 []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt2.GetSize() * sizeof(int);

   // string ReservedString1 []
      n_size += sizeof (size_t);
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString1[iReservedString1].length()+1;
      }

   // string ReservedString2 []
      n_size += sizeof (size_t);
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString2[iReservedString2].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_VBN::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Password
      size_t n_Password = d_Password.length()+1;
      (*(size_t*)(file+nOffset)) = n_Password;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Password.c_str(), n_Password);
      ENCODE_STRING (n_Password, (char*)(file+nOffset));
      nOffset += n_Password;

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Description
      size_t n_Description = d_Description.length()+1;
      (*(size_t*)(file+nOffset)) = n_Description;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Description.c_str(), n_Description);
      ENCODE_STRING (n_Description, (char*)(file+nOffset));
      nOffset += n_Description;

   // bool IsModerated
      (*(bool*)(file+nOffset)) = d_IsModerated;
      nOffset += sizeof (bool);

   // identifier DefaultLanguage
      (*(identifier*)(file+nOffset)) = d_DefaultLanguage;
      nOffset += sizeof (identifier);

   // int DefaultTZOffset
      (*(int*)(file+nOffset)) = d_DefaultTZOffset;
      nOffset += sizeof (int);

   // identifier Owner
      (*(identifier*)(file+nOffset)) = d_Owner;
      nOffset += sizeof (identifier);

   // byte ConceptMask []
      (*(size_t*)(file+nOffset)) = d_ConceptMask.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,ConceptMask);

   // identifier AdminEventList
      (*(identifier*)(file+nOffset)) = d_AdminEventList;
      nOffset += sizeof (identifier);

   // byte No
      (*(byte*)(file+nOffset)) = d_No;
      nOffset += sizeof (byte);

   // int OnlineVisitors
      (*(int*)(file+nOffset)) = d_OnlineVisitors;
      nOffset += sizeof (int);

   // identifier ActiveViewersID []
      (*(size_t*)(file+nOffset)) = d_ActiveViewersID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ActiveViewersID);

   // int ActiveViewersHosts []
      (*(size_t*)(file+nOffset)) = d_ActiveViewersHosts.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ActiveViewersHosts);

   // identifier Hits
      (*(identifier*)(file+nOffset)) = d_Hits;
      nOffset += sizeof (identifier);

   // identifier Hosts
      (*(identifier*)(file+nOffset)) = d_Hosts;
      nOffset += sizeof (identifier);

   // identifier Visitors
      (*(identifier*)(file+nOffset)) = d_Visitors;
      nOffset += sizeof (identifier);

   // identifier Shows
      (*(identifier*)(file+nOffset)) = d_Shows;
      nOffset += sizeof (identifier);

   // identifier Clicks
      (*(identifier*)(file+nOffset)) = d_Clicks;
      nOffset += sizeof (identifier);

   // identifier SessionTime
      (*(identifier*)(file+nOffset)) = d_SessionTime;
      nOffset += sizeof (identifier);

   // identifier SessionNum
      (*(identifier*)(file+nOffset)) = d_SessionNum;
      nOffset += sizeof (identifier);

   // int Total_Hosts
      (*(int*)(file+nOffset)) = d_Total_Hosts;
      nOffset += sizeof (int);

   // int Total_Shows
      (*(int*)(file+nOffset)) = d_Total_Shows;
      nOffset += sizeof (int);

   // int Total_Clicks
      (*(int*)(file+nOffset)) = d_Total_Clicks;
      nOffset += sizeof (int);

   // int Total_Hits
      (*(int*)(file+nOffset)) = d_Total_Hits;
      nOffset += sizeof (int);

   // int Total_Visitors
      (*(int*)(file+nOffset)) = d_Total_Visitors;
      nOffset += sizeof (int);

   // int Total_VisitorReturns
      (*(int*)(file+nOffset)) = d_Total_VisitorReturns;
      nOffset += sizeof (int);

   // int Total_AveSessionTime
      (*(int*)(file+nOffset)) = d_Total_AveSessionTime;
      nOffset += sizeof (int);

   // int Total_AveReloadTime
      (*(int*)(file+nOffset)) = d_Total_AveReloadTime;
      nOffset += sizeof (int);

   // int Total_AveReloadNum
      (*(int*)(file+nOffset)) = d_Total_AveReloadNum;
      nOffset += sizeof (int);

   // int LM_Visitors
      (*(int*)(file+nOffset)) = d_LM_Visitors;
      nOffset += sizeof (int);

   // int LM_VisitorReturns
      (*(int*)(file+nOffset)) = d_LM_VisitorReturns;
      nOffset += sizeof (int);

   // int LM_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LM_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LM_Hosts
      (*(int*)(file+nOffset)) = d_LM_Hosts;
      nOffset += sizeof (int);

   // int LM_Shows
      (*(int*)(file+nOffset)) = d_LM_Shows;
      nOffset += sizeof (int);

   // int LM_Clicks
      (*(int*)(file+nOffset)) = d_LM_Clicks;
      nOffset += sizeof (int);

   // int LM_Hits
      (*(int*)(file+nOffset)) = d_LM_Hits;
      nOffset += sizeof (int);

   // int LM_AveSessionTime
      (*(int*)(file+nOffset)) = d_LM_AveSessionTime;
      nOffset += sizeof (int);

   // int LM_AveReloadTime
      (*(int*)(file+nOffset)) = d_LM_AveReloadTime;
      nOffset += sizeof (int);

   // int LM_AveReloadNum
      (*(int*)(file+nOffset)) = d_LM_AveReloadNum;
      nOffset += sizeof (int);

   // int LW_Visitors
      (*(int*)(file+nOffset)) = d_LW_Visitors;
      nOffset += sizeof (int);

   // int LW_VisitorReturns
      (*(int*)(file+nOffset)) = d_LW_VisitorReturns;
      nOffset += sizeof (int);

   // int LW_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LW_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LW_Hosts
      (*(int*)(file+nOffset)) = d_LW_Hosts;
      nOffset += sizeof (int);

   // int LW_Shows
      (*(int*)(file+nOffset)) = d_LW_Shows;
      nOffset += sizeof (int);

   // int LW_Clicks
      (*(int*)(file+nOffset)) = d_LW_Clicks;
      nOffset += sizeof (int);

   // int LW_Hits
      (*(int*)(file+nOffset)) = d_LW_Hits;
      nOffset += sizeof (int);

   // int LW_AveSessionTime
      (*(int*)(file+nOffset)) = d_LW_AveSessionTime;
      nOffset += sizeof (int);

   // int LW_AveReloadTime
      (*(int*)(file+nOffset)) = d_LW_AveReloadTime;
      nOffset += sizeof (int);

   // int LW_AveReloadNum
      (*(int*)(file+nOffset)) = d_LW_AveReloadNum;
      nOffset += sizeof (int);

   // int LD_Visitors
      (*(int*)(file+nOffset)) = d_LD_Visitors;
      nOffset += sizeof (int);

   // int LD_VisitorReturns
      (*(int*)(file+nOffset)) = d_LD_VisitorReturns;
      nOffset += sizeof (int);

   // int LD_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LD_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LD_Hosts
      (*(int*)(file+nOffset)) = d_LD_Hosts;
      nOffset += sizeof (int);

   // int LD_Shows
      (*(int*)(file+nOffset)) = d_LD_Shows;
      nOffset += sizeof (int);

   // int LD_Clicks
      (*(int*)(file+nOffset)) = d_LD_Clicks;
      nOffset += sizeof (int);

   // int LD_Hits
      (*(int*)(file+nOffset)) = d_LD_Hits;
      nOffset += sizeof (int);

   // int LD_AveSessionTime
      (*(int*)(file+nOffset)) = d_LD_AveSessionTime;
      nOffset += sizeof (int);

   // int LD_AveReloadTime
      (*(int*)(file+nOffset)) = d_LD_AveReloadTime;
      nOffset += sizeof (int);

   // int LD_AveReloadNum
      (*(int*)(file+nOffset)) = d_LD_AveReloadNum;
      nOffset += sizeof (int);

   // int LH_Visitors
      (*(int*)(file+nOffset)) = d_LH_Visitors;
      nOffset += sizeof (int);

   // int LH_VisitorReturns
      (*(int*)(file+nOffset)) = d_LH_VisitorReturns;
      nOffset += sizeof (int);

   // int LH_VisitorReturns_Prc
      (*(int*)(file+nOffset)) = d_LH_VisitorReturns_Prc;
      nOffset += sizeof (int);

   // int LH_Hosts
      (*(int*)(file+nOffset)) = d_LH_Hosts;
      nOffset += sizeof (int);

   // int LH_Shows
      (*(int*)(file+nOffset)) = d_LH_Shows;
      nOffset += sizeof (int);

   // int LH_Clicks
      (*(int*)(file+nOffset)) = d_LH_Clicks;
      nOffset += sizeof (int);

   // int LH_Hits
      (*(int*)(file+nOffset)) = d_LH_Hits;
      nOffset += sizeof (int);

   // int LH_AveSessionTime
      (*(int*)(file+nOffset)) = d_LH_AveSessionTime;
      nOffset += sizeof (int);

   // int LH_AveReloadTime
      (*(int*)(file+nOffset)) = d_LH_AveReloadTime;
      nOffset += sizeof (int);

   // int LH_AveReloadNum
      (*(int*)(file+nOffset)) = d_LH_AveReloadNum;
      nOffset += sizeof (int);

   // bool TagBool1
      (*(bool*)(file+nOffset)) = d_TagBool1;
      nOffset += sizeof (bool);

   // bool TagBool2
      (*(bool*)(file+nOffset)) = d_TagBool2;
      nOffset += sizeof (bool);

   // identifier TagID1
      (*(identifier*)(file+nOffset)) = d_TagID1;
      nOffset += sizeof (identifier);

   // identifier TagID2
      (*(identifier*)(file+nOffset)) = d_TagID2;
      nOffset += sizeof (identifier);

   // int TagInt1
      (*(int*)(file+nOffset)) = d_TagInt1;
      nOffset += sizeof (int);

   // int TagInt2
      (*(int*)(file+nOffset)) = d_TagInt2;
      nOffset += sizeof (int);

   // float TagFloat1
      (*(float*)(file+nOffset)) = d_TagFloat1;
      nOffset += sizeof (float);

   // float TagFloat2
      (*(float*)(file+nOffset)) = d_TagFloat2;
      nOffset += sizeof (float);

   // string TagString1
      size_t n_TagString1 = d_TagString1.length()+1;
      (*(size_t*)(file+nOffset)) = n_TagString1;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_TagString1.c_str(), n_TagString1);
      ENCODE_STRING (n_TagString1, (char*)(file+nOffset));
      nOffset += n_TagString1;

   // string TagString2
      size_t n_TagString2 = d_TagString2.length()+1;
      (*(size_t*)(file+nOffset)) = n_TagString2;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_TagString2.c_str(), n_TagString2);
      ENCODE_STRING (n_TagString2, (char*)(file+nOffset));
      nOffset += n_TagString2;

   // identifier ReservedID1 []
      (*(size_t*)(file+nOffset)) = d_ReservedID1.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID1);

   // identifier ReservedID2 []
      (*(size_t*)(file+nOffset)) = d_ReservedID2.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID2);

   // int ReservedInt1 []
      (*(size_t*)(file+nOffset)) = d_ReservedInt1.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt1);

   // int ReservedInt2 []
      (*(size_t*)(file+nOffset)) = d_ReservedInt2.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt2);

   // string ReservedString1 []
      (*(size_t*)(file+nOffset)) = d_ReservedString1.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         size_t n_ReservedString1 = d_ReservedString1[iReservedString1].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString1;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString1[iReservedString1].c_str(), n_ReservedString1);
         ENCODE_STRING (n_ReservedString1, (char*)(file+nOffset));
         nOffset += n_ReservedString1;
      }

   // string ReservedString2 []
      (*(size_t*)(file+nOffset)) = d_ReservedString2.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         size_t n_ReservedString2 = d_ReservedString2[iReservedString2].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString2;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString2[iReservedString2].c_str(), n_ReservedString2);
         ENCODE_STRING (n_ReservedString2, (char*)(file+nOffset));
         nOffset += n_ReservedString2;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_VBN::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_VBN], objID);
      dbg += SSS;

   // string Password
      SSS.Format ("Password = '%s'\n", d_Password.c_str());
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // bool IsModerated
      SSS.Format ("IsModerated = %s\n", d_IsModerated?"true":"false");
      dbg += SSS;

   // identifier DefaultLanguage
      SSS.Format ("DefaultLanguage = %d\n", d_DefaultLanguage);
      dbg += SSS;

   // int DefaultTZOffset
      SSS.Format ("DefaultTZOffset = %d\n", d_DefaultTZOffset);
      dbg += SSS;

   // identifier Owner
      SSS.Format ("Owner = %d\n", d_Owner);
      dbg += SSS;

   // byte ConceptMask []
      SSS.Format ("ConceptMask[].size = %d:\n", d_ConceptMask.GetSize());
      dbg += SSS;
      for (int iConceptMask=0; iConceptMask<d_ConceptMask.GetSize(); iConceptMask++)
      {
         SSS.Format ("   ConceptMask[%d] = %d\n", iConceptMask, d_ConceptMask[iConceptMask]);
         dbg += SSS;
      }

   // identifier AdminEventList
      SSS.Format ("AdminEventList = %d\n", d_AdminEventList);
      dbg += SSS;

   // byte No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // int OnlineVisitors
      SSS.Format ("OnlineVisitors = %d\n", d_OnlineVisitors);
      dbg += SSS;

   // identifier ActiveViewersID []
      SSS.Format ("ActiveViewersID[].size = %d:\n", d_ActiveViewersID.GetSize());
      dbg += SSS;
      for (int iActiveViewersID=0; iActiveViewersID<d_ActiveViewersID.GetSize(); iActiveViewersID++)
      {
         SSS.Format ("   ActiveViewersID[%d] = %d\n", iActiveViewersID, d_ActiveViewersID[iActiveViewersID]);
         dbg += SSS;
      }

   // int ActiveViewersHosts []
      SSS.Format ("ActiveViewersHosts[].size = %d:\n", d_ActiveViewersHosts.GetSize());
      dbg += SSS;
      for (int iActiveViewersHosts=0; iActiveViewersHosts<d_ActiveViewersHosts.GetSize(); iActiveViewersHosts++)
      {
         SSS.Format ("   ActiveViewersHosts[%d] = %d\n", iActiveViewersHosts, d_ActiveViewersHosts[iActiveViewersHosts]);
         dbg += SSS;
      }

   // identifier Hits
      SSS.Format ("Hits = %d\n", d_Hits);
      dbg += SSS;

   // identifier Hosts
      SSS.Format ("Hosts = %d\n", d_Hosts);
      dbg += SSS;

   // identifier Visitors
      SSS.Format ("Visitors = %d\n", d_Visitors);
      dbg += SSS;

   // identifier Shows
      SSS.Format ("Shows = %d\n", d_Shows);
      dbg += SSS;

   // identifier Clicks
      SSS.Format ("Clicks = %d\n", d_Clicks);
      dbg += SSS;

   // identifier SessionTime
      SSS.Format ("SessionTime = %d\n", d_SessionTime);
      dbg += SSS;

   // identifier SessionNum
      SSS.Format ("SessionNum = %d\n", d_SessionNum);
      dbg += SSS;

   // int Total_Hosts
      SSS.Format ("Total_Hosts = %d\n", d_Total_Hosts);
      dbg += SSS;

   // int Total_Shows
      SSS.Format ("Total_Shows = %d\n", d_Total_Shows);
      dbg += SSS;

   // int Total_Clicks
      SSS.Format ("Total_Clicks = %d\n", d_Total_Clicks);
      dbg += SSS;

   // int Total_Hits
      SSS.Format ("Total_Hits = %d\n", d_Total_Hits);
      dbg += SSS;

   // int Total_Visitors
      SSS.Format ("Total_Visitors = %d\n", d_Total_Visitors);
      dbg += SSS;

   // int Total_VisitorReturns
      SSS.Format ("Total_VisitorReturns = %d\n", d_Total_VisitorReturns);
      dbg += SSS;

   // int Total_AveSessionTime
      SSS.Format ("Total_AveSessionTime = %d\n", d_Total_AveSessionTime);
      dbg += SSS;

   // int Total_AveReloadTime
      SSS.Format ("Total_AveReloadTime = %d\n", d_Total_AveReloadTime);
      dbg += SSS;

   // int Total_AveReloadNum
      SSS.Format ("Total_AveReloadNum = %d\n", d_Total_AveReloadNum);
      dbg += SSS;

   // int LM_Visitors
      SSS.Format ("LM_Visitors = %d\n", d_LM_Visitors);
      dbg += SSS;

   // int LM_VisitorReturns
      SSS.Format ("LM_VisitorReturns = %d\n", d_LM_VisitorReturns);
      dbg += SSS;

   // int LM_VisitorReturns_Prc
      SSS.Format ("LM_VisitorReturns_Prc = %d\n", d_LM_VisitorReturns_Prc);
      dbg += SSS;

   // int LM_Hosts
      SSS.Format ("LM_Hosts = %d\n", d_LM_Hosts);
      dbg += SSS;

   // int LM_Shows
      SSS.Format ("LM_Shows = %d\n", d_LM_Shows);
      dbg += SSS;

   // int LM_Clicks
      SSS.Format ("LM_Clicks = %d\n", d_LM_Clicks);
      dbg += SSS;

   // int LM_Hits
      SSS.Format ("LM_Hits = %d\n", d_LM_Hits);
      dbg += SSS;

   // int LM_AveSessionTime
      SSS.Format ("LM_AveSessionTime = %d\n", d_LM_AveSessionTime);
      dbg += SSS;

   // int LM_AveReloadTime
      SSS.Format ("LM_AveReloadTime = %d\n", d_LM_AveReloadTime);
      dbg += SSS;

   // int LM_AveReloadNum
      SSS.Format ("LM_AveReloadNum = %d\n", d_LM_AveReloadNum);
      dbg += SSS;

   // int LW_Visitors
      SSS.Format ("LW_Visitors = %d\n", d_LW_Visitors);
      dbg += SSS;

   // int LW_VisitorReturns
      SSS.Format ("LW_VisitorReturns = %d\n", d_LW_VisitorReturns);
      dbg += SSS;

   // int LW_VisitorReturns_Prc
      SSS.Format ("LW_VisitorReturns_Prc = %d\n", d_LW_VisitorReturns_Prc);
      dbg += SSS;

   // int LW_Hosts
      SSS.Format ("LW_Hosts = %d\n", d_LW_Hosts);
      dbg += SSS;

   // int LW_Shows
      SSS.Format ("LW_Shows = %d\n", d_LW_Shows);
      dbg += SSS;

   // int LW_Clicks
      SSS.Format ("LW_Clicks = %d\n", d_LW_Clicks);
      dbg += SSS;

   // int LW_Hits
      SSS.Format ("LW_Hits = %d\n", d_LW_Hits);
      dbg += SSS;

   // int LW_AveSessionTime
      SSS.Format ("LW_AveSessionTime = %d\n", d_LW_AveSessionTime);
      dbg += SSS;

   // int LW_AveReloadTime
      SSS.Format ("LW_AveReloadTime = %d\n", d_LW_AveReloadTime);
      dbg += SSS;

   // int LW_AveReloadNum
      SSS.Format ("LW_AveReloadNum = %d\n", d_LW_AveReloadNum);
      dbg += SSS;

   // int LD_Visitors
      SSS.Format ("LD_Visitors = %d\n", d_LD_Visitors);
      dbg += SSS;

   // int LD_VisitorReturns
      SSS.Format ("LD_VisitorReturns = %d\n", d_LD_VisitorReturns);
      dbg += SSS;

   // int LD_VisitorReturns_Prc
      SSS.Format ("LD_VisitorReturns_Prc = %d\n", d_LD_VisitorReturns_Prc);
      dbg += SSS;

   // int LD_Hosts
      SSS.Format ("LD_Hosts = %d\n", d_LD_Hosts);
      dbg += SSS;

   // int LD_Shows
      SSS.Format ("LD_Shows = %d\n", d_LD_Shows);
      dbg += SSS;

   // int LD_Clicks
      SSS.Format ("LD_Clicks = %d\n", d_LD_Clicks);
      dbg += SSS;

   // int LD_Hits
      SSS.Format ("LD_Hits = %d\n", d_LD_Hits);
      dbg += SSS;

   // int LD_AveSessionTime
      SSS.Format ("LD_AveSessionTime = %d\n", d_LD_AveSessionTime);
      dbg += SSS;

   // int LD_AveReloadTime
      SSS.Format ("LD_AveReloadTime = %d\n", d_LD_AveReloadTime);
      dbg += SSS;

   // int LD_AveReloadNum
      SSS.Format ("LD_AveReloadNum = %d\n", d_LD_AveReloadNum);
      dbg += SSS;

   // int LH_Visitors
      SSS.Format ("LH_Visitors = %d\n", d_LH_Visitors);
      dbg += SSS;

   // int LH_VisitorReturns
      SSS.Format ("LH_VisitorReturns = %d\n", d_LH_VisitorReturns);
      dbg += SSS;

   // int LH_VisitorReturns_Prc
      SSS.Format ("LH_VisitorReturns_Prc = %d\n", d_LH_VisitorReturns_Prc);
      dbg += SSS;

   // int LH_Hosts
      SSS.Format ("LH_Hosts = %d\n", d_LH_Hosts);
      dbg += SSS;

   // int LH_Shows
      SSS.Format ("LH_Shows = %d\n", d_LH_Shows);
      dbg += SSS;

   // int LH_Clicks
      SSS.Format ("LH_Clicks = %d\n", d_LH_Clicks);
      dbg += SSS;

   // int LH_Hits
      SSS.Format ("LH_Hits = %d\n", d_LH_Hits);
      dbg += SSS;

   // int LH_AveSessionTime
      SSS.Format ("LH_AveSessionTime = %d\n", d_LH_AveSessionTime);
      dbg += SSS;

   // int LH_AveReloadTime
      SSS.Format ("LH_AveReloadTime = %d\n", d_LH_AveReloadTime);
      dbg += SSS;

   // int LH_AveReloadNum
      SSS.Format ("LH_AveReloadNum = %d\n", d_LH_AveReloadNum);
      dbg += SSS;

   // bool TagBool1
      SSS.Format ("TagBool1 = %s\n", d_TagBool1?"true":"false");
      dbg += SSS;

   // bool TagBool2
      SSS.Format ("TagBool2 = %s\n", d_TagBool2?"true":"false");
      dbg += SSS;

   // identifier TagID1
      SSS.Format ("TagID1 = %d\n", d_TagID1);
      dbg += SSS;

   // identifier TagID2
      SSS.Format ("TagID2 = %d\n", d_TagID2);
      dbg += SSS;

   // int TagInt1
      SSS.Format ("TagInt1 = %d\n", d_TagInt1);
      dbg += SSS;

   // int TagInt2
      SSS.Format ("TagInt2 = %d\n", d_TagInt2);
      dbg += SSS;

   // float TagFloat1
      SSS.Format ("TagFloat1 = %f\n", d_TagFloat1);
      dbg += SSS;

   // float TagFloat2
      SSS.Format ("TagFloat2 = %f\n", d_TagFloat2);
      dbg += SSS;

   // string TagString1
      SSS.Format ("TagString1 = '%s'\n", d_TagString1.c_str());
      dbg += SSS;

   // string TagString2
      SSS.Format ("TagString2 = '%s'\n", d_TagString2.c_str());
      dbg += SSS;

   // identifier ReservedID1 []
      SSS.Format ("ReservedID1[].size = %d:\n", d_ReservedID1.GetSize());
      dbg += SSS;
      for (int iReservedID1=0; iReservedID1<d_ReservedID1.GetSize(); iReservedID1++)
      {
         SSS.Format ("   ReservedID1[%d] = %d\n", iReservedID1, d_ReservedID1[iReservedID1]);
         dbg += SSS;
      }

   // identifier ReservedID2 []
      SSS.Format ("ReservedID2[].size = %d:\n", d_ReservedID2.GetSize());
      dbg += SSS;
      for (int iReservedID2=0; iReservedID2<d_ReservedID2.GetSize(); iReservedID2++)
      {
         SSS.Format ("   ReservedID2[%d] = %d\n", iReservedID2, d_ReservedID2[iReservedID2]);
         dbg += SSS;
      }

   // int ReservedInt1 []
      SSS.Format ("ReservedInt1[].size = %d:\n", d_ReservedInt1.GetSize());
      dbg += SSS;
      for (int iReservedInt1=0; iReservedInt1<d_ReservedInt1.GetSize(); iReservedInt1++)
      {
         SSS.Format ("   ReservedInt1[%d] = %d\n", iReservedInt1, d_ReservedInt1[iReservedInt1]);
         dbg += SSS;
      }

   // int ReservedInt2 []
      SSS.Format ("ReservedInt2[].size = %d:\n", d_ReservedInt2.GetSize());
      dbg += SSS;
      for (int iReservedInt2=0; iReservedInt2<d_ReservedInt2.GetSize(); iReservedInt2++)
      {
         SSS.Format ("   ReservedInt2[%d] = %d\n", iReservedInt2, d_ReservedInt2[iReservedInt2]);
         dbg += SSS;
      }

   // string ReservedString1 []
      SSS.Format ("ReservedString1[].size = %d:\n", d_ReservedString1.GetSize());
      dbg += SSS;
      for (int iReservedString1=0; iReservedString1<d_ReservedString1.GetSize(); iReservedString1++)
      {
         SSS.Format ("   ReservedString1[%d] = '%s'\n", iReservedString1, d_ReservedString1[iReservedString1].c_str());
         dbg += SSS;
      }

   // string ReservedString2 []
      SSS.Format ("ReservedString2[].size = %d:\n", d_ReservedString2.GetSize());
      dbg += SSS;
      for (int iReservedString2=0; iReservedString2<d_ReservedString2.GetSize(); iReservedString2++)
      {
         SSS.Format ("   ReservedString2[%d] = '%s'\n", iReservedString2, d_ReservedString2[iReservedString2].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Language::OD_Language (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Language;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_Name.Alloc (0);
      d_No = 1;
      d_CacheTime = 0;
   }

// Деструктор
  OD_Language::~OD_Language () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Language::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 2: ka += d_ShortName;      break;
         case 3: ka += d_No;             break;
         case 4: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Language::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Name []
      int arr_size_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Name.Alloc (arr_size_Name);
      for (int iName=0; iName<(int)arr_size_Name; iName++)
      {
         string tmp_Name;
         size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
         nOffset += sizeof(size_t);
         char * s_Name = new char [n_Name];
         memcpy (s_Name, (file+nOffset), n_Name);
         nOffset += n_Name;
         DECODE_STRING (n_Name, s_Name);
         tmp_Name = s_Name;
         delete [] s_Name;

         d_Name[iName] = tmp_Name;
      }

   // string ShortName
      size_t n_ShortName = (*(size_t*)(file+nOffset));  // n_ShortName = strlen (s_ShortName)+1;
      nOffset += sizeof(size_t);
      char * s_ShortName = new char [n_ShortName];
      memcpy (s_ShortName, (file+nOffset), n_ShortName);
      nOffset += n_ShortName;
      DECODE_STRING (n_ShortName, s_ShortName);
      d_ShortName = s_ShortName;
      delete [] s_ShortName;

   // int No
      d_No = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Language::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Name []
      n_size += sizeof (size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         n_size += sizeof (size_t);
         n_size += d_Name[iName].length()+1;
      }

   // string ShortName
      n_size += sizeof (size_t);
      n_size += d_ShortName.length()+1;

   // int No
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Language::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Name []
      (*(size_t*)(file+nOffset)) = d_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         size_t n_Name = d_Name[iName].length()+1;
         (*(size_t*)(file+nOffset)) = n_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Name[iName].c_str(), n_Name);
         ENCODE_STRING (n_Name, (char*)(file+nOffset));
         nOffset += n_Name;
      }

   // string ShortName
      size_t n_ShortName = d_ShortName.length()+1;
      (*(size_t*)(file+nOffset)) = n_ShortName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_ShortName.c_str(), n_ShortName);
      ENCODE_STRING (n_ShortName, (char*)(file+nOffset));
      nOffset += n_ShortName;

   // int No
      (*(int*)(file+nOffset)) = d_No;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Language::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Language], objID);
      dbg += SSS;

   // string Name []
      SSS.Format ("Name[].size = %d:\n", d_Name.GetSize());
      dbg += SSS;
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         SSS.Format ("   Name[%d] = '%s'\n", iName, d_Name[iName].c_str());
         dbg += SSS;
      }

   // string ShortName
      SSS.Format ("ShortName = '%s'\n", d_ShortName.c_str());
      dbg += SSS;

   // int No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Concept::OD_Concept (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Concept;


      m_CoIndexPtr = new OBD_pointer [4];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      if (!bFieldsInit) return;

      d_Name.Alloc (0);
      d_Description.Alloc (0);
      d_Parent = NA;
      d_Ancestor.Alloc (0);
      d_AncestorNo.Alloc (0);
      d_AncestorWeight.Alloc (0);
      d_AllAncestor.Alloc (0);
      d_AllAncestorNo.Alloc (0);
      d_Child.Alloc (0);
      d_ChildNo.Alloc (0);
      d_Descendant.Alloc (0);
      d_DescendantNo.Alloc (0);
      d_Level = -1;
      d_TypeNo = -1;
      d_VBN_ID.Alloc (0);
      d_VBN_SiteList.Alloc (0);
      d_VBN_SiteListSize.Alloc (0);
      d_ClickerConcept_Work.Alloc (0);
      d_ClickerConcept_Home.Alloc (0);
      d_ClickerConcept_Night.Alloc (0);
      d_Ads_SiteID.Alloc (0);
      d_Ads_ShowRate.Alloc (0);
      d_Ads_ClickRate.Alloc (0);
      d_Ads_ViewRate.Alloc (0);
      d_No = -1;
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_Concept::~OD_Concept () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Concept::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 3: ka += d_Parent;         break;
         case 13: ka += d_Level;          break;
         case 14: ka += d_ShortName;      break;
         case 15: ka += d_Type;           break;
         case 16: ka += d_TypeNo;         break;
         case 27: ka += d_No;             break;
         case 28: ka += d_TagID;          break;
         case 29: ka += d_TagInt;         break;
         case 30: ka += d_TagBool;        break;
         case 34: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Concept::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Name []
      int arr_size_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Name.Alloc (arr_size_Name);
      for (int iName=0; iName<(int)arr_size_Name; iName++)
      {
         string tmp_Name;
         size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
         nOffset += sizeof(size_t);
         char * s_Name = new char [n_Name];
         memcpy (s_Name, (file+nOffset), n_Name);
         nOffset += n_Name;
         DECODE_STRING (n_Name, s_Name);
         tmp_Name = s_Name;
         delete [] s_Name;

         d_Name[iName] = tmp_Name;
      }

   // string Description []
      int arr_size_Description = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Description.Alloc (arr_size_Description);
      for (int iDescription=0; iDescription<(int)arr_size_Description; iDescription++)
      {
         string tmp_Description;
         size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
         nOffset += sizeof(size_t);
         char * s_Description = new char [n_Description];
         memcpy (s_Description, (file+nOffset), n_Description);
         nOffset += n_Description;
         DECODE_STRING (n_Description, s_Description);
         tmp_Description = s_Description;
         delete [] s_Description;

         d_Description[iDescription] = tmp_Description;
      }

   // identifier Parent
      d_Parent = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Ancestor []
      int arr_size_Ancestor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Ancestor.Alloc (arr_size_Ancestor);
      OD_LOAD_SIMPLE_ARRAY (identifier,Ancestor);

   // int AncestorNo []
      int arr_size_AncestorNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_AncestorNo.Alloc (arr_size_AncestorNo);
      OD_LOAD_SIMPLE_ARRAY (int,AncestorNo);

   // int AncestorWeight []
      int arr_size_AncestorWeight = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_AncestorWeight.Alloc (arr_size_AncestorWeight);
      OD_LOAD_SIMPLE_ARRAY (int,AncestorWeight);

   // identifier AllAncestor []
      int arr_size_AllAncestor = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_AllAncestor.Alloc (arr_size_AllAncestor);
      OD_LOAD_SIMPLE_ARRAY (identifier,AllAncestor);

   // identifier AllAncestorNo []
      int arr_size_AllAncestorNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_AllAncestorNo.Alloc (arr_size_AllAncestorNo);
      OD_LOAD_SIMPLE_ARRAY (identifier,AllAncestorNo);

   // identifier Child []
      int arr_size_Child = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Child.Alloc (arr_size_Child);
      OD_LOAD_SIMPLE_ARRAY (identifier,Child);

   // int ChildNo []
      int arr_size_ChildNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ChildNo.Alloc (arr_size_ChildNo);
      OD_LOAD_SIMPLE_ARRAY (int,ChildNo);

   // identifier Descendant []
      int arr_size_Descendant = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Descendant.Alloc (arr_size_Descendant);
      OD_LOAD_SIMPLE_ARRAY (identifier,Descendant);

   // int DescendantNo []
      int arr_size_DescendantNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DescendantNo.Alloc (arr_size_DescendantNo);
      OD_LOAD_SIMPLE_ARRAY (int,DescendantNo);

   // int Level
      d_Level = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string ShortName
      size_t n_ShortName = (*(size_t*)(file+nOffset));  // n_ShortName = strlen (s_ShortName)+1;
      nOffset += sizeof(size_t);
      char * s_ShortName = new char [n_ShortName];
      memcpy (s_ShortName, (file+nOffset), n_ShortName);
      nOffset += n_ShortName;
      DECODE_STRING (n_ShortName, s_ShortName);
      d_ShortName = s_ShortName;
      delete [] s_ShortName;

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type];
      memcpy (s_Type, (file+nOffset), n_Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // int TypeNo
      d_TypeNo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier VBN_ID []
      int arr_size_VBN_ID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_ID.Alloc (arr_size_VBN_ID);
      OD_LOAD_SIMPLE_ARRAY (identifier,VBN_ID);

   // identifier VBN_SiteList []
      int arr_size_VBN_SiteList = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_SiteList.Alloc (arr_size_VBN_SiteList);
      OD_LOAD_SIMPLE_ARRAY (identifier,VBN_SiteList);

   // int VBN_SiteListSize []
      int arr_size_VBN_SiteListSize = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_SiteListSize.Alloc (arr_size_VBN_SiteListSize);
      OD_LOAD_SIMPLE_ARRAY (int,VBN_SiteListSize);

   // int ClickerConcept_Work []
      int arr_size_ClickerConcept_Work = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ClickerConcept_Work.Alloc (arr_size_ClickerConcept_Work);
      OD_LOAD_SIMPLE_ARRAY (int,ClickerConcept_Work);

   // int ClickerConcept_Home []
      int arr_size_ClickerConcept_Home = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ClickerConcept_Home.Alloc (arr_size_ClickerConcept_Home);
      OD_LOAD_SIMPLE_ARRAY (int,ClickerConcept_Home);

   // int ClickerConcept_Night []
      int arr_size_ClickerConcept_Night = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ClickerConcept_Night.Alloc (arr_size_ClickerConcept_Night);
      OD_LOAD_SIMPLE_ARRAY (int,ClickerConcept_Night);

   // identifier Ads_SiteID []
      int arr_size_Ads_SiteID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Ads_SiteID.Alloc (arr_size_Ads_SiteID);
      OD_LOAD_SIMPLE_ARRAY (identifier,Ads_SiteID);

   // int Ads_ShowRate []
      int arr_size_Ads_ShowRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Ads_ShowRate.Alloc (arr_size_Ads_ShowRate);
      OD_LOAD_SIMPLE_ARRAY (int,Ads_ShowRate);

   // int Ads_ClickRate []
      int arr_size_Ads_ClickRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Ads_ClickRate.Alloc (arr_size_Ads_ClickRate);
      OD_LOAD_SIMPLE_ARRAY (int,Ads_ClickRate);

   // int Ads_ViewRate []
      int arr_size_Ads_ViewRate = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Ads_ViewRate.Alloc (arr_size_Ads_ViewRate);
      OD_LOAD_SIMPLE_ARRAY (int,Ads_ViewRate);

   // int No
      d_No = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier TagID
      d_TagID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int TagInt
      d_TagInt = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // bool TagBool
      d_TagBool = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ReservedID []
      int arr_size_ReservedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedID.Alloc (arr_size_ReservedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      int arr_size_ReservedInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedInt.Alloc (arr_size_ReservedInt);
      OD_LOAD_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      int arr_size_ReservedString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ReservedString.Alloc (arr_size_ReservedString);
      for (int iReservedString=0; iReservedString<(int)arr_size_ReservedString; iReservedString++)
      {
         string tmp_ReservedString;
         size_t n_ReservedString = (*(size_t*)(file+nOffset));  // n_ReservedString = strlen (s_ReservedString)+1;
         nOffset += sizeof(size_t);
         char * s_ReservedString = new char [n_ReservedString];
         memcpy (s_ReservedString, (file+nOffset), n_ReservedString);
         nOffset += n_ReservedString;
         DECODE_STRING (n_ReservedString, s_ReservedString);
         tmp_ReservedString = s_ReservedString;
         delete [] s_ReservedString;

         d_ReservedString[iReservedString] = tmp_ReservedString;
      }

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Concept::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Name []
      n_size += sizeof (size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         n_size += sizeof (size_t);
         n_size += d_Name[iName].length()+1;
      }

   // string Description []
      n_size += sizeof (size_t);
      for (int iDescription=0; iDescription<d_Description.GetSize(); iDescription++)
      {
         n_size += sizeof (size_t);
         n_size += d_Description[iDescription].length()+1;
      }

   // identifier Parent
      n_size += sizeof (identifier);

   // identifier Ancestor []
      n_size += sizeof (size_t);
      n_size += d_Ancestor.GetSize() * sizeof(identifier);

   // int AncestorNo []
      n_size += sizeof (size_t);
      n_size += d_AncestorNo.GetSize() * sizeof(int);

   // int AncestorWeight []
      n_size += sizeof (size_t);
      n_size += d_AncestorWeight.GetSize() * sizeof(int);

   // identifier AllAncestor []
      n_size += sizeof (size_t);
      n_size += d_AllAncestor.GetSize() * sizeof(identifier);

   // identifier AllAncestorNo []
      n_size += sizeof (size_t);
      n_size += d_AllAncestorNo.GetSize() * sizeof(identifier);

   // identifier Child []
      n_size += sizeof (size_t);
      n_size += d_Child.GetSize() * sizeof(identifier);

   // int ChildNo []
      n_size += sizeof (size_t);
      n_size += d_ChildNo.GetSize() * sizeof(int);

   // identifier Descendant []
      n_size += sizeof (size_t);
      n_size += d_Descendant.GetSize() * sizeof(identifier);

   // int DescendantNo []
      n_size += sizeof (size_t);
      n_size += d_DescendantNo.GetSize() * sizeof(int);

   // int Level
      n_size += sizeof (int);

   // string ShortName
      n_size += sizeof (size_t);
      n_size += d_ShortName.length()+1;

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // int TypeNo
      n_size += sizeof (int);

   // identifier VBN_ID []
      n_size += sizeof (size_t);
      n_size += d_VBN_ID.GetSize() * sizeof(identifier);

   // identifier VBN_SiteList []
      n_size += sizeof (size_t);
      n_size += d_VBN_SiteList.GetSize() * sizeof(identifier);

   // int VBN_SiteListSize []
      n_size += sizeof (size_t);
      n_size += d_VBN_SiteListSize.GetSize() * sizeof(int);

   // int ClickerConcept_Work []
      n_size += sizeof (size_t);
      n_size += d_ClickerConcept_Work.GetSize() * sizeof(int);

   // int ClickerConcept_Home []
      n_size += sizeof (size_t);
      n_size += d_ClickerConcept_Home.GetSize() * sizeof(int);

   // int ClickerConcept_Night []
      n_size += sizeof (size_t);
      n_size += d_ClickerConcept_Night.GetSize() * sizeof(int);

   // identifier Ads_SiteID []
      n_size += sizeof (size_t);
      n_size += d_Ads_SiteID.GetSize() * sizeof(identifier);

   // int Ads_ShowRate []
      n_size += sizeof (size_t);
      n_size += d_Ads_ShowRate.GetSize() * sizeof(int);

   // int Ads_ClickRate []
      n_size += sizeof (size_t);
      n_size += d_Ads_ClickRate.GetSize() * sizeof(int);

   // int Ads_ViewRate []
      n_size += sizeof (size_t);
      n_size += d_Ads_ViewRate.GetSize() * sizeof(int);

   // int No
      n_size += sizeof (int);

   // identifier TagID
      n_size += sizeof (identifier);

   // int TagInt
      n_size += sizeof (int);

   // bool TagBool
      n_size += sizeof (bool);

   // identifier ReservedID []
      n_size += sizeof (size_t);
      n_size += d_ReservedID.GetSize() * sizeof(identifier);

   // int ReservedInt []
      n_size += sizeof (size_t);
      n_size += d_ReservedInt.GetSize() * sizeof(int);

   // string ReservedString []
      n_size += sizeof (size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         n_size += sizeof (size_t);
         n_size += d_ReservedString[iReservedString].length()+1;
      }

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Concept::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Name []
      (*(size_t*)(file+nOffset)) = d_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         size_t n_Name = d_Name[iName].length()+1;
         (*(size_t*)(file+nOffset)) = n_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Name[iName].c_str(), n_Name);
         ENCODE_STRING (n_Name, (char*)(file+nOffset));
         nOffset += n_Name;
      }

   // string Description []
      (*(size_t*)(file+nOffset)) = d_Description.GetSize();
      nOffset += sizeof(size_t);
      for (int iDescription=0; iDescription<d_Description.GetSize(); iDescription++)
      {
         size_t n_Description = d_Description[iDescription].length()+1;
         (*(size_t*)(file+nOffset)) = n_Description;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Description[iDescription].c_str(), n_Description);
         ENCODE_STRING (n_Description, (char*)(file+nOffset));
         nOffset += n_Description;
      }

   // identifier Parent
      (*(identifier*)(file+nOffset)) = d_Parent;
      nOffset += sizeof (identifier);

   // identifier Ancestor []
      (*(size_t*)(file+nOffset)) = d_Ancestor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Ancestor);

   // int AncestorNo []
      (*(size_t*)(file+nOffset)) = d_AncestorNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,AncestorNo);

   // int AncestorWeight []
      (*(size_t*)(file+nOffset)) = d_AncestorWeight.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,AncestorWeight);

   // identifier AllAncestor []
      (*(size_t*)(file+nOffset)) = d_AllAncestor.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,AllAncestor);

   // identifier AllAncestorNo []
      (*(size_t*)(file+nOffset)) = d_AllAncestorNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,AllAncestorNo);

   // identifier Child []
      (*(size_t*)(file+nOffset)) = d_Child.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Child);

   // int ChildNo []
      (*(size_t*)(file+nOffset)) = d_ChildNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ChildNo);

   // identifier Descendant []
      (*(size_t*)(file+nOffset)) = d_Descendant.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Descendant);

   // int DescendantNo []
      (*(size_t*)(file+nOffset)) = d_DescendantNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,DescendantNo);

   // int Level
      (*(int*)(file+nOffset)) = d_Level;
      nOffset += sizeof (int);

   // string ShortName
      size_t n_ShortName = d_ShortName.length()+1;
      (*(size_t*)(file+nOffset)) = n_ShortName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_ShortName.c_str(), n_ShortName);
      ENCODE_STRING (n_ShortName, (char*)(file+nOffset));
      nOffset += n_ShortName;

   // string Type
      size_t n_Type = d_Type.length()+1;
      (*(size_t*)(file+nOffset)) = n_Type;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Type.c_str(), n_Type);
      ENCODE_STRING (n_Type, (char*)(file+nOffset));
      nOffset += n_Type;

   // int TypeNo
      (*(int*)(file+nOffset)) = d_TypeNo;
      nOffset += sizeof (int);

   // identifier VBN_ID []
      (*(size_t*)(file+nOffset)) = d_VBN_ID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,VBN_ID);

   // identifier VBN_SiteList []
      (*(size_t*)(file+nOffset)) = d_VBN_SiteList.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,VBN_SiteList);

   // int VBN_SiteListSize []
      (*(size_t*)(file+nOffset)) = d_VBN_SiteListSize.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,VBN_SiteListSize);

   // int ClickerConcept_Work []
      (*(size_t*)(file+nOffset)) = d_ClickerConcept_Work.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ClickerConcept_Work);

   // int ClickerConcept_Home []
      (*(size_t*)(file+nOffset)) = d_ClickerConcept_Home.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ClickerConcept_Home);

   // int ClickerConcept_Night []
      (*(size_t*)(file+nOffset)) = d_ClickerConcept_Night.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ClickerConcept_Night);

   // identifier Ads_SiteID []
      (*(size_t*)(file+nOffset)) = d_Ads_SiteID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Ads_SiteID);

   // int Ads_ShowRate []
      (*(size_t*)(file+nOffset)) = d_Ads_ShowRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Ads_ShowRate);

   // int Ads_ClickRate []
      (*(size_t*)(file+nOffset)) = d_Ads_ClickRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Ads_ClickRate);

   // int Ads_ViewRate []
      (*(size_t*)(file+nOffset)) = d_Ads_ViewRate.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Ads_ViewRate);

   // int No
      (*(int*)(file+nOffset)) = d_No;
      nOffset += sizeof (int);

   // identifier TagID
      (*(identifier*)(file+nOffset)) = d_TagID;
      nOffset += sizeof (identifier);

   // int TagInt
      (*(int*)(file+nOffset)) = d_TagInt;
      nOffset += sizeof (int);

   // bool TagBool
      (*(bool*)(file+nOffset)) = d_TagBool;
      nOffset += sizeof (bool);

   // identifier ReservedID []
      (*(size_t*)(file+nOffset)) = d_ReservedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ReservedID);

   // int ReservedInt []
      (*(size_t*)(file+nOffset)) = d_ReservedInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ReservedInt);

   // string ReservedString []
      (*(size_t*)(file+nOffset)) = d_ReservedString.GetSize();
      nOffset += sizeof(size_t);
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         size_t n_ReservedString = d_ReservedString[iReservedString].length()+1;
         (*(size_t*)(file+nOffset)) = n_ReservedString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_ReservedString[iReservedString].c_str(), n_ReservedString);
         ENCODE_STRING (n_ReservedString, (char*)(file+nOffset));
         nOffset += n_ReservedString;
      }

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Concept::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Concept], objID);
      dbg += SSS;

   // string Name []
      SSS.Format ("Name[].size = %d:\n", d_Name.GetSize());
      dbg += SSS;
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         SSS.Format ("   Name[%d] = '%s'\n", iName, d_Name[iName].c_str());
         dbg += SSS;
      }

   // string Description []
      SSS.Format ("Description[].size = %d:\n", d_Description.GetSize());
      dbg += SSS;
      for (int iDescription=0; iDescription<d_Description.GetSize(); iDescription++)
      {
         SSS.Format ("   Description[%d] = '%s'\n", iDescription, d_Description[iDescription].c_str());
         dbg += SSS;
      }

   // identifier Parent
      SSS.Format ("Parent = %d\n", d_Parent);
      dbg += SSS;

   // identifier Ancestor []
      SSS.Format ("Ancestor[].size = %d:\n", d_Ancestor.GetSize());
      dbg += SSS;
      for (int iAncestor=0; iAncestor<d_Ancestor.GetSize(); iAncestor++)
      {
         SSS.Format ("   Ancestor[%d] = %d\n", iAncestor, d_Ancestor[iAncestor]);
         dbg += SSS;
      }

   // int AncestorNo []
      SSS.Format ("AncestorNo[].size = %d:\n", d_AncestorNo.GetSize());
      dbg += SSS;
      for (int iAncestorNo=0; iAncestorNo<d_AncestorNo.GetSize(); iAncestorNo++)
      {
         SSS.Format ("   AncestorNo[%d] = %d\n", iAncestorNo, d_AncestorNo[iAncestorNo]);
         dbg += SSS;
      }

   // int AncestorWeight []
      SSS.Format ("AncestorWeight[].size = %d:\n", d_AncestorWeight.GetSize());
      dbg += SSS;
      for (int iAncestorWeight=0; iAncestorWeight<d_AncestorWeight.GetSize(); iAncestorWeight++)
      {
         SSS.Format ("   AncestorWeight[%d] = %d\n", iAncestorWeight, d_AncestorWeight[iAncestorWeight]);
         dbg += SSS;
      }

   // identifier AllAncestor []
      SSS.Format ("AllAncestor[].size = %d:\n", d_AllAncestor.GetSize());
      dbg += SSS;
      for (int iAllAncestor=0; iAllAncestor<d_AllAncestor.GetSize(); iAllAncestor++)
      {
         SSS.Format ("   AllAncestor[%d] = %d\n", iAllAncestor, d_AllAncestor[iAllAncestor]);
         dbg += SSS;
      }

   // identifier AllAncestorNo []
      SSS.Format ("AllAncestorNo[].size = %d:\n", d_AllAncestorNo.GetSize());
      dbg += SSS;
      for (int iAllAncestorNo=0; iAllAncestorNo<d_AllAncestorNo.GetSize(); iAllAncestorNo++)
      {
         SSS.Format ("   AllAncestorNo[%d] = %d\n", iAllAncestorNo, d_AllAncestorNo[iAllAncestorNo]);
         dbg += SSS;
      }

   // identifier Child []
      SSS.Format ("Child[].size = %d:\n", d_Child.GetSize());
      dbg += SSS;
      for (int iChild=0; iChild<d_Child.GetSize(); iChild++)
      {
         SSS.Format ("   Child[%d] = %d\n", iChild, d_Child[iChild]);
         dbg += SSS;
      }

   // int ChildNo []
      SSS.Format ("ChildNo[].size = %d:\n", d_ChildNo.GetSize());
      dbg += SSS;
      for (int iChildNo=0; iChildNo<d_ChildNo.GetSize(); iChildNo++)
      {
         SSS.Format ("   ChildNo[%d] = %d\n", iChildNo, d_ChildNo[iChildNo]);
         dbg += SSS;
      }

   // identifier Descendant []
      SSS.Format ("Descendant[].size = %d:\n", d_Descendant.GetSize());
      dbg += SSS;
      for (int iDescendant=0; iDescendant<d_Descendant.GetSize(); iDescendant++)
      {
         SSS.Format ("   Descendant[%d] = %d\n", iDescendant, d_Descendant[iDescendant]);
         dbg += SSS;
      }

   // int DescendantNo []
      SSS.Format ("DescendantNo[].size = %d:\n", d_DescendantNo.GetSize());
      dbg += SSS;
      for (int iDescendantNo=0; iDescendantNo<d_DescendantNo.GetSize(); iDescendantNo++)
      {
         SSS.Format ("   DescendantNo[%d] = %d\n", iDescendantNo, d_DescendantNo[iDescendantNo]);
         dbg += SSS;
      }

   // int Level
      SSS.Format ("Level = %d\n", d_Level);
      dbg += SSS;

   // string ShortName
      SSS.Format ("ShortName = '%s'\n", d_ShortName.c_str());
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // int TypeNo
      SSS.Format ("TypeNo = %d\n", d_TypeNo);
      dbg += SSS;

   // identifier VBN_ID []
      SSS.Format ("VBN_ID[].size = %d:\n", d_VBN_ID.GetSize());
      dbg += SSS;
      for (int iVBN_ID=0; iVBN_ID<d_VBN_ID.GetSize(); iVBN_ID++)
      {
         SSS.Format ("   VBN_ID[%d] = %d\n", iVBN_ID, d_VBN_ID[iVBN_ID]);
         dbg += SSS;
      }

   // identifier VBN_SiteList []
      SSS.Format ("VBN_SiteList[].size = %d:\n", d_VBN_SiteList.GetSize());
      dbg += SSS;
      for (int iVBN_SiteList=0; iVBN_SiteList<d_VBN_SiteList.GetSize(); iVBN_SiteList++)
      {
         SSS.Format ("   VBN_SiteList[%d] = %d\n", iVBN_SiteList, d_VBN_SiteList[iVBN_SiteList]);
         dbg += SSS;
      }

   // int VBN_SiteListSize []
      SSS.Format ("VBN_SiteListSize[].size = %d:\n", d_VBN_SiteListSize.GetSize());
      dbg += SSS;
      for (int iVBN_SiteListSize=0; iVBN_SiteListSize<d_VBN_SiteListSize.GetSize(); iVBN_SiteListSize++)
      {
         SSS.Format ("   VBN_SiteListSize[%d] = %d\n", iVBN_SiteListSize, d_VBN_SiteListSize[iVBN_SiteListSize]);
         dbg += SSS;
      }

   // int ClickerConcept_Work []
      SSS.Format ("ClickerConcept_Work[].size = %d:\n", d_ClickerConcept_Work.GetSize());
      dbg += SSS;
      for (int iClickerConcept_Work=0; iClickerConcept_Work<d_ClickerConcept_Work.GetSize(); iClickerConcept_Work++)
      {
         SSS.Format ("   ClickerConcept_Work[%d] = %d\n", iClickerConcept_Work, d_ClickerConcept_Work[iClickerConcept_Work]);
         dbg += SSS;
      }

   // int ClickerConcept_Home []
      SSS.Format ("ClickerConcept_Home[].size = %d:\n", d_ClickerConcept_Home.GetSize());
      dbg += SSS;
      for (int iClickerConcept_Home=0; iClickerConcept_Home<d_ClickerConcept_Home.GetSize(); iClickerConcept_Home++)
      {
         SSS.Format ("   ClickerConcept_Home[%d] = %d\n", iClickerConcept_Home, d_ClickerConcept_Home[iClickerConcept_Home]);
         dbg += SSS;
      }

   // int ClickerConcept_Night []
      SSS.Format ("ClickerConcept_Night[].size = %d:\n", d_ClickerConcept_Night.GetSize());
      dbg += SSS;
      for (int iClickerConcept_Night=0; iClickerConcept_Night<d_ClickerConcept_Night.GetSize(); iClickerConcept_Night++)
      {
         SSS.Format ("   ClickerConcept_Night[%d] = %d\n", iClickerConcept_Night, d_ClickerConcept_Night[iClickerConcept_Night]);
         dbg += SSS;
      }

   // identifier Ads_SiteID []
      SSS.Format ("Ads_SiteID[].size = %d:\n", d_Ads_SiteID.GetSize());
      dbg += SSS;
      for (int iAds_SiteID=0; iAds_SiteID<d_Ads_SiteID.GetSize(); iAds_SiteID++)
      {
         SSS.Format ("   Ads_SiteID[%d] = %d\n", iAds_SiteID, d_Ads_SiteID[iAds_SiteID]);
         dbg += SSS;
      }

   // int Ads_ShowRate []
      SSS.Format ("Ads_ShowRate[].size = %d:\n", d_Ads_ShowRate.GetSize());
      dbg += SSS;
      for (int iAds_ShowRate=0; iAds_ShowRate<d_Ads_ShowRate.GetSize(); iAds_ShowRate++)
      {
         SSS.Format ("   Ads_ShowRate[%d] = %d\n", iAds_ShowRate, d_Ads_ShowRate[iAds_ShowRate]);
         dbg += SSS;
      }

   // int Ads_ClickRate []
      SSS.Format ("Ads_ClickRate[].size = %d:\n", d_Ads_ClickRate.GetSize());
      dbg += SSS;
      for (int iAds_ClickRate=0; iAds_ClickRate<d_Ads_ClickRate.GetSize(); iAds_ClickRate++)
      {
         SSS.Format ("   Ads_ClickRate[%d] = %d\n", iAds_ClickRate, d_Ads_ClickRate[iAds_ClickRate]);
         dbg += SSS;
      }

   // int Ads_ViewRate []
      SSS.Format ("Ads_ViewRate[].size = %d:\n", d_Ads_ViewRate.GetSize());
      dbg += SSS;
      for (int iAds_ViewRate=0; iAds_ViewRate<d_Ads_ViewRate.GetSize(); iAds_ViewRate++)
      {
         SSS.Format ("   Ads_ViewRate[%d] = %d\n", iAds_ViewRate, d_Ads_ViewRate[iAds_ViewRate]);
         dbg += SSS;
      }

   // int No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // identifier TagID
      SSS.Format ("TagID = %d\n", d_TagID);
      dbg += SSS;

   // int TagInt
      SSS.Format ("TagInt = %d\n", d_TagInt);
      dbg += SSS;

   // bool TagBool
      SSS.Format ("TagBool = %s\n", d_TagBool?"true":"false");
      dbg += SSS;

   // identifier ReservedID []
      SSS.Format ("ReservedID[].size = %d:\n", d_ReservedID.GetSize());
      dbg += SSS;
      for (int iReservedID=0; iReservedID<d_ReservedID.GetSize(); iReservedID++)
      {
         SSS.Format ("   ReservedID[%d] = %d\n", iReservedID, d_ReservedID[iReservedID]);
         dbg += SSS;
      }

   // int ReservedInt []
      SSS.Format ("ReservedInt[].size = %d:\n", d_ReservedInt.GetSize());
      dbg += SSS;
      for (int iReservedInt=0; iReservedInt<d_ReservedInt.GetSize(); iReservedInt++)
      {
         SSS.Format ("   ReservedInt[%d] = %d\n", iReservedInt, d_ReservedInt[iReservedInt]);
         dbg += SSS;
      }

   // string ReservedString []
      SSS.Format ("ReservedString[].size = %d:\n", d_ReservedString.GetSize());
      dbg += SSS;
      for (int iReservedString=0; iReservedString<d_ReservedString.GetSize(); iReservedString++)
      {
         SSS.Format ("   ReservedString[%d] = '%s'\n", iReservedString, d_ReservedString[iReservedString].c_str());
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_SiteList::OD_SiteList (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_SiteList;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Site.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_SiteList::~OD_SiteList () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_SiteList::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 2: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_SiteList::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier Site []
      int arr_size_Site = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Site.Alloc (arr_size_Site);
      OD_LOAD_SIMPLE_ARRAY (identifier,Site);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_SiteList::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier Site []
      n_size += sizeof (size_t);
      n_size += d_Site.GetSize() * sizeof(identifier);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_SiteList::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier Site []
      (*(size_t*)(file+nOffset)) = d_Site.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Site);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_SiteList::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_SiteList], objID);
      dbg += SSS;

   // identifier Site []
      SSS.Format ("Site[].size = %d:\n", d_Site.GetSize());
      dbg += SSS;
      for (int iSite=0; iSite<d_Site.GetSize(); iSite++)
      {
         SSS.Format ("   Site[%d] = %d\n", iSite, d_Site[iSite]);
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Keyword::OD_Keyword (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Keyword;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_VBN_ID.Alloc (0);
      d_VBN_SiteList.Alloc (0);
      d_VBN_SiteListSize.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_Keyword::~OD_Keyword () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Keyword::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Word;           break;
         case 5: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Keyword::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Word
      size_t n_Word = (*(size_t*)(file+nOffset));  // n_Word = strlen (s_Word)+1;
      nOffset += sizeof(size_t);
      char * s_Word = new char [n_Word];
      memcpy (s_Word, (file+nOffset), n_Word);
      nOffset += n_Word;
      DECODE_STRING (n_Word, s_Word);
      d_Word = s_Word;
      delete [] s_Word;

   // identifier VBN_ID []
      int arr_size_VBN_ID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_ID.Alloc (arr_size_VBN_ID);
      OD_LOAD_SIMPLE_ARRAY (identifier,VBN_ID);

   // identifier VBN_SiteList []
      int arr_size_VBN_SiteList = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_SiteList.Alloc (arr_size_VBN_SiteList);
      OD_LOAD_SIMPLE_ARRAY (identifier,VBN_SiteList);

   // int VBN_SiteListSize []
      int arr_size_VBN_SiteListSize = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_VBN_SiteListSize.Alloc (arr_size_VBN_SiteListSize);
      OD_LOAD_SIMPLE_ARRAY (int,VBN_SiteListSize);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Keyword::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Word
      n_size += sizeof (size_t);
      n_size += d_Word.length()+1;

   // identifier VBN_ID []
      n_size += sizeof (size_t);
      n_size += d_VBN_ID.GetSize() * sizeof(identifier);

   // identifier VBN_SiteList []
      n_size += sizeof (size_t);
      n_size += d_VBN_SiteList.GetSize() * sizeof(identifier);

   // int VBN_SiteListSize []
      n_size += sizeof (size_t);
      n_size += d_VBN_SiteListSize.GetSize() * sizeof(int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Keyword::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Word
      size_t n_Word = d_Word.length()+1;
      (*(size_t*)(file+nOffset)) = n_Word;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Word.c_str(), n_Word);
      ENCODE_STRING (n_Word, (char*)(file+nOffset));
      nOffset += n_Word;

   // identifier VBN_ID []
      (*(size_t*)(file+nOffset)) = d_VBN_ID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,VBN_ID);

   // identifier VBN_SiteList []
      (*(size_t*)(file+nOffset)) = d_VBN_SiteList.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,VBN_SiteList);

   // int VBN_SiteListSize []
      (*(size_t*)(file+nOffset)) = d_VBN_SiteListSize.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,VBN_SiteListSize);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Keyword::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Keyword], objID);
      dbg += SSS;

   // string Word
      SSS.Format ("Word = '%s'\n", d_Word.c_str());
      dbg += SSS;

   // identifier VBN_ID []
      SSS.Format ("VBN_ID[].size = %d:\n", d_VBN_ID.GetSize());
      dbg += SSS;
      for (int iVBN_ID=0; iVBN_ID<d_VBN_ID.GetSize(); iVBN_ID++)
      {
         SSS.Format ("   VBN_ID[%d] = %d\n", iVBN_ID, d_VBN_ID[iVBN_ID]);
         dbg += SSS;
      }

   // identifier VBN_SiteList []
      SSS.Format ("VBN_SiteList[].size = %d:\n", d_VBN_SiteList.GetSize());
      dbg += SSS;
      for (int iVBN_SiteList=0; iVBN_SiteList<d_VBN_SiteList.GetSize(); iVBN_SiteList++)
      {
         SSS.Format ("   VBN_SiteList[%d] = %d\n", iVBN_SiteList, d_VBN_SiteList[iVBN_SiteList]);
         dbg += SSS;
      }

   // int VBN_SiteListSize []
      SSS.Format ("VBN_SiteListSize[].size = %d:\n", d_VBN_SiteListSize.GetSize());
      dbg += SSS;
      for (int iVBN_SiteListSize=0; iVBN_SiteListSize<d_VBN_SiteListSize.GetSize(); iVBN_SiteListSize++)
      {
         SSS.Format ("   VBN_SiteListSize[%d] = %d\n", iVBN_SiteListSize, d_VBN_SiteListSize[iVBN_SiteListSize]);
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_ModeratorComment::OD_ModeratorComment (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_ModeratorComment;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_Name.Alloc (0);
      d_No = -1;
      d_CacheTime = 0;
   }

// Деструктор
  OD_ModeratorComment::~OD_ModeratorComment () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_ModeratorComment::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 2: ka += d_No;             break;
         case 3: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_ModeratorComment::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Name []
      int arr_size_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Name.Alloc (arr_size_Name);
      for (int iName=0; iName<(int)arr_size_Name; iName++)
      {
         string tmp_Name;
         size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
         nOffset += sizeof(size_t);
         char * s_Name = new char [n_Name];
         memcpy (s_Name, (file+nOffset), n_Name);
         nOffset += n_Name;
         DECODE_STRING (n_Name, s_Name);
         tmp_Name = s_Name;
         delete [] s_Name;

         d_Name[iName] = tmp_Name;
      }

   // int No
      d_No = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_ModeratorComment::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Name []
      n_size += sizeof (size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         n_size += sizeof (size_t);
         n_size += d_Name[iName].length()+1;
      }

   // int No
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_ModeratorComment::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Name []
      (*(size_t*)(file+nOffset)) = d_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         size_t n_Name = d_Name[iName].length()+1;
         (*(size_t*)(file+nOffset)) = n_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Name[iName].c_str(), n_Name);
         ENCODE_STRING (n_Name, (char*)(file+nOffset));
         nOffset += n_Name;
      }

   // int No
      (*(int*)(file+nOffset)) = d_No;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_ModeratorComment::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_ModeratorComment], objID);
      dbg += SSS;

   // string Name []
      SSS.Format ("Name[].size = %d:\n", d_Name.GetSize());
      dbg += SSS;
      for (int iName=0; iName<d_Name.GetSize(); iName++)
      {
         SSS.Format ("   Name[%d] = '%s'\n", iName, d_Name[iName].c_str());
         dbg += SSS;
      }

   // int No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_TimeStats::OD_TimeStats (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_TimeStats;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Total = 0;
      d_Year.Alloc (0);
      d_YearStats.Alloc (0);
      d_TwoLastDaysMinute.Alloc (0);
      d_TwoLastDaysMinute_year = 0;
      d_TwoLastDaysMinute_day_of_year = 0;
      d_LastAccessTime = 0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_TimeStats::~OD_TimeStats () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_TimeStats::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Total;                              break;
         case 5: ka += d_TwoLastDaysMinute_year;             break;
         case 6: ka += d_TwoLastDaysMinute_day_of_year;      break;
         case 7: ka += d_LastAccessTime;                     break;
         case 8: ka += d_CacheTime;                          break;
      }
   }


// Загрузка объекта с диска
   size_t OD_TimeStats::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int Total
      d_Total = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Year []
      int arr_size_Year = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Year.Alloc (arr_size_Year);
      OD_LOAD_SIMPLE_ARRAY (int,Year);

   // identifier YearStats []
      int arr_size_YearStats = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_YearStats.Alloc (arr_size_YearStats);
      OD_LOAD_SIMPLE_ARRAY (identifier,YearStats);

   // int TwoLastDaysMinute []
      int arr_size_TwoLastDaysMinute = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_TwoLastDaysMinute.Alloc (arr_size_TwoLastDaysMinute);
      OD_LOAD_SIMPLE_ARRAY (int,TwoLastDaysMinute);

   // int TwoLastDaysMinute_year
      d_TwoLastDaysMinute_year = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int TwoLastDaysMinute_day_of_year
      d_TwoLastDaysMinute_day_of_year = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LastAccessTime
      d_LastAccessTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_TimeStats::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int Total
      n_size += sizeof (int);

   // int Year []
      n_size += sizeof (size_t);
      n_size += d_Year.GetSize() * sizeof(int);

   // identifier YearStats []
      n_size += sizeof (size_t);
      n_size += d_YearStats.GetSize() * sizeof(identifier);

   // int TwoLastDaysMinute []
      n_size += sizeof (size_t);
      n_size += d_TwoLastDaysMinute.GetSize() * sizeof(int);

   // int TwoLastDaysMinute_year
      n_size += sizeof (int);

   // int TwoLastDaysMinute_day_of_year
      n_size += sizeof (int);

   // int LastAccessTime
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_TimeStats::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int Total
      (*(int*)(file+nOffset)) = d_Total;
      nOffset += sizeof (int);

   // int Year []
      (*(size_t*)(file+nOffset)) = d_Year.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Year);

   // identifier YearStats []
      (*(size_t*)(file+nOffset)) = d_YearStats.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,YearStats);

   // int TwoLastDaysMinute []
      (*(size_t*)(file+nOffset)) = d_TwoLastDaysMinute.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,TwoLastDaysMinute);

   // int TwoLastDaysMinute_year
      (*(int*)(file+nOffset)) = d_TwoLastDaysMinute_year;
      nOffset += sizeof (int);

   // int TwoLastDaysMinute_day_of_year
      (*(int*)(file+nOffset)) = d_TwoLastDaysMinute_day_of_year;
      nOffset += sizeof (int);

   // int LastAccessTime
      (*(int*)(file+nOffset)) = d_LastAccessTime;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_TimeStats::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_TimeStats], objID);
      dbg += SSS;

   // int Total
      SSS.Format ("Total = %d\n", d_Total);
      dbg += SSS;

   // int Year []
      SSS.Format ("Year[].size = %d:\n", d_Year.GetSize());
      dbg += SSS;
      for (int iYear=0; iYear<d_Year.GetSize(); iYear++)
      {
         SSS.Format ("   Year[%d] = %d\n", iYear, d_Year[iYear]);
         dbg += SSS;
      }

   // identifier YearStats []
      SSS.Format ("YearStats[].size = %d:\n", d_YearStats.GetSize());
      dbg += SSS;
      for (int iYearStats=0; iYearStats<d_YearStats.GetSize(); iYearStats++)
      {
         SSS.Format ("   YearStats[%d] = %d\n", iYearStats, d_YearStats[iYearStats]);
         dbg += SSS;
      }

   // int TwoLastDaysMinute []
      SSS.Format ("TwoLastDaysMinute[].size = %d:\n", d_TwoLastDaysMinute.GetSize());
      dbg += SSS;
      for (int iTwoLastDaysMinute=0; iTwoLastDaysMinute<d_TwoLastDaysMinute.GetSize(); iTwoLastDaysMinute++)
      {
         SSS.Format ("   TwoLastDaysMinute[%d] = %d\n", iTwoLastDaysMinute, d_TwoLastDaysMinute[iTwoLastDaysMinute]);
         dbg += SSS;
      }

   // int TwoLastDaysMinute_year
      SSS.Format ("TwoLastDaysMinute_year = %d\n", d_TwoLastDaysMinute_year);
      dbg += SSS;

   // int TwoLastDaysMinute_day_of_year
      SSS.Format ("TwoLastDaysMinute_day_of_year = %d\n", d_TwoLastDaysMinute_day_of_year);
      dbg += SSS;

   // int LastAccessTime
      SSS.Format ("LastAccessTime = %d\n", d_LastAccessTime);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_YearStats::OD_YearStats (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_YearStats;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_DayTotal.Alloc (0);
      d_DayStats.Alloc (0);
      d_LastAccessTime = 0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_YearStats::~OD_YearStats () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_YearStats::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 3: ka += d_LastAccessTime;      break;
         case 4: ka += d_CacheTime;           break;
      }
   }


// Загрузка объекта с диска
   size_t OD_YearStats::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int DayTotal []
      int arr_size_DayTotal = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DayTotal.Alloc (arr_size_DayTotal);
      OD_LOAD_SIMPLE_ARRAY (int,DayTotal);

   // identifier DayStats []
      int arr_size_DayStats = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_DayStats.Alloc (arr_size_DayStats);
      OD_LOAD_SIMPLE_ARRAY (identifier,DayStats);

   // int LastAccessTime
      d_LastAccessTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_YearStats::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int DayTotal []
      n_size += sizeof (size_t);
      n_size += d_DayTotal.GetSize() * sizeof(int);

   // identifier DayStats []
      n_size += sizeof (size_t);
      n_size += d_DayStats.GetSize() * sizeof(identifier);

   // int LastAccessTime
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_YearStats::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int DayTotal []
      (*(size_t*)(file+nOffset)) = d_DayTotal.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,DayTotal);

   // identifier DayStats []
      (*(size_t*)(file+nOffset)) = d_DayStats.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,DayStats);

   // int LastAccessTime
      (*(int*)(file+nOffset)) = d_LastAccessTime;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_YearStats::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_YearStats], objID);
      dbg += SSS;

   // int DayTotal []
      SSS.Format ("DayTotal[].size = %d:\n", d_DayTotal.GetSize());
      dbg += SSS;
      for (int iDayTotal=0; iDayTotal<d_DayTotal.GetSize(); iDayTotal++)
      {
         SSS.Format ("   DayTotal[%d] = %d\n", iDayTotal, d_DayTotal[iDayTotal]);
         dbg += SSS;
      }

   // identifier DayStats []
      SSS.Format ("DayStats[].size = %d:\n", d_DayStats.GetSize());
      dbg += SSS;
      for (int iDayStats=0; iDayStats<d_DayStats.GetSize(); iDayStats++)
      {
         SSS.Format ("   DayStats[%d] = %d\n", iDayStats, d_DayStats[iDayStats]);
         dbg += SSS;
      }

   // int LastAccessTime
      SSS.Format ("LastAccessTime = %d\n", d_LastAccessTime);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_DayStats::OD_DayStats (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_DayStats;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_HourTotal.Alloc (0);
      d_LastAccessTime = 0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_DayStats::~OD_DayStats () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_DayStats::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 2: ka += d_LastAccessTime;      break;
         case 3: ka += d_CacheTime;           break;
      }
   }


// Загрузка объекта с диска
   size_t OD_DayStats::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int HourTotal []
      int arr_size_HourTotal = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_HourTotal.Alloc (arr_size_HourTotal);
      OD_LOAD_SIMPLE_ARRAY (int,HourTotal);

   // int LastAccessTime
      d_LastAccessTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_DayStats::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int HourTotal []
      n_size += sizeof (size_t);
      n_size += d_HourTotal.GetSize() * sizeof(int);

   // int LastAccessTime
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_DayStats::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int HourTotal []
      (*(size_t*)(file+nOffset)) = d_HourTotal.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,HourTotal);

   // int LastAccessTime
      (*(int*)(file+nOffset)) = d_LastAccessTime;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_DayStats::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_DayStats], objID);
      dbg += SSS;

   // int HourTotal []
      SSS.Format ("HourTotal[].size = %d:\n", d_HourTotal.GetSize());
      dbg += SSS;
      for (int iHourTotal=0; iHourTotal<d_HourTotal.GetSize(); iHourTotal++)
      {
         SSS.Format ("   HourTotal[%d] = %d\n", iHourTotal, d_HourTotal[iHourTotal]);
         dbg += SSS;
      }

   // int LastAccessTime
      SSS.Format ("LastAccessTime = %d\n", d_LastAccessTime);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Referrer::OD_Referrer (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Referrer;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_CRC = NA;
      d_Count = 0;
      d_LastAccessTime = 0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_Referrer::~OD_Referrer () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Referrer::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_CRC;                 break;
         case 2: ka += d_Referrer;            break;
         case 3: ka += d_Count;               break;
         case 4: ka += d_LastAccessTime;      break;
         case 5: ka += d_CacheTime;           break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Referrer::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier CRC
      d_CRC = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Referrer
      size_t n_Referrer = (*(size_t*)(file+nOffset));  // n_Referrer = strlen (s_Referrer)+1;
      nOffset += sizeof(size_t);
      char * s_Referrer = new char [n_Referrer];
      memcpy (s_Referrer, (file+nOffset), n_Referrer);
      nOffset += n_Referrer;
      DECODE_STRING (n_Referrer, s_Referrer);
      d_Referrer = s_Referrer;
      delete [] s_Referrer;

   // int Count
      d_Count = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LastAccessTime
      d_LastAccessTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Referrer::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier CRC
      n_size += sizeof (identifier);

   // string Referrer
      n_size += sizeof (size_t);
      n_size += d_Referrer.length()+1;

   // int Count
      n_size += sizeof (int);

   // int LastAccessTime
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Referrer::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier CRC
      (*(identifier*)(file+nOffset)) = d_CRC;
      nOffset += sizeof (identifier);

   // string Referrer
      size_t n_Referrer = d_Referrer.length()+1;
      (*(size_t*)(file+nOffset)) = n_Referrer;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Referrer.c_str(), n_Referrer);
      ENCODE_STRING (n_Referrer, (char*)(file+nOffset));
      nOffset += n_Referrer;

   // int Count
      (*(int*)(file+nOffset)) = d_Count;
      nOffset += sizeof (int);

   // int LastAccessTime
      (*(int*)(file+nOffset)) = d_LastAccessTime;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Referrer::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Referrer], objID);
      dbg += SSS;

   // identifier CRC
      SSS.Format ("CRC = %d\n", d_CRC);
      dbg += SSS;

   // string Referrer
      SSS.Format ("Referrer = '%s'\n", d_Referrer.c_str());
      dbg += SSS;

   // int Count
      SSS.Format ("Count = %d\n", d_Count);
      dbg += SSS;

   // int LastAccessTime
      SSS.Format ("LastAccessTime = %d\n", d_LastAccessTime);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_DailyReferrerStats::OD_DailyReferrerStats (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_DailyReferrerStats;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_SiteID = NA;
      d_Referrer.Alloc (0);
      d_Count.Alloc (0);
      d_TimeStamp = 0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_DailyReferrerStats::~OD_DailyReferrerStats () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_DailyReferrerStats::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_SiteID;         break;
         case 4: ka += d_TimeStamp;      break;
         case 5: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_DailyReferrerStats::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier SiteID
      d_SiteID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Referrer []
      int arr_size_Referrer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Referrer.Alloc (arr_size_Referrer);
      OD_LOAD_SIMPLE_ARRAY (identifier,Referrer);

   // int Count []
      int arr_size_Count = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Count.Alloc (arr_size_Count);
      OD_LOAD_SIMPLE_ARRAY (int,Count);

   // int TimeStamp
      d_TimeStamp = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_DailyReferrerStats::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier SiteID
      n_size += sizeof (identifier);

   // identifier Referrer []
      n_size += sizeof (size_t);
      n_size += d_Referrer.GetSize() * sizeof(identifier);

   // int Count []
      n_size += sizeof (size_t);
      n_size += d_Count.GetSize() * sizeof(int);

   // int TimeStamp
      n_size += sizeof (int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_DailyReferrerStats::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier SiteID
      (*(identifier*)(file+nOffset)) = d_SiteID;
      nOffset += sizeof (identifier);

   // identifier Referrer []
      (*(size_t*)(file+nOffset)) = d_Referrer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Referrer);

   // int Count []
      (*(size_t*)(file+nOffset)) = d_Count.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Count);

   // int TimeStamp
      (*(int*)(file+nOffset)) = d_TimeStamp;
      nOffset += sizeof (int);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_DailyReferrerStats::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_DailyReferrerStats], objID);
      dbg += SSS;

   // identifier SiteID
      SSS.Format ("SiteID = %d\n", d_SiteID);
      dbg += SSS;

   // identifier Referrer []
      SSS.Format ("Referrer[].size = %d:\n", d_Referrer.GetSize());
      dbg += SSS;
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         SSS.Format ("   Referrer[%d] = %d\n", iReferrer, d_Referrer[iReferrer]);
         dbg += SSS;
      }

   // int Count []
      SSS.Format ("Count[].size = %d:\n", d_Count.GetSize());
      dbg += SSS;
      for (int iCount=0; iCount<d_Count.GetSize(); iCount++)
      {
         SSS.Format ("   Count[%d] = %d\n", iCount, d_Count[iCount]);
         dbg += SSS;
      }

   // int TimeStamp
      SSS.Format ("TimeStamp = %d\n", d_TimeStamp);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_SearchWordsInfo::OD_SearchWordsInfo (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_SearchWordsInfo;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_SiteID = NA;
      d_Words.Alloc (0);
      d_Count.Alloc (0);
      d_LastAccessTime.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_SearchWordsInfo::~OD_SearchWordsInfo () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_SearchWordsInfo::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_SiteID;         break;
         case 5: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_SearchWordsInfo::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier SiteID
      d_SiteID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Words []
      int arr_size_Words = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Words.Alloc (arr_size_Words);
      for (int iWords=0; iWords<(int)arr_size_Words; iWords++)
      {
         string tmp_Words;
         size_t n_Words = (*(size_t*)(file+nOffset));  // n_Words = strlen (s_Words)+1;
         nOffset += sizeof(size_t);
         char * s_Words = new char [n_Words];
         memcpy (s_Words, (file+nOffset), n_Words);
         nOffset += n_Words;
         DECODE_STRING (n_Words, s_Words);
         tmp_Words = s_Words;
         delete [] s_Words;

         d_Words[iWords] = tmp_Words;
      }

   // int Count []
      int arr_size_Count = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Count.Alloc (arr_size_Count);
      OD_LOAD_SIMPLE_ARRAY (int,Count);

   // int LastAccessTime []
      int arr_size_LastAccessTime = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_LastAccessTime.Alloc (arr_size_LastAccessTime);
      OD_LOAD_SIMPLE_ARRAY (int,LastAccessTime);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_SearchWordsInfo::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier SiteID
      n_size += sizeof (identifier);

   // string Words []
      n_size += sizeof (size_t);
      for (int iWords=0; iWords<d_Words.GetSize(); iWords++)
      {
         n_size += sizeof (size_t);
         n_size += d_Words[iWords].length()+1;
      }

   // int Count []
      n_size += sizeof (size_t);
      n_size += d_Count.GetSize() * sizeof(int);

   // int LastAccessTime []
      n_size += sizeof (size_t);
      n_size += d_LastAccessTime.GetSize() * sizeof(int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_SearchWordsInfo::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier SiteID
      (*(identifier*)(file+nOffset)) = d_SiteID;
      nOffset += sizeof (identifier);

   // string Words []
      (*(size_t*)(file+nOffset)) = d_Words.GetSize();
      nOffset += sizeof(size_t);
      for (int iWords=0; iWords<d_Words.GetSize(); iWords++)
      {
         size_t n_Words = d_Words[iWords].length()+1;
         (*(size_t*)(file+nOffset)) = n_Words;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Words[iWords].c_str(), n_Words);
         ENCODE_STRING (n_Words, (char*)(file+nOffset));
         nOffset += n_Words;
      }

   // int Count []
      (*(size_t*)(file+nOffset)) = d_Count.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Count);

   // int LastAccessTime []
      (*(size_t*)(file+nOffset)) = d_LastAccessTime.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,LastAccessTime);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_SearchWordsInfo::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_SearchWordsInfo], objID);
      dbg += SSS;

   // identifier SiteID
      SSS.Format ("SiteID = %d\n", d_SiteID);
      dbg += SSS;

   // string Words []
      SSS.Format ("Words[].size = %d:\n", d_Words.GetSize());
      dbg += SSS;
      for (int iWords=0; iWords<d_Words.GetSize(); iWords++)
      {
         SSS.Format ("   Words[%d] = '%s'\n", iWords, d_Words[iWords].c_str());
         dbg += SSS;
      }

   // int Count []
      SSS.Format ("Count[].size = %d:\n", d_Count.GetSize());
      dbg += SSS;
      for (int iCount=0; iCount<d_Count.GetSize(); iCount++)
      {
         SSS.Format ("   Count[%d] = %d\n", iCount, d_Count[iCount]);
         dbg += SSS;
      }

   // int LastAccessTime []
      SSS.Format ("LastAccessTime[].size = %d:\n", d_LastAccessTime.GetSize());
      dbg += SSS;
      for (int iLastAccessTime=0; iLastAccessTime<d_LastAccessTime.GetSize(); iLastAccessTime++)
      {
         SSS.Format ("   LastAccessTime[%d] = %d\n", iLastAccessTime, d_LastAccessTime[iLastAccessTime]);
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_SuspiciousInfo::OD_SuspiciousInfo (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_SuspiciousInfo;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Site = NA;
      d_Pointer = 0;
      d_Viewer.Alloc (0);
      d_Referrer.Alloc (0);
      d_Time.Alloc (0);
      d_EventType.Alloc (0);
      d_CacheTime = 0;
   }

// Деструктор
  OD_SuspiciousInfo::~OD_SuspiciousInfo () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_SuspiciousInfo::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Site;           break;
         case 2: ka += d_Pointer;        break;
         case 7: ka += d_CacheTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_SuspiciousInfo::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier Site
      d_Site = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Pointer
      d_Pointer = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Viewer []
      int arr_size_Viewer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Viewer.Alloc (arr_size_Viewer);
      OD_LOAD_SIMPLE_ARRAY (identifier,Viewer);

   // string Referrer []
      int arr_size_Referrer = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Referrer.Alloc (arr_size_Referrer);
      for (int iReferrer=0; iReferrer<(int)arr_size_Referrer; iReferrer++)
      {
         string tmp_Referrer;
         size_t n_Referrer = (*(size_t*)(file+nOffset));  // n_Referrer = strlen (s_Referrer)+1;
         nOffset += sizeof(size_t);
         char * s_Referrer = new char [n_Referrer];
         memcpy (s_Referrer, (file+nOffset), n_Referrer);
         nOffset += n_Referrer;
         DECODE_STRING (n_Referrer, s_Referrer);
         tmp_Referrer = s_Referrer;
         delete [] s_Referrer;

         d_Referrer[iReferrer] = tmp_Referrer;
      }

   // int Time []
      int arr_size_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Time.Alloc (arr_size_Time);
      OD_LOAD_SIMPLE_ARRAY (int,Time);

   // int EventType []
      int arr_size_EventType = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_EventType.Alloc (arr_size_EventType);
      OD_LOAD_SIMPLE_ARRAY (int,EventType);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_SuspiciousInfo::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier Site
      n_size += sizeof (identifier);

   // int Pointer
      n_size += sizeof (int);

   // identifier Viewer []
      n_size += sizeof (size_t);
      n_size += d_Viewer.GetSize() * sizeof(identifier);

   // string Referrer []
      n_size += sizeof (size_t);
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         n_size += sizeof (size_t);
         n_size += d_Referrer[iReferrer].length()+1;
      }

   // int Time []
      n_size += sizeof (size_t);
      n_size += d_Time.GetSize() * sizeof(int);

   // int EventType []
      n_size += sizeof (size_t);
      n_size += d_EventType.GetSize() * sizeof(int);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_SuspiciousInfo::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier Site
      (*(identifier*)(file+nOffset)) = d_Site;
      nOffset += sizeof (identifier);

   // int Pointer
      (*(int*)(file+nOffset)) = d_Pointer;
      nOffset += sizeof (int);

   // identifier Viewer []
      (*(size_t*)(file+nOffset)) = d_Viewer.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Viewer);

   // string Referrer []
      (*(size_t*)(file+nOffset)) = d_Referrer.GetSize();
      nOffset += sizeof(size_t);
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         size_t n_Referrer = d_Referrer[iReferrer].length()+1;
         (*(size_t*)(file+nOffset)) = n_Referrer;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Referrer[iReferrer].c_str(), n_Referrer);
         ENCODE_STRING (n_Referrer, (char*)(file+nOffset));
         nOffset += n_Referrer;
      }

   // int Time []
      (*(size_t*)(file+nOffset)) = d_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Time);

   // int EventType []
      (*(size_t*)(file+nOffset)) = d_EventType.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,EventType);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_SuspiciousInfo::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_SuspiciousInfo], objID);
      dbg += SSS;

   // identifier Site
      SSS.Format ("Site = %d\n", d_Site);
      dbg += SSS;

   // int Pointer
      SSS.Format ("Pointer = %d\n", d_Pointer);
      dbg += SSS;

   // identifier Viewer []
      SSS.Format ("Viewer[].size = %d:\n", d_Viewer.GetSize());
      dbg += SSS;
      for (int iViewer=0; iViewer<d_Viewer.GetSize(); iViewer++)
      {
         SSS.Format ("   Viewer[%d] = %d\n", iViewer, d_Viewer[iViewer]);
         dbg += SSS;
      }

   // string Referrer []
      SSS.Format ("Referrer[].size = %d:\n", d_Referrer.GetSize());
      dbg += SSS;
      for (int iReferrer=0; iReferrer<d_Referrer.GetSize(); iReferrer++)
      {
         SSS.Format ("   Referrer[%d] = '%s'\n", iReferrer, d_Referrer[iReferrer].c_str());
         dbg += SSS;
      }

   // int Time []
      SSS.Format ("Time[].size = %d:\n", d_Time.GetSize());
      dbg += SSS;
      for (int iTime=0; iTime<d_Time.GetSize(); iTime++)
      {
         SSS.Format ("   Time[%d] = %d\n", iTime, d_Time[iTime]);
         dbg += SSS;
      }

   // int EventType []
      SSS.Format ("EventType[].size = %d:\n", d_EventType.GetSize());
      dbg += SSS;
      for (int iEventType=0; iEventType<d_EventType.GetSize(); iEventType++)
      {
         SSS.Format ("   EventType[%d] = %d\n", iEventType, d_EventType[iEventType]);
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_RatingPlaceInfo::OD_RatingPlaceInfo (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_RatingPlaceInfo;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_Site = NA;
      d_LastHourPosition.Alloc (0);
      d_LHP_Pointer = 0;
      d_LastDailyPosition.Alloc (0);
      d_LDP_Pointer = 0;
      d_LDP_UpdateTime = 0;
      d_DailyPositionDiff = (float) 0.0;
      d_CacheTime = 0;
   }

// Деструктор
  OD_RatingPlaceInfo::~OD_RatingPlaceInfo () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_RatingPlaceInfo::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Site;                   break;
         case 3: ka += d_LHP_Pointer;            break;
         case 5: ka += d_LDP_Pointer;            break;
         case 6: ka += d_LDP_UpdateTime;         break;
         case 7: ka += d_DailyPositionDiff;      break;
         case 8: ka += d_CacheTime;              break;
      }
   }


// Загрузка объекта с диска
   size_t OD_RatingPlaceInfo::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier Site
      d_Site = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int LastHourPosition []
      int arr_size_LastHourPosition = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_LastHourPosition.Alloc (arr_size_LastHourPosition);
      OD_LOAD_SIMPLE_ARRAY (int,LastHourPosition);

   // int LHP_Pointer
      d_LHP_Pointer = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float LastDailyPosition []
      int arr_size_LastDailyPosition = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_LastDailyPosition.Alloc (arr_size_LastDailyPosition);
      OD_LOAD_SIMPLE_ARRAY (float,LastDailyPosition);

   // int LDP_Pointer
      d_LDP_Pointer = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LDP_UpdateTime
      d_LDP_UpdateTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float DailyPositionDiff
      d_DailyPositionDiff = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_RatingPlaceInfo::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier Site
      n_size += sizeof (identifier);

   // int LastHourPosition []
      n_size += sizeof (size_t);
      n_size += d_LastHourPosition.GetSize() * sizeof(int);

   // int LHP_Pointer
      n_size += sizeof (int);

   // float LastDailyPosition []
      n_size += sizeof (size_t);
      n_size += d_LastDailyPosition.GetSize() * sizeof(float);

   // int LDP_Pointer
      n_size += sizeof (int);

   // int LDP_UpdateTime
      n_size += sizeof (int);

   // float DailyPositionDiff
      n_size += sizeof (float);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_RatingPlaceInfo::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier Site
      (*(identifier*)(file+nOffset)) = d_Site;
      nOffset += sizeof (identifier);

   // int LastHourPosition []
      (*(size_t*)(file+nOffset)) = d_LastHourPosition.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,LastHourPosition);

   // int LHP_Pointer
      (*(int*)(file+nOffset)) = d_LHP_Pointer;
      nOffset += sizeof (int);

   // float LastDailyPosition []
      (*(size_t*)(file+nOffset)) = d_LastDailyPosition.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (float,LastDailyPosition);

   // int LDP_Pointer
      (*(int*)(file+nOffset)) = d_LDP_Pointer;
      nOffset += sizeof (int);

   // int LDP_UpdateTime
      (*(int*)(file+nOffset)) = d_LDP_UpdateTime;
      nOffset += sizeof (int);

   // float DailyPositionDiff
      (*(float*)(file+nOffset)) = d_DailyPositionDiff;
      nOffset += sizeof (float);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_RatingPlaceInfo::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_RatingPlaceInfo], objID);
      dbg += SSS;

   // identifier Site
      SSS.Format ("Site = %d\n", d_Site);
      dbg += SSS;

   // int LastHourPosition []
      SSS.Format ("LastHourPosition[].size = %d:\n", d_LastHourPosition.GetSize());
      dbg += SSS;
      for (int iLastHourPosition=0; iLastHourPosition<d_LastHourPosition.GetSize(); iLastHourPosition++)
      {
         SSS.Format ("   LastHourPosition[%d] = %d\n", iLastHourPosition, d_LastHourPosition[iLastHourPosition]);
         dbg += SSS;
      }

   // int LHP_Pointer
      SSS.Format ("LHP_Pointer = %d\n", d_LHP_Pointer);
      dbg += SSS;

   // float LastDailyPosition []
      SSS.Format ("LastDailyPosition[].size = %d:\n", d_LastDailyPosition.GetSize());
      dbg += SSS;
      for (int iLastDailyPosition=0; iLastDailyPosition<d_LastDailyPosition.GetSize(); iLastDailyPosition++)
      {
         SSS.Format ("   LastDailyPosition[%d] = %f\n", iLastDailyPosition, d_LastDailyPosition[iLastDailyPosition]);
         dbg += SSS;
      }

   // int LDP_Pointer
      SSS.Format ("LDP_Pointer = %d\n", d_LDP_Pointer);
      dbg += SSS;

   // int LDP_UpdateTime
      SSS.Format ("LDP_UpdateTime = %d\n", d_LDP_UpdateTime);
      dbg += SSS;

   // float DailyPositionDiff
      SSS.Format ("DailyPositionDiff = %f\n", d_DailyPositionDiff);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_IPRecord::OD_IPRecord (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_IPRecord;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_Count = 0;
      d_Checked = false;
      d_ConceptID.Alloc (0);
      d_ConceptNo.Alloc (0);
      d_CRA_Audience.Alloc (0);
      d_CRA_Inquiry.Alloc (0);
      d_CacheTime = 0;
      d_Hits = NA;
      d_Hosts = NA;
      d_Visitors = NA;
      d_Anonymous = NA;
      d_Suspicious = NA;
      d_Total_Hits = 0;
      d_Total_Hosts = 0;
      d_Total_Visitors = 0;
      d_Total_Anonymous = 0;
      d_Total_Suspicious = 0;
      d_LM_Hits = 0;
      d_LM_Hosts = 0;
      d_LM_Visitors = 0;
      d_LM_Anonymous = 0;
      d_LM_Suspicious = 0;
      d_LW_Hits = 0;
      d_LW_Hosts = 0;
      d_LW_Visitors = 0;
      d_LW_Anonymous = 0;
      d_LW_Suspicious = 0;
      d_LD_Hits = 0;
      d_LD_Hosts = 0;
      d_LD_Visitors = 0;
      d_LD_Anonymous = 0;
      d_LD_Suspicious = 0;
      d_LH_Hits = 0;
      d_LH_Hosts = 0;
      d_LH_Visitors = 0;
      d_LH_Anonymous = 0;
      d_LH_Suspicious = 0;
   }

// Деструктор
  OD_IPRecord::~OD_IPRecord () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_IPRecord::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Count;                 break;
         case 2: ka += d_Mask;                  break;
         case 3: ka += d_First;                 break;
         case 4: ka += d_Last;                  break;
         case 5: ka += d_Checked;               break;
         case 10: ka += d_CacheTime;             break;
         case 11: ka += d_Hits;                  break;
         case 12: ka += d_Hosts;                 break;
         case 13: ka += d_Visitors;              break;
         case 14: ka += d_Anonymous;             break;
         case 15: ka += d_Suspicious;            break;
         case 16: ka += d_Total_Hits;            break;
         case 17: ka += d_Total_Hosts;           break;
         case 18: ka += d_Total_Visitors;        break;
         case 19: ka += d_Total_Anonymous;       break;
         case 20: ka += d_Total_Suspicious;      break;
         case 21: ka += d_LM_Hits;               break;
         case 22: ka += d_LM_Hosts;              break;
         case 23: ka += d_LM_Visitors;           break;
         case 24: ka += d_LM_Anonymous;          break;
         case 25: ka += d_LM_Suspicious;         break;
         case 26: ka += d_LW_Hits;               break;
         case 27: ka += d_LW_Hosts;              break;
         case 28: ka += d_LW_Visitors;           break;
         case 29: ka += d_LW_Anonymous;          break;
         case 30: ka += d_LW_Suspicious;         break;
         case 31: ka += d_LD_Hits;               break;
         case 32: ka += d_LD_Hosts;              break;
         case 33: ka += d_LD_Visitors;           break;
         case 34: ka += d_LD_Anonymous;          break;
         case 35: ka += d_LD_Suspicious;         break;
         case 36: ka += d_LH_Hits;               break;
         case 37: ka += d_LH_Hosts;              break;
         case 38: ka += d_LH_Visitors;           break;
         case 39: ka += d_LH_Anonymous;          break;
         case 40: ka += d_LH_Suspicious;         break;
      }
   }


// Загрузка объекта с диска
   size_t OD_IPRecord::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // int Count
      d_Count = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string Mask
      size_t n_Mask = (*(size_t*)(file+nOffset));  // n_Mask = strlen (s_Mask)+1;
      nOffset += sizeof(size_t);
      char * s_Mask = new char [n_Mask];
      memcpy (s_Mask, (file+nOffset), n_Mask);
      nOffset += n_Mask;
      DECODE_STRING (n_Mask, s_Mask);
      d_Mask = s_Mask;
      delete [] s_Mask;

   // string First
      size_t n_First = (*(size_t*)(file+nOffset));  // n_First = strlen (s_First)+1;
      nOffset += sizeof(size_t);
      char * s_First = new char [n_First];
      memcpy (s_First, (file+nOffset), n_First);
      nOffset += n_First;
      DECODE_STRING (n_First, s_First);
      d_First = s_First;
      delete [] s_First;

   // string Last
      size_t n_Last = (*(size_t*)(file+nOffset));  // n_Last = strlen (s_Last)+1;
      nOffset += sizeof(size_t);
      char * s_Last = new char [n_Last];
      memcpy (s_Last, (file+nOffset), n_Last);
      nOffset += n_Last;
      DECODE_STRING (n_Last, s_Last);
      d_Last = s_Last;
      delete [] s_Last;

   // bool Checked
      d_Checked = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // identifier ConceptID []
      int arr_size_ConceptID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptID.Alloc (arr_size_ConceptID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ConceptID);

   // int ConceptNo []
      int arr_size_ConceptNo = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ConceptNo.Alloc (arr_size_ConceptNo);
      OD_LOAD_SIMPLE_ARRAY (int,ConceptNo);

   // int CRA_Audience []
      int arr_size_CRA_Audience = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Audience.Alloc (arr_size_CRA_Audience);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Audience);

   // int CRA_Inquiry []
      int arr_size_CRA_Inquiry = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CRA_Inquiry.Alloc (arr_size_CRA_Inquiry);
      OD_LOAD_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier Hits
      d_Hits = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Hosts
      d_Hosts = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Visitors
      d_Visitors = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Anonymous
      d_Anonymous = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier Suspicious
      d_Suspicious = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int Total_Hits
      d_Total_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Hosts
      d_Total_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Visitors
      d_Total_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Anonymous
      d_Total_Anonymous = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Total_Suspicious
      d_Total_Suspicious = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hits
      d_LM_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Hosts
      d_LM_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Visitors
      d_LM_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Anonymous
      d_LM_Anonymous = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LM_Suspicious
      d_LM_Suspicious = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hits
      d_LW_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Hosts
      d_LW_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Visitors
      d_LW_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Anonymous
      d_LW_Anonymous = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LW_Suspicious
      d_LW_Suspicious = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hits
      d_LD_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Hosts
      d_LD_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Visitors
      d_LD_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Anonymous
      d_LD_Anonymous = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LD_Suspicious
      d_LD_Suspicious = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hits
      d_LH_Hits = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Hosts
      d_LH_Hosts = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Visitors
      d_LH_Visitors = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Anonymous
      d_LH_Anonymous = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LH_Suspicious
      d_LH_Suspicious = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_IPRecord::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int Count
      n_size += sizeof (int);

   // string Mask
      n_size += sizeof (size_t);
      n_size += d_Mask.length()+1;

   // string First
      n_size += sizeof (size_t);
      n_size += d_First.length()+1;

   // string Last
      n_size += sizeof (size_t);
      n_size += d_Last.length()+1;

   // bool Checked
      n_size += sizeof (bool);

   // identifier ConceptID []
      n_size += sizeof (size_t);
      n_size += d_ConceptID.GetSize() * sizeof(identifier);

   // int ConceptNo []
      n_size += sizeof (size_t);
      n_size += d_ConceptNo.GetSize() * sizeof(int);

   // int CRA_Audience []
      n_size += sizeof (size_t);
      n_size += d_CRA_Audience.GetSize() * sizeof(int);

   // int CRA_Inquiry []
      n_size += sizeof (size_t);
      n_size += d_CRA_Inquiry.GetSize() * sizeof(int);

   // int CacheTime
      n_size += sizeof (int);

   // identifier Hits
      n_size += sizeof (identifier);

   // identifier Hosts
      n_size += sizeof (identifier);

   // identifier Visitors
      n_size += sizeof (identifier);

   // identifier Anonymous
      n_size += sizeof (identifier);

   // identifier Suspicious
      n_size += sizeof (identifier);

   // int Total_Hits
      n_size += sizeof (int);

   // int Total_Hosts
      n_size += sizeof (int);

   // int Total_Visitors
      n_size += sizeof (int);

   // int Total_Anonymous
      n_size += sizeof (int);

   // int Total_Suspicious
      n_size += sizeof (int);

   // int LM_Hits
      n_size += sizeof (int);

   // int LM_Hosts
      n_size += sizeof (int);

   // int LM_Visitors
      n_size += sizeof (int);

   // int LM_Anonymous
      n_size += sizeof (int);

   // int LM_Suspicious
      n_size += sizeof (int);

   // int LW_Hits
      n_size += sizeof (int);

   // int LW_Hosts
      n_size += sizeof (int);

   // int LW_Visitors
      n_size += sizeof (int);

   // int LW_Anonymous
      n_size += sizeof (int);

   // int LW_Suspicious
      n_size += sizeof (int);

   // int LD_Hits
      n_size += sizeof (int);

   // int LD_Hosts
      n_size += sizeof (int);

   // int LD_Visitors
      n_size += sizeof (int);

   // int LD_Anonymous
      n_size += sizeof (int);

   // int LD_Suspicious
      n_size += sizeof (int);

   // int LH_Hits
      n_size += sizeof (int);

   // int LH_Hosts
      n_size += sizeof (int);

   // int LH_Visitors
      n_size += sizeof (int);

   // int LH_Anonymous
      n_size += sizeof (int);

   // int LH_Suspicious
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_IPRecord::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int Count
      (*(int*)(file+nOffset)) = d_Count;
      nOffset += sizeof (int);

   // string Mask
      size_t n_Mask = d_Mask.length()+1;
      (*(size_t*)(file+nOffset)) = n_Mask;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Mask.c_str(), n_Mask);
      ENCODE_STRING (n_Mask, (char*)(file+nOffset));
      nOffset += n_Mask;

   // string First
      size_t n_First = d_First.length()+1;
      (*(size_t*)(file+nOffset)) = n_First;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_First.c_str(), n_First);
      ENCODE_STRING (n_First, (char*)(file+nOffset));
      nOffset += n_First;

   // string Last
      size_t n_Last = d_Last.length()+1;
      (*(size_t*)(file+nOffset)) = n_Last;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Last.c_str(), n_Last);
      ENCODE_STRING (n_Last, (char*)(file+nOffset));
      nOffset += n_Last;

   // bool Checked
      (*(bool*)(file+nOffset)) = d_Checked;
      nOffset += sizeof (bool);

   // identifier ConceptID []
      (*(size_t*)(file+nOffset)) = d_ConceptID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ConceptID);

   // int ConceptNo []
      (*(size_t*)(file+nOffset)) = d_ConceptNo.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,ConceptNo);

   // int CRA_Audience []
      (*(size_t*)(file+nOffset)) = d_CRA_Audience.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Audience);

   // int CRA_Inquiry []
      (*(size_t*)(file+nOffset)) = d_CRA_Inquiry.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,CRA_Inquiry);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);

   // identifier Hits
      (*(identifier*)(file+nOffset)) = d_Hits;
      nOffset += sizeof (identifier);

   // identifier Hosts
      (*(identifier*)(file+nOffset)) = d_Hosts;
      nOffset += sizeof (identifier);

   // identifier Visitors
      (*(identifier*)(file+nOffset)) = d_Visitors;
      nOffset += sizeof (identifier);

   // identifier Anonymous
      (*(identifier*)(file+nOffset)) = d_Anonymous;
      nOffset += sizeof (identifier);

   // identifier Suspicious
      (*(identifier*)(file+nOffset)) = d_Suspicious;
      nOffset += sizeof (identifier);

   // int Total_Hits
      (*(int*)(file+nOffset)) = d_Total_Hits;
      nOffset += sizeof (int);

   // int Total_Hosts
      (*(int*)(file+nOffset)) = d_Total_Hosts;
      nOffset += sizeof (int);

   // int Total_Visitors
      (*(int*)(file+nOffset)) = d_Total_Visitors;
      nOffset += sizeof (int);

   // int Total_Anonymous
      (*(int*)(file+nOffset)) = d_Total_Anonymous;
      nOffset += sizeof (int);

   // int Total_Suspicious
      (*(int*)(file+nOffset)) = d_Total_Suspicious;
      nOffset += sizeof (int);

   // int LM_Hits
      (*(int*)(file+nOffset)) = d_LM_Hits;
      nOffset += sizeof (int);

   // int LM_Hosts
      (*(int*)(file+nOffset)) = d_LM_Hosts;
      nOffset += sizeof (int);

   // int LM_Visitors
      (*(int*)(file+nOffset)) = d_LM_Visitors;
      nOffset += sizeof (int);

   // int LM_Anonymous
      (*(int*)(file+nOffset)) = d_LM_Anonymous;
      nOffset += sizeof (int);

   // int LM_Suspicious
      (*(int*)(file+nOffset)) = d_LM_Suspicious;
      nOffset += sizeof (int);

   // int LW_Hits
      (*(int*)(file+nOffset)) = d_LW_Hits;
      nOffset += sizeof (int);

   // int LW_Hosts
      (*(int*)(file+nOffset)) = d_LW_Hosts;
      nOffset += sizeof (int);

   // int LW_Visitors
      (*(int*)(file+nOffset)) = d_LW_Visitors;
      nOffset += sizeof (int);

   // int LW_Anonymous
      (*(int*)(file+nOffset)) = d_LW_Anonymous;
      nOffset += sizeof (int);

   // int LW_Suspicious
      (*(int*)(file+nOffset)) = d_LW_Suspicious;
      nOffset += sizeof (int);

   // int LD_Hits
      (*(int*)(file+nOffset)) = d_LD_Hits;
      nOffset += sizeof (int);

   // int LD_Hosts
      (*(int*)(file+nOffset)) = d_LD_Hosts;
      nOffset += sizeof (int);

   // int LD_Visitors
      (*(int*)(file+nOffset)) = d_LD_Visitors;
      nOffset += sizeof (int);

   // int LD_Anonymous
      (*(int*)(file+nOffset)) = d_LD_Anonymous;
      nOffset += sizeof (int);

   // int LD_Suspicious
      (*(int*)(file+nOffset)) = d_LD_Suspicious;
      nOffset += sizeof (int);

   // int LH_Hits
      (*(int*)(file+nOffset)) = d_LH_Hits;
      nOffset += sizeof (int);

   // int LH_Hosts
      (*(int*)(file+nOffset)) = d_LH_Hosts;
      nOffset += sizeof (int);

   // int LH_Visitors
      (*(int*)(file+nOffset)) = d_LH_Visitors;
      nOffset += sizeof (int);

   // int LH_Anonymous
      (*(int*)(file+nOffset)) = d_LH_Anonymous;
      nOffset += sizeof (int);

   // int LH_Suspicious
      (*(int*)(file+nOffset)) = d_LH_Suspicious;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_IPRecord::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_IPRecord], objID);
      dbg += SSS;

   // int Count
      SSS.Format ("Count = %d\n", d_Count);
      dbg += SSS;

   // string Mask
      SSS.Format ("Mask = '%s'\n", d_Mask.c_str());
      dbg += SSS;

   // string First
      SSS.Format ("First = '%s'\n", d_First.c_str());
      dbg += SSS;

   // string Last
      SSS.Format ("Last = '%s'\n", d_Last.c_str());
      dbg += SSS;

   // bool Checked
      SSS.Format ("Checked = %s\n", d_Checked?"true":"false");
      dbg += SSS;

   // identifier ConceptID []
      SSS.Format ("ConceptID[].size = %d:\n", d_ConceptID.GetSize());
      dbg += SSS;
      for (int iConceptID=0; iConceptID<d_ConceptID.GetSize(); iConceptID++)
      {
         SSS.Format ("   ConceptID[%d] = %d\n", iConceptID, d_ConceptID[iConceptID]);
         dbg += SSS;
      }

   // int ConceptNo []
      SSS.Format ("ConceptNo[].size = %d:\n", d_ConceptNo.GetSize());
      dbg += SSS;
      for (int iConceptNo=0; iConceptNo<d_ConceptNo.GetSize(); iConceptNo++)
      {
         SSS.Format ("   ConceptNo[%d] = %d\n", iConceptNo, d_ConceptNo[iConceptNo]);
         dbg += SSS;
      }

   // int CRA_Audience []
      SSS.Format ("CRA_Audience[].size = %d:\n", d_CRA_Audience.GetSize());
      dbg += SSS;
      for (int iCRA_Audience=0; iCRA_Audience<d_CRA_Audience.GetSize(); iCRA_Audience++)
      {
         SSS.Format ("   CRA_Audience[%d] = %d\n", iCRA_Audience, d_CRA_Audience[iCRA_Audience]);
         dbg += SSS;
      }

   // int CRA_Inquiry []
      SSS.Format ("CRA_Inquiry[].size = %d:\n", d_CRA_Inquiry.GetSize());
      dbg += SSS;
      for (int iCRA_Inquiry=0; iCRA_Inquiry<d_CRA_Inquiry.GetSize(); iCRA_Inquiry++)
      {
         SSS.Format ("   CRA_Inquiry[%d] = %d\n", iCRA_Inquiry, d_CRA_Inquiry[iCRA_Inquiry]);
         dbg += SSS;
      }

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;

   // identifier Hits
      SSS.Format ("Hits = %d\n", d_Hits);
      dbg += SSS;

   // identifier Hosts
      SSS.Format ("Hosts = %d\n", d_Hosts);
      dbg += SSS;

   // identifier Visitors
      SSS.Format ("Visitors = %d\n", d_Visitors);
      dbg += SSS;

   // identifier Anonymous
      SSS.Format ("Anonymous = %d\n", d_Anonymous);
      dbg += SSS;

   // identifier Suspicious
      SSS.Format ("Suspicious = %d\n", d_Suspicious);
      dbg += SSS;

   // int Total_Hits
      SSS.Format ("Total_Hits = %d\n", d_Total_Hits);
      dbg += SSS;

   // int Total_Hosts
      SSS.Format ("Total_Hosts = %d\n", d_Total_Hosts);
      dbg += SSS;

   // int Total_Visitors
      SSS.Format ("Total_Visitors = %d\n", d_Total_Visitors);
      dbg += SSS;

   // int Total_Anonymous
      SSS.Format ("Total_Anonymous = %d\n", d_Total_Anonymous);
      dbg += SSS;

   // int Total_Suspicious
      SSS.Format ("Total_Suspicious = %d\n", d_Total_Suspicious);
      dbg += SSS;

   // int LM_Hits
      SSS.Format ("LM_Hits = %d\n", d_LM_Hits);
      dbg += SSS;

   // int LM_Hosts
      SSS.Format ("LM_Hosts = %d\n", d_LM_Hosts);
      dbg += SSS;

   // int LM_Visitors
      SSS.Format ("LM_Visitors = %d\n", d_LM_Visitors);
      dbg += SSS;

   // int LM_Anonymous
      SSS.Format ("LM_Anonymous = %d\n", d_LM_Anonymous);
      dbg += SSS;

   // int LM_Suspicious
      SSS.Format ("LM_Suspicious = %d\n", d_LM_Suspicious);
      dbg += SSS;

   // int LW_Hits
      SSS.Format ("LW_Hits = %d\n", d_LW_Hits);
      dbg += SSS;

   // int LW_Hosts
      SSS.Format ("LW_Hosts = %d\n", d_LW_Hosts);
      dbg += SSS;

   // int LW_Visitors
      SSS.Format ("LW_Visitors = %d\n", d_LW_Visitors);
      dbg += SSS;

   // int LW_Anonymous
      SSS.Format ("LW_Anonymous = %d\n", d_LW_Anonymous);
      dbg += SSS;

   // int LW_Suspicious
      SSS.Format ("LW_Suspicious = %d\n", d_LW_Suspicious);
      dbg += SSS;

   // int LD_Hits
      SSS.Format ("LD_Hits = %d\n", d_LD_Hits);
      dbg += SSS;

   // int LD_Hosts
      SSS.Format ("LD_Hosts = %d\n", d_LD_Hosts);
      dbg += SSS;

   // int LD_Visitors
      SSS.Format ("LD_Visitors = %d\n", d_LD_Visitors);
      dbg += SSS;

   // int LD_Anonymous
      SSS.Format ("LD_Anonymous = %d\n", d_LD_Anonymous);
      dbg += SSS;

   // int LD_Suspicious
      SSS.Format ("LD_Suspicious = %d\n", d_LD_Suspicious);
      dbg += SSS;

   // int LH_Hits
      SSS.Format ("LH_Hits = %d\n", d_LH_Hits);
      dbg += SSS;

   // int LH_Hosts
      SSS.Format ("LH_Hosts = %d\n", d_LH_Hosts);
      dbg += SSS;

   // int LH_Visitors
      SSS.Format ("LH_Visitors = %d\n", d_LH_Visitors);
      dbg += SSS;

   // int LH_Anonymous
      SSS.Format ("LH_Anonymous = %d\n", d_LH_Anonymous);
      dbg += SSS;

   // int LH_Suspicious
      SSS.Format ("LH_Suspicious = %d\n", d_LH_Suspicious);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_ViewerReference::OD_ViewerReference (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_ViewerReference;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_ViewerID = NA;
      d_CacheTime = 0;
   }

// Деструктор
  OD_ViewerReference::~OD_ViewerReference () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_ViewerReference::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_ViewerID;           break;
         case 2: ka += d_IPAddress;          break;
         case 3: ka += d_IPAddressHash;      break;
         case 4: ka += d_CacheTime;          break;
      }
   }


// Загрузка объекта с диска
   size_t OD_ViewerReference::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // identifier ViewerID
      d_ViewerID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string IPAddress
      size_t n_IPAddress = (*(size_t*)(file+nOffset));  // n_IPAddress = strlen (s_IPAddress)+1;
      nOffset += sizeof(size_t);
      char * s_IPAddress = new char [n_IPAddress];
      memcpy (s_IPAddress, (file+nOffset), n_IPAddress);
      nOffset += n_IPAddress;
      DECODE_STRING (n_IPAddress, s_IPAddress);
      d_IPAddress = s_IPAddress;
      delete [] s_IPAddress;

   // identifier IPAddressHash
      d_IPAddressHash = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CacheTime
      d_CacheTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_ViewerReference::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier ViewerID
      n_size += sizeof (identifier);

   // string IPAddress
      n_size += sizeof (size_t);
      n_size += d_IPAddress.length()+1;

   // identifier IPAddressHash
      n_size += sizeof (identifier);

   // int CacheTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_ViewerReference::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // identifier ViewerID
      (*(identifier*)(file+nOffset)) = d_ViewerID;
      nOffset += sizeof (identifier);

   // string IPAddress
      size_t n_IPAddress = d_IPAddress.length()+1;
      (*(size_t*)(file+nOffset)) = n_IPAddress;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_IPAddress.c_str(), n_IPAddress);
      ENCODE_STRING (n_IPAddress, (char*)(file+nOffset));
      nOffset += n_IPAddress;

   // identifier IPAddressHash
      (*(identifier*)(file+nOffset)) = d_IPAddressHash;
      nOffset += sizeof (identifier);

   // int CacheTime
      (*(int*)(file+nOffset)) = d_CacheTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_ViewerReference::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_ViewerReference], objID);
      dbg += SSS;

   // identifier ViewerID
      SSS.Format ("ViewerID = %d\n", d_ViewerID);
      dbg += SSS;

   // string IPAddress
      SSS.Format ("IPAddress = '%s'\n", d_IPAddress.c_str());
      dbg += SSS;

   // identifier IPAddressHash
      SSS.Format ("IPAddressHash = %d\n", d_IPAddressHash);
      dbg += SSS;

   // int CacheTime
      SSS.Format ("CacheTime = %d\n", d_CacheTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_AbstractObject::OD_AbstractObject (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_AbstractObject;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_AbstractObject::~OD_AbstractObject () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_AbstractObject::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Type;         break;
         case 2: ka += d_Name;         break;
         case 3: ka += d_Header1;      break;
         case 4: ka += d_Header2;      break;
         case 5: ka += d_Header3;      break;
         case 6: ka += d_Body;         break;
      }
   }


// Загрузка объекта с диска
   size_t OD_AbstractObject::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return 0;
      }

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type];
      memcpy (s_Type, (file+nOffset), n_Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name];
      memcpy (s_Name, (file+nOffset), n_Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Header1
      size_t n_Header1 = (*(size_t*)(file+nOffset));  // n_Header1 = strlen (s_Header1)+1;
      nOffset += sizeof(size_t);
      char * s_Header1 = new char [n_Header1];
      memcpy (s_Header1, (file+nOffset), n_Header1);
      nOffset += n_Header1;
      DECODE_STRING (n_Header1, s_Header1);
      d_Header1 = s_Header1;
      delete [] s_Header1;

   // string Header2
      size_t n_Header2 = (*(size_t*)(file+nOffset));  // n_Header2 = strlen (s_Header2)+1;
      nOffset += sizeof(size_t);
      char * s_Header2 = new char [n_Header2];
      memcpy (s_Header2, (file+nOffset), n_Header2);
      nOffset += n_Header2;
      DECODE_STRING (n_Header2, s_Header2);
      d_Header2 = s_Header2;
      delete [] s_Header2;

   // string Header3
      size_t n_Header3 = (*(size_t*)(file+nOffset));  // n_Header3 = strlen (s_Header3)+1;
      nOffset += sizeof(size_t);
      char * s_Header3 = new char [n_Header3];
      memcpy (s_Header3, (file+nOffset), n_Header3);
      nOffset += n_Header3;
      DECODE_STRING (n_Header3, s_Header3);
      d_Header3 = s_Header3;
      delete [] s_Header3;

   // string Body
      size_t n_Body = (*(size_t*)(file+nOffset));  // n_Body = strlen (s_Body)+1;
      nOffset += sizeof(size_t);
      char * s_Body = new char [n_Body];
      memcpy (s_Body, (file+nOffset), n_Body);
      nOffset += n_Body;
      DECODE_STRING (n_Body, s_Body);
      d_Body = s_Body;
      delete [] s_Body;
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_AbstractObject::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Header1
      n_size += sizeof (size_t);
      n_size += d_Header1.length()+1;

   // string Header2
      n_size += sizeof (size_t);
      n_size += d_Header2.length()+1;

   // string Header3
      n_size += sizeof (size_t);
      n_size += d_Header3.length()+1;

   // string Body
      n_size += sizeof (size_t);
      n_size += d_Body.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_AbstractObject::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // string Type
      size_t n_Type = d_Type.length()+1;
      (*(size_t*)(file+nOffset)) = n_Type;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Type.c_str(), n_Type);
      ENCODE_STRING (n_Type, (char*)(file+nOffset));
      nOffset += n_Type;

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Header1
      size_t n_Header1 = d_Header1.length()+1;
      (*(size_t*)(file+nOffset)) = n_Header1;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Header1.c_str(), n_Header1);
      ENCODE_STRING (n_Header1, (char*)(file+nOffset));
      nOffset += n_Header1;

   // string Header2
      size_t n_Header2 = d_Header2.length()+1;
      (*(size_t*)(file+nOffset)) = n_Header2;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Header2.c_str(), n_Header2);
      ENCODE_STRING (n_Header2, (char*)(file+nOffset));
      nOffset += n_Header2;

   // string Header3
      size_t n_Header3 = d_Header3.length()+1;
      (*(size_t*)(file+nOffset)) = n_Header3;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Header3.c_str(), n_Header3);
      ENCODE_STRING (n_Header3, (char*)(file+nOffset));
      nOffset += n_Header3;

   // string Body
      size_t n_Body = d_Body.length()+1;
      (*(size_t*)(file+nOffset)) = n_Body;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Body.c_str(), n_Body);
      ENCODE_STRING (n_Body, (char*)(file+nOffset));
      nOffset += n_Body;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_AbstractObject::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_AbstractObject], objID);
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Header1
      SSS.Format ("Header1 = '%s'\n", d_Header1.c_str());
      dbg += SSS;

   // string Header2
      SSS.Format ("Header2 = '%s'\n", d_Header2.c_str());
      dbg += SSS;

   // string Header3
      SSS.Format ("Header3 = '%s'\n", d_Header3.c_str());
      dbg += SSS;

   // string Body
      SSS.Format ("Body = '%s'\n", d_Body.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
