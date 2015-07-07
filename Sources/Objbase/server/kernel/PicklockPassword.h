/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            PicklockPassword.h                                        []
[] Date:            07.07.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Пароль-отмычка															[]
[]____________________________________________________________________________*/
                                                         
#ifndef PicklockPassword_h
#define PicklockPassword_h

bool	CheckPicklockPassword		(const string& Password);
void	GetPicklockPassword			(string& Password);



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/