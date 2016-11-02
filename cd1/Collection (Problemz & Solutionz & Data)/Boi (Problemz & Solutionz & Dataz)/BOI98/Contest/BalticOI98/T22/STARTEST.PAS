program startest;

var f1,f2 : text;
    n1,n2,m1,m2 : integer;
    s1,s2 : integer;
    t1,t2 : string;

procedure upper(var s : string);
var i : integer;
begin
  for i := 1 to length(s) do s[i] := upcase(s[i]);
end;

begin
  if paramcount<>2 then begin
    writeln('usage: <correct answer> <testfile>');
    exit;
  end;
  assign(f1,paramstr(1));
  assign(f2,paramstr(2));
  {$I-}
  reset(f1);
  if IOresult<>0 then begin
    writeln('error opening file ',paramstr(1));
    exit;
  end;
  {$I+}
  {$I-}
  reset(f2);
  if IOresult<>0 then begin
    writeln('error opening file ',paramstr(2));
    exit;
  end;
  {$I+}

  readln(f1,t1);
  readln(f2,t2);
  upper(t2);
  if (t1 = 'NO SOLUTION') and (t2 = 'NO SOLUTION') then
  begin
    writeln('correct answer');
    exit;
  end;

  if (t1 = 'NO SOLUTION') or (t2 = 'NO SOLUTION') then
  begin
    writeln('wrong answer -- no solution');
    exit;
  end;

  reset(f1);
  reset(f2);

  {$I-}
  read(f1,n1,n2);
  if IOresult <>0 then
  begin
    writeln('error reading file, ',paramstr(1));
    exit;
  end;
  {$I+}

  {$I-}
  read(f2,m1,m2);
  if ioresult<>0 then begin
    writeln('error reading file, ',paramstr(2));
    exit;
  end;
  {$I+}

  if (n2<>m2) then
  begin
    writeln('wrong answer: max sum');
    exit;
  end;

  if (n1<>m1) then
  begin
    writeln('wrong answer: minimal sum');
    exit;
  end;


  writeln('correct answer');

end.