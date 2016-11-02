const
	sum = 1000;
var
	f : text;
	n, k, i, j, m, l : integer;
	a : array [1..sum] of integer;
begin
	for i := 1 to sum do
		a[i] := 0;
	assign (f, 'fruits.in'); reset (f);
	readln (f, n);
	m := 0; i := 0;
	while (m < sum) and (i < n) do begin
		readln (f, k);
		if k + m < sum then
			l := k + m
		else
			l := sum;
		for j := l downto k + 1 do
			if a[j] = 0 then
				if a[j - k] > 0 then begin
					a[j] := k;
					if m < j then
						m := j;
				end;
		if a[k] = 0 then
			a[k] := k;
		if m < k then
			m := k;
		i := i + 1;
	end;
	close (f);
	assign (f, 'fruits.out'); rewrite (f);
	if a[sum] = 0 then
		writeln (f, 'NO')
	else begin
		j := sum;
		while j > 0 do begin
			writeln (f, a[j]);
			j := j - a[j];
		end;
	end;
	close (f);
end.
