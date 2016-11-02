#include <fstream.h>
#include <stdio.h>
#include <iomanip.h>

ifstream in("numblock04.in");
ofstream out("numblock04.out");

int bones[7][7];
int layout = 1;


void Print(int board[7][8]) {
   int r, c;

   for (r=0; r<7; r++) {
      for (c=0; c<8; c++) out << setw(3) << board[r][c] << " ";
      out << endl;
   }
   out << endl;
}


int Place(int pips[7][8], int placed[7][8], int used[28],int n_used, int r1, int c1, int r2, int c2)
{
	int b, soln=0, r, c;
	static int call=0;

	b = bones[pips[r1][c1]][pips[r2][c2]];
	if (!used[b]) {
		used[b] = placed[r1][c1] = placed[r2][c2] = b;
		if (n_used == 28) {
			Print(placed);
			soln = 1;
		} else {
			r = r1; c = c1;
			while (placed[r][c] || (r<6 && placed[r+1][c]) && (c<7 && placed[r][c+1])) {
				if (++c > 7) {
					c = 0;
					if (++r > 6) break;
				}
			}
			if (r != 7) {
				if (r<6 && !placed[r+1][c]) soln += Place(pips, placed, used, n_used+1, r, c, r+1, c);
				if (c<7 && !placed[r][c+1]) soln += Place(pips, placed, used, n_used+1, r, c, r, c+1);
			}
		}
		placed[r1][c1]=placed[r2][c2]=used[b]=0;
	}
	return soln;
}

void main() {
	int pips[7][8], placed[7][8], used[29];
	int r, c, i, j, b, layout=1;
   
	for(b=1,i=0,j=0;b<29;b++) {
		bones[i][j]=bones[j][i]= b;
		if(++i==7) i=++j;
	}
	for(r=0;r<7;r++) { 
		for(c=0;c<8;c++) {
			in >> pips[r][c];
			placed[r][c]=0; // 초기화.
		}
	}
	for(i=1;i<=28;i++) used[i] = 0; // 사용한 도미노 체크배열 초기화
	i=Place(pips, placed, used, 1, 0, 0, 0, 1)+Place(pips, placed, used, 1, 0, 0, 1, 0);
}

/*
void main()
{
	int i,j,k;
	struct _t {
		int s1;
		int s2;
	} block[28]={
{0,0},
{0,1},
{0,2},
{0,3},
{0,4},
{0,5},
{0,6},
{1,1},
{1,2},
{1,3},
{1,4},
{1,5},
{1,6},
{2,2},
{2,3},
{2,4},
{2,5},
{2,6},
{3,3},
{3,4},
{3,5},
{3,6},
{4,4},
{4,5},
{4,6},
{5,5},
{5,6},
{6,6}
	};
	int cnt=0;
	int table[2][7][8]={0,};

	for(i=0;i<7;i++)
		for(j=0;j<8;j++)
			in >> table[0][i][j];

	for(k=0;k<28;k++) {
		for(i=0;i<7;i++) {
			for(j=0;j<8;j++) {
				if(table[0][i][j]==k && !table[1][i][j]) {
					if(table[0][i+1][j]==k) {
						table[1][i][j]=block[k].s1;
						table[1][i+1][j]=block[k].s2;
					} else {
						table[1][i][j]=block[k].s1;
						table[1][i][j+1]=block[k].s2;
					}
				}
			}
		}
	}

	for(i=0;i<7;i++) {
		for(j=0;j<8;j++) {
			out << setw(3) << table[1][i][j];
		}
		out << endl;
	}
}
*/