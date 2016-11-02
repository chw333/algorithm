{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
{ Lauryno Biveinio sprendimas, Vilniaus TGTM lic‚jus, 12 kl.}
program LaikauJuostas;

const
    MaxN = 60;

type
    Laikas = record
               h, m : Byte
             end;

var
    Laikai : array[1..MaxN, 0..MaxN - 1] of Laikas;
    n : 1..MaxN;
    KiekVirs : Integer;
    Grafas : array[1..MaxN, 0..MaxN - 1] of record
                i : Set of 0..MaxN - 1;
                is : Set of 0..MaxN - 1
             end;

procedure PradDuom;
    var
       DF        : Text;
       SkaitL, i : Integer;
       L         : Laikas;
       Juosta    : Integer;
begin
    Assign(DF, 'zon.in');
    Reset(DF);
    ReadLn(DF, n);
    for i := 1 to n do begin
       ReadLn(DF, SkaitL);
       L.h := SkaitL div 100;
       L.m := SkaitL mod 100;
       for Juosta := 0 to n - 1 do begin
          Laikai[i, Juosta].h := L.h + Juosta;
          Laikai[i, Juosta].m := L.m
       end
    end;
    Close(DF)
end;

procedure DarykGrafa;
    var
       i, j, k : Integer;
begin
    FillChar(Grafas, SizeOf(Grafas), 0);
    for i := 2 to n do                { i-asis pranežimas }
       for j := 0 to n - 1 do         { j-oji juosta }
           if Laikai[i, j].h < n then
              for k := 0 to n - 1 do  { k-oji juosta }
                 if (j <> k) and
                    (Laikai[i - 1, k].h < Laikai[i, j].h) or
                    ((Laikai[i - 1, k].h = Laikai[i, j].h) and
                    (Laikai[i - 1, k].m < Laikai[i, j].m))
                    then begin
                       Grafas[i, j].I := Grafas[i, j].I + [k];
                       Grafas[i - 1, k].Is := Grafas[i - 1, k].Is + [j]
                    end
end;

procedure PrastinkGrafa;
    var
       Kartoti : Boolean;
       i, j, k : Integer;
       TikVienas : Integer;
begin
    repeat
       Kartoti := False;
       for j := 0 to n - 1 do begin
          if Grafas[1, j].Is = [] then
             for k := 0 to n - 1 do
                if j in Grafas[2, k].I then begin
                   Grafas[2, k].I := Grafas[2, k].I - [j];
                   Kartoti := True
                end;
          if Grafas[n, j].I = [] then
             for k := 0 to n - 1 do
                if j in Grafas[n - 1, k].Is then begin
                   Grafas[n - 1, k].Is := Grafas[n - 1, k].Is - [j];
                   Kartoti := True
                end
       end;
       for i := 2 to n - 1 do
          for j := 0 to n - 1 do begin
             if (Grafas[i, j].Is = []) or (Grafas[i, j].I = []) then begin
                for k := 0 to n - 1 do begin
                   if j in Grafas[i - 1, k].Is then begin
                      Grafas[i - 1, k].Is := Grafas[i - 1, k].Is - [j];
                      Kartoti := True
                   end;
                   if j in Grafas[i + 1, k].I then begin
                      Grafas[i + 1, k].I := Grafas[i + 1, k].I - [j];
                      Kartoti := True
                   end
                end;
                Grafas[i, j].I := [];
                Grafas[i, j].Is := [];
             end
          end;
       { ka‘kuris pranežimas yra tik vienoje juostoje }
       for i := 1 to n do begin
          TikVienas := -1;
          for j := 0 to n - 1 do
             if (Grafas[i, j].Is <> []) or (Grafas[i, j].I <> [])
                then begin
                   if TikVienas > -1
                       then TikVienas := -2
                   else if TikVienas = -1
                       then TikVienas := j;
                end;
          if TikVienas > -1 then begin
             for k := 1 to n do
                if (k <> i) and ((Grafas[k, TikVienas].Is <> []) or
                   (Grafas[k, TikVienas].I <> []))
                   then begin
                      Kartoti := True;
                      Grafas[k, TikVienas].Is := [];
                      Grafas[k, TikVienas].I := []
                   end
          end;
        end;
       { ka‘kurioje juostoje yra tik 1 pranežimas }
       for j := 0 to n-1 do begin
          TikVienas := -1;
          for i := 1 to n do
             if (Grafas[i, j].Is <> []) or (Grafas[i, j].I <> [])
                then begin
                   if TikVienas > -1
                       then TikVienas := -2
                   else if TikVienas = -1
                       then TikVienas := i;
                end;
          if TikVienas > -1 then begin
             for k := 0 to n-1 do
                if (k <> j) and ((Grafas[TikVienas, k].Is <> []) or
                   (Grafas[TikVienas, k].I <> []))
                   then begin
                      Kartoti := True;
                      Grafas[TikVienas, k].Is := [];
                      Grafas[TikVienas, k].I := []
                   end
       end;
      end
    until not Kartoti
end;

procedure PaieskaGrafe;
    var
       Panaudotos : set of 0..MaxN - 1;
       Ats : array[1..MaxN] of 0..MaxN - 1;

    procedure Rezultatai;
       var
          RF : Text;
          i : Integer;
    begin
       Assign(RF, 'zon.out');
       Rewrite(RF);
       for i := 1 to n do
          Write(RF, Ats[i], ' ');
       WriteLn(RF);
       Close(RF);
       Halt
    end;

    procedure Zingsnis(i, j : integer);
       var k : Integer;
    begin
       for k := 0 to n - 1 do begin
          if (k in Grafas[i, j].Is) and not (k in Panaudotos) then begin
             Ats[i + 1] := k;
             if (i + 1) = n then
                Rezultatai;
             Panaudotos := Panaudotos + [k];
             Zingsnis(i + 1, k);
             Panaudotos := Panaudotos - [k];
          end
       end
    end;

    var t : integer;

begin
    for t := 0 to n - 1 do begin
       Ats[1] := t;
       Panaudotos := [t];
       Zingsnis(1, t)
    end
end;

begin
    PradDuom;
    DarykGrafa;
    PrastinkGrafa;
    PaieskaGrafe
end.
