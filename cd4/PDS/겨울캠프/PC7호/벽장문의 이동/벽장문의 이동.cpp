#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;

int open[100];
int cnt,op;
int cur[100];
int door[100],check[100];
void back(int x,int y)
{
	int i,j;
	if(x == op)
	{
	
	}
	else
	{
		for(i=0;i<cnt;i++){
			if(check[cnt[i
	
	}
}

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d %d\n",&cnt,&op);
		for(i=0;i<cnt;i++)fscanf(fp,"%d ",&open[i]);
		fscanf(fp,"\n");
		for(i=0;i<cnt-1;i++)fscanf(fp,"%d\n",&cur[i]);
}		

void process()
{
	int i,j;
	back(0);
}
void output()
{
}
void main(void)
{
}