program barrel_filling; { 2.4, BOI'96 }
{ © M. Opmanis , 1996. }

  uses {$IFDEF WINDOWS} WinCrt,WinDos {$ELSE} Crt,Dos {$ENDIF};
  const barrels_max   = 100;
        volume : real = 100;
        code_pour     = 'P';    { Pour  }
        code_valve    = 'V';    { Valve }
  type mu = record
              gr_no : byte;
              vol   : real;
            end;
       gr = record
              no_barrels : byte;
              vol        : real;
            end;
  var file_name         : string;
      fff, ggg          : Text;
      ve_ta             : array [1..barrels_max, 1..barrels_max] of boolean;
      mu_ta             : array [1..barrels_max] of mu;
      gr_ta             : array [1..barrels_max] of gr;
      ii, jj            : byte;
      code              : char;
      sk_1, sk_2        : integer;
      komanda, errcode, i_no, n_instr        : integer;
      barrels           : byte;
      rmax, rmin        : real;
      h1, min1, sec1, sec100, h2, min2, sec2 : word;
      lo, h, min, sec, lo1, lo2              : longint;

  function vienai (grupa : byte) : boolean;
    var v : real;
        i : byte;
   begin
     v := gr_ta[grupa].vol / gr_ta[grupa].no_barrels;
     if v > volume
        then vienai := false
        else begin
               vienai := true;
               for i := 1 to barrels do
                   if mu_ta[i].gr_no = grupa
                      then mu_ta[i].vol := v;
             end;
   end;

  function pielej (mucas_nr : byte; cik : real) : boolean;
  begin
    gr_ta[mu_ta[mucas_nr].gr_no].vol := gr_ta[mu_ta[mucas_nr].gr_no].vol
                                        + cik ;
    pielej := vienai (mu_ta[mucas_nr].gr_no);
  end;

  procedure ventilis (a, b : byte);
    var c                : array [1 .. barrels_max] of boolean;
        gr_a, gr_b, skaits_a, skaits_b, i, j, pielikts : byte;
        summa_a, summa_b : real;
  begin
    if ve_ta[a,b]
       then begin
              ve_ta[a,b] := false;
              ve_ta[b,a] := ve_ta[a,b];
              gr_a := mu_ta[a].gr_no;
              for i := 1 to barrels do
                  if gr_ta[i].no_barrels = 0
                     then begin
                            gr_b := i;
                            break;
                          end;
              for i := 1 to barrels do
                c[i] := false;
              mu_ta[b].gr_no := gr_b;
              repeat
                pielikts := 0;
                for i := 1 to barrels do
                 if (not c[i]) and (mu_ta[i].gr_no = gr_b)
                    then begin
                           c[i] := true;
                           for j := 1 to barrels do
                               if (not c[j]) and ve_ta[i,j]
                                  then begin
                                         inc (pielikts);
                                         mu_ta[j].gr_no := gr_b;
                                       end;
                         end;
              until pielikts = 0;
              skaits_a := 0;
              summa_a := 0;
              skaits_b := 0;
              summa_b := 0;
              for i := 1 to barrels do
                  if mu_ta[i].gr_no = gr_a
                    then begin
                           inc (skaits_a);
                           summa_a := summa_a + mu_ta[i].vol;
                         end
                    else if mu_ta[i].gr_no = gr_b
                            then begin
                                   inc (skaits_b);
                                   summa_b := summa_b + mu_ta[i].vol;
                                 end;
              gr_ta[gr_a].no_barrels := skaits_a;
              gr_ta[gr_a].vol := summa_a;
              gr_ta[gr_b].no_barrels := skaits_b;
              gr_ta[gr_b].vol := summa_b;
            end
       else begin
              ve_ta[a, b] := true;
              ve_ta[b, a] := ve_ta[a, b];
              gr_a := mu_ta[a].gr_no;
              gr_b := mu_ta[b].gr_no;
              if gr_a <> gr_b
                 then begin
                        inc (gr_ta[gr_a].no_barrels, gr_ta[gr_b].no_barrels);
                        gr_ta[gr_a].vol := gr_ta[gr_a].vol + gr_ta[gr_b].vol;
                        gr_ta[gr_b].no_barrels := 0;
                        gr_ta[gr_b].vol := 0;
                        for i := 1 to barrels do
                            if mu_ta[i].gr_no = gr_b
                              then mu_ta[i].gr_no := gr_a;
                        vienai (gr_a);
                      end;
            end;
  end;

begin
  write ('Input file name => ');
  readln (file_name);
  assign (fff, file_name);
  reset (fff);
  readln (fff, barrels, n_instr);
  for ii := 1 to barrels do
    begin
      mu_ta[ii].gr_no := ii;
      mu_ta[ii].vol := 0;
      gr_ta[ii].no_barrels := 1;
      gr_ta[ii].vol := 0;
      for jj := 1 to barrels do
          if ii = jj
             then ve_ta[ii, jj] := true
             else ve_ta[ii, jj] := false;
    end;
  assign (ggg, 'OUTPUT.TXT');
  rewrite (ggg);
  errcode := 1;      { OK }
  komanda := 0;
  while (komanda < n_instr) and (errcode = 1) do
    begin
      readln (fff, code, sk_1, sk_2);
      inc (komanda);
      case code of
        code_pour  : if (sk_1 > 0) and (sk_1 <= barrels)
                        then errcode := byte (pielej (sk_1, sk_2))
                        else errcode := 2;           { bad input   }
        code_valve : if (sk_1 > 0) and (sk_1 <= barrels) and
                        (sk_2 > 0) and (sk_2 <= barrels)
                        then ventilis (sk_1, sk_2)
                        else errcode := 2;           { bad input   }
        else         errcode := 3                    { bad command }
      end;  { case }
    end;
  case errcode of                { output }
    0 : writeln (ggg, 'OVERFLOW ', komanda);
    1 : begin         { finding min & max }
          rmax :=  mu_ta[1].vol;
          rmin :=  mu_ta[1].vol;
          for ii := 2 to barrels do
            begin
              if rmax < mu_ta[ii].vol
                 then rmax := mu_ta[ii].vol
                 else if rmin > mu_ta[ii].vol
                         then rmin := mu_ta[ii].vol;
            end;
          writeln (ggg, 'OK ', rmin : 5 : 2, ' ', rmax : 5 : 2);
        end;
    2 : begin
          write (ggg, 'BAD VALUE ', sk_1, ' OR ', sk_2, ' IN "',code);
          writeln (ggg, '" COMMAND (line #', komanda, ')');
        end;
    3 : writeln (ggg, 'BAD COMMAND ', code, ' (line #', komanda, ')');
  end;  { case }
  close (fff);
  close (ggg);
end.

