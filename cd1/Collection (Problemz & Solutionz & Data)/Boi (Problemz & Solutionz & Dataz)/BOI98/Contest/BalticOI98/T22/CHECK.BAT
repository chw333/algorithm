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
startest star.T%2 star.o%2 
startest star.T%2 star.o%2 >> %1.log
pause
goto lopp
	:koik
for %%i in (01 02 03 04 05 06 07 08 09 10) do call %0 %1 %%i 
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
