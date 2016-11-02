#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<limits.h>

#define MAX 3001

static long data[MAX];
static long table[MAX];
long min=INT_MAX,mina,minb;

void dynamic(long number)
{
	long i,j,k;
	for(i=0;i<number;i++){
		table[i]=0;
		for(j=i+1;j<=number;j++){
			table[j]=data[j-1]+table[j-1];
			if(abs(table[j])<min){
				min=abs(table[j]);
				mina=i+1;
				minb=j;
			}
		}
	}
}

void main()
{
	FILE *fs=fopen("pasture.in","r");
	FILE *fp=fopen("pasture.out","w");
	long i,j,number;
	fscanf(fs,"%ld\n",&number);
	for(i=0;i<number;i++){
		fscanf(fs,"%ld\n",&data[i]);
	}
	dynamic(number);
	fprintf(fp,"%ld %ld %ld",mina,minb,min);
}