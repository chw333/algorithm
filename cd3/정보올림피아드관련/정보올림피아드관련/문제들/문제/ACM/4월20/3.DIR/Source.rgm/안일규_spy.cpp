#include<fstream.h>
#include<math.h>

int X1[100],Y1[100],X2[100],Y2[100];
int N;

void init()
{
	int i;
	ifstream in("spy.in");
	in >> N;

	for(i=0; i<N; i++){
		in >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
	}
}

int turn1(int x1, int y1, int x2, int y2)
{
	int num;
	float sum;

	num=x1*x1+y1*y1;

	sum=sqrt(num);

	if(sum==x2+y2) return 1;
	return 0;
}

void process()
{
	int i,sw=0;

	for(i=0; i<N; i++){
		if(X1[i]>X2[i] && Y1[i]>Y2[i] || X1[i]>Y1[i] && X2[i]>Y2[i] || turn1(X1[i],Y1[i],X2[i],Y2[i])==0 ) sw++;
	}

	ofstream out("spy.out");
	out << sw;
}

void main()
{
	init();
	process();
}