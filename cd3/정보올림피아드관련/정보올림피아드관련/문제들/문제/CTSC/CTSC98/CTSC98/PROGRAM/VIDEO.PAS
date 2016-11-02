{$A+,B-,D-,E-,F-,G+,I+,L+,N+,O-,P-,Q+,R-,S-,T-,V-,X+,Y+}
{$M 65520,0,655360}
program View_Area;

  uses Crt, graph;

  const
    InputFileName = 'INPUT.TXT';
    OutputFileName = 'OUTPUT.TXT';
    MaxPoint       = 101;
    Sz             = 4;

  type
    PointType = record
                  X, Y : Real;
                end;

    VectorType = record
                 A, B, C : Real;
               end;

  var
    N,                         { Number of Points }
    Room,                      { Number of Room }
    Kps             : Integer; { Number of Key Points }
    Point,                     { Orinigal Points }
    Kp,                        { Key Points }
    Ap                         { Resorted Points }
        : array[1..MaxPoint] of PointType;
    Vec                       { Side Vector }
      : array[1..MaxPoint] of VectorType;
    InF, OutF : Text;

  procedure GenerateVector(P1, P2 : PointType; var Vec : VectorType);
  begin
    { Ax - By = C  B + Ai }
    with Vec do
      begin
        A := P2.Y - P1.Y; { A = dy }
        B := P2.X - P1.X; { B = dx }
        C := A * P1.X - B * P1.Y;
      end;
  end;

  function DataRemain : Boolean;
    var
       i        :       Integer;
  begin
    { Read Data }
    ReadLn(InF, N);
    if N = 0 then
       DataRemain := False
    else
      begin
        DataRemain := True;
        for i := N downto 1 do
          ReadLn(InF, Point[i].X, Point[i].Y);
      end;
  end;

  procedure Initialize;
      var
         i      :       Integer;
    begin
      Point[N + 1] := Point[1];
      for i := 1 to N do
        GenerateVector(Point[i], Point[i + 1], Vec[i]);
    end;

  procedure GetKeyPoint;
    var
       A1, B1, C1, A2, B2, C2, M, X0, Y0, Dx, Dy : Real;
       i, j, k : Integer;
       Ok      : Boolean;
  begin
    Kps := 0;
    for i := 1 to N do
      for j := i + 1 to N do
        begin
          A1 := Vec[i].A; B1 := - Vec[i].B; C1 := Vec[i].C;
          A2 := Vec[j].A; B2 := - Vec[j].B; C2 := Vec[j].C;

          M := A1 * B2 - A2 * B1;
          if M <> 0 then
             begin
               X0 := (C1 * B2 - C2 * B1) / M;
               Y0 := (A1 * C2 - A2 * C1) / M;
               Ok := True;
               for k := 1 to N do
                 begin
                   Dx := X0 - Point[k].X;
                   Dy := Y0 - Point[k].Y;
                   if Dy * Vec[k].B - Dx * Vec[k].A < 0 then
                      begin
                        Ok := False;
                        Break;
                      end;
                 end;
             end
          else Ok := False;

          if Ok then
             begin
               Inc(Kps);
               Kp[Kps].X := X0;
               Kp[Kps].Y := Y0;
             end;
        end;
  end;

  procedure OutputSolution;
    var
       Gd, Gm, i, j   :       Integer;
  begin
    if Room <> 1 then WriteLn(OutF);

    WriteLn(OutF, 'Room #', Room, ':');

    if Kps = 0
       then WriteLn(OutF, 'Surveillance is impossible.')
       else WriteLn(OutF, 'Surveillance is possible.');

    {Gd := Detect;
    InitGraph(Gd, Gm, 'E:\zp');
    FloodFill(1, 1, 1);
    SetColor(Black);
    for i := 1 to N do
      Line(300 + Round(Point[i  ].X) * Sz, GetMaxY DIV 2 - Round(Point[i].Y * Sz),
           300 + Round(Point[i+1].X) * Sz, GetMaxY DIV 2- Round(Point[i+1].Y) * Sz);

    SetColor(Black);
    SetFillStyle(1, Black);
    SetLineStyle(0, 1, 3);
    for i := 1 to Kps do
      begin
        PieSlice(300 + Round(Kp[i].X) * Sz, GetMaxY DIV 2- Round(Kp[i].Y) * Sz,
                 0, 360, 3);
        for j := i + 1 to Kps do
          Line(300 + Round(Kp[i].X) * Sz, GetMaxY DIV 2 - Round(Kp[i].Y) * Sz,
               300 + Round(Kp[j].X) * Sz, GetMaxY DIV 2 - Round(Kp[j].Y) * Sz);
      end;

    if ReadKey = #13 then halt;}
  end;

begin
  Assign(InF, InputFileName);
  Reset(InF);
  Assign(OutF, OutputFileName);
  Rewrite(OutF);
  Room := 0;

  while DataRemain do
    begin
      Inc(Room);
      Initialize;
      GetKeyPoint;
      OutputSolution;
    end;

  Close(InF);
  Close(OutF);
end.