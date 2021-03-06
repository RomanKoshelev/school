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
[] Description:     ��������� ����� ����.                                     []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

//----------------------------------------------------------------------------[]
// ���������� ����������, ��������������� � time(NULL)
// ����� ������ ������� ���������� �������.
#include <time.h>
time_t	TIME_NULL = 0;
//----------------------------------------------------------------------------[]
#ifndef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/types.h>
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
[]` ������������                                                              []
[]                                                                            []
[]____________________________________________________________________________*/

// ��������� ��������� �������:
#define	RequestSignature				"AVRKAVRK"	// ������� ��������� �������.
#define	RequestSignatureSize			8				// ������ ������� ��������� �������.
												
#define	DATATYPE_SERVER_PLAIN		1000			// ��� ������: ������ � ������� �� ���������� ���������.
#define	DATATYPE_SERVER_BINARY		1100			// ��� ������: ������ � ������� �� ��������� ���������.
#define	DATATYPE_CLIENT_PLAIN		2000			// ��� ������: ����� ������� �� ���������� ���������.
#define	DATATYPE_CLIENT_BINARY		2100			// ��� ������: ����� ������� �� ��������� ���������.
												
#define	ENCRIPTION_NONE				1000			// ��� ����������: ��� ����������.

#define	COMMAND_SERVER_DBREQUEST	1000			// ������� �������:	������ � ��.
#define	COMMAND_SERVER_STOP			1100			// ������� �������:	�������.
#define	COMMAND_SERVER_GETSTATS		1200			// ������� �������:	�������� ����������.
#define	COMMAND_CLIENT_ANSWER		10000			// ������� �������:	����� �� ������ � ��.
#define	COMMAND_CLIENT_GETSTATS		10200			// ������� �������:	����� �� ������ ����������.
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[]
void	OBServer_Interface			(const char*,const char*,const char*,void**);
void	OBServer_Interface_Free		(void**);
void	OBServer_OnTimer				(void);
//----------------------------------------------------------------------------[]


//______________________________________________________________________________
//                                                                            []
//` REQUEST_HEADER                                                            []              
//                                                                            []
// ��������� �������
struct	REQUEST_HEADER
{
	char				Signature[RequestSignatureSize];	// �������
	unsigned long	DataBlockSize;							// ����� ����� ������ ����� ���������
	unsigned long	CRC;										// ����������� ����� ����� ������.
	int				DataType;								// ��� ������: �����/��������
	int				DataEncriptionType;					// ������ ����������.
	int				Command;									// ������� �������.
	int				Reserved;								// ���������������.
};
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[]
// ������ ���� ������
#define	BM_WORKING		0
#define	BM_STOPPING		1
volatile	sig_atomic_t	gBaseMode			= BM_WORKING;
//----------------------------------------------------------------------------[]


//----------------------------------------------------------------------------[]
static	FILE*					hTimelog				= NULL;		// ���������� ����� time-����.
static	int					hLockFile			= -1;			// ���������� lock-�����.
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[]
// ��������� ��� ������� ������� ����������
static	struct timeval		tStart;
static	struct timeval		tEnd;

static	double				Count_Read							= 0.0;
static	double				Count_OBServer_Interface		= 0.0;
static	double				Count_Write							= 0.0;
static	double				Count_Timer							= 0.0;
																			
static	double				Ave_Read								= 0.0;
static	double				Ave_OBServer_Interface			= 0.0;
static	double				Ave_Write							= 0.0;
static	double				Ave_Timer							= 0.0;
																			
static	time_t				AveReset_Read						= 0;
static	time_t				AveReset_OBServer_Interface	= 0;
static	time_t				AveReset_Write						= 0;
static	time_t				AveReset_Timer						= 0;

//----------------------------------------------------------------------------[]
#define	TIMECHECK_START(Type)																\
		gettimeofday	(&tStart,	NULL)
//----------------------------------------------------------------------------[]
#define	TIMECHECK_END(Type)																	\
		gettimeofday	(&tEnd,	NULL);														\
		if (Count_##Type < 1.0 || Count_##Type > 1000000.0) {							\
			AveReset_##Type= TIME_NULL;														\
			Count_##Type	= 0.0;																\
			Ave_##Type		= 0.0;																\
		}																								\
		Count_##Type		+= 1.0;																\
		MicrosecDiff		= (tEnd.tv_usec - tStart.tv_usec								\
									+ 1000000.0 * (tEnd.tv_sec - tStart.tv_sec));		\
		Ave_##Type			= ((Count_##Type-1.0) * Ave_##Type + MicrosecDiff)		\
									/ Count_##Type
//----------------------------------------------------------------------------[]




//______________________________________________________________________________
//                                                                            []
//` CreateLockFile                                                            []              
//                                                                            []
// �������� lock-�����: ���������� true  � ������ ������
bool CreateLockFile(void)
{
	if (hLockFile >= 0) {
		return false;
	}
	
	if ((hLockFile = open(LockFileName, O_CREAT|O_RDWR|O_EXLOCK|O_NONBLOCK)) < 0) {//S_IWGRP|S_IWOTH
		return false;
	}

	if (write(hLockFile, ctime(&TIME_NULL), 25) == -1) { // "...returns a pointer to a 26-character string of the form: Thu Nov 24 18:22:48 1986\n\0"
		close (hLockFile);
		hLockFile = -1;
		return false;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` RemoveLockFile                                                            []              
//                                                                            []
// �������� lock-�����: ���������� true  � ������ ������
bool RemoveLockFile(void)
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
// �������� ������������� lock-�����
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
// �������� �  ������������� ����� time-����. ���������� true � ������ ������.
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
		 ctime(&TIME_NULL));
	
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
// ����� � ��� ���������� � ������� ���������� �������
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
		ctime (&TIME_NULL));

//	fflush (hTimelog);

	return;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` CloseTimeLog                                                              []            
//                                                                            []
// �������� ����� time-����.
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
	bzero (pHeader, sizeof (REQUEST_HEADER));

	fd_set	read_fd_set;
	FD_ZERO	(&read_fd_set);
	FD_SET	(SocketID, &read_fd_set);

	timeval ReadTimeout;
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
		fprintf (stderr, "ReceiveHeader(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &read_fd_set))) {
		fprintf (stderr, "\n* * * * * * * * * * * * * *\nReceiveHeader(): select() has unexpected behaviour (Status=%d) !\n* * * * * * * * * * * * * *\n", Status);
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

// �������� ���� ������
	fprintf (stderr, "\nReceiveHeader(): Only %lu of %lu header bytes were received.\n", nBytesRead, sizeof (struct REQUEST_HEADER));
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
		fprintf(stderr, "CloseConnection::shutdown(): errno=%s.\n",
			errno == EBADF ? "EBADF" : errno == ENOTSOCK ? "ENOTSOCK" : errno==ENOTCONN ? "ENOTCONN" : "Unknown");
		perror ("");
	}
*/	int CloseResult		= close		(SocketID);
	if (CloseResult != 0) {
		fprintf(stderr, "CloseConnection::close(): errno=%s.\n",
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
	fd_set	read_fd_set;
	FD_ZERO	(&read_fd_set);
	FD_SET	(SocketID, &read_fd_set);

	timeval ReadTimeout;
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
		fprintf (stderr, "ReadDataBlock(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &read_fd_set))) {
		fprintf (stderr, "\n* * * * * * * * * * * * * *\nReadDataBlock(): select() has unexpected behaviour (Status=%d) !\n* * * * * * * * * * * * * *\n", Status);
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

// �������� ���� ������
	fprintf (stderr, "\nReadDataBlock(): Only %lu of %lu data bytes were received.\n", nBytesRead, DataBlockSize);
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
	fd_set	write_fd_set;
	FD_ZERO	(&write_fd_set);
	FD_SET	(SocketID, &write_fd_set);

	timeval WriteTimeout;
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
		fprintf (stderr, "WriteDataBlockAndHeader(): timeout expired.\n");
		return false;
	}

	if ((Status != 1) || (!FD_ISSET(SocketID, &write_fd_set))) {
		fprintf (stderr, "\n* * * * * * * * * * * * * *\nWriteDataBlockAndHeader(): select() has unexpected behaviour (Status=%d) !\n* * * * * * * * * * * * * *\n", Status);
		return false;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Ready to Write

// Send header
	ssize_t	nBytesWritten;
	nBytesWritten = writen (SocketID, pHeader, sizeof (REQUEST_HEADER));

	if (nBytesWritten != sizeof (REQUEST_HEADER))
	{
		if (nBytesWritten < 0)
		{
			perror ("\nWriteDataBlockAndHeader::send(header): ");
		}
		else
		{
			fprintf(stderr, "WriteDataBlockAndHeader(): Only %lu byte of %lu was sent.\n", nBytesWritten, sizeof (REQUEST_HEADER));
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
			fprintf(stderr, "WriteDataBlockAndHeader(): Only %lu byte of %lu was sent.\n", nBytesWritten, pHeader->DataBlockSize);
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

// pData ����� ���������� � ����� �������, ������� ������ ���������� � �����.
	if (isalpha (*pData) == 0)	return false;
	*ppFunction = pData;

// ���� ����������� ��������������� � �������� ������.
	*ppInputArgs = strchr(pData, QUERYBLOCK_SEP_CHAR);

	if((*ppInputArgs) != NULL)			// �����
	{ 
		**ppInputArgs = 0;				// ������� ����������� �� 0
		(*ppInputArgs)++;					// ������� ��������� ���������� ����� 0
		
	// ���� ����������� �������� � ��������� ������
		*ppOutputArgs = strchr(*ppInputArgs, QUERYBLOCK_SEP_CHAR);

		if((*ppOutputArgs) != NULL) 	// �����
		{
			**ppOutputArgs = 0;			// ������� ����������� �� 0
			(*ppOutputArgs)++;			// �������� ��������� ���������� ����� 0

			return true;
		}
	}

	return false;							// ������
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

	time (&TIME_NULL);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ������� lock-����:
	if (LockFileExists())
	{
		fprintf (stderr, "Base locked.\n");
		gBaseMode = BM_STOPPING;
		return 1;
	}
	
	if (!CreateLockFile())
	{
		fprintf (stderr, "Error creating lock file.\n");
		gBaseMode = BM_STOPPING;
		return 2;
	}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ������� ��� ������� ���������� �������:
	if (!CreateTimeLog())
	{
		fprintf (stderr, "Error creating time log.\n");
		gBaseMode = BM_STOPPING;
		RemoveLockFile ();
		return 3;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ������� ��������� �����
	ListenSocketID = socket (PF_INET, SOCK_STREAM, 0);
	if (ListenSocketID < 0)
	{
		perror ("\nOBServer_MainLoop::socket(): ");
		gBaseMode = BM_STOPPING;
		CloseTimeLog	();
		RemoveLockFile ();
		return 4;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ��������� ����� � �����
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
		RemoveLockFile ();
		return 5;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ���������������� �������� �������:
	Status = listen (ListenSocketID, OBS_MAX_BACKLOG_NUM);
	if (Status != 0)
	{
		perror ("\nOBServer_MainLoop::listen(): ");
		close (ListenSocketID);
		CloseTimeLog	();
		RemoveLockFile ();
		return 6;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ��������� ������������ ��������:
	signal	(SIGPIPE,	SIG_IGN);
	signal	(SIGHUP,		SIG_IGN);
	signal	(SIGTERM,	SigTermHandler);
	signal	(SIGINT,		SigTermHandler);
	signal	(SIGKILL,	SigTermHandler);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	fputs("\nSockets initialized. Listening loop started.\n", stderr);
	

//----------------------------------------------------------------------------[]
// ������� ����
	for (;;)
	{
	// ��������� ����������� �������� ������ �� �������:
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
			fprintf(stderr, "\n * * * * OBServer_MainLoop::select() has unexpected behaviour (Status=%d) !\n* * * * * * * * * * * * * *\n", Status);
		}
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// Timeout - ���� ��������. idle ...
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
			PeerSocketID = accept (ListenSocketID, (struct sockaddr*)&PeerInfo, &PeerInfoSize);

			if (PeerSocketID < 0)
			{
				perror ("\nOBServer_MainLoop::accept(): ");
				continue;
			}

/*			fprintf(stderr, "\n  OBServer_MainLoop: Accepted connection from %s:%hd.",
				inet_ntoa (PeerInfo.sin_addr),
				ntohs (PeerInfo.sin_port));
*/

		// �������� ���������:
			bzero (&RequestHeader_Server, sizeof (RequestHeader_Server));
			if (!ReceiveHeader (PeerSocketID, &RequestHeader_Server))
			{
				fprintf(stderr, "OBServer_MainLoop: Error receiving header.\n");
				CloseConnection (PeerSocketID);
				continue;
			}

		// ��������� ���������:
			if (strncmp (RequestHeader_Server.Signature, RequestSignature, RequestSignatureSize) != 0)
			{
				fprintf(stderr, "OBServer_MainLoop: Invalid header signature.\n");
				CloseConnection (PeerSocketID);
				continue;
			}

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			// ������ ����� ������:
				if (RequestHeader_Server.DataBlockSize > OBS_MAX_DATABLOCK_SIZE)
				{
					fprintf(stderr, "OBServer_MainLoop: Data block too large: %lu.\n", RequestHeader_Server.DataBlockSize);
					CloseConnection (PeerSocketID);
					continue;
				}

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			// ������� ��������:
				if (RequestHeader_Server.Command == COMMAND_SERVER_STOP)	
				{
					fprintf(stderr, "OBServer_MainLoop: STOP Command received.\n");
					CloseConnection (PeerSocketID);
					gBaseMode = BM_STOPPING;
					break;
				}
			// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			// ������� ��������� ����������:
				else if (RequestHeader_Server.Command == COMMAND_SERVER_GETSTATS)
				{
					fprintf(stderr, "OBServer_MainLoop: GETSTATS Command received.\n");
				// ������������ �����:
					char StatAnswer[1024];
					snprintf (StatAnswer, 1024,
						"Count_Read=%.2f&Count_Problem=%.0f&Count_Write=%.0f&Count_Timer=%.0f&"
						"Ave_Read=%.2f&Ave_Problem=%.2f&Ave_Write=%.2f&Ave_Timer=%.2f&"
						"AveReset_Read=%s&AveReset_Problem=%s&AveReset_Write=%s&AveReset_Timer=%s",
						Count_Read, Count_OBServer_Interface, Count_Write,	Count_Timer,
						Ave_Read,	Ave_OBServer_Interface,	Ave_Write,		Ave_Timer,
						ctime(&AveReset_Read),ctime(&AveReset_OBServer_Interface),ctime(&AveReset_Write),ctime(&AveReset_Timer));

				// ����������� ��������� ��� ������:
					bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
					memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
					RequestHeader_Client.DataBlockSize			= strlen (StatAnswer);
					RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
					RequestHeader_Client.Command					= COMMAND_CLIENT_GETSTATS;
					RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

				// �������� ����� �������:
					if (!WriteDataBlockAndHeader (PeerSocketID, &RequestHeader_Client, &StatAnswer))
					{
						fprintf(stderr, "OBServer_MainLoop: Timeout or error sending stats data of size %lu.\n", RequestHeader_Client.DataBlockSize);
					}

					// ������� ���������� � ���������� �������:
					CloseConnection (PeerSocketID);
				}
			// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			// ������� ������� � ��:
				else if (RequestHeader_Server.Command == COMMAND_SERVER_DBREQUEST)
				{
//					TIMECHECK_START(Read);
		
				// ������� ���� ������
					char * pDataBuffer = new char [RequestHeader_Server.DataBlockSize + 1];

					if (!ReadDataBlock (PeerSocketID, pDataBuffer, RequestHeader_Server.DataBlockSize))
					{
						fprintf(stderr,
							"OBServer_MainLoop: Timeout or error reading data block of size %lu.\n",
							RequestHeader_Server.DataBlockSize);
						delete[]	pDataBuffer;
						CloseConnection (PeerSocketID);
						continue;
					}

					pDataBuffer[RequestHeader_Server.DataBlockSize] = 0;

				// ��������� ���� ������
					char *pFunction		= NULL;
					char *pInputArgs		= NULL;
					char *pOutputArgs		= NULL;
					void *pData				= NULL;

					switch (RequestHeader_Server.DataType)
					{
						case DATATYPE_SERVER_PLAIN:
							if (!SplitPlainDataBlock (pDataBuffer, &pFunction, &pInputArgs, &pOutputArgs))
							{
								fprintf(stderr, "OBServer_MainLoop: Error parsing data block.\n");
								delete[]	pDataBuffer;
								pDataBuffer = NULL;
								CloseConnection (PeerSocketID);
							}
							break;

						default:
							fprintf(stderr, "OBServer_MainLoop: Unsupported data type %d.\n", RequestHeader_Server.DataType);
							delete[]	pDataBuffer;
							pDataBuffer = NULL;
							CloseConnection (PeerSocketID);
					}

				//	fprintf(stderr, "\n  Received: %s(%s, %s).\n", pFunction, pInputArgs, pOutputArgs);
					fprintf(stderr, " %s ()\n", pFunction);

//					TIMECHECK_END (Read);


					time (&TIME_NULL);

				// ������� ���������� �������
					if (pDataBuffer != NULL)		// ���� �� ���� ������� � �������� ������
					{
						TIMECHECK_START		(OBServer_Interface);

						OBServer_Interface	(pFunction, pInputArgs, pOutputArgs, &pData);

						TIMECHECK_END			(OBServer_Interface);

						PrintTimeLog			(pFunction, (long)MicrosecDiff);// ���������� � time-���.
					}

				// �������� ������ � �������� ��������:
					if (pDataBuffer != NULL)
					{
						delete[]	pDataBuffer;
						pDataBuffer = NULL;
					}

				// ����������� ��������� ��� ������ �������:
//					TIMECHECK_START(Write);
					bzero		(&RequestHeader_Client, sizeof (RequestHeader_Client));
					memcpy	(RequestHeader_Client.Signature, RequestSignature, RequestSignatureSize);
					RequestHeader_Client.DataBlockSize			= ((int*)pData) [0];
					RequestHeader_Client.DataType					= DATATYPE_CLIENT_PLAIN;
					RequestHeader_Client.Command					= COMMAND_CLIENT_ANSWER;
					RequestHeader_Client.DataEncriptionType	= ENCRIPTION_NONE;

				// �������� ����� �������:
					if (!WriteDataBlockAndHeader (PeerSocketID, &RequestHeader_Client, pData))
					{
						fprintf(stderr, "OBServer_MainLoop: Timeout or error writing data block of size %lu.\n", RequestHeader_Client.DataBlockSize);
					}

				//	fprintf(stderr, "\n  Answer of length %lu sended.\n", RequestHeader_Client.DataBlockSize);
					fputs(" Done.\n", stderr);
					
				// ������� ���������� � ���������� �������:
					CloseConnection (PeerSocketID);

					OBServer_Interface_Free(&pData);

//					TIMECHECK_END(Write);

				} // end if (RequestHeader_Server.Command == COMMAND_SERVER_DBREQUEST)
				else 
				{
					fprintf(stderr, "OBServer_MainLoop: Unsupported command (%d).\n", RequestHeader_Server.Command);
					CloseConnection (PeerSocketID);
					continue;
				}
		
		} // end if (Status == 1)
	//----------------------------------------------------------------------------[]
	// �������� �� ������� ��������:
		if (gBaseMode == BM_STOPPING) {
			fputs ("\nReceived stop command. Gracefully terminating...\n", stderr);
/*			fprintf (stderr,	
						"\nAveReset_Read:\t%sAveReset_OBServer_Interface:\t%sAveReset_Write:\t%.0fAveReset_Timer:\t%.0f\n"
						"Count_Read:\t%.0f\nCount_OBServer_Interface:\t%.0f\nCount_Write:\t%.0f\nCount_Timer:\t%.0f\n"
						"Ave_Read:\t%.0f\nAve_OBServer_Interface:\t%.0f\nAve_Write:\t%.0f\nAve_Timer:\t%.0f\n",
						ctime(&AveReset_Read),ctime(&AveReset_OBServer_Interface),ctime(&AveReset_Write),ctime(&AveReset_Timer),
						Count_Read, Count_OBServer_Interface, Count_Write,	Count_Timer,
						Ave_Read,	Ave_OBServer_Interface,	Ave_Write,		Ave_Timer);
*/			break;
		}

	//----------------------------------------------------------------------------[]
	// ������
		time (&TIME_NULL);
		if (TIME_NULL > OldTime + OBS_TIMER_INTERVAL)
		{
			TIMECHECK_START(Timer);
			fprintf			(stderr, " (*)-");
			OBServer_OnTimer		();
			fprintf			(stderr, "-(*)\n");
			OldTime = TIME_NULL;
			TIMECHECK_END	(Timer);
		}

	
	}	// ����� �������� �����

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// ������� �������� ������, �����, ���������� ������� � �.�.:
	close (ListenSocketID);
	CloseTimeLog	();
	RemoveLockFile	();

	return 0;
}
//____________________________________________________________________________[]





#endif
                                                                    
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/