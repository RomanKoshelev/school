/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Linkage.inc.h															[]
[] Date:          18.09.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с семантическими связями										[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_Linkage_inc_h
#define MOD_Linkage_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
//	NOTHING

// Необходимые данному модулю классы объектов:
	#define USES_OC_Relation
	#define USES_OC_Linkage
	#define USES_OC_LinkProxy
	#define USES_OC_User

// Зависимости от других модулей:
	#define USES_MOD_Feod
	#define USES_MOD_User
	#define USES_MOD_Relation
	#define USES_MOD_Linkage
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