/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain                                                 []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            SmartField.h																[]
[] Date:            11.04.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Хитрожопые поля
[]____________________________________________________________________________[]
*/
#ifndef SmartField_H
#define SmartField_H





#define CSF		const CSmartField
#define SF				CSmartField
#define SFA				CSmartFieldArray
#define CSFA	const	CSmartFieldArray



//----------------------------------------------------------------------------------------[] 
#define GET_FIELD_VALUE 																						\
/*!!!+*/ static FT fv;																							\
	if (m_item==NA && m_fieldArr==NULL && m_field!=NULL)												\
		fv = OBD_GetObjectFieldValue<OD, FT> (classID, *m_pCoPtr, m_field);						\
	else if (m_item!=NA && m_fieldArr!=NULL && m_field==NULL)										\
		fv = OBD_GetObjectFieldArrValue<OD, FT> (classID, *m_pCoPtr, m_fieldArr, m_item);	\
	else																												\
	{																													\
		char Error[1024]; 																						\
		sprintf (Error, "Ошибка чтения %s::CSmartField%s -- поле инициализировано не корректно", className[classID], m_item!=NA?"[]":""); \
		theServerDebug.Value(__FILE__, __LINE__, "Ошибка", Error);									\
		if (SD_ASSERT (__FILE__, __LINE__, "", Error))													\
		DBG_STOP_ASK;																								\
	}
//----------------------------------------------------------------------------------------[] 
#define PUT_FIELD_VALUE(_rv)																					\
	if (m_item==NA && m_fieldArr==NULL && m_field!=NULL)												\
		OBD_PutObjectFieldValue<OD, FT>																		\
			(m_FieldID, classID, *m_pCoPtr, m_field, _rv);												\
	else if (m_item!=NA && m_fieldArr!=NULL && m_field==NULL)										\
		OBD_PutObjectFieldArrValue<OD, FT> (classID, *m_pCoPtr, m_fieldArr, m_item, _rv);	\
	else																												\
	{																													\
		char Error[1024]; 																						\
		sprintf (Error, "Ошибка записи %s::CSmartField%s -- поле инициализировано не корректно", className[classID], m_item!=NA?"[]":""); \
		theServerDebug.Value(__FILE__, __LINE__, "Ошибка", Error);									\
		if (SD_ASSERT (__FILE__, __LINE__, "", Error))													\
		DBG_STOP_ASK;																								\
	}																													\
	return _rv;
//----------------------------------------------------------------------------------------[] 


struct CIndexInfo;
//______________________________________________________________________________
//                                                                            []
//` Простые поля																					[]
//                                                                            []
template <class OD, class FT> class CSmartField
{
// Этот класс реализует поля данных
// контроллеров объектной базы данных.
	protected: void _About_class_CSmartField(){};
// Идентификатор класса объекта
   public:    identifier			classID;
// Внутренний идентификатор для доступа к данным через OBD
	protected:	OBD_pointer *		m_pCoPtr;
// Указатель на поле структуры, хранящей данные
	protected:	FT OD::*				m_field;
// Указатель на поле-массив структуры, хранящей данные
	protected:	CPtr<FT> OD::*		m_fieldArr;
// Значение элемента-индекса в поле-массиве
	protected:	identifier			m_item;
// Идентификатор поля
	protected:	identifier			m_FieldID;

//______________________________________________________________________________
//                                                                            []
//` Инициализация и конструирование															[]
//                                                                            []
//
// Конструктор хитрожопого поля
	public: CSmartField ()
	{
		classID			= NA;
		m_pCoPtr			= NULL;
		m_item			= NA;
		m_field			= NULL;
		m_fieldArr		= NULL;
		m_FieldID		= NA;
	}
// Внутренняя инициализация поля
	public: void _init (identifier _classID, identifier FieldID, OBD_pointer * pCoPtr, FT OD::* field)
	{
		classID			= _classID;
		m_pCoPtr			= pCoPtr;
		m_field			= field;
		m_fieldArr		= NULL;
		m_item			= NA;
		m_FieldID		= FieldID;
	}
// Внутренняя инициализация поля
	public: void _init (identifier _classID, OBD_pointer * pCoPtr, CPtr<FT> OD::* fieldArr, identifier item)	
	{
		classID		= _classID;
		m_pCoPtr		= pCoPtr;
		m_field		= NULL;
		m_fieldArr	= fieldArr;
		m_item		= item;
		m_FieldID	= NA;
	}
// Конструктор сопирования
	public: CSmartField (const CSmartField& from)
	{
		classID			= from.classID;
		m_pCoPtr			= from.m_pCoPtr;
		m_item			= from.m_item;
		m_field			= from.m_field;
		m_fieldArr		= from.m_fieldArr;
		m_FieldID		= from.m_FieldID;
	}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Присваивание значений																		[]
//                                                                            []
	public: const FT operator=  (CSF& rv)		   {						PUT_FIELD_VALUE( (FT)		rv  );}// Field  = Filed_R_value;
	public: const FT operator<< (CSF& rv)		   {						PUT_FIELD_VALUE( (FT)		rv  );}// Field  = Filed_R_value;
	public: const FT operator=  (FT rv)			   {						PUT_FIELD_VALUE(           rv  );}// Field  = R_value;
	public: const FT operator+= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv + rv) );}// Field += R_value;
	public: const FT operator-= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv - rv) );}// Field -= R_value;
	public: const FT operator*= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv * rv) );}// Field *= R_value;
	public: const FT operator/= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv / rv) );}// Field /= R_value;
	public: const FT operator%= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv % rv) );}// Field %= R_value;
	public: const FT operator&= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv & rv) );}// Field &= R_value;
	public: const FT operator|= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv | rv) );}// Field |= R_value;
	public: const FT operator^= (const FT& rv)   {GET_FIELD_VALUE; PUT_FIELD_VALUE( (FT)(fv ^ rv) );}// Field ^= R_value;

//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Унарные операции																				[]
//                                                                            []
// Преобразование типов
	public: operator			FT		()	const 		{GET_FIELD_VALUE; return	fv;			}// L_value = Field;
// Логические
	public: bool operator!			()	const			{GET_FIELD_VALUE; return	!fv;			}// L_value = !Field;
	public: FT   operator~			()	const			{GET_FIELD_VALUE; return	~fv;			}// L_value = ~Field;
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Бинарные операции																			[]
//                                                                            []
// Сравнение
	public: bool     operator== (const FT& rv) {GET_FIELD_VALUE; return	fv == rv;	}// L_value = (Field == R_value);
	public: bool     operator!= (const FT& rv) {GET_FIELD_VALUE; return	fv != rv;	}// L_value = (Field != R_value);
	public: bool     operator<  (const FT& rv) {GET_FIELD_VALUE; return	fv <  rv;	}// L_value = (Field <  R_value);
	public: bool     operator<= (const FT& rv) {GET_FIELD_VALUE; return	fv <= rv;	}// L_value = (Field <= R_value);
	public: bool     operator>  (const FT& rv) {GET_FIELD_VALUE; return	fv >  rv;	}// L_value = (Field >  R_value);
	public: bool     operator>= (const FT& rv) {GET_FIELD_VALUE; return	fv >= rv;	}// L_value = (Field >= R_value);
// Логические
	public: bool     operator|| (const FT& rv) {GET_FIELD_VALUE; return	fv || rv;	}// L_value = (Field || R_value);
	public: bool     operator&& (const FT& rv) {GET_FIELD_VALUE; return	fv && rv;	}// L_value = (Field && R_value);
	public: FT       operator|  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv |  rv);	}// L_value = (Field |  R_value);
	public: FT       operator&  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv &  rv);	}// L_value = (Field &  R_value);
	public: FT		  operator^  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv ^  rv);	}// L_value = (Field ^  R_value); // XOR
// Арифметические
	public: const FT operator+  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv +  rv);	}// L_value = (Field + R_value);
	public: const FT operator-  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv -  rv);	}// L_value = (Field - R_value);
	public: const FT operator*  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv *  rv);	}// L_value = (Field * R_value);
	public: const FT operator/  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv /  rv);	}// L_value = (Field / R_value);
	public: const FT operator%  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv %  rv);	}// L_value = (Field % R_value);

	public: bool     operator== (const CSmartField& rv) {GET_FIELD_VALUE; FT ffv = fv; return	rv == ffv;}// L_value = (Field == R_value);
};
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Поля-массивы																					[]
//                                                                            []
template <class OD, class FT> class CSmartFieldArray
{
// Этот класс реализует поля-массивы данных
// контроллеров объектной базы данных.
	protected: void _About_class_CSmartFieldArray(){};

// Идентификатор класса объекта
   public:    identifier				classID;
// Внутренний идентификатор для доступа к данным через OBD
	protected:	OBD_pointer *			m_pCoPtr;
// Указатель на поле структуры, хранящей данные
	protected:	CPtr<FT> OD::*			m_fieldArr;
// Внутреннее хитрожопое поле -- элемент поля-массива
	protected:	mutable CSmartField<OD, FT>	m_SmartField;

// Конструктор хитрожопого поля-массива
	public: CSmartFieldArray	()
	{
		classID		= NA;
		m_pCoPtr		= NULL;
		m_fieldArr	= NULL;
	}
// ЗАПРЕЩЕНО! Конструктор копирования хитрожопого поля-массива
	protected: CSmartFieldArray (CSmartFieldArray& from)
	{
		SERVER_DEBUG_ERROR_2 ("Конструктор копирования хитрожопого поля-массива ЗАПРЕЩЁН! %s->%s", className[from.classID], className[classID]);
	}
// Внутренняя инициализация поля-массива
	public: void _init (identifier _classID, identifier, OBD_pointer * pCoPtr, CPtr<FT> OD::* fieldArr)	
	{
		classID	  = _classID;
		m_pCoPtr   = pCoPtr; 
		m_fieldArr = fieldArr;
	}

//----------------------------------------------------------------------------[] 
#define CMARTFIELD_AT												\
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))			\
		{																	\
			SERVER_DEBUG_ERROR ("CSmartFieldArray::[] Ошибка доступа к элементу -- поле не инициализировано"); \
		}																	\
		m_SmartField._init (classID, m_pCoPtr, m_fieldArr, item);	\
		return m_SmartField;
//----------------------------------------------------------------------------[] 


// Доступ к элементу поля-массива
	public: CSmartField<OD,FT> At(int item)
	{
		CMARTFIELD_AT;
	}

// Доступ к элементу поля-массива
	public: const CSmartField<OD,FT> At(int item) const
	{
		CMARTFIELD_AT;
	}

// Доступ к элементу поля-массива через []
	public: CSmartField<OD,FT> operator[] (int item)
	{
		CMARTFIELD_AT;
	}

// Доступ к элементу поля-массива через []
	public: const CSmartField<OD,FT> operator[] (int item) const
	{
		CMARTFIELD_AT;
	}

// Очистка массива = Erase()
	public: void Delete ()
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Erase Ошибка удаления элементов -- поле не инициализировано");
		}
		OBD_DelObjectFieldArrAllItems<OD,FT> (classID, *m_pCoPtr, m_fieldArr);
	}

// Очистка массива = Delete()
	public: void Erase ()
	{
		Delete ();
	}


// Выделить память в элементах
	public:	void Alloc (int nSize, const FT& defval)
	{
		CPtr<FT> tmp_arr;
		tmp_arr.Alloc(nSize, defval);
		CopyFrom (tmp_arr);
	}

// Перевыделить память в элементах
	public:	void Realloc (int nSize, const FT& defval)
	{
		size_t	oldSize =GetSize();
		CPtr<FT> tmp_arr;
		CopyTo	(tmp_arr);

		tmp_arr.Realloc	(nSize);


		for (int i=oldSize; i<nSize; i++) 
		{
			tmp_arr[i] = defval;
		}
		CopyFrom	(tmp_arr);
	}

// Копирование данных из массива элементов такого же типа
	public: int CopyFrom (const FT* ptr, int nSize)
	{
		return OBD_CopyObjectFieldArrAllItemsFromPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, ptr, nSize);
	}

// Копирование данных из массива CPtr
	public: int CopyFrom (const CPtr<FT>& from)
	{
		return OBD_CopyObjectFieldArrAllItemsFromPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, (const FT*) from.GetPtr(), from.GetSize());
	}

// Копирование данных из другого массива (CPtr)
	public: CSmartFieldArray& operator= (const CPtr<FT>& from)
	{
		CopyFrom (from);
		return *this;
	}

// Копирование данных из другого поля-массива (CSmartFieldArray)
	public: CSmartFieldArray& operator= (const CSmartFieldArray& from)
	{
		const FT	*	ptr	= from.GetPtr();
		size_t		nSize = from.GetSize();
		CopyFrom		(ptr, nSize);
		return *this;
	}

// Копирование данных из другого поля-массива (CSmartFieldArray)
	public: CSmartFieldArray& operator<< (const CSmartFieldArray& from)
	{
		const FT	*	ptr	= from.GetPtr();
		size_t		nSize = from.GetSize();
		CopyFrom		(ptr, nSize);
		return *this;
	}

// ЗАПРЕЩЕНО! Сравнение CSmartFieldArray
	protected: bool operator== (const CSmartFieldArray& to)
	{
		SERVER_DEBUG_ERROR_2 ("Сравнение (operator==) хитрожопых полей-массивов не реализовано! %s==%s", className[classID], className[to.classID]);
		return false;
	}

// Преобразование к CPtr<..>
// ВНИМАНИЕ!
// Оператор возвращает *копию* данных.
// Изменение их не приведёт к изменениям в базе!
	public: operator const CPtr<FT> ()
	{
		return GetCPtr();
	}

// Преобразование к CPtr<..>
// Оператор возвращает *копию* данных в виде CPtr<..>.
// ВНИМАНИЕ!
// Изменение их не приведёт к изменениям в базе!
	public: const CPtr<FT> GetCPtr () const
	{
		CPtr<FT> cptr;
		OBD_CopyObjectFieldArrAllItemsToCPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, cptr);
		return  cptr;
	}

// Копирование данных в другой массив (CPtr)
	public: int CopyTo (CPtr<FT>& to)
	{
		to.Erase();
		return OBD_CopyObjectFieldArrAllItemsToCPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, to);
	}

// Размер поля-массива
	public: int Size () const
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Size Ошибка доступа к массиву -- поле не инициализировано");
		}
		return OBD_GetObjectFieldArrSize (classID, *m_pCoPtr, m_fieldArr);
	}
// Размер поля-массива
	public: operator size_t () const {return (size_t)Size();}
// Размер поля-массива
	public: operator int    () const {return (int)Size();}
// Размер поля-массива
	public: operator long   () const {return (long)Size();}
// Размер поля-массива
	public: int  GetSize		() const {return Size();}


// Добавить элемент в поле-массив
	public: int Add (const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Add Ошибка добавления элемента -- поле не инициализировано");
		}
		return OBD_AddObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value);
	}

// Добавляет элементы из другого массива к своим.
	public: int AddFrom (const CPtr<FT>& FromArr)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::AddFrom Ошибка добавления элемента -- поле не инициализировано");
		}
		return OBD_AddFromObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, FromArr);
	}

// Вставить элемент в массив
// Возвращает размер массива
	public: int Insert (int item, const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Insert Ошибка вставки элемента -- поле не инициализировано");
		}
		return OBD_InsertObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, item, value);
	}

// Вставить элемент в нужное место в отсортированном массиве.
// Считается, что массив должен быть отсотрирован по возрастанию.
// Возвращает позицию, в которую вставлен элемент.
	public: int InsertSorted (const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::InsertSorted Ошибка вставки элемента -- поле не инициализировано");
		}
		return OBD_InsertSortedObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value);
	}

// Тоже самое, что и CPtr::InsertSorted:
// Вставить элемент в нужное место в отсортированном массиве.
// Считается, что массив должен быть отсотрирован по возрастанию.
// Возвращает позицию, в которую вставлен элемент.
	public: int AddSorted (const FT& value)
	{
		return InsertSorted (value);
	}

// Найти первый элемент в массиве, равный аргументу
// Если не найден -- возвращает -1 
// По умолчанию считается, что массив не отсортирован.
	public: int Find (const FT& value, bool bSorted=false) const
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Find Ошибка поиска элемента -- поле не инициализировано");
		}
		return OBD_FindObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value, bSorted);
	}

// Добавить элемент в поле-массив
	public: int operator+= (const FT& value) {return Add (value);}

// Взять константный указатель на хранимые данные
	public: operator const FT * () 
	{
		return GetPtr ();
	}

// Взять константный указатель на хранимые данные
	public: const FT * GetPtr () const
	{
		return OBD_GetObjectFieldArrDataPointer<OD,FT> (classID, *m_pCoPtr, m_fieldArr);
	}

// Удалить элемент из поля-массива
	public: int Del (int item)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Del Ошибка удаления элемента -- поле не инициализировано");
		}
		return OBD_DelObjectFieldArrItem<OD,FT> (classID, *m_pCoPtr, m_fieldArr, item);
	}
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