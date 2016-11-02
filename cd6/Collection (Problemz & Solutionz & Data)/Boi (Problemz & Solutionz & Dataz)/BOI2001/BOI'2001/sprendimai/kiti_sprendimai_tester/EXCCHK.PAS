{Checker for task Excursion
 2001.05.21
 
 Based on:
   Sprawdzaczka dla zadania Spokojna Komisja
   2001.01.31, Tomasz Waleñ}
{$I+ $R+}

{ interfejs sprawdzaczki zgodny ze standardem: 
 
 * Modul sprawdzajacy wyjscie zawodnika.
 *
 * Program oceniajacy uruchamia sie z czterema parametrami:
 *    1 - NazwaIN - plik wejsciowy
 *    2 - NazwaOUT - odpowiedz zawodnika,
 *    3 - NazwaOK - nazwa pliku z podpowiedzia.
 *    4 - NrTestu - program nie powinien korzystac z tej wartosci.
 * Program oceniajacy wypisuje na standardowym wyjsciu
 * w pierwszym wierszu jedno slowo wielkimi literami:
 *    OK - wyjscie prawidlowe,
 *    SYNTAX - wyjscie prawidlowe, ale sa bledy skladni,
 *    WRONG - wyjscie bledne.
 * Druga linijka jest opisem niepoprawnosci.
 * Wyjscie bledow jest takie samo jest standardowe wyjscie,
 * program oceniajacy nie powinien wypisywac na nim zadnych informacji.
 * Jesli pierwsza linia nie bedzie zgodna ze specyfikacja
 * przyjumje sie, ze wyjscie zostalo ocenione jako bledne.
 * Program nie musi sprawdzac czy istnieja wskazane pliki
 * gdyz jest to gwarantowane przez sprawdzaczke.
 }
 
program spospr;
const
   max_n = 8000;
   white  = [#0,#9,#13,' '];
   white2 = [#0,#9,#10,#13,' '];
   max_token_len = 100;
type
   pbool = ^tbool;
   tbool = array[1..max_n] of boolean;
var
   f : text;
   
   p	: pbool;
   i	: integer;
   n,m	: integer;
   a,b	: integer;
   nie	: boolean;
   s	: string;

  function read_token(var f:text;to_eol:boolean):string;
  var
    tmp : string;
    ch  : char;
    i   : integer;
  begin
    ch:=#0;
    if (to_eol) then
      while (not eof(f)) and (ch in white) do read(f,ch)
    else
      while (not eof(f)) and (ch in white2) do read(f,ch);

    if (not to_eol) and (ch in white2) then read_token:='EOF'
    else if (ch in white) then read_token:='EOF'
    else begin
      if (ch<>#10) then begin {jesli to nie jest przejscie do nastepnej linii}
        i:=0;
        tmp:='';
        while (not (ch in white)) do begin
          tmp:=tmp+ch;
          i:=i+1;
          if (eoln(f)) then break;
	  if (eof(f)) then break;
          if (i=max_token_len) then break;
          read(f,ch);
        end;
	read_token:=tmp;
      end else read_token:='EOLN';
    end;
  end;


{jakies bledy wewnetrzne, np. zly plik in}
procedure blad(s : string);
begin
   Writeln('ERROR');
   Writeln(s);
   halt(255);
end; { blad }

function instr(vv : longint):string;
var
   tmp : string;
begin
   Str(vv,tmp);
   instr:=tmp;
end; { instr }

const NOT_NUMBER = -MaxInt;

function inval(ss : string):longint;
var
  code    : integer;
  tmp_res : longint;
begin
  Val(ss,tmp_res,code);
  if (code<>0) then tmp_res:=NOT_NUMBER;
  inval:=tmp_res;
end;

{zla odpowiedz}
procedure zle(s	: string);
begin
   Writeln('WRONG');
   Writeln(s);
   halt(1);
end;

procedure read_input;

begin
   Assign(f,paramstr(1));
   {$I-}
   reset(f);
   if IOResult<>0 then blad('nie moge otworzyc pliku '+paramstr(1));
   {$I+}
   readln(f,m,n);
   for i:=1 to m do begin
      s:=read_token(f,true);
      a:=inval(s);
      if (a=NOT_NUMBER) then blad('bledny plik IN, oczekiwano liczby a wczytano "'+s+'"');

      s:=read_token(f,true);
      b:=inval(s);
      if (b=NOT_NUMBER) then blad('bledny plik IN, oczekiwano liczby a wczytano "'+s+'"');

      readln(f);

      if (a<-n) or (a>n) or (a=0) then blad('bledny plik IN (a out of range)');
      if (b<-n) or (b>n) or (b=0) then blad('bledny plik IN (b out of range)');

      if ((a > 0) xor p^[abs(a)]) and
         ((b > 0) xor p^[abs(b)]) then 
	 zle('traveller '+instr(i)+' is not satisfied (wish '+instr(a)+' '+instr(b)+')'); 
   end;
   close(f);
end;

procedure read_answer;
var a, last_a, l, i : integer;
begin

   new(p);
   Assign(f,paramstr(2));
   {$I-}
   reset(f);
   {$I+}
   if IOResult<>0 then blad('nie moge otworzyc pliku '+paramstr(2));

   for i:=1 to n do p^[i]:=false;

   nie:=false; last_a := 0;
   s:=read_token(f,false);
   if (s='NO') then begin
     nie:=true;
   end else begin
     l := inval(s);
     if (l=NOT_NUMBER) then zle('number expected, instead of: '+s);
     last_a := -1;
     for i:=1 to l do begin
        s := read_token(f,false);
        a:=inval(s);
        if (a=NOT_NUMBER) then zle('number expected, instead of: '+s);
        if (a<1) or (a>n) then zle('there is no city '+s);
	if (a <= last_a) then zle('not in ascending order on city '+s);
	last_a := a;
        p^[a]:=true;
     end;
   end;
   close(f);
   if nie then begin
      {sprawdzamy w hintfile'u czy jest rozwiazanie}
      Assign(f,paramstr(3));
      {$I-}
      reset(f);     
      {$I+}
      if IOResult<>0 then blad('nie moge otworzyc pliku '+paramstr(3));
      s:=read_token(f,true);
      if s<>'NO' then zle('the output is NO, but solution exists');
      close(f);
   end;
end;

procedure read_n_m;
begin
   Assign(f,paramstr(1));
   {$I-}
   reset(f);
   if IOResult<>0 then blad('nie moge otworzyc pliku '+paramstr(1));
   {$I+}
   readln(f,m,n);
   close(f);
end;

begin
  read_n_m;
  read_answer;
  if not nie then read_input;
  Writeln('OK');
  halt(0);
end.
