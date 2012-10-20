# Microsoft Developer Studio Project File - Name="bj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bj - Win32 DebugPro
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bj.mak" CFG="bj - Win32 DebugPro"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bj - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "bj - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "bj - Win32 DebugPro" (based on "Win32 (x86) Application")
!MESSAGE "bj - Win32 ReleasePro" (based on "Win32 (x86) Application")
!MESSAGE "bj - Win32 Release Trial" (based on "Win32 (x86) Application")
!MESSAGE "bj - Win32 Release Pro Trial" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bj - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bj.exe"

!ELSEIF  "$(CFG)" == "bj - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "bj - Win32 DebugPro"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "bj___Win32_DebugPro"
# PROP BASE Intermediate_Dir "bj___Win32_DebugPro"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bj___Win32_DebugPro"
# PROP Intermediate_Dir "bj___Win32_DebugPro"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "PRO_VERSION" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 \Output\CardLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /debug /machine:I386 /out:"bj___Win32_DebugPro/bjpro.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "bj - Win32 ReleasePro"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bj___Win32_ReleasePro"
# PROP BASE Intermediate_Dir "bj___Win32_ReleasePro"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bj___Win32_ReleasePro"
# PROP Intermediate_Dir "bj___Win32_ReleasePro"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "PRO_VERSION" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bj.exe"
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bjpro.exe"

!ELSEIF  "$(CFG)" == "bj - Win32 Release Trial"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bj___Win32_Release_Trial"
# PROP BASE Intermediate_Dir "bj___Win32_Release_Trial"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bj___Win32_Release_Trial"
# PROP Intermediate_Dir "bj___Win32_Release_Trial"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TRAIN" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bj.exe"
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bjtrial.exe"

!ELSEIF  "$(CFG)" == "bj - Win32 Release Pro Trial"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bj___Win32_Release_Pro_Trial"
# PROP BASE Intermediate_Dir "bj___Win32_Release_Pro_Trial"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bj___Win32_Release_Pro_Trial"
# PROP Intermediate_Dir "bj___Win32_Release_Pro_Trial"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TRAIN" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TRAIN" /D "PRO_VERSION" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bjtrial.exe"
# ADD LINK32 \Release\CardLib.lib /nologo /subsystem:windows /machine:I386 /out:"\Release/bjtrialpro.exe"

!ENDIF 

# Begin Target

# Name "bj - Win32 Release"
# Name "bj - Win32 Debug"
# Name "bj - Win32 DebugPro"
# Name "bj - Win32 ReleasePro"
# Name "bj - Win32 Release Trial"
# Name "bj - Win32 Release Pro Trial"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BetMissThread.cpp
# End Source File
# Begin Source File

SOURCE=.\bj.cpp
# End Source File
# Begin Source File

SOURCE=.\bj.rc
# End Source File
# Begin Source File

SOURCE=.\bjDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BJHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\CountDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Deck.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMistakes.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPractice.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PropBid.cpp
# End Source File
# Begin Source File

SOURCE=.\PropCasino.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\PropStrategy.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BetMissThread.h
# End Source File
# Begin Source File

SOURCE=.\bj.h
# End Source File
# Begin Source File

SOURCE=.\bjDlg.h
# End Source File
# Begin Source File

SOURCE=.\BJHistory.h
# End Source File
# Begin Source File

SOURCE=.\CountDlg.h
# End Source File
# Begin Source File

SOURCE=.\Deck.h
# End Source File
# Begin Source File

SOURCE=.\DialogMistakes.h
# End Source File
# Begin Source File

SOURCE=.\DlgPractice.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\PropBid.h
# End Source File
# Begin Source File

SOURCE=.\PropCasino.h
# End Source File
# Begin Source File

SOURCE=.\PropPlay.h
# End Source File
# Begin Source File

SOURCE=.\PropStrategy.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Background02.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bj.ico
# End Source File
# Begin Source File

SOURCE=.\res\bj.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\History.dat
# End Source File
# Begin Source File

SOURCE=.\notes.txt
# End Source File
# Begin Source File

SOURCE=.\notes2.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
