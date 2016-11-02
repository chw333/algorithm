/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

#include <iostream>
#include <iomanip>

struct side {
  int p1, p2;
  bool used;
  int t1, t2;
} board[18];

int triangles[10], score[2];

void initBoard()
{
  board[0].p1 = 1; board[0].p2 = 2;
  board[0].t1 = 1; board[0].t2 = 0;
  board[1].p1 = 1; board[1].p2 = 3;
  board[1].t1 = 1; board[1].t2 = 0;
  board[2].p1 = 2; board[2].p2 = 3;
  board[2].t1 = 1; board[2].t2 = 3;
  board[3].p1 = 2; board[3].p2 = 4;
  board[3].t1 = 2; board[3].t2 = 0;
  board[4].p1 = 2; board[4].p2 = 5;
  board[4].t1 = 2; board[4].t2 = 3;
  board[5].p1 = 3; board[5].p2 = 5;
  board[5].t1 = 3; board[5].t2 = 4;
  board[6].p1 = 3; board[6].p2 = 6;
  board[6].t1 = 4; board[6].t2 = 0;
  board[7].p1 = 4; board[7].p2 = 5;
  board[7].t1 = 2; board[7].t2 = 6;
  board[8].p1 = 4; board[8].p2 = 7;
  board[8].t1 = 5; board[8].t2 = 0;
  board[9].p1 = 4; board[9].p2 = 8;
  board[9].t1 = 5; board[9].t2 = 6;
  board[10].p1 = 5; board[10].p2 = 6;
  board[10].t1 = 4; board[10].t2 = 8;
  board[11].p1 = 5; board[11].p2 = 8;
  board[11].t1 = 6; board[11].t2 = 7;
  board[12].p1 = 5; board[12].p2 = 9;
  board[12].t1 = 7; board[12].t2 = 8;
  board[13].p1 = 6; board[13].p2 = 9;
  board[13].t1 = 8; board[13].t2 = 9;
  board[14].p1 = 6; board[14].p2 = 10;
  board[14].t1 = 9; board[14].t2 = 0;
  board[15].p1 = 7; board[15].p2 = 8;
  board[15].t1 = 5; board[15].t2 = 0;
  board[16].p1 = 8; board[16].p2 = 9;
  board[16].t1 = 7; board[16].t2 = 0;
  board[17].p1 = 9; board[17].p2 = 10;
  board[17].t1 = 9; board[17].t2 = 0;
}

int findSide(int p1, int p2)
{
  for(int i=0; i<18; i++) {
    if (board[i].p1 == p1 && board[i].p2 == p2)
      return i;
  }
  cout << "ERROR: illegal side " << p1 << ',' << p2 << endl;
  return 0;
}

void initGame(int &player, int &nmoves)
{
  cin >> nmoves;
  triangles[0] = 100;
  for(int i=1; i<=9; i++)
    triangles[i] = 0;
  for(int i=0; i<18; i++)
    board[i].used = false;
  player = 0;
  score[0] = score[1] = 0;
  for(int i=0; i<nmoves; i++) {
    int p1, p2;
    cin >> p1 >> p2;
    int index = findSide(p1, p2);
    board[index].used = true;
    triangles[board[index].t1] += 1;
    triangles[board[index].t2] += 1;
    if (triangles[board[index].t1] != 3 &&
	triangles[board[index].t2] != 3)
      player = 1-player;
    else {
      if (triangles[board[index].t1] == 3) {
	score[player]++;
      }
      if (triangles[board[index].t2] == 3) {
	score[player]++;
      }
    }
  }
}

int playerAPrep(int);
int playerBPrep(int);
int playerB(int, int);

int playerA(int nmoves, int start)
{
  if (nmoves == 18)
    return score[0]-score[1];
  else {

    int evalMax = -10, eval;
    for(int i=start; i<18; i++) {
      if (board[i].used)
	continue;
      //if (nmoves <8) cout << setw(2*nmoves) << "A tries " << i << endl;
      board[i].used = true;
      triangles[board[i].t1] += 1;
      triangles[board[i].t2] += 1;
      if (triangles[board[i].t1] == 3 || triangles[board[i].t2] == 3) {
	bool check = false;
	if (triangles[board[i].t1] == 3)
	  score[0]++;
	else if (triangles[board[i].t1] == 2)
	  check = true;
	if (triangles[board[i].t2] == 3)
	  score[0]++;
	else if (triangles[board[i].t2] == 2)
	  check = true;
	int j=i+1;
	if (check)
	  for(j=0; j<=i; j++)
	    if (!board[j].used && (triangles[board[j].t1] == 2 || triangles[board[j].t2] == 2))
	      break;
	//	eval = playerA(nmoves+1, j);
	eval = playerA(nmoves+1, 0);
      }
      else
	eval = playerB(nmoves+1, 0);
      //if (nmoves <8) cout << setw(2*nmoves) << "A gets " << eval << endl;
      if (eval > evalMax)
	evalMax = eval;
      if (triangles[board[i].t1] == 3)
	score[0]--;
      if (triangles[board[i].t2] == 3)
	score[0]--;
      triangles[board[i].t1] -= 1;
      triangles[board[i].t2] -= 1;
      board[i].used = false;
      
      /* howard's addition, prune early */
      if (evalMax > 0) {
	return evalMax;
      }
    }
    return evalMax;
  }
}

int playerB(int nmoves, int start)
{
  if (nmoves == 18)
    return score[0]-score[1];
  else {
    int evalMin = 10, eval;
    for(int i=start; i<18; i++) {
      if (board[i].used)
	continue;
      //if (nmoves <8) cout << setw(2*nmoves) << "B tries " << i << endl;
      board[i].used = true;
      triangles[board[i].t1] += 1;
      triangles[board[i].t2] += 1;
      if (triangles[board[i].t1] == 3 || triangles[board[i].t2] == 3) {
	bool check = false;
	if (triangles[board[i].t1] == 3)
	  score[1]++;
	else if (triangles[board[i].t1] == 2)
	  check = true;
	if (triangles[board[i].t2] == 3)
	  score[1]++;
	else if (triangles[board[i].t2] == 2)
	  check = true;
	int newstart=i+1;
	if (check)
	  for(newstart=0; newstart<=i; newstart++)
	    if (!board[newstart].used && (triangles[board[newstart].t1] == 2 || triangles[board[newstart].t2] == 2))
	      break;
	//eval = playerB(nmoves+1, newstart);
	eval = playerB(nmoves+1, 0);
      }
      else
	eval = playerA(nmoves+1, 0);

      //if (nmoves <8) cout << setw(2*nmoves) << "B gets " << eval << endl;
      if (eval < evalMin)
	evalMin = eval;
      if (triangles[board[i].t1] == 3)
	score[1]--;
      if (triangles[board[i].t2] == 3)
	score[1]--;
      triangles[board[i].t1] -= 1;
      triangles[board[i].t2] -= 1;
      board[i].used = false;

      /* howard's addition, prune early */
      if (evalMin < 0) {
	return evalMin;
      }
    }
    return evalMin;
  }
}

void main()
{
  int ngames;
  cin >>ngames;
  initBoard();
  for(int game =1; game<=ngames; game++) {
    int player, nmoves;
    initGame(player, nmoves);
    int result;
    if (player==0)
      result = playerA(nmoves, 0);
    else
      result = playerB(nmoves, 0);
    cout << "Game " << game << ": ";
    if (result > 0)
      cout << "A wins." << endl;
    else
      cout << "B wins." << endl;
  }
}
