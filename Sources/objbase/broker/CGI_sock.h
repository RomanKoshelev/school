/*______________________________________________________________________________
[]																										[]
[] This is a part of the PROJECT: 'ObjectBase:CGI'										[]
[] 																									[]
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          sock.h																		[]
[] Date:          20.08.99																		[]
[] Author:        Semyon N. Vepritskiy														[]
[] Description:   класс, инкапсулирующий низкоуровневые API-функции сокетов	[]
[]____________________________________________________________________________[]
*/
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#ifndef SOCK_H
#define SOCK_H
const int BACKLOG_NUM = 100;

class Sock
{
private:
	int m_sid;			// дескриптор сокета
	int m_domain;		// домен сокета
	int m_socktype;	// тип сокета
	int m_rc;			// код возврата (?)

	int constr_name(struct sockaddr_in *addr,
					const char *hostname,
					int port)
	{ // создание интернет-сокета по хост-имени и номеру порта
		bzero(addr,sizeof(*addr));
		addr->sin_family = m_domain;
		if(!hostname) addr->sin_addr.s_addr = INADDR_ANY;
		else {
			struct hostent *hp = gethostbyname(hostname);
			// if (!hp) { perror("gethostbyname"); return -1; }
			memcpy(&(addr->sin_addr),hp->h_addr,hp->h_length);
//			bcopy(&(addr->sin_addr),hp->h_addr,hp->h_length);
		}
		addr->sin_port = htons(port);
		return sizeof(*addr);
	}

	int constr_name(struct sockaddr& addr,
					const char *pathname)
	{ // создание сокета домена UNIX по имени
		addr.sa_family = m_domain;
		strcpy(addr.sa_data,pathname);
		return (sizeof(addr.sa_family)+strlen(pathname)+1);
	}

	char *ip2name(const struct in_addr in)
	{
		u_long laddr = inet_addr(inet_ntoa(in));
		if(((int)laddr)==-1) return 0;
		struct hostent *hp = gethostbyaddr((char*)&laddr,sizeof(laddr),AF_INET);
		if(!hp) return 0;
		for(char **p = hp->h_addr_list;*p;p++) {
			memcpy((void*)&(in.s_addr),*p,sizeof(in.s_addr));
			if(hp->h_name) return hp->h_name;
		}
		return 0;
	}
public:
	Sock(int dom, int type,int protocol=0) : m_domain(dom), m_socktype(type)
	{
		m_sid = socket(m_domain=dom,m_socktype=type,protocol);
	}

	~Sock() { shutdown(); close(m_sid); }

	int fd() { return m_sid; }
	int good() { return m_sid>=0; }

	int bind(const char *name,int port=-1)
	{
		if(port==-1) { // сокет домена UNIX
			struct sockaddr addr;
			int len = constr_name(addr,name);
			if((m_rc=::bind(m_sid,&addr,len))<0) perror("bind");
		}
		else { // интернет сокет
			struct sockaddr_in addr;
			int len = constr_name(&addr,name,port);
			if((m_rc=::bind(m_sid,(struct sockaddr*)&addr,len))<0 ||
				(m_rc=getsockname(m_sid,(struct sockaddr*)&addr,&len))<0)
				perror("bind or getsockname");
//			else
//				printf("Socket port: %s\n",ntohs(addr.sin_port));
//			}
		}
		if(m_rc!=-1 && m_socktype!=SOCK_DGRAM &&
			(m_rc = listen (m_sid, BACKLOG_NUM))<0)
			perror("listen");
		return m_rc;
	}

	int accept(char *name,int *port_p)
	{
//		if(!name) return ::accept(m_sid,0,0);
		if(!port_p||*port_p==-1) { // домен UNIX
			if(!name) return ::accept(m_sid,0,0);
			struct sockaddr addr;
			int size = sizeof(addr);
			if((m_rc=::accept(m_sid,&addr,&size))>-1)
				strncpy(name,addr.sa_data,size), name[size]='\0';
		}
		else {
			struct sockaddr_in addr;
			int size = sizeof(addr);
			if((m_rc=::accept(m_sid,(struct sockaddr*)&addr,&size))>-1) {
				if(name) strcpy(name,ip2name(addr.sin_addr));
				if(port_p) *port_p = ntohs(addr.sin_port);
			}
		}
		return m_rc;
	}

	int connect(const char *hostname, int port=-1)
	{
		if(port==-1) { // домен UNIX
			struct sockaddr addr;
			int len = constr_name(addr,hostname);
			m_rc = ::connect(m_sid,&addr,len);
		}
		else {
			struct sockaddr_in addr;
			int len = constr_name(&addr,hostname,port);
			m_rc = ::connect(m_sid,(struct sockaddr*)&addr,len);
		}
//		if(m_rc<0) perror("connect");
		return m_rc;
	}

	int reconnect(const char *hostname, int port)
	{
		shutdown(); close(m_sid);
		m_sid = socket(m_domain,m_socktype,0);
		if(m_sid<0) return -1;
		return connect(hostname,port);
	}

	int write(const char *buf,int len,int flag=0,int nsid=-1)
	{
		return ::send(nsid==-1?m_sid:nsid,buf,len,flag);
	}

	int read(const char *buf,int len,int flag=0,int nsid=-1)
	{
		return ::recv(nsid==-1?m_sid:nsid,(void*)buf,len,flag);
	}

	int shutdown(int mode=2)
	{
		return ::shutdown(m_sid,mode);
	}

	int writeto(const char *buf,int len,int flag,
				const char *name,const int port,int nsid=-1)
	{
		if(port==-1) { // домен UNIX
			struct sockaddr addr;
			int size = constr_name(addr,name);
			return ::sendto(nsid==-1?m_sid:nsid,buf,len,flag,&addr,size);
		}
		struct sockaddr_in addr;
		char buf1[80];
		if(!name) { // если не указано, используем локальное имя хоста
//			if(sysinfo(SI_HOSTNAME,buf1,sizeof(buf1))==-1L)
//				perror("sysinfo");
			strcpy(buf1,"127.0.0.1");
			name = buf1;
		}
		int size = constr_name(&addr,name,port);
		return ::sendto(nsid==-1?m_sid:nsid,buf,len,
						flag,(struct sockaddr*)&addr,size);
	}

	int readfrom(char *buf,int len,int flag,
				char *name,int *port_p,int nsid=-1)
	{
		if(!port_p||*port_p==-1) { // домен UNIX
			struct sockaddr addr;
			int size = sizeof(addr);
			if((m_rc=::recvfrom(nsid==-1?m_sid:nsid,buf,len,
								flag,&addr,&size))>-1&&name)
					strncpy(name,addr.sa_data,m_rc), name[m_rc]='\0';
		}
		else {
			struct sockaddr_in addr;
			int size = sizeof(addr);
			if((m_rc=::recvfrom(nsid==-1?m_sid:nsid,buf,len,
								flag,(struct sockaddr*)&addr,&size))>-1) {
				if(name) strcpy(name,ip2name(addr.sin_addr));
				if(port_p) *port_p = ntohs(addr.sin_port);
			}
		}
		return m_rc;
	}

};
#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
