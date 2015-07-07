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

#include "./../../kernel/main.h"
#include "./../../kernel/OBD.h"
#include "Lay_ObjData.h"

bool bIGNORE_LOAD_ERROR=true;




char * className[10240]=
{
   "Registry",
   "Extensible",
   "Relation",
   "Linkage",
   "LinkProxy",
   "Connectable",
   "MetaObject",
   "Concept",
   "User",
   "UserGroup",
   "Text",
   "MorphologicRule",
   "SearchItem",
   "StopWord",
   "WordNibbleABC",
   "UsageInFullTextIndex",
   "WebFolder",
   "WebFile",
   "UserProfile",
   "InfoDiv",
   "InfoSource",
   "InfoObject"
};


// Конструктор
   OD_Registry::OD_Registry (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Registry_OD_Registry);

      classID = OBJ_CLASS_ID_Registry;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_NeedInitiate = true;
      d_ConceptID_Sorted.Alloc (0);
      d_ConceptNo_SortID.Alloc (0);
      d_ConceptID_SortNo.Alloc (0);
      d_ConceptParent_SortNo.Alloc (0);
      d_ConceptType_SortNo.Alloc (0);
      d_ConceptLevel_SortNo.Alloc (0);
   }

// Деструктор
  OD_Registry::~OD_Registry () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Registry::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Registry_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_NeedInitiate;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Registry::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Registry_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // bool NeedInitiate
      d_NeedInitiate = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

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
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Registry::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Registry_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // bool NeedInitiate
      n_size += sizeof (bool);

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

      return n_size;
   }

// Запись данных на диск
   bool OD_Registry::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Registry_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // bool NeedInitiate
      (*(bool*)(file+nOffset)) = d_NeedInitiate;
      nOffset += sizeof (bool);

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
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Registry::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Registry_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Registry], objID, d_randID);
      dbg += SSS;

   // bool NeedInitiate
      SSS.Format ("NeedInitiate = %s\n", d_NeedInitiate?"true":"false");
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
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Relation::OD_Relation (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Relation_OD_Relation);

      classID = OBJ_CLASS_ID_Relation;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_CreationTime = 0;
      d_Version = 0;
      d_FieldName.Alloc (0);
      d_FieldType.Alloc (0);
      d_FieldSysName.Alloc (0);
      d_FieldDescription.Alloc (0);
      d_FieldInterfaceType.Alloc (0);
      d_AccessLevelThreshold = 0;
      d_FeodGUID.Alloc (0);
   }

// Деструктор
  OD_Relation::~OD_Relation () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Relation::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Relation_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_SysName;                   break;
         case 3: ka += d_Name;                      break;
         case 4: ka += d_Description;               break;
         case 5: ka += d_CreationTime;              break;
         case 6: ka += d_Version;                   break;
         case 12: ka += d_OwnerGUID;                 break;
         case 13: ka += d_AccessLevelThreshold;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Relation::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Relation_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string SysName
      size_t n_SysName = (*(size_t*)(file+nOffset));  // n_SysName = strlen (s_SysName)+1;
      nOffset += sizeof(size_t);
      char * s_SysName = new char [n_SysName+1];
      LAY_MEMCPY (s_SysName, file, nOffset, n_SysName, file.GetSize(), SysName);
      nOffset += n_SysName;
      DECODE_STRING (n_SysName, s_SysName);
      d_SysName = s_SysName;
      delete [] s_SysName;

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Version
      d_Version = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string FieldName []
      int arr_size_FieldName = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FieldName.Alloc (arr_size_FieldName);
      for (int iFieldName=0; iFieldName<(int)arr_size_FieldName; iFieldName++)
      {
         string tmp_FieldName;
         size_t n_FieldName = (*(size_t*)(file+nOffset));  // n_FieldName = strlen (s_FieldName)+1;
         nOffset += sizeof(size_t);
         char * s_FieldName = new char [n_FieldName+1];
         LAY_MEMCPY (s_FieldName, file, nOffset, n_FieldName, file.GetSize(), FieldName);
         nOffset += n_FieldName;
         DECODE_STRING (n_FieldName, s_FieldName);
         tmp_FieldName = s_FieldName;
         delete [] s_FieldName;

         d_FieldName[iFieldName] = tmp_FieldName;
      }

   // string FieldType []
      int arr_size_FieldType = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FieldType.Alloc (arr_size_FieldType);
      for (int iFieldType=0; iFieldType<(int)arr_size_FieldType; iFieldType++)
      {
         string tmp_FieldType;
         size_t n_FieldType = (*(size_t*)(file+nOffset));  // n_FieldType = strlen (s_FieldType)+1;
         nOffset += sizeof(size_t);
         char * s_FieldType = new char [n_FieldType+1];
         LAY_MEMCPY (s_FieldType, file, nOffset, n_FieldType, file.GetSize(), FieldType);
         nOffset += n_FieldType;
         DECODE_STRING (n_FieldType, s_FieldType);
         tmp_FieldType = s_FieldType;
         delete [] s_FieldType;

         d_FieldType[iFieldType] = tmp_FieldType;
      }

   // string FieldSysName []
      int arr_size_FieldSysName = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FieldSysName.Alloc (arr_size_FieldSysName);
      for (int iFieldSysName=0; iFieldSysName<(int)arr_size_FieldSysName; iFieldSysName++)
      {
         string tmp_FieldSysName;
         size_t n_FieldSysName = (*(size_t*)(file+nOffset));  // n_FieldSysName = strlen (s_FieldSysName)+1;
         nOffset += sizeof(size_t);
         char * s_FieldSysName = new char [n_FieldSysName+1];
         LAY_MEMCPY (s_FieldSysName, file, nOffset, n_FieldSysName, file.GetSize(), FieldSysName);
         nOffset += n_FieldSysName;
         DECODE_STRING (n_FieldSysName, s_FieldSysName);
         tmp_FieldSysName = s_FieldSysName;
         delete [] s_FieldSysName;

         d_FieldSysName[iFieldSysName] = tmp_FieldSysName;
      }

   // string FieldDescription []
      int arr_size_FieldDescription = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FieldDescription.Alloc (arr_size_FieldDescription);
      for (int iFieldDescription=0; iFieldDescription<(int)arr_size_FieldDescription; iFieldDescription++)
      {
         string tmp_FieldDescription;
         size_t n_FieldDescription = (*(size_t*)(file+nOffset));  // n_FieldDescription = strlen (s_FieldDescription)+1;
         nOffset += sizeof(size_t);
         char * s_FieldDescription = new char [n_FieldDescription+1];
         LAY_MEMCPY (s_FieldDescription, file, nOffset, n_FieldDescription, file.GetSize(), FieldDescription);
         nOffset += n_FieldDescription;
         DECODE_STRING (n_FieldDescription, s_FieldDescription);
         tmp_FieldDescription = s_FieldDescription;
         delete [] s_FieldDescription;

         d_FieldDescription[iFieldDescription] = tmp_FieldDescription;
      }

   // string FieldInterfaceType []
      int arr_size_FieldInterfaceType = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FieldInterfaceType.Alloc (arr_size_FieldInterfaceType);
      for (int iFieldInterfaceType=0; iFieldInterfaceType<(int)arr_size_FieldInterfaceType; iFieldInterfaceType++)
      {
         string tmp_FieldInterfaceType;
         size_t n_FieldInterfaceType = (*(size_t*)(file+nOffset));  // n_FieldInterfaceType = strlen (s_FieldInterfaceType)+1;
         nOffset += sizeof(size_t);
         char * s_FieldInterfaceType = new char [n_FieldInterfaceType+1];
         LAY_MEMCPY (s_FieldInterfaceType, file, nOffset, n_FieldInterfaceType, file.GetSize(), FieldInterfaceType);
         nOffset += n_FieldInterfaceType;
         DECODE_STRING (n_FieldInterfaceType, s_FieldInterfaceType);
         tmp_FieldInterfaceType = s_FieldInterfaceType;
         delete [] s_FieldInterfaceType;

         d_FieldInterfaceType[iFieldInterfaceType] = tmp_FieldInterfaceType;
      }

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid FeodGUID []
      int arr_size_FeodGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FeodGUID.Alloc (arr_size_FeodGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,FeodGUID);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Relation::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Relation_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string SysName
      n_size += sizeof (size_t);
      n_size += d_SysName.length()+1;

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // int CreationTime
      n_size += sizeof (int);

   // int Version
      n_size += sizeof (int);

   // string FieldName []
      n_size += sizeof (size_t);
      for (int iFieldName=0; iFieldName<d_FieldName.GetSize(); iFieldName++)
      {
         n_size += sizeof (size_t);
         n_size += d_FieldName[iFieldName].length()+1;
      }

   // string FieldType []
      n_size += sizeof (size_t);
      for (int iFieldType=0; iFieldType<d_FieldType.GetSize(); iFieldType++)
      {
         n_size += sizeof (size_t);
         n_size += d_FieldType[iFieldType].length()+1;
      }

   // string FieldSysName []
      n_size += sizeof (size_t);
      for (int iFieldSysName=0; iFieldSysName<d_FieldSysName.GetSize(); iFieldSysName++)
      {
         n_size += sizeof (size_t);
         n_size += d_FieldSysName[iFieldSysName].length()+1;
      }

   // string FieldDescription []
      n_size += sizeof (size_t);
      for (int iFieldDescription=0; iFieldDescription<d_FieldDescription.GetSize(); iFieldDescription++)
      {
         n_size += sizeof (size_t);
         n_size += d_FieldDescription[iFieldDescription].length()+1;
      }

   // string FieldInterfaceType []
      n_size += sizeof (size_t);
      for (int iFieldInterfaceType=0; iFieldInterfaceType<d_FieldInterfaceType.GetSize(); iFieldInterfaceType++)
      {
         n_size += sizeof (size_t);
         n_size += d_FieldInterfaceType[iFieldInterfaceType].length()+1;
      }

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

   // guid FeodGUID []
      n_size += sizeof (size_t);
      n_size += d_FeodGUID.GetSize() * sizeof(guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_Relation::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Relation_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string SysName
      size_t n_SysName = d_SysName.length()+1;
      (*(size_t*)(file+nOffset)) = n_SysName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_SysName.c_str(), n_SysName);
      ENCODE_STRING (n_SysName, (char*)(file+nOffset));
      nOffset += n_SysName;

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

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // int Version
      (*(int*)(file+nOffset)) = d_Version;
      nOffset += sizeof (int);

   // string FieldName []
      (*(size_t*)(file+nOffset)) = d_FieldName.GetSize();
      nOffset += sizeof(size_t);
      for (int iFieldName=0; iFieldName<d_FieldName.GetSize(); iFieldName++)
      {
         size_t n_FieldName = d_FieldName[iFieldName].length()+1;
         (*(size_t*)(file+nOffset)) = n_FieldName;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FieldName[iFieldName].c_str(), n_FieldName);
         ENCODE_STRING (n_FieldName, (char*)(file+nOffset));
         nOffset += n_FieldName;
      }

   // string FieldType []
      (*(size_t*)(file+nOffset)) = d_FieldType.GetSize();
      nOffset += sizeof(size_t);
      for (int iFieldType=0; iFieldType<d_FieldType.GetSize(); iFieldType++)
      {
         size_t n_FieldType = d_FieldType[iFieldType].length()+1;
         (*(size_t*)(file+nOffset)) = n_FieldType;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FieldType[iFieldType].c_str(), n_FieldType);
         ENCODE_STRING (n_FieldType, (char*)(file+nOffset));
         nOffset += n_FieldType;
      }

   // string FieldSysName []
      (*(size_t*)(file+nOffset)) = d_FieldSysName.GetSize();
      nOffset += sizeof(size_t);
      for (int iFieldSysName=0; iFieldSysName<d_FieldSysName.GetSize(); iFieldSysName++)
      {
         size_t n_FieldSysName = d_FieldSysName[iFieldSysName].length()+1;
         (*(size_t*)(file+nOffset)) = n_FieldSysName;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FieldSysName[iFieldSysName].c_str(), n_FieldSysName);
         ENCODE_STRING (n_FieldSysName, (char*)(file+nOffset));
         nOffset += n_FieldSysName;
      }

   // string FieldDescription []
      (*(size_t*)(file+nOffset)) = d_FieldDescription.GetSize();
      nOffset += sizeof(size_t);
      for (int iFieldDescription=0; iFieldDescription<d_FieldDescription.GetSize(); iFieldDescription++)
      {
         size_t n_FieldDescription = d_FieldDescription[iFieldDescription].length()+1;
         (*(size_t*)(file+nOffset)) = n_FieldDescription;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FieldDescription[iFieldDescription].c_str(), n_FieldDescription);
         ENCODE_STRING (n_FieldDescription, (char*)(file+nOffset));
         nOffset += n_FieldDescription;
      }

   // string FieldInterfaceType []
      (*(size_t*)(file+nOffset)) = d_FieldInterfaceType.GetSize();
      nOffset += sizeof(size_t);
      for (int iFieldInterfaceType=0; iFieldInterfaceType<d_FieldInterfaceType.GetSize(); iFieldInterfaceType++)
      {
         size_t n_FieldInterfaceType = d_FieldInterfaceType[iFieldInterfaceType].length()+1;
         (*(size_t*)(file+nOffset)) = n_FieldInterfaceType;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FieldInterfaceType[iFieldInterfaceType].c_str(), n_FieldInterfaceType);
         ENCODE_STRING (n_FieldInterfaceType, (char*)(file+nOffset));
         nOffset += n_FieldInterfaceType;
      }

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);

   // guid FeodGUID []
      (*(size_t*)(file+nOffset)) = d_FeodGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,FeodGUID);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Relation::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Relation_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Relation], objID, d_randID);
      dbg += SSS;

   // string SysName
      SSS.Format ("SysName = '%s'\n", d_SysName.c_str());
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // int Version
      SSS.Format ("Version = %d\n", d_Version);
      dbg += SSS;

   // string FieldName []
      SSS.Format ("FieldName[].size = %d:\n", d_FieldName.GetSize());
      dbg += SSS;
      for (int iFieldName=0; iFieldName<d_FieldName.GetSize(); iFieldName++)
      {
         SSS.Format ("   FieldName[%d] = '%s'\n", iFieldName, d_FieldName[iFieldName].c_str());
         dbg += SSS;
      }

   // string FieldType []
      SSS.Format ("FieldType[].size = %d:\n", d_FieldType.GetSize());
      dbg += SSS;
      for (int iFieldType=0; iFieldType<d_FieldType.GetSize(); iFieldType++)
      {
         SSS.Format ("   FieldType[%d] = '%s'\n", iFieldType, d_FieldType[iFieldType].c_str());
         dbg += SSS;
      }

   // string FieldSysName []
      SSS.Format ("FieldSysName[].size = %d:\n", d_FieldSysName.GetSize());
      dbg += SSS;
      for (int iFieldSysName=0; iFieldSysName<d_FieldSysName.GetSize(); iFieldSysName++)
      {
         SSS.Format ("   FieldSysName[%d] = '%s'\n", iFieldSysName, d_FieldSysName[iFieldSysName].c_str());
         dbg += SSS;
      }

   // string FieldDescription []
      SSS.Format ("FieldDescription[].size = %d:\n", d_FieldDescription.GetSize());
      dbg += SSS;
      for (int iFieldDescription=0; iFieldDescription<d_FieldDescription.GetSize(); iFieldDescription++)
      {
         SSS.Format ("   FieldDescription[%d] = '%s'\n", iFieldDescription, d_FieldDescription[iFieldDescription].c_str());
         dbg += SSS;
      }

   // string FieldInterfaceType []
      SSS.Format ("FieldInterfaceType[].size = %d:\n", d_FieldInterfaceType.GetSize());
      dbg += SSS;
      for (int iFieldInterfaceType=0; iFieldInterfaceType<d_FieldInterfaceType.GetSize(); iFieldInterfaceType++)
      {
         SSS.Format ("   FieldInterfaceType[%d] = '%s'\n", iFieldInterfaceType, d_FieldInterfaceType[iFieldInterfaceType].c_str());
         dbg += SSS;
      }

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;

   // guid FeodGUID []
      SSS.Format ("FeodGUID[].size = %d:\n", d_FeodGUID.GetSize());
      dbg += SSS;
      for (int iFeodGUID=0; iFeodGUID<d_FeodGUID.GetSize(); iFeodGUID++)
      {
         SSS.Format ("   FeodGUID[%d] = {%d,%d,%d}\n", iFeodGUID, d_FeodGUID[iFeodGUID].cl, iFeodGUID, d_FeodGUID[iFeodGUID].id, iFeodGUID, d_FeodGUID[iFeodGUID].rn);
         dbg += SSS;
      }
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Linkage::OD_Linkage (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Linkage_OD_Linkage);

      classID = OBJ_CLASS_ID_Linkage;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_CreationTime = 0;
      d_RelationID = NA;
      d_ProxyID.Alloc (0);
      d_Value.Alloc (0);
      d_AccessLevelThreshold = 0;
   }

// Деструктор
  OD_Linkage::~OD_Linkage () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Linkage::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Linkage_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_CreationTime;              break;
         case 3: ka += d_RelationID;                break;
         case 6: ka += d_OwnerGUID;                 break;
         case 7: ka += d_AccessLevelThreshold;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Linkage::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Linkage_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier RelationID
      d_RelationID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier ProxyID []
      int arr_size_ProxyID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ProxyID.Alloc (arr_size_ProxyID);
      OD_LOAD_SIMPLE_ARRAY (identifier,ProxyID);

   // string Value []
      int arr_size_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Value.Alloc (arr_size_Value);
      for (int iValue=0; iValue<(int)arr_size_Value; iValue++)
      {
         string tmp_Value;
         size_t n_Value = (*(size_t*)(file+nOffset));  // n_Value = strlen (s_Value)+1;
         nOffset += sizeof(size_t);
         char * s_Value = new char [n_Value+1];
         LAY_MEMCPY (s_Value, file, nOffset, n_Value, file.GetSize(), Value);
         nOffset += n_Value;
         DECODE_STRING (n_Value, s_Value);
         tmp_Value = s_Value;
         delete [] s_Value;

         d_Value[iValue] = tmp_Value;
      }

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Linkage::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Linkage_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // int CreationTime
      n_size += sizeof (int);

   // identifier RelationID
      n_size += sizeof (identifier);

   // identifier ProxyID []
      n_size += sizeof (size_t);
      n_size += d_ProxyID.GetSize() * sizeof(identifier);

   // string Value []
      n_size += sizeof (size_t);
      for (int iValue=0; iValue<d_Value.GetSize(); iValue++)
      {
         n_size += sizeof (size_t);
         n_size += d_Value[iValue].length()+1;
      }

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Linkage::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Linkage_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // identifier RelationID
      (*(identifier*)(file+nOffset)) = d_RelationID;
      nOffset += sizeof (identifier);

   // identifier ProxyID []
      (*(size_t*)(file+nOffset)) = d_ProxyID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,ProxyID);

   // string Value []
      (*(size_t*)(file+nOffset)) = d_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iValue=0; iValue<d_Value.GetSize(); iValue++)
      {
         size_t n_Value = d_Value[iValue].length()+1;
         (*(size_t*)(file+nOffset)) = n_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Value[iValue].c_str(), n_Value);
         ENCODE_STRING (n_Value, (char*)(file+nOffset));
         nOffset += n_Value;
      }

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Linkage::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Linkage_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Linkage], objID, d_randID);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // identifier RelationID
      SSS.Format ("RelationID = %d\n", d_RelationID);
      dbg += SSS;

   // identifier ProxyID []
      SSS.Format ("ProxyID[].size = %d:\n", d_ProxyID.GetSize());
      dbg += SSS;
      for (int iProxyID=0; iProxyID<d_ProxyID.GetSize(); iProxyID++)
      {
         SSS.Format ("   ProxyID[%d] = %d\n", iProxyID, d_ProxyID[iProxyID]);
         dbg += SSS;
      }

   // string Value []
      SSS.Format ("Value[].size = %d:\n", d_Value.GetSize());
      dbg += SSS;
      for (int iValue=0; iValue<d_Value.GetSize(); iValue++)
      {
         SSS.Format ("   Value[%d] = '%s'\n", iValue, d_Value[iValue].c_str());
         dbg += SSS;
      }

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_LinkProxy::OD_LinkProxy (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_LinkProxy_OD_LinkProxy);

      classID = OBJ_CLASS_ID_LinkProxy;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_CreationTime = 0;
      d_LinkageID.Alloc (0);
      d_RelationID.Alloc (0);
      d_RelationField.Alloc (0);
   }

// Деструктор
  OD_LinkProxy::~OD_LinkProxy () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_LinkProxy::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_LinkProxy_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_CreationTime;      break;
         case 3: ka += d_RealObject;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_LinkProxy::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_LinkProxy_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid RealObject
      d_RealObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // identifier LinkageID []
      int arr_size_LinkageID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_LinkageID.Alloc (arr_size_LinkageID);
      OD_LOAD_SIMPLE_ARRAY (identifier,LinkageID);

   // identifier RelationID []
      int arr_size_RelationID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RelationID.Alloc (arr_size_RelationID);
      OD_LOAD_SIMPLE_ARRAY (identifier,RelationID);

   // int RelationField []
      int arr_size_RelationField = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RelationField.Alloc (arr_size_RelationField);
      OD_LOAD_SIMPLE_ARRAY (int,RelationField);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_LinkProxy::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_LinkProxy_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // int CreationTime
      n_size += sizeof (int);

   // guid RealObject
      n_size += sizeof (guid);

   // identifier LinkageID []
      n_size += sizeof (size_t);
      n_size += d_LinkageID.GetSize() * sizeof(identifier);

   // identifier RelationID []
      n_size += sizeof (size_t);
      n_size += d_RelationID.GetSize() * sizeof(identifier);

   // int RelationField []
      n_size += sizeof (size_t);
      n_size += d_RelationField.GetSize() * sizeof(int);

      return n_size;
   }

// Запись данных на диск
   bool OD_LinkProxy::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_LinkProxy_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // guid RealObject
      (*(guid*)(file+nOffset)) = d_RealObject;
      nOffset += sizeof (guid);

   // identifier LinkageID []
      (*(size_t*)(file+nOffset)) = d_LinkageID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,LinkageID);

   // identifier RelationID []
      (*(size_t*)(file+nOffset)) = d_RelationID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,RelationID);

   // int RelationField []
      (*(size_t*)(file+nOffset)) = d_RelationField.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,RelationField);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_LinkProxy::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_LinkProxy_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_LinkProxy], objID, d_randID);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // guid RealObject
      SSS.Format ("RealObject = {%d,%d,%d}\n", d_RealObject.cl, d_RealObject.id, d_RealObject.rn);
      dbg += SSS;

   // identifier LinkageID []
      SSS.Format ("LinkageID[].size = %d:\n", d_LinkageID.GetSize());
      dbg += SSS;
      for (int iLinkageID=0; iLinkageID<d_LinkageID.GetSize(); iLinkageID++)
      {
         SSS.Format ("   LinkageID[%d] = %d\n", iLinkageID, d_LinkageID[iLinkageID]);
         dbg += SSS;
      }

   // identifier RelationID []
      SSS.Format ("RelationID[].size = %d:\n", d_RelationID.GetSize());
      dbg += SSS;
      for (int iRelationID=0; iRelationID<d_RelationID.GetSize(); iRelationID++)
      {
         SSS.Format ("   RelationID[%d] = %d\n", iRelationID, d_RelationID[iRelationID]);
         dbg += SSS;
      }

   // int RelationField []
      SSS.Format ("RelationField[].size = %d:\n", d_RelationField.GetSize());
      dbg += SSS;
      for (int iRelationField=0; iRelationField<d_RelationField.GetSize(); iRelationField++)
      {
         SSS.Format ("   RelationField[%d] = %d\n", iRelationField, d_RelationField[iRelationField]);
         dbg += SSS;
      }
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Connectable::OD_Connectable (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Connectable_OD_Connectable);

      classID = OBJ_CLASS_ID_Connectable;


      m_CoIndexPtr = new OBD_pointer [0];
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
   }

// Деструктор
  OD_Connectable::~OD_Connectable () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Connectable::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Connectable_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_ProxyObject;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Connectable::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Connectable_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Connectable::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Connectable_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // guid ProxyObject
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_Connectable::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Connectable_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Connectable::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Connectable_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Connectable], objID, d_randID);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_MetaObject::OD_MetaObject (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_MetaObject_OD_MetaObject);

      classID = OBJ_CLASS_ID_MetaObject;


      m_CoIndexPtr = new OBD_pointer [3];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_arrInt.Alloc (0);
      d_arrFloat.Alloc (0);
      d_arrBool.Alloc (0);
      d_arrByte.Alloc (0);
      d_arrTime.Alloc (0);
      d_arrString.Alloc (0);
      d_arrGUID.Alloc (0);
      d_arrID.Alloc (0);
      d_CreationTime = 0;
      d_AccessLevelThreshold = 0;
      d_FeodGUID.Alloc (0);
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_MetaObject::~OD_MetaObject () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_MetaObject::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_MetaObject_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Type;                      break;
         case 3: ka += d_Name;                      break;
         case 4: ka += d_SysName;                   break;
         case 5: ka += d_Header1;                   break;
         case 6: ka += d_Header2;                   break;
         case 7: ka += d_Header3;                   break;
         case 8: ka += d_Header4;                   break;
         case 9: ka += d_Header5;                   break;
         case 10: ka += d_Comment;                   break;
         case 11: ka += d_Text;                      break;
         case 20: ka += d_CreationTime;              break;
         case 21: ka += d_OwnerGUID;                 break;
         case 22: ka += d_AccessLevelThreshold;      break;
         case 24: ka += d_ProxyObject;               break;
         case 27: ka += d_MOD_Base_GUID;             break;
         case 28: ka += d_MOD_Extension_GUID;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_MetaObject::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_MetaObject_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type+1];
      LAY_MEMCPY (s_Type, file, nOffset, n_Type, file.GetSize(), Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string SysName
      size_t n_SysName = (*(size_t*)(file+nOffset));  // n_SysName = strlen (s_SysName)+1;
      nOffset += sizeof(size_t);
      char * s_SysName = new char [n_SysName+1];
      LAY_MEMCPY (s_SysName, file, nOffset, n_SysName, file.GetSize(), SysName);
      nOffset += n_SysName;
      DECODE_STRING (n_SysName, s_SysName);
      d_SysName = s_SysName;
      delete [] s_SysName;

   // string Header1
      size_t n_Header1 = (*(size_t*)(file+nOffset));  // n_Header1 = strlen (s_Header1)+1;
      nOffset += sizeof(size_t);
      char * s_Header1 = new char [n_Header1+1];
      LAY_MEMCPY (s_Header1, file, nOffset, n_Header1, file.GetSize(), Header1);
      nOffset += n_Header1;
      DECODE_STRING (n_Header1, s_Header1);
      d_Header1 = s_Header1;
      delete [] s_Header1;

   // string Header2
      size_t n_Header2 = (*(size_t*)(file+nOffset));  // n_Header2 = strlen (s_Header2)+1;
      nOffset += sizeof(size_t);
      char * s_Header2 = new char [n_Header2+1];
      LAY_MEMCPY (s_Header2, file, nOffset, n_Header2, file.GetSize(), Header2);
      nOffset += n_Header2;
      DECODE_STRING (n_Header2, s_Header2);
      d_Header2 = s_Header2;
      delete [] s_Header2;

   // string Header3
      size_t n_Header3 = (*(size_t*)(file+nOffset));  // n_Header3 = strlen (s_Header3)+1;
      nOffset += sizeof(size_t);
      char * s_Header3 = new char [n_Header3+1];
      LAY_MEMCPY (s_Header3, file, nOffset, n_Header3, file.GetSize(), Header3);
      nOffset += n_Header3;
      DECODE_STRING (n_Header3, s_Header3);
      d_Header3 = s_Header3;
      delete [] s_Header3;

   // string Header4
      size_t n_Header4 = (*(size_t*)(file+nOffset));  // n_Header4 = strlen (s_Header4)+1;
      nOffset += sizeof(size_t);
      char * s_Header4 = new char [n_Header4+1];
      LAY_MEMCPY (s_Header4, file, nOffset, n_Header4, file.GetSize(), Header4);
      nOffset += n_Header4;
      DECODE_STRING (n_Header4, s_Header4);
      d_Header4 = s_Header4;
      delete [] s_Header4;

   // string Header5
      size_t n_Header5 = (*(size_t*)(file+nOffset));  // n_Header5 = strlen (s_Header5)+1;
      nOffset += sizeof(size_t);
      char * s_Header5 = new char [n_Header5+1];
      LAY_MEMCPY (s_Header5, file, nOffset, n_Header5, file.GetSize(), Header5);
      nOffset += n_Header5;
      DECODE_STRING (n_Header5, s_Header5);
      d_Header5 = s_Header5;
      delete [] s_Header5;

   // string Comment
      size_t n_Comment = (*(size_t*)(file+nOffset));  // n_Comment = strlen (s_Comment)+1;
      nOffset += sizeof(size_t);
      char * s_Comment = new char [n_Comment+1];
      LAY_MEMCPY (s_Comment, file, nOffset, n_Comment, file.GetSize(), Comment);
      nOffset += n_Comment;
      DECODE_STRING (n_Comment, s_Comment);
      d_Comment = s_Comment;
      delete [] s_Comment;

   // string Text
      size_t n_Text = (*(size_t*)(file+nOffset));  // n_Text = strlen (s_Text)+1;
      nOffset += sizeof(size_t);
      char * s_Text = new char [n_Text+1];
      LAY_MEMCPY (s_Text, file, nOffset, n_Text, file.GetSize(), Text);
      nOffset += n_Text;
      DECODE_STRING (n_Text, s_Text);
      d_Text = s_Text;
      delete [] s_Text;

   // int arrInt []
      int arr_size_arrInt = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrInt.Alloc (arr_size_arrInt);
      OD_LOAD_SIMPLE_ARRAY (int,arrInt);

   // float arrFloat []
      int arr_size_arrFloat = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrFloat.Alloc (arr_size_arrFloat);
      OD_LOAD_SIMPLE_ARRAY (float,arrFloat);

   // bool arrBool []
      int arr_size_arrBool = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrBool.Alloc (arr_size_arrBool);
      OD_LOAD_SIMPLE_ARRAY (bool,arrBool);

   // byte arrByte []
      int arr_size_arrByte = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrByte.Alloc (arr_size_arrByte);
      OD_LOAD_SIMPLE_ARRAY (byte,arrByte);

   // int arrTime []
      int arr_size_arrTime = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrTime.Alloc (arr_size_arrTime);
      OD_LOAD_SIMPLE_ARRAY (int,arrTime);

   // string arrString []
      int arr_size_arrString = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrString.Alloc (arr_size_arrString);
      for (int iarrString=0; iarrString<(int)arr_size_arrString; iarrString++)
      {
         string tmp_arrString;
         size_t n_arrString = (*(size_t*)(file+nOffset));  // n_arrString = strlen (s_arrString)+1;
         nOffset += sizeof(size_t);
         char * s_arrString = new char [n_arrString+1];
         LAY_MEMCPY (s_arrString, file, nOffset, n_arrString, file.GetSize(), arrString);
         nOffset += n_arrString;
         DECODE_STRING (n_arrString, s_arrString);
         tmp_arrString = s_arrString;
         delete [] s_arrString;

         d_arrString[iarrString] = tmp_arrString;
      }

   // guid arrGUID []
      int arr_size_arrGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrGUID.Alloc (arr_size_arrGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,arrGUID);

   // identifier arrID []
      int arr_size_arrID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_arrID.Alloc (arr_size_arrID);
      OD_LOAD_SIMPLE_ARRAY (identifier,arrID);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid FeodGUID []
      int arr_size_FeodGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FeodGUID.Alloc (arr_size_FeodGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,FeodGUID);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_MetaObject::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_MetaObject_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string SysName
      n_size += sizeof (size_t);
      n_size += d_SysName.length()+1;

   // string Header1
      n_size += sizeof (size_t);
      n_size += d_Header1.length()+1;

   // string Header2
      n_size += sizeof (size_t);
      n_size += d_Header2.length()+1;

   // string Header3
      n_size += sizeof (size_t);
      n_size += d_Header3.length()+1;

   // string Header4
      n_size += sizeof (size_t);
      n_size += d_Header4.length()+1;

   // string Header5
      n_size += sizeof (size_t);
      n_size += d_Header5.length()+1;

   // string Comment
      n_size += sizeof (size_t);
      n_size += d_Comment.length()+1;

   // string Text
      n_size += sizeof (size_t);
      n_size += d_Text.length()+1;

   // int arrInt []
      n_size += sizeof (size_t);
      n_size += d_arrInt.GetSize() * sizeof(int);

   // float arrFloat []
      n_size += sizeof (size_t);
      n_size += d_arrFloat.GetSize() * sizeof(float);

   // bool arrBool []
      n_size += sizeof (size_t);
      n_size += d_arrBool.GetSize() * sizeof(bool);

   // byte arrByte []
      n_size += sizeof (size_t);
      n_size += d_arrByte.GetSize() * sizeof(byte);

   // int arrTime []
      n_size += sizeof (size_t);
      n_size += d_arrTime.GetSize() * sizeof(int);

   // string arrString []
      n_size += sizeof (size_t);
      for (int iarrString=0; iarrString<d_arrString.GetSize(); iarrString++)
      {
         n_size += sizeof (size_t);
         n_size += d_arrString[iarrString].length()+1;
      }

   // guid arrGUID []
      n_size += sizeof (size_t);
      n_size += d_arrGUID.GetSize() * sizeof(guid);

   // identifier arrID []
      n_size += sizeof (size_t);
      n_size += d_arrID.GetSize() * sizeof(identifier);

   // int CreationTime
      n_size += sizeof (int);

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

   // guid FeodGUID []
      n_size += sizeof (size_t);
      n_size += d_FeodGUID.GetSize() * sizeof(guid);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_MetaObject::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_MetaObject_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
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

   // string SysName
      size_t n_SysName = d_SysName.length()+1;
      (*(size_t*)(file+nOffset)) = n_SysName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_SysName.c_str(), n_SysName);
      ENCODE_STRING (n_SysName, (char*)(file+nOffset));
      nOffset += n_SysName;

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

   // string Header4
      size_t n_Header4 = d_Header4.length()+1;
      (*(size_t*)(file+nOffset)) = n_Header4;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Header4.c_str(), n_Header4);
      ENCODE_STRING (n_Header4, (char*)(file+nOffset));
      nOffset += n_Header4;

   // string Header5
      size_t n_Header5 = d_Header5.length()+1;
      (*(size_t*)(file+nOffset)) = n_Header5;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Header5.c_str(), n_Header5);
      ENCODE_STRING (n_Header5, (char*)(file+nOffset));
      nOffset += n_Header5;

   // string Comment
      size_t n_Comment = d_Comment.length()+1;
      (*(size_t*)(file+nOffset)) = n_Comment;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Comment.c_str(), n_Comment);
      ENCODE_STRING (n_Comment, (char*)(file+nOffset));
      nOffset += n_Comment;

   // string Text
      size_t n_Text = d_Text.length()+1;
      (*(size_t*)(file+nOffset)) = n_Text;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Text.c_str(), n_Text);
      ENCODE_STRING (n_Text, (char*)(file+nOffset));
      nOffset += n_Text;

   // int arrInt []
      (*(size_t*)(file+nOffset)) = d_arrInt.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,arrInt);

   // float arrFloat []
      (*(size_t*)(file+nOffset)) = d_arrFloat.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (float,arrFloat);

   // bool arrBool []
      (*(size_t*)(file+nOffset)) = d_arrBool.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (bool,arrBool);

   // byte arrByte []
      (*(size_t*)(file+nOffset)) = d_arrByte.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,arrByte);

   // int arrTime []
      (*(size_t*)(file+nOffset)) = d_arrTime.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,arrTime);

   // string arrString []
      (*(size_t*)(file+nOffset)) = d_arrString.GetSize();
      nOffset += sizeof(size_t);
      for (int iarrString=0; iarrString<d_arrString.GetSize(); iarrString++)
      {
         size_t n_arrString = d_arrString[iarrString].length()+1;
         (*(size_t*)(file+nOffset)) = n_arrString;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_arrString[iarrString].c_str(), n_arrString);
         ENCODE_STRING (n_arrString, (char*)(file+nOffset));
         nOffset += n_arrString;
      }

   // guid arrGUID []
      (*(size_t*)(file+nOffset)) = d_arrGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,arrGUID);

   // identifier arrID []
      (*(size_t*)(file+nOffset)) = d_arrID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,arrID);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);

   // guid FeodGUID []
      (*(size_t*)(file+nOffset)) = d_FeodGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,FeodGUID);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_MetaObject::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_MetaObject_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_MetaObject], objID, d_randID);
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string SysName
      SSS.Format ("SysName = '%s'\n", d_SysName.c_str());
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

   // string Header4
      SSS.Format ("Header4 = '%s'\n", d_Header4.c_str());
      dbg += SSS;

   // string Header5
      SSS.Format ("Header5 = '%s'\n", d_Header5.c_str());
      dbg += SSS;

   // string Comment
      SSS.Format ("Comment = '%s'\n", d_Comment.c_str());
      dbg += SSS;

   // string Text
      SSS.Format ("Text = '%s'\n", d_Text.c_str());
      dbg += SSS;

   // int arrInt []
      SSS.Format ("arrInt[].size = %d:\n", d_arrInt.GetSize());
      dbg += SSS;
      for (int iarrInt=0; iarrInt<d_arrInt.GetSize(); iarrInt++)
      {
         SSS.Format ("   arrInt[%d] = %d\n", iarrInt, d_arrInt[iarrInt]);
         dbg += SSS;
      }

   // float arrFloat []
      SSS.Format ("arrFloat[].size = %d:\n", d_arrFloat.GetSize());
      dbg += SSS;
      for (int iarrFloat=0; iarrFloat<d_arrFloat.GetSize(); iarrFloat++)
      {
         SSS.Format ("   arrFloat[%d] = %f\n", iarrFloat, d_arrFloat[iarrFloat]);
         dbg += SSS;
      }

   // bool arrBool []
      SSS.Format ("arrBool[].size = %d:\n", d_arrBool.GetSize());
      dbg += SSS;
      for (int iarrBool=0; iarrBool<d_arrBool.GetSize(); iarrBool++)
      {
         SSS.Format ("   arrBool[%d] = %s\n", iarrBool, d_arrBool[iarrBool]?"true":"false");
         dbg += SSS;
      }

   // byte arrByte []
      SSS.Format ("arrByte[].size = %d:\n", d_arrByte.GetSize());
      dbg += SSS;
      for (int iarrByte=0; iarrByte<d_arrByte.GetSize(); iarrByte++)
      {
         SSS.Format ("   arrByte[%d] = %d\n", iarrByte, d_arrByte[iarrByte]);
         dbg += SSS;
      }

   // int arrTime []
      SSS.Format ("arrTime[].size = %d:\n", d_arrTime.GetSize());
      dbg += SSS;
      for (int iarrTime=0; iarrTime<d_arrTime.GetSize(); iarrTime++)
      {
         SSS.Format ("   arrTime[%d] = %d\n", iarrTime, d_arrTime[iarrTime]);
         dbg += SSS;
      }

   // string arrString []
      SSS.Format ("arrString[].size = %d:\n", d_arrString.GetSize());
      dbg += SSS;
      for (int iarrString=0; iarrString<d_arrString.GetSize(); iarrString++)
      {
         SSS.Format ("   arrString[%d] = '%s'\n", iarrString, d_arrString[iarrString].c_str());
         dbg += SSS;
      }

   // guid arrGUID []
      SSS.Format ("arrGUID[].size = %d:\n", d_arrGUID.GetSize());
      dbg += SSS;
      for (int iarrGUID=0; iarrGUID<d_arrGUID.GetSize(); iarrGUID++)
      {
         SSS.Format ("   arrGUID[%d] = {%d,%d,%d}\n", iarrGUID, d_arrGUID[iarrGUID].cl, iarrGUID, d_arrGUID[iarrGUID].id, iarrGUID, d_arrGUID[iarrGUID].rn);
         dbg += SSS;
      }

   // identifier arrID []
      SSS.Format ("arrID[].size = %d:\n", d_arrID.GetSize());
      dbg += SSS;
      for (int iarrID=0; iarrID<d_arrID.GetSize(); iarrID++)
      {
         SSS.Format ("   arrID[%d] = %d\n", iarrID, d_arrID[iarrID]);
         dbg += SSS;
      }

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;

   // guid FeodGUID []
      SSS.Format ("FeodGUID[].size = %d:\n", d_FeodGUID.GetSize());
      dbg += SSS;
      for (int iFeodGUID=0; iFeodGUID<d_FeodGUID.GetSize(); iFeodGUID++)
      {
         SSS.Format ("   FeodGUID[%d] = {%d,%d,%d}\n", iFeodGUID, d_FeodGUID[iFeodGUID].cl, iFeodGUID, d_FeodGUID[iFeodGUID].id, iFeodGUID, d_FeodGUID[iFeodGUID].rn);
         dbg += SSS;
      }

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Concept::OD_Concept (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Concept_OD_Concept);

      classID = OBJ_CLASS_ID_Concept;


      m_CoIndexPtr = new OBD_pointer [5];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_TypeNo = -1;
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
      d_No = -1;
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_Concept::~OD_Concept () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Concept::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Concept_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Name;                    break;
         case 3: ka += d_Description;             break;
         case 4: ka += d_Type;                    break;
         case 5: ka += d_TypeNo;                  break;
         case 6: ka += d_Parent;                  break;
         case 16: ka += d_Level;                   break;
         case 17: ka += d_No;                      break;
         case 20: ka += d_MOD_Base_GUID;           break;
         case 21: ka += d_MOD_Extension_GUID;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Concept::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Concept_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type+1];
      LAY_MEMCPY (s_Type, file, nOffset, n_Type, file.GetSize(), Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // int TypeNo
      d_TypeNo = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

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

   // int No
      d_No = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Concept::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Concept_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // int TypeNo
      n_size += sizeof (int);

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

   // int No
      n_size += sizeof (int);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_Concept::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Concept_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

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

   // int No
      (*(int*)(file+nOffset)) = d_No;
      nOffset += sizeof (int);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Concept::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Concept_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Concept], objID, d_randID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // int TypeNo
      SSS.Format ("TypeNo = %d\n", d_TypeNo);
      dbg += SSS;

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

   // int No
      SSS.Format ("No = %d\n", d_No);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_User::OD_User (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_User_OD_User);

      classID = OBJ_CLASS_ID_User;


      m_CoIndexPtr = new OBD_pointer [3];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_PasswordInBrowser = false;
      d_CreationTime = 0;
      d_AccessLevel = 0;
      d_GroupID.Alloc (0);
      d_OwnFeodID.Alloc (0);
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_User::~OD_User () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_User::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_User_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Login;                   break;
         case 3: ka += d_Password;                break;
         case 4: ka += d_PasswordInBrowser;       break;
         case 5: ka += d_CreationTime;            break;
         case 6: ka += d_FullName;                break;
         case 7: ka += d_Email;                   break;
         case 8: ka += d_URL;                     break;
         case 9: ka += d_Data;                    break;
         case 10: ka += d_AccessLevel;             break;
         case 13: ka += d_ProxyObject;             break;
         case 16: ka += d_MOD_Base_GUID;           break;
         case 17: ka += d_MOD_Extension_GUID;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_User::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_User_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Login
      size_t n_Login = (*(size_t*)(file+nOffset));  // n_Login = strlen (s_Login)+1;
      nOffset += sizeof(size_t);
      char * s_Login = new char [n_Login+1];
      LAY_MEMCPY (s_Login, file, nOffset, n_Login, file.GetSize(), Login);
      nOffset += n_Login;
      DECODE_STRING (n_Login, s_Login);
      d_Login = s_Login;
      delete [] s_Login;

   // string Password
      size_t n_Password = (*(size_t*)(file+nOffset));  // n_Password = strlen (s_Password)+1;
      nOffset += sizeof(size_t);
      char * s_Password = new char [n_Password+1];
      LAY_MEMCPY (s_Password, file, nOffset, n_Password, file.GetSize(), Password);
      nOffset += n_Password;
      DECODE_STRING (n_Password, s_Password);
      d_Password = s_Password;
      delete [] s_Password;

   // bool PasswordInBrowser
      d_PasswordInBrowser = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // string FullName
      size_t n_FullName = (*(size_t*)(file+nOffset));  // n_FullName = strlen (s_FullName)+1;
      nOffset += sizeof(size_t);
      char * s_FullName = new char [n_FullName+1];
      LAY_MEMCPY (s_FullName, file, nOffset, n_FullName, file.GetSize(), FullName);
      nOffset += n_FullName;
      DECODE_STRING (n_FullName, s_FullName);
      d_FullName = s_FullName;
      delete [] s_FullName;

   // string Email
      size_t n_Email = (*(size_t*)(file+nOffset));  // n_Email = strlen (s_Email)+1;
      nOffset += sizeof(size_t);
      char * s_Email = new char [n_Email+1];
      LAY_MEMCPY (s_Email, file, nOffset, n_Email, file.GetSize(), Email);
      nOffset += n_Email;
      DECODE_STRING (n_Email, s_Email);
      d_Email = s_Email;
      delete [] s_Email;

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL+1];
      LAY_MEMCPY (s_URL, file, nOffset, n_URL, file.GetSize(), URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // string Data
      size_t n_Data = (*(size_t*)(file+nOffset));  // n_Data = strlen (s_Data)+1;
      nOffset += sizeof(size_t);
      char * s_Data = new char [n_Data+1];
      LAY_MEMCPY (s_Data, file, nOffset, n_Data, file.GetSize(), Data);
      nOffset += n_Data;
      DECODE_STRING (n_Data, s_Data);
      d_Data = s_Data;
      delete [] s_Data;

   // int AccessLevel
      d_AccessLevel = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier GroupID []
      int arr_size_GroupID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_GroupID.Alloc (arr_size_GroupID);
      OD_LOAD_SIMPLE_ARRAY (identifier,GroupID);

   // identifier OwnFeodID []
      int arr_size_OwnFeodID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_OwnFeodID.Alloc (arr_size_OwnFeodID);
      OD_LOAD_SIMPLE_ARRAY (identifier,OwnFeodID);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_User::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_User_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Login
      n_size += sizeof (size_t);
      n_size += d_Login.length()+1;

   // string Password
      n_size += sizeof (size_t);
      n_size += d_Password.length()+1;

   // bool PasswordInBrowser
      n_size += sizeof (bool);

   // int CreationTime
      n_size += sizeof (int);

   // string FullName
      n_size += sizeof (size_t);
      n_size += d_FullName.length()+1;

   // string Email
      n_size += sizeof (size_t);
      n_size += d_Email.length()+1;

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // string Data
      n_size += sizeof (size_t);
      n_size += d_Data.length()+1;

   // int AccessLevel
      n_size += sizeof (int);

   // identifier GroupID []
      n_size += sizeof (size_t);
      n_size += d_GroupID.GetSize() * sizeof(identifier);

   // identifier OwnFeodID []
      n_size += sizeof (size_t);
      n_size += d_OwnFeodID.GetSize() * sizeof(identifier);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_User::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_User_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
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

   // bool PasswordInBrowser
      (*(bool*)(file+nOffset)) = d_PasswordInBrowser;
      nOffset += sizeof (bool);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // string FullName
      size_t n_FullName = d_FullName.length()+1;
      (*(size_t*)(file+nOffset)) = n_FullName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_FullName.c_str(), n_FullName);
      ENCODE_STRING (n_FullName, (char*)(file+nOffset));
      nOffset += n_FullName;

   // string Email
      size_t n_Email = d_Email.length()+1;
      (*(size_t*)(file+nOffset)) = n_Email;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Email.c_str(), n_Email);
      ENCODE_STRING (n_Email, (char*)(file+nOffset));
      nOffset += n_Email;

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // string Data
      size_t n_Data = d_Data.length()+1;
      (*(size_t*)(file+nOffset)) = n_Data;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Data.c_str(), n_Data);
      ENCODE_STRING (n_Data, (char*)(file+nOffset));
      nOffset += n_Data;

   // int AccessLevel
      (*(int*)(file+nOffset)) = d_AccessLevel;
      nOffset += sizeof (int);

   // identifier GroupID []
      (*(size_t*)(file+nOffset)) = d_GroupID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,GroupID);

   // identifier OwnFeodID []
      (*(size_t*)(file+nOffset)) = d_OwnFeodID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,OwnFeodID);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_User::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_User_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_User], objID, d_randID);
      dbg += SSS;

   // string Login
      SSS.Format ("Login = '%s'\n", d_Login.c_str());
      dbg += SSS;

   // string Password
      SSS.Format ("Password = '%s'\n", d_Password.c_str());
      dbg += SSS;

   // bool PasswordInBrowser
      SSS.Format ("PasswordInBrowser = %s\n", d_PasswordInBrowser?"true":"false");
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // string FullName
      SSS.Format ("FullName = '%s'\n", d_FullName.c_str());
      dbg += SSS;

   // string Email
      SSS.Format ("Email = '%s'\n", d_Email.c_str());
      dbg += SSS;

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // string Data
      SSS.Format ("Data = '%s'\n", d_Data.c_str());
      dbg += SSS;

   // int AccessLevel
      SSS.Format ("AccessLevel = %d\n", d_AccessLevel);
      dbg += SSS;

   // identifier GroupID []
      SSS.Format ("GroupID[].size = %d:\n", d_GroupID.GetSize());
      dbg += SSS;
      for (int iGroupID=0; iGroupID<d_GroupID.GetSize(); iGroupID++)
      {
         SSS.Format ("   GroupID[%d] = %d\n", iGroupID, d_GroupID[iGroupID]);
         dbg += SSS;
      }

   // identifier OwnFeodID []
      SSS.Format ("OwnFeodID[].size = %d:\n", d_OwnFeodID.GetSize());
      dbg += SSS;
      for (int iOwnFeodID=0; iOwnFeodID<d_OwnFeodID.GetSize(); iOwnFeodID++)
      {
         SSS.Format ("   OwnFeodID[%d] = %d\n", iOwnFeodID, d_OwnFeodID[iOwnFeodID]);
         dbg += SSS;
      }

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_UserGroup::OD_UserGroup (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_UserGroup_OD_UserGroup);

      classID = OBJ_CLASS_ID_UserGroup;


      m_CoIndexPtr = new OBD_pointer [3];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_CreationTime = 0;
      d_AccessLevelThreshold = 0;
      d_UserID.Alloc (0);
      d_Rights_Feod.Alloc (0);
      d_Rights_Attr.Alloc (0);
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_UserGroup::~OD_UserGroup () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_UserGroup::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_UserGroup_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Name;                      break;
         case 3: ka += d_Type;                      break;
         case 4: ka += d_Description;               break;
         case 5: ka += d_CreationTime;              break;
         case 6: ka += d_OwnerGUID;                 break;
         case 7: ka += d_AccessLevelThreshold;      break;
         case 11: ka += d_ProxyObject;               break;
         case 14: ka += d_MOD_Base_GUID;             break;
         case 15: ka += d_MOD_Extension_GUID;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_UserGroup::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserGroup_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type+1];
      LAY_MEMCPY (s_Type, file, nOffset, n_Type, file.GetSize(), Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier UserID []
      int arr_size_UserID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_UserID.Alloc (arr_size_UserID);
      OD_LOAD_SIMPLE_ARRAY (identifier,UserID);

   // identifier Rights_Feod []
      int arr_size_Rights_Feod = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Rights_Feod.Alloc (arr_size_Rights_Feod);
      OD_LOAD_SIMPLE_ARRAY (identifier,Rights_Feod);

   // string Rights_Attr []
      int arr_size_Rights_Attr = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Rights_Attr.Alloc (arr_size_Rights_Attr);
      for (int iRights_Attr=0; iRights_Attr<(int)arr_size_Rights_Attr; iRights_Attr++)
      {
         string tmp_Rights_Attr;
         size_t n_Rights_Attr = (*(size_t*)(file+nOffset));  // n_Rights_Attr = strlen (s_Rights_Attr)+1;
         nOffset += sizeof(size_t);
         char * s_Rights_Attr = new char [n_Rights_Attr+1];
         LAY_MEMCPY (s_Rights_Attr, file, nOffset, n_Rights_Attr, file.GetSize(), Rights_Attr);
         nOffset += n_Rights_Attr;
         DECODE_STRING (n_Rights_Attr, s_Rights_Attr);
         tmp_Rights_Attr = s_Rights_Attr;
         delete [] s_Rights_Attr;

         d_Rights_Attr[iRights_Attr] = tmp_Rights_Attr;
      }

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_UserGroup::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_UserGroup_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // int CreationTime
      n_size += sizeof (int);

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

   // identifier UserID []
      n_size += sizeof (size_t);
      n_size += d_UserID.GetSize() * sizeof(identifier);

   // identifier Rights_Feod []
      n_size += sizeof (size_t);
      n_size += d_Rights_Feod.GetSize() * sizeof(identifier);

   // string Rights_Attr []
      n_size += sizeof (size_t);
      for (int iRights_Attr=0; iRights_Attr<d_Rights_Attr.GetSize(); iRights_Attr++)
      {
         n_size += sizeof (size_t);
         n_size += d_Rights_Attr[iRights_Attr].length()+1;
      }

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_UserGroup::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserGroup_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Type
      size_t n_Type = d_Type.length()+1;
      (*(size_t*)(file+nOffset)) = n_Type;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Type.c_str(), n_Type);
      ENCODE_STRING (n_Type, (char*)(file+nOffset));
      nOffset += n_Type;

   // string Description
      size_t n_Description = d_Description.length()+1;
      (*(size_t*)(file+nOffset)) = n_Description;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Description.c_str(), n_Description);
      ENCODE_STRING (n_Description, (char*)(file+nOffset));
      nOffset += n_Description;

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);

   // identifier UserID []
      (*(size_t*)(file+nOffset)) = d_UserID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,UserID);

   // identifier Rights_Feod []
      (*(size_t*)(file+nOffset)) = d_Rights_Feod.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Rights_Feod);

   // string Rights_Attr []
      (*(size_t*)(file+nOffset)) = d_Rights_Attr.GetSize();
      nOffset += sizeof(size_t);
      for (int iRights_Attr=0; iRights_Attr<d_Rights_Attr.GetSize(); iRights_Attr++)
      {
         size_t n_Rights_Attr = d_Rights_Attr[iRights_Attr].length()+1;
         (*(size_t*)(file+nOffset)) = n_Rights_Attr;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Rights_Attr[iRights_Attr].c_str(), n_Rights_Attr);
         ENCODE_STRING (n_Rights_Attr, (char*)(file+nOffset));
         nOffset += n_Rights_Attr;
      }

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_UserGroup::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserGroup_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_UserGroup], objID, d_randID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;

   // identifier UserID []
      SSS.Format ("UserID[].size = %d:\n", d_UserID.GetSize());
      dbg += SSS;
      for (int iUserID=0; iUserID<d_UserID.GetSize(); iUserID++)
      {
         SSS.Format ("   UserID[%d] = %d\n", iUserID, d_UserID[iUserID]);
         dbg += SSS;
      }

   // identifier Rights_Feod []
      SSS.Format ("Rights_Feod[].size = %d:\n", d_Rights_Feod.GetSize());
      dbg += SSS;
      for (int iRights_Feod=0; iRights_Feod<d_Rights_Feod.GetSize(); iRights_Feod++)
      {
         SSS.Format ("   Rights_Feod[%d] = %d\n", iRights_Feod, d_Rights_Feod[iRights_Feod]);
         dbg += SSS;
      }

   // string Rights_Attr []
      SSS.Format ("Rights_Attr[].size = %d:\n", d_Rights_Attr.GetSize());
      dbg += SSS;
      for (int iRights_Attr=0; iRights_Attr<d_Rights_Attr.GetSize(); iRights_Attr++)
      {
         SSS.Format ("   Rights_Attr[%d] = '%s'\n", iRights_Attr, d_Rights_Attr[iRights_Attr].c_str());
         dbg += SSS;
      }

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_Text::OD_Text (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_Text_OD_Text);

      classID = OBJ_CLASS_ID_Text;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_CreationTime = 0;
   }

// Деструктор
  OD_Text::~OD_Text () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_Text::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_Text_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Name;              break;
         case 3: ka += d_Text;              break;
         case 4: ka += d_CreationTime;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_Text::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Text_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Text
      size_t n_Text = (*(size_t*)(file+nOffset));  // n_Text = strlen (s_Text)+1;
      nOffset += sizeof(size_t);
      char * s_Text = new char [n_Text+1];
      LAY_MEMCPY (s_Text, file, nOffset, n_Text, file.GetSize(), Text);
      nOffset += n_Text;
      DECODE_STRING (n_Text, s_Text);
      d_Text = s_Text;
      delete [] s_Text;

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Text::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_Text_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Text
      n_size += sizeof (size_t);
      n_size += d_Text.length()+1;

   // int CreationTime
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Text::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_Text_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string Name
      size_t n_Name = d_Name.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name.c_str(), n_Name);
      ENCODE_STRING (n_Name, (char*)(file+nOffset));
      nOffset += n_Name;

   // string Text
      size_t n_Text = d_Text.length()+1;
      (*(size_t*)(file+nOffset)) = n_Text;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Text.c_str(), n_Text);
      ENCODE_STRING (n_Text, (char*)(file+nOffset));
      nOffset += n_Text;

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Text::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_Text_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_Text], objID, d_randID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Text
      SSS.Format ("Text = '%s'\n", d_Text.c_str());
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_MorphologicRule::OD_MorphologicRule (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_OD_MorphologicRule);

      classID = OBJ_CLASS_ID_MorphologicRule;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_Attribute = 0;
      d_BaseEnd_Available.Alloc (0);
      d_BaseEnd_Exception.Alloc (0);
      d_Number = 0;
      d_MatchCount = 0;
      d_ApplyCount = 0;
   }

// Деструктор
  OD_MorphologicRule::~OD_MorphologicRule () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_MorphologicRule::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Attribute;         break;
         case 5: ka += d_AffixNormal;       break;
         case 6: ka += d_AffixVariant;      break;
         case 7: ka += d_Comment;           break;
         case 8: ka += d_Number;            break;
         case 9: ka += d_MatchCount;        break;
         case 10: ka += d_ApplyCount;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_MorphologicRule::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // byte Attribute
      d_Attribute = (*(byte*)(file+nOffset));
      nOffset += sizeof(byte);

   // byte BaseEnd_Available []
      int arr_size_BaseEnd_Available = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BaseEnd_Available.Alloc (arr_size_BaseEnd_Available);
      OD_LOAD_SIMPLE_ARRAY (byte,BaseEnd_Available);

   // byte BaseEnd_Exception []
      int arr_size_BaseEnd_Exception = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BaseEnd_Exception.Alloc (arr_size_BaseEnd_Exception);
      OD_LOAD_SIMPLE_ARRAY (byte,BaseEnd_Exception);

   // string AffixNormal
      size_t n_AffixNormal = (*(size_t*)(file+nOffset));  // n_AffixNormal = strlen (s_AffixNormal)+1;
      nOffset += sizeof(size_t);
      char * s_AffixNormal = new char [n_AffixNormal+1];
      LAY_MEMCPY (s_AffixNormal, file, nOffset, n_AffixNormal, file.GetSize(), AffixNormal);
      nOffset += n_AffixNormal;
      DECODE_STRING (n_AffixNormal, s_AffixNormal);
      d_AffixNormal = s_AffixNormal;
      delete [] s_AffixNormal;

   // string AffixVariant
      size_t n_AffixVariant = (*(size_t*)(file+nOffset));  // n_AffixVariant = strlen (s_AffixVariant)+1;
      nOffset += sizeof(size_t);
      char * s_AffixVariant = new char [n_AffixVariant+1];
      LAY_MEMCPY (s_AffixVariant, file, nOffset, n_AffixVariant, file.GetSize(), AffixVariant);
      nOffset += n_AffixVariant;
      DECODE_STRING (n_AffixVariant, s_AffixVariant);
      d_AffixVariant = s_AffixVariant;
      delete [] s_AffixVariant;

   // string Comment
      size_t n_Comment = (*(size_t*)(file+nOffset));  // n_Comment = strlen (s_Comment)+1;
      nOffset += sizeof(size_t);
      char * s_Comment = new char [n_Comment+1];
      LAY_MEMCPY (s_Comment, file, nOffset, n_Comment, file.GetSize(), Comment);
      nOffset += n_Comment;
      DECODE_STRING (n_Comment, s_Comment);
      d_Comment = s_Comment;
      delete [] s_Comment;

   // int Number
      d_Number = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int MatchCount
      d_MatchCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ApplyCount
      d_ApplyCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_MorphologicRule::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // byte Attribute
      n_size += sizeof (byte);

   // byte BaseEnd_Available []
      n_size += sizeof (size_t);
      n_size += d_BaseEnd_Available.GetSize() * sizeof(byte);

   // byte BaseEnd_Exception []
      n_size += sizeof (size_t);
      n_size += d_BaseEnd_Exception.GetSize() * sizeof(byte);

   // string AffixNormal
      n_size += sizeof (size_t);
      n_size += d_AffixNormal.length()+1;

   // string AffixVariant
      n_size += sizeof (size_t);
      n_size += d_AffixVariant.length()+1;

   // string Comment
      n_size += sizeof (size_t);
      n_size += d_Comment.length()+1;

   // int Number
      n_size += sizeof (int);

   // int MatchCount
      n_size += sizeof (int);

   // int ApplyCount
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_MorphologicRule::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // byte Attribute
      (*(byte*)(file+nOffset)) = d_Attribute;
      nOffset += sizeof (byte);

   // byte BaseEnd_Available []
      (*(size_t*)(file+nOffset)) = d_BaseEnd_Available.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,BaseEnd_Available);

   // byte BaseEnd_Exception []
      (*(size_t*)(file+nOffset)) = d_BaseEnd_Exception.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,BaseEnd_Exception);

   // string AffixNormal
      size_t n_AffixNormal = d_AffixNormal.length()+1;
      (*(size_t*)(file+nOffset)) = n_AffixNormal;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_AffixNormal.c_str(), n_AffixNormal);
      ENCODE_STRING (n_AffixNormal, (char*)(file+nOffset));
      nOffset += n_AffixNormal;

   // string AffixVariant
      size_t n_AffixVariant = d_AffixVariant.length()+1;
      (*(size_t*)(file+nOffset)) = n_AffixVariant;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_AffixVariant.c_str(), n_AffixVariant);
      ENCODE_STRING (n_AffixVariant, (char*)(file+nOffset));
      nOffset += n_AffixVariant;

   // string Comment
      size_t n_Comment = d_Comment.length()+1;
      (*(size_t*)(file+nOffset)) = n_Comment;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Comment.c_str(), n_Comment);
      ENCODE_STRING (n_Comment, (char*)(file+nOffset));
      nOffset += n_Comment;

   // int Number
      (*(int*)(file+nOffset)) = d_Number;
      nOffset += sizeof (int);

   // int MatchCount
      (*(int*)(file+nOffset)) = d_MatchCount;
      nOffset += sizeof (int);

   // int ApplyCount
      (*(int*)(file+nOffset)) = d_ApplyCount;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_MorphologicRule::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_MorphologicRule_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_MorphologicRule], objID, d_randID);
      dbg += SSS;

   // byte Attribute
      SSS.Format ("Attribute = %d\n", d_Attribute);
      dbg += SSS;

   // byte BaseEnd_Available []
      SSS.Format ("BaseEnd_Available[].size = %d:\n", d_BaseEnd_Available.GetSize());
      dbg += SSS;
      for (int iBaseEnd_Available=0; iBaseEnd_Available<d_BaseEnd_Available.GetSize(); iBaseEnd_Available++)
      {
         SSS.Format ("   BaseEnd_Available[%d] = %d\n", iBaseEnd_Available, d_BaseEnd_Available[iBaseEnd_Available]);
         dbg += SSS;
      }

   // byte BaseEnd_Exception []
      SSS.Format ("BaseEnd_Exception[].size = %d:\n", d_BaseEnd_Exception.GetSize());
      dbg += SSS;
      for (int iBaseEnd_Exception=0; iBaseEnd_Exception<d_BaseEnd_Exception.GetSize(); iBaseEnd_Exception++)
      {
         SSS.Format ("   BaseEnd_Exception[%d] = %d\n", iBaseEnd_Exception, d_BaseEnd_Exception[iBaseEnd_Exception]);
         dbg += SSS;
      }

   // string AffixNormal
      SSS.Format ("AffixNormal = '%s'\n", d_AffixNormal.c_str());
      dbg += SSS;

   // string AffixVariant
      SSS.Format ("AffixVariant = '%s'\n", d_AffixVariant.c_str());
      dbg += SSS;

   // string Comment
      SSS.Format ("Comment = '%s'\n", d_Comment.c_str());
      dbg += SSS;

   // int Number
      SSS.Format ("Number = %d\n", d_Number);
      dbg += SSS;

   // int MatchCount
      SSS.Format ("MatchCount = %d\n", d_MatchCount);
      dbg += SSS;

   // int ApplyCount
      SSS.Format ("ApplyCount = %d\n", d_ApplyCount);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_SearchItem::OD_SearchItem (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_SearchItem_OD_SearchItem);

      classID = OBJ_CLASS_ID_SearchItem;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_Hypothesis = false;
      d_Text_Number = 0;
      d_Text_ObjectSortedGUID.Alloc (0);
      d_Text_ModificationTime.Alloc (0);
      d_Text_WordAppearanceNum.Alloc (0);
      d_Text_WordFirstPosition.Alloc (0);
   }

// Деструктор
  OD_SearchItem::~OD_SearchItem () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_SearchItem::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_SearchItem_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_NormalWord;         break;
         case 3: ka += d_NormalWordInv;      break;
         case 4: ka += d_Attributes;         break;
         case 5: ka += d_Hypothesis;         break;
         case 6: ka += d_Text_Number;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_SearchItem::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_SearchItem_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string NormalWord
      size_t n_NormalWord = (*(size_t*)(file+nOffset));  // n_NormalWord = strlen (s_NormalWord)+1;
      nOffset += sizeof(size_t);
      char * s_NormalWord = new char [n_NormalWord+1];
      LAY_MEMCPY (s_NormalWord, file, nOffset, n_NormalWord, file.GetSize(), NormalWord);
      nOffset += n_NormalWord;
      DECODE_STRING (n_NormalWord, s_NormalWord);
      d_NormalWord = s_NormalWord;
      delete [] s_NormalWord;

   // string NormalWordInv
      size_t n_NormalWordInv = (*(size_t*)(file+nOffset));  // n_NormalWordInv = strlen (s_NormalWordInv)+1;
      nOffset += sizeof(size_t);
      char * s_NormalWordInv = new char [n_NormalWordInv+1];
      LAY_MEMCPY (s_NormalWordInv, file, nOffset, n_NormalWordInv, file.GetSize(), NormalWordInv);
      nOffset += n_NormalWordInv;
      DECODE_STRING (n_NormalWordInv, s_NormalWordInv);
      d_NormalWordInv = s_NormalWordInv;
      delete [] s_NormalWordInv;

   // string Attributes
      size_t n_Attributes = (*(size_t*)(file+nOffset));  // n_Attributes = strlen (s_Attributes)+1;
      nOffset += sizeof(size_t);
      char * s_Attributes = new char [n_Attributes+1];
      LAY_MEMCPY (s_Attributes, file, nOffset, n_Attributes, file.GetSize(), Attributes);
      nOffset += n_Attributes;
      DECODE_STRING (n_Attributes, s_Attributes);
      d_Attributes = s_Attributes;
      delete [] s_Attributes;

   // bool Hypothesis
      d_Hypothesis = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int Text_Number
      d_Text_Number = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // guid Text_ObjectSortedGUID []
      int arr_size_Text_ObjectSortedGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Text_ObjectSortedGUID.Alloc (arr_size_Text_ObjectSortedGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,Text_ObjectSortedGUID);

   // int Text_ModificationTime []
      int arr_size_Text_ModificationTime = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Text_ModificationTime.Alloc (arr_size_Text_ModificationTime);
      OD_LOAD_SIMPLE_ARRAY (int,Text_ModificationTime);

   // int Text_WordAppearanceNum []
      int arr_size_Text_WordAppearanceNum = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Text_WordAppearanceNum.Alloc (arr_size_Text_WordAppearanceNum);
      OD_LOAD_SIMPLE_ARRAY (int,Text_WordAppearanceNum);

   // int Text_WordFirstPosition []
      int arr_size_Text_WordFirstPosition = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Text_WordFirstPosition.Alloc (arr_size_Text_WordFirstPosition);
      OD_LOAD_SIMPLE_ARRAY (int,Text_WordFirstPosition);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_SearchItem::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_SearchItem_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string NormalWord
      n_size += sizeof (size_t);
      n_size += d_NormalWord.length()+1;

   // string NormalWordInv
      n_size += sizeof (size_t);
      n_size += d_NormalWordInv.length()+1;

   // string Attributes
      n_size += sizeof (size_t);
      n_size += d_Attributes.length()+1;

   // bool Hypothesis
      n_size += sizeof (bool);

   // int Text_Number
      n_size += sizeof (int);

   // guid Text_ObjectSortedGUID []
      n_size += sizeof (size_t);
      n_size += d_Text_ObjectSortedGUID.GetSize() * sizeof(guid);

   // int Text_ModificationTime []
      n_size += sizeof (size_t);
      n_size += d_Text_ModificationTime.GetSize() * sizeof(int);

   // int Text_WordAppearanceNum []
      n_size += sizeof (size_t);
      n_size += d_Text_WordAppearanceNum.GetSize() * sizeof(int);

   // int Text_WordFirstPosition []
      n_size += sizeof (size_t);
      n_size += d_Text_WordFirstPosition.GetSize() * sizeof(int);

      return n_size;
   }

// Запись данных на диск
   bool OD_SearchItem::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_SearchItem_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string NormalWord
      size_t n_NormalWord = d_NormalWord.length()+1;
      (*(size_t*)(file+nOffset)) = n_NormalWord;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_NormalWord.c_str(), n_NormalWord);
      ENCODE_STRING (n_NormalWord, (char*)(file+nOffset));
      nOffset += n_NormalWord;

   // string NormalWordInv
      size_t n_NormalWordInv = d_NormalWordInv.length()+1;
      (*(size_t*)(file+nOffset)) = n_NormalWordInv;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_NormalWordInv.c_str(), n_NormalWordInv);
      ENCODE_STRING (n_NormalWordInv, (char*)(file+nOffset));
      nOffset += n_NormalWordInv;

   // string Attributes
      size_t n_Attributes = d_Attributes.length()+1;
      (*(size_t*)(file+nOffset)) = n_Attributes;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Attributes.c_str(), n_Attributes);
      ENCODE_STRING (n_Attributes, (char*)(file+nOffset));
      nOffset += n_Attributes;

   // bool Hypothesis
      (*(bool*)(file+nOffset)) = d_Hypothesis;
      nOffset += sizeof (bool);

   // int Text_Number
      (*(int*)(file+nOffset)) = d_Text_Number;
      nOffset += sizeof (int);

   // guid Text_ObjectSortedGUID []
      (*(size_t*)(file+nOffset)) = d_Text_ObjectSortedGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,Text_ObjectSortedGUID);

   // int Text_ModificationTime []
      (*(size_t*)(file+nOffset)) = d_Text_ModificationTime.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Text_ModificationTime);

   // int Text_WordAppearanceNum []
      (*(size_t*)(file+nOffset)) = d_Text_WordAppearanceNum.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Text_WordAppearanceNum);

   // int Text_WordFirstPosition []
      (*(size_t*)(file+nOffset)) = d_Text_WordFirstPosition.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Text_WordFirstPosition);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_SearchItem::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_SearchItem_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_SearchItem], objID, d_randID);
      dbg += SSS;

   // string NormalWord
      SSS.Format ("NormalWord = '%s'\n", d_NormalWord.c_str());
      dbg += SSS;

   // string NormalWordInv
      SSS.Format ("NormalWordInv = '%s'\n", d_NormalWordInv.c_str());
      dbg += SSS;

   // string Attributes
      SSS.Format ("Attributes = '%s'\n", d_Attributes.c_str());
      dbg += SSS;

   // bool Hypothesis
      SSS.Format ("Hypothesis = %s\n", d_Hypothesis?"true":"false");
      dbg += SSS;

   // int Text_Number
      SSS.Format ("Text_Number = %d\n", d_Text_Number);
      dbg += SSS;

   // guid Text_ObjectSortedGUID []
      SSS.Format ("Text_ObjectSortedGUID[].size = %d:\n", d_Text_ObjectSortedGUID.GetSize());
      dbg += SSS;
      for (int iText_ObjectSortedGUID=0; iText_ObjectSortedGUID<d_Text_ObjectSortedGUID.GetSize(); iText_ObjectSortedGUID++)
      {
         SSS.Format ("   Text_ObjectSortedGUID[%d] = {%d,%d,%d}\n", iText_ObjectSortedGUID, d_Text_ObjectSortedGUID[iText_ObjectSortedGUID].cl, iText_ObjectSortedGUID, d_Text_ObjectSortedGUID[iText_ObjectSortedGUID].id, iText_ObjectSortedGUID, d_Text_ObjectSortedGUID[iText_ObjectSortedGUID].rn);
         dbg += SSS;
      }

   // int Text_ModificationTime []
      SSS.Format ("Text_ModificationTime[].size = %d:\n", d_Text_ModificationTime.GetSize());
      dbg += SSS;
      for (int iText_ModificationTime=0; iText_ModificationTime<d_Text_ModificationTime.GetSize(); iText_ModificationTime++)
      {
         SSS.Format ("   Text_ModificationTime[%d] = %d\n", iText_ModificationTime, d_Text_ModificationTime[iText_ModificationTime]);
         dbg += SSS;
      }

   // int Text_WordAppearanceNum []
      SSS.Format ("Text_WordAppearanceNum[].size = %d:\n", d_Text_WordAppearanceNum.GetSize());
      dbg += SSS;
      for (int iText_WordAppearanceNum=0; iText_WordAppearanceNum<d_Text_WordAppearanceNum.GetSize(); iText_WordAppearanceNum++)
      {
         SSS.Format ("   Text_WordAppearanceNum[%d] = %d\n", iText_WordAppearanceNum, d_Text_WordAppearanceNum[iText_WordAppearanceNum]);
         dbg += SSS;
      }

   // int Text_WordFirstPosition []
      SSS.Format ("Text_WordFirstPosition[].size = %d:\n", d_Text_WordFirstPosition.GetSize());
      dbg += SSS;
      for (int iText_WordFirstPosition=0; iText_WordFirstPosition<d_Text_WordFirstPosition.GetSize(); iText_WordFirstPosition++)
      {
         SSS.Format ("   Text_WordFirstPosition[%d] = %d\n", iText_WordFirstPosition, d_Text_WordFirstPosition[iText_WordFirstPosition]);
         dbg += SSS;
      }
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_StopWord::OD_StopWord (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_StopWord_OD_StopWord);

      classID = OBJ_CLASS_ID_StopWord;


      m_CoIndexPtr = new OBD_pointer [1];
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
   }

// Деструктор
  OD_StopWord::~OD_StopWord () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_StopWord::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_StopWord_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Word;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_StopWord::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_StopWord_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Word
      size_t n_Word = (*(size_t*)(file+nOffset));  // n_Word = strlen (s_Word)+1;
      nOffset += sizeof(size_t);
      char * s_Word = new char [n_Word+1];
      LAY_MEMCPY (s_Word, file, nOffset, n_Word, file.GetSize(), Word);
      nOffset += n_Word;
      DECODE_STRING (n_Word, s_Word);
      d_Word = s_Word;
      delete [] s_Word;
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_StopWord::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_StopWord_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Word
      n_size += sizeof (size_t);
      n_size += d_Word.length()+1;

      return n_size;
   }

// Запись данных на диск
   bool OD_StopWord::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_StopWord_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string Word
      size_t n_Word = d_Word.length()+1;
      (*(size_t*)(file+nOffset)) = n_Word;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Word.c_str(), n_Word);
      ENCODE_STRING (n_Word, (char*)(file+nOffset));
      nOffset += n_Word;
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_StopWord::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_StopWord_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_StopWord], objID, d_randID);
      dbg += SSS;

   // string Word
      SSS.Format ("Word = '%s'\n", d_Word.c_str());
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_WordNibbleABC::OD_WordNibbleABC (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_OD_WordNibbleABC);

      classID = OBJ_CLASS_ID_WordNibbleABC;


      m_CoIndexPtr = new OBD_pointer [2];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_Num = 0;
      d_FreqPerMillion = (float) 0.0;
   }

// Деструктор
  OD_WordNibbleABC::~OD_WordNibbleABC () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_WordNibbleABC::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Nibble;              break;
         case 3: ka += d_Num;                 break;
         case 4: ka += d_FreqPerMillion;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_WordNibbleABC::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Nibble
      size_t n_Nibble = (*(size_t*)(file+nOffset));  // n_Nibble = strlen (s_Nibble)+1;
      nOffset += sizeof(size_t);
      char * s_Nibble = new char [n_Nibble+1];
      LAY_MEMCPY (s_Nibble, file, nOffset, n_Nibble, file.GetSize(), Nibble);
      nOffset += n_Nibble;
      DECODE_STRING (n_Nibble, s_Nibble);
      d_Nibble = s_Nibble;
      delete [] s_Nibble;

   // int Num
      d_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float FreqPerMillion
      d_FreqPerMillion = (*(float*)(file+nOffset));
      nOffset += sizeof(float);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_WordNibbleABC::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Nibble
      n_size += sizeof (size_t);
      n_size += d_Nibble.length()+1;

   // int Num
      n_size += sizeof (int);

   // float FreqPerMillion
      n_size += sizeof (float);

      return n_size;
   }

// Запись данных на диск
   bool OD_WordNibbleABC::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string Nibble
      size_t n_Nibble = d_Nibble.length()+1;
      (*(size_t*)(file+nOffset)) = n_Nibble;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Nibble.c_str(), n_Nibble);
      ENCODE_STRING (n_Nibble, (char*)(file+nOffset));
      nOffset += n_Nibble;

   // int Num
      (*(int*)(file+nOffset)) = d_Num;
      nOffset += sizeof (int);

   // float FreqPerMillion
      (*(float*)(file+nOffset)) = d_FreqPerMillion;
      nOffset += sizeof (float);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_WordNibbleABC::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_WordNibbleABC_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_WordNibbleABC], objID, d_randID);
      dbg += SSS;

   // string Nibble
      SSS.Format ("Nibble = '%s'\n", d_Nibble.c_str());
      dbg += SSS;

   // int Num
      SSS.Format ("Num = %d\n", d_Num);
      dbg += SSS;

   // float FreqPerMillion
      SSS.Format ("FreqPerMillion = %f\n", d_FreqPerMillion);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_WebFolder::OD_WebFolder (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_WebFolder_OD_WebFolder);

      classID = OBJ_CLASS_ID_WebFolder;


      m_CoIndexPtr = new OBD_pointer [4];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_WebFileSortedID.Alloc (0);
      d_ShowCount = 0;
      d_ClickCount = 0;
      d_CTR = (float) 0.0;
      d_Estimation_Tot = 0;
      d_Estimation_Num = 0;
      d_Estimation = (float) 0.0;
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_WebFolder::~OD_WebFolder () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_WebFolder::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_WebFolder_AddKeyVarForField);

      switch (fieldID)
      {
         case 3: ka += d_ShowCount;               break;
         case 4: ka += d_ClickCount;              break;
         case 5: ka += d_CTR;                     break;
         case 6: ka += d_Estimation_Tot;          break;
         case 7: ka += d_Estimation_Num;          break;
         case 8: ka += d_Estimation;              break;
         case 9: ka += d_ProxyObject;             break;
         case 12: ka += d_MOD_Base_GUID;           break;
         case 13: ka += d_MOD_Extension_GUID;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_WebFolder::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFolder_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier WebFileSortedID []
      int arr_size_WebFileSortedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_WebFileSortedID.Alloc (arr_size_WebFileSortedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,WebFileSortedID);

   // int ShowCount
      d_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickCount
      d_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float CTR
      d_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Estimation_Tot
      d_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Estimation_Num
      d_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Estimation
      d_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_WebFolder::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_WebFolder_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // identifier WebFileSortedID []
      n_size += sizeof (size_t);
      n_size += d_WebFileSortedID.GetSize() * sizeof(identifier);

   // int ShowCount
      n_size += sizeof (int);

   // int ClickCount
      n_size += sizeof (int);

   // float CTR
      n_size += sizeof (float);

   // int Estimation_Tot
      n_size += sizeof (int);

   // int Estimation_Num
      n_size += sizeof (int);

   // float Estimation
      n_size += sizeof (float);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_WebFolder::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFolder_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // identifier WebFileSortedID []
      (*(size_t*)(file+nOffset)) = d_WebFileSortedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,WebFileSortedID);

   // int ShowCount
      (*(int*)(file+nOffset)) = d_ShowCount;
      nOffset += sizeof (int);

   // int ClickCount
      (*(int*)(file+nOffset)) = d_ClickCount;
      nOffset += sizeof (int);

   // float CTR
      (*(float*)(file+nOffset)) = d_CTR;
      nOffset += sizeof (float);

   // int Estimation_Tot
      (*(int*)(file+nOffset)) = d_Estimation_Tot;
      nOffset += sizeof (int);

   // int Estimation_Num
      (*(int*)(file+nOffset)) = d_Estimation_Num;
      nOffset += sizeof (int);

   // float Estimation
      (*(float*)(file+nOffset)) = d_Estimation;
      nOffset += sizeof (float);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_WebFolder::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFolder_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_WebFolder], objID, d_randID);
      dbg += SSS;

   // identifier WebFileSortedID []
      SSS.Format ("WebFileSortedID[].size = %d:\n", d_WebFileSortedID.GetSize());
      dbg += SSS;
      for (int iWebFileSortedID=0; iWebFileSortedID<d_WebFileSortedID.GetSize(); iWebFileSortedID++)
      {
         SSS.Format ("   WebFileSortedID[%d] = %d\n", iWebFileSortedID, d_WebFileSortedID[iWebFileSortedID]);
         dbg += SSS;
      }

   // int ShowCount
      SSS.Format ("ShowCount = %d\n", d_ShowCount);
      dbg += SSS;

   // int ClickCount
      SSS.Format ("ClickCount = %d\n", d_ClickCount);
      dbg += SSS;

   // float CTR
      SSS.Format ("CTR = %f\n", d_CTR);
      dbg += SSS;

   // int Estimation_Tot
      SSS.Format ("Estimation_Tot = %d\n", d_Estimation_Tot);
      dbg += SSS;

   // int Estimation_Num
      SSS.Format ("Estimation_Num = %d\n", d_Estimation_Num);
      dbg += SSS;

   // float Estimation
      SSS.Format ("Estimation = %f\n", d_Estimation);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_WebFile::OD_WebFile (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_WebFile_OD_WebFile);

      classID = OBJ_CLASS_ID_WebFile;


      m_CoIndexPtr = new OBD_pointer [9];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      m_CoIndexPtr[5] = NULL;
      m_CoIndexPtr[6] = NULL;
      m_CoIndexPtr[7] = NULL;
      m_CoIndexPtr[8] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_WebFolderID.Alloc (0);
      d_AccessLevelThreshold = 0;
      d_CreationTime = 0;
      d_Version = 0;
      d_BinaryData.Alloc (0);
      d_ShowCount = 0;
      d_ClickCount = 0;
      d_CTR = (float) 0.0;
      d_Estimation_Tot = 0;
      d_Estimation_Num = 0;
      d_Estimation = (float) 0.0;
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
      d_SearchItemID.Alloc (0);
   }

// Деструктор
  OD_WebFile::~OD_WebFile () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_WebFile::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_WebFile_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Name_OSFile;               break;
         case 3: ka += d_Name_Upload;               break;
         case 4: ka += d_MIMEType;                  break;
         case 5: ka += d_IconType;                  break;
         case 7: ka += d_OwnerGUID;                 break;
         case 8: ka += d_AccessLevelThreshold;      break;
         case 9: ka += d_CreationTime;              break;
         case 10: ka += d_ModificationTime;          break;
         case 11: ka += d_LastAccessTime;            break;
         case 12: ka += d_Version;                   break;
         case 14: ka += d_ShowCount;                 break;
         case 15: ka += d_ClickCount;                break;
         case 16: ka += d_CTR;                       break;
         case 17: ka += d_Estimation_Tot;            break;
         case 18: ka += d_Estimation_Num;            break;
         case 19: ka += d_Estimation;                break;
         case 20: ka += d_ProxyObject;               break;
         case 23: ka += d_MOD_Base_GUID;             break;
         case 24: ka += d_MOD_Extension_GUID;        break;
         case 25: ka += d_Name;                      break;
         case 26: ka += d_Description;               break;
         case 27: ka += d_Text;                      break;
         case 28: ka += d_Additional;                break;
      }
   }


// Загрузка объекта с диска
   size_t OD_WebFile::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFile_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name_OSFile
      size_t n_Name_OSFile = (*(size_t*)(file+nOffset));  // n_Name_OSFile = strlen (s_Name_OSFile)+1;
      nOffset += sizeof(size_t);
      char * s_Name_OSFile = new char [n_Name_OSFile+1];
      LAY_MEMCPY (s_Name_OSFile, file, nOffset, n_Name_OSFile, file.GetSize(), Name_OSFile);
      nOffset += n_Name_OSFile;
      DECODE_STRING (n_Name_OSFile, s_Name_OSFile);
      d_Name_OSFile = s_Name_OSFile;
      delete [] s_Name_OSFile;

   // string Name_Upload
      size_t n_Name_Upload = (*(size_t*)(file+nOffset));  // n_Name_Upload = strlen (s_Name_Upload)+1;
      nOffset += sizeof(size_t);
      char * s_Name_Upload = new char [n_Name_Upload+1];
      LAY_MEMCPY (s_Name_Upload, file, nOffset, n_Name_Upload, file.GetSize(), Name_Upload);
      nOffset += n_Name_Upload;
      DECODE_STRING (n_Name_Upload, s_Name_Upload);
      d_Name_Upload = s_Name_Upload;
      delete [] s_Name_Upload;

   // string MIMEType
      size_t n_MIMEType = (*(size_t*)(file+nOffset));  // n_MIMEType = strlen (s_MIMEType)+1;
      nOffset += sizeof(size_t);
      char * s_MIMEType = new char [n_MIMEType+1];
      LAY_MEMCPY (s_MIMEType, file, nOffset, n_MIMEType, file.GetSize(), MIMEType);
      nOffset += n_MIMEType;
      DECODE_STRING (n_MIMEType, s_MIMEType);
      d_MIMEType = s_MIMEType;
      delete [] s_MIMEType;

   // string IconType
      size_t n_IconType = (*(size_t*)(file+nOffset));  // n_IconType = strlen (s_IconType)+1;
      nOffset += sizeof(size_t);
      char * s_IconType = new char [n_IconType+1];
      LAY_MEMCPY (s_IconType, file, nOffset, n_IconType, file.GetSize(), IconType);
      nOffset += n_IconType;
      DECODE_STRING (n_IconType, s_IconType);
      d_IconType = s_IconType;
      delete [] s_IconType;

   // identifier WebFolderID []
      int arr_size_WebFolderID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_WebFolderID.Alloc (arr_size_WebFolderID);
      OD_LOAD_SIMPLE_ARRAY (identifier,WebFolderID);

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ModificationTime
      d_ModificationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int LastAccessTime
      d_LastAccessTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Version
      d_Version = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // byte BinaryData []
      int arr_size_BinaryData = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_BinaryData.Alloc (arr_size_BinaryData);
      OD_LOAD_SIMPLE_ARRAY (byte,BinaryData);

   // int ShowCount
      d_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickCount
      d_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float CTR
      d_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Estimation_Tot
      d_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Estimation_Num
      d_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Estimation
      d_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // string Text
      size_t n_Text = (*(size_t*)(file+nOffset));  // n_Text = strlen (s_Text)+1;
      nOffset += sizeof(size_t);
      char * s_Text = new char [n_Text+1];
      LAY_MEMCPY (s_Text, file, nOffset, n_Text, file.GetSize(), Text);
      nOffset += n_Text;
      DECODE_STRING (n_Text, s_Text);
      d_Text = s_Text;
      delete [] s_Text;

   // string Additional
      size_t n_Additional = (*(size_t*)(file+nOffset));  // n_Additional = strlen (s_Additional)+1;
      nOffset += sizeof(size_t);
      char * s_Additional = new char [n_Additional+1];
      LAY_MEMCPY (s_Additional, file, nOffset, n_Additional, file.GetSize(), Additional);
      nOffset += n_Additional;
      DECODE_STRING (n_Additional, s_Additional);
      d_Additional = s_Additional;
      delete [] s_Additional;

   // identifier SearchItemID []
      int arr_size_SearchItemID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SearchItemID.Alloc (arr_size_SearchItemID);
      OD_LOAD_SIMPLE_ARRAY (identifier,SearchItemID);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_WebFile::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_WebFile_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Name_OSFile
      n_size += sizeof (size_t);
      n_size += d_Name_OSFile.length()+1;

   // string Name_Upload
      n_size += sizeof (size_t);
      n_size += d_Name_Upload.length()+1;

   // string MIMEType
      n_size += sizeof (size_t);
      n_size += d_MIMEType.length()+1;

   // string IconType
      n_size += sizeof (size_t);
      n_size += d_IconType.length()+1;

   // identifier WebFolderID []
      n_size += sizeof (size_t);
      n_size += d_WebFolderID.GetSize() * sizeof(identifier);

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

   // int CreationTime
      n_size += sizeof (int);

   // int ModificationTime
      n_size += sizeof (int);

   // int LastAccessTime
      n_size += sizeof (int);

   // int Version
      n_size += sizeof (int);

   // byte BinaryData []
      n_size += sizeof (size_t);
      n_size += d_BinaryData.GetSize() * sizeof(byte);

   // int ShowCount
      n_size += sizeof (int);

   // int ClickCount
      n_size += sizeof (int);

   // float CTR
      n_size += sizeof (float);

   // int Estimation_Tot
      n_size += sizeof (int);

   // int Estimation_Num
      n_size += sizeof (int);

   // float Estimation
      n_size += sizeof (float);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // string Text
      n_size += sizeof (size_t);
      n_size += d_Text.length()+1;

   // string Additional
      n_size += sizeof (size_t);
      n_size += d_Additional.length()+1;

   // identifier SearchItemID []
      n_size += sizeof (size_t);
      n_size += d_SearchItemID.GetSize() * sizeof(identifier);

      return n_size;
   }

// Запись данных на диск
   bool OD_WebFile::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFile_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string Name_OSFile
      size_t n_Name_OSFile = d_Name_OSFile.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name_OSFile;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name_OSFile.c_str(), n_Name_OSFile);
      ENCODE_STRING (n_Name_OSFile, (char*)(file+nOffset));
      nOffset += n_Name_OSFile;

   // string Name_Upload
      size_t n_Name_Upload = d_Name_Upload.length()+1;
      (*(size_t*)(file+nOffset)) = n_Name_Upload;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Name_Upload.c_str(), n_Name_Upload);
      ENCODE_STRING (n_Name_Upload, (char*)(file+nOffset));
      nOffset += n_Name_Upload;

   // string MIMEType
      size_t n_MIMEType = d_MIMEType.length()+1;
      (*(size_t*)(file+nOffset)) = n_MIMEType;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_MIMEType.c_str(), n_MIMEType);
      ENCODE_STRING (n_MIMEType, (char*)(file+nOffset));
      nOffset += n_MIMEType;

   // string IconType
      size_t n_IconType = d_IconType.length()+1;
      (*(size_t*)(file+nOffset)) = n_IconType;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_IconType.c_str(), n_IconType);
      ENCODE_STRING (n_IconType, (char*)(file+nOffset));
      nOffset += n_IconType;

   // identifier WebFolderID []
      (*(size_t*)(file+nOffset)) = d_WebFolderID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,WebFolderID);

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // int ModificationTime
      (*(int*)(file+nOffset)) = d_ModificationTime;
      nOffset += sizeof (int);

   // int LastAccessTime
      (*(int*)(file+nOffset)) = d_LastAccessTime;
      nOffset += sizeof (int);

   // int Version
      (*(int*)(file+nOffset)) = d_Version;
      nOffset += sizeof (int);

   // byte BinaryData []
      (*(size_t*)(file+nOffset)) = d_BinaryData.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,BinaryData);

   // int ShowCount
      (*(int*)(file+nOffset)) = d_ShowCount;
      nOffset += sizeof (int);

   // int ClickCount
      (*(int*)(file+nOffset)) = d_ClickCount;
      nOffset += sizeof (int);

   // float CTR
      (*(float*)(file+nOffset)) = d_CTR;
      nOffset += sizeof (float);

   // int Estimation_Tot
      (*(int*)(file+nOffset)) = d_Estimation_Tot;
      nOffset += sizeof (int);

   // int Estimation_Num
      (*(int*)(file+nOffset)) = d_Estimation_Num;
      nOffset += sizeof (int);

   // float Estimation
      (*(float*)(file+nOffset)) = d_Estimation;
      nOffset += sizeof (float);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);

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

   // string Text
      size_t n_Text = d_Text.length()+1;
      (*(size_t*)(file+nOffset)) = n_Text;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Text.c_str(), n_Text);
      ENCODE_STRING (n_Text, (char*)(file+nOffset));
      nOffset += n_Text;

   // string Additional
      size_t n_Additional = d_Additional.length()+1;
      (*(size_t*)(file+nOffset)) = n_Additional;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Additional.c_str(), n_Additional);
      ENCODE_STRING (n_Additional, (char*)(file+nOffset));
      nOffset += n_Additional;

   // identifier SearchItemID []
      (*(size_t*)(file+nOffset)) = d_SearchItemID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SearchItemID);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_WebFile::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_WebFile_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_WebFile], objID, d_randID);
      dbg += SSS;

   // string Name_OSFile
      SSS.Format ("Name_OSFile = '%s'\n", d_Name_OSFile.c_str());
      dbg += SSS;

   // string Name_Upload
      SSS.Format ("Name_Upload = '%s'\n", d_Name_Upload.c_str());
      dbg += SSS;

   // string MIMEType
      SSS.Format ("MIMEType = '%s'\n", d_MIMEType.c_str());
      dbg += SSS;

   // string IconType
      SSS.Format ("IconType = '%s'\n", d_IconType.c_str());
      dbg += SSS;

   // identifier WebFolderID []
      SSS.Format ("WebFolderID[].size = %d:\n", d_WebFolderID.GetSize());
      dbg += SSS;
      for (int iWebFolderID=0; iWebFolderID<d_WebFolderID.GetSize(); iWebFolderID++)
      {
         SSS.Format ("   WebFolderID[%d] = %d\n", iWebFolderID, d_WebFolderID[iWebFolderID]);
         dbg += SSS;
      }

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // int ModificationTime
      SSS.Format ("ModificationTime = %d\n", d_ModificationTime);
      dbg += SSS;

   // int LastAccessTime
      SSS.Format ("LastAccessTime = %d\n", d_LastAccessTime);
      dbg += SSS;

   // int Version
      SSS.Format ("Version = %d\n", d_Version);
      dbg += SSS;

   // byte BinaryData []
      SSS.Format ("BinaryData[].size = %d:\n", d_BinaryData.GetSize());
      dbg += SSS;
      for (int iBinaryData=0; iBinaryData<d_BinaryData.GetSize(); iBinaryData++)
      {
         SSS.Format ("   BinaryData[%d] = %d\n", iBinaryData, d_BinaryData[iBinaryData]);
         dbg += SSS;
      }

   // int ShowCount
      SSS.Format ("ShowCount = %d\n", d_ShowCount);
      dbg += SSS;

   // int ClickCount
      SSS.Format ("ClickCount = %d\n", d_ClickCount);
      dbg += SSS;

   // float CTR
      SSS.Format ("CTR = %f\n", d_CTR);
      dbg += SSS;

   // int Estimation_Tot
      SSS.Format ("Estimation_Tot = %d\n", d_Estimation_Tot);
      dbg += SSS;

   // int Estimation_Num
      SSS.Format ("Estimation_Num = %d\n", d_Estimation_Num);
      dbg += SSS;

   // float Estimation
      SSS.Format ("Estimation = %f\n", d_Estimation);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // string Text
      SSS.Format ("Text = '%s'\n", d_Text.c_str());
      dbg += SSS;

   // string Additional
      SSS.Format ("Additional = '%s'\n", d_Additional.c_str());
      dbg += SSS;

   // identifier SearchItemID []
      SSS.Format ("SearchItemID[].size = %d:\n", d_SearchItemID.GetSize());
      dbg += SSS;
      for (int iSearchItemID=0; iSearchItemID<d_SearchItemID.GetSize(); iSearchItemID++)
      {
         SSS.Format ("   SearchItemID[%d] = %d\n", iSearchItemID, d_SearchItemID[iSearchItemID]);
         dbg += SSS;
      }
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_UserProfile::OD_UserProfile (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_UserProfile_OD_UserProfile);

      classID = OBJ_CLASS_ID_UserProfile;


      m_CoIndexPtr = new OBD_pointer [5];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_InfoDiv_Hide.Alloc (0);
      d_InfoDiv_Show.Alloc (0);
      d_Filter_Name.Alloc (0);
      d_Filter_SearchPhrase.Alloc (0);
      d_Filter_FolderID.Alloc (0);
      d_SeenIO_ID.Alloc (0);
      d_SeenIO_Time.Alloc (0);
      d_SeenIO_Estimation.Alloc (0);
      d_SeenIO_ShowCount = 0;
      d_SeenIO_ClickCount = 0;
      d_SeenIO_CTR = (float) 0.0;
      d_OwnIO.Alloc (0);
      d_OwnIO_Time.Alloc (0);
      d_OwnIO_ShowCount = 0;
      d_OwnIO_ClickCount = 0;
      d_OwnIO_CTR = (float) 0.0;
      d_OwnIO_Estimation_Tot = 0;
      d_OwnIO_Estimation_Num = 0;
      d_OwnIO_Estimation = (float) 0.0;
      d_Log_ObjectGUID.Alloc (0);
      d_Log_Action.Alloc (0);
      d_Log_Time.Alloc (0);
      d_Account_Enable = false;
      d_Account_Debit = (float) 0.0;
      d_Account_Credit = (float) 0.0;
      d_Account_Log_Action.Alloc (0);
      d_Account_Log_Amount.Alloc (0);
      d_Account_Log_Debit.Alloc (0);
      d_Account_Log_Credit.Alloc (0);
      d_Account_Log_Time.Alloc (0);
      d_Account_Log_Comment.Alloc (0);
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_UserProfile::~OD_UserProfile () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_UserProfile::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_UserProfile_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_UserGUID;                  break;
         case 11: ka += d_SeenIO_ShowCount;          break;
         case 12: ka += d_SeenIO_ClickCount;         break;
         case 13: ka += d_SeenIO_CTR;                break;
         case 16: ka += d_OwnIO_ShowCount;           break;
         case 17: ka += d_OwnIO_ClickCount;          break;
         case 18: ka += d_OwnIO_CTR;                 break;
         case 19: ka += d_OwnIO_Estimation_Tot;      break;
         case 20: ka += d_OwnIO_Estimation_Num;      break;
         case 21: ka += d_OwnIO_Estimation;          break;
         case 25: ka += d_Account_Enable;            break;
         case 26: ka += d_Account_Debit;             break;
         case 27: ka += d_Account_Credit;            break;
         case 34: ka += d_RootFolderGUID;            break;
         case 35: ka += d_ProxyObject;               break;
         case 38: ka += d_MOD_Base_GUID;             break;
         case 39: ka += d_MOD_Extension_GUID;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_UserProfile::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserProfile_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // guid UserGUID
      d_UserGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // identifier InfoDiv_Hide []
      int arr_size_InfoDiv_Hide = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoDiv_Hide.Alloc (arr_size_InfoDiv_Hide);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoDiv_Hide);

   // identifier InfoDiv_Show []
      int arr_size_InfoDiv_Show = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoDiv_Show.Alloc (arr_size_InfoDiv_Show);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoDiv_Show);

   // string Filter_Name []
      int arr_size_Filter_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Filter_Name.Alloc (arr_size_Filter_Name);
      for (int iFilter_Name=0; iFilter_Name<(int)arr_size_Filter_Name; iFilter_Name++)
      {
         string tmp_Filter_Name;
         size_t n_Filter_Name = (*(size_t*)(file+nOffset));  // n_Filter_Name = strlen (s_Filter_Name)+1;
         nOffset += sizeof(size_t);
         char * s_Filter_Name = new char [n_Filter_Name+1];
         LAY_MEMCPY (s_Filter_Name, file, nOffset, n_Filter_Name, file.GetSize(), Filter_Name);
         nOffset += n_Filter_Name;
         DECODE_STRING (n_Filter_Name, s_Filter_Name);
         tmp_Filter_Name = s_Filter_Name;
         delete [] s_Filter_Name;

         d_Filter_Name[iFilter_Name] = tmp_Filter_Name;
      }

   // string Filter_SearchPhrase []
      int arr_size_Filter_SearchPhrase = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Filter_SearchPhrase.Alloc (arr_size_Filter_SearchPhrase);
      for (int iFilter_SearchPhrase=0; iFilter_SearchPhrase<(int)arr_size_Filter_SearchPhrase; iFilter_SearchPhrase++)
      {
         string tmp_Filter_SearchPhrase;
         size_t n_Filter_SearchPhrase = (*(size_t*)(file+nOffset));  // n_Filter_SearchPhrase = strlen (s_Filter_SearchPhrase)+1;
         nOffset += sizeof(size_t);
         char * s_Filter_SearchPhrase = new char [n_Filter_SearchPhrase+1];
         LAY_MEMCPY (s_Filter_SearchPhrase, file, nOffset, n_Filter_SearchPhrase, file.GetSize(), Filter_SearchPhrase);
         nOffset += n_Filter_SearchPhrase;
         DECODE_STRING (n_Filter_SearchPhrase, s_Filter_SearchPhrase);
         tmp_Filter_SearchPhrase = s_Filter_SearchPhrase;
         delete [] s_Filter_SearchPhrase;

         d_Filter_SearchPhrase[iFilter_SearchPhrase] = tmp_Filter_SearchPhrase;
      }

   // identifier Filter_FolderID []
      int arr_size_Filter_FolderID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Filter_FolderID.Alloc (arr_size_Filter_FolderID);
      OD_LOAD_SIMPLE_ARRAY (identifier,Filter_FolderID);

   // identifier SeenIO_ID []
      int arr_size_SeenIO_ID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SeenIO_ID.Alloc (arr_size_SeenIO_ID);
      OD_LOAD_SIMPLE_ARRAY (identifier,SeenIO_ID);

   // int SeenIO_Time []
      int arr_size_SeenIO_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SeenIO_Time.Alloc (arr_size_SeenIO_Time);
      OD_LOAD_SIMPLE_ARRAY (int,SeenIO_Time);

   // byte SeenIO_Estimation []
      int arr_size_SeenIO_Estimation = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SeenIO_Estimation.Alloc (arr_size_SeenIO_Estimation);
      OD_LOAD_SIMPLE_ARRAY (byte,SeenIO_Estimation);

   // int SeenIO_ShowCount
      d_SeenIO_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int SeenIO_ClickCount
      d_SeenIO_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float SeenIO_CTR
      d_SeenIO_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // identifier OwnIO []
      int arr_size_OwnIO = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_OwnIO.Alloc (arr_size_OwnIO);
      OD_LOAD_SIMPLE_ARRAY (identifier,OwnIO);

   // int OwnIO_Time []
      int arr_size_OwnIO_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_OwnIO_Time.Alloc (arr_size_OwnIO_Time);
      OD_LOAD_SIMPLE_ARRAY (int,OwnIO_Time);

   // int OwnIO_ShowCount
      d_OwnIO_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int OwnIO_ClickCount
      d_OwnIO_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float OwnIO_CTR
      d_OwnIO_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int OwnIO_Estimation_Tot
      d_OwnIO_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int OwnIO_Estimation_Num
      d_OwnIO_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float OwnIO_Estimation
      d_OwnIO_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // guid Log_ObjectGUID []
      int arr_size_Log_ObjectGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_ObjectGUID.Alloc (arr_size_Log_ObjectGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,Log_ObjectGUID);

   // int Log_Action []
      int arr_size_Log_Action = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_Action.Alloc (arr_size_Log_Action);
      OD_LOAD_SIMPLE_ARRAY (int,Log_Action);

   // int Log_Time []
      int arr_size_Log_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_Time.Alloc (arr_size_Log_Time);
      OD_LOAD_SIMPLE_ARRAY (int,Log_Time);

   // bool Account_Enable
      d_Account_Enable = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // float Account_Debit
      d_Account_Debit = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // float Account_Credit
      d_Account_Credit = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Account_Log_Action []
      int arr_size_Account_Log_Action = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Action.Alloc (arr_size_Account_Log_Action);
      OD_LOAD_SIMPLE_ARRAY (int,Account_Log_Action);

   // float Account_Log_Amount []
      int arr_size_Account_Log_Amount = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Amount.Alloc (arr_size_Account_Log_Amount);
      OD_LOAD_SIMPLE_ARRAY (float,Account_Log_Amount);

   // float Account_Log_Debit []
      int arr_size_Account_Log_Debit = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Debit.Alloc (arr_size_Account_Log_Debit);
      OD_LOAD_SIMPLE_ARRAY (float,Account_Log_Debit);

   // float Account_Log_Credit []
      int arr_size_Account_Log_Credit = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Credit.Alloc (arr_size_Account_Log_Credit);
      OD_LOAD_SIMPLE_ARRAY (float,Account_Log_Credit);

   // int Account_Log_Time []
      int arr_size_Account_Log_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Time.Alloc (arr_size_Account_Log_Time);
      OD_LOAD_SIMPLE_ARRAY (int,Account_Log_Time);

   // string Account_Log_Comment []
      int arr_size_Account_Log_Comment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Account_Log_Comment.Alloc (arr_size_Account_Log_Comment);
      for (int iAccount_Log_Comment=0; iAccount_Log_Comment<(int)arr_size_Account_Log_Comment; iAccount_Log_Comment++)
      {
         string tmp_Account_Log_Comment;
         size_t n_Account_Log_Comment = (*(size_t*)(file+nOffset));  // n_Account_Log_Comment = strlen (s_Account_Log_Comment)+1;
         nOffset += sizeof(size_t);
         char * s_Account_Log_Comment = new char [n_Account_Log_Comment+1];
         LAY_MEMCPY (s_Account_Log_Comment, file, nOffset, n_Account_Log_Comment, file.GetSize(), Account_Log_Comment);
         nOffset += n_Account_Log_Comment;
         DECODE_STRING (n_Account_Log_Comment, s_Account_Log_Comment);
         tmp_Account_Log_Comment = s_Account_Log_Comment;
         delete [] s_Account_Log_Comment;

         d_Account_Log_Comment[iAccount_Log_Comment] = tmp_Account_Log_Comment;
      }

   // guid RootFolderGUID
      d_RootFolderGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_UserProfile::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_UserProfile_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // guid UserGUID
      n_size += sizeof (guid);

   // identifier InfoDiv_Hide []
      n_size += sizeof (size_t);
      n_size += d_InfoDiv_Hide.GetSize() * sizeof(identifier);

   // identifier InfoDiv_Show []
      n_size += sizeof (size_t);
      n_size += d_InfoDiv_Show.GetSize() * sizeof(identifier);

   // string Filter_Name []
      n_size += sizeof (size_t);
      for (int iFilter_Name=0; iFilter_Name<d_Filter_Name.GetSize(); iFilter_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_Filter_Name[iFilter_Name].length()+1;
      }

   // string Filter_SearchPhrase []
      n_size += sizeof (size_t);
      for (int iFilter_SearchPhrase=0; iFilter_SearchPhrase<d_Filter_SearchPhrase.GetSize(); iFilter_SearchPhrase++)
      {
         n_size += sizeof (size_t);
         n_size += d_Filter_SearchPhrase[iFilter_SearchPhrase].length()+1;
      }

   // identifier Filter_FolderID []
      n_size += sizeof (size_t);
      n_size += d_Filter_FolderID.GetSize() * sizeof(identifier);

   // identifier SeenIO_ID []
      n_size += sizeof (size_t);
      n_size += d_SeenIO_ID.GetSize() * sizeof(identifier);

   // int SeenIO_Time []
      n_size += sizeof (size_t);
      n_size += d_SeenIO_Time.GetSize() * sizeof(int);

   // byte SeenIO_Estimation []
      n_size += sizeof (size_t);
      n_size += d_SeenIO_Estimation.GetSize() * sizeof(byte);

   // int SeenIO_ShowCount
      n_size += sizeof (int);

   // int SeenIO_ClickCount
      n_size += sizeof (int);

   // float SeenIO_CTR
      n_size += sizeof (float);

   // identifier OwnIO []
      n_size += sizeof (size_t);
      n_size += d_OwnIO.GetSize() * sizeof(identifier);

   // int OwnIO_Time []
      n_size += sizeof (size_t);
      n_size += d_OwnIO_Time.GetSize() * sizeof(int);

   // int OwnIO_ShowCount
      n_size += sizeof (int);

   // int OwnIO_ClickCount
      n_size += sizeof (int);

   // float OwnIO_CTR
      n_size += sizeof (float);

   // int OwnIO_Estimation_Tot
      n_size += sizeof (int);

   // int OwnIO_Estimation_Num
      n_size += sizeof (int);

   // float OwnIO_Estimation
      n_size += sizeof (float);

   // guid Log_ObjectGUID []
      n_size += sizeof (size_t);
      n_size += d_Log_ObjectGUID.GetSize() * sizeof(guid);

   // int Log_Action []
      n_size += sizeof (size_t);
      n_size += d_Log_Action.GetSize() * sizeof(int);

   // int Log_Time []
      n_size += sizeof (size_t);
      n_size += d_Log_Time.GetSize() * sizeof(int);

   // bool Account_Enable
      n_size += sizeof (bool);

   // float Account_Debit
      n_size += sizeof (float);

   // float Account_Credit
      n_size += sizeof (float);

   // int Account_Log_Action []
      n_size += sizeof (size_t);
      n_size += d_Account_Log_Action.GetSize() * sizeof(int);

   // float Account_Log_Amount []
      n_size += sizeof (size_t);
      n_size += d_Account_Log_Amount.GetSize() * sizeof(float);

   // float Account_Log_Debit []
      n_size += sizeof (size_t);
      n_size += d_Account_Log_Debit.GetSize() * sizeof(float);

   // float Account_Log_Credit []
      n_size += sizeof (size_t);
      n_size += d_Account_Log_Credit.GetSize() * sizeof(float);

   // int Account_Log_Time []
      n_size += sizeof (size_t);
      n_size += d_Account_Log_Time.GetSize() * sizeof(int);

   // string Account_Log_Comment []
      n_size += sizeof (size_t);
      for (int iAccount_Log_Comment=0; iAccount_Log_Comment<d_Account_Log_Comment.GetSize(); iAccount_Log_Comment++)
      {
         n_size += sizeof (size_t);
         n_size += d_Account_Log_Comment[iAccount_Log_Comment].length()+1;
      }

   // guid RootFolderGUID
      n_size += sizeof (guid);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_UserProfile::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserProfile_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // guid UserGUID
      (*(guid*)(file+nOffset)) = d_UserGUID;
      nOffset += sizeof (guid);

   // identifier InfoDiv_Hide []
      (*(size_t*)(file+nOffset)) = d_InfoDiv_Hide.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoDiv_Hide);

   // identifier InfoDiv_Show []
      (*(size_t*)(file+nOffset)) = d_InfoDiv_Show.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoDiv_Show);

   // string Filter_Name []
      (*(size_t*)(file+nOffset)) = d_Filter_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFilter_Name=0; iFilter_Name<d_Filter_Name.GetSize(); iFilter_Name++)
      {
         size_t n_Filter_Name = d_Filter_Name[iFilter_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_Filter_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Filter_Name[iFilter_Name].c_str(), n_Filter_Name);
         ENCODE_STRING (n_Filter_Name, (char*)(file+nOffset));
         nOffset += n_Filter_Name;
      }

   // string Filter_SearchPhrase []
      (*(size_t*)(file+nOffset)) = d_Filter_SearchPhrase.GetSize();
      nOffset += sizeof(size_t);
      for (int iFilter_SearchPhrase=0; iFilter_SearchPhrase<d_Filter_SearchPhrase.GetSize(); iFilter_SearchPhrase++)
      {
         size_t n_Filter_SearchPhrase = d_Filter_SearchPhrase[iFilter_SearchPhrase].length()+1;
         (*(size_t*)(file+nOffset)) = n_Filter_SearchPhrase;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Filter_SearchPhrase[iFilter_SearchPhrase].c_str(), n_Filter_SearchPhrase);
         ENCODE_STRING (n_Filter_SearchPhrase, (char*)(file+nOffset));
         nOffset += n_Filter_SearchPhrase;
      }

   // identifier Filter_FolderID []
      (*(size_t*)(file+nOffset)) = d_Filter_FolderID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,Filter_FolderID);

   // identifier SeenIO_ID []
      (*(size_t*)(file+nOffset)) = d_SeenIO_ID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SeenIO_ID);

   // int SeenIO_Time []
      (*(size_t*)(file+nOffset)) = d_SeenIO_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,SeenIO_Time);

   // byte SeenIO_Estimation []
      (*(size_t*)(file+nOffset)) = d_SeenIO_Estimation.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (byte,SeenIO_Estimation);

   // int SeenIO_ShowCount
      (*(int*)(file+nOffset)) = d_SeenIO_ShowCount;
      nOffset += sizeof (int);

   // int SeenIO_ClickCount
      (*(int*)(file+nOffset)) = d_SeenIO_ClickCount;
      nOffset += sizeof (int);

   // float SeenIO_CTR
      (*(float*)(file+nOffset)) = d_SeenIO_CTR;
      nOffset += sizeof (float);

   // identifier OwnIO []
      (*(size_t*)(file+nOffset)) = d_OwnIO.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,OwnIO);

   // int OwnIO_Time []
      (*(size_t*)(file+nOffset)) = d_OwnIO_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,OwnIO_Time);

   // int OwnIO_ShowCount
      (*(int*)(file+nOffset)) = d_OwnIO_ShowCount;
      nOffset += sizeof (int);

   // int OwnIO_ClickCount
      (*(int*)(file+nOffset)) = d_OwnIO_ClickCount;
      nOffset += sizeof (int);

   // float OwnIO_CTR
      (*(float*)(file+nOffset)) = d_OwnIO_CTR;
      nOffset += sizeof (float);

   // int OwnIO_Estimation_Tot
      (*(int*)(file+nOffset)) = d_OwnIO_Estimation_Tot;
      nOffset += sizeof (int);

   // int OwnIO_Estimation_Num
      (*(int*)(file+nOffset)) = d_OwnIO_Estimation_Num;
      nOffset += sizeof (int);

   // float OwnIO_Estimation
      (*(float*)(file+nOffset)) = d_OwnIO_Estimation;
      nOffset += sizeof (float);

   // guid Log_ObjectGUID []
      (*(size_t*)(file+nOffset)) = d_Log_ObjectGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,Log_ObjectGUID);

   // int Log_Action []
      (*(size_t*)(file+nOffset)) = d_Log_Action.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Log_Action);

   // int Log_Time []
      (*(size_t*)(file+nOffset)) = d_Log_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Log_Time);

   // bool Account_Enable
      (*(bool*)(file+nOffset)) = d_Account_Enable;
      nOffset += sizeof (bool);

   // float Account_Debit
      (*(float*)(file+nOffset)) = d_Account_Debit;
      nOffset += sizeof (float);

   // float Account_Credit
      (*(float*)(file+nOffset)) = d_Account_Credit;
      nOffset += sizeof (float);

   // int Account_Log_Action []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Action.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Account_Log_Action);

   // float Account_Log_Amount []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Amount.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (float,Account_Log_Amount);

   // float Account_Log_Debit []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Debit.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (float,Account_Log_Debit);

   // float Account_Log_Credit []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Credit.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (float,Account_Log_Credit);

   // int Account_Log_Time []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Account_Log_Time);

   // string Account_Log_Comment []
      (*(size_t*)(file+nOffset)) = d_Account_Log_Comment.GetSize();
      nOffset += sizeof(size_t);
      for (int iAccount_Log_Comment=0; iAccount_Log_Comment<d_Account_Log_Comment.GetSize(); iAccount_Log_Comment++)
      {
         size_t n_Account_Log_Comment = d_Account_Log_Comment[iAccount_Log_Comment].length()+1;
         (*(size_t*)(file+nOffset)) = n_Account_Log_Comment;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Account_Log_Comment[iAccount_Log_Comment].c_str(), n_Account_Log_Comment);
         ENCODE_STRING (n_Account_Log_Comment, (char*)(file+nOffset));
         nOffset += n_Account_Log_Comment;
      }

   // guid RootFolderGUID
      (*(guid*)(file+nOffset)) = d_RootFolderGUID;
      nOffset += sizeof (guid);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_UserProfile::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_UserProfile_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_UserProfile], objID, d_randID);
      dbg += SSS;

   // guid UserGUID
      SSS.Format ("UserGUID = {%d,%d,%d}\n", d_UserGUID.cl, d_UserGUID.id, d_UserGUID.rn);
      dbg += SSS;

   // identifier InfoDiv_Hide []
      SSS.Format ("InfoDiv_Hide[].size = %d:\n", d_InfoDiv_Hide.GetSize());
      dbg += SSS;
      for (int iInfoDiv_Hide=0; iInfoDiv_Hide<d_InfoDiv_Hide.GetSize(); iInfoDiv_Hide++)
      {
         SSS.Format ("   InfoDiv_Hide[%d] = %d\n", iInfoDiv_Hide, d_InfoDiv_Hide[iInfoDiv_Hide]);
         dbg += SSS;
      }

   // identifier InfoDiv_Show []
      SSS.Format ("InfoDiv_Show[].size = %d:\n", d_InfoDiv_Show.GetSize());
      dbg += SSS;
      for (int iInfoDiv_Show=0; iInfoDiv_Show<d_InfoDiv_Show.GetSize(); iInfoDiv_Show++)
      {
         SSS.Format ("   InfoDiv_Show[%d] = %d\n", iInfoDiv_Show, d_InfoDiv_Show[iInfoDiv_Show]);
         dbg += SSS;
      }

   // string Filter_Name []
      SSS.Format ("Filter_Name[].size = %d:\n", d_Filter_Name.GetSize());
      dbg += SSS;
      for (int iFilter_Name=0; iFilter_Name<d_Filter_Name.GetSize(); iFilter_Name++)
      {
         SSS.Format ("   Filter_Name[%d] = '%s'\n", iFilter_Name, d_Filter_Name[iFilter_Name].c_str());
         dbg += SSS;
      }

   // string Filter_SearchPhrase []
      SSS.Format ("Filter_SearchPhrase[].size = %d:\n", d_Filter_SearchPhrase.GetSize());
      dbg += SSS;
      for (int iFilter_SearchPhrase=0; iFilter_SearchPhrase<d_Filter_SearchPhrase.GetSize(); iFilter_SearchPhrase++)
      {
         SSS.Format ("   Filter_SearchPhrase[%d] = '%s'\n", iFilter_SearchPhrase, d_Filter_SearchPhrase[iFilter_SearchPhrase].c_str());
         dbg += SSS;
      }

   // identifier Filter_FolderID []
      SSS.Format ("Filter_FolderID[].size = %d:\n", d_Filter_FolderID.GetSize());
      dbg += SSS;
      for (int iFilter_FolderID=0; iFilter_FolderID<d_Filter_FolderID.GetSize(); iFilter_FolderID++)
      {
         SSS.Format ("   Filter_FolderID[%d] = %d\n", iFilter_FolderID, d_Filter_FolderID[iFilter_FolderID]);
         dbg += SSS;
      }

   // identifier SeenIO_ID []
      SSS.Format ("SeenIO_ID[].size = %d:\n", d_SeenIO_ID.GetSize());
      dbg += SSS;
      for (int iSeenIO_ID=0; iSeenIO_ID<d_SeenIO_ID.GetSize(); iSeenIO_ID++)
      {
         SSS.Format ("   SeenIO_ID[%d] = %d\n", iSeenIO_ID, d_SeenIO_ID[iSeenIO_ID]);
         dbg += SSS;
      }

   // int SeenIO_Time []
      SSS.Format ("SeenIO_Time[].size = %d:\n", d_SeenIO_Time.GetSize());
      dbg += SSS;
      for (int iSeenIO_Time=0; iSeenIO_Time<d_SeenIO_Time.GetSize(); iSeenIO_Time++)
      {
         SSS.Format ("   SeenIO_Time[%d] = %d\n", iSeenIO_Time, d_SeenIO_Time[iSeenIO_Time]);
         dbg += SSS;
      }

   // byte SeenIO_Estimation []
      SSS.Format ("SeenIO_Estimation[].size = %d:\n", d_SeenIO_Estimation.GetSize());
      dbg += SSS;
      for (int iSeenIO_Estimation=0; iSeenIO_Estimation<d_SeenIO_Estimation.GetSize(); iSeenIO_Estimation++)
      {
         SSS.Format ("   SeenIO_Estimation[%d] = %d\n", iSeenIO_Estimation, d_SeenIO_Estimation[iSeenIO_Estimation]);
         dbg += SSS;
      }

   // int SeenIO_ShowCount
      SSS.Format ("SeenIO_ShowCount = %d\n", d_SeenIO_ShowCount);
      dbg += SSS;

   // int SeenIO_ClickCount
      SSS.Format ("SeenIO_ClickCount = %d\n", d_SeenIO_ClickCount);
      dbg += SSS;

   // float SeenIO_CTR
      SSS.Format ("SeenIO_CTR = %f\n", d_SeenIO_CTR);
      dbg += SSS;

   // identifier OwnIO []
      SSS.Format ("OwnIO[].size = %d:\n", d_OwnIO.GetSize());
      dbg += SSS;
      for (int iOwnIO=0; iOwnIO<d_OwnIO.GetSize(); iOwnIO++)
      {
         SSS.Format ("   OwnIO[%d] = %d\n", iOwnIO, d_OwnIO[iOwnIO]);
         dbg += SSS;
      }

   // int OwnIO_Time []
      SSS.Format ("OwnIO_Time[].size = %d:\n", d_OwnIO_Time.GetSize());
      dbg += SSS;
      for (int iOwnIO_Time=0; iOwnIO_Time<d_OwnIO_Time.GetSize(); iOwnIO_Time++)
      {
         SSS.Format ("   OwnIO_Time[%d] = %d\n", iOwnIO_Time, d_OwnIO_Time[iOwnIO_Time]);
         dbg += SSS;
      }

   // int OwnIO_ShowCount
      SSS.Format ("OwnIO_ShowCount = %d\n", d_OwnIO_ShowCount);
      dbg += SSS;

   // int OwnIO_ClickCount
      SSS.Format ("OwnIO_ClickCount = %d\n", d_OwnIO_ClickCount);
      dbg += SSS;

   // float OwnIO_CTR
      SSS.Format ("OwnIO_CTR = %f\n", d_OwnIO_CTR);
      dbg += SSS;

   // int OwnIO_Estimation_Tot
      SSS.Format ("OwnIO_Estimation_Tot = %d\n", d_OwnIO_Estimation_Tot);
      dbg += SSS;

   // int OwnIO_Estimation_Num
      SSS.Format ("OwnIO_Estimation_Num = %d\n", d_OwnIO_Estimation_Num);
      dbg += SSS;

   // float OwnIO_Estimation
      SSS.Format ("OwnIO_Estimation = %f\n", d_OwnIO_Estimation);
      dbg += SSS;

   // guid Log_ObjectGUID []
      SSS.Format ("Log_ObjectGUID[].size = %d:\n", d_Log_ObjectGUID.GetSize());
      dbg += SSS;
      for (int iLog_ObjectGUID=0; iLog_ObjectGUID<d_Log_ObjectGUID.GetSize(); iLog_ObjectGUID++)
      {
         SSS.Format ("   Log_ObjectGUID[%d] = {%d,%d,%d}\n", iLog_ObjectGUID, d_Log_ObjectGUID[iLog_ObjectGUID].cl, iLog_ObjectGUID, d_Log_ObjectGUID[iLog_ObjectGUID].id, iLog_ObjectGUID, d_Log_ObjectGUID[iLog_ObjectGUID].rn);
         dbg += SSS;
      }

   // int Log_Action []
      SSS.Format ("Log_Action[].size = %d:\n", d_Log_Action.GetSize());
      dbg += SSS;
      for (int iLog_Action=0; iLog_Action<d_Log_Action.GetSize(); iLog_Action++)
      {
         SSS.Format ("   Log_Action[%d] = %d\n", iLog_Action, d_Log_Action[iLog_Action]);
         dbg += SSS;
      }

   // int Log_Time []
      SSS.Format ("Log_Time[].size = %d:\n", d_Log_Time.GetSize());
      dbg += SSS;
      for (int iLog_Time=0; iLog_Time<d_Log_Time.GetSize(); iLog_Time++)
      {
         SSS.Format ("   Log_Time[%d] = %d\n", iLog_Time, d_Log_Time[iLog_Time]);
         dbg += SSS;
      }

   // bool Account_Enable
      SSS.Format ("Account_Enable = %s\n", d_Account_Enable?"true":"false");
      dbg += SSS;

   // float Account_Debit
      SSS.Format ("Account_Debit = %f\n", d_Account_Debit);
      dbg += SSS;

   // float Account_Credit
      SSS.Format ("Account_Credit = %f\n", d_Account_Credit);
      dbg += SSS;

   // int Account_Log_Action []
      SSS.Format ("Account_Log_Action[].size = %d:\n", d_Account_Log_Action.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Action=0; iAccount_Log_Action<d_Account_Log_Action.GetSize(); iAccount_Log_Action++)
      {
         SSS.Format ("   Account_Log_Action[%d] = %d\n", iAccount_Log_Action, d_Account_Log_Action[iAccount_Log_Action]);
         dbg += SSS;
      }

   // float Account_Log_Amount []
      SSS.Format ("Account_Log_Amount[].size = %d:\n", d_Account_Log_Amount.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Amount=0; iAccount_Log_Amount<d_Account_Log_Amount.GetSize(); iAccount_Log_Amount++)
      {
         SSS.Format ("   Account_Log_Amount[%d] = %f\n", iAccount_Log_Amount, d_Account_Log_Amount[iAccount_Log_Amount]);
         dbg += SSS;
      }

   // float Account_Log_Debit []
      SSS.Format ("Account_Log_Debit[].size = %d:\n", d_Account_Log_Debit.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Debit=0; iAccount_Log_Debit<d_Account_Log_Debit.GetSize(); iAccount_Log_Debit++)
      {
         SSS.Format ("   Account_Log_Debit[%d] = %f\n", iAccount_Log_Debit, d_Account_Log_Debit[iAccount_Log_Debit]);
         dbg += SSS;
      }

   // float Account_Log_Credit []
      SSS.Format ("Account_Log_Credit[].size = %d:\n", d_Account_Log_Credit.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Credit=0; iAccount_Log_Credit<d_Account_Log_Credit.GetSize(); iAccount_Log_Credit++)
      {
         SSS.Format ("   Account_Log_Credit[%d] = %f\n", iAccount_Log_Credit, d_Account_Log_Credit[iAccount_Log_Credit]);
         dbg += SSS;
      }

   // int Account_Log_Time []
      SSS.Format ("Account_Log_Time[].size = %d:\n", d_Account_Log_Time.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Time=0; iAccount_Log_Time<d_Account_Log_Time.GetSize(); iAccount_Log_Time++)
      {
         SSS.Format ("   Account_Log_Time[%d] = %d\n", iAccount_Log_Time, d_Account_Log_Time[iAccount_Log_Time]);
         dbg += SSS;
      }

   // string Account_Log_Comment []
      SSS.Format ("Account_Log_Comment[].size = %d:\n", d_Account_Log_Comment.GetSize());
      dbg += SSS;
      for (int iAccount_Log_Comment=0; iAccount_Log_Comment<d_Account_Log_Comment.GetSize(); iAccount_Log_Comment++)
      {
         SSS.Format ("   Account_Log_Comment[%d] = '%s'\n", iAccount_Log_Comment, d_Account_Log_Comment[iAccount_Log_Comment].c_str());
         dbg += SSS;
      }

   // guid RootFolderGUID
      SSS.Format ("RootFolderGUID = {%d,%d,%d}\n", d_RootFolderGUID.cl, d_RootFolderGUID.id, d_RootFolderGUID.rn);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_InfoDiv::OD_InfoDiv (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_InfoDiv_OD_InfoDiv);

      classID = OBJ_CLASS_ID_InfoDiv;


      m_CoIndexPtr = new OBD_pointer [4];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_InfoSourceSortedID.Alloc (0);
      d_InfoObjectSortedID.Alloc (0);
      d_ShowCount = 0;
      d_ClickCount = 0;
      d_CTR = (float) 0.0;
      d_Estimation_Tot = 0;
      d_Estimation_Num = 0;
      d_Estimation = (float) 0.0;
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_InfoDiv::~OD_InfoDiv () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_InfoDiv::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_InfoDiv_AddKeyVarForField);

      switch (fieldID)
      {
         case 4: ka += d_ClipArtGUID;             break;
         case 5: ka += d_ShowCount;               break;
         case 6: ka += d_ClickCount;              break;
         case 7: ka += d_CTR;                     break;
         case 8: ka += d_Estimation_Tot;          break;
         case 9: ka += d_Estimation_Num;          break;
         case 10: ka += d_Estimation;              break;
         case 11: ka += d_ProxyObject;             break;
         case 14: ka += d_MOD_Base_GUID;           break;
         case 15: ka += d_MOD_Extension_GUID;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_InfoDiv::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoDiv_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier InfoSourceSortedID []
      int arr_size_InfoSourceSortedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoSourceSortedID.Alloc (arr_size_InfoSourceSortedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoSourceSortedID);

   // identifier InfoObjectSortedID []
      int arr_size_InfoObjectSortedID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoObjectSortedID.Alloc (arr_size_InfoObjectSortedID);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoObjectSortedID);

   // guid ClipArtGUID
      d_ClipArtGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int ShowCount
      d_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickCount
      d_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float CTR
      d_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Estimation_Tot
      d_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Estimation_Num
      d_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Estimation
      d_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_InfoDiv::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_InfoDiv_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // identifier InfoSourceSortedID []
      n_size += sizeof (size_t);
      n_size += d_InfoSourceSortedID.GetSize() * sizeof(identifier);

   // identifier InfoObjectSortedID []
      n_size += sizeof (size_t);
      n_size += d_InfoObjectSortedID.GetSize() * sizeof(identifier);

   // guid ClipArtGUID
      n_size += sizeof (guid);

   // int ShowCount
      n_size += sizeof (int);

   // int ClickCount
      n_size += sizeof (int);

   // float CTR
      n_size += sizeof (float);

   // int Estimation_Tot
      n_size += sizeof (int);

   // int Estimation_Num
      n_size += sizeof (int);

   // float Estimation
      n_size += sizeof (float);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_InfoDiv::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoDiv_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // identifier InfoSourceSortedID []
      (*(size_t*)(file+nOffset)) = d_InfoSourceSortedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoSourceSortedID);

   // identifier InfoObjectSortedID []
      (*(size_t*)(file+nOffset)) = d_InfoObjectSortedID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoObjectSortedID);

   // guid ClipArtGUID
      (*(guid*)(file+nOffset)) = d_ClipArtGUID;
      nOffset += sizeof (guid);

   // int ShowCount
      (*(int*)(file+nOffset)) = d_ShowCount;
      nOffset += sizeof (int);

   // int ClickCount
      (*(int*)(file+nOffset)) = d_ClickCount;
      nOffset += sizeof (int);

   // float CTR
      (*(float*)(file+nOffset)) = d_CTR;
      nOffset += sizeof (float);

   // int Estimation_Tot
      (*(int*)(file+nOffset)) = d_Estimation_Tot;
      nOffset += sizeof (int);

   // int Estimation_Num
      (*(int*)(file+nOffset)) = d_Estimation_Num;
      nOffset += sizeof (int);

   // float Estimation
      (*(float*)(file+nOffset)) = d_Estimation;
      nOffset += sizeof (float);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_InfoDiv::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoDiv_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_InfoDiv], objID, d_randID);
      dbg += SSS;

   // identifier InfoSourceSortedID []
      SSS.Format ("InfoSourceSortedID[].size = %d:\n", d_InfoSourceSortedID.GetSize());
      dbg += SSS;
      for (int iInfoSourceSortedID=0; iInfoSourceSortedID<d_InfoSourceSortedID.GetSize(); iInfoSourceSortedID++)
      {
         SSS.Format ("   InfoSourceSortedID[%d] = %d\n", iInfoSourceSortedID, d_InfoSourceSortedID[iInfoSourceSortedID]);
         dbg += SSS;
      }

   // identifier InfoObjectSortedID []
      SSS.Format ("InfoObjectSortedID[].size = %d:\n", d_InfoObjectSortedID.GetSize());
      dbg += SSS;
      for (int iInfoObjectSortedID=0; iInfoObjectSortedID<d_InfoObjectSortedID.GetSize(); iInfoObjectSortedID++)
      {
         SSS.Format ("   InfoObjectSortedID[%d] = %d\n", iInfoObjectSortedID, d_InfoObjectSortedID[iInfoObjectSortedID]);
         dbg += SSS;
      }

   // guid ClipArtGUID
      SSS.Format ("ClipArtGUID = {%d,%d,%d}\n", d_ClipArtGUID.cl, d_ClipArtGUID.id, d_ClipArtGUID.rn);
      dbg += SSS;

   // int ShowCount
      SSS.Format ("ShowCount = %d\n", d_ShowCount);
      dbg += SSS;

   // int ClickCount
      SSS.Format ("ClickCount = %d\n", d_ClickCount);
      dbg += SSS;

   // float CTR
      SSS.Format ("CTR = %f\n", d_CTR);
      dbg += SSS;

   // int Estimation_Tot
      SSS.Format ("Estimation_Tot = %d\n", d_Estimation_Tot);
      dbg += SSS;

   // int Estimation_Num
      SSS.Format ("Estimation_Num = %d\n", d_Estimation_Num);
      dbg += SSS;

   // float Estimation
      SSS.Format ("Estimation = %f\n", d_Estimation);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_InfoSource::OD_InfoSource (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_InfoSource_OD_InfoSource);

      classID = OBJ_CLASS_ID_InfoSource;


      m_CoIndexPtr = new OBD_pointer [6];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      m_CoIndexPtr[5] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_InfoDivID.Alloc (0);
      d_ColumnistGUID.Alloc (0);
      d_ShowCount = 0;
      d_ClickCount = 0;
      d_CTR = (float) 0.0;
      d_Estimation_Tot = 0;
      d_Estimation_Num = 0;
      d_Estimation = (float) 0.0;
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_InfoSource::~OD_InfoSource () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_InfoSource::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_InfoSource_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_Name;                    break;
         case 3: ka += d_Description;             break;
         case 4: ka += d_URL;                     break;
         case 5: ka += d_RefreshType;             break;
         case 7: ka += d_LogoGUID;                break;
         case 9: ka += d_Address;                 break;
         case 10: ka += d_Language;                break;
         case 11: ka += d_Type;                    break;
         case 12: ka += d_State;                   break;
         case 13: ka += d_ShowCount;               break;
         case 14: ka += d_ClickCount;              break;
         case 15: ka += d_CTR;                     break;
         case 16: ka += d_Estimation_Tot;          break;
         case 17: ka += d_Estimation_Num;          break;
         case 18: ka += d_Estimation;              break;
         case 19: ka += d_ProxyObject;             break;
         case 22: ka += d_MOD_Base_GUID;           break;
         case 23: ka += d_MOD_Extension_GUID;      break;
      }
   }


// Загрузка объекта с диска
   size_t OD_InfoSource::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoSource_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL+1];
      LAY_MEMCPY (s_URL, file, nOffset, n_URL, file.GetSize(), URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // int RefreshType
      d_RefreshType = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier InfoDivID []
      int arr_size_InfoDivID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoDivID.Alloc (arr_size_InfoDivID);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoDivID);

   // guid LogoGUID
      d_LogoGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid ColumnistGUID []
      int arr_size_ColumnistGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ColumnistGUID.Alloc (arr_size_ColumnistGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,ColumnistGUID);

   // string Address
      size_t n_Address = (*(size_t*)(file+nOffset));  // n_Address = strlen (s_Address)+1;
      nOffset += sizeof(size_t);
      char * s_Address = new char [n_Address+1];
      LAY_MEMCPY (s_Address, file, nOffset, n_Address, file.GetSize(), Address);
      nOffset += n_Address;
      DECODE_STRING (n_Address, s_Address);
      d_Address = s_Address;
      delete [] s_Address;

   // string Language
      size_t n_Language = (*(size_t*)(file+nOffset));  // n_Language = strlen (s_Language)+1;
      nOffset += sizeof(size_t);
      char * s_Language = new char [n_Language+1];
      LAY_MEMCPY (s_Language, file, nOffset, n_Language, file.GetSize(), Language);
      nOffset += n_Language;
      DECODE_STRING (n_Language, s_Language);
      d_Language = s_Language;
      delete [] s_Language;

   // string Type
      size_t n_Type = (*(size_t*)(file+nOffset));  // n_Type = strlen (s_Type)+1;
      nOffset += sizeof(size_t);
      char * s_Type = new char [n_Type+1];
      LAY_MEMCPY (s_Type, file, nOffset, n_Type, file.GetSize(), Type);
      nOffset += n_Type;
      DECODE_STRING (n_Type, s_Type);
      d_Type = s_Type;
      delete [] s_Type;

   // string State
      size_t n_State = (*(size_t*)(file+nOffset));  // n_State = strlen (s_State)+1;
      nOffset += sizeof(size_t);
      char * s_State = new char [n_State+1];
      LAY_MEMCPY (s_State, file, nOffset, n_State, file.GetSize(), State);
      nOffset += n_State;
      DECODE_STRING (n_State, s_State);
      d_State = s_State;
      delete [] s_State;

   // int ShowCount
      d_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickCount
      d_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float CTR
      d_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Estimation_Tot
      d_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Estimation_Num
      d_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Estimation
      d_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_InfoSource::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_InfoSource_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // int RefreshType
      n_size += sizeof (int);

   // identifier InfoDivID []
      n_size += sizeof (size_t);
      n_size += d_InfoDivID.GetSize() * sizeof(identifier);

   // guid LogoGUID
      n_size += sizeof (guid);

   // guid ColumnistGUID []
      n_size += sizeof (size_t);
      n_size += d_ColumnistGUID.GetSize() * sizeof(guid);

   // string Address
      n_size += sizeof (size_t);
      n_size += d_Address.length()+1;

   // string Language
      n_size += sizeof (size_t);
      n_size += d_Language.length()+1;

   // string Type
      n_size += sizeof (size_t);
      n_size += d_Type.length()+1;

   // string State
      n_size += sizeof (size_t);
      n_size += d_State.length()+1;

   // int ShowCount
      n_size += sizeof (int);

   // int ClickCount
      n_size += sizeof (int);

   // float CTR
      n_size += sizeof (float);

   // int Estimation_Tot
      n_size += sizeof (int);

   // int Estimation_Num
      n_size += sizeof (int);

   // float Estimation
      n_size += sizeof (float);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_InfoSource::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoSource_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

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

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // int RefreshType
      (*(int*)(file+nOffset)) = d_RefreshType;
      nOffset += sizeof (int);

   // identifier InfoDivID []
      (*(size_t*)(file+nOffset)) = d_InfoDivID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoDivID);

   // guid LogoGUID
      (*(guid*)(file+nOffset)) = d_LogoGUID;
      nOffset += sizeof (guid);

   // guid ColumnistGUID []
      (*(size_t*)(file+nOffset)) = d_ColumnistGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,ColumnistGUID);

   // string Address
      size_t n_Address = d_Address.length()+1;
      (*(size_t*)(file+nOffset)) = n_Address;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Address.c_str(), n_Address);
      ENCODE_STRING (n_Address, (char*)(file+nOffset));
      nOffset += n_Address;

   // string Language
      size_t n_Language = d_Language.length()+1;
      (*(size_t*)(file+nOffset)) = n_Language;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Language.c_str(), n_Language);
      ENCODE_STRING (n_Language, (char*)(file+nOffset));
      nOffset += n_Language;

   // string Type
      size_t n_Type = d_Type.length()+1;
      (*(size_t*)(file+nOffset)) = n_Type;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Type.c_str(), n_Type);
      ENCODE_STRING (n_Type, (char*)(file+nOffset));
      nOffset += n_Type;

   // string State
      size_t n_State = d_State.length()+1;
      (*(size_t*)(file+nOffset)) = n_State;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_State.c_str(), n_State);
      ENCODE_STRING (n_State, (char*)(file+nOffset));
      nOffset += n_State;

   // int ShowCount
      (*(int*)(file+nOffset)) = d_ShowCount;
      nOffset += sizeof (int);

   // int ClickCount
      (*(int*)(file+nOffset)) = d_ClickCount;
      nOffset += sizeof (int);

   // float CTR
      (*(float*)(file+nOffset)) = d_CTR;
      nOffset += sizeof (float);

   // int Estimation_Tot
      (*(int*)(file+nOffset)) = d_Estimation_Tot;
      nOffset += sizeof (int);

   // int Estimation_Num
      (*(int*)(file+nOffset)) = d_Estimation_Num;
      nOffset += sizeof (int);

   // float Estimation
      (*(float*)(file+nOffset)) = d_Estimation;
      nOffset += sizeof (float);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_InfoSource::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoSource_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_InfoSource], objID, d_randID);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // int RefreshType
      SSS.Format ("RefreshType = %d\n", d_RefreshType);
      dbg += SSS;

   // identifier InfoDivID []
      SSS.Format ("InfoDivID[].size = %d:\n", d_InfoDivID.GetSize());
      dbg += SSS;
      for (int iInfoDivID=0; iInfoDivID<d_InfoDivID.GetSize(); iInfoDivID++)
      {
         SSS.Format ("   InfoDivID[%d] = %d\n", iInfoDivID, d_InfoDivID[iInfoDivID]);
         dbg += SSS;
      }

   // guid LogoGUID
      SSS.Format ("LogoGUID = {%d,%d,%d}\n", d_LogoGUID.cl, d_LogoGUID.id, d_LogoGUID.rn);
      dbg += SSS;

   // guid ColumnistGUID []
      SSS.Format ("ColumnistGUID[].size = %d:\n", d_ColumnistGUID.GetSize());
      dbg += SSS;
      for (int iColumnistGUID=0; iColumnistGUID<d_ColumnistGUID.GetSize(); iColumnistGUID++)
      {
         SSS.Format ("   ColumnistGUID[%d] = {%d,%d,%d}\n", iColumnistGUID, d_ColumnistGUID[iColumnistGUID].cl, iColumnistGUID, d_ColumnistGUID[iColumnistGUID].id, iColumnistGUID, d_ColumnistGUID[iColumnistGUID].rn);
         dbg += SSS;
      }

   // string Address
      SSS.Format ("Address = '%s'\n", d_Address.c_str());
      dbg += SSS;

   // string Language
      SSS.Format ("Language = '%s'\n", d_Language.c_str());
      dbg += SSS;

   // string Type
      SSS.Format ("Type = '%s'\n", d_Type.c_str());
      dbg += SSS;

   // string State
      SSS.Format ("State = '%s'\n", d_State.c_str());
      dbg += SSS;

   // int ShowCount
      SSS.Format ("ShowCount = %d\n", d_ShowCount);
      dbg += SSS;

   // int ClickCount
      SSS.Format ("ClickCount = %d\n", d_ClickCount);
      dbg += SSS;

   // float CTR
      SSS.Format ("CTR = %f\n", d_CTR);
      dbg += SSS;

   // int Estimation_Tot
      SSS.Format ("Estimation_Tot = %d\n", d_Estimation_Tot);
      dbg += SSS;

   // int Estimation_Num
      SSS.Format ("Estimation_Num = %d\n", d_Estimation_Num);
      dbg += SSS;

   // float Estimation
      SSS.Format ("Estimation = %f\n", d_Estimation);
      dbg += SSS;

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
      dbg += SSS;
      dbg += "\n";
      return true;
   }
// Конструктор
   OD_InfoObject::OD_InfoObject (bool bFieldsInit)
   {
   DEBUG_STACK_NAME (OD_InfoObject_OD_InfoObject);

      classID = OBJ_CLASS_ID_InfoObject;


      m_CoIndexPtr = new OBD_pointer [9];
      m_CoIndexPtr[0] = NULL;
      m_CoIndexPtr[1] = NULL;
      m_CoIndexPtr[2] = NULL;
      m_CoIndexPtr[3] = NULL;
      m_CoIndexPtr[4] = NULL;
      m_CoIndexPtr[5] = NULL;
      m_CoIndexPtr[6] = NULL;
      m_CoIndexPtr[7] = NULL;
      m_CoIndexPtr[8] = NULL;
      if (!bFieldsInit) return;

      d_randID = (identifier(rand()*time(0))/10+1);
      d_AccessLevelThreshold = 0;
      d_CreationTime = 0;
      d_InfoTime = 0;
      d_InfoDivID.Alloc (0);
      d_UsageStrictAccess = true;
      d_Log_Action.Alloc (0);
      d_Log_UserGUID.Alloc (0);
      d_Log_Time.Alloc (0);
      d_Log_Comment.Alloc (0);
      d_ArtworkGUID.Alloc (0);
      d_InfoSourceID = NA;
      d_AuthorID = NA;
      d_RelatedLinks.Alloc (0);
      d_CategoryID.Alloc (0);
      d_ShowCount = 0;
      d_ClickCount = 0;
      d_CTR = (float) 0.0;
      d_Estimation_Tot = 0;
      d_Estimation_Num = 0;
      d_Estimation = (float) 0.0;
      d_SearchItemID.Alloc (0);
      d_FIELD_Extension_Name.Alloc (0);
      d_FIELD_Extension_Value.Alloc (0);
   }

// Деструктор
  OD_InfoObject::~OD_InfoObject () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}


// Создание внешнего набора ключей
   void OD_InfoObject::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
   DEBUG_STACK_NAME (OD_InfoObject_AddKeyVarForField);

      switch (fieldID)
      {
         case 2: ka += d_SysName;                   break;
         case 3: ka += d_OwnerGUID;                 break;
         case 4: ka += d_AccessLevelThreshold;      break;
         case 5: ka += d_CreationTime;              break;
         case 6: ka += d_InfoTime;                  break;
         case 8: ka += d_UsageStrictAccess;         break;
         case 13: ka += d_IconGUID;                  break;
         case 14: ka += d_OriginalText;              break;
         case 16: ka += d_InfoSourceID;              break;
         case 17: ka += d_AuthorID;                  break;
         case 18: ka += d_AuthorStr;                 break;
         case 19: ka += d_URL;                       break;
         case 22: ka += d_ShowCount;                 break;
         case 23: ka += d_ClickCount;                break;
         case 24: ka += d_CTR;                       break;
         case 25: ka += d_Estimation_Tot;            break;
         case 26: ka += d_Estimation_Num;            break;
         case 27: ka += d_Estimation;                break;
         case 28: ka += d_Name;                      break;
         case 29: ka += d_Description;               break;
         case 30: ka += d_Text;                      break;
         case 31: ka += d_Additional;                break;
         case 33: ka += d_ProxyObject;               break;
         case 36: ka += d_MOD_Base_GUID;             break;
         case 37: ka += d_MOD_Extension_GUID;        break;
      }
   }


// Загрузка объекта с диска
   size_t OD_InfoObject::LoadFromFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoObject_LoadFromFile);

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
         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);}
         return 0;
      }

   // identifier randID
      d_randID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string SysName
      size_t n_SysName = (*(size_t*)(file+nOffset));  // n_SysName = strlen (s_SysName)+1;
      nOffset += sizeof(size_t);
      char * s_SysName = new char [n_SysName+1];
      LAY_MEMCPY (s_SysName, file, nOffset, n_SysName, file.GetSize(), SysName);
      nOffset += n_SysName;
      DECODE_STRING (n_SysName, s_SysName);
      d_SysName = s_SysName;
      delete [] s_SysName;

   // guid OwnerGUID
      d_OwnerGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // int AccessLevelThreshold
      d_AccessLevelThreshold = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int CreationTime
      d_CreationTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int InfoTime
      d_InfoTime = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // identifier InfoDivID []
      int arr_size_InfoDivID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_InfoDivID.Alloc (arr_size_InfoDivID);
      OD_LOAD_SIMPLE_ARRAY (identifier,InfoDivID);

   // bool UsageStrictAccess
      d_UsageStrictAccess = (*(bool*)(file+nOffset));
      nOffset += sizeof(bool);

   // int Log_Action []
      int arr_size_Log_Action = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_Action.Alloc (arr_size_Log_Action);
      OD_LOAD_SIMPLE_ARRAY (int,Log_Action);

   // guid Log_UserGUID []
      int arr_size_Log_UserGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_UserGUID.Alloc (arr_size_Log_UserGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,Log_UserGUID);

   // int Log_Time []
      int arr_size_Log_Time = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_Time.Alloc (arr_size_Log_Time);
      OD_LOAD_SIMPLE_ARRAY (int,Log_Time);

   // string Log_Comment []
      int arr_size_Log_Comment = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_Log_Comment.Alloc (arr_size_Log_Comment);
      for (int iLog_Comment=0; iLog_Comment<(int)arr_size_Log_Comment; iLog_Comment++)
      {
         string tmp_Log_Comment;
         size_t n_Log_Comment = (*(size_t*)(file+nOffset));  // n_Log_Comment = strlen (s_Log_Comment)+1;
         nOffset += sizeof(size_t);
         char * s_Log_Comment = new char [n_Log_Comment+1];
         LAY_MEMCPY (s_Log_Comment, file, nOffset, n_Log_Comment, file.GetSize(), Log_Comment);
         nOffset += n_Log_Comment;
         DECODE_STRING (n_Log_Comment, s_Log_Comment);
         tmp_Log_Comment = s_Log_Comment;
         delete [] s_Log_Comment;

         d_Log_Comment[iLog_Comment] = tmp_Log_Comment;
      }

   // guid IconGUID
      d_IconGUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string OriginalText
      size_t n_OriginalText = (*(size_t*)(file+nOffset));  // n_OriginalText = strlen (s_OriginalText)+1;
      nOffset += sizeof(size_t);
      char * s_OriginalText = new char [n_OriginalText+1];
      LAY_MEMCPY (s_OriginalText, file, nOffset, n_OriginalText, file.GetSize(), OriginalText);
      nOffset += n_OriginalText;
      DECODE_STRING (n_OriginalText, s_OriginalText);
      d_OriginalText = s_OriginalText;
      delete [] s_OriginalText;

   // guid ArtworkGUID []
      int arr_size_ArtworkGUID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_ArtworkGUID.Alloc (arr_size_ArtworkGUID);
      OD_LOAD_SIMPLE_ARRAY (guid,ArtworkGUID);

   // identifier InfoSourceID
      d_InfoSourceID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // identifier AuthorID
      d_AuthorID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);

   // string AuthorStr
      size_t n_AuthorStr = (*(size_t*)(file+nOffset));  // n_AuthorStr = strlen (s_AuthorStr)+1;
      nOffset += sizeof(size_t);
      char * s_AuthorStr = new char [n_AuthorStr+1];
      LAY_MEMCPY (s_AuthorStr, file, nOffset, n_AuthorStr, file.GetSize(), AuthorStr);
      nOffset += n_AuthorStr;
      DECODE_STRING (n_AuthorStr, s_AuthorStr);
      d_AuthorStr = s_AuthorStr;
      delete [] s_AuthorStr;

   // string URL
      size_t n_URL = (*(size_t*)(file+nOffset));  // n_URL = strlen (s_URL)+1;
      nOffset += sizeof(size_t);
      char * s_URL = new char [n_URL+1];
      LAY_MEMCPY (s_URL, file, nOffset, n_URL, file.GetSize(), URL);
      nOffset += n_URL;
      DECODE_STRING (n_URL, s_URL);
      d_URL = s_URL;
      delete [] s_URL;

   // string RelatedLinks []
      int arr_size_RelatedLinks = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_RelatedLinks.Alloc (arr_size_RelatedLinks);
      for (int iRelatedLinks=0; iRelatedLinks<(int)arr_size_RelatedLinks; iRelatedLinks++)
      {
         string tmp_RelatedLinks;
         size_t n_RelatedLinks = (*(size_t*)(file+nOffset));  // n_RelatedLinks = strlen (s_RelatedLinks)+1;
         nOffset += sizeof(size_t);
         char * s_RelatedLinks = new char [n_RelatedLinks+1];
         LAY_MEMCPY (s_RelatedLinks, file, nOffset, n_RelatedLinks, file.GetSize(), RelatedLinks);
         nOffset += n_RelatedLinks;
         DECODE_STRING (n_RelatedLinks, s_RelatedLinks);
         tmp_RelatedLinks = s_RelatedLinks;
         delete [] s_RelatedLinks;

         d_RelatedLinks[iRelatedLinks] = tmp_RelatedLinks;
      }

   // identifier CategoryID []
      int arr_size_CategoryID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_CategoryID.Alloc (arr_size_CategoryID);
      OD_LOAD_SIMPLE_ARRAY (identifier,CategoryID);

   // int ShowCount
      d_ShowCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int ClickCount
      d_ClickCount = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float CTR
      d_CTR = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // int Estimation_Tot
      d_Estimation_Tot = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int Estimation_Num
      d_Estimation_Num = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // float Estimation
      d_Estimation = (*(float*)(file+nOffset));
      nOffset += sizeof(float);

   // string Name
      size_t n_Name = (*(size_t*)(file+nOffset));  // n_Name = strlen (s_Name)+1;
      nOffset += sizeof(size_t);
      char * s_Name = new char [n_Name+1];
      LAY_MEMCPY (s_Name, file, nOffset, n_Name, file.GetSize(), Name);
      nOffset += n_Name;
      DECODE_STRING (n_Name, s_Name);
      d_Name = s_Name;
      delete [] s_Name;

   // string Description
      size_t n_Description = (*(size_t*)(file+nOffset));  // n_Description = strlen (s_Description)+1;
      nOffset += sizeof(size_t);
      char * s_Description = new char [n_Description+1];
      LAY_MEMCPY (s_Description, file, nOffset, n_Description, file.GetSize(), Description);
      nOffset += n_Description;
      DECODE_STRING (n_Description, s_Description);
      d_Description = s_Description;
      delete [] s_Description;

   // string Text
      size_t n_Text = (*(size_t*)(file+nOffset));  // n_Text = strlen (s_Text)+1;
      nOffset += sizeof(size_t);
      char * s_Text = new char [n_Text+1];
      LAY_MEMCPY (s_Text, file, nOffset, n_Text, file.GetSize(), Text);
      nOffset += n_Text;
      DECODE_STRING (n_Text, s_Text);
      d_Text = s_Text;
      delete [] s_Text;

   // string Additional
      size_t n_Additional = (*(size_t*)(file+nOffset));  // n_Additional = strlen (s_Additional)+1;
      nOffset += sizeof(size_t);
      char * s_Additional = new char [n_Additional+1];
      LAY_MEMCPY (s_Additional, file, nOffset, n_Additional, file.GetSize(), Additional);
      nOffset += n_Additional;
      DECODE_STRING (n_Additional, s_Additional);
      d_Additional = s_Additional;
      delete [] s_Additional;

   // identifier SearchItemID []
      int arr_size_SearchItemID = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_SearchItemID.Alloc (arr_size_SearchItemID);
      OD_LOAD_SIMPLE_ARRAY (identifier,SearchItemID);

   // guid ProxyObject
      d_ProxyObject = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // string FIELD_Extension_Name []
      int arr_size_FIELD_Extension_Name = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Name.Alloc (arr_size_FIELD_Extension_Name);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<(int)arr_size_FIELD_Extension_Name; iFIELD_Extension_Name++)
      {
         string tmp_FIELD_Extension_Name;
         size_t n_FIELD_Extension_Name = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Name = strlen (s_FIELD_Extension_Name)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Name = new char [n_FIELD_Extension_Name+1];
         LAY_MEMCPY (s_FIELD_Extension_Name, file, nOffset, n_FIELD_Extension_Name, file.GetSize(), FIELD_Extension_Name);
         nOffset += n_FIELD_Extension_Name;
         DECODE_STRING (n_FIELD_Extension_Name, s_FIELD_Extension_Name);
         tmp_FIELD_Extension_Name = s_FIELD_Extension_Name;
         delete [] s_FIELD_Extension_Name;

         d_FIELD_Extension_Name[iFIELD_Extension_Name] = tmp_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      int arr_size_FIELD_Extension_Value = (*(size_t*)(file+nOffset));
      nOffset += sizeof(size_t);
      d_FIELD_Extension_Value.Alloc (arr_size_FIELD_Extension_Value);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<(int)arr_size_FIELD_Extension_Value; iFIELD_Extension_Value++)
      {
         string tmp_FIELD_Extension_Value;
         size_t n_FIELD_Extension_Value = (*(size_t*)(file+nOffset));  // n_FIELD_Extension_Value = strlen (s_FIELD_Extension_Value)+1;
         nOffset += sizeof(size_t);
         char * s_FIELD_Extension_Value = new char [n_FIELD_Extension_Value+1];
         LAY_MEMCPY (s_FIELD_Extension_Value, file, nOffset, n_FIELD_Extension_Value, file.GetSize(), FIELD_Extension_Value);
         nOffset += n_FIELD_Extension_Value;
         DECODE_STRING (n_FIELD_Extension_Value, s_FIELD_Extension_Value);
         tmp_FIELD_Extension_Value = s_FIELD_Extension_Value;
         delete [] s_FIELD_Extension_Value;

         d_FIELD_Extension_Value[iFIELD_Extension_Value] = tmp_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      d_MOD_Base_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);

   // guid MOD_Extension_GUID
      d_MOD_Extension_GUID = (*(guid*)(file+nOffset));
      nOffset += sizeof(guid);
      return nOffset;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_InfoObject::CalculateSize ()
   {
   DEBUG_STACK_NAME (OD_InfoObject_CalculateSize);

      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // identifier randID
      n_size += sizeof (identifier);

   // string SysName
      n_size += sizeof (size_t);
      n_size += d_SysName.length()+1;

   // guid OwnerGUID
      n_size += sizeof (guid);

   // int AccessLevelThreshold
      n_size += sizeof (int);

   // int CreationTime
      n_size += sizeof (int);

   // int InfoTime
      n_size += sizeof (int);

   // identifier InfoDivID []
      n_size += sizeof (size_t);
      n_size += d_InfoDivID.GetSize() * sizeof(identifier);

   // bool UsageStrictAccess
      n_size += sizeof (bool);

   // int Log_Action []
      n_size += sizeof (size_t);
      n_size += d_Log_Action.GetSize() * sizeof(int);

   // guid Log_UserGUID []
      n_size += sizeof (size_t);
      n_size += d_Log_UserGUID.GetSize() * sizeof(guid);

   // int Log_Time []
      n_size += sizeof (size_t);
      n_size += d_Log_Time.GetSize() * sizeof(int);

   // string Log_Comment []
      n_size += sizeof (size_t);
      for (int iLog_Comment=0; iLog_Comment<d_Log_Comment.GetSize(); iLog_Comment++)
      {
         n_size += sizeof (size_t);
         n_size += d_Log_Comment[iLog_Comment].length()+1;
      }

   // guid IconGUID
      n_size += sizeof (guid);

   // string OriginalText
      n_size += sizeof (size_t);
      n_size += d_OriginalText.length()+1;

   // guid ArtworkGUID []
      n_size += sizeof (size_t);
      n_size += d_ArtworkGUID.GetSize() * sizeof(guid);

   // identifier InfoSourceID
      n_size += sizeof (identifier);

   // identifier AuthorID
      n_size += sizeof (identifier);

   // string AuthorStr
      n_size += sizeof (size_t);
      n_size += d_AuthorStr.length()+1;

   // string URL
      n_size += sizeof (size_t);
      n_size += d_URL.length()+1;

   // string RelatedLinks []
      n_size += sizeof (size_t);
      for (int iRelatedLinks=0; iRelatedLinks<d_RelatedLinks.GetSize(); iRelatedLinks++)
      {
         n_size += sizeof (size_t);
         n_size += d_RelatedLinks[iRelatedLinks].length()+1;
      }

   // identifier CategoryID []
      n_size += sizeof (size_t);
      n_size += d_CategoryID.GetSize() * sizeof(identifier);

   // int ShowCount
      n_size += sizeof (int);

   // int ClickCount
      n_size += sizeof (int);

   // float CTR
      n_size += sizeof (float);

   // int Estimation_Tot
      n_size += sizeof (int);

   // int Estimation_Num
      n_size += sizeof (int);

   // float Estimation
      n_size += sizeof (float);

   // string Name
      n_size += sizeof (size_t);
      n_size += d_Name.length()+1;

   // string Description
      n_size += sizeof (size_t);
      n_size += d_Description.length()+1;

   // string Text
      n_size += sizeof (size_t);
      n_size += d_Text.length()+1;

   // string Additional
      n_size += sizeof (size_t);
      n_size += d_Additional.length()+1;

   // identifier SearchItemID []
      n_size += sizeof (size_t);
      n_size += d_SearchItemID.GetSize() * sizeof(identifier);

   // guid ProxyObject
      n_size += sizeof (guid);

   // string FIELD_Extension_Name []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
      }

   // string FIELD_Extension_Value []
      n_size += sizeof (size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         n_size += sizeof (size_t);
         n_size += d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
      }

   // guid MOD_Base_GUID
      n_size += sizeof (guid);

   // guid MOD_Extension_GUID
      n_size += sizeof (guid);

      return n_size;
   }

// Запись данных на диск
   bool OD_InfoObject::WriteToFile (identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoObject_WriteToFile);

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

   // identifier randID
      (*(identifier*)(file+nOffset)) = d_randID;
      nOffset += sizeof (identifier);

   // string SysName
      size_t n_SysName = d_SysName.length()+1;
      (*(size_t*)(file+nOffset)) = n_SysName;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_SysName.c_str(), n_SysName);
      ENCODE_STRING (n_SysName, (char*)(file+nOffset));
      nOffset += n_SysName;

   // guid OwnerGUID
      (*(guid*)(file+nOffset)) = d_OwnerGUID;
      nOffset += sizeof (guid);

   // int AccessLevelThreshold
      (*(int*)(file+nOffset)) = d_AccessLevelThreshold;
      nOffset += sizeof (int);

   // int CreationTime
      (*(int*)(file+nOffset)) = d_CreationTime;
      nOffset += sizeof (int);

   // int InfoTime
      (*(int*)(file+nOffset)) = d_InfoTime;
      nOffset += sizeof (int);

   // identifier InfoDivID []
      (*(size_t*)(file+nOffset)) = d_InfoDivID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,InfoDivID);

   // bool UsageStrictAccess
      (*(bool*)(file+nOffset)) = d_UsageStrictAccess;
      nOffset += sizeof (bool);

   // int Log_Action []
      (*(size_t*)(file+nOffset)) = d_Log_Action.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Log_Action);

   // guid Log_UserGUID []
      (*(size_t*)(file+nOffset)) = d_Log_UserGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,Log_UserGUID);

   // int Log_Time []
      (*(size_t*)(file+nOffset)) = d_Log_Time.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (int,Log_Time);

   // string Log_Comment []
      (*(size_t*)(file+nOffset)) = d_Log_Comment.GetSize();
      nOffset += sizeof(size_t);
      for (int iLog_Comment=0; iLog_Comment<d_Log_Comment.GetSize(); iLog_Comment++)
      {
         size_t n_Log_Comment = d_Log_Comment[iLog_Comment].length()+1;
         (*(size_t*)(file+nOffset)) = n_Log_Comment;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_Log_Comment[iLog_Comment].c_str(), n_Log_Comment);
         ENCODE_STRING (n_Log_Comment, (char*)(file+nOffset));
         nOffset += n_Log_Comment;
      }

   // guid IconGUID
      (*(guid*)(file+nOffset)) = d_IconGUID;
      nOffset += sizeof (guid);

   // string OriginalText
      size_t n_OriginalText = d_OriginalText.length()+1;
      (*(size_t*)(file+nOffset)) = n_OriginalText;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_OriginalText.c_str(), n_OriginalText);
      ENCODE_STRING (n_OriginalText, (char*)(file+nOffset));
      nOffset += n_OriginalText;

   // guid ArtworkGUID []
      (*(size_t*)(file+nOffset)) = d_ArtworkGUID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (guid,ArtworkGUID);

   // identifier InfoSourceID
      (*(identifier*)(file+nOffset)) = d_InfoSourceID;
      nOffset += sizeof (identifier);

   // identifier AuthorID
      (*(identifier*)(file+nOffset)) = d_AuthorID;
      nOffset += sizeof (identifier);

   // string AuthorStr
      size_t n_AuthorStr = d_AuthorStr.length()+1;
      (*(size_t*)(file+nOffset)) = n_AuthorStr;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_AuthorStr.c_str(), n_AuthorStr);
      ENCODE_STRING (n_AuthorStr, (char*)(file+nOffset));
      nOffset += n_AuthorStr;

   // string URL
      size_t n_URL = d_URL.length()+1;
      (*(size_t*)(file+nOffset)) = n_URL;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_URL.c_str(), n_URL);
      ENCODE_STRING (n_URL, (char*)(file+nOffset));
      nOffset += n_URL;

   // string RelatedLinks []
      (*(size_t*)(file+nOffset)) = d_RelatedLinks.GetSize();
      nOffset += sizeof(size_t);
      for (int iRelatedLinks=0; iRelatedLinks<d_RelatedLinks.GetSize(); iRelatedLinks++)
      {
         size_t n_RelatedLinks = d_RelatedLinks[iRelatedLinks].length()+1;
         (*(size_t*)(file+nOffset)) = n_RelatedLinks;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_RelatedLinks[iRelatedLinks].c_str(), n_RelatedLinks);
         ENCODE_STRING (n_RelatedLinks, (char*)(file+nOffset));
         nOffset += n_RelatedLinks;
      }

   // identifier CategoryID []
      (*(size_t*)(file+nOffset)) = d_CategoryID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,CategoryID);

   // int ShowCount
      (*(int*)(file+nOffset)) = d_ShowCount;
      nOffset += sizeof (int);

   // int ClickCount
      (*(int*)(file+nOffset)) = d_ClickCount;
      nOffset += sizeof (int);

   // float CTR
      (*(float*)(file+nOffset)) = d_CTR;
      nOffset += sizeof (float);

   // int Estimation_Tot
      (*(int*)(file+nOffset)) = d_Estimation_Tot;
      nOffset += sizeof (int);

   // int Estimation_Num
      (*(int*)(file+nOffset)) = d_Estimation_Num;
      nOffset += sizeof (int);

   // float Estimation
      (*(float*)(file+nOffset)) = d_Estimation;
      nOffset += sizeof (float);

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

   // string Text
      size_t n_Text = d_Text.length()+1;
      (*(size_t*)(file+nOffset)) = n_Text;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Text.c_str(), n_Text);
      ENCODE_STRING (n_Text, (char*)(file+nOffset));
      nOffset += n_Text;

   // string Additional
      size_t n_Additional = d_Additional.length()+1;
      (*(size_t*)(file+nOffset)) = n_Additional;
      nOffset += sizeof (size_t);
      memcpy ((file+nOffset), d_Additional.c_str(), n_Additional);
      ENCODE_STRING (n_Additional, (char*)(file+nOffset));
      nOffset += n_Additional;

   // identifier SearchItemID []
      (*(size_t*)(file+nOffset)) = d_SearchItemID.GetSize();
      nOffset += sizeof(size_t);
      OD_SAVE_SIMPLE_ARRAY (identifier,SearchItemID);

   // guid ProxyObject
      (*(guid*)(file+nOffset)) = d_ProxyObject;
      nOffset += sizeof (guid);

   // string FIELD_Extension_Name []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Name.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         size_t n_FIELD_Extension_Name = d_FIELD_Extension_Name[iFIELD_Extension_Name].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Name;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str(), n_FIELD_Extension_Name);
         ENCODE_STRING (n_FIELD_Extension_Name, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Name;
      }

   // string FIELD_Extension_Value []
      (*(size_t*)(file+nOffset)) = d_FIELD_Extension_Value.GetSize();
      nOffset += sizeof(size_t);
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         size_t n_FIELD_Extension_Value = d_FIELD_Extension_Value[iFIELD_Extension_Value].length()+1;
         (*(size_t*)(file+nOffset)) = n_FIELD_Extension_Value;
         nOffset += sizeof (size_t);
         memcpy ((file+nOffset), d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str(), n_FIELD_Extension_Value);
         ENCODE_STRING (n_FIELD_Extension_Value, (char*)(file+nOffset));
         nOffset += n_FIELD_Extension_Value;
      }

   // guid MOD_Base_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Base_GUID;
      nOffset += sizeof (guid);

   // guid MOD_Extension_GUID
      (*(guid*)(file+nOffset)) = d_MOD_Extension_GUID;
      nOffset += sizeof (guid);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_InfoObject::DebugPrint (string& dbg, identifier objID)
   {
   DEBUG_STACK_NAME (OD_InfoObject_DebugPrint);

      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s: ID=%d RN=%d]\n\n", className[OBJ_CLASS_ID_InfoObject], objID, d_randID);
      dbg += SSS;

   // string SysName
      SSS.Format ("SysName = '%s'\n", d_SysName.c_str());
      dbg += SSS;

   // guid OwnerGUID
      SSS.Format ("OwnerGUID = {%d,%d,%d}\n", d_OwnerGUID.cl, d_OwnerGUID.id, d_OwnerGUID.rn);
      dbg += SSS;

   // int AccessLevelThreshold
      SSS.Format ("AccessLevelThreshold = %d\n", d_AccessLevelThreshold);
      dbg += SSS;

   // int CreationTime
      SSS.Format ("CreationTime = %d\n", d_CreationTime);
      dbg += SSS;

   // int InfoTime
      SSS.Format ("InfoTime = %d\n", d_InfoTime);
      dbg += SSS;

   // identifier InfoDivID []
      SSS.Format ("InfoDivID[].size = %d:\n", d_InfoDivID.GetSize());
      dbg += SSS;
      for (int iInfoDivID=0; iInfoDivID<d_InfoDivID.GetSize(); iInfoDivID++)
      {
         SSS.Format ("   InfoDivID[%d] = %d\n", iInfoDivID, d_InfoDivID[iInfoDivID]);
         dbg += SSS;
      }

   // bool UsageStrictAccess
      SSS.Format ("UsageStrictAccess = %s\n", d_UsageStrictAccess?"true":"false");
      dbg += SSS;

   // int Log_Action []
      SSS.Format ("Log_Action[].size = %d:\n", d_Log_Action.GetSize());
      dbg += SSS;
      for (int iLog_Action=0; iLog_Action<d_Log_Action.GetSize(); iLog_Action++)
      {
         SSS.Format ("   Log_Action[%d] = %d\n", iLog_Action, d_Log_Action[iLog_Action]);
         dbg += SSS;
      }

   // guid Log_UserGUID []
      SSS.Format ("Log_UserGUID[].size = %d:\n", d_Log_UserGUID.GetSize());
      dbg += SSS;
      for (int iLog_UserGUID=0; iLog_UserGUID<d_Log_UserGUID.GetSize(); iLog_UserGUID++)
      {
         SSS.Format ("   Log_UserGUID[%d] = {%d,%d,%d}\n", iLog_UserGUID, d_Log_UserGUID[iLog_UserGUID].cl, iLog_UserGUID, d_Log_UserGUID[iLog_UserGUID].id, iLog_UserGUID, d_Log_UserGUID[iLog_UserGUID].rn);
         dbg += SSS;
      }

   // int Log_Time []
      SSS.Format ("Log_Time[].size = %d:\n", d_Log_Time.GetSize());
      dbg += SSS;
      for (int iLog_Time=0; iLog_Time<d_Log_Time.GetSize(); iLog_Time++)
      {
         SSS.Format ("   Log_Time[%d] = %d\n", iLog_Time, d_Log_Time[iLog_Time]);
         dbg += SSS;
      }

   // string Log_Comment []
      SSS.Format ("Log_Comment[].size = %d:\n", d_Log_Comment.GetSize());
      dbg += SSS;
      for (int iLog_Comment=0; iLog_Comment<d_Log_Comment.GetSize(); iLog_Comment++)
      {
         SSS.Format ("   Log_Comment[%d] = '%s'\n", iLog_Comment, d_Log_Comment[iLog_Comment].c_str());
         dbg += SSS;
      }

   // guid IconGUID
      SSS.Format ("IconGUID = {%d,%d,%d}\n", d_IconGUID.cl, d_IconGUID.id, d_IconGUID.rn);
      dbg += SSS;

   // string OriginalText
      SSS.Format ("OriginalText = '%s'\n", d_OriginalText.c_str());
      dbg += SSS;

   // guid ArtworkGUID []
      SSS.Format ("ArtworkGUID[].size = %d:\n", d_ArtworkGUID.GetSize());
      dbg += SSS;
      for (int iArtworkGUID=0; iArtworkGUID<d_ArtworkGUID.GetSize(); iArtworkGUID++)
      {
         SSS.Format ("   ArtworkGUID[%d] = {%d,%d,%d}\n", iArtworkGUID, d_ArtworkGUID[iArtworkGUID].cl, iArtworkGUID, d_ArtworkGUID[iArtworkGUID].id, iArtworkGUID, d_ArtworkGUID[iArtworkGUID].rn);
         dbg += SSS;
      }

   // identifier InfoSourceID
      SSS.Format ("InfoSourceID = %d\n", d_InfoSourceID);
      dbg += SSS;

   // identifier AuthorID
      SSS.Format ("AuthorID = %d\n", d_AuthorID);
      dbg += SSS;

   // string AuthorStr
      SSS.Format ("AuthorStr = '%s'\n", d_AuthorStr.c_str());
      dbg += SSS;

   // string URL
      SSS.Format ("URL = '%s'\n", d_URL.c_str());
      dbg += SSS;

   // string RelatedLinks []
      SSS.Format ("RelatedLinks[].size = %d:\n", d_RelatedLinks.GetSize());
      dbg += SSS;
      for (int iRelatedLinks=0; iRelatedLinks<d_RelatedLinks.GetSize(); iRelatedLinks++)
      {
         SSS.Format ("   RelatedLinks[%d] = '%s'\n", iRelatedLinks, d_RelatedLinks[iRelatedLinks].c_str());
         dbg += SSS;
      }

   // identifier CategoryID []
      SSS.Format ("CategoryID[].size = %d:\n", d_CategoryID.GetSize());
      dbg += SSS;
      for (int iCategoryID=0; iCategoryID<d_CategoryID.GetSize(); iCategoryID++)
      {
         SSS.Format ("   CategoryID[%d] = %d\n", iCategoryID, d_CategoryID[iCategoryID]);
         dbg += SSS;
      }

   // int ShowCount
      SSS.Format ("ShowCount = %d\n", d_ShowCount);
      dbg += SSS;

   // int ClickCount
      SSS.Format ("ClickCount = %d\n", d_ClickCount);
      dbg += SSS;

   // float CTR
      SSS.Format ("CTR = %f\n", d_CTR);
      dbg += SSS;

   // int Estimation_Tot
      SSS.Format ("Estimation_Tot = %d\n", d_Estimation_Tot);
      dbg += SSS;

   // int Estimation_Num
      SSS.Format ("Estimation_Num = %d\n", d_Estimation_Num);
      dbg += SSS;

   // float Estimation
      SSS.Format ("Estimation = %f\n", d_Estimation);
      dbg += SSS;

   // string Name
      SSS.Format ("Name = '%s'\n", d_Name.c_str());
      dbg += SSS;

   // string Description
      SSS.Format ("Description = '%s'\n", d_Description.c_str());
      dbg += SSS;

   // string Text
      SSS.Format ("Text = '%s'\n", d_Text.c_str());
      dbg += SSS;

   // string Additional
      SSS.Format ("Additional = '%s'\n", d_Additional.c_str());
      dbg += SSS;

   // identifier SearchItemID []
      SSS.Format ("SearchItemID[].size = %d:\n", d_SearchItemID.GetSize());
      dbg += SSS;
      for (int iSearchItemID=0; iSearchItemID<d_SearchItemID.GetSize(); iSearchItemID++)
      {
         SSS.Format ("   SearchItemID[%d] = %d\n", iSearchItemID, d_SearchItemID[iSearchItemID]);
         dbg += SSS;
      }

   // guid ProxyObject
      SSS.Format ("ProxyObject = {%d,%d,%d}\n", d_ProxyObject.cl, d_ProxyObject.id, d_ProxyObject.rn);
      dbg += SSS;

   // string FIELD_Extension_Name []
      SSS.Format ("FIELD_Extension_Name[].size = %d:\n", d_FIELD_Extension_Name.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Name=0; iFIELD_Extension_Name<d_FIELD_Extension_Name.GetSize(); iFIELD_Extension_Name++)
      {
         SSS.Format ("   FIELD_Extension_Name[%d] = '%s'\n", iFIELD_Extension_Name, d_FIELD_Extension_Name[iFIELD_Extension_Name].c_str());
         dbg += SSS;
      }

   // string FIELD_Extension_Value []
      SSS.Format ("FIELD_Extension_Value[].size = %d:\n", d_FIELD_Extension_Value.GetSize());
      dbg += SSS;
      for (int iFIELD_Extension_Value=0; iFIELD_Extension_Value<d_FIELD_Extension_Value.GetSize(); iFIELD_Extension_Value++)
      {
         SSS.Format ("   FIELD_Extension_Value[%d] = '%s'\n", iFIELD_Extension_Value, d_FIELD_Extension_Value[iFIELD_Extension_Value].c_str());
         dbg += SSS;
      }

   // guid MOD_Base_GUID
      SSS.Format ("MOD_Base_GUID = {%d,%d,%d}\n", d_MOD_Base_GUID.cl, d_MOD_Base_GUID.id, d_MOD_Base_GUID.rn);
      dbg += SSS;

   // guid MOD_Extension_GUID
      SSS.Format ("MOD_Extension_GUID = {%d,%d,%d}\n", d_MOD_Extension_GUID.cl, d_MOD_Extension_GUID.id, d_MOD_Extension_GUID.rn);
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
