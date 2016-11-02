#include<fstream.h>
ifstream in ("poongyo.in");
ofstream out ("poongyo.out");
int data[13+2][7],gs,xnum,num[2],k,ring,count[100],visit[13+2][7],uu,a, cnt=0;

void down() // 뿡요를 떨어뜨리는 함수
{ 
	int i,j,k;
	int flag;

	for(i=13;i>=0;i--){
		for(j=0;j<6;j++){
			flag=0;
			if(data[i][j]) { // 뭔가 데이터가 있을 때만 검사.
				k=1;
				while(!data[i+k][j] && i+k<=13) {
					k++; // 제일 바닥까지
					flag=1;
				}
				if(flag) {
					data[i+k-1][j]=data[i][j];
					data[i][j]=0;
				}
			}
		}
	 }
}

void poong(int y,int x,int c) // 색깔이 같은 것을 모아서 visit[]를 1로 만든다.
{
	// 현재 값의 오른쪽과 윗쪽만 체크하자...
	if(data[y][x] == c && !visit[y][x] && y>=0 && y<14 && x>=0 && x<6) visit[y][x]=1; else return; // 탈출조건
	cnt++;
	poong(y,x+1,c); // 오른쪽
	poong(y-1,x,c); // 위쪽
	poong(y,x-1,c); // 왼쪽
	poong(y+1,x,c); // 아래쪽
}

void procvisit()
{
	int howmany=0;
	int i,j;

	for(i=0;i<=13;i++) {
		for(j=0;j<6;j++) {
			if(visit[i][j]) { 
				visit[i][j]=0;
				data[i][j]=0; 
				howmany++;
				if(howmany>=cnt) return;
			}
		}
	}
}
void initvisit()
{
	int i,j;
	for(i=0;i<=13;i++)
		for(j=0;j<6;j++)
			visit[i][j]=0;
}
void process()
{
	int i,j,flag;
	
	down();
	while (1) {
		flag=0;
		for(i=13;i>=0;i--){
			for(j=0;j<6;j++){
				if(data[i][j]) { // 뭔가 데이터가 있을 때만 검사.
					cnt=0;
					poong(i,j,data[i][j]);
					if(cnt>=4) {
						procvisit();
						count[ring]+=cnt;
						flag=1;  // 터질녀석이 있다는 말...
					} else {
						initvisit(); // visit 초기화
					}	
				}
			}
		}
		if(flag==1) { // 터질녀석이 있다는 말...
			ring++;
			down();
		} else break;
	}
}

void main()
{
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<6;j++)
			in >> data[i+2][j];		
	}
	in >> gs;	in>> xnum;	in >> num[0];	in>> num[1]; xnum = xnum-1;
	if(gs == 1){	data[0][xnum] = num[0];		data[1][xnum] = num[1];	}
	else{	data[0][xnum] = num[0]; data[0][xnum+1] = num[1]; }	
	process();
	out << ring <<endl;
	for(i=0;i<ring;i++){
		out << count[i]<<" ";
	}	
}
