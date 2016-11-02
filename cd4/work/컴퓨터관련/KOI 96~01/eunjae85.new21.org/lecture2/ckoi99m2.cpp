#include <fstream.h>

typedef struct {
	int x, y;
} point;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int fc[4] = {2, 3, 0, 1};

int n, k;
int a[51][51];
point s, e;

int check[51][51];
int trace[51][51];

int min (int a, int b)
{
	if (a > b) return b;
				else return a;
}

int max (int a, int b)
{
	if (a > b) return a;
				else return b;
}

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	in >> s.x >> s.y >> e.x >> e.y;
	in >> k;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = 1;

	int t;
	in >> t;

	for (i = 0; i < t; i++) {
		int q;
		in >> q;

		int x1, y1, x2, y2;

		in >> x1 >> y1;
		for (j = 1; j < q; j++) {
			in >> x2 >> y2;

			for (int x = min (x1, x2); x <= max (x1, x2); x++)
				for (int y = min (y1, y2); y <= max (y1, y2); y++)
					a[x][y] = k;

			x1 = x2;
			y1 = y2;
		}
	}

	in.close ();
}

void process ()
{
	for (int x = 1; x <= n; x++)
		for (int y = 1; y <= n; y++)
			check[x][y] = 30000;

	point que[5000];
	int front = 1, rear = 0;

	que[0] = e;
	check[e.x][e.y] = a[e.x][e.y];
	trace[e.x][e.y] = 9999;

	while (front != rear) {
		point p;

		p = que[rear];
		rear++;
		if (rear == 5000) rear = 0;

		for (int i = 0; i < 4; i++) {
			point t;
			t.x = p.x + dx[i];
			t.y = p.y + dy[i];

			if ((t.x < 1) || (t.x > n) || (t.y < 1) || (t.y > n)) continue;

			if (check[p.x][p.y] + a[t.x][t.y] < check[t.x][t.y]) {
				check[t.x][t.y] = check[p.x][p.y] + a[t.x][t.y];
				trace[t.x][t.y] = fc[i];

				que[front] = t;
				front++;
				if (front == 5000) front = 0;
			}
		}
	}
}

void output ()
{
	int x, y;
	int t1[2000], t2[2000];
	int tc = 0;

	ofstream out ("output.txt");

	out << check[s.x][s.y] << endl;

	int temp = -1;

	x = s.x;
	y = s.y;

	for (;;) {
		if (trace[x][y] != temp) {
			t1[tc] = x;
			t2[tc] = y;
			tc++;
		}

		temp = trace[x][y];
		if (temp == 9999) break;

		x = x + dx[temp];
		y = y + dy[temp];
	}

	out << tc << " ";
	for (int i = 0; i < tc; i++)
		out << t1[i] << " " << t2[i] << " ";

	out.close ();
}

void main()
{
	input ();
	process ();
	output ();
}
