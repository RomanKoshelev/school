/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_User.cpp                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "пользователь".             []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_User
#define USES_BX_Macros
#define USES_BX_Utils
#define USES_BX_Site
#define USES_BX_SiteProfile
#define USES_BX_Banner
#define USES_BX_BannerProfile
#define USES_BX_Concept
#define USES_BX_Admin
#define USES_BX_VBN

//#define USES_OBServer_Interface_h
#define USES_URL_h
#define USES_OC_User
#define USES_OC_VBN
#define USES_OC_SiteProfile
#define USES_OC_BannerProfile
#define USES_OC_Site
#define USES_OC_Banner

#include "BX.h"


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_New                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_New(BX_User_Args& arg)
{
	OC_User		oc_user;
	OC_VBN		oc_vbn;
	key_arr		ka;

	USER_REGISTRATION_RESULT	res = User_New_Undefined;

// Проверим валидность входных параметров:
	if (arg.Password != arg.PasswordConfirm)
		USER_NEW_RETURN(User_New_BadPasswordConfirm);
	if (!Email_IsValid(arg.Email))
		USER_NEW_RETURN(User_New_InvalidEmail);
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN))
		return BXE_User_New_InvalidVBN;
	if (arg.Password.Len() < 4)
		USER_NEW_RETURN(User_New_PasswordTooShort);
	if (arg.Login.Len() < 4)
		USER_NEW_RETURN(User_New_LoginTooShort);

	oc_vbn.Open(arg.VBN);

	oc_user.SetIndex_VBN_Login();
	ka.Init();
	ka += (byte)oc_vbn.m_No;
	ka += arg.Login;
	if (oc_user.Find(ka))
		USER_NEW_RETURN(User_New_LoginAlreadyExists);

// Создадим пользователя:
	oc_user.New();
	SERVER_DEBUG_ASSERT_RETURN(
		oc_user.IsValid(),
		"BX_User_New(): Error creating user.",
		BX_SYSTEM_ERROR);

// Установим параметры пользователя:
	oc_user.m_Login					= arg.Login;
	oc_user.m_Password				= arg.Password;
	oc_user.m_FullName				= arg.FullName;
	oc_user.m_Email					= arg.Email;
	oc_user.m_CreationTime			= time_0;
	oc_user.m_VBN						= (byte)oc_vbn.m_No;

	oc_user.m_Allowed					= !bool(oc_vbn.m_IsModerated);
	oc_user.m_ObjectState			= OBJ_STATE_NEW; // новый
	
	oc_user.m_TZOffset				= oc_vbn.m_DefaultTZOffset;
	oc_user.m_InterfaceLanguage	= oc_vbn.m_DefaultLanguage;

// Создадим профиль сайта по умолчанию:
	BX_SiteProfile_Args		site_profile_args;
	site_profile_args.OwnerID		= oc_user.GetObjectID();
	site_profile_args.objPassword = arg.Password;
	site_profile_args.Name			= string("Default site profile for ") + arg.Login;

	BX_ASSERT_PASSIVE(BX_SiteProfile_New(site_profile_args));

// Создадим профиль баннера по умолчанию:
	BX_BannerProfile_Args	banner_profile_args;
	banner_profile_args.OwnerID		= oc_user.GetObjectID();
	banner_profile_args.objPassword	= arg.Password;
	banner_profile_args.Name			= string("Default banner profile for ") + arg.Login;

	BX_ASSERT_PASSIVE(BX_BannerProfile_New(banner_profile_args));


//- - - - - - - - - - - - - - - - - - - - - - - - - -]

	arg.objID = oc_user.GetObjectID();

	USER_NEW_RETURN(User_Okay);
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_GetData                                                           []               
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_GetData(BX_User_Args& arg)
{
	OC_User		oc_user;
	OC_VBN		oc_vbn;
	key_arr		ka;

// Если не указан идентификатор, то производится поиск по VBN, логину и паролю:
	if (arg.objID == NA)
	{
	// Идентификация и аутентификация:
		if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN))
			return BXE_User_GetData_InvalidVBN;
		oc_vbn.Open(arg.VBN);

		oc_user.SetIndex_VBN_Login();
		ka.Init();
		ka += (byte)oc_vbn.m_No;
		ka += arg.Login;

		if (!oc_user.Find(ka))
			return BXE_User_GetData_LoginNotFound;
		if ((string(oc_user.m_Password) != arg.Password) && (!CheckAdminPassword(arg.Password)))
			return BXE_User_GetData_PasswordIncorrect;
		
		arg.objID = oc_user.GetObjectID();
	
	}
	else
	{
		if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
			return BXE_User_GetData_InvalidUserID;

		oc_user.Open(arg.objID);

		if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
			return BXE_User_AccessDenied;

		ka.Init();
		ka += (byte)oc_user.m_VBN;
		oc_vbn.SetIndex_No();
		SERVER_DEBUG_ASSERT_RETURN(
			oc_vbn.Find(ka),
			"BX_User_GetData(): Invalid User::VBN.",
			BX_SYSTEM_ERROR);
	}
//----------------------------------------------------------------------------[] 
// Login
	arg.Login			= oc_user.m_Login;
// Password
	arg.Password		= oc_user.m_Password;
// FullName
	arg.FullName		= oc_user.m_FullName;
// Region
	_BitsToIDs( arg.Concept, oc_user.m_ba_Concept);
// InterfaceLanguage
	arg.InterfaceLanguage =   oc_user.m_InterfaceLanguage;
// InterfaceType
	arg.InterfaceType = (bool)oc_user.m_InterfaceType;
// CreationTime, sCreationTime
	time_t	createTime =
		(time_t)(oc_user.m_CreationTime + oc_user.m_TZOffset);
	
	arg.CreationTime	= createTime;
	arg.sCreationTime.Format("%s", asctime(gmtime(&createTime)));

// VBN
	arg.VBN				= oc_vbn.GetObjectID();
// Email
	arg.Email			= oc_user.m_Email;
// Phone
	arg.Phone			= oc_user.m_Phone;
// Fax
	arg.Fax				= oc_user.m_Fax;
// Address
	arg.Address			= oc_user.m_Address;
// URL
	arg.URL				= oc_user.m_URL;
// Comment
	arg.Comment			= oc_user.m_Comment;
// TimeZoneOffset
	arg.TZOffset		= oc_user.m_TZOffset;
// NotifyFreq
	arg.NotifyFreq		= oc_user.m_NotifyFreq;
// NotifyHTML
	arg.NotifyHTML		= (bool)oc_user.m_NotifyHTML;
// NotifyDepth
	arg.NotifyDepth	= oc_user.m_NotifyDepth;

// ShowsLeft
	arg.ShowsLeft		= (int)oc_user.m_ShowsLeft;
// ClicksLeft
	arg.ClicksLeft		= (int)oc_user.m_ClicksLeft;

// TradeStats
	arg.TradeStats		= (identifier)oc_user.m_TradeStats;

// Allowed
	arg.Allowed			= (bool)oc_user.m_Allowed;
// ObjectState
	arg.ObjectState	= oc_user.m_ObjectState;
	
	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_GetEmail                                                          []                
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_User_GetEmail(BX_User_Args& arg)
{
	OC_User		oc_user;
	OC_VBN		oc_vbn;
	key_arr		ka;

	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN))
		return BXE_User_GetData_InvalidVBN;
	oc_vbn.Open(arg.VBN);

// Поиск по VBN и логину:
	oc_user.SetIndex_VBN_Login();
	ka.Init();
	ka += (byte)oc_vbn.m_No;
	ka += arg.Login;

	if (!oc_user.Find(ka))
		return BXE_User_GetData_LoginNotFound;

	arg.Email = oc_user.m_Email;

	return BX_OK;
}


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_PutData                                                           []               
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_User_PutData(BX_User_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
		return BXE_User_PutData_InvalidUserID;
	
	OC_User		oc_user;

	oc_user.Open(arg.objID);

	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

// Тут можно также организовать проверку полей arg.* на валидность...

//	if (arg.Password == arg.PasswordConfirm) ПАРОЛЬ МЕНЯТЬ НЕЛЬЗЯ!
//		oc_user.m_Password	= arg.Password;

//----------------------------------------------------------------------------[] 
// Копирование полей:

// FullName	
	oc_user.m_FullName		= arg.FullName;

// Region
	VALIDATE_ID_ARRAY	(OBJ_CLASS_ID_Concept,		arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_user.m_ba_Concept);
	ExpandConcept(arg.Concept);
	_IDsToBits_Set( arg.Concept, oc_user.m_eba_Concept);

// InterfaceLanguage
	if (OC_Exist(OBJ_CLASS_ID_Language, arg.InterfaceLanguage))
		oc_user.m_InterfaceLanguage = arg.InterfaceLanguage;

// InterfaceType
	oc_user.m_InterfaceType = arg.InterfaceType;

// Email
	if (Email_IsValid(arg.Email)) {
		oc_user.m_Email		= arg.Email;
	}
// Phone
	oc_user.m_Phone			= arg.Phone;

// Fax
	oc_user.m_Fax				= arg.Fax;

// Address
	oc_user.m_Address			= arg.Address;

// URL
	HTTP_URL(arg.URL).URL(arg.URL);
	oc_user.m_URL				= arg.URL;

// Comment
	oc_user.m_Comment			= arg.Comment;

// TimeZoneOffset
	if (labs(arg.TZOffset) <= SECS_IN_DAY/2) {
		oc_user.m_TZOffset	= arg.TZOffset;
	}
// NotifyFreq
	oc_user.m_NotifyFreq		= arg.NotifyFreq;

// NotifyHTML
	oc_user.m_NotifyHTML		= arg.NotifyHTML;

// NotifyDepth
	oc_user.m_NotifyDepth	= arg.NotifyDepth;

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 

// Установим признак изменения объекта:	
	oc_user.m_ObjectState	= OBJ_STATE_CHANGED;

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_Delete                                                            []              
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_User_Delete(BX_User_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
		return BXE_User_Delete_InvalidUserID;

	OC_User				oc_user;
	OC_Site				oc_site;
	OC_Banner			oc_banner;
	OC_SiteProfile		oc_site_profile;
	OC_BannerProfile	oc_banner_profile;

	oc_user.Open(arg.objID);

// Проверка пароля:
	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

// Откроем виртуальную сеть пользователя:
	OC_VBN				oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr	ka;
	ka += (byte)oc_user.m_VBN;
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_User_Delete(): Wrong User::VBN or VBN does not exist.",
		BX_SYSTEM_ERROR);

// Если пользователь - системный, то его удалять нельзя:
	if (oc_vbn.m_Owner = arg.objID)
		return BXE_User_Delete_SystemUser;
//----------------------------------------------------------------------------[] 
	

// Удаляем сайты пользователя:	
	while (oc_user.m_Site.Size() > 0)
	{
		BX_Site_Args				site_args;
		site_args.objID = oc_user.m_Site[0];
		BX_ASSERT_RETURN(BX_Site_Delete(site_args));
		
		oc_user.m_Site.Del(0);
	}

// Удаляем баннеры пользователя:
	while (oc_user.m_Banner.Size() > 0)
	{
		BX_Banner_Args				banner_args;
		banner_args.objID = oc_user.m_Banner[0];
		BX_ASSERT_RETURN(BX_Banner_Delete(banner_args));
		oc_user.m_Banner.Del(0);
	}

// Удаляем профили пользователя:
	while (oc_user.m_BannerProfile.Size() > 0)
	{
		BX_BannerProfile_Args	banner_profile_args;
		banner_profile_args.objID = oc_user.m_BannerProfile[0];
		BX_ASSERT_RETURN(BX_BannerProfile_Delete(banner_profile_args));
		oc_user.m_BannerProfile.Del(0);
	}
	while (oc_user.m_SiteProfile.Size() > 0)
	{
		BX_SiteProfile_Args		site_profile_args;
		site_profile_args.objID = oc_user.m_SiteProfile[0];
		BX_ASSERT_RETURN(BX_SiteProfile_Delete(site_profile_args));
		oc_user.m_SiteProfile.Del(0);
	}

// Удаляем самого пользователя:	
	oc_user.Delete();

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_SiteEnumerate		                                                []                          
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_SiteEnumerate(BX_User_Args& arg)
{
	if (arg.objFirstNo < 0)						arg.objFirstNo	= 0;
	if (arg.objLastNo < arg.objFirstNo)		arg.objLastNo	= INT_MAX;

	arg.objNames.Delete();

	if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
	{
		arg.objIDs.Delete();
		return BXE_User_SiteEnumerate_InvalidObjectID;
	}

	OC_User	oc_user;
	oc_user.Open(arg.objID);


// Проверка пароля:
	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

	oc_user.m_Site.CopyTo(arg.objIDs);

	OC_Site	oc_site;

	for (int i=arg.objFirstNo; (i<arg.objIDs.Size()) && (i<=arg.objLastNo); i++) 
	{
		BX_CHECK_AND_OPEN(oc_site, arg.objIDs[i], OBJ_CLASS_ID_Site);
		arg.objNames.Add(oc_site.m_Name);
	}

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_BannerEnumerate		                                             []                            
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_User_BannerEnumerate(BX_User_Args& arg)
{
	if (arg.objFirstNo < 0)						arg.objFirstNo	= 0;
	if (arg.objLastNo < arg.objFirstNo)	arg.objLastNo	= INT_MAX;

	arg.objNames.Delete();

	if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
	{
		arg.objIDs.Delete();
		return BXE_User_BannerEnumerate_InvalidObjectID;
	}
	
	OC_User	oc_user;
	oc_user.Open(arg.objID);

// Проверка пароля:
	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
	oc_user.m_Banner.CopyTo(arg.objIDs);

	OC_Banner	oc_banner;

	for (int i=arg.objFirstNo; (i<arg.objIDs.Size()) && (i<=arg.objLastNo); i++) 
	{
		BX_CHECK_AND_OPEN(oc_banner, arg.objIDs[i], OBJ_CLASS_ID_Banner);
		arg.objNames.Add(oc_banner.m_FileName);
	}

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_SiteProfileEnumerate		                                          []                                 
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_SiteProfileEnumerate(BX_User_Args& arg)
{
	if (arg.objFirstNo < 0)						arg.objFirstNo	= 0;
	if (arg.objLastNo < arg.objFirstNo)	arg.objLastNo	= INT_MAX;

	arg.objNames.Delete();

	if (!OC_Exist(OBJ_CLASS_ID_User,arg.objID))
	{
		arg.objIDs.Delete();
		return BXE_User_SiteProfileEnumerate_InvalidObjectID;
	}
	
	OC_User	oc_user;
	oc_user.Open(arg.objID);

// Проверка пароля:
	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

//----------------------------------------------------------------------------[] 
	oc_user.m_SiteProfile.CopyTo(arg.objIDs);

	OC_SiteProfile	oc_site_profile;

	for (int i=arg.objFirstNo; (i<arg.objIDs.Size()) && (i<=arg.objLastNo); i++) 
	{
		BX_CHECK_AND_OPEN(oc_site_profile, arg.objIDs[i], OBJ_CLASS_ID_SiteProfile);
		arg.objNames.Add(oc_site_profile.m_Name);
	}

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_BannerProfileEnumerate		                                       []                                   
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_BannerProfileEnumerate(BX_User_Args& arg)
{
	arg.objNames.Delete();

	if (!OC_Exist(OBJ_CLASS_ID_User,arg.objID))
	{
		arg.objIDs.Delete();
		return BXE_User_BannerProfileEnumerate_InvalidObjectID;
	}
	
	OC_User	oc_user;
	oc_user.Open(arg.objID);

// Проверка пароля:
	if ((arg.Password != string(oc_user.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_User_AccessDenied;

	oc_user.m_BannerProfile.CopyTo(arg.objIDs);


	OC_BannerProfile	oc_banner_profile;
//----------------------------------------------------------------------------[] 

	for (int i = 0; i < arg.objIDs.Size(); i++) 
	{
		BX_CHECK_AND_OPEN(oc_banner_profile, arg.objIDs[i], OBJ_CLASS_ID_BannerProfile);

		oc_banner_profile.Open(arg.objIDs[i]);
		arg.objNames.Add(oc_banner_profile.m_Name);
	}

	return BX_OK;
}
	 	 
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_RegisterAsSystem                                                  []                        
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_RegisterAsSystem(BX_User_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_User, arg.objID))
		return BXE_User_RegisterAsSystem_InvalidObjectID;

	OC_User	oc_user;
	oc_user.Open(arg.objID);

	OC_VBN	oc_vbn;
	oc_vbn.SetIndex_No();

	key_arr	ka;
	ka += (byte)oc_user.m_VBN;
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.Find(ka),
		"BX_User_RegisterAsSystem: Incorrect User::VBN or VBN not found.",
		BX_SYSTEM_ERROR);

	if ((arg.Password != string(oc_vbn.m_Password)) && (!CheckAdminPassword(arg.Password)))
		return BXE_VBN_AccessDenied;

	oc_vbn.m_Owner = arg.objID;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Security_Authorize                                                     []                     
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_Security_Authorize(BX_Security_Args& arg)
{
	arg.Result = false;

	if (arg.Level == "Root")
	{
		if ((arg.Login == "Root") && CheckAdminPassword(arg.Password))
			arg.Result = true;
	}

	//----------------------------------------------------------------------------[] 
	if (arg.Level == "VBN")
	{
		OC_VBN	oc_vbn;
		oc_vbn.SetIndex_Name();

		key_arr	ka;
		ka += arg.Login;

		if (oc_vbn.Find(ka))
		{
			if (oc_vbn.m_Password ==  arg.Password)
				arg.Result = true;
		}
		if (CheckAdminPassword(arg.Password))
			arg.Result = true;

	}

	//----------------------------------------------------------------------------[] 
	if (arg.Level == "User")
	{
		if (OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN))
		{
			OC_VBN	oc_vbn;
			oc_vbn.Open(arg.VBN);

			OC_User	oc_user;
			oc_user.SetIndex_VBN_Login();
			
			key_arr	ka;
			ka += (byte)oc_vbn.m_No;
			ka += arg.Login;
			
			if (oc_user.Find(ka))
			{
				if (oc_user.m_Password == arg.Password)
					arg.Result = true;
			}

			if (CheckAdminPassword(arg.Password))
				arg.Result = true;
		}
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_GetForgetPassword                                                 []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_GetForgetPassword(BX_User_Args	&arg)
{

	OC_VBN	oc_vbn;
	BX_CHECK_AND_OPEN(oc_vbn, arg.VBN, OBJ_CLASS_ID_VBN);

	OC_User	oc_user;
	oc_user.SetIndex_VBN_Login();
	
	key_arr	ka;
	ka += (byte)oc_vbn.m_No;
	ka += arg.Login;
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_user.Find(ka),
		"BX_User_GetForgetPassword(): Login search failed.",
		BX_SYSTEM_ERROR);

	arg.ForgetPassword = (bool)oc_user.m_ForgetPassword;
	
	return BX_OK;

}


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_User_SetForgetPassword                                                 []                         
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_User_SetForgetPassword(BX_User_Args	&arg)
{
	OC_VBN	oc_vbn;
	BX_CHECK_AND_OPEN(oc_vbn, arg.VBN, OBJ_CLASS_ID_VBN);

	OC_User	oc_user;
	oc_user.SetIndex_VBN_Login();
	
	key_arr	ka;
	ka += (byte)oc_vbn.m_No;
	ka += arg.Login;
	
	SERVER_DEBUG_ASSERT_RETURN(
		oc_user.Find(ka),
		"BX_User_SetForgetPassword(): Login search failed.",
		BX_SYSTEM_ERROR);

	oc_user.m_ForgetPassword = arg.ForgetPassword;
	
	return BX_OK;

}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_User_Enumerate                                                         []                 
//                                                                            []
BX_RESULT BX_User_Enumerate(BX_User_Args& arg)
{
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;

	OC_User			oc_object;
	identifier_arr	IDs;

	oc_object.GetClassIdList(IDs);

	arg.objIDs.Delete();
	arg.objNames.Delete();
	
	for (int i=arg.objFirstNo; (i<=arg.objLastNo) && (i<IDs.Size()); i++)
	{
		oc_object.Open(IDs[i]);
		arg.objIDs.Add(IDs[i]);
		arg.objNames.Add(oc_object.m_Login);
	}

	return BX_OK;	
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_User_GetLanguage                                                       []                   
//                                                                            []
BX_RESULT BX_User_GetLanguage(BX_User_Args& arg)
{
	OC_User	oc_user;
	BX_CHECK_AND_OPEN(oc_user, arg.objID, OBJ_CLASS_ID_User);

	arg.InterfaceLanguage = oc_user.m_InterfaceLanguage;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/