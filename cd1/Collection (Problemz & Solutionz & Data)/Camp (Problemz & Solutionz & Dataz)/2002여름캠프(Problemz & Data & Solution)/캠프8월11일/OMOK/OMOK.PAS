program P1;
var
	n: integer;
	table: array[0..20, 0..20] of shortint;
	f: text;
	i, x, y: integer;

	function chk(x, y, dirx, diry: integer): boolean;
	var
		count: integer;
	begin
		while table[x, y] = table[x - dirx, y - diry] do begin
			x := x - dirx;
			y := y - diry;
		end;
		count := 1;
		while table[x, y] = table[x + dirx, y + diry] do begin
			inc(count);
			x := x + dirx;
			y := y + diry;
		end;
		if count = 5 then chk := true else chk := false;
	end;

begin
	assign(f, 'p1.in');
	reset(f);
	read(f, n);
	for i := 1 to n do begin
		read(f, x, y);
		table[x, y] := i and 1 + 1;
		if chk(x, y, 1, 0) then break;
		if chk(x, y, 0, 1) then break;
		if chk(x, y, 1, 1) then break;
                if chk(x, y, 1, -1) then break;
	end;
	close(f);
	assign(f, 'p1.out');
	rewrite(f);
	writeln(f, i);
	close(f);
end.