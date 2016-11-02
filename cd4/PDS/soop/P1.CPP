#include<stdio.h>

#define infilename "p1.in"
#define outfilename "p1.out"

struct point {
	int x, y;
} p[100];

int n;

float max = -1;

void input()
{
	int i;
	FILE *infile = fopen(infilename, "rt");
	fscanf(infile, "%d", &n);
	for(i=0; i<n; i++)
		fscanf(infile, "%d %d", &p[i].x, &p[i].y);
	fclose(infile);
}

float compute(struct point p1, struct point p2, struct point p3)
{
	return (p1.x*p2.y - p1.y*p2.x + p2.x*p3.y - p2.y*p3.x + p3.x*p1.y - p3.y*p1.x) / 2.0;
}

void process()
{
	int i, j, k;
	float area;

	for(i=0; i<n-2; i++)
		for(j=i+1; j<n-1; j++)
			for(k=j+1; k<n; k++) {
				area = compute(p[i], p[j], p[k]);
				if (area > max) max = area;
			}
}

void output()
{
	FILE *outfile = fopen(outfilename, "wt");
	fprintf(outfile, "%0.2f", max);
	fclose(outfile);
}

int main()
{
	input();
	process();
	output();
	return 0;
}
