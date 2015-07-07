/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Viewer.h                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "���������� �����".         []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#ifndef BX_Viewer_H
#define BX_Viewer_H

#define USES_BX_Events
#define USES_BX_Counter



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Viewer                                                                    []      
[]                                                                            []
[]____________________________________________________________________________[]
*/
struct	BX_Viewer_Args
{

	BX_Viewer_Args() {

		Anonymous			= true;
		TotalShows			= 0;
		TotalClicks			= 0;

		Group					= NA;

		CreationTime		= 0;
		LastVisitTime		= 0;
		TZOffset				= 0L;
		objID					= NA;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}
																
	
	bool				Anonymous		;				// �������� �� ���� ������ �����������
															// ����� ��������� � ���������� IP � 
															// ��������������� Cookie.
															
	int				TotalShows		;				// ����� ���-�� �������.
	int				TotalClicks		;				// ����� ���-�� ������.
															
	string			IPAddress;						// IP �����.
	string			Referrer;						// ���� ����������.
															
	identifier		Group				;				// ������ ������������ �������.
															
	time_t			CreationTime	;				// ����� �������� �������.
	string			sCreationTime	;				// ����� �������� ������� � ��������� ����.
	time_t			LastVisitTime	;				// ����� ���������� ���������.
	string			sLastVisitTime	;				// ����� ���������� ��������� � ��������� ����.
																		
	time_t			TZOffset					;		// �������� �������� ����� ������� � ��������.
	identifier_arr	Site						;		// ID ������, ���������� ��������.
	string_arr		sSite						;		// �������� ������, ���������� ��������.

//	time_t_arr		Site_LastVisited		;		// ����� ���������� ��������� ���������������� �����.
	string_arr		sSite_LastVisited		;		// ����� ���������� ��������� ���������������� ����� � ��������� ����.

	int_arr			Site_Visits				;		// ����� ����� ��������� ���������������� �����.

	byte_arr			Site_Votings			;		// ����� �������, �������� �������� �� ��������������� ����.
	byte_arr			Site_VoteDayNo			;		// ��������� 2 ����� (�.�. ������� �� ������� �� 100) ������ ��� (� ����),
															// � ������� ������������� ��������������� ����������� (������ �� ���� tm::tm_yday).
						
	identifier_arr	Banner					;		// ID ��������, ���������� �������.
	time_t_arr		Banner_LastViewed		;		// ����� ���������� ������ ���������������� ������� �������.
	int_arr			Banner_Shows			;		// ����� ����� ������� ���������������� ������� �������.

	identifier		objID;					// ������������� ������������.
	int				objFirstNo;				// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
	int				objLastNo;				// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
	identifier_arr	objIDs;					// �������������� ��������.
	string_arr		objNames;				// ����� ������������ ����� ��������� *Enumerate().
};
//----------------------------------------------------------------------------[] 

// ����������� ��������.
BX_RESULT BX_Viewer_Enumerate	(BX_Viewer_Args& arg);	
// �������� ���������� �� �������.
BX_RESULT BX_Viewer_GetData	(BX_Viewer_Args& arg);	

//____________________________________________________________________________[]



//----------------------------------------------------------------------------[] 

BX_RESULT
BX_GetViewer(	OC_Viewer&			oc_viewer,
					BX_Event_Args&		arg,
					bool&					bAnonymousViewer, 
					time_t				CurrentTime);

void
UpdateViewerInfo( OC_Viewer&			oc_viewer,		// IN:		�������� � ������������� ���������� �������.
						BX_Counter_Args&	arg,				// IN/OUT:	ID ����� / Visits, LastVisit
						time_t				CurrentTime,	// IN:		������� ����� (GMT).
						bool&					bNewVisitor,	// OUT:		�������� �� ���������� ����� ��� �����.
						bool&					bHost,			// OUT:		�������� �� ���������� ������.
						time_t&				ReturnTime);

//____________________________________________________________________________[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/