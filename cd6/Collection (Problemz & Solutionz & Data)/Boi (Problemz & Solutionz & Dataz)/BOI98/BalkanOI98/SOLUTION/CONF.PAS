{Programed by Grant Guo, Email: grantguo@iname.com}
Const
  Maxn=100;
Var
  Dist:Array[1..Maxn,1..Maxn]of Integer;
  Edge:Array[1..Maxn,1..Maxn]of Byte;
  Used:Array[1..Maxn,1..Maxn]of Boolean;
  s:Array[1..3]of Byte;
  Num:Integer;
  n,M:Byte;
Procedure ReadMap;
  Var e,i,j,a,b,c:Integer;
  Begin
    Assign(Input,'Conf.Inp');
    Reset(Input);
    Readln(n,e);
    for i:=1 to n do
      for j:=1 to n do
        if i=j then dist[i,j]:=0
               else dist[i,j]:=-1;
    Fillchar(Edge,sizeof(Edge),0);
    for i:=1 to e do begin
      readln(a,b,c);
      if (dist[a,b]=-1) or (c<dist[a,b]) then begin
         dist[a,b]:=c;
         dist[b,a]:=c;
         Edge[a,b]:=c;
         Edge[b,a]:=c;
      end;
    end;
    readln(s[1],s[2],s[3]);
    close(input);
  End;
Procedure MakeDist;
  Var i,j,k:Byte;
  Begin
    for i:=1 to n do
      for j:=1 to n do
        for k:=1 to n do
          if (dist[j,i]>=0) and (dist[i,k]>=0) and ((dist[j,k]<0) or (dist[j,i]+dist[i,k]<dist[j,k])) then
             dist[j,k]:=dist[j,i]+dist[i,k];
  End;
Function Mid:Byte;
  Var i,Min:Byte;
      Sum:Integer;
  Begin
    Sum:=Maxint;
    For i:=1 to n do
      if (Dist[i,s[1]]>=0) and (Dist[i,s[2]]>=0) and (Dist[i,s[3]]>=0)
      and (Dist[i,s[1]]+Dist[i,s[2]]+Dist[i,s[3]]<Sum) then Begin
          Sum:=Dist[i,s[1]]+Dist[i,s[2]]+Dist[i,s[3]];
          Min:=i;
      End;
    Mid:=Min;
  End;
Procedure Mark(a,b:Byte);
  Var i:Byte;
  Begin
    if a=b then exit;
    For i:=1 to n do
      if (Edge[a,i]>0) and (Edge[a,i]+Dist[i,b]=Dist[a,b]) then Begin
         if Not Used[a,i] then Inc(Num);
         Used[a,i]:=true;
         Used[i,a]:=true;
         Mark(i,b);
         Exit;
      End;
  End;
Procedure Print;
  Var i,j:Byte;
  Begin
    Assign(Output,'Conf.Out');
    Rewrite(Output);
    Writeln(Dist[M,S[1]]+Dist[M,s[2]]+Dist[M,s[3]],' ',Num);
    for i:=1 to n-1 do
      for j:=i+1 to n do
        if used[i,j] then writeln(i,' ',j);
    close(output);
  End;
Begin
  ReadMap;
  MakeDist;
  M:=Mid;
  Fillchar(Used,Sizeof(Used),0);
  Num:=0;
  Mark(s[1],M);
  Mark(s[2],M);
  Mark(s[3],M);
  Print;
End.







