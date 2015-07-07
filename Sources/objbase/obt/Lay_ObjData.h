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
   OBJ_CLASS_ID_Viewer = 0,
   OBJ_CLASS_ID_Test_Load = 1,
   OBJ_CLASS_ID_jerom_table = 2,
   OBJ_CLASS_ID_tsmc_table = 3,
   OBJ_CLASS_ID_Test_MM = 4,
   OBJ_CLASS_ID_Test_CRC = 5,
   OBJ_CLASS_ID_Test_4G = 6,
   OBJ_CLASS_ID_Test_sort = 7,
   OBJ_CLASS_ID_END
};






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Viewer"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Viewer
#endif
#ifdef USES_OC_Viewer
class OD_Viewer: public OD_BASE
{
public:
// �����������
   OD_Viewer (bool bFieldsInit);
// ����������
  ~OD_Viewer ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string     d_Name;
   string     d_Email;
   string     d_UserAgent;
   bool       d_Anonymous;
   int        d_TotalShows;
   int        d_TotalClicks;
   string     d_IPAddress;
   string     d_Referrer;
   identifier d_IPAddressHash;
   int_arr        d_CRA_Site;
   int_arr        d_CRN_Site;
   int        d_CRN_Site_Update;
   int_arr        d_CRA_Click;
   int_arr        d_CRN_Click;
   identifier d_Group;
   int        d_TZOffset;
   int        d_CreationTime;
   int        d_LastVisitTime;
   identifier_arr d_Site;
   int_arr        d_Site_LastHit;
   int_arr        d_Site_Hits;
   int_arr        d_Site_LastHost;
   int_arr        d_Site_Hosts;
   int        d_TotalHosts;
   byte_arr       d_Site_Votings;
   byte_arr       d_Site_VoteDayNo;
   int_arr        d_CRA_Inquiry;
   int_arr        d_CRN_Inquiry;
   identifier d_Site_SessionLastSiteID;
   identifier_arr d_Banner;
   int_arr        d_Banner_LastViewed;
   int_arr        d_Banner_ShowClick;
   int        d_BannerClickTime;
   identifier d_BannerClickID;
   identifier d_BannerClickSiteID;
   int        d_BannerClickHitCount;
   int        d_BannerClickSessionTime;
   identifier d_TagID;
   int        d_TagInt;
   bool       d_TagBool;
   identifier_arr d_ReservedID;
   int_arr        d_ReservedInt;
   string_arr     d_ReservedString;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Test_Load"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Test_Load
#endif
#ifdef USES_OC_Test_Load
class OD_Test_Load: public OD_BASE
{
public:
// �����������
   OD_Test_Load (bool bFieldsInit);
// ����������
  ~OD_Test_Load ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int        d_Field;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "jerom_table"
// 
#ifdef  USES_OC_ALL
#define USES_OC_jerom_table
#endif
#ifdef USES_OC_jerom_table
class OD_jerom_table: public OD_BASE
{
public:
// �����������
   OD_jerom_table (bool bFieldsInit);
// ����������
  ~OD_jerom_table ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int        d_OperatorID;
   int        d_MessageDate;
   string     d_Message;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "tsmc_table"
// 
#ifdef  USES_OC_ALL
#define USES_OC_tsmc_table
#endif
#ifdef USES_OC_tsmc_table
class OD_tsmc_table: public OD_BASE
{
public:
// �����������
   OD_tsmc_table (bool bFieldsInit);
// ����������
  ~OD_tsmc_table ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int        d_Int_Field;
   float      d_Float_Field;
   string     d_Text_Field;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Test_MM"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Test_MM
#endif
#ifdef USES_OC_Test_MM
class OD_Test_MM: public OD_BASE
{
public:
// �����������
   OD_Test_MM (bool bFieldsInit);
// ����������
  ~OD_Test_MM ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int        d_n;
   string     d_s;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Test_CRC"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Test_CRC
#endif
#ifdef USES_OC_Test_CRC
class OD_Test_CRC: public OD_BASE
{
public:
// �����������
   OD_Test_CRC (bool bFieldsInit);
// ����������
  ~OD_Test_CRC ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   identifier d_CRC;
   string     d_STR;

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






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Test_4G"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Test_4G
#endif
#ifdef USES_OC_Test_4G
class OD_Test_4G: public OD_BASE
{
public:
// �����������
   OD_Test_4G (bool bFieldsInit);
// ����������
  ~OD_Test_4G ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int        d_i;
   string     d_s;

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

// ����-������
   int        d_n1;
   int        d_n2;
   string     d_s1;
   string     d_s2;
   float      d_f1;
   float      d_f2;
   bool       d_b1;
   bool       d_b2;

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
