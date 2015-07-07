/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBD.cpp																	[]
[] Date:            25.03.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Object Base Driver (OBD)												[]
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
#define	USES_stopwatch_h
#define	USES_ObjCache_h

#include "main.h"
#include "OBD.h"
#include "ObjCache.h"

bool CHECK_VALID_IGNORE_DELETED	=	false;
bool IGNORE_LAST_KEY_IDENTIFIER	=	false;


bool OBD_Busy = false;

StopWatch	OBD_Timer;

//______________________________________________________________________________
//                                                                            []
//` CompareFunction_identifier																[]
//                                                                            []
int CompareFunction_identifier (identifier& a, identifier& b)
{
	return	a - b;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` CompareFunction_CObjIndex_AVTree_Item 												[]
//                                                                            []
int CompareFunction_CObjIndex_AVTree_Item (pbyte& a, pbyte& b)
{
// a,b		=	[size_t Size, byte KeyNum, key1, ... keyN]
// Keyi		=	[byte type, data]	
// LastKey	=	idendifier key
	const size_t offset_Key		= sizeof (size_t) + sizeof (byte);

	size_t len = min (*((size_t *)a), *((size_t *)b)) - offset_Key - (IGNORE_LAST_KEY_IDENTIFIER? sizeof(identifier): 0);
	
	return memcmp (a+offset_Key, b+offset_Key, len);
}
//____________________________________________________________________________[]


#ifndef ZOOB_UTILS

extern bool bIGNORE_LOAD_ERROR;

//______________________________________________________________________________
//                                                                            []
//` OBD_Exist																						[]
//                                                                            []
bool OBD_Exist (long classID, identifier objID, identifier randID)
{
	DEBUG_STACK_NAME (OBD_Exist);

// ID из резервоной области
	if (objID<FILE_ID_LAST)
		return false;

// Пустой ID
	if (objID==NA)
		return false;

// Объект загружен в память
	OBD_pointer coPtr = OBD_AllObjectsInMemory.Find (objID);
	if (coPtr!=NULL)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
			return false;
		if (aObject->pData==NULL)
			return false;
		if (pData_classID(classID, aObject->pData) != (identifier)classID)
			return false;
		if (aObject->objID==NA)
			return false;
		if (aObject->bDeleted)
			return false;
		if (randID!=0 && aObject->objRN!=randID)
			return false;
		return true;
	}

// Объект не в памяти -- проверяем на диске.
   CFile file;
   if (!file.Exist(objID))
       return false;
   file.Open (objID);

	if (randID!=0)
	{
		identifier tmp_classID;
		identifier tmp_randID;

		if (file.GetMaxSize() < sizeof (tmp_classID) + sizeof (tmp_randID))
		{
			return false;
		}

		file.ReadData (tmp_classID);
		file.ReadData (tmp_randID);
		return (tmp_classID == identifier(classID)) && (tmp_randID == randID);
	}


	identifier tmp_classID;

	if (file.GetMaxSize() < sizeof (tmp_classID))
	{
		return false;
	}
	file.ReadData (tmp_classID);
	return tmp_classID == identifier(classID);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Проверка существования объекта указанного класса									[]
//  с указанным идентификатором и уникальным номером.									[]
bool OC_Exist (identifier classID, identifier objID, identifier randID) 
{
	DEBUG_STACK_NAME (OC_Exist);

	return OBD_Exist (classID, objID, randID);
}
//----------------------------------------------------------------------------[] 
bool OC_Exist (const guid& gi)
{
	DEBUG_STACK_NAME (OC_Exist);

	return OBD_Exist (gi.cl, gi.id, gi.rn);
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` CAbstractObjectInMemory::Save                                             []                             
//                                                                            []
bool CAbstractObjectInMemory::Save ()
{
	DEBUG_STACK_NAME (CAbstractObjectInMemory);

	if (pData && bChanged && !bDeleted)
	{
		OD_BASE * pBase = (OD_BASE *) pData;

		if (pBase->classID!=classID)
		{
			SERVER_DEBUG_ERROR_3 ("Save: objID = %d; pBase->classID(%d)!=classID(%d)", classID, pBase->classID, classID);
			return false;
		}
		OBD_Timer.Start();
		bool bRes = pData_WriteToFile (classID, (void*) pData, objID);
		OBD_Timer.Stop();
		the_OBJ_CACHE.UpdateClassStats (classID, OBD_Timer.GetTime(), OCUT_ON_CLOSE);

		if (bRes)
		{
			bChanged = false;
			return true;
		}
		return false;
	}
	return true;
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBD
[]                                                                            []
[]____________________________________________________________________________[]
*/


//----------------------------------------------------------------------------[] 
#ifndef ZOOB_UTILS
	IT_AVTree_AllObjectsInMemory	OBD_AllObjectsInMemory (&CAbstractObjectInMemory::objID, CompareFunction_identifier);
#endif
//----------------------------------------------------------------------------[] 






//______________________________________________________________________________
//                                                                            []
//` Корректировка набора ключей -- для случая, если имеет 							[]
//	 место обратная сортировка																	[]
//                                                                            []
void CorrectKeyArr (key_arr& ka, identifier classID, identifier indexID)
{
	DEBUG_STACK_NAME (CorrectKeyArr);

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	int pObjDriveIndex_fieldArr_ascend_GetSize = pObjDriveIndex->fieldArr_ascend.GetSize();
	int ka_GetKeyNum = (int)ka.GetKeyNum();
	for (int k=0; k<pObjDriveIndex_fieldArr_ascend_GetSize && k<ka_GetKeyNum; k++)
	{
	// Поле f отсортировано в обратном порядке
		if (pObjDriveIndex->fieldArr_ascend[k]==false)
		{
			identifier fieldID = pObjDriveIndex->fieldArr[k];
			//SERVER_DEBUG_ASSERT (theObjDriver.GetFieldPtr(classID, fieldID)->type==ka.GetItemType(k), "CorrectKeyArr: Несовпадение типов ключей");

			switch (theObjDriver.GetFieldPtr(classID, fieldID)->type)
			{
				case FT_string:
				{
					static char Value [MAX_KEY_LENGTH];
					Value[0] =0;
					ka.GetKeyData (k, Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_identifier:
				{
					identifier Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_guid:
				{
					guid Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_int:
				{
					int Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_byte:
				{
					byte Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_bool:
				{
					bool Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_float:
				{
					float Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				default:
					SERVER_DEBUG_ERROR ("CorrectKeyArr: Неизвестный тип ключа");
				return;
			}
		}
	}
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` GetObject 																						[]
//                                                                            []
OBD_pointer OBD_GetObject (long classID, identifier objID, identifier indexID, OBD_pointer coIndexPtr)
{
	DEBUG_STACK_NAME (OBD_GetObject);

	OBD_pointer			coPtr;
	coPtr = OBD_AllObjectsInMemory.Find (objID);

	if (coPtr!=NULL)
	{
	// Объект в памяти
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_GetObject: Ошибка поиска закешированного объекта %s[%d]:  aObject==NULL", className[classID], objID);
			return NULL;
		}
	// Объект другого класса
		if ((long)aObject->classID != (long)classID)
		{
		#ifdef WIN32
			SERVER_DEBUG_ERROR_3 ("OBD_GetObject: Попытка открытия закешированного объекта %s[%d] как объект класса '%s'", className[aObject->classID], objID, className[classID]);
		#endif
			return NULL;
		}
	// Объект удалён
		if (aObject->bDeleted)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_GetObject: Ошибка открытия закешированного объекта %s[%d]: объект уже удалён", className[classID], objID);
			return NULL;
		}


		aObject->AddRef ();
	// Если надо -- прописываем указатель на место в индексе
		if (indexID!=NA && coIndexPtr!=NULL)
		{
			pData_m_CoIndexPtr (classID, aObject->pData, indexID, coIndexPtr);
		}

	// Сообщаем кэшу о переоткрытии объекта
		if (!OBD_Busy)
		{
			OBD_Busy = true;
			the_OBJ_CACHE.OnOpen (coPtr);
			OBD_Busy = false;
		}

		return coPtr;
	}
	else  
	{
	// Объект не в памяти -- загружаем с диска

	// Предупреждение об открытии
		if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Open, classID, objID)==false) return NULL;

		void * pData = new_OD (classID, false);

		OBD_Timer.Start();
		size_t nObjSize = pData_LoadFromFile (classID, pData, objID);
		OBD_Timer.Stop();
		the_OBJ_CACHE.UpdateClassStats (classID, OBD_Timer.GetTime(), OCUT_ON_OPEN);

		if (nObjSize!=0)
		{
			CAbstractObjectInMemory aObject;
			aObject.pData				= pData;
			aObject.classID			= classID;
			aObject.objID				= objID;
			aObject.objRN				= ((OD_BASE *) pData)->d_randID;
			aObject.AddRef					();
			aObject.nSize				= nObjSize;
			coPtr = OBD_AllObjectsInMemory.Insert (aObject);
			aObject.pData				= NULL;

			if (coPtr==NULL)
			{
				SERVER_DEBUG_ERROR_2 ("OBD_GetObject: Ошибка добавления в дерево объекта %s[%d]:  aObject==NULL", className[classID], objID);
				return NULL;
			}
		// Если надо -- прописываем указатель на место в индексе
			if (indexID!=NA && coIndexPtr!=NULL)
			{
				pData_m_CoIndexPtr (classID, pData, indexID, coIndexPtr);
			}

			if (!OBD_Busy)
			{
				OBD_Busy = true;
			// Оповещение об открытии
				RAISE_EVENT_OBJBASE (EMT_Object_Open, classID, objID);
			// Сообщаем кэшу об открытии объекта
				the_OBJ_CACHE.OnOpen (coPtr);
				OBD_Busy = false;
			}

			return coPtr;
		}
		else 
		{
         if (!bIGNORE_LOAD_ERROR)
			{
				SERVER_DEBUG_ERROR_2 ("OBD_GetObject: Указанный объект %s[%d] не существует", className[classID], objID);
			}
			if (pData)
			{
				delete_pData (classID, pData);
			}
			return NULL;
		}
	}
	
	return NULL;
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//` OBD_CreateIndexItem 																		[]
//                                                                            []
void OBD_CreateIndexItem (long classID, void * pData, identifier objID)
{
	DEBUG_STACK_NAME (OBD_CreateIndexItem);

	int indexID,k;
	int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

// Для каждого индекса создаём и запоминаем ключи
	for (indexID=0; indexID < IndexNum;  indexID++)
	{
		SERVER_DEBUG_ASSERT (pData_m_CoIndexPtr(classID, pData, indexID)==NULL, "OBD_CreateIndexItem: объект уже есть в индексе");

		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

	// Дерево-индекс
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
		
	// Число ключей в индексе
		size_t index_key_number = pObjDriveIndex->fieldArr.GetSize();

	// Создаём ключи для текущего индекса
		static key_arr ka;
		ka.Init			();
		for (k=0; k < (int) index_key_number; k++)
		{
			pData_AddKeyVarForField (classID, pData, ka, pObjDriveIndex->fieldArr[k]);
		}

	// Прописывем ID объекта
		ka += objID;

	// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
		CorrectKeyArr (ka, classID, indexID);

	// Добавляем новый набор ключей и запоминаем новый указатель внутрь текущего индекса
		static CObjIndex_AVTree_Item newItem;
		newItem.FromPtr (ka.GetPtr());
		pData_m_CoIndexPtr(classID, pData, indexID, pIndexTree->Insert (newItem));
		pObjDriveIndex->bChanged = true;

		SERVER_DEBUG_ASSERT (pData_m_CoIndexPtr(classID, pData, indexID), "Не смогли добавить новый объект в индекс");
	}
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` OBD_CreateObject																				[]
//                                                                            []
OBD_pointer OBD_CreateObject (long classID, bool bInternal)
{
	DEBUG_STACK_NAME (OBD_CreateObject);

	void * pData = new_OD (classID, true);

// Предупреждение о создании
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_New, classID, NA)==false) return NULL;
			
	if (!bInternal && theObjDriver.m_FormatArr[classID].isMaster)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_CreateObject: Ошибка создания -- объект мастер-класса '%s' не может быть создан вручную. Он создаётся автоматически.", className[classID]);
		return NULL;
	}

	if (pData_classID (classID, pData) != (identifier) classID)
	{
		delete_pData (classID, pData);
      SERVER_DEBUG_ERROR_2 ("OBD_CreateObject: Ошибка создания объекта класса '%s' (%d):  pData->classID != classID", className[classID], classID);
		return NULL;
	}

// Создаём файл объекта и записываем в него classID и randID
	struct IDID{identifier classID; identifier randID;} idid;
	idid.classID = classID;
	idid.randID  = ((OD_BASE *) pData)->d_randID;
	identifier objID = FD.Write(&idid, sizeof(IDID));
		
	CAbstractObjectInMemory aObject;
	aObject.pData				= pData;
	aObject.classID			= classID;
	aObject.objID				= objID;
	aObject.objRN				= ((OD_BASE *) pData)->d_randID;
	aObject.AddRef					();
	aObject.bChanged			= true;
	aObject.bDeleted			= false;
	OBD_pointer coPtr			= OBD_AllObjectsInMemory.Insert (aObject);

	aObject.pData				= NULL;
	aObject.bChanged			= false;

	if (coPtr==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CreateObject: Ошибка добавления в дерево объекта %s[%d]:  aObject==NULL", className[classID], objID);
		return NULL;
	}

	OBD_CreateIndexItem (classID, pData, objID);

// Оповещение о создании
	RAISE_EVENT_OBJBASE (EMT_Object_New, classID, objID);
// Сообщаем кэшу о создании объекта
	the_OBJ_CACHE.OnCreate (coPtr);

	return coPtr;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` OBD_GetClassIdList																			[]
//  Получить список всех объектов или (если pka!=NULL) равных аргументу			[]
//                                                                            []
void OBD_GetClassIdList (identifier_arr& id_list, long classID, key_arr* pka, const CIndexInfo& indexInfo)
{
	DEBUG_STACK_NAME (OBD_GetClassIdList);

	id_list.Realloc (0);

	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR_1 ("Нельзя получить список всех идентификаторов -- класс '%s' не имеет индексов", className[classID]);
		return;
	}


// Указано слишком много ключей для поиска
	if (pka) if (((int)pka->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("Указано слишком много ключей для поиска");
		return;
	}

// Проверяем типы ключей
	if (pka) for (int k=0; k < (int)pka->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("Указаны неверные типы ключей");
			return;
		}
	}

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	static key_arr ka;	ka.Init	();
	if (pka) {ka=*pka; CorrectKeyArr (ka, classID, indexID);}

// Дерево-индекс
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	
// Ключ поиска -- используется если задан диапазон, т.е. pka!=NULL
	pbyte arg1 = (pka==NULL || pka->GetKeyNum()==0)? NULL: ka.GetPtr ();	

// Идём по индексу начиная с первого удовлетворяющего элемента (граница диапазона или самый первый элемент)
	for (OBD_pointer coIndexPtr = (arg1?pIndexTree->Find(arg1):pIndexTree->First()); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

	// Если указан диапазон, проверяем на предмет выхода из него
		if (arg1)
		{
		// Собственный полный ключ
			pbyte arg0 = pItem->GetPtr	();	

		// Если ключ найденного не равен аргументу -- выход
			if (CompareFunction_CObjIndex_AVTree_Item (arg0, arg1) != 0)
			{
				break;
			}
		}
		id_list.Add (pItem->GetObjID());
	}
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` OBD_GetClassIdListInRange																	[]
//  Получить список всех объектов из указанного диапазона							[]
//  Если первый аргумент равен NULL -- брать объекты с самого первого,			[]
//  если второй аргумент равен NULL -- брать объекты до самого последнего.		[]
//                                                                            []
void OBD_GetClassIdListInRange (identifier_arr& id_list, long classID, key_arr* pka1, key_arr* pka2, const CIndexInfo& indexInfo)
{
	DEBUG_STACK_NAME (OBD_GetClassIdListInRange);

	id_list.Realloc (0);

	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR_1 ("Нельзя получить список всех идентификаторов -- класс '%s' не имеет индексов", className[classID]);
		return;
	}


// Указано слишком много ключей для поиска
	if (pka1) if (((int)pka1->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("Указано слишком много ключей для поиска");
		return;
	}
	if (pka2) if (((int)pka2->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("Указано слишком много ключей для поиска для второй границы диапазона");
		return;
	}

// Проверяем типы ключей
	if (pka1) for (int k=0; k < (int)pka1->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka1->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("Указаны неверные типы ключей");
			return;
		}
	}
	if (pka2) for (int k=0; k < (int)pka2->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka2->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("Указаны неверные типы ключей для второй границы диапазона");
			return;
		}
	}

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	static key_arr ka1;	ka1.Init	();
	static key_arr ka2;	ka2.Init	();
	if (pka1) {ka1=*pka1; CorrectKeyArr (ka1, classID, indexID);}
	if (pka2) {ka2=*pka2; CorrectKeyArr (ka2, classID, indexID);} else pka2=pka1;

// Дерево-индекс
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	
// Ключ поиска -- используется если задан диапазон, т.е. pka1!=NULL или pka2!=NULL
	pbyte arg1 = (pka1==NULL || pka1->GetKeyNum()==0)? NULL: ka1.GetPtr ();	
	pbyte arg2 = (pka2==NULL || pka2->GetKeyNum()==0)? NULL: ka2.GetPtr ();	

// Идём по индексу начиная с первого удовлетворяющего элемента (граница диапазона или самый первый элемент)
	OBD_pointer coIndexPtr = NULL;
	if (arg1==NULL)
	{
		coIndexPtr = pIndexTree->First();
	}
	else
	{
	// Пытаемся найти элемент, меньший или равный началу диапазону
		coIndexPtr = pIndexTree->Find(arg1, true);

	// Если элемент не найден, значит все элементы строго больше начала диапазона, становимся на первый элемент
		if (coIndexPtr==NULL)
		{
			coIndexPtr = pIndexTree->First();
		}
		else
		{
		// Найден элемент, который, возможно, меньше начала диапазона, следовательно надо найти первый элемент, не меньший чем начало диапазона
			for (; coIndexPtr!=NULL; coIndexPtr=pIndexTree->Next(coIndexPtr))
			{
				CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

			// Собственный полный ключ
				pbyte arg0 = pItem->GetPtr	();	

			// Если ключ найденного больше чем второй ключ (конец диапазона) -- выход
				if (CompareFunction_CObjIndex_AVTree_Item (arg0, arg1) >= 0)
				{
					break;
				}
			}
		}
	}
	for (; coIndexPtr!=NULL; coIndexPtr=pIndexTree->Next(coIndexPtr))
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

	// Если указан диапазон, проверяем на предмет выхода из него
		if (arg2)
		{
		// Собственный полный ключ
			pbyte arg0 = pItem->GetPtr	();	

		// Если ключ найденного больше чем второй ключ (конец диапазона) -- выход
			if (CompareFunction_CObjIndex_AVTree_Item (arg0, arg2) > 0)
			{
				break;
			}
		}
		id_list.Add (pItem->GetObjID());
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` _OBD_IsObjectValid																			[]
//                                                                            []
CAbstractObjectInMemory* _OBD_IsObjectValid (long classID, OBD_pointer coPtr)
{
	static CAbstractObjectInMemory * aObject = NULL;
	if (coPtr==NULL)
	{
		DEBUG_STACK_NAME (_OBD_IsObjectValid);
		SERVER_DEBUG_ERROR_1 ("Использование пустого контроллера класса '%s' (coPtr==NULL)", className[classID]);
		return NULL;
	}

	aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);

	if (aObject==NULL)
	{
		DEBUG_STACK_NAME (_OBD_IsObjectValid);
		SERVER_DEBUG_ERROR_2 ("Ошибка поиска объекта класса '%s':  aObject==NULL coPtr=%d", className[classID], coPtr);
		return NULL;
	}
	if (aObject->pData==NULL)
	{
		DEBUG_STACK_NAME (_OBD_IsObjectValid);
		SERVER_DEBUG_ERROR_2 ("Использование неисправного контроллера (aObject->pData==NULL). Объект %s[%d]", className[classID], aObject->objID);
		return NULL;
	}
	if (pData_classID(classID, aObject->pData) != (identifier)classID)
	{
		DEBUG_STACK_NAME (_OBD_IsObjectValid);
		SERVER_DEBUG_ERROR_3 ("Ошибка поиска объекта класса '%s':  несовпадение classID (%d, %d) ", className[classID], pData_classID(classID, aObject->pData),  classID);
		return NULL;
	}
	if (aObject->objID==NA)
	{
		DEBUG_STACK_NAME (_OBD_IsObjectValid);
		SERVER_DEBUG_ERROR_1 ("Использование неисправного контроллера (aObject->objID==NA). Объекта класса '%s'.", className[classID]);
		return NULL;
	}
	if (!CHECK_VALID_IGNORE_DELETED)
	{
		if (aObject->bDeleted)
		{
			DEBUG_STACK_NAME (_OBD_IsObjectValid);
			SERVER_DEBUG_ERROR_2 ("Использование неисправного контроллера (aObject->bDeleted==true). Объект %s[%d] был удалён.", className[classID], aObject->objID);
			return NULL;
		}
	}
	
	return aObject;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBD_GetObjectID																				[]
//                                                                            []
identifier OBD_GetObjectID (long classID, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_GetObjectID);

	CAbstractObjectInMemory * aObject = _OBD_IsObjectValid (classID, coPtr);
	if (aObject==NULL)
	{SERVER_DEBUG_ERROR_1 ("OBD_GetObjectID: aObject==NULL class='%s'", className[classID]); return NA;}

	return aObject->objID;	
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBD_GetObjectGUID                                                         []                 
//                                                                            []
void OBD_GetObjectGUID (long classID, OBD_pointer coPtr, guid& gi)
{
	DEBUG_STACK_NAME (OBD_GetObjectGUID);

	gi.Init();

	CAbstractObjectInMemory * aObject = _OBD_IsObjectValid (classID, coPtr);
	if (aObject==NULL)		SERVER_DEBUG_ERROR_1 ("OBD_GetObjectGUID: aObject==NULL class='%s'", className[classID]);

	gi.cl = aObject->classID;	
	gi.id = aObject->objID;	
	gi.rn = aObject->objRN;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBD_OpenMasterObject																		[]
//                                                                            []
OBD_pointer OBD_OpenMasterObject (long classID)
{
	DEBUG_STACK_NAME (OBD_OpenMasterObject);

	CFile		FileMasterID	=	FILE_ID_MASTER_CLASS;
	size_t	nFileSize		=	CFile::GetMaxSize(FILE_ID_MASTER_CLASS);
	bool		bContainID		=	nFileSize>=sizeof(identifier);

	if (bContainID)
	{
		identifier objID=NA;
		FileMasterID.ReadData (objID);
		
		return OBD_GetObject (classID, objID);
	}
	else 
	{
		OBD_pointer coPtr	=	OBD_CreateObject	(classID, true);
		identifier	objID	=	OBD_GetObjectID	(classID, coPtr);
		
		FileMasterID.WriteData	(objID);
		FileMasterID.Close		();

//		theFileDriver.flush();
		
		return coPtr;
	}

	return NULL;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_IsObjectValid																			[]
//                                                                            []
bool OBD_IsObjectValid (long classID, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_IsObjectValid);

	if (coPtr==NULL)
		return false;
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	if (aObject==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_IsObjectValid: Ошибка поиска объекта класса '%s':  aObject==NULL coPtr=%d", className[classID], coPtr);
		return false;
	}
	if (aObject->pData==NULL)
	{
		return false;
	}
	if (aObject->objID==NA)
	{
		return false;
	}
	if (aObject->bDeleted)
	{
		return false;
	}

	return 
		pData_classID (classID, aObject->pData) == (identifier)classID;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` OBD_SaveObject																				[]
//                                                                            []
void OBD_SaveObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject)
{
	DEBUG_STACK_NAME (OBD_SaveObject);

	IF_OBJECT_INVALID_A {return;}

	if (!aObject->Save ())
	{
		SERVER_DEBUG_ERROR_2 ("OBD_SaveObject: Ошибка записи объекта %s[%d]:  !aObject->Save ()", className[classID], aObject->objID);
		return;
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` OBD_ReleaseObject																			[]
//                                                                            []
size_t OBD_ReleaseObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject)
{
	DEBUG_STACK_NAME (OBD_ReleaseObject);

	size_t retval = 0;
	CHECK_VALID_IGNORE_DELETED = true;
	{
		IF_OBJECT_INVALID_A {CHECK_VALID_IGNORE_DELETED=false; return 0;}

		retval = aObject->Release();

		if (retval==0)
		{
			OBD_SaveObject (classID, coPtr, aObject);

		// Очищаем данные объекта
			delete_pData (classID, aObject->pData);
			aObject->pData		= NULL;
			aObject->bChanged	= false;
			aObject->bDeleted	= true;

		// Больше на данные никто не ссылается -- можно удалять "объект в памяти".
			bool bRes = OBD_AllObjectsInMemory.Remove (coPtr);
			if (bRes==false)
			{
				SERVER_DEBUG_ERROR_2 ("OBD_ReleaseObject: Не удалось удалить объект %s[%d] из дерева открытых объектов", className[classID], aObject->objID);
			}
		}
		else
		{
		// Сообщаем кэшу о закрытии контроллера объекта
			if (!OBD_Busy)
			{
				OBD_Busy = true;
				if (aObject->nCached) the_OBJ_CACHE.OnClose (coPtr);
				OBD_Busy = false;
			}
		}

	}
	CHECK_VALID_IGNORE_DELETED = false;

	return retval;
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` OBD_CopyObject																				[]
//                                                                            []
OBD_pointer OBD_CopyObject (long classID, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_CopyObject);

	IF_OBJECT_INVALID {return NULL;}

	aObject->AddRef();
	return coPtr;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Определить место объекта в индексе по собственным ключам						[]
//                                                                            []	
OBD_pointer OBD_FindObjectByOwnData (long classID, void * pData, identifier objID, CObjIndex * pObjDriveIndex, identifier indexID)
{
	DEBUG_STACK_NAME (OBD_FindObjectByOwnData);

// Число ключей в индексе
	size_t index_key_number = pObjDriveIndex->fieldArr.GetSize();

// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

// Создаём собственный набор ключей
	static key_arr ka;
	ka.Init			();
	for (int k=0; k < (int)index_key_number; k++)
	{
		pData_AddKeyVarForField (classID, pData, ka, pObjDriveIndex->fieldArr[k]);
	}

// Добавляем в ключ поиска идентификатор объекта
	ka += objID;

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	CorrectKeyArr (ka, classID, indexID);

	pbyte arg = ka.GetPtr();
	
// Ищем объект в индексе с ключами == собственному набору ключей и с нужным идентификатором.
	OBD_pointer coIndexPtr = pIndexTree->Find (arg);

	//----------------------------------------------------------------------------[] 
	// Не удалось определить место объекта в индексе по собственным ключам
	if (coIndexPtr==NULL)
	{
		string ka_dump;
		ka.DebugPrint (&ka_dump);

		printf ("\n\n* * * * * * \n  ERROR FIXING:\n   OBD_IndexFindObject: Correct indicies: ");
		SERVER_DEBUG_ERROR_4 ("OBD_FindObjectByOwnData: Невозможно определить место объекта %s[%d] в индексе %d по собственным ключам. Объект будет найден по ID.<br><pre>key_arr:\n%s</pre>", className[classID], objID, indexID, ka_dump.c_str());

	// Пытаемся найти объект по ID
		bool bOK = false;
		for (coIndexPtr = pIndexTree->First(); coIndexPtr!=NULL; coIndexPtr=pIndexTree->Next(coIndexPtr))
		{
			CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer(coIndexPtr);
			if (pItem && pItem->GetObjID() == objID)
			{
				bOK = true;
				break;
			}
		}
		if (bOK)
		{
			printf ("\n   done\n* * * * * * \n\n");
			return coIndexPtr;
		}
		else
		{
			printf ("\n   !!! FAILED !!!\n* * * * * * \n\n");
			SERVER_DEBUG_ERROR_3 ("OBD_FindObjectByOwnData: <b><font color=red>Попытка исправить ошибку провалилась:</b></font> Не удалось найти объект %s[%d] в индексе %d по ID", className[classID], objID, indexID);
			return NULL;
		}

		return NULL;
	}
	//----------------------------------------------------------------------------[] 


	return coIndexPtr;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Удалить объект из индекса																	[]
//                                                                            []	
void OBD_DeleteIndexItem (long classID, void *pData, identifier objID)
{
	DEBUG_STACK_NAME (OBD_DeleteIndexItem);

	int indexID;
	int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

// Для каждого индекса
	for (indexID=0; indexID < IndexNum;  indexID++)
	{
		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

	// Дерево-индекс
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

	// Объект не знает своего места в индексе
		if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
		{
			pData_m_CoIndexPtr(classID, pData, indexID, OBD_FindObjectByOwnData (classID, pData, objID, pObjDriveIndex, indexID));
		}

	// Объект не присутствует в индексе
		if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_DeleteIndexItem: Объект класса '%s' не присутствует в индексе %d", className[classID], indexID);
			return;
		}

	// Удаляем объект из индекса
		bool bRes = pIndexTree->Remove (pData_m_CoIndexPtr(classID, pData, indexID));
		if (bRes==false)
		{
			SERVER_DEBUG_ERROR_3 ("OBD_DeleteIndexItem: Не удалось удалить объект %s[%d] из индекса %d", className[classID], objID, indexID);
		}
		pData_m_CoIndexPtr(classID, pData, indexID, NULL);

	// Индекс изменился
		pObjDriveIndex->bChanged = true;
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_DeleteObject 																			[]
//                                                                            []
void OBD_DeleteObject (long classID, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_DeleteObject);

	IF_OBJECT_INVALID {return;}

	if (theObjDriver.m_FormatArr[classID].isMaster)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_DeleteObject: Ошибка удаления -- объект id=%d мастер-класса '%s' не может быть удалён.", aObject->objID, className[classID]);
		return;
	}

	identifier objID = aObject->objID;
	if (CFile::Exist(objID))
	{
	// Предупреждение об удалении
		if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Delete, classID, objID)==false) return;
		CFile::DeleteFile (objID);
	}

	OBD_DeleteIndexItem (classID, aObject->pData, objID);

// Очищаем данные объекта
	aObject->bChanged	= false;
	aObject->bDeleted	= true;
// Нельзя удалять "объект в памяти", так как на него ссылаются контроллеры

// Оповещение об удалении
	RAISE_EVENT_OBJBASE (EMT_Object_Delete, classID, objID);
// Сообщаем кэшу об удалении объекта
	if (aObject->nCached) the_OBJ_CACHE.OnDelete (coPtr);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_DeleteObject 																			[]
//                                                                            []
void OBD_DeleteObject (long classID, identifier objID, bool bIgnoreWarning)
{
	DEBUG_STACK_NAME (OBD_DeleteObject);

// Делаем достоверным тот факт, что объект загружен,
// иначе невозможно искать его в индексах -- по идентификатору
// индексы искать не умеют, перебирать их долго, а ключи объекта 
// нам не известны. -- Это одна из самых долгих операций.
	bIGNORE_LOAD_ERROR = bIgnoreWarning;
	if (!OC_Exist (classID, objID))
	{
		if (!bIgnoreWarning)
		{
			SERVER_DEBUG_ERROR ("Объект не найден");			
		}
		return;
	}
	OBD_pointer coPtr  = OBD_GetObject (classID, objID);
	bIGNORE_LOAD_ERROR = true;
	if (coPtr)
	{
		OBD_DeleteObject		(classID, coPtr);
		OBD_ReleaseObject		(classID, coPtr);		
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Удаление объектов по ключу																[]
//                                                                            []
void OBD_DeleteObjects (long classID, key_arr& _ka, CIndexInfo& indexInfo)
{
	DEBUG_STACK_NAME (OBD_DeleteObjects);

	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_DeleteObjects: Значение индекса не определено":"OBD_DeleteObjects: Значение индекса выходит за рамки");
		return;
	}

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	static key_arr  ka;
	ka  =				_ka;
	CorrectKeyArr (ka, classID, indexID);

//----------------------------------------------------------------------------[] 
//	
// Удаляем все объекты класса classID
//
	if (ka.GetKeyNum ()==0)
	{
	// Прочищаем дерево загруженных объектов
		identifier indexID = 0;
		if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
		{
			SERVER_DEBUG_ERROR_1 ("OBD_DeleteObjects: Объекты класса '%s' не могут быть удалены 'скопом' -- класс не имеет индексов", className[classID]);
			return;
		}

	// Дерево
		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

	// Идём по первому индексу и сравниваем идентификаторы
		for (OBD_pointer coIndexPtr = pIndexTree->First(); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
		{
			CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

		// Получили id
			identifier objID = pItem->GetObjID();

			OBD_pointer coPtr =	OBD_AllObjectsInMemory.Find (objID);

		// Объект в памяти - надо очистить его данные
			if (coPtr!=NULL)
			{
				IF_OBJECT_INVALID {continue;}

			// Предупреждение об удалении
				if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Delete, classID, objID)==false)
					continue;

			// Очищаем данные объекта
				aObject->bChanged	= false;
				aObject->bDeleted	= true;
			// нельзя удалять "объект в памяти", так как на него ссылаются контроллеры

			// Оповещение об удалении
				RAISE_EVENT_OBJBASE (EMT_Object_Delete, classID, objID);
			// Сообщаем кэшу об удалении объекта
				if (aObject->nCached) the_OBJ_CACHE.OnDelete (coPtr);
			}

		// Удаляем объект с диска
			if (CFile::Exist(objID))
			{
				CFile::DeleteFile (objID);
			}

		}

	// Очищаем все индексы данного класса
		for (indexID=0; indexID < (size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize();  indexID++)
		{
			theObjDriver.GetIndexPtr (classID, indexID)->AVTree.RemoveAll();
			theObjDriver.GetIndexPtr (classID, indexID)->bChanged = true;
		}

	// Сохраняем изменения в файловой системе
//		theFileDriver.flush();

		return;
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//	
// Удалять все объекты класса classID, имеющие значение ключа "ka"
//

// Дерево-индекс
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	pbyte arg2 = ka.GetPtr     ();	// Ключ поиска
	CPtr <identifier> id_Arr;
	id_Arr.Realloc (0);
// Идём по индексу начиная с первого удовлетворяющего элемента
	for (OBD_pointer coIndexPtr = pIndexTree->Find(arg2); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

	// Собственный полный ключ
		pbyte arg1 = pItem->GetPtr	();	

	// Если ключ найденного равен ключу поиска -- запоминаем для удаления
		if (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)==0)
		{
			id_Arr.Add (pItem->GetObjID());
		}
		else 
		{
			break;
		}
	}
// Удаляем запомненные идентификаторы
	for (int d=0; d<(int)id_Arr.GetSize(); d++)
	{
		OBD_DeleteObject (classID, id_Arr[d]);
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` OBD_GetClassID																				[]
//                                                                            []
identifier OBD_GetClassID (long classID, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_GetClassID);

	IF_OBJECT_INVALID {return NA;}
	return pData_classID (classID, aObject->pData);
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Отладочная печать																			[]
//                                                                            []
void OBD_DebugPrint(long classID, string& dbg, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_DebugPrint);

	IF_OBJECT_INVALID {return;}
	dbg = "";
	pData_DebugPrint (classID, aObject->pData, dbg, aObject->objID);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Сравнение значение ключа по текущему индексу с ключом-аргументом				[]
//                                                                            []
int OBD_CompareToKeyVarArr (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr& _ka)
{
	DEBUG_STACK_NAME (OBD_CompareToKeyVarArr);

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	identifier indexID = indexInfo.m_id;
	static key_arr  ka;
	ka  =				_ka;
	CorrectKeyArr (ka, classID, indexID);

	IF_OBJECT_INVALID {return -1;}
	OD_BASE* pData = (OD_BASE*)aObject->pData;

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_CompareToKeyVarArr: Значение индекса не определено":"OBD_CompareToKeyVarArr: Значение индекса выходит за рамки");
		return -1;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// Указано слишком много ключей для поиска
	if (((int)ka.GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_CompareToKeyVarArr: Указано слишком много ключей для поиска");
		return 0;
	}

// Проверяем типы ключей
	for (int k=0; k < (int)ka.GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != ka.GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_CompareToKeyVarArr: Указаны неверные типы ключей");
			return 0;
		}
	}


// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = pData->m_CoIndexPtr[indexID];

// Объект не знает своего места в индексе
	if (coIndexPtr==NULL)
	{
		pData->m_CoIndexPtr[indexID] = coIndexPtr = OBD_FindObjectByOwnData (classID, pData, aObject->objID, pObjDriveIndex, indexID);
	}
// Объект не присутствует в индексе
	if (coIndexPtr==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CompareToKeyVarArr: Объект класса '%s' не присутствует в индексе %d", className[classID], indexID);
		return -1;
	}
	

// Сравнение ключей
	CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
	if (pItem == NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CompareToKeyVarArr: Ошибка получения элемента индекса %d для объект класса '%s' -- объект не присутствует в индексе", indexID, className[classID]);
		return -1;
	}
	pbyte arg1 = pItem->GetPtr ();
	pbyte arg2 = ka.GetPtr		();
	return CompareFunction_CObjIndex_AVTree_Item (arg1, arg2);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Поиск объека по индексу																	[]
//                                                                            []
OBD_pointer OBD_IndexFindObject (long classID, const CIndexInfo& indexInfo, key_arr& _ka, bool bInexact)
{
	DEBUG_STACK_NAME (OBD_IndexFindObject);

	identifier indexID = indexInfo.m_id;

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	static key_arr	 ka;
	ka  =				_ka;
	CorrectKeyArr (ka, classID, indexID);

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_IndexFindObject: Значение индекса не определено":"OBD_IndexFindObject: Значение индекса выходит за рамки");
		return NULL;
	}

	if (indexID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_IndexFindObject: Поиск объекта класса '%s' при неопределённом индексе", className[classID]);
		return NULL;		
	}

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

//	Число ключей для поиска
	int keyNum = ka.GetKeyNum ();

// Указано слишком много ключей для поиска
	if (keyNum > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_IndexFindObject: Указано слишком много ключей для поиска");
		return NULL;
	}

// Проверяем типы ключей
	for (int k=0; k < keyNum; k++) 
	{
		if (indexInfo.m_keyType[k] != ka.GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_IndexFindObject: Указаны неверные типы ключей");
			return NULL;
		}
	}

// Ищем в индексе
	pbyte arg = ka.GetPtr();
	OBD_pointer coIndexPtr = pIndexTree->Find (arg, bInexact);
	
// Если нашли -- открываем объект
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			identifier objID = pItem->GetObjID ();			
			OBD_pointer coPtr = OBD_GetObject (classID, objID, indexID, coIndexPtr);

			//----------------------------------------------------------------------------[] 
			// Объект не удалось загрузить
			if (coPtr==NULL)
			{
				string ka_dump;
				ka.DebugPrint (&ka_dump);
				SERVER_DEBUG_ERROR_4 ("OBD_IndexFindObject: Ошибка открытия объекта: объект %s[%d], найденный по индексу %d не может быть загружен и будет удалён из индексов<br><pre>key_arr:\n%s</pre>", className[classID], objID, indexID, ka_dump.c_str());

			// перебираем индексы, находим в них объект и удаляем индексы
				printf ("\n\n* * * * * * \n  ERROR FIXING:\n   OBD_IndexFindObject: Correct indicies: ");
				for (int i=0; i<theObjDriver.m_FormatArr[classID].indexArr.GetSize(); i++)
				{
					CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, i);
					CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

					for (OBD_pointer coPtr = pIndexTree->First(); coPtr!=NULL; coPtr=pIndexTree->Next(coPtr))
					{
						CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer(coPtr);
						if (pItem && pItem->GetObjID() == objID)
						{
							if (pIndexTree->Remove (coPtr))
							{
								pObjDriveIndex->bChanged = true;
								printf ("%d ", i);
							}
							break;
						}
					}
				}
				printf ("\n   done\n* * * * * * \n\n");
				return NULL;
			//----------------------------------------------------------------------------[] 
			}
			return coPtr;
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_IndexFindObject: Ошибка при поиске объекта: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NULL;
		}
	}
	return NULL;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Число всех/уникальных объектов с заданным ключом в текущем индексе			[]
//                                                                            []
size_t OBD_GetIndexNumForKey (long classID, const CIndexInfo& indexInfo, key_arr& _ka, key_arr& _ka_rbound, bool bUnique)
{
	identifier indexID = indexInfo.m_id;

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	static key_arr	 ka;
	ka  =				_ka;
	CorrectKeyArr (ka, classID, indexID);
	key_arr			ka_rbound;
	ka_rbound  =  _ka_rbound;
	CorrectKeyArr (ka_rbound, classID, indexID);

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_GetIndexNumForKey: Значение индекса не определено":"OBD_GetIndexNumForKey: Значение индекса выходит за рамки");
		return 0;
	}

	if (indexID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_GetIndexNumForKey: Поиск объекта класса '%s' при неопределённом индексе", className[classID]);
		return 0;		
	}

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

// Проверки
	for (int kki=0; kki<2; kki++)
	{
		key_arr * pka = kki==0? &ka: kki==1? &ka_rbound: NULL;
		SERVER_DEBUG_ASSERT_RETURN (pka, "System Error", 0);

	//	Число ключей для поиска
		int keyNum = pka->GetKeyNum ();

	// Указано слишком много ключей для поиска
		if (keyNum > indexInfo.m_keyNum)
		{
			SERVER_DEBUG_ERROR ("OBD_GetIndexNumForKey: Указано слишком много ключей для поиска");
			return 0;
		}

	// Проверяем типы ключей
		for (int k=0; k < keyNum; k++) 
		{
			if (indexInfo.m_keyType[k] != pka->GetItemType(k))
			{
				SERVER_DEBUG_ERROR ("OBD_GetIndexNumForKey: Указаны неверные типы ключей");
				return 0;
			}
		}
	}

// Общее число объектов в индексе
	if (ka.GetKeyNum()==0 && ka_rbound.GetKeyNum()==0 && !bUnique)
	{
		return pIndexTree->Count();
	}

// Ищем в индексе
	pbyte arg0 = ka.GetPtr();
	pbyte arg1 = NULL;
	pbyte arg_rbound = ka_rbound.GetKeyNum()!=0? ka_rbound.GetPtr(): NULL;
	size_t nResultNum  = 0;
	for (OBD_pointer coIndexPtr = pIndexTree->Find (arg0); coIndexPtr!=NULL; coIndexPtr=pIndexTree->Next (coIndexPtr))
	{
		pbyte arg2 = pIndexTree->ItemPointer (coIndexPtr)->GetPtr();

	//	Проверка на выход за пределы второго ключа
		if (arg_rbound!=NULL && CompareFunction_CObjIndex_AVTree_Item (arg_rbound, arg2)<0)
			break;

	//	Результат сравнения левого ключа с объектом
		int nCompare = CompareFunction_CObjIndex_AVTree_Item (arg0, arg2);

	//	Левый ключ больше объекта
		if (nCompare>0)
		{
			SERVER_DEBUG_ERROR ("Ошибка индексирования");
			break;
		}

	//	Левый ключ меньше объекта и ищем без использования правой границы
	// т.е. необходимо точное совпадение ключа.
		if ((nCompare!=0) && (arg_rbound==NULL))
			break;

	//	Увеличиваем счётчик (с проверкой на уникальность)
		if (bUnique)
		{
			IGNORE_LAST_KEY_IDENTIFIER = true;
			{
				nResultNum += (arg1==NULL || (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)!=0));
			}
			IGNORE_LAST_KEY_IDENTIFIER = false;
		}
		else 
		{
			nResultNum ++;
		}

	//	Запоминаем предыдущее значение для проверки на уникальность
		arg1 = arg2;
	}
	
	return nResultNum;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// Число всех объектов класса																	[]
//                                                                            []
size_t OBD_IndexTotalNum (long classID)
{
// По первому индексу
	identifier indexID = 0;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR_1 ("OBD_IndexTotalNum: Общее число объектов класса '%s' не может быть подсчитано -- класс не имеет индексов", className[classID]);
		return 0;
	}

	return theObjDriver.GetIndexPtr (classID, indexID)->AVTree.Count ();
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор первого/последнего объекта по индексу					[]
//                                                                            []
identifier OBD_FirstLastIDInIndex (long classID, const CIndexInfo& indexInfo, OBD_FIND findType)
{
	DEBUG_STACK_NAME (OBD_FirstLastIDInIndex);

	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_FirstLastIDInIndex: Значение индекса не определено":"OBD_FirstLastIDInIndex: Значение индекса выходит за рамки");
		return NA;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = NULL;

	if (findType == OBD_FIND_First)
	{
		coIndexPtr = pIndexTree->First ();
	}
	else if (findType == OBD_FIND_Last)
	{
		coIndexPtr = pIndexTree->Last ();
	}

// Если нашли -- вернуть id объекта
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			identifier objID = pItem->GetObjID ();			
			return objID;
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_FirstLastIDInIndex: Ошибка при поиске объекта: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NA;
		}
	}
	return NA;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор первого объекта по индексу									[]
//                                                                            []
identifier OBD_FirstIDInIndex (long classID, const CIndexInfo& indexInfo)
{
	DEBUG_STACK_NAME (OBD_FirstIDInIndex);

	return OBD_FirstLastIDInIndex (classID, indexInfo, OBD_FIND_First);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор последнего объекта по индексу								[]
//                                                                            []
identifier OBD_LastIDInIndex (long classID, const CIndexInfo& indexInfo)
{
	DEBUG_STACK_NAME (OBD_LastIDInIndex);

	return OBD_FirstLastIDInIndex (classID, indexInfo, OBD_FIND_Last);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Найти следующий/предыдущий/первый/последний объект								[]
//                                                                            []
OBD_pointer OBD_IndexNextPrevFirstLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, OBD_FIND findType, key_arr* _pka, bool bUnique, bool bSame)
{
	DEBUG_STACK_NAME (OBD_IndexNextPrevFirstLastObject);

	identifier indexID = indexInfo.m_id;

// Корректируем набор ключей -- для случая, если имеет место обратная сортировка
	key_arr * pka=NULL;
	if (_pka)
	{
		pka  =  new key_arr;
		(*pka) = (*_pka);
		CorrectKeyArr (*pka, classID, indexID);
	}

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_IndexNextPrevFirstLastObject: Значение индекса не определено":"OBD_IndexNextPrevFirstLastObject: Значение индекса выходит за рамки");
		return NULL;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// Указано слишком много ключей для поиска
	if (pka) if (((int)pka->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: Указано слишком много ключей для поиска");
		return NULL;
	}

// Проверяем типы ключей
	if (pka) for (int k=0; k < (int)pka->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: Указаны неверные типы ключей");
			return NULL;
		}
	}

// Дерево-индекс
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = NULL;

	if ((findType == OBD_FIND_Next) || (findType == OBD_FIND_Prev))
	{
		IF_OBJECT_INVALID {return NULL;}
		OD_BASE* pData = (OD_BASE*)aObject->pData;
		OBD_pointer old_coIndexPtr = pData->m_CoIndexPtr[indexID];
	// Объект не знает своего места в индексе
		if (old_coIndexPtr==NULL)
		{
			pData->m_CoIndexPtr[indexID] = old_coIndexPtr = OBD_FindObjectByOwnData (classID, pData, aObject->objID, pObjDriveIndex, indexID);
		}
	// Объект не присутствует в индексе
		if (old_coIndexPtr==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: Объект класса '%s' не присутствует в индексе %d", className[classID], indexID);
			return NULL;
		}
		CObjIndex_AVTree_Item * pStartItem = pIndexTree->ItemPointer (old_coIndexPtr);
		if (pStartItem == NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: Ошибка получения элемента индекса %d для объект класса '%s'", indexID, className[classID]);
			return NULL;
		}

	//----------------------------------------------------------------------------[] 
	// Находим следующий/предыдущий объект
		bool bContinue = false;
		do 
		{
			bContinue = false;
			if (bSame)
			{
				coIndexPtr = ((findType == OBD_FIND_Prev)? pIndexTree->PrevWithSameKey (old_coIndexPtr): pIndexTree->NextWithSameKey (old_coIndexPtr));
			}
			else
			{
				coIndexPtr = ((findType == OBD_FIND_Prev)? pIndexTree->Prev (old_coIndexPtr): pIndexTree->Next (old_coIndexPtr));
			}

			if (coIndexPtr && pka!=NULL && !bSame)
			{
				CObjIndex_AVTree_Item * pNextPrevItem = pIndexTree->ItemPointer (coIndexPtr);
				if (pNextPrevItem == NULL)
				{
					SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: Ошибка получения элемента индекса %d для объект класса '%s'", indexID, className[classID]);
					return NULL;
				}
				pbyte arg0 = pStartItem->GetPtr   ();	// Собственный полный ключ
				pbyte arg1 = pka->GetPtr          ();	// Ключ поиска
				pbyte arg2 = pNextPrevItem->GetPtr();	// Полный ключ следующего объекта

			// Ключ следущего не подходит -- ничего не нашли
				if (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)!=0)
				{
					coIndexPtr = NULL;
				}

			// Ключ следущего подходит, но надо сравнить с начальным
				if (coIndexPtr && bUnique)
				{
				// Ключ следущего подходит, но он равен начальному -- бежим дальше
					IGNORE_LAST_KEY_IDENTIFIER = true;
					{
						if ((CompareFunction_CObjIndex_AVTree_Item (arg0, arg2)==0))
						{
							old_coIndexPtr = coIndexPtr;
							bContinue		= true;
						}
					}
					IGNORE_LAST_KEY_IDENTIFIER = false;
				}
			}
		} while (bContinue);
	// Нашли следующий/предыдущий объект
	//----------------------------------------------------------------------------[] 
	}
	else if (findType == OBD_FIND_First)
	{
		coIndexPtr = pIndexTree->First ();
	}
	else if (findType == OBD_FIND_Last)
	{
		coIndexPtr = pIndexTree->Last ();
	}

// Удаляем временный скорректированный ключ
	if (pka){
		delete pka;
	}

	
// Если нашли -- открываем объект
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			return OBD_GetObject (classID, pItem->GetObjID (), indexID, coIndexPtr);
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: Ошибка при поиске объекта: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NULL;
		}
	}
	return NULL;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Найти следующий объект																		[]
//                                                                            []
OBD_pointer OBD_IndexNextObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame)
{
	DEBUG_STACK_NAME (OBD_IndexNextObject);

	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Next, pka, bUnique, bSame);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Найти предыдущий	объект																	[]
//                                                                            []
OBD_pointer OBD_IndexPrevObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame)
{
	DEBUG_STACK_NAME (OBD_IndexPrevObject);

	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Prev, pka, bUnique, bSame);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Найти первый	объект																		[]
//                                                                            []
OBD_pointer OBD_IndexFirstObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_IndexFirstObject);

	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_First, NULL, false);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Найти последний объект																		[]
//                                                                            []
OBD_pointer OBD_IndexLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBD_IndexLastObject);

	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Last, NULL, false);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Сохранить определённый индекс															[]
//                                                                            []	
void OBD_SaveIndexToFile (long classID, const CIndexInfo& indexInfo)
{
	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_SaveIndexToFile: Значение индекса не определено":"OBD_SaveIndexToFile: Значение индекса выходит за рамки");
		return;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	pObjDriveIndex->Save ();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Сохранить все изменённые данные															[]
//                                                                            []	
void OBD_SaveAllData ()
{
	int indexID;
	int classID;

// Сохраняем все индексы всех классов
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

	// Сохраняем все индексы
		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Save ();
		}
	}

// Сохраняем все объекты, загруженные в память
	OBD_pointer coPtr = OBD_AllObjectsInMemory.First ();
	while (coPtr)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR ("OBD_SaveAllData: Ошибка поиска объекта:  aObject==NULL");
			continue;
		}
		else if (!aObject->Save ())
		{
			OD_BASE * pBase = (OD_BASE *) (aObject->pData);
			identifier classID = pBase->classID;
			SERVER_DEBUG_ERROR_2 ("OBD_SaveAllData: Ошибка записи объекта %s[%d]:  !aObject->Save ()", className[classID], aObject->objID);
		}
		
		coPtr = OBD_AllObjectsInMemory.Next (coPtr);
	}

// Сохраняем изменения в файловой системе
	theFileDriver.flush();
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Перегрузить все индексы																	[]
//                                                                            []	
void OBD_ReloadAllBase ()
{
	DEBUG_STACK_NAME (OBD_ReloadAllBase);

	int indexID;
	int classID;

// Сбрасываем указатели в индекс для всех объектов, загруженных в память
	OBD_pointer coPtr = OBD_AllObjectsInMemory.First ();
	while (coPtr)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR ("OBD_SaveAllData: Ошибка поиска объекта:  aObject==NULL");
			return;
		}
		else
		{
			OD_BASE * pBase = (OD_BASE *) (aObject->pData);
			identifier classID = pBase->classID;
			int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();
			for (indexID=0; indexID < IndexNum;  indexID++)
			{
				pData_m_CoIndexPtr (classID, aObject->pData, indexID, NULL);
			}
			if (!aObject->Save ())
			{
				OD_BASE * pBase = (OD_BASE *) (aObject->pData);
				identifier classID = pBase->classID;
				SERVER_DEBUG_ERROR_2 ("OBD_SaveAllData: Ошибка записи объекта %s[%d]:  !aObject->Save ()", className[classID], aObject->objID);
			}
		}
		coPtr = OBD_AllObjectsInMemory.Next (coPtr);
	}

// Сохраняем все индексы
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();
		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Save ();
		}
	}

// Сохраняем изменения в файловой системе
	theFileDriver.flush();

// Загружаем все индексы
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Load ();
		}
	}
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
