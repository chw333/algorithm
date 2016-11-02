#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define N 8

int a[N+1][N+1] = {
	{0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0},
	{0,1,0,1,1,1,0,0,0},
	{0,0,1,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0},
	{0,0,0,0,0,1,0,1,1},
	{0,0,0,1,0,0,1,0,1},
	{0,0,0,0,0,0,1,1,0}};

int v[N+1];

void visit(int);

void main(void)
{
	int i,k;
	clrscr();
	for(k=1;k<=N;k++){
		for(i=1;i<=N;i++)
			v[i] = 0;
		visit(k);
		printf("\n");
	}
}
void visit(int i)
{
	int j;

	v[i] = 1;
	for(j=1;j<=N;j++){
		if(a[i][j] != 0 && v[j] == 0){
			printf("%d->%d\n",i,j);
			getch();
			visit(j);
		}
	}
}
