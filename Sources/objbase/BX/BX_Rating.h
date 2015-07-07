/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Rating.h                                               []
[] Date:            01.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                               
#ifndef BX_Rating_H
#define BX_Rating_H

/*______________________________________________________________________________
[]                                                                            []
[]` BX_RateStats_Args                                                         []                 
[]                                                                            */
struct	BX_RateStats_Args
{
	BX_RateStats_Args()
	{
		VBN					= NA;
		FirstPos				= 0;
		LastPos				= 0;
		Ascending			= false;
		WithDescription	= true;
		VBNTotalObjectsAct= 0;
		VBNTotalObjects	= 0;
		ReqTotalObjects	= 0;
		ReqTotalObjectsAct= 0;
		ObjectsNum			= 0;
		CreatedAfter		= 0;
		CreatedBefore		= INT_MAX;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// ����:
	identifier		VBN;					// ������������� VBN, ��� �������� ������� ��������� ������.
	identifier_arr	Concept;				// ������ ��������� ��������.
	int				FirstPos;			// ������� � �������� ������� �������.
	int				LastPos;				// ������� � �������� ���������� �������.
	bool				Ascending;			// ���������� �� �����������.
	bool				WithDescription;	// �������� �� ��������.
	string_arr		Indices;				// ������ �������� ��������, �������� ������� � ������ ���� ������.
	string			KeyIndex;			// �������� �������, �� �������� ���������� ����������.
	time_t			CreatedAfter;		// ���� ������ ����� ���������� �������
	time_t			CreatedBefore;		// ���� ������ �� ���������� �������

//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
// �����:
	string_arr		RawTable;				// ��������� ������ � ����������� ����������� ��������.
	int_arr			Total;					// ����� � VBN �� ��������� � ���� ��������.
	int_arr			SubTotal;				// ����� � ������ ������ �� ����������� ��������.
	int_arr			ReqTotal;				// ����� �� ����������� �������� � ��������������� ������.
	int				VBNTotalObjects;		// ����� �������� � ������ VBN.
	int				VBNTotalObjectsAct;	// ����� �������� �������� � ������ VBN.
	int				ReqTotalObjects;		// ����� ��������, ��������������� �������
	int				ReqTotalObjectsAct;	// ����� �������� ��������, ��������������� �������
	int				ObjectsNum;				// ���������� ��������, ������ �� ������� ��������� � RawTable.
};
//----------------------------------------------------------------------------[] 

// �������� ����������� ���������� �� ������.
BX_RESULT BX_RateStats_Site				(BX_RateStats_Args& arg);
//____________________________________________________________________________[]



#endif   // end of BX_Rating_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/