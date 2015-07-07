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
[] Description:     ������� ��� ������ � �������� "�������'�� ����������".    []
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
	int			Value;			// ����� �������

	int			Hour;				// ���
	int			Day;				// ����
	int			Week;				// ������
	int			Month;			// �����

	int			DayHour;			// ���				(0-23)
	int			WeekDay;			// ���� ������		(0-6)
	int			MonthDay;		// ����� ������	(0-30)
	int			YearMonth;		// �����				(0-11)
	int			Year;				// ���
};
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ������� ������ �� ����������                                              []                            
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
	
	identifier	idCounter;			// << ������� �������. (���� NA �� ����������� ID ������ �������)
	int			Increment;			// << ���������� ��������

	time_t		timer;				// << ����� � �������� � 1970-�� ����
	bool			CalculateLast;		// << ���� �� ������� ������������ ��������.

											// << ���� � ����� ������� �� ��������.
	int			tm_sec;				//		--	Seconds after minute
	int			tm_min;				//		--	Minutes after hour (0 � 59)
	int			tm_hour;				//		--	Hours after midnight (0 � 23)
	int			tm_day_of_month;	//		--	Day of month (1 � 31)
	int			tm_mon;				//		--	Month (0 � 11; January = 0)
	int			tm_year;				//		--	��� - 4 �����, � �� Year (current year minus 1900)
	int			tm_day_of_week;	//		--	Day of week (0 � 6; Sunday = 0)
	int			tm_day_of_year;	//		--	Day of year (0 � 365; January 1 = 0)

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	int			Total;				// >> ����� ������� �� �� �����.

	int			LM;					// >> ����� ������� �� ��������� 30 ����.		- �������� �� ����.
	int			LW;					// >> ����� ������� �� ��������� 7 ����.		- �������� �� ����.
	int			LD;					// >> ����� ������� �� ��������� 24 ����.		- �������� �� ������.
	int			LH;					// >> ����� ������� �� ��������� 60 �����.	- �������� �� ������.

//----------------------------------------------------------------------------[] 
// ��� BX_TimeStats_GetData

	identifier	objID;				// ID �������-��������� ��������.
	string		OwnerPassword;		// ������ ��������� ����������.
	string		StatsPassword;		// ������ �� ������ � ����������.
	string		Object;				// �������� �������-��������� ��������.
	string		Counter;				// �������� ��������.
														
	time_t		Date_Start;			// ��������� ���� ���������.
	time_t		Date_End;			// �������� ���� ���������.
	time_t		TZOffset;			// �������� �������� ����� (���).
											
	int			TimeDescrete;		// ��c���������� (0-None,1-Hour,2-Day,3-Week,4-Month).
	int			TimeAggregate;		// ������������� (0-None,1-HourOfDay,2-DayOfWeek,3-DayOfMonth,4-MonthOfYear).
											
	bool			WeekdayLong;		// ������������ ������� �������� ���� ������.
	bool			MonthLong;			// ������������ ������� �������� �������.
											
											
	int_arr		Data;					// �������� �������.
	string_arr	Labels;				// ����� �������� �������.
											
	int			ExitCode;			// ��� ��������.

								
//----------------------------------------------------------------------------[] 
// ��� BX_TimeStats_GetStatInfo:
	identifier	Site;					// <	������������� �����.
	string		StatsName;			// <	�������� ��������.
	string_arr	XLabel;				// > 	X-����������.
	int_arr		YValue;				// >	Y-����������.
	int			YMax;					// >	������������ �������� Y-����������.
	int			YMin;					// >	����������� �������� Y-����������.
	int			VisitorsOnline;	// >	����� ����������� �� ��������� 3 ������.

};
//----------------------------------------------------------------------------[] 

BX_RESULT	BX_TimeStats_CreateArgs	(BX_TimeStats_Args& arg);

// ��������� ������ �� ��������������� �������� �����.
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