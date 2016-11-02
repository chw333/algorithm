{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи "СЛУЧАЙНЫЙ НОМЕР"}

{$A-,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}

program NUMBER;

const Digits = 30;
      O = 10000;
      Decimal = 4;
      MaxN = 200;
      MaxM = 200;

type long = record
                D: integer; {максимальная ненулевая степень}
                Num: array [0..Digits] of word;
            end;

procedure error (msg: string);
begin
   writeln (#7, msg);
   HALT
end;

function max (a, b: integer): integer;
begin
   if a < b then  max := b else max := a
end;

(* ==================================================== *)
(* ДЛИННАЯ АРИФМЕТИКА                                   *)
(* ==================================================== *)

procedure SetInt (var a: long; x: integer);
begin
   a.D := 0; a.Num [0] := x;
end;

procedure Add (var x, y, res: long);
var carry: word;
    i: integer;
begin
   carry := 0; i := 0;
   repeat
      if i <= x.D then inc (carry, x.Num [i]);
      if i <= y.D then inc (carry, y.Num [i]);
      res.Num [i] := carry mod O;
      carry := carry div O;
      inc (i);
   until (carry = 0) and (i>x.D) and (i>y.D);
   dec (i);
   res.D := i;
end;

procedure Sub (var x, y, res: long);
var carry: word;
    i: integer;
begin
   carry := 1; i := 0;
   repeat
      if i <= x.D then inc (carry, x.Num [i]);
      if i <= y.D then inc (carry, O - 1 - y.Num [i])
                  else inc (carry, O - 1);
      res.Num [i] := carry mod O;
      carry := carry div O;
      inc (i);
   until (carry = 1) and (i>x.D) and (i>y.D);
   dec (i);

   while (i>0) and (res.Num [i] = 0) do dec (i);
   res.D := i;
end;

procedure Div2 (var a, res: long);
var i: integer;
    carry: word;
begin
   carry := 0;
   for i := a.D downto 0 do
   begin
      carry := carry * O + a.Num [i];
      res.Num [i] := carry div 2;
      carry := carry mod 2
   end;
   i := a.D;
   while (i>0) and (res.Num [i] = 0) do dec (i);
   res.D := i;
end;

function cmp (var x, y: long): integer;
var i: integer;
begin
   if x.D > y.D then cmp := 1
   else if x.D < y.D then cmp := -1
   else begin
           for i := x.D downto 0 do
                if x.Num [i] > y.Num [i] then begin cmp := 1; exit end
                else if x.Num [i] < y.Num [i] then begin cmp := -1; exit end;
           cmp := 0;
   end;
end;

procedure WriteLong (var x: long);
var i: integer;
    help: string;
begin
   for i := x.D downto 0 do
   begin
      Str (x.Num [i], help); while length (help) <> Decimal do help := '0'+help;
      write (help);
   end;
end;

(* =========================================================== *)
(* ОСНОВНАЯ ПРОГРАММА                                          *)
(* =========================================================== *)

Var Bellman: array [1..MaxM] of long;
    M, N: integer;
    Long_1, A, B, T, Number, Sum: long; {Общее количество}
    cur, i, j: integer;
    c: char;

    inf, ouf: TEXT;
BEGIN
   assign (inf, 'INPUT.TXT'); reset (inf);
   assign (ouf, 'OUTPUT.TXT'); rewrite (ouf);
   readln (inf, M, N);

   SetInt (Long_1, 1);

   (* 1. Вычисляем общее количество (T) проходом назад *)

   for j := N to M do SetInt (Bellman [j], 1);
   for i := N-1 downto 1 do {по строкам}
   begin
      SetInt (Bellman [i], 0);
      for j := M-1 downto i do {по столбцам}
        Add (Bellman [j], Bellman [j+1], Bellman [j]);
   end;
   SetInt (T, 0);
   for j := 1 to M do Add (T, Bellman [j], T);

   (* 2. Находим искомый номер *)

   SetInt (A, 1);
   SetInt (B, 0); Add (B, T, B); {A и B - границы для поиска номера}
   repeat read (inf, c); until c = '.'; read (inf, c);
   while ( (c = '0') or (c = '1')) and (cmp (A, B) <> 0) do
   begin
      if c = '0' then begin Add (A, B, B); Div2 (B, B) end
                 else begin Add (A, B, A); Div2 (A, A); Add (A, Long_1, A) end;
      read (inf, c)
   end;
   SetInt (Number, 0); Add (Number, A, Number); {Нашли номер}

   (* 3. Бежим теперь вперед и печатаем последовательность *)

   cur := 1;

   for i := 1 to N do
   begin
      SetInt (Sum, 0); {Сумма снизу}
      dec (cur);
      while cmp (Number, Sum) = 1 do
      begin
         cur := cur+1;
         Add (Sum, Bellman [cur], Sum)
      end;
      writeln (ouf, cur);
      Sub (Sum, Bellman [cur], Sum);
      Sub (Number, Sum, Number);
      {пересчитываем Беллмана}
      for j := i to M-1 do Sub (Bellman [j], Bellman [j+1], Bellman [j]);
   end;

   close (ouf);
end.