#include <fstream.h>
#include <stdlib.h>

#define vertical 0
#define horizon  1

#define left 0
#define right 1
#define up 2
#define down 3
#define turn 4
#define unknown 5
#define start 6

typedef struct {
	int i, j;
	int st;
} point;

int t[2] = {1, 0};

int n;
int a[50][50];
int check[50][50][2];
int dis[50][50][2];

point que[2000];
int front = 1, rear = 0;

point sp, ep;
int len;

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	char str[200];
	point sa, sb, ea, eb;
	sa.i = -1;
	ea.i = -1;

	for (int i = 0; i < n; i++) {
		in >> str;
		for (int j = 0; j < n; j++) {
			if (str[j] == '1') a[i][j] = 1;
										else a[i][j] = 0;

			if ((str[j] == 'B') && (sa.i == -1)) {
				sa.i = i;
				sa.j = j;
			}

			if (str[j] == 'B') {
				sb.i = i;
				sb.j = j;
			}

			if ((str[j] == 'E') && (ea.i == -1)) {
				ea.i = i;
				ea.j = j;
			}

			if (str[j] == 'E') {
				eb.i = i;
				eb.j = j;
			}
		}
	}

	sp.i = (sa.i + sb.i) / 2;
	sp.j = (sa.j + sb.j) / 2;
	if (sa.i == sb.i) sp.st = horizon;
							 else sp.st = vertical;

	ep.i = (ea.i + eb.i) / 2;
	ep.j = (ea.j + eb.j) / 2;
	if (ea.i == eb.i) ep.st = horizon;
							 else ep.st = vertical;

	len = (sb.j - sa.j) + (sb.i - sa.i) + 1;
}

int feasible (int i, int j, int st)
{
	int k;

	if (st == horizon) {
		if ((i < 0) || (i >= n)) return 0;

		for (k = j - len / 2; k <= j + len / 2; k++)
			if ((k < 0) || (k >= n) || (a[i][k] == 1))
				return 0;
	} else {
		if ((j < 0) || (j >= n)) return 0;

		for (k = i - len / 2; k <= i + len / 2; k++)
			if ((k < 0) || (k >= n) || (a[k][j] == 1))
				return 0;
	}

	return 1;
}

int feasible2 (int i, int j)
{
	int k, l;

	for (k = i - len / 2; k <= i + len / 2; k++)
		for (l = j - len / 2; l <= j + len / 2; l++)
			if ((k < 0) || (k >= n) || (l < 0) || (l >= n) || (a[k][l] == 1))
				return 0;

	return 1;
}

void output ()
{
	ofstream out ("output.txt");

	point p = sp;
	out << dis[p.i][p.j][p.st] << endl;

	while (check[p.i][p.j][p.st] != start) {
		switch (check[p.i][p.j][p.st]) {
			case up    : { out << "U" << endl;
										 p.i--;
										 break; }
			case down  : { out << "D" << endl;
										 p.i++;
										 break; }
			case left  : { out << "L" << endl;
										 p.j--;
										 break; }
			case right : { out << "R" << endl;
										 p.j++;
										 break; }
			case turn  : { out << "T" << endl;
										 p.st = t[p.st];
										 break; }
		}
	}

	out.close ();

	exit (0);
}

void process ()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			check[i][j][0] = unknown;
			check[i][j][1] = unknown;
		}

	que[0] = ep;
	check[ep.i][ep.j][ep.st] = start;
	dis[ep.i][ep.j][ep.st] = 0;

	while (front != rear) {
		point p;

		p = que[rear];
		rear++;
		if (rear == 2000) rear = 0;

		if ((p.i == sp.i ) && (p.j == sp.j) && (p.st == sp.st)) {
			output ();
		}

		if (feasible (p.i - 1, p.j, p.st) &&
				(check[p.i - 1][p.j][p.st] == unknown)) {

			check[p.i - 1][p.j][p.st] = down;
			dis[p.i - 1][p.j][p.st] = dis[p.i][p.j][p.st] + 1;

			que[front].i = p.i - 1;
			que[front].j = p.j;
			que[front].st = p.st;
			front++;
			if (front == 2000) front = 0;
		}

		if (feasible (p.i + 1, p.j, p.st) &&
				(check[p.i + 1][p.j][p.st] == unknown)) {

			check[p.i + 1][p.j][p.st] = up;
			dis[p.i + 1][p.j][p.st] = dis[p.i][p.j][p.st] + 1;

			que[front].i = p.i + 1;
			que[front].j = p.j;
			que[front].st = p.st;
			front++;
			if (front == 2000) front = 0;
		}

		if (feasible (p.i, p.j - 1, p.st) &&
				(check[p.i][p.j - 1][p.st] == unknown)) {

			check[p.i][p.j - 1][p.st] = right;
			dis[p.i][p.j - 1][p.st] = dis[p.i][p.j][p.st] + 1;

			que[front].i = p.i;
			que[front].j = p.j - 1;
			que[front].st = p.st;
			front++;
			if (front == 2000) front = 0;
		}

		if (feasible (p.i, p.j + 1, p.st) &&
				(check[p.i][p.j + 1][p.st] == unknown)) {

			check[p.i][p.j + 1][p.st] = left;
			dis[p.i][p.j + 1][p.st] = dis[p.i][p.j][p.st] + 1;

			que[front].i = p.i;
			que[front].j = p.j + 1;
			que[front].st = p.st;
			front++;
			if (front == 2000) front = 0;
		}

		if (feasible2 (p.i, p.j) &&
				(check[p.i][p.j][t[p.st]] == unknown)) {

			check[p.i][p.j][t[p.st]] = turn;
			dis[p.i][p.j][t[p.st]] = dis[p.i][p.j][p.st] + 1;

			que[front].i = p.i;
			que[front].j = p.j;
			que[front].st = t[p.st];
			front++;
			if (front == 2000) front = 0;
		}
	}
}

void main ()
{
	input ();
	process ();
}

