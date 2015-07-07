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
[] Description:     ������������ ��������.												[]
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


// ������������ ����� ������ ��� HTTP_URL � HTTP_USER_AGENT
#define	MAX_URL_SIZE			1024



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SERVER                                                                    []      
[]                                                                            []
[]____________________________________________________________________________*/

// ������ ������ ��� �������� ���������� ����� ���������� � ��������� �������.
#define	OUT_STREAM_BUFFER_SIZE	1024*1024

// ������ ������ ��� �������� ��������� ���������� �������.
#define	MAX_ARG_VALUE_LENGTH		1024*256

// ������ ������ ��� ����� ��������� ���������� �������.
#define	MAX_ARG_NAME_LENGTH		64

// ������ ������ �������� ���������.
#define	FIELD_HEADER_STR			"\x1"
#define	FIELD_HEADER_CHAR			1

// ������ ������ ����� ���������.
#define	ARG_NAME_HEADER_STR		"\x2"
#define	ARG_NAME_HEADER_CHAR		2

// ����������� ��������������/�������/�������� ������ �������.
#define	QUERYBLOCK_SEP_STR		"\x3"
#define	QUERYBLOCK_SEP_CHAR		3

// ������������� �������.
#define	HELPER_DISABLED


// ��������� ������ � ��������:
#define	OBS_LISTEN_PORT			1502				// ����, �������������� ��������.
#define	OBS_ACCEPT_TIMEOUT		0					// ������� �� �������� ��������� ���������� � ������� � �������������.
#define	OBS_READ_TIMEOUT			500000			// ������� �� �������� ���������� ������� ������� ������ � �������������.
#define	OBS_WRITE_TIMEOUT			500000			// ������� �� �������� ���������� ������� ������� ����� � �������������.
#define	OBS_MAX_BACKLOG_NUM		128				// ������ �������� �������.
																
// ��������� ���������������� �������:				
#define	OBS_SLEEP_TIME					10000			// ����������������� ��� ��� ���������� �������� � �������������.
#define	OBS_TIMER_INTERVAL			10				// ����������� ����� � ��������, ����� ������� ���������� ���������� OBServer_OnTimer().
#define	OBS_MAX_DATABLOCK_SIZE		(1024*1024)	// ������������ ������ ����� ������, ����������� ��������.

// ��� ����� ���� ������� ���������� OBServer_Interface().
#define	TimelogFileName				"./../../../public_html/BX/logs/time_log.html"	

// ��� lock-����� �������.
#define	LockFileName					"db.lock"													

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` PROBLEM                                                                   []       
[]                                                                            []
[]____________________________________________________________________________*/


// ����������� ������������� ����������.
//#define	PROBLEM_FORME
//#define	PROBLEM_BIBIREVO
//#define	PROBLEM_DB

//----------------------------------------------------------------------------[]



/*��������:
	bAnonymousViewer	
	bHit					
	bSession				
	bHost					
	bNewVisitor			
	bIgnoredIP			*/
// �������, ������������ ���������� ���������� �� ���������. (?)
#define	STATS_UPDATE_CONDITION				bHost
// �������, ������������ ���������� ���������� �� ����������� ���������.
#define	AUDINTESECT_UPDATE_CONDITION		bHost

// ������������ ���������� ��������, �������� �� ���������� full-time ���������.
#define	TS_MaxOutputSize				(HOURS_IN_DAY * DAYS_IN_WEEK)

// ������������ ���������� ������������� �� ��� ��������.
#define	MAX_ENUMERATE_SIZE				1000

// ����� ���������� ������������ ���������.
#define	CONCEPT_NORM_BASE					1000

// ������� ���������� CRN_VisitorIncr.
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