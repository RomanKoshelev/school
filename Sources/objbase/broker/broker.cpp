/*______________________________________________________________________________
[]																										[]
[] This is a part of the PROJECT: 'ObjectBase:CGI'										[]
[] 																									[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          broker.cpp																	[]
[] Date:          20.08.99																		[]
[] Author:        Semyon N. Vepritskiy														[]
[] Description:   ����� ����� ���������������� �������� � ���������� ��			[]
[]____________________________________________________________________________[]
����� ��������� �������� ������:

����� ��������� ��� ������ � ������ ��������.
�� ������ �� ������� ��������, ���������� ������� � ��, �� �������
������ ���������� ����� � ���������-���������� ������ ������� ��
��� ��������� �������� �� �������� ����������� �������� ��������,
������� ������������� � ������� �� ������������� ������ ����� �
���������� ��. ������������� ��������� �������� �� ���������
������� ���������, ��������� ������� � ���������� �� �� ���������
��������� ������ �������� ������ ���� �������� �������.
����� ��������� ������� ��������� �������� ������� �����������
��-����� � ����� ������� ��������� �������� ���������� ���������
�������� ���������� �� ������ � ��, ����� ���� ��� ����������
������������� ������ ������������ � �����������.
*/
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>

#include "../bcc/CGI_sock.h"

#define MSGSYNKEY 177	// ���� ��� ����� ������� �������������
#define MSGERRKEY 168	// ���� ��� ����� ������� ������
#define SEMKEY 119		// ���� ��� ����� ���������
#define SEM_QUAN 2		// ���������� ��������� � �����
#define SEM_COMMAND 0	// ����� �������� ��� ���������� �������
#define SEM_RECONNECT 1	// ����� �������� ��� ���������� � ��
#define COMMAND_STOP 1	// �������� �������� ��� ���������� ������
#define COMMAND_RECONFIG 2	// �������� �������� ��� ���������� ������������
#define SEM_SET(x) semctl(g_Sem,x,SETVAL,g_sem_set) // ��������� ��������
#define SEM_CLR(x) semctl(g_Sem,x,SETVAL,g_sem_nul) // ����� ��������
#define SEM_TST(x) semctl(g_Sem,x,GETVAL,g_sem_end) // ���� ��������
#define INFO_LEN 90		// ����� ��������� � �� (�������)

#define SIZE_MAX_BUFER 1000	// ������ ������ ��� ��������� ������ �� ������
#define SIZE_STRTIME 30			// ������ ������ ������ �������
#define SIZE_STRCONFIG 200		// ������ ������ ������ ������������
#define SIZE_STRHOST 100		// ������ ������ ����� ���������� �����
#define SIZE_STRMSG 200			// ������ ������ ���������
#define SIZE_RETCODE 10			// ������ ������ ���� ��������
#define SIZE_STRHEADER 50		// ������ ������ ��������� ������ �� PHP3
#define SIZE_STRIP 15			// ������ ������ IP-������
#define SIZE_STRGRP 20			// ������ ����� ������
#define SIZE_STRFUN 50			// ������ ����� �������
#define SIZE_HEAD (sizeof(long)*2)	// ������ ���������� �������� (������ ���� �������� � ���-�� ������)
// ��������� ������������:
#define BIT_CONFIG_PORTDB  0x01	// PortDB
#define BIT_CONFIG_PORTPHP 0x02	// PortPHP
#define BIT_CONFIG_HOST    0x04	// Host
#define BIT_CONFIG_ALL     0x07	// ��� ���� ������������ ����������� ����������

#define CFG_READ_ALL  0	// ������ ��� ������������
#define CFG_READ_MAIN 1	// ������ ������ ������ �� ���� <Config>
#define CFG_READ_ACL  2	// ������ ������ ������ ACL (��� ���� <Config>)

#define LOG_TEXT	1				// ����� ���������� ����
#define LOG_HTML	2				// ����� ���� � ����� HTML

#ifndef MSG_WAITALL
#define MSG_WAITALL 0x40
#endif

//----------------------------------------------------------------------------[] 
#define  TIME_START																				\
	struct timeval tm1;																			\
	struct timeval tm2;																			\
	gettimeofday(&tm1,NULL);
//----------------------------------------------------------------------------[] 
#define  TIME_END																					\
	gettimeofday(&tm2,NULL);																	\
	{																									\
		long s1 = tm2.tv_sec - tm1.tv_sec;													\
		long s2 = tm2.tv_usec - tm1.tv_usec;												\
		s2 += 1000000 * s1;																		\
		printf ("[%d] \n", (s2?1000000/s2:0));												\
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[]

typedef struct {
	unsigned int quan;			// ���������� ������ � �������
	char userIP[SIZE_STRIP+1];	// IP-����� ������������
	char mirrIP[SIZE_STRIP+1];	// IP-����� �������
	time_t time;	// ����� ������� ������� (� ������������)
} REQUEST_HEADER;	// ��������� �������

typedef struct {
	unsigned int quan;// ������ ������ ������������� �� �� ������
	int ret_code;		// ��� �������� �� �� (����>0,msg �������� �������� ������)
	char msg[1];		// ��� �������������� ����� �� ��
} RET_TYPE;				// ��������� ������������� �� �� ������

typedef struct {
	int portCL;		// ����� ����� ����� � �������������
	int portDB;		// ����� ����� ����� � ��
	char host[SIZE_STRHOST]; // ����� ������� � ��
	char ACL;		// ���� ������ ������ (Access Control List)
	char logMode;	// ���� ������� ���-����� �������: 0-���,1-��������� �����,2-html-�����
	char logSend;	// ���� ������� ������� � ��
} CONFIG; // ������������ ����������

typedef struct {
	long mtype;		// ����� (�������-���������� ���������)
	char mtext[1];	// ���� ��������� (��������, ��� ��� ��� ����� ������ mtype)
} MESSAGE_HEADER; // ��������� ��������� ������� ��������� UNIX

typedef struct {
	long mtype;		// ����� (�������-���������� ���������)
	time_t time;	// ����� ����������� �������
	char msg[INFO_LEN]; // ����� ��������� (�������)
} MESSAGE_INFO; // ��������� � ������� ��� �������� � ��

typedef struct sGrp {
	char Name[SIZE_STRGRP];	// ��� ������
	sGrp *pNext;				// ����� ��������� ��������� ������
	int quan;					// ���-�� ������� � ������
	char *pMas;				// ����� ������� �������
} ACCESS_GRP_TYPE;			// ��������� �������� ������

typedef struct sIP {
	char IP[SIZE_STRIP+1];// IP-�����
	sIP *pNext;				// ����� ��������� ��������� IP-������
	int quan;				// ���-�� ����� � �������
	sGrp **pMas;			// ����� ������� ������ �����, ����������� ������� IP-������
} ACCESS_IP_TYPE;			// ��������� �������� IP-������

class Log {			// ����� ��� �������� ����� ���-�����
	char *m_pName;
public:
	Log() { m_pName = 0; }
	~Log() { if(m_pName) delete m_pName; }
	void Set(char *p) { m_pName = p; }
	char *Name() { return m_pName; }
};

class Access {
	ACCESS_IP_TYPE *pTopIP;		// ������� ������ IP-��������
	ACCESS_IP_TYPE *pEndIP;		// ����� ������ ��� �������� ����������
	ACCESS_GRP_TYPE *pTopGrp;	// ������� ������ Grp-��������
	ACCESS_GRP_TYPE *pEndGrp;	// ����� ������ ��� �������� ����������
public:
	Access() { pTopIP = 0; pEndIP = 0; pTopGrp = 0; pEndGrp = 0; }
	~Access() { Clear(); }
	void Clear(void);
	int AddIP(char*,char*,int*);
	int AddGrp(char*,FILE*,int*);
	int Permit(char*,char*);
	int Belong(char*,char*);
	void Show(void); //## �������� ���������� ���������
};

//----------------------------------------------------------------------------[]
void pchild(int);
void prc_request(int,long,long,int);
void msg_to_user(int,char*);
void _info(char*,int=-1);
void SendErrorQueue(void);
//----------------------------------------------------------------------------[]

Log g_rLog;				// ����� ��� �������� ����� ���-�����
Sock *g_pSoCl;			// ����� ������ ��� ������ � ���������
Sock *g_pSoDb;			// ����� ������ ��� ������ � ��
int g_MsgSyn=-1;		// id ������� ��� ������������� �������� ���������
int g_MsgErr=-1;		// id ������� ��� �������� ��������� ��������� �������� �� �������
int g_Sem=-1;			// id ����� ���������
union semun g_sem_nul;				 // ��������� ��������� ���������

union semun g_sem_set = {1};// ��������� ��������� ��������� 

CONFIG g_rCfg;			// ��������� ������������ ������
union semun g_sem_end;// ������� ��� ������� semctl
char g_sConfErr[] = "Configuration error, line "; // ��������� �� ������ ������������
Access g_Acc;

//============================================================================[]
// ������� ������������ �������������� ���������
// � ���-���� � �� stdout, ���� �� ������
void _info(char *msg,int code)
{
	time_t t; time(&t);
	if(g_rCfg.logMode) { // ��������� �������� ������� � ����
		int head = 0;
		if(g_rCfg.logMode==LOG_HTML) {
			if(access(g_rLog.Name(),0)) head++;
		}
		FILE *fil = fopen(g_rLog.Name(),"a");
		if(fil) {
			char str[SIZE_STRTIME];
			strcpy(str,ctime(&t));
			char *p = strchr(str,'\n'); if(p) *p = 0;
			if(g_rCfg.logMode==LOG_HTML) {
				if(head) fprintf(fil,
					"<html><head><META HTTP-EQUIV='expires' CONTENT='0'>\n"
					"<meta http-equiv='Pragma' content='no-cache'>\n"
					"<title>Broker's log file</title></head>\n"
					"<body topmargin=20 bgcolor='#ddddee'>\n"
					"<center><h1><font face='Arial'>Broker's log file</font></h1></center>\n");
				fprintf(fil,"<br><b>- %s</b>, %s: %s\n",str,code>0?"<u>ERR</u>":"INFO",msg);
			}
			else {
				fprintf(fil,"%s, %s: %s\n",str,code>0?"ERR":"INFO",msg);
			}
			fclose(fil);
		}
	}
	if(g_rCfg.logSend) { // ��������� �������� ������� � ��
		MESSAGE_INFO rInfo;
		rInfo.mtype = 1;
		rInfo.time = t;
		strncpy(rInfo.msg+1,msg,INFO_LEN-2);
		rInfo.msg[0] = 1; // ��� ��������� ��� ��
		rInfo.msg[INFO_LEN-1] = 0;
		int len = sizeof(rInfo) - int(sizeof(long));
		msgsnd(g_MsgErr,&rInfo,len,0);
	}
//	if(code>=0) exit(code);
}

//============================================================================[]
// ������� ������ ������ �� ����� ������������ � �������� ���������
// � �������� ��������, ��������� � ������������ � � ��������� ������
// ��� ������������������� �����
// ���������: �����,����������_�����,�����_������
char *get_string(char *str,FILE *fil,int *pLine)
{
	static char sTerm[] = "\n\r#!;";
	char *p;
	while(p=fgets(str,SIZE_STRCONFIG-1,fil)) {
		(*pLine)++;
		p = strpbrk(str,sTerm); if(p) *p = 0;
		p = str;
		while(*p) { if(*p!=' '&&*p!='\t') break; p++; }
		if(*p) break;
	}
	if(p) {
		char *pEnd = strchr(p,'\0') - 1;
		while(pEnd>p) {
			if(*pEnd!=' '&&*pEnd!='\t') break;
			*pEnd = 0;
			pEnd--;
		}
	}
	return p;
}

//============================================================================[]
// ������� ������ ����� ����� ������������ �� ��������� �������
// ���������: �����,������� ������,����������_�����,�����_������
int SeekFor(char *str,char *pMask,FILE *fil,int *pLine)
{
	for(;;) {
		char *p = get_string(str,fil,pLine);
		if(!p) break;
		if(!strcmp(p,pMask)) return 0;
	}
	return 1;
}

//============================================================================[]
// ������� ��������� ������ ��������� AccessList �� ���� <Config>
// ���������: �����,����������_�����,�����_������
int config_main_OnlyACL(char *str,FILE *fil,int *pLine)
{
	static char sDeliv[] = "= ";
	for(;;) {
		char *p = get_string(str,fil,pLine);
		if(!p) break;
		if(!strcmp(p,"</Config>")) break;
		p = strtok(p,sDeliv);
		if(!p) continue;
		char *pVol = strtok(NULL,sDeliv);
		if(!pVol) {
			printf("Broker: %s%d: Unrecognized format '%s'!\n",g_sConfErr,*pLine,p);
			return 1;
		}
		if(!strcmp(p,"AccessList")) {
			g_rCfg.ACL = strcasecmp(pVol,"yes") ? 0 : 1;
			SeekFor(str,"</Config>",fil,pLine);
			break;
		}
	}
	return 0;
}

//============================================================================[]
// ������� ��������� ���������� ������������ �� ���� <Config>
// ���������: �����,����������_�����,�����_������
int config_main(char *str,FILE *fil,int *pLine)
{
	static char sDeliv[] = "= ";
	static char *mas[] = { "txt","html" };
	char *pLogPath = 0;
	int mask = 0;
	int err = 0;
	for(;;) {
		char *p = get_string(str,fil,pLine);
		if(!p) break;
		if(!strcmp(p,"</Config>")) break;
		p = strtok(p,sDeliv);
		if(!p) continue;
		char *pVol = strtok(NULL,sDeliv);
		if(!pVol) {
			printf("Broker: %s%d: Unrecognized format '%s'!\n",g_sConfErr,*pLine,p);
			err++; break;
		}
		if(!strcmp(p,"AccessList")) {
			g_rCfg.ACL = strcasecmp(pVol,"yes") ? 0 : 1;
		}
		else if(!strcmp(p,"PortDB")) {
			g_rCfg.portDB = atoi(pVol);
			mask |= BIT_CONFIG_PORTDB;
		}
		else if(!strcmp(p,"PortPHP")) {
			g_rCfg.portCL = atoi(pVol);
			mask |= BIT_CONFIG_PORTPHP;
		}
		else if(!strcmp(p,"Host")) {
			strncpy(g_rCfg.host,pVol,99);
			mask |= BIT_CONFIG_HOST;
		}
		else if(!strcmp(p,"LogMode")) {
			if((!strcasecmp(pVol,"yes"))||
				(!strcasecmp(pVol,"text")))		g_rCfg.logMode = LOG_TEXT;
			else if(!strcasecmp(pVol,"html"))	g_rCfg.logMode = LOG_HTML;
		}
		else if(!strcmp(p,"LogSend")) {
			g_rCfg.logSend = strcasecmp(pVol,"yes") ? 0 : 1;
		}
		else if(!strcmp(p,"LogPath")) {
			pLogPath = new char [strlen(pVol)+1];
			strcpy(pLogPath,pVol);
		}
	}
	if(!err) {
		if(mask!=BIT_CONFIG_ALL) {
			printf("Broker: %s%d: Tag 'Config' not consist all required parameters!\n",g_sConfErr,*pLine);
			err++;
		}
		else if(g_rCfg.logMode) {
			char name[SIZE_STRTIME];
			sprintf(name,"broker_log.%s",mas[g_rCfg.logMode-1]);
			int len = 0;
			if(pLogPath) {
				len = strlen(pLogPath);
				if(pLogPath[len-1]=='/') pLogPath[--len] = 0;
			}
			char *p = new char [len+strlen(name)+2];
			if(pLogPath) sprintf(p,"%s/%s",pLogPath,name);
			else strcpy(p,name);
			g_rLog.Set(p);
		}
	}
	if(pLogPath) delete pLogPath;
	return err;
}

//============================================================================[]
// ������� ��������� ���������� ������������ �� ���� <Access>
// ���������: �����,����������_�����,�����_������
int config_access(char *str,FILE *fil,int *pLine)
{
	for(;;) {
		char *pN = get_string(str,fil,pLine);
		if(!pN) break;
		if(!strcmp(pN,"</Access>")) break;
		char *pG = strchr(pN,'=');
		if(!pN) {
			printf("Broker: %s%d: Error IP format '%s'!\n",g_sConfErr,*pLine,pN);
			return 1;
		}
		*pG = 0;
		pG++;
		while(*pG) { if(*pG!=' '&&*pG!='\t') break; pG++; }
		switch(g_Acc.AddIP(pN,pG,pLine)) {
		case 1 :
			return 1;
		case 2 :
			printf("Broker: %s%d: No memory!\n",g_sConfErr,*pLine);
			return 1;
		}
	}
	return 0;
}

//============================================================================[]
// ������� ��������� ���������� ������������ �� ���� <Group>
// ���������: �����,���_������,����������_�����,�����_������
int config_group(char *str,char *p,FILE *fil,int *pLine)
{
	char pGrp[SIZE_STRGRP];
	strncpy(pGrp,p,SIZE_STRGRP-1);
	p = strchr(pGrp,'>');
	if(p) *p = 0;
//	for(;;) {
//		p = get_string(str,fil,pLine);
//		if(!p) break;
//		if(!strcmp(p,"</Group>")) break;
		if(g_Acc.AddGrp(pGrp,fil,pLine)) {
			printf("Broker: %s%d: No memory!\n",g_sConfErr,*pLine);
			return 1;
		}
//	}
	return 0;
}

//============================================================================[]
// ������� ��������� ���������� ������������ �� ����� broker.cfg
int get_config(char flg)
{
	static char pName[] = "broker.cfg";
	static char sMoThenOnce[] = "was found more then once";
	FILE *fil = fopen(pName,"rt");
	if(!fil) {
		printf("Broker: Error opening configuration file %s!\n",pName);
		return 1;
	}
	char str[SIZE_STRCONFIG]; // ����� ��� ������ ������
	int err = 0;		// ��� �������� �� ������� (0-OK,1-ERR)
	int line = 0;		// ����� �������� ������
	char MainCfg = 0; // ���� ��� ������ ���������� ������������� ���� <Config>
	char AccCfg = 0; // ���� ��� ������ ���������� ������������� ���� <Access>
	g_Acc.Clear(); // ������� ������ ACL �� ������ ���������� ������
//strcasecmp
	for(;;) {
		char *p = get_string(str,fil,&line);
		if(!p) break;
		if(!strcmp(p,"<Config>")) {
			if(MainCfg) {
				printf("Broker: %s%d: Tag 'Config' %s!\n",g_sConfErr,line,sMoThenOnce);
				err++; break;
			}
			MainCfg++;
			if(flg==CFG_READ_ACL) {
				if(!config_main_OnlyACL(str,fil,&line)) {
					if(!g_rCfg.ACL) break; // ������ ������ �� ���������
					continue;
				}
				err++; break;
			}
			if(!config_main(str,fil,&line)) {
				if(!g_rCfg.ACL||flg==CFG_READ_MAIN) break; // ������ ������ �� ���������
				continue; // OK
			}
			err++; break;
		}
		if(!strcmp(p,"<Access>")) {
			if(flg==CFG_READ_MAIN) {
				SeekFor(str,"</Access>",fil,&line);
				continue;
			}
			if(AccCfg) {
				printf("Broker: %s%d: Tag 'Access' %s!\n",g_sConfErr,line,sMoThenOnce);
				err++; break;
			}
			AccCfg++;
			if(!config_access(str,fil,&line)) continue; // OK
			err++; break;
		}
		if(!strncmp(p,"<Group",6)) {
			if(flg==CFG_READ_MAIN) {
				SeekFor(str,"</Group>",fil,&line);
				continue;
			}
			p = strchr(p,'=');
			if(p) {
				p++;
				while(*p) { if(*p!=' '&&*p!='\t') break; p++; }
				if(!config_group(str,p,fil,&line)) continue; // OK
			}
			err++; break;
		}
		printf("Broker: %s%d: Unrecognized tag '%s'!\n",g_sConfErr,line,p);
		err++; break;
	}
	fclose(fil);
//	if(!err&&flg!=CFG_READ_MAIN) { //## ���������� ���������
//		printf("Broker: ACL=%s\n",g_rCfg.ACL?"Yes":"No");
//		g_Acc.Show();
//	}
	return err;
}

//============================================================================[]
// ������� �������� ������� ����������� ����� ������
void send_daemon(int flg)
{

	if(!g_pSoCl->good()) {
		perror("Broker: socket");
		exit(1);
	}

	g_Sem = semget(SEMKEY,SEM_QUAN,IPC_CREAT|0666); //IPC_EXCL
	if(g_Sem==-1) {
		perror("Broker: semget");
		exit(1);
	}
	g_sem_set.val = flg; // ��������� �������� ����������� ��������
	SEM_SET(SEM_COMMAND); // ��������� ���������� ��������

	if(g_pSoCl->connect("127.0.0.1",g_rCfg.portCL)) {
		perror("Broker: connect");
		exit(1);
	}

	printf("\nBroker: Command %s was sent to daemon\n",flg==COMMAND_STOP?"STOP":"RECONFIG");

	exit(0);
}

//============================================================================[]
// ������� ���������� ������ (�������� �������� � ���������)
void _end(int err,int info_flg=1)
{
	if(g_MsgSyn>=0) msgctl(g_MsgSyn,IPC_RMID,0); // �������� ������� �������������
	if(g_MsgErr>=0) msgctl(g_MsgErr,IPC_RMID,0); // �������� ������� ��������� �� �������
	if(g_Sem>=0) semctl(g_Sem,0,IPC_RMID,g_sem_end); // �������� ���������
	if(info_flg) _info("Daemon finished");
	exit(err);
}

//============================================================================[]
// �������� �������
// � �������� ������������� ��������� ��������� host-��� �������,
// �� ������� ���������� �������-�������� ������ ������� ��
// ���� ������ �������� ������, �������� ������� �� ����� ������������
int main(int argc,char *argv[])
{
	MESSAGE_HEADER rMsg; // ��������� �������� � ������� ���������
	int _err = 0;	// ������ ������ ��� ���������� ������

	if(get_config(argc>1?CFG_READ_MAIN:CFG_READ_ALL)) return 1;

	Sock SoCl(AF_INET,SOCK_STREAM); // ����� ����� ��� ������ � ���������
	Sock SoDb(AF_INET,SOCK_STREAM); // ����� ����� ��� ����� � ���������� ������� ��

// ��������� ������� � ������� ����� ���������� ������.
// ��������� ���������� ������ ������ �������, ������ ��� ���
// ���������� �������� ��������� ����� ���������� ��������
// � ��������� ���������� �������:
	g_pSoCl = &SoCl;
	g_pSoDb = &SoDb; 


	if(argc>1) {
		if(argv[1][0]=='-') {
			if(argv[1][1]=='d') send_daemon(COMMAND_STOP);
			if(argv[1][1]=='r') send_daemon(COMMAND_RECONFIG);
/* // �������� �������� ���������:
		if(if(argv[1][1]=='m') {
			g_MsgErr = msgget(MSGERRKEY,IPC_CREAT|0666);
			g_MsgSyn = msgget(MSGSYNKEY,IPC_CREAT|0666);
			if(g_MsgSyn>=0) msgctl(g_MsgSyn,IPC_RMID,0); // �������� ������� �������������
			if(g_MsgErr>=0) msgctl(g_MsgErr,IPC_RMID,0); // �������� ������� ��������� �� �������
			exit(0);
		}
*/
		}
		printf(	"Broker USAGE: %s [ -d | -r ]\n"
					"  -d   - stop daemon\n"
					"  -r   - reread daemon's ACL\n",argv[0]);
		exit(0);
	}
	g_rCfg.host[SIZE_STRHOST-1] = 0;
// ������� ������� ��� ���������� �������������������
// ���������� ������������:
	g_MsgSyn = msgget(MSGSYNKEY,IPC_CREAT|0666); //IPC_EXCL
	if(g_MsgSyn==-1) {
		perror("Broker: msgget[syn]");
		_end(1,0);
	}

// ���������������� ������� �������:
	while(msgrcv(g_MsgSyn,&rMsg,1,0,MSG_NOERROR|IPC_NOWAIT)>=0);

// ������� ������� ��� ��������� �� ������� ������������� ��������:
	g_MsgErr = msgget(MSGERRKEY,IPC_CREAT|0666);
	if(g_MsgErr==-1) {
		perror("Broker: msgget[err]");
		_end(1,0);
	}


// ���������������� ������� �������:
	while(msgrcv(g_MsgErr,&rMsg,1,0,MSG_NOERROR|IPC_NOWAIT)>=0);


// ������� 2-���������� ������� (��������� � ����������)
	g_Sem = semget(SEMKEY,SEM_QUAN,IPC_CREAT|0666); //IPC_EXCL
	if(g_Sem==-1) {
		perror("Broker: semget");
		_end(1,0);
	}
// ��������� ���������:
	SEM_CLR(SEM_COMMAND);
	SEM_CLR(SEM_RECONNECT);

// ������� ����� ��� ������������� ��������:
	if(!g_pSoCl->good()) {
		perror("Broker: socket [Client]");
		_end(1,0);
	}
	if(g_pSoCl->bind(0,g_rCfg.portCL)<0) _end(1,0);

// ������� ����� ��� �������� ������ ����� � ��:
	if(!g_pSoDb->good()) {
		perror("Broker: socket [DataBase]");
		_end(1,0);
	}


	if(g_pSoDb->connect(g_rCfg.host,g_rCfg.portDB)) {
		perror("Broker: connect [DataBase]");
		_end(1,0);
	}
/*
// �������� ��� �������������� �������� � �����:
	if(getppid()!=1) { // �������� �� init
		signal(SIGTTOU,SIG_IGN);
		signal(SIGTTIN,SIG_IGN);
		signal(SIGTSTP,SIG_IGN);
	}
*/
/*
	if(fork()!=0) exit(0); // �������� �������� ������
	if(setsid()==-1) {
		perror("setsid");
		_end(1,0);
	}
*/
	char str[SIZE_STRMSG];
	sprintf(str,"Daemon started, PortPHP=%d, PortDB=%d, HostDB=%s, ACL=%s",
		g_rCfg.portCL,g_rCfg.portDB,g_rCfg.host,g_rCfg.ACL?"Yes":"No");
	printf("Broker: %s: %s\n",argv[0],str);
	printf("Broker: Log: file=%s, BD=%s\n",
		g_rCfg.logMode==0?"No":(g_rCfg.logMode==1?"TEXT":"HTML"),
		g_rCfg.logSend?"Yes":"No");
	_info(str);
/*
// ����������� �������� ��� �������������� �������� � �����:
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	signal(SIGINT,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
*/
	signal(SIGCHLD,pchild); // ��������� ����������� ������� SIGCLD

	long MyPid = 1;	// ����� �������, �� �� ���������� ������������� ��������
	int ns;				// ������������� �������������� ������

	int num_sec = 0;	// ���������� (���������� �������� � �������)
	int rps = 0;		// ���������� (�������� � �������)

	time_t t,t_sav;
	time(&t_sav);

// ��� ���������� ������ ������� ��������� �������� ����������
// ������ ��� �������� ����������� ������ ����������� ��������
// ������ � ������� ���������:
	rMsg.mtype = MyPid;
	msgsnd(g_MsgSyn,&rMsg,1,0); // perror("msgsnd");

	int val = 1; // ��������� ����� � ������ ������
// � ������ ������ ��������������� �������������� ��������
// ���������� ����� ���������� ������/������, ��� ������� �����
// ������� �� ������� ������/������ ���������� � ����� -1
// � ������������ ������ SIGPIPE, ������� �� ����������:
	signal(SIGPIPE,SIG_IGN);
	setsockopt(g_pSoDb->fd(),SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val));



// ���� ������������� ������ �� ������� ������� �������� �� ��������
	for(;;) 
	{
	// �������� ���������� ��������
		switch (SEM_TST(SEM_COMMAND)) 
		{ 
			case COMMAND_STOP :
				_end(0); // ���������� ������
			break;
			case COMMAND_RECONFIG :
				SEM_CLR(SEM_COMMAND);
				if(g_rCfg.ACL) { // �������� ������ ���� ������� ����� ACL
					if(get_config(CFG_READ_ACL)) {
						_info("Error reread configuration file!",1);
						_end(1);
					}
				}
			break;
		}

		if((ns=g_pSoCl->accept(0,0))<0) 
		{
			sprintf(str,"Broker: Error call accept: %s!",strerror(errno));
			_info(str,1);
			_end(1);
		}

	// �������� ���������� ��������
		switch (SEM_TST(SEM_COMMAND)) 
		{
			case COMMAND_STOP :
				close(ns);
				_end(0); // ���������� ������
			break;
			case COMMAND_RECONFIG :
				SEM_CLR(SEM_COMMAND);
				if(g_rCfg.ACL) { // �������� ������ ���� ������� ����� ACL
					if(get_config(CFG_READ_ACL)) {
						_info("Error reread configuration file!",1);
						_end(1);
					}
				}
			break;
		}

	// ��������������� � ��
		if (SEM_TST(SEM_RECONNECT)) 
		{ 
			_info("Reconnect to DB");
			if(g_pSoDb->reconnect(g_rCfg.host,g_rCfg.portDB)) 
			{
				msg_to_user(ns,"Not connect to DB, request refused!");
				close(ns);
				continue;
			}
			setsockopt(g_pSoDb->fd(),SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val));
			SEM_CLR(SEM_RECONNECT);
		}

		long PrewPid = MyPid; // ��������� ����� ����������� �������
		MyPid++; if(MyPid<=0) MyPid = 1;

//--------- ���������� ��������
		time(&t); num_sec++;
		if(t_sav!=t) 
		{
			t_sav = t;
			rps = num_sec;
			num_sec = 0;
		}
//------------------------------

		int pid = fork(); // ������� �������� �������

	// ����� ��������� ��������
		if(pid==0) 
		{ 
		//#### ����� ������� �������� ����� CL ???
			prc_request (ns,MyPid,PrewPid,rps);
			// close(ns); //` 25.12.1999 RomanVK: -- �������� ���������� � prc_request
			exit(0);
		}
		if(pid==-1) msg_to_user(ns,"Error request processing!");
		close(ns); // ������� ������������� � ��������� ������� ���������� ������
	}
//----------------------------------------------------------------------------[] 

	_end(_err);
	return _err;
}

//============================================================================[]
// �������-���������� ������� SIGCHLD, ������� ����������
// ������������� �������� ��� ���������� ������ ���������
// ������������ ������ ��� ������� ������� ��������� �� ����������
// �� ��������� �������� ��������
void pchild(int from_pid)
{ // ��� ������� ������������ ��� �������� ������� ����������� �������� ���������
	int status;
	while(waitpid((pid_t)-1,&status,WNOHANG)>0);
	signal(SIGCHLD,pchild); // ����� ������������� ���������� ������� SIGCLD
}

//============================================================================[]
// ������� ������������ ��������� ������� �� ���������
// ������ ����������� �� ������� �������� (PHP3)
int get_header(int ns,REQUEST_HEADER *pHead)
{
	char buf[SIZE_STRHEADER+1];
	if(recv(ns,buf,SIZE_STRHEADER,MSG_WAITALL)<SIZE_STRHEADER) return 1;
	buf[SIZE_STRHEADER] = 0; static char dev[] =", ";
	memset(pHead,0,sizeof(*pHead));
	char *p = strtok(buf,dev); if(!p) return 1;
	pHead->quan = (unsigned int)atol(p);
	p = strtok(NULL,dev); if(!p) return 1;
	strncpy(pHead->userIP,p,SIZE_STRIP);
	p = strtok(NULL,dev); if(!p) return 1;
	strncpy(pHead->mirrIP,p,SIZE_STRIP);
	time(&(pHead->time)); // �������� ����� �������
	return 0;
}
//____________________________________________________________________________[]






#define SayToUserAndPermitToChild(x) {msg_to_user(ns,x); msgsnd(g_MsgSyn,&rMsg,1,0);}

//______________________________________________________________________________
//                                                                            []
// ������� ����������� �������� ���������, ������� �����������						[]
// ��� ��������� ������� �������																[]
//                                                                            []
void prc_request (int ns,long MyPid,long PrewPid,int rps)
{
	fd_set rfds;
	struct timeval tv;

	int nbytes,i;
	int retval;
	REQUEST_HEADER rHead;	// ��������� ��������� �������
	MESSAGE_HEADER rMsg;		// ��������� �������� � ������� ���������
	rMsg.mtype = MyPid;		// ��� ��������� - ������������� ���.��������

	FD_ZERO(&rfds);
	FD_SET(g_pSoDb->fd(),&rfds);
	tv.tv_usec = 0;

// ��������� ��������� �������
	if(get_header(ns,&rHead)) 
	{ 
		SayToUserAndPermitToChild ("Error in request header format, request refused");
		close(ns); //` 25.12.1999 RomanVK: 
		return;
	}

	char *buf = new char [sizeof(REQUEST_HEADER)+rHead.quan+1]; // +1 ��� 0 �� �����
	if(!buf) 
	{
		SayToUserAndPermitToChild ("No memory fo received request data, request refused");
		close(ns); //` 25.12.1999 RomanVK: 
		return;
	}
//TIME_START;
	nbytes = recv (ns, buf+sizeof(REQUEST_HEADER), rHead.quan, MSG_WAITALL);
//TIME_END;

	if(nbytes<rHead.quan) 
	{
		SayToUserAndPermitToChild ("Incomplete data, request refused!");
		delete buf;
		close(ns); //` 25.12.1999 RomanVK: 
		return;
	}

	buf[sizeof(REQUEST_HEADER)+rHead.quan] = 0;
	memcpy(buf,&rHead,sizeof(REQUEST_HEADER));


// ��������� �������� ������� � ��������
	if(g_rCfg.ACL) 
	{
		char pFun[SIZE_STRFUN];
		char *p = strchr(buf+sizeof(REQUEST_HEADER),3);
		int l = SIZE_STRFUN - 1;
		if(p) {
			int len = p - (buf+sizeof(REQUEST_HEADER));
			if(len<l) l = len;
		}
		strncpy(pFun,buf+sizeof(REQUEST_HEADER),l);
		pFun[l] = 0;
	// ������ � ������ ������� ��������
		if(!g_Acc.Permit(rHead.userIP,pFun)) 
		{ 
			char str[SIZE_STRMSG];
			sprintf(str,"Function '%s' not permited for %s!",pFun,rHead.userIP);
			SayToUserAndPermitToChild (str);
			delete buf;
			close(ns); //` 25.12.1999 RomanVK: 
			return;
		}
	}


// �������� �� ������� ��������� �� ����������� ��������
// ("�������� �����") � ���, ��� �� ��������� �����,
// ��� ��� � ������� ������� �� ������ �������� � �� � ����
// �� ������������:
	int len = msgrcv (g_MsgSyn, &rMsg, 1, PrewPid, MSG_NOERROR);
// ������������ ��� ��������� - ������������� ���.��������
	rMsg.mtype = MyPid; 

	retval = g_pSoDb->write(buf,sizeof(REQUEST_HEADER)+rHead.quan);

	delete buf; RET_TYPE ret;
	if(retval>0) 
	{
		retval = g_pSoDb->read((char*)&ret,SIZE_HEAD,MSG_WAITALL);
	}
	if(retval<int(SIZE_HEAD)) 
	{
		SEM_SET(SEM_RECONNECT);
		SayToUserAndPermitToChild ("Disconnect whith DB, request refused");
		close(ns); //` 25.12.1999 RomanVK: 
		return;			
	}

// ������� ������ ������ ���������
	ret.quan -= int(SIZE_HEAD);
	buf = new char [ret.quan+SIZE_RETCODE+1];
// ���������� ��� ��������
	sprintf(buf,"%10d",ret.ret_code);
	retval = g_pSoDb->read(buf+SIZE_RETCODE,ret.quan,MSG_WAITALL);

	if(retval<ret.quan)
	{
		msg_to_user (ns,"Incomplit data received from DB, request refused");
	}
	else 
	{
	// ����� � �� ������ �������, ���� �� ����
		SendErrorQueue (); 
	}

	send (ns,buf,ret.quan+SIZE_RETCODE,0);
	close(ns); //` 25.12.1999 RomanVK: 

// ��������� ���������� �������� �� ������������ ��
	msgsnd (g_MsgSyn,&rMsg,1,0); 
	buf[ret.quan+SIZE_RETCODE] = 0;

	delete buf;
}
//____________________________________________________________________________[]








//============================================================================[]
// ������� ������� ������������ ��������� �� ������ � ��������
// ��������� �������
void msg_to_user(int ns,char *pMsg)
{
	fd_set rfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(ns,&rfds);
	tv.tv_sec = 0; // �� �����
	tv.tv_usec = 0;
	char buf[SIZE_MAX_BUFER]; // ����� ��� ��������� ������ �� ������
	unsigned int u = 1;
	_info(pMsg,1);
	ioctl(ns,FIONBIO,&u); // ������� ���������� � ������ ����������� ������
	while(recv(ns,buf,SIZE_MAX_BUFER-1,0)>0);
//### ����� ����� ������� ��� ������ � ������ SIZE_RETCODE ����
	sprintf(buf,"%10d",-2); // ���������� ��� ��������
	strcpy(buf+SIZE_RETCODE,pMsg);
	send (ns,buf,strlen(pMsg)+SIZE_RETCODE,0);
}

//============================================================================[]
// ������� ������� � �� ������ �������, ������������ � ������� �������
void SendErrorQueue()
{
	char buf[sizeof(REQUEST_HEADER)+INFO_LEN];
	MESSAGE_INFO rMsg;
	memset(buf,0,sizeof(buf));
	int len = sizeof(MESSAGE_INFO)-int(sizeof(long));
	REQUEST_HEADER *pHead = (REQUEST_HEADER*)buf;
	pHead->quan = INFO_LEN;
	strcpy(pHead->mirrIP,"mirrorBSD"); // ����� �����������
// ��������� � �������� � �� ���� ���������:
	while(msgrcv(g_MsgErr,&rMsg,len,0,MSG_NOERROR|IPC_NOWAIT)>=0) {
		pHead->time = rMsg.time;
		strcpy(buf+sizeof(REQUEST_HEADER),rMsg.msg);
		if(g_pSoDb->write(buf,sizeof(buf))<sizeof(buf)) break;
	}
}


//============================================================================[]
// �������-����� ������ Access
//============================================================================[]
//============================================================================[]
// ������� ������� ������ ACL
void Access::Clear()
{
	while(pTopIP) {
		pEndIP = pTopIP;
		if(pEndIP->pMas) delete pEndIP->pMas;
		pTopIP = pEndIP->pNext;
		delete pEndIP;
	}
	pEndIP = pTopIP;
	while(pTopGrp) {
		pEndGrp = pTopGrp;
		if(pEndGrp->pMas) delete pEndGrp->pMas;
		pTopGrp = pEndGrp->pNext;
		delete pEndGrp;
	}
	pEndGrp = pTopGrp;
}

//============================================================================[]
// ������� ���������� ip-������ � ������
int Access::AddIP(char *pIPName,char *pGrpName,int *pLine)
{ // ret: 0-OK, 1-�� ������� ������ �� ������,2-��� ������
	static char sDeliv[] = ", ";
	ACCESS_IP_TYPE *pTmp = new ACCESS_IP_TYPE;
	if(!pTmp) return 2;
	if(!pEndIP) pTopIP = pEndIP = pTmp;
	else {
		pEndIP->pNext = pTmp;
		pEndIP = pEndIP->pNext;
	}
	pEndIP->pNext = 0;
	pEndIP->pMas = 0;
	pEndIP->quan = 0;
	strncpy(pEndIP->IP,pIPName,SIZE_STRIP);
	pEndIP->IP[SIZE_STRIP] = 0;
	char *p = strpbrk(pEndIP->IP," \t");
	if(p) *p = 0; // ������� ������ ��������
	char str[SIZE_STRCONFIG];
	strcpy(str,pGrpName);
	p = strtok(str,sDeliv);
	if(!p) return 2;
	while(p) { (pEndIP->quan)++; p = strtok(NULL,sDeliv); }
	pEndIP->pMas = new ACCESS_GRP_TYPE* [pEndIP->quan];
	if(!(pEndIP->pMas)) return 2;
	strcpy(str,pGrpName);
	p = strtok(str,sDeliv);
	int num = 0;
	while(p) {
		ACCESS_GRP_TYPE *pGrp = pTopGrp;
		pEndIP->pMas[num] = 0;
		while(pGrp) {
			if(!strcmp(p,pGrp->Name)) {
				pEndIP->pMas[num] = pGrp;
				break;
			}
			pGrp = pGrp->pNext;
		}
		if(!pEndIP->pMas[num]) {
			printf("Broker: %s%d: Group not found '%s'!\n",g_sConfErr,*pLine,pGrp->Name);
			return 1;
		}
		num++;
		p = strtok(NULL,sDeliv);
	}
	return 0;
}

//============================================================================[]
// ������� ���������� ������ � ������
int Access::AddGrp(char *pName,FILE *fil,int *pLine)
{ // ret: 0-��,1-��� ������
	ACCESS_GRP_TYPE *pTmp = new ACCESS_GRP_TYPE;
	if(!pTmp) return 1;
	if(!pEndGrp) pTopGrp = pEndGrp = pTmp;
	else {
		pEndGrp->pNext = pTmp;
		pEndGrp = pEndGrp->pNext;
	}
	pEndGrp->pNext = 0;
	pEndGrp->pMas = 0;
	pEndGrp->quan = 0;
	strncpy(pEndGrp->Name,pName,SIZE_STRGRP-1);
	pEndGrp->Name[SIZE_STRGRP-1] = 0;
	char str[SIZE_STRCONFIG];
	long lpos = ftell(fil);
	int num = 0;
	for(;;) {
		char *p = get_string(str,fil,&num);
		if(!p) break;
		if(!strcmp(p,"</Group>")) break;
		(pEndGrp->quan)++;
	}
	pEndGrp->pMas = new char [SIZE_STRFUN*pEndGrp->quan];
	if(!(pEndGrp->pMas)) return 1;
	fseek(fil,lpos,SEEK_SET);
	num = 0;
	for(;;) {
		char *p = get_string(str,fil,pLine);
		if(!p) break;
		if(!strcmp(p,"</Group>")) break;
		char *pDan = pEndGrp->pMas + SIZE_STRFUN * num;
		strncpy(pDan,p,SIZE_STRFUN-1);
		pDan[SIZE_STRFUN-1] = 0;
		p = strpbrk(pDan," \t");
		if(p) *p = 0; // ������� ������ ��������
		num++;
	}
	return 0;
}

//============================================================================[]
// ������� �������� �� ����������� ���������� DB-�������
int Access::Permit(char *pAddr,char *pFun)
{
// N.N.N.N - ��������� ���� (���������������� �� ��� �������)
// '*' � ����� ����� ������� ��������������� �� ��� ������� � ����� �������
	ACCESS_IP_TYPE *pIP = pTopIP;
	while(pIP) {
		if(Belong(pAddr,pIP->IP)) { // IP ����������� ����������
			for(int i=0;i<pIP->quan;i++) {
				for(int j=0;j<pIP->pMas[i]->quan;j++) {
					char *pDan = pIP->pMas[i]->pMas + j * SIZE_STRFUN;
					int l = strlen(pDan) - 1;
					if(pDan[l]=='*') l = strncmp(pDan,pFun,l);
					else l = strcmp(pDan,pFun);
					if(!l) return 1; // ��
				}
			}
			break; //## ����������� ������ ������ ����������� ����� ??
		}
		pIP = pIP->pNext;
	}
	return 0;
}

//============================================================================[]
// ������� �������� �������������� IP-������
int Access::Belong(char *pAddr,char *pMask)
{
	int iMask[4],iAddr[4];
	sscanf(pMask,"%d.%d.%d.%d",&(iMask[0]),&(iMask[1]),&(iMask[2]),&(iMask[3]));
	sscanf(pAddr,"%d.%d.%d.%d",&(iAddr[0]),&(iAddr[1]),&(iAddr[2]),&(iAddr[3]));
	for(int i=3;i>=0;i--)
		if(iMask[i]!=0&&iMask[i]!=iAddr[i]) return 0;
	return 1; // ��
}

//============================================================================[]
// ### ������� �������� ���������� ��������� ACL
void Access::Show()
{
	ACCESS_IP_TYPE *pIP = pTopIP;
	while(pIP) {
		printf("Broker: IP=(%s)\n",pIP->IP);
		for(int i=0;i<pIP->quan;i++) {
			printf("Broker:   Group=(%s)\n",pIP->pMas[i]->Name);
			for(int j=0;j<pIP->pMas[i]->quan;j++)
				printf("Broker:     [%s]\n",pIP->pMas[i]->pMas+j*SIZE_STRFUN);
		}
		pIP = pIP->pNext;
	}
}

