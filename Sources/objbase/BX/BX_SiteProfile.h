/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_SiteProfile.h                                          []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������� �����".            []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                     
#ifndef BX_SiteProfile_H
#define BX_SiteProfile_H


//______________________________________________________________________________
//                                                                            []
//` SiteProfile                                                               []           
//                                                                            []

struct BX_SiteProfile_Args
{
	BX_SiteProfile_Args()
	{
		VBN				= NA;
		LastModified	= 0;
		OwnerID			= NA;
		UseKeywords		= false;
		Allowed			= false;
		MaxFileSize		= 0;
		ObjectState		= 1;
		objID				= NA;
		objFromID		= NA;

		objFirstNo		= 0;
		objLastNo		= INT_MAX;
	}
				string			Name;						// �������� �������.
	READONLY	identifier_arr Site;						// ID ������, ������������ ������ ��������.
	READONLY	string_arr		sSite;					// ����� ������, ������������ ������ ��������.
	READONLY	identifier		VBN;						// ID ����������� �������.
	READONLY	time_t			LastModified;			// ����� ���������� ��������� �������.
	READONLY	string			sLastModified;			// ����� ���������� ��������� ������� � ��������� �������������.
	READONLY	identifier		OwnerID;					// ������������� ������������-���������.

// �����������/����������� �������:
				identifier_arr BannerInclude;			// ������ ����������� � ������ ��������.
				identifier_arr BannerExclude;			// ������ ����������� � ������ ��������.
				identifier_arr SiteInclude;			//	������ ����������� � ������� ������.
				identifier_arr SiteExclude;			//	������ ����������� � ������� ������.

// ���������� � �������� :
				int				MaxFileSize;			// ������������ ������ ����� � ���������.
				bool				UseKeywords;			// ���������� ������� � ������������ � ��������� ������� ������.

				identifier_arr	BannerConceptInclude;// ������ ����������x � ������ ��������� ��������.
				identifier_arr	BannerConceptExclude;// ������ ����������� � ������ ��������� ��������.

	READONLY	bool				Allowed;					// ���������� ������������ ��������� �����������.
	READONLY	int				ObjectState;			// ��������� �������: 0 - ��������; 1 - �����;  2 - �������� ����������� ����; 3 - ������.
	READONLY	identifier_arr	ModeratorComment;		// ����������� ����������.

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]

				identifier		objID;					// ������������� ������� �����.
				string			objPassword;			// ������ ������������-��������� �������.
																
	READONLY	identifier		objFromID;				// ������������� source-�������.

				int				objFirstNo;				// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;				// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
																
	READONLY	identifier_arr	objIDs;					// �������������� ��������.
	READONLY	string_arr		objNames;				// ����� ������������ ����� ��������� *Enumerate().
};
//----------------------------------------------------------------------------[]

// ������ ������� ����� ��� ������������ � ��������������� OwnerID.
// ���� ������ objFromID , �� � ��������� ������� ����������
// ��������� �� ������� � ��������������� objFromID.
// � objID ������������ id ���������� �������.
// � Name ������������ �������� ���������� �������.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_SiteProfile_New(BX_SiteProfile_Args& arg);

//	����������� ��������� ������� ����� �� ������� objFromID � ������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_SiteProfile_CopyData(BX_SiteProfile_Args& arg);

//	��������� ��������� ������� ����� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_SiteProfile_GetData(BX_SiteProfile_Args& arg);

//	��������� ��������� ������� ����� � ��������� objID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_SiteProfile_PutData(BX_SiteProfile_Args& arg);

//	�������� ��������� ������� ����� � ��������� ID.
// ���������� ������� ������ ������������-��������� objPassword.
BX_RESULT BX_SiteProfile_Delete(BX_SiteProfile_Args& arg);

// !!!
BX_RESULT BX_SiteProfile_Enumerate(BX_SiteProfile_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/