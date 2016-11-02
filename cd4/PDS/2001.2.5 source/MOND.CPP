#include<stdio.h>
#include<conio.h>

#define MAX 100

void main()
{
	FILE *fs=fopen("input.txt","r");
	FILE *fp=fopen("output.txt","w");
	int i,j,number,high;
	long process;
	fscanf(fs,"%d\n",&number);
	for(i=0;i<number;i++){
		fscanf(fs,"%d\n",&high);
		process=0;
		for(j=0;j<high;j++){
			process+=2*(high-j);
		}
		if(high%2==0) process++;
		fprintf(fp,"%ld\n",process);
	}
}

