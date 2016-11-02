{$A+,B-,D-,E-,F-,G-,I-,L-,N-,O-,P-,Q-,R-,S-,T-,V-,X+,Y+}
{$M 65520,0,655360}
program mul;
const di:array[1..8]of char='INMHRPKT';
      an:array[1..8]of longint=(1,18,324,5832,104976,1889568,34012224,612220032);
type dd=array[0..1000]of longint;
var f,f1:text;
    tp,turn:dd;
    tb,ta:string;
    p,longa,long18,I,J,K,a,b:longint;

procedure readdata;
begin
  readln(f,ta);
  readln(f,tb);
  a:=0;
  b:=0;
  for i:=1 to length(ta) do
  for j:=1 to 5 do
  if di[j]=ta[i] then
  begin
    a:=a+an[j];
    j:=5;
  end;

  for i:=1 to length(tb) do
  for j:=1 to 5 do
  if di[j]=tb[i] then
  begin
    b:=b+an[j];
    j:=5;
  end;
end;

procedure turn2(a:longint;var long:longint; var turn:dd);
var i,j,k:longint;
    tt:dd;
begin
   k:=0;
   while (a>=2) do
   begin
     inc(k);
     tt[k]:=a mod 2;
     a:= a div 2;
   end;

   if a=1 then
   begin
     inc(k);
     tt[k]:=1;
   end;
   for j:=k downto 1 do
   turn[j]:=tt[k+1-j];
   long:=k;
end;

procedure turn10_to_18(a:longint;var long18:longint; var turn:dd);
var i,j,k:longint;
    tt:dd;
begin
   fillchar(tt,sizeof(tt),0);
   k:=0;
   while (a>=18) do
   begin
     inc(k);
     tt[k]:=a mod 18;
     a:= a div 18;
   end;

   if a<>0 then
   begin
     inc(k);
     tt[k]:=a;
   end;
   turn:=tt;
   long18:=k;
end;

begin
   assign(f,'input.txt');
   reset(f);
   assign(f1,'output.txt');
   rewrite(f1);
   readdata;
   turn2(a,longa,turn);

   for i:=1 to longa do
   begin
     p:=trunc(exp((i-1)*ln(2)));
     turn10_to_18(p,long18,tp);
     for j:=1 to long18 do
      for k:=1 to tp[j] do
      write(f1,di[j]);
      if turn[longa+1-i]<>0 then write(f1,'*');
      write(f1,' ');
      turn10_to_18(p*b,long18,tp);
      for j:=1 to long18 do
      for k:=1 to tp[j] do
      write(f1,di[j]);
      writeln(f1);
   end;
   write(f1,'The solution is: ');

   turn10_to_18(a*b,long18,tp);
     for j:=1 to long18 do
      for k:=1 to tp[j] do
      write(f1,di[j]);
      writeln(f1);
      close(f);
      close(f1);
end.
