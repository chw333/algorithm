#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int dt[1024][1024];
int fun[100];
int cur[1024][2];
int n,l;
void main(void)
{
	int i,j,k;
start:
	scanf("%d ",&n);rewind(stdin);
	switch(n)
	{
	case 0:
		{
			scanf("%d",&fun[0]);
			break;
		}
	case 1:
		{
			for(i=0;i<3;i++){
			dt[fun[0]][fun[1]]=fun[2];
			break;
		}
	case 2:
		{
			for(i=0;i<4;i++)scanf("%d ",&fun[i]);
			cur[0][l] = fun[0];
			cur[1][l] = fun[1];
			cur[2][l] = fun[2];
			cur[3][l++] = fun[3];
			break;
		}
	case 3:
		{
			exit(0);
			break;
		}
	}
	for(i=0;i<5;i++)fun[i] = 0;
	goto start;	
}