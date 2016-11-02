#include <fstream.h>
#include <string.h>
ifstream in("marathon.in");
ofstream out("marathon.out");

int indata[100];
int n, m;
int length;
double t;
void input()
{
	int i;
	in >> n >> m;
	for(i=0;i<n;i++){
		in >> indata[i];
	}
	length=m/(n-1);
}
void output()
{
	out << t;
}
void proc()
{
	int i;
	double sum=0;
	for(i=1;i<n;i++) {
		if(indata[i-1]<indata[i]) sum=sum+(0.5*length);
		else if(indata[i-1]>indata[i]) sum=sum+(0.1*length);
		else sum=sum+(0.2*length);
	}
	t=sum;
}

void main()
{
	input();
	proc();
	output();
}