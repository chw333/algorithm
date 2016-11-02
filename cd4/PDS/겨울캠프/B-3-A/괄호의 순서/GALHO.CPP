#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

char dt[100],str1[100],str2[100];
int cur[100];
int cnt = 2,max;
FILE *fp;

void input()
{
	int i,j;
	fp = fopen("galho.inp","r");
		fgets(dt,100,fp);
	for(i=0;i<strlen(dt);i++){
		if(dt[i] == ')')cur[i] = 0;
		if(dt[i] == '(')cur[i] = 1;
	}
	fclose(fp);
}
void process()
{
	int i,j,k=0,o1,o2;
	for(i=strlen(dt)-1;i>=0;i--){
		if(cur[i] == 1)max+= pow(cnt,k);
		k++;
	}
	itoa(max-1,str1,2);
	itoa(max+1,str2,2);
	for(i=0;i<strlen(str1);i++){
		if(o1 < 0)for(j=0;j<=strlen(str1);j++)str1[j] = ' ';
		if(str1[i] == 1)o1++;

}
void output()
{
	clrscr();
	int i;
	for(i=0;i<strlen(dt);i++)printf("%d",cur[i]);
	printf("\n%s\n",dt);
	printf("%s\n",str1);
	printf("%s",str2);
}
void main(void)
{
	input();
	process();
	output();
}