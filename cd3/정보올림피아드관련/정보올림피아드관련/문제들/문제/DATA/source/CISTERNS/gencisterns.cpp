#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#define MAX 10000
ofstream out("cisterns5.in");

int b[MAX];
int h[MAX];
int w[MAX];
int d[MAX];
void main()
{
	int i,j,v=0;
	int flag=0;
    srand((unsigned)time(NULL));
	out << MAX << endl;
	i=0;
	while(i!=MAX) {
		b[i]=rand()%100 ;
		h[i]=rand()%10+1;
		w[i]=rand()%4+1;
		d[i]=rand()%4+1;
		flag=0;
		for(j=0;j<i;j++) {
			if(b[i]==b[j] && h[i]==h[j] && w[i]==w[j] && d[i]==d[j]){
				flag=1;
			}
		}
		if(flag==0) {
			out << b[i] << " " << h[i] << " " << w[i] << " " << d[i];
			out << endl;
			v+=h[i]*w[i]*d[i];
			i++;
		}
	}
	out << v-rand()%v;
}
