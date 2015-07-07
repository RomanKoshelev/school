/*
____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'BX'													[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  BX_SingleObject.h													[]
[] Date: 			  26.07.99																[]
[] Author:			  Alex Vershinin, Roman V. Koshelev								[]
[] Description:	  Глобальный объект баннерной системы							[]
[] Last Modified:																				[]
[]_________________________________________________________________________[]
*/
#ifndef BX_SINGLE_OBJECT_H
#define BX_SINGLE_OBJECT_H


//----------------------------------------------------------------------------[]
typedef  CSmartField<OD_Site, int>  SiteCounter;
typedef  SiteCounter OC_Site::*     pSiteCounter;
//----------------------------------------------------------------------------[]

struct BX_SingleObject_Cache;
/*______________________________________________________________________________
[]                                                                            []
[]` BX_SingleObject                                                           []               
[]                                                                            */
struct BX_SingleObject: public CEventHandler
{
	OC_Registry					*m_pOC_Registry;

	BX_SingleObject_Cache*	m_pCACHE;
	
	BX_SingleObject	();
	~BX_SingleObject	();
	virtual bool OnEvent (const EM_Event& Event);

// Список названий всех рейтингуемых индексов у сайта.
	string_arr				AllSiteIndexNames;	
// Список идентификаторов всех рейтингуемых индексов у сайта.
	identifier_arr			AllSiteIndexIDs;		
// Список указателей на счетчики, соответствующих рейтингуемым индексам у сайта.
	CPtr<pSiteCounter>	AllSiteIndexFields;	

	int CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate;

	void Create							(void);
	void RegisterErrorDescriptions(void);
	void OnTimer						(time_t);
	void CreateEnumObjects			(void);
	void GetSiteIndexInfo			(void);
};

//----------------------------------------------------------------------------[]
time_t GetTZOffset (void);
//----------------------------------------------------------------------------[] 

#define	oc_reg						(*(pBX_SingleObject->m_pOC_Registry))
#define	theBX_SingleObject		(*pBX_SingleObject)
extern	BX_SingleObject			*pBX_SingleObject;
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` PROBLEM_FORME                                                             []
[]                                                                            */
#ifdef	PROBLEM_FORME


//----------------------------------------------------------------------------[] 
#define	CREATE_PREDEFINED_OBJECTS															\
	GetAdminPassword(vbn_arg.AdminPassword);												\
																										\
	vbn_arg.objID					= NA;															\
	vbn_arg.Name					= "Баннерная сеть общего пользования";				\
	vbn_arg.Password				= "vbn";														\
	vbn_arg.Description			= "Пост-модерируемая сеть с неограниченным доступом.";\
	vbn_arg.IsModerated			= false;														\
	vbn_arg.DefaultLanguage		= oc_reg.m_Language[0];									\
	vbn_arg.DefaultTZOffset		= SERVER_TIME_ZONE_OFFSET;								\
	vbn_arg.ConceptMask			= concept_args.objIDs;									\
	SERVER_DEBUG_ASSERT(BX_VBN_New(vbn_arg) == BX_OK,									\
		"CreateEnumObjects(): Error in BX_VBN_New (VBN 1).");							\
																										\
/* User1 */																							\
																										\
	user_arg.Login					= "user1";													\
	user_arg.Password				= "user";													\
	user_arg.PasswordConfirm	= "user";													\
	user_arg.FullName				= "";															\
	user_arg.Email					= "";															\
	user_arg.VBN					= vbn_arg.objID;											\
	SERVER_DEBUG_ASSERT(BX_User_New(user_arg) == BX_OK,								\
		"CreateEnumObjects(): Error in BX_User_New (User 1).");						\
	BX_ASSERT(BX_User_GetData(user_arg));													\
																										\
	user_arg.Phone					= "None.";													\
	user_arg.Fax					= "None.";													\
	user_arg.URL					= "http://tsmc.int.bibirevo.net/BX/";				\
	user_arg.Comment				= "А комментировать тут особенно и нечего...";	\
	user_arg.TZOffset				= SERVER_TIME_ZONE_OFFSET;								\
	SERVER_DEBUG_ASSERT(BX_User_PutData(user_arg) == BX_OK,							\
		"CreateEnumObjects(): Error in BX_User_PutData (User 1).");					\
																										\
	user_arg.Password				= "vbn";														\
	SERVER_DEBUG_ASSERT(BX_User_RegisterAsSystem(user_arg) == BX_OK,				\
		"CreateEnumObjects(): Error in BX_User_RegisterAsSystem (User 1).");		\
																										\
/* Site 1-1 */																						\
	site_arg.Profile				= NA;															\
	site_arg.objID					= NA;															\
	site_arg.OwnerID				= user_arg.objID;											\
	site_arg.objPassword			= "user";													\
	site_arg.URL					= "http://tsmc.int.bibirevo.net/BX/counter_test.html";\
	site_arg.MirrorInclude.Add("http://tsmc.int.bibirevo.net/BX/counter_test_1.html");\
	site_arg.MirrorInclude.Add("http://tsmc/BX/counter_test.html");				\
	site_arg.MirrorInclude.Add("http://tsmc/BX/counter_test_1.html");				\
	BX_ASSERT(BX_Site_New(site_arg));														\
	BX_ASSERT(BX_Site_GetData(site_arg));													\
	site_arg.Name					= "VBN#1, user1-site1 - Counter Test Site";		\
	BX_ASSERT(BX_Site_PutData(site_arg));													\
																										\
/*- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 							\
 User 1-2 */																						\
 																										\
																										\
	user_arg.Login					= "user2";													\
	user_arg.Password				= "user";													\
	user_arg.PasswordConfirm	= "user";													\
	user_arg.FullName				= "";															\
	user_arg.Email					= "";															\
	user_arg.VBN					= vbn_arg.objID;											\
	SERVER_DEBUG_ASSERT(BX_User_New(user_arg) == BX_OK,								\
		"CreateEnumObjects(): Error in BX_User_New (User 1).");						\
																										\
	user_arg.Password				= "user";													\
	user_arg.FullName				= "Alex Vershinin";										\
	user_arg.Email					= "av@bibirevo.net";										\
	user_arg.Phone					= "None.";													\
	user_arg.Fax					= "None.";													\
	user_arg.URL					= "http://bsd.int.bibirevo.net/~av/";				\
	user_arg.Comment				= "No comments...";										\
	user_arg.TZOffset				= SERVER_TIME_ZONE_OFFSET;								\
	SERVER_DEBUG_ASSERT(BX_User_PutData(user_arg) == BX_OK,							\
		"CreateEnumObjects(): Error in BX_User_PutData (User 1).");					\
/*----------------------------------------------------------------------------[] \
 Site av-1*/																						\
	site_arg.Profile				= NA;															\
	site_arg.objID					= NA;															\
	site_arg.OwnerID				= user_arg.objID;											\
	site_arg.objPassword			= "user";													\
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/index.html";	\
	BX_ASSERT(BX_Site_New(site_arg));														\
	BX_ASSERT(BX_Site_GetData(site_arg));													\
	site_arg.Name					= "AV's Developer Home";								\
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/index.html");			\
	site_arg.MirrorInclude.Add("http://bsd/~av/index.html");							\
	BX_ASSERT(BX_Site_PutData(site_arg));													\
/* Site av-2*/																						\
	site_arg.Profile				= NA;															\
	site_arg.objID					= NA;															\
	site_arg.OwnerID				= user_arg.objID;											\
	site_arg.objPassword			= "user";													\
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/gdb_toc.html";\
	BX_ASSERT(BX_Site_New(site_arg));														 \
	BX_ASSERT(BX_Site_GetData(site_arg));													 \
	site_arg.Name					= "Debugging with GDB";									 \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/gdb_toc.html");			 \
	BX_ASSERT(BX_Site_PutData(site_arg));													 \
/*----------------------------------------------------------------------------[]\
 Site av-3*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/gcc4ms.html";  \
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "GCC For Microsoft [Environments] FAQ";			  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/gcc4ms.html");			  \
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-4*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/make_toc.html";\
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "GNU Make";												  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/make_toc.html");		  \
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-5*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/libg_toc.html";\
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "User's Guide to the GNU C++ Library";			  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/libg_toc.html");		  \
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-6*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/chap03.html";  \
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "Hacking Exposed: Network Security Secrets and Solutions";\
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/chap03.html");			  \
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-7*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/The Programmer's Stone.html";\
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "The Programmers' Stone";							  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/The Programmer's Stone.html");\
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-8*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/Unix security.html";\
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "Unix security";										  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/Unix security.html");	  \
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[]\
 Site av-9*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/~av/ElectronicMasturbationFAQ.html";\
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "Electronic Masturbation (FAQ)";					  \
	site_arg.MirrorInclude.Add("http://192.168.61.20/~av/ElectronicMasturbationFAQ.html");\
	BX_ASSERT(BX_Site_PutData(site_arg));													  \
/*----------------------------------------------------------------------------[] */\
																										  \
/* VBN 2*/																							  \
	vbn_arg.objID = NA;																			  \
	vbn_arg.Name					= "Elite Banner Network";								  \
	vbn_arg.Password				= "vbn";														  \
	vbn_arg.Description			= "Elite moderated VBN for English-speaking folks.";\
	vbn_arg.IsModerated			= true;														  \
	vbn_arg.DefaultLanguage		= oc_reg.m_Language[0];									  \
	vbn_arg.DefaultTZOffset		= SERVER_TIME_ZONE_OFFSET;								  \
	vbn_arg.ConceptMask			= concept_args.objIDs;									  \
	SERVER_DEBUG_ASSERT(BX_VBN_New(vbn_arg) == BX_OK,									  \
		"CreateEnumObjects(): Error in BX_VBN_New (VBN 2).");							  \
																										  \
/* User 2-1*/																						  \
																										  \
	user_arg.objID					= NA;															  \
	user_arg.Login					= "user1";													  \
	user_arg.Password				= "user";													  \
	user_arg.PasswordConfirm	= "user";													  \
	user_arg.FullName				= "";															  \
	user_arg.Email					= "";															  \
	user_arg.VBN					= vbn_arg.objID;											  \
	SERVER_DEBUG_ASSERT(BX_User_New(user_arg) == BX_OK,								  \
		"CreateEnumObjects(): Error in BX_User_New (User 2).");						  \
																										  \
	user_arg.Password				= "user";													  \
	user_arg.FullName				= "Test";													  \
	user_arg.Email					= "tsmc@bibirevo.net";									  \
	user_arg.Phone					= "None.";													  \
	user_arg.Fax					= "None.";													  \
	user_arg.URL					= "http://tsmc.int.bibirevo.net";					  \
	user_arg.Comment				= "No comments...";										  \
	user_arg.TZOffset				= SERVER_TIME_ZONE_OFFSET;								  \
	SERVER_DEBUG_ASSERT(BX_User_PutData(user_arg) == BX_OK,							  \
		"CreateEnumObjects(): Error in BX_User_PutData.");								  \
																										  \
	user_arg.Password				= "vbn";														  \
	SERVER_DEBUG_ASSERT(BX_User_RegisterAsSystem(user_arg) == BX_OK,				  \
		"CreateEnumObjects(): Error in BX_User_RegisterAsSystem(User 2).");		  \
																										  \
/* Site 2-1*/																						  \
	site_arg.Profile				= NA;															  \
	site_arg.objID					= NA;															  \
	site_arg.OwnerID				= user_arg.objID;											  \
	site_arg.objPassword			= "user";													  \
	site_arg.URL					= "http://bsd.int.bibirevo.net/index.html";		  \
	BX_ASSERT(BX_Site_New(site_arg));														  \
	BX_ASSERT(BX_Site_GetData(site_arg));													  \
	site_arg.Name					= "VBN #2: !!! This is a test site w/o counter."; \
	BX_ASSERT(BX_Site_PutData(site_arg))


#endif
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` DB                                                                        []  
[]                                                                            */
#ifdef PROBLEM_DB

//----------------------------------------------------------------------------[]
#define	CREATE_PREDEFINED_OBJECTS															\
	GetAdminPassword(vbn_arg.AdminPassword);												\
																										\
	vbn_arg.objID					= NA;															\
	vbn_arg.Name					= "Баннерная сеть общего пользования";				\
	vbn_arg.Password				= "vbn";														\
	vbn_arg.Description			= "Пост-модерируемая сеть с неограниченным доступом.";\
	vbn_arg.IsModerated			= false;														\
	vbn_arg.DefaultLanguage		= oc_reg.m_Language[0];									\
	vbn_arg.DefaultTZOffset		= SERVER_TIME_ZONE_OFFSET;								\
	vbn_arg.ConceptMask			= concept_args.objIDs;									\
	SERVER_DEBUG_ASSERT(BX_VBN_New(vbn_arg) == BX_OK,									\
		"CreateEnumObjects(): Error in BX_VBN_New (VBN 1).");							\
																										\
/* User pooh*/																						\
																										\
	user_arg.Login					= "pooh";													\
	user_arg.Password				= "pooh44";													\
	user_arg.PasswordConfirm	= "pooh44";													\
	user_arg.FullName				= "Роман В. Кошелев";									\
	user_arg.Email					= "pooh@roman.msk.ru";									\
	user_arg.VBN					= vbn_arg.objID;											\
	SERVER_DEBUG_ASSERT(BX_User_New(user_arg) == BX_OK,								\
		"CreateEnumObjects(): Error in BX_User_New (pooh).");							\
	BX_ASSERT(BX_User_GetData(user_arg));													\
																										\
	user_arg.Phone					= "901-23-53";												\
	user_arg.URL					= "http://www.8008.com/roman";						\
	user_arg.Comment				= "Ну это типа тестовый логин такой";				\
	user_arg.TZOffset				= SERVER_TIME_ZONE_OFFSET;								\
	SERVER_DEBUG_ASSERT(BX_User_PutData(user_arg) == BX_OK,							\
		"CreateEnumObjects(): Error in BX_User_PutData (pooh).");					\
																										\
/* Site PoohChat*/																				\
	site_arg.Profile				= NA;															\
	site_arg.objID					= NA;															\
	site_arg.OwnerID				= user_arg.objID;											\
	site_arg.objPassword			= "pooh44";													\
	site_arg.Name					= "Пуховый полуЧат";										\
	site_arg.URL					= "http://www.kiev.com/pooh";							\
	BX_ASSERT(BX_Site_New(site_arg));														\
	BX_ASSERT(BX_Site_GetData(site_arg));													\
	site_arg.Description			= "Место встречи умных и не очень.";				\
	site_arg.MirrorInclude.Add("http://206.79.235.219/pooh");						\
	BX_ASSERT(BX_Site_PutData(site_arg))
//____________________________________________________________________________[]

#endif

/*______________________________________________________________________________
[]                                                                            []
[]` PROBLEM_TEST                                                              []
[]                                                                            */
#ifdef PROBLEM_TEST
#define	CREATE_PREDEFINED_OBJECTS
#endif
//____________________________________________________________________________[]






#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/