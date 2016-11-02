{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+}
{$M 16384,0,655360}
Program Bin_Check;
Const
  iFname = '4.in';
Var
  F : Text;
  m : LongInt;
  i, j, k, Re, s, t : LongInt;
Begin
  Assign(F, iFname);
  Reset(F);
    Readln(F, m);
  Close(F);
  Re := 0;
  For i := 1 to m do
    begin
      S := 0;
      t := i;
      While t <> 0 do
        begin
          if odd(t)
            then Inc(s)
            else Dec(s);
          t := t shr 1;
        end;
      if s < 0 then Inc(Re);
    end;
  Writeln(' m = ', m, '   A = ', Re);
end.
