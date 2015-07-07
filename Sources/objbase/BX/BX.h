/*
________________________________________________________________________________
[] 																								   []
[] This is a part of the PROJECT: 'BX'													   []
[] ___________________________________________________________________________[]
[]																										[]
[] Name: 			  BX.h																		[]
[] Date: 			  01.06.99																	[]
[] Author:			  Alex Vershinin															[]
[] Description:	  Структуры параметров и прототипы функций наполнения базы	[]
[] Last Modified:																					[]
[]____________________________________________________________________________[]
*/
#ifndef	BX_H
#define	BX_H



#define	READONLY

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
#define	SECS_IN_MIN						60
#define	SECS_IN_HOUR					(60 * 60)
#define	SECS_IN_DAY						(60 * 60 * 24)
#define	SECS_IN_WEEK					(60 * 60 * 24 * 7)
#define	SECS_IN_TWO_WEEKS				(60 * 60 * 24 * 14)
#define	SECS_IN_MONTH					(60 * 60 * 24 * 30)
#define	HOURS_IN_WEEK					(24 * 7)
#define	HOURS_IN_DAY					24
#define	MINS_IN_HOUR					60
#define	MINS_IN_DAY						(24 * 60)
#define	DAYS_IN_WEEK					7
#define	MONTHS_IN_YEAR					12
#define	DAYS_IN_YEAR					365
#define	DAYS_IN_MONTH					30
#define	MAX_EVENT_STORAGE_TIME		(3*SECS_IN_MIN)		// Используется для определения количества посетителей online.


extern long SERVER_TIME_ZONE_OFFSET;


//----------------------------------------------------------------------------[] 

#ifdef USES_BX_SingleObject
#define	USES_EventMonitor_h
#define	USES_OC_Registry
#define	USES_OC_User
#define	USES_OC_Banner
#define	USES_OC_BannerProfile
#define	USES_OC_Site
#define	USES_OC_SiteProfile
#define	USES_OC_Concept
#define	USES_OC_Language
#define	USES_OC_VBN
#define	USES_OC_TimeStats
#define	USES_OC_YearStats
#define	USES_OC_DayStats
#endif

#ifdef USES_BX_Viewer
#define USES_OC_Viewer
#endif

//----------------------------------------------------------------------------[] 
#include "Lay_ObjController.h"
//----------------------------------------------------------------------------[] 

#ifdef USES_BX_SingleObject
#include "BX_SingleObject.h"
#endif

#ifdef USES_BX_Errors
#include "BX_Errors.h"
#endif

#ifdef USES_BX_Language
#include "BX_Language.h"
#endif

#ifdef USES_BX_Concept
#include "BX_Concept.h"
#endif

#ifdef USES_BX_Site
#include "BX_Site.h"
#endif

#ifdef USES_BX_SiteProfile
#include "BX_SiteProfile.h"
#endif

#ifdef USES_BX_Banner
#include "BX_Banner.h"
#endif

#ifdef USES_BX_BannerProfile
#include "BX_BannerProfile.h"
#endif

#ifdef USES_BX_VBN
#include "BX_VBN.h"
#endif

#ifdef USES_BX_User
#include "BX_User.h"
#endif

#ifdef USES_BX_Counter
#define USES_BX_Events
#endif

#ifdef USES_BX_Events
#include "BX_Events.h"
#endif

#ifdef USES_BX_Counter
#include "BX_Counter.h"
#endif

#ifdef USES_BX_IPRecord
#include "BX_IPRecord.h"
#endif

#ifdef USES_BX_Viewer
#include "BX_Viewer.h"
#endif

#ifdef USES_BX_Keyword
#include "BX_Keyword.h"
#endif

#ifdef USES_BX_TimeStats
#include "BX_TimeStats.h"
#endif

#ifdef USES_BX_Date
#include "BX_Date.h"
#endif

#ifdef USES_BX_Graph
#include "BX_Graph.h"
#endif

#ifdef USES_BX_Macros
#include "BX_Utils.h"
#include "BX_Macros.h"
#endif

#ifdef USES_BX_Utils
#include "BX_Utils.h"
#endif

#ifdef USES_BX_Stats
#include "BX_Stats.h"
#endif

#ifdef USES_BX_Rating
#include "BX_Rating.h"
#endif

#ifdef USES_BX_Admin
#include "BX_Admin.h"
#endif

#ifdef USES_BX_Interface
#include "Interface_Auto.h"
#endif
//____________________________________________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []
[]                                                                            []
[]____________________________________________________________________________[]
*/