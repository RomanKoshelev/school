/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'bcc'                                       []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            MemoryManager.h		                                       []
[] Date:            12.11.1999                                                []
[] Author:          Roman V. Koshelev                                         []
[] Description:     ���������� �������������� ������                          []
[]____________________________________________________________________________[]
*/

#ifndef MemoryManager_h
#define MemoryManager_h

//______________________________________________________________________________
//                                                                            []
//` ����������� ������� ������ ��������� ������											[]
//																										[]
#define MM_IS_A_FIRST_OBJECT																	\
struct __MM_GL																						\
{																										\
	__MM_GL ()																						\
	{																									\
		MEMORY_MANAGER_START();																	\
	}																									\
	~__MM_GL ()																						\
	{																									\
		MEMORY_MANAGER_STOP();																	\
		puts ("\n\n**********************************\n"								\
					 "       FINITA LA COMEDIA          \n"								\
					 "**********************************\n\n");							\
	}																									\
}__mm_gl;
//____________________________________________________________________________[]


#define USE_RVK_MEMORY_MANAGER						// ������������ �� ���������� �������������� ������

#ifdef USE_RVK_MEMORY_MANAGER
//	#define USE_MEMORY_LEAKS_TRACING					// ��������� �� ���, ���������� ����� ������ ������
//	#define USE_STACK_LEAK_TRACING					// �������� ������ ������ ��� ������ �����, ����� -- ������������� �������� new

	#ifdef WIN32
		#ifndef _DEBUG
			#undef USE_MEMORY_LEAKS_TRACING
		#endif
	#else
		#ifdef USE_MEMORY_LEAKS_TRACING
			#define USE_STACK_LEAK_TRACING
		#endif
	#endif	

	#ifdef USE_MEMORY_LEAKS_TRACING
		#ifndef USE_STACK_LEAK_TRACING
			#define USE_MEMORY_LEAKS_TRACING_OPNEW
	   #endif
   #endif
		
//	#define USE_MAX_PAGED_BLOCK						// ��������� �� ��������� ����� �������� �� 10,000 ����
																// ����� -- ��������� ����� �������� ���� ��  �� 1,000 ����
	#define DROP_RESERVED_PAGE_COUNT 10000			// ����� ������� ��������� � delete ���������� ��������� ��������.
																// (��� ������ ������ ����� �������� ���� ��������� ��������, 
																// ����� �� ���� ����������. ������: TheString += "a"; )


   #ifdef USE_MEMORY_LEAKS_TRACING_OPNEW
		#define DEBUG_NEW       new   (__FILE__, __LINE__)
		void * operator new           (unsigned int nSize, const char * sFileName, int nLine);
		void * operator new[]         (unsigned int nSize, const char * sFileName, int nLine);
		#define new                   DEBUG_NEW
   #endif
#endif

void				MEMORY_MANAGER_START		(bool bCanIgnore = true);								// ��������� ��������� ������
void				MEMORY_MANAGER_STOP		();															// ���������� ��������� ������
void				MEMORY_MANAGER_CLEANUP	();															// ������� ��� ��������� ��������

const char *	MEMORY_MANAGER_REPORT	(bool bIgnoreTime=true, size_t * pnTotal=NULL);	// �������� ������ � ������������� ������
size_t			MEMORY_MANAGER_GET_SIZE ();															//	������ ������, ������� ����������

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
