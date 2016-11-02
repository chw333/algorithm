#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define limit 10000
int visit[10001];
void main()
{
	int size[10];
	int value[limit+1],item[limit+1];
	int i,s,p,newvalue,j,k;

	FILE *fp;
	fp = fopen("coin.inp","r");
		fscanf(fp,"%d\n",&k);
		for(i=0;i<k;i++)fscanf(fp,"%d\n",&size[i]);
	fclose(fp);
	
	for(s=0;s<=limit;s++)value[s] = s;
	for(i=0;i<k;i++)
		for(s=size[i];s<=limit;s++){
			p = s-size[i];
			newvalue=value[p]+1;
			if(newvalue<=value[s]){
				value[s]=newvalue;item[s] = i;
			}
		}
	
	for(i=0;i<k-1;i++)
		for(j=i+1;j<k;j++)
			if(size[i] < size[j]){
				int imsi;
				imsi = size[i];size[i] = size[j];size[j] = imsi;
			}
	for(i=1;i<=10000;i++){
		int f = 0,fun = 0,coin =0;
		fun = i;
		while(f != k){
			if(fun >= size[f]){visit[i]++;fun-=size[f];}
			else f++;
		}
	}
	fp = fopen("coin.out","w");
	for(i=1;i<=10000;i++)
		if(visit[i] != value[i]){
			fprintf(fp,"No\n%d",i);
			exit(0);
		}
	fprintf(fp,"Yes");
}
