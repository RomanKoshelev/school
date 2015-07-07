/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Keyword.cpp                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "�������� �����".           []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                

#define USES_BX_Errors
#define USES_BX_Keyword
#define USES_BX_Macros

#define USES_EventMonitor_h
#define USES_ArgResCache_h
#define USES_OC_Keyword
#define USES_OC_SiteList

#include "BX.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Keyword_AddSite                                                        []                  
[]                                                                            []
[]____________________________________________________________________________[]
*/
// ��������� � �������� ������ Keywords ���� idSite �� ����������� ���� idVBN.
// �������������� �������� �������� ���� ������������ � ������� idKeywords.
BX_RESULT 
BX_Keyword_AddSite(const string_arr& Keywords, identifier idSite, identifier idVBN, identifier_arr& idKeywords)
{
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_Site, idSite),
		"BX_Keyword_AddSite(): Invalid site ID.",
		BX_SYSTEM_ERROR);
	
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_VBN, idVBN),
		"BX_Keyword_AddSite(): Invalid VBN ID.",
		BX_SYSTEM_ERROR);

	idKeywords.Delete();

	OC_SiteList		oc_site_list;
	identifier_arr	siteList;
	
	OC_Keyword	oc_keyword;
	oc_keyword.SetIndex_Word();

	key_arr		ka;
//----------------------------------------------------------------------------[] 

	for (int i = 0; i < Keywords.Size(); i++)
	{
		ka.Init();
		ka += string(Keywords[i]);

	// ������ ��� ������ ��������� ����� ��� ����������:
		if (oc_keyword.Find(ka))
		{
			SERVER_DEBUG_ASSERT_RETURN(
				oc_keyword.m_VBN_ID.Size() == oc_keyword.m_VBN_SiteList.Size(),
				"BX_Keyword_AddSite(): Unequal sizes of Keyword::VBN_ID and Keyword::VBN_SiteList.",
				BX_SYSTEM_ERROR);

			int posVBN = oc_keyword.m_VBN_ID.Find(idVBN);
			
			if (posVBN != -1)
		// ���� ����� ���� VBN ��� ���������������� � ����� ��������� ����� ...
			{
			// �������� ������ ������ ������:
				BX_CHECK_AND_OPEN(oc_site_list, oc_keyword.m_VBN_SiteList[posVBN], OBJ_CLASS_ID_SiteList);

			// ������ ������ �� ����� ���� ������, ����� �� ��� ���������� � BX_Keyword_DeleteSite():
				SERVER_DEBUG_ASSERT_RETURN(
					oc_site_list.m_Site.Size() > 0,
					"BX_Keyword_AddSite(): Empty SiteList opened - it should have been deleted by BX_Keyword_DeleteSite().",
					BX_SYSTEM_ERROR);
			// ��������, � �� �������� �� �������� ������������:
				SERVER_DEBUG_ASSERT_RETURN(
					oc_site_list.m_Site.Find(idSite, true),
					"BX_Keyword_AddSite(): Double reference to site in sitelist.",
					BX_SYSTEM_ERROR);
			// ��������� �������������� ������ �� ��������� ������:
				siteList = oc_site_list.m_Site.GetCPtr();
			// ������� ����� ����:
				siteList.Add(idSite);
			// �����������:
				siteList.Sort();
			// ������� �� �����:
				oc_site_list.m_Site = siteList;
			// ��������� ����� ������ ������ ������:
				oc_keyword.m_VBN_SiteListSize[posVBN] = siteList.GetSize();
			}
		// ���� ����� ���� VBN ��� �� ���������������� � ����� ��������� ����� ...
			else
			{
			// ������� ������ �� VBN � ������ ��������� �����:
				oc_keyword.m_VBN_ID.Add(idVBN);
			// �������� ����� ������ ������ ��� ���� VBN:
				oc_site_list.New();
			// ������� ��� ���� � ����� ������:
				oc_site_list.m_Site.Add(idSite);
			// ������� ������ �� ����� ������ ������ � ������ ��������� �����:
				oc_keyword.m_VBN_SiteList.Add(oc_site_list.GetObjectID());
			// ��������� ����� ������ ������ ������:
				oc_keyword.m_VBN_SiteListSize.Add(1);
			}

		} // end if (oc_keyword.Find(ka))

	// ������� ��� ������ ��������� ����� ��� �� ����������:
		else
		{
		// �������� ����� ������ ��������� �����:
			oc_keyword.New();
			oc_keyword.m_Word = Keywords[i];

		// ������� ������ �� VBN � ������ ��������� �����:
			oc_keyword.m_VBN_ID.Add(idVBN);
		// �������� ����� ������ ������ ��� ���� VBN:
			oc_site_list.New();
		// ������� ��� ���� � ����� ������:
			oc_site_list.m_Site.Add(idSite);
		// ������� ������ �� ����� ������ ������ � ������ ��������� �����:
			oc_keyword.m_VBN_SiteList.Add(oc_site_list.GetObjectID());
		// ��������� ����� ������ ������ ������:
			oc_keyword.m_VBN_SiteListSize.Add(1);
		}
	
	// ������� ������������� ������� ��������� ����� � �������� ������:
		idKeywords.Add(oc_keyword.GetObjectID());

	} // end for (int i = 0; i < Keywords.Size(); i++)

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Keyword_DeleteSite                                                     []                     
[]                                                                            []
[]____________________________________________________________________________[]
*/
// ������� ���� idSite �� ������� � �������� �������� ���� idKeywords.
BX_RESULT
BX_Keyword_DeleteSite(const identifier_arr& idKeywords, identifier idSite, identifier idVBN)
{
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_Site, idSite),
		"BX_Keyword_DeleteSite(): Invalid site ID.",
		BX_SYSTEM_ERROR);
	
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_VBN, idVBN),
		"BX_Keyword_DeleteSite(): Invalid VBN ID.",
		BX_SYSTEM_ERROR);

	OC_Keyword		oc_keyword;
	OC_SiteList		oc_site_list;

//----------------------------------------------------------------------------[] 

	for (int i = 0; i < idKeywords.Size(); i++)
	{
	// �������� ������ ��������� �����:
		BX_CHECK_AND_OPEN(oc_keyword, idKeywords[i], OBJ_CLASS_ID_Keyword);

	// ������ ������ ������, ��������������� VBN:
		int posVBN = oc_keyword.m_VBN_ID.Find(idVBN);
		SERVER_DEBUG_ASSERT_RETURN(
			posVBN != -1,
			"BX_Keyword_DeleteSite(): SiteList for this VBN not found.",
			BX_SYSTEM_ERROR);

	// �������� ���:
		BX_CHECK_AND_OPEN(oc_site_list, oc_keyword.m_VBN_SiteList[posVBN], OBJ_CLASS_ID_SiteList);

	// ������ ���� �� ������:
		int posSite = oc_site_list.m_Site.Find(idSite, true);
		SERVER_DEBUG_ASSERT_RETURN(
			posSite != -1,
			"BX_Keyword_DeleteSite(): Site not found in SiteList.",
			BX_SYSTEM_ERROR);
		oc_site_list.m_Site.Del(posSite);
	// ��������� ����� ������ ������ ������:
		oc_keyword.m_VBN_SiteListSize[posVBN] = oc_site_list.m_Site.GetSize();

	// �������� �� ������������:
		SERVER_DEBUG_ASSERT_RETURN(
			oc_site_list.m_Site.Find(idSite, true) == -1,
			"BX_Keyword_DeleteSite(): Double reference to site in sitelist.",
			BX_SYSTEM_ERROR);
	
	// ������ ������ ������, ���� �� ���� ������:
		if (oc_site_list.m_Site.Size() == 0)
		{
			oc_site_list.Delete();
			oc_keyword.m_VBN_SiteList.Del(posVBN);
			oc_keyword.m_VBN_SiteListSize.Del(posVBN);
			oc_keyword.m_VBN_ID.Del(posVBN);
		}
		
	} // end for (int i = 0; i < idKeywords.Size(); i++)
	
	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Keyword_IDToStr                                                        []                  
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Keyword_IDToStr(string_arr& strKeywords, const identifier_arr& idKeywords)
{
	strKeywords.Erase();

	key_arr		ka;
	OC_Keyword	oc_keyword;

	for (int i = 0; i < idKeywords.Size(); i++)
	{
		if (!OC_Exist(OBJ_CLASS_ID_Keyword, idKeywords[i])) {
			SERVER_DEBUG_ERROR_1 ("BX_Keyword_IDToStr(): Non-existing keyword id #%lu. Skipped",
				idKeywords[i]);
			continue;
		}

		oc_keyword.Open(idKeywords[i]);

		strKeywords.Add(oc_keyword.m_Word);
	}

	return BX_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/