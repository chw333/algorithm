{$A+,B-,G+,O-,Q-,R-,S-}
program Day1d;

const
	nprimes = 25;
	primes : array[1..nprimes] of integer = (2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97);
	infile = 'factor10.in';
	outfile = 'factor10.out';

var
	fi, fo : text;
	primetot : array[1..nprimes] of integer;
	n, i, j, t, highestprime : integer;

begin
	assign(fi, infile);
	reset(fi);
	assign(fo, outfile);
	rewrite(fo);

	for i := 1 to nprimes do
		primetot[i] := 0;

	readln(fi, n);

	for i := 1 to n do
		begin
			t := i;
			for j := 1 to nprimes do
				while t mod primes[j] = 0 do
					begin
						inc(primetot[j]);
						t := t div primes[j];
					end;
		end;

	for i := nprimes downto 1 do
		if primetot[i] <> 0 then
			begin
				highestprime := i;
				break;
			end;

	for i := 1 to highestprime do
		write(fo, primetot[i], ' ');

	writeln(fo);


	close(fi);
	close(fo);

end.
