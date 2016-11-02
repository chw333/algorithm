#include<stdio.h>
#include<conio.h>
void main()
{
	int a[100],b[100],d[100],i,j,k,max = 0,bun = 0,cnt;
	FILE *fp;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++)fscanf(fp,"%d ",&d[i]);
		
	for(i=0;i<cnt;i++){
		a[i] = 1;
		for(k=0;k<i;k++){
			if((d[k]<d[i]) && (a[i]<a[k]+1))
			{
				a[i] = a[k]+1;
				b[i] = k;
			}
		}
		if(max<a[i]){max = a[i];bun = i;}
	}
	printf("%d\n",max);
}

