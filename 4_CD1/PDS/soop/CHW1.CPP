#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define MAX 5
void c(int n,int r)
{
	if(r==0||n==r)return(1);
	else
	return c(n-1,r-1)+c(n-1,r);
}
void main(void)
{
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<=i;j++){
			printf("%dC%d",c(n,r));
		}
	}
}
