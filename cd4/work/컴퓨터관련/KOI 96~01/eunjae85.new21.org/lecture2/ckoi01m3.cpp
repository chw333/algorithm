#include <stdio.h>
#include <fstream.h>

const int maxn = 1000;
const char *infile = "input2.txt";
const char *outfile = "output.txt";

int i, j, k, n, m;
int D1[maxn*2], D2[maxn*2];
long S1[maxn*2], S2[maxn*2], answer, t;

long *timer = (long*)(0x0040006c), start;

void input()
{

  ifstream in (infile);
  in >> t;
  in >> n >> m;
  for (i = 0; i < n; i++) {
	in >> D1[i];
	D1[n + i] = D1[i];
  }
  for (i = 0; i < m; i++) {
	in >> D2[i];
	D2[m + i] = D2[i];
  }
  in.close();

  for (i = 0; i < n*2; i++) {
	if (i == 0) S1[i] = D1[i];
	else S1[i] = S1[i - 1] + D1[i];
  }

  for (i = 0; i < m*2; i++) {
	if (i == 0) S2[i] = D2[i];
	else S2[i] = S2[i - 1] + D2[i];
  }

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

void process()
{

  int front, rear, i, j, temp;

  for (i = 0; i < n; i++)
  for (j = i; j < i + n-1; j++) {
	temp=sum1(i,j);
	if (temp > t) break;
	if (temp == t) {
	  answer++;
	  break;
	}
	if (temp + S2[m - 1] < t) continue;

	front = 0;  rear = 0;  temp=t-temp;
	do {
	  if (temp == sum2(front, rear)) {
	   answer++;
	   front++;
	  }
	  while(temp > sum2(front, rear) && rear < m*2) rear++;
	  while(temp < sum2(front, rear) && front < m*2) front++;
	  if (front > rear) rear = front;
	  if (front >= m || rear >=m*2) break;
	  if (rear - front >= m - 1) break;
	} while (1);
  }
  if (S1[n - 1] == t) answer++;
  if (S2[m - 1] == t) answer++;

}

void output()
{

  ofstream out (outfile);
  out << answer;
  out.close();

}

void main()
{

  start = *timer;

  input();
  process();
  output();

  printf("%1.5f\n", (*timer - start)/18.2);

}