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
#include <stdio.h>
#include <stdlib.h>				// atoi
#include <sys/types.h>			// sockaddr_in
#include <sys/stat.h>			// sockaddr_in
#include <sys/socket.h>			// AF_INET,SOCK_STREAM,...
#include <netdb.h>				// sockaddr_in
#include <unistd.h>				// sockaddr_in
#include <netinet/in.h>			// sockaddr_in
#include <arpa/inet.h>			// inet_aton()
#include <string.h>				// bzero()
#include <errno.h>				// errno, strerr()
#include <time.h>					// timeval
#include <fcntl.h>				// fcntl
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` КОНФИГУРАЦИЯ                                                              []
[]                                                                            []
[]____________________________________________________________________________*/

// Установки сервера
static 	const		char				*Host					= "127.0.0.1";
static 	const		int				Port					= 1502;

// Таймауты
static struct timeval	CNTD_ConnectTimeout	= {20, 0};
static struct timeval	CNTD_ReadTimeout		= { 5, 0};
//----------------------------------------------------------------------------[] 




// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Параметры заголовка запроса:									*
#define	RequestSignature				"AVRKAVRK"				// Подпись заголовка запроса.
#define	RequestSignatureSize			8							// Размер подписи заголовка запроса.
																			
#define	DATATYPE_SERVER_PLAIN		1000						// Тип данных: запрос к серверу по текстовому протоколу.
#define	DATATYPE_SERVER_BINARY		1100						// Тип данных: запрос к серверу по бинарному протоколу.
#define	DATATYPE_CLIENT_PLAIN		2000						// Тип данных: ответ клиенту по текстовому протоколу.
#define	DATATYPE_CLIENT_BINARY		2100						// Тип данных: ответ клиенту по бинарному протоколу.
																			
#define	ENCRIPTION_NONE				1000						// Тип шифрования: нет шифрования.
																			
#define	COMMAND_SERVER_DBREQUEST	1000						// Команда серверу:	запрос к БД.
#define	COMMAND_SERVER_STOP			1100						// Команда серверу:	останов.
#define	COMMAND_CLIENT_ANSWER		10000						// Команда клиенту:	ответ на запрос к БД.
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ошибки																*
#define	CNTD_OKAY								0					// Нормальное завершение.
#define	CNTD_UNDEFINED							-100				// Такой ошибки не должно быть.
#define	CNTD_QUERY_BUFSIZE_EXCEEDED		-200				// Нет места в буфере.
#define	CNTD_NOT_ENOUGH_MEMORY				-300				// Нет памяти.
#define	CNTD_SETFUNCTION_NOTINPLACE		-400				// SET_FUNCTION не на нужном месте.
#define	CNTD_SETFUNCTION_BADARGUMENT		-450				// Кривые аргументы SET_FUNCTION.
#define	CNTD_SETARGIN_NOTINPLACE			-500				// SET_ARG_IN не на нужном месте.
#define	CNTD_SETARGIN_BADARGUMENT			-550				// Кривые аргументы SET_ARG_IN.
#define	CNTD_SETARGOUT_NOTINPLACE			-600				// SET_ARG_OUT не на нужном месте.
#define	CNTD_SETARGOUT_BADARGUMENT			-650				// Кривые аргументы SET_ARG_OUT.

#define	CNTD_NOTHING_TO_SEND					-1000				// CALL_FUNCTION вызвана с пустым буфером.
#define	CNTD_SOCKET_ERROR						-1100				// socket() вернула ошибку.
#define	CNTD_FCNTL_ERROR						-1200				// fcntl() вернула ошибку.
#define	CNTD_INVALID_ADDRESS					-1300				// inet_aton() вернула ошибку.
#define	CNTD_SELECT_ERROR						-1400				// select() вернула ошибку.
#define	CNTD_CONNECT_ERROR					-1500				// connect() вернула ошибку.
#define	CNTD_CONNECT_TIMEOUT					-1600				// Таймаут соединения с базой.
#define	CNTD_READ_TIMEOUT						-1700				// Таймаут ожидания ответа от базы.
#define	CNTD_WRITEHEADER_ERROR				-1800				// Ошибка при посылке заголовка базе.
#define	CNTD_WRITEDATA_ERROR					-1850				// Ошибка при посылке блока данных базе.
#define	CNTD_READHEADER_ERROR				-1900				// Ошибка при приеме заголовка от базы.
#define	CNTD_READDATA_ERROR					-1950				// Ошибка при приеме блока данных от базы.
#define	CNTD_READDATA_BADHEADER				-2000				// Кривой заголовок данных.
#define	CNTD_READDATA_TOOLARGE				-2100				// Слишком большой блок данных - не поместится в буфере.
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Тип логических блоков в буфере:
#define	LBType_None				100
#define	LBType_Function		200
#define	LBType_Input			300
#define	LBType_Output			400
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *


// Макс. кол-во памяти, выделяемое под буфер запросов/ответов порциями по QUERY_CHUNK_SIZE:
#define	MAX_QUERY_SIZE			(128*1024)		
#define	QUERY_CHUNK_SIZE		4096					// Должен быть кратен MAX_QUERY_SIZE !


//---------------------------*------------------------------------------------[]
// СТАТИЧЕСКИЕ ПЕРЕМЕННЫЕ
//----------------------------------------------------------------------------[]

// Заголовок запроса
static struct	REQUEST_HEADER
{
	char				Signature[RequestSignatureSize];	// Подпись
	unsigned long	DataBlockSize;							// Длина блока данных после заголовка
	unsigned long	CRC;										// Контрольная сумма блока данных.
	int				DataType;								// Тип данных: текст/бинарный
	int				DataEncriptionType;					// Способ шифрования.
	int				Command;									// Команда серверу.
	int				Reserved;								// Зарезервировано.
}CNTD_RequestHeader;

// Статус выполнения операций:
static	int		CNTD_Errno		= CNTD_OKAY;

// Указатель на запрос из/в БД:
static	char*		CNTD_Query			= NULL;
static	int		CNTD_QuerySize		= 0;
static	int		CNTD_QueryChunks	= 0;

// Текущий тип логических блоков в буфере:
static	int		BX_LBType			= LBType_None;
// Разделители логических блоков в буфере:
static	char		BX_MainDelim		= 3;		
static	char		BX_ArgNameDelim	= 2;		
static	char		BX_ArgValDelim		= 1;		

static	int		SocketID			= -1;
//----------------------------------------------------------------------------[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ReleaseQueryBuffer                                                        []                  
[]                                                                            []
[]____________________________________________________________________________*/
void	ReleaseQueryBuffer (void)
{
	if (CNTD_Query != NULL)
	{
		free (CNTD_Query);
		CNTD_Query			= NULL;
		CNTD_QuerySize		= 0;
		CNTD_QueryChunks	= 0;
	}

	return;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` AddToQueryBuffer                                                          []                
[]                                                                            []
[]____________________________________________________________________________*/
void	AddToQueryBuffer(const char * pBlock, size_t	 BlockSize)
{
	char*		pTemp;
	size_t	nChunks;

	if (CNTD_Errno != CNTD_OKAY) {
		return;
	}

	if (BlockSize <= 0) {
		return;				
	}

	if (BlockSize + CNTD_QuerySize > MAX_QUERY_SIZE)	{
		CNTD_Errno = CNTD_QUERY_BUFSIZE_EXCEEDED;				
		return;
	}

// Надо ли выделить ещё кусок памяти ?
	if (CNTD_QueryChunks*QUERY_CHUNK_SIZE < BlockSize + CNTD_QuerySize)
	{
	// Свободно в текущем куске:				CNTD_QueryChunks * QUERY_CHUNK_SIZE - CNTD_QuerySize
	// Требуется дополнительно выделить:	BlockSize - (CNTD_QueryChunks*QUERY_CHUNK_SIZE - CNTD_QuerySize)
		nChunks = (BlockSize - (CNTD_QueryChunks*QUERY_CHUNK_SIZE - CNTD_QuerySize)) / QUERY_CHUNK_SIZE + 1;		

		pTemp = (char*)realloc (CNTD_Query, (CNTD_QueryChunks+nChunks)*QUERY_CHUNK_SIZE);
		if (pTemp == NULL) {
			CNTD_Errno = CNTD_NOT_ENOUGH_MEMORY;
			return;
		}

		CNTD_Query			=	pTemp;
		CNTD_QueryChunks += nChunks;
	}

// Скопировать данные в буфер:
	memcpy (CNTD_Query+CNTD_QuerySize, pBlock, BlockSize);

	CNTD_QuerySize += BlockSize;

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBJBASE_CALL_START                                                        []                  
[]                                                                            []
[]____________________________________________________________________________*/
void OBJBASE_CALL_START(void)
{
				int				ConnectReturnCode;
	struct	sockaddr_in		SocketAddress;
//	struct	hostent *		HostStruct;
				int				SocketFlags;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Инициализировать буферы и флаги статуса:
	CNTD_Errno	= CNTD_OKAY;
	BX_LBType	= LBType_None;

	ReleaseQueryBuffer ();

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Инициировать соединение с базой:
	
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создать tcp-сокет:
	SocketID = socket(PF_INET, SOCK_STREAM, 0);
	if(SocketID < 0) {
		CNTD_Errno = CNTD_SOCKET_ERROR;
		return;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Установить неблокирующий режим для сокета
	SocketFlags = fcntl (SocketID, F_GETFL, 0);
	if (SocketFlags == -1)
	{
		CNTD_Errno = CNTD_FCNTL_ERROR;
		return;
	}
	if (fcntl (SocketID, F_SETFL, SocketFlags | O_NONBLOCK) == -1)
	{
		CNTD_Errno = CNTD_FCNTL_ERROR;
		return;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Получить в структуре SocketAddress сокетный адрес:
	bzero(&SocketAddress, sizeof (struct sockaddr_in));

	SocketAddress.sin_family	= PF_INET;
	SocketAddress.sin_port		= htons (Port);
	if (!inet_aton(Host, &SocketAddress.sin_addr)) {
		CNTD_Errno = CNTD_INVALID_ADDRESS;
		return;
	}
/*	HostStruct = gethostbyname (Host);
	if(!HostStruct) {
		herror (NULL);
		puts ("gethostbyname() failed.");
		return -1;
	}
	herror(NULL);
	memcpy((char *)&(SocketAddress.sin_addr), (char *)HostStruct->h_addr, HostStruct->h_length);
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Соединение с БД:
	ConnectReturnCode = connect (SocketID, (struct sockaddr*)&SocketAddress, sizeof(SocketAddress));
	if((ConnectReturnCode < 0) && (errno != EINPROGRESS))
	{
		close (SocketID);
		SocketID		= -1;
		CNTD_Errno	= CNTD_CONNECT_ERROR;
		return;
	}

	return;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SET_FUNCTION                                                              []            
[]                                                                            []
[]____________________________________________________________________________*/
void	SET_FUNCTION (const char *FuncName)
{
	if (CNTD_Errno != CNTD_OKAY) {
		return;
	}

	if (BX_LBType != LBType_None) {
		CNTD_Errno = CNTD_SETFUNCTION_NOTINPLACE;
		return;
	}

	if (FuncName == NULL)
	{
		CNTD_Errno = CNTD_SETFUNCTION_BADARGUMENT;
		return;
	}

	AddToQueryBuffer(FuncName, strlen (FuncName));
	
	if (CNTD_Errno == CNTD_OKAY) {
		BX_LBType = LBType_Function;
	}

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SET_ARG_IN                                                                []          
[]                                                                            []
[]____________________________________________________________________________*/
void	SET_ARG_IN (const char *ArgName, const char *ArgValue)
{
	if (CNTD_Errno != CNTD_OKAY) {
		return;
	}

	if (ArgValue == NULL)
	{
		return;
	}

	if (ArgName == NULL)
	{
		CNTD_Errno = CNTD_SETARGIN_BADARGUMENT;
		return;
	}

	if ((BX_LBType != LBType_Function) && (BX_LBType != LBType_Input)) {
		CNTD_Errno = CNTD_SETARGIN_NOTINPLACE;
		return;
	}

// Если нужно, вставить разделитель функционального и входного блоков :
	if (BX_LBType == LBType_Function) {
		AddToQueryBuffer (&BX_MainDelim, 1);
	}

// Вставить маркер начала имени аргумента:
	AddToQueryBuffer (&BX_ArgNameDelim, 1);

// Вставить имя аргумента:
	AddToQueryBuffer (ArgName, strlen (ArgName));

// Вставить маркер начала значения аргумента:
	AddToQueryBuffer (&BX_ArgValDelim, 1);

// Вставить значение аргумента:
	AddToQueryBuffer (ArgValue, strlen (ArgValue));

	if (CNTD_Errno == CNTD_OKAY) {
		BX_LBType = LBType_Input;
	}

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SET_ARG_OUT                                                               []           
[]                                                                            []
[]____________________________________________________________________________*/
void SET_ARG_OUT (const char *ArgName)
{
	if (CNTD_Errno != CNTD_OKAY) {
		return;
	}

	if (ArgName == NULL)
	{
		CNTD_Errno = CNTD_SETARGOUT_BADARGUMENT;
		return;
	}

	if ((BX_LBType != LBType_Output) && (BX_LBType != LBType_Input)) {
		CNTD_Errno = CNTD_SETARGOUT_NOTINPLACE;
		return;
	}

// Если нужно, вставить разделитель входного и выходного блоков :
	if (BX_LBType == LBType_Input) {
		AddToQueryBuffer (&BX_MainDelim, 1);
	}

// Вставить маркер начала имени аргумента:
	AddToQueryBuffer (&BX_ArgNameDelim, 1);

// Вставить имя аргумента:
	AddToQueryBuffer (ArgName, strlen (ArgName));

	if (CNTD_Errno == CNTD_OKAY) {
		BX_LBType = LBType_Output;
	}

	return;

}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` readn                                                                     []     
//                                                                            []
/* Read "n" bytes from a descriptor. */
ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char		*ptr;

	ptr	= (char*)vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return (nread);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return (n - nleft);		/* return >= 0 */
}
/* end readn */
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` writen                                                                    []      
//                                                                            []
/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr	= (const char*)vptr;
	nleft = n;

	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(nwritten);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return (n);
}
/* end writen */
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CALL_FUNCTION                                                             []             
[]                                                                            []
[]____________________________________________________________________________*/
void CALL_FUNCTION (void)
{
	int				ReturnCode;
	fd_set			rset, wset;

	if (CNTD_Errno != CNTD_OKAY) {
		return;
	}
	if (SocketID < 0) {
		return;
	}

	if (CNTD_Query == NULL) {
		CNTD_Errno = CNTD_NOTHING_TO_SEND;
		return;
	}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Заполнить заголовок:												*
	bzero		(&CNTD_RequestHeader, sizeof (CNTD_RequestHeader));
	memcpy	(&CNTD_RequestHeader.Signature, RequestSignature, RequestSignatureSize);
	CNTD_RequestHeader.DataBlockSize			= CNTD_QuerySize;
	CNTD_RequestHeader.DataType				= DATATYPE_SERVER_PLAIN;
	CNTD_RequestHeader.DataEncriptionType	= ENCRIPTION_NONE;
	CNTD_RequestHeader.Command					= COMMAND_SERVER_DBREQUEST;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ожидание соединения с сервером:
//	if (ConnectReturnCode != 0)
//	{
		FD_ZERO	(&rset);
		FD_SET	(SocketID, &rset);
		wset = rset;
		
		if (select (SocketID+1, &rset, &wset, NULL, &CNTD_ConnectTimeout) == 0)
		{
			close					(SocketID		);
			SocketID = -1;
			errno = ETIMEDOUT;
			CNTD_Errno = CNTD_CONNECT_TIMEOUT;
			return;
		}


		if (!FD_ISSET(SocketID, &rset) && !FD_ISSET(SocketID, &wset))
		{
			close (SocketID);
			SocketID = -1;
			CNTD_Errno = CNTD_SELECT_ERROR;
			return;
		}
//	}
/*
// Соединение произошло. Положим сокетные флаги на место:
	if (fcntl (SocketID, F_SETFL, SocketFlags) == -1)
	{
		close(SocketID);
		CNTD_Errno = CNTD_FCNTL_ERROR;
		SocketID = -1;
		return;
	}
*/
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Посылка запроса к БД:											*

// послать заголовок	
	if (writen(SocketID, &CNTD_RequestHeader,	sizeof(CNTD_RequestHeader)) != sizeof(CNTD_RequestHeader))
	{
		close(SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_WRITEHEADER_ERROR;
		return;
	}
// послать данные
	if (writen(SocketID, CNTD_Query,	CNTD_QuerySize) != CNTD_QuerySize)
	{
		close(SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_WRITEDATA_ERROR;
		return;
	}
// закончить запись
	shutdown (SocketID, SHUT_WR);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Освободить буфер запроса:										*
	ReleaseQueryBuffer	();  // -- теперь туда запишется ответ из базы

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Прием ответа от БД:												*

// Ожидание готовности к чтению - 1:
	FD_ZERO	(&rset);
	FD_SET	(SocketID, &rset);
	
	if (select (SocketID+1, &rset, NULL, NULL, &CNTD_ReadTimeout) == 0)
	{
		close(SocketID);
		SocketID = -1;
		errno = ETIMEDOUT;
		CNTD_Errno = CNTD_READ_TIMEOUT;
		return;
	}

	if (!FD_ISSET(SocketID, &rset))
	{
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_SELECT_ERROR;
		return;
	}

// Считать заголовок	ответа:
	ReturnCode = readn (SocketID, &CNTD_RequestHeader, sizeof (CNTD_RequestHeader));
	if (ReturnCode != sizeof (CNTD_RequestHeader))
	{
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_READHEADER_ERROR;
		return;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Разобрать заголовок ответа:									*
	if ((strncmp (CNTD_RequestHeader.Signature, RequestSignature, RequestSignatureSize) != 0)
		|| (CNTD_RequestHeader.Command != COMMAND_CLIENT_ANSWER)
		|| (CNTD_RequestHeader.DataEncriptionType != ENCRIPTION_NONE)
		/*|| (CNTD_RequestHeader.DataType != DATATYPE_CLIENT_PLAIN)*/)
	{
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_READDATA_BADHEADER;
		return;
	}

	if (CNTD_RequestHeader.DataBlockSize > MAX_QUERY_SIZE)
	{
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_READDATA_TOOLARGE;
		return;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Заказать память для блока данных:							*
	if (CNTD_Query != NULL) {
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_UNDEFINED;
		return;
	}

	CNTD_Query  = (char*)malloc (CNTD_RequestHeader.DataBlockSize+1);

	if (CNTD_Query == NULL) {
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_NOT_ENOUGH_MEMORY;
		return;
	}

	CNTD_QuerySize = CNTD_RequestHeader.DataBlockSize+1;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ожидание готовности к чтению - 2:							*
	FD_ZERO	(&rset);
	FD_SET	(SocketID, &rset);
	
	if (select (SocketID+1, &rset, NULL, NULL, &CNTD_ReadTimeout) == 0)
	{
		close(SocketID);
		SocketID = -1;
		errno = ETIMEDOUT;
		CNTD_Errno = CNTD_READ_TIMEOUT;
		return;
	}

	if (!FD_ISSET(SocketID, &rset))
	{
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_SELECT_ERROR;
		return;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Считать блок данных:												*
	ReturnCode = readn (SocketID, CNTD_Query, CNTD_RequestHeader.DataBlockSize);
	if (ReturnCode != CNTD_RequestHeader.DataBlockSize)
	{
		ReleaseQueryBuffer	();  
		close (SocketID);
		SocketID = -1;
		CNTD_Errno = CNTD_READDATA_ERROR;
		return;
	}

	CNTD_Query[CNTD_RequestHeader.DataBlockSize] = 0;		// Пометим конец запроса.

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Закрыть сокет:														*
	shutdown	(SocketID, SHUT_RD);
	close		(SocketID	);
	SocketID = -1;

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBJBASE_CALL_END                                                          []                
[]                                                                            []
[]____________________________________________________________________________*/
void OBJBASE_CALL_END (void)
{
	if (SocketID >= 0)
	{
		close		(SocketID	);
		SocketID = -1;
	}
	ReleaseQueryBuffer ();
	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` GET_FUNCTION_RESULT                                                       []                   
[]                                                                            []
[]____________________________________________________________________________*/
int	GET_FUNCTION_RESULT (char **ppErrorDescription)
{
	int	BX_Result;
// Выставим для начала описание ошибки в 0
	if (ppErrorDescription != NULL) {
		*ppErrorDescription = NULL;
	}

// Буфер пустой - возврат	
	if (CNTD_Query == NULL) {
		return -30000;
	}

// Получить код ошибки
	BX_Result = ((int *) CNTD_Query) [1];

// Если ошибка, то выставим указатель на её описание:
	if ((BX_Result != 0)  && (ppErrorDescription != NULL)) {
		*ppErrorDescription = CNTD_Query + sizeof (int) + sizeof (int);
	}

	return BX_Result;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ExtractArg_*                                                              []            
[]                                                                            []
[]____________________________________________________________________________*/

//----------------------------------------------------------------------------[]
#define	GET_RETVALUE(Type,ArgName,ValueHolder)											\
	ExtractArg_##Type(ArgName, &ValueHolder)
//----------------------------------------------------------------------------[]
#define	ExtractArg_HEADER																		\
	char		*pName;																				\
	char		*pAnswerStart;																		\
																										\
	*pArgValue		= 0;																			\
																										\
	if (CNTD_Errno != CNTD_OKAY) {															\
		return -6;																					\
	}																									\
																										\
	if (*ArgName == 0)   {																		\
		return -5;																					\
	}																									\
																										\
	if (CNTD_Query == NULL)   {																\
		return -3;																					\
	}																									\
																										\
	pAnswerStart	= CNTD_Query+sizeof(int)+sizeof(int);								\
																										\
	for (;;)																							\
	{																									\
		pName = strstr(pAnswerStart, ArgName);												\
		if (pName == NULL) {																		\
			return -2;																				\
		}																								\
																										\
		if (*(pName-1) == BX_ArgNameDelim)													\
		{																								\
			pName += strlen (ArgName);															\
			if (*pName != BX_ArgValDelim) {													\
				return -4;																			\
			}																							\
			pName++;																					\
			break;																					\
		}																								\
	}

//----------------------------------------------------------------------------[]

//----------------------------------------------------------------------------[]
int	ExtractArg_Int			(const char * ArgName,	int*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName, "%d", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//----------------------------------------------------------------------------[]
int	ExtractArg_Identifier(const char * ArgName,	unsigned long*	pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName, "%lu", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//----------------------------------------------------------------------------[]
int	ExtractArg_Time		(const char * ArgName,	long*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName, "%li", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//----------------------------------------------------------------------------[]
int	ExtractArg_Bool		(const char * ArgName,	char*				pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName, "%c", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//----------------------------------------------------------------------------[]
int	ExtractArg_Float		(const char * ArgName,	float*			pArgValue)
{
	ExtractArg_HEADER;

	if (sscanf(pName, "%f", pArgValue) != 1) {
		return -1;
	}
	return 0;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/