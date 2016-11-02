{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 16384,0,655360}

Program LogicalExpressions; { 2.3, BOI'96 }
{ written by Tomas Laurinavicius on 6th September 1997 }
{ requires Borland/Turbo Pascal 7.0 }

  type TResult = array [0..31] of byte;
  { this type is used to store results of an expression for all possible
    variable values. That is 2^8 = 256 bits = 32 bytes. It's also possible
    to use "set of byte" for this type. }

  var t     : text;
      v     : array ['a'..'h'] of boolean;    { values of the variables }
      R     : array [1..5] of string;         { expressions             }

      res,                                    { just a result for Rx    }
      neg   : array [1..5] of TResult;        { inverted result #Rx     }
      r_and,                                  { result for Rx&Ry...     }
      r_or  : array [1..5, 1..5] of TResult;        { ...and for Rx+Ry        }

  procedure ReadInput;
    var i, j  : word;
        fn, s : string;
  begin
    write ('Input file name: ');
    ReadLn (fn);
    assign (t, fn);
    reset (t);
    for i := 1 to 5 do
      begin
        ReadLn (t, s);
        j := 1;
        while j < length (s) do                              { erase spaces }
          if s[j] = ' '
             then delete (s, j, 1)
             else inc (j);
        R[i] := s;
      end;
    close (t);
  end;

  function value (s : string) : boolean;
    { Gets the value of the expression "s" using variable values in "v".    }
    { This routine is not optimal, because it analyzes the same string a    }
    { lot of times. Compiling the string into some pseudo-machine code      }
    { before calculations would give a HUGE speed gain. However the me-     }
    { thod used is a lot shorter and is fast enough to get the program      }
    { "fit" into 20 sec. }

    function simple (e : string): char;
      { calculates value of expression "e" without brackets;                }
      { returns value of type "char": '0' or '1'.                           }
      var p : word;
    begin
      if e[1] = '('
         then delete (e, 1, 1);
      if e[length (e)] = ')'
         then delete (e, length (e), 1);
      p := pos ('#', e);
      while p > 0 do
        begin
          delete(e, p, 1);
          case e[p] of
            '0': e[p] := '1';
            '1': e[p] := '0';
            '#': delete (e, p, 1);  { in case we have something like '###a' }
          end;
          p := pos('#', e);
        end;
      p := pos ('&', e);
      while p > 0 do
        begin
          if (e[p - 1] = '1') and (e[p + 1] = '1')
             then e[p - 1] := '1'
             else e[p - 1] := '0';
          delete (e, p, 2);
          p := pos ('&', e);
        end;
      p := pos ('+', e);
      while p > 0 do
        begin
          if (e[p - 1] = '0') and (e[p + 1] = '0')
             then e[p - 1] := '0'
             else e[p - 1] := '1';
          delete (e, p, 2);
          p := pos ('+', e);
        end;
      simple := e[1];
    end;

  var i, r, l : word;
  begin
    for i := 1 to length (s) do
        if s[i] in ['a'..'h']
           then s[i] := Chr (Ord ('0') + Ord (v[s[i]]));
    while length (s) > 1 do
      begin
        r := pos (')', s);
        if r = 0
           then begin
                  r := length (s);
                  l := 1;
                end
           else begin
                  l := r;
                  while s[l] <> '(' do
                    dec(l);
                end;
        s[l] := simple (copy( s, l, r - l + 1));
        delete (s, l + 1, r - l);
      end;
    value := s[1] = '1';
  end;

  procedure FindResults;
    { fills the variables "res", "neg", "r_and" and "r_or" with required }
    { values                                                             }
    var exp, exp2, i, j : word;
  begin
    { fill "res" }
    FillChar (res, SizeOf (res), 0);
    for i := 0 to 255 do
      begin
        { variable values are made of the bits of "i". I think this is     }
        { simplier and more efficient than 8 "for" statements or recursion }
        for j := 0 to 7 do
          v[Chr (Ord ('a') + j)] := (i and (1 shl j) > 0);
        for exp := 1 to 5 do
          if value (R[exp])
             then res[exp, i shr 3] := res[exp, i shr 3]
                                       or (1 shl (i and 7));
      end;
    { fill "neg" }
    for exp := 1 to 5 do
        for i := 0 to 31 do
            neg[exp, i] := not res[exp, i];
    { fill "r_and" and "r_or" }
    for exp := 1 to 5 do
      for exp2 := 1 to 5 do
        for i := 0 to 31 do
            begin
              r_and[exp, exp2, i] := res[exp, i] and res[exp2, i];
              r_or[exp, exp2, i] := res[exp, i] or res[exp2, i];
            end;
  end;

  procedure FindLeastSet;
    { finds the least set of expressions }

    function eq (const a, b : TResult) : boolean;
      { returns true if a = b and false otherwise }
      var i : word;
    begin
      eq := false;
      for i := 0 to 31 do
          if a[i] <> b[i]
             then exit;
      eq := True;
    end;

    var i, j, k, l, bsc, nbsc, min_bsc : word;
        found                          : boolean;
        bs,                          { numbers of basic set expressions... }
        nbs  : array [1..5] of byte; { ...and of all the other expressions }
        expr, min_expr : array[ 1..5 ] of
                               record
                                  tp : (basic, o_assign, o_not, o_and, o_or);
                                  e1, e2 : byte;
                                end;
    label 1;
  begin
    min_bsc := 5;
    for j := 1 to 5 do
      min_expr[j].tp := basic;
    for i := 1 to 30 do
      begin
        { The basic expressions are chosen according to the bits of "i".    }
        { Since we need at least one basic expression, we start loop from 1.}
        { 31 is the worst and the last case, which is default if no better  }
        { solution found. So we end the loop at 30.                         }
        bsc := 0;  nbsc := 0;
        for j := 1 to 5 do
            if (i and (1 shl (j-1)) > 0)
               then begin
                      inc (bsc);
                      bs[ bsc ] := j;
                    end
               else begin
                      inc (nbsc);
                      nbs [nbsc] := j;
                    end;
        for j := 1 to bsc do
            expr[bs[j]].tp := basic;
        for j := 1 to nbsc do
            { find a way to represent every non basic expression }
            begin
              found := false;
              for k := 1 to bsc do
                  begin
                    if eq (res[nbs[j]], res[bs[k]]) then
                       begin
                         expr[nbs[j]].tp := o_assign;
                         expr[nbs[j]].e1 := bs[k];
                         found := true;
                         break;
                       end;
                    if eq (res[nbs[j]], neg[bs[k]]) then
                       begin
                         expr[nbs[j]].tp := o_not;
                         expr[nbs[j]].e1 := bs[k];
                         found := true;
                         break;
                       end;
                  end;
              if not found
                 then for k := 1 to bsc do
                        for l := k + 1 to bsc do
                          if eq (res[nbs[j]], r_and[bs[k], bs[l]])
                             then begin
                                    expr[nbs[j]].tp := o_and;
                                    expr[nbs[j]].e1 := bs[k];
                                    expr[nbs[j]].e2 := bs[l];
                                    found := true;
                                    goto 1;        { break out of two loops }
                                  end
                             else if eq (res[nbs[j]], r_or[ bs[k], bs[l]])
                                     then begin
                                            expr[nbs[j]].tp := o_or;
                                            expr[nbs[j]].e1 := bs[k];
                                            expr[nbs[j]].e2 := bs[l];
                                            found := true;
                                            goto 1;
                                          end;
              { if we haven't found a representation of this expression,    }
              { there's no point in finding representations for other       }
              { expressions }
  1 :         if not found
                 then break;
            end;
        if found and (bsc < min_bsc)
           then begin
                  min_bsc := bsc;
                  min_expr := expr;
                end;
      end;
    assign (t, 'output.txt');
    ReWrite (t);
    for j := 1 to 5 do
      if min_expr[j].tp = basic
         then WriteLn (t, 'R', j);
    for j := 1 to 5 do
        if min_expr[j].tp <> basic
           then begin
                  write (t, 'R', j, '=');
                  with min_expr[j] do
                    case tp of
                      o_assign: WriteLn (t, 'R', e1);
                      o_not:    WriteLn (t, '#R', e1);
                      o_and:    WriteLn (t, 'R', e1, '&R', e2);
                      o_or:     WriteLn (t, 'R', e1, '+R', e2);
                    end;
                end;
    close (t);
  end;

begin
  ReadInput;
  FindResults;
  FindLeastSet;
end.