{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R+,S-,T-,V-,X+,Y+}
{$M 65520,0,655360}
program Resistor;

  uses Crt;

  const
    MaxResist = 300;
    MaxPoint = 300;
    InputFileName = 'input.txt';
    OutputFileName = 'output.txt';

  type
    ResistType = record
                   Value  : real;
                   Cp     : array[1..2] of Integer;
                 end;
     ArrayType = array[1..MaxPoint] of real;

  var
     R, Xr    : array[1..MaxResist] of ResistType;
     Res      : array[1..MaxPoint]of ^ArrayType;
     Pos      : array[1..MaxPoint] of real;
     Rs, Rss, Ps, Hp, Lp    : Integer;
     V                      : real;

  procedure Initialize;
    type
      RList = Set of Byte;

    var
       F        :       Text;
       Spot     :       RList;
       i, j, k  :       Integer;
       PList    :       array[1..MaxPoint] of RList;

    procedure ReadSpot(var Spot : RList);
      var
         x      :       Integer;
    begin
      Read(F, x);
      while x <> 0 do
        begin
          Include(Spot, x);
          Read(F, x);
        end;
    end;

    function GetPosition(Spot : RList) : Integer;
      var
         i      :       Integer;
    begin
      for i := 1 to Ps do
        if PList[i] = Spot then
           begin
             GetPosition := i;
             Exit;
           end;
      Inc(Ps);
      PList[Ps] := Spot;
      GetPosition := Ps;
    end;

  begin
    Assign(F, InputFileName);
    Reset(F);
    ReadLn(F, Rs);
    Ps := 0;
    for i := 1 to Rs do
      begin
        Read(F, R[i].Value);
        for j := 1 to 2 do
          begin
            Spot := [i];
            ReadSpot(Spot);
            R[i].Cp[j] := GetPosition(Spot);
          end;
        ReadLn(F);
      end;
    Read(F, V);
    Spot := []; ReadSpot(Spot); Hp := GetPosition(Spot);
    Spot := []; ReadSpot(Spot); Lp := GetPosition(Spot);

    if Ps = 1 then
       begin
         for i := 1 to Rs do R[i].Cp[2] := 2;
         Hp := 1;  Lp := 2; Ps := 2;
       end;
    Rss := Rs; Xr := R;

    for i := 1 to Ps do
      begin
        New(Res[i]);
        FillChar(Res[i]^, SizeOf(Res[i]^), 0);
      end;
  end;

  procedure MainAction;
    var
      PList : array[0..MaxPoint] of Integer;
      Rel   : array[1..MaxPoint, 1..2] of Integer;
      Deter, Can : array[1..MaxPoint] of Boolean;
      i, j, X, Y     : Integer;
      Found       : Boolean;


  begin
    FillChar(Deter, SizeOf(Deter), False);
    FillChar(Rel, SizeOf(Rel), 0);
    while Rs <> 0 do
      begin
        for i := 1 to Rs do
          with R[i] do
            begin
              X := Cp[1]; Y := Cp[2];
              if Res[X]^[Y] = 0
                 then Res[X]^[Y] := Value
                 else Res[X]^[Y] := Res[X]^[Y] * Value / (Res[X]^[Y] + Value);
              Res[Y]^[X] := Res[X]^[Y];
            end;

        Rs := 0;
        FillChar(Can, SizeOf(Can), True);
        Can[Hp] := False; Can[Lp] := False;
        for i := 1 to Ps do
          if not Deter[i] and Can[i] then
             begin
               PList[0] := 0;
               for j := 1 to Ps do
                 if (Res[i]^[j] <> 0) and not Deter[j] then
                    begin
                      Inc(PList[0]);
                      PList[PList[0]] := j;
                    end;

               if PList[0] <> 2 then Continue;

               X := PList[1]; Y := PList[2];

               Inc(Rs);
               R[Rs].Value := Res[X]^[i] + Res[Y]^[i];
               R[Rs].Cp[1] := X; R[Rs].Cp[2] := Y;
               Can[X] := False; Can[Y] := False;

               Deter[i] := True;
               Rel[i, 1] := X;  Rel[i, 2] := Y;
             end;
      end;

    for i := 1 to Ps do
      if Rel[i, 1] = Rel[i, 2] then WriteLn(i);
    FillChar(Deter, SizeOf(Deter), False);
    Pos[Hp] := V; Pos[Lp] := 0;
    Deter[Hp] := True; Deter[Lp] := True;
    repeat
      Found := False;
      for i := 1 to Ps do
        if not Deter[i] and Deter[Rel[i, 1]] and Deter[Rel[i, 2]] then
           begin
             Deter[i] := True; Found := True;
             X := Rel[i, 1];   Y := Rel[i, 2];
             Pos[i] := Pos[Y] +
                       (Pos[X]-Pos[Y])*Res[Y]^[i]/(Res[X]^[i]+Res[Y]^[i]);
           end;
    until not Found;
  end;

  procedure OutputSolution;
    var
       F                :       Text;
       i                :       Integer;
       Ur, Ir           :       real;
       X, Y             :       Integer;
       Flow             :       array[1..MaxPoint] of Real;
  begin
    Assign(F, OutputFileName);
    Rewrite(F);

    FillChar(Flow, SizeOf(Flow), 0);
    for i := 1 to Rss do
      with Xr[i] do
        begin
          Ur := Abs(Pos[Cp[1]] - Pos[Cp[2]]);
          Ir := Ur / Value;
          Flow[Cp[1]] := Flow[Cp[1]] - Ir;
          Flow[Cp[2]] := Flow[Cp[2]] + Ir;
          WriteLn(F, Round(Ur * 100) / 100:0:2, ' ',
                     Round(Ir * 100) / 100:0:2);
        end;
{    for i := 1 to Ps do
      if Abs(Flow[i]) > 1e-7 then WriteLn(i, ' ', Flow[i]);}
    Close(F);
  end;

begin
  ClrScr;

  Initialize;

  MainAction;

  OutputSolution;
end.