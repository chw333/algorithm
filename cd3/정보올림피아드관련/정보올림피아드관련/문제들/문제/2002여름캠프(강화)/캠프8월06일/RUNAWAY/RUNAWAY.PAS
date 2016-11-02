{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 65000,0,655360}
const dx:array[1..4] of shortint=(-1,0,0,1);
      dy:array[1..4] of shortint=(0,-1,1,0);
      infile:='runaway.in';
      outfile:='runaway.out';
var a:array[0..51,0..51] of char;
    v,nrdf,p:array[1..50,1..50] of integer;
    is:array[1..50,1..50] of boolean;
    i,j,k,l,n,ndf,np,ax,ay,nis:integer;
    f:text;

procedure citeste;
begin
     fillchar(a,sizeof(a),'W');
     assign(f,infile);reset(f);
     read(f,n);
     read(f,ax,ay);
     for i:=1 to n do
         for j:=1 to n do begin
             if seekeof(f) then;
             read(f,a[j,n-i+1]);
         end;
     close(f);
end;

procedure trace(x,y:byte);
var i,nx,ny:byte;
begin
     inc(ndf);nrdf[x,y]:=ndf;v[x,y]:=ndf;
     for i:=1 to 4 do begin
         nx:=x+dx[i];ny:=y+dy[i];
         if a[nx,ny]<>'W' then
            if nrdf[nx,ny]=0 then begin
               trace(nx,ny);
               if v[nx,ny]<v[x,y] then v[x,y]:=v[nx,ny] else
               if (a[x,y]='D') and (v[nx,ny]>=nrdf[x,y]) and (nrdf[ax,ay]>=nrdf[nx,ny])
               and (p[ax,ay]<=p[nx,ny]) then is[x,y]:=true
            end else if nrdf[nx,ny]<v[x,y] then v[x,y]:=nrdf[nx,ny];
     end;
     inc(np);p[x,y]:=np;
end;

procedure rezolva;
begin
     for i:=1 to n do
         for j:=1 to n do if a[i,j]='E' then begin
             trace(i,j);
             break
         end;
     if nrdf[ax,ay]=0 then
        for i:=1 to n do
            for j:=1 to n do is[i,j]:=a[i,j]='D';
     for i:=1 to n do
         for j:=1 to n do if is[i,j] then inc(nis);
end;

procedure scrie;
begin
     assign(f,outfile);rewrite(f);
     if nis=0 then writeln(f,'NO') else begin
        writeln(f,'YES');
        writeln(f,nis);
        for i:=1 to n do
            for j:=1 to n do if is[i,j] then writeln(f,i,' ',j);
     end;
     close(f);
end;

begin
     citeste;
     rezolva;
     scrie
end.