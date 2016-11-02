{Description: O(c*n) - simple brush}
{Tomasz Walen, walen@mimuw.edu.pl}
{2001.05.14}
{$I+,$R+}
program mar;
const
   f_in	    = 'mar.in';
   f_out    = 'mar.out';
   maxn	    = 10000;
   miny	    = 0;
   maxy	    = 30000;
var
   f	 : text;
   edge	 : array[0..maxy] of integer;
   e_len : integer;
   e	 : array[0..2*maxn,1..4] of integer; {(x,y0,y1,delta=+-1)}
   en	 : longint;	 
   n	 : integer;
   area	 : longint;
	 
{*****}

procedure qsort(l,r : longint);
var
   i,j	 : longint;
   tmp	 : integer;
   m1,m4 : integer;
   ii	 : integer;
   m	 : longint;
begin
   if (l<r) then begin
      m:=(l+r) div 2;
      m1:=e[m,1];m4:=e[m,4];
      i:=l;j:=r;
      repeat
	 while (e[i,1]<m1) or ((e[i,1]=m1) and (e[i,4]<m4)) do inc(i);
	 while (m1<e[j,1]) or ((e[j,1]=m1) and (m4<e[j,4])) do dec(j);
	 if (i<=j) then begin
	    for ii:=1 to 4 do begin
	       tmp:=e[i,ii];e[i,ii]:=e[j,ii];e[j,ii]:=tmp;
	    end;
	    inc(i);
	    dec(j);
	 end;
      until i>j;
      if (l<j) then qsort(l,j);
      if (i<r) then qsort(i,r);
   end;
end; { qsort }

procedure read_data;
var
   x1,x2,y1,y2 : integer;
   i	       : integer;
begin
   assign(f,f_in);
   reset(f);
   readln(f,n);

   en:=0;
   for i:=1 to n do begin
      readln(f,x1,y1,x2,y2);
      
      inc(en);
      e[en,1]:=x1;
      e[en,2]:=y1;
      e[en,3]:=y2;
      e[en,4]:=1;

      inc(en);
      e[en,1]:=x2;
      e[en,2]:=y1;
      e[en,3]:=y2;
      e[en,4]:=-1;
   end;

   close(f);
end; { read_data }

procedure solve;
var
   i : integer;
   j : integer;
   d : integer;
begin
   fillchar(edge,sizeof(edge),0);
   e_len:=0;
   
   area:=0;
   qsort(1,en);

   e[0,1]:=0;
   for i:=1 to en do begin
      if (i>1) and (e[i,1]<>e[i-1,1]) then begin
	 area:=area+(e_len*(e[i,1]-e[i-1,1]));
      end;
      d:=e[i,4];
      for j:=e[i,2] to e[i,3]-1 do begin
	 inc(edge[j],d);
	 if (d>0) and (edge[j]=1) then inc(e_len);
	 if (d<0) and (edge[j]=0) then dec(e_len);
      end;
{      Writeln('e_len=',e_len,' en=',en);}
   end;
end; { solve }

procedure write_answer;
begin
   assign(f,f_out);
   rewrite(f);
   Writeln(f,area);
   close(f);
end; { write_answer }

begin   
   read_data;
   solve;
   write_answer;
end.
