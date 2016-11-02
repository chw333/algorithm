#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<limits.h>

#define MAX 20001

typedef struct _Queue{
	int x,y;
	int count;
	int ul;
	int visit;
} Queue;

static int room[MAX][MAX];
static int remember[MAX][MAX];
Queue queue[400000];
int back[10000][2];
int sx,sy,ex,ey;
int cnt,poin,t,poin1=9999;
void bfs(int,int);

void main()
{
	FILE *fs=fopen("robot.inp","r");
	FILE *fp=fopen("robot.out","w");
	int i,j,numberx,numbery,f;
	char c;
	fscanf(fs,"%d\n",&numberx);
	numbery = numberx;
	sy = 0;sx = 0;ey = numberx-1;ex = numberx-1;
	for(i=0;i<numberx;i++){
		for(j=0;j<numbery;j++){
			fscanf(fs,"%c",&c);
			if(c=='1') room[i][j]=0;
			else room[i][j]=1;
			remember[i][j]=INT_MAX;
		}
		fscanf(fs,"\n");
	}
	bfs(numberx,numbery);
	fprintf(fp,"%d\n",remember[ex][ey]);
	cnt =queue[poin].count;	
	while(poin!=0)
	{
		poin = queue[poin].visit-1;
		if(queue[poin].count != cnt){
			cnt = queue[poin].count;
			back[t][0]=queue[poin].x;
			back[t][1]=queue[poin].y;
			t++;
		}
	}
	for(i=remember[ex][ey]-1;i>=0;i--)fprintf(fp,"%d %d\n",back[i][0]+1,back[i][1]+1);
	fclose(fp);
}
void bfs(int numberx,int numbery)
{
	int i,j,head,tail,k = 0;
	Queue now;
	head=tail=0;
	queue[tail].x=sx;
	queue[tail].y=sy;
	queue[tail].count=0;
	if(room[sx+1][sy]==0) queue[tail].ul=1;
	else queue[tail].ul=2;
	tail++;
	while(head!=tail){
		now=queue[head++];
		if(remember[now.x][now.y]>now.count){
			remember[now.x][now.y]=now.count;
			if(now.ul==1){
				if(now.x-1>=0){
					if(!room[now.x-1][now.y]){
						queue[tail]=now;
						queue[tail].x--;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.x+1<=numberx-1){
					if(!room[now.x+1][now.y]){
						queue[tail]=now;
						queue[tail].x++;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.y-1>=0){
					if(!room[now.x][now.y-1]){
						queue[tail]=now;
						queue[tail].y--;
						queue[tail].ul=2;
						queue[tail].count++;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.y+1<=numbery-1){
					if(!room[now.x][now.y+1]){
						queue[tail]=now;
						queue[tail].y++;
						queue[tail].ul=2;
						queue[tail].count++;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
			}
			else{
				if(now.y-1>=0){
					if(!room[now.x][now.y-1]){
						queue[tail]=now;
						queue[tail].y--;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.y+1<=numbery-1){
					if(!room[now.x][now.y+1]){
						queue[tail]=now;
						queue[tail].y++;
						queue[tail].visit = head;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.x-1>=0){
					if(!room[now.x-1][now.y]){
						queue[tail]=now;
						queue[tail].x--;
						queue[tail].ul=1;
						queue[tail].visit = head;
						queue[tail].count++;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
				if(now.x+1<=numberx-1){
					if(!room[now.x+1][now.y]){
						queue[tail]=now;
						queue[tail].x++;
						queue[tail].ul=1;
						queue[tail].visit = head;
						queue[tail].count++;
						if(queue[tail].x == ex && queue[tail].y == ex && poin1 > queue[tail].count){poin = tail;poin1=queue[tail].count;}
						tail++;
					}
				}
			}
		}
	}
}