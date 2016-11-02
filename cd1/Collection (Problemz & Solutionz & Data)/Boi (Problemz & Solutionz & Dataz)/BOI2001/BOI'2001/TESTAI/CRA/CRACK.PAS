{ crypto.pas }

const
	len = 10;
	let = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
var
	s1, s2 : string;
	f1, f2 : text;
	key : array [1..len] of byte;
	i, k : integer;
	c : char;
begin
	write ('Input file: '); readln (s1);
	assign (f1, s1); reset (f1);
	write ('Output file: '); readln (s2);
	assign (f2, s2); rewrite (f2);
	write ('Key (', len, ' bytes): ');
	for i := 1 to len do read (key[i]);
	k := 0;
	while not eof (f1) do begin
		while not eoln (f1) do begin
			read (f1, c);
			i := pos (upcase (c), let);
			if i > 0 then begin
				k := k mod len + 1;
				i := (i - 1 + key[k]) mod length (let) + 1;
				c := let[i];
			end;
			write (f2, c);
		end;
		if not eof (f1) then begin
			readln (f1);
			writeln (f2);
		end;
	end;
	close (f1);
	close (f2);
end.
