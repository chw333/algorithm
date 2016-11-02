// prob1c.cpp

#include <fstream.h>
#include <process.h>

#define INFILE "busfare10.in"
#define OUTFILE "busfare10.out"

const int MAXFARE = 500;
const int NUMFARES = 10;
const int MAXTRIP = 10000;

int cost[MAXTRIP + 1];

main()
{
   // C++ arrays normally start at zero, however here i start at 1 (by ignoring 0)
	
	int i;
	ifstream in(INFILE, ios::nocreate);
    if(in == NULL)
    {
		cout << "Error file doesn't exist" << endl;
		exit(1);
    }
	for(i = 1; i <= NUMFARES; i++)
		in >> cost[i];

	int n;
	in >> n;	// Get number of km to be travelled.

    // Initialise the remaining entries to be the max possible
    for(i = 11; i <= n; i++)
        cost[i] = MAXFARE * n / NUMFARES;

	// Now we need to adjust the fares to find the cheapest way of travelling 10 k
	for(i = 2; i <= n; i++)
		for(int j = 1; j <= i/2; j++)
			if(cost[j] + cost[i-j] < cost[i])
				cost[i] = cost[j] + cost[i-j];

	ofstream(OUTFILE) << cost[n] << endl;

	return 0;
}
