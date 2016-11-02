{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи "ТАБЛИЧНЫЙ ПРОЦЕССОР"}

{$A-,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}

Program TABLE;
const MaxM = 100;
      MaxN = 100;

var inf, ouf: TEXT;
    Size: array [1..MaxM] of integer; {ширины столбцов}

function compress (s: string): string;
var i, j: integer;
begin
   i := 1; while (i <= length (s)) and (s [i] = ' ') do inc (i);
   j := length (s);
   while (j >= i) and (s [j] = ' ') do dec (j);
   compress := copy (s, i, j-i+1);
end;

procedure Split (s: string; c: char; var s1, s2: string);
var i, j: integer;
begin
   i := 1;
   j := i; while (j <= length (s)) and (s [j] <> c) do inc (j);
   s1 := compress (copy (s, i, j-i));
   s2 := compress (copy (s, j+1, length (s)-j));
end;

procedure DrawLine (M: integer; Left, Middle, Right: char);
var i, k: integer;
begin
   write (ouf, Left);
   for i := 1 to M do
   begin
      for k := 1 to Size [i] do write (ouf, '─');
      if i = M then writeln (ouf, Right) else write (ouf, Middle);
   end;
end;

var nest, help: string;
    i, k, M: integer; {количество строк и стоблцов}

BEGIN
   assign (inf, 'INPUT.TXT'); reset (inf);
   assign (ouf, 'OUTPUT.TXT'); rewrite (ouf);
   readln (inf, help);
   for i := 1 to MaxM do Size [i] := -1;

   repeat
      readln (inf, help);
      help := compress (help);
      case help [1] of
         '└': break; {выходим из цикла}
         '├':      ; {Ничего не делаем, пропускаем горизонтальную линию}
         '│': begin  {Поехали сканировать очередную строку}
                 delete (help, 1, 1);
                 i := 0;
                 repeat
                    split (help, '│', nest, help); inc (i);
                    if Size [i] < length (nest) + 2 then
                       Size [i] := length (nest) + 2;
                 until help = '';
                 M := i;
              end;
      end;
   until false;

   RESET (inf);
   readln (inf, help);
   DrawLine (M, '┌', '┬', '┐'); {Верхняя линия}

   repeat
      readln (inf, help);
      help := compress (help);
      case help [1] of
         '└': break; {выходим из цикла}
         '├': DrawLine (M, '├', '┼', '┤'); {Рисуем горизонтальный разделитель}
         '│': begin  {Поехали сканировать очередную строку}
                 delete (help, 1, 1);
                 i := 0;
                 repeat
                    write (ouf, '│ ');
                    split (help, '│', nest, help); inc (i);
                    write (ouf, nest);
                    for k := 1 to Size [i]-length(nest)-1 do write (ouf, ' ');
                 until help = '';
                 writeln (ouf, '│');
              end;
      end;
   until false;

   DrawLine (M, '└', '┴', '┘'); {Верхняя линия}
   close (ouf);
END.
            ┌─┬─┐
            ├─┼─┤
            └─┴─┘
