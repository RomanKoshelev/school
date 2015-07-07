/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_xxx.pvt.cpp															[]
[] Date:          ddd.2000																		[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������� ������ xxx											[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_xxx.inc.h"


//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_XXX_GUID (guid xxxGUID)
{
	DEBUG_STACK_NAME (CHECK_XXX_GUID);

// ������ ������ ������������
	if (!OC_Exist (xxxGUID))
	{
		return false;
	}
	
// �������� �� ����������� ��������� ������
	IF_NOT_CHECK_MOD_BASE (xxxClassName, BaseClassName, xxxGUID)
	{
		return false;
	}

// �������������� ��������
//	...



	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_XXX_ID (identifier xxxID)
{
	DEBUG_STACK_NAME (CHECK_XXX_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_xxx, xxxID))
	{
		return false;
	}
	OC_XXX oc_xxx (xxxID);

	guid gi = oc_xxx.GetObjectGUID ();
	
	return CHECK_XXX_GUID(gi);

	return true;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` �������� ������� � xxx																		[]
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_XXX (identifier loginID, identifier xxxID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_XXX);

	return ERR_OK;
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/