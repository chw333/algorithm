#include <fstream.h>

#define MAXN 1000
#define MAXM 1000
#define MAXK 200

ifstream fin("path.inp");
ofstream fout("path.out");

int k, n, m;
int a[MAXM][MAXK], buf[MAXK], bb[MAXK], tot = 0;
int dat[MAXN][MAXM];

void input()
{
  fin >> k;
  fin >> n >> m;
  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++)
      fin >> dat[i][j];
  for (int j=0;j<m;j++)
    if (dat[n - 1][j] < k) a[j][dat[n - 1][j]] = 1;
                      else if (dat[n - 1][j] == k) tot++;
  fin.close();
}

void process()
{
  int sr, kx, sl, dt;
  for (int i=n-2;i>=0;i--)
  {
    kx = 0;
    for (int j=0;j<k;j++)
    {
      bb[j] = a[0][j];
      buf[j] = a[m - 1][j];
    }
    for (int j=0;j<m;j++)
    {
      sr = (j + 1) % m;
      dt = dat[i][j];
      for (int l=k-1;l>=0;l--)
      {
        sl = a[j][l];
        if (sr == 0) a[j][l] = a[j][l] + buf[l] + bb[l];
                else a[j][l] = a[j][l] + buf[l] + a[sr][l];
        if (a[j][l] != 0)
        {
          kx = 1;
          if (l + dt < k) a[j][l + dt] = a[j][l];
                     else if (l + dt == k) tot += a[j][l];
          a[j][l] = 0;
        }
        buf[l] = sl;
      }
    }
    if (kx == 0) break;
    sl = 0;
  }
}

void output()
{
  fout << tot << endl;
  fout.close();
}

void main()
{
  input();
  process();
  output();
}