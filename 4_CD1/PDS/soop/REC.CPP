#include<stdio.h>
#include<conio.h>
#define min(a,b) ((a)>(b)?(b):(a))

int dt[100],cnt;
void process(int x)
{
	int i,j,y;
	if( x == 0 ) {
		for(i=0;i<cnt;i++) {
			printf("%d ",dt[i]);
		}
		printf("\n");
	}
	else {
		for(i=1;i<=min(x,3);i++) {
			dt[cnt++] = i;
			process(x-i);
			cnt--;
		}
	}
}

void main(void)
{
	clrscr();
	process(5);
}