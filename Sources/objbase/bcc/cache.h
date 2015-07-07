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
[] Description:     ��������� � ���� ������������������ �������� ���� ������	[]
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
	OBD_pointer coPtr;					// ��������� �� ������-������

	int			m_Hits;					// ����� �������� �������-������ �� ����� ��� �����������
	time_t		m_FirstAccessTime;	// ����� ������� ��������� � �������-������
	time_t		m_LastAccessTime;		// ����� ���������� ��������� � �������-������

	int			m_Estimation;			// ����� ������ ���������� ��������� ������� � ����

	OBJ_CACHE_ITEM ();
  ~OBJ_CACHE_ITEM ();
	OBJ_CACHE_ITEM (OBJ_CACHE_ITEM& from);

	OBJ_CACHE_ITEM& operator = (OBJ_CACHE_ITEM& from);
	OBJ_CACHE_ITEM& CopyFrom	(OBJ_CACHE_ITEM& from);

	int			MakeEstimation (CAbstractObjectInMemory * aObject);
	size_t		Release ();

	static int m_TimeInCache_WEIGHT		;	// ����������������� ���������� � ������     
	static int m_Hits_WEIGHT				;	// ����� �������� ������� � �����                                     
	static int m_aObject_bChanged_WEIGHT;	// ������ ��� ������ � ����� ������� �� ����
	static int m_aObject_nSize_WEIGHT	;	// ������ ������� � ������                   
														                                             
	static int m_aObject_ref_WEIGHT		;	// ����� ������ �� ������                    
	static int m_aObject_bDeleted_WEIGHT;	// ������ �����                             
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
