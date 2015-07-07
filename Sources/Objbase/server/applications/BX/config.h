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
[] Description:   ������������� ��� ���������� ZOOB/BX ���������					[]
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
// ����������� ������������� ����������.
//#define	PROBLEM_FORME
//#define	PROBLEM_BIBIREVO
//#define	PROBLEM_DB
//#define	PROBLEM_TEST
//#define	PROBLEM_ZVUK

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
#define	TS_MaxOutputSize						(HOURS_IN_DAY * DAYS_IN_WEEK)

// ������������ ���������� ������������� �� ��� ��������.
#define	MAX_ENUMERATE_SIZE					1000

// ����� ���������� ������������� ���������.
#define	CONCEPT_NORM_BASE						1000

// ����������� �������� �������������, ��� ������� 
// ������ ��������� ���������������� � ��������.
#define	CONCEPT_INTEREST_LEVEL				2

// ����. �������� ������������� ���������.
#define	MAX_CONCEPT_RATE						60000

// ������� ���������� CRN_VisitorIncr.
#define	SITE_CRN_VISITOR_INCR_UPDATE		0						
#define	SITE_CRN_VISITOR_UPDATE				0
#define	REG_CRN_INETAUDIENCE_UPDATE		0
#define	VIEWER_CRN_SITE_UPDATE				0

// ������������ �����, ������� ����� ������������ ������.
#define	MAX_SESSION_TIME						(15*SECS_IN_MIN)

// ������������ ���������� ���������� �������, �� 
// �������� �� ���������� �� ��������.
#define	MAX_OBSOLETE_SHOWEVENTS				256

// ����� � ��������, �� ������� ������� ��������� online.
#define	ONLINE_TIME								(3*SECS_IN_MIN)

// ����� � ��������, �� ������� ��� ��������� ���������.
#define	WOUND_TIME								oc_reg.m_MinimumHitsTime

// ������������ ���-�� ������� � ������ �����.
#define	MAX_PAGE_NUM							32

// ������ � �������� ���������� last-��������� � �����.
#define	TIME_TO_UPDATE_SITE_COUNTERS		15

// ���������� ������, ����������� �� ���� ����� BX_Site_UpdateLastCounters.
#define	SITE_NUMBER_TO_UPDATE				5

// ����������� ����� ������ ��� �������� ����������� � �������.
#define	MIN_LOGIN_LENGTH						4

// ����������� ����� ������ ��� �������� ����������� � �������.
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
