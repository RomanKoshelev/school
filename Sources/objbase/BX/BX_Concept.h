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
[] Description:     ������� ��� ������ � �������� "�������"                   []
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

	READONLY identifier		Parent;			// Id �������� - �� ���� ������ ���� ����� NA ������ � ����� ������
				string_arr		Name; 			// ������ �������� �������� �� ���� ������, ��������� � �������.
				string_arr		Description;	// ������ �������� �������� �� ���� ������, ��������� � �������.
	READONLY int				Level;			// ������� �������� � ������ ������������ ��������.
				string_arr		ConceptType;	// ��� �������� (��� Extended Enumerate).
	READONLY int				No;				// ���������� ����� �������� - ������������ ��� BX_Concept_GetData.
				string			ShortName;		// ����������� ���.
				string			Type;				// ��� ��������.
				int				TypeNo;			// ����� ���� ��������.
				int				objLanguageNo;	// ���������� ����� �����, �� ������� �������� ���������� �������� *Enumerate().
				int				objFirstNo;		// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;		// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

				int				SiteCount;		// ���-�� ������ � ������ ���������.
				bool				Indent;
				identifier		VBN;				// ������������� ����������� ����.
				identifier		objID;			// ������������� �������.
				int_arr			objNums;			// ������ ������� ��������.
	READONLY identifier_arr objIDs;			// ������ ��������������� ��������.
	READONLY string_arr		objNames;		// ������ �������� �������� �� ����� � ������� objLanguageNo.
				string			AdminPassword;	// ������ ��������������.
};
//----------------------------------------------------------------------------[] 

// �������� ��������.
// � ������ �������� ������������� ���������� �������� ������������ � objID.
BX_RESULT BX_Concept_New(BX_Concept_Args& arg);

// ����������� ���������� ������������� �������� � ��������������� objID.
BX_RESULT BX_Concept_PutData(BX_Concept_Args& arg);

// ��������� ��������������� ���� ��������� �� ����� # objLanguageNo
// ������� '� ������', �.�. � ������� ����������� ������.
BX_RESULT BX_Concept_Enumerate(BX_Concept_Args& arg);

// �������� ������ ��������������� � �������� ��������� ��������� ������ �� 
// �������� ����� � ���������� ��������� � ������������ � �������.
// �������� ��������� '� �������', �.�. � ������� ���������� ���������.
// ���� ������ Level, �� ��������� �������� � ������� �� Level ������������,
// ����� - ��� ��������.
// ���� ������ objLanguage, �� �� ���������� ���� ��������, ����� ���� ����� �����
// VBN, ����� - �������� �����.
// ���� ������ VBN, �� ��������� �������� �������� VBN.
// ���� SiteCount > 0, �� � ����� �������� ����������� ���������� ������ � 
// ������ ���������, ������ ���� ������� VBN, �� ������ � ������ VBN.
// ���� Indent == true, �� ����� ������ �������� ����������� ������
// ���������� �������� � html-�������.
BX_RESULT BX_Concept_ExtendedEnumerate(BX_Concept_Args& arg);

// ��������� ���������� � �������� � ��������� ��������������� objID.
BX_RESULT BX_Concept_GetData(BX_Concept_Args& arg);

// �������� �������� � ��������� ��������������� objID.
// ��� ������� �������� ����� ���������.
BX_RESULT BX_Concept_Delete(BX_Concept_Args& arg);

// �������� ���-�� ������ � ������ ��������� ��� ���������� VBN.
// ���� vbn �� ������ ��� �� ��������, �� �������� ���������� �� ���� VBN.
BX_RESULT BX_Concept_GetSiteCount(BX_Concept_Args& arg);


// ������� id ����� �� ������� ������ ���� idVBN ��� �������� �� ������� conceptIDs.
BX_RESULT BX_Concept_DeleteSite(const identifier_arr& idConcept, identifier idSite, identifier idVBN);

// ��������� id ����� � ������ ������ �� ���� idVBN ��� �������� �� ������� conceptIDs.
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
// ������� ������ �������������� ���������.												[]
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
// ������� ������ �������������� �� ���������.											[]
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
// ���� ������ ���������� � �������� ������� bitArr ����, ���������������  	[]
// ��������������� �� ������� idArr. ����� ����, ��������������� �������, 	   []
// ������������ �� ���� OC_Name::m_No �����������, ������� ������ �����      	[]
// ������ �� ����� ����. ������� ������ �������������� �� ���������.      	   []
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
// ���� ������ ������� � ������ idArr �������������� �������� ������ OC_Name,	[]
// ��������������� ������������� ����� �� ��������� ������� bitArr.           []
#define _BitsToIDs(idArr,bitArr)																\
{																										\
	idArr.Delete();																				\
	int BTI_byteSize = bitArr.Size();														\
	int BTI_MaxNo	= oc_reg.m_ConceptID_SortNo.Size();									\
	int BTI_i, BTI_j, BTI_pos;																	\
	const byte * BTI_bytePtr = bitArr.GetPtr();											\
/*�� ���� ������:	*/																				\
	for (BTI_i = 0; BTI_i < BTI_byteSize; BTI_i++) 										\
		if (BTI_bytePtr[BTI_i] != 0)															\
		/*�� ���� �����:	*/																		\
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
// ���������� ����� �������� ���� ConceptType 3�� ������ � �������������		[]
// ViewerParam, �������� ����� ������� � ������ �������������.						[]
// ���������� -1 � ������ ���������� ���� ConceptType ��� � ������ ������		[]
// �������� ��������.																			[]
//----------------------------------------------------------------------------[]`

int ViewerParamsToConcepts(const char * ConceptType, const string& ViewerParam);

//______________________________________________________________________________
//                                                                            []
//` Concept_IncreaseRate                                                      []                    
//                                                                            []
// ����������� �������� �������������, ���������������� �������� � �������		[]
// No, �� �������� Increment.																	[]
// ��� ������������� ���� ����� �����������.
// ���������� ������ ��� ����� �������� � �������������.
int
ConceptRate_Increase(int No, int Increment, int_arr& RateArr);


//______________________________________________________________________________
//                                                                            []
//` Concept_IsFind                                                            []             
//                                                                            []
// ���������� ������ �������� ������������� �� ������� RateArr,
// ���������������� ������ No, ��� -1, ���� ������ ���.
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

// ���������� ������ ����� ��������� � �� ��������.
BX_RESULT BX_Concept_TypeEnumerate(BX_Concept_Args& arg);

// ������� �� ������������� CR �������� � ������ �� Types[].
BX_RESULT BX_Concept_FilterType(int_arr& CR, const int_arr& Types);

// ���������� ������������� ���� ��������� ��� �������.
BX_RESULT BX_Concept_SetFilter(BX_Concept_Args& arg);

// �������� ������������� ���� ��������� ��� �������.
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