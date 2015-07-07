/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Counter.h                                              []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������ �� ���������                                       []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                 
#ifndef BX_Counter_H
#define BX_Counter_H

//______________________________________________________________________________
//                                                                            []
//` Counter                                                                   []       
//                                                                            []

struct BX_Counter_Args : public BX_Event_Args 
{
	BX_Counter_Args() {
		JustGetData							= false;
		CounterType							= 0;
		Visits								= 0;
		LastVisitTime						= 0L;
		OnlineVisitors						= 0;
												
		Total_Loads							= 0;
		Total_Visitors						= 0;
		Total_VisitorReturns				= 0;
		Total_AnonymousVisitors			= 0;
		Total_AnonymousVisitors_Prc	= 0;
		Total_VisitorExperience			= 0;
		Ave_VisitorExperience			= 0;
													
		Total_Hosts							= 0;
													
		Total_Hits							= 0;
		OnlineVisitors						= 0;
		Total_AnonymousHits				= 0;
		Total_AnonymousHits_Prc			= 0;
		Total_SuspiciousHits_Prc		= 0;
		Total_SessionTime					= 0;
													
		Total_Shows							= 0;
		Total_Clicks						= 0;
		Total_MouseOver					= 0;
		Total_CTR_Prc						= 0;
													
		Total_Votes							= 0;
		Total_Votes_Sum					= 0;
		Total_Votes_Ave					= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LM_Loads								= 0;
		LM_Visitors							= 0;
   	LM_VisitorReturns					= 0;
   	LM_VisitorReturns_Prc			= 0;
													
   	LM_Hosts								= 0;
													
   	LM_Hits								= 0;
		LM_AnonymousHits					= 0;
		LM_AnonymousHits_Prc				= 0;
		LM_SuspiciousHits_Prc			= 0;
		LM_SessionTime						= 0;
													
		LM_Shows								= 0;
   	LM_Clicks							= 0;
		LM_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LW_Loads								= 0;
		LW_Visitors							= 0;
   	LW_VisitorReturns					= 0;
   	LW_VisitorReturns_Prc			= 0;
													
   	LW_Hosts								= 0;
													
   	LW_Hits								= 0;
		LW_AnonymousHits					= 0;
		LW_AnonymousHits_Prc				= 0;
		LW_SuspiciousHits_Prc			= 0;
		LW_SessionTime						= 0;
													
		LW_Shows								= 0;
   	LW_Clicks							= 0;
		LW_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LD_Loads								= 0;
		LD_Visitors							= 0;
   	LD_VisitorReturns					= 0;
   	LD_VisitorReturns_Prc			= 0;
													
   	LD_Hosts								= 0;
													
		LD_Hits								= 0;
		LD_AnonymousHits					= 0;
		LD_AnonymousHits_Prc				= 0;
		LD_SuspiciousHits_Prc			= 0;
		LD_SessionTime						= 0;
													
		LD_Shows								= 0;
   	LD_Clicks							= 0;
		LD_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LH_Loads								= 0;
		LH_Visitors							= 0;
   	LH_VisitorReturns					= 0;
   	LH_VisitorReturns_Prc			= 0;
													
   	LH_Hosts								= 0;
													
		LH_Hits								= 0;
		LH_AnonymousHits					= 0;
		LH_AnonymousHits_Prc				= 0;
		LH_SuspiciousHits_Prc			= 0;
		LH_SessionTime						= 0;
													
		LH_Shows								= 0;
   	LH_Clicks							= 0;
		LH_CTR_Prc							= 0;
//----------------------------------------------------------------------------[] 
	
	}
	bool		JustGetData						;	// �������� �������� ����� �������� ������ ��� �� �����������. �� ���� ����� ������ ID �����.
	int		CounterType						;	// ��� �������� (�� ��������� - ���, ��� ���������� � �����).
	int		Visits							;	// ���������� �����, ��������� �������� �� ���� �����.
	time_t	LastVisitTime					;	// ����� ���������� ��������� ������ �������� ����� �����.
	int		OnlineVisitors					;	// ����� ���������� ����������� �� ��������� 3 ������.
		
	int		Total_Loads							;	//*  ����� �������� �����.
	int		Total_Visitors						;	//*  ����� ����� ����������� �����.
	int		Total_VisitorReturns				;	//*  ����� ��������� �� ����.
	int		Total_AnonymousVisitors			;	//   ����� ��������� ����������� �����.
	int		Total_AnonymousVisitors_Prc	;	//+  ������� ��������� ����������� ����� �� ������ ����� ����� ����������� �����.
	int		Total_VisitorExperience			;	//   ����� ���������� ���������� ������ ����� ������� ������� �����.
	int		Ave_VisitorExperience			;	//+  ������� ���������� ���������� ������ ��� ����� �� ������ �����.
														
	int		Total_Hosts							;	//   ����� �������� ����� �� �����, ������� �����.
														
	int		Total_Hits							;	//*  ����� (�� ��������������) ����� �����.
	int		Total_AnonymousHits				;	//   ����� ��������� ����������� �����.
	int		Total_AnonymousHits_Prc			;	//*+ ������� ��������� ����������� ����� �� ������ ����� ����� ����������� �����.
	int		Total_SuspiciousHits_Prc		;	//+  ������� �������������� ����� ����� �� ������ ������ ����� ����� �� ����� (������� ��������������).
	int		Total_SessionTime					;	//	  ��������� ����������������� ������ �� �����.
														
	int		Total_Shows							;	//   ����� ������� �������� �� �����.
	int		Total_Clicks						;	//	  ����� ������� �������� �� �����.
	int		Total_MouseOver					;	//   ���������� ������� � �������� �� ���� ����� �� �� �����.
	int		Total_CTR_Prc						;	//*+ CTR �������� �� ���� ����� �� �� �����.
														
	int		Total_Votes							;	//   ����� ��������������� �� ����.
	int		Total_Votes_Sum					;	//   ��������� ������ ����������� �� ����.
	int		Total_Votes_Ave					;	//+  ������� ������ ����������� �� ����.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LM_Loads								;	//	  ����� �������� ����� �� ��������� �����. 
	int		LM_Visitors							;  //   ����� ����������� ����� �� ��������� �����. 
   int		LM_VisitorReturns					;	//   ��������� �� ���� � ������� ������.
   int		LM_VisitorReturns_Prc			;	//+  ������� �������������� � ������� ������ ����������� ����� �� ������ ����� ����������� ����� � ������� ������.
														
   int		LM_Hosts								;  //   ������ �� ����� �� ��������� �����.
														
   int		LM_Hits								;	//   ����� (�� ��������������) �� ����� �� ��������� �����.  
	int		LM_AnonymousHits					;	//   ��������� ����� ����� �� ��������� �����.
	int		LM_AnonymousHits_Prc				;	//+  ������� ��������� ����� ����� �� ��������� ����� �� ������ ����� (�� ��������������) ����� �� ��������� �����.
	int		LM_SuspiciousHits_Prc			;	//+  ������� �������������� ����� ����� �� ��������� ����� �� ������ ����� ����� �� ��������� ����� (������� ��������������).
	int		LM_SessionTime						;	//	  ��������� ����������������� ������ �� ����� �� ��������� �����.

	int		LM_Shows								;	//	  ������� �������� �� ����� �� ��������� �����.
   int		LM_Clicks							;  //   ������� �������� �� ����� �� ��������� �����.  
	int		LM_CTR_Prc							;	//+  CTR �� ��������� �����.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LW_Loads								;	//	  ����� �������� ����� �� ��������� ������.
	int		LW_Visitors							;	//   ����� ����������� ����� �� ��������� ������.
   int		LW_VisitorReturns					;	//   ��������� �� ���� � ������� ������.
   int		LW_VisitorReturns_Prc			;	//+  ������� �������������� � ������� ������ ����������� ����� �� ������ ����� ����������� ����� � ������� ������.
														
   int		LW_Hosts								;	//   ������ �� ����� �� ��������� ������.
														
   int		LW_Hits								;	//   ����� (�� ��������������) �� ����� �� ��������� ������.  
	int		LW_AnonymousHits					;	//   ��������� ����� ����� �� ��������� ������.  
	int		LW_AnonymousHits_Prc				;	//+  ������� ��������� ����� ����� �� ��������� ������ �� ������ ����� (�� ��������������) ����� �� ��������� ������.
	int		LW_SuspiciousHits_Prc			;	//+  ������� �������������� ����� ����� �� ��������� ������ �� ������ ����� ����� �� ��������� ������ (������� ��������������).  
	int		LW_SessionTime						;	//	  ��������� ����������������� ������ �� ����� �� ��������� ������.
														
	int		LW_Shows								;	//	  ������� �������� �� ����� �� ��������� ������.
   int		LW_Clicks							;  //   ������� �������� �� ����� �� ��������� ������.
	int		LW_CTR_Prc							;	//+  CTR �� ��������� ������.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LD_Loads								;	//	  ����� �������� ����� �� ��������� �����.
	int		LD_Visitors							;	//   ����� ����������� ����� �� ��������� �����.
   int		LD_VisitorReturns					;	//+  ��������� �� ���� � ������� �����.  
   int		LD_VisitorReturns_Prc			;	//+  ������� �������������� � ������� ����� ����������� ����� �� ������ ����� ����������� ����� � ������� �����.
														
   int		LD_Hosts								;	//   ������ �� ����� �� ��������� �����.
														
	int		LD_Hits								;	//   ����� (�� ��������������) �� ����� �� ��������� �����.
	int		LD_AnonymousHits					;	//   ��������� ����� ����� �� ��������� �����.
	int		LD_AnonymousHits_Prc				;	//+  ������� ��������� ����� ����� �� ��������� ����� �� ������ ����� (�� ��������������) ����� �� ��������� �����.
	int		LD_SuspiciousHits_Prc			;	//+  ������� �������������� ����� ����� �� ��������� ����� �� ������ ����� ����� �� ��������� ����� (������� ��������������).
	int		LD_SessionTime						;	//	  ��������� ����������������� ������ �� ����� �� ��������� ����.
														
	int		LD_Shows								;	//	  ������� �������� �� ����� �� ��������� �����.
   int		LD_Clicks							;	//   ������� �������� �� ����� �� ��������� �����.
	int		LD_CTR_Prc							;	//+  CTR �� ��������� �����.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LH_Loads								;	//	  ����� �������� ����� �� ��������� ���. 
	int		LH_Visitors							;	//   ����� ����������� ����� �� ��������� ���. 
   int		LH_VisitorReturns					;  //   ��������� �� ���� � ������� ����.  
   int		LH_VisitorReturns_Prc			;	//+  ������� �������������� � ������� ���� ����������� ����� �� ������ ����� ����������� ����� � ������� ����.
														
   int		LH_Hosts								;	//   ������ �� ����� �� ��������� ���.
														
	int		LH_Hits								;  //   ����� (�� ��������������) �� ����� �� ��������� ���.
	int		LH_AnonymousHits					;	//   ��������� ����� ����� �� ��������� ���.
	int		LH_AnonymousHits_Prc				;	//+  ������� ��������� ����� ����� �� ��������� ��� �� ������ ����� (�� ��������������) ����� �� ��������� ���.
	int		LH_SuspiciousHits_Prc			;	// + ������� �������������� ����� ����� �� ��������� ��� �� ������ ����� ����� �� ��������� ��� (������� ��������������).
	int		LH_SessionTime						;	//	  ��������� ����������������� ������ �� ����� �� ��������� ���.
														
	int		LH_Shows								;	//	  ������� �������� �� ����� �� ��������� �����.
   int		LH_Clicks							;  //   ������� �������� �� ����� �� ��������� ���.
	int		LH_CTR_Prc							;	//	+ CTR �� ��������� �����.
//----------------------------------------------------------------------------[] 
	


};
//----------------------------------------------------------------------------[] 

// ���������� �������������� ���������� ��� ������ ��������.
BX_RESULT BX_Counter_GetData(BX_Counter_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/