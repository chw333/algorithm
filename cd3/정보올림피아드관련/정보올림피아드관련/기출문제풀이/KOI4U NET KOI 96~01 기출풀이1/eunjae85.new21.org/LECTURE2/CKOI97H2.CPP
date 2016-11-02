#include <fstream.h>
#include <stdlib.h>

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int n;
int a[50][50];
int check[50][50] = {0, };

int count = 0;

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	char str[200];
	for (int i = 0; i < n; i++) {
		in >> str;

		for (int j = 0; j < n; j++)
			if (str[j] == '1') a[i][j] = 1;
										else a[i][j] = 0;
	}

	in.close ();
}

void output ()
{
	ofstream out ("output.txt");

	out << count << endl;

	out.close ();

	exit (0);
}

void process ()
{
	int qx[3000], qy[3000];
	int nx[3000], ny[3000];
	int front = 1, rear = 0;
	int nc;

	qx[0] = 0;
	qy[0] = 0;

	check[0][0] = 1;

	for (;;) {
		nc = 0;

		while (front != rear) {
			int x, y;

			x = qx[rear];
			y = qy[rear];
			rear++;

			for (int i = 0; i < 4; i++) {
				int xx, yy;

				xx = x + dx[i];
				yy = y + dy[i];

				if ((xx >= 0) && (xx < n) && (yy >= 0) && (yy < n) && (check[xx][yy] != 1)) {
					check[xx][yy] = 1;

					if (a[xx][yy]) {
						qx[front] = xx;
						qy[front] = yy;
						front++;
					} else {
						nx[nc] = xx;
						ny[nc] = yy;
						nc++;
					}
				}
			}
		}

		if (check[n - 1][n - 1]) output ();
		count++;

		for (int i = 0; i < nc; i++) {
			qx[i] = nx[i];
			qy[i] = ny[i];
		}
		front = nc;
		rear = 0;
	}
}

void main ()
{
	input ();
	process ();
}