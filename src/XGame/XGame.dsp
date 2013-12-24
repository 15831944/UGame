# Microsoft Developer Studio Project File - Name="XGame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XGame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XGame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XGame.mak" CFG="XGame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XGame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XGame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XGame - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "..\..\obj\Release\xgame"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp4 /MT /W3 /GX /O2 /I "./" /I "../" /I "../dialog" /I "../common" /I "../data" /I "../ulitity" /I "../impl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "USING_ECODE_ACCOUNT_FILE" /U "USING_SKINPLUSPLUS" /U "USE_FOR_NOT_INCREASE_RES_OFFLINE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib ..\..\obj\release\speedkernel\speedkernel.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin/UGame.exe" /libpath:"../lib"

!ELSEIF  "$(CFG)" == "XGame - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "..\..\obj\Debug\xgame"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp4 /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../" /I "../dialog" /I "../common" /I "../data" /I "../ulitity" /I "../impl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "USING_SKINPLUSPLUS" /D "_AFXDLL" /D "USING_ECODE_ACCOUNT_FILE" /U "USING_SKINPLUSPLUS" /U "NOT_ADJUST_OFFLINE_RESOURCE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib ..\..\obj\debug\speedkernel\speedkernel.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin/UGame_debug.exe" /pdbtype:sept /libpath:"../lib"

!ENDIF 

# Begin Target

# Name "XGame - Win32 Release"
# Name "XGame - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "app"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XGame.cpp
# End Source File
# Begin Source File

SOURCE=.\XGame.rc
# End Source File
# End Group
# Begin Group "windows"

# PROP Default_Filter ""
# Begin Group "pages"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\communication.cpp
# End Source File
# Begin Source File

SOURCE=..\dialog\ObserverBase.cpp
# End Source File
# Begin Source File

SOURCE=..\dialog\pageboatyard.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagebuildings.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagecommander.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagedefense.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagedocuments.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagegalaxy.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\ulitity\PageIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\dialog\pageinformation.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pagepersoninfo.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pageresource.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\pageresreachcenter.cpp
# ADD CPP /I "..\XGame"
# End Source File
# End Group
# Begin Source File

SOURCE=..\dialog\accountdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\findforgotpassdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\finishtipdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\logindlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\newaccountdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\supergatetransferdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\tradecenterdlg.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\dialog\XGameDlg.cpp
# End Source File
# End Group
# Begin Group "ulitity"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ulitity\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\DrawHTML.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\ulitity\ElapsedTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\GameLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\HighFrequencyElapsedTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\HTMLListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\ListBoxST.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\MFECToolTip.cpp
# End Source File
# Begin Source File

SOURCE=..\dialog\TipWarpper.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\UStar.cpp
# End Source File
# End Group
# Begin Group "buildings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\Boatyard.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\Building.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\BuildingsKeeper.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\CrystalFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\DiplogenFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\LabFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\MetalFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\NaniteFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\RobotFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\SunPowerFactory.cpp
# End Source File
# End Group
# Begin Group "data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\data\GameDataRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\data\GameFileReader.cpp
# End Source File
# End Group
# Begin Group "research"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\ResearchKeeper.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\ResearchTechnics.cpp
# End Source File
# End Group
# Begin Group "boats"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\BoatsKeeper.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\Spaceship.cpp
# End Source File
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ulitity\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\comboboxex.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\ulitity\ComboItem.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\EditItem.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\EditList.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\intedit.cpp
# ADD CPP /I "..\XGame"
# End Source File
# Begin Source File

SOURCE=..\ulitity\ReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\ToolTipListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\TreeItem.cpp
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\xgame_common.cpp
# End Source File
# End Group
# Begin Group "battle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\WarSimulator.cpp
# End Source File
# End Group
# Begin Group "defenses"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\Defense.cpp
# End Source File
# Begin Source File

SOURCE=..\impl\DefensesKeeper.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "app_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XGame.h
# End Source File
# End Group
# Begin Group "common_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\game_algo.hpp
# End Source File
# Begin Source File

SOURCE=..\common\xgame_common.hpp
# End Source File
# End Group
# Begin Group "windows_header"

# PROP Default_Filter ""
# Begin Group "pages_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\communication.h
# End Source File
# Begin Source File

SOURCE=..\dialog\ObserverBase.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pageboatyard.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagebuildings.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagecommander.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagedefense.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagedocuments.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagegalaxy.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\PageIcon.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pageinformation.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pagepersoninfo.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pageresource.h
# End Source File
# Begin Source File

SOURCE=..\dialog\pageresreachcenter.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\dialog\accountdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\findforgotpassdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\finishtipdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\logindlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\newaccountdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\supergatetransferdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\tradecenterdlg.h
# End Source File
# Begin Source File

SOURCE=..\dialog\XGameDlg.h
# End Source File
# End Group
# Begin Group "ulitity_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ulitity\BtnST.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\DrawHTML.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ecfile.hpp
# End Source File
# Begin Source File

SOURCE=..\ulitity\ElapsedTimer.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\GameLogger.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\HighFrequencyElapsedTimer.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\HTMLListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\IniFile.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ListBoxST.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\MemDC.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\MFECToolTip.h
# End Source File
# Begin Source File

SOURCE=..\dialog\TipWarpper.h
# End Source File
# Begin Source File

SOURCE=..\impl\UStar.h
# End Source File
# End Group
# Begin Group "buildings_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\Boatyard.h
# End Source File
# Begin Source File

SOURCE=..\impl\Building.h
# End Source File
# Begin Source File

SOURCE=..\impl\BuildingsKeeper.h
# End Source File
# Begin Source File

SOURCE=..\impl\CrystalFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\DiplogenFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\LabFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\MetalFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\NaniteFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\RobotFactory.h
# End Source File
# Begin Source File

SOURCE=..\impl\SunPowerFactory.h
# End Source File
# End Group
# Begin Group "data_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\data\GameDataRecorder.h
# End Source File
# Begin Source File

SOURCE=..\data\GameFileReader.h
# End Source File
# End Group
# Begin Group "research_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\ResearchKeeper.h
# End Source File
# Begin Source File

SOURCE=..\impl\ResearchTechnics.h
# End Source File
# End Group
# Begin Group "boats_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\BoatsKeeper.h
# End Source File
# Begin Source File

SOURCE=..\impl\Spaceship.h
# End Source File
# End Group
# Begin Group "gui_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ulitity\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\comboboxex.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ComboItem.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\EditItem.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\EditList.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\intedit.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ReportCtrl.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\ToolTipListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\ulitity\TreeItem.h
# End Source File
# End Group
# Begin Group "battle_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\WarSimulator.h
# End Source File
# End Group
# Begin Group "defenses_header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\impl\Defense.h
# End Source File
# Begin Source File

SOURCE=..\impl\DefensesKeeper.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\clock\0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\account.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\account.ico
# End Source File
# Begin Source File

SOURCE=.\res\resource\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clock\black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\buildings\boatyard.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\boatyard.ICO
# End Source File
# Begin Source File

SOURCE=.\res\boats\bomber.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\commander.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\computer.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\conoly.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\cruisor.ico
# End Source File
# Begin Source File

SOURCE=.\res\resource\crycal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\buildings\crycalFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\defense.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\defense.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\denglizi.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\destroyer.ico
# End Source File
# Begin Source File

SOURCE=.\res\buildings\dipoFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\dockattack.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\docs.ICO
# End Source File
# Begin Source File

SOURCE=.\res\resource\dpo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\boats\ds.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gui\FACTORY.ICO
# End Source File
# Begin Source File

SOURCE=.\res\research\fire.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\galaxy.ICO
# End Source File
# Begin Source File

SOURCE=.\res\defenses\gauss.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\gravition.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\heavybattleplan.ico
# End Source File
# Begin Source File

SOURCE=.\res\defenses\hlaser.ico
# End Source File
# Begin Source File

SOURCE=.\res\defenses\icon.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\info_center.ICO
# End Source File
# Begin Source File

SOURCE=.\res\buildings\LabFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\largescutter.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\lightbattleplan.ico
# End Source File
# Begin Source File

SOURCE=.\res\log.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gui\main.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource\minal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource\minal.ico
# End Source File
# Begin Source File

SOURCE=.\res\buildings\minalFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\minalFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\defenses\miss.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\mouse.CUR
# End Source File
# Begin Source File

SOURCE=.\res\buildings\natitefactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\optionmarks.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gui\password.ico
# End Source File
# Begin Source File

SOURCE=.\res\password.ico
# End Source File
# Begin Source File

SOURCE=.\res\defenses\pc.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\person.ico
# End Source File
# Begin Source File

SOURCE=.\res\clock\point.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource\power.bmp
# End Source File
# Begin Source File

SOURCE=.\res\research\power.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\pulse.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\radio.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\recycle.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\research.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\resource.ICO
# End Source File
# Begin Source File

SOURCE=.\res\buildings\RobertFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\sheiled.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\ships.ICO
# End Source File
# Begin Source File

SOURCE=.\res\defenses\slaser.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\smallsuttle.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\spy.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\spyplanet.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star1.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star10.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star2.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star3.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star4.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star5.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star6.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star7.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star8.ico
# End Source File
# Begin Source File

SOURCE=.\res\stars\star9.ico
# End Source File
# Begin Source File

SOURCE=.\res\buildings\sunPowerFactory.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\sunpowerplanet.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\superspace.ico
# End Source File
# Begin Source File

SOURCE=.\res\research\superstech.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui\Sword.ico
# End Source File
# Begin Source File

SOURCE=.\res\boats\warship.ico
# End Source File
# Begin Source File

SOURCE=.\res\XGame.ico
# End Source File
# Begin Source File

SOURCE=.\res\XGame.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\XPStyle.manifest
# End Source File
# End Target
# End Project
