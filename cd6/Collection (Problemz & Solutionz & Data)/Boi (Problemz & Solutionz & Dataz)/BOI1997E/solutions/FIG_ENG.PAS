{$B-}
program figures; { 3.6, BOI'97 }

  uses dos;
  type situat = array [1..8, 1..8] of byte;  { 0-out, 1-in, 2-not fixed yet }
       pair   = array [0..1] of byte;
  var inname                                     : string;
      infile, outfile                            : text;
      l, h                                       : integer;
      needed, put, nulle, colorsontable          : pair;
      numb, numb4                                : longint;
      i, j, beginn, left, right, upper, lowbound : integer;
      a                                          : situat;
      sort                                       : byte; { 0-black, 1 white }

  function miin (x, y : byte) : byte;
  begin
    if x < y
       then miin := x
       else miin := y;
  end;

  function colo (i, j : byte) : byte;
  begin
    colo := (i + j) mod 2;
  end;

  procedure buildfig (a : situat; i0, j0 : byte; put, nulle : pair;
                      left, right, upper : byte);
    var newput, newnulle : pair;
        i, j, sort, newi0, newj0, addit : byte;
    label lisamine;
  begin
    if (put[0] > needed[0]) or (put[1] > needed[1])
       then exit;
    if (colorsontable[0] - nulle[0] < needed[0]) or
       (colorsontable[1] - nulle[1] < needed[1])
       then exit;
    if (put[0] = needed[0]) and (put[1] = needed[1])
       then begin
              if left > 2
                 then exit;
              addit := 4;   { if impossible to turn 90 grades and not symmetr. }
              if lowbound = 2
                 then begin
                        if (right < l) or (left > 1) or
                           (colo (right, upper) = 0)
                           then exit;    { then no need to start from row 2 }
                        if (l <= h) and
                           ((colo (upper, 1) = 0) and (upper - 1 <= l)
                             or (colo (upper, 1) = 1) and (upper <= l))
                            or ((l <= h - 1) and (colo (upper, 1) = 1)
                                and (upper - 1 = l))
                           then addit := addit div 2;
                        for i := lowbound to  1 + (upper div 2) do
                          for j := 1 to l do
                            if (a[i, j] - a[upper-i+2, l-j+1]) mod 2  <> 0
                               then begin
                                      addit := addit div 2;
                                      goto lisamine;
                                    end;
                      end;
              if lowbound = 1
                 then
                   case left of
                     1 : begin
                           if ((colo (upper, 1) = 0) or (colo (1, right) = 0))
                              and (right <= h) and (upper <= l)
                              or ((colo (upper, 1) = 1)
                                  or (colo (1, right) = 1))
                              and ((upper <= l - 1) and (right <= h)
                                   or (upper = l) and (right <= h - 1)
                                   and (colo(1, right) = 1))
                              then addit := addit div 2;
                           case colo (upper, right) of
                             0 : for i := 1 to (upper + 1) div 2 do
                                   for j := 1 to right do
                                     if (a[i, j] - a[upper-i+1, right-j+1])
                                         mod 2 <> 0
                                         then begin
                                                addit := addit div 2;
                                                goto lisamine;
                                              end;
                           end;
                         end;
                     2 : begin
                           if colo (upper, right) = 0
                              then exit;
                           if ((colo (upper, 2) = 0) or (colo(1, right) = 0))
                              and (upper <= l) and (right - 1 <= h)
                              or (colo (upper, 2) = 1)
                              and ((upper <= l - 1) and (right - 1 <= h)
                                   or (upper = l) and (right <= h))
                              then addit := addit div 2;
                           for i := 1 to (upper + 1) div 2 do
                             for j := 2 to right do
                               if (a[i, j] - a[upper - i + 1, right - j + 2])
                                   mod 2 <> 0
                                  then begin
                                         addit := addit div 2;
                                         goto lisamine;
                                       end
                         end
                   end;
  lisamine :  numb4 := numb4 + addit;
              exit
            end;

    i := i0;
    j := j0;
    repeat
      repeat
        if (a[i, j] = 2) and
           ((i > lowbound) and (a[i - 1, j] = 1)
             or (i < h) and (a[i + 1, j] = 1)
             or (j > 1) and (a[i, j - 1] = 1)
             or (j < l) and (a[i, j + 1] = 1))
           then begin
                  a[i, j] := 0;
                  newnulle := nulle;
                  newnulle[colo(i, j)] := newnulle[colo(i, j)] + 1;
                  buildfig (a, i, j, put, newnulle, left, right, upper);
                  a[i, j] := 1;
                  newi0 := i;
                  newj0 := j;
                  if (i > lowbound) and (a[i - 1, j] = 2)
                     then newi0 := i - 1
                     else if (j > 1) and (a[i, j - 1] = 2)
                             then newj0 := j - 1;
                  newput := put;
                  newput[colo(i, j)] := newput[colo(i, j)] + 1;
                  if j < left
                     then left := j;
                  if j > right
                     then right := j;
                  if i > upper
                     then upper := i;
                  buildfig (a, newi0, newj0, newput, nulle, left, right,
                            upper);
                  exit
                end;
        j := j + 1;
      until j > l;
      i := i + 1;
      j := 1;
    until i > h;
  end;

begin                                                       {      main     }
  assign (infile, 'figures.dat');
  reset (infile);
  read (infile, l, h, needed[0], needed[1]);
  close (infile);
  numb := 0;
  for lowbound := 1 to 2 do
    { lowbound = 2  for figures which are of full length and diagonal main  }
    { corners are white                                                     }
    begin
      colorsontable [colo (lowbound, 1)] := (l * (h - lowbound + 2) div 2);
      colorsontable [colo (lowbound, 2)] := (l * (h - lowbound + 1) div 2);
      for beginn := 1 to l do
        begin
          for i := 1 to h do
              for j := 1 to l do
                a[i, j] := 2;
          for j := 1 to beginn - 1 do
              a[lowbound, j] := 0;
          a[lowbound, beginn] := 1;
          left := beginn;
          right := beginn;
          upper := lowbound;
          for sort := 0 to 1 do
              put[sort] := 0;
          put [colo(lowbound, beginn)] := 1;
          nulle [lowbound - 1] := beginn div 2;
          nulle [2 - lowbound] := (beginn - 1) div 2;
          buildfig (a, lowbound, beginn, put, nulle, left, right, upper);
        end;
    end;                                                     { for lowbound }
  assign (outfile, 'figures.rez');
  rewrite (outfile);
  writeln (outfile, numb4 div 4);
  close (outfile);
end.

