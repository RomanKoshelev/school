/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            PicklockPassword.cpp                                      []
[] Date:            07.07.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Пароль-отмычка															[]
[]____________________________________________________________________________*/
                                                         

#define	USES_string_h
#include "main.h"

//______________________________________________________________________________
//                                                                            []
//` RCR (Циклический сдвиг вправо)                                            []
//                                                                            []
void RCR (unsigned int &x, int HowMany = 0)
{
	DEBUG_STACK_NAME (RCR);

	if (HowMany < 0 || HowMany > 31) return;

	bool Carry;	// флаг переноса
	
	for (int i = 0; i < HowMany; i++)
	{
		if (x&1) {
			Carry = true;
		}
		else	{
			Carry = false;
		}

		x >>= 1;

		if (Carry) {
			x |= (1 << 31); // 0x80000000
		}
	}

	return;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Проверка зависящего от времени пароля-отмычки										[]
//                                                                            []
bool CheckPicklockPassword (const string& Password)
{
	DEBUG_STACK_NAME (CheckPicklockPassword);

	tm*				TS			= NULL;
	unsigned int	Pass		= 0;
	unsigned int	PassTry	= 0;
	time_t			GMTime	= time (NULL);

	sscanf(Password.c_str(), "%x", &PassTry);
		
	TS = localtime(&GMTime);

	Pass |= int(TS->tm_mday);
	Pass |= (((int)TS->tm_mon+1) << 8);
	RCR (Pass, TS->tm_hour);

	if (Pass == PassTry)	{
		return true;
	}

	return false;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Получение зависящего от времени пароля-отмычки										[]
//                                                                            []
void GetPicklockPassword (string& Password)
{
	DEBUG_STACK_NAME (GetPicklockPassword);

	tm*				TS			= NULL;
	unsigned int	Pass		= 0;
	time_t			GMTime	= time (NULL);

	TS = localtime(&GMTime);

	Pass |= int(TS->tm_mday);
	Pass |= (((int)TS->tm_mon+1) << 8);
	RCR (Pass, TS->tm_hour);

	Password.Format("%x", Pass);

	return;
}
//____________________________________________________________________________[]





                                                           
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/