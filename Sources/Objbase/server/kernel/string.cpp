/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998-2000 W:Brain Software Inc.                              []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            string.h																	[]
[] Date:            20.04.2000                                                []
[] Author:          Roman V. Koshelev														[]
[] Description:     Класс - строковая переменная
[]____________________________________________________________________________[]
*/

#define	USES_string_h
#include "main.h"

#ifdef WIN32
	#define vsnprintf _vsnprintf
#endif

//______________________________________________________________________________
//                                                                            []
//` win_2_dos                                                                 []         
//                                                                            []
char win_2_dos(char ch)
{
  if((unsigned char)ch>=192 && (unsigned char)ch<=223)
    return (char)((unsigned char)ch-64);
  if((unsigned char)ch>=224 && (unsigned char)ch<=239)
    return (char)((unsigned char)ch-64);
  if((unsigned char)ch>=240 && (unsigned char)ch<=255)
    return (char)((unsigned char)ch-16);
  return ch;
}
//______________________________________________________________________________
//                                                                            []
//` win_2_dos                                                                 []         
//                                                                            []
char * win_2_dos(char* str)
{
   for (int i=0; str[i]; i++)
   {
      str[i] = win_2_dos(str[i]);
   }
   return str;
}
//____________________________________________________________________________[]


//	Конструктор = ""
string::string ()
{
	Init			();
	Alloc			(1);
	m_pData[0]	=0;
}

//	Конструктор (string, const char *, char)
string::string (char from)
{
	Init ();
	if (from==0)
	{
		Copy ("", 0);
	}
	else Copy (&from, sizeof (char));
}

//	Конструктор (string, const char *, char)
string::string (const char* from)
{
	Init ();
	Copy (from, strlen(from));
}

//	Конструктор (string, const char *, char)
string::string (const string& from)
{
	Init ();
	Copy (from.m_pData, from.len());
}

//	Оператор присваивания (string, const char *, char)
string& string::operator= (char from)
{
	return Copy (&from, sizeof (char));
}

//	Оператор присваивания (string, const char *, char)
string& string::operator= (const char* from)
{
	return Copy (from, strlen(from));
}

//	Оператор присваивания (string, const char *, char)
string& string::operator= (const string& from)
{
	Copy (from.m_pData, from.len());
	return *this;
}


//	Копирование другой строки (const char*)
string& string::Copy (const char* from, size_t str_len)
{
	CPtr<char>::Erase ();
	if (from!=NULL)
	{
		Realloc	(str_len+1);
		memcpy	(m_pData, from, str_len);
		m_pData  [str_len] = 0;
	}
	return * this;
}

//	Нахождение подстроки или символа. По умолчанию ищется с самого начала.
// Возвращает позицию или -1, если не найдено.
int string::Find (const char * Substr, int nPos)
{
	if (nPos>(int)Len())
		return -1;
	const char * res = strstr (GetPtr()+nPos, Substr);
	return res? int (res - GetPtr()) : -1;
}

//	Нахождение подстроки или символа. По умолчанию ищется с самого начала.
// Возвращает позицию или -1, если не найдено.
int string::Find (char C, int nPos)
{
	if (nPos>(int)Len())
		return -1;
	char * res = NULL;
	for (res=m_pData+nPos; *res && *res!=C; res++);

	return *res? int (res - m_pData) : -1;
}


// Взять подстроку
void string::SubStr (string& Substr, int nPos1, int nPos2)
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

//	Упаковка из массива. По умолчанию разделяется переходами строк '\n'
void string::implode (CPtr<string>& arr, const char * sDelimiter)
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

//	Разбиение на массив. По умолчанию разбивается на строки '\n'
void string::explode (CPtr<string>& arr, const char * sDelimiter, bool PrintPercent)
{
	int pos1=0;
	int pos2=0;
	int nDelimiter = strlen (sDelimiter);
	bool bExit = false;
	int NN = Len();
	CPtr<char> tmp;
	while (!bExit)
	{
		if (PrintPercent)
		{
			PRINT_PERCENT (pos1, NN);
		}

//		if (nDelimiter==1)
//			pos2 = Find (sDelimiter[0], pos1);
//		else
			pos2 = Find (sDelimiter, pos1);

		if (pos2==-1)
		{
			pos2  = m_nSize;
			bExit = true;
		}
		tmp.Realloc (pos2-pos1+1);
		memcpy (tmp.GetPtr(), m_pData+pos1, pos2-pos1);
		tmp[pos2-pos1] = 0;

		arr.Add (tmp.GetPtr());

		pos1 = pos2 + nDelimiter;
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Добавление																					   []
//                                                                            []

//	Оператор конкатенации строк (const char* или string)
const char * string::operator + (const char * add)
{
	static string tmp_str;
	tmp_str  = *this;
	tmp_str += add;
	return tmp_str.c_str();
}
//	Оператор конкатенации строк (const char* или string)
const char * string::operator + (const string& add)
{
	static string tmp_str;
	tmp_str  = *this;
	tmp_str += add;
	return tmp_str.c_str();
}

//	Добавить строку (const char* или string)
string string::operator+= (const char * add)
{
	return AddString (add, strlen (add));
}

//	Добавить строку (const char* или string)
string& string::operator+= (const string& add)
{
	return AddString (add.m_pData, add.length());
}

//	Добавить символ (char)
string& string::operator+= (char C)
{
	return AddString (&C, sizeof(C));
}

//	Добавить строку (const char*)
string& string::AddString (const char* add, size_t add_len)
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

//	Убрать с конца строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
void string::rtrim ()
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

//	Убрать из начала строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
void string::ltrim ()
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

//	Убрать из начала и с конца строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
void string::trim ()
{
	ltrim ();		  
	rtrim ();		  
}

// Переводит символы строки в верхний регистр.
// Предполагается, что кириллица имеет кодировку Win1251.
void string::strupr(void)
{
	static char str_from		[] = "qwertyuiopasdfghjklzxcvbnmёйцукенгшщзхъфывпаролджэячсимтьбю";
	static char str_to		[] = "QWERTYUIOPASDFGHJKLZXCVBNMЁЙЦУКЕНГШЩЗХЪФЫВПАРОЛДЖЭЯЧСИМТЬБЮ";
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

// Переводит символы строки в нижний регистр.
// Предполагается, что кириллица имеет кодировку Win1251.
void string::strlwr(void)
{
	static char str_from		[] = "QWERTYUIOPASDFGHJKLZXCVBNMЁЙЦУКЕНГШЩЗХЪФЫВПАРОЛДЖЭЯЧСИМТЬБЮ";
	static char str_to		[] = "qwertyuiopasdfghjklzxcvbnmёйцукенгшщзхъфывпаролджэячсимтьбю";
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
//` Сравнение																						[]
//                                                                            []
//	Сравнение на равенство со строкой (const char* или string)
bool string::operator == (const string& to) const
{
	return m_nSize==to.m_nSize && (strcmp (m_pData, to.m_pData)==0);
}

//	Сравнение на равенство со строкой (const char* или string)
bool string::operator == (const char * to) const
{
	return strcmp (m_pData, to)==0;
}


//	Сравнение на неравенство со строкой (const char* или string)
bool string::operator != (const string& to) const
{
	return m_nSize!=to.m_nSize || (strcmp (m_pData, to.m_pData)!=0);
}

//	Сравнение на неравенство со строкой (const char* или string)
bool string::operator != (const char * to) const
{
	return strcmp (m_pData, to)!=0;
}

//	Сравнение на равенство со строкой (const char* или string)
bool string::operator <= (const string& to) const
{
	return strcmp (m_pData, to.m_pData)<=0;
}

//	Сравнение на равенство со строкой (const char* или string)
bool string::operator < (const string& to) const
{
	return strcmp (m_pData, to.m_pData)<0;
}

//	Сравнение на равенство со строкой (const char* или string)
bool string::operator >= (const string& to) const
{
	return strcmp (m_pData, to.m_pData)>=0;
}

//	Сравнение на равенство со строкой (const char* или string)
bool string::operator > (const string& to) const
{
	return strcmp (m_pData, to.m_pData)>0;
}

//____________________________________________________________________________[]



// Очистить строку (="") тоже что и Erase()
void string::Delete()
{
   Copy ("", 0);
}

// Очистить строку (="") тоже что и Delete()
void string::Erase()
{
   Copy ("", 0);
}



//	Вывод строки на экран
void string::Print () const
{
	SERVER_DEBUG_ASSERT (m_pData, "string::Print () -- m_pData=NULL");
	printf (m_pData);
}

// CPtr:: Выделить память и считать в неё 		
// данные из файла OS, открытого по имени.
size_t string::ReadFile(const char *fileName)
{
	FILE *srcFile=fopen(fileName,"rb");
	if (srcFile==NULL)
	{
		SERVER_DEBUG_ERROR_1 ("string::ReadFile Ошибка открытия файла %s", fileName);
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

//	Вывод строки на экран
void string::Println () const
{
	Print();
	printf ("\n");
}

// Заполнить строку в соответствии с форматом и аргументами
// Работает как функция sprintf().
void string::Format (const char * sFormat, ...)
{
	const int MAX_SSS_SIZE=102400;
	static char SSS [MAX_SSS_SIZE];
	va_list argList;
	va_start(argList, sFormat);
		vsnprintf (SSS, MAX_SSS_SIZE-1, sFormat, argList);
	va_end(argList);
	Copy (SSS, strlen(SSS));
}

// Преобразовать строку в DOS-кодировку
string& string::win_2_dos ()
{
	::win_2_dos (m_pData);
	return *this;
}

// Сгенерировать случайную строку указанной длины на основе заданного алфавита.
// Если bRandomLen==true, то длина строки выбирается случайным образом в пределах от 0 до strLen.
void string::Randomize (int strLen, const char *alfabet, bool bRandomLen)
{
	static const int	MAX_SSS_LEN = 10240;
	static char SSS	[MAX_SSS_LEN];
	
	strLen = min (MAX_SSS_LEN-1, strLen);
	
	int N = strlen (alfabet);

	for (int i=0; i<(int)strLen; i++)
	{
		int r		= rand()%N;
		SSS[i]	= alfabet[r];
		SSS[i+1] = 0;
	}
	if (bRandomLen)
	{
		SSS[rand()%strLen] = 0;
	}

	*this=SSS;
}


//	Получить 32-х разрядную свёртку от строки.
unsigned long string::GetCRC (void) const
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
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Выдать значение предусмотренного типа                                     []                                     
//                                                                            []
void string::GetVariant (identifier& val)
{
	DEBUG_STACK_NAME (GetVariant_identifier);
	(void) val;
	SERVER_DEBUG_ERROR ("Функция не реализована");
}
//----------------------------------------------------------------------------[] 
void string::GetVariant (int& val)
{
	DEBUG_STACK_NAME (GetVariant_int);
	char SSS [1024];
	memcpy (SSS, m_pData, 128);
	SSS [128]=0;
	sscanf (SSS, "%d", &val);
}
//----------------------------------------------------------------------------[] 
void string::GetVariant (char& val)
{
	DEBUG_STACK_NAME (GetVariant_char);
	(void) val;
	SERVER_DEBUG_ERROR ("Функция не реализована");
}
//----------------------------------------------------------------------------[] 
void string::GetVariant (float& val)
{
	DEBUG_STACK_NAME (GetVariant_float);
	(void) val;
	SERVER_DEBUG_ERROR ("Функция не реализована");
}
//----------------------------------------------------------------------------[] 
void string::GetVariant (string& val)
{
	DEBUG_STACK_NAME (GetVariant_string);
	(void) val;
	SERVER_DEBUG_ERROR ("Функция не реализована");
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Проверить, является ли строка построенной по правилам                     []
//  образования имен переменных С++                                           []
bool string::CheckSysName (void) const
{
	const char * SysName = GetPtr();
	char C = SysName[0];
	if ('a'<=C&&C<='z' || 'A'<=C&&C<='Z' || C=='_')
	{
		for (int i=1; i<256 && SysName[i]; i++)
		{
			if (!('a'<=C&&C<='z' || 'A'<=C&&C<='Z' || '0'<=C&&C<='9' || C=='_'))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}	
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Helpers																							[]
//                                                                            []
bool operator == (const char * str1, string& str2)
{
	return str2==str1;
}

bool operator != (const char * str1, string& str2)
{
	return str2!=str1;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/