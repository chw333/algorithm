#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int a, b, n;
int e[20][20], p[20][20], re[20][20], rp[20][20];
long sum, result = -1;
struct s_tile {
	int p, q;
	int a[10][10];
} s[10];

struct _el {
	int t, i1, j1, i2, j2, v;
} el[1001];
int eln = 0;

int h[1001], hn=0;

long stime;

void input()
{
	FILE *infile = fopen("cover.inp", "rt");
	int l1, i, j;
	fscanf(infile, "%d %d", &a, &b);
	fscanf(infile, "%d", &n);

	for(l1=0; l1<n; l1++) {
		fscanf(infile, "%d %d", &s[l1].p, &s[l1].q);
		for(i=0; i<s[l1].p; i++)
			for(j=0; j<s[l1].q; j++)
				fscanf(infile, "%d", &s[l1].a[i][j]);
	}
	fclose(infile);
}

void upheap(int i)
{
	int x = h[i];
	while (el[h[i/2]].v < el[x].v) { h[i] = h[i/2]; i /= 2; }
	h[i] = x;
}

void insert(struct _el x)
{
	el[eln++] = x;
	h[++hn] = eln-1;
	upheap(hn);
}

void downheap(int i)
{
	int x = h[i];

	while(1) {
		i *= 2;
		if(i > hn) break;
		if(i < hn && el[h[i]].v < el[h[i+1]].v) i++;
		if(el[x].v > el[h[i]].v) break;
		h[i/2] = h[i];
	}
	i /= 2;
	h[i] = x;
}

int delete_()
{
	int x = h[1];
	h[1] = h[hn--];
	downheap(1);
	return x;
}

void add(int i1, int j1, int i2, int j2, int t)
{
	if(i1 < 0 || i1 >= a || j1 < 0 || j1 >= b) return;
	if(i2 < 0 || i2 >= s[t].p || j2 < 0 || j2 >= s[t].q) return;
	if(e[i1][j1] > 0 || s[t].a[i2][j2] <= 0) return;
	struct _el temp;
	temp.i1 = i1;
	temp.j1 = j1;
	temp.i2 = i2;
	temp.j2 = j2;
	temp.v = s[t].a[i2][j2];
	temp.t = t;
	insert(temp);
}

void solve()
{
	int i, j, t;

	for(i=0; i<a; i++)
		for(j=0; j<b; j++) {
			e[i][j] = 0;
			p[i][j] = -1;
		}
	sum = 0;
	eln = 0;
	
	// Creating Start Point & Insert Q

	for(t=0; t<n; t++) {
		struct _el t_el[100]; int t_eln=0, count=0, choice; float ave=0;

		for(i=0; i<s[t].p; i++) {
			for(j=0; j<s[t].q; j++) {
				if(s[t].a[i][j] > 0)  {
					ave += s[t].a[i][j];
					count++;
				}
			}
		}

		ave /= count;
		for(i=0; i<s[t].p; i++) {
			for(j=0; j<s[t].q; j++) {
				if((float)s[t].a[i][j] >= ave) {
					t_el[t_eln].t = t;
					t_el[t_eln].i2 = i;
					t_el[t_eln].j2 = j;
					t_el[t_eln].i1 = rand()%a;
					t_el[t_eln].j1 = rand()%b;
					t_el[t_eln].v = s[t].a[i][j];
					t_eln++;
				}
			}
		}
		if (t_eln > 0) {
			choice = rand() % t_eln;
			insert(t_el[choice]);
		}
	}

	while(hn > 0) {
		int cur = delete_();
		int i1 = el[cur].i1, j1 = el[cur].j1, i2 = el[cur].i2, j2 = el[cur].j2, t = el[cur].t;

		if(e[i1][j1] > 0) continue;
		sum += el[cur].v;
		e[i1][j1] = el[cur].v;
		p[i1][j1] = el[cur].t;

		add(i1+1, j1, i2+1, j2, t);
		add(i1-1, j1, i2-1, j2, t);
		add(i1, j1+1, i2, j2+1, t);
		add(i1, j1-1, i2, j2-1, t);
	}

}

void update()
{
	int i, j;
	result = sum;

	for(i=0; i<a; i++)
		for(j=0; j<b; j++) {
			re[i][j] = e[i][j];
			rp[i][j] = p[i][j];
		}
}

void process()
{
	h[0] = 1000;
	el[1000].v = 999;
	while (1) {
		if((clock()-stime) > 5*CLK_TCK ) {
			break;
		}
		solve();
		if(sum > result) update();
	}
}

void output()
{
	FILE *outfile = fopen("cover.out", "wt");
	fprintf(outfile, "%d %d\n", a, b);
	fprintf(outfile, "%ld\n", result);
	int i, j;

	for(i=0; i<a; i++) {
		for(j=0; j<b; j++)
			fprintf(outfile, "%d ", re[i][j]);
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\n");
	for(i=0; i<a; i++) {
		for(j=0; j<b; j++)
			fprintf(outfile, "%d ", rp[i][j]+1);
		fprintf(outfile, "\n");
	}
	
	fclose(outfile);
}

int main()
{
	srand(time(NULL));
	stime = clock();
	input();
	process();
	output();
	return 0;
}
