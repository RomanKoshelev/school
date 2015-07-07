/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Language.cpp                                           []
[] Date:            21.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                    

#define USES_BX_Errors
#define USES_BX_SingleObject
#define USES_BX_Language
#define USES_BX_Macros
#define USES_BX_Admin

#define USES_OC_Language
#define USES_OC_Concept

#include "BX.h"
//----------------------------------------------------------------------------[] 

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Language_New                                                           []
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Language_New(BX_Language_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
	
	OC_Language			oc_language;
	int					arr_size = 0;
	int					i			= 0;
	
	int nLangs = oc_reg.m_Language.Size();		// Число имеющихся в системе языков.

// Проверка допустимости входных параметров	
	
	if (nLangs != arg.Name.Size())
		return BXE_Language_New_InvalidLanguageNameList;
	
	if (nLangs != arg.Language.Size())
		return BXE_Language_New_InvalidLanguageTransList;

 // Создать новый язык
	oc_language.New();		
	SERVER_DEBUG_ASSERT_RETURN(
		oc_language.IsValid(),
		"BX_Language_New(): Can't create object.",
		BX_SYSTEM_ERROR);

	identifier newLangID = oc_language.GetObjectID();

	arg.objID = newLangID;

// Назначить порядковый номер:
	oc_language.m_No = nLangs;

// Добавить в реестр:
	arr_size = oc_reg.m_Language.Add(newLangID);	
	SERVER_DEBUG_ASSERT_RETURN(
		arr_size == nLangs+1,
		"BX_Language_New(): Error adding language id to registry.",
		BX_SYSTEM_ERROR);

// Добавить аббревиатуру языка.
	oc_language.m_ShortName = arg.ShortName;

// Добавить названия на поддерживаемых языках:
	oc_language.m_Name.CopyFrom(arg.Name);
	oc_language.m_Name.Add(arg.OwnName);

// Добавить названия др. языков на новом языке:
	for (i = 0; i < nLangs; i++)
	{
		oc_language.Open(oc_reg.m_Language[i]);
		arr_size = oc_language.m_Name.Add(arg.Language[i]);
		SERVER_DEBUG_ASSERT_RETURN(
			arr_size == nLangs+1,
			"BX_Language_New(): Error adding language translations.",
			BX_SYSTEM_ERROR);
	}

// Добавить поля имён концептов:
	identifier_arr	ObjectList;

	// Concept
	OC_Concept		oc_concept;
	oc_concept.GetClassIdList(ObjectList);
	for (i = 0; i < ObjectList.Size(); i++)
	{
		oc_concept.Open(ObjectList[i]);
		SERVER_DEBUG_ASSERT_RETURN(
			oc_concept.m_Name.Size() == nLangs,
			"BX_Language_New(): Invalid Concept::Name.Size().",
			BX_SYSTEM_ERROR);
		if (nLangs == 0)
			oc_concept.m_Name.Add("");
		else
			oc_concept.m_Name.Add(oc_concept.m_Name[0]);
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Language_PutData                                                       []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_Language_PutData(BX_Language_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
	
	OC_Language			oc_language;
	int					i			= 0;
	
	int nLangs = oc_reg.m_Language.Size();		// Число имеющихся в системе языков.

// Проверка допустимости входных параметров	
	
	if (!OC_Exist(OBJ_CLASS_ID_Language, arg.objID))
		return BXE_Language_InvalidObjectID;

	if (nLangs-1 != arg.Name.Size())
		return BXE_Language_New_InvalidLanguageNameList;

	if (nLangs-1 != arg.Language.Size())
		return BXE_Language_New_InvalidLanguageTransList;

	int					ExcludeNo	= 0;
	int					indexCount	= 0;
		

// Открыть объект языка
	oc_language.Open(arg.objID);
	ExcludeNo = oc_language.m_No;

// Изменить аббревиатуру языка.
	oc_language.m_ShortName = arg.ShortName;

// Изменить названия языка на поддерживаемых языках:
	oc_language.m_Name.Delete();
	for (i = 0; i < nLangs; i++)
	{
		if (i != ExcludeNo)
		{
			oc_language.m_Name.Add(arg.Name[indexCount]);
			indexCount	++;
		}
		else
		{
			oc_language.m_Name.Add(arg.OwnName);
		}
	}

// Изменить названия др. языков на новом языке:
	indexCount	= 0;
	for (i = 0; i < nLangs; i++)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Language, oc_reg.m_Language[i]),
			"BX_Language_PutData: Invalid Registry::Language[i].",
			BX_SYSTEM_ERROR);

		oc_language.Open(oc_reg.m_Language[i]);
		if (ExcludeNo == oc_language.m_No)
			continue;		// Пропустить себя.
		oc_language.m_Name[ExcludeNo] = arg.Language[indexCount];
		indexCount++;
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Language_Enumerate																		[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Language_Enumerate(BX_Language_Args& arg)
{
	if (arg.objLanguageNo > oc_reg.m_Language.Size())	arg.objLanguageNo = -1;
	if (arg.objFirstNo < 0)										arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)						arg.objLastNo		= INT_MAX;

	OC_Language	oc_language;

	arg.objNames.Delete();
	arg.objIDs.Delete();

	for (int i = arg.objFirstNo; (i<oc_reg.m_Language.Size()) && (i<=arg.objLastNo); i++)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Language, oc_reg.m_Language[i]),
			"BX_Language_Enumerate(): Invalid Registry::Language[i].",
			BX_SYSTEM_ERROR);

		oc_language.Open(oc_reg.m_Language[i]);

		SERVER_DEBUG_ASSERT_RETURN(
			oc_language.m_Name.Size() > 0,
			"BX_Language_Enumerate(): Language::Name.Size() = 0.",
			BX_SYSTEM_ERROR);

		if (arg.objLanguageNo < 0)
			arg.objNames.Add(oc_language.m_Name[oc_language.m_No]);
		else
			arg.objNames.Add(oc_language.m_Name[arg.objLanguageNo]);

	}

	oc_reg.m_Language.CopyTo(arg.objIDs);
	
	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Language_GetData                                                       []
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Language_GetData(BX_Language_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Language, arg.objID))
	{
		arg.Language.Delete();
		arg.Name.Delete();
		arg.OwnName.Delete();
	
		return BXE_Language_InvalidObjectID;
	}
	
	OC_Language		oc_language;
	oc_language.Open(arg.objID);

	int	nLangs		= oc_reg.m_Language.Size();		// Число имеющихся в системе языков.
	int	thisLangNo	= oc_language.m_No;
	int	i				= 0;

// Скопируем названия данного языка на всех имеющихся:
	oc_language.m_Name.CopyTo(arg.Name);

	SERVER_DEBUG_ASSERT_RETURN(
		oc_language.m_No >= 0,
		"BX_Language_GetData(): Language::No < 0.",
		BX_SYSTEM_ERROR);

// Положим названия данного язывка на самом себе:
	arg.OwnName = oc_language.m_Name[oc_language.m_No];

// Скопируем аббревиатуру языка.

	arg.ShortName	= oc_language.m_ShortName;
// Исключим данный язык:
	arg.Name.Del(oc_language.m_No);

// Скопируем номер:
	arg.No = oc_language.m_No;

// Копируем названия имеющихся языков на данном:
	arg.Language.Delete();
	for (i = 0; i < nLangs; i++)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Language, oc_reg.m_Language[i]),
			"BX_Language_GetData(): Invalid Registry::Language[i].",
			BX_SYSTEM_ERROR);

		oc_language.Open(oc_reg.m_Language[i]);

		SERVER_DEBUG_ASSERT_RETURN(
			oc_language.m_No >= 0,
			"BX_Language_GetData(): Language::No < 0.",
			BX_SYSTEM_ERROR);

		if (thisLangNo == oc_language.m_No)
			continue;		// Пропустить себя.

		arg.Language.Add(oc_language.m_Name[thisLangNo]);
	}

	return BX_OK;
}

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Language_Delete                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Language_Delete(const BX_Language_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
	
	if (!OC_Exist(OBJ_CLASS_ID_Language, arg.objID))
		return BXE_Language_InvalidObjectID;

	OC_Language		oc_language;
	int				i;

// Взять порядковый номер языка:
	oc_language.Open(arg.objID);
	int lNo = oc_language.m_No;

// Удалить язык
	oc_language.Delete();

// Удалить упоминания о языке из реестра:	
	DELETE_FROM_ARRAY(oc_reg.m_Language, arg.objID);

// Удалить упоминания о языке из других языков:
	for (i = 0; i < oc_reg.m_Language.Size(); i++)
	{
		SERVER_DEBUG_ASSERT_RETURN(
			OC_Exist(OBJ_CLASS_ID_Language, oc_reg.m_Language[i]),
			"BX_Language_Delete(): Invalid Registry::Language[i].",
			BX_SYSTEM_ERROR);
		oc_language.Open(oc_reg.m_Language[i]);
		oc_language.m_Name.Del(lNo);
		if (oc_language.m_No > lNo) {
			oc_language.m_No -= 1;
		}
	}

// Удалить соответсвующие названия в перечислителях:
	identifier_arr	ObjectList;

	// Concept
	OC_Concept		oc_concept;
	oc_concept.GetClassIdList(ObjectList);
	for (i = 0; i < ObjectList.Size(); i++)
	{
		oc_concept.Open(ObjectList[i]);
		oc_concept.m_Name.Del(lNo);
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