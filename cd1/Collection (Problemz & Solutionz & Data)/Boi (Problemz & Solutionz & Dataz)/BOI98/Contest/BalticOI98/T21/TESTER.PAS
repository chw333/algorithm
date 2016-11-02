{$A+,B-,D+,E-,F-,G-,I+,L+,N-,O-,P+,Q+,R+,S+,T+,V+,X+}
{$M 65520,0,655360}

program tester;
  const max_v = 100;
        max_b = 3000;
  type grafas = array [1.. max_v, 1..max_v] of integer;
       kelias = array [1..2 * max_b] of integer;
       laipsniai = array [1..max_v] of integer;
       aibe = set of 1..255;
  var gr, g : grafas;
      k : kelias;
      l : laipsniai;
      ex : aibe;
      n, b : integer; { tiek briaun— ir virž–ni— turi grafas }
      st, s : string [5];
      ats : kelias;

procedure stop (i, v1, v2 : integer);
begin
  if i <> 1
     then writeln ('Incorrect.');
  case i of
   1 : writeln ('Correct.');
   2 : writeln ('The correct output is: NO');
   3 : writeln ('The covering should be started from an entrance, not from room ', v1);
   4 : writeln ('You are trying to cover an unexiting passage: ', v1, ' ',v2);
   5 : writeln ('There is no room nb, ', v1);
   6 : writeln ('The covering should be ended at exit, not at room ', v1);
   7 : writeln ('The passage ', v1, ' ', v2, ' has already been covered.');
   8 : writeln ('Another mistake at ', v1, ' ', v2);
   9 : writeln ('The solution exists');
   10 : writeln ('The passage ', v1, ' ', v2, ' has not been covered.');
  end;
  halt (1);
end;


  var f : text;
      ii, jj, e, i, j, nr, a, br, v1, v2 : integer;
      galima : boolean;
      nel : aibe;
begin
  { nuskaitomas grafas is pradiniu duomenu failo }
  assign (f, 'FLOOR.IN');
  {$I+}
  reset (f);
  if ioresult<>0 then  begin
    writeln('unable to open floor.in');
  end;
  {$I-}
  readln (f, n, b, e);
  { perskaitomi isejimai }
  ex := [];
  for i := 1 to e do
    begin
      read (f, nr);
      ex := ex + [nr];
    end;
  { visas grafas }
  for i := 1 to n do
    begin
      for j := 1 to n do
        g[i, j] := 0;
      l[i] := 0;
    end;
  for i := 1 to b do
    begin
      readln (f, a, br);
      g[a, br] := g[a, br] + 1;
      g[br, a] := g[br, a] + 1;
      l[br] := l[br] + 1;
      l[a] := l[a] + 1;
    end;
  close (f);
  { surandame nelyginio laipsnio virž–nes }
  galima := true; { ar galima apeiti }
  nel := [];
  for i := 1 to n do
    if l[i] mod 2 <> 0
       then if i in ex
               then nel := nel + [i]
               else galima := false;

  assign (f, 'FLOOR.OUT');
  {$I-}
  reset (f);
  if ioresult<>0 then begin
    writeln('no output file');
  end;
  {$I+}
  gr := g;
  { tikrinama, ar atsakymas nebus NO }
  readln (f, st);
  s := st[1] + st[2];
  if s = 'NO'
    then if not galima
            then stop (1, 0, 0)
            else stop (9, 0, 0);
   { atidaromas is naujo }
   close (f);
   reset (f);

   { perskaitomas gautas failas }
   i := 0;
   while not eof (f) do
     begin
       i := i +1;
       readln (f, ats[i]);
       if (ats[i] < 1) or (ats[i] > n)
          then stop (5, ats[i], 0);
     end;
   close (f);
   { tikrinami, ar teisingi pradiniai ir galiniai kambariai }
   if not (ats[1] in ex)
      then stop (3, 1, 0)
      else if not (ats[i] in ex)
              then stop (6, ats[i], 0);
   for j := 1 to i - 1 do
     begin
       v1 := ats[j]; v2 := ats[j + 1];
       if gr [v1, v2] > 0
          then begin
                 gr[v1, v2] := gr[v1, v2] - 1;
                 gr[v2, v1] := gr[v2, v1] - 1;
                 l[v1] := l[v1] - 1;
                 l[v2] := l[v2] - 1;
               end
          else if (v1 in ex) and (v2 in ex)
                  then { ok }
          else if (g[v1, v2] = 0)
                  then stop (4, v1, v2)
          else if (g[v1, v2] > 0)
                  then stop (7, v1, v2)
          else stop (8, v1, v2);
      end;
  for ii := 1 to n do
    for jj := 1 to n do
       if gr[ii, jj] > 0
          then stop (10, ii, jj);
  stop (1, 0, 0);
end.




