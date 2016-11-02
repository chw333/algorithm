Program Generator;
Const
  dFname = '10.in';
  n = 13;
  m = 20;
  k = 50;
Var
  F : Text;
  i, j, p, hold, r : Integer;
Begin
  RandomIze;
  Assign(F, dFname);
  Rewrite(F);
    Writeln(F, n, ' ', m, ' ', k);
    For i := 1 to m do
      Begin
        hold := Random(7) + 2;
        r := Random(n div 2) + 2;
        Write(F, hold, ' ', r);
        For j := 1 to r do
          Begin
            p := Random(n + 2) - 1;
            Write(F, ' ', p);
          end;
        Writeln(f);
      end;
  Close(F);
end.
