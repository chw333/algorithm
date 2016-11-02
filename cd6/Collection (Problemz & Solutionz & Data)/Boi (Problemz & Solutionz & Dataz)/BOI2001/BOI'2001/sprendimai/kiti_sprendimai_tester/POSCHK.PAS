{***************************}
{* Task: Postman           *}
{* Tomasz Walen            *}
{* Warsaw, 2001.05.25      *}
{***************************}
{ if outpt file consist some garbage at the end of the file but answer is
  correct then the result is OK }
{$I+,$R+}
program pos_checker;
const
   f_in		 = 'pos.in';
   f_out	 = 'pos.out';
   maxn		 = 200;
   maxm		 = maxn*8;
   white	 = [' ',#10,#13,#9];
   max_token_len = 30;
var
   f	: text;
   n,m	: integer;
   w	: array[1..maxn] of integer;
   deg	: array[1..maxn] of integer;
   g	: array[1..maxn,1..maxn] of integer;
   used	: array[1..maxn,1..maxn] of integer;


procedure error(code :string; msg : string);
begin
   Writeln(code);
   Writeln(msg);
   halt(1);
end; { error }

function get_token(var f : text):string;
var
   tmp : string;
   ch  : char;
   len : integer;
begin
   tmp:='';
   ch:=' ';
   while ((not eof(f)) and (ch in white)) do read(f,ch);
   if (not (ch in white)) then begin
      tmp:=ch;
      len:=1;
      while ((not eof(f))) and (not (ch in white)) do
      begin
	 if (len>=max_token_len) then break; 
	 read(f,ch);
	 if (not (ch in white)) then tmp:=tmp+ch;
	 inc(len);
      end;
   end else tmp:='EOF';
   get_token:=tmp;
end; { get_token }

function instr(v : longint):string;
var
   tmp : string;
begin
   str(v,tmp);
   instr:=tmp;
end;

procedure read_input;
var
   i	    : integer;
   a,b	    : integer;
   filename : string;
begin
   fillchar(g,sizeof(g),0);

   filename:=f_in;
   if (paramcount>0) then filename:=paramstr(1);
   
   Assign(f,filename);
   reset(f);
   readln(f,n,m);
   if (n<1) or (n>maxn) then error('ERROR','Bad n value');
   for i:=1 to n do readln(f,w[i]);
   fillchar(deg,sizeof(deg),0);
   for i:=1 to m do begin
      readln(f,a,b);
      if (a<1) or (a>n) then error('ERROR','Bad village number ('+instr(a)+')');
      if (b<1) or (b>n) then error('ERROR','Bad village number ('+instr(b)+')');      
      inc(g[a,b]);
      inc(g[b,a]);
      inc(deg[a]);
      inc(deg[b]);      
   end;
   close(f);
   for i:=1 to n do if not (deg[i] in [2,4,8]) then
      error('ERROR','Bad degree of vertex '+instr(i)+' - '+instr(deg[i]));
end; { read_input }

procedure check;
var
   i,j	    : longint;
   len	    : longint;
   prv,v    : longint;
   code	    : integer;
   s	    : string;
   filename : string;
begin
   filename:=f_out;
   if (paramcount>1) then filename:=paramstr(2);
   
   Assign(f,filename);
   reset(f);
   readln(f,len);
   prv:=1;
   for i:=1 to len+1 do begin
      s:=get_token(f);
      val(s,v,code);
      if (code<>0) then
	 error('WRONG ANSWER','Village number expected, but "'+s+'" found.');

      if (v<1) or (v>n) then
	 error('WRONG ANSWER','Bad village number: '+instr(v));
      
      if (i=1) and (v<>1) then
	 error('WRONG ANSWER','Bad solution, path should start with village number 1');
      if (i=len+1) and (v<>1) then
	 error('WRONG ANSWER','Bad solution, path should end with village number 1');

      if (i>1) and (g[prv,v]=0) then
	 error('WRONG ANSWER','No connection between villages ('+instr(prv)+','+
	       instr(v)+')');

      if (i>1) then begin
	 inc(used[prv,v]);
	 inc(used[v,prv]);
      end;

      prv:=v;
   end;
   {there is not checking garbage on the end of file}
   close(f);

   for i:=1 to n do
      for j:=1 to n do if used[i,j]<g[i,j] then
	 error('WRONG ANSWER','Road from '+instr(i)+' to '+instr(j)+' not visited');
   
   if (len<>m) then
      error('WRONG ANSWER','Solution is not optimal');
end;

begin
   read_input;
   check;
   
   Writeln('OK');
   halt(0);
end.