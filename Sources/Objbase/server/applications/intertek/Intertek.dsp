# Microsoft Developer Studio Project File - Name="Intertek" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Intertek - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Intertek.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Intertek.mak" CFG="Intertek - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Intertek - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Intertek - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Intertek", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Intertek - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./bin"
# PROP Intermediate_Dir "./tmp/r"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "APPLICATION_INTERTEK" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Intertek - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Intertek___Win32_Debug"
# PROP BASE Intermediate_Dir "Intertek___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./bin"
# PROP Intermediate_Dir "./tmp/d"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "APPLICATION_INTERTEK" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Intertek - Win32 Release"
# Name "Intertek - Win32 Debug"
# Begin Group "Server"

# PROP Default_Filter ""
# Begin Group "Intertek"

# PROP Default_Filter ""
# Begin Group "Lay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lay.h
# End Source File
# End Group
# Begin Group "Auto Generated"

# PROP Default_Filter ""
# Begin Group "- Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Interface_Auto.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface_Auto.h
# End Source File
# Begin Source File

SOURCE=.\Interface_Dispatch.cpp
# End Source File
# End Group
# Begin Group "- Object Layout"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lay_ObjController.cpp
# End Source File
# Begin Source File

SOURCE=.\Lay_ObjController.h
# End Source File
# Begin Source File

SOURCE=.\Lay_ObjData.cpp
# End Source File
# Begin Source File

SOURCE=.\Lay_ObjData.h
# End Source File
# Begin Source File

SOURCE=.\Lay_Stubs.cpp
# End Source File
# End Group
# End Group
# Begin Group "Ini"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\concepts.h
# End Source File
# Begin Source File

SOURCE=.\concepts.min.h
# End Source File
# Begin Source File

SOURCE=.\problem_ini.cpp
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# End Group
# Begin Group "Problem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include.h
# End Source File
# Begin Source File

SOURCE=.\problem_errors.h
# End Source File
# Begin Source File

SOURCE=.\problem_interface.h
# End Source File
# Begin Source File

SOURCE=.\problem_main.cpp
# End Source File
# Begin Source File

SOURCE=.\problem_SingleObject.cpp
# End Source File
# Begin Source File

SOURCE=.\problem_SingleObject.h
# End Source File
# Begin Source File

SOURCE=.\problem_test.cpp
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Kernel"

# PROP Default_Filter ""
# Begin Group "File System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\File.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\FileDriver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\FileDriver.h
# End Source File
# End Group
# Begin Group "AV-Tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\AVTree.h
# End Source File
# End Group
# Begin Group "Object System"

# PROP Default_Filter ""
# Begin Group "ObjCache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\ObjCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\ObjCache.h
# End Source File
# End Group
# Begin Group "key_arr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\key_arr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\key_arr.h
# End Source File
# End Group
# Begin Group "OBD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\OBD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\OBD.h
# End Source File
# End Group
# Begin Group "SmartField"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\SmartField.h
# End Source File
# End Group
# Begin Group "ObjDriver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\ObjDriver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\ObjDriver.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\ObjDriver_CASE.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\ObjDriver_inc.h
# End Source File
# End Group
# Begin Group "Object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\Object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\Object.h
# End Source File
# End Group
# End Group
# Begin Group "Server Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\ServerDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\ServerDebug.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Group "string"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\string.h
# End Source File
# End Group
# Begin Group "Memory Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\MemoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\MemoryManager.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\OB_System.h
# End Source File
# End Group
# Begin Group "URL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\URL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\URL.h
# End Source File
# End Group
# Begin Group "UserAgent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\UserAgent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\UserAgent.h
# End Source File
# End Group
# Begin Group "StopWatch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\stopwatch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\stopwatch.h
# End Source File
# End Group
# Begin Group "PicklockPassword"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\PicklockPassword.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\PicklockPassword.h
# End Source File
# End Group
# Begin Group "ArgResCache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\ArgResCache.h
# End Source File
# End Group
# Begin Group "CPtr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\Ptr.h
# End Source File
# End Group
# End Group
# Begin Group "Socket Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\OBServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\OBServer_Interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\OBServer_Interface.h
# End Source File
# End Group
# Begin Group "Problem.inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\problem_errors_1.inc
# End Source File
# Begin Source File

SOURCE=..\..\kernel\problem_errors_2.inc
# End Source File
# Begin Source File

SOURCE=..\..\kernel\problem_SingleObject_1.inc
# End Source File
# End Group
# Begin Group "EventMonitor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\EventMonitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\kernel\EventMonitor.h
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\config.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\main.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\kernel\main.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\problem_main_1.inc
# End Source File
# Begin Source File

SOURCE=..\..\kernel\problem_main_2.inc
# End Source File
# Begin Source File

SOURCE=..\..\kernel\STATIC_FILE_ID.h
# End Source File
# End Group
# End Group
# Begin Group "Modules"

# PROP Default_Filter ""
# Begin Group "{TMPLT}"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\modules\{TMPLT}\MOD_xxx.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\modules\{TMPLT}\MOD_xxx.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\modules\{TMPLT}\MOD_xxx.inc.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\modules\{TMPLT}\MOD_xxx.Interface.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\modules\{TMPLT}\MOD_xxx.pvt.cpp"
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Concept"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\Concept\MOD_Concept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\Concept\MOD_Concept.h
# End Source File
# End Group
# Begin Group "UserRights"

# PROP Default_Filter ""
# Begin Group "Feod"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_Feod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_Feod.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_Feod.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_Feod.pvt.cpp
# End Source File
# End Group
# Begin Group "User"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_User.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_User.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_User.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_User.pvt.cpp
# End Source File
# End Group
# Begin Group "UserGroup"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_UserGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_UserGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_UserGroup.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserRights\MOD_UserGroup.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "Publishing"

# PROP Default_Filter ""
# Begin Group "InfoDiv"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoDiv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoDiv.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoDiv.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoDiv.pvt.cpp
# End Source File
# End Group
# Begin Group "InfoObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoObject.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoObject.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoObject.pvt.cpp
# End Source File
# End Group
# Begin Group "InfoSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoSource.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoSource.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\Publishing\MOD_InfoSource.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "WebFileSystem"

# PROP Default_Filter ""
# Begin Group "WebFolder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFolder.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFolder.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFolder.pvt.cpp
# End Source File
# End Group
# Begin Group "WebFile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFile.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFile.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\WebFileSystem\MOD_WebFile.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "FullTextIndex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.ini.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.pvt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\FullTextIndex\MOD_FullTextIndex.test.cpp
# End Source File
# End Group
# Begin Group "SemanticNet"

# PROP Default_Filter ""
# Begin Group "Relation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Relation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Relation.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Relation.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Relation.ini.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Relation.pvt.cpp
# End Source File
# End Group
# Begin Group "Linkage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Linkage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Linkage.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Linkage.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Linkage.ini.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_Linkage.pvt.cpp
# End Source File
# End Group
# Begin Group "MetaObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_MetaObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_MetaObject.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_MetaObject.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_MetaObject.ini.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\SemanticNet\MOD_MetaObject.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "UserProfile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\UserProfile\MOD_UserProfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserProfile\MOD_UserProfile.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserProfile\MOD_UserProfile.inc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\UserProfile\MOD_UserProfile.pvt.cpp
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Client"

# PROP Default_Filter ""
# Begin Group "Common"

# PROP Default_Filter ""
# End Group
# Begin Group "Project"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Documents"

# PROP Default_Filter ""
# Begin Group "Status Report"

# PROP Default_Filter ""
# End Group
# Begin Group "Design Specs"

# PROP Default_Filter ""
# End Group
# Begin Group "Attention"

# PROP Default_Filter ""
# End Group
# End Group
# End Target
# End Project
