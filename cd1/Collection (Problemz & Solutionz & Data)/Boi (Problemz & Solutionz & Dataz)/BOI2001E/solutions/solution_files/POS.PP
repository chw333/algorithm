{***************************}
{* Task: Postman           *}
{* Tomasz Walen            *}
{* Warsaw, 2001.05.25      *}
{***************************}
{$I+,$R+}
program postman;
const
   f_in	 = 'pos.in';
   f_out = 'pos.out';
   maxn	 = 200;
   maxm	 = maxn*8;
type
   plist = ^tlist;
   tlist = record
	      v	 : integer;
	      n	 : plist;
	      no : integer;
	   end;	 
var 
   f	 : text;
   n,m	 : integer;
   g	 : array[1..maxn] of plist;
   w	 : array[1..maxn] of integer; {weights - not used!}
   e	 : array[1..maxm] of boolean; {used edges}
   s	 : array[1..maxm] of integer; {solution}
   s_len : integer;

procedure add_edge(var l : plist;x:integer;no:integer);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=x;
   tmp^.n:=l;
   tmp^.no:=no;
   l:=tmp;
end;

procedure read_data;
var
   i   : integer;
   a,b : integer;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,n,m);
   for i:=1 to n do readln(f,w[i]);
   for i:=1 to m do begin
      readln(f,a,b);
      add_edge(g[a],b,i);
      add_edge(g[b],a,i);
   end;
   close(f);
end; { read_data }

procedure dfs(v	: integer);
var
   l : plist;
begin
   l:=g[v];
   while (l<>nil) do begin
      if (not e[l^.no]) then begin
	 e[l^.no]:=true;
	 dfs(l^.v);
      end;
      l:=l^.n;
   end;
   inc(s_len);
   s[s_len]:=v;
   { if s_len != m+1 then error }
end;

procedure solve;
begin
   s_len:=0;
   fillchar(e,sizeof(e),0);
   dfs(1);
end; { solve }

procedure write_answer;
var
   i : integer;
begin
   Assign(f,f_out);
   rewrite(f);
   Writeln(f,s_len-1);
   for i:=1 to s_len do begin
      Write(f,s[i]);
      if (i<s_len) then Write(f,' ');
   end;
   close(f);
end; { write_answer }

begin
   read_data;
   solve;
   write_answer;
end.
