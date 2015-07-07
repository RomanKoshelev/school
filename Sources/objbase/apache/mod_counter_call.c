/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'apache'                                     []
[] Copyright (C) 2000 by the author(s) -- see below.                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            mod_counter_call.c                                        []
[] Date:            07.03.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#include "stdio.h"
#include "stdlib.h"				// atoi
#include <sys/types.h>			// sockaddr_in
#include <sys/stat.h>			// sockaddr_in
#include <sys/socket.h>			// AF_INET,SOCK_STREAM,...
#include <netdb.h>				// sockaddr_in
#include <unistd.h>				// sockaddr_in
#include <netinet/in.h>			// sockaddr_in

#include <string.h>				// bzero()
#include <errno.h>				// errno()
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 11.03.2000 by AlexV	-- для проверки утечек памяти
static	int	AllocCount = 0;

void		_Free(void *ptr)
{
	AllocCount--;
	return free(ptr);
}
void *   _Malloc(size_t size)
{
	AllocCount++;
	return malloc(size);
}	
void *	_Realloc(void *ptr, size_t size)
{
	AllocCount++;
	return realloc(ptr, size);
}

#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *


//----------------------------------------------------------------------------[]

enum		BX_ArgType
{
	AT_Undefined,		// неинициализировано - ошибка.
	AT_Function,		// название функции.
	AT_Output,			// выходной аргумент - только имя.
	AT_Identifier,		// unsigned long
	AT_String,			// char *
	AT_Int,				// int
	AT_Time,				// long
	AT_Bool,				// bool: '0' || '1'
	AT_Float				// float
};

//----------------------------------------------------------------------------[]

typedef	struct _BX_Arg		BX_Arg;
typedef	struct _BX_Arg*	PBX_Arg;

//----------------------------------------------------------------------------[]
struct	_BX_Arg
{
	union Arg_Variant
	{
		unsigned long	Arg_Identifier;
		char		*		Arg_String;
		int				Arg_Int;
		long				Arg_Time;
		char				Arg_Bool;
		float				Arg_Float;
	}ArgVal;
	
	char *					ArgName;
	enum		BX_ArgType	ArgType;
	PBX_Arg					pNextArg;
};

//----------------------------------------------------------------------------[]
// Формирование списка входных/выходных аргументов.
//PBX_Arg			CreateArgList	(void);
// Освобождение памяти для списка аргументов.
void				ReleaseArgList	(void/*PBX_Arg		pArgList*/);
//----------------------------------------------------------------------------[]
// Конструирование строки запроса к БД в буфере BX_Query. Если все о'кей, то вернет 0.
//int				ConstructQuery	(PBX_Arg		pArgList);
// Освобождение памяти, выделенной под запрос.
void				ReleaseQueryBuffer	(void);
//----------------------------------------------------------------------------[]
// Обработка ответа из БД:
//void				ProcessQuery			(request_rec *r, const char * Query, int	ResultCode);
// Извлечение аргументов разных типов из запроса.  Если все о'кей, то вернет 0.
int				ExtractArg_Identifier(const char * Query, const char * ArgName,	unsigned long*	pArgValue);
int				ExtractArg_String		(const char * Query, const char * ArgName,	char**			pArgValue);
int				ExtractArg_Int			(const char * Query, const char * ArgName,	int*				pArgValue);
int				ExtractArg_Time		(const char * Query, const char * ArgName,	long*				pArgValue);
int				ExtractArg_Bool		(const char * Query, const char * ArgName,	char*				pArgValue);
int				ExtractArg_Float		(const char * Query, const char * ArgName,	float*			pArgValue);
//----------------------------------------------------------------------------[]

//----------------------------------------------------------------------------[]
// Буферы для запросов
//----------------------------------------------------------------------------[]
#define	QUERY_CHUNK_SIZE		4096
#define	QUERY_WARNING_SIZE	20
#define	QUERY_HEADER_SIZE		50
#define	BX_RESULT_SIZE			11
#define	ARGUMENT_SIZE			128
// Макс. кол-во памяти, выделяемое под буфер запросов/ответов порциями по QUERY_CHUNK_SIZE:
#define	MAX_QUERY_SIZE			1024*1024		
//---------------------------*------------------------------------------------[]
// СТАТИЧЕСКИЕ ПЕРЕМЕННЫЕ
//----------------------------------------------------------------------------[]
static	char		QueryHeader		[QUERY_HEADER_SIZE	];
static	char		ResultTemplate	[BX_RESULT_SIZE+1		];
static	char		SearchTemplate	[ARGUMENT_SIZE			];

// Указатель на запрос из/в БД:
static	char*		BX_Query			= NULL;
static	char*		BX_Answer		= NULL;

// Указатель на список аргументов для запроса
static	PBX_Arg	ArgumentList	= NULL;
static	PBX_Arg	pPrevArg 		= NULL;

// Код возврата из БД:
static	int		BX_ResultCode	= -1;

//----------------------------------------------------------------------------[]

//----------------------------------------------------------------------------[]
// Коды возврата для функции ConstructQuery()
//----------------------------------------------------------------------------[]
#define		BX_Query_Okay					0
#define		BX_Query_NoArgs				-1
#define		BX_Query_NotReleased			-2
#define		BX_Query_CantAlloc			-3
#define		BX_Query_FuncBlockInvalid	-4
#define		BX_Query_InBlockInvalid		-5
#define		BX_Query_OutBlockInvalid	-6
#define		BX_Query_UnknownArgType		-7
#define		BX_Query_BufferOverflow		-8
//----------------------------------------------------------------------------[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` main                                                                      []    
[]                                                                            []
[]____________________________________________________________________________*/
int CALL_FUNCTION ()
{
				int				ReturnCode;
				int				SocketID;
				int				i;
				int				TotalLength;
				int				AnswerLength;

	struct	sockaddr_in		SocketAddress;
	struct	hostent *		HostStruct;

	struct	BX_Arg*	FirstArg = NULL;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Инициализация переменных:
	BX_ResultCode	= -1000;
	BX_Query			= NULL;		  
	BX_Answer		= NULL;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создать сокет:
	SocketID = socket(Domain, SOCK_STREAM, 0);
	if(SocketID < 0) {
		puts("Error creating socket.");
		return -1;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Получить в структуре SocketAddress сокетный адрес:
	bzero(&SocketAddress, sizeof(struct sockaddr_in));

	SocketAddress.sin_family	= Domain;
	SocketAddress.sin_port		= htons (Port);

	HostStruct = gethostbyname (Host);
	if(!HostStruct) {
		herror (NULL);
		puts ("gethostbyname() failed.");
		return -1;
	}
//	herror(NULL);
	memcpy((char *)&(SocketAddress.sin_addr), (char *)HostStruct->h_addr, HostStruct->h_length);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Конструирование запроса к БД:
//	ArgumentList	= CreateArgList	();						// Положить аргументы в список.
	ReturnCode		= ConstructQuery	(/*ArgumentList*/);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Освободить память из списка.									*
	ReleaseArgList		();

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 10.03.2000 by AlexV -- Распечатка сконструированного запроса
	printf("Query constructed:");
	for (i = 0; i < strlen(BX_Query); i++)
		putchar((BX_Query[i] == 1) ? '=':(BX_Query[i] == 2) ? ',':(BX_Query[i] == 3) ? '~' :BX_Query[i]);
	puts("");

#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *
	
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Проверить код возврата из ConstructQuery:					*
	if (ReturnCode != BX_Query_Okay)								
	{
	// !!! Здесь вставить обработку ошибок.
		printf				("ConstructQuery() failed: %d.\n", ReturnCode);
//		ReleaseQueryBuffer(					);
		close					(SocketID		);
		return				ReturnCode;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Соединение с БД:
	ReturnCode = connect (SocketID, (struct sockaddr*)&SocketAddress, sizeof(SocketAddress));
	if(ReturnCode != 0) {
		printf	("connect() failed: %s.\n", strerror(errno));
//		ReleaseQueryBuffer(					);
		close					(SocketID		);
		return				-1;
	}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Посылка запроса к БД:											*
	sprintf(QueryHeader, "%d,192.168.200.8,MirrorBSD", strlen(BX_Query));
	for (i = strlen(QueryHeader); i < QUERY_HEADER_SIZE; i++) {
		QueryHeader[i] = ' ';	// Добьём пробелами.
	}
	QueryHeader[QUERY_HEADER_SIZE] = 0;
	send(SocketID, QueryHeader,	strlen(QueryHeader), 0); // послать заголовок
	send(SocketID, BX_Query,		strlen(BX_Query),		0); // послать запрос

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Освободить буфер запроса:										*
	ReleaseQueryBuffer	();  // -- теперь туда запишется ответ из базы

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Прием ответа от БД:												*
	TotalLength = 0;

	do
	{
		BX_Query			= realloc (BX_Query, QUERY_CHUNK_SIZE);								// Выделить порцию памяти.
		AnswerLength	= recv (SocketID, &BX_Query[TotalLength], QUERY_CHUNK_SIZE, 0);// Считать (частично) ответ от БД.
		if (AnswerLength < 0) {			// ошибка в recv
			puts	("recv() failed."	);
			close	(SocketID			);
			return -1;
		}

		TotalLength		+= AnswerLength;

	} while ((AnswerLength == QUERY_CHUNK_SIZE) && (TotalLength < MAX_QUERY_SIZE-1));

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Закрыть сокет:														*
//	shutdown	(SocketID, 2);
	close		(SocketID	);

// Пометим конец запроса.
	BX_Query[TotalLength] = 0;																			

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Обработка ошибки переполнения буфера:						*
	if (TotalLength >= MAX_QUERY_SIZE)
	{
		puts					("Answer too long."	);
//		ReleaseQueryBuffer(							);
		close					(SocketID				);
		return -1;
	}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Обработка ошибки недополнния буфера:						*
	if (TotalLength < BX_RESULT_SIZE)
	{
		puts					("Answer too short."	);
		close					(SocketID				);
		return -1;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Разбор ответа от БД:												*
	memcpy(ResultTemplate, BX_Query, BX_RESULT_SIZE);
	ResultTemplate[BX_RESULT_SIZE] = 0;
	BX_ResultCode	= atoi(ResultTemplate);

	BX_Answer = &BX_Query[BX_RESULT_SIZE];

//	ProcessQuery(r, &BX_Query[BX_RESULT_SIZE], BX_ResultCode);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Освобождение памяти, выделенной под запрос:				*
//	ReleaseQueryBuffer();

//	printf("Allocation refs: %d\n\n", AllocCount);

	return 0;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` CreateArg_HEADER                                                          []                
//                                                                            []
#define	CreateArg_HEADER																		\
	PBX_Arg		pArg = NULL;																	\
																										\
	if (Name == NULL) {																			\
		return NULL;																				\
	}																									\
																										\
	pArg = (PBX_Arg)malloc(sizeof(BX_Arg));												\
																										\
	if (pArg == NULL) {																			\
		return NULL;																				\
	}																									\
																										\
	pArg->pNextArg = NULL;																		\
																										\
	pArg->ArgName = (char *)malloc(strlen(Name)+1);										\
	if (pArg->ArgName == NULL) {																\
		free(pArg);																					\
		return NULL;																				\
	}																									\
	strcpy(pArg->ArgName, Name)
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` CreateArg_FOOTER                                                          []                
//                                                                            []
#define	CreateArg_FOOTER																		\
	if ((*pPrevArg) != NULL) {			/* Если это НЕ первый элемент списка.*/	\
		(*pPrevArg)->pNextArg = pArg;															\
	}																									\
	else	{									/* Если это первый элемент списка.	*/		\
		*pFirstArg	= pArg;																		\
	}																									\
	*pPrevArg	= pArg;																			\
	return pArg
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CreateArg_*                                                               []           
[]                                                                            []
[]____________________________________________________________________________*/
PBX_Arg	CreateArg_Identifier(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name, unsigned long Value)
{
	CreateArg_HEADER;

	pArg->ArgType						= AT_Identifier;
	pArg->ArgVal.Arg_Identifier	= Value;

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Int(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name,	int Value)
{
	CreateArg_HEADER;

	pArg->ArgType			= AT_Int;
	pArg->ArgVal.Arg_Int = Value;

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_String(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name,	const char *Value)
{
	CreateArg_HEADER;

	if (Value == NULL) {
		free(pArg);
		return NULL;
	}

	pArg->ArgType					= AT_String;
	pArg->ArgVal.Arg_String		= (char *)malloc(strlen(Value));
	if (pArg->ArgVal.Arg_String == NULL) {
		free(pArg);
		return NULL;
	}
	strcpy(pArg->ArgVal.Arg_String, Value);

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Time(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name,	long Value)
{
	CreateArg_HEADER;

	pArg->ArgType				= AT_Time;
	pArg->ArgVal.Arg_Time	= Value;

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Bool(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name,	char Value)
{
	CreateArg_HEADER;

	pArg->ArgType				= AT_Bool;
	pArg->ArgVal.Arg_Bool	= (Value=='0'||Value=='1') ? Value : (Value == 0) ? '0':'1';

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Float(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name,	float Value)
{
	CreateArg_HEADER;

	pArg->ArgType				= AT_Float;
	pArg->ArgVal.Arg_Float	= Value;

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Output(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name)
{
	CreateArg_HEADER;

	pArg->ArgType				= AT_Output;

	CreateArg_FOOTER;
}
PBX_Arg	CreateArg_Function(PBX_Arg *pFirstArg, PBX_Arg	*pPrevArg, const char *Name)
{
	CreateArg_HEADER;

	pArg->ArgType				= AT_Function;

	CreateArg_FOOTER;
}
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[]
//#define	CreateArgList_HEADER
//	PBX_Arg	pFirstArg	= NULL;
//	PBX_Arg	pPrevArg		= NULL

//#define	CreateArgList_FOOTER
//	return pFirstArg

//----------------------------------------------------------------------------[] 
#define	SET_FUNCTION(Name)																	\
{																										\
	pPrevArg = NULL;	  ArgumentList = NULL;												\
	CreateArg_Function(&ArgumentList, &pPrevArg, Name);								\
}
//----------------------------------------------------------------------------[] 

//----------------------------------------------------------------------------[] 
#define	SET_ARG_IN(Type,Name,Value)														\
{																										\
	if (Value)																						\
	{																									\
		if (CreateArg_##Type(&ArgumentList, &pPrevArg, Name,	Value) == NULL)	\
		{																								\
			puts("Error in CreateArg_*().");													\
			/*return pFirstArg;*/																\
		}																								\
	}																									\
}
//----------------------------------------------------------------------------[] 
#define	SET_ARG_OUT(Name)				CreateArg_Output(&ArgumentList, &pPrevArg, Name)
#define	OBJBASE_CALL_START
#define	OBJBASE_CALL_END				ReleaseQueryBuffer	()
//----------------------------------------------------------------------------[]


#if 0  //{ RomanVK
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CreateArgList                                                             []             
[]                                                                            []
[]____________________________________________________________________________*/
PBX_Arg
CreateArgList	(void)
{
	CreateArgList_HEADER;

	SET_ARG_IN (Function,		BX_Counter_GetData,				0		);

	SET_ARG_IN (Identifier,	SiteID,								2063	);
	SET_ARG_IN (Bool,			JustGetData,						1		);

	SET_ARG_IN (Output,			Total_Hits,							0	);
	SET_ARG_IN (Output,			Total_Hosts,						0	);
	SET_ARG_IN (Output,			OnlineVisitors,					0	);
	SET_ARG_IN (Output,			Total_Loads,						0	);
	SET_ARG_IN (Output,			Total_Visitors,					0	);
	SET_ARG_IN (Output,			Total_VisitorReturns,			0	);
	SET_ARG_IN (Output,			Total_AnonymousVisitors,		0	);
	SET_ARG_IN (Output,			Total_AnonymousVisitors_Prc,	0	);
	SET_ARG_IN (Output,			Total_VisitorExperience,		0	);
	SET_ARG_IN (Output,			Ave_VisitorExperience,			0	);
	SET_ARG_IN (Output,			Total_Hosts,						0	);
	SET_ARG_IN (Output,			Total_Hits,							0	);
	SET_ARG_IN (Output,			Total_AnonymousHits,				0	);
	SET_ARG_IN (Output,			Total_AnonymousHits_Prc,		0	);
	SET_ARG_IN (Output,			Total_SuspiciousHits_Prc,		0	);
	SET_ARG_IN (Output,			Total_SessionTime,				0	);
	SET_ARG_IN (Output,			Total_Shows,						0	);
	SET_ARG_IN (Output,			Total_Clicks,						0	);
	SET_ARG_IN (Output,			Total_MouseOver,					0	);
	SET_ARG_IN (Output,			Total_CTR_Prc,						0	);
	SET_ARG_IN (Output,			Total_Votes,						0	);
	SET_ARG_IN (Output,			Total_Votes_Sum,					0	);
	SET_ARG_IN (Output,			Total_Votes_Ave,					0	);
	SET_ARG_IN (Output,			LM_Loads,							0	);
	SET_ARG_IN (Output,			LM_Visitors,						0	);
	SET_ARG_IN (Output,			LM_VisitorReturns,				0	);
	SET_ARG_IN (Output,			LM_VisitorReturns_Prc,			0	);
	SET_ARG_IN (Output,			LM_Hosts,							0	);
	SET_ARG_IN (Output,			LM_Hits,								0	);
	SET_ARG_IN (Output,			LM_AnonymousHits,					0	);
	SET_ARG_IN (Output,			LM_AnonymousHits_Prc,			0	);
	SET_ARG_IN (Output,			LM_SuspiciousHits_Prc,			0	);
	SET_ARG_IN (Output,			LM_SessionTime,					0	);
	SET_ARG_IN (Output,			LM_Shows,							0	);
	SET_ARG_IN (Output,			LM_Clicks,							0	);
	SET_ARG_IN (Output,			LM_CTR_Prc,							0	);
	SET_ARG_IN (Output,			LW_Loads,							0	);
	SET_ARG_IN (Output,			LW_Visitors,						0	);
	SET_ARG_IN (Output,			LW_VisitorReturns,				0	);
	SET_ARG_IN (Output,			LW_VisitorReturns_Prc,			0	);
	SET_ARG_IN (Output,			LW_Hosts,							0	);
	SET_ARG_IN (Output,			LW_Hits,								0	);
	SET_ARG_IN (Output,			LW_AnonymousHits,					0	);
	SET_ARG_IN (Output,			LW_AnonymousHits_Prc,			0	);
	SET_ARG_IN (Output,			LW_SuspiciousHits_Prc,			0	);
	SET_ARG_IN (Output,			LW_SessionTime,					0	);
	SET_ARG_IN (Output,			LW_Shows,							0	);
	SET_ARG_IN (Output,			LW_Clicks,							0	);
	SET_ARG_IN (Output,			LW_CTR_Prc,							0	);
	SET_ARG_IN (Output,			LD_Loads,							0	);
	SET_ARG_IN (Output,			LD_Visitors,						0	);
	SET_ARG_IN (Output,			LD_VisitorReturns,				0	);
	SET_ARG_IN (Output,			LD_VisitorReturns_Prc,			0	);
	SET_ARG_IN (Output,			LD_Hosts,							0	);
	SET_ARG_IN (Output,			LD_Hits,								0	);
	SET_ARG_IN (Output,			LD_AnonymousHits,					0	);
	SET_ARG_IN (Output,			LD_AnonymousHits_Prc,			0	);
	SET_ARG_IN (Output,			LD_SuspiciousHits_Prc,			0	);
	SET_ARG_IN (Output,			LD_SessionTime,					0	);
	SET_ARG_IN (Output,			LD_Shows,							0	);
	SET_ARG_IN (Output,			LD_Clicks,							0	);
	SET_ARG_IN (Output,			LD_CTR_Prc,							0	);
	SET_ARG_IN (Output,			LH_Loads,							0	);
	SET_ARG_IN (Output,			LH_Visitors,						0	);
	SET_ARG_IN (Output,			LH_VisitorReturns,				0	);
	SET_ARG_IN (Output,			LH_VisitorReturns_Prc,			0	);
	SET_ARG_IN (Output,			LH_Hosts,							0	);
	SET_ARG_IN (Output,			LH_Hits,								0	);
	SET_ARG_IN (Output,			LH_AnonymousHits,					0	);
	SET_ARG_IN (Output,			LH_AnonymousHits_Prc,			0	);
	SET_ARG_IN (Output,			LH_SuspiciousHits_Prc,			0	);
	SET_ARG_IN (Output,			LH_SessionTime,					0	);
	SET_ARG_IN (Output,			LH_Shows,							0	);
	SET_ARG_IN (Output,			LH_Clicks,							0	);
	SET_ARG_IN (Output,			LH_CTR_Prc,							0	);

	CreateArgList_FOOTER;
}
//____________________________________________________________________________[]
#endif //}

//----------------------------------------------------------------------------[]
#define		BX_QueryMode_Undefined		0
#define		BX_QueryMode_FuncBlock		1
#define		BX_QueryMode_InBlock			2
#define		BX_QueryMode_OutBlock		3
//----------------------------------------------------------------------------[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ConstructQuery                                                            []
[]                                                                            []
[]____________________________________________________________________________*/
int
ConstructQuery	(/*PBX_Arg		pArg*/void)
{
	int	nPos		= 0;								// позиция в буфере
	int	nChunk	= 1;								// количество блоков по QUERY_CHUNK_SIZE байт в буфере
	int	Mode = BX_QueryMode_Undefined;

	if (ArgumentList == NULL) {
		return BX_Query_NoArgs;
	}
	if (BX_Query != NULL) {
		return BX_Query_NotReleased;
	}

	if ((BX_Query = malloc(QUERY_CHUNK_SIZE)) == NULL) { 
		return BX_Query_CantAlloc;
	}
//	bzero(BX_Query, QUERY_CHUNK_SIZE);		// Инициализация нулями.

// Пока есть аргументы ...
	while (ArgumentList != NULL)
	{
		switch (ArgumentList->ArgType)
		{
			case AT_Function:
				switch (Mode)
				{
					case BX_QueryMode_Undefined:
						sprintf(&BX_Query[nPos], "%s", ArgumentList->ArgName);
						Mode = BX_QueryMode_FuncBlock;
						break;
					default:
						return BX_Query_FuncBlockInvalid;
				}
				break;

			case AT_Output:
				switch (Mode)
				{
					case BX_QueryMode_OutBlock:	
						sprintf(&BX_Query[nPos], "\002%s", ArgumentList->ArgName);
						break;
					case BX_QueryMode_InBlock:	
						sprintf(&BX_Query[nPos], "\003\002%s", ArgumentList->ArgName);
						Mode = BX_QueryMode_OutBlock;
						break;
					default:
						printf("Illegal mode: %d\n", Mode);

						return BX_Query_OutBlockInvalid;
				}
				break;

			case AT_Identifier:
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%lu", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Identifier);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%lu", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Identifier);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			case AT_String:
				if ((nPos + strlen(ArgumentList->ArgVal.Arg_String)) >= (nChunk*QUERY_CHUNK_SIZE-QUERY_WARNING_SIZE))	{
					nChunk++;														// Нужен ещё блок
					if (QUERY_CHUNK_SIZE*nChunk > MAX_QUERY_SIZE)
						return BX_Query_BufferOverflow;
					BX_Query = realloc(BX_Query, QUERY_CHUNK_SIZE*nChunk);
				}
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%s", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_String);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%s", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_String);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			case AT_Int:
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%d", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Int);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%d", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Int);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			case AT_Time:
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%li", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Time);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%li", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Time);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			case AT_Bool:
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%c", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Bool);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%c", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Bool);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			case AT_Float:
				switch (Mode)
				{
					case BX_QueryMode_InBlock:
						sprintf(&BX_Query[nPos], "\002%s\001%f", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Float);
						break;
					case BX_QueryMode_FuncBlock:
						sprintf(&BX_Query[nPos], "\003\002%s\001%f", ArgumentList->ArgName, ArgumentList->ArgVal.Arg_Float);
						Mode = BX_QueryMode_InBlock;
						break;
					default:
						return BX_Query_InBlockInvalid;
				}
				break;

			default:
				return BX_Query_UnknownArgType;
		} // end switch

		nPos = strlen(BX_Query);
		
		if (nPos >= (nChunk*QUERY_CHUNK_SIZE-QUERY_WARNING_SIZE))	{
			nChunk++;		// Нужен ещё блок
			if (QUERY_CHUNK_SIZE*nChunk > MAX_QUERY_SIZE)
				return BX_Query_BufferOverflow;
			BX_Query = realloc(BX_Query, QUERY_CHUNK_SIZE*nChunk);
		}

		ArgumentList = ArgumentList->pNextArg;

	} // end while

	return BX_Query_Okay;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ReleaseQueryBuffer                                                        []            
[]                                                                            []
[]____________________________________________________________________________*/
void
ReleaseQueryBuffer	(void)
{
	if (BX_Query != NULL) {
		free(BX_Query);
		BX_Query = NULL;
	}
	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ReleaseArgList                                                            []              
[]                                                                            []
[]____________________________________________________________________________*/
void
ReleaseArgList	(void)
{
	PBX_Arg	pArgNext;
	while (ArgumentList != NULL)
	{
		pArgNext	= ArgumentList->pNextArg;			// сохраним указатель на следующую структуру

		free(ArgumentList->ArgName);					// освободим имя аргумента

		if (ArgumentList->ArgType == AT_String) {
			free(ArgumentList->ArgVal.Arg_String);	// освободим строку-аргумент (если тип - строка)
		}
		
		free(ArgumentList);								// освободим саму структуру

		ArgumentList = pArgNext;						// перейдем к следующей
	}
	pPrevArg = NULL;
	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ExtractArg_*                                                              []            
[]                                                                            []
[]____________________________________________________________________________*/

#define	ExtractArg_HEADER																		\
	char	*	pName;																				\
	sprintf(SearchTemplate, "\002%s\001", ArgName);										\
	pName = strstr(Query, SearchTemplate);													\
	if (pName == NULL) {																			\
		return -1;																					\
	}

int	ExtractArg_Identifier(const char * Query, const char * ArgName,	unsigned long*	pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName + strlen(SearchTemplate), "%lu", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
int	ExtractArg_Int			(const char * Query, const char * ArgName,	int*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName + strlen(SearchTemplate), "%d", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
int	ExtractArg_Time		(const char * Query, const char * ArgName,	long*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName + strlen(SearchTemplate), "%li", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
int	ExtractArg_Bool		(const char * Query, const char * ArgName,	char*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName + strlen(SearchTemplate), "%c", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
int	ExtractArg_Float		(const char * Query, const char * ArgName,	float*			pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName + strlen(SearchTemplate), "%f", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
#define	ExtractArg(Type,ArgName,ValueHolder)											\
	if (ExtractArg_##Type(BX_Query, ArgName, &ValueHolder) != 0) {					\
		puts("Can't find argument: " ArgName);												\
	}
#define	GET_RETVALUE(Type,ArgName,ValueHolder)											\
	if (ExtractArg_##Type(BX_Query, ArgName, &ValueHolder) != 0) {					\
		puts("Can't find argument: " ArgName);												\
	}

//----------------------------------------------------------------------------[]


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 11.03.2000 by AlexV
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ProcessQuery                                                              []            
[]                                                                            []
[]____________________________________________________________________________*/
void ProcessQuery (request_rec *r, const char * Query, int ResultCode)
{
	int	QueryLength;
	int	RunCounter;
	int	Temp;

	QueryLength = strlen(Query);
	ap_rprintf (r, "Database call result[%d]: %s (%d).\n", QueryLength, ResultCode ? "Error":"Okay", ResultCode);
	puts("---------------------------------------------------------------");

	
	ExtractArg(Int, Total_Hits,		Temp);	ap_rprintf (r, "%-30s: %d\n", "Total_Hits",		Temp);
	ExtractArg(Int, Total_Hosts,		Temp);	ap_rprintf (r, "%-30s: %d\n", "Total_Hosts",		Temp);
	ExtractArg(Int, Total_Visitors,	Temp);	ap_rprintf (r, "%-30s: %d\n", "Total_Visitors",	Temp);
	ExtractArg(Int, Total_Gavno,		Temp);	ap_rprintf (r, "%-30s: %d\n", "Total_Gavno",		Temp);

	if (QueryLength > 0)
	{
		RunCounter = 0;
		while (RunCounter < QueryLength)
		{
			if (Query[RunCounter] == 2) {
				putchar('\n');
			}
			else if (Query[RunCounter] == 1)	{
				putchar('\t');	putchar('\t');	putchar('\t');
			}
			else	{
				putchar(Query[RunCounter]);
			}

			RunCounter++;
		}
	}


	puts("\n---------------------------------------------------------------");

	return;
}
#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/