#include<stdio.h>
#include<conio.h>
main()
{
	int a[100],b[100],d[100] = {1,5,3,7,4,10},i,j,k,max = 0,bun = 0;
	clrscr();
	for(i=0;i<6;i++){
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
	for(i=0;i<max;i++){
		printf("%d ",d[bun]);
		bun = b[bun];
	}
}

