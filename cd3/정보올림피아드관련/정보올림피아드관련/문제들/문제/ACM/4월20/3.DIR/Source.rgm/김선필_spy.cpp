#include <fstream.h>
#include <math.h>
ifstream in("spy.in");
ofstream out("spy.out");
void main()
{
	int i,n,ax,ay,bx,by,cnt=0;
	in>>n;
	for(i=0;i<n;i++){
		in>>ax>>ay>>bx>>by;
		if((double)sqrt(bx*bx+by*by)<(double)sqrt(ax*ax+ay*ay)) cnt++;
	}
	out<<cnt;
}