#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;

int dt[100][100];
int fun[100][100];
int ads[100][100];
int n[2];

void input()
{
	int i,j;
	fp = fopen("flower.inp","r");
	fscanf(fp,"%d %d\n",&n[0],&n[1]);
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			fscanf(fp,"%d ",&dt[i][j]);
		}
	}
	fclose(fp);
}
void process()
{
	int i,j,k,wi;
	for(i=0;i<n[1];i++)fun[0][i] = dt[0][i];
	for(i=1;i<n[0];i++){
		for(j=i;j<n[1];j++){
			int max = 0;
			for(k=0;k<j;k++){
				if(fun[i-1][k] > max)
				{
					max = fun[i-1][k];
					wi = k;
				}
			}
			fun[i][j] = dt[i][j]+max;
			ads[i][j] = wi;
		}
	}


}
void output()
{
	int i,j,max = 0,wi,o = 1,y[100];
	fp = fopen("flower.ans","w");
	for(i=n[0]-1;i<n[1];i++){
		if(fun[n[0]-1][i] > max){max = fun[n[0]-1][i];wi = i;}
	}
	fprintf(fp,"%d\n",max);

	y[0] = wi;
	for(i=n[0]-1;i>0;i--){
		wi = ads[i][wi];
		y[o] = wi;
		o++;
	}
	for(i=o-1;i>=0;i--)fprintf(fp,"%d ",y[i]+1);
}

void main(void)
{
	input();
	process();
	output();
}
