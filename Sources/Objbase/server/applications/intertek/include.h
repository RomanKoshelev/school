/*
________________________________________________________________________________
[] 																								   []
[] This is a part of the PROJECT: 'ZOOB/Intertek'										[]
[] ___________________________________________________________________________[]
[]																										[]
[] Name: 			include.h																	[]
[] Date: 			28.06.2000																	[]
[] Author:			Roman V. Koshelev															[]
[] Description:	Все заголовочные файлы, которые могут понадобиться				[]
[]						данному приложению														[]
[]____________________________________________________________________________[]
*/
#ifndef	INCLUDE_H
#define	INCLUDE_H

extern long SERVER_TIME_ZONE_OFFSET;


#ifdef USES_SingleObject_h
	#define	USES_OC_Registry
	#define	USES_EventMonitor_h
#endif

#include		"Lay_ObjController.h"
#include		"problem_errors.h"
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// Модули
#ifdef USES_MOD_User
	#include "./../../Modules/UserRights/MOD_User.h"
#endif

#ifdef USES_MOD_UserGroup
	#include "./../../Modules/UserRights/MOD_UserGroup.h"
#endif

#ifdef USES_MOD_Concept
	#include "./../../Modules/Concept/MOD_Concept.h"
#endif

#ifdef USES_MOD_Feod
	#include "./../../Modules/UserRights/MOD_Feod.h"
#endif

#ifdef USES_MOD_InfoDiv
	#include "./../../Modules/Publishing/MOD_InfoDiv.h"
#endif

#ifdef USES_MOD_InfoObject
	#include "./../../Modules/Publishing/MOD_InfoObject.h"
#endif

#ifdef USES_MOD_InfoSource
	#include "./../../Modules/Publishing/MOD_InfoSource.h"
#endif

#ifdef USES_MOD_WebFolder
	#include "./../../Modules/WebFileSystem/MOD_WebFolder.h"
#endif

#ifdef USES_MOD_WebFile
	#include "./../../Modules/WebFileSystem/MOD_WebFile.h"
#endif

#ifdef USES_MOD_FullTextIndex
	#include "./../../Modules/FullTextIndex/MOD_FullTextIndex.h"
#endif

#ifdef USES_MOD_Relation
	#include "./../../Modules/SemanticNet/MOD_Relation.h"
#endif

#ifdef USES_MOD_Linkage
	#include "./../../Modules/SemanticNet/MOD_Linkage.h"
#endif

#ifdef USES_MOD_MetaObject
	#include "./../../Modules/SemanticNet/MOD_MetaObject.h"
#endif

#ifdef USES_MOD_UserProfile
	#include "./../../Modules/UserProfile/MOD_UserProfile.h"
#endif
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
// Утилиты
#ifdef USES_SingleObject_h
	#include "problem_SingleObject.h"
#endif

#ifdef USES_Problem_Interface_h
	#include "Interface_Auto.h"
#endif
//----------------------------------------------------------------------------[] 



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []
[]                                                                            []
[]____________________________________________________________________________[]
*/