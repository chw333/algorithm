@del newfun.out >nul
@copy newfun.%1 newfun.in/y >nul
@copy fun.%1 fun.dat/y >nul
@newfun
@comp newfun.out ..\output\newfun.o%1

