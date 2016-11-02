@echo NOI'99 (Singapore)
@echo Problem: %1  Case id: %2
@del %1.out >nul
@copy %2%1.in %1.in/y>nul
@echo Running contestant's program...
@%1
@echo Contestant's Output
@type %1.out
@echo Standard Output
@type %2%1.out

