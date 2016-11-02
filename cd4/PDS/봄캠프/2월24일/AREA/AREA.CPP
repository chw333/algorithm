#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 1200

FILE *fp;
double dt[MAX][4];
double x[MAX],y[MAX];
int cnt;
double max;
int n;

void input()
{
	int i;
	fp = fopen("area.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++){
		double x1,y1,x2,y2;
        fscanf(fp,"%lf %lf %lf %lf\n",&x1,&y1,&x2,&y2);
		dt[i][0] = x1;dt[i][1] = y1;dt[i][2] = x2;dt[i][3] = y2;
		x[cnt] = dt[i][0];y[cnt++] = dt[i][1];
		x[cnt] = dt[i][2];y[cnt++] = dt[i][3];
	}
	fclose(fp);
}
void process()
{
	int i,j,gap,k,imsi,f;
	double t;

	for(gap=1;gap<cnt/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<=cnt;i=i++)
			for(j=i-gap;j>=0;j-=gap){
				if (x[j] > x[j+gap]){
					t = x[j];x[j] = x[j+gap];x[j+gap] = t;
				}
			else
				break;
			}
		gap/=3;
	}
	for(gap=1;gap<cnt/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<=cnt;i=i++)
			for(j=i-gap;j>=0;j-=gap){
				if (y[j] > y[j+gap]){
					t = y[j];y[j] = y[j+gap];y[j+gap] = t;
				}
			else
				break;
			}
		gap/=3;
	}
	for(i=1;i<n*2;i++){
		for(j=1;j<n*2;j++){
			for(k=0;k<n;k++){
				if(x[j] == x[j+1] || y[i] == y[i+1])continue;
				if(dt[k][0]<=x[j] && x[j+1] <= dt[k][2] && dt[k][1] <= y[i] && y[i+1]<=dt[k][3]){
					max += ((x[j+1]-x[j])*(y[i+1]-y[i]));
				break;
				}
			}
		}
	}
}
void output()
{
 	fp = fopen("area.out","w");
	fprintf(fp,"%0.2lf",max);
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}