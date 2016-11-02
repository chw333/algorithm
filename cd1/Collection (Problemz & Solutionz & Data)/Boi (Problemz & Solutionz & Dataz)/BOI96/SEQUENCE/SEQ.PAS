program nice; { 2.2, BOI'96 }
  { by M. Opmanis, 1997 }

  uses {$IFDEF WINDOWS} WinCrt, WinDos {$ELSE} Crt, Dos {$ENDIF};
  const masmax = 25;
  type masis = array [2..masmax] of boolean;
  var a, c, c_min                       : array [1..masmax] of byte;
      vajag_fik                         : masis;
      n, j, min_limenis, i_kur, jaunais : byte;
      kopskaits                         : longint;
      out, infa                         : text;
      f_vards                           : string;
      paliek                            : byte;
      { flag: 2 - any; 1 - needs non-increasing; 3 - needs non-decreasing }

  procedure izdruka_galigo;
    var i : byte;
  begin
    writeln (out, min_limenis);
    if min_limenis > 0
       then for i := 1 to n do
                writeln (out, a[i],' ', c_min[i]);
  end;

  function der_pec_flaga (new_index, old_index, old_flag : byte) : byte;
    { checks whether element with index new_index is valid, depending on   }
    { flag. If is, then returns new flag value ( > 0) or 0 otherwise       }
    var new_flag : byte;
  begin
    new_flag := 0;
    case old_flag of
      1 : if a[new_index] <= a[old_index]
             then new_flag := old_flag;
      3 : if a[new_index] >= a[old_index]
             then new_flag := old_flag;
      2 : if a[new_index] < a[old_index]
             then new_flag := 1
             else if a[new_index] > a[old_index]
                     then new_flag := 3
                     else new_flag := old_flag;
    end;   { case }
    der_pec_flaga := new_flag;
  end;

  function first_free : byte;
    var i : byte;
  begin
    i := 1;
    while c[i] > 0 do
      inc (i);
    first_free := i;
  end;

  procedure atzim (apv_no,                           { index of subsequence }
                   apv_flag,                         { flag of subsequence  }
                   apv_loc_sk, { no. of elements in subs. (till this moment)}
                   ped_index : byte; { index of subsequences last element   }
                                     { in the main sequence                 }
                   var vajag_parb : masis); { array, where are mentioned    }
                                            { these which need checking     }

    var i, k, new_flag   : byte;
        varejam_turpinat : boolean;
        vajag_tal        : masis;
  begin
    if paliek = 0
      then                            { all elements belong to subsequences }
        if apv_no < min_limenis
           then begin
                  min_limenis := apv_no;
                  kopskaits := 1;
                  c_min := c;
                end
           else
      else                                        { there are free elements }
        begin                  { we'll try to continue the same subsequence }
          varejam_turpinat := false;
          for i := ped_index + 1 to n do
              vajag_tal[i] := (c[i] = 0);
          for i := ped_index + 1 to n do
              if vajag_tal[i]    { free and such, that must be investigated }
                 then
                   begin
                     new_flag := der_pec_flaga (i, ped_index, apv_flag);
                     if new_flag > 0
                        then
                          begin             { is valid for this subsequence }
                            varejam_turpinat := true;
                            c[i] := apv_no;
                            dec (paliek);
                            vajag_parb[i] := false;
                            atzim (apv_no, new_flag, apv_loc_sk+1,
                                   i, vajag_tal);
                            c[i] := 0;
                            inc (paliek);
                          end;
                   end;
          { add information about the previous level }
          if varejam_turpinat
             then begin
                    for i := ped_index + 1 to n do
                        vajag_parb[i] := vajag_parb[i] and vajag_tal[i];
                        if paliek > 2
                           then exit;    { we can make one more subsequence }
                  end;
          { try to make new subsequence }
          if (apv_loc_sk > 1) { in the previous subs.are at least two       }
                              { elements }
             and (paliek > 1) { at least two elements are free              }
             and (apv_no < min_limenis - 1) { going one level up there will }
                                            { be min - 1 anyway             }
             then begin                     { let's go one level deeper     }
                    k := first_free;
                    for i := k + 1 to n do
                        vajag_tal[i] := true;
                    c[k] := apv_no + 1;
                    dec (paliek);
                    atzim (apv_no + 1, 2, 1, k, vajag_tal);
                    c[k] := 0;
                    inc (paliek);
                  end;
        end;
  end;   { atzim }

begin
  write ('Input file name =>');
  readln (f_vards);
  assign (infa, f_vards);
  reset (infa);
  readln(infa,N);
  assign (out, 'output.txt');
  rewrite (out);
  if (N < 2) or (N > masmax)
     then begin
            writeln (out, '0');
            close (out);
            close (infa);
            exit;
          end;
  readln (infa, a[1]);
  c[1] := 1;
  i_kur := 1;
  for j := 2 to n do
      begin
        readln (infa, a[j]);
        c[j] := 0;
      end;
  if n < 3
     then begin
            writeln (out, '1');
            close (out);
            close (infa);
            exit;
          end;
  paliek := n - 1;
  kopskaits := 0;
  min_limenis := (n div 2) + 1;
  atzim (1, 2, 1, 1, vajag_fik);
  if kopskaits = 0
     then min_limenis := 0;
  izdruka_galigo;
  close (out);
  close (infa);
end.

