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
[] Description:     ������� ��� ������ � ��������� ����������� ���������		[]
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
#ifndef OB_SYSTEM_H
#define OB_SYSTEM_H

//______________________________________________________________________________
//                                                                            []
//` ��������� �� �������� ���������� �������												[]
//																										[]
#define IMPLEMENT_SYSTEM_OBJECTS																\
/* ������� �������� ������� */																\
	CClearFof									*	pCClearFof						= NULL;	\
/* ����� ��������� �� ������� */																\
	CServerDebug								*	pServerDebug					= NULL;	\
/* ������� ������� */																			\
	CEventMonitor								*	pEventMonitor					= NULL;	\
/* ���������� �������� �������� */															\
	CFileDriver									*	pFileDriver						= NULL;	\
/* ���������� ����� �������� */																\
	CObjDriver									*	pObjDriver						= NULL;	\
/* ������ ������ ��� ������ ������� */														\
	CPtr<OBServer_ERROR_DESCRIPTION>		*													\
												pOBServer_ERROR_DESCRIPTION_ARR	= NULL;	\
/* ��������������� ���� ��� OBD_UpdateIndex */											\
	key_arr										*	p_static_ka						= NULL;	\
/* ��� ����������� ���������� ������� */													\
	IT_AVTree_ARG_RES_CACHE					*	pArgResCache					= NULL;	\
/* ��� �������� ���� ������ */																\
	OBJ_CACHE									*  pOBJ_CACHE;
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ����������� ���������� �� �������� ���������� �������							[]
//																										[]
#define DECLARE_SYSTEM_OBJECTS																\
/* ������� �������� ������� */																\
	extern CClearFof									*	pCClearFof;							\
/* ����� ��������� �� ������� */																\
	extern CServerDebug								*	pServerDebug;						\
/* ������� ������� */																			\
	extern CEventMonitor								*	pEventMonitor;						\
/* ���������� �������� �������� */															\
	extern CFileDriver								*	pFileDriver;						\
/* ���������� ����� �������� */																\
	extern CObjDriver									*	pObjDriver;							\
/* ������ ������ ��� ������ ������� */														\
	extern CPtr<OBServer_ERROR_DESCRIPTION>	*	pOBServer_ERROR_DESCRIPTION_ARR;	\
/* ��������������� ���� ��� OBD_UpdateIndex */											\
	extern key_arr										*	p_static_ka;						\
/* ��� ����������� ���������� ������� */													\
	extern IT_AVTree_ARG_RES_CACHE				*	pArgResCache;						\
/* ��� �������� ���� ������ */																\
	extern OBJ_CACHE									*  pOBJ_CACHE;
//____________________________________________________________________________[]





#ifdef LAY_COMPILER_PROJECT
	static bool b_LAY_COMPILER_PROJECT = true;
#else
	static bool b_LAY_COMPILER_PROJECT = false;
#endif

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



//______________________________________________________________________________
//                                                                            []
//` �������� �������� ���������� ��������													[]
//																										[]
#define CREATE_SYSTEM_OBJECTS																	\
/* 1. ������� �������� ������� */															\
	pCClearFof						= new CClearFof(CLEAR_FILE_SYSTEM_BEFORE_START);\
/* 2. ����� ��������� �� ������� */															\
	pServerDebug					= new CServerDebug(THIS_PROJECT_PREFIX);			\
/* 3. ������� ������� */																		\
	pEventMonitor					= new CEventMonitor;										\
/* 4. ���������� �������� �������� */														\
	pFileDriver						= new CFileDriver (FILE_SYSTEM_PATH_AND_NAME);	\
/* 5. ��������������� ���� ��� OBD_UpdateIndex */										\
	p_static_ka						= new key_arr;												\
/* 6. ���������� ����� �������� */															\
	if (b_LAY_COMPILER_PROJECT)																\
		pObjDriver					= new CObjDriver (SRC_LAYOUT_FILE);					\
	else																								\
		pObjDriver					= new CObjDriver;											\
																										\
/* 7. ������ ������ ��� ������ ������� */													\
	pOBServer_ERROR_DESCRIPTION_ARR	= new CPtr<OBServer_ERROR_DESCRIPTION>;	\
/* 8. ��� ����������� ���������� ������� */												\
	pArgResCache					= new IT_AVTree_ARG_RES_CACHE 						\
										(&CACHE_ITEM::m_arg, CompareFunction_ARG_KEY);	\
/* 9. ��� �������� ���� ������ */															\
	pOBJ_CACHE						= new OBJ_CACHE;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` �������� �������� ���������� ��������													[]
//  NOTE: ������� ���������� ������� � �������, �������� ��������.				[]
//																										[]
#define DELETE_SYSTEM_OBJECTS																	\
/* FF. ���������� ��������� ��������� ������ */											\
	printf(MEMORY_MANAGER_REPORT(false));													\
/* 9. ��� �������� ���� ������ */															\
	delete	pOBJ_CACHE;																			\
				pOBJ_CACHE=NULL;																	\
/* 8. ��� ����������� ���������� ������� */												\
	delete	pArgResCache;																		\
				pArgResCache=NULL;																\
/* 7. ������ ������ ��� ������ ������� */													\
	delete	pOBServer_ERROR_DESCRIPTION_ARR;												\
				pOBServer_ERROR_DESCRIPTION_ARR=NULL;										\
/* 6. ���������� ����� �������� */															\
	delete	pObjDriver;																			\
				pObjDriver=NULL;																	\
/* 5. ��������������� ���� ��� OBD_UpdateIndex */										\
	delete	p_static_ka;																		\
				p_static_ka=NULL;																	\
/* 4. ���������� �������� �������� */														\
	delete	pFileDriver;																		\
				pFileDriver=NULL;																	\
/* 3. ������� ������� */																		\
	delete	pEventMonitor;																		\
				pEventMonitor=NULL;																\
/* 2. ����� ��������� �� ������� */															\
	delete	pServerDebug;																		\
				pServerDebug=NULL;																\
/* 1. ������� �������� ������� */															\
	delete	pCClearFof;																			\
				pCClearFof=NULL;
//____________________________________________________________________________[]





#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
