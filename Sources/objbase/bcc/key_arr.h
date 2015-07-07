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
[] Description:     Упакованные ключи для индексов										[]
[]____________________________________________________________________________[]
*/
#ifndef key_arr_H
#define key_arr_H


enum FIELD_TYPE
{
	FT_identifier	=	0,
	FT_int			=	1,
	FT_byte			=	2,
	FT_bool			=	3,
	FT_float			=	4,
	FT_string		=	5,

	FT_nothing		=	6
};
typedef void* OBD_pointer;

int CompareFunction_CObjIndex_AVTree_Item (pbyte& a, pbyte& b);


#define MAX_KEY_LENGTH (256*1024)

extern char * FT_NAME_SHORT[];
extern char * FT_NAME		[];	
extern char * FT_NAME_ARR	[];
extern char * FT_VOID;
extern char * FT_SIZE_T;

extern int key_arr_AllocCount;

#define	KEY_ARR_HEADER_SIZE			(sizeof(size_t) + sizeof(byte))



//______________________________________________________________________________
//                                                                            []
//` key_arr 																						[]
//                                                                            []
struct key_arr
{
//	Набор ключей для поиска объектов в базе данных.
// Новые ключи добавляются оператором += (type) key;
// Допустимые типы: int, byte, bool, float, identifier, string, const char *;
// Очистить ключ можно функцией Init() -- ключ будет считаться пустым.
// Не полностью заполненный ключ (в т.ч. пустой) означает, что при поиске 
// объектов будут игнорироваться значения полей из недостающей части ключа.
// ВНИМАНИЕ: Если типы ключей идут не в том порядке, что определён
// типами полей текущего индекса, то система будет игнорировать такой ключ.
// Последний ключ в любом индексе -- идентификатор объекта. Он добавляется автоматически.
// Таким образом, абсолютно полный ключ -- это ключ ко всеми полями + идентификатор объекта.
	protected: void About_class_key_arr(){};

// [size_t Size, byte KeyNum, key1, ... keyN]
// Keyi    = [byte type, data]	
// LastKey = idendifier key
	public: 	byte * m_pData; 

	protected: void Erase () 
	{
		if (m_pData)
		{
		-- key_arr_AllocCount;
			delete [] m_pData;
		}
		m_pData = NULL;
	}

	protected: void CopyFrom (const key_arr& from)
	{
		if (from.m_pData!=NULL)
		{
			size_t size = from.GetSize();
		++ key_arr_AllocCount;
			m_pData = new byte [size];
			memcpy (m_pData, from.m_pData, size);
		}
	}


//RVK:>>>
	void SET_MPDATA (byte * M_PDATA, byte type, const byte * data, bool bInvert=false)
	{
		bool bNegative =	((*(data+3)) & 0x80) != 0;
		int  nMASK		=	bNegative ? 0xFF : 0x00;
		int  nSize		=	0;

		switch(FIELD_TYPE(type)) {
			case FT_int:
				M_PDATA[0]	= (byte) (*(data+3)^0x80);
				M_PDATA[1]	= (byte) *(data+2);
				M_PDATA[2]	= (byte) *(data+1);
				M_PDATA[3]	= (byte) *(data+0);
				nSize			= 4;
				break;
			case FT_float:
				M_PDATA[0]	= (byte) (*(data+3)^(bNegative?nMASK:0x80));
				M_PDATA[1]	= (byte) (*(data+2)^nMASK);
				M_PDATA[2]	= (byte) (*(data+1)^nMASK);
				M_PDATA[3]	= (byte) (*(data+0)^nMASK);
				nSize			= 4;
				break;
			case FT_identifier:
				M_PDATA[0]	= (byte) *(data+3);
				M_PDATA[1]	= (byte) *(data+2);
				M_PDATA[2]	= (byte) *(data+1);
				M_PDATA[3]	= (byte) *(data+0);
				nSize			= 4;
				break;
			case FT_byte:
				M_PDATA[0]	= (byte) *(data+0);
				nSize			= 1;
				break;
			case FT_bool:
				M_PDATA[0]	= (byte) (*(data+0) ? 0xFF : 0x00);
				nSize			= 1;
				break;
		}

	// Нужна обратная индексация по полю
		if (bInvert) {
			for (int i=0; i<nSize; i++) {
				M_PDATA[i] = (byte)((byte)255 - (byte)M_PDATA[i]);
			}
		}
	}
	//____________________________________________________________________________[]



	//______________________________________________________________________________
	//                                                                            []
	//` Добавление ключа в набор                                                  []  
	//                                                                            []	
	protected: void AddKey (const pbyte pVal, FIELD_TYPE type, size_t nStrLen=0)
	{
		pbyte pOldData = m_pData;

		nStrLen = min (MAX_KEY_LENGTH-GetSize()-100, nStrLen);
		static byte M_PDATA [MAX_KEY_LENGTH];
		*((size_t*)M_PDATA) = 0;

		size_t keySize = 0;

		switch(type)
		{
			case FT_int:			keySize = sizeof (int);				SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_int,			pVal);	break;
			case FT_byte:			keySize = sizeof (byte);			SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_byte,			pVal);	break;
			case FT_bool:			keySize = sizeof (byte);			SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_bool,			pVal);	break;
			case FT_float:			keySize = sizeof (float);			SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_float,			pVal);	break;
			case FT_identifier:	keySize = sizeof (identifier);	SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_identifier,	pVal);	break;
			case FT_string:		keySize = nStrLen+1;					memcpy		(M_PDATA+sizeof(byte),  pVal, keySize);					break;
			default:
				{
					SERVER_DEBUG_ERROR ("AddKey: Неизвестный тип ключа");
					return;					
				}
		}

		M_PDATA[0] = (byte) type;
		keySize += sizeof (byte);

		size_t oldSize =	GetSize();

	++ key_arr_AllocCount;
		m_pData = new byte[ oldSize + keySize ];

		memcpy(m_pData, pOldData, oldSize);
		memcpy(m_pData+oldSize, M_PDATA, keySize);
		*((size_t *)m_pData) += keySize;	// Размер набора
		(*(m_pData + sizeof(size_t)))++;	// Число ключей
		
	-- key_arr_AllocCount;
		delete [] pOldData;
	}
	//____________________________________________________________________________[]




// Отладочная печать
// Если не указан аргумент -- печать в stdout
	public: void DebugPrint(string* pStr=NULL)
	{
		char SSS [10240];
		byte itemNum=(byte)GetKeyNum();
		sprintf(SSS, "size:%d\n", GetSize(), itemNum);
		if (pStr) (*pStr) += SSS;
		else printf (SSS);

		for(int i = 0; i <itemNum; i++)
		{
			byte itemType=GetItemType(i);
			sprintf(SSS, "   %s",FT_NAME[itemType]);
			if (pStr) (*pStr) += SSS;
			else printf (SSS);
			byte pVal[4];
			pbyte pRawVal=GetItemPtr(i);

			bool bNegative = (pRawVal[0] & 0x80) == 0;
			int  nMASK		= bNegative ? 0xFF : 0x00;

			switch(itemType) {
				case FT_int:
					pVal[3] = (byte) (pRawVal[0]^0x80);
					pVal[2] = pRawVal[1];
					pVal[1] = pRawVal[2];
					pVal[0] = pRawVal[3];
					sprintf(SSS, "%d\n",*((int*)pVal));
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
				case FT_float:
					pVal[3] = byte (pRawVal[0]^(bNegative?nMASK:0x80));
					pVal[2] = byte (pRawVal[1]^nMASK);
					pVal[1] = byte (pRawVal[2]^nMASK);
					pVal[0] = byte (pRawVal[3]^nMASK);
					sprintf(SSS, "%f\n", *((float*)pVal));
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
				case FT_identifier:
					pVal[3]=pRawVal[0];
					pVal[2]=pRawVal[1];
					pVal[1]=pRawVal[2];
					pVal[0]=pRawVal[3];
					sprintf(SSS, "%d\n", *((identifier*)pVal));
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
				case FT_byte:
					sprintf(SSS, "%d\n",*pRawVal);
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
				case FT_bool:
					sprintf(SSS, "%s\n",*pRawVal ? "true" : "false");
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
				case FT_string:
					sprintf(SSS, "'%s'\n",pRawVal);
					if (pStr) (*pStr) += SSS;
					else printf (SSS);
					break;
			}
		}
	}




	//______________________________________________________________________________
	//                                                                            []
	//` Значение ключа из набора                                                  []  
	//                                                                            []			  
	public: void GetKeyData (int item, void *_pRetVal)
	{
		byte *	pRetVal	= (byte*)_pRetVal;
		byte		itemType	=	GetItemType(item);
		pbyte		pRawVal	=	GetItemPtr(item);

		bool bNegative = (pRawVal[0] & 0x80) == 0;
		int  nMASK		= bNegative ? 0xFF : 0x00;

		switch(itemType) {
			case FT_int:
				pRetVal[3] = (byte) (pRawVal[0]^0x80);
				pRetVal[2] = pRawVal[1];
				pRetVal[1] = pRawVal[2];
				pRetVal[0] = pRawVal[3];
				break;
			case FT_float:
				pRetVal[3] = byte (pRawVal[0]^(bNegative?nMASK:0x80));
				pRetVal[2] = byte (pRawVal[1]^nMASK);
				pRetVal[1] = byte (pRawVal[2]^nMASK);
				pRetVal[0] = byte (pRawVal[3]^nMASK);
				break;
			case FT_identifier:
				pRetVal[3]=pRawVal[0];
				pRetVal[2]=pRawVal[1];
				pRetVal[1]=pRawVal[2];
				pRetVal[0]=pRawVal[3];
				break;
			case FT_byte:
				pRetVal[0] = *pRawVal;
				break;
			case FT_bool:
				pRetVal[0] = *pRawVal? true: false;
				break;
			case FT_string:
				strcpy ((char*)pRetVal, (char*)pRawVal);
				break;
		}
	}
	//____________________________________________________________________________[]


// Получить размер набора
	public: size_t GetSize() const
	{
		return m_pData? *((size_t *)m_pData) : 0;
	}

// Очистить набор -- в нём будет ноль ключей.
	public: void Init ()
	{
		Erase ();
	++ key_arr_AllocCount;
		m_pData = new byte[KEY_ARR_HEADER_SIZE];
		memset(m_pData,0,KEY_ARR_HEADER_SIZE); 
		*((size_t *)m_pData)=KEY_ARR_HEADER_SIZE;
	}

// Конструктор
	public: key_arr ()									
	{ 
		m_pData = NULL;
		Init ();
	}
// Конструктор по другому набору ключей
	public: key_arr (const key_arr& from)	{ m_pData = NULL; CopyFrom (from);}
// Деструктор
	public: ~key_arr()									{ Erase();}

// Инициализация по другому набору ключей
	public: key_arr& operator= (const key_arr& from)
	{
		Erase ();
		CopyFrom (from);
		return * this;
	}

// Инициализация по указателю на данные другого набора ключей
	public: void FromPtr(pbyte pData)
	{
		Erase ();
		size_t size = *((size_t *)pData);
	++ key_arr_AllocCount;
		m_pData = new byte[size];
		memcpy(m_pData, pData, size);
	}

// Получить число ключей в наборе
	public: size_t GetKeyNum ()
	{
		const static size_t nOffset = sizeof(size_t);
		return *(m_pData+nOffset);
	}

	protected: pbyte GetPackedItemPtr (size_t item)
	{
	// nOffset указывает на тип первого ключа.
		size_t nOffset = sizeof(size_t) + sizeof(byte);

		const int nTypeOffset = sizeof (byte);

		for(byte iKey=0; iKey < item; iKey++)
		{
			switch(FIELD_TYPE(*(m_pData+nOffset)))
			{
				case FT_identifier:
				case FT_int:
				case FT_float:
					nOffset += nTypeOffset;
					nOffset += sizeof (int);
				break;
				case FT_byte:
				case FT_bool:
					nOffset += nTypeOffset;
					nOffset += sizeof (byte);
				break;
				case FT_string:
					nOffset += nTypeOffset;
					nOffset += strlen ((const char *)m_pData+nOffset)+1;
				break;
			}
		}

		return m_pData + nOffset;
	}

//	Получить тип ключа из набора
	public: byte			GetItemType(size_t item)		{ return *(GetPackedItemPtr(item)); }
//	Получить указатель на ключ из набора
	public: 	pbyte			GetItemPtr (size_t item)		{ return GetPackedItemPtr(item) + sizeof(byte); }


//	Получить идентификатор, записанный в наборе ключей
	public: identifier GetObjID ()
	{
		if (m_pData==NULL)
			return NA;

		pbyte pRawVal=GetItemPtr(GetKeyNum()-1);
		byte pVal[4];
		pVal[3]=pRawVal[0];
		pVal[2]=pRawVal[1];
		pVal[1]=pRawVal[2];
		pVal[0]=pRawVal[3];
		return *((identifier *)pVal);
	}

//RVK:>>>
	protected: void SetNumericItemData (size_t item, pbyte pVal, bool bInvert)
	{
		static byte M_PDATA [MAX_KEY_LENGTH];
		*((size_t*)M_PDATA) = 0;

		pbyte ptr	=	GetPackedItemPtr(item);
		int	nSize	=	0;
		byte	type	=	*ptr;
		switch((FIELD_TYPE)type) 
		{
			case FT_int:			nSize = sizeof (int);			break;
			case FT_byte:			nSize = sizeof (byte);			break;
			case FT_bool:			nSize = sizeof (byte);			break;
			case FT_float:			nSize = sizeof (float);			break;
			case FT_identifier:	nSize = sizeof (identifier);	break;
			default:
				{
					SERVER_DEBUG_ERROR ("SetNumericItemData: Неизвестный тип ключа");
					return;					
				}
		}
		SET_MPDATA (M_PDATA, type, pVal, bInvert);
		memcpy(ptr+sizeof(byte), M_PDATA, nSize);
	}

	//______________________________________________________________________________
	//                                                                            []
	//` SetStringItemData                                                         []  
	//                                                                            []
	//RVK:>>>
	protected: void SetStringItemData (size_t item, const char * _pData, size_t length,  bool bInvert)
	{
		static char  pData[MAX_KEY_LENGTH];
		memcpy (pData, _pData, length);


	// Изменяем строку, если нужен обратный порядок индексации.
		if (bInvert){
		// Храним строку с двумя нулями на конце, т.к. первый будет обращён в 255.
			length++;
			pData[length-1]=0;
			pData[length  ]=0;
			for (size_t i=0; i<length; i++) 
			{
				//  0    1   2   3   4   .  252  253  254  255
				//  |    |   |   |   |   .   |    |    |    |
				// 255  254 254 253 252  .   4    3    2    1
				int nTmp = pData[i];
				pData[i] =	(byte)(	nTmp ==   0?	255: 
											nTmp ==   1?	254: 
											nTmp ==   2?	254: 
																256-nTmp);
			}
		}


		pbyte ptr=GetItemPtr(item);												// Указатель на начало строки
		size_t oldLength = strlen((const char *)ptr);
	
		SERVER_DEBUG_ASSERT (m_pData, "SetStringItemData: Data not allocated in key_arr");
		byte itemNum = (byte)GetKeyNum();
		SERVER_DEBUG_ASSERT (itemNum>0, "SetStringItemData: Empty key");
		SERVER_DEBUG_ASSERT (item<itemNum, "SetStringItemData: Invalid item index");

		if(oldLength != length) {
			size_t beforeString = ptr - m_pData;								// Размер до начала строки
			size_t afterString  = GetSize() - (beforeString+oldLength);	// Размер остатка за строкой

		++ key_arr_AllocCount;
			pbyte pNewData = new byte[ beforeString + length + afterString ];
			memcpy(pNewData,									m_pData,										beforeString);
			memcpy(pNewData + beforeString,				pData,										length);
			memcpy(pNewData + beforeString + length, 	m_pData + beforeString + oldLength, afterString);

		-- key_arr_AllocCount;
			delete m_pData;
			m_pData = pNewData;

			*((size_t *)m_pData) = beforeString + length + afterString;

		} else {
			memcpy(ptr, pData, length);
		}
	}
	//____________________________________________________________________________[]


// Установить в наборе нужное значение у ключа:
// int, byte, bool, float, identifier, string, const char *
	public: void SetKeyData (size_t item, int					val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, byte				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, bool				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, float				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, identifier		val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, const string&	val, bool bInvert)	{SetStringItemData	(item, val.c_str(),	val.length(),	bInvert);}
	public: void SetKeyData (size_t item, const char *		val, bool bInvert)	{SetStringItemData	(item, val,				strlen(val),	bInvert);}

// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (int val)				{AddKey((const pbyte)&val,	FT_int);					return *this;}
// Добавить в набор ключ
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (byte val)				{AddKey((const pbyte)&val,	FT_byte);				return *this;}
// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (bool val)				{AddKey((const pbyte)&val,	FT_bool);				return *this;}
// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (float val)				{AddKey((const pbyte)&val,	FT_float);				return *this;}
// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (identifier val)		{AddKey((const pbyte)&val,	FT_identifier);		return *this;}
// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (const string& val)				{AddKey((const pbyte)val.c_str(), FT_string, val.len());			return *this;}
// Добавить в набор ключ:
// int, byte, bool, float, identifier, string, const char *
	public: key_arr & operator+= (const char * val)	{AddKey((const pbyte)val,			FT_string,	strlen (val));		return *this;}

// Сравнение наборов ключей
	public: bool operator < (key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) <  0;}
// Сравнение наборов ключей
	public: int Compare		(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg);		}
// Сравнение наборов ключей
	public: bool operator <=(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) <= 0;}
// Сравнение наборов ключей
	public: bool operator > (key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) >  0;}
// Сравнение наборов ключей
	public: bool operator >=(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) >= 0;}
// Сравнение наборов ключей
	public: bool operator ==(key_arr& to)	{pbyte arg = to.GetPtr(); return CompareFunction_CObjIndex_AVTree_Item (m_pData, arg) == 0;}
	
// Получить	указатель на данные
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