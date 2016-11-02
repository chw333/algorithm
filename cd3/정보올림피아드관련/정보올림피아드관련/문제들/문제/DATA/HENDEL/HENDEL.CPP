#include <fstream.h>

int n;
char a[1000][1000]={0,};
int table[1000+1][1000+1]={0,};
char trace[1000][1000]={0,};
struct s {
	int x,y;
} solution[2000];

ifstream in("hendel.in");
ofstream out("hendel.out");

void input()
{
	int i,j;
	in >> n;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			in >> a[i][j];
}
void output()
{
	int i,j;

	out << table[0][0] <<endl;
	for(i=0;i<=n*2-2;i++) {
		out << solution[i].y << " " << solution[i].x <<endl;
	}
/*	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			out << table[i][j] << " ";
		}
		out << endl;
	}
	out << endl;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			out << (int)trace[i][j] << " ";
		}
		out << endl;
	}
*/
}
void process()
{
	int i,j,k;

	for(i=0;i<n;i++) {
		table[n][i]=0;
		table[i][n]=0;
	}
	for(i=n-1;i>=0;i--) {
		for(j=n-1;j>=0;j--) {
			if(table[i+1][j]>table[i][j+1]) {
				table[i][j]=table[i+1][j]+a[i][j]-'0';
				trace[i][j]=1;  // up
			} else {
				table[i][j]=table[i][j+1]+a[i][j]-'0';
				trace[i][j]=2;	// left
			}
		}
	}
    i=0;
    j=0;
    k=n*2-2;
	solution[k].x=j;
	solution[k].y=i;
	k--;
	while (!(solution[k+1].x==n-1 && solution[k+1].y==n-1)) {
		solution[k].x=solution[k+1].x;
		solution[k].y=solution[k+1].y;
		if(solution[k].y==n-1) {			
			solution[k].x=solution[k+1].x+1;
		} else if(solution[k].x==n-1) {
			solution[k].y=solution[k+1].y+1;
		} else if(trace[solution[k].y][solution[k].x]==2) {
			solution[k].x=solution[k+1].x+1;
		} else if(trace[solution[k].y][solution[k].x]==1){
			solution[k].y=solution[k+1].y+1;
		}
		k--;
	}
}
void main()
{
	input();
	process();
	output();
}