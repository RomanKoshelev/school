/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Stats.h                                                []
[] Date:            05.08.99                                                  []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[]____________________________________________________________________________[]
*/  
#ifndef BX_Stats_H
#define BX_Stats_H
//----------------------------------------------------------------------------[]

BX_RESULT BX_Site_UpdateLastCounters	(time_t curTime);


/*______________________________________________________________________________
[]                                                                            []
[]` BX_Stats_ExitCode                                                         []                 
[]                                                                            */
enum BX_Stats_ExitCode
{
	Stats_Okay				= 0,
	
	Stats_InvalidObjectID= 1,
	Stats_BadPassword		= 2,
	Stats_StatsOff			= 3,
	Stats_BadRange			= 4,

	Stats_SystemError		= -2,
	Stats_Undifined		= -1
};
//______________________________________________________________________________
//                                                                            []
//` BX_SiteStats_Args                                                         []
//                                                                            []
struct BX_SiteStats_Args
{
	BX_SiteStats_Args()
	{
		objID				= NA;
		TotalObjects	= 0;
		FirstPos			= 0;
		LastPos			= 0;
		ExitCode			= -1;
		StartDate		= 0;
		EndDate			= 0;

		ExitCode			= (int)Stats_Undifined;
	}

// ����:	
	identifier		objID;				// ������������� �����.
	string			OwnerPassword;		// ������ ��������� ����������.
	string			StatsPassword;		// ������ �� ������ � ����������.

	string			Name;					// �������� �����.
	string			Description;		// �������� �����.
	time_t			CreationTime;		// ����� �������� ����� (�� ��������).
	string			URL;					// ����� �����.

	string			Mode;					// ����� ������ ('Last','All','Daily').
	string			SortOrder;			// ������� ���������� ('Hosts','Viewers').
	int				FirstPos;			//	������� � ��������������� ������ ������� �������.
	int				LastPos;				//	������� � ��������������� ������ ���������� �������.

	time_t			StartDate;			// ��������� ����.
	time_t			EndDate;				// �������� ����.

// �����:
	string_arr		RawVector;			// ��������� ������ � ����������� �������������� �����������.
	string_arr		RawTable;			// ��������� ������ � ����������� �������������� �����������.
	int				TotalObjects;		// ���������� ����� � ������� RawTable.

	int				ExitCode;			// ��� ��������.
};
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
// ���������� ����������, ���������� ����������� ��������� �����.
BX_RESULT BX_SiteStats_AudienceIntersect(BX_SiteStats_Args& arg);

// ���������� ���������� � ��������� �������� � ��������.
BX_RESULT BX_SiteStats_WhatsNew(BX_SiteStats_Args& arg);

// ���������� ���������� � ���������.
BX_RESULT BX_SiteStats_Referrer(BX_SiteStats_Args& arg);
//____________________________________________________________________________[]

//----------------------------------------------------------------------------[]
// ��������� �������
//----------------------------------------------------------------------------[]
#define	ADD_FIELD_IF_ALLOWED(FieldName)												\
	if (bStatsAllowed)	Str.Format("%d", (int)oc_othersite.m_##FieldName);	\
	else						Str = "NA";														\
	arg.RawTable.Add(Str)
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
#define	STATS_RETURN(_ExitCode)															\
		arg.ExitCode = (int)_ExitCode;													\
		return BX_OK

//----------------------------------------------------------------------------[]

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/