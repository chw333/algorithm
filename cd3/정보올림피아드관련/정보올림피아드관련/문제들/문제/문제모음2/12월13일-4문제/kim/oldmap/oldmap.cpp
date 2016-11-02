#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define INFILE "oldmap.in"
#define OUTFILE "oldmap.out"

#define MAXN 1024
#define MAXREG (2*MAXN)
#define EPS (1e-11)



int N, K;             //n은 노드의 수, K는 순환해야할 노드의 수
int p[MAXN][2];       //노드의 좌표
short g1[MAXN][MAXN]; //파일에서 읽은 노드의 인접행렬
short g[MAXN][MAXN];  //인접리스트로 저장.

int deg[MAXN];        //인접리스트의 i의 연결되 노드 수.
short g2[MAXN][MAXN]; //g1에서 복사
int deg2[MAXN];       //deg에서 복사.

int inv[MAXN];
int st[MAXN];
int ist;
int used[MAXN];
double nb[MAXN][2];
int nnb;
int P;



void read_all(void);
void do_all(void);
void makereg(void);
int cmp_nb(const void *a, const void *b);
void write_all(void);



int main(void)
{
	read_all();
	do_all();
	write_all();
	return 0;
}



void read_all(void)
{
	int i, d, a;

	FILE *f = fopen(INFILE, "rt");
	fscanf(f, "%d", &N);
	for (i = 0; i < N; i++) {
		fscanf(f, "%d %d %d", &p[i][0], &p[i][1], &d);
		while (d--) {
			fscanf(f, "%d", &a);  a--;
			g1[i][a] = g1[a][i] = 1;
		}
	}
	fscanf(f, "%d", &K);
	fclose(f);
}



void do_all(void)
{
	int i, j, u;

	/*nb[0][0] = atan2(1, 10001);
	nb[0][1] = atan2(1, 10000);
	nb[1][0] = nb[0][0]-nb[0][1];*/
	for (i = 0; i < N; i++) {
		nnb = 0;
		for (j = 0; j < N; j++) {
			if (g1[i][j] == 0)  continue;
			//i에서 j로 연결되었다면,
			//i에서 j로 연결된 각도를 nb에 저장.
			nb[nnb][0] = j;
			nb[nnb][1] = atan2(p[j][1]-p[i][1], p[j][0]-p[i][0]);
			nnb++;
		}
		//i에서 j로 연결된 각도롤 정렬.
		qsort(nb, nnb, sizeof(nb[0]), cmp_nb);

		//정렬된 순서대로, j번호를 g[i]배열에 저장.
		for (j = 0; j < nnb; j++) {
			g[i][deg[i]++] = nb[j][0];
		}
	}
	memmove(g2, g1, sizeof(g1));
	memmove(deg2, deg, sizeof(deg));
	for (;;) {
		int ni = 0;
		for (i = 0; i < N; i++) {
			if (deg2[i] == 1) {
				inv[i] = 1;
				deg2[i]--;
				ni++;
				for (j = 0; j < deg[i]; j++) {
					u = g[i][j];
					if (g2[i][u] == 0)  continue;
					g2[i][u] = g2[u][i] = 0;
					deg2[u]--;
				}
			}
		}
		if (ni == 0)  break;
	}
	for (i = 0; i < N; i++) {
		if (inv[i])  continue;
		for (j = 0; j < deg[i]; j++) {
			u = g[i][j];
			/*printf("%d %d\n", i, u);*/
			if (inv[u])  continue;
			if (g1[i][u] == 2)  continue;
			ist = 0;
			st[ist++] = i;
			st[ist++] = u;
			memset(used, 0, sizeof(used));
			used[u] = 1;
			g1[i][u] = 2;
			makereg();
		}
	}
}



void makereg(void)
{
	int i, u, v;
	int S;

	for (;;) {
		u = st[ist-1];
		for (i = 0; i < deg[u]; i++) {
			if (g[u][i] == st[ist-2])  break;
		}
		i = (i+1)%deg[u];
		v = g[u][i];
		st[ist++] = v;
		used[v]++;
		g1[u][v] = 2;
		if (v == st[0])  break;
	}
	/*  printf("%d\n", ist-1);*/
	if (ist == K+1) {
		S = 0;
		for (i = 0; i < K; i++) {
			u = st[i];
			v = st[i+1];
			if (used[u] > 1)  return;
			S += (p[u][1]+p[v][1])*(p[u][0]-p[v][0]);
		}
		if (S < 0)  P++;
	}
}



int cmp_nb(const void *a, const void *b)
{
  double res = ((double *)a)[1]-((double *)b)[1];
  if (res < -EPS)  return -1;
  if (res >  EPS)  return  1;
  return 0;
}



void write_all(void)
{
  FILE *f = fopen(OUTFILE, "wt");
  fprintf(f, "%d\n", P);
  fclose(f);
}

