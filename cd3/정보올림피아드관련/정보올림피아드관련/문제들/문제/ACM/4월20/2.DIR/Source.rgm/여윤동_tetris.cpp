#include<fstream.h>
#include<stdlib.h>
#define Bang 3
#define Maxq 50000

void init(void);
void process(void);
void bfs(void);
void out(void);

const int py[Bang + 1] = {0 , 1 , 0 , 0};
const int px[Bang + 1] = {0 , 0 , -1 , 1};

int dy[Maxq + 1] = {0 , };
int dx[Maxq + 1] = {0 , };
bool a[501][101];
bool b[101][101];
int check[501][101];
int n , m , n1 , m1;
int count;
int y , y1;
int max = -1;

void main(void){
	init();
	process();
	bfs();
	out();
}

void init(void){
	int i , j;
	char c;
	ifstream in("tetris.in");
	in >> n >> m;
	for(i=1; i<=n; i++)
		for(j=1; j<=m; j++){
			in >> c;
			if(c != '.') y = i;
			if(c == '.') a[i][j] = 0; else a[i][j] = 1;
		}
	in >> n1 >> m1;
	for(i=1; i<=n1; i++)
		for(j=1; j<=m1; j++){
			in >> c;
			if(y1 == 0 && c != '.') y1 = i;
			if(c == '.') b[i + 250][j] = 0; else b[i + 250][j] = 1;
		}
	n1 = 500;
}

void process(void){
	int i , j , k , l;
	for(i=1; i<=n1 - n + 1; i++)
		for(j=1; j<=m1 - m + 1; j++){
			for(k=i; k<=i + n - 1; k++){
				for(l=j; l<=j + m - 1; l++)
					if(b[k][l] == 1 && a[k - i + 1][l - j + 1] == 1) break;
				if(l != j + m) break;
			}
			if(k == i + n){
				check[i][j] = 1;
				count++;
			}
		}
}

void bfs(void){
	int tx , ty , t , t2 , i;
	int l = 1 , cnt = 0;
	dy[l] = 1;
	dx[l] = 1;
	do{
		cnt++;
		if(cnt > Maxq) cnt = 1;
		tx = dx[cnt];
		ty = dy[cnt];
		for(i=1; i<=Bang; i++){
			t = ty + py[i];
			t2 = tx + px[i];
			if(t <= n1 && t2 >= 1 && t2 <= m1 && check[t][t2] == 1){
				check[t][t2] = 2;
				l++;
				if(l > Maxq) l = 1;
				dy[l] = t;
				dx[l] = t2;
				if(t > max) max = t;
			}
		}
		if(cnt == l) break;
	} while(1);
}

void out(void){
	ofstream op("tetris.out");
	max = max + y - 1;
	if(max == 500) op << "pass"; else{
		if(count == 0) max = 250;
		max -= 250;
		op << abs(max - (y1 - 1));
	}
}
