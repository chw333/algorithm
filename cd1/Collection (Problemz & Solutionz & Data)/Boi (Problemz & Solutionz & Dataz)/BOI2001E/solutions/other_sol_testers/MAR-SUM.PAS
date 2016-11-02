{ID: MAR}
{Description: wrong solution!, assumption: area=sum of rectangles}
{Tomasz Walen, 2001.05}
program mar;
const
   f_in	    = 'mar.in';
   f_out    = 'mar.out';
   miny	    = 0;
   maxy	    = 30000;
var
   f	 : text;
   n	 : integer;
   area	 : longint;
	 

procedure read_data;
var
   x1,x2,y1,y2 : longint;
   i	       : integer;
begin
   assign(f,f_in);
   reset(f);
   readln(f,n);

   area:=0;
   for i:=1 to n do begin
      readln(f,x1,y1,x2,y2);
      area:=area+(x2-x1)*(y2-y1);
   end;

   close(f);
end; { read_data }

procedure write_answer;
begin
   assign(f,f_out);
   rewrite(f);
   Writeln(f,area);
   close(f);
end; { write_answer }

begin   
   read_data;
   write_answer;
end.
