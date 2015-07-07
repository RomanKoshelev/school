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

const    char *	BASE_URL				= "http://195.54.192.123:1600/counter";
const    char *	CNTF_LOGFILE_NAME = "/ar/www/4me/BX/logs/cntd_log.txt";
									
#include "mod_counter_call.c"
#include "mod_counter_img_set.c"
#include "mod_counter_dp_img.h"

#define	MAX_COOKIES_NUM		150
#define	MAX_ARGUMENTS_NUM		150
#define	MAX_URL_LEN				1024

module MODULE_VAR_EXPORT counter_module;

#define PRINT_ARGUMENT(arg)	{ap_rprintf (r, #arg " = %s<br>", arg?arg:"NA");}


//----------------------------------------------------------------------------[] 
#define ADD_ULR_ARG(URL,ARG)												\
	if (a_##ARG && ((strlen(URL)+strlen(a_##ARG))<MAX_URL_LEN))	\
	{																				\
		strcat (URL, "&"#ARG"=");											\
		strcat (URL, a_##ARG);												\
	}
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//` SetCookie                                                                 []         
//                                                                            []
void SetCookie (request_rec *r, const char * Name, const char * Value)
{
	char		STR[1024];
	char	*	pSTR;
	sprintf (STR, "%s=%s; expires=Saturday, 29-Nov-19 21:00:00 GMT; path=/", Name, Value);
	pSTR = ap_pstrcat(r->pool, STR, NULL);
	ap_table_setn (r->headers_out, "Set-Cookie", pSTR);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` ChopStr                                                                   []       
//                                                                            []
int ChopStr (const char *Src, table *Target, char delim1, char delim2)
{
	char * Pos = (char *) Src;
	char * pStr1, * pStr2;
	int i=0;

	if (Pos && Pos[0]==delim2) 
	{
		Pos++;
	}

	while (Pos) 
	{
		pStr1 = strchr(Pos,delim1);						// Find delimiters in string
		pStr2 = strchr(Pos,delim2);

		if(pStr2) pStr2[0]=0;								// If second delimiter found, terminate pair;

		ap_unescape_url(Pos);								

		if(pStr1) 												// If first delimiter found
		{															
			pStr1[0]=0; pStr1++;								// Terminate first word, pStr advanced to second;
			ap_table_setn(Target, Pos, pStr1);			// Store both words
		} 
		else 
		{
			ap_table_setn(Target, Pos, "");				// Store empty second word
		}

		if(pStr2)												// If more text to chop
		{
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
//` CheckUndefined                                                            []              
//                                                                            []
char * CheckUndefined (const char * pStr)
{
	if (!pStr)							return "Undefined";
	if (pStr[0]==0)					return "Undefined";
	if (!strcmp (pStr, "NA"))		return "Undefined";
	if (strstr (pStr,"ndefined"))	return "Undefined";
	return (char *) pStr;
}
//____________________________________________________________________________[]


























//______________________________________________________________________________
//                                                                            []
//` counter_handler                                                           []           
//                                                                            []
int counter_handler (request_rec *r)
{
//----------------------------------------------------------------------------[] 
	char			  SSS [1024];
	char			  REDIRECT_URL[MAX_URL_LEN]="";
	table			* table_Cookies;
	table			* table_Arguments;
	const char	* str_Cookie;

// Из request_rec
	char			* a_UserAgent			= NULL;
	char			* a_SiteURL				= NULL;
	char			* a_X_Forwarded_For	= NULL;
	char			* a_Language			= NULL;
	char			* a_ViewerIP			= NULL;
	char			* a_ViewerHostName	= NULL;
	char			* a_Charset				= NULL;

// Cookie
	char			* a_TestCookie			= NULL;
	char			* a_TSMC_Viewer_ID	= NULL;

// Аргументы
	char			* a_SiteAlias			= NULL;
	char			* a_SiteID				= NULL;
	char			* a_PageNo				= NULL;
	char			* a_CounterType		= NULL;
	char			* a_ScreenResolution	= NULL;
	char			* a_ColorDepth			= NULL;
	char			* a_LocalTimeStr		= NULL;
	char			* a_JavaScriptVersion= NULL;
	char			* a_JavaEnabled		= NULL;
	char			* a_Referrer			= NULL;
	char			* a_bShow				= NULL;
	char			* a_bCount				= NULL;
	char			* a_SECOND_REQUEST	= NULL;
	char			* a_TC					= NULL;

	
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
	int				bSetCookie					= 0;
//----------------------------------------------------------------------------[] 


	



	//----------------------------------------------------------------------------[] 
	// Извлекаем переменные окружения
	ap_add_common_vars	(r);
	ap_add_cgi_vars		(r);

	a_UserAgent			= (char*) ap_table_get (r->headers_in,			"User-Agent");
	a_SiteURL			= (char*) ap_table_get (r->headers_in,			"Referer");
	a_X_Forwarded_For	= (char*) ap_table_get (r->headers_in,			"X-Forwarded-For");
	a_Charset			= (char*) ap_table_get (r->headers_in,			"Accept-Charset");
	a_Language			= (char*) ap_table_get (r->headers_in,			"Accept-Language");
	a_ViewerIP			= (char*) ap_table_get (r->subprocess_env,	"REMOTE_ADDR");
	a_ViewerHostName	= (char*) ap_table_get (r->subprocess_env,	"REMOTE_HOST");
	//----------------------------------------------------------------------------[] 


	
	//----------------------------------------------------------------------------[] 
	// Извлекаем cookie
	//
	table_Cookies		= ap_make_table (r->pool, MAX_COOKIES_NUM);

	str_Cookie = ap_table_get (r->headers_in, "Cookie");
	ChopStr (str_Cookie,  table_Cookies,   '=', ';');

	a_TestCookie		= (char*) ap_table_get (table_Cookies, "TestCookie");
	a_TSMC_Viewer_ID	= (char*) ap_table_get (table_Cookies, "TSMC_Viewer_ID");

	ap_clear_table (table_Cookies);
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// Извлекаем аргументы командной строки
	//
	table_Arguments	= ap_make_table (r->pool, MAX_ARGUMENTS_NUM);
	ChopStr (r->args, table_Arguments, '=', '&');

	a_SiteAlias				=	(char*) ap_table_get (table_Arguments, "SiteAlias");
	a_SiteID					=	(char*) ap_table_get (table_Arguments, "SiteID");
	a_PageNo					=	(char*) ap_table_get (table_Arguments, "PageNo");
	a_CounterType			=	(char*) ap_table_get (table_Arguments, "CounterType");
	a_ScreenResolution	=	(char*) ap_table_get (table_Arguments, "ScreenResolution");
	a_ColorDepth			=	(char*) ap_table_get (table_Arguments, "ColorDepth");
	a_LocalTimeStr			=	(char*) ap_table_get (table_Arguments, "LocalTimeStr");
	a_JavaScriptVersion	=	(char*) ap_table_get (table_Arguments, "JavaScriptVersion");
	a_JavaEnabled			=	(char*) ap_table_get (table_Arguments, "JavaEnabled");
	a_Referrer				=	(char*) ap_table_get (table_Arguments, "Referrer");
	a_bShow					=	(char*) ap_table_get (table_Arguments, "bShow");
	a_bCount					=	(char*) ap_table_get (table_Arguments, "bCount");
	a_SECOND_REQUEST		= 	(char*) ap_table_get (table_Arguments, "SECOND_REQUEST");
	a_TC						= 	(char*) ap_table_get (table_Arguments, "TC");

	ap_clear_table (table_Arguments);
	//----------------------------------------------------------------------------[] 





	//----------------------------------------------------------------------------[] 
	bCount					= (a_bCount!=NULL) && (a_bCount[0]!=0) && (a_bCount[0]=='1');
	bShow						= (a_bShow !=NULL) && (a_bShow [0]!=0) && (a_bShow [0]=='1');
	//----------------------------------------------------------------------------[] 





	//----------------------------------------------------------------------------[] 
	// Проверка поддержки cookie																	[]
	if (bCount)
	{
		if (a_TestCookie && a_TestCookie[0]=='1' && a_TestCookie[1]==0 && a_TC==NULL)
		{
			in_CookieSupported = "1";
		}
		else if (a_SECOND_REQUEST && a_SECOND_REQUEST[0]=='1')
		{
			in_CookieSupported = "0";
		}
		else
		{
			strcat (REDIRECT_URL,BASE_URL);
			strcat (REDIRECT_URL,"?");

			a_SECOND_REQUEST = "1";

			ADD_ULR_ARG (REDIRECT_URL, SiteAlias			);
			ADD_ULR_ARG (REDIRECT_URL, SiteID				);
			ADD_ULR_ARG (REDIRECT_URL, PageNo				);
			ADD_ULR_ARG (REDIRECT_URL, CounterType			);
			ADD_ULR_ARG (REDIRECT_URL, ScreenResolution	);
			ADD_ULR_ARG (REDIRECT_URL, ColorDepth			);
			ADD_ULR_ARG (REDIRECT_URL, LocalTimeStr		);
			ADD_ULR_ARG (REDIRECT_URL, JavaScriptVersion	);
			ADD_ULR_ARG (REDIRECT_URL, JavaEnabled			);
			ADD_ULR_ARG (REDIRECT_URL, Referrer				);
			ADD_ULR_ARG (REDIRECT_URL, bShow					);
			ADD_ULR_ARG (REDIRECT_URL, bCount				);
			ADD_ULR_ARG (REDIRECT_URL, SECOND_REQUEST		);
			ADD_ULR_ARG (REDIRECT_URL, TC						);


			r->filename			= ap_pstrcat(r->pool, REDIRECT_URL, NULL);
			r->content_type	= "text/html";
			SetCookie			(r, "TestCookie", a_TC? a_TC: "1");
			ap_table_setn		(r->headers_out, "Location", r->filename);
			r->status			= HTTP_MOVED_TEMPORARILY;
			ap_send_http_header	(r);
			return				DONE;
		}
	}
	//----------------------------------------------------------------------------[] 








	//----------------------------------------------------------------------------[] 
	// Вызов функции из базы
	OBJBASE_CALL_START();
	SET_FUNCTION ("BX_Counter_GetData");
			in_SiteID				= a_SiteAlias? NULL: (char *)a_SiteID;
			in_Alias					= (char *) a_SiteAlias;
			in_JustGetData			= bCount? "0":"1";

			in_PageNo				= (char *) (a_PageNo? a_PageNo : "0");

			in_CounterType			= (char *) a_CounterType;
			in_CookieSupported	= ((a_TestCookie && a_TestCookie[0]=='1') || (a_TSMC_Viewer_ID && a_TSMC_Viewer_ID[0]!=0)) ? "1": "0";
			in_ViewerID				= (char *) a_TSMC_Viewer_ID;
			in_LocalTime			= (char *) a_LocalTimeStr;
			in_ViewerIP				= CheckUndefined (a_X_Forwarded_For? a_X_Forwarded_For: a_ViewerIP);
			in_SiteURL				= (char *) a_SiteURL; //str_replace ("./", "/", a_SiteURL);
			in_Referrer				= CheckUndefined (a_Referrer);
			in_ViewerHostName		= CheckUndefined (a_ViewerHostName);
			in_UserAgent			= CheckUndefined (a_UserAgent);
			in_ScreenResolution	= (a_JavaScriptVersion==NULL || a_JavaScriptVersion[0]=='n') ? "Undefined" : CheckUndefined (a_ScreenResolution);
			in_ColorDepth			= (a_JavaScriptVersion==NULL || a_JavaScriptVersion[0]=='n') ? "Undefined" : CheckUndefined (a_ColorDepth);
			in_JavaEnabled			= (a_JavaScriptVersion==NULL || a_JavaScriptVersion[0]=='n') ? "Undefined" : CheckUndefined (a_JavaEnabled);
			in_JavaScriptVersion	= (a_JavaScriptVersion==NULL										  ) ? "no":         (char *) a_JavaScriptVersion;
			//in_Charset				= CheckUndefined (a_Charset);  // !!! AV -- разбить на массив в базе.
			//in_Language				= CheckUndefined (a_Language); // !!! AV -- разбить на массив в базе.


			if (in_Alias)
			{
				SET_ARG_IN ("Alias"							, in_Alias					);
			}
			else
				SET_ARG_IN ("SiteID"							, in_SiteID					);
			if (bCount)
			{
				SET_ARG_IN ("JustGetData"					, in_JustGetData			);
				SET_ARG_IN ("CounterType"					, in_CounterType			);
				SET_ARG_IN ("PageNo"							, in_PageNo					);
				SET_ARG_IN ("CookieSupported"				, in_CookieSupported		);
				SET_ARG_IN ("ViewerID"						, in_ViewerID				);
				SET_ARG_IN ("LocalTime"						, in_LocalTime				);
				SET_ARG_IN ("ViewerIP"						, in_ViewerIP				);
				SET_ARG_IN ("SiteURL"						, in_SiteURL				);
				SET_ARG_IN ("Referrer"						, in_Referrer				);
				SET_ARG_IN ("ViewerHostName"				, in_ViewerHostName		);
				SET_ARG_IN ("UserAgent"						, in_UserAgent				);
				SET_ARG_IN ("ScreenResolution"			, in_ScreenResolution	);
				SET_ARG_IN ("ColorDepth"					, in_ColorDepth			);
				SET_ARG_IN ("JavaEnabled"					, in_JavaEnabled			);
				SET_ARG_IN ("JavaScriptVersion"			, in_JavaScriptVersion	);
				SET_ARG_IN ("Charset"						, in_Charset				);
				SET_ARG_IN ("Language"						, in_Language				);
			}
			else
			{
				SET_ARG_IN ("JustGetData"					, "1");
			}

			SET_ARG_OUT ("ExitCode"			);
			SET_ARG_OUT ("ViewerID"			);

			if (bShow)
			{
				SET_ARG_OUT	("Total_Hits"		);
				SET_ARG_OUT ("Total_Hosts"		);
				SET_ARG_OUT ("Total_Visitors"	);
			}
			

		CALL_FUNCTION ();
		nCallResult = GET_FUNCTION_RESULT (NULL);
		

	//	BX_ResultCode  - код возрата из базы

		if (nCallResult==0) 
		{
			GET_RETVALUE	(Int,				"ExitCode",				out_ExitCode		);
			GET_RETVALUE	(Identifier,	"ViewerID",				out_ViewerID		);

			if (bShow)
			{
				GET_RETVALUE (Int,			"Total_Hits",			out_Total_Hits		);
				GET_RETVALUE (Int,			"Total_Hosts",			out_Total_Hosts	);
				GET_RETVALUE (Int,			"Total_Visitors",		out_Total_Visitors);
			}
		}
		else
		{
			// диагностика кода возврата
		}
	OBJBASE_CALL_END();
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	// Запись в лог
	if (CNTD_Errno!=CNTD_OKAY)
	{
		FILE	*		logFile;
		time_t		cut_time;
		cut_time	=	time (0);
		logFile	=	fopen (CNTF_LOGFILE_NAME, "a+b");
		fprintf (logFile, "CNTD_Errno = %4d %50s\n", CNTD_Errno, ctime(&cut_time));
		fclose  (logFile);
	}
	//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
// 																									[]
//` Вывод данных																					[]
// 																									[]
	r->content_type = "image/gif";;
	sprintf (SSS, "%d", out_ViewerID);
	bSetCookie = in_CookieSupported[0]=='1' && bCount && strcmp(a_TSMC_Viewer_ID?a_TSMC_Viewer_ID:"", SSS);
	if (CNTD_Errno==CNTD_OKAY && bSetCookie && out_ViewerID!=0 && strcmp (SSS, "2147483647"))
	{
		SetCookie (r, "TSMC_Viewer_ID", SSS);
	}
	ap_table_setn	(r->headers_out, "Expires",			"Mon, 26 Jul 1997 05:00:00 GMT");
	ap_table_setn	(r->headers_out, "Last-Modified",	"Mon, 26 Jul 1997 05:00:00 GMT");
	ap_table_setn	(r->headers_out, "Cache-Control",	"no-cache, must-revalidate");
	ap_table_setn	(r->headers_out, "Pragma",				"no-cache");

	ap_send_http_header	(r);
	ap_rflush				(r);


// Создание изображения
	{
		short int TRANSPARENT_GIF [] = {
			0x4947, 0x3846, 0x6139, 0x000a, 0x000a, 0x0080, 0xff00, 0xffff, 0xc4c4, 0x21c4, 
			0x04f9, 0x0001, 0x0000, 0x2c00, 0x0000, 0x0000, 0x000a, 0x000a, 0x0200, 0x8409, 
			0xa98f, 0xedcb, 0x630f, 0x0523, 0x3b00
		};

		ap_rwrite ((const void *) TRANSPARENT_GIF, 50, r);

/*
		char * gif_template = NULL;	int gif_template_len;
		char * rgb_template = NULL;	int rgb_template_len;
		char * gif_font	  = NULL;	int gif_font_len;
		char * rgb_font	  = NULL;	int rgb_font_len;
		char * gif_output	  = NULL;	int gif_output_len;
		char * p_gif_output = NULL;
		int    nRes=0;
		
		char *str_arr	[6]	=	{"123",  "456", "789", "654", "973", "873"};
		int	pos_x		[6]	=	{  44,     44,    44,    44,    44,    44};
		int	pos_y		[6]	=	{  45,     55,    65,    76,    86,    96};
		int	clr_R		[6]	=	{ 196,      0,     0,     0,     0,     0};
		int	clr_G		[6]	=	{   0,    196,     0,     0,     0,     0};
		int	clr_B		[6]	=	{   0,      0,   196,     0,     0,     0};

		DP_Load_GIF					("/ar/www/4me/BX/images/counter/test/template.gif", (void**)&gif_template, &gif_template_len);
		DP_Create_RGB_from_GIF	(gif_template, gif_template_len, (void**)&rgb_template, &rgb_template_len);
		DP_Destroy_GIF				(gif_template);

		DP_Load_GIF					("/ar/www/4me/BX/images/counter/test/font_0.gif", (void**)&gif_font, &gif_font_len);
		DP_Create_RGB_from_GIF	(gif_font, gif_font_len, (void**)&rgb_font, &rgb_font_len);
		DP_Destroy_GIF				(gif_font);


		DP_Create_GIF_from_template(	rgb_template, 			// <- Образ файла-шаблона                              
												rgb_template_len,		// <- Размер образа шаблона                            
												6, 						// <- Размер массива строк, которые надо вписать в гиф 
												str_arr,					// <- Массив строк. Строки заканчиваются нулём.        
												pos_x, 					// <- Х-координата соответствующей строки              
												pos_y, 					// <- Y-координата соответствующей строки              
												clr_R, clr_G, clr_B,	// <- Цвета соответствующей строки                     
												rgb_font, 				// <- Образ файла-шрифта (шрифт моноширинный)          
												rgb_font_len,			// <- Размер образа шрифта                             
												(void**)&gif_output, // -> Образ полученного гиф-изображения                
												&gif_output_len);		// -> Размер полученного гиф-изображения               

		p_gif_output  = ap_palloc (r->pool, gif_output_len);
		memcpy (p_gif_output, gif_output, gif_output_len);
		ap_rwrite ((const void *) p_gif_output, gif_output_len, r);

		DP_Destroy_RGB (rgb_template);
		DP_Destroy_RGB (rgb_font);
		DP_Destroy_GIF (gif_output);
*/
	}
	return OK;
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//
// Отладочная печать
//
	ap_rprintf (r, "<HTML><HEAD><TITLE>Counter</TITLE></HEAD><BODY BGCOLOR=#FFFFFF><H1>Всё заебись!</H1><PRE>");
/*
		ap_rprintf (r, "<hr><b>Переменные:</b><br>");
		PRINT_ARGUMENT (a_UserAgent		);
		PRINT_ARGUMENT (a_SiteURL			);
		PRINT_ARGUMENT (a_X_Forwarded_For);
		PRINT_ARGUMENT (a_Language			);
		PRINT_ARGUMENT (a_ViewerIP			);
		PRINT_ARGUMENT (a_ViewerHostName	);
		PRINT_ARGUMENT (a_Charset			);

		ap_rprintf (r, "<hr><b>Куки:</b><br>");
		PRINT_ARGUMENT (a_TestCookie		);
		PRINT_ARGUMENT (a_TSMC_Viewer_ID	);

		ap_rprintf (r, "<hr><b>Аргументы:</b><br>");
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
		PRINT_ARGUMENT (a_SECOND_REQUEST		);	
		PRINT_ARGUMENT (a_TC						);	
*/
		ap_rprintf (r, "<p><hr><b>Запрос:</b><br>");
		PRINT_ARGUMENT (in_Alias					   );
		PRINT_ARGUMENT (in_SiteID						);
		PRINT_ARGUMENT (in_JustGetData				);
		PRINT_ARGUMENT (in_CounterType				);
		PRINT_ARGUMENT (in_PageNo						);
		PRINT_ARGUMENT (in_CookieSupported			);
		PRINT_ARGUMENT (in_ViewerID					);
		PRINT_ARGUMENT (in_LocalTime					);
		PRINT_ARGUMENT (in_ViewerIP					);
		PRINT_ARGUMENT (in_SiteURL						);
		PRINT_ARGUMENT (in_Referrer					);
		PRINT_ARGUMENT (in_ViewerHostName			);
		PRINT_ARGUMENT (in_UserAgent					);
		PRINT_ARGUMENT (in_ScreenResolution			);
		PRINT_ARGUMENT (in_ColorDepth					);
		PRINT_ARGUMENT (in_JavaEnabled				);
		PRINT_ARGUMENT (in_JavaScriptVersion		);
		PRINT_ARGUMENT (in_Charset						);
		PRINT_ARGUMENT (in_Language					);

		ap_rprintf (r, "<p><hr><b>Результат запроса:</b><br>");
		ap_rprintf (r, "out_ViewerID       = %lu<br>",	out_ViewerID);
		ap_rprintf (r, "out_ExitCode       = %d<br>",	out_ExitCode);
		ap_rprintf (r, "out_Total_Hits     = %d<br>",	out_Total_Hits);
		ap_rprintf (r, "out_Total_Hosts    = %d<br>",	out_Total_Hosts);
		ap_rprintf (r, "out_Total_Visitors = %d<br>",	out_Total_Visitors);

	ap_rprintf (r, "</PRE></BODY></HTML>");
//----------------------------------------------------------------------------[] 



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

