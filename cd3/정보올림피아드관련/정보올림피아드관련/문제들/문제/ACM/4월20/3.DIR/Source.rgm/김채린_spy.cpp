#include <fstream.h>
int a[401],b[401],x[401],y[401],n,cnt=0,i;
void main()
{
	ifstream in("spy.in");
	in>>n;
	for(i=0; i<n; i++) in>>a[i]>>b[i]>>x[i]>>y[i];
	for(i=0; i<n; i++) if((a[i]>x[i] && b[i]>y[i]) || (a[i]>y[i] && b[i]>x[i])) cnt++;	
	ofstream out("spy.out");
	out<<cnt;
}
