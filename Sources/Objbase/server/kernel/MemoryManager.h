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
[] Description:     Управление распределением памяти                          []
[]____________________________________________________________________________[]
*/

#ifndef MemoryManager_h
#define MemoryManager_h

//______________________________________________________________________________
//                                                                            []
//` Обеспечение порядка вызова менеджера памяти											[]
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


#define USE_RVK_MEMORY_MANAGER						// Использовать ли управление распределением памяти

#ifdef USE_RVK_MEMORY_MANAGER
//	#define USE_MEMORY_LEAKS_TRACING					// Вставлять ли код, помогающий найти утечки памяти
//	#define USE_STACK_LEAK_TRACING					// Находить утечки памяти при помощи стека, иначе -- переопределяя оператор new

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
		
//	#define USE_MAX_PAGED_BLOCK						// Размещать на страницах блоки размером до 10,000 байт
																// Иначе -- размещать блоки размером лишь до  до 1,000 байт
	#define DROP_RESERVED_PAGE_COUNT 10000			// Через сколько обращений к delete сбрасывать резервные страницы.
																// (Под каждый размер блока хранится одна резервная страница, 
																// чтобы не было замедления. Пример: TheString += "a"; )


   #ifdef USE_MEMORY_LEAKS_TRACING_OPNEW
		#define DEBUG_NEW       new   (__FILE__, __LINE__)
		void * operator new           (unsigned int nSize, const char * sFileName, int nLine);
		void * operator new[]         (unsigned int nSize, const char * sFileName, int nLine);
		#define new                   DEBUG_NEW
   #endif
#endif

void				MEMORY_MANAGER_START		(bool bCanIgnore = true);								// Запустить менеджера памяти
void				MEMORY_MANAGER_STOP		();															// Остановить менеджера памяти
void				MEMORY_MANAGER_CLEANUP	();															// Удалить все резервные страницы

const char *	MEMORY_MANAGER_REPORT	(bool bIgnoreTime=true, size_t * pnTotal=NULL);	// Получить сводку о распределении памяти
size_t			MEMORY_MANAGER_GET_SIZE ();															//	Размер памяти, занятой менеджером

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
