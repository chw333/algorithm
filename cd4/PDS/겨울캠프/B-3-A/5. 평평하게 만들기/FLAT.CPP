#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;

int n;
int dt[100];
int cur[100];
int buf[100];

void input()
{
	int i;
	fp = fopen("flat.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++){
		fscanf(fp,"%d ",&dt[i]);
		cur[i] = dt[i];
	}
	fclose(fp);
}

void process()
{
	int i,j,avr = 0;
	clrscr();
	cur[1] +=cur[0];
	cur[0] = 0;

	for(i=0;i<n;i++){
		avr += dt[i];
	}
	avr /= n;
	for(i=1;i<n;i++){
		if(i != n-1){
			buf[i] = abs((avr - cur[i-1])*2);
			cur[i]   -= (avr - cur[i-1])*2;
			cur[i+1] += (avr-cur[i-1]);
			cur[i-1] += (avr-cur[i-1]);
		}
		else
		{
			buf[i] = abs(avr - cur[i-1]);
			cur[i] -= (avr - cur[i-1]);
			cur[i-1] +=(avr - cur[i-1]);
		}
	}
	for(i=0;;i++){
		int max=0,wi,rs;
		for(j=0;j<n;j++){
			if(max < buf[j]){
				max = buf[j];
				wi = j;
			}
		}
		int x;
		if(wi != 0 && wi != n-1)
		{
			x = cur[i]/2;
			buf[i] -= x*2;
			dt[i-1] += x;
			dt[i+1] += x;
		}
		else
		{
			x = cur[i];
			buf[i] -= x;
			if(wi ==0)dt[i+1]+=x;
			else dt[i-1]+=x;
		}
		for(j=0;j<n;j++)if(buf[i] != 0) rs = 1;


		if(rs == 0)break;
	}


}
void output()
{
}
void main(void)
{
	input();
	process();
	output();
}