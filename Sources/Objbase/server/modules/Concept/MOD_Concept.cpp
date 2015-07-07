#define USES_SingleObject_h
#define USES_PicklockPassword_h

#define USES_OC_Registry
#define USES_OC_Concept

#define USES_MOD_Concept


#include "./../../kernel/config.h"
#include MOD_PATH_INCLUDE_H
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
const byte	BitMask		[8] = {1,   2,   4,   8,   16,  32,  64,  128};
const byte	BitMaskNot	[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//----------------------------------------------------------------------------[] 



//______________________________________________________________________________
//                                                                            []
//` �������� ������������� �������� �� ��� �����                              []
//                                                                            []
identifier GetConceptID (const char * Name, const char * Type, bool JustCheck)
{
	DEBUG_STACK_NAME (GetConceptID);

	OC_Concept oc_concept;
	oc_concept.SetIndex_Name ();
	key_arr ka;
	ka += Name;
	if (oc_concept.Find (ka))
	{
		do
		{
			if (string(oc_concept.m_Type).Find (Type)==0)
			{
				return oc_concept.GetObjectID ();
			}
		} while (oc_concept.GoNextSame (&ka));
	}

	if (!JustCheck)
	{
		SERVER_DEBUG_ERROR_1 ("������� � ������ [%s] �� ������", Name);
	}
	
	return NA;
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` �������� ��� ��������																		[]
//                                                                            []
bool GetConceptName (identifier objID, string& objName)
{
	DEBUG_STACK_NAME (GetConceptName);
	objName = "[Error getting concept name]";

	if (!OC_Exist (OBJ_CLASS_ID_Concept, objID))
	{
		SERVER_DEBUG_ERROR_1 ("���������� ������� [%d]", objID);
		return false;
	}

	objName = OC_Concept(objID).m_Name;
	
	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` �������� ������ ��� ��������, �� ������ nLevel	������������					[]
//                                                                            []
bool GetConceptFullName (identifier objID, string& objName, int nLevel, const char* sDelimiter)
{
	DEBUG_STACK_NAME (GetConceptFullName);
	string_arr	Names;
	string		Name;

	objName = "";

	for (int l=0; l<10000; l++)
	{
		if (!GetConceptName (objID, Name))
		{
			objName = "";
			return false;
		}
		Names += Name;
		if (OC_Concept(objID).m_Level <= nLevel)
		{
			break;
		}
		objID =  OC_Concept(objID).m_Parent;
	}

	for (int i=Names.Size()-1; i>=0; i--)
	{
		objName += Names[i];
		if (i>0)
			objName += sDelimiter;
	}	

	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ������� ����� ������� � ��������� ������                                  []
//                                                                            []
bool ConceptHasDescendantWithName (identifier FeodID, const char * descName)
{
	OC_Concept oc_feod;
	oc_feod.Open (FeodID);
	SERVER_DEBUG_ASSERT_RETURN (oc_feod.IsValid (), "��������� ������� �� ����������", false);
	
	identifier_arr FeodDescendants;
	oc_feod.m_Descendant.CopyTo (FeodDescendants);
	
	FOR_EACH_ITEM_EVAL (FeodDescendants, 
		{
			if (OC_Concept(FeodDescendants[i]).m_Name == descName)
			{
				return true;
			}
		}
	);
	
	return false;
}
//____________________________________________________________________________[]


 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_New                                                           []
[]                                                                            []
[]____________________________________________________________________________[]
*/

ERR_RESULT
MOD_Concept_New(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_New);

	if (!CheckPicklockPassword(arg.PicklockPassword))
		return ERR_BadPicklockPassword;
	
// ���������, �������� �� �����������:
	if ((arg.Type.Size() < 1) || (arg.TypeNo < 0))
		return ERR_Concept_New_InvalidTypeInfo;

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
	if (Pos != oc_reg.m_ConceptNo_SortID.Size()) return ERR_SYSTEM_ERROR;

	Pos = oc_reg.m_ConceptID_SortNo.Size();
	if (Pos != oc_reg.m_ConceptParent_SortNo.Size()) return ERR_SYSTEM_ERROR;
	if (Pos != oc_reg.m_ConceptType_SortNo.Size()) return ERR_SYSTEM_ERROR;
//----------------------------------------------------------------------------[]
// ��������� ������������� �������� / �������������� �����, 
// ��������� ���������� �����:
	if (arg.ParentID != NA)	// �� ������.
	{
		if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.ParentID)) return ERR_Concept_New_InvalidParentID;

	// ������� ��������� ��������� �����:
		No = oc_reg.m_ConceptID_SortNo.Size();

	// ��������, ��� ���� ����� ������������� �� �����:
		ka.Init();
		ka += No;
		oc_concept.SetIndex_No();
		SERVER_DEBUG_ASSERT_RETURN(
			!oc_concept.Find(ka),
			"MOD_Concept_New(): Numerating error!",
			ERR_SYSTEM_ERROR);

	// �������� ������ ������������� ��������:
		oc_parent_concept.Open(arg.ParentID);

	// �������� ������� ������������ ��������:
		Level = oc_parent_concept.m_Level + 1;
	}
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	else	// ������.
	{
	// ������ ������ ����������� ������:
		oc_concept.SetIndex_Level();
		if (oc_concept.GetTotalNum() != 0)				return ERR_Concept_New_RootAlreadyExists;
		if (oc_reg.m_ConceptID_SortNo.Size() != 0)	return ERR_Concept_New_RootAlreadyExists;

	// ������ ������ ����� ����� 0:
		No		= 0;

	// ������ ������ ����� ������� 0:
		Level = 0;
	}
//----------------------------------------------------------------------------[]
// �������� ��������:
	OBJ_CREATE_AND_CHECK(oc_concept);

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
		arg.ParentID != NA ? (int)oc_parent_concept.m_No : -1);
	oc_reg.m_ConceptType_SortNo.		Add(arg.TypeNo);
	oc_reg.m_ConceptLevel_SortNo.		Add(Level);

// �������� �������� � �������� �� �������������� ������:
	oc_concept.m_Name				= arg.Name;
	oc_concept.m_Description	= arg.Description;

// �������� ��������� �����������:
	oc_concept.m_Type				= arg.Type;
	oc_concept.m_TypeNo			= arg.TypeNo;
//	oc_concept.m_Mask				= (arg.TypeNo<<11) | (No & 0x7ff);

// ��������� � ���� ������������ �������:
	oc_concept.m_Parent			= arg.ParentID;
//----------------------------------------------------------------------------[]
// ���������� �����, ��������� � �����������:
	if	(arg.ParentID != NA)
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
				OBJ_CHECK_AND_OPEN(oc_parent_concept, oc_parent_concept.m_Parent, OBJ_CLASS_ID_Concept);
			}
			else	{
				break;
			}
		} // end for (;;)

	} // end if (arg.ParentID != NA)
//----------------------------------------------------------------------------[]
// ������� ������������� ���������� ��������:
	arg.objID = conceptID;

//	pBX_SingleObject->CACHE_UPDATE_NO_MOD_Concept_ExtendedEnumerate++;
	
	return ERR_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_PutData                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT
MOD_Concept_PutData(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_PutData);
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))					return ERR_BadID;
	if (!CheckPicklockPassword(arg.PicklockPassword))				return ERR_BadPicklockPassword;
	OC_Concept 			oc_concept;
	oc_concept.Open(arg.objID);

// ����������� ��������� � �������:
	oc_concept.m_Name				=	arg.Name;
	oc_concept.m_Description	=	arg.Description;
	oc_concept.m_Type				=	arg.Type;
	oc_concept.m_TypeNo			=	arg.TypeNo;

//	pBX_SingleObject->CACHE_UPDATE_NO_MOD_Concept_ExtendedEnumerate++;

	return ERR_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_Enumerate																		[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT
MOD_Concept_Enumerate(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_Enumerate);
// ������ ��� ��������:
	if (arg.objFirstNo < 0)														arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)										arg.objLastNo		= INT_MAX;

	arg.objNames.Delete();
	arg.objIDs.Delete();
	
	OC_Concept	oc_concept;
	oc_concept.SetIndex_Level();
	
	int i = arg.objFirstNo;
	for (oc_concept.GoFirst();(oc_concept.IsValid()) && (i <= arg.objLastNo); oc_concept.GoNext())
	{
		arg.objIDs.Add(oc_concept.GetObjectID());
		arg.objNames.Add(oc_concept.m_Name);

		i++;
	}

	return ERR_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` AddFilteredChilds                                                         []                 
//                                                                            []
// ��������������� ������� ��� MOD_Concept_ExtendedEnumerate
void AddFilteredChilds(	const OC_Concept&			oc_concept,
										MOD_Concept_Args&	arg,
								const	identifier_arr&	IncludeIDs)
{
	DEBUG_STACK_NAME (AddFilteredChilds);
	int		i = 0;
	string	OutName;

// ������� ���������� ������� � �������� ���������:
	if (arg.Indent) // � ���������
	{
		for (i = 0; i < oc_concept.m_Level; i++) OutName += "_";
	}

	OutName += string(oc_concept.m_Name);

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
[]` MOD_Concept_ExtendedEnumerate                                             []
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT MOD_Concept_ExtendedEnumerate(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_ExtendedEnumerate);
	int	i;

// ������� �������� ���������:
	arg.objIDs	.Delete();
	arg.objNames.Delete();

// ���� ����������� �������� ��� ��������:
	if (arg.ConceptType.Size() == 0)
		arg.ConceptType.Add("Concept");

//----------------------------------------------------------------------------[] 
	identifier_arr	ParentID;
	identifier_arr	VBN_Concept;

	OC_Concept	oc_concept;
	oc_concept.SetIndex_Type_Level();

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

	
//----------------------------------------------------------------------------[] 
// 
	for (i = 0; i < ParentID.Size(); i++)
	{
		oc_concept.Open(ParentID[i]);
	// �������� �� �������:
		if ((arg.Level >= 0) && (oc_concept.m_Level > arg.Level)) // �� �������� �� ������.
			continue;
	// �������� ����� "� �������":
		AddFilteredChilds(oc_concept, arg , VBN_Concept);			
	}

//----------------------------------------------------------------------------[] 
// ���������� ���������� ���������� �������:
//!!	CACHE_STORE_RESULT_2 (arg.objIDs, arg.objNames);
	return ERR_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_GetData                                                       []
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT
MOD_Concept_GetData(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_GetData);
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))
	{
		arg.ParentID= NA;
		arg.Level	= -1;
		arg.No		= -1;
		arg.Name.Delete();
		arg.Description.Delete();
		return ERR_BadID;
	}

	OC_Concept			oc_concept;
	oc_concept.Open(arg.objID);

	arg.ParentID	= oc_concept.m_Parent		;
	arg.Level		= oc_concept.m_Level			;
	arg.No			= oc_concept.m_No				;
	arg.Name			= oc_concept.m_Name			;
	arg.Description= oc_concept.m_Description	;
	arg.Type			= oc_concept.m_Type			;
	arg.TypeNo		= oc_concept.m_TypeNo		;

	return ERR_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_Delete                                                        []
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT 
MOD_Concept_Delete(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_Delete);
	if (!OC_Exist(OBJ_CLASS_ID_Concept, arg.objID))				return ERR_BadID;
	if (!CheckPicklockPassword(arg.PicklockPassword))			return ERR_BadPicklockPassword;
	
	OC_Concept			oc_concept;
	oc_concept.Open(arg.objID);

//----------------------------------------------------------------------------[]
// ������� ����� (����������):
	while (oc_concept.m_Child.Size() > 0)
	{
		MOD_Concept_Args		concept_args;

		concept_args.objID				= oc_concept.m_Child[0];
		concept_args.PicklockPassword = arg.PicklockPassword;

		OBJ_ASSERT_RETURN(MOD_Concept_Delete(concept_args));
	}
	
// ������� ���� �� ������ Descendant � DescendantNo ���������
	int			Pos		= -1;
	
	identifier	idParent = oc_concept.m_Parent;	// ��������� ��������.
	OC_Concept	oc_parent_concept;

// �� ���� �������:
	while(idParent != NA)
	{
	// ��������� ������ ��������-������:
		OBJ_CHECK_AND_OPEN(oc_parent_concept, idParent, OBJ_CLASS_ID_Concept);

	// ������ ���� ID � ������ �������� � ������:
		Pos = oc_parent_concept.m_Descendant.Find(arg.objID);

	// �� ������� - ������:
		if (Pos < 0)
		{
			SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Can't find concept #%lu in descendant list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_Descendant.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_Descendant.Find(arg.objID) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Duplicate concept #%lu in descendant list of concept #%lu. Deleted anyway!",
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
			SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Can't find No of concept #%lu in DescendantNo list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_DescendantNo.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_DescendantNo.Find(oc_concept.m_No) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Duplicate No of concept #%lu in DescendantNo list of concept #%lu. Deleted anyway!",
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
			SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Can't find concept #%lu in child list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_Child.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_Child.Find(arg.objID) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Duplicate concept #%lu in child list of concept #%lu. Deleted anyway!",
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
			SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Can't find No of concept #%lu in ChildNo list of concept #%lu.",
				arg.objID, idParent);
		}
	// ������� - �������:
		else
		{
			oc_parent_concept.m_ChildNo.Del(Pos);
		// �������� �� ������������:
			if (oc_parent_concept.m_ChildNo.Find(oc_concept.m_No) != -1)
			{
				SERVER_DEBUG_ERROR_2 ("MOD_Concept_Delete(): Duplicate No of concept #%lu in ChildNo list of concept #%lu. Deleted anyway!",
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
		SERVER_DEBUG_ERROR_1 ("MOD_Concept_Delete(): Can't find concept ID #%lu in registry.",
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

//!!	pBX_SingleObject->CACHE_UPDATE_NO_MOD_Concept_ExtendedEnumerate++;

	return ERR_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ExpandConcept                                                             []           
//                                                                            []
// ��� ������� ��������� � ������ (CPtr<id>) concept_arr ��� �����������		[]
// ��������� � �� ���������.																	[]
ERR_RESULT
ExpandConcept(identifier_arr &concept_arr)
{
	DEBUG_STACK_NAME (ExpandConcept);
	if (concept_arr.Size() == 0)		return ERR_OK;

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

	return ERR_OK;
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` ExpandWithParentConcepts                                                  []
//                                                                            []
// ��������� � concept_arr �������������� ���������-������� (� ������� > 2)
// ���������� ������������ � ��� ���������. ������������ ��������� ���������.
ERR_RESULT
ExpandWithParentConcepts(identifier_arr &concept_arr)
{
	DEBUG_STACK_NAME (ExpandWithParentConcepts);
	if (concept_arr.Size() == 0)		return ERR_OK;

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

	return ERR_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` MOD_Concept_TypeEnumerate                                                 []
[]                                                                            []
[]____________________________________________________________________________*/
ERR_RESULT
MOD_Concept_TypeEnumerate(MOD_Concept_Args& arg)
{
	DEBUG_STACK_NAME (MOD_Concept_TypeEnumerate);
	arg.objNums.Erase();
	arg.objNames.Erase();

	OC_Concept		oc_concept;
	oc_concept.SetIndex_TypeNo();

	for (oc_concept.GoFirst(); oc_concept.IsValid(); oc_concept.GoNextUnique())
	{
		arg.objNums.Add(oc_concept.m_TypeNo);
		arg.objNames.Add(oc_concept.m_Type);
	}

	return ERR_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ConceptCompiler                                                           []               
[]                                                                            []
[]____________________________________________________________________________[]
*/
ERR_RESULT ConceptCompiler (const char * sFileName)
{
	DEBUG_STACK_NAME (ConceptCompiler);

	int i, j;
	CPtr<ConceptItem> arr_ConceptItem;
	string_arr			arr_sys_comments;
	
	string srcfile;
	if (srcfile.ReadFile (sFileName)<=1)
	{
		SERVER_DEBUG_ERROR_1 ("��� ������ � ����� %s", sFileName);
		return ERR_SYSTEM_ERROR;
	}
	string_arr arr_srcfile;
	string_arr arr_srcfile_tmp;

	srcfile.explode (arr_srcfile_tmp, "\n");

	for (i=0; i<arr_srcfile_tmp.Size();i++)
	{
		arr_srcfile_tmp[i].rtrim();
		if (strlen (arr_srcfile_tmp[i].c_str()))
			arr_srcfile += arr_srcfile_tmp[i];
	}

	string cur_sys_comment="";

	for (i=0; i<arr_srcfile.Size();i++)
	{
	// ������� �����
		string CurString = arr_srcfile[i];
		string Names = "";
		CurString.SubStr (Names, 0, CurString.Find("{"));
		string_arr arr_Names;
		string_arr arr_Descr;
		int Level = 0;
		for (Level = 0; Names[Level] == '\t'; Level++)
		{
			(void)NULL;
		}
		Names.explode (arr_Names, "|");

		for (j=0; j<arr_Names.Size(); j++)
		{
			arr_Names[j].trim();
		// ������� ��������
			string CurDescr="No description";
			char SSS[10240];
			strcpy (SSS, arr_Names[j].c_str());
			char * pSys1 = strtok (SSS, "[");
			char * pSys2 = strtok (NULL, "]");
			if (pSys1 && pSys2)
			{
				CurDescr = pSys2;
			}
			arr_Descr += CurDescr;
			arr_Names[j] = SSS;
			arr_Names[j].trim();
		}

	// ������� ��������� �����������
		char SSS[10240];
		int cur_sys_comment_no=-1;
		strcpy (SSS, CurString.c_str());
		char * pSys1 = strtok (SSS, "{");
		char * pSys2 = strtok (NULL, "}");
		if (pSys1 && pSys2)
		{
			cur_sys_comment = pSys2;
			cur_sys_comment.trim();
		}
		cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		if (cur_sys_comment_no==-1)
		{
			arr_sys_comments+=cur_sys_comment;
			cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		}

		int Parent=0;
		for (Parent=arr_ConceptItem.Size()-1; Parent>=0; Parent--)
		{
			if (arr_ConceptItem[Parent].m_Level<Level)
			{
				break;
			}
		}
		ConceptItem concept_item;
		concept_item.m_objID			= NA;
		concept_item.m_Level			= Level;
		concept_item.m_nParent		= Parent;
		concept_item.m_Name			= arr_Names[0];
		concept_item.m_Descr			= arr_Descr[0];
		concept_item.m_SysComment	= cur_sys_comment;
		concept_item.m_SysCommentNo= cur_sys_comment_no;


		arr_ConceptItem += concept_item;
	}

/*	for (i=0; i<arr_sys_comments.Size(); i++)
	{
		printf ("%2d [%s]\n", i, arr_sys_comments[i].c_str());
	}
	printf ("\n\n");
*/

// �������� ���������:
//	printf("\nConcepts");

	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		if (arr_ConceptItem[i].m_SysComment.Len() < 1)
		{
			printf ("\n * * Invalid Concept type %s * * \n", arr_ConceptItem[i].m_Name.c_str());
			continue;
		}

		MOD_Concept_Args	concept_args;
		GetPicklockPassword(concept_args.PicklockPassword);
		concept_args.Name					= arr_ConceptItem[i].m_Name;
		concept_args.Description		= arr_ConceptItem[i].m_Descr;
		if (arr_ConceptItem[i].m_nParent >= 0)
		{
			concept_args.ParentID		= arr_ConceptItem[arr_ConceptItem[i].m_nParent].m_objID;
		}

		concept_args.Type					= arr_ConceptItem[i].m_SysComment;
		concept_args.TypeNo				= arr_ConceptItem[i].m_SysCommentNo;

		OBJ_ASSERT_PASSIVE(MOD_Concept_New(concept_args));

		arr_ConceptItem[i].m_objID = concept_args.objID;

//		putchar('.');

	// -------------------------------- []
	//		printf ("\n[%d]\n", i);
	//		arr_ConceptItem[i].DebugPrint();
	// -------------------------------- []
	}

	// printf("\nConcepts created: %d, System types: %d.\n", arr_ConceptItem.Size(), arr_sys_comments.Size());


	return ERR_OK;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ConceptGetUnicTypeNo                                                      []                    
//                                                                            []
int ConceptGetUnicTypeNo ()
{
	OC_Concept oc_concept;
	oc_concept.SetIndex_TypeNo ();
	oc_concept.GoLast();
	return oc_concept.m_TypeNo + 1;
}
//____________________________________________________________________________[]






/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/

