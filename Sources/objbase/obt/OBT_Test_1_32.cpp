//______________________________________________________________________________
//                                                                            []
//` TestServerDebug																				[]
//                                                                            []
void TestServerDebug()
{
	SERVER_DEBUG_STDOUT (false);

	bool	b1=true;
	bool	b2=false;
	int	dummy1=12356789;
	int	dummy2=-987654321;
	char *dummy3= "жываоп ждывоап ж жваодп";

	SERVER_DEBUG_ASSERT (b1,			"Comment 1");
	SERVER_DEBUG_ASSERT (b2,			"Comment 2");
	SERVER_DEBUG_ASSERT (b1 && b2,	"Comment 1 & 2");
	SERVER_DEBUG_ASSERT (b1 || b2,	"Comment 2 | 2");

	SERVER_DEBUG_PLACE;

	SERVER_DEBUG_VALUE (b1);
	SERVER_DEBUG_VALUE (b2);
	SERVER_DEBUG_VALUE (b1==b2);
	SERVER_DEBUG_VALUE (dummy1);
	SERVER_DEBUG_VALUE (dummy2);
	SERVER_DEBUG_VALUE (dummy1+dummy2);
	SERVER_DEBUG_VALUE (dummy3);
	SERVER_DEBUG_VALUE (&dummy3);
	SERVER_DEBUG_PLACE;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` TestString																						[]
//                                                                            []
void TestString ()
{
	CPtr<CPtr<string> > str_arr_arr;
	CPtr<string> str_arr;

	{
		string * pStr = new string ("This is a string");
		string str = *pStr;
		{
			str += string ('A');
		}
		str+=' ';
		str+="+ ";
		str+=str;
		str+="!";
		str+='.';
		str+=str[(int)str.len()-1];

		str_arr.Add(str);
		delete pStr;
		puts (str.c_str());
		puts (str_arr[0].c_str());

		str_arr_arr.Add(str_arr);
		puts (str_arr_arr[0][0].c_str());
	}
	puts (str_arr[0].c_str());
	puts (str_arr_arr[0][0].c_str());
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Работа с мелкими файлами																	[]
//                                                                            []
void Test1()
{
	identifier i;

	printf ("\nCreating:\n");
	for(i=0;i<10000;i++)
	{
		if (i%1000==0)
		{
			printf ("\nadd: i =%5d", i);
		}
		identifier ID=theFileDriver.Write((BYTE *)&theFileDriver,sizeof(theFileDriver));
	}
	identifier * pIdent = new identifier[theFileDriver.GetList()];
	theFileDriver.GetList(pIdent);
	identifier N = theFileDriver.GetList();

	printf ("\n\nDeleting:\n");
	for(i=0;i<N;i+=2)
	{
		if (i%1000==0)
		{
			printf ("\ndel: i =%5d", i);
		}
		theFileDriver.Delete(pIdent[i]);
	}
	delete pIdent;
	
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Работа с разными файлами																	[]
//                                                                            []
void Test2 ()
{
	identifier i;
	char * str1 = "Eto tipa takoj vesj iz sebja pervyj ob'ekt";
	char * str2 = "Eto tipa takoj vesj iz sebja vtoroj ob'ekt";
	char * str3 = "Eto tretij ob'ekt";

	identifier TEST_NUMBER = 11;

	printf ("\nCreating:\n");
	for(i=0;i<TEST_NUMBER;i++)
	{
		theFileDriver.Write (str1, strlen (str1)+1);
		theFileDriver.Write (str2, strlen (str2)+1);
		theFileDriver.Write (str3, strlen (str3)+1);
	}

// Получить список всех файлов	
	identifier * pIdent = new identifier[theFileDriver.GetList()];
	theFileDriver.GetList(pIdent);
	identifier nFileNumber = theFileDriver.GetList();
// Чтение всех файлов
	printf ("\nFiles: %d\n", nFileNumber);
	char SSS[1024];
	for(i=0;i<nFileNumber;i+=1)
	{	
		identifier FileID = pIdent[i];
		size_t nSize = theFileDriver.Read (FileID);
		theFileDriver.Read (FileID, SSS, nSize);
		printf ("\n%3d: [%3d] '%s' ", FileID, nSize, SSS);		
	}


// Удаление некоторых файлов
	printf ("\nDeleting...\n");
	for(i=0;i<nFileNumber;i+=2)
	{
		theFileDriver.Delete(pIdent[i]);
	}
	printf ("\nDeleted\n");

// Получить список всех файлов	
	pIdent = new identifier[theFileDriver.GetList()];
	theFileDriver.GetList(pIdent);
	nFileNumber = theFileDriver.GetList();
// Чтение всех файлов
	printf ("\nFiles:\n");
	for(i=0;i<nFileNumber;i+=1)
	{		
		size_t nSize = theFileDriver.Read (pIdent[i]);
		theFileDriver.Read (pIdent[i], SSS, nSize);
		printf ("\n%3d: [%3d] '%s' ", pIdent[i], nSize, SSS);		
	}

	delete pIdent;

	theFileDriver.PrintMap();
	
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Работа с крупными файлами																	[]
//                                                                            []
void Test3 ()
{
	int nArrSize = 100000;//1024*1024 - 9 - 9 - 9;
	int * pBulk = new int [nArrSize];
	identifier localID=UNKNOWN;

// Инициализация
	printf ("\nInitiation...");
	for (i=0; i<nArrSize; i++)
	{
		pBulk[i]=i;
	}
	printf ("\nInitialized...\n");


// Writing
	printf ("\nWriting...");
		localID = theFileDriver.Write (pBulk, sizeof(pBulk[0])*nArrSize);
	printf ("\nWritten = %d\n",sizeof(pBulk[0])*nArrSize);

	theFileDriver.PrintMap();
	return;

// Деинициализация
	printf ("\nDeInitiation...");
	for (i=0; i<nArrSize; i++)
	{
		pBulk[i]=0;
	}
	printf ("\nDeInitialized\n");


// Получить список всех файлов	
	identifier * pIdent = new identifier[theFileDriver.GetList()];
	theFileDriver.GetList(pIdent);
	identifier nFileNumber = theFileDriver.GetList();
	SERVER_DEBUG_ASSERT (nFileNumber==1, "");
	SERVER_DEBUG_ASSERT (localID==pIdent[0], "");
// Reading
	printf ("\nReading...");
		size_t nSize = theFileDriver.Read (localID);
		theFileDriver.Read (localID, pBulk, sizeof(pBulk[0])*nArrSize);
	printf ("\nRead= %d\n", nSize);


// Проверка
	printf ("\nChecking...");
	for (i=0; i<nArrSize; i++)
	{
		SERVER_DEBUG_ASSERT (pBulk[i]==i, "Cheking failed");
	}
	printf ("\nOK!\n");

	delete pBulk;
	delete pIdent;

	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Работа с мелким кластером в boot-файле												[]
//                                                                            []
void Test4 ()
{
	int nArrSize = 10;
	BYTE * pBulk = new BYTE [nArrSize];
	identifier localID;

// Инициализация
	printf ("\nInitiation...\n");
	for (i=0; i<nArrSize; i++)
	{
		pBulk[i]=i;
	}
	printf ("\nInitialized...\n");


// Writing
	printf ("\nWriting...\n");
		localID = theFileDriver.Write (pBulk, sizeof(pBulk[0])*nArrSize);
	printf ("\nWritten...\n");


// Деинициализация
	printf ("\nDeInitiation...\n");
	for (i=0; i<nArrSize; i++)
	{
		pBulk[i]=0;
	}
	printf ("\nDeInitialized...\n");

// Получить список всех файлов	
	identifier * pIdent = new identifier[theFileDriver.GetList()];
	theFileDriver.GetList(pIdent);
	identifier nFileNumber = theFileDriver.GetList();
	SERVER_DEBUG_ASSERT (nFileNumber==1, "");
	SERVER_DEBUG_ASSERT (localID==pIdent[0], "");
// Reading
	printf ("\nReading...\n");
		size_t nSize = theFileDriver.Read (localID);
		theFileDriver.Read (localID, pBulk, sizeof(pBulk[0])*nArrSize);
		printf ("\nRead= %d", nSize);
	printf ("\nWritten...\n");


// Проверка
	printf ("\nChecking...\n");
	for (i=0; i<nArrSize; i++)
	{
		SERVER_DEBUG_ASSERT (pBulk[i]==i, "Cheking failed");
	}
	printf ("\nOK!\n");

	delete pBulk;
	delete pIdent;

	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Работа с мелким кластером в boot-файле -- проверка переменной длины			[]
//                                                                            []
void Test5 ()
{
// int ArrOfSize [] = {10,11,12,13,14,15, 14,13,12,11,10};
//	int ArrOfSize [] = {1,2,4,8,16,32, 16,8,4,2,1};
	int ArrOfSize [] = {1,24,36,24,12,1}; //,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int ArrOfSizeNum = sizeof (ArrOfSize)/sizeof (ArrOfSize[0]);
	
	identifier localID [] = {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

	for (t=0; t<ArrOfSizeNum; t++) for (f=0; f<3; f++)
	{
		if (t>0 && f==0) continue;
		int nArrSize = ArrOfSize[t];

		printf ("\nCurrent size = %d\n----------------------------\n", nArrSize);
	// Инициализация
		BYTE * pBulk = new BYTE [nArrSize];
		printf ("\nInitiation...\n");
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=f+1;
		}
		printf ("Initialized...\n");


	// Writing
		printf ("\nWriting...\n");
			localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);
		printf ("Written...\n");


	// Деинициализация
		printf ("\nDeInitiation...\n");
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=0;
		}
		printf ("DeInitialized...\n");

	// Получить список всех файлов	
		identifier * pIdent = new identifier[theFileDriver.GetList()];
		theFileDriver.GetList(pIdent);
		identifier nFileNumber = theFileDriver.GetList();
		//SERVER_DEBUG_ASSERT (nFileNumber==10, "");
		//SERVER_DEBUG_ASSERT (localID[f]==pIdent[f], "");
	// Reading
		printf ("\nReading...\n");
			size_t nSize = theFileDriver.Read (localID[f]);
			theFileDriver.Read (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);
		printf ("Read = %d", nSize);

		if(f==2 && t==0) {
			theFileDriver.Delete(localID[0]);
			localID[0]=UNKNOWN;
		}

	// Проверка
		printf ("\nChecking...\n");
		for (i=0; i<nArrSize; i++)
		{
			SERVER_DEBUG_ASSERT (pBulk[i]==f+1, "Cheking failed");
		}
		printf ("OK!\n");

		delete pBulk;
		delete pIdent;
	}
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Работа с мелким кластером в boot-файле -- random									[]
//                                                                            []
void Test6 ()
{
	printf("1\n");
	identifier localID [10];
	int localIDNum=sizeof (localID)/sizeof (localID[0]);
	for (f=0; f< localIDNum; f++)
		localID [f] = UNKNOWN;
	printf("2\n");

	srand(time(0));

	printf("3\n");

	for (t=0; t<10; t++) for (f=0; f<localIDNum; f++)
	{
		int nArrSize = rand()%20+1;

		printf ("\nt=%2d,f=%2d,size=%2d",t,f,nArrSize);
	//	printf ("\nCurrent size = %d\n----------------------------\n", nArrSize);
	// Инициализация
		BYTE * pBulk = new BYTE [nArrSize];
	//	printf ("\nInitiation...\n");
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=f+1;
		}
	//	printf ("Initialized...\n");


	// Writing
	//	printf ("\nWriting...\n");
			if(localID[f]==UNKNOWN)
				printf(" ++ ");
			localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);
	//	printf ("Written...\n");


	// Деинициализация
	//	printf ("\nDeInitiation...\n");
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=0;
		}
	//	printf ("DeInitialized...\n");

	// Получить список всех файлов	
		identifier * pIdent = new identifier[theFileDriver.GetList()];
		theFileDriver.GetList(pIdent);
		identifier nFileNumber = theFileDriver.GetList();
		//SERVER_DEBUG_ASSERT (nFileNumber==10, "");
		//SERVER_DEBUG_ASSERT (localID[f]==pIdent[f], "");
	// Reading
	//	printf ("\nReading...\n");
			size_t nSize = theFileDriver.Read (localID[f]);
			theFileDriver.Read (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);
	//	printf ("Read = %d", nSize);
	 
		if(rand()%6 == 0) {
			int who=rand()%localIDNum;
			if(localID[who]!=UNKNOWN) {
				theFileDriver.Delete(localID[who]);
				localID[who]=UNKNOWN;
				printf (" -- ");
			}
		}

	// Проверка
	//	printf ("\nChecking...\n");
		for (i=0; i<nArrSize; i++)
		{
			SERVER_DEBUG_ASSERT (pBulk[i]==f+1, "Cheking failed");
		}
	//	printf ("OK!\n");

		delete pBulk;
		delete pIdent;
	}
	theFileDriver.PrintMap();
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Проверка нового формата  файлов															[]
//                                                                            []
void Test7 ()
{
	char SSS[256];
	identifier ID=theFileDriver.Write("12345", 6);
	theFileDriver.Read (ID, SSS, 6);
	puts (SSS);
	theFileDriver.Delete (ID);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Проверка замораживания возможность перехода на нижний уровень					[]
//                                                                            []
void Test8 ()
{
	int ArrOfSize [] = {1,2,3,4,5,10,9,8,7,6,5,4,3,2,1};
	int ArrOfSizeNum = sizeof (ArrOfSize)/sizeof (ArrOfSize[0]);
	
	identifier localID [] = {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

	for (t=0; t<ArrOfSizeNum; t++) for (f=0; f<1; f++)
	{
		if (t>=14)
			theFileDriver.flush ();

		int nArrSize = ArrOfSize[t];
		printf ("\n-----------------------------------\nt   =%d\nSize=%d", t, nArrSize);

	// Инициализация
		BYTE * pBulk = new BYTE [nArrSize];
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=f+1;
		}


	// Writing
		localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

	// Деинициализация
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=0;
		}

	// Получить список всех файлов	
		identifier * pIdent = new identifier[theFileDriver.GetList()];
		theFileDriver.GetList(pIdent);
		identifier nFileNumber = theFileDriver.GetList();
	// Reading
		size_t nSize = theFileDriver.Read (localID[f]);
		theFileDriver.Read (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

		if(f==2 && t==0) {
			theFileDriver.Delete(localID[0]);
			localID[0]=UNKNOWN;
		}

	// Проверка
		for (i=0; i<nArrSize; i++)
		{
			SERVER_DEBUG_ASSERT (pBulk[i]==f+1, "Cheking failed");
		}

		delete pBulk;
		delete pIdent;

		theFileDriver.PrintMap ();
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Работа с файлами разного размера random запись 									[]
//                                                                            []
void Test9 ()
{
	identifier localID [1000];
	int localIDNum=sizeof (localID)/sizeof (localID[0]);

	srand(time(0));
	for (f=0; f< localIDNum; f++)
		localID [f] = UNKNOWN;

	for (t=0; t<10; t++) for (f=0; f< localIDNum; f++)
	{
		int arrNN [] = {10, 20, 100, 200, 300, 400, 1000, 2000, 10000, 20000};
		int arrNNnum = sizeof (arrNN)/sizeof (arrNN[0]);
		int nArrSize = rand()%arrNN[rand()%arrNNnum]+1;

		if (f%100==0)
		{
			printf ("\n\n-----------");
			printf ("\nt = %5d",t);
			printf ("\nf = %5d",f);
			printf ("\ns = %5d",nArrSize);
			//theFileDriver.PrintMemoryReport ();
		}

	// Инициализация
		int * pBulk = new int [nArrSize];
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=f+1;
		}

	// Writing
		localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

	// Читаем каждый десятый
		if (rand ()%10)
		{
		// Деинициализация
			for (i=0; i<nArrSize; i++)
			{
				pBulk[i]=0;
			}

		// Получить список всех файлов	
			identifier nFileNumber = theFileDriver.GetList();
		// Reading
			size_t nSize = theFileDriver.Read (localID[f]);
			theFileDriver.Read (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

			if(rand()%6 == 0) {
				int who=rand()%localIDNum;
				if(localID[who]!=UNKNOWN) {
					theFileDriver.Delete(localID[who]);
					localID[who]=UNKNOWN;
				}
			}

		// Проверка
			for (i=0; i<nArrSize; i++)
			{
				SERVER_DEBUG_ASSERT (pBulk[i]==f+1, "Cheking failed");
			}
		}

		delete pBulk;
	}
	//theFileDriver.PrintMap ();
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Работа с большим числом файлов															[]
//                                                                            []
void Test10 ()
{
	identifier localID [10000];
	int localIDNum=sizeof (localID)/sizeof (localID[0]);

	for (f=0; f< localIDNum; f++)
		localID [f] = UNKNOWN;

	for (t=0; t<10; t++) for (f=0; f< localIDNum; f++)
	{
		int nArrSize = 1;

		if (f%1000==0)
		{
			theFileDriver.PrintMemoryReport ();
		}

	// Инициализация
		int * pBulk = new int [nArrSize];
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=f+1;
		}


	// Writing
		localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);


	// Деинициализация
		for (i=0; i<nArrSize; i++)
		{
			pBulk[i]=0;
		}

	// Получить список всех файлов	
		identifier * pIdent = new identifier[theFileDriver.GetList()];
		theFileDriver.GetList(pIdent);
		identifier nFileNumber = theFileDriver.GetList();
	// Reading
		size_t nSize = theFileDriver.Read (localID[f]);
		theFileDriver.Read (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

	// Проверка
		for (i=0; i<nArrSize; i++)
		{
			SERVER_DEBUG_ASSERT (pBulk[i]==f+1, "Cheking failed");
		}

		delete pBulk;
		delete pIdent;
	}
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Работа с файлами разного размера random создание и считывание					[]
//                                                                            []
void Test11 ()
{
	identifier localID [10000];
	int localIDNum=sizeof (localID)/sizeof (localID[0]);

	srand(time(0));
	for (f=0; f< localIDNum; f++)
		localID [f] = UNKNOWN;

	for (t=0; t<2; t++) for (f=0; f< localIDNum; f++)
	{
		if (t==0)
		{
			int arrNN [] = {10, 20, 100, 200, 300, 400, 1000, 2000, 10000, 20000, 100000, 200000};
			int arrNNnum = sizeof (arrNN)/sizeof (arrNN[0]);
			int nArrSize = (rand()%arrNN[rand()%arrNNnum])+1;

			if (f%100==0)
			{
				printf ("\n\nWriting:\n-----------");
				printf ("\nt = %5d",t);
				printf ("\nf = %5d",f);
				printf ("\ns = %5d",nArrSize);
			}

		// Инициализация
			int * pBulk = new int [nArrSize];
			for (i=0; i<nArrSize; i++)
			{
				pBulk[i]=f+i;
			}
			pBulk [0] = nArrSize;

		// Writing
			localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

			delete pBulk;
		}

	// Читаем случайный файл
		if (t>0)
		{
			int randF = rand()%localIDNum;
			size_t nSize = theFileDriver.Read (localID[randF]);
			int * pBulk = new int [nSize/2];
			theFileDriver.Read (localID[randF], pBulk, nSize);
			nSize = pBulk[0];

			if (f%1000==0)
			{
				printf ("\n\nReading:\n-----------");
				printf ("\nt = %5d",t);
				printf ("\nf = %5d",f);
				printf ("\ns = %5d",nSize);
			}

		// Проверка
			for (size_t i=1; i<nSize; i++)
			{
				SERVER_DEBUG_ASSERT (pBulk[i]==randF+(int)i, "Cheking failed");
			}
			delete pBulk;
		}
	}
	printf ("\n\n");
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Работа с созданными файлами разного размера считывание							[]
//                                                                            []
void Test12 ()
{
	int localIDNum=theFileDriver.GetList();
	identifier * localID = new identifier[localIDNum];
	theFileDriver.GetList (localID);

	for (f=0; f<localIDNum; f++)
	{
	// Читаем файл
		size_t nSize = theFileDriver.Read (localID[f]);
		int * pBulk = new int [nSize/2];
		theFileDriver.Read (localID[f], pBulk, nSize);
		nSize = pBulk[0];

		if (f%1000==0)
		{
			printf ("\n\nf = %5d [%d]",f,localIDNum);
			printf ("\ns = %5d",nSize);
		}

	// Проверка
		for (size_t i=1; i<nSize; i++)
		{
			SERVER_DEBUG_ASSERT (pBulk[i]==f+(int)i, "Cheking failed");
		}
		delete pBulk;
	}
	printf ("\n\n");
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Работа с многими файлами одного размера												[]
//                                                                            []
void Test13 ()
{
	identifier localID [10000];
	int localIDNum=sizeof (localID)/sizeof (localID[0]);

	srand(time(0));
	for (f=0; f< localIDNum; f++)
		localID [f] = UNKNOWN;

	for (k=0; k<10; k++) for (t=0; t<10; t++) for (f=0; f< localIDNum; f++)
	{
		if (f==0)
		{
			theFileDriver.flush ();
		}
		if (t==0)
		{
			int arrNN [] = {10, 20, 100, 200, 300, 400, 1000, 2000, 10000, 20000};
			int arrNNnum = sizeof (arrNN)/sizeof (arrNN[0]);
			//int nArrSize = (rand()%arrNN[rand()%arrNNnum])+1;
			int nArrSize = 128;

			if (f%1000==0)
			{
				printf ("\nWriting: %5d\n", f + t*localIDNum + k*localIDNum*10);
			}

		// Инициализация
			int * pBulk = new int [nArrSize];
			for (i=0; i<nArrSize; i++)
			{
				pBulk[i]=f+i;
			}
			pBulk [0] = nArrSize;

		// Writing
			localID[f] = theFileDriver.Write (localID[f], pBulk, sizeof(pBulk[0])*nArrSize);

			delete pBulk;
		}

	// Читаем случайный файл
		if (t>0)
		{
			int randF = rand()%localIDNum;
			size_t nSize = theFileDriver.Read (localID[randF]);
			int * pBulk = new int [nSize/2];
			theFileDriver.Read (localID[randF], pBulk, nSize);
			nSize = pBulk[0];

			if (f%1000==0)
			{
				printf ("\nReading: %5d", f + t*localIDNum + k*localIDNum*10);
			}

		// Проверка
			for (size_t i=1; i<nSize; i++)
			{
				SERVER_DEBUG_ASSERT (pBulk[i]==randF+(int)i, "Cheking failed");
			}
			delete pBulk;
		}
	}
	printf ("\n\n");
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Создание и запись 100,000,0000 объектов по 1 байту								[]
//                                                                            []
void Test14()
{
	SERVER_DEBUG_PLACE;
	
	for (f=0; f< 10000000; f++)
	{
	// Writing
		int C1=f;
		identifier ID = theFileDriver.Write (&C1, sizeof (C1));

	// Readin
		int C2=0;
		theFileDriver.Read (ID, &C2, sizeof (C1));
		SERVER_DEBUG_ASSERT (C1==C2, "");

		if (f%10000==0)
		{
			printf ("\nWriting: %10d\n", f);
		}

		if (f && (f%1000==0))
		{
			theFileDriver.Delete (f/2);
		}
		if (f && (f%100000==0))
		{
			theFileDriver.flush ();
		}
	}
	printf ("\n\n");
	SERVER_DEBUG_PLACE;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` Создание файла; чтение и запись блоков с изменением размера					[]
//                                                                            []
void Test15()
{
	CFile arrFile[10];
	for(f=0;f<10;f++) {
		arrFile[f].CreateOpen();
		arrFile[f].Alloc(1);
		arrFile[f][0]=(BYTE)f;
	}
	srand(time(0));
	for(t=0;t<10;t++) {
		for(f=0;f<10;f++) {
			size_t nOffset	= rand()%10+1;
			size_t nSize	= rand()%10+1;
			printf("\n nOffset = %d, nSize = %d",nOffset,nSize);
			arrFile[f].Realloc(nSize);
			for(i=0;i<(int)nSize;i++)
				arrFile[f][i]=i+nOffset;
			arrFile[f].Seek(nOffset);
			arrFile[f].Write();
			for(i=0;i<(int)nSize;i++)
				arrFile[f][i]=0;
			arrFile[f].Seek(nOffset);
			arrFile[f].Read(nSize);
			for(i=0;i<(int)nSize;i++)
				SERVER_DEBUG_ASSERT (*(arrFile[f]+i)==(i+(int)nOffset), "Error");
			nSize	= rand()%10+1;
			printf("\n\nSize = %d",nSize);
			arrFile[f].SetSize(nSize);
		}
		theFileDriver.PrintMap ();
		theFileDriver.flush();
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Работа с CFile -- random																	[]
//                                                                            []
void Test16 ()
{
	CFile arrFile [10];
	int localIDNum=10;

	srand(time(0));

	int nDelete =0;
	for (t=0; t<10; t++) for (f=0; f<localIDNum; f++)
	{
		int nArrSize = rand()%20+1;

		printf ("\nt=%2d,f=%2d,size=%2d",t,f,nArrSize);
	//	printf ("\nCurrent size = %d\n----------------------------\n", nArrSize);
	// Инициализация
		if(!arrFile[f].IsValid()) {
			arrFile[f].CreateOpen();
			printf(" ++ ");
		}
		arrFile[f].Alloc(nArrSize);
		arrFile[f].SetSize(nArrSize);
		for (i=0; i<nArrSize; i++)
		{
			arrFile[f][i]=f+1;
		}
	//	printf ("Initialized...\n");


	// Writing
	//	printf ("\nWriting...\n");
			arrFile[f].Save();
	//	printf ("Written...\n");


	// Деинициализация
	//	printf ("\nDeInitiation...\n");
		for (i=0; i<nArrSize; i++)
		{
			arrFile[f][i]=0;
		}
	//	printf ("DeInitialized...\n");

		arrFile[f].Load();
	//	printf ("Read = %d", nSize);
	 
		if(rand()%6 == 0) {
			int who=rand()%localIDNum;
			if(arrFile[f].IsValid()) {
				arrFile[f].Delete();
				printf (" -- ");
				nDelete ++;
			}
		}

	// Проверка
	//	printf ("\nChecking...\n");
		for (i=0; i<nArrSize; i++)
		{
			SERVER_DEBUG_ASSERT (arrFile[f][i]==f+1, "Cheking failed");
		}
	//	printf ("OK!\n");

	}
	theFileDriver.PrintMap();
	printf ("\n\nThat's all.\n\n");
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Проверка работы объектов по ID															[]
//                                                                            []
void Test17 ()	
{
	theObjDriver.Compile	(SRC_LAYOUT_FILE);

	//theObjDriver.PrintFormat();


	string dbg="";
	identifier objID = NA;

	int i;

	puts ("Arrays initiation...");
	int NNN = 10*1000;
	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;

	CPtr<identifier>	arrID  = NNN;
	CPtr<OC_Test1>		arrObj = NNN;
	puts ("Objects creation ...");

	for (i=0; i<NNN; i++)
	{
		arrObj[i].New  ();

		arrObj[i].m_Name	 = "!";
		arrObj[i].m_Number = (i+1)*1000;
		arrObj[i].m_Age	 = i+1;
		arrObj[i].m_Text  += "123";
		arrObj[i].m_Text  += "000";
		arrObj[i].m_Text[1]= "32";
		arrObj[i].m_Text[1]+="1";
		arrObj[i].m_References  += i*10;
		arrObj[i].m_Flag	 = (arrObj[i].m_Age%(byte)2)==0;

		//arrObj[i].DebugPrint(dbg);
		//printf ("%s", dbg.c_str());

		arrID[i] = arrObj[i].GetObjectID();

		if (i%NN==0) printf ("i = %6d\r\n", i+NN);
	}
	puts ("\r\n-----------------------------------\n\n\r\n\r\n");

	puts ("\r\n\r\n\r\n-----------------------------------\n\nChecking in memory...");
	for (i=0; i<NNN; i++)
	{
		SERVER_DEBUG_ASSERT ((arrObj[i].m_Number == (i+1)*1000)  &&  (arrObj[i].m_Text[1] == string ("321")) , "");
		if (i%NN==0) printf ("i = %6d\r\n", i+NN);
	}
	
	puts ("\r\n\r\n\r\n-----------------------------------\n\nWriting...");
	arrObj = (int)0;
	arrObj = NNN;
	
	puts ("\r\n\r\n\r\n-----------------------------------\n\nChecking with loading...");
	for (i=0; i<NNN; i++)
	{
		arrObj[i] = arrID[i];

		//arrObj[i].DebugPrint(dbg);
		//printf ("%s", dbg.c_str());

		SERVER_DEBUG_ASSERT ((arrObj[i].m_Number == (i+1)*1000)  &&  (arrObj[i].m_Text[1] == string ("321")) , "");
		if (i%NN==0) printf ("i = %6d\r\n", i+NN);
	}
	puts ("\r\n\r\n\r\n-----------------------------------\n\nDestruction...\r\n");

}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//` Проверка AddRef & Release																	[]
//                                                                            []
void Test18 ()
{
	theObjDriver.Compile	(SRC_LAYOUT_FILE);
	theObjDriver.PrintFormat	();

	{
	OC_Test0 Test[10];

	for (int i=0; i<10; i++) 
	{
		Test[i].New  ();
		Test[i].m_Number = 9-i;
	}

	puts ("");
	}
//	Test1.m_Age = 1;
//	Test2.m_Age = 2;
//	Test3.m_Age = 3;

	puts ("");

	OC_Test0 test;

	OC_Test0 test1 = test;
	
	test1 = test;

	test1 == test;
	test1 != test;

	test1 == ((identifier)test);
	test1 != ((identifier)test);

	test1.New ();
	test1.m_Name = "!";
	test1.Delete ();

	test.SetIndex_Number_Name_Flag_Age();
	for (test = test.First(), i=0; test!=test.Last() && test!=NA; test++, i++)
	{
		printf ("%4d:   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d] \r\n", i+1, (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
	}

	puts ("");
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
// Проверка работы объектов по индексам													[]
//                                                                            []
void Test19 ()	
{
//	theObjDriver.Compile	(SRC_LAYOUT_FILE);
//	theObjDriver.PrintFormat	();

	string dbg="";
	
	//identifier objID = NA;
	//OC_Test1 test;
	//test.m_Number = 1000;
	//return;

	int i;

	puts ("Arrays initiation...");
	
//RVK:>>>
	int NNN = 1000;
	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;
	
	int nDelete=0;

	CPtr<identifier>	arrID  = NNN;
	CPtr<OC_Test0>		arrObj = NNN;

	puts ("Objects creation ...\r\n");
	for (i=0; i<NNN; i++)
	{
		arrObj[i].New  ();
		if (NNN<=10 || (i%NN==0)) printf ("i = %6d\r\n", i+NN);
	}

	puts ("\n\nObjects modification...\r\n");
	for (i=0; i<NNN; i++)
	{
		char SSS [256];
		MakeRandomStr ("  qweeertyuuiiiioooplkjhgfddssaaazxcvbbnmnm", 10, SSS);
		//MakeRandomStr ("ABC", 4, SSS);

		arrObj[i].m_Name	 = SSS;
		arrObj[i].m_Number = rand()%3;
		arrObj[i].m_Age	 = 27+rand()%3;
		arrObj[i].m_Text  += "123";
		arrObj[i].m_Text  += "000";
		arrObj[i].m_Text[1]= "32";
		arrObj[i].m_Text[1]+="1";
		arrObj[i].m_References  += i*10;
		arrObj[i].m_Flag	 = (arrObj[i].m_Age%(byte)2)==0;

		//arrObj[i].DebugPrint(dbg);
		//printf ("%s", dbg.c_str());

		arrID[i] = arrObj[i].GetObjectID();
		if (i>1 && (rand ()%5)==0)
		{
			int iDel = rand()%(i-1);
			if (arrObj[iDel].IsValid ())
			{
				arrObj[iDel].Delete ();
				nDelete ++;
			}
			arrID[iDel] = NA;
		}

		if (NNN<=10 || (i%NN==0)) printf ("i = %6d\r\n", i+NN);
	}
	puts ("\r\n-----------------------------------\n\n\r\n\r\n");



	puts ("\r\n\r\n\r\n-----------------------------------\n\nSetting random value...");
	for (i=0; i<NNN; i++) if ((rand()%10)==0)
	{
		int r = rand()%NNN;
		if (arrObj[r].IsValid ())
		{
			arrObj[r].m_Age	 = 16+(rand()%60);
			arrObj[r].m_Flag	 = (arrObj[r].m_Age%(byte)2)==0;
		}

		if (NNN<=10 || (i%NN==0)) printf ("i = %6d\r\n", i+NN);
	}


	puts ("\r\n\r\n\r\n-----------------------------------\n\nChecking in memory...");
	for (i=0; i<NNN; i++)
	{
		if (arrObj[i].IsValid())
		{
			//arrObj[i].DebugPrint(dbg);
			//printf ("%s", dbg.c_str());

			string text_str = arrObj[i].m_Text[1];
			SERVER_DEBUG_ASSERT (text_str == string ("321") , "Объект не выдержал проверки полей.");
		}
		if (NNN<=10 || (i%NN==0)) printf ("i = %6d\r\n", i+NN);
	}

	
	puts ("\r\n\r\n\r\n-----------------------------------\n\nWriting...");
	arrObj = (int)0;
	arrObj = NNN;
	
	puts ("\r\n\r\n\r\n-----------------------------------\n\nChecking with loading...");
	for (i=0; i<NNN; i++)
	{
		identifier objID = arrID[i];
		if (objID!=NA) 
			arrObj[i] = objID;

		if (arrObj[i].IsValid())
		{
			//arrObj[i].DebugPrint(dbg);
			//printf ("%s", dbg.c_str());

			string text_str = arrObj[i].m_Text[1];
			SERVER_DEBUG_ASSERT (text_str == string ("321") , "Объект не выдержал проверки полей.");
		}

		if (NNN<=10 || (i%NN==0))  printf ("i = %6d %s\r\n", i+NN, arrObj[i].IsValid()? "" :"-");
	}

	OC_Test0 test_in_mem;
	for (i=NNN/2; i>=0 && test_in_mem==NA; i--)
	{
		test_in_mem = arrObj[i];
	}
	if (test_in_mem==NA)
	{
		puts ("!!");
	}

	puts ("\r\n\r\n\r\n-----------------------------------\n\nClose data objects...");
	arrObj = (int)0;
	arrID  = (int)0;


	if(test_in_mem) for (i=0;i<10;i++)
	{
		OC_Test0 tt;
		tt.New();
		tt.m_Number = test_in_mem.m_Number;
		tt.m_Name   = test_in_mem.m_Name;
		tt.m_Age    = 27+(rand()%10);
		tt.m_Flag   = (tt.m_Age%(byte)2)==0;
	}

	puts ("\r\n\r\n\r\n-----------------------------------\n\nSeek Index and load each object...\r\n");
	OC_Test0 test;
	test.SetIndex_Number_Name_Flag_Age();
	for (test.GoFirst(), i=0; test; test++, i++)
	{
		if (i%NN==0)  printf ("%4d:   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d] \r\n", i+1, (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
	}
	printf ("\r\n%4d Total  -- %d was deleted.", i+nDelete, nDelete);


	puts ("\r\n\r\n\r\n-----------------------------------\n\nSearch...\r\n");

	test = NA;
	key_arr ka;
	ka += (int)1;
	ka += "AAA";
	printf ("\r\n\r\n---------------------------\r\nSearch key: ");
	ka.DebugPrint();
	if (test.Find (ka, true)) 
	{
		puts ("\r\nFind:");
		for (; test; test.GoNext(&ka))
		{
			printf ("   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d]\r\n", (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
			printf (test==ka? "Exactly": "Inexactly");
		}
	}
	else
	{
		puts ("\r\nNot found");
	}
	
	if (test_in_mem!=NA)
	{
		ka.Init();
		ka += (int)test_in_mem.m_Number;
		ka += (const char *)test_in_mem.m_Name;
		ka += (bool)test_in_mem.m_Flag;
		ka += (byte)test_in_mem.m_Age;
		printf ("\r\n\r\n---------------------------\r\nSearch key: ");
		ka.DebugPrint();
		if (test.Find (ka))
		{
			puts ("\r\nFind:");
			printf ("   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d]\r\n", (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
		}
		else
		{
			SERVER_DEBUG_ASSERT (test.Find (ka), "Error searchig existing object!");
		}

//RVK:>>>
		ka.Init();
		ka += (int)test_in_mem.m_Number;
		ka += (const char *)test_in_mem.m_Name;
		ka += (bool)test_in_mem.m_Flag;
		printf ("\r\n\r\n---------------------------\r\nSearch key: ");
		ka.DebugPrint();
		printf ("\r\nTotal number with this key  = %d:\r\n", test.GetIndexTotalNum(ka));
		for (test.Find (ka); test; test.GoNext(&ka))
		{
			printf ("   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d]\r\n", (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
			SERVER_DEBUG_ASSERT (test==ka, "Объект не равен ключу");
		}
		printf ("\r\nUnique number with this key = %d.\r\n", test.GetIndexUniqueNum(ka));
		for (test.Find (ka); test; test.GoNext(&ka, true))
		{
			printf ("   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d]\r\n", (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
			SERVER_DEBUG_ASSERT (test==ka, "Объект не равен ключу");
		}
	}


	puts ("\r\n\r\n\r\n-----------------------------------\n\nDestruction...\r\n");
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` Проверка шаблона CObject																	[]
//                                                                            []
void Test20 ()
{
	theObjDriver.Compile	(SRC_LAYOUT_FILE);

	OC_Test0 Test;

	Test.New();

	Test.m_Age = 1;
	Test.m_Number = 2;
	Test.m_Name = "3";
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//` Проверка записи/считывания индексов													[]
//                                                                            []
void Test21 ()
{
	//theObjDriver.Compile	(SRC_LAYOUT_FILE);

	string dbg;
	OC_Test0 test;
	test.SetIndex_Number_Name_Flag_Age();


//RVK:>>> Test21 -- инициализация
	puts ("\r\nObjects creation ...\r\n");
	int NNN = 10*1000;
	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;	
	CPtr<OC_Test0>		arrObj = NNN;
	int N = rand()%NNN;
	for (i=0; i<NNN; i++)
	{
		arrObj[i].New  ();

		char SSS [256];
		MakeRandomStr ("qweeertyuuiiiioooplkjhgfddssaaazxcvbbnmnm", 4, SSS);
		//MakeRandomStr ("01", 4, SSS);

		arrObj[i].m_Number = rand()%2;
		arrObj[i].m_Name	 = SSS;
		arrObj[i].m_Age	 = 27+rand()%3;
		arrObj[i].m_Flag	 = (arrObj[i].m_Age%(byte)2)==0;

		if (NNN<=10 || (i%NN==0)) printf ("  i = %6d\r\n", i+NN);
	}



//RVK:>>> 
// Удаление части объектов при каждом втором запуске программы
	if (0)//((int)test.GetTotalNum()>NNN)
	{
		printf ("\r\n\r\n\r\nDeleting objects whith key:");
		NNN = test.GetTotalNum();
			key_arr ka;
			ka +=	(int)				arrObj[N].m_Number;
			ka +=	(const char *) arrObj[N].m_Name;
		printf ("\r\n- - - - - - - - - - - - \r\n   ");
			ka.DebugPrint();
		printf ("- - - - - - - - - - - - \r\n");

		test.Delete (ka);
		printf ("Was: %d obects, %d deleted\r\n", NNN, NNN-test.GetTotalNum());
	}



//RVK:>>> Test21 -- поиск и подсчёт
	puts ("\r\n\r\n\r\n\r\nSeek index and load each object...");
	test.SetIndex_Number_Name_Flag_Age();

	NNN = test.GetTotalNum();
	NN =	NNN <=      10?      1:
			NNN <=     100?     10:
			NNN <=    1000?    100:
			NNN <=   10000?   1000:
			NNN <=  100000?  10000:
			NNN <= 1000000? 100000:	1000000;	
	printf ("Total objects number: %d\r\n", NNN);

	for (test = test.First(), i=0; test; test++, i++)
	{
		if (i%NN==0)  printf ("%7d:   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d] \r\n", i, (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
	}



	puts ("\r\n\r\n\r\n\r\nSeek index and load each unique object...");
	NNN = test.GetIndexUniqueNum();
	NN =	NNN <=      10?      1:
			NNN <=     100?     10:
			NNN <=    1000?    100:
			NNN <=   10000?   1000:
			NNN <=  100000?  10000:
			NNN <= 1000000? 100000:	1000000;	
	printf ("Unique objects number in current index: %d\r\n", NNN);
	for (test = test.First(), i=0; test; test.GoNextUniqeu(), i++)
	{
		if (i%NN==0)  printf ("%7d:   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d] \r\n", i, (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);
	}

	if (arrObj[N].IsValid())
	{
		printf ("\r\n\r\n\r\n\r\n");
		arrObj[N].DebugPrint (dbg);
		dbg.Print();
		key_arr ka;
			ka +=	(int)				arrObj[N].m_Number;
			ka +=	(const char *) arrObj[N].m_Name;
			ka +=	(bool)			arrObj[N].m_Flag;
		int nTimes = ka.GetKeyNum()==0? 10: ka.GetKeyNum()==1? 100: 10000;
		printf ("\r\rCount %d times with key:", nTimes);
			printf ("\r\n- - - - - - - - - - - - \r\n   ");
			ka.DebugPrint();
			printf ("- - - - - - - - - - - - \r\n");
		for (j=0; j<nTimes; j++)
			test.GetIndexTotalNum(ka);
		printf ("Total number with key: %d\r\n", test.GetIndexTotalNum(ka));
		for (j=0; j<nTimes; j++)
			test.GetIndexUniqueNum(ka);
		printf ("Unique number with key: %d\r\n", test.GetIndexUniqueNum(ka));
	}

	puts ("\r\n\r\n\r\n");

	theFileDriver.PrintMemoryReport ();

	puts ("\r\n\r\nDestruction...\r\n");
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Проверка записи/считывания объектов													[]
//                                                                            []
//RVK:>>>22
void Test22 ()
{
	int					NNN = 100*1000;
	OC_Test0				test;
	CPtr<identifier>	id_arr;

	printf ("\nObjects creation...\n");
	for (i=0; i<NNN; i++)
	{
		test.New();
		id_arr.Add(test.GetObjectID());
		PRINT_PERCENT (i, NNN);
	}



	printf ("\nObjects loading...\n");
	test.SetIndex_Age();
	test.GoFirst();
	SERVER_DEBUG_ASSERT (test.IsValid(), "");
	for (i=0; test; i++)
	{
		test.GoNext();
		PRINT_PERCENT (i, test.GetIndexTotalNum());
	}

	for (int j=0; j<2; j++)
	{
		printf ("\nObjects modification #%d...\n", j+1);
		for (i=0; i<(int)id_arr.GetSize(); i++)
		{
			test = id_arr[i];

			char SSS [256];
			MakeRandomStr ("  qweeertyuuiiiioooplkjhgfddssaaazxcvbbnmnm", 10, SSS);

			test.m_Name				= SSS;
			test.m_Number			= rand()%1000;
			test.m_Age				= 27+rand()%3;
			test.m_Text				+= "123";
			test.m_Text				+= "000";
			test.m_Text[1]			=	"32";
			test.m_Text[1]			+=	"1";
			test.m_References		+= i*10;
			test.m_Flag				=	(test.m_Age%(byte)2)==0;

			PRINT_PERCENT (i, NNN);
		}
	}

	test.SetIndex_Number_Name_Flag_Age();
	printf ("\n\nTotal number: %d, unique number: %d\n", test.GetTotalNum(), test.GetIndexUniqueNum());

	printf ("\nObjects deleting...\n");
	for (i=0; i<(int)id_arr.GetSize()/2; i++)
	{
		test.Delete(id_arr[i]);
		PRINT_PERCENT (i, NNN/2);
	}

	printf ("\n\nAll class objects deleting...\n");
	test.DeleteClassObjects();

	printf ("\n\nTest complete.\n");
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Проверка функции GetClassIdList															[]
//                                                                            []
//RVK:>>>23
void Test23 ()
{
	int					NNN = 100;
	OC_Test0				test;
	CPtr<identifier>	id_arr;

	printf ("\nObjects creation...\n");
	for (i=0; i<NNN; i++)
	{
		test.New();
		id_arr.Add(test.GetObjectID());
		PRINT_PERCENT (i, NNN);
	}

	printf ("\nObjects modification...\n");
	for (i=0; i<(int)id_arr.GetSize(); i++)
	{
		test				= id_arr[i];
		test.m_Age		= i%10;
		PRINT_PERCENT (i, NNN);
	}

	printf ("\nObjects testing...\n");
	CPtr <identifier> id_list;
	key_arr ka;
		ka += (byte)4;
	test.GetClassIdList(id_list, &ka);
	for (CPtr<identifier>::Iterator id = id_list.begin(); id!=id_list.end(); id++)
	{
		test = (identifier) id;
		printf ("  %d\n", (int) test.m_Age);
	}

}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Проверка индексации float																	[]
//                                                                            []
//RVK:>>>24
void Test24 ()
{
	int						NNN = 10;
	OC_Test_int_float		test;
	CPtr<identifier>		id_arr;	

	printf ("\nObjects creation...\n");
	for (i=0; i<NNN; i++)
	{
		test.New();
		id_arr.Add(test.GetObjectID());
		PRINT_PERCENT (i, NNN);
	}

	puts("");
	string dbg;
	test.DebugPrint(dbg);
	dbg.Print ();


	printf ("\nObjects modification...\n");
	for (i=0; i<(int)id_arr.GetSize(); i++)
	{
		test				= id_arr[i];
		float fN1		= (float) (rand()%1000);
		float fN2		= (float) (1 + rand()%100);
		float fSG		= (rand ()>rand ())?(float)-1:(float)1;

		int	iN1		= (rand ()%100);
		int	iSG		= (rand ()>rand ())?-1:1;

		test.m_fval		= fSG*(fN1/fN2);
		test.m_ival		= iSG*iN1;

		PRINT_PERCENT (i, NNN);
	}

	printf ("\n\n\nInteger index:\n");
	test.SetIndex_ival ();
	for (test.GoFirst(); test; test++)
	{
		printf ("  %+d\n", (int)test.m_ival);
	}

	printf ("\n\n\nFloat index:\n");
	test.SetIndex_fval ();
	for (test.GoFirst(); test; test++)
	{
		printf ("  %+.1f\n", (float) test.m_fval);
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` CMemTest																						[]
//                                                                            []
struct CMemTest
{
	CMemTest () {printf ("+");}
	~CMemTest () {printf ("-");}
};
int OD_count=0;
//______________________________________________________________________________
//                                                                            []
//` Проверка утечки памяти и скорости работы												[]
//                                                                            []
//RVK:>>>25
void Test25 ()
{
	printf ("\n\nTest started.\n");
	#ifdef WIN32
		//getch  ();
	#endif
	{

	typedef OC_Test0	OC_Test;

	int					NNN = 1000*1000;
	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;
	OC_Test				test;
	
	CPtr<identifier>	id_arr	= NNN+1;
	id_arr	= NNN;

	printf ("\n\n\nObjects creation [%s]...\n", className [test.GetClassID()]);
	for (i=0; i<NNN; i++)
	{
		test.New();
		id_arr[i] = test.GetObjectID();
		PRINT_PERCENT (i, NNN);
	}

	printf ("\n\n\nObjects modification...\n");
	int nTimes = 1;
	for (j=0; j<nTimes; j++)
	{
		//printf ("\r                                                                                   \r");
		//printf ("\r >> Reloading all base...");
		clock_t ini_clock = clock();
		//test.ReloadAllBase();
		clock_t end_clock = clock();
		double duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
		printf ("\r                                                                                   \r");
		printf (" %.2f sec", duration);
		for (i=0; i<(int)id_arr.GetSize(); i++)
		{
			test = id_arr[i];//rand()%((int)id_arr.GetSize())];

		//for (j=0; j<nTimes; j++)
			{
				static char SSS [256];
				MakeRandomStr ("  qweeertyuuiiiioooplkjhgfddssaaazxcvbbnmnm", 10, SSS);
				//MakeRandomStr ("AA", 10, SSS, true);

				test.m_Name				= SSS;
				test.m_Number			= rand()%3;
				test.m_Age				= 27+rand()%3;
				if (nTimes*NNN<=100000)
				{
					test.m_Text				+= "123";
					test.m_Text				+= "000";
					test.m_Text[1]			=	"32";
					test.m_Text[1]			+=	"1";
					test.m_References		+= i*10;
				}
				test.m_Flag				=	(test.m_Age%(byte)2)==0;
			}

			//PRINT_PERCENT (i*nTimes, NNN*nTimes);
			PRINT_PERCENT (j*NNN+i, NNN*nTimes);
		}
	}


	printf ("\n\n\n\nObjects verification...\n");
	test.SetIndex_Number_Name_Flag_Age();
	for (i=0, test.GoFirst(); test; test++, i++)
	{
		//SERVER_DEBUG_ASSERT (test.m_Text[1]==string("321"), "");
		if (i%NN==0)  printf ("%7d:   [Number=%d  Name=\"%s\"  Flag=%s  Age=%d] \r\n", i, (int)test.m_Number, (const char*) test.m_Name, test.m_Flag? "true ": "false", (int)test.m_Age);		
	}

	printf ("\n\n\nObjects deleting -- half of all...\n");
	for (i=0; i<(int)(id_arr.GetSize()/2); i++)
	{
		test.Delete(id_arr[i]);
		PRINT_PERCENT (i, (int)(id_arr.GetSize()/2));
	}

	printf ("\n\n\nObjects deleting -- the rest...\n");
	clock_t ini_clock = clock();
	test.DeleteClassObjects  ();
	clock_t end_clock = clock();
	double duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf (" %.2f sec\n", duration);
	

	printf ("\n\n\n");
	printf ("OD_count   = %d\n", OD_count);
	printf ("totalRef   = %d\n", CAbstractObjectInMemory::totalRef);
	printf ("totalCount = %d\n", CAbstractObjectInMemory::totalCount);

	id_arr = (int) 0;
	
	}printf ("\n\nTest complete.\n");
	#ifdef WIN32
	getch  ();
	#endif
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка новых ключей 																		[]
//                                                                            []
//RVK:>>>26
void Test26 ()
{
	key_arr ka;
	ka += (int)				1000;
	ka += (float)			3.14;
	ka += (bool)			false;
	ka += (byte)			29;
	ka += (const char *)	"This is a string";
	ka += (identifier)	1000000001;
	ka.DebugPrint();
	printf ("\nObjID = %d\n\n", ka.GetObjID());

	ka.SetKeyData (0, (int)44);
	ka.SetKeyData (1, (float)2.7);
	ka.SetKeyData (2, (bool)true);
	ka.SetKeyData (3, (byte)44);
	ka.SetKeyData (4, "!!");
	ka.SetKeyData (5, (identifier) 123456789);
	ka += (const char *)	"...";
	ka += (identifier)	11111101;
	ka.DebugPrint();
	printf ("\nObjID = %d\n", ka.GetObjID());
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Проверка скорости работы и оптимального удаления объектов						[]
//                                                                            []
//RVK:>>>27
void Test27 ()
{
	int		NNN = 100000; //4*1000*1000;

	clock_t	ini_clock;
	clock_t	end_clock;
	double	duration;

	typedef OC_Test_int OC_Test;

	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;
	OC_Test	test;
	CPtr<identifier> id_arr = NNN/10;


	printf ("\n\n\nObjects creation [%s]...\n", className [test.GetClassID()]);
	for (i=0; i<NNN; i++)
	{
		test.New();
		if (i<id_arr.GetSize ())
			id_arr[i] = test.GetObjectID();

		int pc = PRINT_PERCENT (i, NNN);
		if (pc>0 && pc%10==0)
			puts ("");
	}


	printf ("\n\n\n\nObjects modification...\n");
	for (i=0, test.GoFirst(); i<NNN; test.GoFirst(), i++)
	{
		test.m_ival = i+1;
		int pc = PRINT_PERCENT (i, NNN);
		if (pc>0 && pc%10==0)
			puts ("");
	}



	printf ("\n\n\nCalculation unique number...");
	ini_clock = clock();
	{
		printf ("\nUnique number = %d", test.GetIndexUniqueNum());
	}
	end_clock = clock();
	duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n %.2f sec\n", duration);



	printf ("\n\n\nFlushing file system...");
	ini_clock = clock();
	{
		test.FlushFileSystem ();
	}
	end_clock = clock();
	duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n %.2f sec\n", duration);




	printf ("\n\n\nSaving all base...");
	ini_clock = clock();
	{
		test.SaveAllBase();
	}
	end_clock = clock();
	duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n %.2f sec\n", duration);



	printf ("\n\n\nReloading all base...");
	ini_clock = clock();
	{
		test.ReloadAllBase();
	}
	end_clock = clock();
	duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n %.2f sec\n", duration);



	printf ("\n\n\n\nObjects verification...\n");
	for (i=0, test.GoFirst(); test; test++, i++)
	{
		SERVER_DEBUG_ASSERT (test.m_ival == i+1, "Не прошла проверка значения");
		if (i%NN==0)  printf ("%7d:   [ival = %8d] \n", i, (int)test.m_ival);
	}



	printf ("\n\n\nObjects deleting -- 10%% of all...\n");
	for (i=0; i<id_arr.GetSize(); i++)
	{
		test.Delete(id_arr[i]);

		int pc = PRINT_PERCENT (i, id_arr.GetSize());
		if (pc>0 && pc%10==0)
			puts ("");
	}



	printf ("\n\nObjects deleting -- the rest...");
	ini_clock = clock();
	{
		test.DeleteClassObjects  ();
	}
	end_clock = clock();
	duration = (double)(end_clock - ini_clock) / CLOCKS_PER_SEC;
	printf ("\n %.2f sec\n", duration);

	SERVER_DEBUG_ASSERT (theObjDriver.GetIndexPtr (test.classID, 0)->AVTree.Count()==0, "Не все объекты удалались");
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Проверка оператора копирования данных													[]
//                                                                            []
//RVK:>>>28
void Test28 ()
{
	int		NNN = 20;

	typedef OC_Test0 OC_Test;


	int NN =	NNN <=      10?      1:
				NNN <=     100?     10:
				NNN <=    1000?    100:
				NNN <=   10000?   1000:
				NNN <=  100000?  10000:
				NNN <= 1000000? 100000:	1000000;
	OC_Test	test;
	CPtr<identifier> id_arr = NNN;


	printf ("\n\n\nObjects creation [%s]...\n", className [test.GetClassID()]);
	for (i=0; i<NNN; i++)
	{
		test.New();
		id_arr[i] = test.GetObjectID();
	}


	printf ("\nObjects modification #1...\n");
	for (i=0; i<id_arr.GetSize(); i++)
	{
		test = id_arr[i];

		char SSS [256];
		MakeRandomStr ("  qweeertyuuiiiioooplkjhgfddssaaazxcvbbnmnm", 10, SSS);

		test.m_Name				= SSS;
		test.m_Number			= rand()%3;
		test.m_Age				= 27+rand()%3;
		test.m_Text				+= "123";
		test.m_Text				+= "321";
		test.m_References		+= i*10;
		test.m_Flag	 = (test.m_Age%(byte)2)==0;
	}


	printf ("\n\n\n\n\n\nObjects verification #1...\n");
	for (i=0, test.GoFirst(); test; test++, i++)
	{
		SERVER_DEBUG_ASSERT (test.m_Text[1] == string ("321"), "Не прошла проверка значения");
		test.DebugPrint ();
	}


	printf ("\n\n\n\n\n\nObjects modification #2...\n");
	OC_Test tt;
	tt = id_arr[0];
	tt.m_Name = "tt";
	tt.DebugPrint ();
	for (i=0; i<id_arr.GetSize(); i++)
	{
		test = id_arr[i];
		int nText = tt.m_Text.Size();
		test << tt;
		test.DebugPrint ();
	}

	printf ("\n\n\n\n\n\nObjects verification #2...\n");
	for (i=0, test.GoFirst(); test; test++, i++)
	{
		SERVER_DEBUG_ASSERT ((test.m_Text[1]==tt.m_Text[1]) && (test.m_References[0] == tt.m_References[0]), "Не прошла проверка значения");
		test.DebugPrint ();
	}
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Проверка мастер-класса                                                    []
//                                                                            []
//RVK:>>>29
void Test29 ()
{
   OC_Master oc_master;

   OC_Slave oc_slave;

   oc_master.m_SlaveObjectID += oc_slave.New();
   oc_slave.m_Number = oc_master.m_SlaveObjectID.GetSize()-1;

   for (int i=0; i<oc_master.m_SlaveObjectID.GetSize(); i++)
   {
      oc_slave =  oc_master.m_SlaveObjectID[i];
      printf ("id=%3d Slave.Number=%d\n", oc_slave.GetObjectID(), (int)oc_slave.m_Number);
   }
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Проверка статических функций OC_Exist													[]
//                                                                            []
//RVK:>>>30
void Test30 ()
{
   OC_Master oc_master;

	//oc_master.Delete();

	printf ("%4d %s\n\n", oc_master.GetClassID(), oc_master.Exist(oc_master.GetObjectID())? "+": "-");

	printf ("%4d %s\n", oc_master.GetClassID(), OC_Exist (oc_master.GetClassID(), oc_master.GetObjectID())? "+": "-");
	printf ("%4d %s\n", oc_master.GetClassID(), OC_Exist (oc_master.GetClassID()+1, oc_master.GetObjectID())? "+": "-");
	printf ("%4d %s\n", oc_master.GetClassID(), OC_Exist (oc_master.GetClassID(), oc_master.GetObjectID()+1)? "+": "-");
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Проверка работы событий																	[]
//                                                                            []
//RVK:>>>31
void Test31 ()
{
	RAISE_EVENT (EMM_Application, EMT_Message,		NA, NA,	"Hellow Application!\n");
	RAISE_EVENT (EMM_System,		EMT_Message,		NA, NA,	"Hellow System!\n");
	RAISE_EVENT (EMM_System,		EMT_Error,			NA, NA,	"System ERROR!\n");
	RAISE_EVENT (EMM_ObjBase,		EMT_Object_New,	NA, NA,	"New Object NA\n");
	RAISE_EVENT (EMM_ObjBase,		EMT_Object_New,	OBJ_CLASS_ID_Test0, 1,	"New Object 1\n");
	RAISE_EVENT (EMM_ObjBase,		EMT_Object_Change,OBJ_CLASS_ID_Test0, NA,	"Object Changed!\n");

	if (RAISE_EVENT_AHEAD (EMM_Application, EMT_Message,	1, NA,	"Can I do it (1)?\n"))
		printf ("   I can do it! (1)\n");
	else
		printf ("   No, I can't\n");

	if (RAISE_EVENT_AHEAD (EMM_Application, EMT_Message,	NA, NA,	"Can I do it (NA)?\n"))
		printf ("   I can do it! (NA)\n");
	else
		printf ("   No, I can't\n");
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка CPtr::Sort																			[]
//                                                                            []
void Test32 ()
{
	string_arr	    arr;
	int i		=        0;
	int NN	=	   1000;
	int NNN	=		 500;

	for (i=0; i<NN; i++)
	{
		char SSS [256];
		MakeRandomStr ("10", 10, SSS);
		arr += SSS;
	}

	printf ("Sort %d...\n", NN);

	bool bAscend = false;
	clock_t beg_clock = clock ();
	arr.Sort (bAscend);
	clock_t end_clock = clock ();
	double duration	= (double)(end_clock - beg_clock) / CLOCKS_PER_SEC;
	printf ("%4.2f sec [%d/sec] \n", duration, (int)(1/duration));

	printf ("Check...\n");

	for (i=0; i<NNN; i++)
	{
		for (j=0; j<NN; j++)
		{
			arr.Find (arr[j], true);
		}
		PRINT_PERCENT (i, NNN);
	}

	for (i=0; i<NN; i++)
	{
		if (i>0)
		{
			if (bAscend==true)	SERVER_DEBUG_ASSERT (arr[i-1]<=arr[i], "Ошибка сортировки!");
			if (bAscend==false)	SERVER_DEBUG_ASSERT (arr[i-1]>=arr[i], "Ошибка сортировки!");
		}
		//printf ("Find %s -> %d\n", arr[i].c_str(), arr.Find (arr[i], true));
		SERVER_DEBUG_ASSERT (arr[arr.Find (arr[i], true)]==arr[i], "Ошибка поиска!");
	}
	printf ("\nOK.\n");
}
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
