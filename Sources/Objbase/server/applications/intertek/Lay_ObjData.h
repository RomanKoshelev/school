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
#define LAY_MEMCPY(to, from, offset, size, maxsize, field)						   \
	if (int(offset+size) > (int)maxsize)													\
	{																									\
		SERVER_DEBUG_ERROR_6("LAY_MEMCPY: ������� �������� ������������ ������."\
			" %s[%d].m_%s:  offset=%d size=%d filesize=%d", 							\
			className[classID], objID, #field, offset, size, maxsize);				\
		return 0;																					\
	}																									\
	memcpy (to, from+offset, size);															 
//----------------------------------------------------------------------------[]
#define OD_SAVE_SIMPLE_ARRAY(type,field)													\
		memcpy (file.GetPtr()+nOffset, 														\
			d_##field.GetPtr(), 																	\
			d_##field.GetSize()*sizeof(type));												\
		nOffset  += d_##field.GetSize()*sizeof(type);									
//----------------------------------------------------------------------------[]
#define OD_LOAD_SIMPLE_ARRAY(type,field)													\
		LAY_MEMCPY (																				\
			d_##field.GetPtr(), 																	\
			file.GetPtr(),																			\
			nOffset, 																				\
			arr_size_##field*sizeof(type),													\
			file.GetSize(),																		\
		field);																						\
		nOffset  += arr_size_##field*sizeof(type);
//----------------------------------------------------------------------------[]





//------------------------------------------------------------------------------[]
//
// �������������� �������
//
enum OBJ_CLASS_ID
{
   OBJ_CLASS_ID_Registry = 0,
   OBJ_CLASS_ID_Relation = 2,
   OBJ_CLASS_ID_Linkage = 3,
   OBJ_CLASS_ID_LinkProxy = 4,
   OBJ_CLASS_ID_Connectable = 5,
   OBJ_CLASS_ID_MetaObject = 6,
   OBJ_CLASS_ID_Concept = 7,
   OBJ_CLASS_ID_User = 8,
   OBJ_CLASS_ID_UserGroup = 9,
   OBJ_CLASS_ID_Text = 10,
   OBJ_CLASS_ID_MorphologicRule = 11,
   OBJ_CLASS_ID_SearchItem = 12,
   OBJ_CLASS_ID_StopWord = 13,
   OBJ_CLASS_ID_WordNibbleABC = 14,
   OBJ_CLASS_ID_WebFolder = 16,
   OBJ_CLASS_ID_WebFile = 17,
   OBJ_CLASS_ID_UserProfile = 18,
   OBJ_CLASS_ID_InfoDiv = 19,
   OBJ_CLASS_ID_InfoSource = 20,
   OBJ_CLASS_ID_InfoObject = 21,
   OBJ_CLASS_ID_END
};






//------------------------------------------------------------------------------[]
// 
// ������-������ ��� ������ "Registry"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Registry
#endif
#ifdef USES_OC_Registry
class OD_Registry: public OD_BASE
{
public:
// �����������
   OD_Registry (bool bFieldsInit);
// ����������
  ~OD_Registry ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   bool           d_NeedInitiate;
   identifier_arr d_ConceptID_Sorted;
   int_arr        d_ConceptNo_SortID;
   identifier_arr d_ConceptID_SortNo;
   int_arr        d_ConceptParent_SortNo;
   int_arr        d_ConceptType_SortNo;
   int_arr        d_ConceptLevel_SortNo;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "Relation"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Relation
#endif
#ifdef USES_OC_Relation
class OD_Relation: public OD_BASE
{
public:
// �����������
   OD_Relation (bool bFieldsInit);
// ����������
  ~OD_Relation ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_SysName;
   string         d_Name;
   string         d_Description;
   int            d_CreationTime;
   int            d_Version;
   string_arr     d_FieldName;
   string_arr     d_FieldType;
   string_arr     d_FieldSysName;
   string_arr     d_FieldDescription;
   string_arr     d_FieldInterfaceType;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;
   guid_arr       d_FeodGUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "Linkage"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Linkage
#endif
#ifdef USES_OC_Linkage
class OD_Linkage: public OD_BASE
{
public:
// �����������
   OD_Linkage (bool bFieldsInit);
// ����������
  ~OD_Linkage ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int            d_CreationTime;
   identifier     d_RelationID;
   identifier_arr d_ProxyID;
   string_arr     d_Value;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "LinkProxy"
// 
#ifdef  USES_OC_ALL
#define USES_OC_LinkProxy
#endif
#ifdef USES_OC_LinkProxy
class OD_LinkProxy: public OD_BASE
{
public:
// �����������
   OD_LinkProxy (bool bFieldsInit);
// ����������
  ~OD_LinkProxy ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   int            d_CreationTime;
   guid           d_RealObject;
   identifier_arr d_LinkageID;
   identifier_arr d_RelationID;
   int_arr        d_RelationField;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "Connectable"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Connectable
#endif
#ifdef USES_OC_Connectable
class OD_Connectable: public OD_BASE
{
public:
// �����������
   OD_Connectable (bool bFieldsInit);
// ����������
  ~OD_Connectable ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   guid           d_ProxyObject;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "MetaObject"
// 
#ifdef  USES_OC_ALL
#define USES_OC_MetaObject
#endif
#ifdef USES_OC_MetaObject
class OD_MetaObject: public OD_BASE
{
public:
// �����������
   OD_MetaObject (bool bFieldsInit);
// ����������
  ~OD_MetaObject ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Type;
   string         d_Name;
   string         d_SysName;
   string         d_Header1;
   string         d_Header2;
   string         d_Header3;
   string         d_Header4;
   string         d_Header5;
   string         d_Comment;
   string         d_Text;
   int_arr        d_arrInt;
   float_arr      d_arrFloat;
   bool_arr       d_arrBool;
   byte_arr       d_arrByte;
   int_arr        d_arrTime;
   string_arr     d_arrString;
   guid_arr       d_arrGUID;
   identifier_arr d_arrID;
   int            d_CreationTime;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;
   guid_arr       d_FeodGUID;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "Concept"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Concept
#endif
#ifdef USES_OC_Concept
class OD_Concept: public OD_BASE
{
public:
// �����������
   OD_Concept (bool bFieldsInit);
// ����������
  ~OD_Concept ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Name;
   string         d_Description;
   string         d_Type;
   int            d_TypeNo;
   identifier     d_Parent;
   identifier_arr d_Ancestor;
   int_arr        d_AncestorNo;
   int_arr        d_AncestorWeight;
   identifier_arr d_AllAncestor;
   identifier_arr d_AllAncestorNo;
   identifier_arr d_Child;
   int_arr        d_ChildNo;
   identifier_arr d_Descendant;
   int_arr        d_DescendantNo;
   int            d_Level;
   int            d_No;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "User"
// 
#ifdef  USES_OC_ALL
#define USES_OC_User
#endif
#ifdef USES_OC_User
class OD_User: public OD_BASE
{
public:
// �����������
   OD_User (bool bFieldsInit);
// ����������
  ~OD_User ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Login;
   string         d_Password;
   bool           d_PasswordInBrowser;
   int            d_CreationTime;
   string         d_FullName;
   string         d_Email;
   string         d_URL;
   string         d_Data;
   int            d_AccessLevel;
   identifier_arr d_GroupID;
   identifier_arr d_OwnFeodID;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "UserGroup"
// 
#ifdef  USES_OC_ALL
#define USES_OC_UserGroup
#endif
#ifdef USES_OC_UserGroup
class OD_UserGroup: public OD_BASE
{
public:
// �����������
   OD_UserGroup (bool bFieldsInit);
// ����������
  ~OD_UserGroup ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Name;
   string         d_Type;
   string         d_Description;
   int            d_CreationTime;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;
   identifier_arr d_UserID;
   identifier_arr d_Rights_Feod;
   string_arr     d_Rights_Attr;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "Text"
// 
#ifdef  USES_OC_ALL
#define USES_OC_Text
#endif
#ifdef USES_OC_Text
class OD_Text: public OD_BASE
{
public:
// �����������
   OD_Text (bool bFieldsInit);
// ����������
  ~OD_Text ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Name;
   string         d_Text;
   int            d_CreationTime;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "MorphologicRule"
// 
#ifdef  USES_OC_ALL
#define USES_OC_MorphologicRule
#endif
#ifdef USES_OC_MorphologicRule
class OD_MorphologicRule: public OD_BASE
{
public:
// �����������
   OD_MorphologicRule (bool bFieldsInit);
// ����������
  ~OD_MorphologicRule ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   byte           d_Attribute;
   byte_arr       d_BaseEnd_Available;
   byte_arr       d_BaseEnd_Exception;
   string         d_AffixNormal;
   string         d_AffixVariant;
   string         d_Comment;
   int            d_Number;
   int            d_MatchCount;
   int            d_ApplyCount;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "SearchItem"
// 
#ifdef  USES_OC_ALL
#define USES_OC_SearchItem
#endif
#ifdef USES_OC_SearchItem
class OD_SearchItem: public OD_BASE
{
public:
// �����������
   OD_SearchItem (bool bFieldsInit);
// ����������
  ~OD_SearchItem ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_NormalWord;
   string         d_NormalWordInv;
   string         d_Attributes;
   bool           d_Hypothesis;
   int            d_Text_Number;
   guid_arr       d_Text_ObjectSortedGUID;
   int_arr        d_Text_ModificationTime;
   int_arr        d_Text_WordAppearanceNum;
   int_arr        d_Text_WordFirstPosition;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "StopWord"
// 
#ifdef  USES_OC_ALL
#define USES_OC_StopWord
#endif
#ifdef USES_OC_StopWord
class OD_StopWord: public OD_BASE
{
public:
// �����������
   OD_StopWord (bool bFieldsInit);
// ����������
  ~OD_StopWord ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Word;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "WordNibbleABC"
// 
#ifdef  USES_OC_ALL
#define USES_OC_WordNibbleABC
#endif
#ifdef USES_OC_WordNibbleABC
class OD_WordNibbleABC: public OD_BASE
{
public:
// �����������
   OD_WordNibbleABC (bool bFieldsInit);
// ����������
  ~OD_WordNibbleABC ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Nibble;
   int            d_Num;
   float          d_FreqPerMillion;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "WebFolder"
// 
#ifdef  USES_OC_ALL
#define USES_OC_WebFolder
#endif
#ifdef USES_OC_WebFolder
class OD_WebFolder: public OD_BASE
{
public:
// �����������
   OD_WebFolder (bool bFieldsInit);
// ����������
  ~OD_WebFolder ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   identifier_arr d_WebFileSortedID;
   int            d_ShowCount;
   int            d_ClickCount;
   float          d_CTR;
   int            d_Estimation_Tot;
   int            d_Estimation_Num;
   float          d_Estimation;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "WebFile"
// 
#ifdef  USES_OC_ALL
#define USES_OC_WebFile
#endif
#ifdef USES_OC_WebFile
class OD_WebFile: public OD_BASE
{
public:
// �����������
   OD_WebFile (bool bFieldsInit);
// ����������
  ~OD_WebFile ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Name_OSFile;
   string         d_Name_Upload;
   string         d_MIMEType;
   string         d_IconType;
   identifier_arr d_WebFolderID;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;
   int            d_CreationTime;
   int            d_ModificationTime;
   int            d_LastAccessTime;
   int            d_Version;
   byte_arr       d_BinaryData;
   int            d_ShowCount;
   int            d_ClickCount;
   float          d_CTR;
   int            d_Estimation_Tot;
   int            d_Estimation_Num;
   float          d_Estimation;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;
   string         d_Name;
   string         d_Description;
   string         d_Text;
   string         d_Additional;
   identifier_arr d_SearchItemID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "UserProfile"
// 
#ifdef  USES_OC_ALL
#define USES_OC_UserProfile
#endif
#ifdef USES_OC_UserProfile
class OD_UserProfile: public OD_BASE
{
public:
// �����������
   OD_UserProfile (bool bFieldsInit);
// ����������
  ~OD_UserProfile ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   guid           d_UserGUID;
   identifier_arr d_InfoDiv_Hide;
   identifier_arr d_InfoDiv_Show;
   string_arr     d_Filter_Name;
   string_arr     d_Filter_SearchPhrase;
   identifier_arr d_Filter_FolderID;
   identifier_arr d_SeenIO_ID;
   int_arr        d_SeenIO_Time;
   byte_arr       d_SeenIO_Estimation;
   int            d_SeenIO_ShowCount;
   int            d_SeenIO_ClickCount;
   float          d_SeenIO_CTR;
   identifier_arr d_OwnIO;
   int_arr        d_OwnIO_Time;
   int            d_OwnIO_ShowCount;
   int            d_OwnIO_ClickCount;
   float          d_OwnIO_CTR;
   int            d_OwnIO_Estimation_Tot;
   int            d_OwnIO_Estimation_Num;
   float          d_OwnIO_Estimation;
   guid_arr       d_Log_ObjectGUID;
   int_arr        d_Log_Action;
   int_arr        d_Log_Time;
   bool           d_Account_Enable;
   float          d_Account_Debit;
   float          d_Account_Credit;
   int_arr        d_Account_Log_Action;
   float_arr      d_Account_Log_Amount;
   float_arr      d_Account_Log_Debit;
   float_arr      d_Account_Log_Credit;
   int_arr        d_Account_Log_Time;
   string_arr     d_Account_Log_Comment;
   guid           d_RootFolderGUID;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "InfoDiv"
// 
#ifdef  USES_OC_ALL
#define USES_OC_InfoDiv
#endif
#ifdef USES_OC_InfoDiv
class OD_InfoDiv: public OD_BASE
{
public:
// �����������
   OD_InfoDiv (bool bFieldsInit);
// ����������
  ~OD_InfoDiv ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   identifier_arr d_InfoSourceSortedID;
   identifier_arr d_InfoObjectSortedID;
   guid           d_ClipArtGUID;
   int            d_ShowCount;
   int            d_ClickCount;
   float          d_CTR;
   int            d_Estimation_Tot;
   int            d_Estimation_Num;
   float          d_Estimation;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "InfoSource"
// 
#ifdef  USES_OC_ALL
#define USES_OC_InfoSource
#endif
#ifdef USES_OC_InfoSource
class OD_InfoSource: public OD_BASE
{
public:
// �����������
   OD_InfoSource (bool bFieldsInit);
// ����������
  ~OD_InfoSource ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_Name;
   string         d_Description;
   string         d_URL;
   int            d_RefreshType;
   identifier_arr d_InfoDivID;
   guid           d_LogoGUID;
   guid_arr       d_ColumnistGUID;
   string         d_Address;
   string         d_Language;
   string         d_Type;
   string         d_State;
   int            d_ShowCount;
   int            d_ClickCount;
   float          d_CTR;
   int            d_Estimation_Tot;
   int            d_Estimation_Num;
   float          d_Estimation;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
// ������-������ ��� ������ "InfoObject"
// 
#ifdef  USES_OC_ALL
#define USES_OC_InfoObject
#endif
#ifdef USES_OC_InfoObject
class OD_InfoObject: public OD_BASE
{
public:
// �����������
   OD_InfoObject (bool bFieldsInit);
// ����������
  ~OD_InfoObject ();
// �������� �������� ������ ������
   void AddKeyVarForField (key_arr& ka, identifier fieldID);

// ����-������
   string         d_SysName;
   guid           d_OwnerGUID;
   int            d_AccessLevelThreshold;
   int            d_CreationTime;
   int            d_InfoTime;
   identifier_arr d_InfoDivID;
   bool           d_UsageStrictAccess;
   int_arr        d_Log_Action;
   guid_arr       d_Log_UserGUID;
   int_arr        d_Log_Time;
   string_arr     d_Log_Comment;
   guid           d_IconGUID;
   string         d_OriginalText;
   guid_arr       d_ArtworkGUID;
   identifier     d_InfoSourceID;
   identifier     d_AuthorID;
   string         d_AuthorStr;
   string         d_URL;
   string_arr     d_RelatedLinks;
   identifier_arr d_CategoryID;
   int            d_ShowCount;
   int            d_ClickCount;
   float          d_CTR;
   int            d_Estimation_Tot;
   int            d_Estimation_Num;
   float          d_Estimation;
   string         d_Name;
   string         d_Description;
   string         d_Text;
   string         d_Additional;
   identifier_arr d_SearchItemID;
   guid           d_ProxyObject;
   string_arr     d_FIELD_Extension_Name;
   string_arr     d_FIELD_Extension_Value;
   guid           d_MOD_Base_GUID;
   guid           d_MOD_Extension_GUID;

// �������� ������� � �����
   size_t LoadFromFile (identifier objID);


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
