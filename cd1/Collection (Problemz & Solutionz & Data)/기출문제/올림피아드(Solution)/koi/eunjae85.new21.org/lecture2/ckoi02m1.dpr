program koi02_m1;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  maxn = 1000;
  infile = 'music.in';
  outfile = 'music.out';

var
  i, j, k, n, m, cnt : integer;
  order : array[0..maxn + 1, 0..maxn + 1] of boolean;
  flag : array[0..maxn + 1] of boolean;
  solution : array[0..maxn + 1] of integer;

procedure input;
var
  inf : text;
  cnt, a, b : integer;
begin

  assign(inf, infile);
  reset(inf);
  readln(inf, n, m);
  for i := 1 to m do begin
    read(inf, cnt);
    a := -1;  b := -1;
    for j := 1 to cnt do begin
      read(inf, k);
      a := b;  b := k;
      if (a <> -1) and (b <> -1) then order[a, b] := true;
    end;
  end;
  close(inf);

end;

procedure dfs(now : integer);
var
  i : integer;
begin

  if flag[now] then exit;

  flag[now] := true;

  for i := 1 to n do
    if order[i, now] then dfs(i);

  inc(cnt);
  solution[cnt] := now;

end;

procedure process;
begin

  for i := 1 to n do
    dfs(i);

end;

procedure output;
var
  outf : text;
begin

  assign(outf, outfile);
  rewrite(outf);
  for i := 1 to n do
    writeln(outf, solution[i]);
  close(outf);

end;

begin

  input;
  process;
  output;

end.
