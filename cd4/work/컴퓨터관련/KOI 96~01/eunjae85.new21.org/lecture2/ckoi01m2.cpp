#include <stdio.h>
#include <fstream.h>

const int maxn = 200;
const char *infile = "input.txt";
const char *outfile = "output.txt";

int i, j, k, n, answer;
int data[maxn];
int C[maxn];

void input()
{

  ifstream in (infile);
  in >> n;
  for (i = 0; i < n; i++)
	in >> data[i];
  in.close();

}

void dynamic()
{

  for (i = 0; i < n; i++) {
	C[i] = 1;
	for (j = 0; j < i; j++) {
	  if (data[j] < data[i] && C[i] < C[j] + 1)
		C[i] = C[j] + 1;
	}
  }

  k = 0;
  for (i = 0; i < n; i++)
	if (C[i] > k)
	  k = C[i];

  answer = n - k;

}

void output()
{

  ofstream out (outfile);
  out << answer;
  out.close();

}

void main()
{

  input();
  dynamic();
  output();

}