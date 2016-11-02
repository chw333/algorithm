Program Mkdata (input , output);
Const
  DataN = 100;
  InName = 'h.in';
Var
  infp : text;
  i , j : integer;
Begin
  assign (infp , inname); rewrite (infp);
  writeln (infp , DataN);
  for i :=1 to DataN do
    begin
      for j :=1 to 5 do
        write (infp , random (100) + 1 , ' ');
      writeln (infp , random (1000) + 1);
    end;
  close (infp);
end. {main}