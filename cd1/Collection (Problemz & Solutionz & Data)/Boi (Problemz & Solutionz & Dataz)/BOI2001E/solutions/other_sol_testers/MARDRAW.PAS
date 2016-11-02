{Description: test visualization program (input file into metapost file)}
program mar_draw;
const
   maxn	= 10000;
   maxx	= 30000;
var
   r	    : array[1..maxn,1..4] of integer;
   n	    : integer;
   f	    : text;
   filename : string;
   output   : string;
   m	    : integer;

procedure read_input;
var
   i,j : integer;
begin
   assign(f,filename);
   reset(f);
   readln(f,n);
   for i:=1 to n do readln(f,r[i,1],r[i,2],r[i,3],r[i,4]);
   m:=0;
   for i:=1 to n do
      for j:=1 to n do if (r[i,j]>m) then m:=r[i,j];

   if (m>2000) then 
      for i:=1 to n do
	 for j:=1 to 4 do r[i,j]:=r[i,j] div 10;
   close(f);
end; { read_input }

procedure write_mp;
var
   i : integer;
begin
   assign(f,output);
   rewrite(f);
   Writeln(f,'beginfig(1)');
   if (m<200) then Writeln(f,'u:=10pt;')
   else Writeln(f,'u:=1pt;');
   for i:=1 to n do begin
      Write(f,'draw ');
      Write(f,'(',r[i,1],'*u,',r[i,2],'*u)--');
      Write(f,'(',r[i,1],'*u,',r[i,4],'*u)--');
      Write(f,'(',r[i,3],'*u,',r[i,4],'*u)--');
      Write(f,'(',r[i,3],'*u,',r[i,2],'*u)--');
      Write(f,'(',r[i,1],'*u,',r[i,2],'*u);');
      Writeln(f);
   end;
   Writeln(f,'endfig;');
   Writeln(f,'\bye');
   close(f);
end;


begin
   filename:='mar.in';
   output:='mar.mp';
   if (paramcount>0) then filename:=paramstr(1);
   if (paramcount>1) then output:=paramstr(2);
   
   read_input;
   write_mp;
end.