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


#define USE_RVK_MEMORY_MANAGER						// ������������ �� ���������� �������������� ������

#ifdef USE_RVK_MEMORY_MANAGER
	#define USE_MEMORY_LEAKS_TRACING					// ��������� �� ���, ���������� ����� ������ ������

//	#define USE_MAX_PAGED_BLOCK						// ��������� �� ��������� ����� �������� �� 10,000 ����
																// ����� -- ��������� ����� �������� ���� ��  �� 1,000 ����
	#define DROP_RESERVED_PAGE_COUNT 10000			// ����� ������� ��������� � delete ���������� ��������� ��������.
																// (��� ������ ������ ����� �������� ���� ��������� ��������, 
																// ����� �� ���� ����������. ������: TheString += "a"; )

	#ifndef _DEBUG
		#undef USE_MEMORY_LEAKS_TRACING
	#endif


	#ifdef USE_MEMORY_LEAKS_TRACING
		#define DEBUG_NEW			new	(__FILE__, __LINE__)
		void * operator new				(unsigned int nSize, const char * sFileName, int nLine);
		void * operator new[]			(unsigned int nSize, const char * sFileName, int nLine);
		#define new							DEBUG_NEW
	#endif
#endif

void				MEMORY_MANAGER_START		(bool bCanIgnore = true);	// ��������� ��������� ������
void				MEMORY_MANAGER_STOP		();								// ���������� ��������� ������
const char *	MEMORY_MANAGER_REPORT	(bool bIgnoreTime=true);	// �������� ������ � ������������� ������
void				MEMORY_MANAGER_CLEANUP	();								// ������� ��� ��������� ��������
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
