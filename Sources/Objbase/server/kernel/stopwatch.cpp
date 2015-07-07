/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            stopwatch.cpp                                             []
[] Date:            11.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                 
#include "stopwatch.h"



//----------------------------------------------------------------------------[]
// Юникс
#ifndef WIN32
StopWatch::StopWatch ()
{
	bzero (&TimeStart,	sizeof (timeval));
	bzero (&TimeEnd,		sizeof (timeval));
}
void StopWatch::Start ()
{
	gettimeofday (&TimeStart,	NULL);
}
void StopWatch::Stop ()
{
	gettimeofday (&TimeEnd,		NULL);
}
TIMER_TYPE StopWatch::GetTime ()
{
	return TIMER_TYPE(TimeEnd.tv_usec - TimeStart.tv_usec)
			+ 1000*1000 * (TIMER_TYPE)(TimeEnd.tv_sec - TimeStart.tv_sec);
}
#endif
//----------------------------------------------------------------------------[]
// Винды
#ifdef WIN32
StopWatch::StopWatch ()
{
	ZeroMemory (&TimeStart, sizeof (LARGE_INTEGER));
	ZeroMemory (&TimeEnd,	sizeof (LARGE_INTEGER));
	if (!QueryPerformanceFrequency (&Frequency)) Frequency.QuadPart = 0;
}
void StopWatch::Start ()
{
	QueryPerformanceCounter (&TimeStart);
}
void StopWatch::Stop ()
{
	QueryPerformanceCounter (&TimeEnd);
}
TIMER_TYPE StopWatch::GetTime ()
{
	TIMER_TYPE inexact = (TIMER_TYPE)(TimeEnd.QuadPart - TimeStart.QuadPart);
	return inexact * 1000000 / Frequency.QuadPart;
}
#endif
//----------------------------------------------------------------------------[] 



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
