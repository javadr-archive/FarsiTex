@echo off
rem ftx2bmp with ps convertor
ftx2tex %1
ftxfonts
etex &farsitex %1
del %1.aux
del %1.tex
del %1.log

rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rem we must convert %1.dvi to %1.ps
rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
call dvips %1
del %1.dvi

rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rem at now we have a ps file that is created
rem by executing above commands. we convert
rem this ps file to a 256 color bitmap file.
rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gs386.exe -q -r100 -sDEVICE=bmp256 -sOutputFile=%1.bmp -dNOPAUSE %1.ps quit.ps
del %1.ps