program koi02_h2;
{$APPTYPE CONSOLE}
uses
  SysUtils;

const
  maxn = 1000;
  infile = 'hel.in';
  outfile = 'hel.out';

type
  xy = record
    x, y : longint;
  end;
  xy2 = record
    x, y : real;
  end;

var
  n, cnt : integer;
  data : array[0..maxn + 1] of xy;
  convex : array[0..maxn + 1] of xy;

  answer : real;
  ans : xy2;

procedure swap_xy(var i, j : xy);
var
  k : xy;
begin

  k := i;  i := j;  j := k;

end;

procedure input;
var
  inf : text;
  i, min, index : integer;
begin

  min := maxlongint;
  assign(inf, infile);
  reset(inf);
  readln(inf, n);
  for i := 1 to n do begin
    readln(inf, data[i].x, data[i].y);
    if data[i].y < min then begin
      min := data[i].y;
      index := i;
    end;
  end;
  close(inf);

  swap_xy(data[1], data[index]);

  answer := maxlongint;

end;

function left(a, b, c : xy) : boolean;
begin

  left := a.x*(b.y - c.y) + b.x*(-a.y + c.y) + c.x*(a.y - b.y) > 0;

end;

procedure convex_hull;
var
  i, now, next, temp : integer;
  flag : array[0..maxn + 1] of boolean;
begin

  for i := 1 to n do flag[i] := false;
  cnt := 1;
  convex[cnt] := data[1];
  now := 1;

  repeat
    for next := 1 to n do begin
      if flag[next] then continue;
      if (cnt < 2) and (next = 1) then continue;
      break;
    end;
    for temp := 1 to n do begin
      if flag[next] then continue;
      if (cnt < 2) and (temp = 1) then continue;
      if left(data[now], data[next], data[temp]) then
        next := temp;
    end;
    if next = 1 then break;
    inc(cnt);
    convex[cnt] := data[next];
    flag[next] := true;
    now := next;
  until false;

end;

function dist(x1, y1, x2, y2 : real) : real;
begin

  dist := sqrt(sqr(x2 - x1) + sqr(y2 - y1));

end;

function check(x, y, r : real) : boolean;
var
  i : integer;
  tx, ty : real;
begin

  for i := 1 to n do begin
    tx := data[i].x;
    ty := data[i].y;
    if dist(tx, ty, x, y) > r then begin
      check := false;
      exit;
    end;
  end;

  check := true;

end;

procedure with2(i, j : integer);
var
  p1, p2, center : xy2;
  r : real;
begin

  p1.x := convex[i].x;
  p1.y := convex[i].y;
  p2.x := convex[j].x;
  p2.y := convex[j].y;

  center.x := (p1.x + p2.x)/2;
  center.y := (p1.y + p2.y)/2;

  r := dist(p1.x, p1.y, center.x, center.y);

  if check(center.x, center.y, r) then begin
    if answer > r then begin
      answer := r;
      ans.x := center.x;
      ans.y := center.y;
    end;
  end;

end;

procedure with3(i, j, k : integer);
var
  x1, x2, x3, y1, y2, y3, r : real;
  center : xy2;
begin

  x1 := convex[i].x;  y1 := convex[i].y;
  x2 := convex[j].x;  y2 := convex[j].y;
  x3 := convex[k].x;  y3 := convex[k].y;

  center.x := -((x2*x2 - x1*x1 + y2*y2 - y1*y1)*(y3 - y2) - (x2*x2 - x3*x3 + y2*y2 - y3*y3)*(y1 - y2))/
               (2*(x1 - x2)*(y3 - y2) - 2*(x3 - x2)*(y1 - y2));
  center.y := -((y2*y2 - y1*y1 + x2*x2 - x1*x1)*(x3 - x2) - (y2*y2 - y3*y3 + x2*x2 - x3*x3)*(x1 - x2))/
               (2*(y1 - y2)*(x3 - x2) - 2*(y3 - y2)*(x1 - x2));

  r := dist(x1, y1, center.x, center.y);

  if check(center.x, center.y, r) then begin
    if answer > r then begin
      answer := r;
      ans.x := center.x;
      ans.y := center.y;
    end;
  end;

end;

procedure process;
var
  i, j, k : integer;
begin

  for i := 1 to cnt do
    for j := i + 1 to cnt do begin
      with2(i, j);
      for k := j + 1 to cnt do begin
        with3(i, j, k);
      end;
    end;

end;

procedure output;
var
  outf : text;
begin

  assign(outf, outfile);
  rewrite(outf);
  writeln(outf, answer:1:3);
  writeln(outf, ans.x:1:3, ' ', ans.y:1:3);
  close(outf);

end;

begin

  input;
  convex_hull;
  process;
  output;

end.
