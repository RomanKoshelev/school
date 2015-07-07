/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 2000 Alex Vershinin.                                         []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_IPRecord.cpp                                           []
[] Date:            03.01.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                    
#define USES_OC_Viewer
#define USES_OC_IPRecord

#define USES_BX_IPRecord
#define USES_BX_Macros
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Concept
#define USES_BX_TimeStats
#define USES_BX_Admin
#define USES_BX_Utils

#include "BX.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_IPRecord_New                                                           []               
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_IPRecord_New(BX_IPRecord_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;


	IP_Address		ip_first(arg.First);
	IP_Address		ip_last(arg.Last);

	if ((ip_first.Size() != 4) || (ip_last.Size() != 4))
	{
		SERVER_DEBUG_ERROR_2 ("BX_IPRecord_New(): Invalid IP passed: First='%s', Last='%s'. Aborted.",
			ip_first.GetIP(), ip_last.GetIP());

		return BXE_IPRecord_InvalidIP;
	}

//----------------------------------------------------------------------------[]
	OC_IPRecord	oc_iprecord;
	BX_CREATE_AND_CHECK(oc_iprecord);

	oc_iprecord.m_Checked	= arg.Checked;
	oc_iprecord.m_Count		= 0;
	ip_first.GetMask(arg.Mask, 3, true);
	oc_iprecord.m_Mask		= arg.Mask;
	oc_iprecord.m_First		= arg.First;
	oc_iprecord.m_Last		= arg.Last;

	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.ConceptID);
	oc_iprecord.m_ConceptID = arg.ConceptID;

	for (int i = 0; i < arg.ConceptID.Size(); i++) {
		oc_iprecord.m_ConceptNo.Add(
			oc_reg.m_ConceptNo_SortID[oc_reg.m_ConceptID_Sorted.Find(arg.ConceptID[i], true)]
			);
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_IPRecord_GetData                                                       []                   
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_IPRecord_GetData(BX_IPRecord_Args& arg)
{
/*	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;
*/
	if (!OC_Exist(OBJ_CLASS_ID_IPRecord, arg.objID))
		return BXE_IPRecord_InvalidID;

//----------------------------------------------------------------------------[]
	OC_IPRecord	oc_iprecord;
	oc_iprecord.Open(arg.objID);

	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, oc_iprecord.m_ConceptID);
	
	arg.Checked		= (bool)oc_iprecord.m_Checked;
	arg.Count		= oc_iprecord.m_Count;
	arg.Mask			= oc_iprecord.m_Mask;
	arg.First		= oc_iprecord.m_First;
	arg.Last			= oc_iprecord.m_Last;
	arg.ConceptID	= oc_iprecord.m_ConceptID;

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_IPRecord_Check                                                         []                 
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_IPRecord_Check(BX_IPRecord_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;

	if (!OC_Exist(OBJ_CLASS_ID_IPRecord, arg.objID))
		return BXE_IPRecord_InvalidID;

	IP_Address		ip_first(arg.First);
	IP_Address		ip_last(arg.Last);

	if ((ip_first.Size() != 4) || (ip_last.Size() != 4))
	{
		SERVER_DEBUG_ERROR_2 ("BX_IPRecord_Check(): Invalid IP passed: First='%s', Last='%s'. Aborted.",
			ip_first.GetIP(), ip_last.GetIP());

		return BXE_IPRecord_InvalidIP;
	}

//----------------------------------------------------------------------------[]
	OC_IPRecord	oc_iprecord;
	oc_iprecord.Open(arg.objID);

	oc_iprecord.m_Checked	= true;
	oc_iprecord.m_First		= arg.First;
	oc_iprecord.m_Last		= arg.Last;

	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.ConceptID);

	if (arg.ConceptID.Size() > 0)
	{
		oc_iprecord.m_ConceptID = arg.ConceptID;
		oc_iprecord.m_ConceptNo.Erase();
		for (int i = 0; i < arg.ConceptID.Size(); i++) {
			oc_iprecord.m_ConceptNo.Add(
				oc_reg.m_ConceptNo_SortID[oc_reg.m_ConceptID_Sorted.Find(arg.ConceptID[i], true)]
				);
		}
	}


	return BX_OK;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` RegisterIP                                                                []          
//                                                                            []
// Регистрирует IP-адрес в базе. Если для этого адреса установлены концепты,	[]
// то инкрементирует у зрителя поле CRA_Inquiry.										[]
//----------------------------------------------------------------------------[]`
BX_RESULT
RegisterIP(
	const string&	IPAddressStr,
	OC_Viewer&		oc_viewer,
	bool				bHost,
	bool				bNewVisitor,
	time_t			CurrentTime)
{	
	string		IPRangeMask;
	IP_Address	ipaddress(IPAddressStr);
// Получим маску диапазона для этого адреса:
	ipaddress.GetMask(IPRangeMask, 3, true);

	OC_IPRecord	oc_iprecord;
	oc_iprecord.SetIndex_Checked_Mask();

	key_arr		ka;
	bool			bFoundRange = false;

// Будем искать проверенный диапазон, в который попадает данный адрес:
	ka += true;
	ka += IPRangeMask;

	for (oc_iprecord.Find(ka); oc_iprecord.IsValid() && !bFoundRange; oc_iprecord.GoNextSame(&ka))
	{

		if ((ipaddress >= IP_Address(oc_iprecord.m_First)) && (ipaddress <= IP_Address(oc_iprecord.m_Last))) {
			bFoundRange = true;
			break;
		}
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Если не нашли проверенный диапазон:
	if (!bFoundRange)
	{
	// Будем искать непроверенный диапазон, в который попадает данный адрес:
		ka.Init();
		ka += false;
		ka += IPRangeMask;

		if (!oc_iprecord.Find(ka)) // Непроверенный диапазон с такой маской может быть только один (или ни одного)
		{
			oc_iprecord.New();
			oc_iprecord.m_Mask		= IPRangeMask;
			oc_iprecord.m_Checked	= false;
		}
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// Если нашли проверенный диапазон:
	else
	{
	// Инкремент распределения у зрителя:
		int_arr	CR, RegionRate;
		CR = oc_viewer.m_CRA_Inquiry.GetCPtr();
		BX_Concept_GetPackedWeights (oc_iprecord.m_ConceptID.GetCPtr(), RegionRate);
		PackedArrIncrement (CR, RegionRate);
		oc_viewer.m_CRA_Inquiry = CR;
//		NormalizePackedArrInplace(CR); это делается в конце UpdateViewerInfo
//		oc_viewer.m_CRN_Inquiry = CR;
	}

// Инкремент счетчика хитов
	oc_iprecord.m_Count += 1;

	BX_TimeStats_Args		timestats_args;
	timestats_args.timer				= CurrentTime;
	timestats_args.Increment		= 1;
	timestats_args.CalculateLast	= true;
	BX_TimeStats_CreateArgs(timestats_args);
// Инкремент счетчика хостов
	if (bHost)	{
		timestats_args.idCounter = oc_iprecord.m_Hosts;
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(timestats_args));
		oc_iprecord.m_Hosts = timestats_args.idCounter;
		oc_iprecord.m_Total_Hosts	= timestats_args.Total;
		oc_iprecord.m_LM_Hosts		= timestats_args.LM;
		oc_iprecord.m_LW_Hosts		= timestats_args.LW;
		oc_iprecord.m_LD_Hosts		= timestats_args.LD;
		oc_iprecord.m_LH_Hosts		= timestats_args.LH;
	}
// Инкремент счетчика новых посетителей
	if (bNewVisitor)	{
		timestats_args.idCounter = oc_iprecord.m_Visitors;
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(timestats_args));
		oc_iprecord.m_Visitors = timestats_args.idCounter;
		oc_iprecord.m_Total_Visitors	= timestats_args.Total;
		oc_iprecord.m_LM_Visitors		= timestats_args.LM;
		oc_iprecord.m_LW_Visitors		= timestats_args.LW;
		oc_iprecord.m_LD_Visitors		= timestats_args.LD;
		oc_iprecord.m_LH_Visitors		= timestats_args.LH;
	}
// Инкремент счетчика анонимных
	if (oc_viewer.m_Anonymous)	{
		timestats_args.idCounter = oc_iprecord.m_Anonymous;
		BX_ASSERT_PASSIVE(BX_TimeStats_Increment(timestats_args));
		oc_iprecord.m_Anonymous = timestats_args.idCounter;
		oc_iprecord.m_Total_Anonymous	= timestats_args.Total;
		oc_iprecord.m_LM_Anonymous		= timestats_args.LM;
		oc_iprecord.m_LW_Anonymous		= timestats_args.LW;
		oc_iprecord.m_LD_Anonymous		= timestats_args.LD;
		oc_iprecord.m_LH_Anonymous		= timestats_args.LH;
	}

	return BX_OK;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_IPRecord_Enumerate                                                     []                     
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_IPRecord_Enumerate(BX_IPRecord_Args& arg)
{
	arg.objIDs.Delete();
	arg.objNames.Delete();

// Работа над ошибками:
	if (arg.objFirstNo < 0)							arg.objFirstNo		= 0;
	if (arg.objLastNo < arg.objFirstNo)			arg.objLastNo		= INT_MAX;
	if (arg.objLastNo - arg.objFirstNo >= MAX_ENUMERATE_SIZE)
															arg.objLastNo		=  arg.objFirstNo + MAX_ENUMERATE_SIZE;
	string			Str;
	int				i;
	identifier_arr	SortedIDs;
	OC_IPRecord		oc_iprecord;
	key_arr			ka;

// Получить отсортированный по хитам список ID сетей:
	oc_iprecord.SetIndex_Checked__Count();
	ka += arg.Checked;

	oc_iprecord.GetClassIdList(SortedIDs, &ka);

// Заполнить выходные аргументы информацией о запрошенном количестве сетей:		
	for (i = arg.objFirstNo; (i <= arg.objLastNo) && (i < SortedIDs.Size()); i++)
	{
		oc_iprecord.Open(SortedIDs[i]);

		if (arg.Checked)
		{
			Str.Format("%10d hits from %s-%s [%d concepts]",
				(int)oc_iprecord.m_Count,
				string(oc_iprecord.m_First).c_str(),
				string(oc_iprecord.m_Last).c_str(),
				oc_iprecord.m_ConceptNo.Size());
		}
		else
		{
			Str.Format("%10d hits from %s",
				(int)oc_iprecord.m_Count,
				string(oc_iprecord.m_Mask).c_str());
		}

		arg.objIDs.Add(SortedIDs[i]);
		arg.objNames.Add(Str);
	}

//	ReverseOrder(arg.objNames);
//	ReverseOrder(arg.objIDs);
	
	return BX_OK;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/