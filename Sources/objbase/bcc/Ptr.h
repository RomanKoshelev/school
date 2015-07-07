/*
________________________________________________________________________________
[] 																									[]
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.												[]
[] All rights reserved. 																		[]
[] __________________________________________________________________________ []
[] 																									[]
[] Name: 			  Ptr.h																		[]
[] Date: 			  02/03/99																	[]
[] Author:			  Roman V. Koshelev														[]
[] Description:	  Шаблон для создания массивов различного типа					[]
[] Last Modified:   10.11.1999 [ 21:32:46 ] by Roman V. Koshelev              []                                            
[]____________________________________________________________________________[]
*/
#ifndef Ptr_H
#define Ptr_H

/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[]` CPtr
[] 																									[]
[]____________________________________________________________________________[]
*/

#define GROW(n) ((n) + max (2, (n)/4))


//RVK:>>>
// Информацция о масссиве элементов CPtr<..>
struct CPtr_info
{
	void		** p_ptr;
	size_t	 * p_size;
	size_t	 * p_real_size;
	size_t		item_size;
};

//RVK:>>>
// Массив элементов
template <class T> class CPtr
{
protected:
// Класс CPtr<TYPE> реализует объекты-указатели 
// (массивы) объектов типа TYPE
// 	CPtr<int> arr = 100; // Выделили память в 100 элементов
// 	arr[99]=99;
// 	arr.Add(665);
// 	arr[100] = -100;
	void About_class_CPtr (){};

// CPtr:: Указатель, выделяющий или ссылающийся на чужую память
	T *		m_pData;
// CPtr:: Элемент-затычка, возвращается при ошибочном обращении к массиву.
	T			_m_StubItem;
// CPtr:: Размер маccива в элементах
	size_t	m_nSize;
// CPtr:: Реальный размер выделенной памяти в элементах
	size_t	m_nRealSize;


// CPtr:: Очистить выделенную память и уничтожить элеметны
	public:	void Delete()
	{
		Alloc (0);
		SERVER_DEBUG_ASSERT (m_pData==NULL, "CPtr::Delete -- m_pData!=NULL");
	}

// CPtr:: Очистить выделенную память, не вызывая деструкторы элементов
	public:	void Erase()
	{
		Realloc (0);
	}

// CPtr:: Внутренняя инициализация
	protected:	void Init ()
	{
		m_nRealSize 		= 0;
		m_nSize				= 0;
		m_pData				= (T *)NULL;
	}

// CPtr:: Пустой конструктор -- память не выделена
	public:	CPtr ()
	{
		Init	 ();
	}

// CPtr:: Конструктор копирования
	public:	CPtr (const CPtr& from)
	{
		Init ();
		Copy (from.m_pData, from.m_nSize);
	}

// CPtr:: Конструктор -- выделение памяти в элеметах
	public:	CPtr (int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr:: Конструктор -- указано отрицательное значение размера %d", nSize);
			nSize = 0;			
		}
		Init	();
		Alloc (nSize);
	}


// CPtr:: Конструктор -- выделение и копирование из указателя
	public:	CPtr (const T * ptr, int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr:: указано отрицательное значение размера %d", nSize);
			nSize = 0;			
		}
		Init ();
		Copy (ptr, nSize);
	}


// CPtr:: Деструктор освобождает память, если массив сам её выделял
	public:	~CPtr()
	{
		if(m_pData) 
		{
			delete [] m_pData;
		}
	}

// Взять указатель на хранимые данные
	public: T * GetPtr() const
	{
		return m_pData;
	}

// Взять указатель на хранимые данные
	public:	operator void * () const
	{
		return (void*)GetPtr();
	}


// CPtr:: Получить информацию о массиве
	public:	operator CPtr_info ()
	{
		CPtr_info pi;
		pi.p_ptr 		= (void **)&m_pData;
		pi.p_size		= &m_nSize;
		pi.p_real_size = &m_nRealSize;
		pi.item_size	= sizeof (T);
		return pi;
	}

// CPtr:: Получить ссылку на элемент через []
	public:	T & operator [] (int nIndex)
	{
		return At (nIndex);
	}


// Найти первый элемент в массиве, равный аргументу
// Если не найден -- возвращает -1
// Второй аргумент указывает на то, что массив отсортирован.
// По умолчанию считается, что массив не отсортирован.
	int Find (const T& aItem, bool bSorted=false, bool bExact=true) const
	{
		if (m_nSize==0)
		{
			return -1;
		}

		int i=0;
		
		//----------------------------------------------------------------------------[] 
		if (bSorted)
		{
			int iL=0;
			int iR=m_nSize-1;
			int iF=-1;
			for (i=0; i<=(int)m_nSize; i++)
			{
				int iC = (iR+iL)/2;
				if (aItem < m_pData[iC])
					iR = iC;
				else 
					iL = iC;

				if (iR-iL <= 1)
				{
					if (aItem == m_pData[iL])
						iF = iL;
					else if (aItem == m_pData[iR])
						iF = iR;
					else if (!bExact)
					{
						for (int j=min (iL,iR); j<(int)m_nSize; j++)
						{
							if (aItem <= m_pData[j])
								return j;
						}
						return (int)m_nSize;
					}
					else return -1;
				}
				if (iF!=-1)
				{
					for (int j=iF; j>=0; j--)
					{
						if (aItem == m_pData[j])
							iF = j;
						else 
							return iF;
					}
					return iF;
				}
			}

			SERVER_DEBUG_ERROR ("CPtr::Find: Поиск в неотсортированном массиве с флагом bSorted=true.");
			return Find (aItem, false);
		}
		//----------------------------------------------------------------------------[] 


		//----------------------------------------------------------------------------[] 
		for (i=0; i<(int)m_nSize; i++) if (m_pData[i]==aItem)
		{
			return i;
		}
		return -1;		
	}


// CPtr:: Получить ссылку на элемент через []
	public:	const T & operator [] (int nIndex) const
	{
		return At (nIndex);
	}

// CPtr:: Получить ссылку на элемент
	public:	T& At (int nIndex)
	{
		if ((nIndex<0) || (nIndex>=(int)m_nSize))
		{
			SERVER_DEBUG_ERROR_2 ("CPtr<...>[%d] -- Выход за пределы массива. m_nSize=%d.", nIndex, m_nSize);
			return _m_StubItem;
		}
		if (m_nSize>m_nRealSize)
		{
			SERVER_DEBUG_ERROR ("m_nSize>m_nRealSize");
			return _m_StubItem;
		}
		return m_pData[nIndex];
	}

// CPtr:: Получить ссылку на элемент
	public:	const T & At (int nIndex) const
	{
		if ((nIndex<0) || (nIndex>=(int)m_nSize))
		{
			SERVER_DEBUG_ERROR_2 ("CPtr<...>[%d] -- Выход за пределы массива. m_nSize=%d.", nIndex, m_nSize);
			return _m_StubItem;
		}
		if (m_nSize>m_nRealSize)
		{
			SERVER_DEBUG_ERROR ("m_nSize>m_nRealSize");
			return _m_StubItem;
		}
		return m_pData[nIndex];
	}

// CPtr:: Преобразование к типу -- аргументу шаблона
	public:	T & operator * ()
	{
		return *m_pData;
	}

// CPtr:: Получить указатель прибавлением смещения в элементах
	public:	T * operator + (int nOffset)
	{
		return m_pData+nOffset;
	}

// CPtr:: Получить указатель вычитанием смещения в элементах
	public:	T * operator - (int nOffset)
	{
		return m_pData-nOffset;
	}

// CPtr:: Вычесть указатели -- результат в элементах
	public:	int operator - (T * pPtr)
	{
		return m_pData-pPtr;
	}

// CPtr:: Выделить память в элементах
// CPtr:: Выделить память в элементах и заполинть элементами
	public:	void Alloc (int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr:: указано отрицательное значение размера %d", nSize);
			nSize = 0;			
		}
		if(m_pData)
		{
			delete [] m_pData;
			m_pData = NULL;
		}
		m_nRealSize =	nSize;
		m_nSize		=	nSize;
		if (nSize!=NULL)
		{
			m_pData=new T[m_nRealSize];
			SERVER_DEBUG_ASSERT (m_pData, "Cannot allocate memory");
			if(!m_pData) 
			{
				Init ();
				return ;
			}
		}
	}

// CPtr:: Выделить память в элементах
// CPtr:: Выделить память в элементах и заполинть элементами
	public:	void Alloc(int nSize, const T& value)
	{
		Alloc (nSize);
		Fill  (value);
	}
	

// CPtr:: Перевыделить память в элементах.
// В отличие от Alloc, не теряет значения элементов.
	public: void Realloc (int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr:: Указано отрицательное значение размера %d", nSize);
			nSize = 0;			
		}
		if(nSize>(int)m_nRealSize)
		{
			int nGrowSize = GROW (nSize);
			T * pNewPtr = new T [nGrowSize];
			for (size_t i=0; i<m_nRealSize; i++)
				pNewPtr[i] = m_pData[i];
			if (m_pData)
				delete [] m_pData;
			m_pData=(T *)pNewPtr; 
			m_nRealSize = nGrowSize;
		}
		m_nSize=nSize;
	}

// CPtr:: Добавить элемент в массив = [operator +=]
	public:	void Add (const T& value)
	{
		Realloc(m_nSize+1);
		m_pData[m_nSize-1] = value;
		SERVER_DEBUG_ASSERT (m_nSize<=m_nRealSize, "m_nSize>m_nRealSize");
	}


// CPtr:: Установить элементы массива равными заданному значению
	public:	void Fill (const T& value)
	{
		for (unsigned i = 0; i < m_nSize; i++)
			m_pData[i] = value;
	}

// CPtr:: Вернуть число элементов массива, равных параметру
	public:	int GetItemNum (const T& value, bool Sorted = false)
	{
		int			Count = 0;
		unsigned 	i;

		switch (Sorted)
		{
		case false:
			for (i = 0; i < m_nSize; i++)
				if (m_pData[i] == value)
					Count++;
			break;

		case true:
			i = Find(value, true);
			if (i >= 0)
				do
				{
					Count++;
					i++;
				} while (m_pData[i] == value);
			break;
		}

		return Count;
	}


// CPtr:: Добавить элемент в массив = Add()
	public:	CPtr& operator+= (const T& value)
	{
		Add (value);
		return *this;
	}

// CPtr:: Удалить элемент из массива = Remove
	public:	void Del (int item)
	{
		if ((item>=0) && (item<(int)m_nSize) && (m_nSize>0))
		{
			for (int i=item; i<(int)m_nSize-1; i++)
				m_pData[i] = m_pData[i+1];
			Realloc (m_nSize-1);
		}
		else
		{
			SERVER_DEBUG_ERROR_2 ("CPtr<..>[%d]::Del (%d) -- Удаляемый элемент за пределами массива", m_nSize, item);
		}
	}

// CPtr:: Удалить элемент из массива = Del
	public:	void Remove (int item)
	{
		Del (item);
	}

// CPtr:: Вставить новый элемент на место item
// Возвращает позицию, на которую был вставлен элемент.
	public:	int Insert (int item, const T& value)
	{
		if (item<0)
		{
			item = 0;
		}
		if (item >= (int)m_nSize)
		{
			Add (value);
			return m_nSize -1;
		}
		Add (value);
		int i;
		T   tmp;
		tmp = m_pData[m_nSize-1];
		for (i=m_nSize-1; i>item; i--)
		{
			m_pData[i] = m_pData[i-1];
		}
		m_pData[item] = tmp;
		return item;
	}

// CPtr:: Вставить элемент в нужное место в отсортированном массиве
// Возвращает позицию, в которую вставлен элемент
	public:	int InsertSorted (const T& value)
	{
		int item = Find (value, true, false);
		return Insert (item, value);
	}

// Тоже самое, что и CPtr::InsertSorted:
// CPtr:: Вставить элемент в нужное место в отсортированном массиве
// Возвращает позицию, в которую вставлен элемент
	public:	int AddtSorted (const T& value)
	{
		return InsertSorted (value);
	}

// CPtr:: 
// Копировать все элементы из другого массива на место своих.
// Теряет старые данные. Память выделяется.
	public:	CPtr& operator = (const CPtr<T>& from)
	{
		Copy (from.m_pData, from.m_nSize);
		return * this;
	}

#if 0  //{ RomanVK !!!
// CPtr:: 
// 1. Копировать все элементы из другого массива на место своих.
// Теряет старые данные. Память выделяется.
// 2. Сохранить указатель. Теряет старые данные. 
// Память не выделяется и указатель не удаляется деструктором.
	public:	CPtr& operator = (void *pData)
	{
		if(m_pData) {
			delete [] m_pData;
		}
		m_pData = (T*) pData;
		return    *this;
	}
#endif //}


// CPtr:: Копировать все элементы из другого массива на место своих.
// Теряет старые данные. Память выделяется. = CopyFrom()
	public:	int Copy (const T * ptr, int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr::Copy Указано отрицательное значение размера %d", nSize);
			return 0;			
		}
		Alloc(nSize);
		for (int i=0; i<nSize; i++)
			m_pData[i] = ptr[i];

		return nSize;
	}

// CPtr:: Копировать все элементы из другого массива на место своих.
// Теряет старые данные. Память выделяется. = Copy()
	public:	int CopyFrom (const T * ptr, int nSize)
	{
		return Copy (ptr, nSize);
	}

// CPtr:: Добавляет элементы из другого массива к своим.
	public:	int AddFrom (const T * ptr, int nSize)
	{
		if (nSize<0)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr::AddFrom Указано отрицательное значение размера %d", nSize);
			return 0;			
		}

		int oldSize = m_nSize;
		Realloc(m_nSize + nSize);

		for (int i=0; i<nSize; i++)
			m_pData[oldSize + i] = ptr[i];

		return m_nSize;
	}


// CPtr:: Выделить память и считать в неё 		
// данные из файла OS, открытого по имени.
	public:	size_t ReadFile(const char *fileName)
	{
		FILE *srcFile=fopen(fileName,"rb");
		if (srcFile==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr::ReadFile Ошибка открытия файла %s", fileName);
			return 0;
		}
		fseek(srcFile,0,SEEK_END);
		long nSrcLength=ftell(srcFile);
		fseek(srcFile,0,SEEK_SET);
		Alloc(nSrcLength+1);
		fread(m_pData,nSrcLength,1,srcFile);
		fclose(srcFile);
		return nSrcLength;
	}

// CPtr:: Записать в файл OS, открытого по имени,
// данные из выделенной памяти. Файл создаётся и 
// теряет старое содержимое.
	public:	size_t WriteFile(const char *fileName)
	{
		FILE *srcFile=fopen(fileName,"wb");
		if (srcFile==NULL)
		{
			SERVER_DEBUG_ERROR_1 ("CPtr::WriteFile Ошибка открытия файла %s", fileName);
			return 0;
		}
		fwrite(m_pData,m_nSize,1,srcFile);
		fclose(srcFile);
		return m_nSize;
	}

// CPtr:: Получить размер выделенной памяти в элементах = GetSize()
	public:	int Size() const
	{
		return m_nSize;	
	}

// CPtr:: Получить размер выделенной памяти в элементах = Size()
	public:	int GetSize() const
	{
		return Size();
	}

// Отсортировать элементы по возрастанию
// Только для тех классов-элементов, у которых определены
// необходимые операторы сравнения.
	public: void Sort ()
	{
		CPtr<T> Tmp;
		Tmp = *this;
		T*		pTmp = Tmp.GetPtr ();
		int   nSize= Tmp.Size	();
		Erase ();
		for (int j=0; j<nSize; j++)
		{
			InsertSorted (pTmp[j]);
		}

#if 0  //{ RomanVK
		int i = 0;
		int j = 0;
		for (i=0; i<(int)m_nSize-1; i++)
		{
			int jMax=i;
			for (j=i+1; j<(int)m_nSize; j++)
			{
				if (m_pData[j] < m_pData[jMax])
					jMax=j;
			}
			if (m_pData[jMax] < m_pData[i])
			{
				T tmp = m_pData[i];
				m_pData[i]		=	m_pData[jMax];
				m_pData[jMax]	=	tmp;
			}
		}
#endif //}
	}

// Проверка на равенство с другим массивом CPtr
	public: bool operator == (const CPtr<T>& cptr) 
	{
		unsigned	cptrSize		= cptr.Size();
		if (m_nSize != cptrSize) return false;
		T			*cptrData	= cptr.GetPtr();

		for (unsigned i = 0; i < cptrSize; i++) {
			if (m_pData[i] != cptrData[i])
				return false;
		}
		return true;
	}

// Проверка на неравенство с другим массивом CPtr
	public: bool operator != (const CPtr<T>& cptr) 
	{
		return !(*this == cptr);
	}

// Получить номер максимального элемента в массиве
// (первого по порядку, если макс. элементов несколько).
// Возвращает -1, если массив пустой.
	public: int GetMaxNo(void) const
	{
		T		*pMaxItem = NULL;
		int	MaxNo = -1;
	
		for (unsigned i = 0; i < m_nSize; i++)
		{
			if (i > 0)
			{
				if (*pMaxItem < *(m_pData + i))
				{
					pMaxItem = m_pData + i;
					MaxNo		= i;
				}
			}
			else
			{
				pMaxItem = m_pData;
				MaxNo		= 0;
			}
		}

		return MaxNo;
	}

// Получить номер минимального элемента в массиве
// (первого по порядку, если мин. элементов несколько).
// Возвращает -1, если массив пустой.
	public: int GetMinNo(void) const
	{
		T		*pMinItem = NULL;
		int	MinNo = -1;
	
		for (unsigned i = 0; i < m_nSize; i++)
		{
			if (i > 0)
			{
				if (*pMinItem > *(m_pData + i))
				{
					pMinItem = m_pData + i;
					MinNo		= i;
				}
			}
			else
			{
				pMinItem = m_pData;
				MinNo		= 0;
			}
		}

		return MinNo;
	}

			  
//----------------------------------------------------------------------------[] 
















//----------------------------------------------------------------------------[] 
//RVK:>>>
// CPtr:: Итератор
	public: class Iterator
	{
	// Итератор массива позволяет пробегаться по нему без использования
	// квадратных скобок:
	// 	struct MyStruct {int m_Field;};
	// 	CPtr<MyStruct> arr = 100;
	// 	for (CPtr<MyStruct>::Iterator it = arr.begin(); it!=arr.end()/*it.IsValid()*/; it++)
	// 	{
	// 		it->m_Field = it.GetIndex ();
	// 	}
	// Использование итератора подчас позволяет избежать громоздких
	// выражений внутри циклов.
		protected: void About_class_CPtr_Iterator(){};

	// Индекс в итерируемом массиве
		protected: int  m_index;

	// Итерируемый массив
		protected: CPtr <T> *	m_pCPtr;

	// Конструктор по умолчанию
	// Конструктор из другого итератора
		public: Iterator ()
		{
			m_index	= 0;
			m_pCPtr	= NULL;
		}
	// Конструктор по умолчанию
	// Конструктор из другого итератора
		public: Iterator (const Iterator& from)
		{
			m_index = from.m_index;
			m_pCPtr = from.m_pCPtr;
		}
	// Конструктор по умолчанию
	// Конструктор из другого итератора
		public: Iterator (CPtr& from)
		{
			m_index = 0;
			m_pCPtr = &from;
		}

	// Получить индекс в итерируемом массиве
		public: int GetIndex ()
		{
			return m_index;
		}

	// Возможность испльзования итератора -- индекс в 
	// пределах допустимых значений.
		public: bool IsValid ()
		{
			return (m_pCPtr!=NULL) && (m_index>=0) &&  (m_index < m_pCPtr->GetSize());
		}

	// Установить индекс в итерируемом массиве
		public: void SetIndex (int nIndex)
		{
			m_index = nIndex;
		}

	// Текущее значение
		public: operator T& ()
		{
			return m_pCPtr->At(m_index);
		}

	// Текущее значение
		public: T& operator* ()
		{
			return m_pCPtr->At(m_index);
		}

	// Получение доступа к полям текущего элемента, 
	// если он имеет структурный тип.
		public: T* operator-> ()
		{
			return &(m_pCPtr->At(m_index));
		}


	// Проверка итераторов на равенство
		public: bool operator== (Iterator to)	
		{
			return	m_pCPtr && to.m_pCPtr && 
						m_pCPtr == to.m_pCPtr && 
						m_index == to.m_index;
		}

	// Проверка итераторов на неравенство
		public: bool operator!= (Iterator to)	
		{
			return	m_pCPtr && to.m_pCPtr && 
						(m_pCPtr != to.m_pCPtr || 
						m_index != to.m_index);
		}

	// Перейти на следующий элемент
		public: Iterator& operator++ (int)	{m_index++; return (*this);}
	// Перейти на следующий элемент
		public: void GoNext ()					{m_index++;}

	// Перейти на предыдущий элемент
		public: Iterator& operator-- (int)	{m_index--; return (*this);}
	// Перейти на предыдущий элемент
		public: void GoPrev ()					{m_index--;}

	// Передвинуть итератор на N элементов вперёд
		public: Iterator& operator+= (int N)	{m_index+=N; return (*this);}
	// Передвинуть итератор на N элементов назад
		public: Iterator& operator-= (int N)	{m_index-=N; return (*this);}

		friend CPtr<T>;
	};

	
// CPtr:: Итератор - начало массива
	public: const Iterator& begin()
	{
		static Iterator tmp;
		tmp.m_pCPtr = this;
		tmp.m_index = 0;
		return tmp;
	}

// CPtr:: Итератор - конец массива
	public: const Iterator& end()
	{
		static Iterator tmp;
		tmp.m_pCPtr = this;
		tmp.m_index = m_nSize;
		return tmp;
	}
};
//____________________________________________________________________________[]



//______________________________________________________________________________
// 																									[]
//` CompareFunction																				[]
// 																									[]
template <class T> int CompareFunction (const void *Rec1, const void *Rec2)
{
	T* R1 = (T*) Rec1;
	T* R2 = (T*) Rec2;

	return	(*R1)<(*R2)?	-1:
				(*R1)>(*R2)?	 1:
				0;
}
//____________________________________________________________________________[]






#endif
/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/