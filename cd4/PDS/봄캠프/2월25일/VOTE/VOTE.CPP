#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
FILE *fp;
int n,k,f;
void input()
{
	fp = fopen("vote.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	fscanf(fp,"%d\n",&f);
	fclose(fp);
}
void output()
{
	int i;
	fp = fopen("void.out","w");
	time_t t;
	srand(time(&t));
	for(i=0;i<f;i++){
		fprintf(fp,"%d\n",rand()%2);		
	}
	fclose(fp);
}
void main(void)
{
	input();
	output();
}
