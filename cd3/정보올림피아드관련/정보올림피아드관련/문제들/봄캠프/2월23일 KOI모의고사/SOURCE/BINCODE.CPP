#include <fstream.h>

int n;
char data[20002];
int table[20002];
int g = 0;

int main()
{
	ifstream fin("bincode.inp");
	fin >> n;
	int a = 0, b = 0;
	for(int i = 0; i < n; i++)
	{
		char c;
		fin >> c;
		data[i] = c - 48;
		if (data[i] == 0) b++;
	}
	for(i = 0; i < n; i++)
	{
		if (data[i] == 0) table[a++] = i;
		else table[b++] = i;
	}
	fin.close();
	ofstream fout("bincode.out");
	for(i = 0; i < n; i++)
	{
		if (data[table[g]] == 0) fout << "0 "; else fout << "1 ";
		g = table[g];
	}
	fout << endl;
	fout.close();
	return 0;
}