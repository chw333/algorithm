#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 100000 
#define Lx 100000
#define PI 3.1415926535897932384626433832795

struct Point {
	double x;
	double y;
	double a;
	double d;
} P[Nx], Q[Nx], C[Nx];

struct Line {
	struct Point s;
	struct Point e;
} L[Nx];

struct Angle {
	double s; // <=
	double e; // >
	int p1;
	int p2;
} A[Nx];

int Np, Nl, Si[Nx], Qi, Ci, Ai;

ifstream in ("dwarfs.in");
ofstream out("dwarfs.out");

void input()
{
	int i;
	char p[81];
	in>>Np;
	for(i=0; i<Np; i++){
		Si[i]=i;
		in>>P[i].x>>P[i].y;
	}
	Nl=0;
	in.getline(p, 80);
	while(1){
		in.getline(p, 80);
		if(p[0]=='\0') break;
		sscanf(p, "%lf %lf %lf %lf", &L[Nl].s.x, &L[Nl].s.y, &L[Nl].e.x, &L[Nl].e.y);
		Nl++;
	}
}	

int s_f(const void *a, const void *b)
{
	int AA=*(int*)a;
	int BB=*(int*)b;
	if(P[AA].a>P[BB].a) return 1;
	else if(P[AA].a<P[BB].a) return -1;
	if(P[AA].d<P[BB].d) return 1;
	else if(P[AA].d>P[BB].d) return -1;
	return 0;
}

void getpoint()
{
	int i, mini;
	double x, y;
	struct Point min, tp;
	min=P[0]; mini=0; 
	for(i=1; i<Np; i++){
		if(P[i].y<min.y){
			min=P[i];
			mini=i;
		} else if(P[i].y==min.y && P[i].x<min.x){
			min=P[i];
			mini=i;
		}
	}
	if(mini!=0) {
		tp=P[0];
		P[0]=P[mini];
		P[mini]=tp;
	}
	for(i=1; i<Np; i++){
		x=P[i].x-P[0].x;
		y=P[i].y-P[0].y;
		P[i].a=atan2(y,x);
		P[i].d=x*x+y*y;
	}
	qsort(&Si[1], Np-1, sizeof(Si[1]), s_f);
	Q[0]=P[0];
	tp=Q[1]=P[Si[1]];
	Qi=2;
	for(i=2; i<Np; i++){
		if(tp.a==P[Si[i]].a){
			continue;
		} else {
			tp=Q[Qi++]=P[Si[i]];
		}
	}
}

void push(struct Point p)
{
	C[Ci++]=p;
}

struct Point pop()
{
	return C[--Ci];
}

int ccw(struct Point o, struct Point p1, struct Point p2)
{
	double a=(p1.x-o.x);
	double b=(p1.y-o.y);
	double c=(p2.x-o.x);
	double d=(p2.y-o.y);
	double r=a*d-b*c;
	if(r<0) return -1;
	else if(r>0) return 1;
	return 0;
}

void convex()
{
	int i;
	Ci=0;
	push(Q[0]);
	push(Q[1]);
	push(Q[2]);
	for(i=3; i<Qi; i++) {
		while(0>=ccw(C[Ci-2],C[Ci-1],Q[i])) {
			pop();
		}
		push(Q[i]);
	}
}

void getangle()
{
	int i, s, e, ts, te, t;
	double sa=0.0, ea=0.0, ta, tt;
	s=0;
	tt=C[1].y;e=1;
	for(i=2; i<Ci; i++){
		if(tt<C[i].y){
			tt=C[i].y;
			e=i;
		}
	}
	ts=s;
	te=e;
	ta=0;
	Ai=0;
	while(1){
		t=s+1;
		if(t==Ci)t=0;
		sa=atan2(C[t].y-C[s].y, C[t].x-C[s].x);
		if(sa<0) sa=2*PI+sa;
		t=e+1;
		if(t==Ci)t=0;
		ea=atan2(C[e].y-C[t].y, C[e].x-C[t].x);
		if(ea<0) ea=2*PI+sa;
		if(sa<ea){
			A[Ai].p1=s;
			A[Ai].p2=e;
			A[Ai].s=ta;
			if(sa>PI) {
				A[Ai++].e=PI+1;
				break;
			} else {
				ta=A[Ai++].e=sa;
			}
			s++;
		} else {
			A[Ai].p1=s;
			A[Ai].p2=e;
			A[Ai].s=ta;
			if(ea>PI){
				A[Ai++].e=PI+1;
				break;
			} else {
				ta=A[Ai++].e=ea;
			}
			e++;
		}		
		if(s==Ci) s=0;
		if(e==Ci) e=0;
	}
}

void process()
{
	if(Np==0){
		Ai=0;
	} else {
		if(Np==1){
			Ai=1;
			C[0]=P[0];
			A[0].p1=0;
			A[0].p2=0;
			A[0].s=0;
			A[0].e=PI;
		} else {
			if(Np==2){
				C[0]=P[0];
				C[1]=P[0];
				Ci=2;
			} else {
				getpoint();
				convex();
			}
			getangle();
		}
	}	
}

void output()
{
	int i, l, m, h;
	double la;
	for(i=0; i<Nl; i++){
		if(i!=0) out<<endl;
		if(Ai==0) {
			out<<"GOOD";
			continue;
		}
		la=atan2((L[i].e.y-L[i].s.y),(L[i].e.x-L[i].s.x));
		if(la<0) la+=PI;
		l=0; h=Ai-1;
		while(1){
			m=(l+h)/2;
			if(la<A[m].s){ 
				h=m-1;		
			}else if(la>=A[m].e){
				l=m+1;
			}else{
				break;
			}
		}
		if(ccw(L[i].s,L[i].e,C[A[m].p1])*
		   ccw(L[i].s,L[i].e,C[A[m].p2])>0){
			out<<"GOOD";
		} else {
			out<<"BAD";
		}
	}
}

void main()
{
	input();
	process();
	output();
}