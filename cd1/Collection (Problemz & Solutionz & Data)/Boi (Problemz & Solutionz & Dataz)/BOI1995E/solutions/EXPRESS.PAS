program expression; { 1.2, BOI'95 }

  const enough  = 100;
  type  tpowers = array ['a'..'h'] of byte;
        tmember = record
                    ast : tpowers;
                    kor : real;
                  end;
        tvalue  = record
                    given : boolean;
                    what  : real;
                  end;
  var member    : array [1..enough] of tmember;
      liikmeid  : integer;
      vaartus   : real;
      onvaartus : boolean;
      vaart     : array ['a'..'h'] of tvalue;
      avaldis   : string;

  procedure sisestus;
    var i           : char;
        rida, rida2 : string;
        sf          : text;
        dummy       : integer;
  begin
    liikmeid := 0;
    for i := 'a' to 'h' do
        vaart[i].given := false;
    write ('Enter file name: ');
    readln (rida);
    assign (sf, rida);
    reset (sf);
    read (sf, avaldis);
    while true do
      begin
        if eof (sf)
           then exit;
        readln (sf);
        if eof (sf)
           then exit;
        read (sf, rida2);
        vaart[rida2[1]].given := true;
        val (copy (rida2, 3, length(rida2) - 2), vaart[rida2[1]].what, dummy);
      end;
    close(sf);
  end;

  function pow (b : real; e : integer) : real;
    var i : integer;
        v : real;
  begin
    v := 1;
    for i := 1 to e do
        v := v * b;
    pow := v;
  end;

  function eq (a1, a2 : tpowers) : boolean;
    var i : char;
  begin
    eq := true;
    for i := 'a' to 'h' do
        if (a1[i] <> a2[i])
           then eq := false;
  end;

  procedure tootlus;
    var sp           : integer;
        yksliige     : tmember;
        i            : char;
        arvs         : string;
        arv          : real;
        dummy, j     : integer;
        yl           : real;
        onyksvaartus : boolean;
  begin
    if avaldis[1] <> '-'
       then avaldis := '+' + avaldis;
    sp := 1;
    repeat
      if avaldis[sp] = '+'
         then yksliige.kor := 1
         else yksliige.kor := -1;
      inc (sp);
      arvs := '';
      for i := 'a' to 'h' do
          yksliige.ast[i] := 0;
      repeat
        case avaldis[sp] of
          '0'..'9','.' : begin
                           arvs := arvs + avaldis[sp];
                           inc (sp);
                         end;
          'a'..'h'     : begin
                           if arvs <> ''
                              then begin
                                     val (arvs, arv, dummy);
                                     arvs := '';
                                     yksliige.kor := yksliige.kor * arv;
                                   end;
                           inc (yksliige.ast[avaldis[sp]]);
                           inc (sp);
                         end;
          '+', '-'     : if arvs <> ''
                            then begin
                                   val (arvs, arv, dummy);
                                   arvs := '';
                                   yksliige.kor := yksliige.kor * arv;
                                 end;
        end;
      until (avaldis[sp] in ['+','-']) or (sp > length (avaldis));
      if arvs <> ''
         then begin
                val (arvs, arv, dummy);
                arvs := '';
                yksliige.kor := yksliige.kor * arv;
              end;
      for i := 'a' to 'h' do
          if (vaart[i].given) and (yksliige.ast[i] <> 0)
             then begin
                    yksliige.kor := yksliige.kor *
                                    pow (vaart[i].what, yksliige.ast[i]);
                    yksliige.ast[i] := 0;
                  end;
      j := 1;
      while j <= liikmeid do
        if eq (yksliige.ast, member[j].ast)
           then begin
                  member[j].kor := member[j].kor + yksliige.kor;
                  break;
                  j := j + 1;
                end
           else j := j + 1;
      if (liikmeid = 0) or (j > liikmeid)
         then begin
                inc (liikmeid);
                member[liikmeid] := yksliige;
              end
    until sp > length (avaldis);
    vaartus := 0;
    onvaartus := true;
    for j := 1 to liikmeid do
        begin
          yl := member[j].kor;
          onyksvaartus := true;
          for i := 'a' to 'h' do
              if (not vaart[i].given) and (member[j].ast[i] <> 0)
                 then onyksvaartus := false;
          if (not onyksvaartus) and (yl <> 0)
             then begin
                    onvaartus := false;
                    break;
                  end
             else vaartus := vaartus + yl;
        end;
  end;

  procedure valjastus;
    var f : text;
  begin
    assign (f, 'OUTPUT.TXT');
    rewrite (f);
    if onvaartus
      then writeln (f, Round (vaartus))
      else writeln(f, 'UNDEFINED');
    close (f);
  end;

begin
  sisestus;
  tootlus;
  valjastus;
end.

