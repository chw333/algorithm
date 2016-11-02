#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 1000

FILE *fp;
int dyn[MAX][MAX];
int dt[MAX][MAX];
int count[MAX],visit[MAX];
int ty[MAX],yon[MAX];
int s[MAX],su[MAX];
int n,k;

void input()
{
	int i,j,gap,f;
	fp = fopen("item.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			fscanf(fp,"%d ",&dt[i][j]);
			if(dt[i][j] == 1)s[i]++;
		}
		fscanf(fp,"\n");
		su[i] = i+1;
	}
	fclose(fp);

	for(gap=1;gap<n/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<n;i=i++)
			for(j=i-gap;j>=0;j-=gap){
				if (s[j]<s[j+gap]){
					int t;
					t = s[j];s[j] = s[j+gap];s[j+gap] = t;
					t = su[j];su[j]=su[j+gap];su[j+gap] = t;
					for(f=0;f<k;f++){
						t=dt[j][f];dt[j][f] = dt[j+gap][f];dt[j+gap][f] = t;
					}
				}
				else
					break;
			}
		gap/=3;
	}
}
void process()
{
	int i,j,l;
	visit[0] = -1;
	count[0] = 1;
	for(i=0;i<k;i++)dyn[0][i] = dt[0][i];
	for(i=1;i<n;i++){
		int max=0,h=0;
		for(j=0;j<i;j++){
			int imsi = 0;
			for(l=0;l<k;l++){
				if(dyn[j][l] > dt[i][l])imsi++;
			}
			if(imsi > max || (max == imsi && count[h] > count [j] && h != 0)){
				max = imsi;h = j;
			}
		}
		for(l=0;l<k;l++){
			if(dt[i][l] == 1 || dyn[h][l] == 1){dyn[i][l] = 1;ty[i]++;}
		}
		if(max == 0){
			count[i] = 1;
			visit[i] = -1;
		}
		else{
			count[i] = count[h]+1;
			visit[i] = h;
		}

	}
}
void output()
{
	int i,j,f=0;
	fp = fopen("item.out","w");
	for(i=0;i<n;i++){
		if(ty[i] == k){
			fprintf(fp,"%d\n",count[i]);
 			j=i;
			while(yon[f-1] != -1){
				yon[f++] = j;
				if(yon[f-1] != -1)j=visit[j];				
			}	
			for(f=count[i]-1;f>=0;f--)fprintf(fp,"%d ",su[yon[f]]);
			exit(0);
		}
	}
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();




}
