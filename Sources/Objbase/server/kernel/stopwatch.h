/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            stopwatch.h                                               []
[] Date:            11.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                               
#ifndef stopwatch_H
#define stopwatch_H

#ifndef	WIN32
	#include <sys/time.h>
	#include <string.h>
#endif
#ifdef	WIN32
	#include <windows.h>
#endif

typedef double	TIMER_TYPE;
/*______________________________________________________________________________
[]                                                                            []
[]` СЕКУНДОМЕР                                                                []
[]                                                                            */
class	StopWatch
{
private:

#ifndef WIN32
	timeval	TimeStart;
	timeval	TimeEnd;
#endif

#ifdef WIN32
	LARGE_INTEGER	TimeStart;
	LARGE_INTEGER	TimeEnd;
	LARGE_INTEGER	Frequency;
#endif

public:
// Конструктор
	StopWatch();
// Запустить перед измеряемой функцией.
	void				Start		();
// Запустить после измеряемой функции.
	void				Stop		();
// Получить время работы.
	TIMER_TYPE		GetTime	();
};

extern	StopWatch		OBD_Timer;

#endif   // end of stopwatch_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/