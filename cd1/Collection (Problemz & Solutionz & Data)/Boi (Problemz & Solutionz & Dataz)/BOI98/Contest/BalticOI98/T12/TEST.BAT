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
if exist start.in del start.in
if exist finish.in del finish.in
if exist relay2.out del relay2.out
if exist relay2.o%2 del relay2.o%2
copy start.%2 start.in > nul
copy finish.%2 finish.in > nul
echo. | time
echo. | time >> %1.log
%1.exe
echo. | time >> %1.log
echo. | time
if exist relay2.out ren relay2.out relay2.o%2
pause
goto lopp
	:koik
for %%i in (a b c d e f g h i j k m) do call %0 %1 %%i
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
