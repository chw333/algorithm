#include <stdio.h>
#include <fstream.h>

const int maxn = 1000;
const int maxm = 10000;
const char *infile = "input.txt";
const char *outfile = "output.txt";

int i, j, k, n1, n2, t;
int D1[maxn], D2[maxn];
long S1[maxn], S2[maxn];
long huge T1[maxm + 1], T2[maxm + 1];
long answer;

void input()
{

  ifstream in (infile);
  in >> t;
  in >> n1;
  for (i = 0; i < n1; i++)
	in >> D1[i];
  in >> n2;
  for (i = 0; i < n2; i++)
	in >> D2[i];
  in.close();

}

long sum1(int i, int j)
{

  if (i == 0) return S1[j];
  else return S1[j] - S1[i - 1];

}

long sum2(int i, int j)
{

  if (i == 0) return S2[j];
  else return S2[j] - S2[i - 1];

}

void init()
{

  for (i = 0; i < n1; i++) {
	if (i == 0) S1[i] = D1[i];
	else S1[i] = S1[i - 1] + (long)D1[i];
  }

  for (i = 0; i < n2; i++) {
	if (i == 0) S2[i] = D2[i];
	else S2[i] = S2[i - 1] + (long)D2[i];
  }

  if (n1 > n2) k = n1;
  else k = n2;

  for (i = 0; i < k; i++)
	for (j = 0; j <= i; j++) {
	  if (i < n1 && sum1(j, i) <= 10000) T1[sum1(j, i)]++;
	  if (i < n2 && sum2(j, i) <= 10000) T2[sum2(j, i)]++;
	}

}

void process()
{

  for (i = 1; i < t; i++)
	answer += T1[i]*T2[t - i];

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
  init();
  process();
  output();

}