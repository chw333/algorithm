#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>


#define MAXN 30
#define MAXW 20
#define LIFT 11
#define NOVISIT -1

int N, W;   //N은 회사의 수, M은 리프트의 용량 
struct COMPANY {
    int Profit;
    int Weight;
} Company[MAXN][3];
int Check[MAXN][3];
int MaxProfit;
int Selection[MAXN][2];
int MemFunc[MAXN+1][LIFT+1][MAXW+1];

int AnsCnt; //답이 몇 번 갱신되었는가?
double DfsCnt=1; //회사에서 하나씩 선택하는 경우수는 얼마인가?
int DfsCntCnt;

#define INFILE "lift10.in" 
#define OUTFILE "lift10.out"


#define MAKEN 30
#define MAKEW 20
#define RANGEP 30 //이윤의 범위
#define RANGEW 10 //무게의 범위


void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEN << " " << MAKEW << endl;
	int i, j, p, w;
	for(i=0; i<MAKEN; i++) {
		for(j=0; j<3; j++) {
			if(j!=0) out << " ";
			p=rand()%RANGEP+1;
			w=rand()%RANGEW+1;
			out << p << " " << w;
		}
		out << endl;
	}
}



int calc(int n, int lift, int w)
{
	if(n==1 && lift==1 && w==1) {
		int mp=5;
	}

    if(MemFunc[n][lift][w]!=NOVISIT) return MemFunc[n][lift][w];
    int v1=0, v2=0;
    
    //무게는 Selection[n-1][1]
    //이윤은 Selection[n-1][0] 
    
    //내가 들어가는 경우.
    if(n >= 1 && lift >= 1 && w >= Selection[n-1][1]) {
        v1=calc(n-1, lift-1, w-Selection[n-1][1]);
        v1+=Selection[n-1][0];
    }
    
    //내가 들어가지 않는 경우.
    if(n >= 1) {
        v2=calc(n-1, lift, w);
    }
    
    if(v1 > v2) {
        MemFunc[n][lift][w]=v1;
    } else {
        MemFunc[n][lift][w]=v2;
    }
    
    return MemFunc[n][lift][w];
}


void dfs(int level)
{
    int i,j,k, v;
    if(level==N) {
        //메모리 평션을 위한 배열 초기화. 
        for(i=0; i<=MAXN; i++) {
            for(j=0; j<=LIFT; j++) {
                for(k=0; k<=MAXW; k++) {
                    MemFunc[i][j][k]=NOVISIT;
                }
            }
        }
        
        v=calc(N, LIFT, W);
        if(v > MaxProfit) {
            MaxProfit=v;
			AnsCnt++;
        }
		DfsCntCnt++;
		if(DfsCntCnt %10000==0) cout << DfsCntCnt << endl;
        return;
    }
    
    for(i=0; i<3; i++) {
        if(Check[level][i]==1) {
            Selection[level][0]=Company[level][i].Profit;
            Selection[level][1]=Company[level][i].Weight;
            dfs(level+1);
        }
    }
}


int setcheck(struct COMPANY *p, struct COMPANY *q)
{
	if(p->Profit > q->Profit && p->Weight <= q->Weight) {
		return 1;
	} else if(p->Profit == q->Profit && p->Weight == q->Weight) {
		return 1;
	}
	return 0;
}

void swapcompay(struct COMPANY *p, struct COMPANY *q)
{
    int tmp;
    tmp=p->Profit;
    p->Profit=q->Profit;
    q->Profit=tmp;
    
    tmp=p->Weight;
    p->Weight=q->Weight;
    q->Weight=tmp;
}

void lift()
{
    int i;
    ifstream in(INFILE);
    in >> N >> W;
    for(i=0; i<N; i++) {
        in >> Company[i][0].Profit >> Company[i][0].Weight;
        in >> Company[i][1].Profit >> Company[i][1].Weight;
        in >> Company[i][2].Profit >> Company[i][2].Weight;
        
        Check[i][0]=1;
        Check[i][1]=1;
        Check[i][2]=1;
        
        //sort
        int a, b;
        
        //0번과 1번 비교 
        a=Company[i][0].Profit * Company[i][1].Weight;
        b=Company[i][1].Profit * Company[i][0].Weight;
        if( b > a ) {
            swapcompay(&Company[i][0], &Company[i][1]);
        } else if( a==b && Company[i][1].Profit > Company[i][0].Profit ) {
            swapcompay(&Company[i][0], &Company[i][1]);
        }
        
        //1번과 2번 비교
        a=Company[i][1].Profit * Company[i][2].Weight;
        b=Company[i][2].Profit * Company[i][1].Weight;
        if( b > a ) {
            swapcompay(&Company[i][1], &Company[i][2]);
            
            //다시 바뀌어진 0번과 1번 비교
            a=Company[i][0].Profit * Company[i][1].Weight;
            b=Company[i][1].Profit * Company[i][0].Weight;
            if( b > a ) {
                swapcompay(&Company[i][0], &Company[i][1]);
            } else if( a==b && Company[i][1].Profit > Company[i][0].Profit ) {
                swapcompay(&Company[i][0], &Company[i][1]);
            }
        } else if( a==b && Company[i][2].Profit > Company[i][1].Profit ) {
            swapcompay(&Company[i][1], &Company[i][2]);
        }

		if( setcheck(&Company[i][0], &Company[i][1]) ) Check[i][1]=0;
		if( setcheck(&Company[i][0], &Company[i][2]) ) Check[i][2]=0;
		if( setcheck(&Company[i][1], &Company[i][2]) ) Check[i][2]=0;
		
		/*
        cout << setw(3) << Company[i][0].Profit << "," << setw(3) << Company[i][0].Weight << " | ";
		if(Check[i][1]==1) {
			cout << setw(3) << Company[i][1].Profit << "," << setw(3) << Company[i][1].Weight << " | ";
		} else {
			cout << setw(3) << " " << "," << setw(3) << " " << " | ";
		}
        if(Check[i][2]==1) {
			cout << setw(3) << Company[i][2].Profit << "," << setw(3) << Company[i][2].Weight << endl;
		} else {
			cout << setw(3) << " " << "," << setw(3) << " " << endl;
		}
		*/

		int j, cnt=0;
		for(j=0; j<3; j++) {
			if(Check[i][j]==1) {
				cnt++;
			}
		}
		DfsCnt=DfsCnt*cnt;
    }
    
    printf("회사에서 상품 하나를 뽑아 만들 수 있는 경우수 : %.1lf\n", DfsCnt);
    
	dfs(0);
    cout << "답이 갱신된 회수 : " << AnsCnt << endl;
	cout << "최대 이익 : " << MaxProfit << endl;
	//getch();
    
    ofstream out(OUTFILE);
    out << MaxProfit;
}


void main()
{
	makedata();
	lift();
}