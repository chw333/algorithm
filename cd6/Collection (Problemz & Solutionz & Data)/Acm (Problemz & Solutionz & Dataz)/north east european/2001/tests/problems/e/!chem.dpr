{ VERIFICATION PROGRAM for CHEM problem for NEERC'2001 }
{ (C) Roman Elizarov }
{$APPTYPE CONSOLE}
program CHEM_CHECK;
uses
  sysutils, testlib in '..\testlib.pas';

var
  sans, souf: string;

begin
  try 
    while not ans.seekeof do begin
      sans := ans.readString;
      souf := ouf.readString;
      if souf <> sans then
        Quit(_WA, 'Wrong answer: ' + souf + ' <> ' + sans);
    end;
    if not ouf.seekeof then
      Quit(_PE, 'Extra data in file');
    Quit(_OK, 'Ok');
  except on e: Exception do 
    Quit(_FAIL, e.Message);
  end;
end.
