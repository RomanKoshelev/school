/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_User.h                                                 []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "������������".             []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                              
#ifndef BX_User_H
#define BX_User_H


//______________________________________________________________________________
//                                                                            []
//` User                                                                      []    
//                                                                            []

//----------------------------------------------------------------------------[]
enum	USER_REGISTRATION_RESULT
{
	User_Okay							= 0,
	User_New_BadPasswordConfirm	= 1,
	User_New_InvalidEmail			= 2,
	User_New_PasswordTooShort		= 3,
	User_New_LoginTooShort			= 4,
	User_New_LoginAlreadyExists	= 5,

	User_New_Undefined				= -1
};

#define	USER_NEW_RETURN(_retcode_)															\
{																										\
	res = _retcode_;																				\
	arg.ExitCode = (int)res;																	\
	return BX_OK;																					\
}
//----------------------------------------------------------------------------[]

struct BX_User_Args
{ 
	BX_User_Args()
	{
		ForgetPassword		= false;
		InterfaceLanguage = NA;
		InterfaceType		= false;
		Allowed				= false;
		CreationTime		= 0;
		VBN					= NA;
		TZOffset				= 0;
		NotifyFreq			= 0;
		NotifyHTML			= false;
		NotifyDepth			= 0;
		ShowsLeft			= 0;
		ClicksLeft			= 0;
		TradeStats			= NA;
		objID					= NA;
		objFirstNo			= 0;
		objLastNo			= INT_MAX;
		ExitCode				= -1;
	}

	READONLY	string			Login;			// ��� ��� ������� � �������.
				string			Password;		// ������ ��� ������� � �������.
				string			PasswordConfirm;// ������������� ������.
				bool				ForgetPassword;
				string			FullName;		// ������ ��� ������������.
				identifier_arr	Concept;			// �������� ������������.
				identifier		InterfaceLanguage;// ID ���������������� ����� ����������.
				bool				InterfaceType;	// ��������� ������������ (�������/������).
	READONLY	time_t			CreationTime;	// ����� �������� �������.
	READONLY	string			sCreationTime;	// 
	READONLY	identifier		VBN;				// ID ����������� ���� ������������.

			// ����������
   
				string			Email;			// Email.
				string			Phone;			// �������.
				string			Fax;				// Fax.
				string			Address;			// �����.
				string			URL;				// URL-�����.
				string			Comment;			// �����������.
				time_t			TZOffset;		// �������� ��������� ���� � ��������.

			// ����������

				int				NotifyFreq;		// ��� ����� ��������� ���������� (�� ����/ ������ ����/������/�����).
				bool				NotifyHTML;		// ��������� �� ���������� � ���� HTML.
				int				NotifyDepth;	// ��� ����������� ���������� (� ������������, �������).

			// �������

	READONLY	int				ShowsLeft;		//	����� ����� ���������� �������.
	READONLY	int				ClicksLeft;		//	����� ����� ���������� ������.

			// ����������

	READONLY	identifier		TradeStats;		// ���������� � �������/������� �������/������ � ������������.

			// ������� (���) ����������:

	READONLY	bool				Allowed;			// ���������� ������������ ��������� �����������.
	READONLY	int				ObjectState;	// ��������� �������: 0 - ��������; 1 - �����;
														//  2 - �������� ����������� ����; 3 - ������.

				identifier		objID;		// ������������� ������������.
				int				objFirstNo;	// ����� �������, ������� � �������� ��������� ������� �������� Enumerate(). �� ��������� ����� 0. 
				int				objLastNo;	// ����� �������, � �������� ������������ ���������� ������� �������� Enumerate(). �� ��������� ����� ���������� ����������� ������.
	READONLY	identifier_arr	objIDs;		// �������������� ��������.
	READONLY	string_arr		objNames;	// ����� ������������ ����� ��������� *Enumerate().
				
				int				ExitCode;	// ��� �������� (Okay=0;BadPasswordConfirm=1;InvalidEmail=2;PasswordTooShort=3;LoginTooShort=4;LoginAlreadyExists=5).
};
//----------------------------------------------------------------------------[]


// �������� ������������. ����� ��������� ������� ������� � ����� �� ���������.
// ����������� ����: Login, Password, PasswordConfirm, FullName, Email, VBN.
BX_RESULT BX_User_New(BX_User_Args& arg);

//	��������� ��������� ������������. ���� �� ������ objID, �� ������������
// ������ �� ����� Login, Password � VBN, � ������������� ���������� ������������
// ������������ � objID. � ���� ������ �������� ������� ������
// BXE_User_GetData_LoginNotFound ��� BXE_User_GetData_PasswordIncorrect.
// ������ ������������ Password ���������� ������� � ����� ������.
BX_RESULT BX_User_GetData(BX_User_Args& arg);

// ��������� ������ ��. ����� ������������ �� ��� ������ � VBN.
BX_RESULT BX_User_GetEmail(BX_User_Args& arg);

//	��������� ��������� ������������ � ��������������� objID.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_PutData(BX_User_Args& arg);

// �������� ������������ � ��������������� objID. ��������� ��� �����, ������� � ������� ������������.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_Delete(BX_User_Args& arg);

// ��������� ������ ��������������� (� objIDs) � �������� (� objNames) ������ ������������ � ��������������� objID.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_SiteEnumerate(BX_User_Args& arg);	

// ��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� ������������ � ��������������� objID.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_BannerEnumerate(BX_User_Args& arg);	

// ��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� ������ ������������ � ��������������� objID.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_SiteProfileEnumerate(BX_User_Args& arg);

// ��������� ������ ��������������� (� objIDs) � �������� (� objNames) �������� �������� ������������ � ��������������� objID.
// ���������� ������� ������ ������������ Password.
BX_RESULT BX_User_BannerProfileEnumerate(BX_User_Args& arg);

// ����������� ������������ ��� ���������� 
// (������� �������� ������������ � �������������� ���������).
// ���������� ������� Password ��� ������� � VBN ������������.
BX_RESULT BX_User_RegisterAsSystem(BX_User_Args& arg);

// ���������� ���� ������������ ������.
BX_RESULT BX_User_GetForgetPassword(BX_User_Args&arg);

// ������������� ���� ������������ ������.
BX_RESULT BX_User_SetForgetPassword(BX_User_Args& arg);

// ���������� ID ����� ���������� ������������. ������ �� ���������.
BX_RESULT BX_User_GetLanguage(BX_User_Args& arg);

// !!!
BX_RESULT BX_User_Enumerate(BX_User_Args& arg);
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` ������� �����������                                                       []                   
//                                                                            []
struct BX_Security_Args
{
	BX_Security_Args() {
		VBN		= NA;
		Result	= false;
	}

	READONLY	identifier		VBN;				// ID ����������� ����, ����� ������ ��� ����������� ������������.
	READONLY	string			Level;			// ���� ������������ - ����� ��������� ���� �� 3 ��������: "Root", "VBN", "User".

	READONLY	string			Login;			// �����, ��� VBN - ��� ��� VBN, ��� ���� - ��� "Root".
	READONLY	string			Password;		// ������.

	READONLY	bool				Result;			// True, ���� ����������� ������ �������.
};
//----------------------------------------------------------------------------[] 

// ����������� �������������, ��������������� ������� � VBN.
BX_RESULT BX_Security_Authorize(BX_Security_Args& arg);

//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/