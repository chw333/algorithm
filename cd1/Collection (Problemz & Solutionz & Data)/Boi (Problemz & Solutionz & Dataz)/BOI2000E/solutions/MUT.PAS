{ üç sprendimÖ paraûÇ uëdavinio autoriai iû Esijos }

const
 MAX_THREAD_COUNT = 5;
 MAX_THREAD_LENGTH = 10;
 STATE_MAP_LENGTH = 25000;

 INPUT_FILE = 'MUT.IN';
 OUTPUT_FILE = 'MUT.OUT';


type
 MutexName = 'A' .. 'Z';

 OpType = ( LOCK, UNLOCK );

 Operation = record
                   typ : OpType;
                   mutex : MutexName;
             end;

 Thread = record
                count : integer;
                ops : array[0 .. MAX_THREAD_LENGTH-1] of Operation;
          end;

 State = array[1 .. MAX_THREAD_COUNT] of integer;


var
   t_cnt : integer;
   prg : array[1 .. MAX_THREAD_COUNT] of Thread;


   powers : array[1 .. MAX_THREAD_LENGTH] of longint;
   final_state_index : longint;

   current_state : State;
   state_index : longint;
   mutex_map : array[MutexName] of boolean;

   state_map : array[0 .. STATE_MAP_LENGTH] of byte;

   found_deadlock : boolean;
   deadlock_state : State;



procedure LoadData;
var
   f:text;
   i,j:integer;
   s:string;
begin
     assign(f, INPUT_FILE);
     reset(f);
     readln(f, t_cnt);

     for i:= 1 to t_cnt do
     begin
          readln(f, prg[i].count);

          for j:= 0 to prg[i].count-1 do
          begin
               readln(f, s);

               if (s[1] = 'L') then
                    prg[i].ops[j].typ := LOCK
               else
                    prg[i].ops[j].typ := UNLOCK;

               prg[i].ops[j].mutex := s[length(s)];
          end;
     end;

     close(f);
end;



procedure InitStateMap;
var
   l : integer;
   d : longint;
begin
     fillchar(state_map, sizeof(state_map), 0);

     d := 1;
     final_state_index := 0;

     for l := 1 to t_cnt do
     begin
          powers[l] := d;

          inc(final_state_index, prg[l].count * powers[l]);

          d := d * (MAX_THREAD_LENGTH + 1);
     end;
end;


procedure MarkStateVisited(i:longint);
begin
     state_map[i div 8] := state_map[i div 8] or (1 shl (i mod 8));
end;


function GetStateVisited(i:longint) : boolean;
begin
     GetStateVisited := (state_map[i div 8] and (1 shl (i mod 8))) <> 0;
end;


procedure Search;
var
   op : Operation;
   was : boolean;
   l : integer;
begin
     if (GetStateVisited(state_index)) then exit;
     MarkStateVisited(state_index);

     if (state_index = final_state_index) then exit;

     was := false;

     for l:=1 to t_cnt do
     if (current_state[l] < prg[l].count) then
     begin
          op := prg[l].ops[current_state[l]];

          if ((op.typ = LOCK) and not(mutex_map[op.mutex])) or
             (op.typ = UNLOCK) then
          begin
               inc(state_index, powers[l]);
               inc(current_state[l]);
               mutex_map[op.mutex] := not mutex_map[op.mutex];

               Search;

               mutex_map[op.mutex] := not mutex_map[op.mutex];
               dec(current_state[l]);
               dec(state_index, powers[l]);

               was := true;
          end;
     end;


     if (not was) and (not found_deadlock) then
     begin
          found_deadlock := true;
          deadlock_state := current_state;
     end;
end;


procedure PerformSearch;
var
   l : integer;
begin
     InitStateMap;

     for l := 1 to t_cnt do current_state[l] := 0;
     state_index := 0;

     fillchar(mutex_map, sizeof(mutex_map), 0);

     found_deadlock := false;

     Search;
end;

procedure WriteData;
var
   f : text;
   l : longint;
begin
     assign(f, OUTPUT_FILE);
     rewrite(f);

     if (not found_deadlock) then
     begin
          writeln(f, 0);
          close(f);
          exit;
     end;

     writeln(f, 1);

     for l:=1 to t_cnt do
      if (deadlock_state[l] <> prg[l].count) then
         write(f, deadlock_state[l], ' ')
      else
         write(f, -1, ' ');

     writeln(f);
     close(f);
end;

begin
     LoadData;
     PerformSearch;
     WriteData;
end.