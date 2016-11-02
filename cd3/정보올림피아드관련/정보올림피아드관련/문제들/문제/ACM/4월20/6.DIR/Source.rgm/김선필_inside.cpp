#include <fstream.h>
ifstream in("inside.in");
ofstream out("inside.out");
static int n,cnt;
double p[100][2],red[2];
void input()
{
	int i;
	in>>n;
	for(i=0;i<n;i++) in>>p[i][0]>>p[i][1];
	in>>red[0]>>red[1];
}
int ccw(double ax,double ay,double bx,double by,double cx,double cy)
{
	if(((bx-ax)*(cy-ay))-((by-ay)*(cx-ax))>0) return 1;
	else if(((bx-ax)*(cy-ay))-((by-ay)*(cx-ax))<0) return 2;
	else return 0;
}
void process()
{
	int i,j,k,su1,su2,su3;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			for(k=j+1;k<n;k++){
				su1=ccw(p[i][0],p[i][1],p[j][0],p[j][1],red[0],red[1]);
				su2=ccw(p[j][0],p[j][1],p[k][0],p[k][1],red[0],red[1]);
				su3=ccw(p[k][0],p[k][1],p[i][0],p[i][1],red[0],red[1]);
				if(su1==su2&&su2==su3&&su1==su3&&su1!=0) cnt++;
			}
}
void main()
{
	input();
	process();
	out<<cnt;
}