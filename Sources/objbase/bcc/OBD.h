/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBD.h																		[]
[] Date:            25.03.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Object Base Driver (OBD)												[]
[] Last Modified:																					[]
[]____________________________________________________________________________[]
*/
#ifndef OBD_H
#define OBD_H




extern char * className[];
//------------------------------------------------------------------------------[]
//
// Базовый класс
//
class OD_BASE
{
// Идентификатор класса
   public: identifier  classID;
// Указатели на CObjIndex_AVTree_Item для всех индексов
   OBD_pointer    * m_CoIndexPtr;
};
//------------------------------------------------------------------------------[]


//----------------------------------------------------------------------------[] 
#define IF_OBJECT_INVALID 																		\
	CAbstractObjectInMemory * aObject = _OBD_IsObjectValid (classID, coPtr);	\
	if (aObject==NULL)
//----------------------------------------------------------------------------[] 
#define IF_OBJECT_INVALID_A																	\
	CAbstractObjectInMemory * 																	\
		aObject = _aObject? _aObject: _OBD_IsObjectValid (classID, coPtr);		\
	if (aObject==NULL)
//----------------------------------------------------------------------------[] 


int CompareFunction_identifier (identifier& a, identifier& b);


//#define USE_CHANGE_NOTIFICATION

//----------------------------------------------------------------------------[] 
// Затычки для безмозглых компиляторов.
void *		new_OD						(identifier classID, bool	 bInit);
void			delete_pData				(identifier classID, void * pData);
bool			pData_DebugPrint			(identifier classID, void * pData, string& dbg, identifier objID);
bool			pData_WriteToFile			(identifier classID, void * pData, identifier objID);
size_t		pData_LoadFromFile		(identifier classID, void * pData, identifier objID);
void			pData_m_CoIndexPtr		(identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr);
OBD_pointer pData_m_CoIndexPtr		(identifier classID, void * pData, identifier indexID);
identifier	pData_classID				(identifier classID, void * pData);
void			pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID);
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
enum OBD_FIND
{
	OBD_FIND_Next,
	OBD_FIND_Prev,
	OBD_FIND_First,
	OBD_FIND_Last,
	OBD_FIND_END
};
//----------------------------------------------------------------------------[] 

extern bool			bPrint_ref_count;
extern key_arr *	p_static_ka;
//______________________________________________________________________________
//                                                                            []
// CIndexInfo																						[]
//                                                                            []
struct CIndexInfo
{
	identifier		m_id;
	byte 				m_keyType[MAX_KEY_NUM_IN_INDEX];
	int				m_keyNum;

	void Init ()
	{
		m_id = UNKNOWN;
		for (int i=0; i<MAX_KEY_NUM_IN_INDEX; i++) 
		{
			m_keyType[i] = (byte)FT_nothing;
		}
		m_keyNum = 0;
	}

	CIndexInfo ()	{Init ();}
};
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
// CAbstractObjectInMemory																		[]
//                                                                            []
struct CAbstractObjectInMemory
{
	identifier		classID;
	identifier		objID;
	void			*	pData;
	size_t			ref;
	bool				bChanged;
	bool				bDeleted;

	void			*	pCachePtr;
	size_t			nSize;
	int				nCached;

	CAbstractObjectInMemory ()
	{
		bDeleted			= false;
		bChanged			= false;
		pData				= NULL;
		objID				= UNKNOWN;
		classID			= UNKNOWN;
		ref				= 0;

		pCachePtr		= NULL;
		nSize				= 0;
		nCached			= 0;
	}
	
	//----------------------------------------------------------------------------[]
	DECLARE_COPY_CONSTRUCTORS_BEGIN (CAbstractObjectInMemory)
		CC_COPY (classID			)
		CC_COPY (objID				)
		CC_COPY (pData				)
		CC_COPY (ref				)
		CC_COPY (bChanged			)
		CC_COPY (bDeleted			)
		CC_COPY (pCachePtr		)
		CC_COPY (nSize				)
		CC_COPY (nCached			)		
	DECLARE_COPY_CONSTRUCTORS_END
	//----------------------------------------------------------------------------[] 

	bool Save ()
	{
		if (pData && bChanged)
		{
			OD_BASE * pBase = (OD_BASE *) pData;

			if (pBase->classID!=classID)
			{
				SERVER_DEBUG_ERROR_3 ("Save: objID = %d; pBase->classID(%d)!=classID(%d)", classID, pBase->classID, classID);
				return false;
			}
			if (pData_WriteToFile (classID, (void*) pData, objID))
			{
				bChanged = false;
				return true;
			}
			return false;
		}
		return true;
	}

	~CAbstractObjectInMemory ()
	{
		if (bChanged)
		{
			SERVER_DEBUG_ERROR_1 ("~CAbstractObjectInMemory: Попытка удалить ссылку на несохранённый объект класса %s", className[classID]);
		}
		if (pData)
		{
		// Очищаем данные объекта
			OD_BASE * pBase = (OD_BASE *) pData;
			identifier classID = pBase->classID;
			delete_pData (classID, pData);
			printf(".");
			pData = NULL;
		}
	}

	size_t AddRef  () 
	{
		return ++ref;
	}
	
	size_t Release () 
	{
		if (ref==0)
		{
			SERVER_DEBUG_ERROR ("Release: ref==0");
			return 0;
		}
		return --ref;
	}
};
//____________________________________________________________________________[]


typedef IT_AVTree <CAbstractObjectInMemory, identifier, identifier CAbstractObjectInMemory::*> IT_AVTree_AllObjectsInMemory;
extern  IT_AVTree_AllObjectsInMemory OBD_AllObjectsInMemory;

extern bool CHECK_VALID_IGNORE_DELETED;
extern bool IGNORE_LAST_KEY_IDENTIFIER;





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]  ФУНКЦИИ                                                                   []       
[]                                                                            []
[]____________________________________________________________________________[]
*/


// Корректировка набора ключей -- для случая, если имеет
// место обратная сортировка
void CorrectKeyArr (key_arr& ka, identifier classID, identifier indexID);

// GetObject
OBD_pointer OBD_GetObject (long classID, identifier objID, identifier indexID=NA, OBD_pointer coIndexPtr=NULL);

// OBD_CreateIndexItem
void OBD_CreateIndexItem (long classID, void * pData, identifier objID);;

// OBD_CreateObject
OBD_pointer OBD_CreateObject (long classID, bool bInternal=false);

// OBD_GetClassIdList
void OBD_GetClassIdList (identifier_arr& id_list, long classID, key_arr* pka, const CIndexInfo& indexInfo);

// _OBD_IsObjectValid
CAbstractObjectInMemory* _OBD_IsObjectValid (long classID, OBD_pointer coPtr);

// OBD_GetObjectID
identifier OBD_GetObjectID (long classID, OBD_pointer coPtr);

// OBD_OpenMasterObject
OBD_pointer OBD_OpenMasterObject (long classID);

// OBD_IsObjectValid
bool OBD_IsObjectValid (long classID, OBD_pointer coPtr);

// OBD_Exist
bool OBD_Exist (long classID, identifier objID);

// OBD_SaveObject
void OBD_SaveObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject=NULL);

// OBD_ReleaseObject
size_t OBD_ReleaseObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject=NULL);

// OBD_CopyObject
OBD_pointer OBD_CopyObject (long classID, OBD_pointer coPtr);

// Определить место объекта в индексе по собственным ключам
OBD_pointer OBD_FindObjectByOwnData (long classID, void * pData, identifier objID, CObjIndex * pObjDriveIndex, identifier indexID);

// Удалить объект из индекса
void OBD_DeleteIndexItem (long classID, void *pData, identifier objID);

// OBD_DeleteObject
void OBD_DeleteObject (long classID, OBD_pointer coPtr);

// OBD_DeleteObject
void OBD_DeleteObject (long classID, identifier objID);

// Удаление объектов по ключу
void OBD_DeleteObject (long classID, key_arr& _ka, CIndexInfo& indexInfo);

// OBD_GetClassID
identifier OBD_GetClassID (long classID, OBD_pointer coPtr);

// Отладочная печать
void OBD_DebugPrint(long classID, string& dbg, OBD_pointer coPtr);

// Сравнение значение ключа по текущему индексу с ключом-аргументом
int OBD_CompareToKeyVarArr (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr& _ka);

// Поиск объека по индексу
OBD_pointer OBD_IndexFindObject (long classID, const CIndexInfo& indexInfo, key_arr& _ka, bool bInexact=false);

// Число всех/уникальных объектов с заданным ключом в текущем индексе
size_t OBD_GetIndexNumForKey (long classID, const CIndexInfo& indexInfo, key_arr& _ka, key_arr& _ka_rbound, bool bUnique=false);

// Число всех объектов класса
size_t OBD_IndexTotalNum (long classID);

// Получить идентификатор первого/последнего объекта по индексу
identifier OBD_FirstLastIDInIndex (long classID, const CIndexInfo& indexInfo, OBD_FIND findType);

// Получить идентификатор первого объекта по индексу
identifier OBD_FirstIDInIndex (long classID, const CIndexInfo& indexInfo);

// Получить идентификатор последнего объекта по индексу
identifier OBD_LastIDInIndex (long classID, const CIndexInfo& indexInfo);

// Найти следующий/предыдущий/первый/последний объект
OBD_pointer OBD_IndexNextPrevFirstLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, OBD_FIND findType, key_arr* _pka, bool bUnique, bool bSame=false);

// Найти следующий объект
OBD_pointer OBD_IndexNextObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame=false);

// Найти предыдущий  объект
OBD_pointer OBD_IndexPrevObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame=false);

// Найти первый   объект
OBD_pointer OBD_IndexFirstObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr);

// Найти последний объект
OBD_pointer OBD_IndexLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr);

// Сохранить определённый индекс
void OBD_SaveIndexToFile (long classID, const CIndexInfo& indexInfo);

// Сохранить все изменённые данные
void OBD_SaveAllData ();

// Перегрузить все индексы
void OBD_ReloadAllBase ();

// Проверка существования объекта указанного класса с указанным
//  идентификатором
bool OC_Exist (identifier classID, identifier objID);
//____________________________________________________________________________[]





















//______________________________________________________________________________
//                                                                            []
// OBD_GetObjectFieldValue																		[]
//                                                                            []
template <class OD, class FT> 
const FT& OBD_GetObjectFieldValue (long classID, OBD_pointer coPtr, FT OD::* field)
{
	IF_OBJECT_INVALID {static const FT defval=FT((char)0); return defval;}
	return ((OD*)(aObject->pData))->*field;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
// Get Array Value																				[]
//                                                                            []
template <class OD, class FT> 
const FT& OBD_GetObjectFieldArrValue (long classID, OBD_pointer coPtr, CPtr<FT> OD::* field, identifier item)
{
	IF_OBJECT_INVALID {static const FT defval=FT((char)0); return defval;}
	return (((OD*)(aObject->pData))->*field)[item];
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Upadate Index																					[]
//                                                                            []
template <class OD, class FT> 
void OBD_UpdateIndex (long classID, identifier objID, identifier indexID, identifier fieldID, OD * pData, const FT& value)
{
//	Изменяем значения ключей для поля "fieldID" в индексе "indexID" на "value", 
// запоминеаем новые указатели в индекс "pData->m_CoIndexPtr[indexID]"

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

// Число ключей в индексе
	size_t index_key_number = pObjDriveIndex->fieldArr.GetSize();

// Объект не знает своего места в индексе
	if (pData_m_CoIndexPtr(classID, pData, indexID) == NULL)
	{
		pData_m_CoIndexPtr(classID, pData, indexID, OBD_FindObjectByOwnData (classID, pData, objID, pObjDriveIndex, indexID));
	}

// Не удалось найти объект в индексе 
	if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_UpdateIndex: Не удалось найти объект класса '%s' в индексе %d", className[classID], indexID);
		return;
	}

// Пробегаемся по всем ключам, составляющим индекс indexID
	for (int k=0; k< (int)index_key_number; k++)
	{
	// Если ключ -- изменившееся поле, его значение надо заменить в индексе
		if (pObjDriveIndex->fieldArr[k]==fieldID)
		{
		// Создаём новый ключ на основе старого
			CObjIndex_AVTree_Item * pIndexItem = pIndexTree->ItemPointer (pData_m_CoIndexPtr(classID, pData, indexID));
			if (pIndexItem==NULL)
			{
				SERVER_DEBUG_ERROR ("OBD_UpdateIndex: Ошибка при поиске объекта: pIndexTree->ItemPointer (pData->m_CoIndexPtr[indexID]==NULL");
				return;
			}

			p_static_ka->FromPtr(pIndexItem->m_pData);

		// Меняем нужное поле в ключе
			p_static_ka->SetKeyData (k, value, !pObjDriveIndex->fieldArr_ascend[k]);

		// Удаляем старый ключ
			pIndexTree->Remove (pData_m_CoIndexPtr(classID, pData, indexID));

		// Добавляем новый ключ и запоминаем новый указатель внутрь индекса "indexID"
			CObjIndex_AVTree_Item newItem;
			newItem.FromPtr (p_static_ka->GetPtr());
			pData_m_CoIndexPtr(classID, pData, indexID, pIndexTree->Insert (newItem));
			pObjDriveIndex->bChanged = true;


		// Не удалось обновить индекс
			if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
			{
				SERVER_DEBUG_ERROR_2 ("OBD_UpdateIndex: Не удалось обновить индекс %d в объекта класса '%s'", indexID, className[classID]);
				return;
			}
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
// Put Value																						[]
//                                                                            []
template <class OD, class FT> 
void OBD_PutObjectFieldValue (identifier fieldID, long classID, OBD_pointer coPtr, FT OD::* field, FT value)
{
	IF_OBJECT_INVALID {return;}

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return;
	#endif

// Формат изменяемого поля
	CFieldFormat* pCFieldFormat = theObjDriver.GetFieldPtr(classID, fieldID);

// Число индексов, в которых участвует поле fieldID
	size_t nFieldIndexNum = pCFieldFormat->indexArr.GetSize();

	OD* pData = (OD*)aObject->pData;

// Проверяем, является ли значение отличным от того что уже есть
	bool bNewValue = false;
	FIELD_TYPE ft = pCFieldFormat->type;
	
	if (ft == FT_string)
	{
		if (((string*)(&(pData->*field)))->size() != ((string*)&value)->size())
		{
			bNewValue = true;
		}
		else if (strcmp (((string*)(&(pData->*field)))->c_str(), ((string*)&value)->c_str()))
		{
			bNewValue = true;
		}
	}
	else if (pData->*field != value)
	{
		bNewValue = true;
	}

// Записывается новое значение, не равное тому что уже есть
	if (bNewValue)
	{
	// Для каждого индекса, в котором участвует изменяемое поле fieldID
		for (int iIndex=0; iIndex < (int) nFieldIndexNum; iIndex++)
		{
		// Индекс, в котором участвует поле
			identifier indexID = theObjDriver.GetFieldPtr(classID, fieldID)->indexArr[iIndex];
			OBD_UpdateIndex <OD, FT> (classID, aObject->objID, indexID, fieldID, pData, value);
		}

		pData->*field		= value;
		aObject->bChanged	= true;
	}

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
// Put Array Value																				[]
//                                                                            []
template <class OD, class FT> 
void OBD_PutObjectFieldArrValue (long classID, OBD_pointer coPtr, CPtr<FT> OD::* field, identifier item, FT value)
{
	IF_OBJECT_INVALID {return;}

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return;
	#endif

	OD* pData =  (OD*)aObject->pData;
	(pData->*field)[item]	= value;
	aObject->bChanged			= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
// Size of Array field																			[]
//                                                                            []
template <class OD, class FT>
size_t OBD_GetObjectFieldArrSize (long classID, OBD_pointer coPtr, FT OD::* fieldArr)
{
	IF_OBJECT_INVALID {return 0;}
	return (((OD*)(aObject->pData))->*fieldArr).GetSize();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
// Add item to field array																		[]
//                                                                            []
template <class OD, class FT> 
int OBD_AddObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, const FT& value)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return (pData->*fieldArr).Size();
	#endif

	(pData->*fieldArr).Add (value);
	aObject->bChanged			= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif
	
	return (pData->*fieldArr).Size();
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Add item to field array from another array											[]
//                                                                            []
template <class OD, class FT> 
int OBD_AddFromObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, const CPtr<FT>& FromArr)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return (pData->*fieldArr).Size();
	#endif

	(pData->*fieldArr).AddFrom (FromArr);
	aObject->bChanged			= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif
	
	return (pData->*fieldArr).Size();
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Insert item into array																		[]
//                                                                            []
template <class OD, class FT> 
int  OBD_InsertObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, int item, const FT& value)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return (pData->*fieldArr).Size();
	#endif

	(pData->*fieldArr).Insert (item, value);
	aObject->bChanged			= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif

	return (pData->*fieldArr).Size();
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
// Insert item into sorted array																[]
//                                                                            []
template <class OD, class FT> 
int OBD_InsertSortedObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, const FT& value)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return -1;
	#endif

	int item = (pData->*fieldArr).InsertSorted (value);
	aObject->bChanged			= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif

	return item;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Find Object FieldArr Item																	[]
//                                                                            []
template <class OD, class FT> 
int OBD_FindObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, const FT& value, bool bSorted=false)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;
	return (pData->*fieldArr).Find (value, bSorted);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
// Delete item from field array																[]
//                                                                            []
template <class OD, class FT>
int OBD_DelObjectFieldArrItem (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, int item)
{
	IF_OBJECT_INVALID {return -1;}

	OD* pData = (OD*)aObject->pData;

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return (pData->*fieldArr).Size();
	#endif

	int size = (pData->*fieldArr).GetSize();
	if (item<0 || item>=size || size==0)
	{
		SERVER_DEBUG_ERROR_4 ("Ошибка удаления поля объекта id=%d класса '%s':  item=%d size=%d", aObject->objID, className[classID], item, size);
		return (pData->*fieldArr).Size();
	}
	(pData->*fieldArr).Del (item);
	aObject->bChanged		  = true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif

	return (pData->*fieldArr).Size();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
// Delete item from field array																[]
//                                                                            []
template <class OD, class FT>
void OBD_DelObjectFieldArrAllItems (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr)
{
	IF_OBJECT_INVALID {return;}

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return;
	#endif

	OD* pData = (OD*)aObject->pData;
	(pData->*fieldArr).Realloc(0);
	aObject->bChanged		  = true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Copy ObjectFieldArr All Items																[]
//                                                                            []
template <class OD, class FT>
int OBD_CopyObjectFieldArrAllItemsFromPtr (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, const FT* ptrFrom, int nSize)
{
	IF_OBJECT_INVALID {return 0;}

// Предотвращаем изменение объекта
	#ifdef USE_CHANGE_NOTIFICATION
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Change, classID, aObject->objID)==false) return 0;
	#endif

	OD* pData = (OD*)aObject->pData;
	(pData->*fieldArr).Realloc(0);
	(pData->*fieldArr).CopyFrom (ptrFrom, nSize);
	aObject->bChanged	= true;

// Уведомляем об изменении объекта
	#ifdef USE_CHANGE_NOTIFICATION
	RAISE_EVENT_OBJBASE (EMT_Object_Change, classID, aObject->objID);
	#endif

	return (pData->*fieldArr).GetSize();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Copy ObjectFieldArr All Items																[]
//                                                                            []
template <class OD, class FT>
int OBD_CopyObjectFieldArrAllItemsToCPtr (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr, CPtr<FT>& cptrTo)
{
	IF_OBJECT_INVALID {return 0;}
	OD* pData = (OD*)aObject->pData;
	return cptrTo.CopyFrom ((const FT*)(pData->*fieldArr).GetPtr(), (pData->*fieldArr).GetSize());
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Get Object FieldArr Data-Pointer															[]
//                                                                            []
template <class OD, class FT>
const FT * OBD_GetObjectFieldArrDataPointer (long classID, OBD_pointer coPtr, CPtr<FT> OD::* fieldArr)
{
	IF_OBJECT_INVALID {return NULL;}
	OD* pData = (OD*)aObject->pData;
	return (FT*) (pData->*fieldArr).GetPtr();
}
//____________________________________________________________________________[]





















#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
