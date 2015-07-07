/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            EventMonitor.cpp														[]
[] Date:            06/12/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Отвечает за сбор событий и рассылку их подписчикам			[]
[]____________________________________________________________________________[]
*/

#define	 USES_EventMonitor_h
#include "main.h"

int CompareFunction_EM_EventFilter (EventFilter& a, EventFilter& b)
{
	return	a.m_Module		<	b.m_Module	?	-1 :
				a.m_Module		>	b.m_Module	?	 1 :

				a.m_Type			<	b.m_Type		?	-1 :
				a.m_Type			>	b.m_Type		?	 1 :

				a.classID		<	b.classID	?	-1	:
				a.classID		>	b.classID	?	 1	:

				a.objID			<	b.objID		?	-1	:
				a.objID			>	b.objID		?	 1	:

				a.m_bAhead		<	b.m_bAhead	?	-1	:
				a.m_bAhead		>	b.m_bAhead	?	 1	:
				0;				
}



// Подписаться на событие
identifier CEventHandler::Subscribe (EMM Module, EMT EventType, identifier classID, identifier objID, bool bAhead)
{
	identifier eventID = theEventMonitor.Subscribe(this, Module, EventType, classID, objID, bAhead);
	m_EventArr.Add (eventID);
	return eventID;
}

// Подписаться на событие базы данных
identifier CEventHandler::Subscribe_ObjBase (EMT EventType, identifier classID, identifier objID, bool bAhead)
{
	identifier eventID = theEventMonitor.Subscribe(this, EMM_ObjBase, EventType, classID, objID, bAhead);
	m_EventArr.Add (eventID);
	return eventID;
}

// Подписаться на событие прикладного уровня
identifier CEventHandler::Subscribe_Application (EMT EventType, identifier classID, identifier objID, bool bAhead)
{
	identifier eventID = theEventMonitor.Subscribe(this, EMM_Application, EventType, classID, objID, bAhead);
	m_EventArr.Add (eventID);
	return eventID;
}

// Подписаться на событие уровня приложения (webserver, etc)
identifier CEventHandler::Subscribe_System (EMT EventType, identifier classID, identifier objID, bool bAhead)
{
	identifier eventID = theEventMonitor.Subscribe(this, EMM_System, EventType, classID, objID, bAhead);
	m_EventArr.Add (eventID);
	return eventID;
}

// Отказаться от подписки на событие eventID
bool CEventHandler::Unsubscribe (identifier eventID)
{
	int index = m_EventArr.Find (eventID);
	if (index>=0)
	{
		theEventMonitor.Unsubscribe(this, eventID);
		m_EventArr.Remove(index);
		return true;
	}
	else
	{
		SERVER_DEBUG_ERROR ("CEventHandler::Unsubscribe -- попытка отписаться от события, на которое не подписан");
		return false;
	}
	return true;
}

// Отказаться от подписки на все события
bool CEventHandler::UnsubscribeAll ()
{
	while (m_EventArr.Size()>0)
	{
		if (! Unsubscribe (m_EventArr[0]))
		return false;
	}
	return true;
}









bool CEventMonitor::RaiseEvent (EM_Event& Event)
{
	SERVER_DEBUG_ASSERT_RETURN ((Event.m_Module>EMM_FIRST) && (Event.m_Module<EMM_LAST), "CEventMonitor::Subscribe: Некорректное значение модуля-генератора событий", true);
	SERVER_DEBUG_ASSERT_RETURN ((Event.m_Type>EMT_FIRST) && (Event.m_Type<EMT_LAST), "CEventMonitor::Subscribe: Некорректный типа события", true);
	SERVER_DEBUG_ASSERT_RETURN (Event.m_Module!=EMM_ALL_MODULES, "CEventMonitor::Subscribe: Некорректное значение модуля-генератора событий", true);
	SERVER_DEBUG_ASSERT_RETURN (Event.m_Type!=EMT_ALL_TYPES, "CEventMonitor::Subscribe: Некорректный типа события", true);

	EventFilter			ef;
	bool bResult	=	true;
	bool bRetVal	=	true;
	ef.m_bAhead		=	Event.m_bAhead;

// 0 0 0 0
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	Event.classID;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	
// 1 0 0 0
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	Event.classID;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 0 1 0 0
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	Event.classID;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 1 1 0 0
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	Event.classID;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

	if (Event.classID != UNKNOWN)
	{
// 0 0 1 0
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	UNKNOWN;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 1 0 1 0
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	UNKNOWN;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	
// 0 1 1 0
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	UNKNOWN;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 1 1 1 0
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	UNKNOWN;
	ef.objID			=	Event.objID;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	}

	if (Event.objID != UNKNOWN)
	{
// 0 0 0 1
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	Event.classID;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	
// 1 0 0 1
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	Event.classID;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 0 1 0 1
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	Event.classID;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 1 1 0 1
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	Event.classID;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

	if (Event.classID != UNKNOWN)
	{
// 0 0 1 1
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	UNKNOWN;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	
// 1 0 1 1
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	Event.m_Type;
	ef.classID		=	UNKNOWN;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 0 1 1 1
	ef.m_Module		=	Event.m_Module;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	UNKNOWN;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;

// 1 1 1 1
	ef.m_Module		=	EMM_ALL_MODULES;
	ef.m_Type		=	EMT_ALL_TYPES;
	ef.classID		=	UNKNOWN;
	ef.objID			=	UNKNOWN;
	bResult			= _RaiseEvent (ef, Event);	if (bResult==false)	bRetVal = false;
	}
	}

	return bRetVal;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

