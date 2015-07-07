/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Rating.cpp                                             []
[] Date:            01.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_TimeStats
#define USES_BX_Concept
#define USES_BX_SingleObject
#define USES_BX_Rating

#define USES_OC_Registry
#define USES_OC_ShowEvent
#define USES_OC_Site
#define USES_OC_SiteProfile
#define USES_OC_Language
#define USES_OC_VBN

#include "BX.h"
//----------------------------------------------------------------------------[]

bool		IndexSetInitialized = false;



//______________________________________________________________________________
//                                                                            []
//` GetSiteIndexInfo                                                          []                
//                                                                            []
// Получить идентификаторы индексов и указатели на соответствующие поля 
// счётчиков сайта.
// Вход:		1. Название ключевого индекса KeyIndexName
//				2. Массив названий остальных индексов IndicesNames
// Выход:	1. Идентификатор ключевого индекса KeyIndexID
//				2. Массив идентификаторов остальных индексов IndicesIDs
//				3. Массив указателей на соответствующие поля счётчиков сайта
//					для остальных индексов CounterArr
//				4. Идентификаторы индексов по имени (NameIndexID) и времени
//					создания (CreationTimeIndexID) (они являются 
//					исключительными в том плане, что не является обратными).
void GetSiteIndexInfo(	const string&					KeyIndexName,
								const string_arr&				IndicesNames,
										identifier&				KeyIndexID,
										identifier_arr&		IndicesIDs,
										CPtr<pSiteCounter>&	CounterArr,
										identifier&				NameIndexID,
										identifier&				CreationTimeIndexID)
{
	int	i;
	int	FindPos;

// Очистка выходных аргументов:
	IndicesIDs.Delete();
	CounterArr.Delete();

//----------------------------------------------------------------------------[] 
// Заполнение выходных аргументов:


// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//	NameIndexID
	if ((FindPos = theBX_SingleObject.AllSiteIndexNames.Find("Name", true)) != -1) {
		NameIndexID = theBX_SingleObject.AllSiteIndexIDs[FindPos];
	}
	else	{
		SERVER_DEBUG_ERROR ("GetSiteIndexInfo(): Unsupported 'Name' index.");
		NameIndexID = NA;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// CreationTimeIndexID
	if ((FindPos = theBX_SingleObject.AllSiteIndexNames.Find("CreationTime", true)) != -1) {
		CreationTimeIndexID = theBX_SingleObject.AllSiteIndexIDs[FindPos];
	}
	else	{
		SERVER_DEBUG_ERROR ("GetSiteIndexInfo(): Unsupported 'CreationTime' index.");
		CreationTimeIndexID = NA;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// KeyIndexName
	if ((FindPos = theBX_SingleObject.AllSiteIndexNames.Find(KeyIndexName, true)) != -1)
	{
		KeyIndexID = theBX_SingleObject.AllSiteIndexIDs[FindPos];
	}
	else	{
		SERVER_DEBUG_ERROR_1 ("GetSiteIndexInfo(): Unsupported key index: '%s'. Set to NA...", KeyIndexName.c_str());
		KeyIndexID = NA;
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// IndicesIDs, CounterArr
	for (i = 0; i < IndicesNames.Size(); i++) 
	{
		if ((IndicesNames[i] == "Name") || (IndicesNames[i] == "CreationTime"))	{
			SERVER_DEBUG_ERROR ("GetSiteIndexInfo(): 'Name' or 'Creation Time' requested as non-key indices! Skipped.");
			continue;
		}

		if ((FindPos = theBX_SingleObject.AllSiteIndexNames.Find(IndicesNames[i], true)) != -1)
		{
			IndicesIDs.Add(theBX_SingleObject.AllSiteIndexIDs		[FindPos]);
			CounterArr.Add(theBX_SingleObject.AllSiteIndexFields	[FindPos]);
		}
		else {
			SERVER_DEBUG_ERROR_1 ("GetSiteIndexInfo(): Unsupported index: '%s'. Skipped.", IndicesNames[i].c_str());
		}
	}

	return;
}
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]
#define	GOTO_NEXT_SITE																			\
		if (arg.Ascending)																		\
		{																								\
			oc_site.GoPrev(&ka);																	\
		}																								\
		else																							\
		{																								\
			oc_site.GoNext(&ka);																	\
		}
//----------------------------------------------------------------------------[]
								
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_RateStats_Site                                                         []                 
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_RateStats_Site		(BX_RateStats_Args& arg)
{
	static char * MONTH[] = {"янв", "фев", "мар", "апр", "май", "июн", "июл", "авг", "сен", "окт", "ноя", "дек"};

	int	i	=	0;
	int	j	=	0;


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 24.01.2000 by AlexV
	printf("\nFirstPos: %d", arg.FirstPos);
	printf("\nLastPos:  %d", arg.LastPos);
	printf("\nKeyIndex: %s", arg.KeyIndex.c_str());
	for (i=0; i<arg.Indices.Size(); i++) 
		printf("\n  Indices[%d]: %s", i, arg.Indices[i].c_str());
	for (i=0; i<arg.Concept.Size(); i++) 
		printf("\n  Concept[%d]: %lu", i, arg.Concept[i]);
#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *


// Очистка выходных массивов:
	arg.RawTable.		Delete();
	arg.Total.			Delete();
	arg.SubTotal.		Delete();


// Работа над ошибками:
	if (!OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN)) return BXE_RateStats_InvalidVBN;

	if (arg.FirstPos < 0)							arg.FirstPos	= 0;
	if (arg.LastPos < arg.FirstPos)				arg.LastPos		= arg.FirstPos + 20;
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.Concept);
//----------------------------------------------------------------------------[] 
// Получить нужные идентификаторы индексов и указтели на счётчики сайта:

	identifier				KeyIndexID = NA;
	identifier_arr			IndicesIDs;
	CPtr<pSiteCounter>	CounterArr;

	identifier				NameIndexID				= NA;
	identifier				CreationTimeIndexID	= NA;

	GetSiteIndexInfo(	arg.KeyIndex,
							arg.Indices,
							KeyIndexID,
							IndicesIDs,
							CounterArr,
							NameIndexID,
							CreationTimeIndexID);

	if (KeyIndexID == NA)
	{
		SERVER_DEBUG_ERROR_1 ("BX_RateStats_Site(): Invalid key index: '%s'. Aborted.", arg.KeyIndex.c_str());
		return BXE_RateStats_InvalidKeyIndex;
	}
//----------------------------------------------------------------------------[] 
// Update и определение параметров VBN:

// Положить в ключ номер VBN:
	OC_VBN		oc_vbn;
	oc_vbn.Open(arg.VBN);
	
	key_arr		ka;
	ka += (byte)oc_vbn.m_No;


// Определить язык VBN:
	bool			bRussianDate = false;
	if (oc_vbn.m_DefaultLanguage != NA)
	{
		OC_Language		oc_language;
		BX_CHECK_AND_OPEN(oc_language, oc_vbn.m_DefaultLanguage, OBJ_CLASS_ID_Language);
		if (oc_language.m_ShortName == "RUS") {
			bRussianDate = true;
		}
	}

// Update счётчиков VBN:
	BX_TimeStats_Args	time_stats_args;
	time_stats_args.timer = time_0;
	BX_ASSERT_RETURN(BX_TimeStats_CreateArgs(time_stats_args));
	UPDATE_VBN_COUNTER_W_LASTSYNC(Hits);
	UPDATE_VBN_COUNTER_W_LASTSYNC(Hosts);
	UPDATE_VBN_COUNTER_W_LASTSYNC(Shows);
	UPDATE_VBN_COUNTER_W_LASTSYNC(Clicks);

//----------------------------------------------------------------------------[] 
// Вернуть кол-во сайтов в VBN:

	OC_Site				oc_site;
	oc_site.SetIndex_VBN_Allowed_ObjectState();
	arg.VBNTotalObjects = oc_site.GetIndexTotalNum(ka);

	OC_SiteProfile		oc_site_profile;
//----------------------------------------------------------------------------[] 
// Вернуть кол-во активных (имеющих хиты за последний месяц) сайтов в данной VBN:
	oc_site.SetIndex_VBN__LM_Hits();
	ka += 0;				// нет хитов за последний месяц
	arg.VBNTotalObjectsAct = arg.VBNTotalObjects - oc_site.GetIndexTotalNum (ka);

	ka.Init();
	ka += (byte)oc_vbn.m_No;

//----------------------------------------------------------------------------[] 
// Инициализация объекта сайта в соответствии с ключевым индексом:
	
// Установить у сайта ключевой индекс:
	oc_site.SetIndex(	KeyIndexID );

// Перейти на первую из запрошенных позиций по индексу:
   if (arg.Ascending == true) // По возрастанию:
   {
      if ((KeyIndexID != NameIndexID) && (KeyIndexID != CreationTimeIndexID))
		{
			ka += INT_MIN;
			oc_site.Find (ka, true); 
		}
		else
		{
			oc_site.Find (ka);
		}
   }
	else								// По убыванию:
	{
      if ((KeyIndexID != NameIndexID) && (KeyIndexID != CreationTimeIndexID))
		{
			oc_site.Find (ka);
		}
		else
		{
			oc_site.GoLast();
			if (oc_site.m_VBN != oc_vbn.m_No)
			{
				oc_site.GoPrev(&ka);
			}
		}
	}

	ka.Init();
	ka += (byte)oc_vbn.m_No;
//----------------------------------------------------------------------------[] 
// Инициализация тематического фильтра:

	byte_arr bits_ReqConcepts;
	ExpandConcept(arg.Concept);
	_IDsToBits_Set( arg.Concept, bits_ReqConcepts);

	bool	RootConceptSelected = false;
	if (oc_reg.m_ConceptID_SortNo.Size() > 0)
	{
		if (arg.Concept.Find(oc_reg.m_ConceptID_SortNo[0]) != -1)
			RootConceptSelected = true;
	}

//----------------------------------------------------------------------------[] 
// Изменить направление сортировки, для индексов, не являющихся обратными:
   if ((KeyIndexID == NameIndexID) || (KeyIndexID == CreationTimeIndexID)) {
		arg.Ascending = !arg.Ascending;
	}

//----------------------------------------------------------------------------[] 
// Проходим по всем сайтам VBN и собираем удовлетворяющие фильтрам сайты:
	identifier_arr FoundSiteIDs;
	
	while (oc_site.IsValid())
	{
		bool	bThatsAll = false;

	// Ищем разрешенный сайт с профилем:
		while (	(oc_site.m_Allowed == false) ||
					(oc_site.m_RateMySite == false) ||
					(oc_site.m_Profile == NA))
		{
			GOTO_NEXT_SITE;
			if (!oc_site.IsValid()) {
				bThatsAll = true;
				break;
			}
		}
	// Если сайы кончились - на выход:
		if (bThatsAll) 	{
			break;
		}

	// Пропустим через тематический фильтр:
		bool	bConceptCheckPassed = false;

		if (arg.Concept.Size() == 0) {
			bConceptCheckPassed = true;
		}
		else if (ba_IsEmpty(oc_site.m_ba_Concept.GetCPtr()) && RootConceptSelected) {
			bConceptCheckPassed = true;
		}
		else if (bitIntersect(	oc_site.m_pba_Concept.GetPtr(), oc_site.m_ba_Concept.GetSize(),
										bits_ReqConcepts.GetPtr(), bits_ReqConcepts.GetSize())) {
			bConceptCheckPassed = true;
		}
	// Пропустим через фильтр времени создания:
		if (bConceptCheckPassed)
		{
			time_t oc_site_m_CreationTime = (time_t)oc_site.m_CreationTime;
			if (oc_site_m_CreationTime>=arg.CreatedAfter && oc_site_m_CreationTime<=arg.CreatedBefore)
			{
				FoundSiteIDs += oc_site.GetObjectID();			
			}
		}

		GOTO_NEXT_SITE;
	}
//----------------------------------------------------------------------------[] 
// Инициализация выходных аргументов:
	OC_ShowEvent	oc_show_event;
	oc_show_event.SetIndex_SiteID_ViewerID();

	string	Str;
	arg.SubTotal.Alloc(IndicesIDs.Size());
	arg.SubTotal.Fill(0);
	arg.Total.Alloc(20);
	arg.Total.Fill(0);

	arg.ReqTotalObjectsAct	= 0;
	arg.ReqTotalObjects		= FoundSiteIDs.GetSize();
	arg.ReqTotal.Alloc (IndicesIDs.Size());
	arg.ReqTotal.Fill  (0);

//----------------------------------------------------------------------------[] 
// Цикл по сайтам с запрошенными позициями в индексе:
	for (i = 0; i < FoundSiteIDs.GetSize(); i++)
	{
		oc_site.Open (FoundSiteIDs[i]);

		arg.ReqTotalObjectsAct += ((int)oc_site.m_LM_Hits > 0 ? 1 : 0);

		if ((i >= arg.FirstPos) && (i <= arg.LastPos))
		{
		// Pos
			Str.Format("%d", i+1);
			arg.RawTable += Str;
		// Изменение места
			Str.Format("+0"); //`!!! пока не реализовано
			arg.RawTable += Str;
		// ID
			Str.Format("%lu", FoundSiteIDs[i]);
			arg.RawTable += Str;
		// CreationTime
			time_t	CreationTime = (time_t)(int)oc_site.m_CreationTime;
			struct tm * gmTime = gmtime (&CreationTime);
			if (bRussianDate)
			{
				Str.Format("%d %s %d", gmTime->tm_mday, MONTH[gmTime->tm_mon], gmTime->tm_year+1900);
			}
			else
			{
				Str.Format("%02d/%02d/%4d", gmTime->tm_mday, gmTime->tm_mon, gmTime->tm_year+1900);
			}
			arg.RawTable += Str;
		// Name
			arg.RawTable += oc_site.m_Name;
		// URL
			arg.RawTable += oc_site.m_URL;
		// Description
			if (arg.WithDescription) arg.RawTable += oc_site.m_Description;
		// Возможность показать статистику
         if (string(oc_site.m_RateStatsViewPassword).Len() > 0)   Str.Format("0");
         else                                                     Str.Format("1");
			arg.RawTable += Str;
		// Online
			ka.Init();
			ka += FoundSiteIDs[i];
			oc_site.m_OnlineVisitors = oc_show_event.GetIndexUniqueNum(ka);
			Str.Format("%d", (int)oc_site.m_OnlineVisitors);
			arg.RawTable += Str;

		// Число возвращаемых строк в таблице:
			arg.ObjectsNum++;
		}

	// Значения по запрошенным индексам:
		for (j = 0; j < IndicesIDs.Size(); j++) 
		{
			int	TempInt = oc_site.*(CounterArr[j]);

			arg.ReqTotal[j] += TempInt;

			if ((i >= arg.FirstPos) && (i <= arg.LastPos))
			{
				Str.Format("%d", TempInt);
				arg.SubTotal[j] += TempInt;
				arg.RawTable += Str;
			}

		} // end for (j
	} // end for (i
//----------------------------------------------------------------------------[] 

// Total по VBN
	int n = 0;
	arg.Total[n++] = oc_vbn.m_Total_Hosts;
	arg.Total[n++] = oc_vbn.m_Total_Shows;
	arg.Total[n++] = oc_vbn.m_Total_Clicks;
	arg.Total[n++] = oc_vbn.m_Total_Hits;
	arg.Total[n++] = oc_vbn.m_LM_Hosts;
	arg.Total[n++] = oc_vbn.m_LM_Shows;
	arg.Total[n++] = oc_vbn.m_LM_Clicks;
	arg.Total[n++] = oc_vbn.m_LM_Hits;
	arg.Total[n++] = oc_vbn.m_LW_Hosts;
	arg.Total[n++] = oc_vbn.m_LW_Shows;
	arg.Total[n++] = oc_vbn.m_LW_Clicks;
	arg.Total[n++] = oc_vbn.m_LW_Hits;
	arg.Total[n++] = oc_vbn.m_LD_Hosts;
	arg.Total[n++] = oc_vbn.m_LD_Shows;
	arg.Total[n++] = oc_vbn.m_LD_Clicks;
	arg.Total[n++] = oc_vbn.m_LD_Hits;
	arg.Total[n++] = oc_vbn.m_LH_Hosts;
	arg.Total[n++] = oc_vbn.m_LH_Shows;
	arg.Total[n++] = oc_vbn.m_LH_Clicks;
	arg.Total[n++] = oc_vbn.m_LH_Hits;

//----------------------------------------------------------------------------[] 
#if 0  //{ RomanVK
	printf("\n\nRawTable:");
	for (i=0; i<arg.RawTable.Size(); i++) 
		printf("\n  %s", arg.RawTable[i].c_str());

	printf("\nObjectsNum: %d", arg.ObjectsNum);
	printf("\nVBNTotalObjects: %d", arg.VBNTotalObjects);

	puts("\n----------------------------------------------\n");
#endif //}
//----------------------------------------------------------------------------[] 


	return BX_OK;
}
//____________________________________________________________________________[]



                                                                 
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/