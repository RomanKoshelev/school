/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Site.h                                                 []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "����".                     []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                              
#ifndef BX_Site_H
#define BX_Site_H

//______________________________________________________________________________
//                                                                            []
//` Site                                                                      []    
//                                                                            []
struct BX_Site_Args
{ 
	BX_Site_Args()
	{
		OwnerID				= NA;
		VBN					= NA;
		CreationTime		= 0;
		CounterType			= 0;
		RateMySite			= true;
		ShowAudience		= true;
		Profile				= NA;
		objID					= NA;
		objFromID			= NA;
		Allowed				= false;
		ObjectState			= 1;

								
		objFirstNo			= 0;		
		objLastNo			= INT_MAX;
	}

	READONLY	identifier		OwnerID;						// ID ������������-��������� �����.
	READONLY	identifier		VBN;							// ID ����������� �������.
	READONLY	time_t			CreationTime;				// ����� �������� � ���� gmtime.
	READONLY	string			sCreationTime;				// ����� �������� ����� � ��������� ����.
				
				string_arr		MirrorInclude;				// ������ ������ �����.
				string_arr		MirrorExclude;				// ������ ������������ ������ �����.
				string_arr		MirrorSubstr;				// ������ ����, ������� ������������ � HTTP_REFERER ��� �������� ������.
				string_arr		IgnoredIP;					// ������ IP-�������, ���� � ������� �� ������������� (���� ��� ��������������).
				identifier_arr	IgnoredViewerID;			// ������ ID ��������, ���� � ������� �� ������������� (���� ��� ��������������).

				string			Name;							// �������� �����.
				string			Alias;						// ������� �����.
				string			Description;				// �������� (��� ��������������).
				string			URL;							// URL �����.
				
				int				CounterType;				// ��� �������� ��� ����� �����.

				bool				RateMySite;					// ��������� �� ���� ���� � �������� ������������.
				string			RateStatsViewPassword;	// ������ �� ������ � ���������� ������������ ��� ����� �����.

				bool				ShowAudience;				// ��������� �� ����������� � ��������� ����������� ���������.
				time_t			ShowAudienceOffTime;		// ����� ���������� ���������� ShowAudience.

				identifier		Profile;						// ID �������-������� �����.
				string_arr		Keyword;						// �������� ����� ��� ����� �����.
	
				identifier_arr	Concept;						// �������� �����.
	
				string_arr		PageName;					// ������ �������� ������� �����.
				int_arr			PageNo;						// ������ ������� ������� �����.

	READONLY	identifier_arr	AdBannerProfile;			// ������ ID �������� ��������, ������������� ���� ����.

	READONLY	identifier		SuspiciousInfo;			// ID (class SuspiciousInfo) ������� �� ����������� �������������� �������.

				identifier_arr	Audience_SiteID;			//	ID ������, �� ������� �������� ���������� ������� �����.
				string_arr		Audience_SiteName;		//	�������� ������, �� ������� �������� ���������� ������� �����.
				int_arr			Audience_Viewers;			//	����� ����������� �����, ���������� �� ����� ���������������� ����������.
				int_arr			Audience_Hosts;			//	���-�� ������, ������� ���������� ����� ������� �� ����� ���������������� ����������.

	READONLY	bool				Allowed;						// ���������� ������������ ��������� �����������.
	READONLY	int				ObjectState;				// ��������� �������: 0 - ��������; 1 - �����;
																	//  2 - �������� ����������� ����; 3 - ������.
				identifier		objID;						// ������������� ������� �����.
	READONLY	identifier		objFromID;					// ������������� source-�����.
				string			objPassword;				// ������ ������������-��������� �����.

				int				objFirstNo;	// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;	// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

	READONLY	identifier_arr	objIDs;		// �������������� ��������.
	READONLY	string_arr		objNames;	// ����� ������������ ����� ��������� *Enumerate().

				string			OwnerPassword;		// ������ ��������� ����������.
				string			StatsPassword;		// ������ �� ������ � ����������.
				bool				ExitCode;			// True, ���� ���� �� ���� �� ������� �������� � ���������� �����.
};
//----------------------------------------------------------------------------[]

// �������� �����. ��������� ������������� ��������� OwnerID � URL �����.
// ������������� ���������� ����� ������������ � ���� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Site_New(BX_Site_Args& arg);

// ��������� ���������� ����� � ��������� ��������������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Site_GetData(BX_Site_Args& arg);

// ��������� ���������� ����� � ��������� ��������������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Site_PutData(BX_Site_Args& arg);

//	�������� ����� � ��������� ��������������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Site_Delete(BX_Site_Args& arg);

// �������� ��� �������� ��� �����.
BX_RESULT BX_Site_GetCounterType(BX_Site_Args& arg);

// �������� ����������� ��������� ��� ������� �����.
BX_RESULT BX_Site_GetAudienceIntersect(BX_Site_Args& arg);

// !!! 
BX_RESULT BX_Site_Enumerate(BX_Site_Args& arg);

// �������� ������ �� ������ � ���������� �����.
BX_RESULT BX_Site_GetStatsPassword(BX_Site_Args& arg);

// �������� ������ �� ������ � ���������� �����.
BX_RESULT BX_Site_CheckStatsPassword(BX_Site_Args& arg);

// ��������� ID VBN �� ID �����.
BX_RESULT BX_Site_GetVBN(BX_Site_Args& arg);

// ������� ���������� �� �����. 
BX_RESULT BX_Site_GetBriefInfo(BX_Site_Args& arg);

// �������� ������� ����� �� ID.
BX_RESULT BX_Site_GetAliasByID(BX_Site_Args& arg);

// �������� ID �� �������� �����.
BX_RESULT BX_Site_GetIDByAlias(BX_Site_Args& arg);
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` SiteSuspiciousInfo                                                        []                  
//                                                                            []
struct BX_SiteSuspiciousInfo_Args
{
				string_arr		sEventType;					// ��� �������.
				string_arr		sTime;						// ����� ������������� ������� (����������).
				identifier_arr	Viewer;						// ID �������, ���������� �������.
				string_arr		IP;							// IP-�����, ��������� �������.
				string_arr		Referrer;					// URL, � �������� ������ �������.

	READONLY	identifier		objID;						// ������������� ������� �����.
	READONLY	string			objPassword;				// ������ ������������-��������� �����.

};

// �������� ���������� � �������������� ��������, ������������ �� �����.
BX_RESULT BX_SiteSuspiciousInfo_GetData(BX_SiteSuspiciousInfo_Args& arg);

//____________________________________________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/