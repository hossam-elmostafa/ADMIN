# Microsoft Developer Studio Project File - Name="ADMN" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ADMN - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ADMN.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ADMN.mak" CFG="ADMN - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ADMN - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADMN - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/VC/ADMNPROJECT/ADMN.DLL", NPBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ADMN - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0xc01 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc01 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"D:\Legacy\Runtime_D\ADMN.DLL" /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=\Legacy\Runtime_D\ADMN.DLL
InputPath=\Legacy\Runtime_D\ADMN.DLL
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ADMN - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0xc01 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc01 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"D:\Legacy\Common\ADMN.DLL"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=\Legacy\Common\ADMN.DLL
InputPath=\Legacy\Common\ADMN.DLL
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ADMN - Win32 Debug"
# Name "ADMN - Win32 Release MinDependency"
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ADMNapp.h
# End Source File
# Begin Source File

SOURCE=.\ADMNObj.h
# End Source File
# Begin Source File

SOURCE=.\Category.h
# End Source File
# Begin Source File

SOURCE=.\CMNObjBase.h
# End Source File
# Begin Source File

SOURCE=.\CommonCategory.h
# End Source File
# Begin Source File

SOURCE=.\Connection.h
# End Source File
# Begin Source File

SOURCE=.\DocLib.h
# End Source File
# Begin Source File

SOURCE=.\eventimp.h
# End Source File
# Begin Source File

SOURCE=.\FirstDatabasePrivilegeTool.h
# End Source File
# Begin Source File

SOURCE=.\HandOver.h
# End Source File
# Begin Source File

SOURCE=.\polydb.h
# End Source File
# Begin Source File

SOURCE=.\polytools.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TOOLSCATEGORY.H
# End Source File
# Begin Source File

SOURCE=.\ToolsListener.h
# End Source File
# Begin Source File

SOURCE=.\WaitWnd.h
# End Source File
# End Group
# Begin Group "CPP Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ADMN.cpp
# End Source File
# Begin Source File

SOURCE=.\ADMN.def
# End Source File
# Begin Source File

SOURCE=.\ADMN.idl

!IF  "$(CFG)" == "ADMN - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ADMN.idl

BuildCmds= \
	midl /Oicf /h "ADMN.h" /iid "ADMN_i.c" "ADMN.idl"

".\ADMN.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ADMN.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ADMN_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ADMN - Win32 Release MinDependency"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ADMN.idl

BuildCmds= \
	midl /Oicf /h "ADMN.h" /iid "ADMN_i.c" "ADMN.idl"

".\ADMN.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ADMN.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ADMN_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ADMN.rc
# End Source File
# Begin Source File

SOURCE=.\ADMNObj.cpp
# End Source File
# Begin Source File

SOURCE=.\Category.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonCategory.cpp
# End Source File
# Begin Source File

SOURCE=.\Connection.cpp
# End Source File
# Begin Source File

SOURCE=.\DocLib.cpp
# End Source File
# Begin Source File

SOURCE=.\FirstDatabasePrivilegeTool.cpp
# End Source File
# Begin Source File

SOURCE=.\HandOver.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyDB.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyTools.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolsListener.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ADMNObj.rgs
# End Source File
# End Target
# End Project
# Section ADMN : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section ADMN : {B0F95362-125E-11D0-B7EF-0080C77AF882}
# 	2:5:Class:CHijriCalender
# 	2:10:HeaderFile:hijricalender.h
# 	2:8:ImplFile:hijricalender.cpp
# End Section
# Section ADMN : {B0F95364-125E-11D0-B7EF-0080C77AF882}
# 	2:21:DefaultSinkHeaderFile:hijricalender.h
# 	2:16:DefaultSinkClass:CHijriCalender
# End Section
