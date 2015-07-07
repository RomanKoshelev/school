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
// Поле:   identifier Viewer::TagID
   public: CSmartField      <OD_Viewer, identifier >    m_TagID;
// Поле:   int Viewer::TagInt
   public: CSmartField      <OD_Viewer, int        >    m_TagInt;
// Поле:   bool Viewer::TagBool
   public: CSmartField      <OD_Viewer, bool       >    m_TagBool;
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

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [IPAddressHash, Anonymous]
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
// Контроллер объектов базы данных класса "Test_Load"
// 
class OC_Test_Load: public OC_Object <OC_Test_Load>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_Load  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_Load  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_Load  (const OC_Test_Load& from);
// Деструктор контроллера объекта
   public: ~OC_Test_Load ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_Load& operator= (const OC_Test_Load& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_Load& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_Load& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_Load& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_Load& operator << (OC_Test_Load& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_Load& operator >> (OC_Test_Load& from);

// Поле:   int Test_Load::Field
   public: CSmartField      <OD_Test_Load, int        >    m_Field;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Field]
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
// Контроллер объектов базы данных класса "jerom_table"
// 
class OC_jerom_table: public OC_Object <OC_jerom_table>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_jerom_table  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_jerom_table  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_jerom_table  (const OC_jerom_table& from);
// Деструктор контроллера объекта
   public: ~OC_jerom_table ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_jerom_table& operator= (const OC_jerom_table& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_jerom_table& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_jerom_table& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_jerom_table& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_jerom_table& operator << (OC_jerom_table& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_jerom_table& operator >> (OC_jerom_table& from);

// Поле:   int jerom_table::OperatorID
   public: CSmartField      <OD_jerom_table, int        >    m_OperatorID;
// Поле:   int jerom_table::MessageDate
   public: CSmartField      <OD_jerom_table, int        >    m_MessageDate;
// Поле:   string jerom_table::Message
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
// Контроллер объектов базы данных класса "tsmc_table"
// 
class OC_tsmc_table: public OC_Object <OC_tsmc_table>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_tsmc_table  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_tsmc_table  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_tsmc_table  (const OC_tsmc_table& from);
// Деструктор контроллера объекта
   public: ~OC_tsmc_table ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_tsmc_table& operator= (const OC_tsmc_table& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_tsmc_table& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_tsmc_table& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_tsmc_table& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_tsmc_table& operator << (OC_tsmc_table& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_tsmc_table& operator >> (OC_tsmc_table& from);

// Поле:   int tsmc_table::Int_Field
   public: CSmartField      <OD_tsmc_table, int        >    m_Int_Field;
// Поле:   float tsmc_table::Float_Field
   public: CSmartField      <OD_tsmc_table, float      >    m_Float_Field;
// Поле:   string tsmc_table::Text_Field
   public: CSmartField      <OD_tsmc_table, string     >    m_Text_Field;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Float_Field]
   public: void SetIndex_Float_Field ();
// Установить текущий индекс по полю [Text_Field]
   public: void SetIndex_Text_Field ();
// Установить текущий индекс по набору полей [Int_Field, Float_Field, Text_Field]
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
// Контроллер объектов базы данных класса "Test_MM"
// 
class OC_Test_MM: public OC_Object <OC_Test_MM>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_MM  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_MM  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_MM  (const OC_Test_MM& from);
// Деструктор контроллера объекта
   public: ~OC_Test_MM ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_MM& operator= (const OC_Test_MM& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_MM& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_MM& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_MM& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_MM& operator << (OC_Test_MM& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_MM& operator >> (OC_Test_MM& from);

// Поле:   int Test_MM::n
   public: CSmartField      <OD_Test_MM, int        >    m_n;
// Поле:   string Test_MM::s
   public: CSmartField      <OD_Test_MM, string     >    m_s;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [n, s]
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
// Контроллер объектов базы данных класса "Test_CRC"
// 
class OC_Test_CRC: public OC_Object <OC_Test_CRC>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_CRC  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_CRC  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_CRC  (const OC_Test_CRC& from);
// Деструктор контроллера объекта
   public: ~OC_Test_CRC ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_CRC& operator= (const OC_Test_CRC& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_CRC& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_CRC& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_CRC& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_CRC& operator << (OC_Test_CRC& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_CRC& operator >> (OC_Test_CRC& from);

// Поле:   identifier Test_CRC::CRC
   public: CSmartField      <OD_Test_CRC, identifier >    m_CRC;
// Поле:   string Test_CRC::STR
   public: CSmartField      <OD_Test_CRC, string     >    m_STR;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [CRC]
   public: void SetIndex_CRC ();
// Установить текущий индекс по полю [STR]
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
// Контроллер объектов базы данных класса "Test_4G"
// 
class OC_Test_4G: public OC_Object <OC_Test_4G>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_4G  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_4G  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_4G  (const OC_Test_4G& from);
// Деструктор контроллера объекта
   public: ~OC_Test_4G ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_4G& operator= (const OC_Test_4G& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_4G& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_4G& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_4G& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_4G& operator << (OC_Test_4G& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_4G& operator >> (OC_Test_4G& from);

// Поле:   int Test_4G::i
   public: CSmartField      <OD_Test_4G, int        >    m_i;
// Поле:   string Test_4G::s
   public: CSmartField      <OD_Test_4G, string     >    m_s;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [i]
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
// Контроллер объектов базы данных класса "Test_sort"
// 
class OC_Test_sort: public OC_Object <OC_Test_sort>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_sort  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_sort  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_sort  (const OC_Test_sort& from);
// Деструктор контроллера объекта
   public: ~OC_Test_sort ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_sort& operator= (const OC_Test_sort& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_sort& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_sort& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_sort& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_sort& operator << (OC_Test_sort& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_sort& operator >> (OC_Test_sort& from);

// Поле:   int Test_sort::n1
   public: CSmartField      <OD_Test_sort, int        >    m_n1;
// Поле:   int Test_sort::n2
   public: CSmartField      <OD_Test_sort, int        >    m_n2;
// Поле:   string Test_sort::s1
   public: CSmartField      <OD_Test_sort, string     >    m_s1;
// Поле:   string Test_sort::s2
   public: CSmartField      <OD_Test_sort, string     >    m_s2;
// Поле:   float Test_sort::f1
   public: CSmartField      <OD_Test_sort, float      >    m_f1;
// Поле:   float Test_sort::f2
   public: CSmartField      <OD_Test_sort, float      >    m_f2;
// Поле:   bool Test_sort::b1
   public: CSmartField      <OD_Test_sort, bool       >    m_b1;
// Поле:   bool Test_sort::b2
   public: CSmartField      <OD_Test_sort, bool       >    m_b2;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [n1]
   public: void SetIndex_n1 ();
// Установить текущий индекс по полю [-n1]
   public: void SetIndex__n1 ();
// Установить текущий индекс по полю [s1]
   public: void SetIndex_s1 ();
// Установить текущий индекс по полю [-s1]
   public: void SetIndex__s1 ();
// Установить текущий индекс по набору полей [n1, -f1]
   public: void SetIndex_n1__f1 ();
// Установить текущий индекс по набору полей [-f1, f2]
   public: void SetIndex__f1_f2 ();
// Установить текущий индекс по набору полей [s1, s2]
   public: void SetIndex_s1_s2 ();
// Установить текущий индекс по набору полей [-s1, s2]
   public: void SetIndex__s1_s2 ();
// Установить текущий индекс по набору полей [s1, -s2]
   public: void SetIndex_s1__s2 ();
// Установить текущий индекс по набору полей [-s1, -s2]
   public: void SetIndex__s1__s2 ();
// Установить текущий индекс по набору полей [f1, s1, n2]
   public: void SetIndex_f1_s1_n2 ();
// Установить текущий индекс по набору полей [b1, -s1, n2]
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
