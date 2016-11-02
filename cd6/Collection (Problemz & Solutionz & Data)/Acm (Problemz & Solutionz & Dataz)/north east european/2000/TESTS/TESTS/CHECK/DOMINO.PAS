{ VERIFICATION PROGRAM for DOMINO PUZZLE problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program DOMINO_CHECK;
uses
  testlib, symbols;

const
  NUMS = 6; { Numbers }

var
  g: array[1..NUMS, 1..NUMS] of longint; { Adjacency }
  v: array[1..NUMS] of longint; { Vertice power }

function IsLinkable: boolean;
var
  i, cnt, s, sp: integer;
  st: array[1..NUMS] of integer;
  f: array[1..NUMS] of boolean;
begin
  { Check for odd powers }
  cnt := 0; { Odd counter }
  for i := 1 to NUMS do 
    if Odd(v[i]) then begin
      Inc(cnt);
      if cnt > 2 then begin
        IsLinkable := false;
        exit;
      end;
    end;
  { Count non-zero power vertices }
  cnt := 0;
  for i := 1 to NUMS do
    if v[i] > 0 then begin
      Inc(cnt);
      s := i; { Store some non-zero vertice }
    end;
  if cnt = 0 then { Sanity check }
    QUIT(_FAIL, 'Sanity check failed!!!'); 
  { Check for graph's connectedness }
  fillchar(f, sizeof(f), 0); { Clear visited flag }
  f[s] := true;
  Dec(cnt); { We've visited one! }
  sp := 1; { Initial stack pointer }
  st[1] := s;
  while (sp > 0) and (cnt > 0) do begin
    s := st[sp];
    Dec(sp);
    for i := 1 to NUMS do 
      if not f[i] and (g[s, i] > 0) then begin
        f[i] := true;
        Dec(cnt);
        Inc(sp);
        st[sp] := i;
      end;
  end;
  IsLinkable := cnt = 0;
end;

var
  n, k, i, a, b: integer;
  souf, sans, sum: longint;

begin
  n := inf.readInteger;
  fillchar(g, sizeof(g), 0);
  fillchar(v, sizeof(v), 0);
  for i := 1 to n do begin
    a := inf.readInteger;
    b := inf.readInteger;
    Inc(g[a, b]);
    Inc(g[b, a]);
    Inc(v[a]);
    Inc(v[b]);
  end;

  souf := ouf.readLongint; 
  sans := ans.readLongint;
  k := ouf.readInteger;
  sum := 0;
  for i := 1 to k do begin
    a := ouf.readInteger;
    b := ouf.readInteger;
    if (a < 1) or (a > NUMS) then
      Quit(_PE, 'Wrong digit: ' + str(a, 0));
    if (b < 1) or (b > NUMS) then
      Quit(_PE, 'Wrong digit: ' + str(b, 0));
    Inc(g[a, b]);
    Inc(g[b, a]);
    Inc(v[a]);
    Inc(v[b]);
    Inc(sum, a + b);
  end;
  if not ouf.seekeof then Quit(_PE, 'Extra data in file');

  if sum <> souf then 
    Quit(_WA, 'The sum of output is not consistent');
  if not IsLinkable then
    Quit(_WA, 'Cannot lay out a row');
  if souf > sans then
    Quit(_WA, 'Not an optimal sum');
  if souf < sans then
    Quit(_FAIL, 'More optimal solution was found!!!');

  Quit(_OK, 'Ok');
end.
