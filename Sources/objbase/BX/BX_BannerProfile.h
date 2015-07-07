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
[] Description:     Функции для работы с объектом "профиль баннера".          []
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

				string			Name;						// Название профиля.
	READONLY	identifier		VBN;						// ID виртуальной подсети.
	READONLY	time_t			LastModified;			// Время последнего изменения профиля (gmtime).
	READONLY	string			sLastModified;			// Время последнего изменения профиля в строковом виде.
	READONLY	identifier		OwnerID;					// Идентификатор пользователя-владельца профиля баннера.
																
				identifier		HREF;						// ID сайта, на который надо перейти при нажатии на баннер.
																
				bool				Commercial;				// Являются ли баннеры профиля коммерческими.
																
	READONLY	identifier_arr Banner;					// Список баннеров, пользующихся данным профилем.
	READONLY	string_arr		sBanner;					// Список баннеров, пользующихся данным профилем в строковом виде.
				identifier_arr Concept;					// Концепты профиля.
									
																
				bool				State;					// Состояние (вкл/выкл).
				string			AltText;					// Альтернативный текст.

// Требования к сайтам:
				identifier_arr	SiteConceptInclude;	// Концепты сайтов, на которых показывать баннер.
				identifier_arr	SiteConceptExclude;	// Концепты сайтов, на которых НЕ показывать баннер.

				identifier_arr	SiteInclude;			// Список разрешённых сайтов.
	READONLY	string_arr		sSiteInclude;			// Список имён разрешённых сайтов.
				identifier_arr	SiteExclude;			// Список запрещённых сайтов.
	READONLY	string_arr		sSiteExclude;			// Список имён запрещённых сайтов.

// Требования к зрителям:
				string_arr		ViewerIPEnable;		// Разрешённые IP зрителей.
				string_arr		ViewerIPDisable;		// Запрещённые IP зрителей.

				identifier_arr	ViewerConceptInclude;// Концепты зрителей, которым показывать баннер.
				identifier_arr	ViewerConceptExclude;// Концепты зрителей, которым НЕ показывать баннер.

// Требования ко времени показа:				
				bool				UseLocalTime;			// Применять ли расписание к локальному времени зрителя.
				time_t			ScheduleTZOffset;		// Часовой пояс расписания (если UseLocalTime==false).				
				bool				ShowIfLocalUnknown;	// Показывать ли баннер, если локальное время неизвестно
																// (показывается с использованием ScheduleTZOffset).

				bool_arr			Schedule;				// Расписание - по биту на каждый час недели.
																
				time_t			AutoOn;					// Показывать в промежутке времени от ...
				time_t			AutoOff;					// до ...
	
// Частота показа зрителю:
				int				RepeatCount;			// Сколько раз показывать одному и тому же зрителю.
				time_t			RepeatTime;				// Показывать баннеры одному и тому же зрителю не чаще чем ...

// Статистика

				bool				CountTypeByShows;	// Тип счета: на показы или на клики.
				int				MaxDailyClicks;	// Максимальное число кликов в день.
				int				MaxDailyShows;		// Максимальное число показов в день.
	READONLY	time_t			MaxDailyShowsChangeTime;//	Время последнего изменения MaxDailyShows. 

	READONLY	int				TotalShows;			// Количество показов баннера этого профиля.
	READONLY	int				TotalClicks;		// Количество нажатий на баннеры этого профиля.
															
	READONLY	int				SessionEvents;		// Число событий ShowEvent с момента 
															// последнего изменения MaxDailyShows.
																
	READONLY	float				Priority;			//	Приоритет.

	READONLY	bool				Allowed;				// Информация пользователя разрешена модератором (синоним Available).
	READONLY	int				ObjectState;		// Состояние объекта: 0 - проверен; 1 - новый; 2 - изменено критическое поле; 3 - изменён.
	READONLY	identifier_arr	ModeratorComment; // Комментарии модератора.

				identifier		objID;				// Идентификатор объекта профиля баннера.
	READONLY	identifier		objFromID;			// Идентификатор source-профиля.
				string			objPassword;		// Пароль пользователя-владельца профиля.

				int				objFirstNo;			// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;			// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

	READONLY	identifier_arr	objIDs;				// Идентификаторы объектов.
	READONLY	string_arr		objNames;			// Здесь возвращаются имена функциями *Enumerate().
};
//----------------------------------------------------------------------------[] 

// Создаёт профиль баннера для пользователя OwnerID.
// Если указан objFromID , то в созданный профиль копируются 
// параметры из профиля objFromID.
// В objID возвращается id созданного профиля.
// В Name  возвращается название созданного профиля.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_BannerProfile_New(BX_BannerProfile_Args& arg);

//	Копирование установок профиля баннера из профиля objFromID в профиль objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_BannerProfile_CopyData(BX_BannerProfile_Args& arg);

//	Получение установок профиля баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_BannerProfile_GetData(BX_BannerProfile_Args& arg);

//	Изменение установок профиля баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_BannerProfile_PutData(BX_BannerProfile_Args& arg);

//	Удаление установок профиля баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
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