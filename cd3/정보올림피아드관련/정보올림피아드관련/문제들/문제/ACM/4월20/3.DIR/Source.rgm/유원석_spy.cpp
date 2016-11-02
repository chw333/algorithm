#include <fstream.h>
int n,x,y,xx,yy,cnt,i;
void main()
{
	ifstream fin ("spy.in");
	fin >> n;
	for(i=0;i<n;i++) {
		fin >> x >> y >> xx >> yy;
		if(x>xx && y>yy) cnt++;
		else if(x>yy && y>xx) cnt++;
	}
	ofstream out ("spy.out");out << cnt;
}