{$M 65520,0,655360,R-,Q-,S-,B-}
type
  str50=string[50];
  rectype=record
            rest:str50;
            rfrom:shortint;
            from:integer;
            way:shortint;
            len:integer;
          end;
var
  list:array[1..2*50*100]of ^rectype;
  str:array[1..2,1..100]of str50;
  n:array[1..2]of shortint;
  best,bestnode,op,cl:integer;
  found:boolean;
procedure init;
  var i,j:integer;
  begin
    for i:=1 to 2 do begin
      readln(n[i]);
      for j:=1 to n[i] do readln(str[i,j]);
    end;
  end;
function double(s:str50;rf:shortint):boolean;
  var i:integer;
  begin
    double:=true;
    for i:=2 to cl do
      if (list[i]^.rest=s) and (list[i]^.rfrom=rf) then exit;
    double:=false;
  end;
procedure main;
  var i:integer;
      recfrom:rectype;
      len,rfrom,addgroup,l1,l2:integer;
      s:array[1..2]of string;
  begin
    op:=1;
    cl:=1;
    best:=maxint;
    new(list[1]);
    list[1]^.rest:='';
    list[1]^.rfrom:=1;
    list[1]^.from:=0;
    list[1]^.len:=0;
    while op<=cl do begin
      recfrom:=list[op]^;
      addgroup:=3-recfrom.rfrom;
      for i:=1 to n[addgroup] do begin
        s[recfrom.rfrom]:=recfrom.rest;
        s[addgroup]:=str[addgroup,i];
        while (s[1]<>'') and (s[2]<>'') and (s[1][1]=s[2][1]) do begin
          delete(s[1],1,1);
          delete(s[2],1,1);
        end;
        if (s[1]<>'') and (s[2]<>'') then continue;
        if s[2]='' then rfrom:=1
                   else rfrom:=2;
        if double(s[rfrom],rfrom) then continue;
        l1:=recfrom.len;
        l2:=recfrom.len-length(recfrom.rest)+length(str[addgroup,i]);
        if l1>l2 then len:=l1
                 else len:=l2;
        if len>=best then continue;
        inc(cl);
        if (memavail<200) then exit;
        new(list[cl]);
        list[cl]^.rest:=s[rfrom];
        list[cl]^.rfrom:=rfrom;
        list[cl]^.from:=op;
        list[cl]^.way:=i;
        list[cl]^.len:=len;
        if s[1]=s[2] then begin
           found:=true;
           best:=len;
           bestnode:=cl;
        end;
      end;
      inc(op);
    end;
  end;
procedure printout(last:integer);
  var way:array[1..2,1..1000]of integer;
      t:array[1..2]of integer;
      addgroup,i,j,nlast:integer;
  begin
    writeln(best);
    t[1]:=0;
    t[2]:=0;
    while list[last]^.from<>0 do begin
      nlast:=list[last]^.from;
      addgroup:=3-list[nlast]^.rfrom;
      inc(t[addgroup]);
      way[addgroup,t[addgroup]]:=list[last]^.way;
      last:=nlast;
    end;
    for i:=1 to 2 do begin
      for j:=t[i] downto 2 do write(str[i,way[i,j]],'+');
      writeln(str[i,way[i,1]]);
    end;
  end;
begin
  assign(input,'match.in');
  reset(input);
  assign(output,'match.out');
  rewrite(output);
  init;
  found:=false;
  main;
  if not found then writeln(0)
               else printout(bestnode);
  close(input);
  close(output);
end.


