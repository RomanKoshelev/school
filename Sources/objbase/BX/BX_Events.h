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
[] Description:     Структуры параметров и прототипы обработчиков событий.    []
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
	
	int				ExitCode;			// Код возврата: enum	BX_COUNTER_EXIT_CODE

	identifier		SiteID;				// ID сайта.
	string			Alias;				// Синоним ID сайта.
	int				PageNo;				// Номер страницы сайта.
	
	bool				CookieSupported;	// Поддерживается ли Cookie.
	identifier		ViewerID;			// Cookie (ID) зрителя, если Cookie поддерживается и установлен, или NA в противном случае.
	string			SiteURL;				//	URL сайта, на котором произошло событие (HTTP_REFERER).
	string			Referrer;			// URL предыдущей просмотренной в броузере страницы

	string			Charset;				// CHARSET
	string_arr		Language;			// HTTP_ACCEPT_LANGUAGE

	time_t			LocalTime;			// Местное время посетителя.
	string			ViewerIP;			// IP зрителя.
	string			ViewerHostName;	// IP зрителя.

	string			UserAgent;			// UserAgent посетителя.
	string			ScreenResolution;	// Разрешение экрана.
	string			ColorDepth;			// Глубина цвета.
	string			JavaEnabled;		// Версия Явы (0 - если она отключена).
	string			JavaScriptVersion;// Версия ЯвыСкрипта.

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

	string_arr	Keyword;			// Ключевые слова, для которых надо подобрать баннер.

	identifier	PhysType;		//	ID физического типа баннера, который надо показать на сайте.
	identifier	BannerShape;	//	ID формы баннера, который надо показать на сайте.


	identifier	BannerID;		// Здесь возвращается идентификатор баннера, который надо показывать.
	string		FileName;		// Оригинальное имя файла с баннером.
//	identifier	SiteID;			// ID сайта, на который надо перейти по клику (уже есть в BX_Event_Args).
	string		HREF;				// Здесь возвращается URL сайта, на который надо перейти	по клику.
	string		Alt;				// Здесь возвращается поле ALT для баннера.

};

//----------------------------------------------------------------------------[] 

// Возвращает в BannerID идентификатор баннера для показа (или NA в случае ошибки).
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

	identifier BannerID;				// ID кликнутого баннера.
};
//----------------------------------------------------------------------------[] 

// Эта функция должна вызываться при нажатии на баннер.
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