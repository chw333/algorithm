#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int dyn[100][100];
int dt[100];
int m,n,max,min;
void input()
{
	int i;
	FILE *fp;
	fp = fopen("treasure.inp","r");
	fscanf(fp,"%d %d\n",&n,&m);
	for(i=0;i<n;i++)fscanf(fp,"%d ",&dt[i]);
	fclose(fp);
}
void process()
{
	int i,j,gap;
	for(i=0;i<n;i++)dyn[0][i] = dt[i];
	dyn[1][1] = dyn[0][0] + dyn[0][1];
	for(i=2;i<n;i++)dyn[1][i] = dyn[0][1] + dyn[0][i];
	for(i=2;i<m;i++){
		for(j=i;j<n;j++){
			dyn[i][j] = dyn[0][j] + dyn[i-1][i-1]; 
		}
	}	
	for(gap=1;gap<n/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<n;i=i++)
			for(j=i-gap;j>0;j-=gap){
				if (dyn[m-1][j] > dyn[m-1][j+gap]){
					int t;
					t = dyn[m-1][j];dyn[m-1][j] = dyn[m-1][j+gap];dyn[m-1][j+gap] = t;
				}
			}
		gap/=3;
	}	
	for(i=0;i<n;i++){
		if(dyn[m-1][i] != 0){
			max = dyn[m-1][i];
			min = dyn[m-1][i+m-1];
			break;
		}
	}
}
void output()
{
	FILE *fp;
	fp = fopen("treasure.out","w");
		fprintf(fp,"%d",min-max);
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}
