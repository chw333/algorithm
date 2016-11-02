var
  result:array[1..30000] of boolean;
  am,an,an0:array[1..3] of integer;
  n,m,x,i,sum:integer;
  time:longint;

function cacu(a,b,c:integer):boolean;
var
  max,i,now:integer;
  succ:boolean;
begin
  cacu:=false;
  am[1]:=a; am[2]:=b; am[3]:=c;
  max:=0; for i:=1 to 3 do if am[i]>max then begin max:=am[i]; now:=i; end;
  repeat
    case now of
      1:begin
          if am[2]=am[3] then begin succ:=true; break; end;
          am[1]:=abs(am[2]-am[3]);
          max:=0; for i:=1 to 3 do if am[i]>max then begin max:=am[i]; now:=i; end;
          an[now]:=an[1]-1;
        end;
      2:begin
          if am[1]=am[3] then begin succ:=true; break; end;
          am[2]:=abs(am[1]-am[3]);
          max:=0; for i:=1 to 3 do if am[i]>max then begin max:=am[i]; now:=i; end;
          if now<=2 then an[now]:=an[2] else an[now]:=an[2]-1;
        end;
      3:begin
          if am[2]=am[1] then begin succ:=true; break; end;
          am[3]:=abs(am[2]-am[1]);
          max:=0; for i:=1 to 3 do if am[i]>max then begin max:=am[i]; now:=i; end;
          an[now]:=an[3];
        end;
    end;
  until an[now]<=0;
  cacu:=succ and (an[now]=1);
end;

begin
  assign(input,'guess.in8');
  reset(input);
  assign(output,'guess.out');
  rewrite(output);

  time:=meml[$40:$6c];
  read(n,m);
  while (n<>-1) and (m<>-1) do
    begin
      x:=((n-1) mod 3)+1;
      for i:=1 to 3 do an[i]:=n div 3;
      for i:=1 to n mod 3 do inc(an[i]);
      an0:=an;
      fillchar(result,sizeof(result),0);
      for i:=1 to m-1 do
        begin
          an:=an0;
          case x of
            1:result[i]:=cacu(m,i,m-i);
            2:result[i]:=cacu(i,m,m-i);
            3:result[i]:=cacu(i,m-i,m);
          end;
        end;
      sum:=0;
      for i:=1 to m-1 do if result[i] then inc(sum);
      writeln(sum);
      for i:=1 to m-1 do if result[i] then
        begin
          case x of
            1:writeln(m,' ',i,' ',m-i);
            2:writeln(i,' ',m,' ',m-i);
            3:writeln(i,' ',m-i,' ',m);
          end;
        end;
      read(n,m);
    end;
  close(input);
  close(output);
  assign(output,'');
  rewrite(output);
  writeln((meml[$40:$6c]-time)/18.2:0:2);
  close(output);
end.
