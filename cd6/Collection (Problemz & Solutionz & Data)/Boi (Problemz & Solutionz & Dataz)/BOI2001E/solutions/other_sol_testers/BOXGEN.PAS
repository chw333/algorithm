{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
const
  MaxBoxSize = 100;
  Empty = 0;
  Mirror = 1;
  Horizontal = 2;
  Vertical = 4;

type
  tinout = array[1..MaxBoxSize*2] of integer;
var
  inout : tinout;
  box : array[1..MaxBoxSize,1..MaxBoxSize] of byte;
  mirrorInCol : array[1..MaxBoxSize] of boolean;

  sizex, sizey : integer;


procedure writeIn(name:string);
var
  f : text;
  i : integer;
  outin : tinout;
begin
  assign(f,name);
  rewrite(f);
  writeln(f,sizey,' ',sizex);
  for i := 1 to sizex + sizey do
  begin
    writeln(f,inout[i]);
    outin[inout[i] - sizex - sizey] := i;
  end;
  for i := 1 to sizex + sizey do
  begin
    writeln(f,outin[i]);
  end;
  close(f);
end;


{ Returns X (column) of a given hole }
function XfromNumber(nr : integer): integer;
begin
  if nr <= sizey then
    XfromNumber := 1
  else
  if nr <= sizex + sizey then
    XfromNumber := nr - sizey
  else
  if nr <= sizex + 2 * sizey then
    XfromNumber := sizex
  else
    XfromNumber := sizex - (nr - sizex - 2 * sizey) + 1;
end;
{ Returns Y (row) of a given hole }
function YfromNumber(nr : integer): integer;
begin
  if nr <= sizey then
    YfromNumber := nr
  else
  if nr <= sizex + sizey then
    YfromNumber := sizey
  else
  if nr <= sizex + 2 * sizey then
    YfromNumber := sizey - (nr - sizex - sizey) + 1
  else
    YfromNumber := 1;
end;
{ returns true if hole is a horizontal one}
function HfromNumber(nr : integer): boolean;
begin
  if nr <= sizey then
    HfromNumber := true
  else
  if nr <= sizex + sizey then
    HfromNumber := false
  else
  if nr <= sizex + 2 * sizey then
    HfromNumber := true
  else
    HfromNumber := false;
end;


function number(x,y:integer;horiz:boolean):integer;
begin
  if horiz then
  begin
    if x = 1 then
      number := y
    else
      number := 2 * sizey + sizex + 1 - y;
  end
  else
  begin
    if y = 1 then
      number := 2 * sizey + 2 * sizex + 1 - x
    else
      number := x + sizey;
  end;
end;

procedure randombox(sx,sy:integer;d:real);
var
  x,y:integer;
begin
  sizex := sx;
  sizey := sy;
  for x := 1 to sizex do
    for y := 1 to sizey do
      if random>d then box[x,y] := Empty
                    else box[x,y] := Mirror;
end;

procedure generateInOut(var inout:tinout);
procedure traceV(x, y : integer; var xo, yo : integer; var horiz:boolean);forward;
procedure traceH(x, y : integer; var xo, yo : integer; var horiz:boolean);
begin
  if x > sizex  then
  begin
    xo := sizex;
    yo := y;
    horiz := true;
  end
  else
  if (box[x,y] and Mirror) = 0 then
  begin
    box[x,y] := box[x,y] or Horizontal;
    traceH(x + 1,y ,xo ,yo ,horiz);
  end
  else
  begin
    traceV(x, y - 1,xo ,yo ,horiz);
  end;
end;

procedure traceV(x, y : integer; var xo, yo : integer; var horiz:boolean);
begin
  if (y < 1) then
  begin
    yo := 1;
    xo := x;
    horiz := false;
  end
  else
  if box[x,y] and Mirror <> 0 then
  begin
    traceH(x + 1,y ,xo ,yo ,horiz);
  end
  else
  begin
    traceV(x,y - 1 ,xo ,yo ,horiz);
  end;
end;
var
  i : integer;
  xo, yo : integer;
  horiz : boolean;
begin
  for i := 1 to sizey do
  begin
    traceH(XfromNumber(i), YfromNumber(i), xo, yo, horiz);
    inout[i] := number(xo,yo,horiz);
  end;
  for i := sizey + 1 to sizey + sizex do
  begin
    traceV(XfromNumber(i), YfromNumber(i), xo, yo, horiz);
    inout[i] := number(xo,yo,horiz);
  end;
end;




procedure solve;
procedure traceV(x ,y, xo, yo : integer; horiz : boolean);forward;

procedure traceH(x ,y, xo, yo : integer; horiz : boolean);
begin
  if (x = xo) and (y = yo) then
  begin
    if horiz then
      box[x,y] := box[x,y] or Horizontal
    else
    begin
      box[x,y] := box[x,y] or Mirror;
      mirrorInCol[x] := true;
    end;
  end
  else
  if ((not mirrorInCol[x]) and (x <> xo)) or (y = yo) then
  begin
    box[x,y] := box[x,y] or Horizontal;
    traceH(x + 1,y ,xo ,yo ,horiz);
  end
  else
  begin
    box[x,y] := box[x,y] or Mirror;
    mirrorInCol[x] := true;
    traceV(x, y - 1,xo ,yo ,horiz);
  end;
end;

procedure traceV(x ,y, xo, yo : integer; horiz : boolean);
begin
  if (x = xo) and (y = yo) then
  begin
    if not horiz then
      box[x,y] := box[x,y] or Vertical
    else
    begin
      box[x,y] := box[x,y] or Mirror;
      mirrorInCol[x] := true;
    end;
  end
  else
  if box[x,y] and Mirror <> 0 then
  begin
    traceH(x + 1,y ,xo ,yo ,horiz);
  end
  else
  begin
    box[x,y] := box[x,y] or Vertical;
    traceV(x,y - 1 ,xo ,yo ,horiz);
  end;
end;
var
  i : integer;
begin
  for i := 1 to sizey do
  begin
    traceH(XfromNumber(i), YfromNumber(i),
           XfromNumber(inout[i]), YfromNumber(inout[i]),
           HfromNumber(inout[i]));
  end;
  for i := sizey + 1 to sizey + sizex do
  begin
    traceV(XfromNumber(i), YfromNumber(i),
           XfromNumber(inout[i]), YfromNumber(inout[i]),
           HfromNumber(inout[i]));
  end;
end;

const
  sx : array[1..12] of integer = (10, 10,  20, 20, 40,  50,  60, 60, 70, 80, 80, 100);
  sy : array[1..12] of integer = (10, 30,  20, 50, 45,  50,  100,70, 70, 80, 80, 100);
  d : array[1..12] of real =        (0.1,0.01,0.5,0.2,0.9, 0.05,0.1,0.2,0.5,0.1,0.3,0.1);
  rs : array[1..12] of longint =    (1,  2,   3,  4,  5,   6,   7,  8  ,9  ,10 ,11 ,12);
var
  t : longint;
  tio : tinout;
  i : integer;
  s : string;
  x : real;
begin
  for t:= 1 to 12 do
  begin
    randseed := rs[t];
    x := random;
    randombox(sx[t],sy[t],d[t]);
    generateInOut(tio);
    inout := tio;
    fillchar(box,sizeof(box),0);
    fillchar(mirrorInCol,sizeof(mirrorInCol),0);
    solve;
    generateInOut(tio);
    i := 1;
    while (i<=sizex + sizey) and (tio[i] = inout[i]) do inc(i);
    if i <= sizex + sizey then writeln('BAD');
    writeln(t);
    str(t,s);
    writeIn('box'+ s + '.in');
  end;
end.