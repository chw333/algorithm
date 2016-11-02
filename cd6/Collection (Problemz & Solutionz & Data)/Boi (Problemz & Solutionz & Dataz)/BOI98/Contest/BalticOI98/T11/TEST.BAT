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
if exist fruits.in del fruits.in
if exist fruits.out del fruits.out
copy input.%2 fruits.in > nul
echo. | time
echo. | time >> %1.log
%1.exe
echo. | time >> %1.log
echo. | time
check input.%2 fruits.out
check input.%2 fruits.out >> %1.log
pause
if exist fruits.in del fruits.in
if exist fruits.out del fruits.out
goto lopp
	:koik
for %%i in (a b c d e f g h i j) do call %0 %1 %%i
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
