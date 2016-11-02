(*
  Secret Code
  CERC 1999, Michal Sevcenko 27.10.99
*)
 
program soustavy;

const
	MAXLEVEL = 100;

var
	i, n: integer;

function ceil(x: real): integer;
var p: integer;
begin
	p := trunc(x);
	if p <> x then p := p + 1;
	ceil := p;
end;

procedure DoIt;
	var xr, xi, br, bi, ab2, maxc: integer;
	    d: boolean;

	function cipher(xr, xi, level: integer): boolean;
	var
		i, c, p, x1r, x1i: integer;
		ok: boolean;
	begin
		c := -1;
		if level < MAXLEVEL then
		for i := 0 to maxc do
		begin
			p := (xr - i)*br + xi*bi;
			if p mod ab2 = 0 then
			begin
				x1r := p div ab2;

				p := (xi*br - (xr - i)*bi);
				if p mod ab2 = 0
				then
				begin
					x1i := p div ab2;
					c := i;
				end;
			end;
		end;
		
		if c <> -1 then
		begin
			if (x1r = 0) and (x1i = 0) then
			begin
				write(c:1);
				ok := true;
			end
			else
			begin
				ok := cipher(x1r, x1i, level + 1);
				if ok then write(',', c:1);
			end;
		end
			else
		begin
			ok := false;
			write("The code cannot be decrypted.");
		end;
		cipher := ok;
	end;

begin
	readln(xr, xi, br, bi);

	ab2 := br*br + bi*bi;
	maxc := ceil(sqrt(ab2)) - 1;
	d := cipher(xr, xi, 1);
	writeln;
end;

begin
	readln(n);
	for i := 1 to n do DoIt;
end.
