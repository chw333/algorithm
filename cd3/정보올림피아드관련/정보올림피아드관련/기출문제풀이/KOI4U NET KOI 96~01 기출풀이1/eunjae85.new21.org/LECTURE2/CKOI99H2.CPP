#include <fstream.h>

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3

typedef struct {
	int value;
	int x1, y1, x2, y2;
} sol;

char map[100][100][4] = {0, };

sol best;

void input ()
{
	ifstream in ("input.txt");

	int x, y;
	in >> x >> y;
	x--;
	y--;

	int t;
	in >> t;

	for (int i = 0; i < t; i++) {
		char t;
		int c;

		in >> t >> c;

		switch (t) {
			case 'R' : { for ( ; c > 0; c--) {
										 map[x  ][y  ][RIGHT] = 1;
										 map[x-1][y  ][LEFT ] = 1;
										 x++; }
									 break; }

			case 'L' : { for ( ; c > 0; c--) {
										 map[x  ][y  ][LEFT ] = 1;
										 map[x+1][y  ][RIGHT] = 1;
										 x--; }
									 break; }

			case 'U' : { for ( ; c > 0; c--) {
										 map[x  ][y  ][UP   ] = 1;
										 map[x  ][y+1][DOWN ] = 1;
										 y++; }
									 break; }

			case 'D' : { for ( ; c > 0; c--) {
										 map[x  ][y  ][DOWN ] = 1;
										 map[x  ][y-1][UP   ] = 1;
										 y--; }
									 break; }
		}
	}

	in.close ();
}

void process ()
{
	best.value = 20000;

	for (int x = 0; x < 100; x++)
		for (int y = 0; y < 100; y++)
			if (map[x][y][UP] && map[x][y][LEFT]) {

				int rx = x - 1;
				int ry = y;

				while (map[rx][ry][LEFT] && !map[rx][ry][UP])
					rx--;

				if (!map[rx][ry][UP]) continue;

				ry++;

				while (map[rx][ry][UP] && !map[rx][ry][RIGHT])
					ry++;

				if (!map[rx][ry][RIGHT]) continue;

				if (!map[x][ry][DOWN]) continue;

				int flag = 0;
				for (int i = rx + 1; i <= x - 1; i++)
					if (!map[i][ry][RIGHT] || map[i][ry][DOWN]) flag = 1;

				for (i = y + 1; i <= ry - 1; i++)
					if (!map[x][i][UP] || map[x][i][LEFT]) flag = 1;

				if (flag) continue;

				if ((x - rx) * (ry - y) < best.value) {
					best.value = (x - rx) * (ry - y);
					best.x1 = rx;
					best.y1 = y;
					best.x2 = x;
					best.y2 = ry;
				}
			}
}

void output ()
{
	ofstream out ("output.txt");

	out << best.x1 + 1 << ' ' << best.y1 + 1 << endl;
	out << best.x2 + 1 << ' ' << best.y2 + 1 << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
