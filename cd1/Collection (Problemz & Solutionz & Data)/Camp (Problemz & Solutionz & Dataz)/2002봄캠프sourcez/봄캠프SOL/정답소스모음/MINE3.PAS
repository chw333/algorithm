Program Mine3;
Const
	Di : Array[1..4] of Shortint = (1, -1, 0, 0);
	Dj : Array[1..4] of Shortint = (0, 0, 1, -1);
Var
	n, m, b : Integer;
	Table : Array[0..51, 0..51] of Byte;
	Array1, Array2 : Array[0..51, 0..51] of Integer;
	Bn, Bn2, Tn : Integer;
	Bomb, Bomb2 : Array[1..3000, 1..2] of Byte;
	Check : Array[1..3000] of Boolean;
Procedure Input;
Var
	Filename : Text;
	i, j : Integer;
Begin
	Assign(Filename, 'Mine3.Inp');
	Reset(Filename);
	Readln(Filename, n, m);
	For i := 1 to n do
		For j := 1 to m do
			Read(Filename, Table[i, j]);
	Readln(Filename, b);
	Close(Filename);
	For i := 1 to n do Begin
		Table[i, 0] := 2;
		Table[i, m + 1] := 2;
	End;
	For i := 1 to m do Begin
		Table[0, i] := 2;
		Table[n + 1, i] := 2;
	End;
End;
Procedure Process1;
Var
	i, j, k, l : Integer;
Label Jump1, Jump2;
Begin
	For i := 1 to n do
		For j := 1 to m do
			If Table[i, j] = 0 Then Begin
				For k := 1 to 4 do
					For l := 1 to b do
						If Table[i + l * Di[k], j + l * Dj[k]] = 1 Then Goto Jump1
						Else If Table[i + l * Di[k], j + l * Dj[k]] = 2 Then Break;
				Inc(Bn);
				Bomb[Bn, 1] := i;
				Bomb[Bn, 2] := j;
				Inc(Array1[i, j]);
				For k := 1 to 4 do
					For l := 1 to b do Begin
						If Table[i + l * Di[k], j + l * Dj[k]] = 2 Then Break;
						Inc(Array1[i + l * Di[k], j + l * Dj[k]]);
					End;
				Jump1:
			End;
	Tn := Bn;
	For i := Tn Downto 1 do Begin
		If Array1[Bomb[i, 1], Bomb[i, 2]] = 1 Then Goto Jump2;
		For k := 1 to 4 do
			For l := 1 to b do Begin
				If Table[Bomb[i, 1] + l * Di[k], Bomb[i, 2] + l * Dj[k]] = 2 Then Break;
				If Array1[Bomb[i, 1] + l * Di[k], Bomb[i, 2] + l * Dj[k]] = 1 Then Goto Jump2;
			End;
		Dec(Array1[Bomb[i, 1], Bomb[i, 2]]);
		For k := 1 to 4 do
			For l := 1 to b do Begin
				If Table[Bomb[i, 1] + l * Di[k], Bomb[i, 2] + l * Dj[k]] = 2 Then Break;
				Dec(Array1[Bomb[i, 1] + l * Di[k], Bomb[i, 2] + l * Dj[k]]);
			End;
		Check[i] := True;
		Dec(Bn);
		Jump2:
	End;
End;
Procedure Output;
Var
	Filename : Text;
	i : Integer;
Begin
	Assign(Filename, 'Mine3.Out');
	Rewrite(Filename);
	If Bn > Bn2 Then Begin
		Writeln(Filename, Bn2);
		For i := 1 to Bn2 do
			Writeln(Filename, Bomb2[i, 1], ' ', Bomb2[i, 2]);
	End Else Begin
		Writeln(Filename, Bn);
		For i := 1 to Tn do
			If Not Check[i] Then
				Writeln(Filename, Bomb[i, 1], ' ', Bomb[i, 2]);
	End;
	Close(Filename);
End;
Procedure Process2;
Var
	i, j, k, l, zz : Integer;
	Sw : Integer;
	Max, Maxi, Maxj : Integer;
Label Jump;
Begin
	While True do Begin
		Max := 0;
		For i := 1 to n do
			For j := 1 to m do
				If (Table[i, j] = 0) Then Begin
					If Array2[i, j] = 0 Then zz := 1 Else zz := 0;
					For k := 1 to 4 do
						For l := 1 to b do Begin
							If Table[i + l * Di[k], j + l * Dj[k]] = 1 Then Goto Jump;
							If Table[i + l * Di[k], j + l * Dj[k]] = 2 Then Break;
							If Array2[i + l * Di[k], j + l * Dj[k]] = 0 Then Inc(zz);
						End;
					If zz > Max Then Begin
						Max := zz;
						Maxi := i;
						Maxj := j;
					End;
					Jump:
				End;
		If Max = 0 Then Break;
		Inc(Bn2);
		Bomb2[Bn2][1] := Maxi;
		Bomb2[Bn2][2] := Maxj;
		Array2[Maxi, Maxj] := 1;
		For k := 1 to 4 do
			For l := 1 to b do Begin
				If Table[Maxi + l * Di[k], Maxj + l * Dj[k]] = 2 Then Break;
				Array2[Maxi + l * Di[k], Maxj + l * Dj[k]] := 1;
			End;
	End;
End;
Begin
	Input;
	Process1;
	Process2;
	Output;
End.