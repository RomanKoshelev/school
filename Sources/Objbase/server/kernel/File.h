/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            File.h																		[]
[] Date:            02/03/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     File controller for file driver									[]
[]____________________________________________________________________________[]
*/
#ifndef File_H
#define File_H



void ENCODE_STRING (size_t size, char * str);
void DECODE_STRING (size_t size, char * str);

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CFile
[]                                                                            []
[]____________________________________________________________________________[]
*/

// ������ ��� ���������� ���������� �������� ��������.
class CFile : public CPtr<byte>
{
// ����� CFile ��������� ������� ��� ���������� 
// ������� ���������� �������� ��������.
// ������� ������ ����� ������������� ���������� 
// �������������. ���� ����� ������� �� ����� CPtr:
// class CFile: public CPtr<byte>
// ��� ��� � ������� ���� CFile ����� ���������� ��� � �������,
// ����� � ���� ��������� ������.
// � ����� STATIC_FILE_ID.h ����� ��������������� ���������-��������������
// ��� ������ ������������ ���������� (��������, ini-����)
	protected: void About_class_CFile (){};

// ���������� ������������� �����
	protected: identifier	m_nID;
// �������� ��� ��������� ������ � ������
	protected: size_t			m_nOffset;

public:
// ����������� �� ���������. ������ ������ ������������ -- ���� ������� �������
	CFile ()
	{
		m_nID=UNKNOWN;
		m_nOffset=0;
	}

// ����������� -- ��������� ����
	CFile (identifier nID)
	{
		m_nID=UNKNOWN;
		m_nOffset=0;
		Open(nID);
	}


// ������� ����
	CFile& operator = (identifier nID)
	{
		Open(nID);
		return *this;
	}

// ���������� -- ��������� ���� � ��������� ������ ������ ��������.
	~CFile()
	{
		if(m_nID!=UNKNOWN)
			Close();
	}

// �������� ������������� ����� � ��������� ���������������. ����������� �������.
	static bool	Exist(identifier nID)
	{
		return FD.Exist(nID);
	}

// �������� ����������� ������������� ������� ��� �����
	bool IsValid() 
	{
		DEBUG_STACK_NAME (IsValid);

		return (m_nID!=UNKNOWN) && Exist(m_nID);
	}

// ������� ����� ���� � ������� ���
// ���������� ������������� ���������� �����.
	identifier CreateOpen()
	{
		DEBUG_STACK_NAME (CreateOpen);

		if (IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("CreateOpen: ���� %d ��� ������", m_nID);
			return m_nID;
		}

		m_nOffset=0;
		Open (CreateNewFile());

		return m_nID;
	}

// ������ ������� ����� ����. ����������� �������.
// ���������� ������������� ���������� �����.
	static identifier CreateNewFile()
	{
		DEBUG_STACK_NAME (CreateNewFile);

		return FD.CreateNewFile ();
	}

// ������� ������������ ���� �� ���� �� 
// �������������� (���� �� �� ������). ����������� �������.
	static void DeleteFile (identifier nID)
	{
		DEBUG_STACK_NAME (DeleteFile);

		FD.Delete (nID);
	}

// ������� ���� �� ���� � �������������� ������
	void Delete()
	{
		DEBUG_STACK_NAME (Delete);

		FD.Delete(m_nID);
		m_nID=UNKNOWN;
	}

// ������� ���� � ��������� � ���� ������ ������ ��������
	void Open(identifier nID)
	{
		DEBUG_STACK_NAME (Open);

		if (IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("Open: ���� %d ��� ������", m_nID);
			return;
		}
		m_nID=nID;
		m_nOffset=0;
		FD.Lock(m_nID);
	}

// ������� ���� � ��������� � ���� ������ ������ ��������
	void Close()
	{
		DEBUG_STACK_NAME (Close);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("Close: ������� �������� ������������� ����� %d", m_nID);
			return;
		}
		FD.Unlock(m_nID);
		m_nID=UNKNOWN;
	}

// �������� ������������� �����
	identifier GetID()
	{
		DEBUG_STACK_NAME (GetID);

		return m_nID;
	}

// 1. �������� ������ � ��������� � �� ���� ������� -- ������ ��� � CPtr<byte>
// 2. ��������� �� ����� ��� ������ � ����� ���������. �������� �������� � ������.
	void Load()
	{
		DEBUG_STACK_NAME (Load);

		int nSize = GetMaxSize();
		Alloc(nSize+1);
		FD.Read(m_nID,m_pData,nSize);
		m_nOffset=0;
	}

// 1. �������� ������ � ��������� � �� ���� ������� -- ������ ��� � CPtr<byte>
// 2. ��������� �� ����� ��� ������ � ����� ���������. �������� �������� � ������.
	void Load(void *pData)
	{
		DEBUG_STACK_NAME (Load);

		FD.Read(m_nID,pData,GetMaxSize());
		m_nOffset=0;
	}

// 1. ��������� ���� ������� -- ��� ��� ������ CPtr<byte>. �������� �������� � ������.
// 2. �������� ������ ������ �� ������ ���������. �������� �������������.
	void Save()
	{
		DEBUG_STACK_NAME (Save);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Save: ������� ���������� ������������� �����");
			return;
		}
		if (m_pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Save: ���� %d -- ������ ���������. ������ �� ��������.", m_nID);
			return;			
		}
		FD.Write(m_nID,m_pData,m_nSize);
		m_nOffset=0;
	}

// 1. ��������� ���� ������� -- ��� ��� ������ CPtr<byte>. �������� �������� � ������.
// 2. �������� ������ ������ �� ������ ���������. �������� �������������.
	void Save(void *pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Save);

		FD.Write(m_nID,pData,nSize);
	}

// �������� �������� ������������ ������� (SEEK_SET, SEEK_CUR, SEEK_END)
	size_t Seek(int nOffset, int nWhere=SEEK_SET)
	{
		DEBUG_STACK_NAME (Seek);

		if(nWhere==SEEK_SET)
			m_nOffset=0;
		if (((int)m_nOffset+nOffset)<0)
		{
			SERVER_DEBUG_ERROR_2 ("Seek: ���� %d -- ����� �� ������ �����. offset = %d", m_nID, (int)m_nOffset+nOffset);
			return 0;
		}
		m_nOffset+=nOffset;
		return m_nOffset;
	}

// ������ ��������
	size_t Tell()
	{
		DEBUG_STACK_NAME (Tell);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Tell: ������������ ����.");
			return 0;
		}
		return m_nOffset;
	}

// 1. ������� ������ ������ �� ���������� ���������. ������ ����������, �������� �������������.
// 2. ������� ������ ������ �� ������ ���������. �������� �������������.
	void Read(size_t nSize)
	{
		DEBUG_STACK_NAME (Read);

		Alloc(nSize+1);
		Read(m_pData,nSize);
	}

// 1. ������� ������ ������ �� ���������� ���������. ������ ����������, �������� �������������.
// 2. ������� ������ ������ �� ������ ���������. �������� �������������.
	void Read(void * pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Read);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Read: ������������ ����.");
			return;
		}
		if (pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Read: ���� %d -- ������ ��� ������ �� ��������.", m_nID);
			return;
		}
		FD.ReadBlock(m_nID,pData,m_nOffset,nSize);
		m_nOffset += nSize;
	}


// 1. �������� ��� ������, ���������� � ������. �������� �������� �� ������.
// 2. �������� ������ ������ �� ������ ���������. �������� �������������.
	void Write()
	{
		DEBUG_STACK_NAME (Write);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: ������������ ����.");
			return;
		}
		if (m_pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Write: ���� %d -- ������� ���������� �������������� ���������� ������.", m_nID);
			return;
		}
		Write(m_pData,m_nSize);
		m_nOffset = 0;
	}

// 1. �������� ��� ������, ���������� � ������. �������� �������� �� ������.
// 2. �������� ������ ������ �� ������ ���������. �������� �������������.
	void Write(void * pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Write);

		if (nSize==0)
		{
			return;
		}
		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: ������������ ����.");
			return;
		}
		if (pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Write: ���� %d -- ������ ��� ������ �� ��������.", m_nID);
			return;
		}
		FD.WriteBlock(m_nID,pData,m_nOffset,nSize);
		m_nOffset += nSize;
	}

// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (size_t			data)		{Write (&data, sizeof (size_t));}
// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (int				data)		{Write (&data, sizeof (data));}
// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (bool				data)		{Write (&data, sizeof (data));}
// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (char				data)		{Write (&data, sizeof (data));}
// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (float			data)		{Write (&data, sizeof (data));}
// �������� �������������� ������ (int, bool, ..., identifier). �������� �������������.
	void WriteData (identifier		data)		{Write (&data, sizeof (data));}


// �������� ����� ������. �������� �������������.
	void WriteData (int size, const char * str)
	{
		DEBUG_STACK_NAME (WriteData);

		WriteData (size);
		Write ((void*)str, size);
	}

// �������� ��� ������. �������� �������������.
	void WriteData (const char * str)
	{
		DEBUG_STACK_NAME (WriteData);

		WriteData (strlen (str)+1, str);
	}

// �������� � ������������ "string". �������� �������������.
	void WriteData (string& str)
	{
		DEBUG_STACK_NAME (WriteData);

		int size = str.size()+1;
		char * tmp = new char [size];
		memcpy (tmp, str.c_str(), size);

		ENCODE_STRING (size, tmp);

		WriteData (size, tmp);

		delete [] tmp;
	}

//	�������� ������ �� CPtr<TYPE> �������� �������������.
// ��������: class TYPE ������ �� ��������� ����������,
// �� ����� ����������� ������� � ������������.
	public: void WriteData (CPtr_info pi)
	{
		DEBUG_STACK_NAME (WriteData);

		size_t   nSize = (*(pi.p_size)) * pi.item_size;
		void   * pData = *(pi.p_ptr);
		WriteData	(nSize);
		Write			(pData, nSize);
	}

//	������� ������ � CPtr<TYPE> �������� �������������.
// ��������: class TYPE ������ �� ��������� ����������,
// �� ����� ����������� ������� � ������������.
// ����������� ������ ������ ���� ������ -- ������ CPtr::Erase
	public: void ReadData (CPtr_info pi)
	{
		DEBUG_STACK_NAME (ReadData);

		if (*pi.p_ptr)
		{
			SERVER_DEBUG_ERROR ("ReadData: ����������� ������ ������ CPtr ��� ������ ������");
			return;
		}

		size_t   nSize;
		void   * pData;
		ReadData	(nSize);
		pData = new byte [nSize];
		Read		(pData, nSize);
		*(pi.p_size)		= nSize / pi.item_size;
		*(pi.p_real_size) = nSize / pi.item_size;
		*(pi.p_ptr)			= pData;
	}

// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (size_t&			data)		{Read (&data, sizeof (size_t));}
// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (int&				data)		{Read (&data, sizeof (data));}
// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (bool&				data)		{Read (&data, sizeof (data));}
// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (char&				data)		{Read (&data, sizeof (data));}
// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (float&			data)		{Read (&data, sizeof (data));}
// ������� �������������� ������ �� ������ (int, bool, ..., identifier). �������� �������������.
	void ReadData (identifier&		data)		{Read (&data, sizeof (data));}

// ������� � ������������� "string". �������� �������������.
	void ReadData (string& str)
	{
		DEBUG_STACK_NAME (ReadData);

		int size=0;
		ReadData (size);
		char * tmp = new char [size];
		Read (tmp,  size);
		
		DECODE_STRING (size, tmp);

		str = tmp;
		delete [] tmp;
	}


// ������ ������������ ������, ������� �������� ���� (�������).
	size_t GetMaxSize()
	{
		DEBUG_STACK_NAME (GetMaxSize);

		return FD.GetMaxSize(m_nID);
	}

// ������ ������������ ������, ������� �������� ���� � ��������� ���������������.
	static size_t GetMaxSize(identifier nID)
	{
		DEBUG_STACK_NAME (GetMaxSize);

		return FD.GetMaxSize(nID);
	}

// ��������� ����� ����� ������. ������ ��������������. �������� �������� �� ������
// NOTE: ������ �� ����� ���� ������ ����!
	void SetSize(size_t nSize)
	{
		DEBUG_STACK_NAME (SetSize);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: ������������ ����.");
			return;
		}
		Realloc(nSize);
		FD.SetSize(m_nID,nSize);
		m_nOffset = 0;
	}
};
#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/