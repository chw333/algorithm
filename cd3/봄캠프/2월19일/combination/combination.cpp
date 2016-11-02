#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int sosu[10001];
int bunmo[10001];
int bunja[10001];
int bunmom=1,bunjam=1;
char string[10001];
FILE *fp;
int k,n,max,MAX;

int check(int t)
{
	int i;
	for(i=2;i<=(sqrt(t)+0.5);i++)
		if(t%i == 0)return 0;
	return 1;
}

void input()
{
	fp = fopen("comb.inp","r");
		fscanf(fp,"%d\n",&k);
		if(MAX < k)MAX = k;
		fscanf(fp,"%d\n",&n);
		if(MAX < n)MAX = n;
	fclose(fp);
	
}
void process()
{
	int i,j,o=0;
	for(i=2;i<=MAX;i++)
		if(check(i))sosu[o++] = i;
	
	for(i=1;i<=n-1;i++){
		int imsi=i,o=0;
		for(j=0;;j++){
			if(imsi%sosu[o] == 0){imsi/=sosu[o];bunja[o]++;}
			else o++;
			if(imsi == 1){if(max < o)max = o;break;}
		}
	}
	for(i=1;i<=k-1;i++){
		int imsi=i,o=0;
		for(j=0;;j++){
			if(imsi%sosu[o] == 0){imsi/=sosu[o];bunmo[o]++;}
			else o++;
			if(imsi == 1){if(max < o)max = o;break;}
		}
	}
	for(i=1;i<=n-k;i++){
		int imsi=i,o=0;
		for(j=0;;j++){
			if(imsi%sosu[o] == 0){imsi/=sosu[o];bunmo[o]++;}
			else o++;
			if(imsi == 1){if(max < o)max = o;break;}
		}
	}

	for(i=0;i<=max;i++){
		if(bunja[i]>bunmo[i]){
			bunja[i]-=bunmo[i];
			bunmo[i] = 0;
			bunjam*=pow(sosu[i],bunja[i]);
			bunmom*=pow(sosu[i],bunmo[i]);
			continue;
		}
		if(bunmo[i]>bunja[i]){
			bunmo[i]-=bunja[i];
			bunja[i] = 0;
			bunjam*=pow(sosu[i],bunja[i]);
			bunmom*=pow(sosu[i],bunmo[i]);
			continue;
		}
		if(bunmo[i] == bunja[i]){
			bunmo[i]= bunja[i] = 0;
			continue;
		}
	}
}

void output()
{
	int i;
	fp = fopen("comb.out","w");
	itoa(bunjam/bunmom,string,10);
	for(i=strlen(string)-1;i>=0;i--)
		if(string[i] != '0'){fprintf(fp,"%c",string[i]);exit(0);}
	fclose(fp);
}

void main(void)
{
	input();
	process();
	output();
}