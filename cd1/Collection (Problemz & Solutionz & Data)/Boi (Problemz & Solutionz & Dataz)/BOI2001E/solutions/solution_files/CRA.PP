{ Rozwi±zanie wzorcowe zadania CRA --- program deszyfruj±cy }
{ Autor: Pawe³ Wolff }
{ Data : 28.05.2001  }


program Decrypt_Chi2;

const
  N = Ord('Z') - Ord('A') + 1;
  KEY_LEN = 10;
  CHI2_LIMIT = 0.1;

type
  TDistrib = array [0..N-1] of real;

var
  p: TDistrib;
    { rozk³ad prawdopodobieñstwa wyst±pienia poszczególnych
      liter we fragmencie odkodowanego tekstu }
  q: array [1..KEY_LEN] of TDistrib;
    { q[i] --- rozk³ad prawdopodobieñstwa wyst±pienia poszczególnych
               liter wsrod co KEY_LEN-tej litery tekstu zakodowanego,
               pocz±wszy od i-tej litery tego tekstu }
  letters: array [1..KEY_LEN] of longint;
    { letters[i] --- liczba liter w tek¶cie zakodowanym --- licz±c
                     co KEY_LEN-ta literê, pocz±wszy od i-tej litery
                     tego tekstu }
  key: array [1..KEY_LEN] of integer;


procedure GetDistrib(var f: text);
{ na podstawie tekstu z pliku f wyznaczany jest rozk³ad p }
var
  i: integer;
  c: char;
  t: array [0..N-1] of longint; { liczba poszczególnych liter w tek¶cie }
  letters: longint;             { liczba wszystkich liter w tek¶cie }

begin
  letters := 0;
  for i := 0 to N - 1 do
    t[i] := 0;

  while not Eof(f) do begin
    while not Eoln(f) do begin
      Read(f, c);
      c := UpCase(c);
      if c in ['A'..'Z'] then begin
        Inc(t[Ord(c) - Ord('A')]);
        Inc(letters);
      end;
    end;
    if not Eof(f) then
      Readln(f);
  end;

  for i := 0 to N - 1 do
    p[i] := t[i] / letters;
end;


procedure GetDistribs(var f: text);
{ na podstawie tesktu z pliku f wyznaczanane s± rozk³ady
  q[i] (dla i = 1..KEY_LEN) }
var
  i, j, pos: integer;
  c: char;
  t: array [1..KEY_LEN, 0..N-1] of longint;
    { t[i] --- liczba poszczególnych liter w¶ród co KEY_LEN-tej litery
               tekstu, pocz±wszy od i-tej litery tego tekstu }

begin
  for i := 1 to KEY_LEN do begin
    letters[i] := 0;
    for j := 0 to N - 1 do
      t[i, j] := 0;
  end;

  pos := 0;
  while not Eof(f) do begin
    while not Eoln(f) do begin
      Read(f, c);
      c := UpCase(c);
      if c in ['A'..'Z'] then begin
        pos := pos mod KEY_LEN + 1;
        Inc(t[pos, Ord(c) - Ord('A')]);
        Inc(letters[pos]);
      end;
    end;
    if not Eof(f) then
      Readln(f);
  end;

  for i := 1 to KEY_LEN do
    for j := 0 to N - 1 do
      q[i][j] := t[i, j] / letters[i];
end;


function Chi2(var p, q: TDistrib; letters: longint): real;
{ oblicza stopien rozbie¿nosci rozk³adu q (wyznaczony na podstawie
  próbki letters-liter) od rozk³adu p przy pomocy testu "chi^2" }

var
  i, minI: integer;
  sumP, sumQ, minP, sum: real;
  flag: array [0..N-1] of boolean;
    { okre¶la, które litery (elementy rozk³adu) maj± byæ brane pod uwagê
      przy obliczaniu warto¶ci chi^2 }

begin
  sumP := 0; sumQ := 0;

  for i := 0 to N - 1 do
    if p[i] * letters >= CHI2_LIMIT then
      flag[i] := true
    else
      if (p[i] + sumP) * letters >= CHI2_LIMIT then begin
        { grupuje kilka liter w jedno zdarzenie, o prawdopodobieñstwie
          zaj¶cia równym sumie prawdopodobieñstw wyst±pienia liter, które
          siê na to zdarzenie sk³adaj± }
        flag[i] := true;
        p[i] := p[i] + sumP;
        q[i] := q[i] + sumQ;
        sumP := 0; sumQ := 0;
      end
      else begin
        { dok³ada kolejn± literê do grupy liter, których prawdopodobieñstwo
          jest zbyt ma³e, by stanowiæ odrebne zdarzenie w rozk³adzie }
        flag[i] := false;
        sumP := sumP + p[i];
        sumQ := sumQ + q[i];
      end;

  if (sumP > 0) or (sumQ > 0) then begin
    { zosta³a jeszcze grupa liter, dla których nie utworzono
      nowego zdarzenia }

    { znajduje w rozkladzie p spo¶ród pozosta³ych zdarzeñ (tzn. tych, dla
      których ustawiona jest flaga) zdarzenie o najmniejszym
      prawdopodobieñstwie... }
    minI := -1;
    for i := 0 to N - 1 do
      if flag[i] and ((minI = -1) or (p[i] < minP)) then begin
        minP := p[i];
        minI := i;
      end;

    { ... i do tego zdarzenia do³±cza wspomnian± wy¿ej grupê liter }

    if minI <> -1 then begin
      p[minI] := p[minI] + sumP;
      q[minI] := q[minI] + sumQ;
    end
    else begin
      { ... ale nie znaleziono takiego zdarzenia --- wszystkie
        maj± opuszczon± flagê, zatem tworzone jest jedno zdarzenie,
        odpowiadaj±ce wyst±pieniu jakiejkolwiek litery (jest to przypadek
        patologiczny, który mo¿e mieæ miejsce jedynie w przypadku bardzo
        ma³ej liczby próbek, tzn. ma³ej warto¶ci parametru letters) }
      flag[0] := true;
      p[0] := sumP;
      q[0] := sumQ;
    end;
  end;

  { oblicza chi2 }
  sum := 0;
  for i := 0 to N - 1 do
    if flag[i] then
      sum := sum + (q[i] - p[i]) / p[i] * (q[i] - p[i]) * letters;

  Chi2 := sum;
end;


function FindKey(pos: integer): integer;
{ zwraca warto¶æ pos-tej liczby z klucza, jakim zosta³a
  zaszyfrowana wej¶ciowa wiadomo¶æ }
var
  i: integer;
  shift, bestShift: integer;
  dist, bestDist: real;
  p1, q1: TDistrib;

begin
  bestShift := -1;
  for shift := 0 to N - 1 do begin
    for i := 0 to N-1 do begin
      p1[i] := p[i];
      q1[(i + shift) mod N] := q[pos][i];
    end;

    dist := Chi2(p1, q1, letters[pos]);

    if (bestShift = -1) or (dist < bestDist) then begin
      bestDist := dist;
      bestShift := shift;
    end;
  end;

  FindKey := (N - bestShift) mod N;
end;


procedure Decrypt(var fIn, fOut: text);
{ odszyfrowuje zawarto¶æ pliku fIn wed³ug klucza umieszczonego w tablicy key
  i wynik tej operacji zapisuje do pliku fOut }
var
  c: char;
  x, pos: integer;

begin
  pos := 0;
  while not Eof(fIn) do begin
    while not Eoln(fIn) do begin
      Read(fIn, c);
      if c in ['A'..'Z'] then begin
        pos := pos mod KEY_LEN + 1;
        x := Ord(c) - Ord('A');
        x := (x + N - key[pos]) mod N;
        c := Chr(x + Ord('A'));
      end;
      Write(fOut, c);
    end;
    if not Eof(fIn) then begin
      Readln(fIn);
      Writeln(fOut);
    end;
  end;
end;


function IntToStr(i: longint): string;
var
  s: string[11];
begin
  Str(i, s);
  IntToStr := s;
end;


var
  i: integer;
  test: integer; { numer testu }
  fIn, fTxt, fOut : text;

begin
  Write('Input test case number: ');
  Readln(test);

  Assign(fIn, 'cra' + IntToStr(test) + '.in');
  Assign(fTxt, 'cra' + IntToStr(test) + '.txt');
  Assign(fOut, 'cra' + IntToStr(test) + '.out');

  Reset(fTxt);
  GetDistrib(fTxt);
  Close(fTxt);

  Reset(fIn);
  GetDistribs(fIn);
  Close(fIn);

  for i := 1 to KEY_LEN do begin
    key[i] := FindKey(i);
    Writeln('Key[', i, '] = ', key[i]);
  end;

  Reset(fIn);
  Rewrite(fOut);
  Decrypt(fIn, fOut);
  Close(fIn);
  Close(fOut);
end.
