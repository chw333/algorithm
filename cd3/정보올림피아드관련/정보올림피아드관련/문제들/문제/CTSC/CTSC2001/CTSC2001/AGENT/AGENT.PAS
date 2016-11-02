{$A+,B-,D-,E+,F-,G+,I-,L-,N+,P-,Q-,R-,S-,T-,V+,X+,Y-}
{$M 65520,0}

program agent;
uses dos;
{the original code of MaxReliablity function belongs to
  ACM Tsinghua Team Hurricane Graph Unit v0.1.0805   ShaoZheng

    Original Code of MinCost is from Cupid.pas of ZhangYiFei      }

const
  MaxNode=300+5;  { additional nodes for internal use }
  MaxCost=1e100;
  MaxFlowC=10000;
type
  TCost=extended;
  TFlow=integer;

  TLCost = array[1..MaxNode]of TCost;
  TLFlow = array[1..MaxNode]of TFlow;

  TGCost=array[1..MaxNode] of ^TLCost;
  TGFlow=array[1..MaxNode] of ^TLFlow;

var fin,fout:text;


Function Min(a,b:longint):longint;
begin
     if a<b then Min:=a else Min:=b;
end;

Function MaxReliability(NCount:integer;var Limit:TGFlow;var Cost:TGCost;
                        source,target:integer;var flow:TGFlow;var C:TCost):TFlow;
Var
  i,j,pre     :Integer;
  w           :TFlow;
  More        :Boolean;
  Len:array[1..MaxNode]of TCost;
  Path:array[1..MaxNode]of integer; {-MaxNode<=Path[i]<=MaxNode}
  Width:array[1..MaxNode]of TFlow;

  result:TFlow;

begin
  result:=0;
  repeat
    for i:=1 to NCount do
    begin
         Len[i]:=MaxCost;
         Path[i]:=source;
         Width[i]:=0;
    end;
    Len[source]:=0;                     {  0=-ln1 }
    Width[source]:=MaxFlowC;

    repeat
      More:=False;
      for i:=1 to NCount do
        if Width[i]>0 then
          for j:=1 to NCount do
            begin
              if Flow[i]^[j]<Limit[i]^[j] then
                begin
                  pre:=i;
                  c:=-ln(Cost[i]^[j]);      { x -> -ln(x)  }
                  w:=min(Width[i],Limit[i]^[j]-Flow[i]^[j]);
                  if (Len[i]+c<Len[j]-len[j]/10000000) then
                    begin Len[j]:=Len[i]+c;Path[j]:=pre;Width[j]:=w;More:=True;end;
                end;
              if Flow[j]^[i]>0 then
                begin
                  pre:=-i;
                  c:=ln(Cost[j]^[i]);
                  w:=min(Width[i],Flow[j]^[i]);
                  if (Len[i]+c<Len[j]-len[j]/10000000) then
                    begin Len[j]:=Len[i]+c;Path[j]:=pre;Width[j]:=w;More:=True;end;
                end;
            end;
    until not More;
    if Width[target]=0 then break;
    w:=Width[target];
    result:=result+w;
    pre:=target;
    repeat
      i:=pre;pre:=Abs(Path[i]);
      if Path[i]>0 then Flow[pre]^[i]:=Flow[pre]^[i]+w else Flow[i]^[pre]:=Flow[i]^[pre]-w;
    until pre=source;  {original code is "i=source" }
  until False;
  C:=1;
  for i:=1 to NCount do
    for j:=1 to NCount do
    if flow[i]^[j]>0 then
         C:=C*exp(Flow[i]^[j]*ln(Cost[i]^[j]));
  MaxReliability:=result;
end;

procedure init;
begin
     assign(fin,'agent.in');
     reset(fin);
     assign(fout,'agent.out');
     rewrite(fout);
end;


var n,k:integer;
    reliability:extended;

procedure work;
var i,j:integer;
    limit,flow:TGFlow;
    cost:TGCost;
begin
     readln(fin,n,k);
     for i:=1 to n+3 do
     begin
          new(limit[i]);  fillchar(limit[i]^,sizeof(TLFlow),0);
          new(flow[i]);   fillchar(flow[i]^,sizeof(TLFlow),0);
          new(cost[i]);   fillchar(cost[i]^,sizeof(TLCost),0);
     end;
     for j:=2 to n+1 do  read(fin,cost[1]^[j]);
     for j:=2 to n+1 do  read(fin,limit[1]^[j]);

     for j:=2 to n+1 do
     begin
          read(fin,limit[j]^[n+2]);
          if limit[j]^[n+2]=1 then
          begin limit[j]^[n+2]:=k; cost[j]^[n+2]:=1; end;
     end;

     read(fin,i,j);
     while (i<>-1) do
     begin
          inc(i);       inc(j);
          read(fin,cost[i]^[j]);
          read(fin,limit[i]^[j]);
          cost[j]^[i]:=cost[i]^[j];
          limit[j]^[i]:=limit[i]^[j];
          read(fin,i,j);
     end;

     limit[n+2]^[n+3]:=k;  cost[n+2]^[n+3]:=1;

     if MaxReliability(n+3,limit,cost,1,n+3,flow,reliability)<k then
        reliability:=2;
end;

procedure over;
var ps:string;
    i,s,k:integer;
    d:extended;
begin
     if reliability>1 then writeln(fout,0)
     else
     begin
          d:=0.1;
          str(reliability:0:20,ps);
          i:=3;
          while ps[i]='0' do begin inc(i); d:=d/10; end;
          val(copy(ps,1,i+4),reliability,k);
          if ps[i+5]>='5' then
             reliability:=reliability+d/10000;
          writeln(fout,reliability:0:i+2);
          close(fin);
     end;
     close(fout);
end;

var hour,m,s,s100:word;
    _hour,_m,_s,_s100:word;

begin
     init;

     GetTime(hour,m,s,s100);

     work;

     GetTime(_hour,_m,_s,_s100);
     writeln(((longint(_m)-m)*60+_s-s)+(longint(_s100)-s100)/100:0:2);

     over;
end.
