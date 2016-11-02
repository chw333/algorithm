program prasatko(input,output);

(*
  Piggy-Bank
  CERC 1999, Jan Cada
*)

const MINCI=500; MAXW=10000;

var uloh: integer;
    i   : integer;
    j   : integer;
    k   : integer;
    E,F : integer;
    N   : integer;
    P,W : array [0..MINCI] of integer;
    jde : array [0..MAXW*2] of boolean;
    cena: array [0..MAXW*2] of integer; 

begin
 readln(uloh);
 while(uloh>0) do 
 begin
  readln(E,F);
  readln(N);

  for i:=0 to MAXW do
   jde[i] := false; 

  jde[0]:=true;
  cena[0]:=0;
  
  for i:=1 to N do 
  begin { hodnota, hmotnost}
   readln(P[i],W[i]);
   if not( jde[W[i]] and (cena[W[i]]<P[i])) then 
   begin
    jde[W[i]]:=true;
    cena[W[i]]:=P[i];
   end;   
  end;
  
  
  if (F-E)=0 then cena[0]:=0
  else begin 
  for i:=1 to (F-E) do
   if jde[i] then
  begin 
   for j:=1 to N do
    if((jde[i+W[j]] and (cena[i+W[j]] > (cena[i]+P[j]))) or
       (not jde[i+W[j]])) then
    begin
     jde[i+W[j]] := true;
     cena[i+W[j]]:= cena[i]+P[j]; 
    end; 
  end; 
  end;
  
  if jde[F-E] then
   writeln('The minimum amount of money in the piggy-bank is ',cena[F-E],'.')
  else 
   writeln('This is impossible.');
  uloh := uloh - 1;
 end;
end. 
