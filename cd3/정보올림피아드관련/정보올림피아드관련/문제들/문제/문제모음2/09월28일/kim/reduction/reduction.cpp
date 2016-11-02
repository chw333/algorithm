#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>


#define MAXN 50
#define MAXM 100

int N, M;
int Employee[MAXM];        //ȸ����� ���� 
int Profit[MAXN];          //����� ���� 
int Business[MAXN][MAXM+1]; //����� ������ ȸ��� 

int ChkBusiness[MAXN];
int Participation[MAXM];
int MaxProfit;
int GiveupPath[MAXN];


#define MakeN 46 //����� �� 
#define MakeM 80 //ȸ����� �� 
#define RANGE (MakeN*1/5) //����� �����ϴ� ȸ����� ���� 
#define RANGEProfit 100 //����� ���ͱ� ���� 
#define RANGEEmployee 50 //ȸ����� ���� ���� 

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
    //����� �����ϴ� ȸ��� �����. 
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
                //�̹� �����ϰ� �ִ� ����̸� �ٽ� ����. 
                //employee-1 ����. 
                if(e_arr[employee-1] == 1) continue;
                //out << " " << employee;
                e_all_arr[i][j]=employee;
                
                e_arr[employee-1]=1;
                j++;
            }
            //out << endl;
        }
        
        //��� ȸ����� ����� �Ҵ�Ǿ����� ���
        //�Ҵ�Ǿ�����, ����������,
        //�ƴϸ� �ٽ� ����.
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
    
    //����� ���ͱ� �����
    for(i=0; i<MakeN; i++) {
        v=rand()%RANGEProfit +1;
        if(i!=0) out << " ";
        out << v;
    }
    out << endl;
     
    //ȸ����� ���� �����. 
    for(i=0; i<MakeM; i++) {
        v=rand()%RANGEEmployee +1;
        if(i!=0) out << " ";
        out << v;
    }
}


void dfs(int level)
{
    //������ ���
    int i, j, idx;
    int sumb=0, cnt_p;

    //�������� ������ 1 
    for(i=0; i<M; i++) {
        Participation[i]=1;
    }
    //�����ϸ� 1 
    for(i=0; i<N; i++) {
        //�����ϴ� ����̶��, ���ͱ��� �����ϰ�, 
        if(ChkBusiness[i]==1) {
            sumb-=Profit[i];
        } else {
        //�����ϴ� ����� �����ϴ� ����߿� �ٸ� ������� �������� ���� ����� üũ 
        //�̸� ����, �������� �ʴ� ����� �����ϴ� ����� üũ 
            cnt_p=Business[i][0];
            for(j=1; j<=cnt_p; j++) {
                idx=Business[i][j];
                Participation[idx]=0; 
            }
        }
    }
    //���� ���� ����� ������ �߰�. 
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
        //i�� ����� �������� �ʴ� ���. 
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
    //��� ����. 
    //-----------------------
    for(i=0; i<N; i++) {
        //i�� ����� �����ϴ� ���. 
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

