#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>

int d[100];
void main()
{
	int i,k,p1,p2,x,num;
	printf("Input X,Y,Z,K : ");
		scanf("%d %d %d %d",&x,&d[1],&d[2],&d[3]);
	printf("\nWho first (Computer : 1, You : 2) ");
		scanf("%d",&num);
	if(num == 1) goto s;
start:
	printf ("Which pocket (1, 2, of 3), How many snacks : ");
		scanf("%d %d",&p1,&p2);
		if(p2 > k){
			printf("ERRER\n\n");goto start;
		}
		else
		{
			d[p1]-=p2;
			for(i=1;i<4;i++){
				if(d[i] != 0){
					goto start;printf("\n");
				}
			}
		}
s:
}

