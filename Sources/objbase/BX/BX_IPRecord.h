/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 2000 Alex Vershinin.                                         []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_IPRecord.h                                             []
[] Date:            03.01.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                  
#ifndef BX_IPRecord_H
#define BX_IPRecord_H

struct	BX_IPRecord_Args
{
	BX_IPRecord_Args()
	{
		Count		= 0;
		Checked	= false;
		objID		= NA;
	}

	int				Count;			// ������� ����� � ����� ��������� IP.
	string			Mask;				// ����� ��������� ������� (�.�. ����� ��� ��������� �����).
	string			First;			// ������ ���������.
	string			Last;				// ����� ���������.
	bool				Checked;			// ��������� ���������������
											
											
	identifier_arr	ConceptID;		// �������������� ���������, ��������������� ����� ���������.

	string			AdminPassword;	// ������ ������.
	identifier		objID;			// ������������� ������� ���������.

	int				objFirstNo;		// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
	int				objLastNo;		// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

	identifier_arr	objIDs;			// �������������� ��������.
	string_arr		objNames;		// ���������� � ����������.
};
//----------------------------------------------------------------------------[]
// ������������ IP-����� � ����. ���� ��� ����� ������ ����������� ��������, ��
// �������������� � ������� ���� CRA_Inquiry.
BX_RESULT
RegisterIP(
	const string&	IPAddressStr,
	OC_Viewer&		oc_viewer,
	bool				bHost,
	bool				bNewVisitor,
	time_t			CurrentTime);

// ����� ������������������ IP-����������.
BX_RESULT BX_IPRecord_Enumerate	(BX_IPRecord_Args& arg);

// ���������� ������� ��������� ������� � ��������������� ��� ��������.
BX_RESULT BX_IPRecord_Check		(BX_IPRecord_Args& arg);

// �������� ��������� ��������� �������.
BX_RESULT BX_IPRecord_GetData		(BX_IPRecord_Args& arg);

// ������� ����� �������� �������.
BX_RESULT BX_IPRecord_New			(BX_IPRecord_Args& arg);
//______________________________________________________________________________
//                                                                            []
//` IP_Address                                                                []          
//                                                                            []
class IP_Address
{
private:
	string	m_Address;		// 
	int_arr	m_Digits;

public:

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ������������� �������, ������������ ������ 64 ������� ������ IP
// ����������� - '.', ���� ���������� �� �����, �� ������ �������������,
// �.�.	�� '192.a168.200.8' ��������� '192',
//			�� '192.168a.200.8' ��������� '192.168.200.8',
//			�� '192.16a8.200.8' ��������� '192.16.200.8',
// �� ������-�� ��� ��� ������� ��� ����, ����� �� '192.168.*' �������� '192.16.200'
	void Init(const string& IP)
	{
		const int	AddressBufSize = 64;
		const char	Separators[] = ". (),-\t\n\r";
		static char AddressBuf[AddressBufSize];
		char			*token = NULL;
		string		Str;
		int			IP_Digit = -1;

		m_Address.Erase();
		m_Digits.Erase();

		strncpy(AddressBuf, IP.c_str(), AddressBufSize-1);

		token = strtok(AddressBuf, Separators);
	// ���� ���������������������������� ���� ������:
		while (token != NULL)
		{
			if (!isdigit(int(*token)))			break;

			IP_Digit = atoi(token);

			if (IP_Digit<0 || IP_Digit>255)	break;

			m_Digits.Add(IP_Digit);

			Str.Format("%s%d",
				m_Digits.Size() == 1 ? "" : ".",
				IP_Digit);
			m_Address += Str;

			if (m_Digits.Size() >= 4)			break;

			token = strtok(NULL, Separators);
		}
	// ������ ���������� �� 4 ����:
		for (int i = m_Digits.Size(); i < 4; i++) {
			m_Address += ((i == 0) ? "*":".*");
		}

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ����������� �� string'�
	IP_Address(const string& IP)
	{
		Init(IP);
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ����������� �� const char*
	IP_Address(const char* IP)
	{
		Init(IP);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ����������� �� ���������
	IP_Address(void)
	{
		Init("0.0.0.0");
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ����������� �����������
	IP_Address(const IP_Address& ip_address)
	{
		CopyFrom(ip_address);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ����������� �� ������� �������
	IP_Address& CopyFrom(const IP_Address& ip_address)
	{
		string Str;
		ip_address.GetIP(Str);
		Init(Str);
		
		return *this;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// �������� ������������
	IP_Address& operator = (const IP_Address& from)
	{
		return CopyFrom (from);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� IP-������ � ���� string'�
// ���� WithZeros==true, ����� ���������� ����� ������, ���� �����.
// ���������� Digits ����, ������� ��� �������� ���������� *.
	void GetIP(string& IP_Str, bool WithZeros = false, int Digits = 4) const
	{
		if (Digits < 0 || Digits > 50)	{
			Digits = 4;
		}

		string Str;
		IP_Str.Erase();
		int nSize = m_Digits.Size();
		int i;

		for (i = 0; i < nSize && i < Digits; i++)
		{
			if (WithZeros)	Str.Format("%s%03d", i == 0 ? "" : ".", (int)m_Digits[i]);
			else				Str.Format("%s%d",	i == 0 ? "" : ".", (int)m_Digits[i]);
			IP_Str += Str;
		}

		if (nSize < Digits) {
			for (i = 0; i < Digits; i++)
			{
				if (WithZeros)	IP_Str += "***";
				else				IP_Str += "*";
			}
		}

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� IP-������ � ���� const char* 
	const char* GetIP(void) const
	{
		return m_Address.GetPtr();
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� Level-��� ����� IP-������ (���� ���������� � 0 ����� �������)
// ���������� -1 � ������, ���� ����� ������ ������ ���.
	int GetDigit(int Level) const
	{
		int nSize = m_Digits.Size();
		if (Level < 0 || Level >= nSize) return -1;
		return m_Digits[Level];
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���������� ���� � IP-������
	int Size(void) const
	{
		return m_Digits.Size();
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ����� ��������� � ������� Level � ������ IP_Mask
// �.�. ��������� Level ���� ������, � ������ ��������� �������� '*'.
// ���� WithZeros==true, ����� ���������� ����� ������, ���� �����.
	void GetMask(string& IP_Mask, int Level = 3, bool WithZeros = false) const
	{
		IP_Mask.Erase();
		string Str;
		for (int i = 0; (i < Level) && (i < m_Digits.Size()); i++)
		{
			if (WithZeros)		Str.Format("%03d.", m_Digits[i]);
			else					Str.Format("%d.", m_Digits[i]);
			IP_Mask += Str;		
		}

		IP_Mask += "*";

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� �� IP ����� � ���������, ���������� ����������;
// ����������� ����� � ��������� ���������, ��� *, � this - 
// ��� ����.
	bool IsInRange(const char* ip_address) const
	{
		return IsInRange(IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� �� IP ����� � ���������, ���������� ����������;
// ����������� ����� � ��������� ���������, ��� *, � this - 
// ��� ����.
	bool IsInRange(const string& ip_address) const
	{
		return IsInRange(IP_Address(ip_address));
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� �� IP ����� � ���������, ���������� ����������;
// ����������� ����� � ��������� ���������, ��� *, � this - 
// ��� ����.
	bool IsInRange(const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int i;

	// ��������� ����� ������ ���������:
		for (i = 0; (i < nSize1) && (i < nSize2); i++)	{
			if (m_Digits[i] != ip_address.GetDigit(i)) {
				return false;
			}
		}
	// ���� ����� ������, �� ��� �� �������� ����� ����� ������� �����:
		if (nSize1 >= nSize2) {
			return true;	// * == any num
		}

	// nSize1 < nSize2
	// ���� ����� �������, �� ����������� � ������ ����� ������� ������:
		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) != 0) {
				return false;
			}
		}

		return true;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator > (const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int Digit1, Digit2;
		int i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			Digit1 = m_Digits[i];
			Digit2 = ip_address.GetDigit(i);

			if (Digit1 != Digit2) {
				return (Digit1 > Digit2);
			}
		}

		if (nSize1 <= nSize2) {
			return false; // ��� ����� ��� ����� �������� ������ �� ����� ���� ������.
		}

		// nSize1 > nSize2
		for (i = nSize2; i < nSize1; i++) {
			if (m_Digits[i] > 0) {
				return true;
			}
		}

		return false; // ��� �����
	}			
	bool operator > (const string& ip_address) const
	{
		return (*this > IP_Address(ip_address));
	}			
	bool operator > (const char* ip_address) const
	{
		return (*this > IP_Address(ip_address));
	}			
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator >= (const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int Digit1, Digit2;
		int i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			Digit1 = m_Digits[i];
			Digit2 = ip_address.GetDigit(i);

			if (Digit1 != Digit2) {
				return (Digit1 > Digit2);	// ������
			}
		}

		if (nSize1 >= nSize2) {
			return true; // ��� ����� ��� ����� �������� ������ �� ����� ���� ������.
		}

		// nSize1 < nSize2
		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) > 0) {
				return false; // ������
			}
		}

		return true; // ��� �����
	}			
	bool operator >= (const string& ip_address) const
	{
		return (*this >= IP_Address(ip_address));
	}			
	bool operator >= (const char* ip_address) const
	{
		return (*this >= IP_Address(ip_address));
	}			

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator == (const IP_Address& ip_address) const
	{
		int	nSize1 = m_Digits.Size();
		int	nSize2 = ip_address.Size();
		int	i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			if (m_Digits[i] != ip_address.GetDigit(i))
				return false;
		}

		if (nSize1 == nSize2)
			return true;

		if (nSize1 > nSize2) {
			for (i = nSize2; i < nSize1; i++) {
				if (m_Digits[i] != 0) {
					return false;
				}
			}
			return true;
		}

		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) != 0) {
				return false;
			}
		}

		return true;
	}
	bool operator == (const string& ip_address) const
	{
		return (*this == IP_Address(ip_address));
	}
	bool operator == (const char* ip_address) const
	{
		return (*this == IP_Address(ip_address));
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator != (const IP_Address& ip_address) const
	{
		return !(*this == ip_address);
	}
	bool operator != (const string& ip_address) const
	{

		return !(*this == IP_Address(ip_address));
	}
	bool operator != (const char* ip_address) const
	{
		return !(*this == IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator < (const IP_Address& ip_address) const
	{
		return !(*this >= ip_address);
	}
	bool operator < (const string& ip_address) const
	{
		return !(*this >= IP_Address(ip_address));
	}
	bool operator < (const char* ip_address) const
	{
		return !(*this >= IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// ��������� ���� �������. ��� �������� ������
// ����������� ����� ��������� ������.
	bool operator <= (const IP_Address& ip_address) const
	{
		return !(*this > ip_address);
	}
	bool operator <= (const string& ip_address) const
	{
		return !(*this > IP_Address(ip_address));
	}
	bool operator <= (const char* ip_address) const
	{
		return !(*this > IP_Address(ip_address));
	}
};
//----------------------------------------------------------------------------[] 


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/