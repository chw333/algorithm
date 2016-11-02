#include <stdio.h>
#include <fstream.h>

const int maxm = 100;
const int maxn = 50;
const char *infile = "input.txt";
const char *outfile = "output.txt";
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct xy {
  int x, y;
};

int i, j, k, n, front = 0, rear = 0;
struct xy data[maxn][4], st, la;
char hurdle[maxm + 1][maxm + 1], flag[maxm + 1][maxm + 1];
char chk_x[maxm + 1], chk_y[maxm + 1];
char checking[maxm + 1][maxm + 1];

int v[maxm*maxm];

void input()
{

  ifstream in (infile);
  in >> st.x >> st.y;
  in >> la.x >> la.y;
  in >> n;
  chk_x[st.x] = 1;  chk_x[la.x] = 1;
  chk_y[st.y] = 1;  chk_y[la.y] = 1;
  for (i = 0; i < n; i++)
	for (j = 0; j < 4; j++) {
	  in >> data[i][j].x >> data[i][j].y;
	  chk_x[data[i][j].x] = 1;
	  chk_y[data[i][j].y] = 1;
	}
  in.close();

}

void init()
{

  struct xy p1, p2, p3, p4, p5, p6;

  for (i = 0; i < n; i++) {
	p1 = data[i][0];  p2 = data[i][1];
	p3 = data[i][2];  p4 = data[i][3];

	if (p1.x == p2.x && p1.y > p2.y) {

	  for (j = p2.y; j <= p1.y; j++) hurdle[j][p1.x] = 2;
	  for (j = p2.x; j <= p3.x; j++) hurdle[p2.y][j] = 1;
	  for (j = p3.y; j <= p4.y; j++) hurdle[j][p3.x] = 2;
	  for (j = p4.x; j <= p3.x; j++) hurdle[p4.y][j] = 1;
	  for (j = p1.x; j <= p4.x; j++) hurdle[p1.x][j] = 1;
	  for (j = p4.y; j <= p1.y; j++) hurdle[j][p4.x] = 2;
	  hurdle[p1.y][p4.x] = 3;  hurdle[p4.y][p3.x] = 3;

	} else if (p1.y == p2.y && p1.x < p2.x) {

	  for (j = p1.x; j <= p2.x; j++) hurdle[p1.y][j] = 1;
	  for (j = p2.y; j <= p3.y; j++) hurdle[j][p2.x] = 2;
	  for (j = p1.x; j <= p4.x; j++) hurdle[p4.y][j] = 1;
	  for (j = p4.x; j <= p3.x; j++) hurdle[p3.y][j] = 1;
	  for (j = p1.y; j <= p4.y; j++) hurdle[j][p1.x] = 2;
	  for (j = p4.y; j <= p3.y; j++) hurdle[j][p4.x] = 2;
	  hurdle[p4.y][p1.x] = 3;  hurdle[p3.y][p4.x] = 3;

	} else if (p1.x == p2.x && p1.y < p2.y) {

	  for (j = p3.x; j <= p2.x; j++) hurdle[p3.y][j] = 1;
	  for (j = p3.x; j <= p4.x; j++) hurdle[p4.y][j] = 1;
	  for (j = p4.x; j <= p1.x; j++) hurdle[p1.y][j] = 1;
	  for (j = p4.y; j <= p3.y; j++) hurdle[j][p3.x] = 2;
	  for (j = p1.y; j <= p4.y; j++) hurdle[j][p4.x] = 2;
	  for (j = p1.y; j <= p2.y; j++) hurdle[j][p1.x] = 2;
	  hurdle[p4.y][p3.x] = 3;  hurdle[p1.y][p4.x] = 3;

	} else {

	  for (j = p2.x; j <= p1.x; j++) hurdle[p2.y][j] = 1;
	  for (j = p3.x; j <= p4.x; j++) hurdle[p3.y][j] = 1;
	  for (j = p4.x; j <= p1.x; j++) hurdle[p4.y][j] = 1;
	  for (j = p3.y; j <= p2.y; j++) hurdle[j][p3.x] = 2;
	  for (j = p3.y; j <= p4.y; j++) hurdle[j][p4.x] = 2;
	  for (j = p4.y; j <= p1.y; j++) hurdle[j][p1.x] = 2;
	  hurdle[p4.y][p1.x] = 3;  hurdle[p3.y][p4.x] = 3;

	}
	hurdle[p1.y][p1.x] = 3;  hurdle[p2.y][p2.x] = 3;
	hurdle[p3.y][p3.x] = 3;  hurdle[p4.y][p4.x] = 4;
  }

}

char check(int x, int y, int d)
{

  y -= dy[d];  x -= dx[d];
  if (hurdle[y][x] == 0) return 1;
  else if (hurdle[y][x] == 4) {
	if ((d == 0 || d == 2) && hurdle[y + dy[d]][x + dx[d]] == 1) return 1;
	else if ((d == 0 || d == 2) && hurdle[y + dy[d]][x + dx[d]] == 3) return 1;
	else if ((d == 1 || d == 3) && hurdle[y + dy[d]][x + dx[d]] == 2) return 1;
	else if ((d == 1 || d == 3) && hurdle[y + dy[d]][x + dx[d]] == 3) return 1;
	else return 0;
  }
  else if (hurdle[y][x] == 3) return 1;
  else {
	if (d == 2*(d/2)) {
	  if (checking[y + dy[d]][x + dx[d]] != 1 && hurdle[y][x] == 2) return 0;
	  else return 1;
	} else {
	  if (checking[y + dy[d]][x + dx[d]] != 1 && hurdle[y][x] == 1) return 0;
	  else return 1;
	}
  }

}

void ff()
{

  struct xy q[(maxm + 1)*(maxm + 1)];
  int front = 0, rear = 0, i, tx, ty;
  char flag[maxm + 1][maxm + 1];

  for (i = 0; i <= maxm; i++)
	for (j = 0; j <= maxm; j++)
	  flag[i][j] = 0;

  q[0].x = 0;  q[0].y = 0;
  checking[0][0] = 1;
  do {
	for (i = 0; i < 4; i++) {
	  ty = q[front].y + dy[i];
	  tx = q[front].x + dx[i];
	  if (ty < 0 || tx < 0 || ty > maxm || tx > maxm) continue;
	  if (flag[ty][tx] == 0 && hurdle[ty][tx] == 0) {
		rear++;
		q[rear].x = q[front].x + dx[i];
		q[rear].y = q[front].y + dy[i];
		checking[q[rear].y][q[rear].x] = 1;
		flag[q[rear].y][q[rear].x] = 1;
	  }
	}
	front++;
  } while (front <= rear);

}

void bfs()
{

  struct xy q[maxm*maxm];
  int x, y, tx, ty;
  q[0].x = st.x;  q[0].y = st.y;
  v[0] = -1;
  flag[st.y][st.x] = 1;

  do {
	for (i = 0; i < 4; i++) {
	  x = q[front].x;
	  y = q[front].y;
	  do {
		x += dx[i];  y += dy[i];
		if (y < 1 || x < 1 || y > maxm || x > maxm) break;
		if (flag[y][x] == 1) continue;
		if (check(x, y, i) == 0) break;

		if (((i == (i/2)*2) && (chk_x[x] == 1)) || ((i != (i/2)*2) && (chk_y[y] == 1))) {
		  rear++;
		  q[rear].x = x;  q[rear].y = y;
		  v[rear] = v[front] + 1;
		  flag[y][x] = 1;
		  if (flag[la.y][la.x] == 1)
			return;
		}
	  } while (1);
	}
	front++;
  } while (front <= rear);

}

void output()
{

  ofstream out (outfile);
  out << v[rear];
  out.close();

}

void main()
{

  input();
  init();
  ff();
  bfs();
  output();

}