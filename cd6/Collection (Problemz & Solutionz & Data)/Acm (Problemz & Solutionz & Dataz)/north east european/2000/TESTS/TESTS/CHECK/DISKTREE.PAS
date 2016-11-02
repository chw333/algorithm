{ VERIFICATION PROGRAM for DISKTREE problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program DISKTREE_CHECK;
uses
  testlib, symbols;

var
  souf, sans: string;

begin
  while not ans.eof do begin
    sans:= ans.readString;
    souf:= ouf.readString;
    if sans <> souf then 
      Quit(_WA, 'Wrong response: "' + souf + '" <> "' + sans + '"');
    ans.nextLine;
    ouf.nextLine;
  end;
  if not ouf.seekeof then Quit(_PE, 'Extra data in file');
  Quit(_OK, 'Ok');
end.
