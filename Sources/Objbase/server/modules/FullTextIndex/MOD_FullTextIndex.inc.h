/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.inc.h													[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Полнотекстовая индексация и поиск с учётом морфологии			[]
[]						Описание всего необходимого.											[]
[]____________________________________________________________________________[]
*/

#ifndef MOD_FullTextIndex_inc_h
#define MOD_FullTextIndex_inc_h

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>[]
// Зависимости от утилит:
	#define USES_ArgResCache_h
	#define USES_stopwatch_h

// Необходимые данному модулю классы объектов:
	#define USES_OC_Text
	#define USES_OC_MorphologicRule
	#define USES_OC_SearchItem
	#define USES_OC_StopWord
	#define USES_OC_WordNibbleABC

// Зависимости от других модулей:
	#define USES_MOD_User
	#define USES_MOD_FullTextIndex
	#define USES_MOD_Feod
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