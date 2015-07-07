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


#include "./../bcc/main.h"
#include "./../bcc/OBD.h"
#include "./../bcc/Object.h"
#include "Lay_ObjData.h"








#ifdef  USES_OC_ALL
#define USES_OC_Test_sort
#endif
#ifdef USES_OC_Test_sort
//------------------------------------------------------------------------------[]
// 
// ���������� �������� ���� ������ ������ "Test_sort"
// 
class OC_Test_sort: public OC_Object <OC_Test_sort, OD_Test_sort>
{
// ����������� �� ��������� -- ���������� �� ���������� �� ������!
   public: OC_Test_sort  ();// ����������� �� �������������� -- ����������� ������ �� ����
   public: OC_Test_sort  (identifier objID);
// ����������� ����������� �� ������� �����������
   public: OC_Test_sort  (const OC_Test_sort& from);
// ���������� ����������� �������
   public: ~OC_Test_sort ();

// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_sort& operator= (const OC_Test_sort& from);
// 1. ����������� (�����������, ������������) ������������ ������ ������
// 2. �������� ������� �� ��������������
   public: OC_Test_sort& operator= (identifier objID);

// ������������� ���������� ����� CSmartField<...>
   protected: void InitSmartFields();


// ����������� ������ �� ������� �����������
   public: void CopyDataFrom (OC_Test_sort& from);


// ����������� ������ � ������ ����������
   public: void CopyDataTo (OC_Test_sort& to);

// ����������� ������ �� ������� �����������: to << from;
   public: OC_Test_sort& operator << (OC_Test_sort& from);

// ����������� ������ � ������ ����������: from >> to;
   public: OC_Test_sort& operator >> (OC_Test_sort& from);

// ����:   int Test_sort::n1
   public: CSmartField      <OD_Test_sort, int        >    m_n1;
// ����:   int Test_sort::n2
   public: CSmartField      <OD_Test_sort, int        >    m_n2;
// ����:   int Test_sort::n3
   public: CSmartField      <OD_Test_sort, int        >    m_n3;

// ���������� ������� ������ �� ��� ��������������
// ���������� ������ ������
   identifier SetIndex (identifier newIndex);
// �������� ������������� �������� �������
   identifier GetIndex ();

// ���������� ������� ������ �� ������ ����� [n1, -n2, n3]
   public: void SetIndex_n1__n2_n3 ();
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
