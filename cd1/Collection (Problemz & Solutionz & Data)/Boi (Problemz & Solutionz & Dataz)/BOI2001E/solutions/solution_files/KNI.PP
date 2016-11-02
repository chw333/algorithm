{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T+,V+,X+,Y+}
{$M 16384,0,655360}

program Skoczki;

{  opracowanie wzorcowe
   Marcin Sawicki I.2000.

Algorytm
   licznosc maksymalnego zbioru niezaleznego w grafie dwudzielnym G=<V,E>
   jest wyznaczana z maksymalnego matchingu wedlug wzoru dla grafow
   dwudzielnych:

   licznosc maksymalnego zbioru niezaleznego =
     = ³V³ - licznosc minimalnego pokrycia wierzcholkowego =
     = licznosc maksymalnego matchingu

   dowod: patrz
      Witold Lipski ,,Kombinatoryka dla programistow'' WNT Warszawa 1982
      rozdzial 4, lemat 4.15 i wniosek 4.16

   Matching jest wyznaczany algorytmem Hopcrofta-Karpa
     (patrz tamze, algorytm 4.10)
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
  Tab4 = array [0..99, 1..200] of Word;
  Tab5 = array [1..200, 1..200] of Byte;
  Tab6 = array [1..200, 1..200] of Boolean;

const
  Skoki: array [0..7] of Pole =
    ((w:2; k:-1), (w:1; k:-2), (w:-1; k:-2), (w:-2; k:-1),
     (w:-2; k:1), (w:-1; k:2), (w:1; k:2), (w:2; k:1));
  MAXKOL = 40000;
  NIESKONCZONOSC = 65533;

var
  f, o: Text;
  Pola: ^Tab1;
  Skoj: ^Tab2; { Skoj [j, i] = -1 -- pole nie skojarzone; 0..7 -- skojarzenie}
  MocSkoj: Word;
  n: Word;
  m: Word;
  i, j: Integer;
  l: Word;
  x, y: Integer;
  DagMinSciezek: ^Tab5; {krawedzie dagu najkrotszych sciezek; reprezentacja
    listy sasiedztwa na bitach; DagMinSciezek^ [j, i] ma ustawiony l-ty bit
    l = 0..7 wtwg istnieje w tym dagu krawedz
            (j, i) -----> (j + Skoki [l].w, i + Skoki [l].k); }


{oblicza pozycje w tabeli Skoki, odpowiadajaca danej krawedzi w grafie}
function NrSkoku (j0, i0, j1, i1: Integer): Integer;
var
  l: Integer;
begin
  for l := 0 to 7 do
    with Skoki [l] do
      if (j1 - j0 = w) and (i1 - i0 = k) then
      begin
        NrSkoku := l;
        Break
      end;
end;

{kolejka}
var
  Kolejka: array [0..1] of ^Tab3;
  KolPocz, KolKon, IleWKol: Word;

procedure InicjujKolejke;
begin
  New (Kolejka [0]);
  New (Kolejka [1]);
  KolPocz := 0;
  KolKon := 0;
  IleWKol := 0;
end;

procedure DodajDoKolejki (j, i: Integer);
begin
  with Kolejka [KolKon mod 2]^[KolKon div 2] do
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
  with Kolejka [KolPocz mod 2]^[KolPocz div 2] do
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



{dane procedury PGA}
var
  Odwiedzony: array [0..1] of ^Tab4;
  DlugNajkrSciezkiPlus2: Word;

procedure InicjujOdwiedzony;
begin
  New (Odwiedzony [0]);
  New (Odwiedzony [1]);
end;

function KiedyOdwiedzony (j, i: Integer): Word;
begin
  KiedyOdwiedzony := Odwiedzony [j mod 2]^[(j - 1) div 2, i];
end;

procedure UstawOdwiedzony (j, i: Integer; odw: Word);
begin
  Odwiedzony [j mod 2]^[(j - 1) div 2, i] := odw;
end;

{konstruujemy dag, zbudowany z najkrotszych sciezek powiekszajacych matching}
procedure PGA;
var
  i, j: Integer;
  i1, j1: Integer;
  l: Integer;
  Kiedy: Word;
begin
  KolPocz := 0; KolKon := 0;
  for i := 1 to n do
    for j := 1 to n do
    begin
      DagMinSciezek^ [j, i] := 0;
      if Pola^ [j, i] and
         ((i + j) mod 2 = 0) {biale pole}
         and (Skoj^ [j, i] = -1) then {nie skojarzone}
         begin
           DodajDoKolejki (j, i);
           UstawOdwiedzony (j, i, 1);
         end
      else
        UstawOdwiedzony (j, i, NIESKONCZONOSC);
    end;

  DlugNajkrSciezkiPlus2 := NIESKONCZONOSC;

  while not CzyPustaKolejka do
  begin
    OddajZKolejki (j, i);
    Kiedy := KiedyOdwiedzony (j, i);
    if (i + j) mod 2 = 0 then {biale pole}
    begin
      if DlugNajkrSciezkiPlus2 = NIESKONCZONOSC then
        for l := 0 to 7 do
          if Skoj^ [j, i] <> l then {idziemy po nieskojarzonej krawedzi}
          begin
            j1 := j + Skoki [l].w;
            i1 := i + Skoki [l].k;
            if Pola^ [j1, i1] and {jest takie pole na planszy}
              (KiedyOdwiedzony (j1, i1) > Kiedy) then
                {tzn. KiedyOdwiedzony = Kiedy + 1   lub = NIESKONCZONOSC}
                begin
                  if KiedyOdwiedzony (j1, i1) = NIESKONCZONOSC then
                  begin
                    DodajDoKolejki (j1, i1);
                    UstawOdwiedzony (j1, i1, Kiedy + 1);
                  end;
                  {jesli KiedyOdwiedzony = Kiedy + 1, to tworzy sie w dagu
                    "cykl", choc nie w sensie grafu skierowanego, lecz
                    w sensie grafu nieskierowanego: dwie drogi prowadzace do
                    tego samego wierzcholka }

                  DagMinSciezek^ [j, i] :=      {dodajemy krawedz do dagu}
                    DagMinSciezek^ [j, i] or (1 shl l);
                end;
          end
    end
    else {czarne pole}
    begin
      if Skoj^ [j, i] = -1 then {nieskojarzone, mamy sciezke powiekszajaca}
      begin
        DlugNajkrSciezkiPlus2 := Kiedy + 1
          {najkrotsza sciezka powiekszajaca ma nastepujaca dlugosc
            (Kiedy - 1) krawedzi, czyli Kiedy wierzcholkow}
      end
      else
      begin   {skojarzone, cofamy sie na biale pole po krawedzi skojarzenia}
        {na pewno jeszcze nie bylismy na tym bialym polu, bo startowalismy
         z bialych nieskojarzonych, a dojsc na nie moglismy tylko z tego
         czarnego pola, ktore jest z nim skojarzone, a to z kolei pole
         odwiedzamy co najwyzej raz}
        j1 := j + Skoki [Skoj^ [j, i]].w;
        i1 := i + Skoki [Skoj^ [j, i]].k;
        if DlugNajkrSciezkiPlus2 = NIESKONCZONOSC then
        begin
          DagMinSciezek^ [j, i] :=      {dodajemy krawedz do dagu}
            DagMinSciezek^ [j, i] or (1 shl Skoj^ [j, i]);
          DodajDoKolejki (j1, i1);
          UstawOdwiedzony (j1, i1, Kiedy + 1);
        end;
      end;
    end;
  end;
end;

{Stos -- zajmuje ten sam obszar pamieci, co kolejka procedury PGA}
var
  WysStosu: Word;

procedure InicjujStos;
begin
  WysStosu := 0;
end;

procedure Push (j, i: Integer);
begin
  with Kolejka [WysStosu mod 2]^[WysStosu div 2] do
  begin
    w := j;
    k := i;
  end;
  Inc (WysStosu);
end;

procedure DajSzczyt (var j, i: Integer);
begin
  with Kolejka [(WysStosu - 1) mod 2]^[(WysStosu - 1) div 2] do
  begin
    j := w;
    i := k;
  end;
end;

procedure Pop (var j, i: Integer);
begin
  DajSzczyt (j, i);
  Dec (WysStosu);
end;

function CzyPustyStos: Boolean;
begin
  CzyPustyStos := WysStosu = 0;
end;

{dane procedury FAZA}
var
  Nowy: ^Tab6;
  P: ^Tab5;


{Faza algorytmu Hopcrofta-Karpa, znalezienie maksymalnej ze wzgledu na
inkluzje rodziny rozlacznych wierzcholkowo sciezek w znalezionym dagu}
procedure FAZA;
var
  i, j: Integer;
  i0, j0: Integer;
  i1, j1: Integer;
  B: Boolean;
  ic, jc, ib, jb: Integer;
begin
  for i := 1 to n do
    for j := 1 to n do
      if Pola^ [j, i] then
      begin
        Nowy^ [j, i] := True;
        P^ [j, i] := 0;
        {P - numer nastepnej do odwiedzenia w porzadku DFS krawedzi,
             wychodzacej z danego wierzcholka}
      end;

  for i0 := 1 to n do
    for j0 := 1 to n do
      if Pola^ [j0, i0] and
         ((i0 + j0) mod 2 = 0) {biale pole}
         and (Skoj^ [j0, i0] = -1) {nie skojarzone}
         and Nowy^ [j0, i0] then   {nie odwiedzone}
      begin
        Push (j0, i0);      {startujemy DFS po naszym dagu z tego pola}
        while not CzyPustyStos do
        begin
          DajSzczyt (j, i);
          if ((i + j) mod 2 <> 0) and {czarne pole}
             (Skoj^ [j, i] = -1) then {nieskojarzone, mamy sciezke powieksz.}
          begin
            {zwiekszamy skojarzenie}
            while not CzyPustyStos do
            begin
              Pop (jc, ic);
              Pop (jb, ib);
              Skoj^ [jb, ib] := NrSkoku (jb, ib, jc, ic);
              Skoj^ [jc, ic] := NrSkoku (jc, ic, jb, ib);
            end;
            Inc (MocSkoj);
          end
          else
          begin
            while (P^ [j, i] < 8) and
              ((DagMinSciezek^ [j, i] and (1 shl P^ [j, i]) = 0) or
              not Nowy^ [j + Skoki [P^ [j, i]].w, i + Skoki [P^ [j, i]].k]) do
                Inc (P^ [j, i]);
            if P^ [j, i] < 8 then
            begin
              j1 := j + Skoki [P^ [j, i]].w;
              i1 := i + Skoki [P^ [j, i]].k;
              Push (j1, i1);
              Nowy^ [j1, i1] := False;
            end
            else {przejrzelismy juz wszystkie wychodzace krawedzie}
              Pop (j, i);
          end;
        end;
      end;
end;

begin
  Assign (f, 'KNI.IN');
  Reset (f);
  Assign (o, 'KNI.OUT');
  ReWrite (o);

  New (Pola);
  New (Skoj);
  InicjujKolejke;
  InicjujOdwiedzony;
  New (DagMinSciezek);
  InicjujStos;
  New (Nowy);
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

  PGA;
  while DlugNajkrSciezkiPlus2 < NIESKONCZONOSC do
  begin
    FAZA;
    PGA;
  end;

  WriteLn (o, n * n - m - MocSkoj);

  Close (f);
  Close (o);
end.
