#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define MAX 100

static int x[MAX];
static int y[MAX];
static int room[MAX][MAX];
static int process[MAX];

int xcount=0,ycount=0,polygon_count=2;

typedef struct _line{
	int x1,y1;
	int x2,y2;
} line;

int int_cmp(const void *a,const void *b)
{
	return *(int *)a-*(int *)b;
}

void devide(line l[],int number)
{
	int i,j,a;
	for(i=0;i<number;i++){
		a=l[i].x1;
		if(!xcount){
			x[xcount++]=a;
		}
		else{
			for(j=0;j<xcount;j++){
				if(x[j]==a) break;
				if(j==xcount-1) x[xcount++]=a;
			}
		}
		a=l[i].x2;
		for(j=0;j<xcount;j++){
			if(x[j]==a) break;
			if(j==xcount-1) x[xcount++]=a;
		}
		a=l[i].y1;
		if(!ycount){
			y[ycount++]=a;
		}
		else{
			for(j=0;j<ycount;j++){
				if(y[j]==a) break;
				if(j==ycount-1) y[ycount++]=a;
			}
		}
		a=l[i].y2;
		for(j=0;j<ycount;j++){
			if(y[j]==a) break;
			if(j==ycount-1) y[ycount++]=a;
		}
	}
}

void fill(line l[],int number,int xv,int yv)
{
	int i,j,k;
	if(!room[xv-1][yv]&&xv-1>=0){
		for(k=0;k<number;k++){
			if(l[k].y1==l[k].y2&&l[k].y1==y[xv]){
				if(l[k].x1>=x[yv] && l[k].x2<=x[yv+1]){
					break;
				}
			}
			if(k==number-1){
				room[xv-1][yv]=room[xv][yv];
				fill(l,number,xv-1,yv);
			}
		}
	}
	if(!room[xv+1][yv]&&xv+1<ycount-1){
		for(k=0;k<number;k++){
			if(l[k].y1==l[k].y2&&l[k].y1==y[xv+1]){
				if(l[k].x1>=x[yv] && l[k].x2<=x[yv+1]){
					break;
				}
			}
			if(k==number-1){
				room[xv+1][yv]=room[xv][yv];
				fill(l,number,xv+1,yv);
			}
		}
	}
	if(!room[xv][yv-1]&&yv-1>=0){
		for(k=0;k<number;k++){
			if(l[k].x1==l[k].x2&&l[k].x1==x[yv]){
				if(l[k].y1>=y[xv] && l[k].y2<=y[xv+1]){
					break;
				}
			}
			if(k==number-1){
				room[xv][yv-1]=room[xv][yv];
				fill(l,number,xv,yv-1);
			}
		}
	}
	if(!room[xv][yv+1]&&yv+1<xcount-1){
		for(k=0;k<number;k++){
			if(l[k].x1==l[k].x2&&l[k].x1==x[yv+1]){
				if(l[k].y1>=y[xv] && l[k].y2<=y[xv+1]){
					break;
				}
			}
			if(k==number-1){
				room[xv][yv+1]=room[xv][yv];
				fill(l,number,xv,yv+1);
			}
		}
	}
}
void getS()
{
	int i,j,disx,disy;
	for(i=0;i<ycount-1;i++){
		for(j=0;j<xcount-1;j++){
			disx=x[j+1]-x[j];
			disy=y[i+1]-y[i];
			process[room[i][j]-1]+=disx*disy;
		}
	}
}


void main()
{
	FILE *fs=fopen("q4.inp","r");
	FILE *fp=fopen("q4.out","w");
	int i,j,number,a,b,c,d,xvalue,yvalue,e,f,g,h;
	line l[MAX];
	fscanf(fs,"%d %d %d %d\n",&a,&b,&c,&d);
	fscanf(fs,"%d\n",&number);
	for(i=0;i<number;i++){
		fscanf(fs,"%d %d %d %d\n",&e,&f,&g,&h);
		if(e>g){
			l[i].x1=g;
			l[i].x2=e;
			l[i].y1=f;
			l[i].y2=h;
			continue;
		}
		if(f>h){
			l[i].x1=g;
			l[i].x2=e;
			l[i].y1=h;
			l[i].y2=f;
			continue;
		}
		l[i].x1=e;
		l[i].y1=f;
		l[i].x2=g;
		l[i].y2=h;
	}
/*	l[number].x1=a;
	l[number].y1=c;
	l[number].x2=b;
	l[number++].y2=c;
	l[number].x1=b;
	l[number].y1=c;
	l[number].x2=b;
	l[number++].y2=d;
	l[number].x1=b;
	l[number].y1=d;
	l[number].x2=a;
	l[number++].y2=d;
	l[number].x1=a;
	l[number].y1=b;
	l[number].x2=a;
	l[number++].y2=c;*/
	devide(l,number);
	for(i=0;i<xcount;i++){
		if(x[i]==a) break;
		if(i==xcount-1) x[xcount++]=a;
	}
	for(i=0;i<xcount;i++){
		if(x[i]==b) break;
		if(i==xcount-1) x[xcount++]=b;
	}
	for(i=0;i<ycount;i++){
		if(y[i]==c) break;
		if(i==ycount-1) y[ycount++]=c;
	}
	for(i=0;i<ycount;i++){
		if(y[i]==d) break;
		if(i==ycount-1) y[ycount++]=d;
	}
	qsort(x,xcount,sizeof(x[0]),int_cmp);
	qsort(y,ycount,sizeof(y[0]),int_cmp);
	for(i=0;i<xcount-1;i++){
		for(j=0;j<ycount-1;j++){
			if(!room[j][i]){
				room[j][i]=polygon_count-1;
				fill(l,number,i,j);
				polygon_count++;
			}
		}
	}
	getS();
	fprintf(fp,"%d\n",polygon_count-2);
	for(i=0;i<polygon_count-2;i++){
		fprintf(fp,"%d\n",process[i]);
	}
}