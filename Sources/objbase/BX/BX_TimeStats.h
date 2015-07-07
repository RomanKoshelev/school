/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            TimeStats.h                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "временн'ая статистика".    []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#ifndef BX_TimeStats_H
#define BX_TimeStats_H

//----------------------------------------------------------------------------[]
#define TIMESTATS_DISCRETIZATION			10
#define TIMESTATS_COUNTS_IN_DAY			(MINS_IN_DAY / TIMESTATS_DISCRETIZATION	)
#define TWO_LAST_DAY_MINUTE_SIZE			(2 * TIMESTATS_COUNTS_IN_DAY					)
#define OLD_TWO_LAST_DAY_MINUTE_SIZE	2880
//----------------------------------------------------------------------------[]


//----------------------------------------------------------------------------[]
enum Time_Discretization
{
	TD_None				= 0,
	TD_Hour				= 1,
	TD_Day				= 2,
	TD_Week				= 3,
	TD_Month				= 4
};

enum Time_Aggregation
{
	TA_None				= 0,
	TA_HourOfDay		= 1,
	TA_DayOfWeek		= 2,
	TA_DayOfMonth		= 3,
	TA_MonthOfYear		= 4
};
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]` HourItem                                                                  []
[]                                                                            */
struct	HourItem
{
	int			Value;			// Число событий

	int			Hour;				// Час
	int			Day;				// День
	int			Week;				// Неделя
	int			Month;			// Месяц

	int			DayHour;			// Час				(0-23)
	int			WeekDay;			// День недели		(0-6)
	int			MonthDay;		// Число месяца	(0-30)
	int			YearMonth;		// Месяц				(0-11)
	int			Year;				// год
};
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` Функции работы со счётчиками                                              []                            
//                                                                            []
struct	BX_TimeStats_Args
{
	BX_TimeStats_Args()
	{
		idCounter			= NA;
		Increment			= 1;
		timer					= 0;	
		tm_sec				= 0;	
		tm_min				= 0;	
		tm_hour				= 0;	
		tm_day_of_month	= 0;	
		tm_mon				= 0;
		tm_year				= 0;
		tm_day_of_week		= 0;
		tm_day_of_year		= 0;
	
		Total					= 0;

		CalculateLast		= false;

		LM						= 0;
		LW						= 0;
		LD						= 0;
		LH						= 0;

		Site					= NA;
		YMax					= INT_MIN;
		YMin					= INT_MAX;
		VisitorsOnline		= 0;

		objID					= NA;
		Date_Start			= 0;
		Date_End				= 0;
		TZOffset				= 0;
		TimeAggregate		= (int)TA_None;
		TimeDescrete		= (int)TD_None;

		WeekdayLong			= false;
		MonthLong			= false;
	}	
	
	identifier	idCounter;			// << Счётчик объекта. (Если NA то прописываем ID нового объекта)
	int			Increment;			// << Увеличение счётчика

	time_t		timer;				// << Время в секундах с 1970-го года
	bool			CalculateLast;		// << Надо ли считать динамические значения.

											// << Дата и Время события по Гринвичу.
	int			tm_sec;				//		--	Seconds after minute
	int			tm_min;				//		--	Minutes after hour (0 – 59)
	int			tm_hour;				//		--	Hours after midnight (0 – 23)
	int			tm_day_of_month;	//		--	Day of month (1 – 31)
	int			tm_mon;				//		--	Month (0 – 11; January = 0)
	int			tm_year;				//		--	ГОД - 4 ЦИФРЫ, а не Year (current year minus 1900)
	int			tm_day_of_week;	//		--	Day of week (0 – 6; Sunday = 0)
	int			tm_day_of_year;	//		--	Day of year (0 – 365; January 1 = 0)

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	int			Total;				// >> Число событий за всё время.

	int			LM;					// >> Число событий за последние 30 дней.		- точность до часа.
	int			LW;					// >> Число событий за последние 7 дней.		- точность до часа.
	int			LD;					// >> Число событий за последние 24 часа.		- точность до минуты.
	int			LH;					// >> Число событий за последние 60 минут.	- точность до минуты.

//----------------------------------------------------------------------------[] 
// Для BX_TimeStats_GetData

	identifier	objID;				// ID объекта-владельца счетчика.
	string		OwnerPassword;		// Пароль владельца информации.
	string		StatsPassword;		// Пароль на доступ к статистике.
	string		Object;				// Название объекта-владельца счетчика.
	string		Counter;				// Название счетчика.
														
	time_t		Date_Start;			// Начальная дата диапазона.
	time_t		Date_End;			// Конечная дата диапазона.
	time_t		TZOffset;			// Смещение часового пояса (сек).
											
	int			TimeDescrete;		// Диcкретизация (0-None,1-Hour,2-Day,3-Week,4-Month).
	int			TimeAggregate;		// Агрегирование (0-None,1-HourOfDay,2-DayOfWeek,3-DayOfMonth,4-MonthOfYear).
											
	bool			WeekdayLong;		// Использовать длинные названия дней недели.
	bool			MonthLong;			// Использовать длинные названия месяцев.
											
											
	int_arr		Data;					// Значения выборки.
	string_arr	Labels;				// Метки значений выборки.
											
	int			ExitCode;			// Код возврата.

								
//----------------------------------------------------------------------------[] 
// Для BX_TimeStats_GetStatInfo:
	identifier	Site;					// <	Идентификатор сайта.
	string		StatsName;			// <	Название счётчика.
	string_arr	XLabel;				// > 	X-координаты.
	int_arr		YValue;				// >	Y-координаты.
	int			YMax;					// >	Максимальное значение Y-координаты.
	int			YMin;					// >	Минимальное значение Y-координаты.
	int			VisitorsOnline;	// >	Число посетителей за последние 3 минуты.

};
//----------------------------------------------------------------------------[] 

BX_RESULT	BX_TimeStats_CreateArgs	(BX_TimeStats_Args& arg);

// Получение данных из полновременного счетчика сайта.
BX_RESULT	BX_TimeStats_GetData		(BX_TimeStats_Args& arg);

BX_RESULT	BX_TimeStats_Increment	(BX_TimeStats_Args& arg);

//BX_RESULT	BX_TimeStats_GetValue	(BX_TimeStats_Args& arg);

BX_RESULT	BX_TimeStats_Delete		(BX_TimeStats_Args& arg);

BX_RESULT	BX_TimeStats_GetStatInfo(BX_TimeStats_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/