/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Viewer.cpp                                             []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "посетитель сайта".         []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                  
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Viewer
#define USES_BX_Macros
#define USES_BX_Counter
#define USES_BX_Events
#define USES_BX_Concept
#define USES_BX_IPRecord

//#define USES_OBServer_Interface_h
#define USES_UserAgent_h
#define USES_OC_Viewer
#define USES_OC_ViewerGroup
#define USES_OC_Site
#define USES_OC_ViewerReference

#include "BX.h"

//______________________________________________________________________________
//                                                                            []
//` BX_Viewer_Enumerate                                                       []                   
//                                                                            []
BX_RESULT BX_Viewer_Enumerate	(BX_Viewer_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_Viewer			oc_viewer;

	arg.objIDs.Delete();
	arg.objNames.Delete();

	string	Str;
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<oc_reg.m_Viewers.Size()); i++)
	{
		oc_viewer.Open(oc_reg.m_Viewers[i]);
		arg.objIDs.Add(oc_reg.m_Viewers[i]);
      Str.Format("#%lu: %s (%s)%s",
         oc_viewer.GetObjectID(),
         (string(oc_viewer.m_Referrer)).c_str(),
         (string(oc_viewer.m_IPAddress)).c_str(),
			bool(oc_viewer.m_Anonymous) ? "(*)":"");
		arg.objNames.Add(Str);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` BX_Viewer_GetData                                                         []                 
//                                                                            []
BX_RESULT BX_Viewer_GetData	(BX_Viewer_Args& arg)
{
	int i = 0;

// Открыть объект зрителя:
	OC_Viewer	oc_viewer;
	oc_viewer.Open(arg.objID);
	if (!oc_viewer.IsValid())
		return BXE_Viewer_GetData_InvalidViewerID;
	

//----------------------------------------------------------------------------[] 
// Скопировать данные:

// Anonymous
	arg.Anonymous			= (bool)oc_viewer.m_Anonymous;
// IPAddress
	arg.IPAddress			= oc_viewer.m_IPAddress;

// Viewer::Referrer
	arg.Referrer			= oc_viewer.m_Referrer;

// TZOffset
	arg.TZOffset			= (int)oc_viewer.m_TZOffset;
	
// ViewerParams
//	arg.ViewerParams		= oc_viewer.m_ViewerParams;
// Group
	arg.Group				= oc_viewer.m_Group;
// CreationTime
	time_t	Time =
		time_t(oc_viewer.m_CreationTime) + SERVER_TIME_ZONE_OFFSET;
	
	arg.CreationTime	= Time;
	arg.sCreationTime.Format("%s", asctime(gmtime(&Time)));
// LastVisitTime
	Time =
		time_t(oc_viewer.m_LastVisitTime) + SERVER_TIME_ZONE_OFFSET;
	
	arg.LastVisitTime	= Time;
	arg.sLastVisitTime.Format("%s", asctime(gmtime(&Time)));

// Site, sSite, Site_LastVisited, sSite_LastVisited, Site_Visits

	OC_Site		oc_site;

	arg.Site.					Delete();
	arg.sSite.					Delete();	
//	arg.Site_LastVisited.	Delete();	
	arg.sSite_LastVisited.	Delete();	
	arg.Site_Visits.			Delete();	
	
	
	for (i = 0; i < oc_viewer.m_Site.Size(); i++) 
	{
		BX_CHECK_AND_OPEN(oc_site, oc_viewer.m_Site[i], OBJ_CLASS_ID_Site);


		arg.Site.					Add(oc_viewer.m_Site[i]);
		arg.sSite.					Add(oc_site.m_Name);	
		Time = 
			time_t(oc_viewer.m_Site_LastHit[i]) + SERVER_TIME_ZONE_OFFSET;
//		arg.Site_LastVisited.	Add(Time);	
		arg.sSite_LastVisited.	Add(string(asctime(gmtime(&Time))));	
		arg.Site_Visits.			Add(oc_viewer.m_Site_Hosts[i]);	

	}

	return BX_OK;
}

//____________________________________________________________________________[]


/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[]` CreateViewer																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/
BX_RESULT
CreateViewer(OC_Viewer &oc_viewer, BX_Event_Args& arg, time_t CurrentTime)
{
// Создать объект зрителя:	
	BX_CREATE_AND_CHECK(oc_viewer);
// Добавить зрителя в реестр:
	oc_reg.m_Viewers.Add(oc_viewer.GetObjectID());

// Viewer::IPAddress
	oc_viewer.m_IPAddress		= arg.ViewerIP;
	oc_viewer.m_IPAddressHash	= arg.ViewerIP.GetCRC();

// Viewer::Referrer
	oc_viewer.m_Referrer			= arg.ViewerHostName;

// Viewer::TZOffset
	long		fDiff = arg.LocalTime - CurrentTime;
	if ((fDiff >= 12*SECS_IN_DAY) || (fDiff <= (-12*SECS_IN_DAY))) {
		oc_viewer.m_TZOffset = -1;
	}
	else
	{
		oc_viewer.m_TZOffset			= fDiff > 0 ?
													(fDiff / 1800)*1800 :
													((-fDiff) / 1800)*(-1800) ;
//													int(floor(fDiff / 1800.0 + 0.5))*1800 :
//													int(ceil (fDiff / 1800.0 - 0.5))*1800 ;
	}

#if 0  //{ AlexV	- перенесено в UpdateViewerInfo(), чтобы считать хиты, а не зрителей.
// CRA_Inquiry - регионы
	RegisterIP(arg.ViewerIP, oc_viewer);

#endif //}
// Viewer::*Time
	oc_viewer.m_CreationTime	= CurrentTime;
	oc_viewer.m_LastVisitTime	= CurrentTime;
	oc_viewer.m_CacheTime		= CurrentTime;

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[]` BX_GetViewer																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_GetViewer(	OC_Viewer&			oc_viewer,
					/*OC_ViewerGroup&	oc_viewer_group,*/
					BX_Event_Args&		arg,
					bool&					bAnonymousViewer, 
					time_t				CurrentTime)
{
	key_arr			ka;

// Если в куки невалидный ID, то установим его в NA:
	if ((arg.ViewerID != NA) && (!OC_Exist(OBJ_CLASS_ID_Viewer, arg.ViewerID)))
	{
//		SERVER_DEBUG_VALUE(arg.ViewerID);
		arg.ViewerID			= NA;
		arg.CookieSupported	= false;
//		arg.ExitCode			= int(CNTR_INVALID_COOKIE);
	}

// Идентификация зрителя:
//----------------------------------------------------------------------------[] 
	if	(arg.CookieSupported == false)
// Cookie не поддерживается - будем использовать разделяемый по IP-адресу объект:
	{
		bAnonymousViewer				= true;
		OC_ViewerReference		oc_viewer_reference;

		unsigned long Hash = arg.ViewerIP.GetCRC();
	
		oc_viewer_reference.SetIndex_IPAddressHash();
		ka.Init();
		ka += Hash;

	// Если объект не найден по IP, то создадим его :
		if (!oc_viewer_reference.Find(ka))
		{
			BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
			oc_viewer.m_Anonymous	= true;

		// Ссылка на анонимного:
			oc_viewer_reference.New();
			oc_viewer_reference.m_ViewerID		= oc_viewer.GetObjectID();
			oc_viewer_reference.m_IPAddress		= arg.ViewerIP;
			oc_viewer_reference.m_IPAddressHash = Hash;
			oc_viewer_reference.m_CacheTime		= CurrentTime;
		}
	// Если такой CRC найден, то проверим его уникальность:
		else
		{
		// Совпадает ли IP с заданным ?
			if (string(oc_viewer_reference.m_IPAddress) != arg.ViewerIP)
			{
			// Не совпадает - будем искать дальше ...
				bool bFound;
			
				do
				{
				// Перейдем на следующего анонимного зрителя с таким же CRC:
					bFound = oc_viewer_reference.GoNextSame(&ka);
				// Если IP совпадает с заданным, то это тот зритель,
				// которого мы ищем - откроем его, и на выход:
					if (bFound && (string(oc_viewer_reference.m_IPAddress) == arg.ViewerIP)) {
						BX_CHECK_AND_OPEN(oc_viewer, oc_viewer_reference.m_ViewerID, OBJ_CLASS_ID_Viewer);
						break;
					}
				}while (bFound);	// Пока есть ещё такие же значения CRC ...

			// Если так и не нашли зрителя с нужным IP, то придётся его создать:
				if (!bFound)
				{
					BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
					oc_viewer.m_Anonymous	= true;
				// Ссылка на анонимного:
					oc_viewer_reference.New();
					oc_viewer_reference.m_ViewerID		= oc_viewer.GetObjectID();
					oc_viewer_reference.m_IPAddress		= arg.ViewerIP;
					oc_viewer_reference.m_IPAddressHash = Hash;
					oc_viewer_reference.m_CacheTime		= CurrentTime;
				}
			}
		// Нашли ссылку с нужным IP, откроем зрителя:
			else
			{
				BX_CHECK_AND_OPEN(oc_viewer, oc_viewer_reference.m_ViewerID, OBJ_CLASS_ID_Viewer);
			}
			
		}
	}
//----------------------------------------------------------------------------[] 
// Cookie поддерживается:
	else
	{
	// Эритель ещё не зарегистрирован или убил у себя Cookie:
		if (arg.ViewerID == NA)	{
		// Создадим персональный объект для зрителя.
			BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
		}
	// Эритель зарегистрирован - откроем его контроллер:
		else	{
			oc_viewer.Open(arg.ViewerID);
		// Если зритель зарегистрирован как разделяемый, то сделаем ему персональный объект:
			if (bool(oc_viewer.m_Anonymous))
			{
			// Создадим персональный объект для зрителя.
				BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
			}
		}
	// Признак неразделяемого объекта:
		oc_viewer.m_Anonymous	= false;
	// Куки поддерживается - значит не анонимный:
		bAnonymousViewer			= false;
	}	

// Возвратим в cookie ID объекта:
	SERVER_DEBUG_ASSERT_RETURN(	// параноидальный ассерт.
		oc_viewer.IsValid(),
		"BX_GetViewer(): Invalid viewer --- wrong control path.",
		BX_SYSTEM_ERROR);
	arg.ViewerID = oc_viewer.GetObjectID();
	
	return BX_OK;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` UpdateViewerInfo                                                          []                
//                                                                            []
//----------------------------------------------------------------------------[] 
void
UpdateViewerInfo( OC_Viewer&			oc_viewer,		// IN:	Открытый и установленный контроллер зрителя.
						BX_Counter_Args&	arg,				// IN/OUT:	ID сайта / Visits, LastVisit
						time_t				CurrentTime,	// IN:	Текущее время (GMT).
						bool&					bNewVisitor,	// OUT:	Является ли посетитель новым для сайта.
						bool&					bHost,			// OUT:	Является ли посетитель хостом.
						time_t&				ReturnTime)		// OUT:	Время прошедшее с последнего хоста на этом сайте.
						
{
	int sitePos = -1;

	oc_viewer.m_IPAddress		= arg.ViewerIP;
	//oc_viewer.m_IP_Ind			= IP_2_ULONG(arg.ViewerIP);

	oc_viewer.m_LastVisitTime	= CurrentTime;
	
	if ((sitePos = oc_viewer.m_Site.Find(arg.SiteID, true)) == -1)
// Этот зритель пришёл на сайт в первый раз
	{
		sitePos = oc_viewer.m_Site.	InsertSorted(arg.SiteID);
		oc_viewer.m_Site_Hits.			Insert(sitePos, 0);
		oc_viewer.m_Site_Hosts.			Insert(sitePos, 1);
		oc_viewer.m_Site_LastHit.		Insert(sitePos, 0);
		oc_viewer.m_Site_LastHost.		Insert(sitePos, CurrentTime);
		oc_viewer.m_Site_Votings.		Insert(sitePos, 0);
		oc_viewer.m_Site_VoteDayNo.	Insert(sitePos, 100);

	// Установим признак нового посетителя и хоста:
		bNewVisitor = true;
		bHost			= true;
	}
	else
// Этот зритель уже был на этом сайте
	{
	// Сбросим признак нового посетителя:
		bNewVisitor = false;

	// Посчитаем хост ли это или не очень:
		if ((CurrentTime - time_t(oc_viewer.m_Site_LastHost[sitePos])) < SECS_IN_DAY) {
			bHost		= false;
		}
		else {
			bHost												= true;
			oc_viewer.m_Site_LastHost	[sitePos]	= CurrentTime;
			oc_viewer.m_Site_Hosts		[sitePos]	+= 1;
			oc_viewer.m_TotalHosts						+= 1;
		}
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Вернем время, прошедшее с последнего посещения:
	ReturnTime = CurrentTime - time_t(oc_viewer.m_Site_LastHit[sitePos]);

// Вернём старое время последнего посещения сайта:
	arg.LastVisitTime = (time_t)oc_viewer.m_Site_LastHit[sitePos];

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Инкрементируем счетчик хитов (т.к. эта функция вызывается после проверок
// на накрутку и проч., то это действиельно будет хитом):
	oc_viewer.m_Site_Hits	[sitePos] += 1;

// Установим новое время последнего посещения сайта:
	oc_viewer.m_Site_LastHit[sitePos] = CurrentTime;
	
// Вернем число хитов, сделанных этим посетителем на сайте:
	arg.Visits = oc_viewer.m_Site_Hits[sitePos];
		

// Viewer::Referrer
	oc_viewer.m_Referrer			= arg.ViewerHostName;

// Viewer::TZOffset
//	float		fDiff = float(arg.LocalTime - CurrentTime);
	long		fDiff = arg.LocalTime - CurrentTime;
	if ((fDiff >= 12*SECS_IN_DAY) || (fDiff <= (-12*SECS_IN_DAY))) {
		oc_viewer.m_TZOffset = -1;
	}
	else
	{
		oc_viewer.m_TZOffset			= fDiff > 0 ?
													(fDiff / 1800)*1800 :
													((-fDiff) / 1800)*(-1800) ;
//													int(floor(fDiff / 1800.0 + 0.5))*1800 :
//													int(ceil (fDiff / 1800.0 - 0.5))*1800 ;
	}

//----------------------------------------------------------------------------[]
	oc_viewer.m_UserAgent = 	arg.UserAgent;


// Параметры платформы/компьютера:
	// !!! if (bHost)
	{
		USER_AGENT	useragent = arg.UserAgent;
		string		sTmp;
		int			No = -1;
		int_arr		CR;

		CR = oc_viewer.m_CRA_Inquiry.GetCPtr();

		useragent.OperatingSystemVer(sTmp);
		if (	(sTmp.Len() > 0) &&
				((No = ViewerParamsToConcepts("Concept.Viewer.OS", sTmp)) != -1)) {
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}
		useragent.BrowserVer(sTmp);
		if (	(sTmp.Len() > 0) && 
				((No = ViewerParamsToConcepts("Concept.Viewer.Browser", sTmp)) != -1)) {
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}
		if (	(arg.Charset.Len() > 0) &&
				((No = ViewerParamsToConcepts("Concept.Viewer.Charset", arg.Charset)) != -1)) {
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}

		for (int i = 0; i < arg.Language.Size(); i++)
		{
			if (	(arg.Language[i].Len() > 0) && 
					((No = ViewerParamsToConcepts("Concept.Viewer.Language", arg.Language[i])) != -1)) {
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
			}
		}
		if ((arg.ScreenResolution.Len() > 0) && 
			((No = ViewerParamsToConcepts("Concept.Viewer.ScreenSize", arg.ScreenResolution)) != -1)){
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}
		if ((arg.ColorDepth.Len() > 0) && 
			((No = ViewerParamsToConcepts("Concept.Viewer.Colors", arg.ColorDepth)) != -1)) {
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}
		if ((arg.JavaScriptVersion.Len() > 0) && 
			((No = ViewerParamsToConcepts("Concept.Viewer.JavaScriptVersion", arg.JavaScriptVersion)) != -1))	{
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}
		if ((arg.JavaEnabled.Len() > 0) && 
			((No = ViewerParamsToConcepts("Concept.Viewer.Java", arg.JavaEnabled)) != -1))	{
					ConceptRate_Increase(No, CONCEPT_NORM_BASE, CR);
		}

		oc_viewer.m_CRA_Inquiry = CR;

	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Заполним CRA_Inquiry - регионы
		RegisterIP(arg.ViewerIP, oc_viewer, bHost, bNewVisitor, CurrentTime);
	// Нормализуем и положим в CRN_Inquiry
		NormalizePackedArrInplace(CR);
		oc_viewer.m_CRN_Inquiry = CR;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Viewer::ReloadNum, AveReloadTime -- интенсивности релоадов:
	if (ReturnTime > oc_reg.m_ReloadTimeThreshold)
	{
	// Вычислим cумманое время релоадов:
		oc_viewer.m_AveReloadTime	= oc_viewer.m_ReloadNum*oc_viewer.m_AveReloadTime+(float)ReturnTime;
		oc_viewer.m_ReloadNum		+= 1.0;
	// Поделим на число релоадов для получения среднего:
		if (oc_viewer.m_ReloadNum > 0.0F) {
			oc_viewer.m_AveReloadTime /= oc_viewer.m_ReloadNum;
		}
		else	{
			SERVER_DEBUG_ERROR_1 ("UpdateViewerInfo(): Zero or Negative Viewer::ReloadNum=%f", (float)oc_viewer.m_ReloadNum );
		}
	// Скорректируем статистику интенсивностей релоадов в реестре:
		if (oc_reg.m_ReloadDistribution.Size() != 100) {
			oc_reg.m_ReloadDistribution.Alloc(100, 0);
		}
		if (oc_viewer.m_AveReloadTime > 0.0F)
		{
			int Index = (int)(float(oc_reg.m_ReloadTimeThreshold) / oc_viewer.m_AveReloadTime * 100.0);
			if ((Index > 99) || (Index < 0)) {
				SERVER_DEBUG_ERROR_1 ("UpdateViewerInfo(): Incorrect index for Registry::ReloadDistribution = %d", Index);
			}
			else	{
				oc_reg.m_ReloadDistribution[Index] += 1;
			}
		}
		
	} // end if (ReturnTime >...

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/