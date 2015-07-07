/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:				MOD_UserGroup.pvt.cpp													[]
[] Date:          01.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������� ���� �������������								[]
[]						���������� �������.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserGroup.inc.h"



//______________________________________________________________________________
//                                                                            []
//` �������� ���� ����� � ��������� ������                                    []                                      
//                                                                            []
void AddRootsToGroup (identifier groupID, identifier loginID)
{
	DEBUG_STACK_NAME (AddRootsToGroup);

	identifier rootGroupID = GetGroupIDByType ("root");
	if (rootGroupID!=NA)
	{
		OC_UserGroup oc_root_group (rootGroupID);
		for (int r=0; r<oc_root_group.m_UserID.Size(); r++)
		{
			identifier rootID = oc_root_group.m_UserID[r];
			if (!OC_Exist (OBJ_CLASS_ID_User, rootID))
			{
				SERVER_DEBUG_ERROR_1 ("���������� ������� ������������ [%d]. ����������.", rootID);
				oc_root_group.m_UserID.Del (r);
				r--;
				continue;
			}
		// ������� ������������ ������� ������ ���������� � ��������� ������
		// � ��� ������� �������, ������� �� ����� � ������� ������, ���� ������ 
		// �� �� ��� ����� ������������, ��� ������ ������.
			if (loginID!=rootID) AddUserToGroup (rootID, groupID);
		}
	}
	else if (!IGNORE_AUTHORIZATION)
	{
		SERVER_DEBUG_ERROR ("�� ������� ���������� ��������� ������ � ����� 'root'");
	}
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` �������� ������������� ������ ���� �� � �����                            []                                              
//                                                                            []
identifier GetGroupID (const char * Name, bool JustCheck)
{
	DEBUG_STACK_NAME (GetGroupID);

	OC_UserGroup oc_group;
	oc_group.SetIndex_Name ();
	if (oc_group.Find (Name))
	{
		identifier groupID = oc_group.GetObjectID ();
		if (oc_group.GoNextSame ())
		{
			SERVER_DEBUG_ERROR_1 ("���������� ������������ ��� ������ %s", Name);			
		}
		return groupID;
	}

	if (!JustCheck)
	{
		SERVER_DEBUG_ERROR_1 ("������ � ������ [%s] �� �������", Name);
	}
	
	return NA;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� ������������� ��������� ������ �� � ����								[]
//                                                                            []
identifier GetGroupIDByType (const char * Type)
{
	DEBUG_STACK_NAME (GetGroupIDByType);

	string strType (Type);

	OC_UserGroup oc_group;
	oc_group.SetIndex_Type ();
	if (!oc_group.Find (Type))
	{
		if (!IGNORE_AUTHORIZATION)
		{
			SERVER_DEBUG_ERROR_1 ("�� ������� ����� ������ � ����� %s.", Type);
		}
		return NA;
	}
	if (oc_group.m_AccessLevelThreshold!=0)
	{
		SERVER_DEBUG_ERROR_3 ("����� ������� ������ %s ���� %s ������ ���� ����� SYSTEM_ACCESS_LEVEL (0), � �� %d", string(oc_group.m_Name).c_str(), Type, int (oc_group.m_AccessLevelThreshold));
	}


	return oc_group.GetObjectID();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` �������� �������� ���� ������                                             []                             
//                                                                            []
const char* GetGroupRights (identifier groupID, bool bExpand)
{
	DEBUG_STACK_NAME (GetGroupRights);

	// ������: 
	// feodID|��������|feodName\nfeodID|��������|feodName\n...feodID|��������|feodName

	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("�� ������� ������ [%d]", groupID);
		return "";
	}
	OC_UserGroup oc_group (groupID);


	static string Result;
	Result = ""; // ������������ ����, ��� ��� "static"

//	���������� �� ���� ������ ������
	for (int f=0; f<oc_group.m_Rights_Feod.Size(); f++)
	{
		string strFeodID;
		string strFeodName;

		identifier feodID = oc_group.m_Rights_Feod[f];
		if (!CHECK_FEOD_ID(feodID))
		{
			SERVER_DEBUG_ERROR_2 ("���������� ID ���� ������� (%d) � ������ %s. ����������.", feodID, ((string)oc_group.m_Name).c_str());
			oc_group.m_Rights_Feod.Del (f);
			oc_group.m_Rights_Attr.Del (f);
			f--;
			continue;
		}

	// ���� ��������� ���������� ��� �������� ���� �������, �� ������ ���
		identifier_arr allFeods;
		if (bExpand)
		{
			GetAllFeodChilds	(feodID, allFeods);
			allFeods.Insert	(0, feodID);
		}
		else
		{
			allFeods += feodID;
		}

	// ��������� ���������
		for (int i=0; i<allFeods.Size(); i++)
		{
			if (GetFeodFullName (allFeods[i], strFeodName, 1, "::"))
			{
				string strFeodType;
				GetFeodType (allFeods[i], strFeodType);
				strFeodID.Format ("%d", allFeods[i]);
				Result += "\n";
				Result += strFeodID;
				Result += "|";
				Result += oc_group.m_Rights_Attr[f];
				Result += "|";
				Result += strFeodName;
				Result += "|";
				Result += strFeodType;
			}
			else
			{
				SERVER_DEBUG_ERROR ("��������� ���������� ����, �������� ��������� �������� ������� ������� FIX_FEODS.");
				FIX_FEODS ();
			}
		}
	}

	return Result.c_str();
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` CreateUserGroup                                                           []               
//                                                                            []
ERR_RESULT CreateUserGroup (const char* Name, const char* Type, const char* Description, int AccessLevelThreshold, const char* sFeodAttr)
{
	DEBUG_STACK_NAME (CreateUserGroup);

// ��� ������ ������ ���� ����������
	if (GetGroupID (Name, true)!=NA)
	{
		return ERR_NameAlreadyExists;
	}

// ��������� ������� ������ �� ������� -- ���� ������� � ������ �������
	string		FeodAttrStr (sFeodAttr);
	string_arr	FeodAttrArr;

	FeodAttrStr.explode	(FeodAttrArr, "]");
	FOR_EACH_ITEM			(FeodAttrArr, trim);


// ������ ������ � ��������� � �� ����������� ����� (���� ������� � ������ �������)
	OC_UserGroup oc_group;
	identifier groupID = oc_group.New ();

	oc_group.m_Name						=	Name;
	oc_group.m_Description				=	Description;
	oc_group.m_AccessLevelThreshold	=	AccessLevelThreshold;
	oc_group.m_CreationTime				=	time(0);
	oc_group.m_Type						=  Type;

	FOR_EACH_ITEM_EVAL (FeodAttrArr, 
	{
		if (FeodAttrArr[i].IsEmpty()) continue;
		string_arr FA;
		FeodAttrArr[i].explode	(FA, "[");
		FOR_EACH_ITEM				(FA, trim);
		string sFeod=FA[0];
		string sAttr=FA[1];
		identifier feodID = GetFeodIDByType (sFeod);
		if (feodID!=NA)
		{
		// ��������� ������������ ���������
			if (!CHECK_ATTRIBUTES (sAttr))
			{
				continue;
			}
			oc_group.m_Rights_Feod.Add (feodID);
			oc_group.m_Rights_Attr.Add (sAttr);
		}
		else
		{
			SERVER_DEBUG_ERROR_1 ("��� ����� ���� �������: %s", sFeod.c_str());
		}
	});

// ��������� ���� ����� � ��������� ������
	AddRootsToGroup (groupID, NA);


	return ERR_OK;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` ��������� ����� ���� ������                                               []
//                                                                            []
void UserGroupSimplifyRightsSet	(identifier groupID)
{
	DEBUG_STACK_NAME (UserGroupSimplifyRightsSet);

	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("�� ������� ������ [%d]", groupID);
		return;
	}
	OC_UserGroup oc_group (groupID);

	identifier_arr FeodArr	= oc_group.m_Rights_Feod;
	string_arr		AttrArr	= oc_group.m_Rights_Attr;

// �������� �� ������������ ������������ ��������
	SERVER_DEBUG_ASSERT (FeodArr.Size() == AttrArr.Size(), "������ ������� �������� ��� ���� � �� ���������");

// ��������� ���������� ������������ ����� �������� ������ ������ "INTERNAL COMPILER ERROR" � VC++ 6.0
	static int f,r;

// �������� ������ �� ������������
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (!CHECK_FEOD_ID(FeodArr[f]))
		{
			SERVER_DEBUG_ERROR_2 ("���������� ID ���� ������� (%d) � ������ %s. ����������.", FeodArr[f], ((string)oc_group.m_Name).c_str());
			FeodArr.Del (f);
			AttrArr.Del (f);
			f--;
			continue;
		}
	}

//	���������� ������������ � ������� ��������� ��� ���������� ���
	for (f=0; f<FeodArr.Size(); f++)
	{
		for (r=f+1; r<FeodArr.Size(); r++) if (FeodArr[f]==FeodArr[r])
		{
		// ������� ��� ���������� ����� -- ����� ����� ����������
			for (int a=0; a<(int)AttrArr[r].Len(); a++)
			{
			// �� ������ ����� ���� �������, �� �������������� � ������, ��� ���� ��������� � ������ �����
				if (AttrArr[f].Find(AttrArr[r][a])==-1)
				{
					AttrArr[f]+=AttrArr[r][a];
				}
			}
		// ������� ������������� �����
			FeodArr.Del(r);
			AttrArr.Del(r);
			r--;
		}
	}

//	���������� ��������� ����.
	for (f=0; f<FeodArr.Size(); f++)
	{
		for (r=f+1; r<FeodArr.Size(); r++) if (FeodHasChild (FeodArr[f], FeodArr[r]))
		{
		// ������ ���� ��������� �� �������, ���� �� �� ����� ����� ���������, ����� ��� � �������, ��� ������� ��������
			bool bHasUniqueAttr = false;
			for (int a=0; a<(int)AttrArr[r].Len(); a++)
			{
			// �� ������, ����� �������, ����� ���� �������, �� �������������� � ������, ����� �����. ������� ����� ���� ���������.
				if (AttrArr[f].Find(AttrArr[r][a])==-1)
				{
					bHasUniqueAttr = true;
					break;
				}
			}
			if (!bHasUniqueAttr)
			{
			// ������� ��������� ��������� �����
				FeodArr.Del(r);
				AttrArr.Del(r);
				r--;
			}
		}
	}

// ����������� � ������ ���������� ����� ����
	oc_group.m_Rights_Feod	=	FeodArr;
	oc_group.m_Rights_Attr	=	AttrArr;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/