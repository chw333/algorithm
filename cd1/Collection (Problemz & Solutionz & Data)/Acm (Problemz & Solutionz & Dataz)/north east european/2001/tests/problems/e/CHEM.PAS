{ Solution for CHEMISTRY problem for NEERC'2001 }
{ (C) Roman Elizarov, 2001 }
{ Time to solve and extensively debug: 2 hours 20 min }
{.$DEFINE DEBUG}
{.$DEFINE EXPLAIN}
{$M 65520,0,655360}
{$A+,B-,D+,E+,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
program CHEMISTRY_SOLUTION;

procedure fatal(s: string);
begin
  writeln('*** FATAL ERROR: ', s, ' ***');
  halt;
end;

function str(i: integer): string;
var
  s: string;
begin
  System.str(i, s);
  str := s;
end;

const
  MAXL=100;      { Max. formulae length }
  MAXN=10;       { Max. no. of alternate answers }
  MAX_CHEM=100;  { At most 100 chem. elements }
  MAX_SUM=10000; { At most 10000 chem. element on each side of equation }

type
  TStr = string[MAXL];
  TChem = string[2];
  TParse = array[1..MAX_CHEM] of integer;


var
  chem_cnt: integer;
  parse_new_chem: boolean;
  chems: array[1..MAX_CHEM] of TChem;

(*
  <formulae> ::= [<number>] <sequence> { '+' [<number>] <sequence> }
  <sequence> ::= <element> [<number>] { <element> [<number>] }
  <element>  ::= <chem> | '(' <sequence> ')' 
  <chem>     ::= <upper_case_letter> [ <lower_case_letter> ]
*)

type
  TToken = (_eoln, _number, _chem, _open, _close, _plus);

var
  p_idx: integer; { Parser index for next char }
  p_str: TStr; { Parser string }
  p_tok: TToken; { Parser token }
  p_num: integer; { Parser nubmer if p_tok = _number, or chem index if p_tok = _chem }

procedure next_token; 
var
  ch: char;
  chem: TChem;
  i: integer;
  t: longint;
begin
  if p_idx > length(p_str) then begin
    p_tok := _eoln;
    exit;
  end;
  ch := p_str[p_idx];
  case ch of 
    '(': begin p_tok := _open; inc(p_idx) end;
    ')': begin p_tok := _close; inc(p_idx) end;
    '+': begin p_tok := _plus; inc(p_idx) end;
    '1'..'9': 
      begin
        p_tok := _number;
        t := 0;
        while ch in ['0'..'9'] do begin
          t := t * 10 + (ord(ch) - ord('0'));
          if t > MAX_SUM then
            fatal('Number is too big');
          inc(p_idx);
          if p_idx > length(p_str) then
            break;
          ch := p_str[p_idx];
        end;
        if t < 2 then
          fatal('Number is less than 2');
        p_num := t;
      end;
    'A'..'Z':
      begin
        p_tok := _chem;
        p_num := 0;
        chem[1] := ch;
        inc(p_idx);
        if (p_idx <= length(p_str)) and (p_str[p_idx] in ['a'..'z']) then begin
          chem[2] := p_str[p_idx];
          chem[0] := chr(2);
          inc(p_idx);
        end else
          chem[0] := chr(1);
        for i := 1 to chem_cnt do 
          if chems[i] = chem then begin
            p_num := i;
            break;
          end;
        if p_num = 0 then begin
          parse_new_chem := true;
          if chem_cnt < MAX_CHEM then begin
            inc(chem_cnt);
            chems[chem_cnt] := chem;
            p_num := chem_cnt;
          end;
        end;
      end;
    else fatal('Invalid character "' + ch + '"');
  end;
end;

procedure parse_sequence(var p: TParse); forward;

procedure parse_element(var p: TParse);
begin
  case p_tok of 
    _chem: 
      begin
        if p_num > 0 then
          inc(p[p_num]);
        next_token;
      end;
    _open: 
      begin
        next_token;
        parse_sequence(p);
        if p_tok <> _close then
          fatal('")" is missing');
        next_token;
      end;
    else fatal('Invalid element at ' + str(p_idx));
  end;
end;

procedure parse_sequence(var p: TParse);
var
  this_p: TParse;
  this_e: TParse;
  mult, mult_e: integer;
  i: integer;
begin
  { General multiplier }
  if p_tok = _number then begin
    mult := p_num;
    next_token;
  end else
    mult := 1;
  { This sequence init & parse }
  fillchar(this_p, sizeof(this_p), 0);
  repeat
    fillchar(this_e, sizeof(this_e), 0);
    parse_element(this_e);
    if p_tok = _number then begin
      mult_e := p_num;
      next_token;
    end else
      mult_e := 1;
    for i := 1 to chem_cnt do begin
      inc(this_p[i], mult_e * this_e[i]);
      if this_p[i] > MAX_SUM then
        fatal('Number is too big');
    end;
  until not (p_tok in [_number, _open, _chem]);
  { Multiply & add }
  for i := 1 to chem_cnt do begin
    inc(p[i], mult * this_p[i]);
    if p[i] > MAX_SUM then
      fatal('Number is too big');
  end;
end;

procedure parse(const s: TStr; var p: TParse);
begin
  if length(s) > MAXL then
    fatal('String is too long');
  { Init counters for chems }
  fillchar(p, sizeof(p), 0);
  { Init parser }
  p_str := s;
  p_idx := 1;
  next_token;
  { Parse formulae }
  while true do begin
    parse_sequence(p);
    case p_tok of
      _plus: next_token;
      _eoln: break;
      else fatal('Invalid formulae');
    end;
  end;
end;


var
  n, i, j, ok_cnt: integer;
  s: array[0..MAXN] of TStr;
  p: array[0..MAXN] of TParse;
  ok: boolean;
  ind_ok: array[1..MAXN] of boolean;


begin
  assign(input, 'chem.in'); reset(input);
  {$IFNDEF DEBUG} assign(output, 'chem.out'); rewrite(output); {$ENDIF}
  { Init chemicals }
  chem_cnt := 0;
  { Read input & Parse }
  readln(s[0]);
  parse(s[0], p[0]);
  read(n);
  if not eoln or (n < 1) or (n > MAXN) then
    fatal('Invalid number of answers');
  readln;
  for i := 1 to n do begin
    readln(s[i]);
    parse_new_chem := false;
    parse(s[i], p[i]);
    ind_ok[i] := not parse_new_chem;
  end;
  if not seekeof then 
    fatal('Extra data in file');
  { Solve & output }
  for i := 1 to n do begin
    ok := ind_ok[i];
    if ok then
      for j := 1 to chem_cnt do 
        if p[0,j] <> p[i,j] then begin
          ok := false;
          {$IFDEF EXPLAIN }
          writeln('*** ', chems[j], ': ', p[0,j], ' != ', p[i,j]);
          {$ENDIF}
          break;
        end;
    write(s[0]);
    if ok then
      write('==')
    else
      write('!=');
    writeln(s[i]);
  end;
end.
