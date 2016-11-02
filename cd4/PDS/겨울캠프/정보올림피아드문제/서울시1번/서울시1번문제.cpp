#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int n;
int dt[100][100];
int blcnt,fun;
int max,blmax;
int gol[100][100];

int imsi[100];
void output()
{
	if(fun > max){
		max = fun;
		blmax = blcnt;
		for(i=0;i<=blmax;i++){

	}
	if(fun == max){

	}
}


void back(int x,int y)
{
	
	if(x == n-1 && y == n-1)output();
	
	back(x+1,y);
	back(x,y+1);

	
}

void main(void)
{
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
					fscanf(fp,"%d",&dt[i][j]);
			}
		}
}
