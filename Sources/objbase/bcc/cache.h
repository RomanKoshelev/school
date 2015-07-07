/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 2000 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            CACHE.h																	[]
[] Author:          Roman V. Koshelev														[]
[] Description:     Интерфейс к кешу частоиспользуемыхх объектов базы данных	[]
[]____________________________________________________________________________[]
*/

#ifndef	CACHE_h
#define	CACHE_h


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

	int			m_Estimation;			// Общая оценка разумности удержания объекта в кэше

	OBJ_CACHE_ITEM ();
  ~OBJ_CACHE_ITEM ();
	OBJ_CACHE_ITEM (OBJ_CACHE_ITEM& from);

	OBJ_CACHE_ITEM& operator = (OBJ_CACHE_ITEM& from);
	OBJ_CACHE_ITEM& CopyFrom	(OBJ_CACHE_ITEM& from);

	int			MakeEstimation (CAbstractObjectInMemory * aObject);
	size_t		Release ();

	static int m_TimeInCache_WEIGHT		;	// Продолжительность пребывания в памяти     
	static int m_Hits_WEIGHT				;	// Число загрузок объекта с диска                                     
	static int m_aObject_bChanged_WEIGHT;	// Объект был изменён и будет записан на диск
	static int m_aObject_nSize_WEIGHT	;	// Размер объекта в памяти                   
														                                             
	static int m_aObject_ref_WEIGHT		;	// Число ссылок на объект                    
	static int m_aObject_bDeleted_WEIGHT;	// Объект удалён                             
};
//----------------------------------------------------------------------------[] 
typedef IT_AVTree<OBJ_CACHE_ITEM, int, int OBJ_CACHE_ITEM::*> CACHE_TREE;
//____________________________________________________________________________[]


enum OBJ_CACHE_UPDATE_TYPE
{
	OCUT_ON_OPEN		= 0,
	OCUT_ON_CLOSE		= 1,
	OCUT_ON_CREATE		= 2,
	OCUT_ON_DELETE		= 3,
	OCUT_END				= 0xFFFF
};


//______________________________________________________________________________
//                                                                            []
//` OBJ_CACHE                                                                 []         
//                                                                            []
struct OBJ_CACHE
{
	bool					m_Busy;
	CACHE_TREE *		m_pCACHE;

	OBJ_CACHE			();
	~OBJ_CACHE			();

	void Update			(OBD_pointer coPtr, OBJ_CACHE_UPDATE_TYPE Flag);

	void OnOpen			(OBD_pointer coPtr);
	void OnClose		(OBD_pointer coPtr);

	void OnCreate		(OBD_pointer coPtr);
	void OnDelete		(OBD_pointer coPtr);


	void OnTimer		(time_t cur_Time);

	void Clear			();

	void DebugPrint	(string& Info);
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
