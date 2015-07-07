/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.h														[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Полнотекстовая индексация и поиск с учётом морфологии			[]
[]						Описания используемых в модуле объектов.							[]
[]____________________________________________________________________________[]
*/
#ifndef MOD_FullTextIndex_h
#define MOD_FullTextIndex_h


#define MAX_SEARCH_ENUMERATE_NUM				10000
#define MAX_SEARCH_RESULT_ENUMERATE_NUM	  100

//______________________________________________________________________________
//                                                                            []
//` Аргументы для манипулирования объектами класса xxx								[]
//                                                                            []
struct MOD_FullTextIndex_Args
{ 
	MOD_FullTextIndex_Args()
	{
		objFirstNo				=	0;
		objLastNo				=	INT_MAX;
		Time0						=	0;
		Time1						=	0;
		TotalStoredNum			=	0;
		bNeedDescription		=	false;
		Time						=	0;
		ExitCode					=	-1;
		MaxNumInQuery			=  MAX_SEARCH_RESULT_ENUMERATE_NUM;
		nLookAhead				=	0;
	}


	string			Login;
	string			Password;

	guid				objGUID;
	string			StrName;
	string			StrDescription;
	string			StrText;
	string			StrAdditional;

	bool				bNeedDescription;

	string			Name;
	time_t			Time;

	time_t			Time0;
	time_t			Time1;

	identifier_arr	feodIDs;

	string			Request;
	string			RequestLemma;
	guid_arr			objGUIDs;
	
	string_arr		objClasses;
	identifier_arr	objIDs;
	string_arr		objNames;
	string_arr		objDescriptions;
	int_arr			objTimes;
	int_arr			objWeights;
	string_arr		objPlacements;
	int				nLookAhead;

	int				objFirstNo;
	int				objLastNo;
	int				TotalStoredNum;
	int				MaxNumInQuery;

	int				ExitCode;
	string			ExitCodeComment;
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции                                                      []                    
//                                                                            []
ERR_RESULT		MOD_FullTextIndex_Find		(MOD_FullTextIndex_Args& arg);
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Нормальная форма слова                                                    []                      
//____________________________________________________________________________[]
struct CLemma
{
	identifier	ID;
	string		Word;
	string		Attr;
	float			Weight;
	int			Num;
	bool			IsDigit;
	bool			IsHyp;
	string		WordInv;
	CLemma ()
	{
		Weight	= 0.0; 
		Num		= 1; 
		IsDigit	= false; 
		ID			= NA;
		IsHyp		= true;
	};
	DECLARE_COPY_CONSTRUCTORS_BEGIN(CLemma)
		CC_COPY (ID			)
		CC_COPY (Word		)
		CC_COPY (Attr		)
		CC_COPY (Weight	)
		CC_COPY (Num		)
		CC_COPY (IsDigit	)
		CC_COPY (WordInv	)
		CC_COPY (IsHyp		)		
	DECLARE_COPY_CONSTRUCTORS_END

	bool operator==(const CLemma& to) const {return Word==to.Word && ID==to.ID;}
	bool operator< (const CLemma& to) const {(void)to; return false;}
	bool operator<=(const CLemma& to) const {(void)to; return false;}
};
typedef CPtr<CLemma> lemma_arr;
//______________________________________________________________________________
//                                                                            []
//` Слово в тексте																				[]
//____________________________________________________________________________[]
struct CLemmaInText
{
	string	Word;
	CLemma	Lemma;
	int_arr	Position;
	CLemmaInText (){};
	DECLARE_COPY_CONSTRUCTORS_BEGIN(CLemmaInText)
		CC_COPY (Word		)
		CC_COPY (Lemma		)
		CC_COPY (Position	)
	DECLARE_COPY_CONSTRUCTORS_END

	bool operator==(const CLemmaInText& to) const {return Word==to.Word;}
	bool operator< (const CLemmaInText& to) const {return Word< to.Word;}
	bool operator> (const CLemmaInText& to) const {return Word> to.Word;}
	bool operator<=(const CLemmaInText& to) const {return Word<=to.Word;}			
	bool operator>=(const CLemmaInText& to) const {return Word>=to.Word;}			
	bool operator!=(const CLemmaInText& to) const {return Word!=to.Word;}			
};
//______________________________________________________________________________
//                                                                            []
//` Результат поиска																				[]
//____________________________________________________________________________[]
struct CSearchResult
{
	lemma_arr	m_LemmaArr;
	guid_arr		m_ObjectGUIDs;
	string		m_IniQuery;
};
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Макросы индексирования                                                    []                      
//                                                                            []
#define FULL_INDEX_BEGIN(oc)																	\
	string FTI_Name				= oc.m_Name;												\
	string FTI_Description		= oc.m_Description;										\
	string FTI_Text				= oc.m_Text;												\
	string FTI_Additional		= oc.m_Additional;
//----------------------------------------------------------------------------[] 
#define FULL_INDEX_END(oc)																		\
{ 																										\
	if (FTI_Name			!= oc.m_Name			|| 										\
		 FTI_Description	!= oc.m_Description	||											\
		 FTI_Text			!= oc.m_Text			||											\
		 FTI_Additional	!= oc.m_Additional	)											\
	{																									\
	/* Удаление из индекса */																	\
		{																								\
			MOD_FullTextIndex_Args arg;														\
			arg.objGUID				= oc.GetObjectGUID ();									\
			arg.objIDs				= oc.m_SearchItemID;										\
			MOD_FullTextIndex_Del(arg);														\
		}																								\
	/* Добавление в индекс	*/																	\
		{																								\
			MOD_FullTextIndex_Args arg;														\
			arg.objGUID				= oc.GetObjectGUID ();									\
			arg.StrName				= oc.m_Name;												\
			arg.StrDescription	= oc.m_Description;										\
			arg.StrText				= oc.m_Text;												\
			arg.StrAdditional		= oc.m_Additional;										\
			arg.Time					= time(0);												   \
			MOD_FullTextIndex_Add (arg);														\
			oc.m_SearchItemID		= arg.objIDs;												\
		}																								\
	}																									\
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Интерфейсные функции																		[]
//____________________________________________________________________________[]
ERR_RESULT MOD_FullTextIndex_Add			(MOD_FullTextIndex_Args& arg);
ERR_RESULT MOD_FullTextIndex_Del			(MOD_FullTextIndex_Args& arg);
ERR_RESULT MOD_FullTextIndex_Enumerate	(MOD_FullTextIndex_Args& arg);
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции                                                   []                       
//____________________________________________________________________________[]
const char *	GetInverseWord				(const char * sWord, int nWord);
bool				IsDelimiter					(char C);
bool				GetNormalWord				(const char * sWord, lemma_arr&arrLemma,	 bool bAddToDict);
void				GetNormalWordArr			(const char * sText, lemma_arr& ArrResult, bool bAddToDict, bool bUsageAsterisk=false);
void				CreateFullTextIndex		(const char * sText, const guid& gi, identifier_arr& SearchItemID, time_t cur_time=0);
bool				InitializeSearchSystem	(const char * Lang, bool bFromDatFile);
void				RemoveFromFullTextIndex	(const guid& gi, const identifier_arr& arrLemma);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/