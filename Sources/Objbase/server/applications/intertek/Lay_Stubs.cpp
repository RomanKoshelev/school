/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_Stubs.cpp															  []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Мощные затычки для тупых компиляторов                     []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/
#ifndef Lay_Stubs_H
#define Lay_Stubs_H

#define USES_OC_ALL
#include "./../../kernel/main.h"
#include "./../../kernel/OBD.h"
#include "Lay_ObjData.h"




//------------------------------------------------------------------------------[]
//
// Конструктор
//
void * new_OD (identifier classID, bool bInit)
{
   DEBUG_STACK_NAME (new_OD);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return new OD_Registry (bInit);
      case OBJ_CLASS_ID_Relation: return new OD_Relation (bInit);
      case OBJ_CLASS_ID_Linkage: return new OD_Linkage (bInit);
      case OBJ_CLASS_ID_LinkProxy: return new OD_LinkProxy (bInit);
      case OBJ_CLASS_ID_Connectable: return new OD_Connectable (bInit);
      case OBJ_CLASS_ID_MetaObject: return new OD_MetaObject (bInit);
      case OBJ_CLASS_ID_Concept: return new OD_Concept (bInit);
      case OBJ_CLASS_ID_User: return new OD_User (bInit);
      case OBJ_CLASS_ID_UserGroup: return new OD_UserGroup (bInit);
      case OBJ_CLASS_ID_Text: return new OD_Text (bInit);
      case OBJ_CLASS_ID_MorphologicRule: return new OD_MorphologicRule (bInit);
      case OBJ_CLASS_ID_SearchItem: return new OD_SearchItem (bInit);
      case OBJ_CLASS_ID_StopWord: return new OD_StopWord (bInit);
      case OBJ_CLASS_ID_WordNibbleABC: return new OD_WordNibbleABC (bInit);
      case OBJ_CLASS_ID_WebFolder: return new OD_WebFolder (bInit);
      case OBJ_CLASS_ID_WebFile: return new OD_WebFile (bInit);
      case OBJ_CLASS_ID_UserProfile: return new OD_UserProfile (bInit);
      case OBJ_CLASS_ID_InfoDiv: return new OD_InfoDiv (bInit);
      case OBJ_CLASS_ID_InfoSource: return new OD_InfoSource (bInit);
      case OBJ_CLASS_ID_InfoObject: return new OD_InfoObject (bInit);
      case -1: (void)classID; (void)bInit;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Деструктор
//
void delete_pData (identifier classID, void * pData)
{
   DEBUG_STACK_NAME (delete_pData);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: delete ((OD_Registry*)pData); return;
      case OBJ_CLASS_ID_Relation: delete ((OD_Relation*)pData); return;
      case OBJ_CLASS_ID_Linkage: delete ((OD_Linkage*)pData); return;
      case OBJ_CLASS_ID_LinkProxy: delete ((OD_LinkProxy*)pData); return;
      case OBJ_CLASS_ID_Connectable: delete ((OD_Connectable*)pData); return;
      case OBJ_CLASS_ID_MetaObject: delete ((OD_MetaObject*)pData); return;
      case OBJ_CLASS_ID_Concept: delete ((OD_Concept*)pData); return;
      case OBJ_CLASS_ID_User: delete ((OD_User*)pData); return;
      case OBJ_CLASS_ID_UserGroup: delete ((OD_UserGroup*)pData); return;
      case OBJ_CLASS_ID_Text: delete ((OD_Text*)pData); return;
      case OBJ_CLASS_ID_MorphologicRule: delete ((OD_MorphologicRule*)pData); return;
      case OBJ_CLASS_ID_SearchItem: delete ((OD_SearchItem*)pData); return;
      case OBJ_CLASS_ID_StopWord: delete ((OD_StopWord*)pData); return;
      case OBJ_CLASS_ID_WordNibbleABC: delete ((OD_WordNibbleABC*)pData); return;
      case OBJ_CLASS_ID_WebFolder: delete ((OD_WebFolder*)pData); return;
      case OBJ_CLASS_ID_WebFile: delete ((OD_WebFile*)pData); return;
      case OBJ_CLASS_ID_UserProfile: delete ((OD_UserProfile*)pData); return;
      case OBJ_CLASS_ID_InfoDiv: delete ((OD_InfoDiv*)pData); return;
      case OBJ_CLASS_ID_InfoSource: delete ((OD_InfoSource*)pData); return;
      case OBJ_CLASS_ID_InfoObject: delete ((OD_InfoObject*)pData); return;
      case -1: (void)classID; (void)pData;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Печать
//
bool pData_DebugPrint (identifier classID, void * pData, string& dbg, identifier objID)
{
   DEBUG_STACK_NAME (pData_DebugPrint);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Relation: return ((OD_Relation*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Linkage: return ((OD_Linkage*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_LinkProxy: return ((OD_LinkProxy*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Connectable: return ((OD_Connectable*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_MetaObject: return ((OD_MetaObject*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_UserGroup: return ((OD_UserGroup*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Text: return ((OD_Text*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_MorphologicRule: return ((OD_MorphologicRule*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_SearchItem: return ((OD_SearchItem*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_StopWord: return ((OD_StopWord*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_WordNibbleABC: return ((OD_WordNibbleABC*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_WebFolder: return ((OD_WebFolder*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_WebFile: return ((OD_WebFile*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_UserProfile: return ((OD_UserProfile*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_InfoDiv: return ((OD_InfoDiv*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_InfoSource: return ((OD_InfoSource*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_InfoObject: return ((OD_InfoObject*)pData)->DebugPrint(dbg, objID);
      case -1: (void)classID; (void)pData; (void)objID; (void)dbg;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return false;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Сохранение
//
bool pData_WriteToFile (identifier classID, void * pData, identifier objID)
{
   DEBUG_STACK_NAME (pData_WriteToFile);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Relation: return ((OD_Relation*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Linkage: return ((OD_Linkage*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_LinkProxy: return ((OD_LinkProxy*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Connectable: return ((OD_Connectable*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_MetaObject: return ((OD_MetaObject*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_UserGroup: return ((OD_UserGroup*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Text: return ((OD_Text*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_MorphologicRule: return ((OD_MorphologicRule*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_SearchItem: return ((OD_SearchItem*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_StopWord: return ((OD_StopWord*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_WordNibbleABC: return ((OD_WordNibbleABC*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_WebFolder: return ((OD_WebFolder*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_WebFile: return ((OD_WebFile*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_UserProfile: return ((OD_UserProfile*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_InfoDiv: return ((OD_InfoDiv*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_InfoSource: return ((OD_InfoSource*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_InfoObject: return ((OD_InfoObject*)pData)->WriteToFile (objID);
      case -1: (void)classID; (void)pData; (void)objID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return false;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Загрузка
//
size_t pData_LoadFromFile (identifier classID, void * pData, identifier objID)
{
   DEBUG_STACK_NAME (pData_LoadFromFile);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Relation: return ((OD_Relation*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Linkage: return ((OD_Linkage*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_LinkProxy: return ((OD_LinkProxy*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Connectable: return ((OD_Connectable*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_MetaObject: return ((OD_MetaObject*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_UserGroup: return ((OD_UserGroup*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Text: return ((OD_Text*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_MorphologicRule: return ((OD_MorphologicRule*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_SearchItem: return ((OD_SearchItem*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_StopWord: return ((OD_StopWord*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_WordNibbleABC: return ((OD_WordNibbleABC*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_WebFolder: return ((OD_WebFolder*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_WebFile: return ((OD_WebFile*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_UserProfile: return ((OD_UserProfile*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_InfoDiv: return ((OD_InfoDiv*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_InfoSource: return ((OD_InfoSource*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_InfoObject: return ((OD_InfoObject*)pData)->LoadFromFile (objID);
      case -1: (void)classID; (void)pData; (void)objID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return 0;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Установка указателя в индексе
//
void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)
{
   DEBUG_STACK_NAME (pData_m_CoIndexPtr);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: ((OD_Registry*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Relation: ((OD_Relation*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Linkage: ((OD_Linkage*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_LinkProxy: ((OD_LinkProxy*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Connectable: ((OD_Connectable*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_MetaObject: ((OD_MetaObject*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Concept: ((OD_Concept*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_User: ((OD_User*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_UserGroup: ((OD_UserGroup*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Text: ((OD_Text*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_MorphologicRule: ((OD_MorphologicRule*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_SearchItem: ((OD_SearchItem*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_StopWord: ((OD_StopWord*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_WordNibbleABC: ((OD_WordNibbleABC*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_WebFolder: ((OD_WebFolder*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_WebFile: ((OD_WebFile*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_UserProfile: ((OD_UserProfile*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_InfoDiv: ((OD_InfoDiv*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_InfoSource: ((OD_InfoSource*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_InfoObject: ((OD_InfoObject*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case -1: (void)classID; (void)pData; (void)indexID; (void)coIndexPtr;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Получение указателя в индексе
//
OBD_pointer pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID)
{
   DEBUG_STACK_NAME (pData_m_CoIndexPtr);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Relation: return ((OD_Relation*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Linkage: return ((OD_Linkage*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_LinkProxy: return ((OD_LinkProxy*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Connectable: return ((OD_Connectable*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_MetaObject: return ((OD_MetaObject*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_UserGroup: return ((OD_UserGroup*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Text: return ((OD_Text*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_MorphologicRule: return ((OD_MorphologicRule*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_SearchItem: return ((OD_SearchItem*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_StopWord: return ((OD_StopWord*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_WordNibbleABC: return ((OD_WordNibbleABC*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_WebFolder: return ((OD_WebFolder*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_WebFile: return ((OD_WebFile*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_UserProfile: return ((OD_UserProfile*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_InfoDiv: return ((OD_InfoDiv*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_InfoSource: return ((OD_InfoSource*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_InfoObject: return ((OD_InfoObject*)pData)->m_CoIndexPtr[indexID];
      case -1: (void)classID; (void)pData; (void)indexID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Идентификатор класса
//
identifier pData_classID (identifier classID, void * pData)
{
   DEBUG_STACK_NAME (pData_classID);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->classID;
      case OBJ_CLASS_ID_Relation: return ((OD_Relation*)pData)->classID;
      case OBJ_CLASS_ID_Linkage: return ((OD_Linkage*)pData)->classID;
      case OBJ_CLASS_ID_LinkProxy: return ((OD_LinkProxy*)pData)->classID;
      case OBJ_CLASS_ID_Connectable: return ((OD_Connectable*)pData)->classID;
      case OBJ_CLASS_ID_MetaObject: return ((OD_MetaObject*)pData)->classID;
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->classID;
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->classID;
      case OBJ_CLASS_ID_UserGroup: return ((OD_UserGroup*)pData)->classID;
      case OBJ_CLASS_ID_Text: return ((OD_Text*)pData)->classID;
      case OBJ_CLASS_ID_MorphologicRule: return ((OD_MorphologicRule*)pData)->classID;
      case OBJ_CLASS_ID_SearchItem: return ((OD_SearchItem*)pData)->classID;
      case OBJ_CLASS_ID_StopWord: return ((OD_StopWord*)pData)->classID;
      case OBJ_CLASS_ID_WordNibbleABC: return ((OD_WordNibbleABC*)pData)->classID;
      case OBJ_CLASS_ID_WebFolder: return ((OD_WebFolder*)pData)->classID;
      case OBJ_CLASS_ID_WebFile: return ((OD_WebFile*)pData)->classID;
      case OBJ_CLASS_ID_UserProfile: return ((OD_UserProfile*)pData)->classID;
      case OBJ_CLASS_ID_InfoDiv: return ((OD_InfoDiv*)pData)->classID;
      case OBJ_CLASS_ID_InfoSource: return ((OD_InfoSource*)pData)->classID;
      case OBJ_CLASS_ID_InfoObject: return ((OD_InfoObject*)pData)->classID;
      case -1: (void)classID; (void)pData;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NA;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Добавление ключей
//
void pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID)
{
   DEBUG_STACK_NAME (pData_AddKeyVarForField);

   switch (classID)
   {
      case OBJ_CLASS_ID_Registry: ((OD_Registry*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Relation: ((OD_Relation*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Linkage: ((OD_Linkage*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_LinkProxy: ((OD_LinkProxy*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Connectable: ((OD_Connectable*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_MetaObject: ((OD_MetaObject*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Concept: ((OD_Concept*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_User: ((OD_User*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_UserGroup: ((OD_UserGroup*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Text: ((OD_Text*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_MorphologicRule: ((OD_MorphologicRule*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_SearchItem: ((OD_SearchItem*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_StopWord: ((OD_StopWord*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_WordNibbleABC: ((OD_WordNibbleABC*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_WebFolder: ((OD_WebFolder*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_WebFile: ((OD_WebFile*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_UserProfile: ((OD_UserProfile*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_InfoDiv: ((OD_InfoDiv*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_InfoSource: ((OD_InfoSource*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_InfoObject: ((OD_InfoObject*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case -1: (void)classID; (void)pData; (void)ka; (void)fieldID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
