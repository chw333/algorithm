#include <fstream.h>

int c,r,qx[1000000],qy[1000000],chk3[1000][1000];
char board[1003][1003];
bool chk2[1000][1000],chk1[1000][1000];

/*int c,r,qx[1000],qy[1000],chk3[10][10];
char board[13][13];
bool chk2[10][10],chk1[10][10];*/

int large=0,wx[4]={0,0,1,-1}, wy[4]={1,-1,0,0};

void bfs(int gy,int gx)
{
	int i,h=-1,t=0,x,y,ax,ay,l=0;
	qx[0]=gx; qy[0]=gy; chk3[gy][gx]=0;
	chk1[gy][gx]=1; 
	do{
		h++;
		ax=qx[h]; ay=qy[h];
		if(l<chk3[ay][ax]){
			l=chk3[ay][ax];
		}
		for(i=0;i<4;i++){
			x=ax+wx[i]; y=ay+wy[i];
			if(x>=0 && y>=0 && x<r &&  y<c && chk1[y][x]!=1 && board[y][x]=='.'){
				t++;
				qy[t]=y; qx[t]=x;
				chk3[y][x]=chk3[ay][ax]+1;
				chk1[y][x]=1;
			}
		}
	}while(h!=t);
	for(i=0;i<=h;i++)
		chk1[qy[i]][qx[i]]=0;

	if(l>large){
		large=l;
	}

}
void input()
{
	int i;
	ifstream in("animal.in");
	in >> c >> r;
	for(i=0;i<c;i++)
		in >> board[i];
	in.close();
}
void check()
{
	int i,j;
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			if(board[i][j]=='.'){
				if(((i+1<c && board[i+1][j]=='#') || (i+1==c) ) && 
					((j+1<r && board[i][j+1]=='#')||(j+1==r) ||
					(j-1>=0 && board[i][j-1]=='#')||(j-1<0)))
						chk2[i][j]=1;
				else if(
					((i-1<c && board[i-1][j]=='#') || (i-1<0)) && 
					((j+1<r && board[i][j+1]=='#')||(j+1==r) ||
					(j-1>=0 && board[i][j-1]=='#')||(j-1<0)))
						chk2[i][j]=1;
			}
		}
	}
}
void play()
{
	int i,j;
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			if(chk2[i][j]==1)bfs(i,j);
		}
	}
}
void output()
{
	ofstream out("animal.out");
	out << large;
}
void main(){
	input();
	check();
	play();
	output();
}
