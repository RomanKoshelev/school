/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_VBN.h                                                  []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "Виртуальная баннерная сеть"[]
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                             
#ifndef BX_VBN_H
#define BX_VBN_H

/*______________________________________________________________________________
[]                                                                            []
[]` ObjectState                                                               []           
[]                                                                            */
enum	ObjectState
{
	OBJ_STATE_CHECKED,
	OBJ_STATE_NEW,
	OBJ_STATE_CHANGED_CRITICAL,
	OBJ_STATE_CHANGED
};

//______________________________________________________________________________
// 																									[]
//` VBN																								[]   
// 																									[]
struct BX_VBN_Args
{ 
	BX_VBN_Args()
	{
		DefaultLanguage	= NA;
		DefaultTZOffset	= 0;
		Owner					= NA;
		No						= 255;
		objID					= NA;
		objLanguageNo		= -1;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}

				string			Password;				// Пароль для доступа к настройкам сети.
				string			Name;						// Название сети.
				string			Description;			// Описание сети.

				bool				IsModerated;			// Является ли сеть премодерируемой.

				identifier		DefaultLanguage;		// ID языка сети по умолчанию.
				time_t			DefaultTZOffset;		// Смещение часового пояса по умолчанию (в секундах).

				identifier		Owner;					// Владелец сети, которому идут проценты с показов.

				identifier_arr ConceptMask;			// Массив идентификаторов используемых в сети концептов (если он пуст, то используются все концепты).

	READONLY byte				No;						// Порядковый номер сети.

				identifier		objID;					// Идентификатор объекта.
				int				objLanguageNo;			// Порядковый номер языка, на котором выдаются результаты, по умолчанию равен языку VBN.
				int				objFirstNo;				// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;				// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
	READONLY identifier_arr	objIDs;					// Массив идентификаторов объектов.
	READONLY string_arr		objNames;				// Массив названий объектов.
				string			AdminPassword;			// Пароль администратора.
																
};

// Создание виртуальной баннерной сети.
// На входе нужен пароль владельца сети Password, который будет требоваться 
// для доступа ко всем функциям с данной VBN, а также пароль администратора 
// AdminPassword. В случае создания в objID возвращается идентификатор созданного объекта.
BX_RESULT BX_VBN_New(BX_VBN_Args& arg);

// Изменение параметров виртуальной баннерной сети с идентификатором objID.
// На входе нужен пароль владельца сети Password.
BX_RESULT BX_VBN_PutData(BX_VBN_Args& arg);

// Получение идентификаторов (в objIDs) и названий (objNames)
// всех виртуальных банерных сетей, зарегистрированных в системе.
BX_RESULT BX_VBN_Enumerate(BX_VBN_Args& arg);

// Получение параметров виртуальной баннерной сети с указанным objID.
// Пароль владельца сети передавать не нужно.
BX_RESULT BX_VBN_GetData(BX_VBN_Args& arg);

// Получение идентификаторов (в objIDs) и названий (objNames)
// всех концептов виртуальной банерной сети с идентификатором objID.
BX_RESULT BX_VBN_ConceptEnumerate(BX_VBN_Args& arg);

// Получение идентификатора владельца сети.
// На входе нужен пароль владельца сети Password.
BX_RESULT BX_VBN_GetOwnerID(BX_VBN_Args& arg);

// Удаление виртуальной баннерной сети с указанным идентификатором objID.
// Необходимо передать правильный пароль администратора AdminPassword.
BX_RESULT BX_VBN_Delete(BX_VBN_Args& arg);

// Возвращает в objIDs и objNames идентификаторы и имена 
// объектов, обладающих свойством, указанным  названии функции
// из VBN с id=objID. Необходимо указать пароль для виртуальной сети Password.
BX_RESULT BX_VBN_UserEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_BannerEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_SiteEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_BannerProfileEnumerate         (BX_VBN_Args& arg);
BX_RESULT BX_VBN_SiteProfileEnumerate           (BX_VBN_Args& arg);

BX_RESULT BX_VBN_UnallowedUserEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedSiteEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedSiteProfileEnumerate	(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedBannerEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedBannerProfileEnumerate(BX_VBN_Args& arg);

BX_RESULT BX_VBN_NewUserEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewSiteEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewSiteProfileEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewBannerEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewBannerProfileEnumerate		(BX_VBN_Args& arg);

BX_RESULT BX_VBN_ChangedUserEnumerate           (BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedSiteEnumerate				(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedSiteProfileEnumerate		(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedBannerEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedBannerProfileEnumerate	(BX_VBN_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/