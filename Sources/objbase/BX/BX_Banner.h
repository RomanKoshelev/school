/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Banner.h                                               []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������".					      []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                
#ifndef BX_Banner_H
#define BX_Banner_H

//______________________________________________________________________________
//                                                                            []
//` Banner                                                                    []      
//                                                                            []

// ��������� ��� ���������/��������� ���������� �������.
struct BX_Banner_Args
{
	BX_Banner_Args()
	{
		OwnerID				= NA;
		FileSize				= 0;
		UploadNo				= 0;
		VBN					= NA;
		Profile				= NA;
		CreationTime		= 0;
		TotalShows			= 0;
		TotalClicks			= 0;
		Allowed				= false;
		State					= true;
		ObjectState			= 1;
		objID					= NA;

		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}

	READONLY	identifier		OwnerID;				// ������������� ��������� �������.
	READONLY	string			FileName;			// ��� �������, � ������� ���������� upload.
	READONLY	int				FileSize;			// ������ ����� �������.
				int				UploadNo;			// ���������� ��������� �������� �����.
															
	READONLY	time_t			CreationTime;		// ����� �������� �������.
	READONLY	string			sCreationTime;		// ����� �������� ������� ��������� ����.
	READONLY	identifier		VBN;					// ID ����������� ����, � ������� ����������� ������.
															
				bool				State;				// ��������� ������� (����/���).
															
				identifier		Profile;				// ������������� ������� �������.
															
				identifier_arr	Concept;				// ��������, ������� ��������� � �������.
															
	READONLY	int				TotalShows;			// ���������� ������� �������.
	READONLY	int				TotalClicks;		// ���������� ������� �� ������.
															
	READONLY	bool				Allowed;				// ���������� ������������ ��������� �����������.
	READONLY	int				ObjectState;		// ��������� �������: 0 - ��������; 1 - �����; 2 - �������� ����������� ����; 3 - ������.

	READONLY	identifier_arr	ModeratorComment;	// ����������� ����������.
//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
				identifier		objID;				// ������������� ������� �������.
				string			objPassword;		// ������ ������������-��������� �������.

				int				objFirstNo;			// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;			// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
															
	READONLY	identifier_arr	objIDs;				// �������������� ��������.
	READONLY	string_arr		objNames;			// ����� ������������ ����� ��������� *Enumerate().
};
//----------------------------------------------------------------------------[]

// �������� �������. ��������� OwnerID ��������� � FileName �������.
// ������������� ���������� ������� ������������ � objID. 
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Banner_New(BX_Banner_Args& arg);

// ��������� ���������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Banner_GetData(BX_Banner_Args& arg);

// ��������� ���������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Banner_PutData(BX_Banner_Args& arg);

// �������� ������� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_Banner_Delete(BX_Banner_Args& arg);

// !!!
BX_RESULT BX_Banner_Enumerate(BX_Banner_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/