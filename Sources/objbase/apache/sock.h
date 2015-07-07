// sock.h: interface for the sock class.
//
//////////////////////////////////////////////////////////////////////
// Copyright: Terence Chan
// Writed by Dima Polyakov, 2000
// HomeLabs Software. 2000
// Public Code

#if !defined(AFX_SOCK_H__B9196655_CDA7_11D3_84BD_00A0C99EDEF8__INCLUDED_)
#define AFX_SOCK_H__B9196655_CDA7_11D3_84BD_00A0C99EDEF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// common block
#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>

#include "CString.h"

// windows block
#ifdef _WIN32
#include "winsock.h"
#include <io.h>
#endif

// unix block
#ifndef _WIN32
#include <sys/socket.h>
#include <sys/systeminfo.h>
#include <netdb.h>
#endif

const int BACKLOG_NUM = 5;

class sock  
{
private:
	int sid;
	int domain;
	int socktype;
	int rc;//return code

	// create Internet socket name using host and port number
	int constr_name(struct sockaddr_in &addr, const char *hostnm, int port)
	{
		addr.sin_family = domain;

		if(!hostnm)
		{
			#ifdef _WIN32
			// windows
				addr.sin_addr.S_un.S_addr = INADDR_ANY;
			#else
			// Unix
				addr.sin_addr.s_addr = INADDR_ANY;
			#endif
		}
		else
		{
			struct hostent *hp = gethostbyname(hostnm);
			if(!hp)
			{
				error_str += "::gethostbyname(...) is failure\n";
				return -1;
			}
			memcpy((char *)&addr.sin_addr, (char *)hp->h_addr, hp->h_length);
		}
		addr.sin_port = htons(port);
		return sizeof(addr);
	};

	// create a socket name using path name
	int constr_name(struct sockaddr &addr, const char *Pathnm)
	{
		addr.sa_family = domain;
		strcpy(addr.sa_data, Pathnm);
		return sizeof(addr.sa_family)+strlen(Pathnm)+1;
	};

	// convert IP address to host name
	char *ip2name(const struct in_addr in)
	{
		u_long laddr;
		if((int)(laddr=inet_addr(inet_ntoa(in))) == -1) return 0;
		struct hostent *hp = gethostbyaddr((char *)&laddr, sizeof(laddr), AF_INET);
		if(!hp) return 0;
		for(char **p = hp->h_addr_list; *p!=0; p++)
		{
			memcpy((char*)&in.s_addr, *p, sizeof(in.s_addr));
			if(hp->h_name) return hp->h_name;
		}
		return 0;
	};

public:
	String error_str;
	String socket_port_str;

	sock(int dom, int type, int protocol=0):domain(dom), socktype(type)
	{
		error_str = "";
		if((sid=socket(domain=dom, socktype=type, protocol))<0)
			error_str += "::socket(...) is failure\n";
	};

	~sock() {shutdown(); close(sid);};

	int fd() {return sid;};// socket description
	int good() {return sid>=0;};// status by sock object

	int bind(const char * name, int port=-1)
	{
		if(port==-1)
		{
			struct sockaddr addr;
			int len = constr_name(addr, name);
			if((rc=::bind(sid, &addr, len))<0) error_str += "::bind(...) is failure\n";
		}
		else
		{
			struct sockaddr_in addr;
			int len = constr_name(addr, name, port);
			if((rc=::bind(sid, (struct sockaddr *)&addr, len))<0 ||
				(rc=getsockname(sid, (struct sockaddr*)&addr, &len))<0)
					error_str += "::bind(...) or ::getsockname(...) is failure\n";
			else
			{
				socket_port_str = "Socket port: ";
				socket_port_str += ntohs(addr.sin_port);
			}
		}
		if(rc!=-1 && socktype!=SOCK_DGRAM && (rc=listen(sid, BACKLOG_NUM))<0)
			error_str += "::listen(...) is failure\n";
		return rc;
	}

	int accept(char *name, int *port_p)
	{
		if(!name) return ::accept(sid, 0, 0);
		if(!port_p || *port_p == -1)
		{
			struct sockaddr addr;
			int size=sizeof(addr);
			if((rc=::accept(sid, &addr, &size)) > -1)
			{
				strncpy(name, addr.sa_data, size);
				name[size]='\0';
			}
		}
		else
		{
			struct sockaddr_in addr;
			int size = sizeof(addr);
			if((rc=::accept(sid, (struct sockaddr*)&addr, &size)) > -1)
			{
				if(name) strcpy(name, ip2name(addr.sin_addr));
				if(port_p) *port_p = ntohs(addr.sin_port);
			}
		}
		return rc;
	};

	int connect(const char *hostnm, int port=-1)
	{
		if(port==-1)
		{
			struct sockaddr addr;
			int len = constr_name(addr, hostnm);
			if((rc=::connect(sid, &addr, len)) < 0)
				error_str += "::connect(...) is failure\n";
		}
		else
		{
			struct sockaddr_in addr;
			int len = constr_name(addr, hostnm, port);
			if((rc=::connect(sid, (struct sockaddr *)&addr, len)) < 0)
				error_str += "::connect(...) is failure\n";
		}
		return rc;
	};

	// write the message
	int write(const char* buf, int len, int flag=0, int nsid=-1)
	{
		return ::send(nsid==-1?sid:nsid, buf, len, flag);
	};

	// read the message
	int read(char *buf, int len, int flag=0, int nsid=-1)
	{
		return ::recv(nsid==-1?sid:nsid, buf, len, flag);
	};

	// write to socket UNIX domen with the name
	int writeto(const char *buf, int len, int flag, const char *name, const int port, int nsid=-1)
	{
		if(port==-1)
		{
			struct sockaddr addr;
			int size = constr_name(addr, name);
			return ::sendto(nsid==-1?sid:nsid, buf, len, flag, &addr, size);
		}
		else
		{
			struct sockaddr_in addr;
			char buf1[80];
			if(!name)
			{
				// use local host
				#ifndef _WIN32
					if(sysinfo(SI_HOSTNAME, buf1, 80)==-1L)
						error_str += "::sysinfo(...) is failure\n";
				#else
					::gethostname(buf1,  80);
				#endif
				name = buf1;
			}
			int size = constr_name(addr, name, port);
			return ::sendto(nsid==-1?sid:nsid, buf, len, flag, (struct sockaddr*)&addr, size);
		}
	};

	int readfrom(char *buf, int len, int flag, char *name, int *port_p, int nsid=-1)
	{
		if(!port_p || *port_p == -1)
		{
			struct sockaddr addr;
			int size = sizeof(addr);
			if((rc=::recvfrom(nsid==-1?sid:nsid, buf, len, flag, &addr, &size)) > -1 && name)
				strncpy(name, addr.sa_data, rc), name[rc]='\0';
		}
		else
		{
			struct sockaddr_in addr;
			int size = sizeof(addr);
			if((rc=::recvfrom(nsid==-1?sid:nsid, buf, len, flag, (struct sockaddr *)&addr, &size)) >=1)
			{
				if(name) strcpy(name, ip2name(addr.sin_addr));
				if(port_p) *port_p = ntohs(addr.sin_port);
			}
		}
		return rc;
	};

	int shutdown(int mode = 2)// close socket
	{
		return ::shutdown(sid, mode);
	};
};

#endif // !defined(AFX_SOCK_H__B9196655_CDA7_11D3_84BD_00A0C99EDEF8__INCLUDED_)
