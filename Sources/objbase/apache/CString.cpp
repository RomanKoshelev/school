// HomeLabs Software. 1999-2000
// Dima Poliakov'2000

// NOT A PUBLIC CODE
// Please do not destribute it

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "CString.h"

char *russian_font_ = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

String::String(void)
{
	m_Data = NULL;
	data_len = 0;
}

String::String( const char *src )
{
	data_len = 0;
	if(src != NULL)
	{
		int Len = strlen(src);
		if(Len > 0)
		{
			m_Data = (char*) malloc(Len+1);
			strcpy(m_Data, src);
			data_len = Len;
		}
		else
		{
			m_Data = NULL;
		}
	}
	else m_Data = NULL;
}

String::String(const String &src)
{
	data_len = 0;
	int Len = src.GetLength();
	if(Len > 0)
	{
		m_Data = (char *) malloc(Len+1);
		strcpy(m_Data, src.m_Data);
		data_len = Len;
	}
	else
	{
		m_Data = NULL;
	}
}

String::String( long src )
{
	char buf[32];
	ltoa(src, buf, 10);
	int Len = strlen(buf);
	m_Data = (char *) malloc(Len+1);
	strcpy(m_Data, buf);
	data_len = Len;
}

String::String( unsigned long src )
{
	char buf[32];
	ultoa( src, buf, 10 );
	int Len = strlen(buf);
	m_Data = (char *) malloc(Len+1);
	strcpy( m_Data, buf );
	data_len = Len;
}

String::String( int src )
{
	char buf[32];
	itoa( src, buf, 10 );
	int Len = strlen(buf);
	m_Data = (char *) malloc(Len+1);
	strcpy( m_Data, buf );
	data_len = Len;
}

String::String( unsigned int src )
{
	char buf[32];
	ultoa( (unsigned long)src, buf, 10 );
	int Len = strlen(buf);
	m_Data = (char *) malloc(Len+1);
	strcpy( m_Data, buf );
	data_len = Len;
}

String::String( char src )
{
	m_Data = (char *) malloc(2);
	m_Data[0] = src;
	m_Data[1] = '\0';
	data_len = 1;
}

String::~String( )
{
	if(m_Data) free(m_Data);
	data_len = 0;
}

String String::operator=( const String &rhs )
{
	data_len = 0;
	int Len = rhs.GetLength();
	if( Len > 0 )
	{
		if( m_Data )
			m_Data = (char *) realloc( m_Data, Len+1 );
		else
			m_Data = (char *) malloc( Len+1 );
		strcpy( m_Data, rhs.m_Data );
		data_len = Len;
	}
	else
	{
		if( m_Data )
		{
			free( m_Data );
			m_Data = NULL;
		}
	}
	return *this;
}

String operator+(const char *lhs, const String &rhs)
{
	String result;
	int Len = strlen(lhs)+rhs.GetLength();
	if( Len > 0 )
	{
		result.m_Data = (char *) malloc(Len+1);
		strcpy( result.m_Data, lhs );
		if( !rhs.IsEmpty() ) strcat( result.m_Data, rhs.m_Data );
		result.data_len = Len;
	}
	return result;
}

String String::operator+( const String &rhs ) const
{
	String result;
	int Len = GetLength()+rhs.GetLength();
	if( Len > 0 )
	{
		result.m_Data = (char *) malloc(Len+1);
		if( !IsEmpty() ) strcpy( result.m_Data, m_Data );
		else *(result.m_Data) = '\0';
		if( !rhs.IsEmpty() ) strcat( result.m_Data, rhs.m_Data );
		result.data_len = Len;
	}
	return result;
}

String String::operator+=( const String &rhs )
{
	if( rhs.GetLength() != 0 )
	{
		int OldLength = GetLength();
		SetLength( OldLength+rhs.GetLength() );
		strcpy( m_Data+OldLength, rhs.m_Data );
	}
	return *this;
}

bool String::operator==( const String &rhs )
{
	if( !IsEmpty() && !rhs.IsEmpty() )
	{
		return( strcmp_(m_Data,rhs.m_Data) == 0 );
	}
	if( IsEmpty() && rhs.IsEmpty() ) return true;
	return false;
}

bool String::operator!=( const String &rhs ) const
{
	if(!IsEmpty() && !rhs.IsEmpty()) return (strcmp(m_Data,rhs.m_Data)!= 0);
	if(IsEmpty() && rhs.IsEmpty()) return false;
	return true;
}

bool String::operator<( const String &rhs ) const
{
	if( !IsEmpty() && !rhs.IsEmpty() ) return( strcmp(m_Data,rhs.m_Data) < 0 );
	if( IsEmpty() && !rhs.IsEmpty() ) return true;
	return false;
}

bool String::operator>( const String &rhs ) const
{
	if( !IsEmpty() && !rhs.IsEmpty() ) return( strcmp(m_Data,rhs.m_Data) > 0 );
	if( !IsEmpty() && rhs.IsEmpty() ) return true;
	return false;
}

bool String::operator<=( const String &rhs ) const
{
	if( !IsEmpty() && !rhs.IsEmpty() ) return( strcmp(m_Data,rhs.m_Data) <= 0 );
	if( !IsEmpty() && rhs.IsEmpty() ) return false;
	return true;
}

bool String::operator>=( const String &rhs ) const
{
	if( !IsEmpty() && !rhs.IsEmpty() ) return( strcmp(m_Data,rhs.m_Data) >= 0 );
	if( IsEmpty() && !rhs.IsEmpty() ) return false;
	return true;
}

char &String::operator[]( int index )
{
	if( index >= GetLength() ) index = GetLength()-1;
	return m_Data[index];
}

char String::GetChar( int index )
{
	if( index >= GetLength() ) index = GetLength()-1;
	return m_Data[index];
}

char *String::c_str( void ) const
{
	if( m_Data ) return m_Data;
	return "";
}

// get length of string [standart version - used strlen(...)]
int String::Length( void ) const
{
	if( m_Data )
		return strlen( m_Data );
	return 0;
}

// get length of string (fast version)
int String::GetLength( void ) const
{
	return data_len;
}

// check if empty
bool String::IsEmpty( void ) const
{
	if( m_Data == NULL ) return true;
	return false;
}

// set a new length of string
void String::SetLength( int Len )
{
	int OldLength = this->GetLength();
	if( Len!=OldLength )
	{
		if( Len == 0 )
		{
			if( m_Data )
			{
				free(m_Data);
				m_Data = NULL;
				data_len = 0;
			}
		}
		else
		{
			if( m_Data ) m_Data = (char *) realloc( m_Data, Len+1 );
			else m_Data = (char *) malloc( Len+1 );
			if( Len > OldLength)
			{
//				strnset( m_Data+OldLength, ' ', Len-OldLength );
				// it'll work more finest
				memset(&m_Data[OldLength], ' ', Len - OldLength);
			}
			m_Data[Len] = '\0';
			data_len = Len;
		}
	}
}

// delete some chars
void String::Delete( int Index, int Len )
{
	if( !m_Data ) return;
	if( Len < 1 ) return;
	int myLength = GetLength();
	if( (Index < 0) || (Index >= myLength) || (Index+Len > myLength)) return;
	if( Index == 0 && Len == myLength )
	{
		free(m_Data);
		m_Data = NULL;
		data_len = 0;
	}
	else
	{
		memmove( m_Data+Index, m_Data+Index+Len, myLength - Index - Len + 1 );
		data_len-=Len;
	}
}

// insert string
void String::Insert( int Index, const String &String )
{
	int StringLen = String.GetLength();
	int MyLength = GetLength();
	if( StringLen == 0 ) return;
	if( Index < 0 || Index >= MyLength ) return;
	SetLength( MyLength + StringLen );
	memmove( m_Data+Index+StringLen, m_Data+Index, MyLength - Index );
	memmove( m_Data+Index, String.c_str(), StringLen );
}

String String::LowerCase( void )
{
	String result( *this );
	if( !result.IsEmpty() ) strlwr_( result.m_Data );
	return result;
}

String String::UpperCase( void )
{
	String result( *this );
	if( !result.IsEmpty() ) strupr_( result.m_Data );
	return result;
}

// WARNING: Unchecked function
String String::SubString( int Start, int Len ) const
{
	String result;
	if( GetLength() >= Start )
	{
		result = *this;
		int BytesToMove = GetLength()+1-Start;	 /* 1 */
		if( Len < BytesToMove ) BytesToMove = Len;
		BytesToMove++;
		memmove( result.m_Data, result.m_Data+Start-1, BytesToMove );
		result.SetLength( BytesToMove-1 );
	}
	return result;
}

// WARNING: Unchecked function
int String::Pos( const String &SubStr ) const
{
	int result;
	if( m_Data && SubStr.m_Data )
	{
		char *p = strstr( m_Data, SubStr.m_Data );
		if( p ) result = p - m_Data;
		else result = 0;
	}
	else result = 0;
	return result;
}

char String::LastChar( void ) const
{
	if( IsEmpty() ) return '\0';
	return m_Data[strlen(m_Data)-1];
}

// int stricmp(char *str1, char *str2)
// сравнение строк без различения регистра
// Возвращает:
// 0, если str1 equal str2
// < 0, если str1 < str2
// > 0, если str1 > str2
int String::stricmp_(const char *str1, const char *str2)
{
	char f, l;
	do {
       f = tolower_( (unsigned char)(*(str1++)) );
       l = tolower_( (unsigned char)(*(str2++)) );
   } while ( f && l && (f == l) );
	
	return(f - l);
}

// int strcmp(char *str1, char *str2)
// сравнение строк c различением регистра
// Возвращает:
// 0, если str1 equal str2
// < 0, если str1 < str2
// > 0, если str1 > str2
int String::strcmp_(const char *str1, const char *str2)
{
	while((str1[0]==str2[0]) && *str1 && *str2)
	{
		str1++;
		str2++;
	}

	return ((unsigned char)(*str1) - (unsigned char)(*str2));
}

// bool strupr(char *src)
// конвертирование символов в верхний регистр
char *String::strupr_(char *src)
{
	char *p=src;

	for (p = src; *p; ++p)
	{
		if ('a' <= *p && *p <= 'z')
			*p += 'A' - 'a';
		else
		{
			if ((unsigned char) (*p) > 'z')
			{
				// проверка на русский шрифт
				char *rus = strchr(russian_font_, *p);
				if( rus - russian_font_ >= 33)
				{
					char c = russian_font_[rus - russian_font_ - 33];
					*p=c;
				}
			}
		}
	}
	return src;
}

// bool strlwr(char *src)
// конвертирование символов в нижний регистр
char *String::strlwr_(char *src)
{
	char *p=src;

	for (p = src; *p; ++p)
	{
		if ('A' <= *p && *p <= 'Z')
			*p += 'a' - 'A';
		else
		{
			if ((unsigned char) (*p) > 'z')
			{
				// проверка на русский шрифт
				char *rus = strchr(russian_font_, *p);
				if( rus - russian_font_ < 33)
				{
					char c = russian_font_[rus - russian_font_ + 33];
					*p=c;
				}
			}
		}
	}
	return src;
}

// char toupper(char *src)
// конвертирование символа в верхний регистр
char String::toupper_(char c)
{
	if ('a' <= c && c <= 'z')
		c += 'A' - 'a';
	else
	{
		if ((unsigned char)c > 'z')
		{
			// проверка на русский шрифт
			char *rus = strchr(russian_font_, c);
			if( rus - russian_font_ >= 33)
				c = russian_font_[rus - russian_font_ - 33];
		}
	}

	return c;
}

// bool toupper(char *src)
// конвертирование символов в нижний регистр
char String::tolower_(char c)
{
	if ('A' <= c && c <= 'Z')
			c += 'A' - 'a';
	else
	{
		if ((unsigned char) c > 'z')
		{
			// проверка на русский шрифт
			char *rus = strchr(russian_font_, c);
			if( rus - russian_font_ < 33)
			{
				c = russian_font_[rus - russian_font_ + 33];
			}
		}
	}
	return c;
}

int String::Replace(String str1, String str2)
{
	int str1_len = str1.GetLength();
	int str2_len = str2.GetLength();
	if(!str1_len) return 0;
	if(!str2_len) return 0;

	int count = 0;

	char *res = m_Data;

	res = strstr(res, str1.c_str());
	while(res)
	{
		int index = res-m_Data;
		if(str1_len == str2_len)
		{
			memmove(res, str2.c_str(), str2_len);
			res+=str2_len;
		}
		else
		if(str1_len > str2_len)
		{
			memmove(res, str2.c_str(), str2_len);
			int move_count = GetLength() - (index + str1_len);
			memmove(res + str2_len, res + str1_len, move_count);
			SetLength(move_count + res + str2_len - m_Data);
			res = m_Data + index + str2_len;//go to next token
		}
		else //str1_len < str2_len
		{
			int move_count = GetLength() - (index + str1_len);
			SetLength(index + move_count + str2_len);
			res=m_Data+index+str2_len;
			memmove(res, res-str2_len+str1_len, move_count);
			res=m_Data+index;
			memmove(res, str2.c_str(), str2_len);
			res = m_Data + index + str2_len;//go to next token
		}

		count++;
		res = strstr(res, str1.c_str());
	}
	return count;
}

int String::Replace(char ch, String str)
{
	int str_len = str.GetLength();
	if(!str_len) return 0;

	int count = 0;

	char *res = m_Data;

	res = strchr(res, ch);
	while(res)
	{
		int index = res-m_Data;
		if(str_len == 1)
		{
			memmove(res, str.c_str(), str_len);
			res+=str_len;
		}
		else
		{
			int move_count = GetLength() - (index + 1);
			SetLength(index + move_count + str_len);
			res=m_Data+index+str_len;
			memmove(res, res-str_len+1, move_count);
			res=m_Data+index;
			memmove(res, str.c_str(), str_len);
			res = m_Data + index + str_len;//go to next token
		}

		count++;
		if(res > m_Data + GetLength())
			break;

		res = strchr(res, ch);
	}
	return count;
}

int String::Replace(String str, char ch)
{
	int str_len = str.GetLength();
	if(!str_len) return 0;

	int count = 0;

	char *res = m_Data;

	res = strstr(res, str.c_str());
	while(res)
	{
		int index = res-m_Data;
		if(str_len == 1)
		{
			*res = ch;
			res+=1;
		}
		else
		{
			*res=ch;
			int move_count = GetLength() - (index + str_len);
			memmove(res + 1, res + str_len, move_count);
			SetLength(move_count + res + 1 - m_Data);
			res = m_Data + index + 1;//go to next token
		}

		count++;
		res = strstr(res, str.c_str());
	}
	return count;
}

int String::Replace(char ch1, char ch2)
{
	int count = 0;

	char *p = m_Data;
	while(*p)
	{
		if(*p == ch1)
		{
			*p = ch2;
			count++;
		}
		p++;
	}
	return count;
}

#ifndef WIN32
char *String::itoa(int x, char *y, int z)
{
	if(z==16)// HEX
	{
		sprintf(y,"%x",x);
	}
	else // DEC
		sprintf(y,"%d",x);

	return y;
}
char *String::ltoa(long x, char *y, int z)
{
	sprintf(y,"%f",x);
	return y;
}
char *String::ultoa(unsigned long x, char *y, int z)
{
	sprintf(y,"%f",x);
	return y;
}
#endif
