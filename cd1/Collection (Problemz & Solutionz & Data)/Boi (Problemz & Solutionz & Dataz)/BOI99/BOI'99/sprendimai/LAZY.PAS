{$M 65520,0,655360,R-,S-,Q-,B-}
type
  btype=array[1..100]of boolean;
var
  add,x,best,nc,nr:integer;
  start:longint;
  list:array[1..200,0..100]of byte;
  l,num:array[1..101,0..200]of byte;
  fufiled:btype;
  bestway,used:array[1..200]of boolean;
procedure init;
  var i,j,x,xx:integer;
      meet:array[1..100]of integer;
  begin
    fillchar(meet,sizeof(meet),$FF);
    readln(nc,nr);
    for i:=1 to nc do begin
      list[i,0]:=0;
      for j:=1 to nr do begin
        read(x);
        if x=1 then begin
           inc(list[i,0]);
           list[i,list[i,0]]:=j;
           if (meet[j]<0) then meet[j]:=i
                          else meet[j]:=0;
        end;
      end;
      readln;
    end;
    add:=0;
    for i:=1 to nr do if meet[i]>0 then begin
      for j:=1 to list[meet[i],0] do
        if not fufiled[list[meet[i],j]]
           then begin
                  fufiled[list[meet[i],j]]:=true;
                  dec(nr);
                end;
      used[meet[i]]:=true;
      inc(add);
    end;
  end;
procedure run(lev,nf:integer);
  var n,i,j,k,s:integer;
      temp:^btype;
  begin
    if nf=nr then begin
       if lev-1<best then begin
          best:=lev-1;
          bestway:=used;
       end;
       exit;
    end;
    if (lev>=best) or (MEML[$40:$6c]-start>150) then exit;
    n:=0;
    for i:=1 to nc do if not used[i] then begin
      s:=0;
      for j:=1 to list[i,0] do if not fufiled[list[i,j]] then inc(s);
      num[lev,i]:=s;
      if s>0 then begin
         l[lev,0]:=i;
         k:=n;
         while num[lev,l[lev,k]]<s do begin
           l[lev,k+1]:=l[lev,k];
           dec(k);
         end;
         inc(n);
         l[lev,k+1]:=i;
      end;
    end;
    new(temp);
    temp^:=fufiled;
    for i:=1 to n do begin
      k:=l[lev,i];
      for j:=1 to list[k,0] do fufiled[list[k,j]]:=true;
      used[k]:=true;
      run(lev+1,nf+num[lev,k]);
      used[k]:=false;
      fufiled:=temp^;
    end;
    dispose(temp);
  end;
begin
  start:=meml[$40:$6c];
  assign(input,'lazy.in');
  reset(input);
  assign(output,'lazy.out');
  rewrite(output);
  fillchar(fufiled,sizeof(fufiled),0);
  fillchar(used,sizeof(used),0);
  init;
  best:=nr+1;
  run(1,0);
  writeln(best+add);
  for x:=1 to nc do if bestway[x] then write(x,' ');
  writeln;
  close(input);
  close(output);
end.