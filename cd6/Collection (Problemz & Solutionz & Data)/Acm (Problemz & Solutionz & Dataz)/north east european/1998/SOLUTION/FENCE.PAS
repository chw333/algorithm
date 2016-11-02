{ NEERC'98 Problem "Fence"
  Solution by Roman Elizarov
  19.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program FENCE_SOLUTION;

const
  eps = 1e-10;
  maxn = 100;

type
  real = extended;

function det ( x11, x12, x21, x22: real ): real;
begin
  det:= x11*x22 - x12*x21;
end;

function Angle ( x, y: real ): real; { angle in [0;2*pi) range }
var
  ang: real;
begin
  if abs(x) < eps then
    if y > 0 then
      Angle:= pi/2
    else
      Angle:= 3*pi/2
  else begin
    ang:= arctan ( y / x );
    if x < 0 then
      ang:= pi + ang;
    if ang < 0 then
      ang:= ang + 2*pi;
    Angle:= ang;
  end;
end;

procedure Swap ( var x, y: real );
var
  t: real;
begin
  t:= x;
  x:= y;
  y:= t;
end;

{ getAngInt - returns the interval for angles }
procedure getAngInt ( x1, y1, x2, y2: real; var a1, a2: real );
begin
  if det ( x1, y1, x2, y2 ) < eps then begin
    swap ( x1, x2 );
    swap ( y1, y2 );
  end;
  a1:= Angle ( x1, y1 );
  a2:= Angle ( x2, y2 );
  if a2 < a1 - eps then
    a2:= a2 + 2*pi;
end;

function min( x, y: real ): real;
begin
  if x < y then
    min:= x
  else
    min:= y;
end;

function max(x, y: real): real;
begin
  if x > y then
    max:= x
  else
    max:= y;
end;

function between ( a, x, b: real ): boolean;
begin
  between:= (x > a - eps) and (x < b + eps);
end;

var
  k, h: real;
  n, i, j: integer;
  x, y: array[0..maxn] of real;
  a, b, aa, bb: real;

begin
  assign ( input, 'fence.in' ); reset ( input );
  assign ( output, 'fence.out' ); rewrite ( output );

 { Reading input }
  read ( k, h, n );
  for i:= 1 to n do
    read ( x[i], y[i] );
  x[0]:= x[n];
  y[0]:= y[n];

 { Solving }
  getAngInt ( x[0], y[0], x[1], y[1], a, b ); { [a,b] - current interval }
  for i:= 1 to n-1 do begin
    getAngInt ( x[i], y[i], x[i+1], y[i+1], aa, bb );
   { Now we shall unite [aa,bb] with [a,b] }
    for j:= -1 to 1 do
      if between ( a, aa + 2*pi*j, b ) or between ( a, bb + 2*pi*j, b ) then begin
        a:= min ( a, aa + 2*pi*j );
        b:= max ( b, bb + 2*pi*j );
        break;
      end;
  end;

 { Interval of angles found, let's write the answer }
  writeln ( min ( b - a, 2*pi ) * k * h:0:2 );
end.