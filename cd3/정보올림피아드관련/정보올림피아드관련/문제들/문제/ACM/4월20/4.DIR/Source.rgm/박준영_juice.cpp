#include<fstream.h>
unsigned e,f,p[1000],w[1000],d[20000],i,j,n,flag;
void main()
{
	ifstream in("juice.in");
	in >> e>>f;
	f-=e;
	in >> n;
	for(i=0;i<n;i++){
		in >> p[i]>>w[i];
	}
	for(i=1;i<=f;i++){
		d[i]=2147483644;
		for(j=0;j<n;j++){
			if(i>=w[j]){
				if(d[i]>d[i-w[j]]+p[j]){
					d[i]=d[i-w[j]]+p[j];
				}
			}
		}
	}
	ofstream out("juice.out");
	if(d[f]!=2147483644){out << d[f];}else{out << "impossible";}
}