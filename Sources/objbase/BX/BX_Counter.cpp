/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Counter.cpp                                            []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Работа со счётчиком                                       []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                   


#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Events
#define USES_BX_Counter
#define USES_BX_Macros
#define USES_BX_TimeStats
#define USES_BX_Viewer
#define USES_BX_IPRecord
#define USES_BX_Concept

//#define USES_OBServer_Interface_h
#define USES_URL_h

#define USES_OC_Viewer
#define USES_OC_Site
#define USES_OC_Site
#define USES_OC_SuspiciousInfo
#define USES_OC_ShowEvent
#define USES_OC_Referrer
#define USES_OC_DailyReferrerStats

#include "BX.h"


#define MAX_SESSION_TIME			15*SECS_IN_MIN
#define MAX_REFERRER_LENGTH		512



//______________________________________________________________________________
//                                                                            []
//` CheckMirrors                                                              []            
//                                                                            []
bool
CheckMirrors(const OC_Site& oc_site, const BX_Counter_Args& arg)
{
	int			i;
	bool			bMirrorOkay = false;
	HTTP_URL		refURL = arg.SiteURL.c_str();
	HTTP_URL		mirURL = (string(oc_site.m_URL)).c_str();
	// проверим головной сайт:
	if ((arg.SiteURL.Len() == 0) || refURL.IsChildFor(mirURL))	{ 
		bMirrorOkay = true;
	}
	else	{
	// Проверим разрешенные зеркала...
		for (i = 0; i < oc_site.m_MirrorInclude.Size(); i++)	{
			mirURL = (string(oc_site.m_MirrorInclude[i])).c_str();
			if (refURL.IsChildFor(mirURL)) {
				bMirrorOkay = true;
				break;
			}
		}
	}
	
	if (bMirrorOkay)	{
	// Проверим запрещенные зеркала...
		for (i = 0; i < oc_site.m_MirrorExclude.Size(); i++)	{
			mirURL = (string(oc_site.m_MirrorExclude[i])).c_str();
			if (refURL.IsChildFor(mirURL)) {
				bMirrorOkay = false;
				break;
			}
		}
	}

	return  bMirrorOkay;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` FillCounterFields                                                         []                 
//                                                                            []
void	FillCounterFields(const OC_Site& oc_site, BX_Counter_Args& arg)
{
//----------------------------------------------------------------------------[] 
// Вернём статистику для счётчика:

	arg.Total_Loads						= (int)oc_site.m_Total_Loads						;						
	arg.Total_Visitors					= (int)oc_site.m_Total_Visitors					;
	arg.Total_VisitorReturns			= (int)oc_site.m_Total_VisitorReturns			;
	arg.Total_AnonymousVisitors		= (int)oc_site.m_Total_AnonymousVisitors		;
	arg.Total_AnonymousVisitors_Prc	= (int)oc_site.m_Total_AnonymousVisitors_Prc	;
	arg.Total_VisitorExperience		= (int)oc_site.m_Total_VisitorExperience		;
	arg.Ave_VisitorExperience			= (int)oc_site.m_Ave_VisitorExperience			;
	arg.Total_Hosts						= (int)oc_site.m_Total_Hosts						;
	arg.Total_Hits							= (int)oc_site.m_Total_Hits						;
	arg.OnlineVisitors					= (int)oc_site.m_OnlineVisitors					;
	arg.Total_AnonymousHits				= (int)oc_site.m_Total_AnonymousHits			;
	arg.Total_AnonymousHits_Prc		= (int)oc_site.m_Total_AnonymousHits_Prc		;
	arg.Total_SuspiciousHits_Prc		= (int)oc_site.m_Total_SuspiciousHits_Prc		;
	arg.Total_Shows						= (int)oc_site.m_Total_Shows						;
	arg.Total_Clicks						= (int)oc_site.m_Total_Clicks						;
	arg.Total_MouseOver					= (int)oc_site.m_Total_MouseOver					;
	arg.Total_CTR_Prc						= (int)oc_site.m_Total_CTR_Prc					;
	arg.Total_Votes						= (int)oc_site.m_Total_Votes						;
	arg.Total_Votes_Sum					= (int)oc_site.m_Total_Votes_Sum					;
	arg.Total_Votes_Ave					= (int)oc_site.m_Total_Votes_Ave					;
	arg.LM_Loads							= (int)oc_site.m_LM_Loads							;						
	arg.LM_Visitors						= (int)oc_site.m_LM_Visitors						;
	arg.LM_VisitorReturns				= (int)oc_site.m_LM_VisitorReturns				;
	arg.LM_VisitorReturns_Prc			= (int)oc_site.m_LM_VisitorReturns_Prc			;
	arg.LM_Hosts							= (int)oc_site.m_LM_Hosts							;
	arg.LM_Hits								= (int)oc_site.m_LM_Hits							;
	arg.LM_AnonymousHits					= (int)oc_site.m_LM_AnonymousHits				;
	arg.LM_AnonymousHits_Prc			= (int)oc_site.m_LM_AnonymousHits_Prc			;
	arg.LM_SuspiciousHits_Prc			= (int)oc_site.m_LM_SuspiciousHits_Prc			;
	arg.LM_Shows							= (int)oc_site.m_LM_Shows							;
	arg.LM_Clicks							= (int)oc_site.m_LM_Clicks							;
	arg.LM_CTR_Prc							= (int)oc_site.m_LM_CTR_Prc						;
	arg.LW_Loads							= (int)oc_site.m_LW_Loads							;						
	arg.LW_Visitors						= (int)oc_site.m_LW_Visitors						;
	arg.LW_VisitorReturns				= (int)oc_site.m_LW_VisitorReturns				;
	arg.LW_VisitorReturns_Prc			= (int)oc_site.m_LW_VisitorReturns_Prc			;
	arg.LW_Hosts							= (int)oc_site.m_LW_Hosts							;
	arg.LW_Hits								= (int)oc_site.m_LW_Hits							;
	arg.LW_AnonymousHits					= (int)oc_site.m_LW_AnonymousHits				;
	arg.LW_AnonymousHits_Prc			= (int)oc_site.m_LW_AnonymousHits_Prc			;
	arg.LW_SuspiciousHits_Prc			= (int)oc_site.m_LW_SuspiciousHits_Prc			;
	arg.LW_Shows							= (int)oc_site.m_LW_Shows							;
	arg.LW_Clicks							= (int)oc_site.m_LW_Clicks							;
	arg.LW_CTR_Prc							= (int)oc_site.m_LW_CTR_Prc						;
	arg.LD_Loads							= (int)oc_site.m_LD_Loads							;						
	arg.LD_Visitors						= (int)oc_site.m_LD_Visitors						;
	arg.LD_VisitorReturns				= (int)oc_site.m_LD_VisitorReturns				;
	arg.LD_VisitorReturns_Prc			= (int)oc_site.m_LD_VisitorReturns_Prc			;
	arg.LD_Hosts							= (int)oc_site.m_LD_Hosts							;
	arg.LD_Hits								= (int)oc_site.m_LD_Hits							;
	arg.LD_AnonymousHits					= (int)oc_site.m_LD_AnonymousHits				;
	arg.LD_AnonymousHits_Prc			= (int)oc_site.m_LD_AnonymousHits_Prc			;
	arg.LD_SuspiciousHits_Prc			= (int)oc_site.m_LD_SuspiciousHits_Prc			;
	arg.LD_Shows							= (int)oc_site.m_LD_Shows							;
	arg.LD_Clicks							= (int)oc_site.m_LD_Clicks							;
	arg.LH_Loads							= (int)oc_site.m_LH_Loads							;						
	arg.LH_Visitors						= (int)oc_site.m_LH_Visitors						;
	arg.LH_VisitorReturns				= (int)oc_site.m_LH_VisitorReturns				;
	arg.LH_VisitorReturns_Prc			= (int)oc_site.m_LH_VisitorReturns_Prc			;
	arg.LH_Hosts							= (int)oc_site.m_LH_Hosts							;
	arg.LH_Hits								= (int)oc_site.m_LH_Hits							;
	arg.LH_AnonymousHits					= (int)oc_site.m_LH_AnonymousHits				;
	arg.LH_AnonymousHits_Prc			= (int)oc_site.m_LH_AnonymousHits_Prc			;
	arg.LH_SuspiciousHits_Prc			= (int)oc_site.m_LH_SuspiciousHits_Prc			;
	arg.LH_Shows							= (int)oc_site.m_LH_Shows							;
	arg.LH_Clicks							= (int)oc_site.m_LH_Clicks							;


	return;
}
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[]
// Инициализация статистики по реферерам:
BX_RESULT BX_Site_InitDailyReferrerStats(OC_Site &oc_site, const time_t	*timer);
//----------------------------------------------------------------------------[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_UpdateDailyRefStats                                               []                           
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Site_UpdateDailyRefStats(			OC_Site&			oc_site,
										const	identifier&		ref_ID,
										const	time_t&			CurrentTime)
{
	OC_DailyReferrerStats	oc_daily_ref_stats;
	time_t						TimeDiff = CurrentTime - oc_site.m_DailyReferrerTimeStamp[oc_reg.m_DailyReferrerSize-1];
	int							i;
	SERVER_DEBUG_ASSERT_RETURN(
		TimeDiff >= 0,
		"BX_Site_UpdateDailyRefStats(): Referrer in the past. Aborted...",
		BX_SYSTEM_ERROR);
	SERVER_DEBUG_ASSERT_RETURN(
		oc_site.m_DailyReferrerStats.Size() == oc_reg.m_DailyReferrerSize,
		"BX_Site_UpdateDailyRefStats(): Bad size of Site::DailyReferrerStats. Aborted...",
		BX_SYSTEM_ERROR);

//----------------------------------------------------------------------------[]
// Открыть нужный контроллер OC_DailyReferrerStats:

	if (TimeDiff >= SECS_IN_DAY)
// Попадаем не в текущий день:
	{
	// Определить размер сдвига:
		int ShiftSize = TimeDiff / SECS_IN_DAY;
	// Если сдвиг меньше размера массива:
		if (ShiftSize < oc_reg.m_DailyReferrerSize)
		{
		// Произведем сдвиг:
			for (i = 0; i < oc_reg.m_DailyReferrerSize - ShiftSize; i++)
			{
			// Удалим ненужный контроллер:
				if (OC_Exist(OBJ_CLASS_ID_DailyReferrerStats, oc_site.m_DailyReferrerStats[i])) {
					oc_daily_ref_stats.Delete(oc_site.m_DailyReferrerStats[i]);
				}
			// Скопируем на его место нужный контроллер и время:
				oc_site.m_DailyReferrerStats		[i]	= oc_site.m_DailyReferrerStats		[i+ShiftSize];
				oc_site.m_DailyReferrerTimeStamp	[i]	= oc_site.m_DailyReferrerTimeStamp	[i+ShiftSize];
			}
		// Инициализируем остаток массива:
			for (i = oc_reg.m_DailyReferrerSize - ShiftSize; i < oc_reg.m_DailyReferrerSize; i++)
			{
				oc_site.m_DailyReferrerStats		[i]	= NA;
				oc_site.m_DailyReferrerTimeStamp [i]	= oc_site.m_DailyReferrerTimeStamp [i-1] + SECS_IN_DAY;
			}
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Если сдвиг больше либо равен размеру массива:
		else	{
		// Проинициализируем заново массив (с удалением контроллеров) - нам там больше ничего не нужно:
			BX_ASSERT_RETURN(BX_Site_InitDailyReferrerStats(oc_site, &CurrentTime));
		}
	}

// Откроем контроллер, если он там уже есть:
	identifier RefID = oc_site.m_DailyReferrerStats[oc_reg.m_DailyReferrerSize-1];
	if (RefID != NA)
	{
		oc_daily_ref_stats.Open(oc_site.m_DailyReferrerStats[oc_reg.m_DailyReferrerSize-1]);
		if (!oc_daily_ref_stats.IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("BX_Site_UpdateDailyRefStats(): Invalid DRS ID=%lu. Set to NA.", (unsigned long)RefID);
			oc_site.m_DailyReferrerStats[oc_reg.m_DailyReferrerSize-1] = RefID = NA;
		}
	}
	if (RefID == NA)
	{
	// Иначе создадим контроллер и положим его ID в конец:
		oc_daily_ref_stats.New();
		oc_daily_ref_stats.m_SiteID		= oc_site.GetObjectID();
		oc_daily_ref_stats.m_TimeStamp	= oc_site.m_DailyReferrerTimeStamp[oc_reg.m_DailyReferrerSize-1];

		oc_site.m_DailyReferrerStats[oc_reg.m_DailyReferrerSize-1] = oc_daily_ref_stats.GetObjectID();
	}

	oc_daily_ref_stats.m_CacheTime	= CurrentTime;

//----------------------------------------------------------------------------[]
// Найти/добавить в открытый контроллер ID нужного реферера:
	if ((i = oc_daily_ref_stats.m_Referrer.Find(ref_ID, true)) == -1)	{
		i = oc_daily_ref_stats.m_Referrer.InsertSorted(ref_ID);
		oc_daily_ref_stats.m_Count.Insert(i, 0);
	}
// Инкремент счетчика:
	oc_daily_ref_stats.m_Count[i] += 1;

	return BX_OK;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` RegisterSuspiciousEvent                                                   []                       
//                                                                            []
void RegisterSuspiciousEvent(	identifier		ObjectID,
										int				EventType,
										identifier		ViewerID,
										time_t			CurrentTime,
										const string&	Referrer)
{
// Загрузить объект:
	OC_SuspiciousInfo	oc_suspicious_info;
	oc_suspicious_info.Open(ObjectID);

	if (!oc_suspicious_info.IsValid())
	{
		SERVER_DEBUG_ERROR_2("RegisterSuspiciousEvent(): Invalid SuspiciousInfo ID passed (#%lu). EventType = %d",
			(unsigned long)ObjectID, (int)EventType);
		return;
	}
// Реализация цикличности изменения массивов:
	if ((oc_suspicious_info.m_Pointer >= oc_reg.m_SuspiciousInfoSize) || (oc_suspicious_info.m_Pointer < 0)) {
		oc_suspicious_info.m_Pointer = 0;
	}

	int Pointer = oc_suspicious_info.m_Pointer;

// Если нужна большая длина массивов, то добавим, сколько надо:
	if (Pointer >= oc_suspicious_info.m_Viewer.Size())
	{
		for (int i = oc_suspicious_info.m_Viewer.Size(); i <= Pointer; i++)
		{
			oc_suspicious_info.m_Viewer.Add(NA);
			oc_suspicious_info.m_Time.Add(0);
			oc_suspicious_info.m_EventType.Add(0);
			oc_suspicious_info.m_Referrer.Add("");
		}
	}

// Зарегистрируем событие:
	oc_suspicious_info.m_Viewer	[Pointer] = ViewerID;
	oc_suspicious_info.m_Time		[Pointer] = CurrentTime;
	oc_suspicious_info.m_EventType[Pointer] = EventType;
	oc_suspicious_info.m_Referrer	[Pointer] = Referrer;

// Изменим указатель следующего изменяемого элемента:
	oc_suspicious_info.m_Pointer += 1;

	return;
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Counter_GetData                                                        []                  
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_Counter_GetData(BX_Counter_Args& arg)
{
	arg.ExitCode = int(CNTR_UNDEFINED);

	OC_Site			oc_site;
	key_arr			ka;
//----------------------------------------------------------------------------[] 
// Загрузим сайт:
	
	if (arg.Alias.Len() > 0)
	{
		oc_site.SetIndex_Alias();
		ka.Init();
		ka += arg.Alias;
		if (!oc_site.Find(ka))
		{
			arg.ExitCode = int(CNTR_INVALID_SITE_ID); // !!! Поправить на CNTR_INVALID_SITE_ALIAS
			return BX_OK;
		}
		arg.SiteID = oc_site.GetObjectID();
	}
	else 
	{
		if (arg.SiteID != NA)
		{
			oc_site.Open(arg.SiteID);
		}
		
		if (!oc_site.IsValid())
		{
			arg.ExitCode = int(CNTR_INVALID_SITE_ID);
			return BX_OK;
		}
	}
	
//----------------------------------------------------------------------------[]

//----------------------------------------------------------------------------[]
	arg.ExitCode = int(CNTR_OKAY);
//----------------------------------------------------------------------------[] 
	int			i					= 0;
	int			nPos				= -1;

	time_t		CurrentTime		= time_0;
	time_t		ReturnTime		= 0;	// Время последнего хита этого зрителя на этом сайте.
//----------------------------------------------------------------------------[] 
	OC_ShowEvent	oc_show_event;
	oc_show_event.SetIndex_SiteID_ViewerID__Time();
	ka.Init();
	ka += arg.SiteID;
	ka += arg.ViewerID;


//----------------------------------------------------------------------------[]
// Проверка на read-only:
	if (arg.JustGetData)
	{
		if (oc_show_event.Find(ka) && (CurrentTime - oc_show_event.m_Time < 5))
		{
			arg.ExitCode = oc_show_event.m_ExitCode;
		}

		FillCounterFields(oc_site, arg);
		return BX_OK;
	}
//----------------------------------------------------------------------------[] 
// Проверка на	IgnoredViewerID
	if (oc_site.m_IgnoredViewerID.Find(arg.ViewerID, true) != -1) {
		FillCounterFields (oc_site, arg);
		return BX_OK;
	}
//----------------------------------------------------------------------------[] 
// Проверка на	IgnoredIP
	IP_Address		ip_address(arg.ViewerIP);
	for (i = 0; i < oc_site.m_IgnoredIP.Size(); i++)
	{
		if (!ip_address.IsInRange(oc_site.m_IgnoredIP[i])) {
			arg.ExitCode = int(CNTR_WRONG_IP);
			/*!!!	RegisterSuspiciousEvent(oc_site.m_SuspiciousInfo,
													arg.ExitCode,
													oc_viewer.GetObjectID(),
													CurrentTime,
													arg.SiteURL);*/

			FillCounterFields (oc_site, arg);
			return BX_OK;
		}
	}
//----------------------------------------------------------------------------[] 
// Открыть VBN сайта:
	OC_VBN	oc_vbn;
	oc_vbn.SetIndex_No();
	ka.Init();
	ka += (byte)oc_site.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Counter_GetData(): Wrong Site::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

//----------------------------------------------------------------------------[]
// Время:
// GMT:
	BX_TimeStats_Args	time_stats_args;
	time_stats_args.timer = CurrentTime;
	BX_TimeStats_CreateArgs(time_stats_args);
// Local:
	BX_TimeStats_Args	localtime_stats_args;
	if (labs(arg.LocalTime - CurrentTime) <= 12*SECS_IN_HOUR)
	{
		localtime_stats_args.timer = arg.LocalTime;
		BX_TimeStats_CreateArgs(localtime_stats_args);
	}

//----------------------------------------------------------------------------[] 
// Зритель:
	OC_Viewer		oc_viewer;
	arg.ViewerIP.trim();

//----------------------------------------------------------------------------[] 
	bool				bAnonymousViewer	= false;	// Является ли зритель анонимным (без куки).
	bool				bHit					= false;	// Засчитан ли хит.
	bool				bSession				= false;	// Зритель пришёл с новой сессией.
	bool				bHost					= false;	// Является ли посетитель хостом.
	bool				bNewVisitor			= false;	// Является ли посетитель новым для сайта.

//----------------------------------------------------------------------------[]
// Идентифицируем зрителя. В arg.ViewerID возвращается Cookie,
// который надо отослать обратно на сайт (или NA, если возвращать ничего не надо):
	BX_ASSERT_RETURN(BX_GetViewer(oc_viewer, arg, bAnonymousViewer, CurrentTime));

//----------------------------------------------------------------------------[] 
// Проверим, не является ли этот сайт запрещённым модератором:
	if (oc_site.m_Allowed == false)
	{
		arg.ExitCode = int(CNTR_MODERATOR);
//		CREATE_SHOW_EVENT;
//		FillCounterFields (oc_site, arg);
		return BX_OK;
	}
//----------------------------------------------------------------------------[] 
// Проверка на	Mirrors
	if (!CheckMirrors(oc_site, arg))
	{
		arg.ExitCode = int(CNTR_WRONG_MIRROR);

		time_stats_args.Increment = 1;
		CHANGE_SUSPICIOUS;
//		CREATE_SHOW_EVENT;

/*!!!	RegisterSuspiciousEvent(oc_site.m_SuspiciousInfo,
										arg.ExitCode,
										oc_viewer.GetObjectID(),
										CurrentTime,
										arg.SiteURL);
*/		
//		FillCounterFields (oc_site, arg);
		return BX_OK;
	}

//----------------------------------------------------------------------------[] 
// Site::Loads
	INCREMENT_SITE_COUNTER_W_LASTSYNC	(Loads);
//----------------------------------------------------------------------------[] 
// Проверим, было ли событие с такими же параметрами в ближайшее время
// (Проверка накрутки и вычисление подозрительности сайта):
	ka.Init();
	ka += arg.SiteID;
	ka += arg.ViewerID;
	if (oc_show_event.Find(ka))
	{
		if ((CurrentTime - time_t(oc_show_event.m_Time)) < oc_reg.m_MinimumHitsTime)
		{
			arg.ExitCode = int(CNTR_WOUND);
			time_stats_args.Increment = 1;

			CHANGE_SUSPICIOUS;
		//	CREATE_SHOW_EVENT;

/*!!!			RegisterSuspiciousEvent(oc_site.m_SuspiciousInfo,
											arg.ExitCode,
											oc_viewer.GetObjectID(),
											CurrentTime,
											arg.SiteURL);
*/
			FillCounterFields (oc_site, arg);
			return BX_OK;
		}
	}

//______________________________________________________________________________
//                                                                            []
//` Update информации у зрителя:																[]                               
//                                                                            []
	UpdateViewerInfo  (oc_viewer, arg, CurrentTime, bNewVisitor, bHost, ReturnTime);


//______________________________________________________________________________
//                                                                            []
//`	MAIN UPDATE STAGE																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Update информации на сайте:

	CREATE_SHOW_EVENT;
	bHit	= true;


//----------------------------------------------------------------------------[] 
// Referrer
// !!! Тут еще надо вызвать функцию выдирания ключевых слов из аргументов реферера
	OC_Referrer		oc_referrer;
	HTTP_URL			PrevURL		= arg.Referrer.c_str();
	string			RefStr;
	bool				bIsMirror	= false;
	HTTP_URL			mirURL;

// Получим разобраный реферер:
	PrevURL.DomainPathFileExt(RefStr);	// без аргументов

// Обрежем, если слишком длинный:
	if (RefStr.Len() > MAX_REFERRER_LENGTH)
	{
		string TmpStr;
		RefStr.SubStr(TmpStr, 0, MAX_REFERRER_LENGTH);
		RefStr = TmpStr;
	}

// Проверим, а не является ли он зеркалом:
	for (i = 0; i < oc_site.m_MirrorInclude.Size(); i++) {
		mirURL = (string(oc_site.m_MirrorInclude[i])).c_str();
		if (PrevURL.IsChildFor(mirURL)) {
			bIsMirror = true;
			break;
		}
	}
	
// Для пустых рефереров и зеркал мы ничего не делаем:
	if ((RefStr.Len() > 0) && !bIsMirror)
	{
		unsigned long	PrevURL_CRC = RefStr.GetCRC();

		ka.Init();
		ka += PrevURL_CRC;

		if (!oc_referrer.Find(ka))
	// Такого реферера ещё не было - создадим:
		{
			oc_referrer.New();
			oc_referrer.m_Referrer			= RefStr;
			oc_referrer.m_CRC					= PrevURL_CRC;
		}
		else
	// Реферер с таким CRC уже был - проверим его уникальность:
		{
		// Совпадает ли этот реферер с нашим ?
			if (string(oc_referrer.m_Referrer) != RefStr)
			{
			// Не совпадает - будем искать дальше ...
				bool bFound;
				do
				{
				// Перейдем на следующего реферера с таким же CRC:
					bFound = oc_referrer.GoNextSame(&ka);
				// Если реферер совпадает с заданным, то это тот, которого мы ищем - на выход:
					if (bFound && (string(oc_referrer.m_Referrer) == RefStr)) {
						break;
					}
				}while (bFound);	// Пока есть ещё такие же значения CRC ...

			// Если так и не нашли нужного реферера, то придётся его создать:
				if (!bFound)
				{
					oc_referrer.New();
					oc_referrer.m_Referrer			= RefStr;
					oc_referrer.m_CRC					= PrevURL_CRC;
				}
			} // end if
		}	// end else

	// Другие поля у реферерра:
		oc_referrer.m_LastAccessTime	= CurrentTime;
		oc_referrer.m_CacheTime			= CurrentTime;
		oc_referrer.m_Count				+= 1;

	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Массив реферерров у сайта
		if ((nPos = oc_site.m_Referrer.Find(oc_referrer.GetObjectID(), true)) != -1)
		{
			oc_site.m_ReferrerCount[nPos] += 1;
		}
		else
		{
			nPos = oc_site.m_Referrer.InsertSorted(oc_referrer.GetObjectID());
			oc_site.m_ReferrerCount.Insert(nPos, 1);
		}
	} // end if ((RefStr.Len() > 0) 
//----------------------------------------------------------------------------[] 
// Site::RecentVisitors, RecentReferrers, RecentTimeStamp
// Инициализируем массив, если его размер не соответствует заданному в реестре:	
	if (oc_site.m_RecentVisitor.Size () != oc_reg.m_VisitorHistoryLength)
	{
		oc_site.m_RecentVisitor.	Alloc (oc_reg.m_VisitorHistoryLength, NA);
		oc_site.m_RecentReferrer.	Alloc (oc_reg.m_VisitorHistoryLength, NA);
		oc_site.m_RecentTimeStamp.	Alloc (oc_reg.m_VisitorHistoryLength, 0);
		//oc_site.m_RecentPointer = 0;
	}
	// Если уже есть этот зритель, вставим на его место:
	if ((nPos = oc_site.m_RecentVisitor.Find (arg.ViewerID)) != -1)
	{
		oc_site.m_RecentReferrer	[nPos]	= oc_referrer.IsValid() ? oc_referrer.GetObjectID () : NA;
		oc_site.m_RecentTimeStamp	[nPos]	= CurrentTime;
	}
	else	// Иначе добавим вместо самого старого:
	{
		nPos = oc_site.m_RecentTimeStamp.GetCPtr ().GetMinNo ();

		oc_site.m_RecentVisitor		[nPos]	= arg.ViewerID;
		oc_site.m_RecentReferrer	[nPos]	= oc_referrer.IsValid() ? oc_referrer.GetObjectID () : NA;
		oc_site.m_RecentTimeStamp	[nPos]	= CurrentTime;
	}
//----------------------------------------------------------------------------[]
// Site::DailyReferrerStats[], DailyReferrerTimeStamp[]
// Если массив ещё не инициализировался, то заполним его NA.
	if (oc_site.m_DailyReferrerStats.Size() != oc_reg.m_DailyReferrerSize) {
		BX_ASSERT_RETURN(BX_Site_InitDailyReferrerStats(oc_site, &CurrentTime));
	}
	if (oc_reg.m_DailyReferrerSize > 0) {
		BX_Site_UpdateDailyRefStats(oc_site, oc_referrer.GetObjectID(), CurrentTime);
	}


//----------------------------------------------------------------------------[]
// SessionTime, SessionTime_Local, AveSessionTime, AveReloadTime
	if ((oc_viewer.m_Site_SessionLastSiteID == arg.SiteID) && (ReturnTime <= MAX_SESSION_TIME))
	{
		bSession	= false;												// Сессия продолжается
		GROW_SESSION_TIME (ReturnTime);							// Увеличим продолжительность сессий.
	}
	else
	{
		bSession										= true;			// Новая сессия.
		oc_viewer.m_Site_SessionLastSiteID	= arg.SiteID;	// Запомним ID сайта.
		GROW_SESSION_NUM (1);										// Увеличим счетчик сессий.
	// Коррекция с учётом последнего релоада (т.е. + средняя длительность между релоадами за последние сутки)
		GROW_SESSION_TIME (oc_site.m_Total_AveReloadTime);
	}

//----------------------------------------------------------------------------[] 
// OnlineVisitors
	oc_show_event.SetIndex_SiteID_ViewerID();
	ka.Init();
	ka += arg.SiteID;
	oc_site.m_OnlineVisitors = oc_show_event.GetIndexUniqueNum(ka);

//----------------------------------------------------------------------------[]
// LastVisitTime
	oc_site.m_LastVisitTime = CurrentTime;

//----------------------------------------------------------------------------[] 
//`Обновление распределений концептов:
//----------------------------------------------------------------------------[]
	if (STATS_UPDATE_CONDITION)
	{
	//----------------------------------------------------------------------------[]
	// Viewer::CRA_Site += Site::CRN_VisitorIncr
		int_arr	CR = oc_viewer.m_CRA_Site.GetCPtr();
		PackedArrIncrement (CR, oc_site.m_CRN_VisitorIncr.GetCPtr());
		oc_viewer.m_CRA_Site.CopyFrom(CR.GetPtr(), CR.GetSize());


	//----------------------------------------------------------------------------[]
	// Viewer::CRN_Site = Normalize(Viewer::CRA_Site)
		if (oc_viewer.m_CRN_Site_Update >= VIEWER_CRN_SITE_UPDATE)
		{
			oc_viewer.m_CRN_Site_Update = 0;
			NormalizePackedArrInplace (CR);
			oc_viewer.m_CRN_Site.CopyFrom(CR.GetPtr(), CR.GetSize());
		}
		else
		{
			oc_viewer.m_CRN_Site_Update += 1;
		}
	//----------------------------------------------------------------------------[]
	// Registry::CRA_InetAudience += Viewer::CRN_Site
		CR = oc_reg.m_CRA_InetAudience.GetCPtr();
		PackedArrIncrement (CR, oc_viewer.m_CRN_Site.GetCPtr());
		oc_reg.m_CRA_InetAudience.CopyFrom(CR.GetPtr(), CR.GetSize());

	//----------------------------------------------------------------------------[]
	// Registry::CRN_InetAudience  = Normalize(Registry::CRA_InetAudience)
		if (oc_reg.m_CRN_InetAudience_Update >= REG_CRN_INETAUDIENCE_UPDATE)
		{
			oc_reg.m_CRN_InetAudience_Update = 0;
			NormalizePackedArrInplace (CR);
			oc_reg.m_CRN_InetAudience.CopyFrom(CR.GetPtr(), CR.GetSize());
		}
		else
		{
			oc_reg.m_CRN_InetAudience_Update += 1;			
		}
	//----------------------------------------------------------------------------[]
	// Site::CRA_Visitor += Viewer::CRN_Site
		CR = oc_site.m_CRA_Visitor.GetCPtr();
		PackedArrIncrement (CR, oc_viewer.m_CRN_Site.GetCPtr());
		oc_site.m_CRA_Visitor.CopyFrom(CR.GetPtr(), CR.GetSize());
	//----------------------------------------------------------------------------[]
	// Site::CRA_Visitor += Viewer::CRN_Inquiry
		CR = oc_site.m_CRA_Visitor.GetCPtr();
		PackedArrIncrement (CR, oc_viewer.m_CRN_Inquiry.GetCPtr());
		oc_site.m_CRA_Visitor.CopyFrom(CR.GetPtr(), CR.GetSize());

	//----------------------------------------------------------------------------[]
	// Site::CRN_Visitor = Normalize(Site::CRA_Visitor)
		if (oc_site.m_CRN_Visitor_Update >= SITE_CRN_VISITOR_UPDATE)
		{
			oc_site.m_CRN_Visitor_Update = 0;
			NormalizePackedArrInplace (CR);
			oc_site.m_CRN_Visitor.CopyFrom(CR.GetPtr(), CR.GetSize());
		}
		else
		{
			oc_site.m_CRN_Visitor_Update  += 1;			
		}

	}	 // end if (STATS_UPDATE_CONDITION)
//----------------------------------------------------------------------------[] 
// Пересчитаем поле CRN_VisitorIncr = CRN_Self+(CRN_Visitor-CRN_InetAudience)
	if (oc_site.m_CRN_VisitorIncr_Update >= SITE_CRN_VISITOR_INCR_UPDATE)
	{
		oc_site.m_CRN_VisitorIncr_Update = 0;

		int_arr	CRN_VisitorIncr;
	// Получим разность между аудиторным профилем сайта и инета:
		PackedArrNormalizedDiff(CRN_VisitorIncr,
										oc_site.m_CRN_Visitor.GetCPtr(),
										oc_reg.m_CRN_InetAudience.GetCPtr());
	// Сложим с собственным распределением сайта:
		PackedArrIncrement(CRN_VisitorIncr, oc_site.m_CRN_Self.GetCPtr());
	// Отфильтруем ненужные типы концептов, хранящиеся в Registry::ReservedInt1[]:
		BX_Concept_FilterType(CRN_VisitorIncr, oc_reg.m_ReservedInt1.GetCPtr());
	// Нормализуем:
		NormalizePackedArrInplace(CRN_VisitorIncr);
	// Положим в сайт:
		oc_site.m_CRN_VisitorIncr.CopyFrom(CRN_VisitorIncr.GetPtr(), CRN_VisitorIncr.GetSize());
	}
	else {
		oc_site.m_CRN_VisitorIncr_Update += 1;
	}
//----------------------------------------------------------------------------[] 
//`ПЕРЕСЕЧЕНИЕ АУДИТОРИЙ
//----------------------------------------------------------------------------[]
// Site::Audience_SiteID

	if (AUDINTESECT_UPDATE_CONDITION)
	{
		OC_Site		oc_other_site;
		identifier	otherSite_ID = NA;
	// По всем сайтам-конкурентам:
		for (i = 0; i < oc_viewer.m_Site.Size(); i++)
		{
		// Взять очередного конкурента:
			otherSite_ID = oc_viewer.m_Site[i];
		// Если конкурент уже не валиден, то удалим его у зрителя:
			if (!OC_Exist(OBJ_CLASS_ID_Site, otherSite_ID)) // !!! Может убрать тут Exist ?
			{
				oc_viewer.m_Site.					Del (i);
				oc_viewer.m_Site_LastHit.		Del (i);
				oc_viewer.m_Site_Hits.			Del (i);
				oc_viewer.m_Site_LastHost.		Del (i);
				oc_viewer.m_Site_Hosts.			Del (i);
				oc_viewer.m_Site_Votings.		Del (i);
				oc_viewer.m_Site_VoteDayNo.	Del (i); // !!! тут надо много чего ещё удалить...--- надо проверять при каждом изменении формата у зрителя
				i--;
				continue;
			}
		// Самого себя не будем прописывать:
			if (otherSite_ID == arg.SiteID) {
				continue;
			}

		// Откроем сайт конкурента:
			oc_other_site.Open(otherSite_ID);

			int	ThisSitePos = -1;

		// Инкрементируем у конкурента счетчик хостов, соответствующий нашему сайту:
			if ((ThisSitePos = oc_other_site.m_Audience_SiteID.Find (arg.SiteID, true)) == -1)
			{
				ThisSitePos = oc_other_site.m_Audience_SiteID.InsertSorted (arg.SiteID);
				oc_other_site.m_Audience_Viewers.Insert(ThisSitePos, 0);
				oc_other_site.m_Audience_Hosts.	Insert(ThisSitePos, 0);
			}
			oc_other_site.m_Audience_Hosts [ThisSitePos] += 1;

		// Зритель - новый:
			if (bNewVisitor)
			{
			// Пропишем конкурента у нашего сайта:
				if ((nPos = oc_site.m_Audience_SiteID.Find (otherSite_ID, true)) == -1)
				{
					nPos = oc_site.m_Audience_SiteID.InsertSorted (otherSite_ID);
					oc_site.m_Audience_Viewers.Insert(nPos, 0);
					oc_site.m_Audience_Hosts.	Insert(nPos, 0);
				}
				oc_site.m_Audience_Viewers [nPos] += 1;

			// Инкрементируем у конкурента счетчик зрителей, соответствующий нашему сайту:
				oc_other_site.m_Audience_Viewers[ThisSitePos] += 1;
			}
		} // end for (i
	}	// end if (AUDINTESECT_UPDATE_CONDITION)

//----------------------------------------------------------------------------[]
	if (bHost)
	{
	//----------------------------------------------------------------------------[]
	// ReturnNumRate
		if (oc_site.m_ReturnNumRate.Size() != oc_reg.m_ReturnNumRateSize) {
			oc_site.m_ReturnNumRate.Alloc(oc_reg.m_ReturnNumRateSize, 0);
		}

		if (arg.Visits <= oc_reg.m_ReturnNumRateSize)
		{
			if (arg.Visits > 1) {
				oc_site.m_ReturnNumRate[arg.Visits-2] -= 1;
			}

			oc_site.m_ReturnNumRate[arg.Visits-1] += 1;
		}
		else {
			oc_site.m_ReturnNumRate[oc_reg.m_ReturnNumRateSize-1] += 1;
		}
	} // end if (bHost)

//----------------------------------------------------------------------------[]
// Hits
	INCREMENT_SITE_COUNTER_W_LASTSYNC	(Hits);

	RECALC_AVE_COUNTER(oc_site.m_Total_AveReloadNum,	oc_site.m_Total_Hits,	oc_site.m_Total_SessionNum);
	RECALC_AVE_COUNTER(oc_site.m_LM_AveReloadNum,		oc_site.m_LM_Hits,	  	oc_site.m_LM_SessionNum);
	RECALC_AVE_COUNTER(oc_site.m_LW_AveReloadNum,		oc_site.m_LW_Hits,	  	oc_site.m_LW_SessionNum);
	RECALC_AVE_COUNTER(oc_site.m_LD_AveReloadNum,		oc_site.m_LD_Hits,	  	oc_site.m_LD_SessionNum);
	RECALC_AVE_COUNTER(oc_site.m_LH_AveReloadNum,		oc_site.m_LH_Hits,	  	oc_site.m_LH_SessionNum);
//----------------------------------------------------------------------------[]
// Hits_Local
	if (localtime_stats_args.timer > 0) {
		localtime_stats_args.Increment			= 1;
		localtime_stats_args.CalculateLast		= false;
		localtime_stats_args.idCounter			= oc_site.m_Hits_Local;
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(localtime_stats_args));
		oc_site.m_Hits_Local							= localtime_stats_args.idCounter;
	}
//----------------------------------------------------------------------------[]
// ActiveViewersID, ActiveViewersHits
	int nSize = oc_site.m_ActiveViewersID.Size();
	if (nSize < oc_reg.m_ActiveViewersSize || oc_site.m_ActiveViewersHits[0] < arg.Visits)
	{
	// Вставить или инкрементировать этого зрителя:
		int nPos = oc_site.m_ActiveViewersID.Find(arg.ViewerID);
		if (nPos != -1)	// старый зритель
		{
			oc_site.m_ActiveViewersID.		Del(nPos);
			oc_site.m_ActiveViewersHits.	Del(nPos);
		}
		nPos = oc_site.m_ActiveViewersHits.InsertSorted(arg.Visits);
		oc_site.m_ActiveViewersID.Insert(nPos, arg.ViewerID);

	// Уменьшим размер массива, если он превышает устанвленный лимит:		
		while (oc_site.m_ActiveViewersID.Size() > oc_reg.m_ActiveViewersSize)
		{
			oc_site.m_ActiveViewersID.		Del(0);
			oc_site.m_ActiveViewersHits.	Del(0);
		}
	}
//----------------------------------------------------------------------------[]
// Hosts
	if (bHost)
	{
		INCREMENT_SITE_COUNTER_W_LASTSYNC(Hosts);
		INCREMENT_VBN_COUNTER_WO_SYNC		(Hosts);
	// VisitorExperience
		oc_site.m_Total_VisitorExperience += oc_viewer.m_Site.Size();
		oc_site.m_Ave_VisitorExperience = oc_site.m_Total_Hosts == 0 ? 0 : int(oc_site.m_Total_VisitorExperience) / int(oc_site.m_Total_Hosts);
	}
	else
	{
		UPDATE_SITE_COUNTER_W_LASTSYNC	(Hosts);
	}
//----------------------------------------------------------------------------[]
// Visitors
	if (bNewVisitor)	{
		INCREMENT_SITE_COUNTER_W_LASTSYNC (Visitors);
	}
	else	{
		UPDATE_SITE_COUNTER_W_LASTSYNC (Visitors);
	}
//----------------------------------------------------------------------------[]
// Страничные счетчики:
#if 0  //{ AlexV
	if (arg.PageNo > 0)
	{
		int PageIndex = oc_site.m_PageNo.Find(arg.PageNo);
		if (PageIndex == -1)
		{
			oc_site.m_PageNo.Add(arg.PageNo);
			oc_site.m_PageName.Add(arg.Referrer);
			oc_site.m_Hits_Page.Add(NA);
			PageIndex = oc_site.m_PageNo.Size() - 1;
		}
	// HS_Hits_Page
		if (oc_site.m_Hits_Page.Size() > PageIndex)
		{
			time_stats_args.Increment					= 1;
			time_stats_args.CalculateLast				= false;									
			time_stats_args.idCounter					= oc_site.m_Hits_Page[PageIndex];
			BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));		
			oc_site.m_Hits_Page[PageIndex]	= time_stats_args.idCounter;
		}
		else {
			SERVER_DEBUG_ERROR ("BX_Counter_GetData(): Unsynchronized Site::PageNo[] & Site::Hits_Page[].");
		}
	}
#endif //}
//----------------------------------------------------------------------------[]
// VisitorReturns
	if (ReturnTime > SECS_IN_MIN)
	{
		oc_site.m_Total_VisitorReturns += 1;

		int oc_site_m_Total_VisitorReturns = (int)oc_site.m_Total_VisitorReturns;
		if (ReturnTime < SECS_IN_HOUR)
		{
			oc_site.m_LH_VisitorReturns += 1;
		}
		else if (ReturnTime < SECS_IN_DAY)
		{
			oc_site.m_LD_VisitorReturns += 1;
		}
		else if (ReturnTime < SECS_IN_WEEK)
		{
			oc_site.m_LW_VisitorReturns += 1;
		}
		else if (ReturnTime < SECS_IN_MONTH)
		{
			oc_site.m_LM_VisitorReturns += 1;
		}
		oc_site.m_LH_VisitorReturns_Prc = GET_PERCENT(oc_site.m_LH_VisitorReturns, oc_site_m_Total_VisitorReturns);
		oc_site.m_LD_VisitorReturns_Prc = GET_PERCENT(oc_site.m_LD_VisitorReturns, oc_site_m_Total_VisitorReturns);
		oc_site.m_LW_VisitorReturns_Prc = GET_PERCENT(oc_site.m_LW_VisitorReturns, oc_site_m_Total_VisitorReturns);
		oc_site.m_LM_VisitorReturns_Prc = GET_PERCENT(oc_site.m_LM_VisitorReturns, oc_site_m_Total_VisitorReturns);
	}
//----------------------------------------------------------------------------[]
// AnonymousVisitors
	if (bAnonymousViewer && bNewVisitor) {
		oc_site.m_Total_AnonymousVisitors += 1;
	}
	oc_site.m_Total_AnonymousVisitors_Prc = GET_PERCENT(oc_site.m_Total_AnonymousVisitors, oc_site.m_Total_Visitors);

// AnonymousHits
	if (bAnonymousViewer)
	{
		INCREMENT_SITE_COUNTER_W_LASTSYNC(AnonymousHits);
	}

	oc_site.m_Total_AnonymousHits_Prc	= GET_PERCENT(oc_site.m_Total_AnonymousHits,	oc_site.m_Total_Hits);
	oc_site.m_LM_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LM_AnonymousHits,		oc_site.m_LM_Hits);	
	oc_site.m_LW_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LW_AnonymousHits,		oc_site.m_LW_Hits);	
	oc_site.m_LD_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LD_AnonymousHits,		oc_site.m_LD_Hits);	
	oc_site.m_LH_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LH_AnonymousHits,		oc_site.m_LH_Hits);	

//----------------------------------------------------------------------------[]
// Изменим статистику подозрительных хитов:
	time_stats_args.Increment			= 0;
	CHANGE_SUSPICIOUS;
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	FillCounterFields (oc_site, arg);

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 03.02.2000 by AlexV
		for (i = 0; i < oc_viewer.m_Site.Size(); i++)
		{
		// Взять очередного конкурента:
			otherSite_ID = oc_viewer.m_Site[i];
		// Пропустить себя:
			if (otherSite_ID == arg.SiteID) {
				continue;
			}
		// Если этот сайт ещё валиден:		
			if (OC_Exist(OBJ_CLASS_ID_Site, otherSite_ID))
			{
			// Открыть:
				oc_other_site.Open(otherSite_ID);

			// Найти у конкурента запись, соответствующую этому сайту:
				int	otherSite_IDSize = 
					oc_other_site.m_Audience_SiteID.Size();						// количество конкурентов у другого сайта

				const identifier * oc_other_site_m_Audience_SiteID =
					oc_other_site.m_Audience_SiteID.GetPtr();						// массив конкурентов у другого сайта

				int _j			= otherSite_IDSize/*+1*/;		// позиция меньшего либо равного (если bFound==true) arg.Site
				bool bFound		= false;								// идентификатора в массиве конкурентов у дргого сайта.
			// Поиск начинаем с позиции, которую последний раз изменяли:
				for (j = thisSite_Pos; j < otherSite_IDSize; j++)
				{
					if (oc_other_site_m_Audience_SiteID[j] == arg.SiteID)
					{
						thisSite_Pos = _j = j;
						bFound = true;
						break;
					}
					else if(oc_other_site_m_Audience_SiteID[j] > arg.SiteID)
					{
						_j = j;
						break;
					}
				}

			// Если не нашли запись для этого сайта, то вставим её на нужное место:
				if (!bFound)
				{
					oc_other_site.m_Audience_SiteID.	Insert (_j, arg.SiteID);
					oc_other_site.m_Audience_Viewers.Insert (_j, 0);
					oc_other_site.m_Audience_Hosts.	Insert (_j, 0);
					thisSite_Pos = _j;
				}
			// Инкрементируем у конкурента счётчик хостов этого сайта:
				oc_other_site.m_Audience_Hosts[thisSite_Pos] += 1;
			
				if (bNewVisitor)
				{
				// Инкрементируем у конкурента счётчик зрителей этого сайта:
					oc_other_site.m_Audience_Viewers[thisSite_Pos] += 1;
				}
			}
		// Сайт не валиден - удалим его запись у зрителя:
			else
			{
				oc_viewer.m_Site.					Del(i);
				oc_viewer.m_Site_LastHit.		Del(i);
				oc_viewer.m_Site_Hits.			Del(i);
				oc_viewer.m_Site_LastHost.		Del(i);
				oc_viewer.m_Site_Hosts.			Del(i);
				oc_viewer.m_Site_Votings.		Del(i);
				oc_viewer.m_Site_VoteDayNo.	Del(i); // !!! тут надо много чего ещё удалить...--- надо проверять при каждом изменении формата у зрителя
				i--;
				continue;
			}

		} // end for (i
	}	// end if (bHost)

#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *
