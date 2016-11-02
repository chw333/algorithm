#include<stdio.h>
#include<fstream.h>
#include<iostream.h>

short N,n[100][100];

void loadfile()
{
	ifstream fp("TRIANGLE.IN");
	fp>>N;
	for(short i=0;i<N;i++)
		for(short j=0;j<=i;j++)
			fp>>n[i][j];
}
void core()
{
	for(short i=1;i<N;i++)
	{
		n[i][0]+=n[i-1][0];
		n[i][i]+=n[i-1][i-1];
		for(short j=1;j<i-1;j++)
			n[i][j]+=(n[i-1][j-1]>n[i-1][j]?n[i-1][j-1]:n[i-1][j]);
	}
}

void result()
{
	int max;
	for(short i=0;i<N;i++)
		if(max<n[N-1][i])
			max = n[N-1][i];
	printf("%d",max);
}

void main()
{
	loadfile();
	core();
	result();

}