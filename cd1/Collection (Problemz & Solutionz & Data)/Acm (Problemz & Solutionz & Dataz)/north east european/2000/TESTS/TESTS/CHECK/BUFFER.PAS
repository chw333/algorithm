{ VERIFICATION PROGRAM for BUFFER MANAGER problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program BUFFER_CHECK;
uses
  testlib, symbols;

var
  iouf, ians: longint;

begin
  ians:= ans.readLongint;
  iouf:= ouf.readLongint;
  if not ouf.seekeof then Quit(_PE, 'Extra data in file');
  if iouf <> ians then
    Quit(_WA, 'Wrong answer: ' + str(iouf,0) + ' <> ' + str(ians,0));
  Quit(_OK, 'Ok');
end.
