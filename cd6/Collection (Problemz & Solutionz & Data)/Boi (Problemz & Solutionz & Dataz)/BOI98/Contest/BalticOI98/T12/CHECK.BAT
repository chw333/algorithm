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
set xxx=
if "%2" == "a" set xxx=pos
if "%2" == "b" set xxx=pos
if "%2" == "c" set xxx=pos
if "%2" == "d" set xxx=pos
if "%2" == "e" set xxx=pos
if "%2" == "f" set xxx=pos
if "%2" == "g" set xxx=pos
if "%2" == "h" set xxx=neg
if "%2" == "i" set xxx=neg
if "%2" == "j" set xxx=neg
if "%2" == "k" set xxx=neg
if "%2" == "m" set xxx=chk
if "%xxx%" == "" echo Unknown test %2
if "%xxx%" == "" echo Unknown test %2 >> %1.log
if "%xxx%" == "" echo goto lopp
if "%xxx%" == "pos" checkpos relay2.o%2 relay2.%2
if "%xxx%" == "pos" checkpos relay2.o%2 relay2.%2 >> %1.log
if "%xxx%" == "neg" checkneg relay2.o%2 relay2.%2 correct.%2
if "%xxx%" == "neg" checkneg relay2.o%2 relay2.%2 correct.%2 >> %1.log
pause
goto lopp
	:koik
for %%i in (a b c d e f g h i j k) do call %0 %1 %%i pos
goto lopp
	:info
echo Syntax is: %0 program [test]
echo            default is all tests
goto lopp
	:lopp
