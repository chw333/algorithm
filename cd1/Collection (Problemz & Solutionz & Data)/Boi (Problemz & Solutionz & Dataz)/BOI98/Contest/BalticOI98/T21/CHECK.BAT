@echo off
if "%1" == "" goto info
if "%2" == "" goto koik
	:test
cls
echo ------
echo Test %2
echo ------
echo ------ >> %1.log
echo Test %2 >> %1.log
echo ------ >> %1.log
copy floor.o%2 floor.out
copy floor%2.in floor.in
tester  
tester >> %1.log
pause
goto lopp
	:koik
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %1 %%i 
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
