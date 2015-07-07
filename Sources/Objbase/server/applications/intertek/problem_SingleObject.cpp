/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'														[]
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            problem_SingleObject.cpp												[]
[] Date:            28.06.2000                                                []
[] Author:			  Roman V. Koshelev														[]
[] Description:	  Реализация главного объекта SingleObject						[]
[]____________________________________________________________________________[]
*/

#define	USES_ObjCache_h
#define	USES_SingleObject_h
#define	USES_OBServer_Interface_h

#define	USES_OC_ALL

#define	USES_MOD_User
#define	USES_MOD_Concept
#define	USES_MOD_InfoObject
#define	USES_MOD_InfoSource
#define	USES_MOD_FullTextIndex
#define	USES_MOD_MetaObject

#include "include.h"
#include "../../kernel/problem_SingleObject_1.inc"


fp_MOD_GET_OBJECT_NAME				MOD_GET_OBJECT_NAME_FUNCTION_ARR				[MAX_FA_SIZE];
fp_MOD_GET_OBJECT_DESCRIPTION		MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR	[MAX_FA_SIZE];
fp_MOD_CHECK_ACCESS					MOD_CHECK_ACCESS_FUNCTION_ARR					[MAX_FA_SIZE];
fp_MOD_CHECK_PLACEMENT				MOD_CHECK_PLACEMENT_FUNCTION_ARR				[MAX_FA_SIZE];


//----------------------------------------------------------------------------[] 
// ИНИЦИАЛИЗИРУЮЩИЕ МАССИВЫ
//----------------------------------------------------------------------------[] 
extern GROUP_INI			GROUP_INI_ARR[];
extern int					GROUP_INI_NUM;

extern USER_INI			USER_INI_ARR[];
extern int					USER_INI_NUM;

extern INFOSOURCE_INI	INFOSOURCE_INI_ARR[];
extern int					INFOSOURCE_INI_NUM;
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//` Конструктор																					[]
//                                                                            []
SingleObject::SingleObject()
{
	DEBUG_STACK_NAME (SingleObject_SingleObject);

	m_Name = "SingleObject";
	SERVER_DEBUG_TEXT ("Конструктор SingleObject запущен.");
	m_pOC_Registry = new OC_Registry;
	SERVER_DEBUG_ASSERT (m_pOC_Registry != NULL,
		"BX_SingleObject::BX_SingleObject(): error allocating space for OC_Registry.");

	//----------------------------------------------------------------------------[] 
	bzero (MOD_GET_OBJECT_NAME_FUNCTION_ARR,			MAX_FA_SIZE*sizeof (MOD_GET_OBJECT_NAME_FUNCTION_ARR[0]));
	bzero (MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR, MAX_FA_SIZE*sizeof (MOD_GET_OBJECT_NAME_FUNCTION_ARR[0]));
	bzero (MOD_CHECK_ACCESS_FUNCTION_ARR,				MAX_FA_SIZE*sizeof (MOD_GET_OBJECT_NAME_FUNCTION_ARR[0]));
	bzero (MOD_CHECK_PLACEMENT_FUNCTION_ARR,			MAX_FA_SIZE*sizeof (MOD_GET_OBJECT_NAME_FUNCTION_ARR[0]));

	MOD_GET_OBJECT_NAME_FUNCTION_ARR				[OBJ_CLASS_ID_InfoObject]	=	MOD_GET_OBJECT_NAME_InfoObject;
	MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR	[OBJ_CLASS_ID_InfoObject]	=  MOD_GET_OBJECT_DESCRIPTION_InfoObject;
	MOD_CHECK_ACCESS_FUNCTION_ARR					[OBJ_CLASS_ID_InfoObject]	= 	MOD_CHECK_ACCESS_InfoObject;
	MOD_CHECK_PLACEMENT_FUNCTION_ARR				[OBJ_CLASS_ID_InfoObject]	= 	MOD_CHECK_PLACEMENT_InfoObject;

	MOD_GET_OBJECT_NAME_FUNCTION_ARR				[OBJ_CLASS_ID_MetaObject]	=	MOD_GET_OBJECT_NAME_MetaObject;
	MOD_CHECK_ACCESS_FUNCTION_ARR					[OBJ_CLASS_ID_MetaObject]	= 	MOD_CHECK_ACCESS_MetaObject;
	//----------------------------------------------------------------------------[] 


	SERVER_TIME_ZONE_OFFSET = GetTZOffset ();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Инициализация																					[]
//                                                                            []
bool SingleObject::Create (int argc, char *argv[])
{
	DEBUG_STACK_NAME (SingleObject_Create);

	RegisterErrorDescriptions	();

	if (oc_reg.m_NeedInitiate==true)
	{
		printf ("\n[INI START]");

	// Система запускается в режиме импорта данных
		bool	bImport = (argc>=2) &&  (strcmp ("/import", argv[1])==0);
		if (bImport) IGNORE_AUTHORIZATION = true;


	// Пароль главного пользователя
		char rootPassword   [1024]="root";
		char scriptPassword [1024]="script";
		if (argc>=2) strcpy (rootPassword,		argv[1]);
		if (argc>=3) strcpy (scriptPassword,	argv[2]);


	//----------------------------------------------------------------------------[] 
	// Компилируем концепты
		printf("\n  Concepts");
		ConceptCompiler (bImport? "./../concepts.min.h" : "./../concepts.h");
	//----------------------------------------------------------------------------[] 
	// Создаём предопределённые группы и пользователей
		if (!bImport)
		{
			printf ("\n  Groups and users");
			if (!InitializeSystemRights (rootPassword, scriptPassword, GROUP_INI_ARR, GROUP_INI_NUM, USER_INI_ARR, USER_INI_NUM))
			{
				return false;
			}
		}
	//----------------------------------------------------------------------------[] 
	// Создаём тестовые источники данных
		if (!bImport)
		{
			printf ("\n  Info sources");
			if (!InitializeInfoSources (rootPassword, INFOSOURCE_INI_ARR, INFOSOURCE_INI_NUM))
			{
				return false;
			}
		}
	//----------------------------------------------------------------------------[] 
	// Инициализация модуля поиска и индексирования
		printf ("\n  Search system");
		if (!InitializeSearchSystem ("ru", false))
		{
			return false;
		}
	//----------------------------------------------------------------------------[] 


		printf ("\n[INI DONE]\n\n");
	}

	oc_reg.m_NeedInitiate=false;
	oc_reg.Save();

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Деструктор																						[]
//                                                                            []
SingleObject::~SingleObject()
{
	DEBUG_STACK_NAME (SingleObject_DESTRUCTOR);

	delete m_pOC_Registry;
	m_pOC_Registry = NULL;

	SERVER_DEBUG_TEXT ("Драйвер проблемной области завершил работу");
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Обработка таймера																			[]
//                                                                            []
void SingleObject::OnTimer (void)
{
	DEBUG_STACK_NAME (SingleObject_OnTimer);

//----------------------------[] Чистка кэша
	the_OBJ_CACHE.CleanOut ();
//----------------------------[] Чистка кэша

	return;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` Обработка событий																			[]
//                                                                            []
bool SingleObject::OnEvent (const EM_Event& Event)
{
	DEBUG_STACK_NAME (SingleObject_OnEvent);

	(void) Event;
	return true;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` RegisterErrorDescriptions                                                 []                         
//                                                                            []
void SingleObject::RegisterErrorDescriptions ()
{
	DEBUG_STACK_NAME (SingleObject_RegisterErrorDescriptions);

// Всё в порядке
	REGISTER_ERROR_DESCRIPTION (ERR_OK);
// Сработал ASSERT
	REGISTER_ERROR_DESCRIPTION (ERR_SYSTEM_ERROR);
// Неопознанный запрос
	REGISTER_ERROR_DESCRIPTION (ERR_OBServer_UnsupportedFunctionCall);
// Выходной буфер переполнен
	REGISTER_ERROR_DESCRIPTION (ERR_OBServer_OutputBufferOverflow);
// Функция ещё не реализована
	REGISTER_ERROR_DESCRIPTION (ERR_FunctionNotImplemented);


// Диагностика ошибок проблемной области
	REGISTER_ERROR_DESCRIPTION (ERR_BadID);
	REGISTER_ERROR_DESCRIPTION (ERR_BadPasswordConfirm);
	REGISTER_ERROR_DESCRIPTION (ERR_BadLogin);
	REGISTER_ERROR_DESCRIPTION (ERR_BadPassword);
	REGISTER_ERROR_DESCRIPTION (ERR_BadPicklockPassword);
	REGISTER_ERROR_DESCRIPTION (ERR_LoginAlreadyExists);
	REGISTER_ERROR_DESCRIPTION (ERR_NameAlreadyExists);
	REGISTER_ERROR_DESCRIPTION (ERR_AccessDeny);
	REGISTER_ERROR_DESCRIPTION (ERR_InsufficientAccessLevel);
	REGISTER_ERROR_DESCRIPTION (ERR_TooManyEnumerate);
	REGISTER_ERROR_DESCRIPTION (ERR_BadArgument);
	REGISTER_ERROR_DESCRIPTION (ERR_Concept_New_InvalidTypeInfo);
	REGISTER_ERROR_DESCRIPTION (ERR_Concept_New_InvalidParentID);
	REGISTER_ERROR_DESCRIPTION (ERR_Concept_New_RootAlreadyExists);
}
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/