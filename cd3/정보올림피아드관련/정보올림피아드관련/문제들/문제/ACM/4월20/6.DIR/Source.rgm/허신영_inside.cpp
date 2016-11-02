#include <stdio.h>
#include <fstream.h>

int N;
int BX[20], BY[20];
int RX, RY;
int cnt;

void Input()
{
	int i;
	double aa, bb;

	ifstream in("inside.in");

	in >> N;
	for( i = 0; i < N; i++ )
	{
		in >> aa >> bb;
		BX[i] = (int)(aa * 100);
		BY[i] = (int)(bb * 100);
	}
	in >> aa >> bb;
	RX = (int)(aa * 100);
	RY = (int)(bb * 100);

	in.close();
}

int ccw( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	//int aa = ( x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3 );
	int aa = ( x1 * y2 - x2 * y1 - x3 * y2 + x2 * y3 - x1 * y3 + x3 * y1 );
	if( aa > 0 ) return 1;
	else if( aa < 0 ) return -1;
	else return 0;
}

void abcd( int i1, int i2, int i3 )
{
	int aa = ccw( BX[i1], BY[i1], BX[i2], BY[i2], RX, RY );
	int bb = ccw( BX[i2], BY[i2], BX[i3], BY[i3], RX, RY );
	int cc = ccw( BX[i3], BY[i3], BX[i1], BY[i1], RX, RY );
	if( aa == bb && bb == cc ) cnt++;
}

void Process()
{
	int i, j, k;

	for( i = 0; i < N; i++ )
		for( j = i + 1; j < N; j++ )
			for( k = j + 1; k < N; k++ )
				abcd( i, j, k );
}

void Output()
{
	ofstream out("inside.out");

	out << cnt;

	out.close();
}

void main()
{
	Input();
	Process();
	Output();
}