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
