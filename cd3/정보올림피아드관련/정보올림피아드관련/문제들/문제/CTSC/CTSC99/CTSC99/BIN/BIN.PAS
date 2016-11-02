{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+}
{$M 16384,0,655360}
Program Bin;
Const
  Maxn = 120;
  Maxc = 100;
  iFname = '10.in';
  oFname = '10.out';
Type
  Tnum = array[-MaxC..0] of Integer;
  TListn = array[1..Maxn] of Integer;
Var
  m : Tnum;
  Lenm : Integer;
  Re : Tnum;

Procedure Init;
Var
  F : Text;
  i, pp, t : Integer;
  S : String;
  Bb : Boolean;
Begin
  Assign(F, iFname);
  Reset(F);
    Readln(F, S);
  Close(F);
  While S[Ord(S[0])] = ' ' do Dec(S[0]);
  Lenm := Length(S);
  Fillchar(m, Sizeof(m), 0);
  For i := 1 to Lenm do
    m[-(Lenm - i + 1)] := Ord(S[i]) - 48;
    { Bin }
  S := '';
  Repeat
    Bb := False;
    For i := -Maxc to -1 do
      if m[i] <> 0 then
        begin
          Bb := True;
          Break;
        end;
    if not Bb then Break;
    if odd(m[-1])
      then S := '1' + S
      else S := '0' + S;
    Pp := 0;
    For i := -Maxc to -1 do
      Begin
        t := (Pp + m[i]) div 2;
        Pp := 0;
        if Odd(Pp + m[i]) then Pp := 10;
        m[i] := t;
      end;
  Until False;
  Lenm := Length(S);
  Fillchar(m, Sizeof(m), 0);
  For i := 1 to Lenm do
    m[-(Lenm - i + 1)] := Ord(S[i]) - 48;
end;

Procedure PrintNum(a : Tnum);
Var
  i : Integer;
Begin
  i := -MaxC;
  While (i <= 0) and (a[i] = 0) do Inc(i);
  if i = 0 then Write(0) else
    For i := i to -1 do
      Write(a[i]);
  Writeln;
end;

Procedure PrintNumToFile(a : Tnum; Fname : String);
Var
  F : Text;
  i : Integer;
Begin
  Assign(F, Fname);
  Rewrite(F);
    i := -MaxC;
    While (i <= 0) and (a[i] = 0) do Inc(i);
    if i >= 0 then Write(F, 0) else
      For i := i to -1 do
        Write(F, a[i]);
  Close(F);
end;

Procedure Add(Var a : Tnum; b : Tnum);  { a := a + b }
Var
  i, Jp : Integer;
Begin
  Jp := 0;
  For i := -1 downto -MaxC do
    Begin
      Inc(a[i], b[i] + Jp);
      Jp := a[i] div 10;
      a[i] := a[i] mod 10;
    end;
end;

Procedure Mul(Var a : Tnum; Fac : Byte); { a := a * & }
Var
  i, Jp : Integer;
Begin
  Jp := 0;
  For i := -1 downto -MaxC do
    Begin
      a[i] := a[i] * Fac + Jp;
      Jp := a[i] div 10;
      a[i] := a[i] mod 10;
    end;
end;

Procedure C(n, x : Integer; Var a : Tnum);  { C(x)n }
Var
  i, j, t : Integer;
  Fs : array[1..100] of Integer;
  Procedure DiscardFactor(Fac : Integer);
  Var
    j : Integer;
  Begin
    For j := 1 to n do
      if Fs[j] mod Fac = 0 then
        begin
          Fs[j] := Fs[j] div Fac;
          Exit;
        end;
  end;
Begin
  if x > n div 2 then x := n - x;
  Fillchar(Fs, Sizeof(Fs), 0);
  For i := 1 to x do
    Fs[i] := n - i + 1;
  For i := x downto 1 do
    begin
      t := i;
      For j := 2 to x do
        if t mod j = 0 then
          While t mod j = 0 do
          begin
            t := t div j;
            DiscardFactor(j);
            if t = 1 then Break;
          end;
    end;
  Fillchar(a, Sizeof(a), 0);
  a[-1] := 1;
  For i := 1 to x do
    Mul(a, Fs[i]);
end;

Procedure CountLen(L : Integer; Noa : Integer; Var a : Tnum);
Var
  i, j : Integer;
  cc : Tnum;
Begin
  Fillchar(a, Sizeof(a), 0);
  if L <= Noa then Exit;
  For i := 0 to (L - Noa) div 2 - Ord(not Odd(L - Noa)) do   { i : num of 1 }
    Begin
      c(L, i, cc);
      Add(a, cc);
    end;
end;

Procedure Collect;
Var
  k, Noa : Integer;
  t : Tnum;
Begin
  Fillchar(Re, Sizeof(Re), 0);
{  Re[-1] := -1;  { For 0 }
  { Smaller }
  Noa := 1;
  For k := 2 to Lenm - 1 do
    begin
      CountLen(Lenm - k, Noa, t);
      Add(Re, t);
    end;
  { Larger }
  Noa := 1;
  For k := 2 to Lenm - 1 do
    Begin
      if m[-(Lenm - k + 1)] = 1 then
        begin
          Inc(Noa);
          CountLen(Lenm - k, Noa - 2, t);
          Add(Re, t);
        end else Dec(Noa);
    end;
  Fillchar(t, Sizeof(t), 0);
  t[-1] := 1;
  if (m[-1] = 0) and (Noa - 1 < 0) then Add(Re, t);
  if (m[-1] = 1) and (Noa - 1 < 0) then Add(Re, t);
  if (m[-1] = 1) and (Noa + 1 < 0) then Add(Re, t);
end;

Begin
  Init;
  Collect;
  PrintNumToFile(Re, oFname);
end.
