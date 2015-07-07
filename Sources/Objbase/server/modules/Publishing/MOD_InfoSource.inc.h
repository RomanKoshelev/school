/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoSource.h															[]
[] Date:          21.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса InfoSource								[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoSource_inc_h
#define MOD_InfoSource_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
//	NOTHING

// Необходимые данному модулю классы объектов:
	#define USES_OC_InfoDiv
	#define USES_OC_InfoObject
	#define USES_OC_InfoSource

// Зависимости от других модулей:
	#define USES_MOD_User
	#define USES_MOD_Feod
	#define USES_MOD_InfoDiv
	#define USES_MOD_InfoSource
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]

#include "./../../kernel/config.h"
#include MOD_PATH_INCLUDE_H


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/