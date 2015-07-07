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
[] Description:     ���������� ����
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
		sprintf (Error, "������ ������ %s::CSmartField%s -- ���� ���������������� �� ���������", className[classID], m_item!=NA?"[]":""); \
		theServerDebug.Value(__FILE__, __LINE__, "������", Error);									\
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
		sprintf (Error, "������ ������ %s::CSmartField%s -- ���� ���������������� �� ���������", className[classID], m_item!=NA?"[]":""); \
		theServerDebug.Value(__FILE__, __LINE__, "������", Error);									\
		if (SD_ASSERT (__FILE__, __LINE__, "", Error))													\
		DBG_STOP_ASK;																								\
	}																													\
	return _rv;
//----------------------------------------------------------------------------------------[] 


struct CIndexInfo;
//______________________________________________________________________________
//                                                                            []
//` ������� ����																					[]
//                                                                            []
template <class OD, class FT> class CSmartField
{
// ���� ����� ��������� ���� ������
// ������������ ��������� ���� ������.
	protected: void _About_class_CSmartField(){};
// ������������� ������ �������
   public:    identifier			classID;
// ���������� ������������� ��� ������� � ������ ����� OBD
	protected:	OBD_pointer *		m_pCoPtr;
// ��������� �� ���� ���������, �������� ������
	protected:	FT OD::*				m_field;
// ��������� �� ����-������ ���������, �������� ������
	protected:	CPtr<FT> OD::*		m_fieldArr;
// �������� ��������-������� � ����-�������
	protected:	identifier			m_item;
// ������������� ����
	protected:	identifier			m_FieldID;

//______________________________________________________________________________
//                                                                            []
//` ������������� � ���������������															[]
//                                                                            []
//
// ����������� ����������� ����
	public: CSmartField ()
	{
		classID			= NA;
		m_pCoPtr			= NULL;
		m_item			= NA;
		m_field			= NULL;
		m_fieldArr		= NULL;
		m_FieldID		= NA;
	}
// ���������� ������������� ����
	public: void _init (identifier _classID, identifier FieldID, OBD_pointer * pCoPtr, FT OD::* field)
	{
		classID			= _classID;
		m_pCoPtr			= pCoPtr;
		m_field			= field;
		m_fieldArr		= NULL;
		m_item			= NA;
		m_FieldID		= FieldID;
	}
// ���������� ������������� ����
	public: void _init (identifier _classID, OBD_pointer * pCoPtr, CPtr<FT> OD::* fieldArr, identifier item)	
	{
		classID		= _classID;
		m_pCoPtr		= pCoPtr;
		m_field		= NULL;
		m_fieldArr	= fieldArr;
		m_item		= item;
		m_FieldID	= NA;
	}
// ����������� �����������
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
//` ������������ ��������																		[]
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
//` ������� ��������																				[]
//                                                                            []
// �������������� �����
	public: operator			FT		()	const 		{GET_FIELD_VALUE; return	fv;			}// L_value = Field;
// ����������
	public: bool operator!			()	const			{GET_FIELD_VALUE; return	!fv;			}// L_value = !Field;
	public: FT   operator~			()	const			{GET_FIELD_VALUE; return	~fv;			}// L_value = ~Field;
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` �������� ��������																			[]
//                                                                            []
// ���������
	public: bool     operator== (const FT& rv) {GET_FIELD_VALUE; return	fv == rv;	}// L_value = (Field == R_value);
	public: bool     operator!= (const FT& rv) {GET_FIELD_VALUE; return	fv != rv;	}// L_value = (Field != R_value);
	public: bool     operator<  (const FT& rv) {GET_FIELD_VALUE; return	fv <  rv;	}// L_value = (Field <  R_value);
	public: bool     operator<= (const FT& rv) {GET_FIELD_VALUE; return	fv <= rv;	}// L_value = (Field <= R_value);
	public: bool     operator>  (const FT& rv) {GET_FIELD_VALUE; return	fv >  rv;	}// L_value = (Field >  R_value);
	public: bool     operator>= (const FT& rv) {GET_FIELD_VALUE; return	fv >= rv;	}// L_value = (Field >= R_value);
// ����������
	public: bool     operator|| (const FT& rv) {GET_FIELD_VALUE; return	fv || rv;	}// L_value = (Field || R_value);
	public: bool     operator&& (const FT& rv) {GET_FIELD_VALUE; return	fv && rv;	}// L_value = (Field && R_value);
	public: FT       operator|  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv |  rv);	}// L_value = (Field |  R_value);
	public: FT       operator&  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv &  rv);	}// L_value = (Field &  R_value);
	public: FT		  operator^  (const FT& rv) {GET_FIELD_VALUE; return	(FT)(fv ^  rv);	}// L_value = (Field ^  R_value); // XOR
// ��������������
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
//` ����-�������																					[]
//                                                                            []
template <class OD, class FT> class CSmartFieldArray
{
// ���� ����� ��������� ����-������� ������
// ������������ ��������� ���� ������.
	protected: void _About_class_CSmartFieldArray(){};

// ������������� ������ �������
   public:    identifier				classID;
// ���������� ������������� ��� ������� � ������ ����� OBD
	protected:	OBD_pointer *			m_pCoPtr;
// ��������� �� ���� ���������, �������� ������
	protected:	CPtr<FT> OD::*			m_fieldArr;
// ���������� ���������� ���� -- ������� ����-�������
	protected:	mutable CSmartField<OD, FT>	m_SmartField;

// ����������� ����������� ����-�������
	public: CSmartFieldArray	()
	{
		classID		= NA;
		m_pCoPtr		= NULL;
		m_fieldArr	= NULL;
	}
// ���������! ����������� ����������� ����������� ����-�������
	protected: CSmartFieldArray (CSmartFieldArray& from)
	{
		SERVER_DEBUG_ERROR_2 ("����������� ����������� ����������� ����-������� �����٨�! %s->%s", className[from.classID], className[classID]);
	}
// ���������� ������������� ����-�������
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
			SERVER_DEBUG_ERROR ("CSmartFieldArray::[] ������ ������� � �������� -- ���� �� ����������������"); \
		}																	\
		m_SmartField._init (classID, m_pCoPtr, m_fieldArr, item);	\
		return m_SmartField;
//----------------------------------------------------------------------------[] 


// ������ � �������� ����-�������
	public: CSmartField<OD,FT> At(int item)
	{
		CMARTFIELD_AT;
	}

// ������ � �������� ����-�������
	public: const CSmartField<OD,FT> At(int item) const
	{
		CMARTFIELD_AT;
	}

// ������ � �������� ����-������� ����� []
	public: CSmartField<OD,FT> operator[] (int item)
	{
		CMARTFIELD_AT;
	}

// ������ � �������� ����-������� ����� []
	public: const CSmartField<OD,FT> operator[] (int item) const
	{
		CMARTFIELD_AT;
	}

// ������� ������� = Erase()
	public: void Delete ()
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Erase ������ �������� ��������� -- ���� �� ����������������");
		}
		OBD_DelObjectFieldArrAllItems<OD,FT> (classID, *m_pCoPtr, m_fieldArr);
	}

// ������� ������� = Delete()
	public: void Erase ()
	{
		Delete ();
	}


// �������� ������ � ���������
	public:	void Alloc (int nSize, const FT& defval)
	{
		CPtr<FT> tmp_arr;
		tmp_arr.Alloc(nSize, defval);
		CopyFrom (tmp_arr);
	}

// ������������ ������ � ���������
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

// ����������� ������ �� ������� ��������� ������ �� ����
	public: int CopyFrom (const FT* ptr, int nSize)
	{
		return OBD_CopyObjectFieldArrAllItemsFromPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, ptr, nSize);
	}

// ����������� ������ �� ������� CPtr
	public: int CopyFrom (const CPtr<FT>& from)
	{
		return OBD_CopyObjectFieldArrAllItemsFromPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, (const FT*) from.GetPtr(), from.GetSize());
	}

// ����������� ������ �� ������� ������� (CPtr)
	public: CSmartFieldArray& operator= (const CPtr<FT>& from)
	{
		CopyFrom (from);
		return *this;
	}

// ����������� ������ �� ������� ����-������� (CSmartFieldArray)
	public: CSmartFieldArray& operator= (const CSmartFieldArray& from)
	{
		const FT	*	ptr	= from.GetPtr();
		size_t		nSize = from.GetSize();
		CopyFrom		(ptr, nSize);
		return *this;
	}

// ����������� ������ �� ������� ����-������� (CSmartFieldArray)
	public: CSmartFieldArray& operator<< (const CSmartFieldArray& from)
	{
		const FT	*	ptr	= from.GetPtr();
		size_t		nSize = from.GetSize();
		CopyFrom		(ptr, nSize);
		return *this;
	}

// ���������! ��������� CSmartFieldArray
	protected: bool operator== (const CSmartFieldArray& to)
	{
		SERVER_DEBUG_ERROR_2 ("��������� (operator==) ���������� �����-�������� �� �����������! %s==%s", className[classID], className[to.classID]);
		return false;
	}

// �������������� � CPtr<..>
// ��������!
// �������� ���������� *�����* ������.
// ��������� �� �� ������� � ���������� � ����!
	public: operator const CPtr<FT> ()
	{
		return GetCPtr();
	}

// �������������� � CPtr<..>
// �������� ���������� *�����* ������ � ���� CPtr<..>.
// ��������!
// ��������� �� �� ������� � ���������� � ����!
	public: const CPtr<FT> GetCPtr () const
	{
		CPtr<FT> cptr;
		OBD_CopyObjectFieldArrAllItemsToCPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, cptr);
		return  cptr;
	}

// ����������� ������ � ������ ������ (CPtr)
	public: int CopyTo (CPtr<FT>& to)
	{
		to.Erase();
		return OBD_CopyObjectFieldArrAllItemsToCPtr<OD,FT> (classID, *m_pCoPtr, m_fieldArr, to);
	}

// ������ ����-�������
	public: int Size () const
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Size ������ ������� � ������� -- ���� �� ����������������");
		}
		return OBD_GetObjectFieldArrSize (classID, *m_pCoPtr, m_fieldArr);
	}
// ������ ����-�������
	public: operator size_t () const {return (size_t)Size();}
// ������ ����-�������
	public: operator int    () const {return (int)Size();}
// ������ ����-�������
	public: operator long   () const {return (long)Size();}
// ������ ����-�������
	public: int  GetSize		() const {return Size();}


// �������� ������� � ����-������
	public: int Add (const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Add ������ ���������� �������� -- ���� �� ����������������");
		}
		return OBD_AddObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value);
	}

// ��������� �������� �� ������� ������� � �����.
	public: int AddFrom (const CPtr<FT>& FromArr)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::AddFrom ������ ���������� �������� -- ���� �� ����������������");
		}
		return OBD_AddFromObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, FromArr);
	}

// �������� ������� � ������
// ���������� ������ �������
	public: int Insert (int item, const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Insert ������ ������� �������� -- ���� �� ����������������");
		}
		return OBD_InsertObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, item, value);
	}

// �������� ������� � ������ ����� � ��������������� �������.
// ���������, ��� ������ ������ ���� ������������ �� �����������.
// ���������� �������, � ������� �������� �������.
	public: int InsertSorted (const FT& value)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::InsertSorted ������ ������� �������� -- ���� �� ����������������");
		}
		return OBD_InsertSortedObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value);
	}

// ���� �����, ��� � CPtr::InsertSorted:
// �������� ������� � ������ ����� � ��������������� �������.
// ���������, ��� ������ ������ ���� ������������ �� �����������.
// ���������� �������, � ������� �������� �������.
	public: int AddSorted (const FT& value)
	{
		return InsertSorted (value);
	}

// ����� ������ ������� � �������, ������ ���������
// ���� �� ������ -- ���������� -1 
// �� ��������� ���������, ��� ������ �� ������������.
	public: int Find (const FT& value, bool bSorted=false) const
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Find ������ ������ �������� -- ���� �� ����������������");
		}
		return OBD_FindObjectFieldArrItem (classID, *m_pCoPtr, m_fieldArr, value, bSorted);
	}

// �������� ������� � ����-������
	public: int operator+= (const FT& value) {return Add (value);}

// ����� ����������� ��������� �� �������� ������
	public: operator const FT * () 
	{
		return GetPtr ();
	}

// ����� ����������� ��������� �� �������� ������
	public: const FT * GetPtr () const
	{
		return OBD_GetObjectFieldArrDataPointer<OD,FT> (classID, *m_pCoPtr, m_fieldArr);
	}

// ������� ������� �� ����-�������
	public: int Del (int item)
	{
		if ((m_pCoPtr==NULL) || ((*m_pCoPtr)==NULL))
		{
			SERVER_DEBUG_ERROR ("CSmartFieldArray::Del ������ �������� �������� -- ���� �� ����������������");
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