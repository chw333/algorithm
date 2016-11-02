{Toy Soldiers -- Data Checker, by Rujia Liu}
const
  infile='toy.in';
  outfile='toy.out';
var
  m,n,k,i,j,t,r,x,y,tot:integer;
begin
  write('File ',infile,' -- ');
  assign(input,infile);
  reset(input);
  readln(m,n,k,t);
  for i:=1 to 2*k+1 do
  begin
    read(x,y);
    if (x<1)or(x>m)or(y<1)or(y>n) then halt;
  end;
  tot:=0;
  for i:=1 to t do
  begin
    read(x,y,r);
    tot:=tot+r;
    if (x<1)or(x>m)or(y<1)or(y>n) then halt;
  end;
  if tot<>2*k+1 then halt;
  for i:=1 to m do
    for j:=1 to n do
    begin
      read(x);
      if (x<1)or(x>100) then halt;
    end;
  writeln('Ok');
end.