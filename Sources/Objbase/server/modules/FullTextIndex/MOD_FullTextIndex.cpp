/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 2000 by the author(s) -- see below.									[]
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_FullTextIndex.cpp													[]
[] Date:          24.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   �������������� ���������� � ����� � ������ ����������			[]
[]						������������ �������.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_FullTextIndex.inc.h"				 



//______________________________________________________________________________
//                                                                            []
//` ���������� ������� �� ��������������� �������                             []
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Del (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Del);
/*............................................................................[]
		<objGUID						���������� ������������� ���������� �� ������� ������� (guid).
		<objIDs						�������������� ��������� ����.

		>ExitCode					��� �������� (OK).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]

	RemoveFromFullTextIndex (arg.objGUID, arg.objIDs);

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` ��������� ������� � �������������� ������                                 []                                         
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Add (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Add);
/*............................................................................[]
		<objGUID						���������� ������������� �������������� ������� (guid).
		<StrName						�������� �������������� �������.
		<StrDescription			������� �������� �������������� �������.
		<StrText						��������� ���������� �������������� �������.
		<StrAdditional				�������������� ��������� ����������, ������������ � ������������� �������.
		<Time							�����, ��� ������� ������ ���������� � �������.

		>objIDs						�������������� �������������� ��� �������������� ���� [SearchItemID]
		>ExitCode					��� �������� (OK).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]


	string TotalText = "";
	TotalText += arg.StrName;	  
	TotalText += " ";
	TotalText += arg.StrDescription;
	TotalText += " ";
	TotalText += arg.StrText;
	TotalText += " ";
	TotalText += arg.StrAdditional;

	CreateFullTextIndex (TotalText, arg.objGUID, arg.objIDs, arg.Time);

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` ��������� ������ ��������, ��������������� ���������� �������					[]
//                                                                            []
ERR_RESULT FullTextIndex_Enumerate (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (FullTextIndex_Enumerate);
/*............................................................................[]
		<Request						��������� ������.
		<Time0						���������� ����� ����� ������� ��������. ������ ���������. �� ��������� = time(0);
		<Time1						���������� ����� ����� ������ ��������. ����� ���������. �� ��������� = (time_t)0;

		>objGUIDs					������ ���������� ��������������� ��������� ��������
		>objTimes					������ ����� ���������� � �������� ��������� ��������.
		>objWeights					������ �����-������ ��������� ��������.

		>RequestLemma				��������������� ��������� ������.

		>ExitCode					��� �������� (OK).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]

//	������� ������� ���������
	arg.objGUIDs.Erase ();
	arg.objWeights.Erase ();
	arg.objTimes.Erase ();

// ��������� ������ �� ������ ����
	int				i;
	int				iLemma; (void)iLemma;
	int				iItem;  (void)iItem;
	OC_SearchItem	oc_item;
	lemma_arr		arrLemma;
	GetNormalWordArr (arg.Request, arrLemma, false, true);

	bool bFoundTooMuch = false;

// ���������� ��� ������������ ����������� ������
	guid_arr		Object_GUID					(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_GUID.Erase();
	time_t_arr	Object_ModificationTime	(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_ModificationTime.Erase();
	int_arr		Object_WordAppearanceNum(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_WordAppearanceNum.Erase();
	int_arr		Object_WordFirstPosition(MAX_SEARCH_RESULT_ENUMERATE_NUM); Object_WordFirstPosition.Erase();

// ��� ������ ���� ������� ������ ��������, � ��������� ��� � ����� ������ ��������� ��������
	for (iLemma=0; !bFoundTooMuch && iLemma<arrLemma.Size(); iLemma++)
	{
		if (iLemma)		  arg.RequestLemma += ", ";
		arg.RequestLemma += arrLemma[iLemma].Word;

		key_arr ka;
		ka += arrLemma[iLemma].Word;
		if (oc_item.Find (ka)) for (iItem=0; !bFoundTooMuch && iItem<oc_item.m_Text_ObjectSortedGUID.Size(); iItem++)
		{
		// ���� ������� ������� ����� �������� -- ������������
			if (Object_GUID.Size()> MAX_SEARCH_ENUMERATE_NUM)
			{
				bFoundTooMuch = true;
			}

		// ������ ������������� ���������� ���������
			time_t t = oc_item.m_Text_ModificationTime [iItem];
			if (t>=arg.Time1 && t<=arg.Time0)
			{
			// ���������� ������ � ��� �������������� ��� ����������� ������������
				Object_GUID						+= oc_item.m_Text_ObjectSortedGUID	[iItem];
				Object_ModificationTime		+= oc_item.m_Text_ModificationTime	[iItem];
				Object_WordAppearanceNum	+= oc_item.m_Text_WordAppearanceNum	[iItem];
				Object_WordFirstPosition	+= oc_item.m_Text_WordFirstPosition	[iItem];
			}
		}
	}

// ���������� ���������� ������� � ��������� ���
	guid_arr arrSortedGUID	(Object_GUID.Size()); arrSortedGUID.Erase();
	int_arr	arrWeight		(Object_GUID.Size()); arrWeight.Erase();
	int_arr	arrTimes			(Object_GUID.Size()); arrTimes.Erase();	
	int_arr	arrLemmaNum		(Object_GUID.Size()); arrLemmaNum.Erase();	
	for (i=0; i<Object_GUID.Size(); i++)
	{
		int index = arrSortedGUID.Find (Object_GUID[i], true);
		int	Weight	= 0;
		if (index == -1)
		{
			index = arrSortedGUID.InsertSorted (Object_GUID[i]);
			arrWeight.Insert		(index, 0);
			arrTimes.Insert		(index, Object_ModificationTime[i]);
			arrLemmaNum.Insert	(index, 1);

		// ��� ������ ������� ����, ��� ���� ���
			Weight += Object_WordAppearanceNum [i];
		// ����� �� 10-�� ������� ���������� 10 ����������, �� 100-�� -- ������ ���������
			Weight += 100 / (Object_WordFirstPosition[i]+1);
		// ���������� ���
			arrWeight[index] -= Weight;
		}
		else
		{
			arrLemmaNum[index]++;
		// ��� ������ ������ ���� �������, ��� ���� ����
			arrWeight[index] *= 10;//*arrLemmaNum[index];
		}
//		arrWeight[index] = -arrLemmaNum[index];
	}

//	��������� ��������� ������
	guid_arr arrRangedGUID		(arrSortedGUID.Size()); arrRangedGUID.Erase();
	int_arr	arrSortedWeight	(arrSortedGUID.Size()); arrSortedWeight.Erase();
	int_arr	arrResultTimes		(arrSortedGUID.Size()); arrResultTimes.Erase();
	for (i=0; i<arrSortedGUID.Size(); i++)
	{
		int index = arrSortedWeight.InsertSorted (arrWeight[i]);
		arrRangedGUID.Insert (index, arrSortedGUID[i]);
		arrResultTimes.Insert (index, arrTimes[i]);
	}
	
	arg.objGUIDs	= arrRangedGUID;
	arg.objWeights	= arrSortedWeight;
	arg.objTimes	= arrResultTimes;

// ���� ������� ������� ����� ��������
	if (bFoundTooMuch)
	{
		arg.objGUIDs.Realloc		(MAX_SEARCH_ENUMERATE_NUM);
		arg.objWeights.Realloc	(MAX_SEARCH_ENUMERATE_NUM);
		arg.objTimes.Realloc		(MAX_SEARCH_ENUMERATE_NUM);
	}

// �������� ���� � ������ �����������, ���������, ��� ���� �������������.
	int maxWeight = -1;
	for (i=0; i<arg.objWeights.Size(); i++)	
	{
		arg.objWeights[i] *= -1;
		maxWeight = max (maxWeight, arg.objWeights[i]);
	}
	//printf ("\n\nmaxWeight = %d\n\n", maxWeight);
	for (i=0; i<arg.objWeights.Size(); i++) 
	{
//		printf ("   %6d -->", arg.objWeights[i]);
		arg.objWeights[i]*=10000; arg.objWeights[i]/=maxWeight;
		if (arg.objWeights[i]<0) arg.objWeights[i] = 10000;
//		printf ("%6d\n", arg.objWeights[i]);
	}

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` ��������� ������ ��������, ��������������� ���������� �������					[]
//                                                                            []
ERR_RESULT MOD_FullTextIndex_Enumerate (MOD_FullTextIndex_Args& arg)
{
	DEBUG_STACK_NAME (MOD_FullTextIndex_Enumerate);
/*............................................................................[]
		<Login						����� ������������, �������������� ��������. ����� �������� ������ �� �������, �� ������� ���� ����� [R].
		<Password					������ ������������, �������������� ��������.

		<Request						��������� ������.
		<Time0						���������� ����� ����� ������� ��������. ������ ���������. �� ��������� = time(0);
		<Time1						���������� ����� ����� ������ ��������. ����� ���������. �� ��������� = (time_t)0;
		<feodIDs						������ ��� �������, � ������� ������ ������������������� �������
		<objFirstNo					����� �������, � �������� �� �����������.
		<objLastNo					����� ���������� �������������� �������.
		<nLookAhead					�� ������� ��������� �������� ����������� �����.[=0]
		<bNeedDescription			��������� �� �������� ��������, ��� ���������� ������ �����.

		>objClasses					������ ������� ��������� ��������
		>objIDs						������ ��������������� ��������� ��������.
		>objNames					������ �������� ��������� ��������.
		>objDescriptions			������ �������� ��������� �������� (������).
		>objTimes					������ ����� ���������� � �������� ��������� ��������.
		>objWeights					������ �����-������ ��������� ��������.
		>objPlacements				������ ��������, ���������� �� ������, �������� ��������. ������: {class|id|name\nclass|id|name, ...}
		>RequestLemma				��������������� ��������� ������.
		>TotalStoredNum			������� ����� �������� ������� � ����� ���� �������� ������� ������������.
		>MaxNumInQuery				����������� ���������� ����� ������������� �� ���� ��� ��������.

		>ExitCode					��� �������� (OK).
		>ExitCodeComment			��������� ����������� � ���� ��������.
*///..........................................................................[]




//----------------------------------------------------------------------------[] 
//                                                                            []
// �������� �������																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// ��������� ����� � ������
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "������������ ������ ��� �����");
	}
//----------------------------------------------------------------------------[] 





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
// ����� ������ ������������
	FOR_EACH_ITEM_EVAL (arg.feodIDs, 
	{
		if (!CHECK_FEOD_ID (arg.feodIDs[i])) 
		{
			ERR_RETURN_COMMENT_1 (ERR_BadID, "������� �������������� ���� ������� ID=%u", arg.feodIDs[i]);
		}
	});

// ����� �� ��������� ������� ����� ��������
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_SEARCH_RESULT_ENUMERATE_NUM-1;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_SEARCH_RESULT_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// ���������� �������																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
	int i,j;
// ���� ��� ��������������� ��������� ������ � ���������� ��������� �������
	MOD_FullTextIndex_Args arg0;
	arg0.Request	= arg.Request;
	arg0.Time0		= arg.Time0;
	arg0.Time1		= arg.Time1;
	FullTextIndex_Enumerate (arg0);
	if (arg0.ExitCode!=ERR_OK)
	{
		ERR_RETURN_COMMENT (arg0.ExitCode, arg0.ExitCodeComment);
	}

// ��������� �� �������, � ������� ��� ������� � ������� �� ��������� � ��������� ������
	string Attributes = "R";
	MOD_CHECK_ACCESS_PLACEMENT	(loginID, arg0.objGUIDs, Attributes, arg.feodIDs, arg.objLastNo+arg.nLookAhead);

// ��������� �������� ���������
	for (arg.TotalStoredNum=0, j=0, i=0; i<arg0.objGUIDs.Size(); i++) if (arg0.objGUIDs[i].id!=NA)
	{
		arg.TotalStoredNum ++;
		if (j<arg.objFirstNo || j>arg.objLastNo) 
		{
			j++;
			continue;
		}
		else j++;
		
		arg.objClasses			+= className [arg0.objGUIDs[i].cl];
		arg.objIDs				+= arg0.objGUIDs[i].id;
		arg.objNames			+=	MOD_GET_OBJECT_NAME			(arg0.objGUIDs[i]);
		arg.objDescriptions	+=	MOD_GET_OBJECT_DESCRIPTION (arg0.objGUIDs[i]);
		arg.objTimes			+=	arg0.objTimes[i];
		arg.objWeights			+=	arg0.objWeights[i];
	}
// �������� ������
	arg.RequestLemma = arg0.RequestLemma;
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/