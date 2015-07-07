/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.cpp													[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Полнотекстовая индексация и поиск с учётом морфологии			[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_FullTextIndex.inc.h"				 



//______________________________________________________________________________
//                                                                            []
//` Исключение объекта из полнотекстового индекса                             []
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Del (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Del);
/*............................................................................[]
		<objGUID						Глобальный идентификатор удаляемого из индекса объекта (guid).
		<objIDs						Идентификаторы удаляемых слов.

		>ExitCode					Код возврата (OK).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]

	RemoveFromFullTextIndex (arg.objGUID, arg.objIDs);

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Включение объекта в полнотекстовый индекс                                 []                                         
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Add (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Add);
/*............................................................................[]
		<objGUID						Глобальный идентификатор индексируемого объекта (guid).
		<StrName						Название индексируемого объекта.
		<StrDescription			Краткое описание индексируемого объекта.
		<StrText						Текстовое содержание индексируемого объекта.
		<StrAdditional				Дополнительная текстовая информация, содержащаяся в индексируемом объекте.
		<Time							Время, под которым объект фигурирует в индексе.

		>objIDs						Идентификаторы использованных при индексировании слов [SearchItemID]
		>ExitCode					Код возврата (OK).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]


	string TotalText = "";
	TotalText += arg.StrName;	  
	TotalText += " ";
	TotalText += arg.StrDescription;
	TotalText += " ";
	TotalText += arg.StrText;
	TotalText += " ";
	TotalText += arg.StrAdditional;

	CreateFullTextIndex (TotalText, arg.objGUID, arg.objIDs, arg.Time);

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` Получение списка объектов, удовлетворяющих поисковому запросу					[]
//                                                                            []
ERR_RESULT FullTextIndex_Enumerate (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (FullTextIndex_Enumerate);
/*............................................................................[]
		<Request						Поисковый запрос.
		<Time0						Допустимое время самых молодых объектов. Начало диапазона. По умолчанию = time(0);
		<Time1						Допустимое время самых старых объектов. Конец диапазона. По умолчанию = (time_t)0;

		>objGUIDs					Список уникальных идентификаторов найденных объектов
		>objTimes					Массив времён обновления в индексах найденных объектов.
		>objWeights					Массив весов-рангов найденных объектов.

		>RequestLemma				Преобразованный поисковый запрос.

		>ExitCode					Код возврата (OK).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]

//	Очищаем входные аргументы
	arg.objGUIDs.Erase ();
	arg.objWeights.Erase ();
	arg.objTimes.Erase ();

// Разбиваем запрос на список лемм
	int				i;
	int				iLemma; (void)iLemma;
	int				iItem;  (void)iItem;
	OC_SearchItem	oc_item;
	lemma_arr		arrLemma;
	GetNormalWordArr (arg.Request, arrLemma, false, true);

	bool bFoundTooMuch = false;

// Информация для ранжирования результатов поиска
	guid_arr		Object_GUID					(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_GUID.Erase();
	time_t_arr	Object_ModificationTime	(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_ModificationTime.Erase();
	int_arr		Object_WordAppearanceNum(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_WordAppearanceNum.Erase();
	int_arr		Object_WordFirstPosition(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_WordFirstPosition.Erase();

// Для каждой лемы находим список объектов, и добавляем его в общий список найденных объектов
	for (iLemma=0; !bFoundTooMuch && iLemma<arrLemma.Size(); iLemma++)
	{
		if (iLemma)		  arg.RequestLemma += ", ";
		arg.RequestLemma += arrLemma[iLemma].Word;

		key_arr ka;
		ka += arrLemma[iLemma].Word;
		if (oc_item.Find (ka)) for (iItem=0; !bFoundTooMuch && iItem<oc_item.m_Text_ObjectSortedGUID.Size(); iItem++)
		{
		// Если найдено слишком много объектов -- вываливаемся
			if (Object_GUID.Size()> MAX_SEARCH_ENUMERATE_NUM)
			{
				bFoundTooMuch = true;
			}

		// Объект удовлетворяет временнОму диапозону
			time_t t = oc_item.m_Text_ModificationTime [iItem];
			if (t>=arg.Time1 && t<=arg.Time0)
			{
			// Запоминаем объект и его характеристики для дальнейшего ранжирования
				Object_GUID						+= oc_item.m_Text_ObjectSortedGUID	[iItem];
				Object_ModificationTime		+= oc_item.m_Text_ModificationTime	[iItem];
				Object_WordAppearanceNum	+= oc_item.m_Text_WordAppearanceNum	[iItem];
				Object_WordFirstPosition	+= oc_item.m_Text_WordFirstPosition	[iItem];
			}
		}
	}

// Объединяем одинаковые объекты и вычисляем вес
	guid_arr arrSortedGUID	(Object_GUID.Size()); arrSortedGUID.Erase();
	int_arr	arrWeight		(Object_GUID.Size()); arrWeight.Erase();
	int_arr	arrTimes			(Object_GUID.Size()); arrTimes.Erase();	
	int_arr	arrLemmaNum		(Object_GUID.Size()); arrLemmaNum.Erase();	
	for (i=0; i<Object_GUID.Size(); i++)
	{
		int index = arrSortedGUID.Find (Object_GUID[i], true);
		int	Weight	= 0;
		if (index == -1)
		{
			index = arrSortedGUID.InsertSorted (Object_GUID[i]);
			arrWeight.Insert		(index, 0);
			arrTimes.Insert		(index, Object_ModificationTime[i]);
			arrLemmaNum.Insert	(index, 1);

		// Чем больше найдено слов, тем выше вес
			Weight += Object_WordAppearanceNum [i];
		// Слово на 10-ой позиции равноценно 10 вхождениям, на 100-ой -- одному вхождению
			Weight += 100 / (Object_WordFirstPosition[i]+1);
		// Запоминаем вес
			arrWeight[index] -= Weight;
		}
		else
		{
			arrLemmaNum[index]++;
		// Чем больше разных слов найдено, тем выше ранг
			arrWeight[index] *= 10;//*arrLemmaNum[index];
		}
//		arrWeight[index] = -arrLemmaNum[index];
	}

//	Ранжируем результат поиска
	guid_arr arrRangedGUID		(arrSortedGUID.Size()); arrRangedGUID.Erase();
	int_arr	arrSortedWeight	(arrSortedGUID.Size()); arrSortedWeight.Erase();
	int_arr	arrResultTimes		(arrSortedGUID.Size()); arrResultTimes.Erase();
	for (i=0; i<arrSortedGUID.Size(); i++)
	{
		int index = arrSortedWeight.InsertSorted (arrWeight[i]);
		arrRangedGUID.Insert (index, arrSortedGUID[i]);
		arrResultTimes.Insert (index, arrTimes[i]);
	}
	
	arg.objGUIDs	= arrRangedGUID;
	arg.objWeights	= arrSortedWeight;
	arg.objTimes	= arrResultTimes;

// Если найдено слишком много объектов
	if (bFoundTooMuch)
	{
		arg.objGUIDs.Realloc		(MAX_SEARCH_ENUMERATE_NUM);
		arg.objWeights.Realloc	(MAX_SEARCH_ENUMERATE_NUM);
		arg.objTimes.Realloc		(MAX_SEARCH_ENUMERATE_NUM);
	}

// Приводим веса к общему знаменателю, учитываем, что веса отрицательные.
	int maxWeight = -1;
	for (i=0; i<arg.objWeights.Size(); i++)	
	{
		arg.objWeights[i] *= -1;
		maxWeight = max (maxWeight, arg.objWeights[i]);
	}
	//printf ("\n\nmaxWeight = %d\n\n", maxWeight);
	for (i=0; i<arg.objWeights.Size(); i++) 
	{
//		printf ("   %6d -->", arg.objWeights[i]);
		arg.objWeights[i]*=10000; arg.objWeights[i]/=maxWeight;
		if (arg.objWeights[i]<0) arg.objWeights[i] = 10000;
//		printf ("%6d\n", arg.objWeights[i]);
	}

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Получение списка объектов, удовлетворяющих поисковому запросу					[]
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Enumerate (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Будут показаны только те объекты, на которые есть права [R].
		<Password					Пароль пользователя, запрашивающего операцию.

		<Request						Поисковый запрос.
		<Time0						Допустимое время самых молодых объектов. Начало диапазона. По умолчанию = time(0);
		<Time1						Допустимое время самых старых объектов. Конец диапазона. По умолчанию = (time_t)0;
		<feodIDs						Список зон доступа, к которым должны относитьсянайденные объекты
		<objFirstNo					Номер объекта, с которого их перечислять.
		<objLastNo					Номер последнего запрашиваемого объекта.
		<nLookAhead					На сколько найденных объектов заглядывать вперёд.[=0]
		<bNeedDescription			Требуется ли описание объектов, или достаточно только имени.

		>objClasses					Массив классов найденных объектов
		>objIDs						Массив идентификаторов найденных объектов.
		>objNames					Массив названий найденных объектов.
		>objDescriptions			Массив описаний найденных объектов (анонсы).
		>objTimes					Массив времён обновления в индексах найденных объектов.
		>objWeights					Массив весов-рангов найденных объектов.
		>objPlacements				Массив объектов, выведенных из феодов, например разделов. Формат: {class|id|name\nclass|id|name, ...}
		>RequestLemma				Преобразованный поисковый запрос.
		>TotalStoredNum			Сколько всего объектов найдено и может быть показано данному пользователю.
		>MaxNumInQuery				Максимально допустимое число запрашиваемых за один раз объектов.

		>ExitCode					Код возврата (OK).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
// Если начало временного диапазона не указано, то используется текущее время
	if (arg.Time0==0)
	{
		arg.Time0 = time(0);
	}
// Феоды должны существовать
	FOR_EACH_ITEM_EVAL (arg.feodIDs, 
	{
		if (!CHECK_FEOD_ID (arg.feodIDs[i])) 
		{
			ERR_RETURN_COMMENT_1 (ERR_BadID, "Указана несуществующая зона доступа ID=%u", arg.feodIDs[i]);
		}
	});

// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_SEARCH_RESULT_ENUMERATE_NUM-1;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_SEARCH_RESULT_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	int i,j;
// Ищем все удовлетворяющие поисковой строке и временному диапазону объекты
	MOD_FullTextIndex_Args arg0;
	arg0.Request	= arg.Request;
	arg0.Time0		= arg.Time0;
	arg0.Time1		= arg.Time1;
	FullTextIndex_Enumerate (arg0);
	if (arg0.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (arg0.ExitCode, arg0.ExitCodeComment);
	}

// Отсеиваем те объекты, к которым нет доступа и которые не относятся к указанным феодам
	string Attributes = "R";
	MOD_CHECK_ACCESS_PLACEMENT	(loginID, arg0.objGUIDs, Attributes, arg.feodIDs, arg.objLastNo+arg.nLookAhead);

// Заполняем выходные аргументы
	for (arg.TotalStoredNum=0, j=0, i=0; i<arg0.objGUIDs.Size(); i++) if (arg0.objGUIDs[i].id!=NA)
	{
		arg.TotalStoredNum ++;
		if (j<arg.objFirstNo || j>arg.objLastNo) 
		{
			j++;
			continue;
		}
		else j++;
		
		arg.objClasses			+= className [arg0.objGUIDs[i].cl];
		arg.objIDs				+= arg0.objGUIDs[i].id;
		arg.objNames			+=	MOD_GET_OBJECT_NAME			(arg0.objGUIDs[i]);
		arg.objDescriptions	+=	MOD_GET_OBJECT_DESCRIPTION (arg0.objGUIDs[i]);
		arg.objTimes			+=	arg0.objTimes[i];
		arg.objWeights			+=	arg0.objWeights[i];
	}
// Выходной запрос
	arg.RequestLemma = arg0.RequestLemma;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/