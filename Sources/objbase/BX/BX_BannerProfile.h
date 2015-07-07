/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_BannerProfile.h                                        []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������� �������".          []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                       
#ifndef BX_BannerProfile_H
#define BX_BannerProfile_H

//______________________________________________________________________________
//                                                                            []
//` BannerProfile                                                             []             
//                                                                            []

struct BX_BannerProfile_Args
{
	BX_BannerProfile_Args()
	{
		VBN					= NA;
		LastModified		= 0;
		OwnerID				= NA;
		HREF					= NA;
		Commercial			= false;
		State					= false;
		UseLocalTime		= true;
		RepeatCount			= -1;
		RepeatTime			=	0;
		ScheduleTZOffset	= 0;
		ShowIfLocalUnknown= true;
		AutoOn				= 0;
		AutoOff				= LONG_MAX;
		CountTypeByShows	= true;
		MaxDailyClicks		= 0;
		MaxDailyShows		= 0;
		MaxDailyShowsChangeTime=0;
		TotalShows			= 0;
		Allowed				= false;
		ObjectState			= 1;
		objID					= NA;
		objFromID			= NA;

		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}

				string			Name;						// �������� �������.
	READONLY	identifier		VBN;						// ID ����������� �������.
	READONLY	time_t			LastModified;			// ����� ���������� ��������� ������� (gmtime).
	READONLY	string			sLastModified;			// ����� ���������� ��������� ������� � ��������� ����.
	READONLY	identifier		OwnerID;					// ������������� ������������-��������� ������� �������.
																
				identifier		HREF;						// ID �����, �� ������� ���� ������� ��� ������� �� ������.
																
				bool				Commercial;				// �������� �� ������� ������� �������������.
																
	READONLY	identifier_arr Banner;					// ������ ��������, ������������ ������ ��������.
	READONLY	string_arr		sBanner;					// ������ ��������, ������������ ������ �������� � ��������� ����.
				identifier_arr Concept;					// �������� �������.
									
																
				bool				State;					// ��������� (���/����).
				string			AltText;					// �������������� �����.

// ���������� � ������:
				identifier_arr	SiteConceptInclude;	// �������� ������, �� ������� ���������� ������.
				identifier_arr	SiteConceptExclude;	// �������� ������, �� ������� �� ���������� ������.

				identifier_arr	SiteInclude;			// ������ ����������� ������.
	READONLY	string_arr		sSiteInclude;			// ������ ��� ����������� ������.
				identifier_arr	SiteExclude;			// ������ ����������� ������.
	READONLY	string_arr		sSiteExclude;			// ������ ��� ����������� ������.

// ���������� � ��������:
				string_arr		ViewerIPEnable;		// ����������� IP ��������.
				string_arr		ViewerIPDisable;		// ����������� IP ��������.

				identifier_arr	ViewerConceptInclude;// �������� ��������, ������� ���������� ������.
				identifier_arr	ViewerConceptExclude;// �������� ��������, ������� �� ���������� ������.

// ���������� �� ������� ������:				
				bool				UseLocalTime;			// ��������� �� ���������� � ���������� ������� �������.
				time_t			ScheduleTZOffset;		// ������� ���� ���������� (���� UseLocalTime==false).				
				bool				ShowIfLocalUnknown;	// ���������� �� ������, ���� ��������� ����� ����������
																// (������������ � �������������� ScheduleTZOffset).

				bool_arr			Schedule;				// ���������� - �� ���� �� ������ ��� ������.
																
				time_t			AutoOn;					// ���������� � ���������� ������� �� ...
				time_t			AutoOff;					// �� ...
	
// ������� ������ �������:
				int				RepeatCount;			// ������� ��� ���������� ������ � ���� �� �������.
				time_t			RepeatTime;				// ���������� ������� ������ � ���� �� ������� �� ���� ��� ...

// ����������

				bool				CountTypeByShows;	// ��� �����: �� ������ ��� �� �����.
				int				MaxDailyClicks;	// ������������ ����� ������ � ����.
				int				MaxDailyShows;		// ������������ ����� ������� � ����.
	READONLY	time_t			MaxDailyShowsChangeTime;//	����� ���������� ��������� MaxDailyShows. 

	READONLY	int				TotalShows;			// ���������� ������� ������� ����� �������.
	READONLY	int				TotalClicks;		// ���������� ������� �� ������� ����� �������.
															
	READONLY	int				SessionEvents;		// ����� ������� ShowEvent � ������� 
															// ���������� ��������� MaxDailyShows.
																
	READONLY	float				Priority;			//	���������.

	READONLY	bool				Allowed;				// ���������� ������������ ��������� ����������� (������� Available).
	READONLY	int				ObjectState;		// ��������� �������: 0 - ��������; 1 - �����; 2 - �������� ����������� ����; 3 - ������.
	READONLY	identifier_arr	ModeratorComment; // ����������� ����������.

				identifier		objID;				// ������������� ������� ������� �������.
	READONLY	identifier		objFromID;			// ������������� source-�������.
				string			objPassword;		// ������ ������������-��������� �������.

				int				objFirstNo;			// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;			// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

	READONLY	identifier_arr	objIDs;				// �������������� ��������.
	READONLY	string_arr		objNames;			// ����� ������������ ����� ��������� *Enumerate().
};
//----------------------------------------------------------------------------[] 

// ������ ������� ������� ��� ������������ OwnerID.
// ���� ������ objFromID , �� � ��������� ������� ���������� 
// ��������� �� ������� objFromID.
// � objID ������������ id ���������� �������.
// � Name  ������������ �������� ���������� �������.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_BannerProfile_New(BX_BannerProfile_Args& arg);

//	����������� ��������� ������� ������� �� ������� objFromID � ������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_BannerProfile_CopyData(BX_BannerProfile_Args& arg);

//	��������� ��������� ������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_BannerProfile_GetData(BX_BannerProfile_Args& arg);

//	��������� ��������� ������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_BannerProfile_PutData(BX_BannerProfile_Args& arg);

//	�������� ��������� ������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_BannerProfile_Delete(BX_BannerProfile_Args& arg);

// !!!
BX_RESULT BX_BannerProfile_Enumerate(BX_BannerProfile_Args& arg);
//____________________________________________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/