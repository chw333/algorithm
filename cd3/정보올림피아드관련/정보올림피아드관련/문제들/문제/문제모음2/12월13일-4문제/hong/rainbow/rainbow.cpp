#include <fstream.h>
#include <math.h>

#define MAXP 4000 //2000
#define MAXS 4000 //2000
#define M_PI 3.141592653589793238462643383267950288419716939937510

ifstream in("rainbow05.in");
ofstream out("rainbow05.out");

struct _p {
	int x;
	int y;
	int d;
} P[MAXP];

struct _s {
	int x;
	int y;
	int r;
} S[MAXS];
struct _l {
	int x1, y1, x2, y2;
} L[4];
int W, Pcnt, Scnt, Dcnt; // 적군의 너비, 적군의 수, 총알 수, 죽은 사람의 수

void inp()
{
	int i;
	in >> W;
	in >> Pcnt;
	for(i=0;i<Pcnt;i++) in >> P[i].x >> P[i].y;
	in >> Scnt;
	for(i=0;i<Scnt;i++) in >> S[i].x >> S[i].y >> S[i].r;
}

void oup()
{
	out << Dcnt;
}

void proc()
{
	int i, j, k;
	double ang1,ang2,ang3;
	
	for(i=0;i<Scnt;i++) {
		for(j=0;j<Pcnt;j++) {
			if(P[j].d) continue;
			L[0].x1=P[j].x-W/2;
			L[0].y1=P[j].y-W/2;
			L[0].x2=P[j].x-W/2;
			L[0].y2=P[j].y+W/2;

			L[1].x1=P[j].x-W/2;
			L[1].y1=P[j].y+W/2;
			L[1].x2=P[j].x+W/2;
			L[1].y2=P[j].y+W/2;

			L[2].x1=P[j].x+W/2;
			L[2].y1=P[j].y+W/2;
			L[2].x2=P[j].x+W/2;
			L[2].y2=P[j].y-W/2;

			L[3].x1=P[j].x+W/2;
			L[3].y1=P[j].y-W/2;
			L[3].x2=P[j].x-W/2;
			L[3].y2=P[j].y-W/2;
			for(k=0;k<4;k++) {
				ang1=atan2(L[k].y1-S[i].y,L[k].x1-S[i].x)*180/M_PI;
				if(ang1<0) ang1=360+ang1;
				ang2=atan2(L[k].y2-S[i].y,L[k].x2-S[i].x)*180/M_PI;
				if(ang2<0) ang2=360+ang2;
				ang3=S[i].r;
				if(ang1>ang2) {
					if(ang1-ang2>=180) {
						if(ang3>=ang1 || ang3<=ang2) { P[j].d=1; Dcnt++; break; }
					} else {
						if(ang3<=ang1 && ang3>=ang2) { P[j].d=1; Dcnt++; break; }
					}
				} else {
					if(ang2-ang1>=180) {
						if(ang3>=ang2 || ang3<=ang1) { P[j].d=1; Dcnt++; break; }
					} else {
						if(ang3<=ang2 && ang3>=ang1) { P[j].d=1; Dcnt++; break; }
					}
				}
			}
		}
	}
}

void main()
{
	inp();
	proc();
	oup();
}






