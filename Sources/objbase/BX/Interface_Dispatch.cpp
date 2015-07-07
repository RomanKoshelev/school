/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Dispatch.cpp                                    []
[] Date:            NA                                                        []
[] Author:          Alex Vershinin, Roman V. Koshelev                         []
[] Description:     ��������� ��� ������ �������� ���������� �������.         []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________*/

#define	USES_OBServer_Interface_h
#define	USES_BX_Interface
#include	"BX.h"


//______________________________________________________________________________
//                                                                            []
// ��������� ������� ���������� ������                                        []
//                                                                            []
void OBServer_Interface (const char* OBServer_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)
{
// ����� ������������������ �������
   FNC_BEGIN;
   {
   // Counter
      FNC        (BX_Counter_GetData, "���������� �������������� ���������� ��� ������ ��������.");
			FNC_IN  (BX_Counter, JustGetData, "�������� �������� ����� �������� ������ ��� �� �����������. �� ���� ����� ������ ID �����.");
			FNC_IN  (BX_Counter, SiteID, "{class:Site}ID �����.");
			FNC_IN  (BX_Counter, Alias, "������� ID �����.");
			FNC_IN  (BX_Counter, CounterType, "��� �������� (�� ��������� - ���, ��� ���������� � �����).");
			FNC_IN  (BX_Counter, PageNo, "����� �������� �����.");
			FNC_IN  (BX_Counter, CookieSupported, "�������������� �� Cookie.");
			FNC_IN  (BX_Counter, ViewerID, "{class:Viewer}Cookie (ID) �������, ���� Cookie �������������� � ����������, ��� NA � ��������� ������.");
			FNC_IN  (BX_Counter, LocalTime, "������� ����� ����������.");
			FNC_IN  (BX_Counter, ViewerIP, "IP �������.");
			FNC_IN  (BX_Counter, SiteURL, "URL �����, �� ������� ��������� ������� (HTTP_REFERER).");
			FNC_IN  (BX_Counter, Referrer, "���������� URL (do�ument.referrer �� Javascript'�.");
			FNC_IN  (BX_Counter, ViewerHostName, "���� ����������.");
			FNC_IN  (BX_Counter, UserAgent, "UserAgent ����������.");
			FNC_IN  (BX_Counter, ScreenResolution, "���������� ������.");
			FNC_IN  (BX_Counter, ColorDepth, "������� �����.");
			FNC_IN  (BX_Counter, JavaEnabled, "�������� �� ���-������.");
			FNC_IN  (BX_Counter, JavaScriptVersion, "������ ����������.");
			FNC_IN  (BX_Counter, Charset, "CHARSET");
			FNC_IN  (BX_Counter, Language, "HTTP_ACCEPT_LANGUAGE");
			FNC_OUT (BX_Counter, ViewerID, "Cookie (ID) �������, ������� ����� ����������.");
			FNC_OUT (BX_Counter, ExitCode, "��� ��������: -1 - ����������, 0 - ��� ���������, 1 - �������� (<5 ���), 2 - ������������ � ��������, 3 - ignored IP, 4 - ���� �������� �����������, 5 - ��� ���������, �� ������� �������������� Cookie.");
			FNC_OUT (BX_Counter, Visits, "���������� �����, ��������� �������� �� ���� �����.");
			FNC_OUT (BX_Counter, LastVisitTime, "����� ���������� ��������� ������ �������� ����� �����.");
			FNC_OUT (BX_Counter, OnlineVisitors, "����� ���������� ����������� �� ��������� 3 ������.");
			FNC_OUT (BX_Counter, Total_Loads, "����� �������� �����.");
			FNC_OUT (BX_Counter, Total_Visitors, "����� ����� ����������� �����.");
			FNC_OUT (BX_Counter, Total_VisitorReturns, "����� ��������� �� ����.");
			FNC_OUT (BX_Counter, Total_AnonymousVisitors, "����� ��������� ����������� �����.");
			FNC_OUT (BX_Counter, Total_AnonymousVisitors_Prc, "������� ��������� ����������� ����� �� ������ ����� ����� ����������� �����.");
			FNC_OUT (BX_Counter, Total_VisitorExperience, "����� ���������� ���������� ������ ����� ������� ������� �����.");
			FNC_OUT (BX_Counter, Ave_VisitorExperience, "������� ���������� ���������� ������ ��� ����� �� ������ �����.");
			FNC_OUT (BX_Counter, Total_Hosts, "����� �������� ����� �� �����, ������� �����.");
			FNC_OUT (BX_Counter, Total_Hits, "����� (�� ��������������) ����� �����.");
			FNC_OUT (BX_Counter, Total_AnonymousHits, "����� ��������� ����������� �����.");
			FNC_OUT (BX_Counter, Total_AnonymousHits_Prc, "������� ��������� ����������� ����� �� ������ ����� ����� ����������� �����.");
			FNC_OUT (BX_Counter, Total_SuspiciousHits_Prc, "������� �������������� ����� ����� �� ������ ������ ����� ����� �� ����� (������� ��������������).");
			FNC_OUT (BX_Counter, Total_SessionTime, "��������� ����������������� ������ �� �����.");
			FNC_OUT (BX_Counter, Total_Shows, "����� ������� �������� �� �����.");
			FNC_OUT (BX_Counter, Total_Clicks, "����� ������� �������� �� �����.");
			FNC_OUT (BX_Counter, Total_CTR_Prc, "CTR �������� �� ���� ����� �� �� �����.");
			FNC_OUT (BX_Counter, Total_Votes, "����� ��������������� �� ����.");
			FNC_OUT (BX_Counter, Total_Votes_Sum, "��������� ������ ����������� �� ����.");
			FNC_OUT (BX_Counter, Total_Votes_Ave, "������� ������ ����������� �� ����.");
			FNC_OUT (BX_Counter, LM_Loads, "����� �������� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_Visitors, "����� ����������� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_VisitorReturns, "��������� �� ���� � ������� ������.");
			FNC_OUT (BX_Counter, LM_VisitorReturns_Prc, "������� �������������� � ������� ������ ����������� ����� �� ������ ����� ����������� ����� � ������� ������.");
			FNC_OUT (BX_Counter, LM_Hosts, "������ �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_Hits, "����� (�� ��������������) �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_AnonymousHits, "��������� ����� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_AnonymousHits_Prc, "������� ��������� ����� ����� �� ��������� ����� �� ������ ����� (�� ��������������) ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_SuspiciousHits_Prc, "������� �������������� ����� ����� �� ��������� ����� �� ������ ����� ����� �� ��������� ����� (������� ��������������).");
			FNC_OUT (BX_Counter, LM_SessionTime, "��������� ����������������� ������ �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_Shows, "������� �������� �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_Clicks, "������� �������� �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LM_CTR_Prc, "CTR �� ��������� �����.");
			FNC_OUT (BX_Counter, LW_Loads, "����� �������� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_Visitors, "����� ����������� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_VisitorReturns, "��������� �� ���� � ������� ������.");
			FNC_OUT (BX_Counter, LW_VisitorReturns_Prc, "������� �������������� � ������� ������ ����������� ����� �� ������ ����� ����������� ����� � ������� ������.");
			FNC_OUT (BX_Counter, LW_Hosts, "������ �� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_Hits, "����� (�� ��������������) �� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_AnonymousHits, "��������� ����� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_AnonymousHits_Prc, "������� ��������� ����� ����� �� ��������� ������ �� ������ ����� (�� ��������������) ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_SuspiciousHits_Prc, "������� �������������� ����� ����� �� ��������� ������ �� ������ ����� ����� �� ��������� ������ (������� ��������������).");
			FNC_OUT (BX_Counter, LW_SessionTime, "��������� ����������������� ������ �� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_Shows, "������� �������� �� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_Clicks, "������� �������� �� ����� �� ��������� ������.");
			FNC_OUT (BX_Counter, LW_CTR_Prc, "CTR �� ��������� ������.");
			FNC_OUT (BX_Counter, LD_Loads, "����� �������� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_Visitors, "����� ����������� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_VisitorReturns, "��������� �� ���� � ������� �����.");
			FNC_OUT (BX_Counter, LD_VisitorReturns_Prc, "������� �������������� � ������� ����� ����������� ����� �� ������ ����� ����������� ����� � ������� �����.");
			FNC_OUT (BX_Counter, LD_Hosts, "������ �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_Hits, "����� (�� ��������������) �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_AnonymousHits, "��������� ����� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_AnonymousHits_Prc, "������� ��������� ����� ����� �� ��������� ����� �� ������ ����� (�� ��������������) ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_SuspiciousHits_Prc, "������� �������������� ����� ����� �� ��������� ����� �� ������ ����� ����� �� ��������� ����� (������� ��������������).");
			FNC_OUT (BX_Counter, LD_SessionTime, "��������� ����������������� ������ �� ����� �� ��������� ����.");
			FNC_OUT (BX_Counter, LD_Shows, "������� �������� �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_Clicks, "������� �������� �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LD_CTR_Prc, "CTR �� ��������� �����.");
			FNC_OUT (BX_Counter, LH_Loads, "����� �������� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_Visitors, "����� ����������� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_VisitorReturns, "��������� �� ���� � ������� ����.");
			FNC_OUT (BX_Counter, LH_VisitorReturns_Prc, "������� �������������� � ������� ���� ����������� ����� �� ������ ����� ����������� ����� � ������� ����.");
			FNC_OUT (BX_Counter, LH_Hosts, "������ �� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_Hits, "����� (�� ��������������) �� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_AnonymousHits, "��������� ����� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_AnonymousHits_Prc, "������� ��������� ����� ����� �� ��������� ��� �� ������ ����� (�� ��������������) ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_SuspiciousHits_Prc, "������� �������������� ����� ����� �� ��������� ��� �� ������ ����� ����� �� ��������� ��� (������� ��������������).");
			FNC_OUT (BX_Counter, LH_SessionTime, "��������� ����������������� ������ �� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_Shows, "������� �������� �� ����� �� ��������� �����.");
			FNC_OUT (BX_Counter, LH_Clicks, "������� �������� �� ����� �� ��������� ���.");
			FNC_OUT (BX_Counter, LH_CTR_Prc, "CTR �� ��������� �����.");

   // TimeStats
      FNC        (BX_TimeStats_GetStatInfo, "��������� ��������� ��� ������ ������� �������� ����� �� ��������� 24 ����.");
			FNC_IN  (BX_TimeStats, Site, "������������� �����.");
			FNC_IN  (BX_TimeStats, StatsName, "�������� �������� (Visitors,Hosts,Shows,Clicks,Hits,AnonymousHits,SuspiciousHits).");
			FNC_OUT (BX_TimeStats, XLabel, "X-����������.");
			FNC_OUT (BX_TimeStats, YValue, "Y-����������.");
			FNC_OUT (BX_TimeStats, YMax, "������������ �������� Y-����������.");
			FNC_OUT (BX_TimeStats, YMin, "����������� �������� Y-����������.");
			FNC_OUT (BX_TimeStats, VisitorsOnline, "����� ����������� �� ��������� 3 ������.");

   // Admin
      FNC        (BX_Admin_GetObjectNum, "�������� ���-�� ����������� �������� � ���� ������.");
			FNC_OUT (BX_Admin, Result, "���������� �� ��������, ����������� ��������.");

   // Concept
      FNC        (BX_Concept_SetFilter, "���������� ������������� ���� ��������� ��� �������.");
			FNC_IN  (BX_Concept, ConceptType, "���� ���������, ���������� ���������� ����� ������������ �� ����� � �������.");
			FNC_OUT (BX_Concept, ConceptType, "���� ���������, ������� ������������� � ������.");
      FNC        (BX_Concept_GetFilter, "�������� ������������� ���� ��������� ��� �������.");
			FNC_OUT (BX_Concept, ConceptType, "���� ���������, ���������� ���������� ����� ������������ �� ����� � �������.");

   // SiteStats
      FNC        (BX_SiteStats_Referrer, "���������� ���������� � ���������.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}������������� �����.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "������ ��������� ����������.");
			FNC_IN  (BX_SiteStats, StatsPassword, "������ �� ������ � ����������.");
			FNC_IN  (BX_SiteStats, Mode, "����� ������.");
			FNC_IN  (BX_SiteStats, SortOrder, "������ ��������� URL: ('Domain','Page')");
			FNC_IN  (BX_SiteStats, StartDate, "��������� ����.");
			FNC_IN  (BX_SiteStats, EndDate, "�������� ����.");
			FNC_IN  (BX_SiteStats, FirstPos, "������� � ��������������� ������ ������� �������.");
			FNC_IN  (BX_SiteStats, LastPos, "������� � ��������������� ������ ���������� �������.");
			FNC_OUT (BX_SiteStats, Name, "�������� �����.");
			FNC_OUT (BX_SiteStats, Description, "�������� �����.");
			FNC_OUT (BX_SiteStats, CreationTime, "����� �������� ����� (�� ��������).");
			FNC_OUT (BX_SiteStats, URL, "URL �����.");
			FNC_OUT (BX_SiteStats, RawTable, "��������� ������ � ����������� �������������� �����������.");
			FNC_OUT (BX_SiteStats, TotalObjects, "���������� ����� � ������� RawTable.");
			FNC_OUT (BX_SiteStats, StartDate, "��������� ����.");
			FNC_OUT (BX_SiteStats, EndDate, "�������� ����.");
			FNC_OUT (BX_SiteStats, ExitCode, "��� ��������.");

   // Site
      FNC        (BX_Site_GetAliasByID, "�������� ������� ����� �� ID.");
			FNC_IN  (BX_Site, objID, "{class:Site}������������� �����.");
			FNC_OUT (BX_Site, Alias, "������� �����.");
      FNC        (BX_Site_GetIDByAlias, "�������� ID �� �������� �����.");
			FNC_IN  (BX_Site, Alias, "������� �����.");
			FNC_OUT (BX_Site, objID, "������������� ����� ��� NA ���� ��� ����� � ����� ���������.");

   // Admin
      FNC        (BX_Admin_SaveBXObjects, "���������� �������� �������� BX.");
			FNC_IN  (BX_Admin, Password, "������ ��������������.");
			FNC_OUT (BX_Admin, Result, "�������� ����������� ��������.");

   // Site
      FNC        (BX_Site_GetBriefInfo, "������� ���������� �� �����.");
			FNC_IN  (BX_Site, objID, "{class:Site}������������� �����.");
			FNC_OUT (BX_Site, Name, "�������� �����.");
			FNC_OUT (BX_Site, Description, "��������.");
			FNC_OUT (BX_Site, URL, "URL �����.");
			FNC_OUT (BX_Site, CreationTime, "����� �������� (�� ��������).");

   // TimeStats
      FNC        (BX_TimeStats_GetData, "��������� ������ �� ��������������� �������� �����.");
			FNC_IN  (BX_TimeStats, objID, "ID �������-��������� ��������.");
			FNC_IN  (BX_TimeStats, OwnerPassword, "������ ��������� ����������.");
			FNC_IN  (BX_TimeStats, StatsPassword, "������ �� ������ � ����������.");
			FNC_IN  (BX_TimeStats, Object, "�������� �������-��������� �������� (����. 'Site').");
			FNC_IN  (BX_TimeStats, Counter, "�������� �������� (����. 'Hits').");
			FNC_IN  (BX_TimeStats, Date_Start, "��������� ���� ��������� (���).");
			FNC_IN  (BX_TimeStats, Date_End, "�������� ���� ��������� (���).");
			FNC_IN  (BX_TimeStats, TZOffset, "�������� �������� ����� (���).");
			FNC_IN  (BX_TimeStats, TimeDescrete, "������������ (0-None,1-Hour,2-Day,3-Week,4-Month).");
			FNC_IN  (BX_TimeStats, TimeAggregate, "������������� (0-None,1-HourOfDay,2-DayOfWeek,3-DayOfMonth,4-MonthOfYear).");
			FNC_IN  (BX_TimeStats, WeekdayLong, "������������ ������� �������� ���� ������.");
			FNC_IN  (BX_TimeStats, MonthLong, "������������ ������� �������� �������.");
			FNC_OUT (BX_TimeStats, Data, "�������� �������.");
			FNC_OUT (BX_TimeStats, Labels, "����� �������� �������.");
			FNC_OUT (BX_TimeStats, ExitCode, "��� ��������.");

   // SiteStats
      FNC        (BX_SiteStats_WhatsNew, "���������� ���������� � ��������� �������� � ��������.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}������������� �����.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "������ ��������� ����������.");
			FNC_IN  (BX_SiteStats, StatsPassword, "������ �� ������ � ����������.");
			FNC_OUT (BX_SiteStats, Name, "�������� �����.");
			FNC_OUT (BX_SiteStats, Description, "�������� �����.");
			FNC_OUT (BX_SiteStats, CreationTime, "����� �������� ����� (�� ��������).");
			FNC_OUT (BX_SiteStats, URL, "URL �����.");
			FNC_OUT (BX_SiteStats, RawVector, "��������� ������ � ����������� �������������� �����������.");
			FNC_OUT (BX_SiteStats, RawTable, "��������� ������ � ����������� �������������� �����������.");
			FNC_OUT (BX_SiteStats, TotalObjects, "���������� ����� � ������� RawTable.");
			FNC_OUT (BX_SiteStats, ExitCode, "��� ��������.");

   // Site
      FNC        (BX_Site_GetStatsPassword, "�������� ������ �� ������ � ���������� �����.");
			FNC_IN  (BX_Site, objID, "{class:Site}������������� �����.");
			FNC_OUT (BX_Site, RateStatsViewPassword, "������ �� ������ � ���������� ������������ ��� ����� �����.");
      FNC        (BX_Site_CheckStatsPassword, "�������� ������ �� ������ � ���������� �����.");
			FNC_IN  (BX_Site, objID, "{class:Site}������������� �����.");
			FNC_IN  (BX_Site, OwnerPassword, "������ ��������� ����������.");
			FNC_IN  (BX_Site, StatsPassword, "������ �� ������ � ����������.");
			FNC_OUT (BX_Site, ExitCode, "True, ���� ���� �� ���� �� ������� �������� � ���������� �����.");
      FNC        (BX_Site_GetVBN, "��������� ID VBN �� ID �����.");
			FNC_IN  (BX_Site, objID, "{class:Site}������������� �����.");
			FNC_OUT (BX_Site, VBN, "ID ����������� �������.");

   // SiteStats
      FNC        (BX_SiteStats_AudienceIntersect, "���������� ����������, ���������� ����������� ��������� �����.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}������������� �����.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "������ ��������� ����������.");
			FNC_IN  (BX_SiteStats, StatsPassword, "������ �� ������ � ����������.");
			FNC_IN  (BX_SiteStats, SortOrder, "������� ���������� ('Hosts','Viewers').");
			FNC_IN  (BX_SiteStats, FirstPos, "������� � ��������������� ������ ������� �������.");
			FNC_IN  (BX_SiteStats, LastPos, "������� � ��������������� ������ ���������� �������.");
			FNC_OUT (BX_SiteStats, Name, "�������� �����.");
			FNC_OUT (BX_SiteStats, Description, "�������� �����.");
			FNC_OUT (BX_SiteStats, CreationTime, "����� �������� ����� (�� ��������).");
			FNC_OUT (BX_SiteStats, URL, "URL �����.");
			FNC_OUT (BX_SiteStats, RawTable, "��������� ������ � ����������� �������������� �����������.");
			FNC_OUT (BX_SiteStats, TotalObjects, "���������� ����� � ������� RawTable.");
			FNC_OUT (BX_SiteStats, ExitCode, "��� ��������.");

   // IPRecord
      FNC        (BX_IPRecord_New, "������� ����� �������� �������.");
			FNC_IN  (BX_IPRecord, AdminPassword, "������ ������.");
			FNC_IN  (BX_IPRecord, First, "������ ���������.");
			FNC_IN  (BX_IPRecord, Last, "����� ���������.");
			FNC_IN  (BX_IPRecord, Checked, "��������� ���������������");
			FNC_IN  (BX_IPRecord, ConceptID, "�������������� ���������, ��������������� ����� ���������.");
			FNC_OUT (BX_IPRecord, objID, "������������� ������� ���������.");
      FNC        (BX_IPRecord_GetData, "�������� ��������� ��������� �������.");
			FNC_IN  (BX_IPRecord, AdminPassword, "������ ������.");
			FNC_IN  (BX_IPRecord, objID, "{class:IRecord}������������� ������� ���������.");
			FNC_OUT (BX_IPRecord, Count, "������� ����� � ����� ��������� IP.");
			FNC_OUT (BX_IPRecord, Mask, "����� ��������� ������� (�.�. ����� ��� ��������� �����).");
			FNC_OUT (BX_IPRecord, First, "������ ���������.");
			FNC_OUT (BX_IPRecord, Last, "����� ���������.");
			FNC_OUT (BX_IPRecord, Checked, "��������� ���������������");
			FNC_OUT (BX_IPRecord, ConceptID, "�������������� ���������, ��������������� ����� ���������.");
      FNC        (BX_IPRecord_Check, "���������� ������� ��������� ������� � ��������������� ��� ��������. ���������� �� New ���, ��� �� ������� ������ �������, � ������������� (������ �������) ���� checked � �������������. ���� ������ ��������� ����, �� ������������ � ������� �������� �� ��������.");
			FNC_IN  (BX_IPRecord, AdminPassword, "������ ������.");
			FNC_IN  (BX_IPRecord, objID, "{class:IRecord}������������� ������� ���������.");
			FNC_IN  (BX_IPRecord, First, "������ ���������.");
			FNC_IN  (BX_IPRecord, Last, "����� ���������.");
			FNC_IN  (BX_IPRecord, ConceptID, "�������������� ���������, ��������������� ����� ���������.");
      FNC        (BX_IPRecord_Enumerate, "����� ������������������ � ������� IP-����������.");
			FNC_IN  (BX_IPRecord, Checked, "�������� ���� � ������������� ������ Checked (�.�. � �������������� ������ First � Last).");
			FNC_IN  (BX_IPRecord, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_IPRecord, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_IPRecord, objIDs, "�������������� ��������.");
			FNC_OUT (BX_IPRecord, objNames, "���������� � ����������.");

   // Concept
      FNC        (BX_Concept_TypeEnumerate, "���������� ������ ����� ��������� � �� ��������.");
			FNC_OUT (BX_Concept, objNums, "������ ������� ��������.");
			FNC_OUT (BX_Concept, objNames, "������ �������� ����� ���������.");

   // User
      FNC        (BX_User_GetLanguage, "���������� ID ����� ���������� ������������. ������ �� ���������.");
			FNC_IN  (BX_User, objID, "{class:User}ID ������������.");
			FNC_OUT (BX_User, InterfaceLanguage, "ID ����� ���������� ������������.");

   // Site
      FNC        (BX_Site_GetAudienceIntersect, "�������� ����������� ��������� ��� ������� �����.");
			FNC_IN  (BX_Site, objID, "{class:Site}ID c����.");
			FNC_OUT (BX_Site, Audience_SiteID, "ID ������, �� ������� �������� ���������� ������� �����.");
			FNC_OUT (BX_Site, Audience_SiteName, "�������� ������, �� ������� �������� ���������� ������� �����.");
			FNC_OUT (BX_Site, Audience_Viewers, "����� ����������� �����, ���������� �� ����� ���������������� ����������.");
			FNC_OUT (BX_Site, Audience_Hosts, "���-�� ������, ������� ���������� ����� ������� �� ����� ���������������� ����������.");

   // ConceptRate
      FNC        (BX_ConceptRate_Reg_InetAudience, "�������� ������������� ��������� ��� ��������� ���������.");
			FNC_IN  (BX_ConceptRate, TypeNums, "������ ����� ���������, ������� �������� �� ������� � �������������.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "����� �����, �� ������� ����� �������� �������� ��������� (�� ��������� - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "�������� ���������, ��������� � ��������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "�������� ���������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "������ ��������� �� CRN_Name.");
      FNC        (BX_ConceptRate_Site_Visitor, "�������� ������������� ��������� ����������� �����.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Site}ID c����.");
			FNC_IN  (BX_ConceptRate, TypeNums, "������ ����� ���������, ������� �������� �� ������� � �������������.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "����� �����, �� ������� ����� �������� �������� ��������� (�� ��������� - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "�������� ���������, ��������� � ��������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "�������� ���������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "������ ��������� �� CRN_Name.");
      FNC        (BX_ConceptRate_Viewer_Site, "�������� ������������� ��������� �������.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Viewer}ID �������.");
			FNC_IN  (BX_ConceptRate, TypeNums, "������ ����� ���������, ������� �������� �� ������� � �������������.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "����� �����, �� ������� ����� �������� �������� ��������� (�� ��������� - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "�������� ���������, ��������� � ��������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "�������� ���������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "������ ��������� �� CRN_Name.");
      FNC        (BX_ConceptRate_Viewer_Inquiry, "�������� ������������� �������� ��������� �������.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Viewer}ID �������.");
			FNC_IN  (BX_ConceptRate, TypeNums, "������ ����� ���������, ������� �������� �� ������� � �������������.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "����� �����, �� ������� ����� �������� �������� ��������� (�� ��������� - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "�������� ���������, ��������� � ��������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "�������� ���������������� �������������.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "������ ��������� �� CRN_Name.");

   // Admin
      FNC        (BX_Admin_MemoryManagerReport, "��������� ������ ���������� ������. ��������� ������ ��������������.");
			FNC_OUT (BX_Admin, MemoryManagerReport, "����� ���������� ������.");

   // Viewer
      FNC        (BX_Viewer_Enumerate, "����������� ��������.");
			FNC_IN  (BX_Viewer, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_Viewer, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_Viewer, objIDs, "�������������� ��������.");
			FNC_OUT (BX_Viewer, objNames, "ID+IP �������.");
      FNC        (BX_Viewer_GetData, "�������� ���������� �� �������.");
			FNC_IN  (BX_Viewer, objID, "{class:Viewer}ID �������");
			FNC_IN  (BX_Viewer, IPAddress, "IP ����� (������������, ���� �� ������ objID). ���� ������� � ���� IP �� ������, �� ����� ������� 'NotFound'.");
			FNC_OUT (BX_Viewer, Anonymous, "�������� �� ���� ������ ����������� ����� ��������� � ���������� IP � ��������������� Cookie.");
			FNC_OUT (BX_Viewer, TotalShows, "����� ���-�� �������.");
			FNC_OUT (BX_Viewer, TotalClicks, "����� ���-�� ������.");
			FNC_OUT (BX_Viewer, IPAddress, "IP �����.");
			FNC_OUT (BX_Viewer, Referrer, "���� �������.");
			FNC_OUT (BX_Viewer, CreationTime, "����� �������� �������.");
			FNC_OUT (BX_Viewer, sCreationTime, "����� �������� ������� � ��������� ����.");
			FNC_OUT (BX_Viewer, LastVisitTime, "����� ���������� ���������.");
			FNC_OUT (BX_Viewer, sLastVisitTime, "����� ���������� ��������� � ��������� ����.");
			FNC_OUT (BX_Viewer, TZOffset, "�������� �������� ����� ������� � ��������.");
			FNC_OUT (BX_Viewer, Site, "ID ������, ���������� ��������.");
			FNC_OUT (BX_Viewer, sSite, "�������� ������, ���������� ��������.");
			FNC_OUT (BX_Viewer, sSite_LastVisited, "����� ���������� ��������� ���������������� ����� � ��������� ����.");
			FNC_OUT (BX_Viewer, Site_Visits, "����� ����� ��������� ���������������� �����.");

   // RateStats
      FNC        (BX_RateStats_Site, "�������� ����������� ���������� �� ������.");
			FNC_IN  (BX_RateStats, VBN, "{class:VBN}������������� VBN, ��� �������� ������� ��������� ������.");
			FNC_IN  (BX_RateStats, Concept, "{class:Concept}������ ��������� ��������.");
			FNC_IN  (BX_RateStats, FirstPos, "������� � �������� ������� �������.");
			FNC_IN  (BX_RateStats, LastPos, "������� � �������� ���������� �������.");
			FNC_IN  (BX_RateStats, Ascending, "���������� �� �����������.");
			FNC_IN  (BX_RateStats, WithDescription, "�������� �� ��������.");
			FNC_IN  (BX_RateStats, CreatedAfter, "���� ������ ����� ���������� �������");
			FNC_IN  (BX_RateStats, CreatedBefore, "���� ������ �� ���������� �������");
			FNC_IN  (BX_RateStats, Indices, "������ �������� ��������, �������� ������� � ������ ���� ������.");
			FNC_IN  (BX_RateStats, KeyIndex, "�������� �������, �� �������� ���������� ����������.");
			FNC_OUT (BX_RateStats, RawTable, "��������� ������ � ����������� ����������� ��������.");
			FNC_OUT (BX_RateStats, ObjectsNum, "���������� ��������, ������ �� ������� ��������� � RawTable.");
			FNC_OUT (BX_RateStats, Total, "����� � VBN �� ����������� ��������.");
			FNC_OUT (BX_RateStats, SubTotal, "����� � ������ ������ �� ����������� ��������.");
			FNC_OUT (BX_RateStats, VBNTotalObjects, "����� �������� � ������ VBN.");
			FNC_OUT (BX_RateStats, ReqTotal, "����� �� ����������� �������� � ��������������� ������.");
			FNC_OUT (BX_RateStats, VBNTotalObjectsAct, "����� �������� �������� � ������ VBN.");
			FNC_OUT (BX_RateStats, ReqTotalObjects, "����� ��������, ��������������� �������");
			FNC_OUT (BX_RateStats, ReqTotalObjectsAct, "����� �������� ��������, ��������������� �������");

   // Security
      FNC        (BX_Security_Authorize, "����������� �������������, ��������������� ������� � VBN.");
			FNC_IN  (BX_Security, VBN, "ID ����������� ����, ����� ������ ��� ����������� ������������.");
			FNC_IN  (BX_Security, Level, "���� ������������ - ����� ��������� ���� �� 3 ��������: 'Root', 'VBN', 'User'.");
			FNC_IN  (BX_Security, Login, "�����, ��� VBN - ��� ��� VBN, ��� ���� - ��� 'Root'.");
			FNC_IN  (BX_Security, Password, "������.");
			FNC_OUT (BX_Security, Result, "True, ���� ����������� ������ �������.");

   // User
      FNC        (BX_User_Enumerate, "������������ ���� ������������� ���������� �� VBN.");
			FNC_IN  (BX_User, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_User, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_User, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_User, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");

   // SiteProfile
      FNC        (BX_SiteProfile_Enumerate, "������������ ���� �������� ����� ���������� �� VBN.");
			FNC_IN  (BX_SiteProfile, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_SiteProfile, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_SiteProfile, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_SiteProfile, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");

   // Site
      FNC        (BX_Site_Enumerate, "������������ ���� ������ ���������� �� VBN.");
			FNC_IN  (BX_Site, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_Site, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_Site, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_Site, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");

   // BannerProfile
      FNC        (BX_BannerProfile_Enumerate, "������������ ���� �������� �������� ���������� �� VBN.");
			FNC_IN  (BX_BannerProfile, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_BannerProfile, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_BannerProfile, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_BannerProfile, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");

   // Banner
      FNC        (BX_Banner_Enumerate, "������������ ���� �������� ���������� �� VBN.");
			FNC_IN  (BX_Banner, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_Banner, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_Banner, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_Banner, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");

   // Language
      FNC        (BX_Language_New, "�������� ������ �����. � ������ �������� � objID ������������ ������������� ���������� �������.");
			FNC_IN  (BX_Language, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Language, ShortName, "������������ �����.");
			FNC_IN  (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_IN  (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_IN  (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_OUT (BX_Language, objID, "������������� �������.");
      FNC        (BX_Language_PutData, "��������� ���������� ������������� ����� � ��������������� objID.");
			FNC_IN  (BX_Language, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Language, objID, "������������� �������.");
			FNC_IN  (BX_Language, ShortName, "������������ �����.");
			FNC_IN  (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_IN  (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_IN  (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
      FNC        (BX_Language_Enumerate, "��������� �������� ���� ������, ������������������ � �������. �������� ������������ � ���� objNames[] ������� ���������. ��������������� �������������� ������������ � ���� objIDs[] ������� ���������.");
			FNC_IN  (BX_Language, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_Language, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_IN  (BX_Language, objLanguageNo, "���������� ����� �����, �� ������� �������� ���������� �������� *Enumerate(). �� ��������� ����� ����������� ������ ������� ������������� �����.");
			FNC_OUT (BX_Language, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_Language, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");
      FNC        (BX_Language_GetData, "��������� ���������� � ����� � ��������� ID.");
			FNC_IN  (BX_Language, objID, "������������� �������.");
			FNC_OUT (BX_Language, ShortName, "������������ �����.");
			FNC_OUT (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_OUT (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_OUT (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_OUT (BX_Language, No, "���������� ����� � �������");
      FNC        (BX_Language_Delete, "�������� �����.");
			FNC_IN  (BX_Language, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Language, objID, "������������� �������.");

   // Concept
      FNC        (BX_Concept_New, "�������� ��������. � ������ �������� ������������� ���������� �������� ������������ � objID.");
			FNC_IN  (BX_Concept, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Concept, Parent, "{class:Concept}Id �������� - �� ���� ������ ���� ����� NA ������ � ����� ������");
			FNC_IN  (BX_Concept, Name, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_IN  (BX_Concept, Description, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_IN  (BX_Concept, ShortName, "����������� ���.");
			FNC_IN  (BX_Concept, Type, "��� ��������.");
			FNC_IN  (BX_Concept, TypeNo, "����� ���� ��������.");
			FNC_OUT (BX_Concept, objID, "������������� �������.");
      FNC        (BX_Concept_PutData, "����������� ���������� ������������� �������� � ��������������� objID.");
			FNC_IN  (BX_Concept, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Concept, objID, "������������� �������.");
			FNC_IN  (BX_Concept, Name, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_IN  (BX_Concept, Description, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_IN  (BX_Concept, ShortName, "����������� ���.");
			FNC_IN  (BX_Concept, Type, "��� ��������.");
			FNC_IN  (BX_Concept, TypeNo, "����� ���� ��������.");
      FNC        (BX_Concept_Enumerate, "��������� ��������������� ���� ��������� �� ����� # objLanguageNo ������� '� ������', �.�. � ������� ����������� ������.");
			FNC_IN  (BX_Concept, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_Concept, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_IN  (BX_Concept, objLanguageNo, "���������� ����� �����, �� ������� �������� ���������� �������� *Enumerate().");
			FNC_OUT (BX_Concept, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_Concept, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");
      FNC        (BX_Concept_ExtendedEnumerate, "�������� ������ ��������������� � �������� ��������� ��������� ������ �� �������� ����� � ���������� ��������� � ������������ � �������. �������� ��������� '� �������', �.�. � ������� ���������� ���������. ���� ������ Level, �� ��������� �������� � ������� �� Level ������������, ����� - ��� ��������.");
			FNC_IN  (BX_Concept, SiteCount, "���� SiteCount > 0, �� � ����� �������� ����������� (���������� ������ � ������ ���������).");
			FNC_IN  (BX_Concept, Indent, "���� Indent == true, �� ����� ������ �������� ����������� ������ ���������� �������� � html-�������.");
			FNC_IN  (BX_Concept, VBN, "{class:VBN}���� ������ VBN, �� ��������� �������� �������� VBN.");
			FNC_IN  (BX_Concept, Level, "���� ������ Level, �� ��������� �������� � ������� �� Level ������������, ����� - ��� ��������.");
			FNC_IN  (BX_Concept, ConceptType, "��� �������� (��� Extended Enumerate).");
			FNC_IN  (BX_Concept, objLanguageNo, "���� ������ ����� ����� objLanguage, �� �� ���������� ���� ���������, ����� ���� ����� ����� VBN, ����� - �������� �����.");
			FNC_OUT (BX_Concept, objIDs, "������ ��������������� ���������.");
			FNC_OUT (BX_Concept, objNames, "������ �������� ���������.");
      FNC        (BX_Concept_GetData, "��������� ���������� � �������� � ��������� ��������������� objID.");
			FNC_IN  (BX_Concept, objID, "������������� �������.");
			FNC_OUT (BX_Concept, Parent, "Id �������� - �� ���� ������ ���� ����� NA ������ � ����� ������.");
			FNC_OUT (BX_Concept, Name, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_OUT (BX_Concept, Description, "������ �������� �������� �� ���� ������, ��������� � �������.");
			FNC_OUT (BX_Concept, ShortName, "����������� ���.");
			FNC_OUT (BX_Concept, Type, "��� ��������.");
			FNC_OUT (BX_Concept, TypeNo, "����� ���� ��������.");
			FNC_OUT (BX_Concept, Level, "������� �������� � ������ ������������ ��������.");
			FNC_OUT (BX_Concept, No, "���������� ����� ��������.");
      FNC        (BX_Concept_Delete, "�������� �������� � ��������� ��������������� objID. ��� ������� �������� ����� ���������.");
			FNC_IN  (BX_Concept, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_Concept, objID, "������������� �������.");

   // VBN
      FNC        (BX_VBN_New, "�������� ����������� ��������� ����. �� ����� ����� ������ ��������� ���� Password, ������� ����� �����������  ��� ������� �� ���� �������� � ������ VBN, � ����� ������ �������������� AdminPassword. � ������ �������� � objID ������������ ������������� ���������� �������.");
			FNC_IN  (BX_VBN, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_VBN, Password, "������, ������� ������������ ����� �������������� ��� ������� � ���������� ����.");
			FNC_IN  (BX_VBN, Name, "�������� ����.");
			FNC_IN  (BX_VBN, Description, "�������� ����.");
			FNC_IN  (BX_VBN, IsModerated, "�������� �� ���� ���������������.");
			FNC_IN  (BX_VBN, DefaultLanguage, "{class:Language}ID ����� ���� �� ���������.");
			FNC_IN  (BX_VBN, DefaultTZOffset, "�������� �������� ����� �� ��������� (� ��������).");
			FNC_IN  (BX_VBN, ConceptMask, "{class:Concept}������ ��������������� ������������ � ���� ��������� (���� �� ����, �� ������������ ��� ��������).");
			FNC_OUT (BX_VBN, objID, "������������� �������.");
      FNC        (BX_VBN_PutData, "��������� ���������� ����������� ��������� ���� � ��������������� objID. �� ����� ����� ������ ��������� ���� Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ���������� ����.");
			FNC_IN  (BX_VBN, Name, "�������� ����.");
			FNC_IN  (BX_VBN, Description, "�������� ����.");
			FNC_IN  (BX_VBN, IsModerated, "�������� �� ���� ���������������.");
			FNC_IN  (BX_VBN, DefaultLanguage, "{class:Language}ID ����� ���� �� ���������.");
			FNC_IN  (BX_VBN, DefaultTZOffset, "�������� �������� ����� �� ��������� (� ��������).");
			FNC_IN  (BX_VBN, ConceptMask, "{class:Concept}������ ��������������� ������������ � ���� ��������� (���� �� ����, �� ������������ ��� ��������).");
      FNC        (BX_VBN_Enumerate, "��������� ��������������� (� objIDs) � �������� (objNames) ���� ����������� �������� �����, ������������������ � �������.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� �������� �� ����� � ������� objLanguageNo.");
      FNC        (BX_VBN_GetData, "��������� ���������� ����������� ��������� ���� � ��������� objID. ������ ��������� ���� ���������� �� �����.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_OUT (BX_VBN, Name, "�������� ����.");
			FNC_OUT (BX_VBN, Description, "�������� ����.");
			FNC_OUT (BX_VBN, IsModerated, "�������� �� ���� ���������������.");
			FNC_OUT (BX_VBN, DefaultLanguage, "ID ����� ���� �� ���������.");
			FNC_OUT (BX_VBN, DefaultTZOffset, "�������� �������� ����� �� ��������� (� ��������).");
			FNC_OUT (BX_VBN, ConceptMask, "������ ��������������� ������������ � ���� ��������� (���� �� ����, �� ������������ ��� ��������).");
			FNC_OUT (BX_VBN, No, "���������� ����� ����.");
      FNC        (BX_VBN_ConceptEnumerate, "��������� ��������������� (� objIDs) � �������� (objNames) ���� ��������� ����������� �������� ���� � ��������������� objID.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, objLanguageNo, "���������� ����� �����, �� ������� �������� ����������, �� ��������� ����� ����� VBN.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ���������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ���������.");
      FNC        (BX_VBN_GetOwnerID, "��������� �������������� ��������� ����. �� ����� ����� ������ ��������� ���� Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ���������� ����.");
			FNC_OUT (BX_VBN, Owner, "�������� ����, �������� ���� �������� � �������.");
      FNC        (BX_VBN_Delete, "�������� ����������� ��������� ���� � ��������� ��������������� objID. ���������� �������� ���������� ������ �������������� AdminPassword.");
			FNC_IN  (BX_VBN, AdminPassword, "������ �������������� �������.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
      FNC        (BX_VBN_UserEnumerate, "���������� � objIDs � objNames �������������� � ����� ����������� ������������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_SiteEnumerate, "���������� � objIDs � objNames �������������� � ����� ����������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_SiteProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ����������� �������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_BannerEnumerate, "���������� � objIDs � objNames �������������� � ����� ����������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_BannerProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ����������� �������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_UnallowedUserEnumerate, "���������� � objIDs � objNames �������������� � ����� ������������� ������������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_UnallowedSiteEnumerate, "���������� � objIDs � objNames �������������� � �����  ������������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_UnallowedSiteProfileEnumerate, "���������� � objIDs � objNames �������������� � �����  ������������� �������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_UnallowedBannerEnumerate, "���������� � objIDs � objNames �������������� � ����� ������������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_UnallowedBannerProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ������������� �������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_NewUserEnumerate, "���������� � objIDs � objNames �������������� � ����� ����� ������������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_NewSiteEnumerate, "���������� � objIDs � objNames �������������� � ����� ����� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_NewSiteProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ����� �������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_NewBannerEnumerate, "���������� � objIDs � objNames �������������� � ����� ����� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_NewBannerProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ����� �������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_ChangedUserEnumerate, "���������� � objIDs � objNames �������������� � ����� ��������� ������������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_ChangedSiteEnumerate, "���������� � objIDs � objNames �������������� � ����� ��������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_ChangedSiteProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ��������� �������� ������ �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_ChangedBannerEnumerate, "���������� � objIDs � objNames �������������� � ����� ��������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");
      FNC        (BX_VBN_ChangedBannerProfileEnumerate, "���������� � objIDs � objNames �������������� � ����� ��������� �������� �������� �� VBN � id=objID. ���������� ������� ������ Password.");
			FNC_IN  (BX_VBN, objID, "������������� ����������� ����.");
			FNC_IN  (BX_VBN, Password, "������ ��� ������� � ����������� ��������� ����.");
			FNC_IN  (BX_VBN, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_VBN, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_VBN, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_VBN, objNames, "������ �������� ��������.");

   // User
      FNC        (BX_User_GetForgetPassword, "���������� ���� ������������ ������.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID ����������� ���� ������������.");
			FNC_IN  (BX_User, Login, "��� ��� ������� � �������.");
			FNC_OUT (BX_User, ForgetPassword, "�������� �����.");
      FNC        (BX_User_SetForgetPassword, "������������� ���� ������������ ������.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID ����������� ���� ������������.");
			FNC_IN  (BX_User, Login, "��� ��� ������� � �������.");
			FNC_IN  (BX_User, ForgetPassword, "�������� �����.");
      FNC        (BX_User_New, "�������� ������������. ����� ��������� ������� ������� � ����� �� ���������.");
			FNC_IN  (BX_User, Login, "��� ��� ������� � �������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, PasswordConfirm, "������������� ������.");
			FNC_IN  (BX_User, FullName, "������ ��� ������������.");
			FNC_IN  (BX_User, Email, "E-mail.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID ����������� ���� ������������.");
			FNC_OUT (BX_User, objID, "������������� ������������.");
			FNC_OUT (BX_User, ExitCode, "��� �������� (Okay=0;BadPasswordConfirm=1;InvalidEmail=2;PasswordTooShort=3;LoginTooShort=4;LoginAlreadyExists=5).");
      FNC        (BX_User_GetData, "��������� ��������� ������������. ���� �� ������ objID, �� ������������ ������ �� ����� Login, Password � VBN, � ������������� ���������� ������������ ������������ � objID. � ���� ������ �������� ������� ������ BXE_User_GetData_LoginNotFound ��� BXE_User_GetData_PasswordIncorrect. ������ ������������ Password ���������� ������� � ����� ������.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Login, "��� ��� ������� � �������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID ����������� ����.");
			FNC_OUT (BX_User, objID, "������������� ���������� ������������, ���� ������������ ����� �� Login/Password.");
			FNC_OUT (BX_User, Login, "��� ��� ������� � �������.");
			FNC_OUT (BX_User, FullName, "������ ��� ������������.");
			FNC_OUT (BX_User, InterfaceLanguage, "ID ���������������� ����� ����������.");
			FNC_OUT (BX_User, InterfaceType, "��������� ������������ (�������/������).");
			FNC_OUT (BX_User, CreationTime, "����� �������� �������.");
			FNC_OUT (BX_User, sCreationTime, "����� �������� �������.");
			FNC_OUT (BX_User, VBN, "ID ����������� ���� ������������.");
			FNC_OUT (BX_User, Email, "Email.");
			FNC_OUT (BX_User, Phone, "�������.");
			FNC_OUT (BX_User, Fax, "Fax.");
			FNC_OUT (BX_User, Address, "�����.");
			FNC_OUT (BX_User, URL, "URL-�����.");
			FNC_OUT (BX_User, Comment, "�����������.");
			FNC_OUT (BX_User, TZOffset, "�������� ��������� ���� � ��������.");
			FNC_OUT (BX_User, NotifyFreq, "��� ����� ��������� ���������� (�� ����/ ������ ����/������/�����).");
			FNC_OUT (BX_User, NotifyHTML, "��������� �� ���������� � ���� HTML.");
			FNC_OUT (BX_User, NotifyDepth, "��� ����������� ���������� (� ������������, �������).");
			FNC_OUT (BX_User, ShowsLeft, "����� ����� ���������� �������.");
			FNC_OUT (BX_User, ClicksLeft, "����� ����� ���������� ������.");
			FNC_OUT (BX_User, TradeStats, "���������� � �������/������� �������/������ � ������������.");
			FNC_OUT (BX_User, Allowed, "���������� ������������ ��������� �����������.");
			FNC_OUT (BX_User, ObjectState, "��������� �������: 0 - ��������; 1 - �����; 2 - �������� ����������� ����; 3 - ������.");
      FNC        (BX_User_GetEmail, "��������� ������ ��. ����� ������������ �� ��� ������ � VBN.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID ����������� ���� ������������.");
			FNC_IN  (BX_User, Login, "��� ��� ������� � �������.");
			FNC_OUT (BX_User, Email, "Email.");
      FNC        (BX_User_PutData, "��������� ��������� ������������ � ��������������� objID. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, FullName, "������ ��� ������������.");
			FNC_IN  (BX_User, InterfaceLanguage, "{class:Language}ID ���������������� ����� ����������.");
			FNC_IN  (BX_User, InterfaceType, "��������� ������������ (�������/������).");
			FNC_IN  (BX_User, Email, "Email.");
			FNC_IN  (BX_User, Phone, "�������.");
			FNC_IN  (BX_User, Fax, "Fax.");
			FNC_IN  (BX_User, Address, "�����.");
			FNC_IN  (BX_User, URL, "URL-�����.");
			FNC_IN  (BX_User, Comment, "�����������.");
			FNC_IN  (BX_User, TZOffset, "�������� ��������� ���� � ��������.");
			FNC_IN  (BX_User, NotifyFreq, "��� ����� ��������� ���������� (�� ����/ ������ ����/������/�����).");
			FNC_IN  (BX_User, NotifyHTML, "��������� �� ���������� � ���� HTML.");
			FNC_IN  (BX_User, NotifyDepth, "��� ����������� ���������� (� ������������, �������).");
      FNC        (BX_User_Delete, "�������� ������������ � ��������������� objID. ��������� ��� �����, ������� � ������� ������������. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
      FNC        (BX_User_SiteEnumerate, "��������� ������ ��������������� (� objIDs) � �������� (� objNames) ������ ������������ � ��������������� objID. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_User, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_User, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_User, objNames, "������ �������� ��������.");
      FNC        (BX_User_BannerEnumerate, "��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� ������������ � ��������������� objID. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_User, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_User, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_User, objNames, "������ �������� ��������.");
      FNC        (BX_User_SiteProfileEnumerate, "��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� ������ ������������ � ��������������� objID. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_User, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_User, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_User, objNames, "������ �������� ��������.");
      FNC        (BX_User_BannerProfileEnumerate, "��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� �������� ������������ � ��������������� objID. ���������� ������� ������ ������������ Password.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � �������.");
			FNC_IN  (BX_User, objFirstNo, "����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0.");
			FNC_IN  (BX_User, objLastNo, "����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.");
			FNC_OUT (BX_User, objIDs, "������ ��������������� ��������.");
			FNC_OUT (BX_User, objNames, "������ �������� ��������.");
      FNC        (BX_User_RegisterAsSystem, "����������� ������������ ��� ���������� (������� �������� ������������ � �������������� ���������). ���������� ������� Password ��� ������� � VBN ������������.");
			FNC_IN  (BX_User, objID, "������������� ������������.");
			FNC_IN  (BX_User, Password, "������ ��� ������� � VBN ������������.");

   // SiteProfile
      FNC        (BX_SiteProfile_New, "������ ������� ����� ��� ������������ � ��������������� OwnerID. ���� ������ objFromID , �� � ��������� ������� ���������� ��������� �� ������� � ��������������� objFromID. � objID ������������ id ���������� �������. � Name ������������ �������� ���������� �������. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_SiteProfile, OwnerID, "{class:User}������������� ������������-���������.");
			FNC_IN  (BX_SiteProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_SiteProfile, Name, "�������� ������ ������� (�� ��������� - timestamp).");
			FNC_IN  (BX_SiteProfile, objFromID, "������������� source-�������.");
			FNC_OUT (BX_SiteProfile, objID, "������������� ������� �����.");
			FNC_OUT (BX_SiteProfile, Name, "�������� �������.");
      FNC        (BX_SiteProfile_CopyData, "����������� ��������� ������� ����� �� ������� objFromID � ������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "������������� ������� �����.");
			FNC_IN  (BX_SiteProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_SiteProfile, objFromID, "{class:SiteProfile}������������� source-�������.");
			FNC_OUT (BX_SiteProfile, Name, "�������� �������.");
      FNC        (BX_SiteProfile_GetData, "��������� ��������� ������� ����� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "������������� ������� �����.");
			FNC_IN  (BX_SiteProfile, objPassword, "������ ������������-��������� �������.");
			FNC_OUT (BX_SiteProfile, Name, "�������� �������.");
			FNC_OUT (BX_SiteProfile, Site, "ID ������, ������������ ������ ��������.");
			FNC_OUT (BX_SiteProfile, sSite, "����� ������, ������������ ������ ��������.");
			FNC_OUT (BX_SiteProfile, VBN, "ID ����������� �������.");
			FNC_OUT (BX_SiteProfile, LastModified, "����� ���������� ��������� �������.");
			FNC_OUT (BX_SiteProfile, sLastModified, "����� ���������� ��������� ������� � ��������� �������������.");
			FNC_OUT (BX_SiteProfile, OwnerID, "������������� ������������-���������.");
			FNC_OUT (BX_SiteProfile, BannerInclude, "������ ����������� � ������ ��������.");
			FNC_OUT (BX_SiteProfile, BannerExclude, "������ ����������� � ������ ��������.");
			FNC_OUT (BX_SiteProfile, SiteInclude, "������ ����������� � ������� ������.");
			FNC_OUT (BX_SiteProfile, SiteExclude, "������ ����������� � ������� ������.");
			FNC_OUT (BX_SiteProfile, MaxFileSize, "������������ ������ ����� � ���������.");
			FNC_OUT (BX_SiteProfile, UseKeywords, "���������� ������� � ������������ � ��������� ������� ������.");
			FNC_OUT (BX_SiteProfile, BannerConceptInclude, "������ ����������x � ������ ��������� ��������.");
			FNC_OUT (BX_SiteProfile, BannerConceptExclude, "������ ����������� � ������ ��������� ��������.");
			FNC_OUT (BX_SiteProfile, Allowed, "���������� ������������ ��������� �����������.");
			FNC_OUT (BX_SiteProfile, ObjectState, "��������� �������: 0 - ��������; 1 - �����; 2 - �������� ����������� ����; 3 - ������.");
      FNC        (BX_SiteProfile_PutData, "��������� ��������� ������� ����� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "������������� ������� �����.");
			FNC_IN  (BX_SiteProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_SiteProfile, Name, "�������� �������.");
			FNC_IN  (BX_SiteProfile, BannerInclude, "{class:Banner}������ ����������� � ������ ��������.");
			FNC_IN  (BX_SiteProfile, BannerExclude, "{class:Banner}������ ����������� � ������ ��������.");
			FNC_IN  (BX_SiteProfile, SiteInclude, "������ ����������� � ������� ������.");
			FNC_IN  (BX_SiteProfile, SiteExclude, "������ ����������� � ������� ������.");
			FNC_IN  (BX_SiteProfile, MaxFileSize, "������������ ������ ����� � ���������.");
			FNC_IN  (BX_SiteProfile, UseKeywords, "���������� ������� � ������������ � ��������� ������� ������.");
			FNC_IN  (BX_SiteProfile, BannerConceptInclude, "{class:Concept}������ ����������x � ������ ��������� ��������.");
			FNC_IN  (BX_SiteProfile, BannerConceptExclude, "{class:Concept}������ ����������� � ������ ��������� ��������.");
      FNC        (BX_SiteProfile_Delete, "�������� ��������� ������� ����� � ��������� ID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "������������� ������� �����.");
			FNC_IN  (BX_SiteProfile, objPassword, "������ ������������-��������� �������.");

   // Site
      FNC        (BX_Site_New, "�������� �����. ��������� ������������� ��������� OwnerID � URL �����. ������������� ���������� ����� ������������ � ���� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Site, OwnerID, "{class:User}ID ������������-��������� �����.");
			FNC_IN  (BX_Site, Profile, "{class:SiteProfile}������� ������� (�� ��������� �� ����������).");
			FNC_IN  (BX_Site, Name, "�������� ����� (�� ���������=URL).");
			FNC_IN  (BX_Site, objPassword, "������ ������������-��������� �����.");
			FNC_IN  (BX_Site, URL, "URL �����.");
			FNC_IN  (BX_Site, objFromID, "������������� source-�����.");
			FNC_OUT (BX_Site, objID, "������������� ������� �����.");
      FNC        (BX_Site_GetData, "��������� ���������� ����� � ��������� ��������������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Site, objID, "������������� ������� �����.");
			FNC_IN  (BX_Site, objPassword, "������ ������������-��������� �����.");
			FNC_OUT (BX_Site, OwnerID, "ID ������������-��������� �����.");
			FNC_OUT (BX_Site, VBN, "ID ����������� �������.");
			FNC_OUT (BX_Site, CreationTime, "����� �������� � ���� gmtime.");
			FNC_OUT (BX_Site, sCreationTime, "����� �������� ����� � ��������� ����.");
			FNC_OUT (BX_Site, MirrorInclude, "������ ������ �����.");
			FNC_OUT (BX_Site, MirrorExclude, "������ ������������ ������ �����.");
			FNC_OUT (BX_Site, MirrorSubstr, "������ ����, ������� ������������ � HTTP_REFERER ��� �������� ������.");
			FNC_OUT (BX_Site, IgnoredIP, "������ IP-�������, ���� � ������� �� ������������� (���� ��� ��������������).");
			FNC_OUT (BX_Site, IgnoredViewerID, "������ ID ��������, ���� � ������� �� ������������� (���� ��� ��������������).");
			FNC_OUT (BX_Site, Alias, "������� ID �����.");
			FNC_OUT (BX_Site, Name, "�������� �����.");
			FNC_OUT (BX_Site, Description, "�������� (��� ��������������).");
			FNC_OUT (BX_Site, URL, "URL �����.");
			FNC_OUT (BX_Site, CounterType, "��� �������� ��� ����� �����.");
			FNC_OUT (BX_Site, RateMySite, "��������� �� ���� ���� � �������� ������������.");
			FNC_OUT (BX_Site, RateStatsViewPassword, "������ �� ������ � ���������� ������������ ��� ����� �����.");
			FNC_OUT (BX_Site, ShowAudience, "��������� �� ����������� � ��������� ����������� ���������.");
			FNC_OUT (BX_Site, ShowAudienceOffTime, "����� ���������� ���������� ShowAudience.");
			FNC_OUT (BX_Site, Profile, "ID �������-������� �����.");
			FNC_OUT (BX_Site, Keyword, "�������� ����� ��� ����� �����.");
			FNC_OUT (BX_Site, Concept, "�������� �����.");
			FNC_OUT (BX_Site, PageName, "������ �������� ������� �����.");
			FNC_OUT (BX_Site, PageNo, "������ ������� ������� �����.");
			FNC_OUT (BX_Site, AdBannerProfile, "������ ID �������� ��������, ������������� ���� ����.");
			FNC_OUT (BX_Site, SuspiciousInfo, "ID ������� �� ����������� �������������� �������.");
			FNC_OUT (BX_Site, Allowed, "���������� ������������ ��������� �����������.");
			FNC_OUT (BX_Site, ObjectState, "��������� �������: 0 - ��������; 1 - �����;2 - �������� ����������� ����; 3 - ������.");
      FNC        (BX_Site_PutData, "��������� ���������� ����� � ��������� ��������������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Site, objID, "������������� ������� �����.");
			FNC_IN  (BX_Site, objPassword, "������ ������������-��������� �����.");
			FNC_IN  (BX_Site, MirrorInclude, "������ ������ �����.");
			FNC_IN  (BX_Site, MirrorExclude, "������ ������������ ������ �����.");
			FNC_IN  (BX_Site, MirrorSubstr, "������ ����, ������� ������������ � HTTP_REFERER ��� �������� ������.");
			FNC_IN  (BX_Site, IgnoredIP, "������ IP-�������, ���� � ������� �� ������������� (���� ��� ��������������).");
			FNC_IN  (BX_Site, IgnoredViewerID, "������ ID ��������, ���� � ������� �� ������������� (���� ��� ��������������).");
			FNC_IN  (BX_Site, Alias, "������� ID �����.");
			FNC_IN  (BX_Site, Name, "�������� �����.");
			FNC_IN  (BX_Site, Description, "�������� (��� ��������������).");
			FNC_IN  (BX_Site, URL, "URL �����.");
			FNC_IN  (BX_Site, CounterType, "��� �������� ��� ����� �����.");
			FNC_IN  (BX_Site, RateMySite, "��������� �� ���� ���� � �������� ������������.");
			FNC_IN  (BX_Site, RateStatsViewPassword, "������ �� ������ � ���������� ������������ ��� ����� �����.");
			FNC_IN  (BX_Site, ShowAudience, "��������� �� ����������� � ��������� ����������� ���������.");
			FNC_IN  (BX_Site, Profile, "{class:SiteProfile}ID �������-������� �����.");
			FNC_IN  (BX_Site, Keyword, "�������� ����� ��� ����� �����.");
			FNC_IN  (BX_Site, Concept, "{class:Concept}�������� �����.");
			FNC_IN  (BX_Site, PageName, "������ �������� ������� �����.");
      FNC        (BX_Site_Delete, "�������� ����� � ��������� ��������������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Site, objID, "������������� ������� �����.");
			FNC_IN  (BX_Site, objPassword, "������ ������������-��������� �����.");
      FNC        (BX_Site_GetCounterType, "�������� ��� �������� ��� �����.");
			FNC_IN  (BX_Site, objID, "������������� ������� �����.");
			FNC_OUT (BX_Site, CounterType, "��� �������� ��� ����� �����.");

   // SiteSuspiciousInfo
      FNC        (BX_SiteSuspiciousInfo_GetData, "�������� ���������� � �������������� ��������, ������������ �� �����.");
			FNC_IN  (BX_SiteSuspiciousInfo, objID, "{class:Site}������������� ������� �����.");
			FNC_IN  (BX_SiteSuspiciousInfo, objPassword, "������ ������������-��������� �����.");
			FNC_OUT (BX_SiteSuspiciousInfo, sEventType, "��� ������� (������).");
			FNC_OUT (BX_SiteSuspiciousInfo, sTime, "����� ������������� ������� (����������).");
			FNC_OUT (BX_SiteSuspiciousInfo, Viewer, "ID �������, ���������� �������.");
			FNC_OUT (BX_SiteSuspiciousInfo, IP, "IP-�����, ��������� �������");
			FNC_OUT (BX_SiteSuspiciousInfo, Referrer, "URL, � �������� ������ �������.");

   // BannerProfile
      FNC        (BX_BannerProfile_New, "������ ������� ������� ��� ������������ OwnerID. ���� ������ objFromID , �� � ��������� ������� ���������� ��������� �� ������� objFromID. � objID ������������ id ���������� �������. � Name  ������������ �������� ���������� �������. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_BannerProfile, OwnerID, "{class:User}������������� ������������-��������� ������� �������.");
			FNC_IN  (BX_BannerProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_BannerProfile, Name, "�������� ������ ������� (�� ��������� -Noname).");
			FNC_IN  (BX_BannerProfile, HREF, "{class:Site}ID �����, �� ������� ���� ������� ��� ������� �� ������.");
			FNC_IN  (BX_BannerProfile, objFromID, "������������� source-�������.");
			FNC_OUT (BX_BannerProfile, objID, "������������� ������� ������� �������.");
			FNC_OUT (BX_BannerProfile, Name, "�������� �������.");
      FNC        (BX_BannerProfile_CopyData, "����������� ��������� ������� ������� �� ������� objFromID � ������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "������������� ������� ������� �������.");
			FNC_IN  (BX_BannerProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_BannerProfile, objFromID, "{class:BannerProfile}������������� source-�������.");
      FNC        (BX_BannerProfile_GetData, "��������� ��������� ������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "������������� ������� ������� �������.");
			FNC_IN  (BX_BannerProfile, objPassword, "������ ������������-��������� �������.");
			FNC_OUT (BX_BannerProfile, Name, "�������� �������.");
			FNC_OUT (BX_BannerProfile, VBN, "ID ����������� �������.");
			FNC_OUT (BX_BannerProfile, LastModified, "����� ���������� ��������� ������� (gmtime).");
			FNC_OUT (BX_BannerProfile, sLastModified, "����� ���������� ��������� ������� � ��������� ����.");
			FNC_OUT (BX_BannerProfile, OwnerID, "������������� ������������-��������� ������� �������.");
			FNC_OUT (BX_BannerProfile, HREF, "ID �����, �� ������� ���� ������� ��� ������� �� ������.");
			FNC_OUT (BX_BannerProfile, Commercial, "�������� �� ������� ������� �������������.");
			FNC_OUT (BX_BannerProfile, Banner, "������ ��������, ������������ ������ ��������.");
			FNC_OUT (BX_BannerProfile, sBanner, "������ ��������, ������������ ������ �������� � ��������� ����.");
			FNC_OUT (BX_BannerProfile, Concept, "�������� �������.");
			FNC_OUT (BX_BannerProfile, State, "��������� (���/����).");
			FNC_OUT (BX_BannerProfile, AltText, "�������������� �����.");
			FNC_OUT (BX_BannerProfile, SiteConceptInclude, "�������� ������, �� ������� ���������� ������.");
			FNC_OUT (BX_BannerProfile, SiteConceptExclude, "�������� ������, �� ������� �� ���������� ������.");
			FNC_OUT (BX_BannerProfile, SiteInclude, "������ ����������� ������.");
			FNC_OUT (BX_BannerProfile, sSiteInclude, "������ ��� ����������� ������.");
			FNC_OUT (BX_BannerProfile, SiteExclude, "������ ����������� ������.");
			FNC_OUT (BX_BannerProfile, sSiteExclude, "������ ��� ����������� ������.");
			FNC_OUT (BX_BannerProfile, ViewerIPEnable, "����������� IP ��������.");
			FNC_OUT (BX_BannerProfile, ViewerIPDisable, "����������� IP ��������.");
			FNC_OUT (BX_BannerProfile, ViewerConceptInclude, "�������� ��������, ������� ���������� ������.");
			FNC_OUT (BX_BannerProfile, ViewerConceptExclude, "�������� ��������, ������� �� ���������� ������.");
			FNC_OUT (BX_BannerProfile, UseLocalTime, "��������� �� ���������� � ���������� ������� �������.");
			FNC_OUT (BX_BannerProfile, ScheduleTZOffset, "������� ���� ���������� (���� UseLocalTime==false).");
			FNC_OUT (BX_BannerProfile, ShowIfLocalUnknown, "���������� �� ������, ���� ��������� ����� ���������� (������������ � �������������� ScheduleTZOffset).");
			FNC_OUT (BX_BannerProfile, Schedule, "���������� - �� ���� �� ������ ��� ������.");
			FNC_OUT (BX_BannerProfile, AutoOn, "���������� � ���������� ������� �� ...");
			FNC_OUT (BX_BannerProfile, AutoOff, "�� ...");
			FNC_OUT (BX_BannerProfile, RepeatCount, "������� ��� ���������� ������ � ���� �� �������.");
			FNC_OUT (BX_BannerProfile, RepeatTime, "���������� ������� ������ � ���� �� ������� �� ���� ��� ...");
			FNC_OUT (BX_BannerProfile, CountTypeByShows, "��� �����: �� ������ ��� �� �����.");
			FNC_OUT (BX_BannerProfile, MaxDailyClicks, "������������ ����� ������ � ����.");
			FNC_OUT (BX_BannerProfile, MaxDailyShows, "������������ ����� ������� � ����.");
			FNC_OUT (BX_BannerProfile, TotalShows, "���������� ������� ������� ����� �������.");
			FNC_OUT (BX_BannerProfile, TotalClicks, "���������� ������� �� ������� ����� �������.");
			FNC_OUT (BX_BannerProfile, Allowed, "���������� ������������ ��������� ����������� (������� Available).");
			FNC_OUT (BX_BannerProfile, ObjectState, "��������� �������: 0 - �������� 1 - ����� 2 - �������� ����������� ���� 3 - ������.");
      FNC        (BX_BannerProfile_PutData, "��������� ��������� ������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "������������� ������� ������� �������.");
			FNC_IN  (BX_BannerProfile, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_BannerProfile, Name, "�������� �������.");
			FNC_IN  (BX_BannerProfile, HREF, "ID �����, �� ������� ���� ������� ��� ������� �� ������.");
			FNC_IN  (BX_BannerProfile, Commercial, "�������� �� ������� ������� �������������.");
			FNC_IN  (BX_BannerProfile, Banner, "������ ��������, ������������ ������ ��������.");
			FNC_IN  (BX_BannerProfile, sBanner, "������ ��������, ������������ ������ �������� � ��������� ����.");
			FNC_IN  (BX_BannerProfile, Concept, "�������� �������.");
			FNC_IN  (BX_BannerProfile, State, "��������� (���/����).");
			FNC_IN  (BX_BannerProfile, AltText, "�������������� �����.");
			FNC_IN  (BX_BannerProfile, SiteConceptInclude, "{class:Concept}�������� ������, �� ������� ���������� ������.");
			FNC_IN  (BX_BannerProfile, SiteConceptExclude, "{class:Concept}�������� ������, �� ������� �� ���������� ������.");
			FNC_IN  (BX_BannerProfile, SiteInclude, "������ ����������� ������.");
			FNC_IN  (BX_BannerProfile, sSiteInclude, "������ ��� ����������� ������.");
			FNC_IN  (BX_BannerProfile, SiteExclude, "������ ����������� ������.");
			FNC_IN  (BX_BannerProfile, sSiteExclude, "������ ��� ����������� ������.");
			FNC_IN  (BX_BannerProfile, ViewerIPEnable, "����������� IP ��������.");
			FNC_IN  (BX_BannerProfile, ViewerIPDisable, "����������� IP ��������.");
			FNC_IN  (BX_BannerProfile, ViewerConceptInclude, "{class:Concept}�������� ��������, ������� ���������� ������.");
			FNC_IN  (BX_BannerProfile, ViewerConceptExclude, "{class:Concept}�������� ��������, ������� �� ���������� ������.");
			FNC_IN  (BX_BannerProfile, UseLocalTime, "��������� �� ���������� � ���������� ������� �������.");
			FNC_IN  (BX_BannerProfile, ScheduleTZOffset, "������� ���� ���������� (���� UseLocalTime==false).");
			FNC_IN  (BX_BannerProfile, ShowIfLocalUnknown, "���������� �� ������, ���� ��������� ����� ���������� (������������ � �������������� ScheduleTZOffset).");
			FNC_IN  (BX_BannerProfile, Schedule, "���������� - �� ���� �� ������ ��� ������.");
			FNC_IN  (BX_BannerProfile, AutoOn, "���������� � ���������� ������� �� ...");
			FNC_IN  (BX_BannerProfile, AutoOff, "�� ...");
			FNC_IN  (BX_BannerProfile, RepeatCount, "������� ��� ���������� ������ � ���� �� �������.");
			FNC_IN  (BX_BannerProfile, RepeatTime, "���������� ������� ������ � ���� �� ������� �� ���� ��� ...");
			FNC_IN  (BX_BannerProfile, CountTypeByShows, "��� �����: �� ������ ��� �� �����.");
			FNC_IN  (BX_BannerProfile, MaxDailyClicks, "������������ ����� ������ � ����.");
			FNC_IN  (BX_BannerProfile, MaxDailyShows, "������������ ����� ������� � ����.");
      FNC        (BX_BannerProfile_Delete, "�������� ��������� ������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "������������� ������� ������� �������.");
			FNC_IN  (BX_BannerProfile, objPassword, "������ ������������-��������� �������.");

   // Banner
      FNC        (BX_Banner_New, "�������� �������. ��������� OwnerID ���������, FileName �������. ������������� ���������� ������� ������������ � objID.  ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Banner, OwnerID, "{class:User}������������� ��������� �������.");
			FNC_IN  (BX_Banner, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_Banner, FileName, "��� �������, � ������� ���������� upload.");
			FNC_IN  (BX_Banner, FileSize, "������ ����� �������.");
			FNC_IN  (BX_Banner, Concept, "{class:Concept}��������, ������� ��������� � �������.");
			FNC_IN  (BX_Banner, Profile, "{class:BannerProfile}������� ������� (�� ��������� �� ����������).");
			FNC_OUT (BX_Banner, objID, "������������� ������� �������.");
      FNC        (BX_Banner_GetData, "��������� ���������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Banner, objID, "������������� ������� �������.");
			FNC_IN  (BX_Banner, objPassword, "������ ������������-��������� �������.");
			FNC_OUT (BX_Banner, OwnerID, "������������� ��������� �������.");
			FNC_OUT (BX_Banner, FileName, "��� �������, � ������� ���������� upload.");
			FNC_OUT (BX_Banner, FileSize, "������ ����� �������.");
			FNC_OUT (BX_Banner, UploadNo, "���������� ��������� �������� �����.");
			FNC_OUT (BX_Banner, CreationTime, "����� �������� �������.");
			FNC_OUT (BX_Banner, sCreationTime, "����� �������� ������� ��������� ����.");
			FNC_OUT (BX_Banner, VBN, "ID ����������� ����, � ������� ����������� ������.");
			FNC_OUT (BX_Banner, State, "��������� ������� (����/���).");
			FNC_OUT (BX_Banner, Profile, "������������� ������� �������.");
			FNC_OUT (BX_Banner, Concept, "��������, ������� ��������� � �������.");
			FNC_OUT (BX_Banner, TotalShows, "���������� ������� �������.");
			FNC_OUT (BX_Banner, TotalClicks, "���������� ������� �� ������.");
			FNC_OUT (BX_Banner, Allowed, "���������� ������������ ��������� �����������.");
			FNC_OUT (BX_Banner, ObjectState, "��������� �������: 0 - �������� 1 - ����� 2 - �������� ����������� ���� 3 - ������.");
      FNC        (BX_Banner_PutData, "��������� ���������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Banner, objID, "������������� ������� �������.");
			FNC_IN  (BX_Banner, objPassword, "������ ������������-��������� �������.");
			FNC_IN  (BX_Banner, FileName, "��� �������, � ������� ���������� upload.");
			FNC_IN  (BX_Banner, FileSize, "������ ����� �������.");
			FNC_IN  (BX_Banner, UploadNo, "���������� ��������� �������� �����.");
			FNC_IN  (BX_Banner, State, "��������� ������� (����/���).");
			FNC_IN  (BX_Banner, Profile, "{class:BannerProfile}������������� ������� �������.");
			FNC_IN  (BX_Banner, Concept, "{class:Concept}��������, ������� ��������� � �������.");
      FNC        (BX_Banner_Delete, "�������� ������� � ��������� objID. ���������� ������� ������ ������������-��������� objPassword.");
			FNC_IN  (BX_Banner, objID, "������������� ������� �������.");
			FNC_IN  (BX_Banner, objPassword, "������ ������������-��������� �������.");
   }
// ����� ������������ ������� ��� ��������� �� ������.
   FNC_END;
}
//____________________________________________________________________________[]




