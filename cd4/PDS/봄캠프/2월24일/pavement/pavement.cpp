#include<stdio.h>
#include<conio.h>
int i,j,n,k,cnt=0,dt[1000][1000];

void main(void)
{
	FILE *fp;
	fp = fopen("pavement.inp","r");
		fscanf(fp,"%d %d\n",&n,&k);
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			fscanf(fp,"%d ",&dt[i][j]);
		}
		fscanf(fp,"\n");
	}
	fclose(fp);

	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			if(dt[i][j] == 1)cnt++;
		}
	}
	fp = fopen("pavement.out","w");
	fprintf(fp,"%d",cnt/4);
	fclose(fp);
}