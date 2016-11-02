{$AppType Console}
Program bug;
Const
  Maxn = 20;
  Maxnbin = 1048576 - 1; { 2^10-1 }
  Maxm = 100;
  iFname = '10.in';
  oFname = '10.out';
Type
  Tpatch = Record
      Interval : Integer;
      Ce, Ca : LongInt;   { Condi   exist absent }
      Ae, Aa : LongInt;   { Affec   exist absent }
    end;
  TListPatch = array[1..Maxm] of TPatch;
  TListCheck = array[0..Maxnbin] of word;
Var
  n, nbin : Integer;
  m : Integer;
  a : TListCheck;
  Ps : TListPatch;

Procedure Init;
Var
  f : Text;
  i, j : Integer;
  S, Ss : String;
Begin
  Assign(F, iFname);
  Reset(F);
    Readln(F, n, m);
    nbin := 1 shl n - 1;
    For i := 1 to m do
      With Ps[i] do
        Begin
          Read(F, Interval);
          Readln(F, S);
          { Condi }
          While S[1] = ' ' do Delete(S, 1, 1);
          Ss := Copy(S, 1, n);
          Delete(S, 1, n);
          Ce := 0; Ca := 0;
          For j := 1 to n do
            if Ss[j] = '+' then Ce := Ce + 1 shl (n - j) else
            if Ss[j] = '-' then Ca := Ca + 1 shl (n - j);
          { Affec }
          While S[1] = ' ' do Delete(S, 1, 1);
          Ss := Copy(S, 1, n);
          Ae := 0; Aa := 0;
          For j := 1 to n do
            if Ss[j] = '+' then Ae := Ae + 1 shl (n - j) else
            if Ss[j] = '-' then Aa := Aa + 1 shl (n - j);
        end;
  Close(f);
end;

Procedure Make;
Var
  i, j : Integer;
  Pat : LongInt;
  Bb : Boolean;
Begin
  Fillchar(a, Sizeof(a), $FF);
  a[1 shl n - 1] := 0;
  Repeat
    Bb := False;
    For i:= 1 to nbin do
      if a[i] < $FFFF then
        begin
          For j := 1 to m do
            With Ps[j] do
              Begin
                if    (i and Ce = Ce)
                  and (i and Ca = 0)
                  then
                    Begin
                      Pat := (i or Ae) and not Aa;
                      if a[i] + Interval < a[Pat] then
                        Begin
                          Bb := True;
                          a[Pat] := a[i] + Interval;
                        end;
                    end;
              end;
        end;
  Until not Bb;
end;

Procedure Print;
Var
  F : Text;
Begin
  Assign(F, oFname);
  Rewrite(F);
  if a[0] < $FFFF
    then Writeln(F, a[0])
    else Writeln(F, 0);
  Close(F);
end;

Begin
  Init;
  Make;
  Print;
end.
