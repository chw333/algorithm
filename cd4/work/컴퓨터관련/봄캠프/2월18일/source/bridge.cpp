#include <math.h>
#include <stdio.h>

FILE *fin = fopen("bridge.in", "r");
FILE *fout = fopen("bridge.out", "w");

#define MAXN	2000
#define MAXM	5000

int n, m;
float l;
int town[MAXN][2];
int edge[MAXM*2][2], link[MAXN][MAXN];
float dist[MAXN][MAXN];
float three[3][MAXN];

void input(void)
{
	int i, u, v;
	
	fscanf(fin, "%d %d %f", &n, &m, &l);
	for (i = 0; i < n; i++)
		fscanf(fin, "%d %d", &town[i][0], &town[i][1]);
	for (i = 0; i < m; i++) {
		fscanf(fin, "%d %d", &u, &v);
		edge[i][0] = --u, edge[i][1] = --v;
		edge[i+m][0] = v, edge[i+m][1] = u;
		link[u][v] = link[v][u] = 1;
	}
	fclose(fin);
}

void shortest(int src, float *D)
{
	int i, j, u, v, flag = 1;
	float w;

	D[src] = 0;
	for (i = 0; i < n-1 && flag; i++)
		for (j = flag = 0; j < m; j++)
		{
			u = edge[j][0], v = edge[j][1];
			if (!link[u][v]) continue;
			if (D[v] > (w=D[u] + dist[u][v]))
			{
				flag = 1;
				D[v] = w;
			}
		}
}

void process(void)
{
	int i, j, ans_i, ans_j;
	float ans_dist, tmp;

	for (i = 0; i < n-1; i++)
		for (j = i+1; j < n; j++)
			dist[i][j] = dist[j][i] = sqrt((town[i][0]-town[j][0])*(town[i][0]-town[j][0]) + (town[i][1]-town[j][1])*(town[i][1]-town[j][1]));

	m <<= 1;
	for (i = 0; i < n; i++) three[0][i] = 10000; shortest(0, three[0]);
	for (i = 0; i < n; i++) three[1][i] = 10000; shortest(1, three[1]);
	for (i = 0; i < n; i++) three[2][i] = 10000; shortest(2, three[2]);

	ans_dist = three[0][1] + three[0][2];
	ans_i = ans_j = -1;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (i == j || link[i][j] || dist[i][j] > l) continue;
			
			if (three[0][i] + three[1][j] + dist[i][j] < three[0][1] &&
			    three[0][i] + three[2][j] + dist[i][j] < three[0][2])
			{
				tmp = three[0][i] + three[1][j] + three[2][j] + 2 * dist[i][j];
				if (tmp < ans_dist) ans_dist = tmp, ans_i = i, ans_j = j;
			}
		}

	fprintf(fout, "%f %f\n", three[0][1] + three[0][2], ans_dist);
	fprintf(fout, "%d %d\n", ans_i+1, ans_j+1);
	fprintf(fout, "%f %f\n", three[0][ans_i]+dist[ans_i][ans_j]+three[1][ans_j], three[0][ans_i]+dist[ans_i][ans_j]+three[2][ans_j]);
	fclose(fout);
}

int main(void)
{
	input();
	process();

	return 0;
}
