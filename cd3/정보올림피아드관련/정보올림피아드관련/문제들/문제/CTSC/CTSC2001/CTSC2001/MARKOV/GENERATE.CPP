#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FINNAME "markov.in"
#define FSAMPLENAME "sample.txt"
#define NPREF 2
#define DIFWORDS difwords[index]
#define TOTALWORDS totalwords[index]
#define PREFIXS prefixs[index]
#define WORDS words[index]
#define RANDOMS randoms[index]
#define MAXWORD 10000
#define MAXWORDLEN 20

char *table[MAXWORD];
FILE *fin = fopen(FINNAME, "w"),
	 *fsample = fopen(FSAMPLENAME, "w");
long difwords[10] = {1, 10, 50, 470, 630, 10000, 5000, 1000, 1000, 1000},
     totalwords[10] = {1, 10, 100, 1000, 10000, 10000, 10000, 10000, 10000, 10000},
     prefixs[10] = {0, 5, 60, 100, 4000, 10000, 100000, 0, 0, 0},
     words[10] = {0, 4, 30, 0, 4000, 0, 50000, 1000000, 2000000, 2000000},
     randoms[10] = {3, 1, 30, 0, 2000, 0, 40000, 0, 0, 0},
     randseed[10] = {107, 51012, 1006, 1103, 909, 926, 999, 7107, 7137, 1};

char *randomword(void)
{
	int l = random(MAXWORDLEN) + 1;
	char *s = (char *)malloc(l + 1);
	for (int i = 0; i < l; i++)
		*(s + i) = random('z' - 'a') + 'a';
	s[l] = '\0';
	return s;
}

void main(int argc, char *argv[])
{
	int index = 0;
	if (argc == 2) index = atoi(argv[1]);
	srand(randseed[index]);
	for (unsigned long i = 0; i < DIFWORDS; i++) {
		table[i] = randomword();
		fprintf(fsample, "%s ", table[i]);
	}
	for (; i < TOTALWORDS; i++) {
		table[i] = table[random(DIFWORDS)];
		fprintf(fsample, "%s ", table[i]);
	}
	fprintf(fin, "%lu\n", (unsigned long)(PREFIXS) + WORDS + RANDOMS);
	for (i = 0; i < PREFIXS; i++) {
		int j;
		j = random(TOTALWORDS - 1);
		fprintf(fin, "%s %s\n", table[j], table[j + 1]);
	}
	for (i = 0; i < WORDS; i++)
		fprintf(fin, "%s %s\n", table[random(TOTALWORDS)], table[random(TOTALWORDS)]);
	for (i = 0; i < RANDOMS; i++) {
		char *s1, *s2;
		s1 = randomword();
		s2 = randomword();
		fprintf(fin, "%s %s\n", s1, s2);
		free(s1);
		free(s2);
	}
	fclose(fin);
	fclose(fsample);
}