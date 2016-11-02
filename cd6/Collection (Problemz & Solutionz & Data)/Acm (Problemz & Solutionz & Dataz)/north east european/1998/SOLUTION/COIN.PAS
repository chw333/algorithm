{ NEERC'98 Problem "False coin"
  Solution by Roman Elizarov
  19.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program COIN_SOLUTION;

const
  maxn = 100;

var
  n, k, i, j, p, u, cnt, idx: integer;
  less, more, l, r, all: set of 1..maxn;
  c: char;

begin
  assign ( input, 'coin.in' ); reset ( input );
  assign ( output, 'coin.out' ); rewrite ( output );

 { Gathering information }
  read ( n, k );
  less:= [1..n]; { Possible false coins with lower weight   }
  more:= [1..n]; { Possible false coins with greater weight }
  for i:= 1 to k do begin
    read ( p );
    l:= []; { Coins in left pan  }
    r:= []; { Coins in right pan }
    for j:= 1 to p do begin
      read ( u );
      include ( l, u );
    end;
    for j:= 1 to p do begin
      read ( u );
      include ( r, u );
    end;
    readln;
    read ( c );
    case c of
      '=': begin less:= less - l - r; more:= more - l - r; end;
      '<': begin less:= less * l; more:= more * r; end;
      '>': begin less:= less * r; more:= more * l; end;
    end;
  end;

 { Analyzing information and writing answer }
  all:= less + more;
  cnt:= 0;
  for i:= 1 to n do
    if i in all then begin
      inc ( cnt );
      idx:= i;
    end;
  if cnt = 1 then
    writeln ( idx )
  else
    writeln ( 0 );
end.