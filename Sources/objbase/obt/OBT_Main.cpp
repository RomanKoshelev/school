/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            main.cpp																	[]
[] Date:            01/22/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     ���� � ������� �������� main										[]
[]____________________________________________________________________________[]
*/

#include "ob.h"

DECLARE_SYSTEM_OBJECTS;

//================================================================================================[] 
MM_IS_A_FIRST_OBJECT;											// ����������� ������� ������ ��������� ������
//================================================================================================[] 


//================================================================================================[] 
bool CLEAR_FILE_SYSTEM_BEFORE_START	= false;				// ���� true -- �������� �������� �������.
char * FILE_SYSTEM_PATH_AND_NAME		= "files/test";	// ���� � �������� ������� � � ��������.
char * THIS_PROJECT_PREFIX		      = "TEST";	      // ������� (������������) �������� �������.
IMPLEMENT_SYSTEM_OBJECTS;										// ��������� �� �������� ���������� �������.
//================================================================================================[] 




//================================================================================================[] 
int main (int argc, char *argv[])
{
	int	nRetVal=0;												// ��������, ������������ int main(...)
	CHECK_START_STOP;												// ��������� ������� �� ������/������� ����.
	CREATE_SYSTEM_OBJECTS;										// �������� �������� ��������� ��������
	SERVER_DEBUG_TEXT ("main: ���������� � ������.");	// ���������������� ������ ������.

// []--------- ������ ���� �������� ������� �����. ----- []
// []																		[]
	(void) argc; 
	(void) argv;

	RunTest ();

// []																		[]
// []--------- ������ � ���� ����� ������ �� ����. ----- []

	SERVER_DEBUG_TEXT ("main: ��������� ������.");		// ���������������� ��������� ������.
	DELETE_SYSTEM_OBJECTS;										// �������� �������� ��������� ��������

	return nRetVal;
}
//================================================================================================[] 





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
