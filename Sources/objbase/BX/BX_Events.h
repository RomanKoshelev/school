/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Events.h                                               []
[] Date:            05.08.99                                                  []
[] Author:          Alex Vershinin                                            []
[] Description:     ��������� ���������� � ��������� ������������ �������.    []
[] Last Modified:																					[]
[]____________________________________________________________________________[]
*/  
#ifndef BX_Events_H
#define BX_Events_H
//----------------------------------------------------------------------------[] 

enum	BX_COUNTER_EXIT_CODE
{
	CNTR_UNDEFINED			= 0,
	CNTR_OKAY				= 1,
	CNTR_WOUND				= 2,
	CNTR_WRONG_MIRROR		= 3,
	CNTR_WRONG_IP			= 4,
	CNTR_MODERATOR			= 5,
	CNTR_INVALID_COOKIE	= 6,
	CNTR_INVALID_SITE_ID = 7,

};

//______________________________________________________________________________
//                                                                            []
//` Event                                                                     []     
//                                                                            []

struct BX_Event_Args
{
	BX_Event_Args()
	{
		ExitCode				= -1;
		SiteID				= NA;
		PageNo				= 0;
		LocalTime			= 0;
		ViewerID				= NA;
		CookieSupported	= false;
	}
	
	int				ExitCode;			// ��� ��������: enum	BX_COUNTER_EXIT_CODE

	identifier		SiteID;				// ID �����.
	string			Alias;				// ������� ID �����.
	int				PageNo;				// ����� �������� �����.
	
	bool				CookieSupported;	// �������������� �� Cookie.
	identifier		ViewerID;			// Cookie (ID) �������, ���� Cookie �������������� � ����������, ��� NA � ��������� ������.
	string			SiteURL;				//	URL �����, �� ������� ��������� ������� (HTTP_REFERER).
	string			Referrer;			// URL ���������� ������������� � �������� ��������

	string			Charset;				// CHARSET
	string_arr		Language;			// HTTP_ACCEPT_LANGUAGE

	time_t			LocalTime;			// ������� ����� ����������.
	string			ViewerIP;			// IP �������.
	string			ViewerHostName;	// IP �������.

	string			UserAgent;			// UserAgent ����������.
	string			ScreenResolution;	// ���������� ������.
	string			ColorDepth;			// ������� �����.
	string			JavaEnabled;		// ������ ��� (0 - ���� ��� ���������).
	string			JavaScriptVersion;// ������ ����������.

};
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ShowEvent                                                                 []         
//                                                                            []

struct BX_ShowEvent_Args : public BX_Event_Args
{
	BX_ShowEvent_Args() {
		BannerID		= NA;
		PhysType		= NA;
		BannerShape = NA;
	}

	string_arr	Keyword;			// �������� �����, ��� ������� ���� ��������� ������.

	identifier	PhysType;		//	ID ����������� ���� �������, ������� ���� �������� �� �����.
	identifier	BannerShape;	//	ID ����� �������, ������� ���� �������� �� �����.


	identifier	BannerID;		// ����� ������������ ������������� �������, ������� ���� ����������.
	string		FileName;		// ������������ ��� ����� � ��������.
//	identifier	SiteID;			// ID �����, �� ������� ���� ������� �� ����� (��� ���� � BX_Event_Args).
	string		HREF;				// ����� ������������ URL �����, �� ������� ���� �������	�� �����.
	string		Alt;				// ����� ������������ ���� ALT ��� �������.

};

//----------------------------------------------------------------------------[] 

// ���������� � BannerID ������������� ������� ��� ������ (��� NA � ������ ������).
BX_RESULT BX_ShowEvent_New(BX_ShowEvent_Args& arg);

//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ClickEvent                                                                []          
//                                                                            []
struct BX_ClickEvent_Args: public BX_Event_Args
{
	BX_ClickEvent_Args() {
		BannerID = NA;
	}

	identifier BannerID;				// ID ���������� �������.
};
//----------------------------------------------------------------------------[] 

// ��� ������� ������ ���������� ��� ������� �� ������.
BX_RESULT BX_ClickEvent_New(BX_ClickEvent_Args&);
//----------------------------------------------------------------------------[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/