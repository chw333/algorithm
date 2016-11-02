{$N+,Q-,R-,S-,B-}
var
  f:array[0..38,0..19]of comp;
  n,d:integer;
procedure main;
  var i,j,n1,d1,k:integer;
      s:comp;
  begin;
    fillchar(f,sizeof(f),0);
    f[0,0]:=1;
    for i:=1 to n do if not odd(i) then
      for j:=i div 2 downto 1 do begin
        f[i,j]:=f[i-2,j-1];
        for n1:=i-2 downto 2 do if not odd(n1) then begin
          s:=0;
          for k:=0 to j do s:=s+f[i-n1,k];
          f[i,j]:=f[i,j]+s*f[n1-2,j-1];
          for d1:=j-1 downto 1 do
            f[i,j]:=f[i,j]+f[n1-2,d1-1]*f[i-n1,j];
        end;
      end;
    writeln(f[n,d]:0:0);
  end;
begin
  assign(input,'par.in');
  reset(input);
  assign(output,'par.out');
  rewrite(output);
  readln(n,d);
  main;
  close(input);
  close(output);
end.