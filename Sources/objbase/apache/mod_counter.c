/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'apache'                                     []
[] Copyright (C) 2000 by the author(s) -- see below.                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            mod_counter.c                                             []
[] Date:            10.03.2000                                                []
[] Author:          Roman V. Koshelev. Oleg V. Kobrin									[]
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#include "httpd.h"
#include "http_config.h"

	const		char *			Host					= "127.0.0.1";
	const		int				Port					= 1502;
	const		int				Domain				= AF_INET;
									
#include "mod_counter_call.c"

#define	MAX_COOKIES_NUM	150
#define	MAX_ARGUMENTS_NUM	150

module MODULE_VAR_EXPORT counter_module;

#define PRINT_ARGUMENT(arg)	if(!arg)arg="[-]"; ap_rprintf (r, #arg " = %s<br>", arg);


//______________________________________________________________________________
//                                                                            []
//` ChopStr                                                                   []       
//                                                                            []
int ChopStr (const char *Src, table *Target, char delim1, char delim2)
{
	char * Pos = (char *) Src;
	char * pStr1, * pStr2;
	int i=0;

	while(Pos) {
		pStr1 = strchr(Pos,delim1);						// Find delimiters in string
		pStr2 = strchr(Pos,delim2);

		if(pStr2) pStr2[0]=0;								// If second delimiter found, terminate pair;

		ap_unescape_url(Pos);								

		if(pStr1) {												// If first delimiter found
			pStr1[0]=0; pStr1++;								// Terminate first word, pStr advanced to second;
			ap_table_setn(Target, Pos, pStr1);			// Store both words
		} else {
			ap_table_setn(Target, Pos, "");				// Store empty second word
		}

		if(pStr2) {												// If more text to chop
			pStr2++;												// Advance to next pair
			while(pStr2[0]==' ') pStr2++;					// Skip spaces
		}

		Pos = pStr2;											// Set Pos to next pair
		i++;														// И тебя посчитали
	}
	return i;													// Пошел на хуй мудак!
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` counter_handler                                                           []           
//                                                                            []
int counter_handler (request_rec *r)
{
//----------------------------------------------------------------------------[] 
	table			* table_Cookies;
	table			* table_Arguments;
	const char	* str_Cookie;

// Из request_rec
	const char			* a_UserAgent			= NULL;
	const char			* a_SiteURL				= NULL;
	const char			* a_X_Forwarded_For	= NULL;
	const char			* a_Language			= NULL;
	const char			* a_ViewerIP			= NULL;
	const char			* a_ViewerHostName	= NULL;
	const char			* a_Charset				= NULL;

// Cookie
	const char			* a_TestCookie			= NULL;
	const char			* a_TSMC_Viewer_ID	= NULL;

// Аргументы
	const char			* a_SiteAlias			= NULL;
	const char			* a_SiteID				= NULL;
	const char			* a_PageNo				= NULL;
	const char			* a_CounterType		= NULL;
	const char			* a_ScreenResolution	= NULL;
	const char			* a_ColorDepth			= NULL;
	const char			* a_LocalTimeStr		= NULL;
	const char			* a_JavaScriptVersion= NULL;
	const char			* a_JavaEnabled		= NULL;
	const char			* a_Referrer			= NULL;
	const char			* a_bShow				= NULL;
	const char			* a_bCount				= NULL;

	
	char * in_JustGetData						= NULL;	// Получить значение полей счетчика сайтов без их модификации. На вход нужен только ID сайта.
	char * in_SiteID								= NULL;	// {class:Site}ID сайта.
	char * in_Alias								= NULL;	// Синоним ID сайта.
	char * in_CounterType						= NULL;	// Тип счётчика (по умолчанию - тот, что установлен у сайта).
	char * in_PageNo								= NULL;	// Номер страницы сайта.
	char * in_CookieSupported					= NULL;	// Поддерживается ли Cookie.
	char * in_ViewerID							= NULL;	// {class:Viewer}Cookie (ID) зрителя, если Cookie поддерживается и установлен, или NA в противном случае.
	char * in_LocalTime							= NULL;	// Местное время посетителя.
	char * in_ViewerIP							= NULL;	// IP зрителя.
	char * in_SiteURL								= NULL;	// URL сайта, на котором произошло событие (HTTP_REFERER).
	char * in_Referrer							= NULL;	// Предыдущий URL (doсument.referrer на Javascript'е.
	char * in_ViewerHostName					= NULL;	// Хост посетителя.
	char * in_UserAgent							= NULL;	// UserAgent посетителя.
	char * in_ScreenResolution					= NULL;	// Разрешение экрана.
	char * in_ColorDepth							= NULL;	// Глубина цвета.
	char * in_JavaEnabled						= NULL;	// Включена ли Ява-машина.
	char * in_JavaScriptVersion				= NULL;	// Версия ЯваСкрипта.
	char * in_Charset								= NULL;	// CHARSET
	char * in_Language							= NULL;	// HTTP_ACCEPT_LANGUAGE


	int				out_Total_Hits				= 0;
	int				out_Total_Hosts			= 0;
	int				out_Total_Visitors		= 0;
	unsigned long	out_ViewerID				= 0;
	int				out_ExitCode				= 0;

	int				nCallResult					= 0;
	int				bCount						= 0;
	int				bShow							= 0;
//----------------------------------------------------------------------------[] 



	r->content_type = "text/html";
//	ap_table_setn(r->headers_out, "Set-Cookie", "FUCK=FUCK; path=/");
	ap_send_http_header(r);
	ap_rprintf (r, "<HTML><HEAD><TITLE>Counter</TITLE></HEAD><BODY BGCOLOR=#FFFFFF><H1>Всё заебись!</H1><PRE>");

	

	//----------------------------------------------------------------------------[] 
	// Извлекаем переменные окружения
	ap_add_common_vars	(r);
	ap_add_cgi_vars		(r);

	a_UserAgent			= ap_table_get (r->headers_in,		"User-Agent");
	a_SiteURL			= ap_table_get (r->headers_in,		"Referer");
	a_X_Forwarded_For	= ap_table_get (r->headers_in,		"X-Forwarded-For");
	a_Charset			= ap_table_get (r->headers_in,		"Accept-Charset");
	a_Language			= ap_table_get (r->headers_in,		"Accept-Language");
	a_ViewerIP			= ap_table_get (r->subprocess_env,	"REMOTE_ADDR");
	a_ViewerHostName	= ap_table_get (r->subprocess_env,	"REMOTE_HOST");
	//----------------------------------------------------------------------------[] 


	
	//----------------------------------------------------------------------------[] 
	// Извлекаем cookie
	//
	table_Cookies		= ap_make_table (r->pool, MAX_COOKIES_NUM);

	str_Cookie = ap_table_get (r->headers_in, "Cookie");
	ChopStr (str_Cookie,  table_Cookies,   '=', ';');

	a_TestCookie		= ap_table_get (table_Cookies, "TestCookie");
	a_TSMC_Viewer_ID	= ap_table_get (table_Cookies, "TSMC_Viewer_ID");

	ap_clear_table (table_Cookies);
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// Извлекаем аргументы командной строки
	//
	table_Arguments	= ap_make_table (r->pool, MAX_ARGUMENTS_NUM);
	ChopStr (r->args, table_Arguments, '=', '&');

	a_SiteAlias				=	ap_table_get (table_Arguments, "SiteAlias");
	a_SiteID					=	ap_table_get (table_Arguments, "SiteID");
	a_PageNo					=	ap_table_get (table_Arguments, "PageNo");
	a_CounterType			=	ap_table_get (table_Arguments, "CounterType");
	a_ScreenResolution	=	ap_table_get (table_Arguments, "ScreenResolution");
	a_ColorDepth			=	ap_table_get (table_Arguments, "ColorDepth");
	a_LocalTimeStr			=	ap_table_get (table_Arguments, "LocalTimeStr");
	a_JavaScriptVersion	=	ap_table_get (table_Arguments, "JavaScriptVersion");
	a_JavaEnabled			=	ap_table_get (table_Arguments, "JavaEnabled");
	a_Referrer				=	ap_table_get (table_Arguments, "Referrer");
	a_bShow					=	ap_table_get (table_Arguments, "bShow");
	a_bCount					=	ap_table_get (table_Arguments, "bCount");

	ap_clear_table (table_Arguments);
	//----------------------------------------------------------------------------[] 



	//----------------------------------------------------------------------------[] 
	// Печатаем подготовленные входные аргументы
	//
	ap_rprintf (r, "<hr>Переменные:<br>");
	PRINT_ARGUMENT (a_UserAgent		);
	PRINT_ARGUMENT (a_SiteURL			);
	PRINT_ARGUMENT (a_X_Forwarded_For);
	PRINT_ARGUMENT (a_Language			);
	PRINT_ARGUMENT (a_ViewerIP			);
	PRINT_ARGUMENT (a_ViewerHostName	);
	PRINT_ARGUMENT (a_Charset			);

	ap_rprintf (r, "<hr>Куки:<br>");
	PRINT_ARGUMENT (a_TestCookie		);
	PRINT_ARGUMENT (a_TSMC_Viewer_ID	);

	ap_rprintf (r, "<hr>Аргументы:<br>");
	PRINT_ARGUMENT (a_SiteID				);
	PRINT_ARGUMENT (a_SiteAlias			);
	PRINT_ARGUMENT (a_PageNo				);
	PRINT_ARGUMENT (a_CounterType			);
	PRINT_ARGUMENT (a_ScreenResolution	);
	PRINT_ARGUMENT (a_ColorDepth			);
	PRINT_ARGUMENT (a_LocalTimeStr		);
	PRINT_ARGUMENT (a_JavaScriptVersion	);
	PRINT_ARGUMENT (a_JavaEnabled			);
	PRINT_ARGUMENT (a_Referrer				);
	PRINT_ARGUMENT (a_bShow					);
	PRINT_ARGUMENT (a_bCount				);
	//----------------------------------------------------------------------------[] 







//----------------------------------------------------------------------------[] 
// Вызов фукнкции из базы
	OBJBASE_CALL_START;
	SET_FUNCTION ("BX_Counter_GetData");

			bCount					= (a_bCount!=NULL) && (a_bCount[0]!=0) && (a_bCount[0]=='1');
			bShow						= (a_bShow !=NULL) && (a_bShow [0]!=0) && (a_bShow [0]=='1');
			in_SiteID				= a_SiteAlias? NULL: (char *)a_SiteID;
			in_Alias					= (char *) a_SiteAlias;
			in_JustGetData			= bCount? "1":"0";

			in_PageNo				= (char *) a_PageNo;

			in_CounterType			= (char *) a_CounterType;
			in_CookieSupported	= "0"; // !!!!
			in_ViewerID				= (char *) a_TSMC_Viewer_ID;
			in_LocalTime			= (char *) a_LocalTimeStr;
			in_ViewerIP				= (char *) a_ViewerIP;
			in_SiteURL				= (char *) a_SiteURL;
			in_Referrer				= (char *) a_Referrer;
			in_ViewerHostName		= (char *) a_ViewerHostName;
			in_UserAgent			= (char *) a_UserAgent;
			in_ScreenResolution	= (char *) a_ScreenResolution;
			in_ColorDepth			= (char *) a_ColorDepth;
			in_JavaEnabled			= (char *) a_JavaEnabled;
			in_JavaScriptVersion	= (char *) a_JavaScriptVersion;
			//in_Charset				= (char *) a_Charset;  // !!! AV -- разбить на массив в базе.
			//in_Language				= (char *) a_Language; // !!! AV -- разбить на массив в базе.


			if (in_Alias)
			{
				SET_ARG_IN (String,			"Alias"							, in_Alias						);
			}
			else
				SET_ARG_IN (String,			"SiteID"							, in_SiteID						);
			if (bCount)
			{
				SET_ARG_IN (String,			"JustGetData"					, in_JustGetData				);
				SET_ARG_IN (String,			"CounterType"					, in_CounterType				);
				SET_ARG_IN (String,			"PageNo"							, in_PageNo						);
				SET_ARG_IN (String,			"CookieSupported"				, in_CookieSupported			);
				SET_ARG_IN (String,			"ViewerID"						, in_ViewerID					);
				SET_ARG_IN (String,			"LocalTime"						, in_LocalTime					);
				SET_ARG_IN (String,			"ViewerIP"						, in_ViewerIP					);
				SET_ARG_IN (String,			"SiteURL"						, in_SiteURL					);
				SET_ARG_IN (String,			"Referrer"						, in_Referrer					);
				SET_ARG_IN (String,			"ViewerHostName"				, in_ViewerHostName			);
				SET_ARG_IN (String,			"UserAgent"						, in_UserAgent					);
				SET_ARG_IN (String,			"ScreenResolution"			, in_ScreenResolution		);
				SET_ARG_IN (String,			"ColorDepth"					, in_ColorDepth				);
				SET_ARG_IN (String,			"JavaEnabled"					, in_JavaEnabled				);
				SET_ARG_IN (String,			"JavaScriptVersion"			, in_JavaScriptVersion		);
				SET_ARG_IN (String,			"Charset"						, in_Charset					);
				SET_ARG_IN (String,			"Language"						, in_Language					);
			}
			else
			{
				SET_ARG_IN (String,			"JustGetData"					, "1");
			}

			SET_ARG_OUT ("ExitCode"			);
			SET_ARG_OUT ("ViewerID"			);

			if (bShow)
			{
				SET_ARG_OUT	("Total_Hits"		);
				SET_ARG_OUT ("Total_Hosts"		);
				SET_ARG_OUT ("Total_Visitors"	);
			}
			

		nCallResult = CALL_FUNCTION ();	 
		

	//	BX_ResultCode  - код возрата из базы

		if (nCallResult==0) 
		{
			GET_RETVALUE	 (Int,					"ExitCode",						out_ExitCode				);

			if (bShow)
			{
				GET_RETVALUE (Int,					"Total_Hits",					out_Total_Hits				);
				GET_RETVALUE (Int,					"Total_Hosts",					out_Total_Hosts			);
				GET_RETVALUE (Int,					"Total_Visitors",				out_Total_Visitors		);
			}
			else
			{
				GET_RETVALUE (Identifier,			"ViewerID",						out_ViewerID				);
			}
		}
		else
		{
			// диагностика кода возврата
		}
	OBJBASE_CALL_END;
//----------------------------------------------------------------------------[] 



	ap_rprintf (r, "<p><hr>Результат запроса:<br>");
	ap_rprintf (r, "Total_Hits     = %d<br>",		out_Total_Hits);
	ap_rprintf (r, "Total_Hosts    = %d<br>",		out_Total_Hosts);
	ap_rprintf (r, "Total_Visitors = %d<br>",		out_Total_Visitors);
	ap_rprintf (r, "ViewerID	    = %lu<br>",	out_ViewerID);
	ap_rprintf (r, "ExitCode       = %d<br>",		out_ExitCode);


	ap_rprintf (r, "</PRE><hr><a href=\"http://195.54.192.123:1600/counter?1=2&btt=333\">http://195.54.192.123:1600/counter?1=2&btt=333</a><br>");
	ap_rprintf (r, "</BODY></HTML>");

	return OK;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` counter_handlers                                                          []             
//                                                                            []
handler_rec counter_handlers[] = 
{
	{ "4me-counter", counter_handler },
	{ NULL }
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` counter_child_init                                                        []              
//                                                                            []
static void counter_child_init()
{
	// do nothing yet
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` module counter_module                                                     []                 
//                                                                            []
module counter_module = 
{
	STANDARD_MODULE_STUFF,
		NULL,									/* initializer */
		NULL,									/* dir config creater */
		NULL,									/* dir merger --- default is to override */
		NULL,									/* server config */
		NULL,									/* merge server config */
		NULL,									/* command table */
		counter_handlers,					/* handlers */
		NULL,									/* filename translation */
		NULL,									/* check_user_id */
		NULL,									/* check auth */
		NULL,									/* check access */
		NULL,									/* type_checker */
		NULL,									/* fixups */
		NULL,									/* logger */
		NULL,									/* header parser */
		counter_child_init,				/* child_init */
		NULL,									/* child_exit */
		NULL									/* post read-request */
};
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
