# Microsoft Developer Studio Project File - Name="mod_counter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=mod_counter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mod_counter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mod_counter.mak" CFG="mod_counter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mod_counter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mod_counter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/mod_counter", KKAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mod_counter - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "mod_counter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
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

# Name "mod_counter - Win32 Release"
# Name "mod_counter - Win32 Debug"
# Begin Group "cntd.inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\alloc.h
# End Source File
# Begin Source File

SOURCE=.\include\ap.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_compat.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_config.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_config_auto.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_ctype.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_md5.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_mmn.h
# End Source File
# Begin Source File

SOURCE=.\include\ap_sha1.h
# End Source File
# Begin Source File

SOURCE=.\include\buff.h
# End Source File
# Begin Source File

SOURCE=.\include\compat.h
# End Source File
# Begin Source File

SOURCE=.\include\conf.h
# End Source File
# Begin Source File

SOURCE=.\include\explain.h
# End Source File
# Begin Source File

SOURCE=.\include\fnmatch.h
# End Source File
# Begin Source File

SOURCE=.\include\hsregex.h
# End Source File
# Begin Source File

SOURCE=.\include\http_conf_globals.h
# End Source File
# Begin Source File

SOURCE=.\include\http_config.h
# End Source File
# Begin Source File

SOURCE=.\include\http_core.h
# End Source File
# Begin Source File

SOURCE=.\include\http_log.h
# End Source File
# Begin Source File

SOURCE=.\include\http_main.h
# End Source File
# Begin Source File

SOURCE=.\include\http_protocol.h
# End Source File
# Begin Source File

SOURCE=.\include\http_request.h
# End Source File
# Begin Source File

SOURCE=.\include\http_vhost.h
# End Source File
# Begin Source File

SOURCE=.\include\httpd.h
# End Source File
# Begin Source File

SOURCE=.\include\multithread.h
# End Source File
# Begin Source File

SOURCE=.\include\rfc1413.h
# End Source File
# Begin Source File

SOURCE=.\include\scoreboard.h
# End Source File
# Begin Source File

SOURCE=.\include\util_date.h
# End Source File
# Begin Source File

SOURCE=.\include\util_md5.h
# End Source File
# Begin Source File

SOURCE=.\include\util_script.h
# End Source File
# Begin Source File

SOURCE=.\include\util_uri.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\mod_counter.c
# End Source File
# Begin Source File

SOURCE=.\mod_counter_call.c
# End Source File
# Begin Source File

SOURCE=.\mod_counter_dp_img.h
# End Source File
# Begin Source File

SOURCE=.\mod_counter_img_set.c
# End Source File
# Begin Source File

SOURCE=.\mod_counter_img_set.h
# End Source File
# End Target
# End Project
