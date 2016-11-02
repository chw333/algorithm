#include <iostream.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 2)

const int MAX_PEOPLE = 15;
const int MAX_NAME   = 15;
char Names[MAX_PEOPLE][MAX_NAME];
int Money[MAX_PEOPLE];

int numPeople;                        // number in current 'session'

int
Index(char *s)
// postcondition: return index of string s in global string array     
{
    int k;
    for(k=0; k < numPeople; k++){
	if (strcmp(Names[k],s) == 0){
	    return k;
	}
    }
    cerr << "big trouble, can't find " << s << endl;
    return 0;
}

int
ReadGroup()
{
    if (cin >> numPeople){
	int k;
	for(k=0; k < numPeople; k++){
	    cin >> Names[k];
	}
	    // eat new line
	char buf[MAX_NAME];
	cin.getline(buf,MAX_NAME);

	for(k=0; k < numPeople; k++){
	    Money[k] = 0;
	}
	    // read a person
	for(k=0; k < numPeople; k++){
	    cin >> buf;
	    int where = Index(buf);
	    int money;
	    cin >> money;
	    Money[where] -= money;    // person had it, gives it away
	    int j,donees;
	    cin >> donees;            // # of friends to give to
	    
	    int given = 0;
	    if (donees != 0){         // got any friends?
		given = money/donees;
		Money[where] += money % donees;  // keep leftovers
	    }
	    else{
		    // keep it, but already took it away, so double
		Money[where] += 2*money;
	    }
	    for(j=0; j < donees; j++){ // give money to friends
		cin >> buf;
		Money[Index(buf)] += given;
	    }
	    cin.getline(buf,MAX_NAME);
	}
	return 1;
    }
    else{
	return 0;         // nothing to read, must be done
    }
}

main()
{
    while (ReadGroup()){
	int k;
	cout << endl;
	for(k=0; k < numPeople; k++){
	    cout << Names[k] << " " << Money[k] << endl;
	}
    }
}
