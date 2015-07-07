/*______________________________________________________________________________
[]																										[]
[] This is a part of the PROJECT: 'ObjectBase:CGI'										[]
[] 																									[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          broker.cpp																	[]
[] Date:          20.08.99																		[]
[] Author:        Semyon N. Vepritskiy														[]
[] Description:   демон связи пользовательских запросов с менеджером БД			[]
[]____________________________________________________________________________[]
Более подробное описание работы:

Демон открывает два сокета в домене Интернет.
По одному он слушает клиентов, посылающих запросы к БД, по второму
держит постоянную связь с процессом-менеджером вызова функций БД
При получении запросов от клиентов формируются дочерние процессы,
которые выстраиваются в очередь на использование сокета связи с
менеджером БД. Синхронизация процессов основана на системной
очереди сообщений, благодаря которой с менеджером БД по постоянно
открытому сокету работает только один дочерний процесс.
После обработки запроса очередной дочерний процесс освобождает
БД-сокет и через очередь сообщений посылает следующему дочернему
процессу разрешение на работу с БД, после чего сам возвращает
затребованные данные пользователю и завершается.
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

#define MSGSYNKEY 177	// ключ для имени очереди синхронизации
#define MSGERRKEY 168	// ключ для имени очереди ошибок
#define SEMKEY 119		// ключ для блока семафоров
#define SEM_QUAN 2		// количество семафоров в блоке
#define SEM_COMMAND 0	// номер семафора для управления демоном
#define SEM_RECONNECT 1	// номер семафора для реконнекта с БД
#define COMMAND_STOP 1	// значение семафора для завершения работы
#define COMMAND_RECONFIG 2	// значение семафора для обновления конфигурации
#define SEM_SET(x) semctl(g_Sem,x,SETVAL,g_sem_set) // установка семафора
#define SEM_CLR(x) semctl(g_Sem,x,SETVAL,g_sem_nul) // сброс семафора
#define SEM_TST(x) semctl(g_Sem,x,GETVAL,g_sem_end) // тест семафора
#define INFO_LEN 90		// длина сообщения в БД (события)

#define SIZE_MAX_BUFER 1000	// размер буфера для выжирания данных из сокета
#define SIZE_STRTIME 30			// размер строки вывода времени
#define SIZE_STRCONFIG 200		// размер строки чтения конфигурации
#define SIZE_STRHOST 100		// размер строки имени удаленного хоста
#define SIZE_STRMSG 200			// размер строки сообщений
#define SIZE_RETCODE 10			// размер строки кода возврата
#define SIZE_STRHEADER 50		// размер строки заголовка данных от PHP3
#define SIZE_STRIP 15			// размер строки IP-адреса
#define SIZE_STRGRP 20			// размер имени группы
#define SIZE_STRFUN 50			// размер имени функции
#define SIZE_HEAD (sizeof(long)*2)	// размер начального смещения (размер кода возврата и кол-ва данных)
// параметры конфигурации:
#define BIT_CONFIG_PORTDB  0x01	// PortDB
#define BIT_CONFIG_PORTPHP 0x02	// PortPHP
#define BIT_CONFIG_HOST    0x04	// Host
#define BIT_CONFIG_ALL     0x07	// все биты конфигурации необходимых параметров

#define CFG_READ_ALL  0	// читать всю конфигурацию
#define CFG_READ_MAIN 1	// читать только данные из тэга <Config>
#define CFG_READ_ACL  2	// читать только данные ACL (без тэга <Config>)

#define LOG_TEXT	1				// режим текстового лога
#define LOG_HTML	2				// режим лога в форме HTML

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
	unsigned int quan;			// количество данных в запросе
	char userIP[SIZE_STRIP+1];	// IP-адрес пользователя
	char mirrIP[SIZE_STRIP+1];	// IP-адрес зеркала
	time_t time;	// время прихода запроса (к обработчикам)
} REQUEST_HEADER;	// заголовок запроса

typedef struct {
	unsigned int quan;// полный размер возвращаемого из БД потока
	int ret_code;		// код возврата из БД (если>0,msg содержит описание ошибки)
	char msg[1];		// сам информационный поток из БД
} RET_TYPE;				// заголовок возвращаемого из БД потока

typedef struct {
	int portCL;		// номер порта связи с пользователем
	int portDB;		// номер порта связи с БД
	char host[SIZE_STRHOST]; // адрес сервера с БД
	char ACL;		// флаг режима защиты (Access Control List)
	char logMode;	// флаг ведения лог-файла событий: 0-нет,1-текстовая форма,2-html-форма
	char logSend;	// флаг посылки событий в БД
} CONFIG; // конфигурация соединений

typedef struct {
	long mtype;		// номер (процесс-получатель сообщения)
	char mtext[1];	// само сообщение (заглушка, так как нам нужен только mtype)
} MESSAGE_HEADER; // заголовок системной очереди сообщений UNIX

typedef struct {
	long mtype;		// номер (процесс-получатель сообщения)
	time_t time;	// время наступления события
	char msg[INFO_LEN]; // текст сообщения (событие)
} MESSAGE_INFO; // сообщение о событии для отправки в БД

typedef struct sGrp {
	char Name[SIZE_STRGRP];	// имя группы
	sGrp *pNext;				// адрес следующей структуры группы
	int quan;					// кол-во функций в группе
	char *pMas;				// адрес массива функций
} ACCESS_GRP_TYPE;			// структура хранения группы

typedef struct sIP {
	char IP[SIZE_STRIP+1];// IP-дарес
	sIP *pNext;				// адрес следующей структуры IP-адреса
	int quan;				// кол-во групп в массиве
	sGrp **pMas;			// адрес массива списка групп, назначенных данному IP-адресу
} ACCESS_IP_TYPE;			// структура хранения IP-дареса

class Log {			// класс для хранения имени лог-файла
	char *m_pName;
public:
	Log() { m_pName = 0; }
	~Log() { if(m_pName) delete m_pName; }
	void Set(char *p) { m_pName = p; }
	char *Name() { return m_pName; }
};

class Access {
	ACCESS_IP_TYPE *pTopIP;		// вершина списка IP-объектов
	ACCESS_IP_TYPE *pEndIP;		// хвост списка для быстрого добавления
	ACCESS_GRP_TYPE *pTopGrp;	// вершина списка Grp-объектов
	ACCESS_GRP_TYPE *pEndGrp;	// хвост списка для быстрого добавления
public:
	Access() { pTopIP = 0; pEndIP = 0; pTopGrp = 0; pEndGrp = 0; }
	~Access() { Clear(); }
	void Clear(void);
	int AddIP(char*,char*,int*);
	int AddGrp(char*,FILE*,int*);
	int Permit(char*,char*);
	int Belong(char*,char*);
	void Show(void); //## тестовая распечатка состояния
};

//----------------------------------------------------------------------------[]
void pchild(int);
void prc_request(int,long,long,int);
void msg_to_user(int,char*);
void _info(char*,int=-1);
void SendErrorQueue(void);
//----------------------------------------------------------------------------[]

Log g_rLog;				// класс для хранения имени лог-файла
Sock *g_pSoCl;			// адрес сокета для работы с клиентами
Sock *g_pSoDb;			// адрес сокета для работы с БД
int g_MsgSyn=-1;		// id очереди для синхронизации дочерних процессов
int g_MsgErr=-1;		// id очереди для передачи сообщений головного процесса об ошибках
int g_Sem=-1;			// id блока семафоров
union semun g_sem_nul;				 // структура обнуления семафоров

union semun g_sem_set = {1};// структура установки семафоров 

CONFIG g_rCfg;			// структура конфигурации портов
union semun g_sem_end;// затычка для функции semctl
char g_sConfErr[] = "Configuration error, line "; // сообщение об ошибке конфигурации
Access g_Acc;

//============================================================================[]
// функция формирования информационных сообщений
// в лог-файл и на stdout, если он открыт
void _info(char *msg,int code)
{
	time_t t; time(&t);
	if(g_rCfg.logMode) { // требуется записать событие в файл
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
	if(g_rCfg.logSend) { // требуется передать событие в БД
		MESSAGE_INFO rInfo;
		rInfo.mtype = 1;
		rInfo.time = t;
		strncpy(rInfo.msg+1,msg,INFO_LEN-2);
		rInfo.msg[0] = 1; // код сообщения для БД
		rInfo.msg[INFO_LEN-1] = 0;
		int len = sizeof(rInfo) - int(sizeof(long));
		msgsnd(g_MsgErr,&rInfo,len,0);
	}
//	if(code>=0) exit(code);
}

//============================================================================[]
// функция чтения строки из файла конфигурации с обрезкой начальных
// и конечных пробелов, табуляции и комментариев и с пропуском пустых
// или закомментированмных строк
// параметры: буфер,дескриптор_файла,номер_строки
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
// функция чтения строк файла конфигурации до найденной цепочки
// параметры: буфер,цепочка поиска,дескриптор_файла,номер_строки
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
// функция получения только параметра AccessList из тэга <Config>
// параметры: буфер,дескриптор_файла,номер_строки
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
// функция получения параметров конфигурации из тэга <Config>
// параметры: буфер,дескриптор_файла,номер_строки
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
// функция получения параметров конфигурации из тэга <Access>
// параметры: буфер,дескриптор_файла,номер_строки
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
// функция получения параметров конфигурации из тэга <Group>
// параметры: буфер,имя_группы,дескриптор_файла,номер_строки
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
// функция получения параметров конфигурации из файла broker.cfg
int get_config(char flg)
{
	static char pName[] = "broker.cfg";
	static char sMoThenOnce[] = "was found more then once";
	FILE *fil = fopen(pName,"rt");
	if(!fil) {
		printf("Broker: Error opening configuration file %s!\n",pName);
		return 1;
	}
	char str[SIZE_STRCONFIG]; // буфер для чтения строки
	int err = 0;		// код возврата из функции (0-OK,1-ERR)
	int line = 0;		// номер читаемой строки
	char MainCfg = 0; // флаг для защиты повторного использования тэга <Config>
	char AccCfg = 0; // флаг для защиты повторного использования тэга <Access>
	g_Acc.Clear(); // очистка данных ACL на случай повторного чтения
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
					if(!g_rCfg.ACL) break; // дальше читать не требуется
					continue;
				}
				err++; break;
			}
			if(!config_main(str,fil,&line)) {
				if(!g_rCfg.ACL||flg==CFG_READ_MAIN) break; // дальше читать не требуется
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
//	if(!err&&flg!=CFG_READ_MAIN) { //## распечатка состояния
//		printf("Broker: ACL=%s\n",g_rCfg.ACL?"Yes":"No");
//		g_Acc.Show();
//	}
	return err;
}

//============================================================================[]
// функция передачи команды запущенному ранее демону
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
	g_sem_set.val = flg; // установка значения команднофго семафора
	SEM_SET(SEM_COMMAND); // установка командного семафора

	if(g_pSoCl->connect("127.0.0.1",g_rCfg.portCL)) {
		perror("Broker: connect");
		exit(1);
	}

	printf("\nBroker: Command %s was sent to daemon\n",flg==COMMAND_STOP?"STOP":"RECONFIG");

	exit(0);
}

//============================================================================[]
// функция завершения работы (закрытие очередей и семафоров)
void _end(int err,int info_flg=1)
{
	if(g_MsgSyn>=0) msgctl(g_MsgSyn,IPC_RMID,0); // удаление очереди синхронизации
	if(g_MsgErr>=0) msgctl(g_MsgErr,IPC_RMID,0); // удаление очереди сообщений об ошибках
	if(g_Sem>=0) semctl(g_Sem,0,IPC_RMID,g_sem_end); // удаление семафоров
	if(info_flg) _info("Daemon finished");
	exit(err);
}

//============================================================================[]
// головная функция
// в качестве единственного параметра допускает host-имя сервера,
// на котором расположен процесс-менеджер вызова функций БД
// если данный параметр опущен, значение берется из файла конфигурации
int main(int argc,char *argv[])
{
	MESSAGE_HEADER rMsg; // структура элемента в очереди сообщений
	int _err = 0;	// статус ошибки для завершения работы

	if(get_config(argc>1?CFG_READ_MAIN:CFG_READ_ALL)) return 1;

	Sock SoCl(AF_INET,SOCK_STREAM); // класс сокет для работы с клиентами
	Sock SoDb(AF_INET,SOCK_STREAM); // класс сокет для связи с менеджером функций БД

// установка доступа к сокетам через глобальные адреса.
// глобально передаются только адреса сокетов, потому что при
// завершении дочерних процессов могут возникнуть проблемы
// с закрытием глобальных сокетов:
	g_pSoCl = &SoCl;
	g_pSoDb = &SoDb; 


	if(argc>1) {
		if(argv[1][0]=='-') {
			if(argv[1][1]=='d') send_daemon(COMMAND_STOP);
			if(argv[1][1]=='r') send_daemon(COMMAND_RECONFIG);
/* // удаление очередей сообщений:
		if(if(argv[1][1]=='m') {
			g_MsgErr = msgget(MSGERRKEY,IPC_CREAT|0666);
			g_MsgSyn = msgget(MSGSYNKEY,IPC_CREAT|0666);
			if(g_MsgSyn>=0) msgctl(g_MsgSyn,IPC_RMID,0); // удаление очереди синхронизации
			if(g_MsgErr>=0) msgctl(g_MsgErr,IPC_RMID,0); // удаление очереди сообщений об ошибках
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
// Создаем очередь для управления последовательностью
// выполнения обработчиков:
	g_MsgSyn = msgget(MSGSYNKEY,IPC_CREAT|0666); //IPC_EXCL
	if(g_MsgSyn==-1) {
		perror("Broker: msgget[syn]");
		_end(1,0);
	}

// профилактическая очистка очереди:
	while(msgrcv(g_MsgSyn,&rMsg,1,0,MSG_NOERROR|IPC_NOWAIT)>=0);

// Создаем очередь для сообщения об ошибках родительского процесса:
	g_MsgErr = msgget(MSGERRKEY,IPC_CREAT|0666);
	if(g_MsgErr==-1) {
		perror("Broker: msgget[err]");
		_end(1,0);
	}


// профилактическая очистка очереди:
	while(msgrcv(g_MsgErr,&rMsg,1,0,MSG_NOERROR|IPC_NOWAIT)>=0);


// Создаем 2-элементный семафор (командный и реконнекта)
	g_Sem = semget(SEMKEY,SEM_QUAN,IPC_CREAT|0666); //IPC_EXCL
	if(g_Sem==-1) {
		perror("Broker: semget");
		_end(1,0);
	}
// обнуление семафоров:
	SEM_CLR(SEM_COMMAND);
	SEM_CLR(SEM_RECONNECT);

// Создаем сокет для прослушивания клиентов:
	if(!g_pSoCl->good()) {
		perror("Broker: socket [Client]");
		_end(1,0);
	}
	if(g_pSoCl->bind(0,g_rCfg.portCL)<0) _end(1,0);

// Создаем сокет для открытия канала связи с БД:
	if(!g_pSoDb->good()) {
		perror("Broker: socket [DataBase]");
		_end(1,0);
	}


	if(g_pSoDb->connect(g_rCfg.host,g_rCfg.portDB)) {
		perror("Broker: connect [DataBase]");
		_end(1,0);
	}
/*
// операции для преобразования процесса в демон:
	if(getppid()!=1) { // родитель не init
		signal(SIGTTOU,SIG_IGN);
		signal(SIGTTIN,SIG_IGN);
		signal(SIGTSTP,SIG_IGN);
	}
*/
/*
	if(fork()!=0) exit(0); // родитель завершил работу
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
// завершающие операции для преобразования процесса в демон:
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	signal(SIGINT,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
*/
	signal(SIGCHLD,pchild); // установка обработчика сигнала SIGCLD

	long MyPid = 1;	// номер запроса, он же внутренний идентификатор процесса
	int ns;				// идентификатор отпочкованного сокета

	int num_sec = 0;	// статистика (накопление запросов в секунду)
	int rps = 0;		// статистика (запросов в секунду)

	time_t t,t_sav;
	time(&t_sav);

// для разрешения самому первому дочернему процессу продолжать
// работу без ожидания засвершения работы предыдущего процесса
// кладем в очередь сообщение:
	rMsg.mtype = MyPid;
	msgsnd(g_MsgSyn,&rMsg,1,0); // perror("msgsnd");

	int val = 1; // установка флага в опциях сокета
// в данном режиме устанавливается дополнительный контроль
// соединения перед операциями чтения/записи, при разрыве связи
// возртат из функций чтения/записи происходит с кодом -1
// и генерируется сигнал SIGPIPE, который мы игнорируем:
	signal(SIGPIPE,SIG_IGN);
	setsockopt(g_pSoDb->fd(),SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val));



// цикл прослушивания сокета на предмет прихода запросов от клиентов
	for(;;) 
	{
	// проверка командного семафора
		switch (SEM_TST(SEM_COMMAND)) 
		{ 
			case COMMAND_STOP :
				_end(0); // завершение работы
			break;
			case COMMAND_RECONFIG :
				SEM_CLR(SEM_COMMAND);
				if(g_rCfg.ACL) { // обновить только если включен режим ACL
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

	// проверка командного семафора
		switch (SEM_TST(SEM_COMMAND)) 
		{
			case COMMAND_STOP :
				close(ns);
				_end(0); // завершение работы
			break;
			case COMMAND_RECONFIG :
				SEM_CLR(SEM_COMMAND);
				if(g_rCfg.ACL) { // обновить только если включен режим ACL
					if(get_config(CFG_READ_ACL)) {
						_info("Error reread configuration file!",1);
						_end(1);
					}
				}
			break;
		}

	// переподцепление к БД
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

		long PrewPid = MyPid; // сохраняем номер предыдущего запроса
		MyPid++; if(MyPid<=0) MyPid = 1;

//--------- статистика запросов
		time(&t); num_sec++;
		if(t_sav!=t) 
		{
			t_sav = t;
			rps = num_sec;
			num_sec = 0;
		}
//------------------------------

		int pid = fork(); // создаем дочерний процесс

	// ветвь дочернего процесса
		if(pid==0) 
		{ 
		//#### здесь закрыть головной сокет CL ???
			prc_request (ns,MyPid,PrewPid,rps);
			// close(ns); //` 25.12.1999 RomanVK: -- закрытие перенесено в prc_request
			exit(0);
		}
		if(pid==-1) msg_to_user(ns,"Error request processing!");
		close(ns); // закрыли отпочкованный в дорчерний процесс дескриптор сокета
	}
//----------------------------------------------------------------------------[] 

	_end(_err);
	return _err;
}

//============================================================================[]
// функция-обработчик сигнала SIGCHLD, который посылается
// родительскому процессу при завершении работы дочернего
// используется только для очистки таблицы процессов от информации
// об удаленном дочернем процессе
void pchild(int from_pid)
{ // эта функция используется для удаления записей завершенных дочерних процессов
	int status;
	while(waitpid((pid_t)-1,&status,WNOHANG)>0);
	signal(SIGCHLD,pchild); // снова устанавливаем обработчик сигнала SIGCLD
}

//============================================================================[]
// функция формирования заголовка запроса на основании
// текста полученного от системы скриптов (PHP3)
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
	time(&(pHead->time)); // получили время запроса
	return 0;
}
//____________________________________________________________________________[]






#define SayToUserAndPermitToChild(x) {msg_to_user(ns,x); msgsnd(g_MsgSyn,&rMsg,1,0);}

//______________________________________________________________________________
//                                                                            []
// функция выполняется дочерним процессом, который формируется						[]
// при очередном запросе клиента																[]
//                                                                            []
void prc_request (int ns,long MyPid,long PrewPid,int rps)
{
	fd_set rfds;
	struct timeval tv;

	int nbytes,i;
	int retval;
	REQUEST_HEADER rHead;	// структура заголовка запроса
	MESSAGE_HEADER rMsg;		// структура элемента в очереди сообщений
	rMsg.mtype = MyPid;		// тип сообщения - идентификатор тек.процесса

	FD_ZERO(&rfds);
	FD_SET(g_pSoDb->fd(),&rfds);
	tv.tv_usec = 0;

// Получение заголовка запроса
	if(get_header(ns,&rHead)) 
	{ 
		SayToUserAndPermitToChild ("Error in request header format, request refused");
		close(ns); //` 25.12.1999 RomanVK: 
		return;
	}

	char *buf = new char [sizeof(REQUEST_HEADER)+rHead.quan+1]; // +1 для 0 на конце
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


// Требуется проверка доступа к функциям
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
	// доступ к данной функции запрещен
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


// Засыпаем до прихода сообщения от предыдущего процесса
// ("старшего брата") о том, что он освободил канал,
// так как к данному моменту мы готовы работать с БД и ждем
// ее освобождения:
	int len = msgrcv (g_MsgSyn, &rMsg, 1, PrewPid, MSG_NOERROR);
// восстановили тип сообщения - идентификатор тек.процесса
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

// остался только размер сообщения
	ret.quan -= int(SIZE_HEAD);
	buf = new char [ret.quan+SIZE_RETCODE+1];
// записываем код возврата
	sprintf(buf,"%10d",ret.ret_code);
	retval = g_pSoDb->read(buf+SIZE_RETCODE,ret.quan,MSG_WAITALL);

	if(retval<ret.quan)
	{
		msg_to_user (ns,"Incomplit data received from DB, request refused");
	}
	else 
	{
	// сброс в БД списка событий, если он есть
		SendErrorQueue (); 
	}

	send (ns,buf,ret.quan+SIZE_RETCODE,0);
	close(ns); //` 25.12.1999 RomanVK: 

// сообщение следующему процессу об освобождении БД
	msgsnd (g_MsgSyn,&rMsg,1,0); 
	buf[ret.quan+SIZE_RETCODE] = 0;

	delete buf;
}
//____________________________________________________________________________[]








//============================================================================[]
// функция отсылки пользователю сообщения об ошибке в процессе
// обработки запроса
void msg_to_user(int ns,char *pMsg)
{
	fd_set rfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(ns,&rfds);
	tv.tv_sec = 0; // не ждать
	tv.tv_usec = 0;
	char buf[SIZE_MAX_BUFER]; // буфер для выжирания данных из сокета
	unsigned int u = 1;
	_info(pMsg,1);
	ioctl(ns,FIONBIO,&u); // снимаем блокировку с нового дескриптора сокета
	while(recv(ns,buf,SIZE_MAX_BUFER-1,0)>0);
//### здесь нужно послать код ошибки в первые SIZE_RETCODE байт
	sprintf(buf,"%10d",-2); // записываем код возврата
	strcpy(buf+SIZE_RETCODE,pMsg);
	send (ns,buf,strlen(pMsg)+SIZE_RETCODE,0);
}

//============================================================================[]
// функция отсылки в БД списка событий, накопившихся к данному моменту
void SendErrorQueue()
{
	char buf[sizeof(REQUEST_HEADER)+INFO_LEN];
	MESSAGE_INFO rMsg;
	memset(buf,0,sizeof(buf));
	int len = sizeof(MESSAGE_INFO)-int(sizeof(long));
	REQUEST_HEADER *pHead = (REQUEST_HEADER*)buf;
	pHead->quan = INFO_LEN;
	strcpy(pHead->mirrIP,"mirrorBSD"); // адрес отправителя
// получения и отправка в БД всех сообщений:
	while(msgrcv(g_MsgErr,&rMsg,len,0,MSG_NOERROR|IPC_NOWAIT)>=0) {
		pHead->time = rMsg.time;
		strcpy(buf+sizeof(REQUEST_HEADER),rMsg.msg);
		if(g_pSoDb->write(buf,sizeof(buf))<sizeof(buf)) break;
	}
}


//============================================================================[]
// функции-члены класса Access
//============================================================================[]
//============================================================================[]
// функция очистки данных ACL
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
// функция добавления ip-адреса в список
int Access::AddIP(char *pIPName,char *pGrpName,int *pLine)
{ // ret: 0-OK, 1-не найдена группа из списка,2-нет памяти
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
	if(p) *p = 0; // обрезка правых пробелов
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
// функция добавления группы в список
int Access::AddGrp(char *pName,FILE *fil,int *pLine)
{ // ret: 0-ОК,1-нет памяти
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
		if(p) *p = 0; // обрезка правых пробелов
		num++;
	}
	return 0;
}

//============================================================================[]
// функция проверки на возможность выполнения DB-функций
int Access::Permit(char *pAddr,char *pFun)
{
// N.N.N.N - проверять нули (распространяется на всю подсеть)
// '*' в конце имени функции распространение на все функции с таким началом
	ACCESS_IP_TYPE *pIP = pTopIP;
	while(pIP) {
		if(Belong(pAddr,pIP->IP)) { // IP принадлежит диапазаону
			for(int i=0;i<pIP->quan;i++) {
				for(int j=0;j<pIP->pMas[i]->quan;j++) {
					char *pDan = pIP->pMas[i]->pMas + j * SIZE_STRFUN;
					int l = strlen(pDan) - 1;
					if(pDan[l]=='*') l = strncmp(pDan,pFun,l);
					else l = strcmp(pDan,pFun);
					if(!l) return 1; // ОК
				}
			}
			break; //## проверяется только первый встреченный адрес ??
		}
		pIP = pIP->pNext;
	}
	return 0;
}

//============================================================================[]
// функция проверки принадлежности IP-адреса
int Access::Belong(char *pAddr,char *pMask)
{
	int iMask[4],iAddr[4];
	sscanf(pMask,"%d.%d.%d.%d",&(iMask[0]),&(iMask[1]),&(iMask[2]),&(iMask[3]));
	sscanf(pAddr,"%d.%d.%d.%d",&(iAddr[0]),&(iAddr[1]),&(iAddr[2]),&(iAddr[3]));
	for(int i=3;i>=0;i--)
		if(iMask[i]!=0&&iMask[i]!=iAddr[i]) return 0;
	return 1; // ОК
}

//============================================================================[]
// ### функция тестовой распечатки состояния ACL
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

