#include<stdio.h>
#include<conio.h>

FILE *fp;
int dt[100];
int cur[100];

void input()
{
	fp = fopen("car.in","r");
	fscanf(fp,"%d %d %d\n",&n,&k,&z);
	for(i=0;i<n;i++){
		fscanf("%d ",&dt[i]);
		cur[i] = dt[i];
	}
}
void process()
{
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i]<dt[j]){
				int imsi;
				imsi = dt[i];dt[i] = dt[j];dt[j] = imsi;
			}
		}
	}

	for(i=0;i<n;i++){
		if(cur[i] != dt[i]){
					

}
void output()
{
	int i;
	for(i=0;i<cnt;i++){
	
	}
}
void main(void)
{
	input();
	process();
	output()}
}