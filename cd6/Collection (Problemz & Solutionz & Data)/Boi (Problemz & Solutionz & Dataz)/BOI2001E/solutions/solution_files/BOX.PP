{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
const
  MaxBoxSize = 100;
  Empty = 0;
  Mirror = 1;
  Horizontal = 2;
  Vertical = 4;


var
  inout : array[1..MaxBoxSize*2] of integer;
  box : array[1..MaxBoxSize,1..MaxBoxSize] of byte;
  mirrorInCol : array[1..MaxBoxSize] of boolean;

  sizex, sizey : integer;
{ Reads input file }
procedure readIn;
var
  f : text;
  i : integer;
begin
  assign(f,'box.in');
  reset(f);
  readln(f,sizey,sizex);
  for i := 1 to sizex + sizey do
  begin
    readln(f,inout[i]);
  end;
  close(f);
end;
{ Writes output file }
procedure writeOut;
var
  x, y : integer;
  f : text;
begin
  assign(f,'box.out');
  rewrite(f);
  for y:=1 to sizey do
  begin
    for x:=1 to sizex do
    begin
      write(f, box[x,y] and Mirror, ' ');
    end;
    writeln(f);
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

procedure traceV(x ,y, xo, yo : integer; horiz : boolean);forward;

{ traces light horizontaly }
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

{traces light verticaly }
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


{ we try to put mirrors in such way that every
light beam goes as far as posible to the upper part of the box}

procedure solve;
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

begin
  readIn;

  fillchar(box,sizeof(box),0);
  fillchar(mirrorInCol,sizeof(mirrorInCol),0);
  solve;

  writeOut;
end.
