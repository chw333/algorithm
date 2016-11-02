{Programed by Grant Guo, Email: grantguo@iname.com}
{$M 65520,0,655360,R-}
const
  dd:array[1..4]of record x,y:shortint end
    =((x:0;y:1),(x:1;y:0),(x:1;y:1),(x:1;y:-1));
  inputfile='seq.inp';
  outputfile='seq.out';
var
  map:array[1..100,1..100]of integer;
  mark:array[1..100,1..100]of word;
  bestlen,bestsum,bestx,besty,bestd,n:integer;
  order:word;
procedure search(x,y,d:shortint);
  var sum,len,sx,sy:integer;
  begin
    sum:=0;
    len:=0;
    sx:=x;
    sy:=y;
    repeat
      inc(len);
      sum:=sum+map[x,y];
      mark[x,y]:=order;
      if sum>bestsum then begin
         bestx:=sx;
         besty:=sy;
         bestsum:=sum;
         bestlen:=len;
         bestd:=d;
      end;
      x:=x+dd[d].x;
      y:=y+dd[d].y;
      if (x<1) then x:=x+n;
      if (x>n) then x:=x-n;
      if (y<1) then y:=y+n;
      if (y>n) then y:=y-n;
    until (sum<0) or (mark[x,y]=order);
  end;
procedure init;
  var i,j:byte;
  begin
    assign(input,inputfile);
    reset(input);
    readln(n);
    for i:=1 to n do begin
      for j:=1 to n do read(map[i,j]);
      readln;
    end;
    close(input);
  end;
procedure main;
  var i,j,k:integer;
  begin
    bestsum:=-32768;
    fillchar(mark,sizeof(mark),0);
    order:=0;
    for i:=1 to n do
      for j:=1 to n do
        if map[i,j]>0 then
           for k:=1 to 4 do begin
             inc(order);
             search(i,j,k);
           end;
    assign(output,outputfile);
    rewrite(output);
    if bestsum<0 then writeln(0,' ',0)
                 else begin
                        writeln(bestlen,' ',bestsum);
                        for i:=1 to bestlen do begin
                          writeln(bestx,' ',besty);
                          bestx:=bestx+dd[bestd].x;
                          besty:=besty+dd[bestd].y;
                          if bestx<1 then inc(bestx,n);
                          if besty<1 then inc(besty,n);
                          if bestx>n then dec(bestx,n);
                          if besty>n then dec(besty,n);
                        end;
                      end;
    close(output);
  end;
begin
  init;
  main;
end.



