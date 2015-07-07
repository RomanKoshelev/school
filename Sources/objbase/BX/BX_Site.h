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
[] Description:     Функции для работы с объектом "сайт".                     []
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

	READONLY	identifier		OwnerID;						// ID пользователя-владельца сайта.
	READONLY	identifier		VBN;							// ID виртуальной подсети.
	READONLY	time_t			CreationTime;				// Время создания в виде gmtime.
	READONLY	string			sCreationTime;				// Время создания сайта в строковом виде.
				
				string_arr		MirrorInclude;				// Список зеркал сайта.
				string_arr		MirrorExclude;				// Список игнорируемых зеркал сайта.
				string_arr		MirrorSubstr;				// Список слов, которые игнорируются в HTTP_REFERER при проверке зеркал.
				string_arr		IgnoredIP;					// Список IP-адресов, хиты с которых не засчитываются (даже как подозрительные).
				identifier_arr	IgnoredViewerID;			// Список ID зрителей, хиты с которых не засчитываются (даже как подозрительные).

				string			Name;							// Название сайта.
				string			Alias;						// Синоним сайта.
				string			Description;				// Описание (для категоризатора).
				string			URL;							// URL сайта.
				
				int				CounterType;				// Тип счётчика для этого сайта.

				bool				RateMySite;					// Участвует ли этот сайт в рейтинге посещаемости.
				string			RateStatsViewPassword;	// Пароль на доступ к статистике посещаемости для этого сайта.

				bool				ShowAudience;				// Разрешено ли участвовать в подсчётах пересечений аудиторий.
				time_t			ShowAudienceOffTime;		// Время последнего запрещения ShowAudience.

				identifier		Profile;						// ID объекта-профиля сайта.
				string_arr		Keyword;						// Ключевые слова для этого сайта.
	
				identifier_arr	Concept;						// Концепты сайта.
	
				string_arr		PageName;					// Список названий страниц сайта.
				int_arr			PageNo;						// Список номеров страниц сайта.

	READONLY	identifier_arr	AdBannerProfile;			// Список ID профилей баннеров, рекламирующих этот сайт.

	READONLY	identifier		SuspiciousInfo;			// ID (class SuspiciousInfo) объекта со статистикой подозрительных событий.

				identifier_arr	Audience_SiteID;			//	ID сайтов, на которых побывали посетители данного сайта.
				string_arr		Audience_SiteName;		//	Названия сайтов, на которых побывали посетители данного сайта.
				int_arr			Audience_Viewers;			//	Число посетителей сайта, побывавших на сайте соответствующего конкурента.
				int_arr			Audience_Hosts;			//	Кол-во хостов, которые посетители сайта сделали на сайте соответствующего конкурента.

	READONLY	bool				Allowed;						// Информация пользователя разрешена модератором.
	READONLY	int				ObjectState;				// Состояние объекта: 0 - проверен; 1 - новый;
																	//  2 - изменено критическое поле; 3 - изменён.
				identifier		objID;						// Идентификатор объекта сайта.
	READONLY	identifier		objFromID;					// Идентификатор source-сайта.
				string			objPassword;				// Пароль пользователя-владельца сайта.

				int				objFirstNo;	// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;	// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

	READONLY	identifier_arr	objIDs;		// Идентификаторы объектов.
	READONLY	string_arr		objNames;	// Здесь возвращаются имена функциями *Enumerate().

				string			OwnerPassword;		// Пароль владельца информации.
				string			StatsPassword;		// Пароль на доступ к статистике.
				bool				ExitCode;			// True, если хотя бы один из паролей подходит к статистике сайта.
};
//----------------------------------------------------------------------------[]

// Создание сайта. Требуется идентификатор владельца OwnerID и URL сайта.
// Идентификатор созданного сайта возвращается в поле objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Site_New(BX_Site_Args& arg);

// Получение параметров сайта с указанным идентификатором objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Site_GetData(BX_Site_Args& arg);

// Изменение параметров сайта с указанным идентификатором objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Site_PutData(BX_Site_Args& arg);

//	Удаление сайта с указанным идентификатором objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Site_Delete(BX_Site_Args& arg);

// Получить тип счетчика для сайта.
BX_RESULT BX_Site_GetCounterType(BX_Site_Args& arg);

// Получить пересечение аудиторий для данного сайта.
BX_RESULT BX_Site_GetAudienceIntersect(BX_Site_Args& arg);

// !!! 
BX_RESULT BX_Site_Enumerate(BX_Site_Args& arg);

// Получить пароль на доступ к статистике сайта.
BX_RESULT BX_Site_GetStatsPassword(BX_Site_Args& arg);

// Проверка пароля на доступ к статистике сайта.
BX_RESULT BX_Site_CheckStatsPassword(BX_Site_Args& arg);

// Получение ID VBN по ID сайта.
BX_RESULT BX_Site_GetVBN(BX_Site_Args& arg);

// Краткая информация по сайту. 
BX_RESULT BX_Site_GetBriefInfo(BX_Site_Args& arg);

// Получить синоним сайта по ID.
BX_RESULT BX_Site_GetAliasByID(BX_Site_Args& arg);

// Получить ID по синониму сайта.
BX_RESULT BX_Site_GetIDByAlias(BX_Site_Args& arg);
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` SiteSuspiciousInfo                                                        []                  
//                                                                            []
struct BX_SiteSuspiciousInfo_Args
{
				string_arr		sEventType;					// Тип события.
				string_arr		sTime;						// Время возникновения события (московское).
				identifier_arr	Viewer;						// ID зрителя, вызвавшего событие.
				string_arr		IP;							// IP-адрес, вызвавший событие.
				string_arr		Referrer;					// URL, с которого пришло событие.

	READONLY	identifier		objID;						// Идентификатор объекта сайта.
	READONLY	string			objPassword;				// Пароль пользователя-владельца сайта.

};

// Получить информацию о подозрительных событиях, произошедших на сайте.
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