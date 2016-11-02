#include <fstream.h>

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int n, m;
int a[100][100] = {0, };

char que[10000][2];
int front, rear;

void input ()
{
	ifstream in ("input.txt");

	in >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			in >> a[i][j];

	in.close ();
}

void floodfill ()
{
	char check[100][100] = {0, };

	front = 1;
	rear = 0;

	que[0][0] = 0;
	que[0][1] = 0;
	check[0][0] = 1;

	while (front != rear) {
		int i, j;

		i = que[rear][0];
		j = que[rear][1];
		rear++;

		for (int k = 0; k < 4; k++) {
			int ni, nj;

			ni = i + dy[k];
			nj = j + dx[k];

			if ((ni < 0) || (ni >= n) || (nj < 0) || (nj >= n)) continue;

			if (a[ni][nj] >= 1) a[ni][nj]++;

			if ((a[ni][nj] == 0) && !check[ni][nj]) {
				check[ni][nj] = 1;
				que[front][0] = ni;
				que[front][1] = nj;
				front++;
			}
		}
	}
}

void process ()
{
	for (int count = 0; ;count++) {
		int flag = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (a[i][j] >= 3) a[i][j] = 0;
				if (a[i][j] == 2) a[i][j] = 1;
				if (a[i][j] == 1) flag = 1;
			}

		if (!flag) break;

		floodfill ();
	}

	ofstream out ("output.txt");

	out << count << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
