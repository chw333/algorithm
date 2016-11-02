#include<stdio.h>
#include<time.h>
#include<stdlib.h>
static int n,data[100][100],v[100];
static int move[4][2]={{0,1},{-1,0},{1,0},{0,-1}};
static int cross[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};
static int table[100][100],sx,stime,count;
void input()
{
	FILE *fs = fopen("tree.inp","rt");
	int i,j,x,y;
	fscanf(fs,"%d",&n);
	for(i=0;i<n;i++){
		fscanf(fs,"%d %d",&x,&y);
		if(i==0){ sx=x; }
		data[x][y]=1;
	}
	

}
void process()
{
	FILE *fp;
	int i,j,k,t,a,b,check,cnt;
	table[1][1]=sx; 
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=0;k<4;k++){
				a=i+move[k][0]; b=j+move[k][1];
				check=0;
				if(table[a][b]!=0 && v[table[i][j]]==0){
					for(t=1;t<=n;t++){
						if(data[table[a][b]][t]==1 && v[t]==0){
							table[i][j]=t; v[t]=1;
							check=1; break;
						}
					}
					if(check==1){ break; }
				}
			}
			if(check==0){
				for(k=0;k<4;k++){
					a=i+cross[k][0]; b=j+cross[k][1];
					check=0;
						if(table[a][b]!=0){
						for(t=1;t<=n;t++){
							if(data[table[a][b]][t]==1 && v[t]==0){
									table[i][j]=t; v[t]=1;
								break; check=1;
							}
						}
						if(check==0){ break; }
					}
				}
			}
		}
	}

	cnt=1;
	fp = fopen("tree.out","w");
	do{
		for(i=0;i<=n;i++){
			for(j=0;j<=n;j++){
				if(table[i][j]==cnt){
					cnt++; fprintf(fp,"%d %d\n",i-1,j-1); 
				}
			}
		}
		if((stime-clock())/1000.0==4){ exit(1); }
		if(cnt==n+1){ exit(1); }
		else{ count++; }
		if(count==5){ cnt++; }
	}while(1);
	fclose(fp);
}
void main(void)
{
	stime=clock();
	input();
	process();
//	output();
}
