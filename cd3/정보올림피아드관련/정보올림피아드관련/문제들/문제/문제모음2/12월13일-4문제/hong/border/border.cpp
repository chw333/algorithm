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
    // 8 ���� �̿��� ���� ä���.. 'I'��...
	// ���� ������ ��踦 �����ϴ� �̿� ��� ���� ����.
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
		// ���� ��尡 �ֿܰ��� �ְų� �̿��� ��尡 �� ���϶�...ī��Ʈ..
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
