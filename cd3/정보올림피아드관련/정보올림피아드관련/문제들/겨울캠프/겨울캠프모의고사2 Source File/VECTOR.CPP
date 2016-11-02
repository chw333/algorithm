#include <stdlib.h>
#include <time.h>
#include <fstream.h>
#include <stdio.h>

ifstream fin("vector.in");
FILE *fout = fopen("vector.out", "wt");

int path[11], t[2002][4], p[2000], check[2002] = {0, }, prime[2000];
int tt, x, u, d, n, ttime, stime;

void input()
{
  fin >> u >> d >> n;
  fin.close();
}

void process(int k, int num)
{
  int l;
  if (k == n)
  {
    for (int i=0;i<n;i++)
      fprintf(fout, "%d ", path[i]);
    fprintf(fout, "\n");
    if (clock() - stime >= ttime)
    {
      fprintf(fout, "-1");
      fclose(fout);
      exit(0);
    }
  }
  else
  {
    check[0] = 0;
    check[2001] = 1;
    for (int i=num;i<=d;i++)
    {
      if (!(check[t[i][0]] + check[t[i][1]] + check[t[i][2]] + check[t[i][3]]))
      {
        for (int j=0;j<p[i];j++)
          check[t[i][j]] = 1;
        path[k] = i;
        process(k + 1, i + 1);
        for (int j=0;j<p[i];j++)
          check[t[i][j]] = 0;
      }
    }
  }
}

void compute()
{
  x = 2;
  prime[0] = 2;
  prime[1] = 3;
  t[2][0] = 2001;
  t[3][0] = 2001;
  int sw;
  for (int i=5;i<=d;i+=2)
  {
    sw = 0;
    for (int j=0;j<x&&prime[j]*prime[j]<=i;j++)
      if (i % prime[j] == 0) sw = 1;
    if (sw == 0)
    {
      prime[x] = i;
      t[i][0] = 2001;
      x++;
    }
  }
  for (int i=u;i<=d;i++)
  {
    for (int j=0;j<x;j++)
      if (i % prime[j] == 0 && i != prime[j])
      {
        t[i][p[i]] = prime[j];
        p[i]++;
      }
  }
}


void main()
{
  stime = clock();
  ttime = (int)(2.8 * CLK_TCK);
  input();
  compute();
  process(0, u);
  fprintf(fout, "-1\n");
  fclose(fout);
}
