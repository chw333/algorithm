@echo off
if "%1" == "" goto info
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
if exist match.in del match.in
if exist match.out del match.out
copy bask%2.in match.in > nul
echo. | time
echo. | time >> %1.log
%1.exe
echo. | time >> %1.log
echo. | time
fc match.out bask%2.out
fc match.out bask%2.out >> %1.log
pause
if exist match.in del match.in
if exist match.out del match.out
goto lopp
	:koik
for %%i in (1 2 3 4 5) do call %0 %1 %%i
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
