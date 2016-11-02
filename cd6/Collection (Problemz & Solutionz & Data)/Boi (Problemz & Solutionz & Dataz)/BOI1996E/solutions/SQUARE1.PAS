program SQandCI; { 2.1, BOI'96 }
  type nelik = array [0..3] of real;
  var  infailinimi        : string;
       infail, outfail    : text;
       x, y               : nelik;
       cx, cy, r          : real;
       s                  : real;
       ssquare            : array [1..20] of real;
       i, maxlevel, nmaks :integer;

  procedure pindala (x, y : nelik; level : integer);
    var i, j       : integer;
        innumber   : integer;
        newx, newy : nelik;
  begin
    innumber := 0;
    for i := 0 to 3 do
        begin
          if (x[i] - cx) * (x[i] - cx) + (y[i] - cy) * (y[i] - cy) <= r * r
             then innumber := innumber + 1;
        end;
    case innumber of
      4    : s := s + ssquare[level];
      else if level < maxlevel
              then for i := 0 to 3 do
                       begin
                         for j := 0 to 3 do
                             begin
                               newx[j] := (x[j] + x[i]) / 2;
                               newy[j] := (y[j] + y[i]) / 2;
                             end;
                         if (innumber > 0) or
                            (r < abs (x[0] + y[0] - x[1] - y[1]))
                            then pindala (newx, newy, level + 1);
                       end
              else s := s + ssquare[level] / 2;            { * innumber / 4 }
    end;
  end;

begin                                                      {      main      }
  writeln ('Problem 1: a square and a circle');
  write ('Input file name: ');
  readln (infailinimi);
  assign (infail, infailinimi);
  reset(infail);
  readln (infail, x[1], y[1]);
  readln (infail, x[3], y[3]);
  readln (infail, cx, cy, r);
  close (infail);
  writeln ('This program solves the program approximately... ');
  writeln;
  writeln ('     Choose a positive number from the interval [10..25] ');
  writeln ('The bigger number you choose, the more precisely will be the ');
  writeln ('result, but.. the program will run longer .');
  writeln;
  write ('     Enter the number: ');
  readln (maxlevel);
  x[2] := x[1] + (x[3] - x[1]) / 2 + (y[1] - y[3]) / 2;
  y[0] := y[1] + (y[3] - y[1]) / 2 + (x[1] - x[3]) / 2;
  x[0] := x[1] + (x[3] - x[1]) / 2 - (y[1] - y[3]) / 2;
  y[2] := y[1] + (y[3] - y[1]) / 2 - (x[1] - x[3]) / 2;
  ssquare[1] := (x[0] - x[1]) * (x[0] - x[1]) + (y[0] - y[1]) * (y[0] - y[1]);
  for i := 1 to 15 do
      ssquare[i + 1] := ssquare[i] / 4;
  s := 0;
  nmaks := 0;
  pindala (x, y, 1);
  assign (outfail, 'OUTPUT.TXT');
  rewrite (outfail);
  writeln(outfail, s : 8 : 2);
  close (outfail);
end.
