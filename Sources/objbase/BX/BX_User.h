/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_User.h                                                 []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "пользователь".             []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                              
#ifndef BX_User_H
#define BX_User_H


//______________________________________________________________________________
//                                                                            []
//` User                                                                      []    
//                                                                            []

//----------------------------------------------------------------------------[]
enum	USER_REGISTRATION_RESULT
{
	User_Okay							= 0,
	User_New_BadPasswordConfirm	= 1,
	User_New_InvalidEmail			= 2,
	User_New_PasswordTooShort		= 3,
	User_New_LoginTooShort			= 4,
	User_New_LoginAlreadyExists	= 5,

	User_New_Undefined				= -1
};

#define	USER_NEW_RETURN(_retcode_)															\
{																										\
	res = _retcode_;																				\
	arg.ExitCode = (int)res;																	\
	return BX_OK;																					\
}
//----------------------------------------------------------------------------[]

struct BX_User_Args
{ 
	BX_User_Args()
	{
		ForgetPassword		= false;
		InterfaceLanguage = NA;
		InterfaceType		= false;
		Allowed				= false;
		CreationTime		= 0;
		VBN					= NA;
		TZOffset				= 0;
		NotifyFreq			= 0;
		NotifyHTML			= false;
		NotifyDepth			= 0;
		ShowsLeft			= 0;
		ClicksLeft			= 0;
		TradeStats			= NA;
		objID					= NA;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
		ExitCode				= -1;
	}

	READONLY	string			Login;			// Имя для доступа к объекту.
				string			Password;		// Пароль для доступа к объекту.
				string			PasswordConfirm;// Подтверждение пароля.
				bool				ForgetPassword;
				string			FullName;		// Полное имя пользователя.
				identifier_arr	Concept;			// Концепты пользователя.
				identifier		InterfaceLanguage;// ID препочтительного языка интерфейса.
				bool				InterfaceType;	// Интерфейс пользователя (быстрый/точный).
	READONLY	time_t			CreationTime;	// Время создания объекта.
	READONLY	string			sCreationTime;	// 
	READONLY	identifier		VBN;				// ID виртуальной сети пользователя.

			// Координаты
   
				string			Email;			// Email.
				string			Phone;			// Телефон.
				string			Fax;				// Fax.
				string			Address;			// Адрес.
				string			URL;				// URL-Адрес.
				string			Comment;			// Комментарий.
				time_t			TZOffset;		// Смещение временной зоны в секундах.

			// Оповещение

				int				NotifyFreq;		// Как часто присылать статистику (не надо/ каждый день/неделю/месяц).
				bool				NotifyHTML;		// Присылать ли статистику в виде HTML.
				int				NotifyDepth;	// Тип присылаемой статистики (её развёрнутость, глубина).

			// Кредиты

	READONLY	int				ShowsLeft;		//	Общее число оставшихся показов.
	READONLY	int				ClicksLeft;		//	Общее число оставшихся кликов.

			// Статистика

	READONLY	identifier		TradeStats;		// Информация о продаже/покупке показов/кликов у пользователя.

			// Пометки (для) модератора:

	READONLY	bool				Allowed;			// Информация пользователя разрешена модератором.
	READONLY	int				ObjectState;	// Состояние объекта: 0 - проверен; 1 - новый;
														//  2 - изменено критическое поле; 3 - изменён.

				identifier		objID;		// Идентификатор пользователя.
				int				objFirstNo;	// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;	// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
	READONLY	identifier_arr	objIDs;		// Идентификаторы объектов.
	READONLY	string_arr		objNames;	// Здесь возвращаются имена функциями *Enumerate().
				
				int				ExitCode;	// Код возврата (Okay=0;BadPasswordConfirm=1;InvalidEmail=2;PasswordTooShort=3;LoginTooShort=4;LoginAlreadyExists=5).
};
//----------------------------------------------------------------------------[]


// Создание пользователя. Также создаются профили баннера и сайта по умолчанию.
// Необходимые поля: Login, Password, PasswordConfirm, FullName, Email, VBN.
BX_RESULT BX_User_New(BX_User_Args& arg);

//	Получение установок пользователя. Если не указан objID, то пользователь
// ищется по полям Login, Password и VBN, а идентификатор найденного пользователя
// возвращается в objID. В этом случае возможен возврат ошибок
// BXE_User_GetData_LoginNotFound или BXE_User_GetData_PasswordIncorrect.
// Пароль пользователя Password необходимо указать в любом случае.
BX_RESULT BX_User_GetData(BX_User_Args& arg);

// Получение адреса эл. почты пользователя по его логину и VBN.
BX_RESULT BX_User_GetEmail(BX_User_Args& arg);

//	Изменение установок пользователя с идентификатором objID.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_PutData(BX_User_Args& arg);

// Удаление пользователя с идентификатором objID. Удаляются все сайты, профили и баннеры пользователя.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_Delete(BX_User_Args& arg);

// Получение списка идентификаторов (в objIDs) и названий (в objNames) сайтов пользователя с идентификатором objID.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_SiteEnumerate(BX_User_Args& arg);	

// Получение списка идентификаторов (в objIDs) и названий (в objNames) баннеров пользователя с идентификатором objID.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_BannerEnumerate(BX_User_Args& arg);	

// Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей сайтов пользователя с идентификатором objID.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_SiteProfileEnumerate(BX_User_Args& arg);

// Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей баннеров пользователя с идентификатором objID.
// Необходимо указать пароль пользователя Password.
BX_RESULT BX_User_BannerProfileEnumerate(BX_User_Args& arg);

// Регистрация пользователя как системного 
// (баннеры которого показываются в исключительных ситуациях).
// Необходимо указать Password для доступа к VBN пользователя.
BX_RESULT BX_User_RegisterAsSystem(BX_User_Args& arg);

// Возвращает флаг перезагрузки пароля.
BX_RESULT BX_User_GetForgetPassword(BX_User_Args&arg);

// Устанавливает флаг перезагрузки пароля.
BX_RESULT BX_User_SetForgetPassword(BX_User_Args& arg);

// Возвращает ID языка интерфейса пользователя. Пароль не требуется.
BX_RESULT BX_User_GetLanguage(BX_User_Args& arg);

// !!!
BX_RESULT BX_User_Enumerate(BX_User_Args& arg);
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Функции авторизации                                                       []                   
//                                                                            []
struct BX_Security_Args
{
	BX_Security_Args() {
		VBN		= NA;
		Result	= false;
	}

	READONLY	identifier		VBN;				// ID виртуальной сети, нужен только для авторизации пользователя.
	READONLY	string			Level;			// Кого авторизовать - может принимать одно из 3 значений: "Root", "VBN", "User".

	READONLY	string			Login;			// Логин, для VBN - это имя VBN, для рута - это "Root".
	READONLY	string			Password;		// Пароль.

	READONLY	bool				Result;			// True, если авторизация прошла успешно.
};
//----------------------------------------------------------------------------[] 

// Авторизация пользователей, администраторов системы и VBN.
BX_RESULT BX_Security_Authorize(BX_Security_Args& arg);

//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/