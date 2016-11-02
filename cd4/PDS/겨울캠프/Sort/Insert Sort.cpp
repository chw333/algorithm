#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

char a[100] = {'T','O','L','E','A','R','N','S','O','R','T','A','L','G','O','R','T','I','T','H'};
void main()
{
	int i,j,t,n = 20;
	for(i=1;i<n;i++){
		t = a[i];
		j = i;
			while(a[j-1] > t && j > 0)
			{
				a[j] = a[j-1];
				for(i=1;i<n;i++)printf("%2d ",a[i]);
				printf("\n");
			}
			a[j] = t;
	}
} 

 