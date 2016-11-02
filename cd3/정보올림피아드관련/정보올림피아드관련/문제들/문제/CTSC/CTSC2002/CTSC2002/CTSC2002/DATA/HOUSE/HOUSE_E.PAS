{House Judge by Ziqing Mao}
program HJudge;
  var f1,f2:text; a1,b1,a2,b2,k,t,i:integer;
      s,s1,s2:string;
      a,b:array[1..1000]of string;
      v:array[1..1000]of boolean;
  label U;

  procedure Error;
    begin
      writeln(0);
      halt;
    end;

    begin
      assign(f1,paramstr(2));
      reset(f1);
      assign(f2,paramstr(1));
      reset(f2);
      readln(f1,a1,b1);
      readln(f2,a2,b2);
      if (a1<>a2) or (b1<>b2) then Error;
      t:=0;
      while not seekeof(f1) do
        begin
          readln(f1,s);
          k:=pos(' ',s);
          inc(t);
          a[t]:=copy(s,1,k-1);
          b[t]:=copy(s,k+1,length(s)-k);
        end;
      fillchar(v,sizeof(v),0);
      while not seekeof(f2) do
        begin
          readln(f2,s);
          k:=pos(' ',s);
          s1:=copy(s,1,k-1);
          s2:=copy(s,k+1,length(s)-k);
          for i:=1 to t do
          if not v[i] then
            if ( (s1=a[i]) and (s2=b[i]) ) or ( (s1=b[i]) and (s2=a[i]) ) then
              begin
                v[i]:=true;
                goto U;
              end;
          Error;
          U:
        end;
      for i:=1 to t do if not v[i] then Error;
      close(f1);
      close(f2);
      writeln(10);
    end.
