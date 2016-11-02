#include<stdio.h>
#include<conio.h>
void hanoi(int n,char a,char b,char c)
{
	if(n>0)
	{
		hanoi(n-1,a,c,b);
		printf("%dth plate %c to %c\n",n,a,b);
		hanoi(n-1,c,b,a);
	}
}
void main()
{
	clrscr();
	hanoi(4,'a','b','c');
}
