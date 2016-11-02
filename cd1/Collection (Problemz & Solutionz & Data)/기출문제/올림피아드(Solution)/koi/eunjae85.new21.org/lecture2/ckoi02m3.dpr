program koi02_m3;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  maxn = 1000;
  infile = 'dna.in';
  outfile = 'dna.out';

type
  tq = record
    a, b : integer;
  end;

var
  i, j, n1, n2, k, answer : integer;
  data1, data2 : array[0..maxn + 1] of char;
  c : array[0..maxn + 1, 0..maxn + 1] of integer;

  q : array[0..maxn*maxn + 1] of tq;
  flag : array[0..maxn + 1, 0..maxn + 1] of boolean;
  front, rear : integer;

  chk : array[0..maxn + 1] of char;

procedure input;
var
  inf : text;
  i : integer;
begin

  assign(inf, infile);
  reset(inf);
  readln(inf, k);
  readln(inf, n1);
  for i := 1 to n1 do read(inf, data1[n1 - i + 1]);
  readln(inf, n2);
  for i := 1 to n2 do read(inf, data2[n2 - i + 1]);
  close(inf);

end;

function fmax(a, b : integer) : integer;
begin

  if a > b then fmax := a
  else fmax := b;

end;

procedure dynamic;
var
  i, j, l1, l2, v : integer;
begin

  for i := 1 to n1 do
    for j := 1 to n2 do begin

      if data1[i] <> data2[j] then begin

        c[i, j] := fmax(c[i - 1, j], c[i, j - 1]);

      end else begin

        v := 0;

        for l1 := fmax(1, i - k - 1) to i - 1 do
          for l2 := fmax(1, j - k - 1) to j - 1 do begin
            if data1[l1] = data2[l2] then begin
              if c[l1, l2] > v then
                v := c[l1, l2];
            end;
          end;

        if c[i, j] < v + 1 then
          c[i, j] := v + 1;

      end;

      if c[i, j] > answer then
        answer := c[i, j];

    end;

end;

procedure output;
var
  outf : text;
begin

  assign(outf, outfile);
  rewrite(outf);
  for i := answer downto 1 do
    write(outf, chk[i]);
  close(outf);

end;

procedure backtrace;
var
  a, b, v : integer;
begin

  for i := 1 to answer do
    chk[i] := 'Z';

  front := 1;  rear := 0;
  for i := 1 to n1 do
    for j := 1 to n2 do
      if (flag[i, j] = false) and (c[i, j] = answer) and (data1[i] = data2[j]) and (chk[answer] > data1[i]) then
        chk[answer] := data1[i];

  for i := 1 to n1 do
    for j := 1 to n2 do
      if (flag[i, j] = false) and (c[i, j] = answer) and (data1[i] = data2[j]) then
        if data1[i] = chk[answer] then begin
          inc(rear);
          q[rear].a := i;
          q[rear].b := j;
          flag[i, j] := true;
        end;


  repeat

    a := q[front].a;
    b := q[front].b;
    v := c[a, b];

    if data1[a] <> chk[v] then begin
      inc(front);
      continue;
    end;

    for i := fmax(1, a - k - 1) to a - 1 do
      for j := fmax(1, b - k - 1) to b - 1 do
        if (flag[i, j] = false) and (data1[i] = data2[j]) and (c[i, j] + 1 = v) and (chk[v - 1] > data1[i]) then
          chk[v - 1] := data1[i];

    for i := fmax(1, a - k - 1) to a - 1 do
      for j := fmax(1, b - k - 1) to b - 1 do
        if (flag[i, j] = false) and (data1[i] = data2[j]) and (c[i, j] + 1 = v) and (chk[v - 1] = data1[i]) then begin
          inc(rear);
          q[rear].a := i;
          q[rear].b := j;
          flag[i, j] := true;
        end;

    inc(front);

  until front > rear;

end;

begin

  input;
  dynamic;
  backtrace;
  output;

end.
