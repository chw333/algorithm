{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 65520,0,655360}

Program mazeWithDoors; { 3.3, BOI'97 }
{ written by Tomas Laurinavicius    }
{ requires Borland/Turbo Pascal 7.0 }

  const InFileName  = 'maze.dat';
        OutFileName = 'maze.rez';
        NoWayMsg    = 'NOWAY';
        MaxDim      = 50;       { maximum dimension of the maze             }
        MaxDoor     = 20;       { maximum number of doors                   }
        OpenTime    = 20;       { the doors stay open for this no. of moves }
        infinity    = 100000;   { this is quite a lot for me :)             }
        MaxVert     = MaxDoor*2 + 1; { number of graph vertexes             }
        edge        = MaxVert;
  var maze               : array [1..MaxDim, 1..MaxDim] of integer;
      g                  : array [0..MaxVert, 0..MaxVert] of longint;
      drs, swt           : array [1..MaxDoor] of record
                                                   x, y : integer
                                                 end;
      t : text;
      m, n, man_x, man_y : integer;

  function ire (a, rlo, rhi, e : integer) : boolean;
  { "true" if (rlo <= a <= rhi)  or (a = e) }
  begin
    ire := ((a >= rlo) and (a <= rhi)) or (a = e);
  end;

  procedure start;  { loads data }
    var i, j : integer;
  begin
    FillChar (drs, SizeOf (drs), 0);
    FillChar (swt, SizeOf (swt), 0);
    assign (t, InFileName);
    reset (t);
    ReadLn (t, man_x, man_y);
    ReadLn (t, m, n);
    for j := 1 to n do
      begin
        for i := 1 to m do
          begin
            read (t, maze[j, i]);
            if ire (maze[j, i], 1, MaxDoor, 1)
               then with drs[maze[j, i]] do
                      begin
                        x := i;  y := j;
                      end;
            if maze[j, i] > MaxDoor
              then begin
                     dec (maze[j, i], 100 - MaxDoor);
                     with swt[maze[j, i] - MaxDoor] do
                          begin
                            x := i;  y := j;
                          end;
                   end;
          end;
        ReadLn (t);
      end;
    close (t);
  end;

  procedure FindRooms;
  { finds useless doors and removes them }
    var d            : array [1..MaxDim, 1..MaxDim] of integer;
        rCount, i, j : word;
        rooms : array [1..500] of record
                                    man, edge, useless : boolean;
                                    drCount : byte; { no. of doors }
                                    dr,                    { doors }
                                    sw : set of 1..MaxDoor;
                                            { if any switch inside }
                                  end;
        drem         : set of 1..MaxDoor;        { doors to remove }
        ch           : boolean;
        u, md, mv    : integer;

    procedure fill (j, i : integer);
    begin
      if (j > n) or (j < 1) or (i > m) or (i < 1)
         then begin
                rooms [rCount].edge := true;
                exit;
              end;
      if (maze[j, i] <= MaxDoor) and (maze[j, i] <> 0)
         then begin
                if (maze[j, i] <> -1) and not (maze[j, i] in rooms[rCount].dr)
                   then begin
                          inc (rooms[rCount].drCount);
                          include (rooms[rCount].dr, maze[j, i]);
                        end;
                exit;
              end;
      if (d[j, i] <> 0)
         then exit;
      d[j,i] := rCount;
      if (j = man_y) and (i = man_x)
         then rooms[rCount].man := true;
      if maze[j, i] > MaxDoor
         then include (rooms[rCount].sw, maze[j, i] - MaxDoor);
      fill (j - 1, i);  fill (j + 1, i);
      fill (j, i - 1);  fill(j, i + 1);
    end;

  begin
    rCount := 0;
    FillChar (d, SizeOf(d), 0);
    FillChar (rooms, SizeOf (rooms), 0);
    for j := 1 to n do
      for i := 1 to m do
         if (d[j,i] = 0) and ((maze[j, i] = 0) or (maze[j, i] > MaxDoor))
            then begin
                   inc (rCount);
                   fill (j, i);
                 end;
    repeat
      for i := 1 to rCount do
          with rooms[i] do
               useless := not man and not edge and (sw = [])
                          and (drCount < 2);
      drem := [];  ch := false;
      md := MaxDoor;   mv := MaxVert;
      for i := 1 to MaxDoor do
          if (drs[i].x in [2..m-1]) and (drs[i].y in [2..n-1])
             then begin
                    u := 0;
                    with drs[i] do
                      begin
                        if ire (maze[y - 1, x], md + 1, mv - 1, 0) and
                           not rooms[d[y - 1, x]].useless
                           then inc (u);
                        if ire (maze[y - 1, x], 1, md, 1)
                           then u := 10;
                        if ire (maze[y + 1, x], md + 1, mv - 1, 0) and
                           not rooms[d[y + 1, x]].useless
                           then inc(u);
                        if ire (maze[y + 1, x], 1, md, 1)
                           then u := 10;
                        if ire (maze[y, x - 1], md + 1, mv - 1, 0) and
                           not rooms[d[y, x - 1]].useless
                           then inc (u);
                        if ire (maze[y, x - 1], 1, md, 1)
                           then u := 10;
                        if ire (maze[y, x + 1], md + 1, mv - 1, 0) and
                           not rooms[d[y, x + 1]].useless
                           then inc (u);
                        if ire (maze[y, x + 1], 1, md, 1)
                           then u := 10;
                        if u < 2
                          then begin
                                 include (drem, i);
                                 ch := true
                                end;
                      end;
                  end;
      for i := 1 to MaxDoor do
          if i in drem
             then begin
                    maze[drs[i].y, drs[i].x] := -1;
                    maze[swt[i].y, swt[i].x] := 0;
                    exclude (rooms[d[swt[i].y, swt[i].x]].sw, i);
                    drs[i].x := 0;   swt[i].x := 0;
                  end;
    until not ch;
  end;

  procedure FillGraph;
    var i, j : longint;

    procedure FillRoom (y, x : longint);
      var i, j, cw, clw, lev : longint;
          wave, LastWave     : array [1..1000] of record
                                                    wx, wy : byte
                                                  end;
          d                  : array [1..MaxDim, 1..MaxDim ] of integer;
          changed            : boolean;

      procedure mark (my, mx : longint);
      begin
        if (my > 0) and (my <= n) and (mx > 0) and (mx <= m)
           then begin
                  if (d[my,mx] <> -1) or (maze[my,mx] = -1)
                     then exit;
                  if not ire (maze[my, mx], 1, MaxDoor, 1)
                     then begin
                            changed := true;
                            d[my,mx] := lev;
                            inc (cw);
                            wave[cw].wx := mx;
                            wave[cw].wy := my;
                          end;
                  if (maze[my, mx] > 0) and
                     (g[maze[y, x], maze[my, mx]] > lev)
                     then g[maze[y, x], maze[my, mx]] := lev;
                end
           else if (g[maze[y, x], edge] > lev)
                   then g[maze[y, x], edge] := lev;
      end;

    begin
      clw := 0;  cw := 0;
      wave[1].wx := x;  wave[1].wy := y;
      lev := 0;
      for j := 1 to MaxDim do
        for i := 1 to MaxDim do
          d[j, i] := -1;
      mark (y, x);
      if maze[y, x] > 0
         then cw := 1;
      repeat
        inc (lev);
        changed := false;
        LastWave := wave;
        clw := cw;  cw := 0;
        for i := 1 to clw do
            with LastWave[i] do
              begin
                mark (wy - 1, wx);  mark (wy + 1, wx);
                mark (wy, wx - 1);  mark (wy, wx + 1);
              end;
      until not changed;
    end;

  begin
    for j := 0 to MaxVert do
      for i := 0 to MaxVert do
        g[j, i] := infinity;
    FillRoom (man_y, man_x);
    for j := 1 to n do
      for i := 1 to m do
        if maze[j, i] > 0
           then FillRoom (j, i);
    for i := 0 to MaxVert do
      g[i, i] := infinity;
  end;
{---------------------------------------------------------------------------}
  type PSituation = ^TSituation;
       TSituation = record
                      { counters for all doors; 0 means closed }
                      d    : array[1..MaxDoor] of byte;
                      dist : longint;    { already walked distance }
                      next : PSituation;
                    end;
       TWave      = array [0..MaxVert] of boolean;

  var { all situations found for each graph vertex }
      sit     : array [0..MaxVert] of PSituation;
      { doors already passed, and doors to be passed}
      dp, dtp : array [1..MaxDoor] of boolean;

  procedure AddSit (num : word; var s : TSituation);
  { adds situation "s" to the vertex "num" }
    var ptr : PSituation;
  begin
    if sit[num] = nil
       then begin
              new (sit[num]);
              sit[num]^ := s;
              sit[num]^.next := nil;
            end
       else begin
              ptr := sit[num];
              while ptr^.next <> nil do
                ptr := ptr^.next;
              new (ptr^.next);
              ptr^.next^ := s;
              ptr^.next^.next := nil;
            end;
  end;

  function FindPath: longint;
  { searches for the shortest way out }
    var i, j     : word;
        lw, nw   : TWave;     { last wave, new wave }
        updated  : boolean;   { if any new situations for any vertex found }
        MinFound : longint;   { shortest path so far }
        cur      : TSituation;

    procedure TryToAdd;
    { tries to add new (somewhat better) situations to vertex "j" by }
    { using all the situations available in vertex "i".              }
      var k, l, d, wd, a, b      : word;
          iptr, jptr             : PSituation;
          sbetter, better, worse : boolean;
      label EndTest;
    begin
      d := g[i,j];
      iptr := sit[i];
      while iptr <> nil do
        begin
          for k := 1 to MaxDoor do
              if iptr^.d[k] > d
                 then cur.d[k] := iptr^.d[k] - d
                 else cur.d[k] := 0;
          if (j > MaxDoor) and (j < MaxVert)
             then cur.d[j - MaxDoor] := OpenTime
             else if (j <= MaxDoor) and (cur.d[j] = 0)
                     then begin
                            iptr := iptr^.next;
                            continue;
                          end;
          cur.dist := iptr^.dist + d;
          if cur.dist < MinFound
             then if j = MaxVert
                     then MinFound := cur.dist
                     else
                       begin
                         jptr := sit[j];
                         sbetter := false;
                         while jptr <> nil do
                           begin      { compare situations jptr^ and cur }
                             better := true;
                             worse := true;
                             for k := 1 to MaxDoor do
                                 if (k <> j + MaxDoor)
                                    then begin
                                           a := jptr^.d[k];
                                           b := cur.d[k];
                                           if (a > b) or ((a = 0) and (b > 0))
                                              then
                                                begin
                                                  better := false;
                                                  if not worse
                                                     then goto EndTest;
                                                end;
                                           if (b > a) or ((b = 0) and (a > 0))
                                              then
                                                begin
                                                  worse := false;
                                                  if not better
                                                     then goto EndTest;
                                                end;
                                         end;
                             if better and (jptr^.dist <= cur.dist)
                                then begin
                                       sbetter := true;
                                       break
                                     end;
                             if worse and (cur.dist <= jptr^.dist)
                                then begin
                                       cur.next := jptr^.next;
                                       jptr^ := cur;
                                       sbetter := true;
                                       updated := true;
                                       break;
                                     end;
    EndTest :                jptr := jptr^.next;
                           end;
                         if not sbetter
                            then begin
                                   updated := true;
                                   AddSit (j, cur);
                                 end;
                       end;
          iptr := iptr^.next;
        end;
    end;

    function AllDoors: boolean;
    { shecks, if all the available doors have been passed already }
      var i : word;
    begin
      AllDoors := false;
      for i := 1 to MaxDoor do
        if (drs[i].x > 0) and not dp[i]
            then exit;
      AllDoors := true;
    end;

  begin
    MinFound := infinity;
    FillChar (dp, SizeOf (dp), 0);
    FillChar (dtp, SizeOf (dtp), 0);
    for i := 0 to MaxVert do
        sit[i] := nil;
    FillChar (lw, SizeOf (lw), 0);
    lw[0] := true;
    FillChar (cur, SizeOf (cur), 0);
    AddSit (0, cur);
    while not AllDoors do
      begin
        for i := 1 to MaxDoor do
            if dtp[i]
               then dp[i] := true;
        for i := 1 to MaxVert do
            if sit[i] <> nil
               then lw[i] := true;
        repeat
          updated := false;
          { for ALL vertexes from lw using ALL their situations go to ALL   }
          { their neighbour vertexes and try to add a new situation. If     }
          { vertex is a switch or a door from dp, add it to nw.             }
          FillChar (nw, SizeOf(nw), 0);
          for i := 0 to MaxVert - 1 do        { never go back from the edge }
              if lw[i]
                 then begin
                        for j := 1 to MaxVert do
                            if g[i,j] < infinity
                               then begin  { ...to all neighbouring }
                                      if j > MaxDoor
                                         then nw[j] := true
                                         else if dp[j]
                                                 then nw[j] := true
                                                 else dtp[j] := true;
                                      TryToAdd;
                                    end;
                      end;
          lw := nw;
        until not updated;
      end;
    FindPath := MinFound;
  end;

  procedure done (res: longint);                    { write result to file }
  begin
    assign (t, OutFileName);
    ReWrite (t);
    if res = infinity
       then WriteLn (t, NoWayMsg)
       else WriteLn (t, Res);
    Close(t);
  end;

begin
  start;
  FindRooms;
  FillGraph;
  done (FindPath);
end.