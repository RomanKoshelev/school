/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain                                                 []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            key_arr.h																	[]
[] Date:            11.04.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     ����������� ����� ��� ��������										[]
[]____________________________________________________________________________[]
*/
#ifndef key_arr_H
#define key_arr_H


enum FIELD_TYPE
{
	FT_identifier	=	0,
	FT_guid			=	1,
	FT_int			=	2,
	FT_byte			=	3,
	FT_bool			=	4,
	FT_float			=	5,
	FT_string		=	6,

	FT_nothing		=	7
};
typedef void* OBD_pointer;

int CompareFunction_CObjIndex_AVTree_Item (pbyte& a, pbyte& b);


#define MAX_KEY_LENGTH (256*1024)

extern char * FT_NAME_SHORT[];
extern char * FT_NAME		[];	
extern char * FT_NAME_ARR	[];
extern char * FT_VOID;
extern char * FT_SIZE_T;



//______________________________________________________________________________
//                                                                            []
//` key_arr 																						[]
//                                                                            []
struct key_arr
{
//	����� ������ ��� ������ �������� � ���� ������.
// ����� ����� ����������� ���������� += (type) key;
// ���������� ����: int, byte, bool, float, identifier, string, const char *;
// �������� ���� ����� �������� Init() -- ���� ����� ��������� ������.
// �� ��������� ����������� ���� (� �.�. ������) ��������, ��� ��� ������ 
// �������� ����� �������������� �������� ����� �� ����������� ����� �����.
// ��������: ���� ���� ������ ���� �� � ��� �������, ��� ��������
// ������ ����� �������� �������, �� ������� ����� ������������ ����� ����.
// ��������� ���� � ����� ������� -- ������������� �������. �� ����������� �������������.
// ����� �������, ��������� ������ ���� -- ��� ���� �� ����� ������ + ������������� �������.
	protected: void About_class_key_arr(){};

// [size_t Size, byte KeyNum, key1, ... keyN]
// Keyi    = [byte type, data]	
// LastKey = idendifier key
	public: 		byte * m_pData; 

	protected: 	size_t m_nRealSize; 

	protected: void Erase ();

	protected: void CopyFrom (const key_arr& from);


//RVK:>>>
	void SET_MPDATA (byte * M_PDATA, byte type, const byte * data, bool bInvert=false);


// ���������� ����� � �����
	protected: void AddKey (const pbyte pVal, FIELD_TYPE type, size_t nStrLen=0);


// ���������� ������
// ���� �� ������ �������� -- ������ � stdout
	public: void DebugPrint(string* pStr=NULL);

// �������� ����� �� ������
	public: void GetKeyData (int item, void *_pRetVal);

// �������� ������ ������
	public: size_t GetSize() const;

// �������� ����� -- � �� ����� ���� ������.
	public: void Init ();

// �����������
	public: key_arr ();

// ����������� �� ������� ������ ������
	public: key_arr (const key_arr& from);
// ����������� �� �����
	public: key_arr (int					val);
	public: key_arr (byte				val);
	public: key_arr (bool				val);
	public: key_arr (float				val);
	public: key_arr (identifier		val);
	public: key_arr (const string&	val);
	public: key_arr (const char *		val);
	public: key_arr (time_t				val);

// ����������
	public: ~key_arr();

// ������������� �� ������� ������ ������
	public: key_arr& operator= (const key_arr& from);

// ������������� �� ��������� �� ������ ������� ������ ������
	public: void FromPtr(pbyte pData);

// �������� ����� ������ � ������
	public: size_t GetKeyNum ();

	protected: pbyte GetPackedItemPtr (size_t item);

//	�������� ��� ����� �� ������
	public: byte			GetItemType(size_t item);
//	�������� ��������� �� ���� �� ������
	public: 	pbyte			GetItemPtr (size_t item);


//	�������� �������������, ���������� � ������ ������
	public: identifier GetObjID ();

//RVK:>>>
	protected: void SetNumericItemData (size_t item, pbyte pVal, bool bInvert);

// SetStringItemData
	protected: void SetStringItemData (size_t item, const char * _pData, size_t length,  bool bInvert);

// ���������� � ������ ������ �������� � �����:
// int, byte, bool, float, identifier, string, const char *
	public: void SetKeyData (size_t item, int					val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, byte				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, bool				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, float				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, identifier		val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, guid				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, const string&	val, bool bInvert)	{SetStringItemData	(item, val.c_str(),	val.length(),	bInvert);}
	public: void SetKeyData (size_t item, const char *		val, bool bInvert)	{SetStringItemData	(item, val,				strlen(val),	bInvert);}

// �������� � ����� ����:
// int, byte, bool, float, identifier, string, const char *, time_t, guid
	public: key_arr & operator+= (int				val)	{AddKey((const pbyte)&val,				FT_int);								return *this;}
	public: key_arr & operator+= (byte				val)	{AddKey((const pbyte)&val,				FT_byte);							return *this;}
	public: key_arr & operator+= (bool				val)	{AddKey((const pbyte)&val,				FT_bool);							return *this;}
	public: key_arr & operator+= (float				val)	{AddKey((const pbyte)&val,				FT_float);							return *this;}
	public: key_arr & operator+= (identifier		val)	{AddKey((const pbyte)&val,				FT_identifier);					return *this;}
	public: key_arr & operator+= (guid				val)	{AddKey((const pbyte)&val,				FT_guid);							return *this;}
	public: key_arr & operator+= (const string&	val)	{AddKey((const pbyte)val.c_str(),	FT_string, val.len());			return *this;}
	public: key_arr & operator+= (const char *	val)	{AddKey((const pbyte)val,				FT_string,	strlen (val));		return *this;}
	public: key_arr & operator+= (time_t			val)	{AddKey((const pbyte)&val,				FT_int);								return *this;}

// ��������� ������� ������
	public: bool operator < (key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) <  0;}
// ��������� ������� ������
	public: int Compare		(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg);		}
// ��������� ������� ������
	public: bool operator <=(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) <= 0;}
// ��������� ������� ������
	public: bool operator > (key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) >  0;}
// ��������� ������� ������
	public: bool operator >=(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) >= 0;}
// ��������� ������� ������
	public: bool operator ==(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) == 0;}
	
// ��������	��������� �� ������
	const pbyte GetPtr()		{return m_pData;}
};
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/