Program Max_Duf_Test;
Const
  Maxn = 10;
  iFname = 't.dat';
  oFname = 't.out';
Type
  TMap = array[1..Maxn, 1..Maxn] of Integer;
  TListn = array[1..Maxn] of Integer;
Var
  n : Integer;
  a, f : TMap;
  Lc : TListn;   { swell }

Procedure Init;
Var
  f : Text;
  i, j : Integer;
  p1, p2, hold : Integer;
Begin
  Fillchar(a, Sizeof(a), 0);
  Assign(f, iFname);
  Reset(F);
    Readln(F, n);
    Readln(F, p1, p2, hold);
    While p1 <> 0 do
      begin
        a[p1, p2] := hold;
        Readln(F, p1, p2, hold);
      end;
  Close(F);
end;

Procedure Make;
Var
  i, j, k, hold, P1, P2 : Integer;
  Bb, Dry : Boolean;
Begin
  Fillchar(f, Sizeof(f), 0);
  Repeat
    Dry := False;
    { Distend }
    Fillchar(Lc, Sizeof(Lc), 0);
    Lc[1] := -1;
    Repeat
      Bb := False;
      For i := 1 to n do
      if Lc[i] <> 0 then
        Begin
          For j := 1 to n do
            if    (i <> j)
              and (Lc[j] = 0)
              and (a[i, j] - f[i, j] > 0)
              then
                begin
                  Bb := True;
                  Lc[j] := i;
                 end;
        end;
    Until (Lc[n] <> 0) or (not Bb);
    if not Bb then Dry := True;
    if not Dry then
      begin
        k := n;
        hold := MaxInt;
        While Lc[k] <> -1 do
          begin
            P1 := Lc[k];
            P2 := k;
            j := a[p1, p2] - f[p1, p2];
            if j < hold then hold := j;
            k := Lc[k];
          end;
        k := n;
        While Lc[k] <> -1 do
          begin
            P1 := Lc[k];
            P2 := k;
            Inc(f[p1, p2], hold);
            Dec(f[p2, p1], hold);
            k := Lc[k];
          end;
      end;
  Until Dry;
end;

Procedure Print;
Var
  i, Sum : Integer;
Begin
  Sum := 0;
  For i := 2 to n do
    Inc(Sum, f[1, i]);
  Writeln('  Max = ', Sum);
end;

Begin
  Init;
  Make;
  Print;
end.
