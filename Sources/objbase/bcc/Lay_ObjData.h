/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjData.h                                             []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Data contents for database objects                        []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/


#ifndef Lay_ObjData_h
#define Lay_ObjData_h


//----------------------------------------------------------------------------[]
#define OD_SAVE_SIMPLE_ARRAY(type,field)													\
		memcpy (file.GetPtr()+nOffset, 														\
			d_##field.GetPtr(), 																	\
			d_##field.GetSize()*sizeof(type));												\
		nOffset  += d_##field.GetSize()*sizeof(type);
//----------------------------------------------------------------------------[]
#define OD_LOAD_SIMPLE_ARRAY(type,field)													\
		memcpy (d_##field.GetPtr(), 															\
			file.GetPtr()+nOffset, 																\
			arr_size_##field*sizeof(type));													\
		nOffset  += arr_size_##field*sizeof(type);
//----------------------------------------------------------------------------[]





//------------------------------------------------------------------------------[]
//
// �������������� �������
//
enum OBJ_CLASS_ID
{
   OBJ_CLASS_ID_Test_sort = 0,
   OBJ_CLASS_ID_END
};






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Test_sort"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Test_sort
#endif
#ifdef USES_OC_Test_sort
class OD_Test_sort: public OD_BASE
{
public:
// �����������
   OD_Test_sort (bool bFieldsInit);
// ����������
  ~OD_Test_sort ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ��������� �� CObjIndex_AVTree_Item ��� ���� ��������
   OBD_pointer    m_CoIndexPtr[1];

// ����-������
   int        d_n1;
   int        d_n2;
   int        d_n3;

// �������� ������� � �����
   bool LoadFromFile (identifier objID);


// ������� ������� ������� ��� ��������� �� ����
   size_t CalculateSize ();

// ������ ������ �� ����
   bool WriteToFile (identifier objID);

// ���������� ������
   bool DebugPrint (string& dbg, identifier objID);
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
