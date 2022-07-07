@echo off
%3
cd %1
echo ######################################
echo FarsiTeX-To-Unicode Converter will be available in our next release.
echo ftx2uni.exe %2
echo ######################################
rem pause
echo ######################################
echo FarsiTeX-To-PdfLaTex is available
echo this replaced by S.M.J.Razavian for directly converting ftex to pdf 
echo ######################################
ftx2tex %2.ftx
pdfetex "&fapdftex" %2.tex

