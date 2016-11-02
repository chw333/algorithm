program spiral_of_rectangles; { 1.4, BOI'95 }
  { by M.Opmanis, 1997 }

  uses crt;
  type point = record
                 x, y : real;
               end;
  var  v          : array [1..4] of point;
       number,i   : integer;
       k, xx, yy  : real;
       inp, out   : text;
       inp_f_name : string;

  function in_rectangle (xq, yq : real) : boolean;
  begin
    if ((xq - v[1].x) * (xq - v[4].x) <= 0) and
       ((yq - v[1].y) * (yq - v[2].y) <= 0)
       then in_rectangle := true
       else in_rectangle := false;
  end;

begin
  write ('Input file name => ');
  readln (inp_f_name);
  assign (inp, inp_f_name);
  reset (inp);
  readln (inp, k, xx, yy);
  close (inp);
  v[1].x := 0; v[1].y := 0;
  v[2].x := 0; v[2].y := 1;
  v[3] := v[2];
  v[4] := v[1];
  number := 0;
  repeat
    case ((number mod 4 ) + 1) of
     1 : begin
           v[1].x := v[1].x + (v[2].y - v[1].y) * k;
           v[2].x := v[1].x;
         end;
     2 : begin
           v[2].y := v[2].y + (v[2].x - v[3].x) * k;
           v[3].y := v[2].y;
         end;
     3 : begin
           v[3].x := v[3].x - (v[2].y - v[1].y) * k;
           v[4].x := v[3].x;
         end;
     4 : begin
           v[4].y := v[4].y - (v[2].x - v[3].x) * k;
           v[1].y := v[4].y;
         end;
    end; { case }
    inc (number);
  until In_rectangle(xx,yy);
  assign (out, 'OUTPUT.TXT');
  rewrite (out);
  writeln (out, number);
  close (out);
end.

