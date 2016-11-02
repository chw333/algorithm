{test generator}
program margen;
const
   maxn	= 10000;
   maxx	= 30000;
   task_id = 'mar';
var
   img : boolean;
   n   : integer;
   r   : array[1..maxn,1..4] of integer;

procedure error(s : string);
begin
   Writeln(s);
   readln;
   halt(1);
end;
	   

procedure init;
begin
   n:=0;
   fillchar(r,sizeof(r),0);
end; { init }

procedure check;
var
   i,j : integer;
begin
   if (n<1) or (n>maxn) then error('bad n value');
   for i:=1 to n do
   begin
      for j:=1 to 4 do if (r[i,j]<0) or (r[i,j]>maxx) then error('bad points');
      if (r[i,1]>=r[i,3]) or
	 (r[i,2]>=r[i,4]) then error('bad rectangle');
   end;
end; { check }

procedure write_test(no	: string);
var
   f : text;
   i : integer;
begin
   check;
   Assign(f,'../in/'+task_id+no+'.in');
   rewrite(f);
   Writeln(f,n);
   for i:=1 to n do begin
      Writeln(f,r[i,1],' ',r[i,2],' ',r[i,3],' ',r[i,4]);
   end;
   close(f);
end; { write_test }

procedure set_r(no : integer;x1,y1,x2,y2:integer);
begin
   r[no,1]:=x1;
   r[no,2]:=y1;
   r[no,3]:=x2;
   r[no,4]:=y2;   
end;

procedure simple1;
begin
   n:=4;
   set_r(1,1,1,100,100);
   set_r(2,50,50,200,70);
   set_r(3,20,20,21,24);
   set_r(4,20,19,110,150);
end; { simple1 }

procedure simple2;
begin
   n:=7;
   set_r(1,1,1,100,100);
   set_r(2,50,50,150,150);
   set_r(3,100,100,200,200);
   set_r(4,1,1,500,20);
   set_r(5,1,1,20,500);
   set_r(6,95,92,124,115);
   set_r(7,95,45,130,55);   
end; { simple1 }

procedure boi;
begin
   n:=13;
   {B}
   set_r(1,100, 100, 350,5000);
   
   set_r(2,100, 100,1200,  300);
   set_r(3,100,2500,1200, 2600);
   set_r(4,100,4900, 1000,5000);

   set_r(5,1000,100,1200,2575);
   set_r(6,900,2500,1100,5000);

   {O}
   set_r(7,2000, 100, 2200,5000);
   set_r(8,3000, 100, 3200,5000);

   set_r(9,2000, 100, 3200,300);
   set_r(10,2000, 4900, 3200,5000);   
     
   {I}
   set_r(11,4000,100,4300,5000);
   set_r(12,3700,100,4600,300);
   set_r(13,3700,4900,4600,5000);      
end;

procedure snail(size : integer);
var
   i   : integer;
   s   : integer;
   x,y : integer;
   w,h : integer;
begin
   n:=size;
   if (img) then n:=n div 10;
   if (n mod 4<>0) then n:=((n div 4)+1)*4;
   s:=(maxx div n)-1;
   
   x:=0;y:=maxx;
   w:=maxx;h:=maxx;
   
   for i:=1 to n div 4 do begin
      set_r(4*i-3,x,y-h,x+s,y);
      set_r(4*i-2,x,y-h,x+w,y-h+s);
      set_r(4*i-1,x+w-s,y-h,x+w,y-2*s);
      set_r(4*i  ,x+2*s,y-3*s,x+w,y-2*s);
      x:=x+2*s;
      y:=y-2*s;
      w:=w-4*s;
      h:=h-4*s;
   end;
end;

procedure rand(size : integer);
var
   x,y	 : integer;
   xx,yy : integer;
   i	 : integer;
begin
   n:=size;
   if (img) then begin
      n:=n div 2;
      if (n>100) then n:=100;
   end;
      
   set_r(1,0,1,maxx,2);
   set_r(2,1,0,2,maxx);
   
   for i:=3 to size do
   begin
      x:=random(maxx-1);
      y:=random(maxx-1);
      xx:=x+1+random(maxx-x);
      yy:=y+1+random(maxx-y);
      set_r(i,x,y,xx,yy);
   end;
end; { rand }

procedure bars(size:integer);
var
   i	   : integer;
   s,n0,n1 : integer;
begin
   n:=size;
   if (img) then n:=n div 400;
   s:=maxx div (2*n);
   
   n0:=n div 2;
   n1:=n-n0;
   for i:=1 to n0 do begin
      set_r(i,0,2*s*(i-1),maxx,2*s*(i-1)+s);
   end;
   for i:=1 to n1 do begin
      set_r(n0+i,2*s*(i-1),0,2*s*(i-1)+s,maxx);
   end;   
end; { bars }

procedure ix(size : integer);
var
   n0,n1 : integer;
   i	 : integer;
   s	 : integer;
   w	 : integer;
begin
   n:=size;
   if (img) then n:=n div 100;
   
   n0:=n div 2;
   n1:=(n-n0);
   s:=(maxx div n);
   w:=(maxx*2) div 5;
   for i:=1 to n0 do set_r(i,(i-1)*s,(i-1)*s,(i-1)*s+w,(i-1)*s+w);
   for i:=1 to n1 do set_r(n0+i,(i-1)*s,maxx-(i-1)*s-w,(i-1)*s+w,maxx-(i-1)*s);   
end;

procedure squares(size :integer) ;
var
   i,n0,n1 : integer;
   s	   : integer;
begin
   n:=size;
   if (img) then n:=n div 400;

   s:=maxx div (2*n+10);
   
   n0:=n div 2;
   n1:=(n-n0);
   for i:=1 to n0 do begin
      r[i,1]:=(i-1)*s;
      r[i,2]:=(i-1)*s;
      r[i,3]:=2*n0*s-i*s;
      r[i,4]:=2*n0*s-i*s;
   end;
   for i:=1 to n1 do begin
      r[n0+i,1]:=2*n0*s+2*s+(i-1)*s;
      r[n0+i,2]:=s*(i-1);
      r[n0+i,3]:=2*n0*s+2*s+2*n1*s-(i-1)*s;
      r[n0+i,4]:=2*s*n1-(i-1)*s;
   end;
end;

procedure romb(size :integer) ;
var
   i,y0,x,y : integer;
   s	    : integer;
begin
   n:=size;
   if (img) then n:=n div 800;

   x:=1;
   y:=maxx div 2;
   y0:=y;
   s:=maxx div (2*n+3);
   for i:=1 to n do begin
      r[i,1]:=x;r[i,2]:=y;
      r[i,3]:=maxx-s*(i-1);r[i,4]:=y0+i*s;
      inc(x,s);
      dec(y,s);      
   end;
end;

procedure make;
var
   i   : integer;
   i_s : string;
begin
   for i:=1 to 10 do begin
      Writeln('i=',i);
      init;
      case i of
	1 : simple1;
	2 : simple2;	
	3 : boi;	
	4 : rand(100);
	5 : snail(200);
	6 : rand(1000);		
	7 : ix(2000);
	8 : bars(5000);
	9 : squares(maxn);
	10 : romb(maxn);
      else begin
	 error('unknown test');
      end;
      end; { case }

      Str(i,i_s);
      write_test(i_s);
   end;
end;


begin
   randseed:=12456;
   img:=false;
   if (paramcount>0) and (paramstr(1)='img') then img:=true;
   randomize;
   make;
end.