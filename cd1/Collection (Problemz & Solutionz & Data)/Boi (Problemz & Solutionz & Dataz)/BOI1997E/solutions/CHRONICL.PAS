program ancient_chronicles; { 3.5, BOI'97 }
  { by M. Opmanis ,1997 }

  {$IFDEF WINDOWS} uses WinCrt; {$ENDIF}
  const max_id                      = 500;
        max_lo                      = (max_id + 31) div 32;
        zime : array [0..3] of char = ('?', '>', '<', '=');
  type  rinda = array [1..max_lo] of longint;
        koord = record
                  longs : byte;
                  maska : longint;
                end;
  var   ida : array [1..max_id] of string [2];
        a   : array [1..max_id] of rinda;  { in a[i] is stored information  }
                    { about persons who are younger or of the same age as i }
        koordmas                              : array [1..max_id] of koord;
        i, j, cik_tagad_ir, ind1, ind2, n, nn : integer;
        flag                                  : boolean;
        f_in, f_rez                           : text;
        koord_ir                              : koord;
        pazime                                : byte;


  procedure read_next_row (var i1, i2 : integer; var fl : boolean);
    { reads the current row in the format : }
    { <id_2_simbols><sign><id_2_simbols>    }
    var s_id : array [1..2] of string [2];
        zime : string [1];
        i, j : integer;
        id   : array [1..2] of integer;
        atrasts : boolean;
  begin
    readln (f_in, s_id[1], zime, s_id[2]);
    { seeks for an appropriate identifier }
    for j := 1 to 2 do
        begin
          atrasts := false;
          for i := 1 to cik_tagad_ir do
              if s_id[j] = ida[i]
                 then begin
                        id[j] := i;
                        atrasts := true;
                      end;
          if not atrasts
             then    { we must fill in information about the new person }
               begin
                 inc (cik_tagad_ir);
                 id[j] := cik_tagad_ir;
                 ida[cik_tagad_ir] := s_id[j];
                 with koord_ir do
                   begin
                     maska := maska shl 1;
                     if maska = 0
                        then begin
                               maska := 1;
                               inc (longs);
                             end;
                     for i := 1 to max_lo do
                         if i = longs
                            then a[id[j]][i] := maska
                            else a[id[j]][i] := 0;
                   end;
                 koordmas[id[j]] := koord_ir;
               end;
        end;
    if zime = '<' { sign check }
       then begin
              i1 := id[2];
              i2 := id[1];
            end
       else begin
              i1 := id[1];
              i2 := id[2];
            end;
    if zime = '='
       then flag := true
       else flag := false;
  end;  { read_next_row }

  procedure OR_lielais (i1, i2 : integer);
    var i : integer;
  begin
    if i1 <> i2
       then for i := 1 to max_lo do
                a[i1][i] := a[i1][i] or a[i2][i];
  end;   { OR_lielais }

begin
  cik_tagad_ir := 0;
  with koord_ir do
    begin
      longs := 0;
      maska := 0;
    end;
  assign (f_in, 'AGE.DAT');
  reset(f_in);
  readln (f_in, n);                                  { reads number of rows }
  for nn := 1 to n do
      begin                                          { reads next row       }
        { input is in the following form :                                  }
        {    id_1 > id_2  (id_1 is older than id_2)                         }
        {    id_1 < id_2  (id_1 is younger than id_2)                       }
        {    id_1 = id_2  (id_1 is of the same age as id_2)                 }
        read_next_row (ind1, ind2, flag); { either (flag = false), or       }
                                          { ind1 = ind2 (flag=true)         }
        if ind1 <> ind2
           then begin { ind1 > ind2; fills row ind1 with ind2 : the ones    }
                      { who are younger than ind2, are younger than ind1    }
                  OR_lielais (ind1, ind2); { now the ones who were older    }
                     { than ind1 are older than those who were younger ind1 }
                  for i := 1 to cik_tagad_ir do
                      if (a[i][koordmas[ind1].longs] and
                         koordmas[ind1].maska) <> 0       { older than ind1 }
                         then OR_lielais (i, ind1);
                  if flag
                     then begin { the same operation in the other direction }
                            OR_lielais (ind2, ind1); { now the persons who  }
                            { were older than ind2 are older than those     }
                            { who were younger than ind2                    }
                            for i := 1 to cik_tagad_ir do
                              if (a[i][koordmas[ind2].longs]
                                 and koordmas[ind2].maska) <> 0
                                 then OR_lielais (i, ind2);
                                                          { older than ind2 }
                          end;
                end;   { ind1 <> ind2 }

      end;   { all read }
  close (f_in);
  { now we can start with questions }
  assign (f_in, 'AGE.ASK');
  reset (f_in);
  readln (f_in, n);                                { number of "questions" }
  assign (f_rez, 'AGE.REZ');
  rewrite (f_rez);
  for nn := 1 to n do
      begin
        read_next_row (ind1, ind2, flag); { flag has no sense, because it  }
                                          { always is '?'                  }
        pazime := 0;                                  { seeking for answer }
        { is ind1 >= ind2 ? }
        if (a[ind1][koordmas[ind2].longs] and koordmas[ind2].maska) <> 0
           then inc (pazime);
        { is ind2 >= ind1 ? }
        if (a[ind2][koordmas[ind1].longs] and koordmas[ind1].maska) <> 0
           then inc (pazime, 2);
        { the answer is clear }
        writeln (f_rez, ida[ind1], zime[pazime], ida[ind2]);
      end;
  close (f_in);
  close (f_rez);
end.
