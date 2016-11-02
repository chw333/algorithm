#include <fstream.h>
#include <math.h>

long cnt;

void process()
{
	ifstream in ("spy.in");
	long n;
	in >> n;
	int a,b,c,d,i;
	for (i = 0;i < n;i++)
	{
		in >> a >> b >> c >> d;
		if (a > c && b > d)
		{
			cnt++;
			continue;
		}
		if (a > d && b > c)
		{
			cnt++;
			continue;
		}
		if (sqrt(a * a + b * b) > c + d)
		{
			cnt++;
			continue;
		}
	}
}

void o_stream()
{
	ofstream out ("spy.out");
	out << cnt;
}

void main()
{
	process(); // includes i_stream()
	o_stream();
}