#include <stdio.h>
#include <fstream.h>
#include <mem.h>

const int maxn = 500;
const char *infile = "input1.txt";
const char *outfile = "output.txt";
const float timecut = 18.2*10;

long *timer = (long*)(0x0040006c), start;

int i, j, k, n, numleaf;
int edge[maxn][2];
int path[maxn][2], len[maxn];  // solution

// arrays for function "init"
char leaf[maxn], echeck[maxn];
int temp_len;

// array for funtion "dist"
int used_node[maxn];

void input()
{

  ifstream in (infile);
  in >> n;
  for (i = 0; i < n - 1; i++) {
    in >> edge[i][0] >> edge[i][1];
    edge[i][0]--;
    edge[i][1]--;
  }
  in.close();

}

int findpath(int now, int depth)
{

  int i, j, k;
  if (depth != 0) {
	if (leaf[now] == 1) {
	  temp_len = depth;
	  return now;
	}
  }

  for (i = 0; i < n - 1; i++) {
	if (echeck[i] == 1) continue;
	if (edge[i][0] != now && edge[i][1] != now) continue;
	echeck[i] = 1;
	if (edge[i][0] == now) k = findpath(edge[i][1], depth + 1);
	else k = findpath(edge[i][0], depth + 1);
	if (k != -1) return k;
	echeck[i] = 0;
  }

  return -1;

}

int delpath(int now, int target)
{

  int i, j, k;

  if (now == target) return 1;

  for (i = 0; i < n - 1; i++) {
	if (echeck[i] == 0) continue;
	if (edge[i][0] != now && edge[i][1] != now) continue;
	echeck[i] = 0;
	if (edge[i][0] == now) j = delpath(edge[i][1], target);
	else if (edge[i][1] == now) j = delpath(edge[i][0], target);
	if (j == 0) return 1;
	echeck[i] = 1;
  }

  return 0;

}

int first(int now)
{

  int i, j, k;
  if (now > numleaf/2) return 0;
  else if (now == numleaf/2) {
	k = 0;
	for (i = 0; i < n - 1; i++)
	  if (echeck[i] == 0) k++;
	if (k == 0) return 1;
	else return 0;
  }

  for (i = 0; i < n; i++) {
	if (leaf[i] == 0) continue;
	temp_len = 0;
	j = findpath(i, 0);
	path[now][0] = i;  path[now][1] = j;
	len[now] = temp_len;
	leaf[i] = 0;  leaf[j] = 0;
	if (first(now + 1) == 1) return 1;
	leaf[i] = 1;  leaf[j] = 1;
	k = delpath(i, j);
  }
  return 0;

}

void init()
{

  int temp[maxn];
  memset(temp, 0, maxn);
  // checking leaf nodes
  for (i = 0; i < n - 1; i++) {
	temp[edge[i][0]]++;
	temp[edge[i][1]]++;
  }
  for (i = 0; i < n; i++) {
	if (temp[i] == 1) {
      leaf[i] = 1;
      numleaf++;
    } else leaf[i] = 0;
  }
  // until now

  k = first(0); // making initial solution

}

int dist(int i, int j)
{

  int q[maxn], trace_q[maxn];
  int count = 0, front = 0, rear = 0, k;
  char flag[maxn];
  memset(flag, 0, maxn);
  memset(q, 0, maxn);
  q[0] = i;  flag[i] = 1;  trace_q[0] = -1;

  do {
	for (k = 0; k < n - 1; k++) {
	  if (edge[k][0] == q[front]) {
		if (flag[edge[k][1]] == 0) {
		  rear++;
		  q[rear] = edge[k][1];
		  trace_q[rear] = front;
		  flag[edge[k][1]] = 1;
		}
	  } else if (edge[k][1] == q[front]) {
		if (flag[edge[k][0]] == 0) {
		  rear++;
		  q[rear] = edge[k][0];
		  trace_q[rear] = front;
		  flag[edge[k][0]] = 1;
		}
	  }
	  if (flag[j] == 1) break;
	}
	if (flag[j] == 1) break;
	front++;
  } while (front <= rear);

  do {
	used_node[count++] = q[rear];
    rear = trace_q[rear];
	if (rear == -1) break;
  } while (1);

  return count - 1;

}

int fmax(int i, int j)
{

  if (i >= j) return i;
  else return j;

}

int fmin(int i, int j)
{

  if (i <= j) return i;
  else return j;

}

void swap(int *i, int *j)
{

  int k;
  k = *i;  *i = *j;  *j = k;

}

void lc()
{

  int max, index1, index2, len1, len2, common;
  char check[maxn];
  int p1a, p1b, p2a, p2b, l1a, l1b, l2a, l2b, poss = 0;

  do {
	max = 0;
	for (i = 0; i < numleaf/2; i++)
	  if (len[i] > max) {
		max = len[i];  index1 = i;
	  }
	memset(check, 0, maxn);
	len1 = dist(path[index1][0], path[index1][1]);
	for (i = 0; i <= len1; i++) check[used_node[i]] = 1;

	// search new path and common node

	for (index2 = 0; index2 < numleaf/2; index2++) {
	  if (index1 == index2) continue;
	  len2 = dist(path[index2][0], path[index2][1]);
	  for (common = 0; common <= len2; common++)
		if (check[used_node[common]] == 1) break;
	  if (check[used_node[common]] == 0) continue;

	  common = used_node[common];
	  if (*timer - start > timecut) return;

	  // checking
	  p1a = path[index1][0];  p1b = path[index1][1];
	  p2a = path[index2][0];  p2b = path[index2][1];
	  l1a = dist(p1a, common);  l2a = dist(p2a, common);
	  l1b = len1 - l1a;  l2b = len2 - l2a;

	  k = fmin(fmax(l1a + l2a, l1b + l2b), fmax(l1a + l2b, l1b + l2a));
	  poss = 1;
	  if (k > fmax(l1a + l1b, l2a + l2b)) continue;
	  break;
	}

	if (poss == 0) continue;

	if (k == fmax(l1a + l2a, l1b + l2b)) {
	  swap(&path[index1][1], &path[index2][0]);
	  len[index1] = l1a + l2a;  len[index2] = l1b + l2b;
	} else {
	  swap(&path[index1][1], &path[index2][1]);
	  len[index1] = l1a + l2b;  len[index2] = l1b + l2a;
	}
  } while (1);

}

void output()
{

  ofstream out (outfile);
  int max = 0, i, j, k, l;
  for (i = 0; i < numleaf/2; i++)
    if (len[i] > max) max = len[i];
  out << max << endl;
  out << numleaf/2 << endl;

  for (i = 0; i < numleaf/2; i++) {
    l = dist(path[i][0], path[i][1]);
	for (j = 0; j <= l; j++)
	  out << used_node[j] + 1 << " ";
	out << endl;
  }

  out.close();

}

void main()
{

  start = *timer;
  input();
  init();
  lc();
  output();

}