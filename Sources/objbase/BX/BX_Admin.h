/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Admin.h                                                []
[] Date:            24.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Интерфейсные функции для администратора                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                               
#ifndef BX_Admin_H
#define BX_Admin_H


//----------------------------------------------------------------------------[]

struct	BX_Admin_Args
{
	string	Password;							// Пароль администратора.
	string	MemoryManagerReport;				// Отчет диспетчера памяти.
	string	Result;								// 
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

// Получение отчета диспетчера памяти. Требуется пароль администратора.
BX_RESULT	BX_Admin_MemoryManagerReport(BX_Admin_Args& arg);
//____________________________________________________________________________[]

struct	BX_ConceptRate_Args
{
	BX_ConceptRate_Args()
	{
		objID				= NA;
		objLanguageNo	= 0;
	}

	string_arr	CRA_Name;		// Названия концептов, имеющихся в абсолютном распределении.
	int_arr		CRA_Value;		// Значения абсолютного распределения.
	int_arr		CRA_Max;			// Максимальное значение абсолютного распределения.
	int_arr		CRA_Min;			// Минимальное значение абсолютного распределения.
	int_arr		CRA_Sum;			// Суммарное значение абсолютного распределения.
										
	string_arr	CRN_Name;		// Названия концептов, имеющихся в нормализованном распределении.
	int_arr		CRN_Value;		// Значения нормализованного распределения.
	int_arr		CRN_Level;		// Уровни концептов из CRN_Name.

	int_arr		TypeNums;		// Номера типов концептов, которые хотелось бы увидеть в распределении.
	identifier	objID;			// ID объекта.
	int			objLanguageNo;	//	Номер языка, на котором будут выведены названия концептов (по умолчанию - 0).

};
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

// Получить распределение концептов для аудитории интернета.
BX_RESULT	BX_ConceptRate_Reg_InetAudience(BX_ConceptRate_Args& arg);
// Получить распределение концептов посетителей сайта.
BX_RESULT	BX_ConceptRate_Site_Visitor(BX_ConceptRate_Args& arg);
// Получить распределение концептов зрителя.
BX_RESULT	BX_ConceptRate_Viewer_Site(BX_ConceptRate_Args& arg);
// Получить распределение анкетных концептов зрителя.
BX_RESULT	BX_ConceptRate_Viewer_Inquiry(BX_ConceptRate_Args& arg);

//____________________________________________________________________________[]

bool CheckAdminPassword(const string& Password);
void GetAdminPassword(string& Password);

//----------------------------------------------------------------------------[]

BX_RESULT BX_Admin_SaveBXObjects(BX_Admin_Args& arg);

BX_RESULT BX_Admin_GetObjectNum(BX_Admin_Args& arg);

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/