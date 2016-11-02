program koi02_h1;
{$APPTYPE CONSOLE}
uses
  SysUtils;

const
  maxn = 1000;
  no = -1000000;
  infile = 'path.in';
  outfile = 'path.out';

var
  n : integer;
  data : array[0..maxn + 1, 0..maxn + 1] of longint;
  c : array[0..maxn + 1, 0..maxn + 1, 1..3] of longint;

procedure input;
var
  inf : text;
  i, j : integer;
begin

  assign(inf, infile);
  reset(inf);
  readln(inf, n);
  for i := 1 to n do
    for j := 1 to n do
      read(inf, data[i, j]);
  close(inf);

end;

function fmax2(a, b, c : longint) : longint;
begin

  if (a >= b) and (a >= c) then fmax2 := a
  else if (b >= c) and (b >= a) then fmax2 := b
  else fmax2 := c;

end;

function fmax(a, b : longint) : longint;
begin

  if a > b then fmax := a
  else fmax := b;

end;

procedure dynamic;
var
  i, j, k : integer;
begin

  for i := 1 to n do begin
    for j := 1 to n do begin
      if i = 1 then c[i, j, 1] := data[i, j]
      else c[i, j, 1] := fmax2(c[i - 1, j, 1], c[i - 1, j, 2], c[i - 1, j, 3]) + data[i, j];
      if j = 1 then c[i, j, 2] := no
      else c[i, j, 2] := fmax(c[i, j - 1, 1], c[i, j - 1, 2]) + data[i, j];
    end;

    for j := n downto 1 do begin
      if (j = n) or (i = 1) then c[i, j, 3] := no
      else c[i, j, 3] := fmax(c[i, j + 1, 1], c[i, j + 1, 3]) + data[i, j];
    end;
  end;

end;

procedure output;
var
  outf : text;
begin

  assign(outf, outfile);
  rewrite(outf);
  writeln(outf, fmax2(c[n, n, 1], c[n, n, 2], c[n, n, 3]));
  close(outf);

end;

begin

  input;
  dynamic;
  output;

end.
