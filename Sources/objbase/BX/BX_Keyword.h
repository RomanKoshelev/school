/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Keyword.h                                                 []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     ������� ��� ������ � �������� "�������� �����".           []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                              
#ifndef BX_Keyword_H
#define BX_Keyword_H

// ��������� � �������� ������ Keywords ���� idSite �� ����������� ���� idVBN.
// �������������� �������� �������� ���� ������������ � ������� idKeywords.
BX_RESULT 
BX_Keyword_AddSite(const string_arr& Keywords, identifier idSite, identifier idVBN, identifier_arr& idKeywords);


// ������� ���� idSite �� ������� � �������� �������� ���� idKeywords.
BX_RESULT
BX_Keyword_DeleteSite(const identifier_arr& idKeywords, identifier idSite, identifier idVBN);

BX_RESULT
BX_Keyword_IDToStr(string_arr& Keywords, const identifier_arr& idKeywords);

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/