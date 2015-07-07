/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_Feod.pvt.cpp															[]
[] Date:          07.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с зонами доступа, концептами ветви {Concept.Feod})	[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_Feod.inc.h"



//______________________________________________________________________________
//                                                                            []
//` CHECK_FEOD_ID                                                             []             
//                                                                            []
bool CHECK_FEOD_ID (identifier feodID)
{
	DEBUG_STACK_NAME (CHECK_FEOD_ID);
	
	if (feodID==NA) return false;

	if (!OC_Exist (OBJ_CLASS_ID_Feod, feodID))
	{
		SERVER_DEBUG_ERROR_1 ("Объект Concept[%u] не существует", feodID);
		return false;
	}
	OC_Feod oc_feod (feodID);
	string	sConceptType = oc_feod.m_Type;
	
	if (sConceptType.Find ("Concept.Feod")!=0)
	{
		SERVER_DEBUG_ERROR_2 ("Concept[%u] (%s) не является феодом", sConceptType.c_str(), feodID);
		return false;
	}
	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodName                                                               []           
//                                                                            []
bool GetFeodName (identifier feodID, string& objName)
{
	DEBUG_STACK_NAME (GetFeodName);

	objName = "";
	if (CHECK_FEOD_ID (feodID))
	{
		objName = OC_Feod(feodID).m_Name;
		return true;
	}

	return false;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodFullName                                                           []               
//                                                                            []
bool GetFeodFullName (identifier feodID, string& objName, int nLevel, const char* sDelimiter)
{
	DEBUG_STACK_NAME (GetFeodFullName);

	objName = "";
	if (!CHECK_FEOD_ID (feodID))
	{
		return false;
	}

	return GetConceptFullName (feodID, objName, nLevel, sDelimiter);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodIDByName                                                           []
//                                                                            []
identifier GetFeodIDByName (const char * Name)
{
	DEBUG_STACK_NAME (GetFeodIDByName);

	identifier feodID = GetConceptID (Name, "Concept.Feod", true);
	if (!CHECK_FEOD_ID (feodID))
	{
		return NA;
	}
	return feodID;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodID                                                                 []         
//                                                                            []
identifier GetFeodIDByType (const char * Type)
{
	DEBUG_STACK_NAME (GetFeodIDByType);

	OC_Feod oc_feod;
	oc_feod.SetIndex_Type_Level();

	if (!oc_feod.Find (Type))
	{
		return NA;
	}

	return oc_feod.GetObjectID ();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` FeodHasChild					                                                []
//                                                                            []
bool FeodHasChild	(identifier feodID, identifier childID)
{
	DEBUG_STACK_NAME (FeodHasChild);

	if (!CHECK_FEOD_ID (feodID))
	{
		return false;
	}
	if (!CHECK_FEOD_ID (childID))
	{
		return false;
	}
	return OC_Feod(childID).m_AllAncestor.Find (feodID)!=-1;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` GetAllFeodChilds                                                          []                
//                                                                            []
bool GetAllFeodChilds (identifier feodID, identifier_arr& childIDs)
{
	DEBUG_STACK_NAME (GetAllFeodChilds);

	childIDs.Delete ();

	if (!CHECK_FEOD_ID (feodID))
	{
		return false;
	}
	OC_Feod oc_feod (feodID);

	oc_feod.m_Descendant.CopyTo (childIDs);
//----------------------------------------------------------------------------[] 
	



//----------------------------------------------------------------------------[] 
// Проверка на корректность дочерних феодов
	for (int f=0; f<childIDs.Size(); f++) if (!CHECK_FEOD_ID(childIDs[f]))
	{
		SERVER_DEBUG_ERROR_1 ("Обнаружен некорректный или несуществующий феод %u. Исправлено.", childIDs[f]);
		printf ("\nbad_feod_id = %d\n", childIDs[f]);

		identifier bad_feod_id = childIDs[f];
		childIDs.Del (f);
		f --;

	// Выкидываем ссылку на несуществующи дочерний феод
		int index = oc_feod.m_Child.Find (bad_feod_id);
		if (index!=-1) 
		{
			oc_feod.m_Child			.Del (index);
			oc_feod.m_ChildNo			.Del (index);
		}
		index = oc_feod.m_Descendant.Find (bad_feod_id);
		if (index!=-1) 
		{
			oc_feod.m_Descendant		.Del (index);
			oc_feod.m_DescendantNo	.Del (index);
		}

	// Выкидываем ссылку на несуществующи феод у всех предков
		if (oc_feod.m_Parent!=NA) for (OC_Feod oc_parent_feod (oc_feod.m_Parent); oc_parent_feod.IsValid(); oc_parent_feod.Open (oc_parent_feod.m_Parent))
		{
			index = oc_feod.m_Descendant.Find (bad_feod_id);
			if (index!=-1) 
			{
				oc_feod.m_Descendant		.Del (index);
				oc_feod.m_DescendantNo	.Del (index);
			}
		}

	// Удаляем в реестре ссылку на несуществующи феод:
		int Pos = oc_reg.m_ConceptID_Sorted.Find (bad_feod_id, true);
		if (Pos >= 0)
		{
			oc_reg.m_ConceptID_Sorted.Del (Pos);
			oc_reg.m_ConceptNo_SortID.Del (Pos);
		}
		Pos = oc_reg.m_ConceptID_SortNo.Find (bad_feod_id, true);
		if (Pos >= 0)
		{
			oc_reg.m_ConceptID_SortNo		[Pos] = NA;	// признак удалённого концепта
			oc_reg.m_ConceptParent_SortNo	[Pos] = -1;	// признак удалённого концепта
			oc_reg.m_ConceptType_SortNo	[Pos] = -1;	// признак удалённого концепта
			oc_reg.m_ConceptLevel_SortNo	[Pos] = -1;	// признак удалённого концепта
		}
	}
//----------------------------------------------------------------------------[] 


	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodLevel                                                              []            
//                                                                            []
int GetFeodLevel (identifier feodID)
{
	DEBUG_STACK_NAME (GetFeodLevel);
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("Указанная зона доступа %d не существует", feodID);
		return -1;
	}
	return OC_Feod (feodID).m_Level;
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Получить список всех потомков феода                                       []                                   
//                                                                            []
bool GetFeodDescendantIDs (identifier feodID, identifier_arr& DescendantIDs)
{
	DEBUG_STACK_NAME (GetFeodDescendantIDs);

// Очищаем массив
	DescendantIDs.Erase();

//	Проверка на валидность
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("Некорректный феод %d", feodID);
		return false;
	}

// Рекурсивно заполняем массив
	OC_Feod oc_feod (feodID);

	identifier_arr ChildIDs = oc_feod.m_Child;
	for (int f=0; f<ChildIDs.Size(); f++)
	{
		DescendantIDs += ChildIDs[f];

	// Запращиваем всех потомков у дочернего феода
		identifier_arr tmpArr;
		if (GetFeodDescendantIDs (ChildIDs[f], tmpArr))
		{
		// Добавляем потомков дочернего феода к своим
			for (int i=0; i<tmpArr.Size(); i++)
			{
				DescendantIDs += tmpArr[i];
			}
		}
		else
		{
			SERVER_DEBUG_ERROR_3 ("У феода '%s'[%u] некорректный дочерний феод %u. Исправлено.", string(oc_feod.m_Type).c_str(), feodID, ChildIDs[f]);
			identifier bad_feod_id = ChildIDs[f];
		// Выкидываем ссылку на несуществующи дочерний феод
			int index = oc_feod.m_Child.Find (bad_feod_id);
			if (index!=-1) 
			{
				oc_feod.m_Child			.Del (index);
				oc_feod.m_ChildNo			.Del (index);
			}
			index = oc_feod.m_Descendant.Find (bad_feod_id);
			if (index!=-1) 
			{
				oc_feod.m_Descendant		.Del (index);
				oc_feod.m_DescendantNo	.Del (index);
			}
		// Выкидываем ссылку на несуществующи феод у всех предков
			if (oc_feod.m_Parent!=NA) for (OC_Feod oc_parent_feod (oc_feod.m_Parent); oc_parent_feod.IsValid(); oc_parent_feod.Open (oc_parent_feod.m_Parent))
			{
				index = oc_feod.m_Descendant.Find (bad_feod_id);
				if (index!=-1) 
				{
					oc_feod.m_Descendant		.Del (index);
					oc_feod.m_DescendantNo	.Del (index);
				}
			}
		// Удаляем в реестре ссылку на несуществующи феод:
			int Pos = oc_reg.m_ConceptID_Sorted.Find (bad_feod_id, true);
			if (Pos >= 0)
			{
				oc_reg.m_ConceptID_Sorted.Del (Pos);
				oc_reg.m_ConceptNo_SortID.Del (Pos);
			}

			Pos = oc_reg.m_ConceptID_SortNo.Find (bad_feod_id, true);
			if (Pos >= 0)
			{
				oc_reg.m_ConceptID_SortNo		[Pos] = NA;	// признак удалённого концепта
				oc_reg.m_ConceptParent_SortNo	[Pos] = -1;	// признак удалённого концепта
				oc_reg.m_ConceptType_SortNo	[Pos] = -1;	// признак удалённого концепта
				oc_reg.m_ConceptLevel_SortNo	[Pos] = -1;	// признак удалённого концепта
			}
		}
	}
	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` GetFeodParentID                                                           []               
//                                                                            []
identifier GetFeodParentID (identifier feodID)
{
	DEBUG_STACK_NAME (GetFeodParentID);

//	Проверка на валидность
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("Некорректный феод %d", feodID);
		return false;
	}

	OC_Feod oc_feod (feodID);
	return oc_feod.m_Parent;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` GetFeodType                                                               []           
//                                                                            []
void GetFeodType (identifier feodID, string& Type)
{
	DEBUG_STACK_NAME (GetFeodType);

	Type = "";
//	Проверка на валидность
	if (!CHECK_FEOD_ID (feodID))
	{
		SERVER_DEBUG_ERROR_1 ("Некорректный феод %d", feodID);
		return;
	}

	OC_Feod oc_feod (feodID);
	Type = oc_feod.m_Type;
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ФУНКЦИИ ДЛЯ МЕЖМОДУЛЬНЫХ ВЫЗОВОВ                                          []                                
[]                                                                            []
[]____________________________________________________________________________[]
*/





//______________________________________________________________________________
//                                                                            []
//` MOD_CHECK_ACCESS                                                          []                
//                                                                            []
void MOD_CHECK_ACCESS (identifier userID, guid_arr& objGUIDs, const char * Attributes)
{
	DEBUG_STACK_NAME (MOD_CHECK_ACCESS);
	for (int i=0; i<objGUIDs.Size(); i++)
	{
		if (objGUIDs[i].cl!=NA && objGUIDs[i].id!=NA && !OC_Exist (objGUIDs[i]))
		{
			objGUIDs[i].cl = NA;
			objGUIDs[i].id = NA;
			objGUIDs[i].rn	= NA;
			continue;
		}

		if (MOD_CHECK_ACCESS_FUNCTION_ARR[objGUIDs[i].cl]) 
		{
			(MOD_CHECK_ACCESS_FUNCTION_ARR[objGUIDs[i].cl])(userID, objGUIDs[i], Attributes);
		}
	}
}
//----------------------------------------------------------------------------[] 
bool MOD_CHECK_ACCESS (identifier userID, guid objGUID, const char * Attributes)
{
	DEBUG_STACK_NAME (MOD_CHECK_ACCESS);

// Если не указан объект -- "есть доступ"
	if (objGUID.cl==NA && objGUID.id==NA)
	{
		return true;
	}

// Если указанный объект не существует -- нет доступа
	if (!OC_Exist (objGUID))
	{
		return false;
	}

// Если указанный существует -- проверяем доступ в зависимости от класса
	if (MOD_CHECK_ACCESS_FUNCTION_ARR[objGUID.cl])
	{
		(MOD_CHECK_ACCESS_FUNCTION_ARR[objGUID.cl])(userID, objGUID, Attributes);
		return objGUID.cl!=NA;
	}

// Если никто не контролирует доступ к объектам данного класса -- доступ есть
	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` MOD_CHECK_PLACEMENT                                                       []                   
//                                                                            []
void MOD_CHECK_PLACEMENT (identifier_arr& feodIDs, guid_arr& objGUIDs)
{
	DEBUG_STACK_NAME (MOD_CHECK_PLACEMENT);
	for (int i=0; i<objGUIDs.Size(); i++)
	{
		if (objGUIDs[i].cl!=NA && objGUIDs[i].id!=NA && !OC_Exist (objGUIDs[i]))
		{
			objGUIDs[i].cl = NA;
			objGUIDs[i].id = NA;
			objGUIDs[i].rn	= NA;
			continue;
		}
		if (MOD_CHECK_PLACEMENT_FUNCTION_ARR[objGUIDs[i].cl])
		{
			(MOD_CHECK_PLACEMENT_FUNCTION_ARR[objGUIDs[i].cl])(feodIDs, objGUIDs[i]);
		}
	}
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` MOD_CHECK_ACCESS_PLACEMENT                                                []                          
//                                                                            []
void MOD_CHECK_ACCESS_PLACEMENT (identifier userID, guid_arr& objGUIDs, const char * Attributes, identifier_arr& feodIDs, int nMaxFound)
{
	DEBUG_STACK_NAME (MOD_CHECK_ACCESS_PLACEMENT);
	int i,nFound = 0;
	for (i=0; i<objGUIDs.Size(); i++)
	{
		if (objGUIDs[i].cl!=NA && objGUIDs[i].id!=NA && !OC_Exist (objGUIDs[i]))
		{
			objGUIDs[i].cl = NA;
			objGUIDs[i].id = NA;
			objGUIDs[i].rn	= NA;
			continue;
		}

		if (nMaxFound>=0 && nFound>nMaxFound)
		{
			objGUIDs[i].cl=NA;
			objGUIDs[i].id=NA;
			objGUIDs[i].rn=0;
		}
		else
		{
			if (MOD_CHECK_PLACEMENT_FUNCTION_ARR[objGUIDs[i].cl] && objGUIDs[i].cl!=NA)
			{
				(MOD_CHECK_PLACEMENT_FUNCTION_ARR[objGUIDs[i].cl])(feodIDs, objGUIDs[i]);
			}

			if (MOD_CHECK_ACCESS_FUNCTION_ARR[objGUIDs[i].cl] && objGUIDs[i].cl!=NA)
			{
				(MOD_CHECK_ACCESS_FUNCTION_ARR[objGUIDs[i].cl])(userID, objGUIDs[i], Attributes);
			}
			
			if (objGUIDs[i].cl!=NA)
			{
				nFound++;
			}
		}
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` MOD_GET_OBJECT_NAME                                                       []                   
//                                                                            []
const char * MOD_GET_OBJECT_NAME (guid& gi)
{
	DEBUG_STACK_NAME (MOD_GET_OBJECT_NAME);
	static string sNAME;
	if (MOD_GET_OBJECT_NAME_FUNCTION_ARR[gi.cl])
	{
		if (!OC_Exist (gi))
		{
			return ("{{ERROR: Object not found}}");
		}
		(MOD_GET_OBJECT_NAME_FUNCTION_ARR[gi.cl])(gi, sNAME);
	}
	return sNAME;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` MOD_GET_OBJECT_DESCRIPTION                                                []                          
//                                                                            []
const char * MOD_GET_OBJECT_DESCRIPTION (guid& gi)
{
	DEBUG_STACK_NAME (MOD_GET_OBJECT_DESCRIPTION);
	static string sDESCRIPTION;
	if (MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR[gi.cl])
	{
		if (!OC_Exist (gi))
		{
			return ("{{ERROR: Object not found}}");
		}
		(MOD_GET_OBJECT_DESCRIPTION_FUNCTION_ARR[gi.cl])(gi, sDESCRIPTION);
	}
	return sDESCRIPTION;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Привести набор феодов к корректному состоянию										[]
//                                                                            []
void FIX_FEODS (void)
{
	DEBUG_STACK_NAME (FIX_FEODS);

// Проверяем все феоды на наличие предков -- идём по индексу
	int				i,f;
	OC_Concept		oc_feod;
	identifier_arr	allFeods;
	oc_feod.GetClassIdList (allFeods);
	for (i=0; i<allFeods.Size(); i++)
	{
		oc_feod.Open (allFeods[i]);
		string	sConceptType = oc_feod.m_Type;		
		if (sConceptType.Find ("Concept.Feod")!=0) continue;

		bool bDelete = !OC_Exist (OBJ_CLASS_ID_Concept, oc_feod.m_Parent);
	// Если не существует хотя бы одного предка, то феод надо удалить
		for (f=0; !bDelete && f<oc_feod.m_AllAncestor.Size(); f++)
		{
			if (!OC_Exist (OBJ_CLASS_ID_Concept, oc_feod.m_AllAncestor[f]))
			{
				bDelete = true;
			}
		}
	// Если не существует хотя бы одного предка, то феод надо удалить
		for (f=0; !bDelete && f<oc_feod.m_Ancestor.Size(); f++)
		{
			if (!OC_Exist (OBJ_CLASS_ID_Concept, oc_feod.m_Ancestor[f]))
			{
				bDelete = true;
			}
		}
		if (bDelete)
		{
		// Удаляем феод, так как у него нет одного из предков
			oc_feod.DebugPrint ();
			MOD_Concept_Args concept_arg;
			concept_arg.objID = allFeods[i];
			GetPicklockPassword (concept_arg.PicklockPassword);
			MOD_Concept_Delete (concept_arg);
			if (oc_feod.IsValid()) oc_feod.Delete(); // На всякий случай
		}
	}

// Проверяем потомков всех существующих феодов
	for (oc_feod.GoFirst(); oc_feod.IsValid(); oc_feod++)
	{
		for (f=0; f<oc_feod.m_Descendant.Size(); f++)
		{
			if (!OC_Exist (OBJ_CLASS_ID_Concept, oc_feod.m_Descendant[f]))
			{
				oc_feod.m_Descendant.	Del (f);
				oc_feod.m_DescendantNo.	Del (f);
				f --;
			}
		}
		for (f=0; f<oc_feod.m_Child.Size(); f++)
		{
			if (!OC_Exist (OBJ_CLASS_ID_Concept, oc_feod.m_Child[f]))
			{
				oc_feod.m_Child.	Del (f);
				oc_feod.m_ChildNo.Del (f);
				f --;
			}
		}
	}

// Проверяем на существование все феоды, записанные в реестре
	for (f=0; f<oc_reg.m_ConceptID_Sorted.Size(); f++)
	{
		identifier feodID = oc_reg.m_ConceptID_Sorted[f];
		if (!OC_Exist (OBJ_CLASS_ID_Concept, feodID))
		{
			int Pos = oc_reg.m_ConceptID_Sorted.Find(feodID, true);
			if (Pos >= 0)
			{
				oc_reg.m_ConceptID_Sorted.Del(Pos);
				oc_reg.m_ConceptNo_SortID.Del(Pos);
			}
			Pos = oc_reg.m_ConceptID_SortNo.Find(feodID, true);
			if (Pos >= 0)
			{
				oc_reg.m_ConceptID_SortNo		[Pos] = NA;	// признак удалённого концепта
				oc_reg.m_ConceptParent_SortNo	[Pos] = -1;	// признак удалённого концепта
				oc_reg.m_ConceptType_SortNo	[Pos] = -1;	// признак удалённого концепта
				oc_reg.m_ConceptLevel_SortNo	[Pos] = -1;	// признак удалённого концепта
			}
		}
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Преобразовнаие зон доступа в guid'ы                                       []                                   
//                                                                            []
void GetFeodGUIDs (identifier_arr& FeodIDs, guid_arr& FeodGUIDs)
{
	DEBUG_STACK_NAME (GetFeodGUIDs);

	for (int f=0; f<FeodIDs.Size(); f++)
	{
		OC_Concept		oc_feod;
		oc_feod.Open (FeodIDs[f]);
		FeodGUIDs += oc_feod.GetObjectGUID ();
	}	
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/