#include <fstream.h>

#define MAX 2002
#define MAXIMUM 10000001

void inputdata(void);
void initialize(void);
void process(void);
void quick(int, int);
void quick2(int, int);
void quick3(int, int);
void outputdata(void);

int n;
struct {
	int x,y,l,p;
} t[MAX], t2[MAX];
int tp[MAX*MAX], y[MAX*MAX], yn;
struct {
	int x,p;
} tmp_ed[MAX*2], ed1[MAX*2], ed2[MAX*2];
int ten, en1, en2;
int answer=0.0, answer2=0.0;
//answer에는 사각형으로 계산되는 넓이가 저장되고
//answer2에는 직각삼각형으로 계산되는 부분의 2곱이 저장된다.

void inputdata(void)
{
	int q,w,e;
	double ttt;
	ifstream in("tr.in");
	in>>n;
	for (q=1;q<=n;q++){
		in>>t[q].x>>t[q].y>>t[q].l;
	}
	quick2(1,n); //입력 받은 삼각형을 x좌표로 정렬한다. 
	
	//삼각형들을 복사해서 x+y+m값으로 정렬한다.
	//(직각삼각형의 빗면을 기준으로 왼쪽으로 정렬하는것)
	for (q=1;q<=n;q++){
		t2[q].x=t[q].x;
		t2[q].y=t[q].y;
		t2[q].l=t[q].l;
		t2[q].p=t[q].x+t[q].y+t[q].l;
	}
	quick3(1,n);

}

//Y축을 자르는 선분들을 찾아낸다.
void initialize(void)
{
	int q,w,e;
	int temp;

	//각 삼각형들의 위 아래를 찾아내고
	for (q=1;q<=n;q++){
		tp[2*q-1]=t[q].y;
		tp[2*q]=t[q].y+t[q].l;
	}
	
	//한 삼각형의 세로선이 다른 삼각형의 빗면을 나눌 경우 그 교점의 Y좌표도 추가한다
	e=2*n;
	for (q=1;q<=n;q++){ 
		for (w=1;w<=n;w++){
			if (q==w) continue;
			if (t[q].x>t[w].x||t[q].x+t[q].l<t[w].x) continue;
			if (t[q].y+t[q].l<t[w].y) continue;
			if (t[q].y>t[w].y+t[w].l) continue;
			//이 경우 w의 수선이 q의 비스듬한 선을 지나고 있다
			temp=t[q].y+t[q].l-(t[w].x-t[q].x);
			tp[++e]=temp;
		}
	}

	//정렬해서
	quick(1,e);
	tp[0]=-1*MAXIMUM;

	//겹치는 선은 빼주면서 y[]배열에 정리해준다.
	for (q=1;q<=e;q++){
		if (tp[q]>tp[q-1]) {
			y[++yn]=tp[q];
		}
	}
	tmp_ed[0].x=-1*MAXIMUM;
}

void main(void)
{
	inputdata();
	initialize();
	process();
	outputdata();

}

void outputdata(void)
{
	int q,w,e;

	ofstream out("tr.out");
	q=answer+answer2/2;
	out<<q;
	if (answer2%2==0) out<<".0"<<endl;
	if (answer2%2==1) out<<".5"<<endl;
}

void process(void)
{
	int q,w,e;
	int pa,pb;
	int up, down, len;
	int count;
	int size;
	int asdf;
	int tempcount=0;


	//플래인 스위핑 비슷하게..
	for (q=1;q<yn;q++) {
		down=y[q]; up=y[q+1];
		len=up-down;
		ten=0; en1=0; en2=0;
		//한 구간이 시작하는 부분, 즉 세로선을 뽑아내준다.(이때, x좌표를 축으로 정렬된 상태)
		for (w=1;w<=n;w++){
			if (t[w].y<=down&&t[w].y+t[w].l>=up) {
				en1++;
				ed1[en1].x=t[w].x; 
			}
		}
		//한 구간이 끝나는 부분, 즉 비스듬한 선을 뽑아내준다.(이때, x좌표를 축으로 정렬된상태)
		for (w=1;w<=n;w++){
			if (t2[w].y<=down&&t2[w].y+t2[w].l>=up) {
				en2++;
				ed2[en2].x=t2[w].x+(t2[w].y+t2[w].l-up);
				ed2[en2].p=-1;
			}
		}
	
		//en1==en2이다(당연하지만)

		ten=en1+en2;
		ed1[en1+1].x=MAXIMUM;
		ed2[en2+1].x=MAXIMUM;
		pa=1;pb=1;
		
		//ed1[]과 ed2[]에 뽑아주었던 선분을 합병시킨다(x좌표기준, 같은 경우에는 시작배열을 우선으로)
		for (w=1;w<=ten;w++){
			if (ed1[pa].x<=ed2[pb].x) {
				tmp_ed[w].x=ed1[pa].x;
				tmp_ed[w].p=1;
				pa++;
			}
			else {
				tmp_ed[w].x=ed2[pb].x;
				tmp_ed[w].p=-1;
				pb++;
			}
		}

		tmp_ed[0].x=tmp_ed[1].x;
		
		count=0;
		size=0;
	
		for (w=1;w<=ten;w++){
			count+=tmp_ed[w].p;
			if (count==1&&tmp_ed[w].p==1) continue; 

			if (count>0&&tmp_ed[w].x>tmp_ed[w-1].x) {
				size+=(len*(tmp_ed[w].x-tmp_ed[w-1].x) );

			}
			//이부분이 비스듬하게 끝났는 부분을 계산하여 준다
			if (count==0&&tmp_ed[w].p==-1) {
				size+=(len*(tmp_ed[w].x-tmp_ed[w-1].x) );
				asdf=len*len;
				if (asdf%2==0) size+=(asdf/2);
				else {answer2++; size+=((asdf-1)/2); }
			}
		}
			
		//답에다가 더한다.
		answer+=size;
		
	}
}

//정렬에 쓰이는 함수들
void quick3(int l, int r)
{
	if (l>=r) return;
	int pivot=t2[r].p;
	int i=l-1, j=r;
	int temp;

	for (;;){
		while (pivot>t2[++i].p);
		while (pivot<t2[--j].p);

		if (i>j) break;

		temp=t2[i].x; t2[i].x=t2[j].x; t2[j].x=temp;
		temp=t2[i].y; t2[i].y=t2[j].y; t2[j].y=temp;
		temp=t2[i].l; t2[i].l=t2[j].l; t2[j].l=temp;
		temp=t2[i].p; t2[i].p=t2[j].p; t2[j].p=temp;
	}

	temp=t2[i].x; t2[i].x=t2[r].x; t2[r].x=temp;
	temp=t2[i].y; t2[i].y=t2[r].y; t2[r].y=temp;
	temp=t2[i].l; t2[i].l=t2[r].l; t2[r].l=temp;
	temp=t2[i].p; t2[i].p=t2[r].p; t2[r].p=temp;

	quick3(l,i-1);
	quick3(i+1,r);

}
void quick2(int l, int r)
{
	if (l>=r) return;
	int pivot=t[r].x;
	int i=l-1, j=r;
	int temp;

	for (;;){
		while (pivot>t[++i].x);
		while (pivot<t[--j].x);

		if (i>j) break;

		temp=t[i].x; t[i].x=t[j].x; t[j].x=temp;
		temp=t[i].y; t[i].y=t[j].y; t[j].y=temp;
		temp=t[i].l; t[i].l=t[j].l; t[j].l=temp;
	}

	temp=t[i].x; t[i].x=t[r].x; t[r].x=temp;
	temp=t[i].y; t[i].y=t[r].y; t[r].y=temp;
	temp=t[i].l; t[i].l=t[r].l; t[r].l=temp;

	quick2(l,i-1);
	quick2(i+1,r);

}


void quick(int l, int r)
{
	if (l>=r) return;
	
	int pivot=tp[r];
	int i=l-1, j=r;
	int temp;

	for (;;){
		while (pivot>tp[++i]);
		while (pivot<tp[--j]);

		if (i>j) break;
		
		temp=tp[i]; tp[i]=tp[j]; tp[j]=temp;
	}

	temp=tp[i]; tp[i]=tp[r]; tp[r]=temp;

	quick(l,i-1);
	quick(i+1,r);
}