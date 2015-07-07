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
	public: string ()
	{
		Init			();
		Alloc			(1);
		m_pData[0]	=0;
	}

//	����������� (string, const char *, char)
	public: string (char from)
	{
		Init ();
		if (from==0)
		{
			Copy ("", 0);
		}
		else Copy (&from, sizeof (char));
	}

//	����������� (string, const char *, char)
	public: string (const char* from)
	{
		Init ();
		Copy (from, strlen(from));
	}

//	����������� (string, const char *, char)
	public: string (const string& from)
	{
		Init ();
		Copy (from.m_pData, from.len());
	}

//	�������� ������������ (string, const char *, char)
	public: string& operator = (char from)
	{
		return Copy (&from, sizeof (char));
	}

//	�������� ������������ (string, const char *, char)
	public: string& operator = (const char* from)
	{
		return Copy (from, strlen(from));
	}

//	�������� ������������ (string, const char *, char)
	public: string& operator = (const string& from)
	{
		Copy (from.m_pData, from.len());
		return *this;
	}


//	����������� ������ ������ (const char*)
	public: string& Copy (const char* from, size_t str_len)
	{
		CPtr<char>::Delete ();
		if (from!=NULL)
		{
			Alloc		(str_len+1);
			memcpy	(m_pData, from, str_len);
			m_pData  [str_len] = 0;
		}
		return * this;
	}

//	���������� ���������. �� ��������� ������ � ������ ������.
// ���������� ������� ��� -1, ���� �� �������.
	public: int Find (const char * Substr, int nPos=0)
	{
		if (nPos>(int)Len())
			return -1;
		const char * res = strstr (GetPtr()+nPos, Substr);
		return res? int (res - GetPtr()) : -1;
	}

// ����� ���������
	public: void SubStr (string& Substr, int nPos1=0, int nPos2=-1)
	{
		if (nPos2<0)
			nPos2 = strlen (m_pData);
		int i,j;
		char * pTmp = new char [nPos2-nPos1+1];
		pTmp[0] = 0;
		for (j=0,i=nPos1; i<nPos2 && m_pData[i]; i++,j++)
		{
			pTmp[j  ] = m_pData[i];
			pTmp[j+1] = 0;
		}
		Substr = pTmp;
		delete [] pTmp;
	}

//	�������� �� �������. �� ��������� ����������� ���������� ����� '\n'
	public: void implode (CPtr<string>& arr, const char * sDelimiter="\n")
	{
		Copy ("", 0);
		int nDelimiter = strlen (sDelimiter);

		for (int i=0; i<arr.Size(); i++)
		{
			if (i!=0)
			{
				AddString (sDelimiter, nDelimiter);
			}
			AddString (arr[i].GetPtr(), arr[i].Len());
		}
	}

//	��������� �� ������. �� ��������� ����������� �� ������ '\n'
	public: void explode (CPtr<string>& arr, const char * sDelimiter="\n")
	{
		int pos1=0;
		int pos2=0;
		int nDelimiter = strlen (sDelimiter);
		bool bExit = false;
		while (!bExit)
		{
			pos2 = Find (sDelimiter, pos1);
			if (pos2==-1)
			{
				pos2  = m_nSize;
				bExit = true;
			}
			char * tmp = new char [pos2-pos1+1];
			memcpy (tmp, m_pData+pos1, pos2-pos1);
			tmp[pos2-pos1] = 0;
			arr += string (tmp);
			delete [] tmp;
			pos1 = pos2 + nDelimiter;
		}
	}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ����������																					   []
//                                                                            []

//	�������� ������������ ����� (const char* ��� string)
	public: const char * operator + (const char * add)
	{
/*!!!+*/		static string tmp_str;
		tmp_str  = *this;
		tmp_str += add;
		return tmp_str.c_str();
	}
//	�������� ������������ ����� (const char* ��� string)
	public: const char * operator + (const string& add)
	{
/*!!!+*/		static string tmp_str;
		tmp_str  = *this;
		tmp_str += add;
		return tmp_str.c_str();
	}

//	�������� ������ (const char* ��� string)
	public: string operator += (const char * add)
	{
		return AddString (add, strlen (add));
	}

//	�������� ������ (const char* ��� string)
	public: string& operator += (const string& add)
	{
		return AddString (add.m_pData, add.length());
	}

//	�������� ������ (char)
	public: string& operator += (char C)
	{
		return AddString (&C, sizeof(C));
	}

//	�������� ������ (const char*)
	public: string& AddString (const char* add, size_t add_len)
	{
		if (add_len)
		{
			bool bSelf = add==m_pData;
			size_t oldSize = m_nSize;
			Realloc (m_nSize + add_len);
			memcpy (m_pData+oldSize-1, (bSelf? m_pData: add), add_len);
			m_pData [m_nSize-1] = 0;
		}
		return *this;
	}

//	������ � ����� ������ ������ �������:
// ������ ��������� \r \n
	public: void rtrim ()
	{
		CPtr <char> tmp;
		tmp.CopyFrom (CPtr<char>::GetPtr(), CPtr<char>::Size());

		for (int i=tmp.Size()-1; i>=0; i--)
		{
			char C = tmp[i];
			if ((C=='\t') || (C=='\r') || (C=='\n') || (C==' ') || (C=='\r') || (C==0))
			{
				tmp[i] = 0;
			}
			else break;
		}
		Copy (tmp.GetPtr(), strlen (tmp.GetPtr()));
	}

//	������ �� ������ ������ ������ �������:
// ������ ��������� \r \n
	public: void ltrim ()
	{
		CPtr <char> tmp;
		tmp.CopyFrom (CPtr<char>::GetPtr(), CPtr<char>::Size());

		int i=0;
		for (i=0; i<tmp.Size()-1; i++)
		{
			char C = tmp[i];
			if ((C=='\t') || (C=='\r') || (C=='\n') || (C==' ') || (C=='\r'))
			{
				continue;
			}
			else break;
		}
		Copy (tmp.GetPtr()+i, strlen (tmp.GetPtr()+i));
	}

//	������ �� ������ � � ����� ������ ������ �������:
// ������ ��������� \r \n
	public: void trim ()
	{
		ltrim ();		  
		rtrim ();		  
	}

// ��������� ������� ������ � ������� �������.
// ��������������, ��� ��������� ����� ��������� Win1251.
	public: void strupr(void)
	{
		static char str_from		[] = "qwertyuiopasdfghjklzxcvbnm���������������������������������";
		static char str_to		[] = "QWERTYUIOPASDFGHJKLZXCVBNM���������������������������������";
		static char RESULT		[256];
		static bool bNeedCalc = true;

		size_t i;

		if (bNeedCalc)
		{
			for (i=0;i<256;i++)
			{
				RESULT [i] = (byte)i;
			}
			for (i=0; str_from[i]; i++)
			{
				RESULT [(byte)(str_from[i])] = str_to[i];
			}
			bNeedCalc = false;
		}

		for (i=0; i<m_nSize; i++)
		{
			m_pData[i] = RESULT [(byte)(m_pData[i])];
		}
	}
// ��������� ������� ������ � ������ �������.
// ��������������, ��� ��������� ����� ��������� Win1251.
	public: void strlwr(void)
	{
		static char str_from		[] = "QWERTYUIOPASDFGHJKLZXCVBNM���������������������������������";
		static char str_to		[] = "qwertyuiopasdfghjklzxcvbnm���������������������������������";
		static char RESULT		[256];
		static bool bNeedCalc = true;

		size_t i;

		if (bNeedCalc)
		{
			for (i=0;i<256;i++)
			{
				RESULT [i]=(byte)i;
			}
			for (i=0; str_from[i]; i++)
			{
				RESULT [(byte)(str_from[i])] = str_to[i];
			}
			bNeedCalc = false;
		}

		for (i=0; i<m_nSize; i++)
		{
			m_pData[i] = RESULT [(byte)(m_pData[i])];
		}
	}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ���������																						[]
//                                                                            []
//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator == (const string& to) const
	{
		return m_nSize==to.m_nSize && (strcmp (m_pData, to.m_pData)==0);
	}

//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator == (const char * to) const
	{
		return strcmp (m_pData, to)==0;
	}


//	��������� �� ����������� �� ������� (const char* ��� string)
	public: bool operator != (const string& to) const
	{
		return m_nSize!=to.m_nSize || (strcmp (m_pData, to.m_pData)!=0);
	}

//	��������� �� ����������� �� ������� (const char* ��� string)
	public: bool operator != (const char * to) const
	{
		return strcmp (m_pData, to)!=0;
	}

//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator <= (const string& to) const
	{
		return strcmp (m_pData, to.m_pData)<=0;
	}

//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator < (const string& to) const
	{
		return strcmp (m_pData, to.m_pData)<0;
	}

//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator >= (const string& to) const
	{
		return strcmp (m_pData, to.m_pData)>=0;
	}

//	��������� �� ��������� �� ������� (const char* ��� string)
	public: bool operator > (const string& to) const
	{
		return strcmp (m_pData, to.m_pData)>0;
	}

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
//____________________________________________________________________________[]


// �������� ������ (="") ���� ��� � Erase()
   public:  void Delete()
   {
      Copy ("", 0);
   }

// �������� ������ (="") ���� ��� � Delete()
   public:  void Erase()
   {
      Copy ("", 0);
   }


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
	void Print () const
	{
		SERVER_DEBUG_ASSERT (m_pData, "string::Print () -- m_pData=NULL");
		printf (m_pData);
	}

// CPtr:: �������� ������ � ������� � �� 		
// ������ �� ����� OS, ��������� �� �����.
	public:	size_t ReadFile(const char *fileName)
	{
		FILE *srcFile=fopen(fileName,"rb");
		if (srcFile==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("string::ReadFile ������ �������� ����� %s", fileName);
			return 0;
		}
		fseek(srcFile,0,SEEK_END);
		long nSrcLength=ftell(srcFile);
		fseek(srcFile,0,SEEK_SET);
		Alloc(nSrcLength+1+1);
		fread(m_pData,nSrcLength,1,srcFile);
		fclose(srcFile);
		m_pData[nSrcLength]=0;
		return nSrcLength;
	}

//	����� ������ �� �����
	void Println () const
	{
		Print();
		printf ("\n");
	}

// ��������� ������ � ������������ � �������� � �����������
// �������� ��� ������� sprintf().
	void Format (const char * sFormat, ...)
	{
		static char SSS [102400];
		va_list argList;
		va_start(argList, sFormat);
			vsprintf (SSS, sFormat, argList);
		va_end(argList);
		Copy (SSS, strlen(SSS));
	}

//	�������� 32-� ��������� ������ �� ������.
	public: unsigned long GetCRC (void) const
	{
		static const unsigned long CRC_32_TAB[] = 
		{
			0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
			0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
			0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
			0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
			0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,	0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
			0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
			0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
			0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
			0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
			0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,	0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
			0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
			0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
			0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
			0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,	0xaa0a4c5fL, 0xdd0d7cc9L,
			0x5005713cL, 0x270241aaL, 0xbe0b1010L,	0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
			0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
			0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
			0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L, 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
			0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,	0x196c3671L, 0x6e6b06e7L,
			0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,	0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
			0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
			0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
			0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
			0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,	0x2cd99e8bL, 0x5bdeae1dL,
			0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,	0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
			0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
			0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
			0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
			0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,	0x4969474dL, 0x3e6e77dbL,
			0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,	0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
			0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
			0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
		};

		unsigned long 	curr_crc = 0xffffffffL;
		for (size_t i=0; m_pData[i] && i<m_nSize; i++)
		{
			curr_crc = CRC_32_TAB[byte(curr_crc ^ m_pData[i])] ^ (curr_crc >> 8);
		}
		return curr_crc ^ 0xffffffffL;
	}
};
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Helpers																							[]
//                                                                            []
inline bool operator == (const char * str1, string& str2)
{
	return str2==str1;
}

inline bool operator != (const char * str1, string& str2)
{
	return str2!=str1;
}
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/