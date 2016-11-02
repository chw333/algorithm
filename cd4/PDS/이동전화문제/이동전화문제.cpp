#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

int buf[100];
int cur[100][100];
int SIZE;

int lowbit(int x)
{
	return x&(x^(x-1));
}

void main(void)
{
start:
	scanf("%d",&n);rewind(stdin);
	switch(n)
	{
		case 1:
			{
				for(i=a;i<SIZE;i+=lowbit(i))
				{
					for(j=a;j<SIZE;j+=lowbit(j))
					{
		cur[i][j] += c;
					}
				}
				break;
			}
		case 2:
			{
				for(i=SIZE;i>=0;i--){
					for(j=SIZE;j>=0;j--){
						
				break;
			}
	case 3:
		exit(0);
	}
	scanf("\n");
goto start;

}		
