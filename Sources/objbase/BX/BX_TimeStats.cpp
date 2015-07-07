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
[] Description:     ������� ��� ������ � �������� "�������'�� ����������".    []
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
// ��������� ���� tm_* ��������� BX_TimeStats_Args �� ���� timer.             []
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
[]` ���������� �� ��������� ...                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/

//______________________________________________________________________________
//                                                                            []
//` �������� �������� �� N ��������� �����:                                   []
//                                                                            []
int BX_TimeStats_GetLastHours (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg, int nHours)
{
	if (!oc_time_stats.IsValid())
	{
		SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastHours(%d): Invalid TimeStats for site #lu.", nHours, arg.Site);
		return 0;
	}
	SERVER_DEBUG_ASSERT_RETURN ((nHours<=24) && (nHours>0), "BX_TimeStats_GetLastHours: ����� �� ������� ��������� ��������", 0);

// ������ ������, ��������������� ������� �� ��� �� �������.
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
//` �������� �������� �� ��������� N ����:                                    []                                      
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
// ������� ����� �� ��������� ������ nDays

	OC_YearStats	oc_prev_year_stats;				// ���������� ��� ����������� ����.

	for (i = 0; i < nDays; i++)
	{
		if (Year_arr[i] == arg.tm_year)				// ���� ��� ��� ��, �� ������ � ��������� ����.
		{
			nRes += oc_year_stats.m_DayTotal[Day_arr[i]];
		}
		else if ((Year_arr[i]+1) == arg.tm_year)	// ���� ��� ����������, �� ������� 
		{														// ���������� ����������� ����.
			if (!oc_prev_year_stats.IsValid())
			{
				int nYearIndex = oc_time_stats.m_Year.Find (Year_arr[i]);
				if (nYearIndex != -1)					// ���������� �� ���������� ��� �������.
				{
				// ������� ���������� ����������� ����:
					oc_prev_year_stats.Open (oc_time_stats.m_YearStats[nYearIndex]);
				// ����������, ���� ID �� ��������:
					if (!oc_prev_year_stats.IsValid()) 
					{
						SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(): Invalid YearStats ID=%lu (Year=%d).",
							(unsigned long)(oc_time_stats.m_YearStats[nYearIndex]), Year_arr[i]);
						break;
					}
				}

			// ������ � ��������� ����:
				nRes += oc_prev_year_stats.m_DayTotal[Day_arr[i]];

			}	// ���������� ��� �� ������ � ���������� -- �� � �� ����, �������, ��� ��� ����.
		}
		else // ������ ���� �� ����� ����.
		{
			SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetLastNDays: ����� �� ������� ����������� ����.", Year_arr[i]);
		}
	}


//----------------------------------------------------------------------------[] 
// ���������� ���� �� ������� ���:

	int RestInt = cur_YearDay - nDays;				// ����� ������� ���.
	int RestDay,  RestYear;
	IntToYearDay (RestInt, RestYear, RestDay);	// ��� � ���������� ����� ������� ���.
	

	OC_DayStats		oc_day_stats;

	if (RestYear == arg.tm_year)	// ��� ��� �� -- ������� ���������� ��� ������.
	{
		if (oc_year_stats.m_DayStats[RestDay] != NA)	// ���� ���������� �� ������ ����.
		{
		// ������� ���������� �� ������ ����:
			oc_day_stats.Open(oc_year_stats.m_DayStats[RestDay]);

			if (oc_day_stats.IsValid())
			{
			// ������������ � ��������� ��� �������� �����, ������� � �������� � �� ����� ���:
				const int * oc_day_stats_m_HourTotal = oc_day_stats.m_HourTotal.GetPtr();
				for (int i = arg.tm_hour+1 ; i < HOURS_IN_DAY; i++) 
				{
					nRes +=	oc_day_stats_m_HourTotal[i];
				}
			// ������� �������� �� �������� ������� ���
			// (������� �� ���� ���, � ������ ���� �� ����):
				nRes += oc_day_stats_m_HourTotal[arg.tm_hour]			// ������� ���
							* (MINS_IN_HOUR-arg.tm_min) / MINS_IN_HOUR;	// ����
			}
		// ����������, ���� ������ ID:
			else
			{
				SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays: Invalid DayStats[%d] ID=%lu. Skipped.",
					RestDay, (unsigned long)(oc_year_stats.m_DayStats[RestDay]));
			}
	
		}	
		// ��� ���������� �� ������ ���� -- �� � �����, ��� �� ����� ;)
	}
	else if ((RestYear+1) == arg.tm_year)	// ��� -- ����������, ���� �������
	{													// ��������������� ������� ����������.
		
		int nYearIndex = oc_time_stats.m_Year.Find (RestYear);

	// ���� ���������� �� ���������� ���:
		if (nYearIndex != -1)
		{
		// ������� ����������, ���� �����:
			if (!oc_prev_year_stats.IsValid()) {
				oc_prev_year_stats.Open (oc_time_stats.m_YearStats[nYearIndex]);
			}
			if (oc_prev_year_stats.IsValid())
			{
			// ���� ���� ���������� �� ������ ����:
				if (oc_prev_year_stats.m_DayStats[RestDay] != NA)
				{
					oc_day_stats.Open(oc_prev_year_stats.m_DayStats[RestDay]);
					if (oc_day_stats.IsValid())
					{
					// ������������ � ��������� ��� �������� �����, ������� � �������� � �� ����� ���:
						const int * oc_day_stats_m_HourTotal = oc_day_stats.m_HourTotal.GetPtr();
						
						for (int i = arg.tm_hour+1 ; i < HOURS_IN_DAY; i++) {
							nRes +=	oc_day_stats_m_HourTotal[i];
						}
					// ������� �������� �� �������� ������� ���
					// (������� �� ���� ���, � ������ ���� �� ����):
						nRes += oc_day_stats_m_HourTotal[arg.tm_hour]		// ���
								* (MINS_IN_HOUR-arg.tm_min) / MINS_IN_HOUR;	// ����
					}
				}
			}
			else
			{
				SERVER_DEBUG_ERROR_2 ("BX_TimeStats_GetLastNDays(): Invalid YearStats ID=%lu, Year=%d.",
					(unsigned long)(oc_time_stats.m_YearStats[nYearIndex]), RestYear);
			}
		}
	// ��� ���������� �� ���������� ��� -- ������� � �������.
	}
	else	// ������ ���� �� ������ ���� - ����������:
	{
		SERVER_DEBUG_ERROR_1 ("BX_TimeStats_GetLastNDays: ����� �� ������� ����������� ���� %d.",arg.tm_year);
	}


	return nRes;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` �������� �������� �� ��������� ���:                                       []                                   
BX_RESULT BX_TimeStats_GetLastHour (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg)
{
	arg.LH = BX_TimeStats_GetLastHours (oc_time_stats, arg, 1);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` �������� �������� �� ��������� ����:                                      []                                    
BX_RESULT BX_TimeStats_GetLastDay (const OC_TimeStats& oc_time_stats, BX_TimeStats_Args& arg)
{
	arg.LD = BX_TimeStats_GetLastHours (oc_time_stats, arg, 24);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` �������� �������� �� ��������� �����:                                     []                                     
BX_RESULT
BX_TimeStats_GetLastWeek ( const	OC_TimeStats&			oc_time_stats,
									const	OC_YearStats&			oc_year_stats,
											BX_TimeStats_Args&	arg)
{
	arg.LW = BX_TimeStats_GetLastNDays (oc_time_stats, oc_year_stats, arg, DAYS_IN_WEEK);
	return BX_OK;
}
//----------------------------------------------------------------------------[] 
//` �������� �������� �� ��������� �����:                                     []                                     
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
// ������������ �����
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

// ��������������� TimeStats::TwoLastDaysMinute[]

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
[] ������� ��� ���������� �������� ���� TimeStats.										[]
[] ������� ���������� �������� ������������� ������� ������ TimeStats,			[]
[] ������� ����� ���� ����� NA, � ���� ������ ����� ������ ����� ������.		[]
[]	�������� �������� ����� ���������� ������������ � CounterValue.				[]
[]____________________________________________________________________________*/
BX_RESULT BX_TimeStats_Increment (BX_TimeStats_Args& arg)
{	
	int i;

	//----------------------------------------------------------------------------[] 
	// �������� ������� ����������
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
	// �������� ��� �������� ��������� ������� ����������:
	//
	OC_TimeStats oc_time_stats; 
	if (arg.idCounter == NA)
	{
	// ������ ������ �������� ����������
		oc_time_stats.New ();
	// �������� ������ � TWO_LAST_DAY_MINUTE_SIZE ��������� (TIMESTATS_DISCRETIZATION-���������� ��������� �� 2 �����)
		oc_time_stats.m_TwoLastDaysMinute.Alloc (TWO_LAST_DAY_MINUTE_SIZE, 0);

	// ��������� ������ ���� ��������� ������
		oc_time_stats.m_TwoLastDaysMinute_year				
			= arg.tm_day_of_year==0? arg.tm_year-1	:	arg.tm_year;
		oc_time_stats.m_TwoLastDaysMinute_day_of_year
			= arg.tm_day_of_year==0? LAST_DAY_OF_YEAR(arg.tm_year-1)	: (arg.tm_day_of_year-1);

	// ��������� ID ��������� ������� ����������
		arg.idCounter = oc_time_stats.GetObjectID ();
	}
	else
	{
	// ��������� ������ �������� ���������� 
		oc_time_stats.Open(arg.idCounter);
	
	// ��������� ������������� ������� �������� ���������� 
		if (!oc_time_stats.IsValid())
		{
			SERVER_DEBUG_ERROR_1 ("BX_TimeStats_Increment(): Invalid TimeStats ID: %lu", arg.idCounter);
			return BX_SYSTEM_ERROR;
		}

	// ��������� ������ TimeStats
		if (oc_time_stats.m_TwoLastDaysMinute.Size() != TWO_LAST_DAY_MINUTE_SIZE)
		{
			RecodeTimeStatsFormat (oc_time_stats);
		}
	}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	oc_time_stats.m_LastAccessTime = time_0;
	//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
// �������� ����������� ������� ����������
//
	int nYearIndex = oc_time_stats.m_Year.Find (arg.tm_year);
	OC_YearStats	oc_year_stats;

	if (nYearIndex == -1)	// ���� ���������� �� ���� ��� ��� ���, �� �������� �:
	{
		nYearIndex = oc_time_stats.m_Year.Add (arg.tm_year) - 1;
		oc_time_stats.m_YearStats.Add (NA);

	// ������� ������ ������� ����������:
		oc_year_stats.New ();

	// �������� ������� ����, ������� ����� ��� ����, ����� ���������� ����������� ����
//		oc_year_stats.m_DayTotal.Alloc (REAL_DAYS_IN_YEAR(arg.tm_year), 0);
//		oc_year_stats.m_DayStats.Alloc (REAL_DAYS_IN_YEAR(arg.tm_year), NA);
		
		oc_year_stats.m_DayTotal.Alloc (arg.tm_day_of_year+1, 0);
		oc_year_stats.m_DayStats.Alloc (arg.tm_day_of_year+1, NA);
		
		
	// �������� � �������� ���������� ������ �� ����� ������ ������� ����������:
		oc_time_stats.m_YearStats [nYearIndex] = oc_year_stats.GetObjectID();
	}
	else							// ���������� �� ���� ��� ����, ������� �:
	{
		oc_year_stats.Open(oc_time_stats.m_YearStats[nYearIndex]);
		if (!oc_year_stats.IsValid())
		{
			SERVER_DEBUG_ERROR_2("BX_TimeStats_Increment(): Invalid TimeStats::YearStats[Year=%d]=%lu.",
				arg.tm_year, (unsigned long)(oc_time_stats.m_YearStats[nYearIndex]));
			return BX_SYSTEM_ERROR;
		}
		
	// ��������� ����� ���� � ������� ���������� 
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
	// �������� ��� �������� ������� ������� ����������:
	//
	OC_DayStats	oc_day_stats;

	if (arg.Increment != 0)
	{
		if (oc_year_stats.m_DayStats[arg.tm_day_of_year] == NA)
		{
		// ���������, ��� ������� ���� �������.
			if (oc_year_stats.m_DayTotal[arg.tm_day_of_year]!=0)
			{
				SERVER_DEBUG_ERROR ("������� ��� ������ ��� � ���� �� ����� ����.");
				oc_year_stats.m_DayTotal[arg.tm_day_of_year] = 0;
			}

		// ������� ������ ������� ����������:
			oc_day_stats.New ();
			oc_day_stats.m_HourTotal.Alloc (HOURS_IN_DAY, 0);
		// �������� ������ �� ����� ������ ������� ����������:
			oc_year_stats.m_DayStats[arg.tm_day_of_year] = oc_day_stats.GetObjectID();
		}
		else	// ������ ���� -- ������� ���:
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
	// ��������� ����� ����� � ������� ���������� 
		SERVER_DEBUG_ASSERT_RETURN(
			oc_day_stats.m_HourTotal.Size() == HOURS_IN_DAY,
			"BX_TimeStats_Increment(): Invalid hour index or DayStats::HourStats[].",
			BX_SYSTEM_ERROR);
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// ���������� ������� � ������� �� ��������� ��� ��� � 
	// ������������� ������ �����. 
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
	// ������� ���������� ��������
	//
	//	.......]  [������ ����][���� ���������� ����������]  [��������� ����]  [........
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
		SERVER_DEBUG_ERROR_4 ("�� ����� ������� � ������ ��������� ��������: ������� ���� = [%d.%d], ������ ���� ������� = [%d.%d]",
			arg.tm_year, arg.tm_day_of_year, (int)oc_time_stats.m_TwoLastDaysMinute_year, (int)oc_time_stats.m_TwoLastDaysMinute_day_of_year);
		cur_day = DAY_PAST;
	}
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// ������������ ��������
	// � ������� ������ ����� nMinuteIndex
	switch (cur_day)
	{
	// �������� ������ ������
		case DAY_PAST:
		{
		// ������ ������ � ������ �� ��������.
			SERVER_DEBUG_ERROR ("Incrementing in the past. Nothing done");
			nMinuteIndex = -1;
			break;
		}

	// �������� ������ ������ � ���������� ����
		case DAY_FIRST:
		{
		// ������ ������ � ������
			//SERVER_DEBUG_ERROR ("�������� ������ ������ (DAY_FIRST).");
			nMinuteIndex = arg.tm_hour*MINS_IN_HOUR + arg.tm_min;
			break;
		}

	// ������� ������ � ��� �� ����, ��� � ����������
		case DAY_CURRENT:
		{
		// ������ ������ � ������
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;
			break;
		}

	// ������� ������ �� ��������� ���� ����� ����������� �������
		case DAY_NEXT:
		{
		// ���������� ������� "��������" ��� � ���� ���������� (������ � ������)
		// � �������� ���� �������.
			for (i = 0; i < TIMESTATS_COUNTS_IN_DAY; i++)
			{
				oc_time_stats.m_TwoLastDaysMinute [i]	
					= oc_time_stats.m_TwoLastDaysMinute [i+MINS_IN_DAY];
				oc_time_stats.m_TwoLastDaysMinute [i+TIMESTATS_COUNTS_IN_DAY]
					= 0;
			}

		// ������ ������ � ������.
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;

		// ������ ���� ������.
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

	// ������� ������ ����� ��� ����� ���� ���� ����� ����������� �������
		case DAY_FUTURE:
		{
		// �������� ����� �����.
			for (i = 0; i < 2*TIMESTATS_COUNTS_IN_DAY; i++)
			{
				oc_time_stats.m_TwoLastDaysMinute [i]	= 0;
			}

		// ������ ������ � ������.
			nMinuteIndex = MINS_IN_DAY + arg.tm_hour*MINS_IN_HOUR + arg.tm_min;

		// ������ ���� ������.
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
	// ����������� ��������
	if (arg.Increment!=0)
	{
	// ��������� ��������� ��������:
		oc_time_stats.m_Total									+= arg.Increment;

	// ��������� �������� ��������:
		oc_year_stats.m_DayTotal[arg.tm_day_of_year]		+= arg.Increment;

	// ��������� �������� ��������:
		oc_day_stats.m_HourTotal[arg.tm_hour]				+= arg.Increment;

	// ��������� ��������� ��������:
		if ((nMinuteIndex < 0) || (nMinuteIndex >= (2*MINS_IN_DAY)))
		{
			SERVER_DEBUG_ERROR_2 ("��������� ��������� ��������: ������ ����� ����� �� ����� ���� �����: %d (Max=%d).",
				nMinuteIndex, 2*MINS_IN_DAY);
		}
		else
		{
		// ��������� ������ � ������� �����:
			nMinuteIndex /= TIMESTATS_DISCRETIZATION;
			oc_time_stats.m_TwoLastDaysMinute[nMinuteIndex]	+= arg.Increment;
		}
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// ���� ���� -- ������� ������������ ��������
	if (arg.CalculateLast)
	{
	// ��������� �������� �������� �� ��������� ���:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastHour	(oc_time_stats, arg));

	// ��������� �������� �������� �� ��������� ����:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastDay		(oc_time_stats, arg));

	// ��������� �������� �������� �� ��������� ������:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastWeek	(oc_time_stats, oc_year_stats, arg));

	// ��������� �������� �������� �� ��������� �����:
		BX_ASSERT_RETURN (BX_TimeStats_GetLastMonth	(oc_time_stats, oc_year_stats, arg));
	}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	// ��������� ����� �������� ��������:
	arg.Total		= oc_time_stats.m_Total;

	return BX_OK;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]` BX_TimeStats_Delete                                                       []                     
[]                                                                            []
[]--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- []
[] Description:  �������� �������� arg.idCounter.                             []
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

// ��� ������� ����:
	for (i = 0; i < oc_time_stats.m_YearStats.Size(); i++)
	{
		if (oc_time_stats.m_YearStats[i] != NA)
		{
			BX_CHECK_AND_OPEN(oc_year_stats, oc_time_stats.m_YearStats[i], OBJ_CLASS_ID_YearStats);

		// ��� ������� ���:
			for (j = 0; j < oc_year_stats.m_DayStats.Size(); j++)
			{
				if (oc_year_stats.m_DayStats[j] != NA)
				{
					oc_day_stats.Delete(oc_year_stats.m_DayStats[j]);
					oc_year_stats.m_DayStats[j] = NA;			// �� ������ ��������
				}
			} // end for (j

			oc_year_stats.Delete();
			oc_time_stats.m_YearStats.Del(i);					// �� ������ ��������
			oc_time_stats.m_Year.Del(i);

		} // end if (oc_time_stats
	} // end for (i

	oc_time_stats.Delete();

	arg.idCounter = NA;												// �� ������ ��������
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

// ��������� ������ TimeStats
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

// ����� ����������� �� ��������� 3 ������:
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
// ���������� ��������� hi � ������������ � �������� �������� ������� Time.
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


static const char * WDAY_NAMES			[]	= {"��", "��", "��", "��", "��", "��", "��"};
static const char * WDAY_NAMES_LONG		[]	= {"�����������", "�����������", "�������", "�����", "�������", "�������", "�������"};
static const char * MONTH_NAMES			[]	= {"���", "���", "���", "���", "���", "���", "���", "���", "���", "���", "���", "���"};
static const char * MONTH_NAMES_LONG	[]	= {"������", "�������", "����", "������", "���", "����", "����", "������", "��������", "�������", "������", "�������"};

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
// ������� �������� ��������:
	arg.Data.	Erase	();
	arg.Labels.	Erase	();
// �������� ���������:
	if (arg.Date_End < arg.Date_Start)	{
		return BXE_TimeStats_GetData_InvalidRange;
	}
// ������ ���� �������� ���� �������������, ���� �������������:
	if ((arg.TimeAggregate != TA_None) && (arg.TimeDescrete != TD_None)) {
		return BXE_TimeStats_GetData_InvalidOutputFormat;
	}
// ������������ �������� �����:
	if ((arg.TZOffset > SECS_IN_DAY/2) || (arg.TZOffset < -SECS_IN_DAY/2)) {
		return BXE_TimeStats_GetData_InvalidTZOffset;
	}

//----------------------------------------------------------------------------[]
// �������� �� �������� ������� "Site"
	if (arg.Object == "Site")
	{
		OC_Site	oc_site;
		oc_site.Open (arg.objID);
		if (!oc_site.IsValid())	{
			return BXE_TimeStats_GetData_InvalidObjectID;
		}
	// �������� �������:
		if (string(oc_site.m_RateStatsViewPassword).Len() > 0)
		{
			if (!CheckAdminPassword(arg.OwnerPassword))
			{
				if (string(oc_site.m_RateStatsViewPassword) != arg.StatsPassword)
				{
					OC_User	oc_user;
					BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

					if (string(oc_user.m_Password) != arg.OwnerPassword) {
						STATS_RETURN(Stats_BadPassword);	// �� BX_Stats.h
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
// �������� �� �������� ������� "IPRecord"
	if (arg.Object == "IPRecord")
	{
		if (!CheckAdminPassword(arg.OwnerPassword)) {
			STATS_RETURN(Stats_BadPassword);	// // �� BX_Stats.h
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

// �������, ���� ������� �� ��� ���������������:
	if (arg.idCounter == NA) {
		STATS_RETURN(Stats_Okay);
	}

// �������� ���������� ��������:
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
// ��������� ������ TimeStats
	if (oc_time_stats.m_TwoLastDaysMinute.Size() != TWO_LAST_DAY_MINUTE_SIZE)
	{
		RecodeTimeStatsFormat (oc_time_stats);
	}

//----------------------------------------------------------------------------[] 
	int		i, j, k;

	struct	tm		TimeStruct;
	
	OC_YearStats	oc_year_stats;
	OC_DayStats		oc_day_stats;
	

// ������ ��� �����,
//	������ ������� �������� ����� �������, ������������ � ��� � ������������ arg.Date_Start
// ��������� ������� �������� ����� �������, ������������ � ��� � ������������ arg.Date_End
	CPtr<HourItem>	HourArr;

//----------------------------------------------------------------------------[] 
// �������� � ������ DayItemArr ��� �������� ������� ������� ���������� � ��������� ������ � �����:
	for (i = 0; i < oc_time_stats.m_YearStats.Size(); i++) 
	{	
		BX_CHECK_AND_OPEN (oc_year_stats, oc_time_stats.m_YearStats[i], OBJ_CLASS_ID_YearStats);

	// �������� time_t() ��� ������� ��� ����� ����:
		TimeStruct.tm_year	= oc_time_stats.m_Year[i] - 1900;
		TimeStruct.tm_mon		= 0;
		TimeStruct.tm_mday	= 1;
		TimeStruct.tm_hour	= 0;
		TimeStruct.tm_min		= 0;
		TimeStruct.tm_sec		= 0;
		time_t	gmTimeStart	=	mktime(&TimeStruct)+SERVER_TIME_ZONE_OFFSET;	// ������ ���� �� ��������
		time_t	TimeStart	=	gmTimeStart + arg.TZOffset;						// ������ ���� �� ����������
		
		SERVER_DEBUG_ASSERT_RETURN(
			gmTimeStart != -1,
			"BX_TimeStats_GetData(): Invalid call to mktime(). Aborted...",
			BX_SYSTEM_ERROR);
		

	// !!! ������������ ������ � ����� ���������
	// ������ -- �� ����� ��� ���� �������� ������� �������
	// �����  -- �� ������ (������� + SECS_IN_DAY)
	
		
	// ���������� ����, ������� ������ ���� � ��������������� ����:	
		int YearStatsSize = REAL_DAYS_IN_YEAR (oc_time_stats.m_Year[i]);

	// ���������� ����, ��������� � ��������������� ������� ����������:
		int RealYearStatsSize = oc_year_stats.m_DayStats.Size();

	// ���� �� ���� ����� ���� ���:
		for (j = 0; j < YearStatsSize; j++) 
		{
		// ���� � ���������� ���������
			if (((TimeStart+SECS_IN_DAY) >= arg.Date_Start) && (TimeStart <= arg.Date_End))
			{
			// �� ���� ���� ���� �������
				if ((j < RealYearStatsSize) && (oc_year_stats.m_DayStats[j] != NA))
				{
					BX_CHECK_AND_OPEN (oc_day_stats, oc_year_stats.m_DayStats[j], OBJ_CLASS_ID_DayStats);
				// ����������� �� ���� ����� ��������� ���
					for (k = 0; k < HOURS_IN_DAY; k++, TimeStart += SECS_IN_HOUR)
					{
					// ��� � ���������� ���������
						if ((TimeStart >= arg.Date_Start) && ((TimeStart+SECS_IN_HOUR) <= arg.Date_End))
						{
						// �� ���� ������������:
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
			// �� ���� ���� �� ���� �������
				else 
				{
					for (k = 0; k < HOURS_IN_DAY; k++, TimeStart += SECS_IN_HOUR)
					{
					// ��� � ���������� ��������� 03.02.2001 - �������� break !!!
						if ((TimeStart >= arg.Date_Start) && ((TimeStart+SECS_IN_HOUR) <= arg.Date_End))
						{
						// �� ���� ������������:
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
		// ���� ��� ����������� ���������
			else	{
				TimeStart += SECS_IN_DAY;
			}

		}	// end for (j 
	}	// end for (i 



/*	for (i = 0; i < HourArr.Size(); i++) 
	{
		printf("\nValue:     %d", HourArr[i].Value);
		printf("\nHour:      %d", HourArr[i].Hour);				// ���
		printf("\nDay :      %d", HourArr[i].Day);				// ����
		printf("\nWeek:      %d", HourArr[i].Week);				// ������
		printf("\nMonth:     %d", HourArr[i].Month);			// �����
		printf("\nDayHour:   %d", HourArr[i].DayHour);			// ���				(0-23)
		printf("\nWeekDay:   %d", HourArr[i].WeekDay);			// ���� ������		(0-6)
		printf("\nMonthDay:  %d", HourArr[i].MonthDay);		// ����� ������	(0-30)
		printf("\nYearMonth: %d", HourArr[i].YearMonth);		// �����				(0-11)
		printf("\nYear:      %d", HourArr[i].Year);				// ���		  
		puts("");	
	}
	puts("");	
*/
//----------------------------------------------------------------------------[]
	const char**	WeekDayName = arg.WeekdayLong ? WDAY_NAMES_LONG  : WDAY_NAMES;
	const char**	MonthName	= arg.MonthLong	? MONTH_NAMES_LONG : MONTH_NAMES;

//----------------------------------------------------------------------------[] 
// �������������
	FILL_AGGREGATE_DATA	(TA_HourOfDay,		HOURS_IN_DAY,		DayHour	);
	FILL_AGGREGATE_DATA	(TA_DayOfWeek,		DAYS_IN_WEEK,		WeekDay	);
	FILL_AGGREGATE_DATA	(TA_DayOfMonth,	31,					MonthDay	);
	FILL_AGGREGATE_DATA	(TA_MonthOfYear,	MONTHS_IN_YEAR,	YearMonth);
	
	if (arg.TimeAggregate != TA_None)	{
		STATS_RETURN(Stats_Okay);
	}
//----------------------------------------------------------------------------[] 
// �������������
	
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
