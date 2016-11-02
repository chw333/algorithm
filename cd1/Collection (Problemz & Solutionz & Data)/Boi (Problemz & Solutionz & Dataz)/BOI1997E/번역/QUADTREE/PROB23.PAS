{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T-,V+,X+,Y+}
{$M 32768,0,655360}
type leg=^nod;
     nod=record
               nr:longint;
               tip:char;
               s:array[1..4] of leg
     end;

var a,b:leg;
    n:integer;
    ch:char;
    f:text;

function build(var p:leg):longint;
var i:integer;
begin
     new(p);
     p^.nr:=1;
     read(f,ch);p^.tip:=ch;
     if ch='i' then
        for i:=1 to 4 do inc(p^.nr,build(p^.s[i]));
     build:=p^.nr;
end;

procedure citeste;
begin
     assign(f,'input.txt');reset(f);
     readln(f,n);
     build(a);readln(f);
     build(b);
     close(f);
end;

function count(var p,q:leg):longint;
var i:integer;
    nr:longint;
begin
     case p^.tip of
          'i':case q^.tip of
                   'b':count:=p^.nr;
                   'w':count:=1;
                   'i':begin
                            nr:=1;
                            for i:=1 to 4 do inc(nr,count(p^.s[i],q^.s[i]));
                            count:=nr
                   end;
          end;
          'b':count:=q^.nr;
          'w':count:=1
     end;
end;

procedure scrie;
begin
     assign(f,'output.txt');rewrite(f);
     write(f,count(a,b));
     close(f);
end;

begin
     citeste;
     scrie;
end.