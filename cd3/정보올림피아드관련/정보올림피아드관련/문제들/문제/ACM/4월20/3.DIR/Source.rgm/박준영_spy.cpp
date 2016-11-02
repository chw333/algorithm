#include<fstream.h>
#include<math.h>
int n,cnt,x,y,a,b,i;
void main()
{
	ifstream in("spy.in");
	in >> n;
	for(i=0;i<n;i++){
		in >> a>>b>>x>>y;
		if((a>x&&b>y)||(a>y&&b>x)||sqrt(a*a+b*b)>x+y){cnt++;}
	}
	ofstream out("spy.out");
	out << cnt; 
}