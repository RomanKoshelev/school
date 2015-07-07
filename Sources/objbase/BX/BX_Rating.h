/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Rating.h                                               []
[] Date:            01.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                               
#ifndef BX_Rating_H
#define BX_Rating_H

/*______________________________________________________________________________
[]                                                                            []
[]` BX_RateStats_Args                                                         []                 
[]                                                                            */
struct	BX_RateStats_Args
{
	BX_RateStats_Args()
	{
		VBN					= NA;
		FirstPos				= 0;
		LastPos				= 0;
		Ascending			= false;
		WithDescription	= true;
		VBNTotalObjectsAct= 0;
		VBNTotalObjects	= 0;
		ReqTotalObjects	= 0;
		ReqTotalObjectsAct= 0;
		ObjectsNum			= 0;
		CreatedAfter		= 0;
		CreatedBefore		= INT_MAX;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Вход:
	identifier		VBN;					// Идентификатор VBN, для объектов которой выводится индекс.
	identifier_arr	Concept;				// Массив концептов объектов.
	int				FirstPos;			// Позиция в рейтинге первого объекта.
	int				LastPos;				// Позиция в рейтинге последнего объекта.
	bool				Ascending;			// Сортировка по возрастанию.
	bool				WithDescription;	// Выдавать ли описания.
	string_arr		Indices;				// Массив названий индексов, значения которых у сайтов надо выдать.
	string			KeyIndex;			// Название индекса, по которому происходит сортировка.
	time_t			CreatedAfter;		// Сайт создан после указанного времени
	time_t			CreatedBefore;		// Сайт создан до указанного времени

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Выход:
	string_arr		RawTable;				// Строковый массив с упакованной рейтинговой таблицей.
	int_arr			Total;					// Всего в VBN по имеющимся у него индексам.
	int_arr			SubTotal;				// Всего в данной группе по запрошенным индексам.
	int_arr			ReqTotal;				// Всего по запрошенным индексам у удовлетворяющих сайтов.
	int				VBNTotalObjects;		// Всего объектов в данной VBN.
	int				VBNTotalObjectsAct;	// Всего активных объектов в данной VBN.
	int				ReqTotalObjects;		// Всего объектов, удовлетворяющих выборке
	int				ReqTotalObjectsAct;	// Всего активных объектов, удовлетворяющих выборке
	int				ObjectsNum;				// Количество объектов, данные по которым упакованы в RawTable.
};
//----------------------------------------------------------------------------[] 

// Получить рейтинговую информацию по сайтам.
BX_RESULT BX_RateStats_Site				(BX_RateStats_Args& arg);
//____________________________________________________________________________[]



#endif   // end of BX_Rating_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/