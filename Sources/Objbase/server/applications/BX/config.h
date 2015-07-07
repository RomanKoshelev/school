/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the projects 'ZOOB/BX'												[]
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          config.h																		[]
[] Date:          19.oct.2000																	[]
[] Author:        Roman V. Koshelev, Alexey S. Vershinin								[]
[] Description:   Специфические для приложения ZOOB/BX настройки					[]
[]____________________________________________________________________________[]
*/
                                                             
#ifndef BX_CONFIG_H
#define BX_CONFIG_H


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX																								[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
// Определения специфической реализации.
//#define	PROBLEM_FORME
//#define	PROBLEM_BIBIREVO
//#define	PROBLEM_DB
//#define	PROBLEM_TEST
//#define	PROBLEM_ZVUK

//----------------------------------------------------------------------------[]



/*Варианты:
	bAnonymousViewer	
	bHit					
	bSession				
	bHost					
	bNewVisitor			
	bIgnoredIP			*/
// Событие, определяющее обновление статистики по концептам. (?)
#define	STATS_UPDATE_CONDITION				bHost
// Событие, определяющее обновление статистики по пересечению аудиторий.
#define	AUDINTESECT_UPDATE_CONDITION		bHost

// Максимальное количество отсчетов, выдаемых по статистике full-time счетчиков.
#define	TS_MaxOutputSize						(HOURS_IN_DAY * DAYS_IN_WEEK)

// Максимальное количество перечисляемых за раз объектов.
#define	MAX_ENUMERATE_SIZE					1000

// Базис нормировки распределений концептов.
#define	CONCEPT_NORM_BASE						1000

// Минимальное значение распределения, при котором 
// объект считается заинтересованным в концепте.
#define	CONCEPT_INTEREST_LEVEL				2

// Макс. значение распределения концептов.
#define	MAX_CONCEPT_RATE						60000

// Частота обновления CRN_VisitorIncr.
#define	SITE_CRN_VISITOR_INCR_UPDATE		0						
#define	SITE_CRN_VISITOR_UPDATE				0
#define	REG_CRN_INETAUDIENCE_UPDATE		0
#define	VIEWER_CRN_SITE_UPDATE				0

// Максимальное время, которое может продолжаться сессия.
#define	MAX_SESSION_TIME						(15*SECS_IN_MIN)

// Максимальное количество устаревших событий, до 
// которого не происходит их удаление.
#define	MAX_OBSOLETE_SHOWEVENTS				256

// Время в секундах, за которое зритель считается online.
#define	ONLINE_TIME								(3*SECS_IN_MIN)

// Время в секундах, за которое хит считается накруткой.
#define	WOUND_TIME								oc_reg.m_MinimumHitsTime

// Максимальное кол-во страниц у одного сайта.
#define	MAX_PAGE_NUM							32

// Период с секундах обновления last-счетчиков у сайта.
#define	TIME_TO_UPDATE_SITE_COUNTERS		15

// Количество сайтов, обновляемых за один вызов BX_Site_UpdateLastCounters.
#define	SITE_NUMBER_TO_UPDATE				5

// Минимальная длина логина для успешной регистрации в системе.
#define	MIN_LOGIN_LENGTH						4

// Минимальная длина пароля для успешной регистрации в системе.
#define	MIN_PASSWORD_LENGTH					4
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
