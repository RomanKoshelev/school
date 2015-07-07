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
// Test_sort

// ����������� �� ���������
OC_Test_sort::OC_Test_sort ()
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL;
}


// ����������� �� �������������� -- ����������� ������ �� ����
OC_Test_sort::OC_Test_sort  (identifier objID)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);
}

// ����������� ����������� �� ������� �����������
OC_Test_sort::OC_Test_sort  (const OC_Test_sort& from)
{
   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject<OD_Test_sort>(classID, from.coPtr);
}

// ���������� ����������� �������
OC_Test_sort::~OC_Test_sort ()
{
   Release();
}

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
OC_Test_sort& OC_Test_sort::operator= (const OC_Test_sort& from)
{
   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject<OD_Test_sort>(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;
}

OC_Test_sort& OC_Test_sort::operator= (identifier objID)
{
   Open (objID); return *this;
}



// ������������� ���������� ����� CSmartField<...>
void OC_Test_sort::InitSmartFields (void)
{
   classID = OBJ_CLASS_ID_Test_sort;
   m_n1._init (classID, 1, &coPtr, &OD_Test_sort::d_n1 );
   m_n2._init (classID, 2, &coPtr, &OD_Test_sort::d_n2 );
   m_n3._init (classID, 3, &coPtr, &OD_Test_sort::d_n3 );
   SetIndex (0);
}


// ����������� ������ �� ������� �����������
void OC_Test_sort::CopyDataFrom (OC_Test_sort& from)
{
   m_n1 = from.m_n1;
   m_n2 = from.m_n2;
   m_n3 = from.m_n3;
}


// ����������� ������ � ������ ����������
void OC_Test_sort::CopyDataTo (OC_Test_sort& to)
{
   to.m_n1 = m_n1;
   to.m_n2 = m_n2;
   to.m_n3 = m_n3;
}

// ����������� ������ �� ������� �����������: to << from;
OC_Test_sort&  OC_Test_sort::operator << (OC_Test_sort& from)
{
   CopyDataFrom (from);
   return *this;
}

// ����������� ������ � ������ ����������: from >> to;
OC_Test_sort&  OC_Test_sort::operator >> (OC_Test_sort& from)
{
   CopyDataTo (from);
   return *this;
}

// ���������� ������� ������ �� ��� ��������������
identifier OC_Test_sort::SetIndex (identifier newIndex)
{
   identifier oldIndex = curIndexInfo.m_id;
   switch (newIndex)
   {
      case 0: SetIndex_n1__n2_n3 ();
              return oldIndex;
   }
   SERVER_DEBUG_ERROR_2 ("SetIndex: ������� ��������� ������������� ������� %d � ������� ������ %s ", newIndex, className[classID]);
   return oldIndex;
}

// �������� ������������� �������� �������
identifier OC_Test_sort::GetIndex ()
{
   return curIndexInfo.m_id;
}



// ���������� ������� ������ �� ������ �����
void OC_Test_sort::SetIndex_n1__n2_n3 ()
{
   curIndexInfo.m_id         = 0; 
   curIndexInfo.m_keyNum     = 3; 
   curIndexInfo.m_keyType[0] = (byte)FT_int; 
   curIndexInfo.m_keyType[1] = (byte)FT_int; 
   curIndexInfo.m_keyType[2] = (byte)FT_int; 
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
