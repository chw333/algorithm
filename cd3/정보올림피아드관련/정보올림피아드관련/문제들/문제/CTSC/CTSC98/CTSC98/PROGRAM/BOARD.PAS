{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O+,P-,Q-,R+,S-,T-,V-,X-,Y-}
{$M 65520,0,655360}
program board;
uses crt,dos;
var f,f1:text;
    pig,j,k,i,n,m,mins:integer;
    area:array[1..100]of integer;
    pot:array[1..140,1..4]of SHORTINT;
    bf:array[0..140,1..2]of SHORTINT;
    to_box:array[0..140,1..2]of SHORTINT;
    totalpot,totalbian:integer;
    tb,dayu:array[0..140,1..140]of SHORTINT;
    area_bian:array[1..140,1..4]of SHORTINT;
    bus:array[0..140,1..3]of SHORTINT;
    box_bian:array[0..140,0..140]of SHORTINT;
    t:array[0..140]of SHORTINT;
    answer,sign:array[0..140]of integer;

procedure pang(box,p1,p2,ways:integer);
var i,j,k:integer;
begin
  k:=0;
  j:=0;
  for i:=1 to totalbian do
  if ((bf[i,1]=p1)and(bf[i,2]=p2)) then
  begin
   k:=i;
   i:=totalbian;
   j:=1;
  end
  else
  if ((bf[i,1]=p2)and(bf[i,2]=p1)) then
  begin
   k:=i;
   i:=totalbian;
   j:=2;
  end;

  if k=0 then
  begin
    inc(totalbian);
    bf[totalbian,1]:=p1;
    bf[totalbian,2]:=p2;
    k:=totalbian;
    j:=1;
  end;
  to_box[k,j]:=box;
  area_bian[box,ways]:=k;
end;

procedure trunbian;
var line,col:integer;
begin
 totalbian:=0;
 for i:=1 to m do
 begin
   line:= (area[i]-1) div n+1;
   col:=  (area[i]-1) mod n+1;
   pot[i,1]:=(line-1)*(n+1)+col;
   pot[i,2]:=(line-1)*(n+1)+col+1;
   pot[i,4]:=line*(n+1)+col;
   pot[i,3]:=line*(n+1)+col+1;

   pang(i,pot[i,1],pot[i,2],1);
   pang(i,pot[i,2],pot[i,3],2);
   pang(i,pot[i,3],pot[i,4],3);
   pang(i,pot[i,4],pot[i,1],4);
 end;
end;

procedure print(step:integer);
var pigs,i,j,k,l:integer;
begin

  i:=bus[step,1];
  j:=bus[step,2];
  k:=bus[step,3];
  pigs:=(i-j)*(i-j)+(j-k)*(j-k)+(i-k)*(i-k);

   if pigs>=mins then exit;
   mins:=pigs;

  for i:=1 to 3 do
  write(bus[step,i],' ');
  writeln;
  for i:=1 to totalbian do
  write(sign[i],' ');
  writeln;
  writeln('S=',mins);

  answer:=sign;
  tb:=dayu;
end;

procedure trun(step,now_bian,way:integer;boxname:integer;var bi:boolean);
var p,i,j,k:integer;
    dd:array[1..7]of integer;
    tp:array[1..3]of integer;
begin
  bi:=true;
  for i:=1 to 4 do
  dd[i]:=pot[boxname,i];

  for i:=1 to 3 do
  dd[i+4]:=dd[i];

  p:=0;
  for i:=1 to 4 do
  begin
   if (dayu[dd[i],dd[i+1]]<>0)and(dayu[dd[i+1],dd[i+2]]<>0)and
    (dayu[dd[i+2],dd[i+3]]<>0)and(dayu[dd[i],dd[i+3]]<>0) then
    begin
     inc(bus[step,1]);
     i:=4;
     p:=1;
    end
  else
  if (dayu[dd[i+1],dd[i]]<>0)and(dayu[dd[i+2],dd[i+1]]<>0)and
    (dayu[dd[i+3],dd[i+2]]<>0)and(dayu[dd[i+3],dd[i]]<>0) then
    begin
     inc(bus[step,2]);
     i:=4;
     p:=2;
    end
  else
  if (dayu[dd[i],dd[i+1]]<>0)and(dayu[dd[i+2],dd[i+1]]<>0)and
    (dayu[dd[i+2],dd[i+3]]<>0)and(dayu[dd[i],dd[i+3]]<>0) then
    begin
     inc(bus[step,3]);
     i:=4;
     p:=3;
    end
  end;

  if p=0 then
  begin
    bi:=false;
    exit;
  end;

  for i:=1 to 3 do
  tp[i]:=bus[step,i];

  k:=0;
  for j:=1 to m do
  if box_bian[step,j]<>4 then inc(k);

  while (k>0) do
  begin
    dec(k);
    if (tp[1]=tp[2])and(tp[1]=tp[3]) then
         k:=0
     else
     begin

    if (tp[1]>=tp[2])and(tp[3]>=tp[2]) then inc(tp[2])
    else
    if (tp[1]>=tp[3])and(tp[1]>=tp[3]) then inc(tp[3])
    else
    if (tp[3]>=tp[1])and(tp[2]>=tp[1]) then inc(tp[1]);
   end;
  end;

  if( (tp[1]-tp[2])*(tp[1]-tp[2])+(tp[3]-tp[2])*(tp[3]-tp[2])+
    (tp[1]-tp[3])*(tp[1]-tp[3])>=mins) then bi:=false;

end;

procedure find(step:integer; now_bian:integer; way:integer);
var ii,jj,i,j,k:integer;
    bi:boolean;
begin

   bi:=true;
   if way=2 then
      if dayu[bf[now_bian,1],bf[now_bian,2]]<>0 then exit
      else
   else
      if dayu[bf[now_bian,2],bf[now_bian,1]]<>0 then exit;

  if way=1 then
  begin
   ii:=bf[now_bian,1];
   jj:=bf[now_bian,2];
  end
  else
  begin
   ii:=bf[now_bian,2];
   jj:=bf[now_bian,1];
  end;

  for i:=1 to totalpot do
  if (i=ii)or(dayu[i,ii]<>0) then
    for j:=1 to totalpot do
    if (j=jj)or(dayu[jj,j]<>0) then
     if dayu[i,j]=0 then
     dayu[i,j]:=step;

  sign[now_bian]:=way;
  if mins=0 then bi:=false;
  if (mins=2)and(m mod 3<>0) then bi:=false;

  box_bian[step]:=box_bian[step-1];
  bus[step]:=bus[step-1];

  if bi then
  begin
     for i:=1 to 2 do
     if to_box[now_bian,i]<>0 then
     begin
        inc(box_bian[step,to_box[now_bian,i]]);

        if box_bian[step,to_box[now_bian,i]]=4 then
           trun(step,now_bian,way,to_box[now_bian,i],bi);

        if not bi then
        begin
         for j:=1 to i do
         dec(box_bian[step,to_box[now_bian,j]]);
         i:=2;
        end;
     end;

    if bi then
        if step=totalbian then print(step)
        else
        begin
          for i:=3 downto 0 do
           for j:=1 to m do
           if box_bian[step,j]=i then
            for k:=1 to 4 do
            if sign[area_bian[j,k]]=0 then
            begin
               if step mod 2=0 then
               begin
               find(step+1,area_bian[j,k],1);
               find(step+1,area_bian[j,k],2);
               end
               else
               begin
               find(step+1,area_bian[j,k],2);
               find(step+1,area_bian[j,k],1);
               end;

               k:=4;
               j:=m;
               i:=0;
            end;

        end;
  end;

  sign[now_bian]:=0;
  for i:=1 to totalpot-1 do
  for j:=i+1 to totalpot do
  begin
    if dayu[i,j]=step then dayu[i,j]:=0;
    if dayu[j,i]=step then dayu[j,i]:=0;
  end;
end;

procedure getanswer;
var 
    p,l,i,j:integer;
begin
   fillchar(t,sizeof(t),0);

   k:=0;
   for i:=1 to m do
   for j:=1 to 4 do
   if t[pot[i,j]]=0 then
   begin
    inc(K);
    t[pot[i,j]]:=1;
   end;

   for i:=1 to k do
   begin

     for j:=1 to totalpot do
     if t[j]=1 then
     begin
        p:=1;
        for l:=1 to totalpot do
        if t[l]=1 then
         if tb[j,l]<>0 then
         begin
            p:=0;
            l:=totalpot;
         end;

        if p=1 then
        begin
         answer[j]:=i;
         t[j]:=2;
         j:=totalpot;
        end;
     end;
   end;
end;

begin
  clrscr;
  assign(f,'input.txt');
  reset(f);
  assign(f1,'output.txt');
  rewrite(f1);

  fillchar(dayu,sizeof(dayu),0);
  fillchar(area_bian,sizeof(area_bian),0);
  fillchar(bus,sizeof(bus),0);
  fillchar(sign,sizeof(sign),0);
  fillchar(box_bian,sizeof(box_bian),0);

  readln(f,n);
  readln(f,m);
  for i:=1 to m do
  read(f,area[i]);
  trunbian;
  mins:=2*(m+1)*(m+1);

  k:=0;
  totalpot:=(n+1)*(n+1);

  for i:=1 to totalbian do
  if (to_box[i,1]<>0)and(to_box[i,2]<>0) then
  begin
    k:=i;
    for j:=1 to 2 do
    find(1,i,j);
    i:=totalbian;
  end;

  if k=0 then
   for j:=1 to 2 do
   find(1,1,j);

   fillchar(t,sizeof(t),0);
   getanswer;
   writeln(f1,mins);
   writeln(f1,k);
   for i:=1 to totalpot do
   if t[i]<>0 then
    writeln(f1,i,' ',answer[i]);

  close(f);
  close(f1);
end.
