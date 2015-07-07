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
#include "problem_interface.h"






//______________________________________________________________________________
//                                                                            []
// �������� ������������. ������������� �������� ������ ����, �������� �������� ����� �������.
//                                                                            []
void OBServer_MOD_User_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (PasswordConfirm);
   GET_ARG (PasswordInBrowser);
   GET_ARG (FullName);
   GET_ARG (Email);

// ������� ���������� �������:
   OBServer_result = MOD_User_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ����������� �������������, ��������������� �������.
//                                                                            []
void OBServer_MOD_User_Authorize (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_Authorize);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (PasswordInBrowser);

// ������� ���������� �������:
   OBServer_result = MOD_User_Authorize (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (PasswordInBrowser);
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ���� �������������.
//                                                                            []
void OBServer_MOD_User_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// ������� ���������� �������:
   OBServer_result = MOD_User_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objFullNames);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � ������������.
//                                                                            []
void OBServer_MOD_User_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_User_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Login);
      PACK_ARG (FullName);
      PACK_ARG (Email);
      PACK_ARG (URL);
      PACK_ARG (Data);
      PACK_ARG (PasswordInBrowser);
      PACK_ARG (ReadOnly);
      PACK_ARG (CreationTime);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � ������������ � ��������������� objID.
//                                                                            []
void OBServer_MOD_User_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (NewPassword);
   GET_ARG (NewPasswordConfirm);
   GET_ARG (PasswordInBrowser);
   GET_ARG (FullName);
   GET_ARG (Email);
   GET_ARG (URL);
   GET_ARG (Data);

// ������� ���������� �������:
   OBServer_result = MOD_User_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������ ���� ������������.
//                                                                            []
void OBServer_MOD_User_GetRights (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_GetRights);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (ExpandGroups);
   GET_ARG (ExpandRights);

// ������� ���������� �������:
   OBServer_result = MOD_User_GetRights (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Login);
      PACK_ARG (LoginAccessLevel);
      PACK_ARG (LoginGroupIDs);
      PACK_ARG (LoginGroupNames);
      PACK_ARG (LoginGroupTypes);
      PACK_ARG (LoginGroupRights);
      PACK_ARG (LoginOwnRights);
      PACK_ARG (ObjAccessLevel);
      PACK_ARG (ObjGroupIDs);
      PACK_ARG (CreationTime);
      PACK_ARG (ReadOnly);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ���� ������������ � ��������������� objID.
//                                                                            []
void OBServer_MOD_User_PutRights (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_PutRights);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (AccessLevel);
   GET_ARG (objIDs);

// ������� ���������� �������:
   OBServer_result = MOD_User_PutRights (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������������� ������� � ���� ��������� ����.
//                                                                            []
void OBServer_MOD_User_CheckOwnRights (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_CheckOwnRights);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (FeodNames);
   GET_ARG (FeodAttributes);

// ������� ���������� �������:
   OBServer_result = MOD_User_CheckOwnRights (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Accesses);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������������ � ��������������� objID. ��������� ��� �������, �������� �� ������. ������������ ��������� �� �����.
//                                                                            []
void OBServer_MOD_User_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_User_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_User_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_User_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������.
//                                                                            []
void OBServer_MOD_UserGroup_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserGroup_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserGroup_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Type);
   GET_ARG (Description);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_UserGroup_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ��������� �����.
//                                                                            []
void OBServer_MOD_UserGroup_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserGroup_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserGroup_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// ������� ���������� �������:
   OBServer_result = MOD_UserGroup_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objTypes);
      PACK_ARG (objAccessLevelThresholds);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � ������.
//                                                                            []
void OBServer_MOD_UserGroup_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserGroup_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserGroup_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (UserFirstNo);
   GET_ARG (UserLastNo);

// ������� ���������� �������:
   OBServer_result = MOD_UserGroup_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Type);
      PACK_ARG (Description);
      PACK_ARG (AccessLevelThreshold);
      PACK_ARG (CreationTime);
      PACK_ARG (FeodIDs);
      PACK_ARG (FeodNames);
      PACK_ARG (FeodAttributes);
      PACK_ARG (UserIDs);
      PACK_ARG (UserLogins);
      PACK_ARG (UserFullNames);
      PACK_ARG (UserAccessLevels);
      PACK_ARG (UserCreationTimes);
      PACK_ARG (UserTotalStoredNum);
      PACK_ARG (UserMaxNumInQuery);
      PACK_ARG (ReadOnly);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ ������.
//                                                                            []
void OBServer_MOD_UserGroup_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserGroup_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserGroup_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Type);
   GET_ARG (Description);
   GET_ARG (AccessLevelThreshold);
   GET_ARG (FeodIDs);
   GET_ARG (FeodAttributes);

// ������� ���������� �������:
   OBServer_result = MOD_UserGroup_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������. � ���� �������������, ������������� � ������, ��� ��������� �� ������ �����.
//                                                                            []
void OBServer_MOD_UserGroup_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserGroup_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserGroup_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_UserGroup_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ���� �������. ����������� � ������� ������ �� ����� ���������� � � ������ ������ ���� ���������.
//                                                                            []
void OBServer_MOD_Feod_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Feod_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Feod_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Type);
   GET_ARG (Description);
   GET_ARG (ParentID);
   GET_ARG (ParentName);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_Feod_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ��� �������. ������������ ������ ��, � ������� ���� ������ [L].
//                                                                            []
void OBServer_MOD_Feod_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Feod_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Feod_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (ParentID);
   GET_ARG (ParentName);

// ������� ���������� �������:
   OBServer_result = MOD_Feod_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objTypes);
      PACK_ARG (objDescriptions);
      PACK_ARG (objParentIDs);
      PACK_ARG (objThresholds);
      PACK_ARG (objExtClassNames);
      PACK_ARG (objExtIDs);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ���� �������. ������������ ������ ����� ����� �������� [D] � ����� ��������������� � ��������� ������� � ��� �������.
//                                                                            []
void OBServer_MOD_Feod_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Feod_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Feod_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_Feod_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ��������������� �������.
//                                                                            []
void OBServer_MOD_InfoDiv_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoDiv_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoDiv_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (ParentID);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_InfoDiv_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ��������� ��������.
//                                                                            []
void OBServer_MOD_InfoDiv_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoDiv_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoDiv_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (ParentID);
   GET_ARG (ParentName);
   GET_ARG (IncludeParent);
   GET_ARG (FeodAttributes);
   GET_ARG (FullNameLevel);

// ������� ���������� �������:
   OBServer_result = MOD_InfoDiv_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objTypes);
      PACK_ARG (objLevels);
      PACK_ARG (objFeodIDs);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �������.
//                                                                            []
void OBServer_MOD_InfoDiv_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoDiv_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoDiv_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_InfoDiv_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ��������������� �������
//                                                                            []
void OBServer_MOD_InfoObject_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoObject_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (Text);
   GET_ARG (InfoSourceID);
   GET_ARG (URL);
   GET_ARG (RelatedLinks);
   GET_ARG (divIDs);
   GET_ARG (InfoTime);
   GET_ARG (AuthorStr);

// ������� ���������� �������:
   OBServer_result = MOD_InfoObject_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ProxyID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ �������������� ��������. ������������ ��� �� ����� ������� �������� � ����� ������.
//                                                                            []
void OBServer_MOD_InfoObject_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoObject_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Time0);
   GET_ARG (Time1);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (divIDs);
   GET_ARG (divNames);
   GET_ARG (divLookInSub);
   GET_ARG (divAttributes);
   GET_ARG (UpdateStatistics);
   GET_ARG (InfoSourceID);
   GET_ARG (bNeedTotalStoredNum);
   GET_ARG (bNeedText);
   GET_ARG (bNeedURL);
   GET_ARG (bNeedLog);

// ������� ���������� �������:
   OBServer_result = MOD_InfoObject_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objProxyIDs);
      PACK_ARG (objNames);
      PACK_ARG (objDescriptions);
      PACK_ARG (objLogCreatorIDs);
      PACK_ARG (objLogCreatorLogins);
      PACK_ARG (objLogCreatorNames);
      PACK_ARG (objLogPublisherIDs);
      PACK_ARG (objLogPublisherLogins);
      PACK_ARG (objLogPublisherNames);
      PACK_ARG (objLogForbidderIDs);
      PACK_ARG (objLogForbidderLogins);
      PACK_ARG (objLogForbidderNames);
      PACK_ARG (objLogHotterIDs);
      PACK_ARG (objLogHotterLogins);
      PACK_ARG (objLogHotterNames);
      PACK_ARG (objTexts);
      PACK_ARG (objURLs);
      PACK_ARG (objInfoTimes);
      PACK_ARG (objStatShows);
      PACK_ARG (objStatClicks);
      PACK_ARG (objStatCTRs);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ ��������������� �������.
//                                                                            []
void OBServer_MOD_InfoObject_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoObject_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (UpdateStatistics);
   GET_ARG (bNeedLog);

// ������� ���������� �������:
   OBServer_result = MOD_InfoObject_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ProxyID);
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (Text);
      PACK_ARG (URL);
      PACK_ARG (RelatedLinks);
      PACK_ARG (InfoSourceID);
      PACK_ARG (InfoSourceName);
      PACK_ARG (InfoSourceURL);
      PACK_ARG (InfoTime);
      PACK_ARG (StatShow);
      PACK_ARG (StatClick);
      PACK_ARG (StatCTR);
      PACK_ARG (divIDs);
      PACK_ARG (divNames);
      PACK_ARG (AuthorStr);
      PACK_ARG (OwnerID);
      PACK_ARG (OwnerLogin);
      PACK_ARG (OwnerName);
      PACK_ARG (Log_Action);
      PACK_ARG (Log_Description);
      PACK_ARG (Log_UserID);
      PACK_ARG (Log_UserLogin);
      PACK_ARG (Log_UserName);
      PACK_ARG (Log_Time);
      PACK_ARG (Log_Comment);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ ��������������� �������.
//                                                                            []
void OBServer_MOD_InfoObject_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoObject_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (Text);
   GET_ARG (URL);
   GET_ARG (RelatedLinks);
   GET_ARG (InfoSourceID);
   GET_ARG (InfoTime);
   GET_ARG (divIDs);
   GET_ARG (AuthorStr);

// ������� ���������� �������:
   OBServer_result = MOD_InfoObject_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ��������� ����������.
//                                                                            []
void OBServer_MOD_InfoSource_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoSource_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoSource_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (URL);
   GET_ARG (RefreshType);
   GET_ARG (divIDs);

// ������� ���������� �������:
   OBServer_result = MOD_InfoSource_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ���� ��� ������ ��������� ������������ ��� ������ ���������� ���������� (�.�. ����������� � ��������, � ������� �� ����� ��������� ��� ������������� �������)
//                                                                            []
void OBServer_MOD_InfoSource_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoSource_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoSource_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (ShowAll);
   GET_ARG (divID);
   GET_ARG (divName);

// ������� ���������� �������:
   OBServer_result = MOD_InfoSource_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objURLs);
      PACK_ARG (objRefreshTypes);
      PACK_ARG (objDescriptions);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ ��������� ����������.
//                                                                            []
void OBServer_MOD_InfoSource_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoSource_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoSource_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_InfoSource_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (URL);
      PACK_ARG (RefreshType);
      PACK_ARG (divIDs);
      PACK_ARG (divNames);
      PACK_ARG (ShowCount);
      PACK_ARG (ClickCount);
      PACK_ARG (CTR);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ ��������� ����������.
//                                                                            []
void OBServer_MOD_InfoSource_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoSource_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoSource_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (URL);
   GET_ARG (RefreshType);
   GET_ARG (divIDs);

// ������� ���������� �������:
   OBServer_result = MOD_InfoSource_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ��������� ����������. �������� ��������� �������� �� �������� � �������������� ��������.
//                                                                            []
void OBServer_MOD_InfoSource_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_InfoSource_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_InfoSource_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_InfoSource_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����.
//                                                                            []
void OBServer_MOD_WebFolder_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFolder_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFolder_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (ParentID);
   GET_ARG (ParentName);
   GET_ARG (AccessLevelThreshold);
   GET_ARG (GroupIDs);
   GET_ARG (GroupAttributes);

// ������� ���������� �������:
   OBServer_result = MOD_WebFolder_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ �����. ������������ ������ �� �����, ������� ����� ���� �����������, �.�. � ������� ���� ������ [L]
//                                                                            []
void OBServer_MOD_WebFolder_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFolder_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFolder_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (ParentID);
   GET_ARG (ParentName);
   GET_ARG (IncludeParent);
   GET_ARG (AllDescendants);
   GET_ARG (FeodAttributes);
   GET_ARG (FullNameLevel);

// ������� ���������� �������:
   OBServer_result = MOD_WebFolder_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objTypes);
      PACK_ARG (objLevels);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �����.
//                                                                            []
void OBServer_MOD_WebFolder_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFolder_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFolder_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_WebFolder_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (FullName);
      PACK_ARG (Description);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �����.
//                                                                            []
void OBServer_MOD_WebFolder_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFolder_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFolder_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);

// ������� ���������� �������:
   OBServer_result = MOD_WebFolder_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����.
//                                                                            []
void OBServer_MOD_WebFolder_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFolder_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFolder_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_WebFolder_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����
//                                                                            []
void OBServer_MOD_WebFile_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFile_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFile_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (Name_Upload);
   GET_ARG (OS_Path);
   GET_ARG (OS_Ext);
   GET_ARG (MIMEType);
   GET_ARG (IconType);
   GET_ARG (PlainTextData);
   GET_ARG (BinaryData);
   GET_ARG (folderIDs);

// ������� ���������� �������:
   OBServer_result = MOD_WebFile_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ������. ������������ ��� � ���������� �������.
//                                                                            []
void OBServer_MOD_WebFile_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFile_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFile_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (folderID);
   GET_ARG (folderName);
   GET_ARG (UpdateStatistics);

// ������� ���������� �������:
   OBServer_result = MOD_WebFile_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objOSNames);
      PACK_ARG (objIconTypes);
      PACK_ARG (objDescriptions);
      PACK_ARG (objCreationTimes);
      PACK_ARG (objStatShows);
      PACK_ARG (objStatClicks);
      PACK_ARG (objStatCTRs);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �����
//                                                                            []
void OBServer_MOD_WebFile_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFile_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFile_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (UpdateStatistics);
   GET_ARG (NeedBinaryData);
   GET_ARG (NeedPlainTextData);

// ������� ���������� �������:
   OBServer_result = MOD_WebFile_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Name_Upload);
      PACK_ARG (Name_OS);
      PACK_ARG (Description);
      PACK_ARG (CreationTime);
      PACK_ARG (Version);
      PACK_ARG (MIMEType);
      PACK_ARG (IconType);
      PACK_ARG (BinaryData);
      PACK_ARG (PlainTextData);
      PACK_ARG (OwnerID);
      PACK_ARG (folderIDs);
      PACK_ARG (folderNames);
      PACK_ARG (StatShow);
      PACK_ARG (StatClick);
      PACK_ARG (StatCTR);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �����.
//                                                                            []
void OBServer_MOD_WebFile_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_WebFile_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_WebFile_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (MIMEType);
   GET_ARG (IconType);
   GET_ARG (ContentChanged);
   GET_ARG (Name_Upload);
   GET_ARG (OS_Path);
   GET_ARG (OS_Ext);
   GET_ARG (PlainTextData);
   GET_ARG (BinaryData);
   GET_ARG (folderIDs);

// ������� ���������� �������:
   OBServer_result = MOD_WebFile_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ����� �� �������� ���� ������
//                                                                            []
void OBServer_MOD_FullTextIndex_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_FullTextIndex_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_FullTextIndex_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Request);
   GET_ARG (Time0);
   GET_ARG (Time1);
   GET_ARG (feodIDs);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (nLookAhead);
   GET_ARG (bNeedDescription);

// ������� ���������� �������:
   OBServer_result = MOD_FullTextIndex_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objClasses);
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objDescriptions);
      PACK_ARG (objTimes);
      PACK_ARG (objWeights);
      PACK_ARG (objPlacements);
      PACK_ARG (RequestLemma);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (SysName);
   GET_ARG (Description);
   GET_ARG (FieldNames);
   GET_ARG (FieldTypes);
   GET_ARG (FieldSysNames);
   GET_ARG (FieldDescriptions);
   GET_ARG (FieldInterfaceTypes);
   GET_ARG (FeodIDs);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ���� ��������� ������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (FeodIDs);
   GET_ARG (FeodNames);
   GET_ARG (Attributes);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
      PACK_ARG (objVersions);
      PACK_ARG (objSysNames);
      PACK_ARG (objDescriptions);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � ������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (SysName);
      PACK_ARG (Name);
      PACK_ARG (Version);
      PACK_ARG (Description);
      PACK_ARG (FieldNames);
      PACK_ARG (FieldTypes);
      PACK_ARG (FieldSysNames);
      PACK_ARG (FieldDescriptions);
      PACK_ARG (FieldInterfaceTypes);
      PACK_ARG (FeodIDs);
      PACK_ARG (AccessLevelThreshold);
      PACK_ARG (ReadOnly);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (SysName);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (FieldNames);
   GET_ARG (FieldSysNames);
   GET_ARG (FieldDescriptions);
   GET_ARG (FieldInterfaceTypes);
   GET_ARG (FeodIDs);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Version);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ����� �������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_ChangeField (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_ChangeField);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (ChangeType);
   GET_ARG (FieldID);
   GET_ARG (FieldPos);
   GET_ARG (FieldName);
   GET_ARG (FieldSysName);
   GET_ARG (FieldDescription);
   GET_ARG (FieldInterfaceType);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_ChangeField (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Version);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �������������� ���������.
//                                                                            []
void OBServer_MOD_Relation_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Relation_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Relation_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);

// ������� ���������� �������:
   OBServer_result = MOD_Relation_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����.
//                                                                            []
void OBServer_MOD_Linkage_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (RelationID);
   GET_ARG (RelationVersion);
   GET_ARG (ProxyIDs);
   GET_ARG (Values);
   GET_ARG (AccessLevelThreshold);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ���� ������, ����������� � ���������� ������-�������.
//                                                                            []
void OBServer_MOD_Linkage_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (UseRelationID);
   GET_ARG (RelationID);
   GET_ARG (bNeedFields);
   GET_ARG (FieldIndices);
   GET_ARG (RelationSysName);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objFieldsValues);
      PACK_ARG (objRelationIDs);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � ������������� �����. ������ ���� ����� ������ �� ��������� � �� ��� �������.
//                                                                            []
void OBServer_MOD_Linkage_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (FieldTypes);
      PACK_ARG (FieldValues);
      PACK_ARG (FieldObjectProxyIDs);
      PACK_ARG (FieldObjectClasses);
      PACK_ARG (FieldObjectIDs);
      PACK_ARG (FieldObjectNames);
      PACK_ARG (AccessLevelThreshold);
      PACK_ARG (ReadOnly);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ��������� ������� �� �������������� ������
//                                                                            []
void OBServer_MOD_Linkage_GetRealObjectByProxyID (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_GetRealObjectByProxyID);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_GetRealObjectByProxyID (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (RealObjectClassName);
      PACK_ARG (RealObjectID);
      PACK_ARG (RealObjectName);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ����� ������������� �����.
//                                                                            []
void OBServer_MOD_Linkage_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (RelationVersion);
   GET_ARG (ProxyIDs);
   GET_ARG (Values);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������������� �����. ������ ���� ������ [D] � ��������� � [W] �� ���� �������-����������.
//                                                                            []
void OBServer_MOD_Linkage_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_Linkage_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_Linkage_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_Linkage_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� ������������.
//                                                                            []
void OBServer_MOD_MetaObject_New (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_MetaObject_New);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_MetaObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (Type);
   GET_ARG (Name);
   GET_ARG (SysName);
   GET_ARG (FeodIDs);

// ������� ���������� �������:
   OBServer_result = MOD_MetaObject_New (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ProxyID);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ������������ ���� ��������� ������������.
//                                                                            []
void OBServer_MOD_MetaObject_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_MetaObject_Enumerate);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_MetaObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (TypePrefix);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// ������� ���������� �������:
   OBServer_result = MOD_MetaObject_Enumerate (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objTypes);
      PACK_ARG (objNames);
      PACK_ARG (objSysNames);
      PACK_ARG (objProxyIDs);
      PACK_ARG (TotalStoredNum);
      PACK_ARG (MaxNumInQuery);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ � �����������.
//                                                                            []
void OBServer_MOD_MetaObject_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_MetaObject_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_MetaObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_MetaObject_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ProxyID);
      PACK_ARG (Type);
      PACK_ARG (Name);
      PACK_ARG (SysName);
      PACK_ARG (FeodIDs);
      PACK_ARG (ReadOnly);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �����������.
//                                                                            []
void OBServer_MOD_MetaObject_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_MetaObject_PutData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_MetaObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);
   GET_ARG (Type);
   GET_ARG (Name);
   GET_ARG (SysName);
   GET_ARG (FeodIDs);

// ������� ���������� �������:
   OBServer_result = MOD_MetaObject_PutData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// �������� �����������.
//                                                                            []
void OBServer_MOD_MetaObject_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_MetaObject_Delete);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_MetaObject_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_MetaObject_Delete (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ��������� ������ �� �������� �������������.
//                                                                            []
void OBServer_MOD_UserProfile_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   DEBUG_STACK_NAME (OBServer_MOD_UserProfile_GetData);
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// ����������, ����������� ��� ������ ���������� �������:
   MOD_UserProfile_Args        OBServer_args;
   int                  OBServer_result;

// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (objID);

// ������� ���������� �������:
   OBServer_result = MOD_UserProfile_GetData (OBServer_args);

// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Log_ObjectClassIDs);
      PACK_ARG (Log_ObjectClassNames);
      PACK_ARG (Log_ObjectIDs);
      PACK_ARG (Log_ObjectNames);
      PACK_ARG (Log_ActionCodes);
      PACK_ARG (Log_ActionDescriptions);
      PACK_ARG (Log_Times);
      PACK_ARG (ExitCode);
      PACK_ARG (ExitCodeComment);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
