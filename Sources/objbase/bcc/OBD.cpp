/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBD.cpp																	[]
[] Date:            25.03.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Object Base Driver (OBD)												[]
[] Last Modified:																               []                                
[]____________________________________________________________________________[]
*/

#define	USES_STATIC_FILE_ID_h
#define	USES_Ptr_h
#define	USES_string_h
#define	USES_AVTree_h
#define	USES_EventMonitor_h
#define	USES_File_h
#define	USES_key_arr_h
#define	USES_ObjDriver_h

#include "main.h"
#include "OBD.h"
#include "CACHE.h"

bool CHECK_VALID_IGNORE_DELETED	=	false;
bool IGNORE_LAST_KEY_IDENTIFIER	=	false;


bool OBD_Busy = false;


//______________________________________________________________________________
//                                                                            []
//` CompareFunction_identifier																[]
//                                                                            []
int CompareFunction_identifier (identifier& a, identifier& b)
{
	return	a - b;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` CompareFunction_CObjIndex_AVTree_Item 												[]
//                                                                            []
int CompareFunction_CObjIndex_AVTree_Item (pbyte& a, pbyte& b)
{
// a,b		=	[size_t Size, byte KeyNum, key1, ... keyN]
// Keyi		=	[byte type, data]	
// LastKey	=	idendifier key
	const size_t offset_Key		= sizeof (size_t) + sizeof (byte);

	
	return memcmp (a+offset_Key, b+offset_Key, min (*((size_t *)a), *((size_t *)b)) - offset_Key - (IGNORE_LAST_KEY_IDENTIFIER? sizeof(identifier): 0));
}
//____________________________________________________________________________[]


#ifndef LAY_COMPILER_PROJECT

//______________________________________________________________________________
//                                                                            []
//` OBD_Exist																						[]
//                                                                            []
bool OBD_Exist (long classID, identifier objID)
{
// ID �� ���������� �������
	if (objID<FILE_ID_LAST)
		return false;

// ������ ID
	if (objID==NA)
		return false;

// ������ �������� � ������
	OBD_pointer coPtr = OBD_AllObjectsInMemory.Find (objID);
	if (coPtr!=NULL)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
			return false;
		if (aObject->pData==NULL)
			return false;
		if (pData_classID(classID, aObject->pData) != (identifier)classID)
			return false;
		if (aObject->objID==NA)
			return false;
		if (aObject->bDeleted)
			return false;
		return true;
	}

// ������ �� � ������ -- ��������� �� �����.
   CFile file;
   if (!file.Exist(objID))
       return false;
   file.Open (objID);

   identifier tmp_classID;

	if (file.GetMaxSize()<sizeof (tmp_classID))
	{
		return false;
	}

   file.ReadData(tmp_classID);
   return (tmp_classID == (identifier) classID);
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` �������� ������������� ������� ���������� ������									[]
//  � ��������� ��������������.																[]
bool OC_Exist (identifier classID, identifier objID) 
{
	return OBD_Exist (classID, objID);
};
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OBD
[]                                                                            []
[]____________________________________________________________________________[]
*/


//----------------------------------------------------------------------------[] 
#ifndef LAY_COMPILER_PROJECT
	IT_AVTree_AllObjectsInMemory	OBD_AllObjectsInMemory (&CAbstractObjectInMemory::objID, CompareFunction_identifier);
#endif
//----------------------------------------------------------------------------[] 






//______________________________________________________________________________
//                                                                            []
//` ������������� ������ ������ -- ��� ������, ���� ����� 							[]
//	 ����� �������� ����������																	[]
//                                                                            []
void CorrectKeyArr (key_arr& ka, identifier classID, identifier indexID)
{
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	for (int k=0; k<pObjDriveIndex->fieldArr_ascend.GetSize() && k<(int)ka.GetKeyNum(); k++)
	{
		identifier fieldID = pObjDriveIndex->fieldArr[k];
		SERVER_DEBUG_ASSERT (theObjDriver.GetFieldPtr(classID, fieldID)->type==ka.GetItemType(k), "CorrectKeyArr: ������������ ����� ������");

	// ���� f ������������� � �������� �������
		if (pObjDriveIndex->fieldArr_ascend[k]==false)
		{
			switch (theObjDriver.GetFieldPtr(classID, fieldID)->type)
			{
				case FT_string:
				{
					static char Value [MAX_KEY_LENGTH];
					Value[0] =0;
					ka.GetKeyData (k, Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_identifier:
				{
					identifier Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_int:
				{
					int Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_byte:
				{
					byte Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_bool:
				{
					bool Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				case FT_float:
				{
					float Value;
					ka.GetKeyData (k, &Value);
					ka.SetKeyData (k, Value, true);
				}
				break;
				default:
					SERVER_DEBUG_ERROR ("CorrectKeyArr: ����������� ��� �����");
				return;
			}
		}
	}
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` GetObject 																						[]
//                                                                            []
OBD_pointer OBD_GetObject (long classID, identifier objID, identifier indexID, OBD_pointer coIndexPtr)
{
	OBD_pointer			coPtr;
	coPtr = OBD_AllObjectsInMemory.Find (objID);

	if (coPtr!=NULL)
	{
	// ������ � ������
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_GetObject: ������ ������ ������� ������ '%s':  aObject==NULL objID=%d", className[classID], objID);
			return NULL;
		}
		aObject->AddRef ();
	// ���� ���� -- ����������� ��������� �� ����� � �������
		if (indexID!=NA && coIndexPtr!=NULL)
		{
			pData_m_CoIndexPtr (classID, aObject->pData, indexID, coIndexPtr);
		}

	// �������� ���� � ������������ �������
		if (!OBD_Busy)
		{
			OBD_Busy = true;
			the_OBJ_CACHE.OnOpen (coPtr);
			OBD_Busy = false;
		}

		return coPtr;
	}
	else  
	{
	// ������ �� � ������ -- ��������� � �����

	// �������������� �� ��������
		if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Open, classID, objID)==false) return NULL;

		void * pData = new_OD (classID, false);
		size_t nObjSize = pData_LoadFromFile (classID, pData, objID);
		if (nObjSize!=0)
		{
			CAbstractObjectInMemory aObject;
			aObject.pData				= pData;
			aObject.classID			= classID;
			aObject.objID				= objID;
			aObject.AddRef					();
			aObject.nSize				= nObjSize;
			coPtr = OBD_AllObjectsInMemory.Insert (aObject);
			aObject.pData				= NULL;

			if (coPtr==NULL)
			{
				SERVER_DEBUG_ERROR_2 ("OBD_GetObject: ������ ���������� � ������ ������� id=%d ������ '%s':  aObject==NULL objID=%d", objID, className[classID]);
				return NULL;
			}
		// ���� ���� -- ����������� ��������� �� ����� � �������
			if (indexID!=NA && coIndexPtr!=NULL)
			{
				pData_m_CoIndexPtr (classID, pData, indexID, coIndexPtr);
			}

			if (!OBD_Busy)
			{
				OBD_Busy = true;
			// ���������� �� ��������
				RAISE_EVENT_OBJBASE (EMT_Object_Open, classID, objID);
			// �������� ���� �� �������� �������
				the_OBJ_CACHE.OnOpen (coPtr);
				OBD_Busy = false;
			}

			return coPtr;
		}
		else 
		{
         SERVER_DEBUG_ERROR_3 ("OBD_GetObject: ��������� ������ id=%d ������ '%s' (%d) �� ����������", objID, className[classID], classID);
			return NULL;
		}
	}
	
	return NULL;
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//` OBD_CreateIndexItem 																		[]
//                                                                            []
void OBD_CreateIndexItem (long classID, void * pData, identifier objID)
{
	int indexID,k;
	int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

// ��� ������� ������� ������ � ���������� �����
	for (indexID=0; indexID < IndexNum;  indexID++)
	{
		SERVER_DEBUG_ASSERT (pData_m_CoIndexPtr(classID, pData, indexID)==NULL, "OBD_CreateIndexItem: ������ ��� ���� � �������");

		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

	// ������-������
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
		
	// ����� ������ � �������
		size_t index_key_number = pObjDriveIndex->fieldArr.GetSize();

	// ������ ����� ��� �������� �������
		key_arr ka;
		for (k=0; k < (int) index_key_number; k++)
		{
			pData_AddKeyVarForField (classID, pData, ka, pObjDriveIndex->fieldArr[k]);
		}

	// ���������� ID �������
		ka += objID;

	// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
		CorrectKeyArr (ka, classID, indexID);

	// ��������� ����� ����� ������ � ���������� ����� ��������� ������ �������� �������
		CObjIndex_AVTree_Item newItem;
		newItem.FromPtr (ka.GetPtr());
		pData_m_CoIndexPtr(classID, pData, indexID, pIndexTree->Insert (newItem));
		pObjDriveIndex->bChanged = true;

		SERVER_DEBUG_ASSERT (pData_m_CoIndexPtr(classID, pData, indexID), "�� ������ �������� ����� ������ � ������");
	}
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` OBD_CreateObject																				[]
//                                                                            []
OBD_pointer OBD_CreateObject (long classID, bool bInternal)
{
	void * pData = new_OD (classID, true);

// �������������� � ��������
	if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_New, classID, NA)==false) return NULL;
			
	if (!bInternal && theObjDriver.m_FormatArr[classID].isMaster)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_CreateObject: ������ �������� -- ������ ������-������ '%s' �� ����� ���� ������ �������. �� �������� �������������.", className[classID]);
		return NULL;
	}

	if (pData_classID (classID, pData) != (identifier) classID)
	{
		delete_pData (classID, pData);
      SERVER_DEBUG_ERROR_2 ("OBD_CreateObject: ������ �������� ������� ������ %s (%d):  pData->classID != classID", className[classID], classID);
		return NULL;
	}

// ������ ���� ������� � ���������� � ���� classID
	identifier objID = FD.Write(&classID,sizeof(classID));
		
	CAbstractObjectInMemory aObject;
	aObject.pData				= pData;
	aObject.classID			= classID;
	aObject.objID				= objID;
	aObject.AddRef					();
	aObject.bChanged			= true;
	aObject.bDeleted			= false;
	OBD_pointer coPtr			= OBD_AllObjectsInMemory.Insert (aObject);

	aObject.pData				= NULL;
	aObject.bChanged			= false;


	if (coPtr==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CreateObject: ������ ���������� � ������ ������� id=%d ������ '%s':  aObject==NULL objID=%d", objID, className[classID]);
		return NULL;
	}

	OBD_CreateIndexItem (classID, pData, objID);

// ���������� � ��������
	RAISE_EVENT_OBJBASE (EMT_Object_New, classID, objID);
// �������� ���� � �������� �������
	the_OBJ_CACHE.OnCreate (coPtr);

	return coPtr;
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` OBD_GetClassIdList																			[]
//                                                                            []
void OBD_GetClassIdList	(identifier_arr& id_list, long classID, key_arr* pka, const CIndexInfo& indexInfo)
{
	id_list.Realloc (0);

	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR_1 ("OBD_GetClassIdList: ������ �������� ������ ���� ��������������� -- ����� '%s' �� ����� ��������", className[classID]);
		return;
	}


// ������� ������� ����� ������ ��� ������
	if (pka) if (((int)pka->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_GetClassIdList: ������� ������� ����� ������ ��� ������");
		return;
	}

// ��������� ���� ������
	if (pka) for (int k=0; k < (int)pka->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_GetClassIdList: ������� �������� ���� ������");
			return;
		}
	}

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	key_arr ka;
	if (pka){
		ka  = *pka;
		CorrectKeyArr (ka, classID, indexID);
	}

// ������-������
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	pbyte arg0 = (pka==NULL || pka->GetKeyNum()==0)? NULL: ka.GetPtr  ();	// ���� ������

// ��� �� ������� ������� � ������� ���������������� ��������
	for (OBD_pointer coIndexPtr = (arg0?pIndexTree->Find(arg0):pIndexTree->First()); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (arg0)
		{
		// ����������� ������ ����
			pbyte arg1 = pItem->GetPtr	();	

		// ���� ���� ���������� �� ����� ����� ������ �����
			if (CompareFunction_CObjIndex_AVTree_Item (arg0, arg1)!=0)
			{
				break;
			}
		}
		id_list.Add (pItem->GetObjID());
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` _OBD_IsObjectValid																			[]
//                                                                            []
CAbstractObjectInMemory* _OBD_IsObjectValid (long classID, OBD_pointer coPtr)
{
	if (coPtr==NULL)
	{
		SERVER_DEBUG_ERROR_1 ("������������� ������� ����������� ������ '%s'", className[classID]);
		return NULL;
	}
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	if (aObject==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("������ ������ ������� ������ '%s':  aObject==NULL coPtr=%d", className[classID], coPtr);
		return NULL;
	}
	if (aObject->pData==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("������������� ������������ ����������� (aObject->pData==NULL). ������ id=%d ������ '%s'.", aObject->objID, className[classID]);
		return NULL;
	}
	if (pData_classID(classID, aObject->pData) != (identifier)classID)
	{
		SERVER_DEBUG_ERROR_3 ("������ ������ ������� ������ '%s':  ������������ classID (%d, %d) ", className[classID], pData_classID(classID, aObject->pData),  classID);
		return NULL;
	}
	if (aObject->objID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("������������� ������������ ����������� (aObject->objID==NA). ������� ������ '%s'.", className[classID]);
		return NULL;
	}
	if (!CHECK_VALID_IGNORE_DELETED)
	{
		if (aObject->bDeleted)
		{
			SERVER_DEBUG_ERROR_2 ("������������� ������������ ����������� (aObject->bDeleted==true). ������ %d ������ '%s' ��� �����.", aObject->objID, className[classID]);
			return NULL;
		}
	}
	
	return aObject;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` OBD_GetObjectID																				[]
//                                                                            []
identifier OBD_GetObjectID (long classID, OBD_pointer coPtr)
{
	CAbstractObjectInMemory * aObject = _OBD_IsObjectValid (classID, coPtr);
	if (aObject==NULL)
	{SERVER_DEBUG_ERROR_1 ("OBD_GetObjectID: aObject==NULL class='%s'", className[classID]); return NA;}

	return aObject->objID;	
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_OpenMasterObject																		[]
//                                                                            []
OBD_pointer OBD_OpenMasterObject (long classID)
{
	CFile		FileMasterID	=	FILE_ID_MASTER_CLASS;
	size_t	nFileSize		=	CFile::GetMaxSize(FILE_ID_MASTER_CLASS);
	bool		bContainID		=	nFileSize>=sizeof(identifier);

	if (bContainID)
	{
		identifier objID=NA;
		FileMasterID.ReadData (objID);
		
		return OBD_GetObject (classID, objID);
	}
	else 
	{
		OBD_pointer coPtr	=	OBD_CreateObject	(classID, true);
		identifier	objID	=	OBD_GetObjectID	(classID, coPtr);
		
		FileMasterID.WriteData	(objID);
		FileMasterID.Close		();

		theFileDriver.flush();
		
		return coPtr;
	}

	return NULL;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_IsObjectValid																			[]
//                                                                            []
bool OBD_IsObjectValid (long classID, OBD_pointer coPtr)
{
	if (coPtr==NULL)
		return false;
	CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
	if (aObject==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_IsObjectValid: ������ ������ ������� ������ '%s':  aObject==NULL coPtr=%d", className[classID], coPtr);
		return false;
	}
	if (aObject->pData==NULL)
	{
		return false;
	}
	if (aObject->objID==NA)
	{
		return false;
	}
	if (aObject->bDeleted)
	{
		return false;
	}

	return 
		pData_classID (classID, aObject->pData) == (identifier)classID;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` OBD_Exist																						[]
//                                                                            []
bool OBD_Exist (long classID, identifier objID);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_SaveObject																				[]
//                                                                            []
void OBD_SaveObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject)
{
	IF_OBJECT_INVALID_A {return;}

	if (!aObject->Save ())
	{
		SERVER_DEBUG_ERROR_3 ("OBD_SaveObject: ������ ������ ������� id=%d ������ '%s' (%d):  !aObject->Save ()", aObject->objID, className[classID], classID);
		return;
	}
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` OBD_ReleaseObject																			[]
//                                                                            []
size_t OBD_ReleaseObject (long classID, OBD_pointer coPtr, CAbstractObjectInMemory * _aObject)
{
	size_t retval = 0;
	CHECK_VALID_IGNORE_DELETED = true;
	{
		IF_OBJECT_INVALID_A {CHECK_VALID_IGNORE_DELETED=false; return 0;}

		retval = aObject->Release();

		if (retval==0)
		{
			OBD_SaveObject (classID, coPtr, aObject);

		// ������� ������ �������
			delete_pData (classID, aObject->pData);
			aObject->pData		= NULL;
			aObject->bChanged	= false;
			aObject->bDeleted	= true;

		// ������ �� ������ ����� �� ��������� -- ����� ������� "������ � ������".
			OBD_AllObjectsInMemory.Remove (coPtr);
		}
		else
		{
		// �������� ���� � �������� ����������� �������
			if (!OBD_Busy)
			{
				OBD_Busy = true;
				if (aObject->nCached) the_OBJ_CACHE.OnClose (coPtr);
				OBD_Busy = false;
			}
		}

	}
	CHECK_VALID_IGNORE_DELETED = false;

	return retval;
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` OBD_CopyObject																				[]
//                                                                            []
OBD_pointer OBD_CopyObject (long classID, OBD_pointer coPtr)
{
	IF_OBJECT_INVALID {return NULL;}

	aObject->AddRef();
	return coPtr;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ���������� ����� ������� � ������� �� ����������� ������						[]
//                                                                            []	
OBD_pointer OBD_FindObjectByOwnData (long classID, void * pData, identifier objID, CObjIndex * pObjDriveIndex, identifier indexID)
{
// ����� ������ � �������
	size_t index_key_number = pObjDriveIndex->fieldArr.GetSize();

// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

// ������ ����������� ����� ������
	key_arr ka;
	for (int k=0; k < (int)index_key_number; k++)
	{
		pData_AddKeyVarForField (classID, pData, ka, pObjDriveIndex->fieldArr[k]);
	}

// ��������� � ���� ������ ������������� �������
	ka += objID;

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	CorrectKeyArr (ka, classID, indexID);

	pbyte arg = ka.GetPtr();
	
// ���� ������ � ������� � ������� == ������������ ������ ������ � � ������ ���������������.
	OBD_pointer coIndexPtr = pIndexTree->Find (arg);

// �� ������� ���������� ����� ������� � ������� �� ����������� ������
	if (coIndexPtr==NULL)
	{
		SERVER_DEBUG_ERROR ("OBD_FindObjectByOwnData: ���������� ���������� ����� ������� � ������� �� ����������� ������");
		return NULL;
	}

	return coIndexPtr;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ������� ������ �� �������																	[]
//                                                                            []	
void OBD_DeleteIndexItem (long classID, void *pData, identifier objID)
{
	int indexID;
	int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

// ��� ������� �������
	for (indexID=0; indexID < IndexNum;  indexID++)
	{
		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

	// ������-������
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

	// ������ �� ����� ������ ����� � �������
		if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
		{
			pData_m_CoIndexPtr(classID, pData, indexID, OBD_FindObjectByOwnData (classID, pData, objID, pObjDriveIndex, indexID));
		}

	// ������ �� ������������ � �������
		if (pData_m_CoIndexPtr(classID, pData, indexID)==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_DeleteIndexItem: ������ ������ '%s' �� ������������ � ������� %d", className[classID], indexID);
			return;
		}

	// ������� ������ �� �������
		pIndexTree->Remove (pData_m_CoIndexPtr(classID, pData, indexID));
		pData_m_CoIndexPtr(classID, pData, indexID, NULL);

	// ������ ���������
		pObjDriveIndex->bChanged = true;
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_DeleteObject 																			[]
//                                                                            []
void OBD_DeleteObject (long classID, OBD_pointer coPtr)
{
	IF_OBJECT_INVALID {return;}

	if (theObjDriver.m_FormatArr[classID].isMaster)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_DeleteObject: ������ �������� -- ������ id=%d ������-������ '%s' �� ����� ���� �����.", aObject->objID, className[classID]);
		return;
	}

	identifier objID = aObject->objID;
	if (CFile::Exist(objID))
	{
	// �������������� �� ��������
		if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Delete, classID, objID)==false) return;
		CFile::DeleteFile (objID);
	}

	OBD_DeleteIndexItem (classID, aObject->pData, objID);

// ������� ������ �������
	aObject->bChanged	= false;
	aObject->bDeleted	= true;
// ������ ������� "������ � ������", ��� ��� �� ���� ��������� �����������

// ���������� �� ��������
	RAISE_EVENT_OBJBASE (EMT_Object_Delete, classID, objID);
// �������� ���� �� �������� �������
	if (aObject->nCached) the_OBJ_CACHE.OnDelete (coPtr);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` OBD_DeleteObject 																			[]
//                                                                            []
void OBD_DeleteObject (long classID, identifier objID)
{
// ������ ����������� ��� ����, ��� ������ ��������,
// ����� ���������� ������ ��� � �������� -- �� ��������������
// ������� ������ �� �����, ���������� �� �����, � ����� ������� 
// ��� �� ��������. -- ��� ���� �� ����� ������ ��������.
	OBD_pointer coPtr = OBD_GetObject (classID, objID);
	OBD_DeleteObject		(classID, coPtr);
	OBD_ReleaseObject		(classID, coPtr);		
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �������� �� �����																[]
//                                                                            []
void OBD_DeleteObject (long classID, key_arr& _ka, CIndexInfo& indexInfo)
{
	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_DeleteObject: �������� ������� �� ����������":"OBD_DeleteObject: �������� ������� ������� �� �����");
		return;
	}

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	key_arr ka;
	ka  =  _ka;
	CorrectKeyArr (ka, classID, indexID);

//----------------------------------------------------------------------------[] 
//	
// ������� ��� ������� ������ classID
//
	if (ka.GetKeyNum ()==0)
	{
	// ��������� ������ ����������� ��������
		identifier indexID = 0;
		if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
		{
			SERVER_DEBUG_ERROR_1 ("OBD_DeleteObject: ������� ������ '%s' �� ����� ���� ������� '������' -- ����� �� ����� ��������", className[classID]);
			return;
		}

	// ������
		CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
		CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

	// ��� �� ������� ������� � ���������� ��������������
		for (OBD_pointer coIndexPtr = pIndexTree->First(); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
		{
			CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

		// �������� id
			identifier objID = pItem->GetObjID();

			OBD_pointer coPtr =	OBD_AllObjectsInMemory.Find (objID);

		// ������ � ������ - ���� �������� ��� ������
			if (coPtr!=NULL)
			{
				IF_OBJECT_INVALID {continue;}

			// �������������� �� ��������
				if (RAISE_EVENT_AHEAD_OBJBASE (EMT_Object_Delete, classID, objID)==false)
					continue;

			// ������� ������ �������
				aObject->bChanged	= false;
				aObject->bDeleted	= true;
			// ������ ������� "������ � ������", ��� ��� �� ���� ��������� �����������

			// ���������� �� ��������
				RAISE_EVENT_OBJBASE (EMT_Object_Delete, classID, objID);
			// �������� ���� �� �������� �������
				if (aObject->nCached) the_OBJ_CACHE.OnDelete (coPtr);
			}

		// ������� ������ � �����
			if (CFile::Exist(objID))
				CFile::DeleteFile (objID);

		}

	// ������� ��� ������� ������� ������
		for (indexID=0; indexID < (size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize();  indexID++)
		{
			theObjDriver.GetIndexPtr (classID, indexID)->AVTree.RemoveAll();
			theObjDriver.GetIndexPtr (classID, indexID)->bChanged = true;
		}

	// ��������� ��������� � �������� �������
		theFileDriver.flush();

		return;
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//	
// ������� ��� ������� ������ classID, ������� �������� ����� "ka"
//

// ������-������
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	pbyte arg2 = ka.GetPtr     ();	// ���� ������
	CPtr <identifier> id_Arr;
	id_Arr.Realloc (0);
// ��� �� ������� ������� � ������� ���������������� ��������
	for (OBD_pointer coIndexPtr = pIndexTree->Find(arg2); coIndexPtr!=NULL; coIndexPtr = pIndexTree->Next(coIndexPtr))
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);

	// ����������� ������ ����
		pbyte arg1 = pItem->GetPtr	();	

	// ���� ���� ���������� ����� ����� ������ -- ���������� ��� ��������
		if (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)==0)
		{
			id_Arr.Add (pItem->GetObjID());
		}
		else 
		{
			break;
		}
	}
// ������� ����������� ��������������
	for (int d=0; d<(int)id_Arr.GetSize(); d++)
	{
		OBD_DeleteObject (classID, id_Arr[d]);
	}
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` OBD_GetClassID																				[]
//                                                                            []
identifier OBD_GetClassID (long classID, OBD_pointer coPtr)
{
	IF_OBJECT_INVALID {return NA;}
	return pData_classID (classID, aObject->pData);
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` ���������� ������																			[]
//                                                                            []
void OBD_DebugPrint(long classID, string& dbg, OBD_pointer coPtr)
{
	IF_OBJECT_INVALID {return;}
	dbg = "";
	pData_DebugPrint (classID, aObject->pData, dbg, aObject->objID);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` ��������� �������� ����� �� �������� ������� � ������-����������				[]
//                                                                            []
int OBD_CompareToKeyVarArr (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr& _ka)
{
// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	identifier indexID = indexInfo.m_id;
	key_arr ka;
	ka  =  _ka;
	CorrectKeyArr (ka, classID, indexID);

	IF_OBJECT_INVALID {return -1;}
	OD_BASE* pData = (OD_BASE*)aObject->pData;

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_CompareToKeyVarArr: �������� ������� �� ����������":"OBD_CompareToKeyVarArr: �������� ������� ������� �� �����");
		return -1;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// ������� ������� ����� ������ ��� ������
	if (((int)ka.GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_CompareToKeyVarArr: ������� ������� ����� ������ ��� ������");
		return 0;
	}

// ��������� ���� ������
	for (int k=0; k < (int)ka.GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != ka.GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_CompareToKeyVarArr: ������� �������� ���� ������");
			return 0;
		}
	}


// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = pData->m_CoIndexPtr[indexID];

// ������ �� ����� ������ ����� � �������
	if (coIndexPtr==NULL)
	{
		pData->m_CoIndexPtr[indexID] = coIndexPtr = OBD_FindObjectByOwnData (classID, pData, aObject->objID, pObjDriveIndex, indexID);
	}
// ������ �� ������������ � �������
	if (coIndexPtr==NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CompareToKeyVarArr: ������ ������ '%s' �� ������������ � ������� %d", className[classID], indexID);
		return -1;
	}
	

// ��������� ������
	CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
	if (pItem == NULL)
	{
		SERVER_DEBUG_ERROR_2 ("OBD_CompareToKeyVarArr: ������ ��������� �������� ������� %d ��� ������ ������ '%s' �� ������������ � ������� %d", indexID, className[classID]);
		return -1;
	}
	pbyte arg1 = pItem->GetPtr ();
	pbyte arg2 = ka.GetPtr		();
	return CompareFunction_CObjIndex_AVTree_Item (arg1, arg2);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ����� ������ �� �������																	[]
//                                                                            []
OBD_pointer OBD_IndexFindObject (long classID, const CIndexInfo& indexInfo, key_arr& _ka, bool bInexact)
{
	identifier indexID = indexInfo.m_id;

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	key_arr ka;
	ka  =  _ka;
	CorrectKeyArr (ka, classID, indexID);

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_IndexFindObject: �������� ������� �� ����������":"OBD_IndexFindObject: �������� ������� ������� �� �����");
		return NULL;
	}

	if (indexID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_IndexFindObject: ����� ������� ������ '%s' ��� ������������� �������", className[classID]);
		return NULL;		
	}

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

//	����� ������ ��� ������
	int keyNum = ka.GetKeyNum ();

// ������� ������� ����� ������ ��� ������
	if (keyNum > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_IndexFindObject: ������� ������� ����� ������ ��� ������");
		return NULL;
	}

// ��������� ���� ������
	for (int k=0; k < keyNum; k++) 
	{
		if (indexInfo.m_keyType[k] != ka.GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_IndexFindObject: ������� �������� ���� ������");
			return NULL;
		}
	}

// ���� � �������
	pbyte arg = ka.GetPtr();
	OBD_pointer coIndexPtr = pIndexTree->Find (arg, bInexact);
	
// ���� ����� -- ��������� ������
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			identifier objID = pItem->GetObjID ();			
			OBD_pointer coPtr = OBD_GetObject (classID, objID, indexID, coIndexPtr);
			return coPtr;
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_IndexFindObject: ������ ��� ������ �������: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NULL;
		}
	}
	return NULL;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// ����� ����/���������� �������� � �������� ������ � ������� �������			[]
//                                                                            []
size_t OBD_GetIndexNumForKey (long classID, const CIndexInfo& indexInfo, key_arr& _ka, key_arr& _ka_rbound, bool bUnique)
{
	identifier indexID = indexInfo.m_id;

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	key_arr			ka;
	ka  =				_ka;
	CorrectKeyArr (ka, classID, indexID);
	key_arr			ka_rbound;
	ka_rbound  =  _ka_rbound;
	CorrectKeyArr (ka, classID, indexID);

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_GetIndexNumForKey: �������� ������� �� ����������":"OBD_GetIndexNumForKey: �������� ������� ������� �� �����");
		return 0;
	}

	if (indexID==NA)
	{
		SERVER_DEBUG_ERROR_1 ("OBD_GetIndexNumForKey: ����� ������� ������ '%s' ��� ������������� �������", className[classID]);
		return 0;		
	}

	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);

// ��������
	for (int kki=0; kki<2; kki++)
	{
		key_arr * pka = kki==0? &ka: kki==1? &ka_rbound: NULL;
		SERVER_DEBUG_ASSERT_RETURN (pka, "System Error", 0);

	//	����� ������ ��� ������
		int keyNum = pka->GetKeyNum ();

	// ������� ������� ����� ������ ��� ������
		if (keyNum > indexInfo.m_keyNum)
		{
			SERVER_DEBUG_ERROR ("OBD_GetIndexNumForKey: ������� ������� ����� ������ ��� ������");
			return 0;
		}

	// ��������� ���� ������
		for (int k=0; k < keyNum; k++) 
		{
			if (indexInfo.m_keyType[k] != pka->GetItemType(k))
			{
				SERVER_DEBUG_ERROR ("OBD_GetIndexNumForKey: ������� �������� ���� ������");
				return 0;
			}
		}
	}

// ����� ����� �������� � �������
	if (ka.GetKeyNum()==0 && ka_rbound.GetKeyNum()==0 && !bUnique)
	{
		return pIndexTree->Count();
	}

// ���� � �������
	pbyte arg0 = ka.GetPtr();
	pbyte arg1 = NULL;
	pbyte arg_rbound = ka_rbound.GetKeyNum()!=0? ka_rbound.GetPtr(): NULL;
	size_t nResultNum  = 0;
	for (OBD_pointer coIndexPtr = pIndexTree->Find (arg0); coIndexPtr!=NULL; coIndexPtr=pIndexTree->Next (coIndexPtr))
	{
		pbyte arg2 = pIndexTree->ItemPointer (coIndexPtr)->GetPtr();

	//	�������� �� ����� �� ������� ������� �����
		if (arg_rbound!=NULL && CompareFunction_CObjIndex_AVTree_Item (arg_rbound, arg2)<0)
			break;

	//	��������� ��������� ������ ����� � ��������
		int nCompare = CompareFunction_CObjIndex_AVTree_Item (arg0, arg2);

	//	����� ���� ������ �������
		if (nCompare>0)
		{
			SERVER_DEBUG_ERROR ("������ ��������������");
			break;
		}

	//	����� ���� ������ ������� � ���� ��� ������������� ������ �������
	// �.�. ���������� ������ ���������� �����.
		if ((nCompare!=0) && (arg_rbound==NULL))
			break;

	//	����������� ������� (� ��������� �� ������������)
		if (bUnique)
		{
			IGNORE_LAST_KEY_IDENTIFIER = true;
			{
				nResultNum += (arg1==NULL || (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)!=0));
			}
			IGNORE_LAST_KEY_IDENTIFIER = false;
		}
		else 
		{
			nResultNum ++;
		}

	//	���������� ���������� �������� ��� �������� �� ������������
		arg1 = arg2;
	}
	
	return nResultNum;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
// ����� ���� �������� ������																	[]
//                                                                            []
size_t OBD_IndexTotalNum (long classID)
{
// �� ������� �������
	identifier indexID = 0;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR_1 ("OBD_IndexTotalNum: ����� ����� �������� ������ '%s' �� ����� ���� ���������� -- ����� �� ����� ��������", className[classID]);
		return 0;
	}

	return theObjDriver.GetIndexPtr (classID, indexID)->AVTree.Count ();
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` �������� ������������� �������/���������� ������� �� �������					[]
//                                                                            []
identifier OBD_FirstLastIDInIndex (long classID, const CIndexInfo& indexInfo, OBD_FIND findType)
{
	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_FirstLastIDInIndex: �������� ������� �� ����������":"OBD_FirstLastIDInIndex: �������� ������� ������� �� �����");
		return NA;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = NULL;

	if (findType == OBD_FIND_First)
	{
		coIndexPtr = pIndexTree->First ();
	}
	else if (findType == OBD_FIND_Last)
	{
		coIndexPtr = pIndexTree->Last ();
	}

// ���� ����� -- ������� id �������
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			identifier objID = pItem->GetObjID ();			
			return objID;
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_FirstLastIDInIndex: ������ ��� ������ �������: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NA;
		}
	}
	return NA;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` �������� ������������� ������� ������� �� �������									[]
//                                                                            []
identifier OBD_FirstIDInIndex (long classID, const CIndexInfo& indexInfo)
{
	return OBD_FirstLastIDInIndex (classID, indexInfo, OBD_FIND_First);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` �������� ������������� ���������� ������� �� �������								[]
//                                                                            []
identifier OBD_LastIDInIndex (long classID, const CIndexInfo& indexInfo)
{
	return OBD_FirstLastIDInIndex (classID, indexInfo, OBD_FIND_Last);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ����� ���������/����������/������/��������� ������								[]
//                                                                            []
OBD_pointer OBD_IndexNextPrevFirstLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, OBD_FIND findType, key_arr* _pka, bool bUnique, bool bSame)
{
	identifier indexID = indexInfo.m_id;

// ������������ ����� ������ -- ��� ������, ���� ����� ����� �������� ����������
	key_arr * pka=NULL;
	if (_pka){
		pka  =  new key_arr;
		(*pka) = (*_pka);
		CorrectKeyArr (*pka, classID, indexID);
	}

	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_IndexNextPrevFirstLastObject: �������� ������� �� ����������":"OBD_IndexNextPrevFirstLastObject: �������� ������� ������� �� �����");
		return NULL;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);

// ������� ������� ����� ������ ��� ������
	if (pka) if (((int)pka->GetKeyNum()) > indexInfo.m_keyNum)
	{
		SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: ������� ������� ����� ������ ��� ������");
		return NULL;
	}

// ��������� ���� ������
	if (pka) for (int k=0; k < (int)pka->GetKeyNum(); k++) 
	{
		if (indexInfo.m_keyType[k] != pka->GetItemType(k))
		{
			SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: ������� �������� ���� ������");
			return NULL;
		}
	}

// ������-������
	CObjIndex_AVTree* pIndexTree = &(pObjDriveIndex->AVTree);
	OBD_pointer coIndexPtr = NULL;

	if ((findType == OBD_FIND_Next) || (findType == OBD_FIND_Prev))
	{
		IF_OBJECT_INVALID {return NULL;}
		OD_BASE* pData = (OD_BASE*)aObject->pData;
		OBD_pointer old_coIndexPtr = pData->m_CoIndexPtr[indexID];
	// ������ �� ����� ������ ����� � �������
		if (old_coIndexPtr==NULL)
		{
			pData->m_CoIndexPtr[indexID] = old_coIndexPtr = OBD_FindObjectByOwnData (classID, pData, aObject->objID, pObjDriveIndex, indexID);
		}
	// ������ �� ������������ � �������
		if (old_coIndexPtr==NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: ������ ������ '%s' �� ������������ � ������� %d", className[classID], indexID);
			return NULL;
		}
		CObjIndex_AVTree_Item * pStartItem = pIndexTree->ItemPointer (old_coIndexPtr);
		if (pStartItem == NULL)
		{
			SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: ������ ��������� �������� ������� %d ��� ������ ������ '%s' �� ������������ � ������� %d", indexID, className[classID]);
			return NULL;
		}

	//----------------------------------------------------------------------------[] 
	// ������� ���������/���������� ������
		bool bContinue = false;
		do 
		{
			bContinue = false;
			if (bSame)
			{
				coIndexPtr = ((findType == OBD_FIND_Prev)? pIndexTree->PrevWithSameKey (old_coIndexPtr): pIndexTree->NextWithSameKey (old_coIndexPtr));
			}
			else
			{
				coIndexPtr = ((findType == OBD_FIND_Prev)? pIndexTree->Prev (old_coIndexPtr): pIndexTree->Next (old_coIndexPtr));
			}

			if (coIndexPtr && pka!=NULL && !bSame)
			{
				CObjIndex_AVTree_Item * pNextPrevItem = pIndexTree->ItemPointer (coIndexPtr);
				if (pNextPrevItem == NULL)
				{
					SERVER_DEBUG_ERROR_2 ("OBD_IndexNextPrevFirstLastObject: ������ ��������� �������� ������� %d ��� ������ ������ '%s' �� ������������ � ������� %d", indexID, className[classID]);
					return NULL;
				}
				pbyte arg0 = pStartItem->GetPtr   ();	// ����������� ������ ����
				pbyte arg1 = pka->GetPtr          ();	// ���� ������
				pbyte arg2 = pNextPrevItem->GetPtr();	// ������ ���� ���������� �������

			// ���� ��������� �� �������� -- ������ �� �����
				if (CompareFunction_CObjIndex_AVTree_Item (arg1, arg2)!=0)
				{
					coIndexPtr = NULL;
				}

			// ���� ��������� ��������, �� ���� �������� � ���������
				if (coIndexPtr && bUnique)
				{
				// ���� ��������� ��������, �� �� ����� ���������� -- ����� ������
					IGNORE_LAST_KEY_IDENTIFIER = true;
					{
						if ((CompareFunction_CObjIndex_AVTree_Item (arg0, arg2)==0))
						{
							old_coIndexPtr = coIndexPtr;
							bContinue		= true;
						}
					}
					IGNORE_LAST_KEY_IDENTIFIER = false;
				}
			}
		} while (bContinue);
	// ����� ���������/���������� ������
	//----------------------------------------------------------------------------[] 
	}
	else if (findType == OBD_FIND_First)
	{
		coIndexPtr = pIndexTree->First ();
	}
	else if (findType == OBD_FIND_Last)
	{
		coIndexPtr = pIndexTree->Last ();
	}

// ������� ��������� ����������������� ����
	if (pka){
		delete pka;
	}

	
// ���� ����� -- ��������� ������
	if (coIndexPtr)
	{
		CObjIndex_AVTree_Item * pItem = pIndexTree->ItemPointer (coIndexPtr);
		if (pItem)
		{
			return OBD_GetObject (classID, pItem->GetObjID (), indexID, coIndexPtr);
		}
		else
		{
			SERVER_DEBUG_ERROR ("OBD_IndexNextPrevFirstLastObject: ������ ��� ������ �������: pIndexTree->ItemPointer (coIndexPtr)==NULL");
			return NULL;
		}
	}
	return NULL;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ����� ��������� ������																		[]
//                                                                            []
OBD_pointer OBD_IndexNextObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame)
{
	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Next, pka, bUnique, bSame);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ����� ����������	������																	[]
//                                                                            []
OBD_pointer OBD_IndexPrevObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr, key_arr *pka, bool bUnique, bool bSame)
{
	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Prev, pka, bUnique, bSame);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ����� ������	������																		[]
//                                                                            []
OBD_pointer OBD_IndexFirstObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr)
{
	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_First, NULL, false);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ����� ��������� ������																		[]
//                                                                            []
OBD_pointer OBD_IndexLastObject (long classID, const CIndexInfo& indexInfo, OBD_pointer coPtr)
{
	return OBD_IndexNextPrevFirstLastObject (classID, indexInfo, coPtr, OBD_FIND_Last, NULL, false);
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ��������� ����������� ������															[]
//                                                                            []	
void OBD_SaveIndexToFile (long classID, const CIndexInfo& indexInfo)
{
	identifier indexID = indexInfo.m_id;
	if (indexID>=(size_t)theObjDriver.m_FormatArr[classID].indexArr.GetSize())
	{
		SERVER_DEBUG_ERROR (indexID==NA?"OBD_SaveIndexToFile: �������� ������� �� ����������":"OBD_SaveIndexToFile: �������� ������� ������� �� �����");
		return;
	}
	CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
	pObjDriveIndex->Save ();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ��������� ��� ��������� ������															[]
//                                                                            []	
void OBD_SaveAllData ()
{
	int indexID;
	int classID;

// ��������� ��� ������� ���� �������
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

	// ��������� ��� �������
		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Save ();
		}
	}

// ��������� ��� �������, ����������� � ������
	OBD_pointer coPtr = OBD_AllObjectsInMemory.First ();
	while (coPtr)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR ("OBD_SaveAllData: ������ ������ �������:  aObject==NULL");
			continue;
		}
		else if (!aObject->Save ())
		{
			OD_BASE * pBase = (OD_BASE *) (aObject->pData);
			identifier classID = pBase->classID;
			SERVER_DEBUG_ERROR_3 ("OBD_SaveAllData: ������ ������ ������� id=%d ������ '%s' (%d):  !aObject->Save ()", aObject->objID, className[classID], classID);
		}
		
		coPtr = OBD_AllObjectsInMemory.Next (coPtr);
	}

// ��������� ��������� � �������� �������
	theFileDriver.flush();
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` ����������� ��� �������																	[]
//                                                                            []	
void OBD_ReloadAllBase ()
{
	int indexID;
	int classID;

// ���������� ��������� � ������ ��� ���� ��������, ����������� � ������
	OBD_pointer coPtr = OBD_AllObjectsInMemory.First ();
	while (coPtr)
	{
		CAbstractObjectInMemory * aObject = OBD_AllObjectsInMemory.ItemPointer (coPtr);
		if (aObject==NULL)
		{
			SERVER_DEBUG_ERROR ("OBD_SaveAllData: ������ ������ �������:  aObject==NULL");
			return;
		}
		else
		{
			OD_BASE * pBase = (OD_BASE *) (aObject->pData);
			identifier classID = pBase->classID;
			int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();
			for (indexID=0; indexID < IndexNum;  indexID++)
			{
				pData_m_CoIndexPtr (classID, aObject->pData, indexID, NULL);
			}
			if (!aObject->Save ())
			{
				OD_BASE * pBase = (OD_BASE *) (aObject->pData);
				identifier classID = pBase->classID;
				SERVER_DEBUG_ERROR_3 ("OBD_SaveAllData: ������ ������ ������� id=%d ������ '%s' (%d):  !aObject->Save ()", aObject->objID, className[classID], classID);
			}
		}
		coPtr = OBD_AllObjectsInMemory.Next (coPtr);
	}

// ��������� ��� �������
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();
		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Save ();
		}
	}

// ��������� ��������� � �������� �������
	theFileDriver.flush();

// ��������� ��� �������
	for (classID=0; classID < (int)theObjDriver.m_FormatArr.GetSize(); classID++) 
	{
		int IndexNum = theObjDriver.m_FormatArr[classID].indexArr.GetSize();

		for (indexID=0; indexID < IndexNum;  indexID++)
		{
			CObjIndex * pObjDriveIndex = theObjDriver.GetIndexPtr (classID, indexID);
			pObjDriveIndex->Load ();
		}
	}
}
//____________________________________________________________________________[]

#endif









/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
