#include <iostream.h>
#include <string.h>
#include <strstream.h>
#include <ctype.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 6)

const int MAX_CHARS = 10000;
const int MAX_SMALL = 50;
const int MAX_TITLES = 1000;
const int MAX_IN_TITLE = 15;
const int COL = 40;             // for alligning output at 40th col

char StringSpace[MAX_CHARS];
int currChar;

struct Title{
    char *words[MAX_IN_TITLE];  // words in a title
    int numWords;               // how many
    int keyWord;                // index of keyword in title
};

Title Works[MAX_TITLES];
int numWorks;

char * SmallWords[MAX_SMALL];
int numSmall;

const char * BARRIER = "::";

int operator > (const Title & a, const Title & b)
{
    return (strcmp(a.words[a.keyWord],b.words[b.keyWord]) > 0);
}

char *
AddWord(char *s)
// add word to global string space, adjust space, return pointer to word     
{
    char * temp = strcpy(StringSpace+currChar,s);
    currChar += strlen(s)+1;
    return temp;
}

void
ReadIgnore()
{
    char buf[100];
    while (cin >> buf && strcmp(buf,BARRIER) != 0){
	SmallWords[numSmall] = AddWord(buf);
	numSmall++;
    }
}

int IsIgnore(char * s)
// postcondition: returns 1 iff s is a 'word to ignore'     
{
    int k;
    for(k=0; k < numSmall; k++){
	if (strcmp(s,SmallWords[k]) == 0){
	    return 1;
	}
    }
    return 0;
}

void
Rotate(const Title & title)
// add occurrence of title to Works once for each keyword in title     
{
    int k;
    for(k = 0; k < title.numWords; k++){
	if (!IsIgnore(title.words[k])){
	    Works[numWorks] = title;
	    Works[numWorks].keyWord = k;
	    numWorks++;
	}
    }
}

void
ToLower(char *s)
// postcondition: s all lower case     
{
    int len = strlen(s);
    for(int k=0; k < len; k++){
	s[k] = tolower(s[k]);
    }
}

void
PrintUpper(char *s)
// postcondition: s printed in all upper case     
{
    int len = strlen(s);
    for(int k=0; k < len; k++){
	cout << char(toupper(s[k]));
    }
}

void
SortTitles()
// selection sort used (it's stable) to sort Works     
{
    int j,k,loc;
    Title hold;
    
    for(k=1; k < numWorks;k++) {
	hold = Works[k];
	loc = k;
	while (loc > 0 && Works[loc-1] > hold){
	    Works[loc] = Works[loc-1];
	    loc--;
	}
	Works[loc] = hold;
    }
}

void
PrintTitle(const Title & title)
{
    int j;
    int sum = 0;
#ifdef ALIGN
    for(j=0; j < title.keyWord; j++){
	sum += strlen(title.words[j])+1;
    }
    for(j=0; j < COL - sum; j++){
	cout << " ";
    }
#endif
    for(j=0; j < title.numWords; j++){
	if (j == title.keyWord){
	    PrintUpper(title.words[j]);
	}
	else{
	    cout << title.words[j];
	}
	cout << " ";
    }
    cout << endl;    
}

void
WriteTitles()
{
    int k;
    for(k=0; k < numWorks; k++){
	PrintTitle(Works[k]);
    }
}

void
ReadTitles()
{
    Title title;
    char buf[256];
    while (cin.getline(buf,256)){
	ToLower(buf);
	    // on some DEC machines need to add trailing
	    // whitespace to buf for single-word titles
	istrstream input(buf);
	char word[100];
	int count = 0;
	while (input >> word){
	    title.words[count] = AddWord(word);
	    count++;
	}
	title.numWords = count;
	Rotate(title);
    }
}

main()
{
    ReadIgnore();
    ReadTitles();
    SortTitles();
    WriteTitles();
}


