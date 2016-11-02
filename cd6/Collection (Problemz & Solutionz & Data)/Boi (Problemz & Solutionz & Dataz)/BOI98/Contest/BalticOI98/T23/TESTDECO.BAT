@echo off
if "%1" == "" goto info
rem if not exist %1.exe if exist %1.pas tpc %1
rem if not exist %1.exe if exist %1.c gcc %1
rem if not exist %1.exe if exist %1.cpp gpp %1
if not exist %1.exe echo Where is the program to test?
if not exist %1.exe goto lopp
if "%2" == "" goto koik
	:test
cls
echo ------
echo Test %2
echo ------
echo ------ >> %1.log
echo Test %2 >> %1.log
echo ------ >> %1.log
if exist balt.io del balt.io
if exist balt.out del balt.out
if exist balt.io%2 goto testdo
echo no BALT.IO / incorrect  BALT.IO
echo Nothing to test!
echo no BALT.IO / incorrect BALT.IO >> %1.log
echo Nothing to test! >> %1.log
goto overtest
	:testdo
copy balt.io%2 balt.io > nul
echo. | time
echo. | time >> %1.log
rem running decode.exe
%1.exe
echo. | time >> %1.log
echo. | time
if exist balt.out copy balt.out balt.o%2 > nul
if exist balt.out del balt.out > nul
goto	overtest
	:overtest
pause
goto lopp
	:koik
for %%i in (1 2 3 4 5 6 7 8) do call %0 %1 %%i
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
