#include <fstream.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip.h>

#define MAXBOARD 1000
#define MAXCARD 200

ifstream in("alphacard.in");
ofstream out("alphacard.out");

int table[2][MAXCARD/2][MAXBOARD];
char cards[2][MAXCARD/2][3];
char board[1001];
int N;
int mincard;
int winplayer;
int boardlen;
int boardpos;
///*
void inp()
{
	int i;

	in >> board;
	boardlen=strlen(board);
	in >> N;
	for(i=0;i<N;i++) {
		if(i%2==0) in >> cards[0][i/2];
		else in >> cards[1][i/2];
	}
}
void oup()
{
	out << winplayer << endl;
	out << mincard;
}
int selectone(int player, int row, int col, char ch1, char ch2) //// 한 문자일때
{
	int i,j;
	int cnt=0;
	for(i=col;i<boardlen && cnt<2;i++) {
		if(ch1==board[i]) {
			if(row==0) {
				table[player][row][i]=1;
				cnt++;
				if(i==boardlen-1) return table[player][row][i];
			} else {
				for(j=i-1;j>=0;j--) {
					if(table[player][row-1][j]) {
						table[player][row][i]=table[player][row-1][j]+1;
						cnt++;
						if(i==boardlen-1) return table[player][row][i];
						break;
					}
				}
			}
			
		}
	}
	return -1;
}
int selecttwo(int player, int row, int col, char ch1, char ch2)  // 두 문자일때
{
	int flag;
	int i,j,k,m,n,r;
	
	flag=0;
	for(j=col;j<boardlen;j++) {
		if(ch1==board[j]) {
			flag=1;
			break;
		}
	}		
	if(flag==1) {
		for(k=j+1;k<boardlen;k++) {
			if(ch2==board[k]) {				
				if(row==0) {
					table[player][row][k]=1;
					if(k==boardlen-1) return table[player][row][k];
					break;
				} else {
					for(r=j-1;r>=0;r--) {
						if(table[player][row-1][r]) {
							table[player][row][k]=table[player][row-1][r]+1;
							if(k==boardlen-1) return table[player][row][k];
							break;
						}
					}
					break;
				}				
			}
		}
	}
	flag=0; // 점프 한번
	for(m=k+1;m<boardlen;m++) {
		if(ch1==board[m]) {
			flag=1;
			break;
		}
	}
	if(flag==1) {
		for(n=m+1;n<boardlen;n++) {
			if(ch2==board[n]) {
				if(row==0) {
					table[player][row][n]=1;
					if(n==boardlen-1) return table[player][row][n];
					break;
				} else {
					for(r=m-1;r>=0;r--) {
						if(table[player][row-1][r]) {
							table[player][row][n]=table[player][row-1][r]+1;
							if(n==boardlen-1) return table[player][row][n];
							break;
						}
					}
					break;
				}				
			}
		}
	}
	return -1;
}
int player1()
{
	int i,j;
	int ret=-1;

	for(i=0;i<N/2;i++) {
		if(i==0) {
			if(strlen(cards[0][i])==1) {
				ret=selectone(0,i,0,cards[0][i][0],0);
			} else {
				ret=selecttwo(0,i,0,cards[0][i][0],cards[0][i][1]);
			}
			if(ret!=-1) return ret;
		} else {
			for(j=0;j<boardlen;j++) {
				if(table[0][i-1][j]) {
					if(strlen(cards[0][i])==1) {
						ret=selectone(0,i,j+1,cards[0][i][0],0);
					} else {
						ret=selecttwo(0,i,j+1,cards[0][i][0],cards[0][i][1]);
					}
					if(ret!=-1) return ret;
				}
			}
		}
	}
	return ret;
}
int player2()
{
	int i,j;
	int ret=-1;

	for(i=0;i<N/2;i++) {
		if(i==0) {
			if(strlen(cards[1][i])==1) {
				ret=selectone(1,i,0,cards[1][i][0],0);
			} else {
				ret=selecttwo(1,i,0,cards[1][i][0],cards[1][i][1]);
			}
			if(ret!=-1) return ret;
		} else {
			for(j=0;j<boardlen;j++) {
				if(table[1][i-1][j]) {
					if(strlen(cards[1][i])==1) {
						ret=selectone(1,i,j+1,cards[1][i][0],0);
					} else {
						ret=selecttwo(1,i,j+1,cards[1][i][0],cards[1][i][1]);
					}
					if(ret!=-1) return ret;
				}
			}

		}
	}
	return ret;
}
void proc()
{
	int p1, p2;
	int i,j;

	p1=player1();
	/*
	for(i=0;i<N/2;i++) {
		for(j=0;j<boardlen;j++) {
			out << table[0][i][j];
		}
		out << endl;
	}
	cout << endl;
	*/
	p2=player2();
	/*
	for(i=0;i<N/2;i++) {
		for(j=0;j<boardlen;j++) {
			out << table[1][i][j];
		}
		out << endl;
	}
	*/
	if(p1==-1 && p2==-1) {
		winplayer=4;
		mincard=-1;
	} else if(p1==-1) {
		winplayer=2;
		mincard=p2;
	} else if(p2==-1) {
		winplayer=1;
		mincard=p1;
	} else {
		if(p1<p2) {
			winplayer=1;
			mincard=p1;
		} else if(p1>p2) {
			winplayer=2;
			mincard=p2;
		} else {
			winplayer=3;
			mincard=p1;
		}
	}
}
void main()
{
	inp();
	proc();
	oup();
}
//*/
/*
char t[1000];
char t1[200][3];
void main()
{
	int x,y,i;

	srand((unsigned)time(NULL));

	for(i=0;i<MAXCARD;i++) {
		x=rand()%5;
		t1[i][0]=(char)('A'+x);
		y=rand()%5;
		if(rand()%5==1) { t1[i][1]=(char)('A'+y); t1[i][2]='\0'; } else { t1[i][1]='\0'; }
	}

	for(i=0;i<MAXBOARD;i++) {
		if(strlen(t)>=MAXBOARD) break;
		x=rand()%MAXCARD;
		strcat(t,t1[x]);
	}

	out << strlen(t) << endl;
	out << t << endl;
	out << MAXCARD << endl;
	for(i=0;i<MAXCARD;i++) {
		out << t1[i] << endl;
	}
}
*/