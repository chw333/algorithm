program DigiLog;
{$APPTYPE CONSOLE}
uses
  SysUtils;

const
  maxCompKind = 5;
  inFile = 'digilog.in';
  outFile = 'digilog.out';
  maxCompNum = 15;

type
  Tcomponent = record
    amount: integer;
    ky00, ky01, ky11: word;
  end;
  Tstate = record
    case byte of
      0: (numForm: word);
      1: (setForm: set of 0..15);
  end;
  Tport = record
    kind: byte;
    inPort1, inPort2: integer;
    outState: Tstate;
  end;
  TportArr = array[1..maxCompNum]of Tport;

var
  n: integer;
  component: array[1..maxCompKind]of Tcomponent;
  CompNum: integer;
  aim: array[1..4]of Tstate;
  DiffAim: array[1..4]of Tstate;
  NofDAim: integer;
  ResultFound: boolean;
  ResultRec: TportArr;
  NofPort: byte;

procedure initialize;
  var
    f: text;
    i, j: integer;
    y00, y01, y11: byte;
    inNumForm: integer;
    temp: byte;
    flag: boolean;
  begin
    assignFile(f, inFile);
    reset(f);
    readln(f, n);
    CompNum:= 0;
    for i:= 1 to n do
      with component[i] do begin
        readln(f, amount, y00, y01, y11);
        inc(CompNum, amount);
        if y00 = 0 then ky00:= 0 else ky00:= high(word);
        if y01 = 0 then ky01:= 0 else ky01:= high(word);
        if y11 = 0 then ky11:= 0 else ky11:= high(word);
      end;
    fillchar(aim, sizeof(aim), 0);
    for i:= 0 to 15 do begin
      inNumForm:= 0;
      for j:= 0 to 3 do begin
        read(f, temp);
        inc(inNumForm, temp shl j);
      end;
      for j:= 1 to 4 do begin
        read(f, temp);
        if temp = 1 then include(aim[j].setForm, inNumForm);
      end;
    end;
    NofDAim:= 0;
    for i:= 1 to 4 do begin
      flag:= false;
      for j:= 1 to i - 1 do
        if aim[j].numForm = aim[i].numForm then begin
          flag:= true;
          break;
        end;
      if not flag then begin
        inc(NofDAim);
        DiffAim[NofDAim]:= aim[i];
      end;
    end;
    close(f);
  end;

procedure search;
  var
    done: array[1..4]of boolean; //signs indicating whether an aim finished
    doneNum: integer;            //number of finished aims
    port: TportArr;
    compLeft: array[1..maxCompKind]of byte;

  function checkAim(stp:integer; outState: Tstate): byte;
    var
      i: integer;
    begin
      result:= 0;
      for i:= 1 to NofDAim do
        if outState.numForm = DiffAim[i].numForm then begin
          done[i]:= true;
          inc(doneNum);
          result:= i;
          break;
        end;
    end;

  procedure initSearch;
    var
      i, j: integer;
    begin
      ResultFound:= false;
      fillchar(done, sizeof(done), false);
      doneNum:= 0;
      for i:= 1 to 4 do
        with port[i] do begin
          kind:= 0;
          inPort1:= 0; inPort2:= 0;
          outState.setForm:= [];
          for j:= 0 to 15 do
            if odd(j shr (i - 1)) then include(outState.setForm, j);
          checkAim(i, outState);
        end;
      for i:= 1 to n do compLeft[i]:= component[i].amount;
      NofPort:= CompNum + 1;
    end;

  procedure doSearch(step: integer; in1, in2: integer);
    var
      i, j, k: integer;
      lo: integer;
      op, op1, op2, nop1, nop2: word;
      opt: word;
      temp: byte;

    function occured(op: word): boolean;
      var
        i: integer;
      begin
        for i:= step - 1 downto 1 do
          if op = port[i].outState.numForm then begin
            result:= true;
            exit;
          end;
        result:= false;
      end;

    begin
      if doneNum = NofDAim then begin
        ResultFound:= true;
        ResultRec:= port;
        NofPort:= step - 5;
        exit;
      end;
      for i:= in1 to step - 1 do begin
        if i = in1 then lo:= in2 + 1 else lo:= 1;
        with port[step] do begin
          inPort1:= i;
          op1:= port[i].outState.numForm;
          nop1:= not op1;
        end;
        for j:= lo to i do begin
          with port[step] do begin
            inPort2:= j;
            op2:= port[j].outState.numForm;
            nop2:= not op2;
          end;
          for k:= 1 to n do
            if compLeft[k] > 0 then begin
              with component[k] do begin
                opt:= nop1 and nop2;
                op:= not opt or (ky00 and opt);
                opt:= op1 and nop2;
                op:= (not opt and op) or (ky01 and opt);
                opt:= nop1 and op2;
                op:= (not opt and op) or (ky01 and opt);
                opt:= op1 and op2;
                op:= (not opt and op) or (ky11 and opt);
              end;
              if occured(op) then continue;
              dec(compLeft[k]);
              with port[step] do begin
                kind:= k;
                outState.numForm:= op;
                temp:= checkAim(step, outState);
                if (step - 4 + NofDAim - doneNum < NofPort) then
                  doSearch(step + 1, i, j);
                if temp > 0 then begin
                  done[temp]:= false;
                  dec(doneNum);
                end;
              end;
              inc(compLeft[k]);
            end;
        end;
      end;
    end;

  begin
    initSearch;
    doSearch(5, 1, 0);
  end;

procedure printResult;
  var
    f: text;
    i, j: integer;
  begin
    assignFile(f, outFile);
    rewrite(f);
    if ResultFound then begin
      writeln(f, 'Yes');
      writeln(f, NofPort);
      for i:= 1 to NofPort do
        with ResultRec[4 + i] do
          writeln(f, i + 4, ' ', kind, ' ', inPort1, ' ', inPort2);
      for i:= 1 to 4 do
        for j:= 1 to NofPort + 4 do
          if aim[i].numForm = ResultRec[j].outState.numForm then begin
            write(f, j, ' ');
            break;
          end;
      writeln(f);
    end
    else writeln(f, 'No');
    close(f);
  end;

begin
  initialize;
  search;
  printResult;
end.