Program Generator;
Const
  dFname = '9.in';
  n = 15;
  m = 80;
Var
  F : Text;
  i, j, k : Integer;
  S : String;
Begin
  RandomIze;
  Assign(F, dFname);
  Rewrite(F);
    Writeln(F, n, ' ', m);
    For i := 1 to m do
      Begin
        Write(F, Random(1000) + 10);
        S := '';
        For j := 1 to n do
          begin
            if Random(10) < 8 then S := S + '0' else
              if Random(10) < 5 then S := S + '-' else
                S := S + '+';
          end;
        Write(F, ' ', S);
        S := '';
        For j := 1 to n do
          begin
            if Random(10) < 4 then S := S + '0' else
              if Random(10) < 8 then S := S + '-' else
                S := S + '+';
          end;
        Writeln(F, ' ', S);
      end;
  Close(F);
end.
