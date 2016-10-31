#include<stdio.h>

#define MAXN 5000

int a[MAXN];
int c[7001], v[7001];
int n, t, m;

void readfile()
{
	int i;
	FILE *infile = fopen("fish.inp", "rt");

	fscanf(infile, "%d %d", &n, &t);
	for(i=0; i<n; i++)
		fscanf(infile, "%d", &a[i]);

	fclose(infile);
}

void qsort(int l, int r)
{
	if(l < r) {
		int i=l, j=r+1, t;

		while (1) {
			do i++; while(a[i] > a[l]);
			do j--; while(a[j] < a[l]);

			if(i < j) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			else
				break;
		}
		t = a[l];
		a[l] = a[j];
		a[j] = t;

		qsort(l, j-1);
		qsort(j+1, r);
	}
}

void process()
{
	int i, j;

//	qsort(0, n);

	for(i=0; i<=t; i++) c[i] = -1;

	c[0] = 0;
	for(i=0; i<n; i++)
		for(j=t-a[i]; j >= 0; j--)
			if(c[j] >= 0)
				if(c[j+a[i]] == -1) {
					c[j+a[i]] = c[j] + 1;
					v[j+a[i]] = i;
				}
	m = t;

	while (c[m] < 0) m--;
}

void writefile()
{
	int i;
	FILE *outfile = fopen("fish.out", "wt");
	fprintf(outfile, "%d\n", c[m]);

	i = m;
	while(i > 0) {
		fprintf(outfile, "%d\n", a[v[i]]);
		i = i - a[v[i]];
	}

	fclose(outfile);
}

int main()
{
	readfile();
	process();
	writefile();
	return 0;
}