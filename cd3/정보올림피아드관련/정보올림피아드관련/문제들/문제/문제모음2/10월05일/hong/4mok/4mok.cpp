#include <fstream.h>

char table[4][4];
int wx=-1, wy=-1;

ifstream in("4mok10.in");
ofstream out("4mok10.out");

int xwin(int y, int x);
int oloss(int y, int x);

void inp()
{
	int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			in >> table[i][j];
		}
	}
}
void oup()
{
	if(wx==-1 && wy==-1) out << "impossible" ;
	else out << wy << " " << wx;
}
int iswin(int y, int x, char ch)
{
	if((table[y][0]==ch && table[y][1]==ch && table[y][2]==ch && table[y][3]==ch) ||
	  (table[0][x]==ch && table[1][x]==ch && table[2][x]==ch && table[3][x]==ch) ||
      (table[0][0]==ch && table[1][1]==ch && table[2][2]==ch && table[3][3]==ch) ||
	  (table[0][3]==ch && table[1][2]==ch && table[2][1]==ch && table[3][0]==ch) ) {
		return 1;
	}
	return 0;
}
int xwin(int y, int x)
{
	int i, j;

	table[y][x]='x';
	if(!iswin(y,x,'x')) {
		for(i=0;i<4;i++) {
			for(j=0;j<4;j++) {
				if(table[i][j]=='.' && !oloss(i,j)) {
					table[y][x]='.';
					return 0;
				}
			}
		}
	}
	table[y][x]='.';
	return 1;
}
int oloss(int y, int x)
{
	int i, j;

	table[y][x]='o';
	if(!iswin(y,x,'o')) {
		for(i=0;i<4;i++) {
			for(j=0;j<4;j++) {
				if(table[i][j]=='.' && xwin(i,j)) {
					table[y][x]='.';
					return 1;
				}
			}
		}
	}
	table[y][x]='.';
	return 0;	
}
void proc()
{
	int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			if(table[i][j]=='.' && xwin(i,j)) {
				wy=i;
				wx=j;
				return;
			}
		}
	}
}
void main()
{
	inp();
	proc();
	oup();
}