{$R-,Q-,S-,B-}
uses funit;
var i,j,n:integer;
    f:array[1..4,1..4,1..4,1..4]of shortint;
    list,d:array[1..4]of integer;
procedure sort;
  var i,j:integer;
  begin
    for i:=1 to 4 do begin
      d[i]:=1;
      for j:=1 to 4 do if list[j]<list[i] then begin
        inc(d[i]);
      end;
    end;
  end;
begin
  assign(input,'newfun.in');
  reset(input);
  assign(output,'newfun.out');
  rewrite(output);
  readln(n);
  fillchar(f,sizeof(f),0);
  for i:=1 to n do begin
    readln(list[1],list[2],list[3],list[4]);
    sort;
    if f[d[1],d[2],d[3],d[4]]>0
       then writeln(list[f[d[1],d[2],d[3],d[4]]])
       else begin
              f[d[1],d[2],d[3],d[4]]:=fun(d[1],d[2],d[3],d[4]);
              for j:=1 to 4 do if d[j]=f[d[1],d[2],d[3],d[4]] then begin
                f[d[1],d[2],d[3],d[4]]:=j;
                break;
              end;
              writeln(list[f[d[1],d[2],d[3],d[4]]]);
            end;
  end;
  close(input);
  close(output);
end.