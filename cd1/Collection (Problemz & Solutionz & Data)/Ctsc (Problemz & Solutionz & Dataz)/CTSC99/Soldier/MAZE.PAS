{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R-,S+,T-,V+,X+,Y+}
{$M 65520,0,655360}
Program Maze (input , output);

Const
  Inputname                = 'Maze.005';
  outputname               = 'Maze.ou5';
  Maxsize                  = 10;
  MaxP                     = 9;
  MaxInfoL                 = 1 shl MaxP;
  Direction                : Array[1 ..4 , 1 .. 2] of shortint
                           = ((-1 , 0) , (0 , 1) , (0 , -1) , (1 , 0));
  Mirror                   : array[-1 .. 1 , -1 .. 1] of byte
                           = ((0 , 1 , 0) ,
                              (3 , 0 , 2) ,
                              (0 , 4 , 0));

Type
  TInfo                    = Array[0 .. MaxInfoL - 1] of Integer;
  TList                    = Array[1 .. Maxsize , 1 .. Maxsize] of ^TInfo;
  Tmark                    = Array[0 .. MaxInfoL - 1] of boolean;
  TChange                  = Array[1 .. Maxsize , 1 .. Maxsize] of TMark;
  TKeySet                  = Integer;
  TKeySets                 = array[1 .. maxsize , 1 .. maxsize] of TKeyset;
  TMap                     = array[1 .. maxsize , 1 .. maxsize , 1 .. 4] of Shortint;
Var
  N , M , P                : Integer;
  List                     : TList;
  KeySets                  : TKeySets;
  Map                      : TMap;
  MaxInfoNum               : integer;
  Ans                      : Integer;

Procedure Initialize;
Var
  Infp                     : Text;
  i , j , k  , s , g       : integer;
  x1 , y1 , x2 , y2        : integer;

begin
  fillchar (Keysets , sizeof(Keysets) ,0);
  fillchar (map , sizeof(map) , $FF);
  
  Ans :=-1;

  assign (infp , inputname); reset (infp);
  readln (infp , n , m , p); maxinfoNum :=(1 shl p) - 1;
  readln (infp , k);
  for i :=1 to n do
    for j :=1 to m do
      begin
        new (list[i , j]);
        fillchar (List[i , j]^ , sizeof(List[i ,j ]^) , $FF);
      end;
  for i :=1 to K do
    begin
      readln (infp , x1,y1,x2,y2 , g);
      Map[x1 , y1 , mirror[x2-x1,y2-y1]] :=g;
      Map[x2 , y2 , mirror[x1-x2,y1-y2]] :=g;
    end;
  readln (infp , s);
  for i :=1 to s do
    begin
      readln (infp , x1 , y1 , g);
      Keysets[x1 , y1] :=Keysets[x1 , y1] Or (1 shl (g - 1));
    end;
  close (infp);
end; {initialize}

Procedure Solve;
Var
  i , j , k                : integer;
  change                   : TChange;
  Stop                     : Boolean;
  rx , ry , rinfo          : Integer;
  fx , fy , finfo          : Integer;
  Dp                       : Integer;
Function KeysToDoor (Keys : integer; Door : integer) : boolean;
begin
  KeysToDoor :=(door < 0) or ((keys and (1 shl (door - 1))) > 0);
end; {keysToDoor}

Function Better (ans1 , ans2 : integer) : boolean;
begin
  Better :=(ans2 < 0) or ((ans1 >= 0) and (ans1 < ans2));
end; {better}

begin
  fillchar (change , sizeof(change) , 0);
  List[1 , 1]^[0] :=0;
  Change[1 , 1 , 0] :=True;
  Stop :=False;
  repeat
    Stop :=True;
    for rx :=1 to N do
      for ry :=1 to M do
        for rinfo :=0 to maxinfoNum do
          if change[rx , ry , rinfo] then
          begin
            change[rx , ry , rinfo] :=False;
            for dp :=1 to 4 do
              if (map[rx , ry , dp] <> 0)
                and ((KeysToDoor(rinfo , map[rx , ry , dp]))
                   or(KeysToDoor(Keysets[rx , ry] , map[rx , ry , dp])))

              then
              begin
                fx :=rx + direction[dp , 1]; fy :=ry + direction[dp , 2];
                if (fx >= 1) and (fy >= 1) and (fx <= n) and (fy <= m)
                  then
                  begin
                    for finfo :=0 to MaxinfoNum do
                      if (finfo and rinfo = rinfo) and
                         ((rinfo or keysets[rx , ry]) and finfo = finfo) and
                         (KeysToDoor (finfo , map[rx , ry ,dp]))
                         and (Better (list[rx , ry]^[rinfo] + 1 ,
                                      list[fx , fy]^[finfo]))
                       then begin
                              list[fx , fy]^[finfo] :=list[rx , ry]^[rinfo] + 1;
                              change[fx , fy , finfo] :=True;
                              stop :=False;
                            end;
                  end;
              end;
          end;
  Until Stop;
  for rinfo :=0 to maxinfonum do
    if Better (list[n , m]^[rinfo] , ans)
      then begin
             ans :=list[n , m]^[rinfo];
           end;
end; {Solve}

Procedure Printout;
var
  outfp                    : text;
begin
  assign (outfp , outputname); rewrite (outfp);
  writeln (outfp , ans);
  close (outfp);
end; {Printout}

Procedure Freeall;
var
  i , j  : integer;
begin
  for i :=1 to n do
    for j :=1 to m do
      dispose (list[i , j]);
end; {Freeall}

Begin
  Initialize;
  Solve;
  Printout;
  Freeall;
end. {main}