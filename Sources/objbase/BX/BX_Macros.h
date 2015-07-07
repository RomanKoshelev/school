/*
____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'BX'													[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  BX_Macros.h															[]
[] Date: 			  01.06.99																[]
[] Author:			  Alex Vershinin														[]
[] Description:	  Макросы																[]
[] Last Modified:																				[]
[]_________________________________________________________________________[]
Соглашение об именах: во избежание труднообнаруживаемых ошибок все локальные
переменные в макросах должны иметь уникальные (во всех модулях) имена,
а именно: начинаться с сокращения названия макроса и подчерка_.				*/
#ifndef	BX_MACROS_H
#define	BX_MACROS_H



//______________________________________________________________________________
//                                                                            []
//` GET_PERCENT                                                               []           
//                                                                            []
inline int GET_PERCENT(int N, int NN)
{
	return (NN != 0) ? (N * 100 / NN) : (N==0 ? 0:100);
}

//______________________________________________________________________________
//                                                                            []
//` BX_TRACE                                                                  []        
//                                                                            []
#ifdef BX_TRACE_ENABLED
	#ifdef WIN32	// WINDOWS
		#define BX_TRACE(str)							{puts(str);}
		#define BX_TRACE_1(str, a1)					{printf(str, a1);}
		#define BX_TRACE_2(str, a1, a2)				{printf(str, a1,a2);}
		#define BX_TRACE_3(str, a1, a2, a3)			{printf(str, a1,a2,a3);}
	#else				// UNIX ?
		#define BX_TRACE(str)							{SERVER_DEBUG_ERROR(str);}
		#define BX_TRACE_1(str, a1)					{SERVER_DEBUG_ERROR_1(str, a1);}
		#define BX_TRACE_2(str, a1, a2)				{SERVER_DEBUG_ERROR_2(str, a1,a2);}
		#define BX_TRACE_3(str, a1, a2, a3)			{SERVER_DEBUG_ERROR_3(str, a1,a2,a3);}
	#endif
#else
		#define BX_TRACE(str)							{}
		#define BX_TRACE_1(str, a1)					{}
		#define BX_TRACE_2(str, a1, a2)				{}
		#define BX_TRACE_3(str, a1, a2, a3)			{}
#endif
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` BX_ASSERT			                                                         []         
//                                                                            []
// Используется для вызовов BX-функций.
#define	BX_ASSERT(FunctionCall)																\
	{																									\
		if (FunctionCall != BX_OK)																\
		{																								\
			SERVER_DEBUG_ERROR("BX_ASSERT: BX error in " #FunctionCall );			\
			return;																					\
		}																								\
	}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_ASSERT_PASSIVE                                                         []                 
//                                                                            []
#define	BX_ASSERT_PASSIVE(FunctionCall)													\
	{																									\
		BX_RESULT	BAR_result;																	\
		BAR_result = FunctionCall;																\
		if (BAR_result != BX_OK)																\
		{																								\
			SERVER_DEBUG_ERROR_1("BX_ASSERT: Non-System error #%d in " #FunctionCall,\
				 BAR_result);																		\
		}																								\
	}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_ASSERT_RETURN                                                          []         
//                                                                            []
// Используется для вложенных вызовов BX-функций.
#define	BX_ASSERT_RETURN(FunctionCall)													\
	{																									\
		BX_RESULT	BAR_result;																	\
		BAR_result = FunctionCall;																\
		if (BAR_result != BX_OK)																\
		{																								\
			SERVER_DEBUG_ERROR_1("BX_ASSERT: Non-System error #%d in " #FunctionCall,\
				 BAR_result);																		\
			return BAR_result;																	\
		}																								\
	}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_CHECK                                                                  []        
//                                                                            []
#define BX_CHECK(_id_,_class_)																\
	if (!OC_Exist(_class_, _id_))																\
	{																									\
		SERVER_DEBUG_ERROR_1("BX_CHECK Macro: Invalid id #%d of class " #_class_ "." , (int)_id_);	\
		return BX_SYSTEM_ERROR;																	\
	}
//______________________________________________________________________________
//                                                                            []
//` BX_CHECK_AND_OPEN                                                         []                 
//                                                                            []
#define BX_CHECK_AND_OPEN(_oc_,_id_,_class_)												\
{																										\
	_oc_.Open(_id_);																				\
	if (!_oc_.IsValid())																			\
	{																									\
		string	Str;																				\
		Str.Format("BX_CHECK_AND_OPEN Macro: Invalid id #%lu of class " #_class_ "." , (unsigned long)_id_);	\
		SERVER_DEBUG_TEXT(Str.c_str());														\
		return BX_SYSTEM_ERROR;																	\
	}																									\
}

//______________________________________________________________________________
//                                                                            []
//` BX_CREATE_AND_CHECK                                                       []                   
//                                                                            []
#define BX_CREATE_AND_CHECK(_oc_)															\
{																										\
	_oc_.New();																						\
	if (!_oc_.IsValid())																			\
	{																									\
		SERVER_DEBUG_ERROR("BX_CREATE_AND_CHECK Macro: Error creating new instance of " #_oc_ );	\
		return BX_SYSTEM_ERROR;																	\
	}																									\
}

//______________________________________________________________________________
//                                                                            []
//` _SetBit                                                                   []       
//                                                                            []
// Этот макрос устанавливает в байтовом массиве bitArr бит с номером nPos		[]
// равным значению булевой переменной bValue .											[]
#define _SetBit(bitArr, nPos, bValue)														\
{																										\
	int SB_byteNo = nPos >> 3;																	\
	int SB_addLen = SB_byteNo - bitArr.Size();											\
	switch (bValue)																				\
	{																									\
	case false:																						\
		if (SB_addLen < 0) {	/*если нужно сбросить бит в пределах массива*/		\
			bitArr[SB_byteNo] &= BitMaskNot[nPos % 8];									\
		}																								\
		break;																						\
	case true:																						\
		for (int SB_i = 0; SB_i <= SB_addLen; SB_i++) {									\
			bitArr.Add(0);	/*дополним, если массив слишком короток*/					\
		}																								\
		bitArr[SB_byteNo] |= BitMask[nPos % 8];											\
		break;																						\
	}																									\
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` SetBit                                                                    []      
//                                                                            []
inline void SetBit(byte_arr &bitArr, int nPos)
{
	int SB_byteNo = nPos >> 3;
	int SB_addLen = SB_byteNo - bitArr.Size();
	for (int SB_i = 0; SB_i <= SB_addLen; SB_i++) {
		bitArr.Add(0);	/*дополним, если массив слишком короток*/
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
	if (SB_addLen < 0) {	/*если нужно сбросить бит в пределах массива*/
		bitArr[SB_byteNo] &= BitMaskNot[nPos % 8];
	}
	return;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` _GetBit                                                                   []       
//                                                                            []
// Этот макрос устанавливает булеву переменную bValue равной значению бита		[]
// с номером nPos в байтовом массиве bitArr.												[]
#define _GetBit(bitArr, nPos, bValue)														\
{																										\
	int GB_byteNo = nPos >> 3;																	\
	if (GB_byteNo < bitArr.Size()) {															\
		bValue = ( (bitArr[GB_byteNo] & BitMask[nPos % 8]) != 0);					\
	}																									\
	else {																							\
		bValue = false;																			\
	}																									\
}
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

//______________________________________________________________________________
//                                                                            []
//` DELETE_FROM_ARRAY                                                         []                 
//                                                                            []
// Удаление элемента с заданным значением из массива.									[]
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
//` VALIDATE_ID                                                               []           
//                                                                            []
// Проверка валидности идентификатора.
// Невалидный идентификатор устанавливается в NA.
#define VALIDATE_ID(_class_ID, _id)															\
	if ( (_id != NA) && (!OC_Exist(_class_ID, _id)) )									\
	{																									\
		string	Str;																				\
		Str.Format("Macro VALIDATE_ID erased invalid ID #%lu of class %s.",		\
			(unsigned long)_id, className[_class_ID]);									\
		SERVER_DEBUG_TEXT(Str.c_str());														\
		_id = NA;																					\
	}
//____________________________________________________________________________[]

	
//______________________________________________________________________________
//                                                                            []
//` VALIDATE_ID_ARRAY                                                         []                 
//                                                                            []
// ПРОВЕРКА ВАЛИДНОСТИ ИДЕНТИФИКАТОРОВ В МАССИВЕ CPtr<> или CSmartFieldArray.
// Невалидные идентификаторы удаляются из массива.

#define VALIDATE_ID_ARRAY(_class_ID, _arr)												\
{																										\
	int VIA_i, VIA_x;																				\
	for (VIA_i = 0; VIA_i < _arr.Size(); VIA_i++)										\
	{																									\
		/* проверка на повторы: */																\
		while (((VIA_x= _arr.Find(_arr[VIA_i])) != -1) && (VIA_x>VIA_i))			\
			_arr.Del(VIA_x);																		\
		/* проверка на валидность: */															\
		if (!OC_Exist(_class_ID, _arr[VIA_i]))												\
		{																								\
			string	Str;																			\
			Str.Format(																				\
				"Macro VALIDATE_ID_ARRAY erased invalid ID #%lu of class %s.",		\
				(unsigned long)_arr[VIA_i], className[_class_ID]);						\
			SERVER_DEBUG_TEXT(Str.c_str());													\
																										\
			_arr.Del(VIA_i);																		\
			VIA_i--;																					\
		}																								\
	}																									\
}
//____________________________________________________________________________[]




//----------------------------------------------------------------------------[] 
#define INCREMENT_SITE_COUNTER_WO_SYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
	}
//----------------------------------------------------------------------------[] 
#define UPDATE_SITE_COUNTER_WO_SYNC(_CounterName)										\
	{																									\
		time_stats_args.Increment			= 0;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName			= time_stats_args.idCounter;				\
	}
//----------------------------------------------------------------------------[] 
#define INCREMENT_VBN_COUNTER_WO_SYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_vbn.m_##_CounterName;					\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_vbn.m_##_CounterName				= time_stats_args.idCounter;				\
	}
//----------------------------------------------------------------------------[] 
#define INCREMENT_SITE_COUNTER_W_TOTALSYNC(_CounterName)								\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
																										\
		oc_site.m_Total_##_CounterName	= time_stats_args.Total;					\
	}
#define UPDATE_SITE_COUNTER_W_TOTALSYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 0;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
																										\
		oc_site.m_Total_##_CounterName	= time_stats_args.Total;					\
	}
//----------------------------------------------------------------------------[] 
#define INCREMENT_VBN_COUNTER_W_TOTALSYNC(_CounterName)								\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_vbn.m_##_CounterName;					\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_vbn.m_##_CounterName				= time_stats_args.idCounter;				\
																										\
		oc_vbn.m_Total_##_CounterName		= time_stats_args.Total;					\
	}
#define UPDATE_VBN_COUNTER_W_TOTALSYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 0;												\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_vbn.m_##_CounterName;					\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_vbn.m_##_CounterName				= time_stats_args.idCounter;				\
																										\
		oc_vbn.m_Total_##_CounterName		= time_stats_args.Total;					\
	}
//----------------------------------------------------------------------------[] 
#define INCREMENT_SITE_COUNTER_W_LASTSYNC(_CounterName)								\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= true;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
																										\
		oc_site.m_Total_##_CounterName	= time_stats_args.Total;					\
		oc_site.m_LM_##_CounterName		= time_stats_args.LM;						\
		oc_site.m_LW_##_CounterName		= time_stats_args.LW;						\
		oc_site.m_LD_##_CounterName		= time_stats_args.LD;						\
		oc_site.m_LH_##_CounterName		= time_stats_args.LH;						\
	}
#define GROW_SITE_COUNTER_W_LASTSYNC(_GrowValue, _CounterName)						\
	{																									\
		time_stats_args.Increment			= _GrowValue;									\
		time_stats_args.CalculateLast		= true;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
																										\
		oc_site.m_Total_##_CounterName	= time_stats_args.Total;					\
		oc_site.m_LM_##_CounterName		= time_stats_args.LM;						\
		oc_site.m_LW_##_CounterName		= time_stats_args.LW;						\
		oc_site.m_LD_##_CounterName		= time_stats_args.LD;						\
		oc_site.m_LH_##_CounterName		= time_stats_args.LH;						\
	}
#define GROW_SITE_COUNTER_WO_SYNC(_GrowValue, _CounterName)							\
	{																									\
		time_stats_args.Increment			= _GrowValue;									\
		time_stats_args.CalculateLast		= false;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
	}
#define UPDATE_SITE_COUNTER_W_LASTSYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 0;												\
		time_stats_args.CalculateLast		= true;											\
		time_stats_args.idCounter			= oc_site.m_##_CounterName;				\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_site.m_##_CounterName	= time_stats_args.idCounter;						\
																										\
		oc_site.m_Total_##_CounterName	= time_stats_args.Total;					\
		oc_site.m_LM_##_CounterName		= time_stats_args.LM;						\
		oc_site.m_LW_##_CounterName		= time_stats_args.LW;						\
		oc_site.m_LD_##_CounterName		= time_stats_args.LD;						\
		oc_site.m_LH_##_CounterName		= time_stats_args.LH;						\
	}
//----------------------------------------------------------------------------[] 
#define INCREMENT_VBN_COUNTER_W_LASTSYNC(_CounterName)								\
	{																									\
		time_stats_args.Increment			= 1;												\
		time_stats_args.CalculateLast		= true;											\
		time_stats_args.idCounter			= oc_vbn.m_##_CounterName;					\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_vbn.m_##_CounterName				= time_stats_args.idCounter;				\
																										\
		oc_vbn.m_Total_##_CounterName		= time_stats_args.Total;					\
		oc_vbn.m_LM_##_CounterName			= time_stats_args.LM;						\
		oc_vbn.m_LW_##_CounterName			= time_stats_args.LW;						\
		oc_vbn.m_LD_##_CounterName			= time_stats_args.LD;						\
		oc_vbn.m_LH_##_CounterName			= time_stats_args.LH;						\
	}
#define UPDATE_VBN_COUNTER_W_LASTSYNC(_CounterName)									\
	{																									\
		time_stats_args.Increment			= 0;												\
		time_stats_args.CalculateLast		= true;											\
		time_stats_args.idCounter			= oc_vbn.m_##_CounterName;					\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));					\
		oc_vbn.m_##_CounterName				= time_stats_args.idCounter;				\
																										\
		oc_vbn.m_Total_##_CounterName		= time_stats_args.Total;					\
		oc_vbn.m_LM_##_CounterName			= time_stats_args.LM;						\
		oc_vbn.m_LW_##_CounterName			= time_stats_args.LW;						\
		oc_vbn.m_LD_##_CounterName			= time_stats_args.LD;						\
		oc_vbn.m_LH_##_CounterName			= time_stats_args.LH;						\
	}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ChangeSuspicious                                                          []                
//                                                                            []

#define CHANGE_SUSPICIOUS																		\
																										\
	time_stats_args.CalculateLast		= true;												\
	time_stats_args.idCounter			= (int)oc_site.m_SuspiciousHits;				\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));						\
	oc_site.m_SuspiciousHits			= time_stats_args.idCounter;					\
																										\
	UPDATE_SUSPICIOUS_HITS(Total);															\
	UPDATE_SUSPICIOUS_HITS(LM);																\
	UPDATE_SUSPICIOUS_HITS(LW);																\
	UPDATE_SUSPICIOUS_HITS(LD);																\
	UPDATE_SUSPICIOUS_HITS(LH);
//----------------------------------------------------------------------------[] 
#define	UPDATE_SUSPICIOUS_HITS(_CounterName)											\
	{	int Sum = time_stats_args.##_CounterName +										\
					(int)oc_site.m_##_CounterName##_Hits;									\
		if (Sum != 0) {																			\
			oc_site.m_##_CounterName##_SuspiciousHits_Prc =								\
				(time_stats_args.##_CounterName * 100) / Sum;							\
		}																								\
		else if (time_stats_args.##_CounterName != 0)									\
		{																								\
			oc_site.m_##_CounterName##_SuspiciousHits_Prc = 100;						\
		}																								\
		else																							\
		{																								\
			oc_site.m_##_CounterName##_SuspiciousHits_Prc = 0;							\
		}																								\
	}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` RECALC_AVE_COUNTER                                                        []                  
//                                                                            []
#define RECALC_AVE_COUNTER(SiteCounter, Numerator, Denominator)					\
	if ((Numerator > 0) && (Denominator > 0))	{											\
		SiteCounter = (Numerator)	/ (Denominator);										\
	}																									\
	else {																							\
		SiteCounter = 0;																			\
	}

//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` UPDATE_SESSION_STUFF                                                      []                    
//                                                                            []

#define UPDATE_SESSION_STUFF																											\
	time_stats_args.Increment			= 0;																							\
	time_stats_args.CalculateLast		= true;																						\
	time_stats_args.idCounter			= oc_site.m_SessionNum;																	\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));																\
	oc_site.m_SessionNum					= time_stats_args.idCounter;															\
	oc_site.m_Total_SessionNum			= time_stats_args.Total;																\
	oc_site.m_LM_SessionNum				= time_stats_args.LM;																	\
	oc_site.m_LW_SessionNum				= time_stats_args.LW;																	\
	oc_site.m_LD_SessionNum				= time_stats_args.LD;																	\
	oc_site.m_LH_SessionNum				= time_stats_args.LH;																	\
																																				\
	time_stats_args.idCounter			= oc_site.m_SessionTime;																\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));																\
	oc_site.m_SessionTime				= time_stats_args.idCounter;															\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveSessionTime, time_stats_args.Total,	oc_site.m_Total_SessionNum);	\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveSessionTime,		time_stats_args.LM,		oc_site.m_LM_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveSessionTime,		time_stats_args.LW,		oc_site.m_LW_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveSessionTime,		time_stats_args.LD,		oc_site.m_LD_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveSessionTime,		time_stats_args.LH,		oc_site.m_LH_SessionNum);		\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveReloadTime,	time_stats_args.Total,	oc_site.m_Total_Hits);			\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveReloadTime,		time_stats_args.LM,		oc_site.m_LM_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveReloadTime,		time_stats_args.LW,		oc_site.m_LW_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveReloadTime,		time_stats_args.LD,		oc_site.m_LD_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveReloadTime,		time_stats_args.LH,		oc_site.m_LH_Hits);				\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveReloadNum,	oc_site.m_Total_Hits,	oc_site.m_Total_SessionNum);	\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveReloadNum,		oc_site.m_LM_Hits,	  	oc_site.m_LM_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveReloadNum,		oc_site.m_LW_Hits,	  	oc_site.m_LW_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveReloadNum,		oc_site.m_LD_Hits,	  	oc_site.m_LD_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveReloadNum,		oc_site.m_LH_Hits,	  	oc_site.m_LH_SessionNum)
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` GROW_SESSION_TIME                                                         []                 
//                                                                            []
#define GROW_SESSION_TIME(_GrowValue)																								\
	time_stats_args.Increment			= _GrowValue;																				\
	time_stats_args.CalculateLast		= true;																						\
	time_stats_args.idCounter			= oc_site.m_SessionTime;																\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));																\
	oc_site.m_SessionTime				= time_stats_args.idCounter;															\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveSessionTime, time_stats_args.Total,	oc_site.m_Total_SessionNum);	\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveSessionTime,		time_stats_args.LM,		oc_site.m_LM_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveSessionTime,		time_stats_args.LW,		oc_site.m_LW_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveSessionTime,		time_stats_args.LD,		oc_site.m_LD_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveSessionTime,		time_stats_args.LH,		oc_site.m_LH_SessionNum);		\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveReloadTime,	time_stats_args.Total,	oc_site.m_Total_Hits);			\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveReloadTime,		time_stats_args.LM,		oc_site.m_LM_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveReloadTime,		time_stats_args.LW,		oc_site.m_LW_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveReloadTime,		time_stats_args.LD,		oc_site.m_LD_Hits);				\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveReloadTime,		time_stats_args.LH,		oc_site.m_LH_Hits);				\
																																				\
	if (localtime_stats_args.timer > 0) {																							\
		localtime_stats_args.Increment			= _GrowValue;																	\
		localtime_stats_args.CalculateLast		= false;																			\
		localtime_stats_args.idCounter			= oc_site.m_SessionTime_Local;											\
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(localtime_stats_args));													\
		oc_site.m_SessionTime_Local				= localtime_stats_args.idCounter;										\
	}

//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` GROW_SESSION_NUM                                                          []                
//                                                                            []
#define GROW_SESSION_NUM(_GrowValue)																								\
	time_stats_args.Increment			= _GrowValue;																				\
	time_stats_args.CalculateLast		= true;																						\
	time_stats_args.idCounter			= oc_site.m_SessionNum;																	\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));																\
	oc_site.m_SessionNum					= time_stats_args.idCounter;															\
																																				\
	oc_site.m_Total_SessionNum			= time_stats_args.Total;																\
	oc_site.m_LM_SessionNum				= time_stats_args.LM;																	\
	oc_site.m_LW_SessionNum				= time_stats_args.LW;																	\
	oc_site.m_LD_SessionNum				= time_stats_args.LD;																	\
	oc_site.m_LH_SessionNum				= time_stats_args.LH;																	\
																																				\
	time_stats_args.Increment			= 0;																							\
	time_stats_args.CalculateLast		= true;																						\
	time_stats_args.idCounter			= oc_site.m_SessionTime;																\
	BX_ASSERT_PASSIVE(BX_TimeStats_Increment(time_stats_args));																\
	oc_site.m_SessionTime				= time_stats_args.idCounter;															\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveSessionTime, time_stats_args.Total,	oc_site.m_Total_SessionNum);	\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveSessionTime,		time_stats_args.LM,		oc_site.m_LM_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveSessionTime,		time_stats_args.LW,		oc_site.m_LW_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveSessionTime,		time_stats_args.LD,		oc_site.m_LD_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveSessionTime,		time_stats_args.LH,		oc_site.m_LH_SessionNum);		\
																																				\
	RECALC_AVE_COUNTER(oc_site.m_Total_AveReloadNum,	oc_site.m_Total_Hits,	oc_site.m_Total_SessionNum);	\
	RECALC_AVE_COUNTER(oc_site.m_LM_AveReloadNum,		oc_site.m_LM_Hits,	  	oc_site.m_LM_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LW_AveReloadNum,		oc_site.m_LW_Hits,	  	oc_site.m_LW_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LD_AveReloadNum,		oc_site.m_LD_Hits,	  	oc_site.m_LD_SessionNum);		\
	RECALC_AVE_COUNTER(oc_site.m_LH_AveReloadNum,		oc_site.m_LH_Hits,	  	oc_site.m_LH_SessionNum)
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` CREATE_SHOW_EVENT                                                         []                 
//                                                                            []
#define CREATE_SHOW_EVENT																		\
/* Создадим новое событие:	*/																	\
	oc_show_event.New();																			\
	oc_show_event.m_SiteID				= arg.SiteID;										\
	oc_show_event.m_ViewerID			= arg.ViewerID;									\
	oc_show_event.m_Time 				= CurrentTime;										\
	oc_show_event.m_ExitCode			= arg.ExitCode
//______________________________________________________________________________
//                                                                            []
//` VALIDATE_URL                                                              []            
//                                                                            []
#define VALIDATE_URL(_url_)		HTTP_URL(_url_).URL(_url_)



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/