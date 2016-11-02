#include <stdio.h>
#include <fstream.h>

int cnt;
int N;

void Input()
{
	int i;
	int A, B, X, Y;

	ifstream in("spy.in");

	in >> N;
	for( i = 0; i < N; i++ )
	{
		in >> A >> B >> X >> Y;
		if( ( X <= A && Y <= B ) || ( X <= B && Y <= A ) ) cnt++;
	}

	in.close();
}

void Output()
{
	ofstream out("spy.out");

	out << cnt;

	out.close();
}

void main()
{
	Input();
	Output();
}