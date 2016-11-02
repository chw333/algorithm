program Farmica;
type point = record
               x, y: longint;
             end;
     pointr = ^elem;
     elem = record
              ind: longint;
              next: pointr;
            end;
     niz = array[0..1001] of point;
     niz2 = array[0..1001] of pointr;
     niz3 = array[0..1001] of longint;
     niz4 = array[0..1001] of boolean;
var n, k, ti, i, brsus, result: longint;
    T: niz;
    lon: niz2;
    sus: niz3;
    f, g: text;

procedure load;
var i, j, id, d: longint;
    p: pointr;
begin
  readln(f, n);
  for i := 1 to n do
    begin
      read(f, T[i].x, T[i].y, d);
      lon[i] := nil;
      for j := 1 to d do
        begin
          read(f, id);
          new(p);
          p^.ind := id;
          p^.next := lon[i];
          lon[i] := p;
        end;
      readln(f);
    end;
  readln(f, k);
end;

procedure makesus(k: longint);
var i, id, pom: longint;
    p: pointr;
begin
  brsus := 0;
  p := lon[k];
  while (p <> nil) do
    begin
      id := p^.ind;
      if ((T[id].y > T[k].y) or ((T[id].y = T[k].y) and (T[id].x > T[k].x))) then
        begin
          brsus := brsus + 1;
          sus[brsus] := id;
          i := brsus;
          while ((i > 1) and
            ((T[sus[i]].x - T[k].x) * (T[sus[i-1]].y - T[k].y) > (T[sus[i-1]].x - T[k].x) * (T[sus[i]].y - T[k].y))) do
            begin
              pom := sus[i];
              sus[i] := sus[i - 1];
              sus[i - 1] := pom;
              i := i - 1;
            end;
        end;
      p := p^.next;
    end;
end;

procedure main;
var i, id, tek, pot, a1, a2, brp: longint;
    p: pointr;
    pass, one, st1, st2, st3: boolean;
    path: niz3;
    onpath: niz4;
begin
  result := 0;
  for i := 1 to n do
    onpath[i] := false;
  for i := 1 to n do
    begin
      makesus(i);
      path[1] := i;
      onpath[i] := true;
      if (brsus > 1) then
        for tek := 1 to brsus - 1 do
          begin
            brp := 2;
            path[2] := sus[tek];
            onpath[sus[tek]] := true;
            pass := true;
            while (pass) do
              begin
                one := false;
                p := lon[path[brp]];
                while (not(one) and (p <> nil)) do
                  begin
                    id := p^.ind;
                    if ((id <> path[brp-1]) and ((T[id].y > T[i].y) or ((T[id].y = T[i].y) and (T[id].x >= T[i].x)))) then
                      begin
                        pot := id;
                        one := true;
                      end;
                    p := p^.next;
                  end;
                if (one) then
                  begin
                    while (p <> nil) do
                      begin
                        id := p^.ind;
                        if ((id <> path[brp-1]) and ((T[id].y > T[i].y) or ((T[id].y = T[i].y) and (T[id].x >= T[i].x)))) then
                          begin
                            a1 := path[brp-1];
                            a2 := path[brp];
                            st1 := ((T[pot].x - T[a2].x) * (T[id].y - T[a2].y) > (T[id].x - T[a2].x) * (T[pot].y - T[a2].y));
                            st2 := ((T[id].x - T[a2].x) * (T[a1].y - T[a2].y) > (T[a1].x - T[a2].x) * (T[id].y - T[a2].y));
                            st3 := ((T[a1].x - T[a2].x) * (T[pot].y - T[a2].y) > (T[pot].x - T[a2].x) * (T[a1].y - T[a2].y));
                            if (st3) then
                              begin
                                if ((st1) or (st2)) then
                                  pot := id;
                              end
                            else
                              if ((st1) and (st2)) then
                                pot := id;
                          end;
                        p := p^.next;
                      end;
                    if  (path[brp] = sus[tek + 1]) then
                      begin
                        if (pot = i) then
                          if (brp = k) then
                            result := result + 1;
                        pass := false;
                      end
                    else if (onpath[pot]) then pass := false
                         else
                           begin
                             brp := brp + 1;
                             path[brp] := pot;
                             onpath[pot] := true;
                           end;
                  end
                else pass := false;
              end;
            while (brp > 1) do
              begin
                onpath[path[brp]] := false;
                brp := brp - 1;
              end;
          end;
      onpath[i] := false;
    end;
end;

procedure finalize;
var i: longint;
    p: pointr;
begin
  writeln(g, result);
  for i := 1 to n do
    while (lon[i] <> nil) do
      begin
        p := lon[i];
        lon[i] := lon[i]^.next;
        dispose(p);
      end;
end;

begin
  assign(f, 'zad6.dat');
  assign(g, 'zad6.res');
  reset(f);
  rewrite(g);
  load;
  main;
  finalize;
  close(f);
  close(g);
end.
