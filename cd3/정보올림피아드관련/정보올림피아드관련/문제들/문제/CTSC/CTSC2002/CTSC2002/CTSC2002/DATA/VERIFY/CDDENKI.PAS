{Denki Block -- Data Checker  by Rujia Liu}
const
  infile='denki.in';
  outfile='denki.out';
  ch:array[0..1] of char=(' ',#219);
var
  map:Array[1..20,1..20] of integer;
  x,y:array[1..20] of integer;
  i,j,n:integer;
begin
  write('File ',infile,' -- ');
  assign(input,infile);
  reset(input);
  read(n);
  if (n<2)or(n>20) then halt;
  for i:=1 to n do
  begin
    read(x[i],y[i]);
    if (x[i]<-9)or(x[i]>9)or(y[i]<-9)or(y[i]>9)or(x[i] mod 2=0)or(y[i] mod 2=0) then halt;
  end;
  for i:=1 to n-1 do
    if (x[i]>x[i+1])or((x[i]=x[i+1])and(y[i]>=y[i+1])) then halt;
  fillchar(map,sizeof(map),0);
  for i:=1 to n do
  begin
    read(x[i],y[i]);
    if (x[i]<0)or(y[i]<0) then halt;
    map[x[i],y[i]]:=1;
  end;
  writeln('Ok');
  writeln('The Object:');
  for i:=1 to n do
  begin
    for j:=1 to n do
      write(ch[map[i,j]]);
    writeln;
  end;
end.
