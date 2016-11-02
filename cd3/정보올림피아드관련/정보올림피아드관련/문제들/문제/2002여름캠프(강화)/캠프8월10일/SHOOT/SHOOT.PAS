uses crt;
var redovi, sol : array[1..1000] of integer;
    used : array[1..1000] of boolean;
    kolone : array[1..1000, 1..2] of integer;
    i, j, r, k, n, a, b : integer;
    f, fout : text;

procedure printout (w : boolean);
var i : integer;
begin
  if w=False then writeln (fout, 'NO')
             else
             begin
             for i:=1 to k do write (fout, sol[i], ' ');
             writeln (fout);
             end;
end;

function solve : boolean;
var i, j, min, taj : integer;
begin
  for j:=1 to r do
      begin
      min:=32767;
      for i:=1 to r do
          if redovi[i]<min then
             begin
             min:=redovi[i];
             taj:=i;
             end;

      i:=1; while (i<=k) and
                  ((used[i]) or
                   (kolone[i, 1]<>taj) and (kolone[i, 2]<>taj)) do inc (i);

      if i>k then begin solve:=False; exit; end
             else begin
                  used[i]:=True;
                  dec (redovi[kolone[i, 1]]);
                  dec (redovi[kolone[i, 2]]);
                  redovi[taj]:=32767;
                  sol[i]:=taj;
                  end;
       end;

  for i:=1 to k do
      if not used[i] then
         sol[i]:=kolone[i, 1];

  solve:=True;
end;

begin
  assign (f, 'SHO.IN'); reset (f);
  assign (fout, 'SHO.OUT'); rewrite (fout);

  read (f, n);

  for i:=1 to n do
      begin
      read (f, r, k);
      for j:=1 to r do begin used[j]:=False; redovi[j]:=0; end;

      for j:=1 to k do
          begin
          read (f, a, b); kolone[j, 1]:=a; kolone[j, 2]:=b;
          inc (redovi[a]); inc (redovi[b]);
          end;

      printout (solve);
      end;

  close (fout);
end.


