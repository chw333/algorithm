{Description: O(n*n) - compression}
{Tomasz Walen, walen@mimuw.edu.pl}
{2001.05.14}
{$I+,$R+}
program mar;
const
   f_in	 = 'mar.in';
   f_out = 'mar.out';
   maxn	 = 10000;
   miny	 = 0;
   maxy	 = 30000;
   maxb	 = 1000;
var
   f	: text;
   b	: array[0..maxb,0..maxb] of boolean;
   r	: array[1..maxn,1..4] of integer;
   n	: integer;
   area	: longint;
		 
   y_dict : array[0..2*maxn+1] of integer;
   y2n	  : array[0..maxy] of integer;
   y_len  : integer;
		 
   x_dict : array[0..2*maxn+1] of integer;
   x2n	  : array[0..maxy] of integer;
   x_len  : integer;

   x2len : array[0..2*maxn+1] of longint;
   y2len : array[0..2*maxn+1] of longint;   

		 
	 
{*****}

procedure qsort1(l,r : longint);
var
   i,j : longint;
   tmp : integer;
   mm   : integer;
   m   : longint;
begin
   if (l<r) then begin
      m:=(l+r) div 2;
      mm:=x_dict[m];
      i:=l;j:=r;
      repeat
	 while (x_dict[i]<mm) do inc(i);
	 while (mm<x_dict[j]) do dec(j);
	 if (i<=j) then begin
	       tmp:=x_dict[i];x_dict[i]:=x_dict[j];x_dict[j]:=tmp;
	    inc(i);
	    dec(j);
	 end;
      until i>j;
      if (l<j) then qsort1(l,j);
      if (i<r) then qsort1(i,r);
   end;
end; { qsort1 }


procedure qsort2(l,r : longint);
var
   i,j : longint;
   tmp : integer;
   mm   : integer;
   m   : longint;
begin
   if (l<r) then begin
      m:=(l+r) div 2;
      mm:=y_dict[m];
      i:=l;j:=r;
      repeat
	 while (y_dict[i]<mm) do inc(i);
	 while (mm<y_dict[j]) do dec(j);
	 if (i<=j) then begin
	       tmp:=y_dict[i];y_dict[i]:=y_dict[j];y_dict[j]:=tmp;
	    inc(i);
	    dec(j);
	 end;
      until i>j;
      if (l<j) then qsort2(l,j);
      if (i<r) then qsort2(i,r);
   end;
end; { qsort2 }



procedure read_data;
var
   x1,x2,y1,y2 : integer;
   i	       : integer;
begin
   assign(f,f_in);
   reset(f);
   readln(f,n);

   y_len:=0;
   x_len:=0;
   for i:=1 to n do begin
      readln(f,x1,y1,x2,y2);
      r[i,1]:=x1;r[i,2]:=y1;
      r[i,3]:=x2;r[i,4]:=y2;

      inc(x_len); x_dict[x_len]:=x1;
      inc(x_len); x_dict[x_len]:=x2;      
      
      inc(y_len); y_dict[y_len]:=y1;
      inc(y_len); y_dict[y_len]:=y2;      
   end;

   close(f);
end; { read_data }

procedure solve;
var
   i	       : integer;
   j	       : integer;
   x1,x2,y1,y2 : integer;
   x,y	       : integer;
begin
   fillchar(b,sizeof(b),0);
   area:=0;

   {compression}
   qsort1(1,x_len);   
   qsort2(1,y_len);
   j:=0;
   for i:=1 to x_len do begin
      if (j=0) or (x_dict[i]<>x_dict[j]) then begin
	 inc(j);
	 x_dict[j]:=x_dict[i];
      end;
   end;
   x_len:=j;   
   j:=0;
   for i:=1 to y_len do begin
      if (j=0) or (y_dict[i]<>y_dict[j]) then begin
	 inc(j);
	 y_dict[j]:=y_dict[i];
      end;
   end;
   y_len:=j;

   if (x_len>maxb) or (y_len>maxb) then Writeln('to big!');
   if (x_len>maxb) then x_len:=maxb-1;
   if (y_len>maxb) then y_len:=maxb-1;   

   fillchar(x2n,sizeof(x2n),0);
   x_dict[x_len+1]:=maxy;
   for i:=1 to x_len do 
      for j:=x_dict[i] to x_dict[i+1]-1 do x2n[j]:=i;   
   
   fillchar(y2n,sizeof(y2n),0);
   y_dict[y_len+1]:=maxy;
   for i:=1 to y_len do 
      for j:=y_dict[i] to y_dict[i+1]-1 do y2n[j]:=i;

   for i:=1 to x_len do x2len[i]:=x_dict[i+1]-x_dict[i];   
   for i:=1 to y_len do y2len[i]:=y_dict[i+1]-y_dict[i];
   
{   for i:=1 to y_len do Write(y_dict[i],' ');
   Writeln;}

   for i:=1 to n do begin
      x1:=r[i,1]; y1:=r[i,2];
      x2:=r[i,3]; y2:=r[i,4];

      x1:=x2n[x1]; y1:=y2n[y1];
      x2:=x2n[x2-1]; y2:=y2n[y2-1];

      {TODO tu bedzie zle trzeba poprawic}
      
{      if (x1>=x2) then continue;
      if (y1>=y2) then continue;      }

      for x:=x1 to x2 do
	 for y:=y1 to y2 do 
	    b[x,y]:=true;      
   end;


   area:=0;
   for i:=1 to x_len do
      for j:=1 to y_len do if (b[i,j]) then begin
	 area:=area+(x2len[i]*y2len[j]);
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
