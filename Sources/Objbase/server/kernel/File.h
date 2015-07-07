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

// Объект для управления встроенной файловой системой.
class CFile : public CPtr<byte>
{
// Класс CFile реализует объекты для управления 
// файлами встроенной файловой системой.
// Каждому такому файлу соответствует уникальный 
// идектификатор. Этот класс выведен из класа CPtr:
// class CFile: public CPtr<byte>
// Так что к объекту типа CFile можно обращаться как к массиву,
// когда в него загружены данные.
// В файле STATIC_FILE_ID.h можно зарезервировать константы-идентификаторы
// для файлов определённого назначения (например, ini-файл)
	protected: void About_class_CFile (){};

// Уникальный идентификатор файла
	protected: identifier	m_nID;
// Смещение для потоковой записи и чтения
	protected: size_t			m_nOffset;

public:
// Конструктор по умолчанию. Файлом нельзя пользоватьса -- надо сначала открыть
	CFile ()
	{
		m_nID=UNKNOWN;
		m_nOffset=0;
	}

// Конструктор -- открывает файл
	CFile (identifier nID)
	{
		m_nID=UNKNOWN;
		m_nOffset=0;
		Open(nID);
	}


// Открыть файл
	CFile& operator = (identifier nID)
	{
		Open(nID);
		return *this;
	}

// Деструктор -- закрывает файл и разрешает доступ другим объектам.
	~CFile()
	{
		if(m_nID!=UNKNOWN)
			Close();
	}

// Проверка существования файла с указанным иденитфикатором. Статическая функция.
	static bool	Exist(identifier nID)
	{
		return FD.Exist(nID);
	}

// Проверка возможности использования объекта как файла
	bool IsValid() 
	{
		DEBUG_STACK_NAME (IsValid);

		return (m_nID!=UNKNOWN) && Exist(m_nID);
	}

// Создать новый файл и открыть его
// Возвращает идентификатор созданного файла.
	identifier CreateOpen()
	{
		DEBUG_STACK_NAME (CreateOpen);

		if (IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("CreateOpen: Файл %d уже открыт", m_nID);
			return m_nID;
		}

		m_nOffset=0;
		Open (CreateNewFile());

		return m_nID;
	}

// Просто создать новый файл. Статическая функция.
// Возвращает идентификатор созданного файла.
	static identifier CreateNewFile()
	{
		DEBUG_STACK_NAME (CreateNewFile);

		return FD.CreateNewFile ();
	}

// Удалить произвольный файл из базы по 
// идентификатору (если он не открыт). Статическая функция.
	static void DeleteFile (identifier nID)
	{
		DEBUG_STACK_NAME (DeleteFile);

		FD.Delete (nID);
	}

// Удалить файл из базы и инвалидировать объект
	void Delete()
	{
		DEBUG_STACK_NAME (Delete);

		FD.Delete(m_nID);
		m_nID=UNKNOWN;
	}

// Открыть файл и запретить к нему доступ другим объектам
	void Open(identifier nID)
	{
		DEBUG_STACK_NAME (Open);

		if (IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("Open: Файл %d уже открыт", m_nID);
			return;
		}
		m_nID=nID;
		m_nOffset=0;
		FD.Lock(m_nID);
	}

// Закрыть файл и разрешить к нему доступ другим объектам
	void Close()
	{
		DEBUG_STACK_NAME (Close);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("Close: Попытка закрытия некорректного файла %d", m_nID);
			return;
		}
		FD.Unlock(m_nID);
		m_nID=UNKNOWN;
	}

// Получить идентификатор файла
	identifier GetID()
	{
		DEBUG_STACK_NAME (GetID);

		return m_nID;
	}

// 1. Выделить память и загрузить в неё файл целиком -- доступ как к CPtr<byte>
// 2. Загрузить из файла все данные в чужой указатель. Смещение ставится в начало.
	void Load()
	{
		DEBUG_STACK_NAME (Load);

		int nSize = GetMaxSize();
		Alloc(nSize+1);
		FD.Read(m_nID,m_pData,nSize);
		m_nOffset=0;
	}

// 1. Выделить память и загрузить в неё файл целиком -- доступ как к CPtr<byte>
// 2. Загрузить из файла все данные в чужой указатель. Смещение ставится в начало.
	void Load(void *pData)
	{
		DEBUG_STACK_NAME (Load);

		FD.Read(m_nID,pData,GetMaxSize());
		m_nOffset=0;
	}

// 1. Сохранить файл целиком -- как все данные CPtr<byte>. Смещение ставится в начало.
// 2. Записать порцию данных из чужого указателя. Смещение увеличивается.
	void Save()
	{
		DEBUG_STACK_NAME (Save);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Save: Попытка сохранения некорректного файла");
			return;
		}
		if (m_pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Save: Файл %d -- нечего сохранять. Данные не выделены.", m_nID);
			return;			
		}
		FD.Write(m_nID,m_pData,m_nSize);
		m_nOffset=0;
	}

// 1. Сохранить файл целиком -- как все данные CPtr<byte>. Смещение ставится в начало.
// 2. Записать порцию данных из чужого указателя. Смещение увеличивается.
	void Save(void *pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Save);

		FD.Write(m_nID,pData,nSize);
	}

// Изменить смещение относительно позиции (SEEK_SET, SEEK_CUR, SEEK_END)
	size_t Seek(int nOffset, int nWhere=SEEK_SET)
	{
		DEBUG_STACK_NAME (Seek);

		if(nWhere==SEEK_SET)
			m_nOffset=0;
		if (((int)m_nOffset+nOffset)<0)
		{
			SERVER_DEBUG_ERROR_2 ("Seek: Файл %d -- выход за начало файла. offset = %d", m_nID, (int)m_nOffset+nOffset);
			return 0;
		}
		m_nOffset+=nOffset;
		return m_nOffset;
	}

// Узнать смещение
	size_t Tell()
	{
		DEBUG_STACK_NAME (Tell);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Tell: Некорректный файл.");
			return 0;
		}
		return m_nOffset;
	}

// 1. Считать порцию данных во внутренний указатель. Память выделяется, смещение увеличивается.
// 2. Считать порцию данных по чужому указателю. Смещение увеличивается.
	void Read(size_t nSize)
	{
		DEBUG_STACK_NAME (Read);

		Alloc(nSize+1);
		Read(m_pData,nSize);
	}

// 1. Считать порцию данных во внутренний указатель. Память выделяется, смещение увеличивается.
// 2. Считать порцию данных по чужому указателю. Смещение увеличивается.
	void Read(void * pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Read);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Read: Некорректный файл.");
			return;
		}
		if (pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Read: Файл %d -- память для чтения не выделена.", m_nID);
			return;
		}
		FD.ReadBlock(m_nID,pData,m_nOffset,nSize);
		m_nOffset += nSize;
	}


// 1. Записать все данные, хранящиеся в памяти. Смещение ставится на начало.
// 2. Записать порцию данных из чужого указателя. Смещение увеличивается.
	void Write()
	{
		DEBUG_STACK_NAME (Write);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: Некорректный файл.");
			return;
		}
		if (m_pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Write: Файл %d -- попытка сохранения несуществующих внутренних данных.", m_nID);
			return;
		}
		Write(m_pData,m_nSize);
		m_nOffset = 0;
	}

// 1. Записать все данные, хранящиеся в памяти. Смещение ставится на начало.
// 2. Записать порцию данных из чужого указателя. Смещение увеличивается.
	void Write(void * pData, size_t nSize)
	{
		DEBUG_STACK_NAME (Write);

		if (nSize==0)
		{
			return;
		}
		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: Некорректный файл.");
			return;
		}
		if (pData==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("Write: Файл %d -- память для записи не выделена.", m_nID);
			return;
		}
		FD.WriteBlock(m_nID,pData,m_nOffset,nSize);
		m_nOffset += nSize;
	}

// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (size_t			data)		{Write (&data, sizeof (size_t));}
// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (int				data)		{Write (&data, sizeof (data));}
// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (bool				data)		{Write (&data, sizeof (data));}
// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (char				data)		{Write (&data, sizeof (data));}
// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (float			data)		{Write (&data, sizeof (data));}
// Записать типизированные данные (int, bool, ..., identifier). Смещение увеличивается.
	void WriteData (identifier		data)		{Write (&data, sizeof (data));}


// Записать кусок строки. Смещение увеличивается.
	void WriteData (int size, const char * str)
	{
		DEBUG_STACK_NAME (WriteData);

		WriteData (size);
		Write ((void*)str, size);
	}

// Записать всю строку. Смещение увеличивается.
	void WriteData (const char * str)
	{
		DEBUG_STACK_NAME (WriteData);

		WriteData (strlen (str)+1, str);
	}

// Записать и закодировать "string". Смещение увеличивается.
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

//	Записать данные из CPtr<TYPE> Смещение увеличивается.
// Внимание: class TYPE должен не содержать указателей,
// не иметь виртуальных методов и кнструкторов.
	public: void WriteData (CPtr_info pi)
	{
		DEBUG_STACK_NAME (WriteData);

		size_t   nSize = (*(pi.p_size)) * pi.item_size;
		void   * pData = *(pi.p_ptr);
		WriteData	(nSize);
		Write			(pData, nSize);
	}

//	Считать данные в CPtr<TYPE> Смещение увеличивается.
// Внимание: class TYPE должен не содержать указателей,
// не иметь виртуальных методов и кнструкторов.
// Загружаемый объект должен быть очищен -- вызови CPtr::Erase
	public: void ReadData (CPtr_info pi)
	{
		DEBUG_STACK_NAME (ReadData);

		if (*pi.p_ptr)
		{
			SERVER_DEBUG_ERROR ("ReadData: Загружаемый объект класса CPtr уже хранит данные");
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

// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (size_t&			data)		{Read (&data, sizeof (size_t));}
// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (int&				data)		{Read (&data, sizeof (data));}
// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (bool&				data)		{Read (&data, sizeof (data));}
// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (char&				data)		{Read (&data, sizeof (data));}
// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (float&			data)		{Read (&data, sizeof (data));}
// Считать типизированные данные по ссылке (int, bool, ..., identifier). Смещение увеличивается.
	void ReadData (identifier&		data)		{Read (&data, sizeof (data));}

// Считать и раскодировать "string". Смещение увеличивается.
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


// Узнать максимальный размер, который занимает файл (кластер).
	size_t GetMaxSize()
	{
		DEBUG_STACK_NAME (GetMaxSize);

		return FD.GetMaxSize(m_nID);
	}

// Узнать максимальный размер, который занимает файл с указанным идентификатором.
	static size_t GetMaxSize(identifier nID)
	{
		DEBUG_STACK_NAME (GetMaxSize);

		return FD.GetMaxSize(nID);
	}

// Установть файлу новый размер. Память перевыделяется. Смещение ставится на начало
// NOTE: Размер не может быть равным нулю!
	void SetSize(size_t nSize)
	{
		DEBUG_STACK_NAME (SetSize);

		if (!IsValid())
		{
			SERVER_DEBUG_ERROR ("Write: Некорректный файл.");
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