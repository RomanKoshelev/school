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
	public: 		byte * m_pData; 

	protected: 	size_t m_nRealSize; 

	protected: void Erase ();

	protected: void CopyFrom (const key_arr& from);


//RVK:>>>
	void SET_MPDATA (byte * M_PDATA, byte type, const byte * data, bool bInvert=false);


// Добавление ключа в набор
	protected: void AddKey (const pbyte pVal, FIELD_TYPE type, size_t nStrLen=0);


// Отладочная печать
// Если не указан аргумент -- печать в stdout
	public: void DebugPrint(string* pStr=NULL);

// Значение ключа из набора
	public: void GetKeyData (int item, void *_pRetVal);

// Получить размер набора
	public: size_t GetSize() const;

// Очистить набор -- в нём будет ноль ключей.
	public: void Init ();

// Конструктор
	public: key_arr ();

// Конструктор по другому набору ключей
	public: key_arr (const key_arr& from);
// Конструктор по типам
	public: key_arr (int					val);
	public: key_arr (byte				val);
	public: key_arr (bool				val);
	public: key_arr (float				val);
	public: key_arr (identifier		val);
	public: key_arr (const string&	val);
	public: key_arr (const char *		val);
	public: key_arr (time_t				val);

// Деструктор
	public: ~key_arr();

// Инициализация по другому набору ключей
	public: key_arr& operator= (const key_arr& from);

// Инициализация по указателю на данные другого набора ключей
	public: void FromPtr(pbyte pData);

// Получить число ключей в наборе
	public: size_t GetKeyNum ();

	protected: pbyte GetPackedItemPtr (size_t item);

//	Получить тип ключа из набора
	public: byte			GetItemType(size_t item);
//	Получить указатель на ключ из набора
	public: 	pbyte			GetItemPtr (size_t item);


//	Получить идентификатор, записанный в наборе ключей
	public: identifier GetObjID ();

//RVK:>>>
	protected: void SetNumericItemData (size_t item, pbyte pVal, bool bInvert);

// SetStringItemData
	protected: void SetStringItemData (size_t item, const char * _pData, size_t length,  bool bInvert);

// Установить в наборе нужное значение у ключа:
// int, byte, bool, float, identifier, string, const char *
	public: void SetKeyData (size_t item, int					val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, byte				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, bool				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, float				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, identifier		val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, guid				val, bool bInvert)	{SetNumericItemData	(item, (const pbyte)(&val),			bInvert);}
	public: void SetKeyData (size_t item, const string&	val, bool bInvert)	{SetStringItemData	(item, val.c_str(),	val.length(),	bInvert);}
	public: void SetKeyData (size_t item, const char *		val, bool bInvert)	{SetStringItemData	(item, val,				strlen(val),	bInvert);}

// Добавить в набор ключ:
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