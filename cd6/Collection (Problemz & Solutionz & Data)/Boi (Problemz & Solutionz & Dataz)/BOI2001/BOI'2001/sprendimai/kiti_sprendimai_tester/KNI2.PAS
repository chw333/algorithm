{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T+,V+,X+,Y+}
{$M 16384,0,655360}

program SkoczkiNieoptymalne;

{ opracowanie nieoptymalne, ale dosc dobre
  do wyznaczania maksymalnego matchingu zastosowany jest algorytm
  Edmondsa-Karpa na maksymalny przeplyw z nastepujacymi ulepszeniami:

     * pamietana jest lista nieskojarzonych bialych wierzcholkow
     * BFS w procedurze FAZA nie startuje jednoczesnie ze wszystkich
       nieskojarzonych wierzcholkow, ale kolejno z kazdego, az do znalezienia
       pierwszej sciezki powiekszajacej
     * pamietane jest, ktore wierzcholki sa zaznaczane jako odwiedzone,
       i pozniej tylko one sa odznaczane
}

type
  Pole = record
    w, k: ShortInt;
  end;
  PoleB = record
    w, k: Byte;
  end;
  Tab1 = array [-1..202, -1..202] of Boolean;
  Tab2 = array [1..200, 1..200] of ShortInt;
  Tab3 = array [0..19999] of PoleB;
{  Tab7 = array [0..100, 1..200] of Integer;}


const
  Skoki: array [0..7] of Pole =
    ((w:2; k:-1), (w:1; k:-2), (w:-1; k:-2), (w:-2; k:-1),
     (w:-2; k:1), (w:-1; k:2), (w:1; k:2), (w:2; k:1));
  MAXKOL = 20000;
  NIESKONCZONOSC = 65533;

var
  f, o: Text;
  Pola: ^Tab1;
  Skoj: ^Tab2;
  MocSkoj: Word;
  n: Word;
  m: Word;
  i, j: Integer;
  l: Word;
  x, y: Integer;
  P: ^Tab2; {tablica poprzednikow w drzewie BFS
        -2 -- korzen jednego z drzew
        -1 -- wierzcholek nie odwiedzony
        0..7 -- krawedz, po ktorej do tego wierzcholka przyszlismy}
  BialeNieskoj: ^Tab3; {lista nieskojarzonych bialych pol}
  IleBNieskoj: Word;   {dlugosc tej listy}
{  PozBWBialeNieskoj: ^Tab7; {pozycje poszczegolnych pol na tej liscie}
  CzarneOdwiedzone: ^Tab3;  {lista czarnych odwiedzonych w procedurze FAZA}
  IleCzOdw: Word;

{kolejka}
var
  Kolejka: ^Tab3;
  KolPocz, KolKon, IleWKol: Word;

procedure InicjujKolejke;
begin
  New (Kolejka);
  KolPocz := 0;
  KolKon := 0;
  IleWKol := 0;
end;

procedure DodajDoKolejki (j, i: Integer);
begin
  with Kolejka^ [KolKon] do
  begin
    w := j;
    k := i;
  end;
  Inc (KolKon);
  if KolKon = MAXKOL then
    KolKon := 0;
  Inc (IleWKol);
end;

procedure OddajZKolejki (var j, i: Integer);
begin
  with Kolejka^ [KolPocz] do
  begin
    j := w;
    i := k;
  end;
  Inc (KolPocz);
  if KolPocz = MAXKOL then
    KolPocz := 0;
  Dec (IleWKol);
end;

function CzyPustaKolejka: Boolean;
begin
  CzyPustaKolejka := IleWKol = 0;
end;

{pola czarne odwiedzone}
procedure DodajOdwiedzone (j, i: Integer);
begin
  with CzarneOdwiedzone^ [IleCzOdw] do
  begin
    w := j;
    k := i;
  end;
  Inc (IleCzOdw);
end;

procedure OdznaczOdwiedzone;
begin
  while IleCzOdw > 0 do
  begin
    Dec (IleCzOdw);
    with CzarneOdwiedzone^ [IleCzOdw] do
      P^ [w, k] := -1;
  end;
end;

function FAZA: Boolean;
  {znajduje najkrotsza sciezke powiekszajaca}
var
  i, j: Integer;
  l, l1, StareSkoj: Integer;
  i0, j0: Integer;
  i1, j1: Integer;
  i2, j2: Integer;
  NrB: Integer;

begin
  FAZA := False;

  for NrB := 0 to IleBNieskoj - 1 do
  begin
    with BialeNieskoj^ [NrB] do
    begin
      j := w;
      i := k;
    end;
    DodajDoKolejki (j, i);
    P^ [j, i] := -2;
    while not CzyPustaKolejka do
    begin {w kolejce sa zawsze tylko biale pola}
      OddajZKolejki (j0, i0);
      for l := 0 to 7 do {pole biale, idziemy na dow. z nim nieskoj.}
        if l <> Skoj^ [j0, i0] then
        begin
          j1 := j0 + Skoki [l].w;
          i1 := i0 + Skoki [l].k;
          if Pola^ [j1, i1] and (P^ [j1, i1] = -1) then
            {jest takie pole i jeszcze nie odwiedzone }
            if Skoj^ [j1, i1] = -1 then {pole czarne nie skojarzone}
            begin {mamy sciezke powiekszajaca}
              l1 := l;
              repeat
                StareSkoj := Skoj^ [j0, i0];
                Skoj^ [j0, i0] := l1;             {j0, i0 -- pole biale}
                Skoj^ [j1, i1] := (l1 + 4) mod 8; {j1, i1 -- pole czarne}
                if P^ [j0, i0] = -2 then
                  Break;
                j1 := j0 + Skoki [StareSkoj].w;
                i1 := i0 + Skoki [StareSkoj].k;
                l1 := P^ [j1, i1];
                j0 := j1 - Skoki [l1].w;
                i0 := i1 - Skoki [l1].k;
              until False;
              Dec (IleBNieskoj);
              BialeNieskoj^ [NrB] := BialeNieskoj^ [IleBNieskoj];
              Inc (MocSkoj);
              KolPocz := 0;
              KolKon := 0;
              IleWKol := 0;
              OdznaczOdwiedzone;
              P^ [j, i] := -1;
              FAZA := True;
              Exit;
            end
            else
            begin {pole czarne skojarzone}
              P^ [j1, i1] := l;     {idziemy od razu na biale z nim skoj.}
              DodajOdwiedzone (j1, i1);
              j2 := j1 + Skoki [Skoj^ [j1, i1]].w;
              i2 := i1 + Skoki [Skoj^ [j1, i1]].k;
              {nie bylismy na nim, bo mozna
                 na nie wejsc tylko ze skoj. z nim pola czarnego}
              DodajDoKolejki (j2, i2);
            end
        end
    end;
    P^ [j, i] := -1;
  end;
  OdznaczOdwiedzone;
end;

begin
  Assign (f, 'KNI.IN');
  Reset (f);
  Assign (o, 'KNI2.OUT');
  ReWrite (o);

  New (Pola);
  New (Skoj);
  InicjujKolejke;
  New (P);
  New (BialeNieskoj);
  New (CzarneOdwiedzone);
  IleCzOdw := 0;

  ReadLn (f, n, m);
  for j := -1 to n + 2 do
  begin
    Pola^ [j, -1] := False;
    Pola^ [j, 0] := False;
    Pola^ [j, n + 1] := False;
    Pola^ [j, n + 2] := False;
    Pola^ [-1, j] := False;
    Pola^ [0, j] := False;
    Pola^ [n + 1, j] := False;
    Pola^ [n + 2, j] := False;
  end;

  for i := 1 to n do
    for j := 1 to n do
      Pola^ [j, i] := True;

  for l := 1 to m do
  begin
    ReadLn (f, x, y);
    Pola^ [y, x] := False;
  end;

  IleBNieskoj := 0;
  {szukamy skojarzenia}
  for i := 1 to n do
    for j := 1 to n do
      if Pola^ [j, i] then
      begin
        Skoj^ [j, i] := -1; {na poczatek -- puste skojarzenie}
        if (i + j) mod 2 = 0 then {biale}
        begin
          with BialeNieskoj^ [IleBNieskoj] do
          begin
            w := j;
            k := i;
          end;
{          PozBWBialeNieskoj^ [j div 2, i] := IleBNieskoj;}
          Inc (IleBNieskoj);
        end;
        P^ [j, i] := -1; {nie odwiedzone w procedurze FAZA}
      end;
  MocSkoj := 0;

  while FAZA do;

  WriteLn (o, n * n - m - MocSkoj);

  Close (f);
  Close (o);
end.

