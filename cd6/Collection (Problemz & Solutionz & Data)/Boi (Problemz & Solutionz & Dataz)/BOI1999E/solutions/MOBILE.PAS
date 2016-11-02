{$R-,S-,Q-,M 65520,0,655360,B-}
var
  n,bars:integer;
  tnbars,nbar:array[1..17]of integer;
  tbar,bar:array[1..17,1..17] of record
                                   no,ceof:integer;
                                 end;
  guide:array[1..40]of record
                         no,bno:integer;
                       end;
  used:array[1..17]of boolean;
  v:array[1..17]of integer;
  gn:integer;
procedure readin;
  var s:string;
      ch:char;
      nowbars,err,i,lastn:integer;
  begin
    inc(bars);
    nbar[bars]:=0;
    nowbars:=bars;
    repeat
      s:='';
      repeat
        read(ch);
        if ch in ['0'..'9','-'] then s:=s+ch;
      until not (ch in ['0'..'9','-']);
      lastn:=n+1;
      if ch='(' then begin
         readin;
         read(ch);
      end else inc(n);
      for i:=lastn to n do begin
        inc(nbar[nowbars]);
        val(s,bar[nowbars,nbar[nowbars]].ceof,err);
        bar[nowbars,nbar[nowbars]].no:=i;
      end;
    until ch=')';
  end;
procedure init;
  var ch:char;
  begin
    read(ch);
    n:=0;
    bars:=0;
    readin;
  end;
procedure delete(bno,no:integer);
  var i,p:integer;
  begin
    p:=1;
    while (p<=tnbars[bno]) and (tbar[bno,p].no<>no) do inc(p);
    if p<=tnbars[bno] then begin
       dec(tnbars[bno]);
       for i:=p to tnbars[bno] do tbar[bno,i]:=tbar[bno,i+1];
    end;
  end;
procedure makeguide;
  var i,j,k,min,minno:integer;
  begin
    tnbars:=nbar;
    tbar:=bar;
    gn:=0;
    for i:=1 to bars do begin
      min:=n+1;
      for j:=1 to bars do if tnbars[j]<min then begin
        min:=tnbars[j];
        minno:=j;
      end;
      if min=0 then begin
         inc(gn);
         guide[gn].bno:=minno;
         guide[gn].no:=n+1;
         tnbars[minno]:=n+1;
         continue;
      end;
      for j:=1 to min-1 do begin
        inc(gn);
        guide[gn].no:=tbar[minno,j].no;
        guide[gn].bno:=0;
        for k:=1 to bars do if k<>minno then
          delete(k,tbar[minno,j].no);
      end;
      inc(gn);
      guide[gn].no:=tbar[minno,min].no;
      guide[gn].bno:=minno;
      for k:=1 to bars do if k<>minno then 
        delete(k,tbar[minno,min].no);
      tnbars[minno]:=n+1;
    end;
  end;
procedure printout;
  var ch:char;
      s:string;
      count:integer;
  begin
    count:=0;
    reset(input);
    while not eoln do begin
      read(ch);
      if ch in ['-','0'..'9']
         then begin
                s:=ch;
                repeat
                  read(ch);
                  if ch in ['-','0'..'9'] then s:=s+ch;
                until not (ch in ['-','0'..'9']);
                if ch<>'(' then begin
                   inc(count);
                   write(v[count]);
                end;
                write(ch);
              end
         else write(ch);
    end;
    writeln;
  end;
procedure run(lev:integer);
  var ceof,i,sum:integer;
  begin
    if lev>gn then begin
       printout;
       close(input);
       close(output);
       halt(0);
    end;
    if guide[lev].no=n+1 then begin
               sum:=0;
               for i:=1 to nbar[guide[lev].bno] do
                 sum:=sum+bar[guide[lev].bno,i].ceof * 
                      v[bar[guide[lev].bno,i].no];
               if sum<>0 then exit;
               run(lev+1);
             end else
    if guide[lev].bno<>0 then begin
       sum:=0;
       for i:=1 to nbar[guide[lev].bno] do
         if bar[guide[lev].bno,i].no=guide[lev].no
            then ceof:=bar[guide[lev].bno,i].ceof
            else sum:=sum+bar[guide[lev].bno,i].ceof * 
                      v[bar[guide[lev].bno,i].no];
       if (sum mod ceof <> 0) or (-sum div ceof<=0) or
          (-sum div ceof>n) or used[-sum div ceof] then exit;
       v[guide[lev].no]:=-sum div ceof;
       used[v[guide[lev].no]]:=true;
       run(lev+1);
       used[v[guide[lev].no]]:=false;
    end else begin
       for i:=1 to n do if not used[i] then begin
         v[guide[lev].no]:=i;
         used[i]:=true;
         run(lev+1);
         used[i]:=false;
       end
    end
  end;
procedure main;
  begin
    makeguide;
    fillchar(used,sizeof(used),0);
    run(1);
  end;
begin
  assign(input,'mobile.in');
  reset(input);
  assign(output,'mobile.out');
  rewrite(output);
  init;
  main;
  close(input);
  close(output);
end.