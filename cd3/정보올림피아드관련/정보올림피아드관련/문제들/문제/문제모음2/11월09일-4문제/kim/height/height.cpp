#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXVALUE 10000
#define MAXN 1000
#define MAXQ 1000
#define MAXDR 8

int N;

struct POS {
	int x, y;
};
struct POS Line[MAXN];
struct POS Pos[MAXN*MAXN/2];
int PosCnt;

struct VISIT {
	int XCnt;
	int yvalue;
	struct XPOS {
		int x1, x2;
		int value;
	} XPos[MAXN];
};
struct VISIT Visit[MAXN];

int YIndex[MAXVALUE+1];


struct QUEUE {
	int p1, p2;
	int value;
};
struct QUEUE Que[MAXQ];
int Head, Tail;


#define INFILE "height02.in"
#define OUTFILE "height02.out"

#define MAKEN 10
#define XRANGE 80
#define YRANGE 100

int MakeXIndex[XRANGE+1];
int MakeXValue[MAKEN*2];
struct POS MakeLine[MAKEN*4];
int mcnt;

void makedata()
{
	ofstream out(INFILE);
	out << MAKEN*4-1 << endl;
	srand(time(NULL));
	int i, y1, y2, v;

	i=0;
	while(i<MAKEN*2) {
		v=rand()%(XRANGE+1);
		if(MakeXIndex[v]==1) continue;
		MakeXIndex[v]=1;
		i++;
	}
	int xcnt=0;
	for(i=0; i<=XRANGE; i++) {
		if(MakeXIndex[i]==1) {
			MakeXValue[xcnt]=i;
			xcnt++;
		}
	}

	for(i=0; i<xcnt/2; i++) {                   // 2번    3번
		y1=rand()%YRANGE+1;                     //  +------+
		y2=rand()%(y1-1)+1;                     //  |      |
		                                        //  |      |
		//사각형의 1번 점.                      //  |      |
		MakeLine[mcnt].x=MakeXValue[i*2];       //  |      |
		MakeLine[mcnt].y=MakeLine[mcnt-1].y;    //  +      +
		mcnt++;                                 // 1번    4번
        //2번 점.
		MakeLine[mcnt].x=MakeXValue[i*2];
		MakeLine[mcnt].y=y1;
		mcnt++;
		//3번 점.
		MakeLine[mcnt].x=MakeXValue[i*2+1];
		MakeLine[mcnt].y=y1;
		mcnt++;
		//4번 점.
		MakeLine[mcnt].x=MakeXValue[i*2+1];
		MakeLine[mcnt].y=y2;
		mcnt++;
	}

	MakeLine[0].y=0;
	MakeLine[mcnt-1].y=0;

	for(i=0; i<mcnt; i++) {
		out << MakeLine[i].x << " " << MakeLine[i].y << endl;
	}
}






int iabs(int a)
{
	if(a<0) return -a;
	return a;
}

int getvalue(int y, int x1, int x2)
{
	int i, yidx, cnt;
	struct VISIT *visit;
	
	yidx=YIndex[y];
	visit=&Visit[yidx];
	cnt=visit->XCnt;
	for(i=0; i<cnt; i++) {
		if(visit->XPos[i].x1==x1 && visit->XPos[i].x2==x2) {
			return visit->XPos[i].value;
		}
	}
	return -1;
}


void inque(int p1, int p2, int value)
{
	//이미 방문한 놈이면, 큐에 삽입 안함.
	int y, x1, x2;
	x1=Pos[p1].x;
	x2=Pos[p2].x;
	y=Pos[p1].y;
	if(  getvalue(y, x1, x2)!= -1 ) return;

	//방문 설정.
	int yidx;
	struct VISIT *visit;
	
	yidx=YIndex[y];
	visit=&Visit[yidx];
	visit->XPos[visit->XCnt].x1=x1;
	visit->XPos[visit->XCnt].x2=x2;
	visit->XPos[visit->XCnt].value=value;
	visit->XCnt++;

	//큐에 삽입.
	Que[Tail].p1=p1;
	Que[Tail].p2=p2;
	Que[Tail].value=value;

	Tail++;
	if(Tail>=MAXQ) Tail=0;
}
void outque(int &p1, int &p2, int &value)
{
	p1=Que[Head].p1;
	p2=Que[Head].p2;
	value=Que[Head].value;
	
	Head++;
	if(Head>=MAXQ) Head=0;
}
int isempty()
{
	if(Head==Tail) return 1;
	return 0;
}





int bfs()
{
	int i, y, p1, p2,
		value, ycnt;

	for(i=0; i<=MAXVALUE; i++) {
		YIndex[i]=-1;
	}

	ycnt=0;
	for(i=0; i<N; i++) {
		y=Line[i].y;
		if(YIndex[y]==-1) {
			YIndex[y]=ycnt;
			Visit[ycnt].yvalue=y;
			ycnt++;
		}
	}

	int x1, y1, x2, y2;
	int len1, len2;
	int dr[MAXDR][2]= {
		1,  0, -1,  0,  //p1만 움직이는 경우
		0,  1,  0, -1,  //p2만 움직이는 경우
		1,  1,  1, -1,  //동시에 움직이는 경우,
	   -1,  1, -1, -1
	};
	p1=0;
	p2=PosCnt-1;
	inque(p1, p2, 0);

	while( isempty()==0 ) {
		outque(p1, p2, value);
		if( p1==PosCnt-1 && p2==0 ) break;

		for(i=0; i<MAXDR; i++) {
			if(p1+dr[i][0] < 0 || p1+dr[i][0] >= PosCnt) continue;
			if(p2+dr[i][1] < 0 || p2+dr[i][1] >= PosCnt) continue;
			x1=Pos[ p1+dr[i][0] ].x;
			y1=Pos[ p1+dr[i][0] ].y;
			x2=Pos[ p2+dr[i][1] ].x;
			y2=Pos[ p2+dr[i][1] ].y;
			if(y1!=y2) continue;

			len1=iabs(Pos[p1].x-x1)+iabs(Pos[p1].y-y1);
			len2=iabs(Pos[p2].x-x2)+iabs(Pos[p2].y-y2);
			inque(p1+dr[i][0], p2+dr[i][1], value+len1+len2);
		}
	}
	
	return value;
}


void height()
{
	int i, j, x, y;
	ifstream in(INFILE);

	in >> N;
	N++;
	for(i=0; i<N; i++) {
		in >> x >> y;
		Line[i].x=x;
		Line[i].y=y;
		YIndex[y]=1;
	}
	
	//나올 수 있는 점들을 순서대로 Pos배열에 넣음.
	int start, end;
	Pos[PosCnt].x=Line[0].x;
	Pos[PosCnt].y=Line[0].y;
	PosCnt++;
	for(i=1; i<N; i++) {
		if(Line[i-1].x==Line[i].x) {
			//y로만 이동한 것임.
			start=Line[i-1].y;
			end=Line[i].y;
			if(start < end) {
				for(j=start+1; j<=end; j++) {
					if(YIndex[j]==1) {
						Pos[PosCnt].x=Line[i].x;
						Pos[PosCnt].y=j;
						PosCnt++;
					}
				}
			} else {
				for(j=start-1; j>=end; j--) {
					if(YIndex[j]==1) {
						Pos[PosCnt].x=Line[i].x;
						Pos[PosCnt].y=j;
						PosCnt++;
					}
				}
			}
		} else {
			//x로만 이동한 것임.
			Pos[PosCnt].x=Line[i].x;
			Pos[PosCnt].y=Line[i].y;
			PosCnt++;
		}
	}
	

	
	ofstream out(OUTFILE);
	out << bfs();
}


void main()
{
	//makedata();
	height();
}