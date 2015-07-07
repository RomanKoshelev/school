/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Site.cpp                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "сайт".                     []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                

#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_Utils
#define USES_BX_TimeStats
#define USES_BX_Site
#define USES_BX_Concept
#define USES_BX_Keyword
#define USES_BX_Events
#define USES_BX_IPRecord
#define USES_BX_VBN
#define USES_BX_Admin

//#define USES_OBServer_Interface_h
#define USES_URL_h
#define USES_OC_SiteStats
#define USES_OC_SuspiciousInfo
#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_Site
#define USES_OC_SiteProfile
#define USES_OC_Keyword
#define USES_OC_Viewer
#define USES_OC_DailyReferrerStats

#include "BX.h"
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_New                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Site_New(BX_Site_Args& arg)
{
	arg.objID = NA;
	
	if (!OC_Exist(OBJ_CLASS_ID_User, arg.OwnerID))
		return BXE_Site_New_InvalidOwnerID;

// Откроем объект владельца сайта:
	OC_User		oc_user;
	oc_user.Open(arg.OwnerID);

// Проверим пароль:
	if ((arg.objPassword != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.objPassword)))
		return BXE_User_AccessDenied;

// Откроем VBN владельца:
	OC_VBN	oc_vbn;
	key_arr	ka;
	ka += (byte)oc_user.m_VBN;
	oc_vbn.SetIndex_No();
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Site_New(): Wrong User::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);


//----------------------------------------------------------------------------[]
// Приведём URL к корректному виду:
	if (arg.URL.Len() > 0) HTTP_URL(arg.URL).URL(arg.URL);

// Проверим валидность профиля (если он передан):
	if ((arg.Profile != NA) && (oc_user.m_SiteProfile.Find(arg.Profile) == -1))
	{
		SERVER_DEBUG_ERROR_2 (
			"BX_Site_New(): Submitted siteprofile (#%lu) doesn't belong to user (#%lu). NA selected.",
			arg.Profile, arg.OwnerID);
		arg.Profile = NA;
	}

// Проверим валидность source-сайта (если он передан):
	if ((arg.objFromID != NA) && (oc_user.m_Site.Find(arg.objFromID) < 0))
	{
		SERVER_DEBUG_ERROR_1 ("BX_Site_New(): INTRUDER ALERT !!! Attempt to copy from an alien Site (#%lu). Creation mode selected.",
			arg.objFromID);
		arg.objFromID = NA;
	}
//----------------------------------------------------------------------------[]
// Вычислим алиас (необходимо делать ДО создания контроллера):
	string	AliasStr;
	OC_Site	oc_other_site;
	oc_other_site.SetIndex_Alias();
	oc_other_site.GoLast();
	if (oc_other_site.IsValid()) {	// Если этот сайт не первый ...
		AliasStr.Format("%d",1+atoi(string(oc_other_site.m_Alias).c_str()));
	}
	else	{									// Первый алиас = 100000.
		AliasStr = string("100000");
	}
	
//----------------------------------------------------------------------------[] 
// Создадим сайт:
	OC_Site		oc_site;
	BX_CREATE_AND_CHECK(oc_site);

	if (arg.objFromID != NA)
	// Режим копирования
	{
	// Откроем source-сайт:
		OC_Site	oc_site_from;
		oc_site_from.Open(arg.objFromID);

	// Скопируем из него нужные параметры:

	// Name
		if (arg.Name.Len() == 0) 	oc_site.m_Name = string("Copy of ") + string(oc_site_from.m_Name);
		else								oc_site.m_Name = arg.Name;

	// URL
		if (arg.URL.Len() == 0) 	oc_site.m_URL = oc_site_from.m_URL;
		else								oc_site.m_URL = arg.URL;

	// Description
		oc_site.m_Description = oc_site_from.m_Description;

	// Keyword
		if (oc_site_from.m_Keyword.Size() > 0)
		{
			identifier_arr	keywordIDs;

		// Преобразовать ID слов source-сайта в строки:
			BX_Keyword_IDToStr(arg.Keyword, oc_site_from.m_Keyword.GetCPtr());
			
		// Добавить ссылки на сайт к новым ключевым словам:
			BX_Keyword_AddSite(arg.Keyword, oc_site.GetObjectID(), oc_vbn.GetObjectID(), keywordIDs);

		// Записать в сайт ссылки на новые ключевые слова:
			oc_site.m_Keyword = keywordIDs;
		}
	
	// Concept
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 02.03.2000 by AlexV
		if (!ba_IsEmpty(oc_site_from.m_ba_Concept.GetCPtr()))
		{
			VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.Concept);
			_BitsToIDs(arg.Concept, oc_site_from.m_ba_Concept);
		// Добавим сайт в списки новых концептов:
			ExpandWithParentConcepts(arg.Concept);
			BX_ASSERT_PASSIVE(
				BX_Concept_AddSite(
					arg.Concept,
					oc_site.GetObjectID(),
					oc_vbn.GetObjectID()));

		// Установим новые концепты у сайта:
			oc_site.m_ba_Concept = oc_site_from.m_ba_Concept.GetCPtr();
		//	ExpandConcept(arg.Concept);	// в arg.Concept теперь expanded-концепты.
			_IDsToBits_Set(arg.Concept, oc_site.m_eba_Concept);
		}


#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *
	// Удалим невалидные и повторяющиеся идентификаторы:
		_BitsToIDs(arg.Concept, oc_site_from.m_ba_Concept);
		VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept,		arg.Concept);

		byte_arr	newConceptBits; //	Массив для битового представления новых концептов
		
	// Получим битовое представление новых концептов:
		_IDsToBits_Set( arg.Concept, newConceptBits);
	// Если новые концепты отличаются от старых ...
		if (bitDiffer(
				newConceptBits.GetPtr(),			newConceptBits.Size(), 
				oc_site.m_ba_Concept.GetPtr(),	oc_site.m_ba_Concept.Size()))
		{
		// Спросим кеш функции BX_Concept_ExtendedEnumerate:
			pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

			identifier_arr	oldConceptArr;		// Массив старых концептов.

		// Получим в массиве oldConceptArr идентификаторы старых концептов:
			_BitsToIDs( oldConceptArr, oc_site.m_ba_Concept);
			ExpandWithParentConcepts(oldConceptArr);
		
			BX_ASSERT_RETURN(
				BX_Concept_DeleteSite(
					oldConceptArr,
					arg.objID,
					oc_vbn.GetObjectID()));
		//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

		// Установим новое явное распределение концептов сайта:
			int_arr	CRN_Self;
			BX_Concept_GetPackedWeights (arg.Concept, CRN_Self);
			NormalizePackedArrInplace (CRN_Self);

			oc_site.m_CRN_Self.CopyFrom(CRN_Self.GetPtr(), CRN_Self.GetSize());

		// Пересчитаем поле CRN_VisitorIncr = CRN_Self+(CRN_Visitor-CRN_InetAudience)
			int_arr	CRN_VisitorIncr;
			PackedArrNormalizedDiff(CRN_VisitorIncr,
											oc_site.m_CRN_Visitor.GetCPtr(),
											oc_reg.m_CRN_InetAudience.GetCPtr());
			PackedArrIncrement(CRN_VisitorIncr, CRN_Self);
			NormalizePackedArrInplace(CRN_VisitorIncr);

			oc_site.m_CRN_VisitorIncr.CopyFrom(CRN_VisitorIncr.GetPtr(), CRN_VisitorIncr.GetSize());
		//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
		// Добавим сайт в списки новых концептов:
			oldConceptArr	= arg.Concept;	// сохраним для eba_Concept...
			ExpandWithParentConcepts(arg.Concept);	// Добавим родителей...

			BX_ASSERT_RETURN(
				BX_Concept_AddSite(
					arg.Concept,		// В arg.Concept -- вместе с родителями.
					arg.objID,
					oc_vbn.GetObjectID()));

		// Установим новые концепты у сайта:
			oc_site.m_ba_Concept		= newConceptBits;						// ba_Concept
			_IDsToBits_Set	(arg.Concept, oc_site.m_pba_Concept);		// pba_Concept
			ExpandConcept	(oldConceptArr);	// Добавим детей.
			_IDsToBits_Set	(oldConceptArr, oc_site.m_eba_Concept);	// eba_Concept

		} //end if новые концепты отличаются от старых 

	// CounterType
		oc_site.m_CounterType				= oc_site_from.m_CounterType;

	// MirrorInclude
		oc_site.m_MirrorInclude				= oc_site_from.m_MirrorInclude.GetCPtr();
	// MirrorExclude
		oc_site.m_MirrorExclude				= oc_site_from.m_MirrorExclude.GetCPtr();
	// MirrorSubstr
		oc_site.m_MirrorSubstr				= oc_site_from.m_MirrorSubstr.GetCPtr();
	// IgnoredIP
		oc_site.m_IgnoredIP					= oc_site_from.m_IgnoredIP.GetCPtr();

	// Profile
		arg.Profile								= oc_site_from.m_Profile;

	// RateMySite
		oc_site.m_RateMySite					= oc_site_from.m_RateMySite;
	// RateStatsViewPassword
		oc_site.m_RateStatsViewPassword	= oc_site_from.m_RateStatsViewPassword;
	// ShowAudience
		oc_site.m_ShowAudience				= oc_site_from.m_ShowAudience;
	// ShowAudienceOffTime
		oc_site.m_ShowAudienceOffTime		= oc_site_from.m_ShowAudienceOffTime;

	}
//----------------------------------------------------------------------------[]
	else
// Режим создания:
	{
	// Name
		if (arg.Name.Len() == 0) {
		oc_site.m_Name				= string("No name: ") + arg.URL;
		}
		else	{
			oc_site.m_Name = arg.Name;
		}

	// Description
		oc_site.m_Description	= "";

	// URL
		oc_site.m_URL				= arg.URL;

	// MirrorSubstr
		oc_site.m_MirrorSubstr.Add("www1");
		oc_site.m_MirrorSubstr.Add("www2");
		oc_site.m_MirrorSubstr.Add("www3");
		oc_site.m_MirrorSubstr.Add("win");
		oc_site.m_MirrorSubstr.Add("koi");
		oc_site.m_MirrorSubstr.Add("mac");

	}
//----------------------------------------------------------------------------[]
// Алиас:
	oc_site.m_Alias			= AliasStr;

// OwnerID	
	oc_site.m_OwnerID			= arg.OwnerID;

// VBN
	oc_site.m_VBN				= oc_user.m_VBN;

// CreationTime
	oc_site.m_CreationTime	= time_0;

// Profile
	// Если профиль не валидный, то поставим NA:
		if ((arg.Profile != NA) && !OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.Profile))
		{
			SERVER_DEBUG_ERROR_1 ("BX_Site_New(): Submitted siteprofile (#%lu) is invalid.", arg.Profile);
			arg.Profile		= NA;
		}

	// Если профиль не передали, то поставим первый профиль владельца (если он есть):
		if (arg.Profile == NA)
		{
			if (oc_user.m_SiteProfile.Size() > 0) {
				if (OC_Exist(OBJ_CLASS_ID_SiteProfile, oc_user.m_SiteProfile[0])) {
					arg.Profile = oc_user.m_SiteProfile[0];
				}
				else {
					SERVER_DEBUG_ERROR_1 ("BX_Site_New(): Invalid User::SiteProfile[0] = #%lu.", identifier(oc_user.m_SiteProfile[0]));
				}
			}
		}
	// Установка профиля:
		if (arg.Profile != NA)
		{
		// Пропишем профиль у сайта:
			oc_site.m_Profile		= arg.Profile;
		// Пропишем сайт у профиля:
			OC_SiteProfile	oc_site_profile;
			oc_site_profile.Open(arg.Profile);
			oc_site_profile.m_Site.Add(oc_site.GetObjectID());
		}
	// Если профиля не передали или у владельца нет профилей, то поставим NA:
		else {
			oc_site.m_Profile		= NA;
		}

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]

// Добавим к пользователю ссылку на созданный сайт:
	oc_user.m_Site.Add(oc_site.GetObjectID());

// Создадим объект подозрительных событий на сайте:
	OC_SuspiciousInfo		oc_suspicious_info;
	BX_CREATE_AND_CHECK(oc_suspicious_info);

	oc_suspicious_info.m_Site	= oc_site.GetObjectID();
	oc_site.m_SuspiciousInfo	= oc_suspicious_info.GetObjectID();

// Инициализируем статистику рефереров:
//	BX_ASSERT_PASSIVE(BX_Site_InitDailyReferrerStats(oc_site, &CurrentTime)); -- инициализируется в Counter_GetData когда нужно.

// Установим информацию для модератора:
	oc_site.m_Allowed			= !bool(oc_vbn.m_IsModerated);
	oc_site.m_ObjectState	= OBJ_STATE_NEW; // новый

// Возвратим идентификатор созданного сайта:	
	arg.objID = oc_site.GetObjectID();

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_GetData                                                           []               
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Site_GetData(BX_Site_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_Site_GetData_InvalidSiteID;

// Открыть объект сайта:
	OC_Site	oc_site;
	oc_site.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if ((arg.objPassword != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.objPassword)))
		return BXE_User_AccessDenied;
	
//----------------------------------------------------------------------------[] 
// OwnerID
	arg.OwnerID			= oc_site.m_OwnerID;

// VBN
	arg.VBN				= (byte)oc_site.m_VBN;

// CreationTime, sCreationTime
	time_t	createTime
							= (time_t)(oc_site.m_CreationTime + oc_user.m_TZOffset);
	
	arg.CreationTime	= createTime;
	arg.sCreationTime.Format("%s", asctime(gmtime(&createTime)));

// Alias
	arg.Alias			= oc_site.m_Alias;

// Name
	arg.Name				= oc_site.m_Name;

// Description
	arg.Description	= oc_site.m_Description;

// URL
	arg.URL				= oc_site.m_URL;

// CounterType
	arg.CounterType	= oc_site.m_CounterType;

// RateMySite
	arg.RateMySite		= (bool)oc_site.m_RateMySite;

// RateStatsViewPassword
	arg.RateStatsViewPassword
							= oc_site.m_RateStatsViewPassword;
// ShowAudience
	arg.ShowAudience	= (bool)oc_site.m_ShowAudience;
// ShowAudienceOffTime
	arg.ShowAudienceOffTime
							= oc_site.m_ShowAudienceOffTime;
// Profile
	arg.Profile			= oc_site.m_Profile;

// Keyword
	arg.Keyword.Delete();
	OC_Keyword	oc_keyword;
	for (int i = 0; i < oc_site.m_Keyword.Size(); i++)
	{
		BX_CHECK_AND_OPEN(oc_keyword, oc_site.m_Keyword[i], OBJ_CLASS_ID_Keyword);
		arg.Keyword.Add(oc_keyword.m_Word);
	}

// MirrorInclude
	arg.MirrorInclude = oc_site.m_MirrorInclude;

// MirrorExclude
	arg.MirrorExclude = oc_site.m_MirrorExclude;

// MirrorSubstr
	arg.MirrorSubstr = oc_site.m_MirrorSubstr;

// IgnoredIP
	arg.IgnoredIP		= oc_site.m_IgnoredIP;

// IgnoredViewerID
	arg.IgnoredViewerID= oc_site.m_IgnoredViewerID;

// Concept
	_BitsToIDs( arg.Concept, oc_site.m_ba_Concept);

// Page
	arg.PageName		= oc_site.m_PageName.GetCPtr();
	
// PageNo
	arg.PageNo			= oc_site.m_PageNo.GetCPtr();

// AdBannerProfile
	arg.AdBannerProfile
							= oc_site.m_AdBannerProfile;
// SuspiciousInfo
	arg.SuspiciousInfo
							= oc_site.m_SuspiciousInfo;
// Allowed
	arg.Allowed			= (bool)oc_site.m_Allowed;

// ObjectState
	arg.ObjectState	= oc_site.m_ObjectState;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_PutData                                                           []               
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Site_PutData(BX_Site_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_Site_PutData_InvalidSiteID;

	int			i;

	OC_Site		oc_site;
	oc_site.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if ((arg.objPassword != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.objPassword)))
		return BXE_User_AccessDenied;

// Проверить наличие профиля у пользователя:
	if (arg.Profile != NA)
	{
		if (oc_user.m_SiteProfile.Find(arg.Profile) < 0)
			return BXE_Site_PutData_ProfileAccessDenied;
	}

// Открыть VBN сайта:
	OC_VBN	oc_vbn;
	oc_vbn.SetIndex_No();
	key_arr	ka;
	ka += (byte)oc_site.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Site_PutData(): Wrong Site::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

//----------------------------------------------------------------------------[] 
// Копирование полей

// Alias
	if (arg.Alias.Len() > 0) {
		oc_site.m_Alias			= arg.Alias;
	}
/*	else	{
		SERVER_DEBUG_ERROR ("BX_Site_PutData(): Empty alias. Skipped...");
	}
*/

// Name
	oc_site.m_Name				= arg.Name;

// Description
	oc_site.m_Description	= arg.Description;

// URL
	VALIDATE_URL(arg.URL);
	oc_site.m_URL				= arg.URL;

// CounterType
	oc_site.m_CounterType	= arg.CounterType;
	
// RateMySite
	oc_site.m_RateMySite		= arg.RateMySite;

// RateStatsViewPassword
	oc_site.m_RateStatsViewPassword
									= arg.RateStatsViewPassword;
// ShowAudience
	oc_site.m_ShowAudience
									= arg.ShowAudience;
// ShowAudienceOffTime
	if (arg.ShowAudience == false) {
		oc_site.m_ShowAudienceOffTime = time_0;
	}
		
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
// Profile
		if (OC_Exist(OBJ_CLASS_ID_SiteProfile, arg.Profile))	{
			oc_site.m_Profile = arg.Profile;
		}

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
// Keyword
	// Удалить ссылки на сайт в старых ключевых словах:
		BX_Keyword_DeleteSite(oc_site.m_Keyword.GetCPtr(), oc_site.GetObjectID(), oc_vbn.GetObjectID());

		identifier_arr	keywordIDs;

	// Перевести ключевые слова в верхний регистр:
		for (i = 0; i < arg.Keyword.Size(); i++) {
			arg.Keyword[i].strupr();
		}

	// Добавить ссылки на сайт к новым ключевым словам:
		BX_Keyword_AddSite(arg.Keyword, oc_site.GetObjectID(), oc_vbn.GetObjectID(), keywordIDs);

	// Записать в сайт ссылки на новые ключевые слова:
		oc_site.m_Keyword = keywordIDs;

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]

// MirrorInclude
	for (i=0; i<arg.MirrorInclude.GetSize(); i++) VALIDATE_URL(arg.MirrorInclude[i]);
	oc_site.m_MirrorInclude	= arg.MirrorInclude;

// MirrorExclude
	for (i=0; i<arg.MirrorExclude.GetSize(); i++) VALIDATE_URL(arg.MirrorExclude[i]);
	oc_site.m_MirrorExclude	= arg.MirrorExclude;

// MirrorSubstr
	oc_site.m_MirrorSubstr	= arg.MirrorSubstr;

// IgnoredIP
	oc_site.m_IgnoredIP.Erase();
	for (i = 0; i < arg.IgnoredIP.Size(); i++) {
		oc_site.m_IgnoredIP.Add(string((IP_Address(arg.IgnoredIP[i])).GetIP()));
	}
// IgnoredViewerID
	oc_site.m_IgnoredViewerID.Erase();
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Viewer, arg.IgnoredViewerID);
	for (i = 0; i < arg.IgnoredViewerID.Size(); i++) {
		oc_site.m_IgnoredViewerID.InsertSorted(arg.IgnoredViewerID[i]);
	}
//----------------------------------------------------------------------------[] 
// Concept

// Удалим невалидные и повторяющиеся идентификаторы:
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept,		arg.Concept);

	byte_arr	newConceptBits; //	Массив для битового представления новых концептов
	
// Получим битовое представление новых концептов:
	_IDsToBits_Set( arg.Concept, newConceptBits);

// Если новые концепты отличаются от старых ...
	if (bitDiffer(
			newConceptBits.GetPtr(),			newConceptBits.Size(), 
			oc_site.m_ba_Concept.GetPtr(),	oc_site.m_ba_Concept.Size()))
	{
	// Спросим кеш функции BX_Concept_ExtendedEnumerate:
		pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

		identifier_arr	oldConceptArr;		// Массив старых концептов.

	// Получим в массиве oldConceptArr идентификаторы старых концептов:
		_BitsToIDs( oldConceptArr, oc_site.m_ba_Concept);
		ExpandWithParentConcepts(oldConceptArr);
	
		BX_ASSERT_RETURN(
			BX_Concept_DeleteSite(
				oldConceptArr,
				arg.objID,
				oc_vbn.GetObjectID()));
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	// Установим новое явное распределение концептов сайта:
		int_arr	CRN_Self;
		BX_Concept_GetPackedWeights (arg.Concept, CRN_Self);
		NormalizePackedArrInplace (CRN_Self);

		oc_site.m_CRN_Self.CopyFrom(CRN_Self.GetPtr(), CRN_Self.GetSize());

	// Пересчитаем поле CRN_VisitorIncr = CRN_Self+(CRN_Visitor-CRN_InetAudience)
		int_arr	CRN_VisitorIncr;
		PackedArrNormalizedDiff(CRN_VisitorIncr,
										oc_site.m_CRN_Visitor.GetCPtr(),
										oc_reg.m_CRN_InetAudience.GetCPtr());
		PackedArrIncrement(CRN_VisitorIncr, CRN_Self);
		NormalizePackedArrInplace(CRN_VisitorIncr);

		oc_site.m_CRN_VisitorIncr.CopyFrom(CRN_VisitorIncr.GetPtr(), CRN_VisitorIncr.GetSize());
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Добавим сайт в списки новых концептов:
		oldConceptArr	= arg.Concept;	// сохраним для eba_Concept...
		ExpandWithParentConcepts(arg.Concept);	// Добавим родителей...

		BX_ASSERT_RETURN(
			BX_Concept_AddSite(
				arg.Concept,		// В arg.Concept -- вместе с родителями.
				arg.objID,
				oc_vbn.GetObjectID()));

	// Установим новые концепты у сайта:
		oc_site.m_ba_Concept		= newConceptBits;						// ba_Concept
		_IDsToBits_Set	(arg.Concept, oc_site.m_pba_Concept);		// pba_Concept
		ExpandConcept	(oldConceptArr);	// Добавим детей.
		_IDsToBits_Set	(oldConceptArr, oc_site.m_eba_Concept);	// eba_Concept

	} //end if новые концепты отличаются от старых 

//----------------------------------------------------------------------------[] 
// Page, PageNo
	if (oc_site.m_PageName.Size() == arg.PageName.Size())	{
		oc_site.m_PageName			= arg.PageName;
	}

// Установим признак изменения объекта:
	oc_site.m_ObjectState	= OBJ_STATE_CHANGED;

	return BX_OK;
}	
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_Delete                                                            []              
[]                                                                            []
[]____________________________________________________________________________[]
*/
#define LAST_COUNTER_DELETE(counterName)													\
	timestats_args.idCounter = oc_site.m_##counterName;								\
	BX_ASSERT_PASSIVE(BX_TimeStats_Delete(timestats_args));							\
	oc_site.m_##counterName = timestats_args.idCounter

BX_RESULT
BX_Site_Delete(BX_Site_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_Site_Delete_InvalidSiteID;

	int i;

// Откроем удаляемый сайт:
	OC_Site		oc_site;
	oc_site.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User		oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if ((arg.objPassword != string(oc_user.m_Password)) &&  (!CheckAdminPassword(arg.objPassword)))
		return BXE_User_AccessDenied;

// Открыть VBN сайта:
	OC_VBN	oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr	ka;
	ka += (byte)oc_site.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Site_Delete(): Wrong Site::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);
	
//----------------------------------------------------------------------------[] 

// Удалим ссылку на сайт у пользователя:
	DELETE_FROM_ARRAY(oc_user.m_Site, arg.objID);

// Удалим ссылку на сайт в профиле:
	if (oc_site.m_Profile != NA)
	{
		OC_SiteProfile	oc_site_profile;
		BX_CHECK_AND_OPEN(oc_site_profile, oc_site.m_Profile, OBJ_CLASS_ID_SiteProfile);

		DELETE_FROM_ARRAY(oc_site_profile.m_Site, arg.objID);
	}

// Удалим сайт из списка cайтов у концептов:
	if (!ba_IsEmpty(oc_site.m_ba_Concept))
	{
		identifier_arr		conceptIDs;
	// Получим ID концептов сайта в массиве conceptIDs:
		_BitsToIDs( conceptIDs, oc_site.m_ba_Concept);
		ExpandWithParentConcepts(conceptIDs);
	// Удалим ссылки на сайт из концептов профиля:
		BX_ASSERT_RETURN(
			BX_Concept_DeleteSite(
				conceptIDs,
				arg.objID,
				oc_vbn.GetObjectID()
				));
	}

// !!!Удалить ссылку на сайт у зрителей ?

// Удалить ссылку на сайт у баннеров:
	for (i = 0; i < oc_site.m_AdBannerProfile.Size(); i++)
	{
		OC_BannerProfile	oc_banner_profile;
		BX_CHECK_AND_OPEN(oc_banner_profile, oc_site.m_AdBannerProfile[i], OBJ_CLASS_ID_BannerProfile);
		
		SERVER_DEBUG_ASSERT_RETURN(
			oc_banner_profile.m_HREF == oc_site.GetObjectID(),
			"BX_Site_Delete(): BannerProfile::HREF != Site::AdBannerProfile[i].",
			BX_SYSTEM_ERROR);

		oc_banner_profile.m_HREF = NA;
	}

// Удалить ссылку на сайт в ключевых словах:
	if (oc_site.m_Keyword.Size() > 0) {
		BX_Keyword_DeleteSite(oc_site.m_Keyword.GetCPtr(), oc_site.GetObjectID(), oc_vbn.GetObjectID());
	}

//----------------------------------------------------------------------------[] 
// Удаление статистики:

// Удалим объект подозрительных событий на сайте:
	if (OC_Exist(OBJ_CLASS_ID_SuspiciousInfo, oc_site.m_SuspiciousInfo))
	{
		OC_SuspiciousInfo		oc_suspicious_info;
		oc_suspicious_info.Delete(oc_site.m_SuspiciousInfo);
		oc_site.m_SuspiciousInfo = NA;
	}
	else
	{
		SERVER_DEBUG_ERROR ("BX_Site_Delete(): Invalid Site::SuspiciousInfo !");
	}

// Удалим статистику реферерров:
	OC_DailyReferrerStats	oc_daily_ref_stats;
	for (i = 0; i < oc_site.m_DailyReferrerStats.Size(); i++)
	{
		if (OC_Exist(OBJ_CLASS_ID_DailyReferrerStats, oc_site.m_DailyReferrerStats[i])) {
			oc_daily_ref_stats.Delete(oc_site.m_DailyReferrerStats[i]);
		}
	}
// Удалим счетчики:
	BX_TimeStats_Args	timestats_args;

	LAST_COUNTER_DELETE(Loads					);
	LAST_COUNTER_DELETE(Visitors				);
	LAST_COUNTER_DELETE(Hosts					);
	LAST_COUNTER_DELETE(Shows					);
	LAST_COUNTER_DELETE(Clicks					);
	LAST_COUNTER_DELETE(Clicks_Local			);
	LAST_COUNTER_DELETE(Hits					);
	LAST_COUNTER_DELETE(Hits_Local			);
	LAST_COUNTER_DELETE(AnonymousHits		);
	LAST_COUNTER_DELETE(SuspiciousHits		);
	LAST_COUNTER_DELETE(SessionTime			);
	LAST_COUNTER_DELETE(SessionTime_Local	);
	LAST_COUNTER_DELETE(SessionNum			);
	
// Удаляем сайт:
	oc_site.Delete();

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_GetCounterType                                                    []                      
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT BX_Site_GetCounterType(BX_Site_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_Site_GetCounterType_InvalidSiteID;

// Откроем сайт:
	OC_Site		oc_site;
	oc_site.Open(arg.objID);

// Вернем тип счетчика:
	arg.CounterType = (int)oc_site.m_CounterType;

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_SiteSuspiciousInfo_GetData                                             []                             
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_SiteSuspiciousInfo_GetData(BX_SiteSuspiciousInfo_Args& arg)
{
// Очистка выходных аргументов:
	arg.sEventType.Delete();
	arg.sTime.		Delete();
	arg.Viewer.		Delete();
	arg.IP.			Delete();
	arg.Referrer.	Delete();

// Проверка валидности идентификатора сайта:
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_SiteSuspiciousInfo_GetData_InvalidSiteID;

// Откроем сайт:
	OC_Site		oc_site;
	oc_site.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User		oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if ((arg.objPassword != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.objPassword)))
		return BXE_User_AccessDenied;

// Открыть объект статистики подозрительных событий:
	OC_SuspiciousInfo	oc_suspicious_info;
	BX_CHECK_AND_OPEN(oc_suspicious_info, oc_site.m_SuspiciousInfo, OBJ_CLASS_ID_SuspiciousInfo);

// Скопировать информацию в выходные аргументы:
	oc_suspicious_info.m_Referrer.CopyTo(arg.Referrer);

	OC_Viewer	oc_viewer;

	for (int i = 0; i < oc_suspicious_info.m_Viewer.Size(); i++)
	{
		switch(int(oc_suspicious_info.m_EventType[i]))
		{
			case CNTR_WOUND:				arg.sEventType.Add("Накрутка");	break;
			case CNTR_WRONG_MIRROR:		arg.sEventType.Add("Зеркало");	break;
			case CNTR_WRONG_IP:			arg.sEventType.Add("IP-адрес");	break;
			case CNTR_MODERATOR:			arg.sEventType.Add("Модератор"); break;
			case CNTR_INVALID_COOKIE:	arg.sEventType.Add("Cookie");		break;
			default:							arg.sEventType.Add("Undefined");		
		}
		
		time_t	createTime =	(time_t)(oc_suspicious_info.m_Time[i] + oc_user.m_TZOffset);
	
		arg.sTime.Add(string(asctime(gmtime(&createTime))));

		if (OC_Exist(OBJ_CLASS_ID_Viewer, oc_suspicious_info.m_Viewer[i]))
		{
			oc_viewer.Open(oc_suspicious_info.m_Viewer[i]);

			arg.Viewer.Add(oc_suspicious_info.m_Viewer[i]);
			arg.IP.Add(oc_viewer.m_IPAddress);
		}
		else
		{
			oc_suspicious_info.m_Viewer[i] = NA;

			arg.Viewer.Add(NA);
			arg.IP.Add("NA");
		}
	}

	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_Site_Enumerate                                                         []                 
//                                                                            []
BX_RESULT BX_Site_Enumerate(BX_Site_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_Site			oc_object;
	identifier_arr	IDs;

	oc_object.GetClassIdList(IDs);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<IDs.Size()); i++)
	{
		oc_object.Open(IDs[i]);
		arg.objIDs.Add(IDs[i]);
		arg.objNames.Add(oc_object.m_Name);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_Site_GetAudienceIntersect                                              []                            
//                                                                            []
BX_RESULT BX_Site_GetAudienceIntersect(BX_Site_Args& arg)
{
// Очистка выходных аргументов:
	arg.Audience_SiteID	.Erase();
	arg.Audience_SiteName.Erase();
	arg.Audience_Viewers	.Erase();	
	arg.Audience_Hosts	.Erase();	

// Проверка валидности идентификатора сайта:
	if (!OC_Exist(OBJ_CLASS_ID_Site, arg.objID))
		return BXE_Site_GetAudienceIntersect_InvalidSiteID;

// Откроем сайт:
	OC_Site		oc_site;
	oc_site.Open(arg.objID);

	OC_Site		oc_othersite;
	int			i;
	int			nPos;
	for (i = 0; i < oc_site.m_Audience_SiteID.Size(); i++)
	{
		if (!OC_Exist(OBJ_CLASS_ID_Site, oc_site.m_Audience_SiteID[i]))
		{
			oc_site.m_Audience_SiteID.Del(i);
			oc_site.m_Audience_Viewers.Del(i);
			oc_site.m_Audience_Hosts.Del(i);
			i--;
			continue;
		}

		oc_othersite.Open(oc_site.m_Audience_SiteID[i]);

		nPos = arg.Audience_Hosts.	InsertSorted(oc_site.m_Audience_Hosts[i]);
		arg.Audience_SiteID.			Insert(nPos, oc_site.m_Audience_SiteID[i]);
		arg.Audience_SiteName.		Insert(nPos, oc_othersite.m_Name);
		arg.Audience_Viewers.		Insert(nPos, oc_site.m_Audience_Viewers[i]);
	}
	
	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_GetStatsPassword                                                  []                        
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Site_GetStatsPassword(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);

	arg.RateStatsViewPassword = oc_site.m_RateStatsViewPassword;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_CheckStatsPassword                                                []                          
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Site_CheckStatsPassword(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);

	OC_User		oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

	if (CheckAdminPassword(arg.OwnerPassword)) {
		arg.ExitCode = true;
		return BX_OK;
	}

	if (arg.OwnerPassword == string(oc_user.m_Password)) {
		arg.ExitCode = true;
		return BX_OK;
	}

	if (arg.StatsPassword == string(oc_site.m_RateStatsViewPassword)) {
		arg.ExitCode = true;
		return BX_OK;
	}

	arg.ExitCode = false;
	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_GetVBN                                                            []              
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Site_GetVBN(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);

// Открыть VBN сайта:
	OC_VBN	oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr	ka;
	ka += (byte)oc_site.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_Site_GetVBN(): Wrong Site::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

	arg.VBN = oc_vbn.GetObjectID();

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_GetBriefInfo                                                      []                    
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT BX_Site_GetBriefInfo(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);

	arg.Name				= oc_site.m_Name;
	arg.Description	= oc_site.m_Description;
	arg.CreationTime	= oc_site.m_CreationTime;
	arg.URL				= oc_site.m_URL;

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_Site_GetAliasByID                                                      []                    
//                                                                            []
BX_RESULT
BX_Site_GetAliasByID(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);
	arg.Alias			= oc_site.m_Alias;
	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_Site_GetIDByAlias                                                      []                    
//                                                                            []
BX_RESULT
BX_Site_GetIDByAlias(BX_Site_Args& arg)
{
	OC_Site		oc_site;
	oc_site.SetIndex_Alias();
	key_arr		ka;
	ka += arg.Alias;

	if (oc_site.Find(ka)) {
		arg.objID	= oc_site.GetObjectID();
	}
	else	{
		arg.objID	= NA;
	}

	return BX_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Site_InitDailyReferrerStats                                            []                              
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Site_InitDailyReferrerStats(OC_Site &oc_site, const time_t	*timer)
{
	if (!oc_site.IsValid()) {
		SERVER_DEBUG_ERROR ("BX_Site_InitDailyReferrerStats(): Invalid site controller. Aborting...");
		return BX_SYSTEM_ERROR;
	}

	if (oc_reg.m_DailyReferrerSize < 1)
	{
		SERVER_DEBUG_ERROR_1 ("BX_Site_InitDailyReferrerStats(): Registry DailyReferrerSize = %d. Forced to 0.", (int)oc_reg.m_DailyReferrerSize);
		oc_reg.m_DailyReferrerSize = 0;
	}

	OC_DailyReferrerStats	oc_daily_ref_stats;
	int							i;

// Удалить контроллеры (если они есть):
	for (i = 0; i < oc_site.m_DailyReferrerStats.Size(); i++)
	{
		if (OC_Exist(OBJ_CLASS_ID_DailyReferrerStats, oc_site.m_DailyReferrerStats[i])) {
			oc_daily_ref_stats.Delete(oc_site.m_DailyReferrerStats[i]);
		}
	}

// Установить заданный размер массивов:
	oc_site.m_DailyReferrerStats.		Alloc(oc_reg.m_DailyReferrerSize, NA);
	oc_site.m_DailyReferrerTimeStamp.Alloc(oc_reg.m_DailyReferrerSize, 0);

// Узнать, во сколько была сегодня полночь:
	tm			*pMidTimetruct = gmtime(timer);
	tm			MidTimetruct;
	SERVER_DEBUG_ASSERT_RETURN(
		pMidTimetruct != NULL,
		"BX_Site_InitDailyReferrerStats(): Error calling to localtime(). Aborted.",
		BX_SYSTEM_ERROR);
	memcpy(&MidTimetruct, pMidTimetruct, sizeof (tm));
	MidTimetruct.tm_hour = 0;	// 00:00.00 - полночь.
	MidTimetruct.tm_min	= 0;
	MidTimetruct.tm_sec	= 0;

	time_t	MidnightTime = mktime(&MidTimetruct);
	SERVER_DEBUG_ASSERT_RETURN(
		MidnightTime != -1,
		"BX_Site_InitDailyReferrerStats(): Error calling to mktime(). Aborted.",
		BX_SYSTEM_ERROR);
	
// Установить TimeStamp'ы:
	for (i = 0; i < oc_reg.m_DailyReferrerSize; i++)
	{
		oc_site.m_DailyReferrerTimeStamp[i] = 
			MidnightTime - (oc_reg.m_DailyReferrerSize-1-i)*SECS_IN_DAY;
	}

	return BX_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/
