/*
	Only use in TC++
*/
#include <fstream.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

clock_t start;

int fff = 0;

int l, d;
int m, n;

int x, y;
int x1[4] = {0, 0, -1, 1};
int y1[4] = {-1, 1, 0, 0};

int a[30][30];
int b[30][30];

int dis[30][30];

int escape = 0;

void input()
{
	FILE *fp;
	int i, j;

	fp = fopen("race.inp", "r");

	fscanf(fp, "%d%d", &l, &d);
	fscanf(fp, "%d%d", &m, &n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			b[i][j] = 0;
			fscanf(fp, "%d", &a[i][j]);
			if (a[i][j] == 0)
			{
				x = j;
				y = i;
			}
		}

	/*
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	*/
	fclose(fp);

}

void dijkstra()
{
	int i, j, k, o;
	int y1, x1;
	int v[30][30];
	int min;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			v[i][j] = 0;
			dis[i][j] = 32000;
		}

	v[y][x] = 1;
	dis[y][x] = 0;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			min = 32000;

			for (k = 0; k < m; k++)
				for (o = 0; o < n; o++)
				{
					if (v[k][o] == 1 && dis[k][o] < min)
					{
						y1 = k;
						x1 = o;
						min = dis[k][o];
					}
				}

			v[y1][x1] = 0;

			for (k = 0; k < m; k++)
				for (o = 0; o < n; o++)
				{
					if (dis[y1][x1] + a[k][o] < dis[k][o] && (abs(k - y1) + abs (o - x1)) == 1)
					{
						dis[k][o] = dis[y1][x1] + a[k][o];
						v[k][o] = 1;
					}
				}

		}
	/*
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			cout << dis[i][j] << " ";
		cout << endl;
	}
	*/

}

void output()
{
	ofstream out("race.out");

	int i, j;
	int flag;

	if (fff == 1)
	{
		out << y + 1 << " " << x + 1 << endl;

		while (1)
		{
			flag = 0;
			for (i = 0; i < 4; i++)
			{
				if (y + y1[i] >= 0 && y + y1[i] < m)
					if (x + x1[i] >= 0 && x + x1[i] < n)
						if (b[y + y1[i]][x + x1[i]] == 1)
						{
							out << y + y1[i] + 1 << " " << x + x1[i] + 1 << endl;
							b[y + y1[i]][x + x1[i]] = 0;
							flag = 1;
							y += y1[i];
							x += x1[i];
							break;
						}
			}

			if (flag == 0)
				break;
		}
	}
	else
	{
		out << "None" << endl;
	}
	out.close();
}

void rec(int yy, int xx, int t, int arr, int arrValue)
{
	int i, j;
	int k, o;
	int tempX, tempY;
	int flag;
	int temp;

	int tY, tX;

	if ((clock() - start)/18.206 > 5)
		escape = 1;

	if (t <= l && escape == 0)
	{
		/*
		for (k = 0; k < m; k++)
		{
			for (o = 0; o < n; o++)
				cout << b[k][o] << " ";
			cout << endl;
		}
		cout << t << endl;
		getch();
		*/

		for (i = 0; i < 4; i++)
		{
			tempX = xx + x1[i];
			tempY = yy + y1[i];

			if (tempY >= 0 && tempY < m)
				if (tempX >= 0 && tempX < n && b[tempY][tempX] == 0)
				{
					flag = 0;
					for (j = 0; j < 4; j++)
						if (y1[i] + y1[j] != 0 || x1[i] + x1[j] != 0)
						{
							if (tempY + y1[j] >= 0 && tempY + y1[j] < m)
								if (tempX + x1[j] >= 0 && tempX + x1[j] < n)
								{
									if (b[tempY + y1[j]][tempX + x1[j]] == 1)
									{
										flag = 1;
										break;
									}
								}
						}
					if (tempY == y && tempX == x && t == l)
					{
						temp = 0;
						for (k = 0; k < 4; k++)
						{
							if (tempY + y1[k] >= 0 && tempY + y1[k] < m)
								if (tempX + x1[k] >= 0 && tempX + x1[k] < n)
									temp += b[tempY + y1[k]][tempX + x1[k]];
						}
						if (temp == 2)
							flag = 0;
					}
					if (flag == 0)
					{
						tempX = xx + x1[i];
						tempY = yy + y1[i];

						if (tempY == y && tempX == x)
						{
							if (t == l)
							{
								int check = 0;

								for (k = 0; k < 4; k++)
								{
									tY = tempY;
									tX = tempX;
									while(1)
									{
										if (tY < 0 || tY >= m) break;
										if (tX < 0 || tX >= n) break;

										if (b[tY][tX] == 0)
											break;
										check += a[tY][tX];

										tY += y1[k];
										tX += x1[k];
									}
								}

								if (check <= d && escape == 0)
								{
									escape = 1;
									fff = 1;
									output();
								}
							}
						}
						else
						{
							if (arr == i)
							{
								if (arrValue + a[tempY][tempX] <= d)
								{
									if (dis[tempY][tempX] + t - a[tempY][tempX] <= l)
									{
										b[tempY][tempX] = 1;
										rec(tempY, tempX, t + a[tempY][tempX], i, arrValue + a[tempY][tempX]);
										b[tempY][tempX] = 0;
									}
								}
							}
							else
							{
								if (dis[tempY][tempX] + t - a[tempY][tempX] <= l)
								{
									b[tempY][tempX] = 1;
									rec(tempY, tempX, t + a[tempY][tempX], i, a[yy][xx] + a[tempY][tempX]);
									b[tempY][tempX] = 0;
								}
							}
						}

					}
				}
		}
	}
}

void process()
{

	dijkstra();

	rec(y, x, 0, -1, 0);
}

void main()
{
	//clrscr();
	start = clock();
	input();
	process();
	if (fff == 0)
		output();
}