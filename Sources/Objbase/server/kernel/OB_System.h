/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OB_System.h                                               []
[] Date:            01.04.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Макросы для работы с основными глобальными объектами		[]
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
#ifndef OB_SYSTEM_H
#define OB_SYSTEM_H


//______________________________________________________________________________
//                                                                            []
//` Указатели на основные глобальные объекты												[]
//																										[]
#define IMPLEMENT_SYSTEM_OBJECTS																\
/* Устанавливается в time(NULL) перед каждым вызовом прикладных функций. */	\
	time_t											time_0							= time(0);\
/* Очистка файловой системы */																\
	CClearFof									*	pCClearFof						= NULL;	\
/* Вывод сообщений об ошибках */																\
	CServerDebug								*	pServerDebug					= NULL;	\
/* Монитор событий */																			\
	CEventMonitor								*	pEventMonitor					= NULL;	\
/* Управление файловой системой */															\
	CFileDriver									*	pFileDriver						= NULL;	\
/* Управление базой объектов */																\
	CObjDriver									*	pObjDriver						= NULL;	\
/* Реестр ошибок для модуля сервера */														\
	CPtr<OBServer_ERROR_DESCRIPTION>		*													\
												pOBServer_ERROR_DESCRIPTION_ARR	= NULL;	\
/* Вспомогательный ключ для OBD_UpdateIndex */											\
	key_arr										*	p_static_ka						= NULL;	\
/* Кэш результатов выполнения функций */													\
	IT_AVTree_ARG_RES_CACHE					*	pArgResCache					= NULL;	\
/* Кэш объектов базы данных */																\
	OBJ_CACHE									*  pOBJ_CACHE						= NULL;
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Определение указателей на основные глобальные объекты							[]
//																										[]
#define DECLARE_SYSTEM_OBJECTS																\
/* Очистка файловой системы */																\
	extern CClearFof									*	pCClearFof;							\
/* Вывод сообщений об ошибках */																\
	extern CServerDebug								*	pServerDebug;						\
/* Монитор событий */																			\
	extern CEventMonitor								*	pEventMonitor;						\
/* Управление файловой системой */															\
	extern CFileDriver								*	pFileDriver;						\
/* Управление базой объектов */																\
	extern CObjDriver									*	pObjDriver;							\
/* Реестр ошибок для модуля сервера */														\
	extern CPtr<OBServer_ERROR_DESCRIPTION>	*	pOBServer_ERROR_DESCRIPTION_ARR;	\
/* Вспомогательный ключ для OBD_UpdateIndex */											\
	extern key_arr										*	p_static_ka;						\
/* Кэш результатов выполнения функций */													\
	extern IT_AVTree_ARG_RES_CACHE				*	pArgResCache;						\
/* Кэш объектов базы данных */																\
	extern OBJ_CACHE									*  pOBJ_CACHE;
//____________________________________________________________________________[]





#ifdef ZOOB_UTILS
	static bool b_ZOOB_UTILS = true;
#else
	static bool b_ZOOB_UTILS = false;
#endif



//______________________________________________________________________________
//                                                                            []
//` Создание основных глобальных объектов													[]
//																										[]
#define CREATE_SYSTEM_OBJECTS																	\
/* 1. Очистка файловой системы */															\
	pCClearFof						= new CClearFof(CLEAR_FILE_SYSTEM_BEFORE_START);\
/* 2. Вывод сообщений об ошибках */															\
	pServerDebug					= new CServerDebug(THIS_PROJECT_PREFIX);			\
/* 3. Монитор событий */																		\
	pEventMonitor					= new CEventMonitor;										\
/* 4. Управление файловой системой */														\
	pFileDriver						= new CFileDriver (FILE_SYSTEM_PATH_AND_NAME);	\
	if (pFileDriver->m_bError) {DELETE_SYSTEM_OBJECTS; return nRetVal;}			\
/* 5. Вспомогательный ключ для OBD_UpdateIndex */										\
	p_static_ka						= new key_arr;												\
/* 6. Управление базой объектов */															\
	if (b_ZOOB_UTILS)																				\
		pObjDriver					= new CObjDriver (SRC_LAYOUT_FILE);					\
	else																								\
		pObjDriver					= new CObjDriver;											\
/* 7. Реестр ошибок для модуля сервера */													\
	pOBServer_ERROR_DESCRIPTION_ARR	= new CPtr<OBServer_ERROR_DESCRIPTION>;	\
/* 8. Кэш результатов выполнения функций */												\
	pArgResCache					= new IT_AVTree_ARG_RES_CACHE 						\
										(&CACHE_ITEM::m_arg, CompareFunction_ARG_KEY);	\
/* 9. Кэш объектов базы данных */															\
	pOBJ_CACHE						= new OBJ_CACHE;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Удаление основных глобальных объектов													[]
//  NOTE: Объекты необходимо удалять в порядке, обратном созданию.				[]
//																										[]
#define DELETE_SYSTEM_OBJECTS																	\
/* FF. Распечатка состояния менеджера памяти */											\
	printf(MEMORY_MANAGER_REPORT(false));													\
/* 9. Кэш объектов базы данных */															\
	ifdelete (pOBJ_CACHE);																		\
/* 8. Кэш результатов выполнения функций */												\
	ifdelete	(pArgResCache);																	\
/* 7. Реестр ошибок для модуля сервера */													\
	ifdelete (pOBServer_ERROR_DESCRIPTION_ARR);											\
/* 6. Управление базой объектов */															\
	ifdelete	(pObjDriver);																		\
/* 5. Вспомогательный ключ для OBD_UpdateIndex */										\
	ifdelete	(p_static_ka);																		\
/* 4. Управление файловой системой */														\
	ifdelete	(pFileDriver);																		\
/* 3. Монитор событий */																		\
	ifdelete	(pEventMonitor);																	\
/* 2. Вывод сообщений об ошибках */															\
	ifdelete	(pServerDebug);																	\
/* 1. Очистка файловой системы */															\
	ifdelete	(pCClearFof);																		\
/* 0. Unlock базы */																				\
	OBServer_RemoveLock ();
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
