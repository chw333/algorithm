@echo off
if exist p2.in del p2.in
if exist p2.out del p2.out
if exist p2opt.dat del p2opt.dat

if '%1' == '' goto comerr
if not exist p2.exe goto exeerr

if '%1' == '1' goto continue
if '%1' == '2' goto continue
if '%1' == '3' goto continue
if '%1' == '4' goto continue
if '%1' == '5' goto continue
if '%1' == '6' goto continue
if '%1' == '7' goto continue
if '%1' == '8' goto continue
if '%1' == '9' goto continue
if '%1' == '10' goto continue

goto comerr2

:continue
copy p2-%1.in p2.in > nul
copy p2opt-%1.dat p2opt.dat > nul
echo --------------------------- data No. %1
timer1
p2
timer2
if not exist p2.out goto outerr
p2score
goto end

:comerr
echo usage - check (data number)
echo ex) check 3
goto end

:comerr2
echo wrong data number!
goto end
      
:exeerr
echo p2.exe not found!
goto end

:outerr
echo p2.out not found!
goto end

:end
