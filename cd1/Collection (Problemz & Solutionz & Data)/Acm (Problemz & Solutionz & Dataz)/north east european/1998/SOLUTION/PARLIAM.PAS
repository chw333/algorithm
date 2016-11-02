{ NEERC'98 Problem "Parliament"
  Solution by Roman Elizarov
  08.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program PARLIAM_SOLUTION;

const
  max = 100;

var
  sum, start, cur, i: integer;
  v: array[1..max] of boolean;

begin
  assign ( input, 'parliam.in' ); reset ( input );
  assign ( output, 'parliam.out' ); rewrite ( output );

 { Read input }
  read ( sum );

 { Solve }
  for start:= 2 to 3 do begin { start the seq. from 2 or 3 }
    fillchar ( v, sizeof(v), false );
    i:= start;
    cur:= 0;
    while cur < sum do begin
      inc ( cur, i );
      v[i]:= true;
      inc ( i );
    end;
    if (cur > sum) and v[cur-sum] then begin
      v[cur-sum]:= false;
      cur:= sum;
    end;
    if cur = sum then { solution is Ok }
      break;
  end;

 { Write output }
  for i:= 2 to max do
    if v[i] then
      write ( i, ' ' );
end.
