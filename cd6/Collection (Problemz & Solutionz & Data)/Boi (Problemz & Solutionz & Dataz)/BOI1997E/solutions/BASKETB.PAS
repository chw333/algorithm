program basketball; { 3.1, BOI'97 }

  type team = record
                w, w1 : integer;
                d, p  : longint;
                name  : string [20];
              end;

  var  t    : array [1..300] of team;
       c, n : integer;

  function index (v : string) : integer;
    var i : integer;
  begin
    for i := 1 to c do
        if t[i].name = v
           then begin
                   index := i;
                   exit;
                end;
    inc (c);
    t[c].name := v;
    index := c;
  end;

  procedure ReadInput;
    var j, p1, p2, k1, k2, code : integer;
        v1, v2, s               : string;
        i                       : longint;
  begin
    FillChar (T, SizeOf(T), 0);
    assign (input, 'basket.dat');
    reset (input);
    readln (n);
    c := 0;
    for i := 1 to longint (n) * (n - 1) div 2 do
        begin
          readln (s);
          j := pos ('-', s);
          v1 := copy (s, 1, j - 1);
          delete (s, 1, j);
          k1 := index (v1);
          j := pos(' ', s);
          v2 := copy (s, 1, j - 1);
          delete (s, 1, j);
          k2 := index (v2);
          j := pos (':', s);
          val (copy (s, 1, j - 1), p1, code);
          delete (s, 1, j);
          val (s, p2, code);
          if p1 > p2
             then inc (t[k1].w)
             else inc (t[k2].w);
        end;
    reset (input);
    readln;
    for i := 1 to longint (n) * (n - 1) div 2 do
        begin
          readln (s);
          j := pos ('-', s);
          v1 := copy (s, 1, j - 1);
          delete (s, 1, j);
          k1 := index (v1);
          j := pos (' ', s);
          v2 := copy (s, 1, j - 1);
          delete (s, 1, j);
          k2 := index (v2);
          if t[k1].w = t[k2].w
             then begin
                     j := pos(':', s);
                     val (copy (s, 1, j - 1), p1, code);
                     delete (s, 1, j);
                     val (s, p2, code);
                     if p1 > p2
                        then inc (t[k1].w1)
                        else inc (t[k2].w1);
                     inc (t[k1].d, p1 - p2);
                     inc (t[k2].d, p2 - p1);
                     inc (t[k1].p, p1);
                     inc (t[k2].p, p2);
                  end;
        end;
    close (input);
  end;

  function ok (a, b : team) : boolean;
  begin
    if a.w > b.w
       then begin
              ok := true;
              exit;
            end;
    if a.w < b.w
       then begin
              ok := false;
              exit;
            end;
    if a.w1 > b.w1
       then begin
              ok := true;
              exit;
            end;
    if a.w1 < b.w1
       then begin
              ok := false;
              exit;
            end;
    if a.d > b.d
       then begin
              ok := true;
              exit;
            end;
    if a.d < b.d
       then begin
              ok := false;
              exit;
            end;
    if a.p > b.p
       then ok := true
       else ok := false;
  end;

  procedure sort;
    var i, j, temp : integer;
        ind        : array [1..300] of integer;
  begin
    for i := 1 to n do
      ind[i] := i;
    for i := 1 to n do
        for j := i + 1 to n do
            if not ok (t[ind[i]],t[ind[j]])
               then begin
                      temp := ind[i];
                      ind[i] := ind[j];
                      ind[j] := temp;
                    end;
    assign (output, 'basket.rez');
    rewrite (output);
    for i := 1 to n do
        writeln (t[ind[i]].name);
    close (output);
  end;

begin
  ReadInput;
  sort;
end.