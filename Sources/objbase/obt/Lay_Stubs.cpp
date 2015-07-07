/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_Stubs.cpp                                             []
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
#include "./../bcc/main.h"
#include "./../bcc/OBD.h"
#include "Lay_ObjData.h"




//------------------------------------------------------------------------------[]
//
// Конструктор
//
void * new_OD (identifier classID, bool bInit)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return new OD_Viewer (bInit);
      case OBJ_CLASS_ID_Test_Load: return new OD_Test_Load (bInit);
      case OBJ_CLASS_ID_jerom_table: return new OD_jerom_table (bInit);
      case OBJ_CLASS_ID_tsmc_table: return new OD_tsmc_table (bInit);
      case OBJ_CLASS_ID_Test_MM: return new OD_Test_MM (bInit);
      case OBJ_CLASS_ID_Test_CRC: return new OD_Test_CRC (bInit);
      case OBJ_CLASS_ID_Test_4G: return new OD_Test_4G (bInit);
      case OBJ_CLASS_ID_Test_sort: return new OD_Test_sort (bInit);
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: delete ((OD_Viewer*)pData); return;
      case OBJ_CLASS_ID_Test_Load: delete ((OD_Test_Load*)pData); return;
      case OBJ_CLASS_ID_jerom_table: delete ((OD_jerom_table*)pData); return;
      case OBJ_CLASS_ID_tsmc_table: delete ((OD_tsmc_table*)pData); return;
      case OBJ_CLASS_ID_Test_MM: delete ((OD_Test_MM*)pData); return;
      case OBJ_CLASS_ID_Test_CRC: delete ((OD_Test_CRC*)pData); return;
      case OBJ_CLASS_ID_Test_4G: delete ((OD_Test_4G*)pData); return;
      case OBJ_CLASS_ID_Test_sort: delete ((OD_Test_sort*)pData); return;
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Test_Load: return ((OD_Test_Load*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_jerom_table: return ((OD_jerom_table*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_tsmc_table: return ((OD_tsmc_table*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Test_MM: return ((OD_Test_MM*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Test_4G: return ((OD_Test_4G*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->DebugPrint(dbg, objID);
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Test_Load: return ((OD_Test_Load*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_jerom_table: return ((OD_jerom_table*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_tsmc_table: return ((OD_tsmc_table*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Test_MM: return ((OD_Test_MM*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Test_4G: return ((OD_Test_4G*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->WriteToFile (objID);
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
bool pData_LoadFromFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Test_Load: return ((OD_Test_Load*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_jerom_table: return ((OD_jerom_table*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_tsmc_table: return ((OD_tsmc_table*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Test_MM: return ((OD_Test_MM*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Test_4G: return ((OD_Test_4G*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->LoadFromFile (objID);
      case -1: (void)classID; (void)pData; (void)objID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return false;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Установка указателя в индексе
//
void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: ((OD_Viewer*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Test_Load: ((OD_Test_Load*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_jerom_table: ((OD_jerom_table*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_tsmc_table: ((OD_tsmc_table*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Test_MM: ((OD_Test_MM*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Test_CRC: ((OD_Test_CRC*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Test_4G: ((OD_Test_4G*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Test_Load: return ((OD_Test_Load*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_jerom_table: return ((OD_jerom_table*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_tsmc_table: return ((OD_tsmc_table*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Test_MM: return ((OD_Test_MM*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Test_4G: return ((OD_Test_4G*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID];
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->classID;
      case OBJ_CLASS_ID_Test_Load: return ((OD_Test_Load*)pData)->classID;
      case OBJ_CLASS_ID_jerom_table: return ((OD_jerom_table*)pData)->classID;
      case OBJ_CLASS_ID_tsmc_table: return ((OD_tsmc_table*)pData)->classID;
      case OBJ_CLASS_ID_Test_MM: return ((OD_Test_MM*)pData)->classID;
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->classID;
      case OBJ_CLASS_ID_Test_4G: return ((OD_Test_4G*)pData)->classID;
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->classID;
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
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: ((OD_Viewer*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Test_Load: ((OD_Test_Load*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_jerom_table: ((OD_jerom_table*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_tsmc_table: ((OD_tsmc_table*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Test_MM: ((OD_Test_MM*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Test_CRC: ((OD_Test_CRC*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Test_4G: ((OD_Test_4G*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->AddKeyVarForField (ka, fieldID ); return;
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
