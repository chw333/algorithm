#include<stdio.h>
#include<conio.h>

#define MAX 50

static int room[MAX][MAX];

int is_empty(int x,int y)
{
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(room[i][j]==1) return 1;
		}
	}
	return 0;
}

void process(int x,int y)
{
	int i,j,k,max,indexx,indexy;
	static int pro_room[MAX][MAX];
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			pro_room[i][j]=0;
		}
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(room[i][j]==1){
				for(k=0;k<x;k++) pro_room[k][j]++;
				for(k=0;k<y;k++) pro_room[i][k]++;
				pro_room[i][j]--;
			}
		}
	}
	max=-9999;
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(pro_room[i][j]>max){
				max=pro_room[i][j];
				indexx=i;
				indexy=j;
			}
		}
	}
	for(i=0;i<x;i++){
		if(room[i][indexy]==1) room[i][indexy]=0;
	}
	for(i=0;i<y;i++){
		if(room[indexx][j]!=-1){
			room[indexx][i]=0;
		}
	}
	room[indexx][indexy]=-1;
}

void main()
{
	FILE *fs=fopen("q2.inp","r");
	FILE *fp=fopen("q2.out","w");
	int i,j,x,y;
	char c;
	fscanf(fs,"%d %d\n",&x,&y);
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			fscanf(fs,"%c",&c);
			if(c=='0') room[i][j]=0;
			else room[i][j]=1;
		}
		fscanf(fs,"\n");
	}
	while(is_empty(x,y)){
		process(x,y);
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(room[i][j]==-1) fprintf(fp,"%d %d\n",i,j);
		}
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(room[i][j]==0) fprintf(fp,".");
			if(room[i][j]==1) fprintf(fp,"x");
			if(room[i][j]==-1) fprintf(fp,"r");
		}
		fprintf(fp,"\n");
	}
}


