#include <fstream.h>

int N;
int X[5000], Y[5000];
ifstream fin;
ofstream fout;

void input ()
{
	fin.open ("4-1.in");
	fin >> N;
	for (int i = 0; i < N; i++)
		fin >> X[i] >> Y[i];
	fin.close();
}

void swap (int *temp1, int *temp2)
{
	int temp = *temp1; *temp1 = *temp2; *temp2 = temp;
}

void quicksort(int left, int right)
{
	if (left + 1 < right)
	{
		int lptr, rptr, temp;
		lptr = left-1; rptr = right-1; temp = X[right-1];
		while (1)
		{
			while (X[++lptr] < temp);
			while (X[--rptr] > temp && rptr > left);
			if (lptr >= rptr) break;
			swap (&X[lptr], &X[rptr]);
			swap (&Y[lptr], &Y[rptr]);
		}
		swap (&X[lptr], &X[right-1]);
		swap (&Y[lptr], &Y[right-1]);
		quicksort (left, lptr);
		quicksort (lptr+1, right);
	}
}

void solve ()
{
	quicksort(0, N);

	fout.open ("output.txt");
	fout << N-2 << endl;
	for (int i = 0; i < N-2; i++)
		fout << "(" << X[i] << ", " << Y[i] << ") - (" << X[i+1] <<
				", " << Y[i+1] << ") - (" << X[i+2] << ", " << Y[i+2] << ")" << endl;
	fout.close();
}

void main ()
{
	input();
	solve();
}