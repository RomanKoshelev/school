/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Admin.h                                                []
[] Date:            24.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������������ ������� ��� ��������������                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                               
#ifndef BX_Admin_H
#define BX_Admin_H


//----------------------------------------------------------------------------[]

struct	BX_Admin_Args
{
	string	Password;							// ������ ��������������.
	string	MemoryManagerReport;				// ����� ���������� ������.
	string	Result;								// 
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

// ��������� ������ ���������� ������. ��������� ������ ��������������.
BX_RESULT	BX_Admin_MemoryManagerReport(BX_Admin_Args& arg);
//____________________________________________________________________________[]

struct	BX_ConceptRate_Args
{
	BX_ConceptRate_Args()
	{
		objID				= NA;
		objLanguageNo	= 0;
	}

	string_arr	CRA_Name;		// �������� ���������, ��������� � ���������� �������������.
	int_arr		CRA_Value;		// �������� ����������� �������������.
	int_arr		CRA_Max;			// ������������ �������� ����������� �������������.
	int_arr		CRA_Min;			// ����������� �������� ����������� �������������.
	int_arr		CRA_Sum;			// ��������� �������� ����������� �������������.
										
	string_arr	CRN_Name;		// �������� ���������, ��������� � ��������������� �������������.
	int_arr		CRN_Value;		// �������� ���������������� �������������.
	int_arr		CRN_Level;		// ������ ��������� �� CRN_Name.

	int_arr		TypeNums;		// ������ ����� ���������, ������� �������� �� ������� � �������������.
	identifier	objID;			// ID �������.
	int			objLanguageNo;	//	����� �����, �� ������� ����� �������� �������� ��������� (�� ��������� - 0).

};
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]

// �������� ������������� ��������� ��� ��������� ���������.
BX_RESULT	BX_ConceptRate_Reg_InetAudience(BX_ConceptRate_Args& arg);
// �������� ������������� ��������� ����������� �����.
BX_RESULT	BX_ConceptRate_Site_Visitor(BX_ConceptRate_Args& arg);
// �������� ������������� ��������� �������.
BX_RESULT	BX_ConceptRate_Viewer_Site(BX_ConceptRate_Args& arg);
// �������� ������������� �������� ��������� �������.
BX_RESULT	BX_ConceptRate_Viewer_Inquiry(BX_ConceptRate_Args& arg);

//____________________________________________________________________________[]

bool CheckAdminPassword(const string& Password);
void GetAdminPassword(string& Password);

//----------------------------------------------------------------------------[]

BX_RESULT BX_Admin_SaveBXObjects(BX_Admin_Args& arg);

BX_RESULT BX_Admin_GetObjectNum(BX_Admin_Args& arg);

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/