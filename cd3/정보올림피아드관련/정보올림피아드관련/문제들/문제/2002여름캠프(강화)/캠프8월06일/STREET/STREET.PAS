{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 16384,0,655360}
var a:array[1..50,1..50] of integer;
    nl,na:array[1..50] of integer;
    nr:array[1..50] of longint;
    m:array[1..50] of boolean;
    i,j,k,l,n,s,aa:integer;
    ex:longint;
    f:text;

procedure citeste;
begin
     assign(f,'input.txt');reset(f);
     read(f,n,s);
     for i:=1 to n do
         for j:=1 to n do read(f,a[i,j]);
     close(f);
end;

procedure trace(k:integer);
var i:integer;
begin
     m[k]:=true;
     for i:=1 to n do if not m[i] and ((a[i,k]>0) or (a[k,i]>0)) then trace(i);
end;

procedure punctula;
begin
     trace(1);
     for i:=1 to n do if not m[i] then exit;
     for i:=1 to n do
         for j:=1 to n do begin
             inc(nl[i],a[i,j]);
             inc(na[j],a[i,j]);
         end;
     for i:=1 to n do
         if nl[i]<na[i] then
            if nl[i]+1=na[i] then
               if k>0 then exit else inc(k)
            else exit
         else if nl[i]>na[i] then
            if na[i]+1=nl[i] then
               if l>0 then exit else inc(l)
            else exit;
     if k=1 then aa:=1 else
        if l=1 then aa:=n-1 else aa:=n
end;


procedure punctulb;
begin
     for i:=1 to n do
         case s of
              0:nr[i]:=0;
              1:nr[i]:=a[i,i];
              2:for j:=1 to n do inc(nr[i],longint(a[i,j])*a[j,i]);
              3:for j:=1 to n do
                    for k:=1 to n do
                        inc(nr[i],longint(a[i,j])*a[j,k]*a[k,i]);
         end;
     for i:=1 to n-1 do
         for j:=i+1 to n do
             if nr[j]<nr[i] then begin
                ex:=nr[i];
                nr[i]:=nr[j];
                nr[j]:=ex
             end;
end;

procedure scrie;
begin
     assign(f,'output.txt');rewrite(f);
     if aa=0 then writeln(f,'NO') else
     begin
          writeln(f,'YES');
          writeln(f,aa)
     end;
     for i:=1 to n do write(f,nr[i],' ');
     close(f);
end;

begin
     citeste;
     punctula;
     punctulb;
     scrie;
end.