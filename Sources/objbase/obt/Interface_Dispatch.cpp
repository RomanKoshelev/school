/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Dispatch.cpp                                    []
[] Date:            NA                                                        []
[] Author:          Alex Vershinin, Roman V. Koshelev                         []
[] Description:     Диспетчер для вызова оболочек прикладных функций.         []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________*/

#define	USES_OBServer_Interface_h
#define	USES_TEST_Interface
#include	"TEST.h"


//______________________________________________________________________________
//                                                                            []
// Диспетчер вызовов прикладных фунций                                        []
//                                                                            []
void OBServer_Interface (const char* OBServer_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)
{
// Поиск зарегистрированной функции
   FNC_BEGIN;
   {
   }
// Вызов обнаруженной функции или сообщение об ошибке.
   FNC_END;
}
//____________________________________________________________________________[]




