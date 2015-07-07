/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            URL.cpp                                                   []
[] Date:            31.03.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#define	USES_string_h
#include "main.h"
#include "URL.h"


/*______________________________________________________________________________
[]                                                                            []
[]` Init                                                                      []
[]                                                                            */
void HTTP_URL::Init ()
{
	m_login		[0] =	0;
	m_password	[0] =	0;
	m_domain		[0] =	0;
	m_port		[0] =	0;
	m_path		[0] =	0;
	m_file		[0] =	0;
	m_ext			[0] =	0;
	m_args		[0] =	0;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` HTTP_URL                                                                  []
[]                                                                            */
HTTP_URL::HTTP_URL ()
{
	Init ();
}
//----------------------------------------------------------------------------[]
HTTP_URL::HTTP_URL (const char * sURL)
{
	Parse (sURL);
}
//----------------------------------------------------------------------------[]
HTTP_URL::HTTP_URL (const HTTP_URL& from)
{
	CopyFrom (from);
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` CopyFrom                                                                  []        
[]                                                                            */
void HTTP_URL::CopyFrom (const HTTP_URL& from)
{
	/*
	strcpy (m_login	,	from.m_login		);
	strcpy (m_password,	from.m_password	);
	strcpy (m_domain	,	from.m_domain		);
	strcpy (m_port		,	from.m_port			);
	strcpy (m_path		,	from.m_path			);
	strcpy (m_file		,	from.m_file			);
	strcpy (m_ext		,	from.m_ext			);
	strcpy (m_args		,	from.m_args			);
	*/
	memcpy (this, &from, sizeof (*this));
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]` operator =                                                                []          
[]                                                                            */
HTTP_URL& HTTP_URL::operator= (const HTTP_URL& from)
{
	CopyFrom (from);
	return * this;
}
//----------------------------------------------------------------------------[] 
HTTP_URL& HTTP_URL::operator= (const char * sURL)
{
	Parse (sURL);
	return * this;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]` operator ==                                                               []           
[]                                                                            */
bool HTTP_URL::operator== (const HTTP_URL& to)
{
	if (strcmp (m_domain, to.m_domain))
		return false;
	if (strcmp (m_path, to.m_path))
		return false;
	if (strcmp (m_file, to.m_file))
		return false;
	if (strcmp (m_ext, to.m_ext))
		return false;
	return true;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` IsChildFor                                                                []          
[]                                                                            */
bool HTTP_URL::IsChildFor (const HTTP_URL& Parent)
{
	int i=0;
// Домены должны совпадать
	if (strcmp (m_domain, Parent.m_domain))
		return false;
// Родительский путь должен быть частью дочернего
	for (i=0; Parent.m_path[i]; i++)
	{
		if (m_path[i]!=Parent.m_path[i])
			return false;
	}
	return true;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` Domain                                                                    []      
[]                                                                            */
void HTTP_URL::Domain (string& str)
{
	str = m_domain;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` Path                                                                      []    
[]                                                                            */
void HTTP_URL::Path (string& str)
{
	str = m_path;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` Args                                                                      []    
[]                                                                            */
void HTTP_URL::Args (string& str)
{
	str = m_args;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DomainPath                                                                []          
[]                                                                            */
void HTTP_URL::DomainPath (string& str)
{
	str  = m_domain;
	if (m_path[0])
	{
		str += "/";
		str += m_path;
	}
	str += "/";
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DomainPathFile                                                            []              
[]                                                                            */
void HTTP_URL::DomainPathFile (string& str)
{
	DomainPath (str);
	if (m_file[0])
	{
		if (m_path[0]==0 && m_domain[0]==0)
		{
			str += "/";
		}
		str += m_file;
	}
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DomainPathFileExt                                                         []                 
[]                                                                            */
void HTTP_URL::DomainPathFileExt (string& str)
{
	DomainPathFile (str);
	if (m_ext[0])
	{
		str += ".";
		str += m_ext;
	}
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DomainPathFileExtArgs                                                     []                     
[]                                                                            */
void HTTP_URL::DomainPathFileExtArgs (string& str)
{
	DomainPathFileExt (str);
	if (m_args[0])
	{
		str += "?";
		str += m_args;
	}
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` URL                                                                       []   
[]                                                                            */
void HTTP_URL::URL (string& str)
{
	string tmp_str;
	DomainPathFileExtArgs (tmp_str);
	str = "http://";
	str += tmp_str;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DebugPrint                                                                []          
[]                                                                            */
void HTTP_URL::DebugPrint ()
{
	string ResURL = "[";
	ResURL += "http:";
	ResURL += "//";

	if (m_login[0])
	{
		ResURL += m_login;
		if (m_password[0])
		{
			ResURL += ":";
			ResURL += m_password;
		}
		ResURL += "@";
	}
	ResURL += m_domain;
	if (m_port[0])
	{
		ResURL += ":";
		ResURL += m_port;
	}

	ResURL += "/";

	if (m_path[0])
	{
		ResURL += m_path;
		ResURL += "/";
	}

	if (m_file[0])
	{
		ResURL += m_file;
		if (m_ext[0])
		{
			ResURL += ".";
			ResURL += m_ext;
		}
	}

	if (m_args[0])
	{
		ResURL += "?";
		ResURL += m_args;
	}
	ResURL += "]";
	ResURL.Print();

	printf ("\n\n");
	printf ("login    = [%s]\n", m_login);
	printf ("password = [%s]\n", m_password);
	printf ("domain   = [%s]\n", m_domain);
	printf ("port     = [%s]\n", m_port);
	printf ("path     = [%s]\n", m_path);
	printf ("file     = [%s]\n", m_file);
	printf ("ext      = [%s]\n", m_ext);
	printf ("args     = [%s]\n", m_args);
}
//____________________________________________________________________________[]









/*______________________________________________________________________________
[]                                                                            []
[]` Parse                                                                     []     
[]                                                                            */
void HTTP_URL::Parse (const char * _sURL)
{
	Init			 ();
	int	i		= 0;
	int	j		= 0;
	static char URL[MAX_URL_SIZE+1];
	static char SSS[MAX_URL_SIZE];

	strncpy (URL, _sURL, MAX_URL_SIZE-1);
	URL[MAX_URL_SIZE-1]=0;


// Заменяем слеши на корректные
	for (i=0; URL[i]; i++)
	{
		if (URL[i]=='\\')	URL[i]='/';
	}

	for (i=0; i<10; i++)
	{
		char C = URL[i];
		SSS[i  ] = C<'A'?C: (char)(C>=((char)'a')? C: C+32);
		SSS[i+1] = 0;
		if (C==':' || C=='/')
			break;
	}

// Находим позицию окончания протокола
	if ((strcmp(SSS,"http:")==0) || (strcmp(SSS,"htp:")==0) || (strcmp(SSS,"http:")==0) || (strcmp(SSS,"ttp:")==0) || (strcmp(SSS,"http/")==0))
	{
		i = strlen (SSS);
	}
	else
	{
		i=0;
	}
	
// Пропускаем ':' и '/'
	for (;URL[i]=='/' || URL[i]==':'; i++);

// ЛОГИН, ПАРОЛЬ, ДОМЕН, ПОРТ --  До первого знака '/' или '?' или до конца
	for (j=0; (URL[i]!=0) && (URL[i]!='/') && (URL[i]!='?'); i++,j++)
	{
		m_domain[j  ] = URL[i];
		m_domain[j+1] = 0;
	}

// Пропускаем '/'
	for (;URL[i]=='/'; i++);

// ПУТЬ, ФАЙЛ -- До первого знака '?' или до конца
	for (j=0; URL[i]!=0 && URL[i]!='?'; i++,j++)
	{
		m_path[j  ] = URL[i];
		m_path[j+1] = 0;
	}

// Пропускаем '?'
	for (;URL[i]=='?'; i++);

// АРГУМЕНТЫ -- До конца
	for (j=0; URL[i]!=0; i++,j++)
	{
		m_args[j  ] = URL[i];
		m_args[j+1] = 0;
	}

// Выгрызаем имя файла из пути
	for (i=strlen(m_path); i>0; i--)
	{
		if (m_path[i] == '/')
		{
			m_path[i] = 0;
			strcpy (m_file, m_path+i+1);
			break;
		}
	}
	if (i<=0)
	{
		strcpy (m_file, m_path);
		m_path[0] = 0;
	}

// Выгрызаем расширение файла из имени
	for (i=strlen(m_file); i>=0; i--)
	{
		if (m_file[i] == '.')
		{
			m_file[i] = 0;
			strcpy (m_ext, m_file+i+1);
			break;
		}
	}

// Если у файла нет расширения -- это часть пути
	if (m_ext[0]==0)
	{
		if (m_path[0]!=0)
		{
			strcat (m_path, "/");
		}
		strcat (m_path, m_file);
		m_file[0]=0;
	}

// Убираем лишние / с конца пути
	while (m_path[0] && (m_path[strlen(m_path)-1]=='/'))
	{
		m_path[strlen(m_path)-1]=0;
	}

// Выгрызаем имя и пароль из доменна
	for (i=0; m_domain[i]; i++)
	{
		if (m_domain[i] == '@')
		{
			strcpy (m_login, m_domain);
			m_login[i] =0;
			strcpy (m_domain, m_domain+i+1);
			break;
		}
	}

// Выгрызаем порт из доменна
	for (i=0; m_domain[i]; i++)
	{
		if (m_domain[i] == ':')
		{
			m_domain[i] =0;
			strcpy (m_port, m_domain+i+1);
			break;
		}
	}

// Выгрызаем имя и пароль из имени-и-пароля
	for (i=0; m_login[i]; i++)
	{
		if (m_login[i] == ':')
		{
			m_login[i] =0;
			strcpy (m_password, m_login+i+1);
			break;
		}
	}

// Приводим домен в нормальный вид
	for (i=0; m_domain[i]; i++)
	{
		char C = m_domain[i];
		if (C>='A' && C<='Z')
			m_domain[i] = (char) (C+32);
	}
}
//____________________________________________________________________________[]






                                                           
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/