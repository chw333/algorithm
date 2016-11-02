/*----------------------------------
*          오일러의 한번에 긋기    *
*-----------------------------------
*
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define Node 4
#define Root 6
#define Start 1

int a[Node+1][Node+1] = 
{
	{0,0,0,0,0},
	{0,0,1,0,1},
	{0,1,0,1,2},
	{0,0,1,0,1},
	{0,1,2,1,0}
};

int success,
	v[Root+1],
	n;

void visit(int);

void main(void)
{
	success = 0; n = Root;
	visit(Start);
	if(success==0)
		printf("답없음\n");
}
void visit(int i)
{
	int j;
	v[n] = i;
	if(n==0 && i==Start){
		printf("답 %d:",++success);
		for(i=0;i<=Root;i++)
				printf("%d",v[i]);
		printf("\n");
	}
	else{
		for(j=1;j<=Node;j++)
			if(a[i][j]!=0){
				a[i][j]--;a[j][i]--;
				n--;
				visit(j);
				a[i][j]++; a[j][i]++;
				n++;
			}
	}
}