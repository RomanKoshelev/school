/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'														[]
[] Copyright (C) 2000 by the author(s) -- see below.                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBServer.cpp																[]
[] Date:            15.03.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Серверная часть базы.                                     []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/



//----------------------------------------------------------------------------[]
#ifndef WIN32
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "config.h"
//----------------------------------------------------------------------------[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` КОНФИГУРАЦИЯ                                                              []
[]                                                                            []
[]____________________________________________________________________________*/

// Параметры заголовка запроса:
#define	RequestSignature					"AVRKAVRK"	// Подпись заголовка запроса.
#define	RequestSignatureSize				8				// Размер подписи заголовка запроса.
													
#define	DATATYPE_SERVER_PLAIN			1000			// Тип данных: запрос к серверу по текстовому протоколу.
#define	DATATYPE_SERVER_BINARY			1100			// Тип данных: запрос к серверу по бинарному протоколу.
#define	DATATYPE_CLIENT_PLAIN			2000			// Тип данных: ответ клиенту по текстовому протоколу.
#define	DATATYPE_CLIENT_BINARY			2100			// Тип данных: ответ клиенту по бинарному протоколу.
													
#define	ENCRIPTION_NONE					1000			// Тип шифрования: нет шифрования.
													
#define	COMMAND_SERVER_DBREQUEST		1000			// Команда серверу:	запрос к БД.
#define	COMMAND_SERVER_STOP				1100			// Команда серверу:	останов.
#define	COMMAND_SERVER_GETSTATS			1200			// Команда серверу:	получить статистику.
#define	COMMAND_SERVER_RESETSTATS		1300			// Команда серверу:	сброс статистики.
#define	COMMAND_SERVER_HISTORYSTATS	1400			// Команда серверу:	получение history статистики.
#define	COMMAND_CLIENT_DBANSWER			10000			// Команда клиенту:	ответ на запрос к БД.
#define	COMMAND_CLIENT_GETSTATS			10200			// Команда клиенту:	ответ на запрос статистики.
#define	COMMAND_CLIENT_RESETSTATS		10300			// Команда клиенту:	ответ на сброс статистики.
#define	COMMAND_CLIENT_HISTORYSTATS	10400			// Команда клиенту:	ответ на запрос history статистики.
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[]
void	OBServer_Interface			(const char*,const char*,const char*,void**);
void	OBServer_Interface_Free		(void**);
void	OBServer_OnTimer				(void);

extern time_t	time_0;
//----------------------------------------------------------------------------[]


//______________________________________________________________________________
//                                                                            []
//` REQUEST_HEADER                                                            []              
//                                                                            []
// Заголовок запроса
struct	REQUEST_HEADER
{
	char				Signature[RequestSignatureSize];	// Подпись
	unsigned long	DataBlockSize;							// Длина блока данных после заголовка
	unsigned long	CRC;										// Контрольная сумма блока данных.
	int				DataType;								// Тип данных: текст/бинарный
	int				DataEncriptionType;					// Способ шифрования.
	int				Command;									// Команда серверу.
	int				Reserved;								// Зарезервировано.
};
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[]
// Статус базы данных
#define	BM_WORKING		0
#define	BM_STOPPING		1
volatile	sig_atomic_t	gBaseMode				= BM_WORKING;
//----------------------------------------------------------------------------[]


//----------------------------------------------------------------------------[]
static	FILE*					hTimelog				= NULL;		// Дескриптор файла time-лога.
static	int					hLockFile			= -1;			// Дескриптор lock-файла.
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[]
// Структуры для замеров времени выполнения
static	struct timeval		tStart;
static	struct timeval		tEnd;

// Счетчики числа операций
static	double				Count_Read							= 0.0;
static	double				Count_OBServer_Interface		= 0.0;
static	double				Count_Write							= 0.0;
static	double				Count_Timer							= 0.0;

// Счетчики среднего времени выполнения																			
static	double				Ave_Read								= 0.0;
static	double				Ave_OBServer_Interface			= 0.0;
static	double				Ave_Write							= 0.0;
static	double				Ave_Timer							= 0.0;

// Время сброса счетчиков.
static	time_t				AveReset_Read						= 0;
static	time_t				AveReset_OBServer_Interface	= 0;
static	time_t				AveReset_Write						= 0;
static	time_t				AveReset_Timer						= 0;

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]
// Performance history
static	int					InterfaceHistory_Pos				= 0;
static	time_t				InterfaceHistory_Reset		[OBS_HISTORY_SIZE];

static	double				InterfaceHistory_Count		[OBS_HISTORY_SIZE];
static	double				InterfaceHistory_AveTime	[OBS_HISTORY_SIZE];
static	double				Timer_Count						[OBS_HISTORY_SIZE];
static	double				Timer_AveTime					[OBS_HISTORY_SIZE];
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]


//----------------------------------------------------------------------------[]
#define	TIMECHECK_START(Type)																\
		gettimeofday	(&tStart,	NULL)
//----------------------------------------------------------------------------[]
#define	TIMECHECK_END(Type)																	\
		gettimeofday	(&tEnd,	NULL);														\
		if (Count_##Type < 1.0 || Count_##Type > 1000000.0) {							\
			AveReset_##Type= time_0;															\
			Count_##Type	= 0.0;																\
			Ave_##Type		= 0.0;																\
		}																								\
		Count_##Type		+= 1.0;																\
		MicrosecDiff		= (tEnd.tv_usec - tStart.tv_usec								\
									+ 1000000.0 * (tEnd.tv_sec - tStart.tv_sec));		\
		Ave_##Type			= ((Count_##Type-1.0) * Ave_##Type + MicrosecDiff)		\
									/ Count_##Type
//----------------------------------------------------------------------------[]

//----------------------------------------------------------------------------[]
#define FREE_PTR(_Ptr)																			\
	if (_Ptr != NULL)																				\
	{																									\
		delete[]	_Ptr;																				\
		_Ptr = NULL;																				\
	}
//----------------------------------------------------------------------------[]



//______________________________________________________________________________
//                                                                            []
//` CreateLockFile                                                            []              
//                                                                            []
// Создание lock-файла: возвращает true  в случае успеха
bool CreateLockFile(void)
{
	char	PID_Buf[10];
	bzero (PID_Buf, 10);

	if (hLockFile >= 0) {
		return false;
	}
	
	if ((hLockFile = open(LockFileName, O_CREAT|O_RDWR|O_EXLOCK|O_NONBLOCK)) < 0) {//S_IWGRP|S_IWOTH
		return false;
	}

	if (chmod(LockFileName, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) != 0) {
		close (hLockFile);
		hLockFile = -1;
		return false;
	}

	snprintf (PID_Buf, 10, "%lu", (unsigned long)getpid());

	if (write(hLockFile, PID_Buf, strlen(PID_Buf)) == -1)
	{
		close (hLockFile);
		hLockFile = -1;
		return false;
	}

	return true;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` OBServer_RemoveLock                                                       []
[]                                                                            */
// Удаление lock-файла: возвращает true  в случае успеха
bool OBServer_RemoveLock(void)
{
	if (hLockFile < 0) {
		return false;
	}
	close (hLockFile);
	hLockFile = -1;
	unlink (LockFileName);
	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` LockFileExists                                                            []              
//                                                                            []
// Проверка существования lock-файла
#define LockFileExists	SetDBLockFlag
bool	SetDBLockFlag(void)
{
	return /*(hLockFile >= 0) && */(access (LockFileName, F_OK) != -1);
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` CreateTimeLog                                                             []             
//                                                                            []
// Создание и  инициализация файла time-лога. Возвращает true в случае успеха.
bool CreateTimeLog(void)
{
	bool bNeedHeader = (access (TimelogFileName, F_OK) == -1);

	if ((hTimelog = fopen(TimelogFileName	,"a+b")) == NULL) {
		return false;
	}

	if (bNeedHeader)	{
		fputs (
 			"<html><head><META HTTP-EQUIV='expires' CONTENT='0'>\n"
			"<meta http-equiv='Pragma' content='no-cache'>\n"
			"<title>4me.ru: Execution timing log</title></head>\n"
			"<body topmargin=20 bgcolor='#ddddee'>\n", 
			hTimelog);
	}


	fprintf(hTimelog,	
		"<table align='center' bgcolor='#c0c0c0' cellspacing='1' cellpadding='1' border=1'>\n"
		"<tr><td colspan='4'><P align=center><FONT face='Verdana' size=4>"
		"<b>4me.ru: Execution timing log.<BR>Session starts at %s</b></FONT></P></td></tr>\n",
		 ctime(&time_0));
	
	fputs (
		"<tr><td><P align=center><b>&nbsp;Function name&nbsp;</b></P></td>\n"
		"<td><P align=center><b>&nbsp;Duration, mcsec&nbsp;</b></P></td>\n"
		"<td><P align=center><b>&nbsp;Ops per second&nbsp;</b></P></td>\n"
		"<td><P align=center><b>&nbsp;Timestamp&nbsp;</b></P></td></tr>\n",
		hTimelog);

	fflush (hTimelog);

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` PrintTimeLog                                                              []            
//                                                                            []
// Вывод в лог информации о времени исполнения функций
void PrintTimeLog(const char *pFuncName, long MicrosecDiff)
{
	return;
	
	if (access (TimelogFileName, F_OK) == -1)
	{
		if (hTimelog != NULL)
		{
			fclose (hTimelog);
			hTimelog = NULL;
		}

		CreateTimeLog ();
	}

	fprintf(hTimelog, "<tr><td>&nbsp;%s&nbsp;</td><td align=right>&nbsp;%li&nbsp;</td><td align=right>&nbsp;%li&nbsp;</td><td>&nbsp;%s&nbsp;</td></tr>\n",
		pFuncName ? pFuncName : "Error",
		MicrosecDiff,
		MicrosecDiff ? (1000*1000 / MicrosecDiff) : 0L,
		ctime (&time_0));

//	fflush (hTimelog);

	return;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` CloseTimeLog                                                              []            
//                                                                            []
// Закрытие файла time-лога.
void CloseTimeLog(void)
{
	if (hTimelog == NULL) {
		return;
	}
	fputs (
		"</TABLE><BR>\n\n\n",
		hTimelog);

	fclose (hTimelog);
	hTimelog = NULL;
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
[]` ReceiveHeader                                                             []             
[]                                                                            []
[]____________________________________________________________________________*/
bool	ReceiveHeader (int SocketID /*Must be already accepted!*/, REQUEST_HEADER	*pHeader)
{
//	bzero (pHeader, sizeof (REQUEST_HEADER));

	static fd_set	read_fd_set;
	FD_ZERO	(&read_fd_set);
	FD_SET	(SocketID, &read_fd_set);

	static timeval ReadTimeout;
	ReadTimeout.tv_sec = OBS_READ_TIMEOUT / 1000000;
	ReadTimeout.tv_usec= OBS_READ_TIMEOUT % 1000000;

	int Status = select (SocketID+1, &read_fd_set, NULL, NULL, &ReadTimeout);

	if (Status < 0)
	{
	// System error 
		perror ("\nReceiveHeader(): ");
		return false;
	}
	else if (Status == 0)
	{
	// timeout
		fprintf (OBS_ERROR_LOG, "ReceiveHeader(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &read_fd_set))) {
		fprintf (OBS_ERROR_LOG, "\n* * * * * * * * * * * * * *\nReceiveHeader(): select() has unexpected behaviour (Status=%d) !\n* * * * * * * * * * * * * *\n", Status);
		return false;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ready to read
	ssize_t nBytesRead = readn(SocketID, pHeader, sizeof (struct REQUEST_HEADER));

	if (nBytesRead == sizeof (struct REQUEST_HEADER)) {// everything's alright
		return true;		
	}

	if (nBytesRead < 0)	{										// system error
		perror ("ReceiveHeader(): ");
		return false;
	}

// получено мало данных
	fprintf (OBS_ERROR_LOG,
				"\nReceiveHeader(): Only %lu of %lu header bytes were received.\n",
				nBytesRead,
				sizeof (struct REQUEST_HEADER));

	return false;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CloseConnection                                                           []               
[]                                                                            []
[]____________________________________________________________________________*/
bool CloseConnection (int SocketID)
{
/*	int 	ShutDownResult = shutdown	(SocketID, 2);
	if (ShutDownResult != 0) {
		fprintf(OBS_ERROR_LOG, "CloseConnection::shutdown(): errno=%s.\n",
			errno == EBADF ? "EBADF" : errno == ENOTSOCK ? "ENOTSOCK" : errno==ENOTCONN ? "ENOTCONN" : "Unknown");
		perror ("");
	}*/
	int CloseResult		= close		(SocketID);
	if (CloseResult != 0)
	{
		fprintf(OBS_ERROR_LOG,
			"CloseConnection::close(): errno=%s.\n",
			errno == EBADF ? "EBADF" : errno == EINTR ? "EINTR" : "Unknown");
		perror ("");
	}
	return /*(ShutDownResult==0) && */(CloseResult==0);
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ReadDataBlock                                                             []             
[]                                                                            []
[]____________________________________________________________________________*/
bool	ReadDataBlock (int SocketID, char *pDataBuffer, ssize_t DataBlockSize)
{
	static fd_set	read_fd_set;
	FD_ZERO	(&read_fd_set);
	FD_SET	(SocketID, &read_fd_set);

	static timeval ReadTimeout;
	ReadTimeout.tv_sec = OBS_READ_TIMEOUT / 1000000;
	ReadTimeout.tv_usec= OBS_READ_TIMEOUT % 1000000;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Check readiness
	int Status = select (SocketID+1, &read_fd_set, NULL, NULL, &ReadTimeout);
	if (Status < 0)
	{
	// System error 
		perror ("\nReadDataBlock(): ");
		return false;
	}
	else if (Status == 0)
	{
	// timeout
		fprintf (OBS_ERROR_LOG,
					"ReadDataBlock(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &read_fd_set)))
	{
		fprintf (OBS_ERROR_LOG,
					"\n"
					"* * * * * * * * * * * * * *\n"
					"WriteDataBlockAndHeader(): select() has unexpected behaviour (Status=%d) !\n"
					"* * * * * * * * * * * * * *\n",
					Status);
		return false;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ready to read
	ssize_t nBytesRead = readn(SocketID, pDataBuffer, DataBlockSize);

	if (nBytesRead == DataBlockSize) {					// everything's alright
		return true;		
	}

	if (nBytesRead < 0)	{									// system error
		perror ("\nReadDataBlock(): ");
		return false;
	}

// получено мало данных
	fprintf (OBS_ERROR_LOG,
				"\nReadDataBlock(): Only %lu of %lu data bytes were received.\n",
				nBytesRead,
				DataBlockSize);

	return false;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` WriteDataBlockAndHeader                                                   []
[]                                                                            []
[]____________________________________________________________________________*/
bool WriteDataBlockAndHeader (int SocketID, const REQUEST_HEADER* pHeader, void *pDataBuffer)
{
	static fd_set	write_fd_set;
	FD_ZERO	(&write_fd_set);
	FD_SET	(SocketID, &write_fd_set);

	static timeval WriteTimeout;
	WriteTimeout.tv_sec = OBS_WRITE_TIMEOUT / 1000000;
	WriteTimeout.tv_usec= OBS_WRITE_TIMEOUT % 1000000;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Check readiness
	int Status = select (SocketID+1, NULL, &write_fd_set, NULL, &WriteTimeout);
	if (Status < 0)
	{
	// System error 
		perror ("\nWriteDataBlockAndHeader(): ");
		return false;
	}
	else if (Status == 0)
	{
	// timeout
		fprintf (OBS_ERROR_LOG,
					"WriteDataBlockAndHeader(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &write_fd_set)))
	{
		fprintf (OBS_ERROR_LOG,
					"\n"
					"* * * * * * * * * * * * * *\n"
					"WriteDataBlockAndHeader(): select() has unexpected behaviour (Status=%d) !\n"
					"* * * * * * * * * * * * * *\n",
					Status);
		return false;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ready to Write

// Send header
	ssize_t	nBytesWritten;
	//nBytesWritten = writen (SocketID, pHeader, sizeof (REQUEST_HEADER));

	nBytesWritten = write (SocketID, pHeader, sizeof (REQUEST_HEADER));

	if (nBytesWritten != sizeof (REQUEST_HEADER))
	{
		if (nBytesWritten < 0)
		{
			perror ("\nWriteDataBlockAndHeader::send(header): ");
		}
		else
		{
			fprintf(OBS_ERROR_LOG, "WriteDataBlockAndHeader(): Only %lu byte of %lu was sent.\n", nBytesWritten, sizeof (REQUEST_HEADER));
		}

		return false;
	}
// Send data
	nBytesWritten = writen (SocketID, pDataBuffer, pHeader->DataBlockSize);
	if (nBytesWritten != pHeader->DataBlockSize)
	{
		if (nBytesWritten < 0)
		{
			perror ("\nWriteDataBlockAndHeader::send(data): ");
		}
		else
		{
			fprintf(OBS_ERROR_LOG,
						"WriteDataBlockAndHeader(): Only %lu byte of %lu was sent.\n",
						nBytesWritten,
						pHeader->DataBlockSize);
		}

		return false;
	}

	return true;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SplitPlainDataBlock                                                       []                   
[]                                                                            []
[]____________________________________________________________________________*/
bool SplitPlainDataBlock(char * pData, char **ppFunction, char **ppInputArgs, char **ppOutputArgs)
{
	*ppFunction		= NULL;
	*ppInputArgs	= NULL;
	*ppOutputArgs	= NULL;

	if(pData == NULL)			return false;

// pData дожен начинаться с имени функции, которое должно начинаться с буквы.
	if (isalpha (*pData) == 0)	return false;
	*ppFunction = pData;

// Ищем разделитель функционального и входного блоков.
	*ppInputArgs = strchr(pData, QUERYBLOCK_SEP_CHAR);

	if((*ppInputArgs) != NULL)			// нашли
	{ 
		**ppInputArgs = 0;				// заменим разделитель на 0
		(*ppInputArgs)++;					// входные аргументы начинаются после 0
		
	// Ищем разделитель входного и выходного блоков
		*ppOutputArgs = strchr(*ppInputArgs, QUERYBLOCK_SEP_CHAR);

		if((*ppOutputArgs) != NULL) 	// нашли
		{
			**ppOutputArgs = 0;			// заменим разделитель на 0
			(*ppOutputArgs)++;			// выходные аргументы начинаются после 0

			return true;
		}
	}

	return false;							// ошибка
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SigTermHandler                                                            []              
[]                                                                            []
[]____________________________________________________________________________*/
void SigTermHandler (int)
{
	gBaseMode = BM_STOPPING;
	return;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBServer_MainLoop                                                         []
[]                                                                            []
[]____________________________________________________________________________*/
int OBServer_MainLoop (void)
{
	REQUEST_HEADER			RequestHeader_Server;
	REQUEST_HEADER			RequestHeader_Client;

	time_t					OldTime			= 0;
	time_t					CurTime			= 0;
	double					MicrosecDiff	= 0.0;
								
	int						ListenSocketID =	-1;
	int						Status			=	-1;
								
	fd_set					read_fd_set;

	struct sockaddr_in	PeerInfo;
	int						PeerInfoSize;
	int						PeerSocketID;
								
	timeval					AcceptTimeout;
	AcceptTimeout.tv_sec = OBS_ACCEPT_TIMEOUT / 1000000;
	AcceptTimeout.tv_usec= OBS_ACCEPT_TIMEOUT % 1000000;

	time (&time_0);
	bzero (InterfaceHistory_Reset,	OBS_HISTORY_SIZE*sizeof (time_t));
	bzero (InterfaceHistory_Count,	OBS_HISTORY_SIZE*sizeof (double));
	bzero (InterfaceHistory_AveTime,	OBS_HISTORY_SIZE*sizeof (double));
	bzero (Timer_Count,					OBS_HISTORY_SIZE*sizeof (double));
	bzero (Timer_AveTime,				OBS_HISTORY_SIZE*sizeof (double));
	InterfaceHistory_Pos				= 0		;

	AveReset_Read						= time_0	;
	AveReset_OBServer_Interface	= time_0	;
	AveReset_Write						= time_0	;
	AveReset_Timer						= time_0	;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создать lock-файл:
	if (LockFileExists())
	{
		fprintf (OBS_ERROR_LOG, "Base locked.\n");
		gBaseMode = BM_STOPPING;
		return 1;
	}
	
	if (!CreateLockFile())
	{
		fprintf (OBS_ERROR_LOG, "Error creating lock file.\n");
		gBaseMode = BM_STOPPING;
		return 2;
	}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создать лог времени выполнения функций:
	if (!CreateTimeLog())
	{
		fprintf (OBS_ERROR_LOG, "Error creating time log.\n");
		gBaseMode = BM_STOPPING;
		return 3;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Создать серверный сокет
	ListenSocketID = socket (PF_INET, SOCK_STREAM, 0);
	if (ListenSocketID < 0)
	{
		perror ("\nOBServer_MainLoop::socket(): ");
		gBaseMode = BM_STOPPING;
		CloseTimeLog	();
		return 4;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Привязать сокет к порту
	struct	sockaddr_in	ListenAddr;
	bzero (&ListenAddr, sizeof (ListenAddr));
	ListenAddr.sin_family		= AF_INET;
	ListenAddr.sin_port			= htons (OBS_LISTEN_PORT);
	ListenAddr.sin_addr.s_addr	= htonl (INADDR_ANY);

	Status = bind (ListenSocketID, (struct sockaddr*)&ListenAddr, sizeof (ListenAddr));
	if (Status != 0)
	{
		perror ("\nOBServer_MainLoop::bind(): ");
		gBaseMode = BM_STOPPING;
		close (ListenSocketID);
		CloseTimeLog	();
		return 5;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Инициализировать сокетную очередь:
	Status = listen (ListenSocketID, OBS_MAX_BACKLOG_NUM);
	if (Status != 0)
	{
		perror ("\nOBServer_MainLoop::listen(): ");
		close (ListenSocketID);
		CloseTimeLog	();
		return 6;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Установка обработчиков сигналов:
	signal	(SIGPIPE,	SIG_IGN);
	signal	(SIGHUP,		SIG_IGN);
	signal	(SIGTERM,	SigTermHandler);
	signal	(SIGINT,		SigTermHandler);
	signal	(SIGKILL,	SigTermHandler);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	fputs("\nSockets initialized. Listening loop started.\n", OBS_ERROR_LOG);
	

//----------------------------------------------------------------------------[]
// Главный цикл
	for (;;)
	{
		time (&time_0);

	// Проверить возможность принятия вызова от клиента:
		FD_ZERO	(&read_fd_set);
		FD_SET	(ListenSocketID, &read_fd_set);
		Status = select (ListenSocketID+1, &read_fd_set, NULL, NULL, &AcceptTimeout);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// Error
		if (Status < 0)
		{
			perror ("\nOBServer_MainLoop::select(): ");
		}
		else if (Status > 1)
		{
			fprintf(OBS_ERROR_LOG,
					"\n"
					"* * * * * * * * * * * * * *\n"
					"WriteDataBlockAndHeader(): select() has unexpected behaviour (Status=%d) !\n"
					"* * * * * * * * * * * * * *\n",
					Status);
		}
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// Timeout - база свободна. idle ...
	#ifdef OBS_SLEEP_TIME
		else if (Status == 0)
		{
			usleep (OBS_SLEEP_TIME);
		}
	#endif
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// Ready for accept
		else if (Status == 1)
		{
		// Accept a connection:
			PeerSocketID = accept (ListenSocketID, (struct sockaddr*)&PeerInfo, (socklen_t*)&PeerInfoSize);

			if (PeerSocketID < 0)
			{
				perror ("\nOBServer_MainLoop::accept(): ");
				continue;
			}

/*			fprintf(OBS_ERROR_LOG, "\n  OBServer_MainLoop: Accepted connection from %s:%hd.",
				inet_ntoa (PeerInfo.sin_addr),
				ntohs (PeerInfo.sin_port));
*/

		// Получить заголовок:
			// bzero (&RequestHeader_Server, sizeof (RequestHeader_Server));
			if (!ReceiveHeader (PeerSocketID, &RequestHeader_Server))
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: Error receiving header.\n");
				CloseConnection (PeerSocketID);
				continue;
			}

		// Разобрать заголовок:
			if (strncmp (RequestHeader_Server.Signature, RequestSignature, RequestSignatureSize) != 0)
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: Invalid header signature.\n");
				CloseConnection (PeerSocketID);
				continue;
			}

		//* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Размер блока данных:
			if (RequestHeader_Server.DataBlockSize > OBS_MAX_DATABLOCK_SIZE)
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: Data block too large: %lu.\n", RequestHeader_Server.DataBlockSize);
				CloseConnection (PeerSocketID);
				continue;
			}

		//`* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Команда останова:
			if (RequestHeader_Server.Command == COMMAND_SERVER_STOP)	
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: STOP Command received.\n");
				CloseConnection (PeerSocketID);
				gBaseMode = BM_STOPPING;
				break;
			}
		//`* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Команда получения статистики:
			else if (RequestHeader_Server.Command == COMMAND_SERVER_GETSTATS)
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: GETSTATS Command received.\n");
			// Сформировать ответ:
				char StatAnswer[1024];
				snprintf (StatAnswer, 1024,
					"Count_Read=%.2f&Count_Problem=%.0f&Count_Write=%.0f&Count_Timer=%.0f&"
					"Ave_Read=%.2f&Ave_Problem=%.2f&Ave_Write=%.2f&Ave_Timer=%.2f&"
					"AveReset_Read=%s&AveReset_Problem=%s&AveReset_Write=%s&AveReset_Timer=%s",
					Count_Read, Count_OBServer_Interface, Count_Write,	Count_Timer,
					Ave_Read,	Ave_OBServer_Interface,	Ave_Write,		Ave_Timer,
					ctime(&AveReset_Read),ctime(&AveReset_OBServer_Interface),ctime(&AveReset_Write),ctime(&AveReset_Timer));

			// Подготовить заголовок для ответа:
				// bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
				memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
				RequestHeader_Client.DataBlockSize			= strlen (StatAnswer);
				RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
				RequestHeader_Client.Command					= COMMAND_CLIENT_GETSTATS;
				RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

			// Отослать ответ клиенту:
				if (!WriteDataBlockAndHeader(
							PeerSocketID,
							&RequestHeader_Client,
							&StatAnswer))
				{
					fprintf(OBS_ERROR_LOG,
								"OBServer_MainLoop: Timeout or error sending stats data of size %lu.\n",
								RequestHeader_Client.DataBlockSize);
				}

			// Закрыть соединение и освободить ресурсы:
				CloseConnection (PeerSocketID);
			}
		//`* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Команда сброса статистики:
			else if (RequestHeader_Server.Command == COMMAND_SERVER_RESETSTATS)
			{
				fprintf(OBS_ERROR_LOG, "OBServer_MainLoop: RESETSTATS Command received.\n");

			// Запишем производительность в history:
				InterfaceHistory_Reset	[InterfaceHistory_Pos] = time_0;
				InterfaceHistory_Count	[InterfaceHistory_Pos] = Count_OBServer_Interface;
				InterfaceHistory_AveTime[InterfaceHistory_Pos] = Ave_OBServer_Interface;
				Timer_Count					[InterfaceHistory_Pos] = Count_Timer;
				Timer_AveTime				[InterfaceHistory_Pos] = Ave_Timer;

			// Переведём указатель history на следующую позицию:
				InterfaceHistory_Pos++;
				if (InterfaceHistory_Pos >= OBS_HISTORY_SIZE) {
					InterfaceHistory_Pos = 0;
				}

			// Сбросим счетчики:	
				AveReset_Read					= time_0;	AveReset_Write	= time_0;
				Count_Read						= 0.0;		Count_Write		= 0.0;
				Ave_Read							= 0.0;		Ave_Write		= 0.0;

				AveReset_OBServer_Interface= time_0;	AveReset_Timer	= time_0;
				Count_OBServer_Interface	= 0.0;		Count_Timer		= 0.0;
				Ave_OBServer_Interface		= 0.0;		Ave_Timer		= 0.0;

			// Сформировать ответ:
				char StatAnswer[1024];
				snprintf (StatAnswer, 1024,
					"Counters were reset succesfully at %s",
					ctime(&time_0));

			// Подготовить заголовок для ответа:
				// bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
				memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
				RequestHeader_Client.DataBlockSize			= strlen (StatAnswer);
				RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
				RequestHeader_Client.Command					= COMMAND_CLIENT_RESETSTATS;
				RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

			// Отослать ответ клиенту:
				if (!WriteDataBlockAndHeader(
						PeerSocketID,
						&RequestHeader_Client,
						&StatAnswer))
				{
					fprintf(
						OBS_ERROR_LOG,
						"OBServer_MainLoop: Timeout or error sending stats reset data of size %lu.\n",
						RequestHeader_Client.DataBlockSize);
				}

			// Закрыть соединение и освободить ресурсы:
				CloseConnection (PeerSocketID);
			}
		//`* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Команда получения history статистики:
			else if (RequestHeader_Server.Command == COMMAND_SERVER_HISTORYSTATS)
			{
				fprintf(
					OBS_ERROR_LOG,
					"OBServer_MainLoop: HISTORYSTATS Command received.\n");

			// Сформировать ответ:
				const int	StatAnswerLen = 10240;
				char	StatAnswer[StatAnswerLen];
				int	l, histPos, strPos;

				bzero (StatAnswer, StatAnswerLen);

				histPos	= InterfaceHistory_Pos;
				strPos	= 0;

				for (l = 0; l < OBS_HISTORY_SIZE; l++)
				{
					if (InterfaceHistory_Reset [histPos] != 0) 
					{
						snprintf (StatAnswer+strPos, StatAnswerLen-strPos-1,
							"Times[]=%s&"
							"Interface_Count[]=%.2f&"
							"Interface_AveTime[]=%.2f&"
							"Timer_Count[]=%.2f&"
							"Timer_AveTime[]=%.2f&",
							ctime(&InterfaceHistory_Reset [histPos]),
							InterfaceHistory_Count			[histPos],
							InterfaceHistory_AveTime		[histPos],
							Timer_Count							[histPos],
							Timer_AveTime						[histPos]);
					}

					histPos++;
					if (histPos >= OBS_HISTORY_SIZE) {
						histPos = 0;
					}
					
					strPos = strlen (StatAnswer);
				}

			// Подготовить заголовок для ответа:
				// bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
				memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
				RequestHeader_Client.DataBlockSize			= strlen (StatAnswer);
				RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
				RequestHeader_Client.Command					= COMMAND_CLIENT_HISTORYSTATS;
				RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

			// Отослать ответ клиенту:
				if (!	WriteDataBlockAndHeader (
							PeerSocketID,
							&RequestHeader_Client,
							&StatAnswer))
				{
					fprintf(
						OBS_ERROR_LOG,
						"OBServer_MainLoop: Timeout or error sending stats history data of size %lu.\n",
						RequestHeader_Client.DataBlockSize);
				}

			// Закрыть соединение и освободить ресурсы:
				CloseConnection (PeerSocketID);
			}
		//`* * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// Команда запроса к БД:
			else if (RequestHeader_Server.Command == COMMAND_SERVER_DBREQUEST)
			{
//					TIMECHECK_START(Read);
	
			// Считать блок данных
				char * pDataBuffer = new char [RequestHeader_Server.DataBlockSize + 1];

				if (!ReadDataBlock (PeerSocketID, pDataBuffer, RequestHeader_Server.DataBlockSize))
				{
					fprintf(
						OBS_ERROR_LOG,
						"OBServer_MainLoop: Timeout or error reading data block of size %lu.\n",
						RequestHeader_Server.DataBlockSize);
					FREE_PTR (pDataBuffer);
					CloseConnection (PeerSocketID);
					continue;
				}

				pDataBuffer[RequestHeader_Server.DataBlockSize] = 0;

			// Разобрать блок данных
				char *pFunction		= NULL;
				char *pInputArgs		= NULL;
				char *pOutputArgs		= NULL;
				void *pData				= NULL;

				switch (RequestHeader_Server.DataType)
				{
					case DATATYPE_SERVER_PLAIN:
						if (!SplitPlainDataBlock(
								pDataBuffer,
								&pFunction,
								&pInputArgs,
								&pOutputArgs))
						{
							fprintf(
								OBS_ERROR_LOG,
								"OBServer_MainLoop: Error parsing data block of size.\n");
							FREE_PTR (pDataBuffer);
							CloseConnection (PeerSocketID);
						}
						break;

					default:
						fprintf(
							OBS_ERROR_LOG,
							"OBServer_MainLoop: Unsupported data type %d.\n",
							RequestHeader_Server.DataType);
							
						FREE_PTR (pDataBuffer);
						CloseConnection (PeerSocketID);
				}

			//	fprintf(OBS_ERROR_LOG, "\n  Received: %s(%s, %s).\n", pFunction, pInputArgs, pOutputArgs);
				fprintf(OBS_ERROR_LOG, " %s ()\n", pFunction);

//					TIMECHECK_END (Read);


			// Вызвать проблемную функцию
				if (pDataBuffer != NULL)		// если не было проблем с разбором данных
				{
					TIMECHECK_START		(OBServer_Interface);

					OBServer_Interface	(pFunction, pInputArgs, pOutputArgs, &pData);

					TIMECHECK_END			(OBServer_Interface);

					PrintTimeLog			(pFunction, (long)MicrosecDiff);// напечатать в time-лог.
				}

			// Удаление буфера с принятым запросом:
				FREE_PTR (pDataBuffer);

			// Подготовить заголовок для ответа клиенту:
//					TIMECHECK_START(Write);
				// bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
				memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
				RequestHeader_Client.DataBlockSize			= ((int*)pData) [0];
				RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
				RequestHeader_Client.Command					= COMMAND_CLIENT_DBANSWER;
				RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

			// Отослать ответ клиенту:
				if (!WriteDataBlockAndHeader (PeerSocketID, &RequestHeader_Client, pData))
				{
					fprintf(
						OBS_ERROR_LOG,
						"OBServer_MainLoop: Timeout or error writing data block of size %lu.\n",
						RequestHeader_Client.DataBlockSize);
				}

			//	fprintf(OBS_ERROR_LOG, "\n  Answer of length %lu sended.\n", RequestHeader_Client.DataBlockSize);
				fputs(" Done.\n", OBS_ERROR_LOG);
				
			// Закрыть соединение и освободить ресурсы:
				CloseConnection (PeerSocketID);
				OBServer_Interface_Free(&pData);

//					TIMECHECK_END(Write);

			} // end if (RequestHeader_Server.Command == COMMAND_SERVER_DBREQUEST)
			else 
			{
				fprintf(
					OBS_ERROR_LOG,
					"OBServer_MainLoop: Unsupported command (%d).\n",
					RequestHeader_Server.Command);
				CloseConnection (PeerSocketID);
				continue;
			}
		
		} // end if (Status == 1)
	//----------------------------------------------------------------------------[]
	// Проверка на команду останова:
		if (gBaseMode == BM_STOPPING) {
			fputs (
				"\nReceived stop command. Gracefully terminating...\n",
				OBS_ERROR_LOG);
/*			fprintf (OBS_ERROR_LOG,	
						"\nAveReset_Read:\t%sAveReset_OBServer_Interface:\t%sAveReset_Write:\t%.0fAveReset_Timer:\t%.0f\n"
						"Count_Read:\t%.0f\nCount_OBServer_Interface:\t%.0f\nCount_Write:\t%.0f\nCount_Timer:\t%.0f\n"
						"Ave_Read:\t%.0f\nAve_OBServer_Interface:\t%.0f\nAve_Write:\t%.0f\nAve_Timer:\t%.0f\n",
						ctime(&AveReset_Read),ctime(&AveReset_OBServer_Interface),ctime(&AveReset_Write),ctime(&AveReset_Timer),
						Count_Read, Count_OBServer_Interface, Count_Write,	Count_Timer,
						Ave_Read,	Ave_OBServer_Interface,	Ave_Write,		Ave_Timer);
*/			break;
		}

	//----------------------------------------------------------------------------[]
	// Таймер и чистка кеша.
		time (&time_0);
		if (time_0 >= OldTime + OBS_TIMER_INTERVAL)
		{
			TIMECHECK_START(Timer);

			fprintf			(OBS_ERROR_LOG, " (*)-");
			OBServer_OnTimer		();
			fprintf			(OBS_ERROR_LOG, "-(*)\n");
			OldTime = time_0;

			TIMECHECK_END	(Timer);
		}

	
	}	// конец главного цикла

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Закрыть открытые сокеты, файлы, освободить ресурсы и т.п.:
	close (ListenSocketID);
	CloseTimeLog	();

	return 0;
}
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
#else	// Windows
void OBServer_RemoveLock()
{
	return;
}
//----------------------------------------------------------------------------[]

#endif
                                                                    
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/
