#include <fstream.h>

ifstream in("border.in");
ofstream out("border.out");

#define MAXDIM 25
#define IMAGE_NEIGHBORS 8
#define SIDES 4
int del[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
char grid[MAXDIM][MAXDIM];
char EMPTY_CHAR = '.';
char FILL_CHAR = 'I';
int rows, cols, rstart, cstart;
int lenborder;

void inp()
{
	int r,c;
	in >> rows >> cols >> rstart >> cstart;
    for(r=0;r<rows;r++)
		for (c=0;c<cols;c++)
          in >> grid[r][c];
}
void oup()
{
	out << lenborder;
}
int fill(int r, int c){
	int dir;
	int rn, cn;
	int i,j;
    // 8 개의 이웃한 블럭을 채운다.. 'I'로...
	// 현재 정점과 경계를 공유하는 이웃 노드 수를 센다.
    int count = 0;
    grid[r][c] = FILL_CHAR;
	for(i=0;i<rows;i++) {
		for(j=0;j<cols;j++)
			out << grid[i][j];
		out << endl;
	}
	out << endl;
    for (dir = 0; dir < IMAGE_NEIGHBORS; dir++) {
		rn = r+del[dir][0], cn = c+del[dir][1];
		if ((rn<0 || rn>=rows || cn<0 || cn>=cols || grid[rn][cn]==EMPTY_CHAR )) {
		// 현재 노드가 최외각에 있거나 이웃한 노드가 빈 것일때...카운트..
			if (dir < SIDES) count++;
		} else if (grid[rn][cn] != FILL_CHAR) {
          count += fill(rn, cn);
		}
    }
    return count;
}
void proc()
{
	lenborder=fill(rstart-1,cstart-1);
}
void main()
{
	inp();
	proc();
	oup();
}
