/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_MetaObject.h															[]
[] Date:          03.10.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса MetaObject								[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_MetaObject_inc_h
#define MOD_MetaObject_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
//	NOTHING

// Необходимые данному модулю классы объектов:
	#define USES_OC_User
	#define USES_OC_MetaObject
	#define USES_OC_LinkProxy

// Зависимости от других модулей:
	#define USES_MOD_Feod
	#define USES_MOD_User
	#define USES_MOD_MetaObject
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