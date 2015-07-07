/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            problem_main.cpp                                          []
[] Date:            28.06.2000                                                []
[] Author:          Roman V. Koshelev														[]
[]____________________________________________________________________________*/

#define	USES_SingleObject_h
#define	USES_ALL_H

#include "include.h"
#include "../../kernel/problem_main_1.inc"

//----------------------------------------------------------------------------[] 
#ifdef WIN32
	bool CLEAR_FILE_SYSTEM_BEFORE_START	= false;			// ���� true -- ������� �������� �������.
#else
	bool CLEAR_FILE_SYSTEM_BEFORE_START	= false;			// ���� true -- ������� �������� �������.
#endif

char * FILE_SYSTEM_PATH_AND_NAME		= "files/IT";		// ���� � �������� ������� � � ��������.
char * THIS_PROJECT_PREFIX		      = "IT";	         // ������� (������������) �������� �������.
//----------------------------------------------------------------------------[] 

#include "../../kernel/problem_main_2.inc"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

