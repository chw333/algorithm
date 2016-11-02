program double_primes;  { 1.3, BOI'95}
  { by M.Opmanis, 1997 }

  uses crt;
  var pow10 : array [0..9] of longint;

  function my_mod (n1, n2, m : longint) : longint;
    var ss : string;
  begin
    str (n2, ss);
    my_mod := ((n1 mod m) * (pow10[byte(ss[0])] mod m) + (n2 mod m)) mod m;
   end; { my_mod }

  function prime_paris (n1, n2 : longint) : boolean;
    var i, j, imax : longint;
        ss         : string;
        r          : real;
  begin
    prime_paris := false;
    if my_mod (n1, n2, 2) = 0
       then exit;
    if my_mod (n1, n2, 3) = 0
       then exit;
    str (n2, ss);
    r := n1;
    i := 5; j := 2;
    imax := trunc (sqrt (r * pow10[byte(ss[0])] + n2));
    while i <= imax do
      begin
        if my_mod (n1, n2, i) = 0
           then exit;
        inc (i, j);
        j := 6 - j;
      end;
    prime_paris := true;
  end;  { prime_paris }

  function prime (n : longint) : boolean;
    var i, j : longint;
  begin
    prime := false;
    if n = 0 then exit;
    if n < 4 then begin
                    prime := true;
                    exit;
                  end;
    if n mod 2 = 0 then exit;
    if n < 9 then begin
                    prime := true;
                    exit;
                  end;
    if n mod 3 = 0 then exit;
    if n < 16 then begin
                     prime := true;
                     exit;
                   end;
    i := 5; j := 2;
    while i * i <= n do
     begin
       if n mod i = 0 then exit;
       inc (i, j);
       j := 6 - j;
     end;
    prime := true;
  end;  { prime }

  var vind, paris, sk1, i : longint;
      errcode, ind        : integer;
      inp_f_name          : string;
      inp, out            : text;

begin
  pow10[0] := 1;
  for i := 1 to 9 do
    pow10[i] := pow10[i-1] * 10;
  write ('Input file name => ');
  readln (inp_f_name);
  assign (inp, inp_f_name);
  reset (inp);
  readln (inp, ind);
  close (inp);
  assign (out, 'output.txt');
  rewrite (out);
  vind := 0;
  paris := 1;
  for i := 2 to 40000 do
    begin
      if prime(i)
         then if paris = 1
                 then begin
                        paris := 2;
                        sk1 := i;
                      end
                 else begin
                        paris := 1;
                        if prime_paris (sk1, i)
                           then begin
                                  inc (vind);
                                  if vind = ind
                                     then begin
                                            writeln (out, sk1, i);
                                            break;
                                          end;
                                end;
                      end;
    end;
  close (out);
end.

