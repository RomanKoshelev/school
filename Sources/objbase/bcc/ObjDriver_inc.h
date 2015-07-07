/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999-2000 W:Brain Software Inc.                              []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjDriver_inc.h															[]
[] Author:          Roman V. Koshelev														[]
[] Description:     Object-control layer													[]
[]____________________________________________________________________________[]
*/

#define USES_STATIC_FILE_ID_h
#define USES_key_arr_h
#define USES_FileDriver_h
#define USES_File_h
#define USES_ObjDriver_h

#include "main.h"

#define USE_CObject

extern bool PRINT_PROGRESS;

//----------------------------------------------------------------------------[] 
#define	PRINT_CREATION_PERCENT																\
	int Percent = objtype.GetIndex()*100/m_FormatArr.GetSize();						\
	if (PRINT_PROGRESS) 																			\
	{																									\
		char C='%';																					\
		printf ("\r                                                          ");\
		printf ("\r    %3d%c:  %s",Percent, C, objtype->name.c_str());			   \
	}
//----------------------------------------------------------------------------[] 

extern bool b_CREATE_INTERFACE_ONLY;

extern bool bDoDbgStop;
//----------------------------------------------------------------------------[] 
#define COMPILE_ERROR(sError)																	\
	{																									\
	if (bDoDbgStop) DBG_STOP_ASK;																\
	char SyntaxError[1024];																		\
	sprintf (SyntaxError, "Компиляция базы: '%s' (%d:%d): %s", 						\
				fileName, nLine, nPos, sError);												\
	SERVER_DEBUG_ERROR (SyntaxError);														\
	return false;																					\
	}
//----------------------------------------------------------------------------[] 


void ENCODE_STRING (size_t size, char * str);
void DECODE_STRING (size_t size, char * str);



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

