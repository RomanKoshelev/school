/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            UserAgent.cpp                                             []
[] Date:            31.03.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Разборщик USER_AGENT                                      []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#define	USES_string_h
#include "main.h"
#include "UserAgent.h"


/*______________________________________________________________________________
[]                                                                            []
[]` Init                                                                      []    
[]                                                                            */
void USER_AGENT::Init ()
{
	m_Browser					[0] = 0;
	m_Browser_ver				[0] = 0;
	m_OperatingSystem			[0] = 0;
	m_OperatingSystem_ver	[0] = 0;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` USER_AGENT                                                                []          
[]                                                                            */
USER_AGENT::USER_AGENT ()
{
	Init ();
}
//----------------------------------------------------------------------------[]
USER_AGENT::USER_AGENT (const char * sUSER_AGENT)
{
	Parse (sUSER_AGENT);
}
//----------------------------------------------------------------------------[]
USER_AGENT::USER_AGENT (const string& sUSER_AGENT)
{
	Parse (sUSER_AGENT.c_str());
}
//----------------------------------------------------------------------------[]
USER_AGENT::USER_AGENT (const USER_AGENT& from)
{
	CopyFrom (from);
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` CopyFrom                                                                  []        
[]                                                                            */
void USER_AGENT::CopyFrom (const USER_AGENT& from)
{
	strcpy (m_Browser					,	from.m_Browser					);
	strcpy (m_Browser_ver			,	from.m_Browser_ver			);
	strcpy (m_OperatingSystem		,	from.m_OperatingSystem		);
	strcpy (m_OperatingSystem_ver	,	from.m_OperatingSystem_ver	);
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` operator =                                                                []          
[]                                                                            */
USER_AGENT& USER_AGENT::operator = (const USER_AGENT& from)
{
	CopyFrom (from);
	return * this;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` DebugPrint                                                                []          
[]                                                                            */
void USER_AGENT::DebugPrint ()
{
	printf ("\n\n");
	printf ("Browser           =  [%s] [%s]",	m_Browser, m_Browser_ver);
	printf ("Operating System  =  [%s] [%s]",	m_OperatingSystem, m_OperatingSystem_ver);
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` UserAgent                                                                 []         
[]                                                                            */
void USER_AGENT::UserAgent (string& str)
{
	str = "";
	
	str += m_Browser;
	if (m_Browser_ver[0])
	{
		str += "/";
		str += m_Browser_ver;
	}

	str += "  (";
	str += m_OperatingSystem;
	if (m_OperatingSystem_ver[0])
	{
		str += " ";
		str += m_OperatingSystem_ver;
	}
	str += ")";
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` OperatingSystem                                                           []               
[]                                                                            */
void USER_AGENT::OperatingSystem (string& str)
{
	str = m_OperatingSystem;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` OperatingSystemVer                                                        []                  
[]                                                                            */
void USER_AGENT::OperatingSystemVer (string& str)
{
	str = m_OperatingSystem;
	if (m_OperatingSystem_ver[0])
	{
		str += " ";
		str += m_OperatingSystem_ver;
	}
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` Browser                                                                   []       
[]                                                                            */
void USER_AGENT::Browser (string& str)
{
	str = m_Browser;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` BrowserVer                                                                []          
[]                                                                            */
void USER_AGENT::BrowserVer (string& str)
{
	str = m_Browser;
	if (m_Browser_ver[0])
	{
		str += "/";
		str += m_Browser_ver;
	}
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` Parse                                                                     []     
[]                                                                            */
void USER_AGENT::Parse (const char * _sUSER_AGENT)
{
	int i,j,k;
	static char sUSER_AGENT[USER_AGENT_MAX_LEN+1];
	strcpy (sUSER_AGENT, _sUSER_AGENT);
	bool	 bFound	= false;
	Init	 ();
	char * pUSER_AGENT = sUSER_AGENT;
	int	 nUSER_AGENT = strlen (pUSER_AGENT);

	static char * arr_Mask[] ={"Checkbot",					"GetRight",			"Lotus-Notes",		"Lynx",				"MOMspider", 
										"MS Internet explorer", "Net Vampire", 	"NetAttache", 		"Nutscrape",		"Offline Explorer", 
										"Teleport Pro", 			"WebStripper", 	"Go!Zilla", 		"Jazz Explorer",	"VCI WebViewer",
										"Netscape",					"htdig",				"The Informant",	"MuscatFerret",	"QNX Voyager",    
										"WebTV",						"WebViewer",		"WebWasher",

										/*"CS 2000", */"AOL", /*"MSIECrawler",*/	/*"MSN",*/
										"MSIE", "Opera", "Mozilla"
										};
	int arr_Mask_Size = sizeof (arr_Mask)/sizeof (arr_Mask[0]);

// Mozilla -- перемещаем указатель;
	char * sSompatible = "(compatible;";
	if (strstr(pUSER_AGENT, "WebTV")==NULL) if (strstr(pUSER_AGENT, "Mozilla")==pUSER_AGENT)
	{
		char * ptr = strstr(pUSER_AGENT, sSompatible);
		if (ptr!=NULL)
		{
			pUSER_AGENT = ptr + strlen (sSompatible);
		}
		nUSER_AGENT = strlen (pUSER_AGENT);
	}

// Всякие разные
	for (i=0; !bFound && (i<arr_Mask_Size); i++)
	{
		char * sMask = arr_Mask[i];
		int	 nMask = strlen (sMask);
		char * ptr = strstr(pUSER_AGENT, sMask);
		if (ptr!=NULL && ptr<=(pUSER_AGENT+40))
		{
			strcpy (m_Browser, sMask);
			for (j=(ptr-pUSER_AGENT)+nMask+1; j<nUSER_AGENT; j++)
			{
				char C = pUSER_AGENT[j];
				if ((C>='0') && (C<='9'))
				{
					int nDot = 0;
					for (k=0; (j<nUSER_AGENT) && (pUSER_AGENT[j]!=' ') && (pUSER_AGENT[j]!='-'); j++, k++)
					{
						C = pUSER_AGENT[j];
						nDot += (C=='.');
						if (nDot>1) 
							break;
						if (C!='.' && ((C<'0') || (C>'9')))
							break;
						m_Browser_ver[k  ] = C;
						m_Browser_ver[k+1] = 0;
					}
					break;
				}
				else
					break;
			}
			bFound = true;
		}
	}
// Упростим версию броузера
	m_Browser_ver[3] = 0;

// Неизвестные науке броузеры
	if (!bFound)
	{
		sprintf (m_Browser, "Other", pUSER_AGENT);
	}

	if (strcmp(m_Browser, "Mozilla")==0)
	{
		strcpy (m_Browser, "Netscape");
	}
//----------------------------------------------------------------------------[] 

	
//----------------------------------------------------------------------------[] 
// Ищем название и верcию OS
	static char * OS_MASK_ARR[] = {"Win95", "Win98", "Win16", "Win32",
								 "Windows 95/NT4", "Windows-NT", "Windows NT", "WinNT",  "Windows 2000",
								 "Windows 3.0", "Windows 3.1", "Windows 3.10", "Windows 4.10", "Windows 4.0", "Windows 5.10", "Windows 5.0", 
								 "Windows 95", "Windows 98", "Windows",
								 "Linux", "SunOS", "IRIX64", "IRIX", "Macintosh", "HP-UX", "CP/M", "AIX",
								 "Unix", "OS/2", "FreeBSD", "WebTV", "OSF1", "BSD/OS", "OSF1", "QNX", "PPC", "Mac_", "Lynx", 
								 "BK0010", "OS/360", "SCO_", "X11"};

	int OS_MASK_NUM = sizeof(OS_MASK_ARR)/sizeof(OS_MASK_ARR[0]);
	

	bFound = false;
	pUSER_AGENT = sUSER_AGENT;
	nUSER_AGENT = strlen (pUSER_AGENT);
	for (i=0; !bFound && (i<OS_MASK_NUM); i++)
	{
		char * sMask = OS_MASK_ARR[i];
		int	 nMask = strlen (sMask);
		char * ptr = strstr(pUSER_AGENT, sMask);
		if (ptr!=NULL)
		{
			strcpy (m_OperatingSystem, sMask);
			for (j=(ptr-pUSER_AGENT)+nMask+1; j<nUSER_AGENT; j++)
			{
				char C = pUSER_AGENT[j];
				int nDot = 0;
				if ((C>='0') && (C<='9'))
				{
					for (k=0; (j<nUSER_AGENT) && (pUSER_AGENT[j]!=' ') && (pUSER_AGENT[j]!='-'); j++, k++)
					{
						C = pUSER_AGENT[j];
						nDot += (C=='.');
						if (nDot>1) 
							break;
						if (C!='.' && ((C<'0') || (C>'9')))
							break;
						m_OperatingSystem_ver[k  ] = C;
						m_OperatingSystem_ver[k+1] = 0;
					}
					break;
				}
				else
					break;
			}
			bFound = true;
		}
	}


// Неизвестные науке операционки
	if (!bFound)
	{
		sprintf (m_OperatingSystem, "Other", pUSER_AGENT);
	}

// Корректируем уродов
	if ((strcmp(m_OperatingSystem,	"Windows 95/NT"	) == 0) || 
		 (strcmp(m_OperatingSystem,	"Windows 95/NT4"	) == 0) || 
		 (strcmp(m_OperatingSystem,	"Windows 4.0"		) == 0) || 
		 (strcmp(m_OperatingSystem,	"Windows 4.10"		) == 0) || 
		 (strcmp(m_OperatingSystem,	"Win32"				) == 0))
	{
		static int rmd=0;
		bool b95 = rmd%2==0;
		rmd++;
		strcpy (m_OperatingSystem,     b95? "Windows 95": "Windows NT");
		strcpy (m_OperatingSystem_ver, b95? "":		  "4.0");
	}

	if (strcmp(m_OperatingSystem, "Windows-NT")==0)			strcpy (m_OperatingSystem, "Windows NT");
	if (strcmp(m_OperatingSystem, "WindowsNT")==0)			strcpy (m_OperatingSystem, "Windows NT");
	if (strcmp(m_OperatingSystem, "WinNT")==0)				strcpy (m_OperatingSystem, "Windows NT");
	if (strcmp(m_OperatingSystem, "Windows 2000")==0)	{	strcpy (m_OperatingSystem, "Windows NT"); strcpy (m_OperatingSystem_ver, "5.0");}
	if (strcmp(m_OperatingSystem, "Windows 5.10")==0)	{	strcpy (m_OperatingSystem, "Windows NT");	strcpy (m_OperatingSystem_ver, "5.0");}
	if (strcmp(m_OperatingSystem, "Windows 5.0")==0)	{	strcpy (m_OperatingSystem, "Windows NT");	strcpy (m_OperatingSystem_ver, "5.0");}
	if (strcmp(m_OperatingSystem, "Win95")==0)				strcpy (m_OperatingSystem, "Windows 95");
	if (strcmp(m_OperatingSystem, "Win98")==0)				strcpy (m_OperatingSystem, "Windows 98");
	if (strcmp(m_OperatingSystem, "Win16")==0)				strcpy (m_OperatingSystem, "Windows 3.1");
	if (strcmp(m_OperatingSystem, "Windows 3.0")==0)		strcpy (m_OperatingSystem, "Windows 3.1");
	if (strcmp(m_OperatingSystem, "Windows 3.10")==0)		strcpy (m_OperatingSystem, "Windows 3.1");
	if (strcmp(m_OperatingSystem, "PPC")==0)					strcpy (m_OperatingSystem, "Macintosh");
	if (strcmp(m_OperatingSystem, "Mac_")==0)					strcpy (m_OperatingSystem, "Macintosh");
	if (strcmp(m_OperatingSystem, "Lynx")==0)				{	strcpy (m_OperatingSystem, "Linux");		strcpy (m_OperatingSystem_ver, "");}
	if (strcmp(m_OperatingSystem, "SCO_")==0)					strcpy (m_OperatingSystem, "Unix");
	if (strcmp(m_OperatingSystem, "X11")==0)					strcpy (m_OperatingSystem, "Unix");

// Сливаем "просто Windows" с его версией
	if (strcmp(m_OperatingSystem, "Windows")==0)
	{
		if (m_OperatingSystem_ver[0])
		{
			strcat (m_OperatingSystem, " ");
			strcat (m_OperatingSystem, m_OperatingSystem_ver);
		}
	}

// У макинтоша, Юникса, QNX и WebTV отрезаем версию.
	if (strcmp(m_OperatingSystem, "Macintosh")==0)
	{
		strcpy (m_OperatingSystem_ver, "");
	}
	if (strcmp(m_OperatingSystem, "Unix")==0)
	{
		strcpy (m_OperatingSystem_ver, "");
	}
	if (strcmp(m_OperatingSystem, "WebTV")==0)
	{
		strcpy (m_OperatingSystem_ver, "");
	}
	if (strcmp(m_OperatingSystem, "QNX")==0)
	{
		strcpy (m_OperatingSystem_ver, "");
	}

// Упростим версию операционки
	m_OperatingSystem_ver[3] = 0;
}
//____________________________________________________________________________[]

                                                                  
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/