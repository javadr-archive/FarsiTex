@echo off
ftx2tex %1
ftxfonts
etex &farsitex %1
del %1.aux
del %1.tex
del %1.log

rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rem we convert dvi file(%1.dvi) to a
rem windows bitmap file(%1.bmp).
rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if exist %1.dvi dvidrv dvidot bmpwin @lj /fl=-1 /fa- /om+ /v0 /r150 /fs2 %1.dvi %1.bmp
del dvidot.dlg
del %1.dvi