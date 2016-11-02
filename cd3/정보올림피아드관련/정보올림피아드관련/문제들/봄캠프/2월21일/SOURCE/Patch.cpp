#include <fstream.h>
#include <time.h>

int s,n, m, max, cnt1[101], cnt2[101], Pow[22];
int chk[1048577];
int arr[101];
int index[1048577];
char index2[1048577];
char chk2[1048577];
int queue[4200000];
int arr2[101][2], arr3[101][2];

void input()
{
	int l1, l2, se;
	char tmp;
		
	ifstream fin("patch.inp");
	fin >> n >> m;
	se = 1;
	for (l1 = 0; l1 <= n; l1++)
	{
		Pow[l1] = se;
		se <<= 1;
	}
	for (l1 = 1; l1 <= m; l1++)
	{
		fin >> arr[l1];
		for (l2 = 0; l2 < n; l2++)
		{
			fin >> tmp;
			if (tmp == '+') arr2[l1][0] += Pow[l2]; 
			if (tmp == '-') arr2[l1][1] += Pow[l2];
		}
		for (l2 = 0; l2 < n; l2++)
		{
			fin >> tmp;
			if (tmp == '+') arr3[l1][0] += Pow[l2]; 
			if (tmp == '-') arr3[l1][1] += Pow[l2]; 
		}
	}
}

void process()
{
	int tmp, l1, head, tail, now, now2, nowtot;
	
	head = 0; tail = 0;
	chk[0] = 2147483647;
	s = Pow[n] - 1;
	for (l1 = 0; l1 < s; l1++)
		chk[l1] = 2147483647;
	queue[++tail] = s;
	do
	{
		head++;
		if (head == 4200000) head = 0;
		nowtot = chk[queue[head]];
		now2= queue[head];
		chk2[now2] = 0;
		for (l1 = 1; l1 <= m; l1++)
		{
			now = now2;
			if ((now & arr2[l1][0]) != arr2[l1][0]) continue;
			if ((now & arr2[l1][1]) != 0) continue;
			now |= arr3[l1][0];
			now |= arr3[l1][1];
			now -= arr3[l1][1];
			tmp = nowtot + arr[l1];
			if (chk[now] > tmp && tmp < chk[0])
			{
				chk[now] = tmp; 
				if (chk2[now] == 0)
				{
					tail++;
					if (tail == 4200000) tail = 0;
					queue[tail] = now;
					index[now] = now2;
					index2[now] = l1;
					chk2[now] = 1;
				}	
			}
		}
	} while (head != tail);
}

void output()
{
	int l1, ff, length;
	
	ofstream fout("patch.out");
	if (chk[0] == 2147483647) fout << 0;
	else
	{
		fout << chk[0] << endl;
		ff = length = 0;
		while (ff != s)
		{	
			chk2[++length] = index2[ff];
			ff = index[ff];
		}
		for (l1 = length; l1 >= 1; l1--)
			fout << (int)chk2[l1] << ' ';
	}
}	

int main()
{
	input();
	process();
	output();
	return 0;
}