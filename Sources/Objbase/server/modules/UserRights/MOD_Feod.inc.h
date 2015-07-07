/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Feod.inc.h																[]
[] Date:          07.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с зонами доступа, концептами ветви {Concept.Feod})	[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_Feod_inc_h
#define MOD_Feod_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
	#define USES_PicklockPassword_h
	#define USES_SingleObject_h
	

// Необходимые данному модулю классы объектов:
	#define USES_OC_User
	#define USES_OC_UserGroup
	#define USES_OC_Concept

// Зависимости от других модулей:
	#define USES_MOD_Feod
	#define USES_MOD_User
	#define USES_MOD_UserGroup
	#define USES_MOD_Concept
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]

#include "./../../kernel/config.h"
#include MOD_PATH_INCLUDE_H

typedef OC_Concept			OC_Feod;
#define OBJ_CLASS_ID_Feod	OBJ_CLASS_ID_Concept


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/