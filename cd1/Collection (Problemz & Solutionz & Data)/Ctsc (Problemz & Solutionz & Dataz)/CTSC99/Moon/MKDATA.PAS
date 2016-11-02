{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R+,S+,T-,V+,X+}
{$M 16384,0,655360}
Program Mkdata (input , output);
Const
  FName = 'Eye.InA';
  TmpName = 'Eye.tmp';
  Samname = 'Eye.sam';

  N = 250;
Var
  Fp : Text;
  tmpfp : text;
  S  : Integer;
  i , j  , k , l: integer;
  sort : array[1 .. n] of integer;
  pos  : array[1 .. n] of integer;
begin
{ randomize;
  fillchar (sort , sizeof(sort) , 0);
  fillchar (pos , sizeof(pos) , 0);
  for i :=1 to n do
    begin
      sort[i] :=i;
      if i > 1
        then pos[i] :=pos[i - 1] + Random (11);
    end;
  for i :=1 to n - 1 do
    begin
      j :=random (n - i) + 1;
      k :=sort[i]; sort[i] :=sort[i + j]; sort[i + j] :=k;
    end;
  assign (Fp , TmpName); rewrite (fp);
  writeln (fp , n) ;
  s :=0;
  for i :=1 to n do
    begin
      j :=i + 1;
      While (j <= n) and (pos[j] - pos[i] <= 10) do
        begin
        if (pos[j] > pos[i]) and (random (100) <> 0)
          then begin
                 writeln (fp , sort[i] , ' ' , sort[j] , ' ' , pos[j] - pos[i]);
                 inc (s);
               end;
        inc (j);
        end;
    end;
  close (fp);
  assign (tmpfp , tmpName); reset (tmpfp);
  assign (fp , Fname); rewrite (fp);
  readln (tmpfp); writeln (fp , n , ' ' , s);
  for k :=1 to s do
    begin
      readln (tmpfp , i , j , l);
      writeln (fp , i , ' ' , j , ' ' , l);
    end;
  close (fp);
  close (tmpfp);
  assign (fp , SamName); rewrite (fp);
  for i :=1 to n do
    begin
      if i > 1
        then begin
               if pos[i] > pos[i - 1]
                 then writeln (fp)
                 else write (fp , ' ');
             end;
      write (fp , sort[i]);
    end;
  writeln (fp);
  close (fp);}
  assign (fp , Fname); rewrite (fp);
  writeln (fp , n , ' ' , n);
  for i :=1 to n - 1 do
    begin
      writeln (fp , i , ' ' , i + 1 , ' ' , 10);
    end;
  writeln (fp , 1 , ' ' , n div 2 , ' ' , 10);
  close (fp);
end. {main}
{evil eye}