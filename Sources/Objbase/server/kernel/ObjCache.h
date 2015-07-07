/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 2000 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjCache.h																[]
[] Author:          Roman V. Koshelev														[]
[] Description:     Интерфейс к кешу частоиспользуемыхх объектов базы данных	[]
[]____________________________________________________________________________[]
*/

#ifndef	ObjCache_h
#define	ObjCache_h


//______________________________________________________________________________
//                                                                            []
//` OBJ_CACHE_ITEM                                                            []              
//                                                                            []
struct OBJ_CACHE_ITEM
{
	OBD_pointer coPtr;					// Указатель на объект-данные

	int			m_Hits;					// Число загрузок объекта-данные за время его кеширования
	time_t		m_FirstAccessTime;	// Время первого обращения к объекту-данные
	time_t		m_LastAccessTime;		// Время последнего обращения к объекту-данные

	int			m_Estimate;				// Оценка системных затрат в случае выгрузки из кэша

	OBJ_CACHE_ITEM ();
  ~OBJ_CACHE_ITEM ();
	OBJ_CACHE_ITEM (OBJ_CACHE_ITEM& from);

	OBJ_CACHE_ITEM& operator = (OBJ_CACHE_ITEM& from);
	OBJ_CACHE_ITEM& CopyFrom	(OBJ_CACHE_ITEM& from);

	int			MakeEstimate	(CAbstractObjectInMemory * aObject);
	size_t		Release ();
};
//----------------------------------------------------------------------------[] 
typedef IT_AVTree<OBJ_CACHE_ITEM, int, int OBJ_CACHE_ITEM::*> CACHE_TREE;
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[] 
enum OBJ_CACHE_UPDATE_TYPE
{
	OCUT_ON_OPEN		= 0,
	OCUT_ON_CLOSE		= 1,
	OCUT_ON_CREATE		= 2,
	OCUT_ON_DELETE		= 3,
	OCUT_END				= 0xFFFF
};
//----------------------------------------------------------------------------[] 
struct OBJ_CACHE_CLASS_STATS
{
	TIMER_TYPE	Total_LoadTime;
	TIMER_TYPE	Total_SaveTime;

	int			LoadNum;
	int			SaveNum;

	int			nCount;

	TIMER_TYPE	AveSaveTime;
	TIMER_TYPE	AveLoadTime;

	OBJ_CACHE_CLASS_STATS ()
	{
		Total_LoadTime = 0;
		Total_SaveTime = 0;

		LoadNum			= 0;
		SaveNum			= 0;

		AveSaveTime		= 0;
		AveLoadTime		= 0;
	}
};
//----------------------------------------------------------------------------[] 



//______________________________________________________________________________
//                                                                            []
//` OBJ_CACHE                                                                 []         
//                                                                            []
struct OBJ_CACHE
{
	bool									m_Busy;
	CACHE_TREE *						m_pCACHE;
	CPtr<OBJ_CACHE_CLASS_STATS>	m_ClassStats;
	int									m_nCleanOut;			// Число прочисток кэша
	time_t								m_IniCleanOutTime;	// Время первой прочистки кэша
	time_t								m_CleanOutTime;		// Общее время на прочистку кеша
	time_t								m_StartTime;			// Время начала работы
	

	OBJ_CACHE					();
	~OBJ_CACHE					();

	void Update					(OBD_pointer coPtr, OBJ_CACHE_UPDATE_TYPE Flag);

	void OnOpen					(OBD_pointer coPtr);
	void OnClose				(OBD_pointer coPtr);

	void OnCreate				(OBD_pointer coPtr);
	void OnDelete				(OBD_pointer coPtr);


	void CleanOut				();

	void Clear					();


	void UpdateClassStats	(identifier classID, TIMER_TYPE time, OBJ_CACHE_UPDATE_TYPE Flag);

	int  GetItemNum			();
	void DebugPrint			(string& Info);
};
//____________________________________________________________________________[]


extern  OBJ_CACHE		  *pOBJ_CACHE;
#define the_OBJ_CACHE (*pOBJ_CACHE)


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
