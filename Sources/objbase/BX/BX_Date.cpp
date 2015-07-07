/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'			                                 []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_YearDate.cpp                                           []
[] Date:            28.10.1999                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Работа с датами                                           []
[] Last Modified:																					[]
[]____________________________________________________________________________[]
*/                                                                          

#define USES_BX_Date

#include "BX.h"




//----------------------------------------------------------------------------[] 
static const	int	BASE_YEAR = 1900;
static const	int	MAX_YEARS = 200;
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
static	int	YEAR_DAY_TO_INT	[MAX_YEARS][DAYS_IN_YEAR+1];
static	int	INT_TO_DAY			[MAX_YEARS*(DAYS_IN_YEAR+1)];
static	int	INT_TO_YEAR			[MAX_YEARS*(DAYS_IN_YEAR+1)];
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
int		SUMM_REAL_DAYS_IN_YEAR	[MAX_YEARS];
//----------------------------------------------------------------------------[] 






//______________________________________________________________________________
//                                                                            []
//` Преобразовани даты в целое число и обратно											[]               
//                                                                            []
int _YearDayToInt (int Year, int DayOfYear)
{
	static bool bNeedPrecalculate = true;
	if (bNeedPrecalculate)
	{
		SUMM_REAL_DAYS_IN_YEAR[0]=0;
		for (int i=1; i<MAX_YEARS; i++)
		{
			SUMM_REAL_DAYS_IN_YEAR[i] = SUMM_REAL_DAYS_IN_YEAR[i-1] + REAL_DAYS_IN_YEAR(BASE_YEAR+i-1);
		}
		bNeedPrecalculate = false;
	}
	
	return SUMM_REAL_DAYS_IN_YEAR[Year-BASE_YEAR] + DayOfYear;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` PrecalcYearDay                                                            []              
//                                                                            []
void PrecalcYearDay (void)
{
	static bool bYearDayPrecalcDone = false;

	if (bYearDayPrecalcDone)
		return;

	for (int year=0; year < MAX_YEARS; year++)
	{
		for (int day=0; day < REAL_DAYS_IN_YEAR(year+BASE_YEAR); day++)
		{
			int x = _YearDayToInt (year+BASE_YEAR, day);

			YEAR_DAY_TO_INT[year][day] = x;
			INT_TO_DAY		[x]			= day;
			INT_TO_YEAR		[x]			= year+BASE_YEAR;
		}
	}
	bYearDayPrecalcDone = true;
	return;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Преобразование даты в целое число и обратно											[]               
//                                                                            []
int YearDayToInt (int Year, int DayOfYear)
{
	static bool bYearDayPrecalcDone = false;
	if (!bYearDayPrecalcDone)
	{
		PrecalcYearDay();
		bYearDayPrecalcDone = true;
	}
	

	if (Year < BASE_YEAR || DayOfYear > DAYS_IN_YEAR+1) {
		return -1;
	}

	return YEAR_DAY_TO_INT [Year-BASE_YEAR][DayOfYear];
}
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
void IntToYearDay (int year_day, int& Year, int& DayOfYear)
{
	static bool bYearDayPrecalcDone = false;
	if (!bYearDayPrecalcDone)
	{
		PrecalcYearDay();
		bYearDayPrecalcDone = true;
	}

#if 0  //{ RomanVK
	if ((year_day) < 0 || (year_day > (MAX_YEARS*(DAYS_IN_YEAR+1)))) {
		Year			= -1;
		DayOfYear	= -1;
		return;
	}
#endif //}

	Year			= INT_TO_YEAR  [year_day];
	DayOfYear	= INT_TO_DAY	[year_day];
	return;
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
