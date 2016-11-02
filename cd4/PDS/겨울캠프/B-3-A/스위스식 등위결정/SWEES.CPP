#include<stdio.h>
#include<conio.h>
#include<ctype.h>

FILE *fp;

double dt[60][60],net[100];
int cnt[100][2];
int cur[100];
int ck = 0;
int buf[100][100];
int n[2];
int fun[100][2],che[100];

void input()
{
	int i,j;
	fp = fopen("sweese.inp","r");
	fscanf(fp,"%d %d\n",&n[0],&n[1]);
	for(i=0;i<n[1];i++){
		char imsi0,imsi1;
		fscanf(fp,"%c %c\n",&imsi0,&imsi1);
		imsi0 = toupper(imsi0);
		imsi1 = toupper(imsi1);
		fun[i][0] = imsi0 - 'A';
		fun[i][1] = imsi1 - 'A';
	}

}
void process()
{
	int i,j,k,f;

	for(i=0;i<n[0];i++)che[i] = i+1;

	for(i=0;i<n[1];i++){
		cnt[fun[i][0]][0]++;
		cnt[fun[i][1]][1]++;
		buf[fun[i][0]][cur[fun[i][0]]++] = fun[i][1];
	}

	for(i=0;i<n[0];i++)dt[i][ck] = float(cnt[i][0] / float(cnt[i][0] + cnt[i][1]));

	for(i=0;i<n[0]*n[0];i++){
		for(k=0;k<n[0];k++)
			for(f=0;f<cnt[k][0];f++)
				dt[k][ck] += dt[buf[k][f]][ck-1];
		ck++;
		for(j=0;j<n[0];j++){
			if(i%2 == 0)net[j]+=dt[j][i];
			else net[j] -= dt[j][i];
		}
	}
	for(f=n[0]*n[0]-1;f>=0;f--)
		for(i=0;i<n[0]-1;i++)
			for(j=i+1;j<n[0];j++)
				if(dt[i][f] < dt[j][f]){
					double imsi;
					imsi = dt[i][f]; dt[i][f] = dt[j][f]; dt[j][f] = imsi;
					imsi = che[i];che[i] = che[j];che[j] = imsi;
				}
}
void output()
{
	int i;
	fp = fopen("sweese.ans","w");
	for(i=0;i<n[0];i++){
		fprintf(fp,"%d\n",che[i]);
		if(net[i] != net[i+1])fprintf(fp,"\n");
	}
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}