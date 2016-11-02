@del mobile.out >nul
@copy mobile.%1 mobile.in >nul
@mobile
@echo yours
@type mobile.out
@echo standard
@type ..\output\mobile.o%1

