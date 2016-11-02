@echo off
if exist p1.in del p1.in
if exist p1.out del p1.out

if '%1' == '' goto comerr
if not exist p1.exe goto exeerr

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
copy p1-%1.in p1.in > nul
echo --------------------------- data No. %1
timer1
p1
timer2
if not exist p1.out goto outerr
p1score
goto end

:comerr
echo usage - check (data number)
echo ex) check 3
goto end

:comerr2
echo wrong data number!
goto end
      
:exeerr
echo p1.exe not found!
goto end

:outerr
echo p1.out not found!
goto end

:end
