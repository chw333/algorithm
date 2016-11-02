@del par.out >nul
@copy par.%1 par.in/y >nul
@par
@echo yours
@type par.out
@echo standard
@type ..\output\par.o%1

