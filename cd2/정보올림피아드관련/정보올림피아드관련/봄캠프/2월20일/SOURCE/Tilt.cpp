#include <Stdlib.H>
#include <Fstream.H>
#include <Time.H>

int n, t;
int x[30001], y[30001];
long double Max;
int x1, y1, x2, y2;

void Input(void)
{
	int i;
	ifstream In("Tilt.Inp");
	In >> n;
	for(i = 1; i <= n; i++)
		In >> x[i] >> y[i];
	In.close();
}

void Qsort(int l, int r)
{
	if(l >= r) return;
	int i = l, j = r + 1, k = (rand() % (r - l + 1)) + l;
	t = x[l]; x[l] = x[k]; x[k] = t;
	t = y[l]; y[l] = y[k]; y[k] = t;
	int m = x[l];
	while(1)
	{
		while(x[++i] < m);
		while(x[--j] > m);
		if(i >= j) break;
		t = x[i]; x[i] = x[j]; x[j] = t;
		t = y[i]; y[i] = y[j]; y[j] = t;
	}
	t = x[l]; x[l] = x[j]; x[j] = t;
	t = y[l]; y[l] = y[j]; y[j] = t;
	Qsort(l, j - 1);
	Qsort(j + 1, r);
}

long double Abs(long double a)
{
	if(a > 0) return a; else return -a;
}

void Process(void)
{
	int i;
	for(i = 1; i < n; i++)
		if(Max < Abs((long double)(y[i] - y[i + 1]) / (long double)(x[i] - x[i + 1])))
		{
			Max = Abs((long double)(y[i] - y[i + 1]) / (long double)(x[i] - x[i + 1]));
			x1 = x[i]; y1 = y[i];
			x2 = x[i + 1]; y2 = y[i + 1];
		}
}

void Output(void)
{
	ofstream Out("Tilt.Out");
	Out << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	Out.close();
}

void main(void)
{
	srand((unsigned)time(NULL));
	Input();
	Qsort(1, n);
	Process();
	Output();
}