/*___________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'bcc'												[]
[] Copyright (C) 1999-2000 by the author(s) -- see below.                  []
[] All rights reserved.                                                    []
[] ________________________________________________________________________[]
[]																									[]
[] Name:            problem_SingleObject.h											[]
[] Date:            28.06.2000                                             []
[] Author:			  Roman V. Koshelev													[]
[] Description:	  √лобальный объект проекта										[]
[]_________________________________________________________________________[]
*/
#ifndef SINGLE_OBJECT_H
#define SINGLE_OBJECT_H
//______________________________________________________________________________
//                                                                            []
//` ќЅўјя „ј—“№                                                               []           
//                                                                            []
struct	SingleObject;
time_t	GetTZOffset				(void);
#define	theSingleObject		(*pSingleObject)
extern	SingleObject			*pSingleObject;
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[] ќписание главного объекта SingleObject		                                 []
[]                                                                            */
struct SingleObject: public CEventHandler
{
	OC_Registry * m_pOC_Registry;

	SingleObject	();
	~SingleObject	();
	virtual bool OnEvent (const EM_Event& Event);

	bool	Create							(int argc, char *argv[]);
	void	RegisterErrorDescriptions	(void);
	void	OnTimer							(void);
};
//____________________________________________________________________________[]


#define	oc_reg					(*(pSingleObject->m_pOC_Registry))
#define	theSingleObject		(*pSingleObject)
extern	SingleObject			*pSingleObject;



//----------------------------------------------------------------------------[] 
#define MAX_FA_SIZE 1024
typedef void (*fp_MOD_GET_OBJECT_NAME)				(guid& gi, string& sNAME);
typedef void (*fp_MOD_GET_OBJECT_DESCRIPTION)	(guid& gi, string& sNAME);
typedef void (*fp_MOD_CHECK_ACCESS)					(identifier userID, guid& gi, const string& Attributes);
typedef void (*fp_MOD_CHECK_PLACEMENT)				(identifier_arr& feodIDs, guid& gi);

extern	fp_MOD_GET_OBJECT_NAME				MOD_GET_OBJECT_NAME_FUNCTION_ARR				[];
extern	fp_MOD_GET_OBJECT_DESCRIPTION		MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR	[];
extern	fp_MOD_CHECK_ACCESS					MOD_CHECK_ACCESS_FUNCTION_ARR					[];
extern	fp_MOD_CHECK_PLACEMENT				MOD_CHECK_PLACEMENT_FUNCTION_ARR				[];
//----------------------------------------------------------------------------[] 


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/