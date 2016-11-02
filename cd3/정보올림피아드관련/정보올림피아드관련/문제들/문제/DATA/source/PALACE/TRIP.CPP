/*
ID: cee09001
PROG: spin
*/

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>

#define INFILE "spin.in"
#define OUTFILE "spin.out"

#define N 5
struct SPIN {
	int speed;
	int num;
	int engle[N], extend[N];
} Spin[N];
struct HOLL	{
	int start, extend;
} HollPrev[360], HollNext[360];
int HollprevCnt, HollnextCnt;
int TimeCnt;


void makeholl(struct Holl sour[360], int sourcnt, int spinnum,
			  struct HOLL dest[360], int &destcnt)
{
	destcnt=0;
	int i, j, sourend, destend;
	for(i=0; i<Spin[spinnum].num; i++) {
		for(j=0; j<sourcnt; j++) {
			sourend=sour[j].start+sour[j].extend;
			destend=Spin[spinnum].engle[i] + Spin[spinnum].extend[i];

			if(sourend > 360) {
				if(destend > 360) {
					//두 앵글의 범위가 모두 360을 넘어가는 경우
					sourend-=360;
					destend-=360;
					if(sour[j].start > Spin[spinnum].engle[i]) {
						if(sourend-360 > Spin[spinnum].engle[i]) {
							//겹쳐서 앵글이 두개가 나오는 경우
							dest[destcnt].start=Spin[spinnum].engle[i];
							dest[destcnt].extend=dest[destcnt].start-(sourend-360);
							destcnt++;

							dest[destcnt].start=sour[j].start;
							dest[destcnt].extend=dest[destcnt].start-destend;
							destcnt++;
						} else {
							//하나의 앵글만 나옴.
							dest[destcnt].start=sour[j].start;
							dest[destcnt].extend=(sourend<destend)?
								dest[destcnt].start-sourend : dest[destcnt].start-destend;
							destcnt++;
						}

					} else if(sour[j].start < Spin[spinnum].engle[i]) {
						if(destend-360 > sour[j].start) {
							//겹쳐서 앵글이 두개가 나오는 경우
							dest[destcnt].start=sour[j].start;
							dest[destcnt].extend=dest[destcnt].start-(destend-360);
							destcnt++;

							dest[destcnt].start=Spin[spinnum].engle[i];
							dest[destcnt].extend=(sourend<destend)?
								dest[destcnt].start-sourend : dest[destcnt].start-destend;
							destcnt++;
						} else {
							//하나의 앵글만 나옴.
							dest[destcnt].start=Spin[spinnum].engle[i];
							dest[destcnt].extend=(sourend<destend)?
								dest[destcnt].start-sourend : dest[destcnt].start-destend;
							destcnt++;
						}

					} else {
						dest[destcnt].start=sour[j].start;
						dest[destcnt].extend=(sourend<destend)?
							dest[destcnt].start-sourend : dest[destcnt].start-destend;
						destcnt++;
					}

				} else {
					//sour의 범위만 360을 넘는 경우
					if(sour[j].start >= destend) {
						continue;
					} else {
						//시작 각도는 둘 중에서 큰 것으로 한다.
						dest[destcnt].start=(sour[j].start>Spin[spinnum].engle[i])?
							sour[j].start : Spin[spinnum].engle[i];
						//extend는 무조건 sour가 크므로 destend로 계산한다.
						dest[destcnt].extend=dest[destcnt].start-destend;
						destcnt++;
					}
				}
			} else if(destend > 360) {
				//dest의 범위만 360을 넘는 경우
				if(destend-360 > sour[j].start) {
					//dest가 한바퀴 넘어가서 sour시작 앵글을 넘을 경우
					if(sourend > Spin[spinnum].engle[i]) {
						//두 부분으로 앵글을 따져야 함.
						dest[destcnt].start=sour[j].start;
						dest[destcnt].extend=dest[destcnt].start-(destend-360);
						destcnt++;

						dest[destcnt].start=Spin[spinnum].engle[i];
						dest[destcnt].extend=dest[destcnt].start-sourend;
						destcnt++;
					} else {
						//한 부분 겹침.
						dest[destcnt].start=sour[j].start;
						dest[destcnt].extend=dest[destcnt].start-(destend-360);
						destcnt++;
					}
				} else {
					if(Spin[spinnum].engle[i] >= sourend) {
						continue;
					} else {
						dest[destcnt].start=(sour[j].start>Spin[spinnum].engle[i])?
								sour[j].start : Spin[spinnum].engle[i];
						//extend는 무조건 dest가 크므로 sourend로 계산한다.
						dest[destcnt].extend=dest[destcnt].start-sourend;
						destcnt++;
					}
				}
			} else {
				//두 앵글이 모두 360도 안에서 나오는 경우
				if(sour[j].start > Spin[spinnum].engle[i]) {
					if(sour[j].start >= Spin[spinnum].engle[i] + Spin[spinnum].extend[i]) {
						continue;
					} else {
						dest[destcnt].start=sour[j].start;
						dest[destcnt].extend=(sourend<destend)?
							dest[destcnt].start-sourend : dest[destcnt].start-destend;
						destcnt++;
					}
				} else {
					if(sour[j].start+sour[j].extend <= Spin[spinnum].engle[i]) {
						continue;
					} else {
						dest[destcnt].start=Spin[spinnum].engle[i];
						dest[destcnt].extend=(sourend<destend)?
							dest[destcnt].start-sourend : dest[destcnt].start-destend;
						destcnt++;
					}
				}
			}
		}
		
		
	}
}

int check()
{
	HollnextCnt=1;
	HollNext[0].start=0;
	HollNext[0].extend=360;

	int i,j,k;
	for(i=0; i<N; i++) {
		if(i%2==0) {
			makeholl(HollNext, HollnextCnt, i, HollPrev, HollprevCnt);
			if(HollprevCnt==0) return 0;
		} else {
			makeholl(HollPrev, HollprevCnt, i, HollNext, HollnextCnt);
			if(HollnextCnt==0) return 0;
		}
	}
	return 1;
}

void main()
{
	ifstream in(INFILE);
	int i, j;
	for(i=0; i<N; i++) {
		in >> Spin[i].speed;
		in >> Spin[i].num;
		for(j=0; j<Spin[i].num; j++) {
			in >> Spin[i].engle[j];
			in >> Spin[i].extend[j];
		}
	}

	for(;;) {
		if(check()==1) { break;	}
		for(i=0; i<N; i++) {
			for(j=0; j<Spin[i].num; j++) {
				Spin[i].engle[j]+=Spin[i].speed;
				if(Spin[i].engle[j]>=360) Spin[i].engle[j]-=360;
			}
		}
		TimeCnt++;
		
	}

	ofstream out(OUTFILE);
	out << TimeCnt << endl;
}