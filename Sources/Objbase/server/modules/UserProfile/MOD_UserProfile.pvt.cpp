/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_UserProfile.pvt.cpp													[]
[] Date:          11.октября.2000															[]
[] Author:        Roman V. Koshelev, Ekaterina B. Loupacheva 						[]
[] Description:   Работа с настройками и специфическими данными пользователей	[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserProfile.inc.h"


//______________________________________________________________________________
//                                                                            []
//` Проверка на валидность																		[]
//                                                                            []
bool CHECK_USERPROFILE_GUID (guid profileGUID)
{
	DEBUG_STACK_NAME (CHECK_USERPROFILE_GUID);

// Объект должен существовать
	if (!OC_Exist (profileGUID))
	{
		return false;
	}
	
// Проверка на целостность модульных связей
	IF_NOT_CHECK_MOD_BASE (UserProfile, User, profileGUID)
	{
		return false;
	}

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка на валидность																		[]
//                                                                            []
bool CHECK_USERPROFILE_ID (identifier profileID)
{
	DEBUG_STACK_NAME (CHECK_USERPROFILE_ID);

// Объект должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_UserProfile, profileID))
	{
		return false;
	}
	OC_UserProfile oc_profile (profileID);

	guid gi = oc_profile.GetObjectGUID ();
	
	return CHECK_USERPROFILE_GUID(gi);

	return true;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Получить профиль по пользователю														[]
//  Если не существует, создаётся новый													[]
//                                                                            []
identifier GetUserProfileIDByUserID (identifier userID)
{
	DEBUG_STACK_NAME (GetUserProfileIDByUserID);

	GET_MOD_EXTENSION (User, userID, UserProfile, profile);

	if (profileID!=NA && CHECK_USERPROFILE_ID (profileID))
	{
		return profileID;
	}
	return NA;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Проверка доступа к профилю другого пользователя                           []                                       
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_USERPROFILE (identifier loginID, identifier userID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_USERPROFILE);

// Сам пользователь имеет все права на свой профиль.
	if (loginID==userID)
	{
		return ERR_OK;
	}

// Пользователь должен обладать правами просматривать данные пользователей
	ERR_RESULT res = USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), Attributes);
	if (res != ERR_OK)
	{
		return res;
	}
	
// Пользователь должен обладать более сильным уровнем доступа, чем владелец профиля.
	OC_User oc_login	(loginID);
	OC_User oc_user	(userID);
	if (oc_login.m_AccessLevel >= oc_user.m_AccessLevel)
	{
		return ERR_InsufficientAccessLevel;
	}

	return ERR_OK;
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Обновления лога изменений, проводимых пользователем в базе						[]
//                                                                            []
bool UserProfileLogUpdate (identifier userID, int Action, guid objGUID, int Time)
{
	DEBUG_STACK_NAME (UserProfileLogUpdate);


//----------------------------------------------------------------------------[] 
// Проверка кода действия
	if (Action>=USER_LOG_last_bad || Action<=USER_LOG_first_bad)
	{
		SERVER_DEBUG_ERROR_1 ("Ошибочный тип записи (%d) в лог", Action);
		return false;
	}
// Проверяем идентификатор пользователя
	if (!OC_Exist (OBJ_CLASS_ID_User, userID))
	{
		return false;
	}
// Если не открылся профиль -- системная ошибка
	identifier profileID = GetUserProfileIDByUserID (userID);
	if (profileID==NA) 
	{
		return false;
	}
	OC_UserProfile oc_profile (profileID);
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
// Обновление лога
  	oc_profile.m_Log_Action		+= Action;
	oc_profile.m_Log_Time		+=	Time; 	
	oc_profile.m_Log_ObjectGUID+= objGUID;
//----------------------------------------------------------------------------[] 


	return true;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/