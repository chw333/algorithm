{ VERIFICATION PROGRAM for GARLAND problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program GARLAND_CHECK;
uses
  testlib, symbols;

const
  eps = 0.015; { For safety reasons 0.01 is not enough when rounding!!! }

var
  rouf, rans: extended;

begin
  rans:= ans.readReal;
  rouf:= ouf.readReal;
  if not ouf.seekeof then Quit(_PE, 'Extra data in file');
  if abs(rouf - rans) > eps then
    Quit(_WA, 'Wrong answer: ' +
      realStr(rouf,0,2) + ' <> ' +
      realStr(rans,0,2));
  Quit(_OK, 'Ok');
end.
