#include <fstream.h>
#include <time.h>

const MAXSIZE = 10;
int size;
const char OPEN = '.';
const char PIECE = 'P';
char board[MAXSIZE+2][MAXSIZE+2];

struct _c {
	int rangecnt;
	int range[MAXSIZE][3];
} row[MAXSIZE+2], col[MAXSIZE+2];

ifstream in("survival05.in");
ofstream out("survival05.out");

int safePlace(int x, int y, int &c, int &r)
{
	int i;

	for(i=0;i<row[y].rangecnt;i++) {
		if(row[y].range[i][0]<=x && row[y].range[i][1]>=x) {
			if(row[y].range[i][2]) {
				return 0; 
			} else {
				r=i; 
				break; 
			}
		}
	}
	for(i=0;i<col[x].rangecnt;i++) {
		if(col[x].range[i][0]<=y && col[x].range[i][1]>=y) {
			if(col[x].range[i][2]){
				return 0; 
			} else {
				c=i; 
				break; 
			}
		}
	}
    return 1;
}


int moreSafe(int x, int y)
{
    int nPlaced, mostPlaced = 0;
	int ro, co;
    while (y <= size) {
		ro=co=0;
        if (board[y][x] == OPEN) {
			if(safePlace(x, y, co, ro )) {
				board[y][x] = PIECE;
				/*
				for(int i=1;i<=size;i++) {
					for(int j=1;j<=size;j++)
						cout << board[i][j] << " ";
					cout << endl;
				}
				cout << endl;
				*/
				row[y].range[ro][2]=1;
				col[x].range[co][2]=1;
				nPlaced = 1 + moreSafe(row[y].range[ro][1]+1, y);
				if (nPlaced > mostPlaced) mostPlaced = nPlaced; 
				board[y][x] = OPEN; 
				row[y].range[ro][2]=0;
				col[x].range[co][2]=0;
			}
        }
        if (x >= size) {        
            x = 1;      
            y++;        
        } else x++;
    }
    return mostPlaced;  
}

void main()
{
	int i,j;
	int gorow=0, gocol=0;
	//clock_t s, e;
	
	//s=clock();
    in >> size;
    for(i=1;i<=size;i++) {
        board[0][i] = board[size+1][i] = 'X';
        board[i][0] = 'X';
        in >> board[i]+1;
    }

	for(i=1;i<=size;i++) {
		row[i].rangecnt=0;
		col[i].rangecnt=0;
		gocol=gorow=0;
		for(j=1;j<=size+1;j++) {
			if(board[i][j]=='.') {
				if(!gorow) {
					gorow=1;
					row[i].range[row[i].rangecnt][0]=j;
				}
			} else {
				if(gorow) {
					row[i].range[row[i].rangecnt][1]=j-1;
					gorow=0;
					row[i].rangecnt++;
				}		
			}
			if(board[j][i]=='.') {
				if(!gocol) {
					gocol=1;
					col[i].range[col[i].rangecnt][0]=j;
				}
			} else {
				if(gocol) {
					col[i].range[col[i].rangecnt][1]=j-1;
					gocol=0;
					col[i].rangecnt++;
				}	
			}
		}
	}
    out << moreSafe(1, 1) << endl;
	//e=clock();
	//out << (double)(e-s)/CLOCKS_PER_SEC << endl;
}
            
