/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'OBT'                                       []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ArgResCache.h		                                       []
[] Date:            15.11.1999                                                []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Кэширование результатов вычислений функций.               []
[]____________________________________________________________________________[]
*/                                                                         


#ifndef ArgResCache_h
#define ArgResCache_h

//______________________________________________________________________________
//                                                                            []
//` Кеш для результата функции.                                               []                           
//                                                                            []
//----------------------------------------------------------------------------[]
struct CACHE_ITEM
{
	key_arr		m_arg;
	byte_arr		m_result;
	size_t		m_shift;

	//----------------------------------------------------------------------------[] 
	void Init ()
	{
		m_shift	 = 0;
		m_arg.Init ();
	}
	CACHE_ITEM ()
	{
		Init ();
	}
	CACHE_ITEM (const CACHE_ITEM& from)
	{
		CopyFrom (from);
	}

	CACHE_ITEM& operator= (const CACHE_ITEM& from)
	{
		return CopyFrom (from);
	}
	CACHE_ITEM& CopyFrom (const CACHE_ITEM& from)
	{
		m_arg			=  from.m_arg;
		m_result		=	from.m_result;
		m_shift		=	from.m_shift; 
		return *this;
	}
	~CACHE_ITEM ()
	{
	}
	void BeginExtractArgs ()
	{
		m_shift	 = 0;
	}
	//----------------------------------------------------------------------------[] 

// ПОдготовка аргументов
	void operator+= (int							arg)				{m_arg+=arg;}
	void operator+= (byte						arg)				{m_arg+=arg;}
	void operator+= (bool						arg)				{m_arg+=arg;}
	void operator+= (float						arg)				{m_arg+=arg;}
	void operator+= (identifier				arg)				{m_arg+=arg;}
	void operator+= (const string&			arg)				{m_arg+=arg;}
	void operator+= (const char *				arg)				{m_arg+=arg;}
	void operator+= (const int_arr&			arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}
	void operator+= (const byte_arr&			arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}
	void operator+= (const bool_arr&			arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}
	void operator+= (const float_arr&		arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}
	void operator+= (const identifier_arr&	arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}
	void operator+= (const string_arr&		arg)				{m_arg+=(int)arg.GetSize(); for (int i=0; i<arg.GetSize(); i++) m_arg+=arg[i];}


// Запоминание результатов вычисления
	void operator<< (int				res)		{for (int i=0; i<sizeof (res); i++)	m_result += ((byte*)(&res))[i];}
	void operator<< (byte			res)		{for (int i=0; i<sizeof (res); i++)	m_result += ((byte*)(&res))[i];}
	void operator<< (bool			res)		{for (int i=0; i<sizeof (res); i++)	m_result += ((byte*)(&res))[i];}
	void operator<< (float			res)		{for (int i=0; i<sizeof (res); i++)	m_result += ((byte*)(&res))[i];}
	void operator<< (identifier	res)		{for (int i=0; i<sizeof (res); i++)	m_result += ((byte*)(&res))[i];}
	void operator<< (const char * res)
	{
		int nSize = strlen (res)+1;
		(*this) << nSize;
		for (int i=0; i<nSize; i++)
		{
			m_result += res[i];
		}
	}
	void operator<< (const string&				res)				{(*this)<<     res.c_str();}
	void operator<< (const int_arr&				res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}
	void operator<< (const byte_arr&				res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}
	void operator<< (const bool_arr&				res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}
	void operator<< (const float_arr&			res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}
	void operator<< (const identifier_arr&		res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}
	void operator<< (const string_arr&			res)				{(*this)<<(int)res.GetSize(); for (int i=0; i<res.GetSize(); i++) (*this)<<res[i];}


// Вдача результатов вычисления
	void operator>> (int&					res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}
	void operator>> (byte&					res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}
	void operator>> (char&					res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}
	void operator>> (bool&					res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}
	void operator>> (float&					res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}
	void operator>> (identifier&			res)				{for (int i=0; i<sizeof (res); i++)	((byte*)(&res))[i] = m_result[m_shift++];}

	void operator>> (string&				res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (int_arr&				res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (byte_arr&				res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (bool_arr&				res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (float_arr&			res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (identifier_arr&		res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
	void operator>> (string_arr&			res)				{int nSize;	(*this)>>nSize; res.Alloc (nSize);	for (int i=0; i<nSize; i++) (*this)>>res[i];}
};
//----------------------------------------------------------------------------[] 



typedef IT_AVTree <CACHE_ITEM, key_arr, key_arr CACHE_ITEM::*>  IT_AVTree_ARG_RES_CACHE;
int CompareFunction_ARG_KEY (key_arr& a, key_arr& b);

//----------------------------------------------------------------------------[]
#define CHECK_MAX_CACHED_ITEMS(MAX_CACHED_ITEMS)										\
	if (localArgResCache.Count()>=(MAX_CACHED_ITEMS))									\
	{																									\
		localArgResCache.RemoveAll();															\
	}
//----------------------------------------------------------------------------[] 

#define USE_CACHE																			static IT_AVTree_ARG_RES_CACHE localArgResCache (&CACHE_ITEM::m_arg, CompareFunction_ARG_KEY); CACHE_ITEM _ci; void *_ptr=NULL; CACHE_ITEM *_pci=NULL;

#define IFCACHEDRETURN_BEG																_ptr=localArgResCache.Find(_ci.m_arg);	if(_ptr!=NULL){_pci=localArgResCache.ItemPointer(_ptr);_pci->BeginExtractArgs();
#define IFCACHEDRETURN_END_VOID														return;}
#define IFCACHEDRETURN_END(retval)													return retval;}
																								
#define IF_CACHED_RETURN(rv)															{IFCACHEDRETURN_BEG	goto MARK_1;	MARK_2:;	IFCACHEDRETURN_END(rv)}
#define IF_CACHED_RETURN_VOID															{IFCACHEDRETURN_BEG	goto MARK_1;	MARK_2:;	IFCACHEDRETURN_END_VOID}
																						
#define GOTO_IZVRAT_1(r1														)		goto MARK_3; MARK_1:;		(*_pci)>>(r1);																																				goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_2(r1,r2													)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2);																															goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_3(r1,r2,r3												)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3);																										goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_4(r1,r2,r3,r4											)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3); (*_pci)>>(r4);																					goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_5(r1,r2,r3,r4,r5										)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3); (*_pci)>>(r4); (*_pci)>>(r5);																goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_6(r1,r2,r3,r4,r5,r6									)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3); (*_pci)>>(r4); (*_pci)>>(r5); (*_pci)>>(r6);											goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_7(r1,r2,r3,r4,r5,r6,r7								)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3); (*_pci)>>(r4); (*_pci)>>(r5); (*_pci)>>(r6); (*_pci)>>(r7);						goto MARK_2; MARK_3:;
#define GOTO_IZVRAT_8(r1,r2,r3,r4,r5,r6,r7,r8							)		goto MARK_3; MARK_1:;		(*_pci)>>(r1); (*_pci)>>(r2); (*_pci)>>(r3); (*_pci)>>(r4); (*_pci)>>(r5); (*_pci)>>(r6); (*_pci)>>(r7); (*_pci)>>(r8);	goto MARK_2; MARK_3:;
																						
#define CACHE_STORE_RESULT_1(r1												)		}{_ci<<(r1);																										GOTO_IZVRAT_1 (r1								)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_2(r1,r2											)		}{_ci<<(r1); _ci<<(r2);																							GOTO_IZVRAT_2 (r1,r2							)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_3(r1,r2,r3										)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3);																			GOTO_IZVRAT_3 (r1,r2,r3						)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_4(r1,r2,r3,r4									)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3); _ci<<(r4);															GOTO_IZVRAT_4 (r1,r2,r3,r4					)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_5(r1,r2,r3,r4,r5								)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3); _ci<<(r4); _ci<<(r5);												GOTO_IZVRAT_5 (r1,r2,r3,r4,r5				)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_6(r1,r2,r3,r4,r5,r6							)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3); _ci<<(r4); _ci<<(r5); _ci<<(r6);								GOTO_IZVRAT_6 (r1,r2,r3,r4,r5,r6			)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_7(r1,r2,r3,r4,r5,r6,r7						)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3); _ci<<(r4); _ci<<(r5); _ci<<(r6); _ci<<(r7);				GOTO_IZVRAT_7 (r1,r2,r3,r4,r5,r6,r7		)	localArgResCache.Insert (_ci);	}
#define CACHE_STORE_RESULT_8(r1,r2,r3,r4,r5,r6,r7,r8					)		}{_ci<<(r1); _ci<<(r2); _ci<<(r3); _ci<<(r4); _ci<<(r5); _ci<<(r6); _ci<<(r7); _ci<<(r8);	GOTO_IZVRAT_8 (r1,r2,r3,r4,r5,r6,r7,r8	)	localArgResCache.Insert (_ci);	}
																						
#define CACHE_ARGS_1(a1															)		{_ci+=(a1);																								}
#define CACHE_ARGS_2(a1,a2														)		{_ci+=(a1);_ci+=(a2);																				}
#define CACHE_ARGS_3(a1,a2,a3													)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);																	}
#define CACHE_ARGS_4(a1,a2,a3,a4												)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);_ci+=(a4);														}
#define CACHE_ARGS_5(a1,a2,a3,a4,a5											)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);_ci+=(a4);_ci+=(a5);										}
#define CACHE_ARGS_6(a1,a2,a3,a4,a5,a6										)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);_ci+=(a4);_ci+=(a5);_ci+=(a6);							}
#define CACHE_ARGS_7(a1,a2,a3,a4,a5,a6,a7									)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);_ci+=(a4);_ci+=(a5);_ci+=(a6);_ci+=(a7);				}
#define CACHE_ARGS_8(a1,a2,a3,a4,a5,a6,a7,a8								)		{_ci+=(a1);_ci+=(a2);_ci+=(a3);_ci+=(a4);_ci+=(a5);_ci+=(a6);_ci+=(a7);_ci+=(a8);}
																				
#define IF_CACHED_ARGS_1_RETURN_VOID(CS, a1								)		USE_CACHE;	CACHE_ARGS_1(a1								);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_2_RETURN_VOID(CS, a1,a2							)		USE_CACHE;	CACHE_ARGS_2(a1,a2							);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_3_RETURN_VOID(CS, a1,a2,a3						)		USE_CACHE;	CACHE_ARGS_3(a1,a2,a3						);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_4_RETURN_VOID(CS, a1,a2,a3,a4					)		USE_CACHE;	CACHE_ARGS_4(a1,a2,a3,a4					);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_5_RETURN_VOID(CS, a1,a2,a3,a4,a5				)		USE_CACHE;	CACHE_ARGS_5(a1,a2,a3,a4,a5				);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_6_RETURN_VOID(CS, a1,a2,a3,a4,a5,a6			)		USE_CACHE;	CACHE_ARGS_6(a1,a2,a3,a4,a5,a6			);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_7_RETURN_VOID(CS, a1,a2,a3,a4,a5,a6,a7		)		USE_CACHE;	CACHE_ARGS_7(a1,a2,a3,a4,a5,a6,a7		);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_8_RETURN_VOID(CS, a1,a2,a3,a4,a5,a6,a7,a8	)		USE_CACHE;	CACHE_ARGS_8(a1,a2,a3,a4,a5,a6,a7,a8	);		IF_CACHED_RETURN_VOID;	CHECK_MAX_CACHED_ITEMS (CS);{
																																										
#define IF_CACHED_ARGS_1_RETURN(CS, a1									,rv)		USE_CACHE;	CACHE_ARGS_1(a1								);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_2_RETURN(CS, a1,a2								,rv)		USE_CACHE;	CACHE_ARGS_2(a1,a2							);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_3_RETURN(CS, a1,a2,a3							,rv)		USE_CACHE;	CACHE_ARGS_3(a1,a2,a3						);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_4_RETURN(CS, a1,a2,a3,a4						,rv)		USE_CACHE;	CACHE_ARGS_4(a1,a2,a3,a4					);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_5_RETURN(CS, a1,a2,a3,a4,a5					,rv)		USE_CACHE;	CACHE_ARGS_5(a1,a2,a3,a4,a5				);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_6_RETURN(CS, a1,a2,a3,a4,a5,a6				,rv)		USE_CACHE;	CACHE_ARGS_6(a1,a2,a3,a4,a5,a6			);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_7_RETURN(CS, a1,a2,a3,a4,a5,a6,a7			,rv)		USE_CACHE;	CACHE_ARGS_7(a1,a2,a3,a4,a5,a6,a7		);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{
#define IF_CACHED_ARGS_8_RETURN(CS, a1,a2,a3,a4,a5,a6,a7,a8		,rv)		USE_CACHE;	CACHE_ARGS_8(a1,a2,a3,a4,a5,a6,a7,a8	);		IF_CACHED_RETURN	(rv);	CHECK_MAX_CACHED_ITEMS (CS);{

inline int CompareFunction_ARG_KEY (key_arr& a, key_arr& b)
{
	return a.Compare(b);
}

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
