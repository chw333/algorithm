{Programed by Grant Guo, Email: grantguo@iname.com}
Const
  Maxn=200;
Type
  Listtype=Array[1..Maxn]of Integer;
  EdgeList=Array[1..Maxn]of Record
                              No,Len:Byte;
                            End;
Var
  Dist:Array[1..Maxn]of ^Listtype;
  n:Byte;
  Node:Array[1..Maxn]of Record
                          Num:Byte;
                          Link:^EdgeList;
                        End;
  Arrived:Array[1..Maxn]of Boolean;
  s,t:Byte;
  Best:Integer;
  BestWay,Mark:Array[0..Maxn]of Integer;
Procedure ReadMap;
Procedure Add(a,b,l:Byte);
  Begin
    if Node[a].Num=0 then New(Node[a].Link);
    Inc(Node[a].Num);
    Node[a].Link^[Node[a].Num].No:=b;
    Node[a].Link^[Node[a].Num].Len:=l;
  End;
  Var
    a,b,l:Byte;
    E,i:Integer;
  Begin
    Assign(input,'MEET.INP');
    Reset(input);
    n:=0;
    readln(E,s,t);
    for i:=1 to Maxn do Node[i].Num:=0;
    for i:=1 to E do Begin
      readln(a,b,l);
      if a>n then n:=a;
      if b>n then n:=b;
      Add(a,b,l);
      Add(b,a,l);
    End;
    Close(Input);
  End;
Procedure MakeDist;
  Var i,j,k:Byte;
  Begin
    for i:=1 to n do Begin
      New(Dist[i]);
      For j:=1 to n do
        if i=j then Dist[i]^[j]:=0
               else Dist[i]^[j]:=-1;
    End;
    For i:=1 to n do
      For j:=1 to Node[i].Num do
        Dist[i]^[Node[i].Link^[j].No]:=Node[i].Link^[j].Len;
    For k:=1 to n do
      for i:=1 to n do
        for j:=1 to n do
          if (Dist[i]^[k]>=0) and (Dist[k]^[j]>=0) then
             if (Dist[i]^[j]<0) or (Dist[i]^[k]+Dist[k]^[j]<Dist[i]^[j]) then
                Dist[i]^[j]:=Dist[i]^[k]+Dist[k]^[j];
  End;
Procedure Run(Now:Byte;Sum:Integer);
  Var i,Num:Byte;
  Begin
    Mark[Sum]:=Now;
    if Now=t then Begin
       if Not Odd(Sum) and (Mark[Sum div 2]>0) then Begin
          Best:=Sum;
          BestWay:=Mark;
       ENd;
       Mark[Sum]:=0;
       Exit;
    End;
    Num:=Node[Now].Num;
    for i:=1 to Num do
      if Not Arrived[Node[Now].Link^[i].No] and
         (Dist[Node[Now].Link^[i].No]^[t]+Sum+Node[Now].Link^[i].Len<Best) then Begin
           Arrived[Node[Now].Link^[i].No]:=true;
           Run(Node[Now].Link^[i].No,Sum+Node[Now].Link^[i].Len);
           Arrived[Node[Now].Link^[i].No]:=false;
         End;
    Mark[Sum]:=0;
  End;
Procedure Print;
  Var i:Byte;
  Begin
    Assign(Output,'MEET.OUT');
    Rewrite(Output);
    For i:=0 to Best div 2-1 do
      if BestWay[i]>0 then Write(BestWay[i],' ');
    Writeln(BestWay[Best div 2]);
    for i:=Best downto Best div 2+1 do
      if BestWay[i]>0 then Write(BestWay[i],' ');
    Writeln(BestWay[Best Div 2]);
  ENd;

Begin
  ReadMap;
  MakeDist;
  Fillchar(Arrived,Sizeof(Arrived),0);
  Best:=2002;
  Fillchar(Mark,Sizeof(Mark),0);
  Run(s,0);
  Print;
End.


