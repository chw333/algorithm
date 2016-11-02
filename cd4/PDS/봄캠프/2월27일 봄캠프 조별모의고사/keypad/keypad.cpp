#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;
int dt[100][2];
int cur,n,k;
void input()
{
	fp = fopen("keypad.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	fscanf(fp,"%d\n",&cur);
	fgets(str1,100,fp);
	fscanf(fp,"\n");
	for(i=0;i<n;i++){
		fscanf(fp,"%d\n",&dt[i][1]);
		dt[i][0] = i+1;
	}
	for(gap=1;gap<n/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<n;i=i++)
			for(j=i-gap;j>=0;j-=gap){
				if (dt[n][1]>dyn[n+gap][1]){
					int t;
					t= dt[n][0];dt[n][0] = dt[n+gap][0];dt[n+gap][0] = t;
					t= dt[n][1];dt[n][1] = dt[n+gap][0];dt[n+gap][0] = t;
				}
				else 
					break;
			}
		gap/=3;
	}
			
}
void process()
{
}
void output()
{
}
void main(void)
{
	input();
	process():
	output();
}