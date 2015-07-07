/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBServer_Interface.h                                      []
[] Date:            9/1/99                                                    []
[] Author:          Alex Vershinin, Roman V. Koshelev                         []
[] Description:     Интерфейс с внешними модулями                             []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
#ifndef OBServer_Interface_H
#define OBServer_Interface_H




//=====================================[]
// Коды ошибок
//
#define 	OBServer_OK									0
#define 	OBServer_UnsupportedFunctionCall		-1
#define 	OBServer_OutputBufferOverflow			-2
#define 	OBServer_SYSTEM_ERROR					-3
//=====================================[]


// Буфер для передачи аргументов серверной части.
extern	char OutStreamBuffer[];
//=====================================[]

//=====================================[]
// Функции из OBServer.cpp
//
int		OBServer_MainLoop		();
bool		SetDBLockFlag			();
void		OBServer_RemoveLock	();
//=====================================[]
// Функции из Interface_*.*
//
void OBServer_Interface				(const char*,		const char*, const char*, void**);
void OBServer_Interface_Free		(void ** ppData);
//=====================================[]


bool GetArg(const char * inStr, bool&					argValue, const char* argName);
bool GetArg(const char * inStr, byte&					argValue, const char* argName);
bool GetArg(const char * inStr, int&					argValue, const char* argName);
bool GetArg(const char * inStr, time_t&				argValue, const char* argName);
bool GetArg(const char * inStr, identifier&			argValue, const char* argName);
bool GetArg(const char * inStr, float&					argValue, const char* argName);
bool GetArg(const char * inStr, string&				argValue, const char* argName);

bool GetArg(const char * inStr, bool_arr&				argValue, const char* argName);
bool GetArg(const char * inStr, byte_arr&				argValue, const char* argName);
bool GetArg(const char * inStr, int_arr&				argValue, const char* argName);
bool GetArg(const char * inStr, identifier_arr&		argValue, const char* argName);
bool GetArg(const char * inStr, float_arr&			argValue, const char* argName);
bool GetArg(const char * inStr, string_arr&			argValue, const char* argName);

bool PackArg(const char * outStr, bool&				argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, byte&				argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, int&					argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, time_t&				argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, identifier&		argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, float&				argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, string&				argValue, const char* argName, int& BufferPos);

bool PackArg(const char * outStr, bool_arr&			argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, byte_arr&			argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, int_arr&			argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, identifier_arr&	argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, float_arr&			argValue, const char* argName, int& BufferPos);
bool PackArg(const char * outStr, string_arr&		argValue, const char* argName, int& BufferPos);

//----------------------------------------------------------------------------[] 

struct OBServer_ERROR_DESCRIPTION
{
	int		nEnum;
	string	sDesc;
};

#define theOBServer_ERROR_DESCRIPTION_ARR (*pOBServer_ERROR_DESCRIPTION_ARR)
extern CPtr<OBServer_ERROR_DESCRIPTION> *pOBServer_ERROR_DESCRIPTION_ARR;

bool OBServer_PackErrorDescription(int result, int& BufferPos);

//______________________________________________________________________________
//                                                                            []
//` REGISTER_ERROR_DESCRIPTION                                                []                          
//                                                                            []
#define REGISTER_ERROR_DESCRIPTION(err)													\
{																										\
	OBServer_ERROR_DESCRIPTION err_desc;													\
	err_desc.nEnum = err;																		\
	err_desc.sDesc = #err;																		\
	theOBServer_ERROR_DESCRIPTION_ARR.Add (err_desc);									\
}
//----------------------------------------------------------------------------[]
const char * GET_ERROR_DESCRIPTION (int nErr);
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` FunctionCheck_BEGIN                                                       []            
//                                                                            []
#ifndef	HELPER_DISABLED

#define FNC_BEGIN																					\
	if (ppData == NULL) return;																\
																										\
	*ppData = NULL;																				\
																										\
	static bool			b_ALL_FUNCTIONS_REGISTERED=false;								\
	static string_arr REGISTERED_FUNCTIONS;												\
	static string_arr REGISTERED_FUNCTIONS_DESCRIPTION;								\
	static CPtr<FUNCTION_ARGS> REGISTERED_FUNCTIONS_ARGS;								\
	void  (* pOBServer_PROC)(const char*, const char*, void**) = NULL

//----------------------------------------------------------------------------[]
#else
#define FNC_BEGIN																					\
	if (ppData == NULL) return;																\
																										\
	*ppData = NULL;																				\
																										\
	void  (* pOBServer_PROC)(const char*, const char*, void**) = NULL;

#endif
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` FunctionCheck                                                             []            
//                                                                            []
#ifndef	HELPER_DISABLED
#define FNC(func_name,func_desc)																\
	if (b_ALL_FUNCTIONS_REGISTERED==false)													\
	{																									\
		REGISTERED_FUNCTIONS.Add (string (#func_name));									\
		REGISTERED_FUNCTIONS_DESCRIPTION.Add (string (func_desc));					\
		FUNCTION_ARGS fargs;																		\
		REGISTERED_FUNCTIONS_ARGS.Add (fargs);												\
	}																									\
	if (pOBServer_PROC==NULL && strcmp(OBServer_Function, #func_name)==0)						\
	{																									\
      strcpy (theServerDebug.m_Entrance, #func_name);                         \
      pOBServer_PROC = OBServer_##func_name;															\
	}
//----------------------------------------------------------------------------[]
#else
#define FNC(func_name,func_desc)																\
	if (pOBServer_PROC==NULL && strcmp(OBServer_Function, #func_name)==0)						\
	{																									\
      strcpy (theServerDebug.m_Entrance, #func_name);                         \
      pOBServer_PROC = OBServer_##func_name;															\
	}
#endif
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` FNC_ARG                                                                   []       
//                                                                            []
#ifndef	HELPER_DISABLED
#define SERVER_FNC_ARG(PR_OBJ, argName, ArgDescription, InOut)                \
	if (b_ALL_FUNCTIONS_REGISTERED==false)												   \
	{																								   \
		string farg_n	= #argName;															   \
		string farg_d	= ArgDescription;													   \
																									   \
		PR_OBJ##_Args	  args;																   \
		string farg_t  = GET_FUNCTION_ARG_TYPE(args.argName);						   \
		int nL = REGISTERED_FUNCTIONS_ARGS.Size()-1;									   \
		if (nL>=0)																				   \
		{																							   \
			REGISTERED_FUNCTIONS_ARGS[nL].##InOut##Args_Name.Add(farg_n);		   \
			REGISTERED_FUNCTIONS_ARGS[nL].##InOut##Args_Type.Add(farg_t);		   \
			REGISTERED_FUNCTIONS_ARGS[nL].##InOut##Args_Description.Add(farg_d);	\
		}																							   \
	}
//----------------------------------------------------------------------------[]
#else
#define FNC_ARG(PR_OBJ, argName, ArgDescription, InOut)
#endif
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` FNC_IN FNC_OUT                                                            []      
//                                                                            []
#define FNC_IN(PR_OBJ, argName, ArgDescription)											\
	FNC_ARG(PR_OBJ, argName, ArgDescription, In);
//----------------------------------------------------------------------------[] 
#define FNC_OUT(PR_OBJ, argName, ArgDescription)										\
	FNC_ARG(PR_OBJ, argName, ArgDescription, Out);
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` FunctionCheck_ERROR		                                                   []            
//                                                                            []
#define FNC_ERROR																					\
	OBServer_WRAPPER_START;																			\
/* Ошибка вызова функции	*/																	\
	int OBServer_result = OBServer_UnsupportedFunctionCall;										\
	if (BufferPos != 0)																			\
	{																									\
		BufferPos = 0;																				\
	}																									\
	OBServer_WRAPPER_END;
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` AVOID_WARNING_ON_ARGS                                                     []                     
//                                                                            []
#define AVOID_WARNING_ON_ARGS																	\
(void) inStr;																						\
(void) outStr;
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` FunctionCheck_END		                                                   []            
//                                                                            []
#ifndef	HELPER_DISABLED

void OBServer_Help					(void ** ppData, string_arr& FnNames, string_arr& FnDesc, CPtr<FUNCTION_ARGS>& REGISTERED_FUNCTIONS_ARGS, const char * InputArgs);

#define	FNC_END																					\
	b_ALL_FUNCTIONS_REGISTERED = true;														\
																										\
	if ((strcmp(OBServer_Function, "?"   ) == 0)  ||									\
		 (strcmp(OBServer_Function, "Help") == 0)  ||									\
		 (strcmp(OBServer_Function, "HELP") == 0)  ||									\
		 (strcmp(OBServer_Function, "help") == 0)  )										\
	{																									\
		OBServer_Help(ppData, 																	\
					REGISTERED_FUNCTIONS,														\
					REGISTERED_FUNCTIONS_DESCRIPTION,										\
					REGISTERED_FUNCTIONS_ARGS,													\
					InputArgs																		\
					);																					\
      theServerDebug.m_Entrance[0]=0;                                         \
		return;																						\
	}																									\
																										\
	if (pOBServer_PROC)																			\
	{																									\
		(*pOBServer_PROC)(InputArgs, OutputArgs, ppData);								\
      theServerDebug.m_Entrance[0]=0;                                         \
		return;																						\
	}																									\
   theServerDebug.m_Entrance[0]=0;                                            \
                                                                              \
/* Ошибка вызова -- функция не обнаружена */												\
	FNC_ERROR;
//----------------------------------------------------------------------------[]
#else
#define	FNC_END																					\
	if (pOBServer_PROC != NULL)																\
	{																									\
		(*pOBServer_PROC)(InputArgs, OutputArgs, ppData);								\
      theServerDebug.m_Entrance[0]=0;                                         \
		return;																						\
	}																									\
   theServerDebug.m_Entrance[0]=0;                                            \
                                                                              \
/* Ошибка вызова -- функция не обнаружена */												\
	FNC_ERROR;
#endif
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` PACK_ARG                                                                  []        
//                                                                            []
// Добавить в байтовый массив ReturnStream значение поля val из структуры
// OBServer_Args, если имя этого поля встречается в строке outStr.
#define PACK_ARG(val)	PackArg(outStr, OBServer_args.##val, #val, BufferPos)
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` GET_ARG                                                                   []       
//                                                                            []
// Получить в поле val структуры OBServer_Args одноимённое значение из строки inStr.
#define GET_ARG(val)		GetArg(inStr,  OBServer_args.##val, #val)
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` GET_ARG_START                                                             []             
//                                                                            []
// Установить указатель pName на первый символ после 2argName
#define GET_ARG_START																			\
/* Сформируем в argValueStrBuffer шаблон поиска имени:			*/					\
	int argNameLen = strlen(argName);														\
	if (argNameLen > MAX_ARG_NAME_LENGTH+2) 												\
	{																									\
		char SSS[MAX_ARG_NAME_LENGTH + 1];													\
		memcmp (SSS, argName, MAX_ARG_NAME_LENGTH);										\
		SSS[MAX_ARG_NAME_LENGTH] = 0;															\
		/* Хотелось бы узнать IP с которого пришла ошибка !!!		*/					\
		SERVER_DEBUG_ERROR_2 ("GET_ARG_START: Ошибка -- неизвестное большое имя аргумента %s IP = %s", SSS, "???");\
		return false;																				\
	}																									\
																										\
	argValueStrBuffer[0] = ARG_NAME_HEADER_CHAR;											\
	strcpy(&argValueStrBuffer[1], argName);												\
	argValueStrBuffer[argNameLen + 1] = 0;													\
/* Ищем шаблон:																*/					\
	char * pName = (char*)inStr;																\
	while ((pName = strstr(pName, argValueStrBuffer)) != NULL)						\
	{																									\
		pName += argNameLen + 1;																\
		if (isalnum(*pName) == 0)																\
			break;																					\
	}																									\
	if (pName==NULL) return false
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` PACK_ARG_START                                                            []              
//                                                                            []
// Установить указатель pName на первый символ после 2argName
#define PACK_ARG_START																			\
/*	Проверка на переполненность выходного буффера:					*/					\
	if (BufferPos == -1) return false;														\
/* Сформируем в argValueStrBuffer шаблон поиска имени:			*/					\
	int argNameLen = strlen(argName);														\
	if (argNameLen > MAX_ARG_NAME_LENGTH+2) 												\
	{																									\
		char SSS[MAX_ARG_NAME_LENGTH + 1];													\
		memcmp (SSS, argName, MAX_ARG_NAME_LENGTH);										\
		SSS[MAX_ARG_NAME_LENGTH] = 0;															\
	/* Хотелось бы узнать IP с которого пришла ошибка !!!			*/					\
		SERVER_DEBUG_ERROR_2 ("PACK_ARG_START: Ошибка -- неизвестное большое имя аргумента %s IP = %s", SSS, "???");\
		return false;																				\
	}																									\
																										\
	argValueStrBuffer[0] = ARG_NAME_HEADER_CHAR;											\
	strcpy(&argValueStrBuffer[1], argName);												\
	argValueStrBuffer[argNameLen+1] = 0;													\
/* Ищем шаблон:																*/					\
	char * pName = (char*)outStr;																\
	while ((pName = strstr(pName, argValueStrBuffer)) != NULL)						\
	{																									\
		pName += argNameLen + 1;																\
		if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))						\
			break;																					\
	}																									\
	if (pName==NULL) return false
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBServer_WRAPPER_START                                                         []                 
//                                                                            []
#define OBServer_WRAPPER_START																		\
	int BufferPos = 0
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBServer_WRAPPER_END                                                           []               
//                                                                            []
#define OBServer_WRAPPER_END																			\
/* Если вызов был неуспешным, упакуем в выходной поток описание ошибки:	*/		\
	else																								\
	{																									\
	/*	Проверка на переполнение буфера:												*/		\
		if (BufferPos == -1)	{																	\
				OBServer_result = OBServer_OutputBufferOverflow;										\
		}																								\
		BufferPos = 0;																				\
		OBServer_PackErrorDescription(OBServer_result, BufferPos);								\
	}																									\
																										\
/* Выделить память и скопировать туда выходной поток: 						*/		\
	*ppData = new byte [BufferPos + sizeof(int) + sizeof(int)];						\
	SERVER_DEBUG_ASSERT (*ppData != NULL,													\
		 "OBServer_WRAPPER_END: Out of memory.");												\
/* Копируем из буфера:																	*/		\
	memcpy (																							\
		(void*)(((pbyte)(*ppData)) + sizeof(int) + sizeof(int)), 					\
		OutStreamBuffer,																			\
		BufferPos);																					\
	((int *) (*ppData)) [0] = (int)(BufferPos+sizeof(int)+sizeof(int));			\
	((int *) (*ppData)) [1] = (int)OBServer_result;											\
	return
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` PUT_TO_STREAM_BUFFER                                                      []                    
//                                                                            []
#define PUT_TO_STREAM_BUFFER																	\
{																										\
	int BlockLength = strlen(argValueStrBuffer);											\
	/* Если буфера не хватает из-за его переполненности, то возвратим ошибку */\
	if ((BufferPos + BlockLength) > (OUT_STREAM_BUFFER_SIZE - 1))					\
	{																									\
		SERVER_DEBUG_ERROR_2(																	\
			"PUT_TO_STREAM_BUFFER: <b>OUTPUT BUFFER OVERFLOW!</b> at argument '%s' with output string = '%s'.",\
			argName, outStr);																		\
																										\
		BufferPos = -1;																			\
		return false;																				\
	}																									\
	/* Запишем в буфер (вместе с нулём)													 */\
	memcpy(&OutStreamBuffer[BufferPos], argValueStrBuffer, BlockLength + 1);	\
	BufferPos += BlockLength;																	\
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Обработка запроса на запуск/останов базы.                                 []                                         
//                                                                            []
#ifdef WIN32																						
	#define CHECK_START_STOP																	
//----------------------------------------------------------------------------[]
#else																									
	#define CHECK_START_STOP																	\
/* Обработка повторного запуска базы: */													\
	if(SetDBLockFlag())																			\
	{																									\
		printf("\n%s: Daemon already in use!\n", THIS_PROJECT_PREFIX);				\
		return 1;																					\
	}
#endif
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Установка функции-обработчика секундного таймера.                         []                                                 
//                                                                            []
#define SET_TIMER_HANDLER(func)																\
void OBServer_OnTimer ()																		\
{																										\
	func();																							\
}
//____________________________________________________________________________[]












#ifndef	HELPER_DISABLED

//______________________________________________________________________________
//                                                                            []
//` Определения для компилятора файла Auto_Interface.*								[]
//                                                                            []
//----------------------------------------------------------------------------[] 
#define MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE(TYPE)									\
	const char * GET_FUNCTION_ARG_TYPE (TYPE& );											\
	const char * GET_FUNCTION_ARG_TYPE (TYPE##_arr& );
//----------------------------------------------------------------------------[] 
#define MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE(TYPE)								\
	const char * GET_FUNCTION_ARG_TYPE (TYPE& )											\
	{																									\
		return CONVERT_ARG_TYPE_NAME(#TYPE);												\
	}																									\
	const char * GET_FUNCTION_ARG_TYPE (TYPE##_arr&)									\
	{																									\
		return CONVERT_ARG_TYPE_NAME(#TYPE"_arr");										\
	}
//----------------------------------------------------------------------------[] 



MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (identifier);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (int);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (byte);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (bool);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (float);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (string);
MAKE_DEFINITION__GET_FUNCTION_ARG_TYPE (time_t);

// Описание аргументов функций
struct FUNCTION_ARGS
{
	string_arr InArgs_Name;
	string_arr InArgs_Type;
	string_arr InArgs_Description;

	string_arr OutArgs_Name;
	string_arr OutArgs_Type;
	string_arr OutArgs_Description;

	FUNCTION_ARGS ()
	{
	}

	FUNCTION_ARGS (const FUNCTION_ARGS& from)
	{
		CopyFrom (from);
	}

	FUNCTION_ARGS& operator= (const FUNCTION_ARGS& from)
	{
		return CopyFrom (from);
	}

	FUNCTION_ARGS& CopyFrom (const FUNCTION_ARGS& from)
	{
		InArgs_Name        	= from.InArgs_Name;
		InArgs_Type        	= from.InArgs_Type;
		InArgs_Description	= from.InArgs_Description;                    
		OutArgs_Name			= from.OutArgs_Name;
		OutArgs_Type			= from.OutArgs_Type;
		OutArgs_Description	= from.OutArgs_Description;
		return *this;
	}

};
#endif
//____________________________________________________________________________[]





#endif

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
