{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+}
{$M 16384,0,655360}
Program New_Homeland;   { Cherish }
Const
  Maxn = 15;
  Maxm = 20;
  Maxk = 50;
  MaxT = 100;
  MaxVal = 127;
  iFname = '10.in';
  oFname = '10.out';
Type
  TMap = array[1..MaxT, 1..Maxn, 1..Maxn] of ShortInt;
  TListn2 = array[1..MaxT, 1..Maxn, 1..2] of ShortInt;
  Tfanline = Record
      hold : Byte;
      r : Byte;
      Line : array[1..Maxn] of ShortInt;
    end;
  TListfans = array[1..Maxm] of Tfanline;

Var
  k, n, m, kk : Integer;
  a, f : TMap;
  Lc : TListn2;
  Lfan : TListfans;
  MaxHold : Integer;

Procedure Init;
Var
  F : Text;
  i, j : Integer;
Begin
  Fillchar(a, Sizeof(a), 0);
  Fillchar(Lfan, Sizeof(Lfan), 0);
  Assign(F, iFname);
  Reset(F);
    Readln(F, n, m, kk);
    Inc(n, 2);
    For i := 1 to m do
    With Lfan[i] do
      Begin
        Read(f, hold, r);
        For j := 1 to r do
          begin
            Read(f, Line[j]);
            Inc(Line[j]);
            if Line[j] = 0
              then Line[j] := n;
          end;
      end;
  Close(F);
end;

Procedure Make;
Var
  i, j, p,
  pi, pj, Li, Lj, hold, hol : Integer;
  Bb, Dry : Boolean;
Begin
  Fillchar(f, sizeof(f), 0);
  Repeat
    Dry := False;
    { Distend }
    Fillchar(Lc, Sizeof(Lc), 0);
    Lc[1, 1, 1] := -1;
    Lc[1, 1, 2] := -1;
    Repeat
      Bb := False;
      For i := 1 to k do
      For j := 1 to n do
        if Lc[i, j, 1] <> 0 then
          begin
            { Back }
           if i > 1 then
            For p := 1 to n do
              if    (Lc[i - 1, p, 1] = 0)
                and (f[i - 1, p, j] > 0)
                then
                  begin
                    Bb := True;
                    Lc[i - 1, p, 1] := i;
                    Lc[i - 1, p, 2] := j;
                  end;{}
            { forth }
           if i < k then
            For p := 1 to n do
              if    (Lc[i + 1, p, 1] = 0)
                and (a[i, j, p] - f[i, j, p] > 0)
                then
                  begin
                    Bb := True;
                    Lc[i + 1, p, 1] := i;
                    Lc[i + 1, p, 2] := j;
                  end;
          end;
    Until (Lc[k, n, 1] <> 0) or (not Bb);
    if not Bb then Dry := True;
    if not Dry then
      begin
        Pi := k;   Pj := n;
        hold := Maxval;
        While Lc[Pi, Pj, 1] <> -1 do
          begin
            Li := Lc[Pi, Pj, 1];
            Lj := Lc[Pi, Pj, 2];
            if Li < Pi
              then hol := a[Li, Lj, Pj] - f[Li, Lj, Pj]
              else hol := f[Pi, Pj, Lj];
            if hol < hold then hold := hol;
            p := Lc[Pi, Pj, 1];
            Pj := Lc[Pi, Pj, 2];
            Pi := P;
          end;
        Pi := k;   Pj := n;
        While Lc[Pi, Pj, 1] <> -1 do
          begin
            Li := Lc[Pi, Pj, 1];
            Lj := Lc[Pi, Pj, 2];
            if Li < Pi
              then Inc(f[Li, Lj, Pj], hold)
              else Dec(f[Pi, Pj, Lj], hold);
            p := Lc[Pi, Pj, 1];
            Pj := Lc[Pi, Pj, 2];
            Pi := P;
          end;
      end;
  Until Dry;
  MaxHold := 0;
  For i := 1 to n do
    Inc(MaxHold, f[1, 1, i]);
end;

Procedure Commandor;
Var
  i : Integer;
  S1, S2 : Integer;
Begin
  k := 1;
  Repeat
    { Construction }
    For i := 1 to n do
      a[k, i, i] := MaxVal;
    For i := 1 to m do
      Begin
        With Lfan[i] do
          begin
            S1 := Line[(k - 1) mod r + 1];
            S2 := Line[(k - 0) mod r + 1];
          end;
        if s1 <> s2 then
          a[k, s1, s2] := Lfan[i].hold;
      end;
    Inc(k);
    MaxHold := 0;
    Make;
  Until (MaxHold >= kk) or (k > kk * 2);
  Dec(k);
  if MaxHold < kk then k := 0;
end;

Procedure Print;
Var
  f : Text;
Begin
  Assign(F, oFname);
  Rewrite(F);

    Writeln(F, k);
  Close(F);
end;

Begin
  Init;
  Commandor;
  Print;
end.
