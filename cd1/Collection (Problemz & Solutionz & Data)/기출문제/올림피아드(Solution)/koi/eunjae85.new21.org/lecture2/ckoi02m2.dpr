program koi02_m2;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  maxn = 100;
  maxt = 10000;
  infile = 'coin.in';
  outfile = 'coin.out';

var
  n, t : integer;
  price, num : array[0..maxn + 1] of integer;
  c1, c2 : array[0..maxt + 1, 0..maxn + 1] of integer;

procedure input;
var
  inf : text;
  i : integer;
begin

  assign(inf, infile);
  reset(inf);
  readln(inf, t);
  readln(inf, n);
  for i := 1 to n do begin
    readln(inf, price[i], num[i]);
  end;
  close(inf);

end;

procedure dynamic;
var
  i, j, k : integer;
begin

  for i := 1 to t do
    c2[0, i] := 1;

  for i := 1 to n do begin
    for j := price[i] to t do begin

      k := j - (num[i] + 1)*price[i];
      if k < 1 then k := 0
      else k := c2[i - 1, k];

      c1[i, j] := c2[i - 1, j] - k;

      k := j - price[i];
      if k < 1 then k := 0
      else k := c2[i, k];
      c2[i, j] := c1[i, j] + k;

    end;
  end;

end;

procedure output;
var
  outf : text;
begin

  assign(outf, outfile);
  rewrite(outf);
  writeln(outf, c1[n, t]);
  close(outf);

end;

begin

  input;
  dynamic;
  output;

end.
