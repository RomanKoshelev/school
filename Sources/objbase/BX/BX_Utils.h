/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Utils.h                                                []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Вспомогательные функции                                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                               
#ifndef BX_Utils_H
#define BX_Utils_H

//----------------------------------------------------------------------------[] 
extern const byte	BitMask		[8];
extern const byte	BitMaskNot	[8];
//----------------------------------------------------------------------------[] 

bool
bitIntersect (	const byte* pBytePtr1, int nByteSize1,
					const byte* pBytePtr2, int nByteSize2);

bool
bitDiffer (		const byte* pBytePtr1, int nByteSize1,
					const byte* pBytePtr2, int nByteSize2);

bool
ba_IsEmpty(const byte_arr& ByteArr);


unsigned long
IP_2_ULONG(const string& IP);

bool
Email_IsValid(const string &);

bool
Time_IsValid(time_t Time);


char win_2_dos(char ch);
char * win_2_dos(char* str);
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//` ConceptItem                                                               []           
//                                                                            []
struct ConceptItem
{
	identifier		m_objID;
	int				m_nParent;
	string_arr		m_Name;
	string_arr		m_Descr;
	string			m_SysComment;
	int				m_SysCommentNo;
	string			m_ShortName;
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
		m_ShortName		=	 from.m_ShortName;
		return *this;
	}

	void DebugPrint ()
	{
		string _m_Name;		_m_Name.implode (m_Name, ", ");
		string _m_Descr;		_m_Descr.implode (m_Descr, ", ");
      printf ("------------------------------------------------------\n");
      printf ("m_objID        = [%lu]\n",	m_objID);
      printf ("m_Level        = [%d]\n",	m_Level);
      printf ("m_nParent      = [%d]\n",  m_nParent);
      printf ("m_Name         = [%s]\n",	_m_Name.c_str());
      printf ("m_Descr        = [%s]\n",	_m_Descr.c_str());
      printf ("m_SysComment   = [%s]\n",	m_SysComment.c_str());
      printf ("m_SysCommentNo = [%d]\n",	m_SysCommentNo);
      printf ("m_ShortName    = [%s]\n",	m_ShortName.c_str());
      printf ("------------------------------------------------------\n");
	}
};

//----------------------------------------------------------------------------[] 

BX_RESULT ConceptCompiler(void);

//----------------------------------------------------------------------------[] 
void	NormalizePackedArrInplace	(int_arr& RateArr);
void	NormalizePackedArr			(const int_arr& RateArrIn, int_arr& RateArrOut);
void	PackedArrIncrement			(int_arr& AbsArr, const int_arr& NormArr);
void	PackedArrNormalizedDiff		(int_arr& Result, const int_arr& _NormArr1, const int_arr& _NormArr2);
//----------------------------------------------------------------------------[]`


//----------------------------------------------------------------------------[]
// Изменние порядка следования элементов в массиве:
template <class T>
void ReverseOrder(CPtr<T>&	Arr)
{
	int	nSize			= Arr.Size();
	int	nHalfSize	= nSize / 2;
	int	i;
	T		Item;

	for (i = 0; i < nHalfSize; i++)
	{
		Item				= Arr[i];
		Arr[i]			= Arr[nSize-i];
		Arr[nSize-i]	= Item;
	}

	return;
}
//----------------------------------------------------------------------------[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/