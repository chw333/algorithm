#include <fstream.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 10000
#define ENDMAX 200000

int N, End;
int List[MAXN];
int ListPos[ENDMAX+1];
int MaxLen=1;


#define INFILE "progress05.in"
#define OUTFILE "progress05.out"

#define MAKEN 10000
#define RANGE 11000
int MakePos[ENDMAX+1];

void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEN << endl;
	int i, v, cnt;
	cnt=0;
	while(cnt < MAKEN) {
		v=rand()%RANGE+1;
		if(MakePos[v]==0) {
			cnt++;
			MakePos[v]=1;
		}
	}

	cnt=0;
	for(i=1; i<=ENDMAX; i++) {
		if(MakePos[i]==1) {
			if(cnt!=0) {
				out << " ";
			}
			out << i;
			cnt++;
		}
	}
}


void progress()
{
	int i, v;
	ifstream in(INFILE);
	in >> N;
	for(i=0; i<N; i++) {
		in >> v;
		List[i]=v;
		ListPos[v]=1;
	}
	End=v;

	int j, cnt, deff, enddeff;
	int start, nextstart;
	int expactnum;
	for(i=0; i<N-1; i++) {
		start=List[i];
		nextstart=i+1;
		enddeff=(End+List[i]+1)/2 - start;
		while(1) {
			deff=List[nextstart]-start;
			if(deff > enddeff) break;
		
			//expactnum=(End-start)/deff;
			//if(expactnum > MaxLen) {
				cnt=2;
				for(j=List[nextstart]+deff; j<=End; j+=deff) {
					if(ListPos[j]==1) cnt++;
					else break;
				}

				if(MaxLen < cnt) {
					MaxLen=cnt;
				}
			//}
			nextstart++;
		}
	}


	ofstream out(OUTFILE);
	out << MaxLen;
}


void main()
{
	//makedata();
	progress();
}
