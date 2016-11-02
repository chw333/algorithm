{ VERIFICATION PROGRAM for SEARCH problem for NEERC'2000 }
{ (C) Roman Elizarov }
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program SEARCH_CHECK;
uses
  testlib, symbols;

var
  wa: boolean; { "Wrong answer" flag }
  wm: string;  { Message for "Wrong answer" result }
  kouf, kans, i: longint;
  aouf, aans, bouf, bans: longint;

begin
  wa:= false;
  kouf := ouf.readLongint; 
  kans := ans.readLongint;
  for i := 1 to kouf do begin
    aouf := ouf.readLongint;
    bouf := ouf.readLongint;
    if not wa and (i <= kans) then begin
      aans := ans.readLongint;
      bans := ans.readLongint;
      if (aouf <> aans) or (bouf <> bans) then begin
        wa := true;
        wm := 'Interval ' +
              str(aouf, 0) + '-' + str(bouf, 0) + ' differs from ' +
              str(aans, 0) + '-' + str(bans, 0);
      end; 
    end;
    if not wa and (i > kans) then begin
      wa := true;
      wm := 'Extra intervals in file';
    end;
  end;
  if not wa and (kouf < kans) then begin
    wa := true;
    wm := 'Not enough intervals in file';
  end;

  if not ouf.seekeof then Quit(_PE, 'Extra data in file');
  if wa then Quit(_WA, wm);
  Quit(_OK, 'Ok');
end.
