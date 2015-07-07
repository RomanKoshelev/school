/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Viewer.h                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "посетитель сайта".         []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#ifndef BX_Viewer_H
#define BX_Viewer_H

#define USES_BX_Events
#define USES_BX_Counter



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Viewer                                                                    []      
[]                                                                            []
[]____________________________________________________________________________[]
*/
struct	BX_Viewer_Args
{

	BX_Viewer_Args() {

		Anonymous			= true;
		TotalShows			= 0;
		TotalClicks			= 0;

		Group					= NA;

		CreationTime		= 0;
		LastVisitTime		= 0;
		TZOffset				= 0L;
		objID					= NA;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}
																
	
	bool				Anonymous		;				// Является ли этот объект разделяемым
															// между зрителями с одинаковым IP и 
															// неустановленным Cookie.
															
	int				TotalShows		;				// Общее кол-во показов.
	int				TotalClicks		;				// Общее кол-во кликов.
															
	string			IPAddress;						// IP адрес.
	string			Referrer;						// Хост посетителя.
															
	identifier		Group				;				// Группа предпочтений зрителя.
															
	time_t			CreationTime	;				// Время создания объекта.
	string			sCreationTime	;				// Время создания объекта в строковом виде.
	time_t			LastVisitTime	;				// Время последнего посещения.
	string			sLastVisitTime	;				// Время последнего посещения в строковом виде.
																		
	time_t			TZOffset					;		// Смещение часового пояса зрителя в секундах.
	identifier_arr	Site						;		// ID сайтов, посещённых зрителем.
	string_arr		sSite						;		// Названия сайтов, посещённых зрителем.

//	time_t_arr		Site_LastVisited		;		// Время последнего посещения соответствующего сайта.
	string_arr		sSite_LastVisited		;		// Время последнего посещения соответствующего сайта в строковом виде.

	int_arr			Site_Visits				;		// Общее число посещений соответствующего сайта.

	byte_arr			Site_Votings			;		// Число голосов, отданных зрителем за соответствующий сайт.
	byte_arr			Site_VoteDayNo			;		// Последние 2 цифры (т.е. остаток от деления на 100) номера дня (в году),
															// в который производилось соответствующее голосование (берётся из поля tm::tm_yday).
						
	identifier_arr	Banner					;		// ID баннеров, показанных зрителю.
	time_t_arr		Banner_LastViewed		;		// Время последнего показа соответствующего баннера зрителю.
	int_arr			Banner_Shows			;		// Общее число показов соответствующего баннера зрителю.

	identifier		objID;					// Идентификатор пользователя.
	int				objFirstNo;				// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
	int				objLastNo;				// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
	identifier_arr	objIDs;					// Идентификаторы объектов.
	string_arr		objNames;				// Здесь возвращаются имена функциями *Enumerate().
};
//----------------------------------------------------------------------------[] 

// Перечислить зрителей.
BX_RESULT BX_Viewer_Enumerate	(BX_Viewer_Args& arg);	
// Получить информацию по зрителю.
BX_RESULT BX_Viewer_GetData	(BX_Viewer_Args& arg);	

//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 

BX_RESULT
BX_GetViewer(	OC_Viewer&			oc_viewer,
					BX_Event_Args&		arg,
					bool&					bAnonymousViewer, 
					time_t				CurrentTime);

void
UpdateViewerInfo( OC_Viewer&			oc_viewer,		// IN:		Открытый и установленный контроллер зрителя.
						BX_Counter_Args&	arg,				// IN/OUT:	ID сайта / Visits, LastVisit
						time_t				CurrentTime,	// IN:		Текущее время (GMT).
						bool&					bNewVisitor,	// OUT:		Является ли посетитель новым для сайта.
						bool&					bHost,			// OUT:		Является ли посетитель хостом.
						time_t&				ReturnTime);

//____________________________________________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/