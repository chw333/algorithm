{ Sprawdzaczka do zadania CRA }
{ Autor: Pawe³ Wolff }
{ Data : 28.05.2001  }


{ Interfejs sprawdzaczki jest nastêpuj±cy: 
 *
 * Program oceniaj±cy uruchamia siê z czterema parametrami:
 *    1 - NazwaIN - plik wej¶ciowy --- (ignorowany),
 *    2 - NazwaOUT - odpowied¼ zawodnika,
 *    3 - NazwaOK - nazwa pliku z prawid³ow± odpowiedzi±,
 *    4 - NrTestu - program nie powinien korzystaæ z tej warto¶ci --- (ignorowany).
 * Program oceniaj±cy wypisuje na standardowym wyj¶ciu w pierwszym wierszu
 * jedn± liczbê ca³kowit±, oznaczaj±c± procent poprawnie zdekodowanych
 * liter, wystêpuj±cych w pliku NazwaIN (tj. pliku z zaszyfrowan± wiadomo¶ci±),
 * a w przypadku wyst±pienia b³êdu sk³adni (patrz ni¿ej) w drugim wierszu
 * wypisuje komunikat "SYNTAX"
 *
 * (uwagi:
 *   - w przypadku porównywania liter nie jest rozró¿niana ich wielko¶æ,
 *   - je¶li w pliku NazwaOK zostanie napotkany znak nie bêd±cy liter±,
 *     a porównywany z nim znak z pliku NazwaOUT bêdzie od niego ró¿ny,
 *     to zostanie to potraktowane jako b³±d sk³adni)
 *
}


program crachk;


function Check(var f1, f2: text; var syntax: boolean): integer;
{ zwraca jaki procent liter z pliku f1 wystêpuje w pliku f2 }
var
  correct, all: longint;
  c1, c2: char;

begin
  syntax := false;
  correct := 0; all := 0;
  
  while not (Eof(f1) or Eof(f2)) do begin
    while not (Eoln(f1) or Eoln(f2)) do begin
      Read(f1, c1);
      c1 := UpCase(c1);
      
      Read(f2, c2);
      c2 := UpCase(c2);
      
      if c1 in ['A'..'Z'] then begin
        Inc(all);
        if c1 = c2 then
          Inc(correct);
      end
      else
        if c1 <> c2 then
	  syntax := true;
    end;
  
    if not Eof(f1) and Eoln(f1) then
      Readln(f1);
    if not Eof(f2) and Eoln(f2) then
      Readln(f2);
  end;

  Check := round((100 * correct) / all);
end;


var
  fOUT, fOK: text;
  syntax: boolean;

begin
  Assign(fOUT, ParamStr(2));
  Assign(fOK, ParamStr(3));
  Reset(fOUT);
  Reset(fOK);
  Writeln(Check(fOK, fOUT, syntax));
  if syntax then
    Writeln('SYNTAX');
  Close(fOUT);
  Close(fOK);
end.
