#if 0  //{ RomanVK
//______________________________________________________________________________
//                                                                            []
//` Сравнение с MySQL                                                         []                 
//                                                                            []
void Test50 ()
{
// Создание "таблицы"
	OC_tsmc_table oc_tsmc_table;
	oc_tsmc_table.DeleteClassObjects();

	int TABLE_SIZE = 1000;
	int i=0;
	for (i=0; i<TABLE_SIZE; i++)
	{
		PRINT_PERCENT (i, TABLE_SIZE);
		oc_tsmc_table.New();
		oc_tsmc_table.m_Int_Field		= i;
		oc_tsmc_table.m_Float_Field	= (float) (rand()%TABLE_SIZE);
	}
	printf ("\n");


// Изменение "таблицы"
	oc_tsmc_table.SetIndex_Int_Field_Float_Field_Text_Field();
	for (i=0; i<TABLE_SIZE; i++)
	{
		PRINT_PERCENT (i, TABLE_SIZE);
		key_arr ka;
		ka		+= i;

		oc_tsmc_table.Find (ka);
		oc_tsmc_table.m_Float_Field	= (float) (rand()%TABLE_SIZE);
		oc_tsmc_table.m_Int_Field		= TABLE_SIZE + i;
	}	
}
//____________________________________________________________________________[]
#endif //}






//______________________________________________________________________________
//                                                                            []
//` Работа с большими томами	( > 4 Gb )													[]
//                                                                            []
void __Test50 ()
{
// Создание "таблицы"
	OC_Test_4G oc_test;
	
	int	SIZE			= 10*1000;
	int	NN				= (5*1000*1000 / SIZE) * 1000;
	int	N				= 10*1000;
//	int	CACHE_SIZE	= 1000;

	char * pStr = new char [SIZE];
	memset (pStr, 'a', SIZE);
	pStr [SIZE-1] =0;

	CPtr<OC_Test_4G> CACHE;

	for (i=0; i<NN; i++)
	{
#if 0  //{ RomanVK
		PRINT_PERCENT (i, NN);
		oc_test.New();
		oc_test.m_i = i;
		oc_test.m_s = pStr;
		CACHE.Add (oc_test);
		if (CACHE.Size() >= CACHE_SIZE)
		{
			CACHE.Erase ();
		}
#endif //}
	}
	CACHE.Erase ();

	printf ("\n\n");

	pStr[0] = 'b';

	printf ("\n----------------------------\n");

	for (i=0; i<N; i++)
	{
		PRINT_PERCENT (i, N);
		int m_i;
		key_arr ka;

		do 
		{
			ka.Init();
			m_i = (rand ()*rand ())%NN;
			ka += m_i;
		} while (!oc_test.Find (ka));

		
		if (oc_test.m_i != m_i)
		{
			printf ("\n\nERROR: oc_test[%d].m_i=%d\n\n", i, (int)oc_test.m_i);
			break;
		}
		oc_test.m_s += pStr;
	}

	delete pStr;
	printf ("\n\n");
	getch ();
}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
void Test50 ()
{
// Создание "таблицы"
	OC_Test_4G oc_test;
	
	int	SIZE			= 100;
	int	NN				= (5*1000*1000 / SIZE);
//	int	N				= 10*1000;
	int	CACHE_SIZE	= 1000;

	char * pStr = new char [SIZE];
	memset (pStr, 'a', SIZE);
	pStr [SIZE-1] =0;

	CPtr<OC_Test_4G> CACHE;

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i, NN);
		oc_test.New();
		oc_test.m_i = i;
		oc_test.m_s = pStr;
		CACHE.Add (oc_test);
		if (CACHE.Size() >= CACHE_SIZE)
		{
			CACHE.Erase ();
		}
	}
	CACHE.Erase ();

	printf ("\n\n");

	delete pStr;
	printf ("\n\n");
	getch ();
}
//____________________________________________________________________________[]




