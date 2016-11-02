program journey;  { 2.5, BOI'96 }
  const NB   = 100;                               { maximal number of cities }
  type list  = ^elem;
       elem  = record
                 c, h : integer;
                 next : list
               end;
       graph = array [1..NB] of list;    { graph that describes the traffic }
       pred = array  [1..NB] of integer; { each element of such array is
              either another vertex or nil; the elements are such that the
              chain of predecessors originating at vertex b runs backwards
              along shortest path from the city a(source) to b(destination) }
  { below is the list of global variables }
  var a, b,                             { the source and destination cities }
       n,                                      { the total number of cities }
       r            : integer;                  { the total number of roads }
       source, dest : graph; { 2 graphs that describe incoming and outcoming
                               roads }
       prev         : pred;
       d            : array [1..NB] of integer; { shortest dist. from city A }

  procedure InitGr (var source, dest : graph );
  { initializes graphs }
    var  i : integer;
  begin
    for i := 1 to n do
      begin
        source[i] := nil;
        dest[i] := nil
      end
  end; { InitGr }

  procedure input;
    var f             : text;
        fv            : string;
        p             : list;
        c1, c2, hours : integer;
        i             : integer;
  begin
    write ('Input file name: ');
    readln (fv);
    assign (f, fv);
    reset (f);
    readln (f, a, b);
    readln (f, n, r);
    InitGr (source, dest);     { 2 graphs, one of them describing departure
                          cities, another - arrival cities, are initialized }
    for i := 1 to r do
      begin
        readln (f, c1, c2, hours);
        if hours <= 12
           then begin               { we will add a new road to both graphs }
                  new (p);
                  p^.c := c2;
                  p^.h := hours;
                  p^.next := dest [c1];
                  dest[c1] := p;
                  new (p);
                  p^.c := c1;
                  p^.h :=  hours;
                  p^.next := source [c2];
                  source [c2] := p;
                end
      end;
    close  (f)
  end;  { input }

  procedure Dijkstra (a : integer;  var prev : pred);
    var Q : set of 1..NB;               { a set of vertices to be analysed }
        w, v, u, i,  distance : integer;
        enter : boolean;      { is the edge leaving or entering the vertex }
        p : list;
  begin
    for i := 1 to n do
      begin
        d[i] := maxint;              { initial values of arrays d and prev }
        prev [i] := 0;
     end;
    d[a] := 0;              { the shortest distance from a to a is zero .. }
    Q := [1..n];
    while Q <> [] do      { while there exist vertices we haven't analysed }
      begin
        { we'll find a not analysed vertex u being in a min. distance from a }
        distance := maxint;
        for i := 1 to n do
          if (i in Q)
             then if (d[i] < distance)
                     then begin
                            u := i;
                            distance := d[i];
                          end;
        Q := Q - [u];                                { a vertex u is dequed }
       {   !!! All the edges ENTERING and leaving u will be relaxed due to
           the change of driving directions on the odd and even days; this
           ma kes the basic difference from an ordinary Dijkstra's algorithm }
       for enter := false to true do
         begin
           if enter
             then p := source[u]
             else p := dest[u];
             while p <> nil do   { while there exist vertices adjacent to u }
               begin
                 v := p^.c;
                 w := p^.h;
                 { below we will chech whether we can improve the shortest
                   path to v found so far by going through u }
                 { first we will count the new distance assuming that
                   we will go through u }
                 if not enter  and  odd (d[u] div 12 + 1) or
                    enter  and  not odd (d[u] div 12 + 1)
                    then if (d[u] mod 12 + w) div 12 > 0
                            then w := (12 - d[u] mod  12) + 12 + w
                            { we had to stop for one day until we could
                              continue the journey }
                            else { the value of w doesn't change }
                    else w := (12  - d[u] mod 12) + w;
                 { and then chech whether we can improve }
                 if d[v] > d[u] + w
                    then begin
                           d[v] := d[u] + w;
                           prev [v] := u
                         end;
                 p := p^.next
               end  { while p <> nil do }
         end  { for enter := false to true do }
      end  { while Q <> [] do }
  end;  { Dijkstra }

  procedure output (b : integer);
    { deals with files and contains a recursive printing procedure }
    var f          : text;
        day, hours : integer;
    procedure print ( c : integer);
      { prints to the file f the short. path from the city a to the city c }
      var  city : integer;
    begin
      if c <> a
         then begin
                city := prev [c];
                print ( city );
                day := d[c] div 12 + 1;
                if (d[c] div 12) = (d [city] div 12)
                    then hours := (d[c] - d[city]) mod 12
                    else hours :=  d[c] mod 12;
                if hours = 0 then begin
                                    hours := 12;
                                    day := day -  1;
                                 end;
                writeln (f, city, ' ',c, ' ', day, ' ',hours);
              end  { if c <> a }
    end;  { print }
  begin
    assign (f,  'OUTPUT.TXT');
    rewrite (f);
    print (b);
    close (f)
  end;
begin
  input;
  Dijkstra (a, prev);
  output (b)
end.
