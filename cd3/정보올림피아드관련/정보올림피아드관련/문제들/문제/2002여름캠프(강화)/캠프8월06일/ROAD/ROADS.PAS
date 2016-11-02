const
  maxn=100;
  inputfile='roads.in';
  outputfile='roads.out';
type
  link=^node;
  node=record
         no,toll,len:byte;
         next:link;
       end;
var
  n:byte;
  head:array[1..maxn]of link;
  minlen:array[1..maxn]of record
                            len,toll:integer;
                          end;
  mintoll:array[1..maxn]of integer;
  arrived:array[1..maxn]of boolean;
  graph:array[1..maxn,1..maxn]of record
                                   mtoll:shortint;
                                   len,toll:shortint;
                                 end;
  tottoll,best:integer;
procedure add(s,d,l,t:integer);
  var ok:boolean;
      pre,p:link;
  begin
    pre:=head[s];
    p:=pre^.next;
    ok:=true;
    while ok and (p<>nil) do begin
      if p^.no=d
         then if (p^.len<=l) and (p^.toll<=t)
                 then ok:=false
                 else if (p^.len>=l) and (p^.toll>=t)
                         then begin
                                pre^.next:=p^.next;
                                dispose(p);
                                p:=pre;
                              end;
      pre:=p;
      p:=p^.next;
    end;
    if ok then begin
       new(p);
       p^.no:=d;
       p^.len:=l;
       p^.toll:=t;
       p^.next:=nil;
       pre^.next:=p;
       if (graph[s,d].mtoll<0) or (t<graph[s,d].mtoll)
          then graph[s,d].mtoll:=t;
       if (graph[s,d].len<0) or (l<graph[s,d].len) then begin
          graph[s,d].len:=l;
          graph[s,d].toll:=t;
       end;
    end;
  end;
procedure init;
  var i,j,s,d,l,t,r:integer;
  begin
    assign(input,inputfile);
    reset(input);
    read(tottoll,n,r);
    for i:=1 to n do begin
      new(head[i]);
      head[i]^.next:=nil;
    end;
    for i:=1 to n do begin
      graph[i,i].len:=0;
      graph[i,i].toll:=0;
      graph[i,i].mtoll:=0;
      for j:=i+1 to n do begin
        graph[i,j].mtoll:=-1;
        graph[i,j].len:=-1;
        graph[j,i]:=graph[i,j];
      end;
    end;
    for i:=1 to r do begin
      read(s,d,l,t);
      if t<=tottoll then add(s,d,l,t);
    end;
    close(input);
  end;
procedure make;
  var i,min,nextmin:byte;
      mark:array[1..maxn]of boolean;
  begin
    for i:=1 to n-1 do begin
      mintoll[i]:=-1;
      minlen[i].len:=-1;
    end;
    fillchar(mark,sizeof(mark),0);
    mintoll[n]:=0;
    min:=n;
    repeat
      nextmin:=0;
      mark[min]:=true;
      for i:=1 to n do if not mark[i] then begin
        if graph[i,min].mtoll>=0 then
           if (mintoll[i]<0) or (graph[i,min].mtoll+mintoll[min]<mintoll[i])
           then mintoll[i]:=graph[i,min].mtoll+mintoll[min];
        if (mintoll[i]>=0) and
           ((nextmin=0) or (mintoll[i]<mintoll[nextmin])) then nextmin:=i;
      end;
      min:=nextmin;
    until min=0;
    fillchar(mark,sizeof(mark),0);
    minlen[n].len:=0;
    minlen[n].toll:=0;
    min:=n;
    repeat
      nextmin:=0;
      mark[min]:=true;
      for i:=1 to n do if not mark[i] then begin
        if graph[i,min].len>=0 then
           if (minlen[i].len<0) or
              (graph[i,min].len+minlen[min].len<minlen[i].len) or
              (graph[i,min].len+minlen[min].len=minlen[i].len) and
              (graph[i,min].toll+minlen[min].toll<minlen[i].toll)
           then begin
                  minlen[i].len:=graph[i,min].len+minlen[min].len;
                  minlen[i].toll:=graph[i,min].toll+minlen[min].toll;
                end;
        if (minlen[i].len>=0) and
           ((nextmin=0) or
            (minlen[i].len<minlen[nextmin].len) or
            (minlen[i].len=minlen[nextmin].len) and
            (minlen[i].toll<minlen[nextmin].toll))
        then nextmin:=i;
      end;
      min:=nextmin;
    until min=0;
  end;
procedure run(now:byte;sumlen,sumtoll:integer);
  var p:link;
  begin
    if sumtoll+minlen[now].toll<=tottoll then begin
       best:=sumlen+minlen[now].len;
       exit;
    end;
    p:=head[now]^.next;
    while p<>nil do begin
      if not arrived[p^.no] and (mintoll[p^.no]>=0) and
         (sumlen+p^.len+minlen[p^.no].len<best) and
         (sumtoll+p^.toll+mintoll[p^.no]<=tottoll)
      then begin
             arrived[p^.no]:=true;
             run(p^.no,sumlen+p^.len,sumtoll+p^.toll);
             arrived[p^.no]:=false;
           end;
      p:=p^.next;
    end;
  end;
begin
  init;
  make;
  best:=maxint;
  fillchar(arrived,sizeof(arrived),0);
  arrived[1]:=true;
  if (mintoll[1]>=0) and (mintoll[1]<=tottoll) then run(1,0,0);
  assign(output,outputfile);
  rewrite(output);
  if best=maxint then writeln(-1)
                 else writeln(best);
  close(output);
end.



