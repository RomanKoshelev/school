/*
____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'BX'													[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  BX_Stats.cpp															[]
[] Date: 			  29.06.99																[]
[] Author:			  Alex Vershinin														[]
[] Description:	  �������������� �������											[]
[] Last Modified:																				[]
[]_________________________________________________________________________[]
*/


#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Stats
#define USES_BX_Utils
#define USES_BX_Macros
#define USES_BX_TimeStats
#define USES_BX_Concept
#define USES_BX_Admin

//#define USES_OBServer_Interface_h

#define USES_URL_h
//#define USES_OC_VBN
#define USES_OC_User
//#define USES_OC_Banner
#define USES_OC_Site
//#define USES_OC_SiteProfile
//#define USES_OC_Language
//#define USES_OC_Concept
#define USES_OC_ShowEvent
#define USES_OC_Viewer
#define USES_OC_Referrer
//#define USES_OC_SuspiciousInfo
#define USES_OC_DailyReferrerStats

#include "BX.h"



#define	TIME_TO_UPDATE_SITE_COUNTERS		(3*SECS_IN_MIN)
#define	SITE_NUMBER_TO_UPDATE				10
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_UpdateLastCounters                                                []                          
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Site_UpdateLastCounters (time_t curTime)
{
	OC_Site	oc_site;
	oc_site.SetIndex_LastUpdateTime();

	int		i;

	BX_TimeStats_Args	time_stats_args;
	time_stats_args.timer = curTime;
	BX_TimeStats_CreateArgs(time_stats_args);

	OC_ShowEvent	oc_show_event;
	oc_show_event.SetIndex_SiteID_ViewerID();

#if TIME_TO_UPDATE_SITE_COUNTERS <= MAX_EVENT_STORAGE_TIME
	key_arr	ka;
#endif

	for (oc_site.GoFirst(), i=0; oc_site.IsValid() && i<SITE_NUMBER_TO_UPDATE; oc_site.GoNext(), i++)
	{
		if (curTime - oc_site.m_LastUpdateTime < TIME_TO_UPDATE_SITE_COUNTERS) {
			return BX_OK;
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -]
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Loads);
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Hits);
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Hosts);
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Visitors);
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Shows);
		UPDATE_SITE_COUNTER_W_LASTSYNC		(Clicks);

		UPDATE_SITE_COUNTER_W_LASTSYNC		(AnonymousHits);
		oc_site.m_Total_AnonymousHits_Prc	= GET_PERCENT(oc_site.m_Total_AnonymousHits,	oc_site.m_Total_Hits);
		oc_site.m_LM_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LM_AnonymousHits,		oc_site.m_LM_Hits);	
		oc_site.m_LW_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LW_AnonymousHits,		oc_site.m_LW_Hits);	
		oc_site.m_LD_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LD_AnonymousHits,		oc_site.m_LD_Hits);	
		oc_site.m_LH_AnonymousHits_Prc		= GET_PERCENT(oc_site.m_LH_AnonymousHits,		oc_site.m_LH_Hits);	

		UPDATE_SESSION_STUFF;

		time_stats_args.Increment				= 0;
		CHANGE_SUSPICIOUS;
	
	// ���������� VisitorsOnline
#if TIME_TO_UPDATE_SITE_COUNTERS <= MAX_EVENT_STORAGE_TIME
		ka.Init();
		ka += oc_site.GetObjectID();
		oc_site.m_OnlineVisitors = oc_show_event.GetIndexUniqueNum(ka);
#else
		oc_site.m_OnlineVisitors = 0;
#endif

	// ����� � ��������� ��� �� ������� �� ���� ����.
		oc_site.m_LastUpdateTime = curTime;
	}
//----------------------------------------------------------------------------[]

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteStats_AudienceIntersect                                            []                              
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_SiteStats_AudienceIntersect(BX_SiteStats_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID)) {
		STATS_RETURN(Stats_InvalidObjectID);
	}

	OC_Site	oc_site;
	oc_site.Open(arg.objID);

	arg.Name				= oc_site.m_Name;
	arg.Description	= oc_site.m_Description;
	arg.CreationTime	= oc_site.m_CreationTime;
	arg.URL				= oc_site.m_URL;

	if (oc_site.m_ShowAudience == false) {
		STATS_RETURN(Stats_StatsOff);
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// �������� �������:
	if (string(oc_site.m_RateStatsViewPassword).Len() > 0)
	{
		if (!CheckAdminPassword(arg.OwnerPassword))
		{
			if (string(oc_site.m_RateStatsViewPassword) != arg.StatsPassword)
			{
				OC_User	oc_user;
				BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

				if (string(oc_user.m_Password) != arg.OwnerPassword)	{
					STATS_RETURN(Stats_BadPassword);	// �� BX_Stats.h
				}
			}
		}
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	if (arg.FirstPos < 0)							arg.FirstPos	= 0;
	if (arg.LastPos < arg.FirstPos)				arg.LastPos		= arg.FirstPos + 20;

	//!!! ��� ��� ���� ������� �������� �� Site::ShowAudience
//----------------------------------------------------------------------------[]
// ����������: �� Audience_Viewers ��� �� Audience_Hosts:
	identifier_arr	SiteID;
	int_arr			Viewers;
	int_arr			Hosts;
	int				i;
	int				Pos;
	int				nSites = oc_site.m_Audience_SiteID.Size();
	bool				bSortByHosts;

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	if (arg.SortOrder == "Hosts")	{
		bSortByHosts = true;
	}
	else	{
		bSortByHosts = false;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	for (i = 0; i < nSites; i++)
	{
		if (!OC_Exist(OBJ_CLASS_ID_Site, oc_site.m_Audience_SiteID[i]))
		{
			SERVER_DEBUG_ERROR_1 ("BX_SiteStats_AudienceIntersect(): Deleted invalid site id #%lu.", (unsigned long)oc_site.m_Audience_SiteID[i]);

			oc_site.m_Audience_SiteID.	Del(i);
			oc_site.m_Audience_Hosts.	Del(i);
			oc_site.m_Audience_Viewers.Del(i);
			i--;
			nSites--;
			continue;
		}

		if (bSortByHosts)
		{
			Pos = Hosts.InsertSorted(oc_site.m_Audience_Hosts[i]);
			Viewers.	Insert(Pos, oc_site.m_Audience_Viewers[i]);
		}
		else
		{
			Pos = Viewers.InsertSorted(oc_site.m_Audience_Viewers[i]);
			Hosts.	Insert(Pos, oc_site.m_Audience_Hosts[i]);
		}

		SiteID.	Insert(Pos, oc_site.m_Audience_SiteID[i]);
	}
//----------------------------------------------------------------------------[]
// ������� ����: ����� � �������
	arg.TotalObjects = 0;
	arg.RawTable.Delete();

	OC_Site		oc_othersite;

	/* ������:
		ID
		URL
		Name
		Description
		Visitors
		Hosts
		StatsAllowed
		OnlineVisitors
		Total_Votes_Ave
		Total_Visitors
		LM_Visitors
		LW_Visitors
		LD_Visitors
		LH_Visitors
		Total_Hosts
		LM_Hosts
		LW_Hosts
		LD_Hosts
		LH_Hosts
		Total_Hits
		LM_Hits
		LW_Hits
		LD_Hits
		LH_Hits
	*/ 
	string	Str;
	bool		bStatsAllowed;
	time_t	CurTime = time_0;
	int		PlaceCount = 0;

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	for (i = nSites-1; i >=0 ; i--)
	{
		oc_othersite.Open(SiteID[i]);
		if ((oc_othersite.m_ShowAudience == false)
			&& (CurTime - oc_othersite.m_ShowAudienceOffTime > 5*SECS_IN_MIN)) {
			continue;
		}
		if (PlaceCount < arg.FirstPos) {
			PlaceCount++;
			continue;
		}
		else if (PlaceCount > arg.LastPos)		{
			break;
		}

		PlaceCount++;
		arg.TotalObjects++;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	//	ID
		Str.Format("%lu", SiteID[i]);
		arg.RawTable.Add(Str);	
	//	URL
		arg.RawTable.Add(oc_othersite.m_URL);	
	//	Name
		arg.RawTable.Add(oc_othersite.m_Name);	
	//	Description
		arg.RawTable.Add(oc_othersite.m_Description);	
	//	Visitors
		Str.Format("%d", Viewers[i]);
		arg.RawTable.Add(Str);	
	//	Hosts
		Str.Format("%d", Hosts[i]);
		arg.RawTable.Add(Str);	
	//	StatsAllowed
		bStatsAllowed = string(oc_othersite.m_RateStatsViewPassword).Len() == 0;
      Str = bStatsAllowed ? "0":"1";
		arg.RawTable.Add(Str);	
	//	OnlineVisitors
		ADD_FIELD_IF_ALLOWED(OnlineVisitors);
	//	Total_Votes_Ave
		ADD_FIELD_IF_ALLOWED(Total_Votes_Ave);
	//	Total_Visitors
		ADD_FIELD_IF_ALLOWED(Total_Visitors);
	//	LM_Visitors
		ADD_FIELD_IF_ALLOWED(LM_Visitors);
	//	LW_Visitors
		ADD_FIELD_IF_ALLOWED(LW_Visitors);
	//	LD_Visitors
		ADD_FIELD_IF_ALLOWED(LD_Visitors);
	//	LH_Visitors
		ADD_FIELD_IF_ALLOWED(LH_Visitors);
	//	Total_Hosts
		ADD_FIELD_IF_ALLOWED(Total_Hosts);
	//	LM_Hosts
		ADD_FIELD_IF_ALLOWED(LM_Hosts);
	//	LW_Hosts
		ADD_FIELD_IF_ALLOWED(LW_Hosts);
	//	LD_Hosts
		ADD_FIELD_IF_ALLOWED(LD_Hosts);
	//	LH_Hosts
		ADD_FIELD_IF_ALLOWED(LH_Hosts);
	//	Total_Hits
		ADD_FIELD_IF_ALLOWED(Total_Hits);
	//	LM_Hits
		ADD_FIELD_IF_ALLOWED(LM_Hits);
	//	LW_Hits
		ADD_FIELD_IF_ALLOWED(LW_Hits);
	//	LD_Hits
		ADD_FIELD_IF_ALLOWED(LD_Hits);
	//	LH_Hits
		ADD_FIELD_IF_ALLOWED(LH_Hits);

	}

	STATS_RETURN(Stats_Okay);
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteStats_WhatsNew                                                     []                     
[]                                                                            []
[]____________________________________________________________________________*/
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
#define	PACK_FIELD(FieldName)															\
	Str.Format("%d", (int)oc_site.m_##FieldName);									\
	arg.RawVector.Add(Str)
//* * * * * * * * * * * * * * * * * * * * * * * * * * *]

BX_RESULT
BX_SiteStats_WhatsNew(BX_SiteStats_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID)) {
		STATS_RETURN(Stats_InvalidObjectID);
	}

	OC_Site	oc_site;
	oc_site.Open(arg.objID);

	arg.Name				= oc_site.m_Name;
	arg.Description	= oc_site.m_Description;
	arg.CreationTime	= oc_site.m_CreationTime;
	arg.URL				= oc_site.m_URL;

/*	if (oc_site.m_ShowAudience == false) {
		STATS_RETURN(Stats_StatsOff);
	} */
// �������� �������:
	if (string(oc_site.m_RateStatsViewPassword).Len() > 0)
	{
		if (!CheckAdminPassword(arg.OwnerPassword))
		{
			if (string(oc_site.m_RateStatsViewPassword) != arg.StatsPassword)
			{
				OC_User	oc_user;
				BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

				if (string(oc_user.m_Password) != arg.OwnerPassword)	{
					STATS_RETURN(Stats_BadPassword);
				}
			}
		}
	}
//----------------------------------------------------------------------------[]
	arg.RawVector.Delete();

	arg.TotalObjects = 0;
	arg.RawTable.Delete();

	string	Str;
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Last-��������:
	PACK_FIELD(OnlineVisitors);
	PACK_FIELD(LM_Visitors);
	PACK_FIELD(LW_Visitors);
	PACK_FIELD(LD_Visitors);
	PACK_FIELD(LH_Visitors);
	PACK_FIELD(LM_Hosts);
	PACK_FIELD(LW_Hosts);
	PACK_FIELD(LD_Hosts);
	PACK_FIELD(LH_Hosts);
	PACK_FIELD(LM_Hits);
	PACK_FIELD(LW_Hits);
	PACK_FIELD(LD_Hits);
	PACK_FIELD(LH_Hits);
	PACK_FIELD(LM_SuspiciousHits_Prc);
	PACK_FIELD(LW_SuspiciousHits_Prc);
	PACK_FIELD(LD_SuspiciousHits_Prc);
	PACK_FIELD(LH_SuspiciousHits_Prc);
	PACK_FIELD(LM_AveSessionTime);
	PACK_FIELD(LW_AveSessionTime);
	PACK_FIELD(LD_AveSessionTime);
	PACK_FIELD(LH_AveSessionTime);
//----------------------------------------------------------------------------[]
// �������

	OC_Viewer		oc_viewer;
	OC_Referrer		oc_referrer;

	arg.TotalObjects = 0;

	int				nPos;
	int				i;

	int_arr			IDs;
	CPtr<time_t>	Times;
	identifier_arr	Refs;

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// �������� ��������������� �������:
	for (i = 0; i < oc_site.m_RecentVisitor.Size(); i++)
	{
		identifier	ViewerID			= oc_site.m_RecentVisitor[i];
		if (!OC_Exist(OBJ_CLASS_ID_Viewer, ViewerID)) {
			continue;
		}

		nPos = Times.InsertSorted(oc_site.m_RecentTimeStamp[i]);
		IDs.Insert(nPos, ViewerID);
		Refs.Insert(nPos, oc_site.m_RecentReferrer[i]);

		arg.TotalObjects++;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// �������� � �������
	for (i = 0; i < IDs.Size(); i++)
	{
		oc_viewer.Open(IDs[i]);
// Time
		Str.Format("%li", Times[i]);
		arg.RawTable.Add(Str);
//	ID
		Str.Format("%lu", IDs[i]);
		arg.RawTable.Add(Str);
// Anonymous
		Str.Format("%s", oc_viewer.m_Anonymous == true ? "1":"0");
		arg.RawTable.Add(Str);
//	IPAddress
		Str.Format("%s", string(oc_viewer.m_IPAddress).c_str());
		arg.RawTable.Add(Str);
//	Referrer - ��� ���� �������
		Str.Format("%s", string(oc_viewer.m_Referrer).c_str());
		arg.RawTable.Add(Str);
// UserAgent
		Str.Format("%s", string(oc_viewer.m_UserAgent).c_str());
		arg.RawTable.Add(Str);
//	RecentReferrer - ��� ������ ������ �������
		if (OC_Exist(OBJ_CLASS_ID_Referrer, Refs[i]))
		{
			oc_referrer.Open(Refs[i]);
			Str.Format("%s", string(oc_referrer.m_Referrer).c_str());
		}
		else Str.Format("NA");
		arg.RawTable.Add(Str);
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	STATS_RETURN(Stats_Okay);
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteStats_Referrer                                                     []                     
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_SiteStats_Referrer(BX_SiteStats_Args& arg)
{
//	In:	Mode			= "Last","All","Daily"
//			SortOrder	= �����: ��������/������ ("Page"/"Domain")
//			FirstPos		= 
//			LastPos		= ��������� �� �������, ��������� �� ��������� !
//			StartDate	= ���� ������� ��� ����, �� ����� �� ����������.
//			EndDate		= 
//	Out:	RawTable			- �������/�������
//			TotalObjects	- ����� ��������� � ����� (��� ���������)
//----------------------------------------------------------------------------[]
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID)) {
		STATS_RETURN(Stats_InvalidObjectID);
	}

	OC_Site	oc_site;
	oc_site.Open(arg.objID);

	arg.Name				= oc_site.m_Name;
	arg.Description	= oc_site.m_Description;
	arg.CreationTime	= oc_site.m_CreationTime;
	arg.URL				= oc_site.m_URL;

// �������� �������:
	if (string(oc_site.m_RateStatsViewPassword).Len() > 0)
	{
		if (!CheckAdminPassword(arg.OwnerPassword))
		{
			if (string(oc_site.m_RateStatsViewPassword) != arg.StatsPassword)
			{
				OC_User	oc_user;
				BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

				if (string(oc_user.m_Password) != arg.OwnerPassword)	{
					STATS_RETURN(Stats_BadPassword);
				}
			}
		}
	}
//----------------------------------------------------------------------------[]
	int		i;
	int		nPos;
	string	Str;
	HTTP_URL	URL;
	bool		bDomainSort = (arg.SortOrder == "Domain");
	OC_Referrer		oc_referrer;


	arg.RawTable.Delete();
	arg.TotalObjects = 0;


//----------------------------------------------------------------------------[]
	if (arg.Mode == "All")
	{
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// ������ ��� ��������:
		if (arg.FirstPos < 0)					arg.FirstPos	= 0;
		if (arg.LastPos <= arg.FirstPos)		arg.LastPos		= arg.FirstPos + 20;
		if (arg.LastPos >= oc_site.m_ReferrerCount.Size()) {
			STATS_RETURN(Stats_Okay);
		}
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		int_arr				CountArr;
		string_arr			URLArr;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// ����������� �������� �� ���������� �����:
		for (i = 0; i < oc_site.m_ReferrerCount.Size(); i++)
		{	
			if (!OC_Exist(OBJ_CLASS_ID_Referrer, oc_site.m_Referrer[i])) {
				continue;
			}
		// ������� � ��������� ���������:
			oc_referrer.Open(oc_site.m_Referrer[i]);
			Str = oc_referrer.m_Referrer;
			URL.Parse(Str.c_str());

		// �� �������: 
			if (bDomainSort)	
			{	
				URL.Domain(Str);

			// �������� ������� ��� ��������� �������:
				if ((nPos = URLArr.Find(Str)) == -1)
				{
					nPos = CountArr.InsertSorted(oc_site.m_ReferrerCount[i]);
					URLArr.Insert(nPos, Str);
				}
				else	{
					CountArr[nPos] += oc_site.m_ReferrerCount[i];
				}
			}
		// �����������: 
			else
			{	
				URL.DomainPathFileExt(Str);
				nPos = CountArr.InsertSorted(oc_site.m_ReferrerCount[i]);
				URLArr.Insert(nPos, Str);
			}
		} // end for

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// �����:
		for (i = arg.FirstPos; i < arg.LastPos; i++)
		{
			nPos = URLArr.Size() - 1 - i;		// ������� � ��������������� �������.
			if (nPos < 0)	break;
		// �������� �����:
			arg.RawTable.Add(URLArr[nPos]);
		// �������� �������:
			Str.Format("%d", CountArr[nPos]);
			arg.RawTable.Add(URLArr[nPos]);
		}

		arg.TotalObjects = URLArr.Size();
	}
//----------------------------------------------------------------------------[]
	else if (arg.Mode == "Daily")
	{
	// ������ ��� ��������:
		nPos = oc_site.m_DailyReferrerTimeStamp.Size();

		if (nPos == 0)	{
			STATS_RETURN(Stats_Okay);
		}
/*		if (arg.StartDate < oc_site.m_DailyReferrerTimeStamp[0]) {
			arg.StartDate = oc_site.m_DailyReferrerTimeStamp[0];
		}
		if (arg.EndDate > oc_site.m_DailyReferrerTimeStamp[nPos-1]) {
			arg.EndDate = oc_site.m_DailyReferrerTimeStamp[nPos-1];
		} */
		if (arg.StartDate < oc_site.m_DailyReferrerTimeStamp[0]) {
			arg.StartDate = oc_site.m_DailyReferrerTimeStamp[0];
		}
		if (arg.StartDate > oc_site.m_DailyReferrerTimeStamp[nPos-1]) {
			arg.StartDate = oc_site.m_DailyReferrerTimeStamp[nPos-1];
		}
		
	// ��������� ������ ������� ���:
		nPos = (arg.StartDate - oc_site.m_DailyReferrerTimeStamp[0]) / SECS_IN_DAY;
		if ((nPos < 0) || (nPos >= oc_site.m_DailyReferrerTimeStamp.Size()))
		{
			SERVER_DEBUG_ERROR ("BX_SiteStats_Referrer(): Site::DailyReferrerTimeStamp index not in range. Aborted.");
			STATS_RETURN(Stats_SystemError);
		}
		if (oc_site.m_DailyReferrerStats[nPos] == NA)
		{
			STATS_RETURN(Stats_Okay);	// �� ���� ���� ��� ����������.
		}
	// ������� ������ ������ ������� ����������:
		if (!OC_Exist(OBJ_CLASS_ID_DailyReferrerStats, oc_site.m_DailyReferrerStats[nPos]))
		{
			SERVER_DEBUG_ERROR ("BX_SiteStats_Referrer(): Invalid Site::DailyReferrerStats[nPos]. Aborted.");
			STATS_RETURN(Stats_SystemError);
		}

		OC_DailyReferrerStats	oc_daily_ref_stats;
		oc_daily_ref_stats.Open(oc_site.m_DailyReferrerStats[nPos]);
	// ������������� �� �����:
		int_arr			CountArr;
		identifier_arr	RefArr;

		for (i = 0; i < oc_daily_ref_stats.m_Referrer.Size(); i++)
		{
			if (OC_Exist(OBJ_CLASS_ID_Referrer, oc_daily_ref_stats.m_Referrer[i]))
			{
				nPos = CountArr.InsertSorted(oc_daily_ref_stats.m_Count[i]);
				RefArr.Insert(nPos, oc_daily_ref_stats.m_Referrer[i]);
			}
		}

	// �����:				
		for (i = RefArr.Size()-1; i >= 0 ; i--)
		{
		// ������� � ��������� ���������:
			oc_referrer.Open(RefArr[i]);
			Str = oc_referrer.m_Referrer;
			URL.Parse(Str);
		// �������� URL:
			if (bDomainSort) {
				URL.Domain(Str);
			}
			else	{
				URL.DomainPathFileExt(Str);
			}
			arg.RawTable.Add(Str);
		// �������� �������:
			Str.Format("%d", CountArr[i]);
			arg.RawTable.Add(Str);

			arg.TotalObjects++;
		}
		
	}
//----------------------------------------------------------------------------[]
	else
	{
		arg.Mode = string("Last");

		int_arr			TimeArr;
		identifier_arr	RefArr;
	// ������������� �������� �� �������:
		for (i = 0; i < oc_site.m_RecentTimeStamp.Size(); i++)
		{
			if (OC_Exist(OBJ_CLASS_ID_Referrer, oc_site.m_RecentReferrer[i]))
			{
				nPos = TimeArr.InsertSorted(oc_site.m_RecentTimeStamp[i]);
				RefArr.Insert(nPos, oc_site.m_RecentReferrer[i]);
			}
		}
	// �����:				
		for (i = RefArr.Size()-1; i >= 0 ; i--)
		{
		// ������� � ��������� ���������:
			oc_referrer.Open(RefArr[i]);
			Str = oc_referrer.m_Referrer;
			URL.Parse(Str);
		// �������� �����:
			Str.Format("%d", TimeArr[i]);
			arg.RawTable.Add(Str);
		// �������� URL:
			if (bDomainSort) {
				URL.Domain(Str);
			}
			else	{
				URL.DomainPathFileExt(Str);
			}

			arg.RawTable.Add(Str);

			arg.TotalObjects++;
		}

	// ������� ���� ��� ��������� (�� ��������):
		if (oc_site.m_DailyReferrerTimeStamp.Size() > 0)
		{
			arg.StartDate	= oc_site.m_DailyReferrerTimeStamp[0];
			arg.EndDate		= oc_site.m_DailyReferrerTimeStamp[oc_site.m_DailyReferrerTimeStamp.Size()-1];
		}
		else {
			arg.StartDate = arg.EndDate = -1;
		}

	} // end else (Mode==)

//----------------------------------------------------------------------------[]
	STATS_RETURN(Stats_Okay);
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
