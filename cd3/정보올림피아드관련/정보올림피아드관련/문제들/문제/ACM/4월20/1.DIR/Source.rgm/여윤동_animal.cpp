#include<fstream.h>
#define Maxn 1000
#define Maxq 1000000
#define Bang 4

void init(void);
int process(void);
int bfs(int , int);
bool mo(int , int);
void clear(void);
void out(void);

const int py[Bang + 1] = {0 , -1 , 1 , 0 , 0};
const int px[Bang + 1] = {0 , 0 , 0 , -1 , 1};

char a[Maxn][Maxn + 1];
int b[Maxn][Maxn];
int n , m;
int dx[Maxq + 1] = {0 , };
int dy[Maxq + 1] = {0 , };
bool visit[Maxn][Maxn] = {{0 , } , };
bool check[Bang + 1];

void main(void){
	init();
	ofstream op("animal.out");
	op << process();
}

void init(void){
	int i;
	ifstream in("animal.in");
	in >> m >> n;
	for(i=0; i<n; i++)
		in >> a[i];
}

int process(void){
	int i , j;
	int k;
	int max = -999999;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			if(a[i][j] != '#')
				if(mo(i , j)){
					k = bfs(i , j);
					clear();
					if(k > max) max = k;
				}
	return max;
}

bool mo(int i , int j){
	int k;
	int t , t2;
	for(k=1; k<=Bang; k++){
		t = i + py[k];
		t2 = j + px[k];
		check[k] = 0;
		if(t < 0 || t >= n || t2 < 0 || t2 >= m){
			check[k] = 1;
			continue;
		} else if(a[t][t2] == '#') check[k] = 1;
	}
	// 1  2  3  4
	// ╩С го аб ©Л
	if((check[1] == 1 && check[3] == 1) || (check[1] == 1 && check[4] == 1) || (check[2] == 1 && check[3] == 1) || (check[2] == 1 && check[4] == 1)) return 1; else return 0;
}

int bfs(int sy , int sx){
	int l = 1 , cnt = 0;
	int x , y , t , t2 , i;
	int max = 0;
	visit[sy][sx] = 1;
	b[sy][sx] = 0;
	dx[l] = sx;
	dy[l] = sy;
	do{
		cnt++;
		if(cnt > Maxq) cnt = 1;
		y = dy[cnt];
		x = dx[cnt];
		for(i=1; i<=Bang; i++){
			t = y + py[i];
			t2 = x + px[i];
			if(t >= 0 && t < n && t2 >= 0 && t2 < m && visit[t][t2] == 0 && a[t][t2] == '.'){
				l++;
				if(l > Maxq) l = 1;
				dy[l] = t;
				dx[l] = t2;
				visit[t][t2] = 1;
				b[t][t2] = b[y][x] + 1;
				if(b[t][t2] > max) max = b[t][t2];
			}
		}
		if(cnt == l) break;
	} while(1);
	return max;
}

void clear(void){
	int i , j;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			visit[i][j] = 0;
}