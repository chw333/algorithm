#include<string.h>
#include<conio.h>
#include<stdio.h>
main()
{
static char chr1;
static int input,i,j,l = 0,q;
static char dt[10][20],k;
static int wi,fi;

clrscr();
for(i=0;i<10;i++)
	for(j=0;j<20;j++)
		dt[i][j] = ' ';
printf("STRING = ");scanf("%c",&chr1);
printf("INPUT INT =");scanf("%d",&input);
clrscr();
	fi = 9;
while(l<=255){
clrscr();
	l++;
	if (l!=1){
		for(i=0;i<10;i++){
			for(j=0;j<20;j++){
			 if ( i!= 0){
			 if ( dt[i][j] != ' ' && dt[i][j+1] == ' '){
				dt[i][j+1] = dt[i][j];
				dt[i][j] = ' ';
				j=j+1;
				}
			}
			}
		}
	}
	if ( l%5 == 0 || l == 1){
		dt[fi][0] = chr1;
		if(fi == 0 && q == 1)
			q = 0 ;
		if(fi == 0 && q == 0);
			q = 1;
		if(q==1)
		fi--;
		if(q==0)
		fi++;
   }

   chr1-=input;
   if(chr1 == 'A'-1)
	chr1 = 'Z';

//PRINT
	for(i=0;i<10;i++){
		printf("*");
		for(j=0;j<20;j++){
			if (dt[i][j] != ' ')
			printf("%c",dt[i][j]);
			else
			printf(" ");

		}
		printf("*\n");
	}
	printf("************");
getch();
}
}
