#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>


#define MAXN 50
#define MAXM 100

int N, M;
int Employee[MAXM];        //회사원의 연봉 
int Profit[MAXN];          //사업의 수익 
int Business[MAXN][MAXM+1]; //사업에 참여한 회사원 

int ChkBusiness[MAXN];
int Participation[MAXM];
int MaxProfit;
int GiveupPath[MAXN];


#define MakeN 46 //사업의 수 
#define MakeM 80 //회사원의 수 
#define RANGE (MakeN*1/5) //사업에 참여하는 회사원의 범위 
#define RANGEProfit 100 //사업의 이익금 범위 
#define RANGEEmployee 50 //회사원의 연봉 범위 

#define INFILE "reduction09.in"
#define OUTFILE "reduction09.out"


void makedata()
{
    int i,j,k;
    int cnt, employee, v;
    int e_arr[MAXM];
    int e_all_arr[MAXN][MAXM+1];
    ofstream out(INFILE);
    out << MakeN << " " << MakeM << endl;
    
    srand( time(NULL) );
    //사업에 참여하는 회사원 만들기. 
    while(1) {
        for(i=0; i<MakeM; i++) {
            e_arr[i]=0;
        }
        for(i=0; i<MakeN; i++) {
            for(j=0; j<MakeM; j++) {
                e_all_arr[i][j]=0;
            }
        }
        
        for(i=0; i<MakeN; i++) {
            cnt=rand()%RANGE +1;
            //out << cnt;
            e_all_arr[i][0]=cnt;
            
            for(j=0; j<MakeM; j++) {
                e_arr[j]=0;
            }
            
            j=1;
            while(j<=cnt) {
                employee=rand()%MakeM+1;
                //이미 참여하고 있는 사람이면 다시 랜덤. 
                //employee-1 주의. 
                if(e_arr[employee-1] == 1) continue;
                //out << " " << employee;
                e_all_arr[i][j]=employee;
                
                e_arr[employee-1]=1;
                j++;
            }
            //out << endl;
        }
        
        //모든 회사원이 사업에 할당되었는지 계산
        //할당되었으면, 빠져나가고,
        //아니면 다시 랜덤.
        for(j=0; j<MakeM; j++) {
            e_arr[j]=0;
        } 
        int e_cnt=0;
        for(i=0; i<MakeN; i++) {
            cnt=e_all_arr[i][0];
            for(j=1; j<=cnt; j++) {
                employee=e_all_arr[i][j];
                if(e_arr[ employee-1 ] ==0) {
                    e_arr[ employee-1 ]=1;
                    e_cnt++;
                }
            }
        }
        if(e_cnt==MakeM) {
            for(i=0; i<MakeN; i++) {
                cnt=e_all_arr[i][0];
                out << cnt;
                for(j=1; j<=cnt; j++) {
                    out << " " << e_all_arr[i][j];
                }
                out << endl;
            }
            break;
        }
        
    }
    
    //사업의 수익금 만들기
    for(i=0; i<MakeN; i++) {
        v=rand()%RANGEProfit +1;
        if(i!=0) out << " ";
        out << v;
    }
    out << endl;
     
    //회사원의 연봉 만들기. 
    for(i=0; i<MakeM; i++) {
        v=rand()%RANGEEmployee +1;
        if(i!=0) out << " ";
        out << v;
    }
}


void dfs(int level)
{
    //이익을 계산
    int i, j, idx;
    int sumb=0, cnt_p;

    //참여하지 않으면 1 
    for(i=0; i<M; i++) {
        Participation[i]=1;
    }
    //포기하면 1 
    for(i=0; i<N; i++) {
        //포기하는 사업이라면, 이익금을 빼야하고, 
        if(ChkBusiness[i]==1) {
            sumb-=Profit[i];
        } else {
        //포기하는 사업에 참여하는 사람중에 다른 사업에는 참여하지 않은 사람을 체크 
        //이를 위해, 포기하지 않는 사업에 참여하는 사람을 체크 
            cnt_p=Business[i][0];
            for(j=1; j<=cnt_p; j++) {
                idx=Business[i][j];
                Participation[idx]=0; 
            }
        }
    }
    //일이 없는 사람의 연봉을 추가. 
    for(i=0; i<M; i++) {
        if(Participation[i]==1) {
            sumb+=Employee[i];
        }
    }
    if(sumb > MaxProfit) {
        MaxProfit=sumb;
        for(i=0; i<N; i++) {
            GiveupPath[i]=ChkBusiness[i];
        }
    } 
     
    for(i=level+1; i<N; i++) {
        //i번 사업을 포함하지 않는 경우. 
        ChkBusiness[i]=1;
        dfs(i);
        ChkBusiness[i]=0;
    }
}

void main()
{
    //makedata();
    
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
    }
    
    
    //-----------------------
    //계산 시작. 
    //-----------------------
    for(i=0; i<N; i++) {
        //i번 사업을 포기하는 경우. 
        ChkBusiness[i]=1;
        dfs(i);
        ChkBusiness[i]=0;
    }
    
    ofstream out(OUTFILE);
    out << MaxProfit;
    
    out << endl;
    for(i=0; i<N; i++) {
        if(GiveupPath[i]==1) {
            out << i+1 << " ";
        }
    }
}

