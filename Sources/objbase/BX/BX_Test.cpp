/*
____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'BX'													[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  Test.cpp																[]
[] Date: 			  01.06.99																[]
[] Author:			  Alex Vershinin														[]
[] Description:	  Тесты системы 														[]
[] Last Modified:																				[]                                             
[]_________________________________________________________________________[]
*/


#ifdef WIN32
#define USES_CACHE_h

#define USES_OC_TimeStats
#define USES_OC_Site
#define USES_OC_ShowEvent
#define USES_OC_Viewer
#define USES_OC_IPRecord

#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_Counter
#define USES_BX_IPRecord
#define USES_BX_Admin
#define USES_BX_VBN
#define USES_BX_Site
#define USES_BX_User

#include "BX.h"
//----------------------------------------------------------------------------[] 
void	CreateTestObjects (void);
void	GenerateEvents		(void);
//----------------------------------------------------------------------------[]
#define	SITE_NUM			  	  10			// Количество сайтов в базе.
#define	VIEWER_NUM		 	 500			// Количество зрителей в базе.
#define	IPRECORD_NUM		 200			// Количество IP-сетей в базе (Max 256^2).

// Параметры генераторы событий:
#define	EVENT_NUM			 100000		// Количество событий, которые требуется сгенерировать.
#define	EVENT_PERIOD						// 


// [00:39::45] <Roman> 100,000 зрителей, 20,000 IP сетей, 1000 сайтов
// [00:40::33] <Roman> 1,000,0000 хитов
//----------------------------------------------------------------------------[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` RunTest                                                                   []
[]                                                                            []
[]____________________________________________________________________________*/
void RunTest (void)
{
	srand(time(0));
	clock_t ini_clock = clock();

//----------------------------------------------------------------------------[] 
	
	CreateTestObjects ();
	GenerateEvents ();


//----------------------------------------------------------------------------[] 
	puts("\n-------------------------------------------------------------------------");
	printf("\n\nTotal time: %.3f sec.\n\n", double(clock() - ini_clock) / CLOCKS_PER_SEC);

	return;
}
//____________________________________________________________________________[]





static	identifier_arr	SiteIDs;
static	identifier_arr	ViewerIDs;
static	bool_arr			CookieSupported;
static	string_arr		ViewerIPs;

/*______________________________________________________________________________
[]                                                                            []
[]` CreateTestObjects                                                         []
[]                                                                            */
void CreateTestObjects (void)
{
// Объекты уже созданы ?
	if (oc_reg.m_Viewers.Size() > 0)
	{
		return;
	}

	string					AdminPass;
	GetAdminPassword (AdminPass);
	unsigned long			i;

// Создание VBN
	BX_VBN_Args	vbn_arg;
	printf("Creating vbn ...\n");
	vbn_arg.AdminPassword		= AdminPass;
	vbn_arg.objID					= NA;												
	vbn_arg.Name					= "Test VBN";	
	vbn_arg.Password				= "vbn";											
	vbn_arg.IsModerated			= false;								
	vbn_arg.DefaultLanguage		= oc_reg.m_Language[0];			
	vbn_arg.DefaultTZOffset		= SERVER_TIME_ZONE_OFFSET;		
	BX_ASSERT(BX_VBN_New(vbn_arg));	

// Создание юзера-владельца всех сайтов
	BX_User_Args	user_arg;
	printf("Creating user ...\n");
	user_arg.Login					= "Test User";							
	user_arg.Password				= "testuser";							
	user_arg.PasswordConfirm	= "testuser";							
	user_arg.FullName				= "Mr Test User";			
	user_arg.Email					= "test@user.msk.ru";			
	user_arg.VBN					= vbn_arg.objID;					
	BX_ASSERT(BX_User_New(user_arg));	

// Создание сайтов
	BX_Site_Args	site_arg;
	printf("Creating sites ...\n");
	
	for (i = 0; i < SITE_NUM; i++)
	{
		PRINT_PERCENT (i, SITE_NUM);
		site_arg.Profile				= NA;											
		site_arg.objID					= NA;											
		site_arg.OwnerID				= user_arg.objID;							
		site_arg.objPassword			= "testuser";									
		site_arg.Name.Format ("Test site #%06lu", i+1);
		site_arg.URL.Format	("http://www.test%06lu.com", i+1);
		BX_ASSERT(BX_Site_New(site_arg));
		SiteIDs.Add (site_arg.objID);
	}


// Создание IP-сетей
	BX_IPRecord_Args		iprecord_arg;
	printf("\nCreating ip records ...\n");

	for (i = 0; i < IPRECORD_NUM; i++)
	{
		PRINT_PERCENT (i, IPRECORD_NUM);
		iprecord_arg.objID			= NA;
		iprecord_arg.First.Format ("0.0.%lu.%lu", i/256, i%256);
		iprecord_arg.Last				= iprecord_arg.First;
		iprecord_arg.AdminPassword = AdminPass;
		iprecord_arg.Checked			= false;
		BX_ASSERT(BX_IPRecord_New(iprecord_arg));										
	}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создание зрителей
// Для создания зрителя эмулируется заход на сайт.

	BX_Counter_Args	counter_arg;
	printf("\nCreating viewers ...\n");

const int				IPRECORD_PERCENT_20	= IPRECORD_NUM * 20 / 100; 
const int				IPRECORD_PERCENT_80	= IPRECORD_NUM * 80 / 100; 
const unsigned long	ANONYMOUS_STEP			= 10; // Каждый 10-тый -- анонимный.
		int				RandIP;

	for (i = 0; i < VIEWER_NUM; i++)
	{
		PRINT_PERCENT (i, VIEWER_NUM);
	// Инкремент времени
		time_0++;

		counter_arg.JustGetData			= false;
		counter_arg.SiteID				= site_arg.objID;
		counter_arg.CookieSupported	= i % ANONYMOUS_STEP != 0? true:false;
		counter_arg.ViewerID				= NA;
		
		if ((i * 80) / 100 < VIEWER_NUM)	// 80% зрителей
		// попадают  в 20 % IP-сетей
		{
			RandIP = rand () % IPRECORD_PERCENT_20;
		}
		else										// 20% зрителей
		// попадают  в 80 % IP-сетей
		{
			RandIP = IPRECORD_PERCENT_20 + rand () % IPRECORD_PERCENT_80;
		}
		
		counter_arg.ViewerIP.Format ("0.0.%d.%d", RandIP/256, RandIP%256);
		BX_ASSERT(BX_Counter_GetData(counter_arg));
		SERVER_DEBUG_ASSERT (counter_arg.ExitCode == 1, "Bad exit code.");

		ViewerIDs.Add (counter_arg.ViewerID);
		ViewerIPs.Add (counter_arg.ViewerIP);
		CookieSupported.Add (counter_arg.CookieSupported);
	}
//----------------------------------------------------------------------------[]
// Проверка зрителей
	OC_Viewer		oc_viewer;
	int				AnonymCount = 0;
	for (i = 0; i < (unsigned long)ViewerIDs.Size(); i++)
	{
		oc_viewer.Open (ViewerIDs[i]);
		if (oc_viewer.m_Anonymous)	AnonymCount++;
	}
	

//----------------------------------------------------------------------------[]
// Вывод итоговой информации:
	OC_Site		oc_site;
	OC_IPRecord	oc_iprecord;
	printf("\n\nSites    : %7d\nIPRecords: %7d\nViewers  : %7d (%d) (%d anonymous)\n\n", 
		(int)oc_site.GetTotalNum(),
		(int)oc_iprecord.GetTotalNum(),
		(int)oc_reg.m_Viewers.Size(),
		ViewerIDs.Size(),
		AnonymCount
		);
	return;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ONLINE_VIEWER                                                             []             
//                                                                            []
struct ONLINE_VIEWER
{
	identifier	m_ViewerID;
	string		m_ViewerIP;
	identifier	m_SiteID;
	bool			m_CookieSupported;
};
//____________________________________________________________________________[]



#define ONLINE_SIZE				10
#define OUT_PROB					20
#define SITE_CHANGE_PROB		10


/*______________________________________________________________________________
[]                                                                            []
[]` GenerateEvents                                                            []
[]                                                                            */
void GenerateEvents (void)
{
	unsigned long i, j;
	the_OBJ_CACHE.Clear ();				// Сброс кэша
//	the_OBJ_CACHE.OnTimer (time_0);	// Прочистка кэша -- вызывать постоянно

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Заполнение массива online-зрителей
	printf("\nFilling online array ...\n");
	CPtr<ONLINE_VIEWER>		OnlineArr(ONLINE_SIZE);

	for (i = 0; i < ONLINE_SIZE; i++)
	{
		int nRand = rand () % VIEWER_NUM;
		OnlineArr[i].m_ViewerID				= ViewerIDs			[nRand];
		OnlineArr[i].m_ViewerIP				= ViewerIPs			[nRand];
		OnlineArr[i].m_CookieSupported	= CookieSupported [nRand];
		OnlineArr[i].m_SiteID				= SiteIDs			[nRand%SITE_NUM];
	}
	
//----------------------------------------------------------------------------[]
// Симуляция событий
	printf("\nCalling Counter_GetData ...\n");
	unsigned long	TotalExecTime = 0;
	DWORD				TimeStart;

	for (i = 0; i < EVENT_NUM; i++, time_0++)
	{
		PRINT_PERCENT (i, EVENT_NUM);
		for (j = 0; j < (unsigned long)OnlineArr.Size(); j++)
		{
			BX_Counter_Args	counter_arg;
			counter_arg.JustGetData			= false;
			counter_arg.SiteID				= OnlineArr[j].m_SiteID;
			counter_arg.ViewerID				= OnlineArr[j].m_ViewerID;
			counter_arg.ViewerIP				= OnlineArr[j].m_ViewerIP;
			counter_arg.CookieSupported	= OnlineArr[j].m_CookieSupported;

			TimeStart = GetTickCount ();
			BX_ASSERT (BX_Counter_GetData (counter_arg));
			TotalExecTime += GetTickCount () - TimeStart;
		}
		

	// Обновление массива online-зрителей
		for (j = 0; j < ONLINE_SIZE; j++)
		{
			int nRandProb				= rand () % 100;

			if (nRandProb < OUT_PROB)
		// Зритель меняется на другого
			{
				unsigned long nRandLong			= ((unsigned long)(rand ())) * ((unsigned long)(rand ()));
				unsigned long nRandViewerIn	= nRandLong % VIEWER_NUM;

				OnlineArr[j].m_SiteID			= SiteIDs			[rand () % SITE_NUM];
				OnlineArr[j].m_ViewerID			= ViewerIDs			[nRandViewerIn];
				OnlineArr[j].m_ViewerIP			= ViewerIPs			[nRandViewerIn];
				OnlineArr[j].m_CookieSupported= CookieSupported	[nRandViewerIn];
			}
			else if (nRandProb < OUT_PROB + SITE_CHANGE_PROB)
		// Зритель меняет сайт
			{
				OnlineArr[j].m_SiteID			= SiteIDs			[rand () % SITE_NUM];
			}
			//else // Зритель остается на том же сайте
		}
	}

	printf("\n\nTotal time: %lu s (%lu msec per call).\n", TotalExecTime/1000, TotalExecTime/EVENT_NUM);
	


	return;
}
//____________________________________________________________________________[]






#endif // ifdef WIN32
/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/

