#include <fstream.h>

int n,d[10001],eb,fb;
//int n,d[111],eb,fb;
struct S{
	int p,w;
}a[500];

void input()
{
	int i;
	ifstream in("juice.in");
	in >> eb >>fb >> n;
	for(i=0;i<n;i++){
		in >> a[i].p >> a[i].w; 
	}
}
void play()
{
	int i,j;
	for(i=1;i<=fb-eb;i++){
		for(j=0;j<n;j++){
			if(a[j].w<=i){
				if(i%a[j].w==0){
					if((d[i]==0) || ((i/a[j].w)*a[j].p)<d[i])d[i]=(i/a[j].w)*a[j].p;
				}
				else{
					if(d[i-a[j].w]!=0 && (( ( a[j].p + d[i-a[j].w])<d[i]) || d[i]==0))
						d[i]=a[j].p+d[i-a[j].w];
				}
			}
		}
	}
}
void output()
{
	ofstream out("juice.out");
	if(d[fb-eb]!=0){
		out << d[fb-eb];
	}
	else out << "impossible";
}
void main()
{
	input();
	play();
	output();
}