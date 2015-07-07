/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            TimeStats.cpp                                             []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "временн'ая статистика".    []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                  

#define USES_BX_Errors
#define USES_BX_TimeStats
#define USES_BX_Macros
#define USES_BX_Date
#define USES_BX_SingleObject
#define USES_BX_Stats
#define USES_BX_Admin

#define USES_OC_TimeStats
#define USES_OC_YearStats
#define USES_OC_DayStats
#define USES_OC_Site
#define USES_OC_ShowEvent
#define USES_OC_User
#define USES_OC_Registry
#define USES_OC_IPRecord

#include "BX.h"

//______________________________________________________________________________
//                                                                            []
//` BX_TimeStats_CreateArgs                                                   []                       
//                                                                            []
// Заполняет поля tm_* структуры BX_TimeStats_Args по полю timer.             []
BX_RESULT
BX_TimeStats_CreateArgs(BX_TimeStats_Args& arg)
{
	if(arg.timer < 0)
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_CreateArgs(): Negative timer supplied (%li).",
			arg.timer);
		arg.tm_hour					= -1;
		arg.tm_day_of_month		= -1;
		arg.tm_min					= -1;
		arg.tm_mon					= -1;
		arg.tm_sec					= -1;
		arg.tm_day_of_week		= -1;
		arg.tm_day_of_year		= -1;
		arg.tm_year					= -1;

		return BX_SYSTEM_ERROR;
	}
	
	struct tm *	ptmStruct = gmtime (&arg.timer);

	arg.tm_hour					= ptmStruct->tm_hour;
	arg.tm_day_of_month		= ptmStruct->tm_mday;
	arg.tm_min					= ptmStruct->tm_min;
	arg.tm_mon					= ptmStruct->tm_mon;
	arg.tm_sec					= ptmStruct->tm_sec;
	arg.tm_day_of_week		= ptmStruct->tm_wday;
	arg.tm_day_of_year		= ptmStruct->tm_yday;
	arg.tm_year					= ptmStruct->tm_year + 1900;

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Статистика за последний ...                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/

//______________________________________________________________________________
//                                                                            []
//` Значение счётчика за N последних часов:                                   []
//                                                                            []
int BX_TimeStats_GetLastHours (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg, int nHours)
{
	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastHours(%d): Invalid TimeStats for site #lu.", nHours, arg.Site);
		return 0;
	}
	SERVER_DEBUG_ASSERT_RETURN ((nHours<=24) && (nHours>0), "BX_TimeStats_GetLastHours: Выход за пределы минутного счётчика", 0);

// Индекс минуты, соответствующей времени за час до запроса.
	int			nMinuteIndex			= (MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min - MINS_IN_HOUR*nHours + 1)
													/ TIMESTATS_DISCRETIZATION;
	int			LastMinuteIndex		= nMinuteIndex+MINS_IN_HOUR*nHours / TIMESTATS_DISCRETIZATION;
	const int * pTwoLastDaysMinute	= oc_time_stats.m_TwoLastDaysMinute.GetPtr();
	int			nRes						= 0;

	for (int i=nMinuteIndex; i < LastMinuteIndex; i++)
	{
		nRes += pTwoLastDaysMinute[i];
	}

	return nRes;
}
//______________________________________________________________________________
//                                                                            []
//` Значение счётчика за последние N дней:                                    []                                      
//                                                                            []
int BX_TimeStats_GetLastNDays(const	OC_TimeStats&			oc_time_stats,
										const	OC_YearStats&			oc_year_stats,
												BX_TimeStats_Args&	arg,
												int						nDays)
{
	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(%d): Invalid TimeStats for site #lu.", nDays, arg.Site);
		return 0;
	}

	if (!oc_year_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(%d): Invalid YearStats for site #lu.", nDays, arg.Site);
		return 0;
	}
	
	int		nRes			= 0;

	int_arr	Year_arr	(nDays);
	int_arr	Day_arr	(nDays);

	int 	cur_YearDay = YearDayToInt (arg.tm_year, arg.tm_day_of_year);
	int   i;
	int	yd;

	for (i=nDays-1, yd=cur_YearDay; yd > (cur_YearDay-nDays); yd--, i--)
	{
		IntToYearDay (yd, Year_arr[i], Day_arr[i]);
	}

//----------------------------------------------------------------------------[] 
// Находим сумму за последние полные nDays

	OC_YearStats	oc_prev_year_stats;				// Контроллер для предыдущего года.

	for (i = 0; i < nDays; i++)
	{
		if (Year_arr[i] == arg.tm_year)				// Если год тот же, то сложим с очередным днем.
		{
			nRes += oc_year_stats.m_DayTotal[Day_arr[i]];
		}
		else if ((Year_arr[i]+1) == arg.tm_year)	// Если год предыдущий, то откроем 
		{														// контроллер предыдущего года.
			if (!oc_prev_year_stats.IsValid())
			{
				int nYearIndex = oc_time_stats.m_Year.Find (Year_arr[i]);
				if (nYearIndex != -1)					// Статистика за предыдущий год найдена.
				{
				// Откроем контроллер предыдущего года:
					oc_prev_year_stats.Open (oc_time_stats.m_YearStats[nYearIndex]);
				// Поругаемся, если ID не валидный:
					if (!oc_prev_year_stats.IsValid()) 
					{
						SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(): Invalid YearStats ID=%lu (Year=%d).",
							(unsigned long)(oc_time_stats.m_YearStats[nYearIndex]), Year_arr[i]);
						break;
					}
				}

			// Сложим с очередным днем:
				nRes += oc_prev_year_stats.m_DayTotal[Day_arr[i]];

			}	// Предыдущий год не найден в статистике -- ну и не надо, считаем, что там нули.
		}
		else // Такого года не может быть.
		{
			SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetLastNDays: Выход за пределы предыдущего года.", Year_arr[i]);
		}
	}


//----------------------------------------------------------------------------[] 
// Прибавляем часы из первого дня:

	int RestInt = cur_YearDay - nDays;				// Номер первого дня.
	int RestDay,  RestYear;
	IntToYearDay (RestInt, RestYear, RestDay);	// Год и порядковый номер первого дня.
	

	OC_DayStats		oc_day_stats;

	if (RestYear == arg.tm_year)	// Год тот же -- годовой контроллер уже открыт.
	{
		if (oc_year_stats.m_DayStats[RestDay] != NA)	// Есть статистика за нужный день.
		{
		// Откроем статистику за нужный день:
			oc_day_stats.Open(oc_year_stats.m_DayStats[RestDay]);

			if (oc_day_stats.IsValid())
			{
			// Просуммируем в последнем дне значения часов, начиная с текущего и до конца дня:
				const int * oc_day_stats_m_HourTotal = oc_day_stats.m_HourTotal.GetPtr();
				for (int i = arg.tm_hour+1 ; i < HOURS_IN_DAY; i++) 
				{
					nRes +=	oc_day_stats_m_HourTotal[i];
				}
			// Сделаем поправку на неполный текущий час
			// (добавим не весь час, а нужную долю от него):
				nRes += oc_day_stats_m_HourTotal[arg.tm_hour]			// текущий час
							* (MINS_IN_HOUR-arg.tm_min) / MINS_IN_HOUR;	// доля
			}
		// Поругаемся, если кривой ID:
			else
			{
				SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays: Invalid DayStats[%d] ID=%lu. Skipped.",
					RestDay, (unsigned long)(oc_year_stats.m_DayStats[RestDay]));
			}
	
		}	
		// Нет статистики за нужный день -- ну и пусть, нам же легче ;)
	}
	else if ((RestYear+1) == arg.tm_year)	// Год -- предыдущий, надо открыть
	{													// соответствующий годовой контроллер.
		
		int nYearIndex = oc_time_stats.m_Year.Find (RestYear);

	// Есть статистика за предыдущий год:
		if (nYearIndex != -1)
		{
		// Откроем контроллер, если нужно:
			if (!oc_prev_year_stats.IsValid()) {
				oc_prev_year_stats.Open (oc_time_stats.m_YearStats[nYearIndex]);
			}
			if (oc_prev_year_stats.IsValid())
			{
			// Если есть статистика за нужный день:
				if (oc_prev_year_stats.m_DayStats[RestDay] != NA)
				{
					oc_day_stats.Open(oc_prev_year_stats.m_DayStats[RestDay]);
					if (oc_day_stats.IsValid())
					{
					// Просуммируем в последнем дне значения часов, начиная с текущего и до конца дня:
						const int * oc_day_stats_m_HourTotal = oc_day_stats.m_HourTotal.GetPtr();
						
						for (int i = arg.tm_hour+1 ; i < HOURS_IN_DAY; i++) {
							nRes +=	oc_day_stats_m_HourTotal[i];
						}
					// Сделаем поправку на неполный текущий час
					// (добавим не весь час, а нужную долю от него):
						nRes += oc_day_stats_m_HourTotal[arg.tm_hour]		// час
								* (MINS_IN_HOUR-arg.tm_min) / MINS_IN_HOUR;	// доля
					}
				}
			}
			else
			{
				SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(): Invalid YearStats ID=%lu, Year=%d.",
					(unsigned long)(oc_time_stats.m_YearStats[nYearIndex]), RestYear);
			}
		}
	// Нет статистики за предыдущий год -- считаем её нулевой.
	}
	else	// Такого года не должно быть - поругаемся:
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetLastNDays: Выход за пределы предыдущего года %d.",arg.tm_year);
	}


	return nRes;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Значение счётчика за последний час:                                       []                                   
BX_RESULT BX_TimeStats_GetLastHour (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg)
{
	arg.LH = BX_TimeStats_GetLastHours (oc_time_stats, arg, 1);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` Значение счётчика за последний день:                                      []                                    
BX_RESULT BX_TimeStats_GetLastDay (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg)
{
	arg.LD = BX_TimeStats_GetLastHours (oc_time_stats, arg, 24);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` Значение счётчика за последний месяц:                                     []                                     
BX_RESULT
BX_TimeStats_GetLastWeek ( const	OC_TimeStats&			oc_time_stats,
									const	OC_YearStats&			oc_year_stats,
											BX_TimeStats_Args&	arg)
{
	arg.LW = BX_TimeStats_GetLastNDays (oc_time_stats, oc_year_stats, arg, DAYS_IN_WEEK);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` Значение счётчика за последний месяц:                                     []                                     
BX_RESULT
BX_TimeStats_GetLastMonth( const	OC_TimeStats&			oc_time_stats,
									const	OC_YearStats&			oc_year_stats,
											BX_TimeStats_Args&	arg)
{
	arg.LM = BX_TimeStats_GetLastNDays (oc_time_stats, oc_year_stats, arg, DAYS_IN_MONTH);
	return BX_OK;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]` RecodeTimeStatsFormat                                                     []                     
[]                                                                            */
// Используется тольк
void RecodeTimeStatsFormat (OC_TimeStats& oc_time_stats)
{
	if (!oc_time_stats.IsValid())
		return;
	if (oc_time_stats.m_TwoLastDaysMinute.Size() == TWO_LAST_DAY_MINUTE_SIZE)
		return;
	if (oc_time_stats.m_TwoLastDaysMinute.Size() != OLD_TWO_LAST_DAY_MINUTE_SIZE)
	{
		SERVER_DEBUG_ERROR_1 ("RecodeTimeStatsFormat(): Unknown TwoLastDaysMinute size encountered: %d. Cleared.",
			oc_time_stats.m_TwoLastDaysMinute.Size());
		
		oc_time_stats.m_TwoLastDaysMinute.Alloc (TWO_LAST_DAY_MINUTE_SIZE, 0);

		return;
	}

	SERVER_DEBUG_TEXT ("RecodeTimeStatsFormat().");

// Переформатируем TimeStats::TwoLastDaysMinute[]

	int_arr		New_TwoLastDaysMinute;
	New_TwoLastDaysMinute.Alloc(TWO_LAST_DAY_MINUTE_SIZE, 0);

	const int * pOldTwoLastDaysMinute = oc_time_stats.m_TwoLastDaysMinute.GetPtr();
	
	for (int i = 0; i < OLD_TWO_LAST_DAY_MINUTE_SIZE; i++)
	{
		New_TwoLastDaysMinute[i/TIMESTATS_DISCRETIZATION] += pOldTwoLastDaysMinute[i];
	}
	
	oc_time_stats.m_TwoLastDaysMinute.CopyFrom (New_TwoLastDaysMinute);

	return;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_TimeStats_Increment                                                    []                      
[]                                                                            []
[]____________________________________________________________________________[]
[] Функция для инкремента счётчика типа TimeStats.										[]
[] Функции необходимо передать идентификатор объекта класса TimeStats,			[]
[] который может быть равен NA, в этом случае будет создан новый объект.		[]
[]	Значение счётчика после инкремента возвращается в CounterValue.				[]
[]____________________________________________________________________________*/
BX_RESULT BX_TimeStats_Increment (BX_TimeStats_Args& arg)
{	
	int i;

	//----------------------------------------------------------------------------[] 
	// Проверка входных аргументов
	SERVER_DEBUG_ASSERT_RETURN(
		(arg.tm_min >= 0) && (arg.tm_min < MINS_IN_HOUR),
		"BX_TimeStats_Increment(): Invalid minute index or HourStats::MinuteStats[].",
		BX_SYSTEM_ERROR);

	SERVER_DEBUG_ASSERT_RETURN(
		(arg.tm_day_of_year >= 0) && (arg.tm_day_of_year < REAL_DAYS_IN_YEAR(arg.tm_year)),
		"BX_TimeStats_Increment(): Invalid day index or YearStats::DayStats[].",
		BX_SYSTEM_ERROR);

	SERVER_DEBUG_ASSERT_RETURN(
		(arg.tm_hour >= 0) && (arg.tm_hour < HOURS_IN_DAY),
		"BX_TimeStats_Increment(): Invalid hour index or DayStats::HourStats[].",
		BX_SYSTEM_ERROR);
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// Создание или открытие головного объекта статистики:
	//
	OC_TimeStats oc_time_stats; 
	if (arg.idCounter == NA)
	{
	// Создаём объект головной статистики
		oc_time_stats.New ();
	// Выделить память в TWO_LAST_DAY_MINUTE_SIZE элементов (TIMESTATS_DISCRETIZATION-тиминутные интервалы за 2 суток)
		oc_time_stats.m_TwoLastDaysMinute.Alloc (TWO_LAST_DAY_MINUTE_SIZE, 0);

	// Запомнаем первый день минутного буфера
		oc_time_stats.m_TwoLastDaysMinute_year				
			= arg.tm_day_of_year==0? arg.tm_year-1	:	arg.tm_year;
		oc_time_stats.m_TwoLastDaysMinute_day_of_year
			= arg.tm_day_of_year==0? LAST_DAY_OF_YEAR(arg.tm_year-1)	: (arg.tm_day_of_year-1);

	// Запомнаем ID головного объекта статистики
		arg.idCounter = oc_time_stats.GetObjectID ();
	}
	else
	{
	// Открываем объект головной статистики 
		oc_time_stats.Open(arg.idCounter);
	
	// Проверяем существование объекта головной статистики 
		if (!oc_time_stats.IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("BX_TimeStats_Increment(): Invalid TimeStats ID: %lu", arg.idCounter);
			return BX_SYSTEM_ERROR;
		}

	// Проверяем формат TimeStats
		if (oc_time_stats.m_TwoLastDaysMinute.Size() != TWO_LAST_DAY_MINUTE_SIZE)
		{
			RecodeTimeStatsFormat (oc_time_stats);
		}
	}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	oc_time_stats.m_LastAccessTime = time_0;
	//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
// Открытие контроллера годовой статистики
//
	int nYearIndex = oc_time_stats.m_Year.Find (arg.tm_year);
	OC_YearStats	oc_year_stats;

	if (nYearIndex == -1)	// Если статистики за этот год ещё нет, то создадим её:
	{
		nYearIndex = oc_time_stats.m_Year.Add (arg.tm_year) - 1;
		oc_time_stats.m_YearStats.Add (NA);

	// Создать объект годовой статистики:
		oc_year_stats.New ();

	// Выделить столько дней, сколько нужно для того, чтобы поместился сегодняшний день
//		oc_year_stats.m_DayTotal.Alloc (REAL_DAYS_IN_YEAR(arg.tm_year), 0);
//		oc_year_stats.m_DayStats.Alloc (REAL_DAYS_IN_YEAR(arg.tm_year), NA);
		
		oc_year_stats.m_DayTotal.Alloc (arg.tm_day_of_year+1, 0);
		oc_year_stats.m_DayStats.Alloc (arg.tm_day_of_year+1, NA);
		
		
	// Добавить в головную статистику ссылку на новый объект годовой статистики:
		oc_time_stats.m_YearStats [nYearIndex] = oc_year_stats.GetObjectID();
	}
	else							// Статистика за этот год есть, откроем её:
	{
		oc_year_stats.Open(oc_time_stats.m_YearStats[nYearIndex]);
		if (!oc_year_stats.IsValid())
		{
			SERVER_DEBUG_ERROR_2("BX_TimeStats_Increment(): Invalid TimeStats::YearStats[Year=%d]=%lu.",
				arg.tm_year, (unsigned long)(oc_time_stats.m_YearStats[nYearIndex]));
			return BX_SYSTEM_ERROR;
		}
		
	// Проверяем число дней в годовой статистике 
		if (oc_year_stats.m_DayTotal.Size() != (arg.tm_day_of_year+1))
			oc_year_stats.m_DayTotal.Realloc (arg.tm_day_of_year+1, 0);
		if (oc_year_stats.m_DayStats.Size() != (arg.tm_day_of_year+1))
			oc_year_stats.m_DayStats.Realloc (arg.tm_day_of_year+1, NA);
	}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	oc_year_stats.m_LastAccessTime = time_0;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	// Создание или открытие объекта дневной статистики:
	//
	OC_DayStats	oc_day_stats;

	if (arg.Increment != 0)
	{
		if (oc_year_stats.m_DayStats[arg.tm_day_of_year] == NA)
		{
		// Проверяем, что счётчик пока нулевой.
			if (oc_year_stats.m_DayTotal[arg.tm_day_of_year]!=0)
			{
				SERVER_DEBUG_ERROR ("Счётчик для нового дня в году не равен нулю.");
				oc_year_stats.m_DayTotal[arg.tm_day_of_year] = 0;
			}

		// Создать объект дневной статистики:
			oc_day_stats.New ();
			oc_day_stats.m_HourTotal.Alloc (HOURS_IN_DAY, 0);
		// Добавить ссылку на новый объект дневной статистики:
			oc_year_stats.m_DayStats[arg.tm_day_of_year] = oc_day_stats.GetObjectID();
		}
		else	// Объект есть -- откроем его:
		{
			oc_day_stats.Open(oc_year_stats.m_DayStats[arg.tm_day_of_year]);

			if (!oc_day_stats.IsValid())
			{
				SERVER_DEBUG_ERROR_2 ("BX_TimeStats_Increment(): Invalid YearStats::DayStats[day_of_year=%d]=%lu.",
					arg.tm_day_of_year, (unsigned long)(oc_year_stats.m_DayStats[arg.tm_day_of_year]));
				return BX_SYSTEM_ERROR;
			}
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
		oc_day_stats.m_LastAccessTime = time_0;
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	// Проверяем число часов в дневной статистике 
		SERVER_DEBUG_ASSERT_RETURN(
			oc_day_stats.m_HourTotal.Size() == HOURS_IN_DAY,
			"BX_TimeStats_Increment(): Invalid hour index or DayStats::HourStats[].",
			BX_SYSTEM_ERROR);
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// Нахождение индекса в минутах за последнии два дня и 
	// корректировка буфера минут. 
	int nMinuteIndex = -1;

	const int DAY_UNKNOWN	=-1;
	const int DAY_PAST		= 0;
	const int DAY_FIRST     = 1;
	const int DAY_CURRENT   = 2;
	const int DAY_NEXT      = 3;
	const int DAY_FUTURE    = 4;

	int cur_day = DAY_UNKNOWN;
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// Находим дескриптор ситуации
	//
	//	.......]  [первый день][день последнего обновления]  [следующий день]  [........
	//	 PAST         FIRST             CURRENT                  NEXT            FUTURE
	//
	//
	int BUFFER_YEARDAY	= YearDayToInt (oc_time_stats.m_TwoLastDaysMinute_year,	oc_time_stats.m_TwoLastDaysMinute_day_of_year);
	int cur_YearDay		= YearDayToInt (arg.tm_year,										arg.tm_day_of_year);

	cur_day =	cur_YearDay <  BUFFER_YEARDAY		? DAY_PAST		: 
					cur_YearDay == BUFFER_YEARDAY		? DAY_FIRST		: 
					cur_YearDay == BUFFER_YEARDAY+1	? DAY_CURRENT  :
					cur_YearDay == BUFFER_YEARDAY+2	? DAY_NEXT		:
					cur_YearDay >  BUFFER_YEARDAY+2	? DAY_FUTURE	: DAY_UNKNOWN;

	if (cur_day == DAY_UNKNOWN)
	{
		SERVER_DEBUG_ERROR_4 ("Не нашли позицию в буфере минутного счётчика: текущая дата = [%d.%d], первый день буффера = [%d.%d]",
			arg.tm_year, arg.tm_day_of_year, (int)oc_time_stats.m_TwoLastDaysMinute_year, (int)oc_time_stats.m_TwoLastDaysMinute_day_of_year);
		cur_day = DAY_PAST;
	}
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// Обрабатываем ситуацию
	// И находим индекс минут nMinuteIndex
	switch (cur_day)
	{
	// Приписка задним числом
		case DAY_PAST:
		{
		// Индекс минуты в буфере не определён.
			SERVER_DEBUG_ERROR ("Incrementing in the past. Nothing done");
			nMinuteIndex = -1;
			break;
		}

	// Приписка задним числом в предыдущий день
		case DAY_FIRST:
		{
		// Индекс минуты в буфере
			//SERVER_DEBUG_ERROR ("Приписка задним числом (DAY_FIRST).");
			nMinuteIndex = arg.tm_hour*MINS_IN_HOUR + arg.tm_min;
			break;
		}

	// Событие пришло в тот же день, что и предыдущее
		case DAY_CURRENT:
		{
		// Индекс минуты в буфере
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;
			break;
		}

	// Событие пришло на сдедующий день после предыдущего события
		case DAY_NEXT:
		{
		// Перемещаем события "текущего" дня в день предыдущий (первый в буфере)
		// И обнуляем день текущий.
			for (i = 0; i < TIMESTATS_COUNTS_IN_DAY; i++)
			{
				oc_time_stats.m_TwoLastDaysMinute [i]	
					= oc_time_stats.m_TwoLastDaysMinute [i+MINS_IN_DAY];
				oc_time_stats.m_TwoLastDaysMinute [i+TIMESTATS_COUNTS_IN_DAY]
					= 0;
			}

		// Индекс минуты в буфере.
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;

		// Меняем дату буфера.
			if (arg.tm_day_of_year==0)
			{
				oc_time_stats.m_TwoLastDaysMinute_year				= arg.tm_year-1;
				oc_time_stats.m_TwoLastDaysMinute_day_of_year	= LAST_DAY_OF_YEAR (arg.tm_year-1);
			}
			else
			{
				oc_time_stats.m_TwoLastDaysMinute_year				= arg.tm_year;
				oc_time_stats.m_TwoLastDaysMinute_day_of_year	= arg.tm_day_of_year-1;
			}
			break;
		}

	// Событие пришло более чем через один день после предыдущего события
		case DAY_FUTURE:
		{
		// Обнуляем буфер минут.
			for (i = 0; i < 2*TIMESTATS_COUNTS_IN_DAY; i++)
			{
				oc_time_stats.m_TwoLastDaysMinute [i]	= 0;
			}

		// Индекс минуты в буфере.
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;

		// Меняем дату буфера.
			if (arg.tm_day_of_year==0)
			{
				oc_time_stats.m_TwoLastDaysMinute_year				= arg.tm_year-1;
				oc_time_stats.m_TwoLastDaysMinute_day_of_year	= LAST_DAY_OF_YEAR (arg.tm_year-1);
			}
			else
			{
				oc_time_stats.m_TwoLastDaysMinute_year				= arg.tm_year;
				oc_time_stats.m_TwoLastDaysMinute_day_of_year	= arg.tm_day_of_year-1;
			}
			break;
		}	
	}
	//----------------------------------------------------------------------------[] 







	//----------------------------------------------------------------------------[] 
	// Увеличиваем счётчики
	if (arg.Increment!=0)
	{
	// Инкремент основного счётчика:
		oc_time_stats.m_Total									+= arg.Increment;

	// Инкремент дневного счётчика:
		oc_year_stats.m_DayTotal[arg.tm_day_of_year]		+= arg.Increment;

	// Инкремент часового счётчика:
		oc_day_stats.m_HourTotal[arg.tm_hour]				+= arg.Increment;

	// Инкремент минутного счётчика:
		if ((nMinuteIndex < 0) || (nMinuteIndex >= (2*MINS_IN_DAY)))
		{
			SERVER_DEBUG_ERROR_2 ("Инкремент минутного счётчика: индекс минут вышел за рамки двух суток: %d (Max=%d).",
				nMinuteIndex, 2*MINS_IN_DAY);
		}
		else
		{
		// Переведем минуты в десятки минут:
			nMinuteIndex /= TIMESTATS_DISCRETIZATION;
			oc_time_stats.m_TwoLastDaysMinute[nMinuteIndex]	+= arg.Increment;
		}
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// Если надо -- считаем динамические значения
	if (arg.CalculateLast)
	{
	// Возвратим значение счётчика за последний час:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastHour	(oc_time_stats, arg));

	// Возвратим значение счётчика за последний день:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastDay		(oc_time_stats, arg));

	// Возвратим значение счётчика за последнюю неделю:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastWeek	(oc_time_stats, oc_year_stats, arg));

	// Возвратим значение счётчика за последний месяц:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastMonth	(oc_time_stats, oc_year_stats, arg));
	}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	// Возвратим общее значение счётчика:
	arg.Total		= oc_time_stats.m_Total;

	return BX_OK;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]` BX_TimeStats_Delete                                                       []                     
[]                                                                            []
[]--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- []
[] Description:  Удаление счётчика arg.idCounter.                             []
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT BX_TimeStats_Delete(BX_TimeStats_Args& arg)
{
	int i=0, j=0;

	if (arg.idCounter == NA) {
		return BX_OK;
	}

	OC_TimeStats	oc_time_stats;
	OC_YearStats	oc_year_stats;
	OC_DayStats		oc_day_stats;

	oc_time_stats.Open(arg.idCounter);
	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_Delete(): Invalid TimeStats ID: %lu", arg.idCounter);
		return BX_SYSTEM_ERROR;
	}

// Для каждого года:
	for (i = 0; i < oc_time_stats.m_YearStats.Size(); i++)
	{
		if (oc_time_stats.m_YearStats[i] != NA)
		{
			BX_CHECK_AND_OPEN(oc_year_stats, oc_time_stats.m_YearStats[i], OBJ_CLASS_ID_YearStats);

		// Для каждого дня:
			for (j = 0; j < oc_year_stats.m_DayStats.Size(); j++)
			{
				if (oc_year_stats.m_DayStats[j] != NA)
				{
					oc_day_stats.Delete(oc_year_stats.m_DayStats[j]);
					oc_year_stats.m_DayStats[j] = NA;			// На всякий пожарный
				}
			} // end for (j

			oc_year_stats.Delete();
			oc_time_stats.m_YearStats.Del(i);					// На всякий пожарный
			oc_time_stats.m_Year.Del(i);

		} // end if (oc_time_stats
	} // end for (i

	oc_time_stats.Delete();

	arg.idCounter = NA;												// На всякий пожарный
	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_TimeStats_GetStatInfo                                                  []
//                                                                            []
BX_RESULT BX_TimeStats_GetStatInfo (BX_TimeStats_Args& arg)
{
	OC_Site	oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.Site, OBJ_CLASS_ID_Site);

	if			(arg.StatsName == "Visitors"			) arg.idCounter = oc_site.m_Visitors;
	else if	(arg.StatsName == "Hosts"				) arg.idCounter = oc_site.m_Hosts;
	else if	(arg.StatsName == "Shows"				) arg.idCounter = oc_site.m_Shows;
	else if	(arg.StatsName == "Clicks"				) arg.idCounter = oc_site.m_Clicks;
	else if	(arg.StatsName == "Hits"				) arg.idCounter = oc_site.m_Hits;
	else if	(arg.StatsName == "AnonymousHits"	) arg.idCounter = oc_site.m_AnonymousHits;
	else if	(arg.StatsName == "SuspiciousHits"	) arg.idCounter = oc_site.m_SuspiciousHits;
	else if	(arg.StatsName == "Loads"				) arg.idCounter = oc_site.m_Loads;
	else if	(arg.StatsName == "SessionTime"		) arg.idCounter = oc_site.m_SessionTime;
	else
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetStatInfo(): Unknown counter %s.", arg.StatsName.c_str());
		return BX_SYSTEM_ERROR;
	}

	arg.timer = time_0;
	BX_ASSERT_RETURN (BX_TimeStats_CreateArgs	(arg));
	
//	arg.CalculateLast = false;
//	arg.Increment		= 0;
//	BX_ASSERT_RETURN (BX_TimeStats_Increment	(arg));			// Update

	OC_TimeStats	oc_time_stats;
	oc_time_stats.Open(arg.idCounter);
	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetStatInfo(): Invalid TimeStats ID: %lu", arg.idCounter);
		return BX_SYSTEM_ERROR;
	}

// Проверяем формат TimeStats
	if (oc_time_stats.m_TwoLastDaysMinute.Size() != TWO_LAST_DAY_MINUTE_SIZE)
	{
		RecodeTimeStatsFormat (oc_time_stats);
	}
	
	const int	*pMinuteArr = oc_time_stats.m_TwoLastDaysMinute.GetPtr();

	arg.YValue.Alloc(TIMESTATS_COUNTS_IN_DAY);
	arg.XLabel.Alloc(TIMESTATS_COUNTS_IN_DAY);

	int	FirstMinuteIndex	= (arg.tm_min + (arg.tm_hour*MINS_IN_HOUR) + 1) / TIMESTATS_DISCRETIZATION;
	int	LastMinuteIndex	= FirstMinuteIndex + TIMESTATS_COUNTS_IN_DAY;

	int	HourCount			= arg.tm_hour + (SERVER_TIME_ZONE_OFFSET/SECS_IN_HOUR);
	int	MinuteCount			= (arg.tm_min / 10) * 10;

	string	Str;
	int		Index = 0;

	for (int i = FirstMinuteIndex; i < LastMinuteIndex; i ++)
	{
		Str.Format("%02d:%02d", HourCount, MinuteCount);
		arg.YValue[Index] = pMinuteArr[i];
		arg.XLabel[Index]	= Str;

		if (arg.YMax < pMinuteArr[i])
			arg.YMax = pMinuteArr[i];
		if (arg.YMin > pMinuteArr[i])
			arg.YMin = pMinuteArr[i];

		MinuteCount += TIMESTATS_DISCRETIZATION;
		Index ++;

		if (MinuteCount >= MINS_IN_HOUR)
		{
			MinuteCount -= MINS_IN_HOUR;
			HourCount ++; 
		}
		
		if (HourCount >= HOURS_IN_DAY)
		{
			HourCount -= HOURS_IN_DAY;
		}
	}

// Число посетителей за последние 3 минуты:
	OC_ShowEvent	oc_show_event;
	oc_show_event.SetIndex_SiteID_ViewerID();

	key_arr	ka;
	ka += arg.Site;

	arg.VisitorsOnline = oc_show_event.GetIndexUniqueNum(ka);
	oc_site.m_OnlineVisitors = arg.VisitorsOnline;

	return BX_OK;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]` CalculateCalendar                                                         []
[]                                                                            */
// Заполнение структуры hi в соответствии с заданным моментом времени Time.
void CalculateCalendar (HourItem& hi, time_t Time)
{
	struct tm * t = gmtime(&Time);
	hi.DayHour		= t->tm_hour;
	hi.WeekDay		= t->tm_wday;
	hi.MonthDay		= t->tm_mday-1; // 0-30 !
	hi.YearMonth	= t->tm_mon;
	hi.Year			= t->tm_year;
	return;
}
//____________________________________________________________________________[]


static const char * WDAY_NAMES			[]	= {"Вс", "Пн", "Вт", "Ср", "Чт", "Пт", "Сб"};
static const char * WDAY_NAMES_LONG		[]	= {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
static const char * MONTH_NAMES			[]	= {"Янв", "Фев", "Мар", "Апр", "Май", "Июн", "Июл", "Авг", "Сен", "Окт", "Ноя", "Дек"};
static const char * MONTH_NAMES_LONG	[]	= {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};

/*______________________________________________________________________________
[]                                                                            []
[]` FILL_AGGREGATE_DATA                                                       []
[]                                                                            */
#define	FILL_AGGREGATE_DATA(Aggreg_Type,Data_Size,Aggreg_Field)					\
	if (arg.TimeAggregate == Aggreg_Type)													\
	{																									\
		arg.Data.Alloc(Data_Size, 0);															\
		arg.Labels.Alloc(Data_Size);															\
																										\
		for (i = 0; i < Data_Size; i++) switch (Aggreg_Type)							\
		{																								\
			case TA_HourOfDay:																	\
				arg.Labels[i].Format("%02d", i);												\
			break;																					\
			case TA_DayOfWeek:																	\
				arg.Labels[i].Format("%s", WeekDayName[i]);								\
			break;																					\
			case TA_DayOfMonth:																	\
				arg.Labels[i].Format("%d", i+1);												\
			break;																					\
			case TA_MonthOfYear:																	\
				arg.Labels[i].Format("%s", MonthName[i]);									\
			break;																					\
		}																								\
																										\
		for (i = 0; i < HourArr.Size(); i++) {												\
			arg.Data[HourArr[i].Aggreg_Field] += HourArr[i].Value;					\
		}																								\
	}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` FILL_DISCRETE_DATA                                                        []
[]                                                                            */
#define FILL_DISCRETE_DATA(Descrete_Type,Descrete_Field)								\
	if (arg.TimeDescrete == Descrete_Type)													\
	{																									\
		int		CurItem	= -1;																	\
		string	Str;																				\
																										\
		int		oldDay	= -1;																	\
		int		oldMonth	= -1;																	\
		int		oldYear	= -1;																	\
		bool		bWeek		= Descrete_Type==TD_Week;										\
		string	sFormat;																			\
		for (i = 0; i < HourArr.Size(); i++)												\
		{																								\
			bool bDrawYear  = 																	\
				((oldYear!=HourArr[i].Year) || bWeek);										\
			bool bDrawMonth = 																	\
				((oldMonth!=HourArr[i].YearMonth)||bWeek)||(Descrete_Type>=TD_Month);			\
			bool bDrawDay   =																						\
				((oldDay!=HourArr[i].MonthDay)||bWeek) && (Descrete_Type<TD_Month);				\
																														\
																														\
			if ((HourArr[i].MonthDay != oldDay) || (HourArr[i].DayHour==1) || (i<=1))			\
			{																											\
					sFormat.Format(Descrete_Type!=TD_Hour?"%d|%s|%d|%s|-1":"%d|%s|%d|%s|%%02d",\
					(bDrawYear ? HourArr[i].Year+1900 : -1),								\
					(bDrawMonth? MonthName[HourArr[i].YearMonth]: "-1"),				\
					(bDrawDay  ? (HourArr[i].MonthDay+1)				: -1),			\
					(bDrawDay&&(!bWeek))? WeekDayName[HourArr[i].WeekDay]  : "-1");\
			}																							\
																										\
			if (HourArr[i].Descrete_Field == CurItem)										\
			{																							\
				arg.Data[arg.Data.Size()-1] += HourArr[i].Value;						\
			}																							\
			else																						\
			{																							\
				int nDescrete_Type = Descrete_Type;											\
				if (nDescrete_Type!=TD_Hour)													\
					Str = sFormat;																	\
				else																					\
					Str.Format (sFormat.c_str(), HourArr[i].DayHour);					\
																										\
				arg.Data.Add(HourArr[i].Value);												\
				arg.Labels.Add(Str);																\
																										\
				if (arg.Data.Size() >= TS_MaxOutputSize)									\
				{																						\
					arg.Data.	Add(-1);															\
					arg.Labels.	Add("");															\
					break;																			\
				}																						\
																										\
				CurItem = HourArr[i].Descrete_Field;										\
			}																							\
																										\
			oldYear	= HourArr[i].Year;														\
			oldMonth = HourArr[i].YearMonth;													\
			oldDay	= HourArr[i].MonthDay;													\
		}																								\
	}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_TimeStats_GetData                                                      []
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT BX_TimeStats_GetData (BX_TimeStats_Args& arg)
{
// Очистка выходных массивов:
	arg.Data.	Erase	();
	arg.Labels.	Erase	();
// Проверка диапазона:
	if (arg.Date_End < arg.Date_Start)	{
		return BXE_TimeStats_GetData_InvalidRange;
	}
// Должна быть заказана либо дискретизация, либо агрегирование:
	if ((arg.TimeAggregate != TA_None) && (arg.TimeDescrete != TD_None)) {
		return BXE_TimeStats_GetData_InvalidOutputFormat;
	}
// Корректность часового пояса:
	if ((arg.TZOffset > SECS_IN_DAY/2) || (arg.TZOffset < -SECS_IN_DAY/2)) {
		return BXE_TimeStats_GetData_InvalidTZOffset;
	}

//----------------------------------------------------------------------------[]
// Проверка на счетчики объекта "Site"
	if (arg.Object == "Site")
	{
		OC_Site	oc_site;
		oc_site.Open (arg.objID);
		if (!oc_site.IsValid())	{
			return BXE_TimeStats_GetData_InvalidObjectID;
		}
	// Проверка паролей:
		if (string(oc_site.m_RateStatsViewPassword).Len() > 0)
		{
			if (!CheckAdminPassword(arg.OwnerPassword))
			{
				if (string(oc_site.m_RateStatsViewPassword) != arg.StatsPassword)
				{
					OC_User	oc_user;
					BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

					if (string(oc_user.m_Password) != arg.OwnerPassword) {
						STATS_RETURN(Stats_BadPassword);	// Из BX_Stats.h
					}
				}
			}
		}

		if (arg.Counter == "Loads") 						arg.idCounter = oc_site.m_Loads;
		else if (arg.Counter == "Visitors") 			arg.idCounter = oc_site.m_Visitors;
		else if (arg.Counter == "Hosts") 				arg.idCounter = oc_site.m_Hosts;
		else if (arg.Counter == "Shows") 				arg.idCounter = oc_site.m_Shows;
		else if (arg.Counter == "Clicks") 				arg.idCounter = oc_site.m_Clicks;
		else if (arg.Counter == "Clicks_Local") 		arg.idCounter = oc_site.m_Clicks_Local;
		else if (arg.Counter == "Hits") 					arg.idCounter = oc_site.m_Hits;
		else if (arg.Counter == "Hits_Local") 			arg.idCounter = oc_site.m_Hits_Local;
		else if (arg.Counter == "AnonymousHits") 		arg.idCounter = oc_site.m_AnonymousHits;
		else if (arg.Counter == "SuspiciousHits") 	arg.idCounter = oc_site.m_SuspiciousHits;
		else if (arg.Counter == "SessionTime") 		arg.idCounter = oc_site.m_SessionTime;
		else if (arg.Counter == "SessionTime_Local")	arg.idCounter = oc_site.m_SessionTime_Local;
		else if (arg.Counter == "SessionNum") 			arg.idCounter = oc_site.m_SessionNum;
		else return BXE_TimeStats_GetData_InvalidCounterName;
	}
//----------------------------------------------------------------------------[]
// Проверка на счетчики объекта "IPRecord"
	if (arg.Object == "IPRecord")
	{
		if (!CheckAdminPassword(arg.OwnerPassword)) {
			STATS_RETURN(Stats_BadPassword);	// // Из BX_Stats.h
		}

		OC_IPRecord		oc_iprecord;
		oc_iprecord.Open(arg.objID);

		if (!oc_iprecord.IsValid()) {
			return BXE_TimeStats_GetData_InvalidObjectID;
		}

		if (arg.Counter == "Visitors") 			arg.idCounter = oc_iprecord.m_Visitors;
		else if (arg.Counter == "Hosts") 		arg.idCounter = oc_iprecord.m_Hosts;
		else if (arg.Counter == "Anonymous") 	arg.idCounter = oc_iprecord.m_Anonymous;
		else if (arg.Counter == "Hits") 			arg.idCounter = oc_iprecord.m_Hits;
		else return BXE_TimeStats_GetData_InvalidCounterName;
	}
//----------------------------------------------------------------------------[]

// Возврат, если счетчик не был инициализирован:
	if (arg.idCounter == NA) {
		STATS_RETURN(Stats_Okay);
	}

// Проверка валидности счетчика:
	OC_TimeStats	oc_time_stats;
	oc_time_stats.Open(arg.idCounter);

	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_3(
			"BX_TimeStats_GetData(): Invalid TimeStats ID=%lu for counter '%s' of object '%s'.",
			arg.idCounter,
			arg.Object.c_str(),
			arg.Counter.c_str());

		return BXE_TimeStats_GetData_InvalidCounterID;
	}
// Проверяем формат TimeStats
	if (oc_time_stats.m_TwoLastDaysMinute.Size() != TWO_LAST_DAY_MINUTE_SIZE)
	{
		RecodeTimeStatsFormat (oc_time_stats);
	}

//----------------------------------------------------------------------------[] 
	int		i, j, k;

	struct	tm		TimeStruct;
	
	OC_YearStats	oc_year_stats;
	OC_DayStats		oc_day_stats;
	

// Массив для часов,
//	первый элемент содержит число событий, произошедших в час с координатами arg.Date_Start
// последний элемент содержит число событий, произошедших в час с координатами arg.Date_End
	CPtr<HourItem>	HourArr;

//----------------------------------------------------------------------------[] 
// Положить в массив DayItemArr все валидные объекты дневной статистики с границами начала и конца:
	for (i = 0; i < oc_time_stats.m_YearStats.Size(); i++) 
	{	
		BX_CHECK_AND_OPEN (oc_year_stats, oc_time_stats.m_YearStats[i], OBJ_CLASS_ID_YearStats);

	// Получить time_t() для первого дня этого года:
		TimeStruct.tm_year	= oc_time_stats.m_Year[i] - 1900;
		TimeStruct.tm_mon		= 0;
		TimeStruct.tm_mday	= 1;
		TimeStruct.tm_hour	= 0;
		TimeStruct.tm_min		= 0;
		TimeStruct.tm_sec		= 0;
		time_t	gmTimeStart	=	mktime(&TimeStruct)+SERVER_TIME_ZONE_OFFSET;	// Начало года по гринвичу
		time_t	TimeStart	=	gmTimeStart + arg.TZOffset;						// Начало года по локальному
		
		SERVER_DEBUG_ASSERT_RETURN(
			gmTimeStart != -1,
			"BX_TimeStats_GetData(): Invalid call to mktime(). Aborted...",
			BX_SYSTEM_ERROR);
		

	// !!! Корректируем начало и конец диапазона
	// Начало -- Не ранее чем Дата фиксации первого события
	// Конец  -- не больше (сегодня + SECS_IN_DAY)
	
		
	// Количество дней, которое должно быть в соответствующем году:	
		int YearStatsSize = REAL_DAYS_IN_YEAR (oc_time_stats.m_Year[i]);

	// Количество дней, имеющихся в соответствующей годовой статистике:
		int RealYearStatsSize = oc_year_stats.m_DayStats.Size();

	// Цикл по всем часам всех лет:
		for (j = 0; j < YearStatsSize; j++) 
		{
		// День в заказанном диапазоне
			if (((TimeStart+SECS_IN_DAY) >= arg.Date_Start) && (TimeStart <= arg.Date_End))
			{
			// За этот день были события
				if ((j < RealYearStatsSize) && (oc_year_stats.m_DayStats[j] != NA))
				{
					BX_CHECK_AND_OPEN (oc_day_stats, oc_year_stats.m_DayStats[j], OBJ_CLASS_ID_DayStats);
				// Пробегаемся по всем часам открытого дня
					for (k = 0; k < HOURS_IN_DAY; k++, TimeStart += SECS_IN_HOUR)
					{
					// Час в заказанном диапазоне
						if ((TimeStart >= arg.Date_Start) && ((TimeStart+SECS_IN_HOUR) <= arg.Date_End))
						{
						// По зоне пользователя:
							HourItem hi;

							CalculateCalendar (hi, TimeStart);

							hi.Value			= oc_day_stats.m_HourTotal[k];
							hi.Hour			= TimeStart / SECS_IN_HOUR;
							hi.Day			= TimeStart / SECS_IN_DAY;
							hi.Week			= TimeStart / SECS_IN_WEEK;
							hi.Month			= oc_time_stats.m_Year[i]*MONTHS_IN_YEAR + hi.YearMonth;
							
							HourArr.Add (hi);

							/*
							if (hi.Value!=0)
							{
								printf ("%d ", k);
							}
							*/
						}
					}
				}
			// За этот день не было событий
				else 
				{
					for (k = 0; k < HOURS_IN_DAY; k++, TimeStart += SECS_IN_HOUR)
					{
					// Час в заказанном диапазоне 03.02.2001 - вставить break !!!
						if ((TimeStart >= arg.Date_Start) && ((TimeStart+SECS_IN_HOUR) <= arg.Date_End))
						{
						// По зоне пользователя:
							HourItem hi;

							CalculateCalendar (hi, TimeStart);

							hi.Value			= 0;
							hi.Hour			= TimeStart / SECS_IN_HOUR;
							hi.Day			= TimeStart / SECS_IN_DAY;
							hi.Week			= TimeStart / SECS_IN_WEEK;
							hi.Month			= oc_time_stats.m_Year[i]*MONTHS_IN_YEAR + hi.YearMonth;
							HourArr.Add (hi);
						}
					}
				}
			}
		// День вне заказанного диапазона
			else	{
				TimeStart += SECS_IN_DAY;
			}

		}	// end for (j 
	}	// end for (i 



/*	for (i = 0; i < HourArr.Size(); i++) 
	{
		printf("\nValue:     %d", HourArr[i].Value);
		printf("\nHour:      %d", HourArr[i].Hour);				// Час
		printf("\nDay :      %d", HourArr[i].Day);				// День
		printf("\nWeek:      %d", HourArr[i].Week);				// Неделя
		printf("\nMonth:     %d", HourArr[i].Month);			// Месяц
		printf("\nDayHour:   %d", HourArr[i].DayHour);			// Час				(0-23)
		printf("\nWeekDay:   %d", HourArr[i].WeekDay);			// День недели		(0-6)
		printf("\nMonthDay:  %d", HourArr[i].MonthDay);		// Число месяца	(0-30)
		printf("\nYearMonth: %d", HourArr[i].YearMonth);		// Месяц				(0-11)
		printf("\nYear:      %d", HourArr[i].Year);				// год		  
		puts("");	
	}
	puts("");	
*/
//----------------------------------------------------------------------------[]
	const char**	WeekDayName = arg.WeekdayLong ? WDAY_NAMES_LONG  : WDAY_NAMES;
	const char**	MonthName	= arg.MonthLong	? MONTH_NAMES_LONG : MONTH_NAMES;

//----------------------------------------------------------------------------[] 
// Агрегирование
	FILL_AGGREGATE_DATA	(TA_HourOfDay,		HOURS_IN_DAY,		DayHour	);
	FILL_AGGREGATE_DATA	(TA_DayOfWeek,		DAYS_IN_WEEK,		WeekDay	);
	FILL_AGGREGATE_DATA	(TA_DayOfMonth,	31,					MonthDay	);
	FILL_AGGREGATE_DATA	(TA_MonthOfYear,	MONTHS_IN_YEAR,	YearMonth);
	
	if (arg.TimeAggregate != TA_None)	{
		STATS_RETURN(Stats_Okay);
	}
//----------------------------------------------------------------------------[] 
// Дискретизация
	
	FILL_DISCRETE_DATA	(TD_Hour,	Hour	);
	FILL_DISCRETE_DATA	(TD_Day,		Day	);
	FILL_DISCRETE_DATA	(TD_Week,	Week	);
	FILL_DISCRETE_DATA	(TD_Month,	Month	);

	
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
