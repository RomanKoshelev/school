/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFolder.h															[]
[] Date:          31.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � web-��������� ������������									[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFolder.inc.h"


//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_WEBFOLDER_GUID (guid folderGUID)
{
	DEBUG_STACK_NAME (CHECK_WEBFOLDER_GUID);

// ������ ������ ������������
	if (!OC_Exist (folderGUID))
	{
		return false;
	}
	OC_WebFolder oc_folder;
	oc_folder.Open (folderGUID);
	
// �������� �� ����������� ��������� ������
	IF_NOT_CHECK_MOD_BASE (WebFolder, Concept, folderGUID)
	{
		return false;
	}
	identifier feodID = guid(oc_folder.m_MOD_Base_GUID).id;

// ���� ������ �������� ����������
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR ("������������ ������� ������");
		return false;
	}

// ����� ������ �������� ������ ����� {Concept.Feod.Files}
	identifier_arr folderFeods = OC_Concept (GetFeodIDByType ("Concept.Feod.Files")).m_Descendant;
	folderFeods.Insert (0, GetFeodIDByType ("Concept.Feod.Files"));
	if (folderFeods.Find (feodID)==-1)
	{
		SERVER_DEBUG_ERROR_2 ("����� %s [%d] ������ �������� ������ ����� {Concept.Feod.Files}", string(OC_Concept (feodID).m_Name).c_str(), folderGUID.id);
		return false;
	}

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �� ����������																		[]
//                                                                            []
bool CHECK_WEBFOLDER_ID (identifier folderID)
{
	DEBUG_STACK_NAME (CHECK_WEBFOLDER_ID);

// ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFolder, folderID))
	{
		return false;
	}
	OC_WebFolder oc_folder (folderID);

	guid gi = oc_folder.GetObjectGUID ();
	
	return CHECK_WEBFOLDER_GUID(gi);

	return true;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ����� �� �����																	[]
//  ���� �� ����������, �������� �����													[]
//                                                                            []
identifier GetWebFolderIDByFeodID (identifier feodID)
{
	DEBUG_STACK_NAME (GetWebFolderIDByFeodID);

	GET_MOD_EXTENSION (Concept, feodID, WebFolder, folder);
//	return folderID;

	if (folderID!=NA && CHECK_WEBFOLDER_ID(folderID))
	{
		return folderID;
	}
	return NA;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` �������� ���� �� �����																		[]
//                                                                            []
identifier GetFeodIDByWebFolderID (identifier folderID)
{
	DEBUG_STACK_NAME (GetFeodIDByWebFolderID);
	if (!CHECK_WEBFOLDER_ID(folderID))
	{
		return NA;
	}
	return guid(OC_WebFolder(folderID).m_MOD_Base_GUID).id;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ��������� ������� ����� �����															[]
//                                                                            []
bool GetWebFolderFullName (identifier folderID, string& folderName, int FullNameLevel)
{
	DEBUG_STACK_NAME (GetWebFolderFullName);

	return GetFeodFullName (GetFeodIDByWebFolderID (folderID), folderName, FullNameLevel, "/");
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ��� ���������������� ��������-�����                              []
//                                                                            []
bool GetWebFolderType (identifier folderID, string& folderType)
{
	DEBUG_STACK_NAME (GetWebFolderType);
	
	folderType ="";

  	identifier feodID = GetFeodIDByWebFolderID (folderID);
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("������������ ������������� ����� %d", folderID);
		return false;
	}

	folderType = OC_Concept (feodID).m_Type;
	return true;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` GetWebFolderIDByType                                                      []                    
//                                                                            []
identifier GetWebFolderIDByType (const char * Type)
{
	DEBUG_STACK_NAME (GetWebFolderIDByType);

	identifier feodID = GetFeodIDByType (Type);

	if (feodID!=NA)
	{
		GET_MOD_EXTENSION (Concept, feodID, WebFolder, folder);
		if (folderID!=NA && CHECK_WEBFOLDER_ID(folderID))
		{
			return folderID;
		}
		return NA;
	}
	return NA;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` WebFolderGetAllWebFileSortedIDs                                           []                               
//                                                                            []
void WebFolderGetWebFileSortedIDs (identifier folderID, identifier_arr& fileIDs)
{
	DEBUG_STACK_NAME (WebFolderGetWebFileSortedIDs);

	fileIDs.Erase ();

	if (!CHECK_WEBFOLDER_ID(folderID))
	{
		SERVER_DEBUG_ERROR_1 ("������������ ID=%d �����", folderID);		
	}
	fileIDs = OC_WebFolder (folderID).m_WebFileSortedID;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` USER_CHECK_ACCESS_TO_WEBFOLDER                                            []                              
//                                                                            []
ERR_RESULT USER_CHECK_ACCESS_TO_WEBFOLDER (identifier userID, identifier folderID, const char * Attributes)
{
	DEBUG_STACK_NAME (USER_CHECK_ACCESS_TO_WEBFOLDER);

  	identifier feodID = GetFeodIDByWebFolderID (folderID);
	
	if (!CHECK_FEOD_ID (feodID))
	{
		return ERR_BadID;
	}

	return USER_CHECK_ACCESS (userID, feodID, Attributes);
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/