{ VERIFICATION PROGRAM for TRIATHLON problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program TRIATHLON_CHECK;
uses
  testlib, symbols;

var
  wa: boolean;
  wm: string;
  souf, sans: string;

begin
  wa:= false;
  while not ans.seekeof do begin
    sans:= upstr(compress(ans.readString));
    souf:= upstr(compress(ouf.readString));
    if (souf <> 'YES') and
       (souf <> 'NO') then
      Quit(_PE, 'Unknown response: ' + souf);
    if not wa and (sans <> souf) then begin
      wa:= true;
      wm:= 'Wrong response: ' + souf + ' <> ' + sans;
    end;
  end;

  if not ouf.seekeof then Quit(_PE, 'Extra data in file');
  if wa then Quit(_WA, wm);
  Quit(_OK, 'Ok');
end.
