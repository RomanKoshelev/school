/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_InfoObject.cpp														[]
[] Date:          16.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   ������ � ��������������� ���������.									[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_InfoObject.inc.h"


//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` �������� ������ ��������������� �������												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_New (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_New);
/*............................................................................[]
		<Login                  ����� ������������, �������������� ��������. ������������ ������ �������� ������� �������� �������� �� ���� ��������� ��������.
		<Password               ������ ������������, �������������� ��������.
		<Name                   ��� ������������ �������.
		<Description            �������� ������������ �������.
		<Text							������ ����������.
		<InfoSourceID				�������� ����������.
		<URL							����������� URL
		<RelatedLinks				������ �� ����
		<divIDs						� ����� �������������� �������� ����� ���������� ������.
		<InfoTime					�����, ����������� � ��������������� �������. ���� �� ������� -- ������� �����.
		<AuthorStr					��� ������, �� ����������� �������������

		>objID                  ������������� ���������� �������.
		>ProxyID						��� ������������� ���� -- ������������� ���������������� ������-�������.

		>ExitCode               ��� �������� (OK BadID BadLogin BadPassword AccessDeny InsufficientAccessLevel).
		>ExitCodeComment        ��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������� ������ ������������
	int d;
	for (d=0; d<arg.divIDs.Size(); d++) if (!CHECK_INFODIV_ID (arg.divIDs[d]))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ ������������ �������������� ������ ID=%u", arg.divIDs[d]);
	}
// ���� �������� ������, �� �� ������ ������������
	if (arg.InfoSourceID!=NA && !OC_Exist (OBJ_CLASS_ID_InfoSource, arg.InfoSourceID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ �������������� �������� ���������� ID=%u", arg.InfoSourceID);
	}

// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}

// ������������ ������ ����� ����� ��������� ������� � ��������� ��������
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		OC_InfoDiv oc_div (arg.divIDs[d]);
		res=USER_CHECK_ACCESS (loginID, guid(oc_div.m_MOD_Base_GUID).id, "C");
		if (res!=ERR_OK)
		{
			string divName;
			GetInfoDivFullName (arg.divIDs[d], divName);
			ERR_RETURN_COMMENT_3 (res, "������������ %s �� ����� ����� ��������� ������� � ������� '%s'[%u]", arg.Login.c_str(), divName.c_str(), arg.divIDs[d]);
		}
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
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������� �� ������ ���� ������");
	}
// ���� �� ������� ����� �������, ������ ��� ������ ��������
	if (arg.InfoTime==0)
	{
		arg.InfoTime = time(0);
	}
// ��������� ������� ������������ ������ ��������

#if 0  //{ RomanVK
	identifier_arr subDivIDs;
	bool				bFound=false;
	{
	// ���� �� ���� ������ ������ ���� �����������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Mark"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� �����������, �.�. ����������� {Concept.Feod.Data.Mark}");}
	// ���� �� ���� ������ ������ ���� ���������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Service"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� ���������, �.�. ����������� {Concept.Feod.Data.Service}");}
	// ���� �� ���� ������ ������ ���� ������������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� ������������, �.�. ����������� {Concept.Feod.Data.Topic}");}
	// ���� �� ���� ������ ������ ���� ����� ��������������� ���������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Type"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� �������, �.�. ����������� {Concept.Feod.Data.Type}");}
	}
#endif //}
//----------------------------------------------------------------------------[] 


//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������ ������ � ���������� ��� � ������
	OC_InfoObject oc_info;
	oc_info.New ();
// ������ ������-������ ��� ������������� ����
	CHECK_PROXY_OBJECT_OF (oc_info);

	FULL_INDEX_BEGIN (oc_info);
		identifier infoID					= oc_info.GetObjectID ();
		oc_info.m_Name						= arg.Name;
		oc_info.m_Description			= arg.Description;
		oc_info.m_Text						= arg.Text;
		oc_info.m_OwnerGUID				= GetUserGUID (loginID);
		oc_info.m_URL						= arg.URL;
		oc_info.m_RelatedLinks			= arg.RelatedLinks;
		oc_info.m_InfoSourceID			= arg.InfoSourceID;
		oc_info.m_InfoDivID				= arg.divIDs;
		oc_info.m_CreationTime			= time(0);
		oc_info.m_InfoTime				= arg.InfoTime;
		oc_info.m_AuthorStr				= arg.AuthorStr;
	FULL_INDEX_END (oc_info);

// ��������� ������ � �������
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		OC_InfoDiv oc_div (arg.divIDs[d]);
		oc_div.m_InfoObjectSortedID.InsertSorted (infoID);
	}
//----------------------------------------------------------------------------[] 




	
//----------------------------------------------------------------------------[] 
// [Sonora]
// ������ � ������
//
	guid			loginGUID	=	GetUserGUID (loginID); 
	guid			objGUID		=	oc_info.GetObjectGUID (); 
	time_t		cur_Time		=	time(0);

	identifier_arr DivIDsarr;
	bool				bFound=false;
	string			strDivIDs;

// ���������� ���� ������������ - ������� � ����, ��� ������������ ������ ������
	UserProfileLogUpdate (loginID, USER_LOG_CREATE, objGUID, cur_Time);

//	���������� ���� ������� -- ������� � ����, ��� ������	������
	oc_info.m_Log_Action		+= INFOOBJ_ACTION_CREATE;
	oc_info.m_Log_UserGUID	+= loginGUID;
	oc_info.m_Log_Time		+=	cur_Time;
	oc_info.m_Log_Comment	+=	"";

// ���������� ���� ������������ - ������� � ����, ��� ������������ ������ ��������
	UserProfileLogUpdate (loginID, USER_LOG_ADDTOPIC, objGUID, cur_Time);

// �������� ��������������� ������ strDivIDs �� ��������� ������������� �������
	InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), DivIDsarr);
	for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) 
	{
		if (DivIDsarr.Find (arg.divIDs[d])!=-1) 
		{
			string tmplate;
			tmplate.Format	("+%lu ",arg.divIDs[d] );
			strDivIDs += tmplate;
		}
	}

// ���������� ���� ������� -- ������� � ����, ��������� ��������
	oc_info.m_Log_Action		+= INFOOBJ_ACTION_ADDTOPIC;
	oc_info.m_Log_UserGUID	+= loginGUID;
	oc_info.m_Log_Time		+=	cur_Time;
	oc_info.m_Log_Comment	+=	strDivIDs;

										 
// ������� ������ ������ ��������������� �������� ��� ������� CHECK_DIV_AND_SET_LOG_RECORD	
	identifier_arr InfoDivID;

//	���������, ���� �� ������ ��������������, ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Public",		PUBLIC, "", objGUID, InfoDivID, arg.divIDs);
//	���������, ���� �� ������ �����������, ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Forbidden",	FORBID, "", objGUID, InfoDivID, arg.divIDs);

//	���������, ���� �� ������ "������� ����������", ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Hot",	HOT, "", objGUID, InfoDivID, arg.divIDs);

//	���������, ���� �� ������ "������� ����������", ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Regular",	REGULAR, "", objGUID, InfoDivID, arg.divIDs);

	arg.objID	=	infoID;
	arg.ProxyID	=	guid(oc_info.m_ProxyObject).id;
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ������������ �������������� ��������													[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_Enumerate (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ��������� ������.
		<Password					������ ������������, �������������� ��������.
		<Time0						���������� ����� ����� ������� ��������. ������ ���������. �� ��������� = time(0);
		<Time1						���������� ����� ����� ������ ��������. ����� ���������. �� ��������� = (time_t)0;
		<objFirstNo					����� �������, � �������� �� �����������.
		<objLastNo					����� ���������� �������������� �������.
		<divIDs						� ����� �������� ������ ������������ ������. � ������������ ������ ���� ����� ��������� ������ [L] �� ���� ��������� ��������. ������ ������ ������������ ����� ���� ��������. ��������: "Concept.Feod.Data.Type.News.��������������.������" & "Concept.Feod.Data.Service.Process.Public" -- ��� �������� �������������� ������� ���������� "������". ���� �� ������� -- �������� �� divNames
		<divNames					� ����� �������� ������ ������������ ������, ���� �� ������� divIDs. ������ ����� ���� "Concept.Feod.Data.Type.News.��������������.�����".
		<divLookInSub				���� true -- ����������� ����� � ������� �� �����������. ��� ������� ������������� �� ������ ����.
		<divAttributes				������ ���� "CLWRD". ������������� ������� ������ ��� ��������, ������ � ������� ������ ���������� ����������.
		<UpdateStatistics			���� �� �������� ���������� �������/������/CTR ������������� ��������. ��������, ��� ������������� ���������� ��� �� ���� ������, � �� ����� ����� -- ����.
		<InfoSourceID				���� �� NA, �������� ������ ������� � ��������� ����������.
		<bNeedTotalStoredNum		��������� �� �������� ����� ����� ��������, ������� ����� ���� �����������.
		<bNeedText					���������� �� ������ � ��������� ����������� ��������. ���� ������������ �� ����� ����� [R] �� ���� ��������, � ������� ����� ������, ������������ ������ "{{ACCESS DENY}}"".
		<bNeedURL					���������� �� ������ � �������� ��������. ���� ������������ �� ����� ����� [R] �� ���� ��������, � ������� ����� ������, ������������ ������ "{{ACCESS DENY}}"".
		<bNeedLog					���� �� ���������� ���������� �� ���� (������, �����������, ...) (�� ��������� false) ���������� ���� ����� ����� ����� {Concept.Feod.Admin.User.Data}[R] ������������� ������ �������������.

		>objIDs						������ ��������������� ��������.
		>objProxyIDs				��� ������������� ���� -- ������ ��������������� ��������������� ������-��������.
		>objNames					������ �������� ��������.
		>objDescriptions			������ �������� �������� (������).

		>objLogCreatorIDs			�������������� ���������� (���, ���� ������� �� �������, �� ����������) ���������� (������ ���� bNeedLog == true).
		>objLogCreatorLogins		������ ���������� ���������� (������ ���� bNeedLog == true).
		>objLogCreatorNames		����� ���������� ���������� (������ ���� bNeedLog == true).

		>objLogPublisherIDs		�������������� ������������ ���������� (������ ���� bNeedLog == true).	
		>objLogPublisherLogins	������ ������������ ���������� (������ ���� bNeedLog == true).	
		>objLogPublisherNames	����� ������������ ���������� (������ ���� bNeedLog == true).		

		>objLogForbidderIDs		�������������� ������������ ���������� (������ ���� bNeedLog == true).	
		>objLogForbidderLogins	������ ������������ ���������� (������ ���� bNeedLog == true).	
		>objLogForbidderNames	����� ������������ ���������� (������ ���� bNeedLog == true).		

		>objLogHotterIDs			�������������� Hotter(��) ���������� (������ ���� bNeedLog == true).	
		>objLogHotterLogins		������ Hotter(��) ���������� (������ ���� bNeedLog == true).
		>objLogHotterNames		����� Hotter(��) ���������� (������ ���� bNeedLog == true).	


		>objTexts					������ ��������� ���������� ��������. ���� bNeedText=false, ������ ������ �����. ���� ��� ����� [R], {{ACCESS DENY}}
		>objURLs						������ ����������� web-������� ��������. ���� bNeedURL=false, ������ ������ �����. ���� ��� ����� [R], {{ACCESS DENY}}
		>objInfoTimes				�����, ����������� � ��������������� �������.
		>objStatShows				������� ��� ������ ��� �������
		>objStatClicks				������� ��� ������ ��� ����������� ��� ���������
		>objStatCTRs				objStatClicks*100/objStatShows
		>TotalStoredNum			������� ����� �������� ����� ���� �����������.
		>MaxNumInQuery				����������� ���������� ����� ������������� �� ���� ��� ��������.
		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny TooManyEnumerate).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]

	

//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
// ���� ������ ���������� ��������� �� �������, �� ������������ ������� �����
	if (arg.Time0==0)
	{
		arg.Time0 = time(0);
	}
// ���� �� ������� ID ��������, ���� �� �� �����, ������� ��������� � ����� ��������-�����.
	if (arg.divIDs.Size()==0)
	{
		FOR_EACH_ITEM_EVAL(arg.divNames, 
		{
			arg.divIDs += GetInfoDivIDByType (arg.divNames[i]);
		});
	}
// ������� ������ ������������
	FOR_EACH_ITEM_EVAL (arg.divIDs, {if (!CHECK_INFODIV_ID (arg.divIDs[i])) ERR_RETURN_COMMENT_1 (ERR_BadID, "������ �������������� �������������� ������ ID=%u", arg.divIDs[i]);});

// ���� �������� ������, �� �� ������ ������������
	if (arg.InfoSourceID!=NA && !OC_Exist (OBJ_CLASS_ID_InfoSource, arg.InfoSourceID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������ �������������� �������� ���������� ID=%u", arg.InfoSourceID);
	}

// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_INFOOBJECT_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_INFOOBJECT_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}

//	������ ���� ������ L
	if (arg.divAttributes.Find ("L")==-1)
	{
		arg.divAttributes += "L";
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

// ������������ ������ ����� ����� ��������� ������ �������� �� ���� ��������
	FOR_EACH_ITEM_EVAL (arg.divIDs,
		{
			res = USER_CHECK_ACCESS (loginID, guid(OC_InfoDiv(arg.divIDs[i]).m_MOD_Base_GUID).id, "L");
			if (res!=ERR_OK)
			{
				string feodName="";
				GetFeodFullName (guid(OC_InfoDiv(arg.divIDs[i]).m_MOD_Base_GUID).id, feodName);
				ERR_RETURN_COMMENT_2 (res, "������������ %s �� ����� ����� ������������� ���������� ������� %s", arg.Login.c_str(), feodName.c_str());
			}
		}
	);
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��� ���������� ���� ����� ��� �����������, ��� ��� ����� ������ VC++6.0 
//	����� INTERNAL COMPILER ERROR
	int i=0;
	int j=0;
	int d=0;
	int nFound=0;

// ������� ��� �������������� ��������, ��������������� �� �������� �� ������� - ����� ������ ���� �������
	OC_InfoObject oc_info;
	key_arr ka0, ka1;
	if (arg.InfoSourceID!=NA)
	{
		ka0	+= arg.InfoSourceID;
		ka0	+= arg.Time0;
		ka1	+=	arg.InfoSourceID;
		ka1	+=	arg.Time1;
		oc_info.SetIndex_InfoSourceID__InfoTime ();
	}
	else
	{
		ka0	+= arg.Time0;
		ka1	+=	arg.Time1;
		oc_info.SetIndex__InfoTime ();
	}
	identifier_arr infoIDs;
	oc_info.GetClassIdListInRange (infoIDs, &ka0, &ka1);
	

// ������ ������� ���� �������� �� ���� �������� ��������
	identifier_arr_arr_arr allDivObjs(arg.divIDs.Size());
	for (d=0; d<arg.divIDs.Size(); d++)
	{
	// ��� �������� ������� ���������� ������ ���� �������� -- ��� ��� ����� ��� ������� ������������� ��������.
		if (arg.divLookInSub)	InfoDivGetAllInfoObjectSortedIDs (arg.divIDs[d], allDivObjs[d]);
		else							{allDivObjs[d].Alloc (1); OC_InfoDiv (arg.divIDs[d]).m_InfoObjectSortedID.CopyTo (allDivObjs[d][0]);}
	}


// ����������� �������, ������� �� �������� �� �������� �������� (�� �� ���� �������� ��� ��� �������)
	for (i=0; i<infoIDs.Size(); i++)	
	{
	// ����������� �������, �� �������� ���� �� � ����� �� ������������� ��������
		for (d=0; d<allDivObjs.Size(); d++) 
		{
			bool bFound=false;
		// ���������� �� ���� ����������� �������
			for (int dd=0; dd<allDivObjs[d].Size(); dd++) if (allDivObjs[d][dd].Find (infoIDs[i], true)!=-1)
			{
			// ������ ������ � ����� �� �����������
				bFound = true;
				break;
			}

		// ������ �� ������ �� � ����� �������, �� � ����� �� ��� �����������, ����������� ���.
			if (bFound==false)
			{
				infoIDs[i]=NA;
				break;
			}
		}

	// ����������� �������, � ������� ��� �������
		if (infoIDs[i]!=NA && USER_CHECK_ACCESS_TO_INFOOBJECT(loginID,infoIDs[i],arg.divAttributes)!=ERR_OK)
		{
			infoIDs[i]=NA;
		}

	// ����� ��������� ��������������� ��������
		nFound += infoIDs[i]!=NA;

	// ���� ������� ����������� ����� �������� � �� ��������� ������ ������� �� ����� ����, 
	// �� ������������, ���������� ��� ���������� �������.
		if ((nFound > arg.objLastNo+1) && !arg.bNeedTotalStoredNum)
		{
			for (int j=i+1; j<infoIDs.Size(); j++)	infoIDs[j]=NA;
			break;
		}
	}


//	���������� �������������� ���������� ��� ���� ��������
	identifier PublicDivID		=	GetInfoDivIDByType ("Concept.Feod.Data.Service.Public");
	identifier ForbiddenDivID	=	GetInfoDivIDByType ("Concept.Feod.Data.Service.Forbidden");
	identifier HotDivID			=	GetInfoDivIDByType ("Concept.Feod.Data.Mark.Hot");


// infoIDs -- ��� ���������� ������� ������������� ��������, 
// ��������������� �� ������� �� ������� � ������. 
// ��������� ����������� ����������.
	for (j=0, i=0; i<infoIDs.Size(); i++) if (infoIDs[i]!=NA)
	{
		if (j<arg.objFirstNo || j>arg.objLastNo) 
		{
			j++;
			continue;
		}
		else j++;

		if (!OC_Exist (OBJ_CLASS_ID_InfoObject, infoIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("������������ ������������� ��������������� ������� %u", infoIDs[i]);
			continue;
		}
		OC_InfoObject oc_info (infoIDs[i]);

		arg.objIDs				+= infoIDs[i];
		arg.objProxyIDs		+=	guid(oc_info.m_ProxyObject).id;
		arg.objNames			+=	oc_info.m_Name;
		arg.objDescriptions	+=	oc_info.m_Description;
		arg.objInfoTimes		+=	oc_info.m_InfoTime;
		arg.objStatShows		+= oc_info.m_ShowCount;
		arg.objStatClicks		+=	oc_info.m_ClickCount;
		arg.objStatCTRs		+=	oc_info.m_CTR;





	//----------------------------------------------------------------------------[] 
	// ������ � ���������� ������, ���� ����.
	//
		if (arg.bNeedLog)
		{
		// ��������� ������ -- ����� ������ ����� ����� ������������� ������ �������������
			if (USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), "R") != ERR_OK)
			{
				ERR_RETURN_COMMENT_1 (res, "������������ %s �� ����� ������������� ���, ��� ��� �� ����� ����� {Concept.Feod.Admin.User.Data}[R] (������������� ������ �������������)", arg.Login.c_str());
			}

		// �������������� ���������
			guid			CreatorGUID;
			string		CreatorLogin;
			string		CreatorName;

			guid			PublisherGUID;
			string		PublisherLogin;
			string		PublisherName;

			guid			ForbidderGUID;
			string		ForbidderLogin;
			string		ForbidderName;

			guid			HotterGUID;
			string		HotterLogin;
			string		HotterName;


		// ������� �������������, ����������� ������������ ��������
			int l;
			int oc_info_m_Log_Action_Size = oc_info.m_Log_Action.Size();
			for (l=0; l<oc_info_m_Log_Action_Size; l++)
			{
				int nAction = oc_info.m_Log_Action[l];
				switch (nAction)
				{
					case INFOOBJ_ACTION_CREATE:
						if (CreatorGUID.id == NA)
						{
							CreatorGUID = oc_info.m_Log_UserGUID[l];
							CreatorGUID.id = UserGetLoginFullName (CreatorGUID, CreatorLogin, CreatorName);
						}
						else SERVER_DEBUG_ERROR_2 ("� ���� ������� %s[%d] ��������� ���������� ����� 1-�� ����", string(oc_info.m_Name).c_str(), infoIDs[i]);
					break;

					case INFOOBJ_ACTION_PUBLIC:
						PublisherGUID = oc_info.m_Log_UserGUID[l];
					break;

					case INFOOBJ_ACTION_FORBID:
						ForbidderGUID = oc_info.m_Log_UserGUID[l];
					break;

					case INFOOBJ_ACTION_HOT:
						HotterGUID = oc_info.m_Log_UserGUID[l];
					break;
				}
			}


		// ���� ��������� �� ������, ������ ���� ����� ���������
			if (CreatorGUID.id == NA)
			{
				CreatorGUID		= oc_info.m_OwnerGUID;
				CreatorGUID.id = UserGetLoginFullName (CreatorGUID, CreatorLogin, CreatorName);
			}

		// ���� ������ � ������������ ���������, ����� ��� ��� � ��� ��������� ������
			int oc_info_m_InfoDivID_Size = oc_info.m_InfoDivID.Size();
			bool bPublished	= false;
			bool bForbidded	= false;
			bool bHotted		= false;
			for (int d=0; d< oc_info_m_InfoDivID_Size; d++)
			{
				if (oc_info.m_InfoDivID[d]==PublicDivID)		bPublished	= true;
				if (oc_info.m_InfoDivID[d]==ForbiddenDivID)	bForbidded	= true;
				if (oc_info.m_InfoDivID[d]==HotDivID)			bHotted		= true;
			}

		// ��������� ��������� -- ���������
			arg.objLogCreatorIDs		+=	CreatorGUID.id;
			arg.objLogCreatorLogins	+=	CreatorLogin;
			arg.objLogCreatorNames	+=	CreatorName;

		// ��������� ��������� -- ����������
			if (bPublished)
			{
				PublisherGUID.id = UserGetLoginFullName (PublisherGUID, PublisherLogin, PublisherName);
				arg.objLogPublisherIDs		+=	PublisherGUID.id;
				arg.objLogPublisherLogins	+=	PublisherLogin;
				arg.objLogPublisherNames	+=	PublisherName;
			}
			else
			{
				arg.objLogPublisherIDs		+=	NA;
				arg.objLogPublisherLogins	+=	"";
				arg.objLogPublisherNames	+=	"";
			}

		// ��������� ��������� -- �����������
			if (bForbidded)
			{
				ForbidderGUID.id			= UserGetLoginFullName (ForbidderGUID, ForbidderLogin, ForbidderName);
				arg.objLogForbidderIDs		+=	ForbidderGUID.id;
				arg.objLogForbidderLogins	+=	ForbidderLogin;
				arg.objLogForbidderNames	+=	ForbidderName;
			}
			else
			{
				arg.objLogForbidderIDs		+=	NA;
				arg.objLogForbidderLogins	+=	"";
				arg.objLogForbidderNames	+=	"";
			}


		// ��������� ��������� -- ����������
			if (bHotted)
			{
				HotterGUID.id				= UserGetLoginFullName (HotterGUID, HotterLogin, HotterName);
				arg.objLogHotterIDs		+=	HotterGUID.id;
				arg.objLogHotterLogins	+=	HotterLogin;
				arg.objLogHotterNames	+=	HotterName;
			}
			else
			{
				arg.objLogHotterIDs		+=	NA;
				arg.objLogHotterLogins	+=	"";
				arg.objLogHotterNames	+=	"";
			}

		}
	//----------------------------------------------------------------------------[] 




	// ����������� ������������ -- �������� ������ ��� ������� ����
		bool bReadAccess = false;
		if (arg.bNeedText || arg.bNeedURL)
		{
			bReadAccess = USER_CHECK_ACCESS_TO_INFOOBJECT (loginID, infoIDs[i], "R")==ERR_OK;
		}
		if (arg.bNeedText)
		{
			if (bReadAccess)	arg.objTexts += oc_info.m_Text;
			else					arg.objTexts += "{{ACCESS DENY}}";
		}
		else arg.objTexts+="";
		if (arg.bNeedURL)
		{
			if (bReadAccess)	arg.objURLs += oc_info.m_URL;
			else					arg.objURLs += "{{ACCESS DENY}}";
		}
		else arg.objURLs+="";


	// ���� ����������, �������� ����������.
		if (arg.UpdateStatistics)
		{
			oc_info.m_ShowCount	+= 1;
			if (oc_info.m_ShowCount!=0)
			{
				oc_info.m_CTR = (oc_info.m_ClickCount*100)/float(int(oc_info.m_ShowCount));
			}
		// !!! �������� ���������� � ������������ [UserDPS], ��������� � ��������
		}
	}

	arg.TotalStoredNum = arg.bNeedTotalStoredNum? nFound: -1;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ��������� ������ ��������������� �������												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_GetData (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_GetData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ������ "R" �� ���� ��������, ��� ��������� ������.
		<Password					������ ������������, �������������� ��������.
		<objID						������������� �������������� ��������������� �������.
		<UpdateStatistics			���� �� �������� ���������� ��������/������/CTR ������������� ��������. ��������, ��� ������������� ���������� ��� �� ���� ������, � �� ����� ����� -- ����.

		>ProxyID						��� ������������� ���� -- ������������� ���������������� ������-�������.
		>Name							�������� �������.
		>Description				�������� ������� (�����).
		>Text							���������� �������.
		>URL							����������� ����� �������.
		>RelatedLinks				������ �� ����
		>InfoSourceID				�������� ����������
		>InfoSourceName			�������� ��������� ����������
		>InfoSourceURL				URL ��������� ����������
		>InfoTime					�����, ����������� � ��������������� ������� (�� ���������=CreationTime).
		>StatShow					������� ��� ������ ��� �������
		>StatClick					������� ��� ������ ��� ����������� ��� ���������
		>StatCTR						objStatView*100/objStatShow
		>divIDs						� ����� �������� ����������� ������.
		>divNames					����� ��������.
		>AuthorStr					��� ������, �� ����������� �������������
		>OwnerID						������������� ��������� ����������.
		>OwnerLogin					����� ��������� ����������.
		>OwnerName					��� ��������� ����������.

		>bNeedLog					����� �� �������� ��� ��������� ��������������� �������, ��� ��������� ��������� ������ [R] � ������ ������������� {Concept.Feod.Admin.User.Data}, �� ��������� false.
		>Log_Action					������ �������� ��� �������������� ��������, ���� bNeedLog==false -- ������ ������.
		>Log_UserID					������ ��������������� �������������, ����������� ��������, ���� bNeedLog==false -- ������ ������.
		>Log_UserLogin				������ ������� �������������, ����������� ��������, ���� bNeedLog==false -- ������ ������.
		>Log_UserName				������ ������ ��� �������������, ����������� ��������, ���� bNeedLog==false -- ������ ������.
		>Log_Time					������� ���������� �������� ��� �������������� ��������, ���� bNeedLog==false -- ������ ������.
		>Log_Comment				��������� ����������� � ���������, ���� bNeedLog==false -- ������ ������.

		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny)
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� ����������	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoObject, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ %u �� ����������", arg.objID);
	}
	OC_InfoObject oc_info (arg.objID);
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

// ������������ ������ ����� ����� ������ ������� �� ���� ��������, � ������� ����� ������
	for (int d=0; d<oc_info.m_InfoDivID.Size(); d++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByInfoDivID (oc_info.m_InfoDivID[d]), "R");
		if (res!=ERR_OK)
		{
			string feodName="";
			GetFeodFullName (guid(OC_InfoDiv(oc_info.m_InfoDivID[d]).m_MOD_Base_GUID).id, feodName);
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "������������ %s �� ������ ����� ������ ������, ��� ��� �� ����� ������� [R] � ������� '%s'[%u]", arg.Login.c_str(), feodName.c_str(), identifier (oc_info.m_InfoDivID[d]));
		}
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
		oc_info.m_ClickCount	+= 1;
		if (oc_info.m_ShowCount!=0)
		{
			oc_info.m_CTR = (oc_info.m_ClickCount*100)/float(int(oc_info.m_ShowCount));
		}
	// !!! �������� ���������� � ������������ [UserDPS], ��������� � ��������
	}

	identifier	OwnerID=NA;
	string		OwnerLogin;
	string		OwnerName;
	OwnerID		= UserGetLoginFullName (oc_info.m_OwnerGUID, OwnerLogin, OwnerName);

// ��������� �������� ���������
	arg.ProxyID				=	guid(oc_info.m_ProxyObject).id;
	arg.Name					=	oc_info.m_Name;
	arg.Description		=	oc_info.m_Description;
	arg.Text					=	oc_info.m_Text;
	arg.URL					=	oc_info.m_URL;
	arg.RelatedLinks		=	oc_info.m_RelatedLinks;
	arg.InfoTime			=	oc_info.m_InfoTime;
	arg.StatShow			=	oc_info.m_ShowCount;
	arg.StatClick			=	oc_info.m_ClickCount;
	arg.StatCTR				=	oc_info.m_CTR;
	arg.divIDs				=	oc_info.m_InfoDivID;
	arg.AuthorStr			=	oc_info.m_AuthorStr;
	arg.OwnerID				=	OwnerID;
	arg.OwnerLogin			=	OwnerLogin;
	arg.OwnerName			=	OwnerName;
	arg.InfoSourceID		=	oc_info.m_InfoSourceID;
	if (arg.InfoSourceID!=NA)
	{
		GetInfoSourceNameURL (arg.InfoSourceID, arg.InfoSourceName, arg.InfoSourceURL);
	}

// [Sonora] ��������� ���� ��������� -- ������ ���, ��� ������ ����� ������� [R] � ������ �������������.
	if (arg.bNeedLog && USER_CHECK_ACCESS (loginID, GetFeodIDByType ("Concept.Feod.Admin.User.Data"), "R")==ERR_OK)
	{
		for (int a=0; a<oc_info.m_Log_Action.Size(); a++)
		{
			int nAction = oc_info.m_Log_Action	[a];

			if (nAction>=INFOOBJ_ACTION_last_bad || nAction <= INFOOBJ_ACTION_first_bad)
			{
				SERVER_DEBUG_ERROR_1 ("��������� ��� ������ (%d) � ���, ����������", nAction);
				oc_info.m_Log_Action		.Del (a);
				oc_info.m_Log_UserGUID	.Del (a);
				oc_info.m_Log_Time		.Del (a);
				oc_info.m_Log_Comment	.Del (a);
				a --;
				continue;
			}

			arg.Log_Action			+= nAction;
			arg.Log_Description	+= INFOOBJ_ACTION_DESCRIPTION [nAction];
			arg.Log_Comment		+= oc_info.m_Log_Comment		[a];
			arg.Log_Time			+= oc_info.m_Log_Time			[a];

			identifier	logUserID=NA;
			string		logUserLogin;
			string		logUserName;
			logUserID	= UserGetLoginFullName (oc_info.m_Log_UserGUID[a], logUserLogin, logUserName);

			if (logUserID!=NA)
			{
				arg.Log_UserID			+=	logUserID;
				arg.Log_UserLogin		+=	logUserLogin;
				arg.Log_UserName		+=	logUserName;
			}
			else
			{
				arg.Log_UserID			+=	NA;
				arg.Log_UserLogin		+=	"";
				arg.Log_UserName		+=	"";
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
//` ��������� ������ ��������������� �������												[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_InfoObject_PutData (MOD_InfoObject_Args& arg)
{
	DEBUG_STACK_NAME (MOD_InfoObject_PutData);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ��� ���������� �������� ������������ ������ ����� ����� ������ "W" �� ���� ��������, ��� ��������� ������.
		<Password					������ ������������, �������������� ��������.
		<objID						������������� �������������� ��������������� �������.
		<Name							�������� �������.
		<Description				�������� ������� (�����).
		<Text							���������� �������.
		<URL							����������� ����� �������.
		<RelatedLinks				������ �� ����
		<InfoSourceID				�������� ����������
		<InfoTime					�����, ����������� � ��������������� �������.
		<divIDs						� ����� ��������, �� ������ ������, ������ ������������ ������. ����� �� ����� �������� ������ �� ������� ��� ������� [D] � �������� � ������ ��� ������� [C].
		<AuthorStr					��� ������, �� ����������� �������������

		>ExitCode					��� �������� (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ���������� ������������ ����� �������� ������ ������ "INTERNAL COMPILER ERROR" � VC++ 6.0
	static int d;

// ������������� ������ ������ ������������
	if (!OC_Exist (OBJ_CLASS_ID_InfoObject, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "������������� ������ %u �� ����������", arg.objID);
	}
	OC_InfoObject oc_info (arg.objID);

// �������� ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}

// ������������ ������ ����� ����� �������������� ������� �� ���� ��������
	for (d=0; d<oc_info.m_InfoDivID.Size(); d++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByInfoDivID (oc_info.m_InfoDivID[d]), "W");
		if (res!=ERR_OK)
		{
			string feodName="";
			GetFeodFullName (guid(OC_InfoDiv(oc_info.m_InfoDivID[d]).m_MOD_Base_GUID).id, feodName);
			ERR_RETURN_COMMENT_3 (ERR_AccessDeny, "������������ %s �� ������ ����� �������������� �������, ��� ��� �� ����� ������� [W] � ������� '%s'[%u]", arg.Login.c_str(), feodName.c_str(), identifier (oc_info.m_InfoDivID[d]));
		}
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
		ERR_RETURN_COMMENT (ERR_BadName, "��� ������� �� ������ ���� ������");
	}
// ���� �� ������� ����� ������� -- ������
	if (arg.InfoTime==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "�� ������� �����, ����������� � ��������������� �������");
	}
// ��������� ������� ������������ ������ ��������
#if 0  //{ RomanVK
	identifier_arr subDivIDs;
	bool				bFound=false;
	{
	// ���� �� ���� ������ ������ ���� �����������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Mark"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� �����������, �.�. ����������� {Concept.Feod.Data.Mark}");}
	// ���� �� ���� ������ ������ ���� ���������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Service"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� ���������, �.�. ����������� {Concept.Feod.Data.Service}");}
	// ���� �� ���� ������ ������ ���� ������������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� ������������, �.�. ����������� {Concept.Feod.Data.Topic}");}
	// ���� �� ���� ������ ������ ���� ����� ��������������� ���������
		InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Type"), subDivIDs);
		for (bFound=false, d=0; !bFound && d<arg.divIDs.Size(); d++) if (subDivIDs.Find (arg.divIDs[d])!=-1) {bFound=true;}
		if (!bFound) {ERR_RETURN_COMMENT (ERR_BadArgument, "���� �� ���� ������ ������ ���� �������, �.�. ����������� {Concept.Feod.Data.Type}");}
	}
#endif //}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	guid				loginGUID		=	GetUserGUID (loginID); 
	guid				objGUID			=	oc_info.GetObjectGUID (); 
	time_t			cur_Time			=	time(0);
	string			oldName			=	oc_info.m_Name;
	string			oldText			=	oc_info.m_Text;
	string			oldDescription	=	oc_info.m_Description;
	identifier_arr DivIDsarr;
	string			strDivIDsDel;
	string			strDivIDsAdd;
	identifier_arr info_div_arr	=	oc_info.m_InfoDivID;
	string			stroldnewName;

// �������� ������� ���� �������
	FULL_INDEX_BEGIN (oc_info);
	{
		oc_info.m_Name				= arg.Name;
		oc_info.m_Description	= arg.Description;
		oc_info.m_Text				= arg.Text;
		oc_info.m_URL				= arg.URL;
		oc_info.m_RelatedLinks	= arg.RelatedLinks;
		oc_info.m_InfoTime		= arg.InfoTime;
		oc_info.m_InfoSourceID	= arg.InfoSourceID;
		oc_info.m_AuthorStr		= arg.AuthorStr;
	}
	FULL_INDEX_END (oc_info);


// ���������� ������ �� ��������:
// arg.divIDs -- � ����� ��������, �� ������ ������, ������ ������������ ������. 
// ����� �� ����� �������� ������ �� ������� ��� ������� [D] � �������� � ������ ��� ������� [C].
	identifier_arr new_div_arr = oc_info.m_InfoDivID;

// ���������� �� �������� ������� � �������, ����� �� ��� �� ������� �������������, �.�. �� ����� �� ��������
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
		if (arg.divIDs.Find(divID)==-1)
		{
		// ������������ �����, ��� ������ �� ������ ���������� � ������� divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "D")==ERR_OK)
			{
			// ������������ ����� ����� �������� ������ �� �������
				new_div_arr.Del (d);
				d--;
			// ���������� ������ �� �������
				OC_InfoDiv oc_div (divID);
				int nIndex = oc_div.m_InfoObjectSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_div.m_InfoObjectSortedID.Del (nIndex);
				}
			}
		}
	}

// ���������� �� ��������, ��������� ������������� � �������, ����� �� ��� ��� � �������, �.�. �� ����� �� ��������
	for (d=0; d<arg.divIDs.Size(); d++)
	{
		identifier divID = arg.divIDs[d];
		if (new_div_arr.Find(divID)==-1)
		{
		// ������������ �����, ��� ������ ������ ���������� � ������� divID
			if (USER_CHECK_ACCESS_TO_INFODIV (loginID, divID, "C")==ERR_OK)
			{
			// ������������ ����� ����� �������� ������ � ������
				new_div_arr.Add (divID);
				OC_InfoDiv (divID).m_InfoObjectSortedID.InsertSorted (arg.objID);
			}
		}
	}

// �������� �������������� ������� ��������
	oc_info.m_InfoDivID = new_div_arr;
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
// [Sonora] {
// ���������� ���� �������� ��� ��������
// ���������� �������� ���� ��������� ��������������� �������
	if (oldName!=arg.Name)
	{
	// ���������� ���� ������������ -- ������� � ����, ��� ������������ ������� ���������
		UserProfileLogUpdate (loginID, USER_LOG_CHANGENAME, objGUID, cur_Time);
		string strChangeName;
		strChangeName.Format	("-%s ",oldName.c_str());
		stroldnewName += strChangeName;
		strChangeName.Format	("+%s ",arg.Name.c_str());
		stroldnewName += strChangeName;


	//	���������� ���� ������� -- ������� � ����, ��� ������������ ������� ���������
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGENAME;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	stroldnewName;
	}

// ���������� �������� ���� ��������� ��������������� �������
	if (oldDescription!=arg.Description)
	{
	// ���������� ���� ������������ -- ������� � ����, ��� ������������ ������� ���������
		UserProfileLogUpdate (loginID, USER_LOG_CHANGEDESC, objGUID, cur_Time);

	//	���������� ���� ������� -- ������� � ����, ��� ������������ ������� ���������
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGEDESC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	"";
	}

// ���������� �������� ���� ������ ��������������� �������
	if (oldText!=arg.Text)
	{
	// ���������� ���� ������������ -- ������� � ����, ��� ������������ ������� �����
		UserProfileLogUpdate (loginID, USER_LOG_CHANGETEXT, objGUID, cur_Time);

	//	���������� ���� ������� -- ������� � ����, ��� ������������ ������� �����
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_CHANGETEXT;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	"";
	}

//	���������, ���� �� ������ ��������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Public",		PUBLIC, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	���������, ���� �� ������ �����������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Service.Forbidden",	FORBID, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	���������, ���� �� ������ "������� ����������", ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Hot",	HOT, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
//	���������, ���� �� ������ "������� ����������", ���� ��, ������� ��������� � ��� ������� � ������������
	CHECK_DIV_AND_SET_LOG_RECORD (loginGUID, "Concept.Feod.Data.Mark.Regular",	REGULAR, "", objGUID, oc_info.m_InfoDivID, new_div_arr);
	
	InfoDivGetAllSubDivIDs	(GetInfoDivIDByType ("Concept.Feod.Data.Topic"), DivIDsarr);

// ���������� �� ������ �������� � �������, ����� �� ��� �� ������������ � ������� (������ ���� "��������")
	bool	bDelDiv = false;
	for (d=0; d<info_div_arr.Size(); d++)
	{
		identifier divID = info_div_arr[d];
	// ���������, ������� �� ������������ ������ �� �������-�������� divID
		if (new_div_arr.Find(divID)==-1 && DivIDsarr.Find(divID)!=-1)
		{
		// �������� ��������������� ������ strDivIDsDel �� ����������� ������������� �������
			bDelDiv = true;
			string tmplate;
			tmplate.Format	("-%lu ",divID);
			strDivIDsDel += tmplate;									
		}
	}

// ���������� �� ����� ��������-��������� � �������, ����� �� ��� ������ �� �������������� � �������
	bool	bAddDiv = false;
	for (d=0; d<new_div_arr.Size(); d++)
	{
		identifier divID = new_div_arr[d];
	// ��������� ��� ������������ ������� � ������ ������-�������� divID
		if (info_div_arr.Find(divID)==-1 && DivIDsarr.Find(divID)!=-1)
		{
		//	�������� ��������������� ������ strDivIDsAdd �� ����������� ������������� �������
			bAddDiv	= true;
			string tmplate;
			tmplate.Format	("+%lu ",divID);
			strDivIDsAdd += tmplate;
		}
	}

// ���������� ���� ������� -- ������� � ����, ����������� ��������
	if (bAddDiv)
	{
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_ADDTOPIC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	strDivIDsAdd;

	// ���������� ���� ������������ - ������� � ����, ��� ������������ ������� ��������
		UserProfileLogUpdate (loginID, USER_LOG_ADDTOPIC, objGUID, cur_Time);
	}
							  	 
// ���������� ���� ������� -- ������� � ����, ��������� ��������
	if (bDelDiv)
	{
		oc_info.m_Log_Action		+= INFOOBJ_ACTION_DELTOPIC;
		oc_info.m_Log_UserGUID	+= loginGUID;
		oc_info.m_Log_Time		+=	cur_Time;
		oc_info.m_Log_Comment	+=	strDivIDsDel;

	// ���������� ���� ������������ - ������� � ����, ��� ������������ ������ ��������
		UserProfileLogUpdate (loginID, USER_LOG_DELTOPIC, objGUID, cur_Time);
	}
// [Sonora] }
//----------------------------------------------------------------------------[] 
	
	
	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]





// !! ��� �������� ������� ���������� ��� �� �������!
//	!! ��� �������� ������� ������� ��� ������-������ (� ��� ����� � ������������� ����)
//		DELETE_PROXY_OBJECT_OF (oc_info);








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/