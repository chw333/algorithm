{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+}
{$M 65520,0,655360}
Program EvilEye (input , output);
Const
  MaxN                     = 250;
  MaxL                     = 10;
  Inputname                = 'Eye.InA';
  Outputname               = 'Eye.OuA';
  Maxlength                = MaxL * Maxn;

Type
  TArr                     = array[0 .. maxn + 1] of Integer;
  TMap                     = array[0 .. maxn + 1] of ^TArr;
Var
  N , S                    : integer;
  Map                      : Tmap;
  ps , pt                  : integer;
  dist                     : Tarr;

Procedure Initalize;
Var
  i , j , k                : integer;
  Infp                     : Text;
begin
  assign (infp , inputname); reset (infp);
  readln (infp , n , s);
  for i :=0 to N + 1 do
    begin
      New (Map[i]); fillchar (Map[i]^ , sizeof(Map[i]^) , 0);
    end;
  for k :=1 to s do
    begin
      read (infp , i , j); readln(infp , map[i]^[j]);
      map[j]^[i] :=-map[i]^[j];
    end;
  close (infp);
  ps :=0; pt :=n + 1;
  fillchar (dist , sizeof(dist) , $FF);
end; {initalize}

Procedure Solve;
Var
  i , j , k                : integer;
  change                   : TArr;
  Stop                     : Boolean;
  Times                    : Integer;
  Outfp                    : text;
  place                    : Tarr;

Begin
  fillchar (change , sizeof(change) , 0);
  dist[ps] :=0;  change[ps] :=1;
  Times :=0;
  repeat
    inc (Times);
    Stop :=True;
    for i :=0 to N do
      if change[i] = 1
        then begin
               change[i] :=0;
               for j :=1 to N +  1 do
                 if (i = ps) or (j = pt) or (map[i]^[j] <> 0)
                   then begin
                          if (dist[i] + map[i]^[j] > dist[j])
                            then begin
                                   dist[j] :=dist[i] + map[i]^[j];
                                   change[j] :=1;
                                   stop :=False;
                                   if Dist[j] > Maxlength
                                     then begin
                                            times :=n + 1;
                                            break;
                                          end;
                                 end;
                        end;
               if times = N + 1
                 then break;
             end;
  Until (Times >= N + 1) or (Stop);
  assign (outfp , outputname); rewrite (outfp);
  if stop
    then begin
           fillchar (Place , sizeof(Place) , 0);
           for i :=1 to N do
             place[i] :=i;
           for i :=1 to N - 1 do
             for j :=i + 1 to N do
               if dist[place[i]] > dist[place[j]]
                 then begin
                        k :=place[i]; place[i] :=place[j]; place[j] :=k;
                      end;
           {for i :=1 to n do
             begin
               if (i > 1) and (dist[place[i]] > dist[place[i - 1]])
                 then writeln (outfp)
                 else if (i > 1)
                        then write (outfp , ' ');
               write (outfp , place[i]);
             end;
           writeln (outfp);}
           for i :=1 to n do
             writeln (outfp , dist[i]);
         end
    else writeln (outfp , '-1');
  close (outfp);
end; {Solve}

Begin
  Initalize;
  Solve;
end. {main}