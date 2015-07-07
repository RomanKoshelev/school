/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            string.h																	[]
[] Date:            16.04.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     ����� - ��������� ����������
[]____________________________________________________________________________[]
*/
#ifndef string_H
#define string_H

//______________________________________________________________________________
//                                                                            []
// string																							[]
typedef const char * const_char_ptr;
class string: public CPtr<char>
{
// ����� - ��������� ����������
// ������ ��-�� ����, ��� � ����������� ������ (STL) 
// ����������� ���������� �������� ������������.
// ��������: ������ ���������� ��������� �� ��������� ����������:
// const char * BadFunction()
// {
//    string local_str "��-��";
//    return  local_str;
// }
	protected: void About_class_string (){}


//______________________________________________________________________________
//                                                                            []
//` ������������																					[]
//                                                                            []

//	����������� = ""
	public: string ();
//	����������� (string, const char *, char)
	public: string (char from);
//	����������� (string, const char *, char)
	public: string (const char* from);
//	����������� (string, const char *, char)
	public: string (const string& from);
//	�������� ������������ (string, const char *, char)
	public: string& operator = (char from);
//	�������� ������������ (string, const char *, char)
	public: string& operator = (const char* from);
//	�������� ������������ (string, const char *, char)
	public: string& operator = (const string& from);
//	����������� ������ ������ (const char*)
	public: string& Copy (const char* from, size_t str_len);
// ������������� ��������� ������ ��������� ����� �� ������ ��������� ��������.
// ���� bRandomLen==true, �� ����� ������ ���������� ��������� ������� � �������� �� 0 �� strLen.
	public: void Randomize (int strLen=16, const char *alfabet="1234567890_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", bool bRandomLen=false);
// ��������� �������� ���������������� ���� � ����������� �������
	public: string& SetVariant (const identifier&	val) {Format ("%u",	val); return *this;};
	public: string& SetVariant (const int&				val) {Format ("%d",	val); return *this;};
	public: string& SetVariant (const char&			val) {Format ("%c",	val); return *this;};
	public: string& SetVariant (const float&			val) {Format ("%f",	val); return *this;};
	public: string& SetVariant (const char *			val) {Format ("%s",	val); return *this;};
// ������ �������� ���������������� ����
	public: void GetVariant (identifier&	val);
	public: void GetVariant (int&				val);
	public: void GetVariant (char&			val);
	public: void GetVariant (float&			val);
	public: void GetVariant (string&			val);	


//______________________________________________________________________________
//                                                                            []
//` ����� � ��������                                                          []                
//                                                                            []

//	���������� ��������� ��� �������. �� ��������� ������ � ������ ������.
// ���������� ������� ��� -1, ���� �� �������.
	public: int Find (const char * Substr, int nPos=0);
//	���������� ��������� ��� �������. �� ��������� ������ � ������ ������.
// ���������� ������� ��� -1, ���� �� �������.
	public: int Find (char C, int nPos=0);
// ����� ���������
	public: void SubStr (string& Substr, int nPos1=0, int nPos2=-1);
//	�������� �� �������. �� ��������� ����������� ���������� ����� '\n'
	public: void implode (CPtr<string>& arr, const char * sDelimiter="\n");
//	��������� �� ������. �� ��������� ����������� �� ������ '\n'
	public: void explode (CPtr<string>& arr, const char * sDelimiter="\n", bool PrintPercent=false);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ���������																						[]
//                                                                            []

//	�������� ������������ ����� (const char* ��� string)
	public: const char * operator + (const char * add);
//	�������� ������������ ����� (const char* ��� string)
	public: const char * operator + (const string& add);
//	�������� ������ (const char* ��� string)
	public: string operator += (const char * add);
//	�������� ������ (const char* ��� string)
	public: string& operator += (const string& add);
//	�������� ������ (char)
	public: string& operator += (char C);
//	�������� ������ (const char*)
	public: string& AddString (const char* add, size_t add_len);
//	������ � ����� ������ ������ �������:
// ������ ��������� \r \n
	public: void rtrim ();
//	������ �� ������ ������ ������ �������:
// ������ ��������� \r \n
	public: void ltrim ();
//	������ �� ������ � � ����� ������ ������ �������:
// ������ ��������� \r \n
	public: void trim ();
// ��������� ������� ������ � ������� �������.
// ��������������, ��� ��������� ����� ��������� Win1251.
	public: void strupr(void);
// ��������� ������� ������ � ������ �������.
// ��������������, ��� ��������� ����� ��������� Win1251.
	public: void strlwr(void);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ���������																						[]
//                                                                            []
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator == (const string& to) const;
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator == (const char * to) const;
//	��������� �� ����������� �� ������� (const char* ��� string)
	public: bool operator != (const string& to) const;
//	��������� �� ����������� �� ������� (const char* ��� string)
	public: bool operator != (const char * to) const;
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator <= (const string& to) const;
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator < (const string& to) const;
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator >= (const string& to) const;
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator > (const string& to) const;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` �����																							[]
//                                                                            []
//	����� ���������� ���� -- ����� ������+1 !
	public: public: size_t GetSize () const {return m_nSize;}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t len ()	const	{return m_nSize-1;}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t Len ()	const	{return len();}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t Length ()	const	{return len();}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t length ()	const	{return len();}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t size ()	const	{return len();}
//	����� ������ == ����� ���������� ���� - 1 (��� ����)
	public: size_t Size ()	const	{return len();}
//	������ �������� ������ (=="")
	public: bool IsEmpty	() const {return m_pData==NULL || m_pData[0]==0;};
//____________________________________________________________________________[]


// �������� ������ (="") ���� ��� � Erase()
   public:  void Delete();
// �������� ������ (="") ���� ��� � Delete()
   public:  void Erase();


//______________________________________________________________________________
//                                                                            []
//` ���������																						[]
//                                                                            []

//	�������� ��������� �� ������ - ������
	public: const char * c_str () const
	{
		SERVER_DEBUG_ASSERT_RETURN (m_pData, "string::c_str () -- m_pData=NULL", NULL);
		return m_pData;
	}
//	�������� ��������� �� ������ - ������
	public: operator const_char_ptr () const
	{
		SERVER_DEBUG_ASSERT_RETURN (m_pData, "string::const_char_ptr () -- m_pData=NULL", NULL);
		return m_pData;
	}
//____________________________________________________________________________[]


//	����� ������ �� �����
	void Print () const;
// CPtr:: �������� ������ � ������� � �� 		
// ������ �� ����� OS, ��������� �� �����.
	public:	size_t ReadFile(const char *fileName);
//	����� ������ �� �����
	void Println () const;
// ��������� ������ � ������������ � �������� � �����������
// �������� ��� ������� sprintf().
	void Format (const char * sFormat, ...);
//	�������� 32-� ��������� ������ �� ������.
	public: unsigned long GetCRC (void) const;
// ������������� ������ � DOS-���������
	public: string& win_2_dos ();
// ���������, �������� �� ������ ����������� �� 
//	�������� ����������� ���� ���������� �++
	public: bool CheckSysName (void) const;
};
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Helpers																							[]
//                                                                            []
bool operator == (const char * str1, string& str2);
bool operator != (const char * str1, string& str2);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/