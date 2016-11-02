program moves; { 2.6, BOI'96 }
  uses dos, crt;
  type boolarray = array [1..100] of boolean;
  var  m, n, i, amove, mademove : byte;
       f                   : text;
       name                : string;
       bmove               : array [1..100] of byte;
       wins                : boolean;
       used, result        : boolarray;

  procedure MaksResult (numer, bmove : byte; used : boolarray;
                        var wins : boolean; var goodanswer : byte); forward;

  procedure MinResult (numer, amove : byte; used : boolarray;
                       var wins : boolean;  var badanswer : byte);
    { finds result by worst move of the partner and that move    }
    var bmove, goodanswer : byte;
        winsbranch        : boolean;
  begin
    numer := numer - amove;
    used[amove] := true;
    winsbranch := true;
    for bmove := m downto 1 do
        if not (used[bmove]) and (numer >= bmove)
           then begin
                  MaksResult (numer, bmove, used, winsbranch, goodanswer);
                  if not winsbranch
                     then begin
                            wins := false;
                            badanswer := bmove;
                            exit
                          end;
                end;
    wins := true;
  end;    { MinResult }

  procedure MaksResult (numer, bmove : byte; used : boolarray;
                        var wins : boolean; var goodanswer : byte);
    { finds result by best move of a and such move                }
    var amove, badanswer : byte;
        winsbranch       : boolean;
  begin
    numer := numer - bmove;
    used[bmove] := true;
    winsbranch := false;
    for amove := m downto 1 do
        if not (used[amove]) and (numer >= amove)
           then begin
                  MinResult (numer, amove, used, winsbranch, badanswer);
                  if winsbranch
                     then begin
                            wins := true;
                            goodanswer := amove;
                            exit
                          end;
                end;
    wins := false;
  end;   { MinResult }

begin                                                         {    main    }
  writeln('The program finds after given first move of A');
  writeln('for every first move of B that this move is winning');
  writeln('or shows a winning second move of A');
  write ('Input file name: ');
  readln (name);
  assign (f, name);
  reset (f);
  readln (f, n, m);
  close (f);
  wins := false;
  for i := 1 to m do
      result[i] := true;
  for i := 1 to m do
      used[i] := false;

  write('Move of A:');
  readln (mademove);
  used [mademove] := true;
  for amove := m downto 1 do
      begin
        if used [amove]
           then continue;
        MinResult (n, amove, used, result[amove], bmove[amove]);
        if result[amove]
           then wins:=true;
      end;
  writeln;
  if wins
     then writeln (' B wins')
     else writeln (' A wins');
  for amove := 1 to m do
      begin
        write (amove : 2, '  ');
        if amove = mademove
           then begin
                  writeln;
                  continue
                end;
        if result[amove]
           then writeln ('winning')
           else writeln (bmove[amove]);
      end;

  assign (f, 'OUTPUT.TXT');
  rewrite (f);
  for amove := m downto 1 do
      begin
        MinResult (n, amove, used, result[amove], bmove[amove]);
        if result[amove]
           then wins := true;
      end;
  if wins
     then writeln(f, ' B wins')
     else writeln(f, ' A wins');
  for amove := 1 to m do
      begin
        write(f, amove : 2, ' ');
        if result[amove]
           then writeln(f, 'winning')
           else writeln(f, bmove[amove]);
      end;
  close (f);
end.
