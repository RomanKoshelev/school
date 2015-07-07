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
// Registry

void OC_Registry::About_class_OC_Master (){return;}

// Конструктор по умолчанию
OC_Registry::OC_Registry ()
{
   DEBUG_STACK_NAME (OC_Registry_OC_Registry);
   curIndexInfo.Init(); InitSmartFields(); coPtr=OBD_OpenMasterObject(classID);
}



// Деструктор контроллера объекта
OC_Registry::~OC_Registry ()
{
   DEBUG_STACK_NAME (OC_Registry_Destructor);
   Release();
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Registry::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Registry_InitSmartFields);
   classID = OBJ_CLASS_ID_Registry;
   m_NeedInitiate._init         (classID, 2, &coPtr, &OD_Registry::d_NeedInitiate         );
   m_ConceptID_Sorted._init     (classID, 3, &coPtr, &OD_Registry::d_ConceptID_Sorted     );
   m_ConceptNo_SortID._init     (classID, 4, &coPtr, &OD_Registry::d_ConceptNo_SortID     );
   m_ConceptID_SortNo._init     (classID, 5, &coPtr, &OD_Registry::d_ConceptID_SortNo     );
   m_ConceptParent_SortNo._init (classID, 6, &coPtr, &OD_Registry::d_ConceptParent_SortNo );
   m_ConceptType_SortNo._init   (classID, 7, &coPtr, &OD_Registry::d_ConceptType_SortNo   );
   m_ConceptLevel_SortNo._init  (classID, 8, &coPtr, &OD_Registry::d_ConceptLevel_SortNo  );
}


// ===============================================================================
// Relation

// Конструктор по умолчанию
OC_Relation::OC_Relation ()
{
   DEBUG_STACK_NAME (OC_Relation_OC_Relation);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Relation::OC_Relation  (identifier objID)
{
   DEBUG_STACK_NAME (OC_Relation_OC_Relation);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Relation::OC_Relation  (const OC_Relation& from)
{
   DEBUG_STACK_NAME (OC_Relation_OC_Relation);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Relation::~OC_Relation ()
{
   DEBUG_STACK_NAME (OC_Relation_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Relation& OC_Relation::operator= (const OC_Relation& from)
{
   DEBUG_STACK_NAME (OC_Relation_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Relation& OC_Relation::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_Relation_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Relation::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Relation_InitSmartFields);
   classID = OBJ_CLASS_ID_Relation;
   m_SysName._init              (classID, 2, &coPtr, &OD_Relation::d_SysName              );
   m_Name._init                 (classID, 3, &coPtr, &OD_Relation::d_Name                 );
   m_Description._init          (classID, 4, &coPtr, &OD_Relation::d_Description          );
   m_CreationTime._init         (classID, 5, &coPtr, &OD_Relation::d_CreationTime         );
   m_Version._init              (classID, 6, &coPtr, &OD_Relation::d_Version              );
   m_FieldName._init            (classID, 7, &coPtr, &OD_Relation::d_FieldName            );
   m_FieldType._init            (classID, 8, &coPtr, &OD_Relation::d_FieldType            );
   m_FieldSysName._init         (classID, 9, &coPtr, &OD_Relation::d_FieldSysName         );
   m_FieldDescription._init     (classID, 10, &coPtr, &OD_Relation::d_FieldDescription     );
   m_FieldInterfaceType._init   (classID, 11, &coPtr, &OD_Relation::d_FieldInterfaceType   );
   m_OwnerGUID._init            (classID, 12, &coPtr, &OD_Relation::d_OwnerGUID            );
   m_AccessLevelThreshold._init (classID, 13, &coPtr, &OD_Relation::d_AccessLevelThreshold );
   m_FeodGUID._init             (classID, 14, &coPtr, &OD_Relation::d_FeodGUID             );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Relation::CopyDataFrom (OC_Relation& from)
{
   DEBUG_STACK_NAME (OC_Relation_CopyDataFrom);
   m_SysName              = from.m_SysName;
   m_Name                 = from.m_Name;
   m_Description          = from.m_Description;
   m_CreationTime         = from.m_CreationTime;
   m_Version              = from.m_Version;
   m_FieldName            = from.m_FieldName;
   m_FieldType            = from.m_FieldType;
   m_FieldSysName         = from.m_FieldSysName;
   m_FieldDescription     = from.m_FieldDescription;
   m_FieldInterfaceType   = from.m_FieldInterfaceType;
   m_OwnerGUID            = from.m_OwnerGUID;
   m_AccessLevelThreshold = from.m_AccessLevelThreshold;
   m_FeodGUID             = from.m_FeodGUID;
}


// Копирование данных в другой контроллер
void OC_Relation::CopyDataTo (OC_Relation& to)
{
   DEBUG_STACK_NAME (OC_Relation_CopyDataTo);
   to.m_SysName              = m_SysName;
   to.m_Name                 = m_Name;
   to.m_Description          = m_Description;
   to.m_CreationTime         = m_CreationTime;
   to.m_Version              = m_Version;
   to.m_FieldName            = m_FieldName;
   to.m_FieldType            = m_FieldType;
   to.m_FieldSysName         = m_FieldSysName;
   to.m_FieldDescription     = m_FieldDescription;
   to.m_FieldInterfaceType   = m_FieldInterfaceType;
   to.m_OwnerGUID            = m_OwnerGUID;
   to.m_AccessLevelThreshold = m_AccessLevelThreshold;
   to.m_FeodGUID             = m_FeodGUID;
}

// Копирование данных из другого контроллера: to << from;
OC_Relation&  OC_Relation::operator << (OC_Relation& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Relation&  OC_Relation::operator >> (OC_Relation& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Relation::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_Relation_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_SysName ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Relation::GetIndex ()
{
   DEBUG_STACK_NAME (OC_Relation_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Relation::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_Relation_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_Relation::SetIndex_SysName ()
{
   DEBUG_STACK_NAME (OC_Relation_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Linkage

// Конструктор по умолчанию
OC_Linkage::OC_Linkage ()
{
   DEBUG_STACK_NAME (OC_Linkage_OC_Linkage);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Linkage::OC_Linkage  (identifier objID)
{
   DEBUG_STACK_NAME (OC_Linkage_OC_Linkage);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Linkage::OC_Linkage  (const OC_Linkage& from)
{
   DEBUG_STACK_NAME (OC_Linkage_OC_Linkage);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Linkage::~OC_Linkage ()
{
   DEBUG_STACK_NAME (OC_Linkage_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Linkage& OC_Linkage::operator= (const OC_Linkage& from)
{
   DEBUG_STACK_NAME (OC_Linkage_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Linkage& OC_Linkage::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_Linkage_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Linkage::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Linkage_InitSmartFields);
   classID = OBJ_CLASS_ID_Linkage;
   m_CreationTime._init         (classID, 2, &coPtr, &OD_Linkage::d_CreationTime         );
   m_RelationID._init           (classID, 3, &coPtr, &OD_Linkage::d_RelationID           );
   m_ProxyID._init              (classID, 4, &coPtr, &OD_Linkage::d_ProxyID              );
   m_Value._init                (classID, 5, &coPtr, &OD_Linkage::d_Value                );
   m_OwnerGUID._init            (classID, 6, &coPtr, &OD_Linkage::d_OwnerGUID            );
   m_AccessLevelThreshold._init (classID, 7, &coPtr, &OD_Linkage::d_AccessLevelThreshold );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Linkage::CopyDataFrom (OC_Linkage& from)
{
   DEBUG_STACK_NAME (OC_Linkage_CopyDataFrom);
   m_CreationTime         = from.m_CreationTime;
   m_RelationID           = from.m_RelationID;
   m_ProxyID              = from.m_ProxyID;
   m_Value                = from.m_Value;
   m_OwnerGUID            = from.m_OwnerGUID;
   m_AccessLevelThreshold = from.m_AccessLevelThreshold;
}


// Копирование данных в другой контроллер
void OC_Linkage::CopyDataTo (OC_Linkage& to)
{
   DEBUG_STACK_NAME (OC_Linkage_CopyDataTo);
   to.m_CreationTime         = m_CreationTime;
   to.m_RelationID           = m_RelationID;
   to.m_ProxyID              = m_ProxyID;
   to.m_Value                = m_Value;
   to.m_OwnerGUID            = m_OwnerGUID;
   to.m_AccessLevelThreshold = m_AccessLevelThreshold;
}

// Копирование данных из другого контроллера: to << from;
OC_Linkage&  OC_Linkage::operator << (OC_Linkage& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Linkage&  OC_Linkage::operator >> (OC_Linkage& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Linkage::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_Linkage_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_RelationID ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Linkage::GetIndex ()
{
   DEBUG_STACK_NAME (OC_Linkage_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Linkage::SetIndex_RelationID ()
{
   DEBUG_STACK_NAME (OC_Linkage_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// LinkProxy

// Конструктор по умолчанию
OC_LinkProxy::OC_LinkProxy ()
{
   DEBUG_STACK_NAME (OC_LinkProxy_OC_LinkProxy);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_LinkProxy::OC_LinkProxy  (identifier objID)
{
   DEBUG_STACK_NAME (OC_LinkProxy_OC_LinkProxy);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_LinkProxy::OC_LinkProxy  (const OC_LinkProxy& from)
{
   DEBUG_STACK_NAME (OC_LinkProxy_OC_LinkProxy);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_LinkProxy::~OC_LinkProxy ()
{
   DEBUG_STACK_NAME (OC_LinkProxy_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_LinkProxy& OC_LinkProxy::operator= (const OC_LinkProxy& from)
{
   DEBUG_STACK_NAME (OC_LinkProxy_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_LinkProxy& OC_LinkProxy::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_LinkProxy_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_LinkProxy::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_LinkProxy_InitSmartFields);
   classID = OBJ_CLASS_ID_LinkProxy;
   m_CreationTime._init  (classID, 2, &coPtr, &OD_LinkProxy::d_CreationTime  );
   m_RealObject._init    (classID, 3, &coPtr, &OD_LinkProxy::d_RealObject    );
   m_LinkageID._init     (classID, 4, &coPtr, &OD_LinkProxy::d_LinkageID     );
   m_RelationID._init    (classID, 5, &coPtr, &OD_LinkProxy::d_RelationID    );
   m_RelationField._init (classID, 6, &coPtr, &OD_LinkProxy::d_RelationField );
}


// Копирование данных из другого контроллера
void OC_LinkProxy::CopyDataFrom (OC_LinkProxy& from)
{
   DEBUG_STACK_NAME (OC_LinkProxy_CopyDataFrom);
   m_CreationTime  = from.m_CreationTime;
   m_RealObject    = from.m_RealObject;
   m_LinkageID     = from.m_LinkageID;
   m_RelationID    = from.m_RelationID;
   m_RelationField = from.m_RelationField;
}


// Копирование данных в другой контроллер
void OC_LinkProxy::CopyDataTo (OC_LinkProxy& to)
{
   DEBUG_STACK_NAME (OC_LinkProxy_CopyDataTo);
   to.m_CreationTime  = m_CreationTime;
   to.m_RealObject    = m_RealObject;
   to.m_LinkageID     = m_LinkageID;
   to.m_RelationID    = m_RelationID;
   to.m_RelationField = m_RelationField;
}

// Копирование данных из другого контроллера: to << from;
OC_LinkProxy&  OC_LinkProxy::operator << (OC_LinkProxy& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_LinkProxy&  OC_LinkProxy::operator >> (OC_LinkProxy& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// Connectable

// Конструктор по умолчанию
OC_Connectable::OC_Connectable ()
{
   DEBUG_STACK_NAME (OC_Connectable_OC_Connectable);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Connectable::OC_Connectable  (identifier objID)
{
   DEBUG_STACK_NAME (OC_Connectable_OC_Connectable);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Connectable::OC_Connectable  (const OC_Connectable& from)
{
   DEBUG_STACK_NAME (OC_Connectable_OC_Connectable);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Connectable::~OC_Connectable ()
{
   DEBUG_STACK_NAME (OC_Connectable_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Connectable& OC_Connectable::operator= (const OC_Connectable& from)
{
   DEBUG_STACK_NAME (OC_Connectable_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Connectable& OC_Connectable::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_Connectable_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Connectable::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Connectable_InitSmartFields);
   classID = OBJ_CLASS_ID_Connectable;
   m_ProxyObject._init (classID, 2, &coPtr, &OD_Connectable::d_ProxyObject );
}


// Копирование данных из другого контроллера
void OC_Connectable::CopyDataFrom (OC_Connectable& from)
{
   DEBUG_STACK_NAME (OC_Connectable_CopyDataFrom);
   m_ProxyObject = from.m_ProxyObject;
}


// Копирование данных в другой контроллер
void OC_Connectable::CopyDataTo (OC_Connectable& to)
{
   DEBUG_STACK_NAME (OC_Connectable_CopyDataTo);
   to.m_ProxyObject = m_ProxyObject;
}

// Копирование данных из другого контроллера: to << from;
OC_Connectable&  OC_Connectable::operator << (OC_Connectable& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Connectable&  OC_Connectable::operator >> (OC_Connectable& from)
{
   CopyDataTo (from);
   return *this;
}


// ===============================================================================
// MetaObject

// Конструктор по умолчанию
OC_MetaObject::OC_MetaObject ()
{
   DEBUG_STACK_NAME (OC_MetaObject_OC_MetaObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_MetaObject::OC_MetaObject  (identifier objID)
{
   DEBUG_STACK_NAME (OC_MetaObject_OC_MetaObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_MetaObject::OC_MetaObject  (const OC_MetaObject& from)
{
   DEBUG_STACK_NAME (OC_MetaObject_OC_MetaObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_MetaObject::~OC_MetaObject ()
{
   DEBUG_STACK_NAME (OC_MetaObject_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_MetaObject& OC_MetaObject::operator= (const OC_MetaObject& from)
{
   DEBUG_STACK_NAME (OC_MetaObject_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_MetaObject& OC_MetaObject::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_MetaObject_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_MetaObject::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_MetaObject_InitSmartFields);
   classID = OBJ_CLASS_ID_MetaObject;
   m_Type._init                  (classID, 2, &coPtr, &OD_MetaObject::d_Type                  );
   m_Name._init                  (classID, 3, &coPtr, &OD_MetaObject::d_Name                  );
   m_SysName._init               (classID, 4, &coPtr, &OD_MetaObject::d_SysName               );
   m_Header1._init               (classID, 5, &coPtr, &OD_MetaObject::d_Header1               );
   m_Header2._init               (classID, 6, &coPtr, &OD_MetaObject::d_Header2               );
   m_Header3._init               (classID, 7, &coPtr, &OD_MetaObject::d_Header3               );
   m_Header4._init               (classID, 8, &coPtr, &OD_MetaObject::d_Header4               );
   m_Header5._init               (classID, 9, &coPtr, &OD_MetaObject::d_Header5               );
   m_Comment._init               (classID, 10, &coPtr, &OD_MetaObject::d_Comment               );
   m_Text._init                  (classID, 11, &coPtr, &OD_MetaObject::d_Text                  );
   m_arrInt._init                (classID, 12, &coPtr, &OD_MetaObject::d_arrInt                );
   m_arrFloat._init              (classID, 13, &coPtr, &OD_MetaObject::d_arrFloat              );
   m_arrBool._init               (classID, 14, &coPtr, &OD_MetaObject::d_arrBool               );
   m_arrByte._init               (classID, 15, &coPtr, &OD_MetaObject::d_arrByte               );
   m_arrTime._init               (classID, 16, &coPtr, &OD_MetaObject::d_arrTime               );
   m_arrString._init             (classID, 17, &coPtr, &OD_MetaObject::d_arrString             );
   m_arrGUID._init               (classID, 18, &coPtr, &OD_MetaObject::d_arrGUID               );
   m_arrID._init                 (classID, 19, &coPtr, &OD_MetaObject::d_arrID                 );
   m_CreationTime._init          (classID, 20, &coPtr, &OD_MetaObject::d_CreationTime          );
   m_OwnerGUID._init             (classID, 21, &coPtr, &OD_MetaObject::d_OwnerGUID             );
   m_AccessLevelThreshold._init  (classID, 22, &coPtr, &OD_MetaObject::d_AccessLevelThreshold  );
   m_FeodGUID._init              (classID, 23, &coPtr, &OD_MetaObject::d_FeodGUID              );
   m_ProxyObject._init           (classID, 24, &coPtr, &OD_MetaObject::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 25, &coPtr, &OD_MetaObject::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 26, &coPtr, &OD_MetaObject::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 27, &coPtr, &OD_MetaObject::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 28, &coPtr, &OD_MetaObject::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_MetaObject::CopyDataFrom (OC_MetaObject& from)
{
   DEBUG_STACK_NAME (OC_MetaObject_CopyDataFrom);
   m_Type                  = from.m_Type;
   m_Name                  = from.m_Name;
   m_SysName               = from.m_SysName;
   m_Header1               = from.m_Header1;
   m_Header2               = from.m_Header2;
   m_Header3               = from.m_Header3;
   m_Header4               = from.m_Header4;
   m_Header5               = from.m_Header5;
   m_Comment               = from.m_Comment;
   m_Text                  = from.m_Text;
   m_arrInt                = from.m_arrInt;
   m_arrFloat              = from.m_arrFloat;
   m_arrBool               = from.m_arrBool;
   m_arrByte               = from.m_arrByte;
   m_arrTime               = from.m_arrTime;
   m_arrString             = from.m_arrString;
   m_arrGUID               = from.m_arrGUID;
   m_arrID                 = from.m_arrID;
   m_CreationTime          = from.m_CreationTime;
   m_OwnerGUID             = from.m_OwnerGUID;
   m_AccessLevelThreshold  = from.m_AccessLevelThreshold;
   m_FeodGUID              = from.m_FeodGUID;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_MetaObject::CopyDataTo (OC_MetaObject& to)
{
   DEBUG_STACK_NAME (OC_MetaObject_CopyDataTo);
   to.m_Type                  = m_Type;
   to.m_Name                  = m_Name;
   to.m_SysName               = m_SysName;
   to.m_Header1               = m_Header1;
   to.m_Header2               = m_Header2;
   to.m_Header3               = m_Header3;
   to.m_Header4               = m_Header4;
   to.m_Header5               = m_Header5;
   to.m_Comment               = m_Comment;
   to.m_Text                  = m_Text;
   to.m_arrInt                = m_arrInt;
   to.m_arrFloat              = m_arrFloat;
   to.m_arrBool               = m_arrBool;
   to.m_arrByte               = m_arrByte;
   to.m_arrTime               = m_arrTime;
   to.m_arrString             = m_arrString;
   to.m_arrGUID               = m_arrGUID;
   to.m_arrID                 = m_arrID;
   to.m_CreationTime          = m_CreationTime;
   to.m_OwnerGUID             = m_OwnerGUID;
   to.m_AccessLevelThreshold  = m_AccessLevelThreshold;
   to.m_FeodGUID              = m_FeodGUID;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_MetaObject&  OC_MetaObject::operator << (OC_MetaObject& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_MetaObject&  OC_MetaObject::operator >> (OC_MetaObject& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_MetaObject::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_MetaObject_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Type_Name ();
              return oldIndex;
      case 1: SetIndex_Type_SysName ();
              return oldIndex;
      case 2: SetIndex_Type_Header1_Header2_Header3_Header4_Header5 ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_MetaObject::GetIndex ()
{
   DEBUG_STACK_NAME (OC_MetaObject_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_MetaObject::SetIndex_Type_Name ()
{
   DEBUG_STACK_NAME (OC_MetaObject_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_MetaObject::SetIndex_Type_SysName ()
{
   DEBUG_STACK_NAME (OC_MetaObject_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_MetaObject::SetIndex_Type_Header1_Header2_Header3_Header4_Header5 ()
{
   DEBUG_STACK_NAME (OC_MetaObject_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 6; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
   curIndexInfo.m_keyType[2] = (byte)FT_string; 
   curIndexInfo.m_keyType[3] = (byte)FT_string; 
   curIndexInfo.m_keyType[4] = (byte)FT_string; 
   curIndexInfo.m_keyType[5] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Concept

// Конструктор по умолчанию
OC_Concept::OC_Concept ()
{
   DEBUG_STACK_NAME (OC_Concept_OC_Concept);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Concept::OC_Concept  (identifier objID)
{
   DEBUG_STACK_NAME (OC_Concept_OC_Concept);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Concept::OC_Concept  (const OC_Concept& from)
{
   DEBUG_STACK_NAME (OC_Concept_OC_Concept);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Concept::~OC_Concept ()
{
   DEBUG_STACK_NAME (OC_Concept_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Concept& OC_Concept::operator= (const OC_Concept& from)
{
   DEBUG_STACK_NAME (OC_Concept_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Concept& OC_Concept::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_Concept_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Concept::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Concept_InitSmartFields);
   classID = OBJ_CLASS_ID_Concept;
   m_Name._init                  (classID, 2, &coPtr, &OD_Concept::d_Name                  );
   m_Description._init           (classID, 3, &coPtr, &OD_Concept::d_Description           );
   m_Type._init                  (classID, 4, &coPtr, &OD_Concept::d_Type                  );
   m_TypeNo._init                (classID, 5, &coPtr, &OD_Concept::d_TypeNo                );
   m_Parent._init                (classID, 6, &coPtr, &OD_Concept::d_Parent                );
   m_Ancestor._init              (classID, 7, &coPtr, &OD_Concept::d_Ancestor              );
   m_AncestorNo._init            (classID, 8, &coPtr, &OD_Concept::d_AncestorNo            );
   m_AncestorWeight._init        (classID, 9, &coPtr, &OD_Concept::d_AncestorWeight        );
   m_AllAncestor._init           (classID, 10, &coPtr, &OD_Concept::d_AllAncestor           );
   m_AllAncestorNo._init         (classID, 11, &coPtr, &OD_Concept::d_AllAncestorNo         );
   m_Child._init                 (classID, 12, &coPtr, &OD_Concept::d_Child                 );
   m_ChildNo._init               (classID, 13, &coPtr, &OD_Concept::d_ChildNo               );
   m_Descendant._init            (classID, 14, &coPtr, &OD_Concept::d_Descendant            );
   m_DescendantNo._init          (classID, 15, &coPtr, &OD_Concept::d_DescendantNo          );
   m_Level._init                 (classID, 16, &coPtr, &OD_Concept::d_Level                 );
   m_No._init                    (classID, 17, &coPtr, &OD_Concept::d_No                    );
   m_FIELD_Extension_Name._init  (classID, 18, &coPtr, &OD_Concept::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 19, &coPtr, &OD_Concept::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 20, &coPtr, &OD_Concept::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 21, &coPtr, &OD_Concept::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Concept::CopyDataFrom (OC_Concept& from)
{
   DEBUG_STACK_NAME (OC_Concept_CopyDataFrom);
   m_Name                  = from.m_Name;
   m_Description           = from.m_Description;
   m_Type                  = from.m_Type;
   m_TypeNo                = from.m_TypeNo;
   m_Parent                = from.m_Parent;
   m_Ancestor              = from.m_Ancestor;
   m_AncestorNo            = from.m_AncestorNo;
   m_AncestorWeight        = from.m_AncestorWeight;
   m_AllAncestor           = from.m_AllAncestor;
   m_AllAncestorNo         = from.m_AllAncestorNo;
   m_Child                 = from.m_Child;
   m_ChildNo               = from.m_ChildNo;
   m_Descendant            = from.m_Descendant;
   m_DescendantNo          = from.m_DescendantNo;
   m_Level                 = from.m_Level;
   m_No                    = from.m_No;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_Concept::CopyDataTo (OC_Concept& to)
{
   DEBUG_STACK_NAME (OC_Concept_CopyDataTo);
   to.m_Name                  = m_Name;
   to.m_Description           = m_Description;
   to.m_Type                  = m_Type;
   to.m_TypeNo                = m_TypeNo;
   to.m_Parent                = m_Parent;
   to.m_Ancestor              = m_Ancestor;
   to.m_AncestorNo            = m_AncestorNo;
   to.m_AncestorWeight        = m_AncestorWeight;
   to.m_AllAncestor           = m_AllAncestor;
   to.m_AllAncestorNo         = m_AllAncestorNo;
   to.m_Child                 = m_Child;
   to.m_ChildNo               = m_ChildNo;
   to.m_Descendant            = m_Descendant;
   to.m_DescendantNo          = m_DescendantNo;
   to.m_Level                 = m_Level;
   to.m_No                    = m_No;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_Concept&  OC_Concept::operator << (OC_Concept& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Concept&  OC_Concept::operator >> (OC_Concept& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Concept::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_Level ();
              return oldIndex;
      case 2: SetIndex_No ();
              return oldIndex;
      case 3: SetIndex_Type_Level ();
              return oldIndex;
      case 4: SetIndex_TypeNo ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Concept::GetIndex ()
{
   DEBUG_STACK_NAME (OC_Concept_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Concept::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_Concept::SetIndex_Level ()
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Concept::SetIndex_No ()
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_Concept::SetIndex_Type_Level ()
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_Concept::SetIndex_TypeNo ()
{
   DEBUG_STACK_NAME (OC_Concept_SetIndex_xxx);
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// User

// Конструктор по умолчанию
OC_User::OC_User ()
{
   DEBUG_STACK_NAME (OC_User_OC_User);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_User::OC_User  (identifier objID)
{
   DEBUG_STACK_NAME (OC_User_OC_User);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_User::OC_User  (const OC_User& from)
{
   DEBUG_STACK_NAME (OC_User_OC_User);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_User::~OC_User ()
{
   DEBUG_STACK_NAME (OC_User_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_User& OC_User::operator= (const OC_User& from)
{
   DEBUG_STACK_NAME (OC_User_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_User& OC_User::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_User_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_User::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_User_InitSmartFields);
   classID = OBJ_CLASS_ID_User;
   m_Login._init                 (classID, 2, &coPtr, &OD_User::d_Login                 );
   m_Password._init              (classID, 3, &coPtr, &OD_User::d_Password              );
   m_PasswordInBrowser._init     (classID, 4, &coPtr, &OD_User::d_PasswordInBrowser     );
   m_CreationTime._init          (classID, 5, &coPtr, &OD_User::d_CreationTime          );
   m_FullName._init              (classID, 6, &coPtr, &OD_User::d_FullName              );
   m_Email._init                 (classID, 7, &coPtr, &OD_User::d_Email                 );
   m_URL._init                   (classID, 8, &coPtr, &OD_User::d_URL                   );
   m_Data._init                  (classID, 9, &coPtr, &OD_User::d_Data                  );
   m_AccessLevel._init           (classID, 10, &coPtr, &OD_User::d_AccessLevel           );
   m_GroupID._init               (classID, 11, &coPtr, &OD_User::d_GroupID               );
   m_OwnFeodID._init             (classID, 12, &coPtr, &OD_User::d_OwnFeodID             );
   m_ProxyObject._init           (classID, 13, &coPtr, &OD_User::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 14, &coPtr, &OD_User::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 15, &coPtr, &OD_User::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 16, &coPtr, &OD_User::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 17, &coPtr, &OD_User::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_User::CopyDataFrom (OC_User& from)
{
   DEBUG_STACK_NAME (OC_User_CopyDataFrom);
   m_Login                 = from.m_Login;
   m_Password              = from.m_Password;
   m_PasswordInBrowser     = from.m_PasswordInBrowser;
   m_CreationTime          = from.m_CreationTime;
   m_FullName              = from.m_FullName;
   m_Email                 = from.m_Email;
   m_URL                   = from.m_URL;
   m_Data                  = from.m_Data;
   m_AccessLevel           = from.m_AccessLevel;
   m_GroupID               = from.m_GroupID;
   m_OwnFeodID             = from.m_OwnFeodID;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_User::CopyDataTo (OC_User& to)
{
   DEBUG_STACK_NAME (OC_User_CopyDataTo);
   to.m_Login                 = m_Login;
   to.m_Password              = m_Password;
   to.m_PasswordInBrowser     = m_PasswordInBrowser;
   to.m_CreationTime          = m_CreationTime;
   to.m_FullName              = m_FullName;
   to.m_Email                 = m_Email;
   to.m_URL                   = m_URL;
   to.m_Data                  = m_Data;
   to.m_AccessLevel           = m_AccessLevel;
   to.m_GroupID               = m_GroupID;
   to.m_OwnFeodID             = m_OwnFeodID;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_User&  OC_User::operator << (OC_User& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_User&  OC_User::operator >> (OC_User& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_User::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_User_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Login ();
              return oldIndex;
      case 1: SetIndex_FullName ();
              return oldIndex;
      case 2: SetIndex__CreationTime ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_User::GetIndex ()
{
   DEBUG_STACK_NAME (OC_User_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_User::SetIndex_Login ()
{
   DEBUG_STACK_NAME (OC_User_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_User::SetIndex_FullName ()
{
   DEBUG_STACK_NAME (OC_User_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_User::SetIndex__CreationTime ()
{
   DEBUG_STACK_NAME (OC_User_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// UserGroup

// Конструктор по умолчанию
OC_UserGroup::OC_UserGroup ()
{
   DEBUG_STACK_NAME (OC_UserGroup_OC_UserGroup);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_UserGroup::OC_UserGroup  (identifier objID)
{
   DEBUG_STACK_NAME (OC_UserGroup_OC_UserGroup);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_UserGroup::OC_UserGroup  (const OC_UserGroup& from)
{
   DEBUG_STACK_NAME (OC_UserGroup_OC_UserGroup);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_UserGroup::~OC_UserGroup ()
{
   DEBUG_STACK_NAME (OC_UserGroup_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_UserGroup& OC_UserGroup::operator= (const OC_UserGroup& from)
{
   DEBUG_STACK_NAME (OC_UserGroup_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_UserGroup& OC_UserGroup::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_UserGroup_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_UserGroup::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_UserGroup_InitSmartFields);
   classID = OBJ_CLASS_ID_UserGroup;
   m_Name._init                  (classID, 2, &coPtr, &OD_UserGroup::d_Name                  );
   m_Type._init                  (classID, 3, &coPtr, &OD_UserGroup::d_Type                  );
   m_Description._init           (classID, 4, &coPtr, &OD_UserGroup::d_Description           );
   m_CreationTime._init          (classID, 5, &coPtr, &OD_UserGroup::d_CreationTime          );
   m_OwnerGUID._init             (classID, 6, &coPtr, &OD_UserGroup::d_OwnerGUID             );
   m_AccessLevelThreshold._init  (classID, 7, &coPtr, &OD_UserGroup::d_AccessLevelThreshold  );
   m_UserID._init                (classID, 8, &coPtr, &OD_UserGroup::d_UserID                );
   m_Rights_Feod._init           (classID, 9, &coPtr, &OD_UserGroup::d_Rights_Feod           );
   m_Rights_Attr._init           (classID, 10, &coPtr, &OD_UserGroup::d_Rights_Attr           );
   m_ProxyObject._init           (classID, 11, &coPtr, &OD_UserGroup::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 12, &coPtr, &OD_UserGroup::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 13, &coPtr, &OD_UserGroup::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 14, &coPtr, &OD_UserGroup::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 15, &coPtr, &OD_UserGroup::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_UserGroup::CopyDataFrom (OC_UserGroup& from)
{
   DEBUG_STACK_NAME (OC_UserGroup_CopyDataFrom);
   m_Name                  = from.m_Name;
   m_Type                  = from.m_Type;
   m_Description           = from.m_Description;
   m_CreationTime          = from.m_CreationTime;
   m_OwnerGUID             = from.m_OwnerGUID;
   m_AccessLevelThreshold  = from.m_AccessLevelThreshold;
   m_UserID                = from.m_UserID;
   m_Rights_Feod           = from.m_Rights_Feod;
   m_Rights_Attr           = from.m_Rights_Attr;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_UserGroup::CopyDataTo (OC_UserGroup& to)
{
   DEBUG_STACK_NAME (OC_UserGroup_CopyDataTo);
   to.m_Name                  = m_Name;
   to.m_Type                  = m_Type;
   to.m_Description           = m_Description;
   to.m_CreationTime          = m_CreationTime;
   to.m_OwnerGUID             = m_OwnerGUID;
   to.m_AccessLevelThreshold  = m_AccessLevelThreshold;
   to.m_UserID                = m_UserID;
   to.m_Rights_Feod           = m_Rights_Feod;
   to.m_Rights_Attr           = m_Rights_Attr;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_UserGroup&  OC_UserGroup::operator << (OC_UserGroup& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_UserGroup&  OC_UserGroup::operator >> (OC_UserGroup& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_UserGroup::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_UserGroup_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_Type ();
              return oldIndex;
      case 2: SetIndex_CreationTime ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_UserGroup::GetIndex ()
{
   DEBUG_STACK_NAME (OC_UserGroup_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_UserGroup::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_UserGroup_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_UserGroup::SetIndex_Type ()
{
   DEBUG_STACK_NAME (OC_UserGroup_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_UserGroup::SetIndex_CreationTime ()
{
   DEBUG_STACK_NAME (OC_UserGroup_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// Text

// Конструктор по умолчанию
OC_Text::OC_Text ()
{
   DEBUG_STACK_NAME (OC_Text_OC_Text);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_Text::OC_Text  (identifier objID)
{
   DEBUG_STACK_NAME (OC_Text_OC_Text);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_Text::OC_Text  (const OC_Text& from)
{
   DEBUG_STACK_NAME (OC_Text_OC_Text);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_Text::~OC_Text ()
{
   DEBUG_STACK_NAME (OC_Text_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_Text& OC_Text::operator= (const OC_Text& from)
{
   DEBUG_STACK_NAME (OC_Text_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Text& OC_Text::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_Text_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_Text::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_Text_InitSmartFields);
   classID = OBJ_CLASS_ID_Text;
   m_Name._init         (classID, 2, &coPtr, &OD_Text::d_Name         );
   m_Text._init         (classID, 3, &coPtr, &OD_Text::d_Text         );
   m_CreationTime._init (classID, 4, &coPtr, &OD_Text::d_CreationTime );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_Text::CopyDataFrom (OC_Text& from)
{
   DEBUG_STACK_NAME (OC_Text_CopyDataFrom);
   m_Name         = from.m_Name;
   m_Text         = from.m_Text;
   m_CreationTime = from.m_CreationTime;
}


// Копирование данных в другой контроллер
void OC_Text::CopyDataTo (OC_Text& to)
{
   DEBUG_STACK_NAME (OC_Text_CopyDataTo);
   to.m_Name         = m_Name;
   to.m_Text         = m_Text;
   to.m_CreationTime = m_CreationTime;
}

// Копирование данных из другого контроллера: to << from;
OC_Text&  OC_Text::operator << (OC_Text& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_Text&  OC_Text::operator >> (OC_Text& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_Text::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_Text_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_Text::GetIndex ()
{
   DEBUG_STACK_NAME (OC_Text_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_Text::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_Text_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// MorphologicRule

// Конструктор по умолчанию
OC_MorphologicRule::OC_MorphologicRule ()
{
   DEBUG_STACK_NAME (OC_MorphologicRule_OC_MorphologicRule);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_MorphologicRule::OC_MorphologicRule  (identifier objID)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_OC_MorphologicRule);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_MorphologicRule::OC_MorphologicRule  (const OC_MorphologicRule& from)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_OC_MorphologicRule);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_MorphologicRule::~OC_MorphologicRule ()
{
   DEBUG_STACK_NAME (OC_MorphologicRule_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_MorphologicRule& OC_MorphologicRule::operator= (const OC_MorphologicRule& from)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_MorphologicRule& OC_MorphologicRule::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_MorphologicRule::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_InitSmartFields);
   classID = OBJ_CLASS_ID_MorphologicRule;
   m_Attribute._init         (classID, 2, &coPtr, &OD_MorphologicRule::d_Attribute         );
   m_BaseEnd_Available._init (classID, 3, &coPtr, &OD_MorphologicRule::d_BaseEnd_Available );
   m_BaseEnd_Exception._init (classID, 4, &coPtr, &OD_MorphologicRule::d_BaseEnd_Exception );
   m_AffixNormal._init       (classID, 5, &coPtr, &OD_MorphologicRule::d_AffixNormal       );
   m_AffixVariant._init      (classID, 6, &coPtr, &OD_MorphologicRule::d_AffixVariant      );
   m_Comment._init           (classID, 7, &coPtr, &OD_MorphologicRule::d_Comment           );
   m_Number._init            (classID, 8, &coPtr, &OD_MorphologicRule::d_Number            );
   m_MatchCount._init        (classID, 9, &coPtr, &OD_MorphologicRule::d_MatchCount        );
   m_ApplyCount._init        (classID, 10, &coPtr, &OD_MorphologicRule::d_ApplyCount        );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_MorphologicRule::CopyDataFrom (OC_MorphologicRule& from)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_CopyDataFrom);
   m_Attribute         = from.m_Attribute;
   m_BaseEnd_Available = from.m_BaseEnd_Available;
   m_BaseEnd_Exception = from.m_BaseEnd_Exception;
   m_AffixNormal       = from.m_AffixNormal;
   m_AffixVariant      = from.m_AffixVariant;
   m_Comment           = from.m_Comment;
   m_Number            = from.m_Number;
   m_MatchCount        = from.m_MatchCount;
   m_ApplyCount        = from.m_ApplyCount;
}


// Копирование данных в другой контроллер
void OC_MorphologicRule::CopyDataTo (OC_MorphologicRule& to)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_CopyDataTo);
   to.m_Attribute         = m_Attribute;
   to.m_BaseEnd_Available = m_BaseEnd_Available;
   to.m_BaseEnd_Exception = m_BaseEnd_Exception;
   to.m_AffixNormal       = m_AffixNormal;
   to.m_AffixVariant      = m_AffixVariant;
   to.m_Comment           = m_Comment;
   to.m_Number            = m_Number;
   to.m_MatchCount        = m_MatchCount;
   to.m_ApplyCount        = m_ApplyCount;
}

// Копирование данных из другого контроллера: to << from;
OC_MorphologicRule&  OC_MorphologicRule::operator << (OC_MorphologicRule& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_MorphologicRule&  OC_MorphologicRule::operator >> (OC_MorphologicRule& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_MorphologicRule::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_MorphologicRule_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_AffixVariant ();
              return oldIndex;
      case 1: SetIndex_Attribute_AffixNormal_AffixVariant ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_MorphologicRule::GetIndex ()
{
   DEBUG_STACK_NAME (OC_MorphologicRule_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_MorphologicRule::SetIndex_AffixVariant ()
{
   DEBUG_STACK_NAME (OC_MorphologicRule_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_MorphologicRule::SetIndex_Attribute_AffixNormal_AffixVariant ()
{
   DEBUG_STACK_NAME (OC_MorphologicRule_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_byte; 
   curIndexInfo.m_keyType[1] = (byte)FT_string; 
   curIndexInfo.m_keyType[2] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// SearchItem

// Конструктор по умолчанию
OC_SearchItem::OC_SearchItem ()
{
   DEBUG_STACK_NAME (OC_SearchItem_OC_SearchItem);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_SearchItem::OC_SearchItem  (identifier objID)
{
   DEBUG_STACK_NAME (OC_SearchItem_OC_SearchItem);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_SearchItem::OC_SearchItem  (const OC_SearchItem& from)
{
   DEBUG_STACK_NAME (OC_SearchItem_OC_SearchItem);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_SearchItem::~OC_SearchItem ()
{
   DEBUG_STACK_NAME (OC_SearchItem_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_SearchItem& OC_SearchItem::operator= (const OC_SearchItem& from)
{
   DEBUG_STACK_NAME (OC_SearchItem_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_SearchItem& OC_SearchItem::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_SearchItem_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_SearchItem::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_SearchItem_InitSmartFields);
   classID = OBJ_CLASS_ID_SearchItem;
   m_NormalWord._init             (classID, 2, &coPtr, &OD_SearchItem::d_NormalWord             );
   m_NormalWordInv._init          (classID, 3, &coPtr, &OD_SearchItem::d_NormalWordInv          );
   m_Attributes._init             (classID, 4, &coPtr, &OD_SearchItem::d_Attributes             );
   m_Hypothesis._init             (classID, 5, &coPtr, &OD_SearchItem::d_Hypothesis             );
   m_Text_Number._init            (classID, 6, &coPtr, &OD_SearchItem::d_Text_Number            );
   m_Text_ObjectSortedGUID._init  (classID, 7, &coPtr, &OD_SearchItem::d_Text_ObjectSortedGUID  );
   m_Text_ModificationTime._init  (classID, 8, &coPtr, &OD_SearchItem::d_Text_ModificationTime  );
   m_Text_WordAppearanceNum._init (classID, 9, &coPtr, &OD_SearchItem::d_Text_WordAppearanceNum );
   m_Text_WordFirstPosition._init (classID, 10, &coPtr, &OD_SearchItem::d_Text_WordFirstPosition );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_SearchItem::CopyDataFrom (OC_SearchItem& from)
{
   DEBUG_STACK_NAME (OC_SearchItem_CopyDataFrom);
   m_NormalWord             = from.m_NormalWord;
   m_NormalWordInv          = from.m_NormalWordInv;
   m_Attributes             = from.m_Attributes;
   m_Hypothesis             = from.m_Hypothesis;
   m_Text_Number            = from.m_Text_Number;
   m_Text_ObjectSortedGUID  = from.m_Text_ObjectSortedGUID;
   m_Text_ModificationTime  = from.m_Text_ModificationTime;
   m_Text_WordAppearanceNum = from.m_Text_WordAppearanceNum;
   m_Text_WordFirstPosition = from.m_Text_WordFirstPosition;
}


// Копирование данных в другой контроллер
void OC_SearchItem::CopyDataTo (OC_SearchItem& to)
{
   DEBUG_STACK_NAME (OC_SearchItem_CopyDataTo);
   to.m_NormalWord             = m_NormalWord;
   to.m_NormalWordInv          = m_NormalWordInv;
   to.m_Attributes             = m_Attributes;
   to.m_Hypothesis             = m_Hypothesis;
   to.m_Text_Number            = m_Text_Number;
   to.m_Text_ObjectSortedGUID  = m_Text_ObjectSortedGUID;
   to.m_Text_ModificationTime  = m_Text_ModificationTime;
   to.m_Text_WordAppearanceNum = m_Text_WordAppearanceNum;
   to.m_Text_WordFirstPosition = m_Text_WordFirstPosition;
}

// Копирование данных из другого контроллера: to << from;
OC_SearchItem&  OC_SearchItem::operator << (OC_SearchItem& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_SearchItem&  OC_SearchItem::operator >> (OC_SearchItem& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_SearchItem::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_SearchItem_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_NormalWord_Hypothesis ();
              return oldIndex;
      case 1: SetIndex_NormalWordInv ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_SearchItem::GetIndex ()
{
   DEBUG_STACK_NAME (OC_SearchItem_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по набору полей
void OC_SearchItem::SetIndex_NormalWord_Hypothesis ()
{
   DEBUG_STACK_NAME (OC_SearchItem_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
   curIndexInfo.m_keyType[1] = (byte)FT_bool; 
};

// Установить текущий индекс по полю
void OC_SearchItem::SetIndex_NormalWordInv ()
{
   DEBUG_STACK_NAME (OC_SearchItem_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// StopWord

// Конструктор по умолчанию
OC_StopWord::OC_StopWord ()
{
   DEBUG_STACK_NAME (OC_StopWord_OC_StopWord);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_StopWord::OC_StopWord  (identifier objID)
{
   DEBUG_STACK_NAME (OC_StopWord_OC_StopWord);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_StopWord::OC_StopWord  (const OC_StopWord& from)
{
   DEBUG_STACK_NAME (OC_StopWord_OC_StopWord);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_StopWord::~OC_StopWord ()
{
   DEBUG_STACK_NAME (OC_StopWord_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_StopWord& OC_StopWord::operator= (const OC_StopWord& from)
{
   DEBUG_STACK_NAME (OC_StopWord_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_StopWord& OC_StopWord::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_StopWord_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_StopWord::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_StopWord_InitSmartFields);
   classID = OBJ_CLASS_ID_StopWord;
   m_Word._init (classID, 2, &coPtr, &OD_StopWord::d_Word );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_StopWord::CopyDataFrom (OC_StopWord& from)
{
   DEBUG_STACK_NAME (OC_StopWord_CopyDataFrom);
   m_Word = from.m_Word;
}


// Копирование данных в другой контроллер
void OC_StopWord::CopyDataTo (OC_StopWord& to)
{
   DEBUG_STACK_NAME (OC_StopWord_CopyDataTo);
   to.m_Word = m_Word;
}

// Копирование данных из другого контроллера: to << from;
OC_StopWord&  OC_StopWord::operator << (OC_StopWord& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_StopWord&  OC_StopWord::operator >> (OC_StopWord& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_StopWord::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_StopWord_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Word ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_StopWord::GetIndex ()
{
   DEBUG_STACK_NAME (OC_StopWord_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_StopWord::SetIndex_Word ()
{
   DEBUG_STACK_NAME (OC_StopWord_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// WordNibbleABC

// Конструктор по умолчанию
OC_WordNibbleABC::OC_WordNibbleABC ()
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_OC_WordNibbleABC);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_WordNibbleABC::OC_WordNibbleABC  (identifier objID)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_OC_WordNibbleABC);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_WordNibbleABC::OC_WordNibbleABC  (const OC_WordNibbleABC& from)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_OC_WordNibbleABC);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_WordNibbleABC::~OC_WordNibbleABC ()
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_WordNibbleABC& OC_WordNibbleABC::operator= (const OC_WordNibbleABC& from)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_WordNibbleABC& OC_WordNibbleABC::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_WordNibbleABC::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_InitSmartFields);
   classID = OBJ_CLASS_ID_WordNibbleABC;
   m_Nibble._init         (classID, 2, &coPtr, &OD_WordNibbleABC::d_Nibble         );
   m_Num._init            (classID, 3, &coPtr, &OD_WordNibbleABC::d_Num            );
   m_FreqPerMillion._init (classID, 4, &coPtr, &OD_WordNibbleABC::d_FreqPerMillion );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_WordNibbleABC::CopyDataFrom (OC_WordNibbleABC& from)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_CopyDataFrom);
   m_Nibble         = from.m_Nibble;
   m_Num            = from.m_Num;
   m_FreqPerMillion = from.m_FreqPerMillion;
}


// Копирование данных в другой контроллер
void OC_WordNibbleABC::CopyDataTo (OC_WordNibbleABC& to)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_CopyDataTo);
   to.m_Nibble         = m_Nibble;
   to.m_Num            = m_Num;
   to.m_FreqPerMillion = m_FreqPerMillion;
}

// Копирование данных из другого контроллера: to << from;
OC_WordNibbleABC&  OC_WordNibbleABC::operator << (OC_WordNibbleABC& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_WordNibbleABC&  OC_WordNibbleABC::operator >> (OC_WordNibbleABC& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_WordNibbleABC::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Nibble ();
              return oldIndex;
      case 1: SetIndex_FreqPerMillion ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_WordNibbleABC::GetIndex ()
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_WordNibbleABC::SetIndex_Nibble ()
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_WordNibbleABC::SetIndex_FreqPerMillion ()
{
   DEBUG_STACK_NAME (OC_WordNibbleABC_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// WebFolder

// Конструктор по умолчанию
OC_WebFolder::OC_WebFolder ()
{
   DEBUG_STACK_NAME (OC_WebFolder_OC_WebFolder);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_WebFolder::OC_WebFolder  (identifier objID)
{
   DEBUG_STACK_NAME (OC_WebFolder_OC_WebFolder);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_WebFolder::OC_WebFolder  (const OC_WebFolder& from)
{
   DEBUG_STACK_NAME (OC_WebFolder_OC_WebFolder);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_WebFolder::~OC_WebFolder ()
{
   DEBUG_STACK_NAME (OC_WebFolder_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_WebFolder& OC_WebFolder::operator= (const OC_WebFolder& from)
{
   DEBUG_STACK_NAME (OC_WebFolder_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_WebFolder& OC_WebFolder::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_WebFolder_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_WebFolder::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_WebFolder_InitSmartFields);
   classID = OBJ_CLASS_ID_WebFolder;
   m_WebFileSortedID._init       (classID, 2, &coPtr, &OD_WebFolder::d_WebFileSortedID       );
   m_ShowCount._init             (classID, 3, &coPtr, &OD_WebFolder::d_ShowCount             );
   m_ClickCount._init            (classID, 4, &coPtr, &OD_WebFolder::d_ClickCount            );
   m_CTR._init                   (classID, 5, &coPtr, &OD_WebFolder::d_CTR                   );
   m_Estimation_Tot._init        (classID, 6, &coPtr, &OD_WebFolder::d_Estimation_Tot        );
   m_Estimation_Num._init        (classID, 7, &coPtr, &OD_WebFolder::d_Estimation_Num        );
   m_Estimation._init            (classID, 8, &coPtr, &OD_WebFolder::d_Estimation            );
   m_ProxyObject._init           (classID, 9, &coPtr, &OD_WebFolder::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 10, &coPtr, &OD_WebFolder::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 11, &coPtr, &OD_WebFolder::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 12, &coPtr, &OD_WebFolder::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 13, &coPtr, &OD_WebFolder::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_WebFolder::CopyDataFrom (OC_WebFolder& from)
{
   DEBUG_STACK_NAME (OC_WebFolder_CopyDataFrom);
   m_WebFileSortedID       = from.m_WebFileSortedID;
   m_ShowCount             = from.m_ShowCount;
   m_ClickCount            = from.m_ClickCount;
   m_CTR                   = from.m_CTR;
   m_Estimation_Tot        = from.m_Estimation_Tot;
   m_Estimation_Num        = from.m_Estimation_Num;
   m_Estimation            = from.m_Estimation;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_WebFolder::CopyDataTo (OC_WebFolder& to)
{
   DEBUG_STACK_NAME (OC_WebFolder_CopyDataTo);
   to.m_WebFileSortedID       = m_WebFileSortedID;
   to.m_ShowCount             = m_ShowCount;
   to.m_ClickCount            = m_ClickCount;
   to.m_CTR                   = m_CTR;
   to.m_Estimation_Tot        = m_Estimation_Tot;
   to.m_Estimation_Num        = m_Estimation_Num;
   to.m_Estimation            = m_Estimation;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_WebFolder&  OC_WebFolder::operator << (OC_WebFolder& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_WebFolder&  OC_WebFolder::operator >> (OC_WebFolder& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_WebFolder::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_WebFolder_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex__ShowCount ();
              return oldIndex;
      case 1: SetIndex__ClickCount ();
              return oldIndex;
      case 2: SetIndex__CTR ();
              return oldIndex;
      case 3: SetIndex__Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_WebFolder::GetIndex ()
{
   DEBUG_STACK_NAME (OC_WebFolder_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_WebFolder::SetIndex__ShowCount ()
{
   DEBUG_STACK_NAME (OC_WebFolder_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFolder::SetIndex__ClickCount ()
{
   DEBUG_STACK_NAME (OC_WebFolder_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFolder::SetIndex__CTR ()
{
   DEBUG_STACK_NAME (OC_WebFolder_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_WebFolder::SetIndex__Estimation ()
{
   DEBUG_STACK_NAME (OC_WebFolder_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// WebFile

// Конструктор по умолчанию
OC_WebFile::OC_WebFile ()
{
   DEBUG_STACK_NAME (OC_WebFile_OC_WebFile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_WebFile::OC_WebFile  (identifier objID)
{
   DEBUG_STACK_NAME (OC_WebFile_OC_WebFile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_WebFile::OC_WebFile  (const OC_WebFile& from)
{
   DEBUG_STACK_NAME (OC_WebFile_OC_WebFile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_WebFile::~OC_WebFile ()
{
   DEBUG_STACK_NAME (OC_WebFile_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_WebFile& OC_WebFile::operator= (const OC_WebFile& from)
{
   DEBUG_STACK_NAME (OC_WebFile_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_WebFile& OC_WebFile::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_WebFile_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_WebFile::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_WebFile_InitSmartFields);
   classID = OBJ_CLASS_ID_WebFile;
   m_Name_OSFile._init           (classID, 2, &coPtr, &OD_WebFile::d_Name_OSFile           );
   m_Name_Upload._init           (classID, 3, &coPtr, &OD_WebFile::d_Name_Upload           );
   m_MIMEType._init              (classID, 4, &coPtr, &OD_WebFile::d_MIMEType              );
   m_IconType._init              (classID, 5, &coPtr, &OD_WebFile::d_IconType              );
   m_WebFolderID._init           (classID, 6, &coPtr, &OD_WebFile::d_WebFolderID           );
   m_OwnerGUID._init             (classID, 7, &coPtr, &OD_WebFile::d_OwnerGUID             );
   m_AccessLevelThreshold._init  (classID, 8, &coPtr, &OD_WebFile::d_AccessLevelThreshold  );
   m_CreationTime._init          (classID, 9, &coPtr, &OD_WebFile::d_CreationTime          );
   m_ModificationTime._init      (classID, 10, &coPtr, &OD_WebFile::d_ModificationTime      );
   m_LastAccessTime._init        (classID, 11, &coPtr, &OD_WebFile::d_LastAccessTime        );
   m_Version._init               (classID, 12, &coPtr, &OD_WebFile::d_Version               );
   m_BinaryData._init            (classID, 13, &coPtr, &OD_WebFile::d_BinaryData            );
   m_ShowCount._init             (classID, 14, &coPtr, &OD_WebFile::d_ShowCount             );
   m_ClickCount._init            (classID, 15, &coPtr, &OD_WebFile::d_ClickCount            );
   m_CTR._init                   (classID, 16, &coPtr, &OD_WebFile::d_CTR                   );
   m_Estimation_Tot._init        (classID, 17, &coPtr, &OD_WebFile::d_Estimation_Tot        );
   m_Estimation_Num._init        (classID, 18, &coPtr, &OD_WebFile::d_Estimation_Num        );
   m_Estimation._init            (classID, 19, &coPtr, &OD_WebFile::d_Estimation            );
   m_ProxyObject._init           (classID, 20, &coPtr, &OD_WebFile::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 21, &coPtr, &OD_WebFile::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 22, &coPtr, &OD_WebFile::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 23, &coPtr, &OD_WebFile::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 24, &coPtr, &OD_WebFile::d_MOD_Extension_GUID    );
   m_Name._init                  (classID, 25, &coPtr, &OD_WebFile::d_Name                  );
   m_Description._init           (classID, 26, &coPtr, &OD_WebFile::d_Description           );
   m_Text._init                  (classID, 27, &coPtr, &OD_WebFile::d_Text                  );
   m_Additional._init            (classID, 28, &coPtr, &OD_WebFile::d_Additional            );
   m_SearchItemID._init          (classID, 29, &coPtr, &OD_WebFile::d_SearchItemID          );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_WebFile::CopyDataFrom (OC_WebFile& from)
{
   DEBUG_STACK_NAME (OC_WebFile_CopyDataFrom);
   m_Name_OSFile           = from.m_Name_OSFile;
   m_Name_Upload           = from.m_Name_Upload;
   m_MIMEType              = from.m_MIMEType;
   m_IconType              = from.m_IconType;
   m_WebFolderID           = from.m_WebFolderID;
   m_OwnerGUID             = from.m_OwnerGUID;
   m_AccessLevelThreshold  = from.m_AccessLevelThreshold;
   m_CreationTime          = from.m_CreationTime;
   m_ModificationTime      = from.m_ModificationTime;
   m_LastAccessTime        = from.m_LastAccessTime;
   m_Version               = from.m_Version;
   m_BinaryData            = from.m_BinaryData;
   m_ShowCount             = from.m_ShowCount;
   m_ClickCount            = from.m_ClickCount;
   m_CTR                   = from.m_CTR;
   m_Estimation_Tot        = from.m_Estimation_Tot;
   m_Estimation_Num        = from.m_Estimation_Num;
   m_Estimation            = from.m_Estimation;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
   m_Name                  = from.m_Name;
   m_Description           = from.m_Description;
   m_Text                  = from.m_Text;
   m_Additional            = from.m_Additional;
   m_SearchItemID          = from.m_SearchItemID;
}


// Копирование данных в другой контроллер
void OC_WebFile::CopyDataTo (OC_WebFile& to)
{
   DEBUG_STACK_NAME (OC_WebFile_CopyDataTo);
   to.m_Name_OSFile           = m_Name_OSFile;
   to.m_Name_Upload           = m_Name_Upload;
   to.m_MIMEType              = m_MIMEType;
   to.m_IconType              = m_IconType;
   to.m_WebFolderID           = m_WebFolderID;
   to.m_OwnerGUID             = m_OwnerGUID;
   to.m_AccessLevelThreshold  = m_AccessLevelThreshold;
   to.m_CreationTime          = m_CreationTime;
   to.m_ModificationTime      = m_ModificationTime;
   to.m_LastAccessTime        = m_LastAccessTime;
   to.m_Version               = m_Version;
   to.m_BinaryData            = m_BinaryData;
   to.m_ShowCount             = m_ShowCount;
   to.m_ClickCount            = m_ClickCount;
   to.m_CTR                   = m_CTR;
   to.m_Estimation_Tot        = m_Estimation_Tot;
   to.m_Estimation_Num        = m_Estimation_Num;
   to.m_Estimation            = m_Estimation;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
   to.m_Name                  = m_Name;
   to.m_Description           = m_Description;
   to.m_Text                  = m_Text;
   to.m_Additional            = m_Additional;
   to.m_SearchItemID          = m_SearchItemID;
}

// Копирование данных из другого контроллера: to << from;
OC_WebFile&  OC_WebFile::operator << (OC_WebFile& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_WebFile&  OC_WebFile::operator >> (OC_WebFile& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_WebFile::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_OwnerGUID ();
              return oldIndex;
      case 2: SetIndex__CreationTime ();
              return oldIndex;
      case 3: SetIndex__ModificationTime ();
              return oldIndex;
      case 4: SetIndex__LastAccessTime ();
              return oldIndex;
      case 5: SetIndex__ShowCount ();
              return oldIndex;
      case 6: SetIndex__ClickCount ();
              return oldIndex;
      case 7: SetIndex__CTR ();
              return oldIndex;
      case 8: SetIndex__Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_WebFile::GetIndex ()
{
   DEBUG_STACK_NAME (OC_WebFile_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_WebFile::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex_OwnerGUID ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_guid; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__CreationTime ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__ModificationTime ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__LastAccessTime ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__ShowCount ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 5; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__ClickCount ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 6; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__CTR ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 7; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_WebFile::SetIndex__Estimation ()
{
   DEBUG_STACK_NAME (OC_WebFile_SetIndex_xxx);
   curIndexInfo.m_id         = 8; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// UserProfile

// Конструктор по умолчанию
OC_UserProfile::OC_UserProfile ()
{
   DEBUG_STACK_NAME (OC_UserProfile_OC_UserProfile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_UserProfile::OC_UserProfile  (identifier objID)
{
   DEBUG_STACK_NAME (OC_UserProfile_OC_UserProfile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_UserProfile::OC_UserProfile  (const OC_UserProfile& from)
{
   DEBUG_STACK_NAME (OC_UserProfile_OC_UserProfile);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_UserProfile::~OC_UserProfile ()
{
   DEBUG_STACK_NAME (OC_UserProfile_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_UserProfile& OC_UserProfile::operator= (const OC_UserProfile& from)
{
   DEBUG_STACK_NAME (OC_UserProfile_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_UserProfile& OC_UserProfile::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_UserProfile_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_UserProfile::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_UserProfile_InitSmartFields);
   classID = OBJ_CLASS_ID_UserProfile;
   m_UserGUID._init              (classID, 2, &coPtr, &OD_UserProfile::d_UserGUID              );
   m_InfoDiv_Hide._init          (classID, 3, &coPtr, &OD_UserProfile::d_InfoDiv_Hide          );
   m_InfoDiv_Show._init          (classID, 4, &coPtr, &OD_UserProfile::d_InfoDiv_Show          );
   m_Filter_Name._init           (classID, 5, &coPtr, &OD_UserProfile::d_Filter_Name           );
   m_Filter_SearchPhrase._init   (classID, 6, &coPtr, &OD_UserProfile::d_Filter_SearchPhrase   );
   m_Filter_FolderID._init       (classID, 7, &coPtr, &OD_UserProfile::d_Filter_FolderID       );
   m_SeenIO_ID._init             (classID, 8, &coPtr, &OD_UserProfile::d_SeenIO_ID             );
   m_SeenIO_Time._init           (classID, 9, &coPtr, &OD_UserProfile::d_SeenIO_Time           );
   m_SeenIO_Estimation._init     (classID, 10, &coPtr, &OD_UserProfile::d_SeenIO_Estimation     );
   m_SeenIO_ShowCount._init      (classID, 11, &coPtr, &OD_UserProfile::d_SeenIO_ShowCount      );
   m_SeenIO_ClickCount._init     (classID, 12, &coPtr, &OD_UserProfile::d_SeenIO_ClickCount     );
   m_SeenIO_CTR._init            (classID, 13, &coPtr, &OD_UserProfile::d_SeenIO_CTR            );
   m_OwnIO._init                 (classID, 14, &coPtr, &OD_UserProfile::d_OwnIO                 );
   m_OwnIO_Time._init            (classID, 15, &coPtr, &OD_UserProfile::d_OwnIO_Time            );
   m_OwnIO_ShowCount._init       (classID, 16, &coPtr, &OD_UserProfile::d_OwnIO_ShowCount       );
   m_OwnIO_ClickCount._init      (classID, 17, &coPtr, &OD_UserProfile::d_OwnIO_ClickCount      );
   m_OwnIO_CTR._init             (classID, 18, &coPtr, &OD_UserProfile::d_OwnIO_CTR             );
   m_OwnIO_Estimation_Tot._init  (classID, 19, &coPtr, &OD_UserProfile::d_OwnIO_Estimation_Tot  );
   m_OwnIO_Estimation_Num._init  (classID, 20, &coPtr, &OD_UserProfile::d_OwnIO_Estimation_Num  );
   m_OwnIO_Estimation._init      (classID, 21, &coPtr, &OD_UserProfile::d_OwnIO_Estimation      );
   m_Log_ObjectGUID._init        (classID, 22, &coPtr, &OD_UserProfile::d_Log_ObjectGUID        );
   m_Log_Action._init            (classID, 23, &coPtr, &OD_UserProfile::d_Log_Action            );
   m_Log_Time._init              (classID, 24, &coPtr, &OD_UserProfile::d_Log_Time              );
   m_Account_Enable._init        (classID, 25, &coPtr, &OD_UserProfile::d_Account_Enable        );
   m_Account_Debit._init         (classID, 26, &coPtr, &OD_UserProfile::d_Account_Debit         );
   m_Account_Credit._init        (classID, 27, &coPtr, &OD_UserProfile::d_Account_Credit        );
   m_Account_Log_Action._init    (classID, 28, &coPtr, &OD_UserProfile::d_Account_Log_Action    );
   m_Account_Log_Amount._init    (classID, 29, &coPtr, &OD_UserProfile::d_Account_Log_Amount    );
   m_Account_Log_Debit._init     (classID, 30, &coPtr, &OD_UserProfile::d_Account_Log_Debit     );
   m_Account_Log_Credit._init    (classID, 31, &coPtr, &OD_UserProfile::d_Account_Log_Credit    );
   m_Account_Log_Time._init      (classID, 32, &coPtr, &OD_UserProfile::d_Account_Log_Time      );
   m_Account_Log_Comment._init   (classID, 33, &coPtr, &OD_UserProfile::d_Account_Log_Comment   );
   m_RootFolderGUID._init        (classID, 34, &coPtr, &OD_UserProfile::d_RootFolderGUID        );
   m_ProxyObject._init           (classID, 35, &coPtr, &OD_UserProfile::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 36, &coPtr, &OD_UserProfile::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 37, &coPtr, &OD_UserProfile::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 38, &coPtr, &OD_UserProfile::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 39, &coPtr, &OD_UserProfile::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_UserProfile::CopyDataFrom (OC_UserProfile& from)
{
   DEBUG_STACK_NAME (OC_UserProfile_CopyDataFrom);
   m_UserGUID              = from.m_UserGUID;
   m_InfoDiv_Hide          = from.m_InfoDiv_Hide;
   m_InfoDiv_Show          = from.m_InfoDiv_Show;
   m_Filter_Name           = from.m_Filter_Name;
   m_Filter_SearchPhrase   = from.m_Filter_SearchPhrase;
   m_Filter_FolderID       = from.m_Filter_FolderID;
   m_SeenIO_ID             = from.m_SeenIO_ID;
   m_SeenIO_Time           = from.m_SeenIO_Time;
   m_SeenIO_Estimation     = from.m_SeenIO_Estimation;
   m_SeenIO_ShowCount      = from.m_SeenIO_ShowCount;
   m_SeenIO_ClickCount     = from.m_SeenIO_ClickCount;
   m_SeenIO_CTR            = from.m_SeenIO_CTR;
   m_OwnIO                 = from.m_OwnIO;
   m_OwnIO_Time            = from.m_OwnIO_Time;
   m_OwnIO_ShowCount       = from.m_OwnIO_ShowCount;
   m_OwnIO_ClickCount      = from.m_OwnIO_ClickCount;
   m_OwnIO_CTR             = from.m_OwnIO_CTR;
   m_OwnIO_Estimation_Tot  = from.m_OwnIO_Estimation_Tot;
   m_OwnIO_Estimation_Num  = from.m_OwnIO_Estimation_Num;
   m_OwnIO_Estimation      = from.m_OwnIO_Estimation;
   m_Log_ObjectGUID        = from.m_Log_ObjectGUID;
   m_Log_Action            = from.m_Log_Action;
   m_Log_Time              = from.m_Log_Time;
   m_Account_Enable        = from.m_Account_Enable;
   m_Account_Debit         = from.m_Account_Debit;
   m_Account_Credit        = from.m_Account_Credit;
   m_Account_Log_Action    = from.m_Account_Log_Action;
   m_Account_Log_Amount    = from.m_Account_Log_Amount;
   m_Account_Log_Debit     = from.m_Account_Log_Debit;
   m_Account_Log_Credit    = from.m_Account_Log_Credit;
   m_Account_Log_Time      = from.m_Account_Log_Time;
   m_Account_Log_Comment   = from.m_Account_Log_Comment;
   m_RootFolderGUID        = from.m_RootFolderGUID;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_UserProfile::CopyDataTo (OC_UserProfile& to)
{
   DEBUG_STACK_NAME (OC_UserProfile_CopyDataTo);
   to.m_UserGUID              = m_UserGUID;
   to.m_InfoDiv_Hide          = m_InfoDiv_Hide;
   to.m_InfoDiv_Show          = m_InfoDiv_Show;
   to.m_Filter_Name           = m_Filter_Name;
   to.m_Filter_SearchPhrase   = m_Filter_SearchPhrase;
   to.m_Filter_FolderID       = m_Filter_FolderID;
   to.m_SeenIO_ID             = m_SeenIO_ID;
   to.m_SeenIO_Time           = m_SeenIO_Time;
   to.m_SeenIO_Estimation     = m_SeenIO_Estimation;
   to.m_SeenIO_ShowCount      = m_SeenIO_ShowCount;
   to.m_SeenIO_ClickCount     = m_SeenIO_ClickCount;
   to.m_SeenIO_CTR            = m_SeenIO_CTR;
   to.m_OwnIO                 = m_OwnIO;
   to.m_OwnIO_Time            = m_OwnIO_Time;
   to.m_OwnIO_ShowCount       = m_OwnIO_ShowCount;
   to.m_OwnIO_ClickCount      = m_OwnIO_ClickCount;
   to.m_OwnIO_CTR             = m_OwnIO_CTR;
   to.m_OwnIO_Estimation_Tot  = m_OwnIO_Estimation_Tot;
   to.m_OwnIO_Estimation_Num  = m_OwnIO_Estimation_Num;
   to.m_OwnIO_Estimation      = m_OwnIO_Estimation;
   to.m_Log_ObjectGUID        = m_Log_ObjectGUID;
   to.m_Log_Action            = m_Log_Action;
   to.m_Log_Time              = m_Log_Time;
   to.m_Account_Enable        = m_Account_Enable;
   to.m_Account_Debit         = m_Account_Debit;
   to.m_Account_Credit        = m_Account_Credit;
   to.m_Account_Log_Action    = m_Account_Log_Action;
   to.m_Account_Log_Amount    = m_Account_Log_Amount;
   to.m_Account_Log_Debit     = m_Account_Log_Debit;
   to.m_Account_Log_Credit    = m_Account_Log_Credit;
   to.m_Account_Log_Time      = m_Account_Log_Time;
   to.m_Account_Log_Comment   = m_Account_Log_Comment;
   to.m_RootFolderGUID        = m_RootFolderGUID;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_UserProfile&  OC_UserProfile::operator << (OC_UserProfile& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_UserProfile&  OC_UserProfile::operator >> (OC_UserProfile& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_UserProfile::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex__SeenIO_ShowCount ();
              return oldIndex;
      case 1: SetIndex__SeenIO_CTR ();
              return oldIndex;
      case 2: SetIndex__OwnIO_ShowCount ();
              return oldIndex;
      case 3: SetIndex__OwnIO_CTR ();
              return oldIndex;
      case 4: SetIndex__OwnIO_Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_UserProfile::GetIndex ()
{
   DEBUG_STACK_NAME (OC_UserProfile_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_UserProfile::SetIndex__SeenIO_ShowCount ()
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_UserProfile::SetIndex__SeenIO_CTR ()
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_UserProfile::SetIndex__OwnIO_ShowCount ()
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_UserProfile::SetIndex__OwnIO_CTR ()
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_UserProfile::SetIndex__OwnIO_Estimation ()
{
   DEBUG_STACK_NAME (OC_UserProfile_SetIndex_xxx);
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// InfoDiv

// Конструктор по умолчанию
OC_InfoDiv::OC_InfoDiv ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_OC_InfoDiv);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_InfoDiv::OC_InfoDiv  (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoDiv_OC_InfoDiv);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_InfoDiv::OC_InfoDiv  (const OC_InfoDiv& from)
{
   DEBUG_STACK_NAME (OC_InfoDiv_OC_InfoDiv);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_InfoDiv::~OC_InfoDiv ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_InfoDiv& OC_InfoDiv::operator= (const OC_InfoDiv& from)
{
   DEBUG_STACK_NAME (OC_InfoDiv_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_InfoDiv& OC_InfoDiv::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoDiv_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_InfoDiv::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_InfoDiv_InitSmartFields);
   classID = OBJ_CLASS_ID_InfoDiv;
   m_InfoSourceSortedID._init    (classID, 2, &coPtr, &OD_InfoDiv::d_InfoSourceSortedID    );
   m_InfoObjectSortedID._init    (classID, 3, &coPtr, &OD_InfoDiv::d_InfoObjectSortedID    );
   m_ClipArtGUID._init           (classID, 4, &coPtr, &OD_InfoDiv::d_ClipArtGUID           );
   m_ShowCount._init             (classID, 5, &coPtr, &OD_InfoDiv::d_ShowCount             );
   m_ClickCount._init            (classID, 6, &coPtr, &OD_InfoDiv::d_ClickCount            );
   m_CTR._init                   (classID, 7, &coPtr, &OD_InfoDiv::d_CTR                   );
   m_Estimation_Tot._init        (classID, 8, &coPtr, &OD_InfoDiv::d_Estimation_Tot        );
   m_Estimation_Num._init        (classID, 9, &coPtr, &OD_InfoDiv::d_Estimation_Num        );
   m_Estimation._init            (classID, 10, &coPtr, &OD_InfoDiv::d_Estimation            );
   m_ProxyObject._init           (classID, 11, &coPtr, &OD_InfoDiv::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 12, &coPtr, &OD_InfoDiv::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 13, &coPtr, &OD_InfoDiv::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 14, &coPtr, &OD_InfoDiv::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 15, &coPtr, &OD_InfoDiv::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_InfoDiv::CopyDataFrom (OC_InfoDiv& from)
{
   DEBUG_STACK_NAME (OC_InfoDiv_CopyDataFrom);
   m_InfoSourceSortedID    = from.m_InfoSourceSortedID;
   m_InfoObjectSortedID    = from.m_InfoObjectSortedID;
   m_ClipArtGUID           = from.m_ClipArtGUID;
   m_ShowCount             = from.m_ShowCount;
   m_ClickCount            = from.m_ClickCount;
   m_CTR                   = from.m_CTR;
   m_Estimation_Tot        = from.m_Estimation_Tot;
   m_Estimation_Num        = from.m_Estimation_Num;
   m_Estimation            = from.m_Estimation;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_InfoDiv::CopyDataTo (OC_InfoDiv& to)
{
   DEBUG_STACK_NAME (OC_InfoDiv_CopyDataTo);
   to.m_InfoSourceSortedID    = m_InfoSourceSortedID;
   to.m_InfoObjectSortedID    = m_InfoObjectSortedID;
   to.m_ClipArtGUID           = m_ClipArtGUID;
   to.m_ShowCount             = m_ShowCount;
   to.m_ClickCount            = m_ClickCount;
   to.m_CTR                   = m_CTR;
   to.m_Estimation_Tot        = m_Estimation_Tot;
   to.m_Estimation_Num        = m_Estimation_Num;
   to.m_Estimation            = m_Estimation;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_InfoDiv&  OC_InfoDiv::operator << (OC_InfoDiv& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_InfoDiv&  OC_InfoDiv::operator >> (OC_InfoDiv& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_InfoDiv::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_InfoDiv_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex__ShowCount ();
              return oldIndex;
      case 1: SetIndex__ClickCount ();
              return oldIndex;
      case 2: SetIndex__CTR ();
              return oldIndex;
      case 3: SetIndex__Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_InfoDiv::GetIndex ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_InfoDiv::SetIndex__ShowCount ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoDiv::SetIndex__ClickCount ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoDiv::SetIndex__CTR ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_InfoDiv::SetIndex__Estimation ()
{
   DEBUG_STACK_NAME (OC_InfoDiv_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// InfoSource

// Конструктор по умолчанию
OC_InfoSource::OC_InfoSource ()
{
   DEBUG_STACK_NAME (OC_InfoSource_OC_InfoSource);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_InfoSource::OC_InfoSource  (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoSource_OC_InfoSource);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_InfoSource::OC_InfoSource  (const OC_InfoSource& from)
{
   DEBUG_STACK_NAME (OC_InfoSource_OC_InfoSource);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_InfoSource::~OC_InfoSource ()
{
   DEBUG_STACK_NAME (OC_InfoSource_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_InfoSource& OC_InfoSource::operator= (const OC_InfoSource& from)
{
   DEBUG_STACK_NAME (OC_InfoSource_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_InfoSource& OC_InfoSource::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoSource_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_InfoSource::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_InfoSource_InitSmartFields);
   classID = OBJ_CLASS_ID_InfoSource;
   m_Name._init                  (classID, 2, &coPtr, &OD_InfoSource::d_Name                  );
   m_Description._init           (classID, 3, &coPtr, &OD_InfoSource::d_Description           );
   m_URL._init                   (classID, 4, &coPtr, &OD_InfoSource::d_URL                   );
   m_RefreshType._init           (classID, 5, &coPtr, &OD_InfoSource::d_RefreshType           );
   m_InfoDivID._init             (classID, 6, &coPtr, &OD_InfoSource::d_InfoDivID             );
   m_LogoGUID._init              (classID, 7, &coPtr, &OD_InfoSource::d_LogoGUID              );
   m_ColumnistGUID._init         (classID, 8, &coPtr, &OD_InfoSource::d_ColumnistGUID         );
   m_Address._init               (classID, 9, &coPtr, &OD_InfoSource::d_Address               );
   m_Language._init              (classID, 10, &coPtr, &OD_InfoSource::d_Language              );
   m_Type._init                  (classID, 11, &coPtr, &OD_InfoSource::d_Type                  );
   m_State._init                 (classID, 12, &coPtr, &OD_InfoSource::d_State                 );
   m_ShowCount._init             (classID, 13, &coPtr, &OD_InfoSource::d_ShowCount             );
   m_ClickCount._init            (classID, 14, &coPtr, &OD_InfoSource::d_ClickCount            );
   m_CTR._init                   (classID, 15, &coPtr, &OD_InfoSource::d_CTR                   );
   m_Estimation_Tot._init        (classID, 16, &coPtr, &OD_InfoSource::d_Estimation_Tot        );
   m_Estimation_Num._init        (classID, 17, &coPtr, &OD_InfoSource::d_Estimation_Num        );
   m_Estimation._init            (classID, 18, &coPtr, &OD_InfoSource::d_Estimation            );
   m_ProxyObject._init           (classID, 19, &coPtr, &OD_InfoSource::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 20, &coPtr, &OD_InfoSource::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 21, &coPtr, &OD_InfoSource::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 22, &coPtr, &OD_InfoSource::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 23, &coPtr, &OD_InfoSource::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_InfoSource::CopyDataFrom (OC_InfoSource& from)
{
   DEBUG_STACK_NAME (OC_InfoSource_CopyDataFrom);
   m_Name                  = from.m_Name;
   m_Description           = from.m_Description;
   m_URL                   = from.m_URL;
   m_RefreshType           = from.m_RefreshType;
   m_InfoDivID             = from.m_InfoDivID;
   m_LogoGUID              = from.m_LogoGUID;
   m_ColumnistGUID         = from.m_ColumnistGUID;
   m_Address               = from.m_Address;
   m_Language              = from.m_Language;
   m_Type                  = from.m_Type;
   m_State                 = from.m_State;
   m_ShowCount             = from.m_ShowCount;
   m_ClickCount            = from.m_ClickCount;
   m_CTR                   = from.m_CTR;
   m_Estimation_Tot        = from.m_Estimation_Tot;
   m_Estimation_Num        = from.m_Estimation_Num;
   m_Estimation            = from.m_Estimation;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_InfoSource::CopyDataTo (OC_InfoSource& to)
{
   DEBUG_STACK_NAME (OC_InfoSource_CopyDataTo);
   to.m_Name                  = m_Name;
   to.m_Description           = m_Description;
   to.m_URL                   = m_URL;
   to.m_RefreshType           = m_RefreshType;
   to.m_InfoDivID             = m_InfoDivID;
   to.m_LogoGUID              = m_LogoGUID;
   to.m_ColumnistGUID         = m_ColumnistGUID;
   to.m_Address               = m_Address;
   to.m_Language              = m_Language;
   to.m_Type                  = m_Type;
   to.m_State                 = m_State;
   to.m_ShowCount             = m_ShowCount;
   to.m_ClickCount            = m_ClickCount;
   to.m_CTR                   = m_CTR;
   to.m_Estimation_Tot        = m_Estimation_Tot;
   to.m_Estimation_Num        = m_Estimation_Num;
   to.m_Estimation            = m_Estimation;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_InfoSource&  OC_InfoSource::operator << (OC_InfoSource& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_InfoSource&  OC_InfoSource::operator >> (OC_InfoSource& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_InfoSource::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_RefreshType ();
              return oldIndex;
      case 2: SetIndex__ShowCount ();
              return oldIndex;
      case 3: SetIndex__ClickCount ();
              return oldIndex;
      case 4: SetIndex__CTR ();
              return oldIndex;
      case 5: SetIndex__Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_InfoSource::GetIndex ()
{
   DEBUG_STACK_NAME (OC_InfoSource_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_InfoSource::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по полю
void OC_InfoSource::SetIndex_RefreshType ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoSource::SetIndex__ShowCount ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoSource::SetIndex__ClickCount ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoSource::SetIndex__CTR ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_InfoSource::SetIndex__Estimation ()
{
   DEBUG_STACK_NAME (OC_InfoSource_SetIndex_xxx);
   curIndexInfo.m_id         = 5; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


// ===============================================================================
// InfoObject

// Конструктор по умолчанию
OC_InfoObject::OC_InfoObject ()
{
   DEBUG_STACK_NAME (OC_InfoObject_OC_InfoObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// Конструктор по идентификатору -- загружается объект из базы
OC_InfoObject::OC_InfoObject  (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoObject_OC_InfoObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// Конструктор копирования из другого контроллера
OC_InfoObject::OC_InfoObject  (const OC_InfoObject& from)
{
   DEBUG_STACK_NAME (OC_InfoObject_OC_InfoObject);
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);
}

// Деструктор контроллера объекта
OC_InfoObject::~OC_InfoObject ()
{
   DEBUG_STACK_NAME (OC_InfoObject_Destructor);
   Release();
}

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
OC_InfoObject& OC_InfoObject::operator= (const OC_InfoObject& from)
{
   DEBUG_STACK_NAME (OC_InfoObject_operator_assign);
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_InfoObject& OC_InfoObject::operator= (identifier objID)
{
   DEBUG_STACK_NAME (OC_InfoObject_operator_assign);
   Open (objID); return *this;
}



// Инициализация хитрожопых полей CSmartField<...>
void OC_InfoObject::InitSmartFields (void)
{
   DEBUG_STACK_NAME (OC_InfoObject_InitSmartFields);
   classID = OBJ_CLASS_ID_InfoObject;
   m_SysName._init               (classID, 2, &coPtr, &OD_InfoObject::d_SysName               );
   m_OwnerGUID._init             (classID, 3, &coPtr, &OD_InfoObject::d_OwnerGUID             );
   m_AccessLevelThreshold._init  (classID, 4, &coPtr, &OD_InfoObject::d_AccessLevelThreshold  );
   m_CreationTime._init          (classID, 5, &coPtr, &OD_InfoObject::d_CreationTime          );
   m_InfoTime._init              (classID, 6, &coPtr, &OD_InfoObject::d_InfoTime              );
   m_InfoDivID._init             (classID, 7, &coPtr, &OD_InfoObject::d_InfoDivID             );
   m_UsageStrictAccess._init     (classID, 8, &coPtr, &OD_InfoObject::d_UsageStrictAccess     );
   m_Log_Action._init            (classID, 9, &coPtr, &OD_InfoObject::d_Log_Action            );
   m_Log_UserGUID._init          (classID, 10, &coPtr, &OD_InfoObject::d_Log_UserGUID          );
   m_Log_Time._init              (classID, 11, &coPtr, &OD_InfoObject::d_Log_Time              );
   m_Log_Comment._init           (classID, 12, &coPtr, &OD_InfoObject::d_Log_Comment           );
   m_IconGUID._init              (classID, 13, &coPtr, &OD_InfoObject::d_IconGUID              );
   m_OriginalText._init          (classID, 14, &coPtr, &OD_InfoObject::d_OriginalText          );
   m_ArtworkGUID._init           (classID, 15, &coPtr, &OD_InfoObject::d_ArtworkGUID           );
   m_InfoSourceID._init          (classID, 16, &coPtr, &OD_InfoObject::d_InfoSourceID          );
   m_AuthorID._init              (classID, 17, &coPtr, &OD_InfoObject::d_AuthorID              );
   m_AuthorStr._init             (classID, 18, &coPtr, &OD_InfoObject::d_AuthorStr             );
   m_URL._init                   (classID, 19, &coPtr, &OD_InfoObject::d_URL                   );
   m_RelatedLinks._init          (classID, 20, &coPtr, &OD_InfoObject::d_RelatedLinks          );
   m_CategoryID._init            (classID, 21, &coPtr, &OD_InfoObject::d_CategoryID            );
   m_ShowCount._init             (classID, 22, &coPtr, &OD_InfoObject::d_ShowCount             );
   m_ClickCount._init            (classID, 23, &coPtr, &OD_InfoObject::d_ClickCount            );
   m_CTR._init                   (classID, 24, &coPtr, &OD_InfoObject::d_CTR                   );
   m_Estimation_Tot._init        (classID, 25, &coPtr, &OD_InfoObject::d_Estimation_Tot        );
   m_Estimation_Num._init        (classID, 26, &coPtr, &OD_InfoObject::d_Estimation_Num        );
   m_Estimation._init            (classID, 27, &coPtr, &OD_InfoObject::d_Estimation            );
   m_Name._init                  (classID, 28, &coPtr, &OD_InfoObject::d_Name                  );
   m_Description._init           (classID, 29, &coPtr, &OD_InfoObject::d_Description           );
   m_Text._init                  (classID, 30, &coPtr, &OD_InfoObject::d_Text                  );
   m_Additional._init            (classID, 31, &coPtr, &OD_InfoObject::d_Additional            );
   m_SearchItemID._init          (classID, 32, &coPtr, &OD_InfoObject::d_SearchItemID          );
   m_ProxyObject._init           (classID, 33, &coPtr, &OD_InfoObject::d_ProxyObject           );
   m_FIELD_Extension_Name._init  (classID, 34, &coPtr, &OD_InfoObject::d_FIELD_Extension_Name  );
   m_FIELD_Extension_Value._init (classID, 35, &coPtr, &OD_InfoObject::d_FIELD_Extension_Value );
   m_MOD_Base_GUID._init         (classID, 36, &coPtr, &OD_InfoObject::d_MOD_Base_GUID         );
   m_MOD_Extension_GUID._init    (classID, 37, &coPtr, &OD_InfoObject::d_MOD_Extension_GUID    );
   SetIndex (0);
}


// Копирование данных из другого контроллера
void OC_InfoObject::CopyDataFrom (OC_InfoObject& from)
{
   DEBUG_STACK_NAME (OC_InfoObject_CopyDataFrom);
   m_SysName               = from.m_SysName;
   m_OwnerGUID             = from.m_OwnerGUID;
   m_AccessLevelThreshold  = from.m_AccessLevelThreshold;
   m_CreationTime          = from.m_CreationTime;
   m_InfoTime              = from.m_InfoTime;
   m_InfoDivID             = from.m_InfoDivID;
   m_UsageStrictAccess     = from.m_UsageStrictAccess;
   m_Log_Action            = from.m_Log_Action;
   m_Log_UserGUID          = from.m_Log_UserGUID;
   m_Log_Time              = from.m_Log_Time;
   m_Log_Comment           = from.m_Log_Comment;
   m_IconGUID              = from.m_IconGUID;
   m_OriginalText          = from.m_OriginalText;
   m_ArtworkGUID           = from.m_ArtworkGUID;
   m_InfoSourceID          = from.m_InfoSourceID;
   m_AuthorID              = from.m_AuthorID;
   m_AuthorStr             = from.m_AuthorStr;
   m_URL                   = from.m_URL;
   m_RelatedLinks          = from.m_RelatedLinks;
   m_CategoryID            = from.m_CategoryID;
   m_ShowCount             = from.m_ShowCount;
   m_ClickCount            = from.m_ClickCount;
   m_CTR                   = from.m_CTR;
   m_Estimation_Tot        = from.m_Estimation_Tot;
   m_Estimation_Num        = from.m_Estimation_Num;
   m_Estimation            = from.m_Estimation;
   m_Name                  = from.m_Name;
   m_Description           = from.m_Description;
   m_Text                  = from.m_Text;
   m_Additional            = from.m_Additional;
   m_SearchItemID          = from.m_SearchItemID;
   m_ProxyObject           = from.m_ProxyObject;
   m_FIELD_Extension_Name  = from.m_FIELD_Extension_Name;
   m_FIELD_Extension_Value = from.m_FIELD_Extension_Value;
   m_MOD_Base_GUID         = from.m_MOD_Base_GUID;
   m_MOD_Extension_GUID    = from.m_MOD_Extension_GUID;
}


// Копирование данных в другой контроллер
void OC_InfoObject::CopyDataTo (OC_InfoObject& to)
{
   DEBUG_STACK_NAME (OC_InfoObject_CopyDataTo);
   to.m_SysName               = m_SysName;
   to.m_OwnerGUID             = m_OwnerGUID;
   to.m_AccessLevelThreshold  = m_AccessLevelThreshold;
   to.m_CreationTime          = m_CreationTime;
   to.m_InfoTime              = m_InfoTime;
   to.m_InfoDivID             = m_InfoDivID;
   to.m_UsageStrictAccess     = m_UsageStrictAccess;
   to.m_Log_Action            = m_Log_Action;
   to.m_Log_UserGUID          = m_Log_UserGUID;
   to.m_Log_Time              = m_Log_Time;
   to.m_Log_Comment           = m_Log_Comment;
   to.m_IconGUID              = m_IconGUID;
   to.m_OriginalText          = m_OriginalText;
   to.m_ArtworkGUID           = m_ArtworkGUID;
   to.m_InfoSourceID          = m_InfoSourceID;
   to.m_AuthorID              = m_AuthorID;
   to.m_AuthorStr             = m_AuthorStr;
   to.m_URL                   = m_URL;
   to.m_RelatedLinks          = m_RelatedLinks;
   to.m_CategoryID            = m_CategoryID;
   to.m_ShowCount             = m_ShowCount;
   to.m_ClickCount            = m_ClickCount;
   to.m_CTR                   = m_CTR;
   to.m_Estimation_Tot        = m_Estimation_Tot;
   to.m_Estimation_Num        = m_Estimation_Num;
   to.m_Estimation            = m_Estimation;
   to.m_Name                  = m_Name;
   to.m_Description           = m_Description;
   to.m_Text                  = m_Text;
   to.m_Additional            = m_Additional;
   to.m_SearchItemID          = m_SearchItemID;
   to.m_ProxyObject           = m_ProxyObject;
   to.m_FIELD_Extension_Name  = m_FIELD_Extension_Name;
   to.m_FIELD_Extension_Value = m_FIELD_Extension_Value;
   to.m_MOD_Base_GUID         = m_MOD_Base_GUID;
   to.m_MOD_Extension_GUID    = m_MOD_Extension_GUID;
}

// Копирование данных из другого контроллера: to << from;
OC_InfoObject&  OC_InfoObject::operator << (OC_InfoObject& from)
{
   CopyDataFrom (from);
   return *this;
}

// Копирование данных в другой контроллер: from >> to;
OC_InfoObject&  OC_InfoObject::operator >> (OC_InfoObject& from)
{
   CopyDataTo (from);
   return *this;
}

// Установить текущий индекс по его идентификатору
identifier OC_InfoObject::SetIndex (identifier newIndex)
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex);

   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_Name ();
              return oldIndex;
      case 1: SetIndex_OwnerGUID__InfoTime ();
              return oldIndex;
      case 2: SetIndex__InfoTime ();
              return oldIndex;
      case 3: SetIndex__CreationTime ();
              return oldIndex;
      case 4: SetIndex_InfoSourceID__InfoTime ();
              return oldIndex;
      case 5: SetIndex__ShowCount ();
              return oldIndex;
      case 6: SetIndex__ClickCount ();
              return oldIndex;
      case 7: SetIndex__CTR ();
              return oldIndex;
      case 8: SetIndex__Estimation ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: Попытка установки неправильного индекса %d в объекте класса %s ", newIndex, className[classID]);
   return oldIndex;
}

// Получить идентификатор текущего индекса
identifier OC_InfoObject::GetIndex ()
{
   DEBUG_STACK_NAME (OC_InfoObject_GetIndex);
   return curIndexInfo.m_id;
}



// Установить текущий индекс по полю
void OC_InfoObject::SetIndex_Name ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_string; 
};

// Установить текущий индекс по набору полей
void OC_InfoObject::SetIndex_OwnerGUID__InfoTime ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 1; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_guid; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__InfoTime ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 2; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__CreationTime ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 3; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по набору полей
void OC_InfoObject::SetIndex_InfoSourceID__InfoTime ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 4; 
   curIndexInfo.m_keyNum     = 2; 
   curIndexInfo.m_keyType[0] = (byte)FT_identifier; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__ShowCount ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 5; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__ClickCount ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 6; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__CTR ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 7; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// Установить текущий индекс по полю
void OC_InfoObject::SetIndex__Estimation ()
{
   DEBUG_STACK_NAME (OC_InfoObject_SetIndex_xxx);
   curIndexInfo.m_id         = 8; 
   curIndexInfo.m_keyNum     = 1; 
   curIndexInfo.m_keyType[0] = (byte)FT_float; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
