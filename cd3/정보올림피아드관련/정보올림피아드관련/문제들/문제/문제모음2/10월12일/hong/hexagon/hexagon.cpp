#include <fstream.h>
#include <string.h>

ifstream in("hexagon.in");
ofstream out("hexagon.out");

int maxScore;
int rot[6]; // 삼각형 i의 로테이션 상태 저장, 0,1,2
int tri[6][3]; // 삼각형 6개의 세변.

int getEdge(int n, int shift)
{
    // n번 삼각형에 대해서 값을 리턴한다.
    // 변은 현재 상태에서 회전시킨다.
    // shift 0: 이전 삼각형과 공유하는 변
    // shift 1: 다음 삼각형과 공유하는 변
    // shift 2: 육각형의 외곽선(점수에 사용)
    return tri[n][(rot[n] + shift) % 3];
}
int matchNext(int n)
{
    // n번 삼각형의 현재 로테이션 상태가 true 이면
    // 다음 삼각형과 맞춰본다. n = 0 - 5 
    return getEdge(n, 1) == getEdge((n+1)%6, 0);
}
void swap(int i, int j)
{
    // triangle[i] 와 triangle[j]을 바꾼다.
    int temp[3];
	memmove(temp,tri[i],3*sizeof(int));
    memmove(tri[i],tri[j],3*sizeof(int));
    memmove(tri[j],temp,3*sizeof(int));
}
void fit(int n)
{
    // 삼각형번호 < n 나머지 삼각형과 서로 맞춰본다. 단, n = 1 - 6
    // n = 6이면, 끝으로 tri[5]와 tri[0]을 맞춰본다.
    // 최대값 갱신
    int i, r;
	int score=0;
    if (n == 6) { //  더이상 삼각형이 없으면
		if (matchNext(5)) {
			for (i = 0; i < 6; i++) score += getEdge(i,2);        
			if(score>maxScore) maxScore=score;
		}
    } else { // 다음 삼각형과 맞춰봄
		for(i=n;i<6;i++) { // 남아 있는 다음 삼각형들과 맞춰봄
			swap(n,i); //항상 고려할 삼각형을 n번에 놓는다.
			for (r=0;r<3;r++) { // 3번 돌려본다.
				rot[n] = r;
				if (matchNext(n-1)) fit(n+1);
			}
			swap(n,i); // 다시 복구.
		}
    }
} 
void inp()
{
	int r, n;
    for(n=0;n<6;n++) {
		for(r=0;r<3;r++) {
			in >> tri[n][r];
		}
	}
}
void oup()
{
	if(maxScore==0) out << "impossible";
	else out << maxScore;
}
void proc()
{
	int r;
	for (r=0;r<3;r++) {
		rot[0]=r;
        fit(1);
	}
}
void main()
{
	inp();
	proc();
	oup();
}