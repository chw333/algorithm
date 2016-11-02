const
  FINNAME = 'markov.in';
  FOUTNAME = 'markov.out';
  FSAMPLENAME = 'sample.txt';
  MAXWORDS = 10000;
  NHASH = 4093;
  MULTIPLIER = 37;

type
  pState = ^State;
  pSuffix = ^Suffix;
  State = record
    Pre: Integer;
    Suf: pSuffix;
    Next: pState;
  end;
  Suffix = record
    Word: Integer;
    Next: pSuffix;
  end;
  pString = ^String;
  Prefix = array [1..2] of String;

var
  Fin, Fout, Fsample: Text;
  Table: array [1..MAXWORDS] of pString;
  Index: array [1..MAXWORDS] of Integer;
  nWords, nPres: LongInt;

function GetNextWord: String;
var
  S: string;
  i: Integer;
begin
  i := 0;
  while not Eof(Fsample) do
  begin
    Inc(i);
    Read(Fsample, S[i]);
    if S[i] = ' ' then Break;
  end;
  if (i > 0) and (S[i] = ' ') then S[0] := Chr(i - 1)
  else S[0] := Chr(i);
  GetNextWord := S;
end;

function Lookup(var Pre: Prefix;l, r: Integer): Integer;
var
  m: Integer;
begin
  if l > r then begin Lookup := 0; Exit; end;
  m := (l + r) div 2;
  if (Table[Index[m]]^ = Pre[1]) and (Table[Index[m] + 1]^ = Pre[2]) then
    Lookup := m
  else if (Table[Index[m]]^ < Pre[1]) or
          ((Table[Index[m]]^ = Pre[1]) and
           (Table[Index[m] + 1]^ < Pre[2])
          ) then Lookup := Lookup(Pre, m + 1, r)
  else Lookup := Lookup(Pre, l, m - 1);
end;

procedure Sort(l, r: Integer);
var
  i, j, k: Integer;
begin
  if l >= r then Exit;
  i := Random(r - l + 1) + l;
  k := Index[l]; Index[l] := Index[i];
  i := l; j := r;
  repeat
    while (i < j) and
          ((Table[Index[j]]^ > Table[k]^) or
           ((Table[Index[j]]^ = Table[k]^) and
            (Table[Index[j] + 1]^ >= Table[k + 1]^)
           )
          ) do Dec(j);
    if i >= j then Break;
    Index[i] := Index[j]; Inc(i);
    while (i < j) and
          ((Table[Index[i]]^ < Table[k]^) or
           ((Table[Index[i]]^ = Table[k]^) and
            (Table[Index[i] + 1]^ <= Table[k + 1]^)
           )
          ) do Inc(i);
    if i >= j then Break;
    Index[j] := Index[i]; Dec(j);
  until False;
  Index[i] := k;
  Sort(l, i - 1); Sort(i + 1, r);
end;

procedure Build;
var
  S: string;
  Pre: Prefix;
begin
  nWords := 0;
  repeat
    S := GetNextWord;
    if S[0] <> #0 then
    begin
      Inc(nWords);
      GetMem(Table[nWords], Length(S) + 1);
      Table[nWords]^ := S;
      Index[nWords] := nWords;
    end;
  until S[0] = #0;
  Randomize;
  Sort(1, nWords);
end;

procedure Main;
var
  i, j, k: LongInt;
  S: string;
  Pre: Prefix;
begin
  ReadLn(Fin, nPres);
  for i := 1 to nPres do
  begin
    ReadLn(Fin, S);
    j := Pos(' ', S);
    Pre[1] := Copy(S, 1, j - 1);
    Pre[2] := Copy(S, j + 1, Length(S) - j);
    j := Lookup(Pre, 1, nWords);
    if j = 0 then WriteLn(Fout)
    else begin
      k := j;
      repeat
        if j > nWords then Break
        else begin
          if Index[j] + 2 <= nWords then
            Write(Fout, Table[Index[j] + 2]^, ' ');
          Inc(j);
        end;
      until (Table[Index[j]]^ <> Pre[1]) or (Table[Index[j] + 1]^ <> Pre[2]);
      j := k - 1;
      while (j >= 1) and (Table[Index[j]]^ = Pre[1]) and (Table[Index[j] + 1]^ = Pre[2]) do
      begin
        if Index[j] + 2 <= nWords then
          Write(Fout, Table[Index[j] + 2]^, ' ');
        Dec(j);
      end;
      WriteLn(Fout);
    end;
  end;
end;

begin
  Assign(Fin, FINNAME);
  Reset(Fin);
  Assign(Fsample, FSAMPLENAME);
  Reset(Fsample);
  Assign(Fout, FOUTNAME);
  Rewrite(Fout);
  Build;
  Main;
  Close(Fin);
  Close(Fsample);
  Close(Fout);
end.