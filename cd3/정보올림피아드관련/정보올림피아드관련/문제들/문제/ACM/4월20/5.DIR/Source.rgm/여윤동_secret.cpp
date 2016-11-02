#include<fstream.h>
#include<stdlib.h>
#include<time.h>

void init(void);
void process(void);
int sf(const void * , const void *);
void process2(void);
void out(void);

int n , m;
struct {int st , en , dis;} Road[20001];
bool del[20001];
int selects[2001];
int nmr[20001];
int color[2001];
unsigned min , min2 = 99999999;
clock_t st , en;

void main(void){
	st = clock();
	init();
	process();
	process2();
	out();
}

void process(void){
	int cnt = 0;
	int co , cc;
	int i , j;
	for(i=1; i<=m; i++)
		if(color[Road[nmr[i]].st] != color[Road[nmr[i]].en]){
			cnt++;
			selects[cnt] = i;
			min += Road[nmr[i]].dis;
			co = color[Road[nmr[i]].en];
			cc = color[Road[nmr[i]].st];
			for(j=1; j<=n; j++)
				if(color[j] == co) color[j] = cc;
			if(cnt == n - 1) break;
		}
}

void process2(void){
	int cnt = 0;
	int co , cc;
	int i , j , k , l;
	int d2 = 0;
	unsigned dis;
	for(k=1; k<=n - 1; k++){
		dis = 0;
		del[selects[k - 1]] = 0;
		del[selects[k]] = 1;
		for(l=1; l<=n; l++)
			color[l] = l;
		for(i=1; i<=m; i++)
			if(color[Road[nmr[i]].st] != color[Road[nmr[i]].en] && del[i] != 1){
				en = clock();
				if((double)(((double)en - (double)st) / (double)CLOCKS_PER_SEC) >= 1.89){
					min2 = min + 1;
					out();
				}
				cnt++;
				dis += Road[nmr[i]].dis;
				if(dis > min2) break;
				co = color[Road[nmr[i]].en];
				cc = color[Road[nmr[i]].st];
				for(j=1; j<=n; j++)
					if(color[j] == co) color[j] = cc;
				if(cnt == n - 1) break;
			}
		if(dis < min2 && dis != min && cnt == n - 1){
			min2 = dis;
		}
		if(min2 == min + 1) break;
	}
}

void out(void){
	ofstream op("secret.out");
	op << min2;
	op.close();
	exit(0);
}

void init(void){
	int i;
	ifstream in("secret.in");
	in >> n >> m;
	for(i=1; i<=m; i++){
		in >> Road[i].st >> Road[i].en >> Road[i].dis;
		nmr[i] = i;
	}
	Road[0].dis = -1;
	for(i=1; i<=n; i++)
		color[i] = i;
	qsort((void *)nmr , m + 1 , sizeof(int) , sf);
}

int sf(const void *a1 , const void *b1){
	int a2 = Road[*(int *)a1].dis , b2 = Road[*(int *)b1].dis;
	if(a2 > b2) return 1; else if(a2 == b2) return 0; else return -1;
}