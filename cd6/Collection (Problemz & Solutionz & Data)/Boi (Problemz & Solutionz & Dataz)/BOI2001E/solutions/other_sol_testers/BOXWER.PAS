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
procedure readIn(name:string);
var
  f : text;
  i : integer;
begin
  assign(f,name);
  reset(f);
  readln(f,sizey,sizex);
  for i := 1 to sizex + sizey do
  begin
    readln(f,inout[i]);
  end;
  close(f);
end;
{ Reads output file }
function readOut(name:string):boolean;
var
  x, y : integer;
  f : text;
begin
  readOut := false;
  assign(f,name);
  reset(f);
  for y:=1 to sizey do
  begin
    for x:=1 to sizex do
    begin
      {$I-}
      read(f,box[x,y]);
      {$I+}
      if (IOResult<>0) or (eof(f)) or (box[x,y] > 1) or
         (box[x,y] < 1) then exit;
    end;
    readln(f);
  end;
  close(f);
  readOut := true;
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



function verify:boolean;
var
  i : integer;
  xo, yo : integer;
  horiz : boolean;
begin
  verify := false;
  for i := 1 to sizey do
  begin
    traceH(XfromNumber(i), YfromNumber(i), xo, yo, horiz);
    if (xo <> XfromNumber(inout[i])) or (yo <> YfromNumber(inout[i]))
       or (horiz <> HfromNumber(inout[i])) then exit;
  end;
  for i := sizey + 1 to sizey + sizex do
  begin
    traceV(XfromNumber(i), YfromNumber(i), xo, yo, horiz);
    if (xo <> XfromNumber(inout[i])) or (yo <> YfromNumber(inout[i]))
       or (horiz <> HfromNumber(inout[i])) then exit;
  end;
  verify := true;
end;

begin
  readIn(paramstr(1));
  if not readOut(paramstr(2)) then
  begin
    writeln('SYNTAX');
    exit;
  end;
  if verify then
    writeln('OK')
  else
    writeln('WRONG');
end.
