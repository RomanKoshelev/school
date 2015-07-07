# Microsoft Developer Studio Project File - Name="Kernel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Kernel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kernel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kernel.mak" CFG="Kernel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kernel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Kernel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Kernel", XBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kernel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"tmp/r/Kernel.pch" /YX /Fo"tmp/r/" /Fd"tmp/r/" /FD /c
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

!ELSEIF  "$(CFG)" == "Kernel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "./tmp/d"
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

# Name "Kernel - Win32 Release"
# Name "Kernel - Win32 Debug"
# Begin Group "File System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\File.h
# End Source File
# Begin Source File

SOURCE=.\FileDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDriver.h
# End Source File
# End Group
# Begin Group "AV-Tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AVTree.h
# End Source File
# End Group
# Begin Group "Object System"

# PROP Default_Filter ""
# Begin Group "ObjCache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjCache.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjCache.h
# End Source File
# End Group
# Begin Group "key_arr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\key_arr.cpp
# End Source File
# Begin Source File

SOURCE=.\key_arr.h
# End Source File
# End Group
# Begin Group "OBD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OBD.cpp
# End Source File
# Begin Source File

SOURCE=.\OBD.h
# End Source File
# End Group
# Begin Group "SmartField"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SmartField.h
# End Source File
# End Group
# Begin Group "ObjDriver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjDriver.h
# End Source File
# Begin Source File

SOURCE=.\ObjDriver_CASE.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjDriver_inc.h
# End Source File
# End Group
# Begin Group "Object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\Object.h
# End Source File
# End Group
# End Group
# Begin Group "Server Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ServerDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDebug.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Group "string"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\string.cpp
# End Source File
# Begin Source File

SOURCE=.\string.h
# End Source File
# End Group
# Begin Group "Memory Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MemoryManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryManager.h
# End Source File
# Begin Source File

SOURCE=.\OB_System.h
# End Source File
# End Group
# Begin Group "URL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\URL.cpp
# End Source File
# Begin Source File

SOURCE=.\URL.h
# End Source File
# End Group
# Begin Group "UserAgent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UserAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAgent.h
# End Source File
# End Group
# Begin Group "StopWatch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stopwatch.cpp
# End Source File
# Begin Source File

SOURCE=.\stopwatch.h
# End Source File
# End Group
# Begin Group "PicklockPassword"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PicklockPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\PicklockPassword.h
# End Source File
# End Group
# Begin Group "ArgResCache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArgResCache.h
# End Source File
# End Group
# Begin Group "CPtr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ptr.h
# End Source File
# End Group
# End Group
# Begin Group "Server Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OBServer.cpp
# End Source File
# Begin Source File

SOURCE=.\OBServer_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\OBServer_Interface.h
# End Source File
# End Group
# Begin Group "Problem.inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\problem_errors_1.inc
# End Source File
# Begin Source File

SOURCE=.\problem_errors_2.inc
# End Source File
# Begin Source File

SOURCE=.\problem_SingleObject_1.inc
# End Source File
# End Group
# Begin Group "EventMonitor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EventMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\EventMonitor.h
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\problem_main_1.inc
# End Source File
# Begin Source File

SOURCE=.\problem_main_2.inc
# End Source File
# Begin Source File

SOURCE=.\STATIC_FILE_ID.h
# End Source File
# End Group
# End Target
# End Project
