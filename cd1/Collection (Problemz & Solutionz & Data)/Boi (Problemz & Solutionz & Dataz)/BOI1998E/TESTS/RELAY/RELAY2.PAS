Program RELAY2;
Var STARTPROT, FINPROT, OUTPROT:Text;
    STARTED,FINISHED,RESULTNR,NUMBER,I:Integer;
    HASFINISHED:Array[200..299] of Boolean;
    FINISH:Array[200..299] of Array[1..3] of Integer;
    STARTHOUR,STARTMIN,STARTSEC:Integer;
    RESULT:Array[1..100] of Record NR,MINUTES,SECONDS:Integer; End;
    MI,SE,COUNT:Integer;
Begin {=====================Main================================}
Assign(OUTPROT,'RELAY2.OUT');
Rewrite(OUTPROT);
Assign(FINPROT,'FINISH.IN');
Reset(FINPROT);
For I:=200 to 299 Do HASFINISHED[I]:=False;
Readln(FINPROT,FINISHED);
For I:=1 to FINISHED Do
  Begin
  Read(FINPROT,NUMBER);
  If (NUMBER>200) and (NUMBER<300) {NB! ignores number 200}
    Then Begin
         HASFINISHED[NUMBER]:=True;
         Readln(FINPROT,FINISH[NUMBER,1],FINISH[NUMBER,2],FINISH[NUMBER,3])
         End
    Else Readln(FINPROT);
  End;
Close(FINPROT);

{Filling the table of results in order of (NB!) Start protocol}
Assign(STARTPROT,'START.IN');
Reset(STARTPROT);
Readln(STARTPROT,STARTED);
RESULTNR:=0;
COUNT:=0;
For I:=1 to STARTED Do
  Begin
  Read(STARTPROT,NUMBER);
  If (NUMBER>200) and (NUMBER<300) and HASFINISHED[NUMBER]
    Then Begin
         Readln(STARTPROT,STARTHOUR,STARTMIN,STARTSEC);
         If (STARTED>499) and (STARTHOUR<0) and (STARTMIN>300) Then
           COUNT:=COUNT+60;
         If STARTHOUR>FINISH[NUMBER,1]
           Then FINISH[NUMBER,1]:=FINISH[NUMBER,1]+24;
           {NB! The results 2:00.01 to 2:00.59 will not be disqualified}
         If (60*FINISH[NUMBER,1]+FINISH[NUMBER,2]
            -60*STARTHOUR-STARTMIN<=120) Then
           Begin
           RESULTNR:=RESULTNR+1;
           With RESULT[RESULTNR] Do
             Begin
             NR:=NUMBER;
             MINUTES:=60*FINISH[NUMBER,1]+FINISH[NUMBER,2]
                      -60*STARTHOUR-STARTMIN;
             SECONDS:=FINISH[NUMBER,3]-STARTSEC;
             If SECONDS<0
               Then SECONDS:=SECONDS+60; {NB! Does not correct MINUTES}
             End;
           End;
         End
    Else Readln(STARTPROT);
  If COUNT>499 Then Write(OUTPROT,'499');
  If count>499 Then Break;
  End;
Close(STARTPROT);

{Writing results}
For MI:=0 to 120 Do
  For SE:=0 to 59 Do
    For I:=1 to RESULTNR Do
      If (RESULT[I].MINUTES=MI) and (RESULT[I].SECONDS=SE) Then
        Writeln(OUTPROT,RESULT[I].NR
               { ,result[i].minutes:5,'.',result[i].seconds});
Close(OUTPROT);

End.
