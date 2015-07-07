/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoObject.cpp														[]
[] Date:          16.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с информационными объектами.									[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoObject.inc.h"


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ИНФОРМАЦИОННОГО ОБЪЕКТА												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_New (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_New);
/*............................................................................[]
		<Login                  Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами создания объектов во всех указанных разделах.
		<Password               Пароль пользователя, запрашивающего операцию.
		<Name                   Имя создаваемого объекта.
		<Description            Описание создаваемого объекта.
		<Text							Полное содержание.
		<InfoSourceID				Источник информации.
		<URL							Собственный URL
		<RelatedLinks				Ссылки по теме
		<divIDs						К каким информационным разделам будет относиться объект.
		<InfoTime					Время, приписанное к информационному объекту. Если не указано -- текущее время.
		<AuthorStr					Имя автора, не являющегося пользователем

		>objID                  Идентификатор созданного объекта.
		>ProxyID						Для семантической сети -- идентификатор соответствующего прокси-объекта.

		>ExitCode               Код возврата (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment        Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Разделы должны существовать
	int d;
	for (d=0; d<arg.divIDs.Size(); d++) if (!CHECK_INFODIV_ID (arg.divIDs[d]))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан некорректный информационный раздел ID=%u", arg.divIDs[d]);
	}
// Если источник указан, то он должен существовать
	if (arg.InfoSourceID!=NA && !OC_Exist (OBJ_CLASS_ID_InfoSource, arg.InfoSourceID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан несуществующий источник информации ID=%u", arg.InfoSourceID);
	}

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь права создавать объекты в указанных разделах
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		OC_InfoDiv oc_div (arg.divIDs[d]);
		res=USER_CHECK_ACCESS (loginID, guid(oc_div.m_MOD_Base_GUID).id, "C");
		if (res!=ERR_OK)
		{
			string divName;
			GetInfoDivFullName (arg.divIDs[d], divName);
			ERR_RETURN_COMMENT_3 (res, "Пользователь %s не имеет права создавать объекты в разделе '%s'[%u]", arg.Login.c_str(), divName.c_str(), arg.divIDs[d]);
		}
	}
//----------------------------------------------------------------------------[]


//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя объекта не должно быть пустым");
	}
// Если не указано время объекта, делаем его равным текущему
	if (arg.InfoTime==0)
	{
		arg.InfoTime = time(0);
	}
// Проверяем наличие необходимого набора разделов

#if 0  //{ RomanVK
	identifier_arr subDivIDs;
	bool				bFound=false;
	{
	// Хотя бы один раздел должен быть признаковым
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Mark"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть признаковым, т.е. подразделом {Concept.Feod.Data.Mark}");}
	// Хотя бы один раздел должен быть служебным
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Service"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть служебным, т.е. подразделом {Concept.Feod.Data.Service}");}
	// Хотя бы один раздел должен быть тематическим
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть тематическим, т.е. подразделом {Concept.Feod.Data.Topic}");}
	// Хотя бы один раздел должен быть типом информационного материала
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Type"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть типовым, т.е. подразделом {Concept.Feod.Data.Type}");}
	}
#endif //}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём объект и записываем его в раздел
	OC_InfoObject oc_info;
	oc_info.New ();
// Создаём прокси-объект для семантической сети
	CHECK_PROXY_OBJECT_OF (oc_info);

	FULL_INDEX_BEGIN (oc_info);
		identifier infoID					= oc_info.GetObjectID ();
		oc_info.m_Name						= arg.Name;
		oc_info.m_Description			= arg.Description;
		oc_info.m_Text						= arg.Text;
		oc_info.m_OwnerGUID				= GetUserGUID (loginID);
		oc_info.m_URL						= arg.URL;
		oc_info.m_RelatedLinks			= arg.RelatedLinks;
		oc_info.m_InfoSourceID			= arg.InfoSourceID;
		oc_info.m_InfoDivID				= arg.divIDs;
		oc_info.m_CreationTime			= time(0);
		oc_info.m_InfoTime				= arg.InfoTime;
		oc_info.m_AuthorStr				= arg.AuthorStr;
	FULL_INDEX_END (oc_info);

// Добавляем объект в разделы
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		OC_InfoDiv oc_div (arg.divIDs[d]);
		oc_div.m_InfoObjectSortedID.InsertSorted (infoID);
	}
//----------------------------------------------------------------------------[] 




	
//----------------------------------------------------------------------------[] 
// [Sonora]
// Работа с логами
//
	guid			loginGUID	=	GetUserGUID (loginID); 
	guid			objGUID		=	oc_info.GetObjectGUID (); 
	time_t		cur_Time		=	time(0);

	identifier_arr DivIDsarr;
	bool				bFound=false;
	string			strDivIDs;

// Пополнение лога пользователя - заносим в него, что пользователь создал объект
	UserProfileLogUpdate (loginID, USER_LOG_CREATE, objGUID, cur_Time);

//	Пополнение лога объекта -- заносим в него, что объект	создан
	oc_info.m_Log_Action		+= INFOOBJ_ACTION_CREATE;
	oc_info.m_Log_UserGUID	+= loginGUID;
	oc_info.m_Log_Time		+=	cur_Time;
	oc_info.m_Log_Comment	+=	"";

// Пополнение лога пользователя - заносим в него, что пользователь выбрал тематики
	UserProfileLogUpdate (loginID, USER_LOG_ADDTOPIC, objGUID, cur_Time);

// Собираем форматированную строку strDivIDs из выбранных пользователем тематик
	InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), DivIDsarr);
	for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) 
	{
		if (DivIDsarr.Find (arg.divIDs[d])!=-1) 
		{
			string tmplate;
			tmplate.Format	("+%lu ",arg.divIDs[d] );
			strDivIDs += tmplate;
		}
	}

// Пополнение лога объекта -- заносим в него, выбранные тематики
	oc_info.m_Log_Action		+= INFOOBJ_ACTION_ADDTOPIC;
	oc_info.m_Log_UserGUID	+= loginGUID;
	oc_info.m_Log_Time		+=	cur_Time;
	oc_info.m_Log_Comment	+=	strDivIDs;

										 
// Создаем пустой массив идентификаторов разделов для функции CHECK_DIV_AND_SET_LOG_RECORD	
	identifier_arr InfoDivID;

//	Проверяем, стал ли объект опубликованным, если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Public",		PUBLIC, "", objGUID, InfoDivID, arg.divIDs);
//	Проверяем, стал ли объект запрещённым, если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Forbidden",	FORBID, "", objGUID, InfoDivID, arg.divIDs);

//	Проверяем, стал ли объект "горячим материалом", если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Hot",	HOT, "", objGUID, InfoDivID, arg.divIDs);

//	Проверяем, стал ли объект "обычным материалом", если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Regular",	REGULAR, "", objGUID, InfoDivID, arg.divIDs);

	arg.objID	=	infoID;
	arg.ProxyID	=	guid(oc_info.m_ProxyObject).id;
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ИНФОРМАЦИОННЫХ ОБЪЕКТОВ													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_Enumerate (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право получения списка.
		<Password					Пароль пользователя, запрашивающего операцию.
		<Time0						Допустимое время самых молодых объектов. Начало диапазона. По умолчанию = time(0);
		<Time1						Допустимое время самых старых объектов. Конец диапазона. По умолчанию = (time_t)0;
		<objFirstNo					Номер объекта, с которого их перечислять.
		<objLastNo					Номер последнего запрашиваемого объекта.
		<divIDs						К каким разделам должен принадлежать объект. У пользователя должны быть права получения списка [L] во всех указанных разделах. Объект должен принадлежать сразу всем разделам. Например: "Concept.Feod.Data.Type.News.Промышленность.Власть" & "Concept.Feod.Data.Service.Process.Public" -- что означает опубликованные новости подраздела "Власть". Если не указано -- работать по divNames
		<divNames					К каким разделам должен принадлежать объект, если не указаны divIDs. Полные имена вида "Concept.Feod.Data.Type.News.Промышленность.Нефть".
		<divLookInSub				Если true -- перечислять также и объекты из подразделов. Все объекты перечисляются по одному разу.
		<divAttributes				Строка вида "CLWRD". Перечисляются объекты только тех разделов, доступ к которым снабжён указанными атрибутами.
		<UpdateStatistics			Надо ли изменять статистику показов/кликов/CTR запрашиваемых объектов. Например, для издательского интерфейса это не надо делать, а на морде сайта -- надо.
		<InfoSourceID				Если не NA, выдаются только объекты с указанным источником.
		<bNeedTotalStoredNum		Требуется ли получить общее число объектов, которые могут быть перечислены.
		<bNeedText					Возвращать ли массив с текстовым содержанием объектов. Если пользователь не имеет право [R] во всех разделах, в которых лежит объект, возвращается строка "{{ACCESS DENY}}"".
		<bNeedURL					Возвращать ли массив с ссылками объектов. Если пользователь не имеет право [R] во всех разделах, в которых лежит объект, возвращается строка "{{ACCESS DENY}}"".
		<bNeedLog					Надо ли показывать информацию по логу (авторы, публикаторы, ...) (по умолчанию false) реализуемо если логин имеет право {Concept.Feod.Admin.User.Data}[R] просматривать данные пользователей.

		>objIDs						Массив идентификаторов объектов.
		>objProxyIDs				Для семантической сети -- массив идентификаторов соответствующих прокси-объектов.
		>objNames					Массив названий объектов.
		>objDescriptions			Массив описаний объектов (анонсы).

		>objLogCreatorIDs			Идентификаторы создателей (или, если таковые не найдены, то владельцев) публикаций (только если bNeedLog == true).
		>objLogCreatorLogins		Логины создателей публикаций (только если bNeedLog == true).
		>objLogCreatorNames		Имена создателей публикаций (только если bNeedLog == true).

		>objLogPublisherIDs		Идентификаторы публикаторов публикаций (только если bNeedLog == true).	
		>objLogPublisherLogins	Логины публикаторов публикаций (только если bNeedLog == true).	
		>objLogPublisherNames	Имена публикаторов публикаций (только если bNeedLog == true).		

		>objLogForbidderIDs		Идентификаторы запретителей публикаций (только если bNeedLog == true).	
		>objLogForbidderLogins	Логины запретителей публикаций (только если bNeedLog == true).	
		>objLogForbidderNames	Имена запретителей публикаций (только если bNeedLog == true).		

		>objLogHotterIDs			Идентификаторы Hotter(ов) публикаций (только если bNeedLog == true).	
		>objLogHotterLogins		Логины Hotter(ов) публикаций (только если bNeedLog == true).
		>objLogHotterNames		Имена Hotter(ов) публикаций (только если bNeedLog == true).	


		>objTexts					Массив текстовых содержаний объектов. Если bNeedText=false, массив пустых строк. Если нет права [R], {{ACCESS DENY}}
		>objURLs						Массив собственных web-адресов объектов. Если bNeedURL=false, массив пустых строк. Если нет права [R], {{ACCESS DENY}}
		>objInfoTimes				Время, приписанное к информационному объекту.
		>objStatShows				Сколько раз объект был показан
		>objStatClicks				Сколько раз объект был востребован для просмотра
		>objStatCTRs				objStatClicks*100/objStatShows
		>TotalStoredNum			Сколько всего объектов может быть перечислено.
		>MaxNumInQuery				Максимально допустимое число запрашиваемых за один раз объектов.
		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]

	

//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
// Если начало временного диапазона не указано, то используется текущее время
	if (arg.Time0==0)
	{
		arg.Time0 = time(0);
	}
// Если не указаны ID разделов, берём их по имени, которое совпадает с типом концепта-феода.
	if (arg.divIDs.Size()==0)
	{
		FOR_EACH_ITEM_EVAL(arg.divNames, 
		{
			arg.divIDs += GetInfoDivIDByType (arg.divNames[i]);
		});
	}
// Разделы должны существовать
	FOR_EACH_ITEM_EVAL (arg.divIDs, {if (!CHECK_INFODIV_ID (arg.divIDs[i])) ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан несуществующий информационный раздел ID=%u", arg.divIDs[i]);});

// Если источник указан, то он должен существовать
	if (arg.InfoSourceID!=NA && !OC_Exist (OBJ_CLASS_ID_InfoSource, arg.InfoSourceID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указан несуществующий источник информации ID=%u", arg.InfoSourceID);
	}

// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_INFOOBJECT_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_INFOOBJECT_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}

//	Должен быть доступ L
	if (arg.divAttributes.Find ("L")==-1)
	{
		arg.divAttributes += "L";
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь право получения списка объектов во всех разделах
	FOR_EACH_ITEM_EVAL (arg.divIDs,
		{
			res = USER_CHECK_ACCESS (loginID, guid(OC_InfoDiv(arg.divIDs[i]).m_MOD_Base_GUID).id, "L");
			if (res!=ERR_OK)
			{
				string feodName="";
				GetFeodFullName (guid(OC_InfoDiv(arg.divIDs[i]).m_MOD_Base_GUID).id, feodName);
				ERR_RETURN_COMMENT_2 (res, "Пользователь %s не имеет права просматривать содержимое раздела %s", arg.Login.c_str(), feodName.c_str());
			}
		}
	);
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Эту переменную пишу здесь как статическую, так как иначе глупый VC++6.0 
//	выдаёт INTERNAL COMPILER ERROR
	int i=0;
	int j=0;
	int d=0;
	int nFound=0;

// Находим все идентификаторы объектов, отсортированные по убыванию во времени - самые свежие идут первыми
	OC_InfoObject oc_info;
	key_arr ka0, ka1;
	if (arg.InfoSourceID!=NA)
	{
		ka0	+= arg.InfoSourceID;
		ka0	+= arg.Time0;
		ka1	+=	arg.InfoSourceID;
		ka1	+=	arg.Time1;
		oc_info.SetIndex_InfoSourceID__InfoTime ();
	}
	else
	{
		ka0	+= arg.Time0;
		ka1	+=	arg.Time1;
		oc_info.SetIndex__InfoTime ();
	}
	identifier_arr infoIDs;
	oc_info.GetClassIdListInRange (infoIDs, &ka0, &ka1);
	

// Массив списков всех объектов по всем заданным разделам
	identifier_arr_arr_arr allDivObjs(arg.divIDs.Size());
	for (d=0; d<arg.divIDs.Size(); d++)
	{
	// Для текущего раздела составляем список всех объектов -- или его лично или включая принадлежащие потомкам.
		if (arg.divLookInSub)	InfoDivGetAllInfoObjectSortedIDs (arg.divIDs[d], allDivObjs[d]);
		else							{allDivObjs[d].Alloc (1); OC_InfoDiv (arg.divIDs[d]).m_InfoObjectSortedID.CopyTo (allDivObjs[d][0]);}
	}


// Вычёркиваем объекты, которые не подходят по заданным условиям (не во всех разделах или нет доступа)
	for (i=0; i<infoIDs.Size(); i++)	
	{
	// Вычёркиваем объекты, не найденые хотя бы в одном из запрашиваемых разделов
		for (d=0; d<allDivObjs.Size(); d++) 
		{
			bool bFound=false;
		// Проходимся по всем подразделам раздела
			for (int dd=0; dd<allDivObjs[d].Size(); dd++) if (allDivObjs[d][dd].Find (infoIDs[i], true)!=-1)
			{
			// Объект найден в одном из подразделов
				bFound = true;
				break;
			}

		// Объект не найден ни в самом разделе, ни в одном из его подразделов, вычёркиваем его.
			if (bFound==false)
			{
				infoIDs[i]=NA;
				break;
			}
		}

	// Вычёркиваем объекты, к которым нет доступа
		if (infoIDs[i]!=NA && USER_CHECK_ACCESS_TO_INFOOBJECT(loginID,infoIDs[i],arg.divAttributes)!=ERR_OK)
		{
			infoIDs[i]=NA;
		}

	// Число найденных удовлетворяющих объектов
		nFound += infoIDs[i]!=NA;

	// Если найдено необходимое число объектов и не требуется узнать сколько их всего надо, 
	// то вываливаемся, вычёркивая все оставшиеся объекты.
		if ((nFound > arg.objLastNo+1) && !arg.bNeedTotalStoredNum)
		{
			for (int j=i+1; j<infoIDs.Size(); j++)	infoIDs[j]=NA;
			break;
		}
	}


//	Определяем идентификаторы интересных для лога разделов
	identifier PublicDivID		=	GetInfoDivIDByType ("Concept.Feod.Data.Service.Public");
	identifier ForbiddenDivID	=	GetInfoDivIDByType ("Concept.Feod.Data.Service.Forbidden");
	identifier HotDivID			=	GetInfoDivIDByType ("Concept.Feod.Data.Mark.Hot");


// infoIDs -- все допустимые объекты запрашиваемых разделов, 
// остортированные по времени от молодых к старым. 
// Оставляем необходимое количество.
	for (j=0, i=0; i<infoIDs.Size(); i++) if (infoIDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) 
		{
			j++;
			continue;
		}
		else j++;

		if (!OC_Exist (OBJ_CLASS_ID_InfoObject, infoIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("Некорректный идентификатор информационного объекта %u", infoIDs[i]);
			continue;
		}
		OC_InfoObject oc_info (infoIDs[i]);

		arg.objIDs				+= infoIDs[i];
		arg.objProxyIDs		+=	guid(oc_info.m_ProxyObject).id;
		arg.objNames			+=	oc_info.m_Name;
		arg.objDescriptions	+=	oc_info.m_Description;
		arg.objInfoTimes		+=	oc_info.m_InfoTime;
		arg.objStatShows		+= oc_info.m_ShowCount;
		arg.objStatClicks		+=	oc_info.m_ClickCount;
		arg.objStatCTRs		+=	oc_info.m_CTR;





	//----------------------------------------------------------------------------[] 
	// Работа с урезанными логами, если надо.
	//
		if (arg.bNeedLog)
		{
		// Проверяем доступ -- логин должен иметь право просматривать данные пользователей
			if (USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), "R") != ERR_OK)
			{
				ERR_RETURN_COMMENT_1 (res, "Пользователь %s не может просматривать лог, так как не имеет права {Concept.Feod.Admin.User.Data}[R] (просматривать данные пользователей)", arg.Login.c_str());
			}

		// Подготавливаем аргументы
			guid			CreatorGUID;
			string		CreatorLogin;
			string		CreatorName;

			guid			PublisherGUID;
			string		PublisherLogin;
			string		PublisherName;

			guid			ForbidderGUID;
			string		ForbidderLogin;
			string		ForbidderName;

			guid			HotterGUID;
			string		HotterLogin;
			string		HotterName;


		// Находим пользователей, совершивших интересующие действия
			int l;
			int oc_info_m_Log_Action_Size = oc_info.m_Log_Action.Size();
			for (l=0; l<oc_info_m_Log_Action_Size; l++)
			{
				int nAction = oc_info.m_Log_Action[l];
				switch (nAction)
				{
					case INFOOBJ_ACTION_CREATE:
						if (CreatorGUID.id == NA)
						{
							CreatorGUID = oc_info.m_Log_UserGUID[l];
							CreatorGUID.id = UserGetLoginFullName (CreatorGUID, CreatorLogin, CreatorName);
						}
						else SERVER_DEBUG_ERROR_2 ("В логе объекта %s[%d] создатель встретился более 1-го раза", string(oc_info.m_Name).c_str(), infoIDs[i]);
					break;

					case INFOOBJ_ACTION_PUBLIC:
						PublisherGUID = oc_info.m_Log_UserGUID[l];
					break;

					case INFOOBJ_ACTION_FORBID:
						ForbidderGUID = oc_info.m_Log_UserGUID[l];
					break;

					case INFOOBJ_ACTION_HOT:
						HotterGUID = oc_info.m_Log_UserGUID[l];
					break;
				}
			}


		// Если создатель не найден, вместо него пишем владельца
			if (CreatorGUID.id == NA)
			{
				CreatorGUID		= oc_info.m_OwnerGUID;
				CreatorGUID.id = UserGetLoginFullName (CreatorGUID, CreatorLogin, CreatorName);
			}

		// Если объект в интересующем состоянии, пишем кто его в это состояние перевёл
			int oc_info_m_InfoDivID_Size = oc_info.m_InfoDivID.Size();
			bool bPublished	= false;
			bool bForbidded	= false;
			bool bHotted		= false;
			for (int d=0; d< oc_info_m_InfoDivID_Size; d++)
			{
				if (oc_info.m_InfoDivID[d]==PublicDivID)		bPublished	= true;
				if (oc_info.m_InfoDivID[d]==ForbiddenDivID)	bForbidded	= true;
				if (oc_info.m_InfoDivID[d]==HotDivID)			bHotted		= true;
			}

		// Заполняем аргументы -- создатель
			arg.objLogCreatorIDs		+=	CreatorGUID.id;
			arg.objLogCreatorLogins	+=	CreatorLogin;
			arg.objLogCreatorNames	+=	CreatorName;

		// Заполняем аргументы -- публикатор
			if (bPublished)
			{
				PublisherGUID.id = UserGetLoginFullName (PublisherGUID, PublisherLogin, PublisherName);
				arg.objLogPublisherIDs		+=	PublisherGUID.id;
				arg.objLogPublisherLogins	+=	PublisherLogin;
				arg.objLogPublisherNames	+=	PublisherName;
			}
			else
			{
				arg.objLogPublisherIDs		+=	NA;
				arg.objLogPublisherLogins	+=	"";
				arg.objLogPublisherNames	+=	"";
			}

		// Заполняем аргументы -- запретитель
			if (bForbidded)
			{
				ForbidderGUID.id			= UserGetLoginFullName (ForbidderGUID, ForbidderLogin, ForbidderName);
				arg.objLogForbidderIDs		+=	ForbidderGUID.id;
				arg.objLogForbidderLogins	+=	ForbidderLogin;
				arg.objLogForbidderNames	+=	ForbidderName;
			}
			else
			{
				arg.objLogForbidderIDs		+=	NA;
				arg.objLogForbidderLogins	+=	"";
				arg.objLogForbidderNames	+=	"";
			}


		// Заполняем аргументы -- горячитель
			if (bHotted)
			{
				HotterGUID.id				= UserGetLoginFullName (HotterGUID, HotterLogin, HotterName);
				arg.objLogHotterIDs		+=	HotterGUID.id;
				arg.objLogHotterLogins	+=	HotterLogin;
				arg.objLogHotterNames	+=	HotterName;
			}
			else
			{
				arg.objLogHotterIDs		+=	NA;
				arg.objLogHotterLogins	+=	"";
				arg.objLogHotterNames	+=	"";
			}

		}
	//----------------------------------------------------------------------------[] 




	// Расширенное перечисление -- возможно только при наличии прав
		bool bReadAccess = false;
		if (arg.bNeedText || arg.bNeedURL)
		{
			bReadAccess = USER_CHECK_ACCESS_TO_INFOOBJECT (loginID, infoIDs[i], "R")==ERR_OK;
		}
		if (arg.bNeedText)
		{
			if (bReadAccess)	arg.objTexts += oc_info.m_Text;
			else					arg.objTexts += "{{ACCESS DENY}}";
		}
		else arg.objTexts+="";
		if (arg.bNeedURL)
		{
			if (bReadAccess)	arg.objURLs += oc_info.m_URL;
			else					arg.objURLs += "{{ACCESS DENY}}";
		}
		else arg.objURLs+="";


	// Если необходимо, изменяем статистику.
		if (arg.UpdateStatistics)
		{
			oc_info.m_ShowCount	+= 1;
			if (oc_info.m_ShowCount!=0)
			{
				oc_info.m_CTR = (oc_info.m_ClickCount*100)/float(int(oc_info.m_ShowCount));
			}
		// !!! Изменить статистику у пользователя [UserDPS], источника и разделов
		}
	}

	arg.TotalStoredNum = arg.bNeedTotalStoredNum? nFound: -1;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ИНФОРМАЦИОННОГО ОБЪЕКТА												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_GetData (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_GetData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право чтения "R" во всех разделах, где находится объект.
		<Password					Пароль пользователя, запрашивающего операцию.
		<objID						Идентификатор запрашиваемого информационного объекта.
		<UpdateStatistics			Надо ли изменять статистику показаов/кликов/CTR запрашиваемых объектов. Например, для издательского интерфейса это не надо делать, а на морде сайта -- надо.

		>ProxyID						Для семантической сети -- идентификатор соответствующего прокси-объекта.
		>Name							Название объекта.
		>Description				Описание объекта (анонс).
		>Text							Содержание объекта.
		>URL							Собственный адрес объекта.
		>RelatedLinks				Ссылки по теме
		>InfoSourceID				Источник информации
		>InfoSourceName			Название источника информации
		>InfoSourceURL				URL источника информации
		>InfoTime					Время, приписанное к информационному объекту (по умолчанию=CreationTime).
		>StatShow					Сколько раз объект был показан
		>StatClick					Сколько раз объект был востребован для просмотра
		>StatCTR						objStatView*100/objStatShow
		>divIDs						К каким разделам принадлежит объект.
		>divNames					Имена разделов.
		>AuthorStr					Имя автора, не являющегося пользователем
		>OwnerID						Идентификатор создателя публикации.
		>OwnerLogin					Логин создателя публикации.
		>OwnerName					Имя создателя публикации.

		>bNeedLog					Нужно ли получать лог изменений информационного объекта, для получения требуется доступ [R] к данным пользователей {Concept.Feod.Admin.User.Data}, По умолчанию false.
		>Log_Action					Список действий над информационным объектом, если bNeedLog==false -- пустой массив.
		>Log_UserID					Список идентификаторов пользователей, совершивших действие, если bNeedLog==false -- пустой массив.
		>Log_UserLogin				Список логинов пользователей, совершивших действие, если bNeedLog==false -- пустой массив.
		>Log_UserName				Список полных имён пользователей, совершивших действие, если bNeedLog==false -- пустой массив.
		>Log_Time					Времена совершения действий над информационным объектом, если bNeedLog==false -- пустой массив.
		>Log_Comment				Строковые комментарии к действиям, если bNeedLog==false -- пустой массив.

		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny)
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_InfoObject, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект %u не существует", arg.objID);
	}
	OC_InfoObject oc_info (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь право чтение объекта во всех разделах, в которых лежит объект
	for (int d=0; d<oc_info.m_InfoDivID.Size(); d++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByInfoDivID (oc_info.m_InfoDivID[d]), "R");
		if (res!=ERR_OK)
		{
			string feodName="";
			GetFeodFullName (guid(OC_InfoDiv(oc_info.m_InfoDivID[d]).m_MOD_Base_GUID).id, feodName);
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "Пользователь %s не иммеет права читать объект, так как не имеет доступа [R] к разделу '%s'[%u]", arg.Login.c_str(), feodName.c_str(), identifier (oc_info.m_InfoDivID[d]));
		}
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если необходимо, изменяем статистику.
	if (arg.UpdateStatistics)
	{
		oc_info.m_ClickCount	+= 1;
		if (oc_info.m_ShowCount!=0)
		{
			oc_info.m_CTR = (oc_info.m_ClickCount*100)/float(int(oc_info.m_ShowCount));
		}
	// !!! Изменить статистику у пользователя [UserDPS], источника и разделов
	}

	identifier	OwnerID=NA;
	string		OwnerLogin;
	string		OwnerName;
	OwnerID		= UserGetLoginFullName (oc_info.m_OwnerGUID, OwnerLogin, OwnerName);

// Заполняем выходные аргументы
	arg.ProxyID				=	guid(oc_info.m_ProxyObject).id;
	arg.Name					=	oc_info.m_Name;
	arg.Description		=	oc_info.m_Description;
	arg.Text					=	oc_info.m_Text;
	arg.URL					=	oc_info.m_URL;
	arg.RelatedLinks		=	oc_info.m_RelatedLinks;
	arg.InfoTime			=	oc_info.m_InfoTime;
	arg.StatShow			=	oc_info.m_ShowCount;
	arg.StatClick			=	oc_info.m_ClickCount;
	arg.StatCTR				=	oc_info.m_CTR;
	arg.divIDs				=	oc_info.m_InfoDivID;
	arg.AuthorStr			=	oc_info.m_AuthorStr;
	arg.OwnerID				=	OwnerID;
	arg.OwnerLogin			=	OwnerLogin;
	arg.OwnerName			=	OwnerName;
	arg.InfoSourceID		=	oc_info.m_InfoSourceID;
	if (arg.InfoSourceID!=NA)
	{
		GetInfoSourceNameURL (arg.InfoSourceID, arg.InfoSourceName, arg.InfoSourceURL);
	}

// [Sonora] Получение лога изменений -- только тем, кто имееет право доступа [R] к данным пользователей.
	if (arg.bNeedLog && USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), "R")==ERR_OK)
	{
		for (int a=0; a<oc_info.m_Log_Action.Size(); a++)
		{
			int nAction = oc_info.m_Log_Action	[a];

			if (nAction>=INFOOBJ_ACTION_last_bad || nAction <= INFOOBJ_ACTION_first_bad)
			{
				SERVER_DEBUG_ERROR_1 ("Ошибочный тип записи (%d) в лог, исправлено", nAction);
				oc_info.m_Log_Action		.Del (a);
				oc_info.m_Log_UserGUID	.Del (a);
				oc_info.m_Log_Time		.Del (a);
				oc_info.m_Log_Comment	.Del (a);
				a --;
				continue;
			}

			arg.Log_Action			+= nAction;
			arg.Log_Description	+= INFOOBJ_ACTION_DESCRIPTION [nAction];
			arg.Log_Comment		+= oc_info.m_Log_Comment		[a];
			arg.Log_Time			+= oc_info.m_Log_Time			[a];

			identifier	logUserID=NA;
			string		logUserLogin;
			string		logUserName;
			logUserID	= UserGetLoginFullName (oc_info.m_Log_UserGUID[a], logUserLogin, logUserName);

			if (logUserID!=NA)
			{
				arg.Log_UserID			+=	logUserID;
				arg.Log_UserLogin		+=	logUserLogin;
				arg.Log_UserName		+=	logUserName;
			}
			else
			{
				arg.Log_UserID			+=	NA;
				arg.Log_UserLogin		+=	"";
				arg.Log_UserName		+=	"";
			}
		}
	}


//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ИНФОРМАЦИОННОГО ОБЪЕКТА												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_PutData (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_PutData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право записи "W" во всех разделах, где находится объект.
		<Password					Пароль пользователя, запрашивающего операцию.
		<objID						Идентификатор запрашиваемого информационного объекта.
		<Name							Название объекта.
		<Description				Описание объекта (анонс).
		<Text							Содержание объекта.
		<URL							Собственный адрес объекта.
		<RelatedLinks				Ссылки по теме
		<InfoSourceID				Источник информации
		<InfoTime					Время, приписанное к информационному объекту.
		<divIDs						К каким разделам, по мнению логина, должен принадлежать объект. Логин не может выкинуть объект из раздела без доступа [D] и добавить в раздел без доступа [C].
		<AuthorStr					Имя автора, не являющегося пользователем

		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объявляем переменные статическими чтобы избежать глупой ошибки "INTERNAL COMPILER ERROR" в VC++ 6.0
	static int d;

// Запрашиваемый объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_InfoObject, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый объект %u не существует", arg.objID);
	}
	OC_InfoObject oc_info (arg.objID);

// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь право редактирования объекта во всех разделах
	for (d=0; d<oc_info.m_InfoDivID.Size(); d++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByInfoDivID (oc_info.m_InfoDivID[d]), "W");
		if (res!=ERR_OK)
		{
			string feodName="";
			GetFeodFullName (guid(OC_InfoDiv(oc_info.m_InfoDivID[d]).m_MOD_Base_GUID).id, feodName);
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "Пользователь %s не иммеет права редактирования объекта, так как не имеет доступа [W] к разделу '%s'[%u]", arg.Login.c_str(), feodName.c_str(), identifier (oc_info.m_InfoDivID[d]));
		}
	}
//----------------------------------------------------------------------------[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя объекта не должно быть пустым");
	}
// Если не указано время объекта -- ошибка
	if (arg.InfoTime==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Не указано время, приписанное к информационному объекту");
	}
// Проверяем наличие необходимого набора разделов
#if 0  //{ RomanVK
	identifier_arr subDivIDs;
	bool				bFound=false;
	{
	// Хотя бы один раздел должен быть признаковым
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Mark"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть признаковым, т.е. подразделом {Concept.Feod.Data.Mark}");}
	// Хотя бы один раздел должен быть служебным
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Service"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть служебным, т.е. подразделом {Concept.Feod.Data.Service}");}
	// Хотя бы один раздел должен быть тематическим
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть тематическим, т.е. подразделом {Concept.Feod.Data.Topic}");}
	// Хотя бы один раздел должен быть типом информационного материала
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Type"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "Хотя бы один раздел должен быть типовым, т.е. подразделом {Concept.Feod.Data.Type}");}
	}
#endif //}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	guid				loginGUID		=	GetUserGUID (loginID); 
	guid				objGUID			=	oc_info.GetObjectGUID (); 
	time_t			cur_Time			=	time(0);
	string			oldName			=	oc_info.m_Name;
	string			oldText			=	oc_info.m_Text;
	string			oldDescription	=	oc_info.m_Description;
	identifier_arr DivIDsarr;
	string			strDivIDsDel;
	string			strDivIDsAdd;
	identifier_arr info_div_arr	=	oc_info.m_InfoDivID;
	string			stroldnewName;

// Изменяем простые поля объекта
	FULL_INDEX_BEGIN (oc_info);
	{
		oc_info.m_Name				= arg.Name;
		oc_info.m_Description	= arg.Description;
		oc_info.m_Text				= arg.Text;
		oc_info.m_URL				= arg.URL;
		oc_info.m_RelatedLinks	= arg.RelatedLinks;
		oc_info.m_InfoTime		= arg.InfoTime;
		oc_info.m_InfoSourceID	= arg.InfoSourceID;
		oc_info.m_AuthorStr		= arg.AuthorStr;
	}
	FULL_INDEX_END (oc_info);


// Перемещаем объект по разделам:
// arg.divIDs -- к каким разделам, по мнению логина, должен принадлежать объект. 
// Логин не может выкинуть объект из раздела без доступа [D] и добавить в раздел без доступа [C].
	identifier_arr new_div_arr = oc_info.m_InfoDivID;

// Проходимся по разделам объекта и смотрим, какие из них не указаны пользователем, т.е. он решил их выкинуть
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
		if (arg.divIDs.Find(divID)==-1)
		{
		// Пользователь решил, что объект не должен находиться в разделе divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "D")==ERR_OK)
			{
			// Пользователь имеет право выкинуть объект из раздела
				new_div_arr.Del (d);
				d--;
			// Выкидываем объект из раздела
				OC_InfoDiv oc_div (divID);
				int nIndex = oc_div.m_InfoObjectSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_div.m_InfoObjectSortedID.Del (nIndex);
				}
			}
		}
	}

// Проходимся по разделам, указанным пользователем и смотрим, каких из них нет у объекта, т.е. он решил их добавить
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		identifier divID = arg.divIDs[d];
		if (new_div_arr.Find(divID)==-1)
		{
		// Пользователь решил, что объект должен находиться в разделе divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "C")==ERR_OK)
			{
			// Пользователь имеет право добавить объект в раздел
				new_div_arr.Add (divID);
				OC_InfoDiv (divID).m_InfoObjectSortedID.InsertSorted (arg.objID);
			}
		}
	}

// Изменяем принадлежность объекта разделам
	oc_info.m_InfoDivID = new_div_arr;
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// [Sonora] {
// Пополнение лога действий над объектом
// Изменилось значение поля заголовка информационного объекта
	if (oldName!=arg.Name)
	{
	// Пополнение лога пользователя -- заносим в него, что пользователь изменил заголовок
		UserProfileLogUpdate (loginID, USER_LOG_CHANGENAME, objGUID, cur_Time);
		string strChangeName;
		strChangeName.Format	("-%s ",oldName.c_str());
		stroldnewName += strChangeName;
		strChangeName.Format	("+%s ",arg.Name.c_str());
		stroldnewName += strChangeName;


	//	Пополнение лога объекта -- заносим в него, что пользователь изменил заголовок
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGENAME;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	stroldnewName;
	}

// Изменилось значение поля аннотации информационного объекта
	if (oldDescription!=arg.Description)
	{
	// Пополнение лога пользователя -- заносим в него, что пользователь изменил аннотацию
		UserProfileLogUpdate (loginID, USER_LOG_CHANGEDESC, objGUID, cur_Time);

	//	Пополнение лога объекта -- заносим в него, что пользователь изменил аннотацию
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGEDESC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	"";
	}

// Изменилось значение поля текста информационного объекта
	if (oldText!=arg.Text)
	{
	// Пополнение лога пользователя -- заносим в него, что пользователь изменил текст
		UserProfileLogUpdate (loginID, USER_LOG_CHANGETEXT, objGUID, cur_Time);

	//	Пополнение лога объекта -- заносим в него, что пользователь изменил текст
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGETEXT;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	"";
	}

//	Проверяем, стал ли объект опубликованным
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Public",		PUBLIC, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	Проверяем, стал ли объект запрещённым
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Forbidden",	FORBID, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	Проверяем, стал ли объект "горячим материалом", если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Hot",	HOT, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	Проверяем, стал ли объект "обычным материалом", если да, заносим изменения в лог объекта и пользователя
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Regular",	REGULAR, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
	
	InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), DivIDsarr);

// Проходимся по старым разделам и смотрим, какие из них не присутствуют у объекта (только типа "тематики")
	bool	bDelDiv = false;
	for (d=0; d<info_div_arr.Size(); d++)
	{
		identifier divID = info_div_arr[d];
	// Проверяем, выкинул ли пользователь объект из раздела-тематики divID
		if (new_div_arr.Find(divID)==-1 && DivIDsarr.Find(divID)!=-1)
		{
		// Собираем форматированную строку strDivIDsDel из добавленных пользователем тематик
			bDelDiv = true;
			string tmplate;
			tmplate.Format	("-%lu ",divID);
			strDivIDsDel += tmplate;									
		}
	}

// Проходимся по новым разделам-тематикам и смотрим, какие из них раньше не присутствовали у объекта
	bool	bAddDiv = false;
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
	// Проверяем что пользователь добавил в объект раздел-тематику divID
		if (info_div_arr.Find(divID)==-1 && DivIDsarr.Find(divID)!=-1)
		{
		//	Собираем форматированную строку strDivIDsAdd из добавленных пользователем тематик
			bAddDiv	= true;
			string tmplate;
			tmplate.Format	("+%lu ",divID);
			strDivIDsAdd += tmplate;
		}
	}

// Пополнение лога объекта -- заносим в него, добавленные тематики
	if (bAddDiv)
	{
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_ADDTOPIC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	strDivIDsAdd;

	// Пополнение лога пользователя - заносим в него, что пользователь добавил тематики
		UserProfileLogUpdate (loginID, USER_LOG_ADDTOPIC, objGUID, cur_Time);
	}
							  	 
// Пополнение лога объекта -- заносим в него, выкинутые тематики
	if (bDelDiv)
	{
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_DELTOPIC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	strDivIDsDel;

	// Пополнение лога пользователя - заносим в него, что пользователь удалил тематики
		UserProfileLogUpdate (loginID, USER_LOG_DELTOPIC, objGUID, cur_Time);
	}
// [Sonora] }
//----------------------------------------------------------------------------[] 
	
	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]





// !! При удалении объекта выкидывать его из индекса!
//	!! При удалении объекта удалять его прокси-объект (и все связи в семантической сети)
//		DELETE_PROXY_OBJECT_OF (oc_info);








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/