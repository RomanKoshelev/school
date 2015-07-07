/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFile.pvt.cpp														[]
[] Date:          4.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с файлами.															[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFile.inc.h"



//______________________________________________________________________________
//                                                                            []
//` Проверка доступа к файлу с указанными атрибутами									[]
//                                                                            []
// !! Результаты этой функции можно кешировать											[]
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_WEBFILE (identifier userID, identifier fileID, const string& Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_INFOOBJECT);

	if (!OC_Exist (OBJ_CLASS_ID_WebFile, fileID))
	{
		SERVER_DEBUG_ERROR_1 ("Указанный информационный объект ID=%d не существует", fileID);
		return ERR_BadID;
	}
	OC_WebFile oc_file (fileID);

// Проходимся по всем разделам объекта и проверяем доступ
	for (int f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		ERR_RESULT res = USER_CHECK_ACCESS_TO_WEBFOLDER (userID, oc_file.m_WebFolderID[f], Attributes);
		if (res!=ERR_OK)
		{
			return res;
		}
	}
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