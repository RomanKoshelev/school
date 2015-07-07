/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 2000 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjCache.cpp																[]
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
#define	USES_stopwatch_h

#include "main.h"
#include "OBD.h"
#include "ObjCache.h"

#ifndef  ZOOB_UTILS

//----------------------------------------------------------------------------[] 
//
//	Настройки кэша
//

#define Config_USES_OBJ_CACHE
#define config_MAX_OBJ_IN_CACHE		 (30*1000) // !!! Вынести в config
#define config_REMOVE_OBJ_FROM_CACHE	  (300)

int		MIN_ESTIMATE		=	(-1000*1000);
int		MAX_ESTIMATE		=	 (1000*1000);

int		BASE_ESTIMATE		=		100;
int		LOAD_ESTIMATE		=		100;
//----------------------------------------------------------------------------[] 


#ifdef Config_USES_OBJ_CACHE
	bool  USES_OBJ_CACHE = true;
#else
	bool  USES_OBJ_CACHE = false;
#endif



//______________________________________________________________________________
//                                                                            []
// Элемент кеша																					[]
//                                                                            []
OBJ_CACHE_ITEM::OBJ_CACHE_ITEM ()
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_OBJ_CACHE_ITEM);

	coPtr					= NULL;

	m_Hits				= 0;
	m_FirstAccessTime	= 0;	
	m_LastAccessTime	= 0;
	                     
	m_Estimate			= 0;
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM::~OBJ_CACHE_ITEM ()
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_Destructor);

	Release ();
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM::OBJ_CACHE_ITEM (OBJ_CACHE_ITEM& from)
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_OBJ_CACHE_ITEM_OBJ_CACHE_ITEM_from);

	CopyFrom (from);
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM& OBJ_CACHE_ITEM::operator = (OBJ_CACHE_ITEM& from)
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_operator_assign);

	return CopyFrom (from);
}
//----------------------------------------------------------------------------[] 
OBJ_CACHE_ITEM& OBJ_CACHE_ITEM::CopyFrom (OBJ_CACHE_ITEM& from)
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_CopyFrom);

	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (from.coPtr);
	SERVER_DEBUG_ASSERT_RETURN (aObject, "OBJ_CACHE_ITEM::CopyFrom: aObject==NULL;", *this);

	aObject->AddRef	();
	aObject->nCached++;

	coPtr					= from.coPtr;

	m_Hits				= from.m_Hits;
	m_FirstAccessTime	= from.m_FirstAccessTime;
	m_LastAccessTime	= from.m_LastAccessTime;
                                      
	m_Estimate			= from.m_Estimate;

	return *this;
}
//----------------------------------------------------------------------------[] 
size_t OBJ_CACHE_ITEM::Release ()
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_Release);

	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	SERVER_DEBUG_ASSERT_RETURN (aObject, "OBJ_CACHE_ITEM::Release: aObject==NULL;", 0);

	aObject->nCached--;

	if (aObject->ref > 1)
	{
		DEBUG_STACK_NAME (OBJ_CACHE_ITEM_Release_1);
		return aObject->Release ();
	}
	else
	{
		DEBUG_STACK_NAME (OBJ_CACHE_ITEM_Release_2);
		return OBD_ReleaseObject (aObject->classID, coPtr, aObject);
	}

	return 0;
}
//----------------------------------------------------------------------------[] 
int OBJ_CACHE_ITEM::MakeEstimate (CAbstractObjectInMemory * aObject)
{
	DEBUG_STACK_NAME (OBJ_CACHE_ITEM_MakeEstimate);

	m_Estimate = 0;
	
	int nTimeInCache	= (m_LastAccessTime - m_FirstAccessTime);

	if (aObject->bDeleted)
	{
		m_Estimate = MIN_ESTIMATE;
	}
	else if (aObject->ref>1) // 2
	{
		m_Estimate =  MAX_ESTIMATE; // MIN_ESTIMATE
	}
	else if (nTimeInCache == 0)
	{
		m_Estimate =  MAX_ESTIMATE;
//		puts ("!");
	}
	else
	{
		m_Estimate = MAX_ESTIMATE;
//		puts ("!");

#if 0  //{ RomanVK
		TIMER_TYPE nAveClassLoadTime = the_OBJ_CACHE.m_ClassStats[aObject->classID].AveLoadTime;
		TIMER_TYPE nAveClassSaveTime = the_OBJ_CACHE.m_ClassStats[aObject->classID].AveSaveTime;


	// Время, которое уйдёт на запись объекта на диск в случае его выгрузки из кэша
		int TimeForSave	=	10 * (aObject->bChanged==false? 0: (int)nAveClassSaveTime);

	// Время, которое уйдёт на повторное зачитывание объекта в случае его выгрузки из кэша
		int nFreq			=	10000 * m_Hits / nTimeInCache;
		int TimeForLoad	=	nAveClassLoadTime * nFreq;

	// Среднее время, которое потеряется в случае выгрузки объекта из кэша
		m_Estimate += TimeForSave;
//		m_Estimate += TimeForLoad;
#endif //}
	}

	return m_Estimate;
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
	DEBUG_STACK_NAME (OBJ_CACHE_OBJ_CACHE);

	m_pCACHE				= new CACHE_TREE (&OBJ_CACHE_ITEM::m_Estimate, CompareFunction_OBJ_CACHE_ITEM);
	m_Busy				= false;
	m_nCleanOut			= 0;
	m_IniCleanOutTime	= 0;
	m_CleanOutTime		= 0;
	m_StartTime			= time(0);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Деструктор																						[]
//                                                                            []
OBJ_CACHE::~OBJ_CACHE ()
{
	DEBUG_STACK_NAME (OBJ_CACHE_Destructor);
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
	DEBUG_STACK_NAME (OBJ_CACHE_Clear);

	if (m_pCACHE)
	{
		m_Busy = true;
		m_pCACHE->RemoveAll();
		m_Busy = false;
		m_ClassStats.Erase ();
	}
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Обновление кэша																				[]
//                                                                            []
void OBJ_CACHE::Update (OBD_pointer coPtr, OBJ_CACHE_UPDATE_TYPE Flag)
{
	DEBUG_STACK_NAME (OBJ_CACHE_Update);

	if (!USES_OBJ_CACHE)			return;
	if (m_Busy)						return;
	m_Busy							= true;


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Создаём новый элемент кэша
	OBJ_CACHE_ITEM		newItem;
	time_t cur_Time = time_0;

// Получаем доступ к aObject
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	SERVER_DEBUG_ASSERT (aObject->nCached>=0, "OBJ_CACHE::Update: aObject->nCached<0");

// Если объект в кэше -- на него есть ссылка из coPtr
	item_pointer ItemID = (aObject->nCached!=0) ?  aObject->pCachePtr : NULL;

// Объект находится в кэше
	if (ItemID!=NULL)
	{
		DEBUG_STACK_NAME (OBJ_CACHE_Update_1);
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
		DEBUG_STACK_NAME (OBJ_CACHE_Update_2);
		aObject->AddRef ();
		aObject->nCached++;

		newItem.m_FirstAccessTime	= cur_Time;
		newItem.m_Estimate			= 0;
		newItem.coPtr					= coPtr;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Изменяем элемент кэша
	if (Flag==OCUT_ON_OPEN || Flag==OCUT_ON_CREATE)
	{
		DEBUG_STACK_NAME (OBJ_CACHE_Update_3);
		newItem.m_LastAccessTime	= cur_Time;
		newItem.m_Hits					++;
	}
	newItem.MakeEstimate	(aObject);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - [] 
// Обновляем кэш
	if (Flag==OCUT_ON_DELETE)
	{
		DEBUG_STACK_NAME (OBJ_CACHE_Update_4);
		m_pCACHE->Remove (ItemID);
	}
	else
	{
		DEBUG_STACK_NAME (OBJ_CACHE_Update_5);
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
	DEBUG_STACK_NAME (OBJ_CACHE_OnOpen);
	Update (coPtr, OCUT_ON_OPEN);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnClose (OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBJ_CACHE_OnClose);
	Update (coPtr, OCUT_ON_CLOSE);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnCreate (OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBJ_CACHE_OnCreate);
	Update (coPtr, OCUT_ON_CREATE);
}
//----------------------------------------------------------------------------[] 
void OBJ_CACHE::OnDelete (OBD_pointer coPtr)
{
	DEBUG_STACK_NAME (OBJ_CACHE_OnDelete);
	Update (coPtr, OCUT_ON_DELETE);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` UpdateClassStats                                                          []                
//                                                                            []
void OBJ_CACHE::UpdateClassStats (identifier classID, TIMER_TYPE time, OBJ_CACHE_UPDATE_TYPE Flag)
{
	DEBUG_STACK_NAME (OBJ_CACHE_UpdateClassStats);

	if ((int)m_ClassStats.Size()<=(int)classID)
	{
		m_ClassStats.Realloc (classID+1);
	}

	if (Flag == OCUT_ON_OPEN)
	{
		m_ClassStats[classID].Total_LoadTime	+= time;
		m_ClassStats[classID].LoadNum				++;
		m_ClassStats[classID].AveLoadTime		= (int) (m_ClassStats[classID].Total_LoadTime / m_ClassStats[classID].LoadNum);
	}

	if (Flag == OCUT_ON_CLOSE)
	{
		m_ClassStats[classID].Total_SaveTime	+= time;
		m_ClassStats[classID].SaveNum				++;
		m_ClassStats[classID].AveSaveTime		= (int) (m_ClassStats[classID].Total_SaveTime / m_ClassStats[classID].SaveNum);
	}
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Прочистка кэша																				[]                  
//                                                                            []
void OBJ_CACHE::CleanOut ()
{
	DEBUG_STACK_NAME (OBJ_CACHE_CleanOut);

	m_Busy = true;

	int MAX_OBJ_IN_CACHE	= config_MAX_OBJ_IN_CACHE; 
	int MIN_OBJ_IN_CACHE = MAX_OBJ_IN_CACHE - config_REMOVE_OBJ_FROM_CACHE;

	if (m_pCACHE->Count()>=MAX_OBJ_IN_CACHE)
	{
		static bool bFirstTime = true;
		if (bFirstTime) printf ("\n\n* OBJ_CACHE::CleanOut ()\n");
		bFirstTime = false;

		StopWatch Timer;
		Timer.Start();
		
		while (m_pCACHE->Count()>=MIN_OBJ_IN_CACHE)
		{
			m_pCACHE->Remove (m_pCACHE->First());
		}
		Timer.Stop();
		m_CleanOutTime += (int)Timer.GetTime();

		if (m_IniCleanOutTime==0) m_IniCleanOutTime = time(0);
		m_nCleanOut++;
	}
	m_Busy = false;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Получение спарвки о работе Кэша                                           []                               
//                                                                            []
void OBJ_CACHE::DebugPrint	(string& Info)
{
	DEBUG_STACK_NAME (OBJ_CACHE_DebugPrint);

	char				SSS[10240];
	int				i;
	item_pointer	ppItem;

	Info += "\n\n\n==========================================================================================\n\n";

	sprintf (SSS, "  Max cache size:   %7d\n  Objects in cache: %7d\n\n", config_MAX_OBJ_IN_CACHE, m_pCACHE ? m_pCACHE->Count():0);
	Info += SSS;

	for (i=0; i<(int)m_ClassStats.Size(); i++)
	{
		m_ClassStats[i].nCount = 0;
	}
	for (ppItem = m_pCACHE->First(); ppItem!=NULL; ppItem = m_pCACHE->Next(ppItem))
	{
		OBJ_CACHE_ITEM * pItem = m_pCACHE->ItemPointer (ppItem);
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (pItem->coPtr);
		if ((int)aObject->classID < (int)m_ClassStats.GetSize()) m_ClassStats[aObject->classID].nCount ++;
	}

// Input/Output Class Statistics
	Info += "\n\n\n Class Statistics:";
	Info += "\n ==============================================================================";
	Info += "\n  CLASS               [ LOAD TIME ]   [ SAVE TIME ]   [ CACHED ]   [ LOAD NUM ]\n ------------------------------------------------------------------------------";
	for (i=0; i<(int)m_ClassStats.Size(); i++)// if (m_ClassStats[i].LoadNum)
	{
		snprintf (SSS,	1024, "\n  %-19s ", className[i]);
		Info += SSS;
		if (m_ClassStats[i].LoadNum)	sprintf (SSS,	"[%7d mks]   ", (int)m_ClassStats[i].AveLoadTime);
		else									sprintf (SSS,	"[     -     ]   ");
		Info += SSS;
		if (m_ClassStats[i].SaveNum)	sprintf (SSS,	"[%7d mks]   ", (int)m_ClassStats[i].AveSaveTime);
		else									sprintf (SSS,	"[     -     ]   ");
		Info += SSS;
		if (m_ClassStats[i].nCount)	sprintf (SSS,	"[%7d ]   ", (int)m_ClassStats[i].nCount);
		else									sprintf (SSS,	"[      - ]   ");
		Info += SSS;
		if (m_ClassStats[i].LoadNum)	sprintf (SSS,	"[%9d ]   ", (int)m_ClassStats[i].LoadNum);
		else									sprintf (SSS,	"[        - ]   ");
		Info += SSS;
	}
	Info += "\n ==============================================================================\n\n\n";


//	Number of CleanOut Operations
	time_t cur_Time = time(0);
	Info += "\n CleanOut Operations:\n";
	Info += " ==========================================\n";
	sprintf (SSS, "  Number:    %5d\n  Per hour:  %5d\n", m_nCleanOut, m_IniCleanOutTime? (60*60*m_nCleanOut/max (1, (cur_Time - m_IniCleanOutTime))) : 0);
	Info += SSS;
	sprintf (SSS, "  Total time: %5.2f sec [%.2f %%]\n", float(m_CleanOutTime)/1000/1000, (float(m_CleanOutTime)/1000/10) / max (1, (/* !!! Замениеть на TOTAL_PROC_TIME */cur_Time - m_StartTime)));
	Info += SSS;
	Info += "\n ==========================================\n\n\n";

// Cache contents

	Info += "\n==========================================================================================\n\n\n\n";

/*
m_pCACHE->Remove (m_pCACHE->First()):      Total time:  1.88 sec (1.26 %)
m_pCACHE->Remove (m_pCACHE->Last ()):      Total time: 35.07 sec (15.66 %)
m_pCACHE->Remove (rand()):                 Total time: 28.65 sec (13.91 %)
*/
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Число объектов в Кэше                                                     []                     
//                                                                            []
int OBJ_CACHE::GetItemNum ()
{
	return m_pCACHE ? m_pCACHE->Count() : 0;
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
