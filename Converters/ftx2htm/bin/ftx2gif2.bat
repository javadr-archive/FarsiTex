@echo off
call ftx2bmp2.bat %1 %2
bmp2gif.exe -tw %2\%1.bmp %2\%1.gif
del %2\%1.bmp
del %2\%1.ftx