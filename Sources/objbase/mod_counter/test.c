

#include "mod_counter_call.c"



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` main                                                                      []    
[]                                                                            []
[]____________________________________________________________________________[]
*/
int main (int atgc, char **argv)
{
	int ExitCode, Total_Hits, Total_Hosts, nCallResult;		 

	OBJBASE_CALL_START();
	SET_FUNCTION ("BX_Counter_GetData");
	SET_ARG_IN ("Alias"							, "100000"	);
	SET_ARG_IN ("JustGetData"					, "1"			);

	SET_ARG_OUT ("ExitCode"			);
	SET_ARG_OUT ("Total_Hits"		);
	SET_ARG_OUT ("Total_Hosts"		);

	CALL_FUNCTION ();	 

	nCallResult = GET_FUNCTION_RESULT (NULL);

	printf ("\nExtracting ExitCode:    %d", GET_RETVALUE (Int,			"ExitCode",				ExitCode		));
	printf ("\nExtracting Total_Hits:  %d", GET_RETVALUE (Int,			"Total_Hits",			Total_Hits	));
	printf ("\nExtracting Total_Hosts: %d", GET_RETVALUE (Int,			"Total_Hosts",			Total_Hosts	));

	OBJBASE_CALL_END ();


	printf ("\n* * > ModuleStatus = %d\n", CNTD_Errno);
	printf ("CallResult = %d\n",	nCallResult);
	if (nCallResult == 0 && CNTD_Errno==CNTD_OKAY)
	{
		printf ("ExitCode     = %d\n",		ExitCode);
		printf ("Total_Hits   = %d\n",	Total_Hits);
		printf ("Total_Hosts  = %d\n", Total_Hosts);
	}

	return 0;
}
//____________________________________________________________________________[]


