/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoObject.inc.h														[]
[] Date:          16.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с информационными объектами.									[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoObject_inc_h
#define MOD_InfoObject_inc_h


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
	#define USES_ArgResCache_h

// Необходимые данному модулю классы объектов:
	#define USES_OC_InfoDiv
	#define USES_OC_InfoObject
	#define USES_OC_LinkProxy

// Зависимости от других модулей:
	#define USES_MOD_Feod
	#define USES_MOD_User
	#define USES_MOD_Linkage
	#define USES_MOD_InfoDiv
	#define USES_MOD_InfoObject
	#define USES_MOD_InfoSource
	#define USES_MOD_FullTextIndex
	#define USES_MOD_UserProfile
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