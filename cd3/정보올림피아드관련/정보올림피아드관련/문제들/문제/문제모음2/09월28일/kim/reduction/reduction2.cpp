#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define INFILE "reduction10.in"
#define OUTFILE "reduction10.out"

#define MAXN 50
#define MAXM 100
#define INFINIT 100000

int N, M;
int Employee[MAXM];         //ȸ����� ���� 
int TotalEmployee;          //ȸ������� �ִ� ������ �� ��. 
int Profit[MAXN];           //����� ���� 
int Business[MAXN][MAXM+1]; //����� ������ ȸ���


int ChkBusiness[MAXN];
int Participation[MAXM];
int MaxProfit;
int GiveupPath[MAXN];

int Flow[MAXN+MAXM+2][MAXN+MAXM+2];
int FlowPath[MAXN+MAXM+2];
int Visit[MAXN+MAXM+2];
int FlowCnt, FlowFlag;

int getpath(int node, int cnt)
{
    int i;
    int end=N+M+1;
    FlowPath[cnt]=node;
    if( node==end ) {
        FlowCnt=cnt+1;
        return 1;
    }
    
    Visit[node]=1;
    
    for(i=1; i<=end; i++) {
        if( Flow[node][i] !=0 && Visit[i]==0 ) {
            if( getpath(i, cnt+1)== 1) return 1;
        }
    }
    
    return 0;
}

void main()
{
    int i,j, cnt;
    ifstream in(INFILE);
    in >> N >> M;
    for(i=0; i<N; i++) {
        in >> cnt;
        Business[i][0]=cnt;
        for(j=1; j<=cnt; j++) {
            in >> Business[i][j];
            Business[i][j]--;
        }
    }
    for(i=0; i<N; i++) {
        in >> Profit[i];
    }
    for(i=0; i<M; i++) {
        in >> Employee[i];
        TotalEmployee+=Employee[i];
    }
    
    //-----------------------
    //flow ���� 
    //-----------------------
    //÷�ڿ� 1�� ���� ����
    //0���� �ҽ��̰�, ����� 1�� ���� �����ϱ� �����̴�. 
    
    //����� ���� ���� 
    for(i=0; i<M; i++) {
        Flow[0][i+1]= Employee[i];
    }
    //����� ���ͱ� ����
    for(i=0; i<N; i++) {
        Flow[M+i+1][N+M+1]= Profit[i];
    }
    //����� ����� ���� ����.
    int start, end;
    for(i=0; i<N; i++) {
        cnt=Business[i][0];
        for(j=1; j<=cnt; j++) {
            start=Business[i][j];
            end=i;
            Flow[start+1][M+end+1]= Employee[start];
        }
    } 

    /*
    end=N+M+1;
    for(i=0; i<=end; i++) {
        for(j=0; j<=end; j++) {
            cout << setw(3) << Flow[i][j];
        }
        cout << endl;
    }
    cout << endl;
    getch();*/
    
    //-----------------------
    //��� ����. 
    //-----------------------
    int min;
    end=N+M+1;
    while( 1 ) {
        for(i=1; i<=end; i++) {
            Visit[i]=0;
        }
        if( getpath(0, 0)==0 ) { break; }
        
        //����
        min=INFINIT;
        for(i=1; i<FlowCnt; i++) {
            start=FlowPath[i-1];
            end=FlowPath[i];
            if(min > Flow[start][end]) min=Flow[start][end];
        }
        for(i=1; i<FlowCnt; i++) {
            start=FlowPath[i-1];
            end=FlowPath[i];
            Flow[start][end]-=min;
            Flow[end][start]+=min;
        }
        MaxProfit+=min;
    } 
    
    ofstream out(OUTFILE);
    out << TotalEmployee-MaxProfit;
    
}

