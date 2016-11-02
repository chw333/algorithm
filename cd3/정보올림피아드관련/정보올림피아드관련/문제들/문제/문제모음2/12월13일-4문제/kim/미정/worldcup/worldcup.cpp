#include <fstream.h>
#include <string.h>

#define MAXN 30

int N;
struct LIST {
	int a, b;  //a, b는 국가
};
struct CITY {
	int Play[MAXN/2]; //열리는 경기 번호
};
struct LIST List[MAXN*MAXN]; //n(n-1)/2의 경기가 열림.
int ListCnt;

int Visit[MAXN*MAXN]; //Visit[i] i번째 경기를 방문했는지 기록
struct CITY City[MAXN]; //City[i]  i번째 도시에서 열리는 경기 기록.
int IsAnswer;
int IsDisplay;
struct CITY BkCity[MAXN*1000][MAXN];
int BkCityCnt;


#define INFILE "worldcup01.in"
#define OUTFILE "worldcup.out"


//city는 도시 번호
//playcnt는 그 도시에서 세팅되는 경기 카운트.
//playnum은 열리는 경기 번호.
void dfs(int city, int playcnt, int playnum)
{
	if(IsAnswer==1) return;
	int i, idx, ok=0;
	int n1, n2;
	int nation[MAXN]={0,};
	int newplaynum=playnum;
	Visit[playnum]=1;
	City[city].Play[playcnt]=playnum;
	playcnt++;
	if(playcnt==N/2) {
		city++;
		playcnt=0;
		newplaynum=0;
		if(city==N-1) {
			IsAnswer=1;
			ok=1;
			memmove(BkCity[BkCityCnt], City, sizeof(City) );
			BkCityCnt++;
			return;
		}
	}
	if(ok==0) {

		for(i=0; i<playcnt; i++) {
			idx = City[city].Play[i];
			n1=List[idx].a;
			n2=List[idx].b;
			nation[n1]=1;
			nation[n2]=1;
		}

		for(i=newplaynum+1; i<ListCnt; i++) {
			//i 경기가 열린적이 없어야 하고,
			//한 도시에서 열린 국가가 또 열리지 말아야 한다.
			if(Visit[i]==0 ) {
				n1=List[i].a;
				n2=List[i].b;
				if(nation[n1]==0 && nation[n2]==0) {
					dfs(city, playcnt, i);
					if(IsAnswer==1) return;
				}
			}
			
		}

	}

	Visit[playnum]=0;
	playcnt--;
	if(playcnt<0) {
		city--;
		playcnt=N/2-1;
	}
	City[city].Play[playcnt]=-1;
}

struct DAY {
	int Play[MAXN][2]; //Play[][0] 도시번호.
};                     //Play[][1] 도시의 몇번째 경기.
struct DAY Day[MAXN];
int VisitCity[MAXN][MAXN];
                               //city=도시번호. cityplay=도시의 몇번째 경기.
void dfs2(int day, int daycnt, int city, int cityplay)
{
	if(IsDisplay==1) return;
	int i, j, idx, ck_city, ck_cityplay;
	int n1, n2;
	int nation[MAXN]={0,};
	int newcity=city+1, newcityplay=cityplay;

	VisitCity[city][cityplay]=1;
	Day[day].Play[daycnt][0]=city;
	Day[day].Play[daycnt][1]=cityplay;
	daycnt++;
	if(daycnt==N/2) {
		day++;
		daycnt=0;
		newcity=0;
		newcityplay=0;

		if(day==N-1) {
			IsDisplay=1;
			return;
		}
	}

	for(i=0; i<daycnt; i++) {
		ck_city= Day[day].Play[i][0];
		ck_cityplay= Day[day].Play[i][1];
		idx=City[ck_city].Play[ck_cityplay];
		n1=List[idx].a;
		n2=List[idx].b;
		nation[n1]=1;
		nation[n2]=1;
	}

	for(i=newcity; i<N-1; i++) {
		for(j=0; j<N/2; j++) {
			if(VisitCity[i][j]==0 ) {
				idx=City[i].Play[j];
				n1=List[idx].a;
				n2=List[idx].b;
				if(nation[n1]==0 && nation[n2]==0) {
					dfs2(day, daycnt, i, j);
					if(IsDisplay==1) return;
				}
			}
		}		
	}

	VisitCity[city][cityplay]=0;
	daycnt--;
	if(daycnt<0) {
		day--;
		daycnt=N/2-1;
	}
	Day[day].Play[daycnt][0]=-1;
	Day[day].Play[daycnt][1]=-1;
}

void main()
{
	int i,j;
	ifstream in(INFILE);
	in >> N;
	
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			List[ListCnt].a=i;
			List[ListCnt].b=j;
			ListCnt++;
		}
	}

	dfs(0, 0, 0);

	int line=0, x=0, idx;
	int city, cityplay;
	ofstream out(OUTFILE);
	for(i=0; i<BkCityCnt; i++) {
		memmove(City, BkCity[i], sizeof(City));
		dfs2(0, 0, 0, 0);
		if(Day[0].Play[0][0]!=-1) break;
	}
	if(i==BkCityCnt) {
		out << "no";
	} else {
		for(i=0; i<N-1; i++) {
			for(j=0; j<N/2; j++) {
				if(j!=0) out << " ";
				city=Day[i].Play[j][0];
				cityplay=Day[i].Play[j][1];
				idx=City[city].Play[cityplay];
				out << "(" << List[idx].a+1 << " " << List[idx].b+1 << " "
					<< city+1 << ")";
			}
			out << endl;
		}
	}
}