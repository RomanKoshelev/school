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
// ���������� �������� ���� ������ ������ "Registry"
// 
class OC_Registry: public OC_Object
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

// ����:   bool Registry::NeedInitiate
   public: CSmartField      <OD_Registry, bool           >    m_NeedInitiate;
// ����:   identifier Registry::ConceptID_Sorted []
   public: CSmartFieldArray <OD_Registry, identifier     >    m_ConceptID_Sorted;
// ����:   int Registry::ConceptNo_SortID []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptNo_SortID;
// ����:   identifier Registry::ConceptID_SortNo []
   public: CSmartFieldArray <OD_Registry, identifier     >    m_ConceptID_SortNo;
// ����:   int Registry::ConceptParent_SortNo []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptParent_SortNo;
// ����:   int Registry::ConceptType_SortNo []
   public: CSmartFieldArray <OD_Registry, int            >    m_ConceptType_SortNo;
// ����:   int Registry::ConceptLevel_SortNo []
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
// ���������� �������� ���� ������ ������ "Relation"
// 
class OC_Relation: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Relation  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Relation  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Relation  (const OC_Relation& from);
// ���������� ����������� �������
   public: ~OC_Relation ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Relation& operator= (const OC_Relation& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Relation& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Relation& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Relation& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Relation& operator << (OC_Relation& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Relation& operator >> (OC_Relation& from);

// ����:   string Relation::SysName
   public: CSmartField      <OD_Relation, string         >    m_SysName;
// ����:   string Relation::Name
   public: CSmartField      <OD_Relation, string         >    m_Name;
// ����:   string Relation::Description
   public: CSmartField      <OD_Relation, string         >    m_Description;
// ����:   int Relation::CreationTime
   public: CSmartField      <OD_Relation, int            >    m_CreationTime;
// ����:   int Relation::Version
   public: CSmartField      <OD_Relation, int            >    m_Version;
// ����:   guid Relation::OwnerGUID
   public: CSmartField      <OD_Relation, guid           >    m_OwnerGUID;
// ����:   int Relation::AccessLevelThreshold
   public: CSmartField      <OD_Relation, int            >    m_AccessLevelThreshold;
// ����:   string Relation::FieldName []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldName;
// ����:   string Relation::FieldType []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldType;
// ����:   string Relation::FieldSysName []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldSysName;
// ����:   string Relation::FieldDescription []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldDescription;
// ����:   string Relation::FieldInterfaceType []
   public: CSmartFieldArray <OD_Relation, string         >    m_FieldInterfaceType;
// ����:   guid Relation::FeodGUID []
   public: CSmartFieldArray <OD_Relation, guid           >    m_FeodGUID;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ���� [SysName]
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
// ���������� �������� ���� ������ ������ "Linkage"
// 
class OC_Linkage: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Linkage  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Linkage  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Linkage  (const OC_Linkage& from);
// ���������� ����������� �������
   public: ~OC_Linkage ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Linkage& operator= (const OC_Linkage& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Linkage& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Linkage& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Linkage& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Linkage& operator << (OC_Linkage& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Linkage& operator >> (OC_Linkage& from);

// ����:   int Linkage::CreationTime
   public: CSmartField      <OD_Linkage, int            >    m_CreationTime;
// ����:   identifier Linkage::RelationID
   public: CSmartField      <OD_Linkage, identifier     >    m_RelationID;
// ����:   guid Linkage::OwnerGUID
   public: CSmartField      <OD_Linkage, guid           >    m_OwnerGUID;
// ����:   int Linkage::AccessLevelThreshold
   public: CSmartField      <OD_Linkage, int            >    m_AccessLevelThreshold;
// ����:   identifier Linkage::ProxyID []
   public: CSmartFieldArray <OD_Linkage, identifier     >    m_ProxyID;
// ����:   string Linkage::Value []
   public: CSmartFieldArray <OD_Linkage, string         >    m_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [RelationID]
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
// ���������� �������� ���� ������ ������ "LinkProxy"
// 
class OC_LinkProxy: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_LinkProxy  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_LinkProxy  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_LinkProxy  (const OC_LinkProxy& from);
// ���������� ����������� �������
   public: ~OC_LinkProxy ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_LinkProxy& operator= (const OC_LinkProxy& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_LinkProxy& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_LinkProxy& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_LinkProxy& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_LinkProxy& operator << (OC_LinkProxy& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_LinkProxy& operator >> (OC_LinkProxy& from);

// ����:   int LinkProxy::CreationTime
   public: CSmartField      <OD_LinkProxy, int            >    m_CreationTime;
// ����:   guid LinkProxy::RealObject
   public: CSmartField      <OD_LinkProxy, guid           >    m_RealObject;
// ����:   identifier LinkProxy::LinkageID []
   public: CSmartFieldArray <OD_LinkProxy, identifier     >    m_LinkageID;
// ����:   identifier LinkProxy::RelationID []
   public: CSmartFieldArray <OD_LinkProxy, identifier     >    m_RelationID;
// ����:   int LinkProxy::RelationField []
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
// ���������� �������� ���� ������ ������ "Connectable"
// 
class OC_Connectable: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Connectable  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Connectable  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Connectable  (const OC_Connectable& from);
// ���������� ����������� �������
   public: ~OC_Connectable ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Connectable& operator= (const OC_Connectable& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Connectable& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Connectable& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Connectable& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Connectable& operator << (OC_Connectable& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Connectable& operator >> (OC_Connectable& from);

// ����:   guid Connectable::ProxyObject
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
// ���������� �������� ���� ������ ������ "MetaObject"
// 
class OC_MetaObject: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_MetaObject  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_MetaObject  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_MetaObject  (const OC_MetaObject& from);
// ���������� ����������� �������
   public: ~OC_MetaObject ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_MetaObject& operator= (const OC_MetaObject& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_MetaObject& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_MetaObject& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_MetaObject& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_MetaObject& operator << (OC_MetaObject& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_MetaObject& operator >> (OC_MetaObject& from);

// ����:   string MetaObject::Type
   public: CSmartField      <OD_MetaObject, string         >    m_Type;
// ����:   string MetaObject::Name
   public: CSmartField      <OD_MetaObject, string         >    m_Name;
// ����:   string MetaObject::SysName
   public: CSmartField      <OD_MetaObject, string         >    m_SysName;
// ����:   string MetaObject::Header1
   public: CSmartField      <OD_MetaObject, string         >    m_Header1;
// ����:   string MetaObject::Header2
   public: CSmartField      <OD_MetaObject, string         >    m_Header2;
// ����:   string MetaObject::Header3
   public: CSmartField      <OD_MetaObject, string         >    m_Header3;
// ����:   string MetaObject::Header4
   public: CSmartField      <OD_MetaObject, string         >    m_Header4;
// ����:   string MetaObject::Header5
   public: CSmartField      <OD_MetaObject, string         >    m_Header5;
// ����:   string MetaObject::Comment
   public: CSmartField      <OD_MetaObject, string         >    m_Comment;
// ����:   string MetaObject::Text
   public: CSmartField      <OD_MetaObject, string         >    m_Text;
// ����:   int MetaObject::CreationTime
   public: CSmartField      <OD_MetaObject, int            >    m_CreationTime;
// ����:   guid MetaObject::OwnerGUID
   public: CSmartField      <OD_MetaObject, guid           >    m_OwnerGUID;
// ����:   int MetaObject::AccessLevelThreshold
   public: CSmartField      <OD_MetaObject, int            >    m_AccessLevelThreshold;
// ����:   guid MetaObject::ProxyObject
   public: CSmartField      <OD_MetaObject, guid           >    m_ProxyObject;
// ����:   guid MetaObject::MOD_Base_GUID
   public: CSmartField      <OD_MetaObject, guid           >    m_MOD_Base_GUID;
// ����:   guid MetaObject::MOD_Extension_GUID
   public: CSmartField      <OD_MetaObject, guid           >    m_MOD_Extension_GUID;
// ����:   int MetaObject::arrInt []
   public: CSmartFieldArray <OD_MetaObject, int            >    m_arrInt;
// ����:   float MetaObject::arrFloat []
   public: CSmartFieldArray <OD_MetaObject, float          >    m_arrFloat;
// ����:   bool MetaObject::arrBool []
   public: CSmartFieldArray <OD_MetaObject, bool           >    m_arrBool;
// ����:   byte MetaObject::arrByte []
   public: CSmartFieldArray <OD_MetaObject, byte           >    m_arrByte;
// ����:   int MetaObject::arrTime []
   public: CSmartFieldArray <OD_MetaObject, int            >    m_arrTime;
// ����:   string MetaObject::arrString []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_arrString;
// ����:   guid MetaObject::arrGUID []
   public: CSmartFieldArray <OD_MetaObject, guid           >    m_arrGUID;
// ����:   identifier MetaObject::arrID []
   public: CSmartFieldArray <OD_MetaObject, identifier     >    m_arrID;
// ����:   guid MetaObject::FeodGUID []
   public: CSmartFieldArray <OD_MetaObject, guid           >    m_FeodGUID;
// ����:   string MetaObject::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_FIELD_Extension_Name;
// ����:   string MetaObject::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_MetaObject, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [Type, Name]
   public: void SetIndex_Type_Name ();
// ���������� ������� ������ �� ������ ����� [Type, SysName]
   public: void SetIndex_Type_SysName ();
// ���������� ������� ������ �� ������ ����� [Type, Header1, Header2, Header3, Header4, Header5]
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
// ���������� �������� ���� ������ ������ "Concept"
// 
class OC_Concept: public OC_Object
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

// ����:   string Concept::Name
   public: CSmartField      <OD_Concept, string         >    m_Name;
// ����:   string Concept::Description
   public: CSmartField      <OD_Concept, string         >    m_Description;
// ����:   string Concept::Type
   public: CSmartField      <OD_Concept, string         >    m_Type;
// ����:   int Concept::TypeNo
   public: CSmartField      <OD_Concept, int            >    m_TypeNo;
// ����:   identifier Concept::Parent
   public: CSmartField      <OD_Concept, identifier     >    m_Parent;
// ����:   int Concept::Level
   public: CSmartField      <OD_Concept, int            >    m_Level;
// ����:   int Concept::No
   public: CSmartField      <OD_Concept, int            >    m_No;
// ����:   guid Concept::MOD_Base_GUID
   public: CSmartField      <OD_Concept, guid           >    m_MOD_Base_GUID;
// ����:   guid Concept::MOD_Extension_GUID
   public: CSmartField      <OD_Concept, guid           >    m_MOD_Extension_GUID;
// ����:   identifier Concept::Ancestor []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Ancestor;
// ����:   int Concept::AncestorNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_AncestorNo;
// ����:   int Concept::AncestorWeight []
   public: CSmartFieldArray <OD_Concept, int            >    m_AncestorWeight;
// ����:   identifier Concept::AllAncestor []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_AllAncestor;
// ����:   identifier Concept::AllAncestorNo []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_AllAncestorNo;
// ����:   identifier Concept::Child []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Child;
// ����:   int Concept::ChildNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_ChildNo;
// ����:   identifier Concept::Descendant []
   public: CSmartFieldArray <OD_Concept, identifier     >    m_Descendant;
// ����:   int Concept::DescendantNo []
   public: CSmartFieldArray <OD_Concept, int            >    m_DescendantNo;
// ����:   string Concept::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_Concept, string         >    m_FIELD_Extension_Name;
// ����:   string Concept::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_Concept, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ���� [Level]
   public: void SetIndex_Level ();
// ���������� ������� ������ �� ���� [No]
   public: void SetIndex_No ();
// ���������� ������� ������ �� ������ ����� [Type, Level]
   public: void SetIndex_Type_Level ();
// ���������� ������� ������ �� ���� [TypeNo]
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
// ���������� �������� ���� ������ ������ "User"
// 
class OC_User: public OC_Object
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
   public: CSmartField      <OD_User, string         >    m_Login;
// ����:   string User::Password
   public: CSmartField      <OD_User, string         >    m_Password;
// ����:   bool User::PasswordInBrowser
   public: CSmartField      <OD_User, bool           >    m_PasswordInBrowser;
// ����:   int User::CreationTime
   public: CSmartField      <OD_User, int            >    m_CreationTime;
// ����:   string User::FullName
   public: CSmartField      <OD_User, string         >    m_FullName;
// ����:   string User::Email
   public: CSmartField      <OD_User, string         >    m_Email;
// ����:   string User::URL
   public: CSmartField      <OD_User, string         >    m_URL;
// ����:   string User::Data
   public: CSmartField      <OD_User, string         >    m_Data;
// ����:   int User::AccessLevel
   public: CSmartField      <OD_User, int            >    m_AccessLevel;
// ����:   guid User::ProxyObject
   public: CSmartField      <OD_User, guid           >    m_ProxyObject;
// ����:   guid User::MOD_Base_GUID
   public: CSmartField      <OD_User, guid           >    m_MOD_Base_GUID;
// ����:   guid User::MOD_Extension_GUID
   public: CSmartField      <OD_User, guid           >    m_MOD_Extension_GUID;
// ����:   identifier User::GroupID []
   public: CSmartFieldArray <OD_User, identifier     >    m_GroupID;
// ����:   identifier User::OwnFeodID []
   public: CSmartFieldArray <OD_User, identifier     >    m_OwnFeodID;
// ����:   string User::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_User, string         >    m_FIELD_Extension_Name;
// ����:   string User::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_User, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Login]
   public: void SetIndex_Login ();
// ���������� ������� ������ �� ���� [FullName]
   public: void SetIndex_FullName ();
// ���������� ������� ������ �� ���� [-CreationTime]
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
// ���������� �������� ���� ������ ������ "UserGroup"
// 
class OC_UserGroup: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_UserGroup  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_UserGroup  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_UserGroup  (const OC_UserGroup& from);
// ���������� ����������� �������
   public: ~OC_UserGroup ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_UserGroup& operator= (const OC_UserGroup& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_UserGroup& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_UserGroup& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_UserGroup& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_UserGroup& operator << (OC_UserGroup& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_UserGroup& operator >> (OC_UserGroup& from);

// ����:   string UserGroup::Name
   public: CSmartField      <OD_UserGroup, string         >    m_Name;
// ����:   string UserGroup::Type
   public: CSmartField      <OD_UserGroup, string         >    m_Type;
// ����:   string UserGroup::Description
   public: CSmartField      <OD_UserGroup, string         >    m_Description;
// ����:   int UserGroup::CreationTime
   public: CSmartField      <OD_UserGroup, int            >    m_CreationTime;
// ����:   guid UserGroup::OwnerGUID
   public: CSmartField      <OD_UserGroup, guid           >    m_OwnerGUID;
// ����:   int UserGroup::AccessLevelThreshold
   public: CSmartField      <OD_UserGroup, int            >    m_AccessLevelThreshold;
// ����:   guid UserGroup::ProxyObject
   public: CSmartField      <OD_UserGroup, guid           >    m_ProxyObject;
// ����:   guid UserGroup::MOD_Base_GUID
   public: CSmartField      <OD_UserGroup, guid           >    m_MOD_Base_GUID;
// ����:   guid UserGroup::MOD_Extension_GUID
   public: CSmartField      <OD_UserGroup, guid           >    m_MOD_Extension_GUID;
// ����:   identifier UserGroup::UserID []
   public: CSmartFieldArray <OD_UserGroup, identifier     >    m_UserID;
// ����:   identifier UserGroup::Rights_Feod []
   public: CSmartFieldArray <OD_UserGroup, identifier     >    m_Rights_Feod;
// ����:   string UserGroup::Rights_Attr []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_Rights_Attr;
// ����:   string UserGroup::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_FIELD_Extension_Name;
// ����:   string UserGroup::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_UserGroup, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ���� [Type]
   public: void SetIndex_Type ();
// ���������� ������� ������ �� ���� [CreationTime]
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
// ���������� �������� ���� ������ ������ "Text"
// 
class OC_Text: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Text  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Text  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Text  (const OC_Text& from);
// ���������� ����������� �������
   public: ~OC_Text ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Text& operator= (const OC_Text& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Text& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Text& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Text& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Text& operator << (OC_Text& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Text& operator >> (OC_Text& from);

// ����:   string Text::Name
   public: CSmartField      <OD_Text, string         >    m_Name;
// ����:   string Text::Text
   public: CSmartField      <OD_Text, string         >    m_Text;
// ����:   int Text::CreationTime
   public: CSmartField      <OD_Text, int            >    m_CreationTime;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
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
// ���������� �������� ���� ������ ������ "MorphologicRule"
// 
class OC_MorphologicRule: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_MorphologicRule  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_MorphologicRule  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_MorphologicRule  (const OC_MorphologicRule& from);
// ���������� ����������� �������
   public: ~OC_MorphologicRule ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_MorphologicRule& operator= (const OC_MorphologicRule& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_MorphologicRule& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_MorphologicRule& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_MorphologicRule& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_MorphologicRule& operator << (OC_MorphologicRule& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_MorphologicRule& operator >> (OC_MorphologicRule& from);

// ����:   byte MorphologicRule::Attribute
   public: CSmartField      <OD_MorphologicRule, byte           >    m_Attribute;
// ����:   string MorphologicRule::AffixNormal
   public: CSmartField      <OD_MorphologicRule, string         >    m_AffixNormal;
// ����:   string MorphologicRule::AffixVariant
   public: CSmartField      <OD_MorphologicRule, string         >    m_AffixVariant;
// ����:   string MorphologicRule::Comment
   public: CSmartField      <OD_MorphologicRule, string         >    m_Comment;
// ����:   int MorphologicRule::Number
   public: CSmartField      <OD_MorphologicRule, int            >    m_Number;
// ����:   int MorphologicRule::MatchCount
   public: CSmartField      <OD_MorphologicRule, int            >    m_MatchCount;
// ����:   int MorphologicRule::ApplyCount
   public: CSmartField      <OD_MorphologicRule, int            >    m_ApplyCount;
// ����:   byte MorphologicRule::BaseEnd_Available []
   public: CSmartFieldArray <OD_MorphologicRule, byte           >    m_BaseEnd_Available;
// ����:   byte MorphologicRule::BaseEnd_Exception []
   public: CSmartFieldArray <OD_MorphologicRule, byte           >    m_BaseEnd_Exception;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [AffixVariant]
   public: void SetIndex_AffixVariant ();
// ���������� ������� ������ �� ������ ����� [Attribute, AffixNormal, AffixVariant]
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
// ���������� �������� ���� ������ ������ "SearchItem"
// 
class OC_SearchItem: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_SearchItem  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_SearchItem  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_SearchItem  (const OC_SearchItem& from);
// ���������� ����������� �������
   public: ~OC_SearchItem ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SearchItem& operator= (const OC_SearchItem& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_SearchItem& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_SearchItem& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_SearchItem& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_SearchItem& operator << (OC_SearchItem& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_SearchItem& operator >> (OC_SearchItem& from);

// ����:   string SearchItem::NormalWord
   public: CSmartField      <OD_SearchItem, string         >    m_NormalWord;
// ����:   string SearchItem::NormalWordInv
   public: CSmartField      <OD_SearchItem, string         >    m_NormalWordInv;
// ����:   string SearchItem::Attributes
   public: CSmartField      <OD_SearchItem, string         >    m_Attributes;
// ����:   bool SearchItem::Hypothesis
   public: CSmartField      <OD_SearchItem, bool           >    m_Hypothesis;
// ����:   int SearchItem::Text_Number
   public: CSmartField      <OD_SearchItem, int            >    m_Text_Number;
// ����:   guid SearchItem::Text_ObjectSortedGUID []
   public: CSmartFieldArray <OD_SearchItem, guid           >    m_Text_ObjectSortedGUID;
// ����:   int SearchItem::Text_ModificationTime []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_ModificationTime;
// ����:   int SearchItem::Text_WordAppearanceNum []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_WordAppearanceNum;
// ����:   int SearchItem::Text_WordFirstPosition []
   public: CSmartFieldArray <OD_SearchItem, int            >    m_Text_WordFirstPosition;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [NormalWord, Hypothesis]
   public: void SetIndex_NormalWord_Hypothesis ();
// ���������� ������� ������ �� ���� [NormalWordInv]
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
// ���������� �������� ���� ������ ������ "StopWord"
// 
class OC_StopWord: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_StopWord  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_StopWord  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_StopWord  (const OC_StopWord& from);
// ���������� ����������� �������
   public: ~OC_StopWord ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_StopWord& operator= (const OC_StopWord& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_StopWord& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_StopWord& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_StopWord& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_StopWord& operator << (OC_StopWord& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_StopWord& operator >> (OC_StopWord& from);

// ����:   string StopWord::Word
   public: CSmartField      <OD_StopWord, string         >    m_Word;

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
#define USES_OC_WordNibbleABC
#endif
#ifdef USES_OC_WordNibbleABC
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "WordNibbleABC"
// 
class OC_WordNibbleABC: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_WordNibbleABC  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_WordNibbleABC  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_WordNibbleABC  (const OC_WordNibbleABC& from);
// ���������� ����������� �������
   public: ~OC_WordNibbleABC ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WordNibbleABC& operator= (const OC_WordNibbleABC& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WordNibbleABC& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_WordNibbleABC& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_WordNibbleABC& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_WordNibbleABC& operator << (OC_WordNibbleABC& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_WordNibbleABC& operator >> (OC_WordNibbleABC& from);

// ����:   string WordNibbleABC::Nibble
   public: CSmartField      <OD_WordNibbleABC, string         >    m_Nibble;
// ����:   int WordNibbleABC::Num
   public: CSmartField      <OD_WordNibbleABC, int            >    m_Num;
// ����:   float WordNibbleABC::FreqPerMillion
   public: CSmartField      <OD_WordNibbleABC, float          >    m_FreqPerMillion;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Nibble]
   public: void SetIndex_Nibble ();
// ���������� ������� ������ �� ���� [FreqPerMillion]
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
// ���������� �������� ���� ������ ������ "WebFolder"
// 
class OC_WebFolder: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_WebFolder  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_WebFolder  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_WebFolder  (const OC_WebFolder& from);
// ���������� ����������� �������
   public: ~OC_WebFolder ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WebFolder& operator= (const OC_WebFolder& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WebFolder& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_WebFolder& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_WebFolder& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_WebFolder& operator << (OC_WebFolder& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_WebFolder& operator >> (OC_WebFolder& from);

// ����:   int WebFolder::ShowCount
   public: CSmartField      <OD_WebFolder, int            >    m_ShowCount;
// ����:   int WebFolder::ClickCount
   public: CSmartField      <OD_WebFolder, int            >    m_ClickCount;
// ����:   float WebFolder::CTR
   public: CSmartField      <OD_WebFolder, float          >    m_CTR;
// ����:   int WebFolder::Estimation_Tot
   public: CSmartField      <OD_WebFolder, int            >    m_Estimation_Tot;
// ����:   int WebFolder::Estimation_Num
   public: CSmartField      <OD_WebFolder, int            >    m_Estimation_Num;
// ����:   float WebFolder::Estimation
   public: CSmartField      <OD_WebFolder, float          >    m_Estimation;
// ����:   guid WebFolder::ProxyObject
   public: CSmartField      <OD_WebFolder, guid           >    m_ProxyObject;
// ����:   guid WebFolder::MOD_Base_GUID
   public: CSmartField      <OD_WebFolder, guid           >    m_MOD_Base_GUID;
// ����:   guid WebFolder::MOD_Extension_GUID
   public: CSmartField      <OD_WebFolder, guid           >    m_MOD_Extension_GUID;
// ����:   identifier WebFolder::WebFileSortedID []
   public: CSmartFieldArray <OD_WebFolder, identifier     >    m_WebFileSortedID;
// ����:   string WebFolder::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_WebFolder, string         >    m_FIELD_Extension_Name;
// ����:   string WebFolder::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_WebFolder, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [-ShowCount]
   public: void SetIndex__ShowCount ();
// ���������� ������� ������ �� ���� [-ClickCount]
   public: void SetIndex__ClickCount ();
// ���������� ������� ������ �� ���� [-CTR]
   public: void SetIndex__CTR ();
// ���������� ������� ������ �� ���� [-Estimation]
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
// ���������� �������� ���� ������ ������ "WebFile"
// 
class OC_WebFile: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_WebFile  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_WebFile  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_WebFile  (const OC_WebFile& from);
// ���������� ����������� �������
   public: ~OC_WebFile ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WebFile& operator= (const OC_WebFile& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_WebFile& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_WebFile& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_WebFile& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_WebFile& operator << (OC_WebFile& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_WebFile& operator >> (OC_WebFile& from);

// ����:   string WebFile::Name_OSFile
   public: CSmartField      <OD_WebFile, string         >    m_Name_OSFile;
// ����:   string WebFile::Name_Upload
   public: CSmartField      <OD_WebFile, string         >    m_Name_Upload;
// ����:   string WebFile::MIMEType
   public: CSmartField      <OD_WebFile, string         >    m_MIMEType;
// ����:   string WebFile::IconType
   public: CSmartField      <OD_WebFile, string         >    m_IconType;
// ����:   guid WebFile::OwnerGUID
   public: CSmartField      <OD_WebFile, guid           >    m_OwnerGUID;
// ����:   int WebFile::AccessLevelThreshold
   public: CSmartField      <OD_WebFile, int            >    m_AccessLevelThreshold;
// ����:   int WebFile::CreationTime
   public: CSmartField      <OD_WebFile, int            >    m_CreationTime;
// ����:   int WebFile::ModificationTime
   public: CSmartField      <OD_WebFile, int            >    m_ModificationTime;
// ����:   int WebFile::LastAccessTime
   public: CSmartField      <OD_WebFile, int            >    m_LastAccessTime;
// ����:   int WebFile::Version
   public: CSmartField      <OD_WebFile, int            >    m_Version;
// ����:   int WebFile::ShowCount
   public: CSmartField      <OD_WebFile, int            >    m_ShowCount;
// ����:   int WebFile::ClickCount
   public: CSmartField      <OD_WebFile, int            >    m_ClickCount;
// ����:   float WebFile::CTR
   public: CSmartField      <OD_WebFile, float          >    m_CTR;
// ����:   int WebFile::Estimation_Tot
   public: CSmartField      <OD_WebFile, int            >    m_Estimation_Tot;
// ����:   int WebFile::Estimation_Num
   public: CSmartField      <OD_WebFile, int            >    m_Estimation_Num;
// ����:   float WebFile::Estimation
   public: CSmartField      <OD_WebFile, float          >    m_Estimation;
// ����:   guid WebFile::ProxyObject
   public: CSmartField      <OD_WebFile, guid           >    m_ProxyObject;
// ����:   guid WebFile::MOD_Base_GUID
   public: CSmartField      <OD_WebFile, guid           >    m_MOD_Base_GUID;
// ����:   guid WebFile::MOD_Extension_GUID
   public: CSmartField      <OD_WebFile, guid           >    m_MOD_Extension_GUID;
// ����:   string WebFile::Name
   public: CSmartField      <OD_WebFile, string         >    m_Name;
// ����:   string WebFile::Description
   public: CSmartField      <OD_WebFile, string         >    m_Description;
// ����:   string WebFile::Text
   public: CSmartField      <OD_WebFile, string         >    m_Text;
// ����:   string WebFile::Additional
   public: CSmartField      <OD_WebFile, string         >    m_Additional;
// ����:   identifier WebFile::WebFolderID []
   public: CSmartFieldArray <OD_WebFile, identifier     >    m_WebFolderID;
// ����:   byte WebFile::BinaryData []
   public: CSmartFieldArray <OD_WebFile, byte           >    m_BinaryData;
// ����:   string WebFile::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_WebFile, string         >    m_FIELD_Extension_Name;
// ����:   string WebFile::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_WebFile, string         >    m_FIELD_Extension_Value;
// ����:   identifier WebFile::SearchItemID []
   public: CSmartFieldArray <OD_WebFile, identifier     >    m_SearchItemID;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ���� [OwnerGUID]
   public: void SetIndex_OwnerGUID ();
// ���������� ������� ������ �� ���� [-CreationTime]
   public: void SetIndex__CreationTime ();
// ���������� ������� ������ �� ���� [-ModificationTime]
   public: void SetIndex__ModificationTime ();
// ���������� ������� ������ �� ���� [-LastAccessTime]
   public: void SetIndex__LastAccessTime ();
// ���������� ������� ������ �� ���� [-ShowCount]
   public: void SetIndex__ShowCount ();
// ���������� ������� ������ �� ���� [-ClickCount]
   public: void SetIndex__ClickCount ();
// ���������� ������� ������ �� ���� [-CTR]
   public: void SetIndex__CTR ();
// ���������� ������� ������ �� ���� [-Estimation]
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
// ���������� �������� ���� ������ ������ "UserProfile"
// 
class OC_UserProfile: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_UserProfile  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_UserProfile  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_UserProfile  (const OC_UserProfile& from);
// ���������� ����������� �������
   public: ~OC_UserProfile ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_UserProfile& operator= (const OC_UserProfile& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_UserProfile& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_UserProfile& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_UserProfile& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_UserProfile& operator << (OC_UserProfile& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_UserProfile& operator >> (OC_UserProfile& from);

// ����:   guid UserProfile::UserGUID
   public: CSmartField      <OD_UserProfile, guid           >    m_UserGUID;
// ����:   int UserProfile::SeenIO_ShowCount
   public: CSmartField      <OD_UserProfile, int            >    m_SeenIO_ShowCount;
// ����:   int UserProfile::SeenIO_ClickCount
   public: CSmartField      <OD_UserProfile, int            >    m_SeenIO_ClickCount;
// ����:   float UserProfile::SeenIO_CTR
   public: CSmartField      <OD_UserProfile, float          >    m_SeenIO_CTR;
// ����:   int UserProfile::OwnIO_ShowCount
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_ShowCount;
// ����:   int UserProfile::OwnIO_ClickCount
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_ClickCount;
// ����:   float UserProfile::OwnIO_CTR
   public: CSmartField      <OD_UserProfile, float          >    m_OwnIO_CTR;
// ����:   int UserProfile::OwnIO_Estimation_Tot
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_Estimation_Tot;
// ����:   int UserProfile::OwnIO_Estimation_Num
   public: CSmartField      <OD_UserProfile, int            >    m_OwnIO_Estimation_Num;
// ����:   float UserProfile::OwnIO_Estimation
   public: CSmartField      <OD_UserProfile, float          >    m_OwnIO_Estimation;
// ����:   bool UserProfile::Account_Enable
   public: CSmartField      <OD_UserProfile, bool           >    m_Account_Enable;
// ����:   float UserProfile::Account_Debit
   public: CSmartField      <OD_UserProfile, float          >    m_Account_Debit;
// ����:   float UserProfile::Account_Credit
   public: CSmartField      <OD_UserProfile, float          >    m_Account_Credit;
// ����:   guid UserProfile::RootFolderGUID
   public: CSmartField      <OD_UserProfile, guid           >    m_RootFolderGUID;
// ����:   guid UserProfile::ProxyObject
   public: CSmartField      <OD_UserProfile, guid           >    m_ProxyObject;
// ����:   guid UserProfile::MOD_Base_GUID
   public: CSmartField      <OD_UserProfile, guid           >    m_MOD_Base_GUID;
// ����:   guid UserProfile::MOD_Extension_GUID
   public: CSmartField      <OD_UserProfile, guid           >    m_MOD_Extension_GUID;
// ����:   identifier UserProfile::InfoDiv_Hide []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_InfoDiv_Hide;
// ����:   identifier UserProfile::InfoDiv_Show []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_InfoDiv_Show;
// ����:   string UserProfile::Filter_Name []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Filter_Name;
// ����:   string UserProfile::Filter_SearchPhrase []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Filter_SearchPhrase;
// ����:   identifier UserProfile::Filter_FolderID []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_Filter_FolderID;
// ����:   identifier UserProfile::SeenIO_ID []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_SeenIO_ID;
// ����:   int UserProfile::SeenIO_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_SeenIO_Time;
// ����:   byte UserProfile::SeenIO_Estimation []
   public: CSmartFieldArray <OD_UserProfile, byte           >    m_SeenIO_Estimation;
// ����:   identifier UserProfile::OwnIO []
   public: CSmartFieldArray <OD_UserProfile, identifier     >    m_OwnIO;
// ����:   int UserProfile::OwnIO_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_OwnIO_Time;
// ����:   guid UserProfile::Log_ObjectGUID []
   public: CSmartFieldArray <OD_UserProfile, guid           >    m_Log_ObjectGUID;
// ����:   int UserProfile::Log_Action []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Log_Action;
// ����:   int UserProfile::Log_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Log_Time;
// ����:   int UserProfile::Account_Log_Action []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Account_Log_Action;
// ����:   float UserProfile::Account_Log_Amount []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Amount;
// ����:   float UserProfile::Account_Log_Debit []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Debit;
// ����:   float UserProfile::Account_Log_Credit []
   public: CSmartFieldArray <OD_UserProfile, float          >    m_Account_Log_Credit;
// ����:   int UserProfile::Account_Log_Time []
   public: CSmartFieldArray <OD_UserProfile, int            >    m_Account_Log_Time;
// ����:   string UserProfile::Account_Log_Comment []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_Account_Log_Comment;
// ����:   string UserProfile::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_FIELD_Extension_Name;
// ����:   string UserProfile::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_UserProfile, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [-SeenIO_ShowCount]
   public: void SetIndex__SeenIO_ShowCount ();
// ���������� ������� ������ �� ���� [-SeenIO_CTR]
   public: void SetIndex__SeenIO_CTR ();
// ���������� ������� ������ �� ���� [-OwnIO_ShowCount]
   public: void SetIndex__OwnIO_ShowCount ();
// ���������� ������� ������ �� ���� [-OwnIO_CTR]
   public: void SetIndex__OwnIO_CTR ();
// ���������� ������� ������ �� ���� [-OwnIO_Estimation]
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
// ���������� �������� ���� ������ ������ "InfoDiv"
// 
class OC_InfoDiv: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_InfoDiv  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_InfoDiv  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_InfoDiv  (const OC_InfoDiv& from);
// ���������� ����������� �������
   public: ~OC_InfoDiv ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoDiv& operator= (const OC_InfoDiv& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoDiv& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_InfoDiv& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_InfoDiv& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_InfoDiv& operator << (OC_InfoDiv& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_InfoDiv& operator >> (OC_InfoDiv& from);

// ����:   guid InfoDiv::ClipArtGUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_ClipArtGUID;
// ����:   int InfoDiv::ShowCount
   public: CSmartField      <OD_InfoDiv, int            >    m_ShowCount;
// ����:   int InfoDiv::ClickCount
   public: CSmartField      <OD_InfoDiv, int            >    m_ClickCount;
// ����:   float InfoDiv::CTR
   public: CSmartField      <OD_InfoDiv, float          >    m_CTR;
// ����:   int InfoDiv::Estimation_Tot
   public: CSmartField      <OD_InfoDiv, int            >    m_Estimation_Tot;
// ����:   int InfoDiv::Estimation_Num
   public: CSmartField      <OD_InfoDiv, int            >    m_Estimation_Num;
// ����:   float InfoDiv::Estimation
   public: CSmartField      <OD_InfoDiv, float          >    m_Estimation;
// ����:   guid InfoDiv::ProxyObject
   public: CSmartField      <OD_InfoDiv, guid           >    m_ProxyObject;
// ����:   guid InfoDiv::MOD_Base_GUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_MOD_Base_GUID;
// ����:   guid InfoDiv::MOD_Extension_GUID
   public: CSmartField      <OD_InfoDiv, guid           >    m_MOD_Extension_GUID;
// ����:   identifier InfoDiv::InfoSourceSortedID []
   public: CSmartFieldArray <OD_InfoDiv, identifier     >    m_InfoSourceSortedID;
// ����:   identifier InfoDiv::InfoObjectSortedID []
   public: CSmartFieldArray <OD_InfoDiv, identifier     >    m_InfoObjectSortedID;
// ����:   string InfoDiv::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoDiv, string         >    m_FIELD_Extension_Name;
// ����:   string InfoDiv::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoDiv, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [-ShowCount]
   public: void SetIndex__ShowCount ();
// ���������� ������� ������ �� ���� [-ClickCount]
   public: void SetIndex__ClickCount ();
// ���������� ������� ������ �� ���� [-CTR]
   public: void SetIndex__CTR ();
// ���������� ������� ������ �� ���� [-Estimation]
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
// ���������� �������� ���� ������ ������ "InfoSource"
// 
class OC_InfoSource: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_InfoSource  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_InfoSource  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_InfoSource  (const OC_InfoSource& from);
// ���������� ����������� �������
   public: ~OC_InfoSource ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoSource& operator= (const OC_InfoSource& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoSource& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_InfoSource& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_InfoSource& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_InfoSource& operator << (OC_InfoSource& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_InfoSource& operator >> (OC_InfoSource& from);

// ����:   string InfoSource::Name
   public: CSmartField      <OD_InfoSource, string         >    m_Name;
// ����:   string InfoSource::Description
   public: CSmartField      <OD_InfoSource, string         >    m_Description;
// ����:   string InfoSource::URL
   public: CSmartField      <OD_InfoSource, string         >    m_URL;
// ����:   int InfoSource::RefreshType
   public: CSmartField      <OD_InfoSource, int            >    m_RefreshType;
// ����:   guid InfoSource::LogoGUID
   public: CSmartField      <OD_InfoSource, guid           >    m_LogoGUID;
// ����:   string InfoSource::Address
   public: CSmartField      <OD_InfoSource, string         >    m_Address;
// ����:   string InfoSource::Language
   public: CSmartField      <OD_InfoSource, string         >    m_Language;
// ����:   string InfoSource::Type
   public: CSmartField      <OD_InfoSource, string         >    m_Type;
// ����:   string InfoSource::State
   public: CSmartField      <OD_InfoSource, string         >    m_State;
// ����:   int InfoSource::ShowCount
   public: CSmartField      <OD_InfoSource, int            >    m_ShowCount;
// ����:   int InfoSource::ClickCount
   public: CSmartField      <OD_InfoSource, int            >    m_ClickCount;
// ����:   float InfoSource::CTR
   public: CSmartField      <OD_InfoSource, float          >    m_CTR;
// ����:   int InfoSource::Estimation_Tot
   public: CSmartField      <OD_InfoSource, int            >    m_Estimation_Tot;
// ����:   int InfoSource::Estimation_Num
   public: CSmartField      <OD_InfoSource, int            >    m_Estimation_Num;
// ����:   float InfoSource::Estimation
   public: CSmartField      <OD_InfoSource, float          >    m_Estimation;
// ����:   guid InfoSource::ProxyObject
   public: CSmartField      <OD_InfoSource, guid           >    m_ProxyObject;
// ����:   guid InfoSource::MOD_Base_GUID
   public: CSmartField      <OD_InfoSource, guid           >    m_MOD_Base_GUID;
// ����:   guid InfoSource::MOD_Extension_GUID
   public: CSmartField      <OD_InfoSource, guid           >    m_MOD_Extension_GUID;
// ����:   identifier InfoSource::InfoDivID []
   public: CSmartFieldArray <OD_InfoSource, identifier     >    m_InfoDivID;
// ����:   guid InfoSource::ColumnistGUID []
   public: CSmartFieldArray <OD_InfoSource, guid           >    m_ColumnistGUID;
// ����:   string InfoSource::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoSource, string         >    m_FIELD_Extension_Name;
// ����:   string InfoSource::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoSource, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ���� [RefreshType]
   public: void SetIndex_RefreshType ();
// ���������� ������� ������ �� ���� [-ShowCount]
   public: void SetIndex__ShowCount ();
// ���������� ������� ������ �� ���� [-ClickCount]
   public: void SetIndex__ClickCount ();
// ���������� ������� ������ �� ���� [-CTR]
   public: void SetIndex__CTR ();
// ���������� ������� ������ �� ���� [-Estimation]
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
// ���������� �������� ���� ������ ������ "InfoObject"
// 
class OC_InfoObject: public OC_Object
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_InfoObject  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_InfoObject  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_InfoObject  (const OC_InfoObject& from);
// ���������� ����������� �������
   public: ~OC_InfoObject ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoObject& operator= (const OC_InfoObject& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_InfoObject& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_InfoObject& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_InfoObject& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_InfoObject& operator << (OC_InfoObject& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_InfoObject& operator >> (OC_InfoObject& from);

// ����:   string InfoObject::SysName
   public: CSmartField      <OD_InfoObject, string         >    m_SysName;
// ����:   guid InfoObject::OwnerGUID
   public: CSmartField      <OD_InfoObject, guid           >    m_OwnerGUID;
// ����:   int InfoObject::AccessLevelThreshold
   public: CSmartField      <OD_InfoObject, int            >    m_AccessLevelThreshold;
// ����:   int InfoObject::CreationTime
   public: CSmartField      <OD_InfoObject, int            >    m_CreationTime;
// ����:   int InfoObject::InfoTime
   public: CSmartField      <OD_InfoObject, int            >    m_InfoTime;
// ����:   bool InfoObject::UsageStrictAccess
   public: CSmartField      <OD_InfoObject, bool           >    m_UsageStrictAccess;
// ����:   guid InfoObject::IconGUID
   public: CSmartField      <OD_InfoObject, guid           >    m_IconGUID;
// ����:   string InfoObject::OriginalText
   public: CSmartField      <OD_InfoObject, string         >    m_OriginalText;
// ����:   identifier InfoObject::InfoSourceID
   public: CSmartField      <OD_InfoObject, identifier     >    m_InfoSourceID;
// ����:   identifier InfoObject::AuthorID
   public: CSmartField      <OD_InfoObject, identifier     >    m_AuthorID;
// ����:   string InfoObject::AuthorStr
   public: CSmartField      <OD_InfoObject, string         >    m_AuthorStr;
// ����:   string InfoObject::URL
   public: CSmartField      <OD_InfoObject, string         >    m_URL;
// ����:   int InfoObject::ShowCount
   public: CSmartField      <OD_InfoObject, int            >    m_ShowCount;
// ����:   int InfoObject::ClickCount
   public: CSmartField      <OD_InfoObject, int            >    m_ClickCount;
// ����:   float InfoObject::CTR
   public: CSmartField      <OD_InfoObject, float          >    m_CTR;
// ����:   int InfoObject::Estimation_Tot
   public: CSmartField      <OD_InfoObject, int            >    m_Estimation_Tot;
// ����:   int InfoObject::Estimation_Num
   public: CSmartField      <OD_InfoObject, int            >    m_Estimation_Num;
// ����:   float InfoObject::Estimation
   public: CSmartField      <OD_InfoObject, float          >    m_Estimation;
// ����:   string InfoObject::Name
   public: CSmartField      <OD_InfoObject, string         >    m_Name;
// ����:   string InfoObject::Description
   public: CSmartField      <OD_InfoObject, string         >    m_Description;
// ����:   string InfoObject::Text
   public: CSmartField      <OD_InfoObject, string         >    m_Text;
// ����:   string InfoObject::Additional
   public: CSmartField      <OD_InfoObject, string         >    m_Additional;
// ����:   guid InfoObject::ProxyObject
   public: CSmartField      <OD_InfoObject, guid           >    m_ProxyObject;
// ����:   guid InfoObject::MOD_Base_GUID
   public: CSmartField      <OD_InfoObject, guid           >    m_MOD_Base_GUID;
// ����:   guid InfoObject::MOD_Extension_GUID
   public: CSmartField      <OD_InfoObject, guid           >    m_MOD_Extension_GUID;
// ����:   identifier InfoObject::InfoDivID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_InfoDivID;
// ����:   int InfoObject::Log_Action []
   public: CSmartFieldArray <OD_InfoObject, int            >    m_Log_Action;
// ����:   guid InfoObject::Log_UserGUID []
   public: CSmartFieldArray <OD_InfoObject, guid           >    m_Log_UserGUID;
// ����:   int InfoObject::Log_Time []
   public: CSmartFieldArray <OD_InfoObject, int            >    m_Log_Time;
// ����:   string InfoObject::Log_Comment []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_Log_Comment;
// ����:   guid InfoObject::ArtworkGUID []
   public: CSmartFieldArray <OD_InfoObject, guid           >    m_ArtworkGUID;
// ����:   string InfoObject::RelatedLinks []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_RelatedLinks;
// ����:   identifier InfoObject::CategoryID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_CategoryID;
// ����:   identifier InfoObject::SearchItemID []
   public: CSmartFieldArray <OD_InfoObject, identifier     >    m_SearchItemID;
// ����:   string InfoObject::FIELD_Extension_Name []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_FIELD_Extension_Name;
// ����:   string InfoObject::FIELD_Extension_Value []
   public: CSmartFieldArray <OD_InfoObject, string         >    m_FIELD_Extension_Value;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ���� [Name]
   public: void SetIndex_Name ();
// ���������� ������� ������ �� ������ ����� [OwnerGUID, -InfoTime]
   public: void SetIndex_OwnerGUID__InfoTime ();
// ���������� ������� ������ �� ���� [-InfoTime]
   public: void SetIndex__InfoTime ();
// ���������� ������� ������ �� ���� [-CreationTime]
   public: void SetIndex__CreationTime ();
// ���������� ������� ������ �� ������ ����� [InfoSourceID, -InfoTime]
   public: void SetIndex_InfoSourceID__InfoTime ();
// ���������� ������� ������ �� ���� [-ShowCount]
   public: void SetIndex__ShowCount ();
// ���������� ������� ������ �� ���� [-ClickCount]
   public: void SetIndex__ClickCount ();
// ���������� ������� ������ �� ���� [-CTR]
   public: void SetIndex__CTR ();
// ���������� ������� ������ �� ���� [-Estimation]
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
