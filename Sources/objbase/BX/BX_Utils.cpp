/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Utils.cpp                                              []
[] Date:            02.03.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#define USES_BX_Utils
#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_Concept
#define USES_BX_SingleObject
#define USES_BX_Admin
#include "BX.h"

//----------------------------------------------------------------------------[] 

const byte	BitMask		[8] = {1,   2,   4,   8,   16,  32,  64,  128};
const byte	BitMaskNot	[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

//----------------------------------------------------------------------------[] 

/*______________________________________________________________________________
[]                                                                            []
[]` bitIntersect                                                              []             
[]                                                                            []
[]____________________________________________________________________________[]
[] Эта функция возвращает true, если в байтовых массивах pBytePtr1 и pBytePtr2[]
[] имеются установленные биты, находящиеся на одинаковых позициях, и в false	[]
[] в противном случае.																			[]
[]____________________________________________________________________________*/
bool
bitIntersect (	const byte* pBytePtr1, int nByteSize1,
					const byte* pBytePtr2, int nByteSize2)
{
	int i=0;
	int nSize = min(nByteSize1, nByteSize2);
	for (i = 0; i < nSize; i++)
		if (pBytePtr1[i] & pBytePtr2[i])
			return true;
	return false;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` bitDiffer                                                                 []          
[]                                                                            []
[]____________________________________________________________________________[]
[] Эта функция возвращает true, если в байтовых массивах pBytePtr1 и pBytePtr2[]
[] имеются различные биты, находящиеся на одинаковых позициях, и в false		[]
[] в противном случае.	Пропущенные биты считаются нулевыми.						[]
[]____________________________________________________________________________*/ 

bool
bitDiffer (		const byte* pBytePtr1, int nByteSize1,
					const byte* pBytePtr2, int nByteSize2)
{
	int	nSize = min(nByteSize1, nByteSize2);
	for (int i = 0; i < nSize; i++)
		if (pBytePtr1[i] ^ pBytePtr2[i])
			return true;

	if (nByteSize1 > nByteSize2) {
		for (int i = nSize; i < nByteSize1; i++) {
			if (pBytePtr1[i] ^ 0) {
				return true;
			}
		}
	}
	else if (nByteSize1 < nByteSize2) {
		for (int i = nSize; i < nByteSize2; i++) {
			if (pBytePtr2[i] ^ 0) {
				return true;
			}
		}
	}

	return false;
}
//____________________________________________________________________________[]

 
//______________________________________________________________________________
//                                                                            []
//` ba_IsEmpty                                                                []          
//                                                                            []
bool	ba_IsEmpty(const byte_arr& ByteArr)
{
	const byte* pBytes = ByteArr.GetPtr();
			int	nSize	 = ByteArr.GetSize();
	for (int i = 0; i < nSize; i++)
		if (pBytes[i] != 0)
			return false;

	return true;

}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ba_Inverse                                                                []          
//                                                                            []
void	ba_Inverse(byte_arr& ByteArr)
{
	byte* pBytes = ByteArr.GetPtr();
	int	nSize	 = ByteArr.GetSize();
	for (int i = 0; i < nSize; i++) pBytes[i] = byte(~pBytes[i]);
	return;
}

//______________________________________________________________________________
//                                                                            []
//` IP_2_ULONG                                                                []          
//                                                                            []
unsigned long	IP_2_ULONG(const string& IP)
{
	const int MaxIP_Len = 256;
	if (IP.Size() > MaxIP_Len)
	{
		SERVER_DEBUG_ERROR_2 ("IP_2_ULONG(): Passed IP exceeds maximum length allowed (%i > %i). Returning 0 ...",
			IP.Size(), MaxIP_Len);
		return 0L;
	}

	char	IP_Copy[MaxIP_Len+1];
	strcpy(IP_Copy, IP.c_str());
	
	unsigned long	Result	= 0;
	int				TokenNum = 0;

	char *Token = strtok(IP_Copy, ".");
	while (Token != NULL)
	{
		if (TokenNum < 4) {
			Result	 |= (byte(atoi(Token)) << (TokenNum*8));
		}

		TokenNum++;

		if (TokenNum > 4)
		{
			SERVER_DEBUG_ERROR_1 ("IP_2_ULONG(): Fuck! Too many '.' in IP='%s' . Truncating ...", IP.c_str());
			break;
		}

		Token = strtok(NULL, ".");
	}

	return Result;
}

//______________________________________________________________________________
//                                                                            []
//` Email_IsValid                                                             []             
//                                                                            []
bool
Email_IsValid(const string &s)
{
	if (s.Len() == 0)
		return true;
	return (strchr(s.c_str(), '@') != NULL);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Time_IsValid                                                              []            
//                                                                            []

bool Time_IsValid(time_t Time)
{
	return (Time >= 0);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` win_2_dos                                                                 []         
//                                                                            []
char win_2_dos(char ch)
{
  if((unsigned char)ch>=192 && (unsigned char)ch<=223)
    return (char)((unsigned char)ch-64);
  if((unsigned char)ch>=224 && (unsigned char)ch<=239)
    return (char)((unsigned char)ch-64);
  if((unsigned char)ch>=240 && (unsigned char)ch<=255)
    return (char)((unsigned char)ch-16);
  return ch;
}
//______________________________________________________________________________
//                                                                            []
//` win_2_dos                                                                 []         
//                                                                            []
char * win_2_dos(char* str)
{
   for (int i=0; str[i]; i++)
   {
      str[i] = win_2_dos(str[i]);
   }
   return str;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ConceptCompiler                                                           []               
//                                                                            []
BX_RESULT ConceptCompiler(void)
{
	int i, j;
	CPtr<ConceptItem> arr_ConceptItem;
	string_arr			arr_sys_comments;
	
	string srcfile;
	srcfile.ReadFile ("./../concepts.h");
	string_arr arr_srcfile;
	string_arr arr_srcfile_tmp;

	srcfile.explode (arr_srcfile_tmp, "\n");

	for (i=0; i<arr_srcfile_tmp.Size();i++)
	{
		arr_srcfile_tmp[i].rtrim();
		if (strlen (arr_srcfile_tmp[i].c_str()))
			arr_srcfile += arr_srcfile_tmp[i];
	}

	string cur_sys_comment="";

	for (i=0; i<arr_srcfile.Size();i++)
	{
	// Находим имена
		string CurString = arr_srcfile[i];
		string Names = "";
		CurString.SubStr (Names, 0, CurString.Find("{"));
		string_arr arr_Names;
		string_arr arr_Descr;
		int Level = 0;
		for (Level = 0; Names[Level] == '\t'; Level++)
		{
			(void)NULL;
		}
		Names.explode (arr_Names, "|");

		for (j=0; j<arr_Names.Size(); j++)
		{
			arr_Names[j].trim();
		// Находим описания
			string CurDescr="No description";
			char SSS[10240];
			strcpy (SSS, arr_Names[j].c_str());
			char * pSys1 = strtok (SSS, "[");
			char * pSys2 = strtok (NULL, "]");
			if (pSys1 && pSys2)
			{
				CurDescr = pSys2;
			}
			arr_Descr += CurDescr;
			arr_Names[j] = SSS;
			arr_Names[j].trim();
		}

	// Находим системный комментарий
		char SSS[10240];
		int cur_sys_comment_no=-1;
		strcpy (SSS, CurString.c_str());
		char * pSys1 = strtok (SSS, "{");
		char * pSys2 = strtok (NULL, "}");
		if (pSys1 && pSys2)
		{
			cur_sys_comment = pSys2;
			cur_sys_comment.trim();
		}
		cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		if (cur_sys_comment_no==-1)
		{
			arr_sys_comments+=cur_sys_comment;
			cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		}

		int Parent=0;
		for (Parent=arr_ConceptItem.Size()-1; Parent>=0; Parent--)
		{
			if (arr_ConceptItem[Parent].m_Level<Level)
			{
				break;
			}
		}
		ConceptItem concept_item;
		concept_item.m_objID			= NA;
		concept_item.m_Level			= Level;
		concept_item.m_nParent		= Parent;
		concept_item.m_Name			= arr_Names;
		concept_item.m_Descr			= arr_Descr;
		concept_item.m_SysComment	= cur_sys_comment;
		concept_item.m_SysCommentNo= cur_sys_comment_no;
		concept_item.m_ShortName	= "";


		arr_ConceptItem += concept_item;
	}

/*	for (i=0; i<arr_sys_comments.Size(); i++)
	{
		printf ("%2d [%s]\n", i, arr_sys_comments[i].c_str());
	}
	printf ("\n\n");
*/
	int MaxLangNo =0;
	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		MaxLangNo = max (MaxLangNo, arr_ConceptItem[i].m_Name.Size());
	}

	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		while (arr_ConceptItem[i].m_Name.Size()<MaxLangNo)
		{
			const char *pName = "No name";
			if (arr_ConceptItem.Size() && strlen (arr_ConceptItem[i].m_Name[0].c_str()))
			{
				pName = arr_ConceptItem[i].m_Name[0].c_str();
			}

			arr_ConceptItem[i].m_Name += pName;
		}

		while (arr_ConceptItem[i].m_Descr.Size()<MaxLangNo)
		{
			const char *pDescr = "No description";
			if (arr_ConceptItem.Size() && strlen (arr_ConceptItem[i].m_Descr[0].c_str()))
			{
				pDescr = arr_ConceptItem[i].m_Descr[0].c_str();
			}

			arr_ConceptItem[i].m_Descr += pDescr;
		}
	}
//----------------------------------------------------------------------------[] 
// Создание концептов:
	printf("\nConcepts.h preprocessed. Creating concepts ");

	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		if (arr_ConceptItem[i].m_SysComment.Len() < 1)
		{
			printf ("\n * * Invalid Concept type %s * * \n", arr_ConceptItem[i].m_Name[0].c_str());
			continue;
		}

		BX_Concept_Args	concept_args;
		GetAdminPassword(concept_args.AdminPassword);
		concept_args.Name					= arr_ConceptItem[i].m_Name;
		concept_args.Description		= arr_ConceptItem[i].m_Descr;
		if (arr_ConceptItem[i].m_nParent >= 0)
		{
			concept_args.Parent			= arr_ConceptItem[arr_ConceptItem[i].m_nParent].m_objID;
		}

		concept_args.Type					= arr_ConceptItem[i].m_SysComment;
		concept_args.TypeNo				= arr_ConceptItem[i].m_SysCommentNo;
		concept_args.ShortName			= arr_ConceptItem[i].m_ShortName;

		BX_ASSERT_PASSIVE(BX_Concept_New(concept_args));

		arr_ConceptItem[i].m_objID = concept_args.objID;

		putchar('.');
/*		printf ("\n[%d]\n", i);
		arr_ConceptItem[i].DebugPrint();
*/	}

	printf("\nConcepts created: %d, System types: %d.\n",
		arr_ConceptItem.Size(), arr_sys_comments.Size());


	return BX_OK;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` NormalizePackedArrInplace                                                 []                          
//                                                                            []
void NormalizePackedArrInplace (int_arr& RateArr)
{
	int_arr	ParentNoArr;
	int_arr	ParentSumArr;
	int		i;
	int		nPos;
	int		No;
	int		ParentNo;
	int		Rate;
	int		MaxNo = oc_reg.m_ConceptParent_SortNo.Size();

// Суммирование по родителям:
	for (i = 0; i < RateArr.Size(); i++)
	{
		No = RateArr[i] >> 16;
		if ((No < MaxNo) && ((ParentNo = oc_reg.m_ConceptParent_SortNo[No]) != -1))
		{
			if ((nPos = ParentNoArr.Find(ParentNo)) < 0)
			{
				ParentNoArr.Add(ParentNo);
				ParentSumArr.Add(RateArr[i] & 0xffff);
			}
			else
			{
				ParentSumArr[nPos] += RateArr[i] & 0xffff;
			}
		}
		else
		{
			RateArr.Del(i);
			i--;
		}
	}

// Нормализация:
	for (i = 0; i < RateArr.Size(); i++)
	{
		No = RateArr[i] >> 16;

	// Получим индекс родительской суммы:
		nPos	= ParentNoArr.Find(oc_reg.m_ConceptParent_SortNo[No]);
	// Нормализуем:
		Rate	= ParentSumArr[nPos] != 0 ?
							(RateArr[i] & 0x0000ffff) * CONCEPT_NORM_BASE / ParentSumArr[nPos]
							: 0;
	// Положим обратно:
		if (Rate != 0) {
			RateArr[i] = (No << 16) | Rate;
			RateArr[i] = (No << 16) | Rate;
		}
		else
		{
			RateArr.Del(i);
			i--;
		}
	}

	return;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` NormalizePackedArr                                                        []                  
//                                                                            []
void NormalizePackedArr (const int_arr& RateArrIn, int_arr& RateArrOut)
{
	int_arr	ParentNoArr;
	int_arr	ParentSumArr;
	int		i;
	int		nPos;
	int		No;
	int		ParentNo;
	int		Rate;
	int		MaxNo = oc_reg.m_ConceptParent_SortNo.Size();

	RateArrOut.Erase();

// Суммирование по родителям:
	for (i = 0; i < RateArrIn.Size(); i++)
	{
		No = RateArrIn[i] >> 16;
		if ((No < MaxNo) && ((ParentNo = oc_reg.m_ConceptParent_SortNo[No]) != -1))
		{
			RateArrOut.Add(RateArrIn[i]);
			if ((nPos = ParentNoArr.Find(ParentNo)) < 0)
			{
				ParentNoArr.Add(ParentNo);
				ParentSumArr.Add(RateArrIn[i] & 0xffff);
			}
			else
			{
				ParentSumArr[nPos] += RateArrIn[i] & 0xffff;
			}
		}
	}

// Нормализация:
	for (i = 0; i < RateArrOut.Size(); i++)
	{
		No = RateArrOut[i] >> 16;

	// Получим индекс родительской суммы:
		nPos	= ParentNoArr.Find(oc_reg.m_ConceptParent_SortNo[No]);
	// Нормализуем:
		Rate	= ParentSumArr[nPos] != 0 ?
							(RateArrOut[i] & 0x0000ffff) * CONCEPT_NORM_BASE / ParentSumArr[nPos]
							: 0;
	// Положим обратно:
		if (Rate != 0) {
			RateArrOut[i] = (No << 16) | Rate;
		}
		else
		{
			RateArrOut.Del(i);
			i--;
		}
	}

	return;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` PackedArrIncrement                                                        []                  
//                                                                            []
void PackedArrIncrement (int_arr& AbsArr, const int_arr& NormArr)
{
	int  i = 0;
	int  j = 0;
	int _j = 0;

	int_arr DivideParentArr;

	bool bNeedDivide = false;

	for (i=0; i < NormArr.Size(); i++)
	{
		int	NormArr_i_no	 = NormArr[i] >> 16;
		short NormArr_i_rate  = (short) (NormArr[i] & 0x0000ffff);
		for (j=_j; j<=AbsArr.Size(); j++)
		{
		// Если НЕ нашли номер
			int AbsArr_Size = (int)AbsArr.Size();
			int AbsArr_j_no = j<AbsArr_Size? (int)(AbsArr[j] >> 16): 0xFFFFFFFF;
			if ((j>=AbsArr_Size) || (NormArr_i_no < AbsArr_j_no))
			{
				AbsArr.Insert (j, 0);
				AbsArr[j] = (NormArr_i_no << 16 ) | ((unsigned short)NormArr_i_rate);
				_j = j+1;
				break;
			}
		// Если нашли номер
			else if (NormArr_i_no == AbsArr_j_no)
			{
				short AbsArr_j_rate = short ((AbsArr[j] & 0x0000ffff) + NormArr_i_rate);
				
				AbsArr[j] = (NormArr_i_no << 16) | ((unsigned short)AbsArr_j_rate);

				if (AbsArr_j_rate > (SHRT_MAX - 2*CONCEPT_NORM_BASE))
				{
					bNeedDivide = true;
					DivideParentArr.InsertSorted(oc_reg.m_ConceptParent_SortNo[AbsArr_j_no]);
				}

				_j = j+1;
				break;
			}
		}
	}

	if (bNeedDivide)
	{
		for (i=0; i<AbsArr.Size(); i++)
		{
			int   AbsArr_j_no   = int   (AbsArr[i] >> 16);
			short AbsArr_j_rate = short (AbsArr[i] & 0x0000ffff);

			if (DivideParentArr.Find(oc_reg.m_ConceptParent_SortNo[AbsArr_j_no], true) >= 0)
			{
				if (AbsArr_j_rate <2)
				{
					AbsArr.Del (i);
					i --;
				}
				else
					AbsArr [i] = (AbsArr_j_no << 16) | (AbsArr_j_rate/2);
			}
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` PackedArrNormalizedDiff                                                   []                       
//                                                                            []

void	PackedArrNormalizedDiff(int_arr& Result,
										const int_arr& _NormArr1,
										const int_arr& _NormArr2)
{
	int i;
	int_arr	NormArr1, NormArr2;
	NormArr1 = _NormArr1;
	NormArr2 = _NormArr2;
	int_arr	NormArr1_no_arr;


	for (i=0; i<NormArr2.Size(); i++) 
	{
		short Rate			=  short(NormArr2[i] & 0xffff);
		unsigned short No = (unsigned short)(NormArr2[i] >> 16);
		NormArr2[i] = (No << 16) | (unsigned short)(-Rate);
	}

	for (i=0; i<NormArr1.Size(); i++) 
	{
		unsigned short No = (unsigned short)(NormArr1[i] >> 16);
		NormArr1_no_arr += No;
	}

	PackedArrIncrement(NormArr1, NormArr2);

	short minRate = SHRT_MAX;
	for (i=0; i<NormArr1.Size(); i++) 
	{
		short Rate	=  short(NormArr1[i] & 0xffff);
		if (Rate < minRate)
			minRate = Rate;
	}

	for (i=0; i<NormArr1.Size(); i++)
	{
		unsigned short No = (unsigned short)(NormArr1[i] >> 16);
		if (NormArr1_no_arr.Find (No)==-1)
		{
			NormArr1.Del (i);
			i--;
		}
	}
	
	if (minRate<0)
	{
		for (i=0; i<NormArr1.Size(); i++) 
		{
			short			Rate	=  short(NormArr1[i] & 0xffff);
			unsigned short No = (unsigned short)(NormArr1[i] >> 16);
			Rate = (short) (Rate - minRate);
			NormArr1[i] = (No << 16) | (unsigned short)(Rate);
		}
	}

	NormalizePackedArr (NormArr1, Result);
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/