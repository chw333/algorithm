#include <fstream.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 30

int N;
struct LIST {
	int a, b;  //a, b는 국가
};
struct LIST List[MAXN*MAXN]; //n(n-1)/2의 경기가 열림.
int ListCnt;

int Table[MAXN][MAXN];
struct NATION {
	int NationCnt;
	int DayCnt;
	int Nation[MAXN+1];
	int Day[MAXN];
};
struct NATION City[MAXN], Day[MAXN];


#define INFILE "worldcup01.in"
#define OUTFILE "worldcup.out"


void print()
{
	int i,j;
	
	for(j=1; j<=N; j++) {
		cout << setw(3) << j;
	}
	cout << endl;		
	for(i=1; i<=N; i++) {
		for(j=1; j<=N; j++) {
			cout << setw(3) << Table[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


int dfs(int day, int city, int num)
{
	int i, j, n1, n2;
	int nn1, nn2;
	
	Table[day][city]=num;
	n1=List[num].a;
	n2=List[num].a;
	City[city].NationCnt++;
	City[city].Nation[n1]=1;
	City[city].Nation[n2]=1;
	City[city].DayCnt++;
	City[city].Day[day]=1;
	Day[day].NationCnt++;
	Day[day].Nation[n1]=1;
	Day[day].Nation[n2]=1;
	print();

	if(num==ListCnt) {
		for(i=1; i<N; i++) {
			if(Day[i].NationCnt == N/2) {
			} else {
				return 0;
			}
		}
		for(j=1; j<=N; j++) {
			if(City[j].NationCnt == N/2) {
			} else {
				return 0;
			}
		}
		return 1;

	} else {
		nn1=List[num+1].a;
		nn2=List[num+1].b;
		
		for(i=1; i<N; i++) {
			if(Day[i].NationCnt < N/2) {
				for(j=1; j<N; j++) {
					if(Table[i][j]==0 && 
					  Day[i].Nation[nn1]==0 && Day[i].Nation[nn2]==0 &&
					  City[j].NationCnt < N/2 &&
					  City[j].Nation[nn1]==0 && City[j].Nation[nn2]==0 ) {
						if(dfs(i, j, num+1)==1) {
							return 1;
						}
					}
				}
			}
		}
	}

	City[city].NationCnt--;
	City[city].Nation[n1]=0;
	City[city].Nation[n2]=0;
	City[city].DayCnt--;
	City[city].Day[day]=0;
	Day[day].NationCnt--;
	Day[day].Nation[n1]=0;
	Day[day].Nation[n2]=0;
	Table[day][city]=0;

	return 0;
}


void main()
{
	int i,j, idx, cnt;
	ifstream in(INFILE);
	in >> N;
	
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			ListCnt++;
			List[ListCnt].a=i;
			List[ListCnt].b=j;
		}
	}

	ofstream out(OUTFILE);
	if(dfs(1, 1, 1)==1) {
		for(i=1; i<=N; i++) {
			cnt=0;
			for(j=1; j<=N; j++) {
				idx=Table[i][j];
				if(idx!=0) {
					if(cnt!=0) out << " ";
					out << "(" << List[idx].a << " " << List[idx].b << " " 
						<< j << ")";
					cnt++;
				}
			}
			out << endl;
		}
	} else {
		out << "no";
	}
}