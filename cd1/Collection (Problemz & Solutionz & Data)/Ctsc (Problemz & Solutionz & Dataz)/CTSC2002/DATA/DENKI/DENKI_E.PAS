const
  left=1; up=2; down=3; right=4;
  ch:array[1..4] of char=('L','U','D','R');
  maxn=20;
  maxc=2000;
var
  n,commandcnt:integer;
  command:array[1..maxc] of char;
  posx,posy:integer; {target position}
  map:array[1..maxn,1..maxn] of integer;
  pos:array[1..maxn,1..2] of integer;
  centerx,centery:integer;

procedure init;
var i,x,y:integer; f:text;
begin
  assign(f,paramstr(3));
  reset(f);
  read(f,n);
  for i:=1 to n do
    read(f,pos[i,1],pos[i,2]);
  fillchar(map,sizeof(map),0);
  for i:=1 to n do
  begin
    read(f,x,y);
    map[x,y]:=1;
  end;
  close(f);
end;

procedure judge;
var minx,miny,i:integer;
begin
  minx:=pos[1,1];
  miny:=pos[1,2];
  for i:=2 to n do
  begin
    if pos[i,1]<minx then minx:=pos[i,1];
    if pos[i,2]<miny then miny:=pos[i,2];
  end;
  for i:=1 to n do
    if (pos[i,1]-minx+1>maxn)or(pos[i,2]-miny+1>maxn)or
    (map[pos[i,1]-minx+1,pos[i,2]-miny+1]<>1) then {attension to R+}
    begin
      writeln(0);
      halt;
    end;
end;

procedure DoCommand(c:char);
var
  blocked:array[1..maxn] of boolean;
  foundnew:boolean;
  i,j:integer;
begin
  {mark}
  fillchar(blocked,sizeof(blocked),0);
  case c of
    'U':
    for i:=1 to n do
      if (pos[i,2]=0)and(pos[i,1]=1) then blocked[i]:=true;
    'D':
    for i:=1 to n do
      if (pos[i,2]=0)and(pos[i,1]=-1) then blocked[i]:=true;
    'L':
    for i:=1 to n do
      if (pos[i,1]=0)and(pos[i,2]=1) then blocked[i]:=true;
    'R':
    for i:=1 to n do
      if (pos[i,1]=0)and(pos[i,2]=-1) then blocked[i]:=true;
  end;

  foundnew:=true;
  while foundnew do
  begin
    foundnew:=false;
    for i:=1 to n do
      if blocked[i] then
        for j:=1 to n do
          if not blocked[j] and (abs(pos[i,1]-pos[j,1])+abs(pos[i,2]-pos[j,2])=1) then
          begin
            foundnew:=true;
            blocked[j]:=true;
          end;
  end;
  {move}
  case c of
    'U':
    for i:=1 to n do
      if not blocked[i] then dec(pos[i,1]);
    'D':
    for i:=1 to n do
      if not blocked[i] then inc(pos[i,1]);
    'L':
    for i:=1 to n do
      if not blocked[i] then dec(pos[i,2]);
    'R':
    for i:=1 to n do
      if not blocked[i] then inc(pos[i,2]);
  end;
end;

procedure check;
var i,code:integer; c:char; f:text; firstline:string;
begin
  assign(f,paramstr(1));
  reset(f);
  readln(f,firstline);
  val(firstline,commandcnt,code);
  for i:=1 to commandcnt do
  begin
    read(f,c);
    DoCommand(c);
  end;
  close(f);
  judge;
  if commandcnt<=maxc then writeln(10)
  else writeln(0);
end;

begin
  init;
  check;
end.
