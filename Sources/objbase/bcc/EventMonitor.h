/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            EventMonitor.h															[]
[] Date:            06/12/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     �������� �� ���� ������� � �������� �� �����������			[]
[]____________________________________________________________________________[]
*/
#ifndef EventMonitor_H
#define EventMonitor_H




class CEventHandler;
//______________________________________________________________________________
//                                                                            []
//` ������, ������������ �������																[]
//                                                                            []
typedef enum EVENT_MODULE
{
EMM_FIRST,
	
	EMM_FileDriver,	// �������� �������
	EMM_Compiler,		// ���������� ���� ������

	EMM_ObjBase,		// ���� ������
	EMM_Application,	// ���������� �������, ������������ ���� ������
	EMM_System,			// ������� �������  -- webserver, etc.

	EMM_ALL_MODULES,				// ��� ������

EMM_LAST
}
EMM;
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` ���� �������																					[]
//                                                                            []
typedef enum EVENT_TYPE
{
EMT_FIRST,

	EMT_Error,					// ������

	EMT_Object_New,			// �������� ������ �������				+
	EMT_Object_Delete,		// �������� �������						+
	EMT_Object_Change,		// ��������� �������						+- (����������������)
	EMT_Object_Open,			// �������� �������						+

	EMT_Start,					// ������ ������ ������
	EMT_ShutDown,				// ���������� ������ ������
	EMT_Save,					// ���������� ��������� ������
	
	EMT_Message,				// ��������� �� ������

	EMT_ALL_TYPES,				// ��� ���� �������

EMT_LAST
}EMT;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ������ �������																				[]
//                                                                            []
struct EventFilter
{
	EVENT_MODULE	m_Module;		// ������, ������������ ������� 
	EVENT_TYPE		m_Type;			// ��� �������
	identifier		classID;			// ������ ��������-������������� (����. classID)
	identifier		objID;			// ������ ��������-������������� (����. objID)
	bool				m_bAhead;		// ������� ��������� ���������
};
//______________________________________________________________________________
//                                                                            []
//` ������ � ����������																			[]
//                                                                            []
struct RegestryRecord
{
	EventFilter		m_EventFilter;
	CEventHandler*	m_pHandler;

	RegestryRecord& operator = (const RegestryRecord& from)
	{
		m_EventFilter	= from.m_EventFilter;
		m_pHandler		= from.m_pHandler;
		return			 *this;
	}
};
//____________________________________________________________________________[]


int CompareFunction_EM_EventFilter (EventFilter& a, EventFilter& b);

//______________________________________________________________________________
//                                                                            []
//` �������																							[]
//                                                                            []
struct EM_Event
{
	EVENT_MODULE	m_Module;			// ������, ������������ ������� 
	EVENT_TYPE		m_Type;				// ��� �������
	identifier		classID;				// ������ ��������-������������� (����. classID)
	identifier		objID;				// ������ ��������-������������� (����. objID)
	bool				m_bAhead;			// ������� ��������� ���������

	string			m_Description;		// �������� �������
	void	*			m_pData;				// ��������� �� ������ ������, ����������� �������

	string			m_SRC_FileName;	// ��� �����, � ������� ��������� �������
	int				m_SRC_Line;			// ������ � �����, � ������� ������� �������

	EM_Event()
	{
		m_Module			= EMM_FIRST;
		m_Type			= EMT_FIRST;
		classID			= UNKNOWN;
		objID				= UNKNOWN;
		m_bAhead			= false;

		m_Description	= "";
		m_pData			= NULL;
	}
};
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` ������� ����� ����������� �������														[]
//                                                                            []
class CEventHandler
{
// ������� ����� ��� ��������, �������������� �������
	public: void About_CEventHandler(){}

// ��� �������-����������� �������
	string		m_Name;

// ������ ��������������� �������������� �������
	protected:	CPtr<identifier> m_EventArr;
	public:		CEventHandler(){m_Name="noname";}

// ����������� �� �������
	public: identifier Subscribe (EMM Module=EMM_ALL_MODULES, EMT EventType=EMT_ALL_TYPES, identifier classID=NA, identifier objID=NA, bool bAhead=false);

// ����������� �� ������� ���� ������
	public: identifier Subscribe_ObjBase (EMT EventType=EMT_ALL_TYPES, identifier classID=NA, identifier objID=NA, bool bAhead=false);

// ����������� �� ������� ����������� ������
	public: identifier Subscribe_Application (EMT EventType=EMT_ALL_TYPES, identifier classID=NA, identifier objID=NA, bool bAhead=false);

// ����������� �� ������� ������ ���������� (webserver, etc)
	public: identifier Subscribe_System (EMT EventType=EMT_ALL_TYPES, identifier classID=NA, identifier objID=NA, bool bAhead=false);

// ���������� �� �������� �� ������� eventID
	public: bool Unsubscribe (identifier eventID);

// ���������� �������.
//	���� ������ �������� �� ��������� ����������� � _�����������_ 
// �������, �� �� ����� ������� false ����� ������������� ���.
	public: virtual bool OnEvent (const EM_Event&)
	{
		SERVER_DEBUG_ERROR_1 ("CEventHandler::OnEvent(): � ������ '%s' �� ������ ���������� �������", m_Name.c_str());
		return true;
	}

// ���������� �� �������� �� ��� �������
	bool UnsubscribeAll ();

	public: ~CEventHandler()
	{
		UnsubscribeAll ();
	}
};
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` �������� �� ���������																		[]
[]                                                                            []
[]____________________________________________________________________________[]
*/




//______________________________________________________________________________
//                                                                            []
//` CEventMonitor																					[]
//                                                                            []
typedef class CEventMonitor
{
	typedef IT_AVTree <RegestryRecord, EventFilter, EventFilter RegestryRecord::*> IT_AVTree_RegestryRecord;

	public: IT_AVTree_RegestryRecord m_Tree;

	public: CEventMonitor () :m_Tree (&RegestryRecord::m_EventFilter, CompareFunction_EM_EventFilter)
	{
		SERVER_DEBUG_TEXT ("������� ������� ��������� � ������");
	}
	public: ~CEventMonitor ()
	{
		SERVER_DEBUG_TEXT ("������� ������� �������� ������");
	}

	public: identifier Subscribe (CEventHandler * pHandler, EMM Module, EMT Type, identifier classID=NA, identifier objID=NA, bool bAhead=false)
	{
		SERVER_DEBUG_ASSERT_RETURN ((Module>EMM_FIRST) && (Module<EMM_LAST), "CEventMonitor::Subscribe: ������������ �������� ������-���������� �������", NA);
		SERVER_DEBUG_ASSERT_RETURN ((Type>EMT_FIRST) && (Type<EMT_LAST), "CEventMonitor::Subscribe: ������������ ���� �������", NA);

		RegestryRecord  record;
		record.m_EventFilter.m_Module		= Module;
		record.m_EventFilter.m_Type		= Type;
		record.m_EventFilter.classID		= classID;
		record.m_EventFilter.objID			= objID;
		record.m_EventFilter.m_bAhead		= bAhead;
		record.m_pHandler						= pHandler;

		identifier eventID = (identifier) m_Tree.Insert (record);
		return eventID;
	}

	public: void Unsubscribe (CEventHandler * pHandler, identifier eventID)
	{
		RegestryRecord * pRecord = m_Tree.ItemPointer ((void*)eventID);
		SERVER_DEBUG_ASSERT (pRecord!=NULL, "CEventMonitor::Unsubscribe -- �� ������� ������ � ��������");
		SERVER_DEBUG_ASSERT (pRecord->m_pHandler==pHandler, "CEventMonitor::Unsubscribe -- ������� �������� ����� ��������");
		m_Tree.Remove ((void*)eventID);
	}

	protected: bool _RaiseEvent (EventFilter& ef, EM_Event& Event)
	{
		bool bResult = true;
		for (void * eventID = m_Tree.Find (ef); eventID!=NULL; eventID = m_Tree.NextWithSameKey(eventID))
		{
			RegestryRecord * pRecord = m_Tree.ItemPointer ((void*)eventID);
			if (pRecord->m_pHandler->OnEvent (Event) == false)
			{
				if (Event.m_bAhead && pRecord->m_EventFilter.m_bAhead)
				{
					bResult = false;
				}
				else
				{
					if (!Event.m_bAhead)
						SERVER_DEBUG_ERROR_3 ("������ '%s', �� ����� ����� �������� ������� [%d:%d] -- ������ ������� ��� ���������", pRecord->m_pHandler->m_Name.c_str(), pRecord->m_EventFilter.m_Module, pRecord->m_EventFilter.m_Type);
					if (!pRecord->m_EventFilter.m_bAhead)
						SERVER_DEBUG_ERROR_3 ("������ '%s', �� ����� ����� �������� ������� [%d:%d] -- �� ������� ��������", pRecord->m_pHandler->m_Name.c_str(), pRecord->m_EventFilter.m_Module, pRecord->m_EventFilter.m_Type);
				}
			}
		}
		return bResult;
	}

	public: bool RaiseEvent (EM_Event& Event);

	public: bool RaiseEvent (
				  EMM Module, 
				  EMT Type, 
				  identifier classID=UNKNOWN, 
				  identifier objID=UNKNOWN, 
				  bool bAhead=false, 
				  const char* Description="", 
				  void * pData=NULL, 
				  const char * SRC_FileName="", 
				  int SRC_Line=0)
	{
		EM_Event Event;
		Event.m_Module			= Module;
		Event.m_Type			= Type;
		Event.classID			= classID;
		Event.objID				= objID;
		Event.m_bAhead			= bAhead;
		Event.m_Description	= Description;
		Event.m_pData			= pData;
		Event.m_SRC_FileName	= SRC_FileName;
		Event.m_SRC_Line		= SRC_Line;

		return RaiseEvent (Event);
	}
}CEM;
extern CEventMonitor theEventMonitor;
//____________________________________________________________________________[]



//________________________________________________
//																[]
//` ���������� �������									[]
//																[]
#define RAISE_EVENT(M,T,C,O,D)						\
	theEventMonitor.RaiseEvent(						\
		M, 													\
		T,														\
		C,														\
		O,														\
		false,												\
		D,														\
		NULL,													\
		__FILE__,											\
		__LINE__)
//______________________________________________[]


#define OBJ_CLASS_ID_NA			NA
#define OBJ_CLASS_ID_UNKNOWN	UNKNOWN

//________________________________________________
//																[]
//` ���������� ����������� �������					[]
//																[]
#define RAISE_EVENT_AHEAD(M,T,C,O,D)				\
	theEventMonitor.RaiseEvent(						\
		M, 													\
		T,														\
		C,														\
		O,														\
		true,													\
		D,														\
		NULL,													\
		__FILE__,											\
		__LINE__)
//______________________________________________[]






//________________________________________________
//																[]
//` ����� ��� ������� ���� ������					[]
//																[]
#define	RAISE_EVENT_OBJBASE(T,C,O)					\
			RAISE_EVENT(EMM_ObjBase,T,C,O,"")
//----------------------------------------------[]
#define	RAISE_EVENT_AHEAD_OBJBASE(T,C,O) 		\
			RAISE_EVENT_AHEAD(EMM_ObjBase,T,C,O,"")
//----------------------------------------------[]
#define	RAISE_EVENT_OBJBASE_ARG(T,C,O,D,A)		\
	{															\
			static char DESRC [1024];					\
			sprintf (DESRC, D, A);						\
			RAISE_EVENT(EMM_ObjBase,T,C,O,D);		\
	}
//----------------------------------------------[]
inline bool RAISE_EVENT_AHEAD_OBJBASE_ARG(
				  EMT			  T, 
				  identifier  C,
				  identifier  O,
				  const char* D,
				  const char* A)
	{
		static char DESCR [1024];
		sprintf (DESCR, D, A);
		return theEventMonitor.RaiseEvent(EMM_ObjBase,T,C,O,true,DESCR);
	}
//______________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
