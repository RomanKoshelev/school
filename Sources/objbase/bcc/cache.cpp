/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 2000 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            CACHE.cpp																	[]
[] Author:          Roman V. Koshelev														[]
[] Description:     Кеширование частоиспользуемыхх объектов базы данных			[]
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
#include "OBD.h"
#include "CACHE.h"

#ifndef  LAY_COMPILER_PROJECT



#ifdef Config_USES_OBJ_CACHE
	bool  USES_OBJ_CACHE = true;
#else
	bool  USES_OBJ_CACHE = false;
#endif



//----------------------------------------------------------------------------[] 
//
//	Настройки кэша
//
#define Config_USES_OBJ_CACHE

#define Config_OBJ_CACHE_ITEM_TimeInCache_WEIGHT       1		// Продолжительность пребывания в памяти
#define Config_OBJ_CACHE_ITEM_Hits_WEIGHT              0		// Число загрузок объекта с диска
#define Config_OBJ_CACHE_ITEM_aObject_bChanged_WEIGHT  0		// Объект был изменён и будет записан на диск
#define Config_OBJ_CACHE_ITEM_aObject_nSize_WEIGHT     0		// Размер объекта в памяти
                                              
#define Config_OBJ_CACHE_ITEM_aObject_ref_WEIGHT       0		// Число ссылок на объект
#define Config_OBJ_CACHE_ITEM_aObject_bDeleted_WEIGHT  0		// Объект удалён
//----------------------------------------------------------------------------[] 




//______________________________________________________________________________
//                                                                            []
// Элемент кеша																					[]
//                                                                            []
OBJ_CACHE_ITEM::OBJ_CACHE_ITEM ()
{
	coPtr					= NULL;

	m_Hits				= 0;
	m_FirstAccessTime	= 0;	
	m_LastAccessTime	= 0;
	                     
	m_Estimation		= 0;
}
//----------------------------------------------------------------------------[] 
int OBJ_CACHE_ITEM::m_TimeInCache_WEIGHT			= Config_OBJ_CACHE_ITEM_TimeInCache_WEIGHT;
int OBJ_CACHE_ITEM::m_Hits_WEIGHT					= Config_OBJ_CACHE_ITEM_Hits_WEIGHT;
int OBJ_CACHE_ITEM::m_aObject_bChanged_WEIGHT	= Config_OBJ_CACHE_ITEM_aObject_bChanged_WEIGHT;
int OBJ_CACHE_ITEM::m_aObject_nSize_WEIGHT		= Config_OBJ_CACHE_ITEM_aObject_nSize_WEIGHT;
																                                           
int OBJ_CACHE_ITEM::m_aObject_ref_WEIGHT			= Config_OBJ_CACHE_ITEM_aObject_ref_WEIGHT;
int OBJ_CACHE_ITEM::m_aObject_bDeleted_WEIGHT	= Config_OBJ_CACHE_ITEM_aObject_bDeleted_WEIGHT;
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM::~OBJ_CACHE_ITEM ()
{
	Release ();
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM::OBJ_CACHE_ITEM (OBJ_CACHE_ITEM& from)
{
	CopyFrom (from);
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM& OBJ_CACHE_ITEM::operator = (OBJ_CACHE_ITEM& from)
{
	return CopyFrom (from);
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM& OBJ_CACHE_ITEM::CopyFrom (OBJ_CACHE_ITEM& from)
{
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (from.coPtr);
	SERVER_DEBUG_ASSERT_RETURN (aObject, "OBJ_CACHE_ITEM::CopyFrom: aObject==NULL;", *this);

	aObject->AddRef	();
	aObject->nCached++;

	coPtr					= from.coPtr;

	m_Hits				= from.m_Hits;
	m_FirstAccessTime	= from.m_FirstAccessTime;
	m_LastAccessTime	= from.m_LastAccessTime;
                                      
	m_Estimation		= from.m_Estimation;

	return *this;
}
//----------------------------------------------------------------------------[] 
size_t OBJ_CACHE_ITEM::Release ()
{
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	SERVER_DEBUG_ASSERT_RETURN (aObject, "OBJ_CACHE_ITEM::Release: aObject==NULL;", 0);

	aObject->nCached--;

	if (aObject->ref > 1)
	{
		return aObject->Release ();
	}
	else
	{
		return OBD_ReleaseObject (aObject->classID, coPtr, aObject);
	}

	return 0;
}
//----------------------------------------------------------------------------[] 
int OBJ_CACHE_ITEM::MakeEstimation (CAbstractObjectInMemory * aObject)
{
	m_Estimation +=  m_TimeInCache_WEIGHT				* (m_LastAccessTime - m_FirstAccessTime);
	m_Estimation +=  m_Hits_WEIGHT						*	m_Hits;

	m_Estimation +=  m_aObject_ref_WEIGHT				*	aObject->ref;
	m_Estimation +=  m_aObject_bChanged_WEIGHT		*	aObject->bChanged;
	m_Estimation +=  m_aObject_bDeleted_WEIGHT		*	aObject->bDeleted;
	
	m_Estimation +=  m_aObject_nSize_WEIGHT			*	aObject->nSize;

	return m_Estimation;
}
//____________________________________________________________________________[]












/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` КЭШ ОБЪЕКТОВ БАЗЫ ДАННЫХ                                                  []                        
[]                                                                            []
[]____________________________________________________________________________[]
*/



//______________________________________________________________________________
//                                                                            []
// CompareFunction_OBJ_CACHE_ITEM															[]
//                                                                            []
int CompareFunction_OBJ_CACHE_ITEM (int& a, int& b)
{
	return a-b;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Конструктор																					[]
//                                                                            []
OBJ_CACHE::OBJ_CACHE ()
{
	m_pCACHE		= new CACHE_TREE (&OBJ_CACHE_ITEM::m_Estimation, CompareFunction_OBJ_CACHE_ITEM);
	m_Busy		= false;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Деструктор																						[]
//                                                                            []
OBJ_CACHE::~OBJ_CACHE ()
{
	delete m_pCACHE;
	m_pCACHE	= NULL;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Очистка																							[]
//                                                                            []
void OBJ_CACHE::Clear ()
{
	if (m_pCACHE)
	{
		m_Busy = true;
		m_pCACHE->RemoveAll();
		m_Busy = false;
	}
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Обновление кэша																				[]
//                                                                            []
void OBJ_CACHE::Update (OBD_pointer coPtr, OBJ_CACHE_UPDATE_TYPE Flag)
{
	if (!USES_OBJ_CACHE)			return;
	if (m_Busy)						return;
	m_Busy							= true;


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Создаём новый элемент кэша
	OBJ_CACHE_ITEM		newItem;
	time_t cur_Time = time(0);

// Получаем доступ к aObject
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	SERVER_DEBUG_ASSERT (aObject->nCached>=0, "OBJ_CACHE::Update: aObject->nCached<0");

// Если объект в кэше -- на него есть ссылка из coPtr
	item_pointer ItemID = (aObject->nCached!=0) ?  aObject->pCachePtr : NULL;

// Объект находится в кэше
	if (ItemID!=NULL)
	{
		OBJ_CACHE_ITEM * pItem = m_pCACHE->ItemPointer (ItemID);
		SERVER_DEBUG_ASSERT (pItem, "OBJ_CACHE: Не удалось найти элемент в дереве");
		newItem.CopyFrom (*pItem);
		SERVER_DEBUG_ASSERT (newItem.coPtr==coPtr, "OBJ_CACHE: Несвязанность -- newItem.coPtr!=coPtr");
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Если объект не закэширован -- кешируем его
	if (ItemID==NULL && (Flag==OCUT_ON_OPEN || Flag==OCUT_ON_CREATE))
	{
		aObject->AddRef ();
		aObject->nCached++;

		newItem.m_FirstAccessTime	= cur_Time;
		newItem.m_Estimation			= 0;
		newItem.coPtr					= coPtr;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Обновляем элемент кэша
	newItem.m_LastAccessTime		= cur_Time;
	newItem.MakeEstimation			(aObject);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Обновляем кэш

	if (Flag==OCUT_ON_DELETE)
	{
		m_pCACHE->Remove (ItemID);
	}
	else
	{
		aObject->pCachePtr = m_pCACHE->Replace (ItemID, newItem);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
	m_Busy					= false;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
// Обработка кэше событий базы данных														[]
//                                                                            []
void OBJ_CACHE::OnOpen (OBD_pointer coPtr)
{
	Update (coPtr, OCUT_ON_OPEN);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnClose (OBD_pointer coPtr)
{
	Update (coPtr, OCUT_ON_CLOSE);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnCreate (OBD_pointer coPtr)
{
	Update (coPtr, OCUT_ON_CREATE);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnDelete (OBD_pointer coPtr)
{
	Update (coPtr, OCUT_ON_DELETE);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Обработчик времени                                                        []                  
//                                                                            []
void OBJ_CACHE::OnTimer (time_t cur_Time)
{
	m_Busy = true;

	(void) cur_Time;
	
	m_Busy = false;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Получение спарвки о работе Кэша                                           []                               
//                                                                            []
void OBJ_CACHE::DebugPrint	(string& Info)
{
	(void) Info;
}
//____________________________________________________________________________[]




#else
	OBJ_CACHE::OBJ_CACHE (){}
	OBJ_CACHE::~OBJ_CACHE (){}
#endif

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
