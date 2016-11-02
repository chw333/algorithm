#include<stdio.h>
#include<fstream.h>

static int check[10001],x[10001][2],y[10001][2];
int max=-99999,locat;
int n;

int intersect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	int t;
	long m;
	float x;
	if(x1==x3 && y1==y3 && x2==x4 && y2==y4)
		return 1;
	if(x1>x2){
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
	}
	if(x3>x4){
		t = x3; x3 = x4; x4 = t;
		t = y3; y3 = y4; y4 = t;
	}
	m=(float)(x4-x3)*(y2-y1)-(float)(y4-y3)*(x2-x1);
	if(m==0)
		return -1;
	x=((float)(y3-y1)*(x2-x1)*(x4-x3)+(float)x1*(y2-y1)*(x4-x3)-(float)x3*(y4-y3)*(x2-x1))/(float)m;
	if(x1<=x&&x<=x2&&x3<=x&&x<=x4) return 1;
	else return -1;
}

void pro()
{
	int i,j;

	for (i=0;i<n;i++){
		for (j=i+1;j<n;j++){
			if (i == j) continue;
			if (x[i][1] < x[j][0]) break;
			if (intersect(x[i][0],y[i][0],x[i][1],y[i][1],x[j][0],y[j][0],x[j][1],y[j][1]) == 1){
				check[i]++;
				check[j]++;
			}
		}
		if (check[i] > max){
			max = check[i];
			locat = i;
		}
	}
}

void sort()
{
	int i,j,t,gap;

	for(gap=1;gap<n/3;gap=3*gap+1);
	while(gap>0){
		for(i=gap;i<=n;i=i++)
			for(j=i-gap;j>0;j-=gap){
				if (x[j][0] > x[j+gap][0] && x[j+gap][0] != 0){
					t = x[j][0];
					x[j][0] = x[j+gap][0];
					x[j+gap][0] = t;
						t = x[j][1];
					x[j][1] = x[j+gap][1];
					x[j+gap][1] = t;
						t = y[j][0];
					y[j][0] = y[j+gap][0];
					y[j+gap][0] = t;
						t = y[j][1];
					y[j][1] = y[j+gap][1];
					y[j+gap][1] = t;
				}
			}
		gap/=3;
	}
}

void input()
{
	int i,t;

	ifstream in ("meteor.inp");

	in >> n;

	for (i=0;i<n;i++){
		in >> x[i][0] >> y[i][0] >> x[i][1] >> y[i][1];

		if(x[i][0] > x[i][1]){
			t= x[i][0];x[i][0] = x[i][1];x[i][1] = t;
			t= y[i][0];y[i][0] = y[i][1];y[i][1] = t;
		}
	}
}

void output()
{
	ofstream out ("meteor.out");

	out << max << "\n";

	out << x[locat][0] << ' ' << y[locat][0] << ' ' << x[locat][1] << ' ' << y[locat][1];
}

void main()
{
	input();
	sort();
	pro();
	output();
}