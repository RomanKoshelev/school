//______________________________________________________________________________
//                                                                            []
//` ОБЩАЯ ЧАСТЬ                                                               []           
//                                                                            []
long		SERVER_TIME_ZONE_OFFSET = 0;
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Получить смещение временной зоны                                          []                                
//                                                                            []
time_t GetTZOffset (void)
{
	time_t time_0 = time (NULL);
	tm LcTime; 	memcpy (&LcTime, localtime (&time_0), sizeof (tm));
	tm GmTime; 	memcpy (&GmTime, gmtime		(&time_0), sizeof (tm));

	LcTime.tm_isdst = -1;
	GmTime.tm_isdst = -1;
	
	time_t	TZOffset = mktime(&LcTime) - mktime(&GmTime);

	SERVER_DEBUG_VALUE (TZOffset);

	return TZOffset;
}
//____________________________________________________________________________[]

