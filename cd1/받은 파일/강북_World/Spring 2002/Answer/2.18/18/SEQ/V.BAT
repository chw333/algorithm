@echo off
del seq.out
copy seq.in%1 seq.inp > k.tx
timer 
cmp

