program main;

uses funit;

var
 a1,a2,a3,a4 : integer;

begin
 Write('Input FUN argument values =>'); Readln(a1,a2,a3,a4);
 Writeln;
 Writeln('FUN ( ',a1,', ',a2,', ',a3,', ',a4,' ) = ',fun(a1,a2,a3,a4));
end.
