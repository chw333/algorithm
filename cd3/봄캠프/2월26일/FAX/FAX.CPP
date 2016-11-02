#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int dyn[4][100];
void input()
{
	FILE *fp;
	fp = fopen("fax.inp","r");
	fscanf(fp,"%d ",&d);
	fclose(fp);
}
void process()
{
	int i,j;
	dyn[0][0]=1;
	dyn[1][0]=86;
	dyn[2][0]=172;
	dyn[3][0] = 256;
	for(i=1;i<
}
void output()
{
}
void main(void)
{
	input();
	process();
	output();
}