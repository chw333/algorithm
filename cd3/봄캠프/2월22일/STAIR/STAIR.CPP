#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;
int n,k;
unsigned long buf[200];

void input()
{
	fp = fopen("stair.inp","r");
	fscanf(fp,"%d %d",&n,&k);
	fclose(fp);
}
void process()
{

	int i,j;
	buf[0] = 1;
	for(i=1;i<=n;i++){
		int cnt=0;
		for(j=i-k;j<i;j++){
		if(!(j <0))cnt+=buf[j];
			
		}
			buf[i] = cnt;
	}
}
void output()
{
	fopen("stair.out","w");
//	if(buf[n] > 2147483647)buf[n]=2147483647;

	fprintf(fp,"%u",buf[n]);
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}
