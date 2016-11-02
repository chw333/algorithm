program day2_problem2;

var
  n                : byte;
  a                : array [1..32,1..32] of boolean;
  d                : array [1..32,1..32] of word;
  len              : byte;
  r                : array [1..20] of byte;
  free,used        : array [1..20] of boolean;
  p                : byte;
  ans              : array [1..400] of word;
  x,pp             : word;

procedure read_data;
var
  f                : text;
  i,j              : byte;
  k                : integer;
begin
  assign(f,'input.txt'); reset(f);
  readln(f,n);
  for i:=1 to n do
    begin
      for j:=1 to n do
        begin
          read(f,k);
          a[i,j]:=k<>0;
        end;
      readln(f);
    end;
  close(f);
end;

procedure refresh;
var
  i                : byte;
begin
  for i:=1 to len-1 do
    inc(d[r[i],r[i+1]]);
  inc(d[r[len],r[1]]);
end;

procedure dfs(k:byte);
var
  i                : byte;
begin
  inc(len); r[len]:=k; used[k]:=true;
  for i:=1 to n do
    if a[k,i] then
      if i=p then
        if len>2 then refresh else
      else
        if not used[i] and free[i] then dfs(i);
  dec(len); used[k]:=false;
end;

procedure start;
var
  i                : byte;
begin
  fillchar(free,n,true);
  fillchar(d,sizeof(d),0);
  for p:=1 to n do
    begin
      len:=1; r[1]:=p;
      fillchar(used,n,false);
      used[p]:=true;
      for i:=1 to n do
        if a[p,i] and free[i] then dfs(i);
      free[p]:=false;
    end;
end;

procedure quicksort(k,l:word);
var
  i,j              : word;
begin
  i:=k; j:=l; x:=ans[(i+j) div 2];
  repeat
    while ans[i]<x do inc(i);
    while ans[j]>x do dec(j);
    if i<=j then
      begin
        pp:=ans[i]; ans[i]:=ans[j]; ans[j]:=pp;
        inc(i); dec(j);
      end;
  until i>j;
  if k<j then quicksort(k,j);
  if i<l then quicksort(i,l);
end;

procedure write_result;
var
  f                : text;
  br               : word;
  i,j              : word;
begin
  assign(f,'output.txt'); rewrite(f);
  br:=0;
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if d[i,j]>0 then
        begin
          inc(br);
          ans[br]:=d[i,j];
        end;
  if br=0 then writeln(f,'NO CYCLE') else
    begin
      quicksort(1,br);
      writeln(f,br);
      for i:=1 to br do write(f,ans[i],' ');
      writeln(f);
    end;
  close(f);
end;

begin
  read_data;
  start;
  write_result;
end.