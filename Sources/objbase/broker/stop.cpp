/*______________________________________________________________________________
[]																										[]
[] This is a part of the PROJECT: 'ObjectBase:CGI'										[]
[] 																									[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          stop.cpp																		[]
[] Date:          20.08.99																		[]
[] Author:        Semyon N. Vepritskiy, Roman V. Koshelev							[]
[] Description:   демон связи пользовательских запросов с менеджером БД			[]
[]____________________________________________________________________________[]
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

#define	SIZE_STRCONFIG 200		// размер строки чтения конфигурации
#define	SIZE_STRIP 15				// размер строки IP-адреса

char		g_pLogName[200];			// расположение лог-файла для протокола времени выполнения функций


//______________________________________________________________________________
//                                                                            []
//` заголовок запроса                                                         []                 
//                                                                            []
struct REQUEST_HEADER
{
	unsigned int quan;				// количество данных в запросе
	char userIP[SIZE_STRIP+1];		// IP-адрес пользователя
	char mirrIP[SIZE_STRIP+1];		// IP-адрес зеркала
	time_t time;						// время прихода запроса (к обработчикам)
};
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// функция чтения строки из файла конфигурации с обрезкой начальных				[]
// и конечных пробелов, табуляции и комментариев и с пропуском пустых			[]
// или закомментированмных строк																[]
// параметры: буфер,дескриптор_файла,номер_строки										[]
//																										[]
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
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
// функция получения номера PHP-порта из файла конфигурации							[]
// из файла db.cfg																				[]
//																										[]
int get_port()
{
	static char pName[] = "db.cfg";
	static char sDeliv[] = "= ";
	int port = -1;
	FILE *fil = fopen(pName,"rt");
	if(!fil) {
		printf("DB: Error opening configuration file %s!\n",pName);
		return port;
	}
	char str[SIZE_STRCONFIG];
	int line = 0;
	for(;;) {
		char *p = get_string(str,fil,&line);
		if(!p) break;
		if(!strcmp(p,"<Config>")) {
			for(;;) {
				p = get_string(str,fil,&line);
				if(!p) break;
				if(!strcmp(p,"</Config>")) break;
				p = strtok(p,sDeliv);
				if(!p) continue;
				char *pVol = strtok(NULL,sDeliv);
				if(!pVol) {
					printf("STOP: Error configuration file format %s, line %d!\n",pName,line);
					break;
				}
				if(!strcmp(p,"PortDB")) port = atoi(pVol);
				else if(!strcmp(p,"LogPath")) {
					strcpy(g_pLogName,pVol);
					int len = strlen(g_pLogName);
					if(g_pLogName[len-1]!='/') g_pLogName[len] = '/';
				}
			}
			break;
		}
	}
	fclose(fil);
	return port;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` main                                                                      []    
//                                                                            []
int main (int argc,char *argv[])
{
	Sock SoDb(AF_INET,SOCK_STREAM);

// Создаем сокет для открытия канала связи с БД:
	if(!SoDb.good()) 
	{
		perror("STOP: socket [DataBase]");
		return 1;
	}

	if(SoDb.connect("127.0.0.1", get_port())) 
	{
		perror("STOP: connect [DataBase]");
		return 1;
	}

	char	 buf   [1000];
	memset (buf,0,1000);

	printf("\n\nSTOP: Command STOP was sent to daemon\n");
	SoDb.write (buf, 1000);
	printf("\n\n");

	return 0;
}
//____________________________________________________________________________[]


