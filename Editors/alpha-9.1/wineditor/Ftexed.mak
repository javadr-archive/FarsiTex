# Microsoft Developer Studio Generated NMAKE File, Based on Ftexed.dsp
!IF "$(CFG)" == ""
CFG=Ftexed - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Ftexed - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ftexed - Win32 Release" && "$(CFG)" != "Ftexed - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ftexed.mak" CFG="Ftexed - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ftexed - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ftexed - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Ftexed - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Ftexed.exe" "$(OUTDIR)\Ftexed.bsc" ".\Release\ftexkeyb.dat"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\FarsiRichEdit.obj"
	-@erase "$(INTDIR)\FarsiRichEdit.sbr"
	-@erase "$(INTDIR)\Ftexed.obj"
	-@erase "$(INTDIR)\Ftexed.pch"
	-@erase "$(INTDIR)\Ftexed.res"
	-@erase "$(INTDIR)\Ftexed.sbr"
	-@erase "$(INTDIR)\FtexedDoc.obj"
	-@erase "$(INTDIR)\FtexedDoc.sbr"
	-@erase "$(INTDIR)\FtexedView.obj"
	-@erase "$(INTDIR)\FtexedView.sbr"
	-@erase "$(INTDIR)\GotoDlg.obj"
	-@erase "$(INTDIR)\GotoDlg.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\PrintDLG.obj"
	-@erase "$(INTDIR)\PrintDLG.sbr"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\Search.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Ftexed.bsc"
	-@erase "$(OUTDIR)\Ftexed.exe"
	-@erase "Release\ftexkeyb.dat"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ftexed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ftexed.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ftexed.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\FarsiRichEdit.sbr" \
	"$(INTDIR)\Ftexed.sbr" \
	"$(INTDIR)\FtexedDoc.sbr" \
	"$(INTDIR)\FtexedView.sbr" \
	"$(INTDIR)\GotoDlg.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PrintDLG.sbr" \
	"$(INTDIR)\Search.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ftexed.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Ftexed.pdb" /machine:I386 /out:"$(OUTDIR)\Ftexed.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\FarsiRichEdit.obj" \
	"$(INTDIR)\Ftexed.obj" \
	"$(INTDIR)\FtexedDoc.obj" \
	"$(INTDIR)\FtexedView.obj" \
	"$(INTDIR)\GotoDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PrintDLG.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ftexed.res"

"$(OUTDIR)\Ftexed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

InputPath=.\Release\Ftexed.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\ftexkeyb.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy .\other\ftexkeyb.dat .\Release
<< 
	

!ELSEIF  "$(CFG)" == "Ftexed - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Ftexed.exe" "$(OUTDIR)\Ftexed.bsc" ".\Debug\ftexkeyb.dat"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\FarsiRichEdit.obj"
	-@erase "$(INTDIR)\FarsiRichEdit.sbr"
	-@erase "$(INTDIR)\Ftexed.obj"
	-@erase "$(INTDIR)\Ftexed.pch"
	-@erase "$(INTDIR)\Ftexed.res"
	-@erase "$(INTDIR)\Ftexed.sbr"
	-@erase "$(INTDIR)\FtexedDoc.obj"
	-@erase "$(INTDIR)\FtexedDoc.sbr"
	-@erase "$(INTDIR)\FtexedView.obj"
	-@erase "$(INTDIR)\FtexedView.sbr"
	-@erase "$(INTDIR)\GotoDlg.obj"
	-@erase "$(INTDIR)\GotoDlg.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\PrintDLG.obj"
	-@erase "$(INTDIR)\PrintDLG.sbr"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\Search.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Ftexed.bsc"
	-@erase "$(OUTDIR)\Ftexed.exe"
	-@erase "$(OUTDIR)\Ftexed.ilk"
	-@erase "$(OUTDIR)\Ftexed.pdb"
	-@erase ".\Debug\ftexkeyb.dat"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ftexed.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ftexed.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ftexed.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\FarsiRichEdit.sbr" \
	"$(INTDIR)\Ftexed.sbr" \
	"$(INTDIR)\FtexedDoc.sbr" \
	"$(INTDIR)\FtexedView.sbr" \
	"$(INTDIR)\GotoDlg.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PrintDLG.sbr" \
	"$(INTDIR)\Search.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ftexed.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Ftexed.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Ftexed.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\FarsiRichEdit.obj" \
	"$(INTDIR)\Ftexed.obj" \
	"$(INTDIR)\FtexedDoc.obj" \
	"$(INTDIR)\FtexedView.obj" \
	"$(INTDIR)\GotoDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PrintDLG.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ftexed.res"

"$(OUTDIR)\Ftexed.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

InputPath=.\Debug\Ftexed.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\ftexkeyb.dat" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy .\other\ftexkeyb.dat .\Debug
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Ftexed.dep")
!INCLUDE "Ftexed.dep"
!ELSE 
!MESSAGE Warning: cannot find "Ftexed.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Ftexed - Win32 Release" || "$(CFG)" == "Ftexed - Win32 Debug"
SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\FarsiRichEdit.cpp

"$(INTDIR)\FarsiRichEdit.obj"	"$(INTDIR)\FarsiRichEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\Ftexed.cpp

"$(INTDIR)\Ftexed.obj"	"$(INTDIR)\Ftexed.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\Ftexed.rc

"$(INTDIR)\Ftexed.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FtexedDoc.cpp

"$(INTDIR)\FtexedDoc.obj"	"$(INTDIR)\FtexedDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\FtexedView.cpp

"$(INTDIR)\FtexedView.obj"	"$(INTDIR)\FtexedView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\GotoDlg.cpp

"$(INTDIR)\GotoDlg.obj"	"$(INTDIR)\GotoDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\PrintDLG.cpp

"$(INTDIR)\PrintDLG.obj"	"$(INTDIR)\PrintDLG.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\Search.cpp

"$(INTDIR)\Search.obj"	"$(INTDIR)\Search.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ftexed.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Ftexed - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ftexed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ftexed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ftexed - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ftexed.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ftexed.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

