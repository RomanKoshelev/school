/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFile.cpp															[]
[] Date:          4.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � �������.															[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFile.inc.h"








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ �����																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_New (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_New);
/*............................................................................[]
		<Login                  ����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� ������ �� ���� ��������� ������.
		<Password               ������ ������������, �������������� ��������.

		<Name                   ��� ������������ �����.
		<Description            �������� ������������ �����.
		<Name_Upload				���, ��� ������� ���� ����������.
		<OS_Path						������ ���� � ���� �����, ��� ������� ����� ������� ����� �����.
		<OS_Ext						���������� �����. ������ ��� OS-����� ����� ��������� = <OS_Path><objID>.<OS_ext>
		<MIMEType					MIME-���, ��������: "image/jpeg", "object-link/InfoObject"
		<IconType					���������������� ��������� ��������, ��� ����������� ������.
		<PlainTextData				����� ���������� ���������� �����, ���� ��������.
		<BinaryData					�������� ���������� �����.
		<folderIDs					� ����� ������ ����� ���������� ������.

		>objID                  ������������� ���������� �������.
		>ExitCode               ��� ��������.
		>ExitCodeComment        ��������� ����������� � ���� ��������.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����� ������ ������������
	int f;
	for (f=0; f<arg.folderIDs.Size(); f++) if (!CHECK_WEBFOLDER_ID (arg.folderIDs[f]))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������� ������������ ����� ID=%d", arg.folderIDs[f]);
	}

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}

// ������������ ������ ����� ����� ��������� ������� � ��������� ������
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		OC_WebFolder oc_folder (arg.folderIDs[f]);
		res=USER_CHECK_ACCESS (loginID, guid(oc_folder.m_MOD_Base_GUID).id, "C");
		if (res!=ERR_OK)
		{
			string folderName;
			GetWebFolderFullName (arg.folderIDs[f], folderName);
			ERR_RETURN_COMMENT_3 (res, "������������ %s �� ����� ����� ��������� ������� � ����� '%s'[%d]", arg.Login.c_str(), folderName.c_str(), arg.folderIDs[f]);
		}
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ����������� ��� ����� �� ������ ���� ������
	if (arg.Name_Upload.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "����������� ��� ����� �� ������ ���� ������");
	}
// ���� ��� ������ -- ��g������� Name_Upload
	if (arg.Name.IsEmpty())
	{
		arg.Name = arg.Name_Upload;
	}
// ������ ���� ������� ����-�� ���� �����
	if (arg.folderIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "������ ���� ������� ����-�� ���� �����");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ���� � ���������� ��� � �����
	OC_WebFile oc_file;
	identifier fileID = oc_file.New ();
	guid	fileGUID		= oc_file.GetObjectGUID();
	string OSName;
	OSName.Format ("%s%u.%s", arg.OS_Path.c_str(), fileID, arg.OS_Ext.c_str());
	time_t CurTime	= time (0);


	FULL_INDEX_BEGIN (oc_file);
	{
		oc_file.m_Name						=	arg.Name;
		oc_file.m_Description			=	arg.Description;
		oc_file.m_Name_Upload			=	arg.Name_Upload;
		oc_file.m_Name_OSFile			=	OSName;
		oc_file.m_MIMEType				=	arg.MIMEType;
		oc_file.m_IconType				=	arg.IconType;

		oc_file.m_Text						=	arg.PlainTextData;
		oc_file.m_BinaryData				=	arg.BinaryData;

		oc_file.m_CreationTime			=	CurTime;
		oc_file.m_ModificationTime		=	CurTime;
		oc_file.m_LastAccessTime		=	CurTime;
		oc_file.m_OwnerGUID				=	GetUserGUID (loginID);
	}
	FULL_INDEX_END (oc_file);

// ��������� ���� � �����
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		OC_WebFolder oc_folder (arg.folderIDs[f]);
		oc_folder.m_WebFileSortedID.InsertSorted (fileID);
	}

	arg.objID = fileID;
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ �����																			[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_Enumerate (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ��������� ������.
		<Password					������ ������������, �������������� ��������.
		<objFirstNo					����� �������, � �������� �� �����������.
		<objLastNo					����� ���������� �������������� �������.
		<folderID					� ����� ����� ������ ������������ ����. ���� �� ������� -- �������� �� folderName.
		<folderName					� ����� � ����� ������ ������ ������������ ����, ���� �� ������ folderID. ������ ��� ���� "Concept.Feod.Files.Site".
		<UpdateStatistics			���� �� �������� ���������� �������/������/CTR ������������� ������.

		>objIDs						������ ��������������� ��������.
		>objNames					������ �������� ��������.
		>objOSNames					�����, ��� �������� ����� ����������� �� �������, ��������, files/435662.jpg
		>objIconTypes				���������������� ��������� ��������, ��� ����������� ������.
		>objDescriptions			������ �������� �������� (������).
		>objCreationTimes			������� �������� ������.
		>objStatShows				������� ��� ���� ��� �������
		>objStatClicks				������� ��� ���� ��� ����������� ��� ���������
		>objStatCTRs				objStatClicks*100/objStatShows
		>TotalStoredNum			������� ����� ������ ����� ���� �����������.
		>MaxNumInQuery				����������� ���������� ����� ������������� �� ���� ��� ������.
		>ExitCode					��� ��������.
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]

	

//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
// ���� �� ������ ID �����, ���� �� �����.
	if (arg.folderID==NA)
	{
		arg.folderID = GetWebFolderIDByType (arg.folderName);
	}
// ����� ������ ������������
	if (!CHECK_WEBFOLDER_ID (arg.folderID)) 
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������� �������������� ����� ID=%d", arg.folderID);
	}

// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_WEBFILE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_WEBFILE_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}

// ������������ ������ ����� ����� ��������� ������ ������ � ��������� �����.
	res = USER_CHECK_ACCESS (loginID, guid(OC_WebFolder(arg.folderID).m_MOD_Base_GUID).id, "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_2 (ERR_AccessDeny, "������������ %s �� ������ ����� �������� ������ � ��������� ����� %u", arg.Login.c_str(), arg.folderID);
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ���������� ���� ����� ��� �����������, ��� ��� ����� ������ VC++6.0 
//	����� INTERNAL COMPILER ERROR
	static int i=0;

// ������� ��� �������������� ������, ��������������� �� �����
	OC_WebFile oc_file;
	oc_file.SetIndex_Name ();
	identifier_arr fileIDs;
	oc_file.GetClassIdList (fileIDs);


// ��������� ������ �� �����, ������� ��������� � ��������� �����
	identifier_arr oc_folder_m_WebFileSortedID;
	WebFolderGetWebFileSortedIDs (arg.folderID, oc_folder_m_WebFileSortedID);
// ���� ����� � ������������� ������
	for (i=0; i<fileIDs.Size(); i++)	if (oc_folder_m_WebFileSortedID.Find (fileIDs[i], true)==-1)
	{
	// ���� �� ������ -- ���������� ���
		fileIDs.Del (i);
		i--;
	}

// fileIDs -- ��� ����� ������������� ����� 
// ��������� ����������� ����������.
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<fileIDs.Size(); i++)
	{
		if (!OC_Exist (OBJ_CLASS_ID_WebFile, fileIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("������������ ������������� ����� %d", fileIDs[i]);
			continue;
		}
		OC_WebFile oc_file (fileIDs[i]);
		
		arg.objIDs				+= fileIDs[i];
		arg.objNames			+=	oc_file.m_Name;
		arg.objDescriptions	+=	oc_file.m_Description;
		arg.objCreationTimes	+=	oc_file.m_CreationTime;
		arg.objOSNames			+=	oc_file.m_Name_OSFile;
		arg.objIconTypes		+=	oc_file.m_IconType;

		arg.objStatShows		+= oc_file.m_ShowCount;
		arg.objStatClicks		+=	oc_file.m_ClickCount;
		arg.objStatCTRs		+=	oc_file.m_CTR;

	// ���� ����������, �������� ����������.
		if (arg.UpdateStatistics)
		{
			oc_file.m_ShowCount	+= 1;
			if (oc_file.m_ShowCount!=0)
			{
				oc_file.m_CTR = (oc_file.m_ClickCount*100)/float(int(oc_file.m_ShowCount));
			}
		// !!! �������� ���������� � �����
		}
	}

	arg.TotalStoredNum = fileIDs.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ �����																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_GetData (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_GetData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ������ "R" ���� �� � ����� �����, ���������� ����.
		<Password					������ ������������, �������������� ��������.
		<objID						������������� �������������� ��������������� �������.
		<UpdateStatistics			���� �� �������� ���������� �������/������/CTR.
		<NeedBinaryData			����� �� ���������� �������� ����������.
		<NeedPlainTextData		����� �� ���������� ��������� �����.

		>Name							�������� �����.
		>Name_Upload				���, ��� ������� ���� ����������.
		>Name_OS						���, ��� ������� ���� ����������� �� �������, ��������, files/435662.jpg
		>Description				�������� �����.

		>CreationTime				����� �������� �����.
		>Version						����� ����������� �����.
		>MIMEType					MIME-���, ��������: "image/jpeg", "object-link/InfoObject"
		>IconType					���������������� ��������� ��������, ��� ����������� ������.

		>BinaryData					�������� ���������� �����, ���� ����������.
		>PlainTextData				����� ���������� ���������� �����, ���� ����������.

		>OwnerID						��������� �����. [User]
		>folderIDs					� ����� ������ ��������� ����. (������������� ������ ��, � ������� ���� ������ [L])
		>folderNames				����� �����.

		>StatShow					������� ��� ������ ��� �������
		>StatClick					������� ��� ������ ��� ����������� ��� ���������
		>StatCTR						objStatView*100/objStatShow

		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ���� ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFile, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ���� %d �� ����������", arg.objID);
	}
	OC_WebFile oc_file (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// �������� ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}

// ������������ ������ ����� ����� ������ ����� ���� �� � ����� �� �����, � ������� ��� �����
	bool bAccess=false;
	int f;
	for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (oc_file.m_WebFolderID[f]), "R");
		if (res==ERR_OK)
		{
			bAccess = true;
			break;
		}
	}
	if (!bAccess)
	{
		ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "������������ %s �� ������ ����� ������ ��������� ����", arg.Login.c_str());
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���� ����������, �������� ����������.
	if (arg.UpdateStatistics)
	{
		oc_file.m_ClickCount	+= 1;
		if (oc_file.m_ShowCount!=0)
		{
			oc_file.m_CTR = (oc_file.m_ClickCount*100)/float(int(oc_file.m_ShowCount));
		}
	// !!! �������� ���������� � �����
	}
	oc_file.m_LastAccessTime = time(0);

// ��������� �������� ���������
	arg.Name					=	oc_file.m_Name;
	arg.Description		=	oc_file.m_Description;

	arg.Name_Upload		=	oc_file.m_Name_Upload;
	arg.Name_OS				=	oc_file.m_Name_OSFile;

	arg.CreationTime		=	oc_file.m_CreationTime;
	arg.Version				=	oc_file.m_Version;
	arg.MIMEType			=	oc_file.m_MIMEType;
	arg.IconType			=	oc_file.m_IconType;

	arg.StatShow			=	oc_file.m_ShowCount;
	arg.StatClick			=	oc_file.m_ClickCount;
	arg.StatCTR				=	oc_file.m_CTR;

	if (arg.NeedBinaryData)					arg.BinaryData			= oc_file.m_BinaryData;
	if (arg.NeedPlainTextData)				arg.PlainTextData		= oc_file.m_Text;

	if (OC_Exist(oc_file.m_OwnerGUID))	arg.OwnerID				=	guid(oc_file.m_OwnerGUID).id;
	else											oc_file.m_OwnerGUID	=	guid ((char)0);


// ����������� �� �������, � ������� ������������ ����� ������� ����
	for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		identifier folderID = oc_file.m_WebFolderID[f];
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (folderID), "L");
		if (res==ERR_OK)
		{
			string folderFullName;
			if (GetWebFolderFullName (folderID, folderFullName))
			{
				arg.folderIDs	+=	folderID;
				arg.folderNames+=	folderFullName;
			}
			else
			{
				SERVER_DEBUG_ERROR_2 ("������������ ������������� ����� %d � ����� %d", identifier (folderID), arg.objID);
			}
		}
	}
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ �����																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_PutData (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_PutData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ������ "W" ���� �� � ����� �����, ���������� ���� ��� ���� ���������� �����.
		<Password					������ ������������, �������������� ��������.

		<objID						������������� �������������� ��������������� �����.
		<Name							����� ��� �����.
		<Description				�������� �����.
		<MIMEType					MIME-���, ��������: "image/jpeg", "object-link/InfoObject"
		<IconType					���������������� ��������� ��������, ��� ����������� ������. ������.

		<ContentChanged			���� true, ������ ���������� ���������� � ����������� ���� Name_Upload, OS_Path, OS_Ext, BinaryData � PlainTextData.
		<Name_Upload				���, ��� ������� ����������� ����.
		<OS_Path						������ ���� � ���� �����, ��� ������� ����� ������� ����� �����.
		<OS_Ext						���������� �����. ������ ��� OS-����� ����� ��������� = <OS_Path><objID>.<OS_ext>
		<PlainTextData				����� ���������� ���������� �����, ����������� ���� ContentChanged==true.
		<BinaryData					�������� ���������� �����, ����������� ���� ContentChanged==true.

		<folderIDs					� ����� ������, �� ������ ������, ������ ���������� ����. ����� �� ����� �������� ���� �� ����� ��� ������� [D] � �������� � ����� ��� ������� [C]. ���� ������ ������ ����-�� � ����� �����.

		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ���������� ������������ ����� �������� ������ ������ "INTERNAL COMPILER ERROR" � VC++ 6.0
	static int f;

// ������������� ���� ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_WebFile, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ���� %d �� ����������", arg.objID);
	}
	OC_WebFile oc_file (arg.objID);

// �������� ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
	guid loginGUID = GetUserGUID (loginID);

// ������������ ������ ����� ����� �������������� ����� ���� �� � ����� ����� ��� ���� ���������� �����
	bool	 bAccess = (guid(oc_file.m_OwnerGUID) == loginGUID);
	if (!bAccess) for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (oc_file.m_WebFolderID[f]), "W");
		if (res==ERR_OK)
		{
			bAccess = true;
			break;
		}
	}
	if (!bAccess)
	{
		ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "������������ %s �� ������ �������� ��������� ����", arg.Login.c_str());
	}
//----------------------------------------------------------------------------[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ������� �� ������ ���� ������
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "��� ����� �� ����� ���� ������");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ���������� ������ �� ��������:
// arg.folderIDs -- � ����� ������, �� ������ ������, ������ ������������ ����.
// ����� �� ����� �������� ���� �� ����� ��� ������� [D] � �������� � ����� ��� ������� [C].
	identifier_arr new_folder_arr = oc_file.m_WebFolderID;

// ���������� �� ������ ������� � �������, ����� �� ��� �� ������� �������������, �.�. �� ����� �� ��������
	for (f=0; f<new_folder_arr.Size(); f++)
	{
		identifier folderID = new_folder_arr[f];
		if (arg.folderIDs.Find(folderID)==-1)
		{
		// ������������ �����, ��� ���� �� ������ ���������� � ����� folderID
			if (USER_CHECK_ACCESS_TO_WEBFOLDER (loginID, folderID, "D")==ERR_OK)
			{
			// ������������ ����� ����� �������� ���� �� �����
				new_folder_arr.Del (f);
				f--;
			// ���������� ���� �� �����
				OC_WebFolder oc_folder (folderID);
				int nIndex = oc_folder.m_WebFileSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_folder.m_WebFileSortedID.Del (nIndex);
				}
			}
		}
	}

// ���������� �� ������, ��������� �������������� � �������, ����� �� ��� ��� � �����, �.�. �� ����� �� ��������
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		identifier folderID = arg.folderIDs[f];
		if (new_folder_arr.Find(folderID)==-1)
		{
		// ������������ �����, ��� ���� ������ ���������� � ����� folderID
			if (USER_CHECK_ACCESS_TO_WEBFOLDER (loginID, folderID, "C")==ERR_OK)
			{
			// ������������ ����� ����� �������� ���� � �����
				new_folder_arr.Add (folderID);
				OC_WebFolder (folderID).m_WebFileSortedID.InsertSorted (arg.objID);
			}
		}
	}

// �������� �������������� ������� ������
	if (new_folder_arr.Size()!=0)	oc_file.m_WebFolderID = new_folder_arr;
	else									ERR_RETURN_COMMENT (ERR_BadArgument, "���� ������ ���������� ����-�� ����� �����");


// �������� ������� ���� �����
	FULL_INDEX_BEGIN (oc_file);
	{
		oc_file.m_Name						=	arg.Name;
		oc_file.m_Description			=	arg.Description;
		oc_file.m_MIMEType				=	arg.MIMEType;
		oc_file.m_IconType				=	arg.IconType;
		oc_file.m_ModificationTime		=	time(0);
	}
	FULL_INDEX_END (oc_file);

	if (arg.ContentChanged)
	{
		string OSName;
		OSName.Format ("%s%u.%s", arg.OS_Path.c_str(), arg.objID, arg.OS_Ext.c_str());
		oc_file.m_Text					=	arg.PlainTextData;
		oc_file.m_BinaryData			=	arg.BinaryData;
		oc_file.m_Name_OSFile		=	OSName;
		oc_file.m_Name_Upload		=	arg.Name_Upload;
		oc_file.m_Version				+=	1;
	}

//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]







// !! ��� �������� ������� ���������� ��� �� �������!







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/