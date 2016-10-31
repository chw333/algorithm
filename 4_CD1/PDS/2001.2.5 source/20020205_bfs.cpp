#include <stdio.h>
#include <fstream.h>

int map[21][21],n,start_i,start_j,end_i,end_j;
int ar[4][2]={{-1,0},{0,1},{1,0},{0,-1}},table[21][21];
int queue[100000][2],head,tail,count,min=9999,min_star[2];
int chk[21][21],star[441][2],star_n;

void input(void)
{
	int i,j;
	char temp;

	ifstream in("input.txt");
	in >> n;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++){
			in >> temp;
			if(temp!='*') map[i][j]=1;
			else{ star[++star_n][0]=i; star[star_n][1]=j; }
			if(temp=='S'){ start_i=i; start_j=j; }
			if(temp=='T'){ end_i=i; end_j=j; }
		}
}

void bfs(void)
{
	int i,j,k;

	queue[++tail][0]=start_i;
	queue[tail][1]=start_j;
	chk[start_i][start_j]=1;

	while(head!=tail){
		i=queue[++head][0];
		j=queue[head][1];
		chk[i][j]=1;
		for(k=0; k<=3; k++)
			if(map[i+ar[k][0]][j+ar[k][1]]==1 && chk[i+ar[k][0]][j+ar[k][1]]==0){
				queue[++tail][0]=i+ar[k][0];
				queue[tail][1]=j+ar[k][1];
				table[queue[tail][0]][queue[tail][1]]=table[i][j]+1;
			}
	}
}

void chk_n_table_init(void)
{
	int i,j;

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++){
			chk[i][j]=0;
			table[i][j]=0;
		}
}

void main(void)
{
	int i;

	input();
	for(i=1; i<=star_n; i++){
		map[star[i][0]][star[i][1]]=1;
		
		chk_n_table_init();
		bfs();
		if(table[end_i][end_j]!=0 && table[end_i][end_j]<min){ 
			min=table[end_i][end_j];
			min_star[0]=star[i][0];
			min_star[1]=star[i][1];
		}
		
		map[star[i][0]][star[i][1]]=0;
	}
	printf("%d %d\n",min_star[0],min_star[1]);
	printf("%d\n",min);
}