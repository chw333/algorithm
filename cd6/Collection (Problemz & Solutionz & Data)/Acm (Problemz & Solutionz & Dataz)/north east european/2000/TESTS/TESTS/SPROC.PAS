const
  MAXN = 10000;
var
  A: array[0..MAXN-1] of integer;
  N: integer;

procedure BinarySearch(x: integer);
var
  p, q, i, L: integer;
begin
  p := 0;   { Left border of the search  }
  q := N-1; { Right border of the search }
  L := 0;   { Comparison counter         }
  while p <= q do begin
    i := (p + q) div 2;
    inc(L);
    if A[i] = x then begin
      writeln('Found item i = ', i,
        ' in L = ', L, ' comparisons');
      exit
    end;
    if x < A[i] then
      q := i - 1
    else
      p := i + 1
  end
end;
