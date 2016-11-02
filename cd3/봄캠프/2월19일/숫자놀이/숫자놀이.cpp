#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

int value[50000001];
void main()
{
	int size[51];
	int i,j,k,m;

	FILE *fp;
	fp = fopen("number.inp","r");
	fscanf(fp,"%d\n",&k);
		for(i=0;i<k;i++)fscanf(fp,"%d ",&size[i]);
	fscanf(fp,"\n%d",&m);
	fclose(fp);
	for(i=1;i<=5000001;i++){
		int min = 99999,p;
		for(j=0;j<k;j++){
			p = i-size[j];
			if(p<0)continue;
			if(min > value[p])min = value[p];
		}
		value[i] = min+1;
		if(value[i] > m)break;
	}
	fp = fopen("number.out","w");
	if(i%2==0)fprintf(fp,"holsoon win at %d",i);
	else fprintf(fp,"jjaksoon win at %d",i);
	fclose(fp);
}
