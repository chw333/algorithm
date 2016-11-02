#include <stdio.h>
#include <fstream.h>

int KR, KC;
char KS[100][100];
int LR, LC;
char LS[100][100];
int XX, YY;
char tet[200][100];

bool pass = false;

void Input()
{
	int i, j;

	ifstream in("tetris.in");

	in >> KR >> KC;
	for( i = 0; i < KR; i++ )
		for( j = 0; j < KC; j++ )
			in >> KS[i][j];

	in >> LR >> LC;
	for( i = 0; i < LR; i++ )
		for( j = 0; j < LC; j++ )
		{
			in >> LS[i][j];
			tet[199 - ( LR - i - 1 )][j] = LS[i][j];
		}
	YY = 199 - LR - KR + 1;

	in.close();
}

void Process()
{
	int i, j;
	int i_tmp1;

	i_tmp1 = 0;
	for( j = 0; j < LC; j++ )
	{
		for( i = 0; i < LR; i++ )
			if( LS[i][j] == '#' ) break;
		if( i < LR ) i_tmp1 = 0;
		else
		{
			i_tmp1++;
			if( i_tmp1 >= KC )
			{
				pass = true;
				break;
			}
		}
	}
}

void Output()
{
	ofstream out("tetris.out");

	if( pass == true ) out << "pass";
	else out << "0";

	out.close();
}

void main()
{
	Input();
	Process();
	Output();
}