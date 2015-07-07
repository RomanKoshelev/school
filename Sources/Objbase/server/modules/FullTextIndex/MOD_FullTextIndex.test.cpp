/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.pvt.cpp												[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Полнотекстовая индексация и поиск с учётом морфологии			[]
[]						Тестовые функции															[]
[]____________________________________________________________________________[]
*/
#include "MOD_FullTextIndex.inc.h"



//______________________________________________________________________________
//                                                                            []
//` Создать объекты класса Text                                               []                           
//                                                                            []
void GenerateTexts (const char * sInName, int nMaxWordNum)
{
	DEBUG_STACK_NAME (GenerateTexts);

	int i,j,k,NN,NNN;
	int nText =0;

	string InText;
	InText.ReadFile (sInName);
	NN = InText.Len ();

// Создание текстов
	puts ("\nText generation...");
	OC_Text oc_text;
	oc_text.DeleteClassObjects ();
	byte_arr Txt (max(1024, NN/10));
	for (nText=0, i=0; i<NN; nText ++)
	{
		PRINT_PERCENT (i, NN);
		oc_text.New ();

	// Создаём заголовок текста
		string sName;
		sName.Format ("Text #%05d", nText+1);
		oc_text.m_Name = sName;

	// Создаём тело текста
		NNN = nMaxWordNum;
		bool bPrevIsDelimiter = false;
		for (k=0, j=0; k<NNN && i<NN; j++, i++)
		{
			char C = InText[i];
			Txt[j  ] = C;
			Txt[j+1] = 0;
			bool bIsDelimiter = IsDelimiter (C);
			k += bIsDelimiter && !bPrevIsDelimiter;
			bPrevIsDelimiter = bIsDelimiter;
		}
		oc_text.m_Text = (const char *) Txt.GetPtr();
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` PrintFullTextIndexStatistics																[]
//                                                                            []
void PrintFullTextIndexStatistics ()
{
	DEBUG_STACK_NAME (PrintFullTextIndexStatistics);

	printf ("\n\n\n[]---------------------------------------------[]\n[] STATISTICS:");

	OC_Text oc_text;
	printf ("\n[] Texts            : %6d", oc_text.GetIndexTotalNum ());

	OC_SearchItem oc_item;	   
	printf ("\n[] Normal words     : %6d", oc_item.GetIndexTotalNum ());

	OC_WordNibbleABC oc_nibble;
	printf ("\n[] ABC-like nibbles : %6d", oc_nibble.GetIndexTotalNum ());

	OC_MorphologicRule oc_rule;
	printf ("\n[] Morphologic rules: %6d", oc_rule.GetIndexTotalNum ());

	OC_StopWord oc_stop;
	printf ("\n[] Stop-words       : %6d", oc_stop.GetIndexTotalNum ());

	printf ("\n[]---------------------------------------------[]\n");
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Печать результата поиска                                                  []
//                                                                            []
void PrintFullTextSearchResult (CSearchResult& SearchResult, int nOPS)
{
	DEBUG_STACK_NAME (PrintFullTextSearchResult);

	string	SSS;
	string	StrNormalWords;
	int		i;
	int		nFound = SearchResult.m_ObjectGUIDs.Size();
	for (i=0; i<SearchResult.m_LemmaArr.Size(); i++)
	{
		if (i) StrNormalWords+="|"; 
		StrNormalWords+=SearchResult.m_LemmaArr[i].Word; 
		if (!SearchResult.m_LemmaArr[i].Attr.IsEmpty())
		{
			StrNormalWords+=":";
			StrNormalWords+=SearchResult.m_LemmaArr[i].Attr;
		}
		StrNormalWords+=SearchResult.m_LemmaArr[i].ID==NA?"(?)":"";
	}
	
	SSS.Format ("\n  %3d: %20s->{%s}    %d ops", nFound, SearchResult.m_IniQuery.c_str(), StrNormalWords.c_str(), nOPS);
	SSS.win_2_dos ();
	SSS.Print ();
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//` Тестируем систему словообразования                                        []                                  
//                                                                            []
void TestRules (const char * sInName)
{
	DEBUG_STACK_NAME (TestRules);
	int i,j,N;
	string InText;
	InText.ReadFile (sInName);
	string_arr InTextArr;
	InText.explode (InTextArr);
	N = InTextArr.Size();
	for (i=0; i<N; i++) 
	{
		InTextArr[i].trim();
		if (InTextArr[i].IsEmpty()) continue;
		lemma_arr LemmaArr;
		if (!GetNormalWord (InTextArr[i], LemmaArr, false)) continue;

		string StrDebug;
		string StrTmp;
		StrDebug.Format ("\n---------------------------------\n%s:\n", InTextArr[i].c_str());
		for (j=0; j<LemmaArr.Size(); j++)
		{
			StrTmp.Format ("%4d %-20s", j+1, LemmaArr[j].Word.c_str());
			if (LemmaArr[j].ID==NA) StrTmp+=" (?)";
			StrDebug += StrTmp;
			StrTmp.Format ("     %4.2f", LemmaArr[j].Weight);
			StrDebug += StrTmp;
			StrDebug += "\n";
		}
		StrDebug.win_2_dos();
		StrDebug.Print();
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Скорость нормализации слов                                                []                          
//                                                                            []
void TestNormalizeSpeed (const char * sInName)
{
	DEBUG_STACK_NAME (TestNormalizeSpeed);

	int iText, iWord;
	int nText =0;

	string sText;
	sText.ReadFile (sInName);
	nText = sText.Len ();

// Создание текстов
	puts ("\nConvert word to lemma...");
	char_arr Word (nText/10);

	for (iText=0, iWord=0; iText<nText; iText++)
	{
		PRINT_PERCENT (iText, nText);

	// Разбивка на слова
		Word [0] = 0;
		for (; iText<nText; iText++, iWord++)
		{
			char C = sText[iText];
			if (IsDelimiter (C))
			{
				iWord=0;
				break;
			}
			Word [iWord  ] = C;
			Word [iWord+1] = 0;
		}

	// Выполняем преобразование
		lemma_arr arrLemma;
		bool bRes = GetNormalWord (Word.GetPtr(), arrLemma, false);

	// Отладочная печать
		if (bRes)
		{
#if 0  //{ RomanVK
			string strLemma;
			bool bDigit = false;
			bool bInDict= true;
			for (int iLemma=0; iLemma<arrLemma.Size(); iLemma++)
			{
				if (iLemma) strLemma += ", ";
				strLemma += arrLemma[iLemma].Word;
				if (arrLemma[iLemma].IsDigit) bDigit  = true;
				if (arrLemma[iLemma].ID== NA) bInDict = false;
			}

			string Tmp;
			Tmp.Format ("%s->{%s}\n", Word.GetPtr(), strLemma.c_str());
			Tmp.win_2_dos();
			
			if (!bInDict && !bDigit) 
			{
				Tmp.Print ();
			}
#endif //}
		}
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` FullTextSearch                                                            []              
//                                                                            []
void FullTextSearch (const char * SearchText, CSearchResult& SearchResult)
{
	DEBUG_STACK_NAME (FullTextSearch);

	int				iLemma;
	int				iItem;

	OC_SearchItem	oc_item;

	SearchResult.m_ObjectGUIDs.Erase ();
	SearchResult.m_IniQuery	= SearchText;
	GetNormalWordArr (SearchText, SearchResult.m_LemmaArr, false);
	for (iLemma=0; iLemma<SearchResult.m_LemmaArr.Size(); iLemma++)
	{
		key_arr ka;
		ka += SearchResult.m_LemmaArr[iLemma].Word;
		if (oc_item.Find (ka, false)) for (iItem=0; iItem<oc_item.m_Text_ObjectSortedGUID.Size(); iItem++)
		{
			SearchResult.m_ObjectGUIDs += (guid) oc_item.m_Text_ObjectSortedGUID[iItem];
		}
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` PrintFullTextIndex                                                        []                  
//                                                                            []
void PrintFullTextIndex (const char * sBEG)
{
	key_arr ka;
	ka+=sBEG;
	OC_SearchItem	oc_item;
	oc_item.SetIndex_NormalWord_Hypothesis ();

	if (!oc_item.Find (ka, true)) oc_item.GoFirst ();
	for (; oc_item.IsValid(); oc_item++)
	{
		if (oc_item >= ka)
		{
			if (string(oc_item.m_NormalWord).Find (sBEG)!=0)
			{
				break;
			}
			string StrTmp;
			StrTmp.Format ("\n%s", string(oc_item.m_NormalWord).c_str());
			StrTmp.win_2_dos ();
			StrTmp.Print();
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` TestSearch                                                                []
//                                                                            []
void TestSearch (const char * sInName)
{
	DEBUG_STACK_NAME (TestSearch);
	int i,N;
	string InText;
	InText.ReadFile (sInName);
	string_arr InTextArr;
	InText.explode (InTextArr);
	N = InTextArr.Size();
	for (i=0; i<N; i++) 
	{
		InTextArr[i].trim();
		if (InTextArr[i].IsEmpty()) continue;

		StopWatch sw;
		string NormalWord;

		const char * SearchText = InTextArr[i];
		CSearchResult SearchResult;

	// Поиск и замер времени
		{
		sw.Start ();
			FullTextSearch (SearchText, SearchResult);
		sw.Stop   ();
		}

		PrintFullTextSearchResult (SearchResult, int (1/(sw.GetTime()/1000/1000)));
	}
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//` Полнотекстовая индексация по объектам класса Text									[]
//                                                                            []
void CreateFullTextIndex ()
{
	DEBUG_STACK_NAME (CreateFullTextIndex);

	int i,NN;

	puts ("\nText indexing...");

	OC_Text oc_text;
	NN = oc_text.GetIndexTotalNum ();

	OC_SearchItem oc_item;
	oc_item.SetIndex_NormalWord_Hypothesis ();


// Проходимся по всем текстам
	for (i=0, oc_text.GoFirst(); i<NN && oc_text.IsValid(); oc_text++, i++)
	{
		PRINT_PERCENT (i, NN);
		guid gi = oc_text.GetObjectGUID ();

	// Разбивка на слова и индексирование
		string			oc_text_m_Text  = oc_text.m_Text;
		int				nText = oc_text_m_Text.Len ();
		const char *	sText = oc_text_m_Text;
		int				iText = 0;
		int				iWord = 0;
		int				iLemma= 0;
		string_arr		arrWord;
		int_arr			arrWord_pos;
		char_arr			Word (nText+1);

	// Выделяем слова
		int iPosition=0;
		for (iText=0, iWord=0; iText<nText; iText++)
		{
			Word [0] = 0;
			bool	bHasDigits	= false;
			bool	bHasSymbols	= false;
			for (; iText<nText; iText++, iWord++)
			{
				char C = sText[iText];
				if (IsDelimiter (C))
				{
					iWord=0;
					break;
				}

				if			('a'<=C&&C<='z' || 'а'<=C&&C<='я')		{bHasSymbols=true;				}
				else if	('0'<=C&&C<='9'						)		{bHasDigits =true;				}
				else if	('A'<=C&&C<='Z' || 'А'<=C&&C<='Я')		{bHasSymbols=true;	C += 32;	}
				else if	(C=='ё'			 || C=='Ё'			)		{bHasSymbols=true;	C =  'е';}
				else															{							C =  '*';}

				Word [iWord  ] = C;
				Word [iWord+1] = 0;
			}
		// Пропускаем всякую ересь
			if (bHasDigits || bHasSymbols)
			{
				arrWord		+= Word.GetPtr();
				arrWord_pos	+=	iPosition;
			}
			iPosition ++;
		}


	// Запоминаем все слова в тексте, их леммы и их позиции
		CPtr<CLemmaInText> AllSortedWords;
		for (iWord=0; iWord<arrWord.Size(); iWord++)
		{
			CLemmaInText lemma_text;
			lemma_text.Word = arrWord [iWord];
			int index = AllSortedWords.Find (lemma_text, true);
			if (index==-1)
			{
				lemma_arr arrLemma;
				if (GetNormalWord (lemma_text.Word, arrLemma, true)) for (iLemma=0; iLemma<arrLemma.Size(); iLemma++)
				{
					CLemmaInText new_lemma_text = lemma_text;
					new_lemma_text.Lemma		 = arrLemma[iLemma];
					new_lemma_text.Position += arrWord_pos[iWord];
					AllSortedWords.InsertSorted (new_lemma_text);
				}
			}
			else
			{
				AllSortedWords[index].Position += arrWord_pos[iWord];
			}
		}

	// Заносим все леммы текста в индекс
		time_t cur_time = time(0);
		for (iWord=0; iWord<AllSortedWords.Size(); iWord++)
		{
		// Находим элемент индекса
			oc_item.Open (AllSortedWords[iWord].Lemma.ID);

		// Обновляем в элементе индекса данные об объекте
			int index = oc_item.m_Text_ObjectSortedGUID.Find (gi);
			if (index==-1)
			{
			// объект не был занесён в элемент индекса, заносим
				index = oc_item.m_Text_ObjectSortedGUID.InsertSorted (gi);
				oc_item.m_Text_ModificationTime.Insert		(index, cur_time);
				oc_item.m_Text_WordAppearanceNum.Insert	(index, 1);
				oc_item.m_Text_Number += 1;
			}
			else
			{
			// объект уже был занесён в элемент индекса, обновляем данные
				oc_item.m_Text_ModificationTime  [index]  = cur_time;
				oc_item.m_Text_WordAppearanceNum [index]	+= 1;
			}
		}
	}
}
//____________________________________________________________________________[]

















//______________________________________________________________________________
//                                                                            []
//` Поиск																							[]
//                                                                            []
void FullTextIndex_test ()
{
	DEBUG_STACK_NAME (FullTextIndex_test);

#if 0  //{ RomanVK
	InitializeSearchSystem			("ru", false);
//	GenerateTexts						("./text/test-03.txt", 146);
//	CreateFullTextIndex				();
#endif //}

	GenerateTexts						("./text/test-07.txt", 146);
	CreateFullTextIndex				();

//	TestRules							("./text/test.txt");
//	TestSearch							("./text/test.txt");
//	TestNormalizeSpeed				("./text/test-01.txt");
//	PrintFullTextIndex				("фиг");

	PrintFullTextIndexStatistics	();
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/