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
//answer���� �簢������ ���Ǵ� ���̰� ����ǰ�
//answer2���� �����ﰢ������ ���Ǵ� �κ��� 2���� ����ȴ�.

void inputdata(void)
{
	int q,w,e;
	double ttt;
	ifstream in("tr.in");
	in>>n;
	for (q=1;q<=n;q++){
		in>>t[q].x>>t[q].y>>t[q].l;
	}
	quick2(1,n); //�Է� ���� �ﰢ���� x��ǥ�� �����Ѵ�. 
	
	//�ﰢ������ �����ؼ� x+y+m������ �����Ѵ�.
	//(�����ﰢ���� ������ �������� �������� �����ϴ°�)
	for (q=1;q<=n;q++){
		t2[q].x=t[q].x;
		t2[q].y=t[q].y;
		t2[q].l=t[q].l;
		t2[q].p=t[q].x+t[q].y+t[q].l;
	}
	quick3(1,n);

}

//Y���� �ڸ��� ���е��� ã�Ƴ���.
void initialize(void)
{
	int q,w,e;
	int temp;

	//�� �ﰢ������ �� �Ʒ��� ã�Ƴ���
	for (q=1;q<=n;q++){
		tp[2*q-1]=t[q].y;
		tp[2*q]=t[q].y+t[q].l;
	}
	
	//�� �ﰢ���� ���μ��� �ٸ� �ﰢ���� ������ ���� ��� �� ������ Y��ǥ�� �߰��Ѵ�
	e=2*n;
	for (q=1;q<=n;q++){ 
		for (w=1;w<=n;w++){
			if (q==w) continue;
			if (t[q].x>t[w].x||t[q].x+t[q].l<t[w].x) continue;
			if (t[q].y+t[q].l<t[w].y) continue;
			if (t[q].y>t[w].y+t[w].l) continue;
			//�� ��� w�� ������ q�� �񽺵��� ���� ������ �ִ�
			temp=t[q].y+t[q].l-(t[w].x-t[q].x);
			tp[++e]=temp;
		}
	}

	//�����ؼ�
	quick(1,e);
	tp[0]=-1*MAXIMUM;

	//��ġ�� ���� ���ָ鼭 y[]�迭�� �������ش�.
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


	//�÷��� ������ ����ϰ�..
	for (q=1;q<yn;q++) {
		down=y[q]; up=y[q+1];
		len=up-down;
		ten=0; en1=0; en2=0;
		//�� ������ �����ϴ� �κ�, �� ���μ��� �̾Ƴ��ش�.(�̶�, x��ǥ�� ������ ���ĵ� ����)
		for (w=1;w<=n;w++){
			if (t[w].y<=down&&t[w].y+t[w].l>=up) {
				en1++;
				ed1[en1].x=t[w].x; 
			}
		}
		//�� ������ ������ �κ�, �� �񽺵��� ���� �̾Ƴ��ش�.(�̶�, x��ǥ�� ������ ���ĵȻ���)
		for (w=1;w<=n;w++){
			if (t2[w].y<=down&&t2[w].y+t2[w].l>=up) {
				en2++;
				ed2[en2].x=t2[w].x+(t2[w].y+t2[w].l-up);
				ed2[en2].p=-1;
			}
		}
	
		//en1==en2�̴�(�翬������)

		ten=en1+en2;
		ed1[en1+1].x=MAXIMUM;
		ed2[en2+1].x=MAXIMUM;
		pa=1;pb=1;
		
		//ed1[]�� ed2[]�� �̾��־��� ������ �պ���Ų��(x��ǥ����, ���� ��쿡�� ���۹迭�� �켱����)
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
			//�̺κ��� �񽺵��ϰ� ������ �κ��� ����Ͽ� �ش�
			if (count==0&&tmp_ed[w].p==-1) {
				size+=(len*(tmp_ed[w].x-tmp_ed[w-1].x) );
				asdf=len*len;
				if (asdf%2==0) size+=(asdf/2);
				else {answer2++; size+=((asdf-1)/2); }
			}
		}
			
		//�信�ٰ� ���Ѵ�.
		answer+=size;
		
	}
}

//���Ŀ� ���̴� �Լ���
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