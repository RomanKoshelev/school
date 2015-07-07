/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Concept.h                                              []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Функции для работы с объектом "Концепт"                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                               
#ifndef BX_Concept_H
#define BX_Concept_H


//______________________________________________________________________________
// 																									[]
//` Concept																							[] 	 
// 																									[]

struct BX_Concept_Args
{ 
	BX_Concept_Args()
	{
		Parent			= NA;
		Level				= -1;
		TypeNo			= -1;
		No					= -1;
		objID				= NA;
		objLanguageNo	= -1;
		objFirstNo		= 0;
		objLastNo		= INT_MAX;
		SiteCount		= 0;
		Indent			= false;
		VBN				= NA;
	}

	READONLY identifier		Parent;			// Id родителя - по идее должен быть равен NA только у корня дерева
				string_arr		Name; 			// Массив названий концепта на всех языках, имеющихся в системе.
				string_arr		Description;	// Массив описаний концепта на всех языках, имеющихся в системе.
	READONLY int				Level;			// Уровень концепта в дереве тематической иерархии.
				string_arr		ConceptType;	// Тип концепта (для Extended Enumerate).
	READONLY int				No;				// Порядковый номер концепта - используется для BX_Concept_GetData.
				string			ShortName;		// Сокращённое имя.
				string			Type;				// Тип концепта.
				int				TypeNo;			// Номер типа концепта.
				int				objLanguageNo;	// Порядковый номер языка, на котором выдаются результаты функцией *Enumerate().
				int				objFirstNo;		// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
				int				objLastNo;		// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

				int				SiteCount;		// Кол-во сайтов с данной концептом.
				bool				Indent;
				identifier		VBN;				// Идентификатор виртуальной сети.
				identifier		objID;			// Идентификатор объекта.
				int_arr			objNums;			// Массив номеров объектов.
	READONLY identifier_arr objIDs;			// Массив идентификаторов объектов.
	READONLY string_arr		objNames;		// Массив названий объектов на языке с номером objLanguageNo.
				string			AdminPassword;	// Пароль администратора.
};
//----------------------------------------------------------------------------[] 

// Создание концепта.
// В случае создания идентификатор созданного концепта возвращается в objID.
BX_RESULT BX_Concept_New(BX_Concept_Args& arg);

// Модификация параметров существующего концепта с идентификатором objID.
BX_RESULT BX_Concept_PutData(BX_Concept_Args& arg);

// Получение идентификаторов всех концептов на языке # objLanguageNo
// методом 'в ширину', т.е. в порядке возрастания уровня.
BX_RESULT BX_Concept_Enumerate(BX_Concept_Args& arg);

// Получить список идентификаторов и названий концептов заданного уровня на 
// заданном языке с возможными отступами в соответствии с уровнем.
// Концепты выводятся 'в глубину', т.е. в порядке следования родителей.
// Если указан Level, то выводятся концепты с уровнем до Level включительно,
// иначе - все концепты.
// Если указан objLanguage, то он определяет язык концепта, иначе язык равен языку
// VBN, иначе - нулевому языку.
// Если указан VBN, то выводятся концепты заданной VBN.
// Если SiteCount > 0, то к имени концепта добавляется количество сайтов с 
// данным концептом, причем если указана VBN, то сайтов в данной VBN.
// Если Indent == true, то перед именем концепта вставляется нужное
// количество отступов в html-формате.
BX_RESULT BX_Concept_ExtendedEnumerate(BX_Concept_Args& arg);

// Получение информации о концепте с указанным идентификатором objID.
BX_RESULT BX_Concept_GetData(BX_Concept_Args& arg);

// Удаление концепта с указанным идентификатором objID.
// Все потомки концепта также удаляются.
BX_RESULT BX_Concept_Delete(BX_Concept_Args& arg);

// Получить кол-во сайтов с данным концептом для указанного VBN.
// Если vbn не указан или не валидный, то выдается информация по всем VBN.
BX_RESULT BX_Concept_GetSiteCount(BX_Concept_Args& arg);


// Удаляет id сайта из списков сайтов сети idVBN для концепта из массива conceptIDs.
BX_RESULT BX_Concept_DeleteSite(const identifier_arr& idConcept, identifier idSite, identifier idVBN);

// Добавляет id сайта в списки сайтов из сети idVBN для концепта из массива conceptIDs.
BX_RESULT BX_Concept_AddSite(const identifier_arr& idConcept, identifier idSite, identifier idVBN);

//----------------------------------------------------------------------------[] 

BX_RESULT ExpandConcept					(identifier_arr &concept_arr);
BX_RESULT ExpandWithParentConcepts	(identifier_arr &concept_arr);

BX_RESULT
BX_Concept_GetPackedWeights (const identifier_arr	&ConceptIDs, int_arr &ConceptRate);

void
ConceptPack(int_arr&					ConceptRate,
				int_arr&					AddedConceptNo,
				int						No,
				int						Increment);


//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` _IDsToBits_Set                                                            []          
//                                                                            []
// Битовый массив предварительно ОЧИЩАЕТСЯ.												[]
#define _IDsToBits_Set(idArr, bitArr)														\
{																										\
	bitArr.Erase();																				\
	int ITBS_idSize = idArr.Size();															\
	int ITBS_i,ITBS_j;																			\
	int ITBS_addLen;																				\
	int ITBS_byteNo;																				\
	int ITBS_nPos;																					\
	int ITBS_posArr;																				\
																										\
	for (ITBS_i=0; ITBS_i < ITBS_idSize; ITBS_i++)										\
	{																									\
		if ((ITBS_posArr = oc_reg.m_ConceptID_Sorted.Find(idArr[ITBS_i], true)) < 0)\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"_IDsToBits_Set: Unregistered concept with id #%lu. Skipped.",		\
				(unsigned long)idArr[ITBS_i]);												\
			continue;																				\
		}																								\
		ITBS_nPos = oc_reg.m_ConceptNo_SortID[ITBS_posArr];							\
		ITBS_byteNo = ITBS_nPos >> 3;															\
		ITBS_addLen = ITBS_byteNo - (bitArr).Size();										\
		for (ITBS_j=0; ITBS_j <= ITBS_addLen; ITBS_j++) (bitArr).Add(0);			\
		(bitArr)[ITBS_byteNo] |= BitMask[ITBS_nPos % 8];								\
	}																									\
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` _IDsToBits_Or                                                             []          
//                                                                            []
// Битовый массив предварительно НЕ ОЧИЩАЕТСЯ.											[]
#define _IDsToBits_Or(idArr, bitArr)														\
{																										\
	int ITBS_idSize = idArr.Size();															\
	int ITBS_i,ITBS_j;																			\
	int ITBS_addLen;																				\
	int ITBS_byteNo;																				\
	int ITBS_nPos;																					\
	int ITBS_posArr;																				\
																										\
	for (ITBS_i=0; ITBS_i < ITBS_idSize; ITBS_i++)										\
	{																									\
		if ((ITBS_posArr = oc_reg.m_ConceptID_Sorted.Find(idArr[ITBS_i], true)) < 0)\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"_IDsToBits_OrNot: Unregistered concept with id #%lu. Skipped.",	\
				(unsigned long)idArr[ITBS_i]);												\
			continue;																				\
		}																								\
		ITBS_nPos = oc_reg.m_ConceptNo_SortID[ITBS_posArr];							\
		ITBS_byteNo = ITBS_nPos >> 3;															\
		ITBS_addLen = ITBS_byteNo - (bitArr).Size();										\
		for (ITBS_j=0; ITBS_j <= ITBS_addLen; ITBS_j++) (bitArr).Add(0);			\
		(bitArr)[ITBS_byteNo] |= BitMask[ITBS_nPos % 8];								\
	}																									\
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` _IDsToBits_OrNot                                                          []                
//                                                                            []
#define _IDsToBits_OrNot(idArr, bitArr)													\
{																										\
	int ITBS_idSize = idArr.Size();															\
	int ITBS_i,ITBS_j;																			\
	int ITBS_addLen;																				\
	int ITBS_byteNo;																				\
	int ITBS_nPos;																					\
	int ITBS_posArr;																				\
																										\
	for (ITBS_i=0; ITBS_i < ITBS_idSize; ITBS_i++)										\
	{																									\
		if ((ITBS_posArr = oc_reg.m_ConceptID_Sorted.Find(idArr[ITBS_i], true)) < 0)\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"_IDsToBits_OrNot: Unregistered concept with id #%lu. Skipped.",	\
				(unsigned long)idArr[ITBS_i]);												\
			continue;																				\
		}																								\
		ITBS_nPos = oc_reg.m_ConceptNo_SortID[ITBS_posArr];							\
		ITBS_byteNo = ITBS_nPos >> 3;															\
		ITBS_addLen = ITBS_byteNo - (bitArr).Size();										\
		for (ITBS_j=0; ITBS_j <= ITBS_addLen; ITBS_j++) (bitArr).Add(0);			\
		(bitArr)[ITBS_byteNo] |= byte(BitMaskNot[ITBS_nPos % 8]);					\
	}																									\
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` _IDsToBits_Clear                                                          []          
//                                                                            []
// Этот макрос сбрасывает в байтовом массиве bitArr биты, соответствующие  	[]
// идентификаторам из массива idArr. Номер бита, соответствующий объекту, 	   []
// определяется из поля OC_Name::m_No контроллера, который должен иметь      	[]
// индекс по этому полю. Битовый массив предварительно НЕ очищается.      	   []
#define _IDsToBits_Clear(idArr, bitArr)													\
{																										\
	int ITBC_idSize = idArr.Size();															\
	int ITBC_i;																						\
	int ITBC_byteNo;																				\
	int ITBC_nPos;																					\
	int ITBC_posArr;																				\
																										\
	for (ITBC_i=0; ITBC_i < ITBC_idSize; ITBC_i++)										\
	{																									\
		if ((ITBC_posArr = oc_reg.m_ConceptID_Sorted.Find(idArr[ITBC_i], true)) < 0)\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"_IDsToBits_Clear: Unregistered concept with id #%lu. Skipped.",	\
				(unsigned long)idArr[ITBC_i]);												\
			continue;																				\
		}																								\
		ITBC_nPos = oc_reg.m_ConceptNo_SortID[ITBC_posArr];							\
		ITBC_byteNo = ITBC_nPos >> 3;															\
		if (ITBC_byteNo < (bitArr).Size();													\
			(bitArr)[ITBC_byteNo] &= byte(BitMaskNot[ITBC_nPos % 8]);				\
	}																									\
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` _BitsToIDs                                                                []          
//                                                                            []
// Этот макрос заносит в массив idArr идентификаторы объектов класса OC_Name,	[]
// соответствующие установленным битам из байтового массива bitArr.           []
#define _BitsToIDs(idArr,bitArr)																\
{																										\
	idArr.Delete();																				\
	int BTI_byteSize = bitArr.Size();														\
	int BTI_MaxNo	= oc_reg.m_ConceptID_SortNo.Size();									\
	int BTI_i, BTI_j, BTI_pos;																	\
	const byte * BTI_bytePtr = bitArr.GetPtr();											\
/*По всем байтам:	*/																				\
	for (BTI_i = 0; BTI_i < BTI_byteSize; BTI_i++) 										\
		if (BTI_bytePtr[BTI_i] != 0)															\
		/*По всем битам:	*/																		\
			for (BTI_j = 0; BTI_j < 8; BTI_j++)												\
				if ((int(BTI_bytePtr[BTI_i]) & BitMask[BTI_j]) != 0)					\
				{																						\
					BTI_pos = BTI_i*8+BTI_j;													\
					if (BTI_MaxNo > BTI_pos)													\
						idArr.Add(oc_reg.m_ConceptID_SortNo[BTI_pos]);					\
					else																				\
						SERVER_DEBUG_ERROR_1(													\
							"_BitsToIDs: Too large concept no (%d). Skipped",			\
							BTI_pos);																\
				}																						\
}
//----------------------------------------------------------------------------[]`


//______________________________________________________________________________
//                                                                            []
//` ViewerParamsToConcepts                                                    []
//                                                                            []
// Возвращает номер концепта типа ConceptType 3го уровня с аббревиатурой		[]
// ViewerParam, создавая новый концепт в случае необходимости.						[]
// Возвращает -1 в случае ошибочного типа ConceptType или в случае ошибки		[]
// создания концепта.																			[]
//----------------------------------------------------------------------------[]`

int ViewerParamsToConcepts(const char * ConceptType, const string& ViewerParam);

//______________________________________________________________________________
//                                                                            []
//` Concept_IncreaseRate                                                      []                    
//                                                                            []
// Увеличивает значение распределения, соответствующего концепту с номером		[]
// No, на величину Increment.																	[]
// При необходимости этот номер добавляется.
// Возвращает индекс для этого концепта в распределении.
int
ConceptRate_Increase(int No, int Increment, int_arr& RateArr);


//______________________________________________________________________________
//                                                                            []
//` Concept_IsFind                                                            []             
//                                                                            []
// Возвращает индекс элемента распределения из массива RateArr,
// соответствующего номеру No, или -1, если такого нет.
int
BX_ConceptRate_Find(int No, const int_arr& RateArr, int StartNo = 0);

//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` Concept_PrepareForPrinting                                                []                          
//                                                                            []
BX_RESULT
BX_Concept_PrepareForPrinting(const int_arr&	RateArr,
										const int_arr&	TypeArr,
										int				LanguageNo,
										string_arr&		Names,
										int_arr&			Rates,
										int_arr&			Levels
										);
//____________________________________________________________________________[]

//----------------------------------------------------------------------------[]

// Возвращает номера типов концептов и их названия.
BX_RESULT BX_Concept_TypeEnumerate(BX_Concept_Args& arg);

// Удаляет из распределения CR концепты с типами из Types[].
BX_RESULT BX_Concept_FilterType(int_arr& CR, const int_arr& Types);

// Установить фильтрующиеся типы концептов для зрителя.
BX_RESULT BX_Concept_SetFilter(BX_Concept_Args& arg);

// Получить фильтрующиеся типы концептов для зрителя.
BX_RESULT BX_Concept_GetFilter(BX_Concept_Args& arg);

//----------------------------------------------------------------------------[]
#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/