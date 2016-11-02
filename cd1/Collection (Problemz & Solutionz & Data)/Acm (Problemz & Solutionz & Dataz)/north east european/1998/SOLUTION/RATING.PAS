{ NEERC'98 Problem "Rating"
  Solution by Roman Elizarov
  19.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program RATING_SOLUTION;

const
  maxn = 100;
  maxid = 100;

type
  TRating = record
              n: integer;
              id, place, place_by_id: array[1..maxid+1] of integer;
            end;

procedure ReadRating ( var r: TRating );
var
  n, i, u, p: integer;
begin
  readln ( n );
  r.n:= 0;
  fillchar ( r.place_by_id, sizeof(r.place_by_id), 0 );
  for i:= 1 to n do begin
    p:= r.n + 1;
    while not seekeoln do begin
      read ( u );
      inc ( r.n );
      r.id[r.n]:= u;
      r.place[r.n]:= p;
      r.place_by_id[u]:= p;
    end;
    readln;
  end;
 { put guard at the back }
  r.place[r.n+1]:= maxint;
end;

var
  r1, r2: TRating;

function Twice ( id: integer ): boolean;
begin
  Twice:= (r1.place_by_id[id] <> 0) and (r2.place_by_id[id] <> 0);
end;

var
  b_places: integer;
  b_pos, rating, rating2: array[1..maxid] of integer;

procedure CalcRatings ( const r: TRating );
var
  i, j, id, place, this_r: integer;
  good: boolean;
begin
  for i:= 1 to r.n do
    if not Twice(r.id[i]) then begin
      id:= r.id[i];
      place:= r.place[i];
      rating2[id]:= place;
      j:= place;
      this_r:= -1;
      good:= true;
      while r.place[j] = place do begin
        if Twice(r.id[j]) then begin
          if (this_r >= 0) and (rating[r.id[j]] <> this_r) then
            good:= false
          else
            this_r:= rating[r.id[j]];
        end;
        inc(j);
      end;
      if this_r >= 0 then begin { rule A works }
        if good then
          rating[id]:= this_r;
      end else begin { check for rule B }
        this_r:= -1;
        for j:= 1 to place-1 do
          if Twice(r.id[j]) and (rating[r.id[j]] > this_r) then
            this_r:= rating[r.id[j]];
        inc ( this_r );
        good:= true;
        for j:= place to r.n do
          if (r.place[j] > place) and Twice(r.id[j]) and (rating[r.id[j]] < this_r) then
            good:= false;
        if good then
          rating[id]:= this_r;
      end;
    end;
end;

type
  info = record i, r, r2: integer end;

var
  b: array[1..maxid] of info;
  t: info;
  i, j, bc, prev: integer;

begin
  assign ( input, 'rating.in' ); reset ( input );
  assign ( output, 'rating.out' ); rewrite ( output );

 { Read input }
  readRating ( r1 );
  readRating ( r2 );

 { List the teams that participated twice }
  bc:= 0;
  for i:= 1 to maxid do
    if Twice(i) then begin
      inc ( bc );
      b[bc].i:= i;
      b[bc].r:= r1.place_by_id[i] + r2.place_by_id[i];
    end;

 { Sort the teams that participated twice }
  for i:= 1 to bc-1 do
    for j:= i+1 to bc do
      if b[i].r > b[j].r then begin
        t:= b[i];
        b[i]:= b[j];
        b[j]:= t;
      end;

 { Assign "ratings" for the teams that participated twice }
  prev:= 0;
  b_places:= 0;
  fillchar ( rating, sizeof(rating), $FF );
  fillchar ( rating2, sizeof(rating2), $FF );

 { overall rating   0     begining of list
                   2*i-1  i-th twice-place
                   2*i    after i-th twice-place (additional rating
		          located in "rating2") }

  for i:= 1 to bc do begin
    if b[i].r <> prev then begin
      inc ( b_places );
      b_pos[b_places]:= i;
    end;
    rating[b[i].i]:= 2*b_places-1;
    prev:= b[i].r;
  end;

 { Calculate "rating" for teams that participated only once }
  CalcRatings ( r1 );
  CalcRatings ( r2 );

 { Now create the final list }
  bc:= 0;
  for i:= 1 to maxid do
    if rating[i] >= 0 then begin
      inc ( bc );
      b[bc].i:= i;
      b[bc].r:= rating[i];
      b[bc].r2:= rating2[i];
    end;

 { Sort it }
  for i:= 1 to bc-1 do
    for j:= i+1 to bc do
      if (b[i].r > b[j].r) or ((b[i].r = b[j].r) and (b[i].r2 > b[j].r2)) then begin
        t:= b[i];
        b[i]:= b[j];
        b[j]:= t;
      end;

 { Write it to the output };
  t:= b[1];
  for i:= 1 to bc do begin
    if (b[i].r > t.r) or ((b[i].r mod 2 = 0) and (b[i].r2 > t.r2)) then
      writeln;
    write ( b[i].i, ' ' );
    t:= b[i];
  end;
end.