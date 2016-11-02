program currency; { 1.1, BOI'95 }

  const SIZE = 20;                          { the maximum size of the table }
  type table = array [1..SIZE, 1..SIZE] of real;

  procedure input (var n : integer;                { real size of the table }
                   var t : table);
  var f    : text;
      fn   : string;
      i, j : integer;
  begin
    write ('Input file name: ');
    readln (fn);
    assign (f, fn);
    reset (f);
    readln (f, n);
    for i := 1 to n do
      for j := 1 to n do
        read (f, t[i, j]);
    close (f)
  end;

  procedure CompleteTable (n : integer;            { real size of the table }
                           var t : table);
    var i, j, x : integer;
        changed : boolean;
  begin
    for i := 1 to n do                            { completing the diagonal }
      if t[i, i] = 0
         then t[i, i] := 1.00;
    changed := true;
    while changed do       { if some numbers were rebuild we have to rewiew }
      begin                { the table once more }
        changed := false;
        for i := 1 to n do
          for j := 1 to n do
            if t[i, j] = 0                         { found a missing number }
               then begin                        { and trying to rebuild it }
                      if t[j, i] <> 0
                         then t[i, j] := 1 / t[j, i]
                         else for x := 1 to n do
                                if (t[i, x] <> 0) and (t[x, j] <> 0)
                                    then t[i, j] := t[i, x] * t[x, j];
                      changed := changed or (t[i, j] <> 0)
                    end                               { have we succeeded ? }

      end
  end;

  procedure output (n : integer; t : table);
    var f    : text;
        i, j : integer;
  begin
    assign (f, 'OUTPUT.TXT');
    rewrite (f);
    for i := 1 to n do
      begin
        for j := 1 to n do
          write (f, trunc (t [i,j] * 100) / 100 : 6 : 2);
        writeln (f)
      end;
    close (f)
  end;

  var t : table;
      n : integer;
begin
  input (n, t);
  CompleteTable (n, t);
  output (n, t)
end.


