@echo off
if "%1"=="" goto usage
if "%1"=="-h" goto usage
if "%1"=="-?" goto usage
if "%1"=="/h" goto usage
if "%1"=="/?" goto usage
goto exec

:usage
echo "Usage: ftx2htm <inputfile> [<outputfile>]"
echo Example: ftx2htm fsample.ftx
echo          ftx2htm fsample.ftx fsample.htm
goto end

:exec
ftx2htmC.exe %1 %2 %3 %4 %5 %6 %7 %8 %9

rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rem ftx2gif.bat is ouput of ftex2htmC.exe
rem if its need to convert math formula
rem or other unsupported commands to gif
rem picture and add it in html file.
rem %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if exist ftx2gif.bat call ftx2gif.bat
del ftx2gif.bat

echo ......................................................
echo ... ftx2htm was written by Mohammad Bakuii Katrimi ...
echo ...... under supervision of Dr. Mohammad Ghodsi ......
echo ......................................................

:end