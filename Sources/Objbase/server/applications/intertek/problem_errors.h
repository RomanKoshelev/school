/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'bcc'													[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            problem_errors.h														[]
[] Date:            26.06.2000                                                []
[] Author:          Roman V. Koshelev														[]
[] Description:     Коды ошибок проблемных функций.									[]
[]____________________________________________________________________________[]
*/
#ifndef Problem_Errors_H
#define Problem_Errors_H



#include "./../../kernel/problem_errors_1.inc"
//------------------------------------ [] Коды ошибок данного проекта >>

	ERR_BadID,
	ERR_BadPasswordConfirm,
	ERR_BadLogin,
	ERR_BadPassword,
	ERR_BadPicklockPassword,

	ERR_LoginAlreadyExists,
	ERR_NameAlreadyExists,

	ERR_AccessDeny,
	ERR_InsufficientAccessLevel, // Недостаточный уровень доступа

	ERR_TooManyEnumerate,

	ERR_BadArgument,

	ERR_Concept_New_InvalidTypeInfo,
	ERR_Concept_New_InvalidParentID,
	ERR_Concept_New_RootAlreadyExists,

	ERR_BadName,

	ERR_RelationVersionMismatch,

//------------------------------------ [] << Коды ошибок данного проекта
#include "./../../kernel/problem_errors_2.inc"
#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/