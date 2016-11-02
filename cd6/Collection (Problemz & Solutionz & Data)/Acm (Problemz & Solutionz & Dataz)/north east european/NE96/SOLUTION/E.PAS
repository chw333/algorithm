{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи "КРАТЧАЙШИЙ ПУТЬ"}

{$A-,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}

program shortest_way;

var l,w,h,
    x1,y1,z1,
    x2,y2,z2,
    r: longint;
    inout: text;

procedure swap (var x,y: longint);
   var t: longint;
   begin
       t:=x; x:=y; y:=t
   end;

procedure turn (i,j: integer; x,y,z,x0,y0,l,w,h: longint);
   var rr: longint;
   begin
    if z=0
    then { вторая точка попала в плоскость }
      begin
         rr:=x*x+y*y;
         if rr<r
         then r:=rr
      end
    else
      begin
        if (i>=0) and (i<2)
        then turn(i+1,j,x0+l+z,y,x0+l-x,x0+l,y0,h,w,l);
        if (j>=0) and (j<2)
        then turn(i,j+1,x,y0+w+z,y0+w-y,x0,y0+w,l,h,w);
        if (i<=0) and (i>-2)
        then turn(i-1,j,x0-z,y,x-x0,x0-h,y0,h,w,l);
        if (j<=0) and (j>-2)
        then turn(i,j-1,x,y0-z,y-y0,x0,y0-h,l,h,w)
      end
   end;

begin
    assign(inout,'input.txt');
    reset(inout);
    read(inout, l,w,h,x1,y1,z1,x2,y2,z2);
    close(inout);

    if (z1<>0) and (z1<>h) then
       begin
          if (y1=0) or (y1=w)
          then begin swap(y1,z1); swap(y2,z2); swap(w,h) end
          else begin swap(x1,z1); swap(x2,z2); swap(l,h) end
       end;
    if z1=h then
       begin z1:=0; z2:=h-z2 end;
    { теперь первая точка в плоскости Oxy }

    r:=maxlongint;
    turn(0,0,x2-x1,y2-y1,z2,-x1,-y1,l,w,h);

    assign(inout,'output.txt');
    rewrite(inout);
    writeln(inout,r);
    close(inout)
end.
