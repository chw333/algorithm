@del delivery.out >nul
@copy delivery.%1 delivery.in /y>nul
@delivery
@echo yours
@type delivery.out
@echo standard
@type ..\output\delivery.o%1
