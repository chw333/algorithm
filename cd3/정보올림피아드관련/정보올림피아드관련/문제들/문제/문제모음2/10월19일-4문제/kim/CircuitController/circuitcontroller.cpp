#include <fstream.h>
#include <stdlib.h>
#include <time.h>

#define MAXM 10
#define MAXN 3000
#define MAXK 30

#define INFINIT 100000000

int M, N, K;
int List[MAXN+1][MAXM+1];
    //k�� ���� ����, n�� �� ��, m�� �� ���� ĭ ��.
int Dy[MAXK+1][MAXN+1][MAXM+1][MAXM+1];
    


#define INFILE "circuitcontroller10.in"
#define OUTFILE "circuitcontroller10.out"

#define MAKEN 3000  //3000����
#define MAKEM 10  //10����
#define MAKEK 30  //30����
#define RANGE 500  //500����.

void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEM << " " << MAKEN << " " << MAKEK << endl;
	int i, j, v;
	for(i=0; i<MAKEN; i++) {
		for(j=0; j<MAKEM; j++) {
			if(j!=0) out << " ";
			v=rand()%RANGE + 1;
			out << v;
		}
		out << endl;
	}
}


void circuitcontroller()
{
    int i,j;
    ifstream in(INFILE);
    in >> M >> N >> K;
    for(i=1; i<=N; i++) {
        for(j=1; j<=M; j++) {
            in >> List[i][j];
        }
    }
    
    //���̳���
    int ki, x1, x2;
    int px1, px2, v1, v2, v, min;

    //�� ���� ù�� �ʱ�ȭ
	for(i=1; i<=N; i++) {
		for(x1=1; x1<M; x1++) {
			for(x2=x1+1; x2<=M; x2++) {
				//�ּҰ� ����
				min=INFINIT;
				for(px1=1; px1<M; px1++) {
					for(px2=px1+1; px2<=M; px2++) {
						v1=x1-px1;
						if(v1<0) v1=-v1;
						v1+=List[i][x1];
						v2=x2-px2;
						if(v2<0) v2=-v2;
						v2+=List[i][x2];
						v=v1+v2+Dy[0][i-1][px1][px2];
						if(v < min) {
							min=v;
						}
					}
				}
				Dy[0][i][x1][x2]=min;
			}
		}
	}

	for(ki=1; ki<=K; ki++) {
		//ki�� ���̱� ���ؼ��� �ּ��� ki+1���� �ʿ�.
        for(i=ki+1; i<=N; i++) {
            //i�ٿ��� x1, x2�� �����Ͽ�,
            //x1�� x2�� ���� �ּҰ��� ����
            for(x1=1; x1<M; x1++) {
                for(x2=x1+1; x2<=M; x2++) {
                    //x1, x2�� �� ���� �� ��
                    //�ּҰ� ����
					min=INFINIT;
					//i�� ki+1�̸� ù ���̹Ƿ� ������ ���ƾ� ��.
					//    ����, ki+1���� ū �ٿ����� ����
					//    ���ΰͰ� �Ȳ��� ���� ������ �� ����.
					if(i!=ki+1) {
						for(px1=1; px1<M; px1++) {
							for(px2=px1+1; px2<=M; px2++) {
								v1=x1-px1;
								if(v1<0) v1=-v1;
								v1+=List[i][x1];
								v2=x2-px2;
								if(v2<0) v2=-v2;
								v2+=List[i][x2];
								v=v1+v2+Dy[ki][i-1][px1][px2];
								if(v < min) {
									min=v;
								}
							}
						}
					}
					//x1, x2�� ���� �� ��
                    //�ּҰ� ����
					for(px1=2; px1<=M; px1++) {
						for(px2=1; px2<px1; px2++) {
							v1=x1-px1;
							if(v1<0) v1=-v1;
							v1+=List[i][x1];
							v2=x2-px2;
							if(v2<0) v2=-v2;
							v2+=List[i][x2];
							v=v1+v2+Dy[ki-1][i-1][px2][px1];
							if(v < min) {
								min=v;
							}
						}
					}
					
					Dy[ki][i][x1][x2]=min;
                }
            }
			
        }
    }


	ofstream out(OUTFILE);
	min=INFINIT;
	for(x1=1; x1<M; x1++) {
		for(x2=x1+1; x2<=M; x2++) {
			if(Dy[K][N][x1][x2] < min) {
				min=Dy[K][N][x1][x2];
			}
		}
	}
	out << min;
}

void main()
{
	makedata();
	circuitcontroller();
}