// HomeLabs Software, 1999-2000
// Dima Poliakov'2000

// NOT A PUBLIC CODE
// Please do not destribute it

#ifndef __STRING__
#define __STRING__

class String
{
public:
	String( void );
	String( const char *src );
	String( const String &src );
	String( long src );
	String( unsigned long src );
	String( int src );
	String( unsigned int src );
	String( char src );
	~String( );
	friend String operator+( const char *lhs, const String &rhs );
	String operator=( const String &rhs );
	String operator+( const String &rhs ) const;
	String operator+=( const String &rhs );
	bool operator==( const String &rhs );
	bool operator!=( const String &rhs ) const;
	bool operator<( const String &rhs ) const;
	bool operator>( const String &rhs ) const;
	bool operator<=( const String &rhs ) const;
	bool operator>=( const String &rhs ) const;
	char &operator[]( int index );
	char GetChar( int index );
	char *c_str( void ) const;
	int Length( void ) const;
	int GetLength( void ) const;
	bool IsEmpty( void ) const;
	void SetLength( int Len );
	void Delete( int Index, int Len );
	void Insert( int Index, const String &String );
	String LowerCase( void );
	String UpperCase( void );
	String SubString( int Start, int Len ) const;
	int Pos( const String &SubStr ) const;
	char LastChar( void ) const;
	int Replace(String str1, String str2);
	int Replace(char ch, String str2);
	int Replace(char ch1, char ch2);
	int Replace(String str, char ch);

	// эти функции как ANSI, но понимают русский язык
	int stricmp_(const char *dest, const char *src);
	int strcmp_(const char *dst, const char *src);
	char *strupr_(char *src);
	char *strlwr_(char *src);
	char tolower_(char c);
	char toupper_(char c);

#ifndef WIN32 // UNIX...
	char *itoa(int x, char *y, int z);
	char *ltoa(long x, char *y, int z);
	char *ultoa(unsigned long x, char *y, int z);
#endif

private:
	char *m_Data;
	int data_len;
};

#endif //__STRING__
