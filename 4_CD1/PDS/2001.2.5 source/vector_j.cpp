#include<stdio.h>

#define MAXD 200

int u, d, n;
char c[MAXD+1][MAXD+1];
char p[MAXD+1];

int a[11];
FILE *outfile;

void readfile()
{
	FILE *infile = fopen("vector.in", "rt");
	fscanf(infile, "%d %d %d", &u, &d, &n);
	fclose(infile);
}

void output()
{
	int i;
	for(i=1; i<=n; i++)
		fprintf(outfile, "%d ", a[i]);
	fprintf(outfile, "\n");
}

void back(int i, int j)
{
	int k, err, l1, l2;
	if(i > n) { output(); return; }

	for(; j <= d; j++)
		if(p[j] != 1) {
			err = 0;
			for(l1 = 1; l1 <= i-1; l1++)
				if(c[j][a[l1]] != 1) err = 1;
			if(err == 0) {
				a[i] = j;
				back(i+1, j+1);
			}
		}
}

int gcd(int a, int b)
{
	int t;
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}


void process()
{
	int i, j;

	for(i=1; i<=MAXD-1; i++)
		for(j=i+1; j<=MAXD; j++) {
			if(gcd(j, i) == 1) { c[i][j] = 1; c[j][i] = 1; } else { c[i][j] = 0; c[j][i] = 0; }
		}

	for(i=2; i<=MAXD; i++) p[i] = 1;
	for(i=2; i<=MAXD; i++)
		if(p[i] == 1)
			for(j=2; i*j <= MAXD; j++)
				p[i*j] = 0;
	outfile = fopen("vector.out", "wt");
	back(1, u);
	fprintf(outfile, "-1");
	fclose(outfile);
}

int main()
{
	readfile();
	process();
	return 0;
}