{$A+,B-,C+,D+,E-,F-,G+,H+,I+,J+,K-,L+,M-,N+,O-,P+,Q+,R+,S+,T-,U-,V+,W-,X+,Y+,Z1}
{$MINSTACKSIZE $00004000}
{$MAXSTACKSIZE $00100000}
{$IMAGEBASE $00400000}
{$APPTYPE Console}

program grade;
uses
  Matrix in 'Matrix.pas';
const
  MaxC=100;
  MaxS=500;
  outfname='score.out';
     infname='gpa.in';
  outf2name='';

var
  coursenum,studentnum:integer;
  score:array[1..MaxS,1..MaxC] of real;
  select:array[1..MaxS,1..MaxC] of shortint;
  s_cnum:array[1..MaxS] of integer;
  c_snum:array[1..MaxC] of integer;
  A,A2:TMatrix;
  b:array[1..MaxC] of real;
  delta:array[1..MaxC] of real;
  order:array[1..MaxS] of integer;
  avg:array[1..MaxS] of real;
  outf:Text;

procedure init;
var
  inf:text;
  i,j,ii,jj,k:integer;
  aa,bb,gg,hh,tmpreal:real;
begin
  assign(inf,infname);
  reset(inf);
  fillchar(select,sizeof(select),0);
  fillchar(s_cnum,sizeof(s_cnum),0);
  fillchar(c_snum,sizeof(c_snum),0);
  fillchar(delta,sizeof(delta),0);
  fillchar(avg,sizeof(avg),0);
  readln(inf,studentnum,coursenum);
  for i:=1 to studentnum do
   for j:=1 to coursenum do
    begin
     read(inf,score[i,j]);
     if (score[i,j]>100) or (score[i,j]<-1) then
      begin
       writeln(score[i,j]);
       halt;
      end;
     if score[i,j]>-0.5 then
      begin
       inc(s_cnum[i]);inc(c_snum[j]);
       select[i,j]:=1;
      end;
    end;
  // check if there is a course without a single student's participation
  for j:=coursenum downto 1 do
   if c_snum[j]<>0 then break;
  coursenum:=j; k:=1;
  while(k<=coursenum)do
   begin
     if c_snum[k]=0 then
      begin
       for i:=1 to studentnum do
        begin
         score[i,k]:=score[i,coursenum];
         select[i,k]:=select[i,coursenum];
        end;
        c_snum[k]:=c_snum[coursenum];
        dec(coursenum);
        for j:=coursenum downto 1 do
         if c_snum[j]<>0 then break;
        coursenum:=j;
       end;
     inc(k);
   end;

  A.Create(coursenum,coursenum);
  A2.Create(coursenum,coursenum+1);
  for k:=1 to coursenum do
   begin
     bb:=0;gg:=0;hh:=0;
     for jj:=1 to coursenum do
     begin
      for ii:=1 to studentnum do
       begin
         bb:=bb+select[ii,k]*select[ii,jj];
         gg:=gg+select[ii,k]*select[ii,jj]*score[ii,jj];
       end;
     end;
     for jj:=1 to studentnum do hh:=hh+score[jj,k]*select[jj,k];
     b[k]:=gg/bb-hh/c_snum[k];
     for j:=1 to coursenum-1 do
      begin
       aa:=0;
       for ii:=1 to studentnum do aa:=aa+select[ii,k]*select[ii,j];
       if j=k then A.Matrix[k,j]:=1-aa/bb
       else A.Matrix[k,j]:=-aa/bb;
      end;
    end;
  A2.Matrix:=A.Matrix;
  for k:=1 to coursenum do A2.matrix[k,coursenum+1]:=b[k];
  close(inf);
end;

procedure sort;
var
  i,j:integer;
  tmp:integer;
  outf2:Text;
  count:integer;
begin
  for i:=1 to studentnum do order[i]:=i;
  for i:=1 to studentnum do
   begin
    for j:=1 to coursenum do avg[i]:=avg[i]+select[i,j]*score[i,j];
    avg[i]:=avg[i]/s_cnum[i];
   end;
  for i:=1 to studentnum-1 do
   for j:=i+1 to studentnum do
    begin
     if (avg[order[i]]<avg[order[j]]) then
      begin
        tmp:=order[i];
        order[i]:=order[j];
        order[j]:=tmp;
      end;     
    end;
  assign(outf2,outf2name);
  rewrite(outf2);
  count:=0;
  for i:=1 to studentnum-1 do
   for j:=i+1 to studentnum do
    if abs(avg[i]-avg[j])<1e-3 then
      begin
       inc(count);
       //writeln(outf2,'uhoh',count,' ',i,' ',j);
       //readln;
      end;
  close(outf2);
end;

procedure printorder;
var
 i:integer;
begin
 {for i:=1 to coursenum do write(outf,b[i]:0:2,' ');
 writeln(outf);}
 //for i:=1 to coursenum do write(delta[i]:0:2,' ');
 //writeln;
 //for i:=1 to coursenum do write(outf,delta[i]:0:2,' ');
  //for i:=1 to studentnum do writeln(outf,order[i]);
 //writeln(outf);
 for i:=1 to studentnum do write(outf,avg[i]:0:2,' ');
end;

var
  m1 : TMatrix;
  r1,r2    : integer;
  //d1    : real;
  flg   : boolean;
  i,j:integer;
begin
  init;
  assign(outf,outfname);
  rewrite(outf);
  for i:=1 to studentnum do
   if s_cnum[i]=0 then begin writeln(outf,'fail');close(outf);exit;end;
  if(studentnum=1) then
   begin
    writeln(outf,'1');
    close(outf);
    exit;
   end;
  A.Standardize(m1,R1);
  A2.Standardize(m1,R2);
  if(r1<coursenum-1) or (R2>R1) then
   begin
    writeln(outf,'fail');
    close(outf);
    exit;
   end;
  dec(A.Rn);dec(A.Cn);
  //A.OutputtoFile('');
  A.OprAntiMatrix(m1, flg);
  //m1.OutputtoFile('');
  delta[coursenum]:=0;
  for i:=1 to coursenum-1 do
   for j:=1 to coursenum-1 do
    delta[i]:=delta[i]+m1.matrix[i,j]*b[j];
  for i:=1 to studentnum do
   for j:=1 to coursenum do
   begin
    score[i,j]:=score[i,j]+select[i,j]*delta[j];
   end;
  sort;
  printorder;
  close(outf);
  writeln('program successfully terminated.');
  readln;
end.
