{Module of Matrix, by shirunting}
{WATCH OUT the precision of Standard , AnitMatrix and D}
{modified 11:28,26,Feb,2001}

unit Matrix;

interface

const
  miniDelta = 1E-7; //zero defination
  MAX_MATRIX_SIZE = 101; //maxsize of matrix
type
  real = extended;
  TArr1 = array[1 .. MAX_MATRIX_SIZE] of real;
  TArr2 = array[1 .. MAX_MATRIX_SIZE] of TArr1;

  TMatrix = object
        Rn , Cn : integer;  //row number and column number , matrix[Rn*Cn]
        matrix : TArr2;
{Part 0.1 构造函数}
        Constructor Create(inRn , inCn : integer);

{Part 1设置特殊矩阵}
//1.1空矩阵
        Procedure SetEmptyMatrix;
//1.2单位矩阵
        Procedure SetUnitMatrix;

//Part 2逻辑关系
//2.1 判定0元素 (Function isRealZero(z:real) : boolean)
//2.2 判定0行
        Function isEmptyLine (ln : integer): boolean;
//2.3 判定0矩阵
        Function isEmpty : boolean;
//2.4 判定0相等
        Function isEqual(X : TMatrix) : boolean;

{Part 3 输入输出接口}
//3.1 文件读入
        Procedure InputFromFile (FName : String);
//3.2 文件输出
        Procedure OutputToFile (FName : string);

{Part 4 基本行操作}
//4.1 行交换 Line[Ln1]<->Line[Ln2]
        Procedure LineOprSwap (Ln1 : integer; Ln2 : integer);
//4.2 行相加 Line[Ln1]=Line[Ln1]+Line[Ln2]
        Procedure LineOprAdd (Ln1 , Ln2 : integer);
//4.3 行乘加 Line[Ln1]=Line[Ln1]+c*Line[Ln2]
        Procedure LineOprAdd2 (Ln1 , Ln2 : integer; c : real);
//4.4 行相减 Line[Ln1]=Line[Ln1]-Line[Ln2]
        Procedure LineOprMinus(Ln1 , Ln2 : integer);
//4.5 行乘   Line[Ln1]=c*Line[Ln1]
        Procedure LineOprMultC (Ln1 : integer; c : real);
//4.6 行除   Line[Ln1]=Line[Ln1]/c
        Procedure LineOprDivC (Ln1 : integer; c : real);

{Part 5 矩阵算术运算}
//5.1 转置
        Procedure OprTranspos (var Y : TMatrix);
//5.2 复制
        Procedure OprCopy (var Y : TMatrix);
//5.3 相加
        Procedure OprAdd (X:TMatrix ; var  Y:TMatrix);
//5.4 相减
        Procedure OprMinus (X:TMatrix ; var Y:TMatrix);
//5.5 相乘
        Procedure OprMult (X:TMatrix ; var Y:TMatrix);

{Part 6 矩阵变换和特征提取}
//6.1 相抵标准型，计算秩
        Procedure Standardize (var Y:TMatrix; var Rank : integer); //Gause
//6.2 计算逆矩阵
        Procedure OprAntiMatrix (var Y :TMatrix; var flag : boolean);
//6.3 计算行列式
        Procedure OprD (var D : real);
end;

implementation

//Part 0.0 辅助函数

Function IsZero (com : real) : boolean;
begin
  result :=abs(com) < miniDelta;
end; {IsZero}

Function Min_Int (com1 , com2 : integer) : Integer;
begin
  if com1 < com2
    then Min_Int :=com1
    else min_Int :=com2;
end; {Min_Int}

Function Max_Int (com1 , com2 : integer) : integer;
begin
  if com1 > com2
    then Max_Int :=com1
    else max_Int :=com2;
end; {Max_Int}

//Part 0.1 构造函数
Constructor TMatrix.Create (inRn , inCn : integer);
Begin
  fillchar (Matrix , sizeof(Matrix) , 0);
  Rn :=inRn; Cn :=inCn;
end; {Create}

//Part 1设置特殊矩阵
//1.1空矩阵
Procedure TMatrix.SetEmptyMatrix;
begin
  fillchar (matrix,sizeof(matrix) , 0);
end; {SetEmptyMatrix}

//1.2单位矩阵
Procedure TMatrix.SetUnitMatrix;
var
  i : integer;
begin
  if (Rn <> Cn)
    then exit;
  fillchar (matrix,sizeof(matrix) , 0);
  for i :=1 to Rn do
    matrix[i,i] :=1;
end; {SetEmptyMatrix}

//Part 2逻辑关系

//2.1 判定0元素
Function isRealZero (z : real) : boolean;
begin
  isRealZero :=abs(z)<miniDelta;
end; {isRealZero}

//2.2 判定0行
Function TMatrix.isEmptyLine (ln : integer) : boolean;
var
  j : integer;
begin
  for j :=1 to Cn do
    if not (isRealZero(matrix[ln , j]))
      then begin
        isEmptyLine :=False;
        exit;
      end;
  isEmptyLine :=True;
end; {isEmptyLine}

//2.3 判定0矩阵
Function TMatrix.isEmpty : boolean;
var
  i , j : integer;
begin
  for i :=1 to rn do begin
    if Not (isEmptyLine (i))
      then begin
        isEmpty :=False;
        exit;
      end;
  end;
  isEmpty :=True;
end; {isEmpty}

//2.4 判定0相等
Function TMatrix.isEqual (X : TMatrix) : Boolean;
var
  i , j :integer;
begin
  if (Rn <> X.Rn) or (Cn <> X.Cn) then
    begin
      isEqual :=false;
      exit;
    end;
  for i:=1 to rn do
    for j :=1 to cn do
      if matrix[i , j] <> X.matrix[i , j]
        then begin
          isEqual :=False;
          exit;
        end;
  isEqual :=True;
end; {IsEqual}

//Part 3 输入输出接口

//3.1 文件读入
Procedure TMatrix.InputFromFile (FName : String);
var
  i , j : integer;
  infp : text;
begin
   assign (infp , FName); reset (infp);
   read (infp , Rn , Cn);
   Create (Rn , Cn);
   for i :=1 to Rn do begin
     for j :=1 to Cn do begin
       read (infp , matrix[i,j]);
     end;
   end;
   close (infp);
end; {InputFromFile}

//3.2 文件输出
Procedure TMatrix.OutputToFile (FName : String);
var
  i, j : integer;
  outfp: text;
begin
  assign (outfp , FName); rewrite (outfp);
  writeln (outfp , Rn , ' ' , Cn);
  for i :=1 to Rn do begin
    for j :=1 to Cn do
      write (outfp , matrix[i,j]:10:3);
    writeln (outfp);
  end;
  close (outfp);
end; {OutputToFile}

//Part 4 基本行操作

//4.1 行交换 Line[Ln1]<->Line[Ln2]
Procedure TMatrix.LineOprSwap (Ln1 , Ln2 : integer);
var
  tmpLine : TArr1;
begin
  tmpLine :=matrix[Ln1]; matrix[Ln1] :=matrix[Ln2]; matrix[Ln2] :=tmpLine;
end; {TMatrix}

//4.2 行相加 Line[Ln1]=Line[Ln1]+Line[Ln2]
Procedure TMatrix.LineOprAdd (Ln1 , Ln2 : integer);
var
  j   : integer;
begin
  for j :=1 to Cn do
    matrix[Ln1][j] :=matrix[Ln1][j] + matrix[Ln2][j];
end;

//4.3 行乘加 Line[Ln1]=Line[Ln1] + c*Line[Ln2]
Procedure TMatrix.LineOprAdd2 (Ln1 , Ln2 : integer; c : real);
var
  j   : integer;
begin
  for j :=1 to Cn do
    matrix[Ln1][j] :=matrix[Ln1][j] + matrix[Ln2][j]*c;
end;

//4.4 行相减 Line[Ln1]=Line[Ln1]-Line[Ln2];
Procedure TMatrix.LineOprMinus (Ln1 , Ln2 : integer);
var
  j   : integer;
begin
  for j :=1 to Cn do
    matrix[Ln1][j] :=matrix[Ln1][j] - matrix[Ln2][j];
end;

//4.5 行乘 Line[Ln1]=Line[Ln1]*c;
Procedure TMatrix.LineOprMultC (Ln1 : integer; c : real);
var
  j   : integer;
begin
  for j :=1 to Cn do
    matrix[Ln1][j] :=matrix[Ln1][j]*c;
end;

//4.5 行除 Line[Ln1]=Line[Ln1]/c;
Procedure TMatrix.LineOprDivC (Ln1 : integer; c : real);
var
  j   : integer;
begin
  if IsZero(c)
    then exit;

  for j :=1 to Cn do
    matrix[Ln1][j] :=matrix[Ln1][j]/c;
end;

//Part 5 矩阵算术运算

//5.1 转置
Procedure TMatrix.OprTranspos(var Y:TMatrix);
var
  i , j : integer;
  Res : TMatrix;
begin
  Res.Create(Cn,Rn);
  for i :=1 to Rn do
    for j :=1 to Cn do
      Res.matrix[j,i] :=matrix[i,j];
  Res.OprCopy(Y);
end; {OprTranspos}

//5.2 复制
Procedure TMatrix.OprCopy (var Y: TMatrix);
begin
   Y.Create(Rn,Cn);
   Y.matrix := matrix;
end; {OprCopy}

//5.3 相加
Procedure TMatrix.OprAdd(X:TMatrix;var Y:TMatrix);
var
  i , j : integer;
  Res : TMatrix;
begin
  if (Rn<>X.Rn) or (Cn<>X.Cn)
    then exit;
  Res.Create(Rn,Cn);
  for i :=1 to Rn do
    for j :=1 to Cn do
      res.matrix[i,j]:=matrix[i,j]+x.matrix[i,j];
  Res.OprCopy(Y);
end; {OprAdd}

//5.3 相减
Procedure TMatrix.OprMinus(X:TMatrix;var Y:TMatrix);
var
  i , j : integer;
  Res : TMatrix;
begin
  if (Rn<>X.Rn) or (Cn<>X.Cn)
    then exit;
  Res.Create(Rn,Cn);
  for i :=1 to Rn do
    for j :=1 to Cn do
      Res.matrix[i,j]:=matrix[i,j]-x.matrix[i,j];
  Res.OprCopy(Y);
end; {OprAdd}

//5.3 相乘
Procedure TMatrix.OprMult(X:TMatrix;var Y:TMatrix);
var
  i , j , k: integer;
  Res : TMatrix;
begin
  if (Cn<>X.Rn)
    then exit;
  Res.Create(Rn,X.Cn);
  for i :=1 to Rn do
    for j :=1 to X.Cn do begin
      Res.matrix[i,j]:=0;
      for k :=1 to Cn do begin
        Res.matrix[i,j]:=Res.matrix[i,j] + matrix[i,k]*X.matrix[k,j];
      end;
    end;
  Res.OprCopy(Y);
end; {OprAdd}

//Part 6 矩阵变换和特征提取

//6.1 相抵标准型，计算秩
Procedure TMatrix.Standardize (var Y : TMatrix; var Rank : integer);
var
  i , j , k: integer;
  t : integer;
  res : TMatrix;
begin
  OprCopy (res);
  i :=0;
  j :=0;
  while (i < res.Rn) and (j < res.Cn) do
    begin
      inc (j);
      inc (i);
      k :=i;
      for t :=i + 1 to res.Rn do
        if abs (res.matrix[t , j]) > abs (res.matrix[k , j])
          then k :=t;
      if isZero (res.matrix[k , j])
        then begin
          dec (i);
          continue;
        end;
      if k <> i
        then res.LineOprSwap (i , k);
      res.LineOprDivC (i , res.matrix[i , j]);
      for k :=1 to res.Rn do
        if (k <> i) and (res.matrix[k , j] <> 0)
          then begin
            res.LineOprAdd2 (k , i , -res.matrix[k , j]);
          end;
    end;
  Rank :=Rn;
  while (Rank >= 0) and res.isEmptyLine (Rank)
    do dec (Rank);
  res.OprCopy(Y);
end; {Standardize}

//6.2 计算逆矩阵
Procedure TMatrix.OprAntiMatrix (var Y : TMatrix; var flag : boolean);
var
  i , j , k: integer;
  t : integer;
  res , antiM : TMatrix;
begin
  flag :=False;
  if (Rn <> Cn)
    then exit;

  OprCopy (res);
  antiM.Create(Rn, Cn);
  antiM.SetUnitMatrix;

  i :=0;
  j :=0;
  while (i < res.Rn) and (j < res.Cn) do
    begin
      inc (j);
      inc (i);
      k :=i;
      for t :=i + 1 to res.Rn do
        if abs (res.matrix[t , j]) > abs (res.matrix[k , j])
          then k :=t;
      if isZero (res.matrix[k , j])
        then begin
          dec (i);
          continue;
        end;
      if k <> i
        then begin
          AntiM.LineOprSwap (i , k);
          res.LineOprSwap (i , k);
        end;
      antiM.LineOprDivC (i,  res.matrix[i , j]);
      res.LineOprDivC (i , res.matrix[i , j]);

      for k :=1 to res.Rn do
        if (k <> i) and (res.matrix[k , j] <> 0)
          then begin
            antiM.LineOprAdd2 (k , i , -res.matrix[k , j]);
            res.LineOprAdd2 (k , i , -res.matrix[k , j]);
          end;
    end;
  AntiM.OprCopy(Y);
  flag :=true;
end; {OprAnitMatrix}

//6.3 计算行列式
Procedure TMatrix.OprD (var D : real);
var
  i , j , k: integer;
  t : integer;
  res : TMatrix;
begin
  if Rn <> Cn
    then exit;
  OprCopy (res);
  i :=0;
  j :=0;
  D :=1;
  while (i < res.Rn) and (j < res.Cn) do
    begin
      inc (j);
      inc (i);
      k :=i;
      for t :=i + 1 to res.Rn do
        if abs (res.matrix[t , j]) > abs (res.matrix[k , j])
          then k :=t;
      if isZero (res.matrix[k , j])
        then begin
          dec (i);
          continue;
        end;
      if k <> i
        then begin
          res.LineOprSwap (i , k);
          D :=-D;
        end;
      D :=D * res.matrix[i , j];
      res.LineOprDivC (i , res.matrix[i , j]);
      for k :=1 to res.Rn do
        if (k <> i) and (res.matrix[k , j] <> 0)
          then begin
            res.LineOprAdd2 (k , i , -res.matrix[k , j]);
          end;
    end;
end; {OprD}


end.
