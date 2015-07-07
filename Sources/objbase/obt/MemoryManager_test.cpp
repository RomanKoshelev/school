#include "ob.h"

int PRINT_PERCENT(int i, int NN);


struct MM_Leak
{
	string * pStr;
	MM_Leak ()
	{
		puts ("MM_Leak()");
		pStr = new string;
	}
	~MM_Leak ()
	{
		puts ("~MM_Leak()");
		delete pStr;
	}
};

//______________________________________________________________________________
//                                                                            []
// Тестирование MemoryManager																	[]
//                                                                            []
void Test39 ()
{
	int			NN = 10000;//10*1000*1000;
	int			i;
	char	**		ppStr;
	
	static MM_Leak mm_leak;

	ppStr = new char* [NN];

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT(i, NN);
		ppStr[i] = new char[10];
	}

	printf ("\n\n");

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT(i, NN);
		delete ppStr[i];
	}

	delete [] ppStr;
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
