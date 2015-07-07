/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Auto.h                                          []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Прототипы интерфейсных функций для работы с базой данных. []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________[]
*/
#ifndef Interface_Auto_H
#define Interface_Auto_H




   void OBServer_MOD_User_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_Authorize (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_GetRights (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_PutRights (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_CheckOwnRights (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_User_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserGroup_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserGroup_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserGroup_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserGroup_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserGroup_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Feod_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Feod_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Feod_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoDiv_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoDiv_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoDiv_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoObject_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoObject_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoObject_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoObject_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoSource_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoSource_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoSource_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoSource_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_InfoSource_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFolder_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFolder_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFolder_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFolder_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFolder_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFile_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFile_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFile_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_WebFile_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_FullTextIndex_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_ChangeField (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Relation_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_GetRealObjectByProxyID (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_Linkage_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_MetaObject_New (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_MetaObject_Enumerate (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_MetaObject_GetData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_MetaObject_PutData (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_MetaObject_Delete (const char * inStr, const char * outStr, void ** ppData);
   void OBServer_MOD_UserProfile_GetData (const char * inStr, const char * outStr, void ** ppData);



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
