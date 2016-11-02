#include <fstream.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 1000
ifstream in("exchange05.in");
ofstream out("exchange05b.out");


struct _n {
	unsigned long crate; // 기준 비율의 개수
	unsigned long trate; // 대상 비율의 개수
    int target; // 현재 인덱스
	//struct _n *next;
};

struct _n node[MAX][MAX];

int nodecnt[MAX];
int nodescnt;
int visited[MAX];

char list[MAX][255];
int listcnt;


int str2idx(char *str, int sw)
{
	int i;
	int lc=listcnt;
	if(sw==0) { // for insert
		for(i=0;i<lc;i++) {
			if(strcmp(list[i],str)==0) return i;
		}
		listcnt++;
		nodescnt++;
		strcpy(list[lc],str);
		return lc;
	} else { // for query
		for(i=0;i<lc;i++) {
			if(strcmp(list[i],str)==0) return i;
		}
	}
}
void addEdge(unsigned long m, int tag1, unsigned long n, int tag2)
{
/*	
	struct _n *nd = &node[tag1];
	struct _n *cur;
	while ( nd->next ) {
		nd = nd->next;
	}
	cur=new(struct _n);
	cur->target=tag2;
	cur->crate=m;
	cur->trate=n;
	cur->next=NULL;
	nd->next=cur;
*/
	node[tag1][nodecnt[tag1]].crate=m;
	node[tag1][nodecnt[tag1]].trate=n;
	node[tag1][nodecnt[tag1]].target=tag2;
	nodecnt[tag1]++;
	//node[tag1][nodecnt[tag1]].crate=m;

}
void insert(unsigned long m, char *th1, unsigned long n, char *th2)
{
	int tag1, tag2;

	tag1=str2idx(th1,0);
	tag2=str2idx(th2,0);
    addEdge(m, tag1, n, tag2); // 양쪽에 리스트를 만든다..
    addEdge(n, tag2, m, tag1);
}

unsigned long gcd(unsigned long a, unsigned long b) {
    return b == 0 ? a : gcd(b, (unsigned long) (a%b));
}

void reduce(unsigned long &m, unsigned long &n) {
    unsigned long g = gcd(m, n);
    m /= g;
    n /= g;
}


int dfs(unsigned long &m, int tag1, unsigned long &n, int tag2)
{
	unsigned long oldm, oldn;
	//struct _n *p;
	int i;

	if(tag1==tag2) 	return 1;
	else {
		visited[tag1] = 1;
		for(i=0;i<nodecnt[tag1];i++) { //p=node[tag1].next;p!=NULL;p=p->next) {
			if(!visited[node[tag1][i].target]) {
				oldm=m; oldn=n;
				m=m*node[tag1][i].crate;
				n=n*node[tag1][i].trate;
				reduce(m,n);
				if(dfs(m, node[tag1][i].target, n, tag2)) { 
					//최대 공약수로 처리
					return 1;
				} else {
					// 다시 원상 복구...
					m=oldm; n=oldn;
				}
            }
        }
        return 0;
	}
}

void query(char *th1, char *th2)
{
	int i;
	int tag1, tag2;
	unsigned long m, n;

    for(i=0;i<nodescnt;i++) visited[i]=0;
	tag1=str2idx(th1,1);
	tag2=str2idx(th2,1);
	m=1;
	n=1;
    if(dfs(m, tag1, n, tag2))
       out << m << " " << th1 << " = " << n << " " << th2 << endl;
    else
       out <<"? " << th1 << " = ? " << th2 << endl;
}
void main()
{
	char cmd, ch;
	unsigned long m, n, i;
	char thing1[255];
	char thing2[255];
	int ncnt=0, qcnt=0;
	for(in >> cmd; cmd != '.'; in >> cmd) {
		if (cmd == '!') {
			in >> m;
			in >> thing1;
			in >> ch;
			in >> n;
			in >> thing2;
			insert(m, thing1, n, thing2); // 노드 삽입 명령
			//out2 << "? " << thing2 << " = " << thing1 << endl;
			ncnt++;
		} else {
			in >> thing1;
			in >> ch;
			in >> thing2;
			query(thing1, thing2); // 질의 명령
			qcnt++;
		}
	}
	/*
	srand((unsigned)time(NULL));	
	int cc=0;
	int a, b;
	while(1) {
		if(cc==1000) break;
		a=rand()%nodescnt;
		b=rand()%nodescnt;
		if(a!=b) { out2 << "? " << list[a] << " = " << list[b] << endl; cc++; }
	}
*/
/*	
	int j;
	for(i=0;i<nodescnt;i++) {
		for(j=0;j<nodecnt[i];i++) {
			out2 << "? " << list[i] << " = " << list[node[i][j].target] << endl;
		}
	}
	*/
	out << listcnt << "," << ncnt << "," << qcnt;
}


/*
char str[100000][5];
void main()
{
	int i,j,k,m,cnt=0;
	char ch1,ch2,ch3,ch4;

	for(i=0;i<26;i++) {
		ch1=(char)('A'+i);
		for(j=i+1;j<26;j++) {
			ch2=(char)('A'+j);
			for(k=j+1;k<26;k++) {
				ch3=(char)('A'+k);
				for(m=k+1;m<26;m++) {
					ch4=(char)('A'+m);					
					str[cnt][0]=ch1;
					str[cnt][1]=ch2;
					str[cnt][2]=ch3;
					str[cnt][3]=ch4;
					str[cnt++][4]='\0';
				}
			}
		}
	}
	for(i=0;i<cnt;i++) {
		out << "! " << rand()%100+1 <<" " << str[i] << " = " <<  rand()%100+1 <<  " " << str[i+1] << endl;
	}

/*
	char ch1,ch2;
	srand((unsigned)time(NULL));

	for(i=0;i<MAX;i++) {
		if(i%5!=4) {
			ch1=(char)('a'+i%26);
			ch2=(char)('a'+i%26+1);
			//out << "! " << rand()%100 <<" " << (char)('a'+rand()%26) << (char)('a'+rand()%26) << (char)('a'+rand()%26) << " = " <<  rand()%100 << " " << (char)('a'+rand()%26) << (char)('a'+rand()%26) << (char)('a'+rand()%26) << endl;
			out << "! " << rand()%100+1 <<" " << ch1 << ch2 << " = " <<  rand()%100+1 <<  " " << (char)(ch1+1) << (char)(ch2+1) << endl;
		} else {
			ch1=(char)('a'+rand()%26);
			ch2=(char)('a'+rand()%26+1);
			//out << "? " <<(char)('a'+rand()%26) << (char)('a'+rand()%26) << (char)('a'+rand()%26) << " = " <<  (char)('a'+rand()%26) << (char)('a'+rand()%26) << (char)('a'+rand()%26) << endl;
			out << "? " << ch1 << ch2 << " = " <<  (char)(ch1+1) << (char)(ch2+1) << endl;

		}
	}

}

! 63 mango = 14 papaya
? papaya = mango
*/
