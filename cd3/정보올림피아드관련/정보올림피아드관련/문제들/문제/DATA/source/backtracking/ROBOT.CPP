#include <fstream.h>

ifstream in("robot.in");
ofstream out("robot.out");
struct q {
	int x;
	int y;
	int dir;
	int turn;
} qu[44000];
int head, tail;
char table[201][201];
int minturn=99999;
int dx, dy, sx, sy, ex, ey;

void inp()
{
	int i,j;

	in >> dx >> dy;
	in >> sx >> sy >> ex >> ey;
	sx--; sy--; ex--; ey--;
	for(i=0;i<dy;i++) {
		for(j=0;j<dx;j++) {
			in >> table[i][j];
			table[i][j]=table[i][j]-'0';
		}
	}
}
void oup()
{
	out << minturn-2;
}
void inqu(struct q data)
{
	tail++;
	if(tail<44000) {
		qu[tail].y=data.y;
		qu[tail].x=data.x;
		qu[tail].dir=data.dir;
		qu[tail].turn=data.turn;
	}
}
struct q outqu()
{
	struct q ret;
	head++;
	if(head<44000) {
		ret.x=qu[head].x;
		ret.y=qu[head].y;
		ret.dir=qu[head].dir;
		ret.turn=qu[head].turn;
	}
	return ret;
}
int qempty()
{
	if(head==tail) return 1;
	else return 0;
}
void proc()
{
	struct q temp;
	int i,j;
	int turn=2;
	int olddir; // 1-left, 2-down, 3-right, 4-up
	int oldturn,oldx,oldy;

	temp.x=sx; temp.y=sy; temp.dir=0; // ½ÃÀÛ°ª.
	temp.turn=turn;
	table[temp.y][temp.x]=temp.turn;
	inqu(temp);
	while(!qempty()){
		temp=outqu();
		olddir=temp.dir;
		oldx=temp.x;
		oldy=temp.y;
		oldturn=temp.turn;
		if(temp.x==ex && temp.y==ey && minturn>temp.turn) minturn=temp.turn;
		if(oldx+1<dx && (table[oldy][oldx+1]==0 || table[oldy][oldx+1]>oldturn)) {
			temp.dir=1; 
			temp.x=oldx+1;
			temp.y=oldy;
			temp.turn=oldturn;
			if(olddir && olddir%2!=temp.dir%2) { 
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn; 
				inqu(temp);
			} else if(olddir==0) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn; 
				inqu(temp);
			}
		}
		if(oldy+1<dy && (table[oldy+1][oldx]==0  || table[oldy+1][oldx]>oldturn)) {
			temp.dir=2; 
			temp.y=oldy+1; 
			temp.x=oldx;
			temp.turn=oldturn;
			if(olddir && olddir%2!=temp.dir%2) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn;
				inqu(temp); 
			} else if(olddir==0) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn; 
				inqu(temp);
			}
		}
		if(oldx-1>=0 && (table[oldy][oldx-1]==0 || table[oldy][oldx-1]>oldturn)) {
			temp.dir=3; 
			temp.x=oldx-1; 
			temp.y=oldy;
			temp.turn=oldturn;
			if(olddir && olddir%2!=temp.dir%2) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn;
				inqu(temp); 
			} else if(olddir==0) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn; 
				inqu(temp);
			}
		}
		if(oldy-1>=0 && (table[oldy-1][oldx]==0 || table[oldy-1][oldx]>oldturn)) {
			temp.dir=4; 
			temp.y=oldy-1; 
			temp.x=oldx;
			temp.turn=oldturn;
			if(olddir && olddir%2!=temp.dir%2) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn;
				inqu(temp); 
			} else if(olddir==0) {
				if(table[temp.y][temp.x]>oldturn+1) temp.turn=oldturn+1; else temp.turn=oldturn;
				table[temp.y][temp.x]=temp.turn; 
				inqu(temp);
			}
		}
		for(i=0;i<dy;i++) {
			for(j=0;j<dx;j++) {
				out << (int)table[i][j];
			}
			out << endl;
		}
		out << endl;
	}
}
void main()
{
	int i,j;
	inp();
	proc();
	oup();
}
