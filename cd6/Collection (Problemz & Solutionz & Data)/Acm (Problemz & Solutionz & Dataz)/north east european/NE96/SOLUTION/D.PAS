{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи "Один DEL"}

{$A-,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}

program DEL;
const maxN = 1000;
      Blanks = [' ', #13, #10];
type TNameList = array [1..MaxN] of string [8];
     TFileList = record names, exts: TNameList;
                 end;

var F: array [0..1] of TFileList;
    N: array [0..1] of integer;
    inf, ouf: TEXT;

function CreateMask (L: TNameList; N: integer): string;
var s: string;
    i, j: integer;
    same_char, one_end, all_end: boolean;
begin
   s := '';
   for i := 1 to 8 do
   begin
      same_char := true; all_end := true; one_end := false;
      for j := 1 to N do
        if length (L[j]) < i then one_end := true
        else if length (L [j]) >= i then
        begin
           all_end := false;
           if j > 1 then same_char := same_char and (copy (L[j-1],i,1) = L[j][i]);
        end;

      if all_end {для случая, когда N = 0} or one_end then
      begin
         if not all_end then s := s + '*';
         CreateMask := s;
         exit
      end;

      if same_char then s := s + L [j] [i] else s := s + '?';
   end;
   CreateMask := s;
end;

function Fit (s, mask: string): boolean;
var i: integer;
begin
   Fit := True;
   for i := 1 to length (mask) do
     if mask [i] = '*' then exit
     else if (i > length (s)) or ((mask [i] <> '?') and (mask [i] <> s [i]))
     then begin
        Fit := false;
        exit
     end;
   Fit := length (s) = length (mask);
end;

VAR Flag, FName, FExt, help: string;
    point, x, i: integer;
    Mask_Ext, Mask_Name: string;
    NoAnswer: boolean;

BEGIN
   assign (inf, 'INPUT.TXT');  reset (inf);
   assign (ouf, 'OUTPUT.TXT'); rewrite (ouf);

   while not eof (inf) do
   begin
      readln (inf, help);
      if help [1] = '+' then x := 1 else x := 0;
      point := pos ('.', help);
      if point = 0 then point := length (help)+1;
      inc (N [x]);
      F [x]. names [N[x]] := copy (help, 2, point-2);
      F [x]. exts  [N[x]] := copy (help, point+1, 255);
   end;

   Mask_Name := CreateMask (F [0].names, N [0]);
   Mask_Ext   := CreateMask (F [0].exts, N [0]);

   NoAnswer := false;
   for i := 1 to N [1] do
     NoAnswer := NoAnswer or (Fit (F [1] . names [i], Mask_name) and Fit (F [1] . exts [i], Mask_Ext));

   if NoAnswer then writeln (ouf, 'IMPOSSIBLE')
               else writeln (ouf, 'DEL ' + Mask_Name + '.' + Mask_Ext);

   close (ouf);
   close (inf);
END.
