#include <fstream.h>
#include <iomanip.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define INFINIT 100000000
#define MAXN 30

struct TRI {
	int shape, left, right, line;
	int adj[3];
};
int N;
TRI Tri[MAXN*MAXN];
int StartIdx[MAXN*MAXN];
int RestoreIdx[MAXN*MAXN];
int EndIdx[MAXN*MAXN];
int EndNum;
int Min;
int Change[MAXN*MAXN*3][2];
int ChangeCnt;

clock_t StartTime, CurTime;

int TestCnt[MAXN*MAXN];


#define INFILE "museum10.in"
#define OUTFILE "museum10.out"

#define MAKEN 20
int MakeStartIdx[MAXN*MAXN];
int MakeEndIdx[MAXN*MAXN];

void makedata()
{
	srand(time(NULL));
	int i, endnum=MAKEN*MAKEN;
	int v1, v2, tmp;

	for(i=0; i<endnum; i++) {
		MakeStartIdx[i]=i+1;
	}
	for(i=0; i<endnum; i++) {
		v1=rand()%endnum;
		v2=rand()%endnum;
		tmp=MakeStartIdx[v1];
		MakeStartIdx[v1]=MakeStartIdx[v2];
		MakeStartIdx[v2]=tmp;
	}

	for(i=0; i<endnum; i++) {
		MakeEndIdx[i]=i+1;
	}
	for(i=0; i<endnum; i++) {
		v1=rand()%endnum;
		v2=rand()%endnum;
		tmp=MakeEndIdx[v1];
		MakeEndIdx[v1]=MakeEndIdx[v2];
		MakeEndIdx[v2]=tmp;
	}

	ofstream out(INFILE);
	out << MAKEN << endl;
	for(i=0; i<endnum; i++) {
		if(i!=0) out << " ";
		out << MakeStartIdx[i];
	}
	out << endl;
	for(i=0; i<endnum; i++) {
		if(i!=0) out << " ";
		out << MakeEndIdx[i];
	}
}


#include <windows.h>
void gotoxy(int x, int y)
{
    HANDLE hout;
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cscr;
    cscr.X=x;
    cscr.Y=y;
    SetConsoleCursorPosition(hout,cscr);
}

void print(int index[])
{
	int i,j, endnum=N*N;
	int idx, linenum;

	idx=0; linenum=1;
	for(i=0; i<N; i++) {
		for(j=i+1; j<N; j++) {
			cout << setw(3) << " ";
		}
		for(j=0; j<linenum; j++) {
			cout << setw(3) << index[idx];
			idx++;
		}
		cout << endl;
		linenum+=2;
	}
	cout << endl;
}


int go_upleft(int num)
{
	//���ﰢ���̸�, �� ������ 0��
	//���ﰢ���̸�, ���� 2��.
	if(Tri[num].shape==0) {
		return Tri[num].adj[0];
	} else {
		return Tri[num].adj[2];
	}
}
int go_upright(int num)
{
	//���ﰢ���̸�, �� ������ 1��
	//���ﰢ���̸�, ���� 2��.
	if(Tri[num].shape==0) {
		return Tri[num].adj[1];
	} else {
		return Tri[num].adj[2];
	}
}
int go_downleft(int num)
{
	//���ﰢ���̸�, �Ʒ� ������ 0��.
	//���ﰢ���̸�, �Ʒ��� 2��
	if(Tri[num].shape==1) {
		return Tri[num].adj[0];
	} else {
		return Tri[num].adj[2];
	}
}
int go_downright(int num)
{
	//���ﰢ���̸�, �Ʒ� ������ 1��.
	//���ﰢ���̸�, �Ʒ��� 2��
	if(Tri[num].shape==1) {
		return Tri[num].adj[1];
	} else {
		return Tri[num].adj[2];
	}
}



//move�Լ���
//   1. endpos�� ��ġ�� �ִ� index���� ���ڸ� ã�� 
//   2. ã�� ���ڸ� endpos�� �̵���Ų��.
//�̵����.
//   1. ���� ���̸�, right�� ��ǥ���� �̵�.
//   2. ���� left�� ũ�ų� ����, left�� ������������, left�� �̵�.
//      ��ǥ���� right�� ���� ������ downleft�� �̵�.
//   3. ���� left�� ������, right�� ������ ������ downleft�� �̵�.
//      ��ǥ���� ���� line�� �ɶ����� downright�� �̵�.
//����.
//   1. endpos���� ū ���� �ǵ������ �ȵȴ�.
//   2. ���࿡ �ǵ帮��, �ǵ帰 ���� �ٽ� �ٲ��ش�.
void swap(int index[], int pos1, int pos2)
{
	int tmp;
	tmp=index[pos1];
	index[pos1]=index[pos2];
	index[pos2]=tmp;
}

int move(int index[], int endpos)
{
	int i, cnt;
	int startpos, endnum=EndIdx[endpos];
	int nextpos;
	
	//�̵��ؾ��� ���� ��ġ ã��
	for(i=0; i<EndNum; i++) {
		if( endnum == index[i] ) {
			startpos=i;
			break;
		}
	}

	//��=startpos, ������=endpos
	cnt=0;
	if( Tri[startpos].line == Tri[endpos].line) {
		//1. ���� ���̸�, right�� ��ǥ���� �̵�.
		while(1) {
			if(startpos==endpos) break;
			swap(index, startpos, startpos+1);
			startpos++;
			cnt++;
		}
	} else {
		if( Tri[startpos].left >= Tri[endpos].left) {
		//2. ���� left�� ũ�ų� ����
			//2.0 = left�� ������������, left�� �̵�.
			while(1) {
				if(Tri[startpos].left == Tri[endpos].left) {
					break;
				}
				swap(index, startpos, startpos-1);
				startpos--;
				cnt++;
			}
			//2.1 = ��ǥ���� right�� ���� ������ downleft�� �̵�.
			while(1) {
				if(Tri[startpos].right == Tri[endpos].right) {
					break;
				}
				nextpos= go_downleft(startpos);
				swap(index, startpos, nextpos);
				startpos=nextpos;
				cnt++;
			}
			//2.2 = left�� right�� ��� ������, ��ǥ���� �ƴϸ�,
			//      �ѹ��� downright�� �̵�.
			if(startpos!=endpos) {
				nextpos= go_downright(startpos);
				swap(index, startpos, nextpos);
				startpos=nextpos;
				cnt++;
			}


		} else {
		//3. ���� left�� ������
			//3.0 = right�� ������ ������ downleft�� �̵�.
			while(1) {
				if(Tri[startpos].right >= Tri[endpos].right) {
					break;
				}
				nextpos= go_downleft(startpos);
				swap(index, startpos, nextpos);
				startpos=nextpos;
				cnt++;
			}
			//3.1 = line�� ������ ������ downright�� �̵�.
			while(1) {
				if(Tri[startpos].line >= Tri[endpos].line) {
					break;
				}
				nextpos= go_downright(startpos);
				swap(index, startpos, nextpos);
				startpos=nextpos;
				cnt++;
			}
			//3.1 = ���� line�̸鼭, ��ǥ���� �ƴϸ�, ���������� �̵�.
			while(1) {
				if(startpos == endpos) {
					break;
				}
				swap(index, startpos, startpos+1);
				startpos++;
				cnt++;
			}
		}
	}
	return cnt;
}


//����ϱ�.
int calc(int index[MAXN*MAXN])
{
	int i,j, v, cnt;
	int tmp, startpos, endpos;
	int sum;

	sum=0;
	for(i=0; i<EndNum; i++) {
		endpos=i;
		//�̵��ؾ��� ���� ��ġ ã��
		for(j=0; j<EndNum; j++) {
			if( index[j] == EndIdx[endpos] ) {
				startpos=j;
				break;
			}
		}
		if(startpos > endpos) {
			tmp=startpos;
			startpos=endpos;
			endpos=tmp;
		}

		//���� ��ġ�� �̵��ؾ��� ��ġ�� ���� ���
		//��=startpos, �̵���ġ=endpos
		//�׻� endpos�� startpos���� ũ��.
		cnt=0;
		if( Tri[startpos].line == Tri[endpos].line) {
			//1. ���� ���̸�, right�� ��ǥ���� �̵�.
			cnt=endpos-startpos;
		} else {
			//2. ���� left�� ������,
			while(1) {
				if( Tri[startpos].left >= Tri[endpos].left) {
					break;
				}
				if( Tri[startpos].line == Tri[endpos].line) {
					break;
				}
				startpos=go_downright(startpos);
				cnt++;
			}
			//3. ���� right�� ������,
			while(1) {
				if( Tri[startpos].right >= Tri[endpos].right) {
					break;
				}
				if( Tri[startpos].line == Tri[endpos].line) {
					break;
				}
				startpos=go_downleft(startpos);
				cnt++;
			}
			v=endpos-startpos;
			if(v<0) v=-v;
			cnt+=v;
			
		}	
		sum+=cnt;
	}
	return sum;
}



void museum()
{
	StartTime=clock();
	int i,j;
	int idx, linecnt, leftnum, rightnum;
	int startnum, newnum, endnum;
	ifstream in(INFILE);
	in >> N;
	EndNum=endnum=N*N;
	for(i=0; i<endnum; i++) {
		in >> StartIdx[i];
		StartIdx[i]--;
	}
	for(i=0; i<endnum; i++) {
		in >> EndIdx[i];
		EndIdx[i]--;
	}

	//�ﰢ���� ������ �ʱ�ȭ ��.
	idx=0;
	linecnt=0;
	for(i=0; i<N; i++) {
		leftnum=0;
		rightnum=linecnt-leftnum;
		startnum=idx;
		for(j=0; j<=linecnt; j++) {
			Tri[idx].line=i; //���ٿ��� ���° ��. ��ȣ�� 0������.
			Tri[idx].left=leftnum/2; //���ʿ��� ���°. ��ȣ�� 0������.
			Tri[idx].right=rightnum/2; //�����ʿ��� ���°. ��ȣ�� 0������.
			leftnum++;
			rightnum--;
			Tri[idx].shape=j%2;  //����� ���ﰢ������ ���ﰢ������= ���ﰢ���� 0, ���ﰢ���� 1
			
			//����
			if(idx-1 >= startnum) {
				Tri[idx].adj[ 0 ]=idx-1;
			} else {
				Tri[idx].adj[ 0 ]=-1;
			}
			//������
			if(idx+1 <= startnum+linecnt) {
				Tri[idx].adj[ 1 ]=idx+1;
			} else {
				Tri[idx].adj[ 1 ]=-1;
			}

			//�� �Ǵ� �Ʒ�
			if(Tri[idx].shape==0) {
				//���ﰢ���̸�, �Ʒ�
				newnum=idx+linecnt+2;
				if(newnum < endnum) {
					Tri[idx].adj[ 2 ] = newnum;
				} else {
					Tri[idx].adj[ 2 ] = -1;
				}
			} else {
				//���ﰢ���̸�, ��
				Tri[idx].adj[ 2 ] = idx-linecnt;
			}
			idx++;
		}
		linecnt+=2;
	}

	//�ΰ��� ��ġ�� �ٲٴ� ��� ��� �ʱ�ȭ
	linecnt=1;
	ChangeCnt=0;
	for(i=1; i<N; i++) {
		startnum=i*i;
		startnum++;
		for(j=0; j<linecnt; j++) {
			//�׻� ���ﰢ�� ������� ��Ƽ� ����.
			Change[ChangeCnt][0]=Tri[startnum].adj[2];
			Change[ChangeCnt][1]=startnum;
			ChangeCnt++;

			Change[ChangeCnt][0]=startnum-1;
			Change[ChangeCnt][1]=startnum;
			ChangeCnt++;

			Change[ChangeCnt][0]=startnum;
			Change[ChangeCnt][1]=startnum+1;
			ChangeCnt++;

			startnum+=2;
		}
		linecnt++;
	}


	//gotoxy(0,0);
	//cout.flush();
	//print(StartIdx);
	//print(EndIdx);
	
	int v, cnt, sum;
	int value, bidx;

	for(i=0; i<endnum; i++) {
		RestoreIdx[i]=StartIdx[i];
	}

	sum=0;
	for(i=endnum-1; i>=0; i--) {
		v=move(StartIdx, i);
		sum+=v;

		if(i!=endnum-1) {
			v=move(StartIdx, i+1);
			sum+=v;
		}
	}
	Min=sum;
	cout << sum << endl;


	while(1) {
		CurTime=clock();
		if( ((double)(CurTime-StartTime))/CLK_TCK > 7.9) { 
			break;
		}
		
		for(i=0; i<endnum; i++) {
			StartIdx[i]=RestoreIdx[i];
		}

		value=calc(StartIdx);
		cnt=0;
		while(cnt < 5) {
			bidx=rand()%ChangeCnt;
			swap(StartIdx, Change[bidx][0], Change[bidx][1]);
			v=calc(StartIdx);
			if(v >= value) {
				swap(StartIdx, Change[bidx][0], Change[bidx][1]);
				continue;
			}
			cnt++;
		}

		sum=0;
		for(i=endnum-1; i>=0; i--) {
			v=move(StartIdx, i);
			sum+=v;

			if(i!=endnum-1) {
				v=move(StartIdx, i+1);
				sum+=v;
			}
		}
		sum+=cnt;
		//gotoxy(1,1);
		//cout.flush();
		//cout << sum << endl;
		//cout << "-----------" << endl;
		//cout << Min;


		if(Min > sum) {
			Min=sum;
			cout << Min << endl;
		}
	}

	ofstream out(OUTFILE);
	out << Min;

}


void main()
{
	makedata();
	museum();
}