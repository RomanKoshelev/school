/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Auto.cpp                                        []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     ������������ ������� ��� ������ � ����� ������.           []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________[]
*/
#include "BX_Interface.h"



//______________________________________________________________________________
//                                                                            []
// ��������� ������� ���������� ������                                        []
//                                                                            []
void CGI_Interface (const char* CGI_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)
{
// ����� ������������������ �������
   FNC_BEGIN;
   {
   // EnumObject
      FNC        (BX_EnumObject_New, "�������� ��� ��������� ���������� �������������� ���� ObjType.");
			FNC_IN  (BX_EnumObject, ObjType, "������ � ��������� ���� �������: {Country, City, Domain,ISP}.");
			FNC_IN  (BX_EnumObject, Name, "������ �������� (�� ���� ������ �������) ������������� ���� ObjType.");
			FNC_IN  (BX_EnumObject, objID, "���� �� ������, �� �������� ����� ������");
			FNC_OUT (BX_EnumObject, objID, "� ������ �������� ������� = ID ���������� �������.");
      FNC        (BX_EnumObject_GetData, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, Name, "");
			FNC_IN  (BX_EnumObject, objID, "");
      FNC        (BX_EnumObject_GetNamesAndIDs, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, objID, "");
			FNC_OUT (BX_EnumObject, objIDs, "");
			FNC_OUT (BX_EnumObject, Name, "");
      FNC        (BX_EnumObject_Delete, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, objID, "");
			FNC_OUT (BX_EnumObject, objID, "");

   // Language
      FNC        (BX_Language_New, "���������� �����. � objID ������������ ������������� ���������� �������.");
			FNC_IN  (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_IN  (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������.");
			FNC_IN  (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_OUT (BX_Language, objID, "������������� �������.");
      FNC        (BX_Language_PutData, "��������� ���������� ������������� �����.");
			FNC_IN  (BX_Language, objID, "������������� �������.");
			FNC_IN  (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_IN  (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������.");
			FNC_IN  (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
      FNC        (BX_Language_GetNamesAndIDs, "��������� �������� ���� ������, ������������������ � ������� �� ����� #1. �������� ������������ � ���� Name[] ������� ���������. ��������������� �������������� ������������ � ���� objIDs[] ������� ���������.");
			FNC_IN  (BX_Language, objID, "������������� �������.");
			FNC_OUT (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������.");
			FNC_OUT (BX_Language, objIDs, "�������������� ��������.");
      FNC        (BX_Language_GetData, "��������� ���������� � ����� � ��������� ID.");
			FNC_IN  (BX_Language, objID, "������������� �������.");
			FNC_OUT (BX_Language, OwnName, "�������� ������� ����� �� ����� ����.");
			FNC_OUT (BX_Language, Name, "������ �������� ����� �� ���� �������������� ������.");
			FNC_OUT (BX_Language, Language, "������ �������� �������������� ������ �� ����������� �����. ������� ���������� �������� ������ ��������������� ������� ���������� ������ � �������.");
			FNC_OUT (BX_Language, No, "���������� ����� �����");
      FNC        (BX_Language_Delete, "�������� �����.");
			FNC_IN  (BX_Language, objID, "������������� �������.");

   // QQQQQ
      FNC        (BX_QQQQQ_GetData, "��������� ���������� � ����� � ��������� ID.");
   }
// ����� ������������ ������� ��� ��������� �� ������.
   FNC_END;
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
// �������� ��� ��������� ���������� �������������� ���� ObjType.
//                                                                            []
void CGI_BX_EnumObject_New (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (ObjType);
   GET_ARG (Name);
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_EnumObject_New (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_GetData ()
//                                                                            []
void CGI_BX_EnumObject_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (ObjType);
   GET_ARG (Name);
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_EnumObject_GetData (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
   // �������� ���������� ���.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_GetNamesAndIDs ()
//                                                                            []
void CGI_BX_EnumObject_GetNamesAndIDs (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (ObjType);
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_EnumObject_GetNamesAndIDs (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (Name);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_Delete ()
//                                                                            []
void CGI_BX_EnumObject_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (ObjType);
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_EnumObject_Delete (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ���������� �����. � objID ������������ ������������� ���������� �������.
//                                                                            []
void CGI_BX_Language_New (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// ������� ���������� �������:
   cgi_result = BX_Language_New (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ���������� ������������� �����.
//                                                                            []
void CGI_BX_Language_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (objID);
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// ������� ���������� �������:
   cgi_result = BX_Language_PutData (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
   // �������� ���������� ���.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� �������� ���� ������, ������������������ � ������� �� ����� #1. �������� ������������ � ���� Name[] ������� ���������. ��������������� �������������� ������������ � ���� objIDs[] ������� ���������.
//                                                                            []
void CGI_BX_Language_GetNamesAndIDs (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_Language_GetNamesAndIDs (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (objIDs);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ���������� � ����� � ��������� ID.
//                                                                            []
void CGI_BX_Language_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_Language_GetData (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (OwnName);
      PACK_ARG (Name);
      PACK_ARG (Language);
      PACK_ARG (No);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����.
//                                                                            []
void CGI_BX_Language_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// �������� ������ ��������� �� ������ inStr � ��������� cgi_args:
   GET_ARG (objID);

// ������� ���������� �������:
   cgi_result = BX_Language_Delete (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
   // �������� ���������� ���.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ���������� � ����� � ��������� ID.
//                                                                            []
void CGI_BX_QQQQQ_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   BX_QQQQQ_Args        cgi_args;
   int                  cgi_result;

// ������� ���������� ���.

// ������� ���������� �������:
   cgi_result = BX_QQQQQ_GetData (cgi_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (cgi_result == CGI_OK)
   {
   // �������� ���������� ���.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
