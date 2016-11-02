const
  blank=[' ',#10,#13,#26];

type
  Ttext1=array[0..1023] of char;
  Ttext=array[0..200] of ^Ttext1;
  arr=array[1..10000] of integer;

var
  len:array[1..10000] of byte;
  start:array[1..10000] of longint;
  dic:Ttext;
  first,text,next,last:^arr;
  st1,st2,st:string;
  dics,index,l1,l2,x1,x2,x3,now:longint;

procedure initialize;
var
  i,j,used,dlast,templ,po:longint;
  ch:char;
  found:boolean;
begin
  for i:=0 to 200 do new(dic[i]);
  new(first); fillchar(first^,sizeof(first^),0);
  new(text); fillchar(text^,sizeof(text^),0);
  new(next); fillchar(next^,sizeof(next^),0);
  new(last); fillchar(last^,sizeof(last^),0);
  index:=0;
  dics:=0;
  used:=0;
  dlast:=0;

  assign(input,'sample.txt');
  reset(input);
  while not seekeof(input) do
    begin
      inc(index);

      read(ch);
      templ:=0;
      st:='';
      repeat
        inc(templ);
        st:=st+ch;
        read(ch);
      until (ch=' ') or eof(input);
      if not (ch in blank) then st:=st+ch;
      found:=false;
      for i:=1 to dics do
        if len[i]=templ then
          begin
            found:=true;
            po:=start[i];
            for j:=1 to templ do
              begin
                inc(po);
                if st[j]<>dic[po shr 10]^[po and 1023] then begin found:=false; break; end;
              end;
            if found then
              begin
                text^[index]:=i;
                next^[last^[i]]:=index;
                last^[i]:=index;
                break;
              end;
          end;
      if not found then
        begin
          inc(dics);
          start[dics]:=dlast;
          len[dics]:=templ;
          for i:=dlast+1 to dlast+templ do
            dic[i shr 10]^[i and 1023]:=st[i-dlast];
          text^[index]:=dics;
          last^[dics]:=index;
          first^[dics]:=index;
          dlast:=dlast+templ;
        end;
    end;
  close(input);
end;

procedure solve;
var
  r,n,i,j,po:longint;
  ch:char;
  found:boolean;
begin
  assign(input,'markov.in');
  reset(input);
  assign(output,'markov.ou1');
  rewrite(output);

  readln(n);
  for r:=1 to n do
    begin
      st1:=''; st2:='';
      read(ch);
      repeat
        st1:=st1+ch;
        read(ch);
      until ch=' ';
      readln(st2);
      while st1[1] in blank do delete(st1,1,1);
      while st2[1] in blank do delete(st2,1,1);
      while st1[length(st1)] in blank do delete(st1,length(st1),1);
      while st2[length(st2)] in blank do delete(st2,length(st2),1);

      l1:=length(st1);
      {pickup st1}
      found:=false;
      for i:=1 to dics do
        if len[i]=l1 then
          begin
            found:=true;
            po:=start[i];
            for j:=1 to l1 do
              begin
                inc(po);
                if st1[j]<>dic[po shr 10]^[po and 1023] then begin found:=false; break; end;
              end;
            if found then begin x1:=i; break; end;
          end;
      if not found then begin writeln; continue; end;
      l2:=length(st2);
      {pickup st2}
      found:=false;
      for i:=1 to dics do
        if len[i]=l2 then
          begin
            found:=true;
            po:=start[i];
            for j:=1 to l2 do
              begin
                inc(po);
                if st2[j]<>dic[po shr 10]^[po and 1023] then begin found:=false; break; end;
              end;
            if found then begin x2:=i; break; end;
          end;
      if not found then begin writeln; continue; end;

      now:=first^[x1];
      found:=false;
      repeat
        if (text^[now+1]=x2) and (now+1<index) then
          begin
            if found then write(' ') else found:=true;
            x3:=text^[now+2];
            for i:=start[x3]+1 to start[x3]+len[x3] do write(dic[i shr 10]^[i and 1023]);
          end;
        now:=next^[now];
      until now=0;
      writeln(' ');
    end;
  close(input);
  close(output);
end;

begin
  initialize;
  solve;
end.
