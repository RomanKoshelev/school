# Microsoft Developer Studio Project File - Name="OBT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=OBT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OBT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OBT.mak" CFG="OBT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OBT - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "OBT - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/obi/OBT", KBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OBT - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tmp\r"
# PROP Intermediate_Dir "tmp\r"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /G5 /Zp1 /W3 /WX /Gi /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /nologo
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /machine:I386 /out:".\bin\TEST.exe"

!ELSEIF  "$(CFG)" == "OBT - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tmp\d"
# PROP Intermediate_Dir "tmp\d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W4 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /WX /Fr
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:".\bin\TEST_d.exe" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "OBT - Win32 Release"
# Name "OBT - Win32 Debug"
# Begin Group "Kernel"

# PROP Default_Filter ""
# Begin Group "File System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\File.h
# End Source File
# Begin Source File

SOURCE=..\bcc\FileDriver.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\FileDriver.h
# End Source File
# End Group
# Begin Group "AV-Tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\AVTree.h
# End Source File
# End Group
# Begin Group "Object System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\key_arr.h
# End Source File
# Begin Source File

SOURCE=..\bcc\OBD.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\OBD.h
# End Source File
# Begin Source File

SOURCE=..\bcc\ObjDriver.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\ObjDriver.h
# End Source File
# Begin Source File

SOURCE=..\bcc\ObjDriver_CASE.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\ObjDriver_inc.h
# End Source File
# Begin Source File

SOURCE=..\bcc\Object.h
# End Source File
# Begin Source File

SOURCE=..\bcc\SmartField.h
# End Source File
# End Group
# Begin Group "Server Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\EventMonitor.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\EventMonitor.h
# End Source File
# Begin Source File

SOURCE=..\bcc\ServerDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\ServerDebug.h
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\main.h
# End Source File
# Begin Source File

SOURCE=..\bcc\OB_System.h
# End Source File
# Begin Source File

SOURCE=..\bcc\STATIC_FILE_ID.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\ArgResCache.h
# End Source File
# Begin Source File

SOURCE=..\bcc\MemoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\MemoryManager.h
# End Source File
# Begin Source File

SOURCE=..\bcc\Ptr.h
# End Source File
# Begin Source File

SOURCE=..\bcc\string.h
# End Source File
# Begin Source File

SOURCE=..\bcc\URL.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\URL.h
# End Source File
# Begin Source File

SOURCE=..\bcc\UserAgent.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\UserAgent.h
# End Source File
# End Group
# Begin Group "Server Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\OBServer.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\OBServer_Interface.cpp
# End Source File
# Begin Source File

SOURCE=..\bcc\OBServer_Interface.h
# End Source File
# End Group
# End Group
# Begin Group "Problem"

# PROP Default_Filter ""
# Begin Group "Lay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lay.h
# End Source File
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
# Begin Source File

SOURCE=.\Lay_Stubs.h
# End Source File
# End Group
# Begin Group "OBT_Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bcc\config.h
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\ob.h
# End Source File
# Begin Source File

SOURCE=.\OBT_Main.cpp
# End Source File
# End Group
# Begin Group "Tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MemoryManager_test.cpp
# End Source File
# Begin Source File

SOURCE=.\OBT_Test.cpp
# End Source File
# Begin Source File

SOURCE=.\OBT_Test_1_32.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OBT_Test_33_36.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OBT_Test_37.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OBT_Test_50.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OBT_Test_51.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TestArgCache.cpp
# End Source File
# End Group
# End Group
# End Target
# End Project
