program subsequence; { 3.2, BOI'97 }
var n    : integer;  { number of elements }
    r    : longint;  { sum of all elements modulo 3 }
    S    : array [0..2] of boolean;  { set of elements modulo 3 }
    f    : text;  { input/output file }
    i, x : integer;
begin
  { initial values of r and S }
  r := 0;
  for i := 0 to 2 do
    S[i] := false;
  { open the input file }
  assign (f, 'SEQ.IN');
  reset (f);
  readln (f, n);
  { read in the sequence updating r and S }
  for i := 1 to n do
    begin
      readln (f, x);
      x := x mod 3;
      S[x] := true;
      r := r + x
    end;
  r := r mod 3;
  { close the input file and write out the result }
  close (f);
  assign (f, 'SEQ.OUT');
  rewrite (f);
  if r = 0
     then writeln (f, n)
     else if S[r]
             then writeln (f, n - 1)
             else writeln (f, n - 2);
  close (f);
end.

