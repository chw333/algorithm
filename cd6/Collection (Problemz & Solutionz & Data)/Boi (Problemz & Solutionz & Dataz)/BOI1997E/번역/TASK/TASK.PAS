type
  TZav = array[1..200, 1..200] of boolean;

const
  infile='task05.in';
  outfile='task05.out';

var
  zav: TZav;
  n: byte;

procedure init;
var
  kol, br: longint;
  kod1, kod2: byte;
  f: text;
begin
  assign(f, infile);
  reset(f);
  read(f, n);
  for kol := 1 to n do
    for br := 1 to n do
      zav[kol, br] := false;
  read(f, kol);
  for br := 1 to kol do
    begin
      read(f, kod1, kod2);
      zav[kod2, kod1] := true;
    end;
  close(f);
end;

procedure run;
var
  br, brp, brk, kon, iter, min: word;
  niza, np: array[1..200] of boolean;
  kat, brzad: array[1..200] of byte;
  dali, mozno: boolean;
  f: text;
begin
  for br := 1 to n do
    begin
      niza[br] := false;
      brzad[br] := 0;
    end;
  kon := 0;
  iter := 0;
  while kon < n do
    begin
      inc(iter);
      for br := 1 to n do
        np[br] := false;
      for br := 1 to n do
        if not niza[br] then
          begin
            dali := false;
            for brp := 1 to n do
              if zav[br, brp] and (not niza[brp]) then
                dali := true;
            if not dali then
              begin
                np[br] := true;
                inc(kon);
                kat[br] := iter;
                inc(brzad[iter]);
              end;
          end;
      for br := 1 to n do
        if np[br] then niza[br] := true;
    end;
  min := n div iter + 1;
  mozno := true;
  while mozno do
    begin
      mozno := false;
      br := 1;
      brp := 0;
      for brk := 1 to iter do
        if brZad[brk] > brp then
          begin
            brp := brZad[brk];
            br := brk;
          end;
      for brk := 1 to n do
        if kat[brk] = br then
          begin

          end;
    end;
  assign(f, outfile);
  rewrite(f);
  writeln(f, iter, ' ', min);
  close(f);
end;

begin
  init;
  run;
end.