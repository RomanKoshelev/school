/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Concept.cpp                                            []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "�������"                   []
[] Last Modified:																	            []
[]____________________________________________________________________________[]
*/                                                                 

#define USES_BX_Errors
#define USES_BX_SingleObject
#define USES_BX_Macros
#define USES_BX_Concept
#define USES_BX_Utils
#define USES_BX_Admin

#define USES_ArgResCache_h
#define USES_OBServer_Interface_h
#define USES_OC_Language
#define USES_OC_Concept
#define USES_OC_ConceptList
#define USES_OC_SiteList

#include "BX.h"

//----------------------------------------------------------------------------[] 



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_New                                                            []
[]                                                                            []
[]____________________________________________________________________________[]
*/

BX_RESULT
BX_Concept_New(BX_Concept_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
	
// ���������, �� ���� �� ������ ���� �������� � ��������:
	int nLangs = oc_reg.m_Language.Size();
	if (nLangs < 1)								return BXE_NoLanguages;
	if (nLangs != arg.Name.Size())			return BXE_Concept_New_InvalidNameList;
	if	(nLangs != arg.Description.Size())	return BXE_Concept_New_InvalidDescriptionList;

// ���������, �������� �� �����������:
	if ((arg.Type.Size() < 1) || (arg.TypeNo < 0))
		return BXE_Concept_New_InvalidTypeInfo;

//----------------------------------------------------------------------------[]
	OC_Concept		oc_concept, oc_parent_concept;
	identifier		conceptID;
	key_arr			ka;
	int				No		= -1;
	int				Level = -1;
	int				Pos	= -1;

//----------------------------------------------------------------------------[]
// �������� ����������� �������:
	Pos = oc_reg.m_ConceptID_Sorted.Size();
	if (Pos != oc_reg.m_ConceptNo_SortID.Size()) return BX_SYSTEM_ERROR;

	Pos = oc_reg.m_ConceptID_SortNo.Size();
	if (Pos != oc_reg.m_ConceptParent_SortNo.Size()) return BX_SYSTEM_ERROR;
	if (Pos != oc_reg.m_ConceptType_SortNo.Size()) return BX_SYSTEM_ERROR;
//----------------------------------------------------------------------------[]
// ��������� ������������� �������� / �������������� �����, 
// ��������� ���������� �����:
	if (arg.Parent != NA)	// �� ������.
	{
		if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.Parent)) return BXE_Concept_New_InvalidParentID;

	// ������� ��������� ��������� �����:
		No = oc_reg.m_ConceptID_SortNo.Size();

	// ��������, ��� ���� ����� ������������� �� �����:
		ka.Init();
		ka += No;
		oc_concept.SetIndex_No();
		SERVER_DEBUG_ASSERT_RETURN(
			!oc_concept.Find(ka),
			"BX_Concept_New(): Numerating error!",
			BX_SYSTEM_ERROR);

	// �������� ������ ������������� ��������:
		oc_parent_concept.Open(arg.Parent);

	// �������� ������� ������������ ��������:
		Level = oc_parent_concept.m_Level + 1;
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	else	// ������.
	{
	// ������ ������ ����������� ������:
		oc_concept.SetIndex_Level();
		if (oc_concept.GetTotalNum() != 0)	return BXE_Concept_New_RootAlreadyExists;
		if (oc_reg.m_ConceptID_SortNo.Size() != 0)	return BXE_Concept_New_RootAlreadyExists;

	// ������ ������ ����� ����� 0:
		No		= 0;

	// ������ ������ ����� ������� 0:
		Level = 0;
	}
//----------------------------------------------------------------------------[]
// �������� ��������:
	BX_CREATE_AND_CHECK(oc_concept);

// ��������� �������������:
	conceptID						= oc_concept.GetObjectID();

// ��������� ���������� �����:
	oc_concept.m_No				= No;

// ��������� �������:
	oc_concept.m_Level			= Level;

// �������� � ������ ������������� � �����:
	Pos = oc_reg.m_ConceptID_Sorted.	InsertSorted(conceptID);
	oc_reg.m_ConceptNo_SortID.			Insert(Pos, No);

	oc_reg.m_ConceptID_SortNo.			Add(conceptID);
	oc_reg.m_ConceptParent_SortNo.	Add(
		arg.Parent != NA ? (int)oc_parent_concept.m_No : -1);
	oc_reg.m_ConceptType_SortNo.		Add(arg.TypeNo);
	oc_reg.m_ConceptLevel_SortNo.		Add(Level);

// �������� �������� � �������� �� �������������� ������:
	oc_concept.m_Name.			CopyFrom(arg.Name);
	oc_concept.m_Description.	CopyFrom(arg.Description);
	oc_concept.m_ShortName		= arg.ShortName;

// �������� ��������� �����������:
	oc_concept.m_Type				= arg.Type;
	oc_concept.m_TypeNo			= arg.TypeNo;
//	oc_concept.m_Mask				= (arg.TypeNo<<11) | (No & 0x7ff);

// ��������� � ���� ������������ �������:
	oc_concept.m_Parent			= arg.Parent;
//----------------------------------------------------------------------------[]
// ���������� �����, ��������� � �����������:
	if	(arg.Parent != NA)
	{
	// ����������� � ������ ����� ������������� ��������:
		Pos = oc_parent_concept.m_ChildNo.	AddSorted(No);
		oc_parent_concept.m_Child.				Insert (Pos, conceptID);
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -
	// �������� �� ���� ������� � ���������� � ���� ������������:
		for (;;)
		{
		// �������� ID ���������� �������� � ������ �������� � ������:
			
			Pos = oc_parent_concept.m_DescendantNo.AddSorted(No);
			oc_parent_concept.m_Descendant.			Insert(Pos,	conceptID);

		// �������� � ������ ������� �������� ����� � ��� ������ (���� ��� �������>2): 
			int Weight = oc_parent_concept.m_Level - 2;
			if (Weight > 0)
			{
				Pos = oc_concept.m_AncestorNo.AddSorted((int)oc_parent_concept.m_No);
				oc_concept.m_Ancestor.			Insert (Pos, oc_parent_concept.GetObjectID());
				oc_concept.m_AncestorWeight.	Insert (Pos, Weight);
			}

		// ������ ���� �������:
			oc_concept.m_AllAncestor.Add(oc_parent_concept.GetObjectID());
			oc_concept.m_AllAncestorNo.Add((int)oc_parent_concept.m_No);
		

		// ������� ���������� ������ (���� �� ����):
			if (oc_parent_concept.m_Parent != NA)	{
				BX_CHECK_AND_OPEN(oc_parent_concept, oc_parent_concept.m_Parent, OBJ_CLASS_ID_Concept);
			}
			else	{
				break;
			}
		} // end for (;;)

	} // end if (arg.Parent != NA)
//----------------------------------------------------------------------------[]
// ������� ������������� ���������� ��������:
	arg.objID = conceptID;

	pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;
	
	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_PutData                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Concept_PutData(BX_Concept_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))					return BXE_Concept_InvalidObjectID;
	if (!CheckAdminPassword(arg.AdminPassword))						return BXE_BadAdminPassword;
// ���������, �� ���� �� ������ ���� �������� � ��������:
	int nLangs = oc_reg.m_Language.Size();
	if (nLangs != arg.Name.Size())										return BXE_Concept_New_InvalidNameList;
	if	(nLangs != arg.Description.Size())								return BXE_Concept_New_InvalidDescriptionList;

	OC_Concept 			oc_concept;
	oc_concept.Open(arg.objID);

// ����������� ��������� � �������:
	oc_concept.m_Name.			CopyFrom(arg.Name);
	oc_concept.m_Description.	CopyFrom(arg.Description);
	oc_concept.m_ShortName		= arg.ShortName;
	oc_concept.m_Type				= arg.Type;
	oc_concept.m_TypeNo			= arg.TypeNo;

	pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_Enumerate																		[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Concept_Enumerate(BX_Concept_Args& arg)
{
// ������ �� ��������:
	int nLangs = oc_reg.m_Language.Size();
	if (nLangs == 0)																return BXE_NoLanguages;
	if ((arg.objLanguageNo < 0) || (arg.objLanguageNo >= nLangs))	arg.objLanguageNo = 0;
	if (arg.objFirstNo < 0)														arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)										arg.objLastNo		= INT_MAX;

	arg.objNames.Delete();
	arg.objIDs.Delete();
	
	OC_Concept	oc_concept;
	oc_concept.SetIndex_Level();
	
	int i = arg.objFirstNo;
	for (oc_concept.GoFirst();(oc_concept.IsValid()) && (i <= arg.objLastNo); oc_concept.GoNext())
	{
		if (oc_concept.m_Name.Size() != nLangs)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_Enumerate(#%lu): %d=Concept::Name.Size() != Registry::Language.Size(). Skipped.",
				(unsigned long)oc_concept.GetObjectID(), oc_concept.m_Name.Size());
			continue;
		}

		arg.objIDs.Add(oc_concept.GetObjectID());
		arg.objNames.Add(oc_concept.m_Name[arg.objLanguageNo]);

		i++;
	}

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` AddFilteredChilds                                                         []                 
//                                                                            []
// ��������������� ������� ��� BX_Concept_ExtendedEnumerate
void AddFilteredChilds(	const OC_Concept&			oc_concept,
										BX_Concept_Args&	arg,
								const	identifier_arr&	IncludeIDs)
{
	int		i = 0;
	string	OutName;

// ��������, ��� � ���������� �������� ���� ���������� ����:
	if (oc_concept.m_Name.Size() <= arg.objLanguageNo)
	{
		SERVER_DEBUG_ERROR_2 ("AddFilteredChilds(): Language #%d not supported for concept %lu. Skipped.",
			arg.objLanguageNo, (unsigned long)oc_concept.GetObjectID());
		return;
	}

// ������� ���������� ������� � �������� ���������:
	if (arg.Indent) // � ���������
	{
		for (i = 0; i < oc_concept.m_Level; i++) OutName += "_";
	}

	OutName += string(oc_concept.m_Name[arg.objLanguageNo]);

	if (arg.SiteCount > 0)	// � ����������� ������
	{
		int			SiteCount = 0;

		if (arg.VBN != NA)		// ��� ������ VBN
		{
			int VBN_Offset = oc_concept.m_VBN_ID.Find(arg.VBN);
			if (VBN_Offset != -1)
			{
				SiteCount = oc_concept.m_VBN_SiteListSize[VBN_Offset];
			}
		}
		else							// ��� ���� VBN
		{
			for (i = 0; i < oc_concept.m_VBN_ID.Size(); i++) 
			{
				SiteCount += oc_concept.m_VBN_SiteListSize[i];
			}
		}

		string	TempStr;
		TempStr.Format(" (%d)", SiteCount);
		OutName += TempStr;
	}
	
	arg.objIDs.		Add(oc_concept.GetObjectID());
	arg.objNames.	Add(OutName);

// ���� ���� ����� ������� ������, ��
// ���������� ��������� ��� ���� �����, ������� ���� � ���������� ��������� ���������:
	bool bIncludeCheck = IncludeIDs.Size() > 0 ? true : false;
	if ((arg.Level < 0) || (oc_concept.m_Level < arg.Level))
	{
		for (i = 0; i < oc_concept.m_Child.Size(); i++)
		{
			if ((!bIncludeCheck) || (IncludeIDs.Find(oc_concept.m_Child[i]) != -1))
			{
				OC_Concept	oc_child_concept;
				oc_child_concept.Open(oc_concept.m_Child[i]);
				AddFilteredChilds(oc_child_concept, arg, IncludeIDs);
			}
		}
	}

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_ExtendedEnumerate                                              []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT BX_Concept_ExtendedEnumerate(BX_Concept_Args& arg)
{
	int	i;

// ������� �������� ���������:
	arg.objIDs	.Delete();
	arg.objNames.Delete();

// ���� ����������� �������� ��� ��������:
	if (arg.ConceptType.Size() == 0)
		arg.ConceptType.Add("Concept");


// ������� VBN, ���� ��� �������:
	OC_VBN	oc_vbn;
	if (arg.VBN != NA)
	{
		if (OC_Exist(OBJ_CLASS_ID_VBN, arg.VBN))
		{
			oc_vbn.Open(arg.VBN);
			if (ba_IsEmpty(oc_vbn.m_ConceptMask.GetCPtr())) return BX_OK;	// �������,���� � ���������� VBN ��� ���������.
		}
		else
		{
			SERVER_DEBUG_ERROR_1 ("BX_Concept_ExtendedEnumerate(): Invalid VBN iD passed (#%lu). Set to NA.", (unsigned long)arg.VBN);
			arg.VBN = NA;
		}
	}

// ����������� ��������� �����:
	if (oc_reg.m_Language.Size() == 0)						return BXE_NoLanguages;


	if ((arg.objLanguageNo < 0) || (arg.objLanguageNo >= oc_reg.m_Language.Size()))
	{
		if (arg.VBN != NA)
		{
			if (oc_vbn.m_DefaultLanguage != NA)
			{
				if (OC_Exist(OBJ_CLASS_ID_Language, oc_vbn.m_DefaultLanguage))
				{
					OC_Language	oc_language;
					oc_language.Open(oc_vbn.m_DefaultLanguage);
					arg.objLanguageNo = oc_language.m_No;
				}
				else
				{
					SERVER_DEBUG_ERROR_1 ("BX_Concept_ExtendedEnumerate(): Invalid VBN::DefaultLanguage (#%lu). Set to NA.", (unsigned long)oc_vbn.m_DefaultLanguage);
					oc_vbn.m_DefaultLanguage = NA;
				}
			}
			else
			{
				arg.objLanguageNo = 0;
			}
		}
		else
		{
			arg.objLanguageNo = 0;
		}
	}

	IF_CACHED_ARGS_7_RETURN (	1000,
										arg.Indent,
										arg.Level,
										arg.ConceptType,
										arg.VBN,
										arg.objLanguageNo,
										arg.SiteCount, 
										pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate,
										BX_OK);
//----------------------------------------------------------------------------[] 
	identifier_arr	ParentID;
	identifier_arr	VBN_Concept;

	OC_Concept	oc_concept;
	oc_concept.SetIndex_Type_Level_ShortName();

	key_arr ka;

	for (i = 0; i < arg.ConceptType.Size(); i++)
	{
		ka.Init();
		ka += arg.ConceptType[i];
	// ���� ���� ����� �����������, �� �������� ��� ID:
		if (oc_concept.Find(ka)) {
			ParentID.Add(oc_concept.GetObjectID());
		}
	}

	if (arg.VBN != NA) // VBN �������� - ���� �������� VBN.	
	{
		_BitsToIDs(VBN_Concept, oc_vbn.m_ConceptMask);
		VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, VBN_Concept);
	}

	
//----------------------------------------------------------------------------[] 
// 
	for (i = 0; i < ParentID.Size(); i++)
	{
		oc_concept.Open(ParentID[i]);
	// �������� �� �������:
		if ((arg.Level >= 0) && (oc_concept.m_Level > arg.Level)) // �� �������� �� ������.
			continue;
	// �������� �� VBN:
		if (arg.VBN != NA)
		{
			if (VBN_Concept.Find(ParentID[i]) == -1)					// �� �������� �� VBN.
				continue;
		}
	// �������� ����� "� �������":
		AddFilteredChilds(oc_concept, arg , VBN_Concept);			
	}

//----------------------------------------------------------------------------[] 
// ���������� ���������� ���������� �������:
	CACHE_STORE_RESULT_2 (arg.objIDs, arg.objNames);
	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_GetData                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_Concept_GetData(BX_Concept_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))
	{
		arg.Parent	= NA;
		arg.Level	= -1;
		arg.No		= -1;
		arg.Name.Delete();
		arg.Description.Delete();
		return BXE_Concept_InvalidObjectID;
	}

	OC_Concept			oc_concept;
	oc_concept.Open(arg.objID);

	arg.Parent		= oc_concept.m_Parent					;
	arg.Level		= oc_concept.m_Level						;
	arg.No			= oc_concept.m_No							;
	arg.Name			= oc_concept.m_Name.GetCPtr()			;
	arg.Description= oc_concept.m_Description.GetCPtr();
	arg.ShortName	= oc_concept.m_ShortName				;
	arg.Type			= oc_concept.m_Type						;
	arg.TypeNo		= oc_concept.m_TypeNo					;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_Delete                                                         []
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT 
BX_Concept_Delete(BX_Concept_Args& arg)
{
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))				return BXE_Concept_InvalidObjectID;
	if (!CheckAdminPassword(arg.AdminPassword))					return BXE_BadAdminPassword;
	
	OC_Concept			oc_concept;
	oc_concept.Open(arg.objID);

//----------------------------------------------------------------------------[]
// ������� ����� (����������):
	while (oc_concept.m_Child.Size() > 0)
	{
		BX_Concept_Args		concept_args;

		concept_args.objID			= oc_concept.m_Child[0];
		concept_args.AdminPassword = arg.AdminPassword;

		BX_ASSERT_RETURN(BX_Concept_Delete(concept_args));
	}
	
//----------------------------------------------------------------------------[]
// �������� ������� ������:
	OC_SiteList			oc_site_list;

	SERVER_DEBUG_ASSERT_RETURN(
		oc_concept.m_VBN_ID.Size() == oc_concept.m_VBN_SiteList.Size(),
		"BX_Concept_Delete(): Unequal sizes of Concept::VBN_ID and Concept::VBN_SiteList.",
		BX_SYSTEM_ERROR);

	for (int i = 0; i < oc_concept.m_VBN_SiteList.Size(); i++)
	{
		oc_site_list.Delete(oc_concept.m_VBN_SiteList[i]);
		oc_concept.m_VBN_SiteList	[i]	= NA;
		oc_concept.m_VBN_ID			[i]	= NA;
	}
//----------------------------------------------------------------------------[]
// ������� ���� �� ������ Descendant � DescendantNo ���������
	int			Pos		= -1;
	
	identifier	idParent = oc_concept.m_Parent;	// ��������� ��������.
	OC_Concept	oc_parent_concept;

// �� ���� �������:
	while(idParent != NA)
	{
	// ��������� ������ ��������-������:
		BX_CHECK_AND_OPEN(oc_parent_concept, idParent, OBJ_CLASS_ID_Concept);

	// ������ ���� ID � ������ �������� � ������:
		Pos = oc_parent_concept.m_Descendant.Find(arg.objID);

	// �� ������� - ������:
		if (Pos < 0)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Can't find concept #%lu in descendant list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_Descendant.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_Descendant.Find(arg.objID) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Duplicate concept #%lu in descendant list of concept #%lu. Deleted anyway!",
					arg.objID, idParent);
				DELETE_FROM_ARRAY(oc_parent_concept.m_Descendant, arg.objID);
			}
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	// ������ ���� ����� � ������ ������� �������� � ������:
		Pos = oc_parent_concept.m_DescendantNo.Find(int(oc_concept.m_No));

	// �� ������� - ������:
		if (Pos < 0)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Can't find No of concept #%lu in DescendantNo list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_DescendantNo.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_DescendantNo.Find(oc_concept.m_No) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Duplicate No of concept #%lu in DescendantNo list of concept #%lu. Deleted anyway!",
					arg.objID, idParent);
				DELETE_FROM_ARRAY(oc_parent_concept.m_DescendantNo, oc_concept.m_No);
			}
		}

	// � ���������� ������:
		idParent = oc_parent_concept.m_Parent;
	} 
//----------------------------------------------------------------------------[]
// ������� ���� �� ������ Child � ChildNo ��������:

	// ��������� ������� ��������:
		idParent = oc_concept.m_Parent;
	if (idParent != NA)
	{
		oc_parent_concept.Open(idParent);

	// ������ ���� ID � ������ ����� � ��������:
		Pos = oc_parent_concept.m_Child.Find(arg.objID);

	// �� ������� - ������:
		if (Pos < 0)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Can't find concept #%lu in child list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_Child.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_Child.Find(arg.objID) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Duplicate concept #%lu in child list of concept #%lu. Deleted anyway!",
					arg.objID, idParent);
				DELETE_FROM_ARRAY(oc_parent_concept.m_Child, arg.objID);
			}
		}
	//- - - - - - - - - - - - - - - - - - - - - - - - - -[]
	// ������ ���� ����� � ������ ������� ����� � ��������:
		Pos = oc_parent_concept.m_ChildNo.Find(int(oc_concept.m_No));

	// �� ������� - ������:
		if (Pos < 0)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Can't find No of concept #%lu in ChildNo list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_ChildNo.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_ChildNo.Find(oc_concept.m_No) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("BX_Concept_Delete(): Duplicate No of concept #%lu in ChildNo list of concept #%lu. Deleted anyway!",
					arg.objID, idParent);
				DELETE_FROM_ARRAY(oc_parent_concept.m_ChildNo, oc_concept.m_No);
			}
		}
	}
//----------------------------------------------------------------------------[]
// ������� ������ � �������:
	Pos = oc_reg.m_ConceptID_Sorted.Find(arg.objID, true);
	if (Pos >= 0)
	{
		oc_reg.m_ConceptID_Sorted.Del(Pos);
		oc_reg.m_ConceptNo_SortID.Del(Pos);
	}
	else
	{
		SERVER_DEBUG_ERROR_1 ("BX_Concept_Delete(): Can't find concept ID #%lu in registry.",
			arg.objID);
	}

	Pos = oc_reg.m_ConceptID_SortNo.Find(arg.objID, true);
	if (Pos >= 0)
	{
		oc_reg.m_ConceptID_SortNo		[Pos] = NA;	// ������� ��������� ��������
		oc_reg.m_ConceptParent_SortNo	[Pos] = -1;	// ������� ��������� ��������
		oc_reg.m_ConceptType_SortNo	[Pos] = -1;	// ������� ��������� ��������
		oc_reg.m_ConceptLevel_SortNo	[Pos] = -1;	// ������� ��������� ��������
	}
	
	
//	oc_reg.m_ConceptNo.Del(Pos);

// ������� ����:
	oc_concept.Delete(arg.objID);

	pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_DeleteSite                                                     [] 
[]                                                                            []
[]____________________________________________________________________________[]
*/
// ������� id ����� �� ������� ������ ���� idVBN ��� ��������� �� ������� conceptIDs.
BX_RESULT
BX_Concept_DeleteSite(const identifier_arr& idConcept, identifier idSite, identifier idVBN)
{
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_Site, idSite),
		"BX_Concept_DeleteSite(): Invalid site ID.",
		BX_SYSTEM_ERROR);

	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_VBN, idVBN),
		"BX_Concept_DeleteSite(): Invalid VBN ID.",
		BX_SYSTEM_ERROR);

// ������������� ����������� ������ �����������
	pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

	int			nConcept	= idConcept.Size();
	int			sitePos	= -1;
	int			vbnPos	= -1;
	int			i			= -1;

	OC_SiteList		oc_site_list;
	OC_Concept		oc_concept;

//----------------------------------------------------------------------------[] 
// ��� ���� ��������� ���������:
	for (i = 0; i < nConcept; i++)
	{
	// �������� ������ ��������:
		BX_CHECK_AND_OPEN(oc_concept, idConcept[i], OBJ_CLASS_ID_Concept);

		if (oc_concept.m_VBN_ID.Size() != oc_concept.m_VBN_SiteList.Size())
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_DeleteSite(): Unequal sizes of Concept::VBN_ID and Concept::VBN_SiteList for Concept #%lu and site #%lu. Skipped",
				idConcept[i], idSite);
			continue;
		}

	// ����� ������ ��������� VBN � ������ ���������:
		vbnPos = oc_concept.m_VBN_ID.Find(idVBN, true);
		if (vbnPos == -1)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_DeleteSite(): Can't found vbn ID in Concept::VBN_ID[] for Concept #%lu and site #%lu. Skipped",
				idConcept[i], idSite);
			continue;
		}

	// ������� ������ ������:
		BX_CHECK_AND_OPEN(oc_site_list, oc_concept.m_VBN_SiteList[vbnPos], OBJ_CLASS_ID_SiteList);

	// ���� ���� � ������:
		sitePos = oc_site_list.m_Site.Find(idSite, true);
		if (sitePos == -1)
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_DeleteSite(): Can't found site ID in site list for Concept #%lu and site #%lu. Skipped",
				idConcept[i], idSite);
			continue;
		}
	// ������� ���� �� ������:
		oc_site_list.m_Site.Del(sitePos);

		SERVER_DEBUG_ASSERT_RETURN(
			oc_site_list.m_Site.Find(idSite, true) == -1,
			"BX_Concept_DeleteSite(): Double reference to site in sitelist.",
			BX_SYSTEM_ERROR);

	// ���� ������ ����, �� ������ ��� ������ � ������� �� VBN:
		int nListSize = oc_site_list.m_Site.Size();
		if (nListSize == 0)
		{
			oc_site_list.Delete();
			oc_concept.m_VBN_SiteList.Del(vbnPos);
			oc_concept.m_VBN_SiteListSize.Del(vbnPos);
			oc_concept.m_VBN_ID.Del(vbnPos);
		}
	// ���� ������ �� ����, �������� ��� ������ � VBN_SiteListSize
		else
		{
			oc_concept.m_VBN_SiteListSize[vbnPos] = nListSize;
		}

	}	// end for(i=...

	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_AddSite                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/

// ��������� id ����� � ������ ������ �� ���� idVBN ��� �������� �� ������� conceptIDs.
BX_RESULT
BX_Concept_AddSite(const identifier_arr& idConcept, identifier idSite, identifier idVBN)
{
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_Site, idSite),
		"BX_Concept_AddSite(): Invalid site ID.",
		BX_SYSTEM_ERROR);
	
	SERVER_DEBUG_ASSERT_RETURN(
		OC_Exist(OBJ_CLASS_ID_VBN, idVBN),
		"BX_Concept_AddSite(): Invalid VBN ID.",
		BX_SYSTEM_ERROR);

// ������������� ����������� ������ �����������
	pBX_SingleObject->CACHE_UPDATE_NO_BX_Concept_ExtendedEnumerate++;

	int				nConcept	= idConcept.Size();
	int				vbnPos	= -1;

	OC_SiteList		oc_site_list;
	OC_Concept		oc_concept;

//----------------------------------------------------------------------------[] 
// ��� ���� ��������� ���������:
	for (int i = 0; i < nConcept; i++)
	{
	// �������� ������ ��������:
		BX_CHECK_AND_OPEN(oc_concept, idConcept[i], OBJ_CLASS_ID_Concept);

		if (oc_concept.m_VBN_ID.Size() != oc_concept.m_VBN_SiteList.Size())
		{
			SERVER_DEBUG_ERROR_2 ("BX_Concept_AddSite(): Unequal sizes of Concept::VBN_ID and Concept::VBN_SiteListfor Concept #%lu and Site #%lu.",
				idConcept[i], idSite);
			continue;
		}

	// ����� ������ ��������� VBN ������ ���������:
		vbnPos = oc_concept.m_VBN_ID.Find(idVBN, true);
	// ���� �� �����, �� �������� ������ ������ � ������� ��� � �������� ������ � VBN:
		if (vbnPos == -1)
		{
			oc_site_list.New();
			vbnPos = oc_concept.m_VBN_ID.	AddSorted(idVBN);
			oc_concept.m_VBN_SiteList.		Insert(vbnPos, oc_site_list.GetObjectID());
			oc_concept.m_VBN_SiteListSize.Insert(vbnPos, 0);
		}
	// ���� �����, �� �������� ������ ������:
		else
		{
			BX_CHECK_AND_OPEN(oc_site_list, oc_concept.m_VBN_SiteList[vbnPos], OBJ_CLASS_ID_SiteList);

		// ������ ������ �� ������ ���� ������ (����� �� ������ ���� ��������� � BX_Concept_DeleteSite()):
			if (oc_site_list.m_Site.Size() == 0)
			{
				SERVER_DEBUG_ERROR_2 ("BX_Concept_AddSite(): Empty SiteList opened - it should have been deleted by BX_Concept_DeleteSite()! Concept #%lu, site #%lu.",
					idConcept[i], idSite);
			}
		}
		
	// ������� � ������ ��������� ����:
		oc_site_list.m_Site.AddSorted(idSite);
	
	// ��������� ����� ������ ������ ������:
		oc_concept.m_VBN_SiteListSize[vbnPos] = oc_site_list.m_Site.Size();

	} // end for(i=

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ExpandConcept                                                             []           
//                                                                            []
// ��� ������� ��������� � ������ (CPtr<id>) concept_arr ��� �����������		[]
// ��������� � �� ���������.																	[]
BX_RESULT
ExpandConcept(identifier_arr &concept_arr)
{
	if (concept_arr.Size() == 0)		return BX_OK;

	OC_Concept			oc_concept;
	int					i = 0, InitialSize = concept_arr.Size();

	for (i = 0; i < InitialSize; i++)
	{
		if (!OC_Exist(OBJ_CLASS_ID_Concept, concept_arr[i]))
		{
			SERVER_DEBUG_ERROR_1 ("ExpandConcept(): Bad concept_arr[i]=#%lu. It's been Deleted.", (unsigned long)concept_arr[i]);
			concept_arr.Del(i);
			i--;
			continue;
		}
		
		oc_concept.Open(concept_arr[i]);
		concept_arr.AddFrom(oc_concept.m_Descendant.GetPtr(), oc_concept.m_Descendant.GetSize());

	} // end for (i

	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ExpandWithParentConcepts                                                  []
//                                                                            []
// ��������� � concept_arr �������������� ���������-������� (� ������� > 2)
// ���������� ������������ � ��� ���������. ������������ ��������� ���������.
BX_RESULT
ExpandWithParentConcepts(identifier_arr &concept_arr)
{
	if (concept_arr.Size() == 0)		return BX_OK;

	OC_Concept		oc_concept;
	int				i = 0, j = 0, InitialSize = concept_arr.Size();

	byte_arr			ParentBits;

	for (i = 0; i < InitialSize; i++) 
	{
		oc_concept.Open(concept_arr[i]);
		SetBit(ParentBits, oc_concept.m_No);

		for (j = 0; j < oc_concept.m_AncestorNo.Size(); j++) 
			SetBit(ParentBits, oc_concept.m_AncestorNo[j]);
	}

	_BitsToIDs( concept_arr, ParentBits);

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_Concept_GetPackedWeights                                               []                           
//                                                                            []
// ����: �������������� ���������
// �����:������������� ���� ���������.
BX_RESULT
BX_Concept_GetPackedWeights (const identifier_arr	&ConceptIDs, int_arr &ConceptRate)
{
	int_arr		AddedConceptNo;

	ConceptRate.Delete();
	
	OC_Concept	oc_concept;

	int			InitialSize = ConceptIDs.Size();
	int			i, j, Weight;
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	for (i = 0; i < InitialSize; i++)
	{
	// ������� ������� � ���� �������:
		if (!OC_Exist(OBJ_CLASS_ID_Concept, ConceptIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("BX_Concept_GetPackedWeights(): Invalid concept ID#%lu. Skipped.", ConceptIDs[i]);
			continue;
		}

		oc_concept.Open(ConceptIDs[i]);

	// �������� ��� �������:
		Weight = oc_concept.m_Level - 2;
		if (Weight < 1)
		{
			SERVER_DEBUG_ERROR_1 ("BX_Concept_GetPackedWeights(): �oncept ID#%lu has Level<3. Skipped.", ConceptIDs[i]);
			continue;
		}

	// ������� ���� �������:
		ConceptPack(ConceptRate,
						AddedConceptNo,
						(int)oc_concept.m_No,
						Weight);

	// ������� ���� �������:
		for (j = 0; j < oc_concept.m_Ancestor.Size(); j++) 
		{
			ConceptPack(ConceptRate,
							AddedConceptNo,
							oc_concept.m_AncestorNo[j],
							oc_concept.m_AncestorWeight[j]);
		}

	} // end for

// ����������� ������:
	ConceptRate.Sort();

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ConceptPack                                                               []           
//                                                                            []
void
ConceptPack(int_arr&					ConceptRate,
				int_arr&					AddedConceptNo,
				int						No,
				int						Increment)
{
// ���������, ���� �� ��� ����� ������� � ������� ?
	int	Index = AddedConceptNo.Find(No);

// ���� ��� - ������� ��� ���� ������ � ����� � �������:
	if (Index < 0) 
	{
		ConceptRate.Add((No << 16) | Increment);
		AddedConceptNo.Add(No);
	}
	else
	{
	// ����� �������� ������������� � ������� �����:
		int NewRate = (ConceptRate[Index]+Increment) & 0x0000ffff;	
	// �������� �� ������:
		ConceptRate[Index] = (No << 16) | NewRate;
	}

	return;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` ViewerParamsToConcepts                                                    []                      
//                                                                            []
// ���������� ����� �������� ���� ConceptType 3�� ������ � �������������		[]
// ViewerParam, �������� ����� ������� � ������ �������������.						[]
// ���������� -1 � ������ ���������� ���� ConceptType ��� � ������ ������		[]
// �������� ��������.																			[]

int ViewerParamsToConcepts(const char * ConceptType, const string& ViewerParam)
{
	OC_Concept	oc_concept;
	oc_concept.SetIndex_Type_Level_ShortName();
	key_arr	ka;
	ka += string(ConceptType);
	ka += 3;
	ka += ViewerParam;
// ���� ��� ���� ����� �������, ������� ��� �����:
	if (oc_concept.Find(ka))
	{
		return (int)oc_concept.m_No;
	}
// ���� ������ �������� ���, �� ����� ������������ �������:
	ka.Init();
	ka += string(ConceptType);
	ka += 2;
	if (oc_concept.Find(ka))
	{
	// �������� ������ ���� ������ ����:
		if (oc_concept.GetIndexTotalNum(ka) != 1)
		{
			SERVER_DEBUG_ERROR_2 (
			"ViewerParamsToConcepts(): Multiple or no parent found for concept '%s' of type '%s'.",
				ViewerParam.c_str(), ConceptType);
			return -1;
		}
	// ������������� ��������� ��� �������� ��������:
		BX_Concept_Args arg;

		GetAdminPassword(arg.AdminPassword);
		arg.Parent			= oc_concept.GetObjectID();
		arg.Type				= oc_concept.m_Type;
		arg.TypeNo			= oc_concept.m_TypeNo;
		arg.ShortName		= ViewerParam;

		for (int i = 0; i < oc_reg.m_Language.Size(); i++)
		{
			arg.Name.Add(ViewerParam);
			arg.Description.Add("");
		}

		if (BX_Concept_New(arg) != BX_OK)
		{
		// ������ �������� ��������:
			SERVER_DEBUG_ERROR_2 (
				"ViewerParamsToConcepts(): Error creating concept '%s' of type '%s'.",
				ViewerParam.c_str(), ConceptType);
			return -1;
		}
		else
		{
		// ������� ������ �������, ������ ��� ����� �� �������:
			return oc_reg.m_ConceptNo_SortID[oc_reg.m_ConceptID_Sorted.Find(arg.objID, true)];
		}

	}

// ������������ ������� �� ������ - ������ ������� ������:
	SERVER_DEBUG_ERROR_2 (
	"ViewerParamsToConcepts(): No parent found for concept '%s' of type '%s'.",
		ViewerParam.c_str(), ConceptType);

	return -1;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_ConceptRate_Find                                                       []                
//                                                                            []
// ���������� ������ �������� ������������� �� ������� RateArr,
// ���������������� ������ No, ��� -1, ���� ������ ���.
int
BX_ConceptRate_Find(int No, const int_arr& RateArr, int StartNo)
{
	const int *pRateArr = RateArr.GetPtr();
	int	nSize = RateArr.Size();
	int	RateTemplate = No << 16;

	if (StartNo < 0)
		StartNo = 0;

	for (int i = StartNo; i < nSize; i++)
	{
		if (pRateArr[i] >= RateTemplate)
		{
			if ((pRateArr[i]>>16) == No) {
				return i;
			}
		}
	}

	return -1;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` Concept_IncreaseRate                                                      []                    
//                                                                            []
// ����������� �������� �������������, ���������������� �������� � �������		[]
// No, �� �������� Increment.																	[]
// ��� ������������� ���� ����� �����������.
// ���������� ������ ��� ����� �������� � �������������.
int
ConceptRate_Increase(int No, int Increment, int_arr& RateArr)
{
	int Index			= -1;
	int RateTemplate	= No << 16;

	if ((Index = BX_ConceptRate_Find(No, RateArr)) == -1)
	{
		Index = RateArr.InsertSorted(RateTemplate);
	}

	RateArr[Index] = RateTemplate + ((RateArr[Index]+Increment) & 0xffff);

	return Index;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` Concept_PrepareForPrinting                                                []                          
//                                                                            []
BX_RESULT
BX_Concept_PrepareForPrinting(const int_arr&	RateArr,
										const int_arr&	TypeArr,
										int				LanguageNo,
										string_arr&		Names,
										int_arr&			Rates,
										int_arr&			Levels
										)
{
	Names. Erase();
	Rates. Erase();
	Levels.Erase();

	if (LanguageNo < 0) {
		LanguageNo = 0;
	}
	if (oc_reg.m_Language.Size() < 1) {
		return BXE_NoLanguages;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

	const int		MaxNo			= oc_reg.m_ConceptParent_SortNo.Size()-1;
	int				RateArrSize	= RateArr.Size();
	const int*		pRateArr		= RateArr.GetPtr();
	int				TypeArrSize	= TypeArr.Size();
	int				No;
	int				ParentNo;
	int				Rate;
	int				i;
	int				j;
	OC_Concept		oc_concept;
	oc_concept.SetIndex_No();
	key_arr			ka;
//----------------------------------------------------------------------------[]
// ������������ ������ �������, ��������� �� ������� ���� �������, ��������� 
// � �������������, � �� ���������:
	int_arr			RateWithParents;

	for (i = 0; i < RateArrSize; i++)
	{
		No = pRateArr[i] >> 16;
		if (No < MaxNo)
		{
			if ((TypeArrSize==0) || (TypeArr.Find(oc_reg.m_ConceptType_SortNo[No]) >= 0))
			{
				RateWithParents.InsertSorted(pRateArr[i]);

			// ������� ��������� �� �������� ������ � ����:
				ParentNo = oc_reg.m_ConceptParent_SortNo[No];
				while (oc_reg.m_ConceptLevel_SortNo[ParentNo] >= 2)
				{
				// ���� ����� �������� ��� � �������������:
					if ((BX_ConceptRate_Find(ParentNo, RateArr) < 0) && 
						 (BX_ConceptRate_Find(ParentNo, RateWithParents) < 0)) {
						RateWithParents.InsertSorted(ParentNo << 16);
					}
				// � ���������� ������:
					ParentNo = oc_reg.m_ConceptParent_SortNo[ParentNo];
				}
			}
		}
	}
//----------------------------------------------------------------------------[]
// ��� ������� �������� �� ����������� ������� ...

	string_arr			OrderStr;
	string				TmpStr;
	int					RateWithParentsSize	= RateWithParents.Size();
	const		int*		pRateWithParents		= RateWithParents.GetPtr();
	const		int		MAX_CONCEPT_LEVEL		= 12;	// ����. �������������� ���� �������� �������
	const		int		MAX_CONCEPT_NO_DIGIT = 5;	// 10^(��� �����) - �������������� ���� �������� �����
	static	char		StrBuf[32];


	for (i = 0; i < RateWithParentsSize; i++)
	{
		No		= pRateWithParents[i] >> 16;
		Rate	= pRateWithParents[i] & 0xffff;

		ka.Init();
		ka += No;
		if (oc_concept.Find(ka))
		{
			TmpStr.Erase();
			int LevelCount = 0;
		// ��������� ������ �������:
			for (j = oc_concept.m_AllAncestorNo.Size()-1; j >= 0 ; j--)
			{
				sprintf(StrBuf, "%0*d", MAX_CONCEPT_NO_DIGIT, (int)oc_concept.m_AllAncestorNo[j]);
				TmpStr += StrBuf;
				LevelCount++;
			}
		// ��������� ����������� �����:
			sprintf(StrBuf, "%0*d", MAX_CONCEPT_NO_DIGIT, No);
			TmpStr += StrBuf;
			LevelCount++;

			SERVER_DEBUG_ASSERT_RETURN(
				LevelCount <= MAX_CONCEPT_LEVEL,
				"BX_Concept_PrepareForPrinting(): LevelCount > MAX_CONCEPT_LEVEL !!! What fucker created such number of concept levels ?!",
				BX_SYSTEM_ERROR);

		// ������ ������ �� MAX_CONCEPT_LEVEL:
			while (LevelCount < MAX_CONCEPT_LEVEL)
			{
				sprintf(StrBuf, "%0*d", MAX_CONCEPT_NO_DIGIT, 0);
				TmpStr += StrBuf;
				LevelCount++;
			}
		//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
		// ������� ������ � ���������� ������� � ������� ������ �������:
			int Pos = OrderStr.InsertSorted(TmpStr);
			
			if (oc_concept.m_Name.Size() > LanguageNo) {
				Names.Insert(Pos, oc_concept.m_Name[LanguageNo]);
			}
			else	{
				Names.Insert(Pos, oc_concept.m_Name[0]);
			}

			Levels.Insert(Pos, int(oc_concept.m_Level));
			Rates.Insert(Pos, Rate);
		} // end if (oc_concept.Find(ka))
	} // end for (i 
//----------------------------------------------------------------------------[]
#if 0  //{ AlexV
	static char CharBuf[1024]; 

	puts("\n-----------------------------------------------------------\n\n");

	for (i = 0; i < OrderStr.Size(); i++)
	{
		strncpy(CharBuf, Names[i].c_str(), 1000);
		printf("%s - %s\n", OrderStr[i].c_str(), win_2_dos(CharBuf));
	}
		
	puts("\n-----------------------------------------------------------\n\n");
#endif //}

	return BX_OK;	
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_TypeEnumerate                                                  []                        
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Concept_TypeEnumerate(BX_Concept_Args& arg)
{
	arg.objNums.Erase();
	arg.objNames.Erase();

	OC_Concept		oc_concept;
	oc_concept.SetIndex_TypeNo();

	for (oc_concept.GoFirst(); oc_concept.IsValid(); oc_concept.GoNextUnique())
	{
		arg.objNums.Add(oc_concept.m_TypeNo);
		arg.objNames.Add(oc_concept.m_Type);
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_FilterType                                                     []                     
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Concept_FilterType(int_arr& CR, const int_arr& Types)
{
	int		i;
	int		No;
	bool		bDeleteIt;

	if (Types.Size() == 0) {
		return BX_OK;
	}
	
// ���������� ���������:
	int		MaxNo = oc_reg.m_ConceptType_SortNo.Size();

// ���� ��������:
	for (i = 0; i < CR.Size(); i++)
	{
		No				= CR[i] >> 16;
	// �������, ���� ���, ��������������� ����� ������ ���� � Types ���
	// ���� ����� ������ (������ �������������):
		bDeleteIt	= (No >= MaxNo) || (Types.Find(oc_reg.m_ConceptType_SortNo[No]) != -1);
		
		if (bDeleteIt)
		{
			CR.Del(i);
			i--;
		}
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_SetFilter                                                      []                    
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Concept_SetFilter(BX_Concept_Args& arg)
{
	OC_Concept	oc_concept;
	oc_concept.SetIndex_Type_Level_ShortName();

	key_arr		ka;
	int			i;

	int_arr		Types;

	for (i = 0; i < arg.ConceptType.Size(); i++)
	{
		ka.Init();
		ka += arg.ConceptType[i];

		if (oc_concept.Find(ka)) {
			Types.Add(oc_concept.m_TypeNo);
		}
		else	{
			arg.ConceptType.Del(i);
			i--;
		}
	}

	if (Types.GetSize() > 0) {
		oc_reg.m_ReservedInt1 = Types;
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Concept_GetFilter                                                      []                    
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Concept_GetFilter(BX_Concept_Args& arg)
{
	OC_Concept	oc_concept;
	oc_concept.SetIndex_TypeNo();

	key_arr		ka;
	int			i;

	arg.ConceptType.Erase();

	for (i = 0; i < oc_reg.m_ReservedInt1.Size(); i++)
	{
		ka.Init();
		ka += int(oc_reg.m_ReservedInt1[i]);

		if (oc_concept.Find(ka)) {
			arg.ConceptType.Add(string(oc_concept.m_Type));
		}
		else	{
			SERVER_DEBUG_ERROR_1 ("BX_Concept_GetFilter(): Unknown oncept type #%d detected.", int(oc_reg.m_ReservedInt1[i]));
		}
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/

