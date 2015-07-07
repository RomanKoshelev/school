/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_Stubs.h                                               []
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

#ifdef  USES_OC_ALL
#define USES_OC_Test_CRC
#define USES_OC_Test_sort
#endif





//------------------------------------------------------------------------------[]
//
// Конструктор
//
inline void * new_OD (identifier classID, bool bInit)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return new OD_Test_CRC (bInit);
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return new OD_Test_sort (bInit);
#endif
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
inline void delete_pData (identifier classID, void * pData)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: delete ((OD_Test_CRC*)pData); return;
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: delete ((OD_Test_sort*)pData); return;
#endif
      case -1: (void)classID; (void)pData;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Печать
//
inline bool pData_DebugPrint (identifier classID, void * pData, string& dbg, identifier objID)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->DebugPrint(dbg, objID);
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->DebugPrint(dbg, objID);
#endif
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
inline bool pData_WriteToFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->WriteToFile (objID);
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->WriteToFile (objID);
#endif
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
inline bool pData_LoadFromFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->LoadFromFile (objID);
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->LoadFromFile (objID);
#endif
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
inline void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: ((OD_Test_CRC*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
#endif
      case -1: (void)classID; (void)pData; (void)indexID; (void)coIndexPtr;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Получение указателя в индексе
//
inline OBD_pointer pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->m_CoIndexPtr[indexID];
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID];
#endif
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
inline identifier pData_classID (identifier classID, void * pData)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: return ((OD_Test_CRC*)pData)->classID;
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->classID;
#endif
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
inline void pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID)
{
   switch (classID)
   {
#ifdef USES_OC_Test_CRC
      case OBJ_CLASS_ID_Test_CRC: ((OD_Test_CRC*)pData)->AddKeyVarForField (ka, fieldID ); return;
#endif
#ifdef USES_OC_Test_sort
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->AddKeyVarForField (ka, fieldID ); return;
#endif
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
