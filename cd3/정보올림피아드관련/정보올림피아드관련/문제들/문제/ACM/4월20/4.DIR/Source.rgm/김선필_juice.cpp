#include <fstream.h>
ifstream in("juice.in");
ofstream out("juice.out");
int n,don,money[1000],wei[1000],dab[50000];
void input()
{
	int i,su,su1;
	in>>su>>su1>>n;
	don=su1-su;
	for(i=0;i<n;i++) in>>money[i]>>wei[i];
	for(i=1;i<=don;i++) dab[i]=32000;
}
void process()
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=wei[i];j<=don;j++)
			if(dab[j]>dab[j-wei[i]]+money[i])
				dab[j]=dab[j-wei[i]]+money[i];
}
void output()
{
	if(dab[don]==32000) out<<"impossible";
	else out<<dab[don];
}
void main()
{
	input();
	process();
	output();
}