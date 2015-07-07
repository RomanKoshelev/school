/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_VBN.h                                                  []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "����������� ��������� ����"[]
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                             
#ifndef BX_VBN_H
#define BX_VBN_H

/*______________________________________________________________________________
[]                                                                            []
[]` ObjectState                                                               []           
[]                                                                            */
enum	ObjectState
{
	OBJ_STATE_CHECKED,
	OBJ_STATE_NEW,
	OBJ_STATE_CHANGED_CRITICAL,
	OBJ_STATE_CHANGED
};

//______________________________________________________________________________
// 																									[]
//` VBN																								[]   
// 																									[]
struct BX_VBN_Args
{ 
	BX_VBN_Args()
	{
		DefaultLanguage	= NA;
		DefaultTZOffset	= 0;
		Owner					= NA;
		No						= 255;
		objID					= NA;
		objLanguageNo		= -1;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
	}

				string			Password;				// ������ ��� ������� � ���������� ����.
				string			Name;						// �������� ����.
				string			Description;			// �������� ����.

				bool				IsModerated;			// �������� �� ���� ���������������.

				identifier		DefaultLanguage;		// ID ����� ���� �� ���������.
				time_t			DefaultTZOffset;		// �������� �������� ����� �� ��������� (� ��������).

				identifier		Owner;					// �������� ����, �������� ���� �������� � �������.

				identifier_arr ConceptMask;			// ������ ��������������� ������������ � ���� ��������� (���� �� ����, �� ������������ ��� ��������).

	READONLY byte				No;						// ���������� ����� ����.

				identifier		objID;					// ������������� �������.
				int				objLanguageNo;			// ���������� ����� �����, �� ������� �������� ����������, �� ��������� ����� ����� VBN.
				int				objFirstNo;				// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;				// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
	READONLY identifier_arr	objIDs;					// ������ ��������������� ��������.
	READONLY string_arr		objNames;				// ������ �������� ��������.
				string			AdminPassword;			// ������ ��������������.
																
};

// �������� ����������� ��������� ����.
// �� ����� ����� ������ ��������� ���� Password, ������� ����� ����������� 
// ��� ������� �� ���� �������� � ������ VBN, � ����� ������ �������������� 
// AdminPassword. � ������ �������� � objID ������������ ������������� ���������� �������.
BX_RESULT BX_VBN_New(BX_VBN_Args& arg);

// ��������� ���������� ����������� ��������� ���� � ��������������� objID.
// �� ����� ����� ������ ��������� ���� Password.
BX_RESULT BX_VBN_PutData(BX_VBN_Args& arg);

// ��������� ��������������� (� objIDs) � �������� (objNames)
// ���� ����������� �������� �����, ������������������ � �������.
BX_RESULT BX_VBN_Enumerate(BX_VBN_Args& arg);

// ��������� ���������� ����������� ��������� ���� � ��������� objID.
// ������ ��������� ���� ���������� �� �����.
BX_RESULT BX_VBN_GetData(BX_VBN_Args& arg);

// ��������� ��������������� (� objIDs) � �������� (objNames)
// ���� ��������� ����������� �������� ���� � ��������������� objID.
BX_RESULT BX_VBN_ConceptEnumerate(BX_VBN_Args& arg);

// ��������� �������������� ��������� ����.
// �� ����� ����� ������ ��������� ���� Password.
BX_RESULT BX_VBN_GetOwnerID(BX_VBN_Args& arg);

// �������� ����������� ��������� ���� � ��������� ��������������� objID.
// ���������� �������� ���������� ������ �������������� AdminPassword.
BX_RESULT BX_VBN_Delete(BX_VBN_Args& arg);

// ���������� � objIDs � objNames �������������� � ����� 
// ��������, ���������� ���������, ���������  �������� �������
// �� VBN � id=objID. ���������� ������� ������ ��� ����������� ���� Password.
BX_RESULT BX_VBN_UserEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_BannerEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_SiteEnumerate						(BX_VBN_Args& arg);
BX_RESULT BX_VBN_BannerProfileEnumerate         (BX_VBN_Args& arg);
BX_RESULT BX_VBN_SiteProfileEnumerate           (BX_VBN_Args& arg);

BX_RESULT BX_VBN_UnallowedUserEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedSiteEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedSiteProfileEnumerate	(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedBannerEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_UnallowedBannerProfileEnumerate(BX_VBN_Args& arg);

BX_RESULT BX_VBN_NewUserEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewSiteEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewSiteProfileEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewBannerEnumerate					(BX_VBN_Args& arg);
BX_RESULT BX_VBN_NewBannerProfileEnumerate		(BX_VBN_Args& arg);

BX_RESULT BX_VBN_ChangedUserEnumerate           (BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedSiteEnumerate				(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedSiteProfileEnumerate		(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedBannerEnumerate			(BX_VBN_Args& arg);
BX_RESULT BX_VBN_ChangedBannerProfileEnumerate	(BX_VBN_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/