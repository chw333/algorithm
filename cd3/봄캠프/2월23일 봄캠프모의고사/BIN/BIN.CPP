#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;
int dt[100];
	
void input()
{
	fp = fopen("bin.in","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++)fscanf(fp,"%d ",&dt[i]);
	fclose(fp);
}
void process()
{
	int i,j;
	
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