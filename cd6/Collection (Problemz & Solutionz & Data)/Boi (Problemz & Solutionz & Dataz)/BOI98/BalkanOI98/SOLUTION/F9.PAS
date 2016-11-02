{Programed by Grant Guo, Email: grantguo@iname.com}
Type
  Rectype=array[1..4]of Byte;
  Settype=Set of Byte;
  ScoreList=Array[1..8]of Byte;

Var
  Can:array[1..8,0..5,0..90]of Boolean;
  List:Array[1..1700]of Rectype;
  Num:Integer;
  Drivers,Races,Top:Byte;
  Score:Array[0..4]of Byte;
  Final,InitScore:ScoreList;
  Total:Longint;
  NR:Byte;

  Stack:Array[1..5]of Integer;

procedure ReadData;
  var i:byte;
  begin
    assign(input,'f9.inp');
    reset(input);
    readln(Drivers,Races,Top);
    Score[0]:=0;
    for i:=1 to Top do read(Score[i]);
    readln;
    for i:=1 to Drivers do read(Final[i]);
    close(input);
  end;

procedure Initialize;
  Var i,j,k,l:Byte;
      Rec:Rectype;
      Used:Array[1..8]of Boolean;

  Procedure Make(Lev:Byte);
    Var i:Byte;
    Begin
      if Lev=Top+1 then Begin
         Inc(Num);
         List[Num]:=Rec;
         Exit;
      End;
      For i:=1 to Drivers do
        if Not Used[i] then Begin
           Used[i]:=true;
           Rec[Lev]:=i;
           Make(Lev+1);
           Used[i]:=false;
        End;
    End;

  Begin
    Fillchar(InitScore,Sizeof(InitScore),0);
    NR:=1;
    For i:=1 to Races do NR:=NR*i;
    Num:=0;
    Fillchar(Used,Sizeof(Used),0);
    Make(1);
    Fillchar(Can,sizeof(Can),0);
    For i:=1 to Drivers do begin
      Can[i,Races,Final[i]]:=true;
      for j:=Races-1 downto 0 do
        for k:=0 to Final[i] do
          for l:=0 to Top do
            Can[i,j,k]:=Can[i,j,k] or Can[i,j+1,k+Score[l]];
    end;
  End;

Function Pass:Boolean;
  Var Score_Per_Race,Sum:Integer;
      i:Byte;
  Begin
    Pass:=False;
    Sum:=0;
    For i:=1 to Drivers do Begin
      if Not Can[i,0,0] then exit;
      Inc(Sum,Final[i]);
    End;
    Score_Per_Race:=0;
    For i:=1 to Top do Inc(Score_Per_Race,Score[i]);
    Pass:= Sum = Score_Per_Race*Races;
  End;

Procedure Run(Rno:Byte;Low:Integer;Last,De:Byte;Now:ScoreList);
  Var i:Integer;
      j:Byte;
      Ok:Boolean;
  Begin
    if Rno=Races+1 then Begin
       Inc(Total,NR div De);
       Exit;
    End;
    For i:=Low to Num do Begin
      For j:=1 to Top do Inc(Now[List[i,j]],Score[j]);
      Ok:=true;
      For j:=1 to Drivers do
        if Not Can[j,Rno,Now[j]] then Begin
           Ok:=false;
           Break;
        End;
      if Ok then Begin
         if i=Low then Inc(Last)
                  else Last:=1;
         Stack[Rno]:=i;
         Run(Rno+1,i,Last,De*Last,Now);
      End;
      For j:=1 to Top do Dec(Now[List[i,j]],Score[j]);
    End;
  End;

Begin
  ReadData;
  Assign(Output,'f9.out');
  Rewrite(Output);
  Total:=0;
  Initialize;
  if Pass then Run(1,1,0,1,InitScore);
  Writeln(Total);
  Close(Output);
End.
