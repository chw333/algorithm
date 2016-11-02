{$A+,B-,D-,E+,F-,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V+,X+,Y-}
{$M 65520,0,655360}

program _guess;
var n,m:integer;

var fin,fout:text;

procedure init;
begin
     assign(fin,'guess.in1');
     reset(fin);
     assign(fout,'guess.out');
     rewrite(fout);
end;

function guess(top:integer; n1,n2:integer;t1,t2,t:char):integer;
begin
     if top>n+2 then begin guess:=0; exit; end;

     if n1=n2 then guess:=byte(t)-64
     else if n1>n2 then
             if t>t1 then
                guess:=guess(top+byte(t)-byte(t1),
                             n1-n2,n2,t,t2,t1)+byte(t)-byte(t1)
             else
                guess:=guess(top+3+byte(t)-byte(t1),
                             n1-n2,n2,t,t2,t1)+3+byte(t)-byte(t1)
          else
             if t>t2 then
                guess:=guess(top+byte(t)-byte(t2),
                             n2-n1,n1,t,t1,t2)+byte(t)-byte(t2)
             else
                guess:=guess(top+3+byte(t)-byte(t2),
                             n2-n1,n1,t,t1,t2)+3+byte(t)-byte(t2);
end;


const turns:array[0..2] of char =('C','A','B');
var print:array[1..10000,'A'..'C'] of integer;

procedure work;
var i,total:longint;

begin
     readln(fin,n,m);
     while (n<>-1) do
     begin
          fillchar(print,sizeof(print),0);
          total:=0;
          if n mod 3=2 then
          for i:=1 to m-1 do
              if guess(0,i,m-i,turns[(n+2) mod 3],turns[(n+1) mod 3],turns[n mod 3])=n then
              begin
                   inc(total);
                   print[total,turns[(n+2) mod 3]]:=i;
                   print[total,turns[(n+1) mod 3]]:=m-i;
                   print[total,turns[n mod 3]]:=m;
              end else
          else
          for i:=m-1 downto 1 do
              if guess(0,i,m-i,turns[(n+2) mod 3],turns[(n+1) mod 3],turns[n mod 3])=n then
              begin
                   inc(total);
                   print[total,turns[(n+2) mod 3]]:=i;
                   print[total,turns[(n+1) mod 3]]:=m-i;
                   print[total,turns[n mod 3]]:=m;
              end else;

          writeln(fout,total);
          for i:=1 to total do
              writeln(fout,print[i,'A'],' ',print[i,'B'],' ',print[i,'C']);
          readln(fin,n,m);
     end;
end;

procedure over;
begin
     close(fin);
     close(fout);
end;

var t:longint;
begin
     init;
{     t:=meml[0:$46c];}
     work;
     over;
{     writeln((meml[0:$46c]-t)/18.2:0:2);}
end.
