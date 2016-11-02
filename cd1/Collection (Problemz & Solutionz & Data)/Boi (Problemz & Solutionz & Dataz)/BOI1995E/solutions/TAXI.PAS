program taxi; { 1.5, BOI'95 }

  const MAX_D = 10;         { the maximum distance an express taxi can drive
                               without stop }
        MAX_K = 100;     { the maximum distance the passenger may want to go }
  type costs = array [1..MAX_D] of integer;
       route = array [1..MAX_D] of 0..MAX_K;

  procedure input (var c : costs;     { driving cost table }
                   var d : integer    { the distance } );
    var f  : text;
        fn : string;
        i  : integer;
  begin
    write ('Input file name: ');
    readln (fn);
    assign (f, fn);
    reset (f);
    for i := 1 to MAX_D do
        read (f, c[i]);
    readln (f, d);
    close (f)
  end;

  procedure journey (c : costs;                     { driving cost table }
                     d : integer;                   { the distance to go }
                     var r : route;
                     var min : integer { the minimum cost of the journey } );
    var cheap   : array [0..MAX_K] of integer;
                             { the cheapest cost of driving k kilometers }
        NoStop : array [0..MAX_K] of 0..MAX_D; { the distance to be gone  }
                                    { without stop after the last change }
        max, i, j, k : integer;
  begin
    cheap[0] := 0;                                       { fictious cost }
    NoStop[0] := 0;
    cheap[1] := c[1]; NoStop[1] := 1;
    for k := 2 to d do                               { filling the table }
        begin
          if k > 10 then max := 10
                    else max := k;
          NoStop[k] := max;                              { initial value }
          cheap[k] := cheap[k-max] + c[max];
          for j := max - 1 downto 1 do
              if cheap[k] > cheap[k-j] + c[j]
                 then begin { searching for lower cost to go k kilometers }
                        cheap[k] := cheap[k-j] + c[j];
                        NoStop[k] := j
                      end
        end;
    min := cheap[d];                       { minimal cost of the journey }
    for i := 1 to 10 do
        r[i] := 0;
    j := d;
    repeat                                       { we will trace a route }
       r[NoStop[j]] := r[NoStop[j]] + 1;
       j := j - NoStop[j]
    until j = 0
  end;

  procedure output (c : costs; r : route;
                    min : integer   { the mimimum cost of the journey });
    var f    : text;
        i, j : integer;
  begin
    assign (f, 'OUTPUT.TXT');
    rewrite (f);
    for i := 1 to MAX_D do
      for j := 1 to  r[i] do
          writeln (f, i, ' ', c[i]);
    writeln (f, min);
    close (f)
  end;

  var c      : costs;
      r      : route;
      d, min : integer;
begin
  input (c, d);
  journey (c, d, r, min);
  output (c, r, min)
end.

