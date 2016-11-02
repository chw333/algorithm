#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>

ifstream in("goods.in");
ofstream out("goods.out");

#define MAXSIZE 300
#define CHARS 26

char Word[MAXSIZE];	/* Vstupni/vystupni slovo */
int CC[CHARS];		/* Pocty jednotlivych znaku */
int Len;		/* Delka vstupniho slova */

/* Nacte vstup */
void ReadInp(void)
{
	in >> Word;
    Len = strlen(Word);
}

/* Spocte pocty znaku ve vstupnim slove */
void ParseInp(void)
{
  int i;

  memset(CC, 0, CHARS);
  for (i = 0; i < Len; i++)
    CC[Word[i]-'a']++;
}

/* Vytiskne vsechny anagramy */
void Anagram(int Done)
{
  int i;

  for (i = 0; i < CHARS; i++)
    if (CC[i])	/* Nepouzity znak? */
    {
      Word[Done] = 'a' + i;
      if (Done == Len - 1)	/* Pouzili jsme posledni znak? */
      {
        /* Vypiseme radek */
		Word[Len] = '\0';
		out << Word << endl;
      }
      else
      {
        /* Rekurzivne zkousime dalsi znaky */
        CC[i]--;
        Anagram(Done + 1);
        CC[i]++;
      }
    }
}

void main(void)
{
  ReadInp();	/* Nacte vstup */
  ParseInp();	/* Spocte pocty znaku ve vstupnim slove */
  Anagram(0);	/* Vypise vsechny anagramy */
}

