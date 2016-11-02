#include <stdio.h>
#include <fstream.h>

const int maxn = 128;
const char *infile = "input2.txt";
const char *outfile = "output.txt";

int i, j, k, n, w, b;
int data[maxn][maxn];

void input()
{

  ifstream in (infile);
  in >> n;
  for (i = 0; i < n; i++)
	for (j = 0; j < n; j++)
	  in >> data[i][j];
  in.close();

}

void fdnc(int x1, int y1, int x2, int y2, int *w, int *b)
{

  int w1, w2, w3, w4, b1, b2, b3, b4, mx, my;
  int i, j, c, k = 0;

  c = data[y1][x1];
  for (i = y1; i <= y2; i++) {
	for (j = x1; j <= x2; j++)
	  if (data[i][j] != c) {
		k = 1;
		break;
	  }
	if (k == 1) break;
  }
  if (k == 0) {
	if (c == 1) {
	  *b = 1;
	  *w = 0;
	} else {
	  *w = 1;
	  *b = 0;
	}
	return;
  }

  mx = (x1 + x2 - 1)/2;
  my = (y1 + y2 - 1)/2;
  fdnc(x1, y1, mx, my, &w1, &b1);
  fdnc(mx + 1, y1, x2, my, &w2, &b2);
  fdnc(x1, my + 1, mx, y2, &w3, &b3);
  fdnc(mx + 1, my + 1, x2, y2, &w4, &b4);
  *w = w1 + w2 + w3 + w4;
  *b = b1 + b2 + b3 + b4;

}

void output()
{

  ofstream out (outfile);
  out << w << endl;
  out << b << endl;
  out.close();

}

void main()
{

  input();
  fdnc(0, 0, n - 1, n - 1, &w, &b);
  output();

}