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
[]						  Защита от нехватки памяти не реализована						[]
[]____________________________________________________________________________[]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "MemoryManager.h"
#include "ServerDebug.h"

extern CServerDebug  * pServerDebug;
#define theServerDebug (*pServerDebug)

#define ALLERT_WRONG_CALLS

#ifdef WIN32
	#define bzero(a,b) ZeroMemory(a,b)
#endif

#ifdef WIN32
	#define snprintf _snprintf
	#define vsnprintf _vsnprintf
#endif
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
#ifdef USE_STACK_LEAK_TRACING
	extern	DEBUG_STACK_RECORD	DEBUG_STACK_RECORD_ARR [];
	extern	int						DEBUG_STACK_RECORD_NUM;
#endif
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
#ifdef WIN32  // WINDOWS
	#ifdef _DEBUG
		#define DBG_STOP_ASK																		\
		{																								\
			if (::MessageBox (NULL," Останавливаться для отладки?","STOP",			\
				MB_YESNO|MB_DEFBUTTON1|MB_ICONSTOP)==IDYES)								\
			{																							\
			__asm { int 3 };																		\
			}																							\
		}
		#define DBG_STOP {__asm { int 3 }}
	#else
		#define DBG_STOP {}
		#define DBG_STOP_ASK {}
	#endif
#else			// UNIX
	#define DBG_STOP {}
	#define DBG_STOP_ASK {}
#endif
//----------------------------------------------------------------------------[] 



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` МЕНЕДЖЕР ПАМЯТИ (АЛЛОКАТОР)                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/




//______________________________________________________________________________
//																										[]
#ifdef new
	#undef new
#endif

#ifdef USE_MAX_PAGED_BLOCK
	bool bUSE_MAX_PAGED_BLOCK = true;
#else
	bool bUSE_MAX_PAGED_BLOCK = false;
#endif

#define PAGE_MANAGER_NUM	63
#define OUTSIDE_PAGE_NUM	(PAGE_MANAGER_NUM+1)
#define NON_PAGED_PTR		0xFFFF
#ifndef NULL
	#define NULL	0L
#endif

#define USE_ONE_BIT_FOR_FAT

#define ALL_BITS_IN_INTEGER		0xFFFFFFFF
#define ALL_BITS_IN_BYTE			0xFF

#define PAGE_ITEMS_NUM				1024

#ifdef USE_ONE_BIT_FOR_FAT
	#define FAT_SIZE					128
#else
	#define FAT_SIZE					1024
#endif

#define DATA_SHIFT					(sizeof(int) + FAT_SIZE + WASTE_SIZE)
typedef unsigned char byte;
typedef void* pvoid;
typedef byte* pbyte;


#define GET_FAT_PTR(pPage)		(pPage + sizeof(int))
#define GET_DATA_PTR(pPage)	(pPage + DATA_SHIFT)

size_t BLOCK_SIZE[PAGE_MANAGER_NUM];

#define WASTE_SIZE		10
#define PAGE_SIZE(n)		(sizeof(int) + FAT_SIZE + WASTE_SIZE + (2 + BLOCK_SIZE[n])*PAGE_ITEMS_NUM)
#define PARAGRAF_SIZE   16
typedef bool BIT;
typedef bool bit;
typedef unsigned short ushort;


#ifdef USE_RVK_MEMORY_MANAGER
union	STP
{
	struct
	{
		unsigned int SizeType:  6;
		unsigned int Pos		: 10;
	} s;
	ushort n;
};
inline int GET_SIZE_TYPE_FROM_BLOCK_HEADER (ushort BH)
{
	STP stp;
	stp.n				= BH;
	return stp.s.SizeType;
}

inline int GET_BLOCK_NUM_FROM_BLOCK_HEADER (ushort BH)
{
	STP stp;
	stp.n	= BH;
	return stp.s.Pos;
}

inline ushort MAKE_BLOCK_HEADER (int SizeType, int Pos)
{
	STP stp;
	stp.s.Pos		= Pos;
	stp.s.SizeType = SizeType;

	return stp.n;
}
#endif
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
#define MM_PUTS(S)	{puts (S); /*SERVER_DEBUG_ERROR (S);*/}
//----------------------------------------------------------------------------[] 
#define MM_ERROR(str)											{char SSS[25600]; sprintf (SSS, str								); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
#define MM_ERROR_1(str, a1						)				{char SSS[25600]; sprintf (SSS, str, a1						); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
#define MM_ERROR_2(str, a1, a2				)				{char SSS[25600]; sprintf (SSS, str, a1, a2					); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
#define MM_ERROR_3(str, a1, a2, a3			)				{char SSS[25600]; sprintf (SSS, str, a1, a2, a3				); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
#define MM_ERROR_4(str, a1, a2, a3, a4		)				{char SSS[25600]; sprintf (SSS, str, a1, a2, a3, a4		); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
#define MM_ERROR_5(str, a1, a2, a3, a4, a5)				{char SSS[25600]; sprintf (SSS, str, a1, a2, a3, a4, a5	); puts(""); MM_PUTS (SSS); puts(""); /*DBG_STOP;*/}
//----------------------------------------------------------------------------[] 


#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif

//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING
struct MM_DEBUG_RECORD
{
#ifdef USE_STACK_LEAK_TRACING
	DEBUG_STACK_RECORD * m_StackArr;
	int					   m_StackNum;
#else
	char *	m_sFile;
	int		m_nLine;
#endif
	int		m_nCount;


// Использование стека для слежения за утечками памяти
#ifdef USE_STACK_LEAK_TRACING
	MM_DEBUG_RECORD ()
	{
		if (DEBUG_STACK_RECORD_NUM>0)
		{
			m_StackArr = (DEBUG_STACK_RECORD*) malloc ((DEBUG_STACK_RECORD_NUM+1) * sizeof (DEBUG_STACK_RECORD));
			m_StackNum = DEBUG_STACK_RECORD_NUM+1;
			if (m_StackArr==NULL)
			{
				MM_ERROR_1 ("MM_DEBUG_RECORD::MM_DEBUG_RECORD -- Can't alloc memory for m_StackArr. Size = %d", (DEBUG_STACK_RECORD_NUM+1) * sizeof (DEBUG_STACK_RECORD));
			}

			memcpy (m_StackArr, DEBUG_STACK_RECORD_ARR, (DEBUG_STACK_RECORD_NUM+1) * sizeof (DEBUG_STACK_RECORD));
		}
		else 
		{
			m_StackArr = (DEBUG_STACK_RECORD*) malloc (sizeof (DEBUG_STACK_RECORD));
			m_StackNum = 1;
			m_StackArr[0].m_Name			= "NA";
			m_StackArr[0].m_FileName	= "NA";
			m_StackArr[0].m_Line			=    0;
		}
		m_nCount =  0;
	}
#else
// Использование переопределнных операторов new
	MM_DEBUG_RECORD (const char * sFileName, int nLine)
	{
		int nFileName_Len = strlen (sFileName);
		m_sFile	= (char *) malloc (nFileName_Len+1);
		if (m_sFile==NULL)
		{
			MM_ERROR_1 ("MM_DEBUG_RECORD::MM_DEBUG_RECORD -- Can't alloc memory for m_sFile. Size = %d", nFileName_Len+1);
		}
		strcpy (m_sFile, sFileName);
		m_nLine	=	nLine;
		m_nCount =  0;
	}
#endif

	void * operator new (size_t nSize)		
	{
		void * ptr = malloc (nSize);
		if (ptr==NULL)
		{
			MM_ERROR_1 ("MM_DEBUG_RECORD::new -- Can't alloc memory for record. Size = %d", nSize);
		}
		return ptr;
	}
	void operator delete (void * pData)
	{
		free (pData);
	}
	~MM_DEBUG_RECORD ()
	{
#ifdef USE_STACK_LEAK_TRACING
		if (m_StackArr)
			free (m_StackArr);
		m_StackArr = NULL;
		m_StackNum =0;
#else
		if (m_sFile)
			free (m_sFile);
		m_sFile = NULL;
#endif
	}
};
//----------------------------------------------------------------------------[] 
MM_DEBUG_RECORD **	MM_RECORD_ARR = NULL;
int						MM_RECORD_NUM = 0;

#ifdef USE_STACK_LEAK_TRACING
int MM_DEBUG_RECORD_NEW ()
{
	register int  i	=	0;
	static	int _i	=	0;

	if ((_i>=0) && (_i<MM_RECORD_NUM) && (MM_RECORD_ARR[_i]!=NULL))
	{
		if (memcmp (MM_RECORD_ARR[_i]->m_StackArr, DEBUG_STACK_RECORD_ARR, (DEBUG_STACK_RECORD_NUM+1) * sizeof (DEBUG_STACK_RECORD))==0)
		{
			MM_RECORD_ARR[_i]->m_nCount ++; 
			return _i;
		}
	}
	for (i=0; i<MM_RECORD_NUM; i++)
	{
		if (memcmp (MM_RECORD_ARR[i]->m_StackArr, DEBUG_STACK_RECORD_ARR, (DEBUG_STACK_RECORD_NUM+1) * sizeof (DEBUG_STACK_RECORD))==0)
		{
			_i    = i;
			MM_RECORD_ARR[_i]->m_nCount ++; 
			return _i;
		}
	}

	MM_DEBUG_RECORD ** ppTmp = (MM_DEBUG_RECORD **) malloc ((MM_RECORD_NUM+1)*sizeof(MM_DEBUG_RECORD*));
	memcpy (ppTmp, MM_RECORD_ARR, MM_RECORD_NUM*sizeof(MM_DEBUG_RECORD*));
	if (MM_RECORD_ARR) 
		free (MM_RECORD_ARR);
	MM_RECORD_ARR = ppTmp;
	MM_RECORD_ARR[MM_RECORD_NUM] = new MM_DEBUG_RECORD ();

	MM_RECORD_NUM ++;

	_i    = i;
	MM_RECORD_ARR[_i]->m_nCount ++; 
	return _i;
}
#else
int MM_DEBUG_RECORD_NEW (const char * sFileName, int nLine)
{
	register int  i	=	0;
	static	int _i	=	0;

	if ((_i>=0) && (_i<MM_RECORD_NUM) && (MM_RECORD_ARR[_i]!=NULL))
	{
		if ((MM_RECORD_ARR[_i]->m_nLine == nLine) && (strcmp (MM_RECORD_ARR[_i]->m_sFile, sFileName)==0))
		{
			MM_RECORD_ARR[_i]->m_nCount ++; 
			return _i;
		}
	}
	for (i=0; i<MM_RECORD_NUM; i++)
	{
		if ((MM_RECORD_ARR[i]->m_nLine == nLine) && (strcmp (MM_RECORD_ARR[i]->m_sFile, sFileName)==0))
		{
			_i    = i;
			MM_RECORD_ARR[_i]->m_nCount ++; 
			return _i;
		}
	}

	MM_DEBUG_RECORD ** ppTmp = (MM_DEBUG_RECORD **) malloc ((MM_RECORD_NUM+1)*sizeof(MM_DEBUG_RECORD*));
	memcpy (ppTmp, MM_RECORD_ARR, MM_RECORD_NUM*sizeof(MM_DEBUG_RECORD*));
	if (MM_RECORD_ARR) 
		free (MM_RECORD_ARR);
	MM_RECORD_ARR = ppTmp;
	MM_RECORD_ARR[MM_RECORD_NUM] = new MM_DEBUG_RECORD (sFileName, nLine);

	MM_RECORD_NUM ++;

	_i    = i;
	MM_RECORD_ARR[_i]->m_nCount ++; 
	return _i;
}
#endif
//----------------------------------------------------------------------------[] 
void MM_DEBUG_RECORD_DELETE (int nIndex)
{
	MM_RECORD_ARR[nIndex]->m_nCount --;
}
//----------------------------------------------------------------------------[] 
void MM_DEBUG_RECORD_FREE_ARRAY ()
{
	int i = 0;
	for (i=0; i<MM_RECORD_NUM; i++)
	{
		delete MM_RECORD_ARR[i];
	}
	if (MM_RECORD_ARR) 
		free (MM_RECORD_ARR);
}
//----------------------------------------------------------------------------[] 		
bool MM_DEBUG_RECORD_TRACE ()
{
	int i = 0;
	bool bRes = true;
	for (i=0; i<MM_RECORD_NUM; i++)
	{
		if (MM_RECORD_ARR[i]->m_nCount!=0)
		{
			#ifdef USE_STACK_LEAK_TRACING
				static char SSSS[10240];
				sprintf (SSSS, "%10d leak%s:\n", MM_RECORD_ARR[i]->m_nCount, MM_RECORD_ARR[i]->m_nCount==1?"":"s");
				int j=0;
				for (j = 0; j<20 && j<MM_RECORD_ARR[i]->m_StackNum; j++)
				{
					char sLine [1024];
					sprintf (sLine, "           %-15s  %s (%d)\n", MM_RECORD_ARR[i]->m_StackArr[j].m_Name, MM_RECORD_ARR[i]->m_StackArr[j].m_FileName, MM_RECORD_ARR[i]->m_StackArr[j].m_Line);
					strcat (SSSS, sLine);
				}
				MM_ERROR_1 ("%s", SSSS);
				bRes = false;
			#else
				char sLine [256];
				sprintf (sLine, "(%d)", MM_RECORD_ARR[i]->m_nLine);
				MM_ERROR_4 ("   %-50s %-6s: %10d leak%s", MM_RECORD_ARR[i]->m_sFile, sLine, MM_RECORD_ARR[i]->m_nCount, MM_RECORD_ARR[i]->m_nCount==1?"":"s");
				bRes = false;
			#endif
		}
	}

	return bRes;
}
#endif
//____________________________________________________________________________[]




#ifdef USE_RVK_MEMORY_MANAGER
//----------------------------------------------------------------------------[] 
void SET_FAT_ITEM (pbyte pFAT, int iBlock, byte bValue)
{
#ifndef USE_ONE_BIT_FOR_FAT
	pFAT [iBlock] = bValue;
	return;
#endif

	int	ByteNum	=	iBlock >> 3;
	int	BitNum	=	iBlock  % 8;
	byte	Mask		=	(byte)(1 << BitNum);
	byte	ArrValue	=	*(pFAT+ByteNum);
	byte	Result	=	byte(bValue? (ArrValue | Mask) : (ArrValue & ~Mask));

	*(pFAT+ByteNum) = Result;
}
//----------------------------------------------------------------------------[] 
bool GET_FAT_ITEM (pbyte pFAT, int iBlock)
{
#ifndef USE_ONE_BIT_FOR_FAT
	return pFAT [iBlock]!=0;
#endif

	byte	item	= *(pFAT + (iBlock >> 3));
	byte	mask	= 	(byte)(1 << (int(iBlock) % 8));
	bit	res	=	(item & mask) != 0;

	return  res;
}
//----------------------------------------------------------------------------[] 
int GET_FIRST_FREE_FAT_ITEM (pbyte pFAT)
{
	int i,j;
#ifndef USE_ONE_BIT_FOR_FAT
	for (j=0; j<PAGE_ITEMS_NUM; j++)
	{
		if (GET_FAT_ITEM (pFAT, j)==0)
		{
			return j;
		}
	}
	return -1;
#endif


	//----------------------------------------------------------------------------[] 
	static int FIRST_ZERO_BIT[256];
	static bool bNeedPrecalc = true;
	if (bNeedPrecalc)
	{
		int BitMask [9] = {1,   2,   4,   8,   16,  32,  64,  128, 256};
		for (i=0; i<256; i++)
		{
			FIRST_ZERO_BIT[i] = -1;
			byte B = (byte) (i^0xFF);
			for (j=0; j<8; j++)
			{
				if (B & BitMask [j])
				{
					FIRST_ZERO_BIT [i] = j;
					break;
				}
			}
		}
		bNeedPrecalc = false;
	}
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	int nRes=-1;
	unsigned int  * pINT  = (unsigned int *) pFAT;
	for (i=0; i < FAT_SIZE/sizeof (int); i++) if (pINT[i] != ALL_BITS_IN_INTEGER)
	{
		break;
	}
	for (j=i*sizeof (int); j < (int)((i+1)*sizeof (int)); j++) if (pFAT[j] != ALL_BITS_IN_BYTE)
	{
		nRes = j*8 + FIRST_ZERO_BIT [pFAT[j]];
		break;
	}	
	//----------------------------------------------------------------------------[] 


	return nRes;
}
//----------------------------------------------------------------------------[] 







//----------------------------------------------------------------------------[] 


class MemoryManager;


//______________________________________________________________________________
//                                                                            []
//` MemoryPage                                                                []          
//                                                                            []
struct MemoryPage
{
	pbyte		m_Ptr;
	int		m_Alloced;
	int 		m_iBlock; // Предположительно, первый свободный блок на странице.

#ifdef USE_MEMORY_LEAKS_TRACING
	int		m_DebugRecordIndex[PAGE_ITEMS_NUM];
#endif
	
	MemoryPage (size_t nSize);

	~MemoryPage ();

	public: void * operator new		(size_t nSize);
	public: void	operator delete	(void * pData);
};
MemoryPage::MemoryPage (size_t nSize)
{
	m_Ptr	=  (pbyte) malloc (nSize);
	if (m_Ptr==NULL)
	{
		MM_ERROR_1 ("MemoryPage::MemoryPage -- Can't alloc memory for page. Size = %d", nSize);
	}
	m_Alloced	= 0;
	m_iBlock		= 0;
#ifdef USE_MEMORY_LEAKS_TRACING
	for (int i=0; i<PAGE_ITEMS_NUM; i++)
		m_DebugRecordIndex[i] = -1;
#endif
}
MemoryPage::~MemoryPage ()
{
	if (m_Ptr!=NULL)
	{
		free (m_Ptr);
	}
}
void * MemoryPage::operator new (size_t nSize)		
{
	void * ptr = malloc (nSize);
	if (ptr==NULL)
	{
		MM_ERROR_1 ("MemoryPage::new -- Can't alloc memory for page. Size = %d", nSize);
	}
	return ptr;
}
void	MemoryPage::operator delete	(void * pData)		{free (pData);}

typedef MemoryPage* pMemoryPage;
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` PageManager                                                               []           
//                                                                            []
class PageManager
{
	int				m_Number;
	MemoryPage **	m_PageArr;
	int				m_PageNum;
	int				m_iPage;
	int				m_Alloced;
	int				m_Hits;
	int				m_nReservedPage;
	int				m_BlockTotalSize;

	public: PageManager ();
	public: ~PageManager ();
	void GetFreePagePos (int& iPage, int& iBlock);

#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		void * Alloc (int& nReservedPageCount);
	#else
		void * Alloc (int& nReservedPageCount, const char * sFileName, int nLine);
	#endif
#else
	void * Alloc (int& nReservedPageCount);
#endif

	bool Free (int iPage, int iBlock, int& nReservedPageCount, const void* pData);

	public: void Init (int nNumber);
	friend MemoryManager;
};
//____________________________________________________________________________[]


PageManager::PageManager ()
{
	m_Hits				=  0;
	m_Number				=  0;
	m_PageArr			=  NULL;
	m_PageNum			=  0;
	m_iPage				=  0;
	m_Alloced			=	0;
	m_nReservedPage	= -1;
	m_BlockTotalSize	=  0;
}

PageManager::~PageManager ()
{
	for (int i=0; i<m_PageNum; i++)
	{
		if (m_PageArr[i]!=NULL)
			delete m_PageArr[i];
	}
	if (m_PageArr)
	{
		free (m_PageArr);
	}
}
//----------------------------------------------------------------------------[] 









//----------------------------------------------------------------------------[] 
void PageManager::GetFreePagePos (int& iPage, int& iBlock)
{
	int	   i;
	iPage = -1;

// Если есть возможность найти не полностью занятую страничку
	if (m_Alloced < m_PageNum*PAGE_ITEMS_NUM)
	{
	// Смотрим, свободна ли закэшированная страница m_iPage
		if (m_PageArr[m_iPage] && (m_PageArr[m_iPage]->m_Alloced<PAGE_ITEMS_NUM))
		{
			iPage = m_iPage; //RVK:>>>
		}
	// Если есть резервная страница -- используем её
		else if (m_nReservedPage !=-1)
		{
			iPage		= m_nReservedPage;
			m_iPage	= iPage;
			iBlock	= 0;
			return;
		}
	// Находим не полностью занятую страницу
		else for (i=0; i<m_PageNum; i++) if (m_PageArr[i]!=NULL)
		{
			if (m_PageArr[i]->m_Alloced<PAGE_ITEMS_NUM)
			{
				iPage		= i;
				m_iPage	= iPage;
			}
		}
	}


// На не полностью занятой странице находим свободный блок.
	if ((iPage>=0) && (iPage<m_PageNum))
	{
		pbyte pFAT = GET_FAT_PTR (m_PageArr[iPage]->m_Ptr);

		if (GET_FAT_ITEM(pFAT, m_PageArr[iPage]->m_iBlock)==0)
		{
			iBlock = m_PageArr[iPage]->m_iBlock; //RVK:>>>
			return;
		}
		else 
		{
			iBlock	= GET_FIRST_FREE_FAT_ITEM (pFAT);
			return;
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//
// Все существующие страницы заняты.
//
//----------------------------------------------------------------------------[] 


// Ищем в массиве страниц пустую.
	int nNewPage = -1;
	for (i=0; i<m_PageNum; i++) if (m_PageArr[i]==NULL)
	{
		nNewPage = i;
		break;
	}

// Переаллокируем массив указателей на страницы
	if (nNewPage==-1)
	{
		int nAddPage = max (1, m_PageNum/10);
		int pTMP_SIZE = (m_PageNum+nAddPage)*sizeof (pMemoryPage);
		pMemoryPage * pTMP =  (pMemoryPage*) malloc (pTMP_SIZE);
		if (pTMP==NULL)
		{
			MM_ERROR_3 ("PageManager[%d:%d] -- Can't realloc memory for page array. Size = %d", m_Number, BLOCK_SIZE[m_Number], pTMP_SIZE);
			iPage = -1;
			return;
		}

		bzero (pTMP, pTMP_SIZE);

		if (m_PageArr)
		{
			memcpy	(pTMP, m_PageArr, m_PageNum*sizeof (pvoid));
			free		(m_PageArr);
		}
		nNewPage		=	m_PageNum;
		m_PageNum	+=	nAddPage;
		m_PageArr	=	pTMP;
	}

// Создаём новую страницу
	int nPageSize = PAGE_SIZE (m_Number);
	m_PageArr[nNewPage] = new MemoryPage (nPageSize);
	if (m_PageArr[nNewPage]==NULL)
	{
		MM_ERROR_3 ("PageManager[%d:%d] -- Can't alloc memory for page %d.", m_Number, BLOCK_SIZE[m_Number], nNewPage);
		iPage = -1;
		return;
	}

	if (m_PageArr[nNewPage]->m_Ptr==NULL)
	{
		MM_ERROR_3 ("PageManager[%d:%d] -- Can't alloc data-block for page %d.", m_Number, BLOCK_SIZE[m_Number], nNewPage);
		iPage = -1;
		return;
	}

	pbyte pPage = m_PageArr[nNewPage]->m_Ptr;
	bzero (pPage, nPageSize);

// Форматируем страницу
	int nShift = 0;
	int * pPageNum = (int *) pPage;
	* pPageNum =  nNewPage;
	nShift += sizeof(int);
	nShift += FAT_SIZE;
	nShift += WASTE_SIZE;
	int BLOCK_SHIFT = 2+BLOCK_SIZE [m_Number];
	for (i=0; i<PAGE_ITEMS_NUM; i++)
	{
	// Прописываем тип размера блока и его номер внутри страницы
		ushort BH = MAKE_BLOCK_HEADER (m_Number, i);
		*((ushort*) (pPage+nShift)) = BH;
		nShift += BLOCK_SHIFT;
	}

	iPage		= nNewPage;
	iBlock	= 0;
	m_iPage  = nNewPage;
}
//----------------------------------------------------------------------------[] 













//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		void * PageManager::Alloc (int& nReservedPageCount)
	#else	
		void * PageManager::Alloc (int& nReservedPageCount, const char * sFileName, int nLine)
	#endif
#else
	void * PageManager::Alloc (int& nReservedPageCount)
#endif
{
	register int iPage	= -1;
	register int iBlock	= -1;

	GetFreePagePos (iPage, iBlock);

	if (iPage==-1)
	{
		MM_ERROR_3 ("PageManager[%d:%d] -- Can't alloc memory. Total allocated size=%d", m_Number, BLOCK_SIZE[m_Number], MEMORY_MANAGER_GET_SIZE ());
		return NULL;
	}

	if (iPage == m_nReservedPage)
	{
		m_nReservedPage	= -1;
		nReservedPageCount  --;
	}

	pbyte pFAT  = GET_FAT_PTR (m_PageArr[iPage]->m_Ptr);
	pbyte pDATA = GET_DATA_PTR (m_PageArr[iPage]->m_Ptr);
	SET_FAT_ITEM (pFAT, iBlock, 1);

	void * pRes = pDATA + 2 + iBlock*m_BlockTotalSize;

	m_PageArr[iPage]->m_Alloced++;
	m_PageArr[iPage]->m_iBlock = min (m_PageArr[iPage]->m_iBlock+1, PAGE_ITEMS_NUM-1);

#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		m_PageArr[iPage]->m_DebugRecordIndex [iBlock] = MM_DEBUG_RECORD_NEW ();
	#else
		m_PageArr[iPage]->m_DebugRecordIndex [iBlock] = MM_DEBUG_RECORD_NEW (sFileName, nLine);
	#endif
#endif

	m_Hits	 ++;
	m_Alloced ++;
	return  pRes;
}
//----------------------------------------------------------------------------[] 

	
//----------------------------------------------------------------------------[] 
bool PageManager::Free (int iPage, int iBlock, int& nReservedPageCount, const void* pData)
{
	if (iPage<0 || iPage>=m_PageNum || iBlock<0 || iBlock>=PAGE_ITEMS_NUM)
	{
		MM_ERROR_1 ("Memory block 0x%p corrupted", pData);
		return false;
	}
	pbyte pFAT  = GET_FAT_PTR (m_PageArr[iPage]->m_Ptr);
	if (GET_FAT_ITEM (pFAT, iBlock)==0)
	{
		MM_ERROR_2 ("Attempt to free unusable block 0x%p [size=%d]", pData, BLOCK_SIZE[m_Number]);
		return false;
	}
	SET_FAT_ITEM (pFAT, iBlock, 0);
	m_PageArr[iPage]->m_Alloced--;
	m_Alloced --;

#ifdef USE_MEMORY_LEAKS_TRACING
	MM_DEBUG_RECORD_DELETE (m_PageArr[iPage]->m_DebugRecordIndex [iBlock]);
	m_PageArr[iPage]->m_DebugRecordIndex [iBlock] = -1;
#endif

// Страница освободилась
	if (m_PageArr[iPage]->m_Alloced==0)
	{
	// Нет резервной страницы -- оставляем освободившуюся под резерв
		if (m_nReservedPage==-1)
		{
			m_nReservedPage        = iPage;
			m_PageArr[iPage]->m_iBlock	= 0;
			nReservedPageCount ++;
		}
	// Резервная страница есть -- просто уничтожаем освободившуюся
		else 
		{
			delete m_PageArr[iPage];
			m_PageArr[iPage] = NULL;
		}
	}
// Страница ещё занята -- запоминаем освободившуюся позицию и страницу
	else
	{
		m_iPage							=  iPage;
		m_PageArr[iPage]->m_iBlock	=	iBlock;
	}
	return true;
}
//----------------------------------------------------------------------------[] 



void PageManager::Init (int nNumber)
{
	m_Number				= nNumber;
	m_BlockTotalSize	= 2+BLOCK_SIZE[m_Number];
}
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
	int			m_nDropCount;
	int			m_nReservedPageCount;
	int			m_Alloced;
	int			m_nOutPageTotalSize;
	int			m_nOutPageBlocksNum;
	int			m_Hits;
	int			m_OutHits;


	//----------------------------------------------------------------------------[] 
	protected: void Init ();
	public: void * operator new		(size_t nSize);
	public: void	operator delete	(void * pData);
	//----------------------------------------------------------------------------[] 


	public: MemoryManager ();
	public: ~MemoryManager ();

	protected: bool CheckLeaks ();



	protected: const char * GetSizeName (unsigned long nSize);

	public: const char * GetReport (size_t *pnTotal);


	protected: int FindPageManagerBySize (size_t nSize);


	protected: int FindPageManagerByPtr (const void * pData, int& iPage, int& iBlock);

	//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		public: void * Alloc (size_t nSize);
	#else
		public: void * Alloc (size_t nSize, const char * sFileName, int nLine);
	#endif
#else
	public: void * Alloc (size_t nSize);
#endif

	public: void CleanUp ();

	public: void Free (void * pData);
};
//____________________________________________________________________________[]








//----------------------------------------------------------------------------[] 
void MemoryManager::Init ()
{
	int i;
	m_PageManagerNum = PAGE_MANAGER_NUM;
	for (i=0; i<m_PageManagerNum; i++)
	{
		if (bUSE_MAX_PAGED_BLOCK)
			BLOCK_SIZE[i] = (i==0? 14: (BLOCK_SIZE[i-1] + max (16, BLOCK_SIZE[i-1]*100/1090/16*16)));
		else
			BLOCK_SIZE[i] = 14 + i*16;
		m_PageManager[i].Init (i);
	}
	m_Hits					= 0;
	m_OutHits				= 0;
	m_Alloced				= 0;
	m_nDropCount			= 0;
	m_nReservedPageCount	= 0;
	m_nOutPageTotalSize	= 0;
	m_nOutPageBlocksNum	= 0;
}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
void * MemoryManager::operator new		(size_t nSize)		{return malloc (nSize);}
void	MemoryManager::operator delete	(void * pData)		{free (pData);}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
MemoryManager::MemoryManager ()
{
	Init();
}
//----------------------------------------------------------------------------[] 
MemoryManager::~MemoryManager ()
{
	CheckLeaks				();
#ifdef USE_MEMORY_LEAKS_TRACING
	MM_DEBUG_RECORD_FREE_ARRAY ();
#endif
}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
bool MemoryManager::CheckLeaks ()
{
	int i,j;
	bool bRes = true;
// Проверяем общее несовпадение new/delete
	if (m_Alloced!=0)
	{
		MM_ERROR   ("\n\n * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		MM_ERROR_2 (" Found %d memory leak%s:\n", m_Alloced, m_Alloced==1?"":"s");

		
		SERVER_DEBUG_ERROR_3 ("MM: Обнаружен%s %d утеч%s памяти\n", m_Alloced==1?"а":"о", m_Alloced, m_Alloced==1?"ка":"ек");
		bRes = false;
	}

#ifdef USE_MEMORY_LEAKS_TRACING
	if (!MM_DEBUG_RECORD_TRACE ())
		bRes = false;
#else
// Проверяем несовпадение по менеджерам страниц
	for (i=0; i<m_PageManagerNum; i++)
	{
	// Общее несовпадение new/delete у i-го менеджера страниц
		if (m_PageManager[i].m_Alloced!=0)
		{
			MM_ERROR_3 ("   %6d memory leaks at PageManager    #%d [block size=%d bytes]", m_PageManager[i].m_Alloced, i, BLOCK_SIZE[i]);
			bRes = false;
		}
	// Остались страницы, занимающиие память
		int nPageLeak=0;
		for (j=0; j<m_PageManager[i].m_PageNum; j++) if (m_PageManager[i].m_PageArr[j]!=NULL)
		{
			nPageLeak ++;
		}
		if (nPageLeak>1)
		{
			MM_ERROR_3 ("   %6d allocated pages at PageManager #%d [block size=%d bytes]", nPageLeak, i, BLOCK_SIZE[i]);
			bRes = false;
		}
#if 0  //{ RomanVK
	// На сраницах остались блоки, занимающиие память
		for (j=0; j<m_PageManager[i].m_PageNum; j++) if (m_PageManager[i].m_PageArr[j]!=NULL)
		{
			if (m_PageManager[i].m_PageArr[j]->m_Alloced!=0)
			{
				MM_ERROR_3  ("       %4d allocated blocks at page %d [block size=%d bytes]", m_PageManager[i].m_PageArr[j]->m_Alloced, j, BLOCK_SIZE[i]);
				bRes = false;
			}
		}
#endif //}
	}
// Остались большие блоки, размещённые вне страниц.
	if (m_nOutPageBlocksNum)
	{
		MM_ERROR_2  ("   %d allocated out-page blocks. Total size = %d bytes.", m_nOutPageBlocksNum, m_nOutPageTotalSize);
		bRes = false;
	}
#endif

	if (bRes == false)
	{
		MM_ERROR   ("\n * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n\n\n");
	}

	return bRes;
}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
const char * MemoryManager::GetSizeName (unsigned long nSize)
{
	static char SSS [1024];
	static char sss [1024];
	SSS[0]=0;
	sss[0]=0;

	bool bSign=false;
	if (nSize>=1000*1000*1000)
	{
		sprintf (sss, "%d,", nSize/1000/1000/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000*1000*1000);
		bSign = true;
	}

	if (bSign || nSize>=1000*1000)
	{
		sprintf (sss, bSign? "%03d,": "%d,", nSize/1000/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000*1000);
		bSign = true;
	}

	if (bSign || nSize>=1000)
	{
		sprintf (sss, bSign? "%03d,": "%d,", nSize/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000);
		bSign = true;
	}

	sprintf (sss, bSign? "%03d": "%d", nSize);
	strcat (SSS, sss);
	return SSS;
}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
const char * MemoryManager::GetReport (size_t *pnTotal)
{
	static char SSS [10240];
	char			sss [1024];
	int			i,j;
	SSS[0] = 0;
	if (pnTotal==NULL)
	{
		sprintf	(sss, "\n\n =============================================================================\n MEMORY MANAGER REPORT:\n -----------------------------------------------------------------------------\n");
		strcat	(SSS, sss);
	}

	int Total   = 0;
	int Useful = 0;

	int Pages   = 0;
	int Blocks  = 0;
	int Waste	= 0;
	int Hits		= 0;

	if (pnTotal==NULL)
	{
		sprintf	(sss, " ##    Size     Allocated       Useful   Waste   Pages     Blocks         Hits\n");
		strcat	(SSS, sss);
		strcat	(SSS, " -----------------------------------------------------------------------------\n");
	}
	for (i=0; i<m_PageManagerNum; i++)
	{
		Total   = 0;
		Useful  = 0;
		Pages   = 0;
		Blocks  = 0;
		Hits	  = m_PageManager[i].m_Hits;

		Total += m_PageManager[i].m_PageNum * sizeof (void*);

		for (j=0; j<m_PageManager[i].m_PageNum; j++)
		{
			if (m_PageManager[i].m_PageArr[j]!=NULL)
			{
				Pages   ++;
				Total   += PAGE_SIZE (i);
				Useful  += m_PageManager[i].m_PageArr[j]->m_Alloced * BLOCK_SIZE[i];
				Blocks  += m_PageManager[i].m_PageArr[j]->m_Alloced;
			}
		}
		Waste = Total?(int)(100*((double)Total - (double)Useful)/(double)Total):0;

		if (pnTotal==NULL)
		{
			sprintf	(sss, " %2d:"		,	i);											strcat	(SSS, sss);
			sprintf	(sss, "%7s  "		,	GetSizeName(BLOCK_SIZE[i]));			strcat	(SSS, sss);
			sprintf	(sss, "%12s "		,	Pages?GetSizeName(Total):"-");		strcat	(SSS, sss);
			sprintf	(sss, "%12s    "	,	Pages?GetSizeName(Useful):"-");		strcat	(SSS, sss);
			if (Pages)
				{sprintf	(sss, "%3d%%%%",	Waste);										strcat	(SSS, sss);}
			else
				{sprintf	(sss, "   -");														strcat	(SSS, sss);}
			sprintf	(sss, "%8s "		,	Pages?GetSizeName(Pages):"-");		strcat	(SSS, sss);
			sprintf	(sss, "%10s"		,	Pages?GetSizeName(Blocks):"-");		strcat	(SSS, sss);
			sprintf	(sss, " %12s\n"	,	GetSizeName(Hits));					strcat	(SSS, sss);
		}
	}



	Total   = 0;
	Useful  = 0;
	Pages   = 0;
	Blocks  = 0;
	for (i=0; i<m_PageManagerNum; i++)
	{
		Total += m_PageManager[i].m_PageNum * sizeof (void*);

		for (j=0; j<m_PageManager[i].m_PageNum; j++)
		{
			if (m_PageManager[i].m_PageArr[j]!=NULL)
			{
				Pages   ++;
				Total   += PAGE_SIZE (i);
				Useful  += m_PageManager[i].m_PageArr[j]->m_Alloced * BLOCK_SIZE[i];
				Blocks  += m_PageManager[i].m_PageArr[j]->m_Alloced;
			}
		}
	}

	Waste = Total?(int)(100*((double)Total - (double)Useful)/(double)Total):0;

	if (pnTotal==NULL)
	{
		strcat	(SSS, " -----------------------------------------------------------------------------\n");
		sprintf	(sss, " ##    Size     Allocated       Useful   Waste   Pages     Blocks         Hits\n");
		strcat	(SSS, sss);
		strcat	(SSS, " -----------------------------------------------------------------------------\n");

		strcat	(SSS, " Out-placed: ");
		sprintf	(sss, "%12s"		,	GetSizeName(m_nOutPageTotalSize));		strcat	(SSS, sss);
		sprintf	(sss, " %12s",			GetSizeName(m_nOutPageTotalSize));		strcat	(SSS, sss);
		sprintf	(sss, "      NA      NA %10s",	
						GetSizeName(m_nOutPageBlocksNum));								strcat	(SSS, sss);
		sprintf	(sss, " %12s"		,	GetSizeName(m_OutHits));					strcat	(SSS, sss);

		strcat	(SSS, "\n  In-placed: ");
		sprintf	(sss, "%12s "		,	GetSizeName(Total));							strcat	(SSS, sss);
		sprintf	(sss, "%12s    "	,	GetSizeName(Useful));						strcat	(SSS, sss);
		sprintf	(sss, "%3d%%%%"	,	Waste);											strcat	(SSS, sss);
		sprintf	(sss, "%8s "		,	GetSizeName(Pages));							strcat	(SSS, sss);
		sprintf	(sss, "%10s "		,	GetSizeName(Blocks));						strcat	(SSS, sss);
		sprintf	(sss, "%12s\n"		,	GetSizeName(m_Hits));						strcat	(SSS, sss);
	}

	Total   += m_nOutPageTotalSize;
	Useful  += m_nOutPageTotalSize;
	Blocks  += m_nOutPageBlocksNum;
	Waste = Total?(int)(100*((double)Total - (double)Useful)/(double)Total):0;

	if (pnTotal==NULL)
	{
		strcat	(SSS, " Total info: ");
		sprintf	(sss, "%12s "		,	GetSizeName(Total));							strcat	(SSS, sss);
		sprintf	(sss, "%12s    "	,	GetSizeName(Useful));						strcat	(SSS, sss);
		sprintf	(sss, "%3d%%%%"	,	Waste);											strcat	(SSS, sss);
		sprintf	(sss, "%8s "		,	GetSizeName(Pages));							strcat	(SSS, sss);
		sprintf	(sss, "%10s "		,	GetSizeName(Blocks));						strcat	(SSS, sss);
		sprintf	(sss, "%12s\n"		,	GetSizeName(m_Hits+m_OutHits));			strcat	(SSS, sss);

		sprintf	(sss, " =============================================================================\n\n\n");
		strcat	(SSS, sss);
		return SSS;
	}

	if (pnTotal!=NULL)
	{
		* pnTotal = Total;
	}

	return "";
}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
int MemoryManager::FindPageManagerBySize (size_t nSize)
{
	static int _i=-1;

	int	 i;
	if (_i==0 && nSize<=BLOCK_SIZE[_i])
	{
		return _i; //RVK:>>>
	}
	if (_i>0 && (nSize<=BLOCK_SIZE[_i]) && (nSize>BLOCK_SIZE[_i-1]))
	{
		return _i;
	}
	if (nSize > BLOCK_SIZE[m_PageManagerNum-1])
	{
		_i = -1;
		return OUTSIDE_PAGE_NUM;
	}
	for (i=0; i<m_PageManagerNum; i++)
	{
		if (nSize<=BLOCK_SIZE[i])
		{
			_i   = i;
			return i;
		}
	}
	return OUTSIDE_PAGE_NUM;
}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
int MemoryManager::FindPageManagerByPtr (const void * pData, int& iPage, int& iBlock)
{
	pbyte	 ptr	= (pbyte) pData;
	ushort BH	= *((ushort *)(ptr-2));
	if (BH == NON_PAGED_PTR)
		return OUTSIDE_PAGE_NUM;

	int nBlockSize_type = GET_SIZE_TYPE_FROM_BLOCK_HEADER (BH);
	if (nBlockSize_type<0 || nBlockSize_type>=PAGE_MANAGER_NUM)
		return OUTSIDE_PAGE_NUM;

	int nBlockSize		  = BLOCK_SIZE         [nBlockSize_type];
	int nPosInPage		  = GET_BLOCK_NUM_FROM_BLOCK_HEADER	(BH);

	iBlock = nPosInPage;
	iPage  = * (int*)  (ptr - 2 - (2+nBlockSize)*nPosInPage - WASTE_SIZE - FAT_SIZE - sizeof (int));

	return nBlockSize_type;
}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		void * MemoryManager::Alloc (size_t nSize)
	#else
		void * MemoryManager::Alloc (size_t nSize, const char * sFileName, int nLine)
	#endif
#else
	void * MemoryManager::Alloc (size_t nSize)
#endif
{
	m_Alloced ++;

	int nPageManager = FindPageManagerBySize (nSize);
// Разместить не на странице (большие данные)
	if (nPageManager==OUTSIDE_PAGE_NUM)
	{
		m_OutHits	 ++;
		pbyte pData = (pbyte) malloc (nSize+PARAGRAF_SIZE);
		if (pData==NULL)
		{
			MM_ERROR_2 ("Can't alloc memory for out-page block. Size = %d. Total allocated size=%d", nSize, MEMORY_MANAGER_GET_SIZE ());
			return NULL;
		}
		
		*((ushort*)(pData + PARAGRAF_SIZE - 2))	= NON_PAGED_PTR;
		*((int   *)(pData))								= nSize;
		m_nOutPageTotalSize += nSize;
		m_nOutPageBlocksNum ++;
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		*(((int   *)(pData))+1)							= MM_DEBUG_RECORD_NEW ();
	#else
		*(((int   *)(pData))+1)							= MM_DEBUG_RECORD_NEW (sFileName, nLine);
	#endif
#endif
		return pData+PARAGRAF_SIZE;
	}
// Разместить на странице
	else
	{
		m_Hits	 ++;
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		return m_PageManager[nPageManager].Alloc (m_nReservedPageCount);
	#else
		return m_PageManager[nPageManager].Alloc (m_nReservedPageCount, sFileName, nLine);
	#endif
#else
		return m_PageManager[nPageManager].Alloc (m_nReservedPageCount);
#endif
	}
	return NULL;
}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
void MemoryManager::CleanUp ()
{
	m_nDropCount			= 0;
	m_nReservedPageCount	= 0;

	for (int i=0; i<m_PageManagerNum; i++)
	{
		m_PageManager[i].m_nReservedPage = -1;
		for (int j=0; j<m_PageManager[i].m_PageNum; j++)
		{
			if (m_PageManager[i].m_PageArr[j]!=NULL && m_PageManager[i].m_PageArr[j]->m_Alloced==0)
			{
				delete m_PageManager[i].m_PageArr[j];
				m_PageManager[i].m_PageArr[j] = NULL;
			}
		}
	}
}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
void MemoryManager::Free (void * pData)
{
	if (m_nDropCount%DROP_RESERVED_PAGE_COUNT==0)
	{
		m_nDropCount = 0;
		if (m_nReservedPageCount>0) for (int i=0; i<m_PageManagerNum; i++)
		{
			if (m_PageManager[i].m_nReservedPage!=-1)
			{
				delete m_PageManager[i].m_PageArr[m_PageManager[i].m_nReservedPage];
				m_PageManager[i].m_PageArr[m_PageManager[i].m_nReservedPage] = NULL;
				m_PageManager[i].m_nReservedPage = -1;
			}
		}
	}
	m_nDropCount++;

	int iPage	= -1;
	int iBlock	= -1;
	int nPageManager = FindPageManagerByPtr (pData, iPage, iBlock);
// Указатель не на странице (большие данные)
	if (nPageManager==OUTSIDE_PAGE_NUM) 
	{
		if ( *((ushort*) ((pbyte) pData-2)) == NON_PAGED_PTR)
		{
			int nSize	= *((int*)((pbyte)pData-PARAGRAF_SIZE));
#ifdef USE_MEMORY_LEAKS_TRACING
			int nRecord = *(((int*)((pbyte)pData-PARAGRAF_SIZE))+1);
			MM_DEBUG_RECORD_DELETE (nRecord);
#endif
			m_nOutPageTotalSize -= nSize;
			m_nOutPageBlocksNum --;
			free (((pbyte)pData) - PARAGRAF_SIZE);
			m_Alloced --;
		}
		else
		{
			MM_ERROR_1 ("Wrong non-paged pointer 0x%p", pData);
		}
	}
// Указатель на странице
	else 
	{
		if (m_PageManager[nPageManager].Free (iPage, iBlock, m_nReservedPageCount, pData))
		{
			m_Alloced --;
		}
	}
}
//____________________________________________________________________________[]





























//______________________________________________________________________________
//                                                                            []
//` ОПЕРАТОРЫ new/delete                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
MemoryManager * pMemoryManager = NULL;
bool bPRINT_NEW_NOT		= true;
bool bPRINT_DELETE_NOT  = true;
//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING
	#ifdef USE_STACK_LEAK_TRACING
		void * operator new (unsigned int nSize)
	#else
		void * operator new (unsigned int nSize, const char * sFileName, int nLine)
	#endif
{
	if (pMemoryManager)
	{
		#ifdef USE_STACK_LEAK_TRACING
			return pMemoryManager->Alloc	(nSize);
		#else
			return pMemoryManager->Alloc	(nSize, sFileName, nLine);
		#endif
	}
#ifdef ALLERT_WRONG_CALLS
	if (bPRINT_NEW_NOT)
		MM_ERROR ("\n* * * NEW: Memory manager not initialized * * *\n");
	bPRINT_NEW_NOT = false;
#endif
	return malloc (nSize);
}
#else
//----------------------------------------------------------------------------[] 
void * operator new (unsigned int nSize)
{
	if (pMemoryManager)
	{
		return pMemoryManager->Alloc	(nSize);
	}
#ifdef ALLERT_WRONG_CALLS
	if (bPRINT_NEW_NOT)
		MM_ERROR ("\n* * * NEW: Memory manager not initialized * * *\n");
	bPRINT_NEW_NOT = false;
#endif
	return malloc (nSize);
}
#endif
//----------------------------------------------------------------------------[] 
#ifdef USE_MEMORY_LEAKS_TRACING_OPNEW
void * operator new[] (unsigned int nSize, const char * sFileName, int nLine)
{
	return operator new (nSize, sFileName, nLine);
}
#else
//----------------------------------------------------------------------------[] 
void * operator new[] (unsigned int nSize)
{
	return operator new (nSize);
}
#endif
//----------------------------------------------------------------------------[] 
void operator delete	(void * pData)
{			
	if (pMemoryManager)
	{
		pMemoryManager->Free	(pData);
		return;
	}
#ifdef ALLERT_WRONG_CALLS
	if (bPRINT_DELETE_NOT)
		MM_ERROR ("\n* * * DELETE: Memory manager not initialized * * *\n");
	bPRINT_DELETE_NOT = false;
#endif
}
//----------------------------------------------------------------------------[] 
void operator delete[] (void * pData)
{			
	operator delete (pData);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ИНТЕРФЕЙС				                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
void MEMORY_MANAGER_START (bool bCanIgnore)
{
	bool bIgnore = false; //true;//false;
	if (pMemoryManager==NULL)
	{
		if (!bIgnore || !bCanIgnore)
		{
			pMemoryManager = new MemoryManager;
		}
	}
}
void			MEMORY_MANAGER_STOP	(){if (pMemoryManager!=NULL){delete pMemoryManager; pMemoryManager = NULL;}}
const char* MEMORY_MANAGER_REPORT(bool bIgnoreTime, size_t * pnTotal)
{
	int AVOID_PRINT_REPORT_AFTER_DAYS = 10;
	time_t MAX_TIME = 943363962/* 23 ноября 1999 16:34 */ + 24*60*60 * AVOID_PRINT_REPORT_AFTER_DAYS;
	if (!bIgnoreTime && (time(0)>MAX_TIME))
		return ""; 
	if (pMemoryManager==NULL)
		return "\nMemory manager is off.\n"; 
	return pMemoryManager->GetReport(pnTotal);
}
//______________________________________________________________________________
//                                                                            []
//` Размер памяти, занятой менеджером                                         []                                 
//                                                                            []
size_t MEMORY_MANAGER_GET_SIZE ()
{
	size_t nTotal;

	pMemoryManager->GetReport(&nTotal);

	return nTotal;
}
//____________________________________________________________________________[]
void			MEMORY_MANAGER_CLEANUP	()			{if (pMemoryManager!=NULL) pMemoryManager->CleanUp();}
//----------------------------------------------------------------------------[] 
#else

void			MEMORY_MANAGER_START		(bool)				{return;}
void			MEMORY_MANAGER_STOP		()						{return;}
const char* MEMORY_MANAGER_REPORT	(bool, size_t*)	{return "\nMemory manager not supported.\n";}
void			MEMORY_MANAGER_CLEANUP	()						{return;}
size_t		MEMORY_MANAGER_GET_SIZE ()						{return 0;}

#endif
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
