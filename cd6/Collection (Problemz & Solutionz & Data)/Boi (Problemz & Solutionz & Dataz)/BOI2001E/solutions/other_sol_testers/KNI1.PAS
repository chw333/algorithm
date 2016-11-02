{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T+,V+,X+,Y+}
{$M 16384,0,655360}

program SkoczkiNieoptymalne;

{ opracowanie nieoptymalne
  do wyznaczania maksymalnego matchingu zastosowany jest algorytm
  Edmondsa-Karpa na maksymalny przeplyw }

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


function FAZA: Boolean;
  {znajduje najkrotsza sciezke powiekszajaca}
var
  i, j: Integer;
  l, l1: Integer;
  i0, j0: Integer;
  i1, j1: Integer;
  i2, j2: Integer;
begin
  for i := 1 to n do
    for j := 1 to n do
      if Pola^ [j, i] then
        if ((i + j) mod 2 = 0) and (Skoj^ [j, i] = -1) then
        begin
          DodajDoKolejki (j, i);
          P^ [j, i] := -2
        end
        else
          P^ [j, i] := -1;

  FAZA := False;
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
              Skoj^ [j0, i0] := l1;
              Skoj^ [j1, i1] := (l1 + 4) mod 8;
              if P^ [j0, i0] = -2 then
                Break;
              j1 := j0 - Skoki [P^ [j0, i0]].w;
              i1 := i0 - Skoki [P^ [j0, i0]].k;
              l1 := P^ [j1, i1];
              j0 := j1 - Skoki [l1].w;
              i0 := i1 - Skoki [l1].k;
            until False;
            Inc (MocSkoj);
            KolPocz := 0;
            KolKon := 0;
            IleWKol := 0;
            FAZA := True;
            Exit;
          end
          else
          begin {pole czarne skojarzone}
            P^ [j1, i1] := l;     {idziemy od razu na biale z nim skoj.}
            j2 := j1 + Skoki [Skoj^ [j1, i1]].w;
            i2 := i1 + Skoki [Skoj^ [j1, i1]].k;
            {nie bylismy na nim, bo mozna
               na nie wejsc tylko ze skoj. z nim pola czarnego}
            P^ [j2, i2] := Skoj^ [j1, i1];
            DodajDoKolejki (j2, i2);
          end
      end
  end;
end;

begin
  Assign (f, 'KNI.IN');
  Reset (f);
  Assign (o, 'KNI1.OUT');
  ReWrite (o);

  New (Pola);
  New (Skoj);
  InicjujKolejke;
{  InicjujOdwiedzony;
  New (DagMinSciezek);
  InicjujStos;
  New (Nowy);}
  New (P);

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

  {szukamy skojarzenia}
  for i := 1 to n do
    for j := 1 to n do
      Skoj^ [j, i] := -1; {na poczatek -- puste skojarzenie}
  MocSkoj := 0;

  while FAZA do;

  WriteLn (o, n * n - m - MocSkoj);

  Close (f);
  Close (o);
end.

