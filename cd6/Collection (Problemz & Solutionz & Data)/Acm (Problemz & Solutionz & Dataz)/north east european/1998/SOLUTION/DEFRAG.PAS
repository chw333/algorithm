{ NEERC'98 Problem "Defragment"
  Solution by Roman Elizarov
  20.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program DEFRAGMENT_SOLUTION;

const
  maxn = 10000;

var
  n, k, i, j, s, cnt, cl, free_cl: integer;
  dest, src: array[1..maxn] of integer;
  done: boolean;

procedure Moves;
begin
 { starts moving clusters to place starting from 'i' }
  while (i <> 0) and (dest[i] <> 0) and
        (dest[i] <> i) and (dest[dest[i]] = 0) do begin
    j:= dest[i];
    writeln ( i, ' ', j );
    done:= true;
    dest[j]:= j;
    src[j]:= j;
    dest[i]:= 0;
    i:= src[i];
  end;
end;

begin
  assign ( input, 'defrag.in' ); reset ( input );
  assign ( output, 'defrag.out' ); rewrite ( output );

 { Reading input }
  read ( n, k );
  cnt:= 0;
  fillchar(dest, sizeof(dest), 0);
  fillchar(src, sizeof(src), 0);
  for i:= 1 to k do begin
    read(s);
    for j:= 1 to s do begin
      inc(cnt);
      read(cl);
      dest[cl]:= cnt;
      src[cnt]:= cl;
    end;
  end;

 { Solving }
  done:= false; { No moves were done yet }
  for cl:= 1 to n do begin { check clusters for free transfer }
    i:= cl;
    Moves;
  end;

 { Lets find free cluster }
  free_cl:= 1;
  while (free_cl <= n) and (dest[free_cl] <> 0) do
    inc ( free_cl );

 { Cycles only left, let's work with them }
  for cl:= 1 to n do begin
    if (dest[cl] <> 0) and (dest[cl] <> cl) then begin
     { move cl-th cluster to free place }
      writeln ( cl, ' ', free_cl );
      dest[free_cl]:= dest[cl];
      src[dest[cl]]:= free_cl;
      dest[cl]:= 0;
     { all other moves }
      i:= src[cl];
      Moves;
    end;
  end;

  if not done then
    writeln ( 'No optimization needed' );
end.
