{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
 { üio uëdavinio autorius - Vilniaus TGTM licÇjaus 12 kl. moksleivis
   Laurynas Biveinis.
   Programa pateikia teisingus atsakymus, taáiau 7-10 testai veikia
   per lÇtai. Reikia padirbÇti prie optimizacijos :) }
   
program Lipdukaj;

const
   MaxSkaitm = 100;

type
   DidSk = array[1..MaxSkaitm] of 0..10;
   Lipdukai = array[0..9] of DidSk;

var
   Skaitm : array[0..9] of 0..9;
   VisoSkaitm : Lipdukai;
   DF : Text;
   i : Integer;
   a, b : DidSk;
   Intervalas : DidSk;
   Tmp : DidSk;
   Vienas : DidSk;

procedure Sudeti(const Sk1, Sk2 : DidSk; var Rez : DidSk);
   var
      i : 1..MaxSkaitm;
      Pernasa : 0..18;
begin
   FillChar(Rez, SizeOf(Rez), 0);
   Pernasa := 0;
   for i := 1 to MaxSkaitm do begin
      Rez[i] := (Sk1[i] + Sk2[i] + Pernasa) mod 10;
      Pernasa := (Sk1[i] + Sk2[i] + Pernasa) div 10
   end
end;

procedure Atimti(Sk1, Sk2 : DidSk; var Rez : DidSk);
   var i, j : 1..MaxSkaitm;
begin
   FillChar(Rez, SizeOf(Rez), 0);
   for i := 1 to MaxSkaitm do
      if Sk2[i] > Sk1[i] then begin
         Rez[i] := Sk1[i] + 10 - Sk2[i];
         j := i + 1;
         while Sk1[j] = 0 do begin
            Sk1[j] := 9;
            Inc(j)
         end;
         Dec(Sk1[j])
         end
      else
         Rez[i] := Sk1[i] - Sk2[i]
end;

procedure Dauginti(const Sk1 : DidSk; Sk2 : Integer; var Rez : DidSk);
   var
      Daline : Integer;
      i : Integer;
begin
   Daline := 0;
   for i := 1 to MaxSkaitm do begin
      Daline := Daline + Sk1[i] * Sk2;
      Rez[i] := Daline mod 10;
      Daline := Daline div 10
   end;
end;

function Daugiau(const Sk1, Sk2 : DidSk) : Boolean;
   var
      i : Integer;
begin
   for i := MaxSkaitm downto 1 do
      if Sk1[i] > Sk2[i] then begin
        Daugiau := True;
        Exit
        end
      else if Sk1[i] < Sk2[i] then begin
        Daugiau := False;
        Exit
        end;
   Daugiau := False
end;

function KiekSkaitm(const Sk : DidSk) : Integer;
   var i : Integer;
begin
   i := MaxSkaitm;
   while (i > 0) and (sk[i] = 0) do
      Dec(i);
   KiekSkaitm := i
end;

{ Palygina did. sk. ir vienaëenklç skaiáió }
function ArSk(const Sk : DidSk; Skaitm : Integer) : Boolean;
   var
      i : Integer;
begin
   for i := KiekSkaitm(Sk) downto 2 do
      if Sk[i] <> 0 then begin
         ArSk := False;
         Exit
      end;
   ArSk := (Sk[1] = Skaitm)
end;

procedure Div10(var Sk : DidSk);
   var
      i : Integer;
begin
   for i := 1 to KiekSkaitm(Sk) do
      Sk[i] := Sk[i + 1]
end;

procedure Atidaryti(const Intervalas : DidSk);
   var
      Tmp, Tmp2 : DidSk;
      i : 0..9;
begin
   for i := 0 to 9 do begin
      Dauginti(Intervalas, Skaitm[i], Tmp);
      Sudeti(VisoSkaitm[i], Tmp, Tmp2);
      VisoSkaitm[i] := Tmp2
   end
end;

procedure Spausdinti(const Sk : DidSk);
   var
      i : Integer;
      f : Text;
begin
   assign (f, 'sti.out');
   rewrite (f);
   for i := KiekSkaitm(Sk) downto 1 do
      Write(f,Sk[i]);
   close (f);
   writeln;
end;

function Sunumeruoti(const a, b : DidSk) : Boolean;
   var
      Intervalas, Kiek, Tmp, Tmp2 : DidSk;
      Reikia : Lipdukai;
      Sk, Skb : Integer;
      i : 0..9;
      j : Integer;
begin
   FillChar(Reikia, SizeOf(Reikia), 0);
   Atimti(b, a, Intervalas);
   Sk := KiekSkaitm(Intervalas);
   SkB := KiekSkaitm(b);
   Sudeti(Intervalas, Vienas, Kiek);
   Intervalas := Kiek;
   { Kiek visó skaitmenó }
   Tmp := Kiek;
   Div10(Tmp);
   for i := 0 to 9 do
     Dauginti (tmp, sk, reikia[i]);
   if Skb = Sk then begin
      { Reikia atmesti priekinius nulius }
      FillChar(Kiek, SizeOf(Kiek), 0);
      for j := 1 to Sk do
         Kiek[j] := 1;
      Atimti(Reikia[0], Kiek, Tmp);
      Reikia[0] := Tmp
      end
   else begin
      { Prideti priekinius skaitmenis, bendrus visam intervalui }
      for j := Sk + 1 to SkB do begin
         Sudeti(Reikia[b[j]], Intervalas, Tmp);
         Reikia[b[j]] := Tmp;
      end;
   end;
   for i := 0 to 9 do
      if Daugiau(Reikia[i], VisoSkaitm[i])
         then begin
            Sunumeruoti := False;
            Exit
         end;
   Sunumeruoti := True;
   for i := 0 to 9 do begin
      Atimti(VisoSkaitm[i], Reikia[i], Tmp);
      VisoSkaitm[i] := Tmp
   end
end;

function Sunumeruoti1(const Sk : DidSk) : Boolean;
   var
      i : Integer;
      Tmp : DidSk;
      j : Integer;
begin
   for i := KiekSkaitm(Sk) downto 1 do
      if ArSk(VisoSkaitm[Sk[i]], 0) then begin
          { JUK SKAIÄIAUS SK NEPAVYKO SUNUMERUOTI }
          ATIMTI(SK, VIENAS, TMP);
          Spausdinti(TMP);
          Halt
      end
      else begin
          Atimti(VisoSkaitm[Sk[i]], Vienas, Tmp);
          VisoSkaitm[Sk[i]] := Tmp
      end;
      Sunumeruoti1 := True
end;

var Viskas : Boolean;
    Didinti : Boolean;

begin
   Assign(DF, 'sti.in');
   Reset(DF);
   for i := 0 to 9 do
      Read(DF, Skaitm[i]);
   Close(DF);
   FillChar(a, SizeOf(a), 0);
   FillChar(b, SizeOf(b), 0);
   Vienas := a;
   Vienas[1] := 1;
   FillChar(Intervalas, SizeOf(Intervalas), 0);
   Intervalas[2] := 1; { 10 }
   b[1] := 9;
   Atidaryti(vienas); { atidaroma pirmoji dÇëutÇ }
   repeat
      { ar reikÇs didinti intervalÖ }
      i := 1;
      while (i < MaxSkaitm) and (a[i] = 0) and (b[i]=9)do
        i := i + 1;
      didinti := (a[i] = 9);
      if not Sunumeruoti(a, b) then begin
         if KiekSkaitm(Intervalas) = 2 then begin
            { Jei nesusimeravo intervalas lygus 10, numeruot po viena }
            for i := 1 to 10 do begin
               Atidaryti(Vienas); { atidaroma deûimt dÇëuáió }
               Sunumeruoti1(a);
               Sudeti(a, Vienas, Tmp);
               a := Tmp;
            end;
            Atimti(a, Vienas, Tmp);
            a := Tmp;
            { Galbut didinti intervala? }
            if didinti then begin
               Sudeti(b, Vienas, a);
               Dauginti(Intervalas, 10, Intervalas);
               Sudeti(a, Intervalas, Tmp);
               Atimti(Tmp, Vienas, b)
               end
            else begin
               { Numeruoti sekanti intervala }
               Sudeti(a, Intervalas, b);
               Sudeti(a, Vienas, tmp);
               a := Tmp;
            end
         end
         else begin
            { Jei nesusimeravo 100 ir daugiau intervalas, sumazinti ji }
            Div10(Intervalas);
            Sudeti(a, Intervalas, Tmp);
            Atimti(Tmp, Vienas, b)
         end
         end
      else begin
         { Prideti ka tik sunumeruoto intervalo lipdukus }
         if KiekSkaitm(b) = 1
            { Spec. atvejis: pirmam intervalui naudojam tik 8 lipdukus }
            { (Viena turim is anksciau) }
            then for i := 1 to 8 do Atidaryti(Vienas)
            else Atidaryti(Intervalas);
         { Gal didinti intervala? }
         if didinti then begin
            Sudeti(b, Vienas, a);
            Dauginti(Intervalas, 10, Intervalas);
            Sudeti(a, Intervalas, Tmp);
            Atimti(Tmp, Vienas, b);
            end
         else begin
            { Kitas intervalas }
            Sudeti(b, Vienas, a);
            Sudeti(b, Intervalas, Tmp);
            b := Tmp
         end
      end;
   until False;
end.
