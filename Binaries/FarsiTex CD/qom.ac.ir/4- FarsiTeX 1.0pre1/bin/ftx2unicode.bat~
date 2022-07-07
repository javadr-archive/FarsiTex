@echo off
%3
cd %1
rem echo ######################################
rem echo FarsiTeX-To-Unicode Converter will be available in our next release.
rem echo ftx2uni.exe %2
rem echo ######################################
rem pause
echo ######################################
echo FarsiTeX-To-PdfLaTex is available
echo this replaced by S.M.J.R for directly converting ftex to pdf 
echo ######################################
ftx2tex %2.ftx
rem etex "&farsitex" %2.tex
pdfetex "&fapdftex" %2.tex
del %2.aux
del %2.tex
del %2.log
rem del *.bak
rem pause
rem next line written by me for my MS project
rem ftx2tex ftexthes.ftx
rem etex "&farsitex" ftexthes.tex
rem echo Farsi Make Index will now be executed.
rem dos2unix -c 7bit ftexthes.idx
rem fmakeidx.exe ftexthes.idx
rem yap -1 ftexthes.dvi

