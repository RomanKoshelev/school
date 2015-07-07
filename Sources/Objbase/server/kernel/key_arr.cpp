/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999-2000 W:Brain                                            []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            key_arr.h																	[]
[] Date:            19.04.2000                                                []
[] Author:          Roman V. Koshelev														[]
[] Description:     Упакованные ключи для индексов										[]
[]____________________________________________________________________________[]
*/
#define	USES_STATIC_FILE_ID_h
#define	USES_Ptr_h
#define	USES_string_h
#define	USES_AVTree_h
#define	USES_EventMonitor_h
#define	USES_File_h
#define	USES_key_arr_h
#define	USES_ObjDriver_h

#include "main.h"

extern char * FT_NAME_SHORT[];
extern char * FT_NAME		[];	
extern char * FT_NAME_ARR	[];
extern char * FT_VOID;
extern char * FT_SIZE_T;



//______________________________________________________________________________
//                                                                            []
//` Erase                                                                     []      
//                                                                            []
void key_arr::Erase () 
{
	if (m_pData)
	{
		delete [] m_pData;
	}
	m_pData		= NULL;
	m_nRealSize	= 0;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` CopyFrom                                                                  []         
//                                                                            []
void key_arr::CopyFrom (const key_arr& from)
{
	DEBUG_STACK_NAME (CopyFrom);

	if (from.m_pData)
	{
		size_t size = from.GetSize();
		if (m_nRealSize < size)
		{
			if (m_pData)
			{
				delete [] m_pData;
			}
			m_pData = new byte [m_nRealSize = size];
		}
		// bzero  (m_pData, m_nRealSize); // !!! -- паранойя
		memcpy (m_pData, from.m_pData, size);
	}
	else 
	{
		Init ();
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` SET_MPDATA                                                                []          
//                                                                            []
void key_arr::SET_MPDATA (byte * M_PDATA, byte type, const byte * data, bool bInvert)
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
		case FT_guid:
			M_PDATA[ 0]	= (byte) *(data + 3);
			M_PDATA[ 1]	= (byte) *(data + 2);
			M_PDATA[ 2]	= (byte) *(data + 1);
			M_PDATA[ 3]	= (byte) *(data + 0);

			M_PDATA[ 4]	= (byte) *(data + 7);
			M_PDATA[ 5]	= (byte) *(data + 6);
			M_PDATA[ 6]	= (byte) *(data + 5);
			M_PDATA[ 7]	= (byte) *(data + 4);

			M_PDATA[ 8]	= (byte) *(data +11);
			M_PDATA[ 9]	= (byte) *(data +10);
			M_PDATA[10]	= (byte) *(data + 9);
			M_PDATA[11]	= (byte) *(data + 8);
			nSize			= 12;
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
void key_arr::AddKey (const pbyte pVal, FIELD_TYPE type, size_t nStrLen)
{
	DEBUG_STACK_NAME (AddKey);

	if (m_pData==NULL)
	{
		Init ();
	}

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
		case FT_guid:			keySize = sizeof (guid);			SET_MPDATA	(M_PDATA+sizeof(byte), (byte)FT_guid,			pVal);	break;
		case FT_string:		keySize = nStrLen+1;					memcpy		(M_PDATA+sizeof(byte),  pVal, keySize);					break;
		default:
		{
			SERVER_DEBUG_ERROR ("AddKey: Неизвестный тип ключа");
			return;					
		}
	}

	M_PDATA[0] = (byte) type;
	keySize += sizeof (byte);

	pbyte pOldData = m_pData;
	size_t oldSize =	GetSize();

	size_t newSize = oldSize + keySize;

	if (m_nRealSize<newSize)
	{
		m_pData = new byte[m_nRealSize = newSize];
		memcpy(m_pData, pOldData, oldSize);
		delete [] pOldData;
	}

	memcpy(m_pData+oldSize, M_PDATA, keySize);

	*((size_t *)m_pData) += keySize;	// Размер набора
	(*(m_pData + sizeof(size_t)))++;	// Число ключей
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` Отладочная печать                                                         []                 
//  Если не указан аргумент -- печать в stdout											[]
//                                                                            []
void key_arr::DebugPrint(string* pStr)
{
	char SSS [10240];
	byte itemNum=(byte)GetKeyNum();
	sprintf(SSS, "size:%d\n", GetSize(), itemNum);
	if (pStr) (*pStr) += SSS;
	else printf (SSS);

	for(int i = 0; i <itemNum; i++)
	{
		byte itemType=GetItemType(i);
		snprintf(SSS, 1024, "   %s",FT_NAME[itemType]);
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
				snprintf(SSS, 1024, "%d\n",*((int*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_float:
				pVal[3] = byte (pRawVal[0]^(bNegative?nMASK:0x80));
				pVal[2] = byte (pRawVal[1]^nMASK);
				pVal[1] = byte (pRawVal[2]^nMASK);
				pVal[0] = byte (pRawVal[3]^nMASK);
				snprintf(SSS, 1024, "%f\n", *((float*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_identifier:
				pVal[3]=pRawVal[0];
				pVal[2]=pRawVal[1];
				pVal[1]=pRawVal[2];
				pVal[0]=pRawVal[3];
				snprintf(SSS, 1024, "%d\n", *((identifier*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_guid:
				pVal[3]=pRawVal[0];
				pVal[2]=pRawVal[1];
				pVal[1]=pRawVal[2];
				pVal[0]=pRawVal[3];
				snprintf(SSS, 1024, "{%d,", *((identifier*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				pVal[7]=pRawVal[4];
				pVal[6]=pRawVal[5];
				pVal[5]=pRawVal[6];
				pVal[4]=pRawVal[7];
				snprintf(SSS, 1024, "%d,", *((identifier*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				pVal[11]=pRawVal[ 8];
				pVal[10]=pRawVal[ 9];
				pVal[ 9]=pRawVal[10];
				pVal[ 8]=pRawVal[11];
				snprintf(SSS, 1024, "%d}\n", *((identifier*)pVal));
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_byte:
				snprintf(SSS, 1024, "%d\n",*pRawVal);
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_bool:
				snprintf(SSS, 1024, "%s\n",*pRawVal ? "true" : "false");
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
			case FT_string:
				snprintf(SSS, 1024, "'%s'\n",pRawVal);
				if (pStr) (*pStr) += SSS;
				else printf (SSS);
				break;
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Значение ключа из набора                                                  []  
//                                                                            []			  
void key_arr::GetKeyData (int item, void *_pRetVal)
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
		case FT_guid:
			pRetVal[3]=pRawVal[0];
			pRetVal[2]=pRawVal[1];
			pRetVal[1]=pRawVal[2];
			pRetVal[0]=pRawVal[3];

			pRetVal[7]=pRawVal[4];
			pRetVal[6]=pRawVal[5];
			pRetVal[5]=pRawVal[6];
			pRetVal[4]=pRawVal[7];

			pRetVal[11]=pRawVal[11];
			pRetVal[10]=pRawVal[10];
			pRetVal[ 9]=pRawVal[ 9];
			pRetVal[ 8]=pRawVal[ 8];
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


//______________________________________________________________________________
//                                                                            []
//` Получить размер набора                                                    []                      
//                                                                            []
size_t key_arr::GetSize() const
{
	return m_pData? *((size_t *)m_pData) : 0;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Очистить набор -- в нём будет ноль ключей.                                []                                          
//                                                                            []
void key_arr::Init ()
{
	DEBUG_STACK_NAME (Init);

//	 0 1 2 3      4
// [size_t Size, byte KeyNum, key1, ... keyN]
// Keyi    = [byte type, data]	
// LastKey = idendifier key

	const size_t nKeyNumShift			= sizeof(size_t);
	const size_t KEY_ARR_HEADER_SIZE = sizeof(size_t) + sizeof(byte);

	if (m_nRealSize < KEY_ARR_HEADER_SIZE)
	{
		if (m_pData)
		{
			delete [] m_pData;
		}
		m_pData = new byte[m_nRealSize = KEY_ARR_HEADER_SIZE];
		*(((byte  *)m_pData)+nKeyNumShift) = 0;
		*((size_t *)m_pData)               = KEY_ARR_HEADER_SIZE;
	}
	else
	{
		*(((byte *)m_pData)+nKeyNumShift) = 0;
		*((size_t*)m_pData)               = KEY_ARR_HEADER_SIZE;
	}
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` Конструктор                                                               []           
//                                                                            []
key_arr::key_arr ()									
{ 
	m_pData  = NULL;
	m_nRealSize = 0;
}
//----------------------------------------------------------------------------[] 
key_arr::key_arr (int				val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (byte				val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (bool				val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (float				val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (identifier		val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (const string&	val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (const char *	val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
key_arr::key_arr (time_t			val) {m_pData=NULL; m_nRealSize=0; (*this)+=val;}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Конструктор по другому набору ключей                                      []                                    
//                                                                            []
key_arr::key_arr (const key_arr& from)	
{ 
	m_pData	= NULL;
	m_nRealSize = 0;
	CopyFrom (from);
}
//______________________________________________________________________________
//                                                                            []
//` Деструктор                                                                []          
//                                                                            []
key_arr::~key_arr()									
{
	Erase();
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Инициализация по другому набору ключей                                    []                                      
//                                                                            []
key_arr& key_arr::operator= (const key_arr& from)
{
	CopyFrom (from);
	return * this;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Инициализация по указателю на данные другого набора ключей                []                                                          
//                                                                            []
void key_arr::FromPtr (pbyte pData)
{
	DEBUG_STACK_NAME (FromPtr);

	size_t size = *((size_t *)pData);
	if (m_nRealSize < size)
	{
		Erase ();
		m_pData = new byte[m_nRealSize = size];
	}
	memcpy(m_pData, pData, size);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Получить число ключей в наборе                                            []                              
//                                                                            []
size_t key_arr::GetKeyNum ()
{
	const static size_t nOffset = sizeof(size_t);
	return m_pData? *(m_pData+nOffset) : 0;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` GetPackedItemPtr                                                          []                 
//                                                                            []
pbyte key_arr::GetPackedItemPtr (size_t item)
{
	if (m_pData==NULL)
	{
		Init ();
	}
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
			case FT_guid:
				nOffset += nTypeOffset;
				nOffset += sizeof (guid);
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
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Получить тип ключа из набора                                              []                            
//                                                                            []
byte key_arr::GetItemType(size_t item)		{ return *(GetPackedItemPtr(item)); }
//______________________________________________________________________________
//                                                                            []
//` Получить указатель на ключ из набора                                      []                                    
//                                                                            []
pbyte key_arr::GetItemPtr (size_t item)		{ return GetPackedItemPtr(item) + sizeof(byte); }
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор, записанный в наборе ключей                        []                                                  
//                                                                            []
identifier key_arr::GetObjID ()
{
	if (m_pData==NULL)
	{
		return NA;
	}

	pbyte pRawVal=GetItemPtr(GetKeyNum()-1);
	byte pVal[4];
	pVal[3]=pRawVal[0];
	pVal[2]=pRawVal[1];
	pVal[1]=pRawVal[2];
	pVal[0]=pRawVal[3];
	return *((identifier *)pVal);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` SetNumericItemData                                                        []                   
//                                                                            []
void key_arr::SetNumericItemData (size_t item, pbyte pVal, bool bInvert)
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
		case FT_guid:			nSize = sizeof (guid);			break;
		default:
			{
				SERVER_DEBUG_ERROR ("SetNumericItemData: Неизвестный тип ключа");
				return;					
			}
	}
	SET_MPDATA (M_PDATA, type, pVal, bInvert);
	memcpy(ptr+sizeof(byte), M_PDATA, nSize);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` SetStringItemData                                                         []  
//                                                                            []
void key_arr::SetStringItemData (size_t item, const char * _pData, size_t length,  bool bInvert)
{
	DEBUG_STACK_NAME (SetStringItemData);

	if (m_pData==NULL)
	{
		Init ();
	}
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

	if(oldLength != length) 
	{
		size_t beforeString = ptr - m_pData;								// Размер до начала строки
		size_t afterString  = GetSize() - (beforeString+oldLength);	// Размер остатка за строкой

		size_t newSize =  beforeString + length + afterString;
		pbyte pNewData = new byte[newSize];
		memcpy(pNewData,									m_pData,										beforeString);
		memcpy(pNewData + beforeString,				pData,										length);
		memcpy(pNewData + beforeString + length, 	m_pData + beforeString + oldLength, afterString);

		delete m_pData;
		m_pData = pNewData;
		m_nRealSize = newSize;

		*((size_t *)m_pData) = beforeString + length + afterString;

	} 
	else 
	{
		memcpy(ptr, pData, length);
	}
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/