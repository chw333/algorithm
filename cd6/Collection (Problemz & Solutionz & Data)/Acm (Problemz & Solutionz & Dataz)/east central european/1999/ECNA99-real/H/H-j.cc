/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

#include <iostream>

struct sq {
  char letter;
  int cluster;
};
sq *board[17];

void printBoard()
{
  return;
  for(int row=10; row>=1; row--) {
    for(int col=1; board[col] != 0; col++) {
      cout << board[col][row].letter;
    }
    cout << endl;
  }
  cout << endl;
}

void readBoard()
{
  board[0] = board[16] = 0;
  for(int col=1; col<=15; col++)
    board[col] = new sq[12];
  for(int row=11; row>=0; row-=11)
    for(int col=1; col<=15; col++)
      board[col][row].letter = ' ';
  for(int row=10; row>=1; row--)
    for(int col=1; col<=15; col++) {
      cin >> board[col][row].letter;
      board[col][row].cluster = 0;
    }
}

int findCluster(int cnum, int r, int c, char ch)
{
  if (board[c] == 0 || board[c][r].letter != ch || board[c][r].cluster != 0)
    return 0;
  else  {
    board[c][r].cluster = cnum;
    return 1 + findCluster(cnum,r-1,c,ch)
      + findCluster(cnum,r,c-1,ch)
      + findCluster(cnum,r+1,c,ch)
      + findCluster(cnum,r,c+1,ch);
  }
}

int processBoard(int &row, int &col)
{
  int maxsize = 0, size, cnum=1;

  for(int c=1; board[c] != 0; c++) {
    //cout << "start col " << c << endl;
    for(int r=1; board[c][r].letter != ' '; r++) {
      if (board[c][r].cluster == 0) {
	size = findCluster(cnum, r, c, board[c][r].letter);
	//cout << "cluster size " << size << " at " << r << ',' << c << endl;
	if (size > maxsize) {
	  maxsize = size;
	  row = r;
	  col = c;
	}
	cnum++;
      }
    }
  }
  return maxsize;
}

void removeCluster(int cnum, int r, int c)
{
  if (board[c] != 0 && board[c][r].letter != ' ' && board[c][r].cluster == cnum) {
    board[c][r].letter = ' ';
    removeCluster(cnum,r-1,c);
    removeCluster(cnum,r,c-1);
    removeCluster(cnum,r+1,c);
    removeCluster(cnum,r,c+1);
  }
}



bool remakeBoard(int r, int c)
{
  removeCluster(board[c][r].cluster, r, c);
  //printBoard();
  for(int col=1; board[col] != 0; col++) {
    //cout << "process col " << col << endl;
    int row=1, row2;
    while (1) {                                                                       // compress col
      while (board[col][row].letter != ' ')
	row++;
      row2 = row;
      while (row2 <11 && board[col][row2].letter == ' ')
	row2++;
      int i=row;
      for(int j=row2; j<=11; i++, j++)
	board[col][i] = board[col][j];
      if (row2 == 11)
	break;
      for(;i<=10; i++)
	board[col][i].letter = ' ';
    }
    for(row=1; row<10; row++)                         // check for empty col
      if (board[col][row].letter != ' ')
	break;
    if (board[col][row].letter == ' ')
      board[col] = 0;
  }
  //cout << "compress cols " << endl;
  int col=1, col2;
  while (1) {                                                          // compress cols
    while (board[col] != 0)
      col++;
    col2 = col;
    while (col2 < 16 && board[col2] == 0)
      col2++;
    int i=col;
    for(int j=col2; j<=16; i++, j++)
      board[i] = board[j];
    if (col2 == 16)
      break;
    for(;i<=15; i++)
      board[i] = 0;
  }

  if (board[1] == 0)                   // check for empty board
    return true;
  for(int col=1; board[col] != 0; col++)       // reset clusters
    for(int row=1; row<=10; row++)
      board[col][row].cluster = 0;
  return false;
}


void main()
{
  int ngames;
  cin >> ngames;
  for(int game = 1; game <=ngames; game++) {
    readBoard();
    int score = 0;
    int size, row, col, rem = 150;
    int move = 0;
    printBoard();
    if (game > 1) {
      cout << endl;
    }
    cout << "Game " << game << ":" << endl << endl;
    while((size = processBoard(row, col)) > 1) {
      //cout << "size = " << size << ", row,col = " << row << ',' << col << endl;
      cout << "Move " << ++move << " at (" << row << "," << col << "): "
	   << "removed " << size << " balls of color " 
	   << board[col][row].letter << ", "
	   << "got " << (size-2)*(size-2) << " points." << endl;
      score += (size-2)*(size-2);
      rem -= size;
      if (remakeBoard(row, col))
	break;
      //cout << "back fro remakeBoard" << endl;
      printBoard();
    }
    if (rem == 0) {
      score += 1000;
    }
    cout << "Final score: " << score << ", with " <<  rem
	 << " balls remaining." << endl;
  }
}

