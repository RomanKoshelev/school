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
[] Description:     ������ ������� ��� ����� ������������                     []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/
#ifndef Lay_Stubs_H
#define Lay_Stubs_H




//------------------------------------------------------------------------------
//
// �����������
//
inline void * new_OD (identifier classID, bool bInit)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return new OD_Test_sort (bInit);
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ����������
//
inline void delete_pData (identifier classID, void * pData)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: delete ((OD_Test_sort*)pData); return;
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ������
//
inline bool pData_DebugPrint (identifier classID, void * pData, string& dbg, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->DebugPrint(dbg, objID);
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return false;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ����������
//
inline bool pData_WriteToFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->WriteToFile (objID);
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return false;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ��������
//
inline bool pData_LoadFromFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->LoadFromFile (objID);
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return false;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ��������� ��������� � �������
//
inline void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ��������� ��������� � �������
//
inline OBD_pointer pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->m_CoIndexPtr[indexID];
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ������������� ������
//
inline identifier pData_classID (identifier classID, void * pData)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: return ((OD_Test_sort*)pData)->classID;
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
   return NA;
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//
// ���������� ������
//
inline void pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Test_sort: ((OD_Test_sort*)pData)->AddKeyVarForField (ka, fieldID ); return;
   }
   SERVER_DEBUG_ERROR_1 ("����������� ����� %d", classID);
}
//------------------------------------------------------------------------------



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
