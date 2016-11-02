#include<fstream.h>

ifstream in ("inside.in");
ofstream out ("inside.out");

int n, cnt = 0;
int black[20][2], red[2];

int ccw(int ax, int ay, int bx, int by, int cx, int cy)
{
	int S;
	S = ax * by + bx * cy + cx * ay - ay * bx - by * cx - cy * ax;
	if(S <= 0){
		if(S < 0){
			return -1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

void main(void)
{
	int i, j, k, check[3];
	long double x, y;
	in >> n;
	for(i = 0; i < n; i++){
		in >> x >> y;
		black[i][0] = (int) ((x + 1) * 100);
		black[i][1] = (int) ((y + 1) * 100);
	}
	in >> x >> y;
	red[0] = (int) ((x + 1) * 100);
	red[1] = (int) ((y + 1) * 100);
	for(i = 0; i < n - 2; i++){
		for(j = i + 1; j < n - 1; j++){
			for(k = j + 1; k < n; k++){
				check[0] = ccw(black[i][0], black[i][1], black[j][0], black[j][1], red[0], red[1]);
				check[1] = ccw(black[k][0], black[k][1], black[i][0], black[i][1], red[0], red[1]);
				check[2] = ccw(black[j][0], black[j][1], black[k][0], black[k][1], red[0], red[1]);
				if(check[0] == check[1] && check[1] == check[2] && check[0] != 0){
					cnt++;
				}
			}
		}
	}
	out << cnt;
}
