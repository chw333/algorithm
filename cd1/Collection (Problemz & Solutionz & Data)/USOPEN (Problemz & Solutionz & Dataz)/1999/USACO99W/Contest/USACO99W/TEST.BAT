@copy %1.in%3 input.txt
@echo   If the program finishes in 5 seconds and gives the right answer,
@echo it will get 100% score of this case. If the program finishes in
@echo 8 seconds and also gives the right answer, it will get 80% score
@echo of this case. Otherwise, it will get a score -- 0. So you can stop
@echo the program if it doesn't finish in 8 seconds.
@%2
@echo Your answer
@type output.txt
@echo Grader's answer
@type %1.ou%3
@comp output.txt %1.ou%3
