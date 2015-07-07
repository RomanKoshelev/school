/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the projects 'bcc', 'BX'                                 []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            config.h                                                  []
[] Date:            01.04.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Конфигурация проектов.												[]
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                             
#ifndef config_h
#define config_h
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBJBASE                                                                   []       
[]                                                                            []
[]____________________________________________________________________________*/


// Максимальная длина адреса для HTTP_URL и HTTP_USER_AGENT
#define	MAX_URL_SIZE			1024



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SERVER                                                                    []      
[]                                                                            []
[]____________________________________________________________________________*/

// Размер буфера для передачи аргументов между проблемной и серверной частями.
#define	OUT_STREAM_BUFFER_SIZE	1024*1024

// Размер буфера для значения аргумента проблемной функции.
#define	MAX_ARG_VALUE_LENGTH		1024*256

// Размер буфера для имени аргумента проблемной функции.
#define	MAX_ARG_NAME_LENGTH		64

// Маркер начала значения аргумента.
#define	FIELD_HEADER_STR			"\x1"
#define	FIELD_HEADER_CHAR			1

// Маркер начала имени аргумента.
#define	ARG_NAME_HEADER_STR		"\x2"
#define	ARG_NAME_HEADER_CHAR		2

// Разделитель функциональной/входной/выходной частей запроса.
#define	QUERYBLOCK_SEP_STR		"\x3"
#define	QUERYBLOCK_SEP_CHAR		3

// Использование хелпера.
#define	HELPER_DISABLED


// Параметры работы с сокетами:
#define	OBS_LISTEN_PORT			1502				// Порт, прослушиваемый сервером.
#define	OBS_ACCEPT_TIMEOUT		0					// Таймаут на ожидание появления соединений в очереди в микросекундах.
#define	OBS_READ_TIMEOUT			500000			// Таймаут на ожидание готовности клиента послать запрос в микросекундах.
#define	OBS_WRITE_TIMEOUT			500000			// Таймаут на ожидание готовности клиента принять ответ в микросекундах.
#define	OBS_MAX_BACKLOG_NUM		128				// Размер сокетной очереди.
																
// Параметры функционирования сервера:				
#define	OBS_SLEEP_TIME					10000			// Продолжительность сна при отсутствии запросов в микросекундах.
#define	OBS_TIMER_INTERVAL			10				// Минимальное время в секундах, через которое вызывается обработчик OBServer_OnTimer().
#define	OBS_MAX_DATABLOCK_SIZE		(1024*1024)	// Максимальный размер блока данных, принимаемый сервером.

// Имя файла лога времени выполнения OBServer_Interface().
#define	TimelogFileName				"./../../../public_html/BX/logs/time_log.html"	

// Имя lock-файла сервера.
#define	LockFileName					"db.lock"													

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` PROBLEM                                                                   []       
[]                                                                            []
[]____________________________________________________________________________*/


// Определения специфической реализации.
//#define	PROBLEM_FORME
//#define	PROBLEM_BIBIREVO
//#define	PROBLEM_DB

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
#define	TS_MaxOutputSize				(HOURS_IN_DAY * DAYS_IN_WEEK)

// Максимальное количество перечисляемых за раз объектов.
#define	MAX_ENUMERATE_SIZE				1000

// Базис нормировки распредлений концептов.
#define	CONCEPT_NORM_BASE					1000

// Частота обновления CRN_VisitorIncr.
#define	SITE_CRN_VISITOR_INCR_UPDATE	0						
#define	SITE_CRN_VISITOR_UPDATE			0
#define	REG_CRN_INETAUDIENCE_UPDATE	0
#define	VIEWER_CRN_SITE_UPDATE			0






#endif   // end of config_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/