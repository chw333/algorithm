#include <fstream.h>

const char Infilename[30] = "input.txt";
const char Outfilename[30] = "output.txt";

int n;
int data[30] = {1, 2, 7, 2, 1, 8, 3, 6, 3, 2, 3, 8, 5, 0, 7, 6, 5, 4, 1, 2, 3, 0, 1, 0};

int main()
{
	ifstream fin(Infilename);
	ofstream fout(Outfilename);
	fin >> n;
	for(int i = 0; i < n;i ++)
	{
		long a;
		fin >> a;
		fout << data[a % 24] << endl;
	}
	fout.close();
	fin.close();
	return 0;
}