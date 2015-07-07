/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'bcc'                                       []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            MemoryManager.cpp                                         []
[] Date:            12.11.1999                                                []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Управление распределением памяти                          []
[]-Last Modified:   12.11.1999 [ 19:53:02 ] by Roman V. Koshelev              []                          
[]____________________________________________________________________________[]
*/

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


#define IGNORE_WRONG_CALLS
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` МЕНЕДЖЕР ПАМЯТИ (АЛЛОКАТОР)                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/


//----------------------------------------------------------------------------[] 
#define PAGE_MANAGER_NUM	64
#define OUTSIDE_PAGE_NUM	(PAGE_MANAGER_NUM+1)
#define NON_PAGED_PTR		0xFF
#ifndef NULL
	#define NULL	0L
#endif
#define PAGE_ITEMS_NUM		1024
typedef unsigned char byte;
typedef void* pvoid;
typedef byte* pbyte;

//----------------------------------------------------------------------------[] 


class MemoryManager;
//______________________________________________________________________________
//                                                                            []
//` PageManager                                                               []           
//                                                                            []
class PageManager
{
	size_t	m_PageSize;
	int		m_Number;
	pvoid  *	m_PageArr;
	int		m_PageNum;

	public: PageManager ()
	{
		m_PageSize	=  0;
		m_Number		=  0;
		m_PageArr	=  NULL;
		m_PageNum	=  0;
	}

	//----------------------------------------------------------------------------[] 
	void GetFreePagePos (int iPage, int iPos)
	{
		for (int i=0; i<m_PageNum; i++)
		{
			pbyte pFAT = (pbyte) m_PageArr[i];
			for (int j=0; j<PAGE_ITEMS_NUM; j++)
			{
				if (pFAT[j]==0)
				{
					iPage = i;
					iPos  = j;
					return;
				}
			}
		}

		pvoid * pTMP = (pvoid *) malloc ((m_PageNum+1)*sizeof (pvoid));
		memcpy (pTMP, m_PageArr, m_PageNum*sizeof (pvoid));
		free (m_PageArr);
		m_PageArr = pTMP;
		int PageSize = PAGE_ITEMS_NUM + PAGE_ITEMS_NUM/4 + PAGE_ITEMS_NUM + PAGE_ITEMS_NUM*m_PageSize;
		m_PageArr[m_PageNum] = malloc (PageSize);
		memset (m_PageArr[m_PageNum], 0, PageSize);

		iPage = m_PageNum;
		iPos  = 0;
		m_PageNum++;
	}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	void * Alloc (size_t nSize)
	{
		int iPage	= -1; 
		int iPos		= -1; 

		GetFreePagePos (iPage, iPos);

		void * pRes = malloc (nSize);
		printf ("[%2d:%4d]    Alloc (%d)\n", m_Number, m_PageSize, nSize);
		return pRes;
	}
	//----------------------------------------------------------------------------[] 

	
	//----------------------------------------------------------------------------[] 
	void Free (void * pUserData)
	{
		free (pUserData);
		printf ("[%2d:%4d]    Free (0x%p)\n", m_Number, m_PageSize, pUserData);
	}
	//----------------------------------------------------------------------------[] 



	public: void Init (int nNumber, size_t nPageSize)
	{
		m_PageSize	= nPageSize;
		m_Number		= nNumber;
	}
	friend MemoryManager;
};
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//` MemoryManager                                                             []             
//                                                                            []
class MemoryManager
{
protected: 
	PageManager m_PageManager		[PAGE_MANAGER_NUM];
	int			m_PageManagerNum;
	size_t		m_PageSize			[PAGE_MANAGER_NUM];
	static		MemoryManager*		m_this;

	//----------------------------------------------------------------------------[] 
	protected: void Init ()
	{
		int i;
		static size_t PAGE_SIZE[] = {	0,		1,		2,		3,		4,		5,		6,		7,/*|*/ 8,		9,		10,	12,	14,	16,	18,	20,/*|*/22,	24,	26,	28,	30,	32,	36,	40,/*|*/44,	48,	52,	58,	64,	70,	80,	90,/*|*/100,	120,	140,	160,	180,	200,	240,	280,	/*|*/320,	400,	460,	520,	600,	700,	800,	900,/*|*/1000,	1500,	2000,	2500,	3000,	3500,	4000,	4500,/*|*/5000,	5500,	6000,	6500,	7000,	8000,	9000,	10000};
		m_PageManagerNum = PAGE_MANAGER_NUM;
		for (i=0; i<m_PageManagerNum; i++)
		{
			m_PageSize[i]			=		PAGE_SIZE[i];
			m_PageManager[i].Init (i,	PAGE_SIZE[i]);
		}
		m_this = this;
	}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	public: void * operator new		(size_t nSize)		{return malloc (nSize);}
	public: void	operator delete	(void * pData)		{free (pData);}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	public: MemoryManager ()
	{
		Init();
	}
	//----------------------------------------------------------------------------[] 
	public: ~MemoryManager ()
	{
		m_this = NULL;
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	protected: int FindPageBySize (size_t nSize)
	{
		for (int i=0; i<m_PageManagerNum; i++)
		{
			if (nSize<=m_PageManager[i].m_PageSize)
			{
				return i;
			}
		}
		return OUTSIDE_PAGE_NUM;
	}
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	protected: int FindPageByPtr (void * pUserData)
	{
		(void) pUserData;
		return OUTSIDE_PAGE_NUM; // !!!
	}
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	public: static void * Alloc (size_t nSize)
	{
		if (m_this==NULL)
		{
#ifndef IGNORE_WRONG_CALLS
			printf ("  MemoryManager::Alloc(%d) -- memory manager not initialized\n", nSize);
#endif
			return malloc (nSize);
		}
		int nPage = m_this->FindPageBySize (nSize);
	// Разместить не на странице (большие данные)
		if (nPage==OUTSIDE_PAGE_NUM)
		{
			unsigned char * pData = (unsigned char *) malloc (nSize+1);
			*pData = NON_PAGED_PTR;
			return pData+1;
		}
	// Разместить на странице
		else
		{
			return m_this->m_PageManager[nPage].Alloc (nSize);
		}
		return NULL;
	}
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	public: static void Free (void * pUserData)
	{
		if (m_this==NULL)
		{
#ifndef IGNORE_WRONG_CALLS
			printf ("  MemoryManager::Free(0x%p) -- memory manager not initialized\n", pUserData);
#endif
			return;
		}
		int nPage = m_this->FindPageByPtr (pUserData);
	// Указатель не на странице (большие данные)
		if (nPage==OUTSIDE_PAGE_NUM) 
		{
			unsigned char * pData = ((unsigned char *) pUserData) - 1;
			if (*pData==NON_PAGED_PTR)
			{
				free (pData);
			}
			else
			{
#ifndef IGNORE_WRONG_CALLS
				printf ("  MemoryManager::Free(0x%p) -- wrong non-paged pointer\n", pUserData);
#endif
			}
		}
	// Указатель на странице
		else 
		{
			m_this->m_PageManager[nPage].Free (pUserData);
		}
	}
	//----------------------------------------------------------------------------[] 
};
//____________________________________________________________________________[]













//----------------------------------------------------------------------------[] 
MemoryManager * MemoryManager::m_this=NULL;
MemoryManager * pMemoryManager=NULL;
#define theMemoryManager (*pMemoryManager)

//void  *	operator new		(unsigned int	nSize)	{return	theMemoryManager.Alloc	(nSize);}
//void  *	operator new[]		(unsigned int	nSize)	{return	theMemoryManager.Alloc	(nSize);}
//void 		operator delete	(void *			pData)	{			theMemoryManager.Free	(pData);}
//void 		operator delete[]	(void *			pData)	{			theMemoryManager.Free	(pData);}
//----------------------------------------------------------------------------[] 









//----------------------------------------------------------------------------[] 
struct TestStruct
{
	int int_dummy;
};
//----------------------------------------------------------------------------[] 












int PRINT_PERCENT (int, int);

//______________________________________________________________________________
//                                                                            []
// Тестирование MemoryManager																	[]
//                                                                            []
void Test39 ()
{
	//pMemoryManager = new MemoryManager;


	TestStruct * pTS1		= new TestStruct;
	TestStruct * pTS2		= new TestStruct;
	TestStruct * pTS_arr = new TestStruct [10];


	delete pTS1;
	delete pTS2;
	delete [] pTS_arr;


	//delete pMemoryManager;
	pMemoryManager = NULL;
}
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 
// Тестирование смещения
void Test39_1()
{
	int NN = 1000000;
	int * pint1 = new int [NN+10];
	int * pint2 = (int*)(pbyte(pint1)+1);

	printf ("pint1=0x%p\npint2=0x%p\n%d\n\n", pint1, pint2, (int)pint2-(int)pint1);

	int N = 260;
	for (int i=0; i<N; i++)
	{
		PRINT_PERCENT (i, N);
		for (int j=0; j<NN; j++)
		{
			*(((int*)(pbyte(pint1)+1))+j) = j+i;
		}		
	}
}
//----------------------------------------------------------------------------[] 

#endif

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
