

#if 0  //{ RomanVK
//______________________________________________________________________________
//                                                                            []
//` Проверка обратной сортировки																[]
//                                                                            []
void Test33 ()
{
	OC_Test_sort oc_test;

	int NNN = 24;

	for (i=0; i<NNN; i++)
	{
		PRINT_PERCENT (i,NNN);
		oc_test.New();

		oc_test.m_s1 = MakeRandomStr ("аб", 4, NULL, true);
		oc_test.m_s1 = MakeRandomStr ("аб", 4);//, NULL, true);
		oc_test.m_s2 = MakeRandomStr ("AZ", 2);
		oc_test.m_f1 = (float)(1.1 * (float)(rand()%4));
		oc_test.m_n1 = rand()%4;
	}
	
	oc_test.SetIndex__s1__s2();

//	Проверка поиска
	string sKey = "баб";
	printf ("\n\n");
	key_arr ka;
	ka+= sKey;
	oc_test.Find (ka, true);
	identifier objID = oc_test.GetObjectID ();
	printf ("Key = \"%s\"", win2dos(sKey.c_str()));

//	Проверка сортировки
	printf ("\n\n");
	for (i=0, oc_test.GoLast(); oc_test.IsValid(); oc_test--, i++)
	{
		string s1 = win2dos(((string)oc_test.m_s1).c_str());
		printf ("%4d: %c [%-10s %5s]\n", i, objID == oc_test.GetObjectID ()? '*': ' ', s1.c_str(), ((string)oc_test.m_s2).c_str());
	}

	oc_test.SetIndex_s1_s2();
	printf ("\n\n");
	for (i=0, oc_test.GoFirst(); oc_test.IsValid(); oc_test++, i++)
	{
		printf ("%4d:  [%5s %5s]\n", i, ((string)oc_test.m_s1).c_str(), ((string)oc_test.m_s2).c_str());
	}

	oc_test.SetIndex__s1_s2();
	printf ("\n\n");
	for (i=0, oc_test.GoFirst(); oc_test.IsValid(); oc_test++, i++)
	{
		printf ("%4d:  [%5s %5s]\n", i, ((string)oc_test.m_s1).c_str(), ((string)oc_test.m_s2).c_str());
	}

	oc_test.SetIndex_s1__s2();
	printf ("\n\n");
	for (i=0, oc_test.GoFirst(); oc_test.IsValid(); oc_test++, i++)
	{
		printf ("%4d:  [%5s %5s]\n", i, ((string)oc_test.m_s1).c_str(), ((string)oc_test.m_s2).c_str());
	}

	oc_test.SetIndex__s1__s2();
	printf ("\n\n");
	for (i=0, oc_test.GoFirst(); oc_test.IsValid(); oc_test++, i++)
	{
		printf ("%4d:  [%5s %5s]\n", i, ((string)oc_test.m_s1).c_str(), ((string)oc_test.m_s2).c_str());
	}


	oc_test.SetIndex_n1__f1();
	printf ("\n\n");
	for (i=0, oc_test.GoFirst(); oc_test.IsValid(); oc_test++, i++)
	{
		printf ("%4d:  [%5d %5.1f]\n", i, (int)oc_test.m_n1, (float)oc_test.m_f1);
	}
}
//____________________________________________________________________________[]
#endif //}






#if 0 //{` 09.08.99 RomanVK: 
//______________________________________________________________________________
//                                                                            []
//` Проверка полей-массивов																	[]
//                                                                            []
void Test34(void)
{
   OC_Array a;
   int i;
   const int N = 10;
   
   a.New();

   for (i = 0; i < N; i++){
      a.m_i.Add(i);
	}

   for (i = 1; i < N; i++)
	{
      a.m_i[i-1] = a.m_i[i];
	}

   for (i = 0; i < N; i++){
      printf("\n%d", (int)(a.m_i[i]));
	}
}
//____________________________________________________________________________[]
#endif //}0




#if 0  //{ RomanVK
//______________________________________________________________________________
//                                                                            []
//` Проверка быстрой загрузки/сохранения индексов										[]
//                                                                            []
void Test35(void)
{
   OC_Test_SaveLoadIndex oc_test;

	int NNN = 100*1000;

	for (i=0; i<NNN; i++)
	{
		PRINT_PERCENT (i,NNN);
		oc_test.New();

		oc_test.m_i = i;
	}

	int nReloads = 10;
	printf ("\n\nReloading all base %d times...", nReloads);
	clock_t ini_clock = clock();
	for (i=0; i<nReloads; i++)
	{
		oc_test.ReloadAllBase();
	}
	clock_t end_clock = clock();
	double duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n>> %.2f sec\n", duration/nReloads);

	printf ("\nTest...\n");
	for (oc_test.GoFirst (), i=0; oc_test.IsValid() && i<NNN; oc_test++, i++)
	{
		PRINT_PERCENT (i,NNN);
		SERVER_DEBUG_ASSERT (oc_test.m_i == i, "Ошибка перегрузки индексов!");

		//printf (" %12d\n", (int)oc_test.m_i);
	}
}
//____________________________________________________________________________[]

#endif //}



#if 0  //{ RomanVK
//______________________________________________________________________________
//                                                                            []
//` Проверка string::delete                                                   []                       
//                                                                            []
void Test36 ()
{
	string s; 
	s.Delete(); 
	s += "asabasdfb";
	s.Print();
}
//____________________________________________________________________________[]
#endif //}


//______________________________________________________________________________
//                                                                            []
//` stringURL                                                                 []          
//                                                                            []
/*

http://login:password @ domen /path/file.ext?args

*/

/*struct HTTP_URL
{
	string m_login;
	string m_password;
	string m_domen;
	string m_port;
	string m_path; 
	string m_file;
	string m_ext;
	string m_args;
	
	void DebugPrint ()
	{
		string ResURL = "";
		ResURL += "http:";
		ResURL += "//";

		if (m_login)
		{
			ResURL += m_login;
			if (m_password)
			{
				ResURL += ":";
				ResURL += m_password;
			}
			ResURL += "@";
		}
		ResURL += m_domen;
		if (m_port)
		{
			ResURL += ":";
			ResURL += m_port;
		}

		ResURL += "/";

		if (m_path)
		{
			ResURL += m_path;
			ResURL += "/";
		}

		if (m_file)
		{
			ResURL += m_file;
			if (m_ext)
			{
				ResURL += ".";
				ResURL += m_ext;
			}
		}
		if (m_args)
		{
			ResURL += "?";
			ResURL += m_args;
		}
	}
	void Parse (const char * strURL)
	{
		
	
	}
};

*/

//______________________________________________________________________________
//                                                                            []
//` Проверка Проверка string::ParseURL                                        []                       
//                                                                            []
void Test37 ()
{
	string qqq;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
