#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{
	static int input[3][9];
	int imsi;
	int data[10];
	int dt1,dt2;
	int i,j,k,bun,l;
	clrscr();
	FILE *fp;
	fp = fopen("input.in","r");
		for(i = 0 ; i < 9; i++ ){
			fscanf(fp,"%d %d %d",&input[0][i],&input[1][i],&input[2][i]);
		}
	for(i=0;i<8;i++){
		for(j=i+1;j<9;j++){
			if(input[2][i] > input[2][j])
			{
				imsi = input[0][i];input[0][i] = input[0][j];input[0][j] = imsi;
				imsi = input[1][i];input[1][i] = input[1][j];input[1][j] = imsi;
				imsi = input[2][i];input[2][i] = input[2][j];input[2][j] = imsi;
			}
		}
	}
	printf("%d",input[0][0]);
	dt1 = input[2][0];
	i = 0;
	bun = 0;
	 while(i<20){
		   i++;
		for(j = i+1;j<9;j++){
			if( dt1+1 == input[1][j] && bun == 0){
				data[l] = input[0][j];
				bun = 1;
				dt1 = input[2][j];
				i = j;
				printf("%d",input[0][j]);
			}
			if( dt1+1 == input[1][j] && bun == 1){
				data[l] = input[0][j];
				bun = 0;
				dt1 = input[2][j];
				i = j;
				printf("%d",input[0][j]);

			}

		}
	}

}