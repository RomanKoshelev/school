/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoObject.h															[]
[] Date:          16.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с информационными объектами.									[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_InfoObject_h
#define MOD_InfoObject_h


#define MAX_INFOOBJECT_ENUMERATE_NUM	1000

//----------------------------------------------------------------------------[] 
// Коды и описания действий над объектами
#define INFOOBJ_ACTION_first_bad		0
#define INFOOBJ_ACTION_CREATE			1
#define INFOOBJ_ACTION_PUBLIC			2
#define INFOOBJ_ACTION_FORBID			3
#define INFOOBJ_ACTION_CHANGENAME	4
#define INFOOBJ_ACTION_CHANGETEXT	5
#define INFOOBJ_ACTION_ADDTOPIC		6
#define INFOOBJ_ACTION_DELTOPIC		7
#define INFOOBJ_ACTION_CHANGEDESC	8
#define INFOOBJ_ACTION_REGULAR		9
#define INFOOBJ_ACTION_HOT				10
#define INFOOBJ_ACTION_last_bad		11
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
static char *INFOOBJ_ACTION_DESCRIPTION [] = 
{
	"{{ERROR}}",
	"Создание",
	"Публикация",
	"Запрещение",
	"Изменение заголовка",
	"Изменение содержания",
	"Добавление тематики",
	"Удаление тематики",
	"Изменение аннотации",
	"Обычный материал"
	"Горячий материал",
	"{{ERROR}}"
};
//----------------------------------------------------------------------------[] 


// [Sonora]
//------------------------------------------------------------------------------------[] 
/* Проверка на изменение положения в разделах с записью в лог						        */
#define CHECK_DIV_AND_SET_LOG_RECORD(LOGIN_GUID,DIV,ACT,COMMENT,OBJ_GUID,WAS_ACT,IS_ACT)\
{																													\
	identifier	div_ID		= GetInfoDivIDByType	(DIV);											\
	bool			WasAction	= WAS_ACT.Find			(div_ID)!=-1;									\
	bool			IsAction		= IS_ACT.Find			(div_ID)!=-1;									\
	time_t      cur_Time=time(0);																			\
	if (!WasAction && IsAction)																			\
   { 																												\
		printf ("Action in CHECK: %s", #ACT);															\
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_##ACT;											\
   	oc_info.m_Log_UserGUID	+= LOGIN_GUID;															\
	   oc_info.m_Log_Time		+=	cur_Time;															\
	   oc_info.m_Log_Comment	+=	COMMENT;																\
      UserProfileLogUpdate (guid(LOGIN_GUID).id, USER_LOG_##ACT, OBJ_GUID, cur_Time);	\
	}																												\
}
//-------------------------------------------------------------------------------------[] 






//______________________________________________________________________________
//                                                                            []
//` Разделы информации																			[]
//                                                                            []
struct MOD_InfoObject_Args
{ 
	MOD_InfoObject_Args()
	{
		objID						=	NA;
		ExitCode					=	-1;
		InfoSourceID			=  NA;
		Time0						=	0;
		Time1						=	0;
		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		TotalStoredNum			=	0;
		bNeedTotalStoredNum	=	false;
		UpdateStatistics		=	false;

		divLookInSub			=	false;

		InfoTime					=	0;

		StatShow					=	0;
		StatClick				=	0;
		StatCTR					=	0.0;

		bNeedText				=	false;
		bNeedURL					=	false;
		bNeedLog					=	false;
		ProxyID					=	NA;
		OwnerID					=	NA;

		MaxNumInQuery			=	MAX_USER_ENUMERATE_NUM;
	}

	string			Login;
	string			Password;
	identifier		objID;
	identifier		ProxyID;
	identifier_arr	divIDs;
	string_arr		divNames;
	string			divAttributes;
	bool				divLookInSub;
	bool				bNeedTotalStoredNum;
	bool				bNeedText;
	bool				bNeedURL;
	string_arr		objTexts;
	string_arr		objURLs;
	string			Name;
	string			Description;
	string			Text;
	string			URL;
	string_arr		RelatedLinks;
	identifier_arr	objIDs;
	identifier_arr	objProxyIDs;
	string_arr		objNames;
	string_arr		objDescriptions;
	bool				UpdateStatistics;
	int_arr			objInfoTimes;
	int_arr			objStatShows;
	int_arr			objStatClicks;
	float_arr		objStatCTRs;
	identifier		InfoSourceID;
	string			InfoSourceName;
	string			InfoSourceURL;
	time_t			InfoTime;
	string			AuthorStr;

	bool				bNeedLog;
	identifier		OwnerID;
	string			OwnerLogin;
	string			OwnerName;

	identifier_arr	objLogCreatorIDs;
	string_arr		objLogCreatorLogins;
	string_arr		objLogCreatorNames;
	identifier_arr	objLogPublisherIDs; 
	string_arr		objLogPublisherLogins;
	string_arr		objLogPublisherNames;
	identifier_arr	objLogForbidderIDs; 
	string_arr		objLogForbidderLogins;
	string_arr		objLogForbidderNames;
	identifier_arr	objLogHotterIDs; 
	string_arr		objLogHotterLogins;
	string_arr		objLogHotterNames;


	int_arr			Log_Action;
	string_arr		Log_Description;
	identifier_arr	Log_UserID;
	string_arr		Log_UserLogin;
	string_arr		Log_UserName;
	int_arr			Log_Time;
	string_arr		Log_Comment;
	
	int				StatShow;
	int				StatClick;
	float				StatCTR;
	time_t			Time0;
	time_t			Time1;
	int				TotalStoredNum;
	int				MaxNumInQuery;
	int				objFirstNo;
	int				objLastNo;
	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_InfoObject_New					(MOD_InfoObject_Args& arg);
ERR_RESULT		MOD_InfoObject_Enumerate			(MOD_InfoObject_Args& arg);
ERR_RESULT		MOD_InfoObject_GetData				(MOD_InfoObject_Args& arg);
ERR_RESULT		MOD_InfoObject_PutData				(MOD_InfoObject_Args& arg);
ERR_RESULT		MOD_InfoObject_Delete				(MOD_InfoObject_Args& arg);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//                                                                            []
ERR_RESULT		USER_CHECK_ACCESS_TO_INFOOBJECT	(identifier userID, identifier infoID, const string& Attributes);
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 
void MOD_GET_OBJECT_NAME_InfoObject				(guid& gi, string& sNAME);
void MOD_GET_OBJECT_DESCRIPTION_InfoObject	(guid& gi, string& sNAME);
void MOD_CHECK_ACCESS_InfoObject					(identifier userID, guid& gi, const string& Attributes);
void MOD_CHECK_PLACEMENT_InfoObject				(identifier_arr& feodIDs, guid& gi);
//----------------------------------------------------------------------------[] 



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/