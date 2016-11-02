var f,g:text;
    va,wa,n,i,j,k,a,zp:byte;
    v,z,lowpt:array[1..100] of byte;
    e,t:array[1..100,1..100] of integer;
    ne:array[1..100] of byte;
    s:string;
    code:integer;

begin
  assign(f,'network.in');
  assign(g,'network.out');
  reset(f);
  rewrite(g);
  repeat
    readln(f,n);
    if n=0 then break;
    fillchar(v,sizeof(v),0);
    fillchar(e,sizeof(e),0);
    fillchar(t,sizeof(t),0);
    fillchar(z,sizeof(z),0);
    fillchar(ne,sizeof(ne),0);
    fillchar(lowpt,sizeof(lowpt),0);
    zp:=1;
    z[1]:=1;
    a:=0;
    repeat
      read(f,i);
      if i=0 then break;
      readln(f,s);
      repeat
        while s[1]<>' ' do delete(s,1,1);
        while s[1]=' ' do delete(s,1,1);
        k:=0;while (s[k]<>' ') and (k<=byte(s[0])) do inc(k);
        val(copy(s,1,k-1),j,code);
        inc(ne[i]);
        inc(ne[j]);
        e[i][ne[i]]:=j;
        e[j][ne[j]]:=i;
        if code<>0 then break;
      until k>=byte(s[0]);
    until false;
    v[1]:=1;
    lowpt[1]:=1;
    i:=1;
    repeat
      va:=z[zp];
      while (ne[va]<>0) and (t[va,e[va,ne[va]]]<>0)  do dec(ne[va]);
      if ne[va]=0 then begin
        dec(zp);
        if zp>0 then begin
          if lowpt[z[zp]]>lowpt[z[zp+1]] then lowpt[z[zp]]:=lowpt[z[zp+1]];
        end;
      end else begin
        wa:=e[va,ne[va]];
        {vynech h z e!!!}
        if v[wa]=0 then begin
          inc(zp);
          z[zp]:=wa;
          inc(i);
          lowpt[wa]:=i;
          v[wa]:=i;
          t[va,wa]:=1;
          t[wa,va]:=-1;
        end else begin
          if (lowpt[va]>v[wa]) then lowpt[va]:=v[wa];
          t[va,wa]:=-1;
          t[wa,va]:=-1;
        end;
      end;
    until zp=0;
    for i:=1 to n do for j:=1 to n do
      if (t[i,j]=1) and (1<v[i]) and (v[i]<=lowpt[j]) then begin
        inc(a);
        break;
      end;
    j:=0;
    for i:=2 to n do if t[1,i]=1 then inc(j);
    if j>=2 then inc (a);
    writeln(g,a);
  until false;
  close(f);
  close(g);
end.
