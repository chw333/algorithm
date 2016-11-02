#include <fstream.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INFILE "win04.in"
#define OUTFILE "win04.out"

const int MAXNAMELEN = 17;	// 16 + space for terminating 0

struct SCORE {
	int value;
	char name[MAXNAMELEN + 1];	// could have '+'
	int NumScores;
};

int M, N;
SCORE *score;
int MaxValue = 0;
int *overall;
int MaxOverall = 0;

int Find(SCORE score[], char *name, int n)
{
	int i;
	for(i = 0; i < n; i++)
		if(strcmp(score[i].name, name) == 0)
			return i;

	cerr << "Name not present\n";
	exit(1);
	return -1;	// Keep compiler happy.
}

void ReadInput()
{
	ifstream in(INFILE, ios::nocreate);
	if(in == NULL)
		{
		cerr << "Error no input file\n";
		exit(1);
		}

	// Part 1, read in the different types of scores.
	in >> M; // Number of type of scores
	if(M < 1 || M > 100)
		{
		cerr << "Error bad input\n";
		exit(1);
		}

	score = new SCORE[M];	// Create an array of M scores

	int i;
	for(i = 0; i < M; i++)
		{
		score[i].NumScores = 1;
		in >> score[i].value;
		in >> score[i].name;
		char previous[MAXNAMELEN];
		in >> previous;
		if(previous[0] != '-')
			{
			int p = Find(score, previous, i + 1);	// Find the index

			// The value and numscores of this type, depends on what has gone ahead
			score[i].NumScores = 1 + score[p].NumScores;
			score[i].value += score[p].value;
			}
		else if (!isalpha(score[i].name[0]))
			{
			cerr << "Error bad input\n";
			exit(1);
			}
		if(score[i].value > MaxValue)
			MaxValue = score[i].value;
		}
	// Now read in the overall scores.
	in >> N;
	if(N < 1 || N > 100)
		{
		cerr << "Error bad input\n";
		exit(1);
		}
	overall = new int[N];
	for(i = 0; i < N; i++)
		{
		in >> overall[i];
		if (overall[i] > MaxOverall)
			MaxOverall = overall[i];
		}

	in.close();
}

main()
{
	ReadInput();	// Read in all our variables.

	// Now create an array that will hold the number of scores required for each overall score.
	int *NumScores = new int[MaxOverall+MaxValue];
	cout << "Overall = " << MaxOverall << ", MaxScore = " << MaxValue << endl;

	int i;
	for(i = 0; i < MaxOverall+MaxValue; i++)
		NumScores[i] = MaxOverall+1;	// Initially set to impossible value.

	// Insert all initial scores
	for(i = 0; i < M; i++)
		if (score[i].NumScores < NumScores[score[i].value])
			NumScores[score[i].value] = score[i].NumScores;
	/*
	for(i = 0; i < MaxValue; i++)
		if(NumScores[i] != MaxOverall+1)
			cout << "Score " << i << " achieved in " << NumScores[i] << " attempts\n";
	*/

	// Add all the scores to the table
	for(i = 0; i < MaxOverall; i++)
		if(NumScores[i] != MaxOverall+1)
			// Can we reach this score, then try all scores from here
			for(int j = 0; j < M; j++)
				{
				int NextScore = i + score[j].value;
				int Num = NumScores[i] + score[j].NumScores;
				if (Num < NumScores[NextScore])
					NumScores[NextScore] = Num;	// improve this score
				}

	/*
 	for(i = 0; i < MaxOverall; i++)
		if(NumScores[i] != MaxOverall+1)
			cout << "Score " << i << " achieved in " << NumScores[i] << " attempts\n";
	*/

	// Finally, output the solution
	ofstream out(OUTFILE);
	for(i = 0; i < N; i++)
		if(NumScores[overall[i]] != MaxOverall+1)
			out << NumScores[overall[i]] << endl;
		else
			out << "0\n";

	return 0;
}