{$I-}
const
	sum = 1000;
var
	f : text;
	n : integer;
	a : array [1..sum] of integer;
	b : array [1..sum] of boolean;
	i, j, k, u : integer;
	s : string;
begin
	if paramcount <> 2 then begin
		writeln ('Syntax is: ', paramstr (0), ' inputfile outputfile');
		exit;
	end;

	for i := 1 to sum do begin
		a[i] := 0;
		b[i] := false;
	end;

	assign (f, paramstr (1)); reset (f);
	readln (f, n);
	for i := 1 to n do begin
		readln (f, k);
		a[k] := a[k] + 1;
		for j := sum downto k + 1 do
			if b[j - k] then
				b[j] := true;
		b[k] := true;
	end;
	close (f);
	if ioresult > 0 then begin
		writeln ('Error reading file ', paramstr (1));
		exit;
	end;

	assign (f, paramstr (2)); reset (f);
	if ioresult > 0 then begin
		writeln ('No file ', paramstr (2));
		exit;
	end;

	if b[sum] then begin
		u := 0;
		while not seekeof (f) do begin
			readln (f, s); val (s, k, i);
			if i <> 0 then begin
				writeln ('Invalid format, expected number, got ', s);
				exit;
			end;
			if a[k] = 0 then begin
				writeln ('No more fruits of weight ', k);
				exit;
			end;
			a[k] := a[k] - 1;
			u := u + k;
		end;
		if u = sum then
			writeln ('OK')
		else
			writeln ('Invalid total sum, expected ', sum, ', got ', u);
	end else begin
		readln (f, s);
		if ioresult > 0 then begin
			writeln ('Error reading file ', paramstr (2));
			exit;
		end;
		for i := 1 to length (s) do
			s[i] := upcase (s[i]);
		if (s = 'NO') and seekeof (f) then
			writeln ('OK')
		else
			writeln ('Wrong answer, expected NO, got ', s);
	end;
	close (f);
end.
