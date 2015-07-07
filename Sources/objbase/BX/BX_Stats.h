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

// Вход:	
	identifier		objID;				// Идентификатор сайта.
	string			OwnerPassword;		// Пароль владельца информации.
	string			StatsPassword;		// Пароль на доступ к статистике.

	string			Name;					// Название сайта.
	string			Description;		// Описание сайта.
	time_t			CreationTime;		// Время создания сайта (по Гринвичу).
	string			URL;					// Адрес сайта.

	string			Mode;					// Режим вывода ('Last','All','Daily').
	string			SortOrder;			// Порядок сортировки ('Hosts','Viewers').
	int				FirstPos;			//	Позиция в отсортированном списке первого объекта.
	int				LastPos;				//	Позиция в отсортированном списке последнего объекта.

	time_t			StartDate;			// Начальная дата.
	time_t			EndDate;				// Конечная дата.

// Выход:
	string_arr		RawVector;			// Строковый массив с упакованной статистической информацией.
	string_arr		RawTable;			// Строковый массив с упакованной статистической информацией.
	int				TotalObjects;		// Количество строк в таблице RawTable.

	int				ExitCode;			// Код возврата.
};
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
// Возвращает информацию, касающуюся пересечения аудиторий сайта.
BX_RESULT BX_SiteStats_AudienceIntersect(BX_SiteStats_Args& arg);

// Возвращает информацию о последних событиях и зрителях.
BX_RESULT BX_SiteStats_WhatsNew(BX_SiteStats_Args& arg);

// Возвращает информацию о реферерах.
BX_RESULT BX_SiteStats_Referrer(BX_SiteStats_Args& arg);
//____________________________________________________________________________[]

//----------------------------------------------------------------------------[]
// Некоторые макросы
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