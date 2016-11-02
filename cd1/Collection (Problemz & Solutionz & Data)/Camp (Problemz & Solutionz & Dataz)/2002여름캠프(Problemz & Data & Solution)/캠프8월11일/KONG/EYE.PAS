{Programed by Grant Guo, Email: grantguo@iname.com}
Var
  Graph:Array[1..200,1..200]of shortint;
  High:Array[1..200]of Integer;
  Mark:Array[1..200]of Boolean;
  n:byte;
procedure init;
  var a,b,l:Byte;
      i,s:Integer;
  Begin
    assign(input,'eye.inp');
    reset(input);
    readln(s);
    fillchar(graph,sizeof(graph),0);
    n:=0;
    for i:=1 to s do begin
      readln(a,b,l);
      graph[a,b]:=l;
      graph[b,a]:=-l;
      if a>n then n:=a;
      if b>n then n:=b;
    end;
    close(input);
  End;
procedure dfs(no:Byte;h:Integer);
  var i:byte;
  begin
    high[no]:=h;
    mark[no]:=true;
    for i:=1 to n do begin
      if (graph[no,i]<>0) and not mark[i] then dfs(i,h+graph[i,no]);
      if (graph[no,i]<>0) and (high[i]<>h+graph[i,no]) then begin
         writeln('Impossible');
         close(output);
         halt;
      end;
    end;
  end;
procedure print;
  var i,j,low,temp:integer;
      no:array[1..200]of byte;
  begin
    for i:=1 to n do no[i]:=i;
    for i:=1 to n-1 do begin
      low:=i;
      for j:=i+1 to n do
        if high[j]>high[low] then low:=j;
      if low<>i then begin
         temp:=high[low];
         high[low]:=high[i];
         high[i]:=temp;
         temp:=no[low];
         no[low]:=no[i];
         no[i]:=temp;
      end;
    end;
    for i:=1 to n do begin
      if (i<n) and (high[i]=high[i+1]) then write(no[i],' ')
                                       else writeln(no[i]);
    end;
    close(output);
  ENd;
begin
  init;
  fillchar(mark,sizeof(mark),0);
  assign(output,'eye.out');
  rewrite(output);
  dfs(1,0);
  print;
end.