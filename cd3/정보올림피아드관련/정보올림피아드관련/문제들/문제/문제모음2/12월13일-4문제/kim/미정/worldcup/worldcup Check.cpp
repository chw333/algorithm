#include <fstream.h>

#define MAXN 30

int N;
struct LIST {
	int a, b;  //a, b는 국가
};
struct LIST List[MAXN*MAXN]; //n(n-1)/2의 경기가 열림.
int ListCnt;
int PlayCheck[MAXN*MAXN];

struct DAY {
	int Cnt;
	int Play[MAXN][2]; //Play[][0] 도시번호.
};                     //Play[][1] 도시의 몇번째 경기.
struct DAY Day[MAXN];

int Nation[MAXN], City[MAXN];
int CityCheck[MAXN];


#define INFILE "worldcup02.in"
#define OUTFILE "worldcup02.out"
#define ANSFILE "worldcup.ans"

void main()
{
	int i,j,k;
	ifstream in(INFILE);
	in >> N;
	
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			List[ListCnt].a=i;
			List[ListCnt].b=j;
			ListCnt++;
		}
	}

	ifstream outin(OUTFILE);
	//n-1일 체크
	int a, b, c, ok=1;
	char ch;
	for(i=0; i<N-1; i++) {
		for(j=0; j<N; j++) {
			Nation[j]=0;
		}
		for(j=0; j<N-1; j++) {
			City[j]=0;
		}

		for(j=0; j<N/2; j++) {
			outin >> ch >> a >> b >> c >> ch;
			a--;
			b--;
			c--;
			//경기체크 = 모든 경기는 한번씩 나와야 한다.
			for(k=0; k<ListCnt; k++) {
				if(List[k].a==a && List[k].b==b) {
					PlayCheck[k]++;
				}
			}
			if(City[c]==0) {
				City[c]=1; //하루에 도시는 한번 나와야 한다.
				CityCheck[c]++; //총 도시의 수는 N/2가 되야 한다.
			} else { ok=0; }
			if(Nation[a]==0 && Nation[b]==0) {
				Nation[a]=1; //하루에 국가는 한번 나와야 한다.
				Nation[b]=1;
			} else { ok=0; }

		}
	}

	//경기체크
	for(i=0; i<ListCnt; i++) {
		if(PlayCheck[i]!=1) { ok=0; }
	}
	//도시체크
	for(i=0; i<N-1; i++) {
		if(CityCheck[i]!=N/2) { ok=0; }
	}

	ofstream ans(ANSFILE);
	if(ok==0) {
		ans << "no good";
	} else {
		ans << "good";
	}
}