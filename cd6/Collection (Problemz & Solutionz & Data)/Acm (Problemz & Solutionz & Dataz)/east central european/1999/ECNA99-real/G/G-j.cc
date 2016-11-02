/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

#include <iostream>

const int MAXLAKES = 25;
const int MAXHOURS = 16;

struct lake {
  int fish[MAXHOURS*12];                  // store # of fish per 5-min interval
  int max;                      // current number of fish obtained from lake
  int initial;                                         // number of fish in first 5-min interval
  int decrease;                                                // decrease after each 5 min
  int nextlake;                                                // time to next lake
} lakes[MAXLAKES];

int best[MAXLAKES],                                     // current best # of mins at each lake
  total, runningtotal;

int findMin(int last)
  //
  // determine lake with the minimum # of fish in it's last 5-min interval
  //
{
  int minval = 100000;
  int index = -1;
  int i;
  for(i=0; i<last; i++) {
    if (lakes[i].max == 0)
      continue;
    if (lakes[i].fish[lakes[i].max-1] <= minval) {
      minval = lakes[i].fish[lakes[i].max-1];
      index = i;
    }
  }
  return index;
}

void main()
{
  int n, h, first = 1;
  cin >> n;
  while (n != 0) {
    if (first) {
      first = 0;
    } else {
      cout << endl;
    }
    for(int i=0; i<n; i++) {                        // initialize lakes
      lakes[i].max = 0;
      best[i] = 0;
    }
    total = 0;
    cin >> h;
    h *= 12;
    for(int i=0; i<n; i++)                                    // get lake and interlake data
      cin >> lakes[i].initial;
    for(int i=0; i<n; i++)
      cin >> lakes[i].decrease;
    for(int i=0; i<n-1; i++)
      cin >> lakes[i].nextlake;
    // process lake 0
    int currfish = lakes[0].initial;
    int j=0;
    while (currfish > 0 && j < h) {           // determine # of fish for
      lakes[0].fish[j++] = currfish; //   each 5-min interval...
      total += currfish;
      currfish -= lakes[0].decrease;
    }
    for(;j<h;j++)
      lakes[0].fish[j] = 0;                           // ... even if # of fish = 0
    best[0] = lakes[0].max = h;

    runningtotal = total;
    for(int i=1; i<n; i++) {
      // for each 5 min to go to next
      //   lake, take away the minimum
      //   5-min fishing interval from
      //   a previous lake
      int change = 0;
      for(int j=0; j<lakes[i-1].nextlake; j++) {
	int l = findMin(i);
	if (l== -1) {
	  break;                                   // out of lakes!
	}
	change -= lakes[l].fish[--lakes[l].max];
      }
      // fish this lake while # of
      //   fish in this lake larger
      //   then # of fish in a previous
      //   lake
      int currfish = lakes[i].initial;
      int l = findMin(i);
      while (l != -1 && lakes[l].fish[lakes[l].max-1] < currfish) {
	change += currfish-lakes[l].fish[--lakes[l].max];
	lakes[i].fish[lakes[i].max++] = currfish;
	currfish -= lakes[i].decrease;
	if (currfish <=0)
	  break;
	l = findMin(i);
      }
      // incorporate effect fishing
      //   in this lake has on overall
      //   fish count...
      runningtotal += change;
      if (runningtotal > total) {            // ... and update if it's a new
	for(int j=0; j<=i; j++)              //   max                
	  best[j] = lakes[j].max;
	total = runningtotal;
      }
    }
    // output results
    cout << best[0]*5;
    for(int i=1; i<n; i++)
      cout << ", " << best[i]*5;
    cout << endl << "Number of fish expected: " << total << endl;
    cin >> n;
  }
}
