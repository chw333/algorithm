#include <fstream.h>
#include <stdio.h>
#include <string.h>

ifstream in("lock.in");
ofstream out("lock.out");
int M[25];
char S[3][3];
char P[7][7];

int Goal;
int R, C;
int minpos, pos, minpressed, pressed;
//int back, front;  for BFS

void inp()
{
	int i,j;
	
	in >> R >> C;
    for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			in >> S[i][j];
		}
	}
    for (i= 0; i < R*C; i++) {
		Goal|=1<<i;
		M[i] = 0;
    }
}
void oup()
{
	int j, first; //, path;
//	char ret[256]={0,};
//	char buf[256]={0,};
//	char temp[256]={0,};

	if (minpos == 1<<R*C) out << "impossible";
    else {
		first = 1;
		for(j=0;j<R*C;j++) {
			if(minpos & 1<<j) {
				if (!first) out <<" ";
				else first = 0;
				out << j+1;
			}
		}
    }
    out << endl;
/*

    //FOR BFS

	path=p[MAXBIT];
	while(path!=-1) {
		//first = 1;
		//for(j=0;j<R*C;j++) {
		//	if(path & 1<<j) {
				//if (!first) out <<" ";
				//else first = 0;
			//	out << j+1 << " ";
		//	}
		//}
		sprintf(buf,"%d",b[path]);
		strcpy(temp,ret);
		if(strcmp(buf,"0")!=0) { if(temp[0]!=0) { sprintf(ret,"%s %s",buf,temp); } else { sprintf(ret,"%s",buf); } }
		path=p[path];
	}
	strcpy(temp,ret);
	sprintf(ret,"%s %d",temp,b[MAXBIT]);
	out << ret;
*/
}
// s는 현재 상태...i는 현재 눌린 번호...
void dfs(int s, int i) {
	if (pressed > minpressed) return;
	if (s == Goal) {
		if (pressed < minpressed || (pressed == minpressed && pos < minpos)) {
			minpos = pos;
			minpressed = pressed;
		} 
	}
	if (i+1 < R*C) {
		dfs(s, i+1);
		pressed++; // 눌린다.
		pos |= 1<<(i+1); // 눌린 위치...
		dfs( s^M[i+1], i+1);  
		pos &= ~(1<<(i+1)); // 복구..
		pressed--; // 복구...
	}
}
void proc()
{
	int r, c, i, j, r1, c1;
  
    for(r = 1; r <= R; r++) {
		for(c = 1; c <= C; c++) {
			for(i = 0; i < 7; i++) {
				for (j = 0; j < 7; j++) P[i][j] = 0;
			}
			for(i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) { // 예시... r=1,2 // c=1,2,3
					if (S[i][j] == '*') P[r-1+i][c-1+j] = 1;
				}
			}
			for(r1 = 1; r1 <= R; r1++) {
				for(c1 = 1; c1 <= C; c1++) {
					M[(r-1)*C + c-1] |= (P[r1][c1])<<((r1-1)*C+c1-1);
				} // P[r1-1][c1-1]이 아니고 P[r1][c1]인 까닭은...
			}     // 필요없는 부분의 값이 스위치 될 필요가 없기 때문...
		}
	}
	pressed = pos = 0;
    minpos = 1<<R*C;
    minpressed = R*C;

    dfs(0, 0); // 0번 노드가 눌리지 않을 때.
    pressed = 1;
    pos = 1;
    dfs(M[0], 0); // 0번 노드가 눌릴 때...
}
  
void main()
{
	inp();
	proc();
	oup();
}
