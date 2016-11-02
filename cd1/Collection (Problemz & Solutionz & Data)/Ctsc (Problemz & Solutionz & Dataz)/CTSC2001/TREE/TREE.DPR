{$A+,B-,C+,D+,E-,F-,G+,H+,I+,J+,K-,L+,M-,N+,O+,P+,Q-,R-,S-,T-,U-,V+,W-,X+,Y+,Z1}
{$MINSTACKSIZE $00004000}
{$MAXSTACKSIZE $01000000}
{$IMAGEBASE $00400000}
{$APPTYPE GUI}
program tree;

const
  iname='tree.in';
  oname='tree.out';
  AllCount=5*18*18;
  Error=maxint;
type
  Ta=array[0..3,0..AllCount+1] of integer;

var
  list:array[1..AllCount] of ^Ta;
  readlist:array[1..AllCount] of integer;
  neighbour:array[1..AllCount,1..3] of integer;
  n,count:integer;
procedure readfile;
var i,j:integer;
    t1,t2,t:integer;
    fin:text;
begin
{  n:=18;count:=4*n*n;
  randomize;
  For i:=1 to Count do readlist[i]:=i;
  For j:=1 to 3*count do
  begin
    t1:=random(count)+1;
    t2:=random(count)+1;
    t:=readlist[t1];readlist[t1]:=readlist[t2];readlist[t2]:=t;
  end;
  assign(fin,iname);
  rewrite(fin);
    writeln(fin,n);
    for i:=1 to count do writeln(fin,readlist[i]);
  close(fin);//数据生成}

  assign(fin,iname);
  reset(fin);
    readln(fin,n);
    count:=4*n*n;
    for i:=1 to count do readln(fin,readlist[i]);
  close(fin);
end;

procedure Init;
var i,j,k,l:integer;
    piece,line,place:integer;
    np,nx,nl,ny:integer;
begin
for i:=1 to Count do
  begin
    j:=0;k:=i;
    piece:=(k-1) div (n*n)+1;
    k:=k-(piece-1)*n*n;
    for l:=1 to n do
    begin
      if k>(l*2-1) then k:=k-(l*2-1)
      else
        begin
         line:=l;place:=k;
         break;
        end;
    end;
    inc(j);
    //up and down
    if odd(place) then
    begin
      if line<>n then
      begin
        nx:=(piece-1)*n*n+line*line+place+1;
        neighbour[readlist[i],j]:=readlist[nx];
      end
      else
      begin
        case piece of
          1:begin
              np:=4;
              nl:=(n*2-place+1) div 2 ;
              ny:=1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          2:begin
              np:=4;
              nl:=(place+1) div 2;
              ny:=nl*2-1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          3:begin
              np:=4;
              nl:=n;
              ny:=n*2-place;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          4:begin
              np:=3;
              nl:=n;
              ny:=n*2-place;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
        end;
      end
    end
    else
    begin
        nx:=(piece-1)*n*n+(line-2)*(line-2)+place-1;
        neighbour[readlist[i],j]:=readlist[nx];
    end;
    inc(j);
    //left
    if place<>1 then
    begin
      neighbour[readlist[i],j]:=readlist[i-1];
    end
    else
    begin
        case piece of
          1:begin
              np:=3;
              nl:=line;
              ny:=nl*2-1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          2:begin
              np:=1;
              nl:=line;
              ny:=nl*2-1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          3:begin
              np:=2;
              nl:=line;
              ny:=nl*2-1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          4:begin
              np:=1;
              nl:=n;
              ny:=(n-line)*2+1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
        end;
    end;

    inc(j);
    //right
    if place<>line*2-1 then
    begin
      neighbour[readlist[i],j]:=readlist[i+1];
    end
    else
    begin
        case piece of
          1:begin
              np:=2;
              nl:=line;
              ny:=1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          2:begin
              np:=3;
              nl:=line;
              ny:=1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          3:begin
              np:=1;
              nl:=line;
              ny:=1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
          4:begin
              np:=2;
              nl:=n;
              ny:=line*2-1;
              nx:=(np-1)*n*n+(nl-1)*(nl-1)+ny;
              neighbour[readlist[i],j]:=readlist[nx];
            end;
        end;
    end;
  end; //for i
for i:=1 to Count do
 begin
   new(list[i]);
   for j:=0 to 3 do for k:=0 to count+1 do
     begin
        list[i]^[j,k]:=0;
        if j<>0 then
        begin
          if (neighbour[i,j]=i) or  (k=i) then list[i]^[j,k]:=error;
          if (neighbour[i,j]>i) and (k>i) then list[i]^[j,k]:=error;
          if (neighbour[i,j]<i) and (k<i) then list[i]^[j,k]:=error;
        end;
     end;
   end;

end;

function search(nin,ain,other:integer):integer;
var i,j,l,r,ll,rr:integer;
    min,max:integer;
begin
  if list[nin]^[ain,other]>0  then
    begin
      search:=list[nin]^[ain,other];
      exit;
    end;
  if ain=0 then
  begin
    min:=0;max:=count+1;
  end
  else
  begin
    i:=neighbour[nin,ain];
    if i>other then begin max:=i;min:=other end
               else begin max:=other;min:=i end
  end;

  ll:=0;rr:=0;
  for i:=1 to 3 do
  begin
    l:=neighbour[nin,i];
    if l<nin then
    begin
       for j:=1 to 3 do if neighbour[l,j]=nin then break;
       list[l]^[j,min]:=search(l,j,min);
       if (list[l]^[j,min]<>error) and (list[l]^[j,min]>ll) then ll:=list[l]^[j,min];
    end;
  end;
  for i:=1 to 3 do
  begin
    r:=neighbour[nin,i];
    if r>nin then
    begin
       for j:=1 to 3 do if neighbour[r,j]=nin then break;
       list[r]^[j,max]:=search(r,j,max);
       if (list[r]^[j,max]<>error) and (list[r]^[j,max]>rr) then rr:=list[r]^[j,max];
    end;
  end;
  search:=ll+rr+1;
end;

procedure find;
var i:integer;
begin
  for i:=1 to count do
    begin
      list[i]^[0,count+1]:=search(i,0,count+1);
    end;
end;


procedure writeout;
var fout:text;
    i:integer;
    j:integer;
begin
  assign(fout,oname);
  rewrite(fout);
{  for i:=1 to count do
  begin
    writeln(fout,i,' ',neighbour[i,1],' ',neighbour[i,2],' ',neighbour[i,3],' ');
  end;  }
  j:=0;
  for i:=1 to count do
  begin
    if list[i]^[0,count+1]>j then j:=list[i]^[0,count+1];
  end;
  writeln(fout,j);
  close(fout);
end;

begin
  readfile;
  init;
  find;
  writeout;
end.
