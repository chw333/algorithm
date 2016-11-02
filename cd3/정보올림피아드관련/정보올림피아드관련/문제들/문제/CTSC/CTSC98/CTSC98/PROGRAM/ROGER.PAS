{Roger Game of China IOI 98 Team Selective Contest}
{            by Ni Zhaozhong from SERKOI           }

const

  MaxM = 40;
  MaxN = 40;

  drFront = 1;
  drRight = 2;
  drBack = 3;
  drLeft = 4;

  Dx : array[1..4] of shortint = (0, 1, 0, -1);
  Dy : array[1..4] of shortint = (1, 0, -1, 0);

  pnTop = 1;
  pnBottom = 2;
  pnFront = 3;
  pnBack = 4;
  pnLeft = 5;
  pnRight = 6;

type

  TRoger = array[1..6] of byte;

  TSet = set of 0..6;

  TState = record
    Arrive : boolean;
    Changed : boolean;
    Cost : longint;
  end;

  TGrid = array[1..720] of TState;
  PGrid = ^TGrid;

  TGrids = array[1..MaxM, 1..MaxN] of PGrid;

  TPanel = array[1..MaxM, 1..MaxN] of integer;

  TIndex = array[1..6, 1..6, 1..6, 1..6, 1..6] of word;

{$I Roger.INC}

var
  Z : TIndex; {The Index List of Every Roger State}
  P : TPanel; {The Game Panel}
  G : TGrids; {The Grids on Panel}
  TaskID, { Task ID}
  M, N, {Width and Length of Panel}
  SM, SN, {Start Position}
  DM, DN : byte; {Dest Position}
  SR, {Start Roger}
  DR : TRoger; {Dest Roger}

function Index(R : TRoger) : word;
  begin
    Index := Z[R[1], R[2], R[3], R[4], R[5]];
  end;

procedure Init;
  var
    I, J : word;
  begin
    for I := 1 to 720 do
      Z[S[I, 1], S[I, 2], S[I, 3], S[I, 4], S[I, 5]] := I;

    assign(input, 'input.txt'); reset(input);

    readln(TaskID);
    readln(M, N);

    for J := 1 to N do begin
      for I := 1 to M do
        read(P[I, J]);
      readln;
    end;

    readln(SM, SN, SR[1], SR[2], SR[3], SR[4], SR[5], SR[6]);
    readln(DM, DN, DR[1], DR[2], DR[3], DR[4], DR[5], DR[6]);

    close(input);

    for I := 1 to M do
      for J := 1 to N do begin
        new(G[I, J]);
        fillchar(G[I, J]^, sizeof(G[I, J]^), 0);
      end;
  end;

procedure SetStart;
  var
    S : TSet;
    R : TRoger;
    I : byte;

  procedure Expand(P : byte; S : TSet);
    var
      I : byte;
    begin
      if P > 6 then begin
        G[SM, SN]^[Index(R)].Arrive := true;
        G[SM, SN]^[Index(R)].Changed := true;

        exit;
      end;

      if SR[P] > 0 then
        Expand(P + 1, S)
      else
        for I := 1 to 6 do
          if I in S then begin
            R[P] := I;
            Expand(P + 1, S - [I]);
          end;
    end;

  begin
    S := [1..6];
    for I := 1 to 6 do
      exclude(S, SR[I]);
    R := SR;

    Expand(1, S);
  end;

procedure Print(X, Y : byte; State : word);
  var
    D, I, J : byte;
  begin
    G[X, Y]^[State].Arrive := false;
    if not (X = SM) or not (Y = SN) or not (G[X, Y]^[State].Cost = 0) then
      for D := 1 to 4 do begin
        I := X - Dx[D];
        J := Y - Dy[D];
        if (I >= 1) and (I <= M) and (J >= 1) and (J <= N) and G[I, J]^[C[State, (D + 1) mod 4 + 1]].Arrive and
          (G[I, J]^[C[State, (D + 1) mod 4 + 1]].Cost + S[State][1] * P[X, Y] = G[X, Y]^[State].Cost)
        then begin
          Print(I, J, C[State, (D + 1) mod 4 + 1]);
          break;
        end;
      end;
    writeln(G[X, Y]^[State].Cost, ' ', X, ' ', Y, ' ', S[State, 1], ' ', S[State, 2], ' ', S[State, 3], ' ',
            S[State, 4], ' ', S[State, 5], ' ', S[State, 6]);
  end;

procedure ReportDest;
  var
    Flag : boolean;
    NowCost : longint;
    State : word;
    S : TSet;
    R : TRoger;
    I : byte;

  procedure Expand(P : byte; S : TSet);
    var
      I : byte;
    begin
      if P > 6 then begin
        if G[DM, DN]^[Index(R)].Arrive then begin
          Flag := true;

          if G[DM, DN]^[Index(R)].Cost < NowCost then begin
            NowCost := G[DM, DN]^[Index(R)].Cost;
            State := Index(R);
          end;
        end;

        exit;
      end;

      if DR[P] > 0 then
        Expand(P + 1, S)
      else
        for I := 1 to 6 do
          if I in S then begin
            R[P] := I;
            Expand(P + 1, S - [I]);
          end;
    end;

  begin
    S := [1..6];
    for I := 1 to 6 do
      exclude(S, DR[I]);
    R := DR;
    Flag := false;
    NowCost := 1000000000;

    Expand(1, S);

    assign(output, 'output.txt'); rewrite(output);
    if Flag then begin
      writeln(NowCost);
      Print(DM, DN, State);
    end else
      writeln(-1);
    close(output);
  end;

procedure TaskOne;
  var
    I, J, D, X, Y : byte;
    K : word;
    NewCost : longint;
  begin
    for I := SM to DM do
      for J := SN to DN do
        for K := 1 to 720 do
          if G[I, J]^[K].Arrive then
            for D := 1 to 2 do begin
              X := I + Dx[D];
              Y := J + Dy[D];

              if (X <= DM) and (Y <= DN) and (P[X, Y] > -1) then begin
                NewCost := G[I, J]^[K].Cost + S[C[K, D], pnTop] * P[X, Y];

                if not G[X, Y]^[C[K, D]].Arrive or (NewCost < G[X, Y]^[C[K, D]].Cost) then
                  with G[X, Y]^[C[K, D]] do begin
                    Arrive := true;
                    Cost := NewCost;
                  end;
              end;
            end;
  end;

procedure TaskTwo;
  var
    I, J, D, X, Y : byte;
    K : word;
    NewCost : longint;
    NoChange : boolean;
  begin
    repeat
      NoChange := true;

      for I := 1 to M do
        for J := 1 to N do
          for K := 1 to 720 do
            if G[I, J]^[K].Changed and G[I, J]^[K].Arrive then begin
              G[I, J]^[K].Changed := false;

              for D := 1 to 4 do begin
                X := I + Dx[D];
                Y := J + Dy[D];

                if (X >= 1) and (Y >= 1) and (X <= M) and (Y <= N) and (P[X, Y] > -1) then begin
                  NewCost := G[I, J]^[K].Cost + S[C[K, D], pnTop] * P[X, Y];

                  if not G[X, Y]^[C[K, D]].Arrive or (NewCost < G[X, Y]^[C[K, D]].Cost) then
                    with G[X, Y]^[C[K, D]] do begin
                      Arrive := true;
                      Cost := NewCost;
                      Changed := true;
                      NoChange := false;
                    end;
                end;
              end;
            end;
    until NoChange;
  end;

begin
  Init;
  if (P[SM, SN] > -1) and (P[DM, DN] > -1) then begin
    SetStart;
    case TaskID of
      1 :
        TaskOne;
      2 :
        TaskTwo;
    end;
  end;
  ReportDest;
end.