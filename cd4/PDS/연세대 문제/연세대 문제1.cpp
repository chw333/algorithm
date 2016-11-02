#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int max;
int dyn[100][100];
int dt[100][100];
int n,k;

void input()
{
	FILE *fp;
	int i,j;

	fp = fopen("input.txt","r");
		fp = fopen("input.txt","r");
			fscanf(fp,"%d %d\n",&n,&k);
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++)
					fscanf(fp,"%d ",&dt[i][j]);
			fscanf(fp,"\n");
			}
		fclose(fp);
		for(i=1;i<=n;i++)dyn[1][i] = dt[1][i];
}

void process()
{
	int i,j;
	for(i=2;i<=k;i++){
		for(j=i+1;j<=n;j++){
			dyn[i][j] = dyn[i-1][j-1] + dt[i-1][i];
		}
	}
	for(i=0;i<n;i++){
		if(max < dyn[k][i])
			max = dyn[k][i];
	}
}
void output()
{
	printf("%d",max);
}

void main(void)
{
	input();
	process();
	output();
}