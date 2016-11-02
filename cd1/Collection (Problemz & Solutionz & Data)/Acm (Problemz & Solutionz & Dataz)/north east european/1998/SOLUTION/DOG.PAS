{ NEERC'98 Problem "The dog task"
  Solution by Roman Elizarov
  20.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program DOG_SOLUTION;

const
  max = 100;
  eps = 1e-12;

type
  real = extended;

var
 x, y, x1, y1, goes: array[1..max] of integer;
 n, m, i, j, cnt: integer;
 v: array[1..max] of boolean;

{ "dist" - distance between point (x1,y1) and (x2,y2) }
function dist ( x1, y1, x2, y2: real ): real;
begin
  dist:= sqrt ( sqr ( x1 - x2 ) + sqr ( y1 - y2 ) );
end;

{ "can" - can travel (Xi,Yi) -> (X'j,Y'j) -> (Xi+1, Yi+1) }
function can ( i, j: integer ): boolean;
begin
  can:= dist ( x[i], y[i], x1[j], y1[j] ) +
        dist ( x1[j], y1[j], x[i+1], y[i+1] ) <
        2 * dist ( x[i], y[i], x[i+1], y[i+1] ) + eps;
end;

{ Solving }
function try (j: integer): boolean;
var
  i: integer;
begin
  if v[j] then begin
    try:= false;
    exit;
  end;
  v[j]:= true;
  for i:= 1 to n-1 do
    if can (i, j) and ((goes[i] = 0) or try(goes[i])) then begin
      try:= true;
      goes[i]:= j;
      exit;
    end;
  try:= false;
end;

begin
  assign ( input, 'dog.in' ); reset ( input );
  assign ( output, 'dog.out' ); rewrite ( output );

 { Reading input }
  read ( n, m );
  for i:= 1 to n do
    read ( x[i], y[i] );
  for i:= 1 to m do
    read ( x1[i], y1[i] );

 { Finding solution }
  fillchar ( goes, sizeof(goes), 0 );
  cnt:= n;
  for j:= 1 to m do begin
    fillchar ( v, sizeof(v), false );
    if try ( j ) then
      inc ( cnt );
  end;

 { Solution found. Writing to output }
  writeln ( cnt );
  for i:= 1 to n do begin
    if i > 1 then
      write ( ' ' );
    write ( x[i], ' ', y[i] );
    if goes[i] <> 0 then
      write ( ' ', x1[goes[i]], ' ', y1[goes[i]] );
  end;
end.


