Program Matrix_Cutting;
const
	finame='matrix.inp';
     foname='matrix.out';
{     fsname='matrix.sol';
     frname='matrix.res';}
var
	m,n,x,y:shortint;
     i,j,k,l,sw,bound:shortint;
	adjust:shortint;
     line_x,line_y:Array[0..50] of shortint;
     matrix:array[1..50,1..50] of shortint;
     sum1:array[0..50,1..50] of longint;
     sum:array[1..50,0..50] of longint;
     line:array[1..50,1..50] of shortint;
     max,solution:longint;
     sline_x,sline_y:Array[0..50] of shortint;
     st_time:longint;
function time:longint;
var
	c_time:longint absolute $0040:$006c;
begin
	time:=c_time;
end;
procedure Read_File;
var
	f:text;
begin
	assign(f,finame);
     reset(f);
     readln(f,m,n);
     readln(f,x,y);
     for i:=1 to m do
     	for j:=1 to n do
          	read(f,matrix[i,j]);
end;
procedure printer;
var
	fo:text;
	tot:integer;
begin
	assign(fo,foname);
     rewrite(fo);
     writeln(fo,solution);
     sline_x[0]:=0;
     sline_y[0]:=0;
     sline_x[x+1]:=m;
     sline_y[y+1]:=n;
     for i:=1 to x+1 do
     begin
     	for j:=1 to y+1 do
          begin
              	tot:=0;
			for k:=sline_x[i-1]+1 to sline_x[i] do
               begin
	              	for l:=sline_y[j-1]+1 to sline_y[j] do
                    begin
                    	inc(tot,matrix[k,l]);
                    end;
               end;
               writeln(fo,sline_x[i-1]+1,' ',sline_y[j-1]+1,' ',
 				sline_x[i],' ',sline_y[j],' ',tot);
          end;
     end;
     close(fo);
end;
procedure calculate;
var
     table:array[1..50,1..50] of longint;
     from:array[1..50,1..50] of shortint;
begin
	for i:=1 to x+1 do
     	sum[i,0]:=0;
     for i:=1 to x+1 do
     	for j:=1 to n do
          	sum[i,j]:=sum[i,j-1]+(sum1[line_x[i],j]-sum1[line_x[i-1],j]);
     for i:=1 to n do
     begin
     	table[i,1]:=0;
		for j:=1 to x+1 do
          	if table[i,1]< sum[j,i] then
               	table[i,1]:=sum[j,i];
     end;
	for i:=2 to n do
     begin
     	if i<y+1 then
          	sw:=i
          else
          	sw:=y+1;
     	for j:=2 to sw do
          begin
          	table[i,j]:=maxint;
               for k:=1 to i-1 do
               begin
               	max:=table[k,j-1];
               	for l:=1 to x+1 do
                    begin
                         if sum[l,i]-sum[l,k]>max then
                         	max:=sum[l,i]-sum[l,k];
                    end;
				if max<table[i,j] then
                    	begin
	                        	table[i,j]:=max;
                              from[i,j]:=k;
                         end;
               end;
          end;
	end;
     k:=n;
     for i:=y downto 1 do
     begin
          line_y[i]:=from[k,i+1];
          k:=line_y[i];
     end;
     adjust:=0;
     for i:=1 to x+1 do
     begin
     	for j:=1 to y+1 do
          begin
               if sum[i,line_y[j]]-sum[i,line_y[j-1]]=table[n,y+1] then
               	begin
                    	adjust:=i;
                         break;
                    end;
          end;
          if adjust<>0 then
          	break;
     end;
     if table[n,y+1]<solution then
     	begin
          	solution:=table[n,y+1];
          	for i:=1 to x do
               	sline_x[i]:=line_x[i];
          	for i:=1 to y do
               	sline_y[i]:=line_y[i];
          end;
end;
begin
	randomize;
	Read_File;
	for i:=1 to n do
     	for j:=1 to m do
          	sum1[j,i]:=sum1[j-1,i]+matrix[j,i];
     line_x[0]:=0;
     line_y[0]:=0;
     line_x[x+1]:=m;
     line_y[y+1]:=n;
     solution:=maxint;

     for i:=1 to x do
     	line_x[i]:=trunc((m-1)/x*i);
     st_time:=time;
     repeat
	     calculate;
          if (random<=0.5) and (adjust>1) then
          	line_x[adjust-1]:=
			random(line_x[adjust]-line_x[adjust-2]-1)+1+line_x[adjust-2]
          else if (adjust<=x) then
          	line_x[adjust]:=
			random(line_x[adjust+1]-line_x[adjust-1]-1)+1+line_x[adjust-1];
     until time-st_time>30;
     printer;
end.