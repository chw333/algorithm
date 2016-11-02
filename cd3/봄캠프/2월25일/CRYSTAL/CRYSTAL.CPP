#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<fstream.h>

static int x[100],y[100];
int n,mx=-1,my=-1,ma=999999,mb=9999999;
double sum=0.00;

int ccw(int ax, int ay, int bx, int by, int cx, int cy)
{
	int l;
	long e;
	double a,b,c,d;
	l = (bx*cy)-(ay*bx)-(ax*cy)-(by*cx)+(ax*by)+(ay*cx);
	a = ay - by;
	b = ax - bx;
	c = 0 - (a * cx + b * cy);
	e = pow(a,2) +pow(b,2);
	d = (double)abs(a * cx + b * cy + c) / (double)sqrt(e);
		
	if (l > 0) return 1;
	else if (l < 0 && (d == 0 || d >= 0.5)) return -1;
	else return 0;
}

void pro()
{
	int i,j,k,ck,co=0,cm=0,cnt=0;
	double p,a,b;

	for (i=ma;i<=mx;i++){
		for (j=mb;j<=my;j++){
			cnt=co=cm=0;
			for (k=0;k<n;k++){
				ck = ccw(x[k],y[k],x[k+1],y[k+1],i,j);
				if (ck == 0) co++;
				else if (ck == 1){
					cm = 1;
					break;
				}
				else if (ck == -1) cnt++;
			}
			ck = ccw(x[n-1],y[n-1],x[0],y[0],i,j);
			if (ck == 0) co++; 
			else if (ck == 1) continue;
			else if (ck == -1) cnt++;
	
			if (co >= 2) continue;
			else if (co == 1 && cm != 1){
				sum += (double)((0.5)*(0.5)*(3.141592)) / 2;
			}
			else if (cm != 1){
				sum += (double)(0.5)*(0.5)*(3.141592);
			}
		}
	}

	p = ((double)((n-2)*180)/360)*(0.5)*(0.5)*(3.141592);
	sum += p;
}

void input()
{
	ifstream in ("crystal.inp");

	in >> n;

	for (int i=0;i<n;i++){
		in >> x[i] >> y[i];
		if (x[i] > mx) mx = x[i];
		if (x[i] < ma) ma = x[i];
		if (y[i] > my) my = y[i];
		if (y[i] < mb) mb = y[i];
	}
}

void output()
{
	FILE *fp=fopen("crystal.out","w");

	fprintf(fp,"%.2lf",sum);
}

void main()
{
	input();
	pro();
	output();
}