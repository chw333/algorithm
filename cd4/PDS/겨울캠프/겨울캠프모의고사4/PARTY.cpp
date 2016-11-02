#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

FILE *fp;
int n,k,d;
int ani[100];
int cur[100][100];
void input()
{
	fp = fopen("party.in","r");
	fscanf(fp,"%d %d %d\n",&n,&k,&d);
	for(i=0;i<n;i++)fscanf(fp,"%d ",&ani[i]);
	fscanf(fp,"\n");
	for(i=0;i<n;i++){
		int cnt;
		fscanf(fp,"%d",&cnt);
		for(j=0;j<cnt;j++){
			int imsi;
			fscanf(fp,"%d ",&imsi);
			cur[i][imsi] = 1;
		}
		fscanf(fp,"\n");
	}
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
