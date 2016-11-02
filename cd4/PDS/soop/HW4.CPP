#include <conio.h>
#include <stdio.h>

#define MAXN 30

typedef struct {
	int x1, y1;
	int x2, y2;
} rect;

int n, nx, ny;
rect R[MAXN];

int x[MAXN*2], y[MAXN*2];
int color[MAXN*2][MAXN*2] = {0, }, ncolor = 1;

void input(void);
void sort_xy(void);

#define LEFT	1
#define RIGHT	2
#define UP      4
#define DOWN	8

void fill(int i, int j, int c)        // has some errors
{
	int k, block = 0;

	if (color[i][j] != 0) return;
	color[i][j] = c;

	for (k = 0; k < n; k++)
	{
		if (i <= 0 || (R[k].x1 == x[i] && R[k].x2 == x[i] && R[k].y1 <= y[j] && R[k].y2 >= y[j+1]))
			block |= LEFT;
		if (i >= nx - 1 || (R[k].x1 == x[i+1] && R[k].x2 == x[i+1] && R[k].y1 <= y[j] && R[k].y2 >= y[j+1]))
			block |= RIGHT;
		if (j <= 0 || (R[k].y1 == y[j] && R[k].y2 == y[j] && R[k].x1 <= x[i] && R[k].x2 >= x[i+1]))
			block |= DOWN;
		if (j >= ny - 1 || (R[k].y1 == y[j+1] && R[k].y2 == y[j+1] && R[k].x1 <= x[i] && R[k].x2 >= x[i+1]))
			block |= UP;
	}

	if (!(block&LEFT))	fill(i - 1, j, c);
	if (!(block&RIGHT))	fill(i + 1, j, c);
	if (!(block&UP))	fill(i, j + 1, c);
	if (!(block&DOWN))	fill(i, j - 1, c);
}

void process(void)
{
	int i, j;
	long area[100] = {0, };

	for (i = 0; i < n; i++) {
		x[i*2] = R[i].x1, x[i*2+1] = R[i].x2;
		y[i*2] = R[i].y1, y[i*2+1] = R[i].y2;
	}
	sort_xy();

	for (i = 0; i < nx - 1; i++)
		for (j = 0; j < ny - 1; j++)
			if (color[i][j] == 0)
				fill(i, j, ncolor++);

	for (i = 0; i < nx - 1; i++)
		for (j = 0; j < ny - 1; j++)
			area[color[i][j]] += (x[i+1] - x[i]) * (y[j+1] - y[j]);

	printf("%ld\n", ncolor - 1);
	for (i = 1; i < ncolor; i++)
		printf("%ld\n", area[i]);
}

int main(void)
{
	clrscr();
	input();
	process();

	return 0;
}

void input(void)
{
	FILE *in = fopen("p4.in", "r");
	int x1, x2, y1, y2, tmp;
	fscanf(in, "%d %d %d %d", &x1, &x2, &y1, &y2);
	fscanf(in, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(in, "%d %d %d %d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2);
		if (R[i].x1 > R[i].x2) tmp = R[i].x1, R[i].x1 = R[i].x2, R[i].x2 = tmp;
		if (R[i].y1 > R[i].y2) tmp = R[i].y1, R[i].y1 = R[i].y2, R[i].y2 = tmp;
	}

	R[n].x1 = x1, R[n].y1 = y1, R[n].x2 = x2, R[n].y2 = y1, n++;
	R[n].x1 = x1, R[n].y1 = y1, R[n].x2 = x1, R[n].y2 = y2, n++;
	R[n].x1 = x1, R[n].y2 = y2, R[n].x2 = x2, R[n].y2 = y2, n++;
	R[n].x1 = x2, R[n].y2 = y1, R[n].x2 = x2, R[n].y2 = y2, n++;

	fclose(in);
}

void sort_xy(void)
{
	int i, j, tmp;
	nx = ny = n * 2;

	for (i = 0; i < nx; i++)
		for (j = i + 1; j < ny; j++)
		{
			if (x[i] > x[j]) tmp = x[i], x[i] = x[j], x[j] = tmp;
			if (y[i] > y[j]) tmp = y[i], y[i] = y[j], y[j] = tmp;
		}

	for (i = 0; i < nx - 1; i++)
		while (x[i] == x[i+1]) {
			for (j = i + 1; j < nx; j++)
				x[j] = x[j+1];
			nx--;
		}
	for (i = 0; i < ny - 1; i++)
		while (y[i] == y[i+1]) {
			for (j = i + 1; j < ny; j++)
				y[j] = y[j+1];
			ny--;
		}
}

