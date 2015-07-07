# Microsoft Developer Studio Project File - Name="Modules" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Modules - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Modules.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Modules.mak" CFG="Modules - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Modules - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Modules - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Modules", YDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Modules - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./-"
# PROP Intermediate_Dir "./-"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Modules - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./-"
# PROP Intermediate_Dir "./-"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Modules - Win32 Release"
# Name "Modules - Win32 Debug"
# Begin Group "{TMPLT}"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\{TMPLT}\MOD_xxx.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=".\{TMPLT}\MOD_xxx.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=".\{TMPLT}\MOD_xxx.inc.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=".\{TMPLT}\MOD_xxx.Interface.h"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=".\{TMPLT}\MOD_xxx.pvt.cpp"
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Concept"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Concept\MOD_Concept.cpp
# End Source File
# Begin Source File

SOURCE=.\Concept\MOD_Concept.h
# End Source File
# End Group
# Begin Group "UserRights"

# PROP Default_Filter ""
# Begin Group "Feod"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserRights\MOD_Feod.cpp
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_Feod.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_Feod.inc.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_Feod.pvt.cpp
# End Source File
# End Group
# Begin Group "User"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserRights\MOD_User.cpp
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_User.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_User.inc.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_User.pvt.cpp
# End Source File
# End Group
# Begin Group "UserGroup"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserRights\MOD_UserGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_UserGroup.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_UserGroup.inc.h
# End Source File
# Begin Source File

SOURCE=.\UserRights\MOD_UserGroup.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "Publishing"

# PROP Default_Filter ""
# Begin Group "InfoDiv"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Publishing\MOD_InfoDiv.cpp
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoDiv.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoDiv.inc.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoDiv.pvt.cpp
# End Source File
# End Group
# Begin Group "InfoObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Publishing\MOD_InfoObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoObject.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoObject.inc.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoObject.pvt.cpp
# End Source File
# End Group
# Begin Group "InfoSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Publishing\MOD_InfoSource.cpp
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoSource.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoSource.inc.h
# End Source File
# Begin Source File

SOURCE=.\Publishing\MOD_InfoSource.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "WebFileSystem"

# PROP Default_Filter ""
# Begin Group "WebFolder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFolder.h
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFolder.inc.h
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFolder.pvt.cpp
# End Source File
# End Group
# Begin Group "WebFile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFile.cpp
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFile.h
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFile.inc.h
# End Source File
# Begin Source File

SOURCE=.\WebFileSystem\MOD_WebFile.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "FullTextIndex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.h
# End Source File
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.inc.h
# End Source File
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.ini.cpp
# End Source File
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.pvt.cpp
# End Source File
# Begin Source File

SOURCE=.\FullTextIndex\MOD_FullTextIndex.test.cpp
# End Source File
# End Group
# Begin Group "SemanticNet"

# PROP Default_Filter ""
# Begin Group "Relation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SemanticNet\MOD_Relation.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Relation.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Relation.inc.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Relation.ini.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Relation.pvt.cpp
# End Source File
# End Group
# Begin Group "Linkage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SemanticNet\MOD_Linkage.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Linkage.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Linkage.inc.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Linkage.ini.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_Linkage.pvt.cpp
# End Source File
# End Group
# Begin Group "MetaObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SemanticNet\MOD_MetaObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_MetaObject.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_MetaObject.inc.h
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_MetaObject.ini.cpp
# End Source File
# Begin Source File

SOURCE=.\SemanticNet\MOD_MetaObject.pvt.cpp
# End Source File
# End Group
# End Group
# Begin Group "UserProfile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserProfile\MOD_UserProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\UserProfile\MOD_UserProfile.h
# End Source File
# Begin Source File

SOURCE=.\UserProfile\MOD_UserProfile.inc.h
# End Source File
# Begin Source File

SOURCE=.\UserProfile\MOD_UserProfile.pvt.cpp
# End Source File
# End Group
# End Target
# End Project
