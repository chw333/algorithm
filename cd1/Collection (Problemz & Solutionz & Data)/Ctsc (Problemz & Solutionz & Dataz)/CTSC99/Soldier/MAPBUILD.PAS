{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
Program MkMap (input, output);
Uses
  Graph , Crt;
Const
  MapFilename              = 'Maze.005';
  MaxS                     = 20;
  MaxP                     = 3;
  MaxPn                    = 10;
  GColor                   : array[0 .. Maxpn + 1] of byte
                           = (white , Blue , Green , Cyan , Red , Magenta,
                              Brown , LightGray , LightBlue , LightGreen ,
                              Yellow , Black);

  
  DeltaX                   = 30;
  DeltaY                   = 30;
  Winsize                  = 300;
  QuitC                    = #27;
  rightC                   = #77;
  downC                    = #80;
  upC                      = #72;
  leftC                    = #75;
  rightM                   = 'F';
  leftM                    = 'S';
  upM                      = 'E';
  downM                    = 'D';

Type
  TMap                     = array[1 .. maxs , 1 .. maxs , 1 .. 4] of shortint;
  TPos                     = record
                               x , y : integer;
                             end;
  Tstring                  = string[maxs + maxs];
  TKey                     = set of 0.. maxpn;
Const
  Delta                    : Array[1 .. 4] of TPos
                           = ((x: 0;y:1),
                              (x: 1;y:0),
                              (x:-1;y:0),
                              (x: 0;y:-1));

Var
  Map                      : Tmap;
  n , m  , pn , sn         : integer;
  p                        : Integer;
  Sp , Dp                  : array[1 .. maxp] of TPos;
  USize                    : Integer;
  DN                       : integer;
  GN                       : integer;
  Keysets                  : array[1 .. maxs , 1 .. maxs] of Tkey;
  infolen                  : integer;

Function Max (com1 , com2 : integer) : integer;
begin
  if com1 > com2
    then max :=com1
    else max :=com2;
end; {max}


Procedure Initalize;
Var
  GDriver , GMode          : Integer;
  i , j                    : integer;
begin
  write ('n,m,pn='); readln (n , m ,pn);
  fillchar (map , sizeof(map) , 0);
  fillchar (sp , sizeof(sp) , 0);
  fillchar (dp , sizeof(dp) , 0);
  GDriver :=Vga; Gmode :=VgaHi;
  initgraph (GDriver , GMode , 'e:\xz\tp\bgi');
  Usize :=winsize div max(n , m);
  infoLen :=usize div pn;
  Gn :=0;
  sn :=0;
  fillchar(keysets , sizeof(keysets) , 0);
end; {initalize}


Function LUX (inx , iny : integer) : integer;
begin
  LUX :=(inx - 1) * USize + DeltaX;
end; {LUX}

Function LUY (inx , iny : integer) : integer;
begin
  LUY :=(iny - 1) * USize + DeltaY;
end; {LUY}

Function RUX (inx , iny : integer) : integer;
begin
  RUX :=(inx - 1) * USize + DeltaX;
end; {RUX}

Function RUY (inx , iny : integer) : integer;
begin
  RUY :=(iny - 0) * USize + DeltaY;
end; {RUY}

Function LDX (inx , iny : integer) : integer;
begin
  LDX :=(inx - 0) * USize + DeltaX;
end; {LDX}

Function LDY (inx , iny : integer) : integer;
begin
  LDY :=(iny - 1) * USize + DeltaY;
end; {LDY}

Function RDX (inx , iny : integer) : integer;
begin
  RDX :=(inx - 0) * USize + DeltaX;
end; {RDX}

Function RDY (inx , iny : integer) : integer;
begin
  RDY :=(iny - 0) * USize + DeltaY;
end; {RDY}

Procedure DrawGate (nx , ny : integer; nd : integer; flag : integer);
begin
  setcolor (GColor[flag]);
  if flag > pn
    then setcolor (black);
{  if flag = 0
    then setcolor (White)
    else setcolor (black);}
    if nd = 1
      then line (RUY(nx , ny) , RUX(nx , ny)+1 , RDY(nx , ny) , RDX (nx , ny)-1)
      else line (lDY(nx , ny) + 1 , LDX(nx , ny) , RDY(nx , ny) - 1 , RDX (nx , ny));
{  setcolor (white);}
end; {DrawGate}

Procedure DrawMap;
Var
  i , j , k                : integer;
  si                       : Tstring;
begin
  for i :=1 to n do
    begin
      Str (i , si);
      outtextxy (DeltaY - 15 , (LUX(i , 1)+LDX(i , 1)) div 2 , si);
    end;
  for i :=1 to m do
    begin
      str (i , si);
      outtextxy ((LUY(1 , i) + RUY(1 , i)) div 2 , deltaX - 15 , si);
    end;
  rectangle (LUY (1 , 1) , LUX(1 , 1) , RDY(n , m) , RDX(n , m));
  for i :=1 to n do
    for j :=1 to m do
      begin
        putpixel (RDY(i , j) , RDx(i , j) , White);
        DrawGate (i , j , 1 , map[i,j][1]);
        DrawGate (i , j , 2 , map[i,j][2]);
      end;
end; {DrawMap}

Procedure Freeall;
var readc : char;
begin
  setcolor (white);
  outtextxy (DeltaY , 440 , 'Press Q/q to Ignore ...');
  repeat
    readc :=UpCase (Readkey);
  Until readc in [QuitC , 'Q'];
  closegraph;
  if readc = 'Q'
    then halt;
end; {Freeall}

Function CheckPos (InP : TPos) : boolean;
begin
  checkPos :=(Inp.x >0) and (inp.y > 0) and (Inp.x <= n) and (inp.y <= m);
end; {CheckP}

Procedure ShowPos (InP : tpos;flag : byte);
begin
  if flag = 0
    then setcolor (black)
    else setcolor (Lightred);
  rectangle (LUY (inp.x , inp.y)+3 , LUX(inp.x , inp.y)+3 , RDY(inp.x , inp.y)-3 , RDX(inp.x , inp.y)-3);
end; {ShowPos}

Procedure BuildMap;
var
  Action                   : Char;
  NowP , NextP             : TPos;
  MoveD                    : integer;
  pstr                     : Tstring;
  tmp : integer;
begin
  NowP.x :=1; NowP.y :=1;
  ShowPos (nowp , 1);
  repeat
    Action :=UpCase(Readkey);
    MoveD :=0;
    case Action of
      rightC , RightM: MoveD :=1;
      downC  , DownM : MOveD :=2;
      upC    , UpM   : MoveD :=3;
      leftC  , LeftM : MoveD :=4;
    end;
    if Action in [RightM , DownM , UpM , LeftM]
      then moved :=-moved;
    if MoveD <> 0
      then begin
             NextP.x :=NowP.x + delta[abs(MoveD)].x;
             NextP.y :=NowP.y + delta[abs(MoveD)].y;
             if checkpos (NextP)
               then begin
                      if moved > 0
                        then begin
                               ShowPos (NowP , 0);
                               NowP :=NextP;
                               ShowPos (NextP , 1);
                             end
                        else begin
                               repeat
                                 action :=Upcase(readkey);
                               Until action in ['0' .. chr(pn+48) , 'C'];
                               if action = 'C'
                                 then map[nowp.x , nowp.y][abs(MoveD)] :=pn + 1
                                 else map[nowp.x , nowp.y][abs(MoveD)] :=ord(action)-48;
                               map[nextp.x,nextp.y][5-abs(moveD)] :=map[nowp.x,nowp.y][abs(MoveD)];
                               if abs(MoveD) <= 2
                                 then DrawGate (nowp.x , nowp.y , abs(moved) , map[nowp.x,nowp.y][abs(MoveD)])
                                 else DrawGate (nextp.x , nextp.y , 5-abs(moved) , map[nowp.x,nowp.y][abs(MoveD)]);
                               if (map[nowp.x , nowp.y][abs(moved)] = 0)
                                 then inc (gn)
                                 else if (map[nowp.x , nowp.y][abs(moved)] = pn)
                                        then dec (gn);

{                               inc (gn , map[nowp.x,nowp.y][abs(MoveD)]*2-1);}
                             end;
                    end;
           end
      else
        if action in ['1'..chr(pn+48)] then
          begin
            tmp :=ord(action) - 48;
            include (keysets[nowp.x , nowp.y] , tmp);
            setcolor (Gcolor[tmp]);
            rectangle (LUY(nowp.x , nowp.y) + infolen * (tmp - 1) + 1 ,
                       LUX (nowp.x , nowp.y) + 1 ,
                       LUY(nowp.x , nowp.y) + infolen * tmp - 1,
                       LUX (nowp.x , nowp.y) + USize - 4);
            inc (Sn);
          end;

        {
        if ((p = 0) or (dp[p].x > 0)) and (p < MaxP)
                       then begin
                              inc (p);
                              str (p , pstr);
                              Sp[p] :=nowp;
                              setcolor (LightMagenta);
                              outtextxy (LUY (nowp.x , nowp.y)+5 , LUX(nowp.x , nowp.y)+5 , pstr);
                            end
        else  if (dp[p].x = 0) and (nowp.x >= sp[p].x)
                       and (nowp.y >= sp[p].y)
                       and (nowp.x + nowp.y > sp[p].x + sp[p].y)
                       then begin
                              str (p , pstr);
                              dp[p] :=nowp;
                              Setcolor (LightBlue);
                              outtextxy (LUY (nowp.x , nowp.y)+5 , LUX(nowp.x , nowp.y)+5 , pstr);
                             end;}
  Until Action=QuitC;
end; {BuildMap}

Procedure PrintMap;
var
  outfp                    : text;
  i , j , k                : integer;
  left                     : Integer;
begin
  assign (outfp , MapFileName); rewrite (outfp);
  writeln (outfp , n , ' ' , m , ' ' , pn);
  gn :=0;
  for i :=1 to n do
    for j :=1 to m do
      for k :=1 to 2 do
        if (i+delta[k].x<=n) and (j+delta[k].y<=m) and (map[i , j][k] <= pn)
          then begin
                 inc (gn);
               end;
  writeln (outfp , gn);
  for i :=1 to n do
    for j :=1 to m do
      for k :=1 to 2 do
        if (i+delta[k].x<=n) and (j+delta[k].y<=m) and (map[i , j][k] <= pn)
          then begin
                 writeln (outfp , i , ' ' , j , ' ' , i + delta[k].x , ' ' , j + delta[k].y , ' ' , map[i , j][k]);
               end;

{  writeln (outfp , p);
  for i :=1 to p do
    writeln (outfp , sp[i].x , ' ' , sp[i].y , ' ' , dp[i].x , ' ' , dp[i].y);}
  writeln (outfp , sn);
  for i :=1 to n do
    for j :=1 to m do
      for k :=1 to pn do
        if k in keysets[i , j]
          then writeln (outfp , i , ' ' , j , ' ' , k);
  close (outfp);
end; {Printmap}

Begin
  Initalize;
  Drawmap;
  BuildMap;
  PrintMap;
  Freeall;
end. {main}