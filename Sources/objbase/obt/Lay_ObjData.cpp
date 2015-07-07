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
   "Test_Load",
   "jerom_table",
   "tsmc_table",
   "Test_MM",
   "Test_CRC",
   "Test_4G",
   "Test_sort"
};


// Конструктор
   OD_Viewer::OD_Viewer (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Viewer;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

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
      d_TagID = NA;
      d_TagInt = 0;
      d_TagBool = false;
      d_ReservedID.Alloc (0);
      d_ReservedInt.Alloc (0);
      d_ReservedString.Alloc (0);
   }

// Деструктор
  OD_Viewer::~OD_Viewer () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Viewer::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Name;                        break;
         case 2: ka += d_Email;                       break;
         case 3: ka += d_UserAgent;                   break;
         case 4: ka += d_Anonymous;                   break;
         case 5: ka += d_TotalShows;                  break;
         case 6: ka += d_TotalClicks;                 break;
         case 7: ka += d_IPAddress;                   break;
         case 8: ka += d_Referrer;                    break;
         case 9: ka += d_IPAddressHash;               break;
         case 12: ka += d_CRN_Site_Update;             break;
         case 15: ka += d_Group;                       break;
         case 16: ka += d_TZOffset;                    break;
         case 17: ka += d_CreationTime;                break;
         case 18: ka += d_LastVisitTime;               break;
         case 24: ka += d_TotalHosts;                  break;
         case 29: ka += d_Site_SessionLastSiteID;      break;
         case 33: ka += d_BannerClickTime;             break;
         case 34: ka += d_BannerClickID;               break;
         case 35: ka += d_BannerClickSiteID;           break;
         case 36: ka += d_BannerClickHitCount;         break;
         case 37: ka += d_BannerClickSessionTime;      break;
         case 38: ka += d_TagID;                       break;
         case 39: ka += d_TagInt;                      break;
         case 40: ka += d_TagBool;                     break;
      }
   }


// Загрузка объекта с диска
   bool OD_Viewer::LoadFromFile (identifier objID)
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
         return false;
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
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Viewer::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
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
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Test_Load::OD_Test_Load (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_Load;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_Test_Load::~OD_Test_Load () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Test_Load::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Field;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_Load::LoadFromFile (identifier objID)
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
         return false;
      }

   // int Field
      d_Field = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_Load::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int Field
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_Load::WriteToFile (identifier objID)
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

   // int Field
      (*(int*)(file+nOffset)) = d_Field;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_Load::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_Load], objID);
      dbg += SSS;

   // int Field
      SSS.Format ("Field = %d\n", d_Field);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_jerom_table::OD_jerom_table (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_jerom_table;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_OperatorID = 0;
      d_MessageDate = 0;
   }

// Деструктор
  OD_jerom_table::~OD_jerom_table () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_jerom_table::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_OperatorID;       break;
         case 2: ka += d_MessageDate;      break;
         case 3: ka += d_Message;          break;
      }
   }


// Загрузка объекта с диска
   bool OD_jerom_table::LoadFromFile (identifier objID)
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
         return false;
      }

   // int OperatorID
      d_OperatorID = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MessageDate
      d_MessageDate = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string Message
      size_t n_Message = (*(size_t*)(file+nOffset));  // n_Message = strlen (s_Message)+1;
      nOffset += sizeof(size_t);
      char * s_Message = new char [n_Message];
      memcpy (s_Message, (file+nOffset), n_Message);
      nOffset += n_Message;
      DECODE_STRING (n_Message, s_Message);
      d_Message = s_Message;
      delete [] s_Message;
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_jerom_table::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int OperatorID
      n_size += sizeof (int);

   // int MessageDate
      n_size += sizeof (int);

   // string Message
      n_size += sizeof (size_t);
      n_size += d_Message.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_jerom_table::WriteToFile (identifier objID)
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

   // int OperatorID
      (*(int*)(file+nOffset)) = d_OperatorID;
      nOffset += sizeof (int);

   // int MessageDate
      (*(int*)(file+nOffset)) = d_MessageDate;
      nOffset += sizeof (int);

   // string Message
      size_t n_Message = d_Message.length()+1;
      (*(size_t*)(file+nOffset)) = n_Message;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Message.c_str(), n_Message);
      ENCODE_STRING (n_Message, (char*)(file+nOffset));
      nOffset += n_Message;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_jerom_table::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_jerom_table], objID);
      dbg += SSS;

   // int OperatorID
      SSS.Format ("OperatorID = %d\n", d_OperatorID);
      dbg += SSS;

   // int MessageDate
      SSS.Format ("MessageDate = %d\n", d_MessageDate);
      dbg += SSS;

   // string Message
      SSS.Format ("Message = '%s'\n", d_Message.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_tsmc_table::OD_tsmc_table (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_tsmc_table;


      m_CoIndexPtr = new OBD_pointer [3];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      if (!bFieldsInit) return;

      d_Int_Field = 0;
      d_Float_Field = (float) 0.0;
      d_Text_Field = "abc";
   }

// Деструктор
  OD_tsmc_table::~OD_tsmc_table () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_tsmc_table::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_Int_Field;        break;
         case 2: ka += d_Float_Field;      break;
         case 3: ka += d_Text_Field;       break;
      }
   }


// Загрузка объекта с диска
   bool OD_tsmc_table::LoadFromFile (identifier objID)
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
         return false;
      }

   // int Int_Field
      d_Int_Field = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Float_Field
      d_Float_Field = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // string Text_Field
      size_t n_Text_Field = (*(size_t*)(file+nOffset));  // n_Text_Field = strlen (s_Text_Field)+1;
      nOffset += sizeof(size_t);
      char * s_Text_Field = new char [n_Text_Field];
      memcpy (s_Text_Field, (file+nOffset), n_Text_Field);
      nOffset += n_Text_Field;
      DECODE_STRING (n_Text_Field, s_Text_Field);
      d_Text_Field = s_Text_Field;
      delete [] s_Text_Field;
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_tsmc_table::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int Int_Field
      n_size += sizeof (int);

   // float Float_Field
      n_size += sizeof (float);

   // string Text_Field
      n_size += sizeof (size_t);
      n_size += d_Text_Field.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_tsmc_table::WriteToFile (identifier objID)
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

   // int Int_Field
      (*(int*)(file+nOffset)) = d_Int_Field;
      nOffset += sizeof (int);

   // float Float_Field
      (*(float*)(file+nOffset)) = d_Float_Field;
      nOffset += sizeof (float);

   // string Text_Field
      size_t n_Text_Field = d_Text_Field.length()+1;
      (*(size_t*)(file+nOffset)) = n_Text_Field;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Text_Field.c_str(), n_Text_Field);
      ENCODE_STRING (n_Text_Field, (char*)(file+nOffset));
      nOffset += n_Text_Field;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_tsmc_table::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_tsmc_table], objID);
      dbg += SSS;

   // int Int_Field
      SSS.Format ("Int_Field = %d\n", d_Int_Field);
      dbg += SSS;

   // float Float_Field
      SSS.Format ("Float_Field = %f\n", d_Float_Field);
      dbg += SSS;

   // string Text_Field
      SSS.Format ("Text_Field = '%s'\n", d_Text_Field.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Test_MM::OD_Test_MM (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_MM;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_Test_MM::~OD_Test_MM () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Test_MM::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_n;      break;
         case 2: ka += d_s;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_MM::LoadFromFile (identifier objID)
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
         return false;
      }

   // int n
      d_n = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string s
      size_t n_s = (*(size_t*)(file+nOffset));  // n_s = strlen (s_s)+1;
      nOffset += sizeof(size_t);
      char * s_s = new char [n_s];
      memcpy (s_s, (file+nOffset), n_s);
      nOffset += n_s;
      DECODE_STRING (n_s, s_s);
      d_s = s_s;
      delete [] s_s;
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_MM::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int n
      n_size += sizeof (int);

   // string s
      n_size += sizeof (size_t);
      n_size += d_s.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_MM::WriteToFile (identifier objID)
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

   // int n
      (*(int*)(file+nOffset)) = d_n;
      nOffset += sizeof (int);

   // string s
      size_t n_s = d_s.length()+1;
      (*(size_t*)(file+nOffset)) = n_s;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_s.c_str(), n_s);
      ENCODE_STRING (n_s, (char*)(file+nOffset));
      nOffset += n_s;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_MM::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_MM], objID);
      dbg += SSS;

   // int n
      SSS.Format ("n = %d\n", d_n);
      dbg += SSS;

   // string s
      SSS.Format ("s = '%s'\n", d_s.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Test_CRC::OD_Test_CRC (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_CRC;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_Test_CRC::~OD_Test_CRC () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Test_CRC::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_CRC;      break;
         case 2: ka += d_STR;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_CRC::LoadFromFile (identifier objID)
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
         return false;
      }

   // identifier CRC
      d_CRC = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string STR
      size_t n_STR = (*(size_t*)(file+nOffset));  // n_STR = strlen (s_STR)+1;
      nOffset += sizeof(size_t);
      char * s_STR = new char [n_STR];
      memcpy (s_STR, (file+nOffset), n_STR);
      nOffset += n_STR;
      DECODE_STRING (n_STR, s_STR);
      d_STR = s_STR;
      delete [] s_STR;
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_CRC::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier CRC
      n_size += sizeof (identifier);

   // string STR
      n_size += sizeof (size_t);
      n_size += d_STR.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_CRC::WriteToFile (identifier objID)
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

   // string STR
      size_t n_STR = d_STR.length()+1;
      (*(size_t*)(file+nOffset)) = n_STR;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_STR.c_str(), n_STR);
      ENCODE_STRING (n_STR, (char*)(file+nOffset));
      nOffset += n_STR;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_CRC::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_CRC], objID);
      dbg += SSS;

   // identifier CRC
      SSS.Format ("CRC = %d\n", d_CRC);
      dbg += SSS;

   // string STR
      SSS.Format ("STR = '%s'\n", d_STR.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Test_4G::OD_Test_4G (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_4G;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_Test_4G::~OD_Test_4G () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Test_4G::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_i;      break;
         case 2: ka += d_s;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_4G::LoadFromFile (identifier objID)
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
         return false;
      }

   // int i
      d_i = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string s
      size_t n_s = (*(size_t*)(file+nOffset));  // n_s = strlen (s_s)+1;
      nOffset += sizeof(size_t);
      char * s_s = new char [n_s];
      memcpy (s_s, (file+nOffset), n_s);
      nOffset += n_s;
      DECODE_STRING (n_s, s_s);
      d_s = s_s;
      delete [] s_s;
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_4G::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int i
      n_size += sizeof (int);

   // string s
      n_size += sizeof (size_t);
      n_size += d_s.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_4G::WriteToFile (identifier objID)
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

   // int i
      (*(int*)(file+nOffset)) = d_i;
      nOffset += sizeof (int);

   // string s
      size_t n_s = d_s.length()+1;
      (*(size_t*)(file+nOffset)) = n_s;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_s.c_str(), n_s);
      ENCODE_STRING (n_s, (char*)(file+nOffset));
      nOffset += n_s;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_4G::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_4G], objID);
      dbg += SSS;

   // int i
      SSS.Format ("i = %d\n", d_i);
      dbg += SSS;

   // string s
      SSS.Format ("s = '%s'\n", d_s.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Test_sort::OD_Test_sort (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_sort;


      m_CoIndexPtr = new OBD_pointer [12];
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
      if (!bFieldsInit) return;

      d_n1 = 0;
   }

// Деструктор
  OD_Test_sort::~OD_Test_sort () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Test_sort::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_n1;      break;
         case 2: ka += d_n2;      break;
         case 3: ka += d_s1;      break;
         case 4: ka += d_s2;      break;
         case 5: ka += d_f1;      break;
         case 6: ka += d_f2;      break;
         case 7: ka += d_b1;      break;
         case 8: ka += d_b2;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_sort::LoadFromFile (identifier objID)
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
         return false;
      }

   // int n1
      d_n1 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int n2
      d_n2 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string s1
      size_t n_s1 = (*(size_t*)(file+nOffset));  // n_s1 = strlen (s_s1)+1;
      nOffset += sizeof(size_t);
      char * s_s1 = new char [n_s1];
      memcpy (s_s1, (file+nOffset), n_s1);
      nOffset += n_s1;
      DECODE_STRING (n_s1, s_s1);
      d_s1 = s_s1;
      delete [] s_s1;

   // string s2
      size_t n_s2 = (*(size_t*)(file+nOffset));  // n_s2 = strlen (s_s2)+1;
      nOffset += sizeof(size_t);
      char * s_s2 = new char [n_s2];
      memcpy (s_s2, (file+nOffset), n_s2);
      nOffset += n_s2;
      DECODE_STRING (n_s2, s_s2);
      d_s2 = s_s2;
      delete [] s_s2;

   // float f1
      d_f1 = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // float f2
      d_f2 = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // bool b1
      d_b1 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // bool b2
      d_b2 = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_sort::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int n1
      n_size += sizeof (int);

   // int n2
      n_size += sizeof (int);

   // string s1
      n_size += sizeof (size_t);
      n_size += d_s1.length()+1;

   // string s2
      n_size += sizeof (size_t);
      n_size += d_s2.length()+1;

   // float f1
      n_size += sizeof (float);

   // float f2
      n_size += sizeof (float);

   // bool b1
      n_size += sizeof (bool);

   // bool b2
      n_size += sizeof (bool);

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_sort::WriteToFile (identifier objID)
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

   // int n1
      (*(int*)(file+nOffset)) = d_n1;
      nOffset += sizeof (int);

   // int n2
      (*(int*)(file+nOffset)) = d_n2;
      nOffset += sizeof (int);

   // string s1
      size_t n_s1 = d_s1.length()+1;
      (*(size_t*)(file+nOffset)) = n_s1;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_s1.c_str(), n_s1);
      ENCODE_STRING (n_s1, (char*)(file+nOffset));
      nOffset += n_s1;

   // string s2
      size_t n_s2 = d_s2.length()+1;
      (*(size_t*)(file+nOffset)) = n_s2;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_s2.c_str(), n_s2);
      ENCODE_STRING (n_s2, (char*)(file+nOffset));
      nOffset += n_s2;

   // float f1
      (*(float*)(file+nOffset)) = d_f1;
      nOffset += sizeof (float);

   // float f2
      (*(float*)(file+nOffset)) = d_f2;
      nOffset += sizeof (float);

   // bool b1
      (*(bool*)(file+nOffset)) = d_b1;
      nOffset += sizeof (bool);

   // bool b2
      (*(bool*)(file+nOffset)) = d_b2;
      nOffset += sizeof (bool);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_sort::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_sort], objID);
      dbg += SSS;

   // int n1
      SSS.Format ("n1 = %d\n", d_n1);
      dbg += SSS;

   // int n2
      SSS.Format ("n2 = %d\n", d_n2);
      dbg += SSS;

   // string s1
      SSS.Format ("s1 = '%s'\n", d_s1.c_str());
      dbg += SSS;

   // string s2
      SSS.Format ("s2 = '%s'\n", d_s2.c_str());
      dbg += SSS;

   // float f1
      SSS.Format ("f1 = %f\n", d_f1);
      dbg += SSS;

   // float f2
      SSS.Format ("f2 = %f\n", d_f2);
      dbg += SSS;

   // bool b1
      SSS.Format ("b1 = %s\n", d_b1?"true":"false");
      dbg += SSS;

   // bool b2
      SSS.Format ("b2 = %s\n", d_b2?"true":"false");
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
