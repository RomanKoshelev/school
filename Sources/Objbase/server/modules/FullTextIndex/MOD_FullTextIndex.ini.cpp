/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.ini.cpp												[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Полнотекстовая индексация и поиск с учётом морфологии			[]
[]						Инициализация модуля.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_FullTextIndex.inc.h"


bool bPrint=false;

//______________________________________________________________________________
//                                                                            []
//` Построение набора морфологичекских правил                                 []                                         
//                                                                            []
void CreateMorphologicRules (string& StrRule)
{
	DEBUG_STACK_NAME (CreateMorphologicRules);

	int i,NN;
	OC_MorphologicRule oc_rule;
	oc_rule.SetIndex_AffixVariant();
	oc_rule.DeleteClassObjects ();

	string_arr StrRuleArr;
	StrRule.explode (StrRuleArr, "\n");
	NN = StrRuleArr.Size();
	if (bPrint) printf ("\nCreate morphologic rules...\n");
	byte ATTRIBUTE=' ';
	for (i=0; i<NN; i++) 
	{
		if (bPrint) PRINT_PERCENT (i, NN);
		string Rule  = StrRuleArr[i];
		Rule.trim();
		if (Rule[0]=='#' || Rule.IsEmpty())
		{
			continue;
		}

	// Находим атрибут
		if (Rule.Find("flag *")!=-1)
		{
			ATTRIBUTE = Rule[6];
			continue;
		}

		int pos1;
		int pos2;
		string sss;
		string EXCEPTION, AVAILABLE, AFF, AFF_NORM, AFF_VARIANT, COMMENT;

	// Выделяем исключения
		pos1 = Rule.Find ("[^");
		if (pos1!=-1)
		{
			pos2 = Rule.Find ("]");
			if (pos2)
			{
				Rule.SubStr (EXCEPTION, pos1+2, pos2);
			}
		}
		else
		{
		// Выделяем условия
			pos1 = Rule.Find ("[");
			if (pos1!=-1)
			{
				pos2 = Rule.Find ("]");
				if (pos2)
				{
					Rule.SubStr (AVAILABLE, pos1+1, pos2);
				}
			}
		}

	// Выделяем комментраний
		pos1 = Rule.Find ("#");
		if (pos1!=-1)
		{
			Rule.SubStr (COMMENT, pos1+1);
			COMMENT.trim();
		}
		
	// Выделяем правило
		pos1 = Rule.Find (">");
		if (pos1!=-1)
		{
			pos2 = Rule.Find ("#");
			Rule.SubStr (AFF, pos1+1, pos2);
			AFF.trim();

		// Выделяем из правила нормальное окончание
			pos1 = AFF.Find ("-");
			if (pos1!=-1)
			{
				pos2 = AFF.Find (",");
				AFF.SubStr (AFF_NORM, pos1+1, pos2);
				AFF_NORM.trim();
			}
		// Выделяем из правила вариант окончания
			pos1 = AFF.Find (",");
			if (pos1!=-1)
			{
				AFF.SubStr (AFF_VARIANT, pos1+1);
			}
			else
			{
				AFF_VARIANT = AFF;
			}
		}
		if (AFF_VARIANT=="-") AFF_VARIANT="";

#if 0  //{ RomanVK
		sss.Format   ("%4d %c: [%s%s]%s->%s     #%s\n", 
							i+1, 
								 ATTRIBUTE, 
										EXCEPTION.IsEmpty()?"":"^",
											EXCEPTION.IsEmpty()?AVAILABLE.c_str():EXCEPTION.c_str(),
												AFF_NORM.c_str(),
													AFF_VARIANT.c_str(),
															  COMMENT.c_str()											
		);
		sss.win_2_dos();
		sss.Print();
#endif //}


	// Создаём правило
		oc_rule.New();
		oc_rule.m_Number					= i+1;
		oc_rule.m_Attribute				= ATTRIBUTE;
		oc_rule.m_AffixNormal			= AFF_NORM;
		oc_rule.m_AffixVariant			= AFF_VARIANT;
		oc_rule.m_Comment					= COMMENT;
		oc_rule.m_BaseEnd_Exception.CopyFrom ((const byte*)EXCEPTION.GetPtr(), EXCEPTION.Len());
		oc_rule.m_BaseEnd_Available.CopyFrom ((const byte*)AVAILABLE.GetPtr(), AVAILABLE.Len());
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Инициализация поисковой системы                                           []                               
//                                                                            []
bool InitializeSearchSystem (const char * Lang, bool bFromDatFile)
{
	DEBUG_STACK_NAME (InitializeSearchSystem);
	int i, j, k, NN;
	(void)bFromDatFile;

//----------------------------------------------------------------------------[] 
// Читаем инициализирующие данные
//
	string RuleFileName; RuleFileName.Format ("./modules.ini/FullTextIndex/rule.%s.txt", Lang); string StrRule; StrRule.ReadFile (RuleFileName);
	string WordFileName; WordFileName.Format ("./modules.ini/FullTextIndex/word.%s.txt", Lang); string StrWord; StrWord.ReadFile (WordFileName);
	string StopFileName; StopFileName.Format ("./modules.ini/FullTextIndex/stop.%s.txt", Lang); string StrStop; StrStop.ReadFile (StopFileName);	

#if 0  //{ RomanVK
	string StrText;
	if (!bFromDatFile) 	{string TextFileName; TextFileName.Format ("./modules.ini/FullTextIndex/text.%s.txt", Lang); StrText.ReadFile (TextFileName);}
	else						{string TextFileName; TextFileName.Format ("./modules.ini/FullTextIndex/text.%s.dat", Lang); StrText.ReadFile (TextFileName);}
#endif //}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
// Строим набор правил
//
	CreateMorphologicRules (StrRule);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
// Строим набор стоп-слов языка
//
#if 1  //{ RomanVK
	OC_StopWord oc_stop;
	oc_stop.DeleteClassObjects ();
	string_arr StrStopArr;
	if (bPrint) printf ("\nCreate stop-words...\n");
	StrStop.explode (StrStopArr, "\n");
	NN = StrStopArr.Size();
	for (i=0; i<NN; i++) 
	{
		if (bPrint) PRINT_PERCENT (i, NN);
		StrStopArr[i].trim();
		if (StrStopArr[i].IsEmpty())
		{
			continue;
		}
		oc_stop.New();
		oc_stop.m_Word	= StrStopArr[i];
	}
#endif //}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// Строим набор нормальных слов языка
//
#if 1  //{ RomanVK
	OC_SearchItem oc_item;
	oc_item.DeleteClassObjects ();
	string_arr StrWordArr;
	if (bPrint) printf ("\nCreate normal words...\n");
	StrWord.explode (StrWordArr, "\n");
	NN = StrWordArr.Size();
	for (i=0; i<NN; i++) 
	{
		if (bPrint) PRINT_PERCENT (i, NN);
		StrWordArr[i].trim();
		if (StrWordArr[i].IsEmpty())
		{
			continue;
		}

		static char NORM[1024];
		static char ATTR[1024];
		NORM[0]=0;
		ATTR[0]=0;

		for (k=0, j=0; j<(int)StrWordArr[i].Len(); j++, k++)
		{
			char C = StrWordArr[i][j];
			if (C=='/') break;
			NORM[k  ] = C;
			NORM[k+1] = 0;
		}
		for (k=0, j=j+1; j<(int)StrWordArr[i].Len(); j++, k++)
		{
			char C = StrWordArr[i][j];
			ATTR[k  ] = C;
			ATTR[k+1] = 0;
		}

		oc_item.New();
		oc_item.m_NormalWord		= NORM;
		oc_item.m_NormalWordInv = GetInverseWord (NORM, strlen (NORM));
		oc_item.m_Attributes		= ATTR;
		oc_item.m_Hypothesis		= false;
	}
#endif //}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// Строим набор благозвучных трёхбуквенных сочетаний
//
#if 0  //{ RomanVK
	OC_WordNibbleABC oc_nibble;
	oc_nibble.SetIndex_Nibble ();
	oc_nibble.DeleteClassObjects ();
	if (bPrint) printf ("\nCreate ABC-like nibbles...\n");
	if (bFromDatFile)
	{
		string_arr NibbleArr;
		StrText.explode (NibbleArr, "\n");
		NN = NibbleArr.Size ();
		for (i=0; i<NN; i++)
		{
			if (bPrint) PRINT_PERCENT (i, NN);
			NibbleArr[i].trim();
			if (NibbleArr[i].IsEmpty())
			{
				continue;
			}

			static char sNibble [1024];
			sNibble[0]=0;
			float			fFreq=0.0;
			sscanf (NibbleArr[i], "%s %f", sNibble, &fFreq);

			oc_nibble.New ();
			oc_nibble.m_Nibble			= sNibble;
			oc_nibble.m_FreqPerMillion	= fFreq;
		}
	}
	else
	{
		int		MaxWordLen	= 256;
		int		iWord			= 0;
		int		nWord			= 0;
		byte_arr sWord			(MaxWordLen);
		NN							= StrText.Size();
		for (i=0; i<NN; i++) 
		{
			if (bPrint) PRINT_PERCENT (i, NN);
			sWord [0] = 0;
			nWord		 = 0;
		// Выделяем слово
			for (; i<NN; i++, iWord++)
			{
				char C = StrText[i];
			// Избавляемся от переносов
				if (C=='-' && i<NN-3)
				{
					if (StrText[i+1]=='\r' && StrText[i+2]=='\n')	{iWord-=1; i+=2; continue;}
					if (StrText[i+1]=='\n')									{iWord-=1; i+=1; continue;}
				}

				if			('a'<=C&&C<='z' || 'а'<=C&&C<='я')	{}
				else if	('A'<=C&&C<='Z' || 'А'<=C&&C<='Я')	{C += 32;}
				else if	(C=='ё'			 || C=='Ё'			)	{C =  'е';}
				else														{C =  '*';}
				if (iWord>=MaxWordLen)
				{
					SERVER_DEBUG_ERROR_1 ("Слишком длинное слово в обучающем тексте: %s", sWord);
					break;
				}
				if (C=='*')
				{
					iWord=0;
					break;
				}
				sWord [iWord  ] = C;
				sWord [iWord+1] = 0;
				nWord	++;
			}

		// Для выделенного слова строим все тройные сочетания
			const				nABC=3;
			static char		sABC[1024];
			for (j=0; j<nWord-nABC+1; j++)
			{
				sABC[0] = sWord[j+0];
				sABC[1] = sWord[j+1];
				sABC[2] = sWord[j+2];
				sABC[3] = 0;

				if (!oc_nibble.Find (sABC))
				{
					oc_nibble.New ();
					oc_nibble.m_Nibble	= sABC;
					oc_nibble.m_Num		= 1;
				}
				else
				{
					oc_nibble.m_Num		+= 1;
				}
				float oc_nibble_m_Num	= (float)(int)oc_nibble.m_Num;
				oc_nibble.m_FreqPerMillion = oc_nibble_m_Num / (float(NN)/1000/1000);
			}
		}

	// Распечатываем получившиеся тройные сочетания
		string TextDatFileName; TextDatFileName.Format ("./modules.ini/FullTextIndex/text.%s.dat", Lang); string StrTextDat;
		NN = oc_nibble.GetIndexTotalNum();
		oc_nibble.SetIndex_FreqPerMillion();
		for (i=0, oc_nibble.GoLast(); oc_nibble.IsValid(); oc_nibble--, i++)
		{
			string Tmp;
			Tmp.Format ("%s %.3f\n", string(oc_nibble.m_Nibble).c_str(), float (oc_nibble.m_FreqPerMillion));
			StrTextDat += Tmp;
		}
		StrTextDat.WriteFile (TextDatFileName);
	}
#endif //}

	return true;
}
//____________________________________________________________________________[]












/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/