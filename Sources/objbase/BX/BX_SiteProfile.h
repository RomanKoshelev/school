/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_SiteProfile.h                                          []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "профиль сайта".            []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                     
#ifndef BX_SiteProfile_H
#define BX_SiteProfile_H


//______________________________________________________________________________
//                                                                            []
//` SiteProfile                                                               []           
//                                                                            []

struct BX_SiteProfile_Args
{
	BX_SiteProfile_Args()
	{
		VBN				= NA;
		LastModified	= 0;
		OwnerID			= NA;
		UseKeywords		= false;
		Allowed			= false;
		MaxFileSize		= 0;
		ObjectState		= 1;
		objID				= NA;
		objFromID		= NA;

		objFirstNo		= 0;
		objLastNo		= INT_MAX;
	}
				string			Name;						// Название профиля.
	READONLY	identifier_arr Site;						// ID сайтов, пользующихся данным профилем.
	READONLY	string_arr		sSite;					// Имена сайтов, пользующихся данным профилем.
	READONLY	identifier		VBN;						// ID виртуальной подсети.
	READONLY	time_t			LastModified;			// Время последнего изменения профиля.
	READONLY	string			sLastModified;			// Время последнего изменения профиля в строковом представлении.
	READONLY	identifier		OwnerID;					// Идентификатор пользователя-владельца.

// Разрешённые/запрещённые баннеры:
				identifier_arr BannerInclude;			// Список разрешённых к показу баннеров.
				identifier_arr BannerExclude;			// Список запрещённых к показу баннеров.
				identifier_arr SiteInclude;			//	Список разрешённых к рекламе сайтов.
				identifier_arr SiteExclude;			//	Список запрещённых к рекламе сайтов.

// Требования к баннерам :
				int				MaxFileSize;			// Максимальный размер файла с баннерами.
				bool				UseKeywords;			// Показывать баннеры в соответствии с ключевыми словами сайтов.

				identifier_arr	BannerConceptInclude;// Список разрешённыx к показу концептов ресурсов.
				identifier_arr	BannerConceptExclude;// Список запрещённых к показу концептов ресурсов.

	READONLY	bool				Allowed;					// Информация пользователя разрешена модератором.
	READONLY	int				ObjectState;			// Состояние объекта: 0 - проверен; 1 - новый;  2 - изменено критическое поле; 3 - изменён.
	READONLY	identifier_arr	ModeratorComment;		// Комментарии модератора.

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]

				identifier		objID;					// Идентификатор профиля сайта.
				string			objPassword;			// Пароль пользователя-владельца объекта.
																
	READONLY	identifier		objFromID;				// Идентификатор source-профиля.

				int				objFirstNo;				// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;				// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
																
	READONLY	identifier_arr	objIDs;					// Идентификаторы объектов.
	READONLY	string_arr		objNames;				// Здесь возвращаются имена функциями *Enumerate().
};
//----------------------------------------------------------------------------[]

// Создаёт профиль сайта для пользователя с идентификатором OwnerID.
// Если указан objFromID , то в созданный профиль копируются
// параметры из профиля с идентификатором objFromID.
// В objID возвращается id созданного профиля.
// В Name возвращается название созданного профиля.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_SiteProfile_New(BX_SiteProfile_Args& arg);

//	Копирование установок профиля сайта из профиля objFromID в профиль objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_SiteProfile_CopyData(BX_SiteProfile_Args& arg);

//	Получение установок профиля сайта с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_SiteProfile_GetData(BX_SiteProfile_Args& arg);

//	Изменение установок профиля сайта с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_SiteProfile_PutData(BX_SiteProfile_Args& arg);

//	Удаление установок профиля сайта с указанным ID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_SiteProfile_Delete(BX_SiteProfile_Args& arg);

// !!!
BX_RESULT BX_SiteProfile_Enumerate(BX_SiteProfile_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/