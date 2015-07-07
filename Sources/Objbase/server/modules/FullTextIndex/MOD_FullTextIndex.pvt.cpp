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
[] Description:   �������������� ���������� � ����� � ������ ����������			[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_FullTextIndex.inc.h"





#define USE_FC
//______________________________________________________________________________
//                                                                            []
//` �������� -- �������� �� ������ ������������                               []                                           
//                                                                            []
bool IsDelimiter (char C)
{
	return	C==' ' || C=='!' || C=='(' || C==')' || C=='-' || C=='=' || C=='+' || 
				C=='{' || C=='}' || C=='[' || C==']' || C=='.' || C==',' || C==':' || 
				C==';' || C=='"' || C=='\''|| C=='/' || C=='\\'|| C=='?' || C=='\n'||
				C=='\r'|| C=='\t'|| C=='<' || C=='>' || C=='|';
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ����������� ����� �� ����� "��������"                                     []                                     
//                                                                            []
const char * GetInverseWord (const char * sWord, int nWord)
{
	DEBUG_STACK_NAME (GetInverseWord);

	const int MaxInvertLen = 1024;
	static char sInvert [MaxInvertLen];

	int i, iWord;
	for (i=0, iWord=nWord-1; iWord>=0 && i<MaxInvertLen; iWord--, i++)
	{
		sInvert[i  ] = sWord[iWord];
		sInvert[i+1] = 0;
	}
	return sInvert;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ��� �����                                                                 []         
//                                                                            []
inline int GetNormalWordHash (const char* sNormalWord)
{ 
	DEBUG_STACK_NAME (GetNormalWordHash);

	unsigned int nHash=0;
	unsigned int nMask=0;
	while (*sNormalWord) 
	{
		nHash = (nHash << 4) + *sNormalWord++;
		if ((nMask = nHash & 0xF0000000) != 0) 
		{ 
			nHash ^= nMask >> 24;
		}
		nHash &= ~nMask;
	}
	return int(nHash);
}
//____________________________________________________________________________[]












//______________________________________________________________________________
//                                                                            []
//` IsStopWord                                                                []          
//                                                                            []
void IsStopWord (const char * sWord, bool& bRes)
{
	DEBUG_STACK_NAME (IsStopWord);
	if (strlen (sWord)<=1) 
	{
		bRes=true;
	}
	else
	{
		OC_StopWord oc_stop;
		bRes = oc_stop.Find  (sWord);
	}
}
//----------------------------------------------------------------------------[] 
bool IsStopWord (const char * sWord)
{
	DEBUG_STACK_NAME (IsStopWord);
	bool bRes=false;
	IsStopWord (sWord, bRes);
	return bRes;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ������������ ������� (�� ������������ � ������������ �������  []                                                                        
//                                                                            []
void FC_CheckRuleApply (identifier ruleID, char BaseEnd, bool& bRes, string& ruleAffixNormal, char& ruleAttribute)
{
	DEBUG_STACK_NAME (CheckRuleApply);
#ifdef USE_FC
	IF_CACHED_ARGS_2_RETURN_VOID (10*1000, ruleID, BaseEnd);
#endif
	{
		STATIC_OC (OC_MorphologicRule, oc_rule);
		oc_rule.Open (ruleID);

		bRes = true;
		ruleAffixNormal = "";
		ruleAttribute   = 0;
		if (oc_rule.m_BaseEnd_Exception.Find ((byte)BaseEnd)!=-1)
		{
			bRes = false;
		}
		else if (oc_rule.m_BaseEnd_Available.Size()!=0)
		{
			if (oc_rule.m_BaseEnd_Available.Find ((byte)BaseEnd)==-1) 
			{
				bRes = false;
			}
		}

		if (bRes)
		{
			ruleAffixNormal = oc_rule.m_AffixNormal;
			ruleAttribute   = oc_rule.m_Attribute;
		}
	}
#ifdef USE_FC
	CACHE_STORE_RESULT_3	(bRes, ruleAffixNormal, ruleAttribute);
#endif
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` ���������� ������� ��� �������                                            []                              
//                                                                            []
void FC_GetRulesForAffix (const char* AFFIX, identifier_arr& ruleIDs)
{
	DEBUG_STACK_NAME (GetRulesForAffix);
#ifdef USE_FC
	IF_CACHED_ARGS_1_RETURN_VOID (10*1000, AFFIX);
#endif
	{
		static key_arr ka; ka.Init(); ka+=AFFIX;
		STATIC_OC (OC_MorphologicRule, oc_rule);
		oc_rule.GetClassIdList   (ruleIDs, &ka);
	// ������� ���������, ��� ������ �� ����
		if (ruleIDs.Size ()==0)	return;
	}
#ifdef USE_FC
	CACHE_STORE_RESULT_1	(ruleIDs);
#endif
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` CheckRuleResult																				[]
//                                                                            []
void FC_CheckRuleResult (bool bCreateHypothesis, const char * RuleResult, byte ruleAttribute, identifier_arr& LemmaArr_ID, bool_arr& LemmaArr_IsHyp)
{
	DEBUG_STACK_NAME (CheckRuleResult);
#ifdef USE_FC
	IF_CACHED_ARGS_3_RETURN_VOID (10*1000, bCreateHypothesis, ruleAttribute, RuleResult);
#endif
	{
		static key_arr ka;
		STATIC_OC (OC_SearchItem, oc_item);
		ka.Init();
		ka += RuleResult;
		if (!bCreateHypothesis)
		{
			ka += false;
		}

		bool bFound =	   false;
		LemmaArr_ID.Erase		();
		LemmaArr_IsHyp.Erase ();


	// ������� ���������, ��� ������ �� ����
		if (!oc_item.Find (ka) && !bCreateHypothesis) return;

		for (; oc_item.IsValid(); oc_item.GoNext(&ka))
		{
		// ���������� ����� ������ ����� ������� ������� ����������������
			string oc_item_m_Attributes = oc_item.m_Attributes;					
			if (oc_item_m_Attributes.Find (ruleAttribute)!=-1)
			{
				bFound					 = true;
				LemmaArr_ID				+= oc_item.GetObjectID();
				LemmaArr_IsHyp			+= false;
			}
			else if (bCreateHypothesis && oc_item.m_Hypothesis==true)
			{
				bFound					 = true;
				LemmaArr_ID				+= oc_item.GetObjectID();
				LemmaArr_IsHyp			+= true;
			}
		}
		if (!bFound && bCreateHypothesis)
		{
			LemmaArr_ID				+= NA;
			LemmaArr_IsHyp			+= true;
		}
	}
#ifdef USE_FC
	CACHE_STORE_RESULT_2	(LemmaArr_ID, LemmaArr_IsHyp);
#endif
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` GetAffixInvertNum																			[]
//                                                                            []
void FC_GetAffixInvertNum (const char * AFFIX, int& nMatch)
{
	DEBUG_STACK_NAME (GetAffixInvertNum);
#ifdef USE_FC
	IF_CACHED_ARGS_1_RETURN_VOID (100*1000, AFFIX);
#endif

	nMatch = 0;
	static key_arr ka;
	ka.Init ();
	ka+=AFFIX;
	STATIC_OC (OC_SearchItem, oc_item);
	oc_item.SetIndex_NormalWordInv ();

	if (!oc_item.Find (ka, true)) oc_item.GoFirst ();
	for (; oc_item.IsValid(); oc_item++)
	{
		if (oc_item >= ka)
		{
			if (string(oc_item.m_NormalWordInv).Find (AFFIX)!=0)
			{
				break;
			}
			nMatch++;
		}
	}

#ifdef USE_FC
	CACHE_STORE_RESULT_1 (nMatch);
#endif
}
//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 
#define STRUCT_TO_ARR(ARR,F)																	\
	{																									\
		ARR##_##F.Alloc (ARR.Size());															\
		for (int i=0; i<ARR.Size(); i++)														\
		{																								\
			ARR##_##F[i] = ARR[i].F;															\
		}																								\
	}
//----------------------------------------------------------------------------[] 
#define ARR_TO_STRUCT(ARR,F)																	\
	{																									\
		if (ARR.Size()<ARR##_##F.Size()) ARR.Realloc(ARR##_##F.Size());			\
		for (int i=0; i<ARR.Size(); i++)														\
		{																								\
			ARR[i].F = ARR##_##F[i];															\
		}																								\
	}
//----------------------------------------------------------------------------[] 






//______________________________________________________________________________
//                                                                            []
//` Prepare_INITIAL_WORD                                                      []                    
//                                                                            []
void Prepare_INITIAL_WORD (const char* sWord, char * INITIAL_WORD, int& INITIAL_WORD_LEN, bool& bIsDigit, bool& bReturn, bool& bReturnVal)
{
	DEBUG_STACK_NAME (Prepare_INITIAL_WORD);

	int i;

	const		int MAX_SEARCH_WORD_LEN	= 32;
	const		int MAX_DIGIT_NUM			=  4;

	INITIAL_WORD_LEN	= 0;
	bReturn				= false; 
	bReturnVal			= false;
	bool	bHasDigits	= false;
	bool	bHasSymbols	= false;
	bool	bCyr			= false;
	for (i=0; sWord[i]; i++)
	{
		char C = sWord[i];
		if			('a'<=C&&C<='z' || '�'<=C&&C<='�')		{bHasSymbols=true;				}
		else if	('0'<=C&&C<='9'						)		{bHasDigits =true;				}
		else if	('A'<=C&&C<='Z' || '�'<=C&&C<='�')		{bHasSymbols=true;	C += 32;	}
		else if	(C=='�'			 || C=='�'			)		{bHasSymbols=true;	C =  '�';}
		else															{							C =  '*';}

		if (C>='�' && C<='�')
		{
			bCyr = true;
		}
			 
		if (bCyr && (C<'�' || C>'�'))
		{
			if (C=='o')  C='�';
			if (C=='x')  C='�';
			if (C=='p')  C='�';
			if (C=='e')  C='�';
			if (C=='c')  C='�';
			if (C=='a')  C='�';
		}

		if (i>MAX_SEARCH_WORD_LEN)		{INITIAL_WORD[i] = 0;	break;}
		else									{INITIAL_WORD[i] = C;	INITIAL_WORD[i+1] = 0;}
		INITIAL_WORD_LEN ++;
	}
	if (!bHasDigits && !bHasSymbols)		{bReturn=true; bReturnVal=false; return;}
	if ( bHasDigits && !bHasSymbols)		{bIsDigit=true; INITIAL_WORD[MAX_DIGIT_NUM]=0;}


//	����������� ����� �� ����-�����
	if (IsStopWord(INITIAL_WORD))
	{
		bReturn=true; bReturnVal=false;
	}
}
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[] 
bool GetNormalWord_Algorithm (const char * sWord, lemma_arr&		arrLemma,		bool bCheckIniWord							, bool bAddToDict);
void FC_GetNormalWord_Proxy  (const char * sWord, identifier_arr& arrLemma_ID,	string_arr&  arrLemma_Word, bool& bRes	, bool bAddToDict);
void FC_GetNormalWord_Proxy  (const char * sWord, identifier& ID, string& Word, bool& bRes										, bool bAddToDict);
//----------------------------------------------------------------------------[] 



//RVK:>>>
//______________________________________________________________________________
//                                                                            []
//` ������������ �����                                                        []                  
//                                                                            []
bool GetNormalWord (const char * sWord, lemma_arr&	arrLemma, bool bAddToDict)
{
	DEBUG_STACK_NAME (GetNormalWord);

	identifier_arr	arrLemma_ID;
	string_arr		arrLemma_Word;
	bool				bRes;

	arrLemma.Erase();

	static	char	INITIAL_WORD	[1024];
	int		INITIAL_WORD_LEN		=	0;
	bool		bIsDigit		= false;
	bool		bReturnVal	= false;
	bool		bReturn		= false;

// �������� � �������� ���������
	Prepare_INITIAL_WORD (sWord, INITIAL_WORD, INITIAL_WORD_LEN, bIsDigit, bReturn, bReturnVal);
	if (bReturn)
	{
		return bReturnVal;
	}
	if (bIsDigit)
	{
		OC_SearchItem	oc_item;
		CLemma			lemma;
		if (!oc_item.Find(INITIAL_WORD) && bAddToDict)
		{
			oc_item.New ();
			oc_item.m_NormalWord		= INITIAL_WORD;
			oc_item.m_NormalWordInv = GetInverseWord (INITIAL_WORD, INITIAL_WORD_LEN);
			oc_item.m_Attributes		= "?";
			oc_item.m_Hypothesis		= true;
			
//			string StrTmp; StrTmp.Format ("\nA: %16s -> %s\n", sWord, INITIAL_WORD); StrTmp.win_2_dos(); StrTmp.Print();
		}
		lemma.ID			= oc_item.GetObjectID();
		lemma.Word		= INITIAL_WORD;
		lemma.Attr		= "";
		lemma.Weight	= 0.0;
		lemma.IsDigit	= bIsDigit;
		arrLemma			+= lemma;
		return true;
	}


	FC_GetNormalWord_Proxy (INITIAL_WORD, arrLemma_ID, arrLemma_Word, bRes, bAddToDict);

// ����������� ���������:
	ARR_TO_STRUCT (arrLemma, ID);
	ARR_TO_STRUCT (arrLemma, Word);
	
	return bRes;
}
//----------------------------------------------------------------------------[] 
void FC_GetNormalWord_Proxy (const char * sWord, identifier& ID, string& Word, bool& bRes, bool bAddToDict)
{
	DEBUG_STACK_NAME (GetNormalWord_Proxy);
#ifdef USE_FC
	IF_CACHED_ARGS_1_RETURN_VOID (200*1000, sWord);
#endif

	lemma_arr	arrLemma;
	bRes = GetNormalWord_Algorithm (sWord, arrLemma, false, bAddToDict);
	
	Word	= arrLemma[0].Word;
	ID		= arrLemma[0].ID;
	
#ifdef USE_FC
	CACHE_STORE_RESULT_3 (ID, Word, bRes);
#endif
}
//----------------------------------------------------------------------------[] 
void FC_GetNormalWord_Proxy (const char * sWord, identifier_arr& arrLemma_ID, string_arr& arrLemma_Word, bool& bRes, bool bAddToDict)
{
	DEBUG_STACK_NAME (GetNormalWord_Proxy);
#ifdef USE_FC
	IF_CACHED_ARGS_1_RETURN_VOID (200*1000, sWord);
#endif

	lemma_arr	arrLemma;
	bRes = GetNormalWord_Algorithm (sWord, arrLemma, false, bAddToDict);

// �������������� ��������� ���������:
	STRUCT_TO_ARR (arrLemma, Word);
	STRUCT_TO_ARR (arrLemma, ID);
	
#ifdef USE_FC
	CACHE_STORE_RESULT_3 (arrLemma_ID, arrLemma_Word, bRes);
#endif
}
//____________________________________________________________________________[]


















//______________________________________________________________________________
//                                                                            []
//` GetNormalWord_Algorithm                                                   []                       
//                                                                            []
bool GetNormalWord_Algorithm (const char * sWord, lemma_arr& LemmaArr, bool bCheckIniWord, bool bAddToDict)
{
	DEBUG_STACK_NAME (GetNormalWord_Algorithm);

	int i, j, iLemma;
	LemmaArr.Erase ();

	static	char	INITIAL_WORD	[1024];
	int		INITIAL_WORD_LEN		=	0;
	bool		bIsDigit		= false;
	bool		bReturnVal	= false;
	bool		bReturn		= false;
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
// �������� � �������� ���������
	if (bCheckIniWord)
	{
		Prepare_INITIAL_WORD (sWord, INITIAL_WORD, INITIAL_WORD_LEN, bIsDigit, bReturn, bReturnVal);
		if (bReturn)
		{
			return bReturnVal;
		}
	}
	else
	{
		strcpy (INITIAL_WORD, sWord);
		INITIAL_WORD_LEN = strlen (INITIAL_WORD);
	}

	bool	bFoundInDict	= false;
	bool	bIsStopWord		= false;

	OC_SearchItem	oc_item;
	CLemma			lemma;
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
// ���� ����� ���������� ����
	oc_item.SetIndex_NormalWord_Hypothesis ();
	key_arr ka; 
	ka += (INITIAL_WORD);
	ka += false;
	identifier_arr itemIDs;
	oc_item.GetClassIdList (itemIDs, &ka);
	for (i=0; i<itemIDs.Size(); i++)
	{
		bFoundInDict	= true;
		lemma.ID			= itemIDs[i];
		lemma.Word		= INITIAL_WORD;
		lemma.Attr		= "";
		lemma.Weight	= 0.0;
		lemma.IsDigit	= bIsDigit;
		lemma.IsHyp		= false;

		int index =		LemmaArr.Find (lemma);
		if (index==-1) LemmaArr +=		lemma;
		else				LemmaArr[index].Num++;

	// ����� �� ����� ���������� � ����������
		if (bIsDigit)	return true;
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
// ������, ����� �� �� ������� �������� ��� �����, ���� �� ����� ��� � �������,
// ��� �� ��� ���.
	bool	bCreateHypothesis	= !bFoundInDict && INITIAL_WORD_LEN>=5;
	bool	bBadWord				= false;
	bool	bFindAllAmonims	= false; // �������� ��������������, ���� �� ������ ��� �������

	if (bCreateHypothesis)
	{
		int	nGL		= 0;		// ����� ������ ������ �������
		int	nSG		= 0;		// ����� ������ ������ ���������
		int	nZN		= 0;		// ����� ������ ������ ����, ������� �� ����� ���� ������
		bool	bPrevGL	= false;
		bool	bPrevSG	= false;
		bool	bPrevZN	= false;
		char	PrevC		= 0;
		for (i=0; bCreateHypothesis && i<INITIAL_WORD_LEN; i++)
		{
			char C = INITIAL_WORD[i];
			if (C<'�' || C>'�')
			{
				bBadWord				= true;
				bCreateHypothesis	= false;
			}

			bool bGL = C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�';
			bool bSG = !bGL && C!='�';
			bool bZN = C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�'||C=='�';

			if (bGL) {nGL=bPrevGL?nGL+1:1; bPrevGL=true;} else bPrevGL=false;
			if (bSG) {nSG=bPrevSG?nSG+1:1; bPrevSG=true;} else bPrevSG=false;
			if (bZN) {nZN=bPrevZN?nZN+1:1; bPrevZN=true;} else bPrevZN=false;

			if (nGL>=4 || (nSG>=4 && INITIAL_WORD_LEN<10) || nSG>=5 || (nZN>=2 && PrevC==C)) bCreateHypothesis=false;

			PrevC = C;
		}
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//RVK:>>>
// �������� ��������� ��� ���������� ����� ����� � ������ ����� ���
	for (i=max(0, INITIAL_WORD_LEN-10); !bBadWord && !bIsStopWord && i<=INITIAL_WORD_LEN; i++)
	{
	// ���� ����� ������� � �������, ������ �� ����
		if (bFoundInDict && !bFindAllAmonims)
		{
			break;
		}

	// ������� ���������� ������� ��� �������� ���������
		byte BaseEnd = i>0? INITIAL_WORD[i-1]: char(0);
		identifier_arr ruleIDs;
		FC_GetRulesForAffix (INITIAL_WORD+i, ruleIDs);

		for (int iRule=0; !bIsStopWord && iRule<ruleIDs.Size(); iRule++)
		{
		// ��������� ����������� ���������� �������
			bool		bRuleCanBeApplied;
			char		ruleAttribute=0;
			string	ruleAffixNormal="";
			FC_CheckRuleApply (ruleIDs[iRule], BaseEnd, bRuleCanBeApplied, ruleAffixNormal, ruleAttribute);
			if (!bRuleCanBeApplied) continue;

		// ������ ������� ���������� �����
			static char RuleResult [10240];
			memcpy (RuleResult, INITIAL_WORD, i);
			RuleResult[i]=0;
			strcat (RuleResult, ruleAffixNormal.c_str());
			
		// ���������� ����-�����
			if (IsStopWord (RuleResult)) 
			{
				bIsStopWord = true;
				break;
			}

		// ������� ���������� ����� ��� �������
			identifier_arr LemmaArr_ID;
			bool_arr			LemmaArr_IsHyp;
			FC_CheckRuleResult (bCreateHypothesis, RuleResult, ruleAttribute, LemmaArr_ID, LemmaArr_IsHyp);
			for (iLemma=0; iLemma<LemmaArr_ID.Size(); iLemma++)
			{
			// ���� ����� ������� � �������, ������ �� ����
				if (bFoundInDict && !bFindAllAmonims)
				{
					break;
				}

				lemma.ID			= 	LemmaArr_ID  [iLemma];
				lemma.Word		= 	RuleResult;
				lemma.Attr		= 	ruleAttribute;
				lemma.IsDigit	= 	false;
				lemma.Num		= 	0;
				lemma.Weight	= 	0.0;
				lemma.WordInv	= 	"";
				lemma.IsHyp		= 	LemmaArr_IsHyp [iLemma];

			// ����� ������� � �������
				if (lemma.ID != NA) 
				{
					bFoundInDict = true;
				}

			// ���������� �����
				if (lemma.ID!=NA || bCreateHypothesis)
				{
					int index =		LemmaArr.Find (lemma);
					if (index==-1) LemmaArr +=		lemma;
					else				LemmaArr[index].Num++;
				}
			}
		}
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
// ���� ���������� ����� ������� � �������, ����������� ��� �� ���������
	if (bFoundInDict)									
	{
		for (iLemma=0; iLemma<LemmaArr.Size(); iLemma++)
		{
			if (LemmaArr[iLemma].ID==NA)
			{
				LemmaArr.Del (iLemma);
				iLemma --;
			}
		}
		return true;
	}
//----------------------------------------------------------------------------[] 






//----------------------------------------------------------------------------[] 
//
// ����� �� ������� � �������, ���������� ������ �������� ��� 
// ���������� ��������� �����.
//
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
// ����� �� ����-������ -- ���������� ���
	if (bIsStopWord)			
	{
		LemmaArr.Erase();
		return false;
	}
// ��������� � �������� ����� �� ������� ����������� ����� �����
	else
	{
		CLemma lemma;
		lemma.Word		= INITIAL_WORD;
		lemma.Attr		= "";
		lemma.ID			= NA;
		lemma.IsDigit	= bIsDigit;
		LemmaArr			+= lemma;
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// ��������� �������� ���������� �����
	if (bCreateHypothesis)	
	{
	// ������ ��� ���� ������� ��������� ����� � ������� ����� ������� �������
		int MaxLen = 0;
		for (iLemma=0; iLemma<LemmaArr.Size(); iLemma++)
		{
			LemmaArr[iLemma].WordInv = GetInverseWord (LemmaArr[iLemma].Word.c_str(), LemmaArr[iLemma].Word.Len ());
			MaxLen  = max (MaxLen, int (LemmaArr[iLemma].WordInv.Len()));
		}

	// ����������� ���������� �����
		for (i=0; i<LemmaArr.Size(); i++) 
		{
			for (j=0; i!=j && j<LemmaArr.Size(); j++)
			{
				if (LemmaArr[j].Word==LemmaArr[i].Word) 
				{
					LemmaArr[j].Weight  = -1.0;
				}
			}
		}

	// ������� ������� ��� ��������� ������� �� ��������� ����������� � �������
		float MaxWeigth = 0.0;
		MaxLen = min (7, MaxLen);
		bool bPrintHeader    = true; (void)bPrintHeader;
		bool bPrintNewAffLen = false;
		for (i=MaxLen; i>=3; i--)
		{
			char AFFIX [1024];
			bPrintNewAffLen = true;
			int nVariant =0;
			for (iLemma=0; iLemma<(int)LemmaArr.Size(); iLemma++) if (LemmaArr[iLemma].Weight>=0.0 && int(LemmaArr[iLemma].WordInv.Len())>=i)
			{
				int BaseLen = LemmaArr[iLemma].Word.Len()-i;
				strcpy (AFFIX, LemmaArr[iLemma].WordInv.GetPtr());
				AFFIX[i]=0;
				int		nMatch = 0;
				float		Weight = LemmaArr[iLemma].Weight;


				FC_GetAffixInvertNum (AFFIX, nMatch);
				Weight		=		(float) (double(nMatch) / max(0.1, pow (10, BaseLen)) * pow (10, MaxLen));
				MaxWeigth	=		max (MaxWeigth, Weight);
				LemmaArr[iLemma].Weight = max (Weight, LemmaArr[iLemma].Weight);

				
				nVariant ++;

//RVK:>>>
				if (nMatch)
				{
#if 0  //{ RomanVK
					string sHEADER="", sSUBHEADER="";
					if (bPrintHeader)
					{
						sHEADER.Format ("\n\n\n%s:\n===========================\n", sWord);
						bPrintHeader = false;
					}
					if (bPrintNewAffLen)
					{
						sSUBHEADER.Format ("\nAffix length = %2d:\n------------------\n", i);
						bPrintNewAffLen = false;
					}
					char sBase [1024];
					strcpy (sBase, LemmaArr[iLemma].Word.c_str());
					sBase [BaseLen] = 0;
					string StrDebug;
					string Tmp;
					string BASE_AFF;
					BASE_AFF.Format ("%s+%s", sBase, GetInverseWord (AFFIX, strlen (AFFIX)));
					Tmp.Format ("%s%s[BaseLen=%2d] %22s = %-25s", 
									 sHEADER.c_str(), 
										sSUBHEADER.c_str(),
													  BaseLen, 
															 LemmaArr[iLemma].Word.c_str(),
																	  BASE_AFF);
					StrDebug+=Tmp;
					Tmp.Format (" %6d -> %10.2f\n", nMatch, LemmaArr[iLemma].Weight);
					StrDebug+=Tmp;
					StrDebug.win_2_dos(); StrDebug.Print();
#endif //}
				}
			}

		// ��������� ��������
			int LemmaRest = LemmaArr.Size();
			for (iLemma=0; iLemma<(int)LemmaArr.Size(); iLemma++)
			{
				if ((/*nVariant>=3 ||*/ i<=4) && (LemmaArr[iLemma].Weight < MaxWeigth))
				{
					LemmaArr[iLemma].Weight = -1.0;
					LemmaRest --;
				}
			}
			if (LemmaRest<=1)
			{
				break;
			}
		}
	// ��������� ������ ������� � ������������ �����, ������������� ��������� ��������
		lemma_arr NewLemmaArr;
		if (MaxWeigth>0.0)
		{
			for (iLemma=0; iLemma<LemmaArr.Size(); iLemma++) if (LemmaArr[iLemma].Weight == MaxWeigth)
			{
				NewLemmaArr += LemmaArr[iLemma];
				break;
			}
		}
		else
		{
			CLemma lemma;
			lemma.Word		= INITIAL_WORD;
			lemma.Attr		= "";
			lemma.ID			= NA;
			lemma.IsDigit	= bIsDigit;
			NewLemmaArr	  += lemma;
		}
		LemmaArr = NewLemmaArr;
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// ���� ��������� - ������� � �������
	if (bAddToDict) for (iLemma=0; iLemma<LemmaArr.Size(); iLemma++)
	{
		if (LemmaArr[iLemma].ID==NA)
		{
			oc_item.SetIndex_NormalWord_Hypothesis ();
			key_arr ka; 
			ka += (LemmaArr[iLemma].Word);
			ka += true;
			if (!oc_item.Find (ka))
			{
				oc_item.New ();
				oc_item.m_NormalWord		= LemmaArr[iLemma].Word;
				oc_item.m_NormalWordInv = GetInverseWord (LemmaArr[iLemma].Word.c_str(), LemmaArr[iLemma].Word.Len());
				oc_item.m_Attributes		= "?";
				oc_item.m_Hypothesis		= true;
//				string StrTmp; StrTmp.Format ("\nB: %16s -> %s\n", sWord, LemmaArr[iLemma].Word.c_str()); StrTmp.win_2_dos(); StrTmp.Print();
			}
			LemmaArr[iLemma].ID			= oc_item.GetObjectID();
		}
	}
//----------------------------------------------------------------------------[] 

	return true;
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` GetNormalWordArr																				[]
//                                                                            []
void GetNormalWordArr (const char* sText, lemma_arr& ArrResult, bool bAddToDict, bool bUsageAsterisk)
{
	DEBUG_STACK_NAME (GetNormalWordArr);

	int				nText = strlen (sText);
	int				iText = 0;
	int				iLemma= 0;
	int				iWord = 0;
	byte_arr			Word (nText+1);
	ArrResult.Erase ();

// �������� �����
	for (iText=0, iWord=0; iText<nText; iText++)
	{
		bool	bAsterisk = false;
		int	nAsterisk = -1;
		Word [0] = 0;
		for (; iText<nText; iText++, iWord++)
		{
			char C = sText[iText];
			if (bUsageAsterisk && C=='*')
			{
				bAsterisk = true;
				nAsterisk = iWord;
			}
			if (IsDelimiter (C))
			{
				iWord=0;
				break;
			}
			Word [iWord  ] = C;
			Word [iWord+1] = 0;
		}

		lemma_arr arrLemma;
		if (bAsterisk)
		{
			if (strlen ((const char*)Word.GetPtr())>=2)
			{
				Word[nAsterisk] = 0;
//				printf ("\n\n\nWORD: %s\n", (const char*)Word.GetPtr());
				OC_SearchItem oc_item;
				oc_item.SetIndex_NormalWord_Hypothesis();
				key_arr ka;
				ka+=(const char*)Word.GetPtr();
				int n=0;
				
				if (!oc_item.Find (ka, true)) oc_item.GoFirst ();
				for (n=0; n<100 && oc_item.IsValid (); oc_item++, n++)
				{
					if (oc_item >= ka)
					{
						if (string(oc_item.m_NormalWord).Find ((const char*)Word.GetPtr())!=0)
						{
							break;
						}
						CLemma lemma;
						lemma.ID			= 	oc_item.GetObjectID ();
						lemma.Word		= 	oc_item.m_NormalWord;
						
//						printf ("%d: %s\n", n, lemma.Word.c_str());
						int index = ArrResult.Find (lemma);
						if (index==-1)	
						{
							ArrResult += lemma;
//							printf ("\n********************\n%s\n", lemma.Word.c_str());
						}
					}
				}
			}
		}
		else if (GetNormalWord ((const char *)Word.GetPtr(), arrLemma, bAddToDict)) for (iLemma=0; iLemma<arrLemma.Size(); iLemma++)
		{
			int index = ArrResult.Find (arrLemma[iLemma]);
			if (index==-1)	ArrResult += arrLemma[iLemma];
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` �������������� ���������� ������������� ������� ���� ������					[]
//                                                                            []
void CreateFullTextIndex (const char * sText, const guid& gi, identifier_arr& SearchItemID, time_t cur_time)
{
	DEBUG_STACK_NAME (CreateFullTextIndex);

	OC_SearchItem oc_item;
	oc_item.SetIndex_NormalWord_Hypothesis ();

	if (cur_time==0) cur_time = time(0);

// �������� �� ����� � ��������������
	int				nText = strlen (sText);
	int				iText = 0;
	int				iWord = 0;
	int				nWord	= 0;
	int				iLemma= 0;
	string_arr		arrWord;
	int_arr			arrWord_pos;
	char_arr			Word (nText+1);

// �������� �����
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

			if			('a'<=C&&C<='z' || '�'<=C&&C<='�')		{bHasSymbols=true;				}
			else if	('0'<=C&&C<='9'						)		{bHasDigits =true;				}
			else if	('A'<=C&&C<='Z' || '�'<=C&&C<='�')		{bHasSymbols=true;	C += 32;	}
			else if	(C=='�'			 || C=='�'			)		{bHasSymbols=true;	C =  '�';}
			else															{							C =  '*';}

			Word [iWord  ] = C;
			Word [iWord+1] = 0;
		}
	// ���������� ������ �����
		if (bHasDigits || bHasSymbols)
		{
			arrWord		+= Word.GetPtr();
			arrWord_pos	+=	iPosition;
		}
		iPosition ++;
	}
	nWord = arrWord.Size();

// ���������� ��� ����� � ������, �� ����� � �� �������
	CPtr<CLemmaInText> AllSortedWords;
	for (iWord=0; iWord<nWord; iWord++)
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

// ������� ��� ����� ������ � ������
	for (iWord=0; iWord<AllSortedWords.Size(); iWord++)
	{
		identifier lemmaID = AllSortedWords[iWord].Lemma.ID;
		if (lemmaID==NA)
		{
			SERVER_DEBUG_ERROR_1 ("lemmaID==NA (%s)", AllSortedWords[iWord].Lemma.Word.c_str());
			continue;
		}

	// ������� ������� �������
		oc_item.Open (lemmaID);

	// ��������� � �������� ������� ������ �� �������
		int index = oc_item.m_Text_ObjectSortedGUID.Find (gi, true);
		int nFirstPos			= AllSortedWords[iWord].Position[0];
		int nAppearanceNum	= AllSortedWords[iWord].Position.Size();
//		printf ("%s nFirstPos = %d\n", AllSortedWords[iWord].Lemma.Word.c_str(), nFirstPos);
		if (index==-1)
		{
		// ������ �� ��� ������ � ������� �������, �������
			oc_item.m_Text_Number += 1;

			index = oc_item.m_Text_ObjectSortedGUID.InsertSorted (gi);
			oc_item.m_Text_ModificationTime.Insert		(index, cur_time);
			oc_item.m_Text_WordAppearanceNum.Insert	(index, nAppearanceNum);
			oc_item.m_Text_WordFirstPosition.Insert	(index, nFirstPos);
			SearchItemID += lemmaID;
		}
		else
		{
		// ������ ��� ��� ������ � ������� �������, ��������� ������
			oc_item.m_Text_ModificationTime	[index]  = cur_time;
			oc_item.m_Text_WordAppearanceNum [index] += nAppearanceNum;
			oc_item.m_Text_WordFirstPosition [index]  = min (int(oc_item.m_Text_WordFirstPosition [index]), nFirstPos);
		}
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` ������� ������ �� ������ �� ��������� ����                                []                                          
//                                                                            []
void RemoveFromFullTextIndex (const guid& gi, const identifier_arr& arrLemma)
{
	DEBUG_STACK_NAME (RemoveFromFullTextIndex);

	int iLemma=0;
// ������� ���������� �� ������� �� ���� ����
	for (iLemma=0; iLemma<arrLemma.Size(); iLemma++)
	{
		STATIC_OC (OC_SearchItem, oc_item);
		if (!OC_Exist (OBJ_CLASS_ID_SearchItem, arrLemma[iLemma]))
		{
			continue;
		}

	// ��������� ������� �������
		oc_item.Open (arrLemma[iLemma]);

	// ������� � �� ��� ������ �� ������
		int index;
		for (;;)
		{
			index = oc_item.m_Text_ObjectSortedGUID.Find (gi, true);
			if (index!=-1)
			{
				oc_item.m_Text_ObjectSortedGUID.Del		(index);
				oc_item.m_Text_ModificationTime.Del		(index);
				oc_item.m_Text_WordAppearanceNum.Del	(index);
				oc_item.m_Text_WordFirstPosition.Del	(index);
			}
			else
			{
				break;
			}
		}
	}
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/