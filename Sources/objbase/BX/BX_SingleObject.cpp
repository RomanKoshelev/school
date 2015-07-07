/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_SingleObject.cpp                                       []
[] Date:            01.04.2000                                                []
[] Author:			  Alex Vershinin, Roman V. Koshelev									[]
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_Language
#define USES_BX_Concept
#define USES_BX_VBN
#define USES_BX_User
#define USES_BX_Site
#define USES_BX_Stats
#define USES_BX_Admin
#define USES_BX_Viewer
#define USES_BX_Events
#define USES_BX_Counter

#define USES_OBServer_Interface_h

#define USES_OC_ShowEvent
#define USES_OC_IPRecord
#define USES_OC_Referrer
#define USES_OC_DailyReferrerStats

#include "BX.h"
//----------------------------------------------------------------------------[]



#define CACHE_CLEAR_TIME (10*60)


//----------------------------------------------------------------------------[]
long		SERVER_TIME_ZONE_OFFSET = 0;
int		CACHE_DEBUG					= false;
//----------------------------------------------------------------------------[]



//______________________________________________________________________________
//                                                                            []
//` BX_SingleObject_Cache                                                     []                     
//                                                                            []
struct BX_SingleObject_Cache
{
	CPtr<OC_User>						m_User;
	CPtr<OC_Banner>					m_Banner;
	CPtr<OC_BannerProfile>			m_BannerProfile;
	CPtr<OC_Site>						m_Site;
	CPtr<OC_SiteProfile>				m_SiteProfile;
	CPtr<OC_Concept>					m_Concept;
	CPtr<OC_Language>					m_Language;
	CPtr<OC_VBN>						m_VBN;
	CPtr<OC_ShowEvent>				m_ShowEvent;
	CPtr<OC_IPRecord>					m_IPRecord;
	CPtr<OC_Referrer>					m_Referrer;


   CPtr<OC_DailyReferrerStats>   m_DailyReferrerStats;
   CPtr<OC_TimeStats>            m_TimeStats;
   CPtr<OC_YearStats>            m_YearStats;
   CPtr<OC_DayStats>             m_DayStats;
   CPtr<OC_Viewer>               m_Viewer;

   void Clear (void);
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` BX_SingleObject_Cache::Clear                                              []                     
//                                                                            []
void BX_SingleObject_Cache::Clear (void)
{
   SERVER_DEBUG_TEXT ("BX_SingleObject: Начало очистки кеша");
   m_IPRecord             .Erase();
   m_Referrer             .Erase();
   m_DailyReferrerStats   .Erase();
   m_TimeStats            .Erase();
   m_DayStats             .Erase();
   m_Viewer               .Erase();
   m_YearStats            .Erase();
   SERVER_DEBUG_TEXT ("BX_SingleObject: Очистка кеша завершена");
}
//____________________________________________________________________________[]








//----------------------------------------------------------------------------[]
#define CACHE_SUBSCRIBE(C)																		\
	Subscribe (EMM_ObjBase, EMT_Object_New,	OBJ_CLASS_ID_##C); 					\
	Subscribe (EMM_ObjBase, EMT_Object_Open,	OBJ_CLASS_ID_##C);					\
	Subscribe (EMM_ObjBase, EMT_Object_Delete,OBJ_CLASS_ID_##C,	UNKNOWN, true)
//----------------------------------------------------------------------------[]


//______________________________________________________________________________
//                                                                            []
//` Конструктор																					[]
//                                                                            []
BX_SingleObject::BX_SingleObject()
{
	m_Name = "BX_SingleObject";
	SERVER_DEBUG_TEXT ("Конструктор SingleObject запущен.");


	m_pCACHE = new BX_SingleObject_Cache;

	SERVER_TIME_ZONE_OFFSET = GetTZOffset ();

	m_pOC_Registry = new OC_Registry;
	SERVER_DEBUG_ASSERT (m_pOC_Registry != NULL,
		"BX_SingleObject::BX_SingleObject(): error allocating space for OC_Registry.");

// Уничтожаем все события	
	OC_ShowEvent oc_show_event;
	oc_show_event.DeleteClassObjects ();

// Обнуляем номера апгрейдов кешей.
	CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate =0;

// Подписываемся на кеширование объектов
	CACHE_SUBSCRIBE (User);
	CACHE_SUBSCRIBE (Site);
	CACHE_SUBSCRIBE (SiteProfile);
	CACHE_SUBSCRIBE (Banner);
	CACHE_SUBSCRIBE (BannerProfile);
	CACHE_SUBSCRIBE (Concept);
	CACHE_SUBSCRIBE (Language);
	CACHE_SUBSCRIBE (VBN);
	CACHE_SUBSCRIBE (ShowEvent);
	CACHE_SUBSCRIBE (IPRecord);
	CACHE_SUBSCRIBE (Referrer);
	

	CACHE_SUBSCRIBE (DailyReferrerStats);	
	CACHE_SUBSCRIBE (TimeStats);
	CACHE_SUBSCRIBE (YearStats);
	CACHE_SUBSCRIBE (DayStats);
	CACHE_SUBSCRIBE (Viewer);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Инициализация																					[]
//                                                                            []
void BX_SingleObject::Create (void)
{
	RegisterErrorDescriptions	();
	CreateEnumObjects				();
	GetSiteIndexInfo				();
	return;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Деструктор																						[]
//                                                                            []
BX_SingleObject::~BX_SingleObject()
{
	UnsubscribeAll ();

// Уничтожаем все события	
	OC_ShowEvent oc_show_event;
	oc_show_event.DeleteClassObjects ();

	delete m_pOC_Registry;
	m_pOC_Registry = NULL;

	delete m_pCACHE;
	m_pCACHE = NULL;

	SERVER_DEBUG_TEXT ("Драйвер баннерной системы завершил работу");
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Обработка таймера																			[]
//                                                                            []
void BX_SingleObject::OnTimer (time_t cur_Time)
{
//----------------------------------------------------------------------------[] 
// Очищаем кеш
	{
		static time_t old_Time=0;
		if ((cur_Time-old_Time)>=CACHE_CLEAR_TIME)
		{
			printf ("\n*  CACHE::Clear() [start] [%d sec]\n", cur_Time-old_Time);
			m_pCACHE->Clear  ();
			puts   ("*  CACHE::Clear() [done]");
			old_Time = cur_Time;
		}
	}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
// Удаляем старые события
	OC_ShowEvent oc_show_event;
	oc_show_event.SetIndex_Time();
	key_arr ka;
	ka += int (cur_Time - MAX_EVENT_STORAGE_TIME - 1);

	while (oc_show_event.Find(ka,true))
	{
		oc_show_event.Delete ();
	}
//----------------------------------------------------------------------------[] 

	
//----------------------------------------------------------------------------[] 
// Производим Update счётчиков у редкопосещаемых сайтов
	BX_Site_UpdateLastCounters (cur_Time);
//----------------------------------------------------------------------------[] 

}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` CACHE_CONTROL																					[]
//                                                                            []
#define CASE_CACHE_CONTROL(C)																	\
	case OBJ_CLASS_ID_##C: switch (Event.m_Type)											\
	{																									\
		case EMT_Object_New:																		\
		{																								\
			OC_##C oc=Event.objID;																\
			m_pCACHE->m_##C.Add(oc);															\
			if (CACHE_DEBUG) printf ("   Cache::New    %s\n", #C);					\
		}																								\
		break;																						\
																										\
		case EMT_Object_Open: if (Event.objID!=NA)										\
		{																								\
			bool bInCache=false;																	\
			for (int i=0; i<m_pCACHE->m_##C.Size(); i++)									\
			{																							\
				if (m_pCACHE->m_##C[i].GetObjectID() == Event.objID)					\
				{																						\
					bInCache = true;																\
					break;																			\
				}																						\
			}																							\
			if (!bInCache)																			\
			{																							\
				OC_##C oc;																			\
				oc.Open (Event.objID);															\
				m_pCACHE->m_##C.Add (oc);														\
				if (CACHE_DEBUG) printf ("   Cache::Open   %s\n", #C);				\
			}																							\
		}																								\
		break;																						\
																										\
		case EMT_Object_Delete:																	\
		{																								\
			bool bDeleted=false;																	\
			for (int i=0; i<m_pCACHE->m_##C.Size() && !bDeleted; i++)				\
			{																							\
				if (m_pCACHE->m_##C[i].GetObjectID() == Event.objID)					\
				{																						\
					m_pCACHE->m_##C.Remove(i);													\
					bDeleted = true;																\
					if (CACHE_DEBUG) printf ("   Cache::Delete %s\n", #C);			\
					break;																			\
				}																						\
			}																							\
			if (!bDeleted)																			\
			{																							\
				SERVER_DEBUG_ERROR ( "BX_SingleObject::OnEvent: Объект не найден в кеше");\
			}																							\
		}																								\
		break;																						\
	}																									\
	break;
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Обработка событий																			[]
//                                                                            []
bool BX_SingleObject::OnEvent (const EM_Event& Event)
{
	SERVER_DEBUG_ASSERT_RETURN (Event.m_Module==EMM_ObjBase, "BX_SingleObject::OnEvent: Пришло событие от незарегистрированного модуля!", true);

// Контроль за кэшем объектов
	switch (Event.classID)
	{
		CASE_CACHE_CONTROL (User);
		CASE_CACHE_CONTROL (Banner);
		CASE_CACHE_CONTROL (BannerProfile);
		CASE_CACHE_CONTROL (Site);
		CASE_CACHE_CONTROL (SiteProfile);
		CASE_CACHE_CONTROL (Concept);
		CASE_CACHE_CONTROL (Language);
		CASE_CACHE_CONTROL (VBN);
		CASE_CACHE_CONTROL (ShowEvent);
		CASE_CACHE_CONTROL (IPRecord);
		CASE_CACHE_CONTROL (Referrer);

	// !!! !!! !!! !!! !!! !!! !!! !!!
		CASE_CACHE_CONTROL (DailyReferrerStats);
		CASE_CACHE_CONTROL (TimeStats);
		CASE_CACHE_CONTROL (YearStats);
		CASE_CACHE_CONTROL (DayStats);		
		CASE_CACHE_CONTROL (Viewer);
	// !!! !!! !!! !!! !!! !!! !!! !!!

		default: 
			SERVER_DEBUG_ERROR ("BX_SingleObject::OnEvent: В аргументах события незарегистрированный класс!");
		return true;
	}

	return true;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` RegisterErrorDescriptions                                                 []                         
//                                                                            []
void BX_SingleObject::RegisterErrorDescriptions ()
{
	REGISTER_ERROR_DESCRIPTION (BX_OK);

	REGISTER_ERROR_DESCRIPTION (BXE_BadAdminPassword);
// FILE: BX_Enum.cpp
	REGISTER_ERROR_DESCRIPTION (BXE_NoLanguages);
	REGISTER_ERROR_DESCRIPTION (BXE_Language_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_Language_New_InvalidLanguageNameList);
	REGISTER_ERROR_DESCRIPTION (BXE_Language_New_InvalidLanguageTransList);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_New_InvalidParentID);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_New_InvalidNameList);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_New_InvalidDescriptionList);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_New_RootAlreadyExists);
	REGISTER_ERROR_DESCRIPTION (BXE_Concept_New_InvalidTypeInfo);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_New_PasswordVoid);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_New_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_New_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_GetData_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_GetOwnerID_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_GetOwnerID_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_Delete_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_Delete_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_VBN_RangeTooLarge);
	REGISTER_ERROR_DESCRIPTION (BXE_IPRecord_InvalidID);
	REGISTER_ERROR_DESCRIPTION (BXE_IPRecord_InvalidIP);


	REGISTER_ERROR_DESCRIPTION (BXE_Viewer_GetData_InvalidViewerID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_LoginAlreadyExists);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_BadPasswordConfirm);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_InvalidEmail);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_InvalidVBN);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_PasswordTooShort);
	REGISTER_ERROR_DESCRIPTION (BXE_User_New_LoginTooShort);
	REGISTER_ERROR_DESCRIPTION (BXE_User_GetData_InvalidVBN);
	REGISTER_ERROR_DESCRIPTION (BXE_User_GetData_LoginNotFound);
	REGISTER_ERROR_DESCRIPTION (BXE_User_GetData_PasswordIncorrect);
	REGISTER_ERROR_DESCRIPTION (BXE_User_GetData_InvalidUserID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_PutData_InvalidUserID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_Delete_SystemUser);
	REGISTER_ERROR_DESCRIPTION (BXE_User_Delete_InvalidUserID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_SiteEnumerate_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_BannerEnumerate_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_SiteProfileEnumerate_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_BannerProfileEnumerate_InvalidObjectID);
 	REGISTER_ERROR_DESCRIPTION (BXE_User_RegisterAsSystem_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_User_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_New_InvalidUserID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_New_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_CopyData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_CopyData_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_GetData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_PutData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_Delete_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteProfile_Delete_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_New_InvalidOwnerID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_New_InvalidSourceID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_GetData_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_PutData_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_PutData_ProfileAccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_Delete_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_GetCounterType_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteSuspiciousInfo_GetData_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_Site_GetAudienceIntersect_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_New_InvalidUserID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_CopyData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_GetData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_PutData_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_Delete_InvalidProfileID);
	REGISTER_ERROR_DESCRIPTION (BXE_BannerProfile_Delete_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_New_InvalidOwnerID);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_New_InvalidFileSize);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_GetData_InvalidBannerID);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_PutData_InvalidBannerID);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_PutData_ProfileAccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_Banner_Delete_InvalidBannerID);


// FILE: BX_Common.cpp

// FILE: BX_Events.cpp
	REGISTER_ERROR_DESCRIPTION (BXE_ClickEvent_New_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_ClickEvent_New_InvalidBannerID);
	REGISTER_ERROR_DESCRIPTION (BXE_ShowEvent_New_InvalidSiteID);

// FILE: BX_Stats.cpp
	REGISTER_ERROR_DESCRIPTION (BXE_RateStats_InvalidVBN);
	REGISTER_ERROR_DESCRIPTION (BXE_RateStats_InvalidKeyIndex);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteStats_InvalidSiteID);
	REGISTER_ERROR_DESCRIPTION (BXE_SiteStats_InvalidSitePassword);

// FILE: BX_TimeStats.cpp
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidRange);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidOutputFormat);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidTZOffset);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidObjectID);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_AccessDenied);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidCounterName);
	REGISTER_ERROR_DESCRIPTION (BXE_TimeStats_GetData_InvalidCounterID);

// Сработал ASSERT
	REGISTER_ERROR_DESCRIPTION (BX_SYSTEM_ERROR);
// Неопознанный запрос
	REGISTER_ERROR_DESCRIPTION (OBServer_UnsupportedFunctionCall);

// Выходной буфер переполнен
	REGISTER_ERROR_DESCRIPTION (OBServer_OutputBufferOverflow);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` CreateEnumObjects                                                         []                 
//                                                                            []
void BX_SingleObject::CreateEnumObjects(void)
{
	if (
		!CLEAR_FILE_SYSTEM_BEFORE_START && 
		m_pOC_Registry->m_Language.GetSize()!=0  // !!! -- СДЕЛАТЬ СПЕЦ ФЛАГ.
		) 
	{
		return;
	}

	string	tempStr;

//----------------------------------------------------------------------------[]
//`Language

	BX_Language_Args	language_args;
	
	GetAdminPassword(language_args.AdminPassword);
	language_args.OwnName			= "Русский язык";
	language_args.ShortName			= "RUS";
	SERVER_DEBUG_ASSERT (BX_Language_New(language_args) == BX_OK,
		"CreateEnumObjects(): Error in BX_Language_New.");

	language_args.objID				= NA;
	language_args.OwnName			= "English language";
	language_args.ShortName			= "ENG";
	language_args.Language.			Add("Russian language");
	language_args.Name.				Add("Английский язык");
	SERVER_DEBUG_ASSERT (BX_Language_New(language_args) == BX_OK,
		"CreateEnumObjects(): Error in BX_Language_New.");

//----------------------------------------------------------------------------[] 

	ConceptCompiler();

//----------------------------------------------------------------------------[] 
// VBN 1
	BX_Concept_Args	concept_args;
	SERVER_DEBUG_ASSERT(BX_Concept_Enumerate(concept_args) == BX_OK,
		"CreateEnumObjects(): Error in BX_Concept_Enumerate.");

	BX_VBN_Args		vbn_arg;
	BX_User_Args	user_arg;
	BX_Site_Args	site_arg;	

	CREATE_PREDEFINED_OBJECTS;

	concept_args.ConceptType.Erase();
	concept_args.ConceptType.Add("Concept.Viewer.OS"					);
	concept_args.ConceptType.Add("Concept.Viewer.Browser"				);
	concept_args.ConceptType.Add("Concept.Viewer.Charset"				);
	concept_args.ConceptType.Add("Concept.Viewer.Language"			);
	concept_args.ConceptType.Add("Concept.Viewer.ScreenSize"			);
	concept_args.ConceptType.Add("Concept.Viewer.Colors"				);
	concept_args.ConceptType.Add("Concept.Viewer.JavaScriptVersion");
	concept_args.ConceptType.Add("Concept.Viewer.Java"					);
	concept_args.ConceptType.Add("Concept.Banner"						);
	concept_args.ConceptType.Add("Concept.Banner.Appearance"			);
	concept_args.ConceptType.Add("Concept.Banner.Shape"				);
	concept_args.ConceptType.Add("Concept.Banner.Format"				);
	concept_args.ConceptType.Add("Concept.Goods&Services"				);
	concept_args.ConceptType.Add("Concept.Goods&Services.Goods"		);
	concept_args.ConceptType.Add("Concept.Goods&Services.Soft"		);
	concept_args.ConceptType.Add("Concept.Goods&Services.Services"	);
	concept_args.ConceptType.Add("Concept.Goods&Services.Price"		);
	BX_ASSERT(BX_Concept_SetFilter(concept_args));

	return;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Получить смещение временной зоны                                          []                                
//                                                                            []
time_t GetTZOffset (void)
{
	time_t time_0 = time (NULL);
	tm LcTime; 	memcpy (&LcTime, localtime (&time_0), sizeof (tm));
	tm GmTime; 	memcpy (&GmTime, gmtime		(&time_0), sizeof (tm));
	
	return mktime(&LcTime) - mktime(&GmTime);
}
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
static char* SiteIndexNameArr[]  = {
"Name", "NULL(Alias)", "CreationTime", "NULL(LastVisitTime)",
"LastUpdateTime", "NULL(Allowed,ObjectState)", "Total_Loads", "Total_Hosts",
"Total_Hits", "Total_AnonymousHits", "Total_AnonymousHits_Prc", "Total_SuspiciousHits_Prc",
"Total_Visitors", "Total_VisitorReturns", "Total_VisitorReturns_Prc", "Total_SessionNum",
"Total_AveSessionTime", "Total_AveReloadTime", "Total_AveReloadNum", "Total_Shows",
"Total_Clicks", "Total_CTR_Prc", "Total_CPH_Prc", "Total_AnonymousVisitors",
"Total_AnonymousVisitors_Prc", "Total_VisitorExperience", "Ave_VisitorExperience", "OnlineVisitors",
"Total_MouseOver", "Total_Votes", "Total_Votes_Sum", "Total_Votes_Ave",
"LM_Loads", "LM_Hosts", "LM_Hits", "LM_AnonymousHits",
"LM_AnonymousHits_Prc", "LM_SuspiciousHits_Prc", "LM_Visitors", "LM_VisitorReturns",
"LM_VisitorReturns_Prc", "LM_SessionNum", "LM_AveSessionTime", "LM_AveReloadTime",
"LM_AveReloadNum", "LM_Shows", "LM_Clicks", "LM_CTR_Prc",
"LM_CPH_Prc", "LW_Loads", "LW_Hosts", "LW_Hits",
"LW_AnonymousHits", "LW_AnonymousHits_Prc", "LW_SuspiciousHits_Prc", "LW_Visitors",
"LW_VisitorReturns", "LW_VisitorReturns_Prc", "LW_SessionNum", "LW_AveSessionTime",
"LW_AveReloadTime", "LW_AveReloadNum", "LW_Shows", "LW_Clicks",
"LW_CTR_Prc", "LW_CPH_Prc", "LD_Loads", "LD_Hosts",
"LD_Hits", "LD_AnonymousHits", "LD_AnonymousHits_Prc", "LD_SuspiciousHits_Prc",
"LD_Visitors", "LD_VisitorReturns", "LD_VisitorReturns_Prc", "LD_SessionNum",
"LD_AveSessionTime", "LD_AveReloadTime", "LD_AveReloadNum", "LD_Shows",
"LD_Clicks", "LD_CTR_Prc", "LD_CPH_Prc", "LH_Loads",
"LH_Hosts", "LH_Hits", "LH_AnonymousHits", "LH_AnonymousHits_Prc",
"LH_SuspiciousHits_Prc", "LH_Visitors", "LH_VisitorReturns", "LH_VisitorReturns_Prc",
"LH_SessionNum", "LH_AveSessionTime", "LH_AveReloadTime", "LH_AveReloadNum",
"LH_Shows", "LH_Clicks", "LH_CTR_Prc", "LH_CPH_Prc",
"CustomIndex1", "CustomIndex2", "CustomIndex3", "CustomIndex4", "CustomIndex5", NULL};
//----------------------------------------------------------------------------[]
static pSiteCounter SiteIndexFieldsArr[] = {
NULL,													NULL,												NULL,
NULL,													NULL,												NULL,
&OC_Site::m_Total_Loads,						&OC_Site::m_Total_Hosts,					&OC_Site::m_Total_Hits,
&OC_Site::m_Total_AnonymousHits,				&OC_Site::m_Total_AnonymousHits_Prc,	&OC_Site::m_Total_SuspiciousHits_Prc,
&OC_Site::m_Total_Visitors,					&OC_Site::m_Total_VisitorReturns,		&OC_Site::m_Total_VisitorReturns_Prc,
&OC_Site::m_Total_SessionNum,					&OC_Site::m_Total_AveSessionTime,		&OC_Site::m_Total_AveReloadTime,
&OC_Site::m_Total_AveReloadNum,				&OC_Site::m_Total_Shows,					&OC_Site::m_Total_Clicks,
&OC_Site::m_Total_CTR_Prc,						&OC_Site::m_Total_CPH_Prc,					&OC_Site::m_Total_AnonymousVisitors,
&OC_Site::m_Total_AnonymousVisitors_Prc,	&OC_Site::m_Total_VisitorExperience,	&OC_Site::m_Ave_VisitorExperience,
&OC_Site::m_OnlineVisitors,					&OC_Site::m_Total_MouseOver,				&OC_Site::m_Total_Votes,
&OC_Site::m_Total_Votes_Sum,					&OC_Site::m_Total_Votes_Ave,				&OC_Site::m_LM_Loads,
&OC_Site::m_LM_Hosts,							&OC_Site::m_LM_Hits,							&OC_Site::m_LM_AnonymousHits,
&OC_Site::m_LM_AnonymousHits_Prc,			&OC_Site::m_LM_SuspiciousHits_Prc,		&OC_Site::m_LM_Visitors,
&OC_Site::m_LM_VisitorReturns,				&OC_Site::m_LM_VisitorReturns_Prc,		&OC_Site::m_LM_SessionNum,
&OC_Site::m_LM_AveSessionTime,				&OC_Site::m_LM_AveReloadTime,				&OC_Site::m_LM_AveReloadNum,
&OC_Site::m_LM_Shows,							&OC_Site::m_LM_Clicks,						&OC_Site::m_LM_CTR_Prc,
&OC_Site::m_LM_CPH_Prc,							&OC_Site::m_LW_Loads,						&OC_Site::m_LW_Hosts,
&OC_Site::m_LW_Hits,								&OC_Site::m_LW_AnonymousHits,				&OC_Site::m_LW_AnonymousHits_Prc,
&OC_Site::m_LW_SuspiciousHits_Prc,			&OC_Site::m_LW_Visitors,					&OC_Site::m_LW_VisitorReturns,
&OC_Site::m_LW_VisitorReturns_Prc,			&OC_Site::m_LW_SessionNum,					&OC_Site::m_LW_AveSessionTime,
&OC_Site::m_LW_AveReloadTime,					&OC_Site::m_LW_AveReloadNum,				&OC_Site::m_LW_Shows,
&OC_Site::m_LW_Clicks,							&OC_Site::m_LW_CTR_Prc,						&OC_Site::m_LW_CPH_Prc,
&OC_Site::m_LD_Loads,							&OC_Site::m_LD_Hosts,						&OC_Site::m_LD_Hits,
&OC_Site::m_LD_AnonymousHits,					&OC_Site::m_LD_AnonymousHits_Prc, &OC_Site::m_LD_SuspiciousHits_Prc,
&OC_Site::m_LD_Visitors,						&OC_Site::m_LD_VisitorReturns, &OC_Site::m_LD_VisitorReturns_Prc,
&OC_Site::m_LD_SessionNum,						&OC_Site::m_LD_AveSessionTime, &OC_Site::m_LD_AveReloadTime,
&OC_Site::m_LD_AveReloadNum,					&OC_Site::m_LD_Shows, &OC_Site::m_LD_Clicks,
&OC_Site::m_LD_CTR_Prc,							&OC_Site::m_LD_CPH_Prc, &OC_Site::m_LH_Loads,
&OC_Site::m_LH_Hosts,							&OC_Site::m_LH_Hits, &OC_Site::m_LH_AnonymousHits,
&OC_Site::m_LH_AnonymousHits_Prc, &OC_Site::m_LH_SuspiciousHits_Prc, &OC_Site::m_LH_Visitors,
&OC_Site::m_LH_VisitorReturns, &OC_Site::m_LH_VisitorReturns_Prc, &OC_Site::m_LH_SessionNum,
&OC_Site::m_LH_AveSessionTime, &OC_Site::m_LH_AveReloadTime, &OC_Site::m_LH_AveReloadNum,
&OC_Site::m_LH_Shows, &OC_Site::m_LH_Clicks, &OC_Site::m_LH_CTR_Prc,
&OC_Site::m_LH_CPH_Prc, &OC_Site::m_CustomIndex1, &OC_Site::m_CustomIndex2,
&OC_Site::m_CustomIndex3, &OC_Site::m_CustomIndex4, &OC_Site::m_CustomIndex5};



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 02.04.2000 by AlexV
#define GET_INDEX_NAME_AND_ID(_IndexName)                                     \
   oc_site.SetIndex_VBN__##_IndexName();                                      \
   iPos = AllSiteIndexNames.InsertSorted(#_IndexName);                        \
   AllSiteIndexIDs.Insert(iPos, oc_site.GetIndex());                          \
   AllSiteIndexFields.Insert(iPos, pSiteCounter(&OC_Site::m_##_IndexName));

#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *

/*______________________________________________________________________________
[]                                                                            []
[]` GetSiteIndexInfo                                                          []                
[]                                                                            */
void BX_SingleObject::GetSiteIndexInfo (void)
{
	int						iPos;
	int						indID = 0;

	AllSiteIndexNames.	Erase ();
	AllSiteIndexIDs.		Erase ();
	AllSiteIndexFields.	Erase ();

// Получить 3 параллельных массива, содержащих названия индексов,
// их ID и указатели на соответствующие поля счётчиков:

	for (indID=0; SiteIndexNameArr[indID] != NULL; indID++)
	{
		iPos = AllSiteIndexNames.	InsertSorted(SiteIndexNameArr[indID]);
		AllSiteIndexIDs.				Insert(iPos, indID);
		AllSiteIndexFields.			Insert(iPos, SiteIndexFieldsArr[indID]);
	}

	
	return;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/