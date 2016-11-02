#include <iostream.h>
#include <strstream.h>
#include <ctype.h>

// author: Steve Tate   (srt@cs.unt.edu)
// converted from C to C++ by Owen Astrachan
// for internet programming contest 1993 (problem 7)    
     

const int ALPH_SIZE = 26;

int adj[ALPH_SIZE][ALPH_SIZE];
int nadj[ALPH_SIZE][ALPH_SIZE];
char charlist[ALPH_SIZE];
int nchar;

char order[ALPH_SIZE];
int used[ALPH_SIZE];

int CheckIt(int pos, char newChar)

{
    int i;

    for (i=0; i<pos; i++)
	if (adj[newChar-'a'][order[i]-'a'])
	    return(0);
    return(1);
}

void Orders(int pos)
{
    int i;

    if (pos == nchar) {
	for (i=0; i<nchar; i++){
	    cout << order[i] << " ";
	}
	cout << endl;
	return;
    }

    for (i=0; i<nchar; i++) {
	if (!used[charlist[i]-'a']) {
	    if ((pos == 0) || ((pos > 0) && (CheckIt(pos, charlist[i])))) {
		order[pos] = charlist[i];
		used[charlist[i]-'a'] = 1;
		Orders(pos+1);
		used[charlist[i]-'a'] = 0;
	    }
	}
    }
}

int Process()
{
    const int BUF_SIZE = 300;
    char buf[BUF_SIZE];
    int i, j;
    int ch;

    nchar = 0;

    for (i=0; i<ALPH_SIZE; i++)
	for (j=0; j<ALPH_SIZE; j++)
	    adj[i][j] = 0;

    if (!cin.getline(buf,BUF_SIZE)){
	return (0);
    }
	// read alphabet into charlist
    
    istrstream input(buf);
    while (input >> charlist[nchar]){
	nchar++;
    }
	// sort charlist

    for(i=0; i < nchar-1; i++){
	int min = i;
	for(j=i+1; j < nchar; j++){
	    if (charlist[j] < charlist[min])
		min = j;
	}
	ch = charlist[i]; charlist[i] = charlist[min]; charlist[min] = ch;
    }

    cin.getline(buf,BUF_SIZE);

	// read order pairs, set up adjacency matrix
    
    istrstream pairs(buf);
    char s, d;
    while (pairs >> s >> d){
	adj[s-'a'][d-'a'] = 1;	
    }
    Orders(0);

    cout << endl;

    return(1);
}

int main()
{
    while (Process()){
	// do nothing
    }
    return(0);
}

