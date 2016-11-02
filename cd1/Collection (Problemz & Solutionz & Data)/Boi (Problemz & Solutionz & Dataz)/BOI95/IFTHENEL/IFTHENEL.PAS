{$m 65000,0,655000}
program ifthenelse; { 1.6, BOI'95 }
  { made by R. Prank }

  uses crt, dos;
  type valvector = array ['a'..'z'] of integer;
  var  nlines, eqpos, i              : integer;
       sisend, valjund               : text;
       sisnimi, variables, foundres  : string;
       progline                      : array [1..20] of string;
       values                        : valvector;
       abi, m                        : char;
       tund, minut, sekund, sajandik : word;

  function find_labl (labl : string) : integer;
    var i : integer;
  begin
    if labl = ''
       then find_labl := 1
       else for i := 1 to nlines do
                if pos(labl, progline[i]) = 1
                   then find_labl := i;
  end;

  function argument (whats : string; linenr : integer) : string;
    var tail : string;
  begin
    tail := copy (progline[linenr], pos (whats, progline[linenr])
                + length (whats) + 1, 80);
    if pos (')', tail) > 0
       then delete (tail, pos (')', tail), 80);
    if pos (' ', tail) > 0
       then argument := copy (tail, 1, pos (' ', tail) - 1)
       else argument := tail;
  end;

  function aresound (var values : valvector;
                     negats, neweq : string) : boolean;
    var l, disappearing : integer;
        m               : char;
  begin
    aresound := true;
    if pos ('=', neweq) > 0
       then begin
              disappearing := values[neweq[3]];
              for m := 'a' to 'z' do
                  if values[m] = disappearing
                     then values[m]  := values[neweq[1]];
              for l := 1 to length (negats) do
                  if negats[l] = '#'
                     then
                       if values[negats[l - 1]] = values[negats[l + 1]]
                          then begin
                                 aresound := false;
                                 exit
                               end;
            end;
    if pos ('#', neweq) > 0
       then if values[neweq[1]] = values[neweq[3]]
               then aresound := false;
   end;

  procedure branches (labl : string; values : valvector;
                      negats, way : string);
    var linenr, i, disappearing : integer;
        confirm, negati         : string[3];

    procedure printvars;
      var i : integer;
    begin
      for i := 1 to length (variables) - 1 do
          write (valjund, variables[i], '=', values[variables[i]], ',');
      if variables = ''
         then write (valjund, 'no variables')
         else write (valjund, variables[length (variables)], '=',
                     values[variables[length (variables)]]);
      writeln (valjund);
    end;

  begin
    linenr := find_labl (labl);
    if pos  ('IF', progline[linenr]) > 0
       then
         begin
           confirm := argument ('IF', linenr);
           negati := argument ('IF', linenr);
           negati[2] := '#';
           if aresound (values, negats, negati)
             then if (pos (argument ('ELSE', linenr), way) = 0)
                    then branches (argument('ELSE', linenr), values,
                                   negats + negati,
                                   way + argument ('ELSE', linenr) + ',')
                    else if pos ('tsy', foundres) = 0
                            then begin
                                   writeln(valjund,'cycling:');
                                   foundres := foundres + 'tsy,';
                                   printvars;
                                 end;
           if aresound (values, negats, confirm)
              then if (pos (argument ('THEN', linenr), way) = 0)
                      then begin
                             disappearing := values[confirm[3]];
                             for m := 'a' to 'z' do
                                 if values[m] = disappearing
                                    then values[m] := values[confirm[1]];
                             branches (argument ('THEN', linenr), values,
                                       negats,
                                       way + argument('THEN', linenr) + ',');
                           end
                      else if pos ('tsy', foundres) = 0
                                  then begin
                                         writeln(valjund,'cycling:');
                                         foundres := foundres + 'tsy,';
                                         printvars;
                                       end;
         end;
    if pos ('RETURN', progline[linenr]) > 0
       then if pos (',' + argument ('RETURN', linenr) + ',', foundres) = 0
               then begin
                      writeln (valjund, argument ('RETURN', linenr), ':');
                      foundres := foundres +
                                  argument ('RETURN', linenr) + ',';
                      printvars;
                    end;
  end;

begin {     main     }
  write ('Input file name: ');
  readln (sisnimi);
  assign (sisend, sisnimi);
  reset (sisend);
  assign (valjund, 'OUTPUT.TXT');
  rewrite (valjund);
  nlines := 0;
  while not eof (sisend) do
    begin
      nlines := nlines + 1;
      readln (sisend, progline[nlines]);
    end;
  if progline[nlines] = ''
     then nlines := nlines - 1;
  close (sisend);
  variables := '';
  foundres := ',';
  for i := 1 to nlines do
      if pos ('=', progline[i]) > 0
         then begin
                eqpos := pos ('=', progline[i]);
                if pos (progline[i, eqpos - 1], variables) = 0
                   then variables := variables + progline [i, eqpos - 1];
                if pos (progline[i, eqpos + 1], variables) = 0
                   then variables := variables + progline[i, eqpos + 1];
                if ord (progline[i, eqpos - 1]) > ord (progline[i, eqpos + 1])
                  then begin
                         abi := progline[i, eqpos - 1];
                         progline[i, eqpos - 1] := progline[i, eqpos + 1];
                         progline[i, eqpos + 1] := abi;
                       end;
              end;
  for m := 'a' to 'z' do
      values[m] := ord(m) - ord('a');
  branches ('', values, '', ', 1, ');
  close (valjund);
end.




