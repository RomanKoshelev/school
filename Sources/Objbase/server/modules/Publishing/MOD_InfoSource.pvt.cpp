/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoSource.h															[]
[] Date:          21.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с объектами класса InfoSource								[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoSource.inc.h"



//______________________________________________________________________________
//                                                                            []
//` Получить имя и адрес источника                                            []                              
//                                                                            []
bool GetInfoSourceNameURL (identifier srcID, string& Name, string& URL)
{
	if (OC_Exist (OBJ_CLASS_ID_InfoSource, srcID))
	{
		OC_InfoSource oc_src	(srcID);
		Name	= oc_src.m_Name;
		URL	= oc_src.m_URL	;
		return true;
	}
	Name	= "{{ERROR}}";
	URL	= "http://developer.error.err";
	return false;
}
//____________________________________________________________________________[]















/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Инициализация системы разграничения прав                                  []                                        
[]                                                                            []
[]____________________________________________________________________________[]
*/
bool InitializeInfoSources (const char * sRootPassword, INFOSOURCE_INI* src_ini_arr, int src_ini_num)
{
	DEBUG_STACK_NAME (InitializeInfoSources);

	for (int i=0; i<src_ini_num; i++)
	{
		MOD_InfoSource_Args arg;
		arg.Login				= "root";
		arg.Password			= sRootPassword;
		arg.Name					= src_ini_arr[i].Name;
		arg.Description		= src_ini_arr[i].Description;
		arg.URL					= src_ini_arr[i].URL;
		arg.RefreshType		= src_ini_arr[i].RefreshType;
		arg.divIDs			  += GetInfoDivIDByType (src_ini_arr[i].DivName);

		MOD_InfoSource_New (arg);

		if (arg.objID==NA || arg.ExitCode!=ERR_OK)
		{
			SERVER_DEBUG_ERROR_2 ("Не удолось создать источник информации %s. %s", arg.Name.c_str(), arg.ExitCodeComment.c_str());
			return false;
		}
	}
	return true;
}
//----------------------------------------------------------------------------[] 







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/