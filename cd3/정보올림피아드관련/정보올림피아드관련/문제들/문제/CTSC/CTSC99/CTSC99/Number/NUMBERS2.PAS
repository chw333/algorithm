{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+}
{$M 65520,0,655360}
Program Numbers_Letters (input , output);
Const
  N                        = 5;
  Inputname                = 'h.in';
  outputname               = 'h.sam';
  Maxsize                  = 20;
  Oprs                     : string[4] = '+-*/';

Type
  TNumArr                  = array[1 .. N] of Longint;
  TExpr                    = string[255];
  TNode                    = record
                               Opr     : char;
                               Expr    : TExpr;
                               Res     : Longint;
                               Lp , Rp : Longint;
                               Next , Last : Longint;
                             end;
  TTree                    = array[0 .. Maxsize] of TNode;

Var
  DataN , DataP            : Longint;
  Infp , Outfp             : text;
  Num                      : TNumarr;
  Expected , BestAns       : Longint;
  BestExpr                 : TExpr;
  Tree                     : TTree;
  TN                       : Longint;
  Flag                     : TNumArr;
  Success                  : boolean;

Procedure Initialize;
var
  i , j                    : Longint;

Procedure SwapNum (var com1 , com2 : Longint);
var
  tmp                      : Longint;
begin
  tmp :=com1; com1 :=com2; com2 :=tmp;
end; {SwapNum}

begin
  for i :=1 to n do
    read (infp , num[i]);
  for i :=1 to n - 1 do
    for j :=i + 1 to n do
      if num[i] > num[j]
        then swapNum (num[i] , num[j]);
  readln (infp , expected);
  BestAns :=-1;
  Fillchar (Tree , sizeof(Tree) , 0);
  fillchar (Tn , sizeof(Tn) , 0);
  Fillchar (Flag , sizeof(Flag) , 0);
  Success :=False;
end; {initialize}

Procedure Calc  (FromP : Longint);
var
  i , j , k                : Longint;
  TryP , Tmp , NRes , Code : Longint;

Procedure ComputeAns (n1 , n2 : Longint; nopr : char; var ReAns , ReCode: Longint);
begin
  ReCode :=0;
  case nopr of
    '+' : reans :=n1 + n2;
    '-' : reans :=n1 - n2;
    '*' : reans :=n1 * n2;
    '/' : begin
            if n2 = 0
              then code :=1
              else if n1 mod n2 <> 0
                     then code :=2
                     else ReAns :=n1 div n2;
          end;
  end;
end; {ComputeAns}

Function ObeyRule (lopr , ropr ,nopr : char; lexpr , rexpr : TExpr) : Boolean;
begin
  ObeyRule :=True;
  if ((nopr in ['+' , '-']) and (ropr in ['#' , '*' , '/']))
    or ((nopr in ['*' , '/']) and (ropr in ['#' , '+' , '-']))
  then Begin
         if (((Nopr = '+') and (lopr in ['#' , '*' , '/']))
           or ((Nopr = '*') and (lopr in ['#' , '+' , '-'])))
           and (lexpr > rexpr)
           then ObeyRule :=False;
         if ((Nopr = '+') and (lopr = '-'))
           or ((Nopr = '*') and (lopr = '/'))
         then ObeyRule :=False;
       end
  else ObeyRule :=False;
end; {obeyRule}

begin
  if (Tree[FromP].last = 0) and (Tree[FromP].next = 0)
    then begin
{          writeln (Tree[Fromp].Expr);}
           if (Tree[FromP].Res <= Expected)
             and ((BestAns < 0) or (Tree[Fromp].Res > BestAns))
           then begin
                  BestAns :=Tree[Fromp].Res;
                  BestExpr :=Tree[Fromp].Expr;
                  if BestAns = Expected
                    then Success :=True;
                end;
         end
    else begin
           tryp :=Tree[FromP].last;
           if tryp = 0
             then tryp :=FromP;

           Inc (TN);
           While Tree[Tryp].next <> 0 do
             begin
               Tmp :=Tree[Tryp].next;
               For i :=1 to 4 do
                 if ObeyRule (Tree[Tryp].opr , Tree[Tmp].opr , oprs[i] ,
                              Tree[Tryp].expr , Tree[Tmp].expr)
                 then
                 begin
                   ComputeAns (Tree[Tryp].Res , Tree[Tmp].Res , oprs[i] , NRes , Code);
                   if Code = 0
                     then begin
                            With Tree[TN] do
                              begin
                                opr :=oprs[i];
                                Expr :='('+Tree[Tryp].Expr+oprs[i]+Tree[Tmp].expr+')';
                                Res :=NRes;
                                Lp :=Tryp; Rp :=Tmp;
                                Next :=Tree[Tmp].next;
                                Last :=Tree[Tryp].last;
                                Tree[Last].Next :=TN;
                                Tree[Next].Last :=TN;
                              end;
                            Calc (TN);
                            With Tree[TN] Do
                              begin
                                Tree[Next].Last :=Tmp;
                                Tree[Last].Next :=Tryp;
                                opr :=#0; Expr :='';
                                Res :=0; Lp :=0; Rp :=0;
                                next :=0; last :=0;
                              end;
                            if Success
                              then begin
                                     dec (Tn);
                                     exit;
                                   end;
                          end;
                 end;
               Tryp :=Tmp;
             end;
           Dec (TN);
         end;
end; {Calc}

Procedure Solve (Step : Longint);
Var
  i , j                    : Longint;
begin
  if step > N
    then begin
           Calc (1);
         end
    else begin
           for i :=1 to N do
             if (flag[i] = 0)
               and ((i = 1) or (flag[i - 1] = 1) or (num[i - 1] <> num[i]))
               then begin
                      flag[i] :=1;
                      inc (TN);
                      with Tree[TN] Do
                        begin
                          opr :='#';
                          Str (Num[i] , expr);
                          Res :=Num[i];
                          last :=Tn - 1;
                        end;
                      tree[Tn-1].next :=TN;

                      Solve (step + 1);

                      fillchar (Tree[TN] , sizeof(Tree[Tn]) , 0);
                      tree[tn-1].next:=0;
                      dec (TN);
                      flag[i] :=0;

                      if Success then exit;
                    end;
         end;
end; {Solve}

Procedure Printout;
begin
  writeln (outfp , BestAns , ' : ' + bestexpr);
end; {Printout}

Begin
  assign (infp , inputname); reset (infp);
  assign (outfp , outputname); rewrite (outfp);
  readln (infp , DataN);
  for DataP :=1 to DataN do
    begin
      Initialize;
      Solve (1);
      Printout;
    end;
  close (outfp);
  close (infp);
end. {main}