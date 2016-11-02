program RingJaRuut; { 2.1, BOI'96 }
  type  punkt = record
                  x, y : real;
                end;
  const e     = 0.00001;

  var   filee                           : text;
        p1, p2, p3, p4, o               : punkt;
        a1, a2, s, r, d1, d2, d3, d4, k : real;
        fnimi                           : string;
        between1, between2              : boolean;

  procedure algus;
  begin
    write ('Input file name: ');
    writeln;
    readln (fnimi);
    assign (filee, fnimi);
    reset (filee);
    readln (filee, p1.x, p1.y);
    readln (filee, p3.x,p3.y);
    readln (filee, o.x, o.y, r);
    p2.x := (p3.x + p1.x - p1.y + p3.y) / 2;
    p4.x := (p3.x + p1.x + p1.y - p3.y) / 2;
    p4.y := (p3.y + p1.y - p1.x + p3.x) / 2;
    p2.y := (p3.y + p1.y + p1.x - p3.x) / 2;
  end;

  function min (x1, x2 : real) : real;
  begin
    if x1 < x2
       then min := x1
       else min := x2;
  end;

  function max (x1, x2 : real) : real;
  begin
    if x1 > x2
       then max := x1
       else max := x2;
  end;

  function pdistance (q1, q2 : punkt) : real;     { dist between 2 points }
  begin
    pdistance := sqrt (sqr (q1.x - q2.x) + sqr(q1.y - q2.y))
  end;

  function linedistance (q1, q2, q3 : punkt) : real;
    var a, b1, b2 : real;                     { dist between point and line }
  begin
    b1 := pdistance (q1, q2);
    b2 := pdistance (q1, q3);
    a := (sqr (b1) - sqr (b2) + sqr (k)) / 2 / k;
    linedistance := sqrt (sqr (b1) - sqr (a));
  end;

  function arccos (x : real) : real;
    var u : real;
  begin
    if x = 0
       then u := pi / 2
       else u := arctan (sqrt (1 - sqr (x)) / x);
    if x < 0
       then u := u + pi;
    arccos := u;
  end;

  function integ (x : real) : real;         { integrate f-ni sqrt(r^2-x^2) }
    var u : real;
  begin
    u := (sqrt (sqr (r)-sqr (x)) * x - sqr (r) * arccos (x / r)) / 2;
    integ := u;
  end;

  function sk (d : real) : real;     { part of the circle in one direction }
    var a1, a2, v, u : real;       { of the line, d - distance to the line }
  begin
    if d >= r
       then begin
              sk := 0;
              exit;
            end
       else v := sqrt (sqr (r) - sqr (d));                       { cutpoint }
    if between2
       then begin
              a1 := -min (d2, v);
              a2 := min (d4, v);
            end
       else begin
              a1 := min (v, min (d2, d4));
              a2 := min (v, max (d2, d4));
            end;
    u := integ (a2) - integ (a1) - (a2 - a1) * d;
    { integrate and delete remaining part }
    sk := u;
  end;

begin
  algus;
  k := pdistance (p1, p2);
  d1 := linedistance (o, p1, p2);
  d2 := linedistance (o, p2, p3);
  d3 := linedistance (o, p3, p4);
  d4 := linedistance (o, p4, p1);
  if abs (k - d1 - d3) < e                         { centre between 2 sides }
     then between1 := true;
  if abs (k - d2 - d4) < e
     then between2 := true;
  if between1
     then begin
            if between2
               then begin
                      a1 := -min (d2, r);
                      a2 := min (d4, r);
                    end
               else begin
                      a1 := min (r, min (d2, d4));
                      a2 := min (r, max (d2, d4));
                    end;
            s := 2 * (integ (a2) - integ (a1)) - sk(d1) - sk(d3)
          end
     else s := abs (sk (d1) - sk (d3));
  assign (filee, 'OUTPUT.TXT');
  rewrite (filee);
  write (filee, s : 7 : 2);
  close (filee);
end.