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
[] Description:     ������� ��� ������ � �������� "���������� �����".         []
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

// ������� ������ �������:
	OC_Viewer	oc_viewer;
	oc_viewer.Open(arg.objID);
	if (!oc_viewer.IsValid())
		return BXE_Viewer_GetData_InvalidViewerID;
	

//----------------------------------------------------------------------------[] 
// ����������� ������:

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
// ������� ������ �������:	
	BX_CREATE_AND_CHECK(oc_viewer);
// �������� ������� � ������:
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

#if 0  //{ AlexV	- ���������� � UpdateViewerInfo(), ����� ������� ����, � �� ��������.
// CRA_Inquiry - �������
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

// ���� � ���� ���������� ID, �� ��������� ��� � NA:
	if ((arg.ViewerID != NA) && (!OC_Exist(OBJ_CLASS_ID_Viewer, arg.ViewerID)))
	{
//		SERVER_DEBUG_VALUE(arg.ViewerID);
		arg.ViewerID			= NA;
		arg.CookieSupported	= false;
//		arg.ExitCode			= int(CNTR_INVALID_COOKIE);
	}

// ������������� �������:
//----------------------------------------------------------------------------[] 
	if	(arg.CookieSupported == false)
// Cookie �� �������������� - ����� ������������ ����������� �� IP-������ ������:
	{
		bAnonymousViewer				= true;
		OC_ViewerReference		oc_viewer_reference;

		unsigned long Hash = arg.ViewerIP.GetCRC();
	
		oc_viewer_reference.SetIndex_IPAddressHash();
		ka.Init();
		ka += Hash;

	// ���� ������ �� ������ �� IP, �� �������� ��� :
		if (!oc_viewer_reference.Find(ka))
		{
			BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
			oc_viewer.m_Anonymous	= true;

		// ������ �� ����������:
			oc_viewer_reference.New();
			oc_viewer_reference.m_ViewerID		= oc_viewer.GetObjectID();
			oc_viewer_reference.m_IPAddress		= arg.ViewerIP;
			oc_viewer_reference.m_IPAddressHash = Hash;
			oc_viewer_reference.m_CacheTime		= CurrentTime;
		}
	// ���� ����� CRC ������, �� �������� ��� ������������:
		else
		{
		// ��������� �� IP � �������� ?
			if (string(oc_viewer_reference.m_IPAddress) != arg.ViewerIP)
			{
			// �� ��������� - ����� ������ ������ ...
				bool bFound;
			
				do
				{
				// �������� �� ���������� ���������� ������� � ����� �� CRC:
					bFound = oc_viewer_reference.GoNextSame(&ka);
				// ���� IP ��������� � ��������, �� ��� ��� �������,
				// �������� �� ���� - ������� ���, � �� �����:
					if (bFound && (string(oc_viewer_reference.m_IPAddress) == arg.ViewerIP)) {
						BX_CHECK_AND_OPEN(oc_viewer, oc_viewer_reference.m_ViewerID, OBJ_CLASS_ID_Viewer);
						break;
					}
				}while (bFound);	// ���� ���� ��� ����� �� �������� CRC ...

			// ���� ��� � �� ����� ������� � ������ IP, �� ������� ��� �������:
				if (!bFound)
				{
					BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
					oc_viewer.m_Anonymous	= true;
				// ������ �� ����������:
					oc_viewer_reference.New();
					oc_viewer_reference.m_ViewerID		= oc_viewer.GetObjectID();
					oc_viewer_reference.m_IPAddress		= arg.ViewerIP;
					oc_viewer_reference.m_IPAddressHash = Hash;
					oc_viewer_reference.m_CacheTime		= CurrentTime;
				}
			}
		// ����� ������ � ������ IP, ������� �������:
			else
			{
				BX_CHECK_AND_OPEN(oc_viewer, oc_viewer_reference.m_ViewerID, OBJ_CLASS_ID_Viewer);
			}
			
		}
	}
//----------------------------------------------------------------------------[] 
// Cookie ��������������:
	else
	{
	// ������� ��� �� ��������������� ��� ���� � ���� Cookie:
		if (arg.ViewerID == NA)	{
		// �������� ������������ ������ ��� �������.
			BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
		}
	// ������� ��������������� - ������� ��� ����������:
		else	{
			oc_viewer.Open(arg.ViewerID);
		// ���� ������� ��������������� ��� �����������, �� ������� ��� ������������ ������:
			if (bool(oc_viewer.m_Anonymous))
			{
			// �������� ������������ ������ ��� �������.
				BX_ASSERT_RETURN(CreateViewer(oc_viewer, arg, CurrentTime));
			}
		}
	// ������� �������������� �������:
		oc_viewer.m_Anonymous	= false;
	// ���� �������������� - ������ �� ���������:
		bAnonymousViewer			= false;
	}	

// ��������� � cookie ID �������:
	SERVER_DEBUG_ASSERT_RETURN(	// �������������� ������.
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
UpdateViewerInfo( OC_Viewer&			oc_viewer,		// IN:	�������� � ������������� ���������� �������.
						BX_Counter_Args&	arg,				// IN/OUT:	ID ����� / Visits, LastVisit
						time_t				CurrentTime,	// IN:	������� ����� (GMT).
						bool&					bNewVisitor,	// OUT:	�������� �� ���������� ����� ��� �����.
						bool&					bHost,			// OUT:	�������� �� ���������� ������.
						time_t&				ReturnTime)		// OUT:	����� ��������� � ���������� ����� �� ���� �����.
						
{
	int sitePos = -1;

	oc_viewer.m_IPAddress		= arg.ViewerIP;
	//oc_viewer.m_IP_Ind			= IP_2_ULONG(arg.ViewerIP);

	oc_viewer.m_LastVisitTime	= CurrentTime;
	
	if ((sitePos = oc_viewer.m_Site.Find(arg.SiteID, true)) == -1)
// ���� ������� ������ �� ���� � ������ ���
	{
		sitePos = oc_viewer.m_Site.	InsertSorted(arg.SiteID);
		oc_viewer.m_Site_Hits.			Insert(sitePos, 0);
		oc_viewer.m_Site_Hosts.			Insert(sitePos, 1);
		oc_viewer.m_Site_LastHit.		Insert(sitePos, 0);
		oc_viewer.m_Site_LastHost.		Insert(sitePos, CurrentTime);
		oc_viewer.m_Site_Votings.		Insert(sitePos, 0);
		oc_viewer.m_Site_VoteDayNo.	Insert(sitePos, 100);

	// ��������� ������� ������ ���������� � �����:
		bNewVisitor = true;
		bHost			= true;
	}
	else
// ���� ������� ��� ��� �� ���� �����
	{
	// ������� ������� ������ ����������:
		bNewVisitor = false;

	// ��������� ���� �� ��� ��� �� �����:
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
// ������ �����, ��������� � ���������� ���������:
	ReturnTime = CurrentTime - time_t(oc_viewer.m_Site_LastHit[sitePos]);

// ����� ������ ����� ���������� ��������� �����:
	arg.LastVisitTime = (time_t)oc_viewer.m_Site_LastHit[sitePos];

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// �������������� ������� ����� (�.�. ��� ������� ���������� ����� ��������
// �� �������� � ����., �� ��� ������������ ����� �����):
	oc_viewer.m_Site_Hits	[sitePos] += 1;

// ��������� ����� ����� ���������� ��������� �����:
	oc_viewer.m_Site_LastHit[sitePos] = CurrentTime;
	
// ������ ����� �����, ��������� ���� ����������� �� �����:
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


// ��������� ���������/����������:
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
	// �������� CRA_Inquiry - �������
		RegisterIP(arg.ViewerIP, oc_viewer, bHost, bNewVisitor, CurrentTime);
	// ����������� � ������� � CRN_Inquiry
		NormalizePackedArrInplace(CR);
		oc_viewer.m_CRN_Inquiry = CR;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Viewer::ReloadNum, AveReloadTime -- ������������� ��������:
	if (ReturnTime > oc_reg.m_ReloadTimeThreshold)
	{
	// �������� c������� ����� ��������:
		oc_viewer.m_AveReloadTime	= oc_viewer.m_ReloadNum*oc_viewer.m_AveReloadTime+(float)ReturnTime;
		oc_viewer.m_ReloadNum		+= 1.0;
	// ������� �� ����� �������� ��� ��������� ��������:
		if (oc_viewer.m_ReloadNum > 0.0F) {
			oc_viewer.m_AveReloadTime /= oc_viewer.m_ReloadNum;
		}
		else	{
			SERVER_DEBUG_ERROR_1 ("UpdateViewerInfo(): Zero or Negative Viewer::ReloadNum=%f", (float)oc_viewer.m_ReloadNum );
		}
	// ������������� ���������� �������������� �������� � �������:
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