/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Banner.h                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "баннер".					      []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#ifndef BX_Banner_H
#define BX_Banner_H

//______________________________________________________________________________
//                                                                            []
//` Banner                                                                    []      
//                                                                            []

// Структура для получения/изменения параметров баннера.
struct BX_Banner_Args
{
	BX_Banner_Args()
	{
		OwnerID				= NA;
		FileSize				= 0;
		UploadNo				= 0;
		VBN					= NA;
		Profile				= NA;
		CreationTime		= 0;
		TotalShows			= 0;
		TotalClicks			= 0;
		Allowed				= false;
		State					= true;
		ObjectState			= 1;
		objID					= NA;

		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}

	READONLY	identifier		OwnerID;				// Идентификатор владельца баннера.
	READONLY	string			FileName;			// Имя баннера, с котором происходил upload.
	READONLY	int				FileSize;			// Размер файла баннера.
				int				UploadNo;			// Количество повторных загрузок сайта.
															
	READONLY	time_t			CreationTime;		// Время создания объекта.
	READONLY	string			sCreationTime;		// Время создания объекта текстовом виде.
	READONLY	identifier		VBN;					// ID виртуальной сети, к которой принадлежит баннер.
															
				bool				State;				// Состояние баннера (выкл/вкл).
															
				identifier		Profile;				// Идентификатор профиля баннера.
															
				identifier_arr	Concept;				// Концепты, имеющие отношение к баннеру.
															
	READONLY	int				TotalShows;			// Количество показов баннера.
	READONLY	int				TotalClicks;		// Количество нажатий на баннер.
															
	READONLY	bool				Allowed;				// Информация пользователя разрешена модератором.
	READONLY	int				ObjectState;		// Состояние объекта: 0 - проверен; 1 - новый; 2 - изменено критическое поле; 3 - изменён.

	READONLY	identifier_arr	ModeratorComment;	// Комментарии модератора.
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
				identifier		objID;				// Идентификатор объекта баннера.
				string			objPassword;		// Пароль пользователя-владельца баннера.

				int				objFirstNo;			// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;			// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.
															
	READONLY	identifier_arr	objIDs;				// Идентификаторы объектов.
	READONLY	string_arr		objNames;			// Здесь возвращаются имена функциями *Enumerate().
};
//----------------------------------------------------------------------------[]

// Создание баннера. Требуется OwnerID владельца и FileName баннера.
// Идентификатор созданного баннера возвращается в objID. 
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Banner_New(BX_Banner_Args& arg);

// Получение параметров баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Banner_GetData(BX_Banner_Args& arg);

// Изменение параметров баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Banner_PutData(BX_Banner_Args& arg);

// Удаление баннера с указанным objID.
// Необходимо указать пароль пользователя-владельца objPassword.
BX_RESULT BX_Banner_Delete(BX_Banner_Args& arg);

// !!!
BX_RESULT BX_Banner_Enumerate(BX_Banner_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/