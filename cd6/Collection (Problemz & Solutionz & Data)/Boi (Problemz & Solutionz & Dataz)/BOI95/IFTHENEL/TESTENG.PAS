program tester; { 1.6, BOI'95 }

  uses  crt;
  type  tvalue = record
                   on  : boolean;
                   mis : real;
                 end;
        trida  = record
                   nr        : integer;
                   washere   : boolean;
                   case what : boolean of  {true - condition; false - return}
                     true    : (v1, v2 : char; th, el : integer;);
                     false   : (ret : integer;)
                 end;
  const vigu   = 4;
        veateade : array [0..vigu] of string=(
                  'More than one value for variable  ',
                  'No value for variable ',
                  'Wrong value, must be: ',
                  'Executing cycles by such values',
                  'The same values from different combinations');
  var pread        : array [1..20] of trida;
      ridu, vaidab : integer;
      vaart        : array ['a'..'z'] of tvalue;
      vaitskl      : boolean;
      testfnimi    : string;
      viga         : word;
      veainfo      : array [0..vigu] of string [10];
      kasutab      : array ['a'..'z'] of boolean;

  procedure sisestus;
    var sf    : text;
        rida  : string;
        sp    : integer;
        dummy : integer;
  begin
    for dummy := ord('a') to ord('z')
        do kasutab[chr(dummy)] := false;
    ridu := 0;
    write ('Enter input (data) file name ? ');
    readln (testfnimi);
    assign (sf, testfnimi);
    reset (sf);
    while not eof (sf) do
      begin
        read (sf, rida);
        if not eof (sf)
           then readln (sf);
        inc (ridu);
        sp := pos (' ', rida);
        val (copy (rida, 1, sp - 1), pread[ridu].nr, dummy);
        delete (rida, 1, sp);
        while rida[1]=' ' do
              delete (rida, 1, 1);
        if upcase (rida[1]) = 'R'
           then begin
                  pread[ridu].what := false;
                  delete (rida, 1, 7);
                  sp := pos (')', rida);
                  val (copy (rida, 1, sp - 1), pread[ridu].ret, dummy);
                end
           else begin
                  delete (rida, 1, 3);
                  while rida[1] = ' ' do
                    delete (rida, 1, 1);
                  pread[ridu].what := true;
                  pread[ridu].v1 := rida[1];
                  pread[ridu].v2 := rida[3];
                  kasutab[rida[1]] := true;
                  kasutab[rida[3]] := true;
                  delete (rida, 1, 4);
                  while rida[1] = ' ' do
                    delete (rida, 1, 1);
                  delete (rida, 1, 4);
                  while rida[1]=' ' do
                    delete (rida, 1, 1);
                  sp := pos (' ', rida);
                  val (copy (rida, 1, sp - 1), pread[ridu].th, dummy);
                  delete (rida, 1, sp);
                  while rida[1] = ' ' do
                    delete(rida, 1, 1);
                  delete (rida, 1 ,4);
                  while rida[1] = ' ' do
                    delete (rida, 1, 1);
                  val (rida, pread[ridu].el, dummy);
                end;
      end;
    close (sf);
  end;

  function jahei (j, e : char) : boolean;
    var c : char;
  begin
    repeat
      c := readkey;
    until upcase(c) in [upcase(j), upcase(e)];
    jahei := (upcase(c) = upcase(j));
    writeln;
  end;

  function testbitt (arv : word; nr : byte) : boolean;
  begin
    testbitt := ((arv and (1 shl nr)) <> 0);
  end;

  procedure tostabitt (var arv : word; nr : byte);
  begin
    arv := arv or (1 shl nr);
  end;

  function margend (rnr : integer) : integer;
    var i : integer;
  begin
    for i := 1 to ridu do
        if pread[i].nr = rnr
           then margend := i;
  end;

  var kysitud : boolean;
  function kysi (x : char; c : boolean) : boolean;
  begin
    tostabitt (viga, 1);
    veainfo[1] := x;
    if not c
       then begin
              write('Value for ',x,' is missing. Enter it manually? (Y/N)');
              if jahei ('y', 'n')
                 then begin
                        kysitud := true;
                        write ('What is it? ');
                        readln (vaart[x].mis);
                        vaart[x].on := true;
                        kysi := true;
                      end
                 else kysi := false;
            end
       else kysi := false;
  end;

  procedure tootlus;
    label 1, 2, 3;
    var sf, vf                           : text;
        cont, tsyklisse, koma, antudtskl : boolean;
        orida, vrida, vr2                : string;
        dummy, sp, i, comesout, antudarv : integer;
        onantud                          : array[1..100] of integer;
  begin
    antudarv := 0;
    antudtskl := false;
    for i := 0 to vigu do
        veainfo[i] := '';
{$I-}
    assign (sf, 'OUTPUT.TXT');
    reset (sf);
{$I+}
    if IOResult > 0 then
      begin
      Writeln('Can not find file OUTPUT.TXT!');
      halt;
      end;
    assign (vf, 'OUTPUT.TES');
    rewrite (vf);
    write ('Test whole output file together? (Y/N)');
    cont := jahei ('y', 'n');
    while not eof (sf) do
      begin
        viga := 0;
        readln (sf, orida);
        read (sf, vrida);
        if not eof (sf)
           then readln (sf);
        if not cont
           then begin
                  writeln;
                  writeln (orida);
                  writeln (vrida);
                  write ('Do you want to enter these lines by hand? (Y/N)');
                  if jahei('y', 'n')
                     then begin
                            write ('What''s the result? ');
                            readln (orida);
                            write ('And the values? ');
                            readln (vrida);
                          end;
                end;
        vr2 := vrida;
  2 :   if (orida[1] in ['0'..'9']) or
           ((orida[1] = '-') and (orida[2] in ['0'..'9']))
           then begin
                  vaitskl := false;
                  val (orida, vaidab, dummy);
                  if dummy <> 0
                     then val (copy (orida, 1, dummy - 1), vaidab, dummy);
                end
           else vaitskl := true;
        if vaitskl
           then if antudtskl
                  then tostabitt (viga, 4)
                  else antudtskl := true;
        if not vaitskl
           then begin
                  inc (antudarv);
                  onantud[antudarv] := vaidab;
                  i := 1;
                  for i := 1 to antudarv - 1 do
                      if vaidab = onantud[i]
                         then begin
                                tostabitt (viga, 4);
                                dec (antudarv);
                                goto 3;
                              end;
   3 :          end;
        for i := ord('a') to ord ('z') do
            vaart[chr(i)].on := false;
        while (length (vrida) > 0) and (not (vrida[1] in ['a'..'z'])) do
          delete (vrida, 1, 1);
        while length (vrida) > 0 do
          begin
            i := ord (vrida[1]);
            if vaart[chr(i)].on
               then begin
                      tostabitt (viga, 0);
                      veainfo[0] := chr(i);
                    end;
            vaart[chr(i)].on := true;
            sp := pos ('=', vrida);
            delete (vrida, 1, sp);
            while vrida[1] = ' ' do
              delete (vrida, 1, 1);
            val (vrida, vaart[chr(i)].mis, dummy);
            if dummy <> 0
               then val (copy (vrida, 1, dummy-1), vaart[chr(i)].mis, dummy);
            while (length (vrida) > 0) and (not (vrida[1] in ['a'..'z'])) do
              delete (vrida, 1, 1);
          end;
        for i := ord('a') to ord ('z') do
            if kasutab[chr(i)] and (not vaart[chr(i)].on)
               then begin
                      tostabitt (viga, 1);
                      veainfo[1] := chr(i);
                    end;
        kysitud:=false;
        for i := 1 to ridu do
            pread[i].washere := false;
        i := 1;
        tsyklisse := false;
        comesout := 0;
        repeat
          if pread[i].washere
             then begin
                    tsyklisse := true;
                    goto 1;
                 end
             else if not pread[i].what
                     then begin
                            comesout := pread[i].ret;
                            goto 1;
                         end
                     else begin
                            pread[i].washere := true;
                            if (not vaart[pread[i].v1].on)
                               and (not kysi(pread[i].v1,cont))
                               then begin
                                      tsyklisse := true;
                                      comesout := 1;
                                      goto 1;
                                    end;
                            if (not vaart[pread[i].v2].on)
                               and (not kysi(pread[i].v2, cont))
                               then begin
                                      tsyklisse := true;
                                      comesout := 1;
                                      goto 1;
                                    end;
                            if vaart[pread[i].v1].mis =
                               vaart[pread[i].v2].mis
                               then i := margend (pread[i].th)
                               else i := margend(pread[i].el);
                          end;
        until false;
  1 :   if not vaitskl
           then writeln (vf, vaidab, ':')
           else writeln (vf, 'Cycling:');
        koma := false;
        for i := ord ('a') to ord ('z') do
            if vaart[chr(i)].on
               then begin
                      if koma
                         then write (vf,',')
                         else koma := true;
                      if vaart[chr(i)].mis = round (vaart[chr(i)].mis)
                        then write (vf, chr(i),'=', round(vaart[chr(i)].mis))
                        else write (vf, chr(i),'=', vaart[chr(i)].mis);
                    end;
        writeln (vf);
        writeln (vf, 'Comments: ');
        if not (tsyklisse and (comesout = 1))
           then begin
                  if tsyklisse and (not vaitskl)
                     then begin
                            tostabitt (viga, 2);
                            veainfo[2] := 'Cycling;'
                          end;
                  if (not tsyklisse) and (vaitskl or (comesout <> vaidab))
                     then begin
                            tostabitt (viga, 2);
                            str (comesout, veainfo[2]);
                          end
                end
           else tostabitt (viga, 3);
        if viga = 0
           then writeln (vf, 'OK'#13#10)
           else begin
                  for i := 0 to vigu do
                      if testbitt (viga, i)
                         then writeln (vf, veateade[i],veainfo[i]);
                  writeln (vf);
                end;
        if kysitud
           then begin
                  writeln ('A value for a variable was entered manually');
                  writeln ('Do you wish to test the same answer again?');
                  write ('for example, for entering some other value');
                  writeln (' for that variable...(Y/N)');
                  if jahei ('y', 'n')
                     then begin
                            viga := 0;
                            vrida := vr2;
                            goto 2;
                          end;
                end;
      end;
    close(sf);
    close(vf);
  end;
begin
  Writeln('This program was used for checking the values of variables,');
  Writeln('only when the structure of output file and the RETURN values were correct.');
  Writeln('Do not use by obviously wrong output!');
  sisestus;
  tootlus;
end.