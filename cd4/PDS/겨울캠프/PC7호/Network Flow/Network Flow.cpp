#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void main(void)
{
	int i,j,l = 0,k = 0;
	FILE *fp;
	fp = fopen("input.txt","r");
	fscanf(fp,"%d \n",&n);
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			int imsi;
			fscanf(fp,"%d ",&imsi);
			a[i+1][j+1] = imsi;
			a[j+1][i+1] = imsi;
		}
	}
	fclose(fp);
	back(1);
}
void back(int x)
{
	v[i] = 1;
	for(j=1;j<=N;j++){
		if(a[i][j] == 1 && v[j] == 0){
			printf("%d->%d ",i,j);
			visit(j);
}
