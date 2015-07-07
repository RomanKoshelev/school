/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            MOD_Concept.h                                             []
[] Date:            04.05.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/

#ifndef MOD_Concept_h
#define MOD_Concept_h



/*______________________________________________________________________________
[]                                                                            []
[]` GET_PERCENT                                                               []
[]                                                                            */
inline int GET_PERCENT(int N, int NN)
{
	return (NN != 0) ? (N * 100 / NN) : (N==0 ? 0:100);
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_ASSERT                                                                []
[]                                                                            */
#define	OBJ_ASSERT(FunctionCall)															\
	{																									\
		if (FunctionCall != ERR_OK)															\
		{																								\
			SERVER_DEBUG_ERROR("OBJ_ASSERT: error in " #FunctionCall );				\
			return;																					\
		}																								\
	}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_ASSERT_PASSIVE                                                         []
[]                                                                            */
#define	OBJ_ASSERT_PASSIVE(FunctionCall)													\
	{																									\
		ERR_RESULT	BAR_result;																	\
		BAR_result = FunctionCall;																\
		if (BAR_result != ERR_OK)																\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"OBJ_ASSERT: error #%d in " #FunctionCall,								\
				 BAR_result);																		\
		}																								\
	}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_ASSERT_RETURN                                                         []
[]                                                                            */
#define	OBJ_ASSERT_RETURN(FunctionCall)													\
	{																									\
		ERR_RESULT	BAR_result;																	\
		BAR_result = FunctionCall;																\
		if (BAR_result != ERR_OK)																\
		{																								\
			SERVER_DEBUG_ERROR_1(																\
				"OBJ_ASSERT: error #%d in " #FunctionCall ". Aborted.",			\
				 BAR_result);																		\
			return BAR_result;																	\
		}																								\
	}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_CHECK                                                                 []
[]                                                                            */
#define OBJ_CHECK(_id_,_class_)																\
	if (!OC_Exist(_class_, _id_))																\
	{																									\
		SERVER_DEBUG_ERROR_1("OBJ_CHECK Macro: Invalid id #%d of class " #_class_ "." , (int)_id_);	\
		return ERR_SYSTEM_ERROR;																	\
	}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_CHECK_AND_OPEN                                                        []
[]                                                                            */
#define OBJ_CHECK_AND_OPEN(_oc_,_id_,_class_)												\
{																										\
	_oc_.Open(_id_);																				\
	if (!_oc_.IsValid())																			\
	{																									\
		string	Str;																				\
		Str.Format(																					\
			"OBJ_CHECK_AND_OPEN Macro: Invalid id #%lu of class " #_class_ ". Aborted." ,\
			(unsigned long)_id_);																\
		SERVER_DEBUG_TEXT(Str.c_str());														\
		return ERR_SYSTEM_ERROR;																	\
	}																									\
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` OBJ_CREATE_AND_CHECK                                                      []
[]                                                                            */
#define OBJ_CREATE_AND_CHECK(_oc_)															\
{																										\
	_oc_.New();																						\
	if (!_oc_.IsValid())																			\
	{																									\
		SERVER_DEBUG_ERROR(																		\
			"OBJ_CREATE_AND_CHECK Macro: Error creating new instance of " #_oc_ ". Aborted.");\
		return ERR_SYSTEM_ERROR;																	\
	}																									\
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` DELETE_FROM_ARRAY                                                         []                 
//                                                                            []
// �������� �������� � �������� ��������� �� �������.									[]
#define	DELETE_FROM_ARRAY(element_arr, element)										\
{																										\
	int DFA_i = 0;																					\
	while (DFA_i<(element_arr).Size())														\
	{																									\
		if ((element_arr)[DFA_i] == (element))												\
		 (element_arr).Del(DFA_i); 															\
		else DFA_i++;																				\
	}																									\
}																	
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ConceptItem                                                               []           
//                                                                            []
struct ConceptItem
{
	identifier		m_objID;
	int				m_nParent;
	string			m_Name;
	string			m_Descr;
	string			m_SysComment;
	int				m_SysCommentNo;
	int				m_Level;

	ConceptItem ()
	{
		m_Level			= 0;
		m_objID			= NA;
		m_nParent		= -1;
		m_SysCommentNo	= -1;
	}

	ConceptItem (const ConceptItem& from)
	{
		CopyFrom (from);
	}

	ConceptItem& operator = (const ConceptItem& from)
	{
		return CopyFrom (from);
	}

	ConceptItem& CopyFrom (const ConceptItem& from)
	{
		m_objID			=	 from.m_objID;
		m_Level			=	 from.m_Level;
		m_nParent		=	 from.m_nParent;
		m_Name			=	 from.m_Name;
		m_Descr			=	 from.m_Descr;
		m_SysComment	=	 from.m_SysComment;
		m_SysCommentNo	=	 from.m_SysCommentNo;
		return *this;
	}

	void DebugPrint ()
	{
      printf ("------------------------------------------------------\n");
      printf ("m_objID        = [%lu]\n",	m_objID);
      printf ("m_Level        = [%d]\n",	m_Level);
      printf ("m_nParent      = [%d]\n",  m_nParent);
      printf ("m_Name         = [%s]\n",	m_Name.c_str());
      printf ("m_Descr        = [%s]\n",	m_Descr.c_str());
      printf ("m_SysComment   = [%s]\n",	m_SysComment.c_str());
      printf ("m_SysCommentNo = [%d]\n",	m_SysCommentNo);
      printf ("------------------------------------------------------\n");
	}
};














//______________________________________________________________________________
// 																									[]
//` Concept																							[] 	 
// 																									[]

struct MOD_Concept_Args
{ 
	MOD_Concept_Args()
	{
		ParentID			= NA;
		Level				= -1;
		TypeNo			= -1;
		No					= -1;
		objID				= NA;
		objFirstNo		= 0;
		objLastNo		= INT_MAX;
		Indent			= false;
	}

	identifier		ParentID;		// Id �������� - �� ���� ������ ���� ����� NA ������ � ����� ������
	string			Name; 			// ������ �������� �������� �� ���� ������, ��������� � �������.
	string			Description;	// ������ �������� �������� �� ���� ������, ��������� � �������.
	int				Level;			// ������� �������� � ������ ������������ ��������.
	string_arr		ConceptType;	// ��� �������� (��� Extended Enumerate).
	int				No;				// ���������� ����� �������� - ������������ ��� MOD_Concept_GetData.
	string			Type;				// ��� ��������.
	int				TypeNo;			// ����� ���� ��������.
	int				objFirstNo;		// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
	int				objLastNo;		// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.

	bool				Indent;
	identifier		objID;			// ������������� �������.
	int_arr			objNums;			// ������ ������� ��������.
	identifier_arr objIDs;			// ������ ��������������� ��������.
	string_arr		objNames;		// ������ �������� ��������.
	string			PicklockPassword;	// ������-�������
};
//----------------------------------------------------------------------------[] 

// �������� ��������.
// � ������ �������� ������������� ���������� �������� ������������ � objID.
ERR_RESULT MOD_Concept_New(MOD_Concept_Args& arg);

// ����������� ���������� ������������� �������� � ��������������� objID.
ERR_RESULT MOD_Concept_PutData(MOD_Concept_Args& arg);

// ��������� ��������������� ���� ���������
// ������� '� ������', �.�. � ������� ����������� ������.
ERR_RESULT MOD_Concept_Enumerate(MOD_Concept_Args& arg);

// �������� ������ ��������������� � �������� ��������� ��������� ������ �� 
// �������� ����� � ���������� ��������� � ������������ � �������.
// �������� ��������� '� �������', �.�. � ������� ���������� ���������.
// ���� ������ Level, �� ��������� �������� � ������� �� Level ������������,
// ����� - ��� ��������.
// ���� Indent == true, �� ����� ������ �������� ����������� ������
// ���������� �������� � html-�������.
ERR_RESULT MOD_Concept_ExtendedEnumerate(MOD_Concept_Args& arg);

// ��������� ���������� � �������� � ��������� ��������������� objID.
ERR_RESULT MOD_Concept_GetData(MOD_Concept_Args& arg);

// �������� �������� � ��������� ��������������� objID.
// ��� ������� �������� ����� ���������.
ERR_RESULT MOD_Concept_Delete(MOD_Concept_Args& arg);

//----------------------------------------------------------------------------[] 

ERR_RESULT ExpandConcept					(identifier_arr &concept_arr);
ERR_RESULT ExpandWithParentConcepts	(identifier_arr &concept_arr);

//____________________________________________________________________________[]




//----------------------------------------------------------------------------[] 
extern const byte	BitMask		[8];
extern const byte	BitMaskNot	[8];
//----------------------------------------------------------------------------[] 

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
	idArr.Erase ();																				\
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
//` SetBit                                                                    []      
//                                                                            []
inline void SetBit(byte_arr &bitArr, int nPos)
{
	int SB_byteNo = nPos >> 3;
	int SB_addLen = SB_byteNo - bitArr.Size();
	for (int SB_i = 0; SB_i <= SB_addLen; SB_i++) {
		bitArr.Add(0);	/*��������, ���� ������ ������� �������*/
	}
	bitArr[SB_byteNo] |= BitMask[nPos % 8];
	return;
}
//______________________________________________________________________________
//                                                                            []
//` ClearBit                                                                  []        
//                                                                            []
inline void ClearBit(byte_arr &bitArr, int nPos)
{
	int SB_byteNo = nPos >> 3;
	int SB_addLen = SB_byteNo - bitArr.Size();
	if (SB_addLen < 0) {	/*���� ����� �������� ��� � �������� �������*/
		bitArr[SB_byteNo] &= BitMaskNot[nPos % 8];
	}
	return;
}
//____________________________________________________________________________[]

//----------------------------------------------------------------------------[]`
inline bool GetBit(const byte_arr& bitArr, int nPos)
{
	int GB_byteNo = nPos >> 3;
	if (GB_byteNo < bitArr.Size()) {
		return ( (bitArr[GB_byteNo] & BitMask[nPos % 8]) != 0);
	}
	else {
		return false;
	}
}
//____________________________________________________________________________[]





// ���������� ������ ����� ��������� � �� ��������.
ERR_RESULT	MOD_Concept_TypeEnumerate		(MOD_Concept_Args& arg);
bool			ConceptHasDescendantWithName	(identifier FeodID, const char * descName);
ERR_RESULT	ConceptCompiler					(const char * sFileName);
identifier	GetConceptID						(const char * Name, const char * Type="Concept", bool JustCheck=false);
bool			GetConceptName						(identifier objID, string& objName);
bool			GetConceptFullName				(identifier objID, string& objName, int nLevel=0, const char* sDelimiter="\\");
int			ConceptGetUnicTypeNo				();
//----------------------------------------------------------------------------[]
#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/