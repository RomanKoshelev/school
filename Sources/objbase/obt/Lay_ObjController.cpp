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
   m_Name._init                   (classID, 1, &coPtr, &OD_Viewer::d_Name                   );
   m_Email._init                  (classID, 2, &coPtr, &OD_Viewer::d_Email                  );
   m_UserAgent._init              (classID, 3, &coPtr, &OD_Viewer::d_UserAgent              );
   m_Anonymous._init              (classID, 4, &coPtr, &OD_Viewer::d_Anonymous              );
   m_TotalShows._init             (classID, 5, &coPtr, &OD_Viewer::d_TotalShows             );
   m_TotalClicks._init            (classID, 6, &coPtr, &OD_Viewer::d_TotalClicks            );
   m_IPAddress._init              (classID, 7, &coPtr, &OD_Viewer::d_IPAddress              );
   m_Referrer._init               (classID, 8, &coPtr, &OD_Viewer::d_Referrer               );
   m_IPAddressHash._init          (classID, 9, &coPtr, &OD_Viewer::d_IPAddressHash          );
   m_CRA_Site._init               (classID, 10, &coPtr, &OD_Viewer::d_CRA_Site               );
   m_CRN_Site._init               (classID, 11, &coPtr, &OD_Viewer::d_CRN_Site               );
   m_CRN_Site_Update._init        (classID, 12, &coPtr, &OD_Viewer::d_CRN_Site_Update        );
   m_CRA_Click._init              (classID, 13, &coPtr, &OD_Viewer::d_CRA_Click              );
   m_CRN_Click._init              (classID, 14, &coPtr, &OD_Viewer::d_CRN_Click              );
   m_Group._init                  (classID, 15, &coPtr, &OD_Viewer::d_Group                  );
   m_TZOffset._init               (classID, 16, &coPtr, &OD_Viewer::d_TZOffset               );
   m_CreationTime._init           (classID, 17, &coPtr, &OD_Viewer::d_CreationTime           );
   m_LastVisitTime._init          (classID, 18, &coPtr, &OD_Viewer::d_LastVisitTime          );
   m_Site._init                   (classID, 19, &coPtr, &OD_Viewer::d_Site                   );
   m_Site_LastHit._init           (classID, 20, &coPtr, &OD_Viewer::d_Site_LastHit           );
   m_Site_Hits._init              (classID, 21, &coPtr, &OD_Viewer::d_Site_Hits              );
   m_Site_LastHost._init          (classID, 22, &coPtr, &OD_Viewer::d_Site_LastHost          );
   m_Site_Hosts._init             (classID, 23, &coPtr, &OD_Viewer::d_Site_Hosts             );
   m_TotalHosts._init             (classID, 24, &coPtr, &OD_Viewer::d_TotalHosts             );
   m_Site_Votings._init           (classID, 25, &coPtr, &OD_Viewer::d_Site_Votings           );
   m_Site_VoteDayNo._init         (classID, 26, &coPtr, &OD_Viewer::d_Site_VoteDayNo         );
   m_CRA_Inquiry._init            (classID, 27, &coPtr, &OD_Viewer::d_CRA_Inquiry            );
   m_CRN_Inquiry._init            (classID, 28, &coPtr, &OD_Viewer::d_CRN_Inquiry            );
   m_Site_SessionLastSiteID._init (classID, 29, &coPtr, &OD_Viewer::d_Site_SessionLastSiteID );
   m_Banner._init                 (classID, 30, &coPtr, &OD_Viewer::d_Banner                 );
   m_Banner_LastViewed._init      (classID, 31, &coPtr, &OD_Viewer::d_Banner_LastViewed      );
   m_Banner_ShowClick._init       (classID, 32, &coPtr, &OD_Viewer::d_Banner_ShowClick       );
   m_BannerClickTime._init        (classID, 33, &coPtr, &OD_Viewer::d_BannerClickTime        );
   m_BannerClickID._init          (classID, 34, &coPtr, &OD_Viewer::d_BannerClickID          );
   m_BannerClickSiteID._init      (classID, 35, &coPtr, &OD_Viewer::d_BannerClickSiteID      );
   m_BannerClickHitCount._init    (classID, 36, &coPtr, &OD_Viewer::d_BannerClickHitCount    );
   m_BannerClickSessionTime._init (classID, 37, &coPtr, &OD_Viewer::d_BannerClickSessionTime );
   m_TagID._init                  (classID, 38, &coPtr, &OD_Viewer::d_TagID                  );
   m_TagInt._init                 (classID, 39, &coPtr, &OD_Viewer::d_TagInt                 );
   m_TagBool._init                (classID, 40, &coPtr, &OD_Viewer::d_TagBool                );
   m_ReservedID._init             (classID, 41, &coPtr, &OD_Viewer::d_ReservedID             );
   m_ReservedInt._init            (classID, 42, &coPtr, &OD_Viewer::d_ReservedInt            );
   m_ReservedString._init         (classID, 43, &coPtr, &OD_Viewer::d_ReservedString         );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Viewer::CopyDataFrom (OC_Viewer& from)
{
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
   m_TagID                  = from.m_TagID;
   m_TagInt                 = from.m_TagInt;
   m_TagBool                = from.m_TagBool;
   m_ReservedID             = from.m_ReservedID;
   m_ReservedInt            = from.m_ReservedInt;
   m_ReservedString         = from.m_ReservedString;
}


// Копирование данных в другой контроллер
void OC_Viewer::CopyDataTo (OC_Viewer& to)
{
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
   to.m_TagID                  = m_TagID;
   to.m_TagInt                 = m_TagInt;
   to.m_TagBool                = m_TagBool;
   to.m_ReservedID             = m_ReservedID;
   to.m_ReservedInt            = m_ReservedInt;
   to.m_ReservedString         = m_ReservedString;
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

// Установить текущий индекс по его идентификатору
identifier OC_Viewer::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_IPAddressHash_Anonymous ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Viewer::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_Viewer::SetIndex_IPAddressHash_Anonymous ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Test_Load

// Конструктор по умолчанию
OC_Test_Load::OC_Test_Load ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Test_Load::OC_Test_Load  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Test_Load::OC_Test_Load  (const OC_Test_Load& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Test_Load::~OC_Test_Load ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Test_Load& OC_Test_Load::operator= (const OC_Test_Load& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_Load& OC_Test_Load::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Test_Load::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_Load;
   m_Field._init (classID, 1, &coPtr, &OD_Test_Load::d_Field );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Test_Load::CopyDataFrom (OC_Test_Load& from)
{
   m_Field = from.m_Field;
}


// Копирование данных в другой контроллер
void OC_Test_Load::CopyDataTo (OC_Test_Load& to)
{
   to.m_Field = m_Field;
}

// Копирование данных из другого контроллера: to << from;
OC_Test_Load&  OC_Test_Load::operator << (OC_Test_Load& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Test_Load&  OC_Test_Load::operator >> (OC_Test_Load& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Test_Load::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Field ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Test_Load::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Test_Load::SetIndex_Field ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// jerom_table

// Конструктор по умолчанию
OC_jerom_table::OC_jerom_table ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_jerom_table::OC_jerom_table  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_jerom_table::OC_jerom_table  (const OC_jerom_table& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_jerom_table::~OC_jerom_table ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_jerom_table& OC_jerom_table::operator= (const OC_jerom_table& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_jerom_table& OC_jerom_table::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_jerom_table::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_jerom_table;
   m_OperatorID._init  (classID, 1, &coPtr, &OD_jerom_table::d_OperatorID  );
   m_MessageDate._init (classID, 2, &coPtr, &OD_jerom_table::d_MessageDate );
   m_Message._init     (classID, 3, &coPtr, &OD_jerom_table::d_Message     );
}


// Копирование данных из другого контроллера
void OC_jerom_table::CopyDataFrom (OC_jerom_table& from)
{
   m_OperatorID  = from.m_OperatorID;
   m_MessageDate = from.m_MessageDate;
   m_Message     = from.m_Message;
}


// Копирование данных в другой контроллер
void OC_jerom_table::CopyDataTo (OC_jerom_table& to)
{
   to.m_OperatorID  = m_OperatorID;
   to.m_MessageDate = m_MessageDate;
   to.m_Message     = m_Message;
}

// Копирование данных из другого контроллера: to << from;
OC_jerom_table&  OC_jerom_table::operator << (OC_jerom_table& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_jerom_table&  OC_jerom_table::operator >> (OC_jerom_table& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// tsmc_table

// Конструктор по умолчанию
OC_tsmc_table::OC_tsmc_table ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_tsmc_table::OC_tsmc_table  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_tsmc_table::OC_tsmc_table  (const OC_tsmc_table& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_tsmc_table::~OC_tsmc_table ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_tsmc_table& OC_tsmc_table::operator= (const OC_tsmc_table& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_tsmc_table& OC_tsmc_table::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_tsmc_table::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_tsmc_table;
   m_Int_Field._init   (classID, 1, &coPtr, &OD_tsmc_table::d_Int_Field   );
   m_Float_Field._init (classID, 2, &coPtr, &OD_tsmc_table::d_Float_Field );
   m_Text_Field._init  (classID, 3, &coPtr, &OD_tsmc_table::d_Text_Field  );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_tsmc_table::CopyDataFrom (OC_tsmc_table& from)
{
   m_Int_Field   = from.m_Int_Field;
   m_Float_Field = from.m_Float_Field;
   m_Text_Field  = from.m_Text_Field;
}


// Копирование данных в другой контроллер
void OC_tsmc_table::CopyDataTo (OC_tsmc_table& to)
{
   to.m_Int_Field   = m_Int_Field;
   to.m_Float_Field = m_Float_Field;
   to.m_Text_Field  = m_Text_Field;
}

// Копирование данных из другого контроллера: to << from;
OC_tsmc_table&  OC_tsmc_table::operator << (OC_tsmc_table& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_tsmc_table&  OC_tsmc_table::operator >> (OC_tsmc_table& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_tsmc_table::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Float_Field ();
              return oldIndex;
      case 1: SetIndex_Text_Field ();
              return oldIndex;
      case 2: SetIndex_Int_Field_Float_Field_Text_Field ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_tsmc_table::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_tsmc_table::SetIndex_Float_Field ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_tsmc_table::SetIndex_Text_Field ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_tsmc_table::SetIndex_Int_Field_Float_Field_Text_Field ()
{
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
   curIndexInfo.m_keyType[1] = (byte)FT_float; 
   curIndexInfo.m_keyType[2] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Test_MM

// Конструктор по умолчанию
OC_Test_MM::OC_Test_MM ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Test_MM::OC_Test_MM  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Test_MM::OC_Test_MM  (const OC_Test_MM& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Test_MM::~OC_Test_MM ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Test_MM& OC_Test_MM::operator= (const OC_Test_MM& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_MM& OC_Test_MM::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Test_MM::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_MM;
   m_n._init (classID, 1, &coPtr, &OD_Test_MM::d_n );
   m_s._init (classID, 2, &coPtr, &OD_Test_MM::d_s );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Test_MM::CopyDataFrom (OC_Test_MM& from)
{
   m_n = from.m_n;
   m_s = from.m_s;
}


// Копирование данных в другой контроллер
void OC_Test_MM::CopyDataTo (OC_Test_MM& to)
{
   to.m_n = m_n;
   to.m_s = m_s;
}

// Копирование данных из другого контроллера: to << from;
OC_Test_MM&  OC_Test_MM::operator << (OC_Test_MM& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Test_MM&  OC_Test_MM::operator >> (OC_Test_MM& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Test_MM::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_n_s ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Test_MM::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_Test_MM::SetIndex_n_s ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Test_CRC

// Конструктор по умолчанию
OC_Test_CRC::OC_Test_CRC ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Test_CRC::OC_Test_CRC  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Test_CRC::OC_Test_CRC  (const OC_Test_CRC& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Test_CRC::~OC_Test_CRC ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Test_CRC& OC_Test_CRC::operator= (const OC_Test_CRC& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_CRC& OC_Test_CRC::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Test_CRC::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_CRC;
   m_CRC._init (classID, 1, &coPtr, &OD_Test_CRC::d_CRC );
   m_STR._init (classID, 2, &coPtr, &OD_Test_CRC::d_STR );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Test_CRC::CopyDataFrom (OC_Test_CRC& from)
{
   m_CRC = from.m_CRC;
   m_STR = from.m_STR;
}


// Копирование данных в другой контроллер
void OC_Test_CRC::CopyDataTo (OC_Test_CRC& to)
{
   to.m_CRC = m_CRC;
   to.m_STR = m_STR;
}

// Копирование данных из другого контроллера: to << from;
OC_Test_CRC&  OC_Test_CRC::operator << (OC_Test_CRC& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Test_CRC&  OC_Test_CRC::operator >> (OC_Test_CRC& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Test_CRC::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_CRC ();
              return oldIndex;
      case 1: SetIndex_STR ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Test_CRC::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Test_CRC::SetIndex_CRC ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
};

// Установить текущий индекс по полю
void OC_Test_CRC::SetIndex_STR ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Test_4G

// Конструктор по умолчанию
OC_Test_4G::OC_Test_4G ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Test_4G::OC_Test_4G  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Test_4G::OC_Test_4G  (const OC_Test_4G& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Test_4G::~OC_Test_4G ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Test_4G& OC_Test_4G::operator= (const OC_Test_4G& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_4G& OC_Test_4G::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Test_4G::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_4G;
   m_i._init (classID, 1, &coPtr, &OD_Test_4G::d_i );
   m_s._init (classID, 2, &coPtr, &OD_Test_4G::d_s );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Test_4G::CopyDataFrom (OC_Test_4G& from)
{
   m_i = from.m_i;
   m_s = from.m_s;
}


// Копирование данных в другой контроллер
void OC_Test_4G::CopyDataTo (OC_Test_4G& to)
{
   to.m_i = m_i;
   to.m_s = m_s;
}

// Копирование данных из другого контроллера: to << from;
OC_Test_4G&  OC_Test_4G::operator << (OC_Test_4G& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Test_4G&  OC_Test_4G::operator >> (OC_Test_4G& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Test_4G::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_i ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Test_4G::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Test_4G::SetIndex_i ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Test_sort

// Конструктор по умолчанию
OC_Test_sort::OC_Test_sort ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Test_sort::OC_Test_sort  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Test_sort::OC_Test_sort  (const OC_Test_sort& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Test_sort::~OC_Test_sort ()
{
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Test_sort& OC_Test_sort::operator= (const OC_Test_sort& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_sort& OC_Test_sort::operator= (identifier objID)
{
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Test_sort::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_sort;
   m_n1._init (classID, 1, &coPtr, &OD_Test_sort::d_n1 );
   m_n2._init (classID, 2, &coPtr, &OD_Test_sort::d_n2 );
   m_s1._init (classID, 3, &coPtr, &OD_Test_sort::d_s1 );
   m_s2._init (classID, 4, &coPtr, &OD_Test_sort::d_s2 );
   m_f1._init (classID, 5, &coPtr, &OD_Test_sort::d_f1 );
   m_f2._init (classID, 6, &coPtr, &OD_Test_sort::d_f2 );
   m_b1._init (classID, 7, &coPtr, &OD_Test_sort::d_b1 );
   m_b2._init (classID, 8, &coPtr, &OD_Test_sort::d_b2 );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Test_sort::CopyDataFrom (OC_Test_sort& from)
{
   m_n1 = from.m_n1;
   m_n2 = from.m_n2;
   m_s1 = from.m_s1;
   m_s2 = from.m_s2;
   m_f1 = from.m_f1;
   m_f2 = from.m_f2;
   m_b1 = from.m_b1;
   m_b2 = from.m_b2;
}


// Копирование данных в другой контроллер
void OC_Test_sort::CopyDataTo (OC_Test_sort& to)
{
   to.m_n1 = m_n1;
   to.m_n2 = m_n2;
   to.m_s1 = m_s1;
   to.m_s2 = m_s2;
   to.m_f1 = m_f1;
   to.m_f2 = m_f2;
   to.m_b1 = m_b1;
   to.m_b2 = m_b2;
}

// Копирование данных из другого контроллера: to << from;
OC_Test_sort&  OC_Test_sort::operator << (OC_Test_sort& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Test_sort&  OC_Test_sort::operator >> (OC_Test_sort& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Test_sort::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_n1 ();
              return oldIndex;
      case 1: SetIndex__n1 ();
              return oldIndex;
      case 2: SetIndex_s1 ();
              return oldIndex;
      case 3: SetIndex__s1 ();
              return oldIndex;
      case 4: SetIndex_n1__f1 ();
              return oldIndex;
      case 5: SetIndex__f1_f2 ();
              return oldIndex;
      case 6: SetIndex_s1_s2 ();
              return oldIndex;
      case 7: SetIndex__s1_s2 ();
              return oldIndex;
      case 8: SetIndex_s1__s2 ();
              return oldIndex;
      case 9: SetIndex__s1__s2 ();
              return oldIndex;
      case 10: SetIndex_f1_s1_n2 ();
              return oldIndex;
      case 11: SetIndex_b1__s1_n2 ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Test_sort::GetIndex ()
{
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Test_sort::SetIndex_n1 ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Test_sort::SetIndex__n1 ()
{
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Test_sort::SetIndex_s1 ()
{
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_Test_sort::SetIndex__s1 ()
{
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex_n1__f1 ()
{
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
   curIndexInfo.m_keyType[1] = (byte)FT_float; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex__f1_f2 ()
{
   curIndexInfo.m_id         = 5; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
   curIndexInfo.m_keyType[1] = (byte)FT_float; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex_s1_s2 ()
{
   curIndexInfo.m_id         = 6; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex__s1_s2 ()
{
   curIndexInfo.m_id         = 7; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex_s1__s2 ()
{
   curIndexInfo.m_id         = 8; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex__s1__s2 ()
{
   curIndexInfo.m_id         = 9; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex_f1_s1_n2 ()
{
   curIndexInfo.m_id         = 10; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
   curIndexInfo.m_keyType[2] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Test_sort::SetIndex_b1__s1_n2 ()
{
   curIndexInfo.m_id         = 11; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_bool; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
   curIndexInfo.m_keyType[2] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
