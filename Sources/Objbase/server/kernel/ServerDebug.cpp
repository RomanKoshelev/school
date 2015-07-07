/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ServerDebug.cpp															[]
[] Date:            01/22/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Writing debug info to HTML page									[]
[]-Last Modified:   08.10.99 [ 5:52:28 ] by Roman V. Koshelev                 []                                     
[]____________________________________________________________________________[]
*/
#include "main.h"


bool CServerDebug::m_bCreated = false;
char CServerDebug::m_Entrance	[10240] = "";
char CServerDebug::m_Template	[10240] =
"<table width=80%% border=0 cellspacing=2 align=center>"
	"<tr><td>"
		"<tr><td><b>Файл:&nbsp;%s&nbsp;&nbsp;строка:&nbsp;%d&nbsp;</td>"
		"<td align=right><b><font color=#999966>%s&nbsp</td></tr>"
	"</b></TD></TR>"
"</table>"
"<table width=80%% border=1 cellspacing=1 align=center valign = TOP bgcolor=#d3cd96 bordercolor=#cdc585 bordercolorlight=white bordercolordark=#9a9572>"
	"<tr bgcolor=#eae6b5><td><TABLE><TR><TD>&nbsp;</TD><TD>"
		"<b>%s:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</b>%s"
	"</TD></TR></TABLE></td></tr>"
	"<tr bgcolor=#f3f1d6><td><TABLE><TR><TD>&nbsp;</TD><TD>"
		"%s%s%s%s%s%s"
	"</TD></TR></TABLE></td></tr>"
"</table>"
"<br>\n";


DEBUG_STACK_RECORD	DEBUG_STACK_RECORD_ARR	[DEBUG_STACK_MAX_SIZE];
int						DEBUG_STACK_RECORD_NUM	=-1;

static char * HTML_HEADER = 
"<html><head><META HTTP-EQUIV='expires' CONTENT='0'><meta http-equiv='Pragma' content='no-cache'>"
"<title> Лог базы данных</title></head><body topmargin=20 bgcolor='#ddddee'>"
"<font face='Arial' style='text-decoration: none;'><center><h1><FONT color=#000000 face=''>"
"<font face='Arial' style='text-decoration: none;'>Лог базы данных</FONT></h1></center></font>\n";

char * STR_OSHIBKA = "Ошибка:";
char * STR_NE_VYPOLNJAETTSJA_USLOVIE = "Не выполняется условие:%s";

char SD_ERROR[SD_ERROR_SIZE];


/*______________________________________________________________________________
[]                                                                            []
[]` SERVER_DEBUG_ERROR_VA                                                     []
[]                                                                            */
void SERVER_DEBUG_ERROR_VA(const char *strTemplate, ...)
{
	va_list		ArgList;
	va_start		(ArgList, strTemplate);
	vsnprintf	(SD_ERROR, SD_ERROR_SIZE-1, strTemplate, ArgList);
	va_end		(ArgList);
	theServerDebug.Error(0, 0, SD_ERROR);
	if (SD_ASSERT (0, 0, STR_OSHIBKA, SD_ERROR))
		DBG_STOP_ASK;
	return;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` SERVER_DEBUG_TEXT_VA                                                      []
[]                                                                            */
void SERVER_DEBUG_TEXT_VA(const char *str, ...)
{
	va_list		ArgList;
	va_start		(ArgList, str);
	vsnprintf	(SD_ERROR, SD_ERROR_SIZE-1, str, ArgList);
	va_end		(ArgList);
	theServerDebug.Text(0, 0, str);
	return;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` CServerDebug 																					[]
//                                                                            []
CServerDebug::CServerDebug (const char * sPrefix)
{
	umask (0);
	char sFileName[1024];
	snprintf (sFileName, 1024, DB_LOG_HTML, sPrefix);
	m_bCreated	= true;
	m_LogFile	= fopen(sFileName,"wb");
	
	if (m_LogFile) fwrite (HTML_HEADER, strlen (HTML_HEADER), 1, m_LogFile);
	else printf ("\nCServerDebug: Can't open log-file %s\n", sFileName);
}
//----------------------------------------------------------------------------[] 
CServerDebug::~CServerDebug ()
{
	char * sEND = "<font size=5><center><h1> * * * FINITA LA COMEDIA * * * </FONT></h1></center></font></body></html>\n";
	if (m_LogFile) fwrite	(sEND, strlen (sEND), 1, m_LogFile);
	if (m_LogFile)	fflush	(m_LogFile);

	m_bCreated = false;
	if (m_LogFile) fclose (m_LogFile);
	m_LogFile = NULL;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Write																							[]
//                                                                            []
void CServerDebug::Write(const char * file, int line, const char * s4,const char * s5,const char * s6,const char * s7,const char * s8,const char * s9,const char * s10)
{
	if (!m_bCreated) return;
	static char SSS [10240]; SSS[0]=0;

	long ltime;
	time (&ltime);
//	ltime += 3*60*60;
	struct tm * gmTime = localtime (&ltime);
	static char * MONTH[] = {"января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};

	static char TIME [1024];
	snprintf (TIME, 1024, "%02d:%02d:%02d&nbsp;&nbsp;%d-е %s",
				gmTime->tm_hour,			  // %d
				gmTime->tm_min,			  // %d
				gmTime->tm_sec,			  // %d
				gmTime->tm_mday,			  // %d
				MONTH[gmTime->tm_mon]);	  // %s

	snprintf	(SSS, 10240, m_Template, file, line, TIME, s4, m_Entrance, s5, s6, s7, s8, s9, s10);

	if (m_LogFile) fwrite	(SSS, strlen (SSS), 1, m_LogFile);
	if (m_LogFile)	fflush	(m_LogFile);
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Routines																						[]
//                                                                            []
const char * CServerDebug::GetStack()
{
	const  int  nStack = 4096;
	static char sStack [nStack];
	strcpy (sStack, "<hr align=left width=500 size=0 hoshade color=#666666><table width=100%>");

	char SSS [256];

	for (int i=DEBUG_STACK_RECORD_NUM; i>=0; i--)
	{
		snprintf (SSS, 256, "<tr><td><font size=-1 face='Courier'>%s</td><td><font size=-1>%s (%d)</td></tr>", DEBUG_STACK_RECORD_ARR[i].m_Name, DEBUG_STACK_RECORD_ARR[i].m_FileName, DEBUG_STACK_RECORD_ARR[i].m_Line);
		if (strlen (sStack)+1024 < nStack)
		{
			strcat (sStack, SSS);
		}
	}
	strcat (sStack, "</table>");

	return sStack;
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Assert(const char * sFILE, int line, const char * sCONDITION, const char * sCOMMENT)
{
	static char SSS [10240];
	snprintf (SSS, 10240, "%s<br><i>", sCONDITION);
	
	Write (sFILE, line, "<font color=red> Неккорректные данные</font>", SSS, sCOMMENT, "</i>", GetStack());
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Error(const char * sFILE, int line, const char * sCOMMENT)
{
	static char SSS [10240];
	snprintf (SSS, 10240, "%s<br><i>", sCOMMENT);
	Write (sFILE, line, "<font color=red>Ошибка</font>", SSS, "", "</i>", GetStack());
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Value(const char * sFILE, int line, const char * sVALUE_NAME, const void * pValue)
{
	static char SSS [10240];
	snprintf (SSS, 10240, " <b>=</b> 0x%08X", pValue);
	Write (sFILE, line, "Значение указателя", sVALUE_NAME, SSS);
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Value(const char * sFILE, int line, const char * sVALUE_NAME, int nValue)
{
	static char SSS [10240];
	snprintf (SSS, 10240, " <b>=</b> %d (0x%08X)", nValue, nValue);
	Write (sFILE, line, "Значение числа", sVALUE_NAME, SSS);
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Value(const char * sFILE, int line, const char * sVALUE_NAME, const char * sValue)
{
	static char SSS [10240];
	snprintf (SSS, 10240, " <b>=</b> \"%s", sValue);
	Write (sFILE, line, "Значение строки", sVALUE_NAME, SSS, "\"");
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Text(const char * sFILE, int line, const char * sText)
{
	static char SSS [10240];
	snprintf (SSS, 10240, "%s", sText);
	Write (sFILE, line, "Сообщение", "", SSS, "");
}
//----------------------------------------------------------------------------[] 
void CServerDebug::Place(const char * sFILE, int line)
{
	static char SSS [10240];
	snprintf (SSS, 10240, "%d", line);
	Write (sFILE, line, "Код исполнен", sFILE, "<br>", SSS);
}
//____________________________________________________________________________[]



#ifdef WIN32
	#include <windows.h>
	bool SD_ASSERT(const char * sFILE, int line, const char * sCONDITION, const char * sCOMMENT)
	{
		struct IGNORE_ITEM	{char file [256]; int line;};
		static IGNORE_ITEM	IGNORE_ARR	[10240];
		static int				IGNORE_NUM	=0;

		for (int i=0; i<IGNORE_NUM; i++) if (IGNORE_ARR[i].line==line && (strcmp(IGNORE_ARR[i].file, sFILE)==0))
		{
			return false;
		}

		static char Err [10240];
		snprintf (Err, 10240, "Файл:\t%s\nСтрока:\t%d\n\n%s\n\n%s\t\t\t\t", sFILE, line, sCONDITION, sCOMMENT);

		switch (::MessageBox (NULL, Err, " Критическая остановка", MB_ABORTRETRYIGNORE|MB_DEFBUTTON2|MB_ICONERROR))
		{
			case IDRETRY:
				#ifndef _DEBUG
					::MessageBox (NULL, " Отладка невозможна -- запустите Debug-версию", "Отладка", MB_OK|MB_ICONHAND);
				#endif
				return true;
			break;

			case IDABORT:
				exit (1);
			break;

			case IDIGNORE:
				strcpy (IGNORE_ARR[IGNORE_NUM].file, sFILE);
				IGNORE_ARR[IGNORE_NUM].line = line;
				IGNORE_NUM ++;
				return false;
			break;
		}
		return false;
	}
#else
	bool SD_ASSERT(const char *, int, const char *, const char *)
	{
		return true;
	}
#endif
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` PRINT_PERCENT																					[]
//                                                                            []
static int old_percent=-1;
int PRINT_PERCENT(int i, int N)
{
	N=max(1,N);
	static int old_i = -1;
	static int last_i= -1;
	int percent = (i+1)*100/N;
	static clock_t ini_clock = 0;
	static clock_t old_clock = 0;
	static double old_per_second=-1;
	static double ini_per_second=-1;

	if ((i<old_i) || (old_i==-1))
	{
		old_percent		= -1;
		last_i			=  0;
		old_clock		=  clock ();
		old_per_second =  0;
		ini_clock		=  old_clock;
		ini_per_second =  0;
	}

	if ((percent!=old_percent) || (N==1))
	{
		static int nDif	= 0;
		time_t cur_clock	= clock ();
		nDif = old_percent!=-1? i-last_i: 0;
		char sTimes [256]="";
		double duration			= (double)(cur_clock - old_clock) / CLOCKS_PER_SEC;
		double total_duration	= (double)(cur_clock - ini_clock) / CLOCKS_PER_SEC;
		if (duration)
		{
			double per_second = nDif/duration;
			if (ini_per_second==0) ini_per_second = per_second;
			if (old_per_second>0)
			{
				per_second = (per_second+old_per_second)/2;
			}
			snprintf (sTimes, 256, "%4.f sec [ini:%.f/s ave:%.f/s cur:%.f/s]", total_duration, ini_per_second, ((float)i)/total_duration, per_second);
		}

#ifdef WIN32
		printf ("\r %3d%%  [%d] %s     ", percent, N, sTimes);
#else
		printf ("\n %3d%%  [%d] %s     ", percent, N, sTimes);
#endif
		old_percent = percent;

		old_clock = cur_clock;

		old_i  = i;
		last_i = i;
		return percent;
	}
	old_i = i;

#ifdef WIN32
	if (_kbhit () && (_getch()==27))
	{
		return -2;
	}
#endif

	return -1;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` RANDOM_PERCENT																				[]
//                                                                            []
// Эта функция возвращает true в примерно в nThreshold/nBASE случаях из nBASE.
bool RANDOM_PERCENT (int nThreshold, int nBASE)
{
	int nRandomPercent = rand () % nBASE;
	return nThreshold > nRandomPercent;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
