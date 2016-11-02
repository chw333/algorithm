{$I+,$R+}
program posgen;
const
   id	= 'pos';
   maxn	= 200;
   maxd	= 8;
   maxm	= maxn*maxd;	   
   maxw	= 1000;
   
var
   n,m : integer;
   w   : array[1..maxn] of integer;
   e   : array[1..maxm,1..2] of integer;
   deg : array[1..maxn] of integer;
   set_no : integer;   
   f   : text;

procedure error(code :string; msg : string);
begin
   Writeln(code);
   Writeln(msg);
   halt(1);
end; { error }

procedure gen_w(no :integer) ;
var
   i  : integer;
   mm : integer;
begin
   mm:=maxw;
   if (no<5) then mm:=100;
   for i:=1 to n do w[i]:=random(mm)+1;
   
   if (no=2) then for i:=1 to n do w[i]:=1;
end; { gen_w }

procedure write_test(no	: integer);
var
   s : string;
   i : integer;
begin
   gen_w(no);
   
   Str(no,s);
   Assign(f,'../in/'+id+s+'.in');
   rewrite(f);
   Writeln(f,n,' ',m);
   for i:=1 to n do Writeln(f,w[i]);
   for i:=1 to m do Writeln(f,e[i,1],' ',e[i,2]);
   close(f);
end; { write_test }

procedure add_edge(a,b : integer);
begin
   if (a<1) or (a>n) then error('ERROR','add_edge bad "a" value');
   if (b<1) or (b>n) then error('ERROR','add_edge bad "b" value');   
   inc(m);
   e[m,1]:=a;
   e[m,2]:=b;
   inc(deg[a]);
   inc(deg[b]);
end; { add_edge }

procedure correct;
var
   i,j : integer;
begin
   {all vertex should've even degree}
{   for i:=1 to n do Write(deg[i],' ');Writeln;}
   j:=-1;
   for i:=1 to n do if (deg[i] mod 2 = 1) then
   begin
      if (j=-1) then j:=i
      else begin
	 add_edge(i,j);
	 j:=-1;	 
      end;
   end;
   if (j<>-1) then begin
      Writeln('BAD EXAMPLE!');
      readln;
      halt(1);
   end;

   { from degree 6 to 8}
   for i:=1 to n do if deg[i]=6 then add_edge(i,i);
end;

procedure shuffle;
var
   i,j,a : integer;
begin
   {shuffling edges}
   for i:=1 to m do begin
      j:=random(m)+1;
      a:=e[i,1];e[i,1]:=e[j,1];e[j,1]:=a;
      a:=e[i,2];e[i,2]:=e[j,2];e[j,2]:=a;      
   end;
end;


{-----}

procedure loop(size : integer);
var
   i : integer;
begin
   n:=size;
   for i:=1 to n do add_edge(i,(i mod n)+1);
   for i:=1 to n do add_edge((i mod n)+1,i);   
   correct;
   shuffle;   
end; { loop }

procedure ladder(size : integer);
var
   i  : integer;
   nn : integer;
begin
   n:=size;
   nn:=size div 2;
   for i:=1 to nn do begin
      add_edge(2*i-1,2*i);
      if (i=1) or (i=nn) then add_edge(2*i,2*i-1);
      if (i<nn) then add_edge(2*i-1,2*i+1);
      if (i<nn) then add_edge(2*i,2*i+2);      
   end;
   correct;
   shuffle;
end; { ladder }

procedure ladder2(size : integer);
begin
   ladder(size);
   add_edge(1,size);
   add_edge(size,size div 2);
   add_edge(1,size div 2);
   correct;
   shuffle;
end;

{flower like graph}
procedure flower(size : integer);
var
   i  : integer;
   j  : integer;
   k  : integer;
   n1 : integer;
   n2 : integer;
begin
   n:=size;
   n1:=size div 4;
   k:=1;
   for i:=1 to 4 do begin
      n2:=n1;
      if (i=4) then n2:=n-3*n1-1;
      
      for j:=1 to n2 do begin
	 inc(k);
	 if (j=1) then add_edge(1,k)
	 else add_edge(k-1,k);
      end;
      add_edge(k,1);
   end;
   correct;
   shuffle;   
end;

procedure rand(size : integer);
var
   tmp : array[1..maxn] of integer;
   i : integer;
   a,b : integer;
begin
   n:=size;
   for i:=1 to n do tmp[i]:=i;
   for i:=1 to n do begin
      a:=random(n)+1;
      b:=tmp[i];tmp[i]:=tmp[a];tmp[a]:=b;
   end;
   for i:=1 to n do add_edge(tmp[i],tmp[(i mod n)+1]);
   for i:=1 to 2*n do begin
      a:=random(n)+1;
      b:=random(n)+1;
      if (a<>b) and (deg[a]<maxd-1) and (deg[b]<maxd-1) then begin
	 add_edge(a,b);
	 add_edge(b,a);
      end;
      if (a=b) and (deg[a]<maxd-1) then add_edge(a,a);
   end;

   correct;
   shuffle;  
end; { rand }

procedure rand2(size : integer);
var
   i : integer;
   a,b : integer;
begin
   n:=size;
   for i:=1 to 2*n do begin
      a:=random(n)+1;
      b:=random(n)+1;
      if (a<>b) and (deg[a]<maxd-2) and (deg[b]<maxd-2) then 
	 add_edge(a,b);
      if (a=b) and (deg[a]<maxd-3) then add_edge(a,a);      
   end;

   for i:=1 to n do add_edge(i,(i mod n)+1);

   correct;
   shuffle;  
end;

begin
   randomize;
   randseed:=12000;
   
   for set_no:=2 to 10 do begin
      n:=0;m:=0;
      fillchar(deg,sizeof(deg),0);
      case set_no of
	2 : rand(10);	
	3 : ladder2(20);
	4 : rand2(40);
	5 : loop(100);
	6 : rand(100);
	7 : flower(120);
	8 : rand2(150);
	9 : ladder(200);
	10 : rand2(200);	
      end; { case }
      write_test(set_no);
   end;
end.