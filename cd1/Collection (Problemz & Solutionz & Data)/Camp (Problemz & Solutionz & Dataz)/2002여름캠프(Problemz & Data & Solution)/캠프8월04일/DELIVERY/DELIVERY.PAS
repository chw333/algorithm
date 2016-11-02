{$R-,S-,Q-,B-}
type
  ktype=(Small,Big);
var
  list:array[1..1000]of record
                          time:integer;
                          kind:ktype;
                        end;
  n,t:integer;

procedure insert(time:integer;kind:ktype);
  var p:integer;
  begin
    p:=n;
    while (p>0) and (list[p].time>time) do begin
      list[p+1]:=list[p];
      dec(p);
    end;
    inc(n);
    list[p+1].time:=time;
    list[p+1].kind:=kind;
  end;

procedure init;
  var i,time,nn:integer;
  begin
    n:=0;
    readln(T);
    readln(nn);
    for i:=1 to nn do begin
      readln(time);
      insert(time,Small);
    end;
    readln(nn);
    for i:=1 to nn do begin
      readln(time);
      insert(time,Big);
    end;
  end;

procedure main;
  var can:array[0..1000]of integer;
      last,i,maxcan,nMax,ans,tot:integer;
  begin
    ans:=0;
    fillchar(can,sizeof(can),$FF);
    can[0]:=0;
    maxcan:=0;
    tot:=0;
    last:=0;
    ans:=0;
    repeat
      inc(last);
      if last>n then break;
      inc(tot,list[last].time);
      if tot>T+T then break;
      if list[last].kind=Small then begin
         nMax:=maxcan;
         for i:=0 to maxcan do
           if (i+list[last].time<=T) and (can[i]>=0) and (can[i]<last) then begin
           if can[i+list[last].time]<=0 then can[i+list[last].time]:=last;
           if i+list[last].time>nMax then nMax:=i+list[last].time;
         end;
         if nMax>maxcan then maxcan:=nMax;
         if tot-maxcan>T then break
                         else inc(ans);
      end else if tot-maxcan>T then dec(tot,list[last].time)
                               else inc(ans);
    until false;
    writeln(ans);
  end;

begin
  assign(input,'delivery.in');
  reset(input);
  assign(output,'delivery.out');
  rewrite(output);
  init;
  main;
  close(input);
  close(output);
end.