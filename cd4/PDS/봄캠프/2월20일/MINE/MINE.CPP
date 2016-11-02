#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int buf[100][100];
int cur[100][100];
int bomb[100][3];
int check[100][3];
int poin,x,y,bomsz,v;

void input()
{
	int i,j;
	fp = fopen("mine.inp","r");
		fscanf(fp,"%d %d\n",&x,&y);
			for(i=0;i<x;i++){
				for(j=0;j<y;j++){
					fscanf(fp,"%d ",&buf[i][j]);
					if(buf[i][j] == 0)poin++;
				}
			fscanf(fp,"\n");
		}
		fscanf(fp,"%d",&bomsz);
	fclose(fp);
}

void process()
{
	int i,j,k,t = 0,h;
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			int cnt=0;
			if(buf[i][j] == 0){
				int nswe[4]={0,0,0,0};;
				for(k=1;k<=bomsz;k++){
					int dir[4][2] = {{k,0},{-k,0},{0,k},{0,-k}};
					for(h=0;h<4;h++){
						if(buf[i+dir[h][0]][j+dir[h][1]] == 2)nswe[h] = 1;
						if(buf[i+dir[h][0]][j+dir[h][1]] == 1 && nswe[h] != 1){goto end;}
						//if(buf[i+dir[h][0]][j+dir[h][1]] == 0)cnt;
					}
				}
				cur[i][j]++;
				bomb[t][2] = cnt+1;
				bomb[t][0] = x;
				bomb[t++][1] = y;
				nswe[0] = 0;nswe[1] = 0;nswe[2] = 0;nswe[3] = 0;
				for(k=1;k<=bomsz;k++){
					int dir[4][2] = {{k,0},{-k,0},{0,k},{0,-k}};
					cur[i][j] = 1;
					for(h=0;h<4;h++){
						if(buf[i+dir[h][0]][j+dir[h][1]] == 2)nswe[h] = 1;
						if(cur[i+dir[h][0]][j+dir[h][1]] == 0 && nswe[h] != 1)cur[i+dir[h][0]][j+dir[h][1]]++;
					}
				}
			}
end:;
		}
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(cur[i][j] == 1)v++;
		}
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			printf("%2d ",cur[i][j]);
		}
		printf("\n");
	}
	fp = fopen("mine.out","w");
	if(poin!=v){fprintf(fp,"0");exit(0);}
	fclose(fp);

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