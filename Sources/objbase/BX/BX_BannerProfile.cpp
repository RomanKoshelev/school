/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_BannerProfile.cpp                                      []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "профиль баннера".          []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                         

#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_BannerProfile
#define USES_BX_Macros
#define USES_BX_Concept
#define USES_BX_Utils
#define USES_BX_VBN

#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_Site
#define USES_OC_BannerProfile

#include "BX.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_BannerProfile_New                                                      []                    
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_BannerProfile_New(BX_BannerProfile_Args& arg)
{
	arg.objID = NA;

	if (!OC_Exist(OBJ_CLASS_ID_User, arg.OwnerID))
		return BXE_BannerProfile_New_InvalidUserID;
	if ((arg.objFromID != NA) && !OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objFromID))
	{
		SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_New(): Attempt to copy from an invalid BannerProfile (#%lu). Creation mode selected.",
			arg.objFromID);
		arg.objFromID = NA;
	}

// Открыть объект пользователя-владельца:
	OC_User				oc_user;
	oc_user.Open(arg.OwnerID);

// Проверить пароль:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;
//----------------------------------------------------------------------------[] 
// Проверить, не хотят ли враги скопировать из чужого профиля:
	if ((arg.objFromID != NA) && (oc_user.m_BannerProfile.Find(arg.objFromID) < 0))
	{
		SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_New(): INTRUDER ALERT !!! Attempt to copy from an alien BannerProfile (#%lu). Creation mode selected.",
			arg.objFromID);
		arg.objFromID = NA;
	}

// Создать профиль:
	OC_BannerProfile	oc_banner_profile;
	BX_CREATE_AND_CHECK(oc_banner_profile);

// Добавить ссылку на профиль к пользователю:
	oc_user.m_BannerProfile.Add(oc_banner_profile.GetObjectID());

	if (arg.objFromID != NA)
	{
	// Режим копирования
		OC_BannerProfile		oc_banner_profile_from;
		oc_banner_profile_from.Open(arg.objFromID);

		oc_banner_profile.CopyDataFrom(oc_banner_profile_from);

	// Некоторые поля менять нельзя:
		if (arg.Name.Length() == 0) {
			oc_banner_profile.m_Name = string("Copy of ") + string(oc_banner_profile_from.m_Name);
		}

		oc_banner_profile.m_HREF				= NA;
		oc_banner_profile.m_Banner.Delete();
		oc_banner_profile.m_MaxDailyShowsChangeTime
														= time_0;
		oc_banner_profile.m_TotalShows		= 0;
		oc_banner_profile.m_TotalClicks		= 0;
		oc_banner_profile.m_SessionEvents	= 0;
		oc_banner_profile.m_Priority			= oc_reg.m_DefaultPriority;
	}
	else
// Режим создания:
	{
	// Сделаем название, если надо:
		if (arg.Name.Length() == 0)
		{
			time_t	curtime = time_0 + (time_t)oc_user.m_TZOffset;
			arg.Name.Format("New profile (%s)", 
				asctime( gmtime(&curtime) ) );
		}
	// MaxDailyShows	
		oc_banner_profile.m_MaxDailyShows	= 1000;
	// MaxDailyClicks
		oc_banner_profile.m_MaxDailyClicks	= 1000;
	// Положим в SiteExclude сайты пользователя:
		identifier_arr UserSites;
		UserSites = oc_user.m_Site.GetCPtr();
		UserSites.Sort();
		VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Site, UserSites); 
		oc_banner_profile.m_SiteExclude = UserSites;

	// Разберёмся с HREF:
		if (arg.HREF != NA)
		{
			if (OC_Exist(arg.HREF, OBJ_CLASS_ID_Site))
			{
				if (oc_user.m_Site.Find(arg.HREF) != -1)
				{
				// Откроем сайт:
					OC_Site	oc_site;
					oc_site.Open(arg.HREF);
				// Проверка на дублирование:
					if (oc_site.m_AdBannerProfile.Find(arg.HREF) != -1) {
						SERVER_DEBUG_ERROR ("BX_BannerProfile_New(): Double HREF in Site::AdBannerProfile.");
						oc_site.m_AdBannerProfile.Del(oc_site.m_AdBannerProfile.Find(arg.HREF));
					}
				// Добавим новый профиль к сайту:
					oc_site.m_AdBannerProfile.Add(oc_banner_profile.GetObjectID());

				// Установить ссылку на сайт у профиля баннера:
					oc_banner_profile.m_HREF	= arg.HREF;
				}
				else {
					SERVER_DEBUG_ERROR_2 ("BX_BannerProfile_New(): Attempt to assign an alien site (#%lu) as a HREF to the new banner profile (#%lu).", arg.HREF, oc_banner_profile.GetObjectID());
				}
			}
			else {
				SERVER_DEBUG_ERROR_2 ("BX_BannerProfile_New(): Attempt to assign invalid site (#%lu) as a HREF to the new banner profile (#%lu).", arg.HREF, oc_banner_profile.GetObjectID());
			}
				
		}
		else {
			oc_banner_profile.m_HREF	= NA;
		}

	} // end режим создания

// Установить название:	
	oc_banner_profile.m_Name	= arg.Name;

// Владельца профиля менять нельзя:
	oc_banner_profile.m_OwnerID = arg.OwnerID;

// Номер сетки менять нельзя:
	oc_banner_profile.m_VBN = oc_user.m_VBN;

// Установим время модификации:
	oc_banner_profile.m_LastModified = time_0;

// Установим информацию для модератора:
	OC_VBN		oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr		ka;
	ka += (byte)oc_banner_profile.m_VBN;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_BannerProfile_New(): Incorrect BannerProfile::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

	oc_banner_profile.m_Allowed		= !bool(oc_vbn.m_IsModerated);
	oc_banner_profile.m_ObjectState	= OBJ_STATE_NEW; // новый

// Возвратим идентификатор созданного профиля:	
	arg.objID = oc_banner_profile.GetObjectID();

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_BannerProfile_CopyData                                                 []                         
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_BannerProfile_CopyData(BX_BannerProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objID))
		return BXE_BannerProfile_CopyData_InvalidProfileID;
	if (!OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objFromID))
		return BXE_BannerProfile_CopyData_InvalidProfileID;

// Открыть профиль, в который будем копировать:
	OC_BannerProfile		oc_banner_profile;
	oc_banner_profile.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User				oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner_profile.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// Проверить, есть ли target-профиль у пользователя:
	if (oc_user.m_BannerProfile.Find(arg.objID) < 0)
	{
		SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_CopyData(): INTRUDER ALERT !!! Attempt to copy to an alien BannerProfile (#%lu).",
			arg.objID);
		return BXE_BannerProfile_CopyData_AccessDenied;
	}
// Проверить, есть ли source-профиль у пользователя:
	if (oc_user.m_BannerProfile.Find(arg.objFromID) < 0)
	{
		SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_CopyData(): INTRUDER ALERT !!! Attempt to copy from an alien BannerProfile (#%lu).",
			arg.objFromID);
		return BXE_BannerProfile_CopyData_AccessDenied;
	}

// Открыть профиль, из которого будем копировать:
	OC_BannerProfile		oc_banner_profile_from;
	oc_banner_profile_from.Open(arg.objFromID);

// Скопировать:
	oc_banner_profile.CopyDataFrom(oc_banner_profile_from);

// Некоторые поля менять нельзя:
	oc_banner_profile.m_Name = string("Copy of ") + string(oc_banner_profile_from.m_Name);
	oc_banner_profile.m_Banner.Delete();
	oc_banner_profile.m_MaxDailyShowsChangeTime = time_0;
	oc_banner_profile.m_TotalShows		= 0;
	oc_banner_profile.m_TotalClicks		= 0;
	oc_banner_profile.m_SessionEvents	= 0;
	oc_banner_profile.m_Priority			= oc_reg.m_DefaultPriority;
	oc_banner_profile.m_VBN					= oc_user.m_VBN;
	oc_banner_profile.m_OwnerID			= arg.OwnerID;

// Установим признак изменения объекта:	
	oc_banner_profile.m_ObjectState	= OBJ_STATE_CHANGED;

// Установим время модификации:
	oc_banner_profile.m_LastModified = time_0;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_BannerProfile_GetData                                                  []                        
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_BannerProfile_GetData(BX_BannerProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objID))
		return BXE_BannerProfile_GetData_InvalidProfileID;
	
	int i;

// Открыть профиль:
	OC_BannerProfile	oc_banner_profile;
	oc_banner_profile.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner_profile.m_OwnerID, OBJ_CLASS_ID_User);
	
// Проверить пароль:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
// Копируем:

// Name
	arg.Name				=				oc_banner_profile.m_Name;

// VBN
	arg.VBN				= (byte)		oc_banner_profile.m_VBN;

// LastModified, sLastModified
	time_t	modifyTime =
		(time_t)(oc_banner_profile.m_LastModified + oc_user.m_TZOffset);
	
	arg.LastModified	= modifyTime;
	arg.sLastModified.Format("%s", asctime(gmtime(&modifyTime)));

// OwnerID
	arg.OwnerID			=				oc_banner_profile.m_OwnerID;

// HREF
	arg.HREF				=				oc_banner_profile.m_HREF;

// Commercial
	arg.Commercial		=				(bool)oc_banner_profile.m_Commercial;

// Banner, sBanner
	arg.Banner.Delete();
	arg.sBanner.Delete();
	
	for (i = 0; i < oc_banner_profile.m_Banner.Size(); i++)
	{
	// Откроем очередной сайт профиля:
		OC_Banner	oc_banner;
		BX_CHECK_AND_OPEN(oc_banner, oc_banner_profile.m_Banner[i], OBJ_CLASS_ID_Banner);

	// Проверка синхронизации сайта и профиля:
		if (oc_banner.m_VBN != oc_banner_profile.m_VBN)
		{
			SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_GetData(#%lu): Banner & Profile VBNs do not match. Banner skipped.",
				(unsigned long)arg.objID);
			continue;
		}
		if (oc_banner.m_Profile != arg.objID)
		{
			SERVER_DEBUG_ERROR_1 ("BX_BannerProfile_GetData(#%lu): Banner & Profile are not completely connected. Banner skipped.",
				(unsigned long)arg.objID);
			continue;
		}
	// Добавим id и имена к выходным массивам:	
		arg.Banner.Add(oc_banner.GetObjectID());
		arg.sBanner.Add(oc_banner.m_FileName);
	}

// Concept
	_BitsToIDs(  arg.Concept, oc_banner_profile.m_ba_Concept);


// State
	time_t	CurTime = time_0;
	if (	(CurTime < (time_t)oc_banner_profile.m_AutoOn) ||
			(CurTime > (time_t)oc_banner_profile.m_AutoOff)) {
		oc_banner_profile.m_State = false;
	}
	arg.State			= (bool)		oc_banner_profile.m_State;

// AltText
	arg.AltText			= oc_banner_profile.m_AltText;

// SiteConceptInclude
	_BitsToIDs(  arg.SiteConceptInclude,	  oc_banner_profile.m_ba_SiteConceptInclude);

// SiteConceptExclude
	_BitsToIDs(  arg.SiteConceptExclude,	  oc_banner_profile.m_ba_SiteConceptExclude);

// SiteInclude, sSiteInclude
	arg.SiteInclude.Delete();
	arg.sSiteInclude.Delete();
	
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Site, oc_banner_profile.m_SiteInclude);

	for (i = 0; i < oc_banner_profile.m_SiteInclude.Size(); i++)
	{
	// Откроем очередной сайт:
		OC_Site	oc_site;
		BX_CHECK_AND_OPEN(oc_site, oc_banner_profile.m_SiteInclude[i], OBJ_CLASS_ID_Site);

	// Добавим id и имена к выходным массивам:	
		arg.SiteInclude.Add(oc_site.GetObjectID());
		arg.sSiteInclude.Add(oc_site.m_Name);
	}

// SiteExclude, sSiteExclude
	arg.SiteExclude.Delete();
	arg.sSiteExclude.Delete();
	
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Site, oc_banner_profile.m_SiteExclude);

	for (i = 0; i < oc_banner_profile.m_SiteExclude.Size(); i++)
	{
	// Откроем очередной сайт профиля:
		OC_Site	oc_site;
		BX_CHECK_AND_OPEN(oc_site, oc_banner_profile.m_SiteExclude[i], OBJ_CLASS_ID_Site);
	// Добавим id и имена к выходным массивам:	
		arg.SiteExclude.Add(oc_site.GetObjectID());
		arg.sSiteExclude.Add(oc_site.m_Name);
	}

// ViewerIPEnable
	arg.ViewerIPEnable=				oc_banner_profile.m_ViewerIPEnable;

// ViewerIPDisable
	arg.ViewerIPDisable
							=				oc_banner_profile.m_ViewerIPDisable;

// ViewerConceptInclude
	_BitsToIDs( arg.ViewerConceptInclude, oc_banner_profile.m_ba_ViewerConceptInclude);

// ViewerConceptExclude
	_BitsToIDs( arg.ViewerConceptExclude, oc_banner_profile.m_ba_ViewerConceptExclude);

// UseLocalTime
	arg.UseLocalTime		= (bool)oc_banner_profile.m_UseLocalTime;

// ScheduleTZOffset
	arg.ScheduleTZOffset	= (time_t)oc_banner_profile.m_ScheduleTZOffset;

// ShowIfLocalUnknown
	arg.ShowIfLocalUnknown= (bool)oc_banner_profile.m_ShowIfLocalUnknown;
	
// Schedule
	if (oc_banner_profile.m_ba_Schedule.Size() > 0)
	{
		arg.Schedule.Delete();
		for (int i = 0; i < HOURS_IN_WEEK; i++)
		{
			arg.Schedule.Add(GetBit(oc_banner_profile.m_ba_Schedule.GetCPtr(), i));
		}
	}

// AutoOn
	arg.AutoOn				= (time_t)oc_banner_profile.m_AutoOn;
// AutoOff
	arg.AutoOff				= (time_t)oc_banner_profile.m_AutoOff;

// RepeatCount
	arg.RepeatCount		= (int)oc_banner_profile.m_RepeatCount;

// RepeatTime
	arg.RepeatTime			= (time_t)oc_banner_profile.m_RepeatTime;
	
// CountTypeByShows
	arg.CountTypeByShows	= (bool)oc_banner_profile.m_CountTypeByShows;

// MaxDailyClicks
	arg.MaxDailyClicks	= (int)oc_banner_profile.m_MaxDailyClicks;

// MaxDailyShows
	arg.MaxDailyShows		= (int)oc_banner_profile.m_MaxDailyShows;

// MaxDailyShowsChangeTime
	arg.MaxDailyShowsChangeTime
								= (time_t)oc_banner_profile.m_MaxDailyShowsChangeTime;
// TotalShows
	arg.TotalShows			= (int)oc_banner_profile.m_TotalShows;

// TotalClicks
	arg.TotalClicks		= (int)oc_banner_profile.m_TotalClicks;

// SessionEvents
	arg.SessionEvents		= (int)oc_banner_profile.m_SessionEvents;

// Priority
	arg.Priority			= oc_banner_profile.m_Priority;

// Allowed
	arg.Allowed				= (bool)oc_banner_profile.m_Allowed;

// ObjectState
	arg.ObjectState		= oc_banner_profile.m_ObjectState;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_BannerProfile_PutData                                                  []                        
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_BannerProfile_PutData(BX_BannerProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objID))
		return BXE_BannerProfile_PutData_InvalidProfileID;
	
// Открыть профиль:
	OC_BannerProfile	oc_banner_profile;
	oc_banner_profile.Open(arg.objID);

// Открыть объект пользователя-владельца:
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner_profile.m_OwnerID, OBJ_CLASS_ID_User);
	
// Проверить пароль:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
// Копирование:
	int					i=0;

// Name
	oc_banner_profile.m_Name			= arg.Name;

// HREF
	if (OC_Exist(OBJ_CLASS_ID_Site, arg.HREF))
	{
		if (oc_user.m_Site.Find(arg.HREF) != -1)
		{
			OC_Site	oc_site;
			if (oc_banner_profile.m_HREF != NA)
			// Удалить ссылку у старого сайта:
			{
				BX_CHECK_AND_OPEN(oc_site, oc_banner_profile.m_HREF, OBJ_CLASS_ID_Site);

				int idPos = oc_site.m_AdBannerProfile.Find(oc_banner_profile.GetObjectID());

				SERVER_DEBUG_ASSERT_RETURN(
					idPos != -1,
					"BX_BannerProfile_PutData(): Can't find HREF in Site::AdBannerProfile[].",
					BX_SYSTEM_ERROR);
				
				oc_site.m_AdBannerProfile.Del(idPos);
			}
		// Добавить ссылку в новый сайт:
			oc_site.Open(arg.HREF);
			SERVER_DEBUG_ASSERT_RETURN(
				oc_site.m_AdBannerProfile.Find(arg.HREF) == -1,
				"BX_BannerProfile_PutData(): Double HREF in Site::AdBannerProfile.",
				BX_SYSTEM_ERROR);
			oc_site.m_AdBannerProfile.Add(oc_banner_profile.GetObjectID());
		// Изменить ссылку у профиля:
			oc_banner_profile.m_HREF		= arg.HREF;
		}
	}
	else
	{
		oc_banner_profile.m_HREF		= NA;
	}

// Concept
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Concept,			arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_banner_profile.m_ba_Concept);
	ExpandConcept(arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_banner_profile.m_eba_Concept);

// Commercial
//	oc_banner_profile.m_Commercial	= arg.Commercial;

// State
	oc_banner_profile.m_State			= arg.State;

// AltText
	oc_banner_profile.m_AltText		= arg.AltText;

// SiteConceptInclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Concept,			arg.SiteConceptInclude);
	_IDsToBits_Set( arg.SiteConceptInclude, oc_banner_profile.m_ba_SiteConceptInclude);
	ExpandConcept(arg.SiteConceptInclude);
	_IDsToBits_Set( arg.SiteConceptInclude, oc_banner_profile.m_eba_SiteConcept);

// SiteConceptExclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Concept,			arg.SiteConceptExclude);
	_IDsToBits_Set( arg.SiteConceptExclude, oc_banner_profile.m_ba_SiteConceptExclude);
	ExpandConcept(arg.SiteConceptExclude);
	_IDsToBits_OrNot(arg.SiteConceptExclude, oc_banner_profile.m_eba_SiteConcept);

// SiteInclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Site,			arg.SiteInclude);
	arg.SiteInclude.Sort();
	oc_banner_profile.m_SiteInclude  = arg.SiteInclude;

// SiteExclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Site,			arg.SiteExclude);
	arg.SiteExclude.Sort();
	oc_banner_profile.m_SiteExclude  = arg.SiteExclude;

// ViewerIPEnable
	oc_banner_profile.m_ViewerIPEnable = arg.ViewerIPEnable;

// ViewerIPDisable
	oc_banner_profile.m_ViewerIPDisable = arg.ViewerIPDisable;

// ViewerConceptInclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Concept,		arg.ViewerConceptInclude);
	_IDsToBits_Set( arg.ViewerConceptInclude, oc_banner_profile.m_ba_ViewerConceptInclude);
	ExpandConcept(arg.ViewerConceptInclude);
	_IDsToBits_Set( arg.ViewerConceptInclude, oc_banner_profile.m_eba_ViewerConcept);

// ViewerConceptExclude
	VALIDATE_ID_ARRAY (OBJ_CLASS_ID_Concept,		arg.ViewerConceptExclude);
	_IDsToBits_Set( arg.ViewerConceptExclude, oc_banner_profile.m_ba_ViewerConceptExclude);
	ExpandConcept(arg.ViewerConceptExclude);
	_IDsToBits_OrNot(arg.ViewerConceptExclude, oc_banner_profile.m_eba_ViewerConcept);

// UseLocalTime
	oc_banner_profile.m_UseLocalTime			= arg.UseLocalTime;

// ScheduleTZOffset
	if (labs(arg.ScheduleTZOffset) <= SECS_IN_DAY/2) {
		oc_banner_profile.m_ScheduleTZOffset= arg.ScheduleTZOffset;
	}

// ShowIfLocalUnknown
	oc_banner_profile.m_ShowIfLocalUnknown	= arg.ShowIfLocalUnknown;

// Schedule
	if ((arg.Schedule.Size() != HOURS_IN_WEEK) && (arg.Schedule.Size() != 0)) {
		arg.Schedule.Erase();
	}
	if (arg.Schedule.Size()>0) {
		SERVER_DEBUG_ASSERT_RETURN (arg.Schedule.Size()==HOURS_IN_WEEK, "BX_BannerProfile_PutData: Неправильный размер расписания", BX_SYSTEM_ERROR);
		for (i = 0; i < HOURS_IN_WEEK; i++) {
		_SetBit (oc_banner_profile.m_ba_Schedule, i, arg.Schedule[i]);
		}
	}

// AutoOn/Off
	if (Time_IsValid(arg.AutoOn)) {
		oc_banner_profile.m_AutoOn = arg.AutoOn;
	}
	
	if (Time_IsValid(arg.AutoOff)) {
		oc_banner_profile.m_AutoOff = arg.AutoOff;
	}
	
// RepeatCount
	if (arg.RepeatCount >= -1) {
		oc_banner_profile.m_RepeatCount = arg.RepeatCount;
	}

// RepeatTime
	if (Time_IsValid(arg.RepeatTime)) {
		oc_banner_profile.m_RepeatTime = arg.RepeatTime;
	}


// Поля, связанные с приоритетом:
//!!!
	oc_banner_profile.m_CountTypeByShows = arg.CountTypeByShows;
	
	if (oc_banner_profile.m_MaxDailyClicks != arg.MaxDailyClicks)
	{
		if ((arg.MaxDailyClicks > 0) && (arg.MaxDailyClicks < 10000)) {
			oc_banner_profile.m_MaxDailyClicks  = arg.MaxDailyClicks;
		}
		else {
			oc_banner_profile.m_MaxDailyClicks = 0;
		}

		oc_banner_profile.m_SessionEvents	= 0;
		oc_banner_profile.m_Priority			= oc_reg.m_DefaultPriority;
	}
	
	if (oc_banner_profile.m_MaxDailyShows != arg.MaxDailyShows)
	{
		if ((arg.MaxDailyShows > 0) && (arg.MaxDailyShows < 10000)) {
			oc_banner_profile.m_MaxDailyShows	= arg.MaxDailyShows;
		}
		else {
			oc_banner_profile.m_MaxDailyShows = 0;
		}
		
		oc_banner_profile.m_MaxDailyShowsChangeTime = time_0;
		oc_banner_profile.m_SessionEvents	= 0;
		oc_banner_profile.m_Priority			= oc_reg.m_DefaultPriority;
	}



#if 0  //{ AlexV
	float	CTR = BX_Stat_GetSystemCTR();
	if (oc_banner_profile.m_CountTypeByShows != arg.CountTypeByShows)
	{
	// Если CountTypeByShows стал равным false, то
	// пересчитаем клики на показы:
		oc_banner_profile.m_CountTypeByShows = arg.CountTypeByShows;
		if (arg.CountTypeByShows == false)
		{
			arg.MaxDailyShows = int(CTR * arg.MaxDailyClicks);
		}
	}

	if (oc_banner_profile.m_MaxDailyShows != arg.MaxDailyShows)
	{
	// Если изменился MaxDailyShows, то проверим валидность -
	// он не должен превышать недельного траффика:
		int WeekTraffic = BX_Stat_User_GetWeekTraffic(oc_banner_profile.m_OwnerID);

		if (WeekTraffic < oc_reg.m_MinDailyShows) {
			WeekTraffic = oc_reg.m_MinDailyShows;
		}
		if (arg.MaxDailyShows > WeekTraffic) {
			arg.MaxDailyShows = WeekTraffic;
			arg.MaxDailyClicks = int(WeekTraffic / CTR);
		}

		oc_banner_profile.m_MaxDailyClicks  = arg.MaxDailyClicks;
		oc_banner_profile.m_MaxDailyShows	= arg.MaxDailyShows;
		oc_banner_profile.m_SessionEvents	= 0;
		oc_banner_profile.m_MaxDailyShowsChangeTime = time_0;
		oc_banner_profile.m_Priority			= oc_reg.m_DefaultPriority;
	}
#endif //}

// Установим признак изменения объекта:	
	oc_banner_profile.m_ObjectState	= OBJ_STATE_CHANGED;

// Установим время модификации:
	oc_banner_profile.m_LastModified = time_0;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_BannerProfile_Delete                                                   []                       
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_BannerProfile_Delete(BX_BannerProfile_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_BannerProfile, arg.objID))
		return BXE_BannerProfile_Delete_InvalidProfileID;

// Открыть профиль, который будем уничтожать:
	OC_BannerProfile		oc_banner_profile;
	oc_banner_profile.Open(arg.objID);

// Откроем объект пользователя-владельца профиля:
	OC_User				oc_user;
	BX_CHECK_AND_OPEN(oc_user, oc_banner_profile.m_OwnerID, OBJ_CLASS_ID_User);

// Проверить пароль:
	if (arg.objPassword != string(oc_user.m_Password))
		return BXE_User_AccessDenied;

// Проверить наличие этого профиля у пользователя:
	SERVER_DEBUG_ASSERT_RETURN(
		oc_user.m_BannerProfile.Find(arg.objID) != -1,
		"BX_BannerProfile_Delete(): Can't found banner profile id in User::BannerProfile[].",
		BX_SYSTEM_ERROR);

//----------------------------------------------------------------------------[] 
	int i		= 0;

// Удалим ссылки на профиль у всех баннеров профиля:
	for (i = 0; i < oc_banner_profile.m_Banner.Size(); i++)
	{
		OC_Banner	oc_banner;
		BX_CHECK_AND_OPEN(oc_banner, oc_banner_profile.m_Banner[i], OBJ_CLASS_ID_Banner);
		
		oc_banner.m_Profile = NA;
	}

//!!! Удалить ссылки на баннер у зрителей ?

// Удалить ссылку на профиль у пользователя:
	DELETE_FROM_ARRAY(oc_user.m_BannerProfile, arg.objID);

// Удалить профиль:
	oc_banner_profile.Delete();

	return BX_OK;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` BX_BannerProfile_Enumerate                                                []                          
//                                                                            []
BX_RESULT BX_BannerProfile_Enumerate(BX_BannerProfile_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;

	OC_BannerProfile			oc_object;
	identifier_arr				IDs;

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


/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/
