//______________________________________________________________________________
//                                                                            []
//` Скорость загрузки зрителей																[]                 
//                                                                            []
#if 0  //{ RomanVK
void Test51_old ()
{
	int VIEWERS_NUM		=	10*1000;
	int CONCEPTS_NUM		=	1000;
	int BNR_CONCEPTS_NUM	=	200;
	int ANK_CONCEPTS_NUM	=	150;

	int SITE_NUM			=	1000;			// !!!
	int BANNER_NUM			=	2*SITE_NUM; // !!!

	int i;

// Создание зрителей
	OC_Viewer oc_viewer;
	//oc_viewer.DeleteClassObjects();
	VIEWERS_NUM = 0;

	for (i=0; i<VIEWERS_NUM; i++)
	{
		PRINT_PERCENT (i, VIEWERS_NUM);
		oc_viewer.New();
		oc_viewer.m_IPAddressHash	= rand()%(VIEWERS_NUM/2);

		oc_viewer.m_Anonymous		= rand()%100==0? true: false;
		oc_viewer.m_UserAgent		= "oc_viewer.m_UserAgent";
		oc_viewer.m_IPAddress		= "oc_viewer.m_IPAddress";

		oc_viewer.m_CRA_Site			= CPtr<int>(rand()%CONCEPTS_NUM);
		oc_viewer.m_CRN_Site			<< oc_viewer.m_CRA_Site;

		oc_viewer.m_CRA_Click		= CPtr<int>(rand()%BNR_CONCEPTS_NUM);
		oc_viewer.m_CRN_Click		<< oc_viewer.m_CRA_Click;

		int SITE_NUM_RND = rand()%SITE_NUM;
		oc_viewer.m_Site				= CPtr<identifier>(SITE_NUM_RND);
		oc_viewer.m_Site_LastHit	= CPtr<int>(SITE_NUM_RND);
		oc_viewer.m_Site_Hits		= CPtr<int>(SITE_NUM_RND);
		oc_viewer.m_Site_LastHost	= CPtr<int>(SITE_NUM_RND);
		oc_viewer.m_Site_Hosts		= CPtr<int>(SITE_NUM_RND);
		oc_viewer.m_Site_Votings	= CPtr<byte>(SITE_NUM_RND);
		oc_viewer.m_Site_VoteDayNo	= CPtr<byte>(SITE_NUM_RND);
					
		oc_viewer.m_CRA_Inquiry		= CPtr<int>(rand()%ANK_CONCEPTS_NUM);
		oc_viewer.m_CRN_Inquiry		<< oc_viewer.m_CRA_Inquiry;

		int BANNER_NUM_RND = rand()%BANNER_NUM;
		oc_viewer.m_Banner					= CPtr<identifier>(BANNER_NUM_RND);
		oc_viewer.m_Banner_LastViewed		= CPtr<int>(BANNER_NUM_RND);
		oc_viewer.m_Banner_ShowClick		= CPtr<int>(BANNER_NUM_RND);
	}

	printf ("\n");

	identifier_arr ALL_VIEWERS_ID;
	oc_viewer.GetClassIdList (ALL_VIEWERS_ID);
	VIEWERS_NUM = 1000;

	for (i=0; i<VIEWERS_NUM; i++)
	{
		PRINT_PERCENT (i, VIEWERS_NUM);
		int ind = rand()% ALL_VIEWERS_ID.Size();
		oc_viewer.Open (ALL_VIEWERS_ID[ind]);
		oc_viewer.m_Group	+= 1;
	}
}
#endif //}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Скорость загрузки зрителей																[]                 
//                                                                            []
#if 0  //{ RomanVK
void Test51_old_old ()
{
	int NN = 0;//1000*1000;
	int i;

// Создание
	OC_Test_Load oc_test_load;

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i, NN);
		oc_test_load.New();
		oc_test_load.m_Field = rand ()%NN;
	}

	printf ("\n");

	identifier_arr ALL_ID;
	oc_test_load.GetClassIdList (ALL_ID);
	NN = 10000;

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i, NN);
		int ind = rand()% ALL_ID.Size();
		oc_test_load.Open (ALL_ID[ind]);
		oc_test_load.m_Field += 1;
	}
}
#endif //}
//____________________________________________________________________________[]



void Test51 ()
{
#if 0  //{ RomanVK
	int NN	= 100;
	string	Str;
	for (int i = 0; i < NN; i++) 
	{
		for (int j = 0; j < 365; j++) 
		{
			Str.Format("%d,%d,%d,%d,%%d", j,j,j,j,j);
			for (int k = 0; k < 24; k++) 
			{
				Str.Format("%d", j);
			}
		}

		PRINT_PERCENT (i, NN);
	}
	return;
#endif //}

#if 0  //{ RomanVK
	int N		= 365*24;
	int i,j,k;

	int_arr arr (31);
	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i, NN);
		int sum=0;

		for (k=0; k<30; k++)
		{
			for (j=0; j<N; j++)
			{
				sum += arr[k];
			}
		}
	}
#endif //}
}
