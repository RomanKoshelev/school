/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'OBT'                                       []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            TestArgCache.cpp                                          []
[] Date:            15.11.1999                                                []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Тестируем кеш для результатов функции.                    []
[]____________________________________________________________________________[]
*/                                                                         
#include "ob.h"

//______________________________________________________________________________
//                                                                            []
//` MyFunction_factorial                                                      []                    
//                                                                            []
void MyFunction_factorial (int arg1, float& res1, bool& bCached)
{
	IF_CACHED_ARGS_1_RETURN_VOID (1000, arg1);

// Готового результата нет, надо сделать вычисления
	bCached = false;
	int i,j;
	for (j=0;j<10;j++)
	{
		for (i=1; i<=arg1; i++)
			res1 *= i;
	}


// Запоминаем результат вычислений
	CACHE_STORE_RESULT_1 (res1);
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` TestCache                                                                 []         
//                                                                            []
void TestCache ()
{
	int i;
	int NN=1000000;

	int  nCached=0;

	char SSS[256];
	for (i=0; i<NN; i++) 
	{
		PRINT_PERCENT (i, NN);

#if 0  //{ RomanVK
	// Факториал
		{
			int	arg1		= rand ()%1000;
			float res1		= 0;
			bool	bCached	= true;
			MyFunction_factorial (arg1, res1, bCached);
			if (bCached)
			{
				nCached++;
			}
		}
#endif //}
		sprintf (SSS, "\n\nCache size = %d  (Got from cache in: %d%% cases)\n", 1, 2);
	}
	printf ("\n\nCache size = %d  (Got from cache in: %d%% cases)\n", theArgResCache.GetSize(), nCached*100/NN);
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
