/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoDiv.inc.h															[]
[] Date:          13.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с разделами информации.										[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoDiv_inc_h
#define MOD_InfoDiv_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
 	#define USES_ArgResCache_h

// Необходимые данному модулю классы объектов:
	#define USES_OC_Concept
	#define USES_OC_InfoDiv
	#define USES_OC_InfoSource
	#define USES_OC_InfoObject
	#define USES_OC_User

// Зависимости от других модулей:
	#define USES_MOD_Feod
	#define USES_MOD_User
	#define USES_MOD_UserGroup
	#define USES_MOD_InfoDiv
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