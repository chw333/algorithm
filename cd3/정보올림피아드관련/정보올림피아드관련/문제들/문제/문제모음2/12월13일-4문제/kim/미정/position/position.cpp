#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 1000

int N;
int List[MAXN][2];
struct POINT {
	int x, y;
};


#define INFILE "position10.in"
#define OUTFILE "position10.out"

#define MAKEN 100 //최대 100이하.
#define RANGE 1000 //최대 1000이하.

void makedata()
{
	ofstream out(INFILE);
	out << MAKEN << endl;

	srand(time(NULL));
	int i, x, y;
	for(i=0; i<MAKEN; i++) {
		x=rand()%(RANGE+1);
		y=rand()%(RANGE+1);
		out << x << " " << y << endl;
	}
}




void position()
{
	int i, j;
	ifstream in(INFILE);

	in >> N;
	for(i=0; i<N; i++) {
		in >> List[i][0] >> List[i][1];
	}

	//가장 길이가 긴 두 점을 찾기
	struct POINT p, q, mp, mq;
	int maxlen, v;
	maxlen=0;
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			p.x=List[i][0];
			p.y=List[i][1];
			q.x=List[j][0];
			q.y=List[j][1];
			v= (p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
			if( maxlen < v) {
				mp.x=p.x; mp.y=p.y;
				mq.x=q.x; mq.y=q.y;
				maxlen=v;
			}
		}
	}

	double x, y;
	x= (double) (mp.x+mq.x)/2;
	y= (double) (mp.y+mq.y)/2;


	ofstream out(OUTFILE);
	out << x << " " << y;
}


void main()
{
	//makedata();
	position();
}
