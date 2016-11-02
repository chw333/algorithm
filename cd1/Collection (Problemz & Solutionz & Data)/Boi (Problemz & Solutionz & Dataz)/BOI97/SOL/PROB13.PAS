var n:extended;

procedure readdata;
var f:text;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
end;

procedure solve;
var lo,hi:extended;
    i:word;
    r:extended;
    f:text;
    lr,hr:word;
begin
  assign(f,'output.txt');
  rewrite(f);

  lo:=(n-1)*ln(10);
  hi:=n*ln(10);  {lo <= r < hi}
  i:=1;
  r:=0;
  while r<lo do begin
    inc(i);
    r:=r+ln(i);
  end;
  if r>=hi then begin writeln(f,'NO'); close(f); exit; end;
  lr:=i;
  while r<hi do begin
    inc(i);
    r:=r+ln(i);
  end;
  hr:=i-1;

  writeln(f,hr-lr+1);
  for i:=lr to hr do
    writeln(f,i);

  close(f);
end;

begin
  readdata;
  solve;
end.
