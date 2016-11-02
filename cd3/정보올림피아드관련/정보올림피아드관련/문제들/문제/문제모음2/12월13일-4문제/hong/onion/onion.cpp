#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ifstream in("onion08.in");
ofstream out("onion08.out");

char ostr[512], res[512];
int find, end;

void inp()
{
	in >>ostr;
}

void oup()
{
	out << res;
}

void Do(char *o, char *ins, int &inv, char *outs, int &outv)
{
	int i=0, cnt=0;

	while(strlen(o)>i) { //����...
		if(o[i]=='(') { cnt++; if(inv<cnt) inv=cnt; }
		if(o[i]==')') cnt--;
		if(cnt==0) { strncpy(ins,o,i+1); strcpy(outs, &o[i+1]); ins[i+1]='\0'; i++; break; }
		i++;
	}
	i=0;
	while(strlen(outs)>i) { //�ٱ���...
		if(outs[i]=='(') outv++;
		i++;
	}
	inv--;  // ���� ���� �ϳ� ����
	strcpy(ins,&ins[1]); 
	ins[strlen(ins)-1]='\0';
}
char ret[512];
char temp[512];
char *s_node(char *n)
{
	int i, inv=0, outv=0;
	char ins[512]={0,}, outs[512]={0,};
	
	Do(n,ins,inv,outs,outv);

	//�־��� ���� ������.
	if((inv==0 && outv==1) || (inv==1 && outv==0) || (inv==1 && outv==1)) {
		find=1;
	} else if(outv>1) { // �ٱ����� �˻�.
		if(!find) strcpy(outs,s_node(outs));
	} else { // ���� �˻�.
		if(!find) strcpy(ins,s_node(ins));
	}
	//���� ���� ������.
	if(find && !end && (outv-1)!=-1) {
		ins[0]=outs[0]='\0';
		for(i=1;i<=(inv+1);i++) strcat(ins,"()");
		sprintf(temp,"%s",ins);
		strcpy(ins,temp);
		for(i=1;i<=(outv-1);i++) strcat(outs,"()");
		end=1;
	}
	sprintf(ret,"(%s)%s",ins,outs);
	return ret;
}

void proc()
{
	int i, inv=0, outv=0;
	char ins[512]={0,}, outs[512]={0,};
	
	Do(ostr,ins,inv,outs,outv);

	if((inv==0 && outv==1) || (inv==1 && outv==0) || (inv==1 && outv==1)) {
		find=1;
	} else if(outv>1) { // �ٱ����� �˻�.
		if(!find) strcpy(outs,s_node(outs));
	} else { // ���� �˻�.
		if(!find) strcpy(ins,s_node(ins));
	}
	if(find && !end && (outv-1)!=-1) {
		ins[0]=outs[0]='\0';
		for(i=1;i<=(inv+1);i++) strcat(ins,"()");
		sprintf(temp,"%s",ins);
		strcpy(ins,temp);
		for(i=1;i<=(outv-1);i++) strcat(outs,"()");
		end=1;
	} else if(find && !end && (outv-1)==-1) {
		ins[0]=outs[0]='\0';
		for(i=1;i<=(inv);i++) strcat(ins,"()");
		sprintf(temp,"%s",ins);
		strcpy(ins,temp);
		for(i=1;i<=(outv+1);i++) strcat(outs,"()");
		end=1;
	}
	sprintf(res,"(%s)%s",ins,outs);
}
void main()
{
	inp();
	proc();
	oup();
}