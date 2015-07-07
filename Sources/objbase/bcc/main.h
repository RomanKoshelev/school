/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            main.h																		[]
[] Date:            01/22/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Основной заголовочный файл. 										[]
[]						  Все остальные подключаются через него							[]
[]____________________________________________________________________________[]
*/
#ifndef MAIN_H
#define MAIN_H


//----------------------------------------------------------------------------[]
#include "config.h"
//----------------------------------------------------------------------------[] 
#ifdef USES_URL_h
	#define USES_string_h
#endif

#ifdef USES_UserAgent_h
	#define USES_string_h
#endif

#ifdef Lay_ObjController_h
	#define Lay_Stubs_H
#endif

#ifdef Lay_Stubs_H
	#define USES_key_arr_h
	#define USES_File_h
	#define USES_ObjDriver_h
#endif

#ifdef USES_ObjDriver_h
	#define USES_STATIC_FILE_ID_h
	#define USES_File_h
#endif

#ifdef USES_key_arr_h
	#define USES_string_h
	#define USES_AVTree_h
#endif

#ifdef USES_EventMonitor_h
	#define USES_string_h
	#define USES_AVTree_h
#endif

#ifdef USES_OB_System_h
	#define USES_OBServer_Interface_h
	#define USES_CACHE_h
#endif

#ifdef USES_CACHE_h
	#define USES_OBD_h
#endif

#ifdef USES_OBServer_Interface_h
	#define USES_string_h
#endif

#ifdef USES_string_h
	#define USES_Ptr_h
#endif

#ifdef USES_ArgResCache_h
	#define USES_Ptr_h
	#define USES_AVTree_h
	#define USES_OB_System_h
#endif

#ifdef USES_File_h
	#define USES_FileDriver_h
	#define USES_Ptr_h
	#define USES_string_h
#endif

#ifdef USES_key_arr_h
	#define USES_AVTree_h
#endif

//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
#ifdef USES_ALL_H
	#define USES_STATIC_FILE_ID_h
	#define USES_MemoryManager_h
	#define USES_OB_System_h
	#define USES_Ptr_h
	#define USES_string_h
	#define USES_AVTree_h
	#define USES_EventMonitor_h
	#define USES_FileDriver_h
	#define USES_File_h
	#define USES_key_arr_h
	#define USES_ObjDriver_h
	#define USES_ArgResCache_h
	#define USES_OBServer_Interface_h
	#define USES_URL_h
	#define USES_UserAgent_h
	#define USES_CACHE_h
	#define USES_OBD_h
#endif
//----------------------------------------------------------------------------[] 



//______________________________________________________________________________
//                                                                            []
//` Алиасы основных глобальных объектов													[]
//																										[]
#define theCClearFof							(*pCClearFof)
#define theServerDebug						(*pServerDebug)
#define theEventMonitor						(*pEventMonitor)
#define theFileDriver						(*pFileDriver)
#define theObjDriver							(*pObjDriver)
#define theOBServer_ERROR_DESCRIPTION_ARR	(*pOBServer_ERROR_DESCRIPTION_ARR)
#define theArgResCache						(*pArgResCache)
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Стандартные заголовочные файлы															[]
//                                                                            []
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>


typedef unsigned long identifier;

#define	MAX_OBJECT_ID			((identifier)0xFFFFFFFF)
#define	NA							MAX_OBJECT_ID
#define	UNKNOWN					MAX_OBJECT_ID



//----------------------------------------------------------------------------[] 
#define DECLARE_COPY_CONSTRUCTORS_BEGIN(cl)												\
	cl (cl& from)																					\
	{																									\
		CopyFrom (from);																			\
	}																									\
	cl& operator = (cl& from)																	\
	{																									\
		return CopyFrom (from);																	\
	}																									\
	cl& CopyFrom (cl& from)																		\
	{
//----------------------------------------------------------------------------[] 
#define DECLARE_COPY_CONSTRUCTORS_END														\
		return *this;																				\
	}
//----------------------------------------------------------------------------[] 
#define CC_COPY(fld)																				\
	fld=from.fld;
//----------------------------------------------------------------------------[] 



#include "MemoryManager.h"

#ifdef USES_OB_System_h
	#include "OB_System.h"
#endif

#include "ServerDebug.h"

#ifdef WIN32
	#include <io.h>
	#include <windows.h>
	#include <process.h>
	#include <conio.h>
#else
	#include <unistd.h>
#endif

#ifndef WIN32
	#define rand random
	#define srand srandom
	typedef unsigned int DWORD;
#endif

#ifdef WIN32
	#pragma warning(disable:4786)
	#pragma warning(disable:4700)
	#pragma warning(disable:4284)
#endif


#ifndef BOOL
	#define BOOL bool
#endif
#ifndef TRUE
	#define TRUE true
#endif
#ifndef FALSE
	#define FALSE false
#endif

#ifndef BYTE
	typedef unsigned char BYTE;
#endif

typedef bool BIT;

#ifndef byte
	typedef unsigned char byte;
#endif

typedef bool bit;

#ifndef max
	#define max(x,y)	( ((x)>(y)) ? (x) : (y) )
#endif
#ifndef min
	#define min(x,y)	( ((x)<(y)) ? (x) : (y) )
#endif


#define VAL_IN_RANGE(v,m1,m2)  (((m1)<=(v)) && ((v)<=(m2)))
#define VAL_APPROX_EQ(v1,v2,d) VAL_IN_RANGE(v1,v2-d,v2+d)

typedef byte * pbyte;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Заголовочные файлы проекта ObjBase														[]
//                                                                            []

#ifdef USES_STATIC_FILE_ID_h
	#include "STATIC_FILE_ID.h"
#endif

#ifdef USES_Ptr_h
	#include "Ptr.h"
#endif

#ifdef USES_string_h
	#include "string.h"
#endif

#ifdef USES_AVTree_h
	#include "AVTree.h"
#endif

#ifdef USES_EventMonitor_h
	#include "EventMonitor.h"
#endif

#ifdef USES_FileDriver_h
	#include "FileDriver.h"
#endif

#ifdef USES_File_h
	#include "File.h"
#endif

#ifdef USES_key_arr_h
	#include "key_arr.h"
#endif

#ifdef USES_ObjDriver_h
	#include "ObjDriver.h"
#endif

#ifdef USES_Ptr_h
	typedef CPtr<identifier>	identifier_arr;
	typedef CPtr<int>				int_arr;
	typedef CPtr<byte>			byte_arr;
	typedef CPtr<bool>			bool_arr;
	typedef CPtr<float>			float_arr;
	typedef CPtr<string>			string_arr;
	typedef CPtr<time_t>			time_t_arr;
#endif

#ifdef USES_ArgResCache_h
	#include "ArgResCache.h"
	extern IT_AVTree_ARG_RES_CACHE				*	pArgResCache;
#endif

#ifdef USES_OBServer_Interface_h
	#include "OBServer_Interface.h"
#endif

#ifdef USES_URL_h
	#include "URL.h"
#endif

#ifdef USES_UserAgent_h
	#include "UserAgent.h"
#endif
//#ifdef USES_OB_System_h
//	DECLARE_SYSTEM_OBJECTS;
//#endif

#ifdef USES_OBD_h
	#include "OBD.h"
#endif

#ifdef USES_CACHE_h
	#include "CACHE.h"
#endif

void RunTest (void);

extern	time_t	TIME_NULL;

extern	bool		CLEAR_FILE_SYSTEM_BEFORE_START;
extern	char *	FILE_SYSTEM_PATH_AND_NAME;
extern	char *	THIS_PROJECT_PREFIX;
//____________________________________________________________________________[]






#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

