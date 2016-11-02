#include<fstream.h>
int n,p[400][4],cnt;
void init()
{
	int i;
	ifstream in ("spy.in");
	in >> n;
	for(i=0;i<n;i++)
		in >> p[i][0] >> p[i][1] >> p[i][2] >> p[i][3];
	in.close();
}
void spy()
{
	int i;
	for(i=0;i<n;i++)
		if(p[i][0]>p[i][2] && p[i][1]>p[i][3])
			cnt++;
}
void output()
{
	ofstream out ("spy.out");
	out << cnt;
	out.close();
}
void main()
{
	init();
	spy();
	output();
}
