{ This program is a tester for the 'String Matching' task. It must be
 run after the program tested finished its work. This tester reads in
 data from input file, output file, solves the task itself, and then
 compares its solution with the solution from output file.

  The idea using which this program solves the task:

  Imagine, that we try to build the string sought by concatenating strings
 in all possible ways. Now lets build both strings (the one, that is
 concatenation of strings from sequence A, and the one, that is
 concatenation of strings from sequence B) simultaneously so that always
 one of them is a prefix of another. Even more, the last string of the
 longer string must be partially covered by the prefix, that is equal to
 the shorter string. An example of legal pair could be:

            AAA+BBB+CCC
            AAAB+BBC

 An example of illegal pair coulde be:

            AAA+BBB+CCC
            AA+ABB

  It is obvious (hopefully), that if the string sought exists, then it can
 be 'grown' in such a way, that at each moment the pair of strings built
 is 'legal' (see above).
  In this program, the last string in the representation of the longer string
 is called protruding. Lets call the combination of information of which
 string in the pair is longer, which string is protruding and how many
 symbols of it are covered by the prefix 'the state of a pair'. Lets call
 the length of the longer string in the pair 'the distance of a pair'.
  It is obvious, that when 'growing' the string sought, the intermidiate
 string pairs cannot be twice in the same state (the string wouldn't be the
 shortest).
  It is also obvious, that if there are two pairs in the same state,
 then only one of them, with the smaller length, must be processed.
  All this means, that this task can be solved by searching the shortest
 path in the graph, the vertices of which are all possible states of pairs.
  This program does it with help of (simplified) Dijkstra algorithm.
}

{$I-}{$R+}{$Q+}{$S+}
{$M 65520, 0, 655360}

const
 INPUT_FILE = 'MATCH.IN';
 OUTPUT_FILE = 'MATCH.OUT';

const
 MaxN = 100;
 MaxK = 50;     {Maximum length of stings}
 MaxStateCount = 2 * MaxN * ( MaxK + 1 );

type
 XString = string[ MaxK ];
 StringCollection = array[ 1 .. MaxN ] of XString;
 PCollection = ^StringCollection;
 Representation = array[ 1 .. MaxStateCount ] of integer;
 PRepresentation = ^Representation;

const
 BLANK_CHAR  = #32;
 LINE_BREAK1 = #13;
 LINE_BREAK2 = #10;
 TAB_CHAR    = #9;

const
 SEPARATOR = '--------------------------------------------------------';
 IO_ERROR =
                        'ERROR: I/O error occured!';

 OUT_OF_MEMORY =
                        'ERROR: Out of memory!';

 WRONG_COLLECTION_SIZE =
                        'ERROR: The size of collection is wrong!';

 WRONG_CHAR_IN_INPUT =
                        'ERROR: Wrong character in input!';

 WRONG_SHORTEST_STRING_LENGTH =
                        'ERROR: Wrong length of shortest string!';

 TOO_MANY_STRINGS_IN_REPRESENTATION =
                        'ERROR: Too many strings in representation!';

 ZERO_LENGTH_STRING_IN_REPRESENTATION =
                        'ERROR: Zero-length string in representation!';

 STRING_IN_REPRESENTATION_DOES_NOT_EXIST =
                        'ERROR: String in representation does not exist!';

 WRONG_CHAR_IN_OUTPUT =
                        'ERROR: Wrong character in output!';

 MISSING_LINE_BREAK =
                        'ERROR: Missing line break in output!';

 TRASH_IN_THE_END_OF_FILE =
                        'ERROR: Trash in the end of file!';

 EMPTY_REPRESENTATION =
                        'ERROR: Representation is empty!';

 REPRESENTATIONS_DO_NOT_MATCH =
                        'ERROR: Representations do not match!';

 REPORTED_LENGTH_DOES_NOT_MATCH_REPRESENTATION =
                        'ERROR: Reported length of shortest string found does not match the length of representation!';

 INTERNAL_ERROR_IN_SOLVER =
                        'ERROR: Internal error in solver!';

 PROGRESS_READING_INPUT  =
                        'Reading input file...';

 PROGRESS_READING_OUTPUT =
                        'Reading output file...';

 PROGRESS_SOLVING_TASK =
                        'Solving the task...';

 PROGRESS_VERIFYING_SOLUTION =
                        'Verifying the solution...';

 SOLVER_IS_INCORRECT =
                        'ERROR: Solver is incorrect!';

 SOLUTIONS_LENGTH =
                        'The length of solution: ';

 TESTERS_SOLUTIONS_LENGTH =
                        'Tester''s solution''s length: ';

 RESULT_SOLUTION_ACCEPTED =
                        'RESULT: Solution ACCPETED!';

 RESULT_SOLUTION_NOT_ACCEPTED =
                        'RESULT: Solution NOT accepted!';


{Reads input data. Returns TRUE if successful.}
function readInput( inputFile : string;
                    var N, M : integer;
                    var collectionA, collectionB : PCollection
                    ):boolean;

function ensureRightCharacters( var s:XString ):boolean;
var
 i:integer;
begin
 ensureRightCharacters:= false;

 for i:=1 to length( s ) do
  if not( s[ i ] in ['A'..'Z'] ) then
  begin
   writeln( WRONG_CHAR_IN_INPUT );
   exit;
  end;

 ensureRightCharacters:= true;
end;

var
 f:text;
 l:integer;
begin
 readInput:= false;

 assign( f, inputFile );
 reset( f );
 if ( ioresult <> 0 ) then
 begin
  writeln( IO_ERROR );
  exit;
 end;

 readln( f, N );
 if ( ioresult <> 0 ) then
 begin
  writeln( IO_ERROR );
  exit;
 end;

 if ( N < 0 ) or ( N > MaxN ) then
 begin
  writeln( WRONG_COLLECTION_SIZE );
  exit;
 end;

 if ( sizeOf( StringCollection ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( collectionA );

 for l:=1 to N do
 begin
  readln( f, collectionA^[ l ] );
  if ( ioresult <> 0 ) then
  begin
   writeln( IO_ERROR );
   exit;
  end;

  if not( ensureRightCharacters( collectionA^[ l ] ) ) then exit;

 end;

 readln( f, M );
 if ( ioresult <> 0 ) then
 begin
  writeln( IO_ERROR );
  exit;
 end;

 if ( M < 0 ) or ( M > MaxN ) then
 begin
  writeln( WRONG_COLLECTION_SIZE );
  exit;
 end;

 if ( sizeOf( StringCollection ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( collectionB );

 for l:=1 to M do
 begin
  readln( f, collectionB^[ l ] );
  if ( ioresult <> 0 ) then
  begin
   writeln( IO_ERROR );
   exit;
  end;

  if not( ensureRightCharacters( collectionB^[ l ] ) ) then exit;

 end;

 close( f );

 readInput:= true;
end;

{Reads in output data. Returns TRUE if successful. Otherwise
 outputWrong is TRUE, if the output is wrong, and is FALSE otherwise
 (e.g. if I/O error occured).}
function readOutput( outputFile: string;
                     N,M: integer;
                     collectionA, collectionB: PCollection;
                     var shortestLength: longint;
                     var aLength, bLength: integer;
                     var representationA, representationB: PRepresentation;
                     var outputWrong: boolean;
                     var retCode: integer
                     ):boolean;
var
 f:text;
 l:integer;
 error: integer;
 ch: char;
 buffer: string;

 function readRepresentation( N : integer; collection: PCollection;
                          var representationLength:integer;
                          var representation: PRepresentation
                          ): boolean;

  function findIndex:integer;
  var l: integer;
  begin
   findIndex:= -1;

   if ( length( buffer ) < 1 ) or ( length( buffer ) > MaxK ) then exit;

   for l:=1 to N do
    if ( collection^[ l ] = buffer ) then
    begin
     findIndex:= l;
     exit;
    end;
  end;

  function appendBuffer:boolean;
  var index: integer;
  begin
    appendBuffer:= false;

    if ( length( buffer ) = 0 ) then
    begin
     writeln( ZERO_LENGTH_STRING_IN_REPRESENTATION );
     exit;
    end;

    index:= findIndex;

    if ( index = -1 ) then
    begin
     writeln( STRING_IN_REPRESENTATION_DOES_NOT_EXIST );
     exit;
    end;

    if ( representationLength = MaxStateCount ) then
    begin
     writeln( TOO_MANY_STRINGS_IN_REPRESENTATION );
     exit;
    end;

    inc( representationLength );

    representation^[ representationLength ]:= index;

    appendBuffer:= true;
  end;

 begin
  readRepresentation:= false;

  representationLength:= 0;
  buffer:= '';

  while not( eoln( f ) ) do
  begin
   read( f, ch );
   if ( ioresult <> 0 ) then
   begin
    outputWrong:=false;
    writeln( IO_ERROR );
    exit;
   end;

   if ( ch = '+' ) then
   begin
    if ( not( appendBuffer ) ) then exit;
    buffer:='';
   end
   else if ( ch in [ 'A' .. 'Z' ] ) then
        begin
         if ( length( buffer ) >= MaxK ) then
         begin
          writeln( STRING_IN_REPRESENTATION_DOES_NOT_EXIST );
          exit;
         end;

         insert( ch, buffer, length( buffer ) + 1 );
       end
       else
       begin
        writeln( WRONG_CHAR_IN_OUTPUT );
        exit;
       end;
  end;

  if ( not( appendBuffer ) ) then exit;

  readRepresentation:= true;
 end;

 function ensureLineBreak:boolean;
 var ch: char;
 begin
  ensureLineBreak:= false;

  if ( eof( f ) ) then
  begin
   writeln( MISSING_LINE_BREAK );
   exit;
  end;

  read( f, ch );

  if ( ioresult <> 0 ) then
  begin
   outputWrong:=false;
   writeln( IO_ERROR );
   exit;
  end;

  if ( ch <> char( LINE_BREAK1 ) ) then
  begin
   writeln( MISSING_LINE_BREAK );
   exit;
  end;

  if ( eof( f ) ) then
  begin
   writeln( MISSING_LINE_BREAK );
   exit;
  end;

  read( f, ch );

  if ( ioresult <> 0 ) then
  begin
   outputWrong:=false;
   writeln( IO_ERROR );
   exit;
  end;

  if ( ch <> LINE_BREAK2 ) then
  begin
   writeln( MISSING_LINE_BREAK );
   exit;
  end;

  ensureLineBreak:= true;
 end;

 function ensureEmptyEndOfFile:boolean;
 var ch: char;
 begin
  ensureEmptyEndOfFile:= false;

  while not( eof(f) ) do
  begin
   read( f, ch );
   if ( ioresult <> 0 ) then
   begin
    outputWrong:=false;
    writeln( IO_ERROR );
    exit;
   end;

   if ( not( ch in [ BLANK_CHAR, LINE_BREAK1, LINE_BREAK2, TAB_CHAR ] ) ) then
   begin
    writeln( TRASH_IN_THE_END_OF_FILE );
    exit;
   end;
  end;

  ensureEmptyEndOfFile:= true;
 end;

begin
 readOutput:= false;
 outputWrong:= true;

 if ( sizeOf(Representation) > maxAvail ) then
 begin
  outputWrong:=false;
  writeln( OUT_OF_MEMORY );
  retCode := 0;
  exit;
 end;
 new( representationA );

 if ( sizeOf(Representation) > maxAvail ) then
 begin
  outputWrong:=false;
  writeln( OUT_OF_MEMORY );
  retCode := 0;
  exit;
 end;
 new( representationB );

 assign( f, outputFile );
 reset( f );
 if ( ioresult <> 0 ) then
 begin
  outputWrong:=false;
  writeln( IO_ERROR );
  retCode := 1; { nav faila }
  exit;
 end;

 read( f, buffer );
 if ( ioresult <> 0 ) then
 begin
  outputWrong:=false;
  writeln( IO_ERROR );
  retCode := 2; { nepareizs fails }
  exit;
 end;

 val( buffer, shortestLength, error );
 if ( error <> 0 ) then
 begin
  writeln( WRONG_SHORTEST_STRING_LENGTH );
  retCode := 2;
  exit;
 end;

 if ( shortestLength = 0 ) then
 begin
  if ( not( ensureEmptyEndOfFile ) ) then begin retCode := 2; exit; end;

  outputWrong:= false;
  readOutput:= true;
  retCode := 0;
  exit;
 end;

 if ( not( ensureLineBreak ) ) then begin retCode := 2; exit; end;

 if ( not( readRepresentation( N, collectionA, aLength, representationA ) ) ) then
    begin
         retCode := 2;
         exit;
    end;

 if ( not( ensureLineBreak ) ) then begin retCode := 2; exit; end;

 if ( not( readRepresentation( M, collectionB, bLength, representationB ) ) ) then
    begin
         retCode := 2;
         exit;
    end;

 if ( not( ensureEmptyEndOfFile ) ) then begin retCode := 2; exit; end;

 outputWrong:= false;
 readOutput:= true;
end;

{Verifies solution to be correct. Returns TRUE, if the solution is correct.}
function verifySolution( N, M:integer;
                         collectionA, collectionB: PCollection;
                         shortestLength: longint;
                         aLength, bLength: integer;
                         representationA, representationB: PRepresentation
                         ):boolean;

function verifyAndUpdate( var protrudingString: XString;
                          coveredCount: integer;
                          var correspondingString: XString;
                          var isFirstProtrudingInResult:boolean;
                          var coveredCountInResult: integer ):boolean;
var
 l:integer;
begin

 l:=1;
 while (true) do
 begin

  if ( coveredCount + l > length( protrudingString ) ) then
  begin
   isFirstProtrudingInResult:= false;
   coveredCountInResult:= l - 1;
   verifyAndUpdate:= true;
   exit;
  end;

  if ( l > length( correspondingString ) ) then
  begin
   isFirstProtrudingInResult:= true;
   coveredCountInResult:= coveredCount + l - 1;
   verifyAndUpdate:= true;
   exit;
  end;

  if ( protrudingString[ coveredCount + l ] <>
       correspondingString[ l ] ) then
  begin
   verifyAndUpdate:= false;
   exit;
  end;

  inc( l );
 end;

end;

var
 isAProtruding: boolean;
 protrudingStringIndex: integer;
 correspondingStringIndex: integer;
 coveredCount: integer;
 processedA: integer;
 processedB: integer;
 tmp_IsProtruding: boolean;
 tmp_CoveredCount: integer;
 calculatedLength: longint;
 l:integer;

begin
 verifySolution:= false;

 if ( aLength < 1 ) or ( bLength < 1 ) then
 begin
  writeln( EMPTY_REPRESENTATION );
  exit;
 end;

 calculatedLength:= 0;
 for l:=1 to aLength do
  calculatedLength:= calculatedLength +
                     length( collectionA^[ representationA^[ l ] ] );

 if ( calculatedLength <> shortestLength ) then
 begin
  writeln( REPORTED_LENGTH_DOES_NOT_MATCH_REPRESENTATION );
  exit;
 end;

 isAProtruding:= true;
 protrudingStringIndex:= representationA^[ 1 ];
 coveredCount:= 0;

 processedA:=1;
 processedB:=0;

 while ( processedA < aLength ) or ( processedB < bLength ) do
 begin
  if ( isAProtruding ) then
  begin
   inc( processedB );

   if ( processedB > bLength ) then
   begin
    writeln( REPRESENTATIONS_DO_NOT_MATCH );
    exit;
   end;


   correspondingStringIndex:= representationB^[ processedB ];

   if ( not( verifyAndUpdate( collectionA^[ protrudingStringIndex ],
                              coveredCount,
                              collectionB^[ correspondingStringIndex ],
                              tmp_IsProtruding,
                              tmp_CoveredCount ) ) ) then
   begin
    writeln( REPRESENTATIONS_DO_NOT_MATCH );
    exit;
   end;

   if ( tmp_IsProtruding ) then
   begin
    {A is still protruding:}
    coveredCount:= tmp_CoveredCount;
   end
   else
   begin
    {Now B is protruding:}
    isAProtruding:= false;
    protrudingStringIndex:= correspondingStringIndex;
    coveredCount:= tmp_CoveredCount;
   end;
  end
  else
  begin
   inc( processedA );

   if ( processedA > aLength ) then
   begin
    writeln( REPRESENTATIONS_DO_NOT_MATCH );
    exit;
   end;

   correspondingStringIndex:= representationA^[ processedA ];

   if ( not( verifyAndUpdate( collectionB^[ protrudingStringIndex ],
                              coveredCount,
                              collectionA^[ correspondingStringIndex ],
                              tmp_IsProtruding,
                              tmp_CoveredCount ) ) ) then
   begin
    writeln( REPRESENTATIONS_DO_NOT_MATCH );
    exit;
   end;

   if ( tmp_IsProtruding ) then
   begin
    {B is still protruding:}
    coveredCount:= tmp_CoveredCount;
   end
   else
   begin
    {Now A is protruding:}
    isAProtruding:= true;
    protrudingStringIndex:= correspondingStringIndex;
    coveredCount:= tmp_CoveredCount;
   end;
  end;
 end;

 if ( isAProtruding ) then
  if ( length( collectionA^[ protrudingStringIndex ] ) <> coveredCount )
  then
  begin
   writeln( REPRESENTATIONS_DO_NOT_MATCH );
   exit;
  end;

 if ( not isAProtruding ) then
  if ( length( collectionB^[ protrudingStringIndex ] ) <> coveredCount )
  then
  begin
   writeln( REPRESENTATIONS_DO_NOT_MATCH );
   exit;
  end;

 verifySolution:= true;
end;

{Solves the task.}
function solve(  N, M: integer;
                 collectionA, collectionB: PCollection;
                 var shortestLength: longint;
                 var aLength, bLength: integer;
                 var representationA, representationB: PRepresentation
                 ):boolean;
const
 INFINITY = 2147483647;

type
 DataOnAddition = record
                   whichWasAdded: byte;{ 0, if A was added; 1 if B was assed }
                   addedIndex: integer;
                  end;
 BackReference = record
                  i: byte; { Either 0 or 1. Or 2 to mark first vertice.}
                  j, k: integer;
                 end;
 StateMap = array[ 0 .. 1, 1 .. MaxN, 0 .. MaxK ] of longint;
 PStateMap = ^StateMap;
 BackMap = array[ 0 .. 1, 1 .. MaxN, 0 .. MaxK ] of BackReference;
 PBackMap = ^BackMap;
 AddedMap = array[ 0 .. 1, 1 .. MaxN, 0 .. MaxK ] of DataOnAddition;
 PAddedMap = ^AddedMap;
 UsageMap = array[ 0 .. 1, 1 .. MaxN, 0 .. MaxK ] of boolean;
 PUsageMap = ^UsageMap;

var
 states: PStateMap;
 backRef: PBackMap;
 added: PAddedMap;
 used: PUsageMap;
 tmpRepresentation: PRepresentation;
 i,j,k,l: integer;
 min: longint;
 newI, newJ, newK: integer;
 currentI, currentJ, currentK: integer;

function tryStep( var protrudingString: XString;
                  coveredCount: integer;
                  var correspondingString: XString;
                  var isFirstProtrudingInResult:boolean;
                  var coveredCountInResult: integer ):boolean;
var
 l:integer;
begin

 l:=1;
 while (true) do
 begin

  if ( coveredCount + l > length( protrudingString ) ) then
  begin
   isFirstProtrudingInResult:= false;
   coveredCountInResult:= l - 1;
   tryStep:= true;
   exit;
  end;

  if ( l > length( correspondingString ) ) then
  begin
   isFirstProtrudingInResult:= true;
   coveredCountInResult:= coveredCount + l - 1;
   tryStep:= true;
   exit;
  end;

  if ( protrudingString[ coveredCount + l ] <>
       correspondingString[ l ] ) then
  begin
   tryStep:= false;
   exit;
  end;

  inc( l );
 end;

end;

procedure performSteps( fromI, fromJ, fromK: integer;
                        otherI: integer;
                        var protrudingString: XString;
                        otherN: integer;
                        otherCollection: PCollection
                        );
var
 l: integer;
 tmp_IsProtruding: boolean;
 tmp_CoveredCount: integer;
 newLength: longint;

begin

 for l:= 1 to otherN do
  if tryStep( protrudingString, fromK, otherCollection^[ l ],
              tmp_IsProtruding, tmp_CoveredCount ) then
  begin
       if ( tmp_IsProtruding ) then
       begin
          newLength:= states^[ fromI, fromJ, fromK ];

          if ( newLength < states^[ fromI, fromJ, tmp_CoveredCount ] ) then
          begin
           states^[ fromI, fromJ, tmp_CoveredCount ]:= newLength;
           backRef^[ fromI, fromJ, tmp_CoveredCount ].i:= fromI;
           backRef^[ fromI, fromJ, tmp_CoveredCount ].j:= fromJ;
           backRef^[ fromI, fromJ, tmp_CoveredCount ].k:= fromK;
           added^[ fromI, fromJ, tmp_CoveredCount ].whichWasAdded:= otherI;
           added^[ fromI, fromJ, tmp_CoveredCount ].addedIndex:= l;
          end;
       end
       else
       begin
          newLength:= states^[ fromI, fromJ, fromK ] +
                      length( otherCollection^[ l ] ) -
                      tmp_CoveredCount;

          if ( newLength < states^[ otherI, l, tmp_CoveredCount ] ) then
          begin
           states^[ otherI, l, tmp_CoveredCount ]:= newLength;
           backRef^[ otherI, l, tmp_CoveredCount ].i:= fromI;
           backRef^[ otherI, l, tmp_CoveredCount ].j:= fromJ;
           backRef^[ otherI, l, tmp_CoveredCount ].k:= fromK;
           added^[ otherI, l, tmp_CoveredCount ].whichWasAdded:= otherI;
           added^[ otherI, l, tmp_CoveredCount ].addedIndex:= l;
          end;
       end;
  end;
end;

procedure reverseRepresentation( var source: PRepresentation;
                                 var temp: PRepresentation;
                                 length: integer );
var
 l: integer;
 x: PRepresentation;
begin

 for l:= 1 to length do
  temp^[ l ]:= source^[ 1 + length - l ];

 x:= temp;
 temp:= source;
 source:= x;
end;

begin
 solve:= false;

 {Memory allocation:}
 if ( sizeOf( StateMap ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( states );

 if ( sizeOf( BackMap ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( backRef );

 if ( sizeOf( AddedMap ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( added );

 if ( sizeOf( UsageMap ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( used );

 {Initialization:}
 for i:= 0 to 1 do
  for j:= 1 to MaxN do
   for k:= 0 to MaxK do
   begin
    states^[ i, j , k ]:= INFINITY;
    used^[ i , j, k ]:= false;
   end;

 for j:= 1 to N do
 begin
  states^[ 0, j, 0 ]:= length( collectionA^[ j ] );
  backRef^[ 0, j, 0 ].i:= 2;
  backRef^[ 0, j, 0 ].j:= -1;
  backRef^[ 0, j, 0 ].k:= -1;
  added^[ 0, j, 0 ].whichWasAdded:= 0;
  added^[ 0, j, 0 ].addedIndex:= j;
 end;

 {Processing with Dijkstra algorithm:}
 for l:= 1 to MaxStateCount do
 begin

  min:= INFINITY;

  for j:= 1 to N do
   for k:= 0 to MaxK do
   if ( not used^[ 0, j, k ] ) and ( states^[ 0, j, k ] < min )  then
   begin
    min:= states^[ 0, j, k ];
    newI:= 0;
    newJ:= j;
    newK:= k;
   end;

  for j:= 1 to M do
   for k:= 0 to MaxK do
   if ( not used^[ 1, j, k ] ) and ( states^[ 1, j, k ] < min )  then
   begin
    min:= states^[ 1, j, k ];
    newI:= 1;
    newJ:= j;
    newK:= k;
   end;

  if ( min = INFINITY ) then break;

  if ( newI = 0 ) then performSteps( 0, newJ, newK,
                                     1,
                                     collectionA^[ newJ ],
                                     M,
                                     collectionB
                                     )
                  else performSteps( 1, newJ, newK,
                                     0,
                                     collectionB^[ newJ ],
                                     N,
                                     collectionA
                                     );
  used^[ newI, newJ, newK ]:= true;
 end;

 {Searching for the best seed to build representations:}
 min:= INFINITY;

 for j:= 1 to N do
  if ( states^[ 0, j, length( collectionA^[ j ] ) ] < min ) then
  begin
   min:= states^[ 0, j, length( collectionA^[ j ] ) ];
   currentI:= 0;
   currentJ:= j;
   currentK:= length( collectionA^[ j ] );
  end;

 for j:= 1 to M do
  if ( states^[ 1, j, length( collectionB^[ j ] ) ] < min ) then
  begin
   min:= states^[ 1, j, length( collectionB^[ j ] ) ];
   currentI:= 1;
   currentJ:= j;
   currentK:= length( collectionB^[ j ] );
  end;

 if ( min = INFINITY ) then
 begin
  {No string can be constructed:}
  solve:= true;
  shortestLength:= 0;
  exit;
 end;

 shortestLength:= min;

 {Memory allocation}
 if ( sizeOf( Representation ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( representationA );

 if ( sizeOf( Representation ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( representationB );

 if ( sizeOf( Representation ) > maxAvail ) then
 begin
  writeln( OUT_OF_MEMORY );
  exit;
 end;
 new( tmpRepresentation );

 {Building representations:}
 aLength:= 0;
 bLength:= 0;

 while ( currentI<> 2 ) do
 begin

  if ( added^[ currentI, currentJ, currentK ].whichWasAdded = 0 ) then
  begin

   inc( aLength );
   if ( aLength > MaxStateCount )  then
   begin
    writeln( INTERNAL_ERROR_IN_SOLVER );
    exit;
   end;

   representationA^[ aLength ]:=
                     added^[ currentI, currentJ, currentK ].addedIndex;
  end
  else
  begin

   inc( bLength );
   if ( bLength > MaxStateCount )  then
   begin
    writeln( INTERNAL_ERROR_IN_SOLVER );
    exit;
   end;

   representationB^[ bLength ]:=
                     added^[ currentI, currentJ, currentK ].addedIndex;
  end;

  newI:= backRef^[ currentI, currentJ, currentK ].i;
  newJ:= backRef^[ currentI, currentJ, currentK ].j;
  newK:= backRef^[ currentI, currentJ, currentK ].k;

  currentI:= newI;
  currentJ:= newJ;
  currentK:= newK;

 end;

 reverseRepresentation( representationA, tmpRepresentation, aLength );
 reverseRepresentation( representationB, tmpRepresentation, bLength );

 solve:= true;
end;

var
 N,M:integer;
 collectionA, collectionB:PCollection;
 shortestLength: longint;
 aLength, bLength: integer;
 representationA, representationB: PRepresentation;
 outputWrong: boolean;
 myALength, myBLength: integer;
 myRepresentationA, myRepresentationB: PRepresentation;
 myShortestLength: longint;
 Code : integer;

{ During BOI'99 the following maximum points for test cases were used :
const testcount = 10;
const Points:array[1..testcount] of integer = (2,4,4,6,6,6,2,2,2,6);
 }
begin
 writeln( SEPARATOR );
 writeln( PROGRESS_READING_INPUT );

 if ( not( readInput( 'match.in',
                      N, M,
                      collectionA,
                      collectionB ) ) ) then exit;

 writeln( PROGRESS_READING_OUTPUT );

 if ( not readOutput( OUTPUT_FILE,
                      N, M,
                      collectionA,
                      collectionB,
                      shortestLength,
                      aLength,
                      bLength,
                      representationA,
                      representationB,
                      outputWrong,
                      Code ) ) then
 begin
  if ( outputWrong ) then writeln( RESULT_SOLUTION_NOT_ACCEPTED );
  if ( Code = 2 ) then halt(102) else halt(103);
 end;

 writeln( SOLUTIONS_LENGTH, shortestLength );

 if ( shortestLength <> 0 ) then
 begin
  writeln( PROGRESS_VERIFYING_SOLUTION );

  if ( not verifySolution( N, M,
                           collectionA,
                           collectionB,
                           shortestLength,
                           aLength,
                           bLength,
                           representationA,
                           representationB
                           ) ) then
  begin
   writeln( RESULT_SOLUTION_NOT_ACCEPTED );
   halt(102);
  end;
 end;

 writeln( PROGRESS_SOLVING_TASK );
 if ( not( solve( N, M,
                  collectionA, collectionB,
                  myShortestLength,
                  myALength, myBLength,
                  myRepresentationA,
                  myRepresentationB ) ) ) then exit;

 writeln( TESTERS_SOLUTIONS_LENGTH, myShortestLength );

 if ( myShortestLength = shortestLength ) then
 begin
  writeln( RESULT_SOLUTION_ACCEPTED );
  exit;
 end;

 if ( shortestLength <> 0 ) and
    ( ( shortestLength < myShortestLength) or
      ( myShortestLength = 0 ) ) then
 begin
  writeln( SOLVER_IS_INCORRECT );
  halt(101);
 end;

 writeln( RESULT_SOLUTION_NOT_ACCEPTED );
 halt(102);
end.

