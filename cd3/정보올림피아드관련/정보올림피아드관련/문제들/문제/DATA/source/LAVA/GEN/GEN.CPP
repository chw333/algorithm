#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100000
#define CNT 1000
ofstream out("lava5.in");

struct p {
	int x,y;
} pos[MAX];
void main()
{
	int i=0,j;
	int flag;

    srand((unsigned)time(NULL));
	out << MAX << " "<< MAX <<" " << CNT << endl;
	while(i<CNT) {
		flag=0;
		pos[i].x=rand()%MAX+1;
		pos[i].y=rand()%MAX+1;
		for(j=0;j<i;j++){
			if(pos[i].x==pos[j].x && pos[i].y==pos[j].y) flag=1;
		}
		if(flag==0) i++;
	}
	for(i=0;i<CNT;i++)
		out << pos[i].x << " " << pos[i].y << endl;
}
