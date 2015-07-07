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


#include "./../../kernel/main.h"
#include "./../../kernel/OBD.h"
#include "./../../kernel/Object.h"
#include "Lay_ObjData.h"








#ifdef  USES_OC_ALL
#define USES_OC_Registry
#endif
#ifdef USES_OC_Registry
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Registry"
// 
class OC_Registry: public OC_Object
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

// Поле:   bool Registry::NeedInitiate
   public: CSmartField      <OD_Registry, bool           >    m_NeedInitiate;
// Поле:   identifier Registry::ConceptID_Sorted []
   public: CSmartFieldArray <OD_Registry, identifier     >    m_ConceptID_Sorted;
// Поле:   int Registry::ConceptNo_SortID []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptNo_SortID;
// Поле:   identifier Registry::ConceptID_SortNo []
   public: CSmartFieldArray <OD_Registry, identifier     >    m_ConceptID_SortNo;
// Поле:   int Registry::ConceptParent_SortNo []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptParent_SortNo;
// Поле:   int Registry::ConceptType_SortNo []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptType_SortNo;
// Поле:   int Registry::ConceptLevel_SortNo []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptLevel_SortNo;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Relation
#endif
#ifdef USES_OC_Relation
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Relation"
// 
class OC_Relation: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Relation  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Relation  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Relation  (const OC_Relation& from);
// Деструктор контроллера объекта
   public: ~OC_Relation ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Relation& operator= (const OC_Relation& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Relation& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Relation& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Relation& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Relation& operator << (OC_Relation& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Relation& operator >> (OC_Relation& from);

// Поле:   string Relation::SysName
   public: CSmartField      <OD_Relation, string         >    m_SysName;
// Поле:   string Relation::Name
   public: CSmartField      <OD_Relation, string         >    m_Name;
// Поле:   string Relation::Description
   public: CSmartField      <OD_Relation, string         >    m_Description;
// Поле:   int Relation::CreationTime
   public: CSmartField      <OD_Relation, int            >    m_CreationTime;
// Поле:   int Relation::Version
   public: CSmartField      <OD_Relation, int            >    m_Version;
// Поле:   guid Relation::OwnerGUID
   public: CSmartField      <OD_Relation, guid           >    m_OwnerGUID;
// Поле:   int Relation::AccessLevelThreshold
   public: CSmartField      <OD_Relation, int            >    m_AccessLevelThreshold;
// Поле:   string Relation::FieldName []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldName;
// Поле:   string Relation::FieldType []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldType;
// Поле:   string Relation::FieldSysName []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldSysName;
// Поле:   string Relation::FieldDescription []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldDescription;
// Поле:   string Relation::FieldInterfaceType []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldInterfaceType;
// Поле:   guid Relation::FeodGUID []
   public: CSmartFieldArray <OD_Relation, guid           >    m_FeodGUID;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по полю [SysName]
   public: void SetIndex_SysName ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Linkage
#endif
#ifdef USES_OC_Linkage
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Linkage"
// 
class OC_Linkage: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Linkage  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Linkage  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Linkage  (const OC_Linkage& from);
// Деструктор контроллера объекта
   public: ~OC_Linkage ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Linkage& operator= (const OC_Linkage& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Linkage& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Linkage& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Linkage& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Linkage& operator << (OC_Linkage& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Linkage& operator >> (OC_Linkage& from);

// Поле:   int Linkage::CreationTime
   public: CSmartField      <OD_Linkage, int            >    m_CreationTime;
// Поле:   identifier Linkage::RelationID
   public: CSmartField      <OD_Linkage, identifier     >    m_RelationID;
// Поле:   guid Linkage::OwnerGUID
   public: CSmartField      <OD_Linkage, guid           >    m_OwnerGUID;
// Поле:   int Linkage::AccessLevelThreshold
   public: CSmartField      <OD_Linkage, int            >    m_AccessLevelThreshold;
// Поле:   identifier Linkage::ProxyID []
   public: CSmartFieldArray <OD_Linkage, identifier     >    m_ProxyID;
// Поле:   string Linkage::Value []
   public: CSmartFieldArray <OD_Linkage, string         >    m_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [RelationID]
   public: void SetIndex_RelationID ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_LinkProxy
#endif
#ifdef USES_OC_LinkProxy
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "LinkProxy"
// 
class OC_LinkProxy: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_LinkProxy  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_LinkProxy  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_LinkProxy  (const OC_LinkProxy& from);
// Деструктор контроллера объекта
   public: ~OC_LinkProxy ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_LinkProxy& operator= (const OC_LinkProxy& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_LinkProxy& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_LinkProxy& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_LinkProxy& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_LinkProxy& operator << (OC_LinkProxy& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_LinkProxy& operator >> (OC_LinkProxy& from);

// Поле:   int LinkProxy::CreationTime
   public: CSmartField      <OD_LinkProxy, int            >    m_CreationTime;
// Поле:   guid LinkProxy::RealObject
   public: CSmartField      <OD_LinkProxy, guid           >    m_RealObject;
// Поле:   identifier LinkProxy::LinkageID []
   public: CSmartFieldArray <OD_LinkProxy, identifier     >    m_LinkageID;
// Поле:   identifier LinkProxy::RelationID []
   public: CSmartFieldArray <OD_LinkProxy, identifier     >    m_RelationID;
// Поле:   int LinkProxy::RelationField []
   public: CSmartFieldArray <OD_LinkProxy, int            >    m_RelationField;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Connectable
#endif
#ifdef USES_OC_Connectable
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Connectable"
// 
class OC_Connectable: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Connectable  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Connectable  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Connectable  (const OC_Connectable& from);
// Деструктор контроллера объекта
   public: ~OC_Connectable ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Connectable& operator= (const OC_Connectable& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Connectable& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Connectable& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Connectable& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Connectable& operator << (OC_Connectable& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Connectable& operator >> (OC_Connectable& from);

// Поле:   guid Connectable::ProxyObject
   public: CSmartField      <OD_Connectable, guid           >    m_ProxyObject;
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_MetaObject
#endif
#ifdef USES_OC_MetaObject
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "MetaObject"
// 
class OC_MetaObject: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_MetaObject  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_MetaObject  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_MetaObject  (const OC_MetaObject& from);
// Деструктор контроллера объекта
   public: ~OC_MetaObject ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_MetaObject& operator= (const OC_MetaObject& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_MetaObject& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_MetaObject& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_MetaObject& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_MetaObject& operator << (OC_MetaObject& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_MetaObject& operator >> (OC_MetaObject& from);

// Поле:   string MetaObject::Type
   public: CSmartField      <OD_MetaObject, string         >    m_Type;
// Поле:   string MetaObject::Name
   public: CSmartField      <OD_MetaObject, string         >    m_Name;
// Поле:   string MetaObject::SysName
   public: CSmartField      <OD_MetaObject, string         >    m_SysName;
// Поле:   string MetaObject::Header1
   public: CSmartField      <OD_MetaObject, string         >    m_Header1;
// Поле:   string MetaObject::Header2
   public: CSmartField      <OD_MetaObject, string         >    m_Header2;
// Поле:   string MetaObject::Header3
   public: CSmartField      <OD_MetaObject, string         >    m_Header3;
// Поле:   string MetaObject::Header4
   public: CSmartField      <OD_MetaObject, string         >    m_Header4;
// Поле:   string MetaObject::Header5
   public: CSmartField      <OD_MetaObject, string         >    m_Header5;
// Поле:   string MetaObject::Comment
   public: CSmartField      <OD_MetaObject, string         >    m_Comment;
// Поле:   string MetaObject::Text
   public: CSmartField      <OD_MetaObject, string         >    m_Text;
// Поле:   int MetaObject::CreationTime
   public: CSmartField      <OD_MetaObject, int            >    m_CreationTime;
// Поле:   guid MetaObject::OwnerGUID
   public: CSmartField      <OD_MetaObject, guid           >    m_OwnerGUID;
// Поле:   int MetaObject::AccessLevelThreshold
   public: CSmartField      <OD_MetaObject, int            >    m_AccessLevelThreshold;
// Поле:   guid MetaObject::ProxyObject
   public: CSmartField      <OD_MetaObject, guid           >    m_ProxyObject;
// Поле:   guid MetaObject::MOD_Base_GUID
   public: CSmartField      <OD_MetaObject, guid           >    m_MOD_Base_GUID;
// Поле:   guid MetaObject::MOD_Extension_GUID
   public: CSmartField      <OD_MetaObject, guid           >    m_MOD_Extension_GUID;
// Поле:   int MetaObject::arrInt []
   public: CSmartFieldArray <OD_MetaObject, int            >    m_arrInt;
// Поле:   float MetaObject::arrFloat []
   public: CSmartFieldArray <OD_MetaObject, float          >    m_arrFloat;
// Поле:   bool MetaObject::arrBool []
   public: CSmartFieldArray <OD_MetaObject, bool           >    m_arrBool;
// Поле:   byte MetaObject::arrByte []
   public: CSmartFieldArray <OD_MetaObject, byte           >    m_arrByte;
// Поле:   int MetaObject::arrTime []
   public: CSmartFieldArray <OD_MetaObject, int            >    m_arrTime;
// Поле:   string MetaObject::arrString []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_arrString;
// Поле:   guid MetaObject::arrGUID []
   public: CSmartFieldArray <OD_MetaObject, guid           >    m_arrGUID;
// Поле:   identifier MetaObject::arrID []
   public: CSmartFieldArray <OD_MetaObject, identifier     >    m_arrID;
// Поле:   guid MetaObject::FeodGUID []
   public: CSmartFieldArray <OD_MetaObject, guid           >    m_FeodGUID;
// Поле:   string MetaObject::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_FIELD_Extension_Name;
// Поле:   string MetaObject::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [Type, Name]
   public: void SetIndex_Type_Name ();
// Установить текущий индекс по набору полей [Type, SysName]
   public: void SetIndex_Type_SysName ();
// Установить текущий индекс по набору полей [Type, Header1, Header2, Header3, Header4, Header5]
   public: void SetIndex_Type_Header1_Header2_Header3_Header4_Header5 ();
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
class OC_Concept: public OC_Object
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

// Поле:   string Concept::Name
   public: CSmartField      <OD_Concept, string         >    m_Name;
// Поле:   string Concept::Description
   public: CSmartField      <OD_Concept, string         >    m_Description;
// Поле:   string Concept::Type
   public: CSmartField      <OD_Concept, string         >    m_Type;
// Поле:   int Concept::TypeNo
   public: CSmartField      <OD_Concept, int            >    m_TypeNo;
// Поле:   identifier Concept::Parent
   public: CSmartField      <OD_Concept, identifier     >    m_Parent;
// Поле:   int Concept::Level
   public: CSmartField      <OD_Concept, int            >    m_Level;
// Поле:   int Concept::No
   public: CSmartField      <OD_Concept, int            >    m_No;
// Поле:   guid Concept::MOD_Base_GUID
   public: CSmartField      <OD_Concept, guid           >    m_MOD_Base_GUID;
// Поле:   guid Concept::MOD_Extension_GUID
   public: CSmartField      <OD_Concept, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier Concept::Ancestor []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Ancestor;
// Поле:   int Concept::AncestorNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_AncestorNo;
// Поле:   int Concept::AncestorWeight []
   public: CSmartFieldArray <OD_Concept, int            >    m_AncestorWeight;
// Поле:   identifier Concept::AllAncestor []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_AllAncestor;
// Поле:   identifier Concept::AllAncestorNo []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_AllAncestorNo;
// Поле:   identifier Concept::Child []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Child;
// Поле:   int Concept::ChildNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_ChildNo;
// Поле:   identifier Concept::Descendant []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Descendant;
// Поле:   int Concept::DescendantNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_DescendantNo;
// Поле:   string Concept::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_Concept, string         >    m_FIELD_Extension_Name;
// Поле:   string Concept::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_Concept, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по полю [Level]
   public: void SetIndex_Level ();
// Установить текущий индекс по полю [No]
   public: void SetIndex_No ();
// Установить текущий индекс по набору полей [Type, Level]
   public: void SetIndex_Type_Level ();
// Установить текущий индекс по полю [TypeNo]
   public: void SetIndex_TypeNo ();
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
class OC_User: public OC_Object
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
   public: CSmartField      <OD_User, string         >    m_Login;
// Поле:   string User::Password
   public: CSmartField      <OD_User, string         >    m_Password;
// Поле:   bool User::PasswordInBrowser
   public: CSmartField      <OD_User, bool           >    m_PasswordInBrowser;
// Поле:   int User::CreationTime
   public: CSmartField      <OD_User, int            >    m_CreationTime;
// Поле:   string User::FullName
   public: CSmartField      <OD_User, string         >    m_FullName;
// Поле:   string User::Email
   public: CSmartField      <OD_User, string         >    m_Email;
// Поле:   string User::URL
   public: CSmartField      <OD_User, string         >    m_URL;
// Поле:   string User::Data
   public: CSmartField      <OD_User, string         >    m_Data;
// Поле:   int User::AccessLevel
   public: CSmartField      <OD_User, int            >    m_AccessLevel;
// Поле:   guid User::ProxyObject
   public: CSmartField      <OD_User, guid           >    m_ProxyObject;
// Поле:   guid User::MOD_Base_GUID
   public: CSmartField      <OD_User, guid           >    m_MOD_Base_GUID;
// Поле:   guid User::MOD_Extension_GUID
   public: CSmartField      <OD_User, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier User::GroupID []
   public: CSmartFieldArray <OD_User, identifier     >    m_GroupID;
// Поле:   identifier User::OwnFeodID []
   public: CSmartFieldArray <OD_User, identifier     >    m_OwnFeodID;
// Поле:   string User::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_User, string         >    m_FIELD_Extension_Name;
// Поле:   string User::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_User, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Login]
   public: void SetIndex_Login ();
// Установить текущий индекс по полю [FullName]
   public: void SetIndex_FullName ();
// Установить текущий индекс по полю [-CreationTime]
   public: void SetIndex__CreationTime ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_UserGroup
#endif
#ifdef USES_OC_UserGroup
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "UserGroup"
// 
class OC_UserGroup: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_UserGroup  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_UserGroup  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_UserGroup  (const OC_UserGroup& from);
// Деструктор контроллера объекта
   public: ~OC_UserGroup ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_UserGroup& operator= (const OC_UserGroup& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_UserGroup& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_UserGroup& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_UserGroup& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_UserGroup& operator << (OC_UserGroup& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_UserGroup& operator >> (OC_UserGroup& from);

// Поле:   string UserGroup::Name
   public: CSmartField      <OD_UserGroup, string         >    m_Name;
// Поле:   string UserGroup::Type
   public: CSmartField      <OD_UserGroup, string         >    m_Type;
// Поле:   string UserGroup::Description
   public: CSmartField      <OD_UserGroup, string         >    m_Description;
// Поле:   int UserGroup::CreationTime
   public: CSmartField      <OD_UserGroup, int            >    m_CreationTime;
// Поле:   guid UserGroup::OwnerGUID
   public: CSmartField      <OD_UserGroup, guid           >    m_OwnerGUID;
// Поле:   int UserGroup::AccessLevelThreshold
   public: CSmartField      <OD_UserGroup, int            >    m_AccessLevelThreshold;
// Поле:   guid UserGroup::ProxyObject
   public: CSmartField      <OD_UserGroup, guid           >    m_ProxyObject;
// Поле:   guid UserGroup::MOD_Base_GUID
   public: CSmartField      <OD_UserGroup, guid           >    m_MOD_Base_GUID;
// Поле:   guid UserGroup::MOD_Extension_GUID
   public: CSmartField      <OD_UserGroup, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier UserGroup::UserID []
   public: CSmartFieldArray <OD_UserGroup, identifier     >    m_UserID;
// Поле:   identifier UserGroup::Rights_Feod []
   public: CSmartFieldArray <OD_UserGroup, identifier     >    m_Rights_Feod;
// Поле:   string UserGroup::Rights_Attr []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_Rights_Attr;
// Поле:   string UserGroup::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_FIELD_Extension_Name;
// Поле:   string UserGroup::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по полю [Type]
   public: void SetIndex_Type ();
// Установить текущий индекс по полю [CreationTime]
   public: void SetIndex_CreationTime ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_Text
#endif
#ifdef USES_OC_Text
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Text"
// 
class OC_Text: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Text  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Text  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Text  (const OC_Text& from);
// Деструктор контроллера объекта
   public: ~OC_Text ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Text& operator= (const OC_Text& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Text& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Text& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Text& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Text& operator << (OC_Text& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Text& operator >> (OC_Text& from);

// Поле:   string Text::Name
   public: CSmartField      <OD_Text, string         >    m_Name;
// Поле:   string Text::Text
   public: CSmartField      <OD_Text, string         >    m_Text;
// Поле:   int Text::CreationTime
   public: CSmartField      <OD_Text, int            >    m_CreationTime;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_MorphologicRule
#endif
#ifdef USES_OC_MorphologicRule
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "MorphologicRule"
// 
class OC_MorphologicRule: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_MorphologicRule  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_MorphologicRule  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_MorphologicRule  (const OC_MorphologicRule& from);
// Деструктор контроллера объекта
   public: ~OC_MorphologicRule ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_MorphologicRule& operator= (const OC_MorphologicRule& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_MorphologicRule& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_MorphologicRule& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_MorphologicRule& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_MorphologicRule& operator << (OC_MorphologicRule& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_MorphologicRule& operator >> (OC_MorphologicRule& from);

// Поле:   byte MorphologicRule::Attribute
   public: CSmartField      <OD_MorphologicRule, byte           >    m_Attribute;
// Поле:   string MorphologicRule::AffixNormal
   public: CSmartField      <OD_MorphologicRule, string         >    m_AffixNormal;
// Поле:   string MorphologicRule::AffixVariant
   public: CSmartField      <OD_MorphologicRule, string         >    m_AffixVariant;
// Поле:   string MorphologicRule::Comment
   public: CSmartField      <OD_MorphologicRule, string         >    m_Comment;
// Поле:   int MorphologicRule::Number
   public: CSmartField      <OD_MorphologicRule, int            >    m_Number;
// Поле:   int MorphologicRule::MatchCount
   public: CSmartField      <OD_MorphologicRule, int            >    m_MatchCount;
// Поле:   int MorphologicRule::ApplyCount
   public: CSmartField      <OD_MorphologicRule, int            >    m_ApplyCount;
// Поле:   byte MorphologicRule::BaseEnd_Available []
   public: CSmartFieldArray <OD_MorphologicRule, byte           >    m_BaseEnd_Available;
// Поле:   byte MorphologicRule::BaseEnd_Exception []
   public: CSmartFieldArray <OD_MorphologicRule, byte           >    m_BaseEnd_Exception;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [AffixVariant]
   public: void SetIndex_AffixVariant ();
// Установить текущий индекс по набору полей [Attribute, AffixNormal, AffixVariant]
   public: void SetIndex_Attribute_AffixNormal_AffixVariant ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_SearchItem
#endif
#ifdef USES_OC_SearchItem
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "SearchItem"
// 
class OC_SearchItem: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_SearchItem  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_SearchItem  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_SearchItem  (const OC_SearchItem& from);
// Деструктор контроллера объекта
   public: ~OC_SearchItem ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SearchItem& operator= (const OC_SearchItem& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_SearchItem& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_SearchItem& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_SearchItem& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_SearchItem& operator << (OC_SearchItem& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_SearchItem& operator >> (OC_SearchItem& from);

// Поле:   string SearchItem::NormalWord
   public: CSmartField      <OD_SearchItem, string         >    m_NormalWord;
// Поле:   string SearchItem::NormalWordInv
   public: CSmartField      <OD_SearchItem, string         >    m_NormalWordInv;
// Поле:   string SearchItem::Attributes
   public: CSmartField      <OD_SearchItem, string         >    m_Attributes;
// Поле:   bool SearchItem::Hypothesis
   public: CSmartField      <OD_SearchItem, bool           >    m_Hypothesis;
// Поле:   int SearchItem::Text_Number
   public: CSmartField      <OD_SearchItem, int            >    m_Text_Number;
// Поле:   guid SearchItem::Text_ObjectSortedGUID []
   public: CSmartFieldArray <OD_SearchItem, guid           >    m_Text_ObjectSortedGUID;
// Поле:   int SearchItem::Text_ModificationTime []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_ModificationTime;
// Поле:   int SearchItem::Text_WordAppearanceNum []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_WordAppearanceNum;
// Поле:   int SearchItem::Text_WordFirstPosition []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_WordFirstPosition;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [NormalWord, Hypothesis]
   public: void SetIndex_NormalWord_Hypothesis ();
// Установить текущий индекс по полю [NormalWordInv]
   public: void SetIndex_NormalWordInv ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_StopWord
#endif
#ifdef USES_OC_StopWord
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "StopWord"
// 
class OC_StopWord: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_StopWord  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_StopWord  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_StopWord  (const OC_StopWord& from);
// Деструктор контроллера объекта
   public: ~OC_StopWord ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_StopWord& operator= (const OC_StopWord& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_StopWord& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_StopWord& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_StopWord& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_StopWord& operator << (OC_StopWord& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_StopWord& operator >> (OC_StopWord& from);

// Поле:   string StopWord::Word
   public: CSmartField      <OD_StopWord, string         >    m_Word;

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
#define USES_OC_WordNibbleABC
#endif
#ifdef USES_OC_WordNibbleABC
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "WordNibbleABC"
// 
class OC_WordNibbleABC: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_WordNibbleABC  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_WordNibbleABC  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_WordNibbleABC  (const OC_WordNibbleABC& from);
// Деструктор контроллера объекта
   public: ~OC_WordNibbleABC ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WordNibbleABC& operator= (const OC_WordNibbleABC& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WordNibbleABC& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_WordNibbleABC& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_WordNibbleABC& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_WordNibbleABC& operator << (OC_WordNibbleABC& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_WordNibbleABC& operator >> (OC_WordNibbleABC& from);

// Поле:   string WordNibbleABC::Nibble
   public: CSmartField      <OD_WordNibbleABC, string         >    m_Nibble;
// Поле:   int WordNibbleABC::Num
   public: CSmartField      <OD_WordNibbleABC, int            >    m_Num;
// Поле:   float WordNibbleABC::FreqPerMillion
   public: CSmartField      <OD_WordNibbleABC, float          >    m_FreqPerMillion;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Nibble]
   public: void SetIndex_Nibble ();
// Установить текущий индекс по полю [FreqPerMillion]
   public: void SetIndex_FreqPerMillion ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_WebFolder
#endif
#ifdef USES_OC_WebFolder
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "WebFolder"
// 
class OC_WebFolder: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_WebFolder  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_WebFolder  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_WebFolder  (const OC_WebFolder& from);
// Деструктор контроллера объекта
   public: ~OC_WebFolder ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WebFolder& operator= (const OC_WebFolder& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WebFolder& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_WebFolder& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_WebFolder& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_WebFolder& operator << (OC_WebFolder& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_WebFolder& operator >> (OC_WebFolder& from);

// Поле:   int WebFolder::ShowCount
   public: CSmartField      <OD_WebFolder, int            >    m_ShowCount;
// Поле:   int WebFolder::ClickCount
   public: CSmartField      <OD_WebFolder, int            >    m_ClickCount;
// Поле:   float WebFolder::CTR
   public: CSmartField      <OD_WebFolder, float          >    m_CTR;
// Поле:   int WebFolder::Estimation_Tot
   public: CSmartField      <OD_WebFolder, int            >    m_Estimation_Tot;
// Поле:   int WebFolder::Estimation_Num
   public: CSmartField      <OD_WebFolder, int            >    m_Estimation_Num;
// Поле:   float WebFolder::Estimation
   public: CSmartField      <OD_WebFolder, float          >    m_Estimation;
// Поле:   guid WebFolder::ProxyObject
   public: CSmartField      <OD_WebFolder, guid           >    m_ProxyObject;
// Поле:   guid WebFolder::MOD_Base_GUID
   public: CSmartField      <OD_WebFolder, guid           >    m_MOD_Base_GUID;
// Поле:   guid WebFolder::MOD_Extension_GUID
   public: CSmartField      <OD_WebFolder, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier WebFolder::WebFileSortedID []
   public: CSmartFieldArray <OD_WebFolder, identifier     >    m_WebFileSortedID;
// Поле:   string WebFolder::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_WebFolder, string         >    m_FIELD_Extension_Name;
// Поле:   string WebFolder::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_WebFolder, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [-ShowCount]
   public: void SetIndex__ShowCount ();
// Установить текущий индекс по полю [-ClickCount]
   public: void SetIndex__ClickCount ();
// Установить текущий индекс по полю [-CTR]
   public: void SetIndex__CTR ();
// Установить текущий индекс по полю [-Estimation]
   public: void SetIndex__Estimation ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_WebFile
#endif
#ifdef USES_OC_WebFile
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "WebFile"
// 
class OC_WebFile: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_WebFile  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_WebFile  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_WebFile  (const OC_WebFile& from);
// Деструктор контроллера объекта
   public: ~OC_WebFile ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WebFile& operator= (const OC_WebFile& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_WebFile& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_WebFile& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_WebFile& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_WebFile& operator << (OC_WebFile& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_WebFile& operator >> (OC_WebFile& from);

// Поле:   string WebFile::Name_OSFile
   public: CSmartField      <OD_WebFile, string         >    m_Name_OSFile;
// Поле:   string WebFile::Name_Upload
   public: CSmartField      <OD_WebFile, string         >    m_Name_Upload;
// Поле:   string WebFile::MIMEType
   public: CSmartField      <OD_WebFile, string         >    m_MIMEType;
// Поле:   string WebFile::IconType
   public: CSmartField      <OD_WebFile, string         >    m_IconType;
// Поле:   guid WebFile::OwnerGUID
   public: CSmartField      <OD_WebFile, guid           >    m_OwnerGUID;
// Поле:   int WebFile::AccessLevelThreshold
   public: CSmartField      <OD_WebFile, int            >    m_AccessLevelThreshold;
// Поле:   int WebFile::CreationTime
   public: CSmartField      <OD_WebFile, int            >    m_CreationTime;
// Поле:   int WebFile::ModificationTime
   public: CSmartField      <OD_WebFile, int            >    m_ModificationTime;
// Поле:   int WebFile::LastAccessTime
   public: CSmartField      <OD_WebFile, int            >    m_LastAccessTime;
// Поле:   int WebFile::Version
   public: CSmartField      <OD_WebFile, int            >    m_Version;
// Поле:   int WebFile::ShowCount
   public: CSmartField      <OD_WebFile, int            >    m_ShowCount;
// Поле:   int WebFile::ClickCount
   public: CSmartField      <OD_WebFile, int            >    m_ClickCount;
// Поле:   float WebFile::CTR
   public: CSmartField      <OD_WebFile, float          >    m_CTR;
// Поле:   int WebFile::Estimation_Tot
   public: CSmartField      <OD_WebFile, int            >    m_Estimation_Tot;
// Поле:   int WebFile::Estimation_Num
   public: CSmartField      <OD_WebFile, int            >    m_Estimation_Num;
// Поле:   float WebFile::Estimation
   public: CSmartField      <OD_WebFile, float          >    m_Estimation;
// Поле:   guid WebFile::ProxyObject
   public: CSmartField      <OD_WebFile, guid           >    m_ProxyObject;
// Поле:   guid WebFile::MOD_Base_GUID
   public: CSmartField      <OD_WebFile, guid           >    m_MOD_Base_GUID;
// Поле:   guid WebFile::MOD_Extension_GUID
   public: CSmartField      <OD_WebFile, guid           >    m_MOD_Extension_GUID;
// Поле:   string WebFile::Name
   public: CSmartField      <OD_WebFile, string         >    m_Name;
// Поле:   string WebFile::Description
   public: CSmartField      <OD_WebFile, string         >    m_Description;
// Поле:   string WebFile::Text
   public: CSmartField      <OD_WebFile, string         >    m_Text;
// Поле:   string WebFile::Additional
   public: CSmartField      <OD_WebFile, string         >    m_Additional;
// Поле:   identifier WebFile::WebFolderID []
   public: CSmartFieldArray <OD_WebFile, identifier     >    m_WebFolderID;
// Поле:   byte WebFile::BinaryData []
   public: CSmartFieldArray <OD_WebFile, byte           >    m_BinaryData;
// Поле:   string WebFile::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_WebFile, string         >    m_FIELD_Extension_Name;
// Поле:   string WebFile::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_WebFile, string         >    m_FIELD_Extension_Value;
// Поле:   identifier WebFile::SearchItemID []
   public: CSmartFieldArray <OD_WebFile, identifier     >    m_SearchItemID;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по полю [OwnerGUID]
   public: void SetIndex_OwnerGUID ();
// Установить текущий индекс по полю [-CreationTime]
   public: void SetIndex__CreationTime ();
// Установить текущий индекс по полю [-ModificationTime]
   public: void SetIndex__ModificationTime ();
// Установить текущий индекс по полю [-LastAccessTime]
   public: void SetIndex__LastAccessTime ();
// Установить текущий индекс по полю [-ShowCount]
   public: void SetIndex__ShowCount ();
// Установить текущий индекс по полю [-ClickCount]
   public: void SetIndex__ClickCount ();
// Установить текущий индекс по полю [-CTR]
   public: void SetIndex__CTR ();
// Установить текущий индекс по полю [-Estimation]
   public: void SetIndex__Estimation ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_UserProfile
#endif
#ifdef USES_OC_UserProfile
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "UserProfile"
// 
class OC_UserProfile: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_UserProfile  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_UserProfile  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_UserProfile  (const OC_UserProfile& from);
// Деструктор контроллера объекта
   public: ~OC_UserProfile ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_UserProfile& operator= (const OC_UserProfile& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_UserProfile& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_UserProfile& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_UserProfile& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_UserProfile& operator << (OC_UserProfile& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_UserProfile& operator >> (OC_UserProfile& from);

// Поле:   guid UserProfile::UserGUID
   public: CSmartField      <OD_UserProfile, guid           >    m_UserGUID;
// Поле:   int UserProfile::SeenIO_ShowCount
   public: CSmartField      <OD_UserProfile, int            >    m_SeenIO_ShowCount;
// Поле:   int UserProfile::SeenIO_ClickCount
   public: CSmartField      <OD_UserProfile, int            >    m_SeenIO_ClickCount;
// Поле:   float UserProfile::SeenIO_CTR
   public: CSmartField      <OD_UserProfile, float          >    m_SeenIO_CTR;
// Поле:   int UserProfile::OwnIO_ShowCount
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_ShowCount;
// Поле:   int UserProfile::OwnIO_ClickCount
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_ClickCount;
// Поле:   float UserProfile::OwnIO_CTR
   public: CSmartField      <OD_UserProfile, float          >    m_OwnIO_CTR;
// Поле:   int UserProfile::OwnIO_Estimation_Tot
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_Estimation_Tot;
// Поле:   int UserProfile::OwnIO_Estimation_Num
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_Estimation_Num;
// Поле:   float UserProfile::OwnIO_Estimation
   public: CSmartField      <OD_UserProfile, float          >    m_OwnIO_Estimation;
// Поле:   bool UserProfile::Account_Enable
   public: CSmartField      <OD_UserProfile, bool           >    m_Account_Enable;
// Поле:   float UserProfile::Account_Debit
   public: CSmartField      <OD_UserProfile, float          >    m_Account_Debit;
// Поле:   float UserProfile::Account_Credit
   public: CSmartField      <OD_UserProfile, float          >    m_Account_Credit;
// Поле:   guid UserProfile::RootFolderGUID
   public: CSmartField      <OD_UserProfile, guid           >    m_RootFolderGUID;
// Поле:   guid UserProfile::ProxyObject
   public: CSmartField      <OD_UserProfile, guid           >    m_ProxyObject;
// Поле:   guid UserProfile::MOD_Base_GUID
   public: CSmartField      <OD_UserProfile, guid           >    m_MOD_Base_GUID;
// Поле:   guid UserProfile::MOD_Extension_GUID
   public: CSmartField      <OD_UserProfile, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier UserProfile::InfoDiv_Hide []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_InfoDiv_Hide;
// Поле:   identifier UserProfile::InfoDiv_Show []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_InfoDiv_Show;
// Поле:   string UserProfile::Filter_Name []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Filter_Name;
// Поле:   string UserProfile::Filter_SearchPhrase []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Filter_SearchPhrase;
// Поле:   identifier UserProfile::Filter_FolderID []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_Filter_FolderID;
// Поле:   identifier UserProfile::SeenIO_ID []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_SeenIO_ID;
// Поле:   int UserProfile::SeenIO_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_SeenIO_Time;
// Поле:   byte UserProfile::SeenIO_Estimation []
   public: CSmartFieldArray <OD_UserProfile, byte           >    m_SeenIO_Estimation;
// Поле:   identifier UserProfile::OwnIO []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_OwnIO;
// Поле:   int UserProfile::OwnIO_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_OwnIO_Time;
// Поле:   guid UserProfile::Log_ObjectGUID []
   public: CSmartFieldArray <OD_UserProfile, guid           >    m_Log_ObjectGUID;
// Поле:   int UserProfile::Log_Action []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Log_Action;
// Поле:   int UserProfile::Log_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Log_Time;
// Поле:   int UserProfile::Account_Log_Action []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Account_Log_Action;
// Поле:   float UserProfile::Account_Log_Amount []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Amount;
// Поле:   float UserProfile::Account_Log_Debit []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Debit;
// Поле:   float UserProfile::Account_Log_Credit []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Credit;
// Поле:   int UserProfile::Account_Log_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Account_Log_Time;
// Поле:   string UserProfile::Account_Log_Comment []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Account_Log_Comment;
// Поле:   string UserProfile::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_FIELD_Extension_Name;
// Поле:   string UserProfile::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [-SeenIO_ShowCount]
   public: void SetIndex__SeenIO_ShowCount ();
// Установить текущий индекс по полю [-SeenIO_CTR]
   public: void SetIndex__SeenIO_CTR ();
// Установить текущий индекс по полю [-OwnIO_ShowCount]
   public: void SetIndex__OwnIO_ShowCount ();
// Установить текущий индекс по полю [-OwnIO_CTR]
   public: void SetIndex__OwnIO_CTR ();
// Установить текущий индекс по полю [-OwnIO_Estimation]
   public: void SetIndex__OwnIO_Estimation ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_InfoDiv
#endif
#ifdef USES_OC_InfoDiv
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "InfoDiv"
// 
class OC_InfoDiv: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_InfoDiv  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_InfoDiv  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_InfoDiv  (const OC_InfoDiv& from);
// Деструктор контроллера объекта
   public: ~OC_InfoDiv ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoDiv& operator= (const OC_InfoDiv& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoDiv& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_InfoDiv& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_InfoDiv& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_InfoDiv& operator << (OC_InfoDiv& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_InfoDiv& operator >> (OC_InfoDiv& from);

// Поле:   guid InfoDiv::ClipArtGUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_ClipArtGUID;
// Поле:   int InfoDiv::ShowCount
   public: CSmartField      <OD_InfoDiv, int            >    m_ShowCount;
// Поле:   int InfoDiv::ClickCount
   public: CSmartField      <OD_InfoDiv, int            >    m_ClickCount;
// Поле:   float InfoDiv::CTR
   public: CSmartField      <OD_InfoDiv, float          >    m_CTR;
// Поле:   int InfoDiv::Estimation_Tot
   public: CSmartField      <OD_InfoDiv, int            >    m_Estimation_Tot;
// Поле:   int InfoDiv::Estimation_Num
   public: CSmartField      <OD_InfoDiv, int            >    m_Estimation_Num;
// Поле:   float InfoDiv::Estimation
   public: CSmartField      <OD_InfoDiv, float          >    m_Estimation;
// Поле:   guid InfoDiv::ProxyObject
   public: CSmartField      <OD_InfoDiv, guid           >    m_ProxyObject;
// Поле:   guid InfoDiv::MOD_Base_GUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_MOD_Base_GUID;
// Поле:   guid InfoDiv::MOD_Extension_GUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier InfoDiv::InfoSourceSortedID []
   public: CSmartFieldArray <OD_InfoDiv, identifier     >    m_InfoSourceSortedID;
// Поле:   identifier InfoDiv::InfoObjectSortedID []
   public: CSmartFieldArray <OD_InfoDiv, identifier     >    m_InfoObjectSortedID;
// Поле:   string InfoDiv::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoDiv, string         >    m_FIELD_Extension_Name;
// Поле:   string InfoDiv::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoDiv, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [-ShowCount]
   public: void SetIndex__ShowCount ();
// Установить текущий индекс по полю [-ClickCount]
   public: void SetIndex__ClickCount ();
// Установить текущий индекс по полю [-CTR]
   public: void SetIndex__CTR ();
// Установить текущий индекс по полю [-Estimation]
   public: void SetIndex__Estimation ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_InfoSource
#endif
#ifdef USES_OC_InfoSource
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "InfoSource"
// 
class OC_InfoSource: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_InfoSource  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_InfoSource  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_InfoSource  (const OC_InfoSource& from);
// Деструктор контроллера объекта
   public: ~OC_InfoSource ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoSource& operator= (const OC_InfoSource& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoSource& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_InfoSource& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_InfoSource& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_InfoSource& operator << (OC_InfoSource& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_InfoSource& operator >> (OC_InfoSource& from);

// Поле:   string InfoSource::Name
   public: CSmartField      <OD_InfoSource, string         >    m_Name;
// Поле:   string InfoSource::Description
   public: CSmartField      <OD_InfoSource, string         >    m_Description;
// Поле:   string InfoSource::URL
   public: CSmartField      <OD_InfoSource, string         >    m_URL;
// Поле:   int InfoSource::RefreshType
   public: CSmartField      <OD_InfoSource, int            >    m_RefreshType;
// Поле:   guid InfoSource::LogoGUID
   public: CSmartField      <OD_InfoSource, guid           >    m_LogoGUID;
// Поле:   string InfoSource::Address
   public: CSmartField      <OD_InfoSource, string         >    m_Address;
// Поле:   string InfoSource::Language
   public: CSmartField      <OD_InfoSource, string         >    m_Language;
// Поле:   string InfoSource::Type
   public: CSmartField      <OD_InfoSource, string         >    m_Type;
// Поле:   string InfoSource::State
   public: CSmartField      <OD_InfoSource, string         >    m_State;
// Поле:   int InfoSource::ShowCount
   public: CSmartField      <OD_InfoSource, int            >    m_ShowCount;
// Поле:   int InfoSource::ClickCount
   public: CSmartField      <OD_InfoSource, int            >    m_ClickCount;
// Поле:   float InfoSource::CTR
   public: CSmartField      <OD_InfoSource, float          >    m_CTR;
// Поле:   int InfoSource::Estimation_Tot
   public: CSmartField      <OD_InfoSource, int            >    m_Estimation_Tot;
// Поле:   int InfoSource::Estimation_Num
   public: CSmartField      <OD_InfoSource, int            >    m_Estimation_Num;
// Поле:   float InfoSource::Estimation
   public: CSmartField      <OD_InfoSource, float          >    m_Estimation;
// Поле:   guid InfoSource::ProxyObject
   public: CSmartField      <OD_InfoSource, guid           >    m_ProxyObject;
// Поле:   guid InfoSource::MOD_Base_GUID
   public: CSmartField      <OD_InfoSource, guid           >    m_MOD_Base_GUID;
// Поле:   guid InfoSource::MOD_Extension_GUID
   public: CSmartField      <OD_InfoSource, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier InfoSource::InfoDivID []
   public: CSmartFieldArray <OD_InfoSource, identifier     >    m_InfoDivID;
// Поле:   guid InfoSource::ColumnistGUID []
   public: CSmartFieldArray <OD_InfoSource, guid           >    m_ColumnistGUID;
// Поле:   string InfoSource::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoSource, string         >    m_FIELD_Extension_Name;
// Поле:   string InfoSource::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoSource, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по полю [RefreshType]
   public: void SetIndex_RefreshType ();
// Установить текущий индекс по полю [-ShowCount]
   public: void SetIndex__ShowCount ();
// Установить текущий индекс по полю [-ClickCount]
   public: void SetIndex__ClickCount ();
// Установить текущий индекс по полю [-CTR]
   public: void SetIndex__CTR ();
// Установить текущий индекс по полю [-Estimation]
   public: void SetIndex__Estimation ();
};
#endif
//------------------------------------------------------------------------------[]






#ifdef  USES_OC_ALL
#define USES_OC_InfoObject
#endif
#ifdef USES_OC_InfoObject
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "InfoObject"
// 
class OC_InfoObject: public OC_Object
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_InfoObject  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_InfoObject  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_InfoObject  (const OC_InfoObject& from);
// Деструктор контроллера объекта
   public: ~OC_InfoObject ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoObject& operator= (const OC_InfoObject& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_InfoObject& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_InfoObject& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_InfoObject& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_InfoObject& operator << (OC_InfoObject& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_InfoObject& operator >> (OC_InfoObject& from);

// Поле:   string InfoObject::SysName
   public: CSmartField      <OD_InfoObject, string         >    m_SysName;
// Поле:   guid InfoObject::OwnerGUID
   public: CSmartField      <OD_InfoObject, guid           >    m_OwnerGUID;
// Поле:   int InfoObject::AccessLevelThreshold
   public: CSmartField      <OD_InfoObject, int            >    m_AccessLevelThreshold;
// Поле:   int InfoObject::CreationTime
   public: CSmartField      <OD_InfoObject, int            >    m_CreationTime;
// Поле:   int InfoObject::InfoTime
   public: CSmartField      <OD_InfoObject, int            >    m_InfoTime;
// Поле:   bool InfoObject::UsageStrictAccess
   public: CSmartField      <OD_InfoObject, bool           >    m_UsageStrictAccess;
// Поле:   guid InfoObject::IconGUID
   public: CSmartField      <OD_InfoObject, guid           >    m_IconGUID;
// Поле:   string InfoObject::OriginalText
   public: CSmartField      <OD_InfoObject, string         >    m_OriginalText;
// Поле:   identifier InfoObject::InfoSourceID
   public: CSmartField      <OD_InfoObject, identifier     >    m_InfoSourceID;
// Поле:   identifier InfoObject::AuthorID
   public: CSmartField      <OD_InfoObject, identifier     >    m_AuthorID;
// Поле:   string InfoObject::AuthorStr
   public: CSmartField      <OD_InfoObject, string         >    m_AuthorStr;
// Поле:   string InfoObject::URL
   public: CSmartField      <OD_InfoObject, string         >    m_URL;
// Поле:   int InfoObject::ShowCount
   public: CSmartField      <OD_InfoObject, int            >    m_ShowCount;
// Поле:   int InfoObject::ClickCount
   public: CSmartField      <OD_InfoObject, int            >    m_ClickCount;
// Поле:   float InfoObject::CTR
   public: CSmartField      <OD_InfoObject, float          >    m_CTR;
// Поле:   int InfoObject::Estimation_Tot
   public: CSmartField      <OD_InfoObject, int            >    m_Estimation_Tot;
// Поле:   int InfoObject::Estimation_Num
   public: CSmartField      <OD_InfoObject, int            >    m_Estimation_Num;
// Поле:   float InfoObject::Estimation
   public: CSmartField      <OD_InfoObject, float          >    m_Estimation;
// Поле:   string InfoObject::Name
   public: CSmartField      <OD_InfoObject, string         >    m_Name;
// Поле:   string InfoObject::Description
   public: CSmartField      <OD_InfoObject, string         >    m_Description;
// Поле:   string InfoObject::Text
   public: CSmartField      <OD_InfoObject, string         >    m_Text;
// Поле:   string InfoObject::Additional
   public: CSmartField      <OD_InfoObject, string         >    m_Additional;
// Поле:   guid InfoObject::ProxyObject
   public: CSmartField      <OD_InfoObject, guid           >    m_ProxyObject;
// Поле:   guid InfoObject::MOD_Base_GUID
   public: CSmartField      <OD_InfoObject, guid           >    m_MOD_Base_GUID;
// Поле:   guid InfoObject::MOD_Extension_GUID
   public: CSmartField      <OD_InfoObject, guid           >    m_MOD_Extension_GUID;
// Поле:   identifier InfoObject::InfoDivID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_InfoDivID;
// Поле:   int InfoObject::Log_Action []
   public: CSmartFieldArray <OD_InfoObject, int            >    m_Log_Action;
// Поле:   guid InfoObject::Log_UserGUID []
   public: CSmartFieldArray <OD_InfoObject, guid           >    m_Log_UserGUID;
// Поле:   int InfoObject::Log_Time []
   public: CSmartFieldArray <OD_InfoObject, int            >    m_Log_Time;
// Поле:   string InfoObject::Log_Comment []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_Log_Comment;
// Поле:   guid InfoObject::ArtworkGUID []
   public: CSmartFieldArray <OD_InfoObject, guid           >    m_ArtworkGUID;
// Поле:   string InfoObject::RelatedLinks []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_RelatedLinks;
// Поле:   identifier InfoObject::CategoryID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_CategoryID;
// Поле:   identifier InfoObject::SearchItemID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_SearchItemID;
// Поле:   string InfoObject::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_FIELD_Extension_Name;
// Поле:   string InfoObject::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_FIELD_Extension_Value;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по полю [Name]
   public: void SetIndex_Name ();
// Установить текущий индекс по набору полей [OwnerGUID, -InfoTime]
   public: void SetIndex_OwnerGUID__InfoTime ();
// Установить текущий индекс по полю [-InfoTime]
   public: void SetIndex__InfoTime ();
// Установить текущий индекс по полю [-CreationTime]
   public: void SetIndex__CreationTime ();
// Установить текущий индекс по набору полей [InfoSourceID, -InfoTime]
   public: void SetIndex_InfoSourceID__InfoTime ();
// Установить текущий индекс по полю [-ShowCount]
   public: void SetIndex__ShowCount ();
// Установить текущий индекс по полю [-ClickCount]
   public: void SetIndex__ClickCount ();
// Установить текущий индекс по полю [-CTR]
   public: void SetIndex__CTR ();
// Установить текущий индекс по полю [-Estimation]
   public: void SetIndex__Estimation ();
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
